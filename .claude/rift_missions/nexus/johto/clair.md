# Clair

**Região da ficha:** Johto

Aparece no checklist como:

- **Clair — Dragão** (Johto · Líderes de Ginásio) — orgulhosa Líder de Blackthorn e prima de Lance.

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
| `OBJ_EVENT_GFX_CLAIR` | `graphics/object_events/pics/people/gym_leaders/clair.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_LEADER_CLAIR` | `graphics/trainers/front_pics/leader_clair.png` |

### Field mugshot

| Constante | Arquivo |
|---|---|
| `MUGSHOT_CLAIR` | `graphics/field_mugshots/clair.png` |

Aparece sozinho quando o objeto que fala usa o sprite acima (`GetFieldMugshotIdByObjectGraphicsId`, `src/field_mugshot.c`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_CLAIR_1` | 541 | 0x71D | Goodra-Hisui Lv58, Gyarados Lv58, Dragonite Lv58, Altaria Lv58, Hydrapple Lv58, Kingdra Lv59 · *dupla* · VS: Green | `BlackthornCity_Gym`, `src/battle_setup.c`, `src/data/level_scaling_rules.h` |
| `TRAINER_CLAIR_2` | 542 | 0x71E | Goodra Lv81, Kingdra Lv82, Haxorus Lv82, Noivern Lv83, Kommo-o Lv83, Charizard Lv84 · *dupla* | `DragonsDen_Cavern`, `KitakamiRoad_House`, `SaffronCity_FightingDojoVIP`, `src/achievements.c`, `src/battle_dome.c`, `src/battle_setup.c` |
| `TRAINER_TITLE_DEFENSE_CLAIR` | 898 | 0x882 | Goodra Lv85, Kingdra Lv85, Haxorus Lv85, Rayquaza Lv85, Kommo-o Lv85, Charizard Lv85 | `src/title_defense.c` |

### Time das Rift Missions

✅ **Implementado em 27/09/2026** (a proposta abaixo virou código): `TRAINER_NEXUS_CLAIR` = **1008** (flag de batalha `0x8F0`, limpa antes e depois de cada luta), bloco em `src/data/trainers.party`, nível pelo R2 (tabela em `src/data/nexus/trainers.h`). Fala genérica `Nexus_EventScript_Clair_Fight`; campeão: `Nexus_EventScript_Clair_ChampionFight` (para Kyurem). Tudo em `data/scripts/nexus.inc`, sem blackout, resultado em `VAR_TEMP_3`. Para testar: menu de debug → Rift Missions… → Nexus fights… → Clair.

📝 **Proposta de 27/09/2026, aguardando o autor.** `TRAINER_NEXUS_CLAIR`, campeã do Kyurem. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler).

Lendário **Kyurem**, o dragão incompleto do qual ela é campeã: o Gelo, a fraqueza de todo time de Dragão, virado arma do lado dela. Semi-lendário **Raging Bolt**, o dragão ancestral (Paradoxo do passado), a cara do clã de Blackthorn que venera dragões antigos no Dragon's Den. Mega **Dragonite** (Dragotite): o dragão-assinatura do primo Lance, nas mãos da prima que passou a vida querendo ser vista sem ele. Mais **Kingdra**, o ás dela desde Gold/Silver, e **Goodra-Hisui** e **Noivern**, dos times dela na campanha. Tudo Dragão; o Goodra-Hisui (Aço) segura Fada e Gelo.

*Plano (Doubles):* o formato dela (a luta do ginásio já é dupla). Noivern abre com Tailwind; Kyurem de Choice Specs dispara Glaciate, que acerta os dois e ainda baixa a velocidade deles; Kingdra solta Muddy Water em área com Sniper; Raging Bolt fecha com Thunderclap (prioridade) e se guarda com Protect; a Mega Dragonite sobe Dragon Dance atrás do Multiscale enquanto o parceiro chama a atenção.
*Plano (Singles):* Noivern vira pivô (U-turn, Focus Sash); Raging Bolt sobe Calm Mind com Booster Energy; Dragonite faz Dragon Dance com Multiscale intacto e limpa com Extreme Speed; Kyurem entra para quebrar com Draco Meteor e Freeze-Dry; Goodra-Hisui de Assault Vest absorve os golpes especiais que ameaçam o resto.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Kyurem | Choice Specs | Pressure | Modest | Glaciate, Draco Meteor, Freeze-Dry, Earth Power |
| Raging Bolt | Booster Energy | Protosynthesis | Modest | Thunderclap, Draco Meteor, Calm Mind, Protect |
| Dragonite | Dragotite | Multiscale | Adamant | Dragon Dance, Extreme Speed, Dragon Claw, Fire Punch |
| Kingdra | Life Orb | Sniper | Modest | Muddy Water, Draco Meteor, Ice Beam, Protect |
| Goodra-Hisui | Assault Vest | Sap Sipper | Sassy | Heavy Slam, Draco Meteor, Flamethrower, Thunderbolt |
| Noivern | Focus Sash | Infiltrator | Timid | Tailwind, Hurricane, Flamethrower, U-turn |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>nexus_validar_time.py</code>: trainerproc, constantes, learnsets e categorias)</summary>

```
=== TRAINER_NEXUS_CLAIR ===
Name: Clair
Class: Leader
Pic: Leader Clair
Gender: Female
Music: Female
Double Battle: Yes
AI: Smart Trainer

Kyurem @ Choice Specs
Modest Nature
Level: 100
Ability: Pressure
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Glaciate
- Draco Meteor
- Freeze-Dry
- Earth Power

Raging Bolt @ Booster Energy
Modest Nature
Level: 100
Ability: Protosynthesis
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Thunderclap
- Draco Meteor
- Calm Mind
- Protect

Dragonite @ Dragotite
Adamant Nature
Level: 100
Ability: Multiscale
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Dragon Dance
- Extreme Speed
- Dragon Claw
- Fire Punch

Kingdra @ Life Orb
Modest Nature
Level: 100
Ability: Sniper
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Muddy Water
- Draco Meteor
- Ice Beam
- Protect

Goodra-Hisui @ Assault Vest
Sassy Nature
Level: 100
Ability: Sap Sipper
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Heavy Slam
- Draco Meteor
- Flamethrower
- Thunderbolt

Noivern @ Focus Sash
Timid Nature
Level: 100
Ability: Infiltrator
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Tailwind
- Hurricane
- Flamethrower
- U-turn
```

</details>

### Lendário associado

#### Kyurem

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_Kyurem_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Kyurem**. Clair é a campeã dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Clair, Líder de Blackthorn e prima do Lance, "a melhor mestra de dragões do mundo" nas palavras dela. Perdeu a Rising Badge para o jogador, recusou-se a entregá-la e foi o Ancião do Dragon's Den que a fez ceder.

**A criatura.** Kyurem (Gelo/Dragão) gera dentro de si uma energia congelante que vaza e congela o próprio corpo. As lendas de Unova dizem que ele espera um herói que preencha as partes que faltam no corpo dele com verdade ou com ideais. Mundo em Black/White 2: Giant Chasm.

**O fragmento.** Um abismo tomado de gelo de parede a parede. No gelo, o molde vazio de um dragão, como se alguma coisa tivesse saído dali e deixado a forma para trás. O frio não vem do ar: vem do buraco.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A chasm, and ice from wall to wall.
>
> Pressed into the ice was the shape of a dragon. Empty, as if something had stepped out of it and left the mold behind.
>
> The cold was not coming from the air. It was coming from the hollow.

**Boss**

> The hollow was not empty after all.
>
> Something grey climbed out of it, half a dragon, and the ice cracked every time it breathed.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md))

> File L-646. Boundary.
>
> A dragon made of what was left over, and a dragon master people call the one left over.
>
> What came back with you is a small, cold piece of it. Keep it warm. I suspect nobody ever has.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Kyurem_Arrival:
	.string "A chasm, and ice from wall to wall.\p"
	.string "Pressed into the ice was the shape of a\n"
	.string "dragon. Empty, as if something had\l"
	.string "stepped out of it and left the mold\l"
	.string "behind.\p"
	.string "The cold was not coming from the air. It\n"
	.string "was coming from the hollow.$"

Nexus_Text_Kyurem_Boss:
	.string "The hollow was not empty after all.\p"
	.string "Something grey climbed out of it, half a\n"
	.string "dragon, and the ice cracked every time\l"
	.string "it breathed.$"

Nexus_Text_Kyurem_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-646. Boundary.\p"
	.string "A dragon made of what was left over,\n"
	.string "and a dragon master people call the one\l"
	.string "left over.\p"
	.string "What came back with you is a small, cold\n"
	.string "piece of it. Keep it warm. I suspect\l"
	.string "nobody ever has.$"
```

</details>


### Diálogo genérico

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Clair_Fight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Clair cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala dela mesma, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

**Antes da luta**

> I am Clair. The world's best dragon master.
>
> Don't look behind me for my cousin. He isn't coming, and I don't need him to.
>
> My dragons and I will do this ourselves!

**Derrota**

> …There must be some mistake. Fine. I'll say it once: you're good.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Clair_Intro:
	.string "I am Clair. The world's best dragon\n"
	.string "master.\p"
	.string "Don't look behind me for my cousin. He\n"
	.string "isn't coming, and I don't need him to.\p"
	.string "My dragons and I will do this ourselves!$"

Nexus_Text_Clair_Defeat:
	.string "…There must be some mistake. Fine. I'll\n"
	.string "say it once: you're good.$"
```

</details>

#### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mais duas falas para as **quatro primeiras salas** ([R16](../NEXUS_REGRAS.md)): fala de si, sem citar o lugar nem a criatura do dia. A variação 1 é a de cima, que já está no jogo; o sorteio de qual variação toca ainda não existe no código.

**Variação 2** — humor e orgulho: a capa. Sim, o primo também usa uma. A dela veio primeiro.

**Antes da luta**

> Yes, it's a cape. Yes, my cousin wears one too. Mine came first.
>
> The Dragon Tamers of Blackthorn have always worn capes. I don't care what anyone says.
>
> Now stop staring at it and battle me!

**Derrota**

> …Fine. You win. The cape stays, though.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Clair_Intro2:
	.string "Yes, it's a cape. Yes, my cousin wears\n"
	.string "one too. Mine came first.\p"
	.string "The Dragon Tamers of Blackthorn have\n"
	.string "always worn capes. I don't care what\l"
	.string "anyone says.\p"
	.string "Now stop staring at it and battle me!$"

Nexus_Text_Clair_Defeat2:
	.string "…Fine. You win. The cape stays, though.$"
```

</details>

**Variação 3** — o que ela perdeu no fragmento dela: ninguém a venceu, e o Ancião parou de vir assistir. Pior que perder é vencer sem ninguém olhando.

**Antes da luta**

> Do you know what's worse than losing? Winning with nobody watching.
>
> In Blackthorn I beat everyone who came. Every single one. The Elder stopped coming to watch.
>
> …So you'd better make this worth watching!

**Derrota**

> …There. Someone was watching. I suppose that's something.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Clair_Intro3:
	.string "Do you know what's worse than losing?\n"
	.string "Winning with nobody watching.\p"
	.string "In Blackthorn I beat everyone who\n"
	.string "came. Every single one. The Elder\l"
	.string "stopped coming to watch.\p"
	.string "…So you'd better make this worth\n"
	.string "watching!$"

Nexus_Text_Clair_Defeat3:
	.string "…There. Someone was watching. I\n"
	.string "suppose that's something.$"
```

</details>

### Diálogo associado ao lendário

#### Kyurem

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Clair_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Clair é a **campeã**, a luta logo antes do Kyurem. A fala é sobre a criatura, sem dizer o nome dela.

A Clair vê no Kyurem um dragão com metade de si faltando, esperando um herói que o complete, e esperando há tanto tempo que o próprio frio o congelou no lugar. Ela conhece a sensação: é a prima do Lance, a que sobra ao lado dele. A virada vem no depois: quando perdeu a insígnia para o jogador, foi mandada ao Dragon's Den como uma criança e esperava que o Ancião lhe devolvesse o orgulho; ele lhe deu perguntas. O que ela aprendeu lá é o que diz sobre a criatura: ninguém vem preencher o que falta. Ou você preenche sozinha, ou congela esperando.

**Antes da luta**

> Did you see it? Down in the ice. A dragon with half of itself missing.
>
> The old stories say it waits for a hero to fill in what it lost. Truth, or ideals. Whichever comes first.
>
> It has waited so long that its own cold froze it where it stands.
>
> …Don't look at me like that. I know what waiting feels like. Dragons, go!

**Derrota**

> I lost? …No. I am not going to sulk this time.

**Depois da luta**

> When I lost my badge to you, the Elder sent me into the Dragon's Den like a child.
>
> I thought he would give me back my pride. He gave me questions instead.
>
> That thing down there is waiting for someone to fill it up. Nobody is coming. Nobody ever does.
>
> You fill the hollow yourself, or you freeze in it. Go on. Show it how.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Clair_ChampionIntro:
	.string "Did you see it? Down in the ice. A dragon\n"
	.string "with half of itself missing.\p"
	.string "The old stories say it waits for a hero\n"
	.string "to fill in what it lost. Truth, or ideals.\l"
	.string "Whichever comes first.\p"
	.string "It has waited so long that its own cold\n"
	.string "froze it where it stands.\p"
	.string "…Don't look at me like that. I know what\n"
	.string "waiting feels like. Dragons, go!$"

Nexus_Text_Clair_ChampionDefeat:
	.string "I lost? …No. I am not going to sulk this\n"
	.string "time.$"

Nexus_Text_Clair_ChampionAfter:
	.string "{SPEAKER NAME_CLAIR}When I lost my badge to you, the Elder\n"
	.string "sent me into the Dragon's Den like a\l"
	.string "child.\p"
	.string "I thought he would give me back my\n"
	.string "pride. He gave me questions instead.\p"
	.string "That thing down there is waiting for\n"
	.string "someone to fill it up. Nobody is coming.\l"
	.string "Nobody ever does.\p"
	.string "You fill the hollow yourself, or you\n"
	.string "freeze in it. Go on. Show it how.$"
```

</details>

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mais duas falas de campeão para este lendário ([R16](../NEXUS_REGRAS.md)), sem dizer o nome da espécie. A variação 1 é a de cima, que já está no jogo.

**Variação 2** — a pergunta do Ancião (o teste do Dragon's Den), aplicada ao jogador: o que você daria a um dragão que perdeu metade de si? A resposta dela: nada. Todo mundo trouxe alguma coisa (fogo, raio, máquina); ele quer alguém que se sente com o buraco.

**Antes da luta**

> The Elder of my clan asks questions before he lets anyone near a dragon. Let me try one on you.
>
> What would you give a dragon that is missing half of itself? …Don't answer. You'll get it wrong.
>
> The one in the ice has been asked that for longer than anyone remembers. Dragons, go!

**Derrota**

> …Wrong answer. And you still won. Annoying.

**Depois da luta**

> The answer, by the way, is nothing. You don't give it anything.
>
> Everyone who came to the chasm brought something. Fire. Lightning. A machine. A speech.
>
> It doesn't want to be filled. It wants someone to sit with the hole. …Go. I'm bad at sitting.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Clair_ChampionIntro2:
	.string "The Elder of my clan asks questions\n"
	.string "before he lets anyone near a dragon.\l"
	.string "Let me try one on you.\p"
	.string "What would you give a dragon that is\n"
	.string "missing half of itself? …Don't answer.\l"
	.string "You'll get it wrong.\p"
	.string "The one in the ice has been asked that\n"
	.string "for longer than anyone remembers.\l"
	.string "Dragons, go!$"

Nexus_Text_Clair_ChampionDefeat2:
	.string "…Wrong answer. And you still won.\n"
	.string "Annoying.$"

Nexus_Text_Clair_ChampionAfter2:
	.string "{SPEAKER NAME_CLAIR}The answer, by the way, is nothing. You\n"
	.string "don't give it anything.\p"
	.string "Everyone who came to the chasm brought\n"
	.string "something. Fire. Lightning. A machine. A\l"
	.string "speech.\p"
	.string "It doesn't want to be filled. It wants\n"
	.string "someone to sit with the hole. …Go. I'm\l"
	.string "bad at sitting.$"
```

</details>

**Variação 3** — a provocação: o que vence dragão é gelo, e aquela criatura é as duas coisas, um dragão que é a própria fraqueza. Dizem que ela é igual. Lembrança do primo e da semana em que ela congelou no Den.

**Antes da luta**

> You know what beats a dragon? Ice. Every child in Blackthorn learns that first.
>
> And that thing down there is both. A dragon that is its own weakness.
>
> …I've been told I'm the same. We'll see about that. Dragons, go!

**Derrota**

> Don't say it. I know what you're thinking. Don't say it.

**Depois da luta**

> My cousin used to tease me that I'd freeze solid if anyone ever told me I was wrong.
>
> He was right. I froze for a whole week once. In the Den, with the Elder watching.
>
> That thing never got its week to thaw. Be quick with it. It's colder than it looks.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Clair_ChampionIntro3:
	.string "You know what beats a dragon? Ice.\n"
	.string "Every child in Blackthorn learns that\l"
	.string "first.\p"
	.string "And that thing down there is both. A\n"
	.string "dragon that is its own weakness.\p"
	.string "…I've been told I'm the same. We'll see\n"
	.string "about that. Dragons, go!$"

Nexus_Text_Clair_ChampionDefeat3:
	.string "Don't say it. I know what you're\n"
	.string "thinking. Don't say it.$"

Nexus_Text_Clair_ChampionAfter3:
	.string "{SPEAKER NAME_CLAIR}My cousin used to tease me that I'd\n"
	.string "freeze solid if anyone ever told me I\l"
	.string "was wrong.\p"
	.string "He was right. I froze for a whole week\n"
	.string "once. In the Den, with the Elder\l"
	.string "watching.\p"
	.string "That thing never got its week to thaw.\n"
	.string "Be quick with it. It's colder than it\l"
	.string "looks.$"
```

</details>
