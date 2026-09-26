# Volkner

**Região da ficha:** Sinnoh

Aparece no checklist como:

- **Volkner — Elétrico** (Sinnoh · Líderes de Ginásio) — talentoso Líder de Sunyshore que busca um desafio verdadeiro.

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

📝 **Proposta de 26/09/2026, aguardando o autor.** `TRAINER_NEXUS_VOLKNER` em [`ULTRA_BEASTS.party`](../ULTRA_BEASTS.party). Segue R10–R13 (1 lendário, 1 semi-lendário, 1 Mega; 31 IV e 252 EV em tudo; nível pelo R2). O plano de jogo está em [`ULTRA_BEASTS.md`](../ULTRA_BEASTS.md) §3.4.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Zekrom | Life Orb | Teravolt | Adamant | Bolt Strike, Dragon Claw, Stone Edge, Dragon Dance |
| Raikou | Choice Specs | Pressure | Timid | Thunderbolt, Shadow Ball, Extrasensory, Volt Switch |
| Raichu | Electrite | Static | Timid | Fake Out, Thunderbolt, Grass Knot, Nasty Plot |
| Luxray | Choice Band | Intimidate | Adamant | Wild Charge, Crunch, Ice Fang, Play Rough |
| Electivire | Expert Belt | Motor Drive | Adamant | Wild Charge, Ice Punch, Cross Chop, Earthquake |
| Ambipom | Silk Scarf | Technician | Jolly | Fake Out, Double Hit, U-turn, Knock Off |

### Lendário associado

📝 **Proposta de 26/09/2026:** campeão da **Xurkitree** (UB-03 Lighting) no Nexus: a quinta luta, logo antes da boss battle. Por quê, e como é o fragmento: [`ULTRA_BEASTS.md`](../ULTRA_BEASTS.md) §3.4.

### Diálogo genérico

📝 **Proposta de 26/09/2026.** Quando Volkner cai numa das **quatro primeiras salas** (qualquer fragmento, qualquer lendário). Fala dele mesmo, sem citar o lugar nem a criatura do dia. Rótulos `Nexus_Text_Volkner_Intro` e `_Defeat` em [`ULTRA_BEASTS_TEXTS.inc`](../ULTRA_BEASTS_TEXTS.inc).

**Antes da luta**

> Huh. A challenger. Out here, of all places.
>
> I've been bored so long I stopped noticing where I was.
>
> Go on. Give me a reason to pay attention.

**Derrota**

> Ha… That's more like it. Now I'm awake.


### Diálogo associado ao lendário

📝 **Proposta de 26/09/2026.** Quando Volkner é o **campeão**, a luta logo antes da Xurkitree. Aqui a fala é sobre a criatura: o que Volkner viu nela, pelo olhar de quem é. Ninguém diz o nome da espécie. Rótulos `Nexus_Text_Volkner_ChampionIntro`, `_ChampionDefeat` e `_ChampionAfter`.

**Antes da luta**

> See that light up there? That's it. It's been drinking this city dry, one street at a time.
>
> I'd like to say I hate it. I'm the last guy who gets to.
>
> Back home I pulled so much power into my Gym that the whole town went dark. Just so I'd have something to do.
>
> So. Show me you're the kind of spark worth all that dark.

**Derrota**

> …Yeah. That's the kind. Worth every light in town.

**Depois da luta**

> That thing isn't cruel. It's hungry, and it found a whole city to eat.
>
> I get it. That's what scares me.
>
> Go pull the plug on it, challenger. I'll be here, learning to be bored in the dark.

