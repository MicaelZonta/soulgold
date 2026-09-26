# Sprites no SoulGold: restrições, formatos e custo de memória

Guia de referência para **qualquer** gráfico de personagem: front pic de
treinador, overworld (boneco no mapa) e mugshot. Os números daqui foram
**medidos** no build de 26/09/2026, não estimados — refaça a medição com
`sprite_gba.py rom` quando a decisão depender deles.

- Registrar overworld novo no código: skill `adicionar-npc` ([guia](adicionar-npc.md)).
- Registrar front pic / mugshot: skill `adicionar-grafico-trainer` ([guia](adicionar-grafico-trainer.md)).
- Trazer arte de fora (Showdown, DeviantArt, folha de comunidade): skill `converter-sprite`.

---

## 1. Regras que valem para todo gráfico

| Regra | Por quê | O que acontece se quebrar |
|---|---|---|
| PNG **indexado** (com paleta) | o `gbagfx` só lê paleta | erro de build |
| **≤ 16 cores contando a transparência** | hardware: 1 paleta de 16 por sprite | `gbagfx: too many colors` |
| **Índice 0 = transparente** | hardware | fundo aparece como cor sólida |
| Nenhuma cor do desenho **igual** à cor do índice 0 | ferramentas que reconstroem a paleta juntam as duas | a parte com essa cor some (o contorno preto do Guzma sumiu inteiro assim) |
| Só o `.png` vai para o git | `.4bpp`, `.4bpp.smol`, `.gbapal` são gerados | — |

`python3 dev_scripts/sprites/sprite_gba.py conferir <png>` confere tudo isso e
mede onde o boneco está em cada quadro.

---

## 2. Front pic (sprite na batalha) — 64x64, fixo

- **64x64 px**, sem exceção. Não existe front pic maior.
- **Um quadro só** (sem animação).
- Boneco com os **pés na última linha**. Os do projeto ocupam praticamente os
  64 px de altura (Guzma: x15–48, y0–63).
- Arte de Showdown / Gen 4–5 costuma ser **80x80**: precisa encolher para 64.
  Não reamostre (borra); `sprite_gba.py front` remove linhas e colunas
  repetidas espalhadas pelo corpo — ver skill `converter-sprite`.
- Mugshot (retrato na caixa de texto): mesmas regras, 64x64, gráfico separado
  e opcional.

---

## 3. Overworld (boneco no mapa)

### 3.1 A folha

9 quadros lado a lado, **nesta ordem** (`sAnimTable_Standard`):

| Quadro | Uso |
|---|---|
| 0 | parado, virado para **baixo** |
| 1 | parado, virado para **cima** |
| 2 | parado, virado para a **esquerda** |
| 3, 4 | andando para baixo |
| 5, 6 | andando para cima |
| 7, 8 | andando para a esquerda |

**Não existe quadro para a direita**: o jogo espelha a esquerda. Detalhe
assimétrico (corrente, tatuagem, franja de um lado) troca de lado quando o NPC
anda para a direita. Se a arte de origem traz uma linha "direita", ela é
descartada.

### 3.2 16x32 — o padrão

Folha **144x32**. Medido nos overworlds do projeto:

| | Limite | Gladion | Kukui | Lusamine | Looker | Lillie |
|---|---|---|---|---|---|---|
| Largura do boneco | **16, sem exceção** | 16 | 16 | 14 | 16 | 16 |
| Altura do boneco | 32 | 22 | 20 | 20 | 20 | 18 |
| Linha dos pés | 30 ou 31 | 30 | 30 | 30 | 30 | 31 |
| Topo da cabeça | — | 9 | 11 | 11 | 11 | 14 |

- **Altura de referência: 18–22 px.** Boneco de 26 px (o Guzma que chegou)
  cabe, mas fica visivelmente mais alto que todo o elenco.
- Centralizado na largura: o eixo do tile é entre as colunas 7 e 8.
- Nos quadros de passo o corpo costuma subir 1 px; os pés ficam na base.
- Boneco com 17 px de largura **não cabe**: corte 1 coluna (mão ou ponta de
  cabelo) ou vá para 32x32.

### 3.3 32x32 — a exceção

Folha **288x32** (9 quadros de 32x32). Quando usar: o boneco é **mais largo
que 16 px** e cortar estraga a arte.

Precedentes no jogo: **Quinty Plump** (único humano que só anda a pé em
32x32), Biker, ciclistas, o jogador de bike/surf/pesca e os lendários de cena.
Nenhum personagem que o SoulGold adicionou usa 32x32 ainda.

Diferenças em relação ao 16x32 (o resto do `adicionar-npc` é igual):

| Onde | 16x32 | 32x32 |
|---|---|---|
| `spritesheet_rules.mk` | `-mwidth 2 -mheight 4` | **`-mwidth 4 -mheight 4`** |
| pic table | `overworld_frame(pic, 2, 4, i)` | **`overworld_frame(pic, 4, 4, i)`** |
| graphics info `size, width, height` | `256, 16, 32` | **`512, 32, 32`** |
| `oam` / `subspriteTables` | `gObjectEventBaseOam_16x32` / `sOamTables_16x32` | **`gObjectEventBaseOam_32x32` / `sOamTables_32x32`** |
| `shadowSize` | `SHADOW_SIZE_M` | `SHADOW_SIZE_M` (Quinty usa `_L` por ser largo) |

Os quatro têm que concordar entre si: metatile, pic table e `size` errados
dão sprite picotado; regra faltando dá NPC **invisível**.

O quadro de 32x32 fica centralizado no tile do mesmo jeito que o de 16x32, e
com a mesma base: desenhe o boneco centralizado na largura e com os pés na
linha 30.

Custos a mais: dobro de ROM por quadro, dobro de VRAM enquanto está na tela
(ver §4). Paleta e OAM não mudam (continua 1 paleta e 1 sprite de hardware).

### 3.4 Um quadro só (NPC que nunca anda nem vira)

Para personagem que só fica parado olhando para a frente (proposta para os
treinadores do Nexus): a folha tem **1 quadro** e a pic table repete o mesmo
quadro 9 vezes, para o jogo continuar achando que tem 9:

```c
static const struct SpriteFrameImage sPicTable_Guzma[] = {
    overworld_frame(gObjectEventPic_Guzma, 4, 4, 0),
    overworld_frame(gObjectEventPic_Guzma, 4, 4, 0),
    // ... 9 entradas, todas quadro 0
};
```

Cada entrada extra custa 8 bytes. Script que manda virar ou andar não quebra
nada: ele só continua na mesma pose.

O que se perde: `faceplayer` não vira; se andar, desliza parado; treinador que
avista e caminha até o jogador fica estranho — a luta deve começar por script.

> Ainda **não testado no jogo** em 26/09/2026. Primeiro uso: validar em runtime
> antes de replicar.

---

## 4. Custo de memória (medido)

### 4.1 Onde está o jogo hoje

O build imprime no final (`--print-memory-usage`):

```
Memory region         Used Size  Region Size  %age Used
           EWRAM:      247140 B       256 KB     94.28%
           IWRAM:       24152 B        32 KB     73.71%
             ROM:    31147940 B        32 MB     92.83%
```

> ⚠️ **Não confunda EWRAM com ROM.** O número alto (94%) é a **EWRAM**, a RAM
> de trabalho — sprites não mexem nela. O espaço de cartucho é a linha **ROM**:
> 92,83%, **2,30 MB livres**.

### 4.2 Quanto cada gráfico ocupa na ROM

| Gráfico | Bytes | Observação |
|---|---|---|
| Front pic 64x64 | **~670** (média de 140; máx 1.036) | comprimido (`.4bpp.smol`); +32 B de paleta |
| Overworld 16x32, 9 quadros | **2.304** | sem compressão; +32 B de paleta |
| Overworld 32x32, 9 quadros | **4.608** | |
| Overworld 16x32, 1 quadro | **256** | |
| Overworld 32x32, 1 quadro | **512** | |
| Mugshot 64x64 | **~406** (média de 52) | comprimido (`.4bpp.smol`); +32 B de paleta |

Hoje há **180 folhas de overworld 16x32** na ROM: **374.400 B**.

### 4.3 Cenários já calculados (ROM de 92,83%)

| Cenário | A mais | ROM | Livre |
|---|---|---|---|
| Migrar o jogo todo para 32x32 | +366 KB | 93,94% | 1,94 MB |
| Nexus, 60 treinadores, 16x32 com 9 quadros (+ front pic) | +178 KB | 93,37% | 2,12 MB |
| Nexus, 60 treinadores, 32x32 com 9 quadros | +313 KB | 93,78% | 1,99 MB |
| Nexus, 60 treinadores, 16x32 com 1 quadro | +58 KB | 93,01% | 2,24 MB |
| Nexus, 60 treinadores, 32x32 com 1 quadro | +73 KB | 93,05% | 2,22 MB |
| Mugshot para os 60 | +~26 KB | | |

Falas, times e scripts não entram na tabela (~1 KB por treinador, estimado).

Leitura: memória não é o que impede 32x32; **arte é**. Migrar o jogo todo são
1.480 quadros para redesenhar — alargar a folha sem redesenhar gasta ROM sem
ganho visual, e sombra, "!", reflexo e bike/surf foram calibrados para 16x32.
Um quadro só economiza mais que qualquer outra escolha.

### 4.4 VRAM (vídeo, em tempo de jogo)

Só o quadro atual de cada NPC fica na VRAM: 16x32 = 8 tiles, 32x32 = 16 tiles.
Máximo de 16 NPCs carregados → **+4 KB no pior caso** se todos fossem 32x32,
de 32 KB de área de sprites (dividida com "!", sombras, follower, clima, grama).
Mapa lotado + follower + chuva é o teste de estresse.

Paleta: cada personagem com paleta própria ocupa um slot enquanto está na tela.
Sala com vários personagens únicos ao mesmo tempo (Nexus: 3 teleportes por
sala) → conferir no jogo.

### 4.5 Como medir de novo

```bash
make -j$(nproc) 2>&1 | tee /tmp/build.log
python3 dev_scripts/sprites/sprite_gba.py rom --log /tmp/build.log
```

Imprime EWRAM/IWRAM/ROM, espaço livre e o total/média de overworlds
(`gObjectEventPic_`, inclui Pokémon), front pics (`gTrainerFrontPic_`) e
mugshots (`sFieldMugshotGfx_`). Na nuvem o compilador não vem instalado:
`apt-get install -y gcc-arm-none-eabi binutils-arm-none-eabi libnewlib-arm-none-eabi`
(primeiro build do zero: ~3 min).

---

## 5. Pedido de arte (para mandar a um artista)

> Front pic **64x64** e overworld **16x32 em 9 quadros** (ordem da §3.1), os
> dois com **até 15 cores + transparente**, fundo numa cor que não aparece no
> desenho. Boneco de 18–22 px de altura no overworld, pés na linha 30.

Chegando assim, é só registrar — sem conversão.
