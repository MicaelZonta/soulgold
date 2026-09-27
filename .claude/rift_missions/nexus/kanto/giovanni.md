# Giovanni

**Região da ficha:** Kanto

Aparece no checklist como:

- **Giovanni — Terra** (Kanto · Líderes de Ginásio) — Líder de Viridian e chefe do Team Rocket.
- **Giovanni** (Kanto · Team Rocket) — líder do sindicato criminoso que explora Pokémon em busca de poder e lucro.

**Pronto para o Nexus:** ✅ sim — tem sprite e battle sprite.

## Checklist

- [x] Sprite de overworld *(obrigatório)*
- [x] Battle sprite / front pic *(obrigatório)*
- [ ] Field mugshot (retrato na caixa de diálogo)
- [ ] Time para as Rift Missions definido
- [x] Associado a um lendário
- [ ] Diálogo genérico escrito
- [ ] Diálogo associado ao lendário escrito

## Referências no repositório

### Sprite de overworld

| Constante | Arquivo |
|---|---|
| `OBJ_EVENT_GFX_GIOVANNI` | `graphics/object_events/pics/people/rockets/giovanni.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_GIOVANNI` | `graphics/trainers/front_pics/giovanni.png` |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_GIOVANNI` | 95 | 0x55F | Kangaskhan Lv60, Honchkrow Lv61, Nidoqueen Lv61, Persian Lv61, Ursaluna Lv60, Nidoking Lv62 | `src/battle_dome.c` |

### Time das Rift Missions

📝 **Proposta de 27/09/2026, aguardando o autor.** `TRAINER_NEXUS_GIOVANNI`, campeão de Mewtwo e Genesect. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler). `Double Battle: No` é o formato em que o time brilha mais; o plano vale nos dois.

Lendário **Mewtwo**, a arma que foi feita para ser a mais forte e não aceitou dono: o que o chefe da Team Rocket mais quis ter. O Genesect, a outra criatura de que ele é campeão, também é lendário (R10), então não cabe junto; fica nas falas. Semi-lendário **Mew**, o original de onde o Mewtwo foi feito. Mega **Kangaskhan** (Normalite), a assinatura dele desde o Red/Blue e do time de campanha. Mais **Nidoking** (o ás de Terra dele), **Rhyperior** (o Rhydon do ginásio de Viridian, evoluído) e **Persian**, o gato do chefe. *Plano (Singles):* o Mew arma Stealth Rock e queima com Will-O-Wisp, o Persian pivota com Taunt e U-turn, o Mewtwo sobe Calm Mind, e Nidoking (Sheer Force + Life Orb) e Rhyperior (Solid Rock, Weakness Policy) batem. *Plano (Doubles):* Fake Out do Persian mais Tailwind do Mew no primeiro turno; a Mega Kangaskhan (Parental Bond) bate Sucker Punch e Double-Edge; o Rhyperior usa Rock Slide nos dois e Protect; o Nidoking usa Earth Power, de alvo único, para não acertar o parceiro.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Mewtwo | Leftovers | Pressure | Timid | Psystrike, Aura Sphere, Ice Beam, Calm Mind |
| Mew | Mental Herb | Synchronize | Timid | Stealth Rock, Will-O-Wisp, Tailwind, Knock Off |
| Kangaskhan | Normalite | Scrappy | Adamant | Double-Edge, Sucker Punch, Drain Punch, Ice Punch |
| Nidoking | Life Orb | Sheer Force | Timid | Earth Power, Sludge Wave, Ice Beam, Flamethrower |
| Rhyperior | Weakness Policy | Solid Rock | Adamant | High Horsepower, Rock Slide, Megahorn, Protect |
| Persian | Focus Sash | Technician | Jolly | Fake Out, Knock Off, U-turn, Taunt |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>dev_scripts/nexus_validar_time.py</code>)</summary>

```
=== TRAINER_NEXUS_GIOVANNI ===
Name: Giovanni
Class: RocketA
Pic: Giovanni
Gender: Male
Music: Rocket
Double Battle: No
AI: Smart Trainer

Mewtwo @ Leftovers
Timid Nature
Level: 100
Ability: Pressure
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Psystrike
- Aura Sphere
- Ice Beam
- Calm Mind

Mew @ Mental Herb
Timid Nature
Level: 100
Ability: Synchronize
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Stealth Rock
- Will-O-Wisp
- Tailwind
- Knock Off

Kangaskhan @ Normalite
Adamant Nature
Level: 100
Ability: Scrappy
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Double-Edge
- Sucker Punch
- Drain Punch
- Ice Punch

Nidoking @ Life Orb
Timid Nature
Level: 100
Ability: Sheer Force
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Earth Power
- Sludge Wave
- Ice Beam
- Flamethrower

Rhyperior @ Weakness Policy
Adamant Nature
Level: 100
Ability: Solid Rock
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- High Horsepower
- Rock Slide
- Megahorn
- Protect

Persian @ Focus Sash
Jolly Nature
Level: 100
Ability: Technician
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Fake Out
- Knock Off
- U-turn
- Taunt
```

</details>


### Lendário associado

**Mewtwo** ou **Genesect** — exemplo aprovado no design (`SOULGOLD_RIFT_MISSIONS_DESIGN.md` §10, "Estrutura do loop": "Giovanni podendo anteceder Mewtwo ou Genesect"). Aprovado só como associação; nada implementado. As fichas abaixo são a proposta de fragmento e falas para cada um.

#### Mewtwo

📝 **Proposta de 27/09/2026, aguardando o autor.** **Mewtwo**. Giovanni é o campeão dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Giovanni, chefe da Team Rocket e Líder de Viridian. Perdeu para uma criança, desfez a Team Rocket e sumiu; os homens dele passaram anos esperando que voltasse.

**A criatura.** Mewtwo, o Pokémon genético. Criado por cientistas a partir do Mew, numa mansão em Cinnabar, para ser o Pokémon mais forte do mundo. Os diários da mansão dizem que ele ficou poderoso demais para ser controlado; fugiu e foi viver na Cerulean Cave.

**O fragmento.** Uma mansão queimada numa ilha de cinza. Os corredores têm tanques de vidro, todos quebrados de dentro para fora. Páginas de diário rasgadas rolam pelo chão.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário). Pelo [R17](../NEXUS_REGRAS.md), o que o jogador leva é o fragmento que sobra, no nível 1; a ficha do Looker fala desse pedaço, não da criatura domada.

**Chegada**

> A burnt mansion on an island of ash. Its halls were lined with glass tanks, every one cracked open from the inside.
>
> Torn journal pages drifted across the floor. The last one read: 'We could not control it.'

**Boss**

> Every loose page in the mansion lifted off the floor at once and hung in the air.
>
> At the end of the hall, something pale was floating, and it had been waiting for you.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento**

> File L-150. Genetic.
>
> A laboratory that made a power it could not hold, and a man who once wanted to own it.
>
> What came back with you was made by no one. It is small, and new, and nobody's weapon. Keep it that way.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Mewtwo_Arrival:
	.string "A burnt mansion on an island of ash. Its\n"
	.string "halls were lined with glass tanks, every\l"
	.string "one cracked open from the inside.\p"
	.string "Torn journal pages drifted across the\n"
	.string "floor. The last one read: 'We could not\l"
	.string "control it.'$"

Nexus_Text_Mewtwo_Boss:
	.string "Every loose page in the mansion lifted\n"
	.string "off the floor at once and hung in the\l"
	.string "air.\p"
	.string "At the end of the hall, something pale\n"
	.string "was floating, and it had been waiting\l"
	.string "for you.$"

Nexus_Text_Mewtwo_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-150. Genetic.\p"
	.string "A laboratory that made a power it could\n"
	.string "not hold, and a man who once wanted to\l"
	.string "own it.\p"
	.string "What came back with you was made by no\n"
	.string "one. It is small, and new, and nobody's\l"
	.string "weapon. Keep it that way.$"
```

</details>


#### Genesect

📝 **Proposta de 27/09/2026, aguardando o autor.** **Genesect**. Giovanni é o campeão dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Giovanni, o chefe que abandonou a Team Rocket depois de perder e deixou os homens dele esperando por um sinal durante três anos.

**A criatura.** Genesect, o Pokémon paleozoico. Um Pokémon Inseto de 300 milhões de anos, revivido pela Team Plasma e modificado com um canhão nas costas para virar arma.

**O fragmento.** Uma fábrica mais velha que qualquer cidade, metade fóssil, metade máquina. Esteiras levam ossos de pedra por fileiras de canhões parados. Em algum lugar, um bipe de mira repete sem parar.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário). Pelo [R17](../NEXUS_REGRAS.md), o que o jogador leva é o fragmento que sobra, no nível 1; a ficha do Looker fala desse pedaço, não da criatura domada.

**Chegada**

> A factory older than any city, half fossil and half machine. Conveyor belts carried stone bones past rows of silent cannons.
>
> Somewhere, a targeting beep kept repeating.

**Boss**

> The beeping stopped. Every cannon on the line turned toward you.
>
> A violet insect of steel dropped from the rafters, and the cannon on its back was already glowing.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento**

> File L-649. Paleozoic.
>
> An ancient hunter rebuilt as a weapon, and a retired boss who knows what his own soldiers felt.
>
> What you carried out has no cannon on its back. Only an old hunter's patience.
>
> He asked me who gave it its last order. I said no one living. He seemed relieved.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Genesect_Arrival:
	.string "A factory older than any city, half\n"
	.string "fossil and half machine. Conveyor belts\l"
	.string "carried stone bones past rows of silent\l"
	.string "cannons.\p"
	.string "Somewhere, a targeting beep kept\n"
	.string "repeating.$"

Nexus_Text_Genesect_Boss:
	.string "The beeping stopped. Every cannon on\n"
	.string "the line turned toward you.\p"
	.string "A violet insect of steel dropped from\n"
	.string "the rafters, and the cannon on its back\l"
	.string "was already glowing.$"

Nexus_Text_Genesect_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-649. Paleozoic.\p"
	.string "An ancient hunter rebuilt as a weapon,\n"
	.string "and a retired boss who knows what his\l"
	.string "own soldiers felt.\p"
	.string "What you carried out has no cannon on\n"
	.string "its back. Only an old hunter's patience.\p"
	.string "He asked me who gave it its last order. I\n"
	.string "said no one living. He seemed relieved.$"
```

</details>


### Diálogo genérico

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Giovanni cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala dele mesmo, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

**Antes da luta**

> So, you found me. Don't look so pleased. I've been found by children before.
>
> For years, Viridian's Gym sat locked while its Leader ran an empire from the back door. No adult ever noticed.
>
> A child did. Let us see what kind of child you are.

**Derrota**

> …Again. You all have the same look in your eyes.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Giovanni_Intro:
	.string "So, you found me. Don't look so pleased.\n"
	.string "I've been found by children before.\p"
	.string "For years, Viridian's Gym sat locked\n"
	.string "while its Leader ran an empire from the\l"
	.string "back door. No adult ever noticed.\p"
	.string "A child did. Let us see what kind of\n"
	.string "child you are.$"

Nexus_Text_Giovanni_Defeat:
	.string "…Again. You all have the same look in\n"
	.string "your eyes.$"
```

</details>


### Diálogo associado ao lendário

#### Mewtwo

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Giovanni é o **campeão**, a luta logo antes do Mewtwo. A fala é sobre a criatura, sem dizer o nome dela.

O Giovanni fala da criatura com um respeito que não admitiria aos homens dele: fizeram aquilo numa ilha, a partir de algo mais antigo e gentil, para ser o Pokémon mais forte do mundo, e conseguiram. Aí ela foi embora. Ninguém comanda uma coisa feita para ser mais forte que quem a fez. A virada vem depois da luta: ele sempre disse que *possuía* Pokémon fortes; ela foi feita para ser possuída e recusou, preferiu uma caverna. Ele também se escondeu uma vez, depois que uma criança o venceu, e chamou isso de estratégia. Não tente possuí-la; dê a ela um motivo. É um conselho que ele mesmo nunca seguiu.

**Antes da luta**

> You've seen it. The one that floats as if gravity were only a suggestion.
>
> Men made it on an island, from something older and gentler. They wanted the strongest Pokémon in the world. They got it.
>
> Then it left. No one commands a thing built to be stronger than its makers.
>
> I respect that more than I would ever tell my men. Come!

**Derrota**

> Hm. You fight like someone with nothing to prove. Irritating.

**Depois da luta**

> I have owned many strong Pokémon. Owned. That was always the word I used.
>
> That creature was made to be owned, and it refused. It chose a cave over a master.
>
> I went into hiding once too, after a child beat me. I called it strategy.
>
> Don't try to own it. Give it a reason. …Advice I never took myself.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Giovanni_Mewtwo_ChampionIntro:
	.string "You've seen it. The one that floats as\n"
	.string "if gravity were only a suggestion.\p"
	.string "Men made it on an island, from something\n"
	.string "older and gentler. They wanted the\l"
	.string "strongest Pokémon in the world. They\l"
	.string "got it.\p"
	.string "Then it left. No one commands a thing\n"
	.string "built to be stronger than its makers.\p"
	.string "I respect that more than I would ever\n"
	.string "tell my men. Come!$"

Nexus_Text_Giovanni_Mewtwo_ChampionDefeat:
	.string "Hm. You fight like someone with nothing\n"
	.string "to prove. Irritating.$"

Nexus_Text_Giovanni_Mewtwo_ChampionAfter:
	.string "{SPEAKER NAME_GIOVANNI}I have owned many strong Pokémon.\n"
	.string "Owned. That was always the word I used.\p"
	.string "That creature was made to be owned, and\n"
	.string "it refused. It chose a cave over a\l"
	.string "master.\p"
	.string "I went into hiding once too, after a\n"
	.string "child beat me. I called it strategy.\p"
	.string "Don't try to own it. Give it a reason.\n"
	.string "…Advice I never took myself.$"
```

</details>


#### Genesect

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Giovanni é o **campeão**, a luta logo antes do Genesect. A fala é sobre a criatura, sem dizer o nome dela.

O Giovanni reconhece a criatura como a um soldado: trezentos milhões de anos, desenterrada e reconstruída como arma por gente que tinha um rei e um discurso. Depois perderam e se espalharam, e ela continua ali, armada, esperando ordem. A virada: ele sabe como é isso, deixou um exército esperando uma vez. Depois da luta ele conta que os homens dele mantiveram o uniforme por três anos, esperando um sinal que ele nunca mandou; ele chamava de lealdade e era só um hábito que ele pôs neles. Vença a criatura e não dê ordens: dê a ela o que ele nunca deu aos homens dele, um dia de folga.

**Antes da luta**

> Did you see the one with the cannon on its back? Three hundred million years old. Dug up and rebuilt as a weapon.
>
> The people who rebuilt it had a king and a grand speech. Then they lost, and scattered.
>
> It's still here. Still armed. Still waiting for an order.
>
> I know what that looks like. I once left an army waiting. Let's go!

**Derrota**

> Enough. Your aim was cleaner than mine.

**Depois da luta**

> When I left Team Rocket, my men kept their uniforms on for three years, waiting for a signal I never sent.
>
> I called it loyalty. It was only a habit I had built into them.
>
> That creature is the same. Its habit simply has a cannon.
>
> Beat it, and give it no orders. Give it what I never gave them. A day off.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Giovanni_Genesect_ChampionIntro:
	.string "Did you see the one with the cannon on\n"
	.string "its back? Three hundred million years\l"
	.string "old. Dug up and rebuilt as a weapon.\p"
	.string "The people who rebuilt it had a king and\n"
	.string "a grand speech. Then they lost, and\l"
	.string "scattered.\p"
	.string "It's still here. Still armed. Still\n"
	.string "waiting for an order.\p"
	.string "I know what that looks like. I once left\n"
	.string "an army waiting. Let's go!$"

Nexus_Text_Giovanni_Genesect_ChampionDefeat:
	.string "Enough. Your aim was cleaner than mine.$"

Nexus_Text_Giovanni_Genesect_ChampionAfter:
	.string "{SPEAKER NAME_GIOVANNI}When I left Team Rocket, my men kept\n"
	.string "their uniforms on for three years,\l"
	.string "waiting for a signal I never sent.\p"
	.string "I called it loyalty. It was only a habit I\n"
	.string "had built into them.\p"
	.string "That creature is the same. Its habit\n"
	.string "simply has a cannon.\p"
	.string "Beat it, and give it no orders. Give it\n"
	.string "what I never gave them. A day off.$"
```

</details>


Falante novo: `SP_NAME_GIOVANNI` (ainda não existe em `include/constants/speaker_names.h`).
