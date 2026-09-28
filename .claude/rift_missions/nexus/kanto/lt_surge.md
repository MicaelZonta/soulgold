# Lt. Surge

**Região da ficha:** Kanto

Aparece no checklist como:

- **Lt. Surge — Elétrico** (Kanto · Líderes de Ginásio) — veterano militar e Líder de Vermilion.

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
| `OBJ_EVENT_GFX_SURGE` | `graphics/object_events/pics/people/gym_leaders/surge.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_LEADER_SURGE` | `graphics/trainers/front_pics/surge.png` |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_LTSURGE` | 302 | 0x62E | Electrode Lv57, Magnezone Lv59, Lanturn Lv58, Manectric Lv58, Electivire Lv59, Raichu Lv60 | `SaffronCity_FightingDojoVIP`, `VermilionCity_Gym`, `src/battle_dome.c`, `src/battle_setup.c`, `src/match_call.c` |

### Time das Rift Missions

✅ **Implementado em 27/09/2026** (a proposta abaixo virou código): `TRAINER_NEXUS_LT_SURGE` = **989** (flag de batalha `0x8DD`, limpa antes e depois de cada luta), bloco em `src/data/trainers.party`, nível pelo R2 (tabela em `src/data/nexus/trainers.h`). Fala genérica `Nexus_EventScript_LtSurge_Fight`; campeão: `Nexus_EventScript_LtSurge_Zapdos_ChampionFight` (para Zapdos), `Nexus_EventScript_LtSurge_SandyShocks_ChampionFight` (para Sandy Shocks), `Nexus_EventScript_LtSurge_Regieleki_ChampionFight` (para Regieleki). Tudo em `data/scripts/nexus.inc`, sem blackout, resultado em `VAR_TEMP_3`. Para testar: menu de debug → Rift Missions… → Nexus fights… → Lt. Surge.

📝 **Proposta de 27/09/2026, aguardando o autor.** `TRAINER_NEXUS_LT_SURGE`, campeão de Zapdos, Regieleki e Sandy Shocks. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler).

Lendário **Zekrom**, o dragão do raio e dos ideais: o soldado que vive de disciplina e convicção. Semi-lendário **Regieleki** (dos três de que ele é campeão, o que mais serve ao time: Electroweb controla velocidade nos dois formatos; Zapdos e Sandy Shocks ficam fora porque só cabe um semi), a eletricidade pura presa em anéis. Mega **Raichu X** (Electrite), o Raichu do "Lightning American", ás dele desde Red/Blue. Mais Electivire, Magnezone e Electrode, do time de Vermilion da campanha (o Electrode é o Voltorb das latas de lixo do ginásio). É o monotipo Elétrico mais puro possível; "Electric Pokémon saved me during the war!"

*Plano (Singles):* velocidade e pivot. O Electrode (Focus Sash) abre com Taunt e Thunder Wave e sai com Volt Switch; o Regieleki (Transistor) e a Magnezone pivotam com Volt Switch até achar a brecha; o Zekrom sobe Dragon Dance e limpa com Bolt Strike (Teravolt ignora habilidades defensivas). Contra Terra: Grass Knot no Raichu, Ice Punch no Electivire, Air Balloon na Magnezone, e o Zekrom é Dragão.

*Plano (Doubles):* Fake Out do Mega Raichu + Electroweb do Regieleki (acerta os dois e tira velocidade) no primeiro turno; o Raichu base tem Lightning Rod antes de megaevoluir; o Electivire (Motor Drive) e o Zekrom batem em alvo único. Nenhum Discharge nem Earthquake: nada acerta o parceiro.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Zekrom | Life Orb | Teravolt | Adamant | Bolt Strike, Dragon Claw, Dragon Dance, Crunch |
| Regieleki | Life Orb | Transistor | Timid | Thunderbolt, Electroweb, Volt Switch, Extreme Speed |
| Raichu | Electrite | Lightning Rod | Timid | Fake Out, Thunderbolt, Grass Knot, Nasty Plot |
| Electivire | Expert Belt | Motor Drive | Adamant | Wild Charge, Ice Punch, Cross Chop, Fire Punch |
| Magnezone | Air Balloon | Sturdy | Modest | Thunderbolt, Flash Cannon, Volt Switch, Body Press |
| Electrode | Focus Sash | Aftermath | Timid | Taunt, Volt Switch, Thunder Wave, Foul Play |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>dev_scripts/nexus_validar_time.py</code>: trainerproc, constantes, learnsets e categorias)</summary>

```
=== TRAINER_NEXUS_LT_SURGE ===
Name: Lt. Surge
Class: Leader
Pic: Leader Surge
Gender: Male
Music: Male
Double Battle: Yes
AI: Smart Trainer

Zekrom @ Life Orb
Adamant Nature
Level: 100
Ability: Teravolt
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Bolt Strike
- Dragon Claw
- Dragon Dance
- Crunch

Regieleki @ Life Orb
Timid Nature
Level: 100
Ability: Transistor
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Thunderbolt
- Electroweb
- Volt Switch
- Extreme Speed

Raichu @ Electrite
Timid Nature
Level: 100
Ability: Lightning Rod
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Fake Out
- Thunderbolt
- Grass Knot
- Nasty Plot

Electivire @ Expert Belt
Adamant Nature
Level: 100
Ability: Motor Drive
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Wild Charge
- Ice Punch
- Cross Chop
- Fire Punch

Magnezone @ Air Balloon
Modest Nature
Level: 100
Ability: Sturdy
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Thunderbolt
- Flash Cannon
- Volt Switch
- Body Press

Electrode @ Focus Sash
Timid Nature
Level: 100
Ability: Aftermath
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Taunt
- Volt Switch
- Thunder Wave
- Foul Play
```

</details>

### Lendário associado

#### Zapdos

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_Zapdos_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Zapdos**. Lt. Surge é o campeão dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Lt. Surge, Líder de Vermilion, veterano de guerra, "the Lightning American". Em Red/Blue: "Electric Pokémon saved me during the war!" O ginásio dele esconde a porta atrás de interruptores em latas de lixo.

**A criatura.** Zapdos, a ave lendária do trovão, aparece de nuvens de tempestade e fica mais forte quando atingido por um raio. Em Red/Blue/FireRed vive na Power Plant abandonada de Kanto.

**O fragmento.** Uma usina abandonada: toda máquina morta, enferrujada, desmontada. E mesmo assim todas as luzes estão acesas, zumbindo, alimentadas por nada que se veja. A usina roda com uma tempestade.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A power plant, long abandoned. Every machine was dead, rusted, gutted.
>
> And yet every light in the building was on, humming, fed by nothing you could see.

**Boss**

> Thunder rolled, indoors.
>
> Something yellow and jagged dropped out of the dark rafters, and every bulb in the building burst at once.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md))

> File L-145. Electric.
>
> A plant that runs on a storm, and a soldier whose life was saved by lightning once.
>
> What came back with you is a chick. Its feathers crackle when it sneezes. I have learned not to stand close.
>
> He saluted it before he left. I do not think he noticed he was doing it.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Zapdos_Arrival:
	.string "A power plant, long abandoned. Every\n"
	.string "machine was dead, rusted, gutted.\p"
	.string "And yet every light in the building was\n"
	.string "on, humming, fed by nothing you could\l"
	.string "see.$"

Nexus_Text_Zapdos_Boss:
	.string "Thunder rolled, indoors.\p"
	.string "Something yellow and jagged dropped\n"
	.string "out of the dark rafters, and every bulb\l"
	.string "in the building burst at once.$"

Nexus_Text_Zapdos_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-145. Electric.\p"
	.string "A plant that runs on a storm, and a\n"
	.string "soldier whose life was saved by\l"
	.string "lightning once.\p"
	.string "What came back with you is a chick. Its\n"
	.string "feathers crackle when it sneezes. I\l"
	.string "have learned not to stand close.\p"
	.string "He saluted it before he left. I do not\n"
	.string "think he noticed he was doing it.$"
```

</details>

#### Regieleki

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_Regieleki_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Regieleki**. Lt. Surge é o campeão dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** O mesmo Lt. Surge: o soldado barulhento que acredita em disciplina.

**A criatura.** Regieleki é um aglomerado de energia elétrica; o corpo inteiro é um órgão que gera eletricidade. Diz-se que tirar os anéis do corpo dele libera o poder que está preso. Em Sword/Shield dorme na Split-Decision Ruins da Crown Tundra.

**O fragmento.** Uma câmara de pedra selada de todos os lados. No chão, centenas de anéis amarelos quebrados. O ar tem gosto de bateria. Algo que era segurado por anéis e ficou maior do que a gaiola.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A stone chamber, sealed on every side. Hundreds of yellow rings lay on the floor, broken open.
>
> The air tasted like a battery.

**Boss**

> A spark crossed the room faster than you could turn your head. Then it crossed it again.
>
> It stopped in the middle of the chamber, and it had only one ring left.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md))

> File L-894. Electron.
>
> Pure power held in by rings someone else put there, and a soldier who says discipline is the ring you choose.
>
> What came back with you is small, and wears every one of its rings. For now it seems content to.
>
> I am not sure he believes what he said. He said it very loudly.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Regieleki_Arrival:
	.string "A stone chamber, sealed on every side.\n"
	.string "Hundreds of yellow rings lay on the\l"
	.string "floor, broken open.\p"
	.string "The air tasted like a battery.$"

Nexus_Text_Regieleki_Boss:
	.string "A spark crossed the room faster than\n"
	.string "you could turn your head. Then it\l"
	.string "crossed it again.\p"
	.string "It stopped in the middle of the\n"
	.string "chamber, and it had only one ring left.$"

Nexus_Text_Regieleki_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-894. Electron.\p"
	.string "Pure power held in by rings someone\n"
	.string "else put there, and a soldier who says\l"
	.string "discipline is the ring you choose.\p"
	.string "What came back with you is small, and\n"
	.string "wears every one of its rings. For now it\l"
	.string "seems content to.\p"
	.string "I am not sure he believes what he said.\n"
	.string "He said it very loudly.$"
```

</details>

#### Sandy Shocks

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_SandyShocks_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Sandy Shocks**. Lt. Surge é o campeão dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** O mesmo Lt. Surge, veterano: conhece desertos e sabe o que a areia esconde.

**A criatura.** Sandy Shocks é um Pokémon Paradoxo do passado (Scarlet), Elétrico/Terra, parecido com um Magneton antigo coberto por uma juba de areia magnetizada. Veio pela máquina do tempo da Area Zero; o único registro dele é um velho diário de expedição.

**O fragmento.** Um deserto sob céu pesado. A areia se move em linhas, puxada em desenhos como limalha de ferro ao redor de um ímã. Formas redondas e antigas meio enterradas nas dunas, zumbindo. Algo muito velho enterrado e ainda ativo.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A desert under a heavy sky. The sand moved in lines, pulled into patterns like iron filings around a magnet.
>
> Round, old shapes stuck half out of the dunes, humming.

**Boss**

> The dunes pulled together into a shaggy mane of sand.
>
> Underneath it, something old and magnetic lifted its head, and your Poké Balls tugged at your belt.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md))

> File L-989. Paradox.
>
> Something ancient buried under sand and still live, and a soldier who knows exactly what that means.
>
> What came back with you is small and has almost no mane yet. My paper clips follow it around the room.
>
> He walked the desert in straight lines before he would let you cross it. Old habit, he said.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_SandyShocks_Arrival:
	.string "A desert under a heavy sky. The sand\n"
	.string "moved in lines, pulled into patterns\l"
	.string "like iron filings around a magnet.\p"
	.string "Round, old shapes stuck half out of\n"
	.string "the dunes, humming.$"

Nexus_Text_SandyShocks_Boss:
	.string "The dunes pulled together into a\n"
	.string "shaggy mane of sand.\p"
	.string "Underneath it, something old and\n"
	.string "magnetic lifted its head, and your Poké\l"
	.string "Balls tugged at your belt.$"

Nexus_Text_SandyShocks_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-989. Paradox.\p"
	.string "Something ancient buried under sand\n"
	.string "and still live, and a soldier who knows\l"
	.string "exactly what that means.\p"
	.string "What came back with you is small and\n"
	.string "has almost no mane yet. My paper clips\l"
	.string "follow it around the room.\p"
	.string "He walked the desert in straight lines\n"
	.string "before he would let you cross it. Old\l"
	.string "habit, he said.$"
```

</details>

### Diálogo genérico

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_LtSurge_Fight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Lt. Surge cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala de si, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

**Antes da luta**

> Hey, kid! You picked a strange place for a picnic!
>
> Electric Pokémon saved my life in the war, baby. I haven't gone anywhere without 'em since.
>
> Now, ten-hut! Show me what you got!

**Derrota**

> Whoa! You're the real deal, kid! Dismissed… with honors!

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_LtSurge_Intro:
	.string "Hey, kid! You picked a strange place\n"
	.string "for a picnic!\p"
	.string "Electric Pokémon saved my life in the\n"
	.string "war, baby. I haven't gone anywhere\l"
	.string "without 'em since.\p"
	.string "Now, ten-hut! Show me what you got!$"

Nexus_Text_LtSurge_Defeat:
	.string "Whoa! You're the real deal, kid!\n"
	.string "Dismissed… with honors!$"
```

</details>

### Diálogo associado ao lendário

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Lt. Surge é o **campeão**, a luta logo antes do lendário. A fala é sobre a criatura, sem dizer o nome dela ([R16](../NEXUS_REGRAS.md)).

#### Zapdos

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_LtSurge_Zapdos_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

O Surge fala da criatura como fala de guerra: tempestade era cobertura, barulho e clarão para ninguém ver você chegando. A virada: a ave não se esconde na tempestade, ela é a tempestade, e disso não se toma cobertura. No fim ele liga a criatura à usina fechada perto de casa (a Power Plant de Kanto, que dizem ainda zumbir à noite) e dá um conselho de soldado: nunca enfrentar a tempestade de frente; esperar o clarão, contar, e mexer-se.

**Antes da luta**

> Listen up, kid. In the war, we used thunderstorms for cover. Loud. Blinding. Nobody sees you coming.
>
> That bird up there isn't hiding in the storm, baby. It IS the storm.
>
> You don't take cover from that. …So let's see if you can stand in it!

**Derrota**

> Ha! Struck by lightning and still standing, huh?

**Depois da luta**

> That old plant back home, the one they shut down? Folks say it still hums at night.
>
> I used to think it was the machines. Now I know better.
>
> A soldier's advice: never fight a storm head-on. Wait for the flash, count, then move.
>
> Move out, kid!

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_LtSurge_Zapdos_ChampionIntro:
	.string "Listen up, kid. In the war, we used\n"
	.string "thunderstorms for cover. Loud.\l"
	.string "Blinding. Nobody sees you coming.\p"
	.string "That bird up there isn't hiding in the\n"
	.string "storm, baby. It IS the storm.\p"
	.string "You don't take cover from that. …So\n"
	.string "let's see if you can stand in it!$"

Nexus_Text_LtSurge_Zapdos_ChampionDefeat:
	.string "Ha! Struck by lightning and still\n"
	.string "standing, huh?$"

Nexus_Text_LtSurge_Zapdos_ChampionAfter:
	.string "{SPEAKER NAME_LT_SURGE}That old plant back home, the one they\n"
	.string "shut down? Folks say it still hums at\l"
	.string "night.\p"
	.string "I used to think it was the machines.\n"
	.string "Now I know better.\p"
	.string "A soldier's advice: never fight a storm\n"
	.string "head-on. Wait for the flash, count,\l"
	.string "then move.\p"
	.string "Move out, kid!$"
```

</details>

#### Regieleki

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_LtSurge_Regieleki_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

O Surge vê nos anéis uma gaiola, não uma armadura: alguém construiu aquilo para segurar tanta força. A cada anel que quebra, a criatura fica mais rápida; ele já viu soldados assim, que sem regra não param. A virada é sobre ele mesmo: o barulho do Surge é o anel dele, deixa a carga sair aos poucos para nunca explodir de uma vez. A criatura nunca aprendeu a gritar.

**Antes da luta**

> See those yellow rings, kid? That's not armor. That's a cage. Somebody built it to hold all that power in.
>
> Every ring it breaks, it gets faster. I've seen soldiers like that, baby. Take away the rules and they don't stop.
>
> Discipline is the ring you choose to wear! Let's go!

**Derrota**

> Whoa! That was faster than me!

**Depois da luta**

> Think I'm loud? Loud's my ring, baby. Lets the charge out a little at a time, so it never goes off all at once.
>
> That thing out there never learned to yell. It just runs until the lights go out.
>
> One ring left. Don't let it drop that one near you.
>
> Now move it, soldier!

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_LtSurge_Regieleki_ChampionIntro:
	.string "See those yellow rings, kid? That's not\n"
	.string "armor. That's a cage. Somebody built it\l"
	.string "to hold all that power in.\p"
	.string "Every ring it breaks, it gets faster.\n"
	.string "I've seen soldiers like that, baby.\l"
	.string "Take away the rules and they don't\l"
	.string "stop.\p"
	.string "Discipline is the ring you choose to\n"
	.string "wear! Let's go!$"

Nexus_Text_LtSurge_Regieleki_ChampionDefeat:
	.string "Whoa! That was faster than me!$"

Nexus_Text_LtSurge_Regieleki_ChampionAfter:
	.string "{SPEAKER NAME_LT_SURGE}Think I'm loud? Loud's my ring, baby.\n"
	.string "Lets the charge out a little at a time,\l"
	.string "so it never goes off all at once.\p"
	.string "That thing out there never learned to\n"
	.string "yell. It just runs until the lights go\l"
	.string "out.\p"
	.string "One ring left. Don't let it drop that\n"
	.string "one near you.\p"
	.string "Now move it, soldier!$"
```

</details>

#### Sandy Shocks

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_LtSurge_SandyShocks_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

Deserto é terreno conhecido para o Surge, e deserto esconde coisa. A criatura é munição velha: enterrada há tanto tempo que parece chão, e ainda viva. A virada é a regra de veterano: tudo que fica enterrado tempo bastante começa a parecer o chão, e ela vai puxar as Poké Balls antes de puxar você. "Pise onde eu pisei."

**Antes da luta**

> Sand, kid. I've crossed deserts like this before. Deserts hide things.
>
> Out there, something old is buried under the dunes. Magnetic. Still live, after who knows how long.
>
> Old ordnance never forgets it's a bomb, baby. Watch your step, and fight me first!

**Derrota**

> Hah! You walked right through, kid!

**Depois da luta**

> Rule one in a desert: anything buried long enough starts to look like the ground.
>
> That thing's been waiting under the sand since before anybody drew a map.
>
> It'll pull at your Poké Balls before it pulls at you. Hold 'em tight.
>
> Step where I stepped, and move out!

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_LtSurge_SandyShocks_ChampionIntro:
	.string "Sand, kid. I've crossed deserts like\n"
	.string "this before. Deserts hide things.\p"
	.string "Out there, something old is buried\n"
	.string "under the dunes. Magnetic. Still live,\l"
	.string "after who knows how long.\p"
	.string "Old ordnance never forgets it's a\n"
	.string "bomb, baby. Watch your step, and fight\l"
	.string "me first!$"

Nexus_Text_LtSurge_SandyShocks_ChampionDefeat:
	.string "Hah! You walked right through, kid!$"

Nexus_Text_LtSurge_SandyShocks_ChampionAfter:
	.string "{SPEAKER NAME_LT_SURGE}Rule one in a desert: anything buried\n"
	.string "long enough starts to look like the\l"
	.string "ground.\p"
	.string "That thing's been waiting under the\n"
	.string "sand since before anybody drew a map.\p"
	.string "It'll pull at your Poké Balls before it\n"
	.string "pulls at you. Hold 'em tight.\p"
	.string "Step where I stepped, and move out!$"
```

</details>

Falante novo: `SP_NAME_LT_SURGE` (ainda não existe em `include/constants/speaker_names.h`).
