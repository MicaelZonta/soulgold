# Fantina

**Região da ficha:** Sinnoh

Aparece no checklist como:

- **Fantina — Fantasma** (Sinnoh · Líderes de Ginásio) — coordenadora e Líder de Hearthome com estilo teatral.

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

📝 **Proposta de 26/09/2026, aguardando o autor.** `TRAINER_NEXUS_FANTINA`, campeão da Blacephalon. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler).

Lendário **Hoopa**, o gênio travesso que tira coisas dos anéis, um mágico de palco; semi-lendário **Meloetta**, a cantora que passa para a forma de dança com Relic Song; Mega **Chandelure** (Ghostite: Fantasma/Fogo como a Blacephalon, Infiltrator). Mais **Mismagius** (o ás dela em Diamond/Pearl), Oricorio-Sensu e Drifblim. *Plano:* o espetáculo. O Drifblim põe Tailwind, o Oricorio-Sensu (Dancer) copia toda dança do campo em Doubles, a Meloetta dança, e Mismagius e Hoopa atacam. A fraqueza a Sombrio e Fantasma é o risco do número.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Hoopa | Choice Specs | Magician | Modest | Hyperspace Hole, Shadow Ball, Focus Blast, Trick |
| Meloetta | Life Orb | Serene Grace | Modest | Relic Song, Psychic, Shadow Ball, Calm Mind |
| Chandelure | Ghostite | Flash Fire | Modest | Shadow Ball, Flamethrower, Energy Ball, Protect |
| Mismagius | Life Orb | Levitate | Timid | Nasty Plot, Shadow Ball, Mystical Fire, Dazzling Gleam |
| Oricorio-Sensu | Leftovers | Dancer | Timid | Revelation Dance, Quiver Dance, Hurricane, Roost |
| Drifblim | Sitrus Berry | Unburden | Calm | Tailwind, Shadow Ball, Will-O-Wisp, Destiny Bond |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>trainerproc</code>, constantes, learnsets e categorias)</summary>

```
=== TRAINER_NEXUS_FANTINA ===
Name: Fantina
Class: Leader
Pic: Fantina
Gender: Female
Music: Dp Artist
Double Battle: No
AI: Smart Trainer

Hoopa @ Choice Specs
Modest Nature
Level: 100
Ability: Magician
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Hyperspace Hole
- Shadow Ball
- Focus Blast
- Trick

Meloetta @ Life Orb
Modest Nature
Level: 100
Ability: Serene Grace
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Relic Song
- Psychic
- Shadow Ball
- Calm Mind

Chandelure @ Ghostite
Modest Nature
Level: 100
Ability: Flash Fire
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Shadow Ball
- Flamethrower
- Energy Ball
- Protect

Mismagius @ Life Orb
Timid Nature
Level: 100
Ability: Levitate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Nasty Plot
- Shadow Ball
- Mystical Fire
- Dazzling Gleam

Oricorio-Sensu @ Leftovers
Timid Nature
Level: 100
Ability: Dancer
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Revelation Dance
- Quiver Dance
- Hurricane
- Roost

Drifblim @ Sitrus Berry
Calm Nature
Level: 100
Ability: Unburden
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Tailwind
- Shadow Ball
- Will-O-Wisp
- Destiny Bond
```

</details>


### Lendário associado

📝 **Proposta de 26/09/2026, aguardando o autor.** **Blacephalon** (UB Burst). Fantina é o campeão dela: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Fantina, líder de Hearthome, "a dançarina sedutora e cheia de alma", estrela de concursos, com Pokémon Fantasma.

**A criatura.** Blacephalon baixa a guarda do alvo com o andar esquisito, detona a própria cabeça sem aviso e rouba a vitalidade dele. É um palhaço de fogos de artifício.

**O fragmento.** Um teatro vazio, com cada poltrona ocupada por uma sombra. Fogos estouram no alto sem som. A cada estouro, as sombras nas poltronas ficam mais fracas.

**Falas do fragmento** (narração e Looker; tocam só nos dias desta UB):

**Chegada**

> An empty theatre, every seat filled with shadow.
>
> Fireworks burst overhead without a sound. Each time one went off, the shadows in the seats grew fainter.

**Boss**

> The curtain rose on an empty stage.
>
> Something walked out with a strange, careless step. It bowed deeply, and its head began to glow.

**Ficha do Looker, no altar, no dia em que a UB é capturada**

> File UB Burst.
>
> A performer who charms its audience, blows its own head off, and takes their strength while they clap.
>
> I have been to theatre like that. I did not know it was a species.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Burst_Arrival:
	.string "An empty theatre, every seat filled\n"
	.string "with shadow.\p"
	.string "Fireworks burst overhead without a\n"
	.string "sound. Each time one went off, the\l"
	.string "shadows in the seats grew fainter.$"

Nexus_Text_Burst_Boss:
	.string "The curtain rose on an empty stage.\p"
	.string "Something walked out with a strange,\n"
	.string "careless step. It bowed deeply, and its\l"
	.string "head began to glow.$"

Nexus_Text_Burst_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File UB Burst.\p"
	.string "A performer who charms its audience,\n"
	.string "blows its own head off, and takes their\l"
	.string "strength while they clap.\p"
	.string "I have been to theatre like that. I did\n"
	.string "not know it was a species.$"
```

</details>


### Diálogo genérico

📝 **Proposta de 26/09/2026, aguardando o autor.** Quando Fantina cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala dele mesmo, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

**Antes da luta**

> Bonjour! Ah, a new stage, a new audience!
>
> I do not know this place, but it does not matter. Wherever I am, I dance.
>
> Allez! Let us make this battle beautiful!

**Derrota**

> Magnifique! You danced better than me! …Non, I will not say that twice.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Fantina_Intro:
	.string "Bonjour! Ah, a new stage, a new\n"
	.string "audience!\p"
	.string "I do not know this place, but it does\n"
	.string "not matter. Wherever I am, I dance.\p"
	.string "Allez! Let us make this battle\n"
	.string "beautiful!$"

Nexus_Text_Fantina_Defeat:
	.string "Magnifique! You danced better than me!\n"
	.string "…Non, I will not say that twice.$"
```

</details>


### Diálogo associado ao lendário

📝 **Proposta de 26/09/2026, aguardando o autor.** Quando Fantina é o **campeão**, a luta logo antes da Blacephalon. A fala é sobre a criatura, sem dizer o nome dela.

A Fantina fala da criatura como de uma colega de palco: dança mal de propósito para você rir, você ri e se inclina, e aí, *boum*, ela tira a vida da plateia e faz uma reverência. A Fantina também tira o fôlego do público, mas devolve. A vitória: o jogador assistiu ao show inteiro sem se perder. O que fica: um bom artista dá tudo e o público sai com mais do que trouxe; aquela lá só tira e chama isso de aplauso. "Quando ela se curvar para você, não aplauda. Não se incline. Só termine o show."

**Antes da luta**

> Ah, you have met the star of this theatre? Such charm! Such timing!
>
> It dances badly on purpose, so you laugh. When you laugh, you lean in. And when you lean in… boum.
>
> Then it takes the life right out of its audience, and bows.
>
> I also take a crowd's breath away, mon ami. But I give it back! Come -- let me show you how a real show ends!

**Derrota**

> Bravo! You watched the whole show and never lost yourself.

**Depois da luta**

> A good performer gives everything, and the audience goes home with more than it brought.
>
> That one takes, and takes, and calls it applause.
>
> When it bows to you, do not clap. Do not lean in. Just end the show.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Fantina_ChampionIntro:
	.string "Ah, you have met the star of this\n"
	.string "theatre? Such charm! Such timing!\p"
	.string "It dances badly on purpose, so you\n"
	.string "laugh. When you laugh, you lean in. And\l"
	.string "when you lean in… boum.\p"
	.string "Then it takes the life right out of its\n"
	.string "audience, and bows.\p"
	.string "I also take a crowd's breath away, mon\n"
	.string "ami. But I give it back! Come -- let me\l"
	.string "show you how a real show ends!$"

Nexus_Text_Fantina_ChampionDefeat:
	.string "Bravo! You watched the whole show and\n"
	.string "never lost yourself.$"

Nexus_Text_Fantina_ChampionAfter:
	.string "{SPEAKER NAME_FANTINA}A good performer gives everything, and\n"
	.string "the audience goes home with more than\l"
	.string "it brought.\p"
	.string "That one takes, and takes, and calls it\n"
	.string "applause.\p"
	.string "When it bows to you, do not clap. Do not\n"
	.string "lean in. Just end the show.$"
```

</details>

