# Valerie

**Região da ficha:** Kalos

Aparece no checklist como:

- **Valerie — Fada** (Kalos · Líderes de Ginásio) — estilista que deseja compreender o ponto de vista dos Pokémon.

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

✅ **Implementado em 31/10/2026** (lote novo, time montado e revisado para Singles/Doubles pelo Codex — `novos/revisao_singles_doubles.md` — e conferido pelo `novos/integrar.py`: R10–R13 e habilidades): `TRAINER_NEXUS_VALERIE` = **1214** (bloco 2, flag `0xB32`), luta genérica `Nexus_EventScript_Valerie_Fight` em `data/scripts/nexus.inc`, linha em `src/data/nexus/trainers.h`. Ainda não é campeão de nenhum lendário.

```
=== TRAINER_NEXUS_VALERIE ===
Name: Valerie
Class: Leader
Pic: Valerie
Gender: Female
Music: Female
Double Battle: No
AI: Smart Trainer

Mr Mime @ Light Clay
Timid Nature
Level: 100
Ability: Filter
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Reflect
- Light Screen
- Dazzling Gleam
- Psychic

Xerneas @ Power Herb
Modest Nature
Level: 100
Ability: Fairy Aura
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Geomancy
- Moonblast
- Grass Knot
- Focus Blast

Diancie @ Fairytite
Modest Nature
Level: 100
Ability: Clear Body
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Diamond Storm
- Moonblast
- Earth Power
- Protect

Sylveon @ Throat Spray
Modest Nature
Level: 100
Ability: Pixilate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Hyper Voice
- Psyshock
- Mystical Fire
- Protect

Mawile @ Assault Vest
Adamant Nature
Level: 100
Ability: Intimidate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Play Rough
- Iron Head
- Sucker Punch
- Fire Fang

Aromatisse @ Leftovers
Quiet Nature
Level: 100
Ability: Aroma Veil
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Moonblast
- Protect
- Wish
- Heal Pulse
```

### Lendário associado

✅ **Campeão extra desde 31/10/2026** (lendário com vários campeões; o do dia é sorteado, `src/data/nexus/champions.h`; associações e falas montadas pelo Codex):

- **Xerneas** — `Nexus_EventScript_Valerie_Xerneas_ChampionFight` (falas `Nexus_Text_Valerie_Xerneas_Champion*`)
- **Diancie** — `Nexus_EventScript_Valerie_Diancie_ChampionFight` (falas `Nexus_Text_Valerie_Diancie_Champion*`)
- **Pheromosa** — `Nexus_EventScript_Valerie_Pheromosa_ChampionFight` (falas `Nexus_Text_Valerie_Pheromosa_Champion*`)


### Diálogo genérico

✅ **Implementado em 31/10/2026:** `Nexus_Text_Valerie_Intro` / `_Defeat` em `data/scripts/nexus.inc`.

**Antes da luta**

> I try to make clothes that feel the way a Pokemon must feel in its own skin.
>
> Battling brings me a little closer. Would you care to join us?

**Derrota**

> How lovely. For a moment, I almost understood their language.

### Diálogo associado ao lendário

_Não escrito._ (texto do jogo em inglês)
