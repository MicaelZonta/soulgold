# Brandon

**Região da ficha:** Hoenn

Aparece no checklist como:

- **Brandon — Battle Pyramid** (Hoenn · Battle Frontier — Frontier Brains) — explorador que utiliza os três Regis.

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


### Diálogo associado ao lendário

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Brandon é o campeão, a luta logo antes do lendário do dia. Um registro por lendário; a fala é sobre a criatura, sem dizer o nome dela.

#### Regirock

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


#### Regice

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


#### Registeel

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


Falante novo: `SP_NAME_BRANDON` (não existe em `include/constants/speaker_names.h`).
