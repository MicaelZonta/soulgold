# Wallace

**Região da ficha:** Hoenn

Aparece no checklist como:

- **Wallace — Água** (Hoenn · Líderes de Ginásio) — artista elegante, Líder de Sootopolis e Campeão em *Emerald*.
- **Wallace — Campeão** (Hoenn · Elite Four e Campeões) — assume o título de Hoenn em *Emerald*.

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
| `OBJ_EVENT_GFX_WALLACE` | `graphics/object_events/pics/people/wallace.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_CHAMPION_WALLACE` | `graphics/trainers/front_pics/champion_wallace.png` |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_WALLACE` | 335 | 0x64F | **sem time** (ID reservado, sem bloco no `.party`) | — (nenhum script chama) |
| `TRAINER_WALLACE2` | 856 | 0x858 | **sem time** (ID reservado, sem bloco no `.party`) | `src/battle_dome.c` |

### Time das Rift Missions

✅ **Implementado em 27/09/2026** (a proposta abaixo virou código): `TRAINER_NEXUS_WALLACE` = **1022** (flag de batalha `0x8FE`, limpa antes e depois de cada luta), bloco em `src/data/trainers.party`, nível pelo R2 (tabela em `src/data/nexus/trainers.h`). Fala genérica `Nexus_EventScript_Wallace_Fight`; campeão: `Nexus_EventScript_Wallace_Diancie_ChampionFight` (para Diancie), `Nexus_EventScript_Wallace_Xerneas_ChampionFight` (para Xerneas). Tudo em `data/scripts/nexus.inc`, sem blackout, resultado em `VAR_TEMP_3`. Para testar: menu de debug → Rift Missions… → Nexus fights… → Wallace.

📝 **Proposta de 27/09/2026, aguardando o autor.** `TRAINER_NEXUS_WALLACE`, campeão de Xerneas e Diancie. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler).

Lendário **Xerneas** (Fada, a vida eterna, a beleza que nunca murcha); semi-lendário e Mega na mesma peça: **Diancie** com Fairytite (Pedra/Fada, a joia; Mega de semi ocupa as duas vagas, R10). O Wallace é campeão dos dois. Mais **Milotic** (o ás de sempre, que foi Feebas), **Gyarados**, **Ludicolo** e **Tentacruel**, do time dele em Emerald/ORAS. O Fairy Aura do Xerneas reforça também os golpes de Fada da Diancie.

*Plano (Singles):* Tentacruel espalha Toxic Spikes e tira hazards com Rapid Spin; o Gyarados dá Intimidate e Thunder Wave; a Milotic (Competitive) pune Intimidate e Defog; a Mega Diancie rebate hazards e status com Magic Bounce; o Xerneas usa Geomancy num turno só com Power Herb e varre.

*Plano (Doubles):* o Ludicolo abre com Fake Out para o Xerneas fazer Geomancy em paz; Dazzling Gleam e Diamond Storm acertam os dois lados com Fairy Aura; o Gyarados enfraquece com Intimidate.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Xerneas | Power Herb | Fairy Aura | Modest | Geomancy, Moonblast, Dazzling Gleam, Focus Blast |
| Diancie | Fairytite | Clear Body | Modest | Diamond Storm, Moonblast, Earth Power, Protect |
| Milotic | Leftovers | Competitive | Bold | Scald, Recover, Ice Beam, Haze |
| Gyarados | Sitrus Berry | Intimidate | Adamant | Waterfall, Dragon Dance, Earthquake, Thunder Wave |
| Ludicolo | Sitrus Berry | Own Tempo | Modest | Fake Out, Giga Drain, Scald, Ice Beam |
| Tentacruel | Black Sludge | Clear Body | Calm | Rapid Spin, Toxic Spikes, Scald, Knock Off |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>dev_scripts/nexus_validar_time.py</code>)</summary>

```
=== TRAINER_NEXUS_WALLACE ===
Name: Wallace
Class: Champion
Pic: Champion Wallace
Gender: Male
Music: Hg Champion
Double Battle: No
AI: Smart Trainer

Xerneas @ Power Herb
Modest Nature
Level: 100
Ability: Fairy Aura
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Geomancy
- Moonblast
- Dazzling Gleam
- Focus Blast

Diancie @ Fairytite
Modest Nature
Level: 100
Ability: Clear Body
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Diamond Storm
- Moonblast
- Earth Power
- Protect

Milotic @ Leftovers
Bold Nature
Level: 100
Ability: Competitive
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Scald
- Recover
- Ice Beam
- Haze

Gyarados @ Sitrus Berry
Adamant Nature
Level: 100
Ability: Intimidate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Waterfall
- Dragon Dance
- Earthquake
- Thunder Wave

Ludicolo @ Sitrus Berry
Modest Nature
Level: 100
Ability: Own Tempo
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Fake Out
- Giga Drain
- Scald
- Ice Beam

Tentacruel @ Black Sludge
Calm Nature
Level: 100
Ability: Clear Body
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Rapid Spin
- Toxic Spikes
- Scald
- Knock Off
```

</details>


### Lendário associado

#### Xerneas

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_Xerneas_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Xerneas**. Wallace é o campeão dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Wallace, Campeão de Hoenn em Emerald, antes Líder de Sootopolis e aluno do Juan. Artista, mestre de Contest, obcecado por beleza; a Milotic é o ás dele.

**A criatura.** Xerneas, o Pokémon da vida (Fada), de Kalos. Os chifres brilham em sete cores; ele partilha vida eterna, e quando a própria vida acaba, vira uma árvore por mil anos.

**O fragmento.** Uma floresta onde tudo floresce ao mesmo tempo: flor, fruto e folha nova no mesmo galho, e nada murcha. No centro, uma árvore de galhos que brilham em todas as cores.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A forest where everything was in bloom at once.
>
> Flowers, fruit and new leaves, all on the same branch. Nothing here was withering.
>
> In the center stood a tree with branches that shone in every color.

**Boss**

> The tree stepped forward.
>
> Its branches were antlers, and every color on them grew brighter as it looked at you.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md))

> File L-716. The Everbloom.
>
> A forest where nothing ever fades, and an artist who has built his whole life on moments that do.
>
> What came back with you is small, and a little clumsy, and it will grow old. He found that the loveliest thing in the file.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Xerneas_Arrival:
	.string "A forest where everything was in bloom\n"
	.string "at once.\p"
	.string "Flowers, fruit and new leaves, all on\n"
	.string "the same branch. Nothing here was\l"
	.string "withering.\p"
	.string "In the center stood a tree with\n"
	.string "branches that shone in every color.$"

Nexus_Text_Xerneas_Boss:
	.string "The tree stepped forward.\p"
	.string "Its branches were antlers, and every\n"
	.string "color on them grew brighter as it\l"
	.string "looked at you.$"

Nexus_Text_Xerneas_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-716. The Everbloom.\p"
	.string "A forest where nothing ever fades, and\n"
	.string "an artist who has built his whole life\l"
	.string "on moments that do.\p"
	.string "What came back with you is small, and a\n"
	.string "little clumsy, and it will grow old. He\l"
	.string "found that the loveliest thing in the\l"
	.string "file.$"
```

</details>


#### Diancie

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_Diancie_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Diancie**. Wallace é o campeão dela: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Wallace, o Campeão artista de Hoenn, para quem a elegância é o que se vê de um trabalho que ninguém vê.

**A criatura.** Diancie, a Pokémon joia (Pedra/Fada), mítica. Uma mutação de um Pokémon de rocha comum; comprime o carbono do ar entre as mãos e faz diamantes.

**O fragmento.** Uma caverna onde as paredes estão virando diamante devagar: carvão preto nas bordas, pedra clara e brilhante no meio, e uma pressão no ar que se sente nos dentes.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A cave where the walls were slowly turning into diamond.
>
> Black coal at the edges, clear glittering stone at the heart, and a pressure in the air you could feel in your teeth.

**Boss**

> Pink light spilled out of the deepest wall.
>
> Something small and crowned stepped from the stone, and the diamonds around it began to grow.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md))

> File L-719. The Jewel Princess.
>
> A cave where coal is squeezed into diamonds, and a Champion who believes beauty is only pressure, patiently endured.
>
> What came back with you is small and still rough at the edges. He polished my magnifying glass before he left. It has never been so clean.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Diancie_Arrival:
	.string "A cave where the walls were slowly\n"
	.string "turning into diamond.\p"
	.string "Black coal at the edges, clear\n"
	.string "glittering stone at the heart, and a\l"
	.string "pressure in the air you could feel in\l"
	.string "your teeth.$"

Nexus_Text_Diancie_Boss:
	.string "Pink light spilled out of the deepest\n"
	.string "wall.\p"
	.string "Something small and crowned stepped\n"
	.string "from the stone, and the diamonds\l"
	.string "around it began to grow.$"

Nexus_Text_Diancie_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-719. The Jewel Princess.\p"
	.string "A cave where coal is squeezed into\n"
	.string "diamonds, and a Champion who believes\l"
	.string "beauty is only pressure, patiently\l"
	.string "endured.\p"
	.string "What came back with you is small and\n"
	.string "still rough at the edges. He polished\l"
	.string "my magnifying glass before he left. It\l"
	.string "has never been so clean.$"
```

</details>


### Diálogo genérico

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Wallace_Fight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Wallace cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala dele mesmo, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

**Antes da luta**

> Welcome. I am Wallace.
>
> People call my battles elegant. They see only the performance.
>
> They never see the mornings I spend in Sootopolis repeating a single turn until Milotic and I move as one.
>
> Beauty is mostly repetition no one sees. Now, let us show you some!

**Derrota**

> Bravo. The most beautiful thing on this stage today, and it was not mine.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Wallace_Intro:
	.string "Welcome. I am Wallace.\p"
	.string "People call my battles elegant. They\n"
	.string "see only the performance.\p"
	.string "They never see the mornings I spend in\n"
	.string "Sootopolis repeating a single turn\l"
	.string "until Milotic and I move as one.\p"
	.string "Beauty is mostly repetition no one\n"
	.string "sees. Now, let us show you some!$"

Nexus_Text_Wallace_Defeat:
	.string "Bravo. The most beautiful thing on this\n"
	.string "stage today, and it was not mine.$"
```

</details>


### Diálogo associado ao lendário

#### Xerneas

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Wallace_Xerneas_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Wallace é o **campeão**, a luta logo antes do Xerneas. A fala é sobre a criatura, sem dizer o nome dele.

O Wallace passou a vida atrás da beleza, e o fragmento é beleza que nunca acaba. Ele deveria adorar, e não adora: uma apresentação que nunca termina não é apresentação. A virada é a Milotic: ela foi um Feebas feio e ignorado e ficou bonita porque mudou; a criatura nunca precisa mudar. Ele espera que um dia ela aprenda como é bonito murchar.

**Antes da luta**

> Did you see the forest? Everything blooming at once, and nothing ever wilting.
>
> I should adore it. I have spent my whole life chasing beauty.
>
> And yet… a performance that never ends is not a performance.
>
> Ah, forgive me. Let us make something that ends!

**Derrota**

> Bravo. And now it has ended. That is the beautiful part.

**Depois da luta**

> My Milotic was a Feebas once. Plain. Overlooked.
>
> It became beautiful because it changed. That creature never has to.
>
> It gives life to everything around it. Even to that endless forest.
>
> I hope it learns someday how lovely it is to wilt. Go on.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Wallace_Xerneas_ChampionIntro:
	.string "Did you see the forest? Everything\n"
	.string "blooming at once, and nothing ever\l"
	.string "wilting.\p"
	.string "I should adore it. I have spent my\n"
	.string "whole life chasing beauty.\p"
	.string "And yet… a performance that never\n"
	.string "ends is not a performance.\p"
	.string "Ah, forgive me. Let us make something\n"
	.string "that ends!$"

Nexus_Text_Wallace_Xerneas_ChampionDefeat:
	.string "Bravo. And now it has ended. That is\n"
	.string "the beautiful part.$"

Nexus_Text_Wallace_Xerneas_ChampionAfter:
	.string "{SPEAKER NAME_WALLACE}My Milotic was a Feebas once. Plain.\n"
	.string "Overlooked.\p"
	.string "It became beautiful because it\n"
	.string "changed. That creature never has to.\p"
	.string "It gives life to everything around it.\n"
	.string "Even to that endless forest.\p"
	.string "I hope it learns someday how lovely it\n"
	.string "is to wilt. Go on.$"
```

</details>


#### Diancie

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Wallace_Diancie_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Wallace é o **campeão**, a luta logo antes da Diancie. A fala é sobre a criatura, sem dizer o nome dela.

Um diamante é carvão que não quebrou sob pressão. O Wallace se vê nisso: todo mundo acha a elegância dele natural, e nunca foi. A virada é que a criatura também era uma pedra comum antes de mudar, e ele entende perfeitamente: também foi só um menino de Sootopolis. O último conselho é gentil: ela é mais dura do que parece, e mais frágil também.

**Antes da luta**

> That cave! Coal on the walls, and in the heart of it, diamonds.
>
> A diamond is only coal that did not break under pressure.
>
> People think my elegance is effortless. It never was.
>
> Let us see which of us sparkles under pressure!

**Derrota**

> Bravo. You did not break. Neither did I, I hope.

**Depois da luta**

> They say that little princess was a common rock creature once, like any other.
>
> Something in it changed, and now it makes diamonds with its own hands.
>
> I understand it perfectly. I was only a boy from Sootopolis, once.
>
> Go and meet it. Be gentle. It is harder than it looks, and softer.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Wallace_Diancie_ChampionIntro:
	.string "That cave! Coal on the walls, and in the\n"
	.string "heart of it, diamonds.\p"
	.string "A diamond is only coal that did not\n"
	.string "break under pressure.\p"
	.string "People think my elegance is\n"
	.string "effortless. It never was.\p"
	.string "Let us see which of us sparkles under\n"
	.string "pressure!$"

Nexus_Text_Wallace_Diancie_ChampionDefeat:
	.string "Bravo. You did not break. Neither did I,\n"
	.string "I hope.$"

Nexus_Text_Wallace_Diancie_ChampionAfter:
	.string "{SPEAKER NAME_WALLACE}They say that little princess was a\n"
	.string "common rock creature once, like any\l"
	.string "other.\p"
	.string "Something in it changed, and now it\n"
	.string "makes diamonds with its own hands.\p"
	.string "I understand it perfectly. I was only a\n"
	.string "boy from Sootopolis, once.\p"
	.string "Go and meet it. Be gentle. It is harder\n"
	.string "than it looks, and softer.$"
```

</details>


Falante novo: `SP_NAME_WALLACE` (ainda não existe em `include/constants/speaker_names.h`).
