# Blue/Green

**Região da ficha:** Kanto

Aparece no checklist como:

- **Blue/Green** (Kanto · Rivais e protagonistas) — rival de Red, primeiro Campeão enfrentado pelo jogador e futuro Líder de Viridian.
- **Blue — Campeão** (Kanto · Elite Four e Campeões) — conquista o título pouco antes da chegada de Red.
- **Blue** (Alola · Outros notáveis) — veterano, chefe da Battle Tree e antigo Campeão.

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
| `OBJ_EVENT_GFX_BLUE` | `graphics/object_events/pics/people/gym_leaders/blue.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_LEADER_BLUE` | `graphics/trainers/front_pics/leader_blue.png` |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_BLUE` | 595 | 0x753 | Rhyperior Lv69, Pidgeot Lv68, Machamp Lv67, Exeggutor Lv68, Tyranitar Lv68, Arcanine Lv69 | `SaffronCity_FightingDojoVIP`, `ViridianCity_Gym`, `src/battle_dome.c` |

IDs aposentados na limpeza de treinadores (não reaproveitar sem necessidade): `TRAINER_UNUSED_386` (ex-`TRAINER_BLUE_2`, 282).

### Time das Rift Missions

✅ **Implementado em 27/09/2026** (a proposta abaixo virou código): `TRAINER_NEXUS_BLUE` = **986** (flag de batalha `0x8DA`, limpa antes e depois de cada luta), bloco em `src/data/trainers.party`, nível pelo R2 (tabela em `src/data/nexus/trainers.h`). Fala genérica `Nexus_EventScript_Blue_Fight`; campeão: `Nexus_EventScript_Blue_Victini_ChampionFight` (para Victini), `Nexus_EventScript_Blue_Zacian_ChampionFight` (para Zacian). Tudo em `data/scripts/nexus.inc`, sem blackout, resultado em `VAR_TEMP_3`. Para testar: menu de debug → Rift Missions… → Nexus fights… → Blue.

📝 **Proposta de 27/09/2026, aguardando o autor.** `TRAINER_NEXUS_BLUE`, campeão de Zacian e Victini. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler).

Lendário **Zacian**, o herói de Galar que venceu a Darkest Day e viu os reis levarem a estátua; é o Blue, que foi Campeão por um instante e só é lembrado por quem o tirou de lá. Semi-lendário **Victini**, o Pokémon da vitória, porque o Blue quer ganhar mais do que qualquer coisa. Mega **Pidgeot** (Flyingite), o Pokémon dele desde Pallet Town. Mais Gyarados, Rhyperior e Alakazam, do time de Viridian (HGSS e o `TRAINER_BLUE` da campanha). É um time de quem quer vencer rápido e na frente de todo mundo.

*Plano (Singles):* o Alakazam abre com Focus Sash e cobre quatro tipos; o Gyarados entra com Intimidate e sobe Dragon Dance; a Mega Pidgeot atira Hurricane com No Guard (nunca erra) e volta com Roost; o Zacian entra com a Rusted Sword (vira Crowned, o Iron Head vira Behemoth Blade), Swords Dance e limpa; o Victini de Choice Scarf pega quem sobrou com V-create e sai com U-turn.

*Plano (Doubles):* a Mega Pidgeot põe Tailwind e usa Heat Wave; o Rhyperior (Solid Rock + Weakness Policy) espalha Rock Slide com o vento a favor; o Gyarados baixa o ataque dos dois lados com Intimidate; o Alakazam tem Dazzling Gleam. O Rhyperior usa High Horsepower (alvo único) em vez de Earthquake para não acertar o parceiro.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Zacian | Rusted Sword | Intrepid Sword | Jolly | Iron Head, Play Rough, Close Combat, Swords Dance |
| Victini | Choice Scarf | Victory Star | Jolly | V-create, Wild Charge, Zen Headbutt, U-turn |
| Pidgeot | Flyingite | Keen Eye | Timid | Hurricane, Heat Wave, Tailwind, Roost |
| Gyarados | Lum Berry | Intimidate | Jolly | Dragon Dance, Waterfall, Crunch, Taunt |
| Rhyperior | Weakness Policy | Solid Rock | Adamant | Rock Slide, High Horsepower, Megahorn, Protect |
| Alakazam | Focus Sash | Magic Guard | Timid | Psychic, Dazzling Gleam, Shadow Ball, Focus Blast |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>dev_scripts/nexus_validar_time.py</code>: trainerproc, constantes, learnsets e categorias)</summary>

```
=== TRAINER_NEXUS_BLUE ===
Name: Blue
Class: Leader
Pic: Leader Blue
Gender: Male
Music: Male
Double Battle: No
AI: Smart Trainer

Zacian @ Rusted Sword
Jolly Nature
Level: 100
Ability: Intrepid Sword
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Iron Head
- Play Rough
- Close Combat
- Swords Dance

Victini @ Choice Scarf
Jolly Nature
Level: 100
Ability: Victory Star
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- V-create
- Wild Charge
- Zen Headbutt
- U-turn

Pidgeot @ Flyingite
Timid Nature
Level: 100
Ability: Keen Eye
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Hurricane
- Heat Wave
- Tailwind
- Roost

Gyarados @ Lum Berry
Jolly Nature
Level: 100
Ability: Intimidate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Dragon Dance
- Waterfall
- Crunch
- Taunt

Rhyperior @ Weakness Policy
Adamant Nature
Level: 100
Ability: Solid Rock
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Rock Slide
- High Horsepower
- Megahorn
- Protect

Alakazam @ Focus Sash
Timid Nature
Level: 100
Ability: Magic Guard
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Psychic
- Dazzling Gleam
- Shadow Ball
- Focus Blast
```

</details>

### Lendário associado

#### Zacian

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_Zacian_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Zacian**. Blue é o campeão dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Blue, o rival de Red, neto do Professor Oak. Chegou ao topo da Liga de Kanto antes de Red e foi Campeão só até Red subir a escada. Anos depois virou Líder de Viridian.

**A criatura.** Zacian, o Pokémon Guerreiro, é o herói lendário de Galar. Com Zamazenta, venceu a Darkest Day; a história oficial deu o crédito a dois jovens que viraram reis, e as estátuas são deles. A espada enferrujada (Rusted Sword) é o que o transforma na forma Crowned.

**O fragmento.** Um campo de batalha que acabou há muito tempo. Espadas enferrujadas fincadas na grama em fileiras, como plantação. No fim do campo, a estátua de um rei segurando uma espada, e a espada da estátua é a única coisa ali que não enferrujou.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A battlefield that had been over for a very long time.
>
> Rusted swords stood in the grass in rows, like a crop. At the far end, a stone king held a sword of his own, the only blade in the field without a spot of rust.

**Boss**

> One of the rusted swords pulled itself out of the ground.
>
> It was held in the jaws of something that had been waiting, very patiently, for someone to notice who really won.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md))

> File L-888. Warrior.
>
> A field where the kings got the statues and the true hero got the rust. And a young man who was Champion for one afternoon.
>
> What came home with you is a pup, and its sword is not even rusted yet. Nobody will build it a statue.
>
> He said that is fine. He said it twice, so I believe him once.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Zacian_Arrival:
	.string "A battlefield that had been over for a\n"
	.string "very long time.\p"
	.string "Rusted swords stood in the grass in\n"
	.string "rows, like a crop. At the far end, a\l"
	.string "stone king held a sword of his own, the\l"
	.string "only blade in the field without a spot\l"
	.string "of rust.$"

Nexus_Text_Zacian_Boss:
	.string "One of the rusted swords pulled itself\n"
	.string "out of the ground.\p"
	.string "It was held in the jaws of something\n"
	.string "that had been waiting, very patiently,\l"
	.string "for someone to notice who really won.$"

Nexus_Text_Zacian_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-888. Warrior.\p"
	.string "A field where the kings got the\n"
	.string "statues and the true hero got the\l"
	.string "rust. And a young man who was Champion\l"
	.string "for one afternoon.\p"
	.string "What came home with you is a pup, and\n"
	.string "its sword is not even rusted yet.\l"
	.string "Nobody will build it a statue.\p"
	.string "He said that is fine. He said it twice,\n"
	.string "so I believe him once.$"
```

</details>

#### Victini

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_Victini_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Victini**. Blue é o campeão dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** O mesmo Blue: quer vencer mais do que qualquer coisa, e é o único treinador de Kanto que conhece o gosto de chegar em segundo lugar ao Red.

**A criatura.** Victini, o Pokémon da Vitória, gera energia sem limite dentro de si e a divide com quem toca; diz-se que o treinador que o tem vence qualquer batalha. Em Black/White ele vive trancado no porão do farol de Liberty Garden, uma ilhota ao largo de Castelia.

**O fragmento.** Uma ilha pequena com um farol apagado. A cada passo o chão parece mais leve, como se quisesse que você ganhasse. Tudo ali foi feito para entregar a vitória a quem chega.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A small island, and a lighthouse with its lamp dark.
>
> Every step you took felt lighter than the one before, as if the ground itself wanted you to win.

**Boss**

> The lighthouse lamp came on by itself.
>
> Something small sat in the light, holding up two fingers in a V. It was warm enough to feel from the shore.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md))

> File L-494. Victory.
>
> An island that hands out wins, and a young man who would hate to be handed one.
>
> What came back with you is small, and warm, and sleeps a great deal. It has not decided who to let win yet.
>
> I asked him if he wanted it. He said he wants to earn the next one. Then he said, 'Smell ya later.'

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Victini_Arrival:
	.string "A small island, and a lighthouse with\n"
	.string "its lamp dark.\p"
	.string "Every step you took felt lighter than\n"
	.string "the one before, as if the ground itself\l"
	.string "wanted you to win.$"

Nexus_Text_Victini_Boss:
	.string "The lighthouse lamp came on by itself.\p"
	.string "Something small sat in the light,\n"
	.string "holding up two fingers in a V. It was\l"
	.string "warm enough to feel from the shore.$"

Nexus_Text_Victini_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-494. Victory.\p"
	.string "An island that hands out wins, and a\n"
	.string "young man who would hate to be handed\l"
	.string "one.\p"
	.string "What came back with you is small, and\n"
	.string "warm, and sleeps a great deal. It has\l"
	.string "not decided who to let win yet.\p"
	.string "I asked him if he wanted it. He said he\n"
	.string "wants to earn the next one. Then he\l"
	.string "said, 'Smell ya later.'$"
```

</details>

### Diálogo genérico

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Blue_Fight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Blue cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala de si, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

**Antes da luta**

> Hey! Wherever this is, I got here first. That's how it always goes with me.
>
> You're not Red, but you'll do. Gramps always said I should battle people who aren't him once in a while.
>
> Let's go! I'll show you why I'm the greatest!

**Derrota**

> What?! Unbelievable! …Okay, fine. Smell ya later!

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Blue_Intro:
	.string "Hey! Wherever this is, I got here first.\n"
	.string "That's how it always goes with me.\p"
	.string "You're not Red, but you'll do. Gramps\n"
	.string "always said I should battle people who\l"
	.string "aren't him once in a while.\p"
	.string "Let's go! I'll show you why I'm the\n"
	.string "greatest!$"

Nexus_Text_Blue_Defeat:
	.string "What?! Unbelievable! …Okay, fine. Smell\n"
	.string "ya later!$"
```

</details>

### Diálogo associado ao lendário

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Blue é o **campeão**, a luta logo antes do lendário. A fala é sobre a criatura, sem dizer o nome dela ([R16](../NEXUS_REGRAS.md)).

#### Zacian

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Blue_Zacian_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

O Blue fala de crédito, que é a ferida dele: foi Campeão pelo tempo que o Red levou para subir a escada, e ninguém lembra. A criatura é o herói de verdade cuja glória ficou com os reis, e mesmo assim continuou guardando. O Blue teria feito escândalo e mandado consertar a placa. A virada é ele perceber que talvez seja por isso que ela é a lenda e ele não.

**Antes da luta**

> Did you see the statue out there? The king got the credit. The one that actually fought got a rusty sword.
>
> I was Champion once, you know. For about as long as it took Red to walk up the stairs.
>
> Nobody remembers that. Believe me, I do.
>
> So let's make this one count!

**Derrota**

> Beaten again… and nobody's even watching.

**Depois da luta**

> Here's what bugs me. That wolf doesn't care. The kings got the statues, and it just… kept guarding.
>
> Me? I'd have been furious. I'd have made them fix the plaque.
>
> Maybe that's why it's the legend, and I'm the guy who was Champion for an afternoon.
>
> Go on. Win it fair. Somebody should.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Blue_Zacian_ChampionIntro:
	.string "Did you see the statue out there? The\n"
	.string "king got the credit. The one that\l"
	.string "actually fought got a rusty sword.\p"
	.string "I was Champion once, you know. For\n"
	.string "about as long as it took Red to walk up\l"
	.string "the stairs.\p"
	.string "Nobody remembers that. Believe me, I\n"
	.string "do.\p"
	.string "So let's make this one count!$"

Nexus_Text_Blue_Zacian_ChampionDefeat:
	.string "Beaten again… and nobody's even\n"
	.string "watching.$"

Nexus_Text_Blue_Zacian_ChampionAfter:
	.string "{SPEAKER NAME_BLUE}Here's what bugs me. That wolf doesn't\n"
	.string "care. The kings got the statues, and it\l"
	.string "just… kept guarding.\p"
	.string "Me? I'd have been furious. I'd have\n"
	.string "made them fix the plaque.\p"
	.string "Maybe that's why it's the legend, and\n"
	.string "I'm the guy who was Champion for an\l"
	.string "afternoon.\p"
	.string "Go on. Win it fair. Somebody should.$"
```

</details>

#### Victini

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Blue_Victini_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

O Blue carrega um desses no próprio time (o Victini dele entra em todo dia do Nexus), e a lenda diz que quem o tem não perde. Ele perdeu mesmo assim, para o Red. Então ou não funciona, ou a criatura nunca gostou dele. A virada: ele fica aliviado. Se um dia vencer o Red, quer que seja ele, não um amuleto de orelhas compridas. E pede para ninguém contar ao avô que ele disse algo sensato.

**Antes da luta**

> Heard about the little guy on the island? It hands out wins. Whoever it likes just can't lose.
>
> Know what? I've been carrying one this whole time. Took it all the way to the top.
>
> Still came in second to Red.
>
> So either it doesn't work, or it never liked me. Let's find out!

**Derrota**

> …Yeah. Figured it was the second one.

**Depois da luta**

> Real talk? I'm glad it doesn't work on me.
>
> If I ever beat Red, I want it to be me. Not luck. Not some lucky charm with big ears.
>
> …Don't tell Gramps I said anything that sensible.
>
> Go get your win. The real kind. Smell ya later!

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Blue_Victini_ChampionIntro:
	.string "Heard about the little guy on the\n"
	.string "island? It hands out wins. Whoever it\l"
	.string "likes just can't lose.\p"
	.string "Know what? I've been carrying one this\n"
	.string "whole time. Took it all the way to the\l"
	.string "top.\p"
	.string "Still came in second to Red.\p"
	.string "So either it doesn't work, or it never\n"
	.string "liked me. Let's find out!$"

Nexus_Text_Blue_Victini_ChampionDefeat:
	.string "…Yeah. Figured it was the second one.$"

Nexus_Text_Blue_Victini_ChampionAfter:
	.string "{SPEAKER NAME_BLUE}Real talk? I'm glad it doesn't work on\n"
	.string "me.\p"
	.string "If I ever beat Red, I want it to be me.\n"
	.string "Not luck. Not some lucky charm with big\l"
	.string "ears.\p"
	.string "…Don't tell Gramps I said anything\n"
	.string "that sensible.\p"
	.string "Go get your win. The real kind. Smell ya\n"
	.string "later!$"
```

</details>

Falante novo: `SP_NAME_BLUE` (ainda não existe em `include/constants/speaker_names.h`).
