# Alder

**Região da ficha:** Unova

Aparece no checklist como:

- **Alder — Campeão** (Unova · Elite Four e Campeões) — viajante experiente que ensina sobre os vínculos com Pokémon.

**Pronto para o Nexus:** ✅ sim — no pool desde 31/10/2026 (lote novo, bloco 2 de IDs).

**Arte disponível:** ✅ overworld e front pic em `.filetransfer/.trainers/Alder/` (o overworld já está registrado no código; a front pic ainda não).

## Checklist

- [x] Sprite de overworld *(obrigatório)* — `OBJ_EVENT_GFX_ALDER` (registrado no merge de 30/09/2026)
- [x] Battle sprite / front pic *(obrigatório)* — arte em `.filetransfer/.trainers/Alder/`, falta registrar
- [ ] Field mugshot (retrato na caixa de diálogo)
- [x] Time para as Rift Missions definido — 📝 proposta nesta ficha (30/09/2026), fora do código
- [x] Associado a um lendário — 📝 proposta nesta ficha (Slither Wing), fora do código
- [x] Diálogo genérico escrito — 📝 proposta nesta ficha (3 variações), fora do código
- [x] Diálogo associado ao lendário escrito — 📝 proposta nesta ficha (3 variações), fora do código

## Referências no repositório

### Sprite de overworld

| Constante | Arquivo | Tamanho |
|---|---|---|
| `OBJ_EVENT_GFX_ALDER` | `graphics/object_events/pics/people/special/alder.png` | 16x32 |

Registrado no merge de 30/09/2026 (`include/constants/event_objects.h`, paleta própria `OBJ_EVENT_PAL_TAG_ALDER`). A arte original está em `.filetransfer/.trainers/Alder/Sprite - aveontrainer.png` (autor: aveontrainer), com `Sprite - comparacao no jogo.png` ao lado.

### Battle sprite (front pic)

**Não está no código.** A arte está em `.filetransfer/.trainers/Alder/`:

- `Trainer - desconhecido.png` — 80x80, autor desconhecido (o nome do arquivo diz "desconhecido")
- `Trainer - comparacao no jogo.png` — comparação no jogo

Falta converter para 64x64 e registrar (skills `converter-sprite` e `adicionar-grafico-trainer`). Até lá o bloco do `.party` usa uma pic provisória.

### Field mugshot

Não existe. Nada parecido na pasta dele. Opcional; criar com a skill `adicionar-grafico-trainer`.

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

Nenhuma. Ao criar, seguir a skill `adicionar-batalha-npc` (e `alocar-flag` se precisar de flag nova).

### Time das Rift Missions

✅ **Implementado em 31/10/2026** (lote novo, time montado pelo Codex e conferido pelo `novos/integrar.py`: R10–R13 e habilidades): `TRAINER_NEXUS_ALDER` = **1166** (bloco 2, flag `0xB02`), luta genérica `Nexus_EventScript_Alder_Fight` em `data/scripts/nexus.inc`, linha em `src/data/nexus/trainers.h`. Ainda não é campeão de nenhum lendário.

```
=== TRAINER_NEXUS_ALDER ===
Name: Alder
Class: Champion
Pic: Alder
Gender: Male
Music: Male
Double Battle: No
AI: Smart Trainer

Groudon @ Leftovers
Adamant Nature
Level: 100
Ability: Drought
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Precipice Blades
- Heat Crash
- Stealth Rock
- Protect

Slither Wing @ Choice Band
Adamant Nature
Level: 100
Ability: Protosynthesis
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- First Impression
- Close Combat
- Flare Blitz
- U-turn

Scolipede @ Poisontite
Jolly Nature
Level: 100
Ability: Speed Boost
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Megahorn
- Poison Jab
- Protect
- Swords Dance

Volcarona @ Heavy-Duty Boots
Timid Nature
Level: 100
Ability: Flame Body
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Quiver Dance
- Fiery Dance
- Giga Drain
- Rage Powder

Bouffalant @ Assault Vest
Adamant Nature
Level: 100
Ability: Sap Sipper
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Head Charge
- Rock Slide
- Megahorn
- Iron Head

Druddigon @ Rocky Helmet
Adamant Nature
Level: 100
Ability: Rough Skin
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Dragon Claw
- Dragon Tail
- Sucker Punch
- Glare
```

### Lendário associado

✅ **Campeão extra desde 31/10/2026** (lendário com vários campeões; o do dia é sorteado, `src/data/nexus/champions.h`; associações e falas montadas pelo Codex):

- **Slither Wing** — `Nexus_EventScript_Alder_SlitherWing_ChampionFight` (falas `Nexus_Text_Alder_SlitherWing_Champion*`)
- **Groudon** — `Nexus_EventScript_Alder_Groudon_ChampionFight` (falas `Nexus_Text_Alder_Groudon_Champion*`)
- **Ho Oh** — `Nexus_EventScript_Alder_HoOh_ChampionFight` (falas `Nexus_Text_Alder_HoOh_Champion*`)


#### Slither Wing

📝 **Proposta de 30/09/2026, aguardando o autor.** **Slither Wing**. O Alder é o campeão dele: a quinta luta do Daily, logo antes da boss battle. **Quem cede:** o Bugsy (tabela "Campeões novos" em [`DIARIO_LOOKER.md`](../DIARIO_LOOKER.md)), que fica com o Iron Moth. Enquanto o autor não aprova, a ficha do Bugsy e o código continuam como estão. O Slither Wing tem método fora do Nexus (selvagem em `MeteorCave1`, [`POOL_LENDARIOS.md`](../POOL_LENDARIOS.md)): pelo [R1](../NEXUS_REGRAS.md), só aparece depois de capturado — e o Alder, como campeão, só nesses dias.

**Quem é.** Alder, o Campeão de Unova em *Black/White*, que quase nunca está na Liga: vive viajando, falando com as pessoas. Perdeu o primeiro parceiro (a espécie nunca é dita) e passou anos vagando de luto. O N o derrota antes da heroína chegar; em *Black 2/White 2* a campeã é a Iris, e ele mora em Floccesy.

**A criatura.** Slither Wing (Inseto/Lutador), o Paradoxo antigo da Volcarona, vindo do passado pela Area Zero de *Scarlet/Violet*. Asas grandes demais para voar; anda com elas dobradas, e as escamas que caem estão pegando fogo. A lenda da Volcarona é a do sol substituto: quando as cinzas taparam o céu, o fogo dela salvou os Pokémon do frio.

**O fragmento.** A floresta de samambaias quente e úmida, cheia de pegadas pesadas (o que o jogo já tem). No fragmento do Alder, é a cratera onde o passado volta: ele foi até lá para rever o primeiro parceiro, ficou um dia inteiro diante da máquina e não apertou o botão.

**Falas do fragmento e ficha do Looker:** **já estão no jogo** — não reescrevi. Aponto as que existem em `data/scripts/nexus.inc`:

| Fala | Label | Onde |
|---|---|---|
| Chegada | `Nexus_Text_SlitherWing_Arrival` | `data/scripts/nexus.inc` |
| Boss | `Nexus_Text_SlitherWing_Boss` | `data/scripts/nexus.inc` |
| Ficha do Looker (**File L-988. Grounded Sun.**) | `Nexus_Text_SlitherWing_LookerFile` (script `Nexus_EventScript_SlitherWing_LookerFile`) | `data/scripts/nexus.inc` |

⚠️ O texto do Looker File que está no jogo foi escrito para o campeão atual (Bugsy): "a boy with a notebook who filled every page of it". Se a troca for aprovada, a linha do Looker File que descreve a pessoa deixa de bater com o campeão — decisão do autor (trocar só essa frase, ou manter como está, já que o Looker File descreve o universo e não precisa bater). Não reescrevi.

### Diálogo genérico

✅ **Implementado em 31/10/2026:** `Nexus_Text_Alder_Intro` / `_Defeat` em `data/scripts/nexus.inc`.

**Antes da luta**

> Ha ha! Another traveler! Sit, sit... No? Battle first? Just like the young ones!
>
> Very well! Show me how you and your Pokemon get along!

**Derrota**

> Ha! Wonderful! That's a team that eats dinner together.

### Diálogo associado ao lendário

📝 **Proposta de 30/09/2026, aguardando o autor.** Quando Alder é o **campeão**, a luta logo antes do lendário. A fala é sobre a criatura, sem dizer o nome dela ([R16](../NEXUS_REGRAS.md)).

#### Slither Wing

A fala do Bugsy (a variação 1 de hoje) já usa "asas daquele tamanho, e ele anda". Para não repetir, o Alder vê a criatura pelo **luto** e pelo **sol**: o sol que ainda está no chão (ele também ficou no chão depois do primeiro parceiro), as escamas que caem acesas e fazem crescer samambaias (a perda que vira semente) e o bicho velho que nunca se atrasou porque nunca aceitou horário (com humor).

##### Variação 1 — o sol no chão

**Antes da luta**

> Long ago, when ash hid the sun, a burning moth was the only light left. People prayed to it.
>
> That one is older still. From before its kind learned to rise. Its sun is still on the ground.
>
> Ha! Let's warm up, then!

**Derrota**

> Ha ha! You burned brighter!

**Depois da luta**

> When my first partner passed, I stayed on the ground too. For years.
>
> I thought I'd lost my wings. But look at it. It never flew, and it still carried the sun.
>
> You don't need to fly to keep someone warm. Go on, young one!

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Alder_ChampionIntro:
	.string "Long ago, when ash hid the sun, a\n"
	.string "burning moth was the only light left.\l"
	.string "People prayed to it.\p"
	.string "That one is older still. From before its\n"
	.string "kind learned to rise. Its sun is still on\l"
	.string "the ground.\p"
	.string "Ha! Let's warm up, then!$"

Nexus_Text_Alder_ChampionDefeat:
	.string "Ha ha! You burned brighter!$"

Nexus_Text_Alder_ChampionAfter:
	.string "{SPEAKER NAME_ALDER}When my first partner passed, I stayed\n"
	.string "on the ground too. For years.\p"
	.string "I thought I'd lost my wings. But look\n"
	.string "at it. It never flew, and it still carried\l"
	.string "the sun.\p"
	.string "You don't need to fly to keep someone\n"
	.string "warm. Go on, young one!$"
```

</details>

##### Variação 2 — as escamas acesas

**Antes da luta**

> Its scales fall off burning, and it keeps walking. It leaves a trail of little fires.
>
> I've left a trail, too. Friends in every town. Some of them I'll never see again.
>
> Let's add you to the trail! Battle!

**Derrota**

> A good fire. I'll remember it.

**Depois da luta**

> Every scale it drops starts something small. A fern grows there by next season.
>
> I used to think a loss was only a loss. It isn't. It's a scale. Something grows there.
>
> Heh. Listen to me. Go on, before I get sentimental.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Alder_ChampionIntro2:
	.string "Its scales fall off burning, and it\n"
	.string "keeps walking. It leaves a trail of\l"
	.string "little fires.\p"
	.string "I've left a trail, too. Friends in every\n"
	.string "town. Some of them I'll never see again.\p"
	.string "Let's add you to the trail! Battle!$"

Nexus_Text_Alder_ChampionDefeat2:
	.string "A good fire. I'll remember it.$"

Nexus_Text_Alder_ChampionAfter2:
	.string "{SPEAKER NAME_ALDER}Every scale it drops starts something\n"
	.string "small. A fern grows there by next\l"
	.string "season.\p"
	.string "I used to think a loss was only a loss.\n"
	.string "It isn't. It's a scale. Something grows\l"
	.string "there.\p"
	.string "Heh. Listen to me. Go on, before I get\n"
	.string "sentimental.$"
```

</details>

##### Variação 3 — ninguém apressa um velho

**Antes da luta**

> I've met a lot of old things. That one is older than me, and it has better posture!
>
> It never hurries. It's never been late for anything, because it never agreed to a schedule.
>
> My kind of creature. Battle!

**Derrota**

> Ha! Late again, and happy about it.

**Depois da luta**

> The young ones ask me what a Champion's job is.
>
> I tell them: walk. Meet people. Remember them. Come back when you're needed.
>
> It's been walking since before there were people, waiting to be needed. Let's not keep it waiting. Go!

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Alder_ChampionIntro3:
	.string "I've met a lot of old things. That one\n"
	.string "is older than me, and it has better\l"
	.string "posture!\p"
	.string "It never hurries. It's never been late\n"
	.string "for anything, because it never agreed\l"
	.string "to a schedule.\p"
	.string "My kind of creature. Battle!$"

Nexus_Text_Alder_ChampionDefeat3:
	.string "Ha! Late again, and happy about it.$"

Nexus_Text_Alder_ChampionAfter3:
	.string "{SPEAKER NAME_ALDER}The young ones ask me what a\n"
	.string "Champion's job is.\p"
	.string "I tell them: walk. Meet people. Remember\n"
	.string "them. Come back when you're needed.\p"
	.string "It's been walking since before there\n"
	.string "were people, waiting to be needed.\l"
	.string "Let's not keep it waiting. Go!$"
```

</details>

Falante novo: `SP_NAME_ALDER` (ainda não existe em `include/constants/speaker_names.h`; a plaquinha usa `NAME_ALDER`).

### Diário do Looker

📝 **Proposta de 30/09/2026, aguardando o autor.** Três páginas em [`diario_looker/alder/`](diario_looker/alder/) — formato e fios em [`DIARIO_LOOKER.md`](../DIARIO_LOOKER.md).

- [1_comeco.md](diario_looker/alder/1_comeco.md) — começo: a floresta de samambaias; o velho que viu o dragão negro e o branco saírem da Liga; a Poké Ball vazia
- [2_meio.md](diario_looker/alder/2_meio.md) — meio: o primeiro parceiro; a cratera onde o passado volta; o botão que ele não apertou
- [3_fim.md](diario_looker/alder/3_fim.md) — fim: o velho levanta acampamento; as duas luzes no horizonte; a bola vazia deixada numa pedra
