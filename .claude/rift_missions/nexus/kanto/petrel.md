# Petrel

**Região da ficha:** Kanto

Aparece no checklist como:

- **Petrel** (Kanto · Team Rocket) — mestre dos disfarces responsável por imitar o Diretor da Radio Tower.
- **Petrel** (Johto · Team Rocket) — infiltra-se na Radio Tower usando disfarces.

**Pronto para o Nexus:** ✅ sim — tem sprite e battle sprite.

## Checklist

- [x] Sprite de overworld *(obrigatório)*
- [x] Battle sprite / front pic *(obrigatório)*
- [x] Field mugshot (retrato na caixa de diálogo)
- [x] Time para as Rift Missions definido
- [x] Associado a um lendário
- [x] Diálogo genérico escrito
- [x] Diálogo associado ao lendário escrito

## Referências no repositório

### Sprite de overworld

| Constante | Arquivo |
|---|---|
| `OBJ_EVENT_GFX_PETREL` | `graphics/object_events/pics/people/rockets/petrel.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_PETREL` | `graphics/trainers/front_pics/petrel.png` |

### Field mugshot

| Constante | Arquivo |
|---|---|
| `MUGSHOT_PETREL` | `graphics/field_mugshots/petrel.png` |

Aparece sozinho quando o objeto que fala usa o sprite acima (`GetFieldMugshotIdByObjectGraphicsId`, `src/field_mugshot.c`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_PETREL_2` | 278 | 0x616 | Scrafty Lv49, Honchkrow Lv49, Persian Alola Lv49, Pyroar Lv51, Weezing Galar Lv50, Rotom-Wash Lv50 | `GoldenrodCity_RadioTower_5F` |
| `TRAINER_PETREL_1` | 467 | 0x6D3 | Scrafty Lv48, Persian Alola Lv48, Pyroar Lv49, Weezing Galar Lv48, Rotom-Wash Lv48 | `RocketHideout_B3F`, `src/battle_setup.c` |

### Time das Rift Missions

✅ **Implementado em 27/09/2026** (a proposta abaixo virou código): `TRAINER_NEXUS_PETREL` = **999** (flag de batalha `0x8E7`, limpa antes e depois de cada luta), bloco em `src/data/trainers.party`, nível pelo R2 (tabela em `src/data/nexus/trainers.h`). Fala genérica `Nexus_EventScript_Petrel_Fight`; campeão: `Nexus_EventScript_Petrel_Ogerpon_ChampionFight` (para Ogerpon), `Nexus_EventScript_Petrel_Meloetta_ChampionFight` (para Meloetta). Tudo em `data/scripts/nexus.inc`, sem blackout, resultado em `VAR_TEMP_3`. Para testar: menu de debug → Rift Missions… → Nexus fights… → Petrel.

📝 **Proposta de 27/09/2026, aguardando o autor.** `TRAINER_NEXUS_PETREL`, campeão de Meloetta e Ogerpon. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler).

Lendário **Hoopa** (Unbound): os anéis que trazem coisas de outro lugar, o truque de aparecer onde não devia, que é o ofício do Petrel. Semi-lendário **Meloetta**, de que ele é campeão, que troca de forma no meio da música. Mega **Pyroar** (Firetite), do time dele. Mais **Zoroark** (Illusion: o mestre dos disfarces com o Pokémon dos disfarces), **Persian-Alola** e **Weezing-Galar**, os dois do time dele neste hack. Ogerpon, a outra de que ele é campeão, fica fora do time: a Mega do Pyroar já ocupa a vaga, e a máscara dela seria a segunda.

*Plano (Singles):* Zoroark entra disfarçado do último da fila e ganha um golpe de graça; Persian-Alola pivota com Parting Shot e tira item com Knock Off; Weezing-Galar queima e limpa hazard com Defog; Hoopa de Life Orb bate com Hyperspace Fury, que atravessa Protect e Substitute; Meloetta e a Mega Pyroar limpam.

*Plano (Doubles):* Persian-Alola abre com Fake Out, Mega Pyroar com Heat Wave e Meloetta com Hyper Voice nos dois; Weezing-Galar com Levitate e Will-O-Wisp; Hyperspace Fury fura o Protect que o jogador usar contra o spread.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Hoopa-Unbound | Life Orb | Magician | Naive | Hyperspace Fury, Psyshock, Focus Blast, Protect |
| Meloetta | Life Orb | Serene Grace | Modest | Hyper Voice, Relic Song, Shadow Ball, Protect |
| Zoroark | Life Orb | Illusion | Timid | Night Daze, Flamethrower, Sludge Bomb, Nasty Plot |
| Persian-Alola | Sitrus Berry | Fur Coat | Jolly | Fake Out, Parting Shot, Knock Off, Taunt |
| Weezing-Galar | Black Sludge | Levitate | Bold | Strange Steam, Will-O-Wisp, Defog, Pain Split |
| Pyroar | Firetite | Unnerve | Timid | Heat Wave, Dark Pulse, Solar Beam, Protect |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>dev_scripts/nexus_validar_time.py</code>)</summary>

```
=== TRAINER_NEXUS_PETREL ===
Name: Petrel
Class: RocketA
Pic: Petrel
Gender: Male
Music: Rocket
Double Battle: Yes
AI: Smart Trainer

Hoopa-Unbound @ Life Orb
Naive Nature
Level: 100
Ability: Magician
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Hyperspace Fury
- Psyshock
- Focus Blast
- Protect

Meloetta @ Life Orb
Modest Nature
Level: 100
Ability: Serene Grace
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Hyper Voice
- Relic Song
- Shadow Ball
- Protect

Zoroark @ Life Orb
Timid Nature
Level: 100
Ability: Illusion
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Night Daze
- Flamethrower
- Sludge Bomb
- Nasty Plot

Persian-Alola @ Sitrus Berry
Jolly Nature
Level: 100
Ability: Fur Coat
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Fake Out
- Parting Shot
- Knock Off
- Taunt

Weezing-Galar @ Black Sludge
Bold Nature
Level: 100
Ability: Levitate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Strange Steam
- Will-O-Wisp
- Defog
- Pain Split

Pyroar @ Firetite
Timid Nature
Level: 100
Ability: Unnerve
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Heat Wave
- Dark Pulse
- Solar Beam
- Protect
```

</details>


### Lendário associado

#### Meloetta

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_Meloetta_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Meloetta**. Petrel é o campeão dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Petrel, executivo do Team Rocket e mestre dos disfarces, que se passou pelo Diretor da Radio Tower de Goldenrod.

**A criatura.** Meloetta é o Pokémon da melodia. Ao cantar a Relic Song, troca a forma de cantora (Aria) pela de dançarina (Pirouette) e volta; as melodias dela mexem com as emoções de quem ouve.

**O fragmento.** Um teatro com todos os assentos ocupados, não por gente: por figurinos, sentados de pé, de chapéu, esperando. Do palco vazio sai uma canção que ninguém está cantando.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A theater with every seat taken. Not by people: by costumes, sitting upright, hats on, waiting.
>
> A song was coming from the stage. There was nobody on it.

**Boss**

> The song changed key in the middle of a note.
>
> The singer on the stage was a dancer now, spinning, and it had been both all along.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md): o que volta é um pedaço dele, no nível 1)

> File L-648. Melody.
>
> A theater of empty costumes, and a man who owns more faces than any of them.
>
> What came home with you hums a tune I cannot place, very quietly. It changes every time I listen. It is still finding its own voice.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Meloetta_Arrival:
	.string "A theater with every seat taken. Not by\n"
	.string "people: by costumes, sitting upright,\l"
	.string "hats on, waiting.\p"
	.string "A song was coming from the stage. There\n"
	.string "was nobody on it.$"

Nexus_Text_Meloetta_Boss:
	.string "The song changed key in the middle of a\n"
	.string "note.\p"
	.string "The singer on the stage was a dancer\n"
	.string "now, spinning, and it had been both all\l"
	.string "along.$"

Nexus_Text_Meloetta_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-648. Melody.\p"
	.string "A theater of empty costumes, and a man\n"
	.string "who owns more faces than any of them.\p"
	.string "What came home with you hums a tune I\n"
	.string "cannot place, very quietly. It changes\l"
	.string "every time I listen. It is still finding\l"
	.string "its own voice.$"
```

</details>

#### Ogerpon

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_Ogerpon_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Ogerpon**. Petrel é o campeão dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Petrel, executivo do Team Rocket e mestre dos disfarces, mentiroso profissional.

**A criatura.** Ogerpon é o Pokémon da máscara de Kitakami. A vila celebra num festival três heróis que teriam expulsado um ogro; na verdade os três roubaram as máscaras da Ogerpon, e ela só queria recuperá-las. Troca de tipo com a máscara que usa.

**O fragmento.** Uma vila de montanha em noite de festival, lanternas por toda parte e todo rosto da multidão escondido atrás da mesma máscara de ogro. Morro acima, uma coisa pequena, também de máscara, observa.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A mountain village on festival night. Lanterns everywhere, and every face in the crowd hidden behind the same ogre mask.
>
> Up the hill, above the lanterns, something small was watching. It wore a mask too.

**Boss**

> The small thing came down the hill, and the crowd scattered.
>
> Only its mask held still. The eyes behind it were not angry. They were tired of being called a monster.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md): o que volta é um pedaço dele, no nível 1)

> File L-1017. Mask.
>
> A festival that tells its story backward, and a man who lies for a living and could not stand to watch it.
>
> The fragment you brought back wears no mask at all. Only a face. That is rarer than you would think.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Ogerpon_Arrival:
	.string "A mountain village on festival night.\n"
	.string "Lanterns everywhere, and every face in\l"
	.string "the crowd hidden behind the same ogre\l"
	.string "mask.\p"
	.string "Up the hill, above the lanterns,\n"
	.string "something small was watching. It wore a\l"
	.string "mask too.$"

Nexus_Text_Ogerpon_Boss:
	.string "The small thing came down the hill, and\n"
	.string "the crowd scattered.\p"
	.string "Only its mask held still. The eyes\n"
	.string "behind it were not angry. They were\l"
	.string "tired of being called a monster.$"

Nexus_Text_Ogerpon_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-1017. Mask.\p"
	.string "A festival that tells its story\n"
	.string "backward, and a man who lies for a\l"
	.string "living and could not stand to watch it.\p"
	.string "The fragment you brought back wears\n"
	.string "no mask at all. Only a face. That is\l"
	.string "rarer than you would think.$"
```

</details>


### Diálogo genérico

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Petrel_Fight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Petrel cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala dele mesmo, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

**Antes da luta**

> Ahahaha! Did you know I once ran a whole Radio Tower as its Director? Voice, suit, hair. Nobody noticed.
>
> I've been so many people, some mornings I have to check which one I am.
>
> Today? Today I'm the guy who beats you!

**Derrota**

> Ha! Tell nobody. Or tell them it was someone else.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Petrel_Intro:
	.string "Ahahaha! Did you know I once ran a\n"
	.string "whole Radio Tower as its Director?\l"
	.string "Voice, suit, hair. Nobody noticed.\p"
	.string "I've been so many people, some\n"
	.string "mornings I have to check which one I\l"
	.string "am.\p"
	.string "Today? Today I'm the guy who beats\n"
	.string "you!$"

Nexus_Text_Petrel_Defeat:
	.string "Ha! Tell nobody. Or tell them it was\n"
	.string "someone else.$"
```

</details>


#### Variações 2 e 3 (📝 proposta de 30/09/2026)

A variação 1 é o homem de mil rostos. A 2 é lore de HGSS: no esconderijo de Mahogany ele se disfarçou do próprio chefe (e aqui o chefe nunca voltou para pedir o terno de volta). A 3 é humor e dúvida: ele confere a carteira para saber quem é hoje.

**Variação 2 — o terno do chefe**

**Antes da luta**

> Ahahaha! Once I dressed up as the boss himself. Suit, voice, the cat on the lap. The grunts saluted me for a week.
>
> Then the real one never came back, and I kept the suit on a little longer.
>
> Too long? Nah. Let's go!

**Derrota**

> Lost as the boss, lost as myself. At least I'm consistent.

**Variação 3 — a carteira**

**Antes da luta**

> Quick question. Do I look like a Petrel to you? Be honest.
>
> I woke up today and couldn't remember which face I went to sleep in. Had to check my wallet.
>
> The wallet said Petrel. The wallet's been wrong before. Let's go!

**Derrota**

> Well, whoever I am, he lost. Ahaha!

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Petrel_Intro2:
	.string "Ahahaha! Once I dressed up as the boss\n"
	.string "himself. Suit, voice, the cat on the lap.\l"
	.string "The grunts saluted me for a week.\p"
	.string "Then the real one never came back, and\n"
	.string "I kept the suit on a little longer.\p"
	.string "Too long? Nah. Let's go!$"

Nexus_Text_Petrel_Defeat2:
	.string "Lost as the boss, lost as myself. At\n"
	.string "least I'm consistent.$"

Nexus_Text_Petrel_Intro3:
	.string "Quick question. Do I look like a Petrel\n"
	.string "to you? Be honest.\p"
	.string "I woke up today and couldn't remember\n"
	.string "which face I went to sleep in. Had to\l"
	.string "check my wallet.\p"
	.string "The wallet said Petrel. The wallet's\n"
	.string "been wrong before. Let's go!$"

Nexus_Text_Petrel_Defeat3:
	.string "Well, whoever I am, he lost. Ahaha!$"
```

</details>

### Diálogo associado ao lendário

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Petrel é o **campeão**, a luta logo antes do lendário. A fala é sobre a criatura, sem dizer o nome dela.

#### Meloetta

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Petrel_Meloetta_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

O Petrel já fez cem vozes: a do Diretor, a de um recruta, uma que nem a mãe dele reconheceria. Mas quando a criatura muda de forma, as duas formas são de verdade, e ele tem inveja. A virada: na noite anterior ele cantou na frente de um espelho procurando a própria voz, a de antes de todas as outras, e não achou.

**Antes da luta**

> There's a performer on that stage. Sings one way, then spins and becomes something else, mid-song.
>
> I've done a hundred voices. The Director's. A grunt's. My own mother wouldn't know me.
>
> But when it changes, both of them are real. I'm jealous, kid. Let's go!

**Derrota**

> Bravo. And that was my real voice, for once.

**Depois da luta**

> Here's a secret. Last night I sang in front of a mirror, trying to find my own voice. The one from before all the others.
>
> Couldn't find it. Every note came out as somebody I used to pretend to be.
>
> That creature doesn't have that problem. Two faces, one voice.
>
> Go listen to it. Then come tell me what I sound like.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Petrel_Meloetta_ChampionIntro:
	.string "There's a performer on that stage.\n"
	.string "Sings one way, then spins and becomes\l"
	.string "something else, mid-song.\p"
	.string "I've done a hundred voices. The\n"
	.string "Director's. A grunt's. My own mother\l"
	.string "wouldn't know me.\p"
	.string "But when it changes, both of them are\n"
	.string "real. I'm jealous, kid. Let's go!$"

Nexus_Text_Petrel_Meloetta_ChampionDefeat:
	.string "Bravo. And that was my real voice, for\n"
	.string "once.$"

Nexus_Text_Petrel_Meloetta_ChampionAfter:
	.string "{SPEAKER NAME_PETREL}Here's a secret. Last night I sang in\n"
	.string "front of a mirror, trying to find my own\l"
	.string "voice. The one from before all the\l"
	.string "others.\p"
	.string "Couldn't find it. Every note came out\n"
	.string "as somebody I used to pretend to be.\p"
	.string "That creature doesn't have that\n"
	.string "problem. Two faces, one voice.\p"
	.string "Go listen to it. Then come tell me what I\n"
	.string "sound like.$"
```

</details>

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

A variação 1 é a inveja de quem tem dois rostos verdadeiros. A 2 são os dois figurinos da primeira fila que não são dele (uniforme branco, cabelo vermelho comprido): fio de Jessie e James, a quem a proposta de campeões novos dá esta criatura; a canção fala de dois tolos que sempre perdem e voltam. A 3 é o imitador que é pego imitando.

**Variação 2 — a primeira fila**

**Antes da luta**

> Front row, center. Two costumes sitting together. White uniforms, big red R, long red hair pinned into one of the hats.
>
> They're not mine. I checked. I've never worn them in my life.
>
> Somebody out there is doing my act without me. Let's go!

**Derrota**

> Bravo. Nobody in the front row clapped, though.

**Depois da luta**

> The song comes from the stage every night. Tonight I sat in those two seats and listened.
>
> It sang about two fools who kept losing and kept coming back, and it sounded happy about it.
>
> I'd give a lot to know who they are. Go on. Ask it for an encore.

**Variação 3 — pego imitando**

**Antes da luta**

> I tried to sing along with it. Figured I could copy anything. Perfect pitch, perfect imitation.
>
> It changed key in the middle of a note, just to lose me. And then it laughed.
>
> First time anyone ever caught me copying. Let's go!

**Derrota**

> Caught twice in one day. I'm slipping.

**Depois da luta**

> Here's my theory. It changes shape so nobody can hold onto just one of it.
>
> Smart. I did the same, for years. Difference is, it always comes back to the first one.
>
> I lost track of my first one around the third wig. Go. Don't try to sing along.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Petrel_Meloetta_ChampionIntro2:
	.string "Front row, center. Two costumes sitting\n"
	.string "together. White uniforms, big red R, long\l"
	.string "red hair pinned into one of the hats.\p"
	.string "They're not mine. I checked. I've never\n"
	.string "worn them in my life.\p"
	.string "Somebody out there is doing my act\n"
	.string "without me. Let's go!$"

Nexus_Text_Petrel_Meloetta_ChampionDefeat2:
	.string "Bravo. Nobody in the front row clapped,\n"
	.string "though.$"

Nexus_Text_Petrel_Meloetta_ChampionAfter2:
	.string "{SPEAKER NAME_PETREL}The song comes from the stage every\n"
	.string "night. Tonight I sat in those two seats\l"
	.string "and listened.\p"
	.string "It sang about two fools who kept losing\n"
	.string "and kept coming back, and it sounded\l"
	.string "happy about it.\p"
	.string "I'd give a lot to know who they are. Go\n"
	.string "on. Ask it for an encore.$"

Nexus_Text_Petrel_Meloetta_ChampionIntro3:
	.string "I tried to sing along with it. Figured I\n"
	.string "could copy anything. Perfect pitch,\l"
	.string "perfect imitation.\p"
	.string "It changed key in the middle of a note,\n"
	.string "just to lose me. And then it laughed.\p"
	.string "First time anyone ever caught me\n"
	.string "copying. Let's go!$"

Nexus_Text_Petrel_Meloetta_ChampionDefeat3:
	.string "Caught twice in one day. I'm slipping.$"

Nexus_Text_Petrel_Meloetta_ChampionAfter3:
	.string "{SPEAKER NAME_PETREL}Here's my theory. It changes shape so\n"
	.string "nobody can hold onto just one of it.\p"
	.string "Smart. I did the same, for years.\n"
	.string "Difference is, it always comes back to\l"
	.string "the first one.\p"
	.string "I lost track of my first one around the\n"
	.string "third wig. Go. Don't try to sing along.$"
```

</details>

#### Ogerpon

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Petrel_Ogerpon_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

O Petrel mente por profissão, mas as mentiras dele acabam no jantar. Esta vila conta a mesma mentira há gerações, e ela machucou uma criatura o tempo todo. A virada: a criatura ainda usa a única máscara que não levaram, para ter atrás do que se esconder. Ele conhece o truque, inventou metade dele. E pede ao jogador que, quando ela tirar a máscara, não diga nada.

**Antes da luta**

> You know the story here? The village throws a festival for three heroes who drove off an ogre.
>
> It's a lie. The heroes stole the ogre's masks. The ogre only wanted them back.
>
> I lie for a living, kid. But my lies end by dinner. This one's been running for generations. Let's go!

**Derrota**

> Beat me fair and square. No mask. Good.

**Depois da luta**

> The worst part? It still wears a mask. The one they didn't take. Keeps it on so it has something to hide behind.
>
> I know that trick. I invented half of it.
>
> Go on. When it takes the mask off, don't say anything. Just let it be seen.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Petrel_Ogerpon_ChampionIntro:
	.string "You know the story here? The village\n"
	.string "throws a festival for three heroes who\l"
	.string "drove off an ogre.\p"
	.string "It's a lie. The heroes stole the ogre's\n"
	.string "masks. The ogre only wanted them back.\p"
	.string "I lie for a living, kid. But my lies end by\n"
	.string "dinner. This one's been running for\l"
	.string "generations. Let's go!$"

Nexus_Text_Petrel_Ogerpon_ChampionDefeat:
	.string "Beat me fair and square. No mask. Good.$"

Nexus_Text_Petrel_Ogerpon_ChampionAfter:
	.string "{SPEAKER NAME_PETREL}The worst part? It still wears a mask.\n"
	.string "The one they didn't take. Keeps it on\l"
	.string "so it has something to hide behind.\p"
	.string "I know that trick. I invented half of\n"
	.string "it.\p"
	.string "Go on. When it takes the mask off,\n"
	.string "don't say anything. Just let it be\l"
	.string "seen.$"
```

</details>

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

A variação 1 é a mentira do festival. A 2 é lore de Kitakami: as três estátuas dos "heróis" (cão, macaco e ave) e a máscara nas garras da ave, que o escultor nem escondeu. A 3 é o disfarce perfeito comprado na barraca, e a única criatura que o tira do rosto dele no meio de mil.

**Variação 2 — as três estátuas**

**Antes da luta**

> Up at the shrine there are three statues. Big heroes, the town says. A dog, a monkey, a bird.
>
> I looked close. The bird has a mask in its claws. The sculptor didn't even hide it.
>
> Everybody walks right past. Best con I've ever seen. Let's go!

**Derrota**

> Ahaha! Loyal to the end, huh? Not me. I'm loyal till dinner.

**Depois da luta**

> Every stall at the festival sells ogre masks. Kids wear them and run around roaring.
>
> The little one watches from the hill. It's the only real face at the whole party, and it's the one hiding.
>
> Go on up. Take a lantern. It likes the light.

**Variação 3 — desmascarado**

**Antes da luta**

> I bought a mask at the festival. Blended right in. Best disguise I ever had, and it cost me three hundred.
>
> The little one came down the hill and pulled it off my face. Mine. Out of a thousand.
>
> It knew I was the one lying. Let's go!

**Derrota**

> Unmasked twice. That's a record.

**Depois da luta**

> It didn't keep my mask. It handed it back. Held it out, like, ‘you'll want this.’
>
> It thought I needed it. …It was right. That's the worst part.
>
> I left it on the hill anyway. Go on. It doesn't hate liars. It feels sorry for us.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Petrel_Ogerpon_ChampionIntro2:
	.string "Up at the shrine there are three\n"
	.string "statues. Big heroes, the town says. A\l"
	.string "dog, a monkey, a bird.\p"
	.string "I looked close. The bird has a mask in\n"
	.string "its claws. The sculptor didn't even hide\l"
	.string "it.\p"
	.string "Everybody walks right past. Best con\n"
	.string "I've ever seen. Let's go!$"

Nexus_Text_Petrel_Ogerpon_ChampionDefeat2:
	.string "Ahaha! Loyal to the end, huh? Not me.\n"
	.string "I'm loyal till dinner.$"

Nexus_Text_Petrel_Ogerpon_ChampionAfter2:
	.string "{SPEAKER NAME_PETREL}Every stall at the festival sells ogre\n"
	.string "masks. Kids wear them and run around\l"
	.string "roaring.\p"
	.string "The little one watches from the hill.\n"
	.string "It's the only real face at the whole\l"
	.string "party, and it's the one hiding.\p"
	.string "Go on up. Take a lantern. It likes the\n"
	.string "light.$"

Nexus_Text_Petrel_Ogerpon_ChampionIntro3:
	.string "I bought a mask at the festival.\n"
	.string "Blended right in. Best disguise I ever\l"
	.string "had, and it cost me three hundred.\p"
	.string "The little one came down the hill and\n"
	.string "pulled it off my face. Mine. Out of a\l"
	.string "thousand.\p"
	.string "It knew I was the one lying. Let's go!$"

Nexus_Text_Petrel_Ogerpon_ChampionDefeat3:
	.string "Unmasked twice. That's a record.$"

Nexus_Text_Petrel_Ogerpon_ChampionAfter3:
	.string "{SPEAKER NAME_PETREL}It didn't keep my mask. It handed it\n"
	.string "back. Held it out, like, ‘you'll want\l"
	.string "this.’\p"
	.string "It thought I needed it. …It was right.\n"
	.string "That's the worst part.\p"
	.string "I left it on the hill anyway. Go on. It\n"
	.string "doesn't hate liars. It feels sorry for\l"
	.string "us.$"
```

</details>

Falante novo: `SP_NAME_PETREL`.
