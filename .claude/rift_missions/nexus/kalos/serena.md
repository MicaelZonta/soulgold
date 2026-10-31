# Serena

**Região da ficha:** Kalos

Aparece no checklist como:

- **Serena** (Kalos · Rivais e companheiros) — protagonista ou rival habilidosa que busca superar o jogador.

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

✅ **Implementado em 31/10/2026** (lote novo, time montado pelo Codex e conferido pelo `novos/integrar.py`: R10–R13 e habilidades): `TRAINER_NEXUS_SERENA` = **1210** (bloco 2, flag `0xB2E`), luta genérica `Nexus_EventScript_Serena_Fight` em `data/scripts/nexus.inc`, linha em `src/data/nexus/trainers.h`. Ainda não é campeão de nenhum lendário.

```
=== TRAINER_NEXUS_SERENA ===
Name: Serena
Class: Pkmn Trainer 1
Pic: Serena
Gender: Female
Music: Female
Double Battle: No
AI: Smart Trainer

Meowstic @ Light Clay
Timid Nature
Level: 100
Ability: Prankster
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Reflect
- Light Screen
- Psychic
- Thunder Wave

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

Delphox @ Life Orb
Timid Nature
Level: 100
Ability: Blaze
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Heat Wave
- Psychic
- Grass Knot
- Protect

Pangoro @ Assault Vest
Adamant Nature
Level: 100
Ability: Scrappy
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Drain Punch
- Knock Off
- Gunk Shot
- Bullet Punch

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
```

### Lendário associado

✅ **Campeão extra desde 31/10/2026** (lendário com vários campeões; o do dia é sorteado, `src/data/nexus/champions.h`; associações e falas montadas pelo Codex):

- **Xerneas** — `Nexus_EventScript_Serena_Xerneas_ChampionFight` (falas `Nexus_Text_Serena_Xerneas_Champion*`)
- **Diancie** — `Nexus_EventScript_Serena_Diancie_ChampionFight` (falas `Nexus_Text_Serena_Diancie_Champion*`)
- **Latias** — `Nexus_EventScript_Serena_Latias_ChampionFight` (falas `Nexus_Text_Serena_Latias_Champion*`)


### Diálogo genérico

✅ **Implementado em 31/10/2026:** `Nexus_Text_Serena_Intro` / `_Defeat` em `data/scripts/nexus.inc`.

**Antes da luta**

> I used to count how often somebody else won. It didn't help my team get any stronger.
>
> I'm Serena. Today I'll give you a battle that belongs to us.

**Derrota**

> That was yours. I'll take what I learned and build on it.

### Diálogo associado ao lendário

_Não escrito._ (texto do jogo em inglês)
