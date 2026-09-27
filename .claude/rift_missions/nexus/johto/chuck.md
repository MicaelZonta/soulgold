# Chuck

**Região da ficha:** Johto

Aparece no checklist como:

- **Chuck — Lutador** (Johto · Líderes de Ginásio) — Líder de Cianwood dedicado ao treinamento físico.

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
| `OBJ_EVENT_GFX_CHUCK` | `graphics/object_events/pics/people/gym_leaders/chuck.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_LEADER_CHUCK` | `graphics/trainers/front_pics/leader_chuck.png` |

### Field mugshot

| Constante | Arquivo |
|---|---|
| `MUGSHOT_CHUCK` | `graphics/field_mugshots/chuck.png` |

Aparece sozinho quando o objeto que fala usa o sprite acima (`GetFieldMugshotIdByObjectGraphicsId`, `src/field_mugshot.c`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_CHUCK_2` | 402 | 0x692 | Mienshao Lv78, Annihilape Lv78, Lilligant Hisui Lv77, Pawmot Lv78, Hawlucha Lv79, Poliwrath Lv78 · *dupla* | `KitakamiRoad_House`, `Route47`, `SaffronCity_FightingDojoVIP`, `src/achievements.c`, `src/battle_dome.c` |
| `TRAINER_CHUCK_1_2` | 442 | 0x6BA | Hitmontop Lv45, Sirfetch'd Lv45, Mienshao Lv45, Poliwrath Lv45, Falinks Lv46 · *dupla* · VS: Pink | `CianwoodGym` |
| `TRAINER_CHUCK_1` | 510 | 0x6FE | Hitmontop Lv42, Annihilape Lv42, Mienshao Lv42, Poliwrath Lv42, Falinks Lv42 · *dupla* · VS: Pink | `CianwoodGym`, `src/data/level_scaling_rules.h` |
| `TRAINER_CHUCK_1_3` | 538 | 0x71A | Hitmontop Lv48, Sirfetch'd Lv48, Mienshao Lv48, Poliwrath Lv48, Falinks Lv49 · *dupla* · VS: Pink | `CianwoodGym`, `src/battle_setup.c`, `src/match_call.c` |
| `TRAINER_TITLE_DEFENSE_CHUCK` | 895 | 0x87F | Mienshao Lv85, Annihilape Lv85, Lilligant Hisui Lv85, Pawmot Lv85, Hawlucha Lv85, Zamazenta Lv85 | `src/title_defense.c` |

### Time das Rift Missions

📝 **Proposta de 27/09/2026, aguardando o autor.** `TRAINER_NEXUS_CHUCK`, campeão do Urshifu e do Cobalion. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler).

Lendário **Zamazenta**, o escudo: com o Rusted Shield entra na forma Crowned e o Iron Head vira Behemoth Bash (`form_change_tables.h`). Para o homem que só sabe bater, o lendário do time é o que defende; é o que a luta do Cobalion ensina a ele. Semi-lendário **Urshifu** no estilo **Rapid Strike**: treinado na torre da água, a arte que flui como a cachoeira debaixo da qual o Chuck treina (ele é campeão dele e do Cobalion). Mega **Hawlucha** (Fightite), o lutador de luta livre da Title Defense. Mais **Poliwrath**, o parceiro da cachoeira e do DynamicPunch desde Gold/Silver, Annihilape (a linha do Primeape dele) e Hitmontop.

*Plano (Singles):* o Hitmontop (Intimidate) tira hazards com Rapid Spin, o Zamazenta sobe Iron Defense e bate com Body Press, Poliwrath e Annihilape sobem Bulk Up, o Urshifu acerta crítico garantido e atravessa Protect, e a Mega Hawlucha fecha com Swords Dance. *Plano (Doubles):* Fake Out e Wide Guard do Hitmontop no turno 1, Intimidate duplo, o Annihilape (Defiant) pune o Intimidate do adversário e o Urshifu (Unseen Fist) ignora o Protect de quem tenta ganhar tempo.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Zamazenta | Rusted Shield | Dauntless Shield | Impish | Iron Head, Body Press, Iron Defense, Crunch |
| Urshifu-Rapid-Strike | Life Orb | Unseen Fist | Adamant | Surging Strikes, Close Combat, Aqua Jet, U-turn |
| Hawlucha | Fightite | Unburden | Jolly | Close Combat, Brave Bird, Swords Dance, Detect |
| Poliwrath | Sitrus Berry | Water Absorb | Adamant | Waterfall, Dynamic Punch, Ice Punch, Bulk Up |
| Annihilape | Leftovers | Defiant | Careful | Rage Fist, Drain Punch, Bulk Up, Protect |
| Hitmontop | Rocky Helmet | Intimidate | Impish | Fake Out, Close Combat, Rapid Spin, Wide Guard |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>nexus_validar_time.py</code>: trainerproc, constantes, learnsets e categorias)</summary>

```
=== TRAINER_NEXUS_CHUCK ===
Name: Chuck
Class: Leader
Pic: Leader Chuck
Gender: Male
Music: Male
Double Battle: Yes
AI: Smart Trainer

Zamazenta @ Rusted Shield
Impish Nature
Level: 100
Ability: Dauntless Shield
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Iron Head
- Body Press
- Iron Defense
- Crunch

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

Hawlucha @ Fightite
Jolly Nature
Level: 100
Ability: Unburden
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Close Combat
- Brave Bird
- Swords Dance
- Detect

Poliwrath @ Sitrus Berry
Adamant Nature
Level: 100
Ability: Water Absorb
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Waterfall
- Dynamic Punch
- Ice Punch
- Bulk Up

Annihilape @ Leftovers
Careful Nature
Level: 100
Ability: Defiant
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Rage Fist
- Drain Punch
- Bulk Up
- Protect

Hitmontop @ Rocky Helmet
Impish Nature
Level: 100
Ability: Intimidate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Fake Out
- Close Combat
- Rapid Spin
- Wide Guard
```

</details>

### Lendário associado

#### Urshifu

📝 **Proposta de 27/09/2026, aguardando o autor.** **Urshifu**. Chuck é o campeão dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Chuck, Líder de Cianwood, que treina debaixo de uma cachoeira com o Poliwrath e ri alto de tudo.

**A criatura.** Urshifu evolui do Kubfu depois de treinar numa das duas Towers of Two Fists da Isle of Armor: a das trevas dá o estilo Single Strike (um golpe decisivo) e a da água dá o Rapid Strike (golpes que fluem como um rio). Os golpes dele atravessam a defesa (Unseen Fist).

**O fragmento.** Duas torres de pedra num lago: uma escura por dentro, a outra com uma cachoeira caindo por todos os andares. Das duas vem o mesmo som, um punho batendo num alvo, sem parar, há anos.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> Two stone towers stood in a lake. One was dark inside. The other had a waterfall pouring through every floor.
>
> From both came the same sound: a fist hitting a target, over and over, for years.

**Boss**

> The sound stopped.
>
> It came down the stairs of both towers at once, somehow, and bowed before it raised its fists.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md))

> File L-892. Wushu.
>
> Two towers of practice with no top, and a man who trains under waterfalls finally finding a harder one.
>
> What came back with you is small and round, and it has never trained a day. It will.
>
> He wants to come back tomorrow. I told him it may not be here. He said then he will train until it is.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Urshifu_Arrival:
	.string "Two stone towers stood in a lake. One\n"
	.string "was dark inside. The other had a\l"
	.string "waterfall pouring through every floor.\p"
	.string "From both came the same sound: a fist\n"
	.string "hitting a target, over and over, for\l"
	.string "years.$"

Nexus_Text_Urshifu_Boss:
	.string "The sound stopped.\p"
	.string "It came down the stairs of both towers\n"
	.string "at once, somehow, and bowed before it\l"
	.string "raised its fists.$"

Nexus_Text_Urshifu_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-892. Wushu.\p"
	.string "Two towers of practice with no top, and\n"
	.string "a man who trains under waterfalls\l"
	.string "finally finding a harder one.\p"
	.string "What came back with you is small and\n"
	.string "round, and it has never trained a day.\l"
	.string "It will.\p"
	.string "He wants to come back tomorrow. I told\n"
	.string "him it may not be here. He said then\l"
	.string "he will train until it is.$"
```

</details>

#### Cobalion

📝 **Proposta de 27/09/2026, aguardando o autor.** **Cobalion**. Chuck é o campeão dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Chuck, o mesmo, diante de uma criatura que luta para proteger, não para bater.

**A criatura.** Cobalion, líder das Swords of Justice de Unova (com Terrakion e Virizion). Aço/Lutador, de corpo e coração de aço, calmo. Numa guerra antiga dos humanos, protegeu os Pokémon que perderam as casas no fogo.

**O fragmento.** Um campo de batalha muito depois da batalha. Espadas enferrujadas fincadas no chão, densas como uma floresta, e entre elas Pokémon pequenos escondidos que não fogem: esperam alguém.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A battlefield long after the battle. Rusted swords stood in the ground as thick as a forest.
>
> Small Pokémon hid between them, and none of them ran. They were waiting for someone.

**Boss**

> The small ones came out of hiding.
>
> Something with a steel heart walked between the swords, and every blade leaned away to let it pass.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md))

> File L-638. Iron Will.
>
> A field of rusted swords, and a man who hits things for a living, learning that a fist can also be a shield.
>
> What you brought back stood in front of my shoe the whole way. I let it.
>
> He says the lesson hurt more than the waterfall. I have written that he is exaggerating. He is not.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Cobalion_Arrival:
	.string "A battlefield long after the battle.\n"
	.string "Rusted swords stood in the ground as\l"
	.string "thick as a forest.\p"
	.string "Small Pokémon hid between them, and\n"
	.string "none of them ran. They were waiting\l"
	.string "for someone.$"

Nexus_Text_Cobalion_Boss:
	.string "The small ones came out of hiding.\p"
	.string "Something with a steel heart walked\n"
	.string "between the swords, and every blade\l"
	.string "leaned away to let it pass.$"

Nexus_Text_Cobalion_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-638. Iron Will.\p"
	.string "A field of rusted swords, and a man\n"
	.string "who hits things for a living, learning\l"
	.string "that a fist can also be a shield.\p"
	.string "What you brought back stood in front\n"
	.string "of my shoe the whole way. I let it.\p"
	.string "He says the lesson hurt more than the\n"
	.string "waterfall. I have written that he is\l"
	.string "exaggerating. He is not.$"
```

</details>

### Diálogo genérico

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Chuck cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala dele mesmo, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

**Antes da luta**

> WAHAHAH! Finally, someone to fight!
>
> I've done a thousand push-ups since I got here. I stopped counting at a thousand, so it's probably more!
>
> My wife says I don't know when to stop. She's right. Let's go!

**Derrota**

> WAHAHAH... hah. Ow. You're strong!

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Chuck_Intro:
	.string "WAHAHAH! Finally, someone to fight!\p"
	.string "I've done a thousand push-ups since I\n"
	.string "got here. I stopped counting at a\l"
	.string "thousand, so it's probably more!\p"
	.string "My wife says I don't know when to stop.\n"
	.string "She's right. Let's go!$"

Nexus_Text_Chuck_Defeat:
	.string "WAHAHAH... hah. Ow. You're strong!$"
```

</details>

### Diálogo associado ao lendário

#### Urshifu

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Chuck é o **campeão**, a luta logo antes do Urshifu. A fala é sobre a criatura, sem dizer o nome dela.

O Chuck ouve o som das torres, um punho batendo num alvo, e sabe que ele vem de mais longe que a cachoeira dele. Quer que a criatura o ensine: um Líder de Ginásio querendo ser aluno de novo. Perde porque o jogador flui como água e ele não acerta nada. A lição é a da própria cachoeira: não dá para socar água, ela contorna o punho e continua caindo. A criatura luta assim. Então não bata mais forte, bata melhor; e, se perder, volte para debaixo dela.

**Antes da luta**

> Did you hear it? The sound from the towers? That's a fist hitting a target.
>
> I've trained under a waterfall most of my life. That sound has been going longer than that.
>
> I want it to teach me. First I have to get past you. WAHAHAH!

**Derrota**

> Hah! You flow like water. I hit nothing!

**Depois da luta**

> You know what the waterfall taught me? You can't punch water.
>
> It just goes around your fist and keeps falling. It doesn't even notice.
>
> That creature fights the same way. Hit it, and it's already somewhere else.
>
> So don't hit harder. Hit smarter. And if you lose, stand back under it and try again!

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Chuck_Urshifu_ChampionIntro:
	.string "Did you hear it? The sound from the\n"
	.string "towers? That's a fist hitting a\l"
	.string "target.\p"
	.string "I've trained under a waterfall most of\n"
	.string "my life. That sound has been going\l"
	.string "longer than that.\p"
	.string "I want it to teach me. First I have to\n"
	.string "get past you. WAHAHAH!$"

Nexus_Text_Chuck_Urshifu_ChampionDefeat:
	.string "Hah! You flow like water. I hit\n"
	.string "nothing!$"

Nexus_Text_Chuck_Urshifu_ChampionAfter:
	.string "{SPEAKER NAME_CHUCK}You know what the waterfall taught me?\n"
	.string "You can't punch water.\p"
	.string "It just goes around your fist and\n"
	.string "keeps falling. It doesn't even notice.\p"
	.string "That creature fights the same way. Hit\n"
	.string "it, and it's already somewhere else.\p"
	.string "So don't hit harder. Hit smarter. And\n"
	.string "if you lose, stand back under it and\l"
	.string "try again!$"
```

</details>

#### Cobalion

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Chuck é o **campeão**, a luta logo antes do Cobalion. A fala é sobre a criatura, sem dizer o nome dela.

Os pequenos escondidos atrás das espadas não têm medo do Chuck; têm medo do que veio antes. A criatura de coração de aço fica na frente deles: não ataca, só fica. O Chuck nunca lutou assim e tenta aprender ali mesmo. A virada é sobre ele como mestre: ensinou todos os alunos a bater (mais forte, mais rápido, de novo) e nunca ensinou nenhum a ficar na frente de alguém sem se mexer. A criatura não faz outra coisa, e é a mais forte que ele já viu.

**Antes da luta**

> See those little ones behind the swords? They're not scared of me. They're scared of what came before.
>
> The big one with the steel heart stands in front of them. Doesn't attack. Just stands.
>
> I've never fought like that in my life. Let's see if I can learn it right now!

**Derrota**

> I hit and hit, and you just held.

**Depois da luta**

> Every student I ever had, I taught how to hit. Harder, faster, again.
>
> I never taught one of them how to stand in front of someone and not move.
>
> That creature does nothing else. It's the strongest thing I've ever seen.
>
> Go on. And don't just win. Leave those little ones something to stand behind.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Chuck_Cobalion_ChampionIntro:
	.string "See those little ones behind the\n"
	.string "swords? They're not scared of me.\l"
	.string "They're scared of what came before.\p"
	.string "The big one with the steel heart stands\n"
	.string "in front of them. Doesn't attack. Just\l"
	.string "stands.\p"
	.string "I've never fought like that in my life.\n"
	.string "Let's see if I can learn it right now!$"

Nexus_Text_Chuck_Cobalion_ChampionDefeat:
	.string "I hit and hit, and you just held.$"

Nexus_Text_Chuck_Cobalion_ChampionAfter:
	.string "{SPEAKER NAME_CHUCK}Every student I ever had, I taught how\n"
	.string "to hit. Harder, faster, again.\p"
	.string "I never taught one of them how to\n"
	.string "stand in front of someone and not\l"
	.string "move.\p"
	.string "That creature does nothing else. It's\n"
	.string "the strongest thing I've ever seen.\p"
	.string "Go on. And don't just win. Leave those\n"
	.string "little ones something to stand\l"
	.string "behind.$"
```

</details>

Falante novo: `SP_NAME_CHUCK` (ainda não existe em `include/constants/speaker_names.h`; skill `nomear-falante`).
