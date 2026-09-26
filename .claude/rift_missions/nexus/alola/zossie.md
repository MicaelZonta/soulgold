# Zossie

**Região da ficha:** Alola

Aparece no checklist como:

- **Zossie** (Alola · Ultra Recon Squad) — jovem e curiosa parceira de Dulse.

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

📝 **Proposta de 26/09/2026, aguardando o autor.** `TRAINER_NEXUS_ZOSSIE` em [`ULTRA_BEASTS.party`](../ULTRA_BEASTS.party). Segue R10–R13 (1 lendário, 1 semi-lendário, 1 Mega; 31 IV e 252 EV em tudo; nível pelo R2). O plano de jogo está em [`ULTRA_BEASTS.md`](../ULTRA_BEASTS.md) §3.8.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Magearna | Leftovers | Soul-Heart | Modest | Fleur Cannon, Flash Cannon, Aura Sphere, Ice Beam |
| Mew | Leftovers | Synchronize | Timid | Psychic, Nasty Plot, Tailwind, Will-O-Wisp |
| Clefable | Fairytite | Magic Guard | Bold | Moonblast, Follow Me, Moonlight, Thunder Wave |
| Mimikyu | Life Orb | Disguise | Jolly | Play Rough, Shadow Claw, Shadow Sneak, Swords Dance |
| Ribombee | Focus Sash | Shield Dust | Timid | Sticky Web, Moonblast, Pollen Puff, Stun Spore |
| Goodra | Assault Vest | Gooey | Modest | Draco Meteor, Sludge Bomb, Fire Blast, Thunderbolt |

### Lendário associado

📝 **Proposta de 26/09/2026:** campeão da **Poipole** (UB Adhesive) no Nexus: a quinta luta, logo antes da boss battle. Por quê, e como é o fragmento: [`ULTRA_BEASTS.md`](../ULTRA_BEASTS.md) §3.8.

### Diálogo genérico

📝 **Proposta de 26/09/2026.** Quando Zossie cai numa das **quatro primeiras salas** (qualquer fragmento, qualquer lendário). Fala dele mesmo, sem citar o lugar nem a criatura do dia. Rótulos `Nexus_Text_Zossie_Intro` e `_Defeat` em [`ULTRA_BEASTS_TEXTS.inc`](../ULTRA_BEASTS_TEXTS.inc).

**Antes da luta**

> Hiii! Wait, where am I? It's not dark, so it's definitely not home!
>
> You're a Trainer, right? Battle me! Please please please!

**Derrota**

> Aww! You're really good! Can we be friends now? That's how it works, right?


### Diálogo associado ao lendário

📝 **Proposta de 26/09/2026.** Quando Zossie é o **campeão**, a luta logo antes da Poipole. Aqui a fala é sobre a criatura: o que Zossie viu nela, pelo olhar de quem é. Ninguém diz o nome da espécie. Rótulos `Nexus_Text_Zossie_ChampionIntro`, `_ChampionDefeat` e `_ChampionAfter`.

**Antes da luta**

> There's a little one hiding up in the lights. It's been following me around all day!
>
> It's poisonous, you know. Its whole head is a needle. But it only sticks to people it likes.
>
> I think it likes me! …And I think it wants to see if it likes you.
>
> So let's show it a really, really good battle!

**Derrota**

> Aww… It liked that! It liked you! I could tell!

**Depois da luta**

> Where I'm from, it was dark for so long. We forgot what it feels like when something small and bright just… wants to be near you.
>
> It's going to come say hi. It might sting a little. That's just how it says hello!
>
> Be gentle with it, okay? Promise.

