# Wally

**Região da ficha:** Hoenn

Aparece no checklist como:

- **Wally** (Hoenn · Rivais) — jovem inicialmente frágil que se torna um treinador habilidoso com Gallade ou Gardevoir.

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
| `OBJ_EVENT_GFX_WALLY` | `graphics/object_events/pics/people/wally.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_WALLY` | `graphics/trainers/front_pics/wally.png` |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_WALLY_VR_3` | 658 | 0x792 | **sem time** (ID reservado, sem bloco no `.party`) | — (nenhum script chama) |
| `TRAINER_WALLY_VR_4` | 659 | 0x793 | **sem time** (ID reservado, sem bloco no `.party`) | — (nenhum script chama) |
| `TRAINER_WALLY_VR_5` | 660 | 0x794 | **sem time** (ID reservado, sem bloco no `.party`) | — (nenhum script chama) |

IDs aposentados na limpeza de treinadores (não reaproveitar sem necessidade): `TRAINER_UNUSED_473` (ex-`TRAINER_WALLY_VR_1`, 519), `TRAINER_UNUSED_445` (ex-`TRAINER_WALLY_MAUVILLE`, 656), `TRAINER_UNUSED_446` (ex-`TRAINER_WALLY_VR_2`, 657).

### Time das Rift Missions

✅ **Implementado em 27/09/2026** (a proposta abaixo virou código): `TRAINER_NEXUS_WALLY` = **1014** (flag de batalha `0x8F6`, limpa antes e depois de cada luta), bloco em `src/data/trainers.party`, nível pelo R2 (tabela em `src/data/nexus/trainers.h`). Fala genérica `Nexus_EventScript_Wally_Fight`; campeão: `Nexus_EventScript_Wally_Azelf_ChampionFight` (para Azelf), `Nexus_EventScript_Wally_IronValiant_ChampionFight` (para Iron Valiant). Tudo em `data/scripts/nexus.inc`, sem blackout, resultado em `VAR_TEMP_3`. Para testar: menu de debug → Rift Missions… → Nexus fights… → Wally.

📝 **Proposta de 27/09/2026, aguardando o autor.** `TRAINER_NEXUS_WALLY`, campeão do Azelf e do Iron Valiant. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler).

Lendário **Xerneas**, o Pokémon da vida: o menino doente que se mudou para Verdanturf pelo ar puro e voltou para a Victory Road cheio de fôlego. Semi-lendário **Iron Valiant**, o Paradoxo do qual ele é campeão, que tem traços de Gardevoir e de Gallade, o futuro de ferro do Ralts dele. Mega **Gallade** (Psychite), o ás dele em Omega Ruby/Alpha Sapphire. Mais **Altaria**, **Roserade** e **Magnezone**, do time dele na Victory Road de ORAS. Fada e Psíquico na frente; o Magnezone (Magnet Pull) prende os Aço que seguram Fada.

*Plano:* Geomancy de um turno. O Xerneas segura Power Herb, e com Fairy Aura cada Moonblast e Dazzling Gleam pesa o dobro depois do +2.
*Plano (Singles):* a Roserade (Focus Sash) espalha Toxic Spikes e põe um alvo para dormir; a Altaria queima atacantes físicos com Will-O-Wisp e se cura com Roost; o Xerneas faz Geomancy e varre; a Mega Gallade (Sharpness) sobe Swords Dance como segundo limpador.
*Plano (Doubles):* o formato em que o time brilha. A Altaria abre com Tailwind; o Xerneas faz Geomancy no mesmo turno e depois usa Dazzling Gleam nos dois oponentes; o Iron Valiant (Booster Energy) derruba com Close Combat e Spirit Break; a Roserade tira um oponente com Sleep Powder.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Xerneas | Power Herb | Fairy Aura | Modest | Geomancy, Moonblast, Dazzling Gleam, Focus Blast |
| Iron Valiant | Booster Energy | Quark Drive | Naive | Moonblast, Close Combat, Spirit Break, Knock Off |
| Gallade | Psychite | Sharpness | Jolly | Sacred Sword, Psycho Cut, Leaf Blade, Swords Dance |
| Altaria | Leftovers | Natural Cure | Bold | Tailwind, Draco Meteor, Roost, Will-O-Wisp |
| Roserade | Focus Sash | Natural Cure | Timid | Sleep Powder, Sludge Bomb, Giga Drain, Toxic Spikes |
| Magnezone | Choice Specs | Magnet Pull | Modest | Thunderbolt, Flash Cannon, Volt Switch, Tri Attack |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>nexus_validar_time.py</code>: trainerproc, constantes, learnsets e categorias)</summary>

```
=== TRAINER_NEXUS_WALLY ===
Name: Wally
Class: Pkmn Trainer 1
Pic: Wally
Gender: Male
Music: Male
Double Battle: Yes
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

Iron Valiant @ Booster Energy
Naive Nature
Level: 100
Ability: Quark Drive
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Moonblast
- Close Combat
- Spirit Break
- Knock Off

Gallade @ Psychite
Jolly Nature
Level: 100
Ability: Sharpness
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Sacred Sword
- Psycho Cut
- Leaf Blade
- Swords Dance

Altaria @ Leftovers
Bold Nature
Level: 100
Ability: Natural Cure
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Tailwind
- Draco Meteor
- Roost
- Will-O-Wisp

Roserade @ Focus Sash
Timid Nature
Level: 100
Ability: Natural Cure
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Sleep Powder
- Sludge Bomb
- Giga Drain
- Toxic Spikes

Magnezone @ Choice Specs
Modest Nature
Level: 100
Ability: Magnet Pull
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Thunderbolt
- Flash Cannon
- Volt Switch
- Tri Attack
```

</details>

### Lendário associado

#### Azelf

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_Azelf_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Azelf**. Wally é o campeão dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Wally, o menino frágil de Petalburg que pegou o primeiro Ralts com a ajuda do jogador, mudou-se para Verdanturf pelo ar puro e reapareceu forte na Victory Road.

**A criatura.** Azelf (Psíquico), o Ser da Força de Vontade, que dorme no fundo do Lake Valor e mantém o equilíbrio do mundo. Em Diamond/Pearl, a bomba da Team Galactic secou o Lake Valor e deixou só os Magikarp se debatendo na lama.

**O fragmento.** Um lago sem água: lama rachada e uma cratera no meio, como se alguma coisa tivesse explodido. Nas últimas poças, Magikarp ainda se debatem, e nenhum desistiu.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A lake with no water in it. Only cracked mud, and a crater in the middle, as if something had exploded.
>
> In the last puddles, Magikarp were still flopping. Not one of them had given up.

**Boss**

> The mud at the bottom of the crater stirred.
>
> Something small and blue rose out of it, and every Magikarp went still, as if listening.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md))

> File L-482. Willpower.
>
> A lake blown dry, and a boy who once could not climb a hill without resting.
>
> What came back with you is tiny and will not stay put. Neither will he. I have stopped trying to keep them in one place.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Azelf_Arrival:
	.string "A lake with no water in it. Only cracked\n"
	.string "mud, and a crater in the middle, as if\l"
	.string "something had exploded.\p"
	.string "In the last puddles, Magikarp were still\n"
	.string "flopping. Not one of them had given up.$"

Nexus_Text_Azelf_Boss:
	.string "The mud at the bottom of the crater\n"
	.string "stirred.\p"
	.string "Something small and blue rose out of it,\n"
	.string "and every Magikarp went still, as if\l"
	.string "listening.$"

Nexus_Text_Azelf_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-482. Willpower.\p"
	.string "A lake blown dry, and a boy who once\n"
	.string "could not climb a hill without resting.\p"
	.string "What came back with you is tiny and will\n"
	.string "not stay put. Neither will he. I have\l"
	.string "stopped trying to keep them in one\l"
	.string "place.$"
```

</details>

#### Iron Valiant

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_IronValiant_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Iron Valiant**. Wally é o campeão dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Wally, o menino frágil de Petalburg que pegou o primeiro Ralts com a ajuda do jogador, mudou-se para Verdanturf pelo ar puro e reapareceu forte na Victory Road.

**A criatura.** Iron Valiant (Fada/Lutador) é um Paradoxo: tem traços de Gardevoir e de Gallade ao mesmo tempo, todo de metal, e talvez seja o Pokémon citado com esse nome num livro antigo. Vem de um futuro possível pela máquina do tempo da Area Zero. Mundo em Violet.

**O fragmento.** Um jardim de flores de metal, perfeitamente paradas, debaixo de uma luz sem sol. Nada ali cresce, nada murcha; tudo foi terminado há muito tempo.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A garden of metal flowers, perfectly still, under a light with no sun behind it.
>
> Nothing here grew. Nothing here wilted. Everything had been finished a long time ago.

**Boss**

> Something walked through the flowers without bending a single one.
>
> It had a blade on each arm and a gown of steel, and it did not breathe.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md))

> File L-1006. Paradox.
>
> A garden where nothing ever tires, and a boy who knows exactly what being tired is worth.
>
> What came back with you is small and warm, and it yawned. Machines do not yawn. I have written that down twice.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_IronValiant_Arrival:
	.string "A garden of metal flowers, perfectly\n"
	.string "still, under a light with no sun behind\l"
	.string "it.\p"
	.string "Nothing here grew. Nothing here wilted.\n"
	.string "Everything had been finished a long\l"
	.string "time ago.$"

Nexus_Text_IronValiant_Boss:
	.string "Something walked through the flowers\n"
	.string "without bending a single one.\p"
	.string "It had a blade on each arm and a gown of\n"
	.string "steel, and it did not breathe.$"

Nexus_Text_IronValiant_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-1006. Paradox.\p"
	.string "A garden where nothing ever tires, and a\n"
	.string "boy who knows exactly what being tired\l"
	.string "is worth.\p"
	.string "What came back with you is small and\n"
	.string "warm, and it yawned. Machines do not\l"
	.string "yawn. I have written that down twice.$"
```

</details>


### Diálogo genérico

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Wally_Fight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Wally cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala dele mesmo, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

**Antes da luta**

> Oh! H-hi. Sorry, I'm still catching my breath. I always am.
>
> When I was little, I couldn't walk up a hill without resting. Now I climb them for fun.
>
> My Pokémon did that. Let me show you!

**Derrota**

> Hah… hah… I lost, but I'm still standing. That's new.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Wally_Intro:
	.string "Oh! H-hi. Sorry, I'm still catching my\n"
	.string "breath. I always am.\p"
	.string "When I was little, I couldn't walk up a\n"
	.string "hill without resting. Now I climb them\l"
	.string "for fun.\p"
	.string "My Pokémon did that. Let me show you!$"

Nexus_Text_Wally_Defeat:
	.string "Hah… hah… I lost, but I'm still\n"
	.string "standing. That's new.$"
```

</details>


### Diálogo associado ao lendário

#### Azelf

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Wally_Azelf_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Wally é o **campeão**, a luta logo antes do Azelf. A fala é sobre a criatura, sem dizer o nome dela.

O Wally não consegue passar pelos Magikarp se debatendo no lago seco: todo mundo passa reto, e eles continuam tentando. Quando o Azelf olhou para ele, sentiu que conseguia correr uma milha, e ele nunca correu uma milha. A virada é a definição dele de força de vontade: não é gritar e nunca desistir, é sair da cama nos dias em que respirar dói, e ninguém vê esses dias. Ele acha que a criatura lhe deu isso há muito tempo e que nunca agradeceu. Pede ao jogador que agradeça por ele.

**Antes da luta**

> The lake out there is gone. Just mud and a crater, and Magikarp flopping in the puddles.
>
> Everyone walks past them. I couldn't. They're still trying.
>
> Something lives in the crater. When it looked at me, I felt like I could run a mile. I've never run a mile.
>
> L-let's battle! Before the feeling wears off!

**Derrota**

> It wore off. …No. It didn't, actually.

**Depois da luta**

> People think willpower is shouting and never giving up.
>
> It isn't. It's getting out of bed on the days breathing hurts. Nobody sees those days.
>
> That creature gave people the will to do things. I think it gave me mine, a long time ago, and I never thanked it.
>
> Would you? When you get there. Just say Wally says thanks.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Wally_Azelf_ChampionIntro:
	.string "The lake out there is gone. Just mud and\n"
	.string "a crater, and Magikarp flopping in the\l"
	.string "puddles.\p"
	.string "Everyone walks past them. I couldn't.\n"
	.string "They're still trying.\p"
	.string "Something lives in the crater. When it\n"
	.string "looked at me, I felt like I could run a\l"
	.string "mile. I've never run a mile.\p"
	.string "L-let's battle! Before the feeling\n"
	.string "wears off!$"

Nexus_Text_Wally_Azelf_ChampionDefeat:
	.string "It wore off. …No. It didn't, actually.$"

Nexus_Text_Wally_Azelf_ChampionAfter:
	.string "{SPEAKER NAME_WALLY}People think willpower is shouting and\n"
	.string "never giving up.\p"
	.string "It isn't. It's getting out of bed on\n"
	.string "the days breathing hurts. Nobody sees\l"
	.string "those days.\p"
	.string "That creature gave people the will to\n"
	.string "do things. I think it gave me mine, a\l"
	.string "long time ago, and I never thanked it.\p"
	.string "Would you? When you get there. Just say\n"
	.string "Wally says thanks.$"
```

</details>

#### Iron Valiant

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Wally_IronValiant_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Wally é o **campeão**, a luta logo antes do Iron Valiant. A fala é sobre a criatura, sem dizer o nome dela.

O Wally vê no Iron Valiant o rosto do parceiro dele: meio lâmina, meio vestido, tudo de metal, talvez do futuro em que ninguém mais fica cansado nem doente. Ele contou: a criatura não respirou nenhuma vez. A virada: ele já quis um corpo assim, que nunca perdesse o fôlego. Mas ele e o parceiro se cansam juntos, e é assim que ele sabe que os dois escolheram continuar. Quem nunca se cansa nunca precisa escolher; ele não inveja mais.

**Antes da luta**

> There's a Pokémon out there with my partner's face. Half blade, half gown. All made of metal.
>
> They say it's from a future. Maybe the one where nobody gets tired or sick anymore.
>
> It didn't breathe once while I watched. I counted.
>
> …Sorry. Let's battle. I need to know my partner is still mine.

**Derrota**

> Hah… hah… we're tired. Both of us. Good.

**Depois da luta**

> I used to wish I had a body like that. One that never ran out of breath.
>
> But my partner and I get tired together. That's how I know we chose to keep going.
>
> Something that never gets tired never has to choose. I don't think I envy it anymore.
>
> Go on. Be kind to it, if you can.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Wally_IronValiant_ChampionIntro:
	.string "There's a Pokémon out there with my\n"
	.string "partner's face. Half blade, half gown.\l"
	.string "All made of metal.\p"
	.string "They say it's from a future. Maybe the\n"
	.string "one where nobody gets tired or sick\l"
	.string "anymore.\p"
	.string "It didn't breathe once while I watched.\n"
	.string "I counted.\p"
	.string "…Sorry. Let's battle. I need to know my\n"
	.string "partner is still mine.$"

Nexus_Text_Wally_IronValiant_ChampionDefeat:
	.string "Hah… hah… we're tired. Both of us. Good.$"

Nexus_Text_Wally_IronValiant_ChampionAfter:
	.string "{SPEAKER NAME_WALLY}I used to wish I had a body like that.\n"
	.string "One that never ran out of breath.\p"
	.string "But my partner and I get tired\n"
	.string "together. That's how I know we chose\l"
	.string "to keep going.\p"
	.string "Something that never gets tired never\n"
	.string "has to choose. I don't think I envy it\l"
	.string "anymore.\p"
	.string "Go on. Be kind to it, if you can.$"
```

</details>

Falante novo: `SP_NAME_WALLY` (o `_ChampionAfter` usa `{SPEAKER NAME_WALLY}`; ainda não existe em `include/constants/speaker_names.h`, skill `nomear-falante`).
