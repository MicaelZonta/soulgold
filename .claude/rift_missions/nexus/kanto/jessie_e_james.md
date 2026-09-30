# Jessie e James

**Região da ficha:** Kanto

Aparece no checklist como:

- **Jessie e James** (Kanto · Team Rocket) — dupla recorrente do Team Rocket presente em versões especiais e nos jogos *Let's Go*.

**Pronto para o Nexus:** ❌ não — o overworld já está no código, mas falta o battle sprite (front pic), que é obrigatório.

**Arte disponível:** ✅ overworld (já registrado) e front pic em `.filetransfer/.trainers/Jessie e James/`

## Checklist

- [x] Sprite de overworld *(obrigatório)*
- [ ] Battle sprite / front pic *(obrigatório)* — arte em `.filetransfer/`, falta registrar
- [ ] Field mugshot (retrato na caixa de diálogo)
- [ ] Time para as Rift Missions definido — 📝 proposta abaixo, validada, não está no código
- [ ] Associado a um lendário — 📝 proposta abaixo (Meloetta)
- [ ] Diálogo genérico escrito — 📝 proposta abaixo
- [ ] Diálogo associado ao lendário escrito — 📝 proposta abaixo

## Referências no repositório

### Sprite de overworld

Já registrado, **um boneco para cada** (a dupla anda em dois objetos; o Meowth não tem sprite próprio). Quadro 16x32, 9 quadros (`sAnimTable_Standard`); tamanho do boneco decidido em `.filetransfer/.trainers/TAMANHOS.md` (Jessie 16x18, James 16x19, "forma pronta" de 30/09 — não regravar).

| Constante | Arquivo | Paleta |
|---|---|---|
| `OBJ_EVENT_GFX_JESSIE` (359) | `graphics/object_events/pics/people/special/jessie.png` | `OBJ_EVENT_PAL_TAG_JESSIE` (0x1188) |
| `OBJ_EVENT_GFX_JAMES` (360) | `graphics/object_events/pics/people/special/james.png` | `OBJ_EVENT_PAL_TAG_JAMES` (0x1189) |

Nenhum mapa usa esses objetos ainda.

### Battle sprite (front pic)

Não existe no código (nenhum `TRAINER_PIC_FRONT_*` de Jessie/James). A arte chegou em `.filetransfer/.trainers/Jessie e James/`, autor **FallenSoldier** (nome do arquivo):

| Arquivo | O que é |
|---|---|
| `Trainer - FallenSoldier.png` | front pic da dupla (a que falta registrar) |
| `Trainer - comparacao no jogo.png` | prévia da front pic dentro da batalha |
| `Sprite - FallenSoldier.png` | overworld (origem do que já está no jogo) |
| `Sprite - comparacao no jogo (Jessie).png`, `Sprite - comparacao no jogo (James).png` | prévias do overworld no mapa |
| `outras/Folha completa - FallenSoldier.png` | folha completa de onde saiu o overworld |

Falta registrar a front pic: skills `converter-sprite` (64x64, ≤16 cores) e `adicionar-grafico-trainer`. O overworld já passou por `converter-sprite`/`adicionar-npc`. Até lá o time usa uma pic provisória (ver abaixo).

### Field mugshot

Não existe, e a pasta da arte não traz mugshot. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

Nenhuma. (`TRAINER_JAMES` = 431 em `include/constants/opponents.h` é um Bug Catcher de Hoenn, sem relação.) Ao criar, seguir a skill `adicionar-batalha-npc`.

### Time das Rift Missions

📝 **Proposta de 30/09/2026, aguardando o autor.** `TRAINER_NEXUS_JESSIE_AND_JAMES`, ID **a alocar** (IDs aposentados abaixo de 1056; 1056–1163 não servem, [R16](../NEXUS_REGRAS.md)), campeões do Meloetta. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega; 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler). Lutam juntos, como Tate e Liza: `Double Battle: Yes`, e o time funciona em Singles.

O time é o Team Rocket do anime, com as três criaturas que eles passaram séries inteiras perseguindo "para o chefe". Lendário **Zygarde** (50%): em *XY&Z* eles caçaram o Squishy, o núcleo do Zygarde, por ordem do Giovanni; no fragmento deles não existe Giovanni, então ninguém cobrou a entrega e ele ficou. Semi-lendário **Meloetta**, de que eles são campeões — em *Best Wishes* a Operation Tempest também queria a cantora. Mega **Victreebel** (Poisontite, a Mega de *Legends Z-A*): o Victreebel do James, famoso por abocanhar a cabeça do dono. Mais os originais: **Arbok** (Jessie), **Weezing** (James) e o **Meowth**, que não fica de fora de jeito nenhum. O Wobbuffet da Jessie **não** está no time — e aparece nas falas mesmo assim, como sempre.

*Plano (Singles):* o Meowth abre com Fake Out e sai com U-turn (Eviolite segura o golpe de volta; Pay Day com Technician é chip de verdade, não só piada). O Arbok entra com Intimidate e paralisa com Glare; o Weezing queima atacante físico com Will-O-Wisp e espalha Toxic Spikes. Com o jogador lento e envenenado, o Meloetta põe para dormir com Sing ou Relic Song (Serene Grace dobra a chance de sono) e a Mega Victreebel bate misto nos dois lados (Innards Out pune quem a derruba). O Zygarde fecha: Dragon Dance e Thousand Arrows, que acerta até quem voa.

*Plano (Doubles, o formato deles):* Meowth e Arbok lideram — Fake Out + Intimidate no primeiro turno, Glare no seguinte. O Zygarde usa Thousand Arrows e Rock Slide, que acertam os dois adversários e nunca o parceiro; o Weezing de Levitate e o Meloetta ficam à vontade ao lado dele. O Meloetta bate Hyper Voice nos dois (Throat Spray sobe o Sp. Atk); a Mega Victreebel usa Protect para ler o jogador. Nenhum golpe do time acerta o parceiro.

Nome no `trainers.party`: `Jess&James` (o limite é 10 caracteres, `TRAINER_NAME_LENGTH`; "Jessie&James" tem 12). Classe `Team Rocket` (a dos grunts; o Petrel usa `RocketA`). **Pic provisória até registrar a arte:** `Rocket Grunt F` (alternativa: `Young Couple`, que já mostra uma dupla).

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Zygarde (50%) | Lum Berry | Aura Break | Adamant | Thousand Arrows, Outrage, Rock Slide, Dragon Dance |
| Meloetta | Throat Spray | Serene Grace | Timid | Relic Song, Hyper Voice, Psyshock, Sing |
| Victreebel | Poisontite | Chlorophyll (Mega: Innards Out) | Modest | Sludge Bomb, Leaf Storm, Sleep Powder, Protect |
| Arbok | Sitrus Berry | Intimidate | Jolly | Gunk Shot, Knock Off, Glare, Sucker Punch |
| Weezing | Black Sludge | Levitate | Bold | Sludge Bomb, Will-O-Wisp, Toxic Spikes, Pain Split |
| Meowth | Eviolite | Technician | Jolly | Fake Out, Pay Day, U-turn, Taunt |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>dev_scripts/nexus_validar_time.py</code> em 30/09/2026: ✓ L=ZYGARDE_50 S=MELOETTA_ARIA M=VICTREEBEL→VICTREEBEL_MEGA)</summary>

```
=== TRAINER_NEXUS_JESSIE_AND_JAMES ===
Name: Jess&James
Class: Team Rocket
Pic: Rocket Grunt F
Gender: Female
Music: Rocket
Double Battle: Yes
AI: Smart Trainer

Zygarde @ Lum Berry
Adamant Nature
Level: 100
Ability: Aura Break
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Thousand Arrows
- Outrage
- Rock Slide
- Dragon Dance

Meloetta @ Throat Spray
Timid Nature
Level: 100
Ability: Serene Grace
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Relic Song
- Hyper Voice
- Psyshock
- Sing

Victreebel @ Poisontite
Modest Nature
Level: 100
Ability: Chlorophyll
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Sludge Bomb
- Leaf Storm
- Sleep Powder
- Protect

Arbok @ Sitrus Berry
Jolly Nature
Level: 100
Ability: Intimidate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Gunk Shot
- Knock Off
- Glare
- Sucker Punch

Weezing @ Black Sludge
Bold Nature
Level: 100
Ability: Levitate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Sludge Bomb
- Will-O-Wisp
- Toxic Spikes
- Pain Split

Meowth @ Eviolite
Jolly Nature
Level: 100
Ability: Technician
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Fake Out
- Pay Day
- U-turn
- Taunt
```

</details>

### Lendário associado

#### Meloetta

📝 **Proposta de 30/09/2026, aguardando o autor.** **Meloetta**. Jessie e James são os campeões dele: a quinta luta do Daily, logo antes da boss battle. Hoje o campeão do Meloetta no código é o **Petrel**, que fica só com o Ogerpon se a troca for aprovada (tabela "Campeões novos" em [`DIARIO_LOOKER.md`](../DIARIO_LOOKER.md)). Até lá, a ficha do Petrel e o código continuam como estão.

**Quem é.** Jessie, James e o Meowth que fala: a dupla cômica do Team Rocket, mestres do disfarce, com um lema recitado a cada entrada e um plano que sempre acaba com eles voando longe. No fragmento deles, o Team Rocket tem uniforme, esconderijo e lema — mas **nunca teve chefe**: o homem que eles procuram não existiu ali (fio **Rocket** de `DIARIO_LOOKER.md`).

**A criatura.** Meloetta é o Pokémon da melodia. Ao cantar a Relic Song, troca a forma de cantora (Aria) pela de dançarina (Pirouette) e volta; as melodias dela mexem com as emoções de quem ouve. No anime, o Team Rocket a perseguiu na Operation Tempest; aqui, sem ninguém para dar a ordem, eles só sentaram para ouvir.

**O fragmento.** O mesmo que já está no jogo: um teatro com todos os assentos ocupados por figurinos, e uma canção vinda de um palco vazio. Com Jessie e James de campeões, os figurinos ganham dono — são os disfarces que eles usaram a vida inteira (enfermeira, chef, caixa de correio…), sentados esperando a próxima entrada. O "homem que tem mais rostos que qualquer um deles" do Looker File serve tanto ao Petrel quanto ao James, então **o texto existente não precisa mudar**.

**Falas do fragmento** (narração; já no jogo, `Nexus_Text_Meloetta_Arrival` e `Nexus_Text_Meloetta_Boss` em `data/scripts/nexus.inc`; tocam só nos dias deste lendário, com qualquer campeão):

**Chegada**

> A theater with every seat taken. Not by people: by costumes, sitting upright, hats on, waiting.
>
> A song was coming from the stage. There was nobody on it.

**Boss**

> The song changed key in the middle of a note.
>
> The singer on the stage was a dancer now, spinning, and it had been both all along.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md): o que volta é um pedaço dele, no nível 1)

Já existe: **File L-648**, `Nexus_EventScript_Meloetta_LookerFile` / `Nexus_Text_Meloetta_LookerFile` em `data/scripts/nexus.inc` (texto e `.inc` na ficha do [Petrel](petrel.md#meloetta)). Não duplicar.

> File L-648. Melody.
>
> A theater of empty costumes, and a man who owns more faces than any of them.
>
> What came home with you hums a tune I cannot place, very quietly. It changes every time I listen. It is still finding its own voice.

### Diálogo genérico

📝 **Proposta de 30/09/2026, aguardando o autor.** Quando Jessie e James caem numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Falam deles mesmos, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)). Como na ficha de Tate e Liza, as linhas se alternam entre os dois sem plaquinha; o Meowth entra quando quer.

**Variação 1** — o lema, reescrito (original, no ritmo do deles), com o fim ainda "em ensaio".

**Antes da luta**

> Is that a challenger we hear?  
> Why, yes! It's perfectly clear!
>
> To spread a little chaos wherever we roam!  
> To find, one day, a boss to call home!
>
> Jessie!  
> James!
>
> And Meowth's the name, and trouble's the game!
>
> …We're still polishing the ending.  
> Battle us anyway!

**Derrota**

> Looks like we're blasting off again…  
> …Huh. We didn't go anywhere. That's new.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_JessieAndJames_Intro:
	.string "Is that a challenger we hear?\n"
	.string "Why, yes! It's perfectly clear!\p"
	.string "To spread a little chaos wherever we\n"
	.string "roam!\l"
	.string "To find, one day, a boss to call home!\p"
	.string "Jessie!\n"
	.string "James!\p"
	.string "And Meowth's the name, and trouble's\n"
	.string "the game!\p"
	.string "…We're still polishing the ending.\n"
	.string "Battle us anyway!$"

Nexus_Text_JessieAndJames_Defeat:
	.string "Looks like we're blasting off again…\n"
	.string "…Huh. We didn't go anywhere. That's\l"
	.string "new.$"
```

</details>

**Variação 2** — os disfarces, e o chefe que ninguém viu (fio Rocket, R21: no fragmento deles ele nunca existiu).

**Antes da luta**

> Don't look so surprised. You didn't recognize us? It's the costumes.
>
> We've been nurses, chefs, tour guides, and one very convincing mailbox.
>
> All to find one man. Tall. Nice suit. A cat on his lap. Ring any bells?
>
> No? Nobody's ever seen him. Well, if we can't find a boss, we'll find a battle!

**Derrota**

> Lost again… and I didn't even get to change outfits!

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_JessieAndJames_Intro2:
	.string "Don't look so surprised. You didn't\n"
	.string "recognize us? It's the costumes.\p"
	.string "We've been nurses, chefs, tour guides,\n"
	.string "and one very convincing mailbox.\p"
	.string "All to find one man. Tall. Nice suit.\n"
	.string "A cat on his lap. Ring any bells?\p"
	.string "No? Nobody's ever seen him. Well, if we\n"
	.string "can't find a boss, we'll find a battle!$"

Nexus_Text_JessieAndJames_Defeat2:
	.string "Lost again… and I didn't even get to\n"
	.string "change outfits!$"
```

</details>

**Variação 3** — o plano "perfeito" em passos, e o Wobbuffet que não foi convidado.

**Antes da luta**

> Right! Today's plan is flawless. Step one: we battle. Step two: we win.
>
> Step three is Meowth's. He says it's a surprise. …He always says that.
>
> And whatever happens, nobody opens that last Poké Ball. Wobbuffet isn't even on the team today.
>
> It just keeps showing up.

**Derrota**

> Step two didn't work…  
> Wob-buffet!  
> …Who let it out?!

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_JessieAndJames_Intro3:
	.string "Right! Today's plan is flawless. Step\n"
	.string "one: we battle. Step two: we win.\p"
	.string "Step three is Meowth's. He says it's a\n"
	.string "surprise. …He always says that.\p"
	.string "And whatever happens, nobody opens\n"
	.string "that last Poké Ball. Wobbuffet isn't\l"
	.string "even on the team today.\p"
	.string "It just keeps showing up.$"

Nexus_Text_JessieAndJames_Defeat3:
	.string "Step two didn't work…\n"
	.string "Wob-buffet!\l"
	.string "…Who let it out?!$"
```

</details>

### Diálogo associado ao lendário

#### Meloetta

📝 **Proposta de 30/09/2026, aguardando o autor.** Quando Jessie e James são os **campeões**, a luta logo antes do Meloetta. A fala é sobre a criatura, sem dizer o nome dela ([R16](../NEXUS_REGRAS.md)). Três ângulos: o lema que ganhou plateia, a diva que encontrou concorrência, e o Meowth que queria vender ingresso.

Falante novo: `SP_NAME_JESSIE_AND_JAMES` (não existe ainda em `include/constants/speaker_names.h`; o `ChampionAfter` usa `{SPEAKER NAME_JESSIE_AND_JAMES}`).

**Variação 1** — sem ordem de captura, eles só sentaram para ouvir; o lema escrito para um chefe que nunca veio ganhou o primeiro bis.

**Antes da luta**

> There's a song coming from that stage. Nobody's singing it. We checked.
>
> Some other us, somewhere, would've been ordered to grab that singer. Net, cage, giant balloon. The works.
>
> Nobody ordered us. So we just sat down and listened. …For three days.
>
> Don't tell anyone. It's bad for our reputation. Now, battle!

**Derrota**

> Beaten right before the big number…  
> The critics will be brutal.

**Depois da luta**

> We wrote our motto for one audience. A boss. He never came to a single show.
>
> Then that little voice started singing it back to us. Every word. In harmony.
>
> First encore we ever got.  
> …Don't cry, James.  
> …I'm not crying, YOU'RE crying!
>
> Go on, twerp. It's waiting for its next audience.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_JessieAndJames_ChampionIntro:
	.string "There's a song coming from that stage.\n"
	.string "Nobody's singing it. We checked.\p"
	.string "Some other us, somewhere, would've\n"
	.string "been ordered to grab that singer. Net,\l"
	.string "cage, giant balloon. The works.\p"
	.string "Nobody ordered us. So we just sat down\n"
	.string "and listened. …For three days.\p"
	.string "Don't tell anyone. It's bad for our\n"
	.string "reputation. Now, battle!$"

Nexus_Text_JessieAndJames_ChampionDefeat:
	.string "Beaten right before the big number…\n"
	.string "The critics will be brutal.$"

Nexus_Text_JessieAndJames_ChampionAfter:
	.string "{SPEAKER NAME_JESSIE_AND_JAMES}We wrote our motto for one audience.\n"
	.string "A boss. He never came to a single show.\p"
	.string "Then that little voice started singing\n"
	.string "it back to us. Every word. In harmony.\p"
	.string "First encore we ever got.\n"
	.string "…Don't cry, James.\l"
	.string "…I'm not crying, YOU'RE crying!\p"
	.string "Go on, twerp. It's waiting for its next\n"
	.string "audience.$"
```

</details>

**Variação 2** — a diva: a Jessie não divide palco… até ver a troca de figurino no meio da nota.

**Antes da luta**

> Let me make one thing clear. On any stage, there is only ONE star.
>
> And that little singer out there keeps stealing my spotlight! It sings, it dances, it changes costume mid-note!
>
> …Okay, the costume change is good. Very good. I'm taking notes.
>
> But notes can wait. First, you!

**Derrota**

> Upstaged twice in one day…  
> That's a new personal worst.

**Depois da luta**

> It switches from singer to dancer in the middle of a song, and nobody calls it a fake.
>
> We change costumes, and everybody points and shouts our name.
>
> …Maybe we should learn to spin. James, you're on dancing.
>
> Go on. Just don't clap louder for it than you did for me.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_JessieAndJames_ChampionIntro2:
	.string "Let me make one thing clear. On any\n"
	.string "stage, there is only ONE star.\p"
	.string "And that little singer out there keeps\n"
	.string "stealing my spotlight! It sings, it\l"
	.string "dances, it changes costume mid-note!\p"
	.string "…Okay, the costume change is good.\n"
	.string "Very good. I'm taking notes.\p"
	.string "But notes can wait. First, you!$"

Nexus_Text_JessieAndJames_ChampionDefeat2:
	.string "Upstaged twice in one day…\n"
	.string "That's a new personal worst.$"

Nexus_Text_JessieAndJames_ChampionAfter2:
	.string "{SPEAKER NAME_JESSIE_AND_JAMES}It switches from singer to dancer in\n"
	.string "the middle of a song, and nobody calls\l"
	.string "it a fake.\p"
	.string "We change costumes, and everybody\n"
	.string "points and shouts our name.\p"
	.string "…Maybe we should learn to spin. James,\n"
	.string "you're on dancing.\p"
	.string "Go on. Just don't clap louder for it\n"
	.string "than you did for me.$"
```

</details>

**Variação 3** — o Meowth e a canção de graça (no anime ele aprendeu a falar para impressionar alguém; não deu certo).

**Antes da luta**

> Meowth had a plan. Sell tickets to that song out there. Easy money.
>
> Problem is, the song is free. Anybody can hear it. You can't charge for air.
>
> Meowth's been sulking for an hour. We need a win to cheer him up. Ready?

**Derrota**

> No tickets, no win…  
> Meowth's gonna sulk for a week.

**Depois da luta**

> You know, Meowth learned to talk once. To impress someone. It didn't work.
>
> That singer never learned anything to impress anyone. It just sings. For whoever's there.
>
> Meowth's been humming along all afternoon. Off-key. It doesn't seem to mind.
>
> Go on, go listen. First row's free.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_JessieAndJames_ChampionIntro3:
	.string "Meowth had a plan. Sell tickets to that\n"
	.string "song out there. Easy money.\p"
	.string "Problem is, the song is free. Anybody\n"
	.string "can hear it. You can't charge for air.\p"
	.string "Meowth's been sulking for an hour. We\n"
	.string "need a win to cheer him up. Ready?$"

Nexus_Text_JessieAndJames_ChampionDefeat3:
	.string "No tickets, no win…\n"
	.string "Meowth's gonna sulk for a week.$"

Nexus_Text_JessieAndJames_ChampionAfter3:
	.string "{SPEAKER NAME_JESSIE_AND_JAMES}You know, Meowth learned to talk once.\n"
	.string "To impress someone. It didn't work.\p"
	.string "That singer never learned anything to\n"
	.string "impress anyone. It just sings. For\l"
	.string "whoever's there.\p"
	.string "Meowth's been humming along all\n"
	.string "afternoon. Off-key. It doesn't seem to\l"
	.string "mind.\p"
	.string "Go on, go listen. First row's free.$"
```

</details>

### Diário do Looker

📝 **Proposta de 30/09/2026.** Três páginas em [`diario_looker/jessie_e_james/`](diario_looker/jessie_e_james/) (formato em [`DIARIO_LOOKER.md`](../DIARIO_LOOKER.md)): [1 — começo](diario_looker/jessie_e_james/1_comeco.md), [2 — meio](diario_looker/jessie_e_james/2_meio.md), [3 — fim](diario_looker/jessie_e_james/3_fim.md). Fio **Rocket**: procuram um chefe que, no fragmento deles, nunca existiu.
