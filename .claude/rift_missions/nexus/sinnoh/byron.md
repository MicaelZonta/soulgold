# Byron

**Região da ficha:** Sinnoh

Aparece no checklist como:

- **Byron — Aço** (Sinnoh · Líderes de Ginásio) — Líder de Canalave e pai de Roark.

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

📝 **Proposta de 26/09/2026, aguardando o autor.** `TRAINER_NEXUS_BYRON` em [`ULTRA_BEASTS.party`](../ULTRA_BEASTS.party). Segue R10–R13 (1 lendário, 1 semi-lendário, 1 Mega; 31 IV e 252 EV em tudo; nível pelo R2). O plano de jogo está em [`ULTRA_BEASTS.md`](../ULTRA_BEASTS.md) §3.10.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Zamazenta | Rusted Shield | Dauntless Shield | Impish | Body Press, Iron Defense, Iron Head, Crunch |
| Registeel | Leftovers | Clear Body | Careful | Iron Head, Body Press, Stealth Rock, Thunder Wave |
| Steelix | Steeltite | Sturdy | Brave | Earthquake, Heavy Slam, Rock Slide, Curse |
| Bastiodon | Custap Berry | Sturdy | Relaxed | Body Press, Iron Defense, Metal Burst, Wide Guard |
| Bronzong | Mental Herb | Levitate | Sassy | Trick Room, Gyro Ball, Hypnosis, Reflect |
| Tyranitar | Smooth Rock | Sand Stream | Brave | Rock Slide, Crunch, Earthquake, Low Kick |

### Lendário associado

📝 **Proposta de 26/09/2026:** campeão da **Stakataka** (UB Assembly) no Nexus: a quinta luta, logo antes da boss battle. Por quê, e como é o fragmento: [`ULTRA_BEASTS.md`](../ULTRA_BEASTS.md) §3.10.

### Diálogo genérico

📝 **Proposta de 26/09/2026.** Quando Byron cai numa das **quatro primeiras salas** (qualquer fragmento, qualquer lendário). Fala dele mesmo, sem citar o lugar nem a criatura do dia. Rótulos `Nexus_Text_Byron_Intro` e `_Defeat` em [`ULTRA_BEASTS_TEXTS.inc`](../ULTRA_BEASTS_TEXTS.inc).

**Antes da luta**

> Hah! No idea how I ended up here, but there's stone under my boots, so I'm not complaining!
>
> I'm a miner, youngster. Hard rock, hard steel, hard battles.
>
> Let's see what you're made of!

**Derrota**

> Hah! Solid! You'd make a fine miner.


### Diálogo associado ao lendário

📝 **Proposta de 26/09/2026.** Quando Byron é o **campeão**, a luta logo antes da Stakataka. Aqui a fala é sobre a criatura: o que Byron viu nela, pelo olhar de quem é. Ninguém diz o nome da espécie. Rótulos `Nexus_Text_Byron_ChampionIntro`, `_ChampionDefeat` e `_ChampionAfter`.

**Antes da luta**

> Youngster, I've spent my whole life cutting stone out of mountains. I know rock.
>
> That wall over there isn't rock. Every brick of it is alive. A hundred and fifty, near as I can count, each one holding up the next.
>
> My son and I can't agree on how to stack a shelf. These things built a fortress together.
>
> Hah! Let's see if you and your team hold together half as well!

**Derrota**

> Hah! Now THAT'S a team that holds! Not a crack in it!

**Depois da luta**

> When it comes, don't hunt for the weak brick. There isn't one. They share the load.
>
> Hit the whole wall. Hit it with everything you've got, all at once.
>
> …Then maybe go home and call your family. I'm going to call mine.

