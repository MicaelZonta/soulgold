# SoulGold — Rift Missions

**Design consolidado v7 — revisão de continuidade e Lillie entregando o SquirtBottle**

## 1. Objetivo e autoridade deste documento

Rift Missions é uma história adicional de SoulGold que apresenta personagens de Alola durante a campanha de Johto, desenvolve uma investigação de Ultra Beasts após a Elite Four e termina em um sistema permanente de expedições com batalhas e capturas de lendários.

Este documento consolida as decisões mais recentes da conversa. É uma especificação de design, não um relatório de implementação: nenhuma mecânica, mapa, disponibilidade de Pokémon ou capacidade do engine foi validada no código para esta entrega. O repositório público pode não refletir as alterações locais do projeto.

As seções de conteúdo estabelecido são a referência para a execução. Recomendações técnicas e pendências são identificadas separadamente; não devem ser confundidas com novas decisões aprovadas. As fontes dos jogos contextualizam a inspiração; o estado vigente de cada personagem neste documento governa os diálogos do hack.

### Direção narrativa: uma história que acontece em paralelo

O arco de Alola se desenvolve ao mesmo tempo que a jornada pelos ginásios de Johto. Lillie está aprendendo a ser treinadora, Gladion viaja e desafia o jogador, Kukui pesquisa formas regionais e Looker e Anabel investigam acontecimentos que ainda não são plenamente compreendidos. Eles têm motivos próprios para estar na região e reaparecem em momentos naturais da viagem.

A campanha de Johto mantém seu próprio conflito e sua conclusão. Os encontros recorrentes, o crescimento do Cosmog e o incidente de Blackthorn constroem gradualmente uma segunda história, cuja investigação principal e resolução ficam para depois da Liga. Não atribuir todos os acontecimentos de Johto a Necrozma nem transformar cada encontro em uma explicação sobre portais.

O efeito desejado é um mundo maior e em movimento: o jogador cruza caminhos com outras pessoas, acompanha suas mudanças e, no final, reúne aliados que conheceu ao longo da jornada. Cosmog conecta o início íntimo dessa relação à escala do desfecho no altar.

## 2. Estrutura geral

1. Apresentar Lillie, Gladion e Kukui durante a campanha normal e receber o Mystery Egg de Cosmog em Violet.
2. Mostrar uma ruptura em Blackthorn, com Buzzwole e Pheromosa em batalha dupla.
3. Após a E4, iniciar a investigação no escritório de Looker e Anabel em Olivine.
4. Concluir nove missões consecutivas de Ultra Beasts, retornando ao escritório após cada uma.
5. Após as nove missões, apresentar Solgaleo **ou** Lunala a Looker para liberar a reunião e o navio.
6. Viajar ao altar com o parceiro evoluído do Mystery Egg para abrir a passagem até Necrozma.
7. Ativar o evento do Eclipse, resolver o conflito com Lusamine e enfrentar Ultra Necrozma.
8. Encerrar a história com uma despedida e manter Looker e Anabel no altar para expedições repetíveis.

O conteúdo de captura de Ultra Beasts desta história fica no pós-E4. A batalha de Blackthorn é a única aparição antecipada prevista nesta questline. Isso não instrui remover fontes de Pokémon já existentes em outros sistemas do jogo.

## 3. Elenco e arcos

### Looker

Investiga as aparições e rupturas em Johto. Deve aparecer em todas as quests de Ultra Beasts, além de participar do incidente de Blackthorn. É o fio condutor da investigação, apresenta as missões e recebe o jogador ao final de cada uma.

Sua presença não deve se limitar a entregar tarefas no escritório: os roteiros precisam incluí-lo nas ocorrências locais. O acompanhante da tabela de missões se soma a Looker, não o substitui.

### Anabel

Anabel é uma Faller e já sabe disso nesta continuação. Ainda possui lacunas de memória. Sua experiência pessoal com o deslocamento entre realidades orienta o cuidado com quem chega pelas rupturas e sua insistência em preparar o retorno das expedições. Ela compartilha essa história com o jogador antes da viagem ao altar.

Trabalha com Looker na investigação. Compartilha o escritório em Olivine e vende Beast Balls desde o início das missões pós-E4. Participa da preparação do evento final e, após Necrozma, permanece no altar com Looker.

O fornecimento de Beast Balls faz parte do apoio à investigação. Não é necessário introduzir uma ligação com a Ultra Recon Squad para justificar esse serviço.

### Lusamine

A história assume uma continuidade própria posterior aos acontecimentos de Alola, combinando elementos de Sun/Moon e Ultra Sun/Ultra Moon. Lusamine viaja para Johto, busca reparar seus erros e reconstruir sua relação com os filhos. Participa diretamente das missões de Kartana e Nihilego.

O jogador a enfrenta uma única vez, perto do final. Para conter a crise, o grupo precisa atravessar uma passagem instável e derrotar Necrozma, mas existe o risco de não conseguir retornar. Lusamine insiste em assumir a operação sozinha, movida pela culpa e pela necessidade de reparação. O confronto com o jogador resolve essa disputa e conduz à aceitação de ajuda.

O encerramento do arco deve mostrar responsabilidade, cooperação e continuidade da relação familiar. O perigo da travessia é um conflito a resolver, não uma recompensa ou prova de valor pessoal.

### Lillie

Viaja com a mãe e está se encontrando como treinadora. Sua progressão passa pela batalha inicial com Oak e Kukui, pela revanche e entrega do SquirtBottle em Goldenrod e pelo teste do Dragon’s Den. Atua nas missões de Pheromosa, Celesteela e Guzzlord.

Ela não entrega Cosmog nem Cosmoem. O jogador recebe Cosmog pelo Mystery Egg em Violet e o desenvolve ao longo da jornada.

### Gladion

Age como um rival recorrente ao longo da história, alternando desafios e cooperação. Sua primeira batalha ocorre no Pokémon Center de Violet, onde substitui o assistente de Elm e entrega o Mystery Egg após a vitória do jogador. Oferece aquecimento opcional na Liga, luta ao lado do jogador em Blackthorn e participa das missões de Buzzwole, Xurkitree e Guzzlord. O antigo encontro ligado à Whitney foi removido.

#### Novo parceiro de Gladion

Gladion encontrou outro Type: Null abandonado em Alola, acolheu-o e o trouxe para sua jornada por Johto. Ele está treinando esse novo parceiro e construindo uma relação de confiança. Esta origem é uma adição autoral do hack à continuidade híbrida SM/USUM.

O Silvally de sua jornada anterior continua existindo na história. O Type: Null atual é outro indivíduo: não houve regressão do parceiro original. Não é necessário explicar nesta trama onde está cada integrante de sua equipe anterior. O responsável pelo abandono e a procedência específica deste novo Type: Null ficam em aberto, sem criar outra investigação obrigatória.

Gladion continua sendo um treinador experiente. Seu objetivo nesta viagem é dar ao parceiro espaço para aprender, confiar e agir por iniciativa própria. As primeiras batalhas usam uma equipe em desenvolvimento, justificando o desafio acessível em Violet sem apagar sua experiência.

| Etapa | Parceiro | Desenvolvimento narrativo |
| --- | --- | --- |
| Violet, antes da entrega do ovo | Type: Null | Está se acostumando a Gladion e a batalhar contra outros treinadores. |
| Blackthorn, dupla contra as Ultra Beasts | Type: Null | Coopera com o jogador e Gladion confia nele para ajudar a proteger os outros. |
| Entrada da Liga, aquecimento opcional | Silvally | A evolução revela a confiança construída ao longo da viagem. |
| Missões pós-E4 | Silvally | Mantém a evolução e a relação consolidada, mesmo se o jogador recusou o aquecimento. |

A evolução acontece na jornada de Gladion entre Blackthorn e a Liga. Não depende de vencer o jogador nem de aceitar a batalha opcional. Não exige uma cutscene de evolução ou nova flag: as equipes de cada encontro podem representar os estágios previstos. Níveis, golpes, itens, demais membros e Memórias ainda precisam de balanceamento.

**Sequência de diálogo para implementação:**

1. Em Violet, depois de mencionar Lillie e antes do desafio, Gladion apresenta brevemente o parceiro. O ovo continua sendo entregue após a vitória, conforme a cena existente no design.
2. Após a batalha, ele reconhece uma iniciativa do Type: Null em vez de avaliar somente o resultado.
3. Em Blackthorn, uma instrução curta mostra a confiança maior entre os dois, sem repetir a história do abandono.
4. Na Liga, antes de oferecer o aquecimento, Gladion apresenta a evolução. Assim, o jogador acompanha o arco mesmo recusando a luta.

**Falas originais propostas em inglês:**

> Violet, apresentação: “I found this Type: Null in Alola. Someone had left it behind. It's traveling with me now.”
>
> Antes do desafio: “We're still getting used to each other. A battle with someone new should help.”
>
> Após a batalha: “You saw that? It made that move on its own. That's progress.”
>
> Blackthorn: “Stay with me, Null. We'll cover them.”
>
> Liga: “Remember the Type: Null you met in Violet? Take a look. It used to wait for me to decide everything. Now it takes the first step.”

Não repetir a mesma explicação em todos os encontros. A evolução deve ser percebida nas atitudes de ambos. Esse parceiro permanece com Gladion; esta decisão não autoriza um presente de Type: Null ao jogador.

### Kukui

Estava viajando por Kanto e decide visitar Johto ao ouvir relatos de formas de Alola na região. Sua curiosidade o envolve na investigação. Está com Oak e Lillie na apresentação inicial e participa diretamente das missões de Blacephalon e Stakataka.

Seu papel deve preservar essa motivação de pesquisador que acaba envolvido nos acontecimentos, sem exigir outra linha de quests independente.

### 3.1. Referência de continuidade e voz para os roteiristas

Pesquisa consultada em 9 de setembro de 2026. **Decisão do autor: este sideplot é uma continuação híbrida de SM e USUM**, situada depois dos acontecimentos de Alola. Não precisa reproduzir integralmente a cronologia de uma das versões. Sua progressão em Johto acontece em paralelo à campanha principal e culmina depois da Liga.

Da estrutura de SM, aproveitamos a investigação de Ultra Beasts de Looker e Anabel e o peso das relações familiares. De USUM, aproveitamos Necrozma, a viagem de Gladion a Kanto/Johto e referências para o desenvolvimento posterior da família. As decisões específicas deste design têm prioridade ao combinar essas fontes.

Os jogos originais são continuidades alternativas. Isso serve para identificar de onde vem cada referência, não para proibir a mistura aprovada. Eventos incompatíveis precisam de uma escolha coerente no roteiro; não presumir que todas as cenas das duas versões aconteceram literalmente. Detalhes como a fusão de Lusamine com Nihilego permanecem sem adoção explícita. Anime, manga e Masters não são continuidade obrigatória.

Os resumos canônicos abaixo são separados das escolhas de escrita de SoulGold. Todas as falas de exemplo deste documento são originais, não transcrições dos jogos.

#### Gladion — reservado, exigente, protetor

**Base pesquisada:** resgata Type: Null, valoriza força e desenvolve confiança na cooperação. Seu cuidado com a família contrasta com sua postura inicialmente hostil. Em USUM, parte para treinar em Kanto e Johto: a viagem do hack tem um apoio direto nessa versão. [Fonte: Gladion, jogos principais](https://bulbapedia.bulbagarden.net/wiki/Gladion#In_the_core_series_games).

**Direção autoral:** frases curtas e concretas; reconhecimento relutante, mas sincero. Demonstra cuidado por ações e instruções práticas. Não converter toda fala em reticências, ameaça ou provocação. Sua competição serve ao desejo de estar preparado para proteger alguém. Evitar repetir a dinâmica de Silver: Gladion pode desconfiar de pessoas, mas valoriza seus parceiros Pokémon.

Em Violet, a menção a Lillie explica sua curiosidade; a entrega mostra responsabilidade. Na dupla de Blackthorn, ele divide tarefas com o jogador. Na Liga, o convite opcional mostra respeito pela escolha alheia. Sua preocupação com Lillie não lhe dá autoridade para escolher por ela.

> “You take the one on the left. I'll keep the other away from the houses.”

#### Lillie — delicada na expressão, firme nas escolhas

**Base pesquisada:** gosta de leitura, ajuda Kukui, protege Nebby e cresce em confiança ao longo da jornada. Sua linguagem é educada e seu cuidado com Pokémon é central. A hesitação inicial diante de batalhas não resume todo o seu arco. [Fonte: Lillie, personalidade nos jogos](https://bulbapedia.bulbagarden.net/wiki/Lillie#Personality).

**Direção autoral:** nesta continuação ela já sabe tomar decisões; ainda aprende a competir. Pode estar nervosa com uma estratégia sem voltar à insegurança do início de Alola. Usar observações específicas, pedidos educados e conclusões próprias. Não escrever gagueira constante, dependência permanente do jogador ou pedidos de desculpa em cada caixa.

Em Goldenrod, ela pede a revanche por iniciativa própria. No Dragon's Den, responde segundo seus valores, mesmo que a mãe ou o irmão pensassem diferente. Nas missões, percebe necessidades dos Pokémon e ajuda a agir; não fica somente preocupada ao fundo.

Alolan Vulpix nível 7 é uma escolha aprovada do hack, não uma exigência do cânone dos jogos. O Cosmog do jogador não deve ser chamado automaticamente de Nebby. Proposta: tratá-lo como outro indivíduo, cuja origem específica não está fechada.

> “I am worried. But I can still help. Tell me where you need us.”

#### Kukui — entusiasmo de pesquisador e presença de mentor

**Base pesquisada:** sua especialidade são os movimentos Pokémon; é um treinador experiente, tem histórico de viagem e desafios em Kanto e acolhe Lillie com Burnet. Sua identidade como Masked Royal também mostra seu entusiasmo pelas batalhas. [Fonte: Professor Kukui, história nos jogos](https://bulbapedia.bulbagarden.net/wiki/Professor_Kukui#Pokémon_Sun_and_Moon).

**Direção autoral:** informal, caloroso e atento ao que ocorre diante dele. Explica ciência a partir de um movimento ou comportamento observado. Um comentário divertido pode quebrar tensão, mas ele sabe reconhecer perigo e parar de brincar. Não reduzir sua voz a bordões ou fazê-lo soar como um relatório de laboratório.

A viagem atual e o interesse por formas de Alola em Johto são escolhas do hack. Relacionar as formas a diferenças em movimento, adaptação e comportamento preserva sua especialidade. Na casa da Route 30, encoraja Lillie sem falar por ela. Em Cherrygrove e Violet, transforma observações de campo em orientação útil.

> “That turn was sharp! See how it keeps its balance? Let's give it room before we try getting closer.”

#### Lusamine — autoridade aprendendo a escutar

**Base pesquisada:** presidente da Aether e mãe de Lillie e Gladion. Sun/Moon enfatiza sua obsessão por Ultra Beasts; USUM coloca sua intervenção contra Necrozma e seu desejo de proteger Alola no centro, sem apagar o comportamento controlador ou o dano às relações familiares. Não importar automaticamente a fusão com Nihilego de Sun/Moon. [Fonte: Lusamine, diferenças entre as histórias](https://bulbapedia.bulbagarden.net/wiki/Lusamine#In_the_core_series_games).

**Direção autoral:** fala elaborada, assertiva e habituada a decidir. A reparação aparece quando ela pergunta, escuta uma recusa e muda sua conduta. Não fazer uma mãe subitamente perfeita nem repetir desculpas em todas as cenas. Nas missões, sua experiência ajuda; seu impulso de assumir controle pode criar tensão.

Na missão de Nihilego, explorar responsabilidade e limites da pesquisa, sem pressupor lembranças de uma fusão nesta continuidade. No clímax, ela quer liderar a travessia por acreditar que sua experiência lhe impõe responsabilidade. O grupo constrói um plano de retorno; a batalha demonstra coordenação e leva à aceitação de ajuda. Reconciliação exige atitudes posteriores, não apenas uma derrota.

> “I had already decided what would be best for you. Again. Tell me your plan, Lillie. This time, I will listen.”

#### Anabel — comando sereno e proteção concreta

**Referência de personagem:** treinadora ligada à Battle Frontier e integrante da Polícia Internacional, com experiência em operações de Ultra Beasts e proteção de áreas povoadas. [Fonte de inspiração: Anabel nos jogos](https://bulbapedia.bulbagarden.net/wiki/Anabel#In_the_core_series_games).

**Estado vigente em SoulGold:** Anabel é uma Faller, sabe que atravessou uma ruptura e ainda tem lacunas de memória. Os roteiristas devem escrever suas cenas com esse conhecimento desde o início; a revelação posterior informa o jogador, não a própria Anabel.

**Direção autoral:** instruções precisas, gentileza contida e atenção às condições da equipe. No hack, Looker conduz os relatórios e a conversa com testemunhas; Anabel coordena proteção, preparo e retirada. Isso não a transforma em subordinada sem iniciativa ou apenas vendedora de Beast Balls.

Ela descobriu sua condição antes dos acontecimentos de Johto. O modo exato como recebeu essa informação não precisa de uma nova quest nem impede a escrita das cenas atuais. Não é necessário encenar essa descoberta ou explicar a origem de todas as suas lembranças.

Ela distingue observação de hipótese. Sua experiência não concede poderes para detectar portais, identificar qualquer realidade ou prever o enredo. Saber que atravessou uma ruptura não significa lembrar de tudo que viveu antes dela. Ela pode falar com segurança sobre sua condição e admitir as lacunas.

**Progressão da revelação:**

| Momento | Conteúdo e intenção |
| --- | --- |
| Primeiras missões pós-E4 | Mostra atenção especial a desorientação e deslocamento. Não explica toda a biografia no primeiro briefing. |
| Reunião em Olivine, antes de liberar o navio | Após cumprir as nove missões e apresentar Solgaleo ou Lunala, conta ao jogador que também atravessou uma ruptura. Liga a revelação à preparação do retorno. |
| Preparação no altar | Usa essa experiência para sustentar um plano coletivo. Escuta Lusamine, mas insiste em que todos tenham uma forma de voltar. |
| Despedida e pós-Necrozma | Escolhe permanecer para ajudar a fechar rupturas e dar assistência a quem for deslocado. Sua motivação vai além da obrigação profissional. |

**Sequência de cena para Terra, dentro da reunião já existente:**

1. Looker conclui o resumo da investigação e reconhece o Pokémon apresentado pelo jogador.
2. Anabel explica o risco da travessia e pede um momento para contextualizar sua preocupação.
3. Ela revela que é uma Faller e ainda não recuperou todas as lembranças. A fala é serena e pessoal, sem uma exposição longa.
4. Explica que recebeu ajuda quando chegou e quer oferecer o mesmo cuidado a outros deslocados.
5. Looker reconhece a decisão de compartilhar isso sem contar a história por ela.
6. Anabel retoma a condução da preparação: a equipe precisa planejar a ida e a volta. A reunião então libera o navio normalmente.

**Falas originais propostas em inglês:**

> Primeiras missões: “Being somewhere unfamiliar can be frightening. Give it room. We don't yet know what it has been through.”
>
> Revelação: “There is something you should know. I am a Faller. I crossed an Ultra Wormhole, too. Some of my memories are still missing.”
>
> Continuação: “I arrived somewhere I didn't recognize. Someone helped me. I want others to have that same chance.”
>
> Looker: “Thank you for telling them, Chief. We'll make sure the preparations are in place.”
>
> Anabel: “Then let's finish our plan. Opening the passage is only the beginning. We must be able to bring everyone home.”
>
> Pós-Necrozma: “I'll stay here with Looker. We can close these rifts—and help anyone who reaches us through them.”

**Implementação:** integrar as falas à progressão da reunião e da despedida, sem uma flag exclusiva para a revelação. Não criar uma missão adicional de recuperação de memória. As expedições repetíveis continuam seguindo o loop definido; a motivação de acolhimento não adiciona um sistema obrigatório de resgate em cada run.

> “The street is clear. Take your time preparing. We proceed when you and your Pokémon are ready.”

#### Looker — investigador expressivo, atento às pessoas

**Base pesquisada:** agente da Polícia Internacional, trabalha com investigação, disfarces e apoio de campo. Em X/Y, seu cuidado com Emma evidencia compaixão para além da missão. Em SM, Anabel é sua superior; ele apoia a operação de Ultra Beasts e se preocupa com o desgaste dela. Nesse período, não possui Pokémon para combater. A fala peculiar da localização inglesa de Platinum é menos acentuada nos jogos posteriores. [Fonte: Looker, história nos jogos principais](https://bulbapedia.bulbagarden.net/wiki/Looker#In_the_core_series_games).

**Direção autoral:** um pouco teatral na apresentação, formal de um jeito pessoal, caloroso quando percebe medo ou cansaço. Pode começar um comentário com solenidade e corrigi-lo de maneira simples. O humor vem do contraste entre postura de detetive e situações cotidianas, sem torná-lo incompetente. Evitar gramática artificialmente quebrada, bordões em toda fala e explicações longas de fatos que o jogador acabou de ver.

Ele faz perguntas antes de concluir, confere testemunhos e separa pistas de hipóteses. Diante de perigo, suas frases ficam diretas. O relatório importa, mas primeiro ele verifica se todos voltaram bem. Não tratar Ultra Beasts como criminosos apenas por terem aparecido em Johto.

**Com Anabel:** respeita sua liderança e experiência; ela orienta a operação, enquanto ele conduz entrevistas, acompanha ocorrências e recebe relatórios. A centralidade do escritório de Looker na interface não o transforma automaticamente no chefe dela. Sua preocupação pode aparecer num pedido discreto de descanso; não deve retirar a autonomia de Anabel.

**Em Blackthorn:** ajuda a afastar moradores, observa a ruptura e orienta o retorno enquanto jogador e Gladion combatem. Participar de todas as quests não exige dar-lhe uma batalha ou equipe nova. **No escritório:** reconhece uma informação específica de cada missão, em vez de repetir apenas que surgiu outra ocorrência. **No altar:** informa o que foi confirmado sobre a passagem e admite o que ainda é incerto. **No loop:** mantém falas breves para partidas repetidas, com interesse pelo retorno da equipe.

**Referências ao longo dos jogos:** a base de Looker inclui sua trajetória na série principal, não apenas Alola. A tabela distingue acontecimentos pesquisados de aplicações propostas para Johto. [Histórico por jogo](https://bulbapedia.bulbagarden.net/wiki/Looker#In_the_core_series_games) e [registro dos diálogos](https://bulbapedia.bulbagarden.net/wiki/Looker/Quotes).

| Jogo | Referência pesquisada | Aplicação autoral ao sideplot |
| --- | --- | --- |
| Platinum | Investiga a Team Galactic, infiltra-se com disfarces e fornece acesso e informações ao jogador. | Mostrar trabalho acontecendo fora das batalhas: entrevistas, pistas e preparação da próxima ação. Sua entrada pode ser teatral, mas precisa trazer algo útil. |
| Black/White | Procura os Sete Sábios e reaparece para assumir a custódia dos encontrados. | Cada retorno deve produzir uma consequência concreta. Ele acompanha e conclui a parte investigativa de cada ocorrência. |
| X/Y | A relação com Emma dá ao escritório uma dimensão pessoal e protetora. | Conhecer moradores pelo nome e lembrar consequências locais; as pessoas continuam importantes depois do relatório. |
| ORAS | Aparece desorientado e sem memória após chegar à praia. | Referência de vulnerabilidade, não uma condição permanente a impor ao Looker de Johto. Não inventar uma causa confirmada para esse episódio. |
| Sun/Moon | Apoia Anabel na operação de Ultra Beasts. | Experiência, cuidado com a equipe e divisão clara de responsabilidades. |
| USUM | Atua em aparições mais breves e acompanha Anabel em Alola. | Espaço para cenas cotidianas e humor fora de uma emergência. |

**Leitura de voz a partir dos diálogos:** em Platinum, ele pode superestimar dramaticamente o significado de uma conversa comum e corrigir o próprio pedido. Há contraste entre formalidade policial e desejo de contato. Para o hack, aproveitar o ritmo e a humanidade dessas falas, sem reproduzir literalmente sua gramática ou copiar bordões. [Fonte de análise: falas de Looker](https://bulbapedia.bulbagarden.net/wiki/Looker/Quotes#Pokémon_Platinum).

**Propostas de encenação para as quests:**

- Chegar com uma pista obtida de um morador, não apenas anunciar a espécie que o jogador já viu.
- Permitir um disfarce ocasional quando houver motivo investigativo. Não repetir a mesma piada em todas as cidades.
- Depois de uma resolução, perguntar por alguém afetado e providenciar ajuda antes de mudar de assunto.
- Alternar apresentações expressivas com instruções curtas durante crises. O humor cessa quando alguém precisa de assistência.
- Em Guzzlord, dar mais peso à preparação e à confiança na equipe; não transformar a missão em uma exposição longa de seu passado.
- Na despedida, mostrar que permanecer em Johto também significa continuar acompanhando as pessoas que conheceu.

Essas propostas não adicionam missões, flags ou personagens obrigatórios. Servem para escrever os encontros já aprovados. Não é necessário inserir referências nominais a todas as regiões: o histórico deve orientar suas atitudes, não virar uma lista de participações anteriores.

**Exemplos originais em inglês:**

> Primeiro contato: “Looker. International Police. I have a few questions—but first, is everyone all right?”
>
> Investigação: “Three witnesses, three different descriptions. Let us begin with what they all agree on.”
>
> Humor leve: “A most discreet observation post! ...Until that delivery cart needed the doorway.”
>
> Retorno: “There you are! The report can wait a moment. How are your Pokémon?”
>
> Com Anabel: “Chief, I'll finish the interviews. Please take a moment to rest.”
>
> No altar: “We have a way through. Now we make certain we have a way back.”

### 3.2. Aplicação às nove missões

Estas são orientações de escrita propostas, preservando cidades e acompanhantes definidos:

| Missão | O que a participação revela |
| --- | --- |
| Buzzwole / Gladion | Força aplicada à proteção de quem está perto, não uma disputa de ego. |
| Pheromosa / Lillie | Ela observa antes de agir e toma uma decisão por conta própria. |
| Xurkitree / Gladion | Ele aceita dividir tarefas e confiar no jogador. |
| Celesteela / Lillie | Consegue explicar sua ideia ao grupo e sustentar sua posição. |
| Blacephalon / Kukui | Curiosidade acompanhada de responsabilidade pelo entorno. |
| Stakataka / Kukui | Observações sobre coordenação e movimento viram ajuda prática. |
| Kartana / Lusamine | Oferece conhecimento sem exigir que todos obedeçam. |
| Guzzlord / Lillie e Gladion | O irmão escuta a irmã e ambos agem como parceiros. |
| Nihilego / Lusamine | Reconhece limites e prioriza cuidado sobre controle. |

Looker participa de todas as quests. Anabel ajuda a estabelecer objetivos e condições de segurança. Os acompanhantes não devem repetir a mesma explicação do investigador com palavras diferentes.

### 3.3. Regras de escrita e revisão de cenas

- Antes de escrever, identificar o que cada personagem sabe naquele momento. Experiência com Cosmog não revela automaticamente a espécie de um ovo fechado.
- Cada cena precisa dar ao personagem um objetivo além de elogiar o jogador ou entregar uma recompensa.
- Reencontros mudam a relação: Gladion passa de avaliação a confiança; Lillie transforma preparação em iniciativa; Lusamine aprende a compartilhar decisões.
- Tom de conversa e extensão da fala devem variar. Usar poucas caixas com informação concreta; reservar falas longas para decisões importantes.
- Equipes iniciais acessíveis não devem fazer personagens experientes fingirem que nunca lutaram. Tratar os confrontos iniciais como treino com uma equipe adequada; não fixar novas espécies ou níveis sem decisão de balanceamento.
- Teste editorial: sem a identificação do falante, a escolha das palavras e a intenção ainda sugerem quem está falando?

## 4. Encontros durante a campanha

| Evento | Gatilho narrativo | Conteúdo fechado |
| --- | --- | --- |
| Primeira batalha de Lillie | Recebimento da Pokédex | Lillie está com Oak e Kukui; usa Alolan Vulpix nível 7. |
| Gladion em Violet | Ligação de Elm e entrega do Mystery Egg no Pokémon Center | Substitui o assistente; reconhece o jogador pela conversa com Lillie, batalha obrigatoriamente antes de entregar o ovo. |
| Lillie em Goldenrod | Evento de entrega do SquirtBottle, após Whitney | Lillie assume a entrega do item na floricultura; aproxima-se para a revanche antes de entregá-lo. |
| Lillie no Dragon’s Den | Depois de derrotar Clair, durante o teste de perguntas | Jogador e Lillie participam das perguntas. Ao final, o mestre pede uma demonstração da sintonia de ambos com seus Pokémon, levando à batalha entre eles. |
| Incidente de Blackthorn | Durante a passagem pela cidade, antes da E4 | Jogador e Gladion enfrentam Buzzwole + Pheromosa em uma batalha dupla conjunta; Looker participa da história. |
| Aquecimento de Gladion | Entrada da Liga | Gladion oferece uma batalha opcional antes do desafio da E4. |

O posicionamento exato do incidente de Blackthorn em relação ao Dragon’s Den ainda precisa ser definido no roteiro. A entrega da insígnia de Whitney e os eventos de Clair devem continuar funcionando normalmente após a inserção das cenas.

**Diretriz para Blackthorn:** apresentar a ameaça sem antecipar o ciclo de captura pós-E4. A implementação deve definir explicitamente a restrição de captura desse encontro. A falta de Beast Balls, por si só, não é uma regra suficiente para impedir capturas. O formato exato da batalha com aliado depende de verificação do engine.

### 4.1. Oak, Kukui e Lillie — abertura da jornada

Kukui substitui o papel do antigo NPC de Mr. Pokémon na sala e permanece como pesquisador no local. Oak mantém sua função de apresentar e entregar a Pokédex. As posições já ajustadas pelo autor devem ser respeitadas: Kukui ao lado de Oak; somente Lillie começa na cadeira. Não reposicionar os três juntos.

Sequência de encenação:

1. Kukui recebe o jogador e identifica a visita enviada por Elm.
2. Oak participa cedo da conversa, reconhecendo o jogador e observando seu Pokémon. Evitar deixá-lo sem reação durante uma longa apresentação.
3. Kukui contextualiza sua viagem por Kanto e o interesse nas formas de Alola vistas em Johto.
4. Lillie reage da cadeira, se apresenta e se aproxima fisicamente do jogador por um caminho livre. Ela deve parar perto dele e ambos se encarar antes do desafio.
5. Lillie desafia o jogador com Alolan Vulpix nível 7. A batalha ocorre antes de qualquer entrega de item ou Pokédex dessa cena.
6. Em derrota, o fluxo normal leva o jogador ao Pokémon Center. O estado atual do evento permanece pendente; ao retornar, a cena recomeça, sem uma flag adicional exclusiva para Lillie.
7. Em vitória, Lillie comenta a batalha; Kukui entrega o Mystery Egg destinado a Elm e Oak conclui a apresentação e entrega da Pokédex.
8. Oak se despede para seu programa de rádio em Goldenrod e sai.
9. Lillie diz que sua mãe está esperando e sai caminhando até a saída. Kukui permanece na sala e oferece o suporte de cura previsto no evento.
10. Concluir as mudanças de estado da campanha somente após as entregas necessárias, preservando os eventos seguintes de Elm e Silver.

O caminho exato de Lillie depende das coordenadas já configuradas no mapa; não inventar movimentos a partir de coordenadas antigas. A aproximação, o desafio e a saída precisam usar esperas de movimento para não sobrepor texto e deslocamento.

As falas recorrentes de Kukui podem abordar pesquisa, formas regionais e o comportamento dos Pokémon. As referências narrativas a Mr. Pokémon já foram substituídas por Kukui segundo confirmação do autor; não tratar essa troca como pendência.

### 4.2. Mystery Egg de Cosmog

O objeto de missão continua sendo o Mystery Egg levado de Kukui a Elm. Mais tarde, o ovo de Pokémon recebido no Pokémon Center de Violet contém **Cosmog**, substituindo Togepi. Não antecipar a entrega de um Cosmog utilizável para a casa de Kukui.

A sequência é: Kukui entrega o objeto de missão → jogador o leva a Elm → Gladion entrega o ovo em Violet após a batalha → ovo choca como Cosmog → jogador o evolui durante a campanha → Looker reconhece Solgaleo ou Lunala como requisito para a expedição final.


### 4.3. Apresentação ao Prof. Elm e Eviolite

O evento antigo de apresentação de Togepi e entrega de Shiny Stone é substituído por uma apresentação da família de Cosmog com recompensa única de **Eviolite**. Não criar uma segunda cena de recompensa para Togepi.

Condições: Mystery Egg recebido, recompensa ainda não entregue e um membro não-ovo da família Cosmog no time. A busca percorre o time inteiro e aceita Cosmog, Cosmoem, Solgaleo ou Lunala. Aceitar evoluções evita perder a cena por ter desenvolvido o Pokémon antes de voltar ao laboratório. Esta regra é diferente da exigência de Looker, que aceita somente as duas evoluções finais.

Sequência para Terra:

1. Elm reconhece a visita e pergunta pelo ovo que Kukui lhe enviou.
2. O jogador apresenta o Pokémon; Elm interrompe suas anotações para observá-lo.
3. Com Cosmog, Elm reage à aparência de uma pequena nuvem de estrelas e à surpresa de encontrá-lo dentro daquele ovo. Com uma evolução, reconhece que ele já mudou desde que nasceu; não o descrever como se ainda fosse Cosmog.
4. Elm associa o desenvolvimento aos cuidados do jogador e à curiosidade científica despertada pelo ovo.
5. Elm oferece a Eviolite para ajudar a proteger Pokémon que ainda podem evoluir.
6. Entregar o item e confirmar o sucesso antes de marcar a recompensa como concluída. Se a bolsa estiver cheia, manter o evento disponível para nova tentativa.
7. Explicar o efeito de defesa e defesa especial em Pokémon que ainda evoluem. Caso o apresentado seja Solgaleo ou Lunala, esclarecer que a pedra será útil para outro parceiro em desenvolvimento.
8. Encerrar incentivando o jogador a continuar observando e cuidando de seus Pokémon.

**Direção de diálogo proposta, para adaptação ao inglês dos scripts:**

> Elm: “Kukui me enviou um ovo e acabou enchendo meu caderno de perguntas! Agora, olhando para seu parceiro... acho que vou precisar de outro caderno.”
>
> Elm, diante de Cosmog: “Parece que um pedacinho do céu noturno resolveu visitar meu laboratório. E você esteve ao lado dele desde o primeiro instante.”
>
> Elm, diante de uma evolução: “Ele já mudou tanto! Eu queria estudar o que nasceria daquele ovo, e você acabou me trazendo uma nova etapa da descoberta.”
>
> Elm: “Quero lhe dar uma Eviolite. Ela ajuda a proteger Pokémon que ainda estão crescendo. Descobertas levam tempo... e crescer também.”

Essas falas definem intenção e sequência, não novos comandos ou labels obrigatórios. Ajustar quebras de linha ao limite das caixas de texto.

### 4.4. Flags e continuidade do Mystery Egg

- Reaproveitar os IDs de `FLAG_RECEIVED_TOGEPI_EGG` e `FLAG_SHOWN_ELM_TOGEPI`, renomeando os símbolos para refletir o ovo de Cosmog e a apresentação com recompensa. Atualizar todas as referências; os nomes finais seguem o padrão do projeto.
- Não alocar uma nova flag para esse par de eventos. O primeiro estado significa ovo recebido com sucesso; o segundo significa apresentação concluída e Eviolite entregue.
- Revisar o reset em New Game e os scripts de inicialização para que entrar novamente em Violet não apague progresso.
- Alinhar a ligação de Elm em Goldenrod ao ovo recebido e à apresentação ainda pendente, preservando o controle existente da chamada.
- O NPC da Route 32 continua verificando o recebimento do ovo, sem exigir que tenha chocado, que Elm tenha visto Cosmog ou que a Eviolite tenha sido recebida. Atualizar sua indicação para Gladion no Pokémon Center, removendo a referência ao assistente/homem de óculos.
- As falas das Kimono Girls em Violet e de Zuki no teatro continuam válidas com Kukui. O cuidado com o ovo demonstra o vínculo do jogador; não afirma que Cosmog seja uma evolução de Lugia ou Ho-Oh. Essa revisão narrativa está encerrada conforme confirmação do autor.
- Compatibilidade com saves antigos não é requisito. Não criar migração nem conversão de antigos Togepi.

### 4.5. Gladion em Violet — sequência definitiva

1. A ligação de Elm informa que Gladion passou pelo laboratório e aceitou levar o ovo a Violet. Elm pede ao jogador que o encontre no Pokémon Center.
2. O evento de aparição antes usado pelo assistente passa a apresentar Gladion. Revisar a ação que escondia o assistente em New Bark: a entrega agora não exige a ausência dele do laboratório.
3. Gladion ouve ou confirma o nome do jogador. Lillie lhe contou sobre a batalha inicial e seu desejo de tentar novamente.
4. Gladion confirma que trouxe o ovo e pede uma batalha para conhecer o estilo do jogador. Ele não alega que Elm condicionou a entrega a um teste: o desafio é iniciativa sua.
5. Curar o time antes do confronto. Aproximar e orientar os personagens antes de iniciar a batalha obrigatória.
6. Em derrota, permitir nova tentativa pelo fluxo normal. Em vitória, seguir para a entrega existente do ovo de Cosmog e demais entregas realmente presentes no script.
7. Confirmar sucesso da entrega antes de concluir seu estado. Se a entrega falhar após a vitória, retomar a entrega sem exigir nova batalha; verificar se a flag de treinador derrotado ou variável existente resolve esse caso.
8. Gladion se despede e sai. O recebimento do ovo libera o bloqueio correspondente da Route 32.

**Falas originais propostas em inglês:**

> Elm: “{PLAYER}, I've asked a Trainer named Gladion to bring you the Egg. He was heading to Violet City. Meet him at the Pokémon Center, would you?”
>
> Gladion: “You're {PLAYER}? Lillie mentioned you. She's already planning your next battle. Before that, let me see how you fight.”
>
> Gladion, após vencer o jogador: “Your Pokémon kept trying. Pay attention to what they need. We'll try again when you're ready.”
>
> Gladion, após perder: “All right. I see why she wants another match. Here's the Egg. Elm asked me to bring it to you. Take care of it.”
>
> Gladion, despedida: “And when Lillie challenges you again... give her a proper battle.”

Ele não sabe automaticamente qual espécie está dentro do ovo. A entrega é um favor plausível durante sua viagem, não um emprego como assistente de Elm.

### 4.6. Lillie em Goldenrod — revanche e entrega do SquirtBottle

A revanche de Lillie ocupa o evento de entrega do SquirtBottle em Goldenrod. Ela é a responsável por entregar o item ao jogador. A floricultura é o ponto de encenação adotado para aproveitar a entrega existente; coordenadas e movimentos serão ajustados no mapa. Gladion permanece ligado ao ovo em Violet.

**Motivação proposta:** Lillie passou pela floricultura para perguntar sobre a árvore da Route 36 e conseguiu um SquirtBottle. Ao reencontrar o jogador, resolve confiá-lo a ele e aproveitar o momento para a revanche. Não precisa trabalhar na loja nem interromper uma entrega feita por outra NPC.

**Sequência para Terra:**

1. Preservar os requisitos de progressão da entrega, incluindo Whitney, verificando as condições exatas nos scripts atuais.
2. Lillie recebe o jogador no evento e comenta o motivo de estar com o SquirtBottle.
3. Ela menciona seu treino com Vulpix e pede a revanche. Aproximar e orientar os personagens, curando o time antes da batalha.
4. A vitória é necessária para continuar esta sequência e receber o item. Em derrota, manter a cena disponível para nova tentativa.
5. Depois da vitória, Lillie comenta um aprendizado concreto e entrega o SquirtBottle usando a lógica existente do item.
6. Marcar a entrega como concluída somente após sucesso. Caso falhe, retomar apenas a entrega, preservando a vitória.
7. Ela explica que o item permite tentar fazer a árvore sair do caminho, despede-se e segue viagem. Não revelar antecipadamente tudo sobre Sudowoodo.

Reutilizar o estado de recebimento do SquirtBottle e conferir o estado de treinador derrotado ou a variável local para separar batalha e entrega. Atualizar as falas de encaminhamento e a antiga NPC entregadora para que apontem para Lillie e não ofereçam outra cópia. A cena não depende do quiz da Torre de Rádio nem de Gladion ou de uma intervenção no ginásio.

**Falas originais propostas em inglês:**

> Lillie, reencontro: “{PLAYER}! I came to ask about that strange tree on Route 36. The florist gave me this SquirtBottle. You're heading that way, aren't you?”

> Lillie: “I've been practicing with Vulpix. Last time, I was so busy remembering my plan that I almost stopped watching her. I'd like another battle, if you're ready.”
>
> Lillie, depois: “We changed our plan halfway through! I couldn't have done that last time. Next time, I'd like to win, too.”

> Lillie, entrega: “Here, take the SquirtBottle. A little water might persuade that tree to move. I'd like to hear what happens!”

O encontro de Gladion em Mahogany foi uma sugestão anterior, sem aprovação final. Não adicioná-lo como obrigatório. As propostas de Gladion em Azalea e Lillie no Sudowoodo também não são encontros adicionais confirmados.

### 4.7. Encadeamento econômico dos eventos

Reutilizar eventos e estados existentes é uma prioridade. Conferir variáveis locais, flags de treinador e flags de entrega antes de propor novos IDs. A simples inserção de uma batalha antes de um presente não elimina a necessidade de distinguir vitória de entrega pendente. Não prometer custo zero de flags sem auditoria dos scripts.
 
As condições de presença dos NPCs devem acompanhar esses estados. Derrota não pode duplicar recompensas; entrega frustrada não deve repetir uma vitória; sair e voltar não deve apagar progresso. O detalhamento é para New Game, sem migração de saves.

## 5. Escritório em Olivine

O início formal da investigação exige que o jogador tenha concluído a E4 e visite o escritório de Looker e Anabel em Olivine. A casa ou sala exata ainda será escolhida.

O escritório concentra o briefing da missão ativa, o retorno após cada missão e a compra de Beast Balls com Anabel. As missões são consecutivas, seguindo a ordem fixa abaixo. Não é necessário criar um sistema aberto de seleção durante essa parte da história.

Cada missão deve ter uma ocorrência local, participação do elenco indicado e resolução que permita ao jogador apresentar o resultado a Looker. Os objetivos intermediários e diálogos completos serão desenvolvidos a partir das diretrizes de personagem; este design não estabelece puzzles ou minijogos obrigatórios.

## 6. As nove missões pós-E4

| Ordem | Ultra Beast | Cidade ou local | Personagem em destaque, além de Looker |
| --- | --- | --- | --- |
| 1 | Buzzwole | Goldenrod | Gladion |
| 2 | Pheromosa | Olivine | Lillie |
| 3 | Xurkitree | Cianwood | Gladion |
| 4 | Celesteela | Mahogany | Lillie |
| 5 | Blacephalon | Cherrygrove | Kukui |
| 6 | Stakataka | Violet City | Kukui |
| 7 | Kartana | Kitakami Village | Lusamine |
| 8 | Guzzlord | Ecruteak | Lillie e Gladion |
| 9 | Nihilego | New Bark | Lusamine |

A progressão exige retorno ao escritório após cada missão. Nihilego é a última ocorrência e prepara a transição para o encerramento da investigação e a expedição ao altar.

As capturas das Ultra Beasts integram o objetivo de disponibilizar esses Pokémon. A condição exata para concluir uma missão — captura ou vitória com captura disponível depois — ainda precisa ser definida. Nenhuma escolha pode tornar uma espécie permanentemente indisponível por uma derrota ou captura perdida.

Os acompanhantes indicam participação narrativa. Não se deve presumir que todas as missões serão batalhas com aliado: esse formato só está fechado para o encontro de Blackthorn.

## 7. Reunião e expedição

Após concluir as nove missões e entregar o último relatório, o jogador retorna a Looker e Anabel no escritório de Olivine. Looker verifica se há **Solgaleo OU Lunala no time**. Basta um deles; não é necessário ter ambos, e um registro na Pokédex não substitui sua presença.

Essa condição bloqueia somente a expedição final. Não bloqueia o início nem a realização das nove missões de Ultra Beasts.

### Ordem da cena para implementação

1. Looker encerra o relatório de Nihilego e explica que o grupo localizou o altar ligado às rupturas.
2. Anabel explica que alcançar Necrozma exige um Pokémon capaz de abrir a passagem.
3. Looker verifica o time. Cosmog, Cosmoem, um ovo ou a ausência da família não satisfazem o requisito.
4. Se faltar Solgaleo ou Lunala, Looker orienta o jogador a continuar desenvolvendo seu parceiro. A expedição permanece pendente, sem repetir missões concluídas.
5. Quando o jogador voltar com um dos dois, a cena prossegue. Não exigir evolução no próprio mapa, procedência individual ou presença dos dois lendários.
6. A reunião inclui Looker, Anabel, Lusamine, Lillie, Gladion e Kukui. O grupo reconhece que o Pokémon recebido no começo da jornada agora pode ajudá-los a alcançar Necrozma. Anabel revela sua condição de Faller e relaciona sua experiência à necessidade de preparar o retorno, conforme a sequência de seu guia de personagem.
7. A reunião libera o navio em Olivine. A primeira chegada ao altar acontece por essa viagem.

**Fala proposta de Looker quando falta a evolução:**

> “Encontramos a passagem, mas ainda nos falta uma maneira de abri-la. Segundo Kukui, seu parceiro precisa completar sua evolução. Continue cuidando dele e volte com Solgaleo ou Lunala. Nós vamos preparar a expedição.”

Não há evolução automática no altar. O jogador evolui Cosmog normalmente para Cosmoem e depois para Solgaleo ou Lunala. Os dados discutidos usam níveis 43 e 53, com a evolução final definida por dia/noite; confirmar esses valores na árvore de implementação, sem adicionar outro bloqueio à evolução.

### Transporte permanente

- O navio permanece disponível nos dois sentidos após ser desbloqueado.
- A viagem funciona em qualquer horário.
- A primeira chegada libera o altar como destino de Fly.
- O ponto de pouso fica próximo à entrada; Fly também permite sair normalmente.
- Visitas posteriores não repetem a cena completa da expedição.
- O acesso permanece disponível no pós-Necrozma, quando o local se torna a base do conteúdo repetível.

## 8. Um único altar: Sol e Lua

Existe um único local físico. Sol e Lua são estados narrativos e visuais desse altar; não são dois destinos independentes.

| Condição | Estado | Conteúdo |
| --- | --- | --- |
| Dia | Altar do Sol | Apresentação visual diurna; acesso à cena de Necrozma. |
| Noite | Altar da Lua | Apresentação visual noturna; acesso à mesma cena. |
| Após o encerramento | Altar com portal estável | Base permanente das Rift Missions repetíveis. |

Não há encontros de captura de Solgaleo ou Lunala no altar. O Pokémon do jogador abre a passagem até Necrozma. Qualquer um dos dois funciona em qualquer horário: o estado visual do altar não exige a evolução correspondente.

O antigo presente/encontro de Cosmoem foi removido. O altar não entrega outro membro da família e não transforma automaticamente Cosmog ou Cosmoem.

**Recomendação de execução:** na primeira abertura do portal, conferir novamente a presença de Solgaleo ou Lunala para que a cena mostre um Pokémon que realmente está no time. Caso tenha sido guardado, pedir que o jogador o traga, preservando o navio, Fly e a reunião concluída. Após a abertura e a resolução da história, o loop não exige reapresentar o Pokémon.

### Direção visual

A arquitetura segue as referências dos altares de USUM: paredão avermelhado, mecanismo vertical de pedra, disco celestial monumental, escadarias, plataformas e canais de água.

O acabamento deve seguir a escala e o estilo dos tilesets de SoulGold, com peças modulares compactas e pixels definidos. A paleta deve ter mais vida: terracota, pedra clara, água azul-turquesa, vegetação verde, dourado para o Sol e lilás para a Lua.

As imagens conceituais produzidas são referências visuais. Ainda não constituem tilesets de produção validados quanto a grade, paletas, metatiles, camadas ou colisões.

## 9. Lusamine e Ultra Necrozma

Com as nove missões concluídas e Solgaleo ou Lunala apresentado a Looker, a investigação chega ao ponto de enfrentar a origem da instabilidade. A travessia até Necrozma envolve risco de a passagem se desestabilizar e impedir o retorno.

Lusamine insiste em realizar a operação sozinha. A única batalha do jogador contra ela ocorre aqui, resolvendo a disputa e levando-a a aceitar a ajuda do grupo. O roteiro deve dar espaço à reação de Lillie e Gladion sem retirar do jogador o papel no confronto final.

O jogador então atravessa para enfrentar Ultra Necrozma em uma boss battle e obter Necrozma por captura. O tratamento da forma após a batalha precisa respeitar a implementação local: não presumir que Ultra Necrozma pode permanecer como forma de armazenamento. Também não está definido se a captura ocorre durante o combate ou em uma etapa posterior.

Perder, fugir quando permitido ou derrotar sem capturar não pode bloquear definitivamente o encerramento nem a obtenção do Pokémon. O mecanismo de repetição deve ser definido antes da implementação do encontro.

Após a resolução, ocorre o evento de despedida. Looker e Anabel permanecem no altar; os destinos e falas finais dos demais personagens ainda serão escritos.

## 10. Pós-Necrozma: expedições permanentes

As rupturas continuam surgindo depois da história, mas a passagem principal está mais estável sem a interferência de Ultra Necrozma. Looker e Anabel conduzem novas missões para fechar o máximo possível dessas conexões. Anabel também permanece por uma razão pessoal: como Faller, quer oferecer assistência a quem precisar, assim como recebeu ajuda quando chegou. Isso não altera a natureza conceitual dos destinos nem significa que todas as expedições encontrem pessoas.

Os destinos são realidades quebradas: fragmentos que materializam conceitos do universo. Não representam necessariamente outra dimensão completa ou um mundo habitado. Essa premissa permite espaços temáticos e encontros variados sem exigir uma nova região coerente para cada expedição.

End of Time e Legendary Nexus foram nomes de trabalho usados para esse conteúdo. Rift Missions é o nome de trabalho do sistema; o nome final de cada destino e do altar no mapa ainda pode ser definido.

### Estrutura do loop

1. Iniciar uma expedição com Looker e Anabel no altar.
2. Enfrentar cinco treinadores em sequência, escolhidos aleatoriamente de pools apropriados.
3. O quinto treinador deve ter uma associação temática com o lendário da expedição.
4. Enfrentar uma boss battle contra o lendário, com possibilidade de captura.
5. Retornar à base e iniciar outra expedição quando desejar.

A relação entre treinador e lendário não precisa ser exclusiva nem individual. Os exemplos definidos são Misty associada a Kyogre e Giovanni podendo anteceder Mewtwo ou Genesect. Cada batalha deve ter uma frase contextual; o texto e os pools serão desenvolvidos depois.

Lendários já capturados continuam elegíveis. O loop é infinito e permite capturar novas cópias, inclusive para procurar IVs melhores. Não aplicar um filtro que limite encontros a espécies ainda não capturadas.

O objetivo anterior de ampla disponibilidade de lendários permanece como direção para o pool, mas a lista exata de espécies, formas, míticos e Ultra Beasts elegíveis exige uma tabela própria. Não presumir que todas as formas temporárias são capturas independentes.

O horário não deve restringir o loop: dia e noite controlam a apresentação visual do altar. Navio e Fly mantêm o acesso fácil. A venda de Beast Balls por Anabel acompanha sua mudança para a base final.

## 11. Regras de continuidade e recuperação

Estas são diretrizes de execução para preservar a intenção do design, não sistemas adicionais de progressão.

- Distinguir encontro apresentado, batalha vencida, Pokémon capturado, missão resolvida e relatório entregue.
- Não apagar progresso concluído ao perder uma batalha posterior.
- Oferecer nova tentativa quando uma captura necessária não acontece.
- Não repetir presentes de história, como o Mystery Egg, o SquirtBottle e a Eviolite, por sair e entrar no mapa.
- Manter retorno seguro do altar e das expedições.
- Não exigir Solgaleo ou Lunala novamente a cada expedição depois de liberar o sistema.
- Evitar cenas repetidas ou diálogos longos obrigatórios em viagens e runs posteriores.
- Manter os gatilhos de Whitney, Clair e da Liga compatíveis com a campanha existente.
- O alvo é uma campanha iniciada em New Game. Compatibilidade e migração de saves antigos estão fora de escopo por decisão do autor.

## 12. Escopo técnico e assets

O projeto é uma ROM GBA de SoulGold. A execução deve verificar primeiro os sistemas locais de quests, encontros especiais, batalhas com aliado, bosses, navios, Fly, horário e persistência. Reutilizar mecanismos adequados é preferível a introduzir sistemas paralelos sem necessidade.

Já houve trabalho visual na conversa para sprites de Lillie, Gladion, Lusamine, Kukui e Looker, além de referências de Anabel. A existência dos arquivos não comprova integração na ROM. Sprites e tilesets precisam passar pela conversão e validação exigidas pelo projeto, incluindo transparência, paletas e dimensões.

O elenco recorrente e o altar compartilhado favorecem reutilização de assets. Não há orçamento de memória atualizado confirmado neste documento; medir ROM, EWRAM e IWRAM na árvore local durante a implementação. Os valores antigos discutidos não são um orçamento garantido para esta versão.

## 13. Decisões substituídas ou não confirmadas

| Ideia anterior | Situação vigente |
| --- | --- |
| Quatro missões completas de Ultra Beasts antes da E4 | Substituída: apenas o incidente duplo de Blackthorn ocorre antes da E4. |
| Escritório em local indefinido ou Goldenrod | Substituída por Olivine. |
| Revelação de Anabel | Ela já sabe ser Faller; conta sua história ao jogador na reunião antes do navio. |
| Gladion ligado ao choro de Whitney | Substituído pela batalha e entrega do ovo em Violet. |
| Assistente de Elm entrega o ovo | Substituído por Gladion; revisar ligação de Violet e indicação da Route 32. |
| Lillie em Goldenrod | Revanche no evento do SquirtBottle; ela própria entrega o item. As alternativas de Torre e saída do ginásio foram substituídas. |
| Altares do Sol, Lua e Eclipse em locais separados | Substituída por um único local com estados diferentes. |
| Sol à noite e Lua de dia | Corrigida: visual do Sol de dia e da Lua à noite, sem capturas nesses horários. |
| Blacephalon com Lillie e Stakataka com Gladion | Substituída: ambas as missões têm Kukui em destaque. |
| Kartana duplicada na lista | Corrigida: uma missão de Kartana em Kitakami, com Lusamine. |
| Hoopa como centro da história | Não faz parte deste design. |
| Lillie entregar Cosmog cedo | Substituída pelo Mystery Egg de Cosmog em Violet. |
| Capturar Solgaleo e Lunala no altar | Removida: Looker exige apenas um dos dois no time após as nove missões. |
| Presente de Cosmoem no altar | Removido. |
| Evolução automática no altar | Rejeitada: evolução normal antes de Looker liberar a expedição. |
| Cena separada de Togepi/Shiny Stone | Removida; Elm apresenta Cosmog e entrega Eviolite. |
| Suporte a saves antigos | Fora de escopo; trabalhar para New Game. |
| Troca de formas de Solgaleo/Lunala nos altares | Não faz parte da versão atual. |
| Apenas lendários ainda não capturados no loop | Rejeitada: capturas repetidas são parte do objetivo. |
| Gladion entregar Type: Null | Ideia anterior não reafirmada na versão final; não implementar automaticamente. |

## 14. Detalhes a fechar antes de executar cada etapa

O desenho geral está fechado. As pendências abaixo completam a implementação sem alterar sua estrutura.

| Tema | Detalhe pendente |
| --- | --- |
| Escritório | Edifício e coordenadas em Olivine; presença dos NPCs antes e depois da história. |
| Campanha | Gatilhos exatos, resultado de derrota e equipes; apenas o Vulpix inicial tem nível definido. |
| Lillie em Goldenrod | Conferir requisitos atuais do SquirtBottle, estados reutilizáveis, equipe, coordenadas e movimentos na floricultura. |
| Blackthorn | Posição na sequência de eventos e suporte real à batalha com aliado contra duas Ultra Beasts. |
| Missões | Objetivos locais, diálogos, pontos de encontro, níveis e parâmetros de boss. |
| Capturas | Condição de conclusão da missão e mecanismo de revanche/recuperação. |
| Beast Balls | Preço, estoque e eventual entrega inicial; nenhum valor está fechado. |
| Altar | Localização, nome no mapa, embarque, desembarque e ponto de Fly. |
| Solgaleo/Lunala | Implementar a checagem de qualquer um no time; verificar a evolução normal no código. |
| Necrozma | Equipe de Lusamine, sequência de travessia, regras de boss, captura e forma armazenada. |
| Despedida | Diálogos e posição final dos personagens além de Looker e Anabel. |
| Loop | Pools de treinadores/lendários, equipes, níveis, cura, itens, derrota, saída e eventual recompensa adicional. |
| Conteúdo total | Disponibilidade de Type: Null e Poipole/Naganadel fora desta sequência; auditar antes de adicionar fontes. |
| Texto | Idioma final dos diálogos e nomes exibidos. |

## 15. Critérios de aceite do design implementado

- [ ] Encontros de campanha preservam os personagens, locais e motivações definidos.
- [ ] Vulpix de Alola da primeira Lillie está no nível 7; ela se aproxima antes da batalha e as entregas ocorrem depois da vitória.
- [ ] Mystery Egg recebido em Violet nasce como Cosmog.
- [ ] Elm aceita a família de Cosmog no time e entrega Eviolite uma única vez, reutilizando os estados existentes.
- [ ] O arco se desenvolve em paralelo à campanha de Johto, preservando suas motivações e conclusão próprias.
- [ ] Aquecimento de Gladion na Liga pode ser recusado.
- [ ] Gladion usa um novo Type: Null em Violet e Blackthorn; o parceiro anterior não foi regredido.
- [ ] Na Liga e no pós-E4, esse novo parceiro aparece como Silvally, mesmo se a batalha opcional for recusada.
- [ ] A apresentação de Silvally precede o convite de aquecimento e não cria exigência adicional de vitória.
- [ ] Gladion substitui o assistente na entrega de Violet, com batalha obrigatória anterior ao ovo e falas de encaminhamento atualizadas.
- [ ] O antigo encontro de Gladion com Whitney foi removido do roteiro.
- [ ] Lillie realiza a revanche e entrega o SquirtBottle no evento da floricultura, preservando os requisitos da entrega.
- [ ] Falha na entrega não repete a vitória; a antiga NPC não entrega outra cópia do item.
- [ ] Diálogos seguem o guia de voz; diferenças entre SM, USUM e adaptações próprias permanecem explícitas.
- [ ] Blackthorn contém a batalha jogador + Gladion contra Buzzwole + Pheromosa e a participação de Looker.
- [ ] Escritório de Olivine inicia a sequência somente após a E4.
- [ ] Nove missões seguem a ordem e os acompanhantes da tabela, com Looker em todas.
- [ ] Há retorno ao escritório após cada missão e venda de Beast Balls desde o começo.
- [ ] Após Nihilego e apresentação de Solgaleo OU Lunala no time, a reunião libera o navio.
- [ ] Cosmog/Cosmoem não liberam a expedição; a ausência da evolução não impede as nove missões.
- [ ] Primeira visita desbloqueia Fly; navio permanece disponível nos dois sentidos.
- [ ] Existe apenas um altar físico, com visual diurno/noturno e sem capturas de Solgaleo/Lunala.
- [ ] Um dos dois lendários permite abrir o portal em qualquer horário.
- [ ] Não há presente de Cosmoem nem evolução automática no altar.
- [ ] Lusamine é enfrentada apenas uma vez na história, perto da travessia final.
- [ ] Necrozma pode ser obtido e falhas não bloqueiam permanentemente sua captura.
- [ ] Despedida deixa Looker e Anabel no altar.
- [ ] Anabel revela sua condição de Faller na reunião anterior ao navio, sem uma flag exclusiva.
- [ ] Sua decisão de permanecer no altar inclui a motivação pessoal de ajudar outros deslocados.
- [ ] Expedições têm cinco treinadores e um boss lendário capturável.
- [ ] Quinto treinador tem associação temática com o lendário e as batalhas possuem frases contextuais.
- [ ] Lendários já capturados continuam disponíveis para repetição e busca de IVs.
- [ ] Acesso ao loop funciona em qualquer horário.
- [ ] Memória, assets e persistência são validados na ROM local, sem presumir suporte pelo design.

## 16. Entrega por etapas

Uma divisão prática de implementação é: encontros de campanha; escritório e progressão das nove missões; expedição/navio/Fly/altar; clímax e despedida; loop repetível. Cada etapa deve entregar seus gatilhos, textos, batalhas e recuperação de falhas de forma verificável antes da próxima.

Esta divisão é uma recomendação de produção. Não autoriza alterar o elenco, a ordem das missões, a condição de evolução exigida por Looker ou a estrutura do loop.
