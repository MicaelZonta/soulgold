# Giovanni

**Região da ficha:** Kanto

Aparece no checklist como:

- **Giovanni — Terra** (Kanto · Líderes de Ginásio) — Líder de Viridian e chefe do Team Rocket.
- **Giovanni** (Kanto · Team Rocket) — líder do sindicato criminoso que explora Pokémon em busca de poder e lucro.

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
| `OBJ_EVENT_GFX_GIOVANNI` | `graphics/object_events/pics/people/rockets/giovanni.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_GIOVANNI` | `graphics/trainers/front_pics/giovanni.png` |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_GIOVANNI` | 95 | 0x55F | Kangaskhan Lv60, Honchkrow Lv61, Nidoqueen Lv61, Persian Lv61, Ursaluna Lv60, Nidoking Lv62 | `src/battle_dome.c` |

### Time das Rift Missions

✅ **Implementado em 27/09/2026** (a proposta abaixo virou código): `TRAINER_NEXUS_GIOVANNI` = **994** (flag de batalha `0x8E2`, limpa antes e depois de cada luta), bloco em `src/data/trainers.party`, nível pelo R2 (tabela em `src/data/nexus/trainers.h`). Fala genérica `Nexus_EventScript_Giovanni_Fight`; campeão: `Nexus_EventScript_Giovanni_Mewtwo_ChampionFight` (para Mewtwo), `Nexus_EventScript_Giovanni_Genesect_ChampionFight` (para Genesect). Tudo em `data/scripts/nexus.inc`, sem blackout, resultado em `VAR_TEMP_3`. Para testar: menu de debug → Rift Missions… → Nexus fights… → Giovanni.

📝 **Proposta de 27/09/2026, aguardando o autor.** `TRAINER_NEXUS_GIOVANNI`, campeão de Mewtwo e Genesect. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler). `Double Battle: No` é o formato em que o time brilha mais; o plano vale nos dois.

Lendário **Mewtwo**, a arma que foi feita para ser a mais forte e não aceitou dono: o que o chefe da Team Rocket mais quis ter. O Genesect, a outra criatura de que ele é campeão, também é lendário (R10), então não cabe junto; fica nas falas. Semi-lendário **Mew**, o original de onde o Mewtwo foi feito. Mega **Kangaskhan** (Normalite), a assinatura dele desde o Red/Blue e do time de campanha. Mais **Nidoking** (o ás de Terra dele), **Rhyperior** (o Rhydon do ginásio de Viridian, evoluído) e **Persian**, o gato do chefe. *Plano (Singles):* o Mew arma Stealth Rock e queima com Will-O-Wisp, o Persian pivota com Taunt e U-turn, o Mewtwo sobe Calm Mind, e Nidoking (Sheer Force + Life Orb) e Rhyperior (Solid Rock, Weakness Policy) batem. *Plano (Doubles):* Fake Out do Persian mais Tailwind do Mew no primeiro turno; a Mega Kangaskhan (Parental Bond) bate Sucker Punch e Double-Edge; o Rhyperior usa Rock Slide nos dois e Protect; o Nidoking usa Earth Power, de alvo único, para não acertar o parceiro.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Mewtwo | Leftovers | Pressure | Timid | Psystrike, Aura Sphere, Ice Beam, Calm Mind |
| Mew | Mental Herb | Synchronize | Timid | Stealth Rock, Will-O-Wisp, Tailwind, Knock Off |
| Kangaskhan | Normalite | Scrappy | Adamant | Double-Edge, Sucker Punch, Drain Punch, Ice Punch |
| Nidoking | Life Orb | Sheer Force | Timid | Earth Power, Sludge Wave, Ice Beam, Flamethrower |
| Rhyperior | Weakness Policy | Solid Rock | Adamant | High Horsepower, Rock Slide, Megahorn, Protect |
| Persian | Focus Sash | Technician | Jolly | Fake Out, Knock Off, U-turn, Taunt |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>dev_scripts/nexus_validar_time.py</code>)</summary>

```
=== TRAINER_NEXUS_GIOVANNI ===
Name: Giovanni
Class: RocketA
Pic: Giovanni
Gender: Male
Music: Rocket
Double Battle: No
AI: Smart Trainer

Mewtwo @ Leftovers
Timid Nature
Level: 100
Ability: Pressure
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Psystrike
- Aura Sphere
- Ice Beam
- Calm Mind

Mew @ Mental Herb
Timid Nature
Level: 100
Ability: Synchronize
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Stealth Rock
- Will-O-Wisp
- Tailwind
- Knock Off

Kangaskhan @ Normalite
Adamant Nature
Level: 100
Ability: Scrappy
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Double-Edge
- Sucker Punch
- Drain Punch
- Ice Punch

Nidoking @ Life Orb
Timid Nature
Level: 100
Ability: Sheer Force
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Earth Power
- Sludge Wave
- Ice Beam
- Flamethrower

Rhyperior @ Weakness Policy
Adamant Nature
Level: 100
Ability: Solid Rock
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- High Horsepower
- Rock Slide
- Megahorn
- Protect

Persian @ Focus Sash
Jolly Nature
Level: 100
Ability: Technician
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Fake Out
- Knock Off
- U-turn
- Taunt
```

</details>


### Lendário associado

**Mewtwo** ou **Genesect** — exemplo aprovado no design (`SOULGOLD_RIFT_MISSIONS_DESIGN.md` §10, "Estrutura do loop": "Giovanni podendo anteceder Mewtwo ou Genesect"). Aprovado só como associação; nada implementado. As fichas abaixo são a proposta de fragmento e falas para cada um.

#### Mewtwo

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_Mewtwo_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Mewtwo**. Giovanni é o campeão dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Giovanni, chefe da Team Rocket e Líder de Viridian. Perdeu para uma criança, desfez a Team Rocket e sumiu; os homens dele passaram anos esperando que voltasse.

**A criatura.** Mewtwo, o Pokémon genético. Criado por cientistas a partir do Mew, numa mansão em Cinnabar, para ser o Pokémon mais forte do mundo. Os diários da mansão dizem que ele ficou poderoso demais para ser controlado; fugiu e foi viver na Cerulean Cave.

**O fragmento.** Uma mansão queimada numa ilha de cinza. Os corredores têm tanques de vidro, todos quebrados de dentro para fora. Páginas de diário rasgadas rolam pelo chão.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário). Pelo [R17](../NEXUS_REGRAS.md), o que o jogador leva é o fragmento que sobra, no nível 1; a ficha do Looker fala desse pedaço, não da criatura domada.

**Chegada**

> A burnt mansion on an island of ash. Its halls were lined with glass tanks, every one cracked open from the inside.
>
> Torn journal pages drifted across the floor. The last one read: 'We could not control it.'

**Boss**

> Every loose page in the mansion lifted off the floor at once and hung in the air.
>
> At the end of the hall, something pale was floating, and it had been waiting for you.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento**

> File L-150. Genetic.
>
> A laboratory that made a power it could not hold, and a man who once wanted to own it.
>
> What came back with you was made by no one. It is small, and new, and nobody's weapon. Keep it that way.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Mewtwo_Arrival:
	.string "A burnt mansion on an island of ash. Its\n"
	.string "halls were lined with glass tanks, every\l"
	.string "one cracked open from the inside.\p"
	.string "Torn journal pages drifted across the\n"
	.string "floor. The last one read: 'We could not\l"
	.string "control it.'$"

Nexus_Text_Mewtwo_Boss:
	.string "Every loose page in the mansion lifted\n"
	.string "off the floor at once and hung in the\l"
	.string "air.\p"
	.string "At the end of the hall, something pale\n"
	.string "was floating, and it had been waiting\l"
	.string "for you.$"

Nexus_Text_Mewtwo_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-150. Genetic.\p"
	.string "A laboratory that made a power it could\n"
	.string "not hold, and a man who once wanted to\l"
	.string "own it.\p"
	.string "What came back with you was made by no\n"
	.string "one. It is small, and new, and nobody's\l"
	.string "weapon. Keep it that way.$"
```

</details>


#### Genesect

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_Genesect_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Genesect**. Giovanni é o campeão dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Giovanni, o chefe que abandonou a Team Rocket depois de perder e deixou os homens dele esperando por um sinal durante três anos.

**A criatura.** Genesect, o Pokémon paleozoico. Um Pokémon Inseto de 300 milhões de anos, revivido pela Team Plasma e modificado com um canhão nas costas para virar arma.

**O fragmento.** Uma fábrica mais velha que qualquer cidade, metade fóssil, metade máquina. Esteiras levam ossos de pedra por fileiras de canhões parados. Em algum lugar, um bipe de mira repete sem parar.

**Falas do fragmento** (narração e Looker; tocam só nos dias deste lendário). Pelo [R17](../NEXUS_REGRAS.md), o que o jogador leva é o fragmento que sobra, no nível 1; a ficha do Looker fala desse pedaço, não da criatura domada.

**Chegada**

> A factory older than any city, half fossil and half machine. Conveyor belts carried stone bones past rows of silent cannons.
>
> Somewhere, a targeting beep kept repeating.

**Boss**

> The beeping stopped. Every cannon on the line turned toward you.
>
> A violet insect of steel dropped from the rafters, and the cannon on its back was already glowing.

**Ficha do Looker, no altar, no dia em que o jogador traz o fragmento**

> File L-649. Paleozoic.
>
> An ancient hunter rebuilt as a weapon, and a retired boss who knows what his own soldiers felt.
>
> What you carried out has no cannon on its back. Only an old hunter's patience.
>
> He asked me who gave it its last order. I said no one living. He seemed relieved.

<details><summary><code>.inc</code> do fragmento</summary>

```asm
Nexus_Text_Genesect_Arrival:
	.string "A factory older than any city, half\n"
	.string "fossil and half machine. Conveyor belts\l"
	.string "carried stone bones past rows of silent\l"
	.string "cannons.\p"
	.string "Somewhere, a targeting beep kept\n"
	.string "repeating.$"

Nexus_Text_Genesect_Boss:
	.string "The beeping stopped. Every cannon on\n"
	.string "the line turned toward you.\p"
	.string "A violet insect of steel dropped from\n"
	.string "the rafters, and the cannon on its back\l"
	.string "was already glowing.$"

Nexus_Text_Genesect_LookerFile:
	.string "{SPEAKER NAME_LOOKER}File L-649. Paleozoic.\p"
	.string "An ancient hunter rebuilt as a weapon,\n"
	.string "and a retired boss who knows what his\l"
	.string "own soldiers felt.\p"
	.string "What you carried out has no cannon on\n"
	.string "its back. Only an old hunter's patience.\p"
	.string "He asked me who gave it its last order. I\n"
	.string "said no one living. He seemed relieved.$"
```

</details>


### Diálogo genérico

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Giovanni_Fight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Giovanni cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala dele mesmo, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

**Antes da luta**

> So, you found me. Don't look so pleased. I've been found by children before.
>
> For years, Viridian's Gym sat locked while its Leader ran an empire from the back door. No adult ever noticed.
>
> A child did. Let us see what kind of child you are.

**Derrota**

> …Again. You all have the same look in your eyes.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Giovanni_Intro:
	.string "So, you found me. Don't look so pleased.\n"
	.string "I've been found by children before.\p"
	.string "For years, Viridian's Gym sat locked\n"
	.string "while its Leader ran an empire from the\l"
	.string "back door. No adult ever noticed.\p"
	.string "A child did. Let us see what kind of\n"
	.string "child you are.$"

Nexus_Text_Giovanni_Defeat:
	.string "…Again. You all have the same look in\n"
	.string "your eyes.$"
```

</details>


#### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mais duas falas genéricas para Giovanni, com a variação 1 (acima, já no jogo) formam as três do sorteio. Mesmo registro do [R16](../NEXUS_REGRAS.md): fala de si, sem citar o lugar nem a criatura do dia.

**Variação 2 — quem não quer nada.** Provocação de chefe: quem chega até ele sempre quer dinheiro, poder ou emprego. Os perigosos são os que não querem nada — e o jogador não quer nada. Na derrota, a constatação irritada.

**Antes da luta**

> Most people who come this far want something from me. Money. Power. A job.
>
> I used to give all three. Then I learned that the ones who want nothing are the dangerous ones.
>
> You want nothing. I can see it. Very well. Then I will take something from you.

**Derrota**

> …Nothing. You want nothing, and still you won.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Giovanni_Intro2:
	.string "Most people who come this far want\n"
	.string "something from me. Money. Power. A job.\p"
	.string "I used to give all three. Then I learned\n"
	.string "that the ones who want nothing are the\l"
	.string "dangerous ones.\p"
	.string "You want nothing. I can see it. Very\n"
	.string "well. Then I will take something from\l"
	.string "you.$"

Nexus_Text_Giovanni_Defeat2:
	.string "…Nothing. You want nothing, and still\n"
	.string "you won.$"
```

</details>

**Variação 3 — o filho.** O que ele perdeu (R21 + fio Rocket, o lado do pai): um filho de cabelo vermelho e o temperamento dele, que odiava tudo o que ele construiu. O Giovanni esperava que o menino viesse tomar tudo; quem veio foi outra criança (coerente com a variação 1). Não depende de o jogador conhecer o Silver.

**Antes da luta**

> I had a son. Red hair. My temper. He hated everything I built.
>
> I thought one day he would come and take it all from me. I was almost looking forward to it.
>
> He never came. Someone else did. …You'll do. Come!

**Derrota**

> You have his eyes. …No. You don't. Go.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Giovanni_Intro3:
	.string "I had a son. Red hair. My temper. He\n"
	.string "hated everything I built.\p"
	.string "I thought one day he would come and\n"
	.string "take it all from me. I was almost looking\l"
	.string "forward to it.\p"
	.string "He never came. Someone else did. …You'll\n"
	.string "do. Come!$"

Nexus_Text_Giovanni_Defeat3:
	.string "You have his eyes. …No. You don't. Go.$"
```

</details>


### Diálogo associado ao lendário

#### Mewtwo

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Giovanni_Mewtwo_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Giovanni é o **campeão**, a luta logo antes do Mewtwo. A fala é sobre a criatura, sem dizer o nome dela.

O Giovanni fala da criatura com um respeito que não admitiria aos homens dele: fizeram aquilo numa ilha, a partir de algo mais antigo e gentil, para ser o Pokémon mais forte do mundo, e conseguiram. Aí ela foi embora. Ninguém comanda uma coisa feita para ser mais forte que quem a fez. A virada vem depois da luta: ele sempre disse que *possuía* Pokémon fortes; ela foi feita para ser possuída e recusou, preferiu uma caverna. Ele também se escondeu uma vez, depois que uma criança o venceu, e chamou isso de estratégia. Não tente possuí-la; dê a ela um motivo. É um conselho que ele mesmo nunca seguiu.

**Antes da luta**

> You've seen it. The one that floats as if gravity were only a suggestion.
>
> Men made it on an island, from something older and gentler. They wanted the strongest Pokémon in the world. They got it.
>
> Then it left. No one commands a thing built to be stronger than its makers.
>
> I respect that more than I would ever tell my men. Come!

**Derrota**

> Hm. You fight like someone with nothing to prove. Irritating.

**Depois da luta**

> I have owned many strong Pokémon. Owned. That was always the word I used.
>
> That creature was made to be owned, and it refused. It chose a cave over a master.
>
> I went into hiding once too, after a child beat me. I called it strategy.
>
> Don't try to own it. Give it a reason. …Advice I never took myself.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Giovanni_Mewtwo_ChampionIntro:
	.string "You've seen it. The one that floats as\n"
	.string "if gravity were only a suggestion.\p"
	.string "Men made it on an island, from something\n"
	.string "older and gentler. They wanted the\l"
	.string "strongest Pokémon in the world. They\l"
	.string "got it.\p"
	.string "Then it left. No one commands a thing\n"
	.string "built to be stronger than its makers.\p"
	.string "I respect that more than I would ever\n"
	.string "tell my men. Come!$"

Nexus_Text_Giovanni_Mewtwo_ChampionDefeat:
	.string "Hm. You fight like someone with nothing\n"
	.string "to prove. Irritating.$"

Nexus_Text_Giovanni_Mewtwo_ChampionAfter:
	.string "{SPEAKER NAME_GIOVANNI}I have owned many strong Pokémon.\n"
	.string "Owned. That was always the word I used.\p"
	.string "That creature was made to be owned, and\n"
	.string "it refused. It chose a cave over a\l"
	.string "master.\p"
	.string "I went into hiding once too, after a\n"
	.string "child beat me. I called it strategy.\p"
	.string "Don't try to own it. Give it a reason.\n"
	.string "…Advice I never took myself.$"
```

</details>


##### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mais duas falas de campeão para este lendário; com a variação 1 (acima, já no jogo) formam as três. Sobre a criatura, sem dizer o nome dela; só o `ChampionAfter` leva plaquinha.

**Variação 2 — a armadura vazia.** Lore do anime (primeiro filme): o Giovanni mandou fazer uma armadura para a criatura, e ela o chamou de mestre por um tempo. Depois saiu do ginásio e deixou a armadura em pé no corredor, vazia — imagem que o diário retoma. Depois da luta: mediram a força dela e esqueceram de medir a paciência.

**Antes da luta**

> I once commissioned armor for it. Plates of steel, a helmet full of wires. The finest engineers in Kanto.
>
> It wore the armor for a time. It called me master. I believed it.
>
> Then it walked out of my Gym and left the armor standing in the hall, empty. It stands there still.
>
> Let us see if you are harder to keep. Come!

**Derrota**

> …You shed my strategy the way it shed that armor.

**Depois da luta**

> The scientists called it the strongest. They measured its power and forgot to measure its patience.
>
> It waited years inside that armor, deciding what it was. Then it decided.
>
> Don't cage it and don't command it. Ask it a question. It has been waiting for someone to ask.
>
> No one ever did. Certainly not me.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Giovanni_Mewtwo_ChampionIntro2:
	.string "I once commissioned armor for it. Plates\n"
	.string "of steel, a helmet full of wires. The\l"
	.string "finest engineers in Kanto.\p"
	.string "It wore the armor for a time. It called\n"
	.string "me master. I believed it.\p"
	.string "Then it walked out of my Gym and left\n"
	.string "the armor standing in the hall, empty.\l"
	.string "It stands there still.\p"
	.string "Let us see if you are harder to keep.\n"
	.string "Come!$"

Nexus_Text_Giovanni_Mewtwo_ChampionDefeat2:
	.string "…You shed my strategy the way it shed\n"
	.string "that armor.$"

Nexus_Text_Giovanni_Mewtwo_ChampionAfter2:
	.string "{SPEAKER NAME_GIOVANNI}The scientists called it the strongest.\n"
	.string "They measured its power and forgot to\l"
	.string "measure its patience.\p"
	.string "It waited years inside that armor,\n"
	.string "deciding what it was. Then it decided.\p"
	.string "Don't cage it and don't command it. Ask\n"
	.string "it a question. It has been waiting for\l"
	.string "someone to ask.\p"
	.string "No one ever did. Certainly not me.$"
```

</details>

**Variação 3 — o riso que tiraram.** Dúvida: a criatura foi feita de algo pequeno e rosa que brinca nas nuvens e ri; tiraram o riso e o resto virou o mais forte. O Giovanni se pergunta o que sobraria se fizessem o mesmo com ele. Depois, a confissão que liga ao caderno do Blaine: ele pagou pela ilha e nunca leu os diários dos cientistas.

**Antes da luta**

> Do you know what it was made from? Something small and pink that plays in the clouds and laughs.
>
> They took that laugh out. Everything left over became the strongest Pokémon alive.
>
> I have always wondered what they would get if they did the same to me.
>
> …Something like this. Come!

**Derrota**

> Hm. Laughter would have served me better.

**Depois da luta**

> On that island, the scientists wrote in their journals every day. The last entries are all questions.
>
> 'Why was it born? Who asked for it?' Not one of them wrote an answer.
>
> I paid for that island. I never read the journals until it was far too late.
>
> Read them for me. Then decide if it deserves an answer from you.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Giovanni_Mewtwo_ChampionIntro3:
	.string "Do you know what it was made from?\n"
	.string "Something small and pink that plays in\l"
	.string "the clouds and laughs.\p"
	.string "They took that laugh out. Everything\n"
	.string "left over became the strongest\l"
	.string "Pokémon alive.\p"
	.string "I have always wondered what they would\n"
	.string "get if they did the same to me.\p"
	.string "…Something like this. Come!$"

Nexus_Text_Giovanni_Mewtwo_ChampionDefeat3:
	.string "Hm. Laughter would have served me\n"
	.string "better.$"

Nexus_Text_Giovanni_Mewtwo_ChampionAfter3:
	.string "{SPEAKER NAME_GIOVANNI}On that island, the scientists wrote in\n"
	.string "their journals every day. The last\l"
	.string "entries are all questions.\p"
	.string "'Why was it born? Who asked for it?'\n"
	.string "Not one of them wrote an answer.\p"
	.string "I paid for that island. I never read the\n"
	.string "journals until it was far too late.\p"
	.string "Read them for me. Then decide if it\n"
	.string "deserves an answer from you.$"
```

</details>



#### Genesect

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Giovanni_Genesect_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Giovanni é o **campeão**, a luta logo antes do Genesect. A fala é sobre a criatura, sem dizer o nome dela.

O Giovanni reconhece a criatura como a um soldado: trezentos milhões de anos, desenterrada e reconstruída como arma por gente que tinha um rei e um discurso. Depois perderam e se espalharam, e ela continua ali, armada, esperando ordem. A virada: ele sabe como é isso, deixou um exército esperando uma vez. Depois da luta ele conta que os homens dele mantiveram o uniforme por três anos, esperando um sinal que ele nunca mandou; ele chamava de lealdade e era só um hábito que ele pôs neles. Vença a criatura e não dê ordens: dê a ela o que ele nunca deu aos homens dele, um dia de folga.

**Antes da luta**

> Did you see the one with the cannon on its back? Three hundred million years old. Dug up and rebuilt as a weapon.
>
> The people who rebuilt it had a king and a grand speech. Then they lost, and scattered.
>
> It's still here. Still armed. Still waiting for an order.
>
> I know what that looks like. I once left an army waiting. Let's go!

**Derrota**

> Enough. Your aim was cleaner than mine.

**Depois da luta**

> When I left Team Rocket, my men kept their uniforms on for three years, waiting for a signal I never sent.
>
> I called it loyalty. It was only a habit I had built into them.
>
> That creature is the same. Its habit simply has a cannon.
>
> Beat it, and give it no orders. Give it what I never gave them. A day off.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Giovanni_Genesect_ChampionIntro:
	.string "Did you see the one with the cannon on\n"
	.string "its back? Three hundred million years\l"
	.string "old. Dug up and rebuilt as a weapon.\p"
	.string "The people who rebuilt it had a king and\n"
	.string "a grand speech. Then they lost, and\l"
	.string "scattered.\p"
	.string "It's still here. Still armed. Still\n"
	.string "waiting for an order.\p"
	.string "I know what that looks like. I once left\n"
	.string "an army waiting. Let's go!$"

Nexus_Text_Giovanni_Genesect_ChampionDefeat:
	.string "Enough. Your aim was cleaner than mine.$"

Nexus_Text_Giovanni_Genesect_ChampionAfter:
	.string "{SPEAKER NAME_GIOVANNI}When I left Team Rocket, my men kept\n"
	.string "their uniforms on for three years,\l"
	.string "waiting for a signal I never sent.\p"
	.string "I called it loyalty. It was only a habit I\n"
	.string "had built into them.\p"
	.string "That creature is the same. Its habit\n"
	.string "simply has a cannon.\p"
	.string "Beat it, and give it no orders. Give it\n"
	.string "what I never gave them. A day off.$"
```

</details>


##### Variações 2 e 3 (📝 proposta de 30/09/2026)

Mais duas falas de campeão para este lendário; com a variação 1 (acima, já no jogo) formam as três. Sobre a criatura, sem dizer o nome dela; só o `ChampionAfter` leva plaquinha.

**Variação 2 — fóssil com canhão.** Negócio e melancolia: os homens dele já cavaram fósseis numa caverna de montanha e venderam (o Mt. Moon da Rocket). Alguém cavou este e deu a ele um canhão — negócio melhor. Mas fóssil armado ainda é fóssil, de um mundo que acabou; ele também, alguns dias. Depois: os Drives, uma arma para cada estação, e o caçador que nunca precisou delas.

**Antes da luta**

> My men once dug fossils out of a mountain cave. We sold them. Good business.
>
> Someone else dug up this one and gave it a cannon. Better business, I suppose.
>
> But a fossil with a gun is still a fossil. It belongs to a world that ended long ago.
>
> So do I, some days. Come!

**Derrota**

> Hm. Obsolete. The two of us.

**Depois da luta**

> It has a slot on its back for a drive. Each one changes what the cannon fires.
>
> Fire, ice, water, lightning. Its makers wanted a weapon for every season.
>
> They forgot it was a hunter first. It never needed their seasons.
>
> Leave the slot empty, if you can. Let it remember what it hunted for itself.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Giovanni_Genesect_ChampionIntro2:
	.string "My men once dug fossils out of a\n"
	.string "mountain cave. We sold them. Good\l"
	.string "business.\p"
	.string "Someone else dug up this one and gave\n"
	.string "it a cannon. Better business, I suppose.\p"
	.string "But a fossil with a gun is still a fossil.\n"
	.string "It belongs to a world that ended long\l"
	.string "ago.\p"
	.string "So do I, some days. Come!$"

Nexus_Text_Giovanni_Genesect_ChampionDefeat2:
	.string "Hm. Obsolete. The two of us.$"

Nexus_Text_Giovanni_Genesect_ChampionAfter2:
	.string "{SPEAKER NAME_GIOVANNI}It has a slot on its back for a drive.\n"
	.string "Each one changes what the cannon\l"
	.string "fires.\p"
	.string "Fire, ice, water, lightning. Its makers\n"
	.string "wanted a weapon for every season.\p"
	.string "They forgot it was a hunter first. It\n"
	.string "never needed their seasons.\p"
	.string "Leave the slot empty, if you can. Let it\n"
	.string "remember what it hunted for itself.$"
```

</details>

**Variação 3 — o alvo.** Dúvida: a criatura mirou nele, o canhão brilhando, e parou para olhá-lo — o olhar dos soldados esperando para saber se ele era quem dava as ordens. Ela baixou o canhão; misericórdia ou decepção? Depois: ela reconheceu a espécie dele, a de quem aponta e diz "aquele". É a primeira vez que ele é o apontado. Educativo.

**Antes da luta**

> It aimed at me. The cannon was glowing. Then it stopped, and looked at me for a long time.
>
> I have been looked at like that before. By soldiers, waiting to hear if I was the one giving orders.
>
> I said nothing. It lowered the cannon. …I still don't know if that was mercy or disappointment.
>
> Let us find out what it thinks of you.

**Derrota**

> …It would have lowered the cannon for you too.

**Depois da luta**

> I think it recognized me. Not my face. My kind. The kind that points at things and says, 'That one.'
>
> I've pointed at a great many things. People. Pokémon. Whole towns.
>
> It is the first time I have been the thing pointed at. It's educational.
>
> Go on. And don't point. Walk up to it.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Giovanni_Genesect_ChampionIntro3:
	.string "It aimed at me. The cannon was glowing.\n"
	.string "Then it stopped, and looked at me for a\l"
	.string "long time.\p"
	.string "I have been looked at like that before.\n"
	.string "By soldiers, waiting to hear if I was the\l"
	.string "one giving orders.\p"
	.string "I said nothing. It lowered the cannon.\n"
	.string "…I still don't know if that was mercy or\l"
	.string "disappointment.\p"
	.string "Let us find out what it thinks of you.$"

Nexus_Text_Giovanni_Genesect_ChampionDefeat3:
	.string "…It would have lowered the cannon for\n"
	.string "you too.$"

Nexus_Text_Giovanni_Genesect_ChampionAfter3:
	.string "{SPEAKER NAME_GIOVANNI}I think it recognized me. Not my face.\n"
	.string "My kind. The kind that points at things\l"
	.string "and says, 'That one.'\p"
	.string "I've pointed at a great many things.\n"
	.string "People. Pokémon. Whole towns.\p"
	.string "It is the first time I have been the\n"
	.string "thing pointed at. It's educational.\p"
	.string "Go on. And don't point. Walk up to it.$"
```

</details>



Falante novo: `SP_NAME_GIOVANNI` (ainda não existe em `include/constants/speaker_names.h`).
