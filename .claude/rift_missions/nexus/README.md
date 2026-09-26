# Nexus — fichas dos treinadores das Rift Missions

> **Regras do Nexus:** [`NEXUS_REGRAS.md`](NEXUS_REGRAS.md) — formato Traditional
> (6 / 1 lendário / 1 semi-lendário / 1 Mega), 31 IV e 252 EV, level scaling no maior nível, Daily,
> pool de lendários. Todo time e toda decisão de sorteio seguem aquele arquivo.

Uma ficha por treinador candidato ao pool do loop pós-Necrozma (design
[`SOULGOLD_RIFT_MISSIONS_DESIGN.md`](../SOULGOLD_RIFT_MISSIONS_DESIGN.md) §10:
cinco treinadores por expedição, o quinto ligado ao lendário da vez). O índice
é o [checklist](../../Checklist_Treinadores_UltraDimension.md): cada nome
de lá aponta para a ficha daqui. O lado dos lendários — quais existem no
jogo e quais já têm método de obtenção — está em
[`POOL_LENDARIOS.md`](POOL_LENDARIOS.md).

**Campeões das Ultra Beasts:** [`ULTRA_BEASTS.md`](ULTRA_BEASTS.md) — o quinto
treinador de cada uma das 11 UBs (conceito do fragmento, time R10–R13, falas).
Proposta de 26/09/2026, aguardando o autor.

## Estrutura

```
nexus/<região>/<treinador>.md
```

Regiões: `kanto`, `johto`, `hoenn`, `sinnoh`, `unova`, `kalos`, `alola`,
`galar`, `hisui`, `paldea` (Kitakami e Blueberry entram em `paldea`).
Quem aparece em várias seções do checklist (Koga, Lance, Anabel, Looker, Ingo…)
tem **uma** ficha só, na região da primeira aparição. A ficha lista todas.

## O que cada ficha marca

| Item | Obrigatório | Como foi conferido |
|---|---|---|
| Sprite de overworld | **sim** | `OBJ_EVENT_GFX_*` resolvido até o PNG (pointers → graphics info → pic table → `INCBIN`) |
| Battle sprite (front pic) | **sim** | `TRAINER_PIC_FRONT_*` com entrada em `gTrainerSprites[]` (`src/data/graphics/trainers.h`) |
| Field mugshot | não | `case` do sprite em `GetFieldMugshotIdByObjectGraphicsId` (`src/field_mugshot.c`) |
| Time das Rift Missions | — | nenhum existe ainda; a ficha aponta o time mais forte já escrito como ponto de partida |
| Lendário associado | — | só o que o design aprovou |
| Diálogo genérico / do lendário | — | nenhum escrito ainda (texto do jogo em inglês) |

**Pronto para o Nexus** = sprite de overworld **e** battle sprite. No
checklist isso é o `[x]` do treinador.

Cada ficha também traz as batalhas que **já existem** para o personagem:
constante, ID, **flag de batalha** (`0x500 + ID`), time resumido e em que
mapa/arquivo a constante é usada — mais os IDs aposentados na limpeza e os
homônimos genéricos que não são o personagem.

## Estado em 25/09/2026

**60 de 260 prontas.** Todas de Kanto, Johto, Hoenn e o elenco de Alola do
hack; de Sinnoh em diante não há arte nenhuma.

| Região | Prontas | Quais |
|---|---|---|
| Kanto | 18/22 | Red, Blue, Brock, Misty, Lt. Surge, Erika, Koga, Sabrina, Blaine, Giovanni, Janine, Leaf, Bruno, Lance, Archer, Ariana, Proton, Petrel |
| Johto | 12/12 | Silver, Falkner, Bugsy, Whitney, Morty, Chuck, Jasmine, Pryce, Clair, Will, Karen, Eusine |
| Hoenn | 26/31 | Brendan, May, Wally, os 8 líderes + Juan, Tate e Liza, a Elite Four, Steven, Wallace, os 7 Frontier Brains, Maxie, Archie |
| Alola | 4/27 | Gladion, Lusamine, Kukui, Lillie |

Lendário associado: só **Misty → Kyogre** e **Giovanni → Mewtwo ou Genesect**
(os dois exemplos do design). Time das Rift Missions e diálogos: nenhum ainda.

## Armadilhas encontradas ao levantar

- **Brendan e May não são o que parecem.** `OBJ_EVENT_GFX_BRENDAN_*`,
  `OBJ_EVENT_GFX_MAY_*`, `TRAINER_PIC_FRONT_BRENDAN` e `TRAINER_PIC_FRONT_MAY`
  foram trocados pela arte de **Gold** e **Kris**. Os de Hoenn de verdade são
  os de *Ruby/Sapphire*: `OBJ_EVENT_GFX_LINK_RS_*` e `TRAINER_PIC_FRONT_RS_*`.
- **Hoenn tem arte mas não tem time.** Dos 26 prontos de Hoenn, só o **Steven**
  tem time em `trainers.party`. Os outros têm, no máximo, IDs reservados em
  `opponents.h` (`TRAINER_ROXANNE_2..5`, `TRAINER_WALLACE2`…) **sem bloco no
  `.party`**. A tabela "Treinadores preservados para o loop" do design §10
  descreve uma intenção; os times ainda precisam ser escritos.
- **Homônimos genéricos.** `TRAINER_SIDNEY` é um Hiker, `TRAINER_BRANDON` um
  Pokéfan, `TRAINER_NOLAND` um Hiker, `TRAINER_TUCKER` um Swimmer,
  `TRAINER_ROXANNE` uma Expert, `TRAINER_NORMAN` um Psychic. O nome da constante
  não prova nada; a ficha só conta a batalha se a `Pic:` for a do personagem.
- **Cynthia tem PNG solto.** `graphics/trainers/front_pics/cynthia_front_pic.png`
  existe, mas não há `TRAINER_PIC_FRONT_CYNTHIA` — não está no jogo.
- **Quase lá:** Looker (tem overworld, falta front pic); Tabitha, Matt e Shelly
  (têm front pic de admin, falta overworld próprio).
- **Flags de batalha.** Os IDs 1056–1163 têm a faixa de flag reaproveitada por
  `RECLAIMED_TRAINER_FLAGS`; nenhum treinador das fichas cai nela, mas um
  treinador novo do Nexus não pode usar esses IDs.
- **VS:** na tabela de batalhas é a cor do `Mugshot:` do `.party` — o slide da
  transição de batalha, **não** o field mugshot.

## Mantendo as fichas

As fichas foram geradas a partir do código e a partir de agora são editadas à
mão. Ao definir time, lendário ou diálogo:

1. Preencha a seção da ficha e marque o item no checklist dela.
2. Atualize a linha de status do treinador no checklist principal.
3. Batalha nova → skill `adicionar-batalha-npc`; flag nova → `alocar-flag`
   e `catalogar-flags`; arte nova → `adicionar-npc` / `adicionar-grafico-trainer`.
4. Diálogo que vai para o jogo é em **inglês**.
