# Olivia

**Região da ficha:** Alola

Aparece no checklist como:

- **Olivia — Pedra** (Alola · Island Kahunas) — Kahuna de Akala e joalheira.
- **Olivia — Pedra** (Alola · Elite Four e Campeões) — representa Akala na Elite Four.

**Pronto para o Nexus:** ❌ não — o overworld próprio entrou no código em 30/09/2026 (`OBJ_EVENT_GFX_OLIVIA`), mas falta a front pic (obrigatória).

**Arte disponível:** ✅ overworld e front pic em `.filetransfer/.trainers/Olivia/` (o overworld já registrado; a front pic, não).

## Checklist

- [x] Sprite de overworld *(obrigatório)* — `OBJ_EVENT_GFX_OLIVIA`, 30/09/2026
- [ ] Battle sprite / front pic *(obrigatório)* — arte disponível, falta registrar
- [ ] Field mugshot (retrato na caixa de diálogo)
- [ ] Time para as Rift Missions definido — 📝 proposta abaixo (30/09/2026), fora do código
- [ ] Associado a um lendário — 📝 proposta: Tapu Lele (cedida pela Lillie)
- [ ] Diálogo genérico escrito — 📝 proposta abaixo, 3 variações
- [ ] Diálogo associado ao lendário escrito — 📝 proposta abaixo, 3 variações

## Referências no repositório

### Sprite de overworld

| Constante | Arquivo |
|---|---|
| `OBJ_EVENT_GFX_OLIVIA` | `graphics/object_events/pics/people/special/olivia.png` (16x32, 12 quadros, `sAnimTable_StandardAsym`; paleta própria `OBJ_EVENT_PAL_TAG_OLIVIA`) — registrado em 30/09/2026 |

Fonte da arte em `.filetransfer/.trainers/Olivia/`:

| Arquivo | O que é |
|---|---|
| `Sprite - desconhecido.png` | overworld, autor **desconhecido** (folha ampliada por IA; origem do `olivia.png` acima, reduzida com `reamostrar=(256, 40)` e `pre_cores=96`) |
| `Sprite - comparacao no jogo.png` | comparação do overworld no jogo |
| `Trainer - desconhecido.png` | front pic, autor **desconhecido** — **ainda não registrada** |
| `Trainer - comparacao no jogo.png` | comparação da front pic no jogo |
| `outras/Sprite - zender1752.jpg` | overworld antigo (zender1752), trocado pela arte nova em 30/09/2026 |

### Battle sprite (front pic)

Não existe no código. A arte está em `.filetransfer/.trainers/Olivia/Trainer - desconhecido.png`; falta converter e registrar (skills `converter-sprite` e `adicionar-grafico-trainer`).

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`). A pasta da arte não traz mugshot.

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

Nenhuma. Ao criar, seguir a skill `adicionar-batalha-npc` (e `alocar-flag` se precisar de flag nova).

Homônimo que **não** é a personagem: `TRAINER_OLIVIA` (ID 130, classe Beauty, Corsola e Corsola de Galar), usado em `data/maps/Route38/scripts.inc` e `data/maps/SootopolisCity_Gym_B1F/scripts.inc`.

### Time das Rift Missions

📝 **Proposta de 30/09/2026, aguardando o autor.** `TRAINER_NEXUS_OLIVIA`, ID **a alocar** (IDs livres abaixo de 1056; não usar 1056–1163), campeã da **Tapu Lele**. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega; 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler).

Pic `Cooltrainer F` — **pic provisória até registrar a arte**. Classe `Elite Four`, música `Elite Four`.

Lendário **Necrozma**, o prisma: uma pedra negra que come luz, para a joalheira que vive de pedras que devolvem a luz. Semi-lendário **Tapu Lele**, a guardiã de Akala, de quem ela é Kahuna e campeã; o Psychic Surge reforça o Photon Geyser do Necrozma. Mega **Aerodactyl** (Rocktite, Tough Claws): o fóssil que volta do Old Amber, a gema que uma joalheira guardaria na vitrine. Mais **Lycanroc** Midnight (o ás dela, do Z-Move Continental Crush), **Probopass** e **Carbink** (a joia viva), do time dela na Elite Four.

*Plano (Singles):* o Carbink põe Stealth Rock e Reflect/Light Screen com Light Clay; a Tapu Lele de Choice Specs bate no Psychic Terrain; o Necrozma arma Calm Mind atrás do Prism Armor e das telas; o Lycanroc de Focus Sash acerta Stone Edge sempre (No Guard); o Probopass de Assault Vest segura os especiais.

*Plano (Doubles):* o formato em que o time brilha (`Double Battle: Yes`). O Psychic Terrain tira a prioridade do outro lado (nada de Fake Out nos aliados no chão); a Mega Aerodactyl põe Tailwind e as duas pedras — dela e do Lycanroc, que nunca erra — caem de Rock Slide nos dois oponentes; o Carbink sustenta as telas. Nenhum golpe do time acerta o parceiro.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Necrozma | Life Orb | Prism Armor | Modest | Photon Geyser, Earth Power, Power Gem, Calm Mind |
| Tapu Lele | Choice Specs | Psychic Surge | Timid | Psychic, Moonblast, Dazzling Gleam, Focus Blast |
| Aerodactyl | Rocktite | Unnerve | Jolly | Rock Slide, Dual Wingbeat, Tailwind, Protect |
| Lycanroc-Midnight | Focus Sash | No Guard | Jolly | Stone Edge, Close Combat, Crunch, Rock Slide |
| Probopass | Assault Vest | Sturdy | Modest | Power Gem, Earth Power, Thunderbolt, Flash Cannon |
| Carbink | Light Clay | Sturdy | Bold | Reflect, Light Screen, Stealth Rock, Moonblast |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>dev_scripts/nexus_validar_time.py</code>: trainerproc, constantes, learnsets e categorias)</summary>

```
=== TRAINER_NEXUS_OLIVIA ===
Name: Olivia
Class: Elite Four
Pic: Cooltrainer F
Gender: Female
Music: Elite Four
Double Battle: Yes
AI: Smart Trainer

Necrozma @ Life Orb
Modest Nature
Level: 100
Ability: Prism Armor
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Photon Geyser
- Earth Power
- Power Gem
- Calm Mind

Tapu Lele @ Choice Specs
Timid Nature
Level: 100
Ability: Psychic Surge
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Psychic
- Moonblast
- Dazzling Gleam
- Focus Blast

Aerodactyl @ Rocktite
Jolly Nature
Level: 100
Ability: Unnerve
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Rock Slide
- Dual Wingbeat
- Tailwind
- Protect

Lycanroc-Midnight @ Focus Sash
Jolly Nature
Level: 100
Ability: No Guard
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Stone Edge
- Close Combat
- Crunch
- Rock Slide

Probopass @ Assault Vest
Modest Nature
Level: 100
Ability: Sturdy
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Power Gem
- Earth Power
- Thunderbolt
- Flash Cannon

Carbink @ Light Clay
Bold Nature
Level: 100
Ability: Sturdy
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Reflect
- Light Screen
- Stealth Rock
- Moonblast

```

</details>

### Lendário associado

#### Tapu Lele

📝 **Proposta de 30/09/2026, aguardando o autor.** **Tapu Lele**, cedida pela **Lillie** (que fica com o Lunala), pela tabela "Campeões novos" de [`DIARIO_LOOKER.md`](../DIARIO_LOOKER.md). Enquanto o autor não aprova, o código e a ficha da Lillie continuam como estão. Olivia seria a campeã dela: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Olivia, Kahuna de Akala em Sun/Moon e membro da Elite Four de Alola: especialista em Pedra, dona da loja de joias de Konikoni City, brincalhona, dramática e sempre saindo de um fora amoroso. É a Kahuna escolhida pela Tapu Lele.

**A criatura.** Tapu Lele, a guardiã de Akala. Espalha escamas brilhantes que curam quem as toca — e, dizem, em excesso fazem mal. A Pokédex a chama de "natureza em pessoa": não é boa nem má, e não sente culpa pelo que faz. O templo dela é a Ruins of Life.

**O fragmento.** Já existe no jogo e **não é reescrito**: as escamas caindo como neve sobre um jardim, as flores que abriram demais, os Pokémon dormindo fundo demais. É Akala no fragmento da Olivia, depois que a guardiã curou o coração dela e não parou mais.

- Chegada: `Nexus_Text_TapuLele_Arrival` (`data/scripts/nexus.inc`)
- Boss: `Nexus_Text_TapuLele_Boss`
- Ficha do Looker: `Nexus_EventScript_TapuLele_LookerFile` → `Nexus_Text_TapuLele_LookerFile` (**File L-786. Guardian of Akala.**), ver a ficha da [Lillie](lillie.md#tapu-lele).

> ⚠️ O Looker File de hoje fala da campeã atual ("a young lady who has learned where kindness should stop"). A frase quase serve para a Olivia sem mudar nada — ela aprendeu exatamente isso —, mas "young lady" é a Lillie; se a troca for aprovada, vale revisar.

O caderno da Olivia (três páginas) está em [`diario_looker/olivia/`](diario_looker/olivia/1_comeco.md) e cita o `File L-786` como "see also".

### Diálogo genérico

📝 **Proposta de 30/09/2026, aguardando o autor.** Quando a Olivia cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala de si, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

A Olivia dos jogos fala alto, faz trocadilho com pedra e muda de humor ao lembrar do último namorado. Esta é a única pessoa do fragmento dela que ainda sabe ficar triste — e acha isso um luxo.

**Antes da luta**

> Alola! Kahuna of Akala, part-time jeweler, full-time rock enthusiast.
>
> You know what gems are? Just rocks that got squeezed hard enough, for long enough.
>
> So let's squeeze. Hard!

**Derrota**

> Oof. You cut clean. Nice facets.
>
> I'd put you right in the front window.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Olivia_Intro:
	.string "Alola! Kahuna of Akala, part-time\n"
	.string "jeweler, full-time rock enthusiast.\p"
	.string "You know what gems are? Just rocks\n"
	.string "that got squeezed hard enough, for\l"
	.string "long enough.\p"
	.string "So let's squeeze. Hard!$"

Nexus_Text_Olivia_Defeat:
	.string "Oof. You cut clean. Nice facets.\p"
	.string "I'd put you right in the front window.$"
```

</details>

#### Variações 2 e 3 (📝 proposta de 30/09/2026)

**Variação 2** — o coração partido, com humor.

**Antes da luta**

> Word of advice? Never date a guy who calls rocks “just rocks.”
>
> Never date a guy who forgets your anniversary three years running, either.
>
> Actually, forget dating. Battling is way more honest. Let's go!

**Derrota**

> …Great. Dumped by a battle, too.
>
> Kidding! Mostly. You were great.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Olivia_Intro2:
	.string "Word of advice? Never date a guy who\n"
	.string "calls rocks “just rocks.”\p"
	.string "Never date a guy who forgets your\n"
	.string "anniversary three years running,\l"
	.string "either.\p"
	.string "Actually, forget dating. Battling is\n"
	.string "way more honest. Let's go!$"

Nexus_Text_Olivia_Defeat2:
	.string "…Great. Dumped by a battle, too.\p"
	.string "Kidding! Mostly. You were great.$"
```

</details>

**Variação 3** — o anel esquecido no balcão pelo homem de sobretudo (fio 3 do diário).

**Antes da luta**

> A man in a long coat bought a ring at my shop once. Paid in full.
>
> Then he walked off and left it on the counter. Never came back for it.
>
> Some people just leave things behind, huh? Let's battle!

**Derrota**

> Ha! Solid as bedrock. You're a keeper.
>
> Don't let anybody leave you on a counter, got it?

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Olivia_Intro3:
	.string "A man in a long coat bought a ring at my\n"
	.string "shop once. Paid in full.\p"
	.string "Then he walked off and left it on the\n"
	.string "counter. Never came back for it.\p"
	.string "Some people just leave things behind,\n"
	.string "huh? Let's battle!$"

Nexus_Text_Olivia_Defeat3:
	.string "Ha! Solid as bedrock. You're a keeper.\p"
	.string "Don't let anybody leave you on a\n"
	.string "counter, got it?$"
```

</details>

### Diálogo associado ao lendário

📝 **Proposta de 30/09/2026, aguardando o autor.** Quando a Olivia é a **campeã**, a luta logo antes do lendário. A fala é sobre a criatura, sem dizer o nome dela ([R16](../NEXUS_REGRAS.md)).

#### Tapu Lele

A guardiã cura tudo e não sabe onde parar. A Olivia pediu que ela curasse o coração dela depois de um fora, e a cura não parou mais: Akala inteira ficou contente e dormindo. Ela é a Kahuna que obrigou a guardiã a devolver o coração partido — e agora fica entre a porta e o jogador para que ninguém leve cura demais.

**Antes da luta**

> Careful. Past that door, there's a guardian that heals everything it touches.
>
> Scrapes, fevers, broken bones. Broken hearts, even. Trust me, I know.
>
> Thing is, it never knows when to stop. Let me show you how to say no!

**Derrota**

> Heh… Guess you already knew how.

**Depois da luta**

> I asked it to fix my heart once. After a real bad breakup.
>
> It did. Then it kept going, all over the island. Nobody on Akala could feel sad anymore.
>
> Nobody could feel much of anything. They just smiled and slept.
>
> I made it give mine back. Broken, but mine. …Go on. Don't take more than you need.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Olivia_ChampionIntro:
	.string "Careful. Past that door, there's a\n"
	.string "guardian that heals everything it\l"
	.string "touches.\p"
	.string "Scrapes, fevers, broken bones. Broken\n"
	.string "hearts, even. Trust me, I know.\p"
	.string "Thing is, it never knows when to stop.\n"
	.string "Let me show you how to say no!$"

Nexus_Text_Olivia_ChampionDefeat:
	.string "Heh… Guess you already knew how.$"

Nexus_Text_Olivia_ChampionAfter:
	.string "{SPEAKER NAME_OLIVIA}I asked it to fix my heart once. After a\n"
	.string "real bad breakup.\p"
	.string "It did. Then it kept going, all over the\n"
	.string "island. Nobody on Akala could feel sad\l"
	.string "anymore.\p"
	.string "Nobody could feel much of anything.\n"
	.string "They just smiled and slept.\p"
	.string "I made it give mine back. Broken, but\n"
	.string "mine. …Go on. Don't take more than you\l"
	.string "need.$"
```

</details>

Falante novo: `SP_NAME_OLIVIA` (ainda não existe em `include/constants/speaker_names.h`).

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

**Variação 2** — a Kahuna: a guardiã não é boa nem má, é muita coisa.

**Antes da luta**

> People call it a guardian deity. I've been its Kahuna for years.
>
> Here's the truth: it isn't kind. It isn't cruel. It's just… a lot. Like weather.
>
> Somebody has to stand between it and everybody else. Guess who!

**Derrota**

> Ow. Good thing I know someone with healing scales. …Kidding! Don't you dare.

**Depois da luta**

> Sometimes it drops by my shop. Hovers right over the display cases.
>
> It likes shiny things. Its scales look like crushed diamonds, you know.
>
> Worth nothing, though. They fade by morning. Nothing it gives lasts the right way.
>
> Go meet it. Keep your guard up, and keep your heart to yourself.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Olivia_ChampionIntro2:
	.string "People call it a guardian deity. I've\n"
	.string "been its Kahuna for years.\p"
	.string "Here's the truth: it isn't kind. It\n"
	.string "isn't cruel. It's just… a lot. Like\l"
	.string "weather.\p"
	.string "Somebody has to stand between it and\n"
	.string "everybody else. Guess who!$"

Nexus_Text_Olivia_ChampionDefeat2:
	.string "Ow. Good thing I know someone with\n"
	.string "healing scales. …Kidding! Don't you\l"
	.string "dare.$"

Nexus_Text_Olivia_ChampionAfter2:
	.string "{SPEAKER NAME_OLIVIA}Sometimes it drops by my shop. Hovers\n"
	.string "right over the display cases.\p"
	.string "It likes shiny things. Its scales look\n"
	.string "like crushed diamonds, you know.\p"
	.string "Worth nothing, though. They fade by\n"
	.string "morning. Nothing it gives lasts the\l"
	.string "right way.\p"
	.string "Go meet it. Keep your guard up, and\n"
	.string "keep your heart to yourself.$"
```

</details>

**Variação 3** — a joalheira: uma gema precisa dos defeitos.

**Antes da luta**

> If I could cut one of its scales, I'd make the prettiest ring in all of Alola.
>
> Nobody would ever feel sick wearing it. Or sad. Or anything.
>
> …Yeah, no. I'll stick to rocks. Let's rock!

**Derrota**

> Aw, rocks. …See what I did there?

**Depois da luta**

> Here's a Kahuna tip: a gem needs its flaws. That's how you know it's real.
>
> The thing behind that door wants to polish every flaw out of everybody.
>
> What comes home with you will be tiny, and it'll hum at you.
>
> Love it anyway. Just don't let it polish you.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Olivia_ChampionIntro3:
	.string "If I could cut one of its scales, I'd\n"
	.string "make the prettiest ring in all of Alola.\p"
	.string "Nobody would ever feel sick wearing it.\n"
	.string "Or sad. Or anything.\p"
	.string "…Yeah, no. I'll stick to rocks. Let's\n"
	.string "rock!$"

Nexus_Text_Olivia_ChampionDefeat3:
	.string "Aw, rocks. …See what I did there?$"

Nexus_Text_Olivia_ChampionAfter3:
	.string "{SPEAKER NAME_OLIVIA}Here's a Kahuna tip: a gem needs its\n"
	.string "flaws. That's how you know it's real.\p"
	.string "The thing behind that door wants to\n"
	.string "polish every flaw out of everybody.\p"
	.string "What comes home with you will be tiny,\n"
	.string "and it'll hum at you.\p"
	.string "Love it anyway. Just don't let it\n"
	.string "polish you.$"
```

</details>
