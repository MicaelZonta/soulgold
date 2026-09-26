# Bruno

**Região da ficha:** Kanto

Aparece no checklist como:

- **Bruno — Lutador** (Kanto · Elite Four e Campeões) — artista marcial que usa Pokémon Lutadores e resistentes.
- **Bruno — Lutador** (Johto · Elite Four e Campeão) — veterano que permanece na Elite Four entre as duas gerações.

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
| `OBJ_EVENT_GFX_BRUNO` | `graphics/object_events/pics/people/elite_four/bruno.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_ELITE_FOUR_BRUNO` | `graphics/trainers/front_pics/elite_four_bruno.png` |

### Field mugshot

| Constante | Arquivo |
|---|---|
| `MUGSHOT_BRUNO` | `graphics/field_mugshots/bruno.png` |

Aparece sozinho quando o objeto que fala usa o sprite acima (`GetFieldMugshotIdByObjectGraphicsId`, `src/field_mugshot.c`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_BRUNO_1` | 379 | 0x67B | Hitmontop Lv69, Staraptor Lv69, Gallade Lv69, Annihilape Lv70, Kommo O Lv70, Machamp Lv70 · *dupla* · VS: Yellow | `PokemonLeague_BrunosRoom`, `src/battle_setup.c` |
| `TRAINER_BRUNO_2` | 380 | 0x67C | Hitmontop Lv85, Staraptor Lv85, Gallade Lv85, Annihilape Lv85, Kommo O Lv85, Machamp Lv85 | `PokemonLeague_BrunosRoom`, `src/battle_setup.c` |

### Time das Rift Missions

📝 **Proposta de 26/09/2026, aguardando o autor.** `TRAINER_NEXUS_BRUNO` em [`ULTRA_BEASTS.party`](../ULTRA_BEASTS.party). Segue R10–R13 (1 lendário, 1 semi-lendário, 1 Mega; 31 IV e 252 EV em tudo; nível pelo R2). O plano de jogo está em [`ULTRA_BEASTS.md`](../ULTRA_BEASTS.md) §3.2.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Marshadow | Life Orb | Technician | Jolly | Spectral Thief, Close Combat, Shadow Sneak, Bulk Up |
| Urshifu | Choice Band | Unseen Fist | Adamant | Wicked Blow, Close Combat, Sucker Punch, U-turn |
| Heracross | Bugtite | Guts | Jolly | Pin Missile, Rock Blast, Close Combat, Swords Dance |
| Machamp | Leftovers | No Guard | Adamant | Dynamic Punch, Stone Edge, Knock Off, Bulk Up |
| Hitmontop | Assault Vest | Intimidate | Adamant | Fake Out, Close Combat, Sucker Punch, Rapid Spin |
| Hitmonlee | White Herb | Unburden | Jolly | Close Combat, Knock Off, Poison Jab, Mach Punch |

### Lendário associado

📝 **Proposta de 26/09/2026:** campeão da **Buzzwole** (UB-02 Absorption) no Nexus: a quinta luta, logo antes da boss battle. Por quê, e como é o fragmento: [`ULTRA_BEASTS.md`](../ULTRA_BEASTS.md) §3.2.

### Diálogo genérico

📝 **Proposta de 26/09/2026.** Quando Bruno cai numa das **quatro primeiras salas** (qualquer fragmento, qualquer lendário). Fala dele mesmo, sem citar o lugar nem a criatura do dia. Rótulos `Nexus_Text_Bruno_Intro` e `_Defeat` em [`ULTRA_BEASTS_TEXTS.inc`](../ULTRA_BEASTS_TEXTS.inc).

**Antes da luta**

> I woke in a strange place, so I did what I always do. I trained until the sun came up.
>
> There is no sun here. So I am still training.
>
> You will make a fine partner. Brace yourself!

**Derrota**

> Hoo hah! A good blow. I will remember it in my training.


### Diálogo associado ao lendário

📝 **Proposta de 26/09/2026.** Quando Bruno é o **campeão**, a luta logo antes da Buzzwole. Aqui a fala é sobre a criatura: o que Bruno viu nela, pelo olhar de quem é. Ninguém diz o nome da espécie. Rótulos `Nexus_Text_Bruno_ChampionIntro`, `_ChampionDefeat` e `_ChampionAfter`.

**Antes da luta**

> I have watched it for three days. It lifts nothing. It trains nothing. It poses, and it drinks.
>
> And it is stronger than any fighter I have ever faced.
>
> I do not hate it. It is only doing what it is. But I will not stand beside it and call that strength.
>
> Show me the other kind!

**Derrota**

> Hoo hah! Yes. That. It cannot drink that from anyone.

**Depois da luta**

> When it comes, it will flex first. It wants you to fear its size before it ever throws a punch.
>
> Do not look at the muscles. Look at the legs. Anything that strong still has to stand somewhere.
>
> Go. I will be here. Training.

