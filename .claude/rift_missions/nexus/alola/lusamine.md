# Lusamine

**Região da ficha:** Alola

Aparece no checklist como:

- **Lusamine** (Alola · Team Skull e Aether Foundation) — presidente da Aether Foundation obcecada pelas Ultra Beasts.

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
| `OBJ_EVENT_GFX_LUSAMINE` | `graphics/object_events/pics/people/special/lusamine.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_LUSAMINE` | `graphics/trainers/front_pics/lusamine.png` |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

> **Atenção:** Personagem do arco das Rift Missions; `TRAINER_LUSAMINE_ALTAR` é o duelo do clímax (ALTAR_SUN_MOON).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_LUSAMINE` | 964 | 0x8C4 | Clefable Lv70, Lilligant Lv70, Mismagius Lv71, Bewear Lv71, Milotic Lv72 | `SunMoonAltar` |
| `TRAINER_LUSAMINE_ALTAR` | 972 | 0x8CC | Clefable Lv78, Lilligant Lv78, Mismagius Lv79, Bewear Lv79, Milotic Lv79, Nihilego Lv80 | `SunMoonAltar` |

### Time das Rift Missions

✅ **Implementado em 27/09/2026** (a proposta abaixo virou código): `TRAINER_NEXUS_LUSAMINE` = **1039** (flag de batalha `0x90F`, limpa antes e depois de cada luta), bloco em `src/data/trainers.party`, nível pelo R2 (tabela em `src/data/nexus/trainers.h`). Fala genérica `Nexus_EventScript_Lusamine_Fight`; campeão: `Nexus_EventScript_Lusamine_Enamorus_ChampionFight` (para Enamorus), `Nexus_EventScript_Lusamine_Fezandipiti_ChampionFight` (para Fezandipiti). Tudo em `data/scripts/nexus.inc`, sem blackout, resultado em `VAR_TEMP_3`. Para testar: menu de debug → Rift Missions… → Nexus fights… → Lusamine.

📝 **Proposta de 27/09/2026, aguardando o autor.** `TRAINER_NEXUS_LUSAMINE`, campeã de Enamorus e Fezandipiti. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler).

Lendário **Xerneas**, que segundo a lenda pode partilhar a vida eterna: a Lusamine congelava Pokémon para mantê-los belos para sempre, e agora carrega a criatura que dá vida em vez de parar o tempo. Semi-lendário **Nihilego**, a UB que a Aether confiou aos cuidados dela depois do resgate das nove (Altar, `SunMoonAltar_Text_LusaminePost`; sem fusão). Ela é campeã de Enamorus e Fezandipiti, mas a Nihilego é quem conta a história dela; se o autor preferir, a Enamorus (Fada/Voador) entra no lugar sem mudar o plano. Mega **Clefable** (Fairytite), a primeira do time dela em Sun/Moon. Mais Mismagius, Bewear e Milotic, do `TRAINER_LUSAMINE_ALTAR` (a Milotic é a que saiu da Ball em New Bark).

*Plano (Singles):* a Nihilego (Focus Sash) arma Toxic Spikes, a Mismagius espalha Will-O-Wisp, e o Xerneas usa Geomancy num turno só com Power Herb. A Clefable Mega (Magic Guard) sobe Calm Mind e se cura; a Milotic (Marvel Scale com Flame Orb) segura físicos e devolve com Mirror Coat.

*Plano (Doubles):* Geomancy do Xerneas no primeiro turno, com a Fairy Aura reforçando o Dazzling Gleam de dois alvos dele e da Mismagius e o Moonblast da Clefable. Icy Wind da Milotic controla a velocidade; a Bewear (Fluffy, Assault Vest) quebra Aço e Veneno com Drain Punch, a fraqueza de um time de Fadas. Nada no time acerta o parceiro.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Xerneas | Power Herb | Fairy Aura | Modest | Geomancy, Moonblast, Dazzling Gleam, Focus Blast |
| Nihilego | Focus Sash | Beast Boost | Timid | Sludge Bomb, Power Gem, Thunderbolt, Toxic Spikes |
| Clefable | Fairytite | Magic Guard | Calm | Moonblast, Moonlight, Calm Mind, Thunder Wave |
| Mismagius | Life Orb | Levitate | Timid | Shadow Ball, Dazzling Gleam, Will-O-Wisp, Nasty Plot |
| Bewear | Assault Vest | Fluffy | Adamant | Double-Edge, Drain Punch, Ice Punch, Darkest Lariat |
| Milotic | Flame Orb | Marvel Scale | Bold | Scald, Recover, Icy Wind, Mirror Coat |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>dev_scripts/nexus_validar_time.py</code>)</summary>

```
=== TRAINER_NEXUS_LUSAMINE ===
Name: Lusamine
Class: Beauty
Pic: Lusamine
Gender: Female
Music: Hg Girl 2
Double Battle: Yes
AI: Smart Trainer

Xerneas @ Power Herb
Modest Nature
Level: 100
Ability: Fairy Aura
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Geomancy
- Moonblast
- Dazzling Gleam
- Focus Blast

Nihilego @ Focus Sash
Timid Nature
Level: 100
Ability: Beast Boost
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Sludge Bomb
- Power Gem
- Thunderbolt
- Toxic Spikes

Clefable @ Fairytite
Calm Nature
Level: 100
Ability: Magic Guard
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Moonblast
- Moonlight
- Calm Mind
- Thunder Wave

Mismagius @ Life Orb
Timid Nature
Level: 100
Ability: Levitate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Shadow Ball
- Dazzling Gleam
- Will-O-Wisp
- Nasty Plot

Bewear @ Assault Vest
Adamant Nature
Level: 100
Ability: Fluffy
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Double-Edge
- Drain Punch
- Ice Punch
- Darkest Lariat

Milotic @ Flame Orb
Bold Nature
Level: 100
Ability: Marvel Scale
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Scald
- Recover
- Icy Wind
- Mirror Coat
```

</details>

### Lendário associado

#### Enamorus

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_Enamorus_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Enamorus**. Lusamine é a campeã dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Lusamine, presidente da Aether Foundation e mãe da Lillie e do Gladion. Neste hack trouxe o campo de contenção à M4, aceitou ficar na base no Altar e seguiu uma instrução da filha no resgate; no pós-game, chá com os filhos em Olivine.

**A criatura.** Enamorus, a quarta Força da Natureza, de Hisui. Quando ela chega voando do outro lado do mar, o inverno acaba e o amor dela faz brotar vida nova; mas desce das nuvens para punir sem piedade quem desrespeita qualquer forma de vida.

**O fragmento.** Um campo em pleno inverno, e depois, numa linha reta atravessando a neve, a primavera. Flores abrem atrás de um vento morno; do outro lado da linha a neve nem se mexeu. Quando o vento vira, as flores mais perto do jogador murcham.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> Winter, and then, in a single line across the field, spring.
>
> Flowers opened behind a warm wind. On the other side of the line, the snow had not moved at all.

**Boss**

> The warm wind stopped and turned around.
>
> Something rode down on it from the clouds, smiling, and the flowers nearest you began to wilt.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md): o que fica é o fragmento, no nível 1)

> File L-905. Love-Hate.
>
> A spring that arrives for everyone, and a punishment for anyone who forgets to be kind.
>
> The lady from the Aether Foundation read this twice, and asked me to leave it as it is.
>
> What stayed with you is small and warm, and has not decided what it thinks of you yet.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Enamorus_Arrival:
	.string "Winter, and then, in a single line\n"
	.string "across the field, spring.\p"
	.string "Flowers opened behind a warm wind. On\n"
	.string "the other side of the line, the snow\l"
	.string "had not moved at all.$"

Nexus_Text_Enamorus_Boss:
	.string "The warm wind stopped and turned\n"
	.string "around.\p"
	.string "Something rode down on it from the\n"
	.string "clouds, smiling, and the flowers\l"
	.string "nearest you began to wilt.$"

Nexus_Text_Enamorus_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-905. Love-Hate.\p"
	.string "A spring that arrives for everyone,\n"
	.string "and a punishment for anyone who\l"
	.string "forgets to be kind.\p"
	.string "The lady from the Aether Foundation\n"
	.string "read this twice, and asked me to leave\l"
	.string "it as it is.\p"
	.string "What stayed with you is small and\n"
	.string "warm, and has not decided what it\l"
	.string "thinks of you yet.$"
```

</details>


#### Fezandipiti

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_Fezandipiti_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Fezandipiti**. Lusamine é a campeã dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Lusamine, que teve um paraíso (Aether Paradise) e aplausos por ele, enquanto por dentro colecionava e congelava. Neste hack, a reparação é perguntar e escutar.

**A criatura.** Fezandipiti, um dos Loyal Three de Kitakami. Bate as asas brilhantes e solta um perfume que encanta; as correntes (Toxic Chain) envenenam e dominam a vontade de quem é tocado. Os três ganharam estátuas de heróis na vila, mas eram os vilões da lenda.

**O fragmento.** Uma praça cheia de flores e fitas, todas aos pés de uma estátua: um pássaro de pedra de asas abertas, com um colar de contas de vidro no pescoço. As contas pingam. Um cheiro doce desce do alto e dá vontade de admirar o que vier.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A plaza full of flowers and ribbons, all laid at the feet of one statue.
>
> A bird carved in stone, wings open, with a chain of glass beads around its neck. The beads were dripping.

**Boss**

> A sweet smell drifted down. You felt a sudden, strong wish to admire whatever came next.
>
> It landed on the statue's head and spread its wings for you.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md): o que fica é o fragmento, no nível 1)

> File L-1016. Retainer.
>
> A hero with a statue in the square, and a poison under the feathers that no one wanted to see.
>
> The lady who fought there knows about statues. She says she never wants another one.
>
> What you brought back is small and plain, and nobody will build it a statue. It seems relieved.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Fezandipiti_Arrival:
	.string "A plaza full of flowers and ribbons,\n"
	.string "all laid at the feet of one statue.\p"
	.string "A bird carved in stone, wings open,\n"
	.string "with a chain of glass beads around its\l"
	.string "neck. The beads were dripping.$"

Nexus_Text_Fezandipiti_Boss:
	.string "A sweet smell drifted down. You felt\n"
	.string "a sudden, strong wish to admire\l"
	.string "whatever came next.\p"
	.string "It landed on the statue's head and\n"
	.string "spread its wings for you.$"

Nexus_Text_Fezandipiti_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-1016. Retainer.\p"
	.string "A hero with a statue in the square,\n"
	.string "and a poison under the feathers that\l"
	.string "no one wanted to see.\p"
	.string "The lady who fought there knows about\n"
	.string "statues. She says she never wants\l"
	.string "another one.\p"
	.string "What you brought back is small and\n"
	.string "plain, and nobody will build it a\l"
	.string "statue. It seems relieved.$"
```

</details>

### Diálogo genérico

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Lusamine_Fight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Lusamine cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala de si, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

A Lusamine é formal e habituada a decidir; a reparação aparece quando ela pergunta e escuta (design §3). O detalhe concreto é a coleção congelada de Sun/Moon; a virada é que agora ela pede antes.

**Antes da luta**

> Ah. A Trainer. Forgive me, I was admiring your Pokémon.
>
> There was a time I would have wanted to keep them. Frozen, perfect, never changing.
>
> My daughter taught me to ask first. So I am asking. Will you battle me?

**Derrota**

> Beautiful. I won't try to keep that moment. I will only remember it.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Lusamine_Intro:
	.string "Ah. A Trainer. Forgive me, I was\n"
	.string "admiring your Pokémon.\p"
	.string "There was a time I would have wanted\n"
	.string "to keep them. Frozen, perfect, never\l"
	.string "changing.\p"
	.string "My daughter taught me to ask first. So\n"
	.string "I am asking. Will you battle me?$"

Nexus_Text_Lusamine_Defeat:
	.string "Beautiful. I won't try to keep that\n"
	.string "moment. I will only remember it.$"
```

</details>

### Diálogo associado ao lendário

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Lusamine é a **campeã**, a luta logo antes do lendário do dia. Uma fala por lendário; o nome da espécie não aparece ([R16](../NEXUS_REGRAS.md)). Rótulos com a espécie porque Lusamine é campeã de dois.

#### Enamorus

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Lusamine_Enamorus_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

A Lusamine passou pela primavera que a criatura trouxe e conhece a lenda: o amor dela faz tudo florescer, e ela cai das nuvens sobre quem trata a vida sem respeito. Antes, ela a quereria na coleção; hoje acha que a criatura teria vindo atrás dela. A virada, no depois: esse amor não fica, traz a primavera e segue. Ela achava que amar era guardar; os filhos ensinaram outra coisa, e "ainda estão ensinando". Sem declarar a família consertada.

**Antes da luta**

> Did you walk through the spring out there? It came with that creature.
>
> They say its love makes every living thing bloom. They also say it falls from the clouds on anyone who treats life without respect.
>
> Once, I would have wanted it in my collection. Today I think it would have come for me.
>
> ...Let us see what you have learned about love, then.

**Derrota**

> You treated them with respect, even in battle. I noticed.

**Depois da luta**

> Its love does not stay. It brings the spring, and then it moves on.
>
> I used to believe love meant keeping. Holding still whatever I found beautiful.
>
> My children taught me otherwise. They are still teaching me.
>
> Go. Be kind to it, even if it is not kind to you.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Lusamine_Enamorus_ChampionIntro:
	.string "Did you walk through the spring out\n"
	.string "there? It came with that creature.\p"
	.string "They say its love makes every living\n"
	.string "thing bloom. They also say it falls\l"
	.string "from the clouds on anyone who treats\l"
	.string "life without respect.\p"
	.string "Once, I would have wanted it in my\n"
	.string "collection. Today I think it would have\l"
	.string "come for me.\p"
	.string "...Let us see what you have learned\n"
	.string "about love, then.$"

Nexus_Text_Lusamine_Enamorus_ChampionDefeat:
	.string "You treated them with respect, even in\n"
	.string "battle. I noticed.$"

Nexus_Text_Lusamine_Enamorus_ChampionAfter:
	.string "{SPEAKER NAME_LUSAMINE}Its love does not stay. It brings the\n"
	.string "spring, and then it moves on.\p"
	.string "I used to believe love meant keeping.\n"
	.string "Holding still whatever I found\l"
	.string "beautiful.\p"
	.string "My children taught me otherwise. They\n"
	.string "are still teaching me.\p"
	.string "Go. Be kind to it, even if it is not\n"
	.string "kind to you.$"
```

</details>


#### Fezandipiti

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Lusamine_Fezandipiti_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

A Lusamine olha a estátua e as flores ("todo mundo ama um herói") e depois as penas, e a corrente cheia de veneno que faz as pessoas adorarem a criatura. Ela teve um paraíso e foi aplaudida; conhece aquela corrente por dentro. A virada, no depois: ninguém perguntou o que a estátua fez para merecer, e ninguém perguntou a ela também, porque ela garantiu que não perguntassem. Conselho: olhe a corrente, não as penas; e se sobrar dela algo pequeno (R17), deixe ser comum por um tempo.

**Antes da luta**

> What a beautiful statue out there. All those flowers. Everyone loves a hero.
>
> Its feathers are lovely, too. Look closer, and the chain around its neck is full of poison. It makes people adore it.
>
> I had a paradise once, and people applauded. I know how that chain feels from the inside.
>
> ...Come. Let us not keep the audience waiting.

**Derrota**

> No applause, please. You simply won.

**Depois da luta**

> People built that statue out of gratitude. They never asked what it had done to earn it.
>
> No one asked me, either. I made very sure they would not.
>
> When you face it, don't look at the feathers too long. Look at the chain.
>
> ...And if anything is left of it, let it be ordinary for a while. It may be a relief.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Lusamine_Fezandipiti_ChampionIntro:
	.string "What a beautiful statue out there. All\n"
	.string "those flowers. Everyone loves a hero.\p"
	.string "Its feathers are lovely, too. Look\n"
	.string "closer, and the chain around its neck\l"
	.string "is full of poison. It makes people\l"
	.string "adore it.\p"
	.string "I had a paradise once, and people\n"
	.string "applauded. I know how that chain feels\l"
	.string "from the inside.\p"
	.string "...Come. Let us not keep the audience\n"
	.string "waiting.$"

Nexus_Text_Lusamine_Fezandipiti_ChampionDefeat:
	.string "No applause, please. You simply won.$"

Nexus_Text_Lusamine_Fezandipiti_ChampionAfter:
	.string "{SPEAKER NAME_LUSAMINE}People built that statue out of\n"
	.string "gratitude. They never asked what it\l"
	.string "had done to earn it.\p"
	.string "No one asked me, either. I made very\n"
	.string "sure they would not.\p"
	.string "When you face it, don't look at the\n"
	.string "feathers too long. Look at the chain.\p"
	.string "...And if anything is left of it, let\n"
	.string "it be ordinary for a while. It may be\l"
	.string "a relief.$"
```

</details>


Falante: `SP_NAME_LUSAMINE` já existe em `include/constants/speaker_names.h`.
