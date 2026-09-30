# Lillie

**Região da ficha:** Alola

Aparece no checklist como:

- **Lillie** (Alola · Outros notáveis) — filha de Lusamine e protagonista do arco de Alola do hack.

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
| `OBJ_EVENT_GFX_LILLIE` | `graphics/object_events/pics/people/special/lillie.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_LILLIE` | `graphics/trainers/front_pics/lillie.png` |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

> **Atenção:** Personagem central do arco das Rift Missions; `TRAINER_LILLIE_POSTGAME` é o time mais forte já escrito.

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_LILLIE` | 965 | 0x8C5 | Vulpix Alola Lv7 | `Route30_MrPokemonsHouse` |
| `TRAINER_LILLIE_GOLDENROD` | 968 | 0x8C8 | Clefairy Lv28, Ribombee Lv29, Comfey Lv28, Vulpix Alola Lv29 | `GoldenrodCity_FlowerShop` |
| `TRAINER_LILLIE_DRAGONS_DEN` | 970 | 0x8CA | Ninetales Alola Lv62, Ribombee Lv59, Clefable Lv60, Lilligant Lv59, Milotic Lv61, Comfey Lv60 | `DragonsDen_Shrine` |
| `TRAINER_LILLIE_POSTGAME` | 973 | 0x8CD | Clefable Lv76, Comfey Lv76, Ribombee Lv77, Primarina Lv77, Togekiss Lv78, Ninetales Alola Lv78 | `CherrygroveCity` |

### Time das Rift Missions

✅ **Implementado em 27/09/2026** (a proposta abaixo virou código): `TRAINER_NEXUS_LILLIE` = **1042** (flag de batalha `0x912`, limpa antes e depois de cada luta), bloco em `src/data/trainers.party`, nível pelo R2 (tabela em `src/data/nexus/trainers.h`). Fala genérica `Nexus_EventScript_Lillie_Fight`; campeão: `Nexus_EventScript_Lillie_Lunala_ChampionFight` (para Lunala), `Nexus_EventScript_Lillie_TapuLele_ChampionFight` (para Tapu Lele). Tudo em `data/scripts/nexus.inc`, sem blackout, resultado em `VAR_TEMP_3`. Para testar: menu de debug → Rift Missions… → Nexus fights… → Lillie.

📝 **Proposta de 27/09/2026, aguardando o autor.** `TRAINER_NEXUS_LILLIE`, campeã de Lunala e Tapu Lele. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler).

Lendário **Lunala**: pode ser o **Nebby**. O Nexus é outro universo, tempo ou dimensão; esta Lillie vem de um lugar onde o Cosmog que ela carregou na bolsa cresceu ao lado dela e virou a lua. Pode ser que nada do que o jogador viveu tenha acontecido lá, ou tudo; o texto não decide. Ela chama o **dela** de Nebby, nunca o do jogador (design §3). Semi-lendário **Tapu Lele**, a guardiã que cura, a outra luta de campeã dela. Mega **Primarina** (Bondstone), do time de pós-game dela: a pedra de laço combina com quem só aprendeu a lutar junto de alguém. Mais **Ninetales de Alola** (a parceira, presença permanente, design §3; o mesmo Vulpix da Route 30), Ribombee e Clefable, todos do `TRAINER_LILLIE_POSTGAME`. Time de Fada e Psíquico, que observa antes de bater.

*Plano (Singles):* a Ribombee (Focus Sash) arma Sticky Web e Tailwind, a Ninetales põe Aurora Veil na neve, e atrás do véu o Lunala (Shadow Shield) e a Clefable (Cosmic Power + Stored Power) sobem. A Tapu Lele de Choice Specs pune quem entra para parar o setup.

*Plano (Doubles):* a Psychic Terrain da Tapu Lele protege os parceiros de Fake Out e prioridade; Aurora Veil + Tailwind no primeiro turno. Golpes de dois alvos: Blizzard (100% na neve), Hyper Voice com Liquid Voice (vira Água), Dazzling Gleam; o Pollen Puff da Ribombee cura o parceiro em vez de bater. Nada no time acerta o parceiro.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Lunala | Leftovers | Shadow Shield | Timid | Moongeist Beam, Moonblast, Calm Mind, Roost |
| Tapu Lele | Choice Specs | Psychic Surge | Modest | Psyshock, Moonblast, Dazzling Gleam, Focus Blast |
| Primarina | Bondstone | Liquid Voice | Modest | Hyper Voice, Moonblast, Ice Beam, Energy Ball |
| Ninetales-Alola | Light Clay | Snow Warning | Timid | Blizzard, Moonblast, Aurora Veil, Freeze-Dry |
| Ribombee | Focus Sash | Shield Dust | Timid | Sticky Web, Moonblast, Pollen Puff, Tailwind |
| Clefable | Sitrus Berry | Magic Guard | Bold | Moonblast, Soft-Boiled, Cosmic Power, Stored Power |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>dev_scripts/nexus_validar_time.py</code>)</summary>

```
=== TRAINER_NEXUS_LILLIE ===
Name: Lillie
Class: Lass
Pic: Lillie
Gender: Female
Music: Hg Girl 1
Double Battle: No
AI: Smart Trainer

Lunala @ Leftovers
Timid Nature
Level: 100
Ability: Shadow Shield
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Moongeist Beam
- Moonblast
- Calm Mind
- Roost

Tapu Lele @ Choice Specs
Modest Nature
Level: 100
Ability: Psychic Surge
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Psyshock
- Moonblast
- Dazzling Gleam
- Focus Blast

Primarina @ Bondstone
Modest Nature
Level: 100
Ability: Liquid Voice
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Hyper Voice
- Moonblast
- Ice Beam
- Energy Ball

Ninetales-Alola @ Light Clay
Timid Nature
Level: 100
Ability: Snow Warning
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Blizzard
- Moonblast
- Aurora Veil
- Freeze-Dry

Ribombee @ Focus Sash
Timid Nature
Level: 100
Ability: Shield Dust
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Sticky Web
- Moonblast
- Pollen Puff
- Tailwind

Clefable @ Sitrus Berry
Bold Nature
Level: 100
Ability: Magic Guard
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Moonblast
- Soft-Boiled
- Cosmic Power
- Stored Power
```

</details>

### Lendário associado

#### Lunala

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_Lunala_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Lunala**. Lillie é a campeã dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Lillie, filha da Lusamine. Em Alola protegeu o Cosmog na bolsa; neste hack cruza a campanha com o Vulpix (hoje Ninetales), ergueu a parede de gelo da M2 e, no Altar, estava ao lado da mãe no resgate.

**A criatura.** Lunala, o lendário da lua, forma final do Cosmog. As asas absorvem a luz e fazem noite em pleno dia; quando o terceiro olho se ativa, ela abre passagens para outro mundo.

**O fragmento.** Noite sem chão: um lago negro em todas as direções, segurando as estrelas paradas. No céu não há lua, só um buraco redondo onde ela deveria estar. Quando o buraco abre as asas, as estrelas se apagam fileira por fileira.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> Night, and no ground under it. A black lake stretched out in every direction, holding the stars perfectly still.
>
> There was no moon in the sky. Only a round hole where it should have been.

**Boss**

> The round hole in the sky opened its wings.
>
> The stars went out one row at a time, and a third eye began to shine.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md): o que fica é o fragmento, no nível 1)

> File L-792. Moone.
>
> A night that swallowed its own moon, and a young lady whose moon once fit inside her bag.
>
> What came back with you is a little cloud of stars. She asked me whose it was. I said: whoever carries it.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Lunala_Arrival:
	.string "Night, and no ground under it. A black\n"
	.string "lake stretched out in every direction,\l"
	.string "holding the stars perfectly still.\p"
	.string "There was no moon in the sky. Only a\n"
	.string "round hole where it should have been.$"

Nexus_Text_Lunala_Boss:
	.string "The round hole in the sky opened its\n"
	.string "wings.\p"
	.string "The stars went out one row at a time,\n"
	.string "and a third eye began to shine.$"

Nexus_Text_Lunala_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-792. Moone.\p"
	.string "A night that swallowed its own moon,\n"
	.string "and a young lady whose moon once fit\l"
	.string "inside her bag.\p"
	.string "What came back with you is a little\n"
	.string "cloud of stars. She asked me whose it\l"
	.string "was. I said: whoever carries it.$"
```

</details>


#### Tapu Lele

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_TapuLele_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Tapu Lele**. Lillie é a campeã dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Lillie, a menina que aprendeu a lutar e a dizer o que viu; no pós-game toma chá com a mãe e o irmão em Olivine (design §8).

**A criatura.** Tapu Lele, guardiã de Akala. Espalha escamas brilhantes que curam feridas e doenças; é inocente e cruel ao mesmo tempo, e o excesso das escamas faz mal. Não se importa com o que acontece a quem ela cura.

**O fragmento.** Um jardim sob uma neve de escamas brilhantes. Todas as flores abriram além da conta, e os Pokémon deitados entre elas dormem fundo demais. Algo pequeno e luminoso passa zumbindo e sacode mais escamas por cima, como um presente.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> Glittering scales fell like snow over a garden.
>
> Every flower had bloomed too far. The Pokémon lying among them were sleeping far too deeply.

**Boss**

> Something small and bright came through the petals, humming.
>
> It shook a shower of scales over you, as if it were a gift.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md): o que fica é o fragmento, no nível 1)

> File L-786. Guardian of Akala.
>
> A kindness with no end to it, and a young lady who has learned where kindness should stop.
>
> What remains of it is small, and it hums. Keep it close. Not too close.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_TapuLele_Arrival:
	.string "Glittering scales fell like snow over\n"
	.string "a garden.\p"
	.string "Every flower had bloomed too far. The\n"
	.string "Pokémon lying among them were\l"
	.string "sleeping far too deeply.$"

Nexus_Text_TapuLele_Boss:
	.string "Something small and bright came\n"
	.string "through the petals, humming.\p"
	.string "It shook a shower of scales over you,\n"
	.string "as if it were a gift.$"

Nexus_Text_TapuLele_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-786. Guardian of Akala.\p"
	.string "A kindness with no end to it, and a\n"
	.string "young lady who has learned where\l"
	.string "kindness should stop.\p"
	.string "What remains of it is small, and it\n"
	.string "hums. Keep it close. Not too close.$"
```

</details>

### Diálogo genérico

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Lillie_Fight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Lillie cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala de si, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

A Lillie observa e anota (design §3); ela lembra de quando não lutava e escondia um Pokémon na bolsa. A virada: agora é a Ninetales que não deixa ela esconder nada.

**Antes da luta**

> Oh! Hello. I've been writing down everything I see, so I don't get lost.
>
> Once, I couldn't battle at all. I kept a little Pokémon hidden in my bag and asked everyone not to look.
>
> Now Ninetales won't let me hide anything. So... I'll do my best!

**Derrota**

> Oh... I'll write that down. All of it. Even the part where I lost.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Lillie_Intro:
	.string "Oh! Hello. I've been writing down\n"
	.string "everything I see, so I don't get lost.\p"
	.string "Once, I couldn't battle at all. I kept\n"
	.string "a little Pokémon hidden in my bag and\l"
	.string "asked everyone not to look.\p"
	.string "Now Ninetales won't let me hide\n"
	.string "anything. So... I'll do my best!$"

Nexus_Text_Lillie_Defeat:
	.string "Oh... I'll write that down. All of it.\n"
	.string "Even the part where I lost.$"
```

</details>

#### Variações 2 e 3 (📝 proposta de 30/09/2026)

📝 **Proposta de 30/09/2026, aguardando o autor.** A variação 1 é a que já está no jogo (acima). Estas duas também servem para qualquer sala e qualquer dia ([R16](../NEXUS_REGRAS.md)): falam só de Lillie. Nada disto está no código.

**Variação 2 — a Ninetales vai primeiro.** Humor leve com a parceira. A Ninetales sempre sai primeiro agora, porque a Lillie demora demais para decidir, e ela tem razão. A Lillie decide ali mesmo. Na derrota, a Ninetales fica emburrada; a Lillie não.

**Antes da luta**

> Oh! Excuse me. Ninetales, you can come out. It's only a Trainer.
>
> She always goes first now. She says I take too long to decide. She's right.
>
> ...I've decided! Let's battle!

**Derrota**

> Ninetales is sulking. I'm not. That was wonderful.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Lillie_Intro2:
	.string "Oh! Excuse me. Ninetales, you can come\n"
	.string "out. It's only a Trainer.\p"
	.string "She always goes first now. She says I\n"
	.string "take too long to decide. She's right.\p"
	.string "...I've decided! Let's battle!$"

Nexus_Text_Lillie_Defeat2:
	.string "Ninetales is sulking. I'm not. That was\n"
	.string "wonderful.$"
```

</details>

**Variação 3 — escolher a roupa.** A virada de visual da Lillie (o rabo de cavalo de Sun/Moon). A mãe escolhia tudo o que ela vestia, sempre branco, como uma boneca na vitrine. Um dia ela prendeu o cabelo e escolheu sozinha: a coisa mais corajosa que tinha feito. Esta luta talvez seja a mais corajosa.

**Antes da luta**

> My mother used to choose everything I wore. White, always white. Like a doll in a glass case.
>
> One day I tied up my hair and chose for myself. It was the bravest thing I had ever done.
>
> ...Well, the second bravest. This might be the bravest! Let's battle!

**Derrota**

> I'm still glad I chose this. Even now.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Lillie_Intro3:
	.string "My mother used to choose everything I\n"
	.string "wore. White, always white. Like a doll in\l"
	.string "a glass case.\p"
	.string "One day I tied up my hair and chose for\n"
	.string "myself. It was the bravest thing I had\l"
	.string "ever done.\p"
	.string "...Well, the second bravest. This might\n"
	.string "be the bravest! Let's battle!$"

Nexus_Text_Lillie_Defeat3:
	.string "I'm still glad I chose this. Even now.$"
```

</details>


### Diálogo associado ao lendário

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Lillie é a **campeã**, a luta logo antes do lendário do dia. Uma fala por lendário; o nome da espécie não aparece ([R16](../NEXUS_REGRAS.md)). Rótulos com a espécie porque Lillie é campeã de dois.

#### Lunala

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Lillie_Lunala_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

A Lillie viu a criatura atravessar o céu apagando a luz, e o Lunala dela ficou olhando também. Esta Lillie vem de um lugar onde o Cosmog da bolsa cresceu com ela: o Lunala do time é o Nebby dela, e ela diz isso sem cerimônia. Ela nota que o parceiro do jogador também começou pequeno (a família Cosmog que ele carrega) e pergunta, sem afirmar, se os dois carregaram o mesmo, em algum lugar. A virada, no depois: talvez no mundo do jogador o Nebby tenha crescido ao lado dele, ou nunca; ela acha que não importa qual, porque alguém o carregou até ele poder voar. Ela observa e pergunta, não prevê (design §3). O fragmento do R17 é um Cosmog, e a ficha do Looker devolve a pergunta: de quem é? De quem carrega.

**Antes da luta**

> I watched it cross the sky before you came. Wherever its wings passed, the light went out.
>
> My Lunala watched it too. It used to be small enough to fit in my bag. I called it Nebby.
>
> Yours started out small too, didn't it? I wonder if we carried the same one... somewhere.
>
> ...Ninetales, Nebby, are you ready? Let's go!

**Derrota**

> You didn't look away. Not once. Nebby noticed, too.

**Depois da luta**

> Its wings drink the light. That's why it's so dark around it.
>
> Where I come from, Nebby grew up by my side. Maybe where you come from, it grew up by yours. Or never at all.
>
> I don't think it matters which. Someone carried it until it could fly.
>
> Please be careful. And... look up, while you're there.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Lillie_Lunala_ChampionIntro:
	.string "I watched it cross the sky before you\n"
	.string "came. Wherever its wings passed, the\l"
	.string "light went out.\p"
	.string "My Lunala watched it too. It used to\n"
	.string "be small enough to fit in my bag. I\l"
	.string "called it Nebby.\p"
	.string "Yours started out small too, didn't\n"
	.string "it? I wonder if we carried the same\l"
	.string "one... somewhere.\p"
	.string "...Ninetales, Nebby, are you ready?\n"
	.string "Let's go!$"

Nexus_Text_Lillie_Lunala_ChampionDefeat:
	.string "You didn't look away. Not once.\n"
	.string "Nebby noticed, too.$"

Nexus_Text_Lillie_Lunala_ChampionAfter:
	.string "{SPEAKER NAME_LILLIE}Its wings drink the light. That's why\n"
	.string "it's so dark around it.\p"
	.string "Where I come from, Nebby grew up by\n"
	.string "my side. Maybe where you come from, it\l"
	.string "grew up by yours. Or never at all.\p"
	.string "I don't think it matters which.\n"
	.string "Someone carried it until it could fly.\p"
	.string "Please be careful. And... look up,\n"
	.string "while you're there.$"
```

</details>

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

📝 **Proposta de 30/09/2026, aguardando o autor.** A variação 1 é a que já está no jogo (acima). Sobre a criatura, pelo olhar de Lillie, sem o nome da espécie ([R16](../NEXUS_REGRAS.md)). Nada disto está no código.

**Variação 2 — o escuro com nome.** A Lillie tinha medo do escuro, e a mãe deixava todas as luzes acesas. Quando o Nebby cresceu e as asas beberam a luz, ela perdeu o medo: sabia o que fazia o escuro. No depois: o escuro em volta dela não é vazio, é a luz guardada; o terceiro olho abre caminho para longe, e se abrir um para o jogador, que ele procure quem ainda espera do outro lado (o irmão, neste fragmento; página 2 do diário).

**Antes da luta**

> When I was small, I was afraid of the dark. My mother kept every light in the house on.
>
> Then Nebby grew up, and its wings drank all the light around us. And I wasn't afraid at all.
>
> Because I knew what was making the dark. ...That's the difference, I think. Let's battle!

**Derrota**

> You weren't afraid either. I could tell.

**Depois da luta**

> The dark around it isn't empty. It's the light, kept safe inside its wings.
>
> When its third eye opens, it can take you somewhere else. Somewhere very far.
>
> If it opens one for you, please... look for anyone who is still waiting on the other side.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Lillie_Lunala_ChampionIntro2:
	.string "When I was small, I was afraid of the\n"
	.string "dark. My mother kept every light in the\l"
	.string "house on.\p"
	.string "Then Nebby grew up, and its wings drank\n"
	.string "all the light around us. And I wasn't\l"
	.string "afraid at all.\p"
	.string "Because I knew what was making the\n"
	.string "dark. ...That's the difference, I think.\l"
	.string "Let's battle!$"

Nexus_Text_Lillie_Lunala_ChampionDefeat2:
	.string "You weren't afraid either. I could tell.$"

Nexus_Text_Lillie_Lunala_ChampionAfter2:
	.string "{SPEAKER NAME_LILLIE}The dark around it isn't empty. It's\n"
	.string "the light, kept safe inside its wings.\p"
	.string "When its third eye opens, it can take\n"
	.string "you somewhere else. Somewhere very\l"
	.string "far.\p"
	.string "If it opens one for you, please... look\n"
	.string "for anyone who is still waiting on the\l"
	.string "other side.$"
```

</details>

**Variação 3 — a bolsa.** Antes ela carregava a criatura numa bolsa; agora a criatura a carrega. O Nebby ainda tenta entrar na bolsa às vezes, não cabe e não liga. A de lá não tem bolsa onde entrar, e por isso parece tão sozinha. No depois: tudo o que é grande começa pequeno o bastante para se esconder; se o jogador trouxer algo pequeno de lá (o Cosmog do R17), não o deixe na bolsa por muito tempo.

**Antes da luta**

> It's so strange. I used to carry it in a bag, and now it carries me.
>
> Nebby still tries to climb into my bag sometimes. It doesn't fit. It doesn't care.
>
> ...The one out there has no bag to climb into. I think that's why it looks so lonely. Let's battle.

**Derrota**

> Oh... Nebby is trying to hide in my bag again.

**Depois da luta**

> Everything big starts out small enough to hide.
>
> If you bring something small back from in there, please don't keep it in a bag. Not for too long.
>
> Let it see the sky. That's how it learns to become one.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Lillie_Lunala_ChampionIntro3:
	.string "It's so strange. I used to carry it in a\n"
	.string "bag, and now it carries me.\p"
	.string "Nebby still tries to climb into my bag\n"
	.string "sometimes. It doesn't fit. It doesn't\l"
	.string "care.\p"
	.string "...The one out there has no bag to climb\n"
	.string "into. I think that's why it looks so\l"
	.string "lonely. Let's battle.$"

Nexus_Text_Lillie_Lunala_ChampionDefeat3:
	.string "Oh... Nebby is trying to hide in my bag\n"
	.string "again.$"

Nexus_Text_Lillie_Lunala_ChampionAfter3:
	.string "{SPEAKER NAME_LILLIE}Everything big starts out small enough\n"
	.string "to hide.\p"
	.string "If you bring something small back from\n"
	.string "in there, please don't keep it in a bag.\l"
	.string "Not for too long.\p"
	.string "Let it see the sky. That's how it learns\n"
	.string "to become one.$"
```

</details>


#### Tapu Lele

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Lillie_TapuLele_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

A Lillie testou as escamas na própria mão (ela confere antes de afirmar): funcionam. Depois olhou os Pokémon dormindo entre as flores, curados de novo e de novo. A criatura não quer fazer mal; só não sabe parar. "Acho que conheço alguém assim." A virada, no depois: alguém que ela ama segurava tudo o que amava, e também com boa intenção; hoje elas tomam chá e a Lillie diz quando basta, e a mãe escuta. Sem dizer que a família está consertada (roteiro do Altar).

**Antes da luta**

> Did you feel the scales? They heal a scratch in a moment. I tried it on my hand. It works.
>
> Then I looked at the Pokémon sleeping in the flowers. They were healed too. Again, and again, and again.
>
> It doesn't mean any harm. It just doesn't know when to stop.
>
> ...I think I know someone like that. Let's battle, please!

**Derrota**

> Oh... That's enough, I think. You win.

**Depois da luta**

> Too much care can hurt. I didn't understand that for a long time.
>
> Someone I love used to hold on to everything she loved. She meant it kindly, too.
>
> We have tea now, sometimes. I tell her when it's enough, and she listens.
>
> Go gently with it. It's only trying to help.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Lillie_TapuLele_ChampionIntro:
	.string "Did you feel the scales? They heal a\n"
	.string "scratch in a moment. I tried it on my\l"
	.string "hand. It works.\p"
	.string "Then I looked at the Pokémon sleeping\n"
	.string "in the flowers. They were healed too.\l"
	.string "Again, and again, and again.\p"
	.string "It doesn't mean any harm. It just\n"
	.string "doesn't know when to stop.\p"
	.string "...I think I know someone like that.\n"
	.string "Let's battle, please!$"

Nexus_Text_Lillie_TapuLele_ChampionDefeat:
	.string "Oh... That's enough, I think. You\n"
	.string "win.$"

Nexus_Text_Lillie_TapuLele_ChampionAfter:
	.string "{SPEAKER NAME_LILLIE}Too much care can hurt. I didn't\n"
	.string "understand that for a long time.\p"
	.string "Someone I love used to hold on to\n"
	.string "everything she loved. She meant it\l"
	.string "kindly, too.\p"
	.string "We have tea now, sometimes. I tell her\n"
	.string "when it's enough, and she listens.\p"
	.string "Go gently with it. It's only trying\n"
	.string "to help.$"
```

</details>

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

📝 **Proposta de 30/09/2026, aguardando o autor.** A variação 1 é a que já está no jogo (acima). Sobre a criatura, pelo olhar de Lillie, sem o nome da espécie ([R16](../NEXUS_REGRAS.md)). Nada disto está no código.

**Variação 2 — inocente.** A guardiã voou até a Lillie e jogou escamas na cabeça dela, como uma bênção; depois foi até os Pokémon adormecidos e fez de novo e de novo, rindo. É a inocência que assusta. No depois: dizem que ela não se importa com quem cura; a Lillie acha que ela só nunca aprendeu que as pessoas podem estar satisfeitas. Se ela tentar curar você, diga obrigado, e depois diga não.

**Antes da luta**

> It flew right up to me and sprinkled its scales on my head. Like a blessing.
>
> Then it flew off to the Pokémon asleep in the flowers and did it again. And again. It was giggling.
>
> It's so innocent. That's what frightens me. Let's battle, please!

**Derrota**

> You knew when to stop. It doesn't.

**Depois da luta**

> The old stories say it doesn't care what happens to the ones it heals.
>
> I don't think that's cruelty. I think it just never learned that people can be full.
>
> If it tries to heal you, say thank you. And then say no.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Lillie_TapuLele_ChampionIntro2:
	.string "It flew right up to me and sprinkled its\n"
	.string "scales on my head. Like a blessing.\p"
	.string "Then it flew off to the Pokémon asleep\n"
	.string "in the flowers and did it again. And\l"
	.string "again. It was giggling.\p"
	.string "It's so innocent. That's what\n"
	.string "frightens me. Let's battle, please!$"

Nexus_Text_Lillie_TapuLele_ChampionDefeat2:
	.string "You knew when to stop. It doesn't.$"

Nexus_Text_Lillie_TapuLele_ChampionAfter2:
	.string "{SPEAKER NAME_LILLIE}The old stories say it doesn't care\n"
	.string "what happens to the ones it heals.\p"
	.string "I don't think that's cruelty. I think\n"
	.string "it just never learned that people can\l"
	.string "be full.\p"
	.string "If it tries to heal you, say thank you.\n"
	.string "And then say no.$"
```

</details>

**Variação 3 — eu também.** A autocrítica: a Lillie segurava o amiguinho dela tão apertado que não o deixava sair da bolsa; achava que o protegia, e o mantinha pequeno. Ela e a guardiã têm mais em comum do que gostaria. No depois: os Pokémon entre as flores não querem mais acordar, porque nada dói; deixe as coisas doerem um pouco, se precisarem.

**Antes da luta**

> I used to hold my little friend so tightly. I wouldn't let it out of my bag for anything.
>
> I thought I was keeping it safe. I was keeping it small.
>
> ...That guardian and I have more in common than I'd like. Let's battle!

**Derrota**

> Oh... I held on too tightly there, didn't I?

**Depois da luta**

> Its scales heal almost anything. Scrapes, fevers, bad dreams.
>
> But the Pokémon in those flowers don't want to wake up anymore. Why would they? Nothing hurts.
>
> Please be gentle. And let things hurt a little, if they need to.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Lillie_TapuLele_ChampionIntro3:
	.string "I used to hold my little friend so\n"
	.string "tightly. I wouldn't let it out of my bag\l"
	.string "for anything.\p"
	.string "I thought I was keeping it safe. I was\n"
	.string "keeping it small.\p"
	.string "...That guardian and I have more in\n"
	.string "common than I'd like. Let's battle!$"

Nexus_Text_Lillie_TapuLele_ChampionDefeat3:
	.string "Oh... I held on too tightly there, didn't\n"
	.string "I?$"

Nexus_Text_Lillie_TapuLele_ChampionAfter3:
	.string "{SPEAKER NAME_LILLIE}Its scales heal almost anything.\n"
	.string "Scrapes, fevers, bad dreams.\p"
	.string "But the Pokémon in those flowers don't\n"
	.string "want to wake up anymore. Why would\l"
	.string "they? Nothing hurts.\p"
	.string "Please be gentle. And let things hurt a\n"
	.string "little, if they need to.$"
```

</details>


Falante: `SP_NAME_LILLIE` já existe em `include/constants/speaker_names.h`.
