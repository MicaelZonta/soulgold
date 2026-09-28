# Red

**Região da ficha:** Kanto

Aparece no checklist como:

- **Red** (Kanto · Rivais e protagonistas) — protagonista original de Kanto e um dos treinadores mais fortes da franquia.
- **Red** (Johto · Outros notáveis) — superchefe silencioso encontrado no topo do Mt. Silver.
- **Red** (Alola · Outros notáveis) — veterano e chefe da Battle Tree.

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
| `OBJ_EVENT_GFX_RED` | `graphics/object_events/pics/people/red.png` |
| `OBJ_EVENT_GFX_RED_NORMAL` | `graphics/object_events/pics/people/red.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_RED` | `graphics/trainers/front_pics/red.png` |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_RED_1` | 230 | 0x5E6 | **sem time** (ID reservado, sem bloco no `.party`) | `src/battle_setup.c` |
| `TRAINER_RED_2` | 231 | 0x5E7 | Pikachu Lv93, Snorlax Lv75, Charizard Lv77, Venusaur Lv77, Blastoise Lv77, Espeon Lv80 | `src/battle_setup.c` |
| `TRAINER_RED` | 851 | 0x853 | **sem time** (ID reservado, sem bloco no `.party`) | `src/battle_dome.c` |

### Time das Rift Missions

✅ **Implementado em 27/09/2026** (a proposta abaixo virou código): `TRAINER_NEXUS_RED` = **985** (flag de batalha `0x8D9`, limpa antes e depois de cada luta), bloco em `src/data/trainers.party`, nível pelo R2 (tabela em `src/data/nexus/trainers.h`). Fala genérica `Nexus_EventScript_Red_Fight`; campeão: `Nexus_EventScript_Red_ChampionFight` (para Arceus). Tudo em `data/scripts/nexus.inc`, sem blackout, resultado em `VAR_TEMP_3`. Para testar: menu de debug → Rift Missions… → Nexus fights… → Red.

📝 **Proposta de 27/09/2026, aguardando o autor.** `TRAINER_NEXUS_RED`, campeão de Arceus. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler).

Lendário **Arceus**, o Original, para o treinador que já venceu todo mundo e foi morar sozinho no topo do Mt. Silver; semi-lendário **Zapdos**, a ave da Power Plant de Kanto, a primeira lenda que ele encontrou no caminho; Mega **Charizard Y** (Firetite), o inicial dele. Mais Pikachu, Venusaur e Snorlax, do time dele no Mt. Silver (`TRAINER_RED_2`). O Blastoise e o Espeon saem: no sol eles pesam mais do que ajudam. É o time "clássico" de Red, com o Arceus no lugar de quem ele deixou no PC.

*Plano (Singles):* sol. O Pikachu entra de Fake Out e bate com Light Ball; a Mega Charizard Y põe Drought e o Venusaur corre com Chlorophyll (Sleep Powder na frente, Giga Drain e Earth Power para cobrir); o Zapdos pivota com Roost e segura os Water/Rock que ameaçam o sol; o Snorlax fecha a porta com Curse + Rest; o Arceus fica para o fim, Swords Dance e limpa com Extreme Speed.

*Plano (Doubles):* Fake Out do Pikachu + Heat Wave da Charizard Y no primeiro turno; o Zapdos põe Tailwind, e com sol e vento o Venusaur dobra a velocidade duas vezes. O Pikachu tem Lightning Rod: puxa os golpes elétricos que iam na Charizard e no Zapdos. Nenhum golpe do time acerta o parceiro.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Arceus | Life Orb | Multitype | Adamant | Extreme Speed, Swords Dance, Shadow Claw, Recover |
| Zapdos | Sitrus Berry | Static | Timid | Thunderbolt, Heat Wave, Tailwind, Roost |
| Charizard | Firetite | Blaze | Timid | Heat Wave, Solar Beam, Focus Blast, Roost |
| Pikachu | Light Ball | Lightning Rod | Naive | Fake Out, Volt Tackle, Surf, Knock Off |
| Venusaur | Life Orb | Chlorophyll | Modest | Giga Drain, Sludge Bomb, Earth Power, Sleep Powder |
| Snorlax | Chesto Berry | Thick Fat | Careful | Body Slam, Crunch, Curse, Rest |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>dev_scripts/nexus_validar_time.py</code>: trainerproc, constantes, learnsets e categorias)</summary>

```
=== TRAINER_NEXUS_RED ===
Name: Red
Class: Pkmn Trainer 1
Pic: Red
Gender: Male
Music: Hg Champion
Double Battle: No
AI: Smart Trainer

Arceus @ Life Orb
Adamant Nature
Level: 100
Ability: Multitype
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Extreme Speed
- Swords Dance
- Shadow Claw
- Recover

Zapdos @ Sitrus Berry
Timid Nature
Level: 100
Ability: Static
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Thunderbolt
- Heat Wave
- Tailwind
- Roost

Charizard @ Firetite
Timid Nature
Level: 100
Ability: Blaze
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Heat Wave
- Solar Beam
- Focus Blast
- Roost

Pikachu @ Light Ball
Naive Nature
Level: 100
Ability: Lightning Rod
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Fake Out
- Volt Tackle
- Surf
- Knock Off

Venusaur @ Life Orb
Modest Nature
Level: 100
Ability: Chlorophyll
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Giga Drain
- Sludge Bomb
- Earth Power
- Sleep Powder

Snorlax @ Chesto Berry
Careful Nature
Level: 100
Ability: Thick Fat
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Body Slam
- Crunch
- Curse
- Rest
```

</details>

### Lendário associado

#### Arceus

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_Arceus_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Arceus**. Red é o campeão dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Red, o protagonista de Red/Green/Blue. Venceu a Liga de Kanto, derrubou a Team Rocket, e três anos depois é o superchefe silencioso no topo do Mt. Silver, sozinho na neve. Nos jogos ele não diz nada além de "…".

**A criatura.** Arceus é o Original: segundo o mito de Sinnoh, saiu de um ovo no meio do caos, antes de existir o universo, e moldou o mundo com mil braços. Criou Dialga, Palkia e Giratina. As Plates são pedaços do corpo dele.

**O fragmento.** O que existia antes de qualquer coisa. Um chão sem fim e um céu que ainda não foi decidido, com placas de pedra colorida paradas no ar, cada uma zumbindo uma nota. Nada foi feito ainda; o lugar está esperando.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> Nothing. Not dark, not light. Just a floor that went on forever, under a sky that had not been decided yet.
>
> Tablets of colored stone hung in the air around you. Each one hummed a different note.

**Boss**

> The tablets turned, all at once, toward the same empty point.
>
> Something stepped out of the place where nothing had been, and the floor under its feet became real.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md))

> File L-493. Alpha.
>
> A world before the world, and a young man who says almost nothing, standing at the edge of it.
>
> What came back with you is very small and very new. It has made nothing yet. Give it time.
>
> He spoke today. I have the words. I am keeping them to myself.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Arceus_Arrival:
	.string "Nothing. Not dark, not light. Just a\n"
	.string "floor that went on forever, under a sky\l"
	.string "that had not been decided yet.\p"
	.string "Tablets of colored stone hung in the\n"
	.string "air around you. Each one hummed a\l"
	.string "different note.$"

Nexus_Text_Arceus_Boss:
	.string "The tablets turned, all at once, toward\n"
	.string "the same empty point.\p"
	.string "Something stepped out of the place\n"
	.string "where nothing had been, and the floor\l"
	.string "under its feet became real.$"

Nexus_Text_Arceus_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-493. Alpha.\p"
	.string "A world before the world, and a young\n"
	.string "man who says almost nothing, standing\l"
	.string "at the edge of it.\p"
	.string "What came back with you is very small\n"
	.string "and very new. It has made nothing yet.\l"
	.string "Give it time.\p"
	.string "He spoke today. I have the words. I am\n"
	.string "keeping them to myself.$"
```

</details>

### Diálogo genérico

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Red_Fight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Red cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala de si, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

O Red nos jogos só diz "…" e "…!". A proposta mantém isso e deixa escapar uma frase curta por luta: é o detalhe que o leitor não espera dele.

**Antes da luta**

> …
>
> ……
>
> …Quiet here. Like the summit.
>
> …!

**Derrota**

> ……
>
> …Heh.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Red_Intro:
	.string "…\p"
	.string "……\p"
	.string "…Quiet here. Like the summit.\p"
	.string "…!$"

Nexus_Text_Red_Defeat:
	.string "……\p"
	.string "…Heh.$"
```

</details>

### Diálogo associado ao lendário

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Red é o **campeão**, a luta logo antes do lendário. A fala é sobre a criatura, sem dizer o nome dela ([R16](../NEXUS_REGRAS.md)).

#### Arceus

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Red_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

O Red não fala; a fala dele são reticências, e o que ele diz em palavras vale por dez. Ele subiu uma montanha para ficar sozinho e ficou anos lá. A criatura também estava sozinha, antes de tudo, e o que ela fez com isso foi criar um mundo inteiro. A virada é que o Red, que nunca fala, fala sobre isso: ele entendeu a criatura porque fez o contrário, e agora desceu da montanha. O "Heh" da derrota é o sorriso que ninguém vê.

**Antes da luta**

> ……
>
> …It was here first. Before anything.
>
> …Alone.
>
> …!

**Derrota**

> ……Heh.

**Depois da luta**

> ……
>
> …I went up a mountain. To be alone.
>
> …Stayed a long time.
>
> …It was alone first. So it made everything. Every one of us.
>
> …I just came down. …Go.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Red_ChampionIntro:
	.string "……\p"
	.string "…It was here first. Before anything.\p"
	.string "…Alone.\p"
	.string "…!$"

Nexus_Text_Red_ChampionDefeat:
	.string "……Heh.$"

Nexus_Text_Red_ChampionAfter:
	.string "{SPEAKER NAME_RED}……\p"
	.string "…I went up a mountain. To be alone.\p"
	.string "…Stayed a long time.\p"
	.string "…It was alone first. So it made\n"
	.string "everything. Every one of us.\p"
	.string "…I just came down. …Go.$"
```

</details>

Falante novo: `SP_NAME_RED` (ainda não existe em `include/constants/speaker_names.h`).
