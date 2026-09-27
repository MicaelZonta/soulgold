# Erika

**Região da ficha:** Kanto

Aparece no checklist como:

- **Erika — Grama** (Kanto · Líderes de Ginásio) — elegante Líder de Celadon e especialista em plantas.

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
| `OBJ_EVENT_GFX_ERIKA` | `graphics/object_events/pics/people/gym_leaders/erika.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_LEADER_ERIKA` | `graphics/trainers/front_pics/erika.png` |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_ERIKA` | 303 | 0x62F | Jumpluff Lv61, Roserade Lv60, Tangrowth Lv60, Venusaur Lv61, Victreebel Lv62, Bellossom Lv62 | `CeladonCity_Gym`, `SaffronCity_FightingDojoVIP`, `src/battle_dome.c`, `src/battle_setup.c` |

### Time das Rift Missions

📝 **Proposta de 27/09/2026, aguardando o autor.** `TRAINER_NEXUS_ERIKA`, campeã de Shaymin e Virizion. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler). `Double Battle: Yes` é o formato em que o time brilha mais; o plano vale nos dois.

Lendário **Xerneas**, o Pokémon da vida, que espalha vida em volta com Geomancy: é o jardim da Erika no tamanho de uma lenda. Semi-lendário **Shaymin**, de quem ela é campeã, o ouriço que limpa o ar envenenado e deixa flores. Mega **Venusaur** (Grasstite), a Grama clássica de Kanto e o Venusaur que já está no time dela na campanha. Mais **Bellossom** (a assinatura dela em HGSS), **Jumpluff** e **Tangrowth** (do time de campanha; o Tangela é dela desde o Red/Blue). *Plano (Singles):* sono e dreno. O Jumpluff abre com Sleep Powder e Leech Seed e sai de U-turn; o Tangrowth (Regenerator, Assault Vest) segura o físico; a Power Herb faz o Geomancy do Xerneas num turno só; a Bellossom sobe com Quiver Dance e se cura com Strength Sap. *Plano (Doubles):* Jumpluff dá Tailwind e põe um alvo para dormir no mesmo turno; Xerneas bate Dazzling Gleam nos dois depois do Geomancy; a Bellossom com Healer cura o status do parceiro; o Tangrowth usa Rock Slide nos dois.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Xerneas | Power Herb | Fairy Aura | Modest | Geomancy, Moonblast, Dazzling Gleam, Focus Blast |
| Shaymin | Leftovers | Natural Cure | Timid | Seed Flare, Earth Power, Leech Seed, Synthesis |
| Venusaur | Grasstite | Chlorophyll | Bold | Giga Drain, Sludge Bomb, Sleep Powder, Synthesis |
| Bellossom | Sitrus Berry | Healer | Modest | Quiver Dance, Giga Drain, Moonblast, Strength Sap |
| Jumpluff | Focus Sash | Infiltrator | Jolly | Sleep Powder, Tailwind, Leech Seed, U-turn |
| Tangrowth | Assault Vest | Regenerator | Sassy | Power Whip, Knock Off, Rock Slide, Sludge Bomb |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>dev_scripts/nexus_validar_time.py</code>)</summary>

```
=== TRAINER_NEXUS_ERIKA ===
Name: Erika
Class: Leader
Pic: Leader Erika
Gender: Female
Music: Female
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

Shaymin @ Leftovers
Timid Nature
Level: 100
Ability: Natural Cure
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Seed Flare
- Earth Power
- Leech Seed
- Synthesis

Venusaur @ Grasstite
Bold Nature
Level: 100
Ability: Chlorophyll
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Giga Drain
- Sludge Bomb
- Sleep Powder
- Synthesis

Bellossom @ Sitrus Berry
Modest Nature
Level: 100
Ability: Healer
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Quiver Dance
- Giga Drain
- Moonblast
- Strength Sap

Jumpluff @ Focus Sash
Jolly Nature
Level: 100
Ability: Infiltrator
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Sleep Powder
- Tailwind
- Leech Seed
- U-turn

Tangrowth @ Assault Vest
Sassy Nature
Level: 100
Ability: Regenerator
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Power Whip
- Knock Off
- Rock Slide
- Sludge Bomb
```

</details>


### Lendário associado

#### Shaymin

📝 **Proposta de 27/09/2026, aguardando o autor.** **Shaymin**. Erika é a campeã dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Erika, Líder de Celadon, especialista em Grama. Educada, cochila no meio da conversa, vende perfume e ensina arranjo de flores; o ginásio dela tem uma árvore na porta que só quem tem Cut atravessa.

**A criatura.** Shaymin, o Pokémon da gratidão. Absorve as toxinas do ar e da terra e transforma chão arruinado num campo de flores. Tímido: se enrola e se disfarça de moita. Com a flor Gracidea vira a Forma Céu e sai voando.

**O fragmento.** Um campo de cinza sob céu cinza, ar com gosto de fumaça. Atravessando tudo, uma trilha estreita de flores frescas, como pegadas. Onde a trilha termina, o ar ainda está ficando limpo.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário). Pelo [R17](../NEXUS_REGRAS.md), o que o jogador leva é o fragmento que sobra, no nível 1; a ficha do Looker fala desse pedaço, não da criatura domada.

**Chegada**

> A field of grey ash under a grey sky. Nothing grew, and the air tasted of smoke.
>
> But a thin line of fresh flowers ran across it, bright as footprints.

**Boss**

> The flowers at your feet shivered.
>
> Something small rose out of the grass, and the grey air around it was already turning clear.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento**

> File L-492. Gratitude.
>
> A dead field, and a small thing walking across it, leaving flowers behind.
>
> The woman who sells perfume in Celadon asked me who it was thanking. I had no answer.
>
> What came back with you is very small, and asleep inside a blossom. She says that is how they begin.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Shaymin_Arrival:
	.string "A field of grey ash under a grey sky.\n"
	.string "Nothing grew, and the air tasted of\l"
	.string "smoke.\p"
	.string "But a thin line of fresh flowers ran\n"
	.string "across it, bright as footprints.$"

Nexus_Text_Shaymin_Boss:
	.string "The flowers at your feet shivered.\p"
	.string "Something small rose out of the grass,\n"
	.string "and the grey air around it was already\l"
	.string "turning clear.$"

Nexus_Text_Shaymin_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-492. Gratitude.\p"
	.string "A dead field, and a small thing walking\n"
	.string "across it, leaving flowers behind.\p"
	.string "The woman who sells perfume in Celadon\n"
	.string "asked me who it was thanking. I had no\l"
	.string "answer.\p"
	.string "What came back with you is very small,\n"
	.string "and asleep inside a blossom. She says\l"
	.string "that is how they begin.$"
```

</details>


#### Virizion

📝 **Proposta de 27/09/2026, aguardando o autor.** **Virizion**. Erika é a campeã dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Erika, Líder de Celadon: gentil, sonolenta, a mulher que planta uma árvore na porta do próprio ginásio para que só quem sabe cortá-la entre.

**A criatura.** Virizion, o Pokémon da pradaria, uma das Espadas da Justiça. Com Cobalion e Terrakion, protegeu os Pokémon cujos lares foram destruídos por uma guerra dos humanos. Os chifres são lâminas, e ela se move rápida e graciosa como o vento.

**O fragmento.** Uma campina de capim alto, e dentro dela lâminas velhas: espadas e pontas de lança enferrujadas, com flores nascendo delas. Alguma coisa lutou ali uma vez, e alguma coisa venceu. O capim se abre em linha reta, como cortado.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário). Pelo [R17](../NEXUS_REGRAS.md), o que o jogador leva é o fragmento que sobra, no nível 1; a ficha do Looker fala desse pedaço, não da criatura domada.

**Chegada**

> A meadow of tall grass. Hidden in it lay old blades, swords and spearheads rusted through, with flowers growing out of them.
>
> Something had fought here once. Something had won.

**Boss**

> The grass parted in a straight line toward you, as if cut.
>
> At the end of it stood a green shape with horns like drawn blades, between you and the small Pokémon hiding in the grass.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento**

> File L-640. Grassland.
>
> A meadow that remembers a war, and a guardian who never left it.
>
> A gentle Gym Leader stood between us and it today, and it allowed her.
>
> What followed you home is small and all legs. It already stands in front of your other Pokémon. Old habits.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Virizion_Arrival:
	.string "A meadow of tall grass. Hidden in it lay\n"
	.string "old blades, swords and spearheads\l"
	.string "rusted through, with flowers growing\l"
	.string "out of them.\p"
	.string "Something had fought here once.\n"
	.string "Something had won.$"

Nexus_Text_Virizion_Boss:
	.string "The grass parted in a straight line\n"
	.string "toward you, as if cut.\p"
	.string "At the end of it stood a green shape\n"
	.string "with horns like drawn blades, between\l"
	.string "you and the small Pokémon hiding in the\l"
	.string "grass.$"

Nexus_Text_Virizion_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-640. Grassland.\p"
	.string "A meadow that remembers a war, and a\n"
	.string "guardian who never left it.\p"
	.string "A gentle Gym Leader stood between us\n"
	.string "and it today, and it allowed her.\p"
	.string "What followed you home is small and all\n"
	.string "legs. It already stands in front of your\l"
	.string "other Pokémon. Old habits.$"
```

</details>


### Diálogo genérico

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Erika cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala dela mesma, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

**Antes da luta**

> Oh, my… Please forgive me. I must have dozed off.
>
> I always keep a seed in my sleeve, in case a place has no flowers. This one had none, so I planted it.
>
> It is already sprouting. How rude of me to keep it waiting. Shall we?

**Derrota**

> You pruned my arrangement down to the stem. It's lovely that way, too.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Erika_Intro:
	.string "Oh, my… Please forgive me. I must have\n"
	.string "dozed off.\p"
	.string "I always keep a seed in my sleeve, in\n"
	.string "case a place has no flowers. This one\l"
	.string "had none, so I planted it.\p"
	.string "It is already sprouting. How rude of me\n"
	.string "to keep it waiting. Shall we?$"

Nexus_Text_Erika_Defeat:
	.string "You pruned my arrangement down to the\n"
	.string "stem. It's lovely that way, too.$"
```

</details>


### Diálogo associado ao lendário

#### Shaymin

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Erika é a **campeã**, a luta logo antes do Shaymin. A fala é sobre a criatura, sem dizer o nome dela.

A Erika vende perfume em Celadon: o perfume cobre o cheiro da cidade, nunca o tira. A criatura faz o contrário: respira o veneno e devolve um campo. A virada é o que isso revela da Erika, uma vida inteira cobrindo as coisas com algo bonito. Na derrota ela é elegante como sempre. Depois, o conselho prático (é tímida, se disfarça de moita, ande devagar) e a pergunta que fica: dizem que ela aparece para agradecer alguém, e a Erika não sabe a quem ela mesma deveria agradecer. Começa pelo jogador.

**Antes da luta**

> Did you see the little one covered in flowers? Everywhere it walks, the grey air goes clear and something blooms.
>
> In Celadon, I sell perfume. It hides the smell of the city. It has never once removed it.
>
> That little one breathes the poison in… and gives back a whole field.
>
> I have spent my life covering things up. Let me see if I can do more than that.

**Derrota**

> You grew right through me. How lovely. I'm not even cross.

**Depois da luta**

> It is terribly shy. If you run at it, it will curl up and pretend to be a bush.
>
> Walk slowly. Let it smell you first.
>
> The old stories say it appears to thank someone. I keep wondering whom I ought to thank.
>
> I suppose I will start with you. Thank you. Now go gently.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Erika_Shaymin_ChampionIntro:
	.string "Did you see the little one covered in\n"
	.string "flowers? Everywhere it walks, the grey\l"
	.string "air goes clear and something blooms.\p"
	.string "In Celadon, I sell perfume. It hides the\n"
	.string "smell of the city. It has never once\l"
	.string "removed it.\p"
	.string "That little one breathes the poison in…\n"
	.string "and gives back a whole field.\p"
	.string "I have spent my life covering things up.\n"
	.string "Let me see if I can do more than that.$"

Nexus_Text_Erika_Shaymin_ChampionDefeat:
	.string "You grew right through me. How lovely.\n"
	.string "I'm not even cross.$"

Nexus_Text_Erika_Shaymin_ChampionAfter:
	.string "{SPEAKER NAME_ERIKA}It is terribly shy. If you run at it, it\n"
	.string "will curl up and pretend to be a bush.\p"
	.string "Walk slowly. Let it smell you first.\p"
	.string "The old stories say it appears to thank\n"
	.string "someone. I keep wondering whom I ought\l"
	.string "to thank.\p"
	.string "I suppose I will start with you. Thank\n"
	.string "you. Now go gently.$"
```

</details>


#### Virizion

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Erika é a **campeã**, a luta logo antes do Virizion. A fala é sobre a criatura, sem dizer o nome dela.

A Erika viu a criatura passar pelo capim: os chifres cortaram as hastes e nenhuma flor caiu. Ela sabe a história (protegia os Pokémon de gente que queimava campos) e a virada é o olhar: a criatura olhou para ela, não para os Pokémon dela, porque ela é gente. A derrota: um corte limpo que não machucou pétala. Depois, a comparação com a árvore da porta do ginásio de Celadon: a Erika deixa entrar quem sabe cortar; aquilo fica na porta e decide. Se decidir contra você, não discuta: mostre que não veio queimar nada.

**Antes da luta**

> Something came through the grass a moment ago. So quick. Its horns cut the stems, and not one flower fell.
>
> They say it protected Pokémon from people who burned their fields, long ago.
>
> It looked at me as it passed. Not at my Pokémon. At me.
>
> I think I understand why. Please… help me earn a kinder look.

**Derrota**

> A clean cut. It didn't bruise a single petal.

**Depois da luta**

> My Gym has a small tree at the door. Anyone who can cut it may come in. I planted it that way.
>
> That creature is the opposite. It stands at the door and decides.
>
> If it decides against you, don't argue. Just show it you did not come here to burn anything.
>
> …And please don't cut its grass on the way in.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Erika_Virizion_ChampionIntro:
	.string "Something came through the grass a\n"
	.string "moment ago. So quick. Its horns cut the\l"
	.string "stems, and not one flower fell.\p"
	.string "They say it protected Pokémon from\n"
	.string "people who burned their fields, long\l"
	.string "ago.\p"
	.string "It looked at me as it passed. Not at my\n"
	.string "Pokémon. At me.\p"
	.string "I think I understand why. Please… help\n"
	.string "me earn a kinder look.$"

Nexus_Text_Erika_Virizion_ChampionDefeat:
	.string "A clean cut. It didn't bruise a single\n"
	.string "petal.$"

Nexus_Text_Erika_Virizion_ChampionAfter:
	.string "{SPEAKER NAME_ERIKA}My Gym has a small tree at the door.\n"
	.string "Anyone who can cut it may come in. I\l"
	.string "planted it that way.\p"
	.string "That creature is the opposite. It\n"
	.string "stands at the door and decides.\p"
	.string "If it decides against you, don't argue.\n"
	.string "Just show it you did not come here to\l"
	.string "burn anything.\p"
	.string "…And please don't cut its grass on the\n"
	.string "way in.$"
```

</details>


Falante novo: `SP_NAME_ERIKA` (ainda não existe em `include/constants/speaker_names.h`).
