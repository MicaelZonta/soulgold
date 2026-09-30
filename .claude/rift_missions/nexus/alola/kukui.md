# Professor Kukui

**Região da ficha:** Alola

Aparece no checklist como:

- **Professor Kukui** (Alola · Elite Four e Campeões) — professor que testa o jogador na primeira defesa do título em *Sun/Moon*.

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
| `OBJ_EVENT_GFX_KUKUI` | `graphics/object_events/pics/people/special/kukui.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_KUKUI` | `graphics/trainers/front_pics/kukui.png` |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

> **Atenção:** Personagem do arco das Rift Missions (M3 Cherrygrove, reunião de Olivine, altar).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_KUKUI` | 966 | 0x8C6 | Lycanroc Midday Lv78, Braviary Lv78, Ninetales Alola Lv79, Magnezone Lv79, Snorlax Lv79, Incineroar Lv80 | `CherrygroveCity` |

### Time das Rift Missions

✅ **Implementado em 27/09/2026** (a proposta abaixo virou código): `TRAINER_NEXUS_KUKUI` = **1038** (flag de batalha `0x90E`, limpa antes e depois de cada luta), bloco em `src/data/trainers.party`, nível pelo R2 (tabela em `src/data/nexus/trainers.h`). Fala genérica `Nexus_EventScript_Kukui_Fight`; campeão: `Nexus_EventScript_Kukui_Solgaleo_ChampionFight` (para Solgaleo), `Nexus_EventScript_Kukui_TapuKoko_ChampionFight` (para Tapu Koko). Tudo em `data/scripts/nexus.inc`, sem blackout, resultado em `VAR_TEMP_3`. Para testar: menu de debug → Rift Missions… → Nexus fights… → Kukui.

📝 **Proposta de 27/09/2026, aguardando o autor.** `TRAINER_NEXUS_KUKUI`, campeão de Solgaleo e Tapu Koko. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler).

Lendário **Solgaleo**, o sol, par do Lunala da Lillie: o professor que estuda o instante em que um golpe acerta, com a criatura cujo golpe é o próprio corpo (Sunsteel Strike). Veio de um fragmento, como todo treinador do Nexus. Semi-lendário **Tapu Koko**, o guardião de Melemele, a ilha do laboratório dele e a outra luta de campeão. Mega **Snorlax** Gigantamax (Normalite), o Snorlax do time dele em Sun/Moon. Mais **Incineroar** (o que ele solta em Cherrygrove), Lycanroc Midday (o Rockruff dele) e Braviary, do `TRAINER_KUKUI`. É o time mais "de Doubles" do lote: o Kukui gosta de Battle Royal.

*Plano (Singles):* o Lycanroc (Focus Sash) arma Stealth Rock; o Incineroar gira com Parting Shot e o Tapu Koko com Volt Switch, trazendo o Solgaleo (Full Metal Body + Weakness Policy) ou o Snorlax Gmax com Curse para a hora certa.

*Plano (Doubles):* Fake Out + Intimidate do Incineroar e Tailwind do Braviary no primeiro turno; Electric Terrain do Tapu Koko impede sono. Rock Slide de dois lados (Lycanroc e Braviary) e Dazzling Gleam; o Snorlax usa High Horsepower (alvo único) em vez de Earthquake, para não acertar o parceiro.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Solgaleo | Weakness Policy | Full Metal Body | Adamant | Sunsteel Strike, Flare Blitz, Close Combat, Morning Sun |
| Tapu Koko | Life Orb | Electric Surge | Timid | Thunderbolt, Dazzling Gleam, Volt Switch, Taunt |
| Snorlax | Normalite | Thick Fat | Careful | Body Slam, Heavy Slam, Curse, High Horsepower |
| Lycanroc | Focus Sash | Steadfast | Jolly | Accelerock, Rock Slide, Close Combat, Stealth Rock |
| Incineroar | Sitrus Berry | Intimidate | Adamant | Fake Out, Flare Blitz, Darkest Lariat, Parting Shot |
| Braviary | Sharp Beak | Defiant | Adamant | Brave Bird, Close Combat, Tailwind, Rock Slide |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>dev_scripts/nexus_validar_time.py</code>)</summary>

```
=== TRAINER_NEXUS_KUKUI ===
Name: Kukui
Class: Expert
Pic: Kukui
Gender: Male
Music: Hg Boy 1
Double Battle: Yes
AI: Smart Trainer

Solgaleo @ Weakness Policy
Adamant Nature
Level: 100
Ability: Full Metal Body
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Sunsteel Strike
- Flare Blitz
- Close Combat
- Morning Sun

Tapu Koko @ Life Orb
Timid Nature
Level: 100
Ability: Electric Surge
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Thunderbolt
- Dazzling Gleam
- Volt Switch
- Taunt

Snorlax @ Normalite
Careful Nature
Level: 100
Ability: Thick Fat
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Body Slam
- Heavy Slam
- Curse
- High Horsepower

Lycanroc @ Focus Sash
Jolly Nature
Level: 100
Ability: Steadfast
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Accelerock
- Rock Slide
- Close Combat
- Stealth Rock

Incineroar @ Sitrus Berry
Adamant Nature
Level: 100
Ability: Intimidate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Fake Out
- Flare Blitz
- Darkest Lariat
- Parting Shot

Braviary @ Sharp Beak
Adamant Nature
Level: 100
Ability: Defiant
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Brave Bird
- Close Combat
- Tailwind
- Rock Slide
```

</details>

### Lendário associado

#### Solgaleo

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_Solgaleo_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Solgaleo**. Kukui é o campeão dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Professor Kukui, pesquisador de golpes, "cousin". Reportou os sinais de Cherrygrove na M3, soltou o Incineroar no banco de areia e pediu ao Elm as leituras que levaram a New Bark; no Altar se despediu querendo uma batalha numa praia "sem nada saindo dela".

**A criatura.** Solgaleo, o lendário do sol, forma final do Cosmog. Vive em outro mundo e emite uma luz tão forte que a noite mais escura fica clara como meio-dia; no Sunsteel Strike ele se lança como um meteoro.

**O fragmento.** Uma praça à meia-noite, clara como meio-dia. O relógio da torre diz uma coisa e o céu diz outra, e todas as sombras apontam para o mesmo lado, para longe de algo que ainda não apareceu.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> The clock on the tower said midnight. The sky said noon.
>
> Every shadow in the square pointed the same way, away from something just out of sight.

**Boss**

> All the shadows swung around at once.
>
> It walked into the square, and the stones under its feet glowed white.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md): o que fica é o fragmento, no nível 1)

> File L-791. Sunne.
>
> A midnight lit up like noon, and a professor taking notes in it with a very large grin.
>
> What is left of it is a small cloud that glows when you speak to it. It begins again from there.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Solgaleo_Arrival:
	.string "The clock on the tower said midnight.\n"
	.string "The sky said noon.\p"
	.string "Every shadow in the square pointed the\n"
	.string "same way, away from something just\l"
	.string "out of sight.$"

Nexus_Text_Solgaleo_Boss:
	.string "All the shadows swung around at once.\p"
	.string "It walked into the square, and the\n"
	.string "stones under its feet glowed white.$"

Nexus_Text_Solgaleo_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-791. Sunne.\p"
	.string "A midnight lit up like noon, and a\n"
	.string "professor taking notes in it with a\l"
	.string "very large grin.\p"
	.string "What is left of it is a small cloud\n"
	.string "that glows when you speak to it. It\l"
	.string "begins again from there.$"
```

</details>


#### Tapu Koko

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_TapuKoko_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Tapu Koko**. Kukui é o campeão dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Professor Kukui, que tem o laboratório na praia de Melemele e batalha por curiosidade desde a primeira cena (design §3: treinador competente, sem mestre secreto).

**A criatura.** Tapu Koko, guardião de Melemele. Curioso ao extremo, junta nuvens de tempestade e guarda os raios no corpo; aparece nas batalhas por capricho. Em Sun/Moon salvou o protagonista e a Lillie de uma ponte que caía.

**O fragmento.** Um estádio vazio sob um céu cheio de nuvens de tempestade. Marcas de queimado cruzam o campo em anéis, como se alguém treinasse ali há muito tempo. Um raio cai no centro e fica lá: não é raio, é alguém segurando uma concha aberta.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> An empty stadium under a sky full of thunderclouds.
>
> Scorch marks crossed the field in rings, as if someone had practiced there for a very long time.

**Boss**

> Lightning struck the center of the field and stayed there.
>
> It wasn't lightning. It held the two halves of a shell open, and it looked at you with great interest.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md): o que fica é o fragmento, no nível 1)

> File L-785. Guardian of Melemele.
>
> A stadium with no crowd, and a guardian that keeps coming back to fight in it. The professor knows the feeling.
>
> The spark that followed you home is tiny, and already curious about me. I am not sure I like that.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_TapuKoko_Arrival:
	.string "An empty stadium under a sky full of\n"
	.string "thunderclouds.\p"
	.string "Scorch marks crossed the field in\n"
	.string "rings, as if someone had practiced\l"
	.string "there for a very long time.$"

Nexus_Text_TapuKoko_Boss:
	.string "Lightning struck the center of the\n"
	.string "field and stayed there.\p"
	.string "It wasn't lightning. It held the two\n"
	.string "halves of a shell open, and it looked\l"
	.string "at you with great interest.$"

Nexus_Text_TapuKoko_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-785. Guardian of Melemele.\p"
	.string "A stadium with no crowd, and a guardian\n"
	.string "that keeps coming back to fight in it.\l"
	.string "The professor knows the feeling.\p"
	.string "The spark that followed you home is\n"
	.string "tiny, and already curious about me. I\l"
	.string "am not sure I like that.$"
```

</details>

### Diálogo genérico

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Kukui_Fight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Kukui cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala de si, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

O Kukui de Sun/Moon pesquisa golpes deixando que o Rockruff os use nele mesmo. A virada: "a melhor forma de estudar um golpe é levar um", e o Lycanroc de hoje já o acertou cem vezes.

**Antes da luta**

> Alola, cousin! Woo, what a surprise!
>
> Here's a secret. The best way to study a move is to take one yourself. My Lycanroc's hit me a hundred times.
>
> Don't worry, I'll let our Pokémon handle this one, yeah? Here we go!

**Derrota**

> Woo! Now THAT was a move worth studying, yeah!

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Kukui_Intro:
	.string "Alola, cousin! Woo, what a surprise!\p"
	.string "Here's a secret. The best way to study\n"
	.string "a move is to take one yourself. My\l"
	.string "Lycanroc's hit me a hundred times.\p"
	.string "Don't worry, I'll let our Pokémon\n"
	.string "handle this one, yeah? Here we go!$"

Nexus_Text_Kukui_Defeat:
	.string "Woo! Now THAT was a move worth\n"
	.string "studying, yeah!$"
```

</details>

#### Variações 2 e 3 (📝 proposta de 30/09/2026)

📝 **Proposta de 30/09/2026, aguardando o autor.** A variação 1 é a que já está no jogo (acima). Estas duas também servem para qualquer sala e qualquer dia ([R16](../NEXUS_REGRAS.md)): falam só de Kukui. Nada disto está no código.

**Variação 2 — o som antes.** O Kukui fundou uma Liga. O melhor som do mundo, para ele, não é a torcida: é o instante antes do primeiro golpe, quando todo mundo prende a respiração. Construiu um estádio inteiro para ouvir isso. Na derrota, o som logo depois é melhor ainda.

**Antes da luta**

> Alola, cousin! Hey, you know what the best sound in the world is?
>
> It's not a crowd. It's the moment right before the first move, when everybody's holding their breath.
>
> I built a whole stadium just to hear that sound. Woo! Let's make it!

**Derrota**

> Woo! And THAT'S the sound right after! Even better, yeah!

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Kukui_Intro2:
	.string "Alola, cousin! Hey, you know what the\n"
	.string "best sound in the world is?\p"
	.string "It's not a crowd. It's the moment right\n"
	.string "before the first move, when\l"
	.string "everybody's holding their breath.\p"
	.string "I built a whole stadium just to hear\n"
	.string "that sound. Woo! Let's make it!$"

Nexus_Text_Kukui_Defeat2:
	.string "Woo! And THAT'S the sound right after!\n"
	.string "Even better, yeah!$"
```

</details>

**Variação 3 — perder sorrindo.** O aprendiz do Hala. O velho mestre dizia que o Kukui perdia sorrindo; o amigo dele perdia sem sorrir, e o Kukui acha que isso fez toda a diferença (o Guzma, sem nome). Então, ganhando ou perdendo, ele sorri.

**Antes da luta**

> You know, I lost a lot growing up. My old teacher said I always lost with a smile on.
>
> My buddy lost too, but he never smiled. I think that made all the difference, yeah.
>
> So win or lose, I'm smiling! Let's go, cousin!

**Derrota**

> See? Still smiling! Woo!

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Kukui_Intro3:
	.string "You know, I lost a lot growing up. My old\n"
	.string "teacher said I always lost with a smile\l"
	.string "on.\p"
	.string "My buddy lost too, but he never smiled.\n"
	.string "I think that made all the difference,\l"
	.string "yeah.\p"
	.string "So win or lose, I'm smiling! Let's go,\n"
	.string "cousin!$"

Nexus_Text_Kukui_Defeat3:
	.string "See? Still smiling! Woo!$"
```

</details>


### Diálogo associado ao lendário

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Kukui é o **campeão**, a luta logo antes do lendário do dia. Uma fala por lendário; o nome da espécie não aparece ([R16](../NEXUS_REGRAS.md)). Rótulos com a espécie porque Kukui é campeão de dois.

#### Solgaleo

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Kukui_Solgaleo_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

O Kukui fala como pesquisador: viu a criatura andar e iluminar a noite, e anotou que ela brilha mais forte logo antes de investir, um meteoro em que o meteoro é o Pokémon. Ele lembra que o parceiro do jogador começou como uma nuvenzinha (vale para Solgaleo e Lunala, e o fragmento do R17 é exatamente isso). A virada, no depois: com tanta luz, ela nunca queima o que está em volta; escolhe para onde vai o calor. "Esse é o golpe mais forte que existe."

**Antes da luta**

> Cousin! Did you see it walk? A night like this, and it lights the whole place up like midday!
>
> I've been watching its steps. It glows brightest right before it charges. A meteor, but the meteor's the Pokémon!
>
> And your partner started out as a tiny cloud too, yeah? Woo! Show me how far you two have come!

**Derrota**

> Woo! You two shine brighter than midday, yeah!

**Depois da luta**

> Here's my notes, cousin. It glows so bright, nothing can hide near it. Not even itself.
>
> So it never sneaks. It walks straight at you, every time.
>
> Thing is, all that light, and it never burns what's around it. It picks where the heat goes.
>
> That's the strongest move there is, yeah? Go show it you know it too!

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Kukui_Solgaleo_ChampionIntro:
	.string "Cousin! Did you see it walk? A night\n"
	.string "like this, and it lights the whole\l"
	.string "place up like midday!\p"
	.string "I've been watching its steps. It glows\n"
	.string "brightest right before it charges. A\l"
	.string "meteor, but the meteor's the Pokémon!\p"
	.string "And your partner started out as a tiny\n"
	.string "cloud too, yeah? Woo! Show me how far\l"
	.string "you two have come!$"

Nexus_Text_Kukui_Solgaleo_ChampionDefeat:
	.string "Woo! You two shine brighter than\n"
	.string "midday, yeah!$"

Nexus_Text_Kukui_Solgaleo_ChampionAfter:
	.string "{SPEAKER NAME_KUKUI}Here's my notes, cousin. It glows so\n"
	.string "bright, nothing can hide near it. Not\l"
	.string "even itself.\p"
	.string "So it never sneaks. It walks straight\n"
	.string "at you, every time.\p"
	.string "Thing is, all that light, and it never\n"
	.string "burns what's around it. It picks\l"
	.string "where the heat goes.\p"
	.string "That's the strongest move there is,\n"
	.string "yeah? Go show it you know it too!$"
```

</details>

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

📝 **Proposta de 30/09/2026, aguardando o autor.** A variação 1 é a que já está no jogo (acima). Sobre a criatura, pelo olhar de Kukui, sem o nome da espécie ([R16](../NEXUS_REGRAS.md)). Nada disto está no código.

**Variação 2 — a luz acesa.** O relógio diz meia-noite, o céu diz meio-dia, ninguém dorme e as sombras fogem da criatura. O Kukui gosta: alguém lá fora pode precisar da luz para achar o caminho de casa. No depois: a esposa dele estuda o outro lado, onde é sempre escuro, então alguém tem que deixar uma luz acesa deste lado (Burnet, sem nome; é a página 2 do diário).

**Antes da luta**

> Cousin, here's what I can't figure out. It's midnight. My watch says so. The sky says noon.
>
> Nobody's slept in ages, yeah. Too bright. The shadows all point away from it, like they're scared.
>
> But me? I kinda like it. Somebody out there might need the light to find their way home.
>
> Woo! Let's light this place up even more!

**Derrota**

> Woo! Blinding, cousin! Totally blinding!

**Depois da luta**

> Here's a thing I noticed. It never looks back at its shadow. Doesn't have one.
>
> My wife studies the other side, yeah. The places past the holes in the sky.
>
> She says it's always dark out there. So I figure somebody's gotta keep a light on over here.
>
> Go on, cousin. Walk straight at it. That's the only way it knows.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Kukui_Solgaleo_ChampionIntro2:
	.string "Cousin, here's what I can't figure out.\n"
	.string "It's midnight. My watch says so. The\l"
	.string "sky says noon.\p"
	.string "Nobody's slept in ages, yeah. Too\n"
	.string "bright. The shadows all point away from\l"
	.string "it, like they're scared.\p"
	.string "But me? I kinda like it. Somebody out\n"
	.string "there might need the light to find\l"
	.string "their way home.\p"
	.string "Woo! Let's light this place up even\n"
	.string "more!$"

Nexus_Text_Kukui_Solgaleo_ChampionDefeat2:
	.string "Woo! Blinding, cousin! Totally blinding!$"

Nexus_Text_Kukui_Solgaleo_ChampionAfter2:
	.string "{SPEAKER NAME_KUKUI}Here's a thing I noticed. It never\n"
	.string "looks back at its shadow. Doesn't have\l"
	.string "one.\p"
	.string "My wife studies the other side, yeah.\n"
	.string "The places past the holes in the sky.\p"
	.string "She says it's always dark out there. So\n"
	.string "I figure somebody's gotta keep a light\l"
	.string "on over here.\p"
	.string "Go on, cousin. Walk straight at it.\n"
	.string "That's the only way it knows.$"
```

</details>

**Variação 3 — pelo bem da ciência.** Humor de pesquisador: ele passou uma hora pedindo à criatura um golpe só, pela ciência, e ela chegou perto, olhou nos olhos dele e seguiu andando. "Acho que eu não valho um meteoro." No depois: tanto poder, e não bateu em quem pediu; os mais fortes escolhem. Deixe ela escolher você.

**Antes da luta**

> I've been asking it nicely for an hour, cousin. Just one hit. For science.
>
> It won't do it! It walked right up to me, looked me in the eye, and just... kept walking.
>
> Guess I'm not worth a meteor, yeah? Woo! Maybe you are!

**Derrota**

> Woo! Now THAT'S a meteor, cousin!

**Depois da luta**

> All that power, and it wouldn't hit a guy who asked for it. That's a lesson right there.
>
> The strongest ones don't swing at everything. They pick.
>
> Let it pick you. Go on, cousin!

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Kukui_Solgaleo_ChampionIntro3:
	.string "I've been asking it nicely for an hour,\n"
	.string "cousin. Just one hit. For science.\p"
	.string "It won't do it! It walked right up to\n"
	.string "me, looked me in the eye, and just...\l"
	.string "kept walking.\p"
	.string "Guess I'm not worth a meteor, yeah?\n"
	.string "Woo! Maybe you are!$"

Nexus_Text_Kukui_Solgaleo_ChampionDefeat3:
	.string "Woo! Now THAT'S a meteor, cousin!$"

Nexus_Text_Kukui_Solgaleo_ChampionAfter3:
	.string "{SPEAKER NAME_KUKUI}All that power, and it wouldn't hit a\n"
	.string "guy who asked for it. That's a lesson\l"
	.string "right there.\p"
	.string "The strongest ones don't swing at\n"
	.string "everything. They pick.\p"
	.string "Let it pick you. Go on, cousin!$"
```

</details>


#### Tapu Koko

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Kukui_TapuKoko_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

O Kukui reconhece o trovão: mora debaixo dele, em Melemele. O guardião tem mais curiosidade do que juízo, entra em qualquer batalha só para ver; já salvou duas crianças numa ponte quebrada e foi embora antes de alguém agradecer. A virada, no depois: ele não quer vencer, quer conhecer quem luta, e o Kukui admite que batalha pelo mesmo motivo.

**Antes da luta**

> Hear that thunder? I know that sound, cousin. I live right under it, back on Melemele.
>
> That guardian's got more curiosity than sense. It'll jump into any battle it hears about, just to see.
>
> Saved a couple of kids on a broken bridge once, too. Then it flew off before anyone could thank it.
>
> Woo! Let's give it something worth hearing about!

**Derrota**

> Woo! It heard that one for sure, yeah!

**Depois da luta**

> It keeps the lightning in its shell, cousin. Holds it close, like a secret.
>
> People on Melemele ask why it keeps showing up to fight. It doesn't want to win. It wants to know you.
>
> Honestly? Same reason I battle. Took me a while to admit it, yeah.
>
> Go on. Let it get to know you!

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Kukui_TapuKoko_ChampionIntro:
	.string "Hear that thunder? I know that sound,\n"
	.string "cousin. I live right under it, back on\l"
	.string "Melemele.\p"
	.string "That guardian's got more curiosity\n"
	.string "than sense. It'll jump into any battle\l"
	.string "it hears about, just to see.\p"
	.string "Saved a couple of kids on a broken\n"
	.string "bridge once, too. Then it flew off\l"
	.string "before anyone could thank it.\p"
	.string "Woo! Let's give it something worth\n"
	.string "hearing about!$"

Nexus_Text_Kukui_TapuKoko_ChampionDefeat:
	.string "Woo! It heard that one for sure,\n"
	.string "yeah!$"

Nexus_Text_Kukui_TapuKoko_ChampionAfter:
	.string "{SPEAKER NAME_KUKUI}It keeps the lightning in its shell,\n"
	.string "cousin. Holds it close, like a secret.\p"
	.string "People on Melemele ask why it keeps\n"
	.string "showing up to fight. It doesn't want\l"
	.string "to win. It wants to know you.\p"
	.string "Honestly? Same reason I battle. Took\n"
	.string "me a while to admit it, yeah.\p"
	.string "Go on. Let it get to know you!$"
```

</details>

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

📝 **Proposta de 30/09/2026, aguardando o autor.** A variação 1 é a que já está no jogo (acima). Sobre a criatura, pelo olhar de Kukui, sem o nome da espécie ([R16](../NEXUS_REGRAS.md)). Nada disto está no código.

**Variação 2 — o mascarado.** O Masked Royal, sem dizer que é ele. Um sujeito de máscara luta num estádio vazio toda noite, e toda noite o guardião cai da tempestade para lutar com ele: sem público, sem prêmio. O mascarado perde muito e volta sempre. "Não pergunta como eu sei." No depois: ele aparece mesmo sem ninguém olhando; dê a ele uma plateia de um.

**Antes da luta**

> Cousin, can I tell you a secret? There's a masked fella who fights in an empty stadium every night.
>
> And every night, a guardian drops out of the storm to fight him. No crowd. No prize. Just the two of them.
>
> The masked fella loses a lot. Keeps coming back anyway. ...Don't ask how I know, yeah! Let's battle!

**Derrota**

> Woo! The masked fella would've loved that one!

**Depois da luta**

> It holds the lightning in its shell like it's saving it for someone.
>
> Doesn't matter if nobody's watching. It shows up anyway. That's the whole point, yeah.
>
> Go give it a crowd of one, cousin. Trust me, it's enough.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Kukui_TapuKoko_ChampionIntro2:
	.string "Cousin, can I tell you a secret?\n"
	.string "There's a masked fella who fights in an\l"
	.string "empty stadium every night.\p"
	.string "And every night, a guardian drops out\n"
	.string "of the storm to fight him. No crowd. No\l"
	.string "prize. Just the two of them.\p"
	.string "The masked fella loses a lot. Keeps\n"
	.string "coming back anyway. ...Don't ask how I\l"
	.string "know, yeah! Let's battle!$"

Nexus_Text_Kukui_TapuKoko_ChampionDefeat2:
	.string "Woo! The masked fella would've loved\n"
	.string "that one!$"

Nexus_Text_Kukui_TapuKoko_ChampionAfter2:
	.string "{SPEAKER NAME_KUKUI}It holds the lightning in its shell like\n"
	.string "it's saving it for someone.\p"
	.string "Doesn't matter if nobody's watching.\n"
	.string "It shows up anyway. That's the whole\l"
	.string "point, yeah.\p"
	.string "Go give it a crowd of one, cousin. Trust\n"
	.string "me, it's enough.$"
```

</details>

**Variação 3 — o ciúme.** Quando criança, o Kukui subia às ruínas toda semana e esperava o dia inteiro; o guardião nunca desceu para ele, e desceu para uma criança numa ponte (a da variação 1). Levou anos para parar de ter ciúme, e ainda tem um pouco. No depois: ele aparece para quem o deixa curioso, não para quem espera mais; então o Kukui parou de esperar e passou a ser interessante.

**Antes da luta**

> When I was a kid, I climbed up to its ruins every week. Waited all day.
>
> It never came down for me. Not once, yeah. It came down for some kids on a bridge instead.
>
> Took me years to stop being jealous. Woo! Kinda still am! Let's go!

**Derrota**

> Woo! It'd come down for you, cousin. No doubt.

**Depois da luta**

> It shows up for whoever makes it curious. Not for whoever waits the longest.
>
> So I quit waiting and started being interesting. Built a League. Studied moves.
>
> It still hasn't come down for me. But I've had a great time, yeah. Go on!

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Kukui_TapuKoko_ChampionIntro3:
	.string "When I was a kid, I climbed up to its\n"
	.string "ruins every week. Waited all day.\p"
	.string "It never came down for me. Not once,\n"
	.string "yeah. It came down for some kids on a\l"
	.string "bridge instead.\p"
	.string "Took me years to stop being jealous.\n"
	.string "Woo! Kinda still am! Let's go!$"

Nexus_Text_Kukui_TapuKoko_ChampionDefeat3:
	.string "Woo! It'd come down for you, cousin. No\n"
	.string "doubt.$"

Nexus_Text_Kukui_TapuKoko_ChampionAfter3:
	.string "{SPEAKER NAME_KUKUI}It shows up for whoever makes it\n"
	.string "curious. Not for whoever waits the\l"
	.string "longest.\p"
	.string "So I quit waiting and started being\n"
	.string "interesting. Built a League. Studied\l"
	.string "moves.\p"
	.string "It still hasn't come down for me. But\n"
	.string "I've had a great time, yeah. Go on!$"
```

</details>


Falante: `SP_NAME_KUKUI` já existe em `include/constants/speaker_names.h`.
