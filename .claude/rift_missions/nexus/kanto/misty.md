# Misty

**Região da ficha:** Kanto

Aparece no checklist como:

- **Misty — Água** (Kanto · Líderes de Ginásio) — Líder de Cerulean, treinadora veloz associada a Starmie.

**Pronto para o Nexus:** ✅ sim — tem sprite e battle sprite.

## Checklist

- [x] Sprite de overworld *(obrigatório)*
- [x] Battle sprite / front pic *(obrigatório)*
- [ ] Field mugshot (retrato na caixa de diálogo)
- [x] Time para as Rift Missions definido
- [x] Associado a um lendário
- [x] Diálogo genérico escrito
- [x] Diálogo associado ao lendário escrito

## Referências no repositório

### Sprite de overworld

| Constante | Arquivo |
|---|---|
| `OBJ_EVENT_GFX_MISTY` | `graphics/object_events/pics/people/gym_leaders/misty.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_LEADER_MISTY` | `graphics/trainers/front_pics/misty.png` |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_MISTY` | 544 | 0x720 | Quagsire Lv62, Vaporeon Lv61, Milotic Lv61, Lapras Lv62, Starmie Lv63 | `CeruleanCity_Gym`, `SaffronCity_FightingDojoVIP`, `src/battle_dome.c`, `src/battle_setup.c` |

### Time das Rift Missions

✅ **Implementado em 27/09/2026** (a proposta abaixo virou código): `TRAINER_NEXUS_MISTY` = **988** (flag de batalha `0x8DC`, limpa antes e depois de cada luta), bloco em `src/data/trainers.party`, nível pelo R2 (tabela em `src/data/nexus/trainers.h`). Fala genérica `Nexus_EventScript_Misty_Fight`; campeão: `Nexus_EventScript_Misty_Kyogre_ChampionFight` (para Kyogre), `Nexus_EventScript_Misty_Manaphy_ChampionFight` (para Manaphy). Tudo em `data/scripts/nexus.inc`, sem blackout, resultado em `VAR_TEMP_3`. Para testar: menu de debug → Rift Missions… → Nexus fights… → Misty.

📝 **Proposta de 27/09/2026, aguardando o autor.** `TRAINER_NEXUS_MISTY`, campeão de Kyogre e Manaphy. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler).

Lendário **Kyogre** com **Blue Orb** (Primal: ocupa a vaga de lendário e a de Mega, R10), o dono dos mares para a "tomboyish mermaid" de Cerulean; semi-lendário **Manaphy**, o Príncipe do Mar, de quem ela também é campeã. Mais Starmie (o ás dela desde Red/Blue), Lapras, Milotic e Quagsire, do time de Cerulean da campanha. A política dela nos jogos é "all-out offensive with Water-type Pokémon", e o time faz exatamente isso.

*Plano (Singles):* chuva sem fim. A Primal Kyogre põe Primordial Sea (Fogo não funciona, Água sobe); o Manaphy sobe Tail Glow e se cura com Rest + Hydration na chuva; a Starmie limpa hazards com Rapid Spin e bate com Hydro Pump e Thunder que não erram na chuva; a Milotic (Competitive) pune Intimidate e se cura com Recover; o Quagsire (Water Absorb) segura os Elétricos com Yawn e Recover.

*Plano (Doubles):* Origin Pulse e Water Spout acertam os dois oponentes e não o parceiro; o Thunder da Starmie e o Freeze-Dry da Lapras (Assault Vest, Ice Shard de prioridade) cobrem Água e Grama do outro lado; o Quagsire e a Lapras têm Water Absorb, então nenhum golpe do time machuca quem está ao lado. O Quagsire usa High Horsepower em vez de Earthquake.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Kyogre | Blue Orb | Drizzle | Modest | Origin Pulse, Water Spout, Ice Beam, Thunder |
| Manaphy | Leftovers | Hydration | Timid | Tail Glow, Scald, Energy Ball, Rest |
| Starmie | Life Orb | Analytic | Timid | Hydro Pump, Thunder, Ice Beam, Rapid Spin |
| Lapras | Assault Vest | Water Absorb | Modest | Freeze-Dry, Hydro Pump, Ice Shard, Thunderbolt |
| Milotic | Leftovers | Competitive | Bold | Scald, Ice Beam, Recover, Coil |
| Quagsire | Rindo Berry | Water Absorb | Relaxed | High Horsepower, Liquidation, Recover, Yawn |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>dev_scripts/nexus_validar_time.py</code>: trainerproc, constantes, learnsets e categorias)</summary>

```
=== TRAINER_NEXUS_MISTY ===
Name: Misty
Class: Leader
Pic: Leader Misty
Gender: Female
Music: Female
Double Battle: Yes
AI: Smart Trainer

Kyogre @ Blue Orb
Modest Nature
Level: 100
Ability: Drizzle
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Origin Pulse
- Water Spout
- Ice Beam
- Thunder

Manaphy @ Leftovers
Timid Nature
Level: 100
Ability: Hydration
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Tail Glow
- Scald
- Energy Ball
- Rest

Starmie @ Life Orb
Timid Nature
Level: 100
Ability: Analytic
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Hydro Pump
- Thunder
- Ice Beam
- Rapid Spin

Lapras @ Assault Vest
Modest Nature
Level: 100
Ability: Water Absorb
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Freeze-Dry
- Hydro Pump
- Ice Shard
- Thunderbolt

Milotic @ Leftovers
Bold Nature
Level: 100
Ability: Competitive
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Scald
- Ice Beam
- Recover
- Coil

Quagsire @ Rindo Berry
Relaxed Nature
Level: 100
Ability: Water Absorb
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- High Horsepower
- Liquidation
- Recover
- Yawn
```

</details>

### Lendário associado

**Kyogre** — exemplo aprovado no design (`SOULGOLD_RIFT_MISSIONS_DESIGN.md` §10, "Estrutura do loop"). Aprovado só como associação; nada implementado. O Kyogre tem **dois** campeões (Misty e Archie): as falas do fragmento e a ficha do Looker ficam aqui; a ficha do Archie só tem a fala de campeão dele.

#### Kyogre

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_Kyogre_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Kyogre**. Misty é a campeã dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Misty, Líder de Cerulean, especialista em Água, "the tomboyish mermaid". O ginásio dela é uma piscina. A Starmie é o ás de sempre.

**A criatura.** Kyogre, o Pokémon Bacia do Mar, é dito ter expandido os mares com chuva torrencial e ondas enormes; lutou contra Groudon até ser acalmado por Rayquaza e dormiu no fundo do oceano. Com a Blue Orb volta à forma Primal.

**O fragmento.** Chuva que cai desde antes de existir terra. Não há praia, só uma linha onde a água ainda não chegou, e essa linha vem andando na sua direção. O mar quer o mundo de volta.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> Rain. It had been raining here since before there was a here.
>
> There was no shore, only a line where the water had not arrived yet, and that line kept moving toward you.

**Boss**

> The sea swelled into a shape bigger than an island.
>
> Lines of light glowed along its sides, and the rain fell harder, as if it had been told to.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md))

> File L-382. Sea Basin.
>
> A sea that wants the whole world back, and a Gym Leader who has loved water all her life.
>
> What came back with you fits in a bathtub. It still makes it rain indoors, a little. I have moved my papers.
>
> She told me water needs a shore. It may be the wisest thing anyone has said to me this year.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Kyogre_Arrival:
	.string "Rain. It had been raining here since\n"
	.string "before there was a here.\p"
	.string "There was no shore, only a line where\n"
	.string "the water had not arrived yet, and\l"
	.string "that line kept moving toward you.$"

Nexus_Text_Kyogre_Boss:
	.string "The sea swelled into a shape bigger\n"
	.string "than an island.\p"
	.string "Lines of light glowed along its sides,\n"
	.string "and the rain fell harder, as if it had\l"
	.string "been told to.$"

Nexus_Text_Kyogre_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-382. Sea Basin.\p"
	.string "A sea that wants the whole world back,\n"
	.string "and a Gym Leader who has loved water\l"
	.string "all her life.\p"
	.string "What came back with you fits in a\n"
	.string "bathtub. It still makes it rain indoors,\l"
	.string "a little. I have moved my papers.\p"
	.string "She told me water needs a shore. It may\n"
	.string "be the wisest thing anyone has said to\l"
	.string "me this year.$"
```

</details>

#### Manaphy

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_Manaphy_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Manaphy**. Misty é a campeã dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** A mesma Misty, que vive dizendo que vai ser a maior mestra de Pokémon de Água do mundo, e continua em Cerulean.

**A criatura.** Manaphy, o Pokémon Navegante, é conhecido como o Príncipe do Mar. Nasce no fundo frio do oceano e nada distâncias enormes para voltar ao lugar onde nasceu; tem o poder de se ligar a qualquer Pokémon. Neste hack evolui de Phione no nível 58.

**O fragmento.** Um fundo de mar frio e muito fundo, iluminado por ovos que flutuam. Cada ovo vai embora numa corrente diferente, e cada um, devagar, acha o caminho de volta. Tudo que sai volta para casa.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A seafloor, cold and very deep, lit by small floating eggs.
>
> Each egg drifted off on a different current. Each one, slowly, found its way back.

**Boss**

> One egg did not drift away. It hatched.
>
> Something small and blue floated up to meet you, curious, as if it had been expecting you all along.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md))

> File L-490. Seafaring.
>
> A seafloor where everything that leaves comes home, and a Gym Leader who keeps saying she will leave.
>
> What came back with you is paler, and smaller, and not a prince of anything yet. It keeps swimming toward the door.
>
> She wanted it written that she always goes back to her city. I did not ask. I have written it.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Manaphy_Arrival:
	.string "A seafloor, cold and very deep, lit by\n"
	.string "small floating eggs.\p"
	.string "Each egg drifted off on a different\n"
	.string "current. Each one, slowly, found its\l"
	.string "way back.$"

Nexus_Text_Manaphy_Boss:
	.string "One egg did not drift away. It hatched.\p"
	.string "Something small and blue floated up to\n"
	.string "meet you, curious, as if it had been\l"
	.string "expecting you all along.$"

Nexus_Text_Manaphy_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-490. Seafaring.\p"
	.string "A seafloor where everything that\n"
	.string "leaves comes home, and a Gym Leader\l"
	.string "who keeps saying she will leave.\p"
	.string "What came back with you is paler, and\n"
	.string "smaller, and not a prince of anything\l"
	.string "yet. It keeps swimming toward the door.\p"
	.string "She wanted it written that she always\n"
	.string "goes back to her city. I did not ask. I\l"
	.string "have written it.$"
```

</details>

### Diálogo genérico

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Misty_Fight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Misty cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala de si, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

**Antes da luta**

> Hi, you're a new face! I'm Misty, the tomboyish mermaid!
>
> My policy is simple: an all-out offensive with Water-type Pokémon! Whatever this place is, that doesn't change.
>
> Ready to get soaked?

**Derrota**

> You're really strong! …I mean it! Don't look at me like that!

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Misty_Intro:
	.string "Hi, you're a new face! I'm Misty, the\n"
	.string "tomboyish mermaid!\p"
	.string "My policy is simple: an all-out\n"
	.string "offensive with Water-type Pokémon!\l"
	.string "Whatever this place is, that doesn't\l"
	.string "change.\p"
	.string "Ready to get soaked?$"

Nexus_Text_Misty_Defeat:
	.string "You're really strong! …I mean it! Don't\n"
	.string "look at me like that!$"
```

</details>

#### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mesmo registro da variação 1 ([R16](../NEXUS_REGRAS.md)): fala de si, sem citar o lugar nem a criatura do dia. Variação 2: as três irmãs (Daisy, Lily e Violet, nunca nomeadas) que foram fazer cruzeiro enquanto ela ficou com o ginásio; humor e orgulho. Variação 3: o que ela ama nos Pokémon de Água — nunca ficam parados, nem dormindo (a Starmie gira, o Psyduck só boia).

**Variação 2 — antes da luta**

> Let me guess. You thought the Cerulean Gym Leader would be one of my sisters. Everybody does.
>
> Well, they're off on a cruise, and I'm the one who stayed. The strong one.
>
> That's me! Let's battle!

**Variação 2 — derrota**

> …Okay, don't tell my sisters about this one. Ever.

**Variação 3 — antes da luta**

> Know what I like best about Water-types? They never stand still. Not even when they're asleep.
>
> My Starmie spins in its sleep. My Psyduck… well, Psyduck just floats.
>
> Let's make some waves!

**Variação 3 — derrota**

> You made the bigger wave. …This time!

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Misty_Intro2:
	.string "Let me guess. You thought the Cerulean\n"
	.string "Gym Leader would be one of my sisters.\l"
	.string "Everybody does.\p"
	.string "Well, they're off on a cruise, and I'm\n"
	.string "the one who stayed. The strong one.\p"
	.string "That's me! Let's battle!$"

Nexus_Text_Misty_Defeat2:
	.string "…Okay, don't tell my sisters about this\n"
	.string "one. Ever.$"

Nexus_Text_Misty_Intro3:
	.string "Know what I like best about\n"
	.string "Water-types? They never stand still.\l"
	.string "Not even when they're asleep.\p"
	.string "My Starmie spins in its sleep. My\n"
	.string "Psyduck… well, Psyduck just floats.\p"
	.string "Let's make some waves!$"

Nexus_Text_Misty_Defeat3:
	.string "You made the bigger wave. …This time!$"
```

</details>


### Diálogo associado ao lendário

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Misty é a **campeã**, a luta logo antes do lendário. A fala é sobre a criatura, sem dizer o nome dela ([R16](../NEXUS_REGRAS.md)).

#### Kyogre

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Misty_Kyogre_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

Todo mundo acha que a Misty amaria um mundo só de água. Ela viu a coisa chegando e não é bonita: não faz onda, não brilha, só vem. A virada é a piscina do ginásio dela: uma piscina é só água que alguém amou o bastante para dar bordas. A criatura não tem borda nenhuma e quer o mapa inteiro azul. A Misty entende o sentimento e discorda. "Mostra pra ela onde fica a praia."

**Antes da luta**

> Everyone thinks I'd love a world that was all ocean. No land, just water, forever.
>
> I watched it coming in out there. It doesn't wave. It doesn't sparkle. It just keeps coming.
>
> Water's supposed to have somewhere to go back to! …Let's battle before I think about it more!

**Derrota**

> Soaked. Totally soaked. …By you, at least.

**Depois da luta**

> My gym's a pool. People laugh, but a pool is just water somebody loved enough to give it edges.
>
> That thing out there has no edges. It wants the whole map blue.
>
> I get the feeling. I just don't agree with it.
>
> Go on. Show it where the shore is.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Misty_Kyogre_ChampionIntro:
	.string "Everyone thinks I'd love a world that\n"
	.string "was all ocean. No land, just water,\l"
	.string "forever.\p"
	.string "I watched it coming in out there. It\n"
	.string "doesn't wave. It doesn't sparkle. It\l"
	.string "just keeps coming.\p"
	.string "Water's supposed to have somewhere\n"
	.string "to go back to! …Let's battle before I\l"
	.string "think about it more!$"

Nexus_Text_Misty_Kyogre_ChampionDefeat:
	.string "Soaked. Totally soaked. …By you, at\n"
	.string "least.$"

Nexus_Text_Misty_Kyogre_ChampionAfter:
	.string "{SPEAKER NAME_MISTY}My gym's a pool. People laugh, but a\n"
	.string "pool is just water somebody loved\l"
	.string "enough to give it edges.\p"
	.string "That thing out there has no edges. It\n"
	.string "wants the whole map blue.\p"
	.string "I get the feeling. I just don't agree\n"
	.string "with it.\p"
	.string "Go on. Show it where the shore is.$"
```

</details>

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

Variação 2: a dúvida — as irmãs estão num cruzeiro e o último cartão-postal só dizia 'So much water!!'; depois, a leitura dela: água com medo sobe; a criatura não está com raiva, tem medo de ser pequena. Variação 3: humor de 'sereia' que precisa de pedra para sentar, e a confissão de que ela, criança, desejou chuva para sempre.

**Variação 2 — antes da luta**

> My sisters are on a cruise somewhere out there. They send postcards. The last one just said 'So much water!!'
>
> I laughed. Then I saw that thing out there, and I stopped laughing.
>
> I'm sure they're fine! Totally sure! Let's battle!

**Variação 2 — derrota**

> Okay. I'm… a little less sure. But okay.

**Variação 2 — depois da luta**

> Know what water does when it's scared? It rises. It fills every corner, so nothing can sneak up on it.
>
> That thing isn't angry. I think it's scared of being small again.
>
> Don't make it feel small. Just… give it a shore. Go on.

**Variação 3 — antes da luta**

> People call me a mermaid. The tomboyish mermaid, fine. But a mermaid still needs rocks to sit on!
>
> That thing out there took all the rocks. Every single one.
>
> I'm taking them back, starting with you! Let's go!

**Variação 3 — derrota**

> You're a really stubborn rock. I'll give you that.

**Variação 3 — depois da luta**

> Here's a secret. When I was little, I wished it would rain forever, so I could swim everywhere.
>
> Looks like somebody's wish came true. Just not mine.
>
> Be careful what you wish for. And bring an umbrella. Go!

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Misty_Kyogre_ChampionIntro2:
	.string "My sisters are on a cruise somewhere\n"
	.string "out there. They send postcards. The\l"
	.string "last one just said 'So much water!!'\p"
	.string "I laughed. Then I saw that thing out\n"
	.string "there, and I stopped laughing.\p"
	.string "I'm sure they're fine! Totally sure!\n"
	.string "Let's battle!$"

Nexus_Text_Misty_Kyogre_ChampionDefeat2:
	.string "Okay. I'm… a little less sure. But okay.$"

Nexus_Text_Misty_Kyogre_ChampionAfter2:
	.string "{SPEAKER NAME_MISTY}Know what water does when it's scared?\n"
	.string "It rises. It fills every corner, so\l"
	.string "nothing can sneak up on it.\p"
	.string "That thing isn't angry. I think it's\n"
	.string "scared of being small again.\p"
	.string "Don't make it feel small. Just… give it a\n"
	.string "shore. Go on.$"

Nexus_Text_Misty_Kyogre_ChampionIntro3:
	.string "People call me a mermaid. The tomboyish\n"
	.string "mermaid, fine. But a mermaid still needs\l"
	.string "rocks to sit on!\p"
	.string "That thing out there took all the rocks.\n"
	.string "Every single one.\p"
	.string "I'm taking them back, starting with\n"
	.string "you! Let's go!$"

Nexus_Text_Misty_Kyogre_ChampionDefeat3:
	.string "You're a really stubborn rock. I'll give\n"
	.string "you that.$"

Nexus_Text_Misty_Kyogre_ChampionAfter3:
	.string "{SPEAKER NAME_MISTY}Here's a secret. When I was little, I\n"
	.string "wished it would rain forever, so I could\l"
	.string "swim everywhere.\p"
	.string "Looks like somebody's wish came true.\n"
	.string "Just not mine.\p"
	.string "Be careful what you wish for. And bring\n"
	.string "an umbrella. Go!$"
```

</details>


#### Manaphy

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Misty_Manaphy_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

A criaturinha pode nadar para qualquer lugar do mundo e sempre volta para casa. A Misty vive prometendo viajar o mundo e nunca vai. Primeiro ela se defende; depois, a virada: a criatura não volta por medo de sair, volta porque tem alguém esperando. Casa, para ela, não é lugar, é quem espera. E é por isso que a Misty nunca fica longe de Cerulean por muito tempo.

**Antes da luta**

> Did you see the eggs out there? Every one drifted off, and every one came back.
>
> The little one that hatched is the same. It could swim anywhere in the world, and it always swims home.
>
> I keep saying I'll travel the whole world. I never do! Let's battle!

**Derrota**

> Aww… okay. You win this one.

**Depois da luta**

> Know what I figured out? It doesn't come home because it's scared to leave.
>
> It comes home because somebody's there. Home isn't a place for it. It's who's waiting.
>
> …That's why I never stay away from Cerulean for long.
>
> Go say hi. Gently! It's only a baby.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Misty_Manaphy_ChampionIntro:
	.string "Did you see the eggs out there? Every\n"
	.string "one drifted off, and every one came\l"
	.string "back.\p"
	.string "The little one that hatched is the\n"
	.string "same. It could swim anywhere in the\l"
	.string "world, and it always swims home.\p"
	.string "I keep saying I'll travel the whole\n"
	.string "world. I never do! Let's battle!$"

Nexus_Text_Misty_Manaphy_ChampionDefeat:
	.string "Aww… okay. You win this one.$"

Nexus_Text_Misty_Manaphy_ChampionAfter:
	.string "{SPEAKER NAME_MISTY}Know what I figured out? It doesn't\n"
	.string "come home because it's scared to\l"
	.string "leave.\p"
	.string "It comes home because somebody's\n"
	.string "there. Home isn't a place for it. It's\l"
	.string "who's waiting.\p"
	.string "…That's why I never stay away from\n"
	.string "Cerulean for long.\p"
	.string "Go say hi. Gently! It's only a baby.$"
```

</details>

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

Variação 2: a lembrança (R21: no anime quem cuidou do ovo foi a May; no fragmento dela, foi a Misty) — o bichinho achou que ela era a mãe; depois, o Heart Swap: ele deixa qualquer um sentir o que ele sente, até estranhos. Variação 3: humor — o Príncipe do Mar mimado, com coroa num templo no fundo do mar, contra a piscina dela; voltar é a parte corajosa.

**Variação 2 — antes da luta**

> I babysat an egg once. It hatched into a little blue thing that thought I was its mom.
>
> I had a gym to run! I was not ready!
>
> …I cried when it went home. Let's battle before I cry again!

**Variação 2 — derrota**

> Aww… That's fine. I'm not crying. It's the water.

**Variação 2 — depois da luta**

> It can make anyone feel what it feels, just by touching them. Swapping hearts, some people say.
>
> I'd be scared of that. Letting someone feel everything I feel?
>
> It does it with strangers. …Go say hi. Let it swap a little.

**Variação 3 — antes da luta**

> The sea has a prince. Did you know that? A tiny, blue, very spoiled prince.
>
> It has a crown somewhere, too. At the bottom of the ocean, in a temple nobody can find.
>
> I have a gym and a pool. Let's see whose kingdom is better!

**Variação 3 — derrota**

> Fine! Its kingdom wins. Mine has better lighting, though.

**Variação 3 — depois da luta**

> A prince who only knows how to go home. That's all it does. Swim away, swim back.
>
> Sounds boring, right? It isn't. Going back is the brave part. Anyone can leave.
>
> Go on. It's waiting at the door.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Misty_Manaphy_ChampionIntro2:
	.string "I babysat an egg once. It hatched into\n"
	.string "a little blue thing that thought I was\l"
	.string "its mom.\p"
	.string "I had a gym to run! I was not ready!\p"
	.string "…I cried when it went home. Let's\n"
	.string "battle before I cry again!$"

Nexus_Text_Misty_Manaphy_ChampionDefeat2:
	.string "Aww… That's fine. I'm not crying. It's\n"
	.string "the water.$"

Nexus_Text_Misty_Manaphy_ChampionAfter2:
	.string "{SPEAKER NAME_MISTY}It can make anyone feel what it feels,\n"
	.string "just by touching them. Swapping hearts,\l"
	.string "some people say.\p"
	.string "I'd be scared of that. Letting someone\n"
	.string "feel everything I feel?\p"
	.string "It does it with strangers. …Go say hi.\n"
	.string "Let it swap a little.$"

Nexus_Text_Misty_Manaphy_ChampionIntro3:
	.string "The sea has a prince. Did you know that?\n"
	.string "A tiny, blue, very spoiled prince.\p"
	.string "It has a crown somewhere, too. At the\n"
	.string "bottom of the ocean, in a temple nobody\l"
	.string "can find.\p"
	.string "I have a gym and a pool. Let's see whose\n"
	.string "kingdom is better!$"

Nexus_Text_Misty_Manaphy_ChampionDefeat3:
	.string "Fine! Its kingdom wins. Mine has better\n"
	.string "lighting, though.$"

Nexus_Text_Misty_Manaphy_ChampionAfter3:
	.string "{SPEAKER NAME_MISTY}A prince who only knows how to go home.\n"
	.string "That's all it does. Swim away, swim back.\p"
	.string "Sounds boring, right? It isn't. Going\n"
	.string "back is the brave part. Anyone can\l"
	.string "leave.\p"
	.string "Go on. It's waiting at the door.$"
```

</details>


Falante novo: `SP_NAME_MISTY` (ainda não existe em `include/constants/speaker_names.h`).
