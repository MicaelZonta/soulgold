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

📝 **Proposta de 26/09/2026, aguardando o autor.** `TRAINER_NEXUS_GUZMA` em [`ULTRA_BEASTS.party`](../ULTRA_BEASTS.party). Segue R10–R13 (1 lendário, 1 semi-lendário, 1 Mega; 31 IV e 252 EV em tudo; nível pelo R2). O plano de jogo está em [`ULTRA_BEASTS.md`](../ULTRA_BEASTS.md) §3.7.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Yveltal | Life Orb | Dark Aura | Naive | Dark Pulse, Oblivion Wing, Heat Wave, Sucker Punch |
| Buzzwole | Leftovers | Beast Boost | Adamant | Leech Life, Drain Punch, Ice Punch, Bulk Up |
| Golisopod | Bugtite | Emergency Exit | Adamant | First Impression, Liquidation, Leech Life, Knock Off |
| Ariados | Focus Sash | Insomnia | Jolly | Sticky Web, Toxic Spikes, Poison Jab, Sucker Punch |
| Scizor | Choice Band | Technician | Adamant | Bullet Punch, U-turn, Knock Off, Superpower |
| Vikavolt | Choice Specs | Levitate | Modest | Thunderbolt, Bug Buzz, Energy Ball, Volt Switch |

### Lendário associado

📝 **Proposta de 26/09/2026:** campeão da **Guzzlord** (UB-05 Glutton) no Nexus: a quinta luta, logo antes da boss battle. Por quê, e como é o fragmento: [`ULTRA_BEASTS.md`](../ULTRA_BEASTS.md) §3.7.

### Diálogo genérico

📝 **Proposta de 26/09/2026.** Quando Guzma cai numa das **quatro primeiras salas** (qualquer fragmento, qualquer lendário). Fala dele mesmo, sem citar o lugar nem a criatura do dia. Rótulos `Nexus_Text_Guzma_Intro` e `_Defeat` em [`ULTRA_BEASTS_TEXTS.inc`](../ULTRA_BEASTS_TEXTS.inc).

**Antes da luta**

> You lost, kid? Yeah. Me too.
>
> Don't matter where I end up. Wherever Guzma goes, stuff gets broken.
>
> Might as well start with you!

**Derrota**

> …Tch. Figures. Even here, huh.


### Diálogo associado ao lendário

📝 **Proposta de 26/09/2026.** Quando Guzma é o **campeão**, a luta logo antes da Guzzlord. Aqui a fala é sobre a criatura: o que Guzma viu nela, pelo olhar de quem é. Ninguém diz o nome da espécie. Rótulos `Nexus_Text_Guzma_ChampionIntro`, `_ChampionDefeat` e `_ChampionAfter`.

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

