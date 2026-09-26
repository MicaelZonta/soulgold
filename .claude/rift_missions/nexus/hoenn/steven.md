# Steven Stone

**Região da ficha:** Hoenn

Aparece no checklist como:

- **Steven Stone — Campeão** (Hoenn · Elite Four e Campeões) — colecionador de pedras raras e especialista em Pokémon de Aço.

**Pronto para o Nexus:** ✅ sim — tem sprite e battle sprite.

## Checklist

- [x] Sprite de overworld *(obrigatório)*
- [x] Battle sprite / front pic *(obrigatório)*
- [x] Field mugshot (retrato na caixa de diálogo)
- [ ] Time para as Rift Missions definido
- [ ] Associado a um lendário
- [ ] Diálogo genérico escrito
- [ ] Diálogo associado ao lendário escrito

## Referências no repositório

### Sprite de overworld

| Constante | Arquivo |
|---|---|
| `OBJ_EVENT_GFX_STEVEN` | `graphics/object_events/pics/people/steven.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_STEVEN` | `graphics/trainers/front_pics/steven.png` |

### Field mugshot

| Constante | Arquivo |
|---|---|
| `MUGSHOT_STEVEN` | `graphics/field_mugshots/steven.png` |

Aparece sozinho quando o objeto que fala usa o sprite acima (`GetFieldMugshotIdByObjectGraphicsId`, `src/field_mugshot.c`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_STEVEN2` | 568 | 0x738 | **sem time** (ID reservado, sem bloco no `.party`) | — (nenhum script chama) |
| `TRAINER_STEVEN` | 804 | 0x824 | Gholdengo Lv84, Aggron Lv85, Cradily Lv85, Excadrill Lv85, Archeops Lv85, Metagross Lv86 · *dupla* · VS: Purple | `Kitakami_Houses`, `MeteorFalls_StevensCave`, `src/achievements.c`, `src/battle_dome.c` |
| `TRAINER_TITLE_DEFENSE_STEVEN` | 878 | 0x86E | Gholdengo Lv84, Aggron Lv85, Cradily Lv85, Excadrill Lv85, Archeops Lv85, Metagross Lv86 · *dupla* · VS: Purple | `src/title_defense.c` |

### Time das Rift Missions

📝 **Proposta de 26/09/2026, aguardando o autor.** `TRAINER_NEXUS_STEVEN` em [`ULTRA_BEASTS.party`](../ULTRA_BEASTS.party). Segue R10–R13 (1 lendário, 1 semi-lendário, 1 Mega; 31 IV e 252 EV em tudo; nível pelo R2). O plano de jogo está em [`ULTRA_BEASTS.md`](../ULTRA_BEASTS.md) §3.5.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Deoxys | Life Orb | Pressure | Naive | Psycho Boost, Knock Off, Ice Beam, Stealth Rock |
| Jirachi | Leftovers | Serene Grace | Careful | Iron Head, Body Slam, Wish, U-turn |
| Metagross | Steeltite | Clear Body | Jolly | Meteor Mash, Zen Headbutt, Earthquake, Bullet Punch |
| Skarmory | Rocky Helmet | Sturdy | Impish | Spikes, Tailwind, Brave Bird, Roost |
| Claydol | Light Clay | Levitate | Bold | Stealth Rock, Earth Power, Reflect, Light Screen |
| Cradily | Leftovers | Storm Drain | Careful | Giga Drain, Rock Slide, Recover, Toxic |

### Lendário associado

📝 **Proposta de 26/09/2026:** campeão da **Celesteela** (UB-04 Blaster) no Nexus: a quinta luta, logo antes da boss battle. Por quê, e como é o fragmento: [`ULTRA_BEASTS.md`](../ULTRA_BEASTS.md) §3.5.

### Diálogo genérico

📝 **Proposta de 26/09/2026.** Quando Steven cai numa das **quatro primeiras salas** (qualquer fragmento, qualquer lendário). Fala dele mesmo, sem citar o lugar nem a criatura do dia. Rótulos `Nexus_Text_Steven_Intro` e `_Defeat` em [`ULTRA_BEASTS_TEXTS.inc`](../ULTRA_BEASTS_TEXTS.inc).

**Antes da luta**

> Oh -- hello. I was looking at the stones here. They're nothing like the ones back home.
>
> Every stone has a history, and so does every Trainer. I'd like to know yours.
>
> Shall we?

**Derrota**

> A fine battle. I'll keep it the way I keep a rare stone.


### Diálogo associado ao lendário

📝 **Proposta de 26/09/2026.** Quando Steven é o **campeão**, a luta logo antes da Celesteela. Aqui a fala é sobre a criatura: o que Steven viu nela, pelo olhar de quem é. Ninguém diz o nome da espécie. Rótulos `Nexus_Text_Steven_ChampionIntro`, `_ChampionDefeat` e `_ChampionAfter`.

**Antes da luta**

> All my life, I've collected what the sky let fall. Meteorites. Shards. Small pieces of somewhere else.
>
> The creature here goes the other way. It burns a forest to lift itself off the ground, and it never comes back down.
>
> I can't decide if it's running from something, or going home.
>
> …Forgive me. You didn't come here to listen to me think. Let's battle.

**Derrota**

> Your Pokémon kept their feet on the ground the whole time. I admire that more than I can say.

**Depois da luta**

> If it takes off while you're near it, don't chase it. Nothing can follow something like that.
>
> Stop it before it leaves. Or let it leave. Both are answers.
>
> I'll stay a while. Something that high up might drop a stone for me, sooner or later.

