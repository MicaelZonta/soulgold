# Silver

**Região da ficha:** Johto

Aparece no checklist como:

- **Silver** (Johto · Rival) — filho de Giovanni; começa cruel e aprende gradualmente a respeitar seus Pokémon.

**Pronto para o Nexus:** ✅ sim — tem sprite e battle sprite.

## Checklist

- [x] Sprite de overworld *(obrigatório)*
- [x] Battle sprite / front pic *(obrigatório)*
- [x] Field mugshot (retrato na caixa de diálogo)
- [ ] Time para as Rift Missions definido
- [ ] Associado a um lendário
- [ ] Diálogo genérico escrito
- [ ] Diálogo associado ao lendário escrito

## Referências no repositório

### Sprite de overworld

| Constante | Arquivo |
|---|---|
| `OBJ_EVENT_GFX_SILVER` | `graphics/object_events/pics/people/special/silver.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_SILVER` | `graphics/trainers/front_pics/silver.png` |

### Field mugshot

| Constante | Arquivo |
|---|---|
| `MUGSHOT_SILVER` | `graphics/field_mugshots/silver.png` |

Aparece sozinho quando o objeto que fala usa o sprite acima (`GetFieldMugshotIdByObjectGraphicsId`, `src/field_mugshot.c`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_RIVAL_TOTODILE_5` | 226 | 0x5E2 | Gengar Lv66, Kingambit Lv67, Staraptor Lv66, Victreebel Lv67, Feraligatr Lv67, Armarouge Lv66 · VS: Pink | `VictoryRoadKanto_1F`, `src/battle_setup.c`, `src/match_call.c` |
| `TRAINER_RIVAL_TOTODILE_6` | 228 | 0x5E4 | Ursaluna Bloodmoon Lv64, Crobat Lv64, Victreebel Lv64, Houndoom Lv64, Feraligatr Lv64, Tyranitar Lv64 · VS: Green | `MtMoon_Cave`, `src/battle_setup.c` |
| `TRAINER_RIVAL_TOTODILE_7` | 229 | 0x5E5 | Ursaluna Bloodmoon Lv68, Crobat Lv68, Victreebel Lv68, Houndoom Lv68, Feraligatr Lv68, Tyranitar Lv68 · VS: Pink | `IndigoPlateau_PokemonCenter`, `src/battle_setup.c` |
| `TRAINER_RIVAL_CHIKORITA_1` | 251 | 0x5FB | Chikorita Lv5 · VS: Purple | `CherrygroveCity`, `src/battle_setup.c` |
| `TRAINER_RIVAL_CHIKORITA_2` | 252 | 0x5FC | Haunter Lv20, Pawniard Lv20, Pidgeotto Lv21, Bayleef Lv21 · VS: Yellow | `AzaleaTown`, `src/battle_setup.c` |
| `TRAINER_RIVAL_CHIKORITA_3` | 253 | 0x5FD | Floatzel Lv31, Pawniard Lv31, Staravia Lv32, Lampent Lv32, Bayleef Lv32 · VS: Blue | `BurnedTower_1F`, `src/battle_setup.c` |
| `TRAINER_RIVAL_TOTODILE_3` | 326 | 0x646 | Haunter Lv31, Pawniard Lv31, Staravia Lv32, Weepinbell Lv31, Croconaw Lv33 · VS: Blue | `BurnedTower_1F` |
| `TRAINER_RIVAL_CYNDAQUIL_2` | 351 | 0x65F | Haunter Lv20, Pawniard Lv20, Pidgeotto Lv21, Quilava Lv22 · VS: Yellow | `AzaleaTown` |
| `TRAINER_RIVAL_TOTODILE_4` | 503 | 0x6F7 | Gengar Lv49, Bisharp Lv50, Staraptor Lv49, Victreebel Lv50, Feraligatr Lv51 · VS: Blue | `GoldenrodCity_UndergroundSwitches` |
| `TRAINER_RIVAL_CHIKORITA_4` | 552 | 0x728 | Floatzel Lv49, Bisharp Lv50, Staraptor Lv49, Chandelure Lv50, Meganium Lv51 · VS: Pink | `GoldenrodCity_UndergroundSwitches`, `src/battle_setup.c`, `src/match_call.c` |
| `TRAINER_RIVAL_CHIKORITA_5` | 555 | 0x72B | Floatzel Lv66, Kingambit Lv67, Staraptor Lv66, Chandelure Lv66, Meganium Lv67, Haxorus Lv66 · VS: Pink | `VictoryRoadKanto_1F`, `src/battle_setup.c` |
| `TRAINER_RIVAL_CHIKORITA_6` | 556 | 0x72C | Ursaluna Bloodmoon Lv64, Crobat Lv64, Houndoom Lv64, Meganium Lv64, Tyranitar Lv64 · VS: Green | `MtMoon_Cave`, `src/battle_setup.c` |
| `TRAINER_RIVAL_CHIKORITA_7` | 557 | 0x72D | Ursaluna Bloodmoon Lv68, Crobat Lv68, Houndoom Lv68, Meganium Lv68, Tyranitar Lv68 · VS: Pink | `IndigoPlateau_PokemonCenter`, `src/battle_setup.c` |
| `TRAINER_RIVAL_CYNDAQUIL_1` | 558 | 0x72E | Cyndaquil Lv5 · VS: Purple | `CherrygroveCity`, `src/battle_setup.c` |
| `TRAINER_RIVAL_TOTODILE_1` | 605 | 0x75D | Totodile Lv5 · VS: Purple | `CherrygroveCity`, `src/battle_setup.c` |
| `TRAINER_RIVAL_CYNDAQUIL_4` | 621 | 0x76D | Gengar Lv49, Bisharp Lv50, Staraptor Lv49, Clodsire Lv50, Typhlosion Lv51 · VS: Blue | `GoldenrodCity_UndergroundSwitches`, `src/battle_setup.c`, `src/match_call.c` |
| `TRAINER_RIVAL_CYNDAQUIL_5` | 622 | 0x76E | Gengar Lv66, Kingambit Lv67, Staraptor Lv66, Clodsire Lv67, Typhlosion Lv67, Eelektross Lv66 · VS: Pink | `VictoryRoadKanto_1F`, `src/battle_setup.c` |
| `TRAINER_RIVAL_CYNDAQUIL_6` | 623 | 0x76F | Ursaluna Bloodmoon Lv64, Crobat Lv64, Victreebel Lv64, Typhlosion Lv64, Tyranitar Lv64 · VS: Green | `MtMoon_Cave`, `src/battle_setup.c` |
| `TRAINER_RIVAL_CYNDAQUIL_7` | 624 | 0x770 | Ursaluna Bloodmoon Lv68, Crobat Lv68, Victreebel Lv68, Typhlosion Lv68, Tyranitar Lv68 · VS: Pink | `IndigoPlateau_PokemonCenter`, `src/battle_setup.c` |
| `TRAINER_RIVAL_TOTODILE_2` | 625 | 0x771 | Haunter Lv20, Pawniard Lv20, Pidgeotto Lv21, Croconaw Lv21 · VS: Yellow | `AzaleaTown` |
| `TRAINER_RIVAL_CYNDAQUIL_3` | 749 | 0x7ED | Haunter Lv30, Pawniard Lv30, Staravia Lv31, Clodsire Lv30, Quilava Lv32 · VS: Blue | `BurnedTower_1F` |

### Time das Rift Missions

📝 **Proposta de 27/09/2026, aguardando o autor.** `TRAINER_NEXUS_SILVER`, campeão de Giratina. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler).

Lendário **Giratina**, de que ele é campeão: banido do mundo pela própria violência, o que o Silver foi com os Pokémon dele antes de aprender. Semi-lendário **Raikou**: o Silver estava na Burned Tower no dia em que as feras fugiram, atrás de Pokémon lendários. Mega **Feraligatr** (Bondstone, a pedra do vínculo): o starter que ele roubou do laboratório do Elm vira Mega pela pedra da amizade. Mais **Weavile** (o Sneasel de sempre), **Crobat** (o Golbat dele evolui por amizade em HGSS: a prova de que ele mudou) e **Kingambit**, do time dele neste hack. Na campanha o starter do Silver muda conforme a escolha do jogador; aqui fica fixo no Feraligatr. Se o autor preferir, Meganium e Typhlosion também têm Mega pela Bondstone.

*Plano (Singles):* Weavile de Sash abre com Fake Out e Ice Shard; Crobat tira o ritmo com Taunt e sai com U-turn; Giratina queima com Will-O-Wisp, força troca com Dragon Tail e cura com Rest; Raikou de Specs pivota com Volt Switch; a Mega Feraligatr sobe com Dragon Dance e limpa com Sheer Force.

*Plano (Doubles):* Weavile com Fake Out e Crobat com Tailwind abrem espaço para a Mega Feraligatr subir com Dragon Dance; Kingambit com Defiant castiga o Intimidate do jogador; Giratina queima o atacante físico e Raikou pressiona com Volt Switch.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Giratina | Leftovers | Pressure | Careful | Shadow Ball, Dragon Tail, Will-O-Wisp, Rest |
| Raikou | Choice Specs | Pressure | Timid | Thunderbolt, Volt Switch, Shadow Ball, Scald |
| Feraligatr | Bondstone | Sheer Force | Adamant | Dragon Dance, Liquidation, Ice Punch, Crunch |
| Weavile | Focus Sash | Pressure | Jolly | Fake Out, Knock Off, Ice Shard, Triple Axel |
| Crobat | Leftovers | Inner Focus | Jolly | Brave Bird, Tailwind, Taunt, U-turn |
| Kingambit | Black Glasses | Defiant | Adamant | Kowtow Cleave, Sucker Punch, Iron Head, Swords Dance |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>dev_scripts/nexus_validar_time.py</code>)</summary>

```
=== TRAINER_NEXUS_SILVER ===
Name: {RIVAL}
Class: Rival
Pic: Silver
Gender: Male
Music: Silver
Double Battle: No
AI: Smart Trainer

Giratina @ Leftovers
Careful Nature
Level: 100
Ability: Pressure
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Shadow Ball
- Dragon Tail
- Will-O-Wisp
- Rest

Raikou @ Choice Specs
Timid Nature
Level: 100
Ability: Pressure
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Thunderbolt
- Volt Switch
- Shadow Ball
- Scald

Feraligatr @ Bondstone
Adamant Nature
Level: 100
Ability: Sheer Force
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Dragon Dance
- Liquidation
- Ice Punch
- Crunch

Weavile @ Focus Sash
Jolly Nature
Level: 100
Ability: Pressure
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Fake Out
- Knock Off
- Ice Shard
- Triple Axel

Crobat @ Leftovers
Jolly Nature
Level: 100
Ability: Inner Focus
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Brave Bird
- Tailwind
- Taunt
- U-turn

Kingambit @ Black Glasses
Adamant Nature
Level: 100
Ability: Defiant
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Kowtow Cleave
- Sucker Punch
- Iron Head
- Swords Dance
```

</details>


### Lendário associado

#### Giratina

📝 **Proposta de 27/09/2026, aguardando o autor.** **Giratina**. Silver é o campeão dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Silver, o rival, filho do Giovanni. Roubou um starter do laboratório do Elm, tratava os Pokémon como ferramentas e aprendeu, depois de perder para o Lance, que não confiava neles.

**A criatura.** Giratina foi banido para o Mundo Distorção pela própria violência. Lá nada está do lado certo: é o avesso do nosso mundo, e dizem que ele o observa do outro lado.

**O fragmento.** Um mundo em que nada concorda sobre onde é o chão: uma cachoeira corre de lado pelo céu, árvores crescem embaixo de rochas flutuantes e a sua sombra cai para cima.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> Nothing here agreed on which way was down.
>
> A waterfall ran sideways across the sky. Trees grew from the undersides of floating rocks. Your shadow fell up.

**Boss**

> The shadows gathered into one, huge and long, and black wings tipped with red unfolded out of it.
>
> Somewhere, the right way up was being torn open again.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md): o que volta é um pedaço dele, no nível 1)

> File L-487. Renegade.
>
> A world with no down, and a young man who ran from his father and never quite stopped.
>
> What came back with you is a small shadow that falls the right way. For now. He asked me if it would stay that way. I told him that depends on who raises it.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Giratina_Arrival:
	.string "Nothing here agreed on which way was\n"
	.string "down.\p"
	.string "A waterfall ran sideways across the\n"
	.string "sky. Trees grew from the undersides of\l"
	.string "floating rocks. Your shadow fell up.$"

Nexus_Text_Giratina_Boss:
	.string "The shadows gathered into one, huge\n"
	.string "and long, and black wings tipped with\l"
	.string "red unfolded out of it.\p"
	.string "Somewhere, the right way up was being\n"
	.string "torn open again.$"

Nexus_Text_Giratina_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-487. Renegade.\p"
	.string "A world with no down, and a young man\n"
	.string "who ran from his father and never quite\l"
	.string "stopped.\p"
	.string "What came back with you is a small\n"
	.string "shadow that falls the right way. For\l"
	.string "now. He asked me if it would stay that\l"
	.string "way. I told him that depends on who\l"
	.string "raises it.$"
```

</details>


### Diálogo genérico

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Silver cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala dele mesmo, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

**Antes da luta**

> …It's you. Figures.
>
> My Golbat evolved. You know what that takes. Don't say it.
>
> I'm still not doing this for fun. Let's go.

**Derrota**

> …Fine. I'll get stronger. With them, this time.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Silver_Intro:
	.string "…It's you. Figures.\p"
	.string "My Golbat evolved. You know what that\n"
	.string "takes. Don't say it.\p"
	.string "I'm still not doing this for fun. Let's\n"
	.string "go.$"

Nexus_Text_Silver_Defeat:
	.string "…Fine. I'll get stronger. With them,\n"
	.string "this time.$"
```

</details>


### Diálogo associado ao lendário

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Silver é o **campeão**, a luta logo antes do lendário. A fala é sobre a criatura, sem dizer o nome dela.

#### Giratina

A criatura foi jogada para fora do mundo por ser violenta e trancada num lugar onde nada fica do lado certo. O Silver se vê nela: gritava com os Pokémon quando perdiam, chamava de inúteis. Ninguém o expulsou; alguém disse que ele estava errado, e ele odiou o Lance por isso. A virada: a criatura nunca ganhou segunda chance, só uma porta e um cadeado. Ele ganhou uma, não quis e aceitou mesmo assim. E pede ao jogador que não tranque o que trouxer de lá.

**Antes da luta**

> They say that thing was thrown out of the world for being violent. Locked in a place where nothing's the right way up.
>
> I used to yell at my Pokémon when they lost. Called them useless.
>
> Nobody threw me out. Somebody told me I was wrong, and I hated him for it. …Just battle.

**Derrota**

> …Tch. Still not enough. Not yet.

**Depois da luta**

> That thing's been angry so long it probably forgot why. It never got a second chance. Just a door, and a lock.
>
> I got one. Didn't want it. Took it anyway.
>
> Go. If you bring something back from in there, don't lock it up. And don't tell it it's useless. I'd know.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Silver_ChampionIntro:
	.string "They say that thing was thrown out of\n"
	.string "the world for being violent. Locked in a\l"
	.string "place where nothing's the right way up.\p"
	.string "I used to yell at my Pokémon when they\n"
	.string "lost. Called them useless.\p"
	.string "Nobody threw me out. Somebody told me\n"
	.string "I was wrong, and I hated him for it.\l"
	.string "…Just battle.$"

Nexus_Text_Silver_ChampionDefeat:
	.string "…Tch. Still not enough. Not yet.$"

Nexus_Text_Silver_ChampionAfter:
	.string "{SPEAKER NAME_SILVER}That thing's been angry so long it\n"
	.string "probably forgot why. It never got a\l"
	.string "second chance. Just a door, and a lock.\p"
	.string "I got one. Didn't want it. Took it\n"
	.string "anyway.\p"
	.string "Go. If you bring something back from in\n"
	.string "there, don't lock it up. And don't tell\l"
	.string "it it's useless. I'd know.$"
```

</details>

Falante novo: `SP_NAME_SILVER` (o nome do Silver é escolhido pelo jogador, `{RIVAL}`; a plaquinha fixa "Silver" não acompanha o nome escolhido, decidir se ela deve ler o buffer do rival).
