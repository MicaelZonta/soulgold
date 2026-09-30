# Erika

**Região da ficha:** Kanto

Aparece no checklist como:

- **Erika — Grama** (Kanto · Líderes de Ginásio) — elegante Líder de Celadon e especialista em plantas.

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

✅ **Implementado em 27/09/2026** (a proposta abaixo virou código): `TRAINER_NEXUS_ERIKA` = **990** (flag de batalha `0x8DE`, limpa antes e depois de cada luta), bloco em `src/data/trainers.party`, nível pelo R2 (tabela em `src/data/nexus/trainers.h`). Fala genérica `Nexus_EventScript_Erika_Fight`; campeão: `Nexus_EventScript_Erika_Virizion_ChampionFight` (para Virizion), `Nexus_EventScript_Erika_Shaymin_ChampionFight` (para Shaymin). Tudo em `data/scripts/nexus.inc`, sem blackout, resultado em `VAR_TEMP_3`. Para testar: menu de debug → Rift Missions… → Nexus fights… → Erika.

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

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_Shaymin_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

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

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_Virizion_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

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

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Erika_Fight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

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


#### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mais duas falas genéricas para Erika, com a variação 1 (acima, já no jogo) formam as três do sorteio. Mesmo registro do [R16](../NEXUS_REGRAS.md): fala de si, sem citar o lugar nem a criatura do dia.

**Variação 2 — o cochilo como talento.** Humor: a fama de dormir no meio da luta, virada do avesso. Ela acorda exatamente quando importa.

**Antes da luta**

> Mm… Is it morning? I was dreaming of my Gym. All my trainers were asleep too, and no one noticed.
>
> People say I nap through battles and still win. That is only half true.
>
> The other half is that I wake up exactly when it matters. …Right about now, I think.

**Derrota**

> Oh dear. I woke up a moment too late.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Erika_Intro2:
	.string "Mm… Is it morning? I was dreaming of my\n"
	.string "Gym. All my trainers were asleep too, and\l"
	.string "no one noticed.\p"
	.string "People say I nap through battles and\n"
	.string "still win. That is only half true.\p"
	.string "The other half is that I wake up\n"
	.string "exactly when it matters. …Right about\l"
	.string "now, I think.$"

Nexus_Text_Erika_Defeat2:
	.string "Oh dear. I woke up a moment too late.$"
```

</details>

**Variação 3 — o cheiro de fumaça.** O que ela perdeu no fragmento dela (R21): uma cidade que ficou cinza enquanto ela regava um jardim de telhado. Não cita lugar do Nexus nem lendário; é a vida dela. Prepara o diário.

**Antes da luta**

> Excuse me. Do I smell of smoke? I washed and washed, but it followed me here.
>
> Where I'm from, I kept a garden on a rooftop. I watered it every morning while the city below went grey.
>
> A garden that small can't save anything. It can only remind you. …Let me remind you, then.

**Derrota**

> Then I shall go and water something. It always helps.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Erika_Intro3:
	.string "Excuse me. Do I smell of smoke? I\n"
	.string "washed and washed, but it followed me\l"
	.string "here.\p"
	.string "Where I'm from, I kept a garden on a\n"
	.string "rooftop. I watered it every morning\l"
	.string "while the city below went grey.\p"
	.string "A garden that small can't save\n"
	.string "anything. It can only remind you. …Let\l"
	.string "me remind you, then.$"

Nexus_Text_Erika_Defeat3:
	.string "Then I shall go and water something. It\n"
	.string "always helps.$"
```

</details>


### Diálogo associado ao lendário

#### Shaymin

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Erika_Shaymin_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

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


##### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mais duas falas de campeão para este lendário; com a variação 1 (acima, já no jogo) formam as três. Sobre a criatura, sem dizer o nome dela; só o `ChampionAfter` leva plaquinha.

**Variação 2 — a flor da gratidão.** Lembrança de arranjadora de flores: ela ofereceu à criatura a flor rosa que se dá para agradecer, e viu a criatura mudar de forma e voar. Guardou uma semente dessa flor na manga (liga com a semente da fala genérica 1).

**Antes da luta**

> I brought it a flower. A pink one, the kind people give to say thank you.
>
> It sniffed the petals, and all at once its shape changed, lighter, winged, and it was gone into the grey sky.
>
> I have arranged flowers my whole life. I never once saw one make something fly.
>
> …I would like to try again. After you, of course.

**Derrota**

> You arranged that better than I ever could.

**Depois da luta**

> That flower only blooms where someone is grateful. Where I'm from, it stopped blooming for years.
>
> I kept one seed. I kept it in my sleeve and told no one.
>
> If the little one flies from you, don't chase it. Look up and say thank you. It always comes down for that.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Erika_Shaymin_ChampionIntro2:
	.string "I brought it a flower. A pink one, the\n"
	.string "kind people give to say thank you.\p"
	.string "It sniffed the petals, and all at once\n"
	.string "its shape changed, lighter, winged, and\l"
	.string "it was gone into the grey sky.\p"
	.string "I have arranged flowers my whole life. I\n"
	.string "never once saw one make something fly.\p"
	.string "…I would like to try again. After you, of\n"
	.string "course.$"

Nexus_Text_Erika_Shaymin_ChampionDefeat2:
	.string "You arranged that better than I ever\n"
	.string "could.$"

Nexus_Text_Erika_Shaymin_ChampionAfter2:
	.string "{SPEAKER NAME_ERIKA}That flower only blooms where someone\n"
	.string "is grateful. Where I'm from, it stopped\l"
	.string "blooming for years.\p"
	.string "I kept one seed. I kept it in my sleeve\n"
	.string "and told no one.\p"
	.string "If the little one flies from you, don't\n"
	.string "chase it. Look up and say thank you. It\l"
	.string "always comes down for that.$"
```

</details>

**Variação 3 — a soneca e a culpa.** Humor que vira confissão: as duas cochilaram juntas, e só a criatura fez algo útil dormindo. Depois a Erika admite que deixou construírem por cima da campina de Celadon ("eu estava dormindo, em mais de um sentido") — o segredo do diário, dito pela metade.

**Antes da luta**

> I found it asleep in a flower bed, so I lay down beside it. We napped together for, oh, an hour.
>
> When I woke, the dead grass under me was green. So was the whole field.
>
> I have never done anything useful in my sleep. It does everything useful in its sleep.
>
> Forgive me. I am a little jealous. Shall we?

**Derrota**

> Mm… Wake me when it blooms again.

**Depois da luta**

> Before the grey came, there was a meadow behind my city. I picked flowers there for my Gym.
>
> I let them build over it. I was asleep, I suppose. In more ways than one.
>
> That little one walks over what we ruined and never asks who did it. It simply mends it.
>
> Be kind to it. It has been kinder to us than we deserve.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Erika_Shaymin_ChampionIntro3:
	.string "I found it asleep in a flower bed, so I\n"
	.string "lay down beside it. We napped together\l"
	.string "for, oh, an hour.\p"
	.string "When I woke, the dead grass under me\n"
	.string "was green. So was the whole field.\p"
	.string "I have never done anything useful in my\n"
	.string "sleep. It does everything useful in its\l"
	.string "sleep.\p"
	.string "Forgive me. I am a little jealous. Shall\n"
	.string "we?$"

Nexus_Text_Erika_Shaymin_ChampionDefeat3:
	.string "Mm… Wake me when it blooms again.$"

Nexus_Text_Erika_Shaymin_ChampionAfter3:
	.string "{SPEAKER NAME_ERIKA}Before the grey came, there was a\n"
	.string "meadow behind my city. I picked flowers\l"
	.string "there for my Gym.\p"
	.string "I let them build over it. I was asleep, I\n"
	.string "suppose. In more ways than one.\p"
	.string "That little one walks over what we\n"
	.string "ruined and never asks who did it. It\l"
	.string "simply mends it.\p"
	.string "Be kind to it. It has been kinder to us\n"
	.string "than we deserve.$"
```

</details>



#### Virizion

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Erika_Virizion_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

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


##### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mais duas falas de campeão para este lendário; com a variação 1 (acima, já no jogo) formam as três. Sobre a criatura, sem dizer o nome dela; só o `ChampionAfter` leva plaquinha.

**Variação 2 — a raiva.** A Erika brava, uma vez: homens de preto puseram fogo atrás do ginásio (a Rocket do Game Corner de Celadon). Ela ficou uma semana com raiva e achou cansativo; a criatura está com raiva há séculos e não cansa. Depois, a lenda das três espadas: ela é a rápida, a última a chegar e a primeira a ir.

**Antes da luta**

> I do not often get angry. Once, men in black set a fire behind my Gym.
>
> I was angry for a whole week. I found it terribly tiring.
>
> The one in the grass has been angry for longer than any city has stood, and it is not tired at all.
>
> …Let me borrow a little of that. Just for this battle.

**Derrota**

> Oh. You were angrier. Or perhaps only braver.

**Depois da luta**

> Long ago it fought beside two others, one of steel and one of stone. It was the swift one.
>
> The swift one is always the last to arrive and the first to be gone. I understand. I am usually late.
>
> When it rushes you, don't flinch. To that creature, flinching looks like guilt.
>
> …And forgive it if it cuts your hat. It is never on purpose.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Erika_Virizion_ChampionIntro2:
	.string "I do not often get angry. Once, men in\n"
	.string "black set a fire behind my Gym.\p"
	.string "I was angry for a whole week. I found it\n"
	.string "terribly tiring.\p"
	.string "The one in the grass has been angry for\n"
	.string "longer than any city has stood, and it\l"
	.string "is not tired at all.\p"
	.string "…Let me borrow a little of that. Just\n"
	.string "for this battle.$"

Nexus_Text_Erika_Virizion_ChampionDefeat2:
	.string "Oh. You were angrier. Or perhaps only\n"
	.string "braver.$"

Nexus_Text_Erika_Virizion_ChampionAfter2:
	.string "{SPEAKER NAME_ERIKA}Long ago it fought beside two others,\n"
	.string "one of steel and one of stone. It was\l"
	.string "the swift one.\p"
	.string "The swift one is always the last to\n"
	.string "arrive and the first to be gone. I\l"
	.string "understand. I am usually late.\p"
	.string "When it rushes you, don't flinch. To\n"
	.string "that creature, flinching looks like\l"
	.string "guilt.\p"
	.string "…And forgive it if it cuts your hat. It\n"
	.string "is never on purpose.$"
```

</details>

**Variação 3 — o arranjo de espadas.** O ofício dela diante do fragmento: as espadas enferrujadas com flores nascendo delas viram um ikebana. A criatura observou para ver o que ela guardaria. No ikebana o espaço vazio importa tanto quanto as flores — e a criatura é espaço vazio que protege.

**Antes da luta**

> There are old swords in the grass here, rusted through. Flowers grow out of every one.
>
> I have been arranging them. A blade here, a bloom there. It is what I do when I don't know what else to do.
>
> The green one watched me the whole time. I think it wanted to see which I would keep.
>
> I kept both. Let us see if that was right.

**Derrota**

> Both, then. I shall keep both.

**Depois da luta**

> In flower arranging, the empty space matters as much as the flowers.
>
> That creature is all empty space. It doesn't stay. It doesn't hold. It stands only where it is needed.
>
> When it is gone, the space it leaves is what protects the little ones.
>
> Please leave that space empty for it. Don't fill it with anything of yours.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Erika_Virizion_ChampionIntro3:
	.string "There are old swords in the grass here,\n"
	.string "rusted through. Flowers grow out of\l"
	.string "every one.\p"
	.string "I have been arranging them. A blade\n"
	.string "here, a bloom there. It is what I do when\l"
	.string "I don't know what else to do.\p"
	.string "The green one watched me the whole\n"
	.string "time. I think it wanted to see which I\l"
	.string "would keep.\p"
	.string "I kept both. Let us see if that was\n"
	.string "right.$"

Nexus_Text_Erika_Virizion_ChampionDefeat3:
	.string "Both, then. I shall keep both.$"

Nexus_Text_Erika_Virizion_ChampionAfter3:
	.string "{SPEAKER NAME_ERIKA}In flower arranging, the empty space\n"
	.string "matters as much as the flowers.\p"
	.string "That creature is all empty space. It\n"
	.string "doesn't stay. It doesn't hold. It\l"
	.string "stands only where it is needed.\p"
	.string "When it is gone, the space it leaves is\n"
	.string "what protects the little ones.\p"
	.string "Please leave that space empty for it.\n"
	.string "Don't fill it with anything of yours.$"
```

</details>



Falante novo: `SP_NAME_ERIKA` (ainda não existe em `include/constants/speaker_names.h`).
