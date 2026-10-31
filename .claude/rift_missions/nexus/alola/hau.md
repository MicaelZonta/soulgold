# Hau

**Região da ficha:** Alola

Aparece no checklist como:

- **Hau** (Alola · Rivais) — rival otimista e neto do Kahuna Hala.
- **Hau** (Alola · Elite Four e Campeões) — desafiante final da Liga em *Ultra Sun/Ultra Moon*.

**Pronto para o Nexus:** ✅ sim — no pool desde 31/10/2026 (lote novo, bloco 2 de IDs).

**Arte disponível:** ✅ overworld e front pic em `.filetransfer/.trainers/Hau/` (o overworld já registrado; a front pic, não).

## Checklist

- [x] Sprite de overworld *(obrigatório)* — `OBJ_EVENT_GFX_HAU`, 30/09/2026
- [x] Battle sprite / front pic *(obrigatório)* — arte disponível, falta registrar
- [ ] Field mugshot (retrato na caixa de diálogo)
- [x] Time para as Rift Missions definido — 📝 proposta abaixo (30/09/2026), fora do código
- [x] Associado a um lendário — 📝 proposta: Tapu Koko (cedido pelo Kukui)
- [x] Diálogo genérico escrito — 📝 proposta abaixo, 3 variações
- [x] Diálogo associado ao lendário escrito — 📝 proposta abaixo, 3 variações

## Referências no repositório

### Sprite de overworld

| Constante | Arquivo |
|---|---|
| `OBJ_EVENT_GFX_HAU` | `graphics/object_events/pics/people/special/hau.png` (16x32, 12 quadros, `sAnimTable_StandardAsym`; paleta própria `OBJ_EVENT_PAL_TAG_HAU`) — registrado em 30/09/2026 |

Fonte da arte em `.filetransfer/.trainers/Hau/`:

| Arquivo | O que é |
|---|---|
| `Sprite - Wergan.png` | overworld, autor **Wergan** (origem do `hau.png` acima) |
| `Sprite - comparacao no jogo.png` | comparação do overworld no jogo |
| `Trainer - Beliot419.png` | front pic, autor **Beliot419** — **ainda não registrada** |
| `Trainer - comparacao no jogo.png` | comparação da front pic no jogo |

### Battle sprite (front pic)

Não existe no código. A arte está em `.filetransfer/.trainers/Hau/Trainer - Beliot419.png`; falta converter e registrar (skills `converter-sprite` e `adicionar-grafico-trainer`).

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`). A pasta da arte não traz mugshot.

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

Nenhuma. Ao criar, seguir a skill `adicionar-batalha-npc` (e `alocar-flag` se precisar de flag nova).

### Time das Rift Missions

✅ **Implementado em 31/10/2026** (lote novo, time montado pelo Codex e conferido pelo `novos/integrar.py`: R10–R13 e habilidades): `TRAINER_NEXUS_HAU` = **1183** (bloco 2, flag `0xB13`), luta genérica `Nexus_EventScript_Hau_Fight` em `data/scripts/nexus.inc`, linha em `src/data/nexus/trainers.h`. Ainda não é campeão de nenhum lendário.

```
=== TRAINER_NEXUS_HAU ===
Name: Hau
Class: Rival
Pic: Hau
Gender: Male
Music: Male
Double Battle: No
AI: Smart Trainer

Solgaleo @ Weakness Policy
Adamant Nature
Level: 100
Ability: Full Metal Body
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Sunsteel Strike
- Psychic Fangs
- Flare Blitz
- Protect

Tapu Koko @ Life Orb
Timid Nature
Level: 100
Ability: Electric Surge
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Thunderbolt
- Dazzling Gleam
- Volt Switch
- Roost

Crabominable @ Icetite
Adamant Nature
Level: 100
Ability: Iron Fist
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Ice Hammer
- Drain Punch
- Thunder Punch
- Protect

Raichu-Alola @ Choice Specs
Timid Nature
Level: 100
Ability: Surge Surfer
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Thunderbolt
- Psychic
- Focus Blast
- Volt Switch

Tauros @ Choice Band
Jolly Nature
Level: 100
Ability: Intimidate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Double-Edge
- Close Combat
- Rock Slide
- Zen Headbutt

Decidueye @ Sitrus Berry
Adamant Nature
Level: 100
Ability: Long Reach
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Spirit Shackle
- Leaf Blade
- Knock Off
- Protect
```

### Lendário associado

✅ **Campeão extra desde 31/10/2026** (lendário com vários campeões; o do dia é sorteado, `src/data/nexus/champions.h`; associações e falas montadas pelo Codex):

- **Tapu Koko** — `Nexus_EventScript_Hau_TapuKoko_ChampionFight` (falas `Nexus_Text_Hau_TapuKoko_Champion*`)
- **Solgaleo** — `Nexus_EventScript_Hau_Solgaleo_ChampionFight` (falas `Nexus_Text_Hau_Solgaleo_Champion*`)
- **Tapu Lele** — `Nexus_EventScript_Hau_TapuLele_ChampionFight` (falas `Nexus_Text_Hau_TapuLele_Champion*`)


#### Tapu Koko

📝 **Proposta de 30/09/2026, aguardando o autor.** **Tapu Koko**, cedido pelo **Kukui** (que fica com o Solgaleo), pela tabela "Campeões novos" de [`DIARIO_LOOKER.md`](../DIARIO_LOOKER.md). Enquanto o autor não aprova, o código e a ficha do Kukui continuam como estão. Hau seria o campeão dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Hau, neto do Kahuna Hala de Melemele, rival do protagonista em Sun/Moon: alegre, comilão de malasada, e com o peso de ser "o neto do Kahuna". Em Ultra Sun/Ultra Moon é o primeiro desafiante do título de Campeão.

**A criatura.** Tapu Koko, o guardião de Melemele. Curioso, esquentado e volúvel: adora uma briga, some quando quer, e o festival de Iki Town é em honra dele. Em Sun/Moon é ele quem deixa cair a pedra brilhante que vira o Z-Ring do protagonista.

**O fragmento.** Já existe no jogo e **não é reescrito**: o estádio vazio sob nuvens de tempestade, com marcas de queimado em anéis, "como se alguém tivesse treinado ali por muito tempo". No fragmento do Hau, alguém treinou: ele, todo dia, contra o guardião.

- Chegada: `Nexus_Text_TapuKoko_Arrival` (`data/scripts/nexus.inc`)
- Boss: `Nexus_Text_TapuKoko_Boss`
- Ficha do Looker: `Nexus_EventScript_TapuKoko_LookerFile` → `Nexus_Text_TapuKoko_LookerFile` (**File L-785. Guardian of Melemele.**), ver a ficha do [Kukui](kukui.md#tapu-koko).

> ⚠️ O Looker File de hoje fala do campeão atual ("The professor knows the feeling"). Se a troca for aprovada, essa frase precisa de ajuste para o Hau — que conhece o sentimento melhor ainda.

O caderno do Hau (três páginas) está em [`diario_looker/hau/`](diario_looker/hau/1_comeco.md) e cita o `File L-785` como "see also".

### Diálogo genérico

✅ **Implementado em 31/10/2026:** `Nexus_Text_Hau_Intro` / `_Defeat` em `data/scripts/nexus.inc`.

**Antes da luta**

> Hey! Alola! Wanna battle? 'Course you do! Everybody does!
>
> I've got a malasada in my bag for after. Maybe even two, if you win.
>
> Let's make this one fun, yeah?

**Derrota**

> Ahaha! Aw man, that was awesome!
>
> Okay, okay. The malasada's yours. ...Half of it.

### Diálogo associado ao lendário

📝 **Proposta de 30/09/2026, aguardando o autor.** Quando o Hau é o **campeão**, a luta logo antes do lendário. A fala é sobre a criatura, sem dizer o nome dela ([R16](../NEXUS_REGRAS.md)).

#### Tapu Koko

No fragmento do Hau ninguém veio de fora, e a pedra brilhante caiu na frente dele. Ele fez tudo — provas, Kahunas, Liga — e virou Campeão sem ninguém para perseguir. O estádio ficou vazio, e o guardião, que ama uma briga, passou a descer todo dia com o trovão. O Hau nunca ganhou dele, e diz que é a melhor parte do dia.

**Antes da luta**

> You're going in there? Awesome! I get to go first, though!
>
> The guardian back home picks fights with anybody it likes. And it likes me way too much.
>
> It comes to my stadium every single day. We've been battling for years!

**Derrota**

> Ahaha! It's gonna love you. Like, a lot.

**Depois da luta**

> Where I'm from, I'm the Champion! Pretty cool, huh? Nobody else ever came to take it.
>
> So the stands are empty. Except for the guardian. It comes down with the thunder every afternoon.
>
> I've never beaten it. Not once. That's okay! It's the best part of my day.
>
> Go on! Tell it I'll be late tomorrow. …Just kidding. I'm never late.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Hau_ChampionIntro:
	.string "You're going in there? Awesome! I get\n"
	.string "to go first, though!\p"
	.string "The guardian back home picks fights\n"
	.string "with anybody it likes. And it likes me\l"
	.string "way too much.\p"
	.string "It comes to my stadium every single\n"
	.string "day. We've been battling for years!$"

Nexus_Text_Hau_ChampionDefeat:
	.string "Ahaha! It's gonna love you. Like, a lot.$"

Nexus_Text_Hau_ChampionAfter:
	.string "{SPEAKER NAME_HAU}Where I'm from, I'm the Champion!\n"
	.string "Pretty cool, huh? Nobody else ever\l"
	.string "came to take it.\p"
	.string "So the stands are empty. Except for\n"
	.string "the guardian. It comes down with the\l"
	.string "thunder every afternoon.\p"
	.string "I've never beaten it. Not once. That's\n"
	.string "okay! It's the best part of my day.\p"
	.string "Go on! Tell it I'll be late tomorrow.\n"
	.string "…Just kidding. I'm never late.$"
```

</details>

Falante novo: `SP_NAME_HAU` (ainda não existe em `include/constants/speaker_names.h`).

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

**Variação 2** — a pedra brilhante que caiu na frente dele, e não do "novo".

**Antes da luta**

> When I was little, the guardian dropped a sparkly stone right in front of me at the festival.
>
> Everybody said that meant I was chosen. Chosen for what, though?
>
> I'm still figuring it out! Maybe for this!

**Derrota**

> Ahaha! Maybe it should've dropped that stone in front of you instead.

**Depois da luta**

> I always thought I'd be the guy chasing somebody else. The rival, you know?
>
> Instead it chose me. Trials, Kahunas, the League, all of it. Nobody left to chase.
>
> It's fickle, that guardian. It gives you stuff, then just watches what you do with it.
>
> So show it what you'd do. It'd love that.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Hau_ChampionIntro2:
	.string "When I was little, the guardian dropped\n"
	.string "a sparkly stone right in front of me at\l"
	.string "the festival.\p"
	.string "Everybody said that meant I was\n"
	.string "chosen. Chosen for what, though?\p"
	.string "I'm still figuring it out! Maybe for\n"
	.string "this!$"

Nexus_Text_Hau_ChampionDefeat2:
	.string "Ahaha! Maybe it should've dropped\n"
	.string "that stone in front of you instead.$"

Nexus_Text_Hau_ChampionAfter2:
	.string "{SPEAKER NAME_HAU}I always thought I'd be the guy\n"
	.string "chasing somebody else. The rival, you\l"
	.string "know?\p"
	.string "Instead it chose me. Trials, Kahunas,\n"
	.string "the League, all of it. Nobody left to\l"
	.string "chase.\p"
	.string "It's fickle, that guardian. It gives\n"
	.string "you stuff, then just watches what you\l"
	.string "do with it.\p"
	.string "So show it what you'd do. It'd love\n"
	.string "that.$"
```

</details>

**Variação 3** — humor: a malasada roubada.

**Antes da luta**

> I tried feeding it a malasada once. Big Sweet, extra sugar.
>
> It zapped the malasada, zapped me, and then flew off with the whole bag.
>
> I'm still mad about that! Let's battle!

**Derrota**

> Aw man… Two losses in one day. I'm counting the malasada.

**Depois da luta**

> It's curious about everything. It'll poke at you, zap you a little, see what you do.
>
> If you laugh, it comes back. If you run, it gets bored.
>
> What goes home with you will be tiny, but it's gonna be curious about you forever.
>
> Laugh a lot, okay? Oh, and hide your snacks.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Hau_ChampionIntro3:
	.string "I tried feeding it a malasada once. Big\n"
	.string "Sweet, extra sugar.\p"
	.string "It zapped the malasada, zapped me, and\n"
	.string "then flew off with the whole bag.\p"
	.string "I'm still mad about that! Let's battle!$"

Nexus_Text_Hau_ChampionDefeat3:
	.string "Aw man… Two losses in one day. I'm\n"
	.string "counting the malasada.$"

Nexus_Text_Hau_ChampionAfter3:
	.string "{SPEAKER NAME_HAU}It's curious about everything. It'll\n"
	.string "poke at you, zap you a little, see what\l"
	.string "you do.\p"
	.string "If you laugh, it comes back. If you run,\n"
	.string "it gets bored.\p"
	.string "What goes home with you will be tiny,\n"
	.string "but it's gonna be curious about you\l"
	.string "forever.\p"
	.string "Laugh a lot, okay? Oh, and hide your\n"
	.string "snacks.$"
```

</details>
