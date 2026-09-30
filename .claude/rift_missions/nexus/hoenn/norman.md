# Norman

**Região da ficha:** Hoenn

Aparece no checklist como:

- **Norman — Normal** (Hoenn · Líderes de Ginásio) — pai do protagonista e respeitado Líder de Petalburg.

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
| `OBJ_EVENT_GFX_NORMAN` | `graphics/object_events/pics/people/gym_leaders/norman.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_LEADER_NORMAN` | `graphics/trainers/front_pics/leader_norman.png` |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_NORMAN_2` | 786 | 0x812 | **sem time** (ID reservado, sem bloco no `.party`) | — (nenhum script chama) |
| `TRAINER_NORMAN_3` | 787 | 0x813 | **sem time** (ID reservado, sem bloco no `.party`) | — (nenhum script chama) |
| `TRAINER_NORMAN_4` | 788 | 0x814 | **sem time** (ID reservado, sem bloco no `.party`) | — (nenhum script chama) |
| `TRAINER_NORMAN_5` | 789 | 0x815 | **sem time** (ID reservado, sem bloco no `.party`) | `src/battle_dome.c` |

IDs aposentados na limpeza de treinadores (não reaproveitar sem necessidade): `TRAINER_UNUSED_454` (ex-`TRAINER_NORMAN_1`, 269).

### Time das Rift Missions

✅ **Implementado em 27/09/2026** (a proposta abaixo virou código): `TRAINER_NEXUS_NORMAN` = **1019** (flag de batalha `0x8FB`, limpa antes e depois de cada luta), bloco em `src/data/trainers.party`, nível pelo R2 (tabela em `src/data/nexus/trainers.h`). Fala genérica `Nexus_EventScript_Norman_Fight`; campeão: `Nexus_EventScript_Norman_Zarude_ChampionFight` (para Zarude), `Nexus_EventScript_Norman_Zamazenta_ChampionFight` (para Zamazenta). Tudo em `data/scripts/nexus.inc`, sem blackout, resultado em `VAR_TEMP_3`. Para testar: menu de debug → Rift Missions… → Nexus fights… → Norman.

📝 **Proposta de 27/09/2026, aguardando o autor.** `TRAINER_NEXUS_NORMAN`, campeão de Zamazenta e Zarude. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler).

Um time sobre criar e proteger. Lendário **Zamazenta**, o escudo que segurou a linha de Galar: o pai que fica na frente; semi-lendário **Zarude**, do bando da selva que expulsa estranhos, mas do qual saiu o Dada que criou uma criança humana como filho; Mega **Kangaskhan** (Normalite), a mãe com o filhote na bolsa (Parental Bond). Mais **Slaking** (o ás dele), **Vigoroth** e **Linoone** (o Zigzagoon que ele emprestou ao Wally, evoluído).

*Plano (Singles):* o Vigoroth de Eviolite abre com Taunt e Encore e trava quem quer se preparar; o Zamazenta fica de muralha com Iron Defense e Body Press; o Linoone faz Belly Drum (a Sitrus Berry com Gluttony devolve o HP) e limpa com Extreme Speed; o Slaking de Choice Band compensa o Truant saindo depois de cada golpe.

*Plano (Doubles, o formato de escrita):* Fake Out da Mega Kangaskhan no turno 1; o Wide Guard do Zamazenta anula os golpes de alvo duplo do adversário; o Jungle Healing do Zarude cura os dois do lado dele; o Linoone usa Protect enquanto o parceiro chama a atenção. Nenhum golpe do time acerta o parceiro.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Zamazenta | Leftovers | Dauntless Shield | Impish | Body Press, Iron Defense, Wide Guard, Crunch |
| Zarude | Life Orb | Leaf Guard | Jolly | Power Whip, Jungle Healing, Knock Off, U-turn |
| Kangaskhan | Normalite | Scrappy | Adamant | Fake Out, Double-Edge, Sucker Punch, Drain Punch |
| Slaking | Choice Band | Truant | Adamant | Double-Edge, High Horsepower, Knock Off, Fire Punch |
| Linoone | Sitrus Berry | Gluttony | Jolly | Belly Drum, Extreme Speed, Shadow Claw, Protect |
| Vigoroth | Eviolite | Vital Spirit | Jolly | Taunt, Knock Off, Encore, Body Slam |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>dev_scripts/nexus_validar_time.py</code>: espécie, item, habilidade, golpes e vagas)</summary>

```
=== TRAINER_NEXUS_NORMAN ===
Name: Norman
Class: Leader
Pic: Leader Norman
Gender: Male
Music: Male
Double Battle: Yes
AI: Smart Trainer

Zamazenta @ Leftovers
Impish Nature
Level: 100
Ability: Dauntless Shield
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Body Press
- Iron Defense
- Wide Guard
- Crunch

Zarude @ Life Orb
Jolly Nature
Level: 100
Ability: Leaf Guard
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Power Whip
- Jungle Healing
- Knock Off
- U-turn

Kangaskhan @ Normalite
Adamant Nature
Level: 100
Ability: Scrappy
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Fake Out
- Double-Edge
- Sucker Punch
- Drain Punch

Slaking @ Choice Band
Adamant Nature
Level: 100
Ability: Truant
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Double-Edge
- High Horsepower
- Knock Off
- Fire Punch

Linoone @ Sitrus Berry
Jolly Nature
Level: 100
Ability: Gluttony
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Belly Drum
- Extreme Speed
- Shadow Claw
- Protect

Vigoroth @ Eviolite
Jolly Nature
Level: 100
Ability: Vital Spirit
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Taunt
- Knock Off
- Encore
- Body Slam
```

</details>


### Lendário associado

#### Zamazenta

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_Zamazenta_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Zamazenta**. Norman é o campeão dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Norman, Líder de Petalburg, especialista em Normal, pai de família que passou anos mais no ginásio do que em casa.

**A criatura.** Zamazenta, o Guerreiro de Galar. Na lenda, ele e o Zacian defenderam Galar no Darkest Day; com o Rusted Shield assume a forma Crowned Shield. Luta defendendo, não atacando.

**O fragmento.** Um campo de batalha sob uma alvorada cinza, sem ninguém. Centenas de escudos cravados na lama, todos virados para o mesmo lado, ainda segurando a linha por soldados que foram para casa há muito tempo.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A battlefield under a gray dawn. No one was left on it.
>
> Hundreds of shields stood planted in the mud, all facing the same way, still holding the line for soldiers who had gone home long ago.

**Boss**

> One shield in the middle of the field moved.
>
> It was not a shield. It was a great wolf, and it had stood guard so long that the grass had grown around its paws.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** (o que volta é o fragmento no nível 1, [R17](../NEXUS_REGRAS.md))

> File L-889. The Shield.
>
> A field where every shield outlasted the one who carried it, and a father who only ever wanted to be the thing standing in front.
>
> What came back with you is young, and it already sits between you and the door. I did not teach it that.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Zamazenta_Arrival:
	.string "A battlefield under a gray dawn. No one\n"
	.string "was left on it.\p"
	.string "Hundreds of shields stood planted in\n"
	.string "the mud, all facing the same way, still\l"
	.string "holding the line for soldiers who had\l"
	.string "gone home long ago.$"

Nexus_Text_Zamazenta_Boss:
	.string "One shield in the middle of the field\n"
	.string "moved.\p"
	.string "It was not a shield. It was a great\n"
	.string "wolf, and it had stood guard so long\l"
	.string "that the grass had grown around its\l"
	.string "paws.$"

Nexus_Text_Zamazenta_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-889. The Shield.\p"
	.string "A field where every shield outlasted\n"
	.string "the one who carried it, and a father\l"
	.string "who only ever wanted to be the thing\l"
	.string "standing in front.\p"
	.string "What came back with you is young, and\n"
	.string "it already sits between you and the\l"
	.string "door. I did not teach it that.$"
```

</details>

#### Zarude

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_Zarude_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Zarude**. Norman é o campeão dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Norman, Líder de Petalburg, que emprestou o próprio Zigzagoon ao Wally, um menino doente de outra família, para ele pegar o primeiro Pokémon.

**A criatura.** Zarude (Sombrio/Grama) vive em bando no fundo da selva e expulsa sem piedade quem não é do bando. Um deles, o Dada, encontrou um bebê humano e o criou como filho.

**O fragmento.** Uma selva tão fechada que a luz chega verde. Cipós por toda parte, alguns se mexendo sozinhos: estendem-se na sua direção e recuam, como se alguém tivesse mandado não tocar.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A jungle so thick the daylight came through green.
>
> Vines hung everywhere, and some of them moved on their own, reaching toward you and pulling back, as if they had been told not to.

**Boss**

> The vines parted.
>
> Something stood there with its arms crossed, watching you the way a parent watches a stranger near a child.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** (o que volta é o fragmento no nível 1, [R17](../NEXUS_REGRAS.md))

> File L-893. The Rogue.
>
> A jungle that does not trust outsiders, and a Gym Leader who once lent his own Pokémon to a stranger's child.
>
> What came back with you grabbed my sleeve and would not let go. I have decided to count that as a good sign.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Zarude_Arrival:
	.string "A jungle so thick the daylight came\n"
	.string "through green.\p"
	.string "Vines hung everywhere, and some of\n"
	.string "them moved on their own, reaching\l"
	.string "toward you and pulling back, as if they\l"
	.string "had been told not to.$"

Nexus_Text_Zarude_Boss:
	.string "The vines parted.\p"
	.string "Something stood there with its arms\n"
	.string "crossed, watching you the way a parent\l"
	.string "watches a stranger near a child.$"

Nexus_Text_Zarude_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-893. The Rogue.\p"
	.string "A jungle that does not trust\n"
	.string "outsiders, and a Gym Leader who once\l"
	.string "lent his own Pokémon to a stranger's\l"
	.string "child.\p"
	.string "What came back with you grabbed my\n"
	.string "sleeve and would not let go. I have\l"
	.string "decided to count that as a good sign.$"
```

</details>


### Diálogo genérico

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Norman_Fight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Norman cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala dele mesmo, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

**Antes da luta**

> Hm. I don't know how I got here. But a Gym Leader doesn't need to know where he is to do his job.
>
> I'm Norman. In Petalburg, I teach one thing above all: strength is something you train, every single day.
>
> Show me what your days have been like.

**Derrota**

> Well done. Your Pokémon were trained with care.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Norman_Intro:
	.string "Hm. I don't know how I got here. But a\n"
	.string "Gym Leader doesn't need to know where\l"
	.string "he is to do his job.\p"
	.string "I'm Norman. In Petalburg, I teach one\n"
	.string "thing above all: strength is something\l"
	.string "you train, every single day.\p"
	.string "Show me what your days have been like.$"

Nexus_Text_Norman_Defeat:
	.string "Well done. Your Pokémon were trained\n"
	.string "with care.$"
```

</details>


#### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mais duas falas genéricas ([R16](../NEXUS_REGRAS.md)): falam só dele mesmo, sem o lugar nem a criatura do dia. A variação 1 é a de cima, que está no jogo; as novas não a repetem. Nada disto está no código.

**Variação 2** — o pai: o jogador lembra alguém, o filho que ele não vê há muito tempo (R21: pode ser outro filho, de outro fragmento).

**Antes da luta**

> You remind me of someone. The way you stand, maybe. Or the way you look at a door before you walk through it.
>
> My child used to do that. I haven't seen my child in a long time. Longer than I can explain.
>
> …Enough. Here, I'm a Gym Leader first. Let's begin.

**Derrota**

> You'd have made any parent proud. Remember that.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Norman_Intro2:
	.string "You remind me of someone. The way you\n"
	.string "stand, maybe. Or the way you look at a\l"
	.string "door before you walk through it.\p"
	.string "My child used to do that. I haven't\n"
	.string "seen my child in a long time. Longer than\l"
	.string "I can explain.\p"
	.string "…Enough. Here, I'm a Gym Leader first.\n"
	.string "Let's begin.$"

Nexus_Text_Norman_Defeat2:
	.string "You'd have made any parent proud.\n"
	.string "Remember that.$"
```

</details>

**Variação 3** — a regra dos quatro Badges de Petalburg e o Slaking que levou três anos para treinar, metade deitado: paciência como força, com humor seco.

**Antes da luta**

> In Petalburg, I don't battle anyone who hasn't earned four Badges. That's my rule.
>
> Here, no one checks. I suppose I'll have to trust you.
>
> My Slaking took three years to train. It spent half of them lying down. Patience is a strength too. Let me show you.

**Derrota**

> I lost. My Slaking is still lying down about it.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Norman_Intro3:
	.string "In Petalburg, I don't battle anyone who\n"
	.string "hasn't earned four Badges. That's my\l"
	.string "rule.\p"
	.string "Here, no one checks. I suppose I'll have\n"
	.string "to trust you.\p"
	.string "My Slaking took three years to train. It\n"
	.string "spent half of them lying down. Patience\l"
	.string "is a strength too. Let me show you.$"

Nexus_Text_Norman_Defeat3:
	.string "I lost. My Slaking is still lying down\n"
	.string "about it.$"
```

</details>

### Diálogo associado ao lendário

#### Zamazenta

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Norman_Zamazenta_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Norman é o **campeão**, a luta logo antes do Zamazenta. A fala é sobre a criatura, sem dizer o nome dela.

A primeira coisa que o Norman nota é que a criatura fica sempre na frente dos outros; nas histórias, ela venceu não atacando, mas não saindo do lugar. Ele tentou ser isso para a família, nem sempre bem: estava sempre no ginásio. A virada: um escudo só significa alguma coisa se há alguém atrás dele. Ele passou anos de frente, segurando a linha, e quando se virou o filho já tinha saído em jornada. O conselho: não tente atravessar a criatura, descubra o que ela protege.

**Antes da luta**

> It stands in front of the others. Always. That's what I noticed first.
>
> The old stories say it held the line when the sky went dark. It didn't win by attacking. It won by not moving.
>
> I've tried to be that for my family. Not always well. I was often at the Gym.
>
> …Let me see if my line holds against you!

**Derrota**

> My line broke. Fairly. Well done.

**Depois da luta**

> Here's what I understood, too late.
>
> A shield only means something if there's someone behind it.
>
> I spent years facing forward, holding the line. By the time I turned around, my child had already left on a journey.
>
> When you face it, don't try to break through. Find out what it's protecting.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Norman_Zamazenta_ChampionIntro:
	.string "It stands in front of the others.\n"
	.string "Always. That's what I noticed first.\p"
	.string "The old stories say it held the line\n"
	.string "when the sky went dark. It didn't win\l"
	.string "by attacking. It won by not moving.\p"
	.string "I've tried to be that for my family.\n"
	.string "Not always well. I was often at the Gym.\p"
	.string "…Let me see if my line holds against\n"
	.string "you!$"

Nexus_Text_Norman_Zamazenta_ChampionDefeat:
	.string "My line broke. Fairly. Well done.$"

Nexus_Text_Norman_Zamazenta_ChampionAfter:
	.string "{SPEAKER NAME_NORMAN}Here's what I understood, too late.\p"
	.string "A shield only means something if\n"
	.string "there's someone behind it.\p"
	.string "I spent years facing forward, holding\n"
	.string "the line. By the time I turned around,\l"
	.string "my child had already left on a journey.\p"
	.string "When you face it, don't try to break\n"
	.string "through. Find out what it's\l"
	.string "protecting.$"
```

</details>

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mais duas falas de campeão para Zamazenta: sobre a criatura, sem o nome da espécie. A variação 1 é a de cima, que está no jogo. Nada disto está no código.

**Variação 2** — a provocação: ele está sozinho. Na lenda havia a espada ao lado do escudo; aqui a espada sumiu, e o lobo segura a linha pelos dois. Acena para o fio Galar (a espada em mãos erradas).

**Antes da luta**

> It stands alone out there. That's what bothers me.
>
> In the stories it never fought by itself. There was another beside it, with a blade. The shield and the sword.
>
> Wherever the sword went, it isn't here. So that wolf has been holding the line for two.
>
> I know how that feels. Come on!

**Derrota**

> Held for two. Broke for one. Fair.

**Depois da luta**

> I asked it, in my way, where the other one went. It turned and looked at the horizon.
>
> Someone else is carrying that sword now, I think. Someone who shouldn't be.
>
> If you meet a young man with a blade that isn't his, tell him the shield is still waiting. And tell him to come home.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Norman_Zamazenta_ChampionIntro2:
	.string "It stands alone out there. That's what\n"
	.string "bothers me.\p"
	.string "In the stories it never fought by\n"
	.string "itself. There was another beside it,\l"
	.string "with a blade. The shield and the sword.\p"
	.string "Wherever the sword went, it isn't here.\n"
	.string "So that wolf has been holding the line\l"
	.string "for two.\p"
	.string "I know how that feels. Come on!$"

Nexus_Text_Norman_Zamazenta_ChampionDefeat2:
	.string "Held for two. Broke for one. Fair.$"

Nexus_Text_Norman_Zamazenta_ChampionAfter2:
	.string "{SPEAKER NAME_NORMAN}I asked it, in my way, where the other\n"
	.string "one went. It turned and looked at the\l"
	.string "horizon.\p"
	.string "Someone else is carrying that sword\n"
	.string "now, I think. Someone who shouldn't be.\p"
	.string "If you meet a young man with a blade\n"
	.string "that isn't his, tell him the shield is\l"
	.string "still waiting. And tell him to come home.$"
```

</details>

**Variação 3** — a lembrança com humor: a grama cresceu em volta das patas; a esposa dele disse que o piso do ginásio tinha a marca das botas dele. A parte difícil nunca foi ficar parado, foi sair da frente.

**Antes da luta**

> The grass has grown around its paws. That's how long it's been standing there.
>
> My wife once said the floor of my Gym had a dent in the shape of my boots. I laughed. Then I looked.
>
> There was a dent. …Let's see if I can still move!

**Derrota**

> Moved at last. Too late, but I moved.

**Depois da luta**

> Here's the funny part. It isn't tired. It could stand there another hundred years.
>
> Standing still was never the hard part for me, either. The hard part was stepping aside when I wasn't needed anymore.
>
> When you've beaten it, let it rest. Someone should tell it the war is over.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Norman_Zamazenta_ChampionIntro3:
	.string "The grass has grown around its paws.\n"
	.string "That's how long it's been standing\l"
	.string "there.\p"
	.string "My wife once said the floor of my Gym\n"
	.string "had a dent in the shape of my boots. I\l"
	.string "laughed. Then I looked.\p"
	.string "There was a dent. …Let's see if I can\n"
	.string "still move!$"

Nexus_Text_Norman_Zamazenta_ChampionDefeat3:
	.string "Moved at last. Too late, but I moved.$"

Nexus_Text_Norman_Zamazenta_ChampionAfter3:
	.string "{SPEAKER NAME_NORMAN}Here's the funny part. It isn't tired.\n"
	.string "It could stand there another hundred\l"
	.string "years.\p"
	.string "Standing still was never the hard part\n"
	.string "for me, either. The hard part was\l"
	.string "stepping aside when I wasn't needed\l"
	.string "anymore.\p"
	.string "When you've beaten it, let it rest.\n"
	.string "Someone should tell it the war is over.$"
```

</details>

#### Zarude

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Norman_Zarude_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Norman é o **campeão**, a luta logo antes do Zarude. A fala é sobre a criatura, sem dizer o nome dela.

O Norman ouviu a história do macaco da selva que não confia em ninguém de fora, mas que achou um bebê humano e o criou, alimentou e defendeu. Família não é só de quem você nasce, e ele aprendeu isso com um menino que não era dele. A virada é o orgulho que ele nunca conta: das vitórias todas, a de que mais se orgulha é ter visto o Wally, com as mãos tremendo, pegar o primeiro Ralts com o Zigzagoon emprestado.

**Antes da luta**

> The creatures in this jungle don't trust outsiders. They drive off anyone who isn't family.
>
> But I heard of one that found a human baby and raised it as its own. Fed it. Fought for it.
>
> Family isn't only who you're born to. I learned that from a boy who wasn't mine.
>
> Come. Let's see how you were raised!

**Derrota**

> Whoever raised you did good work.

**Depois da luta**

> There was a sickly boy in Petalburg. Wally. He wanted to catch a Pokémon before he moved away.
>
> I lent him my own Zigzagoon, and I watched him catch his first Ralts. His hands were shaking.
>
> I've won a great many battles. That moment is the one I'm proudest of.
>
> That creature would understand. Go on.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Norman_Zarude_ChampionIntro:
	.string "The creatures in this jungle don't\n"
	.string "trust outsiders. They drive off anyone\l"
	.string "who isn't family.\p"
	.string "But I heard of one that found a human\n"
	.string "baby and raised it as its own. Fed it.\l"
	.string "Fought for it.\p"
	.string "Family isn't only who you're born to. I\n"
	.string "learned that from a boy who wasn't\l"
	.string "mine.\p"
	.string "Come. Let's see how you were raised!$"

Nexus_Text_Norman_Zarude_ChampionDefeat:
	.string "Whoever raised you did good work.$"

Nexus_Text_Norman_Zarude_ChampionAfter:
	.string "{SPEAKER NAME_NORMAN}There was a sickly boy in Petalburg.\n"
	.string "Wally. He wanted to catch a Pokémon\l"
	.string "before he moved away.\p"
	.string "I lent him my own Zigzagoon, and I\n"
	.string "watched him catch his first Ralts. His\l"
	.string "hands were shaking.\p"
	.string "I've won a great many battles. That\n"
	.string "moment is the one I'm proudest of.\p"
	.string "That creature would understand. Go on.$"
```

</details>

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mais duas falas de campeão para Zarude: sobre a criatura, sem o nome da espécie. A variação 1 é a de cima, que está no jogo. Nada disto está no código.

**Variação 2** — o teste: os cipós se estendem e recuam, ele é o estranho sendo avaliado, como os desafiantes no ginásio dele. Depois, a postura de braços cruzados, que é a de um pai.

**Antes da luta**

> The vines keep reaching for me and pulling back. I think I'm being tested.
>
> In this jungle, you're family or you're gone. There's no middle.
>
> My Gym is the same. You earn your place, one Badge at a time. So. Earn yours.

**Derrota**

> You've earned it. The vines agree.

**Depois da luta**

> I've been watching the one that stands with its arms crossed. It never lets them hang at its sides.
>
> That's a parent's posture. Ready to grab, ready to push. Never sure which.
>
> I stood that way at every one of my child's battles. They thought I was stern. I was only holding still.
>
> Go. And no sudden moves near the little ones.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Norman_Zarude_ChampionIntro2:
	.string "The vines keep reaching for me and\n"
	.string "pulling back. I think I'm being tested.\p"
	.string "In this jungle, you're family or you're\n"
	.string "gone. There's no middle.\p"
	.string "My Gym is the same. You earn your place,\n"
	.string "one Badge at a time. So. Earn yours.$"

Nexus_Text_Norman_Zarude_ChampionDefeat2:
	.string "You've earned it. The vines agree.$"

Nexus_Text_Norman_Zarude_ChampionAfter2:
	.string "{SPEAKER NAME_NORMAN}I've been watching the one that stands\n"
	.string "with its arms crossed. It never lets\l"
	.string "them hang at its sides.\p"
	.string "That's a parent's posture. Ready to\n"
	.string "grab, ready to push. Never sure which.\p"
	.string "I stood that way at every one of my\n"
	.string "child's battles. They thought I was\l"
	.string "stern. I was only holding still.\p"
	.string "Go. And no sudden moves near the little\n"
	.string "ones.$"
```

</details>

**Variação 3** — a dúvida: no filme, o menino criado pelo bando sai da selva para achar os seus, e a criatura fica na beira das árvores sem seguir. Norman já ficou na beira de uma cidade assim.

**Antes da luta**

> In the story, the child it raised grew up and walked out of the jungle to find his own kind.
>
> The creature let him go. It stood at the edge of the trees and didn't follow.
>
> I've stood at the edge of a town like that. …Let's not talk about it. Let's battle.

**Derrota**

> Good. You don't hold back either.

**Depois da luta**

> The child came back, you know. In the story. Not to stay. Just to say he was fine.
>
> That was enough for it. I've been trying to decide if it would be enough for me.
>
> …It would. Go on. If you see my child out there, tell them I said so.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Norman_Zarude_ChampionIntro3:
	.string "In the story, the child it raised grew up\n"
	.string "and walked out of the jungle to find his\l"
	.string "own kind.\p"
	.string "The creature let him go. It stood at the\n"
	.string "edge of the trees and didn't follow.\p"
	.string "I've stood at the edge of a town like\n"
	.string "that. …Let's not talk about it. Let's\l"
	.string "battle.$"

Nexus_Text_Norman_Zarude_ChampionDefeat3:
	.string "Good. You don't hold back either.$"

Nexus_Text_Norman_Zarude_ChampionAfter3:
	.string "{SPEAKER NAME_NORMAN}The child came back, you know. In the\n"
	.string "story. Not to stay. Just to say he was\l"
	.string "fine.\p"
	.string "That was enough for it. I've been\n"
	.string "trying to decide if it would be enough\l"
	.string "for me.\p"
	.string "…It would. Go on. If you see my child out\n"
	.string "there, tell them I said so.$"
```

</details>

Falante novo: `SP_NAME_NORMAN` (não existe ainda em `include/constants/speaker_names.h`).
