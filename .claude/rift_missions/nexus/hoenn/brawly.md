# Brawly

**Região da ficha:** Hoenn

Aparece no checklist como:

- **Brawly — Lutador** (Hoenn · Líderes de Ginásio) — surfista e Líder de Dewford.

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


### Diálogo associado ao lendário

#### Keldeo

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

#### Iron Hands

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

Falante novo: `SP_NAME_BRAWLY` (não existe ainda em `include/constants/speaker_names.h`).
