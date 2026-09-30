# Cynthia

**Região da ficha:** Sinnoh

Aparece no checklist como:

- **Cynthia — Campeã** (Sinnoh · Elite Four e Campeã) — arqueóloga, pesquisadora de mitos e uma das Campeãs mais poderosas.
- **Cynthia** (Unova · Outros notáveis) — Campeã visitante que pode ser desafiada em Undella Town.

**Pronto para o Nexus:** ✅ sim — tem sprite e battle sprite.

**Arte disponível:** ✅ overworld e front pic em `.filetransfer/.trainers/Cynthia/` — e os dois **já registrados** no código (ver abaixo).

## Checklist

- [x] Sprite de overworld *(obrigatório)*
- [x] Battle sprite / front pic *(obrigatório)*
- [ ] Field mugshot (retrato na caixa de diálogo)
- [ ] Time para as Rift Missions definido — 📝 proposta abaixo (30/09/2026)
- [ ] Associado a um lendário — 📝 proposta abaixo (30/09/2026)
- [ ] Diálogo genérico escrito — 📝 proposta abaixo (30/09/2026)
- [ ] Diálogo associado ao lendário escrito — 📝 proposta abaixo (30/09/2026)

## Referências no repositório

### Sprite de overworld

| Constante | Arquivo |
|---|---|
| `OBJ_EVENT_GFX_CYNTHIA` | `graphics/object_events/pics/people/special/cynthia.png` (32x32, 9 quadros; a folha de origem não tem o lado direito). Arte oficial (Pokémon Platinum) |

Origem em `.filetransfer/.trainers/Cynthia/`: `Sprite - oficial Platinum.png` (arte oficial de Platinum) e `Sprite - comparacao no jogo.png`.

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_CYNTHIA` | `graphics/trainers/front_pics/cynthia_front_pic.png` (64x64) + `cynthia_large.png` (80x80, só na batalha). Arte oficial (Pokémon Platinum) |

Origem em `.filetransfer/.trainers/Cynthia/`: `Trainer - Brumirage.png` (80x80, autor **Brumirage**) e `Trainer - comparacao no jogo.png`.

### Field mugshot

Não existe (a pasta da arte não tem retrato). Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

Nenhuma. Ao criar, seguir a skill `adicionar-batalha-npc` (e `alocar-flag` se precisar de flag nova).

### Time das Rift Missions

📝 **Proposta de 30/09/2026, aguardando o autor.** `TRAINER_NEXUS_CYNTHIA` (ID **a alocar**: livre abaixo de 1056, nunca 1056–1163), campeã de Giratina (co-campeã com o Silver). Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega; 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler). Validado com `python3 dev_scripts/nexus_validar_time.py` (✓). Pic `Cynthia` (`TRAINER_PIC_FRONT_CYNTHIA`, já no código).

Lendário **Giratina, Forma Origem** (Griseous Core), de que ela é co-campeã: a estudiosa de mitos que, em Platinum, entra no Mundo Distorção atrás do Cyrus, e a descendente do homem de Hisui que pediu poder a ele. Semi-lendário **Azelf**, o Ser da Vontade: em Platinum o trio dos lagos surge em Spear Pillar para segurar a corrente, logo antes de ela e o jogador entrarem no Mundo Distorção. Mega **Garchomp** (Groundite), o ás dela desde Diamond/Pearl. Mais **Spiritomb** (a abertura clássica dela), **Milotic** e **Togekiss**, do time de Platinum. O Lucario e a Roserade saem: a Togekiss e a Milotic cobrem melhor o plano, e em Doubles o Earthquake da Garchomp não acerta a Giratina, o Azelf (Levitate) nem a Togekiss (Voador).

*Plano (Singles):* o Azelf de Focus Sash abre com Stealth Rock e Taunt e sai de U-turn; a Spiritomb queima com Will-O-Wisp e castiga o atacante com Foul Play; a Milotic segura especiais com Recover e apaga boosts com Haze; a Giratina-O bate com Poltergeist e fecha com Shadow Sneak; a Mega Garchomp sobe Swords Dance quando o campo está limpo e varre no fim.

*Plano (Doubles):* a Togekiss puxa tudo com Follow Me enquanto a Mega Garchomp sobe Swords Dance; depois a Garchomp solta Earthquake ao lado de quem é imune (Giratina, Azelf, Togekiss). A Milotic de Competitive castiga o Intimidate do jogador; a Spiritomb queima o atacante físico.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Giratina-Origin | Griseous Core | Levitate | Adamant | Poltergeist, Dragon Claw, Shadow Sneak, Earthquake |
| Azelf | Focus Sash | Levitate | Timid | Stealth Rock, Taunt, Psychic, U-turn |
| Garchomp | Groundite | Rough Skin | Jolly | Swords Dance, Earthquake, Dragon Claw, Stone Edge |
| Spiritomb | Leftovers | Infiltrator | Careful | Foul Play, Will-O-Wisp, Sucker Punch, Pain Split |
| Milotic | Leftovers | Competitive | Bold | Scald, Ice Beam, Recover, Haze |
| Togekiss | Sitrus Berry | Serene Grace | Timid | Air Slash, Dazzling Gleam, Follow Me, Roost |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>dev_scripts/nexus_validar_time.py</code>: trainerproc, constantes, learnsets e vagas)</summary>

```
=== TRAINER_NEXUS_CYNTHIA ===
Name: Cynthia
Class: Champion
Pic: Cynthia
Gender: Female
Music: Hg Champion
Double Battle: No
AI: Smart Trainer

Giratina-Origin @ Griseous Core
Adamant Nature
Level: 100
Ability: Levitate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Poltergeist
- Dragon Claw
- Shadow Sneak
- Earthquake

Azelf @ Focus Sash
Timid Nature
Level: 100
Ability: Levitate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Stealth Rock
- Taunt
- Psychic
- U-turn

Garchomp @ Groundite
Jolly Nature
Level: 100
Ability: Rough Skin
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Swords Dance
- Earthquake
- Dragon Claw
- Stone Edge

Spiritomb @ Leftovers
Careful Nature
Level: 100
Ability: Infiltrator
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Foul Play
- Will-O-Wisp
- Sucker Punch
- Pain Split

Milotic @ Leftovers
Bold Nature
Level: 100
Ability: Competitive
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Scald
- Ice Beam
- Recover
- Haze

Togekiss @ Sitrus Berry
Timid Nature
Level: 100
Ability: Serene Grace
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Air Slash
- Dazzling Gleam
- Follow Me
- Roost
```

</details>

### Lendário associado

#### Giratina

📝 **Proposta de 30/09/2026, aguardando o autor.** **Giratina**, com a Cynthia como **co-campeã** ao lado do Silver (o Silver continua campeão; ninguém cede — tabela de [`DIARIO_LOOKER.md`](../DIARIO_LOOKER.md)). No dia do Giratina, o sorteio escolhe um dos dois.

**Quem é.** Cynthia, Campeã de Sinnoh em Diamond/Pearl/Platinum, arqueóloga e pesquisadora de mitos, neta da anciã de Celestic Town. Em Platinum é ela quem entra com o jogador no Mundo Distorção atrás do Cyrus. Em Legends: Arceus, o mercador Volo — de rosto e sangue ligados a ela — pede poder ao Giratina.

**A criatura.** Giratina foi banido para o Mundo Distorção pela própria violência, diz o mito de Sinnoh. Vive no avesso do nosso mundo e o observa de lá; fora dele, só mantém a Forma Origem com a Griseous Orb (ou o Griseous Core).

**O fragmento.** O mesmo do Silver: um mundo sem baixo. No da Cynthia, ninguém chegou a tempo em Spear Pillar; ela subiu sozinha, quebrou a corrente vermelha com as mãos, caiu no rasgo e foi apanhada por uma asa preta. Ficou, e guarda a porta. O Silver, de outro fragmento, guarda a mesma porta; ela nunca o viu, só a sombra dele, caindo para cima.

**Falas do fragmento** (narração; **já estão no jogo**, `Nexus_Text_Giratina_Arrival` e `Nexus_Text_Giratina_Boss` em `data/scripts/nexus.inc` — valem para qualquer campeão deste lendário e não mudam):

**Chegada**

> Nothing here agreed on which way was down.
>
> A waterfall ran sideways across the sky. Trees grew from the undersides of floating rocks. Your shadow fell up.

**Boss**

> The shadows gathered into one, huge and long, and black wings tipped with red unfolded out of it.
>
> Somewhere, the right way up was being torn open again.

**Ficha do Looker** — **já existe no jogo**: `Nexus_EventScript_Giratina_LookerFile` → `Nexus_Text_Giratina_LookerFile` (`data/scripts/nexus.inc`). Não reescrita aqui; o texto atual, para referência:

> File L-487. Renegade.
>
> A world with no down, and a young man who ran from his father and never quite stopped.
>
> What came back with you is a small shadow that falls the right way. For now. He asked me if it would stay that way. I told him that depends on who raises it.

O File L-487 fala do Silver (“a young man who ran from his father”). **Mantido como está**, a pedido: a Cynthia é co-campeã, e o diário dela (página 3) liga os dois pela mesma porta. Se o autor quiser um texto por campeão, é código novo (o Looker File hoje é por lendário, R18).


### Diálogo genérico

📝 **Proposta de 30/09/2026, aguardando o autor.** Quando Cynthia cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala de si, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

Voz da Cynthia de DP/Pt: calma, culta, gentil, com a curiosidade de quem estuda mitos e a segurança de quem nunca perdeu. As três variações: quem ela é (a pesquisadora), o cansaço de quem está no topo há tempo demais, e a avó de Celestic.

**Antes da luta**

> I'm Cynthia. I study myths -- the stories people tell when they can't explain what they saw.
>
> Every myth I've read began with someone who stood where you're standing, and decided to look closer.
>
> So. Let me see what you've decided.

**Derrota**

> …Wonderful. I'll have to write this down before it turns into a legend.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Cynthia_Intro:
	.string "I'm Cynthia. I study myths -- the\n"
	.string "stories people tell when they can't\l"
	.string "explain what they saw.\p"
	.string "Every myth I've read began with\n"
	.string "someone who stood where you're\l"
	.string "standing, and decided to look closer.\p"
	.string "So. Let me see what you've decided.$"

Nexus_Text_Cynthia_Defeat:
	.string "…Wonderful. I'll have to write this\n"
	.string "down before it turns into a legend.$"
```

</details>

#### Variações 2 e 3 (📝 proposta de 30/09/2026)

**Variação 2** — o cansaço do topo (e um aceno ao lugar sem manhã de onde ela veio, sem citá-lo)

**Antes da luta**

> Pardon me. I've been awake a very long time. Where I've been, there isn't a morning to wake up to.
>
> I've been Champion for so long, I've forgotten what it feels like to be the one climbing.
>
> Remind me. And please, don't hold back.

**Derrota**

> Ah… so this is the view from the bottom of the stairs. I'd missed it.

**Variação 3** — a avó de Celestic e as ruínas como carta ao futuro

**Antes da luta**

> My grandmother says the old ruins in our town are a letter, written to someone in the future.
>
> I've spent my whole life trying to read it. I never once asked who it was addressed to.
>
> Maybe it was you. Show me.

**Derrota**

> The letter's still unfinished, then. Good. I'd hate for it to end here.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Cynthia_Intro2:
	.string "Pardon me. I've been awake a very long\n"
	.string "time. Where I've been, there isn't a\l"
	.string "morning to wake up to.\p"
	.string "I've been Champion for so long, I've\n"
	.string "forgotten what it feels like to be the\l"
	.string "one climbing.\p"
	.string "Remind me. And please, don't hold back.$"

Nexus_Text_Cynthia_Defeat2:
	.string "Ah… so this is the view from the bottom\n"
	.string "of the stairs. I'd missed it.$"

Nexus_Text_Cynthia_Intro3:
	.string "My grandmother says the old ruins in\n"
	.string "our town are a letter, written to\l"
	.string "someone in the future.\p"
	.string "I've spent my whole life trying to read\n"
	.string "it. I never once asked who it was\l"
	.string "addressed to.\p"
	.string "Maybe it was you. Show me.$"

Nexus_Text_Cynthia_Defeat3:
	.string "The letter's still unfinished, then.\n"
	.string "Good. I'd hate for it to end here.$"
```

</details>

### Diálogo associado ao lendário

📝 **Proposta de 30/09/2026, aguardando o autor.** Quando Cynthia é o **campeão**, a luta logo antes do lendário. A fala é sobre a criatura, sem dizer o nome dela ([R16](../NEXUS_REGRAS.md)).

#### Giratina

A Cynthia é co-campeã com o Silver ([`johto/silver.md`](../johto/silver.md)): a fala dele é sobre ser expulso; a dela é de estudiosa. Ela leu tudo o que se escreveu sobre a criatura e percebeu que foi escrito só pelo lado de cá. No fragmento dela, ela quebrou a corrente vermelha, caiu no rasgo e foi apanhada. As três variações: reescrever o mito, a queda (a gentileza que ninguém espera dele) e o homem de Hisui com o rosto dela (Volo, nunca nomeado) — a dúvida se a criatura a vê como ele.

**Antes da luta**

> The old texts call it a renegade. Thrown out of the world for its violence.
>
> I've read those texts a hundred times. Every one was written by someone standing safely on this side.
>
> I've been on the other side now. I'd like to rewrite a few pages. …Shall we?

**Derrota**

> You fight like someone who reads the footnotes. I approve.

**Depois da luta**

> It isn't guarding a prison. It's holding up the back of the world, so ours doesn't fall through.
>
> Nobody thanks it. Nobody even draws it the right way up.
>
> Go on. When you meet it, look it in the eye. I think it's been waiting a long time for someone who isn't afraid.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Cynthia_ChampionIntro:
	.string "The old texts call it a renegade.\n"
	.string "Thrown out of the world for its\l"
	.string "violence.\p"
	.string "I've read those texts a hundred times.\n"
	.string "Every one was written by someone\l"
	.string "standing safely on this side.\p"
	.string "I've been on the other side now. I'd\n"
	.string "like to rewrite a few pages. …Shall we?$"

Nexus_Text_Cynthia_ChampionDefeat:
	.string "You fight like someone who reads the\n"
	.string "footnotes. I approve.$"

Nexus_Text_Cynthia_ChampionAfter:
	.string "{SPEAKER NAME_CYNTHIA}It isn't guarding a prison. It's\n"
	.string "holding up the back of the world, so\l"
	.string "ours doesn't fall through.\p"
	.string "Nobody thanks it. Nobody even draws it\n"
	.string "the right way up.\p"
	.string "Go on. When you meet it, look it in the\n"
	.string "eye. I think it's been waiting a long\l"
	.string "time for someone who isn't afraid.$"
```

</details>

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

**Variação 2** — a queda no rasgo e a asa que a apanhou (liga à corrente vermelha do fio Tempo)

**Antes da luta**

> Someone once tried to bind the lords of time and space with a red chain. I broke it with my own hands.
>
> The links fell into the dark, and so did I. Something caught me down there.
>
> It didn't have to. …I'm curious whether it'll do the same for you.

**Derrota**

> Caught again. How embarrassing.

**Depois da luta**

> It has no reason to be kind to anyone from our side. We called it a monster and shut the door.
>
> And still, when I fell, it caught me on one wing and set me down the right way up.
>
> Be gentle with whatever you bring back. It learned gentleness somewhere. I'd like to think it's catching.

**Variação 3** — o homem de Hisui com o rosto dela (Volo, nunca nomeado) e o pedido de desculpas

**Antes da luta**

> Long ago, there was a man who looked a great deal like me. He wanted its power, and it gave him some.
>
> I keep wondering what it saw when I walked in. Him again? Or me?
>
> Help me find out.

**Derrota**

> Hm. I think it saw me. Thank you.

**Depois da luta**

> It remembers faces for a very long time. Longer than names. Longer than apologies.
>
> I apologized anyway. For him. For all of us who only ever came to take something.
>
> Now go. And if it looks at you like it's measuring you… it is. Stand up straight.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Cynthia_ChampionIntro2:
	.string "Someone once tried to bind the lords\n"
	.string "of time and space with a red chain. I\l"
	.string "broke it with my own hands.\p"
	.string "The links fell into the dark, and so did\n"
	.string "I. Something caught me down there.\p"
	.string "It didn't have to. …I'm curious\n"
	.string "whether it'll do the same for you.$"

Nexus_Text_Cynthia_ChampionDefeat2:
	.string "Caught again. How embarrassing.$"

Nexus_Text_Cynthia_ChampionAfter2:
	.string "{SPEAKER NAME_CYNTHIA}It has no reason to be kind to anyone\n"
	.string "from our side. We called it a monster\l"
	.string "and shut the door.\p"
	.string "And still, when I fell, it caught me on\n"
	.string "one wing and set me down the right way\l"
	.string "up.\p"
	.string "Be gentle with whatever you bring\n"
	.string "back. It learned gentleness somewhere.\l"
	.string "I'd like to think it's catching.$"

Nexus_Text_Cynthia_ChampionIntro3:
	.string "Long ago, there was a man who looked a\n"
	.string "great deal like me. He wanted its power,\l"
	.string "and it gave him some.\p"
	.string "I keep wondering what it saw when I\n"
	.string "walked in. Him again? Or me?\p"
	.string "Help me find out.$"

Nexus_Text_Cynthia_ChampionDefeat3:
	.string "Hm. I think it saw me. Thank you.$"

Nexus_Text_Cynthia_ChampionAfter3:
	.string "{SPEAKER NAME_CYNTHIA}It remembers faces for a very long\n"
	.string "time. Longer than names. Longer than\l"
	.string "apologies.\p"
	.string "I apologized anyway. For him. For all of\n"
	.string "us who only ever came to take\l"
	.string "something.\p"
	.string "Now go. And if it looks at you like it's\n"
	.string "measuring you… it is. Stand up\l"
	.string "straight.$"
```

</details>

Falante novo: `SP_NAME_CYNTHIA` (ainda não existe em `include/constants/speaker_names.h`).

### Diário do Looker

📝 **Proposta de 30/09/2026, aguardando o autor.** Três páginas em [`diario_looker/cynthia/`](diario_looker/cynthia/) ([formato e fios](../DIARIO_LOOKER.md)): [`1_comeco.md`](diario_looker/cynthia/1_comeco.md), [`2_meio.md`](diario_looker/cynthia/2_meio.md), [`3_fim.md`](diario_looker/cynthia/3_fim.md). Labels `Nexus_Text_Diary_Cynthia_1` a `_3`.
