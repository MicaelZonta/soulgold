# Cheren

**Região da ficha:** Unova

Aparece no checklist como:

- **Cheren** (Unova · Rivais) — rival estudioso que busca força e posteriormente vira Líder de Ginásio.
- **Cheren — Normal** (Unova · Líderes de Ginásio) — novo Líder de Aspertia em *Black 2/White 2*.

**Pronto para o Nexus:** ❌ não — tem sprite de overworld, falta o battle sprite (front pic), obrigatório.

**Arte disponível:** ✅ overworld e front pic em `.filetransfer/.trainers/Cheren/` (o overworld já está registrado no código; a front pic ainda não).

## Checklist

- [x] Sprite de overworld *(obrigatório)* — `OBJ_EVENT_GFX_CHEREN` (registrado no merge de 30/09/2026)
- [ ] Battle sprite / front pic *(obrigatório)* — arte em `.filetransfer/.trainers/Cheren/`, falta registrar
- [ ] Field mugshot (retrato na caixa de diálogo)
- [ ] Time para as Rift Missions definido — 📝 proposta nesta ficha (30/09/2026), fora do código
- [ ] Associado a um lendário — 📝 proposta nesta ficha (Cobalion), fora do código
- [ ] Diálogo genérico escrito — 📝 proposta nesta ficha (3 variações), fora do código
- [ ] Diálogo associado ao lendário escrito — 📝 proposta nesta ficha (3 variações), fora do código

## Referências no repositório

### Sprite de overworld

| Constante | Arquivo | Tamanho |
|---|---|---|
| `OBJ_EVENT_GFX_CHEREN` | `graphics/object_events/pics/people/special/cheren.png` | 16x32 |

Registrado no merge de 30/09/2026 (`include/constants/event_objects.h`, paleta própria `OBJ_EVENT_PAL_TAG_CHEREN`). A arte original está em `.filetransfer/.trainers/Cheren/Sprite - aveontrainer.png` (autor: aveontrainer), com `Sprite - comparacao no jogo.png` ao lado.

### Battle sprite (front pic)

**Não está no código.** A arte está em `.filetransfer/.trainers/Cheren/`:

- `Trainer - desconhecido.png` — 80x80, autor desconhecido (o nome do arquivo diz "desconhecido")
- `Trainer - comparacao no jogo.png` — comparação no jogo

Falta converter para 64x64 e registrar (skills `converter-sprite` e `adicionar-grafico-trainer`). Até lá o bloco do `.party` usa uma pic provisória.

### Field mugshot

Não existe. Nada parecido na pasta dele. Opcional; criar com a skill `adicionar-grafico-trainer`.

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

Nenhuma. Ao criar, seguir a skill `adicionar-batalha-npc` (e `alocar-flag` se precisar de flag nova).

### Time das Rift Missions

📝 **Proposta de 30/09/2026, aguardando o autor.** `TRAINER_NEXUS_CHEREN`, campeão do Cobalion. ID: **a alocar** (IDs livres abaixo de 1056; não usar 1056–1163). Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega; 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler). **Pic provisória** (`Cooltrainer M`) até registrar a arte.

O Cobalion é **semi-lendário** (`isSubLegendary`), então ocupa a vaga de semi-lendário, não a de lendário. Lendário **Kyurem**, o terceiro dragão, o que ninguém levou: no fragmento dele, o dragão do Giant Chasm recusou o Cheren e depois passou a voltar para perto dele mesmo assim (diário, páginas 2 e 3). O Kyurem vai na forma base (sem DNA Splicers). Semi-lendário **Cobalion**, o líder dos Swords of Justice, que ficou do lado dele na frente dos alunos. Mega **Kangaskhan** (Normalite, Parental Bond): o Líder de Ginásio de tipo Normal de *Black 2/White 2*, e a força que carrega uma criança — é o professor. Mais o **Samurott** (o inicial que ele escolhe quando a heroína pega o Tepig), o **Liepard** do time de rival e o **Stoutland** do Ginásio de Aspertia.

*Plano (Singles):* metódico. O Liepard (Prankster) entra de Fake Out, Encore e Thunder Wave: tranca o adversário no golpe errado. A Mega Kangaskhan bate duas vezes com Fake Out, Double-Edge e Drain Punch; o Cobalion (Justified) sobe Swords Dance quando o adversário tenta Dark; o Kyurem limpa com Freeze-Dry, Ice Beam e Earth Power; o Samurott fecha com Aqua Jet.

*Plano (Doubles):* Fake Out duplo (Liepard + Kangaskhan) no turno 1, Intimidate do Stoutland, e o Cobalion atrás. Nenhum golpe do time acerta o parceiro.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Kyurem | Life Orb | Pressure | Modest | Ice Beam, Draco Meteor, Earth Power, Freeze-Dry |
| Cobalion | Chople Berry | Justified | Jolly | Iron Head, Close Combat, Swords Dance, Stone Edge |
| Kangaskhan | Normalite | Scrappy | Adamant | Fake Out, Double-Edge, Sucker Punch, Drain Punch |
| Samurott | Sitrus Berry | Torrent | Adamant | Razor Shell, Aqua Jet, Megahorn, Swords Dance |
| Liepard | Focus Sash | Prankster | Timid | Fake Out, Encore, Thunder Wave, Foul Play |
| Stoutland | Leftovers | Intimidate | Adamant | Return, Crunch, Wild Charge, Protect |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>dev_scripts/nexus_validar_time.py</code>: trainerproc, constantes, learnsets e categorias)</summary>

```
=== TRAINER_NEXUS_CHEREN ===
Name: Cheren
Class: Leader
Pic: Cooltrainer M
Gender: Male
Music: Male
Double Battle: No
AI: Smart Trainer

Kyurem @ Life Orb
Modest Nature
Level: 100
Ability: Pressure
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Ice Beam
- Draco Meteor
- Earth Power
- Freeze-Dry

Cobalion @ Chople Berry
Jolly Nature
Level: 100
Ability: Justified
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Iron Head
- Close Combat
- Swords Dance
- Stone Edge

Kangaskhan @ Normalite
Adamant Nature
Level: 100
Ability: Scrappy
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Fake Out
- Double-Edge
- Sucker Punch
- Drain Punch

Samurott @ Sitrus Berry
Adamant Nature
Level: 100
Ability: Torrent
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Razor Shell
- Aqua Jet
- Megahorn
- Swords Dance

Liepard @ Focus Sash
Timid Nature
Level: 100
Ability: Prankster
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Fake Out
- Encore
- Thunder Wave
- Foul Play

Stoutland @ Leftovers
Adamant Nature
Level: 100
Ability: Intimidate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Return
- Crunch
- Wild Charge
- Protect
```

</details>

### Lendário associado

#### Cobalion

📝 **Proposta de 30/09/2026, aguardando o autor.** **Cobalion**. O Cheren é o campeão dele: a quinta luta do Daily, logo antes da boss battle. **Quem cede:** o Chuck (tabela "Campeões novos" em [`DIARIO_LOOKER.md`](../DIARIO_LOOKER.md)), que fica com o Urshifu. Enquanto o autor não aprova, a ficha do Chuck e o código continuam como estão.

**Quem é.** Cheren, de Nuvema Town, o amigo de infância estudioso da heroína. Em *Black/White* é o rival que pergunta a todos "o que é ser forte?" (o Alder conversa com ele sobre isso); em *Black 2/White 2* é Líder de Ginásio de tipo Normal em Aspertia e professor da escola da cidade. Nunca foi escolhido por dragão nenhum.

**A criatura.** Cobalion (Aço/Lutador), o líder dos Swords of Justice. Há muito tempo, humanos queimaram uma floresta numa guerra; o Cobalion, o Terrakion e o Virizion protegeram os Pokémon **contra** as pessoas. Tem o coração e o corpo de aço, e convence os outros só com a firmeza.

**O fragmento.** O campo de espadas enferrujadas com Pokémon pequenos escondidos entre elas (o que o jogo já tem). No fragmento do Cheren, a guerra é pequena: homens de uniforme cinza na porta de uma escola, e crianças atrás de um professor que não tinha nada pronto.

**Falas do fragmento e ficha do Looker:** **já estão no jogo** — não reescrevi. Aponto as que existem em `data/scripts/nexus.inc`:

| Fala | Label | Onde |
|---|---|---|
| Chegada | `Nexus_Text_Cobalion_Arrival` | `data/scripts/nexus.inc` |
| Boss | `Nexus_Text_Cobalion_Boss` | `data/scripts/nexus.inc` |
| Ficha do Looker (**File L-638. Iron Will.**) | `Nexus_Text_Cobalion_LookerFile` (script `Nexus_EventScript_Cobalion_LookerFile`) | `data/scripts/nexus.inc` |

⚠️ O texto do Looker File que está no jogo foi escrito para o campeão atual (Chuck): "a man who hits things for a living, learning that a fist can also be a shield". Se a troca for aprovada, a linha do Looker File que descreve a pessoa deixa de bater com o campeão — decisão do autor (trocar só essa frase, ou manter como está, já que o Looker File descreve o universo e não precisa bater). Não reescrevi.

### Diálogo genérico

📝 **Proposta de 30/09/2026, aguardando o autor.** Quando Cheren cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala de si, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)). Ainda não há nada no `nexus.inc`: as três variações são novas.

O Cheren é lógico, sério, empurra os óculos e hoje é professor. As três variações: a pergunta que ele faz a toda turma ("what is strength for?"), o planejamento excessivo (com a Bianca, sem nome, puxando a orelha dele) e a carteira vazia na primeira fila.

#### Variação 1 — a pergunta do primeiro dia

**Antes da luta**

> On the first day, I ask every student the same question: what is strength for?
>
> No one has given me the right answer yet. Including me. Let's see if you can.

**Derrota**

> That was an answer. I'll need to write it down.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Cheren_Intro:
	.string "On the first day, I ask every student\n"
	.string "the same question: what is strength\l"
	.string "for?\p"
	.string "No one has given me the right answer\n"
	.string "yet. Including me. Let's see if you can.$"

Nexus_Text_Cheren_Defeat:
	.string "That was an answer. I'll need to write\n"
	.string "it down.$"
```

</details>

#### Variação 2 — o plano

**Antes da luta**

> I planned this battle. Three turns ahead, five alternatives each.
>
> A friend once told me plans are just nerves wearing a nice outfit. …She was right. Annoyingly.
>
> Begin!

**Derrota**

> Six alternatives. I needed six.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Cheren_Intro2:
	.string "I planned this battle. Three turns\n"
	.string "ahead, five alternatives each.\p"
	.string "A friend once told me plans are just\n"
	.string "nerves wearing a nice outfit. …She was\l"
	.string "right. Annoyingly.\p"
	.string "Begin!$"

Nexus_Text_Cheren_Defeat2:
	.string "Six alternatives. I needed six.$"
```

</details>

#### Variação 3 — a carteira vazia

**Antes da luta**

> There's an empty desk in the front row of my classroom. I keep it for someone who went away.
>
> The students think it's for the best student who will ever come. I let them.
>
> Show me if it's you!

**Derrota**

> Not the desk's owner. But close.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Cheren_Intro3:
	.string "There's an empty desk in the front row\n"
	.string "of my classroom. I keep it for someone\l"
	.string "who went away.\p"
	.string "The students think it's for the best\n"
	.string "student who will ever come. I let them.\p"
	.string "Show me if it's you!$"

Nexus_Text_Cheren_Defeat3:
	.string "Not the desk's owner. But close.$"
```

</details>

### Diálogo associado ao lendário

📝 **Proposta de 30/09/2026, aguardando o autor.** Quando Cheren é o **campeão**, a luta logo antes do lendário. A fala é sobre a criatura, sem dizer o nome dela ([R16](../NEXUS_REGRAS.md)).

#### Cobalion

A fala do Chuck (a variação 1 de hoje) já usa "ficar na frente dos pequenos sem se mexer". Para não repetir, o Cheren olha a criatura por outros ângulos: a **justiça contra as pessoas** (a lenda da floresta queimada, que ele não sabe explicar aos alunos), o **coração de aço** que não dobra (ele dobra, reescreve tudo três vezes), e **não ser escolhido** (os amigos tiveram dragões; ele só teve alguém ao lado).

##### Variação 1 — justiça contra nós

**Antes da luta**

> Long ago, people burned a forest in a war. Three of them stood against the people. That one led.
>
> Justice, standing against us. I teach children, and I never knew how to explain that.
>
> Maybe a battle explains it better. Let's go!

**Derrota**

> You explained it. Without a single word.

**Depois da luta**

> It looked at me the way I look at a student who hasn't done the reading.
>
> Not angry. Just waiting.
>
> I've waited years to learn what strength is for. It already knows. It just won't say. Go on.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Cheren_ChampionIntro:
	.string "Long ago, people burned a forest in a\n"
	.string "war. Three of them stood against the\l"
	.string "people. That one led.\p"
	.string "Justice, standing against us. I teach\n"
	.string "children, and I never knew how to\l"
	.string "explain that.\p"
	.string "Maybe a battle explains it better.\n"
	.string "Let's go!$"

Nexus_Text_Cheren_ChampionDefeat:
	.string "You explained it. Without a single word.$"

Nexus_Text_Cheren_ChampionAfter:
	.string "{SPEAKER NAME_CHEREN}It looked at me the way I look at a\n"
	.string "student who hasn't done the reading.\p"
	.string "Not angry. Just waiting.\p"
	.string "I've waited years to learn what\n"
	.string "strength is for. It already knows. It\l"
	.string "just won't say. Go on.$"
```

</details>

##### Variação 2 — o coração que não dobra

**Antes da luta**

> They say its heart is steel. It persuades others just by refusing to bend.
>
> I bend. I reconsider. I rewrite every lesson plan three times.
>
> Maybe that's a weakness. Let's test it!

**Derrota**

> Bent. Not broken, though.

**Depois da luta**

> While I talked, a small Pokémon hid behind its leg. It never once looked down.
>
> It didn't need to check. It knew the small one was there.
>
> I check on my students constantly. …Perhaps that's fine. Steel isn't the only kind of heart. Go.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Cheren_ChampionIntro2:
	.string "They say its heart is steel. It\n"
	.string "persuades others just by refusing to\l"
	.string "bend.\p"
	.string "I bend. I reconsider. I rewrite every\n"
	.string "lesson plan three times.\p"
	.string "Maybe that's a weakness. Let's test\n"
	.string "it!$"

Nexus_Text_Cheren_ChampionDefeat2:
	.string "Bent. Not broken, though.$"

Nexus_Text_Cheren_ChampionAfter2:
	.string "{SPEAKER NAME_CHEREN}While I talked, a small Pokémon hid\n"
	.string "behind its leg. It never once looked\l"
	.string "down.\p"
	.string "It didn't need to check. It knew the\n"
	.string "small one was there.\p"
	.string "I check on my students constantly.\n"
	.string "…Perhaps that's fine. Steel isn't the\l"
	.string "only kind of heart. Go.$"
```

</details>

##### Variação 3 — ninguém escolheu

**Antes da luta**

> Everyone I grew up with was chosen by something. A white dragon. A black one.
>
> Nothing chose me. So I went looking, and that one let me walk beside it. That's all.
>
> It's enough. Let me show you!

**Derrota**

> Beside, not ahead. I remember.

**Depois da luta**

> It never chose anyone either. It just stood where it was needed, and the others followed.
>
> I used to think being chosen was the point.
>
> Now I think the point is showing up. …I'm glad you showed up. Go.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Cheren_ChampionIntro3:
	.string "Everyone I grew up with was chosen by\n"
	.string "something. A white dragon. A black one.\p"
	.string "Nothing chose me. So I went looking,\n"
	.string "and that one let me walk beside it.\l"
	.string "That's all.\p"
	.string "It's enough. Let me show you!$"

Nexus_Text_Cheren_ChampionDefeat3:
	.string "Beside, not ahead. I remember.$"

Nexus_Text_Cheren_ChampionAfter3:
	.string "{SPEAKER NAME_CHEREN}It never chose anyone either. It just\n"
	.string "stood where it was needed, and the\l"
	.string "others followed.\p"
	.string "I used to think being chosen was the\n"
	.string "point.\p"
	.string "Now I think the point is showing up.\n"
	.string "…I'm glad you showed up. Go.$"
```

</details>

Falante novo: `SP_NAME_CHEREN` (ainda não existe em `include/constants/speaker_names.h`; a plaquinha usa `NAME_CHEREN`).

### Diário do Looker

📝 **Proposta de 30/09/2026, aguardando o autor.** Três páginas em [`diario_looker/cheren/`](diario_looker/cheren/) — formato e fios em [`DIARIO_LOOKER.md`](../DIARIO_LOOKER.md).

- [1_comeco.md](diario_looker/cheren/1_comeco.md) — começo: Aspertia: a escola e o Ginásio, a carteira vazia, o número que ele liga e desliga antes do sinal
- [2_meio.md](diario_looker/cheren/2_meio.md) — meio: o Giant Chasm e o dragão que olhou para outro lado; a criatura de aço na porta da escola
- [3_fim.md](diario_looker/cheren/3_fim.md) — fim: o cartão com nome virado para baixo; a mensagem gravada; "Strength is for showing up."
