# SoulGold — Rift Missions

**Design consolidado v12 — parceiros fora da Poké Ball, Dragon’s Den refinado e arco pré-Liga consolidado**

Revisão: 16 de setembro de 2026. Substitui o V12; preserva a política de duelos narrativos, o encontro de Gladion antes da Victory Road, o arco pós-game e o loop pós-Necrozma, e refaz integralmente o Dragon’s Den para que Lillie participe do mesmo teste do Elder e reaja às escolhas do jogador.

## 1. Objetivo e autoridade deste documento

Rift Missions é uma história adicional de SoulGold que apresenta personagens de Alola durante a campanha de Johto, desenvolve uma investigação de Ultra Beasts após a Elite Four e termina em um sistema permanente de expedições com batalhas e capturas de lendários.

Este documento consolida as decisões mais recentes da conversa. Gladion em Violet, Lillie em Goldenrod e Gladion em Cianwood já possuíam implementação confirmada pelo autor, mas o V12 mantém o contrato de resultado de algumas dessas cenas; portanto, comportamento antigo incompatível deve ser refatorado sem reconstruir desnecessariamente equipes, mapas ou parâmetros já integrados. Lillie no Dragon’s Den e Gladion antes da Victory Road estão fechados em design, mas não são declarados implementados ou testados nesta revisão. O repositório público pode não refletir as alterações locais do projeto.

As seções de conteúdo estabelecido são a referência para a execução. Recomendações técnicas e pendências são identificadas separadamente; não devem ser confundidas com novas decisões aprovadas. As fontes dos jogos contextualizam a inspiração; o estado vigente de cada personagem neste documento governa os diálogos do hack.

### Status e precedência

| Conteúdo | Status nesta revisão |
| --- | --- |
| Lillie inicial / Route 30 | Cena existente; V12 mantém a derrota para continuidade sem blackout. Refatoração de resultado pendente. |
| Gladion em Violet | Implementado anteriormente; V12 passa a aceitar vitória **ou derrota** antes da entrega do Mystery Egg. Refatoração de resultado pendente. |
| Lillie em Goldenrod | Implementada e já compatível com a política V12 de vitória/derrota sem blackout. |
| Gladion em Cianwood | Implementado anteriormente; V12 mantém removida a recusa da revanche. A batalha passa a ser obrigatória e vitória/derrota convergem para Fly. Refatoração de fluxo pendente. |
| Lillie no Dragon’s Den | Design V12: Lillie acompanha as cinco perguntas vanilla com Alolan Ninetales visível fora da Poké Ball, reage a cada escolha do jogador em branches locais e dá sua própria resposta; a batalha final conclui em vitória ou derrota sem blackout. Implementação e validação pendentes. |
| Gladion antes da Victory Road | Novo encontro fechado em design: batalha obrigatória, primeira apresentação de Silvally, vitória ou derrota continuam sem blackout. Implementação pendente. |
| Incidente de Blackthorn | Pós-game; primeira batalha de ameaça da questline e início da política normal de derrota/blackout/retry. |
| Limpeza de treinadores | Informada como concluída pelo autor; este documento não certifica IDs ou contagens livres. |
| Restante das Rift Missions | Design estabelecido ou pendência explicitamente indicada; não presumir implementação. |

As decisões mais recentes prevalecem sobre trechos antigos. Nos **duelos narrativos com treinadores**, a luta pode ser obrigatória, mas a vitória não é requisito de progresso: vitória ou derrota recebem falas próprias e convergem sem blackout. Menus de recusa deixam de ser usados nos encontros de campanha aqui definidos. A primeira falha tratada como derrota real de uma ameaça ocorre contra Ultra Beasts em Blackthorn; encontros de ameaça posteriores seguem sua própria recuperação. A política de dificuldade única baseada no antigo Hard permanece vigente.

O documento é autossuficiente para o design. Não exigir leitura dos refinamentos antigos para compreender as cenas aqui consolidadas. As referências externas são herdadas do V7 e do refinamento de Lillie; não representam nova pesquisa nesta revisão.

### Política V12 — duelo narrativo não é gate de vitória

Os encontros de Lillie, Gladion e outros personagens usados para desenvolvimento narrativo são conteúdo bônus integrado à jornada. Neles, **a batalha precisa acontecer quando o roteiro a prevê, mas o jogador não precisa vencer para a história continuar**.

Contrato padrão para duelo narrativo:

1. Curar quando a cena exigir igualdade de condições.
2. Ativar o mecanismo de batalha sem blackout/whiteout.
3. Executar a batalha obrigatória; não oferecer opção de recusa nos encontros definidos pelo V12.
4. Capturar o resultado imediatamente ao retornar da batalha, antes de qualquer cura ou comando que possa sobrescrever variáveis especiais.
5. Usar diálogo próprio para vitória e derrota. Nunca reescrever uma derrota como vitória do jogador.
6. Curar novamente quando apropriado.
7. Fazer os branches convergirem para a mesma entrega, despedida ou continuação da campanha.
8. Marcar progresso pelo estado real do evento/recompensa, não pela flag de `trainer defeated`, quando a derrota também conclui a cena.

Essa política se aplica às lutas de personagem da campanha: Lillie na abertura, Gladion em Violet, Lillie em Goldenrod, Gladion em Cianwood, Lillie no Dragon’s Den e Gladion antes da Victory Road. Também se aplica a confrontos de personagem posteriores quando o objetivo narrativo é a conversa/decisão, como a batalha com Lusamine no clímax, salvo decisão posterior explícita.

**Batalhas de ameaça são diferentes.** A partir do incidente pós-game de Blackthorn, Ultra Beasts, Ultra Necrozma e bosses capturáveis não são simples duelos de relacionamento. Derrota pode usar blackout/retorno seguro e exigir nova tentativa, porque a ameaça continua sem resolução. Isso não autoriza perda permanente de Pokémon únicos ou softlock. O loop repetível e eventuais gauntlets de treinadores possuem regras próprias e não herdam automaticamente a política de duelos narrativos apenas por serem batalhas contra treinadores.

Empate, desistência ou resultados especiais, se o engine os expuser, precisam de tratamento explícito. Não convertê-los silenciosamente em vitória; também não provocar blackout por acidente em uma cena marcada como duelo narrativo.

### Direção narrativa: uma história que acontece em paralelo

O arco de Alola se desenvolve ao mesmo tempo que a jornada pelos ginásios de Johto. Lillie está aprendendo a ser treinadora, Gladion viaja e desafia o jogador, Kukui pesquisa formas regionais e Looker e Anabel investigam acontecimentos que ainda não são plenamente compreendidos. Eles têm motivos próprios para estar na região e reaparecem em momentos naturais da viagem.

A campanha de Johto mantém seu próprio conflito e sua conclusão. Os encontros recorrentes e o crescimento do Cosmog constroem o arco dos personagens durante a jornada, mas a primeira ruptura explícita das Rift Missions fica para depois da Liga. O incidente de Blackthorn funciona como prólogo da investigação pós-game, não como evento pré-E4. Não atribuir todos os acontecimentos de Johto a Necrozma nem transformar cada encontro em uma explicação sobre portais.

O efeito desejado é um mundo maior e em movimento: o jogador cruza caminhos com outras pessoas, acompanha suas mudanças e, no final, reúne aliados que conheceu ao longo da jornada. Cosmog conecta o início íntimo dessa relação à escala do desfecho no altar.

### Regra visual de parceiros recorrentes

Nos encontros de campanha e nas cenas narrativas em que estão presentes, os parceiros principais de Gladion e Lillie devem aparecer **fora da Poké Ball**, acompanhando seus Trainers no mapa sempre que a cena permitir sem quebrar colisão, follower, warps ou limites de objetos.

- **Gladion:** Type: Null permanece fora da Poké Ball em Violet e Cianwood. Depois da evolução, **Silvally continua fora da Poké Ball em todas as aparições narrativas posteriores de Gladion**, incluindo Victory Road, Blackthorn, suas Rift Missions, reunião e clímax quando ele estiver presente.
- **Lillie:** Alolan Vulpix permanece fora da Poké Ball em seus encontros iniciais e em Goldenrod. No Dragon’s Den, ela já aparece como **Alolan Ninetales**. A partir daí, **Ninetales continua fora da Poké Ball em todas as aparições narrativas posteriores de Lillie**, incluindo Pheromosa, Celesteela, Guzzlord, reunião e clímax quando ela estiver presente.
- Essa regra é visual e narrativa; não exige sistema de follower genérico nem altera quem inicia cada batalha.
- Quando a cena começar, o parceiro deve estar posicionado de forma coerente ao lado do Trainer. Quando a cena terminar, ambos devem sair ou ser ocultados de forma coordenada quando aplicável.
- Se um mapa específico não comportar o objeto extra sem conflito técnico real, a implementação deve registrar a limitação e preservar a intenção por outro meio de encenação, sem simplesmente remover o parceiro por conveniência.


## 2. Estrutura geral

1. Apresentar Lillie, Gladion e Kukui durante a campanha normal; receber o Mystery Egg de Cosmog em Violet, o SquirtBottle com Lillie em Goldenrod e Fly com Gladion em Cianwood; concluir o arco pré-Liga de Lillie no Dragon’s Den após Clair.
2. Antes de entrar na Victory Road, reencontrar Gladion. Ele apresenta Silvally e ocorre uma batalha obrigatória que avança tanto em vitória quanto em derrota, sem blackout.
3. Concluir Victory Road e a Liga normalmente, sem ruptura de Ultra Beast obrigatória antes da E4.
4. No pós-game, mostrar a primeira ruptura explícita em Blackthorn, com Buzzwole e Pheromosa em batalha dupla ao lado de Gladion e com participação de Looker. A partir daqui derrotas contra ameaças podem usar blackout/retry.
5. Ao final do incidente, Looker encaminha o jogador ao escritório de Olivine; essa visita inicia formalmente a sequência das nove Rift Missions.
6. Concluir nove missões consecutivas de Ultra Beasts, retornando ao escritório após cada uma.
7. Após as nove missões, apresentar Solgaleo **ou** Lunala a Looker para liberar a reunião e o navio.
8. Viajar ao altar com o parceiro evoluído do Mystery Egg para abrir a passagem até Necrozma.
9. Encenar o clímax conhecido como Eclipse no mesmo altar, resolver o conflito com Lusamine e enfrentar Ultra Necrozma.
10. Encerrar a história com uma despedida e manter Looker e Anabel no altar para expedições repetíveis.

Todo o conteúdo explícito de Ultra Beasts desta questline fica no pós-E4, incluindo Blackthorn. O incidente é um prólogo especial da investigação e não conta entre as nove missões consecutivas. Isso não instrui remover fontes de Pokémon já existentes em outros sistemas do jogo.

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

Viaja com a mãe e está se encontrando como treinadora. Sua progressão pré-Liga possui três estágios claros: na Route 30 começa a batalhar; em Goldenrod aprende a observar sua parceira e adaptar um plano; no Dragon’s Den participa do mesmo teste do jogador, escuta respostas diferentes das suas e demonstra que consegue considerar outra perspectiva sem abandonar o próprio julgamento. **Vulpix acompanha Lillie fora da Poké Ball nos encontros anteriores; no Dragon’s Den, a parceira já evoluiu para Alolan Ninetales e continua visível ao lado dela. Ninetales permanece fora da Poké Ball também nas aparições pós-game de Lillie.** Atua depois nas missões de Pheromosa, Celesteela e Guzzlord.

No Dragon’s Den, o jogador não escolhe as respostas de Lillie. O Elder faz ao protagonista as cinco perguntas do teste vanilla; depois de cada escolha, Lillie reage ao que ouviu e formula sua própria posição. Ela pode concordar, discordar ou aceitar parte do raciocínio sem copiar o jogador. A cena não deve transformar sua independência em hostilidade à família: seu crescimento é demonstrado justamente pela capacidade de ouvir sem entregar o próprio julgamento.

Ela não entrega Cosmog nem Cosmoem. O jogador recebe Cosmog pelo Mystery Egg em Violet e o desenvolve ao longo da jornada.

### Gladion

Age como um rival recorrente ao longo da história, alternando desafios e cooperação. Sua primeira batalha ocorre no Pokémon Center de Violet, onde substitui o assistente de Elm e entrega o Mystery Egg após a batalha, independentemente de vitória ou derrota do jogador. Reaparece em Cianwood após Chuck, enfrenta o jogador novamente e assume a entrega de Fly; a revanche deixa de ser opcional no V12. Antes da Victory Road, apresenta Silvally e trava a última batalha de rival da campanha, também com continuidade em vitória ou derrota. No pós-game luta ao lado do jogador em Blackthorn e participa das missões de Buzzwole, Xurkitree e Guzzlord. O antigo encontro ligado à Whitney e o antigo aquecimento opcional na entrada da Liga foram removidos.

#### Novo parceiro de Gladion

Gladion encontrou outro Type: Null abandonado em Alola, acolheu-o e o trouxe para sua jornada por Johto. Ele está treinando esse novo parceiro e construindo uma relação de confiança. **Type: Null deve acompanhar Gladion fora da Poké Ball em seus encontros de Violet e Cianwood; após evoluir, Silvally assume a mesma presença visual em todas as aparições seguintes de Gladion.** Esta origem é uma adição autoral do hack à continuidade híbrida SM/USUM.

O Silvally de sua jornada anterior continua existindo na história. O Type: Null atual é outro indivíduo: não houve regressão do parceiro original. Não é necessário explicar nesta trama onde está cada integrante de sua equipe anterior. O responsável pelo abandono e a procedência específica deste novo Type: Null ficam em aberto, sem criar outra investigação obrigatória.

Gladion continua sendo um treinador experiente. Seu objetivo nesta viagem é dar ao parceiro espaço para aprender, confiar e agir por iniciativa própria. As primeiras batalhas usam uma equipe em desenvolvimento, mantendo desafios possíveis para a etapa sem apagar sua experiência. Gladion deve funcionar como boss; equipe em desenvolvimento não significa batalha trivial. Preservar a equipe implementada em Violet e balancear o novo encontro separadamente.

| Etapa | Parceiro | Desenvolvimento narrativo |
| --- | --- | --- |
| Violet, antes da entrega do ovo | Type: Null | Está se acostumando a Gladion e a batalhar contra outros treinadores; o resultado não bloqueia a entrega. |
| Cianwood, entrega de Fly após Chuck | Type: Null | Explora a praia e toma a iniciativa de partir; a batalha obrigatória mostra a parceria em crescimento. |
| Antes da Victory Road | Silvally | A evolução é revelada. Silvally já toma a iniciativa, materializando o progresso construído desde Violet. |
| Blackthorn, dupla pós-game contra as Ultra Beasts | Silvally | O parceiro já evoluído coopera com o jogador; a relação consolidada aparece sob pressão real. |
| Missões pós-E4 | Silvally | Mantém a evolução e a relação consolidada. |

A evolução acontece na jornada de Gladion entre Cianwood e a Victory Road. Não depende de vencer o jogador em nenhuma batalha anterior. A primeira apresentação explícita de Silvally ocorre no encontro anterior à Victory Road; portanto, Blackthorn já usa Silvally. Não exige uma cutscene de evolução ou nova flag: as equipes de cada encontro podem representar os estágios previstos. Níveis, golpes, itens, demais membros e Memórias ainda precisam de balanceamento.

**Sequência de diálogo para implementação:**

1. Em Violet, depois de mencionar Lillie e antes do desafio, Gladion apresenta brevemente Type: Null. Após qualquer resultado válido da batalha, reconhece algo observado e entrega o ovo.
2. Em Cianwood, o diálogo sobre Johto e Lillie mostra Gladion vivendo sua própria viagem; a batalha acontece sem menu de recusa e Type: Null sai na frente na despedida.
3. Antes da Victory Road, Gladion apresenta Silvally antes da luta. A evolução precisa ser vista mesmo se o jogador perder; não depende de resultado anterior.
4. Em Blackthorn, já no pós-game, uma instrução curta mostra a parceria consolidada entre Gladion e Silvally, sem repetir a história do abandono.

**Falas originais propostas em inglês:**

> Violet, apresentação: “I found this Type: Null in Alola. Someone had left it behind. It's traveling with me now.”
>
> Antes do desafio: “We're still getting used to each other. A battle with someone new should help.”
>
> Após a batalha: “You saw that? It made that move on its own. That's progress.”
>
> Victory Road: “Remember the Type: Null you met in Violet? Take a look. It used to wait for me to decide everything. Now it takes the first step.”
>
> Blackthorn: “Silvally, stay with me. We'll cover them.”

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

Em Violet, a menção a Lillie explica sua curiosidade; a entrega mostra responsabilidade independentemente do resultado. Em Cianwood, fala de Lillie e da própria viagem, e acompanha a iniciativa do parceiro na despedida. Antes da Victory Road, apresenta Silvally e busca uma última comparação entre os dois treinadores; a luta é obrigatória no roteiro, mas não funciona como permissão para passar. Na dupla pós-game de Blackthorn, ele divide tarefas com o jogador já ao lado de Silvally. Sua preocupação com Lillie não lhe dá autoridade para escolher por ela.

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

**Continuidade visual dos parceiros:** quando Lillie participa de Pheromosa, Celesteela ou Guzzlord, Alolan Ninetales deve estar presente fora da Poké Ball ao lado dela. Quando Gladion participa de Buzzwole, Xurkitree ou Guzzlord, Silvally deve estar presente fora da Poké Ball ao lado dele. A batalha específica da missão pode usar outros membros da equipe; a presença overworld do parceiro principal continua sendo parte da identidade visual da cena.

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
| Primeira batalha de Lillie | Recebimento da Pokédex | Batalha obrigatória com Alolan Vulpix nível 7; vitória ou derrota continuam a cena sem blackout. |
| Gladion em Violet | Ligação de Elm e entrega do Mystery Egg no Pokémon Center | Substitui o assistente; batalha obrigatória antes do ovo; vitória ou derrota permitem a entrega. |
| Lillie em Goldenrod | Evento de entrega do SquirtBottle, após Whitney | Cena automática; batalha obrigatória com continuidade em vitória ou derrota, entrega e saída pela porta. |
| Gladion em Cianwood | Entrega existente de Fly, após Chuck | Conversa sobre Johto/Lillie, batalha obrigatória e Fly em vitória ou derrota; Type: Null sai na frente. |
| Lillie no Dragon’s Den | Depois de derrotar Clair, durante o teste de perguntas | Lillie acompanha as cinco perguntas vanilla, reage às escolhas do jogador e responde por si mesma; o Elder encerra com uma demonstração prática. Vitória ou derrota concluem sem blackout. |
| Gladion antes da Victory Road | Imediatamente antes do acesso à Victory Road | Primeira apresentação de Silvally; batalha obrigatória, sem menu de recusa, com continuidade em vitória ou derrota. Gladion não é gate de acesso. |
| Incidente de Blackthorn | Pós-game, após concluir a E4 | Primeira ruptura explícita: jogador e Gladion/Silvally enfrentam Buzzwole + Pheromosa; derrota é falha real e pode usar blackout/retry. Looker encaminha o jogador para Olivine após resolução. |

A ordem pré-Liga fica: **Route 30 → Violet → Goldenrod → Cianwood → Dragon’s Den → Gladion antes da Victory Road → Victory Road → Liga**. A ordem lista apenas os encontros desta questline, não todos os eventos vanilla entre eles. Não existe mais batalha opcional de Gladion na entrada da Liga.

Depois da E4: **Blackthorn → escritório de Olivine → nove missões → reunião/altar → Lusamine → Ultra Necrozma**.

**Diretriz para Blackthorn:** o incidente abre a trama pós-game e é o primeiro confronto em que derrota deixa de ser apenas um resultado de personagem. Ele não conta como uma das nove missões e não deve oferecer captura antecipada de Buzzwole ou Pheromosa. A implementação precisa restringir explicitamente a captura desse encontro. O formato exato da batalha com aliado depende de verificação do engine.

### Política de resultados por encontro

| Encontro | Escolha antes da luta | Derrota do jogador | Conclusão |
| --- | --- | --- | --- |
| Lillie inicial, Route 30 | Não; batalha obrigatória | Sem blackout; fala própria e continuação | Pokédex/Mystery Egg e demais entregas seguem normalmente |
| Gladion, Violet | Não; batalha obrigatória | Sem blackout; fala própria e continuação | Mystery Egg entregue se houver espaço em party/PC |
| Lillie, Goldenrod | Não; batalha obrigatória | Sem blackout; fala própria e cura | SquirtBottle entregue |
| Gladion, Cianwood | Não; batalha obrigatória | Sem blackout; fala própria e cura | Fly entregue |
| Lillie, Dragon’s Den | Não; batalha obrigatória | Sem blackout; Elder avalia a demonstração e a cena continua | Retorna ao fluxo original de Clair em qualquer resultado |
| Gladion, Victory Road | Não; batalha obrigatória | Sem blackout; fala própria e cura | Gladion se despede e Victory Road permanece acessível |
| Blackthorn / Ultra Beasts | Não; confronto de ameaça | Blackout/retorno seguro e retry conforme implementação | Só avança quando a ameaça for resolvida |
| Lusamine, clímax | Não; confronto de personagem | Sem blackout; fala própria e continuação do conflito | Ambos os resultados conduzem à aceitação do plano coletivo |
| Ultra Necrozma | Boss de ameaça | Blackout/retorno seguro e retry | Só conclui após resolução; captura não pode ficar perdida para sempre |

A flag automática de trainer vencido não deve ser usada como único estado de conclusão nos duelos narrativos, porque derrota também é um resultado válido. O evento precisa registrar que **a batalha ocorreu e a cena avançou**, não que o jogador necessariamente venceu.

### 4.1. Oak, Kukui e Lillie — abertura da jornada

Kukui substitui o papel do antigo NPC de Mr. Pokémon na sala e permanece como pesquisador no local. Oak mantém sua função de apresentar e entregar a Pokédex. As posições já ajustadas pelo autor devem ser respeitadas: Kukui ao lado de Oak; somente Lillie começa na cadeira. Não reposicionar os três juntos.

Sequência de encenação:

1. Kukui recebe o jogador e identifica a visita enviada por Elm.
2. Oak participa cedo da conversa, reconhecendo o jogador e observando seu Pokémon. Evitar deixá-lo sem reação durante uma longa apresentação.
3. Kukui contextualiza sua viagem por Kanto e o interesse nas formas de Alola vistas em Johto.
4. Lillie reage da cadeira, se apresenta e se aproxima fisicamente do jogador por um caminho livre. **Alolan Vulpix deve estar fora da Poké Ball e acompanhá-la visualmente na cena**, mantendo posição segura ao lado dela. Lillie deve parar perto do jogador e ambos se encarar antes do desafio.
5. Lillie desafia o jogador com Alolan Vulpix nível 7. A batalha ocorre antes de qualquer entrega de item ou Pokédex dessa cena. Curar se necessário e usar batalha sem blackout.
6. Capturar o resultado imediatamente ao retornar. Em vitória do jogador, Lillie reconhece o que ainda precisa aprender; em derrota do jogador, ela comemora sua primeira vitória sem transformar o momento em humilhação ou gate. Ambos os resultados são válidos.
7. Curar após a batalha quando necessário e convergir para a mesma continuação: Kukui entrega o Mystery Egg destinado a Elm e Oak conclui a apresentação e entrega da Pokédex.
8. Oak se despede para seu programa de rádio em Goldenrod e sai.
9. Lillie diz que sua mãe está esperando e sai caminhando até a saída. Kukui permanece na sala e oferece o suporte de cura previsto no evento.
10. Concluir as mudanças de estado da campanha somente após as entregas necessárias, preservando os eventos seguintes de Elm e Silver. Não usar vitória contra Lillie como requisito persistente dessa progressão.

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

### 4.5. Gladion em Violet — sequência vigente

**Status:** a cena já existe no projeto, mas o V12 altera o contrato de derrota. Preservar mapa, equipe e entrega implementados; refatorar apenas o necessário para remover blackout/retry por derrota e permitir que ambos os resultados cheguem ao ovo.

1. A ligação de Elm informa que Gladion passou pelo laboratório e aceitou levar o ovo a Violet. Elm pede ao jogador que o encontre no Pokémon Center.
2. O evento de aparição antes usado pelo assistente passa a apresentar Gladion. A entrega não exige que o assistente desapareça do laboratório por motivo narrativo novo.
3. Gladion confirma o nome do jogador. Lillie lhe contou sobre a batalha inicial e seu desejo de tentar novamente.
4. Gladion confirma que trouxe o ovo e inicia uma batalha para conhecer o estilo do jogador. Ele não alega que Elm condicionou a entrega ao resultado.
5. Antes do confronto, verificar espaço na party OU no PC para o ovo. Se ambos estiverem lotados, não iniciar batalha nem marcar progresso. Curar e iniciar a batalha obrigatória em modo sem blackout.
6. Ao retornar, salvar o resultado antes da cura. Vitória e derrota possuem falas diferentes, mas convergem para a entrega. Não oferecer retry apenas porque o jogador perdeu.
7. Entregar Cosmog Egg na party quando houver espaço; caso contrário, usar o PC conforme o suporte implementado. Confirmar sucesso antes de marcar o estado de recebimento.
8. Se a entrega falhar excepcionalmente depois da batalha, retomar somente a entrega; nunca exigir repetir o duelo para obter o ovo.
9. Gladion se despede e sai. O recebimento do ovo libera o bloqueio correspondente da Route 32.

**Falas originais propostas em inglês:**

> Elm: “{PLAYER}, I've asked a Trainer named Gladion to bring you the Egg. He was heading to Violet City. Meet him at the Pokémon Center, would you?”
>
> Gladion: “You're {PLAYER}? Lillie mentioned you. She's already planning your next battle. Before that, let me see how you fight.”
>
> Se o jogador vencer: “All right. I see why she wants another match.”
>
> Se Gladion vencer: “Your Pokémon kept looking for a way through. That's enough for me to understand how you fight.”
>
> Gladion, convergência: “Here's the Egg. Elm asked me to bring it to you. Take care of it.”
>
> Despedida: “And when Lillie challenges you again... give her a proper battle.”

Ele não sabe automaticamente qual espécie está dentro do ovo. A entrega é um favor plausível durante sua viagem, não um emprego como assistente de Elm. A batalha é parte da relação com o jogador; **o ovo nunca é prêmio por vitória**.

### 4.6. Lillie em Goldenrod — evento implementado e refinamento consolidado

**Status:** implementado conforme informado pelo autor. Os detalhes abaixo registram o refinamento aprovado; não constituem uma nova certificação de build ou testes do checkout.

#### Regras e sequência

1. Após Whitney, ao entrar na floricultura com FLAG_RECEIVED_SQUIRTBOTTLE ainda desmarcada, iniciar a cena automática. Preservar os demais requisitos existentes da entrega.
2. Lillie conversa com a dona; percebe o jogador, vira, mostra exclamação e se aproxima. Usar MUS_HG_LYRA no reencontro e no retorno da batalha.
3. **Alolan Vulpix permanece fora da Poké Ball durante a cena**, posicionada próxima de Lillie sem bloquear balcão, flores, saída, follower ou movimentos. Quando Lillie caminha até a porta no encerramento, Vulpix sai junto ou é removida de forma sincronizada.
4. O diálogo conecta a viagem em Johto, observações em Ilex Forest, Vulpix e o encontro anterior com Gladion e seu novo Type: Null. Não presumir que o ovo chocou ou quem venceu batalhas anteriores.
5. A florista autoriza passar o SquirtBottle ao jogador, que seguirá ao norte. Lillie pretende encontrar a mãe antes de continuar a viagem. O item não é prêmio por vitória.
6. Verificar capacidade para receber ITEM_SQUIRTBOTTLE antes de curar e lutar. Falta de espaço não inicia batalha nem marca progresso.
7. Curar antes do treino. Vitória e derrota permitem continuar, com falas diferentes; sem blackout. Curar novamente após capturar o resultado.
8. Entregar uma unidade; confirmar sucesso antes de marcar FLAG_RECEIVED_SQUIRTBOTTLE.
9. Lillie se despede, caminha até a porta e é removida da cena; restaurar música e controles. A mesma FLAG_RECEIVED_SQUIRTBOTTLE controla sua ausência em visitas futuras. Não criar flag de ocultação.
10. A dona preserva seus demais serviços, inclusive os relacionados a perfume, e não entrega outra cópia. Preservar o evento de Sudowoodo e ajustar apenas encaminhamentos necessários.

**Dificuldade única:** por confirmação do autor, Whitney usa a equipe do antigo Hard como única versão: Maushold, Audino, Cinccino e Miltank, todos nível 27. Não exigir outra consulta para validar essa premissa nem recriar variantes. Lillie mantém Clefairy 28, Ribombee 29, Comfey 28 e Vulpix Alola 29, em batalha simples com Smart Trainer. Vulpix não evolui nesta cena, inclusive por scaling. O objetivo é um desafio superior a Whitney; isso não equivale a afirmar balanceamento comprovado apenas pelos níveis.

#### Roteiro consolidado

Falas abaixo definem conteúdo. O executor deve distribuí-las em caixas curtas, com identificação do falante quando necessário e quebras compatíveis com a fonte. São acontecimentos autorais da viagem em Johto, não fatos canônicos externos.

##### 1. Conversa com a florista

Florista: “It stops people on their way to Ecruteak. A little water makes it wriggle, but nobody wants to get too close.”

Lillie: “Then we shouldn't pull at its branches. If it can move, perhaps we can persuade it to move on its own.”

Florista: “You can take this SquirtBottle. Just be careful, dear.”

Lillie percebe o jogador, vira, mostra !. Começa MUS_HG_LYRA; ela se aproxima.

##### 2. Reencontro e Johto

Lillie: “{PLAYER}! You've been to Whitney's Gym, haven't you? I recognized the Badge.”

Lillie: “I thought traveling would mean getting better at following a map. Then I spent half a morning in Ilex Forest watching which flowers Ribombee visited.”

Lillie: “She kept returning to the sheltered flowers whenever the wind picked up. I was watching the path. She was watching everything around us.”

##### 3. Gladion e o parceiro

Lillie: “Gladion told me he met you in Violet. He said, 'They didn't hesitate.' From him, that's practically a speech.”

Lillie: “And you met the Type: Null traveling with him. He pretends not to fuss over it, but he checks on it whenever he thinks nobody is looking.”

Não presumir que o jogador venceu Gladion com facilidade, que o ovo já chocou, nem confundir este Type: Null com o antigo Silvally. O encontro de Violet já é parte da progressão normal.

##### 4. A razão para entregar o item

Lillie: “Are you heading north? I promised Mother I'd meet her before we leave Goldenrod.”

Lillie, para a dona: “Would it be all right if {PLAYER} took the bottle? We've traveled some of the same roads.”

Florista: “Of course. You may keep it. I'd just like that path clear again!”

Lillie: “Then it's yours. But before you go... could we have another battle? I want to see how much we've learned.”

Checar espaço aqui. Se não houver: “Your Bag looks full. Make room for the bottle first. I'll be here.” Não curar nem lutar; liberar os controles e manter acesso à saída.

##### 5. Desafio

Lillie: “Vulpix and I have been practicing. She's started looking back at me when she sees an opening. I'm learning not to miss it.”

Lillie: “Let's take care of your Pokémon first. And please don't hold back. I won't, either.”

Cura, batalha. Manter Vulpix Alola, a mesma parceira de Route 30, sem evolução nesta cena.

##### 6A. Jogador vence

Texto de derrota da treinadora: “We couldn't quite catch up... but we kept trying!”

Depois: “I spent so long deciding what to do that I missed some of Vulpix's signals. I want to get better at answering her.”

Depois: “I want to try that again someday. After I've worked out a better answer!”

##### 6B. Jogador perde

Lillie: “We did it...? We did! Oh, Vulpix, you were wonderful!”

Lillie: “Sorry! I didn't mean to get carried away. I kept watching Vulpix instead of worrying about every command. That felt different.”

Lillie: “Thank you for taking us seriously. Let's get your Pokémon feeling better.”

Empate usa uma fala própria curta: “That was close for both of us. Let's take a moment to look after everyone.” Forfeit, se o menu permitir, não deve ser chamado de vitória da Lillie: “Of course. We can stop here. Let's look after your Pokémon.”

##### 7. Final comum

Curar o time em todos os resultados. Ler/salvar o resultado antes da cura; ela pode modificar variáveis especiais.

Lillie: “Here, the SquirtBottle, just as we agreed. Try a little water first. Whatever that tree is, there's no need to frighten it.”

giveitem; confirmar sucesso; setflag FLAG_RECEIVED_SQUIRTBOTTLE.

Lillie, virando para a dona: “Thank you for your help. And for letting us borrow a little room!”

Florista: “Just don't make a habit of battling beside my flowers!”

Lillie, para o jogador: “I'd better find Mother. Tell me what happened when we meet again, won't you?”

Jogador abre passagem se necessário. Lillie caminha até a porta e some. Retorna a música normal.

#### Equipe e identidade de batalha

Base canônica: Lillie usa Clefairy em Episode RR e Ribombee/Comfey na Battle Tree de USUM. Vulpix Alola mantém a continuidade autoral já estabelecida no hack; não é apresentada como integrante da equipe canônica de USUM.

Fonte consultada: [Lillie — Pokémon em USUM](https://bulbapedia.bulbagarden.net/wiki/Lillie).

A referência única é Whitney com Maushold, Audino, Cinccino e Miltank, todos Lv.27, conforme a premissa confirmada pelo usuário. Lillie foi proposta para oferecer um desafio maior logo após essa batalha. O teste de balanceamento considera innates, IA e scaling do hack; não é uma nova auditoria da equipe de Whitney nem condição para começar a implementação. Níveis superiores, isoladamente, não comprovam dificuldade superior.

| Ordem | Pokémon | Nível | Item | Ability | Nature | Golpes |
| --- | --- | --- | --- | --- | --- | --- |
| 1 | Clefairy | 28 | Eviolite | Magic Guard | Bold | Reflect, Moonblast, Thunder Wave, Flamethrower |
| 2 | Ribombee | 29 | Sitrus Berry | Shield Dust | Timid | Pollen Puff, Draining Kiss, Psychic, Stun Spore |
| 3 | Comfey | 28 | Sitrus Berry | Triage | Modest | Draining Kiss, Giga Drain, Calm Mind, Synthesis |
| 4 | Vulpix Alola | 29 | Eviolite | Snow Warning | Timid | Aurora Veil, Ice Beam, Icy Wind, Encore |

Todos: IVs 31. Clefairy: 100 HP / 100 Def / 60 SpA. Ribombee: 100 SpA / 100 Spe / 60 HP. Comfey: 100 HP / 100 SpA / 60 Def. Vulpix: 100 HP / 100 Spe / 60 SpA. AI: Smart Trainer. Batalha simples, sem variação de dificuldade, sem itens de cura usados pela treinadora.

Identidade: proteger, observar e responder; não apenas atacar com Pokémon Fairy. Clefairy dá cobertura contra Steel, Ribombee pressiona com velocidade, Comfey oferece sustain e Vulpix exige cuidado com Encore e Aurora Veil. A equipe é vulnerável a Poison/Steel e remoção de telas; não adicionar respostas para tudo. Vulpix é o ás narrativo, sem forçar ordem de troca via script. Validar abilities, innates, golpes e itens nas definições do hack; não mudar dados globais de espécies para esta luta. Conferir se Snow Warning cria hail ou snow nesta configuração.


#### Persistência e recuperação

FLAG_RECEIVED_SQUIRTBOTTLE conserva seu significado de recompensa entregue. Não usar a flag de treinador vencido como conclusão, porque a derrota do jogador também permite a entrega. Não marcar recebimento antes da luta.

Aproximação, resultado e entrega pendente podem usar temporários livres do mapa. Se uma entrega falhar excepcionalmente, repetir somente a entrega na mesma visita. Não prometer persistência desses temporários após troca de mapa/reload; a prevenção principal é verificar capacidade antes da batalha e entregar no mesmo fluxo. Nenhum novo estado persistente está autorizado.

Preservar o estado anterior do controle existente de no-whiteout e restaurá-lo em todas as saídas. Resultado desconhecido não deve ser convertido em vitória. Empate e desistência, se disponíveis, exigem falas próprias e tratamento explícito. Revisar reentrada por bolsa cheia, posicionamento no retorno da batalha, interlocutor da cena automática e colisões com follower.

### 4.7. Gladion em Cianwood — “O caminho de volta”

**Status:** implementado anteriormente conforme informação do autor, mas o V12 altera o fluxo: a opção de recusar a revanche é removida. Preservar equipe, mapa, entrega e soluções técnicas já integradas; refatorar somente o necessário para tornar a batalha obrigatória e manter vitória/derrota como resultados válidos sem blackout.

#### Escopo e gatilho

Substituir a entrega existente de Fly por uma cena compartilhada com a esposa de Chuck, após os requisitos originais, durante a campanha pré-Liga. O jogador inicia a interação manualmente. Gladion e o novo Type: Null ficam próximos do ginásio; **Type: Null permanece fora da Poké Ball durante todo o encontro**, inclusive conversa, revanche e despedida. O parceiro permanece sem evoluir.

A esposa de Chuck fornece a HM e pede que Gladion a entregue. Ela mantém sua presença e função normais; não criar outra fonte de Fly. A batalha com Gladion é obrigatória como parte da cena, mas **não condiciona Fly à vitória**: vitória ou derrota convergem para a mesma entrega.

#### Checagem silenciosa no início

Antes de conversa longa, deslocamentos ou batalha:
- Conferir recebimento já concluído.
- Conferir capacidade para uma unidade do item real de Fly pela rotina correta do projeto.
- Se a entrega não puder ocorrer, Gladion olha para o jogador e volta a atenção a Type: Null:

> “Agora não. Estou terminando um treino com ele.”
>
> “Volte depois.”

Liberar controles sem batalha ou progresso. Não mencionar HM ou bolsa nessa fala. Na manutenção, preservar a checagem efetivamente implementada para capacidade e outras condições reais de falha. A checagem prévia não elimina a confirmação de sucesso na entrega.

#### Roteiro aprovado

Os diálogos abaixo estão em português como roteiro autoral. Adaptar ao idioma e às caixas de texto do projeto sem alterar a intenção.

**Conversa com a esposa de Chuck**

> Esposa de Chuck: “Você veio de tão longe e pretende voltar pelo mar?”
>
> “Leve Fly. Até quem gosta de caminhar precisa descansar.”
>
> Gladion: “Não vim com pressa.”

Type: Null percebe o jogador e vira a cabeça. Gladion acompanha seu olhar.

> Gladion: “Olha quem chegou.”
>
> “Venceu Chuck? Ele não costuma encerrar um treino cedo.”
>
> Esposa de Chuck: “E depois diz que perdeu a noção do tempo!”
>
> “Trouxe uma HM para você também. Gladion, pode entregá-la? Vou ver se meu marido finalmente aceita fazer uma pausa.”

Ela passa a HM destinada ao jogador a Gladion e segue em direção ao ginásio. A encenação não concede automaticamente uma HM ao jogador antes da etapa de entrega.

**Johto e Lillie**

> Gladion: “Lillie me contou de Goldenrod.”
>
> “Primeiro a batalha. Depois as flores. Depois voltou à batalha.”
>
> “Ela está gostando daqui.”

Type: Null se acomoda ao lado dele.

> Gladion: “Eu também.”
>
> “Achei que passaria por Johto procurando os treinadores mais fortes.”
>
> “Acabei passando uma manhã inteira nesta praia. Ele ainda estava se acostumando com as ondas.”

Gladion olha para o parceiro.

> “Toda vez que a água chegava perto, ele recuava.”
>
> “Depois começou a ir atrás dela.”
>
> “Ficamos mais tempo do que eu planejava.”

Pausa curta; ele volta a olhar para o jogador.

> “Foi uma boa manhã.”

**Revanche obrigatória**

Type: Null se levanta e dá alguns passos na direção do jogador.

> Gladion: “Você lembra dele?”
>
> “É. Eu também quero saber.”
>
> “Antes de partir, vamos lutar de novo.”
>
> “A HM é sua de qualquer jeito. Isto é entre nós.”

Não mostrar menu de aceitar/recusar.

> “Primeiro, vamos cuidar dos seus Pokémon. Você acabou de sair de um ginásio.”
>
> “Pronto. Agora não precisa pegar leve.”

Curar e iniciar a batalha sem blackout. A fala sobre ter acabado de sair do ginásio pressupõe realização imediata; se a implementação final já tratou interação adiada, preservar essa solução.

**Vitória do jogador**

> “Você mudou desde Violet.”
>
> “Tentei encontrar as mesmas aberturas. Não estavam mais lá.”

Gladion se volta para Type: Null.

> “Vamos precisar de outro plano.”
>
> “Você também percebeu, não foi?”

**Derrota do jogador**

> “Dessa vez foi nossa.”
>
> “Mas você nos fez trabalhar por ela.”

Ele olha para Type: Null.

> “Você já estava pronto antes da minha ordem.”
>
> “Bom trabalho.”

São falas de intenção narrativa; não presumir uma troca específica se o combate não a garantir. Capturar o resultado antes da cura. Vitória e derrota convergem para cura e entrega, sem blackout, retry ou penalidade correspondente.

**Entrega e despedida**

> Gladion: “Aqui. A HM que ela deixou para você.”
>
> “Fly. Vai facilitar o caminho de volta.”

Entregar a HM e confirmar sucesso. Só depois marcar o estado existente de recebimento.

> “Se encontrar Lillie, diga que estamos bem.”
>
> “E que eu ouvi a história inteira da batalha.”

Type: Null começa a caminhar pela praia. Para após alguns passos e olha para trás. Gladion percebe.

> “Já escolheu?”
>
> “Estou indo.”

Ele se vira uma última vez para o jogador.

> “Até a próxima, {PLAYER}.”

Type: Null segue na frente; Gladion o acompanha. Ambos saem visivelmente, a música normal retorna e o jogador recupera os controles.

#### Contrato técnico sem novas flags

- Reutilizar o controle real de recebimento de Fly, conservando seu significado. O nome da constante e até o tipo de controle ainda não foram comprovados nesta revisão.
- Não alocar flag persistente de presença, conversa, recusa ou resultado. Como a batalha agora é obrigatória, não existe branch de recusa a persistir. Não reutilizar flags alheias apenas por parecerem livres.
- Condicionar presença dos dois objetos ao recebimento por mecanismo suportado pelo mapa; se não for flag de objeto, verificar script de carregamento existente.
- Não esconder permanentemente a esposa de Chuck.
- Vitória e derrota convergem à mesma entrega. O estado de vitória de treinador não governa a conclusão; o recebimento de Fly continua sendo o estado persistente principal.
- A batalha precisa de entrada/ID de treinador disponível; isso tem custo próprio e não é promessa de ausência de qualquer armazenamento.
- Usar temporários apenas quando necessários, sem colisão com outros scripts; não afirmar que sobrevivem à saída do mapa.
- Confirmar resultado antes de chamadas que o sobrescrevam; preservar/restaurar no-whiteout, música, interlocutor e posições.
- Entrega excepcionalmente frustrada não marca recebimento nem inicia saída. Retomar somente a entrega conforme o comportamento implementado.
- Não bloquear Fly para sempre se o jogador chegar ao evento em uma ordem incomum. Preservar a solução final integrada para interação tardia e evolução futura do parceiro.
- Equipe, níveis, moves e demais parâmetros reais de Gladion passam a ser os da implementação final. Não substituir por propostas antigas do V8 sem uma decisão posterior explícita.

#### Checklist de regressão para manutenção

1. A entrega continua reutilizando a fonte original de Fly e não cria duplicata.
2. A batalha ocorre sem menu de recusa; vitória e derrota convergem para a entrega sem blackout.
3. Type: Null permanece sem evoluir neste encontro e sai na frente de Gladion.
4. Reentrada, interação tardia, follower, música, controles e posições pós-batalha não bloqueiam progressão.
5. A esposa de Chuck permanece funcional e não é escondida permanentemente.
6. Alterações futuras devem partir dos arquivos implementados, não de hipóteses antigas de auditoria.

As alternativas de Gladion em Mahogany, Route 44, Azalea e outros locais não são encontros adicionais aprovados. A escolha desta revisão é a entrega de Fly em Cianwood.

### 4.8. Lillie no Dragon’s Den — “Escutar sem copiar”

**Status:** refinamento refeito no V12 e fechado narrativamente. Implementação, coordenadas, integração com o script real do Dragon Shrine e validação de batalha ainda precisam ser executadas. O objetivo é preservar integralmente o teste e as recompensas vanilla, adicionando Lillie como participante narrativa do **mesmo teste**, não como dona de um segundo questionário paralelo.

#### Papel no arco de Lillie

O encontro fecha a progressão pré-Liga de Lillie:

1. **Route 30:** ela decide começar a batalhar e experimentar uma nova forma de se relacionar com seus Pokémon.
2. **Goldenrod:** aprende que seguir um plano não pode fazê-la ignorar os sinais da parceira; vitória ou derrota servem como treino.
3. **Dragon’s Den:** aprende a ouvir uma resposta diferente, considerar o que ela revela e ainda formular sua própria posição.

O ponto central não é “Lillie finalmente sabe todas as respostas certas”. O Elder deve perceber que ela **escuta antes de responder, mas não copia automaticamente o jogador**. Essa é a maturidade que prepara seus encontros posteriores com Gladion e Lusamine.

A cena não deve fazê-la regredir à insegurança do início de Alola nem transformá-la em confrontacional. Ela pode discordar com calma, mudar uma nuance da própria resposta ou concordar sem parecer dependente da validação do protagonista.

#### Ordem e gatilho

1. O jogador derrota Clair e recebe normalmente a orientação para procurar o Dragon Shrine.
2. Lillie já está no Shrine quando o jogador chega. Ela não está esperando pelo protagonista e não foi enviada por Gladion, Lusamine ou Kukui. **Alolan Ninetales está fora da Poké Ball ao lado dela desde a chegada do jogador.**
3. Sua motivação é própria: ouviu que o Dragon Clan avalia a maneira como Trainers pensam sobre seus Pokémon e pediu ao Elder para acompanhar o teste.
4. O Elder realiza **as cinco perguntas vanilla do jogador**, preservando exatamente a lógica, as alternativas, os estados e as consequências existentes no projeto.
5. Depois de cada escolha do jogador, o script lê temporariamente a alternativa escolhida e executa um branch curto de Lillie.
6. Lillie reage à escolha e então declara sua própria posição. O jogador nunca seleciona a resposta dela.
7. Cada branch converge imediatamente para a próxima pergunta vanilla. Não criar combinações acumuladas de respostas.
8. Depois da quinta pergunta e da avaliação vanilla necessária, o Elder comenta a participação dos dois e pede uma demonstração prática.
9. Curar o time e iniciar a batalha obrigatória entre jogador e Lillie.
10. Vitória ou derrota concluem a demonstração; não há blackout nem retry obrigatório.
11. A sequência retorna ao fluxo original de Clair/Dragon Shrine e Lillie deixa o Shrine normalmente.
12. Nenhuma Ultra Beast aparece como consequência imediata da cena. Blackthorn permanece pós-game.

#### Chegada e reencontro

Lillie deve estar próxima do Elder em uma posição que não bloqueie o caminho, objetos vanilla, follower nem movimentos posteriores da cena. **Alolan Ninetales deve ocupar uma posição própria próxima de Lillie**, visível durante o reencontro, as perguntas e a transição para a batalha.

Falas propostas em inglês:

> Lillie: “{PLAYER}! I didn't know Clair had sent you here.”
>
> “I heard the Dragon Clan doesn't test Trainers only by battling them.”
>
> “They ask what you think about your Pokémon, too. I wanted to hear the questions for myself.”

O Elder contextualiza por que ela participa:

> Elder: “The young lady asked to observe your trial.”
>
> “But an answer can teach us something about the person who gives it... and the person who hears it.”
>
> “So I have asked her to answer as well.”

Lillie:

> “I thought I knew exactly what I would say on the way here.”
>
> “Now I'm not so sure.”
>
> “I think that may be the point.”

Se o jogador falar com Lillie antes de iniciar o teste, manter uma fala curta e não disparar a batalha separadamente:

> “I thought about my answers all the way here. I'm trying not to decide them before I hear the questions.”

#### Estrutura das ramificações

O teste do jogador continua sendo o teste vanilla. O V12 adiciona **15 branches locais**: cinco perguntas, três alternativas em cada uma.

A estrutura desejada é:

```text
pergunta vanilla
      ↓
escolha do jogador
   /    |    \
  A     B     C
  ↓     ↓     ↓
fala específica de Lillie
   \    |    /
      ↓
próxima pergunta vanilla
```

Não combinar respostas anteriores para criar finais diferentes. Cinco perguntas com três alternativas dariam 243 combinações possíveis; isso não agrega valor proporcional e não deve ser implementado.

As falas abaixo usam nomes conceituais das alternativas para facilitar o design. A implementação deve mapear cada branch para os valores reais usados pelo script vanilla do projeto, sem reescrever ou substituir o texto original do quiz.

---

#### Pergunta 1 — relação com os Pokémon

Tema vanilla: como o jogador enxerga seus Pokémon.

##### Se o jogador escolher `ALLY`

> Lillie: “An ally... Someone who stands beside you.”
>
> “I like that.”
>
> “I think I'd say ‘friend,’ though. Sometimes Ninetales understands what I'm trying to do before I've even worked it out myself.”

##### Se o jogador escolher `JUNIOR`

Lillie pensa por um instante.

> Lillie: “I don't think I could call my Pokémon juniors.”
>
> “I'm supposed to be teaching them, but they notice things I don't all the time.”
>
> “I'd say ‘friend.’”

A discordância é calma. Ela não repreende o jogador nem transforma a resposta em julgamento moral.

##### Se o jogador escolher `FRIEND`

> Lillie: “Friend... Yes. That's my answer too.”
>
> “Though lately I've wondered which of us is teaching the other.”

Essa primeira pergunta estabelece a dinâmica da cena: Lillie escuta, considera e só então responde. Quando a fala mencionar Ninetales, uma pequena virada de sprite entre Lillie e a parceira pode reforçar a relação sem interromper o fluxo do quiz.

---

#### Pergunta 2 — o que ajuda a vencer

Tema vanilla: o que mais contribui para vencer uma batalha.

Essa pergunta conecta diretamente o teste ao desenvolvimento de Goldenrod.

##### Se o jogador escolher `STRATEGY`

> Lillie: “I used to think having the right plan was the most important part.”
>
> “Then I started noticing how often my Pokémon saw something before I did.”
>
> “Strategy matters... but only if I'm willing to change it.”

##### Se o jogador escolher `TRAINING`

> Lillie: “Training.”
>
> “I think I understand that answer much better now.”
>
> “It isn't only practicing the same thing until we get it right. It's learning how each of us reacts when something goes wrong.”

##### Se o jogador escolher `CHEATING`

Lillie demonstra surpresa, mas não hostilidade.

> Lillie: “I don't think that would be my answer.”
>
> “You might get the result you wanted...”
>
> “But I don't think my Pokémon and I would have learned anything from it.”
>
> “I'd choose training.”

Não adicionar punição própria de Lillie. Qualquer consequência da escolha continua pertencendo exclusivamente à lógica vanilla.

---

#### Pergunta 3 — quem vale a pena enfrentar

Tema vanilla: que tipo de Trainer vale a pena enfrentar.

A resposta mostra que Lillie já não encara batalha apenas como medição de força.

##### Se o jogador escolher `WEAK`

> Lillie: “Someone weaker...”
>
> “I don't think I'd want to choose an opponent because I expected to beat them.”
>
> “I'd rather battle anyone and find out what they can show me.”

##### Se o jogador escolher `STRONG`

> Lillie: “I understand that.”
>
> “A strong Trainer can show you very quickly what you still need to learn.”
>
> “But someone doesn't have to look strong to surprise you.”
>
> “I think I'd choose anyone.”

##### Se o jogador escolher `ANYONE`

> Lillie: “Anyone.”
>
> “That's mine too.”
>
> “You don't really know what you'll learn from a battle until it starts.”

Essa resposta também prepara conceitualmente a batalha entre jogador e Lillie ao final.

---

#### Pergunta 4 — cuidado e desenvolvimento

Tema vanilla: o que mais importa ao cuidar e desenvolver Pokémon.

Esta é a pergunta de maior peso para o subtexto familiar, mas **não nomear Lusamine nem Gladion**.

##### Se o jogador escolher `LOVE`

Lillie demora um pouco mais para responder.

> Lillie: “Love.”
>
> “Yes... but I think I'm still learning what that means.”
>
> “Caring about someone doesn't mean deciding everything for them.”
>
> “Sometimes it means listening when they choose something you didn't expect.”

Essa fala deve receber uma pequena pausa de encenação. O crescimento familiar aparece sem transformar a cena em exposição sobre Alola.

##### Se o jogador escolher `KNOWLEDGE`

> Lillie: “Knowledge is important.”
>
> “The more I understand my Pokémon, the easier it is to notice what they need.”
>
> “But knowing more about someone doesn't mean you should make every choice for them.”
>
> “I'd still choose love.”

##### Se o jogador escolher `VIOLENCE`

Lillie fica séria, sem reação melodramática.

> Lillie: “No.”
>
> “I want my Pokémon to become stronger because they trust me enough to try.”
>
> “Not because they're afraid of what happens if they don't.”
>
> “I'd choose love.”

Aqui ela pode discordar com clareza. A firmeza é parte do crescimento.

---

#### Pergunta 5 — força e fraqueza

Tema vanilla: como interpretar força e fraqueza em um Pokémon.

A última resposta deve funcionar como conclusão natural do teste compartilhado.

##### Se o jogador escolher `STRENGTH`

> Lillie: “Strength matters.”
>
> “Especially when someone is depending on you.”
>
> “But if I only looked at what they were strongest at, I'd miss half of who they are.”
>
> “I'd choose both.”

##### Se o jogador escolher `BOTH`

> Lillie: “Both.”
>
> “That's my answer too.”
>
> “Their strengths tell me what they can do.”
>
> “Their weaknesses tell me where I need to stand beside them.”

Essa é a resposta em que Lillie soa mais segura.

##### Se o jogador escolher `WEAKNESS`

> Lillie: “I think weaknesses are important to understand.”
>
> “But I wouldn't want a Pokémon to believe that's all I see when I look at them.”
>
> “I'd choose both.”

---

#### Conclusão das perguntas

Depois da quinta resposta, executar toda avaliação vanilla necessária do jogador antes da conclusão adicional de Lillie.

O Elder não deve resumir as quinze possibilidades nem declarar um “vencedor” filosófico do quiz.

> Elder: “Interesting.”
>
> “You did not always give the same answers.”
>
> “That is not a failing.”
>
> “Understanding another Trainer does not require becoming that Trainer.”

Ele olha para Lillie:

> Elder: “You listened before answering, yet you did not surrender your own judgment.”

Lillie:

> “I almost did.”
>
> “A few times.”
>
> “But then they wouldn't really have been my answers.”

Esse é o payoff principal do teste. Lillie aprendeu a **escutar sem copiar**.

#### Transição para a demonstração

O Elder muda o teste de palavras para ação:

> Elder: “Words reveal conviction.”
>
> “But a Trainer cannot prepare every moment of a battle.”
>
> “When circumstances change, understanding must become action.”
>
> “Show me.”

Lillie:

> “A battle...”
>
> “Yes.”
>
> “That makes sense.”
>
> “{PLAYER}, we've just spent all this time explaining what kind of Trainers we want to be.”
>
> “Let's see what we actually do when the plan stops being simple.”

Curar o time do jogador antes do combate. A batalha é obrigatória como parte da demonstração, mas **não exige vitória**.

#### Equipe V12

A equipe preserva os quatro parceiros de Goldenrod e mostra progressão sem adicionar espécies novas. **Alolan Vulpix evolui para Alolan Ninetales neste estágio**, tornando a mudança visual da parceira um marcador natural do crescimento de ambas.

Os números abaixo são a baseline de design do V12. Balanceamento após teste pode ajustar níveis, EVs, itens ou um golpe sem alterar o roster, o papel de cada membro ou o fato de Ninetales ser o ás.

| Ordem | Pokémon | Nível | Item | Ability | Nature | Golpes |
| --- | --- | --- | --- | --- | --- | --- |
| 1 | Ribombee | 43 | Sitrus Berry | Shield Dust | Timid | Sticky Web, Pollen Puff, Psychic, U-turn |
| 2 | Clefairy | 43 | Eviolite | Magic Guard | Bold | Moonblast, Thunder Wave, Moonlight, Flamethrower |
| 3 | Comfey | 44 | Sitrus Berry | Triage | Modest | Draining Kiss, Giga Drain, Calm Mind, Synthesis |
| 4 | Ninetales Alola | 45 | Light Clay | Snow Warning | Timid | Aurora Veil, Freeze-Dry, Moonblast, Encore |

Todos devem usar IVs altos/coerentes com o padrão de bosses do hack. Não alterar dados globais das espécies para conseguir o comportamento desta luta. Conferir no projeto se `Snow Warning`, clima, `Aurora Veil`, `Sticky Web`, itens e IA funcionam com a semântica local esperada.

**Identidade de batalha:** preparar, observar e responder. Ribombee cria ritmo e pivota; Clefairy interrompe e cobre fraquezas; Comfey transforma dano em sustain; Ninetales entra como ás e comprime defesa, pressão e controle. A equipe não precisa responder perfeitamente a Poison e Steel: manter fraquezas exploráveis.

A batalha deve usar a IA de treinador forte já disponível no projeto. Não dar itens de cura consumidos por Lillie durante a luta salvo se isso for padrão do trainer class existente.

#### Revelação de Ninetales

Não é necessária uma cutscene de evolução. **A evolução já aconteceu antes da chegada ao Dragon’s Den, fora de cena.** Ninetales está visível fora da Poké Ball desde o início do encontro. Antes da batalha, Lillie pode reconhecer a mudança:

> Lillie: “You remember Vulpix, don't you?”
>
> “She evolved while we were traveling. I thought I would need to change everything.”
>
> “But she didn't become someone different. I just had to learn to keep up.”

#### Resultado — jogador vence

Trainer defeat text:

> “We adjusted again... and you still found the opening!”

Depois da batalha:

> Lillie: “I thought I knew what you were going to do twice.”
>
> “I was wrong twice.”
>
> “But we didn't freeze when it happened.”
>
> “Goldenrod felt different from our first battle.”
>
> “This felt different again.”

O foco não é elogiar genericamente o protagonista; ela identifica o próprio progresso.

#### Resultado — Lillie vence

A derrota do jogador é um resultado válido, sem blackout e sem retry.

> Lillie: “We did it.”
>
> “And this time I don't think I need to apologize for being happy about that.”

Ela olha para o jogador:

> “You changed what you were doing halfway through.”
>
> “We noticed.”
>
> “And we changed too.”

Lillie pode celebrar a própria vitória sem voltar imediatamente a pedir desculpas por ter vencido.

#### Empate, forfeit e resultados inesperados

Se o engine expuser empate ou desistência, tratar explicitamente sem blackout. Não declarar vitória de ninguém.

> Lillie: “Let's look after everyone first.”
>
> “I think we both learned something from that.”

Resultado desconhecido não deve ser convertido silenciosamente em vitória do jogador.

#### Conclusão comum

Depois de registrar o resultado, curar o time.

O Elder não avalia a relação pelo vencedor:

> Elder: “Good.”
>
> “Neither result changes what I wished to see.”
>
> “You watched your Pokémon. You watched your opponent. And when the battle changed, you answered it together.”

Ele conclui:

> Elder: “Remember your answers.”
>
> “Not because they must remain the same forever.”
>
> “Remember why you gave them.”

Lillie:

> “I will.”
>
> “And I think I'll remember some of yours, too.”
>
> “Even the ones I wouldn't have chosen.”

A sequência retorna então ao fluxo normal de Clair/Dragon Shrine.

Lillie deixa o Shrine antes da continuação apropriada de Clair, usando movimento seguro e sem bloquear objetos, warps ou follower. **Ninetales sai junto com ela**; não deve desaparecer isoladamente antes da Trainer.

#### Integração com Clair e progressão pós-Liga

- Não remover, duplicar nem substituir badge, TM, Dratini, Dragon Fang ou qualquer outra recompensa/controle vanilla existente no projeto.
- As cinco perguntas do jogador preservam sua lógica original. As falas de Lillie são camadas narrativas executadas **depois de cada escolha**, não substituições do quiz.
- As escolhas de Lillie não alteram a avaliação do jogador nem os rewards/estados vanilla.
- A batalha de Lillie é uma demonstração intermediária, não uma recompensa material.
- Após qualquer resultado válido da batalha, retornar ao label/estado vanilla correto para que Clair continue exatamente de onde deveria.
- Nenhum incidente de Ultra Beast é disparado ao sair do Dragon Shrine; Blackthorn permanece inativo durante a campanha pré-Liga.
- A presença futura de Lillie nas Rift Missions não depende de uma nova flag narrativa exclusiva desta cena.
- Ninetales permanece fora da Poké Ball durante toda a cena do Shrine, salvo transição técnica estritamente necessária para iniciar a batalha.

#### Contrato técnico das 15 ramificações

Implementar como branches **locais e imediatos**, não como combinações persistentes.

Padrão:

```text
Q1 vanilla
→ ler escolha Q1
→ Lillie_Q1_A/B/C
→ Q2 vanilla
→ ler escolha Q2
→ Lillie_Q2_A/B/C
→ ...
→ Q5 vanilla
→ ler escolha Q5
→ Lillie_Q5_A/B/C
→ avaliação vanilla
→ conclusão compartilhada
→ batalha
```

Se o script vanilla usar uma variável especial reutilizada entre perguntas, capturar a alternativa **antes** de iniciar a próxima pergunta. Não reservar cinco flags persistentes apenas para lembrar respostas cujo branch já foi consumido.

A implementação deve auditar:
- qual variável/retorno contém cada alternativa;
- quando esse valor é sobrescrito;
- quais labels executam sucesso/avaliação vanilla;
- se alguma escolha pula diretamente para outro trecho;
- se o Dratini ou outra recompensa depende de contagem/estado acumulado;
- como inserir a fala de Lillie sem alterar essa contagem.

A camada de Lillie não deve modificar a pontuação, contador ou condição vanilla.

#### Contrato técnico da batalha e economia de estado

O executor deve distinguir no mínimo:
- teste vanilla ainda não concluído;
- cinco perguntas processadas e conclusão compartilhada ainda pendente;
- batalha de Lillie ainda não executada;
- batalha executada, independentemente do vencedor, e retorno ao fluxo vanilla;
- sequência de Clair concluída.

A flag automática de trainer derrotado não é suficiente, porque ela pode não ser marcada quando Lillie vence. Preferir o próprio estado de progressão do Shrine/Clair ou outro estado já existente que represente que a cena aconteceu. Só reservar nova flag persistente se a auditoria provar que não há como distinguir reentrada/reload com os estados existentes.

Preservar música, no-whiteout quando usado, follower, direção dos sprites, posições após combate e controles em todas as saídas.


### 4.9. Gladion antes da Victory Road — “O primeiro passo”

**Status:** novo encontro fechado em design no V12; implementação e balanceamento pendentes.

#### Papel no arco

Este é o último duelo de Gladion com o jogador antes da Liga e a primeira apresentação explícita do novo parceiro como **Silvally**. A cena não funciona como teste de permissão para entrar na Victory Road. Gladion está ali porque quer comparar o quanto ambos mudaram desde Violet; a passagem permanece parte da progressão normal do jogo.

A transformação do parceiro deve ser percebida em comportamento, não em exposição longa. A frase “now it takes the first step” é materializada em gameplay: **Silvally é o lead planejado da batalha**, entrando primeiro por iniciativa do par narrativo. O restante da equipe deve formar um boss forte para a etapa; alvo atual de estrutura: cinco Pokémon no total. As outras quatro espécies, itens, níveis, EVs e golpes permanecem pendentes de balanceamento e não devem ser inventados como decisão fechada sem revisão posterior.

#### Gatilho e encenação

1. Usar um ponto imediatamente anterior ao acesso à Victory Road que não interfira com guardas, checagens de badges, followers ou warps.
2. Ao entrar no gatilho, Gladion e Silvally chamam a atenção do jogador. A cena é automática.
3. Gladion apresenta a evolução antes da batalha. Não depende de resultado em Violet/Cianwood.
4. Curar o jogador.
5. Iniciar batalha obrigatória sem blackout; não mostrar menu de recusa.
6. Capturar o resultado imediatamente após retornar.
7. Usar branch de vitória ou derrota; ambos convergem para cura e despedida.
8. Gladion e Silvally saem; restaurar música/controles. A Victory Road continua acessível normalmente.
9. Não deixar revanche infinita nem mover esse confronto para a entrada da Liga.

#### Roteiro em inglês

Chegada:

> Gladion: “You made it.”
>
> “Victory Road is just ahead.”

Ele olha para Silvally.

> “Remember the Type: Null you met in Violet?”
>
> “Take a look.”
>
> “It used to wait for me to decide everything.”
>
> “Now it takes the first step.”

Silvally avança primeiro.

> Gladion: “Seems like it already decided what it wants.”
>
> “One battle before Victory Road.”
>
> “Not because you need my permission.”
>
> “I want to know how far we've both come.”

Não há opção de recusar. Gladion cura o time e inicia a luta.

**Se o jogador vencer:**

> Gladion: “That's different.”
>
> “In Violet, I was trying to figure out how you battled.”
>
> “This time, I knew what you would try.”
>
> “You still found another way.”

Ele olha para Silvally.

> “Looks like we're not the only ones who learned something.”

**Se Gladion vencer:**

> Gladion: “This time, we got you.”
>
> “But you didn't stop looking for an opening.”

Ele olha para Silvally.

> “Neither did you.”
>
> “Good.”

**Conclusão comum:**

> Gladion: “Victory Road is ahead.”
>
> “Whatever happens in there, make your Pokémon part of the answer.”
>
> “See you after the League, {PLAYER}.”

Silvally começa a caminhar primeiro e Gladion o acompanha. Essa repetição visual ecoa Cianwood: antes Type: Null começava a se adiantar; agora Silvally faz isso com confiança plena.

#### Contrato técnico

- Batalha obrigatória, sem menu de escolha.
- Vitória e derrota são conclusões válidas; nenhuma causa blackout.
- Salvar resultado antes de cura/comandos que possam sobrescrevê-lo.
- Não usar `trainer defeated` como único estado de conclusão. O evento precisa ficar concluído mesmo quando Gladion vence.
- Não criar gate artificial da Victory Road baseado no resultado.
- Não repetir a cena em reentrada após conclusão.
- Preservar guardas, checagem de badges e warp original.
- Silvally deve aparecer tanto na overworld/cutscene quanto na equipe, conforme os assets e sistema disponíveis; se não for viável mostrar follower separado, preservar ao menos a apresentação e a equipe sem inventar asset novo.

### 4.10. Encadeamento econômico dos eventos

Reutilizar eventos e estados existentes é prioridade, mas o V12 separa claramente **resultado de batalha** de **conclusão narrativa**.

- Route 30: progresso pertence à cena de Oak/Kukui e às entregas; não à vitória contra Lillie.
- Violet: progresso pertence ao recebimento do Mystery Egg; vitória contra Gladion não é requisito.
- Goldenrod: conclusão continua sendo `FLAG_RECEIVED_SQUIRTBOTTLE`; resultado da batalha não governa o item.
- Cianwood: conclusão continua sendo o controle real de Fly; a batalha passa a ser obrigatória, mas resultado não governa a HM.
- Dragon’s Den: conclusão pertence ao progresso do teste/Clair; a flag automática de trainer derrotado não pode ser a única condição.
- Victory Road: usar estado de cena já concluída ou mecanismo existente do mapa; derrota precisa ocultar Gladion da mesma forma que vitória.

O padrão técnico desejado é: **battle occurred → save result → dialogue branch → common continuation → persist actual event state**.

Checar capacidade antes de presentes, confirmar entregas antes de esconder NPCs e nunca confiar em temporários para persistência após reload. Não apagar recebimentos concluídos, duplicar presentes nem bloquear saídas. O alvo continua New Game, sem migração de saves antigos.

## 5. Escritório em Olivine

O início formal da sequência das nove missões exige que o jogador tenha concluído a E4 **e resolvido o incidente pós-game de Blackthorn**. Ao final desse incidente, Looker encaminha o jogador ao escritório de Looker e Anabel em Olivine. A casa ou sala exata ainda será escolhida.

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
- A primeira chegada libera o altar como destino de Fly. Isso é o registro do ponto de pouso, não outra entrega da HM de Cianwood.
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

O nome “Eclipse” identifica o clímax narrativo no mesmo local. Não acrescenta terceiro altar nem exige esperar um eclipse astronômico ou horário específico. Detalhes visuais da transição ainda podem ser desenvolvidos.

### Direção visual

A arquitetura segue as referências dos altares de USUM: paredão avermelhado, mecanismo vertical de pedra, disco celestial monumental, escadarias, plataformas e canais de água.

O acabamento deve seguir a escala e o estilo dos tilesets de SoulGold, com peças modulares compactas e pixels definidos. A paleta deve ter mais vida: terracota, pedra clara, água azul-turquesa, vegetação verde, dourado para o Sol e lilás para a Lua.

As imagens conceituais produzidas são referências visuais. Ainda não constituem tilesets de produção validados quanto a grade, paletas, metatiles, camadas ou colisões.

## 9. Lusamine e Ultra Necrozma

Com as nove missões concluídas e Solgaleo ou Lunala apresentado a Looker, a investigação chega ao ponto de enfrentar a origem da instabilidade. A travessia até Necrozma envolve risco de a passagem se desestabilizar e impedir o retorno.

Lusamine insiste em realizar a operação sozinha. A única batalha do jogador contra ela ocorre aqui como **duelo de personagem**, não como boss de ameaça: usar o contrato V12 sem blackout. Vitória e derrota recebem respostas próprias, mas ambas resolvem a disputa narrativa e levam Lusamine a aceitar a ajuda do grupo. O resultado não deve ser reescrito como vitória do jogador. O roteiro deve dar espaço à reação de Lillie e Gladion sem retirar do jogador o papel no confronto contra Necrozma.

O jogador então atravessa para enfrentar Ultra Necrozma em uma boss battle e obter Necrozma por captura. O tratamento da forma após a batalha precisa respeitar a implementação local: não presumir que Ultra Necrozma pode permanecer como forma de armazenamento. Também não está definido se a captura ocorre durante o combate ou em uma etapa posterior.

Ultra Necrozma é um **boss de ameaça**. Derrota pode usar blackout ou retorno seguro para um checkpoint e exige nova tentativa; fugir quando permitido ou derrotar sem capturar também não pode tornar Necrozma permanentemente indisponível. O mecanismo de retry/captura deve ser definido antes da implementação do encontro.

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

### Treinadores preservados para o loop

A limpeza informada pelo autor deve preservar uma batalha representativa de cada personagem selecionado de Hoenn. Isso define uma reserva de conteúdo para o futuro pool, não afirma que todos os IDs já foram auditados ou que os sorteios estejam implementados.

| Grupo | Seleção aprovada |
| --- | --- |
| Gym Leaders de Hoenn | Uma luta por líder preservado. Identificar no inventário as versões presentes de Wallace/Juan e o formato de Tate e Liza; não inventar batalhas individuais ausentes. |
| Elite Four de Hoenn | Uma luta por integrante. |
| Líderes de Aqua e Magma | Uma luta de Archie e uma de Maxie. |
| May e Brendan | Somente a última luta de cada um. |
| Wally | Uma luta representativa. |
| Steven | Preservar uma luta; inclusão expressamente solicitada. |

Não inferir que somente esses personagens podem aparecer em todos os pools: Misty e Giovanni continuam exemplos aprovados de associação temática. A seleção acima se refere ao conteúdo de Hoenn discutido na limpeza. Outros personagens marcantes são sugestões, não acréscimos automáticos.

O inventário deve mapear nome, ID real, equipe e referências. Não renumerar treinadores nem recuperar entradas eliminadas sem necessidade comprovada. A ausência de chamada direta em um mapa não comprova inutilidade: examinar tabelas de rematch/Match Call, eventos e seleção dinâmica. A menção anterior a “208 livres” não é contagem validada nesta versão.

Uma luta por personagem não exige uma cópia por dificuldade ou por expedição. O loop precisa permitir repetir batalhas mesmo quando o trainer já foi vencido, sem limpar indiscriminadamente flags da campanha. O mecanismo deve ser definido na implementação do sistema.

## 11. Regras de continuidade e recuperação

Estas são diretrizes de execução para preservar a intenção do design, não sistemas adicionais de progressão.

- Duelos narrativos de personagem avançam em vitória ou derrota sem blackout; armazenar o resultado apenas para diálogo, não como gate.
- Blackthorn marca a transição para confrontos de ameaça: Ultra Beasts e bosses equivalentes podem usar blackout/retorno seguro e retry.

- Distinguir encontro apresentado, batalha vencida, Pokémon capturado, missão resolvida e relatório entregue.
- Não apagar progresso concluído ao perder uma batalha posterior.
- Oferecer nova tentativa quando uma captura necessária não acontece.
- Não repetir presentes de história, como o Mystery Egg, o SquirtBottle, Fly e a Eviolite, por sair e entrar no mapa.
- Manter retorno seguro do altar e das expedições.
- Não exigir Solgaleo ou Lunala novamente a cada expedição depois de liberar o sistema.
- Evitar cenas repetidas ou diálogos longos obrigatórios em viagens e runs posteriores.
- Manter os gatilhos de Whitney, Chuck, Clair e da Liga compatíveis com a campanha existente.
- O alvo é uma campanha iniciada em New Game. Compatibilidade e migração de saves antigos estão fora de escopo por decisão do autor.

## 12. Escopo técnico e assets

O projeto é uma ROM GBA de SoulGold. A execução deve verificar primeiro os sistemas locais de quests, encontros especiais, batalhas com aliado, bosses, navios, Fly, horário e persistência. Reutilizar mecanismos adequados é preferível a introduzir sistemas paralelos sem necessidade.

Já houve trabalho visual na conversa para sprites de Lillie, Gladion, Lusamine, Kukui e Looker, além de referências de Anabel. A existência dos arquivos não comprova integração na ROM. Sprites e tilesets precisam passar pela conversão e validação exigidas pelo projeto, incluindo transparência, paletas e dimensões.

O elenco recorrente e o altar compartilhado favorecem reutilização de assets. Não há orçamento de memória atualizado confirmado neste documento; medir ROM, EWRAM e IWRAM na árvore local durante a implementação. Os valores antigos discutidos não são um orçamento garantido para esta versão.

## 13. Decisões substituídas ou não confirmadas

| Ideia anterior | Situação vigente |
| --- | --- |
| Qualquer incidente obrigatório de Ultra Beast antes da E4 | Substituído: Blackthorn foi movido para o pós-game; a campanha pré-Liga não contém ruptura obrigatória desta questline. |
| Escritório em local indefinido ou Goldenrod | Substituída por Olivine. |
| Revelação de Anabel | Ela já sabe ser Faller; conta sua história ao jogador na reunião antes do navio. |
| Gladion ligado ao choro de Whitney | Substituído pela batalha e entrega do ovo em Violet. |
| Assistente de Elm entrega o ovo | Substituído por Gladion; revisar ligação de Violet e indicação da Route 32. |
| Lillie em Goldenrod | Evento implementado conforme o autor; vitória ou derrota permitem SquirtBottle, seguido de saída pela porta. FLAG_RECEIVED_SQUIRTBOTTLE controla a ausência. |
| Vitória obrigatória contra Lillie em Goldenrod | Substituída por continuidade em vitória e derrota. O V12 preserva a mesma filosofia aos demais duelos narrativos. |
| Gladion sem encontro intermediário antes de Blackthorn | Substituído por Cianwood e pelo novo encontro obrigatório antes da Victory Road. |
| Fly condicionado a vencer Gladion | Não aprovado: vitória ou derrota permitem receber a HM. A opção de recusa foi removida no V12. |
| Aviso explícito de bolsa/HM na checagem inicial de Gladion | Substituído por fala de treino ocupado, sem iniciar a cena. |
| Vitória obrigatória em Route 30/Violet/Dragon’s Den | Substituída: esses duelos concluem em vitória ou derrota, sem blackout. |
| Gladion opcional na entrada da Liga | Removido: a luta foi movida para antes da Victory Road, é obrigatória e não exige vitória. |
| Retry de Lillie após derrota no Dragon’s Den | Removido: a demonstração termina após a batalha independentemente do vencedor. |
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
| Campanha | Refatorar Route 30, Violet e Cianwood para a política V12; Goldenrod já é compatível. Implementar Dragon’s Den e Victory Road. |
| Lillie em Goldenrod | Implementada conforme o autor; preservar o evento e registrar evidências de regressão quando houver manutenção, sem tratá-lo como tarefa nova. |
| Gladion em Cianwood | Preservar a implementação existente, mas remover a recusa e garantir batalha obrigatória com vitória/derrota sem blackout. |
| Lillie no Dragon’s Den | Integrar o roteiro V12; validar estado de batalha executada independentemente do vencedor, mapa, música, follower e retorno à sequência de Clair. |
| Gladion / Victory Road | Escolher gatilho/mapa seguro antes do acesso, criar estado de conclusão independente do vencedor e fechar equipe de cinco com Silvally lead. |
| Blackthorn | Pós-game, imediatamente antes da abertura formal do escritório de Olivine; verificar suporte real à batalha com aliado contra duas Ultra Beasts, restrição de captura e gatilho após E4. |
| Missões | Objetivos locais, diálogos, pontos de encontro, níveis e parâmetros de boss. |
| Capturas | Condição de conclusão da missão e mecanismo de revanche/recuperação. |
| Beast Balls | Preço, estoque e eventual entrega inicial; nenhum valor está fechado. |
| Altar | Localização, nome no mapa, embarque, desembarque e ponto de Fly. |
| Solgaleo/Lunala | Implementar a checagem de qualquer um no time; verificar a evolução normal no código. |
| Necrozma | Equipe de Lusamine, sequência de travessia, regras de boss, captura e forma armazenada. |
| Despedida | Diálogos e posição final dos personagens além de Looker e Anabel. |
| Loop | Pools de treinadores/lendários, equipes, níveis, cura, itens, derrota, saída e eventual recompensa adicional. |
| Conteúdo total | Disponibilidade de Type: Null e Poipole/Naganadel fora desta sequência; auditar antes de adicionar fontes. |
| Texto | Adaptar os roteiros autorais ao idioma existente do jogo e às caixas de texto; preservar falas já implementadas salvo correção necessária. |
| Pool de Hoenn | Mapear uma luta por personagem aprovado, incluindo Steven, e identificar formatos/IDs preservados após limpeza. |
| Cianwood tardio | Não é mais pendência de design; preservar o tratamento existente da implementação final e reabrir apenas se surgir regressão comprovada. |

## 15. Critérios de aceite do design implementado

As caixas abaixo são critérios de verificação, não uma declaração de teste executado nesta revisão. Violet, Goldenrod e Cianwood possuem implementação anterior confirmada pelo autor, mas Violet e Cianwood precisam do retrofit V12. Dragon’s Den e Victory Road estão fechados em design e pendentes de implementação/teste.

- [ ] Encontros de campanha preservam os personagens, locais e motivações definidos.
- [ ] Vulpix de Alola da primeira Lillie está no nível 7; a batalha é obrigatória e vitória ou derrota continuam para as entregas sem blackout.
- [ ] Mystery Egg recebido em Violet nasce como Cosmog.
- [ ] Elm aceita a família de Cosmog no time e entrega Eviolite uma única vez, reutilizando os estados existentes.
- [ ] O arco se desenvolve em paralelo à campanha de Johto, preservando suas motivações e conclusão próprias.
- [ ] O antigo aquecimento opcional na entrada da Liga foi removido; Gladion enfrenta o jogador obrigatoriamente antes da Victory Road.
- [ ] Gladion usa o novo Type: Null em Violet e Cianwood; o parceiro anterior não foi regredido.
- [ ] Type: Null permanece fora da Poké Ball ao lado de Gladion em Violet e Cianwood; após a evolução, Silvally assume essa presença visual em Victory Road, Blackthorn e todas as aparições posteriores de Gladion.
- [ ] Silvally é apresentado antes da Victory Road e permanece com Gladion em Blackthorn e no pós-E4, independentemente dos resultados anteriores.
- [ ] A apresentação de Silvally precede a batalha obrigatória de Victory Road e não transforma Gladion em gate de acesso.
- [ ] Gladion substitui o assistente em Violet; a batalha é obrigatória, mas vitória e derrota permitem a entrega do ovo sem blackout.
- [ ] O antigo encontro de Gladion com Whitney foi removido do roteiro.
- [ ] Lillie realiza a revanche e entrega o SquirtBottle no evento da floricultura, preservando os requisitos da entrega.
- [ ] Goldenrod permite entrega em vitória e derrota, cura antes/depois e mantém Vulpix Alola sem evolução.
- [ ] Lillie usa FLAG_RECEIVED_SQUIRTBOTTLE para ausência definitiva após entrega e caminhada até a porta, sem nova flag.
- [ ] Falha na entrega não esconde NPCs; retoma só a entrega na mesma visita, sem prometer persistência de temporários após reload.
- [ ] Cianwood reutiliza a entrega original de Fly sem nova flag/variável persistente e sem duplicar a fonte da esposa de Chuck.
- [ ] Checagem inicial de Fly é silenciosa; impedimento usa fala de treino ocupado antes da cena longa ou batalha.
- [ ] Gladion entrega Fly após vitória ou derrota; o V12 mantém removida a recusa e não usa flag de trainer vencido como gate.
- [ ] Type: Null sai na frente e Gladion o acompanha; ambos permanecem ausentes após entrega.
- [ ] Evento tardio de Cianwood não bloqueia Fly nem contradiz a evolução do parceiro; preservar a solução já implementada.
- [ ] Esposa de Chuck, follower, música, controles e posições pós-batalha permanecem corretos.
- [ ] Dragon’s Den preserva as cinco perguntas, avaliação e recompensas vanilla e adiciona exatamente uma reação/resposta de Lillie após cada escolha do jogador, sem permitir que o jogador responda por ela.
- [ ] As cinco perguntas geram 15 branches locais (3 por pergunta), convergindo imediatamente para a próxima pergunta; não existem 243 combinações persistentes.
- [ ] As respostas de Lillie nunca alteram pontuação, contador, Dratini ou qualquer outro estado/recompensa vanilla do teste.
- [ ] No Dragon’s Den, Alolan Ninetales já está evoluída antes da chegada do jogador e permanece fora da Poké Ball ao lado de Lillie durante reencontro, quiz e transição para a batalha.
- [ ] Após o Dragon’s Den, Ninetales continua fora da Poké Ball em todas as aparições posteriores de Lillie, inclusive nas Rift Missions e cenas finais em que ela estiver presente.
- [ ] A batalha de Dragon’s Den usa Ribombee, Clefairy, Comfey e Alolan Ninetales, com Ninetales como ás e identidade de controle/adaptação.
- [ ] Derrota contra Lillie no Dragon’s Den não repete Clair nem o quiz e conclui a demonstração sem blackout ou retry obrigatório.
- [ ] Vitória ou derrota contra Lillie devolvem o fluxo ao estado correto de Clair e Lillie deixa o Shrine normalmente.
- [ ] A ordem final pré-Liga inclui Gladion antes da Victory Road: Clair → Dragon’s Den/Lillie → Victory Road Gladion → Victory Road → Liga, sem ruptura obrigatória de Ultra Beast.
- [ ] Gladion antes da Victory Road usa Silvally como lead planejado, batalha obrigatória sem blackout e saída definitiva da cena em vitória ou derrota.
- [ ] Victory Road permanece acessível independentemente do resultado e o encontro antigo na entrada da Liga não existe mais.
- [ ] Diálogos seguem o guia de voz; diferenças entre SM, USUM e adaptações próprias permanecem explícitas.
- [ ] Blackthorn só dispara no pós-game e contém a batalha jogador + Gladion/Silvally contra Buzzwole + Pheromosa, com participação de Looker; **Silvally já está fora da Poké Ball ao lado de Gladion quando a crise começa**. Derrota usa recuperação de ameaça e exige retry; não avança o incidente.
- [ ] Ao resolver Blackthorn, Looker encaminha o jogador ao escritório de Olivine.
- [ ] Escritório de Olivine inicia as nove missões somente após a E4 e a resolução de Blackthorn.
- [ ] Nove missões seguem a ordem e os acompanhantes da tabela, com Looker em todas.
- [ ] Há retorno ao escritório após cada missão e venda de Beast Balls desde o começo.
- [ ] Após Nihilego e apresentação de Solgaleo OU Lunala no time, a reunião libera o navio.
- [ ] Cosmog/Cosmoem não liberam a expedição; a ausência da evolução não impede as nove missões.
- [ ] Primeira visita desbloqueia o destino do altar no mapa de Fly, sem entregar outra HM; navio permanece disponível nos dois sentidos.
- [ ] Existe apenas um altar físico, com visual diurno/noturno e sem capturas de Solgaleo/Lunala.
- [ ] Um dos dois lendários permite abrir o portal em qualquer horário.
- [ ] Não há presente de Cosmoem nem evolução automática no altar.
- [ ] Lusamine é enfrentada apenas uma vez na história, perto da travessia final. Vitória ou derrota continuam sem blackout e levam à aceitação do plano coletivo.
- [ ] Necrozma pode ser obtido e falhas não bloqueiam permanentemente sua captura.
- [ ] Despedida deixa Looker e Anabel no altar.
- [ ] Anabel revela sua condição de Faller na reunião anterior ao navio, sem uma flag exclusiva.
- [ ] Sua decisão de permanecer no altar inclui a motivação pessoal de ajudar outros deslocados.
- [ ] Expedições têm cinco treinadores e um boss lendário capturável.
- [ ] Quinto treinador tem associação temática com o lendário e as batalhas possuem frases contextuais.
- [ ] Lendários já capturados continuam disponíveis para repetição e busca de IVs.
- [ ] Acesso ao loop funciona em qualquer horário.
- [ ] Pool preserva uma luta de cada personagem de Hoenn aprovado, incluindo Steven, sem variantes de dificuldade adicionais.
- [ ] Repetição do loop não depende de apagar flags de vitória da campanha.
- [ ] Espaço para o ovo em Violet considera party e PC antes da batalha.
- [ ] Todos os duelos narrativos V12 salvam o resultado e continuam sem blackout; progressão não depende de vitória nem de menu de recusa.
- [ ] Memória, assets e persistência são validados na ROM local, sem presumir suporte pelo design.

## 16. Entrega por etapas

1. Refatorar os duelos já existentes de campanha para a política V12: Route 30 e Violet passam a continuar após derrota; Cianwood perde a opção de recusa e continua em vitória/derrota. Preservar equipes, mapas e entregas já implementados.
2. Implementar Lillie no Dragon’s Den conforme a seção 4.8: primeiro auditar os cinco retornos de escolha do quiz, inserir os 15 branches locais sem tocar na avaliação vanilla e então usar estado de **batalha executada** — não de vitória — para devolver o fluxo a Clair.
3. Implementar Gladion antes da Victory Road conforme a seção 4.9; fechar equipe de cinco e gatilho seguro sem criar gate de acesso.
4. Preservar Victory Road e Liga sem incidente obrigatório de Ultra Beast e sem segundo encontro de Gladion na entrada da Liga.
5. Implementar Blackthorn como primeiro confronto de ameaça pós-game; derrota deve usar recuperação/retry e não avançar a resolução.
6. Implementar escritório, nove missões, expedição, duelo de Lusamine sem blackout e boss de Ultra Necrozma com retry conforme os contratos aprovados.
7. Integrar o inventário de treinadores preservados ao loop repetível e validar acesso e repetição.

Uma divisão prática de produção continua sendo: encontros de campanha; Blackthorn/escritório e progressão das nove missões; expedição/navio/Fly/altar; clímax e despedida; loop repetível. Cada etapa deve entregar gatilhos, textos, batalhas e recuperação de falhas de forma verificável antes da próxima.

Esta divisão é uma recomendação de produção. Não autoriza alterar o elenco, a ordem das missões, a condição de evolução exigida por Looker ou a estrutura do loop.

## 17. Registro da revisão V12

- Preservada a política global de duelos narrativos sem blackout: vitória ou derrota continuam a história; bosses de ameaça permanecem sujeitos a retry.
- Preservado o Dragon’s Den compartilhado do V12, com cinco perguntas vanilla e 15 branches locais de Lillie.
- Adicionada uma regra visual de continuidade para parceiros recorrentes fora da Poké Ball.
- **Type: Null permanece fora da Poké Ball ao lado de Gladion em Violet e Cianwood.**
- Depois da evolução, **Silvally** assume a mesma presença visual em Victory Road e continua fora da Poké Ball em todas as aparições posteriores de Gladion.
- **Alolan Vulpix permanece fora da Poké Ball com Lillie** nos encontros anteriores ao Dragon’s Den, incluindo Route 30 e Goldenrod.
- No Dragon’s Den, a evolução já aconteceu fora de cena: **Alolan Ninetales está fora da Poké Ball desde a chegada do jogador**, participa visualmente do quiz e sai junto com Lillie.
- A partir do Dragon’s Den, **Ninetales permanece fora da Poké Ball em todas as aparições posteriores de Lillie**, inclusive Rift Missions, reunião e clímax quando aplicável.
- Mantida Ninetales como ás da batalha do Dragon’s Den; não há cutscene obrigatória de evolução.
- Acrescentadas exigências de posicionamento, saída sincronizada e compatibilidade com follower, warps, objetos vanilla e limites de objetos dos mapas.
- Preservados Gladion antes da Victory Road, Blackthorn pós-game, escritório de Olivine, nove missões, altar único, clímax e loop repetível.

### Nota de autoridade da V12

O V12 substitui o V9 para decisões de design. Para cenas já implementadas, preservar dados técnicos que não foram alterados — equipes, mapas, assets e entregas — mas refatorar branches incompatíveis com a nova política de resultado. Uma implementação antiga não prevalece sobre a decisão V12 de permitir continuidade após derrota.

O contrato editorial principal é: **duelo de personagem testa/revela relação; boss de ameaça precisa ser resolvido**. Assim, perder para Lillie, Gladion ou Lusamine pode fazer parte da história sem punição estrutural, enquanto perder para Ultra Beasts, Ultra Necrozma ou outro boss de ameaça mantém o conflito pendente e exige recuperação/retry.
