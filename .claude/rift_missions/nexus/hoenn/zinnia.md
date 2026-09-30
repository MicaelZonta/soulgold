# Zinnia

**Região da ficha:** Hoenn

Aparece no checklist como:

- **Zinnia** (Hoenn · Outros notáveis) — Lorekeeper do povo Draconid que conduz os eventos do Delta Episode.

**Pronto para o Nexus:** ❌ não — o overworld próprio entrou no código em 30/09/2026 (`OBJ_EVENT_GFX_ZINNIA`), mas falta a front pic (obrigatória).

**Arte disponível:** ✅ overworld e front pic em `.filetransfer/.trainers/Zinnia/` (o overworld já registrado; a front pic, não).

## Checklist

- [x] Sprite de overworld *(obrigatório)* — `OBJ_EVENT_GFX_ZINNIA`, 30/09/2026
- [ ] Battle sprite / front pic *(obrigatório)* — arte disponível, falta registrar
- [ ] Field mugshot (retrato na caixa de diálogo)
- [ ] Time para as Rift Missions definido — 📝 proposta abaixo (30/09/2026), fora do código
- [ ] Associado a um lendário — 📝 proposta: Rayquaza (cedido pelo Lance)
- [ ] Diálogo genérico escrito — 📝 proposta abaixo, 3 variações
- [ ] Diálogo associado ao lendário escrito — 📝 proposta abaixo, 3 variações

## Referências no repositório

### Sprite de overworld

| Constante | Arquivo |
|---|---|
| `OBJ_EVENT_GFX_ZINNIA` | `graphics/object_events/pics/people/special/zinnia.png` (16x32, 12 quadros, `sAnimTable_StandardAsym`; paleta própria `OBJ_EVENT_PAL_TAG_ZINNIA`) — registrado em 30/09/2026 |

Fonte da arte em `.filetransfer/.trainers/Zinnia/`:

| Arquivo | O que é |
|---|---|
| `Sprite - Aveontrainer.png` | overworld, autor **Aveontrainer** (origem do `zinnia.png` acima) |
| `Sprite - comparacao no jogo.png` | comparação do overworld no jogo |
| `Trainer - Gnomowladny.png` | front pic, autor **Gnomowladny** — **ainda não registrada** |
| `Trainer - comparacao no jogo.png` | comparação da front pic no jogo |

### Battle sprite (front pic)

Não existe no código. A arte está em `.filetransfer/.trainers/Zinnia/Trainer - Gnomowladny.png`; falta converter e registrar (skills `converter-sprite` e `adicionar-grafico-trainer`).

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`). A pasta da arte não traz mugshot.

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

Nenhuma. Ao criar, seguir a skill `adicionar-batalha-npc` (e `alocar-flag` se precisar de flag nova).

### Time das Rift Missions

📝 **Proposta de 30/09/2026, aguardando o autor.** `TRAINER_NEXUS_ZINNIA`, ID **a alocar** (IDs livres abaixo de 1056; não usar 1056–1163), campeã do **Rayquaza**. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega; 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler).

Pic `Hex Maniac` — **pic provisória até registrar a arte** (capa escura, a mais perto do capuz da Zinnia entre as que já existem). Classe `Dragon Tamer`, música `Hg Champion`.

Lendário **Rayquaza**, com **Dragon Ascent**: é a Mega Rayquaza, lendário **e** Mega na mesma peça (R10; o validador conta Dragon Ascent como Mega). O Delta Episode inteiro é a Zinnia tentando fazer o dragão do céu aprender esse golpe; aqui ele aprendeu. Semi-lendário **Jirachi**, a estrela dos desejos que acorda com o cometa: para a guardiã de um povo que lê o céu, e com Doom Desire, a estrela que cai depois. É também o Aço que segura Fada e Gelo pelos dragões. Mais **Salamence** (a Mega dela em ORAS; aqui sem pedra, porque a vaga é do Rayquaza), **Goodra** e **Noivern**, do time dela em ORAS, e **Exploud**: a Aster, a Whismur que ela carrega em ORAS, crescida neste fragmento.

*Plano (Singles):* a Mega Rayquaza põe Delta Stream (tira as fraquezas de Voador) e arma Dragon Dance, depois limpa com Dragon Ascent e Extreme Speed; o Jirachi dá Wish e planta Doom Desire para o turno seguinte; o Salamence entra de Intimidate; o Goodra de Assault Vest segura os especiais; o Noivern tira metade de qualquer tanque com Super Fang; o Exploud de Choice Specs bate Hyper Voice em Fantasma graças ao Scrappy.

*Plano (Doubles):* o Noivern põe Tailwind enquanto o Jirachi dá Helping Hand no Exploud, e o Hyper Voice pega os dois oponentes; o Salamence abre de Intimidate; a Mega Rayquaza entra com o vento já soprando. Nenhum golpe do time acerta o parceiro.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Rayquaza | Life Orb | Air Lock | Naive | Dragon Ascent, Extreme Speed, Draco Meteor, Dragon Dance |
| Jirachi | Leftovers | Serene Grace | Careful | Iron Head, Doom Desire, Wish, Helping Hand |
| Salamence | Sitrus Berry | Intimidate | Timid | Draco Meteor, Hurricane, Fire Blast, Protect |
| Goodra | Assault Vest | Sap Sipper | Modest | Draco Meteor, Fire Blast, Sludge Bomb, Thunderbolt |
| Noivern | Sitrus Berry | Infiltrator | Timid | Hurricane, Super Fang, Tailwind, Roost |
| Exploud | Choice Specs | Scrappy | Modest | Hyper Voice, Fire Blast, Focus Blast, Ice Beam |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>dev_scripts/nexus_validar_time.py</code>: trainerproc, constantes, learnsets e categorias)</summary>

```
=== TRAINER_NEXUS_ZINNIA ===
Name: Zinnia
Class: Dragon Tamer
Pic: Hex Maniac
Gender: Female
Music: Hg Champion
Double Battle: No
AI: Smart Trainer

Rayquaza @ Life Orb
Naive Nature
Level: 100
Ability: Air Lock
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Dragon Ascent
- Extreme Speed
- Draco Meteor
- Dragon Dance

Jirachi @ Leftovers
Careful Nature
Level: 100
Ability: Serene Grace
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Iron Head
- Doom Desire
- Wish
- Helping Hand

Salamence @ Sitrus Berry
Timid Nature
Level: 100
Ability: Intimidate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Draco Meteor
- Hurricane
- Fire Blast
- Protect

Goodra @ Assault Vest
Modest Nature
Level: 100
Ability: Sap Sipper
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Draco Meteor
- Fire Blast
- Sludge Bomb
- Thunderbolt

Noivern @ Sitrus Berry
Timid Nature
Level: 100
Ability: Infiltrator
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Hurricane
- Super Fang
- Tailwind
- Roost

Exploud @ Choice Specs
Modest Nature
Level: 100
Ability: Scrappy
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Hyper Voice
- Fire Blast
- Focus Blast
- Ice Beam

```

</details>

### Lendário associado

#### Rayquaza

📝 **Proposta de 30/09/2026, aguardando o autor.** **Rayquaza**, cedido pelo **Lance** (que fica com o Gouging Fire), pela tabela "Campeões novos" de [`DIARIO_LOOKER.md`](../DIARIO_LOOKER.md). Enquanto o autor não aprova, o código e a ficha do Lance continuam como estão. Zinnia seria a campeã dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Zinnia, a Lorekeeper dos Draconid, o povo de Meteor Falls que guarda, palavra por palavra, a lenda do dragão do céu. No Delta Episode de ORAS ela quer que alguém chame o dragão para engolir a rocha gigante que vai cair em Hoenn; no fim, fala de outros mundos, um em que a Mega Evolução nem existe. É a personagem dos jogos que mais perto chega de saber que o Nexus existe.

**A criatura.** Rayquaza, o Pokémon do Céu Alto: vive na camada de ozônio, acima do clima, e desce para acalmar Kyogre e Groudon. Come meteoros; foi assim, comendo um, que aprendeu o Dragon Ascent e passou a megaevoluir sem pedra.

**O fragmento.** Já existe no jogo e **não é reescrito**: a torre sem chão nem topo, o céu escuro ao meio-dia, a poeira de ferro caindo como neve — "alguma coisa aqui em cima andou comendo estrelas cadentes". É exatamente o fim do fragmento da Zinnia: ninguém veio montar o dragão, ela subiu sozinha, e a poeira da rocha engolida ainda cai.

- Chegada: `Nexus_Text_Rayquaza_Arrival` (`data/scripts/nexus.inc`)
- Boss: `Nexus_Text_Rayquaza_Boss`
- Ficha do Looker: `Nexus_EventScript_Rayquaza_LookerFile` → `Nexus_Text_Rayquaza_LookerFile` (**File L-384. Sky High.**), ver a ficha do [Lance](../kanto/lance.md#rayquaza).

> ⚠️ O Looker File de hoje fala do campeão atual ("a Champion who flew up on his own dragon to meet it"). Se a troca for aprovada, essa frase precisa de ajuste para a Zinnia (que subiu no próprio lendário, e não num dragão dela).

O caderno da Zinnia (três páginas) está em [`diario_looker/zinnia/`](diario_looker/zinnia/1_comeco.md) e cita o `File L-384` como "see also".

### Diálogo genérico

📝 **Proposta de 30/09/2026, aguardando o autor.** Quando a Zinnia cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala de si, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

A Zinnia dos jogos é leve, provocadora e some quando quer; de repente fica séria e fala de coisas grandes demais. Esta chega sempre por último (fio "Hoenn" do diário) e acha graça nisso.

**Antes da luta**

> Hey! You made it. Everybody makes it here eventually.
>
> Me? I'm always last. Last one to the party, last one out the door.
>
> Doesn't mean I lose, though. C'mon, let's see if you can keep up!

**Derrota**

> Ahaha! Wow. Okay, you're good.
>
> Guess I'm last again. I'm used to it.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Zinnia_Intro:
	.string "Hey! You made it. Everybody makes it\n"
	.string "here eventually.\p"
	.string "Me? I'm always last. Last one to the\n"
	.string "party, last one out the door.\p"
	.string "Doesn't mean I lose, though. C'mon,\n"
	.string "let's see if you can keep up!$"

Nexus_Text_Zinnia_Defeat:
	.string "Ahaha! Wow. Okay, you're good.\p"
	.string "Guess I'm last again. I'm used to it.$"
```

</details>

#### Variações 2 e 3 (📝 proposta de 30/09/2026)

**Variação 2** — a Lorekeeper: a história na cabeça dela não bate mais com a de fora.

**Antes da luta**

> My people have one job. We remember the story, word for word, so nobody else has to.
>
> Thing is, the story in my head doesn't match the one out there anymore.
>
> Maybe I got a line wrong. Or maybe the world did. Let's battle and find out!

**Derrota**

> Huh. That's not how the story goes.
>
> …Or maybe it is, now. Guess I'll have to learn it again.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Zinnia_Intro2:
	.string "My people have one job. We remember\n"
	.string "the story, word for word, so nobody\l"
	.string "else has to.\p"
	.string "Thing is, the story in my head doesn't\n"
	.string "match the one out there anymore.\p"
	.string "Maybe I got a line wrong. Or maybe the\n"
	.string "world did. Let's battle and find out!$"

Nexus_Text_Zinnia_Defeat2:
	.string "Huh. That's not how the story goes.\p"
	.string "…Or maybe it is, now. Guess I'll have to\n"
	.string "learn it again.$"
```

</details>

**Variação 3** — a Aster, que gritava pequena e grita grande.

**Antes da luta**

> See this one? When we met, it was tiny and it wouldn't stop shouting.
>
> Now it's huge and it still won't stop shouting. Some things never change.
>
> Her name's Aster. After a flower. After somebody. Don't ask! Let's go!

**Derrota**

> Aster's gonna sulk all day. Thanks a lot!
>
> …Nah, she'll be fine. We lose, we shout, we get back up.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Zinnia_Intro3:
	.string "See this one? When we met, it was tiny\n"
	.string "and it wouldn't stop shouting.\p"
	.string "Now it's huge and it still won't stop\n"
	.string "shouting. Some things never change.\p"
	.string "Her name's Aster. After a flower. After\n"
	.string "somebody. Don't ask! Let's go!$"

Nexus_Text_Zinnia_Defeat3:
	.string "Aster's gonna sulk all day. Thanks a\n"
	.string "lot!\p"
	.string "…Nah, she'll be fine. We lose, we shout,\n"
	.string "we get back up.$"
```

</details>

### Diálogo associado ao lendário

📝 **Proposta de 30/09/2026, aguardando o autor.** Quando a Zinnia é a **campeã**, a luta logo antes do lendário. A fala é sobre a criatura, sem dizer o nome dela ([R16](../NEXUS_REGRAS.md)).

#### Rayquaza

A Lorekeeper passou a vida recitando a lenda de quem come estrelas. No fragmento dela, a lenda se cumpriu pela metade: o dragão subiu e engoliu a rocha, mas ninguém tinha dito o que acontece com a poeira. Ela guarda a porta porque foi ela quem chamou — e quem chama responde pelo que chamou.

**Antes da luta**

> Look up. Farther. Past the clouds, past the blue.
>
> There's something up there that eats falling stars. My people have sung about it for a thousand years.
>
> I'm the one who called it down. So I'm the one who answers for it. Ready?

**Derrota**

> Ahaha… Even the sky loses sometimes. Don't tell it I said that.

**Depois da luta**

> Where I come from, a rock the size of a mountain was falling on us.
>
> I called it, it rose, it swallowed the rock. Just like the story.
>
> But the story never said what happens to the dust. It's still falling. Years later.
>
> Go on up. And if it looks at you, look back. It hates being the only one who looks.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Zinnia_ChampionIntro:
	.string "Look up. Farther. Past the clouds, past\n"
	.string "the blue.\p"
	.string "There's something up there that eats\n"
	.string "falling stars. My people have sung\l"
	.string "about it for a thousand years.\p"
	.string "I'm the one who called it down. So I'm\n"
	.string "the one who answers for it. Ready?$"

Nexus_Text_Zinnia_ChampionDefeat:
	.string "Ahaha… Even the sky loses sometimes.\n"
	.string "Don't tell it I said that.$"

Nexus_Text_Zinnia_ChampionAfter:
	.string "{SPEAKER NAME_ZINNIA}Where I come from, a rock the size of a\n"
	.string "mountain was falling on us.\p"
	.string "I called it, it rose, it swallowed the\n"
	.string "rock. Just like the story.\p"
	.string "But the story never said what happens\n"
	.string "to the dust. It's still falling. Years\l"
	.string "later.\p"
	.string "Go on up. And if it looks at you, look\n"
	.string "back. It hates being the only one who\l"
	.string "looks.$"
```

</details>

Falante novo: `SP_NAME_ZINNIA` (ainda não existe em `include/constants/speaker_names.h`).

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

**Variação 2** — o outro mundo em que uma criança montou nele (R21, sem depender do jogador).

**Antes da luta**

> In the lore there's always a kid. Some kid from nowhere who climbs onto its back.
>
> In my world, the kid never showed up. So I climbed on myself.
>
> Turns out it doesn't like passengers much. Let's see if it likes you!

**Derrota**

> Wow… Maybe you're the kid from the lore after all. Took you long enough!

**Depois da luta**

> I think there are lots of worlds. One where a kid rode it. One where nobody did.
>
> One where the sky stayed blue. One where it came down in pieces.
>
> I got the pieces. That's okay. Somebody has to.
>
> You go meet it. Tell it the Lorekeeper sends her regards.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Zinnia_ChampionIntro2:
	.string "In the lore there's always a kid. Some\n"
	.string "kid from nowhere who climbs onto its\l"
	.string "back.\p"
	.string "In my world, the kid never showed up. So\n"
	.string "I climbed on myself.\p"
	.string "Turns out it doesn't like passengers\n"
	.string "much. Let's see if it likes you!$"

Nexus_Text_Zinnia_ChampionDefeat2:
	.string "Wow… Maybe you're the kid from the\n"
	.string "lore after all. Took you long enough!$"

Nexus_Text_Zinnia_ChampionAfter2:
	.string "{SPEAKER NAME_ZINNIA}I think there are lots of worlds. One\n"
	.string "where a kid rode it. One where nobody\l"
	.string "did.\p"
	.string "One where the sky stayed blue. One\n"
	.string "where it came down in pieces.\p"
	.string "I got the pieces. That's okay.\n"
	.string "Somebody has to.\p"
	.string "You go meet it. Tell it the Lorekeeper\n"
	.string "sends her regards.$"
```

</details>

**Variação 3** — a fome dele, com humor, e a solidão por baixo.

**Antes da luta**

> Fun fact! It doesn't eat. Not food, anyway. It eats whatever falls from the sky.
>
> Rocks. Stars. Once, almost, me.
>
> I'm not bitter! Just… careful. Let's battle!

**Derrota**

> Ahahaha! Okay, okay. You earned the view.

**Depois da luta**

> Up there, it's so high the air runs out. It doesn't care.
>
> It's never landed. Not once, in the whole story. It just goes up and up.
>
> Sometimes I think it's not hungry at all. It's lonely, and falling stars are the only things that visit.
>
> So be a visitor. Just… don't fall.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Zinnia_ChampionIntro3:
	.string "Fun fact! It doesn't eat. Not food,\n"
	.string "anyway. It eats whatever falls from\l"
	.string "the sky.\p"
	.string "Rocks. Stars. Once, almost, me.\p"
	.string "I'm not bitter! Just… careful. Let's\n"
	.string "battle!$"

Nexus_Text_Zinnia_ChampionDefeat3:
	.string "Ahahaha! Okay, okay. You earned the\n"
	.string "view.$"

Nexus_Text_Zinnia_ChampionAfter3:
	.string "{SPEAKER NAME_ZINNIA}Up there, it's so high the air runs out.\n"
	.string "It doesn't care.\p"
	.string "It's never landed. Not once, in the\n"
	.string "whole story. It just goes up and up.\p"
	.string "Sometimes I think it's not hungry at\n"
	.string "all. It's lonely, and falling stars are\l"
	.string "the only things that visit.\p"
	.string "So be a visitor. Just… don't fall.$"
```

</details>
