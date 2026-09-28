# Glacia

**Região da ficha:** Hoenn

Aparece no checklist como:

- **Glacia — Gelo** (Hoenn · Elite Four e Campeões) — treinadora que escolheu Hoenn para fortalecer seus Pokémon.

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
| `OBJ_EVENT_GFX_GLACIA` | `graphics/object_events/pics/people/elite_four/glacia.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_ELITE_FOUR_GLACIA` | `graphics/trainers/front_pics/elite_four_glacia.png` |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_GLACIA` | 263 | 0x607 | **sem time** (ID reservado, sem bloco no `.party`) | `EverGrandeCity_GlaciasRoom`, `src/battle_setup.c`, `src/data/level_scaling_rules.h` |

### Time das Rift Missions

✅ **Implementado em 27/09/2026** (a proposta abaixo virou código): `TRAINER_NEXUS_GLACIA` = **1026** (flag de batalha `0x902`, limpa antes e depois de cada luta), bloco em `src/data/trainers.party`, nível pelo R2 (tabela em `src/data/nexus/trainers.h`). Fala genérica `Nexus_EventScript_Glacia_Fight`; campeão: `Nexus_EventScript_Glacia_ChienPao_ChampionFight` (para Chien-Pao), `Nexus_EventScript_Glacia_IronBundle_ChampionFight` (para Iron Bundle). Tudo em `data/scripts/nexus.inc`, sem blackout, resultado em `VAR_TEMP_3`. Para testar: menu de debug → Rift Missions… → Nexus fights… → Glacia.

📝 **Proposta de 27/09/2026, aguardando o autor.** `TRAINER_NEXUS_GLACIA`, campeão de Iron Bundle e Chien-Pao. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler).

Lendário **Kyurem** (Dragão/Gelo, a casca vazia e congelada do dragão original: o frio que sobrou); semi-lendário **Chien-Pao** (Sombrio/Gelo, o tesouro da ruína que racha toda defesa por perto, de quem ela é campeã); Mega **Glalie** (Icetite; em ORAS a Glalie dela mega-evolui). Mais **Walrein** (o ás dela em Emerald), **Froslass** (do time dela em ORAS) e **Abomasnow** (Snow Warning). A Glacia veio de longe atrás de rivais à altura; o time é neve pura.

*Plano (Singles):* o Abomasnow chama a neve e ergue Aurora Veil; Blizzard acerta sempre na neve; o Sword of Ruin da Chien-Pao baixa a Defesa de todos em campo, e a Mega Glalie (Refrigerate) e a própria Chien-Pao aproveitam; a Froslass de Sash tem Destiny Bond; o Walrein (Thick Fat) segura Fogo e põe Yawn.

*Plano (Doubles):* Blizzard em área de Abomasnow, Walrein e Kyurem, com acerto certo na neve; Icy Wind da Froslass controla a velocidade; Aurora Veil corta o dano; Ice Shard e Sucker Punch fecham com prioridade.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Kyurem | Life Orb | Pressure | Modest | Blizzard, Freeze-Dry, Draco Meteor, Earth Power |
| Chien-Pao | Focus Sash | Sword of Ruin | Jolly | Icicle Crash, Sacred Sword, Sucker Punch, Ice Shard |
| Glalie | Icetite | Inner Focus | Jolly | Double-Edge, Ice Shard, Crunch, Protect |
| Walrein | Leftovers | Thick Fat | Bold | Blizzard, Surf, Protect, Yawn |
| Abomasnow | Light Clay | Snow Warning | Modest | Blizzard, Giga Drain, Aurora Veil, Protect |
| Froslass | Focus Sash | Cursed Body | Timid | Icy Wind, Shadow Ball, Will-O-Wisp, Destiny Bond |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>dev_scripts/nexus_validar_time.py</code>)</summary>

```
=== TRAINER_NEXUS_GLACIA ===
Name: Glacia
Class: Elite Four
Pic: Elite Four Glacia
Gender: Female
Music: Elite Four
Double Battle: Yes
AI: Smart Trainer

Kyurem @ Life Orb
Modest Nature
Level: 100
Ability: Pressure
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Blizzard
- Freeze-Dry
- Draco Meteor
- Earth Power

Chien-Pao @ Focus Sash
Jolly Nature
Level: 100
Ability: Sword of Ruin
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Icicle Crash
- Sacred Sword
- Sucker Punch
- Ice Shard

Glalie @ Icetite
Jolly Nature
Level: 100
Ability: Inner Focus
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Double-Edge
- Ice Shard
- Crunch
- Protect

Walrein @ Leftovers
Bold Nature
Level: 100
Ability: Thick Fat
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Blizzard
- Surf
- Protect
- Yawn

Abomasnow @ Light Clay
Modest Nature
Level: 100
Ability: Snow Warning
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Blizzard
- Giga Drain
- Aurora Veil
- Protect

Froslass @ Focus Sash
Timid Nature
Level: 100
Ability: Cursed Body
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Icy Wind
- Shadow Ball
- Will-O-Wisp
- Destiny Bond
```

</details>


### Lendário associado

#### Iron Bundle

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_IronBundle_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Iron Bundle**. Glacia é o campeão dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Glacia, da Elite Four de Hoenn, especialista em Gelo. Viajou de longe até Hoenn para afiar suas técnicas e reclama de só encontrar desafiantes fracos.

**A criatura.** Iron Bundle, Pokémon Paradoxo do futuro (Gelo/Água), uma versão robótica de um pássaro entregador que carrega comida no rabo. Veloz, patina pelo gelo.

**O fragmento.** Uma estação polar do futuro, vazia. Neve caindo dentro de casa, corredores de metal branco, e um alarme que ninguém desligou tocando há séculos.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A polar station from some far-off future, empty.
>
> Snow was falling indoors, down long white metal hallways.
>
> Somewhere an alarm had been ringing for centuries, and no one had come to turn it off.

**Boss**

> The alarm stopped.
>
> Something small and white came skating down the hall, far too fast, carrying a sack made of ice.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md))

> File L-991. The Last Courier.
>
> A station everyone left, and a woman who crossed the world looking for a place cold enough, and was not glad when she found it.
>
> What followed you home is small, and it keeps trying to hand me things. She says even ice wants somebody to deliver to.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_IronBundle_Arrival:
	.string "A polar station from some far-off\n"
	.string "future, empty.\p"
	.string "Snow was falling indoors, down long\n"
	.string "white metal hallways.\p"
	.string "Somewhere an alarm had been ringing\n"
	.string "for centuries, and no one had come to\l"
	.string "turn it off.$"

Nexus_Text_IronBundle_Boss:
	.string "The alarm stopped.\p"
	.string "Something small and white came skating\n"
	.string "down the hall, far too fast, carrying a\l"
	.string "sack made of ice.$"

Nexus_Text_IronBundle_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-991. The Last Courier.\p"
	.string "A station everyone left, and a woman\n"
	.string "who crossed the world looking for a\l"
	.string "place cold enough, and was not glad\l"
	.string "when she found it.\p"
	.string "What followed you home is small, and it\n"
	.string "keeps trying to hand me things. She\l"
	.string "says even ice wants somebody to\l"
	.string "deliver to.$"
```

</details>


#### Chien-Pao

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_ChienPao_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Chien-Pao**. Glacia é o campeão dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Glacia, a especialista em Gelo da Elite Four de Hoenn: fria, altiva, feita de gelo por escolha.

**A criatura.** Chien-Pao, um dos quatro Tesouros da Ruína (Sombrio/Gelo), ligado a uma espada antiga. Foi selado num santuário com estacas; sua presença enfraquece a defesa de todos ao redor.

**O fragmento.** Um santuário enterrado na neve, com uma grande estaca rachada ao meio. Tudo em volta está trincado: a pedra, o gelo, até o ar parece fino como vidro.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A shrine buried in snow.
>
> A great stake had been driven into the ground here once, and it had split in two.
>
> Around it, everything was cracked. The stone, the ice. Even the air felt thin, like glass.

**Boss**

> The cracks in the ice ran toward you.
>
> Something with blades of ice for fangs stepped out of them, and your guard suddenly felt like paper.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md))

> File L-1002. The Ruinous Sword.
>
> A shrine where every defense cracks, and a woman who has spent her life making herself hard and cold.
>
> What came back with you is small, and nothing cracks around it yet. She walked out thawed. I do not know which of them won.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_ChienPao_Arrival:
	.string "A shrine buried in snow.\p"
	.string "A great stake had been driven into the\n"
	.string "ground here once, and it had split in\l"
	.string "two.\p"
	.string "Around it, everything was cracked. The\n"
	.string "stone, the ice. Even the air felt thin,\l"
	.string "like glass.$"

Nexus_Text_ChienPao_Boss:
	.string "The cracks in the ice ran toward you.\p"
	.string "Something with blades of ice for fangs\n"
	.string "stepped out of them, and your guard\l"
	.string "suddenly felt like paper.$"

Nexus_Text_ChienPao_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-1002. The Ruinous Sword.\p"
	.string "A shrine where every defense cracks,\n"
	.string "and a woman who has spent her life\l"
	.string "making herself hard and cold.\p"
	.string "What came back with you is small, and\n"
	.string "nothing cracks around it yet. She\l"
	.string "walked out thawed. I do not know which\l"
	.string "of them won.$"
```

</details>


### Diálogo genérico

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Glacia_Fight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Glacia cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala dela mesma, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

**Antes da luta**

> Welcome. I am Glacia. I traveled far to Hoenn to hone my icy skills.
>
> The heat there was unbearable. I stayed anyway.
>
> Ice is not tempered in the cold, you see. It is tempered by what tries to melt it.
>
> So show me your fire. I would hate to be disappointed again.

**Derrota**

> How hot your spirit burns… My ice could not even leave a mark.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Glacia_Intro:
	.string "Welcome. I am Glacia. I traveled far to\n"
	.string "Hoenn to hone my icy skills.\p"
	.string "The heat there was unbearable. I\n"
	.string "stayed anyway.\p"
	.string "Ice is not tempered in the cold, you\n"
	.string "see. It is tempered by what tries to\l"
	.string "melt it.\p"
	.string "So show me your fire. I would hate to be\n"
	.string "disappointed again.$"

Nexus_Text_Glacia_Defeat:
	.string "How hot your spirit burns… My ice could\n"
	.string "not even leave a mark.$"
```

</details>


### Diálogo associado ao lendário

#### Iron Bundle

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Glacia_IronBundle_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Glacia é o **campeão**, a luta logo antes do Iron Bundle. A fala é sobre a criatura, sem dizer o nome dele.

A Glacia deixou a própria terra atrás de rivais e de frio. Aqui encontra o frio perfeito, silencioso e vazio, e uma máquina que continua entregando coisas para ninguém. Ela percebe que o frio só é bonito quando alguém sente. A virada: a máquina não para porque não sabe deixar de ter esperança, e uma batalha também conta como entrega.

**Antes da luta**

> Did you see that little machine racing down the halls?
>
> It is carrying something to someone. Every day, for centuries, and there is no one left.
>
> I left my home to find worthy rivals in the cold. This is the coldest place I have ever been, and I cannot stand it.
>
> Cold is only beautiful when someone is shivering. Come.

**Derrota**

> Your warmth again. It seems I cannot escape it.

**Depois da luta**

> I thought I wanted a world as cold as my Pokémon. Quiet. Pure.
>
> This is that world, and it is only lonely.
>
> That machine keeps delivering because it does not know how to stop hoping.
>
> Take it something. Even a battle counts as a delivery.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Glacia_IronBundle_ChampionIntro:
	.string "Did you see that little machine racing\n"
	.string "down the halls?\p"
	.string "It is carrying something to someone.\n"
	.string "Every day, for centuries, and there is\l"
	.string "no one left.\p"
	.string "I left my home to find worthy rivals in\n"
	.string "the cold. This is the coldest place I\l"
	.string "have ever been, and I cannot stand it.\p"
	.string "Cold is only beautiful when someone is\n"
	.string "shivering. Come.$"

Nexus_Text_Glacia_IronBundle_ChampionDefeat:
	.string "Your warmth again. It seems I cannot\n"
	.string "escape it.$"

Nexus_Text_Glacia_IronBundle_ChampionAfter:
	.string "{SPEAKER NAME_GLACIA}I thought I wanted a world as cold as\n"
	.string "my Pokémon. Quiet. Pure.\p"
	.string "This is that world, and it is only\n"
	.string "lonely.\p"
	.string "That machine keeps delivering because\n"
	.string "it does not know how to stop hoping.\p"
	.string "Take it something. Even a battle\n"
	.string "counts as a delivery.$"
```

</details>


#### Chien-Pao

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Glacia_ChienPao_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Glacia é o **campeão**, a luta logo antes do Chien-Pao. A fala é sobre a criatura, sem dizer o nome dele.

A Glacia construiu a si mesma de gelo, duro e frio de propósito. A criatura racha toda defesa por perto, e a dela rachou num instante. Ela fica curiosa pelo que há por baixo. A virada: medo faz as pessoas erguerem muros, e aquilo só quebra muros; deve ser solitário ser a coisa contra a qual todos constroem. O conselho: entre sem armadura.

**Antes da luta**

> Do you feel it? Your guard, cracking, like thin ice under a boot.
>
> Everything near that sword grows weaker. Stone. Steel. People.
>
> I have built myself of ice for many years. It cracked in an instant here.
>
> …Interesting. Let us see if there is anything underneath.

**Derrota**

> So there was something underneath. It was not enough.

**Depois da luta**

> They say it was sealed with stakes, driven in by people who feared it.
>
> Fear makes you build walls. It breaks walls. That is all it does.
>
> It must be very lonely, being the thing everyone builds walls against.
>
> Go. Walk in without armor. It will have nothing to break.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Glacia_ChienPao_ChampionIntro:
	.string "Do you feel it? Your guard, cracking,\n"
	.string "like thin ice under a boot.\p"
	.string "Everything near that sword grows\n"
	.string "weaker. Stone. Steel. People.\p"
	.string "I have built myself of ice for many\n"
	.string "years. It cracked in an instant here.\p"
	.string "…Interesting. Let us see if there is\n"
	.string "anything underneath.$"

Nexus_Text_Glacia_ChienPao_ChampionDefeat:
	.string "So there was something underneath. It\n"
	.string "was not enough.$"

Nexus_Text_Glacia_ChienPao_ChampionAfter:
	.string "{SPEAKER NAME_GLACIA}They say it was sealed with stakes,\n"
	.string "driven in by people who feared it.\p"
	.string "Fear makes you build walls. It breaks\n"
	.string "walls. That is all it does.\p"
	.string "It must be very lonely, being the thing\n"
	.string "everyone builds walls against.\p"
	.string "Go. Walk in without armor. It will have\n"
	.string "nothing to break.$"
```

</details>


Falante novo: `SP_NAME_GLACIA` (ainda não existe em `include/constants/speaker_names.h`).
