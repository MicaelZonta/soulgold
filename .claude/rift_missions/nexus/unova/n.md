# N

**Região da ficha:** Unova

Aparece no checklist como:

- **N** (Unova · Team Plasma) — jovem capaz de ouvir Pokémon, criado para ser o rei do Team Plasma.

**Pronto para o Nexus:** ❌ não — tem sprite de overworld, falta o battle sprite (front pic), obrigatório.

**Arte disponível:** ✅ overworld e front pic em `.filetransfer/.trainers/N/` (o overworld já está registrado no código; a front pic ainda não).

## Checklist

- [x] Sprite de overworld *(obrigatório)* — `OBJ_EVENT_GFX_N` (registrado no merge de 30/09/2026)
- [ ] Battle sprite / front pic *(obrigatório)* — arte em `.filetransfer/.trainers/N/`, falta registrar
- [ ] Field mugshot (retrato na caixa de diálogo)
- [ ] Time para as Rift Missions definido — 📝 proposta nesta ficha (30/09/2026), fora do código
- [ ] Associado a um lendário — 📝 proposta nesta ficha (Zekrom), fora do código
- [ ] Diálogo genérico escrito — 📝 proposta nesta ficha (3 variações), fora do código
- [ ] Diálogo associado ao lendário escrito — 📝 proposta nesta ficha (3 variações), fora do código

## Referências no repositório

### Sprite de overworld

| Constante | Arquivo | Tamanho |
|---|---|---|
| `OBJ_EVENT_GFX_N` | `graphics/object_events/pics/people/special/n.png` | 16x32 |

Registrado no merge de 30/09/2026 (`include/constants/event_objects.h`, paleta própria `OBJ_EVENT_PAL_TAG_N`). A arte original está em `.filetransfer/.trainers/N/Sprite - Boyaloxer e outros.png` (autores: Boyaloxer e outros — créditos completos em `creditos.txt`: Boyaloxer, PurpleZaffre, Luckygirl88, JpKEKS, Delgatron; back sprites de LightningKillua15 / mid117), com `Sprite - comparacao no jogo.png` ao lado.

### Battle sprite (front pic)

**Não está no código.** A arte está em `.filetransfer/.trainers/N/`:

- `Trainer - Boyaloxer e outros.png` — 114x136, autores em `creditos.txt` (precisa recorte para 64x64)
- `Trainer - comparacao no jogo.png` — comparação no jogo
- `outras/Folha completa - Boyaloxer e outros.jpg` — folha completa (o `creditos.txt` cita back sprites também)

Falta converter para 64x64 e registrar (skills `converter-sprite` e `adicionar-grafico-trainer`). Até lá o bloco do `.party` usa uma pic provisória.

### Field mugshot

Não existe. Nada parecido na pasta dele. Opcional; criar com a skill `adicionar-grafico-trainer`.

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

Nenhuma. Ao criar, seguir a skill `adicionar-batalha-npc` (e `alocar-flag` se precisar de flag nova).

### Time das Rift Missions

📝 **Proposta de 30/09/2026, aguardando o autor.** `TRAINER_NEXUS_N`, campeão do Zekrom. ID: **a alocar** (IDs livres abaixo de 1056; não usar 1056–1163). Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega; 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler). **Pic provisória** (`Psychic M`) até registrar a arte.

Lendário **Zekrom**, o dragão do ideal, o que segue o N em *Pokémon Black*. Semi-lendário **Thundurus**, o gênio do trovão: nuvem de tempestade com a nuvem de tempestade. Mega **Audino** (Normalite, Mega com Healer, Normal/Fada): o Pokémon que **escuta** batimentos com as antenas das orelhas, para o garoto que escuta a voz dos Pokémon. Mais três do time dele em *Black/White*: **Zoroark** (o primeiro amigo, a ilusão), **Carracosta** e **Klinklang** (as engrenagens do quarto de brinquedos e da fórmula).

*Plano (Singles):* o Thundurus (Prankster) paralisa com Thunder Wave e trava com Taunt; com o adversário lento, o Carracosta (Sturdy + White Herb) usa Shell Smash sem medo de cair no turno, e o Klinklang sobe Shift Gear. O Zekrom (Teravolt, ignora habilidades) fecha com Bolt Strike. O Zoroark entra disfarçado de outro do time e bate com Choice Scarf.

*Plano (Doubles):* o formato favorito dele (`Double Battle: Yes`). Thunder Wave de prioridade + Heal Pulse/Helping Hand da Mega Audino (Healer cura status do parceiro). O Zekrom recebe Helping Hand e bate; o Carracosta sobe Shell Smash enquanto a Audino segura. Nenhum golpe do time acerta o parceiro.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Zekrom | Life Orb | Teravolt | Adamant | Bolt Strike, Dragon Claw, Crunch, Protect |
| Thundurus | Sitrus Berry | Prankster | Timid | Thunderbolt, Thunder Wave, Taunt, Nasty Plot |
| Audino | Normalite | Healer | Bold | Heal Pulse, Helping Hand, Dazzling Gleam, Protect |
| Zoroark | Choice Scarf | Illusion | Timid | Night Daze, Flamethrower, Focus Blast, U-turn |
| Carracosta | White Herb | Sturdy | Adamant | Shell Smash, Liquidation, Stone Edge, Aqua Jet |
| Klinklang | Leftovers | Clear Body | Adamant | Shift Gear, Gear Grind, Wild Charge, Protect |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>dev_scripts/nexus_validar_time.py</code>: trainerproc, constantes, learnsets e categorias)</summary>

```
=== TRAINER_NEXUS_N ===
Name: N
Class: Pkmn Trainer 1
Pic: Psychic M
Gender: Male
Music: Intense
Double Battle: Yes
AI: Smart Trainer

Zekrom @ Life Orb
Adamant Nature
Level: 100
Ability: Teravolt
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Bolt Strike
- Dragon Claw
- Crunch
- Protect

Thundurus @ Sitrus Berry
Timid Nature
Level: 100
Ability: Prankster
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Thunderbolt
- Thunder Wave
- Taunt
- Nasty Plot

Audino @ Normalite
Bold Nature
Level: 100
Ability: Healer
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Heal Pulse
- Helping Hand
- Dazzling Gleam
- Protect

Zoroark @ Choice Scarf
Timid Nature
Level: 100
Ability: Illusion
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Night Daze
- Flamethrower
- Focus Blast
- U-turn

Carracosta @ White Herb
Adamant Nature
Level: 100
Ability: Sturdy
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Shell Smash
- Liquidation
- Stone Edge
- Aqua Jet

Klinklang @ Leftovers
Adamant Nature
Level: 100
Ability: Clear Body
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Shift Gear
- Gear Grind
- Wild Charge
- Protect
```

</details>

### Lendário associado

#### Zekrom

📝 **Proposta de 30/09/2026, aguardando o autor.** **Zekrom**. O N é o campeão dele: a quinta luta do Daily, logo antes da boss battle. **Quem cede:** a May (tabela "Campeões novos" em [`DIARIO_LOOKER.md`](../DIARIO_LOOKER.md)), que fica com o Mesprit. Enquanto o autor não aprova, a ficha da May e o código continuam como estão.

**Quem é.** N, Natural Harmonia Gropius. Criado pelo Ghetsis num quarto de brinquedos, isolado, ouvindo só Pokémon maltratados, para ser o rei do Team Plasma e "libertar" os Pokémon dos humanos. Fala rápido, pensa em fórmulas, ouve a voz dos Pokémon. Em *Black/White* derrota o Alder e vira "campeão"; perde para o herói da verdade e parte no Zekrom.

**A criatura.** Zekrom (Dragão/Elétrico), o Pokémon do ideal. A metade negra do dragão que se partiu quando os irmãos heróis brigaram. Segue quem persegue um ideal com força; a cauda é um gerador, e ele se esconde dentro de nuvens de trovão.

**O fragmento.** A cidade de torres negras dentro de uma nuvem de trovão (o que o jogo já tem). No fragmento do N, é a Unova em que **o Team Plasma venceu**: todas as bolas foram abertas, os Pokémon libertados ficam sentados na porta das casas onde moravam, e o N é o único que ainda tem um Pokémon ao lado. A heroína da verdade nunca chegou ali.

**Falas do fragmento e ficha do Looker:** **já estão no jogo** — não reescrevi. Aponto as que existem em `data/scripts/nexus.inc`:

| Fala | Label | Onde |
|---|---|---|
| Chegada | `Nexus_Text_Zekrom_Arrival` | `data/scripts/nexus.inc` |
| Boss | `Nexus_Text_Zekrom_Boss` | `data/scripts/nexus.inc` |
| Ficha do Looker (**File L-644. Deep Black.**) | `Nexus_Text_Zekrom_LookerFile` (script `Nexus_EventScript_Zekrom_LookerFile`) | `data/scripts/nexus.inc` |

⚠️ O texto do Looker File que está no jogo foi escrito para o campeão atual (May): "a girl who wants to see everything". Se a troca for aprovada, a linha do Looker File que descreve a pessoa deixa de bater com o campeão — decisão do autor (trocar só essa frase, ou manter como está, já que o Looker File descreve o universo e não precisa bater). Não reescrevi.

### Diálogo genérico

📝 **Proposta de 30/09/2026, aguardando o autor.** Quando N cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala de si, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)). Ainda não há nada no `nexus.inc`: as três variações são novas.

O N fala rápido, em frases longas, com palavras de matemática, e sempre conta o que os Pokémon **do outro** estão dizendo. As três variações: ele ouvindo os Pokémon do jogador (a assinatura dele nos jogos), o quarto de brinquedos sem janela (o trem que anda em círculo) e a fórmula que não fechou.

#### Variação 1 — o que os seus Pokémon dizem

**Antes da luta**

> Your Pokémon are talking. They say you walk too fast, and that you apologize to them afterward.
>
> …Interesting. Mine say I think too much. Shall we find out which of us is right?

**Derrota**

> Their voices were so clear. Clearer than mine. Hm.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_N_Intro:
	.string "Your Pokémon are talking. They say you\n"
	.string "walk too fast, and that you apologize\l"
	.string "to them afterward.\p"
	.string "…Interesting. Mine say I think too\n"
	.string "much. Shall we find out which of us is\l"
	.string "right?$"

Nexus_Text_N_Defeat:
	.string "Their voices were so clear. Clearer than\n"
	.string "mine. Hm.$"
```

</details>

#### Variação 2 — o quarto de brinquedos

**Antes da luta**

> I grew up in a room full of toys and no windows. A train that ran in a circle. A ramp nobody used.
>
> I thought the whole world was that circle. It isn't. It's so much larger.
>
> Show me more of it!

**Derrota**

> Another piece of the world. I'll keep it.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_N_Intro2:
	.string "I grew up in a room full of toys and no\n"
	.string "windows. A train that ran in a circle. A\l"
	.string "ramp nobody used.\p"
	.string "I thought the whole world was that\n"
	.string "circle. It isn't. It's so much larger.\p"
	.string "Show me more of it!$"

Nexus_Text_N_Defeat2:
	.string "Another piece of the world. I'll keep\n"
	.string "it.$"
```

</details>

#### Variação 3 — a fórmula

**Antes da luta**

> I believed the world was a formula. Solve it, and every Pokémon would be free.
>
> The formula had a variable I never counted. People. People like you.
>
> Let's calculate it again!

**Derrota**

> Unsolved. That's… not an unpleasant feeling.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_N_Intro3:
	.string "I believed the world was a formula.\n"
	.string "Solve it, and every Pokémon would be\l"
	.string "free.\p"
	.string "The formula had a variable I never\n"
	.string "counted. People. People like you.\p"
	.string "Let's calculate it again!$"

Nexus_Text_N_Defeat3:
	.string "Unsolved. That's… not an unpleasant\n"
	.string "feeling.$"
```

</details>

### Diálogo associado ao lendário

📝 **Proposta de 30/09/2026, aguardando o autor.** Quando N é o **campeão**, a luta logo antes do lendário. A fala é sobre a criatura, sem dizer o nome dela ([R16](../NEXUS_REGRAS.md)).

#### Zekrom

O dragão negro segue quem quer algo com força. No fragmento dele, **o ideal se cumpriu** e ficou errado: os libertados chamam nomes humanos à noite. As três variações: o ideal realizado (e o novo ideal que ele ainda não sabe), o zumbido que nunca descansa (o vazio no meio da tempestade) e a luz branca no horizonte (a Hilda, do outro lado).

##### Variação 1 — o ideal que se cumpriu

**Antes da luta**

> It follows whoever wants something badly enough. I wanted a world where every Pokémon was free.
>
> I got it. Every ball opened. Every city quiet.
>
> And still it follows me. So I must want something else now. Let's find out what!

**Derrota**

> Your ideal was louder. How?

**Depois da luta**

> The freed ones stay near the towns. They don't hunt. They sit by the doors.
>
> I can hear them at night. They're calling names. Human names.
>
> My ideal was right, and it was wrong. The dragon doesn't mind which. It only minds that I still want. Go.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_N_ChampionIntro:
	.string "It follows whoever wants something\n"
	.string "badly enough. I wanted a world where\l"
	.string "every Pokémon was free.\p"
	.string "I got it. Every ball opened. Every city\n"
	.string "quiet.\p"
	.string "And still it follows me. So I must want\n"
	.string "something else now. Let's find out\l"
	.string "what!$"

Nexus_Text_N_ChampionDefeat:
	.string "Your ideal was louder. How?$"

Nexus_Text_N_ChampionAfter:
	.string "{SPEAKER NAME_N}The freed ones stay near the towns.\n"
	.string "They don't hunt. They sit by the doors.\p"
	.string "I can hear them at night. They're\n"
	.string "calling names. Human names.\p"
	.string "My ideal was right, and it was wrong. The\n"
	.string "dragon doesn't mind which. It only\l"
	.string "minds that I still want. Go.$"
```

</details>

##### Variação 2 — o zumbido que não descansa

**Antes da luta**

> Hear that hum? It's charging. It's always charging. It doesn't know how to rest.
>
> An ideal is like that. Beautiful, and it never lets you sleep.
>
> Let me show you how it feels!

**Derrota**

> The hum stopped. Just for a moment.

**Depois da luta**

> I asked it once why it chose me. It showed me a storm with nothing in the middle.
>
> I think that was the answer. I'm the middle. And I was empty.
>
> …Your friends say you want to tell me something kind. You don't have to. Go.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_N_ChampionIntro2:
	.string "Hear that hum? It's charging. It's\n"
	.string "always charging. It doesn't know how\l"
	.string "to rest.\p"
	.string "An ideal is like that. Beautiful, and it\n"
	.string "never lets you sleep.\p"
	.string "Let me show you how it feels!$"

Nexus_Text_N_ChampionDefeat2:
	.string "The hum stopped. Just for a moment.$"

Nexus_Text_N_ChampionAfter2:
	.string "{SPEAKER NAME_N}I asked it once why it chose me. It\n"
	.string "showed me a storm with nothing in the\l"
	.string "middle.\p"
	.string "I think that was the answer. I'm the\n"
	.string "middle. And I was empty.\p"
	.string "…Your friends say you want to tell me\n"
	.string "something kind. You don't have to. Go.$"
```

</details>

##### Variação 3 — a luz branca no horizonte

**Antes da luta**

> At the far edge of the storm there's a white light. Always far away. Always burning.
>
> The other dragon, and someone walking beside it.
>
> I've run toward it a hundred times. The storm moves with me. Battle!

**Derrota**

> Still far. Still burning.

**Depois da luta**

> Two dragons, once one. They split because two brothers couldn't agree.
>
> I used to read that as a warning. Now I read it as a map.
>
> If truth and ideal were one thing once, the problem is the distance, not the difference. …Go. I'll keep walking.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_N_ChampionIntro3:
	.string "At the far edge of the storm there's a\n"
	.string "white light. Always far away. Always\l"
	.string "burning.\p"
	.string "The other dragon, and someone walking\n"
	.string "beside it.\p"
	.string "I've run toward it a hundred times. The\n"
	.string "storm moves with me. Battle!$"

Nexus_Text_N_ChampionDefeat3:
	.string "Still far. Still burning.$"

Nexus_Text_N_ChampionAfter3:
	.string "{SPEAKER NAME_N}Two dragons, once one. They split\n"
	.string "because two brothers couldn't agree.\p"
	.string "I used to read that as a warning. Now I\n"
	.string "read it as a map.\p"
	.string "If truth and ideal were one thing once,\n"
	.string "the problem is the distance, not the\l"
	.string "difference. …Go. I'll keep walking.$"
```

</details>

Falante novo: `SP_NAME_N` (ainda não existe em `include/constants/speaker_names.h`; a plaquinha usa `NAME_N`).

### Diário do Looker

📝 **Proposta de 30/09/2026, aguardando o autor.** Três páginas em [`diario_looker/n/`](diario_looker/n/) — formato e fios em [`DIARIO_LOOKER.md`](../DIARIO_LOOKER.md).

- [1_comeco.md](diario_looker/n/1_comeco.md) — começo: a Unova silenciosa da Libertação; a pilha de Poké Balls; o rei que ouve o Croagunk do Looker
- [2_meio.md](diario_looker/n/2_meio.md) — meio: o quarto de brinquedos com um vagão faltando; o pai que não é pai; o boné no alto da torre
- [3_fim.md](diario_looker/n/3_fim.md) — fim: o rei abrindo a pilha, bola por bola; o vagão deixado na linha, apontando para a cinza
