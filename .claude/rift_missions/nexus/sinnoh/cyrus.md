# Cyrus

**Região da ficha:** Sinnoh

Aparece no checklist como:

- **Cyrus** (Sinnoh · Team Galactic) — líder que pretende destruir o universo e criar um mundo sem emoções.

**Pronto para o Nexus:** ✅ sim — no pool desde 31/10/2026 (lote novo, bloco 2 de IDs).

**Arte disponível:** ✅ overworld (já registrado) e front pic em `.filetransfer/.trainers/Cyrus/`.

## Checklist

- [x] Sprite de overworld *(obrigatório)*
- [x] Battle sprite / front pic *(obrigatório)* — 📦 arte pronta em `.filetransfer`, falta registrar
- [ ] Field mugshot (retrato na caixa de diálogo)
- [x] Time para as Rift Missions definido — 📝 proposta abaixo (30/09/2026)
- [x] Associado a um lendário — 📝 proposta abaixo (30/09/2026)
- [x] Diálogo genérico escrito — 📝 proposta abaixo (30/09/2026)
- [x] Diálogo associado ao lendário escrito — 📝 proposta abaixo (30/09/2026)

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

✅ **Implementado em 31/10/2026** (lote novo, time montado pelo Codex e conferido pelo `novos/integrar.py`: R10–R13 e habilidades): `TRAINER_NEXUS_CYRUS` = **1175** (bloco 2, flag `0xB0B`), luta genérica `Nexus_EventScript_Cyrus_Fight` em `data/scripts/nexus.inc`, linha em `src/data/nexus/trainers.h`. Ainda não é campeão de nenhum lendário.

```
=== TRAINER_NEXUS_CYRUS ===
Name: Cyrus
Class: Pkmn Trainer 1
Pic: Cyrus
Gender: Male
Music: Male
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

### Lendário associado

✅ **Campeão extra desde 31/10/2026** (lendário com vários campeões; o do dia é sorteado, `src/data/nexus/champions.h`; associações e falas montadas pelo Codex):

- **Dialga** — `Nexus_EventScript_Cyrus_Dialga_ChampionFight` (falas `Nexus_Text_Cyrus_Dialga_Champion*`)
- **Palkia** — `Nexus_EventScript_Cyrus_Palkia_ChampionFight` (falas `Nexus_Text_Cyrus_Palkia_Champion*`)
- **Mesprit** — `Nexus_EventScript_Cyrus_Mesprit_ChampionFight` (falas `Nexus_Text_Cyrus_Mesprit_Champion*`)


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

✅ **Implementado em 31/10/2026:** `Nexus_Text_Cyrus_Intro` / `_Defeat` em `data/scripts/nexus.inc`.

**Antes da luta**

> I am Cyrus. I once believed the heart was an incomplete machine.
>
> Fear. Pride. Grief. Noise, which makes a person hesitate at the precise moment it matters.
>
> You seem hesitant. Allow me to correct that.

**Derrota**

> ...Irregular. I will have to recalculate what I expected of you.

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
