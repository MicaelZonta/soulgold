# Norman

**Região da ficha:** Hoenn

Aparece no checklist como:

- **Norman — Normal** (Hoenn · Líderes de Ginásio) — pai do protagonista e respeitado Líder de Petalburg.

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


### Diálogo associado ao lendário

#### Zamazenta

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

#### Zarude

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

Falante novo: `SP_NAME_NORMAN` (não existe ainda em `include/constants/speaker_names.h`).
