# Guzma

**Região da ficha:** Alola

Aparece no checklist como:

- **Guzma** (Alola · Team Skull e Aether Foundation) — chefe carismático do Team Skull e especialista em Pokémon Inseto.

**Pronto para o Nexus:** ❌ não — falta sprite de overworld e battle sprite (os dois são obrigatórios).

## Checklist

- [ ] Sprite de overworld *(obrigatório)*
- [ ] Battle sprite / front pic *(obrigatório)*
- [ ] Field mugshot (retrato na caixa de diálogo)
- [ ] Time para as Rift Missions definido
- [ ] Associado a um lendário
- [ ] Diálogo genérico escrito
- [ ] Diálogo associado ao lendário escrito

## Referências no repositório

### Sprite de overworld

Não existe. Criar com a skill `adicionar-npc`.

### Battle sprite (front pic)

Não existe. Criar com a skill `adicionar-grafico-trainer`.

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

Nenhuma. Ao criar, seguir a skill `adicionar-batalha-npc` (e `alocar-flag` se precisar de flag nova).

### Time das Rift Missions

📝 **Proposta de 26/09/2026, aguardando o autor.** `TRAINER_NEXUS_GUZMA`, campeão da Guzzlord. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler).

Lendário **Yveltal**, o Pokémon da destruição; semi-lendário **Buzzwole**, a outra UB de Inseto, que vive de exibir força, o espelho do Guzma; Mega **Golisopod** (Bugtite: Inseto/Aço), o ás dele. Mais Ariados, Scizor e Vikavolt, do time dele em Sun/Moon. *Plano:* destruição sem freio. O Ariados lança Sticky Web e Toxic Spikes, o Yveltal bate com Dark Aura e Life Orb, Scizor e Vikavolt entram de Choice, e o Buzzwole sobe com Bulk Up.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Yveltal | Life Orb | Dark Aura | Naive | Dark Pulse, Oblivion Wing, Heat Wave, Sucker Punch |
| Buzzwole | Leftovers | Beast Boost | Adamant | Leech Life, Drain Punch, Ice Punch, Bulk Up |
| Golisopod | Bugtite | Emergency Exit | Adamant | First Impression, Liquidation, Leech Life, Knock Off |
| Ariados | Focus Sash | Insomnia | Jolly | Sticky Web, Toxic Spikes, Poison Jab, Sucker Punch |
| Scizor | Choice Band | Technician | Adamant | Bullet Punch, U-turn, Knock Off, Superpower |
| Vikavolt | Choice Specs | Levitate | Modest | Thunderbolt, Bug Buzz, Energy Ball, Volt Switch |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>trainerproc</code>, constantes, learnsets e categorias)</summary>

```
=== TRAINER_NEXUS_GUZMA ===
Name: Guzma
Class: Expert
Pic: Guzma
Gender: Male
Music: Intense
Double Battle: No
AI: Smart Trainer

Yveltal @ Life Orb
Naive Nature
Level: 100
Ability: Dark Aura
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Dark Pulse
- Oblivion Wing
- Heat Wave
- Sucker Punch

Buzzwole @ Leftovers
Adamant Nature
Level: 100
Ability: Beast Boost
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Leech Life
- Drain Punch
- Ice Punch
- Bulk Up

Golisopod @ Bugtite
Adamant Nature
Level: 100
Ability: Emergency Exit
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- First Impression
- Liquidation
- Leech Life
- Knock Off

Ariados @ Focus Sash
Jolly Nature
Level: 100
Ability: Insomnia
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Sticky Web
- Toxic Spikes
- Poison Jab
- Sucker Punch

Scizor @ Choice Band
Adamant Nature
Level: 100
Ability: Technician
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Bullet Punch
- U-turn
- Knock Off
- Superpower

Vikavolt @ Choice Specs
Modest Nature
Level: 100
Ability: Levitate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Thunderbolt
- Bug Buzz
- Energy Ball
- Volt Switch
```

</details>


### Lendário associado

📝 **Proposta de 26/09/2026, aguardando o autor.** **Guzzlord** (UB-05 Glutton). Guzma é o campeão dela: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Guzma, chefe da Team Skull. Foi aprendiz do Hala junto com o Kukui, perdeu para o Kukui, teve negado o posto de Trial Captain e fez da destruição a própria identidade.

**A criatura.** Guzzlord já devorou montanhas e engoliu prédios inteiros, e parece estar sempre comendo. Mundo em USUM: Ultra Ruin, uma cidade em ruínas.

**O fragmento.** Uma cidade, ou o que sobrou dela. Metade dos prédios não caiu: sumiu, como se tivesse sido mordida. Longe, alguma coisa ainda mastiga.

**Falas do fragmento** (narração e Looker; tocam só nos dias desta UB):

**Chegada**

> A city, or what was left of one.
>
> Half the buildings were gone. Not fallen. Missing, as if bitten off.
>
> Somewhere far away, something was still chewing.

**Boss**

> The chewing stopped.
>
> A mouth that was most of a body turned toward you, and the street in front of it was simply not there anymore.

**Ficha do Looker, no altar, no dia em que a UB é capturada**

> File UB-05. Glutton.
>
> A city eaten down to the street, and a young man sitting in it who used to think that was what strength looked like.
>
> He does not think so now. I have written that down for him, in case he ever asks.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Glutton_Arrival:
	.string "A city, or what was left of one.\p"
	.string "Half the buildings were gone. Not\n"
	.string "fallen. Missing, as if bitten off.\p"
	.string "Somewhere far away, something was still\n"
	.string "chewing.$"

Nexus_Text_Glutton_Boss:
	.string "The chewing stopped.\p"
	.string "A mouth that was most of a body turned\n"
	.string "toward you, and the street in front of\l"
	.string "it was simply not there anymore.$"

Nexus_Text_Glutton_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File UB-05. Glutton.\p"
	.string "A city eaten down to the street, and a\n"
	.string "young man sitting in it who used to\l"
	.string "think that was what strength looked\l"
	.string "like.\p"
	.string "He does not think so now. I have written\n"
	.string "that down for him, in case he ever asks.$"
```

</details>


### Diálogo genérico

📝 **Proposta de 26/09/2026, aguardando o autor.** Quando Guzma cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala dele mesmo, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

**Antes da luta**

> You lost, kid? Yeah. Me too.
>
> Don't matter where I end up. Wherever Guzma goes, stuff gets broken.
>
> Might as well start with you!

**Derrota**

> …Tch. Figures. Even here, huh.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Guzma_Intro:
	.string "You lost, kid? Yeah. Me too.\p"
	.string "Don't matter where I end up. Wherever\n"
	.string "Guzma goes, stuff gets broken.\p"
	.string "Might as well start with you!$"

Nexus_Text_Guzma_Defeat:
	.string "…Tch. Figures. Even here, huh.$"
```

</details>


### Diálogo associado ao lendário

📝 **Proposta de 26/09/2026, aguardando o autor.** Quando Guzma é o **campeão**, a luta logo antes da Guzzlord. A fala é sobre a criatura, sem dizer o nome dela.

O Guzma viu a boca comer um prédio, e depois o seguinte. Em casa diziam que ele era a destruição andando em duas pernas, e ele gostava. Até ver aquilo mastigar uma cidade inteira e continuar com fome, e não achar graça nenhuma. A derrota é a dele de sempre ("tudo o que eu tenho, e ainda não basta"). O que fica é o que ninguém conta: quem destrói tudo não fica satisfeito depois, só fica parado numa bagunça maior. O Kukui disse isso uma vez, sobre ele, e o Guzma demorou para ouvir.

**Antes da luta**

> You seen it? That big mouth down the road? It ate a building while I watched. Then it ate the next one.
>
> Folks back home used to say I was destruction walkin' around on two legs. I kinda liked it.
>
> Then I watched that thing chew through a whole city and still look hungry.
>
> …It ain't fun to watch. Let's just go!

**Derrota**

> Again. Everything I got, and it still ain't enough.

**Depois da luta**

> Here's what nobody tells ya. When you wreck everything, you ain't full after. You're just standin' in a bigger mess.
>
> That thing's never gonna be full. Not ever.
>
> Kukui told me that once. About me. Took me a long time to hear it.
>
> Go on. Go show that mouth what enough looks like.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Guzma_ChampionIntro:
	.string "You seen it? That big mouth down the\n"
	.string "road? It ate a building while I watched.\l"
	.string "Then it ate the next one.\p"
	.string "Folks back home used to say I was\n"
	.string "destruction walkin' around on two legs.\l"
	.string "I kinda liked it.\p"
	.string "Then I watched that thing chew through\n"
	.string "a whole city and still look hungry.\p"
	.string "…It ain't fun to watch. Let's just go!$"

Nexus_Text_Guzma_ChampionDefeat:
	.string "Again. Everything I got, and it still\n"
	.string "ain't enough.$"

Nexus_Text_Guzma_ChampionAfter:
	.string "{SPEAKER NAME_GUZMA}Here's what nobody tells ya. When you\n"
	.string "wreck everything, you ain't full after.\l"
	.string "You're just standin' in a bigger mess.\p"
	.string "That thing's never gonna be full. Not\n"
	.string "ever.\p"
	.string "Kukui told me that once. About me. Took\n"
	.string "me a long time to hear it.\p"
	.string "Go on. Go show that mouth what enough\n"
	.string "looks like.$"
```

</details>

