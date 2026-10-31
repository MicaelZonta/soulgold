# Leon

**Região da ficha:** Galar

Aparece no checklist como:

- **Leon — Campeão** (Galar · Campeão e Champion Cup) — Campeão invicto de Galar, famoso por seu Charizard e péssimo senso de direção.

**Pronto para o Nexus:** ✅ sim — no pool desde 31/10/2026 (lote novo, bloco 2 de IDs).

**Arte disponível:** ✅ overworld e front pic em `.filetransfer/.trainers/Leon/` (o overworld já está registrado; a front pic ainda não).

## Checklist

- [x] Sprite de overworld *(obrigatório)*
- [x] Battle sprite / front pic *(obrigatório)* — arte em `.filetransfer/.trainers/Leon/`, falta registrar
- [ ] Field mugshot (retrato na caixa de diálogo)
- [x] Time para as Rift Missions definido — 📝 proposta de 30/09/2026 abaixo (validada), fora do código
- [x] Associado a um lendário — 📝 proposta de 30/09/2026: Eternatus (cedido pelo Tucker)
- [x] Diálogo genérico escrito — 📝 proposta de 30/09/2026 (3 variações)
- [x] Diálogo associado ao lendário escrito — 📝 proposta de 30/09/2026 (3 variações)

## Referências no repositório

### Sprite de overworld

| Constante | Arquivo |
|---|---|
| `OBJ_EVENT_GFX_LEON` (361; paleta `OBJ_EVENT_PAL_TAG_LEON` = `0x118A`) | `graphics/object_events/pics/people/special/leon.png` (16x32, `sAnimTable_StandardAsym`; `gObjectEventGraphicsInfo_Leon` em `src/data/object_events/object_event_graphics_info.h`) |

Nenhum mapa usa ainda. Folha de origem: `.filetransfer/.trainers/Leon/Sprite - Wolfang62.png` (256x256, autor **Wolfang62**); comparação no jogo em `Sprite - comparacao no jogo.png`.

### Battle sprite (front pic)

Não existe no código (`TRAINER_PIC_FRONT_LEON` não existe). A arte chegou:

| Arquivo | O que é |
|---|---|
| `.filetransfer/.trainers/Leon/Trainer - Wolfang62.png` | front pic, 160x160 (80x80 ampliado 2x), autor **Wolfang62** |
| `.filetransfer/.trainers/Leon/Trainer - comparacao no jogo.png` | comparação no jogo |

Falta converter para 64x64 (skill `converter-sprite`) e registrar (skill `adicionar-grafico-trainer`). O overworld já foi feito com a skill `adicionar-npc`.

### Field mugshot

Não existe, e a pasta `.filetransfer/.trainers/Leon/` não traz arte de mugshot. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

Nenhuma. Ao criar, seguir a skill `adicionar-batalha-npc` (e `alocar-flag` se precisar de flag nova).

### Time das Rift Missions

✅ **Implementado em 31/10/2026** (lote novo, time montado pelo Codex e conferido pelo `novos/integrar.py`: R10–R13 e habilidades): `TRAINER_NEXUS_LEON` = **1195** (bloco 2, flag `0xB1F`), luta genérica `Nexus_EventScript_Leon_Fight` em `data/scripts/nexus.inc`, linha em `src/data/nexus/trainers.h`. Ainda não é campeão de nenhum lendário.

```
=== TRAINER_NEXUS_LEON ===
Name: Leon
Class: Champion
Pic: Leon
Gender: Male
Music: Male
Double Battle: No
AI: Smart Trainer

Eternatus @ Power Herb
Timid Nature
Level: 100
Ability: Pressure
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Meteor Beam
- Dynamax Cannon
- Sludge Bomb
- Flamethrower

Urshifu @ Choice Band
Adamant Nature
Level: 100
Ability: Unseen Fist
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Wicked Blow
- Close Combat
- Sucker Punch
- U-turn

Charizard @ Gigantatite
Timid Nature
Level: 100
Ability: Blaze
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Heat Wave
- Air Slash
- Focus Blast
- Roost

Dragapult @ Light Clay
Jolly Nature
Level: 100
Ability: Infiltrator
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Dragon Darts
- Reflect
- Light Screen
- Will-O-Wisp

Aegislash @ Leftovers
Quiet Nature
Level: 100
Ability: Stance Change
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- King's Shield
- Shadow Ball
- Flash Cannon
- Shadow Sneak

Seismitoad @ Sitrus Berry
Modest Nature
Level: 100
Ability: Water Absorb
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Muddy Water
- Earth Power
- Stealth Rock
- Knock Off
```

### Lendário associado

✅ **Campeão extra desde 31/10/2026** (lendário com vários campeões; o do dia é sorteado, `src/data/nexus/champions.h`; associações e falas montadas pelo Codex):

- **Eternatus** — `Nexus_EventScript_Leon_Eternatus_ChampionFight` (falas `Nexus_Text_Leon_Eternatus_Champion*`)
- **Zacian** — `Nexus_EventScript_Leon_Zacian_ChampionFight` (falas `Nexus_Text_Leon_Zacian_Champion*`)
- **Urshifu Single Strike** — `Nexus_EventScript_Leon_Urshifu_ChampionFight` (falas `Nexus_Text_Leon_Urshifu_Champion*`)


#### Eternatus

📝 **Proposta de 30/09/2026, aguardando o autor.** **Eternatus**. Leon é o campeão dele: a quinta luta do Daily, logo antes da boss battle. Vem da tabela "Campeões novos" de [`DIARIO_LOOKER.md`](../DIARIO_LOOKER.md): quem cede é o **Tucker** (`hoenn/tucker.md`), que fica com o **Hoopa**. Enquanto o autor não aprova, a ficha do Tucker e o código continuam como estão (`Nexus_EventScript_Tucker_Eternatus_ChampionFight`).

**Quem é.** Leon, o Campeão invicto de Galar em Sword/Shield: capa cheia de patrocinadores, boné, a pose de "Champion Time" com o dedo para o alto. Irmão mais velho do Hop, de Postwick. Treinou com o Mustard no Master Dojo. Perde-se em qualquer lugar (o jogo inteiro brinca com isso). No jogo, na noite da final, sai correndo para parar o Rose e o Darkest Day — e quem resolve de verdade são o jogador e o Hop, com Zacian e Zamazenta.

**A criatura.** Caiu num meteoro há uns vinte mil anos e dormiu sob Galar. Absorve energia; foi a fonte do fenômeno Dynamax nos estádios e, acordado cedo demais pelo Chairman Rose, causou o Darkest Day. Nas lendas, a espada e o escudo (Zacian e Zamazenta) o devolveram ao sono.

**O fragmento.** O mesmo estádio sob céu vermelho que o jogo já usa (Chegada e Boss abaixo são os existentes). No fragmento do Leon, **a espada e o escudo nunca vieram**: estão em mãos erradas, em outros fragmentos (o Zacian com o Blue, o Zamazenta com o Norman). Sem eles, a noite escura não terminou. O Leon pegou a criatura sozinho, depois de uma noite inteira — e a noite continua, porque o céu não sabe que perdeu. Ele guarda a porta porque, invicto, é a única coisa que segura a luz dentro da bola (ver diário).

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário) — **já estão no jogo**, com o Tucker como campeão: `Nexus_Text_Eternatus_Arrival`, `Nexus_Text_Eternatus_Boss` e o Looker File `Nexus_Text_Eternatus_LookerFile` (**File L-890. Darkest Day.**) em `data/scripts/nexus.inc`. Não se repete nada aqui.

**Chegada** (existente)

> A huge stadium under a red sky.
>
> Every floodlight was on, every one of them aimed at the center of the pitch, and every seat was empty.
>
> The lights were not shining. They were pulling the light in.

**Boss** (existente)

> The pitch cracked open, and the red sky poured down into it.
>
> Something long and bone-white rose out of the ground, and every floodlight turned to face it.

**Ficha do Looker** (existente, File L-890)

> File L-890. Darkest Day.
>
> A stadium lit by the thing that eats its light, and a showman who loves an audience a little too much.
>
> What came back with you glows faintly, and only when someone looks at it. I have decided to look at it often.

O "showman who loves an audience a little too much" serve para o Leon tão bem quanto para o Tucker (a capa de patrocinadores, o Champion Time): se a troca for aprovada, **o File L-890 fica como está**. O `.inc` é o de `nexus.inc` (e o da ficha do Tucker); não há texto novo de fragmento.

### Diálogo genérico

✅ **Implementado em 31/10/2026:** `Nexus_Text_Leon_Intro` / `_Defeat` em `data/scripts/nexus.inc`.

**Antes da luta**

> Well, hello! I was looking for the stadium. It was left, wasn't it? Or... the other left?
>
> Never mind! Wherever there's a battle, that's where I was headed all along.
>
> Let's have a champion time!

**Derrota**

> Ha! Brilliant! That's the kind of battle that brings a whole stadium to its feet!

### Diálogo associado ao lendário

📝 **Proposta de 30/09/2026, aguardando o autor.** Quando o Leon é o **campeão**, a luta logo antes do lendário. A fala é sobre a criatura, sem dizer o nome dela ([R16](../NEXUS_REGRAS.md)).

#### Eternatus

O Tucker (variação do jogo) vê a criatura como uma estrela que rouba os holofotes. O Leon vê outra coisa: a noite que ele **não conseguiu parar**. As três variações: os heróis que não vieram e o jogador que veio (1); a fome da criatura como espelho da fome dele por vitória, e perder como presente (2); o elevador errado na noite em que ela acordou, e o irmão esperando o céu ficar azul (3). R21: nada depende do jogador ter conhecido este Leon.

##### Variação 1

**Antes da luta**

> It fell from the sky a long time ago and went to sleep under our feet. We built our stadiums right on top of it.
>
> Then someone woke it up too early, and the night came down and never lifted.
>
> I've held it back ever since. One more match won't hurt. Let's make it a good one!

**Derrota**

> Ha… Looks like the night gets a break tonight.

**Depois da luta**

> In the old stories, two heroes came with a sword and a shield and sent it back to sleep.
>
> Where I'm from, they never showed up. Maybe they got lost. I'd understand.
>
> So it's you, then. You're the one who showed up. Go on. Give it a proper final!

##### Variação 2

**Antes da luta**

> You know what it wants? Power. More and more of it, and it's never full.
>
> I know that feeling. Every win only made me want the next match.
>
> The difference is, I know when to stop! …Mostly. Champion time!

**Derrota**

> That's it. That's the match I've been waiting for.

**Depois da luta**

> Here's something nobody tells you about never losing. You never get to rest.
>
> It's the same for that thing out there. It can't stop taking, so it can't stop.
>
> Maybe it needs to lose once, too. Go and give it that.

##### Variação 3

**Antes da luta**

> I tried to reach it the night it woke up. I took the lift to the top of the tower… and came out in the basement.
>
> By the time I found the right floor, the sky had already gone red.
>
> I'm not letting you take a wrong turn. Straight through me, and straight to it!

**Derrota**

> Right. Straight through. You didn't even need a map.

**Depois da luta**

> My little brother is waiting for me back home. He's been waiting a long time.
>
> I told him I'd come back when the sky was blue again.
>
> Clear it up for me, would you? And if you pass a farm full of Wooloo… tell him his big brother says hi.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Leon_ChampionIntro:
	.string "It fell from the sky a long time ago\n"
	.string "and went to sleep under our feet. We\l"
	.string "built our stadiums right on top of it.\p"
	.string "Then someone woke it up too early, and\n"
	.string "the night came down and never lifted.\p"
	.string "I've held it back ever since. One more\n"
	.string "match won't hurt. Let's make it a good\l"
	.string "one!$"

Nexus_Text_Leon_ChampionDefeat:
	.string "Ha… Looks like the night gets a break\n"
	.string "tonight.$"

Nexus_Text_Leon_ChampionAfter:
	.string "{SPEAKER NAME_LEON}In the old stories, two heroes came\n"
	.string "with a sword and a shield and sent it\l"
	.string "back to sleep.\p"
	.string "Where I'm from, they never showed up.\n"
	.string "Maybe they got lost. I'd understand.\p"
	.string "So it's you, then. You're the one who\n"
	.string "showed up. Go on. Give it a proper\l"
	.string "final!$"

Nexus_Text_Leon_ChampionIntro2:
	.string "You know what it wants? Power. More\n"
	.string "and more of it, and it's never full.\p"
	.string "I know that feeling. Every win only\n"
	.string "made me want the next match.\p"
	.string "The difference is, I know when to stop!\n"
	.string "…Mostly. Champion time!$"

Nexus_Text_Leon_ChampionDefeat2:
	.string "That's it. That's the match I've been\n"
	.string "waiting for.$"

Nexus_Text_Leon_ChampionAfter2:
	.string "{SPEAKER NAME_LEON}Here's something nobody tells you\n"
	.string "about never losing. You never get to\l"
	.string "rest.\p"
	.string "It's the same for that thing out there.\n"
	.string "It can't stop taking, so it can't stop.\p"
	.string "Maybe it needs to lose once, too. Go\n"
	.string "and give it that.$"

Nexus_Text_Leon_ChampionIntro3:
	.string "I tried to reach it the night it woke\n"
	.string "up. I took the lift to the top of the\l"
	.string "tower… and came out in the basement.\p"
	.string "By the time I found the right floor,\n"
	.string "the sky had already gone red.\p"
	.string "I'm not letting you take a wrong turn.\n"
	.string "Straight through me, and straight to\l"
	.string "it!$"

Nexus_Text_Leon_ChampionDefeat3:
	.string "Right. Straight through. You didn't\n"
	.string "even need a map.$"

Nexus_Text_Leon_ChampionAfter3:
	.string "{SPEAKER NAME_LEON}My little brother is waiting for me\n"
	.string "back home. He's been waiting a long\l"
	.string "time.\p"
	.string "I told him I'd come back when the sky\n"
	.string "was blue again.\p"
	.string "Clear it up for me, would you? And if\n"
	.string "you pass a farm full of Wooloo… tell\l"
	.string "him his big brother says hi.$"
```

</details>

Falante novo: `SP_NAME_LEON` (ainda não existe em `include/constants/speaker_names.h`).

### Diário do Looker

📝 **Proposta de 30/09/2026, aguardando o autor.** Três páginas em [`diario_looker/leon/`](diario_looker/leon/) ([formato](../DIARIO_LOOKER.md)): [começo](diario_looker/leon/1_comeco.md) (a torre, a noite que não acaba), [meio](diario_looker/leon/2_meio.md) (os dois lobos que foram embora do menino perdido na névoa), [fim](diario_looker/leon/3_fim.md) (September 31st: o homem de sobretudo pede o caminho ao Leon). See also: File L-890.
