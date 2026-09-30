# Agatha

**Região da ficha:** Kanto

Aparece no checklist como:

- **Agatha — Fantasma** (Kanto · Elite Four e Campeões) — veterana ligada ao passado do Professor Oak, famosa por seu Gengar.

**Pronto para o Nexus:** ❌ não — tem sprite de overworld, falta o battle sprite (front pic) registrado no código.

**Arte disponível:** ✅ overworld e front pic em `.filetransfer/.trainers/Agatha/` (o overworld já está registrado; a front pic ainda não).

## Checklist

- [x] Sprite de overworld *(obrigatório)*
- [ ] Battle sprite / front pic *(obrigatório)* — arte em `.filetransfer/.trainers/Agatha/`, falta registrar
- [ ] Field mugshot (retrato na caixa de diálogo)
- [ ] Time para as Rift Missions definido — 📝 proposta de 30/09/2026 abaixo (validada), fora do código
- [ ] Associado a um lendário — 📝 proposta de 30/09/2026: Spectrier (cedido pelo Morty)
- [ ] Diálogo genérico escrito — 📝 proposta de 30/09/2026 (3 variações)
- [ ] Diálogo associado ao lendário escrito — 📝 proposta de 30/09/2026 (3 variações)

## Referências no repositório

### Sprite de overworld

| Constante | Arquivo |
|---|---|
| `OBJ_EVENT_GFX_AGATHA` (350; paleta `OBJ_EVENT_PAL_TAG_AGATHA` = `0x117F`) | `graphics/object_events/pics/people/special/agatha.png` (32x32, doze quadros, `sAnimTable_StandardAsym`; `gObjectEventGraphicsInfo_Agatha` em `src/data/object_events/object_event_graphics_info.h`) |

Nenhum mapa usa ainda. Folha de origem em `.filetransfer/.trainers/Agatha/`: `Sprite - desconhecido.png` (autor **desconhecido**), comparação no jogo em `Sprite - comparacao no jogo.png`, e uma alternativa em `outras/Sprite - RegentOfRaios.jpg` (autor **RegentOfRaios**).

### Battle sprite (front pic)

Não existe no código (`TRAINER_PIC_FRONT_AGATHA` não existe). A arte chegou:

| Arquivo | O que é |
|---|---|
| `.filetransfer/.trainers/Agatha/Trainer - Brumirage.png` | front pic, 80x80, autor **Brumirage** |
| `.filetransfer/.trainers/Agatha/Trainer - comparacao no jogo.png` | comparação no jogo |

Falta converter para 64x64 (skill `converter-sprite`) e registrar (skill `adicionar-grafico-trainer`). O overworld já foi feito com a skill `adicionar-npc`.

### Field mugshot

Não existe, e a pasta `.filetransfer/.trainers/Agatha/` não traz arte de mugshot. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

Nenhuma. Ao criar, seguir a skill `adicionar-batalha-npc` (e `alocar-flag` se precisar de flag nova).

### Time das Rift Missions

📝 **Proposta de 30/09/2026, aguardando o autor.** `TRAINER_NEXUS_AGATHA`, ID **a alocar** (IDs livres abaixo de 1056; não usar 1056–1163), campeã do Spectrier. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega; 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler). **Pic provisória** (`Hex Maniac`) até registrar a arte.

⚠️ **O Spectrier é semi-lendário neste engine** (`isSubLegendary`, igual no time do Morty, que leva o Ho-Oh como lendário). Por isso ele ocupa a vaga de **semi-lendário**, e a vaga de lendário vai para outro: **Marshadow** (mítico que o R10 conta como lendário). O validador confirma: `L=MARSHADOW S=SPECTRIER`.

Lendário **Marshadow**, o Pokémon que vive escondido na sombra dos outros: para a Agatha, uma sombra que anda atrás dela desde menina e que ela nunca tentou mandar embora. Semi-lendário **Spectrier**, o corcel de sombra do rei, que ela atraiu com as cenouras escuras do próprio jardim (ver "Lendário associado" e o diário). Mega **Gengar** (`Ghostite`), o Pokémon-assinatura dela desde Red/Blue ("famosa por seu Gengar"). Mais **Arbok** e **Crobat** (o Golbat de RBY, evoluído — ironia: evolui por amizade, e ela diz que Pokémon são para batalhar) e **Marowak de Alola**, Fantasma/Fogo: o eco do Marowak-mãe da Pokémon Tower de Lavender.

*Plano (Singles):* "truques de velha raposa" — status e punição. O Arbok entra com Intimidate e paralisa com Glare; a Mega Gengar prende com Shadow Tag, queima com Will-O-Wisp e bate com Hex (dobra em alvo com status); o Crobat usa Taunt contra quem quer montar e sai de U-turn; o Marshadow pune qualquer setup com Spectral Thief (rouba os boosts) e fecha com Shadow Sneak; o Spectrier, com Nasty Plot atrás de Protect, vira bola de neve com Grim Neigh; o Marowak de Alola com Thick Club quebra muralhas com Shadow Bone e Flare Blitz.

*Plano (Doubles):* o Crobat põe Tailwind no primeiro turno (Inner Focus: não recua de Fake Out); o Arbok abaixa o Ataque dos dois com Intimidate e paralisa o mais rápido com Glare; o Marowak de Alola, com Lightning Rod, puxa os golpes elétricos que iam no Crobat e no Gengar; a Mega Gengar prende os dois oponentes com Shadow Tag. Nenhum golpe do time acerta o parceiro (Bonemerang e Shadow Bone são de alvo único).

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Marshadow | Life Orb | Technician | Jolly | Spectral Thief, Close Combat, Shadow Sneak, Protect |
| Spectrier | Life Orb | Grim Neigh | Timid | Shadow Ball, Dark Pulse, Nasty Plot, Protect |
| Gengar | Ghostite | Cursed Body | Timid | Hex, Sludge Bomb, Will-O-Wisp, Protect |
| Crobat | Sitrus Berry | Inner Focus | Jolly | Brave Bird, Taunt, Tailwind, U-turn |
| Marowak-Alola | Thick Club | Lightning Rod | Adamant | Shadow Bone, Flare Blitz, Bonemerang, Protect |
| Arbok | Black Sludge | Intimidate | Adamant | Glare, Gunk Shot, Sucker Punch, Coil |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>dev_scripts/nexus_validar_time.py</code>: trainerproc, constantes, learnsets e categorias)</summary>

```
=== TRAINER_NEXUS_AGATHA ===
Name: Agatha
Class: Elite Four
Pic: Hex Maniac
Gender: Female
Music: Elite Four
Double Battle: No
AI: Smart Trainer

Spectrier @ Life Orb
Timid Nature
Level: 100
Ability: Grim Neigh
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Shadow Ball
- Dark Pulse
- Nasty Plot
- Protect

Marshadow @ Life Orb
Jolly Nature
Level: 100
Ability: Technician
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Spectral Thief
- Close Combat
- Shadow Sneak
- Protect

Gengar @ Ghostite
Timid Nature
Level: 100
Ability: Cursed Body
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Hex
- Sludge Bomb
- Will-O-Wisp
- Protect

Crobat @ Sitrus Berry
Jolly Nature
Level: 100
Ability: Inner Focus
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Brave Bird
- Taunt
- Tailwind
- U-turn

Marowak-Alola @ Thick Club
Adamant Nature
Level: 100
Ability: Lightning Rod
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Shadow Bone
- Flare Blitz
- Bonemerang
- Protect

Arbok @ Black Sludge
Adamant Nature
Level: 100
Ability: Intimidate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Glare
- Gunk Shot
- Sucker Punch
- Coil
```

</details>

### Lendário associado

#### Spectrier

📝 **Proposta de 30/09/2026, aguardando o autor.** **Spectrier**. Agatha é a campeã dele: a quinta luta do Daily, logo antes da boss battle. Vem da tabela "Campeões novos" de [`DIARIO_LOOKER.md`](../DIARIO_LOOKER.md): quem cede é o **Morty** (`johto/morty.md`), que fica com o **Ho-Oh**. Enquanto o autor não aprova, a ficha do Morty e o código continuam como estão (`Nexus_EventScript_Morty_Spectrier_ChampionFight`).

**Quem é.** Agatha, a Fantasma da Elite Four de Kanto em Red/Blue/Yellow e FireRed/LeafGreen: a mais velha da Liga, bengala na mão, Gengar como estrela. Foi rival do Professor Oak na juventude ("aquele velho já foi forte e bonito, décadas atrás") e desdenha da Pokédex: para ela, Pokémon são para batalhar. Em Gold/Silver ela já saiu da Liga e a Karen está no lugar. No fio **Liga de Kanto** do diário, ela e a Lorelei guardam os corcéis do rei e procuram o **Will**, que tem o rei (Calyrex).

**A criatura.** Spectrier, o corcel de sombra da Crown Tundra, montaria do Calyrex. Não usa a visão: sonda tudo com os outros sentidos. Fugiu quando o povo esqueceu o rei, e só volta a se aproximar atraído pela Shaderoot Carrot, a cenoura escura que o Calyrex planta. Grim Neigh: fica mais forte a cada adversário que derruba.

**O fragmento.** O campo de neve escura à meia-noite, com neblina e cascos circulando, que o jogo já usa. No fragmento da Agatha (diário), é uma Kanto em que **nenhuma criança ganhou uma Pokédex**: a Agatha venceu a última batalha contra o Oak, ele nunca escreveu o livro, e a Elite Four nunca foi derrotada. Nevou preto sobre a Pokémon Tower de Lavender na noite em que o cavalo chegou procurando o rei; a Agatha o atraiu com as cenouras escuras do jardim dela, montou nele e saiu da cadeira da Liga para procurar o rapaz de máscara.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário) — **já estão no jogo**, com o Morty como campeão: `Nexus_Text_Spectrier_Arrival`, `Nexus_Text_Spectrier_Boss` e o Looker File `Nexus_Text_Spectrier_LookerFile` (**File L-897. Shadow Steed.**) em `data/scripts/nexus.inc`. Não se repete nada aqui.

**Chegada** (existente)

> A field of dark snow at midnight, and a fog so thick you could not see your own hands.
>
> You could hear hooves, though. Circling. Closer. Then farther. Then closer.

**Boss** (existente)

> The hooves stopped right in front of you.
>
> You still could not see it. It did not need to see you either.

**Ficha do Looker** (existente, File L-897)

> File L-897. Shadow Steed.
>
> A field where eyes are useless, and a man who has trained all his life to see what isn't there.
>
> What came back with you makes no sound at all. I checked twice.
>
> He found it before I did. He found it with his eyes closed.

⚠️ O File L-897 fala de **um homem** ("a man who has trained all his life to see", "He found it"): é o Morty. Se a troca for aprovada, **só a segunda e a quarta caixas** precisam de outra pessoa (a primeira e a terceira servem para qualquer campeão). Fica para o autor decidir; esta ficha não reescreve o File. O `.inc` é o de `nexus.inc` (e o da ficha do Morty).

### Diálogo genérico

📝 **Proposta de 30/09/2026, aguardando o autor.** Quando a Agatha cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala de si, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)). Três ângulos: apresentação e a velha briga: Pokémon são para batalhar (1); o rival de juventude (Oak, nunca nomeado) — cinquenta anos de discussão (2); R21: no fragmento dela a Elite Four nunca perdeu, e a sala do Campeão junta poeira (3).

#### Variação 1

**Antes da luta**

> Hah! Another youngster. I'm Agatha. I was battling with ghosts before your grandparents learned to walk.
>
> People call me scary. Nonsense! I'm only honest. Pokémon are for battling, child, and I'll prove it.

**Derrota**

> Oh ho! You're something special, child!

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Agatha_Intro:
	.string "Hah! Another youngster. I'm Agatha. I\n"
	.string "was battling with ghosts before your\l"
	.string "grandparents learned to walk.\p"
	.string "People call me scary. Nonsense! I'm\n"
	.string "only honest. Pokémon are for battling,\l"
	.string "child, and I'll prove it.$"

Nexus_Text_Agatha_Defeat:
	.string "Oh ho! You're something special, child!$"
```

</details>

#### Variação 2

**Antes da luta**

> There was a boy in my town who wanted to study Pokémon instead of battling them. We argued about it for fifty years.
>
> He'd say, 'Look how they live!' I'd say, 'Look how they fight!' We were both right. Neither of us ever said so.
>
> Well? Which kind are you? Show me!

**Derrota**

> Hmph. You battle the way he did. Kindly. …It still works. How annoying.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Agatha_Intro2:
	.string "There was a boy in my town who wanted\n"
	.string "to study Pokémon instead of battling\l"
	.string "them. We argued about it for fifty\l"
	.string "years.\p"
	.string "He'd say, 'Look how they live!' I'd\n"
	.string "say, 'Look how they fight!' We were\l"
	.string "both right. Neither of us ever said so.\p"
	.string "Well? Which kind are you? Show me!$"

Nexus_Text_Agatha_Defeat2:
	.string "Hmph. You battle the way he did. Kindly.\n"
	.string "…It still works. How annoying.$"
```

</details>

#### Variação 3

**Antes da luta**

> Forty years in the League, and not one Trainer ever got past my room. Not one!
>
> The room after mine is full of dust. Sometimes I open the door just to let it breathe.
>
> Well? Are you going to be the first? Hah! Let's find out!

**Derrota**

> Oh ho! So that's what the next door looks like from this side. …Dusty.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Agatha_Intro3:
	.string "Forty years in the League, and not one\n"
	.string "Trainer ever got past my room. Not one!\p"
	.string "The room after mine is full of dust.\n"
	.string "Sometimes I open the door just to let\l"
	.string "it breathe.\p"
	.string "Well? Are you going to be the first?\n"
	.string "Hah! Let's find out!$"

Nexus_Text_Agatha_Defeat3:
	.string "Oh ho! So that's what the next door\n"
	.string "looks like from this side. …Dusty.$"
```

</details>

### Diálogo associado ao lendário

📝 **Proposta de 30/09/2026, aguardando o autor.** Quando a Agatha é a **campeã**, a luta logo antes do Spectrier. A fala é sobre a criatura, pelo olhar dela, sem dizer o nome da espécie ([R16](../NEXUS_REGRAS.md)).

#### Spectrier

##### Variação 1

*Ângulo:* o fantasma de uma promessa: o cavalo espera um cavaleiro que ainda não voltou; o Gengar de cinquenta anos.

**Antes da luta**

> Hear that? Hooves. Round and round, all night, and it never once looks where it's going.
>
> Most ghosts are sad about something that ended. This one is waiting for something that hasn't come back yet.
>
> Hah! I know that feeling. Come on, child. Show me some spirit!

**Derrota**

> Oh ho! Even the hooves stopped to watch that one.

**Depois da luta**

> It had a rider once. Someone small, with a crown. It carried him everywhere.
>
> Then they quarreled, the way old friends do, and neither one went after the other.
>
> My Gengar has stayed by me my whole life. That's the scary thing about ghosts, child. They don't leave.
>
> Be kind to it in there. It's only waiting.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Agatha_ChampionIntro:
	.string "Hear that? Hooves. Round and round, all\n"
	.string "night, and it never once looks where\l"
	.string "it's going.\p"
	.string "Most ghosts are sad about something\n"
	.string "that ended. This one is waiting for\l"
	.string "something that hasn't come back yet.\p"
	.string "Hah! I know that feeling. Come on,\n"
	.string "child. Show me some spirit!$"

Nexus_Text_Agatha_ChampionDefeat:
	.string "Oh ho! Even the hooves stopped to\n"
	.string "watch that one.$"

Nexus_Text_Agatha_ChampionAfter:
	.string "{SPEAKER NAME_AGATHA}It had a rider once. Someone small, with\n"
	.string "a crown. It carried him everywhere.\p"
	.string "Then they quarreled, the way old\n"
	.string "friends do, and neither one went after\l"
	.string "the other.\p"
	.string "My Gengar has stayed by me my whole\n"
	.string "life. That's the scary thing about\l"
	.string "ghosts, child. They don't leave.\p"
	.string "Be kind to it in there. It's only\n"
	.string "waiting.$"
```

</details>

##### Variação 2

*Ângulo:* fio Liga de Kanto: ela e o cavalo procuram a mesma pessoa, o rapaz de máscara que leva o rei (Will, nunca nomeado); R21 brinca com a aposentadoria dela.

**Antes da luta**

> That horse and I are after the same person. A young man in a mask, who does magic tricks.
>
> He has its king with him, somewhere. And I hear that in some other world, I retired and let him have the League!
>
> Retired! Me! Hah! You first, then. I'll deal with him later!

**Derrota**

> Hmph! Fine, fine. Go on ahead of me, then.

**Depois da luta**

> The horse is fast. I'm not. But I'm stubborn, and stubborn gets there too, eventually.
>
> When you find the boy in the mask, tell him the horse is still looking. It hasn't given up.
>
> And tell him Agatha says hello. He'll know who I am. Everyone does.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Agatha_ChampionIntro2:
	.string "That horse and I are after the same\n"
	.string "person. A young man in a mask, who does\l"
	.string "magic tricks.\p"
	.string "He has its king with him, somewhere. And\n"
	.string "I hear that in some other world, I\l"
	.string "retired and let him have the League!\p"
	.string "Retired! Me! Hah! You first, then. I'll\n"
	.string "deal with him later!$"

Nexus_Text_Agatha_ChampionDefeat2:
	.string "Hmph! Fine, fine. Go on ahead of me,\n"
	.string "then.$"

Nexus_Text_Agatha_ChampionAfter2:
	.string "{SPEAKER NAME_AGATHA}The horse is fast. I'm not. But I'm\n"
	.string "stubborn, and stubborn gets there too,\l"
	.string "eventually.\p"
	.string "When you find the boy in the mask, tell\n"
	.string "him the horse is still looking. It\l"
	.string "hasn't given up.\p"
	.string "And tell him Agatha says hello. He'll\n"
	.string "know who I am. Everyone does.$"
```

</details>

##### Variação 3

*Ângulo:* humor e lore de Galar: a cenoura escura que ela planta no jardim (Shaderoot Carrot, nunca nomeada) e o cavalo mal-educado.

**Antes da luta**

> I grow a dark little carrot in my garden. Black as a shadow. Sweet as anything.
>
> I left one out last night. By morning it was gone, and there were hoofprints all around my porch.
>
> No thank you! No goodbye! Rude! I hope your manners are better, child. Let's go!

**Derrota**

> Hah! Good manners AND a good battle. Fine, fine.

**Depois da luta**

> That horse only ever trusted one hand to feed it. A small hand, under a crown.
>
> Mine isn't the right hand. It ate my carrot anyway. Hungry things aren't picky.
>
> If you have something to offer it, offer it. Nobody is too wild for a kind gesture.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Agatha_ChampionIntro3:
	.string "I grow a dark little carrot in my\n"
	.string "garden. Black as a shadow. Sweet as\l"
	.string "anything.\p"
	.string "I left one out last night. By morning it\n"
	.string "was gone, and there were hoofprints all\l"
	.string "around my porch.\p"
	.string "No thank you! No goodbye! Rude! I hope\n"
	.string "your manners are better, child. Let's\l"
	.string "go!$"

Nexus_Text_Agatha_ChampionDefeat3:
	.string "Hah! Good manners AND a good battle.\n"
	.string "Fine, fine.$"

Nexus_Text_Agatha_ChampionAfter3:
	.string "{SPEAKER NAME_AGATHA}That horse only ever trusted one hand\n"
	.string "to feed it. A small hand, under a crown.\p"
	.string "Mine isn't the right hand. It ate my\n"
	.string "carrot anyway. Hungry things aren't\l"
	.string "picky.\p"
	.string "If you have something to offer it,\n"
	.string "offer it. Nobody is too wild for a kind\l"
	.string "gesture.$"
```

</details>

Falante novo: `SP_NAME_AGATHA` (ainda não existe em `include/constants/speaker_names.h`; `{SPEAKER NAME_AGATHA}` só no `ChampionAfter`).

### Diário do Looker

📝 **Proposta de 30/09/2026, aguardando o autor.** Três páginas em [`diario_looker/agatha/`](diario_looker/agatha/) ([formato](../DIARIO_LOOKER.md)): [começo](diario_looker/agatha/1_comeco.md) (Lavender sob neve preta, a Kanto sem Pokédex e a cenoura escura estendida para o nada), [meio](diario_looker/agatha/2_meio.md) (o relógio do Oak parado às 4:12: ela venceu a última batalha, e ele nunca escreveu o livro), [fim](diario_looker/agatha/3_fim.md) (September 31st: ela sai da cadeira montada no cavalo, atrás do rapaz de máscara; o relógio fica na porta do laboratório de Pallet). See also: File L-897.
