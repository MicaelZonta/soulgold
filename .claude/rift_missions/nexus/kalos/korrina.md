# Korrina

**Região da ficha:** Kalos

Aparece no checklist como:

- **Korrina — Lutador** (Kalos · Líderes de Ginásio) — herdeira dos segredos da Mega Evolução.

**Pronto para o Nexus:** ✅ sim — no pool desde 31/10/2026 (lote novo, bloco 2 de IDs).

## Checklist

- [x] Sprite de overworld *(obrigatório)*
- [x] Battle sprite / front pic *(obrigatório)*
- [ ] Field mugshot (retrato na caixa de diálogo)
- [x] Time para as Rift Missions definido
- [x] Associado a um lendário
- [x] Diálogo genérico escrito
- [x] Diálogo associado ao lendário escrito

## Referências no repositório

### Sprite de overworld

Não existe. Criar com a skill `adicionar-npc`.

### Battle sprite (front pic)

Não existe. Criar com a skill `adicionar-grafico-trainer`.

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

Nenhuma. Ao criar, seguir a skill `adicionar-batalha-npc` (e `alocar-flag` se precisar de flag nova).

### Time das Rift Missions

✅ **Implementado em 31/10/2026** (lote novo, time montado pelo Codex e conferido pelo `novos/integrar.py`: R10–R13 e habilidades): `TRAINER_NEXUS_KORRINA` = **1192** (bloco 2, flag `0xB1C`), luta genérica `Nexus_EventScript_Korrina_Fight` em `data/scripts/nexus.inc`, linha em `src/data/nexus/trainers.h`. Ainda não é campeão de nenhum lendário.

```
=== TRAINER_NEXUS_KORRINA ===
Name: Korrina
Class: Leader
Pic: Korrina
Gender: Female
Music: Female
Double Battle: No
AI: Smart Trainer

Mienshao @ Focus Sash
Jolly Nature
Level: 100
Ability: Regenerator
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Fake Out
- Close Combat
- Knock Off
- Wide Guard

Koraidon @ Life Orb
Jolly Nature
Level: 100
Ability: Orichalcum Pulse
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Collision Course
- Flare Blitz
- Dragon Claw
- U-turn

Urshifu @ Choice Band
Adamant Nature
Level: 100
Ability: Unseen Fist
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Wicked Blow
- Close Combat
- Sucker Punch
- U-turn

Lucario @ Fightite
Jolly Nature
Level: 100
Ability: Justified
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Close Combat
- Meteor Mash
- Extreme Speed
- Swords Dance

Hawlucha @ White Herb
Jolly Nature
Level: 100
Ability: Unburden
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Close Combat
- Brave Bird
- Swords Dance
- Taunt

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
```

### Lendário associado

✅ **Campeão extra desde 31/10/2026** (lendário com vários campeões; o do dia é sorteado, `src/data/nexus/champions.h`; associações e falas montadas pelo Codex):

- **Urshifu Single Strike** — `Nexus_EventScript_Korrina_Urshifu_ChampionFight` (falas `Nexus_Text_Korrina_Urshifu_Champion*`)
- **Koraidon** — `Nexus_EventScript_Korrina_Koraidon_ChampionFight` (falas `Nexus_Text_Korrina_Koraidon_Champion*`)
- **Zeraora** — `Nexus_EventScript_Korrina_Zeraora_ChampionFight` (falas `Nexus_Text_Korrina_Zeraora_Champion*`)


### Diálogo genérico

✅ **Implementado em 31/10/2026:** `Nexus_Text_Korrina_Intro` / `_Defeat` em `data/scripts/nexus.inc`.

**Antes da luta**

> Hear those wheels? That's your warning! I'm Korrina!
>
> My partner and I have been practicing until we move together without thinking. Ready?

**Derrota**

> Whoa! You read us perfectly! Let's practice even harder, partner!

### Diálogo associado ao lendário

_Não escrito._ (texto do jogo em inglês)
