# Brawly

**Região da ficha:** Hoenn

Aparece no checklist como:

- **Brawly — Lutador** (Hoenn · Líderes de Ginásio) — surfista e Líder de Dewford.

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
| `OBJ_EVENT_GFX_BRAWLY` | `graphics/object_events/pics/people/gym_leaders/brawly.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_LEADER_BRAWLY` | `graphics/trainers/front_pics/leader_brawly.png` |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

Nenhuma. Ao criar, seguir a skill `adicionar-batalha-npc` (e `alocar-flag` se precisar de flag nova).

### Time das Rift Missions

✅ **Implementado em 27/09/2026** (a proposta abaixo virou código): `TRAINER_NEXUS_BRAWLY` = **1016** (flag de batalha `0x8F8`, limpa antes e depois de cada luta), bloco em `src/data/trainers.party`, nível pelo R2 (tabela em `src/data/nexus/trainers.h`). Fala genérica `Nexus_EventScript_Brawly_Fight`; campeão: `Nexus_EventScript_Brawly_IronHands_ChampionFight` (para Iron Hands), `Nexus_EventScript_Brawly_Keldeo_ChampionFight` (para Keldeo). Tudo em `data/scripts/nexus.inc`, sem blackout, resultado em `VAR_TEMP_3`. Para testar: menu de debug → Rift Missions… → Nexus fights… → Brawly.

📝 **Proposta de 27/09/2026, aguardando o autor.** `TRAINER_NEXUS_BRAWLY`, campeão de Keldeo e Iron Hands. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler).

Lendário **Kyogre** com Blue Orb (a Primal ocupa a vaga de Mega, R10): o mar em que o Brawly surfa desde sempre, e a chuva sem fim do Primordial Sea, que transforma o time numa onda; semi-lendário **Keldeo**, Água/Lutador, o potro que corre sobre a água, a outra metade do Brawly. Mais **Hariyama** (o ás dele, criado desde Makuhita), **Medicham** (o Meditite do ginásio de Dewford), **Poliwrath** (Água/Lutador, Swift Swim) e **Breloom** (Mach Punch e Spore, cobre Grama e Elétrico).

*Plano (Singles):* o Primal Kyogre abre com chuva que não acaba enquanto ele está em campo e anula Fogo. O Keldeo de Choice Specs e o Poliwrath de Swift Swim varrem; o Breloom de Focus Sash põe alguém para dormir; o Hariyama de Assault Vest aguenta os golpes especiais e segura com Bullet Punch.

*Plano (Doubles, o formato de escrita):* Fake Out do Hariyama e Water Spout (ou Origin Pulse) do Kyogre no turno 1, os dois golpes de alvo duplo que só acertam os adversários. O Icy Wind do Keldeo controla velocidade, o Poliwrath entra com Protect e Swift Swim. Nenhum golpe do time acerta o parceiro.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Kyogre | Blue Orb | Drizzle | Timid | Origin Pulse, Water Spout, Ice Beam, Thunder |
| Keldeo | Choice Specs | Justified | Timid | Secret Sword, Hydro Pump, Icy Wind, Vacuum Wave |
| Hariyama | Assault Vest | Thick Fat | Adamant | Fake Out, Close Combat, Knock Off, Bullet Punch |
| Medicham | Choice Band | Pure Power | Jolly | High Jump Kick, Zen Headbutt, Ice Punch, Bullet Punch |
| Poliwrath | Life Orb | Swift Swim | Adamant | Liquidation, Close Combat, Ice Punch, Protect |
| Breloom | Focus Sash | Technician | Jolly | Spore, Mach Punch, Bullet Seed, Rock Tomb |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>dev_scripts/nexus_validar_time.py</code>: espécie, item, habilidade, golpes e vagas)</summary>

```
=== TRAINER_NEXUS_BRAWLY ===
Name: Brawly
Class: Leader
Pic: Leader Brawly
Gender: Male
Music: Male
Double Battle: Yes
AI: Smart Trainer

Kyogre @ Blue Orb
Timid Nature
Level: 100
Ability: Drizzle
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Origin Pulse
- Water Spout
- Ice Beam
- Thunder

Keldeo @ Choice Specs
Timid Nature
Level: 100
Ability: Justified
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Secret Sword
- Hydro Pump
- Icy Wind
- Vacuum Wave

Hariyama @ Assault Vest
Adamant Nature
Level: 100
Ability: Thick Fat
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Fake Out
- Close Combat
- Knock Off
- Bullet Punch

Medicham @ Choice Band
Jolly Nature
Level: 100
Ability: Pure Power
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- High Jump Kick
- Zen Headbutt
- Ice Punch
- Bullet Punch

Poliwrath @ Life Orb
Adamant Nature
Level: 100
Ability: Swift Swim
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Liquidation
- Close Combat
- Ice Punch
- Protect

Breloom @ Focus Sash
Jolly Nature
Level: 100
Ability: Technician
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Spore
- Mach Punch
- Bullet Seed
- Rock Tomb
```

</details>


### Lendário associado

#### Keldeo

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_Keldeo_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Keldeo**. Brawly é o campeão dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Brawly, Líder de Dewford, surfista e lutador, que treina nas ondas e na caverna escura da ilha.

**A criatura.** Keldeo (Água/Lutador) é o potro que aprendeu com os Swords of Justice. Galopa sobre a superfície da água e, quando se decide de verdade, ganha a forma Resolute, com uma lâmina de luz na fronte.

**O fragmento.** Um mar sem margem em direção nenhuma, liso mas não calmo: prendendo a respiração. Na superfície, uma trilha de marcas de casco, cada uma ainda soando como um sino batido.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A sea with no shore in any direction. The water was flat, but not calm. It was holding its breath.
>
> Across its surface ran a line of hoofprints, each one still ringing like a struck bell.

**Boss**

> The hoofprints stopped right in front of you.
>
> Something small and fast stood on the water, and a blade of light slowly grew from its brow.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** (o que volta é o fragmento no nível 1, [R17](../NEXUS_REGRAS.md))

> File L-647. The Colt.
>
> A sea that would not let anything sink, and a young man who learned to stand on waves before he learned to fight.
>
> What came back with you is a colt that has not found its sword yet. It will. The young ones always go looking.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Keldeo_Arrival:
	.string "A sea with no shore in any direction.\n"
	.string "The water was flat, but not calm. It\l"
	.string "was holding its breath.\p"
	.string "Across its surface ran a line of\n"
	.string "hoofprints, each one still ringing like\l"
	.string "a struck bell.$"

Nexus_Text_Keldeo_Boss:
	.string "The hoofprints stopped right in front\n"
	.string "of you.\p"
	.string "Something small and fast stood on the\n"
	.string "water, and a blade of light slowly grew\l"
	.string "from its brow.$"

Nexus_Text_Keldeo_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-647. The Colt.\p"
	.string "A sea that would not let anything sink,\n"
	.string "and a young man who learned to stand\l"
	.string "on waves before he learned to fight.\p"
	.string "What came back with you is a colt that\n"
	.string "has not found its sword yet. It will.\l"
	.string "The young ones always go looking.$"
```

</details>

#### Iron Hands

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_IronHands_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Iron Hands**. Brawly é o campeão dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Brawly, Líder de Dewford, cujo parceiro de sempre é um Hariyama que ele criou desde Makuhita.

**A criatura.** Iron Hands (Lutador/Elétrico) é um Paradoxo da Area Zero: parece um Hariyama de um futuro possível, feito de metal, com mãos enormes que soltam eletricidade.

**O fragmento.** Um salão de treino enorme e vazio, iluminado por faíscas. Pilares de aço em fileiras, cada um amassado pela mesma palma gigante, de novo e de novo, mais fundo a cada vez.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste Paradoxo):

**Chegada**

> A training hall, huge and empty, lit only by sparks.
>
> Steel pillars stood in rows, each dented by the same enormous palm, over and over, deeper every time.

**Boss**

> Something clanked to its feet between the pillars.
>
> It was built like a wrestler, and its hands were bigger than you. It bowed, the way a sumo does, before it charged.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** (o que volta é o fragmento no nível 1, [R17](../NEXUS_REGRAS.md))

> File L-992. The Future Heavyweight.
>
> A training hall in a time that has not happened, and a Gym Leader who met what his partner might someday become.
>
> What came back with you is small and cold, and it keeps clapping its hands together to hear the sound. I have not told the young man. I think he would cry.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_IronHands_Arrival:
	.string "A training hall, huge and empty, lit only\n"
	.string "by sparks.\p"
	.string "Steel pillars stood in rows, each\n"
	.string "dented by the same enormous palm, over\l"
	.string "and over, deeper every time.$"

Nexus_Text_IronHands_Boss:
	.string "Something clanked to its feet between\n"
	.string "the pillars.\p"
	.string "It was built like a wrestler, and its\n"
	.string "hands were bigger than you. It bowed,\l"
	.string "the way a sumo does, before it charged.$"

Nexus_Text_IronHands_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-992. The Future Heavyweight.\p"
	.string "A training hall in a time that has not\n"
	.string "happened, and a Gym Leader who met\l"
	.string "what his partner might someday become.\p"
	.string "What came back with you is small and\n"
	.string "cold, and it keeps clapping its hands\l"
	.string "together to hear the sound. I have not\l"
	.string "told the young man. I think he would\l"
	.string "cry.$"
```

</details>


### Diálogo genérico

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Brawly_Fight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Brawly cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala dele mesmo, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

**Antes da luta**

> Whoa, a new spot! I don't know where I washed up, but it's got a serious current.
>
> I'm Brawly! I got churned in the rough waves of Dewford and toughened up in a pitch-black cave.
>
> Wherever I land, I paddle out and ride the biggest wave around. Today, that's you! Let's go!

**Derrota**

> Wiped out! Man, what a wave that was.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Brawly_Intro:
	.string "Whoa, a new spot! I don't know where I\n"
	.string "washed up, but it's got a serious\l"
	.string "current.\p"
	.string "I'm Brawly! I got churned in the rough\n"
	.string "waves of Dewford and toughened up in a\l"
	.string "pitch-black cave.\p"
	.string "Wherever I land, I paddle out and ride\n"
	.string "the biggest wave around. Today, that's\l"
	.string "you! Let's go!$"

Nexus_Text_Brawly_Defeat:
	.string "Wiped out! Man, what a wave that was.$"
```

</details>

#### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mais duas falas genéricas para as quatro primeiras salas, com ângulos diferentes da variação 1 (que está no jogo). Seguem o [R16](../NEXUS_REGRAS.md): falam dele mesmo, sem o lugar nem a criatura do dia.

**Variação 2** — a caverna escura de Dewford (lembrança de treino).

**Antes da luta**

> Ever trained in total darkness? Like, can't-see-your-own-hands dark?
>
> That's the cave on my island. You learn to feel a punch coming before you see it.
>
> So close your eyes if you want. Mine are open. Let's go!

**Derrota**

> Didn't see that coming. Literally.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Brawly_Intro2:
	.string "Ever trained in total darkness? Like,\n"
	.string "can't-see-your-own-hands dark?\p"
	.string "That's the cave on my island. You learn\n"
	.string "to feel a punch coming before you see\l"
	.string "it.\p"
	.string "So close your eyes if you want. Mine are\n"
	.string "open. Let's go!$"

Nexus_Text_Brawly_Defeat2:
	.string "Didn't see that coming. Literally.$"
```

</details>

**Variação 3** — a ilha que sumiu (R21: o que aconteceu diferente no fragmento dele, dito com humor de surfista).

**Antes da luta**

> Hey, have you seen an island? Small. Palm trees. One Gym, one Poké Mart, big cave?
>
> I paddled out one morning, and when I turned around it wasn't there.
>
> No worries! Waves bring everything back eventually. Meanwhile, battle!

**Derrota**

> Wiped out. Still no island. Still no worries.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Brawly_Intro3:
	.string "Hey, have you seen an island? Small.\n"
	.string "Palm trees. One Gym, one Poké Mart, big\l"
	.string "cave?\p"
	.string "I paddled out one morning, and when I\n"
	.string "turned around it wasn't there.\p"
	.string "No worries! Waves bring everything back\n"
	.string "eventually. Meanwhile, battle!$"

Nexus_Text_Brawly_Defeat3:
	.string "Wiped out. Still no island. Still no\n"
	.string "worries.$"
```

</details>


### Diálogo associado ao lendário

#### Keldeo

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Brawly_Keldeo_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Brawly é o **campeão**, a luta logo antes do Keldeo. A fala é sobre a criatura, sem dizer o nome dela.

O Brawly vê o potro correndo sobre o mar, não surfando: correndo, como quem já decidiu o caminho. Quando começou a surfar, ele caiu mil vezes; aquilo nunca caiu uma. A virada é de surfista: quem nunca cai nunca aprende a levantar. O Brawly ficou bom porque o mar o derrubou, e pede ao jogador que não pegue leve: o potro precisa de uma onda grande para cair e voltar melhor.

**Antes da luta**

> You see it out there? Running on the water. Not surfing, dude. Running. Like the sea's a road it already picked.
>
> When I started surfing, I wiped out a thousand times. That little guy has never fallen once.
>
> Not 'cause it's strong. 'Cause it made up its mind. I respect that. So let's go all out!

**Derrota**

> Wiped out. You held your line the whole way.

**Depois da luta**

> Here's the thing about never falling. You never learn how to get back up.
>
> I got good because I wiped out. Every single time, the sea taught me something.
>
> So don't go easy on that colt. Give it a big one to fall off of. It'll come back better. That's how it works for all of us.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Brawly_Keldeo_ChampionIntro:
	.string "You see it out there? Running on the\n"
	.string "water. Not surfing, dude. Running. Like\l"
	.string "the sea's a road it already picked.\p"
	.string "When I started surfing, I wiped out a\n"
	.string "thousand times. That little guy has\l"
	.string "never fallen once.\p"
	.string "Not 'cause it's strong. 'Cause it made\n"
	.string "up its mind. I respect that. So let's go\l"
	.string "all out!$"

Nexus_Text_Brawly_Keldeo_ChampionDefeat:
	.string "Wiped out. You held your line the whole\n"
	.string "way.$"

Nexus_Text_Brawly_Keldeo_ChampionAfter:
	.string "{SPEAKER NAME_BRAWLY}Here's the thing about never falling.\n"
	.string "You never learn how to get back up.\p"
	.string "I got good because I wiped out. Every\n"
	.string "single time, the sea taught me\l"
	.string "something.\p"
	.string "So don't go easy on that colt. Give it a\n"
	.string "big one to fall off of. It'll come back\l"
	.string "better. That's how it works for all of\l"
	.string "us.$"
```

</details>

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mais duas falas de campeão para esta criatura, sem dizer o nome dela ([R16](../NEXUS_REGRAS.md)); a variação 1 é a que está no jogo.

**Variação 2** — os três mestres de espada contra o único mestre dele, o mar.

**Antes da luta**

> Word is that colt had three teachers. Big, serious ones. Swords, all of 'em.
>
> I had one teacher: the ocean. Never said a word. Just knocked me down till I got it.
>
> Let's see whose training holds up! Let's go!

**Derrota**

> Your teachers did good, dude.

**Depois da luta**

> The old story says the three found it after a flood took its herd.
>
> They taught it to stand on the thing that took everything.
>
> I get that more than I'd like. My island's under that water somewhere.
>
> Go on. Ride with it, not against it.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Brawly_Keldeo_ChampionIntro2:
	.string "Word is that colt had three teachers.\n"
	.string "Big, serious ones. Swords, all of 'em.\p"
	.string "I had one teacher: the ocean. Never\n"
	.string "said a word. Just knocked me down till I\l"
	.string "got it.\p"
	.string "Let's see whose training holds up!\n"
	.string "Let's go!$"

Nexus_Text_Brawly_Keldeo_ChampionDefeat2:
	.string "Your teachers did good, dude.$"

Nexus_Text_Brawly_Keldeo_ChampionAfter2:
	.string "{SPEAKER NAME_BRAWLY}The old story says the three found it\n"
	.string "after a flood took its herd.\p"
	.string "They taught it to stand on the thing\n"
	.string "that took everything.\p"
	.string "I get that more than I'd like. My\n"
	.string "island's under that water somewhere.\p"
	.string "Go on. Ride with it, not against it.$"
```

</details>

**Variação 3** — humor: a corrida perdida, e o potro que voltava por ele.

**Antes da luta**

> I tried racing it. Paddled as hard as I've ever paddled.
>
> It went past me, turned around, came back, and went past me again. Just to be nice.
>
> My arms are noodles now. Doesn't matter! Fists still work!

**Derrota**

> Noodle arms. Knew it.

**Depois da luta**

> Thing is, it came back for me. Every time. Didn't have to.
>
> That's a good heart, dude. Fast feet are nothing without it.
>
> If it falls today, help it up. It'll remember.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Brawly_Keldeo_ChampionIntro3:
	.string "I tried racing it. Paddled as hard as\n"
	.string "I've ever paddled.\p"
	.string "It went past me, turned around, came\n"
	.string "back, and went past me again. Just to be\l"
	.string "nice.\p"
	.string "My arms are noodles now. Doesn't\n"
	.string "matter! Fists still work!$"

Nexus_Text_Brawly_Keldeo_ChampionDefeat3:
	.string "Noodle arms. Knew it.$"

Nexus_Text_Brawly_Keldeo_ChampionAfter3:
	.string "{SPEAKER NAME_BRAWLY}Thing is, it came back for me. Every\n"
	.string "time. Didn't have to.\p"
	.string "That's a good heart, dude. Fast feet\n"
	.string "are nothing without it.\p"
	.string "If it falls today, help it up. It'll\n"
	.string "remember.$"
```

</details>

#### Iron Hands

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Brawly_IronHands_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Brawly é o **campeão**, a luta logo antes do Iron Hands. A fala é sobre a criatura, sem dizer o nome dela.

O Brawly reconhece o Hariyama dele naquela máquina: a mesma postura, o mesmo tapa, a mesma reverência antes do avanço. Só que de ferro, e sem respirar. Ver os hábitos do parceiro num corpo de metal o assusta. A virada vem no meio da luta: aquilo nunca cansa, nunca sua, nunca escorrega; e é justamente por cansar que o Hariyama sabe onde é fraco e continua melhorando. O que não cansa não fica mais forte.

**Antes da luta**

> There's a Pokémon down there that fights exactly like my Hariyama. Same stance. Same slap. Same bow before it charges.
>
> Only it's made of iron, and it doesn't breathe.
>
> I raised Hariyama from a little Makuhita. I know every habit it has. Seeing them on a machine… that shook me, dude.
>
> Let's go! I need to feel a real one hit!

**Derrota**

> That was real, all right. Thanks for that.

**Depois da luta**

> Figured it out while we were battling.
>
> That iron one never gets tired. Never sweats, never slips. Sounds great, right?
>
> But my Hariyama gets tired. That's how it learns where it's weak. That's why it keeps getting better.
>
> Something that can't get tired can't get any stronger. Go show it that.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Brawly_IronHands_ChampionIntro:
	.string "There's a Pokémon down there that\n"
	.string "fights exactly like my Hariyama. Same\l"
	.string "stance. Same slap. Same bow before it\l"
	.string "charges.\p"
	.string "Only it's made of iron, and it doesn't\n"
	.string "breathe.\p"
	.string "I raised Hariyama from a little\n"
	.string "Makuhita. I know every habit it has.\l"
	.string "Seeing them on a machine… that shook\l"
	.string "me, dude.\p"
	.string "Let's go! I need to feel a real one hit!$"

Nexus_Text_Brawly_IronHands_ChampionDefeat:
	.string "That was real, all right. Thanks for\n"
	.string "that.$"

Nexus_Text_Brawly_IronHands_ChampionAfter:
	.string "{SPEAKER NAME_BRAWLY}Figured it out while we were battling.\p"
	.string "That iron one never gets tired. Never\n"
	.string "sweats, never slips. Sounds great,\l"
	.string "right?\p"
	.string "But my Hariyama gets tired. That's how\n"
	.string "it learns where it's weak. That's why\l"
	.string "it keeps getting better.\p"
	.string "Something that can't get tired can't\n"
	.string "get any stronger. Go show it that.$"
```

</details>

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mais duas falas de campeão para esta criatura, sem dizer o nome dela ([R16](../NEXUS_REGRAS.md)); a variação 1 é a que está no jogo.

**Variação 2** — as marcas nos pilares: a mesma palma, todo dia (liga ao aplauso do Looker File).

**Antes da luta**

> Count the dents in those steel pillars. Go on. I got to three hundred before I quit.
>
> Every one's the same palm, same spot, a little deeper. That's how my Hariyama trains too.
>
> Somebody taught it that. I wanna know if it was me. Let's go!

**Derrota**

> Okay. Big hands. Bigger heart. Good match.

**Depois da luta**

> A Hariyama's slap isn't about power. It's about showing up to the same pillar every morning.
>
> That iron one's been showing up for who knows how long. With nobody watching.
>
> Clap for it when you win. I bet nobody ever has.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Brawly_IronHands_ChampionIntro2:
	.string "Count the dents in those steel pillars.\n"
	.string "Go on. I got to three hundred before I\l"
	.string "quit.\p"
	.string "Every one's the same palm, same spot, a\n"
	.string "little deeper. That's how my Hariyama\l"
	.string "trains too.\p"
	.string "Somebody taught it that. I wanna know\n"
	.string "if it was me. Let's go!$"

Nexus_Text_Brawly_IronHands_ChampionDefeat2:
	.string "Okay. Big hands. Bigger heart. Good\n"
	.string "match.$"

Nexus_Text_Brawly_IronHands_ChampionAfter2:
	.string "{SPEAKER NAME_BRAWLY}A Hariyama's slap isn't about power.\n"
	.string "It's about showing up to the same\l"
	.string "pillar every morning.\p"
	.string "That iron one's been showing up for who\n"
	.string "knows how long. With nobody watching.\p"
	.string "Clap for it when you win. I bet nobody\n"
	.string "ever has.$"
```

</details>

**Variação 3** — o medo: e se for isso que o Hariyama vira depois dele?.

**Antes da luta**

> What if that's what my Hariyama turns into? After me, I mean. After a long, long time.
>
> Iron, and sparks, and nobody to train with.
>
> Nah. Can't think like that. Can't punch like that either. Let's go!

**Derrota**

> Still punching. Good sign.

**Depois da luta**

> Made up my mind. If that's the future, I'm leaving it a message.
>
> Something like: 'You were good before you were iron. Somebody loved your stance.'
>
> Take that in there with you, okay? Say it loud. Iron's got good ears.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Brawly_IronHands_ChampionIntro3:
	.string "What if that's what my Hariyama turns\n"
	.string "into? After me, I mean. After a long,\l"
	.string "long time.\p"
	.string "Iron, and sparks, and nobody to train\n"
	.string "with.\p"
	.string "Nah. Can't think like that. Can't punch\n"
	.string "like that either. Let's go!$"

Nexus_Text_Brawly_IronHands_ChampionDefeat3:
	.string "Still punching. Good sign.$"

Nexus_Text_Brawly_IronHands_ChampionAfter3:
	.string "{SPEAKER NAME_BRAWLY}Made up my mind. If that's the future,\n"
	.string "I'm leaving it a message.\p"
	.string "Something like: 'You were good before\n"
	.string "you were iron. Somebody loved your\l"
	.string "stance.'\p"
	.string "Take that in there with you, okay? Say\n"
	.string "it loud. Iron's got good ears.$"
```

</details>

Falante novo: `SP_NAME_BRAWLY` (não existe ainda em `include/constants/speaker_names.h`).
