# Tulip

**Região da ficha:** Paldea (Kitakami e Blueberry)

Aparece no checklist como:

- **Tulip — Psíquico** (Paldea (Kitakami e Blueberry) · Líderes de Ginásio) — modelo e maquiadora de Alfornada.

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

✅ **Implementado em 31/10/2026** (lote novo, time montado e revisado para Singles/Doubles pelo Codex — `novos/revisao_singles_doubles.md` — e conferido pelo `novos/integrar.py`: R10–R13 e habilidades): `TRAINER_NEXUS_TULIP` = **1213** (bloco 2, flag `0xB31`), luta genérica `Nexus_EventScript_Tulip_Fight` em `data/scripts/nexus.inc`, linha em `src/data/nexus/trainers.h`. Ainda não é campeão de nenhum lendário.

```
=== TRAINER_NEXUS_TULIP ===
Name: Tulip
Class: Leader
Pic: Tulip
Gender: Female
Music: Female
Double Battle: No
AI: Smart Trainer

Farigiraf @ Sitrus Berry
Quiet Nature
Level: 100
Ability: Armor Tail
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Hyper Voice
- Psychic
- Thunder Wave
- Helping Hand

Lunala @ Leftovers
Timid Nature
Level: 100
Ability: Shadow Shield
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Moongeist Beam
- Psyshock
- Moonblast
- Calm Mind

Cresselia @ Leftovers
Bold Nature
Level: 100
Ability: Levitate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Moonblast
- Psyshock
- Moonlight
- Thunder Wave

Gardevoir @ Fairytite
Timid Nature
Level: 100
Ability: Trace
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Hyper Voice
- Psychic
- Mystical Fire
- Protect

Espathra @ Leftovers
Modest Nature
Level: 100
Ability: Speed Boost
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Lumina Crash
- Dazzling Gleam
- Calm Mind
- Protect

Medicham @ Choice Band
Jolly Nature
Level: 100
Ability: Pure Power
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Close Combat
- Zen Headbutt
- Ice Punch
- Rock Slide
```

### Lendário associado

✅ **Campeão extra desde 31/10/2026** (lendário com vários campeões; o do dia é sorteado, `src/data/nexus/champions.h`; associações e falas montadas pelo Codex):

- **Lunala** — `Nexus_EventScript_Tulip_Lunala_ChampionFight` (falas `Nexus_Text_Tulip_Lunala_Champion*`)
- **Cresselia** — `Nexus_EventScript_Tulip_Cresselia_ChampionFight` (falas `Nexus_Text_Tulip_Cresselia_Champion*`)
- **Articuno Galar** — `Nexus_EventScript_Tulip_GalarianArticuno_ChampionFight` (falas `Nexus_Text_Tulip_GalarianArticuno_Champion*`)


### Diálogo genérico

✅ **Implementado em 31/10/2026:** `Nexus_Text_Tulip_Intro` / `_Defeat` em `data/scripts/nexus.inc`.

**Antes da luta**

> A little care can bring out something lovely. A little pressure reveals whether it will last.
>
> I'm Tulip. Let's see how your composure holds under the lights.

**Derrota**

> Beautiful. You kept your poise right through the final move.

### Diálogo associado ao lendário

_Não escrito._ (texto do jogo em inglês)
