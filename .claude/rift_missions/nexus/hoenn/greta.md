# Greta

**Região da ficha:** Hoenn

Aparece no checklist como:

- **Greta — Battle Arena** (Hoenn · Battle Frontier — Frontier Brains) — avalia mente, habilidade e corpo em combates curtos.

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
| `OBJ_EVENT_GFX_GRETA` | `graphics/object_events/pics/people/frontier_brains/greta.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_ARENA_TYCOON_GRETA` | `graphics/trainers/front_pics/arena_tycoon_greta.png` |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

Nenhuma. Ao criar, seguir a skill `adicionar-batalha-npc` (e `alocar-flag` se precisar de flag nova).

### Time das Rift Missions

✅ **Implementado em 27/09/2026** (a proposta abaixo virou código): `TRAINER_NEXUS_GRETA` = **1029** (flag de batalha `0x905`, limpa antes e depois de cada luta), bloco em `src/data/trainers.party`, nível pelo R2 (tabela em `src/data/nexus/trainers.h`). Fala genérica `Nexus_EventScript_Greta_Fight`; campeão: `Nexus_EventScript_Greta_Koraidon_ChampionFight` (para Koraidon), `Nexus_EventScript_Greta_GreatTusk_ChampionFight` (para Great Tusk). Tudo em `data/scripts/nexus.inc`, sem blackout, resultado em `VAR_TEMP_3`. Para testar: menu de debug → Rift Missions… → Nexus fights… → Greta.

📝 **Proposta de 27/09/2026, aguardando o autor.** `TRAINER_NEXUS_GRETA`, campeão de Koraidon e Great Tusk. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler).

Lendário **Koraidon**, semi-lendário **Great Tusk** (os dois vindos do passado), Mega **Heracross** (Bugtite), o ás da Greta em Emerald, ao lado do Umbreon. A Battle Arena julga **Mind, Skill e Body** em três turnos; este time é o lado *Body* levado ao extremo: bichos antigos que batem forte e cedo. O Hitmontop é o lutador de arena clássico; o Gliscor fecha a fraqueza a Flying e Psychic dos lutadores. *Plano:* **sol antigo e pressão desde o primeiro turno.** O Orichalcum Pulse do Koraidon liga o sol, que acende o Protosynthesis do Great Tusk (e o Booster Energy garante mesmo sem sol).

*Plano (Singles):* Gliscor arma Stealth Rock e faz pivô de U-turn, Great Tusk tira hazards com Rapid Spin, o Umbreon absorve golpe especial e passa Wish, e o Koraidon e a Mega Heracross (Skill Link) limpam; o Hitmontop entra contra físicos com Intimidate. *Plano (Doubles):* Fake Out do Hitmontop e Intimidate na entrada, Wide Guard contra spread; Snarl do Umbreon enfraquece os dois atacantes especiais; o Koraidon bate de Collision Course com o sol no lugar. Nenhum golpe do time acerta o parceiro (Headlong Rush e Close Combat são de alvo único).

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Koraidon | Life Orb | Orichalcum Pulse | Jolly | Collision Course, Flare Blitz, Dragon Claw, U-turn |
| Great Tusk | Booster Energy | Protosynthesis | Jolly | Headlong Rush, Close Combat, Ice Spinner, Rapid Spin |
| Heracross | Bugtite | Guts | Jolly | Pin Missile, Close Combat, Rock Blast, Knock Off |
| Umbreon | Leftovers | Inner Focus | Calm | Foul Play, Snarl, Wish, Protect |
| Hitmontop | Sitrus Berry | Intimidate | Impish | Fake Out, Close Combat, Sucker Punch, Wide Guard |
| Gliscor | Toxic Orb | Poison Heal | Impish | Stealth Rock, Knock Off, U-turn, Protect |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>dev_scripts/nexus_validar_time.py</code>: espécie, item, habilidade, learnsets e vagas)</summary>

```
=== TRAINER_NEXUS_GRETA ===
Name: Greta
Class: Arena Tycoon
Pic: Arena Tycoon Greta
Gender: Female
Music: Female
Double Battle: No
AI: Smart Trainer

Koraidon @ Life Orb
Jolly Nature
Level: 100
Ability: Orichalcum Pulse
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Collision Course
- Flare Blitz
- Dragon Claw
- U-turn

Great Tusk @ Booster Energy
Jolly Nature
Level: 100
Ability: Protosynthesis
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Headlong Rush
- Close Combat
- Ice Spinner
- Rapid Spin

Heracross @ Bugtite
Jolly Nature
Level: 100
Ability: Guts
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Pin Missile
- Close Combat
- Rock Blast
- Knock Off

Umbreon @ Leftovers
Calm Nature
Level: 100
Ability: Inner Focus
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Foul Play
- Snarl
- Wish
- Protect

Hitmontop @ Sitrus Berry
Impish Nature
Level: 100
Ability: Intimidate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Fake Out
- Close Combat
- Sucker Punch
- Wide Guard

Gliscor @ Toxic Orb
Impish Nature
Level: 100
Ability: Poison Heal
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Stealth Rock
- Knock Off
- U-turn
- Protect
```

</details>


### Lendário associado

#### Koraidon

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_Koraidon_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Koraidon**. Greta é a campeã dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Greta, Arena Tycoon da Battle Frontier de Hoenn, alegre e direta, que julga batalhas em três turnos: Mind, Skill e Body.

**A criatura.** Paradoxo do passado (Scarlet), trazido pela máquina do tempo de Area Zero. O Orichalcum Pulse acende um sol forte ao entrar e aquece o sangue antigo dele; na região de Paldea foi montaria de um estudante e adorava sanduíche.

**O fragmento.** Um vale sob um sol que não se põe, mais perto e mais vermelho que o nosso. O chão é quente demais para ficar parado, e as samambaias são da altura de casas. No meio do vale, uma pedra redonda tem marcas de dentes.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A valley under a sun that did not set. It hung closer than ours, and redder.
>
> The ground was too warm to stand still on. The ferns were as tall as houses.
>
> In the middle of the valley, a round stone had been chewed on.

**Boss**

> The sun got brighter, and something roared back at it.
>
> It came down the valley on all fours, fast, like it had been waiting a very long time for someone to race.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md))

> File L-1007. The Old Sun.
>
> A valley that is always noon, and a woman who scores everything in three turns.
>
> What came back with you is little, hot to the touch, and it already tried to eat my notebook. I am giving it a very high score for Body.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Koraidon_Arrival:
	.string "A valley under a sun that did not set.\n"
	.string "It hung closer than ours, and redder.\p"
	.string "The ground was too warm to stand still\n"
	.string "on. The ferns were as tall as houses.\p"
	.string "In the middle of the valley, a round\n"
	.string "stone had been chewed on.$"

Nexus_Text_Koraidon_Boss:
	.string "The sun got brighter, and something\n"
	.string "roared back at it.\p"
	.string "It came down the valley on all fours,\n"
	.string "fast, like it had been waiting a very\l"
	.string "long time for someone to race.$"

Nexus_Text_Koraidon_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-1007. The Old Sun.\p"
	.string "A valley that is always noon, and a\n"
	.string "woman who scores everything in three\l"
	.string "turns.\p"
	.string "What came back with you is little, hot\n"
	.string "to the touch, and it already tried to\l"
	.string "eat my notebook. I am giving it a very\l"
	.string "high score for Body.$"
```

</details>


#### Great Tusk

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_GreatTusk_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Great Tusk**. Greta é a campeã dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Greta, a juíza da Arena, para quem Body é um terço da nota e nunca a nota inteira.

**A criatura.** Paradoxo do passado, descrito no Scarlet Book como um Donphan antigo e gigante. Dizem que enfrentava Pokémon enormes com as presas e que andava em bando; o Protosynthesis dele acorda no sol.

**O fragmento.** Uma arena de terra batida sem arquibancada, cercada por presas enormes fincadas no chão como estacas. Cada presa tem uma marca de choque, e nenhuma de desistência.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> An arena of packed earth, with no seats around it.
>
> Huge tusks had been driven into the ground all around it, like the posts of a fence.
>
> Every tusk was cracked from a hit. None of them had been pulled out.

**Boss**

> The earth shook in a rhythm, like footsteps, or a drum.
>
> Something shaggy and enormous lowered its head at the edge of the arena and started to roll.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md))

> File L-984. Ancient Tusk.
>
> An arena with no seats, and a judge who finally had something to judge.
>
> What came back with you is smaller than its tusks should be. It headbutted my chair. Twice. The chair lost.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_GreatTusk_Arrival:
	.string "An arena of packed earth, with no\n"
	.string "seats around it.\p"
	.string "Huge tusks had been driven into the\n"
	.string "ground all around it, like the posts of\l"
	.string "a fence.\p"
	.string "Every tusk was cracked from a hit.\n"
	.string "None of them had been pulled out.$"

Nexus_Text_GreatTusk_Boss:
	.string "The earth shook in a rhythm, like\n"
	.string "footsteps, or a drum.\p"
	.string "Something shaggy and enormous lowered\n"
	.string "its head at the edge of the arena and\l"
	.string "started to roll.$"

Nexus_Text_GreatTusk_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-984. Ancient Tusk.\p"
	.string "An arena with no seats, and a judge who\n"
	.string "finally had something to judge.\p"
	.string "What came back with you is smaller than\n"
	.string "its tusks should be. It headbutted my\l"
	.string "chair. Twice. The chair lost.$"
```

</details>


### Diálogo genérico

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Greta_Fight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Greta cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala dela mesma, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

**Antes da luta**

> Hey there! Greta, Arena Tycoon! You know how my Arena works? Three turns, and I judge you on Mind, Skill and Body.
>
> I've been in here a while now, and nobody's come to judge me. So I've been judging myself.
>
> Mind: kind of lost. Skill: just fine. Body: raring to go! Let's make it three turns, champ!

**Derrota**

> Mind, Skill, Body… OK, OK, you win on all three. No arguing with the judges!

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Greta_Intro:
	.string "Hey there! Greta, Arena Tycoon! You\n"
	.string "know how my Arena works? Three turns,\l"
	.string "and I judge you on Mind, Skill and Body.\p"
	.string "I've been in here a while now, and\n"
	.string "nobody's come to judge me. So I've\l"
	.string "been judging myself.\p"
	.string "Mind: kind of lost. Skill: just fine.\n"
	.string "Body: raring to go! Let's make it three\l"
	.string "turns, champ!$"

Nexus_Text_Greta_Defeat:
	.string "Mind, Skill, Body… OK, OK, you win on all\n"
	.string "three. No arguing with the judges!$"
```

</details>


#### Variações 2 e 3 (📝 proposta de 30/09/2026)

A variação 1 é a Greta julgando a si mesma porque ninguém veio julgá-la. Na 2, uma lembrança engraçada: a primeira luta dela na Arena, perdida nos pontos, e o choro que virou carreira de juíza. Na 3, o R21: no fragmento dela a Arena nunca foi construída (a ilha ficou vazia; ver o diário), então ela carrega as regras na cabeça e o Umbreon, ás dela em Emerald, marca os pontos.

**Variação 2 — a primeira derrota nos pontos**

**Antes da luta**

> Hiya! Greta! Quick question: you ever lose a battle on points?
>
> It's the worst! Nobody fainted, you're still standing, and three judges go, “Sorry, champ, not today.”
>
> I lost my first ever Arena match like that. Cried for an hour. Then I went and became the judge!
>
> So no crying today, OK? Let's go!

**Derrota**

> Aaand that's a points loss. …I'm fine! Totally fine! Great battle!

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Greta_Intro2:
	.string "Hiya! Greta! Quick question: you ever\n"
	.string "lose a battle on points?\p"
	.string "It's the worst! Nobody fainted, you're\n"
	.string "still standing, and three judges go,\l"
	.string "“Sorry, champ, not today.”\p"
	.string "I lost my first ever Arena match like\n"
	.string "that. Cried for an hour. Then I went and\l"
	.string "became the judge!\p"
	.string "So no crying today, OK? Let's go!$"

Nexus_Text_Greta_Defeat2:
	.string "Aaand that's a points loss. …I'm fine!\n"
	.string "Totally fine! Great battle!$"
```

</details>

**Variação 3 — a Arena que nunca existiu**

**Antes da luta**

> OK, heads up, champ. My Umbreon keeps score now. Somebody has to.
>
> Where I'm from, the Arena never got built. The island just stayed empty. No judges, no scoreboard.
>
> So I carry the rules around in my head. Mind, Skill, Body. Works anywhere!
>
> Umbreon, you ready? Three turns!

**Derrota**

> Umbreon says you win. I'd argue, but it's got a very serious face.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Greta_Intro3:
	.string "OK, heads up, champ. My Umbreon keeps\n"
	.string "score now. Somebody has to.\p"
	.string "Where I'm from, the Arena never got\n"
	.string "built. The island just stayed empty. No\l"
	.string "judges, no scoreboard.\p"
	.string "So I carry the rules around in my head.\n"
	.string "Mind, Skill, Body. Works anywhere!\p"
	.string "Umbreon, you ready? Three turns!$"

Nexus_Text_Greta_Defeat3:
	.string "Umbreon says you win. I'd argue, but\n"
	.string "it's got a very serious face.$"
```

</details>


### Diálogo associado ao lendário

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Greta é a campeã, a luta logo antes do lendário do dia. Um registro por lendário; a fala é sobre a criatura, sem dizer o nome dela.

#### Koraidon

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Greta_Koraidon_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

A Greta julga todo mundo em três turnos: Mind, Skill, Body. Ela tenta julgar a criatura do vale e o placar sai estranho: Body fora da escala, Skill bruto, e Mind… ela só queria correr e comer. A virada é que a Greta, que passou a vida medindo, descobre que o que mais gostou nele não entra na tabela: ele não luta para vencer, luta porque é divertido. E ela lembra que a Arena começou assim para ela também.

**Antes da luta**

> Hey! Did you see that big guy down in the valley? I tried to judge it. Three turns, like always.
>
> Body: off the charts! Skill: raw, but wow. Mind: …it wanted to race me, and then it tried to eat a rock.
>
> I didn't have a column for that. I just laughed.
>
> Come on, champ! Let's see how your three turns stack up!

**Derrota**

> Ha! Full marks. I'd give you a trophy if I had one in here.

**Depois da luta**

> You know what I figured out, watching that thing?
>
> It doesn't fight to win. It fights because it's fun. It just wants somebody fast enough to keep up.
>
> That's how I started too, before all the scoring. I kinda forgot.
>
> Go race it! And hey, if it's hungry, don't let it eat your bag!

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Greta_Koraidon_ChampionIntro:
	.string "Hey! Did you see that big guy down in\n"
	.string "the valley? I tried to judge it. Three\l"
	.string "turns, like always.\p"
	.string "Body: off the charts! Skill: raw, but\n"
	.string "wow. Mind: …it wanted to race me, and\l"
	.string "then it tried to eat a rock.\p"
	.string "I didn't have a column for that. I just\n"
	.string "laughed.\p"
	.string "Come on, champ! Let's see how your\n"
	.string "three turns stack up!$"

Nexus_Text_Greta_Koraidon_ChampionDefeat:
	.string "Ha! Full marks. I'd give you a trophy if\n"
	.string "I had one in here.$"

Nexus_Text_Greta_Koraidon_ChampionAfter:
	.string "{SPEAKER NAME_GRETA}You know what I figured out, watching\n"
	.string "that thing?\p"
	.string "It doesn't fight to win. It fights\n"
	.string "because it's fun. It just wants\l"
	.string "somebody fast enough to keep up.\p"
	.string "That's how I started too, before all\n"
	.string "the scoring. I kinda forgot.\p"
	.string "Go race it! And hey, if it's hungry,\n"
	.string "don't let it eat your bag!$"
```

</details>

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

Na variação 1 a Greta descobre que a criatura luta porque é divertido. Na 2, o humor do sanduíche (ele comia sanduíche em Paldea): comeu o prato e a ficha de nota, e o sol esquenta quando ele está feliz; é clima com pernas. Na 3, a perda: uma mulher de jaleco, cabelo solto e colar de dentes (a Sada, nunca nomeada) abriu uma porta para o mundo antigo, passou e não voltou; ele espera na porta todo dia.

**Variação 2 — o sanduíche**

**Antes da luta**

> OK, true story. I made that big guy a sandwich. Ham, tomato, a lot of mustard.
>
> It ate the sandwich, the plate, and most of my scorecard.
>
> Then it lay down in the sun and purred like an engine. Body: ten. Manners: we're working on it.
>
> Your turn, champ! I'm hungry for a good battle!

**Derrota**

> Ha! Well fed on that one. Thanks, champ!

**Depois da luta**

> You know what I noticed? When it's full and happy, the sun gets warmer.
>
> When it's sad, the whole valley goes gray. It's not a creature, it's weather with legs.
>
> Somebody left it here all alone. You shouldn't leave weather alone. It gets moody.
>
> Go on! And bring a snack. Trust me on this one.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Greta_Koraidon_ChampionIntro2:
	.string "OK, true story. I made that big guy a\n"
	.string "sandwich. Ham, tomato, a lot of mustard.\p"
	.string "It ate the sandwich, the plate, and\n"
	.string "most of my scorecard.\p"
	.string "Then it lay down in the sun and purred\n"
	.string "like an engine. Body: ten. Manners: we're\l"
	.string "working on it.\p"
	.string "Your turn, champ! I'm hungry for a good\n"
	.string "battle!$"

Nexus_Text_Greta_Koraidon_ChampionDefeat2:
	.string "Ha! Well fed on that one. Thanks, champ!$"

Nexus_Text_Greta_Koraidon_ChampionAfter2:
	.string "{SPEAKER NAME_GRETA}You know what I noticed? When it's full\n"
	.string "and happy, the sun gets warmer.\p"
	.string "When it's sad, the whole valley goes\n"
	.string "gray. It's not a creature, it's weather\l"
	.string "with legs.\p"
	.string "Somebody left it here all alone. You\n"
	.string "shouldn't leave weather alone. It gets\l"
	.string "moody.\p"
	.string "Go on! And bring a snack. Trust me on\n"
	.string "this one.$"
```

</details>

**Variação 3 — a porta que ficou aberta**

**Antes da luta**

> Champ, can I ask you something? You think something from way back can ever really belong in now?
>
> That big guy is from before anybody. Before people, before rules, before scoring.
>
> Someone reached back and pulled it forward. Then they just… stopped reaching.
>
> OK! Too gloomy! Three turns, cheer me up!

**Derrota**

> There we go. Cheered up. Full marks.

**Depois da luta**

> There's a woman in a lab coat I keep almost remembering. Wild hair. A necklace made of teeth.
>
> She built a door to the old world and walked through it. The door's still open. She's not back.
>
> That big guy waits by it every day. Just in case.
>
> Go on. If it races you, let it win the first time. It's been waiting a while.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Greta_Koraidon_ChampionIntro3:
	.string "Champ, can I ask you something? You\n"
	.string "think something from way back can ever\l"
	.string "really belong in now?\p"
	.string "That big guy is from before anybody.\n"
	.string "Before people, before rules, before\l"
	.string "scoring.\p"
	.string "Someone reached back and pulled it\n"
	.string "forward. Then they just… stopped\l"
	.string "reaching.\p"
	.string "OK! Too gloomy! Three turns, cheer me\n"
	.string "up!$"

Nexus_Text_Greta_Koraidon_ChampionDefeat3:
	.string "There we go. Cheered up. Full marks.$"

Nexus_Text_Greta_Koraidon_ChampionAfter3:
	.string "{SPEAKER NAME_GRETA}There's a woman in a lab coat I keep\n"
	.string "almost remembering. Wild hair. A\l"
	.string "necklace made of teeth.\p"
	.string "She built a door to the old world and\n"
	.string "walked through it. The door's still\l"
	.string "open. She's not back.\p"
	.string "That big guy waits by it every day. Just\n"
	.string "in case.\p"
	.string "Go on. If it races you, let it win the\n"
	.string "first time. It's been waiting a while.$"
```

</details>


#### Great Tusk

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Greta_GreatTusk_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

A Greta foi ver a criatura da arena e deu a nota que ela nunca tinha dado: Body perfeito, e nada mais. Ela bate, ela rola, ela bate de novo. A virada: a Greta sempre disse que o Body sozinho perde na Arena, porque o julgamento pede os três. Ali, sem juiz nenhum, o Body sozinho venceu tudo o que havia, e sobrou uma arena vazia de estacas quebradas. Ela entende por que a Arena julga três coisas: não é para premiar o forte, é para que sobre alguém depois.

**Antes da luta**

> OK, champ, straight talk. There's a big shaggy thing out there that's all Body. Nothing else.
>
> At my Arena, all Body loses. The judges want Mind and Skill too. That's the rule!
>
> Out here, there were no judges. It just kept winning. Look at all those broken tusks.
>
> So give me three good turns. I want to remember why the rule's there.

**Derrota**

> Yes! That's it! That's what Mind and Skill look like!

**Depois da luta**

> You know why my Arena judges three things? I used to think it was to be fair.
>
> It's not. It's so there's somebody left standing after. Nobody fights all Body for long.
>
> That thing out there never had a judge. It won every fight, and now it's alone in a ring full of broken fence posts.
>
> Go on. Be the judge it never had.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Greta_GreatTusk_ChampionIntro:
	.string "OK, champ, straight talk. There's a big\n"
	.string "shaggy thing out there that's all\l"
	.string "Body. Nothing else.\p"
	.string "At my Arena, all Body loses. The judges\n"
	.string "want Mind and Skill too. That's the\l"
	.string "rule!\p"
	.string "Out here, there were no judges. It just\n"
	.string "kept winning. Look at all those broken\l"
	.string "tusks.\p"
	.string "So give me three good turns. I want to\n"
	.string "remember why the rule's there.$"

Nexus_Text_Greta_GreatTusk_ChampionDefeat:
	.string "Yes! That's it! That's what Mind and\n"
	.string "Skill look like!$"

Nexus_Text_Greta_GreatTusk_ChampionAfter:
	.string "{SPEAKER NAME_GRETA}You know why my Arena judges three\n"
	.string "things? I used to think it was to be\l"
	.string "fair.\p"
	.string "It's not. It's so there's somebody\n"
	.string "left standing after. Nobody fights all\l"
	.string "Body for long.\p"
	.string "That thing out there never had a\n"
	.string "judge. It won every fight, and now it's\l"
	.string "alone in a ring full of broken fence\l"
	.string "posts.\p"
	.string "Go on. Be the judge it never had.$"
```

</details>

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

Na variação 1 o Body sozinho venceu tudo e sobrou uma arena vazia. Na 2 a Greta muda a nota: a criatura olha para trás esperando o bando (o Scarlet Book diz que andavam em bando), e lembrar é Mind; e quando ela perdeu, ele parou e não terminou o serviço, então ganhou o primeiro ponto de Skill, escrito numa presa quebrada. Na 3, a confissão: a Greta também é toda Body (o Heracross que o diga), achou aquilo divertido e ficou com vergonha; ela teve juízes que diziam "chega", a criatura não.

**Variação 2 — o bando, e o primeiro ponto**

**Antes da luta**

> Straight talk again, champ. I found out those big shaggy things used to travel in herds.
>
> Now there's only one. It keeps turning around, like it's waiting for the others to catch up.
>
> That's not Body. That's Mind. It remembers. I had to change its score!
>
> Let's see if you can make me change yours!

**Derrota**

> Changed! Upgraded! You earned it!

**Depois da luta**

> Know what that thing did when I lost to it? It walked away. It didn't finish me.
>
> All Body would've kept going. It stopped. Looked back at me. And then it just… stopped.
>
> So I gave it a point for Skill. First one ever. I wrote it on one of those broken tusks.
>
> Go on. Maybe you can get it all the way to three.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Greta_GreatTusk_ChampionIntro2:
	.string "Straight talk again, champ. I found out\n"
	.string "those big shaggy things used to travel\l"
	.string "in herds.\p"
	.string "Now there's only one. It keeps turning\n"
	.string "around, like it's waiting for the others\l"
	.string "to catch up.\p"
	.string "That's not Body. That's Mind. It\n"
	.string "remembers. I had to change its score!\p"
	.string "Let's see if you can make me change\n"
	.string "yours!$"

Nexus_Text_Greta_GreatTusk_ChampionDefeat2:
	.string "Changed! Upgraded! You earned it!$"

Nexus_Text_Greta_GreatTusk_ChampionAfter2:
	.string "{SPEAKER NAME_GRETA}Know what that thing did when I lost to\n"
	.string "it? It walked away. It didn't finish me.\p"
	.string "All Body would've kept going. It\n"
	.string "stopped. Looked back at me. And then it\l"
	.string "just… stopped.\p"
	.string "So I gave it a point for Skill. First one\n"
	.string "ever. I wrote it on one of those broken\l"
	.string "tusks.\p"
	.string "Go on. Maybe you can get it all the way\n"
	.string "to three.$"
```

</details>

**Variação 3 — a juíza que também é só Body**

**Antes da luta**

> Confession time, champ. I'm a judge, but I'm all Body. Always have been. Just ask my Heracross.
>
> When I saw that thing out there smashing tusk after tusk, I didn't think, “What a brute.”
>
> I thought, “That looks fun!” Then I felt bad about it!
>
> So keep me honest, OK? Three turns!

**Derrota**

> Honest! Kept! You're a good influence, champ.

**Depois da luta**

> Here's the thing about hitting hard. It feels great. Every time. That's the problem.
>
> That shaggy guy never had anybody tell it when to stop. So it never did.
>
> I had judges. A whole Arena going, “OK, Greta, that's three turns.” Lucky me.
>
> Go on. Tell it when to stop. Nicely.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Greta_GreatTusk_ChampionIntro3:
	.string "Confession time, champ. I'm a judge, but\n"
	.string "I'm all Body. Always have been. Just ask\l"
	.string "my Heracross.\p"
	.string "When I saw that thing out there\n"
	.string "smashing tusk after tusk, I didn't\l"
	.string "think, “What a brute.”\p"
	.string "I thought, “That looks fun!” Then I\n"
	.string "felt bad about it!\p"
	.string "So keep me honest, OK? Three turns!$"

Nexus_Text_Greta_GreatTusk_ChampionDefeat3:
	.string "Honest! Kept! You're a good influence,\n"
	.string "champ.$"

Nexus_Text_Greta_GreatTusk_ChampionAfter3:
	.string "{SPEAKER NAME_GRETA}Here's the thing about hitting hard. It\n"
	.string "feels great. Every time. That's the\l"
	.string "problem.\p"
	.string "That shaggy guy never had anybody tell\n"
	.string "it when to stop. So it never did.\p"
	.string "I had judges. A whole Arena going, “OK,\n"
	.string "Greta, that's three turns.” Lucky me.\p"
	.string "Go on. Tell it when to stop. Nicely.$"
```

</details>


Falante novo: `SP_NAME_GRETA` (não existe em `include/constants/speaker_names.h`).
