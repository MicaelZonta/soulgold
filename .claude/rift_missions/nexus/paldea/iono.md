# Iono

**Região da ficha:** Paldea (Kitakami e Blueberry)

Aparece no checklist como:

- **Iono — Elétrico** (Paldea (Kitakami e Blueberry) · Líderes de Ginásio) — streamer famosa e Líder de Levincia.

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

✅ **Implementado em 31/10/2026** (lote novo, time montado e revisado para Singles/Doubles pelo Codex — `novos/revisao_singles_doubles.md` — e conferido pelo `novos/integrar.py`: R10–R13 e habilidades): `TRAINER_NEXUS_IONO` = **1186** (bloco 2, flag `0xB16`), luta genérica `Nexus_EventScript_Iono_Fight` em `data/scripts/nexus.inc`, linha em `src/data/nexus/trainers.h`. Ainda não é campeão de nenhum lendário.

```
=== TRAINER_NEXUS_IONO ===
Name: Iono
Class: Leader
Pic: Iono
Gender: Female
Music: Female
Double Battle: No
AI: Smart Trainer

Kilowattrel @ Focus Sash
Timid Nature
Level: 100
Ability: Competitive
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Thunderbolt
- Air Slash
- Volt Switch
- Tailwind

Miraidon @ Choice Specs
Timid Nature
Level: 100
Ability: Hadron Engine
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Electro Drift
- Draco Meteor
- Volt Switch
- Dazzling Gleam

Regieleki @ Life Orb
Timid Nature
Level: 100
Ability: Transistor
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Thunderbolt
- Electroweb
- Volt Switch
- Extreme Speed

Eelektross @ Electrite
Modest Nature
Level: 100
Ability: Levitate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Thunderbolt
- Flamethrower
- Giga Drain
- Knock Off

Rotom-Wash @ Leftovers
Bold Nature
Level: 100
Ability: Levitate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Thunderbolt
- Will-O-Wisp
- Volt Switch
- Protect

Mismagius @ Focus Sash
Timid Nature
Level: 100
Ability: Levitate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Shadow Ball
- Mystical Fire
- Will-O-Wisp
- Taunt
```

### Lendário associado

✅ **Campeão extra desde 31/10/2026** (lendário com vários campeões; o do dia é sorteado, `src/data/nexus/champions.h`; associações e falas montadas pelo Codex):

- **Miraidon** — `Nexus_EventScript_Iono_Miraidon_ChampionFight` (falas `Nexus_Text_Iono_Miraidon_Champion*`)
- **Regieleki** — `Nexus_EventScript_Iono_Regieleki_ChampionFight` (falas `Nexus_Text_Iono_Regieleki_Champion*`)
- **Xurkitree** — `Nexus_EventScript_Iono_Xurkitree_ChampionFight` (falas `Nexus_Text_Iono_Xurkitree_Champion*`)


### Diálogo genérico

✅ **Implementado em 31/10/2026:** `Nexus_Text_Iono_Intro` / `_Defeat` em `data/scripts/nexus.inc`.

**Antes da luta**

> Your eyeballs are MINE! Iono's got a challenger with a very interesting look!
>
> Think you can keep up when the voltage spikes? Let's find out!

**Derrota**

> Bzzt! You just blew the ratings through the roof!

### Diálogo associado ao lendário

_Não escrito._ (texto do jogo em inglês)
