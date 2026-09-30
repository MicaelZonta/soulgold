# Hilda

**Região da ficha:** Unova

Aparece no checklist como:

- **Hilda** (Unova · Outros notáveis) — protagonista feminina de *Black/White* ligada à derrota inicial do Team Plasma.

Ficha separada da do **Hilbert** desde 30/09/2026 (protagonista masculino da mesma dupla): ele não tem arte nenhuma ainda, então fica em [`hilbert.md`](hilbert.md), fora do Nexus.

**Pronto para o Nexus:** ❌ não — tem sprite de overworld, falta o battle sprite (front pic), obrigatório.

**Arte disponível:** ✅ overworld e front pic em `.filetransfer/.trainers/Hilda/` (o overworld já está registrado no código; a front pic ainda não).

## Checklist

- [x] Sprite de overworld *(obrigatório)* — `OBJ_EVENT_GFX_HILDA` (registrado no merge de 30/09/2026)
- [ ] Battle sprite / front pic *(obrigatório)* — arte em `.filetransfer/.trainers/Hilda/`, falta registrar
- [ ] Field mugshot (retrato na caixa de diálogo)
- [ ] Time para as Rift Missions definido — 📝 proposta nesta ficha (30/09/2026), fora do código
- [ ] Associado a um lendário — 📝 proposta nesta ficha (Reshiram), fora do código
- [ ] Diálogo genérico escrito — 📝 proposta nesta ficha (3 variações), fora do código
- [ ] Diálogo associado ao lendário escrito — 📝 proposta nesta ficha (3 variações), fora do código

## Referências no repositório

### Sprite de overworld

| Constante | Arquivo | Tamanho |
|---|---|---|
| `OBJ_EVENT_GFX_HILDA` | `graphics/object_events/pics/people/special/hilda.png` | 32x32 (boneco mais largo que 16 px) |

Registrado no merge de 30/09/2026 (`include/constants/event_objects.h`, paleta própria `OBJ_EVENT_PAL_TAG_HILDA`). A arte original está em `.filetransfer/.trainers/Hilda/Sprite - Redboy265.png` (autor: Redboy265), com `Sprite - comparacao no jogo.png` ao lado.

### Battle sprite (front pic)

**Não está no código.** A arte está em `.filetransfer/.trainers/Hilda/`:

- `Trainer - oficial BW (rip).png` — sprite oficial de *Black/White* (rip), 47x83, precisa recorte para 64x64
- `Trainer - comparacao no jogo.png` — comparação no jogo
- `outras/Folha BW completa - oficial (rip).jpg` — folha completa oficial de *Black/White*

Falta converter para 64x64 e registrar (skills `converter-sprite` e `adicionar-grafico-trainer`). Até lá o bloco do `.party` usa uma pic provisória.

### Field mugshot

Não existe. Nada parecido na pasta dela. Opcional; criar com a skill `adicionar-grafico-trainer`.

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

Nenhuma. Ao criar, seguir a skill `adicionar-batalha-npc` (e `alocar-flag` se precisar de flag nova).

### Time das Rift Missions

📝 **Proposta de 30/09/2026, aguardando o autor.** `TRAINER_NEXUS_HILDA`, campeã do Reshiram. ID: **a alocar** (IDs livres abaixo de 1056; não usar 1056–1163). Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega; 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler). **Pic provisória** (`Cooltrainer F`) até registrar a arte.

Lendário **Reshiram**, o dragão da verdade, o de *Pokémon Black* (em *Black* é a protagonista quem fica com ele, e o N com o Zekrom). Semi-lendário **Tornadus**, o gênio do vento que só aparece em *Black*: a Hilda corre, e ele empurra. Mega **Emboar** (Firetite, a pedra de tipo do hack; a Mega tem Mold Breaker): o Tepig dela, o inicial de fogo que combina com a chama branca. Mais **Excadrill** e **Galvantula**, da campanha de Unova, e **Jellicent**, que segura o que ameaça os dois de fogo. É o time de quem **chega primeiro**.

*Plano (Singles):* velocidade. O Tornadus (Prankster) põe Tailwind ou Taunt antes de qualquer um; com o vento, o Reshiram (Turboblaze, ignora Flash Fire e afins) bate Blue Flare e Draco Meteor, a Mega Emboar entra de Flare Blitz/Close Combat e o Galvantula (Compound Eyes) acerta Thunder a 91%. O Excadrill, de Focus Sash, sobe Swords Dance e segura as pedras. O Jellicent (Water Absorb) entra contra água/terra/luta e desgasta com Scald e Will-O-Wisp.

*Plano (Doubles):* Tailwind de prioridade no turno 1 + Heat Wave do Reshiram; o Galvantula prende com Electroweb; o Jellicent come os golpes de água mirados nos dois de fogo. Nenhum golpe do time acerta o parceiro (o Excadrill usa High Horsepower, não Earthquake).

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Reshiram | Life Orb | Turboblaze | Modest | Blue Flare, Draco Meteor, Earth Power, Heat Wave |
| Tornadus | Covert Cloak | Prankster | Timid | Bleakwind Storm, Tailwind, Taunt, Protect |
| Emboar | Firetite | Reckless | Adamant | Flare Blitz, Close Combat, Head Smash, Protect |
| Excadrill | Focus Sash | Mold Breaker | Jolly | High Horsepower, Iron Head, Rock Slide, Swords Dance |
| Jellicent | Leftovers | Water Absorb | Calm | Scald, Shadow Ball, Will-O-Wisp, Recover |
| Galvantula | Choice Specs | Compound Eyes | Timid | Thunder, Bug Buzz, Electroweb, Volt Switch |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>dev_scripts/nexus_validar_time.py</code>: trainerproc, constantes, learnsets e categorias)</summary>

```
=== TRAINER_NEXUS_HILDA ===
Name: Hilda
Class: Pkmn Trainer 1
Pic: Cooltrainer F
Gender: Female
Music: Female
Double Battle: No
AI: Smart Trainer

Reshiram @ Life Orb
Modest Nature
Level: 100
Ability: Turboblaze
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Blue Flare
- Draco Meteor
- Earth Power
- Heat Wave

Tornadus @ Covert Cloak
Timid Nature
Level: 100
Ability: Prankster
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Bleakwind Storm
- Tailwind
- Taunt
- Protect

Emboar @ Firetite
Adamant Nature
Level: 100
Ability: Reckless
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Flare Blitz
- Close Combat
- Head Smash
- Protect

Excadrill @ Focus Sash
Jolly Nature
Level: 100
Ability: Mold Breaker
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- High Horsepower
- Iron Head
- Rock Slide
- Swords Dance

Jellicent @ Leftovers
Calm Nature
Level: 100
Ability: Water Absorb
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Scald
- Shadow Ball
- Will-O-Wisp
- Recover

Galvantula @ Choice Specs
Timid Nature
Level: 100
Ability: Compound Eyes
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Thunder
- Bug Buzz
- Electroweb
- Volt Switch
```

</details>

### Lendário associado

#### Reshiram

📝 **Proposta de 30/09/2026, aguardando o autor.** **Reshiram**. A Hilda é a campeã dele: a quinta luta do Daily, logo antes da boss battle. **Quem cede:** o Brendan (tabela "Campeões novos" em [`DIARIO_LOOKER.md`](../DIARIO_LOOKER.md)), que fica com o Jirachi. Enquanto o autor não aprova, a ficha do Brendan e o código continuam como estão.

**Quem é.** Hilda, a protagonista feminina de *Black/White*, de Nuvema Town. Derrota o N e o Ghetsis no castelo do Team Plasma e, dois anos depois, em *Black 2/White 2*, **sumiu**: saiu de Unova atrás do N, e só se ouve falar dela. No fragmento dela, ela está há dois anos atrás dele — e o dragão branco a segue.

**A criatura.** Reshiram (Dragão/Fogo), o Pokémon da verdade. Ele e o Zekrom eram um dragão só, que se partiu quando os dois irmãos heróis de Unova brigaram, um pela verdade e outro pelo ideal. Sem herói, dorme como a Light Stone. A cauda inflamada move a atmosfera e muda o clima do mundo.

**O fragmento.** Um deserto de cinza branca sem sombra nenhuma (é o fragmento que o jogo já tem). No fragmento da Hilda, a cinza cobre Unova inteira no caminho que ela faz, e na borda dele fica uma linha: do outro lado começa a tempestade de torres negras do N.

**Falas do fragmento e ficha do Looker:** **já estão no jogo** — não reescrevi. Aponto as que existem em `data/scripts/nexus.inc`:

| Fala | Label | Onde |
|---|---|---|
| Chegada | `Nexus_Text_Reshiram_Arrival` | `data/scripts/nexus.inc` |
| Boss | `Nexus_Text_Reshiram_Boss` | `data/scripts/nexus.inc` |
| Ficha do Looker (**File L-643. Vast White.**) | `Nexus_Text_Reshiram_LookerFile` (script `Nexus_EventScript_Reshiram_LookerFile`) | `data/scripts/nexus.inc` |

⚠️ O texto do Looker File que está no jogo foi escrito para o campeão atual (Brendan): "a young man who finally stopped hiding one small thing". Se a troca for aprovada, a linha do Looker File que descreve a pessoa deixa de bater com o campeão — decisão do autor (trocar só essa frase, ou manter como está, já que o Looker File descreve o universo e não precisa bater). Não reescrevi.

### Diálogo genérico

📝 **Proposta de 30/09/2026, aguardando o autor.** Quando Hilda cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala de si, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)). Ainda não há nada no `nexus.inc`: as três variações são novas.

A Hilda dos jogos não fala (é a protagonista). Aqui ela ganha voz: direta, sempre com pressa, corajosa e um pouco fugindo de casa. As três variações são três ângulos: a pressa (quem ela persegue), a casa (as cartas da mãe que ela não abre) e a infância (os três amigos de Nuvema).

#### Variação 1 — a pressa

**Antes da luta**

> Sorry, I'm in a hurry. I've been in a hurry for about two years now.
>
> Somebody left without saying where he was going. I'm going to catch up.
>
> You're standing between me and the next door. So… battle!

**Derrota**

> Fine. This one's yours. I still have to keep going.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Hilda_Intro:
	.string "Sorry, I'm in a hurry. I've been in a\n"
	.string "hurry for about two years now.\p"
	.string "Somebody left without saying where he\n"
	.string "was going. I'm going to catch up.\p"
	.string "You're standing between me and the\n"
	.string "next door. So… battle!$"

Nexus_Text_Hilda_Defeat:
	.string "Fine. This one's yours. I still have to\n"
	.string "keep going.$"
```

</details>

#### Variação 2 — as cartas

**Antes da luta**

> My mom sends a letter to every Pokémon Center I might pass through. I've collected forty.
>
> I haven't opened one. If I open one, I'll go home.
>
> …Let's battle before I think about that too hard.

**Derrota**

> Okay. Okay. Maybe I'll open one tonight.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Hilda_Intro2:
	.string "My mom sends a letter to every Pokémon\n"
	.string "Center I might pass through. I've\l"
	.string "collected forty.\p"
	.string "I haven't opened one. If I open one,\n"
	.string "I'll go home.\p"
	.string "…Let's battle before I think about\n"
	.string "that too hard.$"

Nexus_Text_Hilda_Defeat2:
	.string "Okay. Okay. Maybe I'll open one\n"
	.string "tonight.$"
```

</details>

#### Variação 3 — os três de Nuvema

**Antes da luta**

> Back home there were three of us. One wanted to be strong. One wanted to be free.
>
> Me? I just wanted to go first. Out the door, down the road, first.
>
> I still do. Let's go!

**Derrota**

> Second place. Cheren would have a speech ready for this.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Hilda_Intro3:
	.string "Back home there were three of us. One\n"
	.string "wanted to be strong. One wanted to be\l"
	.string "free.\p"
	.string "Me? I just wanted to go first. Out the\n"
	.string "door, down the road, first.\p"
	.string "I still do. Let's go!$"

Nexus_Text_Hilda_Defeat3:
	.string "Second place. Cheren would have a\n"
	.string "speech ready for this.$"
```

</details>

### Diálogo associado ao lendário

📝 **Proposta de 30/09/2026, aguardando o autor.** Quando Hilda é o **campeão**, a luta logo antes do lendário. A fala é sobre a criatura, sem dizer o nome dela ([R16](../NEXUS_REGRAS.md)).

#### Reshiram

O dragão branco só fica com quem diz a verdade; no fragmento dela, a cauda **fica cinza** quando ela mente, como se voltasse a ser pedra. As três variações: a verdade que ela não queria dizer (não quer trazer o N de volta, quer saber se ele está feliz), o lugar sem sombra que mostra tudo, e a tempestade negra no horizonte (o dragão que foi irmão deste). A 3 termina com ela mentindo de leve e o dragão percebendo.

##### Variação 1 — a verdade que ela não queria dizer

**Antes da luta**

> See the white one out there? It only stays with someone who tells the truth.
>
> So here's mine. I'm not chasing him to bring him home. I just want to know if he found what he left to find.
>
> …That was awful to say out loud. Battle me before I take it back!

**Derrota**

> Truth hurts. So do you.

**Depois da luta**

> When I lie, even a little, its tail goes grey. Like ash. Like it's turning back into a stone.
>
> So I've been honest for two years. With everyone. It's exhausting. I don't recommend it.
>
> Go on. It'll know if you're pretending, too.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Hilda_ChampionIntro:
	.string "See the white one out there? It only\n"
	.string "stays with someone who tells the truth.\p"
	.string "So here's mine. I'm not chasing him to\n"
	.string "bring him home. I just want to know if\l"
	.string "he found what he left to find.\p"
	.string "…That was awful to say out loud. Battle\n"
	.string "me before I take it back!$"

Nexus_Text_Hilda_ChampionDefeat:
	.string "Truth hurts. So do you.$"

Nexus_Text_Hilda_ChampionAfter:
	.string "{SPEAKER NAME_HILDA}When I lie, even a little, its tail goes\n"
	.string "grey. Like ash. Like it's turning back\l"
	.string "into a stone.\p"
	.string "So I've been honest for two years. With\n"
	.string "everyone. It's exhausting. I don't\l"
	.string "recommend it.\p"
	.string "Go on. It'll know if you're pretending,\n"
	.string "too.$"
```

</details>

##### Variação 2 — nada tem sombra

**Antes da luta**

> It burns so bright out there that nothing has a shadow. I tried to hide from it once. Couldn't.
>
> It doesn't judge you. It just shows everything. Somehow that's worse.
>
> Come on. Let's see what it shows about you!

**Derrota**

> Everything showing. Nothing left to hide.

**Depois da luta**

> The first time it flew beside me, I could see my whole route. Every town I ran through without stopping.
>
> It wasn't scolding me. It was just… the truth. I'd been running, not searching.
>
> Go on. Walk slowly, if you can. It's nicer.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Hilda_ChampionIntro2:
	.string "It burns so bright out there that\n"
	.string "nothing has a shadow. I tried to hide\l"
	.string "from it once. Couldn't.\p"
	.string "It doesn't judge you. It just shows\n"
	.string "everything. Somehow that's worse.\p"
	.string "Come on. Let's see what it shows about\n"
	.string "you!$"

Nexus_Text_Hilda_ChampionDefeat2:
	.string "Everything showing. Nothing left to\n"
	.string "hide.$"

Nexus_Text_Hilda_ChampionAfter2:
	.string "{SPEAKER NAME_HILDA}The first time it flew beside me, I could\n"
	.string "see my whole route. Every town I ran\l"
	.string "through without stopping.\p"
	.string "It wasn't scolding me. It was just… the\n"
	.string "truth. I'd been running, not searching.\p"
	.string "Go on. Walk slowly, if you can. It's\n"
	.string "nicer.$"
```

</details>

##### Variação 3 — a tempestade no horizonte

**Antes da luta**

> Sometimes, far off, there's a black storm at the edge of all this white. It never comes closer.
>
> They say the two dragons were one, a long time ago. Then two brothers argued, and it split.
>
> I wonder who stopped talking first. Battle!

**Derrota**

> Guess I'm the one who stopped.

**Depois da luta**

> The white one looks at that storm sometimes. The same way I do.
>
> Neither of us goes over there. We tell ourselves it's respect.
>
> …That's not quite the truth, is it? Its tail's going grey. Go on, before it notices.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Hilda_ChampionIntro3:
	.string "Sometimes, far off, there's a black\n"
	.string "storm at the edge of all this white. It\l"
	.string "never comes closer.\p"
	.string "They say the two dragons were one, a\n"
	.string "long time ago. Then two brothers\l"
	.string "argued, and it split.\p"
	.string "I wonder who stopped talking first.\n"
	.string "Battle!$"

Nexus_Text_Hilda_ChampionDefeat3:
	.string "Guess I'm the one who stopped.$"

Nexus_Text_Hilda_ChampionAfter3:
	.string "{SPEAKER NAME_HILDA}The white one looks at that storm\n"
	.string "sometimes. The same way I do.\p"
	.string "Neither of us goes over there. We tell\n"
	.string "ourselves it's respect.\p"
	.string "…That's not quite the truth, is it? Its\n"
	.string "tail's going grey. Go on, before it\l"
	.string "notices.$"
```

</details>

Falante novo: `SP_NAME_HILDA` (ainda não existe em `include/constants/speaker_names.h`; a plaquinha usa `NAME_HILDA`).

### Diário do Looker

📝 **Proposta de 30/09/2026, aguardando o autor.** Três páginas em [`diario_looker/hilda/`](diario_looker/hilda/) — formato e fios em [`DIARIO_LOOKER.md`](../DIARIO_LOOKER.md).

- [1_comeco.md](diario_looker/hilda/1_comeco.md) — começo: o deserto de cinza, a garota sempre na frente, o vagão de brinquedo nas cinzas
- [2_meio.md](diario_looker/hilda/2_meio.md) — meio: a cauda cinza, a chamada de "C." sem resposta, a verdade dela
- [3_fim.md](diario_looker/hilda/3_fim.md) — fim: a linha entre a cinza e a tempestade; o boné na pedra; a mensagem que a faz rir
