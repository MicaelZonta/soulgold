# Cyrus

**Região da ficha:** Sinnoh

Aparece no checklist como:

- **Cyrus** (Sinnoh · Team Galactic) — líder que pretende destruir o universo e criar um mundo sem emoções.

**Pronto para o Nexus:** ❌ não — tem sprite de overworld, falta o battle sprite (front pic), obrigatório.

**Arte disponível:** ✅ overworld (já registrado) e front pic em `.filetransfer/.trainers/Cyrus/`.

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
| `OBJ_EVENT_GFX_CYRUS` | `graphics/object_events/pics/people/special/cyrus.png` (32x32, 9 quadros, `sAnimTable_Standard`) |

Registrado em 30/09/2026. Origem em `.filetransfer/.trainers/Cyrus/`: `Sprite - RHcks.png` (autor **RHcks**), `Sprite - comparacao no jogo.png` e `outras/Folha completa - RHcks.jpg`.

### Battle sprite (front pic)

Não registrado no código. **Arte pronta** em `.filetransfer/.trainers/Cyrus/`:

- `Trainer - RHcks.png` (62x63, autor **RHcks**)
- `Trainer - comparacao no jogo.png` (comparação no jogo)

Falta registrar: skills `converter-sprite` (conferir/reduzir para 64x64, ≤16 cores) e `adicionar-grafico-trainer` (`TRAINER_PIC_FRONT_CYRUS`). Até lá o bloco do time usa uma **pic provisória** (ver abaixo).

### Field mugshot

Não existe (a pasta da arte não tem retrato). Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

Nenhuma. Ao criar, seguir a skill `adicionar-batalha-npc` (e `alocar-flag` se precisar de flag nova).

### Time das Rift Missions

📝 **Proposta de 30/09/2026, aguardando o autor.** `TRAINER_NEXUS_CYRUS` (ID **a alocar**: livre abaixo de 1056, nunca 1056–1163), campeão de Dialga. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega; 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler). Validado com `python3 dev_scripts/nexus_validar_time.py` (✓). **Pic provisória `Gentleman`** (o terno) até registrar a arte; classe `Mystery Man` (não há classe da Galactic).

Lendário **Dialga, Forma Origem** (Adamant Crystal), de que ele é campeão: a forma “original” de Legends: Arceus, para o homem que quis voltar o mundo ao começo e parou nele. Semi-lendário **Mesprit**, o Ser da Emoção que ele arrancou do Lago Verity para forjar a Red Chain — preso, no fragmento dele, numa redoma sobre a mesa. Mega **Gyarados** (Watertite; Mega Água/Sombrio), do time dele em Platinum. Mais **Weavile**, **Honchkrow** e **Crobat** (o Golbat dele desde o primeiro encontro), todos do time dele. O Houndoom sai: a Mega dele tem Solar Power e o time não tem sol.

*Plano (Singles):* frieza e controle. O Mesprit põe Stealth Rock e sai de U-turn; o Crobat usa Taunt e Tailwind; o Dialga “para” o mais rápido com Thunder Wave e bate com Draco Meteor e Earth Power; o Honchkrow de Super Luck + Scope Lens faz de todo Night Slash um crítico; a Mega Gyarados sobe Dragon Dance e limpa. Quando alguém importante cai, o Mesprit volta e usa Healing Wish — a emoção se sacrifica para curar a máquina.

*Plano (Doubles):* Fake Out do Weavile e Tailwind do Crobat no primeiro turno; o Intimidate do Gyarados na entrada; Sucker Punch do Honchkrow contra quem tentar bater primeiro; Healing Wish do Mesprit traz o Dialga de volta inteiro. Nenhum golpe do time acerta o parceiro.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Dialga-Origin | Adamant Crystal | Pressure | Modest | Draco Meteor, Flash Cannon, Earth Power, Thunder Wave |
| Mesprit | Sitrus Berry | Levitate | Bold | Stealth Rock, Psychic, U-turn, Healing Wish |
| Gyarados | Watertite | Intimidate | Adamant | Dragon Dance, Waterfall, Crunch, Ice Fang |
| Weavile | Life Orb | Pickpocket | Jolly | Fake Out, Knock Off, Icicle Crash, Ice Shard |
| Honchkrow | Scope Lens | Super Luck | Adamant | Brave Bird, Night Slash, Sucker Punch, Protect |
| Crobat | Black Sludge | Infiltrator | Jolly | Cross Poison, Taunt, Tailwind, U-turn |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>dev_scripts/nexus_validar_time.py</code>: trainerproc, constantes, learnsets e vagas)</summary>

```
=== TRAINER_NEXUS_CYRUS ===
Name: Cyrus
Class: Mystery Man
Pic: Gentleman
Gender: Male
Music: Dp Intense
Double Battle: No
AI: Smart Trainer

Dialga-Origin @ Adamant Crystal
Modest Nature
Level: 100
Ability: Pressure
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Draco Meteor
- Flash Cannon
- Earth Power
- Thunder Wave

Mesprit @ Sitrus Berry
Bold Nature
Level: 100
Ability: Levitate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Stealth Rock
- Psychic
- U-turn
- Healing Wish

Gyarados @ Watertite
Adamant Nature
Level: 100
Ability: Intimidate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Dragon Dance
- Waterfall
- Crunch
- Ice Fang

Weavile @ Life Orb
Jolly Nature
Level: 100
Ability: Pickpocket
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Fake Out
- Knock Off
- Icicle Crash
- Ice Shard

Honchkrow @ Scope Lens
Adamant Nature
Level: 100
Ability: Super Luck
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Brave Bird
- Night Slash
- Sucker Punch
- Protect

Crobat @ Black Sludge
Jolly Nature
Level: 100
Ability: Infiltrator
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Cross Poison
- Taunt
- Tailwind
- U-turn
```

</details>

### Lendário associado

#### Dialga

📝 **Proposta de 30/09/2026, aguardando o autor.** **Dialga**. O Cyrus é o campeão dele; quem cede é o **Spenser**, que fica com o Celebi (tabela de [`DIARIO_LOOKER.md`](../DIARIO_LOOKER.md)). Enquanto o autor não aprova, a ficha do Spenser e o código continuam como estão.

**Quem é.** Cyrus, chefe da Team Galactic em Diamond/Pearl/Platinum. Queria apagar o espírito do mundo e criar um universo novo, sem emoção; capturou o trio dos lagos, forjou a Red Chain com os cristais deles e convocou o Dialga (e o Palkia) em Spear Pillar. Cresceu em Veilstone, um menino brilhante que se fechou nas máquinas; o avô ainda mora lá.

**A criatura.** Dialga, o Pokémon temporal: dizem que o tempo avança enquanto o coração dele bate. Uma das divindades da criação de Sinnoh, parceiro do Palkia. A Forma Origem (Legends: Arceus) é a aparência dele no começo do mundo.

**O fragmento.** O salão de relógios que obedecem a um coração (`Nexus_Text_Dialga_Arrival`). No fragmento do Cyrus, a corrente segurou esse coração e o mundo parou ao meio-dia: Veilstone na chuva, cada gota presa no ar, cada pessoa no meio do passo. Só ele se move. Ele pediu um mundo sem espírito e ganhou uma pausa.

**Falas do fragmento** (narração; **já estão no jogo**, `Nexus_Text_Dialga_Arrival` e `Nexus_Text_Dialga_Boss` em `data/scripts/nexus.inc` — valem para qualquer campeão deste lendário e não mudam):

**Chegada**

> A stone hall full of clocks, each one keeping its own time.
>
> One ran fast. One ran slow. One had stopped centuries ago.
>
> Under the floor, a deep beat shook, and every hand on every clock trembled at once.

**Boss**

> The beat got louder, and closer, and the clocks began to agree with it.
>
> Something steel and blue stood at the end of the hall. Its chest glowed on every beat.

**Ficha do Looker** — **já existe no jogo**: `Nexus_EventScript_Dialga_LookerFile` → `Nexus_Text_Dialga_LookerFile` (`data/scripts/nexus.inc`). Não reescrita aqui; o texto atual, para referência:

> File L-483. Heartbeat.
>
> A hall where the clocks obey a heart, and an old man who would not ask it for one more minute.
>
> What came back with you has a small, quick heartbeat. The clock on my wall has started keeping time with it. I have decided not to mind.

O File L-483 foi escrito para o Spenser (“an old man who would not ask it for one more minute”). **Mantido como está**, a pedido — e ele cabe no fragmento do Cyrus sem mudar uma palavra: o velho que não pede nem um minuto a mais é o avô dele, parado no meio da frase. Se a troca for aprovada, vale conferir se o autor quer outra leitura.


### Diálogo genérico

📝 **Proposta de 30/09/2026, aguardando o autor.** Quando Cyrus cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala de si, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

Voz do Cyrus de DP/Pt: frio, educado, frases completas e sem pressa, vocabulário de engenheiro; trata emoção como defeito de fabricação. As três variações: a tese (o coração como máquina incompleta), o mundo parado dele (a solidão que ele não admite) e a infância desmontando relógios na casa do avô, em Veilstone.

**Antes da luta**

> I am Cyrus. I once believed the heart was an incomplete machine.
>
> Fear. Pride. Grief. Noise, which makes a person hesitate at the precise moment it matters.
>
> You seem hesitant. Allow me to correct that.

**Derrota**

> …Irregular. I will have to recalculate what I expected of you.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Cyrus_Intro:
	.string "I am Cyrus. I once believed the heart\n"
	.string "was an incomplete machine.\p"
	.string "Fear. Pride. Grief. Noise, which makes a\n"
	.string "person hesitate at the precise moment\l"
	.string "it matters.\p"
	.string "You seem hesitant. Allow me to correct\n"
	.string "that.$"

Nexus_Text_Cyrus_Defeat:
	.string "…Irregular. I will have to recalculate\n"
	.string "what I expected of you.$"
```

</details>

#### Variações 2 e 3 (📝 proposta de 30/09/2026)

**Variação 2** — o mundo parado de onde ele vem, contado como se fosse uma virtude

**Antes da luta**

> Where I come from, nothing moves. I arranged it that way. It is very quiet.
>
> People used to ask whether I was lonely. The question assumes loneliness is a flaw.
>
> I find it restful. …Let us see whether you are restful, too.

**Derrota**

> …You moved too much. It was difficult to predict you.

**Variação 3** — os relógios desmontados na casa do avô

**Antes da luta**

> As a child, I took apart every clock in my grandfather's house. I wanted to see where the time was kept.
>
> There was nothing inside. Gears. Springs. No time at all.
>
> I have been looking for it ever since. Perhaps it is in you.

**Derrota**

> …Nothing in you either. Only spirit. Hm.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Cyrus_Intro2:
	.string "Where I come from, nothing moves. I\n"
	.string "arranged it that way. It is very quiet.\p"
	.string "People used to ask whether I was\n"
	.string "lonely. The question assumes\l"
	.string "loneliness is a flaw.\p"
	.string "I find it restful. …Let us see whether\n"
	.string "you are restful, too.$"

Nexus_Text_Cyrus_Defeat2:
	.string "…You moved too much. It was difficult\n"
	.string "to predict you.$"

Nexus_Text_Cyrus_Intro3:
	.string "As a child, I took apart every clock in\n"
	.string "my grandfather's house. I wanted to\l"
	.string "see where the time was kept.\p"
	.string "There was nothing inside. Gears.\n"
	.string "Springs. No time at all.\p"
	.string "I have been looking for it ever since.\n"
	.string "Perhaps it is in you.$"

Nexus_Text_Cyrus_Defeat3:
	.string "…Nothing in you either. Only spirit. Hm.$"
```

</details>

### Diálogo associado ao lendário

📝 **Proposta de 30/09/2026, aguardando o autor.** Quando Cyrus é o **campeão**, a luta logo antes do lendário. A fala é sobre a criatura, sem dizer o nome dela ([R16](../NEXUS_REGRAS.md)).

#### Dialga

No fragmento do Cyrus, o plano de Spear Pillar deu certo pela metade: a corrente vermelha segurou o coração do tempo e ele pediu um mundo sem espírito. Ganhou uma pausa. Ele admira a criatura porque ela é a única coisa honesta que conhece — um relógio não liga para quem está atrasado ou de luto. A fissura: o avô parado no meio de uma frase para ele, e o medo de ouvir o fim. O texto do Looker File que já existe (“an old man who would not ask it for one more minute”) cabe neste fragmento sem mudar uma palavra, lido como o avô.

**Antes da luta**

> Its heart beats, and time advances. One beat, one moment. There is no other mechanism.
>
> I once held a chain to that heart and asked it to stop.
>
> It obeyed. You are standing in what remains.

**Derrota**

> …The beat skipped. Did you feel it?

**Depois da luta**

> A world without spirit requires a world without time. Nothing that changes can ever be perfect.
>
> So I stopped it. Everything I knew, perfectly still.
>
> …Go. It still beats in there, very slowly. I listen to it at night. I do not know why.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Cyrus_ChampionIntro:
	.string "Its heart beats, and time advances.\n"
	.string "One beat, one moment. There is no other\l"
	.string "mechanism.\p"
	.string "I once held a chain to that heart and\n"
	.string "asked it to stop.\p"
	.string "It obeyed. You are standing in what\n"
	.string "remains.$"

Nexus_Text_Cyrus_ChampionDefeat:
	.string "…The beat skipped. Did you feel it?$"

Nexus_Text_Cyrus_ChampionAfter:
	.string "{SPEAKER NAME_CYRUS}A world without spirit requires a world\n"
	.string "without time. Nothing that changes can\l"
	.string "ever be perfect.\p"
	.string "So I stopped it. Everything I knew,\n"
	.string "perfectly still.\p"
	.string "…Go. It still beats in there, very\n"
	.string "slowly. I listen to it at night. I do not\l"
	.string "know why.$"
```

</details>

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

**Variação 2** — a admiração pelo relógio honesto, que não atende pedidos

**Antes da luta**

> People fear it because it rules time. I never did. A clock is simply honest.
>
> It does not care who is late, who is grieving, who wants one more minute.
>
> It is the only thing I have ever admired. Show me you can face it without begging.

**Derrota**

> …You did not beg. Acceptable.

**Depois da luta**

> Everyone who stands before it wants something. Their youth. A second chance. One more minute with someone.
>
> I asked that nothing should ever happen again.
>
> It granted that. I suspect it was the easiest request it ever heard. …Go.

**Variação 3** — a dúvida: o avô parado no meio da frase

**Antes da luta**

> When time stopped, my grandfather was in the middle of a sentence. He was speaking to me.
>
> I do not know how it ends. I have stood in front of him for a very long time.
>
> One beat of that heart would finish the sentence. I have not asked. Battle me instead.

**Derrota**

> …That lasted longer than one beat. I noticed.

**Depois da luta**

> Do not tell it about my grandfather. It would only offer to help.
>
> The sentence begins, “Cyrus, you were always…” Always what. Always alone. Always wrong. Always…
>
> …Go. It has been waiting. It does not know how to do anything else. Neither do I.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Cyrus_ChampionIntro2:
	.string "People fear it because it rules time. I\n"
	.string "never did. A clock is simply honest.\p"
	.string "It does not care who is late, who is\n"
	.string "grieving, who wants one more minute.\p"
	.string "It is the only thing I have ever\n"
	.string "admired. Show me you can face it\l"
	.string "without begging.$"

Nexus_Text_Cyrus_ChampionDefeat2:
	.string "…You did not beg. Acceptable.$"

Nexus_Text_Cyrus_ChampionAfter2:
	.string "{SPEAKER NAME_CYRUS}Everyone who stands before it wants\n"
	.string "something. Their youth. A second\l"
	.string "chance. One more minute with someone.\p"
	.string "I asked that nothing should ever\n"
	.string "happen again.\p"
	.string "It granted that. I suspect it was the\n"
	.string "easiest request it ever heard. …Go.$"

Nexus_Text_Cyrus_ChampionIntro3:
	.string "When time stopped, my grandfather was\n"
	.string "in the middle of a sentence. He was\l"
	.string "speaking to me.\p"
	.string "I do not know how it ends. I have stood\n"
	.string "in front of him for a very long time.\p"
	.string "One beat of that heart would finish\n"
	.string "the sentence. I have not asked. Battle\l"
	.string "me instead.$"

Nexus_Text_Cyrus_ChampionDefeat3:
	.string "…That lasted longer than one beat. I\n"
	.string "noticed.$"

Nexus_Text_Cyrus_ChampionAfter3:
	.string "{SPEAKER NAME_CYRUS}Do not tell it about my grandfather. It\n"
	.string "would only offer to help.\p"
	.string "The sentence begins, “Cyrus, you were\n"
	.string "always…” Always what. Always alone.\l"
	.string "Always wrong. Always…\p"
	.string "…Go. It has been waiting. It does not\n"
	.string "know how to do anything else. Neither\l"
	.string "do I.$"
```

</details>

Falante novo: `SP_NAME_CYRUS` (ainda não existe em `include/constants/speaker_names.h`).

### Diário do Looker

📝 **Proposta de 30/09/2026, aguardando o autor.** Três páginas em [`diario_looker/cyrus/`](diario_looker/cyrus/) ([formato e fios](../DIARIO_LOOKER.md)): [`1_comeco.md`](diario_looker/cyrus/1_comeco.md), [`2_meio.md`](diario_looker/cyrus/2_meio.md), [`3_fim.md`](diario_looker/cyrus/3_fim.md). Labels `Nexus_Text_Diary_Cyrus_1` a `_3`.
