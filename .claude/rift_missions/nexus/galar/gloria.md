# Gloria

**Região da ficha:** Galar

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

### Time das Rift Missions

✅ **Implementado em 31/10/2026** (lote novo, time montado pelo Codex e conferido pelo `novos/integrar.py`: R10–R13 e habilidades): `TRAINER_NEXUS_GLORIA` = **1180** (bloco 2, flag `0xB10`), luta genérica `Nexus_EventScript_Gloria_Fight` em `data/scripts/nexus.inc`, linha em `src/data/nexus/trainers.h`. Ainda não é campeão de nenhum lendário.

```
=== TRAINER_NEXUS_GLORIA ===
Name: Gloria
Class: Champion
Pic: Gloria
Gender: Female
Music: Female
Double Battle: No
AI: Smart Trainer

Rillaboom @ Assault Vest
Adamant Nature
Level: 100
Ability: Grassy Surge
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Fake Out
- Grassy Glide
- Wood Hammer
- U-turn

Zacian @ Rusted Sword
Jolly Nature
Level: 100
Ability: Intrepid Sword
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Iron Head
- Play Rough
- Close Combat
- Swords Dance

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

Inteleon @ Scope Lens
Timid Nature
Level: 100
Ability: Sniper
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Snipe Shot
- Ice Beam
- Dark Pulse
- Protect
```

### Lendário associado

✅ **Campeão extra desde 31/10/2026** (lendário com vários campeões; o do dia é sorteado, `src/data/nexus/champions.h`; associações e falas montadas pelo Codex):

- **Zacian** — `Nexus_EventScript_Gloria_Zacian_ChampionFight` (falas `Nexus_Text_Gloria_Zacian_Champion*`)
- **Zamazenta** — `Nexus_EventScript_Gloria_Zamazenta_ChampionFight` (falas `Nexus_Text_Gloria_Zamazenta_Champion*`)
- **Eternatus** — `Nexus_EventScript_Gloria_Eternatus_ChampionFight` (falas `Nexus_Text_Gloria_Eternatus_Champion*`)


### Diálogo genérico

✅ **Implementado em 31/10/2026:** `Nexus_Text_Gloria_Intro` / `_Defeat` em `data/scripts/nexus.inc`.

**Antes da luta**

> I'm Gloria! I promised my team a proper challenge today.
>
> They've been watching every Trainer we pass. Looks like they've picked you!

**Derrota**

> You gave them exactly what they wanted. Me too!

### Diálogo associado ao lendário

_Não escrito._
