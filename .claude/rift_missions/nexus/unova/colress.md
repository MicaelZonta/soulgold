# Colress

**Região da ficha:** Unova

Aparece no checklist como:

- **Colress** (Unova · Team Plasma) — cientista interessado em descobrir como liberar o potencial máximo dos Pokémon.

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

📝 **Proposta de 26/09/2026, aguardando o autor.** `TRAINER_NEXUS_COLRESS` em [`ULTRA_BEASTS.party`](../ULTRA_BEASTS.party). Segue R10–R13 (1 lendário, 1 semi-lendário, 1 Mega; 31 IV e 252 EV em tudo; nível pelo R2). O plano de jogo está em [`ULTRA_BEASTS.md`](../ULTRA_BEASTS.md) §3.1.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Genesect | Choice Scarf | Download | Naive | U-turn, Iron Head, Thunderbolt, Flamethrower |
| Iron Hands | Assault Vest | Quark Drive | Adamant | Fake Out, Drain Punch, Wild Charge, Ice Punch |
| Golurk | Groundite | No Guard | Adamant | Earthquake, Shadow Punch, Ice Punch, Drain Punch |
| Klinklang | Sitrus Berry | Clear Body | Adamant | Shift Gear, Gear Grind, Wild Charge, Protect |
| Magnezone | Choice Specs | Magnet Pull | Modest | Thunderbolt, Flash Cannon, Volt Switch, Tri Attack |
| Porygon-Z | Life Orb | Adaptability | Timid | Tri Attack, Shadow Ball, Ice Beam, Nasty Plot |

### Lendário associado

📝 **Proposta de 26/09/2026:** campeão da **Nihilego** (UB-01 Symbiont) no Nexus: a quinta luta, logo antes da boss battle. Por quê, e como é o fragmento: [`ULTRA_BEASTS.md`](../ULTRA_BEASTS.md) §3.1.

### Diálogo genérico

📝 **Proposta de 26/09/2026.** Quando Colress cai numa das **quatro primeiras salas** (qualquer fragmento, qualquer lendário). Fala dele mesmo, sem citar o lugar nem a criatura do dia. Rótulos `Nexus_Text_Colress_Intro` e `_Defeat` em [`ULTRA_BEASTS_TEXTS.inc`](../ULTRA_BEASTS_TEXTS.inc).

**Antes da luta**

> Ah! A test subject. Forgive me -- a challenger.
>
> I don't remember how I arrived here, and I find I don't mind. A new place is only a new set of conditions.
>
> My question is the same one I always ask: what draws out a Pokémon's true strength? Let's collect another answer!

**Derrota**

> Remarkable. I am going to need a larger notebook.


### Diálogo associado ao lendário

📝 **Proposta de 26/09/2026.** Quando Colress é o **campeão**, a luta logo antes da Nihilego. Aqui a fala é sobre a criatura: o que Colress viu nela, pelo olhar de quem é. Ninguém diz o nome da espécie. Rótulos `Nexus_Text_Colress_ChampionIntro`, `_ChampionDefeat` e `_ChampionAfter`.

**Antes da luta**

> You feel it too, don't you? Something in the water, deciding whether to let us in.
>
> I have been observing it. It does not attack. It offers.
>
> Whatever it touches grows stronger and forgets how to stop. It is everything I ever set out to find…
>
> …and I find I do not enjoy watching it. Before it chooses you, show me what your Pokémon are without it!

**Derrota**

> …There. That was their own strength, every last point of it. No toxin could have measured that.

**Depois da luta**

> I spent years trying to take away a Pokémon's limits. It took that creature to show me what a limit is for.
>
> It will offer you strength. It will be very generous about it.
>
> Refuse. I say that as a man who would have said yes.

