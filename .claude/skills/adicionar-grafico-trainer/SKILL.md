---
name: adicionar-grafico-trainer
description: Use ao adicionar ou corrigir grafico de treinador - front pic (sprite na batalha), back pic (costas do jogador) ou field mugshot (retrato na caixa de texto do overworld). Use tambem ao diagnosticar sprite embaralhado na batalha, crash ao iniciar batalha, mugshot que nao aparece, ou erro de gbagfx "too many colors".
---

# Gráficos de treinador

Passo a passo completo dos três:
**[`.claude/adicionar-grafico-trainer.md`](../../adicionar-grafico-trainer.md)**.

## São quatro gráficos diferentes — confira qual você quer

| Gráfico | Onde aparece | Pasta |
|---|---|---|
| **Front pic** | treinador **na batalha** | `graphics/trainers/front_pics/` |
| **Back pic** | costas do jogador na batalha | `graphics/trainers/back_pics/` |
| **Field mugshot** | retrato na caixa de texto do overworld | `graphics/field_mugshots/` |
| **Overworld sprite** | o boneco andando no mapa | skill `adicionar-npc` |

Confundir front pic com overworld sprite é o erro de partida mais comum.
Para ligar o treinador ao gráfico, ver skill `adicionar-batalha-npc`.

## Regras dos três

- **64x64 px**, PNG **indexado**, **≤16 cores contando a transparência**
  (índice 0 = transparente).
- `.4bpp`, `.4bpp.smol` e `.gbapal` são **gerados e gitignored** — commite só o `.png`.
- **Front pic e mugshot não precisam de regra em `spritesheet_rules.mk`.**
  Aquilo é só para object events (que usam metatile). Não confunda com a
  armadilha da skill `adicionar-npc`.

> ⚠️ Front pic é **`u32` + `.4bpp.smol`** (comprimido).
> Back pic é **`u8` + `.4bpp`** (cru). Trocar os dois embaralha o sprite.

## Armadilhas

| Sintoma | Causa |
|---|---|
| `gbagfx: too many colors` | PNG com mais de 16 cores (a transparência conta) |
| Sprite embaralhado na batalha | Front pic como `.4bpp` cru, ou `INCBIN_U8` no lugar de `U32` |
| **Crash ao começar a batalha** | Faltou a entrada em `gTrainerSprites[]` — índice NULL |
| `undeclared identifier 'TRAINER_PIC_FRONT_X'` | `Pic:` do `.party` não bate com a constante (espaços viram `_`, maiúsculo) |
| Back pics viraram outro treinador | Front pic novo inserido **depois** de `TRAINER_PIC_FRONT_COUNT` |
| Animação de arremesso quebrada | `yOffset`/`anim` do back pic não batem com os frames (4=Hoenn, 5=Kanto) |
| PNG novo não aparece | Cache do make — apague os `.4bpp*`/`.gbapal` ao lado do PNG |
| Mugshot não aparece no diálogo | Falta `case` em `GetFieldMugshotIdByObjectGraphicsId`, ou o script não chama `createfieldmugshot` |
| Mugshot da transição fora de lugar | Ajuste os 3 parâmetros extras do `TRAINER_SPRITE` (x, y, rotação) |

## Checklist

- [ ] É mesmo o gráfico certo dos quatro
- [ ] PNG 64x64 indexado, ≤16 cores, índice 0 transparente
- [ ] Front pic: `u32` + `.4bpp.smol`; back pic: `u8` + `.4bpp`
- [ ] Entrada em `gTrainerSprites[]` (senão é crash, não sprite errado)
- [ ] Front pic novo inserido **antes** de `TRAINER_PIC_FRONT_COUNT`
- [ ] Mugshot: `case` registrado **e** `createfieldmugshot` no script
- [ ] Vi o sprite **no jogo**, na batalha/diálogo real
