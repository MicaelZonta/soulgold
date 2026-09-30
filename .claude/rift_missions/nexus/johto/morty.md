# Morty

**Região da ficha:** Johto

Aparece no checklist como:

- **Morty — Fantasma** (Johto · Líderes de Ginásio) — místico de Ecruteak que busca encontrar Pokémon lendários.

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
| `OBJ_EVENT_GFX_MORTY` | `graphics/object_events/pics/people/gym_leaders/morty.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_LEADER_MORTY` | `graphics/trainers/front_pics/leader_morty.png` |

### Field mugshot

| Constante | Arquivo |
|---|---|
| `MUGSHOT_MORTY` | `graphics/field_mugshots/morty.png` |

Aparece sozinho quando o objeto que fala usa o sprite acima (`GetFieldMugshotIdByObjectGraphicsId`, `src/field_mugshot.c`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_MORTY_1` | 608 | 0x760 | Mimikyu Lv34, Misdreavus Lv34, Shedinja Lv34, Doublade Lv34, Gengar Lv34 · *dupla* · VS: Purple | `EcruteakCity_Gym`, `src/battle_setup.c`, `src/data/level_scaling_rules.h` |
| `TRAINER_MORTY_2` | 609 | 0x761 | Aegislash Lv78, Dragapult Lv78, Gengar Lv78, Mismagius Lv77, Basculegion Lv77, Cofagrigus Lv78 · *dupla* | `BellchimeTrail`, `KitakamiRoad_House`, `SaffronCity_FightingDojoVIP`, `src/achievements.c`, `src/battle_dome.c`, `src/battle_setup.c` |
| `TRAINER_TITLE_DEFENSE_MORTY` | 894 | 0x87E | Aegislash Lv85, Dragapult Lv85, Gengar Lv85, Mismagius Lv85, Basculegion Lv85, Giratina Lv85 | `src/title_defense.c` |

### Time das Rift Missions

✅ **Implementado em 27/09/2026** (a proposta abaixo virou código): `TRAINER_NEXUS_MORTY` = **1004** (flag de batalha `0x8EC`, limpa antes e depois de cada luta), bloco em `src/data/trainers.party`, nível pelo R2 (tabela em `src/data/nexus/trainers.h`). Fala genérica `Nexus_EventScript_Morty_Fight`; campeão: `Nexus_EventScript_Morty_HoOh_ChampionFight` (para Ho-Oh), `Nexus_EventScript_Morty_Spectrier_ChampionFight` (para Spectrier). Tudo em `data/scripts/nexus.inc`, sem blackout, resultado em `VAR_TEMP_3`. Para testar: menu de debug → Rift Missions… → Nexus fights… → Morty.

📝 **Proposta de 27/09/2026, aguardando o autor.** `TRAINER_NEXUS_MORTY`, campeão do Ho-Oh e do Spectrier. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler).

Lendário **Ho-Oh**: o Morty treinou a vida inteira para ser digno de vê-lo, como manda a tradição de Ecruteak. Semi-lendário **Spectrier**, o cavalo fantasma que caça sem usar a visão, o avesso de um homem que treinou os olhos para ver o que não está lá (ele é campeão dele e do Ho-Oh). Mega **Gengar** (Ghostite): o Gengar clássico dele, ás desde Gold/Silver. Mais Dragapult, Aegislash e Mismagius (a linha do Misdreavus dele), da revanche e da Title Defense.

*Plano (Singles):* a Mismagius (Focus Sash) usa Taunt e Will-O-Wisp, o Ho-Oh entra e sai com Regenerator queimando com Sacred Fire, o Spectrier sobe Nasty Plot e ganha Grim Neigh a cada nocaute, o Dragapult de Choice Band limpa o Aegislash fecha com King's Shield e Shadow Sneak, e a Mega Gengar (Shadow Tag) prende quem não pode fugir e derruba com Shadow Ball e Focus Blast. *Plano (Doubles):* Tailwind do Ho-Oh, e com ele Mega Gengar e Spectrier batem primeiro nos dois lados (Shadow Tag prende os dois adversários), Dragon Darts divididos, e Protect/King's Shield para ganhar turnos. O risco é Sombrio; o Aegislash e o Ho-Oh seguram.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Ho-Oh | Heavy-Duty Boots | Regenerator | Adamant | Sacred Fire, Brave Bird, Recover, Tailwind |
| Spectrier | Life Orb | Grim Neigh | Timid | Shadow Ball, Dark Pulse, Nasty Plot, Protect |
| Gengar | Ghostite | Cursed Body | Timid | Shadow Ball, Sludge Bomb, Focus Blast, Protect |
| Dragapult | Choice Band | Clear Body | Jolly | Dragon Darts, Phantom Force, U-turn, Sucker Punch |
| Aegislash | Leftovers | Stance Change | Quiet | Shadow Ball, Flash Cannon, Shadow Sneak, King's Shield |
| Mismagius | Focus Sash | Levitate | Timid | Shadow Ball, Mystical Fire, Will-O-Wisp, Taunt |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>nexus_validar_time.py</code>: trainerproc, constantes, learnsets e categorias)</summary>

```
=== TRAINER_NEXUS_MORTY ===
Name: Morty
Class: Leader
Pic: Leader Morty
Gender: Male
Music: Male
Double Battle: No
AI: Smart Trainer

Ho-Oh @ Heavy-Duty Boots
Adamant Nature
Level: 100
Ability: Regenerator
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Sacred Fire
- Brave Bird
- Recover
- Tailwind

Spectrier @ Life Orb
Timid Nature
Level: 100
Ability: Grim Neigh
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Shadow Ball
- Dark Pulse
- Nasty Plot
- Protect

Gengar @ Ghostite
Timid Nature
Level: 100
Ability: Cursed Body
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Shadow Ball
- Sludge Bomb
- Focus Blast
- Protect

Dragapult @ Choice Band
Jolly Nature
Level: 100
Ability: Clear Body
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Dragon Darts
- Phantom Force
- U-turn
- Sucker Punch

Aegislash @ Leftovers
Quiet Nature
Level: 100
Ability: Stance Change
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Shadow Ball
- Flash Cannon
- Shadow Sneak
- King's Shield

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

</details>

### Lendário associado

#### Ho-Oh

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_HoOh_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Ho-Oh**. Morty é o campeão dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Morty, Líder de Ecruteak, místico que treina desde criança para ver o pássaro do arco-íris.

**A criatura.** Ho-Oh, o guardião dos céus de Johto, de penas de sete cores; deixa um arco-íris por onde voa. Quando a Brass Tower de Ecruteak queimou, três Pokémon morreram no incêndio e ele os trouxe de volta. A lenda diz que desce diante de um Treinador de verdadeira força.

**O fragmento.** A torre queimando para sempre: nem cai, nem apaga. As chamas estão paradas no ar, a cinza flutua na altura dos olhos, e um arco-íris atravessa a fumaça.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A tower on fire. Not burning down. Just burning, and burning, and never done.
>
> The flames hung still in the air. Ash floated at eye level. Through the smoke, a rainbow.

**Boss**

> The rainbow bent and came down.
>
> Wings of seven colors spread over the burning tower, and the flames bowed to them.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md))

> File L-250. Rainbow.
>
> A tower that never finishes burning, and a man who has waited for a rainbow since he was a child.
>
> What you carried out of the fire is small and warm, and it is not burned.
>
> He saw it today. He did not say a word for a long time. Neither did I.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_HoOh_Arrival:
	.string "A tower on fire. Not burning down.\n"
	.string "Just burning, and burning, and never\l"
	.string "done.\p"
	.string "The flames hung still in the air. Ash\n"
	.string "floated at eye level. Through the\l"
	.string "smoke, a rainbow.$"

Nexus_Text_HoOh_Boss:
	.string "The rainbow bent and came down.\p"
	.string "Wings of seven colors spread over the\n"
	.string "burning tower, and the flames bowed to\l"
	.string "them.$"

Nexus_Text_HoOh_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-250. Rainbow.\p"
	.string "A tower that never finishes burning,\n"
	.string "and a man who has waited for a rainbow\l"
	.string "since he was a child.\p"
	.string "What you carried out of the fire is\n"
	.string "small and warm, and it is not burned.\p"
	.string "He saw it today. He did not say a\n"
	.string "word for a long time. Neither did I.$"
```

</details>

#### Spectrier

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_Spectrier_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Spectrier**. Morty é o campeão dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Morty, o mesmo, diante de uma criatura que não usa os olhos.

**A criatura.** Spectrier, o cavalo fantasma de Galar, montaria do Calyrex. Sonda o que está em volta com todos os sentidos menos um: não usa a visão. Chuta sem parar e fica mais forte a cada adversário que derruba (Grim Neigh).

**O fragmento.** Um campo de neve escura à meia-noite, com uma neblina tão fechada que não se vê as próprias mãos. Só se ouve cascos, circulando, mais perto, mais longe, mais perto.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A field of dark snow at midnight, and a fog so thick you could not see your own hands.
>
> You could hear hooves, though. Circling. Closer. Then farther. Then closer.

**Boss**

> The hooves stopped right in front of you.
>
> You still could not see it. It did not need to see you either.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md))

> File L-897. Shadow Steed.
>
> A field where eyes are useless, and a man who has trained all his life to see what isn't there.
>
> What you brought back makes no sound at all. I checked twice.
>
> He found it before I did. He found it with his eyes closed.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Spectrier_Arrival:
	.string "A field of dark snow at midnight, and\n"
	.string "a fog so thick you could not see your\l"
	.string "own hands.\p"
	.string "You could hear hooves, though.\n"
	.string "Circling. Closer. Then farther. Then\l"
	.string "closer.$"

Nexus_Text_Spectrier_Boss:
	.string "The hooves stopped right in front of\n"
	.string "you.\p"
	.string "You still could not see it. It did not\n"
	.string "need to see you either.$"

Nexus_Text_Spectrier_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-897. Shadow Steed.\p"
	.string "A field where eyes are useless, and a\n"
	.string "man who has trained all his life to\l"
	.string "see what isn't there.\p"
	.string "What you brought back makes no sound\n"
	.string "at all. I checked twice.\p"
	.string "He found it before I did. He found it\n"
	.string "with his eyes closed.$"
```

</details>

### Diálogo genérico

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Morty_Fight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Morty cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala dele mesmo, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

**Antes da luta**

> I've been expecting you. Or someone. In Ecruteak, we're taught to expect.
>
> My family has trained for generations to see things that aren't there.
>
> You're here, though. That makes you easy. Shall we?

**Derrota**

> I saw that coming. I still couldn't stop it.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Morty_Intro:
	.string "I've been expecting you. Or someone.\n"
	.string "In Ecruteak, we're taught to expect.\p"
	.string "My family has trained for generations\n"
	.string "to see things that aren't there.\p"
	.string "You're here, though. That makes you\n"
	.string "easy. Shall we?$"

Nexus_Text_Morty_Defeat:
	.string "I saw that coming. I still couldn't\n"
	.string "stop it.$"
```

</details>

#### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mesmo registro da variação 1 ([R16](../NEXUS_REGRAS.md)): fala de si, sem citar o lugar nem a criatura do dia. Ainda não estão no código.

**Variação 2 — o amigo que corre.** O Eusine, sem nome: corre atrás de um Pokémon pela região inteira; o Morty espera. Esperar funciona há vinte anos, "a qualquer momento".

**Antes da luta**

> A friend of mine chases one Pokémon across the whole region. He never catches up.
>
> I told him to stop running and wait. It works for me.
>
> Well. It has worked for twenty years. Any day now. …Shall we?

**Derrota**

> Waiting would have been wiser. I'll remember that.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Morty_Intro2:
	.string "A friend of mine chases one Pokémon\n"
	.string "across the whole region. He never\l"
	.string "catches up.\p"
	.string "I told him to stop running and wait. It\n"
	.string "works for me.\p"
	.string "Well. It has worked for twenty years.\n"
	.string "Any day now. …Shall we?$"

Nexus_Text_Morty_Defeat2:
	.string "Waiting would have been wiser. I'll\n"
	.string "remember that.$"
```

</details>

**Variação 3 — o Gengar atrás de você.** Humor de fantasma: o ponto frio atrás do jogador é o Gengar dele, e gostar de alguém raramente é boa notícia.

**Antes da luta**

> Don't be alarmed. That cold spot behind you is my Gengar. He's been there since you walked in.
>
> He likes you. That's rarely good news.
>
> Let's battle before he decides to keep you.

**Derrota**

> Now he's sulking. You'll have to visit him sometime.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Morty_Intro3:
	.string "Don't be alarmed. That cold spot behind\n"
	.string "you is my Gengar. He's been there since\l"
	.string "you walked in.\p"
	.string "He likes you. That's rarely good news.\p"
	.string "Let's battle before he decides to keep\n"
	.string "you.$"

Nexus_Text_Morty_Defeat3:
	.string "Now he's sulking. You'll have to visit\n"
	.string "him sometime.$"
```

</details>

### Diálogo associado ao lendário

#### Ho-Oh

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Morty_HoOh_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Morty é o **campeão**, a luta logo antes do Ho-Oh. A fala é sobre a criatura, sem dizer o nome dela.

É a torre de Ecruteak, a que queimou antes de ele nascer; ele conhece cada viga. A lenda diz que o arco-íris desce para um Treinador de verdadeira força, e ele treinou a vida toda para isso. Hoje desceu, com o jogador ali. A derrota é curta: "não era eu". A virada é que ele não se sente enganado: se lembra de que a criatura não veio pelos mais fortes naquele dia, veio pelos três que morreram no fogo. Ela vem por quem entra no fogo mesmo assim.

**Antes da luta**

> That's our tower. The one that burned before I was born. I know every blackened beam of it.
>
> Ecruteak says the rainbow comes down for a Trainer of true power. I've trained for it my whole life.
>
> And it came down today. With you here. ...Let's find out which of us it came for.

**Derrota**

> So. It wasn't me.

**Depois da luta**

> I thought I'd feel cheated. I don't.
>
> When that tower burned, three Pokémon died in the fire. It came down and brought them back.
>
> It doesn't come for the strongest. It comes for whoever walks into the fire anyway.
>
> Go on. The tower's still burning. I'll wait out here and watch the rainbow.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Morty_HoOh_ChampionIntro:
	.string "That's our tower. The one that burned\n"
	.string "before I was born. I know every\l"
	.string "blackened beam of it.\p"
	.string "Ecruteak says the rainbow comes down\n"
	.string "for a Trainer of true power. I've\l"
	.string "trained for it my whole life.\p"
	.string "And it came down today. With you here.\n"
	.string "...Let's find out which of us it came\l"
	.string "for.$"

Nexus_Text_Morty_HoOh_ChampionDefeat:
	.string "So. It wasn't me.$"

Nexus_Text_Morty_HoOh_ChampionAfter:
	.string "{SPEAKER NAME_MORTY}I thought I'd feel cheated. I don't.\p"
	.string "When that tower burned, three Pokémon\n"
	.string "died in the fire. It came down and\l"
	.string "brought them back.\p"
	.string "It doesn't come for the strongest. It\n"
	.string "comes for whoever walks into the fire\l"
	.string "anyway.\p"
	.string "Go on. The tower's still burning. I'll\n"
	.string "wait out here and watch the rainbow.$"
```

</details>

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mesmo registro da variação 1: a criatura pelo olhar do campeão, sem o nome da espécie. Ainda não estão no código.

**Variação 2 — a outra torre.** Ecruteak tem a Bell Tower de nove andares, feita para o arco-íris pousar, e ele nunca pousa lá: pousa na queimada. O Morty conclui que a criatura prefere o lugar onde fez mais bem.

**Antes da luta**

> There's a second tower in Ecruteak. Nine floors, never touched by fire. It was built for the rainbow to land on.
>
> It never lands there. It lands on the burned one. Every time.
>
> I've always wondered why. Maybe you know. Let's find out.

**Derrota**

> The answer was you. Of course it was.

**Depois da luta**

> I think it prefers the burned one. The place where it did the most good.
>
> The new tower is beautiful. Nothing ever happened in it.
>
> Go. Walk into the fire. It will like you better for it.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Morty_HoOh_ChampionIntro2:
	.string "There's a second tower in Ecruteak.\n"
	.string "Nine floors, never touched by fire. It\l"
	.string "was built for the rainbow to land on.\p"
	.string "It never lands there. It lands on the\n"
	.string "burned one. Every time.\p"
	.string "I've always wondered why. Maybe you\n"
	.string "know. Let's find out.$"

Nexus_Text_Morty_HoOh_ChampionDefeat2:
	.string "The answer was you. Of course it was.$"

Nexus_Text_Morty_HoOh_ChampionAfter2:
	.string "{SPEAKER NAME_MORTY}I think it prefers the burned one. The\n"
	.string "place where it did the most good.\p"
	.string "The new tower is beautiful. Nothing\n"
	.string "ever happened in it.\p"
	.string "Go. Walk into the fire. It will like you\n"
	.string "better for it.$"
```

</details>

**Variação 3 — três gerações esperando.** O avô e o pai esperaram a vida toda e não viram. Ele é o primeiro da família a ver as cores, e gasta o momento lutando. A cor de perto é o detalhe que ninguém escreveu.

**Antes da luta**

> My grandfather waited his whole life to see it. My father too. Neither of them did.
>
> I'm the first in my family to see its colors, and I'm spending the moment battling you.
>
> …They would have laughed at that. Come on.

**Derrota**

> Grandfather, I'm sorry. That was embarrassing.

**Depois da luta**

> Do you know what the colors look like up close? I thought they'd be bright.
>
> They're soft. Like light through a paper screen at dusk.
>
> Nobody in my family ever wrote that down. I'll do it tonight. Go on, see for yourself.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Morty_HoOh_ChampionIntro3:
	.string "My grandfather waited his whole life to\n"
	.string "see it. My father too. Neither of them\l"
	.string "did.\p"
	.string "I'm the first in my family to see its\n"
	.string "colors, and I'm spending the moment\l"
	.string "battling you.\p"
	.string "…They would have laughed at that. Come\n"
	.string "on.$"

Nexus_Text_Morty_HoOh_ChampionDefeat3:
	.string "Grandfather, I'm sorry. That was\n"
	.string "embarrassing.$"

Nexus_Text_Morty_HoOh_ChampionAfter3:
	.string "{SPEAKER NAME_MORTY}Do you know what the colors look like up\n"
	.string "close? I thought they'd be bright.\p"
	.string "They're soft. Like light through a\n"
	.string "paper screen at dusk.\p"
	.string "Nobody in my family ever wrote that\n"
	.string "down. I'll do it tonight. Go on, see for\l"
	.string "yourself.$"
```

</details>

#### Spectrier

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Morty_Spectrier_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Morty é o **campeão**, a luta logo antes do Spectrier. A fala é sobre a criatura, sem dizer o nome dela.

O Morty é o homem que treinou os olhos para ver o que ninguém vê. A criatura caça por tudo menos a visão: som, frio, o medo na pele. Ela circula os dois desde que o jogador chegou e não olhou para nenhum deles. A virada: ele sempre achou que ver era o dom. Talvez só estivesse olhando com força demais. O conselho é fechar os olhos, porque ela vai fechar os dela de qualquer jeito.

**Antes da luta**

> Close your eyes. Go on. Listen.
>
> That's hooves. It's been circling us since you arrived, and it hasn't looked at either of us once.
>
> It doesn't need eyes. My whole life, I trained mine. ...Let's battle.

**Derrota**

> I saw every move. It didn't help.

**Depois da luta**

> It hunts by everything except sight. Sound. Cold. The fear on your skin.
>
> All these years, I thought seeing was the gift. Seeing what others can't.
>
> Maybe I was just looking too hard. Close your eyes when you face it. It will anyway.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Morty_Spectrier_ChampionIntro:
	.string "Close your eyes. Go on. Listen.\p"
	.string "That's hooves. It's been circling us\n"
	.string "since you arrived, and it hasn't looked\l"
	.string "at either of us once.\p"
	.string "It doesn't need eyes. My whole life, I\n"
	.string "trained mine. ...Let's battle.$"

Nexus_Text_Morty_Spectrier_ChampionDefeat:
	.string "I saw every move. It didn't help.$"

Nexus_Text_Morty_Spectrier_ChampionAfter:
	.string "{SPEAKER NAME_MORTY}It hunts by everything except sight.\n"
	.string "Sound. Cold. The fear on your skin.\p"
	.string "All these years, I thought seeing was\n"
	.string "the gift. Seeing what others can't.\p"
	.string "Maybe I was just looking too hard.\n"
	.string "Close your eyes when you face it. It\l"
	.string "will anyway.$"
```

</details>

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mesmo registro da variação 1: a criatura pelo olhar do campeão, sem o nome da espécie. Ainda não estão no código.

**Variação 2 — o cavalo sem cavaleiro.** Lore de Galar: é a montaria do rei da coroa. Ele circula como montaria sem cavaleiro. Aceno ao fio **Liga de Kanto** (os corcéis procuram o **Will**, que tem o rei) — o homem mascarado que fala com reis, sem nome.

**Antes da luta**

> It isn't wild. Listen to how it circles. Tight. Careful. That's a steed without its rider.
>
> It's looking for someone. A king, I think. Someone with a crown and a mind stronger than its own.
>
> It certainly isn't looking for me. Let's battle.

**Derrota**

> Not me. Not you either, I suspect.

**Depois da luta**

> I tried to call it. Ghost to ghost. It didn't even slow down.
>
> Whoever rides it doesn't need to shout. It can hear a thought from across a field.
>
> If you ever meet a masked man who talks to kings, tell him his horse is waiting.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Morty_Spectrier_ChampionIntro2:
	.string "It isn't wild. Listen to how it circles.\n"
	.string "Tight. Careful. That's a steed without\l"
	.string "its rider.\p"
	.string "It's looking for someone. A king, I\n"
	.string "think. Someone with a crown and a mind\l"
	.string "stronger than its own.\p"
	.string "It certainly isn't looking for me. Let's\n"
	.string "battle.$"

Nexus_Text_Morty_Spectrier_ChampionDefeat2:
	.string "Not me. Not you either, I suspect.$"

Nexus_Text_Morty_Spectrier_ChampionAfter2:
	.string "{SPEAKER NAME_MORTY}I tried to call it. Ghost to ghost. It\n"
	.string "didn't even slow down.\p"
	.string "Whoever rides it doesn't need to shout.\n"
	.string "It can hear a thought from across a\l"
	.string "field.\p"
	.string "If you ever meet a masked man who talks\n"
	.string "to kings, tell him his horse is waiting.$"
```

</details>

**Variação 3 — o medo do lado de cá.** Fantasma não assusta o Morty. Algo que sabe onde você está sem olhar, sim: é o que ele é para os outros, e ele nunca gostou de estar deste lado. Grim Neigh vira imagem: cada medo que ela acha é uma rédea.

**Antes da luta**

> I'll confess something. I'm afraid of it.
>
> Ghosts don't scare me. Graveyards don't scare me. But something that knows where you are without looking…
>
> That's what I am to other people. I never liked being on this side. Let's battle.

**Derrota**

> So that's how my opponents feel.

**Depois da luta**

> It found my fear and pulled on it, like a rein.
>
> That's how it grows stronger. Every fear it finds. Every foe it drops.
>
> So don't be afraid of it. …Easy for me to say. Go.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Morty_Spectrier_ChampionIntro3:
	.string "I'll confess something. I'm afraid of\n"
	.string "it.\p"
	.string "Ghosts don't scare me. Graveyards\n"
	.string "don't scare me. But something that\l"
	.string "knows where you are without looking…\p"
	.string "That's what I am to other people. I\n"
	.string "never liked being on this side. Let's\l"
	.string "battle.$"

Nexus_Text_Morty_Spectrier_ChampionDefeat3:
	.string "So that's how my opponents feel.$"

Nexus_Text_Morty_Spectrier_ChampionAfter3:
	.string "{SPEAKER NAME_MORTY}It found my fear and pulled on it, like a\n"
	.string "rein.\p"
	.string "That's how it grows stronger. Every\n"
	.string "fear it finds. Every foe it drops.\p"
	.string "So don't be afraid of it. …Easy for me\n"
	.string "to say. Go.$"
```

</details>

Falante novo: `SP_NAME_MORTY` (ainda não existe em `include/constants/speaker_names.h`; skill `nomear-falante`).
