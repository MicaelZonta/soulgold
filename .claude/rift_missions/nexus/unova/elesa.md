# Elesa

**Região da ficha:** Unova

Aparece no checklist como:

- **Elesa — Elétrico** (Unova · Líderes de Ginásio) — modelo famosa e Líder de Nimbasa.

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

📝 **Proposta de 26/09/2026, aguardando o autor.** `TRAINER_NEXUS_ELESA` em [`ULTRA_BEASTS.party`](../ULTRA_BEASTS.party). Segue R10–R13 (1 lendário, 1 semi-lendário, 1 Mega; 31 IV e 252 EV em tudo; nível pelo R2). O plano de jogo está em [`ULTRA_BEASTS.md`](../ULTRA_BEASTS.md) §3.3.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Miraidon | Choice Specs | Hadron Engine | Timid | Electro Drift, Draco Meteor, Volt Switch, Dazzling Gleam |
| Zapdos | Leftovers | Static | Timid | Tailwind, Thunderbolt, Hurricane, Roost |
| Eelektross | Electrite | Levitate | Modest | Thunderbolt, Flamethrower, Giga Drain, Knock Off |
| Zebstrika | Life Orb | Sap Sipper | Jolly | Supercell Slam, High Horsepower, Flame Charge, Volt Switch |
| Galvantula | Focus Sash | Compound Eyes | Timid | Sticky Web, Thunder, Bug Buzz, Energy Ball |
| Emolga | Light Clay | Motor Drive | Timid | Nuzzle, Encore, Light Screen, U-turn |

### Lendário associado

📝 **Proposta de 26/09/2026:** campeão da **Pheromosa** (UB-02 Beauty) no Nexus: a quinta luta, logo antes da boss battle. Por quê, e como é o fragmento: [`ULTRA_BEASTS.md`](../ULTRA_BEASTS.md) §3.3.

### Diálogo genérico

📝 **Proposta de 26/09/2026.** Quando Elesa cai numa das **quatro primeiras salas** (qualquer fragmento, qualquer lendário). Fala dele mesmo, sem citar o lugar nem a criatura do dia. Rótulos `Nexus_Text_Elesa_Intro` e `_Defeat` em [`ULTRA_BEASTS_TEXTS.inc`](../ULTRA_BEASTS_TEXTS.inc).

**Antes da luta**

> No stage, no lights, no audience. This is the strangest runway I've ever walked.
>
> Well. I never stop in the middle of a show.
>
> You'll have to be my audience -- and my opponent. Try to keep up!

**Derrota**

> You made me forget my pose. Nobody does that.


### Diálogo associado ao lendário

📝 **Proposta de 26/09/2026.** Quando Elesa é o **campeão**, a luta logo antes da Pheromosa. Aqui a fala é sobre a criatura: o que Elesa viu nela, pelo olhar de quem é. Ninguém diz o nome da espécie. Rótulos `Nexus_Text_Elesa_ChampionIntro`, `_ChampionDefeat` e `_ChampionAfter`.

**Antes da luta**

> I've seen it. From a distance -- it won't allow anything closer.
>
> It moves like the only clean thing left in the world, and it looks at everything else like a stain.
>
> Everyone who sees it stops and stares. I know that look. I've been on the other side of it my whole career.
>
> …Enough. Battle me. And don't you dare just stand there staring.

**Derrota**

> You never stared once. You were too busy fighting. …Good.

**Depois da luta**

> People think being admired is the same as being loved. It isn't. It's lonelier.
>
> That creature has never been touched by anything in its life, and it thinks that's perfection.
>
> Go show it what it's missing. Get your hands dirty.

