# Nexus — o campeão de cada Ultra Beast

> **Status: proposta, 26/09/2026, aguardando o autor.** Nada daqui está na ROM.
> Este documento fecha o conteúdo das 11 expedições de Ultra Beast do Nexus:
> conceito do fragmento, o **campeão do lendário** (a quinta luta do R5 de
> [`NEXUS_REGRAS.md`](NEXUS_REGRAS.md)), o time dele e as falas. O sistema do
> Daily (salas, teleportes, sorteio, estado) é das regras R3, R5 e R15 e não é
> tratado aqui.
>
> Arquivos que acompanham este doc:
> - [`ULTRA_BEASTS.party`](ULTRA_BEASTS.party): os 11 times no formato do
>   `src/data/trainers.party`, seguindo R10–R13 (conferência em §5.2).
> - [`ULTRA_BEASTS_TEXTS.inc`](ULTRA_BEASTS_TEXTS.inc): as 66 falas em formato
>   `.string`, medidas com `medir_linha.py` (nenhuma passa de 208 px).
>
> Cada um dos 11 treinadores tem ficha em `nexus/<região>/`, e a ficha aponta
> para cá nas seções de time, lendário associado e diálogo do lendário.

---

## 1. O que é o Nexus

O §10 do design define os destinos como **realidades quebradas: fragmentos que
materializam conceitos do universo**, e não mundos inteiros. Este documento leva
isso ao pé da letra para as Ultra Beasts.

**Cada Ultra Beast é um conceito, e o conceito já tem nome.** A Polícia
Internacional batizou cada uma com um codinome (UB-01 Symbiont, UB-02 Absorption,
e assim por diante). O Looker é da Polícia Internacional. É natural que o
fragmento seja chamado pelo codinome no arquivo dele, e que o lugar *seja* o
codinome: o fragmento de Symbiont é o que "simbionte" significa, transformado
em chão, luz e ar.

**O quinto treinador é um eco.** O fragmento não tem habitantes. Ele puxa de
algum lugar uma pessoa cuja essência ressoa com o conceito e a monta ali: o
suficiente para lutar com o time que ela teria, falar como ela fala e lembrar do
que ela lembra. Não é a pessoa de verdade, e o jogo nunca afirma nem nega isso
em voz alta. É por isso que o treinador pode vir de qualquer região, inclusive
de uma que o jogador nunca visitou.

**O conceito vaza para dentro do eco.** Esse é o motor de cada cena. O eco não
é só "o Volkner num cenário elétrico": é o Volkner vivendo o conceito do
fragmento, e percebendo, ou quase, que alguma coisa está errada. Cada um tem o
mesmo arco curto de três batidas:

| Batida | Onde | O que faz |
|---|---|---|
| **Estranhamento** | `_Intro` | O eco descreve o fragmento de dentro, na própria voz, e diz o que há de errado com ele. |
| **Resposta** | `_Defeat` | A vitória do jogador contradiz o conceito (o que não se deixa tocar foi tocado; o que nunca cai ficou no chão). |
| **Aviso** | `_After` | O eco aponta para o que vem, sem nomear a criatura, e dá ao jogador uma instrução que é a lição do conceito. |

Depois do aviso, o conceito se condensa na Ultra Beast (`_Boss`). De volta ao
altar, o Looker arquiva o dia (`_LookerFile`): uma fala curta que junta o eco e a
criatura na mesma ficha. É a coleção de quem joga o loop: onze fichas, e cada
uma só aparece depois de a expedição daquela UB ser vencida.

### 1.1. Regras de escrita do Nexus

Valem para todo texto de fragmento, inclusive os que ainda vão ser escritos para
lendários.

- **Ninguém provoca o jogador.** O eco não está ali para desafiar nem para
  humilhar. Ele está preso num conceito e fala disso. O tom é de estranheza,
  não de rivalidade.
- **Ninguém nomeia a criatura.** Nem o eco, nem a narração. "Something below us",
  "that thing", "a little one". O nome só aparece na tela de batalha. O codinome
  só aparece na ficha do Looker, depois.
- **O eco não sabe que é eco.** Alguns desconfiam (Colress mede, Steven percebe
  que nada cai, Fantina se pergunta quem paga as luzes). Nenhum conclui.
- **O eco não conhece o jogador.** Trata-o como um visitante, sem saber que é o
  Campeão, sem citar a campanha de Johto. A única memória que o eco traz é a
  dele mesmo (Guzma lembra do Kukui; Byron, do filho; Zossie, de um mundo sem
  luz; Soliera, de um Poipole entregue a alguém).
- **O Looker fica no altar e escreve.** Ele não entra no fragmento. A ficha é o
  único lugar onde o Looker fala do Nexus, e o humor dele cabe ali (o do altar:
  "feeling largely decorative"), porque é depois do perigo.
- **A Anabel não ganha poder novo.** A regra V21 continua valendo: ela sente a
  fenda abrir, e só. Não sabe qual conceito está do outro lado.
- **Nenhuma fala transcreve os jogos.** Todas são originais (design §3.1), mesmo
  quando lembram um traço canônico (o "Hoo hah!" do Bruno é interjeição, não
  citação; o francês da Fantina é traço de personagem).
- **O texto do jogo é em inglês** (CLAUDE.md), as notas de design em português.

---

## 2. As onze expedições

| Codinome | Ultra Beast | Campeão | Conceito em uma linha | Lendário · Semi · Mega do time | Sprite |
|---|---|---|---|---|---|
| UB-01 Symbiont | Nihilego | **Colress** | Poder dado de graça, que tira o freio. | Genesect · Iron Hands · Golurk | **novo** |
| UB-02 Absorption | Buzzwole | **Bruno** | Força tomada dos outros e exibida. | Marshadow · Urshifu · Heracross | existe |
| UB-02 Beauty | Pheromosa | **Elesa** | Beleza que ofusca e não se deixa tocar. | Miraidon · Zapdos · Eelektross | **novo** |
| UB-03 Lighting | Xurkitree | **Volkner** | Luz que apaga tudo em volta para ficar acesa. | Zekrom · Raikou · Raichu | **novo** |
| UB-04 Blaster | Celesteela | **Steven** | Um corpo feito para deixar o chão. | Deoxys · Jirachi · Metagross | existe |
| UB-04 Blade | Kartana | **Ramos** | O corte perfeito, que não deixa nada crescer. | Xerneas · Celebi · Victreebel | **novo** |
| UB-05 Glutton | Guzzlord | **Guzma** | Fome que nunca se sacia. | Yveltal · Buzzwole · Golisopod | **novo** |
| UB Adhesive | Poipole | **Zossie** | O pequeno que gruda em quem traz luz. | Magearna · Mew · Clefable | **novo** |
| UB Stinger | Naganadel | **Soliera** | Um único golpe certeiro, de muito longe. | Eternatus · Latios · Beedrill | **novo** |
| UB Assembly | Stakataka | **Byron** | Muitos que escolheram segurar uns aos outros. | Zamazenta · Registeel · Steelix | **novo** |
| UB Burst | Blacephalon | **Fantina** | O espetáculo que cobra da plateia. | Hoopa · Meloetta · Chandelure | **novo** |

Nenhuma espécie se repete entre dois times. Nenhum time leva a Ultra Beast que
ele mesmo antecede (o Guzma leva a Buzzwole, não a Guzzlord).

**Por que a Lusamine saiu da Nihilego** (ela era a primeira ideia). Ela está
viva no elenco, mora no altar em três dias da semana e luta uma revanche
diária ali: ver um eco dela do outro lado da fenda, no mesmo dia, cria uma
pergunta que o jogo não responde. E o design §3.1 diz que a fusão com a Nihilego
"permanece sem adoção explícita". O Colress ocupa o conceito melhor: o objetivo
dele nos jogos é **tirar de um Pokémon toda a força escondida**, e a neurotoxina
da Nihilego **dá grande poder e tira as inibições**. É o mesmo desejo, visto de
dentro.

**Por que os três da Ultra Recon Squad e não outros.** Em USUM, quem entrega o
Poipole ao jogador é a **Soliera** (Ultra Sun) ou o **Dulse** (Ultra Moon), e o
mundo deles, Ultra Megalopolis, perdeu a luz. A Zossie é a mais nova do grupo e a
mais entusiasmada. A Zossie fica com o Poipole (o filhote) e a Soliera com o
Naganadel (o que o Poipole vira), e a fala dela é sobre "um pequeno que demos a
alguém que nos ajudou".

---

## 3. Fragmento por fragmento

Cada seção traz: o conceito (com o que a Pokédex diz), como o lugar se parece
(para o mapa), por que esse treinador, o que o conceito faz com o eco, o time e
as falas. As falas estão aqui em texto corrido para leitura. A versão exata,
com quebras e códigos, está no `.inc`.

### 3.1. UB-01 Symbiont — Nihilego — Colress

**Conceito.** A Pokédex diz que a Nihilego produz uma neurotoxina forte, e que ela
dá grande poder a quem é injetado enquanto derruba as inibições. O mundo dela, em
USUM, é o Ultra Deep Sea.

**O fragmento.** Água funda que não afoga. Luzes pálidas flutuando, arrastando
fios. Onde uma toca o chão de vidro, o vidro brilha mais forte e trinca um pouco.
Leitura visual: laboratório submerso, tons de azul e branco.

**O treinador.** Colress, o cientista de Black 2/White 2, cujo objetivo declarado
é descobrir como trazer à tona a força verdadeira dos Pokémon.

**O eco.** Tudo o que o Colress sempre quis está ali de graça: o fragmento dá
força a todo Pokémon sem que ninguém precise fazer nada. Ele não precisa mais
pesquisar, só olhar. A vitória do jogador é o dado que ele não consegue
explicar: os Pokémon do jogador pararam antes do limite, e por escolha. O aviso é
o mais honesto que ele consegue dar: "eu recusaria, se fosse você. Digo isso como
alguém que não recusaria".

**Time (R11).** Lendário **Genesect**, semi-lendário **Iron Hands**, Mega
**Golurk** (Groundite: Terra/Fantasma, Unseen Fist), mais Klinklang, Magnezone e
Porygon-Z. **Todos são Pokémon artificiais**: o Genesect que a Team Plasma
reconstruiu, o robô vindo do futuro, o autômato antigo de Unova, as
engrenagens, o ímã e o programa. É o time de quem quer ver até onde vai uma
máquina. *Plano:* Genesect de Scarf e Magnezone de Specs giram com U-turn e Volt
Switch até o Klinklang ter um turno para o Shift Gear. Em Doubles, o Iron Hands
abre com Fake Out e a Mega Golurk bate através de Protect.

**Falas.**
- *Chegada:* The rift let out into deep water that did not drown you. / Pale
  lights drifted overhead, trailing threads. Wherever one touched the glass
  floor, the glass glowed brighter, and cracked a little.
- *Intro:* Ah. A visitor. Good. I was running short of variables. / This place
  gives strength away. Every Pokémon here is stronger than it ought to be, and
  not one of them asks what it costs. / I have always wanted to see a Pokémon's
  full power. Here, I only have to watch. / Let us see how far yours will go.
- *Derrota:* Fascinating. Every one of your Pokémon stopped short of the edge. /
  By choice.
- *Depois:* I measured everything, and I still cannot tell you what held them
  back. / …Perhaps that is the result. / Something below us has noticed you. It
  is looking for someone to lend its strength to. / I would decline, if I were
  you. I say that as a man who would not.
- *Boss:* The lights in the water drew together into one shape. / It hung in
  front of you, weightless and patient, as if waiting to be let in.
- *Ficha do Looker:* File UB-01. Symbiont. / A scientist who would not stop
  taking notes on your Pokémon, and a creature that offers power to anyone who
  holds still. / I have filed them together. I suspect they would both find that
  flattering.

### 3.2. UB-02 Absorption — Buzzwole — Bruno

**Conceito.** Buzzwole anda por aí exibindo os músculos anormalmente inchados.
O codinome é *Absorption*: ela suga energia com a probóscide. Mundo em USUM:
Ultra Jungle.

**O fragmento.** Calor que bate na chegada. Uma copa verde onde tudo cresceu
demais (folhas maiores que portas, raízes grossas como pilares), e tudo parece
exausto. A força do lugar foi tirada de alguém.

**O treinador.** Bruno, o homem que construiu a própria força treinando todo dia.

**O eco.** O fragmento faz o Bruno acordar mais forte do que foi dormir, sem
treinar, e ele detesta isso: força que ninguém conquistou tem de ter vindo de
algum lugar. É o único eco que rejeita o conceito de frente. Depois da luta, a
selva toma de volta o que tinha dado a ele, e ele acha bom. O aviso vira a lição
contrária à da Buzzwole: ela vai se exibir antes de atacar, e o jogador não deve
se impressionar.

**Time (R11).** Lendário **Marshadow**, semi-lendário **Urshifu** (Single
Strike), Mega **Heracross** (Bugtite: Skill Link), mais Machamp, Hitmontop e
Hitmonlee. O Spectral Thief do Marshadow **rouba os aumentos do adversário**: é o
conceito de Absorption na mão do Bruno, virado contra quem se fortalece de
graça. O Urshifu ganhou a forma que tem treinando numa torre: força conquistada.
*Plano:* Bulk Up e prioridade (Mach Punch, Sucker Punch, Shadow Sneak). Em
Doubles, o Hitmontop abre com Intimidate e Fake Out, e o Urshifu atravessa
Protect. Marshadow e Urshifu cobrem os pontos fracos do Lutador (Fantasma e
Psíquico).

**Falas.**
- *Chegada:* Heat hit you the moment you stepped through. / Under a green canopy,
  everything had grown too large. Leaves wider than doors, roots as thick as
  pillars. / And every one of them looked tired.
- *Intro:* I have trained every day of my life. / Here, I wake up stronger than I
  was when I went to sleep. Without lifting a finger. / I do not like it.
  Strength nobody earned has to come from somewhere. / Show me yours. I want to
  know if it is real!
- *Derrota:* Hoo hah! …Yes. That was earned.
- *Depois:* Did you feel it? The jungle took something back just now. From me. /
  Good. It was never mine. / The one that feeds on all this is close. It will
  show you its strength before it ever uses it. / Do not be impressed. Hit it.
- *Boss:* The canopy shook. / Something landed in the clearing, flexed once, and
  waited to be admired.
- *Ficha do Looker:* File UB-02. Absorption. / A creature that takes strength from
  others and shows it off, and a man who built his own and would not accept a
  gift. / I have underlined the man. Twice.

### 3.3. UB-02 Beauty — Pheromosa — Elesa

**Conceito.** Pheromosa se recusa a tocar em qualquer coisa, talvez por sentir
alguma impureza neste mundo. Emite um feromônio que deixa quem a encara confuso,
como se atingido pela beleza dela. Mundo em USUM: Ultra Desert.

**O fragmento.** Areia branca e uma passarela reta, branca, iluminada por baixo.
Nada deixa marca: quando o jogador olha para trás, as próprias pegadas já
sumiram. Leitura visual: passarela de desfile no deserto.

**O treinador.** Elesa, líder de Nimbasa e modelo famosa.

**O eco.** No fragmento, a Elesa é admirada por todos e ninguém nunca chega até
ela, e ela já não sabe se isso ainda é plateia. O "não dê nem um passo" é o
conceito falando pela boca dela. A vitória do jogador é o contrário da Pheromosa:
ele não estava olhando para ela, estava olhando para os próprios Pokémon. O aviso
é sobre o feromônio: quem ela olha esquece por que veio.

**Time (R11).** Lendário **Miraidon**, semi-lendário **Zapdos**, Mega
**Eelektross** (Electrite: Eelevate), mais Zebstrika, Galvantula e Emolga. O
Miraidon é o palco: acende o Electric Terrain ao entrar (Hadron Engine), e todo
golpe elétrico do time sobe. *Plano:* o Zapdos põe Tailwind, a Galvantula arma
Sticky Web e a Emolga prende com Encore e Light Screen. Zapdos e Emolga voam, e o
Eelektross flutua, então o time não cai de uma vez para um golpe de Terra.

**Falas.**
- *Chegada:* White sand, and a straight white path across it, lit from below. /
  Nothing marked it. When you looked back, your own footprints were already gone.
- *Intro:* Stop right there. Not one step closer. / Everyone in this place looks at
  me, and no one ever reaches me. I used to call that an audience. / Battle me
  from where you're standing. Dazzle me, if you can.
- *Derrota:* …You weren't looking at me at all. You were looking at your Pokémon. /
  How rude. How refreshing.
- *Depois:* The sand takes every footprint away. Yours are still there. I checked. /
  There's something out there that won't let anything touch it. Everyone it looks
  at forgets why they came. / Remember why you came.
- *Boss:* Someone was already standing at the end of the path. Perfectly still.
  Perfectly clean. / For a moment, you forgot what you were doing there.
- *Ficha do Looker:* File UB-02. Beauty. / You described the creature, and I wrote
  down the word "lovely." / I have crossed it out. It is still perfectly legible.
  That, I think, is the whole report.

### 3.4. UB-03 Lighting — Xurkitree — Volkner

**Conceito.** A Pokédex conta que a Xurkitree invadiu uma usina elétrica, e por
isso se acha que ela se alimenta de eletricidade. Mundo em USUM: Ultra Plant.

**O fragmento.** Uma cidade de torres e cabos sob um céu sem estrelas. Todas as
janelas apagadas, menos uma, lá no alto, queimando em branco. Todos os cabos
correm até ela.

**O treinador.** Volkner, líder de Sunyshore. Em Platinum, entediado e sem
desafiantes à altura, ele reformou os equipamentos elétricos do ginásio e a
cidade ficou sem luz.

**O eco.** O Volkner vive a própria história com o volume no máximo: a cidade
inteira apagou para aquela sala continuar acesa, e ele repete para si que é uma
troca justa por uma boa batalha. Enquanto os dois lutam, as luzes lá fora voltam
pela primeira vez. A luta que ele esperava é o que o conceito não consegue
engolir. O aviso: a coisa descobriu para onde foi a energia.

**Time (R11).** Lendário **Zekrom**, semi-lendário **Raikou**, Mega **Raichu**
(Electrite: Mega Raichu X, com Electric Surge), mais Luxray, Electivire e
Ambipom. Raichu, Ambipom, Electivire e Luxray são do time dele em Platinum; o
Raikou é o trovão de Johto. *Plano:* um gerador. A Mega Raichu X liga o terreno
ao megaevoluir, o Zekrom sobe com Dragon Dance e o Raikou de Specs gira com Volt
Switch. Em Doubles, dois Fake Outs (Raichu e Ambipom) e o Intimidate do Luxray.

**Falas.**
- *Chegada:* A city of towers and cables, under a sky with no stars. / Every window
  was dark but one, high up, burning white. All the cables ran toward it.
- *Intro:* Took you long enough. / Every light in this city went out so this one
  room could stay on. I keep telling myself that's a fair trade for a decent
  battle. / So. Are you worth the blackout?
- *Derrota:* Ha! There it is. That's the spark I've been waiting for.
- *Depois:* Funny. The lights outside came back on while we fought. First time
  ever. / Something's pulling on the lines again. Harder. It's figured out where
  all the power went. / Go on. I'll keep the lights on for you.
- *Boss:* Every cable in the room went taut at once. / The window flickered, and
  something that was mostly wire stood up in the light.
- *Ficha do Looker:* File UB-03. Lighting. / A city kept in the dark so that one
  room could stay lit, and one bored man could have a good fight. / The old file
  says the creature once emptied a power plant. I find I am not sure which of the
  two I am filing.

### 3.5. UB-04 Blaster — Celesteela — Steven

**Conceito.** Celesteela tem o corpo entre um ônibus espacial e um broto de
bambu. Testemunhas a viram incendiar uma floresta expelindo gás pelos dois
braços. Mundo em USUM: Ultra Crater.

**O fragmento.** Uma cratera sob um céu lotado de estrelas. Brotos de aço altos
como bambu, queimados de preto na base, todos apontando para cima.

**O treinador.** Steven, colecionador de pedras raras, especialista em Aço, e o
homem do Space Center de Mossdeep e do meteoro do Delta Episode.

**O eco.** O Steven passou a vida juntando pedras que caíram do céu. Num lugar
onde tudo só sobe, ele não achou nenhuma. É o eco mais melancólico: ele não luta
por desafio, luta porque alguém enfim "ficou tempo suficiente". A vitória do
jogador é a resposta que ele procurava: algo com os pés no chão também alcança
essa altura. O aviso vem da Pokédex: fique longe dos braços.

**Time (R11).** Lendário **Deoxys**, semi-lendário **Jirachi**, Mega
**Metagross** (Steeltite, a pedra do Steven neste hack), mais Skarmory, Claydol
e Cradily. **Tudo veio do céu ou da rocha antiga**: o Deoxys chegou num meteoro,
o Jirachi acorda com um cometa, o Cradily é fóssil e o Claydol é argila antiga.
É a coleção do Steven. *Plano:* Deoxys e Claydol armam Stealth Rock e as telas,
o Skarmory espalha Spikes e põe Tailwind em Doubles, e a Mega Metagross limpa.

**Falas.**
- *Chegada:* A crater under a sky crowded with stars. / Tall steel shoots rose
  from the floor like bamboo, scorched black at the base, all pointing straight
  up.
- *Intro:* Look up. Nothing in this place ever falls. / I have walked the whole
  crater, and I have not found a single stone that came down. / Everything here
  only leaves. / …Forgive me. A battle, then. I have been hoping someone would
  stay long enough.
- *Derrota:* So that's it. Something that keeps its feet on the ground can still
  reach this high.
- *Depois:* I'll stay a little longer. I would like to find one stone here that
  fell. / Something is warming up past the towers. You can feel the heat in the
  steel. / Stand well away from its arms.
- *Boss:* The ground shook, and one of the steel shoots began to rise. / It was not
  a tower. It had arms, and both of them were glowing.
- *Ficha do Looker:* File UB-04. Blaster. / A crater where nothing falls, and a
  collector of fallen stones who could not find a single one. / I have closed
  this file very gently. I cannot tell you why.

### 3.6. UB-04 Blade — Kartana — Ramos

**Conceito.** Kartana é um origami: corpo fino como papel, afiado como espada.
Foi vista derrubando uma torre de aço com um golpe só. Mundo em USUM: Ultra
Forest.

**O fragmento.** Uma floresta de árvores brancas, todas dobradas. Galhos vincados
em ângulos limpos, folhas cortadas no mesmo formato. Nada cresce: tudo foi podado.

**O treinador.** Ramos, líder de Coumarine, jardineiro que leva a mesma tesoura
de poda há trinta anos e chama o jogador de "sprout".

**O eco.** Um jardineiro num lugar sem nada para podar, porque tudo já foi
cortado, e por isso nada cresce. O eco é o mais sábio: ele sabe exatamente o que
há de errado e pede ao jogador que mostre "algo que cresce". O aviso é a lição
inteira do jardinagem: nada cresce sem corte, mas nada cresce só de corte, e a
coisa lá dentro só aprendeu a primeira metade.

**Time (R11).** Lendário **Xerneas**, semi-lendário **Celebi**, Mega
**Victreebel** (Poisontite: Innards Out), mais Gogoat, Jumpluff e Ferrothorn. O
Xerneas dá vida e vira árvore quando descansa; o Celebi é o guardião das
florestas. São "algo que cresce", que é o que o eco pede. *Plano:* um jardim
de desgaste. Leech Seed (Celebi, Jumpluff, Ferrothorn), Sleep Powder e Spikes; o
Xerneas usa Geomancy no primeiro turno com Power Herb; a Mega Victreebel pune
quem a derruba. Em Doubles, o Jumpluff põe Tailwind.

**Falas.**
- *Chegada:* A forest of white trees, every one of them folded. / Branches creased
  at clean angles. Leaves cut to the same shape. Nothing was growing. Everything
  had been trimmed.
- *Intro:* Hoho! A sprout, all the way out here. / Thirty years I've carried these
  shears, and I've never been anywhere with nothing left to prune. / Every tree
  here is cut already. Clean as a folded letter. And not one of them is growing. /
  Show an old man something that grows!
- *Derrota:* Hohoho! Now that is a sprout with roots.
- *Depois:* Nothing grows without a little cutting, sprout. But nothing grows from
  cutting alone, either. / Mind your step past the trees. Something in there only
  ever learned the first half.
- *Boss:* A leaf came loose from the nearest branch and did not fall. / It stood up
  and unfolded one arm, and the tree behind it slid apart in two clean pieces.
- *Ficha do Looker:* File UB-04. Blade. / A gardener in a forest where nothing
  grows, and a creature as thin as paper that once cut down a steel tower. / I
  have put a paperweight on this file. It seemed only sensible.

### 3.7. UB-05 Glutton — Guzzlord — Guzma

**Conceito.** Guzzlord já devorou montanhas e engoliu prédios inteiros, e parece
estar sempre comendo. Mundo em USUM: Ultra Ruin, uma cidade em ruínas.

**O fragmento.** Uma cidade, ou o que sobrou dela. Metade dos prédios não caiu:
sumiu, como se tivesse sido mordida. Longe, alguma coisa ainda mastiga.

**O treinador.** Guzma, chefe da Team Skull. Foi aprendiz do Hala junto com o
Kukui, perdeu para o Kukui, teve negado o posto de Trial Captain e fez da
destruição a própria identidade.

**O eco.** O Guzma achou um lugar todo destruído e concluiu que só podia ser dele,
até descobrir que outra coisa chegou antes. É o conceito da fome virado para
dentro: ele joga tudo o que tem e nunca é suficiente. A lembrança do Kukui ("ganhar
não é o ponto") é a única ponte com o elenco de SoulGold, e passa como memória,
não como encontro. O aviso é o que ele nunca soube fazer: "mostra pra ela como é
ter o bastante".

**Time (R11).** Lendário **Yveltal**, o Pokémon da destruição; semi-lendário
**Buzzwole**, a outra UB de Inseto, que vive de exibir força, o espelho do
Guzma; Mega **Golisopod** (Bugtite: Inseto/Aço), o ás dele. Mais Ariados, Scizor
e Vikavolt, do time dele em Sun/Moon. *Plano:* destruição sem freio. O Ariados
lança Sticky Web e Toxic Spikes, o Yveltal bate com Dark Aura e Life Orb, Scizor
e Vikavolt entram de Choice, e o Buzzwole sobe com Bulk Up.

**Falas.**
- *Chegada:* A city, or what was left of one. / Half the buildings were gone. Not
  fallen. Missing, as if bitten off. / Somewhere far away, something was still
  chewing.
- *Intro:* See this street? Every building, wrecked. Every single one. / Folks
  always said I break everything I touch. So I figured a place like this had to
  be mine. / Turns out somethin' else got here first. And it's still hungry. / So
  what are YOU hungry for, huh?!
- *Derrota:* …Again. I throw everything I got at it, and it's never enough. Never.
- *Depois:* Kukui used to say winnin' ain't the point. Used to drive me nuts. /
  …Tch. Forget it. / That thing's on the next block, eatin' whatever's left. It
  don't get full. It don't ever get full. / Go on. Go show it what enough looks
  like.
- *Boss:* The chewing stopped. / A mouth that was most of a body turned toward you,
  and the street in front of it was simply not there anymore.
- *Ficha do Looker:* File UB-05. Glutton. / A city eaten down to the street, and a
  young man sitting in it, insisting he had done it himself. / He had not. I have
  written that down for him, in case he ever asks.

### 3.8. UB Adhesive — Poipole — Zossie

**Conceito.** O filhote das Ultra Beasts, dado ao jogador pela Ultra Recon Squad
em USUM. O codinome é *Adhesive*: o veneno dele gruda.

**O fragmento.** Uma sala pequena, clara, sem cantos. Luzes macias perto do teto.
Quando uma encosta na manga do jogador, fica grudada um instante antes de soltar.
É o único fragmento sem ameaça, e a expedição mais leve do loop.

**O treinador.** Zossie, a mais nova e mais entusiasmada da Ultra Recon Squad,
vinda de Ultra Megalopolis, o mundo que perdeu a luz.

**O eco.** Tudo gruda ali, e a Zossie grudou também. Ela é o conceito sem medo
nenhum: quer amigos, quer aprovação, inventa uma regra na hora para o jogador não
ir embora. O depois explica o conceito pela história dela: de onde ela vem não
havia luz, e quando aparece algo que brilha, dá vontade de grudar. O aviso é um
pedido: "seja bonzinho com ele".

**Time (R11).** Lendário **Magearna**, feita à mão e com um coração artificial
(Soul-Heart); semi-lendário **Mew**, curioso e brincalhão como o Poipole; Mega
**Clefable** (Fairytite: Fada/Voador, Magic Bounce). Mais Mimikyu, Ribombee e
Goodra. Tudo gruda ou cuida (Sticky Web, Gooey, Follow Me), e o Mimikyu só quer
ser amado, como ela. *Plano:* apoio em Doubles. A Clefable puxa os golpes com
Follow Me, o Mew põe Tailwind e queima com Will-O-Wisp, o Ribombee arma a teia,
e a Magearna fica mais forte a cada Pokémon que cai.

**Falas.**
- *Chegada:* A small bright room with no corners. / Soft lights floated near the
  ceiling. When one brushed your sleeve, it stayed there a moment before letting
  go.
- *Intro:* Oh! Oh! Someone came! Hi! Hello! / Everything in here sticks together.
  The lights, the floor, the little ones… And now you! / You're not leaving till we
  battle. That's the rule. I just made it up!
- *Derrota:* Aww… But that was fun, right? You had fun? Say you had fun!
- *Depois:* Can I tell you a secret? Where I'm from, there wasn't any light. None! /
  So when something bright shows up, you kind of want to stick to it. / There's a
  little one over there who wants to stick to you. Be nice to it, okay? Promise!
- *Boss:* One of the lights drifted down from the ceiling and landed in front of
  you. / It had a face, and it was very, very curious about yours.
- *Ficha do Looker:* File UB Adhesive. / No harm done. No damage. One very small
  creature that followed you all the way to the door. / It is the shortest file I
  have. I have read it four times.

### 3.9. UB Stinger — Naganadel — Soliera

**Conceito.** Naganadel guarda centenas de litros de líquido venenoso no corpo e
voa rápido demais para acompanhar. É o Poipole crescido.

**O fragmento.** O topo de uma torre, muito acima de uma cidade de luzes (a Megalo
Tower lembrada de longe). Vento de todos os lados. Riscos longos e retos cortados
no telhado, todos apontando para o mesmo ponto.

**O treinador.** Soliera, a integrante da Ultra Recon Squad focada na missão
acima de tudo, e quem entrega o Poipole ao jogador em Ultra Sun.

**O eco.** O conceito vira ordem: um objetivo, um golpe, e certeiro. Ela trata o
jogador como obstáculo, não como inimigo. A derrota é anotada ("…Noted."), porque
é assim que ela recebe um fracasso. O depois é a única vez que ela fala de si: de
onde ela vem, entregaram um pequeno a alguém que ajudou, e ela nunca soube no que
ele se tornou. Talvez seja aquilo que circula a torre.

**Time (R11).** Lendário **Eternatus**, Veneno/Dragão como o Naganadel e
chegado do espaço; semi-lendário **Latios**, o jato do céu; Mega **Beedrill**
(Bugtite: Adaptability), o ferrão. Mais Crobat, Dragapult e Drapion. *Plano:*
velocidade e um golpe só. O Crobat abre com Tailwind e Taunt, e a Mega Beedrill
e o Dragapult batem antes de tudo. O Fell Stinger do Beedrill é o golpe que
termina e ainda sobe o ataque. O Drapion arma Toxic Spikes e o Eternatus fecha
com Dynamax Cannon e Recover.

**Falas.**
- *Chegada:* The top of a tower, far above a city of lights. / The wind came from
  every side at once. Long straight scars were cut into the roof, all of them
  pointing at the same spot.
- *Intro:* Stop. State your purpose. / …No. It does not matter. / I was given one
  objective in this place. Strike once, and strike true. / You are standing where
  my objective is. Prepare yourself.
- *Derrota:* One strike was not enough. …Noted.
- *Depois:* Where I come from, we gave a small one away. To someone who helped
  us. / I never learned what it grew into. / If what is circling this tower is the
  answer, do not look away from the needle. Not once.
- *Boss:* Something passed overhead too fast to see. Then again, lower. / The
  third time, it stopped in the air in front of you, and pointed.
- *Ficha do Looker:* File UB Stinger. / You tell me it carries enough poison to
  fill a bathtub, and flies faster than you could follow. / I have moved my desk
  slightly further from the window. For no reason.

### 3.10. UB Assembly — Stakataka — Byron

**Conceito.** Parece feita de pedras empilhadas, mas cada "pedra" é uma forma de
vida separada. Muros que começaram a andar e atacar. Segundo o Phyco, uma
Stakataka reúne quase 150 dessas criaturas.

**O fragmento.** Uma pedreira de pedra cinza, com muros em todas as direções. O
jogador tinha certeza de que o caminho atrás dele estava aberto um instante antes.

**O treinador.** Byron, líder de Canalave, minerador, "o homem de corpo de aço",
pai do Roark, e dono de um Bastiodon, ele mesmo um muro vivo.

**O eco.** O Byron é o único que admira o conceito. Ele entende de pedra e sabe
que nenhuma pedra ali é pedra: cada tijolo está vivo e escolheu segurar o
seguinte. Para ele isso é família e ofício. A lembrança do filho é a memória dele.
O aviso é respeito, não medo: eles se seguram porque escolheram, e não vão
desmontar só porque o jogador pediu.

**Time (R11).** Lendário **Zamazenta** (com o Rusted Shield, a forma Crowned: o
escudo), semi-lendário **Registeel**, Mega **Steelix** (Steeltite: Aço/Terra,
Sand Force), mais Bastiodon, Bronzong e Tyranitar. O muro, peça por peça.
*Plano:* areia e Trick Room. O Tyranitar chama a tempestade de areia, o Bronzong
inverte a ordem dos turnos, e os lentos batem primeiro: a Mega Steelix na
areia, Bastiodon e Zamazenta com Iron Defense e Body Press, o Registeel com
Stealth Rock e o Bastiodon com Wide Guard em Doubles. Em Singles, o mesmo time
joga como parede.

**Falas.**
- *Chegada:* A quarry of grey stone, with walls in every direction. / You were sure
  the way behind you had been open a moment ago.
- *Intro:* Hah! Another one wandered into the quarry! Mind the walls, youngster.
  They move. / I dig for a living. I know stone. And not one stone in this place
  is stone. / Every brick is alive, and every one of them decided to hold up the
  next. / That's a wall worth respecting! Now let's see about you!
- *Derrota:* Hah! Good! A wall's only as good as whatever's hitting it!
- *Depois:* My son would love this place. He'd dig the whole thing up, the fool. /
  Listen. There's something stacking itself behind that wall. A lot of
  somethings. / They hold together because they chose to. Don't expect them to
  fall apart because you asked.
- *Boss:* The wall ahead shifted, brick by brick, and stood up on four thin legs. /
  Every stone in it turned to look at you.
- *Ficha do Looker:* File UB Assembly. / One creature that is really a hundred and
  fifty, all holding each other up. / I have been told it is a threat. I have
  filed it under threats. I keep wanting to move it.

### 3.11. UB Burst — Blacephalon — Fantina

**Conceito.** Blacephalon baixa a guarda do alvo com o andar esquisito, detona a
própria cabeça sem aviso e rouba a vitalidade dele. É um palhaço de fogos de
artifício.

**O fragmento.** Um teatro vazio, com cada poltrona ocupada por uma sombra. Fogos
estouram no alto sem som. A cada estouro, as sombras nas poltronas ficam mais
fracas.

**O treinador.** Fantina, líder de Hearthome, "a dançarina sedutora e cheia de
alma", estrela de concursos, com Pokémon Fantasma.

**O eco.** Todo dia o show é magnífico, e todo dia a plateia está um pouco mais
fraca. A Fantina começou a se perguntar quem paga pelas luzes, e em seguida se
proíbe de pensar nisso e chama o jogador para dançar. A vitória dele é o
contrário do conceito: ele assistiu ao show inteiro e não deu nada em troca. O
aviso: o último ato não é dela, vai ser encantador, e o jogador não deve se
inclinar para ver.

**Time (R11).** Lendário **Hoopa**, o gênio travesso que tira coisas dos anéis,
um mágico de palco; semi-lendário **Meloetta**, a cantora que passa para a forma
de dança com Relic Song; Mega **Chandelure** (Ghostite: Fantasma/Fogo como a
Blacephalon, Infiltrator). Mais **Mismagius** (o ás dela em Diamond/Pearl),
Oricorio-Sensu e Drifblim. *Plano:* o espetáculo. O Drifblim põe Tailwind, o
Oricorio-Sensu (Dancer) copia toda dança do campo em Doubles, a Meloetta dança,
e Mismagius e Hoopa atacam. A fraqueza a Sombrio e Fantasma é o risco do número.

**Falas.**
- *Chegada:* An empty theatre, every seat filled with shadow. / Fireworks burst
  overhead without a sound. Each time one went off, the shadows in the seats grew
  fainter.
- *Intro:* Bonsoir! Ah, enfin! Someone in the seats who is still breathing! / Every
  night here, the show is magnifique. Fireworks, applause… / And every night, the
  audience is a little fainter. I have begun to wonder who pays for the lights. /
  Non, non! No more thinking! Dance with me!
- *Derrota:* Bravo! Bravo! You took the whole show and gave nothing away!
- *Depois:* The final act is not mine. It never was. / When the curtain goes up out
  there, it will be charming. It will make you want to lean in. / Do not lean in,
  mon ami. Whatever you do.
- *Boss:* The curtain rose on an empty stage. / Something walked out with a strange,
  careless step. It bowed deeply, and its head began to glow.
- *Ficha do Looker:* File UB Burst. / A performer who charms its audience, blows its
  own head off, and takes their strength while they clap. / I have been to theatre
  like that. I did not know it was a species.

---

## 4. Como isso encaixa no Daily

Isto é o que este documento entrega às regras do Daily; não é o Daily.

1. **O sorteio do dia escolhe o lendário** (R15, `dailySeed`). Quando sai uma
   Ultra Beast, o destino é o fragmento dela, e o **campeão** é o eco deste
   documento. As 11 UBs não têm método de obtenção fora do Nexus
   ([`POOL_LENDARIOS.md`](POOL_LENDARIOS.md)), então pela R1 entram no sorteio
   desde o começo.
2. **Chegada** (`_Arrival`) ao entrar no fragmento. Uma vez por tentativa; na
   reentrada do mesmo dia (R3) pode ser pulada, porque o jogador já viu.
3. **Quatro salas de três teleportes** (R5.1), com os treinadores dos pools.
4. **O campeão:** `_Intro` → batalha → `_Defeat` → `_After`. Na reentrada
   depois de já vencê-lo, nenhuma fala toca (R3: quem já foi vencido não luta de
   novo).
5. **Boss:** `_Boss` e a boss battle contra a Ultra Beast (R6), capturável, com
   3 IVs perfeitos (R8). UBs são semi-lendárias (R10), e o jogador pode levar
   uma no time depois.
6. **No altar:** o Looker diz a `_LookerFile` da UB capturada naquele dia. Liga
   no bit de progresso 6 da `VAR_NEXUS_DAILY` ("lendário capturado", R15), sem
   flag nova se a ficha puder tocar toda vez.

**Nível:** nenhum. Pela R2, campeão e boss escalam para o maior nível do time do
jogador. O `Level: 100` do `.party` é só teto para o scaler.

**Singles e Doubles (R10):** cada plano de time foi escrito para os dois
formatos (§3, "Plano"). O `Double Battle:` do `.party` marca o formato em que o
time brilha quando a opção Battle Format está em Default: **Yes** para Elesa
(Tailwind + terreno), Zossie (Follow Me) e Byron (Trick Room); **No** para os
outros oito.

---

## 5. Implementação

### 5.1. Treinadores e flags

- **Cada campeão é um `TRAINER_NEXUS_*` próprio**, mesmo quem já tem batalha na
  campanha (Bruno, Steven). A flag de treinador é `TRAINER_FLAGS_START + id`
  (`include/constants/flags.h`), então cada luta do Nexus tem a sua flag
  exclusiva, separada da campanha. O Daily não depende dela para saber quem já
  foi vencido (isso é a `VAR_NEXUS_DAILY`, R15); a luta roda com a flag
  limpa a cada tentativa.
- **Onde cabem os 11 IDs.** O jogo está no teto: `TRAINERS_COUNT` =
  `MAX_TRAINERS_COUNT` = 1164 (`include/constants/opponents.h`). E os IDs
  1056–1163 têm a faixa de flag reaproveitada por `RECLAIMED_TRAINER_FLAGS`
  (README das fichas), então **não servem**. Subir o `MAX_TRAINERS_COUNT` empurra
  o bloco `SYSTEM_FLAGS`, que vem logo depois da faixa de treinador. O caminho
  mais barato é **reaproveitar IDs aposentados na limpeza, abaixo de 1056**, que
  as fichas já listam. Decisão do autor (§6).
- Terminar com `catalogar-flags`, como todo trabalho que mexe em flag.

### 5.2. Times

Os 11 times estão em [`ULTRA_BEASTS.party`](ULTRA_BEASTS.party), prontos para
colar no `src/data/trainers.party` quando os IDs existirem. Conferido em
26/09/2026, por script:

- **R11:** cada time tem **exatamente** 1 lendário, 1 semi-lendário e 1 Mega. A
  categoria vem das flags da espécie (`isRestrictedLegendary`,
  `isSubLegendary`, `isUltraBeast`, `isParadox`, `isMythical`) e da tabela de
  míticos do R10 (Genesect, Marshadow, Deoxys, Magearna e Hoopa contam como
  lendários; Celebi, Jirachi, Mew e Meloetta, como semi). A Mega é a espécie
  segurando a pedra que `src/data/pokemon/form_change_tables.h` liga a ela.
- **Megas por pedra de tipo.** Neste hack a Mega sai da pedra do **tipo**, não da
  pedra da espécie: Steeltite (Metagross, Steelix), Electrite (Eelektross, Raichu
  X), Bugtite (Heracross, Golisopod, Beedrill), Poisontite (Victreebel),
  Fairytite (Clefable), Ghostite (Chandelure), Groundite (Golurk). Várias têm
  habilidade própria do hack, e os planos contam com elas: Mega Raichu X com
  Electric Surge, Mega Steelix com Sand Force, Mega Golurk com Unseen Fist, Mega
  Victreebel com Innards Out.
- **R13:** 31 IVs e 252 EVs em todos os stats, em todos os 66 Pokémon.
- `cpp | tools/trainerproc` sem erro, e todas as constantes geradas existem
  (espécies, golpes, itens, habilidades, naturezas, classes, músicas), menos os
  9 `TRAINER_PIC_FRONT_*` novos (§5.3).
- Todo golpe está no learnset da espécie (level-up, ovo com as pré-evoluções e
  `all_learnables.json`). O Zamazenta usa **Iron Head**, que vira Behemoth Bash
  na forma Crowned.

### 5.3. Assets

| Personagem | Sprite de batalha | Sprite no mapa | Plaquinha de fala |
|---|---|---|---|
| Colress | novo | novo | `SP_NAME_COLRESS` |
| Bruno | existe | existe | `SP_NAME_BRUNO` |
| Elesa | novo | novo | `SP_NAME_ELESA` |
| Volkner | novo | novo | `SP_NAME_VOLKNER` |
| Steven | existe | existe | `SP_NAME_STEVEN` |
| Ramos | novo | novo | `SP_NAME_RAMOS` |
| Guzma | novo | novo | `SP_NAME_GUZMA` |
| Zossie | novo | novo | `SP_NAME_ZOSSIE` |
| Soliera | novo | novo | `SP_NAME_SOLIERA` |
| Byron | novo | novo | `SP_NAME_BYRON` |
| Fantina | novo | novo | `SP_NAME_FANTINA` |

- **Plaquinhas:** 11 nomes novos, acrescentados **no fim** dos três arquivos da
  skill `nomear-falante`, depois de `SP_NAME_KURT`. Todos cabem nos 64 px.
- **Classes:** usei classes que já existem. A do Guzma (`Expert`) e a da Zossie e
  da Soliera (`Pkmn Ranger`) são provisórias; "Team Skull Boss" e "Ultra Recon"
  pedem classe nova se o autor quiser o título certo na tela de batalha.
- **Mapas:** a seção "O fragmento" de cada UB serve de briefing para a skill
  `prototipo-de-mapa`, se o Daily usar um mapa por destino.

### 5.4. Textos

As 66 falas estão em [`ULTRA_BEASTS_TEXTS.inc`](ULTRA_BEASTS_TEXTS.inc), com
rótulos `Nexus_Text_<Codinome>_<Parte>`. Conferido:

- `medir_linha.py`: nenhuma linha passa de 208 px.
- Todos os caracteres estão no `charmap.txt` (`…` e aspas curvas incluídas; sem
  traço longo).
- O maior texto tem bem menos de 600 bytes, longe do teto de 1000 do
  `gStringVar4`.
- `_Intro` e `_Defeat` são textos de `trainerbattle` e não levam `{SPEAKER}` (a
  plaquinha vem do treinador). `_After` e `_LookerFile` levam, e são os que pedem
  os `SP_NAME_*` novos.

---

## 6. Decisões para o autor

1. **Os onze campeões** (§2). Cada linha da tabela é independente: trocar uma
   não mexe nas outras.
2. **O eco como regra do Nexus** (§1). Se aprovado, entra no design §10 e vale
   também para os fragmentos de lendários.
3. **As fichas do Looker** (onze, uma por UB capturada). A proposta é tocar toda
   vez que o jogador capturar aquela UB no dia, sem flag nova.
4. **Onde cabem os 11 IDs** (§5.1): reaproveitar IDs aposentados abaixo de 1056
   ou subir o `MAX_TRAINERS_COUNT`.
5. **Classes novas** para Guzma e Ultra Recon Squad (§5.3).

---

## 7. Fontes consultadas (26/09/2026)

A Bulbapedia está bloqueada pela rede deste ambiente; as informações vieram de
busca, cruzando as fontes abaixo.

- Codinomes das UBs: [Pokémon Wiki — Ultra Beast](https://pokemon.fandom.com/wiki/Ultra_Beast), [PokéJungle — Ultra Beast list](https://pokejungle.net/sun-moon/ultra-beast-list/).
- Mundos de cada UB em USUM: [Serebii — Ultra Space Wilds](https://www.serebii.net/pokearth/alola/ultraspacewilds.shtml), [Bogleech — The Ultra Wormhole Worlds](https://bogleech.com/pokemon/ultraspace).
- Pokédex: [Nihilego](https://www.pokemon.com/us/pokedex/nihilego), [Buzzwole](https://www.pokemon.com/us/pokedex/buzzwole), [Pheromosa](https://www.pokemon.com/us/pokedex/pheromosa), [Xurkitree](https://www.pokemon.com/us/pokedex/xurkitree), [Celesteela](https://www.pokemon.com/us/pokedex/celesteela), [Kartana](https://www.pokemon.com/us/pokedex/kartana), [Naganadel](https://www.pokemon.com/us/pokedex/naganadel), [Stakataka](https://www.pokemon.com/us/pokedex/stakataka), [Blacephalon](https://www.pokemon.com/us/pokedex/blacephalon), [Guzzlord (Pokémon Database)](https://pokemondb.net/pokedex/guzzlord).
- Ultra Recon Squad e o Poipole: [Serebii — Ultra Recon Squad](https://www.serebii.net/ultrasunultramoon/ultrareconsquad.shtml), [Gamer Guides — Ultra Megapolis](https://www.gamerguides.com/pokemon-ultra-sun-moon/guide/walkthrough/poni-island/ultra-megapolis).
- Colress: [Serebii — Team Plasma (BW2)](https://www.serebii.net/black2white2/teamplasma.shtml).
- Volkner e o apagão de Sunyshore: [Pokémon Let's Play Wiki — Sunyshore City](https://pokemonlp.fandom.com/wiki/Appendix:Pok%C3%A9mon_Platinum_Walkthrough/Sunyshore_City).
- Ramos e a tesoura: [Pokémon Let's Play Wiki — Ramos](https://pokemonlp.fandom.com/wiki/Ramos).
- Guzma, Hala e Kukui: [Villains Wiki — Guzma](https://villains.fandom.com/wiki/Guzma).
- Elesa: [Heroes Wiki — Elesa](https://hero.fandom.com/wiki/Elesa).
- Fantina: [Nintendo of America](https://x.com/NintendoAmerica/status/1472597626579308550).
- Byron: [Nintendo of America](https://x.com/NintendoAmerica/status/1473050683607814150).
