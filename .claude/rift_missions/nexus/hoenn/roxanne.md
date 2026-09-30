# Roxanne

**Região da ficha:** Hoenn

Aparece no checklist como:

- **Roxanne — Pedra** (Hoenn · Líderes de Ginásio) — professora e Líder de Rustboro que valoriza o estudo.

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
| `OBJ_EVENT_GFX_ROXANNE` | `graphics/object_events/pics/people/gym_leaders/roxanne.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_LEADER_ROXANNE` | `graphics/trainers/front_pics/leader_roxanne.png` |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_ROXANNE_2` | 770 | 0x802 | **sem time** (ID reservado, sem bloco no `.party`) | — (nenhum script chama) |
| `TRAINER_ROXANNE_3` | 771 | 0x803 | **sem time** (ID reservado, sem bloco no `.party`) | — (nenhum script chama) |
| `TRAINER_ROXANNE_4` | 772 | 0x804 | **sem time** (ID reservado, sem bloco no `.party`) | — (nenhum script chama) |
| `TRAINER_ROXANNE_5` | 773 | 0x805 | **sem time** (ID reservado, sem bloco no `.party`) | `src/battle_dome.c` |

IDs aposentados na limpeza de treinadores (não reaproveitar sem necessidade): `TRAINER_UNUSED_452` (ex-`TRAINER_ROXANNE_1`, 265).

### Time das Rift Missions

✅ **Implementado em 27/09/2026** (a proposta abaixo virou código): `TRAINER_NEXUS_ROXANNE` = **1015** (flag de batalha `0x8F7`, limpa antes e depois de cada luta), bloco em `src/data/trainers.party`, nível pelo R2 (tabela em `src/data/nexus/trainers.h`). Fala genérica `Nexus_EventScript_Roxanne_Fight`; campeão: `Nexus_EventScript_Roxanne_Uxie_ChampionFight` (para Uxie), `Nexus_EventScript_Roxanne_Terapagos_ChampionFight` (para Terapagos). Tudo em `data/scripts/nexus.inc`, sem blackout, resultado em `VAR_TEMP_3`. Para testar: menu de debug → Rift Missions… → Nexus fights… → Roxanne.

📝 **Proposta de 27/09/2026, aguardando o autor.** `TRAINER_NEXUS_ROXANNE`, campeã de Terapagos e Uxie. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler).

Lendário **Terapagos**, a origem do fenômeno Terastal: uma pedra viva que transforma a pedra comum em cristal, o objeto de estudo perfeito para a professora da Trainer's School; semi-lendário **Uxie**, o Ser do Conhecimento, que apaga a memória de quem o olha nos olhos (o medo de uma professora); Mega **Aerodactyl** (Rocktite), o fóssil revivido, como os que a Devon revive em Rustboro. Mais **Probopass** (o Nosepass dela, evoluído), **Omastar** e **Kabutops**: a coleção de fósseis de quem aprende Pedra pelos livros.

*Plano (Singles):* aula em etapas. O Uxie arma Stealth Rock e as duas telas e sai de U-turn; atrás das telas o Terapagos acumula Calm Mind e o Omastar usa Shell Smash (a White Herb devolve as defesas). O Probopass de Sturdy com Assault Vest segura qualquer golpe especial e pivota com Volt Switch; o Kabutops remove o Rapid Spin da equação com Knock Off.

*Plano (Doubles):* a Mega Aerodactyl põe Tailwind no turno 1 e entra de Rock Slide junto do Kabutops (dois Rock Slides com flinch sob Tailwind); o Uxie de Levitate põe as telas nos dois; o Terapagos e o Omastar entram depois que o campo está seguro. Nenhum golpe do time acerta o parceiro.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Terapagos | Leftovers | Tera Shift | Modest | Tera Starstorm, Earth Power, Calm Mind, Rapid Spin |
| Uxie | Light Clay | Levitate | Bold | Stealth Rock, Reflect, Light Screen, U-turn |
| Aerodactyl | Rocktite | Unnerve | Jolly | Rock Slide, Dual Wingbeat, Ice Fang, Tailwind |
| Probopass | Assault Vest | Sturdy | Modest | Power Gem, Flash Cannon, Earth Power, Volt Switch |
| Omastar | White Herb | Swift Swim | Modest | Shell Smash, Hydro Pump, Ice Beam, Ancient Power |
| Kabutops | Life Orb | Battle Armor | Adamant | Liquidation, Rock Slide, Aqua Jet, Knock Off |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>dev_scripts/nexus_validar_time.py</code>: espécie, item, habilidade, golpes e vagas)</summary>

```
=== TRAINER_NEXUS_ROXANNE ===
Name: Roxanne
Class: Leader
Pic: Leader Roxanne
Gender: Female
Music: Female
Double Battle: No
AI: Smart Trainer

Terapagos @ Leftovers
Modest Nature
Level: 100
Ability: Tera Shift
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Tera Starstorm
- Earth Power
- Calm Mind
- Rapid Spin

Uxie @ Light Clay
Bold Nature
Level: 100
Ability: Levitate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Stealth Rock
- Reflect
- Light Screen
- U-turn

Aerodactyl @ Rocktite
Jolly Nature
Level: 100
Ability: Unnerve
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Rock Slide
- Dual Wingbeat
- Ice Fang
- Tailwind

Probopass @ Assault Vest
Modest Nature
Level: 100
Ability: Sturdy
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Power Gem
- Flash Cannon
- Earth Power
- Volt Switch

Omastar @ White Herb
Modest Nature
Level: 100
Ability: Swift Swim
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Shell Smash
- Hydro Pump
- Ice Beam
- Ancient Power

Kabutops @ Life Orb
Adamant Nature
Level: 100
Ability: Battle Armor
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Liquidation
- Rock Slide
- Aqua Jet
- Knock Off
```

</details>


### Lendário associado

#### Terapagos

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_Terapagos_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Terapagos**. Roxanne é a campeã dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Roxanne, Líder de Rustboro e professora da Trainer's School, especialista em Pedra. Estuda tudo pelos livros e aprendeu na própria derrota que a batalha também se aprende fora deles.

**A criatura.** Terapagos (Normal) vive no fundo da Area Zero, em Paldea, e é tido como a origem do fenômeno Terastal. Guarda essa energia num casco de cristais e, ao liberá-la, muda para a Forma Terastal.

**O fragmento.** Uma cratera em que toda pedra criou cristal. Granito e basalto comuns brotando facetas como dentes novos, cada faceta com uma cor que não existe em lugar nenhum da cratera.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A crater, and every stone in it had grown a crystal.
>
> Plain gray rocks, sprouting facets like new teeth. Each facet held a color that was nowhere else in the crater.

**Boss**

> In the deepest part of the crater, the crystals all turned at once, toward a single point.
>
> Something lifted a shell that was more jewel than stone, and the light in every facet went out.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** (o que volta é o fragmento no nível 1, [R17](../NEXUS_REGRAS.md))

> File L-1024. Crystal Heart.
>
> A crater where every stone was trying to become a jewel, and a teacher who only ever asked stones to be stones.
>
> What came back with you is small, and its shell has no crystals yet. I have left room in this file for them to grow.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Terapagos_Arrival:
	.string "A crater, and every stone in it had\n"
	.string "grown a crystal.\p"
	.string "Plain gray rocks, sprouting facets like\n"
	.string "new teeth. Each facet held a color\l"
	.string "that was nowhere else in the crater.$"

Nexus_Text_Terapagos_Boss:
	.string "In the deepest part of the crater, the\n"
	.string "crystals all turned at once, toward a\l"
	.string "single point.\p"
	.string "Something lifted a shell that was more\n"
	.string "jewel than stone, and the light in\l"
	.string "every facet went out.$"

Nexus_Text_Terapagos_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-1024. Crystal Heart.\p"
	.string "A crater where every stone was trying\n"
	.string "to become a jewel, and a teacher who\l"
	.string "only ever asked stones to be stones.\p"
	.string "What came back with you is small, and\n"
	.string "its shell has no crystals yet. I have\l"
	.string "left room in this file for them to grow.$"
```

</details>

#### Uxie

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_Uxie_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Uxie**. Roxanne é a campeã dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Roxanne, Líder de Rustboro e professora da Trainer's School. Anota tudo, sempre, num caderno.

**A criatura.** Uxie, o Ser do Conhecimento, dorme no fundo do Lago Acuity, em Sinnoh. Dizem que apaga a memória de quem o olha nos olhos; por isso anda de olhos fechados.

**O fragmento.** Um lago parado coberto de folhas soltas, centenas delas, todas em branco. A tinta acabou de sair delas e ainda se espalha em fios finos pela água.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A still lake, and on its surface floated hundreds of loose pages.
>
> Every page was blank. The ink had only just left them. It was still spreading through the water in thin gray threads.

**Boss**

> The pages stopped drifting.
>
> Something rose from the middle of the lake with its eyes shut tight. It felt, somehow, like it was being polite.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** (o que volta é o fragmento no nível 1, [R17](../NEXUS_REGRAS.md))

> File L-480. Keeper of Memory.
>
> A lake of blank pages, and a teacher who writes everything down so she never has to trust her memory.
>
> What came back with you is very small, and it keeps its eyes closed. I did not check what I still remember. I would rather not know.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Uxie_Arrival:
	.string "A still lake, and on its surface floated\n"
	.string "hundreds of loose pages.\p"
	.string "Every page was blank. The ink had only\n"
	.string "just left them. It was still spreading\l"
	.string "through the water in thin gray\l"
	.string "threads.$"

Nexus_Text_Uxie_Boss:
	.string "The pages stopped drifting.\p"
	.string "Something rose from the middle of the\n"
	.string "lake with its eyes shut tight. It felt,\l"
	.string "somehow, like it was being polite.$"

Nexus_Text_Uxie_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-480. Keeper of Memory.\p"
	.string "A lake of blank pages, and a teacher\n"
	.string "who writes everything down so she\l"
	.string "never has to trust her memory.\p"
	.string "What came back with you is very small,\n"
	.string "and it keeps its eyes closed. I did not\l"
	.string "check what I still remember. I would\l"
	.string "rather not know.$"
```

</details>


### Diálogo genérico

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Roxanne_Fight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Roxanne cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala dela mesma, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

**Antes da luta**

> Good day! Please don't mind the notebook. I write down every battle, even the ones I lose.
>
> Especially those, actually. A loss teaches you more, but only if you remember it properly.
>
> I'm Roxanne, Gym Leader of Rustboro City. Now then -- shall we begin the lesson?

**Derrota**

> I see. I'll need a fresh page for this.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Roxanne_Intro:
	.string "Good day! Please don't mind the\n"
	.string "notebook. I write down every battle,\l"
	.string "even the ones I lose.\p"
	.string "Especially those, actually. A loss\n"
	.string "teaches you more, but only if you\l"
	.string "remember it properly.\p"
	.string "I'm Roxanne, Gym Leader of Rustboro\n"
	.string "City. Now then -- shall we begin the\l"
	.string "lesson?$"

Nexus_Text_Roxanne_Defeat:
	.string "I see. I'll need a fresh page for this.$"
```

</details>

#### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mais duas falas genéricas para as quatro primeiras salas, com ângulos diferentes da variação 1 (que está no jogo). Seguem o [R16](../NEXUS_REGRAS.md): falam dela mesma, sem o lugar nem a criatura do dia.

**Variação 2** — humor: o Nosepass que perdeu o norte.

**Antes da luta**

> Excuse me, have you seen a Nosepass? Mine always faces north, and I seem to have lost north.
>
> Nothing here points anywhere. It's quite upsetting for a Rock type.
>
> Well. A battle has a clear direction, at least. Shall we?

**Derrota**

> Your lesson, not mine. I'll take notes.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Roxanne_Intro2:
	.string "Excuse me, have you seen a Nosepass?\n"
	.string "Mine always faces north, and I seem to\l"
	.string "have lost north.\p"
	.string "Nothing here points anywhere. It's\n"
	.string "quite upsetting for a Rock type.\p"
	.string "Well. A battle has a clear direction, at\n"
	.string "least. Shall we?$"

Nexus_Text_Roxanne_Defeat2:
	.string "Your lesson, not mine. I'll take notes.$"
```

</details>

**Variação 3** — a regra da Trainer's School que nem ela seguiu (lembrança de uma derrota).

**Antes da luta**

> The Trainer's School in Rustboro has a rule I wrote myself: check your notes before every battle.
>
> Nobody follows it. Including me, once. I lost rather badly.
>
> So now I check twice. …Right. Checked. Let us begin!

**Derrota**

> Checked twice, lost once. The data is humbling.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Roxanne_Intro3:
	.string "The Trainer's School in Rustboro has a\n"
	.string "rule I wrote myself: check your notes\l"
	.string "before every battle.\p"
	.string "Nobody follows it. Including me, once. I\n"
	.string "lost rather badly.\p"
	.string "So now I check twice. …Right. Checked.\n"
	.string "Let us begin!$"

Nexus_Text_Roxanne_Defeat3:
	.string "Checked twice, lost once. The data is\n"
	.string "humbling.$"
```

</details>


### Diálogo associado ao lendário

#### Terapagos

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Roxanne_Terapagos_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Roxanne é a **campeã**, a luta logo antes do Terapagos. A fala é sobre a criatura, sem dizer o nome dela.

A Roxanne escolheu Pedra porque pedra não muda: é por isso que confia nela. A criatura faz o contrário: toca uma pedra comum e a obriga a virar joia agora. A professora encheu seis páginas tentando classificar os cristais e as anotações não fecham. A derrota: as anotações dela acertaram tudo, menos o resultado. O que fica é a conclusão de cientista: pedra muda, sim, só que devagar o bastante para chamarmos de permanência; e ela pede um cristal de volta, porque quer estar errada por escrito.

**Antes da luta**

> I've filled six pages trying to classify the crystals down there. Every single one is a different color.
>
> Those rocks were ordinary this morning. Granite, basalt. I checked. Now they're growing facets.
>
> I chose Rock types because stones don't change on you. I'm starting to think I was wrong about that, too.
>
> …Let me test one thing I'm still sure of. My team!

**Derrota**

> My notes were right about everything except the outcome.

**Depois da luta**

> Here is my conclusion, for what it's worth.
>
> Stones do change. They just do it slowly enough that we call it permanence.
>
> That creature doesn't wait. It touches a rock and asks it to become what it could be, right now.
>
> Go on ahead. And if you can, bring me back one crystal. I'd like to be wrong in writing.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Roxanne_Terapagos_ChampionIntro:
	.string "I've filled six pages trying to\n"
	.string "classify the crystals down there.\l"
	.string "Every single one is a different color.\p"
	.string "Those rocks were ordinary this\n"
	.string "morning. Granite, basalt. I checked.\l"
	.string "Now they're growing facets.\p"
	.string "I chose Rock types because stones\n"
	.string "don't change on you. I'm starting to\l"
	.string "think I was wrong about that, too.\p"
	.string "…Let me test one thing I'm still sure\n"
	.string "of. My team!$"

Nexus_Text_Roxanne_Terapagos_ChampionDefeat:
	.string "My notes were right about everything\n"
	.string "except the outcome.$"

Nexus_Text_Roxanne_Terapagos_ChampionAfter:
	.string "{SPEAKER NAME_ROXANNE}Here is my conclusion, for what it's\n"
	.string "worth.\p"
	.string "Stones do change. They just do it\n"
	.string "slowly enough that we call it\l"
	.string "permanence.\p"
	.string "That creature doesn't wait. It\n"
	.string "touches a rock and asks it to become\l"
	.string "what it could be, right now.\p"
	.string "Go on ahead. And if you can, bring me\n"
	.string "back one crystal. I'd like to be wrong\l"
	.string "in writing.$"
```

</details>

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mais duas falas de campeão para esta criatura, sem dizer o nome dela ([R16](../NEXUS_REGRAS.md)); a variação 1 é a que está no jogo.

**Variação 2** — humor: inventar nomes de cor para cristais.

**Antes da luta**

> I've invented eleven new words for colors today. The crystals down there keep needing more.
>
> 'Grenite.' 'Basaltine.' 'Rustboro dusk.' I'm rather proud of that one.
>
> Now, let's see what color a battle turns. My team!

**Derrota**

> That color, I shall call 'humbling.'

**Depois da luta**

> Every crystal changes when the light touches it. Every one becomes something different.
>
> Students are like that. Teach twenty the same lesson and you get twenty different people.
>
> The one down there is the teacher of them all, I think. Go on. It's a hard class.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Roxanne_Terapagos_ChampionIntro2:
	.string "I've invented eleven new words for\n"
	.string "colors today. The crystals down there\l"
	.string "keep needing more.\p"
	.string "'Grenite.' 'Basaltine.' 'Rustboro\n"
	.string "dusk.' I'm rather proud of that one.\p"
	.string "Now, let's see what color a battle\n"
	.string "turns. My team!$"

Nexus_Text_Roxanne_Terapagos_ChampionDefeat2:
	.string "That color, I shall call 'humbling.'$"

Nexus_Text_Roxanne_Terapagos_ChampionAfter2:
	.string "{SPEAKER NAME_ROXANNE}Every crystal changes when the light\n"
	.string "touches it. Every one becomes\l"
	.string "something different.\p"
	.string "Students are like that. Teach twenty\n"
	.string "the same lesson and you get twenty\l"
	.string "different people.\p"
	.string "The one down there is the teacher of\n"
	.string "them all, I think. Go on. It's a hard\l"
	.string "class.$"
```

</details>

**Variação 3** — o chão do Ginásio de Rustboro florescendo em cristal (o que ela perdeu, ou ganhou).

**Antes da luta**

> Rustboro is a city of stone. I grew up thinking that meant it would never change.
>
> This morning the floor of my Gym began to grow crystals too. I watched it bloom.
>
> I can't tell if I'm frightened or delighted. Let a battle decide!

**Derrota**

> Delighted, I think. Mostly.

**Depois da luta**

> The old builders of Rustboro used to say that stone is patient.
>
> They were right. It was patient for a very long time. It was only waiting to be asked.
>
> Go on. Whatever it asks you to become, take a moment before you answer.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Roxanne_Terapagos_ChampionIntro3:
	.string "Rustboro is a city of stone. I grew up\n"
	.string "thinking that meant it would never\l"
	.string "change.\p"
	.string "This morning the floor of my Gym began\n"
	.string "to grow crystals too. I watched it\l"
	.string "bloom.\p"
	.string "I can't tell if I'm frightened or\n"
	.string "delighted. Let a battle decide!$"

Nexus_Text_Roxanne_Terapagos_ChampionDefeat3:
	.string "Delighted, I think. Mostly.$"

Nexus_Text_Roxanne_Terapagos_ChampionAfter3:
	.string "{SPEAKER NAME_ROXANNE}The old builders of Rustboro used to\n"
	.string "say that stone is patient.\p"
	.string "They were right. It was patient for a\n"
	.string "very long time. It was only waiting to be\l"
	.string "asked.\p"
	.string "Go on. Whatever it asks you to become,\n"
	.string "take a moment before you answer.$"
```

</details>

#### Uxie

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Roxanne_Uxie_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Roxanne é a **campeã**, a luta logo antes do Uxie. A fala é sobre a criatura, sem dizer o nome dela.

Para uma professora, o pior não é perder: é o aluno que esquece tudo o que ela ensinou. Por isso a Roxanne escreve tudo. A criatura do lago apaga a memória de quem a encara, e mesmo assim passa o tempo inteiro de olhos fechados. A virada: aquilo que podia tomar todas as lembranças escolhe não olhar, e a Roxanne chama isso de boas maneiras. E admite, como professora, que às vezes o aluno precisa esquecer uma coisa para aprendê-la direito.

**Antes da luta**

> Don't look at it. The creature on the lake. If it opens its eyes, you forget. That's what the old texts say.
>
> I've taught for years. What I fear most isn't losing. It's a student who forgets everything I said.
>
> So I write it all down. Everything. Just in case.
>
> …Now, let's make a memory worth writing!

**Derrota**

> Noted. Underlined twice.

**Depois da luta**

> Did you notice? It keeps its eyes closed. The whole time.
>
> It could take every memory we have, and it chooses not to look. I think that is a kind of manners.
>
> A good teacher does the same, now and then. Some things a student has to forget, to learn them properly.
>
> …That goes in the notebook, too. Go on.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Roxanne_Uxie_ChampionIntro:
	.string "Don't look at it. The creature on the\n"
	.string "lake. If it opens its eyes, you forget.\l"
	.string "That's what the old texts say.\p"
	.string "I've taught for years. What I fear\n"
	.string "most isn't losing. It's a student who\l"
	.string "forgets everything I said.\p"
	.string "So I write it all down. Everything. Just\n"
	.string "in case.\p"
	.string "…Now, let's make a memory worth\n"
	.string "writing!$"

Nexus_Text_Roxanne_Uxie_ChampionDefeat:
	.string "Noted. Underlined twice.$"

Nexus_Text_Roxanne_Uxie_ChampionAfter:
	.string "{SPEAKER NAME_ROXANNE}Did you notice? It keeps its eyes\n"
	.string "closed. The whole time.\p"
	.string "It could take every memory we have,\n"
	.string "and it chooses not to look. I think\l"
	.string "that is a kind of manners.\p"
	.string "A good teacher does the same, now and\n"
	.string "then. Some things a student has to\l"
	.string "forget, to learn them properly.\p"
	.string "…That goes in the notebook, too. Go on.$"
```

</details>

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mais duas falas de campeão para esta criatura, sem dizer o nome dela ([R16](../NEXUS_REGRAS.md)); a variação 1 é a que está no jogo.

**Variação 2** — a folha que voltou em branco do lago.

**Antes da luta**

> I dropped a page of my notes into the lake. When I pulled it out, it was blank.
>
> Not wet. Not smudged. Blank. As if I had never written it.
>
> I can't remember what was on it. That frightens me more than any battle. …Let us begin.

**Derrota**

> I'll write this one on the inside cover. Away from the water.

**Depois da luta**

> I've been thinking. Perhaps the page wasn't taken. Perhaps it was returned.
>
> Things I learned wrongly, handed back so I can learn them again. A good teacher does that with a red pen.
>
> Go on. If you forget anything in there, I'll lend you my notes.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Roxanne_Uxie_ChampionIntro2:
	.string "I dropped a page of my notes into the\n"
	.string "lake. When I pulled it out, it was blank.\p"
	.string "Not wet. Not smudged. Blank. As if I had\n"
	.string "never written it.\p"
	.string "I can't remember what was on it. That\n"
	.string "frightens me more than any battle. …Let\l"
	.string "us begin.$"

Nexus_Text_Roxanne_Uxie_ChampionDefeat2:
	.string "I'll write this one on the inside cover.\n"
	.string "Away from the water.$"

Nexus_Text_Roxanne_Uxie_ChampionAfter2:
	.string "{SPEAKER NAME_ROXANNE}I've been thinking. Perhaps the page\n"
	.string "wasn't taken. Perhaps it was returned.\p"
	.string "Things I learned wrongly, handed back\n"
	.string "so I can learn them again. A good\l"
	.string "teacher does that with a red pen.\p"
	.string "Go on. If you forget anything in there,\n"
	.string "I'll lend you my notes.$"
```

</details>

**Variação 3** — a letra que ela não reconhece no próprio caderno (aceno leve ao fio da mão que muda).

**Antes da luta**

> Some pages in my notebook are in handwriting I don't recognize. Neat, but hurried.
>
> They describe battles I don't remember. Very good battles. Very careful notes.
>
> Either I've forgotten, or someone else has been writing in my book. Let's settle one question today!

**Derrota**

> Settled. This one I'll remember myself.

**Depois da luta**

> The one on the lake keeps what people forget. I asked it to give my missing days back.
>
> It didn't open its eyes. I think that was an answer.
>
> Perhaps some things are better kept by someone else. …I'll still check. Go on.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Roxanne_Uxie_ChampionIntro3:
	.string "Some pages in my notebook are in\n"
	.string "handwriting I don't recognize. Neat,\l"
	.string "but hurried.\p"
	.string "They describe battles I don't\n"
	.string "remember. Very good battles. Very\l"
	.string "careful notes.\p"
	.string "Either I've forgotten, or someone else\n"
	.string "has been writing in my book. Let's\l"
	.string "settle one question today!$"

Nexus_Text_Roxanne_Uxie_ChampionDefeat3:
	.string "Settled. This one I'll remember myself.$"

Nexus_Text_Roxanne_Uxie_ChampionAfter3:
	.string "{SPEAKER NAME_ROXANNE}The one on the lake keeps what people\n"
	.string "forget. I asked it to give my missing\l"
	.string "days back.\p"
	.string "It didn't open its eyes. I think that\n"
	.string "was an answer.\p"
	.string "Perhaps some things are better kept by\n"
	.string "someone else. …I'll still check. Go on.$"
```

</details>

Falante novo: `SP_NAME_ROXANNE` (não existe ainda em `include/constants/speaker_names.h`).
