# Soliera

**Região da ficha:** Alola

Aparece no checklist como:

- **Soliera** (Alola · Ultra Recon Squad) — comandante da equipe encontrada principalmente em *Ultra Moon*.

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

📝 **Proposta de 26/09/2026, aguardando o autor.** `TRAINER_NEXUS_SOLIERA` em [`ULTRA_BEASTS.party`](../ULTRA_BEASTS.party). Segue R10–R13 (1 lendário, 1 semi-lendário, 1 Mega; 31 IV e 252 EV em tudo; nível pelo R2). O plano de jogo está em [`ULTRA_BEASTS.md`](../ULTRA_BEASTS.md) §3.9.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Eternatus | Life Orb | Pressure | Timid | Dynamax Cannon, Sludge Bomb, Flamethrower, Recover |
| Latios | Choice Specs | Levitate | Timid | Draco Meteor, Luster Purge, Aura Sphere, Surf |
| Beedrill | Bugtite | Sniper | Jolly | Poison Jab, Fell Stinger, U-turn, Drill Run |
| Crobat | Sitrus Berry | Infiltrator | Jolly | Tailwind, Brave Bird, Cross Poison, Taunt |
| Dragapult | Choice Band | Clear Body | Jolly | Dragon Darts, Phantom Force, U-turn, Sucker Punch |
| Drapion | Leftovers | Battle Armor | Careful | Knock Off, Poison Jab, Toxic Spikes, Swords Dance |

### Lendário associado

📝 **Proposta de 26/09/2026:** campeão da **Naganadel** (UB Stinger) no Nexus: a quinta luta, logo antes da boss battle. Por quê, e como é o fragmento: [`ULTRA_BEASTS.md`](../ULTRA_BEASTS.md) §3.9.

### Diálogo genérico

📝 **Proposta de 26/09/2026.** Quando Soliera cai numa das **quatro primeiras salas** (qualquer fragmento, qualquer lendário). Fala dele mesmo, sem citar o lugar nem a criatura do dia. Rótulos `Nexus_Text_Soliera_Intro` e `_Defeat` em [`ULTRA_BEASTS_TEXTS.inc`](../ULTRA_BEASTS_TEXTS.inc).

**Antes da luta**

> Identify yourself. …No matter.
>
> I do not know how I arrived here. My orders have not changed.
>
> Obstacles are removed. Prepare yourself.

**Derrota**

> Understood. Obstacle not removed. Adjusting.


### Diálogo associado ao lendário

📝 **Proposta de 26/09/2026.** Quando Soliera é o **campeão**, a luta logo antes da Naganadel. Aqui a fala é sobre a criatura: o que Soliera viu nela, pelo olhar de quem é. Ninguém diz o nome da espécie. Rótulos `Nexus_Text_Soliera_ChampionIntro`, `_ChampionDefeat` e `_ChampionAfter`.

**Antes da luta**

> It has passed over this tower eleven times. I have counted.
>
> It is faster than anything in our records, and it carries enough venom to fell a city. Every pass comes lower.
>
> In my world, we gave a small one like it to someone who helped us. I was the one who handed it over.
>
> I never learned what it became. …Perhaps I am about to. Prepare yourself.

**Derrota**

> My strike missed. I will not ask for a second.

**Depois da luta**

> If that is what it grew into, then someone raised it well. Or no one did.
>
> I cannot tell which from here. You will be close enough to see.
>
> Watch the needle. It points before it strikes. That is the only warning it gives.

