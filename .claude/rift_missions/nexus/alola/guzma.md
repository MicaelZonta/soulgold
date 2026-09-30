# Guzma

**Região da ficha:** Alola

Aparece no checklist como:

- **Guzma** (Alola · Team Skull e Aether Foundation) — chefe carismático do Team Skull e especialista em Pokémon Inseto.

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
| `OBJ_EVENT_GFX_GUZMA` | `graphics/object_events/pics/people/special/guzma.png` |

32x32, doze quadros (`sAnimTable_StandardAsym`, igual à Lusamine). Convertido em 26/09/2026 da arte em `.filetransfer/`.

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_GUZMA` | `graphics/trainers/front_pics/guzma.png` |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

Nenhuma. Ao criar, seguir a skill `adicionar-batalha-npc` (e `alocar-flag` se precisar de flag nova).

### Time das Rift Missions

✅ **Implementado em 26/09/2026** (a proposta abaixo virou código): `TRAINER_NEXUS_GUZMA` = **981** (flag de batalha `0x8D5`, limpa antes e depois de cada luta), bloco em `src/data/trainers.party`, nível pelo `sNexusTrainerIds` (`src/data/level_scaling_rules.h`, R2). Falas e lutas em `data/scripts/nexus.inc`: `Nexus_EventScript_Guzma_Fight` (genérica) e `Nexus_EventScript_Guzma_ChampionFight` (campeão), sem blackout, resultado em `VAR_TEMP_3`. Para testar: menu de debug → Rift Missions… → Nexus fights… → Guzma.

📝 **Proposta de 26/09/2026, aguardando o autor.** `TRAINER_NEXUS_GUZMA`, campeão da Guzzlord. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler).

Lendário **Yveltal**, o Pokémon da destruição; semi-lendário **Buzzwole**, a outra UB de Inseto, que vive de exibir força, o espelho do Guzma; Mega **Golisopod** (Bugtite: Inseto/Aço), o ás dele. Mais Ariados, Scizor e Vikavolt, do time dele em Sun/Moon. *Plano:* destruição sem freio. O Ariados lança Sticky Web e Toxic Spikes, o Yveltal bate com Dark Aura e Life Orb, Scizor e Vikavolt entram de Choice, e o Buzzwole sobe com Bulk Up.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Yveltal | Life Orb | Dark Aura | Naive | Dark Pulse, Oblivion Wing, Heat Wave, Sucker Punch |
| Buzzwole | Leftovers | Beast Boost | Adamant | Leech Life, Drain Punch, Ice Punch, Bulk Up |
| Golisopod | Bugtite | Emergency Exit | Adamant | First Impression, Liquidation, Leech Life, Knock Off |
| Ariados | Focus Sash | Insomnia | Jolly | Sticky Web, Toxic Spikes, Poison Jab, Sucker Punch |
| Scizor | Choice Band | Technician | Adamant | Bullet Punch, U-turn, Knock Off, Superpower |
| Vikavolt | Choice Specs | Levitate | Modest | Thunderbolt, Bug Buzz, Energy Ball, Volt Switch |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>trainerproc</code>, constantes, learnsets e categorias)</summary>

```
=== TRAINER_NEXUS_GUZMA ===
Name: Guzma
Class: Expert
Pic: Guzma
Gender: Male
Music: Intense
Double Battle: No
AI: Smart Trainer

Yveltal @ Life Orb
Naive Nature
Level: 100
Ability: Dark Aura
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Dark Pulse
- Oblivion Wing
- Heat Wave
- Sucker Punch

Buzzwole @ Leftovers
Adamant Nature
Level: 100
Ability: Beast Boost
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Leech Life
- Drain Punch
- Ice Punch
- Bulk Up

Golisopod @ Bugtite
Adamant Nature
Level: 100
Ability: Emergency Exit
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- First Impression
- Liquidation
- Leech Life
- Knock Off

Ariados @ Focus Sash
Jolly Nature
Level: 100
Ability: Insomnia
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Sticky Web
- Toxic Spikes
- Poison Jab
- Sucker Punch

Scizor @ Choice Band
Adamant Nature
Level: 100
Ability: Technician
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Bullet Punch
- U-turn
- Knock Off
- Superpower

Vikavolt @ Choice Specs
Modest Nature
Level: 100
Ability: Levitate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Thunderbolt
- Bug Buzz
- Energy Ball
- Volt Switch
```

</details>


### Lendário associado

✅ **Aprovado em 26/09/2026:** a fala de campeão implementada (`Nexus_EventScript_Guzma_ChampionFight`) é sobre este lendário. O sorteio do Daily que usa a ligação ainda não existe.

**Proposta de 26/09/2026:** **Guzzlord** (UB-05 Glutton). Guzma é o campeão dela: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Guzma, chefe da Team Skull. Foi aprendiz do Hala junto com o Kukui, perdeu para o Kukui, teve negado o posto de Trial Captain e fez da destruição a própria identidade.

**A criatura.** Guzzlord já devorou montanhas e engoliu prédios inteiros, e parece estar sempre comendo. Mundo em USUM: Ultra Ruin, uma cidade em ruínas.

**O fragmento.** Uma cidade, ou o que sobrou dela. Metade dos prédios não caiu: sumiu, como se tivesse sido mordida. Longe, alguma coisa ainda mastiga.

**Falas do fragmento** (narração e Looker; tocam só nos dias desta UB):

**Chegada**

> A city, or what was left of one.
>
> Half the buildings were gone. Not fallen. Missing, as if bitten off.
>
> Somewhere far away, something was still chewing.

**Boss**

> The chewing stopped.
>
> A mouth that was most of a body turned toward you, and the street in front of it was simply not there anymore.

**Looker File** — ✅ implementado em 27/09/2026 como **caderno no chão da sala do campeão** ([R18](../NEXUS_REGRAS.md)), descrevendo o universo do fragmento. O texto do jogo foi reescrito e está em `data/scripts/nexus.inc` (`Nexus_Text_<Conceito>_LookerFile`) — ele vence o rascunho abaixo, que era a versão antiga "no altar, no dia da captura".

> File UB-05. Glutton.
>
> A city eaten down to the street, and a young man sitting in it who used to think that was what strength looked like.
>
> He does not think so now. I have written that down for him, in case he ever asks.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Glutton_Arrival:
	.string "A city, or what was left of one.\p"
	.string "Half the buildings were gone. Not\n"
	.string "fallen. Missing, as if bitten off.\p"
	.string "Somewhere far away, something was still\n"
	.string "chewing.$"

Nexus_Text_Glutton_Boss:
	.string "The chewing stopped.\p"
	.string "A mouth that was most of a body turned\n"
	.string "toward you, and the street in front of\l"
	.string "it was simply not there anymore.$"

Nexus_Text_Glutton_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File UB-05. Glutton.\p"
	.string "A city eaten down to the street, and a\n"
	.string "young man sitting in it who used to\l"
	.string "think that was what strength looked\l"
	.string "like.\p"
	.string "He does not think so now. I have written\n"
	.string "that down for him, in case he ever asks.$"
```

</details>


### Diálogo genérico

✅ **Implementado em 26/09/2026:** `Nexus_EventScript_Guzma_Fight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

**Proposta de 26/09/2026:** Quando Guzma cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala dele mesmo, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

**Antes da luta**

> You lost, kid? Yeah. Me too.
>
> Don't matter where I end up. Wherever Guzma goes, stuff gets broken.
>
> Might as well start with you!

**Derrota**

> …Tch. Figures. Even here, huh.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Guzma_Intro:
	.string "You lost, kid? Yeah. Me too.\p"
	.string "Don't matter where I end up. Wherever\n"
	.string "Guzma goes, stuff gets broken.\p"
	.string "Might as well start with you!$"

Nexus_Text_Guzma_Defeat:
	.string "…Tch. Figures. Even here, huh.$"
```

</details>

#### Variações 2 e 3 (📝 proposta de 30/09/2026)

📝 **Proposta de 30/09/2026, aguardando o autor.** A variação 1 é a que já está no jogo (acima). Estas duas também servem para qualquer sala e qualquer dia ([R16](../NEXUS_REGRAS.md)): falam só de Guzma. Nada disto está no código.

**Variação 2 — capitão.** A ferida de origem: o velho (o Hala, sem nome) disse na cara dele que ele não tinha estofo de Trial Captain. Então ele fez o próprio time, as próprias regras e muita bagunça. Na derrota, o eco amargo.

**Antes da luta**

> Big bad Guzma, kid. You heard of me? No? Figures.
>
> Old man back home said I wasn't Captain material. Said it right to my face.
>
> So I made my own team. My own rules. A whole lotta mess. Let's add you to it!

**Derrota**

> ...Captain material, huh. Guess not.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Guzma_Intro2:
	.string "Big bad Guzma, kid. You heard of me? No?\n"
	.string "Figures.\p"
	.string "Old man back home said I wasn't\n"
	.string "Captain material. Said it right to my\l"
	.string "face.\p"
	.string "So I made my own team. My own rules. A\n"
	.string "whole lotta mess. Let's add you to it!$"

Nexus_Text_Guzma_Defeat2:
	.string "...Captain material, huh. Guess not.$"
```

</details>

**Variação 3 — saber a hora de correr.** Humor com o Golisopod (Emergency Exit): quando a coisa aperta, ele corre de volta para a bola. O pessoal ri; o Guzma não, porque saber a hora de cair fora é talento. Mas ele não vai fugir do jogador. Na derrota, o Golisopod já está no meio do caminho de volta.

**Antes da luta**

> You know what my Golisopod does when things go bad? Runs. Straight back to the ball.
>
> Folks laugh. I don't. Knowin' when to bail is a skill, kid.
>
> ...Not that I'm bailin' on you! Get over here!

**Derrota**

> Yeah, yeah. Golisopod's already halfway back to the ball.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Guzma_Intro3:
	.string "You know what my Golisopod does when\n"
	.string "things go bad? Runs. Straight back to\l"
	.string "the ball.\p"
	.string "Folks laugh. I don't. Knowin' when to\n"
	.string "bail is a skill, kid.\p"
	.string "...Not that I'm bailin' on you! Get over\n"
	.string "here!$"

Nexus_Text_Guzma_Defeat3:
	.string "Yeah, yeah. Golisopod's already\n"
	.string "halfway back to the ball.$"
```

</details>


### Diálogo associado ao lendário

✅ **Implementado em 26/09/2026:** `Nexus_EventScript_Guzma_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

**Proposta de 26/09/2026:** Quando Guzma é o **campeão**, a luta logo antes da Guzzlord. A fala é sobre a criatura, sem dizer o nome dela.

O Guzma viu a boca comer um prédio, e depois o seguinte. Em casa diziam que ele era a destruição andando em duas pernas, e ele gostava. Até ver aquilo mastigar uma cidade inteira e continuar com fome, e não achar graça nenhuma. A derrota é a dele de sempre ("tudo o que eu tenho, e ainda não basta"). O que fica é o que ninguém conta: quem destrói tudo não fica satisfeito depois, só fica parado numa bagunça maior. O Kukui disse isso uma vez, sobre ele, e o Guzma demorou para ouvir.

**Antes da luta**

> You seen it? That big mouth down the road? It ate a building while I watched. Then it ate the next one.
>
> Folks back home used to say I was destruction walkin' around on two legs. I kinda liked it.
>
> Then I watched that thing chew through a whole city and still look hungry.
>
> …It ain't fun to watch. Let's just go!

**Derrota**

> Again. Everything I got, and it still ain't enough.

**Depois da luta**

> Here's what nobody tells ya. When you wreck everything, you ain't full after. You're just standin' in a bigger mess.
>
> That thing's never gonna be full. Not ever.
>
> Kukui told me that once. About me. Took me a long time to hear it.
>
> Go on. Go show that mouth what enough looks like.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Guzma_ChampionIntro:
	.string "You seen it? That big mouth down the\n"
	.string "road? It ate a building while I watched.\l"
	.string "Then it ate the next one.\p"
	.string "Folks back home used to say I was\n"
	.string "destruction walkin' around on two legs.\l"
	.string "I kinda liked it.\p"
	.string "Then I watched that thing chew through\n"
	.string "a whole city and still look hungry.\p"
	.string "…It ain't fun to watch. Let's just go!$"

Nexus_Text_Guzma_ChampionDefeat:
	.string "Again. Everything I got, and it still\n"
	.string "ain't enough.$"

Nexus_Text_Guzma_ChampionAfter:
	.string "{SPEAKER NAME_GUZMA}Here's what nobody tells ya. When you\n"
	.string "wreck everything, you ain't full after.\l"
	.string "You're just standin' in a bigger mess.\p"
	.string "That thing's never gonna be full. Not\n"
	.string "ever.\p"
	.string "Kukui told me that once. About me. Took\n"
	.string "me a long time to hear it.\p"
	.string "Go on. Go show that mouth what enough\n"
	.string "looks like.$"
```

</details>

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

📝 **Proposta de 30/09/2026, aguardando o autor.** A variação 1 é a que já está no jogo (acima). Sobre a criatura, pelo olhar de Guzma, sem o nome da espécie ([R16](../NEXUS_REGRAS.md)). Nada disto está no código.

**Variação 2 — o espelho.** Três dias olhando a boca mastigar, e o Guzma notou que ela não parece feliz, nem sente gosto de nada: come porque é a única coisa que sabe fazer. "Que espelho." No depois: todo mundo tem medo dela e ninguém pergunta do que ela tem tanta fome; ninguém perguntou para ele também.

**Antes da luta**

> Watched it chew for three days straight, kid. Know what I noticed?
>
> It don't look happy. Not once. It don't even look like it's tastin' anything.
>
> It just eats 'cause it's the only thing it knows how to do. ...Heh. Some mirror. Let's go!

**Derrota**

> ...Yeah. That's about how it feels. Every time.

**Depois da luta**

> Everybody's scared of it. Nobody ever asks what it's so hungry for.
>
> Nobody asked me, neither. I'd've said somethin' dumb, but still.
>
> Go on. Ask it the only way it understands. Hit it hard.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Guzma_ChampionIntro2:
	.string "Watched it chew for three days\n"
	.string "straight, kid. Know what I noticed?\p"
	.string "It don't look happy. Not once. It don't\n"
	.string "even look like it's tastin' anything.\p"
	.string "It just eats 'cause it's the only thing\n"
	.string "it knows how to do. ...Heh. Some mirror.\l"
	.string "Let's go!$"

Nexus_Text_Guzma_ChampionDefeat2:
	.string "...Yeah. That's about how it feels.\n"
	.string "Every time.$"

Nexus_Text_Guzma_ChampionAfter2:
	.string "{SPEAKER NAME_GUZMA}Everybody's scared of it. Nobody ever\n"
	.string "asks what it's so hungry for.\p"
	.string "Nobody asked me, neither. I'd've said\n"
	.string "somethin' dumb, but still.\p"
	.string "Go on. Ask it the only way it\n"
	.string "understands. Hit it hard.$"
```

</details>

**Variação 3 — os meninos.** A cidade comida era parecida com a dele: muro, chuva, um monte de moleque que ninguém queria. O Guzma procurou os garotos dele no entulho e não achou nenhum; ótimo, quer dizer que saíram. No depois: pior do que uma coisa que come tudo é ser o último em pé no que sobrou. Vá, acabe com isso, saia e não volte por ele. Ecoa a página 2 do diário.

**Antes da luta**

> This place used to be a town like mine. Walls, rain, a bunch of kids nobody wanted.
>
> Now it's a street and half a street and a whole lotta nothin'. The mouth took the rest.
>
> I kept lookin' for my guys in the rubble. ...Didn't find 'em. Good. Means they got out. Let's go.

**Derrota**

> ...Big bad Guzma. Lost again. Somebody tell the guys.

**Depois da luta**

> Know what's worse than a thing that eats everything? Bein' the last guy standin' in what's left.
>
> Nobody to boss. Nobody to lose to. Just you and the chewin'.
>
> Go on, kid. Get it done. Then get out, and don't come back for me.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Guzma_ChampionIntro3:
	.string "This place used to be a town like mine.\n"
	.string "Walls, rain, a bunch of kids nobody\l"
	.string "wanted.\p"
	.string "Now it's a street and half a street and\n"
	.string "a whole lotta nothin'. The mouth took\l"
	.string "the rest.\p"
	.string "I kept lookin' for my guys in the\n"
	.string "rubble. ...Didn't find 'em. Good. Means\l"
	.string "they got out. Let's go.$"

Nexus_Text_Guzma_ChampionDefeat3:
	.string "...Big bad Guzma. Lost again. Somebody\n"
	.string "tell the guys.$"

Nexus_Text_Guzma_ChampionAfter3:
	.string "{SPEAKER NAME_GUZMA}Know what's worse than a thing that\n"
	.string "eats everything? Bein' the last guy\l"
	.string "standin' in what's left.\p"
	.string "Nobody to boss. Nobody to lose to. Just\n"
	.string "you and the chewin'.\p"
	.string "Go on, kid. Get it done. Then get out,\n"
	.string "and don't come back for me.$"
```

</details>
