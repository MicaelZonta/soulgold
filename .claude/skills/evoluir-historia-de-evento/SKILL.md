---
name: evoluir-historia-de-evento
description: Use ao transformar um evento que ja funciona (esqueleto, ou cena com falas placeholder) numa HISTORIA - reescrever dialogos pela voz de cada personagem, montar o arco dramatico da cena (ameaca ja em acao, tentativa que falha, escalada, perigo direto ao jogador, resgate, consequencia inesperada, reacao, cuidado, presente, gancho), guardar surpresas e misterios, envolver o lider local, reagir ao que o jogador carrega na party (familia Cosmog), e encenar golpes/rupturas/resgates so com movimentos e flashes. Tambem use ao receber uma lista de feedback do autor sobre uma cena. Receita tirada da Missao 1 de Blackthorn (revisao 3, 22/09/2026), validada em runtime pelo autor.
---

# Evoluir a história de um evento

O esqueleto prova que o evento **funciona**. Esta skill é o passo seguinte:
fazer ele **valer a pena**. Exemplo completo, aprovado pelo autor depois de
jogar: [`.claude/rift_missions/BLACKTHORN_ULTRABEAST/BLACKTHORN_ULTRABEAST_IMPLEMENTATION.md`](../../rift_missions/BLACKTHORN_ULTRABEAST/BLACKTHORN_ULTRABEAST_IMPLEMENTATION.md)
§5–§7 e §13; código em `data/maps/BlackthornCity/scripts.inc` (seção "Rift Mission 1").

Antes de mexer, carregue `evento-esqueleto` §7 (o que pode e o que não pode mudar)
e `encenar-cutscene` (toda coordenada nova se mede). Voz dos personagens:
`SOULGOLD_RIFT_MISSIONS_DESIGN.md` §3.1 e §3.3.

## 1. Transforme o feedback numa tabela antes de escrever

Liste cada pedido do autor numa linha e decida onde ele entra na cena. Guarde a
tabela no doc do evento (seção "Revisão N": *pedido → como ficou*). Ela serve de
checklist enquanto você escreve e de prova para o autor no final.

- **Ambiguidade que o design resolve:** siga o design e registre a escolha na
  tabela. Ex.: o pedido dizia "Gladion e o Type: Null te salvam"; no pós-game o
  parceiro dele é o Silvally (regra visual do design §1), então foi o Silvally.
- **Pedido que contradiz o design:** o pedido novo vence, mas **reescreva o
  trecho do design** — nunca deixe as duas regras vivas. Ex.: "não dar Type: Null
  ao jogador" virou "o Gladion dá um Type: Null ao fim da M1".
- **Pedido que vale para o arco inteiro** ("em todos os encontros"): implemente
  no evento atual e escreva como **regra comum** no design, marcando quais eventos
  ainda não a cumprem. Não saia reimplementando os outros sem ser pedido.
- **Sugestão no meio do trabalho:** acolha se ela simplifica (as portas trancadas
  substituíram o plano de esconder a Clair do Ginásio e resolveram mais que ele).

## 2. O arco da cena

A Missão 1 segue esta ordem. Cada passo é barato de encenar e dá à cena um
começo, um meio e um fim:

| # | Passo | Em Blackthorn |
|---|---|---|
| 1 | **O mundo já está em movimento na chegada.** A ameaça não espera o jogador. | Clair e Kingdra já enfrentam o Necrozma na rua. |
| 2 | **Uma autoridade local tenta e falha.** Mostra o tamanho da ameaça sem gastar batalha. | "Kingdra! Dragon Pulse!" → flash → "nem um arranhão". |
| 3 | **Escalada.** A situação piora por ação da ameaça. | O Necrozma abre a fenda; as UBs atravessam. |
| 4 | **Perigo direto ao jogador.** Algo vem para cima *dele*, não do cenário. | Buzzwole e Pheromosa correm até dois tiles do jogador. |
| 5 | **Resgate no último segundo, por alguém que ninguém anunciou.** | O Silvally salta na frente; o Gladion chega correndo. |
| 6 | Estrutura de jogo (escolha, batalha, retry) — **intocada**. | Escolha + boss, igual ao esqueleto. |
| 7 | **Consequência inesperada depois da vitória.** A vitória não fecha a história. | O Necrozma absorve as duas UBs e vai embora. |
| 8 | **Cada personagem reage na própria voz** ao que viu. | Clair não acredita; Looker registra; Gladion diz o que viu; Anabel diz que nada age assim. |
| 9 | **Cuidar das pessoas antes do relatório.** | Looker: "Is anyone hurt? … The report can wait a moment." |
| 10 | **Um presente com significado**, ligado ao arco de quem dá. | Gladion dá um Type: Null e devolve ao jogador a lição dele: "let it take the first step". |
| 11 | **Gancho de mistério**, sem destino. | "Volte a Olivine; a gente avisa quando abrir outra." |

Não precisa usar todos em todo evento, mas 1, 4, 7 e 11 são o que mais mudou a
sensação da cena.

## 3. Surpresa e mistério são estado de script, não só texto

- **Quem é surpresa não é anunciado antes.** Tire do briefing, das falas de
  espera e de qualquer ligação. Confira com `grep` o nome do personagem em todos
  os textos que tocam antes da cena.
- **E também não está no mapa.** Objeto com `FLAG_TEMP_*` que o `ON_TRANSITION`
  **sempre** seta no load; só a cena faz `clearflag` + `addobject`. Retry depois
  de blackout volta escondido de graça.
- **Spawn fora da câmera.** A tela vai de ~4 linhas acima a ~5 abaixo do jogador,
  e ±7 colunas. Na M1 o Gladion nasce 6 linhas acima e desce correndo para dentro
  do quadro.
- **Ninguém nomeia o mistério.** Para Johto o Necrozma é "the creature" / "that
  crystal thing". Quem sabe algo solta **uma** frase e corta ("I've seen light
  like that before. In Alola." — "Later."). O nome fica para o evento que vai
  explicá-lo.
- **O gancho não diz o próximo lugar.** O próximo briefing revela. Confira se o
  briefing seguinte não citava o gancho antigo (o da M2 dizia "Lake of Rage") e
  corrija os dois lados juntos.
- **Quem não conhece não finge conhecer.** O Looker pergunta "And who might YOU
  be?!" ao Gladion. Antes de cada fala, pergunte: o que este personagem sabe
  *agora*? (design §3.3).

## 4. Voz: poucas caixas, cada uma com intenção

- Teste editorial do design §3.3: tape o nome do falante — dá para saber quem é?
- Looker: começa teatral e se corrige ("Hello? Is this…? …Forgive me. Allow me to
  begin again."); direto no perigo; pergunta pelas pessoas primeiro.
- Anabel: precisa, distingue observação de hipótese ("It wasn't attacking
  Blackthorn. It was feeding.").
- Gladion: frases curtas e concretas; cuidado por ação ("Silvally, in front!").
- Líder local (Clair): orgulho + responsabilidade pela cidade; é ela quem chamou
  a polícia, evacuou e segurou a ameaça. Dá peso à cidade e justifica a
  evacuação sem exposição.
- Uma regra de jogo pode virar regra do mundo. A checagem de party+PC cheios
  virou a "regra da Anabel": sempre espaço para mais um Pokémon, caso uma fenda
  deixe alguém para trás. Justifica o bloqueio **e** não estraga o presente.

## 5. Reações ao que o jogador carrega (opcionais, sem estado)

Padrão das reações à família Cosmog (design §4.11), reusável para qualquer
Pokémon de história:

```asm
<Mapa>_EventScript_CosmogComment::
	specialvar VAR_RESULT, CheckMysteryEggPokemon   @ party inteira, ignora ovo
	goto_if_eq VAR_RESULT, SPECIES_NONE, <Mapa>_EventScript_CosmogCommentEnd
	bufferspeciesname STR_VAR_1, VAR_RESULT
	applymovement <PARCEIRO>, Common_Movement_ExclamationMark   @ o Pokémon percebe primeiro
	waitmovement <PARCEIRO>
	goto_if_eq VAR_RESULT, SPECIES_COSMOG, ...     @ uma fala por estágio
	...
```

- Nenhuma flag, nenhuma var persistente. Sem o Pokémon, a cena é idêntica.
- `call` num ponto onde `VAR_RESULT` não é lido depois — confira as linhas
  seguintes do chamador antes de inserir.
- Uma fala por estágio (Cosmog / Cosmoem / Solgaleo-Lunala): cada um é uma
  lembrança diferente (Nebby escapando da bolsa; Nebby virando casca; Nebby
  virando lendário).
- Depois de batalha, **cheque de novo**: a batalha pode evoluir o Pokémon. Guarde
  em `VAR_TEMP_*` se a conversa final também reage.
- Lembrar ≠ identificar: a Lillie lembra do Nebby, mas nunca chama o Pokémon do
  jogador de Nebby. Quem entregou um ovo fechado descobre a espécie na cena.

## 6. Coreografia barata que lê bem

Tudo com movimentos que já existem (`asm/macros/movement.inc`):

| Efeito | Receita |
|---|---|
| Golpe | `walk_in_place_fast_<dir>` ×2 no atacante + grito + flash |
| Flash | `fadescreenswapbuffers FADE_TO_WHITE` + `fadescreenswapbuffers FADE_FROM_WHITE` (sub-rotina) |
| Impacto / ruptura | `special ShakeCamera` curto (12 tremores, delay 4) numa sub-rotina `call`ável |
| Pulso de energia | `walk_in_place_fast_<dir>` ×3 no Pokémon parado |
| Carga | `walk_fast_<dir>` ×N, mesma sequência para os dois atacantes em linhas vizinhas (formação preservada) |
| Salto de resgate | `walk_faster_<dir>` até a borda + `jump_2_<dir>` por cima de um tile livre |
| Recuo / arrasto | `lock_facing_direction` + `walk_fast_<dir>` (recuo) ou `walk_slow_<dir>` ×2 (arrasto) + `unlock_facing_direction` |
| Aparecer/sumir de ruptura | tremor → `fadescreenswapbuffers FADE_TO_WHITE` → `addobject`/`removeobject` → `fadescreenswapbuffers FADE_FROM_WHITE` → grito |
| Espanto coletivo | `Common_Movement_ExclamationMark` em 3–4 atores seguidos, depois um `waitmovement` por ator |
| Líder que não tira os olhos da ameaça | script de objeto **sem** `faceplayer` |

**Nunca `fadescreen` no meio de uma cena que volta para o mesmo mapa.** Ao
escurecer, `fadescreen` copia `gPlttBufferFaded` por cima de `gPlttBufferUnfaded`
(`FadeScreen`, `src/field_weather.c`), e o `FADE_FROM_*` seguinte reaplica o tint
de horário em cima de paletas já tintadas. À noite (coeff 10, ~0,46) cada par de
flashes escurece a cena de novo, e em três ou quatro a cidade fica preta — sem
erro de build, só no jogo. `fadescreenswapbuffers` faz o mesmo efeito com BLDY no
hardware e não encosta nas paletas. `fadescreen` só onde um warp ou uma batalha
recarrega o mapa logo depois (o fim da cena, o retry do blackout).

**Trilha da cena.** O tema alegre da cidade tocando enquanto a ruptura abre
estraga o beat. `fadeoutbgm 4` quando alguém percebe, `playbgm <trilha>, TRUE`
quando a criatura aparece (o `TRUE` grava em `savedMusic`, então a batalha de
boss devolve a trilha certa ao voltar), e `fadedefaultbgm` no pós-cena. Carregar
mapa limpa o `savedMusic` sozinho, então o retry depois de blackout começa limpo.
Trilha nova exige ligar o `SONG_*` em `include/config/songs_enabled.h`.

Pokémon que some sozinho no meio da cena ganha **flag temporária própria**, para o
`removeobject` não mexer no elenco. Reconte o orçamento de 16 object events a
cada objeto novo (light sprite custa zero).

## 7. Cidade evacuada: tranque as portas

Em vez de esconder NPCs de dentro dos prédios, a M1 tranca as portas da cidade
durante o incidente, menos a do Pokémon Center: tabela `sLockedTownDoors` em
`src/field_control_avatar.c` (`{flag do evento, mapa, porta que fica aberta,
script}`) e um script de fala ("A note is taped to it…"). Evento novo = uma linha
na tabela + `extern` em `include/event_scripts.h`. Entradas de caverna não são
porta e ficam abertas.

## 8. Dificuldade

"Mais difícil" sem virar parede: suba **uma** barra, 5 níveis e 10 pontos de
multiplicador, e troque golpes de nível por um moveset curado com um golpe de
preparo (Bulk Up / Quiver Dance) + item (Leftovers / Life Orb). Confira que a
escala entre eventos continua crescendo.

## 9. Fechar

- `@ SKELETON:` apagado onde a fala ficou final; comentário no topo do bloco com a
  planta nova e a história em três linhas.
- Doc do evento: seções reescritas para o estado novo, a antiga marcada como
  histórico, tabela *pedido → como ficou*, runtime.
- Design: status do evento, regras comuns novas, registro da revisão.
- `make -j$(nproc)` limpo.

## Checklist

- [ ] Feedback virou tabela; ambiguidades e contradições resolvidas por escrito
- [ ] Arco: ameaça ativa na chegada, perigo ao jogador, consequência pós-vitória, gancho
- [ ] Surpresa fora dos textos anteriores **e** escondida por `FLAG_TEMP_*` sempre setada no load
- [ ] Mistério sem nome; gancho sem destino; briefing seguinte coerente
- [ ] Cada personagem só sabe o que pode saber; teste editorial das vozes
- [ ] Reações opcionais sem estado, rechecadas depois de batalha
- [ ] Toda coordenada nova medida (`dump_mapa.py`); orçamento de objetos recontado
- [ ] Estado, retry e resultados do esqueleto intactos
- [ ] Doc e design atualizados; build limpo
