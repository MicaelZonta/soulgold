# Barry

**Região da ficha:** Sinnoh

Aparece no checklist como:

- **Barry** (Sinnoh · Rival) — rival hiperativo, competitivo e filho do Frontier Brain Palmer.

**Pronto para o Nexus:** ❌ não — tem sprite de overworld, falta o battle sprite (front pic), obrigatório.

**Arte disponível:** ✅ overworld (já registrado) e front pic em `.filetransfer/.trainers/Barry/`.

## Checklist

- [x] Sprite de overworld *(obrigatório)*
- [ ] Battle sprite / front pic *(obrigatório)* — 📦 arte pronta em `.filetransfer`, falta registrar
- [ ] Field mugshot (retrato na caixa de diálogo)
- [ ] Time para as Rift Missions definido — 📝 proposta abaixo (30/09/2026)
- [ ] Associado a um lendário — 📝 proposta abaixo (30/09/2026)
- [ ] Diálogo genérico escrito — 📝 proposta abaixo (30/09/2026)
- [ ] Diálogo associado ao lendário escrito — 📝 proposta abaixo (30/09/2026)

## Referências no repositório

### Sprite de overworld

| Constante | Arquivo |
|---|---|
| `OBJ_EVENT_GFX_BARRY` | `graphics/object_events/pics/people/special/barry.png` (32x32, 12 quadros com lado direito próprio, `sAnimTable_StandardAsym`) |

Registrado em 30/09/2026. Origem em `.filetransfer/.trainers/Barry/`: `Sprite - redblueyellow (rip).png` (autor **redblueyellow**, rip), `Sprite - comparacao no jogo.png` e `outras/Folha completa - redblueyellow (rip).png`.

### Battle sprite (front pic)

Não registrado no código. **Arte pronta** em `.filetransfer/.trainers/Barry/`:

- `Trainer - redblueyellow (rip).png` (56x118, autor **redblueyellow**, rip; maior que 64x64 na altura — precisa de recorte)
- `Trainer - comparacao no jogo.png` (comparação no jogo)

Falta registrar: skills `converter-sprite` (conferir/reduzir para 64x64, ≤16 cores) e `adicionar-grafico-trainer` (`TRAINER_PIC_FRONT_BARRY`). Até lá o bloco do time usa uma **pic provisória** (ver abaixo).

### Field mugshot

Não existe (a pasta da arte não tem retrato). Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

Nenhuma. Ao criar, seguir a skill `adicionar-batalha-npc` (e `alocar-flag` se precisar de flag nova).

### Time das Rift Missions

📝 **Proposta de 30/09/2026, aguardando o autor.** `TRAINER_NEXUS_BARRY` (ID **a alocar**: livre abaixo de 1056, nunca 1056–1163), campeão de Uxie. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega; 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler). Validado com `python3 dev_scripts/nexus_validar_time.py` (✓). **Pic provisória `Youngster`** até registrar a arte; classe `Rival`. `Double Battle: Yes`: em Platinum o Barry luta em dupla com o jogador; o plano vale nos dois.

O Uxie é **semi-lendário** (R10), então o time leva também um lendário. Lendário **Deoxys, Forma Speed** ([R21](../NEXUS_REGRAS.md)): no fragmento dele, a única coisa que já correu mais que o Barry caiu do céu perto de Twinleaf, e ele a seguiu até ela desistir. Semi-lendário **Uxie**, de que ele é campeão: o lago que em Diamond/Pearl ele não conseguiu proteger. Mega **Staraptor** (Flyingite; Mega Lutador/Voador com **Contrary**: cada Close Combat sobe as defesas em vez de baixar), o Starly dele desde a Rota 201. Mais **Empoleon** (o Piplup, uma das escolhas de inicial dele), **Heracross** e **Snorlax**, do time dele em Platinum.

*Plano (Singles):* pressa. O Deoxys-S de Focus Sash põe Stealth Rock, Taunt e bate com Psycho Boost; o Uxie põe o alvo para dormir com Yawn e pivota com U-turn; a Mega Staraptor fica mais dura a cada Close Combat; o Heracross de Guts com Flame Orb bate de Facade; o Empoleon de Competitive pune quem baixa os status dele; o Snorlax, o único do time sem pressa, sobe Belly Drum no fim.

*Plano (Doubles):* Intimidate do Staraptor na entrada e Tailwind no primeiro turno; Helping Hand do Uxie no Snorlax ou no Heracross; Taunt do Deoxys no suporte adversário. Nenhum golpe do time acerta o parceiro.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Deoxys-Speed | Focus Sash | Pressure | Hasty | Psycho Boost, Knock Off, Taunt, Stealth Rock |
| Uxie | Sitrus Berry | Levitate | Bold | Psychic, Yawn, U-turn, Helping Hand |
| Staraptor | Flyingite | Intimidate | Jolly | Brave Bird, Close Combat, Tailwind, U-turn |
| Empoleon | Leftovers | Competitive | Modest | Hydro Pump, Flash Cannon, Ice Beam, Grass Knot |
| Heracross | Flame Orb | Guts | Jolly | Close Combat, Megahorn, Knock Off, Facade |
| Snorlax | Sitrus Berry | Thick Fat | Adamant | Belly Drum, Double-Edge, Crunch, Heavy Slam |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>dev_scripts/nexus_validar_time.py</code>: trainerproc, constantes, learnsets e vagas)</summary>

```
=== TRAINER_NEXUS_BARRY ===
Name: Barry
Class: Rival
Pic: Youngster
Gender: Male
Music: Dp Ace Trainer
Double Battle: Yes
AI: Smart Trainer

Deoxys-Speed @ Focus Sash
Hasty Nature
Level: 100
Ability: Pressure
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Psycho Boost
- Knock Off
- Taunt
- Stealth Rock

Uxie @ Sitrus Berry
Bold Nature
Level: 100
Ability: Levitate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Psychic
- Yawn
- U-turn
- Helping Hand

Staraptor @ Flyingite
Jolly Nature
Level: 100
Ability: Intimidate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Brave Bird
- Close Combat
- Tailwind
- U-turn

Empoleon @ Leftovers
Modest Nature
Level: 100
Ability: Competitive
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Hydro Pump
- Flash Cannon
- Ice Beam
- Grass Knot

Heracross @ Flame Orb
Jolly Nature
Level: 100
Ability: Guts
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Close Combat
- Megahorn
- Knock Off
- Facade

Snorlax @ Sitrus Berry
Adamant Nature
Level: 100
Ability: Thick Fat
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Belly Drum
- Double-Edge
- Crunch
- Heavy Slam
```

</details>

### Lendário associado

#### Uxie

📝 **Proposta de 30/09/2026, aguardando o autor.** **Uxie**. O Barry é o campeão dele; quem cede é a **Roxanne**, que fica com o Terapagos (tabela de [`DIARIO_LOOKER.md`](../DIARIO_LOOKER.md)). Enquanto o autor não aprova, a ficha da Roxanne e o código continuam como estão.

**Quem é.** Barry, o rival de Diamond/Pearl/Platinum, vizinho do protagonista em Twinleaf Town, filho do Palmer (Tower Tycoon). Hiperativo, sempre atrasado, ameaça multar todo mundo em dez milhões. Em DP/Pt corre para o Lago Acuity para proteger o Uxie e chega tarde: a comandante Jupiter já o levou.

**A criatura.** Uxie, o Ser do Conhecimento, dorme no fundo do Lago Acuity. Dizem que apaga a memória de quem o olha nos olhos; por isso anda de olhos fechados. Forma, com o Mesprit e o Azelf, o trio dos lagos.

**O fragmento.** O lago de páginas em branco (`Nexus_Text_Uxie_Arrival`). No fragmento do Barry, ele chegou **cedo**, pela primeira vez na vida, e ficou entre a comandante e o lago. A criatura abriu os olhos para salvá-lo; a comandante esqueceu o que tinha vindo fazer — e o Barry, na mesma linha de visão, esqueceu a pessoa que ele perseguia todo dia. Agora vai ao lago toda manhã esperar o nome voltar.

**Falas do fragmento** (narração; **já estão no jogo**, `Nexus_Text_Uxie_Arrival` e `Nexus_Text_Uxie_Boss` em `data/scripts/nexus.inc` — valem para qualquer campeão deste lendário e não mudam):

**Chegada**

> A still lake, and on its surface floated hundreds of loose pages.
>
> Every page was blank. The ink had only just left them. It was still spreading through the water in thin gray threads.

**Boss**

> The pages stopped drifting.
>
> Something rose from the middle of the lake with its eyes shut tight. It felt, somehow, like it was being polite.

**Ficha do Looker** — **já existe no jogo**: `Nexus_EventScript_Uxie_LookerFile` → `Nexus_Text_Uxie_LookerFile` (`data/scripts/nexus.inc`). Não reescrita aqui; o texto atual, para referência:

> File L-480. Keeper of Memory.
>
> A lake of blank pages, and a teacher who writes everything down so she never has to trust her memory.
>
> What came back with you is very small, and it keeps its eyes closed. I did not check what I still remember. I would rather not know.

O File L-480 atual fala da Roxanne (“a teacher who writes everything down”). Não serve para o fragmento do Barry. Proponho uma **versão alternativa**, para substituir o texto de `Nexus_Text_Uxie_LookerFile` **só se** a troca de campeão for aprovada (o Looker File é por lendário, R18; manter os dois pediria código novo).

**Versão alternativa** (📝 30/09/2026):

> File L-480. Keeper of Memory.
>
> A lake of blank pages, and a boy who runs there every morning to wait for a name he forgot.
>
> What came back with you keeps its eyes closed. I have written my own name inside my hat. Just in case.

<details><summary><code>.inc</code> da versão alternativa</summary>

```asm
Nexus_Text_Uxie_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-480. Keeper of Memory.\p"
	.string "A lake of blank pages, and a boy who\n"
	.string "runs there every morning to wait for a\l"
	.string "name he forgot.\p"
	.string "What came back with you keeps its eyes\n"
	.string "closed. I have written my own name\l"
	.string "inside my hat. Just in case.$"
```

</details>


### Diálogo genérico

📝 **Proposta de 30/09/2026, aguardando o autor.** Quando Barry cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala de si, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

Voz do Barry de DP/Pt: fala correndo, grita, se atropela, ameaça multar todo mundo em dez milhões e sempre chega atrasado. As três variações: a apresentação (a multa e o pai), o caderno de multas com nomes em branco (o que ele perdeu no fragmento, sem explicar) e a mania de chegar atrasado.

**Antes da luta**

> Whoa, whoa! You're in my way! …Wait, no, I'm in yours. Whatever! Battle!
>
> I'm Barry! I'm gonna be the strongest Trainer ever. Stronger than my dad, even!
>
> And if you're slow about it, I'm fining you ten million! Let's GO!

**Derrota**

> Aaargh! How?! Okay, okay. I'll fine myself this time. Ten million. Ouch.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Barry_Intro:
	.string "Whoa, whoa! You're in my way! …Wait, no,\n"
	.string "I'm in yours. Whatever! Battle!\p"
	.string "I'm Barry! I'm gonna be the strongest\n"
	.string "Trainer ever. Stronger than my dad,\l"
	.string "even!\p"
	.string "And if you're slow about it, I'm fining\n"
	.string "you ten million! Let's GO!$"

Nexus_Text_Barry_Defeat:
	.string "Aaargh! How?! Okay, okay. I'll fine\n"
	.string "myself this time. Ten million. Ouch.$"
```

</details>

#### Variações 2 e 3 (📝 proposta de 30/09/2026)

**Variação 2** — o caderno de multas com os nomes em branco

**Antes da luta**

> Hold on! I gotta write this down. I write down everybody who owes me a fine.
>
> See? Pages and pages! …Huh. This one's got no name. Neither does this one. Weird.
>
> Whatever! You're getting a page WITH a name! Battle!

**Derrota**

> Fine, fine, you win! …Hey, can you spell your name for me? Slowly? I keep losing them.

**Variação 3** — o atraso, o pai e a indignação de ter chegado cedo

**Antes da luta**

> My dad says I've never been on time for anything. Not once. Not even being born!
>
> That's not true! I was early for this! I've been waiting here, like, forever!
>
> …Okay, five minutes. That still counts! Battle!

**Derrota**

> I lost AND I was early?! That's not how it works! I'm filing a complaint! With me!

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Barry_Intro2:
	.string "Hold on! I gotta write this down. I\n"
	.string "write down everybody who owes me a\l"
	.string "fine.\p"
	.string "See? Pages and pages! …Huh. This one's\n"
	.string "got no name. Neither does this one.\l"
	.string "Weird.\p"
	.string "Whatever! You're getting a page WITH a\n"
	.string "name! Battle!$"

Nexus_Text_Barry_Defeat2:
	.string "Fine, fine, you win! …Hey, can you spell\n"
	.string "your name for me? Slowly? I keep losing\l"
	.string "them.$"

Nexus_Text_Barry_Intro3:
	.string "My dad says I've never been on time\n"
	.string "for anything. Not once. Not even being\l"
	.string "born!\p"
	.string "That's not true! I was early for this!\n"
	.string "I've been waiting here, like, forever!\p"
	.string "…Okay, five minutes. That still counts!\n"
	.string "Battle!$"

Nexus_Text_Barry_Defeat3:
	.string "I lost AND I was early?! That's not how\n"
	.string "it works! I'm filing a complaint! With\l"
	.string "me!$"
```

</details>

### Diálogo associado ao lendário

📝 **Proposta de 30/09/2026, aguardando o autor.** Quando Barry é o **campeão**, a luta logo antes do lendário. A fala é sobre a criatura, sem dizer o nome dela ([R16](../NEXUS_REGRAS.md)).

#### Uxie

O Barry de DP/Pt corre para o Lago Acuity para proteger o Uxie e chega tarde: a Jupiter já levou a criatura. No fragmento dele, pela primeira vez na vida, ele chegou **cedo**. Ficou entre a comandante e o lago; a criatura abriu os olhos para salvá-lo, a comandante esqueceu o que tinha vindo fazer — e o Barry, na mesma linha de visão, esqueceu o rival que ele perseguia todo dia ([R21](../NEXUS_REGRAS.md): nunca se diz quem era; não depende de o jogador ser lembrado). As três variações: o aviso (não olhe nos olhos) e o que ele perdeu, a paciência infinita da criatura que só sabe e não responde, e o nome do jogador anotado por garantia.

**Antes da luta**

> Listen! There's a thing in there that erases your memories if you look it in the eyes!
>
> So don't look! Just battle! That's what I did! …I think. I don't remember. Isn't that funny?
>
> …Wait, no, it isn't. Let's GO!

**Derrota**

> Gah! Okay, you're good! Don't let it make you forget that!

**Depois da luta**

> I got there on time, you know. First time in my whole life. Somebody came to take it, and I got in the way.
>
> It opened its eyes to save me. And I was right there. And now there's somebody I used to race every day… who isn't there.
>
> …Go! Hurry! And DON'T look it in the eyes. Seriously. You'd lose so much stuff.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Barry_ChampionIntro:
	.string "Listen! There's a thing in there that\n"
	.string "erases your memories if you look it in\l"
	.string "the eyes!\p"
	.string "So don't look! Just battle! That's\n"
	.string "what I did! …I think. I don't remember.\l"
	.string "Isn't that funny?\p"
	.string "…Wait, no, it isn't. Let's GO!$"

Nexus_Text_Barry_ChampionDefeat:
	.string "Gah! Okay, you're good! Don't let it\n"
	.string "make you forget that!$"

Nexus_Text_Barry_ChampionAfter:
	.string "{SPEAKER NAME_BARRY}I got there on time, you know. First\n"
	.string "time in my whole life. Somebody came to\l"
	.string "take it, and I got in the way.\p"
	.string "It opened its eyes to save me. And I\n"
	.string "was right there. And now there's\l"
	.string "somebody I used to race every day…\l"
	.string "who isn't there.\p"
	.string "…Go! Hurry! And DON'T look it in the\n"
	.string "eyes. Seriously. You'd lose so much\l"
	.string "stuff.$"
```

</details>

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

**Variação 2** — a pergunta que a criatura não respondeu por gentileza

**Antes da luta**

> It keeps its eyes shut the whole time. Like, the WHOLE time! Doesn't that drive you nuts?!
>
> I tried it for a day. Walked into three trees and a Ponyta.
>
> It's got way more patience than me. Everybody does! Battle!

**Derrota**

> Ow ow ow. Okay. That one I'll remember.

**Depois da luta**

> It knows everything, supposedly. Every single thing anybody ever knew.
>
> I asked it one question. Just one. It didn't answer. It just floated there, all polite, eyes shut.
>
> I think it was being nice. I think the answer would've hurt. …Anyway! GO! You're late!

**Variação 3** — o nome anotado por garantia, e a memória como uma bolsa que alguém segura

**Antes da luta**

> Okay, rule! Before we battle, you tell me your name. Then I say it back. Then I write it down.
>
> It's not for me! It's for… uh. It's a lake thing. You wouldn't get it.
>
> There! Now I won't forget you! Probably! BATTLE!

**Derrota**

> You're way too strong for somebody I just met. …We did just meet, right?

**Depois da luta**

> The thing in there doesn't steal memories. I thought it did. It just… holds on to them. Like a friend holding your bag.
>
> Mine's in there somewhere. Somebody's face. Somebody I was always chasing.
>
> If it gives it to you by accident, bring it here! I'll pay you! Ten million! …In installments!

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Barry_ChampionIntro2:
	.string "It keeps its eyes shut the whole time.\n"
	.string "Like, the WHOLE time! Doesn't that\l"
	.string "drive you nuts?!\p"
	.string "I tried it for a day. Walked into three\n"
	.string "trees and a Ponyta.\p"
	.string "It's got way more patience than me.\n"
	.string "Everybody does! Battle!$"

Nexus_Text_Barry_ChampionDefeat2:
	.string "Ow ow ow. Okay. That one I'll remember.$"

Nexus_Text_Barry_ChampionAfter2:
	.string "{SPEAKER NAME_BARRY}It knows everything, supposedly. Every\n"
	.string "single thing anybody ever knew.\p"
	.string "I asked it one question. Just one. It\n"
	.string "didn't answer. It just floated there,\l"
	.string "all polite, eyes shut.\p"
	.string "I think it was being nice. I think the\n"
	.string "answer would've hurt. …Anyway! GO!\l"
	.string "You're late!$"

Nexus_Text_Barry_ChampionIntro3:
	.string "Okay, rule! Before we battle, you tell\n"
	.string "me your name. Then I say it back. Then I\l"
	.string "write it down.\p"
	.string "It's not for me! It's for… uh. It's a\n"
	.string "lake thing. You wouldn't get it.\p"
	.string "There! Now I won't forget you!\n"
	.string "Probably! BATTLE!$"

Nexus_Text_Barry_ChampionDefeat3:
	.string "You're way too strong for somebody I\n"
	.string "just met. …We did just meet, right?$"

Nexus_Text_Barry_ChampionAfter3:
	.string "{SPEAKER NAME_BARRY}The thing in there doesn't steal\n"
	.string "memories. I thought it did. It just…\l"
	.string "holds on to them. Like a friend holding\l"
	.string "your bag.\p"
	.string "Mine's in there somewhere. Somebody's\n"
	.string "face. Somebody I was always chasing.\p"
	.string "If it gives it to you by accident, bring\n"
	.string "it here! I'll pay you! Ten million! …In\l"
	.string "installments!$"
```

</details>

Falante novo: `SP_NAME_BARRY` (ainda não existe em `include/constants/speaker_names.h`).

### Diário do Looker

📝 **Proposta de 30/09/2026, aguardando o autor.** Três páginas em [`diario_looker/barry/`](diario_looker/barry/) ([formato e fios](../DIARIO_LOOKER.md)): [`1_comeco.md`](diario_looker/barry/1_comeco.md), [`2_meio.md`](diario_looker/barry/2_meio.md), [`3_fim.md`](diario_looker/barry/3_fim.md). Labels `Nexus_Text_Diary_Barry_1` a `_3`.
