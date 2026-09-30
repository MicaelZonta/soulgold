# Diantha

**Região da ficha:** Kalos

Aparece no checklist como:

- **Diantha — Campeã** (Kalos · Elite Four e Campeã) — famosa atriz e poderosa treinadora de Kalos.

**Pronto para o Nexus:** ❌ não — o overworld próprio entrou no código em 30/09/2026 (`OBJ_EVENT_GFX_DIANTHA`), mas falta a front pic (obrigatória).

**Arte disponível:** ✅ overworld e front pic em `.filetransfer/.trainers/Diantha/` (o overworld já registrado; a front pic, não).

## Checklist

- [x] Sprite de overworld *(obrigatório)* — `OBJ_EVENT_GFX_DIANTHA`, 30/09/2026
- [ ] Battle sprite / front pic *(obrigatório)* — arte disponível, falta registrar
- [ ] Field mugshot (retrato na caixa de diálogo)
- [ ] Time para as Rift Missions definido — 📝 proposta abaixo (30/09/2026), fora do código
- [ ] Associado a um lendário — 📝 proposta: Xerneas (cedido pelo Wallace)
- [ ] Diálogo genérico escrito — 📝 proposta abaixo, 3 variações
- [ ] Diálogo associado ao lendário escrito — 📝 proposta abaixo, 3 variações

## Referências no repositório

### Sprite de overworld

| Constante | Arquivo |
|---|---|
| `OBJ_EVENT_GFX_DIANTHA` | `graphics/object_events/pics/people/special/diantha.png` (16x32, 12 quadros, `sAnimTable_StandardAsym`; paleta própria `OBJ_EVENT_PAL_TAG_DIANTHA`) — registrado em 30/09/2026 |

Fonte da arte em `.filetransfer/.trainers/Diantha/`:

| Arquivo | O que é |
|---|---|
| `Sprite - Lolw3e932.png` | overworld, autor **Lolw3e932** (origem do `diantha.png` acima) |
| `Sprite - comparacao no jogo.png` | comparação do overworld no jogo |
| `Trainer - Brumirage.png` | front pic, autor **Brumirage** — **ainda não registrada** |
| `Trainer - comparacao no jogo.png` | comparação da front pic no jogo |

### Battle sprite (front pic)

Não existe no código. A arte está em `.filetransfer/.trainers/Diantha/Trainer - Brumirage.png`; falta converter e registrar (skills `converter-sprite` e `adicionar-grafico-trainer`).

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`). A pasta da arte não traz mugshot.

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

Nenhuma. Ao criar, seguir a skill `adicionar-batalha-npc` (e `alocar-flag` se precisar de flag nova).

### Time das Rift Missions

📝 **Proposta de 30/09/2026, aguardando o autor.** `TRAINER_NEXUS_DIANTHA`, ID **a alocar** (IDs livres abaixo de 1056; não usar 1056–1163), campeã do **Xerneas**. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega; 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler).

Pic `Beauty` — **pic provisória até registrar a arte**. Classe `Champion`, música `Hg Champion`.

Lendário **Xerneas**, a vida que não acaba, para a atriz que um dia disse, brincando, que queria ficar bonita para sempre. Semi-lendário **Iron Valiant**, o Paradoxo que vem do futuro de Gardevoir e Gallade: a beleza que durou tanto que virou metal. Mega **Gardevoir** (Fairytite, Pixilate), a Mega dela em X/Y. Mais **Hawlucha**, **Tyrantrum** e **Gourgeist**, do time de campeã dela (saem o Aurorus, fraco demais a Aço e Lutador, e o Goodra). Time de Fada com o Fairy Aura do Xerneas empurrando tudo: o Hyper Voice da Mega Gardevoir vira Fada e ganha o aura também.

*Plano (Singles):* o Gourgeist abre com Will-O-Wisp e Leech Seed e gasta o adversário; o Xerneas faz Geomancy num turno só (Power Herb) e limpa; o Hawlucha usa Close Combat, a White Herb desfaz a queda e liga o Unburden; o Tyrantrum arma Dragon Dance e bate Head Smash sem recuo (Rock Head); o Iron Valiant, rápido pela Booster Energy, prende quem se prepara com Encore.

*Plano (Doubles):* o formato em que o time brilha (`Double Battle: Yes`). Hyper Voice da Mega Gardevoir e Dazzling Gleam do Xerneas nos dois oponentes, os dois com Fairy Aura; o Iron Valiant tranca setup com Encore; o Hawlucha usa Taunt no Trick Room ou no suporte do outro lado; o Tyrantrum espalha Rock Slide. Nenhum golpe do time acerta o parceiro.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Xerneas | Power Herb | Fairy Aura | Modest | Geomancy, Moonblast, Dazzling Gleam, Focus Blast |
| Iron Valiant | Booster Energy | Quark Drive | Naive | Moonblast, Close Combat, Knock Off, Encore |
| Gardevoir | Fairytite | Trace | Timid | Hyper Voice, Psychic, Mystical Fire, Protect |
| Hawlucha | White Herb | Unburden | Jolly | Close Combat, Brave Bird, Swords Dance, Taunt |
| Tyrantrum | Life Orb | Rock Head | Adamant | Head Smash, Dragon Claw, Rock Slide, Dragon Dance |
| Gourgeist | Sitrus Berry | Frisk | Impish | Will-O-Wisp, Poltergeist, Leech Seed, Protect |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>dev_scripts/nexus_validar_time.py</code>: trainerproc, constantes, learnsets e categorias)</summary>

```
=== TRAINER_NEXUS_DIANTHA ===
Name: Diantha
Class: Champion
Pic: Beauty
Gender: Female
Music: Hg Champion
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

Iron Valiant @ Booster Energy
Naive Nature
Level: 100
Ability: Quark Drive
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Moonblast
- Close Combat
- Knock Off
- Encore

Gardevoir @ Fairytite
Timid Nature
Level: 100
Ability: Trace
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Hyper Voice
- Psychic
- Mystical Fire
- Protect

Hawlucha @ White Herb
Jolly Nature
Level: 100
Ability: Unburden
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Close Combat
- Brave Bird
- Swords Dance
- Taunt

Tyrantrum @ Life Orb
Adamant Nature
Level: 100
Ability: Rock Head
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Head Smash
- Dragon Claw
- Rock Slide
- Dragon Dance

Gourgeist @ Sitrus Berry
Impish Nature
Level: 100
Ability: Frisk
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Will-O-Wisp
- Poltergeist
- Leech Seed
- Protect

```

</details>

### Lendário associado

#### Xerneas

📝 **Proposta de 30/09/2026, aguardando o autor.** **Xerneas**, cedido pelo **Wallace** (que fica com a Diancie), pela tabela "Campeões novos" de [`DIARIO_LOOKER.md`](../DIARIO_LOOKER.md). Enquanto o autor não aprova, o código e a ficha do Wallace continuam como estão. Diantha seria a campeã dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Diantha, Campeã de Kalos em X/Y e estrela de cinema. Graciosa, calorosa, teatral. Em X/Y ela conversa com o Lysandre sobre ficar bonita para sempre — e é esse desejo, dito de brincadeira, que o fragmento dela leva a sério.

**A criatura.** Xerneas, o Pokémon da Vida. Dorme em forma de árvore por mil anos, acorda e dá vida aos outros; os chifres brilham em todas as cores. A arma suprema de Kalos, que o AZ construiu 3.000 anos atrás, foi movida pela energia de vida e de morte dos lendários de Kalos.

**O fragmento.** Já existe no jogo e **não é reescrito**: a floresta onde tudo floresce ao mesmo tempo e nada murcha, com a árvore de galhos de todas as cores no meio. É Kalos depois que a máquina, no fragmento da Diantha, deu vida em vez de tirar: nada morre, nada envelhece, nada termina.

- Chegada: `Nexus_Text_Xerneas_Arrival` (`data/scripts/nexus.inc`)
- Boss: `Nexus_Text_Xerneas_Boss`
- Ficha do Looker: `Nexus_EventScript_Xerneas_LookerFile` → `Nexus_Text_Xerneas_LookerFile` (**File L-716. The Everbloom.**), ver a ficha do [Wallace](../hoenn/wallace.md#xerneas).

> ⚠️ O Looker File de hoje fala do campeão atual ("an artist who has built his whole life on moments that do [fade]… He found that the loveliest thing in the file"). Se a troca for aprovada, o "his/He" precisa virar a Diantha — e a ideia serve melhor ainda para ela.

O caderno da Diantha (três páginas) está em [`diario_looker/diantha/`](diario_looker/diantha/1_comeco.md) e cita o `File L-716` como "see also".

### Diálogo genérico

📝 **Proposta de 30/09/2026, aguardando o autor.** Quando a Diantha cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala de si, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

A Diantha dos jogos trata qualquer luta como uma estreia. Esta é a mesma estrela, com cansaço de décadas por baixo do rosto que não mudou.

**Antes da luta**

> Oh! An audience. How wonderful.
>
> I've played queens, thieves and ghosts. Tonight, I'll play your opponent.
>
> Don't worry. I never break character. Shall we begin?

**Derrota**

> Bravo! Truly.
>
> I'd give you a standing ovation, but I'm already standing.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Diantha_Intro:
	.string "Oh! An audience. How wonderful.\p"
	.string "I've played queens, thieves and\n"
	.string "ghosts. Tonight, I'll play your\l"
	.string "opponent.\p"
	.string "Don't worry. I never break character.\n"
	.string "Shall we begin?$"

Nexus_Text_Diantha_Defeat:
	.string "Bravo! Truly.\p"
	.string "I'd give you a standing ovation, but\n"
	.string "I'm already standing.$"
```

</details>

#### Variações 2 e 3 (📝 proposta de 30/09/2026)

**Variação 2** — a lembrança do café e a pergunta do homem de juba vermelha (nunca nomeado).

**Antes da luta**

> Once, in a café, a man with a magnificent red mane asked me a question.
>
> “If you could stay just as you are forever, would you?” I laughed and said yes.
>
> I was joking, you know. Mostly. Now, let's see what you would say!

**Derrota**

> Wonderful. You battle like someone who plans to grow old.
>
> I envy that more than you know.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Diantha_Intro2:
	.string "Once, in a café, a man with a\n"
	.string "magnificent red mane asked me a\l"
	.string "question.\p"
	.string "“If you could stay just as you are\n"
	.string "forever, would you?” I laughed and\l"
	.string "said yes.\p"
	.string "I was joking, you know. Mostly. Now,\n"
	.string "let's see what you would say!$"

Nexus_Text_Diantha_Defeat2:
	.string "Wonderful. You battle like someone who\n"
	.string "plans to grow old.\p"
	.string "I envy that more than you know.$"
```

</details>

**Variação 3** — a atriz que ama cenas finais.

**Antes da luta**

> Every role I ever played had a final scene. I adored final scenes.
>
> Tears, a bow, the lights go down, and everyone goes home.
>
> Let's give this one a proper ending, shall we?

**Derrota**

> And… scene. Oh, that was lovely.
>
> Take a bow, darling. You've earned it.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Diantha_Intro3:
	.string "Every role I ever played had a final\n"
	.string "scene. I adored final scenes.\p"
	.string "Tears, a bow, the lights go down, and\n"
	.string "everyone goes home.\p"
	.string "Let's give this one a proper ending,\n"
	.string "shall we?$"

Nexus_Text_Diantha_Defeat3:
	.string "And… scene. Oh, that was lovely.\p"
	.string "Take a bow, darling. You've earned it.$"
```

</details>

### Diálogo associado ao lendário

📝 **Proposta de 30/09/2026, aguardando o autor.** Quando a Diantha é a **campeã**, a luta logo antes do lendário. A fala é sobre a criatura, sem dizer o nome dela ([R16](../NEXUS_REGRAS.md)).

#### Xerneas

A criatura dá vida e não sabe parar; no fragmento da Diantha ela deu vida a Kalos inteira, de uma vez, para sempre. A atriz que queria ficar como estava ganhou exatamente isso, e descobriu que o que ela amava no teatro era a cortina descer. Ela guarda a porta de quem pode dar a ela um final — e não pede.

**Antes da luta**

> Beyond that door is the loveliest thing I have ever seen.
>
> It gives life. It sleeps as a tree for a thousand years, then wakes and gives it all away.
>
> In my world, it never went back to sleep. Nothing faded. Nothing ended.
>
> I was so beautiful. For so long. Let me show you.

**Derrota**

> …Ah. So there is an ending after all. How lovely.

**Depois da luta**

> Do you know what nobody tells you about forever?
>
> The flowers never fall. The curtain never comes down. The applause never, ever stops.
>
> After a hundred years, you'd give anything for one quiet, empty theater.
>
> Go and meet it. It's radiant. Just… don't ask it for anything.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Diantha_ChampionIntro:
	.string "Beyond that door is the loveliest\n"
	.string "thing I have ever seen.\p"
	.string "It gives life. It sleeps as a tree for a\n"
	.string "thousand years, then wakes and gives\l"
	.string "it all away.\p"
	.string "In my world, it never went back to\n"
	.string "sleep. Nothing faded. Nothing ended.\p"
	.string "I was so beautiful. For so long. Let me\n"
	.string "show you.$"

Nexus_Text_Diantha_ChampionDefeat:
	.string "…Ah. So there is an ending after all.\n"
	.string "How lovely.$"

Nexus_Text_Diantha_ChampionAfter:
	.string "{SPEAKER NAME_DIANTHA}Do you know what nobody tells you\n"
	.string "about forever?\p"
	.string "The flowers never fall. The curtain\n"
	.string "never comes down. The applause never,\l"
	.string "ever stops.\p"
	.string "After a hundred years, you'd give\n"
	.string "anything for one quiet, empty theater.\p"
	.string "Go and meet it. It's radiant. Just…\n"
	.string "don't ask it for anything.$"
```

</details>

Falante novo: `SP_NAME_DIANTHA` (ainda não existe em `include/constants/speaker_names.h`).

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

**Variação 2** — o homem muito alto que esperou 3.000 anos (o AZ, nunca nomeado; fio "Kalos").

**Antes da luta**

> A very tall man came to my dressing room once. He carried a flower that never closed.
>
> He said he had waited three thousand years. He said it the way you'd say “three days.”
>
> He looked at me as if he knew exactly where I was headed. Let's see where you're headed!

**Derrota**

> Oh, well played. He would have liked you.

**Depois da luta**

> I asked him how he could bear it. All that time.
>
> He said, “I don't. I only keep walking.”
>
> What's waiting for you gives that kind of time away as if it were nothing.
>
> Take only a little. A lifetime is plenty, darling.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Diantha_ChampionIntro2:
	.string "A very tall man came to my dressing\n"
	.string "room once. He carried a flower that\l"
	.string "never closed.\p"
	.string "He said he had waited three thousand\n"
	.string "years. He said it the way you'd say\l"
	.string "“three days.”\p"
	.string "He looked at me as if he knew exactly\n"
	.string "where I was headed. Let's see where\l"
	.string "you're headed!$"

Nexus_Text_Diantha_ChampionDefeat2:
	.string "Oh, well played. He would have liked you.$"

Nexus_Text_Diantha_ChampionAfter2:
	.string "{SPEAKER NAME_DIANTHA}I asked him how he could bear it. All\n"
	.string "that time.\p"
	.string "He said, “I don't. I only keep walking.”\p"
	.string "What's waiting for you gives that kind\n"
	.string "of time away as if it were nothing.\p"
	.string "Take only a little. A lifetime is plenty,\n"
	.string "darling.$"
```

</details>

**Variação 3** — humor: o primeiro fio de cabelo branco em décadas.

**Antes da luta**

> Would you believe I found a grey hair this morning? Here! In this very place!
>
> I nearly wept for joy. It's my first in… oh, far too long.
>
> What lives behind that door would be so disappointed in me. Let's battle!

**Derrota**

> Marvelous. I'm sure you've given me another grey hair. Thank you!

**Depois da luta**

> Where I come from, it grew over everything. Its branches shone in every color.
>
> Nobody wilted, nobody aged, and nobody ever had to say goodbye.
>
> It meant it kindly. Life always does.
>
> When you bring its little piece home, let it grow old with you. That's the real gift.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Diantha_ChampionIntro3:
	.string "Would you believe I found a grey hair\n"
	.string "this morning? Here! In this very place!\p"
	.string "I nearly wept for joy. It's my first in…\n"
	.string "oh, far too long.\p"
	.string "What lives behind that door would be so\n"
	.string "disappointed in me. Let's battle!$"

Nexus_Text_Diantha_ChampionDefeat3:
	.string "Marvelous. I'm sure you've given me\n"
	.string "another grey hair. Thank you!$"

Nexus_Text_Diantha_ChampionAfter3:
	.string "{SPEAKER NAME_DIANTHA}Where I come from, it grew over\n"
	.string "everything. Its branches shone in\l"
	.string "every color.\p"
	.string "Nobody wilted, nobody aged, and nobody\n"
	.string "ever had to say goodbye.\p"
	.string "It meant it kindly. Life always does.\p"
	.string "When you bring its little piece home,\n"
	.string "let it grow old with you. That's the\l"
	.string "real gift.$"
```

</details>
