# Karen

**Região da ficha:** Johto

Aparece no checklist como:

- **Karen — Noturno** (Johto · Elite Four e Campeão) — defensora da ideia de vencer usando os Pokémon de que se gosta.

**Pronto para o Nexus:** ✅ sim — tem sprite e battle sprite.

## Checklist

- [x] Sprite de overworld *(obrigatório)*
- [x] Battle sprite / front pic *(obrigatório)*
- [x] Field mugshot (retrato na caixa de diálogo)
- [ ] Time para as Rift Missions definido
- [ ] Associado a um lendário
- [ ] Diálogo genérico escrito
- [ ] Diálogo associado ao lendário escrito

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


### Diálogo associado ao lendário

#### Darkrai

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

#### Galarian Moltres

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

Falante novo: `SP_NAME_KAREN` (o `_ChampionAfter` usa `{SPEAKER NAME_KAREN}`; ainda não existe em `include/constants/speaker_names.h`, skill `nomear-falante`).
