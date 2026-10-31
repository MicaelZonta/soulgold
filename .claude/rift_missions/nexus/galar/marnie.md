# Marnie

**Região da ficha:** Galar

Aparece no checklist como:

- **Marnie** (Galar · Rivais de Galar) — rival de Spikemuth apoiada pelo Team Yell.
- **Marnie — Noturno** (Galar · Líderes de Ginásio) — assume o Ginásio de Spikemuth após Piers.
- **Marnie** (Galar · Campeão e Champion Cup) — representa Spikemuth na competição.
- **Marnie** (Galar · Team Yell) — candidata apoiada pelo grupo, embora não aprove suas trapaças.

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

✅ **Implementado em 31/10/2026** (lote novo, time montado pelo Codex e conferido pelo `novos/integrar.py`: R10–R13 e habilidades): `TRAINER_NEXUS_MARNIE` = **1198** (bloco 2, flag `0xB22`), luta genérica `Nexus_EventScript_Marnie_Fight` em `data/scripts/nexus.inc`, linha em `src/data/nexus/trainers.h`. Ainda não é campeão de nenhum lendário.

```
=== TRAINER_NEXUS_MARNIE ===
Name: Marnie
Class: Leader
Pic: Marnie
Gender: Female
Music: Female
Double Battle: No
AI: Smart Trainer

Grimmsnarl @ Light Clay
Careful Nature
Level: 100
Ability: Prankster
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Reflect
- Light Screen
- Spirit Break
- Fake Out

Moltres-Galar @ Weakness Policy
Modest Nature
Level: 100
Ability: Berserk
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Fiery Wrath
- Hurricane
- Nasty Plot
- Protect

Yveltal @ Life Orb
Naive Nature
Level: 100
Ability: Dark Aura
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Dark Pulse
- Oblivion Wing
- Heat Wave
- Sucker Punch

Absol @ Darktite
Jolly Nature
Level: 100
Ability: Super Luck
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Knock Off
- Sucker Punch
- Play Rough
- Swords Dance

Morpeko @ Focus Sash
Jolly Nature
Level: 100
Ability: Hunger Switch
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Fake Out
- Aura Wheel
- Parting Shot
- Protect

Toxicroak @ Life Orb
Adamant Nature
Level: 100
Ability: Dry Skin
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Drain Punch
- Gunk Shot
- Sucker Punch
- Protect
```

### Lendário associado

✅ **Campeão extra desde 31/10/2026** (lendário com vários campeões; o do dia é sorteado, `src/data/nexus/champions.h`; associações e falas montadas pelo Codex):

- **Moltres Galar** — `Nexus_EventScript_Marnie_GalarianMoltres_ChampionFight` (falas `Nexus_Text_Marnie_GalarianMoltres_Champion*`)
- **Yveltal** — `Nexus_EventScript_Marnie_Yveltal_ChampionFight` (falas `Nexus_Text_Marnie_Yveltal_Champion*`)
- **Darkrai** — `Nexus_EventScript_Marnie_Darkrai_ChampionFight` (falas `Nexus_Text_Marnie_Darkrai_Champion*`)


### Diálogo genérico

✅ **Implementado em 31/10/2026:** `Nexus_Text_Marnie_Intro` / `_Defeat` em `data/scripts/nexus.inc`.

**Antes da luta**

> I'm Marnie. My fans make enough noise for both of us.
>
> I'll let my team handle the rest. Don't expect us to hold back.

**Derrota**

> You earned that. I'll have to give everyone a better show next time.

### Diálogo associado ao lendário

_Não escrito._ (texto do jogo em inglês)
