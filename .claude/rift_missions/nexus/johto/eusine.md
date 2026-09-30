# Eusine

**Região da ficha:** Johto

Aparece no checklist como:

- **Eusine** (Johto · Outros notáveis) — pesquisador e treinador obcecado em encontrar Suicune.

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
| `OBJ_EVENT_GFX_EUSINE` | `graphics/object_events/pics/people/special/eusine.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_EUSINE` | `graphics/trainers/front_pics/eusine.png` |

### Field mugshot

| Constante | Arquivo |
|---|---|
| `MUGSHOT_EUSINE` | `graphics/field_mugshots/eusine.png` |

Aparece sozinho quando o objeto que fala usa o sprite acima (`GetFieldMugshotIdByObjectGraphicsId`, `src/field_mugshot.c`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_EUSINE` | 560 | 0x730 | Golisopod Lv38, Wobbuffet Lv38, Magnezone Lv39 | `CianwoodCity` |

### Time das Rift Missions

✅ **Implementado em 27/09/2026** (a proposta abaixo virou código): `TRAINER_NEXUS_EUSINE` = **1011** (flag de batalha `0x8F3`, limpa antes e depois de cada luta), bloco em `src/data/trainers.party`, nível pelo R2 (tabela em `src/data/nexus/trainers.h`). Fala genérica `Nexus_EventScript_Eusine_Fight`; campeão: `Nexus_EventScript_Eusine_Raikou_ChampionFight` (para Raikou), `Nexus_EventScript_Eusine_Entei_ChampionFight` (para Entei), `Nexus_EventScript_Eusine_Suicune_ChampionFight` (para Suicune). Tudo em `data/scripts/nexus.inc`, sem blackout, resultado em `VAR_TEMP_3`. Para testar: menu de debug → Rift Missions… → Nexus fights… → Eusine.

📝 **Proposta de 27/09/2026, aguardando o autor.** `TRAINER_NEXUS_EUSINE`, campeão do Suicune, do Raikou e do Entei. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler).

Lendário **Ho-Oh**, o pássaro que ressuscitou as três feras depois do incêndio da Brass Tower: a lenda por trás de tudo o que o Eusine estuda. Semi-lendário **Suicune**, a obsessão dele há dez anos (e um dos três de que é campeão). Mega **Gengar** (Ghostite), o Haunter do time dele em Crystal/HGSS já evoluído, e o fantasma de um pesquisador que passa a vida atrás de espíritos e lendas. Mais **Hypno** e **Electrode**, do mesmo time de Crystal/HGSS, e **Magnezone**, da luta dele na campanha.

*Plano:* o pesquisador que controla o ritmo. Electrode e Hypno preparam o campo, Suicune e Ho-Oh aguentam e desgastam, a Mega Gengar e o Magnezone batem.
*Plano (Singles):* Electrode (Focus Sash) dá Taunt e Thunder Wave e sai com Volt Switch; Hypno de Light Clay arma as telas; Suicune sobe Calm Mind com Pressure e Scald; Ho-Oh (Regenerator, Heavy-Duty Boots) entra e sai queimando com Sacred Fire; a Mega Gengar (Shadow Tag) prende o alvo que quiser e o derruba com Shadow Ball, Sludge Bomb ou Focus Blast; Magnezone (Magnet Pull) prende os Aço que seguram o time.
*Plano (Doubles):* Suicune põe Tailwind e usa Snarl nos dois oponentes; a Mega Gengar bate com Shadow Ball e Sludge Bomb e usa Protect no turno em que o parceiro atrai o golpe; Electrode dá Thunder Wave e Foul Play; Ho-Oh usa Protect enquanto o parceiro trabalha.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Ho-Oh | Heavy-Duty Boots | Regenerator | Adamant | Sacred Fire, Brave Bird, Recover, Protect |
| Suicune | Leftovers | Pressure | Bold | Scald, Snarl, Calm Mind, Tailwind |
| Gengar | Ghostite | Cursed Body | Timid | Shadow Ball, Sludge Bomb, Focus Blast, Protect |
| Hypno | Light Clay | Insomnia | Calm | Reflect, Light Screen, Psychic, Thunder Wave |
| Electrode | Focus Sash | Aftermath | Timid | Taunt, Volt Switch, Foul Play, Thunder Wave |
| Magnezone | Choice Specs | Magnet Pull | Modest | Thunderbolt, Flash Cannon, Volt Switch, Body Press |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>nexus_validar_time.py</code>: trainerproc, constantes, learnsets e categorias)</summary>

```
=== TRAINER_NEXUS_EUSINE ===
Name: Eusine
Class: Mystery Man
Pic: Eusine
Gender: Male
Music: Male
Double Battle: No
AI: Smart Trainer

Ho-Oh @ Heavy-Duty Boots
Adamant Nature
Level: 100
Ability: Regenerator
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Sacred Fire
- Brave Bird
- Recover
- Protect

Suicune @ Leftovers
Bold Nature
Level: 100
Ability: Pressure
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Scald
- Snarl
- Calm Mind
- Tailwind

Gengar @ Ghostite
Timid Nature
Level: 100
Ability: Cursed Body
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Shadow Ball
- Sludge Bomb
- Focus Blast
- Protect

Hypno @ Light Clay
Calm Nature
Level: 100
Ability: Insomnia
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Reflect
- Light Screen
- Psychic
- Thunder Wave

Electrode @ Focus Sash
Timid Nature
Level: 100
Ability: Aftermath
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Taunt
- Volt Switch
- Foul Play
- Thunder Wave

Magnezone @ Choice Specs
Modest Nature
Level: 100
Ability: Magnet Pull
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Thunderbolt
- Flash Cannon
- Volt Switch
- Body Press
```

</details>

### Lendário associado

#### Suicune

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_Suicune_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Suicune**. Eusine é o campeão dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Eusine, o místico pesquisador que persegue o Suicune há dez anos, amigo do Morty de Ecruteak. Em Crystal/HGSS o Suicune escolhe o jogador, não ele.

**A criatura.** Suicune (Água), a encarnação dos ventos do norte, que purifica a água suja por onde passa e corre pelo mundo. Um dos três Pokémon que morreram no incêndio da Brass Tower e foram ressuscitados pelo Ho-Oh.

**O fragmento.** Um lago tão limpo que não tem superfície: dá para ver cada pedra do fundo e nenhuma água. Um vento frio sopra do norte, e as marolas correm contra ele.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A lake so clear it had no surface. You could see every stone on the bottom, and no water at all.
>
> A cold wind blew from the north, and the ripples ran against it.

**Boss**

> The wind stopped. Something stepped onto the lake, and the water held it.
>
> Wherever it walked, the lake grew clearer still.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md))

> File L-245. Aurora.
>
> A lake clean enough to drown in, and a man who spent ten years learning its tracks.
>
> What came back with you is small and leaves wet pawprints. He will want to see them. Let him.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Suicune_Arrival:
	.string "A lake so clear it had no surface. You\n"
	.string "could see every stone on the bottom,\l"
	.string "and no water at all.\p"
	.string "A cold wind blew from the north, and the\n"
	.string "ripples ran against it.$"

Nexus_Text_Suicune_Boss:
	.string "The wind stopped. Something stepped\n"
	.string "onto the lake, and the water held it.\p"
	.string "Wherever it walked, the lake grew\n"
	.string "clearer still.$"

Nexus_Text_Suicune_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-245. Aurora.\p"
	.string "A lake clean enough to drown in, and a\n"
	.string "man who spent ten years learning its\l"
	.string "tracks.\p"
	.string "What came back with you is small and\n"
	.string "leaves wet pawprints. He will want to\l"
	.string "see them. Let him.$"
```

</details>

#### Raikou

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_Raikou_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Raikou**. Eusine é o campeão dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Eusine, o místico pesquisador que persegue o Suicune há dez anos, amigo do Morty de Ecruteak. Em Crystal/HGSS o Suicune escolhe o jogador, não ele.

**A criatura.** Raikou (Elétrico), que dizem ter descido junto com um raio e que dispara trovões à vontade com as nuvens de chuva que carrega. Um dos três ressuscitados pelo Ho-Oh; a Brass Tower pegou fogo depois de ser atingida por um raio.

**O fragmento.** Uma planície debaixo de céu negro, iluminada de branco por cima. Um raio parado entre as nuvens e a grama, sem piscar, como se tivesse esquecido de terminar de cair.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A plain under a black sky, lit white from above.
>
> A bolt of lightning hung between the clouds and the grass. It did not flicker. It had forgotten how to finish falling.

**Boss**

> The bolt came down at last. It did not strike the ground.
>
> It landed on four legs, and the thunder came after it, late.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md))

> File L-243. Thunder.
>
> A storm stopped at the instant of the strike, and a researcher who finally saw the one that got away.
>
> What came back with you crackles in its sleep. I have moved my notes to a drier pocket.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Raikou_Arrival:
	.string "A plain under a black sky, lit white from\n"
	.string "above.\p"
	.string "A bolt of lightning hung between the\n"
	.string "clouds and the grass. It did not\l"
	.string "flicker. It had forgotten how to finish\l"
	.string "falling.$"

Nexus_Text_Raikou_Boss:
	.string "The bolt came down at last. It did not\n"
	.string "strike the ground.\p"
	.string "It landed on four legs, and the thunder\n"
	.string "came after it, late.$"

Nexus_Text_Raikou_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-243. Thunder.\p"
	.string "A storm stopped at the instant of the\n"
	.string "strike, and a researcher who finally saw\l"
	.string "the one that got away.\p"
	.string "What came back with you crackles in its\n"
	.string "sleep. I have moved my notes to a drier\l"
	.string "pocket.$"
```

</details>

#### Entei

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_Entei_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Entei**. Eusine é o campeão dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Eusine, o místico pesquisador que persegue o Suicune há dez anos, amigo do Morty de Ecruteak. Em Crystal/HGSS o Suicune escolhe o jogador, não ele.

**A criatura.** Entei (Fogo), que dizem ter nascido na erupção de um vulcão; quando ruge, vulcões entram em erupção. Um dos três ressuscitados pelo Ho-Oh depois do incêndio da Brass Tower, há 150 anos.

**O fragmento.** A Brass Tower em chamas, como há 150 anos: madeira velha, um sino em algum lugar lá dentro, fumaça com cheiro de século e meio. O fogo já devia ter acabado há muito tempo e não acabou.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A tower on fire. Old wood, a bell somewhere inside, and smoke that smelled of a hundred and fifty years.
>
> The fire should have burned out long ago. It had not.

**Boss**

> Something barked inside the flames. Every fire in the tower lay flat, the way a dog lies down.
>
> Then it rose, and so did they.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md))

> File L-244. Volcano.
>
> A tower that never stopped burning, and a man who read about that fire until he could smell it.
>
> What came back with you is small and very warm. It did not flinch at the smoke. I did.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Entei_Arrival:
	.string "A tower on fire. Old wood, a bell\n"
	.string "somewhere inside, and smoke that\l"
	.string "smelled of a hundred and fifty years.\p"
	.string "The fire should have burned out long\n"
	.string "ago. It had not.$"

Nexus_Text_Entei_Boss:
	.string "Something barked inside the flames.\n"
	.string "Every fire in the tower lay flat, the way\l"
	.string "a dog lies down.\p"
	.string "Then it rose, and so did they.$"

Nexus_Text_Entei_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-244. Volcano.\p"
	.string "A tower that never stopped burning, and\n"
	.string "a man who read about that fire until he\l"
	.string "could smell it.\p"
	.string "What came back with you is small and\n"
	.string "very warm. It did not flinch at the\l"
	.string "smoke. I did.$"
```

</details>


### Diálogo genérico

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Eusine_Fight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Eusine cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala dele mesmo, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

**Antes da luta**

> Ah, a Trainer! My name's Eusine. I'm on the trail of a certain legend.
>
> Ten years of rumors, puddles, and north winds. You'd be amazed what I know about puddles.
>
> Let's battle! A true researcher tests everything!

**Derrota**

> I hate to admit it, but you win. …I'm writing that down, too.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Eusine_Intro:
	.string "Ah, a Trainer! My name's Eusine. I'm on\n"
	.string "the trail of a certain legend.\p"
	.string "Ten years of rumors, puddles, and north\n"
	.string "winds. You'd be amazed what I know\l"
	.string "about puddles.\p"
	.string "Let's battle! A true researcher tests\n"
	.string "everything!$"

Nexus_Text_Eusine_Defeat:
	.string "I hate to admit it, but you win. …I'm\n"
	.string "writing that down, too.$"
```

</details>

#### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mais duas falas para as **quatro primeiras salas** ([R16](../NEXUS_REGRAS.md)): fala de si, sem citar o lugar nem a criatura do dia. A variação 1 é a de cima, que já está no jogo; o sorteio de qual variação toca ainda não existe no código.

**Variação 2** — o amigo Morty, que vê o futuro: perguntou se um dia ia pegar o que persegue, e o Morty sorriu e mudou de assunto. O Eusine decidiu que é sim.

**Antes da luta**

> My friend Morty says I talk too much about legends. He sees the future, and he still listens.
>
> I asked him once if I'd ever catch what I'm chasing. He smiled and changed the subject.
>
> …I've decided that means yes! Battle me!

**Derrota**

> He changed the subject because of you, didn't he? …Don't answer that.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Eusine_Intro2:
	.string "My friend Morty says I talk too much\n"
	.string "about legends. He sees the future, and\l"
	.string "he still listens.\p"
	.string "I asked him once if I'd ever catch what\n"
	.string "I'm chasing. He smiled and changed the\l"
	.string "subject.\p"
	.string "…I've decided that means yes! Battle\n"
	.string "me!$"

Nexus_Text_Eusine_Defeat2:
	.string "He changed the subject because of you,\n"
	.string "didn't he? …Don't answer that.$"
```

</details>

**Variação 3** — R21 com humor: uma cartomante disse que em algum lugar uma criança de boné pegou a lenda dele primeiro. Que absurdo. …Por que você está ajeitando o boné?

**Antes da luta**

> A fortune teller once told me that somewhere, a child in a cap caught my legend before I did.
>
> What nonsense! I've been at this for ten years. What child has ten years?
>
> …Why are you adjusting your cap? Battle me!

**Derrota**

> …It's the cap, isn't it. I knew it.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Eusine_Intro3:
	.string "A fortune teller once told me that\n"
	.string "somewhere, a child in a cap caught my\l"
	.string "legend before I did.\p"
	.string "What nonsense! I've been at this for\n"
	.string "ten years. What child has ten years?\p"
	.string "…Why are you adjusting your cap?\n"
	.string "Battle me!$"

Nexus_Text_Eusine_Defeat3:
	.string "…It's the cap, isn't it. I knew it.$"
```

</details>

### Diálogo associado ao lendário

#### Suicune

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Eusine_Suicune_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Eusine é o **campeão**, a luta logo antes do Suicune. A fala é sobre a criatura, sem dizer o nome dela.

Dez anos atrás do Suicune, e aqui ele finalmente parou a dez passos do Eusine, e olhou através dele, para a porta por onde o jogador entrou. A virada é a paz dele depois da derrota: dez anos de perseguição ensinam a reconhecer quem a criatura está esperando. Nunca ia ser ele (ele desconfia que sabia disso desde a Burned Tower). Então ele será quem a conhece melhor.

**Antes da luta**

> It's here! It stood on the water not ten steps from me, and the lake turned clear as glass beneath it.
>
> Ten years I've chased it. I know its tracks, its wind, the way puddles taste after it passes.
>
> And it looked straight through me… at the door you came in by.
>
> No! Before it chooses you again, I'll prove myself!

**Derrota**

> Again. It's always you, isn't it?

**Depois da luta**

> You know what ten years of chasing teaches you? How to recognize the one it's waiting for.
>
> It was never going to be me. I think I knew that in the Burned Tower.
>
> Fine. Then I'll be the one who knows it best. Go on. It's been waiting.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Eusine_Suicune_ChampionIntro:
	.string "It's here! It stood on the water not\n"
	.string "ten steps from me, and the lake turned\l"
	.string "clear as glass beneath it.\p"
	.string "Ten years I've chased it. I know its\n"
	.string "tracks, its wind, the way puddles taste\l"
	.string "after it passes.\p"
	.string "And it looked straight through me… at\n"
	.string "the door you came in by.\p"
	.string "No! Before it chooses you again, I'll\n"
	.string "prove myself!$"

Nexus_Text_Eusine_Suicune_ChampionDefeat:
	.string "Again. It's always you, isn't it?$"

Nexus_Text_Eusine_Suicune_ChampionAfter:
	.string "{SPEAKER NAME_EUSINE}You know what ten years of chasing\n"
	.string "teaches you? How to recognize the one\l"
	.string "it's waiting for.\p"
	.string "It was never going to be me. I think I\n"
	.string "knew that in the Burned Tower.\p"
	.string "Fine. Then I'll be the one who knows it\n"
	.string "best. Go on. It's been waiting.$"
```

</details>

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mais duas falas de campeão para este lendário ([R16](../NEXUS_REGRAS.md)), sem dizer o nome da espécie. A variação 1 é a de cima, que já está no jogo.

**Variação 2** — humor de pesquisador: ele provou a água do lago. Gosto de nada, puro. Depois: a criatura não anda na água, anda na água limpa; a sujeira solta porque pode, não porque é forçada.

**Antes da luta**

> I tasted the lake. For science. It tastes like nothing. Pure nothing!
>
> Ten years of puddles, and every one tasted a little of it. This one tastes of nothing else.
>
> …That sounds poetic. It isn't. It's research. Battle me!

**Derrota**

> Ha… I'm soaked, and not even from the lake.

**Depois da luta**

> Here's one for your notebook. It never walks on water. It walks on clean water.
>
> Where it steps, the dirt lets go. Not because it's forced to. Because it's allowed to.
>
> Keep your heart clean when you face it. Or at least… rinsed. Go!

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Eusine_Suicune_ChampionIntro2:
	.string "I tasted the lake. For science. It\n"
	.string "tastes like nothing. Pure nothing!\p"
	.string "Ten years of puddles, and every one\n"
	.string "tasted a little of it. This one tastes\l"
	.string "of nothing else.\p"
	.string "…That sounds poetic. It isn't. It's\n"
	.string "research. Battle me!$"

Nexus_Text_Eusine_Suicune_ChampionDefeat2:
	.string "Ha… I'm soaked, and not even from the\n"
	.string "lake.$"

Nexus_Text_Eusine_Suicune_ChampionAfter2:
	.string "{SPEAKER NAME_EUSINE}Here's one for your notebook. It never\n"
	.string "walks on water. It walks on clean water.\p"
	.string "Where it steps, the dirt lets go. Not\n"
	.string "because it's forced to. Because it's\l"
	.string "allowed to.\p"
	.string "Keep your heart clean when you face it.\n"
	.string "Or at least… rinsed. Go!$"
```

</details>

**Variação 3** — a dúvida que tira o sono: e se ela o escolheu anos atrás e ele estava ocupado demais anotando? Ele confere as notas: numa manhã de chuva, parou para amarrar a bota.

**Antes da luta**

> Here's what keeps me up at night. What if it chose me years ago, and I was too busy chasing to notice?
>
> What if it slowed down once, on some rainy road, and I was looking at my notes?
>
> …No. No, I refuse to believe that. Let's battle!

**Derrota**

> …I'll check my notes. All ten years of them.

**Depois da luta**

> I checked. One entry, a rainy morning. 'Wind from the north. Stopped to tie my boot.'
>
> That's all. I stopped to tie my boot.
>
> Go on. Don't stop for anything. Especially not your boots.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Eusine_Suicune_ChampionIntro3:
	.string "Here's what keeps me up at night. What\n"
	.string "if it chose me years ago, and I was too\l"
	.string "busy chasing to notice?\p"
	.string "What if it slowed down once, on some\n"
	.string "rainy road, and I was looking at my\l"
	.string "notes?\p"
	.string "…No. No, I refuse to believe that. Let's\n"
	.string "battle!$"

Nexus_Text_Eusine_Suicune_ChampionDefeat3:
	.string "…I'll check my notes. All ten years of\n"
	.string "them.$"

Nexus_Text_Eusine_Suicune_ChampionAfter3:
	.string "{SPEAKER NAME_EUSINE}I checked. One entry, a rainy morning.\n"
	.string "'Wind from the north. Stopped to tie my\l"
	.string "boot.'\p"
	.string "That's all. I stopped to tie my boot.\p"
	.string "Go on. Don't stop for anything.\n"
	.string "Especially not your boots.$"
```

</details>

#### Raikou

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Eusine_Raikou_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Eusine é o **campeão**, a luta logo antes do Raikou. A fala é sobre a criatura, sem dizer o nome dela.

O Raikou foi o primeiro a fugir da torre, e o mais rápido: em dez anos o Eusine nunca conseguiu uma foto dele. A virada é a conta que o Eusine fez e ninguém faz: a torre pegou fogo porque um raio a atingiu, e o Pokémon que morreu naquele fogo voltou como o raio. Ele ainda está com raiva, e não se corre tão rápido de nada. O pedido: não leve o rugido para o lado pessoal.

**Antes da luta**

> Did you feel that? The thunder here never stops. The bolt just hangs in the sky, as if it forgot to finish falling.
>
> In the old tower, three Pokémon burned and three beasts ran out. This one ran first, and fastest.
>
> In ten years, I never managed a single photograph of it.
>
> Today I will! After I beat you, naturally!

**Derrota**

> My hands are shaking. Is that you, or the thunder?

**Depois da luta**

> The tower burned because lightning struck it. One of the Pokémon that died in that fire came back as lightning.
>
> Think about that. You don't run that fast from nothing. I think it's still angry.
>
> Don't take it personally when it roars. Nobody put that fire out in time. Not for it.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Eusine_Raikou_ChampionIntro:
	.string "Did you feel that? The thunder here\n"
	.string "never stops. The bolt just hangs in the\l"
	.string "sky, as if it forgot to finish falling.\p"
	.string "In the old tower, three Pokémon burned\n"
	.string "and three beasts ran out. This one ran\l"
	.string "first, and fastest.\p"
	.string "In ten years, I never managed a single\n"
	.string "photograph of it.\p"
	.string "Today I will! After I beat you,\n"
	.string "naturally!$"

Nexus_Text_Eusine_Raikou_ChampionDefeat:
	.string "My hands are shaking. Is that you, or\n"
	.string "the thunder?$"

Nexus_Text_Eusine_Raikou_ChampionAfter:
	.string "{SPEAKER NAME_EUSINE}The tower burned because lightning\n"
	.string "struck it. One of the Pokémon that died\l"
	.string "in that fire came back as lightning.\p"
	.string "Think about that. You don't run that\n"
	.string "fast from nothing. I think it's still\l"
	.string "angry.\p"
	.string "Don't take it personally when it roars.\n"
	.string "Nobody put that fire out in time. Not\l"
	.string "for it.$"
```

</details>

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mais duas falas de campeão para este lendário ([R16](../NEXUS_REGRAS.md)), sem dizer o nome da espécie. A variação 1 é a de cima, que já está no jogo.

**Variação 2** — a câmera: setenta rolos de filme e setenta fotos de um borrão. Em todo borrão a forma corre para longe da torre. Não se fotografa quem vai embora para sempre.

**Antes da luta**

> I've brought a camera. Seventy rolls of film. A tripod with rubber feet, obviously.
>
> The thunder here has gone on for hours, and I have seventy photographs of a blur.
>
> …They say battling steadies the hands. Let's test that!

**Derrota**

> My hands are worse now. Thank you so much.

**Depois da luta**

> I went through the photos again. In every blur there's a shape, running away from the tower.
>
> Not toward anything. Away.
>
> Maybe that's why I never caught it on film. You can't photograph someone leaving forever. Go.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Eusine_Raikou_ChampionIntro2:
	.string "I've brought a camera. Seventy rolls of\n"
	.string "film. A tripod with rubber feet,\l"
	.string "obviously.\p"
	.string "The thunder here has gone on for hours,\n"
	.string "and I have seventy photographs of a\l"
	.string "blur.\p"
	.string "…They say battling steadies the hands.\n"
	.string "Let's test that!$"

Nexus_Text_Eusine_Raikou_ChampionDefeat2:
	.string "My hands are worse now. Thank you so\n"
	.string "much.$"

Nexus_Text_Eusine_Raikou_ChampionAfter2:
	.string "{SPEAKER NAME_EUSINE}I went through the photos again. In\n"
	.string "every blur there's a shape, running\l"
	.string "away from the tower.\p"
	.string "Not toward anything. Away.\p"
	.string "Maybe that's why I never caught it on\n"
	.string "film. You can't photograph someone\l"
	.string "leaving forever. Go.$"
```

</details>

**Variação 3** — a história do Morty: na noite do incêndio o sino da torre tocou sozinho, com o raio. A criatura é o que sobrou daquela nota, que nunca parou de tocar.

**Antes da luta**

> Morty told me a story, from the old men of Ecruteak. The night the tower burned, its bell rang by itself.
>
> Not from the wind. From the lightning. One strike, and the whole tower sang.
>
> …I think the beast out there is what's left of that note. Let's battle!

**Derrota**

> Ha. My ears are ringing. Coincidence, surely.

**Depois da luta**

> If it's a note, it's the loudest one ever played, and it never stopped.
>
> Every roar is that bell, still ringing, a hundred and fifty years later.
>
> When you face it, listen for the end of the note. I never could. Maybe you will.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Eusine_Raikou_ChampionIntro3:
	.string "Morty told me a story, from the old men\n"
	.string "of Ecruteak. The night the tower\l"
	.string "burned, its bell rang by itself.\p"
	.string "Not from the wind. From the lightning.\n"
	.string "One strike, and the whole tower sang.\p"
	.string "…I think the beast out there is what's\n"
	.string "left of that note. Let's battle!$"

Nexus_Text_Eusine_Raikou_ChampionDefeat3:
	.string "Ha. My ears are ringing. Coincidence,\n"
	.string "surely.$"

Nexus_Text_Eusine_Raikou_ChampionAfter3:
	.string "{SPEAKER NAME_EUSINE}If it's a note, it's the loudest one\n"
	.string "ever played, and it never stopped.\p"
	.string "Every roar is that bell, still ringing, a\n"
	.string "hundred and fifty years later.\p"
	.string "When you face it, listen for the end of\n"
	.string "the note. I never could. Maybe you will.$"
```

</details>

#### Entei

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Eusine_Entei_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Eusine é o **campeão**, a luta logo antes do Entei. A fala é sobre a criatura, sem dizer o nome dela.

O Eusine leu sobre aquele incêndio a vida toda, e aqui a torre ainda está queimando na frente dele. No meio do fogo alguma coisa latiu e as chamas deitaram como cães. A virada é uma leitura que não está em livro nenhum: a lenda diz que o Entei nasceu de um vulcão; o Eusine acha que ele nasceu naquele fogo e escolheu virar um. Se você não pode escapar do fogo, pode decidir ser o fogo. O pedido: vá com cuidado, o que sobrou dele já queimou uma vez.

**Antes da luta**

> I've read about that fire all my life. The tower. The storm. The three who didn't get out.
>
> Here, it's still burning. I can feel the heat on my face.
>
> And in the middle of it, something barked, and the flames lay down like dogs.
>
> I'm shaking, and it isn't fear. Battle me before I lose my nerve!

**Derrota**

> Ha… I lost my nerve anyway.

**Depois da luta**

> The stories say it was born from a volcano. I think it was born in that fire, and chose to become one.
>
> If you can't escape a fire, you can decide to be the fire. That's… not in any book.
>
> Go gently. Whatever is left of it has burned once already.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Eusine_Entei_ChampionIntro:
	.string "I've read about that fire all my life.\n"
	.string "The tower. The storm. The three who\l"
	.string "didn't get out.\p"
	.string "Here, it's still burning. I can feel the\n"
	.string "heat on my face.\p"
	.string "And in the middle of it, something\n"
	.string "barked, and the flames lay down like\l"
	.string "dogs.\p"
	.string "I'm shaking, and it isn't fear. Battle\n"
	.string "me before I lose my nerve!$"

Nexus_Text_Eusine_Entei_ChampionDefeat:
	.string "Ha… I lost my nerve anyway.$"

Nexus_Text_Eusine_Entei_ChampionAfter:
	.string "{SPEAKER NAME_EUSINE}The stories say it was born from a\n"
	.string "volcano. I think it was born in that\l"
	.string "fire, and chose to become one.\p"
	.string "If you can't escape a fire, you can\n"
	.string "decide to be the fire. That's… not in\l"
	.string "any book.\p"
	.string "Go gently. Whatever is left of it has\n"
	.string "burned once already.$"
```

</details>

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mais duas falas de campeão para este lendário ([R16](../NEXUS_REGRAS.md)), sem dizer o nome da espécie. A variação 1 é a de cima, que já está no jogo.

**Variação 2** — humor: a capa pegou fogo duas vezes na entrada. O fogo daqui não se espalha: fica onde estava naquela noite, esperando permissão. Depois: ele ouviu o rugido e nenhum vulcão respondeu; a torre só queimou mais forte, como quem escuta.

**Antes da luta**

> My cape caught fire twice on the way in. It's fine. It's a very resilient cape.
>
> The fire here doesn't spread. It stays exactly where it was that night, as if waiting for permission.
>
> …I won't give it permission. I'll give you a battle instead!

**Derrota**

> Ha… my cape is the only thing still burning.

**Depois da luta**

> The legend says it roars and volcanoes answer. I heard it roar just now.
>
> Nothing answered. The tower just burned a little brighter, like it was listening.
>
> Go carefully. It isn't angry. It's just loud. Very, very loud.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Eusine_Entei_ChampionIntro2:
	.string "My cape caught fire twice on the way in.\n"
	.string "It's fine. It's a very resilient cape.\p"
	.string "The fire here doesn't spread. It stays\n"
	.string "exactly where it was that night, as if\l"
	.string "waiting for permission.\p"
	.string "…I won't give it permission. I'll give\n"
	.string "you a battle instead!$"

Nexus_Text_Eusine_Entei_ChampionDefeat2:
	.string "Ha… my cape is the only thing still\n"
	.string "burning.$"

Nexus_Text_Eusine_Entei_ChampionAfter2:
	.string "{SPEAKER NAME_EUSINE}The legend says it roars and volcanoes\n"
	.string "answer. I heard it roar just now.\p"
	.string "Nothing answered. The tower just\n"
	.string "burned a little brighter, like it was\l"
	.string "listening.\p"
	.string "Go carefully. It isn't angry. It's just\n"
	.string "loud. Very, very loud.$"
```

</details>

**Variação 3** — o luto: ninguém escreveu o que os três eram antes do fogo. Nenhum nome, nenhuma espécie. Ele perguntou à criatura, e ela deitou nas chamas como um cão ao pé da cama: era de alguém.

**Antes da luta**

> Nobody wrote down what they were before. The three who died in the fire. Not in one book.
>
> A hundred and fifty years of scholarship, and not one name. Not even a species.
>
> …I'll find out someday. Today I'll settle for a battle!

**Derrota**

> …Settled. Painfully.

**Depois da luta**

> I asked it. What were you, before the fire? It looked at me for a very long time.
>
> Then it lay down in the flames, the way a dog lies down at the foot of a bed.
>
> …I think that was the answer. It was someone's. Go gently.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Eusine_Entei_ChampionIntro3:
	.string "Nobody wrote down what they were\n"
	.string "before. The three who died in the fire.\l"
	.string "Not in one book.\p"
	.string "A hundred and fifty years of\n"
	.string "scholarship, and not one name. Not even\l"
	.string "a species.\p"
	.string "…I'll find out someday. Today I'll\n"
	.string "settle for a battle!$"

Nexus_Text_Eusine_Entei_ChampionDefeat3:
	.string "…Settled. Painfully.$"

Nexus_Text_Eusine_Entei_ChampionAfter3:
	.string "{SPEAKER NAME_EUSINE}I asked it. What were you, before the\n"
	.string "fire? It looked at me for a very long\l"
	.string "time.\p"
	.string "Then it lay down in the flames, the way a\n"
	.string "dog lies down at the foot of a bed.\p"
	.string "…I think that was the answer. It was\n"
	.string "someone's. Go gently.$"
```

</details>

Falante novo: `SP_NAME_EUSINE` (o `_ChampionAfter` usa `{SPEAKER NAME_EUSINE}`; ainda não existe em `include/constants/speaker_names.h`, skill `nomear-falante`).
