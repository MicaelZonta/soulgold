# May

**Região da ficha:** Hoenn

Aparece no checklist como:

- **May** (Hoenn · Rivais) — protagonista ou rival, filha do Professor Birch.

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
| `OBJ_EVENT_GFX_LINK_RS_MAY` | `graphics/object_events/pics/people/ruby_sapphire_may/walking.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_RS_MAY` | `graphics/trainers/front_pics/may_rs.png` |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

> **Atenção:** `OBJ_EVENT_GFX_MAY_*` e `TRAINER_PIC_FRONT_MAY` **não são a May**: neste hack a arte foi trocada pela protagonista **Kris/Crystal** (os `TRAINER_RIVALCRYSTAL*` usam essa pic). A May de Hoenn de verdade é a arte de *Ruby/Sapphire* (`RS_`), listada acima. O overworld RS só tem andar/correr (sem bike/surf).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_MAY_PLACEHOLDER` | 854 | 0x856 | **sem time** (ID reservado, sem bloco no `.party`) | — (nenhum script chama) |

IDs aposentados na limpeza de treinadores (não reaproveitar sem necessidade): `TRAINER_UNUSED_409` (ex-`TRAINER_MAY_ROUTE_103_MUDKIP`, 529), `TRAINER_UNUSED_398` (ex-`TRAINER_MAY_ROUTE_110_MUDKIP`, 530), `TRAINER_UNUSED_404` (ex-`TRAINER_MAY_ROUTE_119_MUDKIP`, 531), `TRAINER_UNUSED_410` (ex-`TRAINER_MAY_ROUTE_103_TREECKO`, 532), `TRAINER_UNUSED_399` (ex-`TRAINER_MAY_ROUTE_110_TREECKO`, 533), `TRAINER_UNUSED_405` (ex-`TRAINER_MAY_ROUTE_119_TREECKO`, 534), `TRAINER_UNUSED_411` (ex-`TRAINER_MAY_ROUTE_103_TORCHIC`, 535), `TRAINER_UNUSED_400` (ex-`TRAINER_MAY_ROUTE_110_TORCHIC`, 536), `TRAINER_UNUSED_406` (ex-`TRAINER_MAY_ROUTE_119_TORCHIC`, 537), `TRAINER_UNUSED_415` (ex-`TRAINER_MAY_RUSTBORO_MUDKIP`, 600), `TRAINER_UNUSED_421` (ex-`TRAINER_MAY_LILYCOVE_MUDKIP`, 664), `TRAINER_UNUSED_422` (ex-`TRAINER_MAY_LILYCOVE_TREECKO`, 665), `TRAINER_UNUSED_423` (ex-`TRAINER_MAY_LILYCOVE_TORCHIC`, 666), `TRAINER_UNUSED_416` (ex-`TRAINER_MAY_RUSTBORO_TREECKO`, 768), `TRAINER_UNUSED_417` (ex-`TRAINER_MAY_RUSTBORO_TORCHIC`, 769).

### Time das Rift Missions

✅ **Implementado em 27/09/2026** (a proposta abaixo virou código): `TRAINER_NEXUS_MAY` = **1013** (flag de batalha `0x8F5`, limpa antes e depois de cada luta), bloco em `src/data/trainers.party`, nível pelo R2 (tabela em `src/data/nexus/trainers.h`). Fala genérica `Nexus_EventScript_May_Fight`; campeão: `Nexus_EventScript_May_Mesprit_ChampionFight` (para Mesprit), `Nexus_EventScript_May_Zekrom_ChampionFight` (para Zekrom). Tudo em `data/scripts/nexus.inc`, sem blackout, resultado em `VAR_TEMP_3`. Para testar: menu de debug → Rift Missions… → Nexus fights… → May.

📝 **Proposta de 27/09/2026, aguardando o autor.** `TRAINER_NEXUS_MAY`, campeã do Zekrom e do Mesprit. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler).

Pic `RS May` (`TRAINER_PIC_FRONT_RS_MAY`), a arte de Ruby/Sapphire; a `May` deste hack é a Kris/Crystal (ver a atenção acima). Lendário **Zekrom**, o dragão dos ideais, do qual ela é campeã: a menina que quer ver todo Pokémon que existe. Semi-lendário **Mesprit**, o Ser da Emoção, o outro de que é campeã. Mega **Blaziken** (Bondstone, a pedra do vínculo), a linha do Torchic, a parceira dela no anime. Mais **Blastoise**, **Venusaur** e **Snorlax**: o Squirtle, o Bulbasaur e o Munchlax dela no anime, aqui já evoluídos.

*Plano:* o Mesprit põe as telas e pivota; atrás delas, Zekrom e Mega Blaziken sobem (Dragon Dance, Speed Boost) e limpam; Snorlax e Venusaur seguram o jogo longo.
*Plano (Singles):* Mesprit de Light Clay arma Reflect e Light Screen e sai com U-turn; a Mega Blaziken usa Protect para ganhar um Speed Boost de graça; o Zekrom sobe Dragon Dance; o Venusaur desgasta com Leech Seed e Sleep Powder; o Snorlax (Thick Fat) aguenta com Curse e Rest.
*Plano (Doubles):* o Blastoise abre com Fake Out e, de HP cheio, Water Spout nos dois oponentes; o Mesprit segura as telas para os dois lados; Zekrom (Teravolt, que ignora habilidades defensivas) e Blaziken batem enquanto um deles usa Protect.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Zekrom | Life Orb | Teravolt | Adamant | Bolt Strike, Dragon Claw, Dragon Dance, Protect |
| Mesprit | Light Clay | Levitate | Calm | Reflect, Light Screen, Psychic, U-turn |
| Blaziken | Bondstone | Speed Boost | Adamant | Flare Blitz, Close Combat, Knock Off, Protect |
| Snorlax | Leftovers | Thick Fat | Careful | Body Slam, Curse, Rest, Heat Crash |
| Blastoise | Sitrus Berry | Rain Dish | Modest | Water Spout, Ice Beam, Fake Out, Protect |
| Venusaur | Black Sludge | Chlorophyll | Bold | Giga Drain, Sludge Bomb, Sleep Powder, Leech Seed |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>nexus_validar_time.py</code>: trainerproc, constantes, learnsets e categorias)</summary>

```
=== TRAINER_NEXUS_MAY ===
Name: May
Class: Rival
Pic: RS May
Gender: Female
Music: Female
Double Battle: No
AI: Smart Trainer

Zekrom @ Life Orb
Adamant Nature
Level: 100
Ability: Teravolt
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Bolt Strike
- Dragon Claw
- Dragon Dance
- Protect

Mesprit @ Light Clay
Calm Nature
Level: 100
Ability: Levitate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Reflect
- Light Screen
- Psychic
- U-turn

Blaziken @ Bondstone
Adamant Nature
Level: 100
Ability: Speed Boost
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Flare Blitz
- Close Combat
- Knock Off
- Protect

Snorlax @ Leftovers
Careful Nature
Level: 100
Ability: Thick Fat
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Body Slam
- Curse
- Rest
- Heat Crash

Blastoise @ Sitrus Berry
Modest Nature
Level: 100
Ability: Rain Dish
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Water Spout
- Ice Beam
- Fake Out
- Protect

Venusaur @ Black Sludge
Bold Nature
Level: 100
Ability: Chlorophyll
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Giga Drain
- Sludge Bomb
- Sleep Powder
- Leech Seed
```

</details>

### Lendário associado

#### Zekrom

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_Zekrom_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Zekrom**. May é a campeã dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** May, filha do Professor Birch, de Littleroot. Rival em Ruby/Sapphire/Emerald, alegre, faz pesquisa de campo para o pai e quer ver todos os Pokémon.

**A criatura.** Zekrom (Dragão/Elétrico), o Pokémon dos ideais, que ajuda quem quer construir um mundo ideal. Esconde-se voando dentro de nuvens de tempestade, e a cauda funciona como um gerador de eletricidade. Mundo em Black/White: Dragonspiral Tower.

**O fragmento.** Uma cidade de torres negras dentro de uma nuvem de tempestade. Todas as janelas acesas de leve, e o lugar inteiro zumbindo como se alguma coisa enorme estivesse carregando.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A city of black towers, inside a thundercloud.
>
> Every window glowed faintly. The whole place hummed, as if something enormous were charging.

**Boss**

> The hum became a roar. Lightning ran up every tower at once.
>
> In the heart of the cloud, a tail began to spin like a generator.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md))

> File L-644. Deep Black.
>
> A storm that pulls in whoever wants something badly enough, and a girl who wants to see everything.
>
> What came back with you is small, and your hair is standing up. So is mine.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Zekrom_Arrival:
	.string "A city of black towers, inside a\n"
	.string "thundercloud.\p"
	.string "Every window glowed faintly. The whole\n"
	.string "place hummed, as if something enormous\l"
	.string "were charging.$"

Nexus_Text_Zekrom_Boss:
	.string "The hum became a roar. Lightning ran up\n"
	.string "every tower at once.\p"
	.string "In the heart of the cloud, a tail began\n"
	.string "to spin like a generator.$"

Nexus_Text_Zekrom_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-644. Deep Black.\p"
	.string "A storm that pulls in whoever wants\n"
	.string "something badly enough, and a girl who\l"
	.string "wants to see everything.\p"
	.string "What came back with you is small, and\n"
	.string "your hair is standing up. So is mine.$"
```

</details>

#### Mesprit

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_Mesprit_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Mesprit**. May é a campeã dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** May, filha do Professor Birch, de Littleroot. Rival em Ruby/Sapphire/Emerald, alegre, faz pesquisa de campo para o pai e quer ver todos os Pokémon.

**A criatura.** Mesprit (Psíquico), o Ser da Emoção, que ensinou aos humanos a nobreza da tristeza, da dor e da alegria. Dorme no fundo do Lake Verity, e dizem que o espírito dele sai do corpo para voar sobre a superfície do lago. Mundo em Diamond/Pearl.

**O fragmento.** Um lago na neblina com rostos na superfície. Uns riem, outros choram, e cada vez que a água mexe eles trocam de lugar.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A lake in the fog, and on its surface, faces.
>
> Some were laughing and some were crying, and every time the water moved, they traded places.

**Boss**

> Something pink flew low over the water, and every face turned toward it.
>
> For a moment you felt happy and sad at once, and could not tell which had come first.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md))

> File L-481. Emotion.
>
> A lake that feels everything at once, and a girl who laughs so she will not have to cry.
>
> What came back with you cried a little on the way. So did she, I think. I have written that in pencil.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Mesprit_Arrival:
	.string "A lake in the fog, and on its surface,\n"
	.string "faces.\p"
	.string "Some were laughing and some were\n"
	.string "crying, and every time the water moved,\l"
	.string "they traded places.$"

Nexus_Text_Mesprit_Boss:
	.string "Something pink flew low over the water,\n"
	.string "and every face turned toward it.\p"
	.string "For a moment you felt happy and sad at\n"
	.string "once, and could not tell which had come\l"
	.string "first.$"

Nexus_Text_Mesprit_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-481. Emotion.\p"
	.string "A lake that feels everything at once,\n"
	.string "and a girl who laughs so she will not\l"
	.string "have to cry.\p"
	.string "What came back with you cried a little\n"
	.string "on the way. So did she, I think. I have\l"
	.string "written that in pencil.$"
```

</details>


### Diálogo genérico

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_May_Fight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando May cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala dela mesma, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

**Antes da luta**

> Hi! Wait, don't tell me. Traveling Trainer, first time here, a little lost?
>
> Me too! My dad says getting lost is the best way to find new Pokémon.
>
> And the best way to find out about a Trainer is a battle. Ready?

**Derrota**

> Aww! …Okay, that was fun anyway. I'm writing you down as 'strong.'

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_May_Intro:
	.string "Hi! Wait, don't tell me. Traveling\n"
	.string "Trainer, first time here, a little lost?\p"
	.string "Me too! My dad says getting lost is the\n"
	.string "best way to find new Pokémon.\p"
	.string "And the best way to find out about a\n"
	.string "Trainer is a battle. Ready?$"

Nexus_Text_May_Defeat:
	.string "Aww! …Okay, that was fun anyway. I'm\n"
	.string "writing you down as 'strong.'$"
```

</details>


### Diálogo associado ao lendário

#### Zekrom

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_May_Zekrom_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando May é a **campeã**, a luta logo antes do Zekrom. A fala é sobre a criatura, sem dizer o nome dela.

A May passou uma hora com o cabelo em pé perto da nuvem do Zekrom e não teve medo. Os livros dizem que ele só ajuda quem tem ideais fortes o bastante; o dela sempre foi um só, ver todo Pokémon que existe, e ela quer saber se isso é grande o bastante para uma lenda. A virada vem depois: o que assustou não foi o raio, foi a vontade de segui-lo. Um ideal não pergunta se você está cansada; só puxa. O pai diz que um bom pesquisador sabe a hora de voltar para casa, e ela ainda está aprendendo essa parte.

**Antes da luta**

> There's a black dragon inside that thundercloud. My hair's been standing up for an hour!
>
> The books say it only helps someone whose ideals are strong enough.
>
> I've only ever had one: to see every Pokémon there is. Is that big enough for a legend?
>
> Let's find out!

**Derrota**

> Ahaha… my ideals got zapped.

**Depois da luta**

> You know what scared me? Not the lightning. How badly I wanted to follow it.
>
> An ideal is like that. It never asks if you're tired. It just keeps pulling.
>
> Dad says a good researcher knows when to go home. I'm still learning that part.
>
> Go ahead. Just remember to come back, okay?

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_May_Zekrom_ChampionIntro:
	.string "There's a black dragon inside that\n"
	.string "thundercloud. My hair's been standing\l"
	.string "up for an hour!\p"
	.string "The books say it only helps someone\n"
	.string "whose ideals are strong enough.\p"
	.string "I've only ever had one: to see every\n"
	.string "Pokémon there is. Is that big enough\l"
	.string "for a legend?\p"
	.string "Let's find out!$"

Nexus_Text_May_Zekrom_ChampionDefeat:
	.string "Ahaha… my ideals got zapped.$"

Nexus_Text_May_Zekrom_ChampionAfter:
	.string "{SPEAKER NAME_MAY}You know what scared me? Not the\n"
	.string "lightning. How badly I wanted to follow\l"
	.string "it.\p"
	.string "An ideal is like that. It never asks if\n"
	.string "you're tired. It just keeps pulling.\p"
	.string "Dad says a good researcher knows when\n"
	.string "to go home. I'm still learning that part.\p"
	.string "Go ahead. Just remember to come back,\n"
	.string "okay?$"
```

</details>

#### Mesprit

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_May_Mesprit_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando May é a **campeã**, a luta logo antes do Mesprit. A fala é sobre a criatura, sem dizer o nome dela.

Cada vez que o Mesprit passa por cima do lago, a May tem vontade de rir e depois de chorar. As histórias dizem que ele ensinou às pessoas para que servem a alegria e a tristeza. A May é das que sempre riem, até quando perdem, principalmente quando perdem. A virada é o depois: ele passou por ela e ela chorou, só por um segundo, e não quis disfarçar com riso. É para isso que ele serve: lembrar que a parte triste também conta.

**Antes da luta**

> Something's flying over the lake. Every time it passes, I want to laugh, and then I want to cry.
>
> The old stories say it taught people what sorrow and joy are for.
>
> I guess I'm the kind who always laughs. Even when I lose. Especially then.
>
> Ready? I'll try not to laugh this time!

**Derrota**

> Ahaha… see? There it is.

**Depois da luta**

> Can I tell you something? It flew right past me and I cried. Just for a second.
>
> I didn't laugh it off. I didn't want to.
>
> I think that's what it's for. To remind you that the sad part counts too.
>
> Go on. And if you cry, that's okay. It's supposed to happen here.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_May_Mesprit_ChampionIntro:
	.string "Something's flying over the lake. Every\n"
	.string "time it passes, I want to laugh, and\l"
	.string "then I want to cry.\p"
	.string "The old stories say it taught people\n"
	.string "what sorrow and joy are for.\p"
	.string "I guess I'm the kind who always laughs.\n"
	.string "Even when I lose. Especially then.\p"
	.string "Ready? I'll try not to laugh this time!$"

Nexus_Text_May_Mesprit_ChampionDefeat:
	.string "Ahaha… see? There it is.$"

Nexus_Text_May_Mesprit_ChampionAfter:
	.string "{SPEAKER NAME_MAY}Can I tell you something? It flew right\n"
	.string "past me and I cried. Just for a second.\p"
	.string "I didn't laugh it off. I didn't want to.\p"
	.string "I think that's what it's for. To remind\n"
	.string "you that the sad part counts too.\p"
	.string "Go on. And if you cry, that's okay. It's\n"
	.string "supposed to happen here.$"
```

</details>

Falante novo: `SP_NAME_MAY` (o `_ChampionAfter` usa `{SPEAKER NAME_MAY}`; ainda não existe em `include/constants/speaker_names.h`, skill `nomear-falante`).
