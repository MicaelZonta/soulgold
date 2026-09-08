# Como adicionar gráficos novos de treinador no SoulGold

São **quatro** gráficos diferentes, em lugares diferentes, e é fácil confundir:

| Gráfico | Onde aparece | Pasta | Guia |
|---------|--------------|-------|------|
| **Front pic** | sprite do treinador **na batalha** | `graphics/trainers/front_pics/` | este, [§1](#1-front-pic-o-sprite-de-batalha) |
| **Back pic** | costas do jogador/parceiro na batalha | `graphics/trainers/back_pics/` | este, [§2](#2-back-pic) |
| **Field mugshot** | retrato na caixa de texto do overworld | `graphics/field_mugshots/` | este, [§3](#3-field-mugshot-retrato-do-overworld) |
| **Overworld sprite** | o boneco andando no mapa | `graphics/object_events/pics/` | [`adicionar-npc.md`](adicionar-npc.md) |

Para ligar o treinador ao gráfico, ver [`adicionar-batalha-npc.md`](adicionar-batalha-npc.md).

Referência upstream (em inglês, sem as particularidades do SoulGold):
[`docs/tutorials/how_to_trainer_front_pic.md`](../docs/tutorials/how_to_trainer_front_pic.md) e
[`how_to_trainer_back_pic.md`](../docs/tutorials/how_to_trainer_back_pic.md).

---

## Regras que valem para os três

- **64 x 64 px**, PNG **indexado**, **no máximo 16 cores contando a transparência**
  (índice 0 da paleta = transparente). Front pic de 5 frames não existe; só back pic.
- `.4bpp`, `.4bpp.smol` e `.gbapal` são **gerados e gitignored** — você commita só o `.png`.
  As regras genéricas do [`Makefile:493`](../Makefile#L493) e [`:500`](../Makefile#L500)
  fazem a conversão; **front pics e mugshots não precisam de regra em
  `spritesheet_rules.mk`** (isso é só para object events, que usam metatile).
- Se você reexportar o PNG e o jogo continuar mostrando o antigo, é **cache do make**:
  ```bash
  rm -f graphics/trainers/front_pics/<nome>.4bpp*  graphics/trainers/front_pics/<nome>.gbapal
  ```

---

## 1. Front pic (o sprite de batalha)

### Checklist

| # | Arquivo | O que fazer |
|---|---------|-------------|
| 1 | `graphics/trainers/front_pics/<nome>.png` | 64x64, ≤16 cores |
| 2 | `include/constants/trainers.h` | `TRAINER_PIC_FRONT_<NOME>` **antes** de `TRAINER_PIC_FRONT_COUNT` |
| 3 | `src/data/graphics/trainers.h` | os dois `INCBIN` (pic **`.4bpp.smol`** + paleta) |
| 4 | `src/data/graphics/trainers.h` | linha `TRAINER_SPRITE(...)` em `gTrainerSprites[]` |
| 5 | `src/data/trainers.party` | `Pic: <Nome Com Espaços>` no treinador |

### A constante

[`include/constants/trainers.h:18`](../include/constants/trainers.h#L18), no fim da lista
de front pics:

```diff
     TRAINER_PIC_FRONT_GAMBLER,
+    TRAINER_PIC_FRONT_KUKUI,
     TRAINER_PIC_FRONT_COUNT,
     TRAINER_PIC_BACK_BRENDAN = TRAINER_PIC_FRONT_COUNT,
```

**Front pic novo entra antes de `TRAINER_PIC_FRONT_COUNT`; back pic novo entra antes de
`TRAINER_PIC_COUNT`.** Nunca depois.

> O enum é `__attribute__((packed))` → cabe em **u8**. Hoje há ~148 pics (140 front + 8
> back) dos 256 possíveis. Não é urgente, mas é um teto real.

### Registrar os INCBIN

[`src/data/graphics/trainers.h`](../src/data/graphics/trainers.h), junto dos vizinhos:

```c
const u32 gTrainerFrontPic_Kukui[] = INCBIN_U32("graphics/trainers/front_pics/kukui.4bpp.smol");
const u16 gTrainerPalette_Kukui[]  = INCBIN_U16("graphics/trainers/front_pics/kukui.gbapal");
```

> ⚠️ Front pic é **`u32` + `.4bpp.smol`** (comprimido). Back pic é **`u8` + `.4bpp`** (cru).
> Trocar os dois dá lixo na tela ou crash, não erro de compilação.
> A paleta sai da mesma pasta do PNG (`front_pics/`); a pasta `graphics/trainers/palettes/`
> só serve para as 8 paletas do jogador/rival, que têm `.pal` escrito à mão.

### A entrada em `gTrainerSprites[]`

Mesmo arquivo, array na linha ~404:

```c
TRAINER_SPRITE(TRAINER_PIC_FRONT_KUKUI, gTrainerFrontPic_Kukui, gTrainerPalette_Kukui),
```

O macro usa o próprio `TRAINER_PIC_*` como **tag de sheet e de paleta** — não existe tag
separada para inventar. A ordem no array não importa (é inicialização por índice).

**Mugshot da transição de batalha:** os 3 parâmetros opcionais são `x`, `y` e `rotation`
do retrato que entra na tela:

```c
TRAINER_SPRITE(TRAINER_PIC_FRONT_STEVEN, gTrainerFrontPic_Steven, gTrainerPalette_Steven, 0, 7, 0x188),
```

Padrões: `0, 0, 0x200`. Só ajuste se o treinador usar `Mugshot:` no `.party` — é esse
campo que liga a transição (`Mugshot: Blue` → `MUGSHOT_COLOR_BLUE`,
[`include/battle_transition.h:15`](../include/battle_transition.h#L15)).

### Usar no treinador

Em [`src/data/trainers.party`](../src/data/trainers.party), o `Pic:` é **o nome da
constante sem o prefixo `TRAINER_PIC_FRONT_`, com espaços no lugar dos `_`**:

```diff
 === TRAINER_KUKUI ===
 Name: Kukui
 Class: Expert
-Pic: Expert M
+Pic: Kukui
```

Se o nome não bater com nenhuma constante, o erro vem do **compilador C** (`use of
undeclared identifier 'TRAINER_PIC_FRONT_KUKUI'`) e não do trainerproc — ele monta o
identificador às cegas ([`tools/trainerproc/main.c:1859`](../tools/trainerproc/main.c#L1859)).

---

## 2. Back pic

Só é necessário para o **jogador** ou para um **parceiro de batalha dupla**. Mesmo caminho,
com três diferenças:

1. PNG é **64 x 256** (4 frames) ou **64 x 320** (5 frames) — uma coluna vertical.
2. INCBIN é **`INCBIN_U8` do `.4bpp` cru**, sem `.smol`.
3. A entrada vai em `gTrainerBacksprites[]` (linha ~610) com o macro
   `TRAINER_BACK_SPRITE(pic, yOffset, sprite, pal, anim)`:

```c
TRAINER_BACK_SPRITE(TRAINER_PIC_BACK_RED, 5, gTrainerBackPic_Red, gTrainerBackPicPalette_Red, sBackAnims_Kanto),
```

**4 frames → `yOffset = 4` e `sBackAnims_Hoenn`; 5 frames → `yOffset = 5` e
`sBackAnims_Kanto`.** Misturar os dois faz a animação de arremesso travar ou piscar.

---

## 3. Field mugshot (retrato do overworld)

Sistema próprio do SoulGold, sem doc upstream. É o retrato que aparece na caixa de texto
via `createfieldmugshot(MUGSHOT_X)` ou automaticamente ao falar com certos NPCs.

### Checklist

| # | Arquivo | O que fazer |
|---|---------|-------------|
| 1 | `graphics/field_mugshots/<nome>.png` | 64x64, ≤16 cores |
| 2 | `include/constants/field_mugshots.h` | `MUGSHOT_<NOME>` antes de `MUGSHOT_COUNT` |
| 3 | `src/data/field_mugshots.h` | os dois INCBIN (`.4bpp.smol` + `.gbapal`) |
| 4 | `src/data/field_mugshots.h` | entrada em `sFieldMugshots[][]` |
| 5 | `src/field_mugshot.c` *(opcional)* | `case OBJ_EVENT_GFX_<X>:` em `GetFieldMugshotIdByObjectGraphicsId` |

```c
// src/data/field_mugshots.h
static const u32 sFieldMugshotGfx_KukuiNormal[] = INCBIN_U32("graphics/field_mugshots/kukui.4bpp.smol");
static const u16 sFieldMugshotPal_KukuiNormal[] = INCBIN_U16("graphics/field_mugshots/kukui.gbapal");

// ... no array sFieldMugshots[MUGSHOT_COUNT][EMOTE_COUNT]:
    [MUGSHOT_KUKUI] =
    {
        [EMOTE_NORMAL] =
        {
            .gfx = sFieldMugshotGfx_KukuiNormal,
            .pal = sFieldMugshotPal_KukuiNormal,
        },
    },
```

O passo 5 é o que faz o retrato aparecer **sozinho** quando o jogador fala com um NPC
daquele `graphics_id` (modo `FIELD_MUGSHOT_AUTO`). Sem ele, o retrato só aparece com
`createfieldmugshot()` explícito no script.

> `EMOTE_ALT` existe no enum mas **nenhum mugshot do jogo tem variante alt** hoje. Se você
> chamar um emote não definido, `IsFieldMugshotDefined()` retorna FALSE e nada é desenhado —
> falha silenciosa.

---

## Build e verificação

```bash
make release USE_LTO_ON_RELEASE=1 -j32
```

Para converter só o gráfico e conferir que o PNG passou no gbagfx:

```bash
make graphics/trainers/front_pics/kukui.4bpp.smol
ls -l graphics/trainers/front_pics/kukui.4bpp        # 2048 bytes = 64x64 4bpp
```

`2048` é o valor esperado (`TRAINER_PIC_SIZE = 64*64/2`). Qualquer outro número quer dizer
que o PNG não tem 64x64.

---

## Armadilhas

| Sintoma | Causa provável |
|---------|----------------|
| `gbagfx: too many colors` | PNG com mais de 16 cores (a transparência conta) |
| Sprite embaralhado / colorido errado na batalha | Front pic incluído como `.4bpp` cru em vez de `.4bpp.smol` (ou `INCBIN_U8` no lugar de `U32`) |
| Crash ao começar a batalha | Faltou a entrada em `gTrainerSprites[]` — o índice do array fica NULL |
| `use of undeclared identifier 'TRAINER_PIC_FRONT_X'` | `Pic:` do `.party` não bate com a constante (espaços viram `_`, tudo maiúsculo) |
| Back pics viraram outro treinador | Front pic novo inserido **depois** de `TRAINER_PIC_FRONT_COUNT` |
| Animação de arremesso quebrada | `yOffset`/`anim` do back pic não batem com o número de frames (4=Hoenn, 5=Kanto) |
| PNG novo não aparece no jogo | Cache do make: apague os `.4bpp*`/`.gbapal` gerados ao lado do PNG |
| Mugshot não aparece no diálogo | Faltou o `case` em `GetFieldMugshotIdByObjectGraphicsId`, ou o script não chama `createfieldmugshot` |
| Mugshot da transição no lugar errado | Ajuste os 3 parâmetros extras do `TRAINER_SPRITE` (x, y, rotação) |
