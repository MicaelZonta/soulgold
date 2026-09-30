# Phoebe

**Região da ficha:** Hoenn

Aparece no checklist como:

- **Phoebe — Fantasma** (Hoenn · Elite Four e Campeões) — treinadora espiritual ligada ao Mt. Pyre.

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
| `OBJ_EVENT_GFX_PHOEBE` | `graphics/object_events/pics/people/elite_four/phoebe.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_ELITE_FOUR_PHOEBE` | `graphics/trainers/front_pics/elite_four_phoebe.png` |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_PHOEBE2` | 861 | 0x85D | **sem time** (ID reservado, sem bloco no `.party`) | — (nenhum script chama) |

IDs aposentados na limpeza de treinadores (não reaproveitar sem necessidade): `TRAINER_UNUSED_451` (ex-`TRAINER_PHOEBE`, 262).

### Time das Rift Missions

✅ **Implementado em 27/09/2026** (a proposta abaixo virou código): `TRAINER_NEXUS_PHOEBE` = **1025** (flag de batalha `0x901`, limpa antes e depois de cada luta), bloco em `src/data/trainers.party`, nível pelo R2 (tabela em `src/data/nexus/trainers.h`). Fala genérica `Nexus_EventScript_Phoebe_Fight`; campeão: `Nexus_EventScript_Phoebe_ChampionFight` (para Flutter Mane). Tudo em `data/scripts/nexus.inc`, sem blackout, resultado em `VAR_TEMP_3`. Para testar: menu de debug → Rift Missions… → Nexus fights… → Phoebe.

📝 **Proposta de 27/09/2026, aguardando o autor.** `TRAINER_NEXUS_PHOEBE`, campeão de Flutter Mane. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler).

Lendário **Giratina** (Fantasma/Dragão, o senhor do Mundo Distorcido, o outro lado que a Phoebe escuta desde o Mt. Pyre); semi-lendário **Flutter Mane** (Fantasma/Fada, o fantasma antigo de quem ela é campeã); Mega **Banette** (Ghostite; Prankster, a boneca abandonada que ela tem desde Emerald). Mais **Dusclops** (o ás dela em Emerald), **Sableye** e **Dusknoir** (do time dela em ORAS).

*Plano (Singles):* queimar e drenar. Sableye (Prankster) e Dusclops espalham Will-O-Wisp; o Giratina bate de Hex, que dobra contra alvo com status; a Mega Banette ameaça Destiny Bond com prioridade; a Flutter Mane limpa rápido. Contra time muito rápido, o Dusclops tem Trick Room: aí Giratina, Dusknoir e Banette passam na frente.

*Plano (Doubles):* Sableye abre com Fake Out e Will-O-Wisp com prioridade; a Flutter Mane varre com Dazzling Gleam nos dois; o Giratina segue com Hex no queimado; o Dusknoir cobre com Ice Punch e Protect.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Giratina | Leftovers | Pressure | Bold | Hex, Will-O-Wisp, Dragon Pulse, Rest |
| Flutter Mane | Booster Energy | Protosynthesis | Timid | Moonblast, Shadow Ball, Dazzling Gleam, Protect |
| Banette | Ghostite | Frisk | Adamant | Poltergeist, Shadow Sneak, Knock Off, Destiny Bond |
| Dusclops | Eviolite | Frisk | Relaxed | Trick Room, Night Shade, Will-O-Wisp, Pain Split |
| Sableye | Leftovers | Prankster | Careful | Fake Out, Will-O-Wisp, Recover, Foul Play |
| Dusknoir | Sitrus Berry | Frisk | Brave | Poltergeist, Ice Punch, Shadow Sneak, Protect |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>dev_scripts/nexus_validar_time.py</code>)</summary>

```
=== TRAINER_NEXUS_PHOEBE ===
Name: Phoebe
Class: Elite Four
Pic: Elite Four Phoebe
Gender: Female
Music: Elite Four
Double Battle: No
AI: Smart Trainer

Giratina @ Leftovers
Bold Nature
Level: 100
Ability: Pressure
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Hex
- Will-O-Wisp
- Dragon Pulse
- Rest

Flutter Mane @ Booster Energy
Timid Nature
Level: 100
Ability: Protosynthesis
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Moonblast
- Shadow Ball
- Dazzling Gleam
- Protect

Banette @ Ghostite
Adamant Nature
Level: 100
Ability: Frisk
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Poltergeist
- Shadow Sneak
- Knock Off
- Destiny Bond

Dusclops @ Eviolite
Relaxed Nature
Level: 100
Ability: Frisk
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Trick Room
- Night Shade
- Will-O-Wisp
- Pain Split

Sableye @ Leftovers
Careful Nature
Level: 100
Ability: Prankster
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Fake Out
- Will-O-Wisp
- Recover
- Foul Play

Dusknoir @ Sitrus Berry
Brave Nature
Level: 100
Ability: Frisk
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Poltergeist
- Ice Punch
- Shadow Sneak
- Protect
```

</details>


### Lendário associado

#### Flutter Mane

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_FlutterMane_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Flutter Mane**. Phoebe é o campeão dela: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Phoebe, da Elite Four de Hoenn, especialista em Fantasma. Treinou no Mt. Pyre, o monte dos túmulos, e diz conversar com os Pokémon Fantasma.

**A criatura.** Flutter Mane, Pokémon Paradoxo antigo (Fantasma/Fada), parente pré-histórico de um fantasma travesso que se alimenta de sustos. Tem uma juba de penas e vive nas profundezas da Area Zero.

**O fragmento.** Uma caverna sem fundo onde plumas cor de ferrugem flutuam sem vento. Lá embaixo alguém ri, como uma criança escondida há tempo demais.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário):

**Chegada**

> A cave with no bottom.
>
> Rust-colored plumes drifted in the air, though there was no wind.
>
> Somewhere below, someone was laughing. It sounded like a child who had been hiding for a very long time.

**Boss**

> The laughing stopped, right behind you.
>
> A mane of feathers unfolded in the dark, and every one of them was looking at you.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento** ([R17](../NEXUS_REGRAS.md))

> File L-987. The Laugh in the Dark.
>
> A cave full of very old laughter, and a girl from the mountain of graves who laughed right back.
>
> What came home with you is small, and it giggles when I turn off the light. She says ghosts are only lonely. I have decided to believe her.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_FlutterMane_Arrival:
	.string "A cave with no bottom.\p"
	.string "Rust-colored plumes drifted in the air,\n"
	.string "though there was no wind.\p"
	.string "Somewhere below, someone was laughing.\n"
	.string "It sounded like a child who had been\l"
	.string "hiding for a very long time.$"

Nexus_Text_FlutterMane_Boss:
	.string "The laughing stopped, right behind you.\p"
	.string "A mane of feathers unfolded in the\n"
	.string "dark, and every one of them was looking\l"
	.string "at you.$"

Nexus_Text_FlutterMane_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-987. The Laugh in the Dark.\p"
	.string "A cave full of very old laughter, and a\n"
	.string "girl from the mountain of graves who\l"
	.string "laughed right back.\p"
	.string "What came home with you is small, and it\n"
	.string "giggles when I turn off the light. She\l"
	.string "says ghosts are only lonely. I have\l"
	.string "decided to believe her.$"
```

</details>


### Diálogo genérico

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Phoebe_Fight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Phoebe cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala dela mesma, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

**Antes da luta**

> Ahahaha! I'm Phoebe. I trained on Mt. Pyre, way up where the graves are.
>
> Everyone thinks the dead are scary, but mostly they're just lonely!
>
> Up there I learned to hear them. My Dusclops hears them best of all.
>
> So let's play! They love it when someone plays!

**Derrota**

> Oh, you win! Ahaha, the ghosts are cheering for you.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Phoebe_Intro:
	.string "Ahahaha! I'm Phoebe. I trained on Mt.\n"
	.string "Pyre, way up where the graves are.\p"
	.string "Everyone thinks the dead are scary,\n"
	.string "but mostly they're just lonely!\p"
	.string "Up there I learned to hear them. My\n"
	.string "Dusclops hears them best of all.\p"
	.string "So let's play! They love it when\n"
	.string "someone plays!$"

Nexus_Text_Phoebe_Defeat:
	.string "Oh, you win! Ahaha, the ghosts are\n"
	.string "cheering for you.$"
```

</details>

#### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mais duas falas genéricas ([R16](../NEXUS_REGRAS.md)): para o jogo sortear junto com a variação 1 acima (o sorteio ainda não existe no código). Nenhuma cita o lugar nem a criatura do dia.

**Variação 2** — lembrança: a avó guarda duas esferas, vermelha e azul, no topo do Mt. Pyre; se alguém as levar, a montanha fica triste. A Phoebe não sabe como é uma montanha triste. ([R21](../NEXUS_REGRAS.md): no fragmento dela alguém levou — ver o diário.)

**Antes da luta**

> My grandma keeps two orbs at the top of Mt. Pyre. Red and blue, and very, very old.
>
> She says if anyone ever takes them, the mountain gets sad.
>
> I don't know what a sad mountain looks like! Ahaha, I hope I never find out.
>
> Come on, let's play! My Pokémon are bored!

**Derrota**

> Ahaha! You're good! Grandma would like you.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Phoebe_Intro2:
	.string "My grandma keeps two orbs at the top\n"
	.string "of Mt. Pyre. Red and blue, and very,\l"
	.string "very old.\p"
	.string "She says if anyone ever takes them,\n"
	.string "the mountain gets sad.\p"
	.string "I don't know what a sad mountain looks\n"
	.string "like! Ahaha, I hope I never find out.\p"
	.string "Come on, let's play! My Pokémon are\n"
	.string "bored!$"

Nexus_Text_Phoebe_Defeat2:
	.string "Ahaha! You're good! Grandma would like\n"
	.string "you.$"
```

</details>

**Variação 3** — humor e pegadinha: “fique parado, tem alguém atrás de você” — e ri da cara do jogador. Quase ninguém: eles só queriam ver o susto.

**Antes da luta**

> Shh! Hold still. Someone's standing right behind you.
>
> …Ahahaha! Your face! There's nobody there.
>
> Well. Almost nobody. They just wanted to see you jump.
>
> Now they've seen it, so let's battle!

**Derrota**

> Ahaha, they jumped that time. I told them you were good.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Phoebe_Intro3:
	.string "Shh! Hold still. Someone's standing\n"
	.string "right behind you.\p"
	.string "…Ahahaha! Your face! There's nobody\n"
	.string "there.\p"
	.string "Well. Almost nobody. They just wanted\n"
	.string "to see you jump.\p"
	.string "Now they've seen it, so let's battle!$"

Nexus_Text_Phoebe_Defeat3:
	.string "Ahaha, they jumped that time. I told\n"
	.string "them you were good.$"
```

</details>


### Diálogo associado ao lendário

#### Flutter Mane

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Phoebe_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Phoebe é o **campeão**, a luta logo antes da Flutter Mane. A fala é sobre a criatura, sem dizer o nome dela.

A Phoebe acha que os fantasmas não são assustadores, só solitários. Aqui ela encontra um fantasma que come susto e tentou assustar de volta; não deu certo. A criatura é tão antiga que ninguém grita perto dela há milhares de anos: está faminta. A virada: o conselho da Phoebe é não ser corajoso diante dela, e sim se surpreender, porque é só isso que ela quer.

**Antes da luta**

> Did you hear it laughing? I tried to scare it back! It didn't work.
>
> I think it's a ghost that eats fear. It hides and giggles and waits for you to scream.
>
> But it's so old… Nobody has screamed for it in thousands of years.
>
> Ahaha! It's starving! Let's play first!

**Derrota**

> Ahaha! I lost! Should I scream? Would that help it?

**Depois da luta**

> Ghosts on Mt. Pyre want to be remembered. That's all.
>
> This one is older than remembering. It just wants someone to react.
>
> So when you meet it, don't be brave, okay? Be surprised.
>
> It's been waiting so long for someone to be surprised.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Phoebe_ChampionIntro:
	.string "Did you hear it laughing? I tried to\n"
	.string "scare it back! It didn't work.\p"
	.string "I think it's a ghost that eats fear. It\n"
	.string "hides and giggles and waits for you to\l"
	.string "scream.\p"
	.string "But it's so old… Nobody has screamed\n"
	.string "for it in thousands of years.\p"
	.string "Ahaha! It's starving! Let's play\n"
	.string "first!$"

Nexus_Text_Phoebe_ChampionDefeat:
	.string "Ahaha! I lost! Should I scream? Would\n"
	.string "that help it?$"

Nexus_Text_Phoebe_ChampionAfter:
	.string "{SPEAKER NAME_PHOEBE}Ghosts on Mt. Pyre want to be\n"
	.string "remembered. That's all.\p"
	.string "This one is older than remembering. It\n"
	.string "just wants someone to react.\p"
	.string "So when you meet it, don't be brave,\n"
	.string "okay? Be surprised.\p"
	.string "It's been waiting so long for someone\n"
	.string "to be surprised.$"
```

</details>

##### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mais duas falas de campeão para esta criatura, sem dizer o nome dela; para o jogo sortear junto com a variação 1 acima (o sorteio ainda não existe no código).

**Variação 2** — brincadeira que revela: a criatura quis brincar de esconde-esconde; a Phoebe se escondeu e esperou, até perceber que ela nunca ia procurar. Só sabe se esconder, ninguém a ensinou a procurar. O conselho: não espere, vá procurar e diga “achei!”.

**Antes da luta**

> It wanted to play hide-and-seek! So I hid. I'm really good at hiding.
>
> I waited so long… Then I realized it was never going to look.
>
> It only knows how to hide. Nobody ever taught it to seek.
>
> Ahaha! You seek me, then!

**Derrota**

> Found me! Ahaha, that's how it's done.

**Depois da luta**

> Things that hide for a very long time forget how to come out.
>
> Some ghosts on Mt. Pyre are like that. You have to go and find them.
>
> So when you get in there, don't wait for it. Go looking.
>
> Then say, 'Found you!' It's never heard that before.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Phoebe_ChampionIntro2:
	.string "It wanted to play hide-and-seek! So I\n"
	.string "hid. I'm really good at hiding.\p"
	.string "I waited so long… Then I realized it\n"
	.string "was never going to look.\p"
	.string "It only knows how to hide. Nobody ever\n"
	.string "taught it to seek.\p"
	.string "Ahaha! You seek me, then!$"

Nexus_Text_Phoebe_ChampionDefeat2:
	.string "Found me! Ahaha, that's how it's done.$"

Nexus_Text_Phoebe_ChampionAfter2:
	.string "{SPEAKER NAME_PHOEBE}Things that hide for a very long time\n"
	.string "forget how to come out.\p"
	.string "Some ghosts on Mt. Pyre are like that.\n"
	.string "You have to go and find them.\p"
	.string "So when you get in there, don't wait\n"
	.string "for it. Go looking.\p"
	.string "Then say, 'Found you!' It's never\n"
	.string "heard that before.$"
```

</details>

**Variação 3** — o que ela perdeu: a risada da criatura parece a da Phoebe pequena, antes de aprender a rir de propósito. Ela não gosta de pensar nisso. A virada: a coisa não ri para assustar; ri para não ter medo, pelo mesmo motivo que ela.

**Antes da luta**

> Can I tell you something strange? Its laugh sounds a little like mine.
>
> Not now. When I was small. Before I learned to laugh on purpose.
>
> I don't like thinking about that. So, ahaha! Let's play instead!

**Derrota**

> Oh… you won. I'm laughing on purpose again, aren't I?

**Depois da luta**

> I learned to laugh on Mt. Pyre so the graves wouldn't feel so quiet.
>
> I think it's been laughing down there forever, for the same reason.
>
> It's not trying to scare anyone. It's trying not to be scared.
>
> Be gentle, okay? You'd be laughing too.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Phoebe_ChampionIntro3:
	.string "Can I tell you something strange? Its\n"
	.string "laugh sounds a little like mine.\p"
	.string "Not now. When I was small. Before I\n"
	.string "learned to laugh on purpose.\p"
	.string "I don't like thinking about that. So,\n"
	.string "ahaha! Let's play instead!$"

Nexus_Text_Phoebe_ChampionDefeat3:
	.string "Oh… you won. I'm laughing on purpose\n"
	.string "again, aren't I?$"

Nexus_Text_Phoebe_ChampionAfter3:
	.string "{SPEAKER NAME_PHOEBE}I learned to laugh on Mt. Pyre so the\n"
	.string "graves wouldn't feel so quiet.\p"
	.string "I think it's been laughing down there\n"
	.string "forever, for the same reason.\p"
	.string "It's not trying to scare anyone. It's\n"
	.string "trying not to be scared.\p"
	.string "Be gentle, okay? You'd be laughing too.$"
```

</details>


Falante novo: `SP_NAME_PHOEBE` (ainda não existe em `include/constants/speaker_names.h`).
