# Ramos

**Região da ficha:** Kalos

Aparece no checklist como:

- **Ramos — Grama** (Kalos · Líderes de Ginásio) — jardineiro veterano e Líder de Coumarine.

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

📝 **Proposta de 26/09/2026, aguardando o autor.** `TRAINER_NEXUS_RAMOS` em [`ULTRA_BEASTS.party`](../ULTRA_BEASTS.party). Segue R10–R13 (1 lendário, 1 semi-lendário, 1 Mega; 31 IV e 252 EV em tudo; nível pelo R2). O plano de jogo está em [`ULTRA_BEASTS.md`](../ULTRA_BEASTS.md) §3.6.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Xerneas | Power Herb | Fairy Aura | Modest | Geomancy, Moonblast, Grass Knot, Focus Blast |
| Celebi | Leftovers | Natural Cure | Bold | Giga Drain, Psychic, Recover, Leech Seed |
| Victreebel | Poisontite | Chlorophyll | Modest | Sludge Bomb, Leaf Storm, Sleep Powder, Sucker Punch |
| Gogoat | Sitrus Berry | Sap Sipper | Adamant | Horn Leech, Bulk Up, Earthquake, Milk Drink |
| Jumpluff | Focus Sash | Infiltrator | Jolly | Sleep Powder, Tailwind, Leech Seed, U-turn |
| Ferrothorn | Leftovers | Iron Barbs | Relaxed | Power Whip, Gyro Ball, Leech Seed, Spikes |

### Lendário associado

📝 **Proposta de 26/09/2026:** campeão da **Kartana** (UB-04 Blade) no Nexus: a quinta luta, logo antes da boss battle. Por quê, e como é o fragmento: [`ULTRA_BEASTS.md`](../ULTRA_BEASTS.md) §3.6.

### Diálogo genérico

📝 **Proposta de 26/09/2026.** Quando Ramos cai numa das **quatro primeiras salas** (qualquer fragmento, qualquer lendário). Fala dele mesmo, sem citar o lugar nem a criatura do dia. Rótulos `Nexus_Text_Ramos_Intro` e `_Defeat` em [`ULTRA_BEASTS_TEXTS.inc`](../ULTRA_BEASTS_TEXTS.inc).

**Antes da luta**

> Hoho! Now where has this old gardener wandered off to?
>
> Never mind, never mind. Wherever there's ground, something can grow. And wherever something grows, there's a sprout to test.
>
> Let's see how deep your roots go!

**Derrota**

> Hohoho! Deep roots, sprout. Deep roots.


### Diálogo associado ao lendário

📝 **Proposta de 26/09/2026.** Quando Ramos é o **campeão**, a luta logo antes da Kartana. Aqui a fala é sobre a criatura: o que Ramos viu nela, pelo olhar de quem é. Ninguém diz o nome da espécie. Rótulos `Nexus_Text_Ramos_ChampionIntro`, `_ChampionDefeat` e `_ChampionAfter`.

**Antes da luta**

> Thirty years with these shears, sprout. Want to know the secret?
>
> You never cut to hurt the tree. You cut so it grows back stronger.
>
> The little thing in this forest cuts better than I ever could. Clean. Perfect. Through steel, even.
>
> And not once has it let anything grow back. Show me something with roots!

**Derrota**

> Hohoho! Now that's growing, that is. Nothing here could trim that down.

**Depois da luta**

> It's light enough for the wind to carry, and sharp enough to halve a mountain.
>
> Don't try to be sharper than it, sprout. You'll lose.
>
> Be something that grows back. That's the one thing a blade can never finish.

