# Hop

**Região da ficha:** Galar

Aparece no checklist como:

- **Hop** (Galar · Rivais de Galar) — irmão de Leon que busca tornar-se Campeão e depois encontra vocação como pesquisador.
- **Hop** (Galar · Campeão e Champion Cup) — compete na Champion Cup para tentar superar o irmão.

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

✅ **Implementado em 31/10/2026** (lote novo, time montado e revisado para Singles/Doubles pelo Codex — `novos/revisao_singles_doubles.md` — e conferido pelo `novos/integrar.py`: R10–R13 e habilidades): `TRAINER_NEXUS_HOP` = **1185** (bloco 2, flag `0xB15`), luta genérica `Nexus_EventScript_Hop_Fight` em `data/scripts/nexus.inc`, linha em `src/data/nexus/trainers.h`. Ainda não é campeão de nenhum lendário.

```
=== TRAINER_NEXUS_HOP ===
Name: Hop
Class: Rival
Pic: Hop
Gender: Male
Music: Male
Double Battle: No
AI: Smart Trainer

Zamazenta @ Rusted Shield
Impish Nature
Level: 100
Ability: Dauntless Shield
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Body Press
- Iron Defense
- Iron Head
- Wide Guard

Silvally @ Life Orb
Adamant Nature
Level: 100
Ability: RKS System
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Multi-Attack
- Crunch
- Flamethrower
- Parting Shot

Snorlax @ Normalite
Careful Nature
Level: 100
Ability: Thick Fat
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Body Slam
- Heavy Slam
- Curse
- High Horsepower

Dubwool @ Leftovers
Impish Nature
Level: 100
Ability: Fluffy
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Body Press
- Cotton Guard
- Rest
- Sleep Talk

Corviknight @ Rocky Helmet
Impish Nature
Level: 100
Ability: Mirror Armor
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Brave Bird
- Body Press
- Tailwind
- Roost

Cramorant @ Heavy-Duty Boots
Timid Nature
Level: 100
Ability: Gulp Missile
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Dive
- Hurricane
- Roost
- Tailwind
```

### Lendário associado

✅ **Campeão extra desde 31/10/2026** (lendário com vários campeões; o do dia é sorteado, `src/data/nexus/champions.h`; associações e falas montadas pelo Codex):

- **Zamazenta** — `Nexus_EventScript_Hop_Zamazenta_ChampionFight` (falas `Nexus_Text_Hop_Zamazenta_Champion*`)
- **Silvally** — `Nexus_EventScript_Hop_Silvally_ChampionFight` (falas `Nexus_Text_Hop_Silvally_Champion*`)
- **Suicune** — `Nexus_EventScript_Hop_Suicune_ChampionFight` (falas `Nexus_Text_Hop_Suicune_Champion*`)


### Diálogo genérico

✅ **Implementado em 31/10/2026:** `Nexus_Text_Hop_Intro` / `_Defeat` em `data/scripts/nexus.inc`.

**Antes da luta**

> I used to measure every win against my brother's.
>
> Now I watch my partners. They're ready, and that's all the reason I need. Come on!

**Derrota**

> Right! I'll remember how they moved. There's loads to learn from you!

### Diálogo associado ao lendário

_Não escrito._ (texto do jogo em inglês)
