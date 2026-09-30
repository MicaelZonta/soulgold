---
name: encenar-cutscene
description: Use ao escrever ou corrigir qualquer applymovement, turnobject, faceplayer ou coreografia de NPC em data/maps/*/scripts.{pory,inc} - cenas em que personagens andam, se aproximam, se encaram ou saem. Cobre como ler a colisão real do mapa, derivar direções de olhar a partir das coordenadas, e as armadilhas que fazem NPC atravessar parede, olhar pro lado errado ou ficar escondido atrás da caixa de diálogo.
---

# Encenar cutscene: movimento e olhares

Antes de escrever um único `walk_`, derive a planta da cena a partir dos
**dados reais**. Todo erro caro nesta base veio de alguém (inclusive eu)
assumir a geometria em vez de medir.

Guia narrativo complementar, com exemplo completo:
[`.claude/encenar-evento.md`](../../encenar-evento.md). Esta skill é a
parte que **não pode ser esquecida**.

## Onde editar

```bash
ls data/maps/<Mapa>/scripts.pory 2>/dev/null
```

- Existe `.pory` → edite **só o `.pory`**. O `.inc` é gerado
  (`data/%.inc: data/%.pory` no Makefile) e sua edição some no build.
- Não existe → edite o `.inc` direto. É o caso da **maioria** dos mapas
  (229 têm `.pory`, ~1058 só `.inc`).

## 1. Medir antes de escrever

```bash
python3 .claude/skills/encenar-cutscene/dump_mapa.py <Mapa>
```

Imprime a grade de colisão com as posições dos objetos e dos warps
sobrepostas. Use a saída como fonte de verdade; não confie em memória nem
em comentários antigos do script.

Se for decodificar `map.bin` na mão, o formato é (`include/global.fieldmap.h:7-9`):

| Bits | Campo | Máscara |
|------|-------|---------|
| 0-10 | metatile id | `0x07FF` |
| **11** | **colisão — 1 bit só** | `0x0800` |
| 12-15 | elevação | `0xF000` |

> ⚠️ Colisão é **1 bit** (`(v >> 11) & 1`). Usar o layout clássico do
> pokeemerald (`(v >> 10) & 3`) faz o bit alto do metatile vazar pra
> colisão e metade do chão vira parede fantasma — você vai inventar
> desvios para contornar paredes inexistentes e ao mesmo tempo mandar o
> NPC atravessar as reais. Qualquer valor ≠ 0 é intransponível
> (`GetCollisionFlagsAtCoords`, `src/event_object_movement.c:6913`).

## 2. A geometria: **y cresce para baixo**

Isto é a origem do bug mais caro desta base. Consequências diretas:

- Quem **sai de uma porta** de prédio anda para **baixo** e termina ao
  **norte** de quem está na praça. Para um NPC na praça olhar para esse
  jogador, a direção é **`DIR_NORTH`**, não `DIR_SOUTH`.
- `DIR_SOUTH` = y maior = **mais para baixo na tela**.

**Nunca escreva uma direção de cabeça.** Derive da diferença de coordenadas:

| Alvo em relação ao NPC | Direção |
|---|---|
| y menor (acima na tela) | `DIR_NORTH` |
| y maior (abaixo na tela) | `DIR_SOUTH` |
| x menor (à esquerda) | `DIR_WEST` |
| x maior (à direita) | `DIR_EAST` |

Escreva a planta final como comentário `@` no topo do bloco, com as
coordenadas de cada ator. É o que impede a próxima pessoa de refazer a
análise — e de errar o sinal.

## 3. A caixa de diálogo cobre a parte de baixo da tela

Não estacione um ator que precisa ser visto **ao sul do jogador** durante
o diálogo — a msgbox cobre exatamente essa faixa e ele some.

Pior ainda: ator + jogador + segundo ator na **mesma coluna** viram uma
"totem pole" — os sprites se sobrepõem e fica impossível dizer para quem
o NPC está olhando, porque olhar para o jogador e olhar para o parceiro
viram a mesma direção visual. Espalhe os atores em **linha, lado a lado**
(mesma `y`, `x` adjacentes), não empilhados.

## 4. `faceplayer` não serve em cutscene

`ScrCmd_faceplayer` (`src/scrcmd.c:1558`) só gira
`gObjectEvents[gSelectedObjectEvent]` — **um** objeto, e só o que o
jogador acionou com A. Numa cena automática (gatilho de frame/coord) esse
índice é indefinido.

Em cutscene use sempre **`turnobject <LOCALID>, DIR_*`** explícito, um por
ator. É determinístico e gira quantos atores você quiser.

## 5. Colisão entre atores é responsabilidade sua

`applymovement` com `walk_*` **não valida terreno** — o NPC atravessa a
parede sem erro nem travamento. Mas **atores se bloqueiam entre si**
(`DoesObjectCollideWithObjectAt`), inclusive o jogador.

Ao mover dois atores ao mesmo tempo (duas `applymovement` antes de um
único `waitmovement 0`), simule **passo a passo** e confirme que os dois
nunca querem o mesmo tile no mesmo passo. Dois padrões seguros:

- **Formação preservada:** ambos executam a *mesma* sequência a partir de
  posições deslocadas — o deslocamento se mantém e eles nunca se cruzam.
- **Sequencial:** `applymovement` A → `waitmovement 0` → `applymovement` B
  → `waitmovement 0`. Elimina qualquer ambiguidade de "quem estava onde
  naquele tick", ao custo de os dois não andarem juntos.

Evite que B entre no tile que A está desocupando **no mesmo tick** — a
checagem usa a posição do início do passo e pode falhar.

## 6. Depois da batalha os atores continuam onde pararam

`trainerbattle` não recarrega o mapa. O caminho de saída de um NPC parte
do tile onde ele **parou na cena**, não do `map.json`. Se você reposicionar
alguém no começo da cena, **recalcule a saída**.

## Checklist antes de fechar

- [ ] Rodei `dump_mapa.py` e conferi que todo tile de todo `walk_*` é `.`
- [ ] Toda `DIR_*` foi derivada da diferença de coordenadas, não de memória
- [ ] Ninguém que precisa ser visto está ao sul do jogador durante a fala
- [ ] Nenhum ator termina no tile de outro ator ou do jogador
- [ ] `waitmovement 0` depois de todo `applymovement` que precede uma fala
- [ ] Zero `faceplayer` em trecho de cutscene automática
- [ ] Caminhos de saída recalculados a partir das posições finais reais
- [ ] Movimentos órfãos apagados, não deixados para trás
- [ ] `make -j$(nproc)` limpo
