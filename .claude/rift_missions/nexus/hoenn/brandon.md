# Brandon

**Região da ficha:** Hoenn

Aparece no checklist como:

- **Brandon — Battle Pyramid** (Hoenn · Battle Frontier — Frontier Brains) — explorador que utiliza os três Regis.

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
| `OBJ_EVENT_GFX_BRANDON` | `graphics/object_events/pics/people/frontier_brains/brandon.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_PYRAMID_KING_BRANDON` | `graphics/trainers/front_pics/pyramid_king_brandon.png` |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

Nenhuma. Ao criar, seguir a skill `adicionar-batalha-npc` (e `alocar-flag` se precisar de flag nova).

Homônimos genéricos, **não** são este personagem: `TRAINER_BRANDON` ("Brandon", pic Pokefan M).

### Time das Rift Missions

✅ **Implementado em 27/09/2026** (a proposta abaixo virou código): `TRAINER_NEXUS_BRANDON` = **1033** (flag de batalha `0x909`, limpa antes e depois de cada luta), bloco em `src/data/trainers.party`, nível pelo R2 (tabela em `src/data/nexus/trainers.h`). Fala genérica `Nexus_EventScript_Brandon_Fight`; campeão: `Nexus_EventScript_Brandon_Regirock_ChampionFight` (para Regirock), `Nexus_EventScript_Brandon_Regice_ChampionFight` (para Regice), `Nexus_EventScript_Brandon_Registeel_ChampionFight` (para Registeel). Tudo em `data/scripts/nexus.inc`, sem blackout, resultado em `VAR_TEMP_3`. Para testar: menu de debug → Rift Missions… → Nexus fights… → Brandon.

📝 **Proposta de 27/09/2026, aguardando o autor.** `TRAINER_NEXUS_BRANDON`, campeão de Regirock, Regice e Registeel. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler).

Lendário **Arceus** (Earth Plate: Arceus-Ground), semi-lendário **Regirock**, Mega **Tyranitar** (Rocktite). O Brandon é campeão dos três Regis, mas o R10 só deixa **um** semi-lendário: fica o **Regirock**, o da pedra e do deserto, que é a cara da Battle Pyramid; o Regice e o Registeel ficam só como lendários do dia. O Arceus é a descoberta que todo explorador sonha (o que moldou o mundo antes de haver ruína para explorar); com ele vêm Excadrill (escava), Cofagrigus (o sarcófago da pirâmide) e Aerodactyl (o fóssil vivo). *Plano:* **tempestade de areia.** A Mega Tyranitar liga Sand Stream, que dá +50% de SpD ao Regirock e à Tyranitar e dobra a velocidade do Excadrill (Sand Rush); o Arceus-Ground, o Excadrill e o Regirock não sofrem com a areia.

*Plano (Singles):* Regirock arma Stealth Rock e segura com Iron Defense e Body Press; o Excadrill limpa hazards com Rapid Spin; o Arceus sobe com Calm Mind e Recover; a Tyranitar sobe com Dragon Dance e cobre Ground e Flying com Ice Punch. Cofagrigus (Mummy) queima físicos com Will-O-Wisp. *Plano (Doubles):* Rock Slide da Tyranitar, do Excadrill e do Aerodactyl (spread) com Tailwind ou Trick Room, conforme o adversário; Taunt do Aerodactyl contra suporte. Ninguém tem Earthquake: o Ground do time vem do Judgment do Arceus e do High Horsepower do Excadrill, de alvo único.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Arceus-Ground | Earth Plate | Multitype | Timid | Judgment, Ice Beam, Calm Mind, Recover |
| Regirock | Leftovers | Clear Body | Careful | Stone Edge, Body Press, Stealth Rock, Iron Defense |
| Tyranitar | Rocktite | Sand Stream | Adamant | Rock Slide, Crunch, Ice Punch, Dragon Dance |
| Excadrill | Life Orb | Sand Rush | Jolly | High Horsepower, Iron Head, Rock Slide, Rapid Spin |
| Cofagrigus | Leftovers | Mummy | Relaxed | Shadow Ball, Will-O-Wisp, Trick Room, Protect |
| Aerodactyl | Focus Sash | Unnerve | Jolly | Rock Slide, Tailwind, Taunt, Dual Wingbeat |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>dev_scripts/nexus_validar_time.py</code>: espécie, item, habilidade, learnsets e vagas)</summary>

```
=== TRAINER_NEXUS_BRANDON ===
Name: Brandon
Class: Pyramid King
Pic: Pyramid King Brandon
Gender: Male
Music: Male
Double Battle: No
AI: Smart Trainer

Arceus-Ground @ Earth Plate
Timid Nature
Level: 100
Ability: Multitype
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Judgment
- Ice Beam
- Calm Mind
- Recover

Regirock @ Leftovers
Careful Nature
Level: 100
Ability: Clear Body
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Stone Edge
- Body Press
- Stealth Rock
- Iron Defense

Tyranitar @ Rocktite
Adamant Nature
Level: 100
Ability: Sand Stream
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Rock Slide
- Crunch
- Ice Punch
- Dragon Dance

Excadrill @ Life Orb
Jolly Nature
Level: 100
Ability: Sand Rush
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- High Horsepower
- Iron Head
- Rock Slide
- Rapid Spin

Cofagrigus @ Leftovers
Relaxed Nature
Level: 100
Ability: Mummy
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Shadow Ball
- Will-O-Wisp
- Trick Room
- Protect

Aerodactyl @ Focus Sash
Jolly Nature
Level: 100
Ability: Unnerve
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Rock Slide
- Tailwind
- Taunt
- Dual Wingbeat
```

</details>


### Lendário associado

#### Regirock

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_Regirock_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Regirock**. Brandon é o campeão dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Brandon, Pyramid King da Battle Frontier de Hoenn, explorador barulhento e corajoso que usa os três Regis.

**A criatura.** Um dos três golems selados por gente antiga em câmaras marcadas em Braille. O corpo é todo de pedra; dizem que, quando se danifica, procura sozinho pedras novas para se consertar.

**O fragmento.** Uma câmara de pedra sem teto, sob um céu de areia. Nas paredes, pontos em relevo, fileira após fileira, alguns gastos por mãos. No chão, pedras de lugares diferentes, nenhuma igual à outra.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A stone chamber with no roof, under a sky full of blowing sand.
>
> The walls were covered in raised dots, row after row. Some rows had been worn smooth by hands.
>
> On the floor lay stones from a hundred different places.

**Boss**

> The stones on the floor rolled toward the far wall, one by one.
>
> They climbed onto something that was standing there, and it turned. Seven dots on its face lit up.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md))

> File L-377. Mended Stone.
>
> A chamber of messages, and a king of pyramids who got lost in it on purpose.
>
> What came back with you is a small, rough stone with dots on it. It picks up pebbles from my floor and tries them on. I have stopped sweeping.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Regirock_Arrival:
	.string "A stone chamber with no roof, under a\n"
	.string "sky full of blowing sand.\p"
	.string "The walls were covered in raised dots,\n"
	.string "row after row. Some rows had been worn\l"
	.string "smooth by hands.\p"
	.string "On the floor lay stones from a hundred\n"
	.string "different places.$"

Nexus_Text_Regirock_Boss:
	.string "The stones on the floor rolled toward\n"
	.string "the far wall, one by one.\p"
	.string "They climbed onto something that was\n"
	.string "standing there, and it turned. Seven\l"
	.string "dots on its face lit up.$"

Nexus_Text_Regirock_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-377. Mended Stone.\p"
	.string "A chamber of messages, and a king of\n"
	.string "pyramids who got lost in it on purpose.\p"
	.string "What came back with you is a small,\n"
	.string "rough stone with dots on it. It picks\l"
	.string "up pebbles from my floor and tries them\l"
	.string "on. I have stopped sweeping.$"
```

</details>


#### Regice

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_Regice_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Regice**. Brandon é o campeão dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Brandon, o explorador que entra em qualquer ruína, incluindo as geladas.

**A criatura.** Golem do trio selado; o corpo foi feito numa era do gelo e não derrete nem com magma. Controla um ar gelado de cerca de duzentos graus negativos.

**O fragmento.** Uma caverna de gelo onde nada derrete: nem o gelo das paredes, nem a lava congelada que escorre de uma rachadura e parou no meio do caminho. Dentro do gelo, pegadas de alguém que tentou sair.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A cave of ice where nothing melted.
>
> Lava had poured through a crack in the wall long ago, and had frozen halfway down.
>
> Inside the ice, you could see footprints. Someone had tried to leave.

**Boss**

> The air got so cold that it rang.
>
> Something stood up out of the ice floor, as clear as glass, with seven dots across its face.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md))

> File L-378. Unmelting.
>
> A cave where even fire froze, and a loud man who stood in it until he got quiet.
>
> What came back with you is a small, clear chip of ice. It sits beside my coffee, and my coffee is always cold now. That is fair.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Regice_Arrival:
	.string "A cave of ice where nothing melted.\p"
	.string "Lava had poured through a crack in the\n"
	.string "wall long ago, and had frozen halfway\l"
	.string "down.\p"
	.string "Inside the ice, you could see\n"
	.string "footprints. Someone had tried to\l"
	.string "leave.$"

Nexus_Text_Regice_Boss:
	.string "The air got so cold that it rang.\p"
	.string "Something stood up out of the ice\n"
	.string "floor, as clear as glass, with seven\l"
	.string "dots across its face.$"

Nexus_Text_Regice_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-378. Unmelting.\p"
	.string "A cave where even fire froze, and a\n"
	.string "loud man who stood in it until he got\l"
	.string "quiet.\p"
	.string "What came back with you is a small,\n"
	.string "clear chip of ice. It sits beside my\l"
	.string "coffee, and my coffee is always cold\l"
	.string "now. That is fair.$"
```

</details>


#### Registeel

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_Registeel_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Registeel**. Brandon é o campeão dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Brandon, que já escavou de tudo, e ainda se espanta com o que é oco por dentro.

**A criatura.** Golem do trio selado; o corpo é mais duro que qualquer metal conhecido, e dizem que é oco por dentro. Ninguém sabe dizer do que é feito.

**O fragmento.** Uma tumba de metal escuro, sem porta e sem ferrugem. Cada batida no chão ecoa por muito tempo, como se lá dentro não houvesse nada para segurar o som.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A tomb of dark metal, with no door and not a speck of rust.
>
> Every footstep echoed for a long time, as if there was nothing inside to stop the sound.

**Boss**

> The echo came back wrong. It came back as a hum.
>
> A shape of dark steel stepped out of the wall, and the seven dots on its face lit one at a time.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md))

> File L-379. Hollow Steel.
>
> A tomb that rings, and an explorer who listened to the echo instead of digging.
>
> What came back with you is a small steel piece that hums when it is tapped. It is hollow. I tapped it more than I should have.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Registeel_Arrival:
	.string "A tomb of dark metal, with no door and\n"
	.string "not a speck of rust.\p"
	.string "Every footstep echoed for a long time,\n"
	.string "as if there was nothing inside to stop\l"
	.string "the sound.$"

Nexus_Text_Registeel_Boss:
	.string "The echo came back wrong. It came back\n"
	.string "as a hum.\p"
	.string "A shape of dark steel stepped out of\n"
	.string "the wall, and the seven dots on its\l"
	.string "face lit one at a time.$"

Nexus_Text_Registeel_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-379. Hollow Steel.\p"
	.string "A tomb that rings, and an explorer who\n"
	.string "listened to the echo instead of\l"
	.string "digging.\p"
	.string "What came back with you is a small\n"
	.string "steel piece that hums when it is\l"
	.string "tapped. It is hollow. I tapped it more\l"
	.string "than I should have.$"
```

</details>


### Diálogo genérico

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Brandon_Fight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Brandon cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala dele mesmo, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

**Antes da luta**

> Hahahah! Brandon, Pyramid King! I got lost in a pyramid once, you know. Three whole days!
>
> Best three days of my life. When you're lost, every corner is a discovery.
>
> And this place? I've never been this lost. Hahahah! Show me some courage!

**Derrota**

> Hahahah! Wonderful! I got beaten AND discovered something!

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Brandon_Intro:
	.string "Hahahah! Brandon, Pyramid King! I got\n"
	.string "lost in a pyramid once, you know. Three\l"
	.string "whole days!\p"
	.string "Best three days of my life. When you're\n"
	.string "lost, every corner is a discovery.\p"
	.string "And this place? I've never been this\n"
	.string "lost. Hahahah! Show me some courage!$"

Nexus_Text_Brandon_Defeat:
	.string "Hahahah! Wonderful! I got beaten AND\n"
	.string "discovered something!$"
```

</details>

#### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mais duas falas genéricas ([R16](../NEXUS_REGRAS.md)), além da que já está no jogo (variação 1). O sorteio de qual variação toca ainda não existe no código.

**Variação 2** — provocação alegre: ele nunca leva mapa, e por isso se perdeu três dias.

**Antes da luta**

> Hahahah! Want to know my secret? I never carry a map!
>
> A map tells you where things are. I want to find out for myself!
>
> Of course, that's how I got lost for three days. Totally worth it!
>
> Now! Where's your courage? Show me!

**Derrota**

> Hahahah! You found the exit! Where was it? No, don't tell me!

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Brandon_Intro2:
	.string "Hahahah! Want to know my secret? I\n"
	.string "never carry a map!\p"
	.string "A map tells you where things are. I want\n"
	.string "to find out for myself!\p"
	.string "Of course, that's how I got lost for\n"
	.string "three days. Totally worth it!\p"
	.string "Now! Where's your courage? Show me!$"

Nexus_Text_Brandon_Defeat2:
	.string "Hahahah! You found the exit! Where was\n"
	.string "it? No, don't tell me!$"
```

</details>

**Variação 3** — R21 e dúvida: no fragmento dele é sempre o terceiro dia; ele ri, mas percebeu.

**Antes da luta**

> Hahahah! Quick question, friend. What day is it? I make it day three.
>
> I've made it day three for a good while now. Funny thing, that.
>
> Doesn't matter! An explorer who counts the days isn't looking at the walls!
>
> Come on! Courage!

**Derrota**

> Hahahah! Still day three, and I still learned something!

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Brandon_Intro3:
	.string "Hahahah! Quick question, friend. What\n"
	.string "day is it? I make it day three.\p"
	.string "I've made it day three for a good while\n"
	.string "now. Funny thing, that.\p"
	.string "Doesn't matter! An explorer who counts\n"
	.string "the days isn't looking at the walls!\p"
	.string "Come on! Courage!$"

Nexus_Text_Brandon_Defeat3:
	.string "Hahahah! Still day three, and I still\n"
	.string "learned something!$"
```

</details>


### Diálogo associado ao lendário

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Brandon é o campeão, a luta logo antes do lendário do dia. Um registro por lendário; a fala é sobre a criatura, sem dizer o nome dela.

#### Regirock

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Brandon_Regirock_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

O Brandon é o homem que já passou três dias perdido numa pirâmide e chamou isso de férias. Na câmara ele lê o que os antigos escreveram nas paredes e vê a criatura se consertar com pedras de todo lugar. A virada: aquele corpo é o mapa de tudo o que ela atravessou. O Brandon, que só fala de coragem, admite que o que ele admira não é a força: é continuar inteiro juntando pedaços de onde passou. E ele diz que é o que ele faz também.

**Antes da luta**

> Hahahah! Did you see it? It walks around picking up stones and sticking them on itself!
>
> Every rock on that body comes from somewhere different. It fixes itself with whatever it finds on the road.
>
> It's a map! A map of everywhere it's ever been!
>
> I want to read it all. Come on, courage! Let's go!

**Derrota**

> Hahahah! You found a way through! Just like a good explorer!

**Depois da luta**

> You know, I've been lost in ruins more times than I can count. Every time I came out a bit different.
>
> A scrape here, a story there. You pick up pieces wherever you go.
>
> That old golem does the same. It's not strong because it never breaks. It's strong because it keeps mending.
>
> Go on! Show it a new stone!

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Brandon_Regirock_ChampionIntro:
	.string "Hahahah! Did you see it? It walks\n"
	.string "around picking up stones and sticking\l"
	.string "them on itself!\p"
	.string "Every rock on that body comes from\n"
	.string "somewhere different. It fixes itself\l"
	.string "with whatever it finds on the road.\p"
	.string "It's a map! A map of everywhere it's\n"
	.string "ever been!\p"
	.string "I want to read it all. Come on, courage!\n"
	.string "Let's go!$"

Nexus_Text_Brandon_Regirock_ChampionDefeat:
	.string "Hahahah! You found a way through!\n"
	.string "Just like a good explorer!$"

Nexus_Text_Brandon_Regirock_ChampionAfter:
	.string "{SPEAKER NAME_BRANDON}You know, I've been lost in ruins more\n"
	.string "times than I can count. Every time I\l"
	.string "came out a bit different.\p"
	.string "A scrape here, a story there. You pick\n"
	.string "up pieces wherever you go.\p"
	.string "That old golem does the same. It's not\n"
	.string "strong because it never breaks. It's\l"
	.string "strong because it keeps mending.\p"
	.string "Go on! Show it a new stone!$"
```

</details>

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mais duas falas de campeão para este lendário, além da variação 1 que já está no jogo. Sem o nome da espécie ([R16](../NEXUS_REGRAS.md)).

**Variação 2** — orgulho de explorador: ele deu uma pedrinha da Pirâmide, e ela virou parte do corpo da criatura; as paredes dizem “We wait”.

**Antes da luta**

> Hahahah! I tossed that golem a pebble from my pocket. From the Pyramid! It stuck it right on its shoulder!
>
> A piece of my Pyramid is walking around on it now. Best thing you ever heard?
>
> Every explorer wants to leave a mark. I left a pebble!
>
> Come on! Let's see if it remembers me! Courage!

**Derrota**

> Hahahah! Crumbled! Somebody pass me a stone!

**Depois da luta**

> The walls in there are covered in dots. Old writing, for fingers instead of eyes.
>
> I ran my hand along one row for hours. All it said was, “We wait.”
>
> That golem has been mending itself for ages, waiting for whoever wrote that.
>
> Go on! If you meet them first, say hello from me!

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Brandon_Regirock_ChampionIntro2:
	.string "Hahahah! I tossed that golem a pebble\n"
	.string "from my pocket. From the Pyramid! It\l"
	.string "stuck it right on its shoulder!\p"
	.string "A piece of my Pyramid is walking around\n"
	.string "on it now. Best thing you ever heard?\p"
	.string "Every explorer wants to leave a mark. I\n"
	.string "left a pebble!\p"
	.string "Come on! Let's see if it remembers me!\n"
	.string "Courage!$"

Nexus_Text_Brandon_Regirock_ChampionDefeat2:
	.string "Hahahah! Crumbled! Somebody pass me a\n"
	.string "stone!$"

Nexus_Text_Brandon_Regirock_ChampionAfter2:
	.string "{SPEAKER NAME_BRANDON}The walls in there are covered in dots.\n"
	.string "Old writing, for fingers instead of\l"
	.string "eyes.\p"
	.string "I ran my hand along one row for hours.\n"
	.string "All it said was, “We wait.”\p"
	.string "That golem has been mending itself for\n"
	.string "ages, waiting for whoever wrote that.\p"
	.string "Go on! If you meet them first, say hello\n"
	.string "from me!$"
```

</details>

**Variação 3** — humor e tentação: a criatura confundiu o Brandon com uma pedra e quis grudá-lo no braço.

**Antes da luta**

> Hahahah! Funny story. I sat down in there to rest. Very still, for a long while.
>
> Next thing I know, that golem is trying to pick me up and stick me on its arm!
>
> I must've looked like a good sturdy rock. Best compliment I ever got!
>
> Let's go! Solid as a rock, you and me!

**Derrota**

> Hahahah! Rolled right over! Good one!

**Depois da luta**

> You know, part of me wanted to let it. Just ride on that arm forever.
>
> See every road it ever walked. Every desert, every cave.
>
> But a stone on a golem doesn't choose where it goes. An explorer does.
>
> Go on! Choose your road!

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Brandon_Regirock_ChampionIntro3:
	.string "Hahahah! Funny story. I sat down in\n"
	.string "there to rest. Very still, for a long\l"
	.string "while.\p"
	.string "Next thing I know, that golem is trying\n"
	.string "to pick me up and stick me on its arm!\p"
	.string "I must've looked like a good sturdy\n"
	.string "rock. Best compliment I ever got!\p"
	.string "Let's go! Solid as a rock, you and me!$"

Nexus_Text_Brandon_Regirock_ChampionDefeat3:
	.string "Hahahah! Rolled right over! Good one!$"

Nexus_Text_Brandon_Regirock_ChampionAfter3:
	.string "{SPEAKER NAME_BRANDON}You know, part of me wanted to let it.\n"
	.string "Just ride on that arm forever.\p"
	.string "See every road it ever walked. Every\n"
	.string "desert, every cave.\p"
	.string "But a stone on a golem doesn't choose\n"
	.string "where it goes. An explorer does.\p"
	.string "Go on! Choose your road!$"
```

</details>


#### Regice

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Brandon_Regice_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

O Brandon, que sempre acha que coragem resolve, chega à caverna e vê as pegadas presas no gelo: alguém entrou antes e não saiu. A criatura foi feita numa era do gelo e nem magma a derrete. A virada: o Brandon admite que coragem não derrete tudo; às vezes coragem é saber a hora de voltar. E diz isso rindo, porque aprendeu na própria pirâmide.

**Antes da luta**

> Brr! Hahahah! Even the lava froze in there! Did you see it? Stopped halfway down the wall!
>
> That golem was made in the ice age. Fire won't melt it. Nothing will.
>
> And there are footprints in the ice. Somebody went in before us… and didn't come out.
>
> Well! Courage means going in. Let's go!

**Derrota**

> Hahahah! You're warmer than that cave, I'll give you that!

**Depois da luta**

> Here's a thing I don't say often. Courage isn't just going in.
>
> The footprints in that ice? That fellow had courage. He didn't have a way back.
>
> In the Pyramid, I always tell challengers: know your way out before you go in.
>
> Go on. And come back!

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Brandon_Regice_ChampionIntro:
	.string "Brr! Hahahah! Even the lava froze in\n"
	.string "there! Did you see it? Stopped halfway\l"
	.string "down the wall!\p"
	.string "That golem was made in the ice age. Fire\n"
	.string "won't melt it. Nothing will.\p"
	.string "And there are footprints in the ice.\n"
	.string "Somebody went in before us… and\l"
	.string "didn't come out.\p"
	.string "Well! Courage means going in. Let's go!$"

Nexus_Text_Brandon_Regice_ChampionDefeat:
	.string "Hahahah! You're warmer than that\n"
	.string "cave, I'll give you that!$"

Nexus_Text_Brandon_Regice_ChampionAfter:
	.string "{SPEAKER NAME_BRANDON}Here's a thing I don't say often.\n"
	.string "Courage isn't just going in.\p"
	.string "The footprints in that ice? That\n"
	.string "fellow had courage. He didn't have a\l"
	.string "way back.\p"
	.string "In the Pyramid, I always tell\n"
	.string "challengers: know your way out before\l"
	.string "you go in.\p"
	.string "Go on. And come back!$"
```

</details>

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mais duas falas de campeão para este lendário, além da variação 1 que já está no jogo. Sem o nome da espécie ([R16](../NEXUS_REGRAS.md)).

**Variação 2** — o que ele perdeu: o frio calou o Brandon; a confissão de que ele é barulhento porque o silêncio dá medo.

**Antes da luta**

> …Hahah. Sorry. Hard to laugh in there. The cold gets into your voice.
>
> Two hundred below, they say. Your breath freezes before it leaves your mouth.
>
> I stood in that cave until I went quiet. First time in my life I heard my own heartbeat.
>
> …Right! That's enough quiet! Let's go!

**Derrota**

> Hahahah! There! Warmed right up!

**Depois da luta**

> People think I'm loud because I'm brave. Truth is, I'm loud because silence scares me.
>
> That golem lives in perfect silence. Nothing melts. Nothing moves. Nothing talks.
>
> In there, I found out I could be quiet too. And nothing bad happened.
>
> Go on. Listen to the ice a bit before you fight it.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Brandon_Regice_ChampionIntro2:
	.string "…Hahah. Sorry. Hard to laugh in there.\n"
	.string "The cold gets into your voice.\p"
	.string "Two hundred below, they say. Your\n"
	.string "breath freezes before it leaves your\l"
	.string "mouth.\p"
	.string "I stood in that cave until I went quiet.\n"
	.string "First time in my life I heard my own\l"
	.string "heartbeat.\p"
	.string "…Right! That's enough quiet! Let's go!$"

Nexus_Text_Brandon_Regice_ChampionDefeat2:
	.string "Hahahah! There! Warmed right up!$"

Nexus_Text_Brandon_Regice_ChampionAfter2:
	.string "{SPEAKER NAME_BRANDON}People think I'm loud because I'm\n"
	.string "brave. Truth is, I'm loud because\l"
	.string "silence scares me.\p"
	.string "That golem lives in perfect silence.\n"
	.string "Nothing melts. Nothing moves. Nothing\l"
	.string "talks.\p"
	.string "In there, I found out I could be quiet\n"
	.string "too. And nothing bad happened.\p"
	.string "Go on. Listen to the ice a bit before\n"
	.string "you fight it.$"
```

</details>

**Variação 3** — lore: a lava congelada, um empate eterno, e quem fez o golem, que arrastou continentes com cordas.

**Antes da luta**

> Hahahah! Did you touch the lava in there? Frozen solid! You can knock on it like a door!
>
> Fire and ice, stuck in the same wall. Neither one winning.
>
> First time I ever saw a fight end in a draw that lasts forever!
>
> We won't draw, though! Courage!

**Derrota**

> Hahahah! No draw! Clean win! For you!

**Depois da luta**

> Somebody made that golem in an ice age. Somebody older than any ruin I've found.
>
> The walls say its maker towed the land around with ropes. Whole continents!
>
> Imagine that fellow. And imagine what he'd think of us, stomping around his cellar.
>
> Go on! And tread lightly. It's his cellar.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Brandon_Regice_ChampionIntro3:
	.string "Hahahah! Did you touch the lava in\n"
	.string "there? Frozen solid! You can knock on\l"
	.string "it like a door!\p"
	.string "Fire and ice, stuck in the same wall.\n"
	.string "Neither one winning.\p"
	.string "First time I ever saw a fight end in a\n"
	.string "draw that lasts forever!\p"
	.string "We won't draw, though! Courage!$"

Nexus_Text_Brandon_Regice_ChampionDefeat3:
	.string "Hahahah! No draw! Clean win! For you!$"

Nexus_Text_Brandon_Regice_ChampionAfter3:
	.string "{SPEAKER NAME_BRANDON}Somebody made that golem in an ice age.\n"
	.string "Somebody older than any ruin I've\l"
	.string "found.\p"
	.string "The walls say its maker towed the land\n"
	.string "around with ropes. Whole continents!\p"
	.string "Imagine that fellow. And imagine what\n"
	.string "he'd think of us, stomping around his\l"
	.string "cellar.\p"
	.string "Go on! And tread lightly. It's his\n"
	.string "cellar.$"
```

</details>


#### Registeel

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Brandon_Registeel_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

O Brandon bate na parede da tumba e o eco não acaba: é oco. A criatura mais dura do mundo é vazia por dentro, e ninguém sabe do que é feita. A virada: o explorador que sempre quer abrir tudo descobre que tem coisa que não é para abrir. Ele fica feliz com um mistério que não se resolve, e diz que a melhor ruína é a que ainda guarda um segredo quando você vai embora.

**Antes da luta**

> Hahahah! Knock on that thing and it rings like a bell! It's hollow! The hardest metal there is… and hollow!
>
> Nobody knows what it's made of. Folks have been guessing for ages.
>
> Every explorer wants to crack it open and look inside.
>
> Me? Hahahah! I kind of hope nobody ever does. Let's go!

**Derrota**

> Hahahah! Solid! You're solid all the way through!

**Depois da luta**

> Everyone thinks an explorer wants every answer. Not me.
>
> The best ruins are the ones that keep one secret after you leave.
>
> That steel golem is empty inside, and nobody knows why. That's perfect. That's a treasure.
>
> Go on! Just don't open it!

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Brandon_Registeel_ChampionIntro:
	.string "Hahahah! Knock on that thing and it\n"
	.string "rings like a bell! It's hollow! The\l"
	.string "hardest metal there is… and hollow!\p"
	.string "Nobody knows what it's made of. Folks\n"
	.string "have been guessing for ages.\p"
	.string "Every explorer wants to crack it open\n"
	.string "and look inside.\p"
	.string "Me? Hahahah! I kind of hope nobody\n"
	.string "ever does. Let's go!$"

Nexus_Text_Brandon_Registeel_ChampionDefeat:
	.string "Hahahah! Solid! You're solid all the\n"
	.string "way through!$"

Nexus_Text_Brandon_Registeel_ChampionAfter:
	.string "{SPEAKER NAME_BRANDON}Everyone thinks an explorer wants\n"
	.string "every answer. Not me.\p"
	.string "The best ruins are the ones that keep\n"
	.string "one secret after you leave.\p"
	.string "That steel golem is empty inside, and\n"
	.string "nobody knows why. That's perfect.\l"
	.string "That's a treasure.\p"
	.string "Go on! Just don't open it!$"
```

</details>

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mais duas falas de campeão para este lendário, além da variação 1 que já está no jogo. Sem o nome da espécie ([R16](../NEXUS_REGRAS.md)).

**Variação 2** — humor: ele cantou uma nota na tumba e a criatura respondeu; teoria de que ela é feita dos sons que entraram ali.

**Antes da luta**

> Hahahah! I sang in that tomb! One note! It's still echoing!
>
> And the golem hummed it back. Same note. Perfect pitch!
>
> Something hollow and hard, singing back at a loud man in the dark. Now that's a duet!
>
> Let's make some noise!

**Derrota**

> Hahahah! You hit a higher note than me!

**Depois da luta**

> They say nobody knows what that golem's made of. I have a theory.
>
> I think it's made of every sound that ever went into that tomb and never came out.
>
> Knocks, footsteps, a laugh or two. Mine, now.
>
> Go on! Say something nice when you pass it. It keeps everything.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Brandon_Registeel_ChampionIntro2:
	.string "Hahahah! I sang in that tomb! One note!\n"
	.string "It's still echoing!\p"
	.string "And the golem hummed it back. Same\n"
	.string "note. Perfect pitch!\p"
	.string "Something hollow and hard, singing back\n"
	.string "at a loud man in the dark. Now that's a\l"
	.string "duet!\p"
	.string "Let's make some noise!$"

Nexus_Text_Brandon_Registeel_ChampionDefeat2:
	.string "Hahahah! You hit a higher note than me!$"

Nexus_Text_Brandon_Registeel_ChampionAfter2:
	.string "{SPEAKER NAME_BRANDON}They say nobody knows what that\n"
	.string "golem's made of. I have a theory.\p"
	.string "I think it's made of every sound that\n"
	.string "ever went into that tomb and never\l"
	.string "came out.\p"
	.string "Knocks, footsteps, a laugh or two. Mine,\n"
	.string "now.\p"
	.string "Go on! Say something nice when you pass\n"
	.string "it. It keeps everything.$"
```

</details>

**Variação 3** — R21 e fio do sobretudo: o homem de sobretudo pediu um martelo; o oco foi feito para carregar alguma coisa.

**Antes da luta**

> Hahahah! A man in a long coat was in that tomb before me. Tapping the walls. Listening.
>
> He asked if I had a hammer. I did! I always do!
>
> I didn't give it to him. Some things you don't break open.
>
> Now, no hammers! Just courage!

**Derrota**

> Hahahah! Hard as steel, you are!

**Depois da luta**

> Want to know what I think? Nobody makes something hollow by accident.
>
> It was built to carry something. A message. A spark. Maybe the voice of whoever made it.
>
> Whatever it was, it's still in there. That hum is it, saying so.
>
> Go on! And leave the hammers at home!

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Brandon_Registeel_ChampionIntro3:
	.string "Hahahah! A man in a long coat was in\n"
	.string "that tomb before me. Tapping the walls.\l"
	.string "Listening.\p"
	.string "He asked if I had a hammer. I did! I\n"
	.string "always do!\p"
	.string "I didn't give it to him. Some things you\n"
	.string "don't break open.\p"
	.string "Now, no hammers! Just courage!$"

Nexus_Text_Brandon_Registeel_ChampionDefeat3:
	.string "Hahahah! Hard as steel, you are!$"

Nexus_Text_Brandon_Registeel_ChampionAfter3:
	.string "{SPEAKER NAME_BRANDON}Want to know what I think? Nobody\n"
	.string "makes something hollow by accident.\p"
	.string "It was built to carry something. A\n"
	.string "message. A spark. Maybe the voice of\l"
	.string "whoever made it.\p"
	.string "Whatever it was, it's still in there.\n"
	.string "That hum is it, saying so.\p"
	.string "Go on! And leave the hammers at home!$"
```

</details>


Falante novo: `SP_NAME_BRANDON` (não existe em `include/constants/speaker_names.h`).
