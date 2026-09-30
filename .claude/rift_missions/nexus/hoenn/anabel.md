# Anabel

**Região da ficha:** Hoenn

Aparece no checklist como:

- **Anabel — Battle Tower** (Hoenn · Battle Frontier — Frontier Brains) — jovem prodígio conhecida como Salon Maiden.
- **Anabel** (Alola · Outros notáveis) — antiga Frontier Brain que agora trabalha para a International Police.

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
| `OBJ_EVENT_GFX_ANABEL` | `graphics/object_events/pics/people/frontier_brains/anabel.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_SALON_MAIDEN_ANABEL` | `graphics/trainers/front_pics/salon_maiden_anabel.png` |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

> **Atenção:** Personagem fixa do arco das Rift Missions (Looker e Anabel conduzem as expedições, §10 do design). Como treinadora do pool ela exigiria uma justificativa na história.

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

Nenhuma. Ao criar, seguir a skill `adicionar-batalha-npc` (e `alocar-flag` se precisar de flag nova).

### Time das Rift Missions

✅ **Implementado em 27/09/2026** (a proposta abaixo virou código): `TRAINER_NEXUS_ANABEL` = **1034** (flag de batalha `0x90A`, limpa antes e depois de cada luta), bloco em `src/data/trainers.party`, nível pelo R2 (tabela em `src/data/nexus/trainers.h`). Fala genérica `Nexus_EventScript_Anabel_Fight`; campeão: `Nexus_EventScript_Anabel_Necrozma_ChampionFight` (para Necrozma), `Nexus_EventScript_Anabel_Deoxys_ChampionFight` (para Deoxys). Tudo em `data/scripts/nexus.inc`, sem blackout, resultado em `VAR_TEMP_3`. Para testar: menu de debug → Rift Missions… → Nexus fights… → Anabel.

📝 **Proposta de 27/09/2026, aguardando o autor.** `TRAINER_NEXUS_ANABEL`, campeão de Necrozma e Deoxys. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler).

Lendário **Necrozma** (forma base: sem Solgaleo/Lunala para fundir e a Ultra é só de batalha), semi-lendário e Mega **Latios** (Dragotite: Latios Mega ocupa as duas vagas, R10), do time Gold Symbol da Anabel em Emerald, com Alakazam e Snorlax, também dos times dela em Emerald (e o Snorlax é o que ela solta em New Bark na M4). Metagross e Bronzong completam o "time de investigação": um que calcula, um que protege. A Deoxys, de que ela também é campeã, não entra porque o Deoxys também ocupa a vaga de lendário (R10).

**Quem é esta Anabel.** Aprovado pelo autor em 27/09/2026 (e vira regra, [R21](../NEXUS_REGRAS.md)): a Anabel do altar não sai de lá (ela ajuda quem chega pelas fendas). A Anabel das salas é **outra**, arrancada de um fragmento em que a história terminou diferente: **foi ela quem jogou a Beast Ball** no Necrozma, e ele ficou com ela. Por isso ela tem um Necrozma no time sem contradizer a campanha (o do jogador continua sendo do jogador). Ela sabe que tem lacunas de memória (é Faller) e trata a dúvida como trata tudo: separa o que mediu do que sente.

*Plano:* **ler e proteger.** O Bronzong põe Reflect e Light Screen (Light Clay), o Necrozma (Prism Armor) sobe com Calm Mind atrás das telas, e a Mega Latios e o Alakazam batem especial rápido. *Plano (Singles):* Bronzong arma Stealth Rock e telas; Snorlax com Curse e Rest segura físicos; o Necrozma sobe com Calm Mind (o Weakness Policy pune quem acertar super efetivo) e varre com Photon Geyser. *Plano (Doubles):* telas protegem os dois lados; Heat Wave e Dazzling Gleam (spread) do Necrozma e do Alakazam; Metagross de Assault Vest com Bullet Punch contra Fairy; Levitate do Latios e do Bronzong deixa o High Horsepower do Snorlax livre (alvo único, de qualquer jeito).

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Necrozma | Weakness Policy | Prism Armor | Modest | Photon Geyser, Earth Power, Heat Wave, Calm Mind |
| Latios | Dragotite | Levitate | Timid | Draco Meteor, Psyshock, Aura Sphere, Recover |
| Alakazam | Focus Sash | Magic Guard | Timid | Psychic, Focus Blast, Shadow Ball, Dazzling Gleam |
| Snorlax | Leftovers | Thick Fat | Careful | Body Slam, High Horsepower, Curse, Rest |
| Metagross | Assault Vest | Clear Body | Adamant | Meteor Mash, Zen Headbutt, Bullet Punch, Ice Punch |
| Bronzong | Light Clay | Levitate | Sassy | Reflect, Light Screen, Stealth Rock, Gyro Ball |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>dev_scripts/nexus_validar_time.py</code>: espécie, item, habilidade, learnsets e vagas)</summary>

```
=== TRAINER_NEXUS_ANABEL ===
Name: Anabel
Class: Salon Maiden
Pic: Salon Maiden Anabel
Gender: Female
Music: Female
Double Battle: No
AI: Smart Trainer

Necrozma @ Weakness Policy
Modest Nature
Level: 100
Ability: Prism Armor
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Photon Geyser
- Earth Power
- Heat Wave
- Calm Mind

Latios @ Dragotite
Timid Nature
Level: 100
Ability: Levitate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Draco Meteor
- Psyshock
- Aura Sphere
- Recover

Alakazam @ Focus Sash
Timid Nature
Level: 100
Ability: Magic Guard
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Psychic
- Focus Blast
- Shadow Ball
- Dazzling Gleam

Snorlax @ Leftovers
Careful Nature
Level: 100
Ability: Thick Fat
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Body Slam
- High Horsepower
- Curse
- Rest

Metagross @ Assault Vest
Adamant Nature
Level: 100
Ability: Clear Body
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Meteor Mash
- Zen Headbutt
- Bullet Punch
- Ice Punch

Bronzong @ Light Clay
Sassy Nature
Level: 100
Ability: Levitate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Reflect
- Light Screen
- Stealth Rock
- Gyro Ball
```

</details>


### Lendário associado

#### Necrozma

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_Necrozma_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Necrozma**. Anabel é a campeã dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Anabel, ex-Salon Maiden da Battle Tower, agente da International Police e chefe da investigação das Rift Missions. Faller: veio por uma Ultra Wormhole, lembra pouco de antes e sente uma abertura um instante antes do instrumento.

**A criatura.** Pokémon Prism. Perdeu a própria luz e, em Ultra Megalopolis, vive de roubar luz; funde-se a Solgaleo ou Lunala e, com a luz de volta, vira Ultra Necrozma. Nas Rift Missions foi ele quem arrastou as nove UBs.

**O fragmento.** Uma sala de vidro partido em mil prismas. Cada pedaço devolve um pedaço de luz, e nenhum devolve a imagem inteira de quem olha. No centro, um vazio escuro onde a luz entra e não sai.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A room of broken glass, split into a thousand prisms.
>
> Each piece gave back a sliver of light. None of them gave back your whole reflection.
>
> In the middle, a dark space where light went in and did not come out.

**Boss**

> The prisms turned, all together, toward the dark space.
>
> Something black and jagged unfolded out of it and reached for the light, and every reflection in the room went dim.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md))

> File L-800. Prism.
>
> The creature we chased across Johto, and an Anabel who is not quite ours, standing guard in front of it.
>
> What came back with you is small and gives off an uneven light. It does not steal. It only looks for more. Anabel, ours, sat with it for an hour and did not say why.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Necrozma_Arrival:
	.string "A room of broken glass, split into a\n"
	.string "thousand prisms.\p"
	.string "Each piece gave back a sliver of light.\n"
	.string "None of them gave back your whole\l"
	.string "reflection.\p"
	.string "In the middle, a dark space where light\n"
	.string "went in and did not come out.$"

Nexus_Text_Necrozma_Boss:
	.string "The prisms turned, all together, toward\n"
	.string "the dark space.\p"
	.string "Something black and jagged unfolded\n"
	.string "out of it and reached for the light,\l"
	.string "and every reflection in the room went\l"
	.string "dim.$"

Nexus_Text_Necrozma_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-800. Prism.\p"
	.string "The creature we chased across Johto,\n"
	.string "and an Anabel who is not quite ours,\l"
	.string "standing guard in front of it.\p"
	.string "What came back with you is small and\n"
	.string "gives off an uneven light. It does not\l"
	.string "steal. It only looks for more. Anabel,\l"
	.string "ours, sat with it for an hour and did\l"
	.string "not say why.$"
```

</details>


#### Deoxys

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_Deoxys_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Deoxys**. Anabel é a campeã dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Anabel, a Faller que caiu de algum lugar e chegou mudada.

**A criatura.** Mítico nascido de um vírus espacial que sofreu mutação ao ser atingido por um laser. Chegou num meteoro; o cristal no peito é o cérebro, e muda de forma (Normal, Attack, Defense, Speed) para sobreviver.

**O fragmento.** Um céu de noite riscado por um feixe de luz que desce reto e bate num meteoro caído. Em volta da cratera, as pedras mudam de forma devagar, como se não tivessem decidido o que ser.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A night sky, and one straight beam of light coming down.
>
> It struck a fallen meteor. All around the crater, the stones were slowly changing shape, as if they had not decided what to be.

**Boss**

> The beam went out. The meteor split open.
>
> Something stood up from it, orange and blue, with a crystal in its chest. It changed its shape twice before it moved.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md))

> File L-386. Rewritten.
>
> Something that fell from the sky and changed to survive the landing, and a woman who knows exactly how that feels.
>
> What came back with you changes a little every day. Anabel says that is normal. She says it quietly.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Deoxys_Arrival:
	.string "A night sky, and one straight beam of\n"
	.string "light coming down.\p"
	.string "It struck a fallen meteor. All around\n"
	.string "the crater, the stones were slowly\l"
	.string "changing shape, as if they had not\l"
	.string "decided what to be.$"

Nexus_Text_Deoxys_Boss:
	.string "The beam went out. The meteor split\n"
	.string "open.\p"
	.string "Something stood up from it, orange and\n"
	.string "blue, with a crystal in its chest. It\l"
	.string "changed its shape twice before it\l"
	.string "moved.$"

Nexus_Text_Deoxys_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-386. Rewritten.\p"
	.string "Something that fell from the sky and\n"
	.string "changed to survive the landing, and a\l"
	.string "woman who knows exactly how that\l"
	.string "feels.\p"
	.string "What came back with you changes a\n"
	.string "little every day. Anabel says that is\l"
	.string "normal. She says it quietly.$"
```

</details>


### Diálogo genérico

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Anabel_Fight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Anabel cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala dela mesma, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

A Anabel das salas é a do fragmento (ver o time acima): ela reconhece o jogador, lembra da captura com ela mesma jogando a Ball, e não finge ter certeza de quem é. A voz é a do design (§3): frases curtas, pergunta objetiva, cuidado sem condescendência; a percepção de Faller aparece do tamanho certo (um instante antes, sem radar).

**Antes da luta**

> Anabel. International Police. I know your face. You went through the altar with your partner.
>
> In the version I remember, I threw the Beast Ball. I've checked that memory twice. It holds.
>
> So either my memory is wrong, or I'm not the Anabel you left at the altar. I felt this room open a second before you walked in. That part hasn't changed.
>
> Either way, the procedure is the same. Show me.

**Derrota**

> Noted. I'll trust the result over the feeling.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Anabel_Intro:
	.string "Anabel. International Police. I know\n"
	.string "your face. You went through the altar\l"
	.string "with your partner.\p"
	.string "In the version I remember, I threw the\n"
	.string "Beast Ball. I've checked that memory\l"
	.string "twice. It holds.\p"
	.string "So either my memory is wrong, or I'm\n"
	.string "not the Anabel you left at the altar. I\l"
	.string "felt this room open a second before\l"
	.string "you walked in. That part hasn't\l"
	.string "changed.\p"
	.string "Either way, the procedure is the same.\n"
	.string "Show me.$"

Nexus_Text_Anabel_Defeat:
	.string "Noted. I'll trust the result over the\n"
	.string "feeling.$"
```

</details>


#### Variações 2 e 3 (📝 proposta de 30/09/2026)

A Anabel das salas é a do fragmento em que ela jogou a Beast Ball (R21). A variação 1 fala dessa memória. Na 2, a lembrança de antes da polícia: a Salon Maiden que lia os desafiantes na escada da Battle Tower e não consegue ler o jogador. Na 3, um aceno leve aos fios do diário: o homem de sobretudo e um caderno com anotações na margem na letra dela, que ela não lembra de ter escrito (nunca confirmar de quem é a segunda mão).

**Variação 2 — a Salon Maiden que lia a escada**

**Antes da luta**

> Anabel. Before the police, I kept the top floor of a tower. Challengers climbed seven battles to reach me.
>
> I used to read them on the stairs. Breathing. Footsteps. By the time they reached the door, I knew who would win.
>
> I can't read you. Not yet. That's either your talent or my problem.
>
> Let's find out which.

**Derrota**

> Your talent. Logged.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Anabel_Intro2:
	.string "Anabel. Before the police, I kept the\n"
	.string "top floor of a tower. Challengers\l"
	.string "climbed seven battles to reach me.\p"
	.string "I used to read them on the stairs.\n"
	.string "Breathing. Footsteps. By the time they\l"
	.string "reached the door, I knew who would win.\p"
	.string "I can't read you. Not yet. That's\n"
	.string "either your talent or my problem.\p"
	.string "Let's find out which.$"

Nexus_Text_Anabel_Defeat2:
	.string "Your talent. Logged.$"
```

</details>

**Variação 3 — o sobretudo e a letra na margem**

**Antes da luta**

> Before we start. Have you seen a man in a long coat? He asks questions and writes the answers down.
>
> He left a notebook behind. Some of the notes in the margins are in my handwriting. I don't remember writing them.
>
> I've filed that under “later.” The file is getting thick.
>
> Right now, you're the case. Begin.

**Derrota**

> Case closed. For now. I'll reopen it if the evidence changes.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Anabel_Intro3:
	.string "Before we start. Have you seen a man in\n"
	.string "a long coat? He asks questions and\l"
	.string "writes the answers down.\p"
	.string "He left a notebook behind. Some of the\n"
	.string "notes in the margins are in my\l"
	.string "handwriting. I don't remember writing\l"
	.string "them.\p"
	.string "I've filed that under “later.” The file\n"
	.string "is getting thick.\p"
	.string "Right now, you're the case. Begin.$"

Nexus_Text_Anabel_Defeat3:
	.string "Case closed. For now. I'll reopen it if\n"
	.string "the evidence changes.$"
```

</details>


### Diálogo associado ao lendário

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Anabel é a campeã, a luta logo antes do lendário do dia. Um registro por lendário; a fala é sobre a criatura, sem dizer o nome dela.

#### Necrozma

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Anabel_Necrozma_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

A Anabel conhece a criatura melhor que ninguém: correu atrás dela por Johto inteira. Aqui ela não fala do perigo; fala do que mediu. O bicho não é cruel: perdeu a própria luz e continua procurando. A virada é pessoal e curta, do jeito dela: ela, Faller com lacunas de memória, sabe como é ficar faltando um pedaço e continuar estendendo a mão. Ela não sente pena; sente reconhecimento. E pede ao jogador o que pediria de qualquer operação: que traga de volta o que sobrar, e que volte.

**Antes da luta**

> You know this one. So do I. We chased it across Johto.
>
> Here's what I measured: it isn't cruel. It lost its own light, and it keeps reaching for more.
>
> Here's what I feel: I know what it's like to be missing a piece and keep reaching.
>
> I won't let that make me gentle. Ready?

**Derrota**

> Good. You didn't hesitate. It won't either.

**Depois da luta**

> I can't tell you what it wants. I only know what it's missing.
>
> People think a Faller remembers the other side. I don't. I remember the edge of it.
>
> That creature lives at the edge too. Always almost whole.
>
> Bring back whatever is left of it. And come back yourself. That part isn't optional.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Anabel_Necrozma_ChampionIntro:
	.string "You know this one. So do I. We chased it\n"
	.string "across Johto.\p"
	.string "Here's what I measured: it isn't cruel.\n"
	.string "It lost its own light, and it keeps\l"
	.string "reaching for more.\p"
	.string "Here's what I feel: I know what it's\n"
	.string "like to be missing a piece and keep\l"
	.string "reaching.\p"
	.string "I won't let that make me gentle.\n"
	.string "Ready?$"

Nexus_Text_Anabel_Necrozma_ChampionDefeat:
	.string "Good. You didn't hesitate. It won't\n"
	.string "either.$"

Nexus_Text_Anabel_Necrozma_ChampionAfter:
	.string "{SPEAKER NAME_ANABEL}I can't tell you what it wants. I only\n"
	.string "know what it's missing.\p"
	.string "People think a Faller remembers the\n"
	.string "other side. I don't. I remember the\l"
	.string "edge of it.\p"
	.string "That creature lives at the edge too.\n"
	.string "Always almost whole.\p"
	.string "Bring back whatever is left of it. And\n"
	.string "come back yourself. That part isn't\l"
	.string "optional.$"
```

</details>

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

Na variação 1 ela reconhece a criatura (falta um pedaço, e continua estendendo a mão). Na 2, a lembrança do arremesso, contada como relatório: pulso, ângulo, três balançadas, e a bola quente desde então; à noite ela brilha com luz que não é dele. Na 3, o fio **Ultra**: a cidade do outro lado que perdeu o céu, a dúvida sobre o que fizeram com ele, e a **Beast Ball rachada** (a rachadura cresce menos de um milímetro por dia).

**Variação 2 — o arremesso**

**Antes da luta**

> I remember the throw. Wrist, angle, distance. I've replayed it more times than I can count.
>
> The ball shook three times. On the third, the light around us came back. All of it at once.
>
> People cheered. I didn't. I was watching the ball. It was still warm.
>
> It's been warm ever since. Ready?

**Derrota**

> Confirmed. You would have made the throw too.

**Depois da luta**

> It's in a ball on my belt. It doesn't struggle. It doesn't sleep either.
>
> At night the ball gives off light. Not its own. Pieces it took, still trying to find their way home.
>
> I kept it because someone had to. I'm not sure that's the same as a reason.
>
> Go. What's out there is the part that never went into the ball. And come back.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Anabel_Necrozma_ChampionIntro2:
	.string "I remember the throw. Wrist, angle,\n"
	.string "distance. I've replayed it more times\l"
	.string "than I can count.\p"
	.string "The ball shook three times. On the\n"
	.string "third, the light around us came back. All\l"
	.string "of it at once.\p"
	.string "People cheered. I didn't. I was\n"
	.string "watching the ball. It was still warm.\p"
	.string "It's been warm ever since. Ready?$"

Nexus_Text_Anabel_Necrozma_ChampionDefeat2:
	.string "Confirmed. You would have made the\n"
	.string "throw too.$"

Nexus_Text_Anabel_Necrozma_ChampionAfter2:
	.string "{SPEAKER NAME_ANABEL}It's in a ball on my belt. It doesn't\n"
	.string "struggle. It doesn't sleep either.\p"
	.string "At night the ball gives off light. Not\n"
	.string "its own. Pieces it took, still trying to\l"
	.string "find their way home.\p"
	.string "I kept it because someone had to. I'm\n"
	.string "not sure that's the same as a reason.\p"
	.string "Go. What's out there is the part that\n"
	.string "never went into the ball. And come back.$"
```

</details>

**Variação 3 — a cidade sem céu, e a rachadura**

**Antes da luta**

> There's a city on the other side of the wormholes. Its people lost their sky to this creature.
>
> They built a tower to feed it light, so it would stop taking. It kept taking.
>
> In my version, I gave them their sky back. I have no idea what they did with it.
>
> That bothers me more than it should. Let's go.

**Derrota**

> Good. One less thing to wonder about.

**Depois da luta**

> My Beast Ball has a crack in it now. Hairline. It wasn't there last week.
>
> I measured it. It grows by less than a millimeter a day. Very patient.
>
> My feeling: it isn't trying to escape. It's trying to see out.
>
> Bring back whatever you find. And come back. I'll be here, checking the crack.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Anabel_Necrozma_ChampionIntro3:
	.string "There's a city on the other side of the\n"
	.string "wormholes. Its people lost their sky to\l"
	.string "this creature.\p"
	.string "They built a tower to feed it light, so\n"
	.string "it would stop taking. It kept taking.\p"
	.string "In my version, I gave them their sky\n"
	.string "back. I have no idea what they did with\l"
	.string "it.\p"
	.string "That bothers me more than it should.\n"
	.string "Let's go.$"

Nexus_Text_Anabel_Necrozma_ChampionDefeat3:
	.string "Good. One less thing to wonder about.$"

Nexus_Text_Anabel_Necrozma_ChampionAfter3:
	.string "{SPEAKER NAME_ANABEL}My Beast Ball has a crack in it now.\n"
	.string "Hairline. It wasn't there last week.\p"
	.string "I measured it. It grows by less than a\n"
	.string "millimeter a day. Very patient.\p"
	.string "My feeling: it isn't trying to escape.\n"
	.string "It's trying to see out.\p"
	.string "Bring back whatever you find. And come\n"
	.string "back. I'll be here, checking the crack.$"
```

</details>


#### Deoxys

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Anabel_Deoxys_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

A criatura caiu do céu e se reescreveu para sobreviver à chegada: muda de forma quando precisa. A Anabel também caiu de outro lugar e chegou diferente, sem boa parte do que era antes. A virada: a Anabel não trata isso como perda. Ela diz, com a precisão de sempre, que o que mudou nela na queda foi o preço de estar aqui, e que a criatura pagou o mesmo. E que as duas decidiram ficar.

**Antes da luta**

> It fell from the sky. So did I, more or less.
>
> It changed its shape to survive the landing. I lost most of what came before mine.
>
> Two different ways of paying the same price.
>
> I've stopped thinking of it as a loss. Let's see what you think.

**Derrota**

> Measured and confirmed. You're stronger than I planned for.

**Depois da luta**

> People ask me what I was before. I tell them the truth: I don't know.
>
> What I know is what I chose after. The police. This work. Staying.
>
> That creature changed to survive. Then it had to decide what to do with the shape it had.
>
> Go on. Find out what it decided.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Anabel_Deoxys_ChampionIntro:
	.string "It fell from the sky. So did I, more or\n"
	.string "less.\p"
	.string "It changed its shape to survive the\n"
	.string "landing. I lost most of what came\l"
	.string "before mine.\p"
	.string "Two different ways of paying the same\n"
	.string "price.\p"
	.string "I've stopped thinking of it as a loss.\n"
	.string "Let's see what you think.$"

Nexus_Text_Anabel_Deoxys_ChampionDefeat:
	.string "Measured and confirmed. You're\n"
	.string "stronger than I planned for.$"

Nexus_Text_Anabel_Deoxys_ChampionAfter:
	.string "{SPEAKER NAME_ANABEL}People ask me what I was before. I tell\n"
	.string "them the truth: I don't know.\p"
	.string "What I know is what I chose after. The\n"
	.string "police. This work. Staying.\p"
	.string "That creature changed to survive.\n"
	.string "Then it had to decide what to do with\l"
	.string "the shape it had.\p"
	.string "Go on. Find out what it decided.$"
```

</details>

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

Na variação 1 a queda e a mudança são o mesmo preço. Na 2 ela lê a ficha oficial (vírus do espaço + laser = acidente) e compara com a própria: as quatro formas da criatura são o que ela faz devagar, escolhendo voz, postura, quanto fala. Na 3 a surpresa: é a primeira coisa que chega sem ela sentir antes; e o segredo que ela nunca pôs em relatório: o clarão da Beast Ball fechando subiu reto para o céu, e semanas depois algo caiu de volta procurando aquela luz. Liga os dois lendários dela (e é a página 2 do diário).

**Variação 2 — a ficha oficial**

**Antes da luta**

> A virus from space. Hit by a laser. Changed into something that thinks with a crystal.
>
> That's the official file. I read it twice. It reads like an accident.
>
> Mine reads like one too. Fell through a hole in the sky. Woke up with half a memory.
>
> Accidents can still turn out well. Show me one.

**Derrota**

> Noted. Some accidents go right.

**Depois da luta**

> It has four shapes. It picks one for every situation, and it never apologizes for the choice.
>
> I have one shape. I choose everything else. Voice, posture, how much I say.
>
> Maybe that's the same thing, done more slowly.
>
> Go. Watch which shape it picks for you. That's its opinion of you.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Anabel_Deoxys_ChampionIntro2:
	.string "A virus from space. Hit by a laser.\n"
	.string "Changed into something that thinks\l"
	.string "with a crystal.\p"
	.string "That's the official file. I read it\n"
	.string "twice. It reads like an accident.\p"
	.string "Mine reads like one too. Fell through a\n"
	.string "hole in the sky. Woke up with half a\l"
	.string "memory.\p"
	.string "Accidents can still turn out well. Show\n"
	.string "me one.$"

Nexus_Text_Anabel_Deoxys_ChampionDefeat2:
	.string "Noted. Some accidents go right.$"

Nexus_Text_Anabel_Deoxys_ChampionAfter2:
	.string "{SPEAKER NAME_ANABEL}It has four shapes. It picks one for\n"
	.string "every situation, and it never\l"
	.string "apologizes for the choice.\p"
	.string "I have one shape. I choose everything\n"
	.string "else. Voice, posture, how much I say.\p"
	.string "Maybe that's the same thing, done more\n"
	.string "slowly.\p"
	.string "Go. Watch which shape it picks for you.\n"
	.string "That's its opinion of you.$"
```

</details>

**Variação 3 — o que ela não pôs no relatório**

**Antes da luta**

> I feel openings a second before they happen. Every wormhole. Every rift.
>
> When that meteor came down, I felt nothing. No warning. It simply arrived.
>
> First time in years something surprised me. I didn't enjoy it. I'm told I smiled.
>
> Don't tell anyone. Begin.

**Derrota**

> Surprised twice in one day. Unacceptable. Well done.

**Depois da luta**

> Here's something I haven't put in any report.
>
> The night I made my catch, there was a flash when the ball closed. Straight up, into the sky.
>
> Weeks later, something came back down. Changed. Looking for the light that sent it.
>
> I don't know if I made it. I'd rather know. Go and find out for me.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Anabel_Deoxys_ChampionIntro3:
	.string "I feel openings a second before they\n"
	.string "happen. Every wormhole. Every rift.\p"
	.string "When that meteor came down, I felt\n"
	.string "nothing. No warning. It simply arrived.\p"
	.string "First time in years something surprised\n"
	.string "me. I didn't enjoy it. I'm told I smiled.\p"
	.string "Don't tell anyone. Begin.$"

Nexus_Text_Anabel_Deoxys_ChampionDefeat3:
	.string "Surprised twice in one day.\n"
	.string "Unacceptable. Well done.$"

Nexus_Text_Anabel_Deoxys_ChampionAfter3:
	.string "{SPEAKER NAME_ANABEL}Here's something I haven't put in any\n"
	.string "report.\p"
	.string "The night I made my catch, there was a\n"
	.string "flash when the ball closed. Straight up,\l"
	.string "into the sky.\p"
	.string "Weeks later, something came back down.\n"
	.string "Changed. Looking for the light that\l"
	.string "sent it.\p"
	.string "I don't know if I made it. I'd rather\n"
	.string "know. Go and find out for me.$"
```

</details>


