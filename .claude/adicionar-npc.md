# Como adicionar um NPC novo (object event) no SoulGold

Guia derivado da implementação da Lusamine em `NewBarkTown_PlayersHouse_2F`.
Usa como exemplo um NPC humano padrão de **16x32 px, 9 frames** (folha de 144x32).

> ⚠️ **Leia a seção [A armadilha](#a-armadilha-spritesheet_rulesmk) antes de fechar a task.**
> É o passo que ninguém lembra e que faz o NPC aparecer **invisível** sem nenhum erro de build.

---

## Checklist rápido

| # | Arquivo | O que fazer |
|---|---------|-------------|
| 1 | `graphics/object_events/pics/people/<cat>/<nome>.png` | A folha de sprites (144x32, indexada) |
| 2 | **`spritesheet_rules.mk`** | **Regra `-mwidth 2 -mheight 4`** ← a armadilha |
| 3 | `include/constants/event_objects.h` | `OBJ_EVENT_GFX_<NOME>` + `NUM_OBJ_EVENT_GFX++` + `OBJ_EVENT_PAL_TAG_<NOME>` |
| 4 | `src/data/object_events/object_event_graphics.h` | `INCBIN` do `.4bpp` e do `.gbapal` |
| 5 | `src/data/object_events/object_event_pic_tables.h` | `sPicTable_<Nome>[]` com 9 `overworld_frame` |
| 6 | `src/data/object_events/object_event_graphics_info.h` | `gObjectEventGraphicsInfo_<Nome>` |
| 7 | `src/data/object_events/object_event_graphics_info_pointers.h` | `extern` + entrada no array indexado |
| 8 | `src/event_object_movement.c` | Entrada em `sObjectEventSpritePalettes[]` |
| 9 | `data/maps/<Mapa>/map.json` + `scripts.inc` | Colocar o NPC no mapa e dar um script |

---

## Passo a passo

### 1. A imagem

Salve em `graphics/object_events/pics/people/special/<nome>.png` (ou `.../people/`,
`.../pokemon/`, conforme a categoria).

- **144 x 32 px** — 9 frames de 16x32 lado a lado, na horizontal.
- PNG **indexado (colormap) de no máximo 16 cores**. A **cor de índice 0 é a transparência**.
- Ordem dos frames (para `sAnimTable_Standard`):

| Frame | Uso |
|-------|-----|
| 0 | parado, virado para **baixo** (sul) |
| 1 | parado, virado para **cima** (norte) |
| 2 | parado, virado para a **esquerda** (leste usa o mesmo com `hFlip`) |
| 3, 4 | andando para baixo |
| 5, 6 | andando para cima |
| 7, 8 | andando para a esquerda (direita = flip) |

Como o frame 0 é o estado parado padrão, **um erro de layout aparece primeiro como "NPC invisível"**.

### 2. `spritesheet_rules.mk` ← NÃO PULE

Adicione junto dos vizinhos da mesma pasta (procure por `people/special`):

```make
$(OBJEVENTGFXDIR)/people/special/<nome>.4bpp: %.4bpp: %.png
	$(GFX) $< $@ -mwidth 2 -mheight 4
```

O `.gbapal` **não** precisa de regra — a regra genérica do `Makefile` já serve.

Para sprites maiores use o metatile correspondente (`-mwidth 4 -mheight 4` para 32x32, etc.).

### 3. `include/constants/event_objects.h`

```c
#define OBJ_EVENT_GFX_LUSAMINE                  330
// ...
#define NUM_OBJ_EVENT_GFX                        331   // <- incrementar!
```

E uma paleta nova no fim da lista de tags (antes do bloco `#if OW_FOLLOWERS_POKEBALLS`,
que começa em `0x1150` — não invada esse range):

```c
#define OBJ_EVENT_PAL_TAG_LUSAMINE                0x114C
```

Se o NPC puder reusar uma paleta existente (`OBJ_EVENT_PAL_TAG_NPC_1`…`NPC_5`, etc.),
pule a tag nova e os passos 4-pal e 8.

### 4. `src/data/object_events/object_event_graphics.h`

```c
const u32 gObjectEventPic_Lusamine[] = INCBIN_U32("graphics/object_events/pics/people/special/lusamine.4bpp");
// ... mais abaixo, na seção de paletas:
const u16 gObjectEventPal_Lusamine[] = INCBIN_U16("graphics/object_events/pics/people/special/lusamine.gbapal");
```

### 5. `src/data/object_events/object_event_pic_tables.h`

```c
static const struct SpriteFrameImage sPicTable_Lusamine[] = {
    overworld_frame(gObjectEventPic_Lusamine, 2, 4, 0),
    // ... 1 a 8
    overworld_frame(gObjectEventPic_Lusamine, 2, 4, 8),
};
```

Os `2, 4` são largura/altura **em tiles** (2*8 x 4*8 = 16x32) — têm que bater com o
`-mwidth`/`-mheight` do passo 2.

### 6. `src/data/object_events/object_event_graphics_info.h`

```c
const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Lusamine = {
    TAG_NONE, OBJ_EVENT_PAL_TAG_LUSAMINE, OBJ_EVENT_PAL_TAG_NONE,
    256, 16, 32, 4, SHADOW_SIZE_M, FALSE, FALSE, TRACKS_FOOT,
    &gObjectEventBaseOam_16x32, sOamTables_16x32, sAnimTable_Standard,
    sPicTable_Lusamine, gDummySpriteAffineAnimTable};
```

Campos, na ordem (`struct ObjectEventGraphicsInfo`, `include/global.fieldmap.h:264`):

`tileTag`, `paletteTag`, `reflectionPaletteTag`, `size`, `width`, `height`,
`paletteSlot`, `shadowSize`, `inanimate`, `compressed`, `tracks`,
`oam`, `subspriteTables`, `anims`, `images`, `affineAnims`.

- `size` = bytes de **um** frame: `16*32/2 = 256` para 16x32 4bpp.
- `paletteSlot` = 4 (`PALSLOT_NPC_4`) é o padrão para NPC comum.

### 7. `src/data/object_events/object_event_graphics_info_pointers.h`

Duas edições — o `extern` no topo e a entrada no array:

```c
extern const struct ObjectEventGraphicsInfo gObjectEventGraphicsInfo_Lusamine;
// ...
[OBJ_EVENT_GFX_LUSAMINE] = &gObjectEventGraphicsInfo_Lusamine,
```

### 8. `src/event_object_movement.c` — `sObjectEventSpritePalettes[]`

```c
{gObjectEventPal_Lusamine, OBJ_EVENT_PAL_TAG_LUSAMINE},
```

Tem que ficar **antes** do terminador do array. Se esquecer, o sprite aparece com a
paleta errada (cores trocadas), não invisível.

### 9. O mapa

`data/maps/<Mapa>/map.json`:

```json
{
  "graphics_id": "OBJ_EVENT_GFX_LUSAMINE",
  "x": 5, "y": 5,
  "elevation": 0,
  "movement_type": "MOVEMENT_TYPE_FACE_DOWN",
  "movement_range_x": 0, "movement_range_y": 0,
  "trainer_type": "TRAINER_TYPE_NONE",
  "trainer_sight_or_berry_tree_id": "0",
  "script": "NewBarkTown_PlayersHouse_2F_EventScript_Lusamine",
  "flag": "0"
}
```

`flag: "0"` = sempre visível. Uma flag real esconde o NPC quando ela está setada.

`data/maps/<Mapa>/scripts.inc`:

```
NewBarkTown_PlayersHouse_2F_EventScript_Lusamine::
	lock
	faceplayer
	msgbox NewBarkTown_PlayersHouse_2F_Text_Lusamine, MSGBOX_DEFAULT
	release
	end
```

---

## A armadilha: `spritesheet_rules.mk`

**Sintoma:** o NPC existe, dá para conversar com ele, colide — mas o
sprite é **totalmente invisível**. O build passa sem nenhum warning.

**Causa:** os `.4bpp` de object events precisam ser convertidos com metatiles de 2x4 tiles,
para que os 256 bytes de cada frame contenham um retângulo de 16x32 px. Isso só acontece
por causa das regras explícitas em `spritesheet_rules.mk`:

```make
$(OBJEVENTGFXDIR)/people/special/bill.4bpp: %.4bpp: %.png
	$(GFX) $< $@ -mwidth 2 -mheight 4
```

Se o PNG novo **não tem** regra própria, ele cai na regra genérica do `Makefile:493`:

```make
%.4bpp:     %.png  ; $(GFX) $< $@
```

que converte sem metatile, ou seja, em ordem row-major de tiles 8x8 sobre a folha
inteira de 144x32. O "frame 0" passa a ser a **faixa superior de 64x8 px da folha**, que
é o espaço vazio acima das cabeças. Resultado: frames 0 e 1 100% transparentes → o NPC
parado virado para baixo não desenha nada.

Foi exatamente isso que aconteceu com a Lusamine.

## Diagnóstico

Antes de suspeitar do C, **cheque o binário**. Um frame correto tem os 2 primeiros tiles
vazios (espaço acima da cabeça) e os outros 6 com conteúdo:

```bash
python3 -c "
d=open('graphics/object_events/pics/people/special/lusamine.4bpp','rb').read()
for f in range(len(d)//256):
    blk=d[f*256:(f+1)*256]
    print('frame%d tiles=%s'%(f,[sum(1 for b in blk[t*32:(t+1)*32] for n in (b&15,b>>4) if n) for t in range(8)]))
"
```

```
ERRADO (sem a regra)          CERTO (com -mwidth 2 -mheight 4)
frame0 tiles=[0,0,0,0,0,0,0,0]   frame0 tiles=[0,0,22,22,54,54,36,36]
frame1 tiles=[0,0,0,0,0,0,0,0]   frame1 tiles=[0,0,22,22,53,53,33,32]
frame2 tiles=[0,0,22,22,22,22,22,22]  ...
```

O padrão "escorregando" (blocos de 22 iguais migrando entre frames) é a assinatura do
row-major errado.

Confirmação definitiva — compare as duas conversões:

```bash
tools/gbagfx/gbagfx <png> /tmp/a.4bpp                        # genérica
tools/gbagfx/gbagfx <png> /tmp/b.4bpp -mwidth 2 -mheight 4   # correta
cmp -s /tmp/a.4bpp graphics/.../<nome>.4bpp && echo "caiu na regra genérica = BUG"
```

## Cuidado com o cache do make

`.4bpp` e `.gbapal` são **gitignored** e ficam ao lado do PNG. O `make` só reconverte se o
PNG for mais novo que o `.4bpp`. Depois de corrigir uma regra em `spritesheet_rules.mk`
(ou de reexportar o PNG), **apague o `.4bpp` na mão**:

```bash
rm -f graphics/object_events/pics/people/special/<nome>.4bpp
make graphics/object_events/pics/people/special/<nome>.4bpp
```

Build normal do projeto: `make release USE_LTO_ON_RELEASE=1 -j32`.

## Outras causas de NPC invisível / errado

| Sintoma | Causa provável |
|---------|----------------|
| Invisível, mas interagível | Regra faltando em `spritesheet_rules.mk` (frames 0/1 vazios) |
| Sprite embaralhado / picotado | `-mwidth`/`-mheight` não batem com `overworld_frame(..., w, h, i)` |
| Cores erradas | Falta a entrada em `sObjectEventSpritePalettes[]`, ou tag de paleta duplicada |
| Só metade do sprite | `size`, `width` ou `height` errados no `GraphicsInfo` |
| NPC não aparece de jeito nenhum | `flag` do `map.json` está setada, ou `NUM_OBJ_EVENT_GFX` não foi incrementado |
| Sprite de outro NPC | Entrada no array de `_pointers.h` com índice errado |
