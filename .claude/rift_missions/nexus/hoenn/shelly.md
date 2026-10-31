# Shelly

**Região da ficha:** Hoenn

Aparece no checklist como:

- **Shelly** (Hoenn · Team Aqua) — administradora inteligente envolvida nas operações científicas da equipe.

**Pronto para o Nexus:** ✅ sim — no pool desde 31/10/2026 (lote novo, bloco 2 de IDs).

**Arte disponível:** ✅ overworld e front pic em `.filetransfer/.trainers/Shelly/` (o overworld já registrado; a front pic, não).

## Checklist

- [x] Sprite de overworld *(obrigatório)* — `OBJ_EVENT_GFX_SHELLY`, 30/09/2026; arte DiegoWT 25x21 em 03/10/2026
- [x] Battle sprite / front pic *(obrigatório)* — `TRAINER_PIC_FRONT_SHELLY` (64x64 + 80x80), 03/10/2026
- [ ] Field mugshot (retrato na caixa de diálogo)
- [x] Time para as Rift Missions definido — 📝 proposta abaixo (30/09/2026), fora do código
- [x] Associado a um lendário — 📝 proposta: Manaphy (cedido pela Misty)
- [x] Diálogo genérico escrito — 📝 proposta abaixo, 3 variações
- [x] Diálogo associado ao lendário escrito — 📝 proposta abaixo, 3 variações

## Referências no repositório

### Sprite de overworld

| Constante | Arquivo |
|---|---|
| `OBJ_EVENT_GFX_SHELLY` | `graphics/object_events/pics/people/special/shelly.png` — desde 03/10/2026 a arte da **DiegoWT** (`Sprite - DiegoWT.png`), boneco 25x21, quadro 32x32, 12 quadros, `sAnimTable_StandardAsym`; paleta própria `OBJ_EVENT_PAL_TAG_SHELLY` (a Swizzler121 16x19 de 30/09 saiu, escolha do autor) |

Fonte da arte em `.filetransfer/.trainers/Shelly/` (autor **Swizzler121**):

| Arquivo | O que é |
|---|---|
| `Sprite - DiegoWT.png` | overworld atual (origem do `shelly.png` acima) |
| `Sprite - Swizzler121.png` | overworld antigo (30/09), substituído |
| `Trainer - AI.png` | front pic alternativa (comparação `Trainer - comparacao no jogo (AI).png`) |
| `Sprite - comparacao no jogo.png` | comparação do overworld no jogo |
| `Trainer - Swizzler121.png` | front pic — **ainda não registrada** (skills `converter-sprite` e `adicionar-grafico-trainer`) |
| `Trainer - comparacao no jogo.png` | comparação da front pic no jogo |
| `outras/Folha completa - Swizzler121.png` | a folha inteira de onde saiu o overworld |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_SHELLY` | `graphics/trainers/front_pics/shelly.png` (64x64) + `shelly_large.png` (80x80, `TRAINER_SPRITE_LARGE`) — 03/10/2026; nenhuma batalha usa ainda |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`). A pasta da arte não traz mugshot.

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

Nenhuma. Ao criar, seguir a skill `adicionar-batalha-npc` (e `alocar-flag` se precisar de flag nova).

### Time das Rift Missions

✅ **Implementado em 31/10/2026** (lote novo, time montado pelo Codex e conferido pelo `novos/integrar.py`: R10–R13 e habilidades): `TRAINER_NEXUS_SHELLY` = **1211** (bloco 2, flag `0xB2F`), luta genérica `Nexus_EventScript_Shelly_Fight` em `data/scripts/nexus.inc`, linha em `src/data/nexus/trainers.h`. Ainda não é campeão de nenhum lendário.

```
=== TRAINER_NEXUS_SHELLY ===
Name: Shelly
Class: Pkmn Trainer 1
Pic: Shelly
Gender: Female
Music: Female
Double Battle: No
AI: Smart Trainer

Kyogre @ Choice Specs
Modest Nature
Level: 100
Ability: Drizzle
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Water Spout
- Origin Pulse
- Ice Beam
- Thunder

Manaphy @ Leftovers
Calm Nature
Level: 100
Ability: Hydration
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Take Heart
- Scald
- Energy Ball
- Rest

Sharpedo @ Watertite
Adamant Nature
Level: 100
Ability: Speed Boost
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Liquidation
- Crunch
- Psychic Fangs
- Protect

Mightyena @ Sitrus Berry
Jolly Nature
Level: 100
Ability: Intimidate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Sucker Punch
- Play Rough
- Taunt
- Yawn

Crobat @ Mental Herb
Jolly Nature
Level: 100
Ability: Infiltrator
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Tailwind
- Brave Bird
- Taunt
- U-turn

Ludicolo @ Life Orb
Modest Nature
Level: 100
Ability: Swift Swim
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Fake Out
- Hydro Pump
- Giga Drain
- Ice Beam
```

### Lendário associado

✅ **Campeão extra desde 31/10/2026** (lendário com vários campeões; o do dia é sorteado, `src/data/nexus/champions.h`; associações e falas montadas pelo Codex):

- **Manaphy** — `Nexus_EventScript_Shelly_Manaphy_ChampionFight` (falas `Nexus_Text_Shelly_Manaphy_Champion*`)
- **Kyogre** — `Nexus_EventScript_Shelly_Kyogre_ChampionFight` (falas `Nexus_Text_Shelly_Kyogre_Champion*`)
- **Volcanion** — `Nexus_EventScript_Shelly_Volcanion_ChampionFight` (falas `Nexus_Text_Shelly_Volcanion_Champion*`)


#### Manaphy

📝 **Proposta de 30/09/2026, aguardando o autor.** **Manaphy**, cedido pela **Misty** (que fica com o Kyogre), pela tabela "Campeões novos" de [`DIARIO_LOOKER.md`](../DIARIO_LOOKER.md). Enquanto o autor não aprova, o código e a ficha da Misty continuam como estão. Shelly seria a campeã dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Shelly, admin da Team Aqua em Emerald e em ORAS: cuida da parte científica (é ela quem invade o Weather Institute atrás dos dados de clima que levam ao dono do mar) e ri antes de responder ("Ahahahaha!"). Neste fragmento, ela largou a Aqua (fio "Hoenn" do diário).

**A criatura.** Manaphy, o Pokémon Navegante, o Príncipe do Mar. Nasce no fundo frio do oceano, nada distâncias enormes para voltar ao lugar onde nasceu, e com Heart Swap troca o coração de dois seres. Quem ele vê primeiro ao sair do ovo vira a mãe dele (o filme do Templo do Mar). Neste hack evolui de Phione no nível 58; o fragmento que o jogador leva é um Phione ([R17](../NEXUS_REGRAS.md)).

**O fragmento.** Já existe no jogo e **não é reescrito**: é o mesmo de hoje, o fundo de mar frio iluminado por ovos que vão embora e voltam. Ele serve à Shelly sem mudar uma vírgula — o bebê que nasceu nas mãos dela sempre volta para ela.

- Chegada: `Nexus_Text_Manaphy_Arrival` (`data/scripts/nexus.inc`)
- Boss: `Nexus_Text_Manaphy_Boss`
- Ficha do Looker: `Nexus_EventScript_Manaphy_LookerFile` → `Nexus_Text_Manaphy_LookerFile` (**File L-490. Seafaring.**), ver a ficha da [Misty](../kanto/misty.md#manaphy).

> ⚠️ O Looker File de hoje fala da campeã atual ("a Gym Leader who keeps saying she will leave… she always goes back to her city"). Se a troca for aprovada, essas duas frases precisam de ajuste — por acaso, "keeps saying she will leave" também serve para a Shelly, que de fato saiu.

O caderno da Shelly (três páginas) está em [`diario_looker/shelly/`](diario_looker/shelly/1_comeco.md) e cita o `File L-490` como "see also".

### Diálogo genérico

✅ **Implementado em 31/10/2026:** `Nexus_Text_Shelly_Intro` / `_Defeat` em `data/scripts/nexus.inc`.

**Antes da luta**

> Ahahahaha! Look at that confidence!
>
> I used to wear a uniform, you know. Stripes, a bandana, the whole act.
>
> I left it folded on a boat seat somewhere. I don't miss it. ...Much.
>
> Now then. Let's see what you're made of, child!

**Derrota**

> Ahahaha... Well. That stung.
>
> Fine. I've lost bigger things than a battle.

### Diálogo associado ao lendário

📝 **Proposta de 30/09/2026, aguardando o autor.** Quando a Shelly é a **campeã**, a luta logo antes do lendário. A fala é sobre a criatura, sem dizer o nome dela ([R16](../NEXUS_REGRAS.md)).

#### Manaphy

O bebê abriu os olhos nas mãos de uma admin da Aqua e decidiu que ela era a mãe. A Shelly, que planejava afogar o mundo, acha isso a coisa mais engraçada que já aconteceu — e fica. A criatura sempre nada de volta para onde nasceu, e ela nasceu *nas mãos dela*: a porta que ela guarda é o caminho de volta.

**Antes da luta**

> Don't step any closer to that door, child.
>
> What's behind it hatched in my hands. The first face it ever saw was mine.
>
> It thinks I'm its mother. Ahahaha! Me! Of all people!
>
> So I'm going to act like one.

**Derrota**

> …Ahahaha. Of course. It's already swimming toward you.

**Depois da luta**

> Listen. It always swims back to where it was born.
>
> It was born in my hands. So wherever it goes, it comes back to me.
>
> Whatever you take home today will be looking for its way back, too.
>
> Let it look. That's how you'll know you did right by it.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Shelly_ChampionIntro:
	.string "Don't step any closer to that door,\n"
	.string "child.\p"
	.string "What's behind it hatched in my hands.\n"
	.string "The first face it ever saw was mine.\p"
	.string "It thinks I'm its mother. Ahahaha! Me!\n"
	.string "Of all people!\p"
	.string "So I'm going to act like one.$"

Nexus_Text_Shelly_ChampionDefeat:
	.string "…Ahahaha. Of course. It's already\n"
	.string "swimming toward you.$"

Nexus_Text_Shelly_ChampionAfter:
	.string "{SPEAKER NAME_SHELLY}Listen. It always swims back to where\n"
	.string "it was born.\p"
	.string "It was born in my hands. So wherever it\n"
	.string "goes, it comes back to me.\p"
	.string "Whatever you take home today will be\n"
	.string "looking for its way back, too.\p"
	.string "Let it look. That's how you'll know you\n"
	.string "did right by it.$"
```

</details>

Falante novo: `SP_NAME_SHELLY` (ainda não existe em `include/constants/speaker_names.h`).

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

**Variação 2** — o Heart Swap: um minuto dentro de quem ela seguia.

**Antes da luta**

> It can touch two hearts and swap them. Did you know that?
>
> It did it to me once. For one minute, I was inside someone I used to follow.
>
> It was cold in there, child. Cold, and very quiet.
>
> I don't ever want to be anyone else again. Ahahaha! So let's go!

**Derrota**

> Ahahaha… Yours is a warm one. I could tell before the first move.

**Depois da luta**

> That one minute taught me more than all of my charts.
>
> I came back to myself and left before morning.
>
> I took a boat, one small blue stranger, and nothing else.
>
> Go on in. And keep your own heart, child. It's a good one.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Shelly_ChampionIntro2:
	.string "It can touch two hearts and swap them.\n"
	.string "Did you know that?\p"
	.string "It did it to me once. For one minute, I\n"
	.string "was inside someone I used to follow.\p"
	.string "It was cold in there, child. Cold, and\n"
	.string "very quiet.\p"
	.string "I don't ever want to be anyone else\n"
	.string "again. Ahahaha! So let's go!$"

Nexus_Text_Shelly_ChampionDefeat2:
	.string "Ahahaha… Yours is a warm one. I could\n"
	.string "tell before the first move.$"

Nexus_Text_Shelly_ChampionAfter2:
	.string "{SPEAKER NAME_SHELLY}That one minute taught me more than\n"
	.string "all of my charts.\p"
	.string "I came back to myself and left before\n"
	.string "morning.\p"
	.string "I took a boat, one small blue stranger,\n"
	.string "and nothing else.\p"
	.string "Go on in. And keep your own heart,\n"
	.string "child. It's a good one.$"
```

</details>

**Variação 3** — humor: de planejar o dilúvio a planejar mamadeira.

**Antes da luta**

> I used to plan how to flood the world. Now I plan feeding times.
>
> It likes warm water, bad jokes, and me. In that order, some days.
>
> You want to meet it? Then you go through its mother first. Ahahahaha!

**Derrota**

> Ahahaha… Fine. You win. I hate that you win.

**Depois da luta**

> It won't look like much when you take it home. Pale. Tiny. Ridiculous.
>
> Don't let that fool you. It knows exactly where it came from.
>
> Some night it'll float up to your window and just stare at the sea.
>
> When it does, tell it its mother says hi. …Well? Go on, then!

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Shelly_ChampionIntro3:
	.string "I used to plan how to flood the world.\n"
	.string "Now I plan feeding times.\p"
	.string "It likes warm water, bad jokes, and me.\n"
	.string "In that order, some days.\p"
	.string "You want to meet it? Then you go\n"
	.string "through its mother first. Ahahahaha!$"

Nexus_Text_Shelly_ChampionDefeat3:
	.string "Ahahaha… Fine. You win. I hate that you\n"
	.string "win.$"

Nexus_Text_Shelly_ChampionAfter3:
	.string "{SPEAKER NAME_SHELLY}It won't look like much when you take\n"
	.string "it home. Pale. Tiny. Ridiculous.\p"
	.string "Don't let that fool you. It knows\n"
	.string "exactly where it came from.\p"
	.string "Some night it'll float up to your\n"
	.string "window and just stare at the sea.\p"
	.string "When it does, tell it its mother says hi.\n"
	.string "…Well? Go on, then!$"
```

</details>
