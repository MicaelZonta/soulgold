# Bugsy

**Região da ficha:** Johto

Aparece no checklist como:

- **Bugsy — Inseto** (Johto · Líderes de Ginásio) — pesquisador de Pokémon Inseto e Líder de Azalea.

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
| `OBJ_EVENT_GFX_BUGSY` | `graphics/object_events/pics/people/gym_leaders/bugsy.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_LEADER_BUGSY` | `graphics/trainers/front_pics/leader_bugsy.png` |

### Field mugshot

| Constante | Arquivo |
|---|---|
| `MUGSHOT_BUGSY` | `graphics/field_mugshots/bugsy.png` |

Aparece sozinho quando o objeto que fala usa o sprite acima (`GetFieldMugshotIdByObjectGraphicsId`, `src/field_mugshot.c`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_BUGSY_1` | 596 | 0x754 | Scizor Lv20, Beedrill Lv20, Pinsir Lv20, Larvesta Lv20 · *dupla* · VS: Purple | `AzaleaTown_Gym`, `src/data/level_scaling_rules.h` |
| `TRAINER_BUGSY_2` | 697 | 0x7B9 | Kleavor Lv77, Ribombee Lv77, Centiskorch Lv77, Scizor Lv78, Volcarona Lv77, Golisopod Lv77 · *dupla* | `KitakamiRoad_House`, `NationalPark_Normal`, `SaffronCity_FightingDojoVIP`, `src/achievements.c`, `src/battle_dome.c` |
| `TRAINER_TITLE_DEFENSE_BUGSY` | 892 | 0x87C | Kleavor Lv85, Ribombee Lv85, Centiskorch Lv85, Scizor Lv85, Volcarona Lv85, Genesect Lv85 | `src/title_defense.c` |

### Time das Rift Missions

✅ **Implementado em 27/09/2026** (a proposta abaixo virou código): `TRAINER_NEXUS_BUGSY` = **1002** (flag de batalha `0x8EA`, limpa antes e depois de cada luta), bloco em `src/data/trainers.party`, nível pelo R2 (tabela em `src/data/nexus/trainers.h`). Fala genérica `Nexus_EventScript_Bugsy_Fight`; campeão: `Nexus_EventScript_Bugsy_SlitherWing_ChampionFight` (para Slither Wing), `Nexus_EventScript_Bugsy_IronMoth_ChampionFight` (para Iron Moth). Tudo em `data/scripts/nexus.inc`, sem blackout, resultado em `VAR_TEMP_3`. Para testar: menu de debug → Rift Missions… → Nexus fights… → Bugsy.

📝 **Proposta de 27/09/2026, aguardando o autor.** `TRAINER_NEXUS_BUGSY`, campeão da Slither Wing e da Iron Moth. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler).

Lendário **Genesect**, um inseto de 300 milhões de anos revivido e modificado pela Team Plasma: o fóssil que todo pesquisador de Inseto sonha estudar, com um canhão nas costas que nenhum deveria ter posto. Semi-lendário **Slither Wing**, a Volcarona ancestral (ele é campeão dela e da Iron Moth; a Slither Wing entra porque é o passado, e o Bugsy é pesquisador). Mega **Scizor** (Bugtite): a linha do Scyther, ás dele desde Gold/Silver. Mais Volcarona (a espécie das duas Paradoxo, ao lado das duas), Ribombee e Kleavor, dos times de revanche e Title Defense.

*Plano (Singles):* a Ribombee põe Sticky Web e sai de U-turn, o Kleavor arma Stealth Rock com Stone Axe, a Volcarona sobe Quiver Dance, o Genesect de Choice Scarf limpa ou faz pivot, e a Mega Scizor sobe Swords Dance e fecha com Bullet Punch. *Plano (Doubles):* First Impression da Slither Wing no turno 1, Heat Wave da Volcarona nos dois alvos, Pollen Puff da Ribombee cura o parceiro (e bate no Singles), e Bullet Punch acaba com quem sobrou. O risco é Fogo; a Volcarona (Flame Body) segura o lado.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Genesect | Choice Scarf | Download | Hasty | U-turn, Iron Head, Flamethrower, Bug Buzz |
| Slither Wing | Booster Energy | Protosynthesis | Adamant | First Impression, Close Combat, Leech Life, Protect |
| Scizor | Bugtite | Technician | Adamant | Bullet Punch, Bug Bite, Knock Off, Swords Dance |
| Volcarona | Heavy-Duty Boots | Flame Body | Timid | Quiver Dance, Heat Wave, Bug Buzz, Giga Drain |
| Ribombee | Focus Sash | Shield Dust | Timid | Sticky Web, Moonblast, Pollen Puff, U-turn |
| Kleavor | Life Orb | Sharpness | Jolly | Stone Axe, X-Scissor, Close Combat, Protect |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>nexus_validar_time.py</code>: trainerproc, constantes, learnsets e categorias)</summary>

```
=== TRAINER_NEXUS_BUGSY ===
Name: Bugsy
Class: Leader
Pic: Leader Bugsy
Gender: Male
Music: Male
Double Battle: Yes
AI: Smart Trainer

Genesect @ Choice Scarf
Hasty Nature
Level: 100
Ability: Download
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- U-turn
- Iron Head
- Flamethrower
- Bug Buzz

Slither Wing @ Booster Energy
Adamant Nature
Level: 100
Ability: Protosynthesis
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- First Impression
- Close Combat
- Leech Life
- Protect

Scizor @ Bugtite
Adamant Nature
Level: 100
Ability: Technician
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Bullet Punch
- Bug Bite
- Knock Off
- Swords Dance

Volcarona @ Heavy-Duty Boots
Timid Nature
Level: 100
Ability: Flame Body
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Quiver Dance
- Heat Wave
- Bug Buzz
- Giga Drain

Ribombee @ Focus Sash
Timid Nature
Level: 100
Ability: Shield Dust
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Sticky Web
- Moonblast
- Pollen Puff
- U-turn

Kleavor @ Life Orb
Jolly Nature
Level: 100
Ability: Sharpness
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Stone Axe
- X-Scissor
- Close Combat
- Protect
```

</details>

### Lendário associado

#### Slither Wing

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_SlitherWing_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Slither Wing**. Bugsy é o campeão dela: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Bugsy, Líder de Azalea e pesquisador de Pokémon Inseto, a enciclopédia ambulante de Johto.

**A criatura.** Slither Wing é um Paradoxo que lembra uma Volcarona muito antiga, descrita num velho diário de expedição. Inseto/Lutador: tem asas enormes, mas anda sobre as patas, com as asas dobradas como uma capa.

**O fragmento.** Uma floresta de samambaias mais altas que casas, num ar quente e úmido como sopa. O lodo está cheio de pegadas pesadas e, entre elas, o rastro comprido de asas grandes demais para levantar.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> Ferns taller than houses, and air so hot and wet it felt like breathing soup.
>
> The mud was full of tracks. Heavy feet, and between them, the long drag of wings too big to lift.

**Boss**

> The ferns parted.
>
> It walked out on its legs, wings folded like a cloak, and the scales falling off it were on fire.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md))

> File L-988. Grounded Sun.
>
> A forest from before any book, and a boy with a notebook who filled every page of it.
>
> What came back with you is a single warm scale. It has not cooled yet.
>
> He asked me to keep one sketch out of the file. It is of the footprints.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_SlitherWing_Arrival:
	.string "Ferns taller than houses, and air so\n"
	.string "hot and wet it felt like breathing\l"
	.string "soup.\p"
	.string "The mud was full of tracks. Heavy\n"
	.string "feet, and between them, the long drag\l"
	.string "of wings too big to lift.$"

Nexus_Text_SlitherWing_Boss:
	.string "The ferns parted.\p"
	.string "It walked out on its legs, wings\n"
	.string "folded like a cloak, and the scales\l"
	.string "falling off it were on fire.$"

Nexus_Text_SlitherWing_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-988. Grounded Sun.\p"
	.string "A forest from before any book, and a\n"
	.string "boy with a notebook who filled every\l"
	.string "page of it.\p"
	.string "What came back with you is a single\n"
	.string "warm scale. It has not cooled yet.\p"
	.string "He asked me to keep one sketch out of\n"
	.string "the file. It is of the footprints.$"
```

</details>

#### Iron Moth

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_IronMoth_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Iron Moth**. Bugsy é o campeão dela: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Bugsy, o mesmo pesquisador, diante do oposto da Slither Wing: uma Volcarona que parece construída.

**A criatura.** Iron Moth é um Paradoxo que lembra uma Volcarona do futuro, de metal, descrita num velho diário de expedição. Fogo/Venenoso: asas de lâminas brilhantes e um núcleo que arde como um pequeno sol.

**O fragmento.** Uma estufa de vidro e aço iluminada por um sol pendurado no teto por correntes. Todas as plantas são perfeitas, e todas são de plástico; nada zumbe além das lâmpadas.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A greenhouse of glass and steel, lit by a sun hanging from the ceiling on chains.
>
> Every plant was perfect, and every one was plastic. Nothing buzzed but the lights.

**Boss**

> The hanging sun moved.
>
> It unfolded wings of bright metal blades and rose, and the air under it began to taste of poison.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md))

> File L-994. Iron Sun.
>
> A garden with nothing alive in it, and a researcher who kept checking the leaves for eggs.
>
> What you brought out still hums. He listened to it for a long time.
>
> He found no eggs. He says that is the most important thing he has ever written down.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_IronMoth_Arrival:
	.string "A greenhouse of glass and steel, lit\n"
	.string "by a sun hanging from the ceiling on\l"
	.string "chains.\p"
	.string "Every plant was perfect, and every\n"
	.string "one was plastic. Nothing buzzed but\l"
	.string "the lights.$"

Nexus_Text_IronMoth_Boss:
	.string "The hanging sun moved.\p"
	.string "It unfolded wings of bright metal\n"
	.string "blades and rose, and the air under it\l"
	.string "began to taste of poison.$"

Nexus_Text_IronMoth_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-994. Iron Sun.\p"
	.string "A garden with nothing alive in it, and\n"
	.string "a researcher who kept checking the\l"
	.string "leaves for eggs.\p"
	.string "What you brought out still hums. He\n"
	.string "listened to it for a long time.\p"
	.string "He found no eggs. He says that is the\n"
	.string "most important thing he has ever\l"
	.string "written down.$"
```

</details>

### Diálogo genérico

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Bugsy_Fight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Bugsy cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala dele mesmo, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

**Antes da luta**

> People think Bug Pokémon are weak because they're small.
>
> They've survived every age of the world so far. Every single one.
>
> My team is very patient. Let's see how patient you are!

**Derrota**

> Amazing! I have to write this down before I forget how you did it.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Bugsy_Intro:
	.string "People think Bug Pokémon are weak\n"
	.string "because they're small.\p"
	.string "They've survived every age of the\n"
	.string "world so far. Every single one.\p"
	.string "My team is very patient. Let's see how\n"
	.string "patient you are!$"

Nexus_Text_Bugsy_Defeat:
	.string "Amazing! I have to write this down\n"
	.string "before I forget how you did it.$"
```

</details>

### Diálogo associado ao lendário

#### Slither Wing

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Bugsy_SlitherWing_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Bugsy é o **campeão**, a luta logo antes da Slither Wing. A fala é sobre a criatura, sem dizer o nome dela.

O Bugsy passou a vida desenhando insetos e nunca desenhou um que não voasse. Esta criatura tem asas daquele tamanho e anda: ele acha que é o que um inseto muito antigo era antes de o céu valer o esforço. A virada vem pelo Scizor dele, que também tem asas e não voa com elas (usa para regular a temperatura do corpo). Ele sempre sentiu pena, como se algo tivesse sido tirado. Aqui entende que nada foi tirado: é paciência.

**Antes da luta**

> Did you see its tracks? Wings that size, and it walks. It walks!
>
> I think it's what a very old bug looked like, before the sky was worth the trouble.
>
> I have to see what it knows. You're in the way, so... let's battle!

**Derrota**

> Noted. Carefully. With a diagram.

**Depois da luta**

> My Scizor has wings too. It can't fly with them. It flaps them to cool down.
>
> I used to feel sorry for it. Like something had been taken away.
>
> But that creature walked through a whole age of the world with its wings folded. Nothing was taken. It's just patient.
>
> Go on. I'll be here, sketching the footprints.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Bugsy_SlitherWing_ChampionIntro:
	.string "Did you see its tracks? Wings that\n"
	.string "size, and it walks. It walks!\p"
	.string "I think it's what a very old bug looked\n"
	.string "like, before the sky was worth the\l"
	.string "trouble.\p"
	.string "I have to see what it knows. You're in\n"
	.string "the way, so... let's battle!$"

Nexus_Text_Bugsy_SlitherWing_ChampionDefeat:
	.string "Noted. Carefully. With a diagram.$"

Nexus_Text_Bugsy_SlitherWing_ChampionAfter:
	.string "{SPEAKER NAME_BUGSY}My Scizor has wings too. It can't fly\n"
	.string "with them. It flaps them to cool down.\p"
	.string "I used to feel sorry for it. Like\n"
	.string "something had been taken away.\p"
	.string "But that creature walked through a\n"
	.string "whole age of the world with its wings\l"
	.string "folded. Nothing was taken. It's just\l"
	.string "patient.\p"
	.string "Go on. I'll be here, sketching the\n"
	.string "footprints.$"
```

</details>

#### Iron Moth

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Bugsy_IronMoth_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Bugsy é o **campeão**, a luta logo antes da Iron Moth. A fala é sobre a criatura, sem dizer o nome dela.

Uma mariposa de metal: alguém a projetou, então ninguém nunca vai precisar estudá-la, porque alguém já escreveu o manual. Para um pesquisador é a coisa mais triste que se pode ver num jardim. A virada: ele a observou por uma hora e ela ficou circulando o sol pendurado, cada vez mais perto. Ninguém programaria isso numa máquina; é inútil, é coisa de mariposa. Alguém esqueceu de escrever essa parte do manual.

**Antes da luta**

> That moth up there is made of metal. Wings, legs, all of it.
>
> Someone designed it. Nobody will ever need to study it, because somebody already wrote the manual.
>
> ...That's the saddest thing I've ever seen in a garden. Battle me, please. I need to think.

**Derrota**

> You beat me. I'm still thinking.

**Depois da luta**

> I watched it for an hour before you came. It kept circling the hanging sun.
>
> Round and round. Closer every time.
>
> Nobody would ever build that into a machine. It's useless. It's a moth thing.
>
> So somebody forgot to write that part of the manual. Go and read the rest of it for me.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Bugsy_IronMoth_ChampionIntro:
	.string "That moth up there is made of metal.\n"
	.string "Wings, legs, all of it.\p"
	.string "Someone designed it. Nobody will ever\n"
	.string "need to study it, because somebody\l"
	.string "already wrote the manual.\p"
	.string "...That's the saddest thing I've ever\n"
	.string "seen in a garden. Battle me, please.\l"
	.string "I need to think.$"

Nexus_Text_Bugsy_IronMoth_ChampionDefeat:
	.string "You beat me. I'm still thinking.$"

Nexus_Text_Bugsy_IronMoth_ChampionAfter:
	.string "{SPEAKER NAME_BUGSY}I watched it for an hour before you\n"
	.string "came. It kept circling the hanging sun.\p"
	.string "Round and round. Closer every time.\p"
	.string "Nobody would ever build that into a\n"
	.string "machine. It's useless. It's a moth\l"
	.string "thing.\p"
	.string "So somebody forgot to write that part\n"
	.string "of the manual. Go and read the rest\l"
	.string "of it for me.$"
```

</details>

Falante novo: `SP_NAME_BUGSY` (ainda não existe em `include/constants/speaker_names.h`; skill `nomear-falante`).
