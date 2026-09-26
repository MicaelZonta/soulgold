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
> - [`ULTRA_BEASTS_TEXTS.inc`](ULTRA_BEASTS_TEXTS.inc): as 88 falas em formato
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

**Dois registros de fala por treinador.** O mesmo treinador pode aparecer de
dois jeitos no Daily, e cada jeito tem a sua fala:

| Onde ele aparece | Registro | Sobre o quê | Rótulos |
|---|---|---|---|
| Uma das **quatro primeiras salas** (R5), em qualquer fragmento | **Genérico** | **Ele mesmo.** Quem é, o que faz, como reage a acordar num lugar que não conhece. Não cita o lugar nem a criatura do dia, porque serve para qualquer um. | `_Intro`, `_Defeat` |
| **Campeão**, a luta logo antes do lendário | **Do lendário** | **A criatura.** O que ele viu nela, pelo olhar de quem ele é. É uma reflexão, não um aviso de manual. | `_ChampionIntro`, `_ChampionDefeat`, `_ChampionAfter` |

A fala de campeão tem três batidas:

| Batida | Onde | O que faz |
|---|---|---|
| **O que ele viu** | `_ChampionIntro` | Descreve a criatura com um detalhe concreto (o que ela faz, não o nome) e diz o que isso mexe nele: o Colress vê o próprio sonho e não gosta; o Volkner reconhece a própria fome; o Steven não sabe se ela foge ou volta para casa. |
| **A resposta** | `_ChampionDefeat` | A vitória do jogador é o contrário da criatura: força que não foi tomada, um olhar que não foi capturado, algo que cresce de volta. |
| **O que fica** | `_ChampionAfter` | Uma leitura final da criatura e **uma instrução que só essa pessoa daria** ("olhe as pernas", "seja algo que volta a crescer", "não aplauda"). Termina apontando para ela. |

Depois disso, a Ultra Beast aparece (`_Boss`). De volta ao altar, o Looker
arquiva o dia (`_LookerFile`) numa fala curta que junta o campeão e a criatura na
mesma ficha. É a coleção de quem joga o Daily: onze fichas, cada uma liberada
quando aquela UB é capturada.

As falas de cada treinador (genérica e de campeão) ficam na **ficha dele**, em
`nexus/<região>/<treinador>.md`. Este documento guarda o que é do fragmento:
conceito, lugar, time, chegada, boss e ficha do Looker.

### 1.1. Regras de escrita do Nexus

Valem para todo texto de fragmento, inclusive os que ainda vão ser escritos para
lendários.

- **Ninguém provoca o jogador.** O eco não está ali para desafiar nem para
  humilhar. Ele está preso num conceito e fala disso. O tom é de estranheza,
  não de rivalidade.
- **Ninguém nomeia a criatura.** Nem o campeão, nem a narração. "Something below us",
  "that thing", "a little one". O nome só aparece na tela de batalha. O codinome
  só aparece na ficha do Looker, depois.
- **O eco não sabe que é eco.** Na fala genérica, todos acordaram num lugar que
  não conhecem e reagem do seu jeito (o Bruno treina, o Steven olha as pedras, a
  Zossie comemora que não está escuro). Nenhum conclui nada.
- **A fala genérica serve para qualquer dia.** Nada de areia, cabos, teatro ou
  criatura: ela toca em qualquer fragmento, inclusive nos de lendários.
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

**O campeão.** O Colress passou a vida tentando tirar os limites dos Pokémon, e
encontra uma criatura que faz exatamente isso, de graça, para quem ficar parado.
Ele vê o próprio sonho realizado e descobre que não gosta de assistir. A vitória
do jogador é a força que veio dos Pokémon, sem toxina nenhuma. O que fica: foi
preciso aquela criatura para ele entender para que serve um limite, e o pedido
final é o mais honesto dele: "recuse. Digo isso como alguém que teria aceitado".

**Time (R11).** Lendário **Genesect**, semi-lendário **Iron Hands**, Mega
**Golurk** (Groundite: Terra/Fantasma, Unseen Fist), mais Klinklang, Magnezone e
Porygon-Z. **Todos são Pokémon artificiais**: o Genesect que a Team Plasma
reconstruiu, o robô vindo do futuro, o autômato antigo de Unova, as
engrenagens, o ímã e o programa. É o time de quem quer ver até onde vai uma
máquina. *Plano:* Genesect de Scarf e Magnezone de Specs giram com U-turn e Volt
Switch até o Klinklang ter um turno para o Shift Gear. Em Doubles, o Iron Hands
abre com Fake Out e a Mega Golurk bate através de Protect.

**Falas do fragmento.**
- *Chegada:* The rift let out into deep water that did not drown you. / Pale lights drifted overhead, trailing threads. Wherever one touched the glass floor, the glass glowed brighter, and cracked a little.
- *Boss:* The lights in the water drew together into one shape. / It hung in front of you, weightless and patient, as if waiting to be let in.
- *Ficha do Looker:* File UB-01. Symbiont. / A scientist who spent his life trying to remove a Pokémon's limits, and a creature that removes them for free. / You tell me he asked you to refuse it. I have underlined that. I did not expect to.

**Falas do campeão** (e as genéricas, de quando Colress cai numa das quatro primeiras salas): na [ficha](unova/colress.md) dele, seções "Diálogo associado ao lendário" e "Diálogo genérico".

### 3.2. UB-02 Absorption — Buzzwole — Bruno

**Conceito.** Buzzwole anda por aí exibindo os músculos anormalmente inchados.
O codinome é *Absorption*: ela suga energia com a probóscide. Mundo em USUM:
Ultra Jungle.

**O fragmento.** Calor que bate na chegada. Uma copa verde onde tudo cresceu
demais (folhas maiores que portas, raízes grossas como pilares), e tudo parece
exausto. A força do lugar foi tirada de alguém.

**O treinador.** Bruno, o homem que construiu a própria força treinando todo dia.

**O campeão.** O Bruno observou a criatura por três dias: ela não levanta nada,
não treina, só posa e bebe a força dos outros, e ainda assim é mais forte que
qualquer lutador que ele já enfrentou. Ele não a odeia, mas se recusa a chamar
aquilo de força. A vitória do jogador é "a outra força", a que não se bebe de
ninguém. O que fica é um conselho de lutador: ela vai se exibir antes de bater,
então não olhe os músculos, olhe as pernas.

**Time (R11).** Lendário **Marshadow**, semi-lendário **Urshifu** (Single
Strike), Mega **Heracross** (Bugtite: Skill Link), mais Machamp, Hitmontop e
Hitmonlee. O Spectral Thief do Marshadow **rouba os aumentos do adversário**: é o
conceito de Absorption na mão do Bruno, virado contra quem se fortalece de
graça. O Urshifu ganhou a forma que tem treinando numa torre: força conquistada.
*Plano:* Bulk Up e prioridade (Mach Punch, Sucker Punch, Shadow Sneak). Em
Doubles, o Hitmontop abre com Intimidate e Fake Out, e o Urshifu atravessa
Protect. Marshadow e Urshifu cobrem os pontos fracos do Lutador (Fantasma e
Psíquico).

**Falas do fragmento.**
- *Chegada:* Heat hit you the moment you stepped through. / Under a green canopy, everything had grown too large. Leaves wider than doors, roots as thick as pillars. / And every one of them looked tired.
- *Boss:* The canopy shook. / Something landed in the clearing, flexed once, and waited to be admired.
- *Ficha do Looker:* File UB-02. Absorption. / A creature that drinks strength from others and then shows it off, and a man who built his own and would not call that strength. / “Look at the legs,” he told you. I have no idea what it means, and I have written it down anyway.

**Falas do campeão** (e as genéricas, de quando Bruno cai numa das quatro primeiras salas): na [ficha](kanto/bruno.md) dele, seções "Diálogo associado ao lendário" e "Diálogo genérico".

### 3.3. UB-02 Beauty — Pheromosa — Elesa

**Conceito.** Pheromosa se recusa a tocar em qualquer coisa, talvez por sentir
alguma impureza neste mundo. Emite um feromônio que deixa quem a encara confuso,
como se atingido pela beleza dela. Mundo em USUM: Ultra Desert.

**O fragmento.** Areia branca e uma passarela reta, branca, iluminada por baixo.
Nada deixa marca: quando o jogador olha para trás, as próprias pegadas já
sumiram. Leitura visual: passarela de desfile no deserto.

**O treinador.** Elesa, líder de Nimbasa e modelo famosa.

**O campeão.** A Elesa só viu a criatura de longe, porque ela não deixa nada
chegar perto: move-se como a última coisa limpa do mundo e olha todo o resto como
uma mancha. Todo mundo para e encara, e a Elesa conhece esse olhar do outro lado,
de uma carreira inteira. A vitória do jogador: ele nunca encarou, estava ocupado
lutando. O que fica: ser admirado não é ser amado, é mais solitário, e a criatura
acha que nunca ter sido tocada é perfeição. "Vá mostrar o que ela está perdendo.
Suje as mãos."

**Time (R11).** Lendário **Miraidon**, semi-lendário **Zapdos**, Mega
**Eelektross** (Electrite: Eelevate), mais Zebstrika, Galvantula e Emolga. O
Miraidon é o palco: acende o Electric Terrain ao entrar (Hadron Engine), e todo
golpe elétrico do time sobe. *Plano:* o Zapdos põe Tailwind, a Galvantula arma
Sticky Web e a Emolga prende com Encore e Light Screen. Zapdos e Emolga voam, e o
Eelektross flutua, então o time não cai de uma vez para um golpe de Terra.

**Falas do fragmento.**
- *Chegada:* White sand, and a straight white path across it, lit from below. / Nothing marked it. When you looked back, your own footprints were already gone.
- *Boss:* Someone was already standing at the end of the path. Perfectly still. Perfectly clean. / For a moment, you forgot what you were doing there.
- *Ficha do Looker:* File UB-02. Beauty. / You described the creature, and I wrote down the word “lovely.” / I have crossed it out. It is still perfectly legible. That, I think, is the whole report.

**Falas do campeão** (e as genéricas, de quando Elesa cai numa das quatro primeiras salas): na [ficha](unova/elesa.md) dele, seções "Diálogo associado ao lendário" e "Diálogo genérico".

### 3.4. UB-03 Lighting — Xurkitree — Volkner

**Conceito.** A Pokédex conta que a Xurkitree invadiu uma usina elétrica, e por
isso se acha que ela se alimenta de eletricidade. Mundo em USUM: Ultra Plant.

**O fragmento.** Uma cidade de torres e cabos sob um céu sem estrelas. Todas as
janelas apagadas, menos uma, lá no alto, queimando em branco. Todos os cabos
correm até ela.

**O treinador.** Volkner, líder de Sunyshore. Em Platinum, entediado e sem
desafiantes à altura, ele reformou os equipamentos elétricos do ginásio e a
cidade ficou sem luz.

**O campeão.** A criatura está secando a cidade rua por rua, e o Volkner queria
odiá-la, mas é o último com esse direito: ele mesmo apagou a própria cidade para
ter o que fazer. Ele se reconhece nela. A vitória do jogador é a faísca que vale
todo aquele escuro. O que fica: ela não é cruel, só está com fome e achou uma
cidade inteira para comer, e é exatamente isso que o assusta, porque ele entende.

**Time (R11).** Lendário **Zekrom**, semi-lendário **Raikou**, Mega **Raichu**
(Electrite: Mega Raichu X, com Electric Surge), mais Luxray, Electivire e
Ambipom. Raichu, Ambipom, Electivire e Luxray são do time dele em Platinum; o
Raikou é o trovão de Johto. *Plano:* um gerador. A Mega Raichu X liga o terreno
ao megaevoluir, o Zekrom sobe com Dragon Dance e o Raikou de Specs gira com Volt
Switch. Em Doubles, dois Fake Outs (Raichu e Ambipom) e o Intimidate do Luxray.

**Falas do fragmento.**
- *Chegada:* A city of towers and cables, under a sky with no stars. / Every window was dark but one, high up, burning white. All the cables ran toward it.
- *Boss:* Every cable in the room went taut at once. / The window flickered, and something that was mostly wire stood up in the light.
- *Ficha do Looker:* File UB-03. Lighting. / The old file says the creature once emptied a power plant. Your witness says he once emptied a town, for a good battle. / I find I am not sure which of the two I am filing.

**Falas do campeão** (e as genéricas, de quando Volkner cai numa das quatro primeiras salas): na [ficha](sinnoh/volkner.md) dele, seções "Diálogo associado ao lendário" e "Diálogo genérico".

### 3.5. UB-04 Blaster — Celesteela — Steven

**Conceito.** Celesteela tem o corpo entre um ônibus espacial e um broto de
bambu. Testemunhas a viram incendiar uma floresta expelindo gás pelos dois
braços. Mundo em USUM: Ultra Crater.

**O fragmento.** Uma cratera sob um céu lotado de estrelas. Brotos de aço altos
como bambu, queimados de preto na base, todos apontando para cima.

**O treinador.** Steven, colecionador de pedras raras, especialista em Aço, e o
homem do Space Center de Mossdeep e do meteoro do Delta Episode.

**O campeão.** O Steven passou a vida juntando o que o céu deixou cair, e a
criatura faz o caminho contrário: queima uma floresta para sair do chão e nunca
volta. Ele não sabe se ela está fugindo ou voltando para casa. A vitória do
jogador: os Pokémon dele ficaram com os pés no chão o tempo todo. O que fica:
não persiga algo assim; pare antes que ela parta, ou deixe partir, "as duas são
respostas". E ele fica esperando que algo lá de cima deixe cair uma pedra.

**Time (R11).** Lendário **Deoxys**, semi-lendário **Jirachi**, Mega
**Metagross** (Steeltite, a pedra do Steven neste hack), mais Skarmory, Claydol
e Cradily. **Tudo veio do céu ou da rocha antiga**: o Deoxys chegou num meteoro,
o Jirachi acorda com um cometa, o Cradily é fóssil e o Claydol é argila antiga.
É a coleção do Steven. *Plano:* Deoxys e Claydol armam Stealth Rock e as telas,
o Skarmory espalha Spikes e põe Tailwind em Doubles, e a Mega Metagross limpa.

**Falas do fragmento.**
- *Chegada:* A crater under a sky crowded with stars. / Tall steel shoots rose from the floor like bamboo, scorched black at the base, all pointing straight up.
- *Boss:* The ground shook, and one of the steel shoots began to rise. / It was not a tower. It had arms, and both of them were glowing.
- *Ficha do Looker:* File UB-04. Blaster. / A crater where nothing falls, and a collector of fallen stones waiting for one. / I have closed this file very gently. I cannot tell you why.

**Falas do campeão** (e as genéricas, de quando Steven cai numa das quatro primeiras salas): na [ficha](hoenn/steven.md) dele, seções "Diálogo associado ao lendário" e "Diálogo genérico".

### 3.6. UB-04 Blade — Kartana — Ramos

**Conceito.** Kartana é um origami: corpo fino como papel, afiado como espada.
Foi vista derrubando uma torre de aço com um golpe só. Mundo em USUM: Ultra
Forest.

**O fragmento.** Uma floresta de árvores brancas, todas dobradas. Galhos vincados
em ângulos limpos, folhas cortadas no mesmo formato. Nada cresce: tudo foi podado.

**O treinador.** Ramos, líder de Coumarine, jardineiro que leva a mesma tesoura
de poda há trinta anos e chama o jogador de "sprout".

**O campeão.** O segredo de trinta anos de tesoura: você nunca corta para ferir a
árvore, corta para ela voltar mais forte. A criatura corta melhor do que ele
jamais cortou, limpo, perfeito, até aço, e nunca deixou nada crescer de volta. A
vitória do jogador é "algo que cresce". O que fica: não tente ser mais afiado que
ela; seja algo que volta a crescer, "a única coisa que uma lâmina nunca consegue
terminar".

**Time (R11).** Lendário **Xerneas**, semi-lendário **Celebi**, Mega
**Victreebel** (Poisontite: Innards Out), mais Gogoat, Jumpluff e Ferrothorn. O
Xerneas dá vida e vira árvore quando descansa; o Celebi é o guardião das
florestas. São "algo que cresce", que é o que o eco pede. *Plano:* um jardim
de desgaste. Leech Seed (Celebi, Jumpluff, Ferrothorn), Sleep Powder e Spikes; o
Xerneas usa Geomancy no primeiro turno com Power Herb; a Mega Victreebel pune
quem a derruba. Em Doubles, o Jumpluff põe Tailwind.

**Falas do fragmento.**
- *Chegada:* A forest of white trees, every one of them folded. / Branches creased at clean angles. Leaves cut to the same shape. Nothing was growing. Everything had been trimmed.
- *Boss:* A leaf came loose from the nearest branch and did not fall. / It stood up and unfolded one arm, and the tree behind it slid apart in two clean pieces.
- *Ficha do Looker:* File UB-04. Blade. / A gardener in a forest where nothing grows, and a creature as thin as paper that once cut down a steel tower. / I have put a paperweight on this file. It seemed only sensible.

**Falas do campeão** (e as genéricas, de quando Ramos cai numa das quatro primeiras salas): na [ficha](kalos/ramos.md) dele, seções "Diálogo associado ao lendário" e "Diálogo genérico".

### 3.7. UB-05 Glutton — Guzzlord — Guzma

**Conceito.** Guzzlord já devorou montanhas e engoliu prédios inteiros, e parece
estar sempre comendo. Mundo em USUM: Ultra Ruin, uma cidade em ruínas.

**O fragmento.** Uma cidade, ou o que sobrou dela. Metade dos prédios não caiu:
sumiu, como se tivesse sido mordida. Longe, alguma coisa ainda mastiga.

**O treinador.** Guzma, chefe da Team Skull. Foi aprendiz do Hala junto com o
Kukui, perdeu para o Kukui, teve negado o posto de Trial Captain e fez da
destruição a própria identidade.

**O campeão.** O Guzma viu a boca comer um prédio, e depois o seguinte. Em casa
diziam que ele era a destruição andando em duas pernas, e ele gostava. Até ver
aquilo mastigar uma cidade inteira e continuar com fome, e não achar graça
nenhuma. A derrota é a dele de sempre ("tudo o que eu tenho, e ainda não
basta"). O que fica é o que ninguém conta: quem destrói tudo não fica satisfeito
depois, só fica parado numa bagunça maior. O Kukui disse isso uma vez, sobre ele,
e o Guzma demorou para ouvir.

**Time (R11).** Lendário **Yveltal**, o Pokémon da destruição; semi-lendário
**Buzzwole**, a outra UB de Inseto, que vive de exibir força, o espelho do
Guzma; Mega **Golisopod** (Bugtite: Inseto/Aço), o ás dele. Mais Ariados, Scizor
e Vikavolt, do time dele em Sun/Moon. *Plano:* destruição sem freio. O Ariados
lança Sticky Web e Toxic Spikes, o Yveltal bate com Dark Aura e Life Orb, Scizor
e Vikavolt entram de Choice, e o Buzzwole sobe com Bulk Up.

**Falas do fragmento.**
- *Chegada:* A city, or what was left of one. / Half the buildings were gone. Not fallen. Missing, as if bitten off. / Somewhere far away, something was still chewing.
- *Boss:* The chewing stopped. / A mouth that was most of a body turned toward you, and the street in front of it was simply not there anymore.
- *Ficha do Looker:* File UB-05. Glutton. / A city eaten down to the street, and a young man sitting in it who used to think that was what strength looked like. / He does not think so now. I have written that down for him, in case he ever asks.

**Falas do campeão** (e as genéricas, de quando Guzma cai numa das quatro primeiras salas): na [ficha](alola/guzma.md) dele, seções "Diálogo associado ao lendário" e "Diálogo genérico".

### 3.8. UB Adhesive — Poipole — Zossie

**Conceito.** O filhote das Ultra Beasts, dado ao jogador pela Ultra Recon Squad
em USUM. O codinome é *Adhesive*: o veneno dele gruda.

**O fragmento.** Uma sala pequena, clara, sem cantos. Luzes macias perto do teto.
Quando uma encosta na manga do jogador, fica grudada um instante antes de soltar.
É o único fragmento sem ameaça, e a expedição mais leve do loop.

**O treinador.** Zossie, a mais nova e mais entusiasmada da Ultra Recon Squad,
vinda de Ultra Megalopolis, o mundo que perdeu a luz.

**O campeão.** Tem um pequeno escondido nas luzes, seguindo a Zossie o dia todo.
É venenoso, a cabeça inteira é uma agulha, mas só gruda em quem ele gosta, e ele
quer ver se gosta do jogador. A vitória: "ele gostou de você!". O que fica é o
mundo dela: ficou escuro por tanto tempo que esqueceram como é quando uma coisa
pequena e brilhante só quer ficar perto. Ele vai vir dizer oi, talvez dê uma
picadinha, e ela pede que o jogador prometa ser gentil.

**Time (R11).** Lendário **Magearna**, feita à mão e com um coração artificial
(Soul-Heart); semi-lendário **Mew**, curioso e brincalhão como o Poipole; Mega
**Clefable** (Fairytite: Fada/Voador, Magic Bounce). Mais Mimikyu, Ribombee e
Goodra. Tudo gruda ou cuida (Sticky Web, Gooey, Follow Me), e o Mimikyu só quer
ser amado, como ela. *Plano:* apoio em Doubles. A Clefable puxa os golpes com
Follow Me, o Mew põe Tailwind e queima com Will-O-Wisp, o Ribombee arma a teia,
e a Magearna fica mais forte a cada Pokémon que cai.

**Falas do fragmento.**
- *Chegada:* A small bright room with no corners. / Soft lights floated near the ceiling. When one brushed your sleeve, it stayed there a moment before letting go.
- *Boss:* One of the lights drifted down from the ceiling and landed in front of you. / It had a face, and it was very, very curious about yours.
- *Ficha do Looker:* File UB Adhesive. / No harm done. No damage. One very small creature that followed you all the way to the door. / It is the shortest file I have. I have read it four times.

**Falas do campeão** (e as genéricas, de quando Zossie cai numa das quatro primeiras salas): na [ficha](alola/zossie.md) dele, seções "Diálogo associado ao lendário" e "Diálogo genérico".

### 3.9. UB Stinger — Naganadel — Soliera

**Conceito.** Naganadel guarda centenas de litros de líquido venenoso no corpo e
voa rápido demais para acompanhar. É o Poipole crescido.

**O fragmento.** O topo de uma torre, muito acima de uma cidade de luzes (a Megalo
Tower lembrada de longe). Vento de todos os lados. Riscos longos e retos cortados
no telhado, todos apontando para o mesmo ponto.

**O treinador.** Soliera, a integrante da Ultra Recon Squad focada na missão
acima de tudo, e quem entrega o Poipole ao jogador em Ultra Sun.

**O campeão.** A criatura já passou onze vezes sobre a torre, cada vez mais
baixo, e a Soliera contou. No mundo dela, entregaram um pequeno como aquele a
quem os ajudou, e foi ela quem entregou. Nunca soube no que ele se tornou, e
talvez esteja prestes a descobrir. Na derrota, ela não pede segunda chance. O
que fica: se foi nisso que ele cresceu, alguém o criou bem, ou ninguém criou; de
perto, o jogador vai saber. E o único aviso que a criatura dá: a agulha aponta
antes do golpe. (A narração do boss fecha a conta: "the twelfth time".)

**Time (R11).** Lendário **Eternatus**, Veneno/Dragão como o Naganadel e
chegado do espaço; semi-lendário **Latios**, o jato do céu; Mega **Beedrill**
(Bugtite: Adaptability), o ferrão. Mais Crobat, Dragapult e Drapion. *Plano:*
velocidade e um golpe só. O Crobat abre com Tailwind e Taunt, e a Mega Beedrill
e o Dragapult batem antes de tudo. O Fell Stinger do Beedrill é o golpe que
termina e ainda sobe o ataque. O Drapion arma Toxic Spikes e o Eternatus fecha
com Dynamax Cannon e Recover.

**Falas do fragmento.**
- *Chegada:* The top of a tower, far above a city of lights. / The wind came from every side at once. Long straight scars were cut into the roof, all of them pointing at the same spot.
- *Boss:* Something passed overhead too fast to see. Then again, lower. / The twelfth time, it stopped in the air in front of you, and pointed.
- *Ficha do Looker:* File UB Stinger. / You tell me it carries enough poison to fill a bathtub, and flies faster than you could follow. / I have moved my desk slightly further from the window. For no reason.

**Falas do campeão** (e as genéricas, de quando Soliera cai numa das quatro primeiras salas): na [ficha](alola/soliera.md) dele, seções "Diálogo associado ao lendário" e "Diálogo genérico".

### 3.10. UB Assembly — Stakataka — Byron

**Conceito.** Parece feita de pedras empilhadas, mas cada "pedra" é uma forma de
vida separada. Muros que começaram a andar e atacar. Segundo o Phyco, uma
Stakataka reúne quase 150 dessas criaturas.

**O fragmento.** Uma pedreira de pedra cinza, com muros em todas as direções. O
jogador tinha certeza de que o caminho atrás dele estava aberto um instante antes.

**O treinador.** Byron, líder de Canalave, minerador, "o homem de corpo de aço",
pai do Roark, e dono de um Bastiodon, ele mesmo um muro vivo.

**O campeão.** O Byron corta pedra de montanha a vida inteira e sabe que aquele
muro não é pedra: cada tijolo está vivo, uns cento e cinquenta, cada um
segurando o próximo. Ele e o filho não concordam nem em como empilhar uma
prateleira, e aquelas criaturas levantaram uma fortaleza juntas. A vitória: um
time que segura, sem rachadura. O que fica: não procure o tijolo fraco, não
existe; bata no muro inteiro, com tudo, de uma vez. E depois vá ligar para a
família. Ele vai ligar para a dele.

**Time (R11).** Lendário **Zamazenta** (com o Rusted Shield, a forma Crowned: o
escudo), semi-lendário **Registeel**, Mega **Steelix** (Steeltite: Aço/Terra,
Sand Force), mais Bastiodon, Bronzong e Tyranitar. O muro, peça por peça.
*Plano:* areia e Trick Room. O Tyranitar chama a tempestade de areia, o Bronzong
inverte a ordem dos turnos, e os lentos batem primeiro: a Mega Steelix na
areia, Bastiodon e Zamazenta com Iron Defense e Body Press, o Registeel com
Stealth Rock e o Bastiodon com Wide Guard em Doubles. Em Singles, o mesmo time
joga como parede.

**Falas do fragmento.**
- *Chegada:* A quarry of grey stone, with walls in every direction. / You were sure the way behind you had been open a moment ago.
- *Boss:* The wall ahead shifted, brick by brick, and stood up on four thin legs. / Every stone in it turned to look at you.
- *Ficha do Looker:* File UB Assembly. / One creature that is really a hundred and fifty, all holding each other up. / I have been told it is a threat. I have filed it under threats. I keep wanting to move it.

**Falas do campeão** (e as genéricas, de quando Byron cai numa das quatro primeiras salas): na [ficha](sinnoh/byron.md) dele, seções "Diálogo associado ao lendário" e "Diálogo genérico".

### 3.11. UB Burst — Blacephalon — Fantina

**Conceito.** Blacephalon baixa a guarda do alvo com o andar esquisito, detona a
própria cabeça sem aviso e rouba a vitalidade dele. É um palhaço de fogos de
artifício.

**O fragmento.** Um teatro vazio, com cada poltrona ocupada por uma sombra. Fogos
estouram no alto sem som. A cada estouro, as sombras nas poltronas ficam mais
fracas.

**O treinador.** Fantina, líder de Hearthome, "a dançarina sedutora e cheia de
alma", estrela de concursos, com Pokémon Fantasma.

**O campeão.** A Fantina fala da criatura como de uma colega de palco: dança mal
de propósito para você rir, você ri e se inclina, e aí, *boum*, ela tira a vida
da plateia e faz uma reverência. A Fantina também tira o fôlego do público, mas
devolve. A vitória: o jogador assistiu ao show inteiro sem se perder. O que fica:
um bom artista dá tudo e o público sai com mais do que trouxe; aquela lá só tira
e chama isso de aplauso. "Quando ela se curvar para você, não aplauda. Não se
incline. Só termine o show."

**Time (R11).** Lendário **Hoopa**, o gênio travesso que tira coisas dos anéis,
um mágico de palco; semi-lendário **Meloetta**, a cantora que passa para a forma
de dança com Relic Song; Mega **Chandelure** (Ghostite: Fantasma/Fogo como a
Blacephalon, Infiltrator). Mais **Mismagius** (o ás dela em Diamond/Pearl),
Oricorio-Sensu e Drifblim. *Plano:* o espetáculo. O Drifblim põe Tailwind, o
Oricorio-Sensu (Dancer) copia toda dança do campo em Doubles, a Meloetta dança,
e Mismagius e Hoopa atacam. A fraqueza a Sombrio e Fantasma é o risco do número.

**Falas do fragmento.**
- *Chegada:* An empty theatre, every seat filled with shadow. / Fireworks burst overhead without a sound. Each time one went off, the shadows in the seats grew fainter.
- *Boss:* The curtain rose on an empty stage. / Something walked out with a strange, careless step. It bowed deeply, and its head began to glow.
- *Ficha do Looker:* File UB Burst. / A performer who charms its audience, blows its own head off, and takes their strength while they clap. / I have been to theatre like that. I did not know it was a species.

**Falas do campeão** (e as genéricas, de quando Fantina cai numa das quatro primeiras salas): na [ficha](sinnoh/fantina.md) dele, seções "Diálogo associado ao lendário" e "Diálogo genérico".

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
4. **O campeão:** `_ChampionIntro` → batalha → `_ChampionDefeat` →
   `_ChampionAfter`. Os mesmos onze também podem cair nas salas 1–4 de
   qualquer dia, com a fala genérica (`_Intro`, `_Defeat`). Na reentrada
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

As 88 falas estão em [`ULTRA_BEASTS_TEXTS.inc`](ULTRA_BEASTS_TEXTS.inc), com
rótulos `Nexus_Text_<Codinome>_<Parte>` (fragmento) e
`Nexus_Text_<Treinador>_<Parte>` (treinador). O arquivo é a fonte das strings do
jogo; as fichas trazem as mesmas falas em texto corrido. Conferido:

- `medir_linha.py`: nenhuma linha passa de 208 px.
- Todos os caracteres estão no `charmap.txt` (`…` e aspas curvas incluídas; sem
  traço longo).
- O maior texto tem bem menos de 600 bytes, longe do teto de 1000 do
  `gStringVar4`.
- `_Intro`, `_Defeat`, `_ChampionIntro` e `_ChampionDefeat` são textos de
  `trainerbattle` e não levam `{SPEAKER}` (a plaquinha vem do treinador).
  `_ChampionAfter` e `_LookerFile` levam, e são os que pedem os `SP_NAME_*` novos.

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
