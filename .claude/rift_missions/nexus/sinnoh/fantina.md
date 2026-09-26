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

📝 **Proposta de 26/09/2026, aguardando o autor.** `TRAINER_NEXUS_FANTINA` em [`ULTRA_BEASTS.party`](../ULTRA_BEASTS.party). Segue R10–R13 (1 lendário, 1 semi-lendário, 1 Mega; 31 IV e 252 EV em tudo; nível pelo R2). O plano de jogo está em [`ULTRA_BEASTS.md`](../ULTRA_BEASTS.md) §3.11.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Hoopa | Choice Specs | Magician | Modest | Hyperspace Hole, Shadow Ball, Focus Blast, Trick |
| Meloetta | Life Orb | Serene Grace | Modest | Relic Song, Psychic, Shadow Ball, Calm Mind |
| Chandelure | Ghostite | Flash Fire | Modest | Shadow Ball, Flamethrower, Energy Ball, Protect |
| Mismagius | Life Orb | Levitate | Timid | Nasty Plot, Shadow Ball, Mystical Fire, Dazzling Gleam |
| Oricorio-Sensu | Leftovers | Dancer | Timid | Revelation Dance, Quiver Dance, Hurricane, Roost |
| Drifblim | Sitrus Berry | Unburden | Calm | Tailwind, Shadow Ball, Will-O-Wisp, Destiny Bond |

### Lendário associado

📝 **Proposta de 26/09/2026:** campeão da **Blacephalon** (UB Burst) no Nexus: a quinta luta, logo antes da boss battle. Por quê, e como é o fragmento: [`ULTRA_BEASTS.md`](../ULTRA_BEASTS.md) §3.11.

### Diálogo genérico

📝 **Proposta de 26/09/2026.** Quando Fantina cai numa das **quatro primeiras salas** (qualquer fragmento, qualquer lendário). Fala dele mesmo, sem citar o lugar nem a criatura do dia. Rótulos `Nexus_Text_Fantina_Intro` e `_Defeat` em [`ULTRA_BEASTS_TEXTS.inc`](../ULTRA_BEASTS_TEXTS.inc).

**Antes da luta**

> Bonjour! Ah, a new stage, a new audience!
>
> I do not know this place, but it does not matter. Wherever I am, I dance.
>
> Allez! Let us make this battle beautiful!

**Derrota**

> Magnifique! You danced better than me! …Non, I will not say that twice.


### Diálogo associado ao lendário

📝 **Proposta de 26/09/2026.** Quando Fantina é o **campeão**, a luta logo antes da Blacephalon. Aqui a fala é sobre a criatura: o que Fantina viu nela, pelo olhar de quem é. Ninguém diz o nome da espécie. Rótulos `Nexus_Text_Fantina_ChampionIntro`, `_ChampionDefeat` e `_ChampionAfter`.

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

