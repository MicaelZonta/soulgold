# Melony

**Região da ficha:** Galar

Aparece no checklist como:

- **Melony — Gelo** (Galar · Líderes de Ginásio) — Líder exclusiva de *Shield* e mãe de Gordie.

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

✅ **Implementado em 31/10/2026** (lote novo, time montado e revisado para Singles/Doubles pelo Codex — `novos/revisao_singles_doubles.md` — e conferido pelo `novos/integrar.py`: R10–R13 e habilidades): `TRAINER_NEXUS_MELONY` = **1199** (bloco 2, flag `0xB23`), luta genérica `Nexus_EventScript_Melony_Fight` em `data/scripts/nexus.inc`, linha em `src/data/nexus/trainers.h`. Ainda não é campeão de nenhum lendário.

```
=== TRAINER_NEXUS_MELONY ===
Name: Melony
Class: Leader
Pic: Melony
Gender: Female
Music: Female
Double Battle: No
AI: Smart Trainer

Ninetales-Alola @ Light Clay
Timid Nature
Level: 100
Ability: Snow Warning
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Aurora Veil
- Blizzard
- Moonblast
- Encore

Calyrex-Ice @ Leftovers
Brave Nature
Level: 100
Ability: As One Ice Rider
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Glacial Lance
- High Horsepower
- Trick Room
- Protect

Articuno @ Heavy-Duty Boots
Modest Nature
Level: 100
Ability: Pressure
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Blizzard
- Hurricane
- Roost
- Haze

Lapras @ Icetite
Modest Nature
Level: 100
Ability: Water Absorb
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Freeze-Dry
- Hydro Pump
- Thunderbolt
- Ice Shard

Frosmoth @ Heavy-Duty Boots
Modest Nature
Level: 100
Ability: Ice Scales
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Quiver Dance
- Ice Beam
- Bug Buzz
- Wide Guard

Mr Rime @ Heavy-Duty Boots
Timid Nature
Level: 100
Ability: Ice Body
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Freeze-Dry
- Psychic
- Rapid Spin
- Fake Out
```

### Lendário associado

✅ **Campeão extra desde 31/10/2026** (lendário com vários campeões; o do dia é sorteado, `src/data/nexus/champions.h`; associações e falas montadas pelo Codex):

- **Calyrex** — `Nexus_EventScript_Melony_Calyrex_ChampionFight` (falas `Nexus_Text_Melony_Calyrex_Champion*`)
- **Articuno** — `Nexus_EventScript_Melony_Articuno_ChampionFight` (falas `Nexus_Text_Melony_Articuno_Champion*`)
- **Glastrier** — `Nexus_EventScript_Melony_Glastrier_ChampionFight` (falas `Nexus_Text_Melony_Glastrier_Champion*`)


### Diálogo genérico

✅ **Implementado em 31/10/2026:** `Nexus_Text_Melony_Intro` / `_Defeat` em `data/scripts/nexus.inc`.

**Antes da luta**

> Oh, don't look so tense, love. I always give my challengers a warm welcome.
>
> After that, things get rather chilly. Shall we?

**Derrota**

> Beautifully done! I hope my children were paying attention.

### Diálogo associado ao lendário

_Não escrito._ (texto do jogo em inglês)
