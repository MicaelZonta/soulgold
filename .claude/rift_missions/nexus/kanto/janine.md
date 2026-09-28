# Janine

**Região da ficha:** Kanto

Aparece no checklist como:

- **Janine — Veneno** (Kanto · Líderes de Ginásio) — filha de Koga que assume o Ginásio de Fuchsia em *Gold/Silver/Crystal* e *HGSS*.

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
| `OBJ_EVENT_GFX_JANINE` | `graphics/object_events/pics/people/gym_leaders/janine.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_LEADER_JANINE` | `graphics/trainers/front_pics/janine.png` |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_JANINE` | 305 | 0x631 | Weezing Lv63, Muk Lv62, Toxapex Lv61, Nidoqueen Lv62, Crobat Lv63, Muk Alola Lv64 | `FuchsiaCity_Gym`, `SaffronCity_FightingDojoVIP`, `src/battle_dome.c`, `src/battle_setup.c` |

### Time das Rift Missions

✅ **Implementado em 27/09/2026** (a proposta abaixo virou código): `TRAINER_NEXUS_JANINE` = **1040** (flag de batalha `0x910`, limpa antes e depois de cada luta), bloco em `src/data/trainers.party`, nível pelo R2 (tabela em `src/data/nexus/trainers.h`). Fala genérica `Nexus_EventScript_Janine_Fight`; campeão: `Nexus_EventScript_Janine_Okidogi_ChampionFight` (para Okidogi), `Nexus_EventScript_Janine_Munkidori_ChampionFight` (para Munkidori). Tudo em `data/scripts/nexus.inc`, sem blackout, resultado em `VAR_TEMP_3`. Para testar: menu de debug → Rift Missions… → Nexus fights… → Janine.

📝 **Proposta de 27/09/2026, aguardando o autor.** `TRAINER_NEXUS_JANINE`, campeã de Okidogi e Munkidori. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler). `Double Battle: Yes` é o formato em que o time brilha mais; o plano vale nos dois.

Lendário **Marshadow**, o Pokémon que mora nas sombras e imita os movimentos de quem segue: um ninja de verdade, e a arte da Janine é justamente o disfarce e a imitação. Semi-lendário **Munkidori**, de quem ela é campeã, o macaco que confunde a cabeça dos outros. Mega **Gengar** (Ghostite), o Veneno/Fantasma que vive na sombra dos outros; com Shadow Tag, ninguém foge dele, como ninguém foge de um ninja. Mais **Crobat** (o ás dela em GSC/HGSS), **Ariados** (GSC/HGSS) e **Weezing de Galar**, o Weezing dela *disfarçado*. *Plano (Singles):* o Ariados arma Sticky Web e Toxic Spikes, o Crobat dá Taunt e sai de U-turn, o Marshadow rouba os boosts do adversário com Spectral Thief, e a Mega Gengar (Shadow Tag) prende e derruba o que ficou, com Destiny Bond como último truque. *Plano (Doubles):* Fake Out do Munkidori, Rage Powder do Ariados puxando os golpes, Tailwind do Crobat, e o Weezing de Galar queima e apaga boosts com Clear Smog.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Marshadow | Life Orb | Technician | Jolly | Spectral Thief, Close Combat, Shadow Sneak, Ice Punch |
| Munkidori | Focus Sash | Toxic Chain | Timid | Fake Out, Sludge Bomb, Psychic, U-turn |
| Gengar | Ghostite | Cursed Body | Timid | Shadow Ball, Sludge Bomb, Focus Blast, Destiny Bond |
| Crobat | Sitrus Berry | Infiltrator | Jolly | Brave Bird, Tailwind, Taunt, U-turn |
| Ariados | Mental Herb | Insomnia | Careful | Sticky Web, Toxic Spikes, Rage Powder, Sucker Punch |
| Weezing-Galar | Rocky Helmet | Levitate | Bold | Strange Steam, Will-O-Wisp, Clear Smog, Pain Split |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>dev_scripts/nexus_validar_time.py</code>)</summary>

```
=== TRAINER_NEXUS_JANINE ===
Name: Janine
Class: Leader
Pic: Leader Janine
Gender: Female
Music: Female
Double Battle: Yes
AI: Smart Trainer

Marshadow @ Life Orb
Jolly Nature
Level: 100
Ability: Technician
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Spectral Thief
- Close Combat
- Shadow Sneak
- Ice Punch

Munkidori @ Focus Sash
Timid Nature
Level: 100
Ability: Toxic Chain
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Fake Out
- Sludge Bomb
- Psychic
- U-turn

Gengar @ Ghostite
Timid Nature
Level: 100
Ability: Cursed Body
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Shadow Ball
- Sludge Bomb
- Focus Blast
- Destiny Bond

Crobat @ Sitrus Berry
Jolly Nature
Level: 100
Ability: Infiltrator
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Brave Bird
- Tailwind
- Taunt
- U-turn

Ariados @ Mental Herb
Careful Nature
Level: 100
Ability: Insomnia
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Sticky Web
- Toxic Spikes
- Rage Powder
- Sucker Punch

Weezing-Galar @ Rocky Helmet
Bold Nature
Level: 100
Ability: Levitate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Strange Steam
- Will-O-Wisp
- Clear Smog
- Pain Split
```

</details>


### Lendário associado

#### Okidogi

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_Okidogi_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Okidogi**. Janine é a campeã dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Janine, filha do Koga e Líder de Fuchsia depois dele. Ninja em treino, cheia de energia; no ginásio dela todos os alunos se vestem de Janine.

**A criatura.** Okidogi, um dos Loyal Three de Kitakami: brigão de pavio curto, o braço direito musculoso derruba um caminhão. A corrente tóxica aumenta a força dele. A vila ergueu estátuas dos três como heróis, mas os verdadeiros vilões da lenda eram eles.

**O fragmento.** Uma vila de montanha ao anoitecer. Na praça, três estátuas de pedra em fila, cobertas de flores frescas. Uma delas está rachada, como se a coisa que ela mostra tivesse saído a socos.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário). Pelo [R17](../NEXUS_REGRAS.md), o que o jogador leva é o fragmento que sobra, no nível 1; a ficha do Looker fala desse pedaço, não da criatura domada.

**Chegada**

> A mountain village at dusk. In the square stood three stone statues in a row, heaped with fresh flowers.
>
> One was cracked open, as if the thing it showed had punched its way out.

**Boss**

> A chain rattled somewhere in the dark, and the smell of poison came with it.
>
> Something huge and grinning stepped down from the empty pedestal.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento**

> File L-1014. Retainer.
>
> A village that raised a statue to a bully, and a young ninja who knows a disguise when she sees one.
>
> What you brought back has no chain yet, and no statue. It will have to earn both. She approves.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Okidogi_Arrival:
	.string "A mountain village at dusk. In the\n"
	.string "square stood three stone statues in a\l"
	.string "row, heaped with fresh flowers.\p"
	.string "One was cracked open, as if the thing it\n"
	.string "showed had punched its way out.$"

Nexus_Text_Okidogi_Boss:
	.string "A chain rattled somewhere in the dark,\n"
	.string "and the smell of poison came with it.\p"
	.string "Something huge and grinning stepped\n"
	.string "down from the empty pedestal.$"

Nexus_Text_Okidogi_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-1014. Retainer.\p"
	.string "A village that raised a statue to a\n"
	.string "bully, and a young ninja who knows a\l"
	.string "disguise when she sees one.\p"
	.string "What you brought back has no chain yet,\n"
	.string "and no statue. It will have to earn\l"
	.string "both. She approves.$"
```

</details>


#### Munkidori

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_Munkidori_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Munkidori**. Janine é a campeã dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Janine, ninja de Fuchsia e filha do Koga. A brincadeira favorita dela é vestir os alunos de Janine para confundir o desafiante.

**A criatura.** Munkidori, outro dos Loyal Three. A corrente tóxica estimulou o cérebro dele e despertou poderes psíquicos; ele os usa para confundir e enganar quem cruza o caminho.

**O fragmento.** Um bambuzal em que os caminhos mudam de lugar: toda curva volta para a mesma lanterna de pedra. Longe, alguém ri, e a risada tem a voz de quem está ouvindo.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário). Pelo [R17](../NEXUS_REGRAS.md), o que o jogador leva é o fragmento que sobra, no nível 1; a ficha do Looker fala desse pedaço, não da criatura domada.

**Chegada**

> A bamboo forest where the paths kept moving. Every turn led back to the same stone lantern.
>
> Far away, someone was laughing. It sounded like your own voice.

**Boss**

> The lantern flickered, and the bamboo leaned in close.
>
> Something small with a chain across its shoulders dropped from above, and your reflection in its eyes waved at you.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento**

> File L-1015. Retainer.
>
> A forest that showed everyone what they feared, and a ninja who saw only her father, and then herself.
>
> The piece that came back with you is small and has not learned a single trick. I checked twice. Then a third time.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Munkidori_Arrival:
	.string "A bamboo forest where the paths kept\n"
	.string "moving. Every turn led back to the same\l"
	.string "stone lantern.\p"
	.string "Far away, someone was laughing. It\n"
	.string "sounded like your own voice.$"

Nexus_Text_Munkidori_Boss:
	.string "The lantern flickered, and the bamboo\n"
	.string "leaned in close.\p"
	.string "Something small with a chain across its\n"
	.string "shoulders dropped from above, and your\l"
	.string "reflection in its eyes waved at you.$"

Nexus_Text_Munkidori_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-1015. Retainer.\p"
	.string "A forest that showed everyone what\n"
	.string "they feared, and a ninja who saw only\l"
	.string "her father, and then herself.\p"
	.string "The piece that came back with you is\n"
	.string "small and has not learned a single trick.\l"
	.string "I checked twice. Then a third time.$"
```

</details>


### Diálogo genérico

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Janine_Fight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Janine cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala dela mesma, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

**Antes da luta**

> Surprise! Bet you thought I was one of my students. Or were they all me?
>
> Father taught me how to hide. I taught myself how to jump out!
>
> Ninja arts, full power! Hyah!

**Derrota**

> Aw… You saw through the real me. That's rarer than you think.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Janine_Intro:
	.string "Surprise! Bet you thought I was one of\n"
	.string "my students. Or were they all me?\p"
	.string "Father taught me how to hide. I taught\n"
	.string "myself how to jump out!\p"
	.string "Ninja arts, full power! Hyah!$"

Nexus_Text_Janine_Defeat:
	.string "Aw… You saw through the real me. That's\n"
	.string "rarer than you think.$"
```

</details>


### Diálogo associado ao lendário

#### Okidogi

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Janine_Okidogi_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Janine é a **campeã**, a luta logo antes do Okidogi. A fala é sobre a criatura, sem dizer o nome dela.

A Janine viu o cachorrão socar uma pedra só para se mostrar e viu a estátua dele na praça, herói segundo a placa. A virada é que ela entende de fantasia: uma estátua é só uma fantasia de pedra. Depois ela fala de si: em casa todo mundo a chama de filha do Koga, uma estátua dela para a qual ela nunca posou, e ela ganha o nome de verdade uma luta de cada vez. A criatura nunca precisou ganhar nada: a corrente dá a força e a estátua dá a glória.

**Antes da luta**

> Hey! Did you see the big one with the chain? It punched a boulder in half just to show off.
>
> There's a statue of it in the square. Flowers at its feet. A hero, says the sign.
>
> Funny… Nobody here would tell me what it did to deserve it.
>
> I know costumes. A statue's just a costume made of stone. Hyah!

**Derrota**

> Oof! You hit harder than that thing ever did.

**Depois da luta**

> Back home, everyone calls me Koga's daughter. It's like a statue of me I never posed for.
>
> So I earn my real name. One battle at a time.
>
> That brute never had to earn anything. The chain gives it strength, and the statue gives it glory.
>
> Take both away and see what's left. My guess? Not much.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Janine_Okidogi_ChampionIntro:
	.string "Hey! Did you see the big one with the\n"
	.string "chain? It punched a boulder in half\l"
	.string "just to show off.\p"
	.string "There's a statue of it in the square.\n"
	.string "Flowers at its feet. A hero, says the\l"
	.string "sign.\p"
	.string "Funny… Nobody here would tell me what\n"
	.string "it did to deserve it.\p"
	.string "I know costumes. A statue's just a\n"
	.string "costume made of stone. Hyah!$"

Nexus_Text_Janine_Okidogi_ChampionDefeat:
	.string "Oof! You hit harder than that thing\n"
	.string "ever did.$"

Nexus_Text_Janine_Okidogi_ChampionAfter:
	.string "{SPEAKER NAME_JANINE}Back home, everyone calls me Koga's\n"
	.string "daughter. It's like a statue of me I\l"
	.string "never posed for.\p"
	.string "So I earn my real name. One battle at a\n"
	.string "time.\p"
	.string "That brute never had to earn anything.\n"
	.string "The chain gives it strength, and the\l"
	.string "statue gives it glory.\p"
	.string "Take both away and see what's left. My\n"
	.string "guess? Not much.$"
```

</details>


#### Munkidori

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Janine_Munkidori_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Janine é a **campeã**, a luta logo antes do Munkidori. A fala é sobre a criatura, sem dizer o nome dela.

A Janine também caiu no truque: viu o pai no caminho, depois viu a si mesma. A virada é a comparação com o jogo dela: ela veste os alunos de Janine e todo mundo ri no final; aquilo não ri no final, só fica olhando. Depois, o segredo de ninja: todo bom disfarce tem uma costura, uma saída, para a piada poder acabar; o que o macaco mostra não tem costura. Confie nos seus Pokémon, não nos olhos. E se você me vir lá dentro, não sou eu.

**Antes da luta**

> Did it get you too? The little monkey? I saw my father standing on the path. Then I saw me.
>
> That wasn't a trick of the light. It crawled into my head and moved the furniture around.
>
> I dress my students up as me. It's a game! We all laugh after.
>
> That thing doesn't laugh after. It just watches. Hyah!

**Derrota**

> You didn't blink once. How?!

**Depois da luta**

> Here's a ninja secret. A good disguise always has a seam. A way out, so the joke can end.
>
> What that monkey shows you has no seam. You just keep looking.
>
> If the world starts to wobble, trust your Pokémon, not your eyes. They can smell what's real.
>
> …And if you see me in there, it isn't me. Promise.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Janine_Munkidori_ChampionIntro:
	.string "Did it get you too? The little monkey? I\n"
	.string "saw my father standing on the path.\l"
	.string "Then I saw me.\p"
	.string "That wasn't a trick of the light. It\n"
	.string "crawled into my head and moved the\l"
	.string "furniture around.\p"
	.string "I dress my students up as me. It's a\n"
	.string "game! We all laugh after.\p"
	.string "That thing doesn't laugh after. It just\n"
	.string "watches. Hyah!$"

Nexus_Text_Janine_Munkidori_ChampionDefeat:
	.string "You didn't blink once. How?!$"

Nexus_Text_Janine_Munkidori_ChampionAfter:
	.string "{SPEAKER NAME_JANINE}Here's a ninja secret. A good disguise\n"
	.string "always has a seam. A way out, so the\l"
	.string "joke can end.\p"
	.string "What that monkey shows you has no\n"
	.string "seam. You just keep looking.\p"
	.string "If the world starts to wobble, trust\n"
	.string "your Pokémon, not your eyes. They can\l"
	.string "smell what's real.\p"
	.string "…And if you see me in there, it isn't me.\n"
	.string "Promise.$"
```

</details>


Falante novo: `SP_NAME_JANINE` (ainda não existe em `include/constants/speaker_names.h`).
