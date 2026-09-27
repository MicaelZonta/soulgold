# Clair

**Região da ficha:** Johto

Aparece no checklist como:

- **Clair — Dragão** (Johto · Líderes de Ginásio) — orgulhosa Líder de Blackthorn e prima de Lance.

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
| `OBJ_EVENT_GFX_CLAIR` | `graphics/object_events/pics/people/gym_leaders/clair.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_LEADER_CLAIR` | `graphics/trainers/front_pics/leader_clair.png` |

### Field mugshot

| Constante | Arquivo |
|---|---|
| `MUGSHOT_CLAIR` | `graphics/field_mugshots/clair.png` |

Aparece sozinho quando o objeto que fala usa o sprite acima (`GetFieldMugshotIdByObjectGraphicsId`, `src/field_mugshot.c`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_CLAIR_1` | 541 | 0x71D | Goodra-Hisui Lv58, Gyarados Lv58, Dragonite Lv58, Altaria Lv58, Hydrapple Lv58, Kingdra Lv59 · *dupla* · VS: Green | `BlackthornCity_Gym`, `src/battle_setup.c`, `src/data/level_scaling_rules.h` |
| `TRAINER_CLAIR_2` | 542 | 0x71E | Goodra Lv81, Kingdra Lv82, Haxorus Lv82, Noivern Lv83, Kommo-o Lv83, Charizard Lv84 · *dupla* | `DragonsDen_Cavern`, `KitakamiRoad_House`, `SaffronCity_FightingDojoVIP`, `src/achievements.c`, `src/battle_dome.c`, `src/battle_setup.c` |
| `TRAINER_TITLE_DEFENSE_CLAIR` | 898 | 0x882 | Goodra Lv85, Kingdra Lv85, Haxorus Lv85, Rayquaza Lv85, Kommo-o Lv85, Charizard Lv85 | `src/title_defense.c` |

### Time das Rift Missions

📝 **Proposta de 27/09/2026, aguardando o autor.** `TRAINER_NEXUS_CLAIR`, campeã do Kyurem. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler).

Lendário **Kyurem**, o dragão incompleto do qual ela é campeã: o Gelo, a fraqueza de todo time de Dragão, virado arma do lado dela. Semi-lendário **Raging Bolt**, o dragão ancestral (Paradoxo do passado), a cara do clã de Blackthorn que venera dragões antigos no Dragon's Den. Mega **Dragonite** (Dragotite): o dragão-assinatura do primo Lance, nas mãos da prima que passou a vida querendo ser vista sem ele. Mais **Kingdra**, o ás dela desde Gold/Silver, e **Goodra-Hisui** e **Noivern**, dos times dela na campanha. Tudo Dragão; o Goodra-Hisui (Aço) segura Fada e Gelo.

*Plano (Doubles):* o formato dela (a luta do ginásio já é dupla). Noivern abre com Tailwind; Kyurem de Choice Specs dispara Glaciate, que acerta os dois e ainda baixa a velocidade deles; Kingdra solta Muddy Water em área com Sniper; Raging Bolt fecha com Thunderclap (prioridade) e se guarda com Protect; a Mega Dragonite sobe Dragon Dance atrás do Multiscale enquanto o parceiro chama a atenção.
*Plano (Singles):* Noivern vira pivô (U-turn, Focus Sash); Raging Bolt sobe Calm Mind com Booster Energy; Dragonite faz Dragon Dance com Multiscale intacto e limpa com Extreme Speed; Kyurem entra para quebrar com Draco Meteor e Freeze-Dry; Goodra-Hisui de Assault Vest absorve os golpes especiais que ameaçam o resto.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Kyurem | Choice Specs | Pressure | Modest | Glaciate, Draco Meteor, Freeze-Dry, Earth Power |
| Raging Bolt | Booster Energy | Protosynthesis | Modest | Thunderclap, Draco Meteor, Calm Mind, Protect |
| Dragonite | Dragotite | Multiscale | Adamant | Dragon Dance, Extreme Speed, Dragon Claw, Fire Punch |
| Kingdra | Life Orb | Sniper | Modest | Muddy Water, Draco Meteor, Ice Beam, Protect |
| Goodra-Hisui | Assault Vest | Sap Sipper | Sassy | Heavy Slam, Draco Meteor, Flamethrower, Thunderbolt |
| Noivern | Focus Sash | Infiltrator | Timid | Tailwind, Hurricane, Flamethrower, U-turn |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>nexus_validar_time.py</code>: trainerproc, constantes, learnsets e categorias)</summary>

```
=== TRAINER_NEXUS_CLAIR ===
Name: Clair
Class: Leader
Pic: Leader Clair
Gender: Female
Music: Female
Double Battle: Yes
AI: Smart Trainer

Kyurem @ Choice Specs
Modest Nature
Level: 100
Ability: Pressure
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Glaciate
- Draco Meteor
- Freeze-Dry
- Earth Power

Raging Bolt @ Booster Energy
Modest Nature
Level: 100
Ability: Protosynthesis
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Thunderclap
- Draco Meteor
- Calm Mind
- Protect

Dragonite @ Dragotite
Adamant Nature
Level: 100
Ability: Multiscale
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Dragon Dance
- Extreme Speed
- Dragon Claw
- Fire Punch

Kingdra @ Life Orb
Modest Nature
Level: 100
Ability: Sniper
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Muddy Water
- Draco Meteor
- Ice Beam
- Protect

Goodra-Hisui @ Assault Vest
Sassy Nature
Level: 100
Ability: Sap Sipper
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Heavy Slam
- Draco Meteor
- Flamethrower
- Thunderbolt

Noivern @ Focus Sash
Timid Nature
Level: 100
Ability: Infiltrator
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Tailwind
- Hurricane
- Flamethrower
- U-turn
```

</details>

### Lendário associado

#### Kyurem

📝 **Proposta de 27/09/2026, aguardando o autor.** **Kyurem**. Clair é a campeã dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Clair, Líder de Blackthorn e prima do Lance, "a melhor mestra de dragões do mundo" nas palavras dela. Perdeu a Rising Badge para o jogador, recusou-se a entregá-la e foi o Ancião do Dragon's Den que a fez ceder.

**A criatura.** Kyurem (Gelo/Dragão) gera dentro de si uma energia congelante que vaza e congela o próprio corpo. As lendas de Unova dizem que ele espera um herói que preencha as partes que faltam no corpo dele com verdade ou com ideais. Mundo em Black/White 2: Giant Chasm.

**O fragmento.** Um abismo tomado de gelo de parede a parede. No gelo, o molde vazio de um dragão, como se alguma coisa tivesse saído dali e deixado a forma para trás. O frio não vem do ar: vem do buraco.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A chasm, and ice from wall to wall.
>
> Pressed into the ice was the shape of a dragon. Empty, as if something had stepped out of it and left the mold behind.
>
> The cold was not coming from the air. It was coming from the hollow.

**Boss**

> The hollow was not empty after all.
>
> Something grey climbed out of it, half a dragon, and the ice cracked every time it breathed.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md))

> File L-646. Boundary.
>
> A dragon made of what was left over, and a dragon master people call the one left over.
>
> What came back with you is a small, cold piece of it. Keep it warm. I suspect nobody ever has.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Kyurem_Arrival:
	.string "A chasm, and ice from wall to wall.\p"
	.string "Pressed into the ice was the shape of a\n"
	.string "dragon. Empty, as if something had\l"
	.string "stepped out of it and left the mold\l"
	.string "behind.\p"
	.string "The cold was not coming from the air. It\n"
	.string "was coming from the hollow.$"

Nexus_Text_Kyurem_Boss:
	.string "The hollow was not empty after all.\p"
	.string "Something grey climbed out of it, half a\n"
	.string "dragon, and the ice cracked every time\l"
	.string "it breathed.$"

Nexus_Text_Kyurem_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-646. Boundary.\p"
	.string "A dragon made of what was left over,\n"
	.string "and a dragon master people call the one\l"
	.string "left over.\p"
	.string "What came back with you is a small, cold\n"
	.string "piece of it. Keep it warm. I suspect\l"
	.string "nobody ever has.$"
```

</details>


### Diálogo genérico

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Clair cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala dela mesma, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

**Antes da luta**

> I am Clair. The world's best dragon master.
>
> Don't look behind me for my cousin. He isn't coming, and I don't need him to.
>
> My dragons and I will do this ourselves!

**Derrota**

> …There must be some mistake. Fine. I'll say it once: you're good.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Clair_Intro:
	.string "I am Clair. The world's best dragon\n"
	.string "master.\p"
	.string "Don't look behind me for my cousin. He\n"
	.string "isn't coming, and I don't need him to.\p"
	.string "My dragons and I will do this ourselves!$"

Nexus_Text_Clair_Defeat:
	.string "…There must be some mistake. Fine. I'll\n"
	.string "say it once: you're good.$"
```

</details>


### Diálogo associado ao lendário

#### Kyurem

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Clair é a **campeã**, a luta logo antes do Kyurem. A fala é sobre a criatura, sem dizer o nome dela.

A Clair vê no Kyurem um dragão com metade de si faltando, esperando um herói que o complete, e esperando há tanto tempo que o próprio frio o congelou no lugar. Ela conhece a sensação: é a prima do Lance, a que sobra ao lado dele. A virada vem no depois: quando perdeu a insígnia para o jogador, foi mandada ao Dragon's Den como uma criança e esperava que o Ancião lhe devolvesse o orgulho; ele lhe deu perguntas. O que ela aprendeu lá é o que diz sobre a criatura: ninguém vem preencher o que falta. Ou você preenche sozinha, ou congela esperando.

**Antes da luta**

> Did you see it? Down in the ice. A dragon with half of itself missing.
>
> The old stories say it waits for a hero to fill in what it lost. Truth, or ideals. Whichever comes first.
>
> It has waited so long that its own cold froze it where it stands.
>
> …Don't look at me like that. I know what waiting feels like. Dragons, go!

**Derrota**

> I lost? …No. I am not going to sulk this time.

**Depois da luta**

> When I lost my badge to you, the Elder sent me into the Dragon's Den like a child.
>
> I thought he would give me back my pride. He gave me questions instead.
>
> That thing down there is waiting for someone to fill it up. Nobody is coming. Nobody ever does.
>
> You fill the hollow yourself, or you freeze in it. Go on. Show it how.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Clair_ChampionIntro:
	.string "Did you see it? Down in the ice. A dragon\n"
	.string "with half of itself missing.\p"
	.string "The old stories say it waits for a hero\n"
	.string "to fill in what it lost. Truth, or ideals.\l"
	.string "Whichever comes first.\p"
	.string "It has waited so long that its own cold\n"
	.string "froze it where it stands.\p"
	.string "…Don't look at me like that. I know what\n"
	.string "waiting feels like. Dragons, go!$"

Nexus_Text_Clair_ChampionDefeat:
	.string "I lost? …No. I am not going to sulk this\n"
	.string "time.$"

Nexus_Text_Clair_ChampionAfter:
	.string "{SPEAKER NAME_CLAIR}When I lost my badge to you, the Elder\n"
	.string "sent me into the Dragon's Den like a\l"
	.string "child.\p"
	.string "I thought he would give me back my\n"
	.string "pride. He gave me questions instead.\p"
	.string "That thing down there is waiting for\n"
	.string "someone to fill it up. Nobody is coming.\l"
	.string "Nobody ever does.\p"
	.string "You fill the hollow yourself, or you\n"
	.string "freeze in it. Go on. Show it how.$"
```

</details>
