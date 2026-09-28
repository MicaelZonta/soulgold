# Gladion

**Região da ficha:** Alola

Aparece no checklist como:

- **Gladion** (Alola · Rivais) — rival sério que foge da Aether Foundation com Type: Null.
- **Gladion** (Alola · Team Skull e Aether Foundation) — enforcer temporário do Team Skull que possui Type: Null.

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
| `OBJ_EVENT_GFX_GLADION` | `graphics/object_events/pics/people/special/gladion.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_GLADION` | `graphics/trainers/front_pics/gladion.png` |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

> **Atenção:** Personagem do arco das Rift Missions, com várias batalhas de história. `TRAINER_GLADION_POSTGAME` é o time mais forte já escrito.

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_GLADION` | 967 | 0x8C7 | Grubbin Lv14, Sandile Lv14, Rockruff Lv14, Type: Null Lv15 | `VioletCity_PokemonCenter` |
| `TRAINER_GLADION_CIANWOOD` | 969 | 0x8C9 | Krookodile Lv43, Vikavolt Lv43, Lycanroc Midday Lv44, Type: Null Lv44 | `CianwoodCity` |
| `TRAINER_GLADION_VICTORY_ROAD` | 971 | 0x8CB | Silvally Lv65, Krookodile Lv64, Vikavolt Lv63, Lycanroc Midday Lv63, Zoroark Lv64, Gastrodon West Lv64 | `ReceptionGate` |
| `TRAINER_GLADION_POSTGAME` | 974 | 0x8CE | Lucario Lv78, Crobat Lv78, Weavile Lv79, Zoroark Lv79, Umbreon Lv79, Silvally Lv80 | `CianwoodCity` |

### Time das Rift Missions

✅ **Implementado em 27/09/2026** (a proposta abaixo virou código): `TRAINER_NEXUS_GLADION` = **1037** (flag de batalha `0x90D`, limpa antes e depois de cada luta), bloco em `src/data/trainers.party`, nível pelo R2 (tabela em `src/data/nexus/trainers.h`). Fala genérica `Nexus_EventScript_Gladion_Fight`; campeão: `Nexus_EventScript_Gladion_Silvally_ChampionFight` (para Silvally), `Nexus_EventScript_Gladion_TapuBulu_ChampionFight` (para Tapu Bulu). Tudo em `data/scripts/nexus.inc`, sem blackout, resultado em `VAR_TEMP_3`. Para testar: menu de debug → Rift Missions… → Nexus fights… → Gladion.

📝 **Proposta de 27/09/2026, aguardando o autor.** `TRAINER_NEXUS_GLADION`, campeão de Silvally e Tapu Bulu. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler).

Lendário **Necrozma**: é a criatura que o Gladion persegue desde Alola e que ele **nomeou** na M1; este Gladion foi arrancado de um fragmento em que ele a alcançou antes do jogador (o Nexus traz versões de outro lugar, design §10). Semi-lendário **Silvally**, o parceiro de sempre (presença permanente, design §3), com Life Orb para ficar Normal como no time de pós-game. Mega **Lucario** (Fightite), o Lucario do time dele em USUM e do `TRAINER_GLADION_POSTGAME`. Mais Weavile, Crobat e Zoroark, o resto do núcleo dele em Sun/Moon: Pokémon rápidos e escuros, de quem cresceu sozinho e aprendeu a bater primeiro.

*Plano (Singles):* o Necrozma entra cedo, arma Stealth Rock e usa Knock Off; com Prism Armor e Weakness Policy ele aguenta um golpe forte e vira ameaça de Dragon Dance. Silvally (Parting Shot) e Zoroark (Illusion + U-turn) giram o campo para o Lucario Mega entrar de graça e limpar com Extreme Speed; Weavile quebra Focus Sash com Ice Shard.

*Plano (Doubles):* Fake Out do Weavile e Tailwind do Crobat no primeiro turno; o Necrozma sobe Dragon Dance ou o Lucario usa Swords Dance atrás disso. Illusion confunde o alvo dos golpes de alvo único, e o Parting Shot do Silvally derruba o ataque do adversário mais perigoso. Nada no time acerta o parceiro.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Necrozma | Weakness Policy | Prism Armor | Adamant | Photon Geyser, Knock Off, Dragon Dance, Stealth Rock |
| Silvally | Life Orb | RKS System | Adamant | Multi-Attack, Crunch, Flamethrower, Parting Shot |
| Lucario | Fightite | Justified | Jolly | Close Combat, Meteor Mash, Extreme Speed, Swords Dance |
| Weavile | Focus Sash | Pressure | Jolly | Triple Axel, Knock Off, Ice Shard, Fake Out |
| Crobat | Sitrus Berry | Inner Focus | Jolly | Cross Poison, Brave Bird, U-turn, Tailwind |
| Zoroark | Choice Specs | Illusion | Timid | Dark Pulse, Flamethrower, Focus Blast, U-turn |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>dev_scripts/nexus_validar_time.py</code>)</summary>

```
=== TRAINER_NEXUS_GLADION ===
Name: Gladion
Class: Rival
Pic: Gladion
Gender: Male
Music: Silver
Double Battle: No
AI: Smart Trainer

Necrozma @ Weakness Policy
Adamant Nature
Level: 100
Ability: Prism Armor
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Photon Geyser
- Knock Off
- Dragon Dance
- Stealth Rock

Silvally @ Life Orb
Adamant Nature
Level: 100
Ability: RKS System
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Multi-Attack
- Crunch
- Flamethrower
- Parting Shot

Lucario @ Fightite
Jolly Nature
Level: 100
Ability: Justified
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Close Combat
- Meteor Mash
- Extreme Speed
- Swords Dance

Weavile @ Focus Sash
Jolly Nature
Level: 100
Ability: Pressure
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Triple Axel
- Knock Off
- Ice Shard
- Fake Out

Crobat @ Sitrus Berry
Jolly Nature
Level: 100
Ability: Inner Focus
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Cross Poison
- Brave Bird
- U-turn
- Tailwind

Zoroark @ Choice Specs
Timid Nature
Level: 100
Ability: Illusion
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Dark Pulse
- Flamethrower
- Focus Blast
- U-turn
```

</details>

### Lendário associado

#### Silvally

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_Silvally_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Silvally**. Gladion é o campeão dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Gladion, irmão da Lillie e filho da Lusamine. Fugiu da Aether com o Type: Null, lutou pelo Team Skull, e neste hack deu ao jogador o Mystery Egg em Violet e, na M1, **outro** Type: Null.

**A criatura.** Silvally é o Type: Null que rompeu a máscara de controle (o RKS System) ao confiar no treinador. A Aether o criou como a arma "Beast Killer" contra as Ultra Beasts; com um disco de memória ele muda de tipo.

**O fragmento.** Um laboratório branco, limpo e frio demais. Fileiras de tanques de vidro abertos e vazios, e embaixo de cada um um capacete pesado partido ao meio. Algo com garras anda entre os tanques e não tem nada no rosto.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> White rooms, too clean and too cold. Rows of glass tanks stood open and empty.
>
> On the floor under each one lay a heavy helmet, split down the middle.

**Boss**

> Claws on tile, somewhere behind the tanks.
>
> It stepped into the light with nothing on its face, and its crest changed color twice while it looked at you.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md): o que fica é o fragmento, no nível 1)

> File L-773. Synthetic.
>
> A laboratory that built a weapon, and then a cage for it. The weapon kept neither.
>
> What you carried out was small, and it wore no mask at all. I have written that down twice.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Silvally_Arrival:
	.string "White rooms, too clean and too cold.\n"
	.string "Rows of glass tanks stood open and\l"
	.string "empty.\p"
	.string "On the floor under each one lay a\n"
	.string "heavy helmet, split down the middle.$"

Nexus_Text_Silvally_Boss:
	.string "Claws on tile, somewhere behind the\n"
	.string "tanks.\p"
	.string "It stepped into the light with nothing\n"
	.string "on its face, and its crest changed\l"
	.string "color twice while it looked at you.$"

Nexus_Text_Silvally_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-773. Synthetic.\p"
	.string "A laboratory that built a weapon, and\n"
	.string "then a cage for it. The weapon kept\l"
	.string "neither.\p"
	.string "What you carried out was small, and it\n"
	.string "wore no mask at all. I have written\l"
	.string "that down twice.$"
```

</details>


#### Tapu Bulu

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_TapuBulu_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Tapu Bulu**. Gladion é o campeão dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Gladion, que foi enforcer do Team Skull em Ula'ula antes de voltar para a família; neste hack, o rival de frases curtas que mostra cuidado em ação.

**A criatura.** Tapu Bulu, guardião de Ula'ula. Arranca árvores pela raiz e as gira como clavas; faz a vegetação crescer e tira energia desse crescimento. Chamado de divindade guardiã, vira uma divindade maligna com quem o irrita.

**O fragmento.** Uma cidade murada que a floresta está engolindo. Árvores arrancadas com raiz e tudo atravessam as ruas, e árvores novas furam o calçamento enquanto o jogador olha. Um sino toca uma vez, em algum lugar no verde.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A walled town, and a forest eating it.
>
> Trees lay across the streets, torn out roots and all. New ones pushed up through the pavement as you watched.

**Boss**

> A bell rang once, somewhere in the green.
>
> Something with horns came out of the trees, dragging a whole trunk behind it as if it weighed nothing.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md): o que fica é o fragmento, no nível 1)

> File L-787. Guardian of Ula'ula.
>
> A town that locked its gates, and a guardian that grew a forest over them.
>
> The young man who once stood guard at such gates says it was right to.
>
> What you brought back fits in two hands, and it is already asleep. I find that very reassuring.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_TapuBulu_Arrival:
	.string "A walled town, and a forest eating it.\p"
	.string "Trees lay across the streets, torn out\n"
	.string "roots and all. New ones pushed up\l"
	.string "through the pavement as you watched.$"

Nexus_Text_TapuBulu_Boss:
	.string "A bell rang once, somewhere in the\n"
	.string "green.\p"
	.string "Something with horns came out of the\n"
	.string "trees, dragging a whole trunk behind\l"
	.string "it as if it weighed nothing.$"

Nexus_Text_TapuBulu_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-787. Guardian of Ula'ula.\p"
	.string "A town that locked its gates, and a\n"
	.string "guardian that grew a forest over them.\p"
	.string "The young man who once stood guard at\n"
	.string "such gates says it was right to.\p"
	.string "What you brought back fits in two\n"
	.string "hands, and it is already asleep. I find\l"
	.string "that very reassuring.$"
```

</details>

### Diálogo genérico

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Gladion_Fight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Gladion cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala de si, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

O Gladion fala do que sabe de si: o parceiro dele usou uma máscara de controle e só a quebrou quando confiou nele. A virada é que ele também não aceita máscara nenhuma, nem aqui.

**Antes da luta**

> ...You. Fine.
>
> Somebody put a mask on my partner once, so it would obey. It broke the mask the day it decided to trust me.
>
> Nobody's putting a mask on me here, either. Come on!

**Derrota**

> ...Hmph. You don't hold back. Good.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Gladion_Intro:
	.string "...You. Fine.\p"
	.string "Somebody put a mask on my partner\n"
	.string "once, so it would obey. It broke the\l"
	.string "mask the day it decided to trust me.\p"
	.string "Nobody's putting a mask on me here,\n"
	.string "either. Come on!$"

Nexus_Text_Gladion_Defeat:
	.string "...Hmph. You don't hold back. Good.$"
```

</details>

### Diálogo associado ao lendário

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Gladion é o **campeão**, a luta logo antes do lendário do dia. Uma fala por lendário; o nome da espécie não aparece ([R16](../NEXUS_REGRAS.md)). Rótulos com a espécie porque Gladion é campeão de dois.

#### Silvally

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Gladion_Silvally_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

O Gladion vê lá fora outro Silvally, igual ao dele, com a máscara partida no chão ao lado. A Aether fez esses Pokémon para matar o tipo de criatura que o jogador vem enfrentando, e depois os trancou porque funcionaram. O dele quebrou a máscara por confiar nele; aquele quebrou sozinho, e o Gladion não sabe o que é pior. A virada vem no depois: não tente controlar, foi o que fizeram; e se sobrar alguma coisa dele (o fragmento do R17 é um Type: Null), dê um nome, porque ninguém nunca deu nada a ele. Ecoa o Type: Null que o Gladion deu ao jogador na M1.

**Antes da luta**

> There's another one out there. Same as mine. Broken mask on the ground next to it.
>
> They built them to take down things like what you've been fighting. Then locked them up because they worked.
>
> Mine broke its mask for me. That one broke it alone. I don't know which is worse.
>
> ...Silvally won't stop staring at it. Let's get this over with.

**Derrota**

> ...Fine. You'll do.

**Depois da luta**

> It doesn't need a Memory to fight. It'll turn into whatever hurts you.
>
> Don't try to control it. That's what they did. That's how it ended up here.
>
> If something's left of it after, give it a name. Nobody ever gave that one anything.
>
> Go. Silvally and I will watch the door.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Gladion_Silvally_ChampionIntro:
	.string "There's another one out there. Same\n"
	.string "as mine. Broken mask on the ground\l"
	.string "next to it.\p"
	.string "They built them to take down things\n"
	.string "like what you've been fighting. Then\l"
	.string "locked them up because they worked.\p"
	.string "Mine broke its mask for me. That one\n"
	.string "broke it alone. I don't know which is\l"
	.string "worse.\p"
	.string "...Silvally won't stop staring at it.\n"
	.string "Let's get this over with.$"

Nexus_Text_Gladion_Silvally_ChampionDefeat:
	.string "...Fine. You'll do.$"

Nexus_Text_Gladion_Silvally_ChampionAfter:
	.string "{SPEAKER NAME_GLADION}It doesn't need a Memory to fight.\n"
	.string "It'll turn into whatever hurts you.\p"
	.string "Don't try to control it. That's what\n"
	.string "they did. That's how it ended up here.\p"
	.string "If something's left of it after, give\n"
	.string "it a name. Nobody ever gave that one\l"
	.string "anything.\p"
	.string "Go. Silvally and I will watch the\n"
	.string "door.$"
```

</details>


#### Tapu Bulu

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Gladion_TapuBulu_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

O Gladion reconhece o sino: ouviu em Ula'ula, quando andava com o Team Skull e guardava uma cidade atrás de um muro. O guardião nunca veio salvar aquela cidade; deixou o mato crescer por cima. Todos diziam que era preguiça; ele acha que era espera. A virada, no depois: irritado, o guardião deixa de proteger e vira um muro com chifres. "Eu já estive do lado errado de um muro. Ele fez bem em não me ajudar."

**Antes da luta**

> You hear that bell? I heard it on Ula'ula, back when I ran with Skull.
>
> We kept a town behind a wall. The island's guardian never came to save it. It just let the grass grow over us.
>
> Everyone said it was lazy. It wasn't. It was waiting for us to leave.
>
> ...Enough. Show me what you've got.

**Derrota**

> Hmph. You didn't flinch. Good.

**Depois da luta**

> It rips trees out and grows new ones. Takes its strength from the growing.
>
> Make it angry and it stops being a guardian. It's just a wall with horns.
>
> I was on the wrong side of a wall once. It was right not to help me.
>
> ...Don't make it angry. Or do. Just win.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Gladion_TapuBulu_ChampionIntro:
	.string "You hear that bell? I heard it on\n"
	.string "Ula'ula, back when I ran with Skull.\p"
	.string "We kept a town behind a wall. The\n"
	.string "island's guardian never came to save\l"
	.string "it. It just let the grass grow over us.\p"
	.string "Everyone said it was lazy. It wasn't.\n"
	.string "It was waiting for us to leave.\p"
	.string "...Enough. Show me what you've got.$"

Nexus_Text_Gladion_TapuBulu_ChampionDefeat:
	.string "Hmph. You didn't flinch. Good.$"

Nexus_Text_Gladion_TapuBulu_ChampionAfter:
	.string "{SPEAKER NAME_GLADION}It rips trees out and grows new ones.\n"
	.string "Takes its strength from the growing.\p"
	.string "Make it angry and it stops being a\n"
	.string "guardian. It's just a wall with horns.\p"
	.string "I was on the wrong side of a wall once.\n"
	.string "It was right not to help me.\p"
	.string "...Don't make it angry. Or do. Just\n"
	.string "win.$"
```

</details>


Falante: `SP_NAME_GLADION` já existe em `include/constants/speaker_names.h`.
