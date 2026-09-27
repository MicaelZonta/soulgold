# Wattson

**Região da ficha:** Hoenn

Aparece no checklist como:

- **Wattson — Elétrico** (Hoenn · Líderes de Ginásio) — inventor alegre responsável pelo Ginásio de Mauville.

**Pronto para o Nexus:** ✅ sim — tem sprite e battle sprite.

## Checklist

- [x] Sprite de overworld *(obrigatório)*
- [x] Battle sprite / front pic *(obrigatório)*
- [ ] Field mugshot (retrato na caixa de diálogo)
- [ ] Time para as Rift Missions definido
- [ ] Associado a um lendário
- [ ] Diálogo genérico escrito
- [ ] Diálogo associado ao lendário escrito

## Referências no repositório

### Sprite de overworld

| Constante | Arquivo |
|---|---|
| `OBJ_EVENT_GFX_WATTSON` | `graphics/object_events/pics/people/gym_leaders/wattson.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_LEADER_WATTSON` | `graphics/trainers/front_pics/leader_wattson.png` |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_WATTSON_4` | 780 | 0x80C | **sem time** (ID reservado, sem bloco no `.party`) | — (nenhum script chama) |
| `TRAINER_WATTSON_5` | 781 | 0x80D | **sem time** (ID reservado, sem bloco no `.party`) | `src/battle_dome.c` |

IDs aposentados na limpeza de treinadores (não reaproveitar sem necessidade): `TRAINER_UNUSED_453` (ex-`TRAINER_WATTSON_1`, 267).

### Time das Rift Missions

📝 **Proposta de 27/09/2026, aguardando o autor.** `TRAINER_NEXUS_WATTSON`, campeão de Magearna e Zeraora. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler).

Lendário **Magearna**, o Pokémon artificial construído há 500 anos: a obra-prima de um inventor, no time de outro inventor; semi-lendário **Zeraora**, eletricidade com pernas; Mega **Manectric** (Electrite), o ás dele. Mais **Magnezone** e **Electrode** (o Magneton e o Voltorb dos times dele, evoluídos) e **Rotom-Wash**, o fantasma que mora nos aparelhos (aqui, na máquina de lavar), bem-vindo numa cidade feita de fios como Mauville.

*Plano (Singles):* corrente contínua. O Electrode, rápido, abre com Taunt e as duas telas; daí em diante tudo pivota com Volt Switch (Magnezone de Choice Specs, Manectric, Zeraora, Rotom) até achar a troca boa. O Magnezone com Magnet Pull prende e derruba o Aço do adversário; a Magearna de Assault Vest e Soul-Heart é a âncora especial; o Rotom-Wash de Levitate segura os golpes de Terra que o resto do time teme, e o Hydro Pump dele pune Terra e Fogo.

*Plano (Doubles):* a Mega Manectric com Lightning Rod puxa os golpes Elétricos do adversário e ganha Sp. Atk; Snarl e Electroweb (alvo duplo, só nos adversários) controlam o campo; o Zeraora de Volt Absorb e o Rotom-Wash de Levitate cobrem as fraquezas (o Rotom-Wash, Água/Elétrico, tira o Fogo e a Terra de cima do resto do time). Nada de Discharge nem Earthquake: nenhum golpe acerta o parceiro.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Magearna | Assault Vest | Soul-Heart | Modest | Fleur Cannon, Flash Cannon, Volt Switch, Aura Sphere |
| Zeraora | Life Orb | Volt Absorb | Jolly | Plasma Fists, Close Combat, Knock Off, Volt Switch |
| Manectric | Electrite | Lightning Rod | Timid | Thunderbolt, Overheat, Volt Switch, Snarl |
| Magnezone | Choice Specs | Magnet Pull | Modest | Thunderbolt, Flash Cannon, Volt Switch, Electroweb |
| Electrode | Light Clay | Static | Timid | Taunt, Reflect, Light Screen, Volt Switch |
| Rotom-Wash | Leftovers | Levitate | Bold | Hydro Pump, Volt Switch, Will-O-Wisp, Thunderbolt |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>dev_scripts/nexus_validar_time.py</code>: espécie, item, habilidade, golpes e vagas)</summary>

```
=== TRAINER_NEXUS_WATTSON ===
Name: Wattson
Class: Leader
Pic: Leader Wattson
Gender: Male
Music: Male
Double Battle: No
AI: Smart Trainer

Magearna @ Assault Vest
Modest Nature
Level: 100
Ability: Soul-Heart
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Fleur Cannon
- Flash Cannon
- Volt Switch
- Aura Sphere

Zeraora @ Life Orb
Jolly Nature
Level: 100
Ability: Volt Absorb
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Plasma Fists
- Close Combat
- Knock Off
- Volt Switch

Manectric @ Electrite
Timid Nature
Level: 100
Ability: Lightning Rod
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Thunderbolt
- Overheat
- Volt Switch
- Snarl

Magnezone @ Choice Specs
Modest Nature
Level: 100
Ability: Magnet Pull
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Thunderbolt
- Flash Cannon
- Volt Switch
- Electroweb

Electrode @ Light Clay
Timid Nature
Level: 100
Ability: Static
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Taunt
- Reflect
- Light Screen
- Volt Switch

Rotom-Wash @ Leftovers
Bold Nature
Level: 100
Ability: Levitate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Hydro Pump
- Volt Switch
- Will-O-Wisp
- Thunderbolt
```

</details>


### Lendário associado

#### Magearna

📝 **Proposta de 27/09/2026, aguardando o autor.** **Magearna**. Wattson é o campeão dela: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Wattson, Líder de Mauville, o velho risonho do "Wahahaha!", inventor, responsável pela cidade coberta e pelo gerador de New Mauville, que quase explodiu.

**A criatura.** Magearna é o Pokémon artificial construído por um cientista há cerca de 500 anos. O coração dela, o Soul-Heart, é a parte que a faz viva.

**O fragmento.** Uma oficina empoeirada e morna, com todos os relógios parados no mesmo minuto. Nas bancadas, ferramentas que ninguém vivo sabe usar, todas ainda zumbindo baixinho, como se o dono tivesse acabado de sair.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A workshop, dusty and warm. Every clock on the walls had stopped at the same minute.
>
> On the benches lay tools no one alive knew how to use, and every one of them was still humming, as if someone had just stepped out.

**Boss**

> Somewhere in the dust, a gear turned over once, stiffly.
>
> A small figure of pink and steel stood up, curtsied, and opened its chest. Inside, something that was not quite a heart began to glow.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** (o que volta é o fragmento no nível 1, [R17](../NEXUS_REGRAS.md))

> File L-801. The Artificial.
>
> A workshop where every clock stopped five hundred years ago, and an old inventor who still laughs at his own sparks.
>
> What came back with you is a brand-new body, and the heart inside it is very old. Be kind to it. It remembers its maker.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Magearna_Arrival:
	.string "A workshop, dusty and warm. Every\n"
	.string "clock on the walls had stopped at the\l"
	.string "same minute.\p"
	.string "On the benches lay tools no one alive\n"
	.string "knew how to use, and every one of them\l"
	.string "was still humming, as if someone had\l"
	.string "just stepped out.$"

Nexus_Text_Magearna_Boss:
	.string "Somewhere in the dust, a gear turned\n"
	.string "over once, stiffly.\p"
	.string "A small figure of pink and steel stood\n"
	.string "up, curtsied, and opened its chest.\l"
	.string "Inside, something that was not quite a\l"
	.string "heart began to glow.$"

Nexus_Text_Magearna_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-801. The Artificial.\p"
	.string "A workshop where every clock stopped\n"
	.string "five hundred years ago, and an old\l"
	.string "inventor who still laughs at his own\l"
	.string "sparks.\p"
	.string "What came back with you is a brand-new\n"
	.string "body, and the heart inside it is very\l"
	.string "old. Be kind to it. It remembers its\l"
	.string "maker.$"
```

</details>

#### Zeraora

📝 **Proposta de 27/09/2026, aguardando o autor.** **Zeraora**. Wattson é o campeão dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Wattson, Líder de Mauville, que passou a vida domando eletricidade com chaves, circuitos e geradores.

**A criatura.** Zeraora é o mítico Trovão: junta eletricidade no corpo e ataca na velocidade de um relâmpago, com garras elétricas.

**O fragmento.** Uma cidade à noite com todas as luzes acesas. Em cada rua os postes piscam em ordem, um atrás do outro, como se alguma coisa corresse pelos fios mais rápido do que a energia.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A city at night where every light was on.
>
> Down each street the lamps flickered in order, one after another, as if something was running through the wires faster than the power could.

**Boss**

> Every light in the city went out at once.
>
> In the dark, something crackled, very close. Claws of lightning, a grin -- and then it was already somewhere else.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** (o que volta é o fragmento no nível 1, [R17](../NEXUS_REGRAS.md))

> File L-807. Thunderclap.
>
> A city whose lights could not keep up with something, and an old man who built a city of wires and laughs when they spark.
>
> What came back with you fits in the palm of a hand, and it will not stay still long enough to be counted. I counted it anyway.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Zeraora_Arrival:
	.string "A city at night where every light was\n"
	.string "on.\p"
	.string "Down each street the lamps flickered\n"
	.string "in order, one after another, as if\l"
	.string "something was running through the\l"
	.string "wires faster than the power could.$"

Nexus_Text_Zeraora_Boss:
	.string "Every light in the city went out at\n"
	.string "once.\p"
	.string "In the dark, something crackled, very\n"
	.string "close. Claws of lightning, a grin -- and\l"
	.string "then it was already somewhere else.$"

Nexus_Text_Zeraora_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-807. Thunderclap.\p"
	.string "A city whose lights could not keep up\n"
	.string "with something, and an old man who\l"
	.string "built a city of wires and laughs when\l"
	.string "they spark.\p"
	.string "What came back with you fits in the\n"
	.string "palm of a hand, and it will not stay\l"
	.string "still long enough to be counted. I\l"
	.string "counted it anyway.$"
```

</details>


### Diálogo genérico

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Wattson cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala dele mesmo, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

**Antes da luta**

> Wahahahaha! Well, would you look at this! Somewhere new, and not a single power outlet in sight!
>
> Doesn't matter a whit. I carry my own spark, young one.
>
> I'm Wattson! Now, let's see if you can light up an old man's day! Wahahaha!

**Derrota**

> Wahahaha! Blew my fuse clean out! Splendid!

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Wattson_Intro:
	.string "Wahahahaha! Well, would you look at\n"
	.string "this! Somewhere new, and not a single\l"
	.string "power outlet in sight!\p"
	.string "Doesn't matter a whit. I carry my own\n"
	.string "spark, young one.\p"
	.string "I'm Wattson! Now, let's see if you can\n"
	.string "light up an old man's day! Wahahaha!$"

Nexus_Text_Wattson_Defeat:
	.string "Wahahaha! Blew my fuse clean out!\n"
	.string "Splendid!$"
```

</details>


### Diálogo associado ao lendário

#### Magearna

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Wattson é o **campeão**, a luta logo antes da Magearna. A fala é sobre a criatura, sem dizer o nome dela.

O Wattson olha para a Magearna com olho de inventor: 500 anos e nenhuma engrenagem enferrujada. Tudo o que ele construiu (a cidade sob um teto só, o gerador subterrâneo que quase explodiu) precisava dele para funcionar; aquilo roda com o próprio coração. A virada é sobre quem a construiu: não se põe um coração numa máquina para ela funcionar melhor, e sim para alguém ficar depois que você for. O velho pensa no que ele vai deixar, e conclui, rindo, que Mauville serve: barulhenta, acesa, sempre zumbindo.

**Antes da luta**

> Wahahaha! Did you see it? Five hundred years old, and every gear still turning! Not one speck of rust!
>
> I've built plenty of things in my time. A whole city under one roof. A generator underground that nearly blew!
>
> Everything I ever built needed me to keep it running. That little marvel runs on its own heart!
>
> Show me what keeps YOUR team running! Wahahaha!

**Derrota**

> Wahahaha! Beautifully engineered, young one!

**Depois da luta**

> I've been thinking about whoever built it.
>
> You don't put a heart in a machine to make it work better. You do it so that something will stay after you're gone.
>
> I'm an old man. I suppose Mauville is the thing I leave behind. Noisy, bright, always buzzing.
>
> …Wahahaha! Not a bad heart, either! Go on, now.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Wattson_Magearna_ChampionIntro:
	.string "Wahahaha! Did you see it? Five hundred\n"
	.string "years old, and every gear still turning!\l"
	.string "Not one speck of rust!\p"
	.string "I've built plenty of things in my time.\n"
	.string "A whole city under one roof. A\l"
	.string "generator underground that nearly\l"
	.string "blew!\p"
	.string "Everything I ever built needed me to\n"
	.string "keep it running. That little marvel runs\l"
	.string "on its own heart!\p"
	.string "Show me what keeps YOUR team running!\n"
	.string "Wahahaha!$"

Nexus_Text_Wattson_Magearna_ChampionDefeat:
	.string "Wahahaha! Beautifully engineered,\n"
	.string "young one!$"

Nexus_Text_Wattson_Magearna_ChampionAfter:
	.string "{SPEAKER NAME_WATTSON}I've been thinking about whoever built\n"
	.string "it.\p"
	.string "You don't put a heart in a machine to\n"
	.string "make it work better. You do it so that\l"
	.string "something will stay after you're gone.\p"
	.string "I'm an old man. I suppose Mauville is\n"
	.string "the thing I leave behind. Noisy, bright,\l"
	.string "always buzzing.\p"
	.string "…Wahahaha! Not a bad heart, either! Go\n"
	.string "on, now.$"
```

</details>

#### Zeraora

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Wattson é o **campeão**, a luta logo antes do Zeraora. A fala é sobre a criatura, sem dizer o nome dela.

O Wattson domou eletricidade a vida toda, e ela sempre obedeceu (quase sempre). Aquilo não obedece: é a própria corrente. Ele adora na hora. A virada é a sabedoria do velho eletricista: o raio não é perigoso por ser forte, e sim por ter pressa. Então o conselho ao jogador é ser a única coisa que aquilo não consegue apressar.

**Antes da luta**

> Wahahaha! Did you see the lamps down every street? Something's running through the wires faster than the power!
>
> I've spent my whole life taming electricity. Switches, circuits, generators. It always does what I say… mostly!
>
> That thing doesn't take orders. It IS the current. Oh, I like it already! Wahahaha!
>
> Let's crackle!

**Derrota**

> Wahahaha! Grounded! Completely grounded!

**Depois da luta**

> Here's something they don't teach at any school.
>
> Lightning isn't dangerous because it's strong. It's dangerous because it's in a hurry.
>
> That creature never waits for anything. So be the one thing it can't rush.
>
> Stand still, young one. Let it come to you. Wahahaha!

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Wattson_Zeraora_ChampionIntro:
	.string "Wahahaha! Did you see the lamps down\n"
	.string "every street? Something's running\l"
	.string "through the wires faster than the\l"
	.string "power!\p"
	.string "I've spent my whole life taming\n"
	.string "electricity. Switches, circuits,\l"
	.string "generators. It always does what I say…\l"
	.string "mostly!\p"
	.string "That thing doesn't take orders. It IS\n"
	.string "the current. Oh, I like it already!\l"
	.string "Wahahaha!\p"
	.string "Let's crackle!$"

Nexus_Text_Wattson_Zeraora_ChampionDefeat:
	.string "Wahahaha! Grounded! Completely\n"
	.string "grounded!$"

Nexus_Text_Wattson_Zeraora_ChampionAfter:
	.string "{SPEAKER NAME_WATTSON}Here's something they don't teach at\n"
	.string "any school.\p"
	.string "Lightning isn't dangerous because\n"
	.string "it's strong. It's dangerous because\l"
	.string "it's in a hurry.\p"
	.string "That creature never waits for\n"
	.string "anything. So be the one thing it can't\l"
	.string "rush.\p"
	.string "Stand still, young one. Let it come to\n"
	.string "you. Wahahaha!$"
```

</details>

Falante novo: `SP_NAME_WATTSON` (não existe ainda em `include/constants/speaker_names.h`).
