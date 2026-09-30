# Wattson

**Região da ficha:** Hoenn

Aparece no checklist como:

- **Wattson — Elétrico** (Hoenn · Líderes de Ginásio) — inventor alegre responsável pelo Ginásio de Mauville.

**Pronto para o Nexus:** ✅ sim — tem sprite e battle sprite.

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

✅ **Implementado em 27/09/2026** (a proposta abaixo virou código): `TRAINER_NEXUS_WATTSON` = **1017** (flag de batalha `0x8F9`, limpa antes e depois de cada luta), bloco em `src/data/trainers.party`, nível pelo R2 (tabela em `src/data/nexus/trainers.h`). Fala genérica `Nexus_EventScript_Wattson_Fight`; campeão: `Nexus_EventScript_Wattson_Magearna_ChampionFight` (para Magearna), `Nexus_EventScript_Wattson_Zeraora_ChampionFight` (para Zeraora). Tudo em `data/scripts/nexus.inc`, sem blackout, resultado em `VAR_TEMP_3`. Para testar: menu de debug → Rift Missions… → Nexus fights… → Wattson.

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

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_Magearna_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

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

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_Zeraora_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

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

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Wattson_Fight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

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


#### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mais duas falas genéricas ([R16](../NEXUS_REGRAS.md)): falam só dele mesmo, sem o lugar nem a criatura do dia. A variação 1 é a de cima, que está no jogo; as novas não a repetem. Nada disto está no código.

**Variação 2** — a lembrança de New Mauville: tudo que ele constrói explode pelo menos uma vez, e ele se orgulha disso.

**Antes da luta**

> Wahahaha! Stand back, young one! Last time I pressed a button like this, a whole city underground lit up and nearly went up in smoke!
>
> They called it New Mauville. I called it a learning experience! Wahahaha!
>
> Everything I build blows up at least once. That's how you know it works. Now let's see if YOU work!

**Derrota**

> Wahahaha! Kaboom! Right on schedule!

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Wattson_Intro2:
	.string "Wahahaha! Stand back, young one! Last\n"
	.string "time I pressed a button like this, a\l"
	.string "whole city underground lit up and\l"
	.string "nearly went up in smoke!\p"
	.string "They called it New Mauville. I called it a\n"
	.string "learning experience! Wahahaha!\p"
	.string "Everything I build blows up at least\n"
	.string "once. That's how you know it works. Now\l"
	.string "let's see if YOU work!$"

Nexus_Text_Wattson_Defeat2:
	.string "Wahahaha! Kaboom! Right on schedule!$"
```

</details>

**Variação 3** — a dúvida: um homem de sobretudo pediu as horas, e o relógio dos dois tinha parado no mesmo minuto (fio do casaco e do relógio parado, com leveza).

**Antes da luta**

> Wahahaha! Say, you don't happen to know what time it is?
>
> A fellow in a long coat asked me that a while ago. I checked my watch. Stopped! Checked his. Stopped too!
>
> Two stopped watches, same minute! Now that's a circuit worth studying. But first -- a battle! Wahahaha!

**Derrota**

> Wahahaha! Well, THAT was quick. Did anyone time it?

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Wattson_Intro3:
	.string "Wahahaha! Say, you don't happen to\n"
	.string "know what time it is?\p"
	.string "A fellow in a long coat asked me that a\n"
	.string "while ago. I checked my watch. Stopped!\l"
	.string "Checked his. Stopped too!\p"
	.string "Two stopped watches, same minute! Now\n"
	.string "that's a circuit worth studying. But\l"
	.string "first -- a battle! Wahahaha!$"

Nexus_Text_Wattson_Defeat3:
	.string "Wahahaha! Well, THAT was quick. Did\n"
	.string "anyone time it?$"
```

</details>

### Diálogo associado ao lendário

#### Magearna

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Wattson_Magearna_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

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

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mais duas falas de campeão para Magearna: sobre a criatura, sem o nome da espécie. A variação 1 é a de cima, que está no jogo. Nada disto está no código.

**Variação 2** — o olho de inventor: ele espiou as engrenagens e viu que quem a fez nunca jogou nada fora; ele tem um ferro-velho maior que o ginásio. Depois, o que ele teria posto nela (uma risada) e o que ela já tem (um zumbido de chaleira).

**Antes da luta**

> Wahahaha! I peeked at its gears while it curtsied. Couldn't help myself! An old inventor never can.
>
> Every tooth cut by hand. Not one spare part. Whoever made it never threw anything away.
>
> Me, I've got a scrap heap taller than my Gym! Let's see if my junk can beat a masterpiece!

**Derrota**

> Wahahaha! Outclassed by quality craftsmanship!

**Depois da luta**

> You know what I'd have added, if I'd built it? A laugh. A good loud one, right in the chest.
>
> But I listened close, and it doesn't need one. It hums. Soft, like a kettle just before it boils.
>
> That's the sound of something happy to be switched on. Wahahaha! Go on, go hear it hum.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Wattson_Magearna_ChampionIntro2:
	.string "Wahahaha! I peeked at its gears while it\n"
	.string "curtsied. Couldn't help myself! An old\l"
	.string "inventor never can.\p"
	.string "Every tooth cut by hand. Not one spare\n"
	.string "part. Whoever made it never threw\l"
	.string "anything away.\p"
	.string "Me, I've got a scrap heap taller than my\n"
	.string "Gym! Let's see if my junk can beat a\l"
	.string "masterpiece!$"

Nexus_Text_Wattson_Magearna_ChampionDefeat2:
	.string "Wahahaha! Outclassed by quality\n"
	.string "craftsmanship!$"

Nexus_Text_Wattson_Magearna_ChampionAfter2:
	.string "{SPEAKER NAME_WATTSON}You know what I'd have added, if I'd\n"
	.string "built it? A laugh. A good loud one, right\l"
	.string "in the chest.\p"
	.string "But I listened close, and it doesn't\n"
	.string "need one. It hums. Soft, like a kettle\l"
	.string "just before it boils.\p"
	.string "That's the sound of something happy to\n"
	.string "be switched on. Wahahaha! Go on, go hear\l"
	.string "it hum.$"
```

</details>

**Variação 3** — o que ele perdeu: pela lenda, ela foi feita de presente para uma menina (a princesa de Azoth). O Wattson lembra da criança que lhe passava parafusos na oficina e foi embora sem se despedir.

**Antes da luta**

> I read the markings on its base. Old writing, but I made out a word or two. It was made as a present. For a little girl.
>
> Five hundred years of work, and the whole point was to make one child smile. Wahahaha… best reason I ever heard!
>
> Come on! Show me what you'd build for someone you love!

**Derrota**

> Wahahaha… Built with love, that team. I can tell.

**Depois da luta**

> There was a kid in Mauville who used to sit in my workshop and hand me screws. Never said much.
>
> I built that kid a little tin Voltorb once. It rolled. It sparked. It blew up. We laughed for an hour!
>
> The kid grew up and went off somewhere. I never did build a better one.
>
> …Go on, young one. Somebody made that little marvel a promise. Let's see it kept.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Wattson_Magearna_ChampionIntro3:
	.string "I read the markings on its base. Old\n"
	.string "writing, but I made out a word or two. It\l"
	.string "was made as a present. For a little girl.\p"
	.string "Five hundred years of work, and the\n"
	.string "whole point was to make one child smile.\l"
	.string "Wahahaha… best reason I ever heard!\p"
	.string "Come on! Show me what you'd build for\n"
	.string "someone you love!$"

Nexus_Text_Wattson_Magearna_ChampionDefeat3:
	.string "Wahahaha… Built with love, that team. I\n"
	.string "can tell.$"

Nexus_Text_Wattson_Magearna_ChampionAfter3:
	.string "{SPEAKER NAME_WATTSON}There was a kid in Mauville who used to\n"
	.string "sit in my workshop and hand me screws.\l"
	.string "Never said much.\p"
	.string "I built that kid a little tin Voltorb\n"
	.string "once. It rolled. It sparked. It blew up.\l"
	.string "We laughed for an hour!\p"
	.string "The kid grew up and went off somewhere.\n"
	.string "I never did build a better one.\p"
	.string "…Go on, young one. Somebody made that\n"
	.string "little marvel a promise. Let's see it\l"
	.string "kept.$"
```

</details>

#### Zeraora

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Wattson_Zeraora_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

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

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mais duas falas de campeão para Zeraora: sobre a criatura, sem o nome da espécie. A variação 1 é a de cima, que está no jogo. Nada disto está no código.

**Variação 2** — humor: o velho tentou correr atrás dele pela rua e os joelhos reclamaram; tentou medir a velocidade e o ponteiro caiu. O conselho muda de "fique parado" (variação 1) para "chegue antes".

**Antes da luta**

> Wahahaha! I tried to follow it down the street. Made it three lampposts before my knees filed a complaint!
>
> It's gone before the spark even lands. I've clocked lightning in my lab slower than that!
>
> Well, I may be slow, but I'm stubborn! Let's see how fast YOU are!

**Derrota**

> Wahahaha! Left in the dust! Or the static!

**Depois da luta**

> I tried to measure its speed. The needle on my meter spun around twice and fell off!
>
> So I counted lampposts instead. Four hundred lamps, gone dark in one breath.
>
> Don't try to catch up to it, young one. Get where it's going first! Wahahaha!

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Wattson_Zeraora_ChampionIntro2:
	.string "Wahahaha! I tried to follow it down the\n"
	.string "street. Made it three lampposts before\l"
	.string "my knees filed a complaint!\p"
	.string "It's gone before the spark even lands.\n"
	.string "I've clocked lightning in my lab slower\l"
	.string "than that!\p"
	.string "Well, I may be slow, but I'm stubborn!\n"
	.string "Let's see how fast YOU are!$"

Nexus_Text_Wattson_Zeraora_ChampionDefeat2:
	.string "Wahahaha! Left in the dust! Or the\n"
	.string "static!$"

Nexus_Text_Wattson_Zeraora_ChampionAfter2:
	.string "{SPEAKER NAME_WATTSON}I tried to measure its speed. The needle\n"
	.string "on my meter spun around twice and fell\l"
	.string "off!\p"
	.string "So I counted lampposts instead. Four\n"
	.string "hundred lamps, gone dark in one breath.\p"
	.string "Don't try to catch up to it, young one.\n"
	.string "Get where it's going first! Wahahaha!$"
```

</details>

**Variação 3** — a culpa: no filme, ele vivia numa floresta que virou cidade cheia de fios. O Wattson também construiu uma cidade de fios e nunca perguntou o que havia ali antes.

**Antes da luta**

> I heard a story about it. Once it lived in a forest. Then people came, cut the trees, and built a city full of wires.
>
> Now it runs through those wires and turns every light off behind it.
>
> Wahahaha… I built a city of wires too, you know. Makes an old man wonder whose trees were there first.
>
> Battle me! I think better after a good shock!

**Derrota**

> Wahahaha… Short-circuited. Fair enough.

**Depois da luta**

> When they built Mauville, I cut the ribbon myself. Big scissors! Big crowd! I never asked what was there before.
>
> That creature isn't angry at the light. It's angry that nobody asked.
>
> So when you meet it… ask. Wahahaha! Worst it can do is zap you!

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Wattson_Zeraora_ChampionIntro3:
	.string "I heard a story about it. Once it lived\n"
	.string "in a forest. Then people came, cut the\l"
	.string "trees, and built a city full of wires.\p"
	.string "Now it runs through those wires and\n"
	.string "turns every light off behind it.\p"
	.string "Wahahaha… I built a city of wires too,\n"
	.string "you know. Makes an old man wonder whose\l"
	.string "trees were there first.\p"
	.string "Battle me! I think better after a good\n"
	.string "shock!$"

Nexus_Text_Wattson_Zeraora_ChampionDefeat3:
	.string "Wahahaha… Short-circuited. Fair\n"
	.string "enough.$"

Nexus_Text_Wattson_Zeraora_ChampionAfter3:
	.string "{SPEAKER NAME_WATTSON}When they built Mauville, I cut the\n"
	.string "ribbon myself. Big scissors! Big crowd! I\l"
	.string "never asked what was there before.\p"
	.string "That creature isn't angry at the light.\n"
	.string "It's angry that nobody asked.\p"
	.string "So when you meet it… ask. Wahahaha!\n"
	.string "Worst it can do is zap you!$"
```

</details>

Falante novo: `SP_NAME_WATTSON` (não existe ainda em `include/constants/speaker_names.h`).
