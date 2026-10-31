# Bea

**Região da ficha:** Galar

Aparece no checklist como:

- **Bea — Lutador** (Galar · Líderes de Ginásio) — Líder exclusiva de *Sword*, séria e dedicada às artes marciais.

**Pronto para o Nexus:** ✅ sim — no pool desde 31/10/2026 (lote novo, bloco 2 de IDs).

## Checklist

- [x] Sprite de overworld *(obrigatório)* — `OBJ_EVENT_GFX_BEA`, 03/10/2026
- [x] Battle sprite / front pic *(obrigatório)* — `TRAINER_PIC_FRONT_BEA` (64x64 + 80x80), 03/10/2026
- [ ] Field mugshot (retrato na caixa de diálogo)
- [x] Time para as Rift Missions definido
- [x] Associado a um lendário
- [x] Diálogo genérico escrito
- [x] Diálogo associado ao lendário escrito

## Referências no repositório

### Sprite de overworld

| Constante | Arquivo |
|---|---|
| `OBJ_EVENT_GFX_BEA` | `graphics/object_events/pics/people/special/bea.png` (boneco 21x24, quadro 32x32, 12 quadros, `sAnimTable_StandardAsym`; paleta própria `OBJ_EVENT_PAL_TAG_BEA`) — registrado em 03/10/2026, visto no jogo de frente |

Origem: `.filetransfer/.trainers/Bea/Sprite - DiegoWT.png` (tamanho escolhido pelo autor; ver `TAMANHOS.md`).

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_BEA` | `graphics/trainers/front_pics/bea.png` (64x64) + `bea_large.png` (80x80, `TRAINER_SPRITE_LARGE`) — 03/10/2026; nenhuma batalha usa ainda |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

Nenhuma. Ao criar, seguir a skill `adicionar-batalha-npc` (e `alocar-flag` se precisar de flag nova).

### Time das Rift Missions

✅ **Implementado em 31/10/2026** (lote novo, time montado pelo Codex e conferido pelo `novos/integrar.py`: R10–R13 e habilidades): `TRAINER_NEXUS_BEA` = **1170** (bloco 2, flag `0xB06`), luta genérica `Nexus_EventScript_Bea_Fight` em `data/scripts/nexus.inc`, linha em `src/data/nexus/trainers.h`. Ainda não é campeão de nenhum lendário.

```
=== TRAINER_NEXUS_BEA ===
Name: Bea
Class: Leader
Pic: Bea
Gender: Female
Music: Female
Double Battle: No
AI: Smart Trainer

Marshadow @ Life Orb
Jolly Nature
Level: 100
Ability: Technician
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Spectral Thief
- Close Combat
- Shadow Sneak
- Bulk Up

Urshifu-Rapid-Strike @ Life Orb
Adamant Nature
Level: 100
Ability: Unseen Fist
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Surging Strikes
- Close Combat
- Aqua Jet
- U-turn

Hawlucha @ Fightite
Jolly Nature
Level: 100
Ability: Unburden
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Close Combat
- Brave Bird
- Swords Dance
- Detect

Hitmontop @ Rocky Helmet
Impish Nature
Level: 100
Ability: Intimidate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Fake Out
- Close Combat
- Rapid Spin
- Wide Guard

Sirfetchd @ Leek
Adamant Nature
Level: 100
Ability: Scrappy
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Close Combat
- Leaf Blade
- Knock Off
- Quick Guard

Falinks @ Sitrus Berry
Jolly Nature
Level: 100
Ability: Defiant
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Close Combat
- Throat Chop
- No Retreat
- Protect
```

### Lendário associado

✅ **Campeão extra desde 31/10/2026** (lendário com vários campeões; o do dia é sorteado, `src/data/nexus/champions.h`; associações e falas montadas pelo Codex):

- **Marshadow** — `Nexus_EventScript_Bea_Marshadow_ChampionFight` (falas `Nexus_Text_Bea_Marshadow_Champion*`)
- **Urshifu Single Strike** — `Nexus_EventScript_Bea_Urshifu_ChampionFight` (falas `Nexus_Text_Bea_Urshifu_Champion*`)
- **Zapdos Galar** — `Nexus_EventScript_Bea_GalarianZapdos_ChampionFight` (falas `Nexus_Text_Bea_GalarianZapdos_Champion*`)


### Diálogo genérico

✅ **Implementado em 31/10/2026:** `Nexus_Text_Bea_Intro` / `_Defeat` em `data/scripts/nexus.inc`.

**Antes da luta**

> Training teaches you to stand when your legs say you cannot.
>
> My partners and I have practiced. Let us see what we have learned.

**Derrota**

> A clean victory. I must train harder. Thank you.

### Diálogo associado ao lendário

_Não escrito._ (texto do jogo em inglês)
