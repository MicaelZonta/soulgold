# Ariana

**Região da ficha:** Kanto

Aparece no checklist como:

- **Ariana** (Kanto · Team Rocket) — executiva habilidosa e uma das figuras centrais da organização após Giovanni.
- **Ariana** (Johto · Team Rocket) — supervisiona operações importantes, incluindo a base de Mahogany.

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
| `OBJ_EVENT_GFX_ARIANA` | `graphics/object_events/pics/people/rockets/ariana.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_ARIANA` | `graphics/trainers/front_pics/ariana.png` |

### Field mugshot

| Constante | Arquivo |
|---|---|
| `MUGSHOT_ARIANA` | `graphics/field_mugshots/ariana.png` |

Aparece sozinho quando o objeto que fala usa o sprite acima (`GetFieldMugshotIdByObjectGraphicsId`, `src/field_mugshot.c`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_ARIANA_1` | 127 | 0x57F | Arbok Lv48, Vileplume Lv48, Dragalge Lv49 | `RocketHideout_B2F`, `src/battle_setup.c`, `src/match_call.c` |
| `TRAINER_ARIANA_2` | 132 | 0x584 | Arbok Lv52, Toxapex Lv53, Vileplume Lv54, Roserade Lv54, Trevenant Lv53, Dragalge Lv54 | `GoldenrodCity_RadioTower_5F`, `src/battle_setup.c` |

### Time das Rift Missions

✅ **Implementado em 27/09/2026** (a proposta abaixo virou código): `TRAINER_NEXUS_ARIANA` = **997** (flag de batalha `0x8E5`, limpa antes e depois de cada luta), bloco em `src/data/trainers.party`, nível pelo R2 (tabela em `src/data/nexus/trainers.h`). Fala genérica `Nexus_EventScript_Ariana_Fight`; campeão: `Nexus_EventScript_Ariana_ChampionFight` (para Cresselia). Tudo em `data/scripts/nexus.inc`, sem blackout, resultado em `VAR_TEMP_3`. Para testar: menu de debug → Rift Missions… → Nexus fights… → Ariana.

📝 **Proposta de 27/09/2026, aguardando o autor.** `TRAINER_NEXUS_ARIANA`, campeã de Cresselia. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler).

Lendário **Darkrai**, o dono dos pesadelos; semi-lendário **Cresselia**, de que ela é campeã, a dona dos sonhos bons: o par da lua nova e da lua crescente no mesmo time, e a fala de campeã vive dessa tensão. Mega **Dragalge** (Poisontite), do time dela neste hack. Mais **Arbok** (o ás dela em HGSS), **Vileplume** e **Toxapex**, também da campanha. *Plano geral:* sono e veneno; o Bad Dreams do Darkrai tira HP de todo oponente adormecido, e o resto do time envenena, paralisa e desgasta. Double Battle: No porque o time é de desgaste, mas nada nele depende de parceiro.

*Plano (Singles):* Toxapex põe Toxic Spikes e segura com Baneful Bunker e Regenerator; Arbok paralisa com Glare; Darkrai faz Hypnosis e sobe com Nasty Plot enquanto o Bad Dreams corrói; Cresselia é a parede com Moonlight e Thunder Wave; a Mega Dragalge de Adaptability fecha.

*Plano (Doubles):* Arbok abre com Intimidate e Glare, Vileplume com Stun Spore e Effect Spore (quem bate nele arrisca sono, paralisia ou veneno); o Bad Dreams pega os dois oponentes adormecidos; Cresselia com Levitate e a Dragalge com Sludge Bomb e Draco Meteor pressionam enquanto o Toxapex, trocado para dentro, segura com Baneful Bunker.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Darkrai | Life Orb | Bad Dreams | Timid | Dark Pulse, Sludge Bomb, Hypnosis, Nasty Plot |
| Cresselia | Leftovers | Levitate | Bold | Moonblast, Psyshock, Moonlight, Thunder Wave |
| Dragalge | Poisontite | Adaptability | Modest | Sludge Bomb, Draco Meteor, Hydro Pump, Focus Blast |
| Arbok | Black Sludge | Intimidate | Jolly | Gunk Shot, Glare, Sucker Punch, Knock Off |
| Vileplume | Rocky Helmet | Effect Spore | Bold | Giga Drain, Sludge Bomb, Strength Sap, Stun Spore |
| Toxapex | Black Sludge | Regenerator | Bold | Toxic Spikes, Baneful Bunker, Recover, Scald |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>dev_scripts/nexus_validar_time.py</code>)</summary>

```
=== TRAINER_NEXUS_ARIANA ===
Name: Ariana
Class: RocketA
Pic: Ariana
Gender: Female
Music: Rocket
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
- Hypnosis
- Nasty Plot

Cresselia @ Leftovers
Bold Nature
Level: 100
Ability: Levitate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Moonblast
- Psyshock
- Moonlight
- Thunder Wave

Dragalge @ Poisontite
Modest Nature
Level: 100
Ability: Adaptability
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Sludge Bomb
- Draco Meteor
- Hydro Pump
- Focus Blast

Arbok @ Black Sludge
Jolly Nature
Level: 100
Ability: Intimidate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Gunk Shot
- Glare
- Sucker Punch
- Knock Off

Vileplume @ Rocky Helmet
Bold Nature
Level: 100
Ability: Effect Spore
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Giga Drain
- Sludge Bomb
- Strength Sap
- Stun Spore

Toxapex @ Black Sludge
Bold Nature
Level: 100
Ability: Regenerator
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Toxic Spikes
- Baneful Bunker
- Recover
- Scald
```

</details>


### Lendário associado

#### Cresselia

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_Cresselia_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Cresselia**. Ariana é a campeã dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Ariana, executiva do Team Rocket, a que comandava a base de Mahogany, de onde saía o sinal de rádio que forçou os Magikarp do Lake of Rage a evoluir.

**A criatura.** Cresselia é o Pokémon da lua crescente. Quem dorme segurando uma pena dela tem sonhos felizes; é a contraparte do Darkrai, que traz pesadelos.

**O fragmento.** Um lago sob uma lua crescente fina, com a água tão parada que nem a respiração a mexe. Na margem, pessoas dormem na grama, e todas estão sorrindo.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A lake under a thin crescent moon.
>
> The water was so still it didn't ripple when you breathed. Along the shore, people lay asleep in the grass, and every one of them was smiling.

**Boss**

> Something pale rose over the water, trailing light like a scarf of cloud.
>
> Every sleeper on the shore sighed at once. None of them woke.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md): o que volta é um pedaço dele, no nível 1)

> File L-488. Lunar.
>
> A lake of good dreams, and a woman who once filled another lake with a signal made to hurt.
>
> The fragment you brought back is as light as a feather. Keep it near your pillow. That much, the old stories got right.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Cresselia_Arrival:
	.string "A lake under a thin crescent moon.\p"
	.string "The water was so still it didn't ripple\n"
	.string "when you breathed. Along the shore,\l"
	.string "people lay asleep in the grass, and\l"
	.string "every one of them was smiling.$"

Nexus_Text_Cresselia_Boss:
	.string "Something pale rose over the water,\n"
	.string "trailing light like a scarf of cloud.\p"
	.string "Every sleeper on the shore sighed at\n"
	.string "once. None of them woke.$"

Nexus_Text_Cresselia_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-488. Lunar.\p"
	.string "A lake of good dreams, and a woman who\n"
	.string "once filled another lake with a signal\l"
	.string "made to hurt.\p"
	.string "The fragment you brought back is as\n"
	.string "light as a feather. Keep it near your\l"
	.string "pillow. That much, the old stories got\l"
	.string "right.$"
```

</details>


### Diálogo genérico

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Ariana_Fight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Ariana cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala dela mesma, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

**Antes da luta**

> I am Ariana. I don't waste words on children, so listen.
>
> At the Lake of Rage, one signal from our base forced the Magikarp there to evolve. People remember the red Gyarados.
>
> They forget the signal worked. I don't. Come here.

**Derrota**

> Hmph. Write it down, then. It won't happen twice.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Ariana_Intro:
	.string "I am Ariana. I don't waste words on\n"
	.string "children, so listen.\p"
	.string "At the Lake of Rage, one signal from\n"
	.string "our base forced the Magikarp there to\l"
	.string "evolve. People remember the red\l"
	.string "Gyarados.\p"
	.string "They forget the signal worked. I don't.\n"
	.string "Come here.$"

Nexus_Text_Ariana_Defeat:
	.string "Hmph. Write it down, then. It won't\n"
	.string "happen twice.$"
```

</details>


### Diálogo associado ao lendário

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Ariana é o **campeão**, a luta logo antes do lendário. A fala é sobre a criatura, sem dizer o nome dela.

#### Cresselia

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Ariana_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

A Ariana não sonha há anos: dorme, acorda, trabalha. Na noite anterior, na beira deste lago, sonhou: um lago sem sinal nenhum, com peixes que eram só peixes. Não sabe de quem era o sonho. A virada: o sinal dela fez o outro lago gritar por uma semana, e este dá descanso a qualquer um que deite ao lado, sem perguntar quem é. Ela trouxe o Pokémon dos pesadelos como guarda, e ele também dormiu. Ela não gosta de presente que não pode pagar.

**Antes da luta**

> I haven't dreamed in years. I sleep, I wake, I work.
>
> Last night, by this lake, I dreamed. Something calm. A lake with no signal in it, and fish that were only fish.
>
> I don't know whose dream that was. It wasn't mine. …Battle me. I need to feel awake.

**Derrota**

> That, at least, was real.

**Depois da luta**

> Our signal made that other lake scream for a week. This one gives rest to anyone lying beside it. It doesn't ask who they are.
>
> I brought the one who gives nightmares with me. I thought I'd need a guard. It's been sleeping too.
>
> I don't like gifts I can't pay for. Go. Give it a reason to wake up.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Ariana_ChampionIntro:
	.string "I haven't dreamed in years. I sleep, I\n"
	.string "wake, I work.\p"
	.string "Last night, by this lake, I dreamed.\n"
	.string "Something calm. A lake with no signal in\l"
	.string "it, and fish that were only fish.\p"
	.string "I don't know whose dream that was. It\n"
	.string "wasn't mine. …Battle me. I need to feel\l"
	.string "awake.$"

Nexus_Text_Ariana_ChampionDefeat:
	.string "That, at least, was real.$"

Nexus_Text_Ariana_ChampionAfter:
	.string "{SPEAKER NAME_ARIANA}Our signal made that other lake scream\n"
	.string "for a week. This one gives rest to\l"
	.string "anyone lying beside it. It doesn't ask\l"
	.string "who they are.\p"
	.string "I brought the one who gives nightmares\n"
	.string "with me. I thought I'd need a guard.\l"
	.string "It's been sleeping too.\p"
	.string "I don't like gifts I can't pay for. Go.\n"
	.string "Give it a reason to wake up.$"
```

</details>

Falante novo: `SP_NAME_ARIANA`.
