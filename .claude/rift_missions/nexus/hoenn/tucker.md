# Tucker

**Região da ficha:** Hoenn

Aparece no checklist como:

- **Tucker — Battle Dome** (Hoenn · Battle Frontier — Frontier Brains) — estrela extravagante de torneios eliminatórios.

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
| `OBJ_EVENT_GFX_TUCKER` | `graphics/object_events/pics/people/frontier_brains/tucker.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_DOME_ACE_TUCKER` | `graphics/trainers/front_pics/dome_ace_tucker.png` |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

Nenhuma. Ao criar, seguir a skill `adicionar-batalha-npc` (e `alocar-flag` se precisar de flag nova).

Homônimos genéricos, **não** são este personagem: `TRAINER_TUCKER` ("Tucker", pic Swimmer M).

### Time das Rift Missions

✅ **Implementado em 27/09/2026** (a proposta abaixo virou código): `TRAINER_NEXUS_TUCKER` = **1030** (flag de batalha `0x906`, limpa antes e depois de cada luta), bloco em `src/data/trainers.party`, nível pelo R2 (tabela em `src/data/nexus/trainers.h`). Fala genérica `Nexus_EventScript_Tucker_Fight`; campeão: `Nexus_EventScript_Tucker_Hoopa_ChampionFight` (para Hoopa), `Nexus_EventScript_Tucker_Eternatus_ChampionFight` (para Eternatus). Tudo em `data/scripts/nexus.inc`, sem blackout, resultado em `VAR_TEMP_3`. Para testar: menu de debug → Rift Missions… → Nexus fights… → Tucker.

📝 **Proposta de 27/09/2026, aguardando o autor.** `TRAINER_NEXUS_TUCKER`, campeão de Eternatus e Hoopa. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler).

Lendário **Eternatus** (o mais "palco" dos lendários: a energia dele acendia os estádios de Galar), semi-lendário **Meloetta**, a artista, Mega **Salamence** (Dragotite), o ás do Tucker desde Emerald. Ele não é campeão da Hoopa no time porque os dois são lendários (R10); a Hoopa fica só como o lendário do dia. Com Swampert e Metagross, dos times dele no Battle Dome, e o Arcanine como "segurança do show". *Plano:* **o show começa forte e não deixa o público respirar.** Intimidate duplo (Salamence e Arcanine) para os físicos, Meloetta com Throat Spray para os especiais, Eternatus como a atração principal.

*Plano (Singles):* Swampert arma Stealth Rock, Arcanine queima físicos com Will-O-Wisp, a Mega Salamence (Aerilate) sobe com Dragon Dance e usa Double-Edge voador, o Eternatus bate com Dynamax Cannon e se cura com Recover. *Plano (Doubles):* dois Intimidate em rotação, Snarl do Arcanine, Hyper Voice da Meloetta (spread, sobe o SpA pelo Throat Spray); Metagross de Assault Vest segura o especial do outro lado. Nada de Earthquake: o Swampert usa High Horsepower, de alvo único.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Eternatus | Life Orb | Pressure | Timid | Dynamax Cannon, Sludge Bomb, Flamethrower, Recover |
| Meloetta | Throat Spray | Serene Grace | Timid | Hyper Voice, Psychic, Focus Blast, U-turn |
| Salamence | Dragotite | Intimidate | Adamant | Double-Edge, Dragon Claw, Fire Fang, Dragon Dance |
| Metagross | Assault Vest | Clear Body | Adamant | Meteor Mash, Zen Headbutt, Bullet Punch, Ice Punch |
| Swampert | Leftovers | Torrent | Adamant | Liquidation, High Horsepower, Stealth Rock, Ice Punch |
| Arcanine | Sitrus Berry | Intimidate | Adamant | Flare Blitz, Extreme Speed, Snarl, Will-O-Wisp |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>dev_scripts/nexus_validar_time.py</code>: espécie, item, habilidade, learnsets e vagas)</summary>

```
=== TRAINER_NEXUS_TUCKER ===
Name: Tucker
Class: Dome Ace
Pic: Dome Ace Tucker
Gender: Male
Music: Male
Double Battle: Yes
AI: Smart Trainer

Eternatus @ Life Orb
Timid Nature
Level: 100
Ability: Pressure
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Dynamax Cannon
- Sludge Bomb
- Flamethrower
- Recover

Meloetta @ Throat Spray
Timid Nature
Level: 100
Ability: Serene Grace
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Hyper Voice
- Psychic
- Focus Blast
- U-turn

Salamence @ Dragotite
Adamant Nature
Level: 100
Ability: Intimidate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Double-Edge
- Dragon Claw
- Fire Fang
- Dragon Dance

Metagross @ Assault Vest
Adamant Nature
Level: 100
Ability: Clear Body
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Meteor Mash
- Zen Headbutt
- Bullet Punch
- Ice Punch

Swampert @ Leftovers
Adamant Nature
Level: 100
Ability: Torrent
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Liquidation
- High Horsepower
- Stealth Rock
- Ice Punch

Arcanine @ Sitrus Berry
Adamant Nature
Level: 100
Ability: Intimidate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Flare Blitz
- Extreme Speed
- Snarl
- Will-O-Wisp
```

</details>


### Lendário associado

#### Eternatus

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_Eternatus_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Eternatus**. Tucker é o campeão dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Tucker, Dome Ace da Battle Frontier de Hoenn, extravagante e apaixonado pela plateia do torneio do Battle Dome.

**A criatura.** Caiu num meteoro há uns vinte mil anos e dormiu sob Galar. Absorve energia; foi a fonte do fenômeno Dynamax nos estádios de Galar e, acordado, causou o Darkest Day. Sua forma Eternamax é o núcleo gigante daquele dia.

**O fragmento.** Um estádio enorme sob um céu vermelho. Todos os refletores estão acesos e virados para o centro do campo, e as arquibancadas estão vazias. Os holofotes não iluminam ninguém: eles sugam a luz para dentro.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A huge stadium under a red sky.
>
> Every floodlight was on, every one of them aimed at the center of the pitch, and every seat was empty.
>
> The lights were not shining. They were pulling the light in.

**Boss**

> The pitch cracked open, and the red sky poured down into it.
>
> Something long and bone-white rose out of the ground, and every floodlight turned to face it.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md))

> File L-890. Darkest Day.
>
> A stadium lit by the thing that eats its light, and a showman who loves an audience a little too much.
>
> What came back with you glows faintly, and only when someone looks at it. I have decided to look at it often.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Eternatus_Arrival:
	.string "A huge stadium under a red sky.\p"
	.string "Every floodlight was on, every one of\n"
	.string "them aimed at the center of the pitch,\l"
	.string "and every seat was empty.\p"
	.string "The lights were not shining. They were\n"
	.string "pulling the light in.$"

Nexus_Text_Eternatus_Boss:
	.string "The pitch cracked open, and the red\n"
	.string "sky poured down into it.\p"
	.string "Something long and bone-white rose\n"
	.string "out of the ground, and every\l"
	.string "floodlight turned to face it.$"

Nexus_Text_Eternatus_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-890. Darkest Day.\p"
	.string "A stadium lit by the thing that eats\n"
	.string "its light, and a showman who loves an\l"
	.string "audience a little too much.\p"
	.string "What came back with you glows faintly,\n"
	.string "and only when someone looks at it. I\l"
	.string "have decided to look at it often.$"
```

</details>


#### Hoopa

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_Hoopa_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Hoopa**. Tucker é o campeão dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Tucker, o Dome Ace que precisa de plateia para lutar.

**A criatura.** Mítico travesso que puxa coisas de outros lugares pelos anéis que carrega. Na forma confinada é pequeno e brincalhão; solto (Unbound), foi tão destrutivo que o selaram num vaso, o Prison Bottle.

**O fragmento.** Um torneio montado no meio do nada: chave pendurada, holofotes, palco. As arquibancadas estão lotadas de gente que atravessou anéis dourados e ainda olha em volta sem saber onde está. Ninguém aplaude.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A tournament stage in the middle of nowhere. A bracket on the wall, spotlights, a ring.
>
> The stands were packed with people who had stepped out of golden hoops, and were still looking around.
>
> None of them were clapping.

**Boss**

> A golden ring opened above the stage, and a laugh came out of it before anything else did.
>
> Then more rings, and more, until the whole stage was a mouth full of doors.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md))

> File L-720. Rings.
>
> A crowd pulled in from everywhere, and a star who noticed they were not his.
>
> What came back with you is tiny and laughs at everything. The rings are gone. I checked my pockets, just in case.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Hoopa_Arrival:
	.string "A tournament stage in the middle of\n"
	.string "nowhere. A bracket on the wall,\l"
	.string "spotlights, a ring.\p"
	.string "The stands were packed with people\n"
	.string "who had stepped out of golden hoops,\l"
	.string "and were still looking around.\p"
	.string "None of them were clapping.$"

Nexus_Text_Hoopa_Boss:
	.string "A golden ring opened above the stage,\n"
	.string "and a laugh came out of it before\l"
	.string "anything else did.\p"
	.string "Then more rings, and more, until the\n"
	.string "whole stage was a mouth full of doors.$"

Nexus_Text_Hoopa_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-720. Rings.\p"
	.string "A crowd pulled in from everywhere, and\n"
	.string "a star who noticed they were not his.\p"
	.string "What came back with you is tiny and\n"
	.string "laughs at everything. The rings are\l"
	.string "gone. I checked my pockets, just in\l"
	.string "case.$"
```

</details>


### Diálogo genérico

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Tucker_Fight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Tucker cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala dele mesmo, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

**Antes da luta**

> Ha ha ha! Did you hear that? No? That's the crowd! They always cheer when Tucker walks in.
>
> Here, they're a little… quiet. That's fine. I'll cheer for myself until they catch up.
>
> Now, fan! Give me a match worth a standing ovation!

**Derrota**

> Bravo! Bravo! …That was me clapping. For you. Don't let it go to your head.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Tucker_Intro:
	.string "Ha ha ha! Did you hear that? No?\n"
	.string "That's the crowd! They always cheer\l"
	.string "when Tucker walks in.\p"
	.string "Here, they're a little… quiet. That's\n"
	.string "fine. I'll cheer for myself until they\l"
	.string "catch up.\p"
	.string "Now, fan! Give me a match worth a\n"
	.string "standing ovation!$"

Nexus_Text_Tucker_Defeat:
	.string "Bravo! Bravo! …That was me clapping.\n"
	.string "For you. Don't let it go to your head.$"
```

</details>


### Diálogo associado ao lendário

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Tucker é o campeão, a luta logo antes do lendário do dia. Um registro por lendário; a fala é sobre a criatura, sem dizer o nome dela.

#### Eternatus

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Tucker_Eternatus_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

O Tucker entende de palco e reconhece a criatura como uma colega: ela tem os refletores, tem o estádio, tem o céu tingido para a entrada dela. Mas a luz dos estádios de Galar era energia tirada dela, e ela vem cobrar. A virada: o Tucker, que vive do aplauso, percebe que aquela criatura faz o que ele tem medo de fazer, que é tirar mais do público do que dá. E admite, meio rindo, que já pensou em fazer igual.

**Antes da luta**

> Ha! Now THAT is an entrance! Red sky, every light in the house aimed right at it!
>
> I know a star when I see one. I also know a star who's stealing the lights.
>
> Every stadium over there glowed because of that thing. And now it wants all that glow back.
>
> Well, fan? Let's see who the crowd is really here for!

**Derrota**

> Hm. Fine. You can have the spotlight. For now.

**Depois da luta**

> Want to know a secret? Sometimes, in the Dome, I've thought about it.
>
> Taking the whole crowd for myself. Every cheer, every light. Nothing left for the challenger.
>
> That thing out there did it. And look what it's got. An empty stadium.
>
> A star gives the crowd something to take home. Go remind it, fan!

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Tucker_Eternatus_ChampionIntro:
	.string "Ha! Now THAT is an entrance! Red sky,\n"
	.string "every light in the house aimed right at\l"
	.string "it!\p"
	.string "I know a star when I see one. I also\n"
	.string "know a star who's stealing the lights.\p"
	.string "Every stadium over there glowed\n"
	.string "because of that thing. And now it\l"
	.string "wants all that glow back.\p"
	.string "Well, fan? Let's see who the crowd is\n"
	.string "really here for!$"

Nexus_Text_Tucker_Eternatus_ChampionDefeat:
	.string "Hm. Fine. You can have the spotlight.\n"
	.string "For now.$"

Nexus_Text_Tucker_Eternatus_ChampionAfter:
	.string "{SPEAKER NAME_TUCKER}Want to know a secret? Sometimes, in\n"
	.string "the Dome, I've thought about it.\p"
	.string "Taking the whole crowd for myself.\n"
	.string "Every cheer, every light. Nothing left\l"
	.string "for the challenger.\p"
	.string "That thing out there did it. And look\n"
	.string "what it's got. An empty stadium.\p"
	.string "A star gives the crowd something to\n"
	.string "take home. Go remind it, fan!$"
```

</details>


#### Hoopa

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Tucker_Hoopa_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

O Tucker chega ao fragmento e encontra o sonho dele: um estádio lotado. Só que a plateia foi puxada pelos anéis da criatura, arrancada de algum lugar, e ninguém ali quer estar ali. A virada: o Tucker descobre que uma arquibancada cheia não vale nada se ninguém escolheu vir. E, pela primeira vez, ele luta para uma plateia de uma pessoa só: o jogador, que escolheu entrar.

**Antes da luta**

> Ha ha! What a house! Every seat full! Somebody's been busy with those gold rings.
>
> But look at their faces, fan. They didn't buy tickets. They got pulled in.
>
> Nobody chose to be here. Nobody's cheering.
>
> Except you. You walked in on your own. So this one's for an audience of one!

**Derrota**

> …Now that's what a real crowd sounds like. Just one person, meaning it.

**Depois da luta**

> All my life I wanted a full house. Every seat. Every light.
>
> That little prankster gave me one, and it was the worst show I ever played.
>
> Turns out a crowd's only worth something if they chose to come.
>
> Go send those people home, fan. The show's over.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Tucker_Hoopa_ChampionIntro:
	.string "Ha ha! What a house! Every seat full!\n"
	.string "Somebody's been busy with those gold\l"
	.string "rings.\p"
	.string "But look at their faces, fan. They\n"
	.string "didn't buy tickets. They got pulled in.\p"
	.string "Nobody chose to be here. Nobody's\n"
	.string "cheering.\p"
	.string "Except you. You walked in on your own.\n"
	.string "So this one's for an audience of one!$"

Nexus_Text_Tucker_Hoopa_ChampionDefeat:
	.string "…Now that's what a real crowd sounds\n"
	.string "like. Just one person, meaning it.$"

Nexus_Text_Tucker_Hoopa_ChampionAfter:
	.string "{SPEAKER NAME_TUCKER}All my life I wanted a full house. Every\n"
	.string "seat. Every light.\p"
	.string "That little prankster gave me one, and\n"
	.string "it was the worst show I ever played.\p"
	.string "Turns out a crowd's only worth\n"
	.string "something if they chose to come.\p"
	.string "Go send those people home, fan. The\n"
	.string "show's over.$"
```

</details>


Falante novo: `SP_NAME_TUCKER` (não existe em `include/constants/speaker_names.h`).
