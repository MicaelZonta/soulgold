# Fantina

**Região da ficha:** Sinnoh

Aparece no checklist como:

- **Fantina — Fantasma** (Sinnoh · Líderes de Ginásio) — coordenadora e Líder de Hearthome com estilo teatral.

**Pronto para o Nexus:** ✅ sim — tem sprite e battle sprite.

## Checklist

- [x] Sprite de overworld *(obrigatório)*
- [x] Battle sprite / front pic *(obrigatório)*
- [ ] Field mugshot (retrato na caixa de diálogo)
- [x] Time para as Rift Missions definido
- [x] Associado a um lendário
- [x] Diálogo genérico escrito
- [x] Diálogo associado ao lendário escrito

## Referências no repositório

### Sprite de overworld

| Constante | Arquivo |
|---|---|
| `OBJ_EVENT_GFX_FANTINA` | `graphics/object_events/pics/people/special/fantina.png` |

32x32, doze quadros (`sAnimTable_StandardAsym`, igual à Lusamine). Convertido em 26/09/2026 da arte em `.filetransfer/`.

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_FANTINA` | `graphics/trainers/front_pics/fantina.png` |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

Nenhuma. Ao criar, seguir a skill `adicionar-batalha-npc` (e `alocar-flag` se precisar de flag nova).

### Time das Rift Missions

✅ **Implementado em 26/09/2026** (a proposta abaixo virou código): `TRAINER_NEXUS_FANTINA` = **984** (flag de batalha `0x8D8`, limpa antes e depois de cada luta), bloco em `src/data/trainers.party`, nível pelo `sNexusTrainerIds` (`src/data/level_scaling_rules.h`, R2). Falas e lutas em `data/scripts/nexus.inc`: `Nexus_EventScript_Fantina_Fight` (genérica) e `Nexus_EventScript_Fantina_ChampionFight` (campeão), sem blackout, resultado em `VAR_TEMP_3`. Para testar: menu de debug → Rift Missions… → Nexus fights… → Fantina.

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

✅ **Aprovado em 26/09/2026:** a fala de campeão implementada (`Nexus_EventScript_Fantina_ChampionFight`) é sobre este lendário. O sorteio do Daily que usa a ligação ainda não existe.

**Proposta de 26/09/2026:** **Blacephalon** (UB Burst). Fantina é o campeão dela: a quinta luta do Daily, logo antes da boss battle.

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

**Looker File** — ✅ implementado em 27/09/2026 como **caderno no chão da sala do campeão** ([R18](../NEXUS_REGRAS.md)), descrevendo o universo do fragmento. O texto do jogo foi reescrito e está em `data/scripts/nexus.inc` (`Nexus_Text_<Conceito>_LookerFile`) — ele vence o rascunho abaixo, que era a versão antiga "no altar, no dia da captura".

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

✅ **Implementado em 26/09/2026:** `Nexus_EventScript_Fantina_Fight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

**Proposta de 26/09/2026:** Quando Fantina cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala dele mesmo, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

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


#### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mesma regra da variação 1 ([R16](../NEXUS_REGRAS.md)): fala de si, sem citar o lugar nem a criatura do dia. Cada variação pega um ângulo diferente do personagem.

**Variação 2 — a cidade quente.** Hearthome (sem nome), a cidade onde estranhos se abraçam na rua. Aqui não tem rua, então ela aquece o jogador do jeito dela.

**Antes da luta**

> Ah, mon ami, you look cold! Where I come from, the whole city is warm. Strangers hug in the street!
>
> Here there is no street. So I will warm you up another way!
>
> Allez, allez! On with the show!

**Derrota**

> Ooh! You have warmed me up instead. C'est pas juste!

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Fantina_Intro2:
	.string "Ah, mon ami, you look cold! Where I come\n"
	.string "from, the whole city is warm. Strangers\l"
	.string "hug in the street!\p"
	.string "Here there is no street. So I will warm\n"
	.string "you up another way!\p"
	.string "Allez, allez! On with the show!$"

Nexus_Text_Fantina_Defeat2:
	.string "Ooh! You have warmed me up instead.\n"
	.string "C'est pas juste!$"
```

</details>

**Variação 3 — o homem de sobretudo.** Aceno leve ao fio do sobretudo (DIARIO_LOOKER): um homem de casaco comprido disse que ela dança como um fantasma. Ela tomou como elogio.

**Antes da luta**

> Hmm! A strange man in a long coat told me I dance like a ghost.
>
> I think he meant it as a warning. I took it as a compliment! My Pokémon are ghosts, after all.
>
> Now! Let us see if you can catch one!

**Derrota**

> Oh là là! You caught me. Nobody catches me!

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Fantina_Intro3:
	.string "Hmm! A strange man in a long coat told\n"
	.string "me I dance like a ghost.\p"
	.string "I think he meant it as a warning. I took\n"
	.string "it as a compliment! My Pokémon are\l"
	.string "ghosts, after all.\p"
	.string "Now! Let us see if you can catch one!$"

Nexus_Text_Fantina_Defeat3:
	.string "Oh là là! You caught me. Nobody catches\n"
	.string "me!$"
```

</details>



### Diálogo associado ao lendário

✅ **Implementado em 26/09/2026:** `Nexus_EventScript_Fantina_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

**Proposta de 26/09/2026:** Quando Fantina é o **campeão**, a luta logo antes da Blacephalon. A fala é sobre a criatura, sem dizer o nome dela.

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

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mesma regra da variação 1: sobre a criatura, pelo olhar dele, sem dizer o nome da espécie. Labels no padrão `Nexus_Text_Fantina_Champion*` + sufixo.

**Variação 2 — ciúme de palco.** A Fantina admite ciúme: a criatura lota todas as poltronas, toda noite, e ela precisou de vinte anos e um figurino muito bom. O conselho vem dos bastidores: todo truque tem o instante em que o mágico olha para o outro lado.

**Antes da luta**

> I will be honest with you, mon ami. I am jealous.
>
> That one fills every seat. Every night! The crowd cannot look away, even when it knows what is coming.
>
> Me, I needed twenty years, a hundred Contests, and a very good costume.
>
> Hmph! Jealousy is bad for the skin. Let us battle instead!

**Derrota**

> Ahh… Now I am not jealous. I am inspired!

**Depois da luta**

> A little secret from backstage: every trick has a moment where the magician must look away.
>
> When it lights its head, it cannot see you. Just for one breath.
>
> That is your moment. Do not waste it on applause.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Fantina_ChampionIntro2:
	.string "I will be honest with you, mon ami. I am\n"
	.string "jealous.\p"
	.string "That one fills every seat. Every night!\n"
	.string "The crowd cannot look away, even when\l"
	.string "it knows what is coming.\p"
	.string "Me, I needed twenty years, a hundred\n"
	.string "Contests, and a very good costume.\p"
	.string "Hmph! Jealousy is bad for the skin. Let\n"
	.string "us battle instead!$"

Nexus_Text_Fantina_ChampionDefeat2:
	.string "Ahh… Now I am not jealous. I am\n"
	.string "inspired!$"

Nexus_Text_Fantina_ChampionAfter2:
	.string "{SPEAKER NAME_FANTINA}A little secret from backstage: every\n"
	.string "trick has a moment where the magician\l"
	.string "must look away.\p"
	.string "When it lights its head, it cannot see\n"
	.string "you. Just for one breath.\p"
	.string "That is your moment. Do not waste it on\n"
	.string "applause.$"
```

</details>

**Variação 3 — fileira quatro, poltrona doze.** A perda: um senhor que ia a todos os shows e ria primeiro. Na noite da criatura ele riu primeiro de novo, e se inclinou primeiro. Hoje a poltrona dele tem só uma sombra, que ainda se inclina. Ela dança para as sombras para que não sumam de vez.

**Antes da luta**

> Row four, seat twelve. An old man came to every one of my shows. He always laughed first.
>
> The night it came, he laughed first again. He was the first to lean in.
>
> Tonight his seat holds only a shadow. It still leans forward.
>
> …Pardon. The show must go on. Allez!

**Derrota**

> Bravo… He would have laughed at that. The good kind.

**Depois da luta**

> I dance for the shadows every night. It keeps them from fading all the way.
>
> I do not know if they can see me. I think they can. They lean in.
>
> End its show, mon ami. Maybe then the house lights come up at last.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Fantina_ChampionIntro3:
	.string "Row four, seat twelve. An old man came\n"
	.string "to every one of my shows. He always\l"
	.string "laughed first.\p"
	.string "The night it came, he laughed first\n"
	.string "again. He was the first to lean in.\p"
	.string "Tonight his seat holds only a shadow. It\n"
	.string "still leans forward.\p"
	.string "…Pardon. The show must go on. Allez!$"

Nexus_Text_Fantina_ChampionDefeat3:
	.string "Bravo… He would have laughed at that.\n"
	.string "The good kind.$"

Nexus_Text_Fantina_ChampionAfter3:
	.string "{SPEAKER NAME_FANTINA}I dance for the shadows every night. It\n"
	.string "keeps them from fading all the way.\p"
	.string "I do not know if they can see me. I\n"
	.string "think they can. They lean in.\p"
	.string "End its show, mon ami. Maybe then the\n"
	.string "house lights come up at last.$"
```

</details>

