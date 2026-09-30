# Karen

**Região da ficha:** Johto

Aparece no checklist como:

- **Karen — Noturno** (Johto · Elite Four e Campeão) — defensora da ideia de vencer usando os Pokémon de que se gosta.

**Pronto para o Nexus:** ✅ sim — tem sprite e battle sprite.

## Checklist

- [x] Sprite de overworld *(obrigatório)*
- [x] Battle sprite / front pic *(obrigatório)*
- [x] Field mugshot (retrato na caixa de diálogo)
- [x] Time para as Rift Missions definido
- [x] Associado a um lendário
- [x] Diálogo genérico escrito
- [x] Diálogo associado ao lendário escrito

## Referências no repositório

### Sprite de overworld

| Constante | Arquivo |
|---|---|
| `OBJ_EVENT_GFX_KAREN` | `graphics/object_events/pics/people/elite_four/karen.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_ELITE_FOUR_KAREN` | `graphics/trainers/front_pics/elite_four_karen.png` |

### Field mugshot

| Constante | Arquivo |
|---|---|
| `MUGSHOT_KAREN` | `graphics/field_mugshots/karen.png` |

Aparece sozinho quando o objeto que fala usa o sprite acima (`GetFieldMugshotIdByObjectGraphicsId`, `src/field_mugshot.c`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_KAREN_3` | 283 | 0x61B | **sem time** (ID reservado, sem bloco no `.party`) | `src/battle_setup.c` |
| `TRAINER_KAREN_4` | 284 | 0x61C | **sem time** (ID reservado, sem bloco no `.party`) | `src/battle_setup.c` |
| `TRAINER_KAREN_5` | 285 | 0x61D | **sem time** (ID reservado, sem bloco no `.party`) | `src/battle_setup.c` |
| `TRAINER_KAREN_1` | 381 | 0x67D | Grimmsnarl Lv70, Absol Lv71, Umbreon Lv70, Kingambit Lv70, Scrafty Lv70, Honchkrow Lv70 · *dupla* · VS: Blue | `PokemonLeague_KarensRoom`, `Route116`, `src/battle_setup.c`, `src/match_call.c` |
| `TRAINER_KAREN_2` | 382 | 0x67E | Grimmsnarl Lv85, Absol Lv85, Umbreon Lv85, Kingambit Lv85, Scrafty Lv85, Honchkrow Lv85 · VS: Blue | `PokemonLeague_KarensRoom`, `src/battle_setup.c` |

### Time das Rift Missions

✅ **Implementado em 27/09/2026** (a proposta abaixo virou código): `TRAINER_NEXUS_KAREN` = **1010** (flag de batalha `0x8F2`, limpa antes e depois de cada luta), bloco em `src/data/trainers.party`, nível pelo R2 (tabela em `src/data/nexus/trainers.h`). Fala genérica `Nexus_EventScript_Karen_Fight`; campeão: `Nexus_EventScript_Karen_GalarianMoltres_ChampionFight` (para Galarian Moltres), `Nexus_EventScript_Karen_Darkrai_ChampionFight` (para Darkrai). Tudo em `data/scripts/nexus.inc`, sem blackout, resultado em `VAR_TEMP_3`. Para testar: menu de debug → Rift Missions… → Nexus fights… → Karen.

📝 **Proposta de 27/09/2026, aguardando o autor.** `TRAINER_NEXUS_KAREN`, campeã do Darkrai e da Moltres de Galar. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler).

Lendário **Darkrai**, do qual ela é campeã: o Pokémon que todo mundo chama de maligno porque dá pesadelos, o caso perfeito para quem defende que "forte e fraco é só a percepção egoísta das pessoas". Semi-lendário **Moltres de Galar** (Sombrio/Voador), a outra criatura de que ela é campeã: o mesmo pássaro das lendas, julgado pela cor. Mega **Houndoom** (Darktite), o ás dela em Gold/Silver/Crystal. Mais **Umbreon**, a assinatura dela, e **Kingambit** e **Grimmsnarl**, da campanha. Sombrio de ponta a ponta, com o Grimmsnarl (Fada) cobrindo Lutador.

*Plano:* Nasty Plot atrás das telas. O Grimmsnarl (Prankster, Light Clay) põe Reflect e Light Screen primeiro; o Darkrai, a Moltres de Galar e a Mega Houndoom sobem Nasty Plot protegidos; a Weakness Policy e o Berserk fazem a Moltres ficar mais perigosa justamente quando apanha; o Kingambit fecha com Sucker Punch e Supreme Overlord quando o resto já caiu.
*Plano (Singles):* telas, depois setup um de cada vez; o Umbreon segura com Wish e Foul Play enquanto o próximo entra.
*Plano (Doubles):* Grimmsnarl dá Fake Out no turno das telas; o Umbreon usa Snarl, que baixa o Sp. Atk dos dois oponentes; Fiery Wrath e Heat Wave acertam os dois lados; Protect na Moltres enquanto o parceiro trabalha.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Darkrai | Life Orb | Bad Dreams | Timid | Dark Pulse, Sludge Bomb, Focus Blast, Nasty Plot |
| Moltres-Galar | Weakness Policy | Berserk | Modest | Fiery Wrath, Hurricane, Nasty Plot, Protect |
| Houndoom | Darktite | Flash Fire | Timid | Heat Wave, Dark Pulse, Sludge Bomb, Nasty Plot |
| Umbreon | Leftovers | Synchronize | Calm | Foul Play, Snarl, Wish, Protect |
| Kingambit | Black Glasses | Supreme Overlord | Adamant | Kowtow Cleave, Sucker Punch, Iron Head, Swords Dance |
| Grimmsnarl | Light Clay | Prankster | Careful | Reflect, Light Screen, Spirit Break, Fake Out |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>nexus_validar_time.py</code>: trainerproc, constantes, learnsets e categorias)</summary>

```
=== TRAINER_NEXUS_KAREN ===
Name: Karen
Class: Elite Four
Pic: Elite Four Karen
Gender: Female
Music: Elite Four
Double Battle: No
AI: Smart Trainer

Darkrai @ Life Orb
Timid Nature
Level: 100
Ability: Bad Dreams
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Dark Pulse
- Sludge Bomb
- Focus Blast
- Nasty Plot

Moltres-Galar @ Weakness Policy
Modest Nature
Level: 100
Ability: Berserk
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Fiery Wrath
- Hurricane
- Nasty Plot
- Protect

Houndoom @ Darktite
Timid Nature
Level: 100
Ability: Flash Fire
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Heat Wave
- Dark Pulse
- Sludge Bomb
- Nasty Plot

Umbreon @ Leftovers
Calm Nature
Level: 100
Ability: Synchronize
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Foul Play
- Snarl
- Wish
- Protect

Kingambit @ Black Glasses
Adamant Nature
Level: 100
Ability: Supreme Overlord
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Kowtow Cleave
- Sucker Punch
- Iron Head
- Swords Dance

Grimmsnarl @ Light Clay
Careful Nature
Level: 100
Ability: Prankster
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Reflect
- Light Screen
- Spirit Break
- Fake Out
```

</details>

### Lendário associado

#### Darkrai

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_Darkrai_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Darkrai**. Karen é a campeã dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Karen, a Sombria da Elite Four de Johto, que responde a quem fala de Pokémon fortes e fracos: "isso é só a percepção egoísta das pessoas; treinadores de verdade tentam vencer com os seus favoritos".

**A criatura.** Darkrai (Sombrio), o Pokémon Breu, ativo nas noites de lua nova. Para proteger o próprio território, faz as pessoas e os Pokémon caírem num sono fundo, cheio de pesadelos. Em Sinnoh, a Lunar Wing da Cresselia é o que desfaz os pesadelos (Canalave e Newmoon Island).

**O fragmento.** Uma cidade de porto numa noite sem lua. Todas as lanternas apagadas; as pessoas de pé nas ruas, de olhos fechados, dormindo em pé, e algumas delas chorando.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A harbor town on a night with no moon.
>
> Every lamp was out. People stood in the streets with their eyes closed, asleep on their feet, and some of them were crying.

**Boss**

> One of the shadows on the pier did not belong to anyone.
>
> It stood up, and all around you the sleepers began to whisper.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md))

> File L-491. Pitch-Black.
>
> A town asleep inside its worst dreams, and a woman who is not afraid of the dark, because she has always lived next to it.
>
> What came back with you sleeps like a child. I checked. It is not dreaming of anything bad.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Darkrai_Arrival:
	.string "A harbor town on a night with no moon.\p"
	.string "Every lamp was out. People stood in the\n"
	.string "streets with their eyes closed, asleep\l"
	.string "on their feet, and some of them were\l"
	.string "crying.$"

Nexus_Text_Darkrai_Boss:
	.string "One of the shadows on the pier did not\n"
	.string "belong to anyone.\p"
	.string "It stood up, and all around you the\n"
	.string "sleepers began to whisper.$"

Nexus_Text_Darkrai_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-491. Pitch-Black.\p"
	.string "A town asleep inside its worst dreams,\n"
	.string "and a woman who is not afraid of the\l"
	.string "dark, because she has always lived next\l"
	.string "to it.\p"
	.string "What came back with you sleeps like a\n"
	.string "child. I checked. It is not dreaming of\l"
	.string "anything bad.$"
```

</details>

#### Galarian Moltres

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_GalarianMoltres_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Galarian Moltres**. Karen é a campeã dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Karen, a Sombria da Elite Four de Johto, que responde a quem fala de Pokémon fortes e fracos: "isso é só a percepção egoísta das pessoas; treinadores de verdade tentam vencer com os seus favoritos".

**A criatura.** A Moltres de Galar (Sombrio/Voador), o Pokémon Malévolo. A aura sinistra, parecida com chamas, consome o espírito de quem ela atinge, e as vítimas viram sombras queimadas de si mesmas. Mundo em Sword/Shield: Crown Tundra.

**O fragmento.** Uma floresta pegando fogo sem fumaça e sem calor. As chamas são roxo-escuras; as árvores que elas tocam continuam de pé, mas cinzentas por dentro, sem vida nenhuma.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A forest, burning. There was no smoke, and no heat.
>
> The flames were dark purple. The trees they touched still stood, but their bark had gone grey, and they no longer looked alive.

**Boss**

> A shadow crossed the treetops, and every flame in the forest leaned toward it.
>
> It landed on a burned-out branch, and the branch did not break. There was nothing left in it to break.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md))

> File L-146. Malevolent.
>
> A forest burned hollow, and a woman who defends things for the very colour people fear.
>
> What came back with you is small, and its flame is still dark. It has not burned anything. I would like the record to show that.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_GalarianMoltres_Arrival:
	.string "A forest, burning. There was no smoke,\n"
	.string "and no heat.\p"
	.string "The flames were dark purple. The trees\n"
	.string "they touched still stood, but their\l"
	.string "bark had gone grey, and they no longer\l"
	.string "looked alive.$"

Nexus_Text_GalarianMoltres_Boss:
	.string "A shadow crossed the treetops, and\n"
	.string "every flame in the forest leaned toward\l"
	.string "it.\p"
	.string "It landed on a burned-out branch, and\n"
	.string "the branch did not break. There was\l"
	.string "nothing left in it to break.$"

Nexus_Text_GalarianMoltres_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-146. Malevolent.\p"
	.string "A forest burned hollow, and a woman who\n"
	.string "defends things for the very colour\l"
	.string "people fear.\p"
	.string "What came back with you is small, and\n"
	.string "its flame is still dark. It has not\l"
	.string "burned anything. I would like the record\l"
	.string "to show that.$"
```

</details>


### Diálogo genérico

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Karen_Fight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Karen cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala dela mesma, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

**Antes da luta**

> I'm Karen. I don't know this place, and I don't need to.
>
> Strong Pokémon. Weak Pokémon. That is only the selfish perception of people. It follows you everywhere, even here.
>
> Show me your favorites. Not your strongest. Your favorites.

**Derrota**

> Your favorites won. As they should.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Karen_Intro:
	.string "I'm Karen. I don't know this place, and\n"
	.string "I don't need to.\p"
	.string "Strong Pokémon. Weak Pokémon. That is\n"
	.string "only the selfish perception of people.\l"
	.string "It follows you everywhere, even here.\p"
	.string "Show me your favorites. Not your\n"
	.string "strongest. Your favorites.$"

Nexus_Text_Karen_Defeat:
	.string "Your favorites won. As they should.$"
```

</details>

#### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mais duas falas para as **quatro primeiras salas** ([R16](../NEXUS_REGRAS.md)): fala de si, sem citar o lugar nem a criatura do dia. A variação 1 é a de cima, que já está no jogo; o sorteio de qual variação toca ainda não existe no código.

**Variação 2** — a lembrança do primeiro Pokémon dela: o que ninguém queria na Day-Care e mordia todo mundo. Lealdade é escolher parar de morder.

**Antes da luta**

> My first Pokémon was the one nobody wanted at the Day-Care. It bit everyone.
>
> It bit me too. Then it stopped. That's all loyalty is, really. Choosing to stop biting.
>
> …Mine won't stop for you, though. Come.

**Derrota**

> Hm. They stopped biting for you. Interesting.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Karen_Intro2:
	.string "My first Pokémon was the one nobody\n"
	.string "wanted at the Day-Care. It bit\l"
	.string "everyone.\p"
	.string "It bit me too. Then it stopped. That's\n"
	.string "all loyalty is, really. Choosing to stop\l"
	.string "biting.\p"
	.string "…Mine won't stop for you, though. Come.$"

Nexus_Text_Karen_Defeat2:
	.string "Hm. They stopped biting for you.\n"
	.string "Interesting.$"
```

</details>

**Variação 3** — a máscara que ela jogou no mar. Alguém disse que ela a faria forte (as crianças mascaradas; o **Pryce** de outro fragmento). R21 com leveza.

**Antes da luta**

> I stay up late. Always have. The night doesn't ask you to be anything.
>
> Someone once gave me a mask and said it would make me strong. I threw it in the sea.
>
> I didn't need it. Let me show you why.

**Derrota**

> …Still didn't need it. Even losing.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Karen_Intro3:
	.string "I stay up late. Always have. The night\n"
	.string "doesn't ask you to be anything.\p"
	.string "Someone once gave me a mask and said it\n"
	.string "would make me strong. I threw it in the\l"
	.string "sea.\p"
	.string "I didn't need it. Let me show you why.$"

Nexus_Text_Karen_Defeat3:
	.string "…Still didn't need it. Even losing.$"
```

</details>

### Diálogo associado ao lendário

#### Darkrai

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Karen_Darkrai_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Karen é a **campeã**, a luta logo antes do Darkrai. A fala é sobre a criatura, sem dizer o nome dela.

A Karen cochilou perto do Darkrai e teve o pesadelo: o Umbreon dela perdia, e uma voz dizia que ele era um Pokémon fraco. A voz era a dela. É a frase contra a qual ela passou a vida inteira discutindo. A leitura dela da criatura: o Darkrai não cria o pesadelo, só apaga a luz para você ver o que já estava lá. E não é maligno; só quer ser deixado em paz no escuro. O conselho: se ele mostrar o seu, não discuta, siga andando.

**Antes da luta**

> I fell asleep out there. Only for a moment.
>
> I dreamed my Umbreon lost, and a voice said it was a weak Pokémon. The voice was mine.
>
> That creature doesn't make the nightmare. It only turns off the light, so you can see what was already there.
>
> Now. Show me what's in yours.

**Derrota**

> …Hm. You wake up fast. I like that.

**Depois da luta**

> People will tell you it's evil. It isn't. It just wants to be left alone in the dark.
>
> Everyone has one sentence they're afraid to hear in their own voice. Mine is the one I've spent my life arguing against.
>
> Go on. If it shows you yours, don't argue. Just keep walking.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Karen_Darkrai_ChampionIntro:
	.string "I fell asleep out there. Only for a\n"
	.string "moment.\p"
	.string "I dreamed my Umbreon lost, and a voice\n"
	.string "said it was a weak Pokémon. The voice\l"
	.string "was mine.\p"
	.string "That creature doesn't make the\n"
	.string "nightmare. It only turns off the light,\l"
	.string "so you can see what was already there.\p"
	.string "Now. Show me what's in yours.$"

Nexus_Text_Karen_Darkrai_ChampionDefeat:
	.string "…Hm. You wake up fast. I like that.$"

Nexus_Text_Karen_Darkrai_ChampionAfter:
	.string "{SPEAKER NAME_KAREN}People will tell you it's evil. It isn't.\n"
	.string "It just wants to be left alone in the\l"
	.string "dark.\p"
	.string "Everyone has one sentence they're\n"
	.string "afraid to hear in their own voice. Mine\l"
	.string "is the one I've spent my life arguing\l"
	.string "against.\p"
	.string "Go on. If it shows you yours, don't\n"
	.string "argue. Just keep walking.$"
```

</details>

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mais duas falas de campeão para este lendário ([R16](../NEXUS_REGRAS.md)), sem dizer o nome da espécie. A variação 1 é a de cima, que já está no jogo.

**Variação 2** — a pena da ilha da lua cheia (a Lunar Wing) que devia acordar a cidade e ninguém trouxe. Talvez ninguém deva: quem dorme perto da criatura não envelhece. Ela protege de algo pior que sonho (a Moltres de Galar, fio do diário).

**Antes da luta**

> Everyone here is asleep except me. I'm told that's rude. I'm told a lot of things.
>
> There's supposed to be a feather, from an island where the moon is always full. It wakes people.
>
> Nobody brought it. Maybe nobody should. Battle first.

**Derrota**

> …You're awake, at least. That makes two of us.

**Depois da luta**

> I asked it once why it won't let them wake. It didn't answer. It never does.
>
> But the ones who sleep near it don't grow any older. I checked. Every night.
>
> …Maybe it's protecting them from something worse than dreams. Go and ask it for me.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Karen_Darkrai_ChampionIntro2:
	.string "Everyone here is asleep except me. I'm\n"
	.string "told that's rude. I'm told a lot of\l"
	.string "things.\p"
	.string "There's supposed to be a feather, from\n"
	.string "an island where the moon is always full.\l"
	.string "It wakes people.\p"
	.string "Nobody brought it. Maybe nobody should.\n"
	.string "Battle first.$"

Nexus_Text_Karen_Darkrai_ChampionDefeat2:
	.string "…You're awake, at least. That makes two\n"
	.string "of us.$"

Nexus_Text_Karen_Darkrai_ChampionAfter2:
	.string "{SPEAKER NAME_KAREN}I asked it once why it won't let them\n"
	.string "wake. It didn't answer. It never does.\p"
	.string "But the ones who sleep near it don't\n"
	.string "grow any older. I checked. Every night.\p"
	.string "…Maybe it's protecting them from\n"
	.string "something worse than dreams. Go and\l"
	.string "ask it for me.$"
```

</details>

**Variação 3** — o Umbreon: os anéis brilham na lua, e aqui não há lua, então brilham sozinhos, como se ele fosse a lua de todo mundo. O escuro não é inimigo da luz; é onde a luz serve.

**Antes da luta**

> My Umbreon's rings glow under the moon. Here there's no moon, so they glow on their own.
>
> Faintly. Like it's trying to be the moon for everyone asleep in this town.
>
> That one out there does the opposite. It turns everything off. Let's see who's brighter.

**Derrota**

> …You. Tonight, anyway.

**Depois da luta**

> Dark isn't the enemy of light. It's where light gets to be useful.
>
> That one knows it. It's why it stays. Something has to be dark here.
>
> Go on. Take a little light with you. Not too much. It doesn't like being stared at.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Karen_Darkrai_ChampionIntro3:
	.string "My Umbreon's rings glow under the moon.\n"
	.string "Here there's no moon, so they glow on\l"
	.string "their own.\p"
	.string "Faintly. Like it's trying to be the moon\n"
	.string "for everyone asleep in this town.\p"
	.string "That one out there does the opposite.\n"
	.string "It turns everything off. Let's see\l"
	.string "who's brighter.$"

Nexus_Text_Karen_Darkrai_ChampionDefeat3:
	.string "…You. Tonight, anyway.$"

Nexus_Text_Karen_Darkrai_ChampionAfter3:
	.string "{SPEAKER NAME_KAREN}Dark isn't the enemy of light. It's\n"
	.string "where light gets to be useful.\p"
	.string "That one knows it. It's why it stays.\n"
	.string "Something has to be dark here.\p"
	.string "Go on. Take a little light with you. Not\n"
	.string "too much. It doesn't like being stared\l"
	.string "at.$"
```

</details>

#### Galarian Moltres

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Karen_GalarianMoltres_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Karen é a **campeã**, a luta logo antes da Galarian Moltres. A fala é sobre a criatura, sem dizer o nome dela.

A Karen olha para a Moltres de Galar como olha para os Pokémon dela: é o mesmo pássaro das histórias antigas, que lá é fogo e esperança, e aqui tem a cor de um hematoma e é chamado de perverso. Mesmas asas, outro céu. A virada é que ela não gosta da criatura por ser escura: gosta porque ela nunca tentou ser a outra. Podia ter passado a vida pedindo desculpas pela cor; preferiu queimar. O aviso é concreto: o fogo dela leva o espírito, não o corpo.

**Antes da luta**

> There's a bird out there that burns without heat. Everything its flames touch keeps standing… but it's empty inside.
>
> In the old stories, the same bird is fire and hope. Here it's the colour of a bruise, and people call it wicked.
>
> Same wings. Different sky. That's all it is.
>
> Let's see if you judge by colour too.

**Derrota**

> You didn't flinch at the dark. Good.

**Depois da luta**

> I don't love it because it's dark. I love it because it never tried to be the other one.
>
> It could have spent its life apologizing for its colour. It burned instead.
>
> Be careful. Its fire takes the spirit, not the body. Keep yours.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Karen_GalarianMoltres_ChampionIntro:
	.string "There's a bird out there that burns\n"
	.string "without heat. Everything its flames\l"
	.string "touch keeps standing… but it's empty\l"
	.string "inside.\p"
	.string "In the old stories, the same bird is fire\n"
	.string "and hope. Here it's the colour of a\l"
	.string "bruise, and people call it wicked.\p"
	.string "Same wings. Different sky. That's all it\n"
	.string "is.\p"
	.string "Let's see if you judge by colour too.$"

Nexus_Text_Karen_GalarianMoltres_ChampionDefeat:
	.string "You didn't flinch at the dark. Good.$"

Nexus_Text_Karen_GalarianMoltres_ChampionAfter:
	.string "{SPEAKER NAME_KAREN}I don't love it because it's dark. I\n"
	.string "love it because it never tried to be the\l"
	.string "other one.\p"
	.string "It could have spent its life apologizing\n"
	.string "for its colour. It burned instead.\p"
	.string "Be careful. Its fire takes the spirit,\n"
	.string "not the body. Keep yours.$"
```

</details>

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mais duas falas de campeão para este lendário ([R16](../NEXUS_REGRAS.md)), sem dizer o nome da espécie. A variação 1 é a de cima, que já está no jogo.

**Variação 2** — o Houndoom: as pessoas recuam do fogo e fogem quando veem que é preto. A ave recebe o mesmo tratamento, pior. Depois: as árvores queimadas ficam de pé — o único fogo que não derruba nada. Mas ficar de pé não é viver.

**Antes da luta**

> My Houndoom breathes fire, and people back away. Then they see it's black, and they run.
>
> That bird gets the same treatment. Worse. In its own land, mothers use it to scare children.
>
> …I'd like a word with those mothers. You'll do for now.

**Derrota**

> Hm. You didn't run. My Houndoom noticed.

**Depois da luta**

> Look at the trees it burned. Still standing. Grey inside, but standing.
>
> People call that cruel. I think it's the only fire in the world that doesn't knock anything down.
>
> …Just don't stand in it too long. Standing isn't the same as living.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Karen_GalarianMoltres_ChampionIntro2:
	.string "My Houndoom breathes fire, and people\n"
	.string "back away. Then they see it's black,\l"
	.string "and they run.\p"
	.string "That bird gets the same treatment.\n"
	.string "Worse. In its own land, mothers use it to\l"
	.string "scare children.\p"
	.string "…I'd like a word with those mothers.\n"
	.string "You'll do for now.$"

Nexus_Text_Karen_GalarianMoltres_ChampionDefeat2:
	.string "Hm. You didn't run. My Houndoom noticed.$"

Nexus_Text_Karen_GalarianMoltres_ChampionAfter2:
	.string "{SPEAKER NAME_KAREN}Look at the trees it burned. Still\n"
	.string "standing. Grey inside, but standing.\p"
	.string "People call that cruel. I think it's the\n"
	.string "only fire in the world that doesn't\l"
	.string "knock anything down.\p"
	.string "…Just don't stand in it too long.\n"
	.string "Standing isn't the same as living.$"
```

</details>

**Variação 3** — a confissão: a ave assusta a Karen, não por ser escura, mas porque olha como quem já sabe quanto você vale. Ela encarou de volta, e a ave desviou primeiro.

**Antes da luta**

> I'll admit something, since only the trees are listening. That bird scares me.
>
> Not because it's dark. Because it looks at you like it already knows what you're worth.
>
> …I don't like being measured. Let me measure you instead.

**Derrota**

> …You're worth plenty. There. Now you know.

**Depois da luta**

> It measured me when I arrived. It stared. I stared back, for a long time.
>
> Then it looked away. First time anything has ever looked away from me first.
>
> Go and stare it down. Don't blink. It respects that. So do I.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Karen_GalarianMoltres_ChampionIntro3:
	.string "I'll admit something, since only the\n"
	.string "trees are listening. That bird scares\l"
	.string "me.\p"
	.string "Not because it's dark. Because it looks\n"
	.string "at you like it already knows what\l"
	.string "you're worth.\p"
	.string "…I don't like being measured. Let me\n"
	.string "measure you instead.$"

Nexus_Text_Karen_GalarianMoltres_ChampionDefeat3:
	.string "…You're worth plenty. There. Now you\n"
	.string "know.$"

Nexus_Text_Karen_GalarianMoltres_ChampionAfter3:
	.string "{SPEAKER NAME_KAREN}It measured me when I arrived. It\n"
	.string "stared. I stared back, for a long time.\p"
	.string "Then it looked away. First time anything\n"
	.string "has ever looked away from me first.\p"
	.string "Go and stare it down. Don't blink. It\n"
	.string "respects that. So do I.$"
```

</details>

Falante novo: `SP_NAME_KAREN` (o `_ChampionAfter` usa `{SPEAKER NAME_KAREN}`; ainda não existe em `include/constants/speaker_names.h`, skill `nomear-falante`).
