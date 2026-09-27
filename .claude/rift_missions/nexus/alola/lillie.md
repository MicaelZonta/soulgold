# Lillie

**Região da ficha:** Alola

Aparece no checklist como:

- **Lillie** (Alola · Outros notáveis) — filha de Lusamine e protagonista do arco de Alola do hack.

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

📝 **Proposta de 27/09/2026, aguardando o autor.** `TRAINER_NEXUS_LILLIE`, campeã de Lunala e Tapu Lele. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler).

Lendário **Lunala**: a Lillie carregou um Cosmog na bolsa em Alola, e em Moon ele virou a lua. **Não é o Nebby** (design §3: ninguém dá esse nome a Pokémon nenhum); é o Lunala do fragmento de onde esta Lillie veio, e ela nunca explica. Semi-lendário **Tapu Lele**, a guardiã que cura, a outra luta de campeã dela. Mega **Primarina** (Bondstone), do time de pós-game dela: a pedra de laço combina com quem só aprendeu a lutar junto de alguém. Mais **Ninetales de Alola** (a parceira, presença permanente, design §3; o mesmo Vulpix da Route 30), Ribombee e Clefable, todos do `TRAINER_LILLIE_POSTGAME`. Time de Fada e Psíquico, que observa antes de bater.

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
> A night that swallowed its own moon, and a young lady writing down every star it left behind.
>
> What came back with you is a little cloud of stars. She would know how to carry it. I suggest a bag.

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
	.string "and a young lady writing down every\l"
	.string "star it left behind.\p"
	.string "What came back with you is a little\n"
	.string "cloud of stars. She would know how to\l"
	.string "carry it. I suggest a bag.$"
```

</details>


#### Tapu Lele

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

### Diálogo associado ao lendário

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Lillie é a **campeã**, a luta logo antes do lendário do dia. Uma fala por lendário; o nome da espécie não aparece ([R16](../NEXUS_REGRAS.md)). Rótulos com a espécie porque Lillie é campeã de dois.

#### Lunala

A Lillie viu a criatura atravessar o céu e anotou que, onde as asas passam, a luz some. Mas anotou uma coisa estranha: onde escurece, aparecem mais estrelas, estrelas que não estavam lá. Ela carregou um Pokémon bem pequeno na bolsa e ele cresceu em algo parecido; ela não viu isso chegando (não prevê, observa). A virada, no depois: ela tinha medo da noite; hoje acha que a noite é só quando se enxerga mais longe. O fragmento do R17 é um Cosmog, e a ficha do Looker brinca com a bolsa.

**Antes da luta**

> I watched it cross the sky before you came. Wherever its wings passed, the light went out.
>
> But I wrote down something odd. Where it went dark, more stars came out. Stars that weren't there before.
>
> I once carried a very small Pokémon in my bag. It grew into something like that. I didn't see it coming.
>
> ...Ninetales, are you ready? Let's go!

**Derrota**

> You didn't look away. Not once. I noticed.

**Depois da luta**

> Its wings drink the light. That's why it's so dark around it.
>
> But the dark isn't empty. It's where it keeps the stars. I didn't know that when I was little.
>
> I used to be afraid of the night. Now I think it's just when you can see the farthest.
>
> Please be careful. And... look up, while you're there.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Lillie_Lunala_ChampionIntro:
	.string "I watched it cross the sky before you\n"
	.string "came. Wherever its wings passed, the\l"
	.string "light went out.\p"
	.string "But I wrote down something odd. Where\n"
	.string "it went dark, more stars came out.\l"
	.string "Stars that weren't there before.\p"
	.string "I once carried a very small Pokémon\n"
	.string "in my bag. It grew into something like\l"
	.string "that. I didn't see it coming.\p"
	.string "...Ninetales, are you ready? Let's go!$"

Nexus_Text_Lillie_Lunala_ChampionDefeat:
	.string "You didn't look away. Not once.\n"
	.string "I noticed.$"

Nexus_Text_Lillie_Lunala_ChampionAfter:
	.string "{SPEAKER NAME_LILLIE}Its wings drink the light. That's why\n"
	.string "it's so dark around it.\p"
	.string "But the dark isn't empty. It's where\n"
	.string "it keeps the stars. I didn't know that\l"
	.string "when I was little.\p"
	.string "I used to be afraid of the night. Now\n"
	.string "I think it's just when you can see the\l"
	.string "farthest.\p"
	.string "Please be careful. And... look up,\n"
	.string "while you're there.$"
```

</details>


#### Tapu Lele

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


Falante: `SP_NAME_LILLIE` já existe em `include/constants/speaker_names.h`.
