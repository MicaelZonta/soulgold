---
name: adicionar-npc
description: Use ao criar um object event novo com sprite proprio (NPC humano, Pokemon de overworld, qualquer boneco novo andando no mapa) - envolve PNG em graphics/object_events/pics, OBJ_EVENT_GFX_*, pic tables, graphics info e paleta. Use tambem ao diagnosticar NPC que aparece invisivel, embaralhado ou com paleta errada. Nao use se o NPC reaproveita um sprite que ja existe: nesse caso so o map.json basta.
---

# Adicionar NPC (object event) com sprite novo

Passo a passo completo, com exemplo real (Lusamine):
**[`.claude/adicionar-npc.md`](../../adicionar-npc.md)** — abra antes de começar.
Esta skill existe para você não fechar a task com o bug silencioso abaixo.

## Precisa mesmo de sprite novo?

Se o NPC usa um gráfico existente (`OBJ_EVENT_GFX_YOUNGSTER`, `OBJ_EVENT_GFX_GLADION`…),
**pule tudo isto**: basta um `object_event` no `map.json` do mapa. Os 8 passos
do pipeline só valem para um sprite que ainda não existe.

## A armadilha: `spritesheet_rules.mk`

**Sintoma:** o NPC existe, colide, conversa — e é **totalmente invisível**.
Build limpo, zero warning.

**Causa:** object events precisam ser convertidos com metatile de 2x4 tiles
para que cada frame de 256 bytes forme um retângulo de 16x32 px. Isso só
acontece se o PNG tiver **regra própria** em `spritesheet_rules.mk`:

```make
$(OBJEVENTGFXDIR)/people/special/<nome>.4bpp: %.4bpp: %.png
	$(GFX) $< $@ -mwidth 2 -mheight 4
```

Sem essa regra ele cai na genérica do `Makefile:493` (`$(GFX) $< $@`, sem
metatile), que fatia a folha em ordem row-major. O "frame 0" vira a faixa
superior de 64x8 px — o vazio acima das cabeças. Frames 0 e 1 saem 100%
transparentes, e o NPC parado virado para baixo não desenha nada.

> É o passo que ninguém lembra. Confira que a regra existe **antes** de
> dizer que terminou.

## Os 9 lugares

| # | Arquivo |
|---|---------|
| 1 | `graphics/object_events/pics/people/<cat>/<nome>.png` — 144x32, indexado, ≤16 cores |
| 2 | **`spritesheet_rules.mk`** ← a armadilha |
| 3 | `include/constants/event_objects.h` — `OBJ_EVENT_GFX_*`, `NUM_OBJ_EVENT_GFX++`, `OBJ_EVENT_PAL_TAG_*` |
| 4 | `src/data/object_events/object_event_graphics.h` — `INCBIN` |
| 5 | `src/data/object_events/object_event_pic_tables.h` — 9 `overworld_frame` |
| 6 | `src/data/object_events/object_event_graphics_info.h` |
| 7 | `src/data/object_events/object_event_graphics_info_pointers.h` |
| 8 | `src/event_object_movement.c` — `sObjectEventSpritePalettes[]` |
| 9 | `data/maps/<Mapa>/map.json` + script |

O PNG é **indexado, no máximo 16 cores, índice 0 = transparência**. Só o
`.png` é commitado; `.4bpp`/`.gbapal` são gerados e gitignored.

## Cache do make

Reexportou o PNG e o jogo mostra o antigo? Apague os derivados ao lado:

```bash
rm -f graphics/object_events/pics/people/<cat>/<nome>.4bpp* \
      graphics/object_events/pics/people/<cat>/<nome>.gbapal
```

## Checklist

- [ ] Confirmei que o sprite realmente não existe ainda
- [ ] **Regra em `spritesheet_rules.mk` com `-mwidth 2 -mheight 4`**
- [ ] PNG indexado, ≤16 cores, índice 0 transparente, 144x32
- [ ] Os 9 lugares preenchidos (o guia tem o diff de cada um)
- [ ] Rodei no jogo e **vi o sprite parado virado para baixo** — é o frame
      que a armadilha apaga, e o único que prova que deu certo
