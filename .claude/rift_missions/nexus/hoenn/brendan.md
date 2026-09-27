# Brendan

**Região da ficha:** Hoenn

Aparece no checklist como:

- **Brendan** (Hoenn · Rivais) — protagonista ou rival, filho do Professor Birch.

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
| `OBJ_EVENT_GFX_LINK_RS_BRENDAN` | `graphics/object_events/pics/people/ruby_sapphire_brendan/walking.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_RS_BRENDAN` | `graphics/trainers/front_pics/brendan_rs.png` |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

> **Atenção:** `OBJ_EVENT_GFX_BRENDAN_*` e `TRAINER_PIC_FRONT_BRENDAN` **não são o Brendan**: neste hack a arte foi trocada pelo protagonista **Gold** (os `TRAINER_RIVALGOLD*` usam essa pic). O Brendan de Hoenn de verdade é a arte de *Ruby/Sapphire* (`RS_`), listada acima. O overworld RS só tem andar/correr (sem bike/surf).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_BRENDAN_PLACEHOLDER` | 853 | 0x855 | **sem time** (ID reservado, sem bloco no `.party`) | — (nenhum script chama) |

IDs aposentados na limpeza de treinadores (não reaproveitar sem necessidade): `TRAINER_UNUSED_401` (ex-`TRAINER_BRENDAN_ROUTE_119_MUDKIP`, 522), `TRAINER_UNUSED_407` (ex-`TRAINER_BRENDAN_ROUTE_103_TREECKO`, 523), `TRAINER_UNUSED_396` (ex-`TRAINER_BRENDAN_ROUTE_110_TREECKO`, 524), `TRAINER_UNUSED_402` (ex-`TRAINER_BRENDAN_ROUTE_119_TREECKO`, 525), `TRAINER_UNUSED_408` (ex-`TRAINER_BRENDAN_ROUTE_103_TORCHIC`, 526), `TRAINER_UNUSED_397` (ex-`TRAINER_BRENDAN_ROUTE_110_TORCHIC`, 527), `TRAINER_UNUSED_403` (ex-`TRAINER_BRENDAN_ROUTE_119_TORCHIC`, 528), `TRAINER_UNUSED_412` (ex-`TRAINER_BRENDAN_RUSTBORO_TREECKO`, 592), `TRAINER_UNUSED_413` (ex-`TRAINER_BRENDAN_RUSTBORO_MUDKIP`, 593), `TRAINER_UNUSED_414` (ex-`TRAINER_BRENDAN_RUSTBORO_TORCHIC`, 599), `TRAINER_UNUSED_418` (ex-`TRAINER_BRENDAN_LILYCOVE_MUDKIP`, 661), `TRAINER_UNUSED_419` (ex-`TRAINER_BRENDAN_LILYCOVE_TREECKO`, 662), `TRAINER_UNUSED_420` (ex-`TRAINER_BRENDAN_LILYCOVE_TORCHIC`, 663).

### Time das Rift Missions

📝 **Proposta de 27/09/2026, aguardando o autor.** `TRAINER_NEXUS_BRENDAN`, campeão do Reshiram e do Jirachi. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler).

Pic `RS Brendan` (`TRAINER_PIC_FRONT_RS_BRENDAN`), a arte de Ruby/Sapphire; a `Brendan` deste hack é o Gold (ver a atenção acima). Lendário **Reshiram**, o dragão da verdade, do qual ele é campeão: o filho do Professor Birch faz pesquisa de campo e só anota o que é verdade. Semi-lendário **Jirachi**, o outro de que é campeão, o Pokémon dos desejos de Hoenn. Mega **Sceptile** (Grasstite), a linha do Treecko, inicial de Hoenn. Mais **Torkoal** (Drought), **Swellow** (o Taillow que o rival sempre carrega em Emerald) e **Hariyama**, todos de Hoenn.

*Plano:* sol. O Torkoal liga o Drought e o Reshiram queima com Blue Flare e Heat Wave; a Mega Sceptile solta Solar Beam sem carregar; o Swellow bate de Guts com Flame Orb; o Jirachi dá Wish e segura o ritmo.
*Plano (Singles):* o Torkoal arma Stealth Rock e limpa hazards com Rapid Spin antes de soltar a Eruption; o Jirachi pivota com U-turn e Wish; o Reshiram de Choice Specs quebra; o Swellow limpa no fim.
*Plano (Doubles):* o formato em que o time brilha. Hariyama dá Fake Out enquanto o Torkoal solta Eruption nos dois oponentes; o Reshiram usa Heat Wave no sol; o Jirachi dá Helping Hand; a Mega Sceptile (Lightning Rod) puxa os golpes Elétricos para longe dos parceiros.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Reshiram | Choice Specs | Turboblaze | Modest | Blue Flare, Draco Meteor, Heat Wave, Earth Power |
| Jirachi | Leftovers | Serene Grace | Careful | Iron Head, Helping Hand, Wish, U-turn |
| Sceptile | Grasstite | Overgrow | Timid | Solar Beam, Dragon Pulse, Focus Blast, Protect |
| Torkoal | Charcoal | Drought | Quiet | Eruption, Heat Wave, Stealth Rock, Rapid Spin |
| Swellow | Flame Orb | Guts | Jolly | Facade, Brave Bird, U-turn, Protect |
| Hariyama | Assault Vest | Thick Fat | Adamant | Fake Out, Close Combat, Knock Off, Heavy Slam |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>nexus_validar_time.py</code>: trainerproc, constantes, learnsets e categorias)</summary>

```
=== TRAINER_NEXUS_BRENDAN ===
Name: Brendan
Class: Rival
Pic: RS Brendan
Gender: Male
Music: Male
Double Battle: Yes
AI: Smart Trainer

Reshiram @ Choice Specs
Modest Nature
Level: 100
Ability: Turboblaze
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Blue Flare
- Draco Meteor
- Heat Wave
- Earth Power

Jirachi @ Leftovers
Careful Nature
Level: 100
Ability: Serene Grace
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Iron Head
- Helping Hand
- Wish
- U-turn

Sceptile @ Grasstite
Timid Nature
Level: 100
Ability: Overgrow
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Solar Beam
- Dragon Pulse
- Focus Blast
- Protect

Torkoal @ Charcoal
Quiet Nature
Level: 100
Ability: Drought
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Eruption
- Heat Wave
- Stealth Rock
- Rapid Spin

Swellow @ Flame Orb
Jolly Nature
Level: 100
Ability: Guts
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Facade
- Brave Bird
- U-turn
- Protect

Hariyama @ Assault Vest
Adamant Nature
Level: 100
Ability: Thick Fat
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Fake Out
- Close Combat
- Knock Off
- Heavy Slam
```

</details>

### Lendário associado

#### Reshiram

📝 **Proposta de 27/09/2026, aguardando o autor.** **Reshiram**. Brendan é o campeão dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Brendan, filho do Professor Birch, de Littleroot. Rival em Ruby/Sapphire/Emerald, faz pesquisa de campo para o pai, e depois de perder para o jogador volta a ajudar na pesquisa.

**A criatura.** Reshiram (Dragão/Fogo), o Pokémon da verdade, que ajuda quem quer construir um mundo de verdade. Quando a cauda dele se inflama, o calor movimenta a atmosfera e muda o clima do mundo. Mundo em Black/White: Dragonspiral Tower.

**O fragmento.** Um deserto de cinza branca, debaixo de um céu que queima azul nas bordas. Não há sombra nenhuma: tudo é iluminado de todos os lados ao mesmo tempo, como se nada tivesse permissão de se esconder.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A desert of white ash, under a sky that burned blue at the edges.
>
> There were no shadows. Everything was lit from every side at once, as if nothing here was allowed to hide.

**Boss**

> The heat rose all at once, and the sky itself began to move.
>
> Something white turned its head, and a great tail began to spin, bright as a furnace.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md))

> File L-643. Vast White.
>
> A place where nothing can hide, and a young man who finally stopped hiding one small thing.
>
> What came back with you is small and glows faintly. It glowed brighter when he laughed. I have no explanation.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Reshiram_Arrival:
	.string "A desert of white ash, under a sky that\n"
	.string "burned blue at the edges.\p"
	.string "There were no shadows. Everything was\n"
	.string "lit from every side at once, as if\l"
	.string "nothing here was allowed to hide.$"

Nexus_Text_Reshiram_Boss:
	.string "The heat rose all at once, and the sky\n"
	.string "itself began to move.\p"
	.string "Something white turned its head, and a\n"
	.string "great tail began to spin, bright as a\l"
	.string "furnace.$"

Nexus_Text_Reshiram_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-643. Vast White.\p"
	.string "A place where nothing can hide, and a\n"
	.string "young man who finally stopped hiding\l"
	.string "one small thing.\p"
	.string "What came back with you is small and\n"
	.string "glows faintly. It glowed brighter when\l"
	.string "he laughed. I have no explanation.$"
```

</details>

#### Jirachi

📝 **Proposta de 27/09/2026, aguardando o autor.** **Jirachi**. Brendan é o campeão dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Brendan, filho do Professor Birch, de Littleroot. Rival em Ruby/Sapphire/Emerald, faz pesquisa de campo para o pai, e depois de perder para o jogador volta a ajudar na pesquisa.

**A criatura.** Jirachi (Aço/Psíquico) acorda só por sete dias a cada mil anos. Os desejos escritos nas tirinhas de papel da cabeça dele se realizam, e ele tem um terceiro olho na barriga. Ligado a Hoenn pelo Millennium Comet do filme.

**O fragmento.** Um morro debaixo de um cometa que não se move. Tirinhas de papel amarradas em cada folha de grama, milhares, cada uma com um desejo escrito.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A hill, and above it a comet that did not move.
>
> Paper tags were tied to every blade of grass, thousands of them, and each one had a wish written on it.

**Boss**

> The comet flared. One tag tore loose and flew up toward something small and sleeping.
>
> It woke, and the eye on its belly opened last.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md))

> File L-385. Wish.
>
> A hill full of other people's wishes, and a young man who wished for the smallest thing on it.
>
> What came back with you is asleep. It will likely stay asleep a long time. That is how it keeps its promises.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Jirachi_Arrival:
	.string "A hill, and above it a comet that did not\n"
	.string "move.\p"
	.string "Paper tags were tied to every blade of\n"
	.string "grass, thousands of them, and each one\l"
	.string "had a wish written on it.$"

Nexus_Text_Jirachi_Boss:
	.string "The comet flared. One tag tore loose\n"
	.string "and flew up toward something small and\l"
	.string "sleeping.\p"
	.string "It woke, and the eye on its belly opened\n"
	.string "last.$"

Nexus_Text_Jirachi_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-385. Wish.\p"
	.string "A hill full of other people's wishes, and\n"
	.string "a young man who wished for the smallest\l"
	.string "thing on it.\p"
	.string "What came back with you is asleep. It\n"
	.string "will likely stay asleep a long time. That\l"
	.string "is how it keeps its promises.$"
```

</details>


### Diálogo genérico

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Brendan cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala dele mesmo, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

**Antes da luta**

> Hey! Hold still a sec, I'm writing this down.
>
> My dad sends me out to record every Pokémon I see. Habitat, height, what it eats.
>
> So what do you eat? …Kidding. Let's battle, I'll take notes after!

**Derrota**

> Huh. You're pretty good. That's going in the notebook, underlined.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Brendan_Intro:
	.string "Hey! Hold still a sec, I'm writing this\n"
	.string "down.\p"
	.string "My dad sends me out to record every\n"
	.string "Pokémon I see. Habitat, height, what it\l"
	.string "eats.\p"
	.string "So what do you eat? …Kidding. Let's\n"
	.string "battle, I'll take notes after!$"

Nexus_Text_Brendan_Defeat:
	.string "Huh. You're pretty good. That's going\n"
	.string "in the notebook, underlined.$"
```

</details>


### Diálogo associado ao lendário

#### Reshiram

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Brendan é o **campeão**, a luta logo antes do Reshiram. A fala é sobre a criatura, sem dizer o nome dela.

O Brendan leu em três livros que o dragão branco só escuta quem fala a verdade. Então contou tudo o que já viu: cada Pokémon, cada rota. O dragão não ligou; esperava a única coisa que ele deixou de fora. A virada é essa verdade: o Brendan sempre quis ser a pessoa sobre quem os outros escrevem, e virou o cara do caderno, anotando o que o jogador fez. Quando disse isso em voz alta, a cauda do dragão esfriou um pouco.

**Antes da luta**

> That white dragon out there only listens to people who tell the truth. I read that in three different books.
>
> So I tried. I told it everything I've ever seen. Every Pokémon, every route.
>
> It didn't care. I think it was waiting for the one thing I left out.
>
> …Battle first. Truth later.

**Derrota**

> Okay. Okay. There's the truth, I guess.

**Depois da luta**

> Here's what I left out. I always wanted to be the one people write about.
>
> Instead I'm the guy with the notebook, writing down what you did.
>
> I said that out loud to it, and its tail stopped burning so hot. Weird, right?
>
> Anyway. Go on. I'll write this part down properly.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Brendan_Reshiram_ChampionIntro:
	.string "That white dragon out there only\n"
	.string "listens to people who tell the truth. I\l"
	.string "read that in three different books.\p"
	.string "So I tried. I told it everything I've\n"
	.string "ever seen. Every Pokémon, every route.\p"
	.string "It didn't care. I think it was waiting\n"
	.string "for the one thing I left out.\p"
	.string "…Battle first. Truth later.$"

Nexus_Text_Brendan_Reshiram_ChampionDefeat:
	.string "Okay. Okay. There's the truth, I guess.$"

Nexus_Text_Brendan_Reshiram_ChampionAfter:
	.string "{SPEAKER NAME_BRENDAN}Here's what I left out. I always wanted\n"
	.string "to be the one people write about.\p"
	.string "Instead I'm the guy with the notebook,\n"
	.string "writing down what you did.\p"
	.string "I said that out loud to it, and its tail\n"
	.string "stopped burning so hot. Weird, right?\p"
	.string "Anyway. Go on. I'll write this part down\n"
	.string "properly.$"
```

</details>

#### Jirachi

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Brendan é o **campeão**, a luta logo antes do Jirachi. A fala é sobre a criatura, sem dizer o nome dela.

No morro do cometa, o Brendan leu uns cinquenta desejos pendurados na grama; quase todos eram sobre voltar para casa. Ele escreveu o dele e não quer contar. A virada é que o desejo é pequeno: nem "ser campeão", nem "vencer você", só "quero contar ao meu pai sobre este lugar". É o pesquisador de campo inteiro numa frase. O pedido: se achar a tirinha dele, deixe onde está.

**Antes da luta**

> Up on the hill there's a comet that doesn't move, and paper tags tied to every blade of grass.
>
> Every tag has a wish on it. I read about fifty. Most of them are about going home.
>
> I wrote one too. Don't ask. …Okay, you can ask after I win!

**Derrota**

> Nope. Guess that wish is on hold.

**Depois da luta**

> Fine, my wish. It said: 'I want to tell my dad about this place.'
>
> Not 'be Champion.' Not 'beat you.' Just that.
>
> It only wakes up for a week every thousand years, so hurry. And if you find my tag, leave it where it is.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Brendan_Jirachi_ChampionIntro:
	.string "Up on the hill there's a comet that\n"
	.string "doesn't move, and paper tags tied to\l"
	.string "every blade of grass.\p"
	.string "Every tag has a wish on it. I read about\n"
	.string "fifty. Most of them are about going\l"
	.string "home.\p"
	.string "I wrote one too. Don't ask. …Okay, you\n"
	.string "can ask after I win!$"

Nexus_Text_Brendan_Jirachi_ChampionDefeat:
	.string "Nope. Guess that wish is on hold.$"

Nexus_Text_Brendan_Jirachi_ChampionAfter:
	.string "{SPEAKER NAME_BRENDAN}Fine, my wish. It said: 'I want to tell my\n"
	.string "dad about this place.'\p"
	.string "Not 'be Champion.' Not 'beat you.' Just\n"
	.string "that.\p"
	.string "It only wakes up for a week every\n"
	.string "thousand years, so hurry. And if you\l"
	.string "find my tag, leave it where it is.$"
```

</details>

Falante novo: `SP_NAME_BRENDAN` (o `_ChampionAfter` usa `{SPEAKER NAME_BRENDAN}`; ainda não existe em `include/constants/speaker_names.h`, skill `nomear-falante`).
