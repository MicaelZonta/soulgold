# SoulGold — Rift Missions

**Design consolidado v18 — Missões 1 (Blackthorn), 2 (Mahogany), 3 (Cherrygrove) e 4 (New Bark) e o evento PRÉ-NECROZMA (reunião de Olivine) em esqueleto implementado; arco de missões fechado no código e a reunião em cima dele; runtime pendente nos cinco**

Revisão V18: 20 de setembro de 2026. Substitui o V17 apenas no pós-E4. Faz duas coisas: (1) consolida no design o que a **implementação** da Missão 4 fixou como contrato (§6.4 e §22) — com isso as **quatro** missões estão em esqueleto implementado e o arco de missões está fechado no código, com runtime pendente em todas; (2) abre o primeiro evento depois das missões, o **PRÉ-NECROZMA** (§7), com documento de implementação próprio: a reunião do escritório de Olivine. Nada da campanha pré-Liga muda. Três decisões de escopo do autor nesta revisão, todas sobre esse evento: ele **acontece inteiro dentro de `OlivineCity_House1`**, com os seis personagens e os dois parceiros; **termina antes da ida ao altar**; e **entrega o gancho do altar** em vez de encená-lo, terminando numa flag persistente que o encontro com Necrozma vai consumir na sessão seguinte. O evento foi **implementado em esqueleto no mesmo dia**, inteiro e sem cortes, com build limpo e runtime pendente; o §12 do doc dele registra o feedback da implementação e vence o resto daquele arquivo onde os dois divergem.

Revisão V17: 20 de setembro de 2026. Substitui o V16 apenas no pós-E4: consolida no design o que a **implementação** da Missão 3 fixou como contrato (§6.3 e §21), fecha o conteúdo da **Missão 4** (Kartana + Guzzlord + Nihilego, New Bark, Lusamine) em §6.4 — incluindo a volta de Cherrygrove ao escritório de Olivine e o gancho que reúne o elenco inteiro lá — e **move a revelação da Anabel como Faller da reunião do §7 para dentro da Missão 4** (§3.1 e §7). Nada da campanha pré-Liga muda. A Missão 4 fica em **planejada**: o documento de implementação existe, mas nada dela está no código.

Revisão V16: 19 de setembro de 2026. Substitui o V15 apenas no pós-E4: consolida no design o que a **implementação** da Missão 2 fixou como contrato (§6.2 e §20), e abre a **Missão 3** (Blacephalon + Stakataka, Cherrygrove, Kukui) com conteúdo fechado em §6.3 e documento de implementação próprio. Nada da campanha pré-Liga muda. O arquivo da Missão 2 passou a se chamar `MAHOGANY_ULTRABEAST_IMPLEMENTATION.md`, uniformizando o nome com os das Missões 1 e 3.

Revisão V15: 19 de setembro de 2026. Substitui o V14 apenas no pós-E4: registra o estado real da Missão 1 depois da implementação em esqueleto, abre a Missão 2 (Xurkitree + Celesteela, Mahogany, Lillie) com documento de implementação próprio, e fixa a **escala de dificuldade crescente entre as missões** (ver §6, §6.2 e §19). Nada da campanha pré-Liga muda.

Revisão V14: 19 de setembro de 2026. Substitui o V13 apenas no arco pós-E4 (ligação do Looker, escritório em Olivine, Blackthorn como Missão 1 e redução de nove para quatro missões — ver §6 e §18); todo o conteúdo de campanha do V13 permanece vigente. O pós-E4 passa a ser produzido em **modo esqueleto** (skill `evento-esqueleto`): cenas simples, mas tecnicamente completas e documentadas para evolução posterior.

Revisão V13: 17 de setembro de 2026. Substitui o V12; preserva a política global de duelos narrativos, os parceiros fora da Poké Ball, Gladion antes da Victory Road e todo o arco pós-game. Consolida a implementação compilada da Lillie em Route 30, Goldenrod e Dragon’s Den, sem declarar validação em runtime.

## 1. Objetivo e autoridade deste documento

Rift Missions é uma história adicional de SoulGold que apresenta personagens de Alola durante a campanha de Johto, desenvolve uma investigação de Ultra Beasts após a Elite Four e termina em um sistema permanente de expedições com batalhas e capturas de lendários.

Este documento consolida as decisões mais recentes da conversa. Gladion em Violet, Lillie em Goldenrod e Gladion em Cianwood já possuíam implementação confirmada pelo autor, mas o V12 mantém o contrato de resultado de algumas dessas cenas; portanto, comportamento antigo incompatível deve ser refatorado sem reconstruir desnecessariamente equipes, mapas ou parâmetros já integrados. Lillie em Route 30, Goldenrod e Dragon’s Den está implementada e compilada segundo o registro de execução de 17/09/2026, mas ainda não foi validada em runtime. Gladion antes da Victory Road permanece fechado em design e pendente de implementação/teste. O estado descrito aqui refere-se ao planejamento e à implementação local documentada neste projeto.

As seções de conteúdo estabelecido são a referência para a execução. Recomendações técnicas e pendências são identificadas separadamente; não devem ser confundidas com novas decisões aprovadas. As fontes dos jogos contextualizam a inspiração; o estado vigente de cada personagem neste documento governa os diálogos do hack.

### Status e precedência

| Conteúdo | Status nesta revisão |
| --- | --- |
| Lillie inicial / Route 30 | **Implementada e compilada:** batalha com no-whiteout, outcomes WON/LOST/DREW/FORFEITED/UNKNOWN convergentes, Vulpix Alola fora da Poké Ball e saída pareada. Runtime pendente. |
| Gladion em Violet | Implementado anteriormente; V12 passa a aceitar vitória **ou derrota** antes da entrega do Mystery Egg. Refatoração de resultado pendente. |
| Lillie em Goldenrod | **Implementada e compilada:** política de vitória/derrota preservada, Vulpix Alola fora da Poké Ball e saída pareada adicionada. Runtime pendente para regressão visual. |
| Gladion em Cianwood | Implementado anteriormente; V12 mantém removida a recusa da revanche. A batalha passa a ser obrigatória e vitória/derrota convergem para Fly. Refatoração de fluxo pendente. |
| Lillie no Dragon’s Den | **Implementada e compilada:** 15 reações integradas ao quiz vanilla; 9 respostas aceitas avançam e 6 rejeitadas preservam punição/re-pergunta; Ninetales fora da Poké Ball; batalha final de 6 Pokémon com no-whiteout. Runtime pendente. |
| Gladion antes da Victory Road | **Implementada e compilada:**  Novo encontro fechado em design: batalha obrigatória, primeira apresentação de Silvally, vitória ou derrota continuam sem blackout. Implementação pendente. |
| Ligação do Looker + escritório de Olivine + Blackthorn (Missão 1) | **Esqueleto implementado (19/09/2026):** conforme [`.claude/BLACKTHORN_ULTRABEAST_IMPLEMENTATION.md`](BLACKTHORN_ULTRABEAST_IMPLEMENTATION.md), da ligação ao gancho para a Missão 2 (Looker e Anabel moram em Olivine desde o New Game; escolha da UB + boss battle). Build limpo; runtime pendente. Primeira batalha de ameaça: derrota = blackout/retry. |
| Limpeza de treinadores | Informada como concluída pelo autor; este documento não certifica IDs ou contagens livres. |
| Missão 2 — Mahogany (Xurkitree + Celesteela, Lillie) | **Esqueleto implementado (19/09/2026):** conforme [`.claude/MAHOGANY_ULTRABEAST_IMPLEMENTATION.md`](MAHOGANY_ULTRABEAST_IMPLEMENTATION.md) (§12 registra o feedback da implementação). Implementada **inteira, sem cortes**, nos cinco arquivos previstos e sem alterar nenhuma decisão de estado. Continua a var da M1 nos estados 4→5→6 e substituiu o stub da M2 em Olivine, que virou stub da M3. Primeira aplicação da escala crescente (4 barras / Lv80 / x130 / moveset curado + item). Build limpo; runtime pendente. |
| Missão 3 — Cherrygrove (Blacephalon + Stakataka, Kukui) | **Esqueleto implementado (20/09/2026):** conforme [`.claude/CHERRYGROVE_ULTRABEAST_IMPLEMENTATION.md`](CHERRYGROVE_ULTRABEAST_IMPLEMENTATION.md) (§12 registra o feedback da implementação). Implementada **inteira, sem cortes**, nos cinco arquivos previstos e sem alterar nenhuma decisão de estado. Continua a var nos estados 6→7→8 e substituiu o stub da M3 em Olivine, que virou stub da M4. Terceiro degrau da escala (4 barras / Lv85 / x140 / moveset curado + golpe de controle + item) e **primeira missão a mexer em conteúdo pré-existente** (os dois presentes do Friendly Trader). Build limpo; runtime pendente. |
| Missão 4 — New Bark (Kartana + Guzzlord + Nihilego, Lusamine) | **Esqueleto implementado (20/09/2026):** conforme [`.claude/NEWBARK_ULTRABEAST_IMPLEMENTATION.md`](NEWBARK_ULTRABEAST_IMPLEMENTATION.md) (§12 registra o feedback da implementação e **vence o resto daquele doc** onde os dois divergem). Implementada **inteira, sem cortes**, nos nove arquivos previstos e sem alterar nenhuma decisão de estado. Continua a var nos estados 8→9→10, **encerra a cadeia de missões** e transformou o stub da M4 em Olivine no stub da **reunião**. Quarto degrau da escala (4 barras / Lv90 / x150 / moveset de dois eixos + item) e primeira cena do arco com **orçamento de objetos medido em código** (12/16). Build limpo; runtime pendente. |
| Evento PRÉ-NECROZMA — reunião de Olivine (Looker, Anabel, Lusamine, Lillie + Ninetales, Gladion + Silvally, Kukui) | **Esqueleto implementado (20/09/2026):** conforme [`.claude/PRE_NECROZMA_ULTRABEAST_IMPLEMENTATION.md`](PRE_NECROZMA_ULTRABEAST_IMPLEMENTATION.md) (§12 registra o feedback da implementação e **vence o resto daquele doc** onde os dois divergem). Implementada **inteira, sem cortes**, nos cinco arquivos previstos e sem alterar nenhuma decisão de estado. Continua a var nos estados 10→11→12, **substituiu o stub da reunião** que a M4 deixou em Olivine e termina ligando `FLAG_EVENT_NECROZMA_ALTAR_UNLOCKED` — a primeira flag do arco que **nunca é limpa** e o primeiro handoff por flag entre dois documentos. Primeiro evento do arco **sem batalha nenhuma**: o papel do retry cabe ao estado 11, e a única checagem de time do arco (Solgaleo **ou** Lunala, só na equipe) pode falhar indefinidamente sem custo. Oito objetos numa sala de 11x7 (10/16 de orçamento). Build limpo; runtime pendente. Navio, altar, duelo da Lusamine e Ultra Necrozma **não** são escopo dele. |

As decisões mais recentes prevalecem sobre trechos antigos. Nos **duelos narrativos com treinadores**, a luta pode ser obrigatória, mas a vitória não é requisito de progresso: vitória ou derrota recebem falas próprias e convergem sem blackout. Menus de recusa deixam de ser usados nos encontros de campanha aqui definidos. A primeira falha tratada como derrota real de uma ameaça ocorre contra Ultra Beasts em Blackthorn; encontros de ameaça posteriores seguem sua própria recuperação. A política de dificuldade única baseada no antigo Hard permanece vigente.

O documento é autossuficiente para o design. Não exigir leitura dos refinamentos antigos para compreender as cenas aqui consolidadas. As referências externas são herdadas do V7 e do refinamento de Lillie; não representam nova pesquisa nesta revisão.

### Política V13 — duelo narrativo não é gate de vitória

Os encontros de Lillie, Gladion e outros personagens usados para desenvolvimento narrativo são conteúdo bônus integrado à jornada. Neles, **a batalha precisa acontecer quando o roteiro a prevê, mas o jogador não precisa vencer para a história continuar**.

Contrato padrão para duelo narrativo:

1. Curar quando a cena exigir igualdade de condições.
2. Ativar o mecanismo de batalha sem blackout/whiteout.
3. Executar a batalha obrigatória; não oferecer opção de recusa nos encontros definidos pelo V13.
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

A campanha de Johto mantém seu próprio conflito e sua conclusão. Os encontros recorrentes e o crescimento do Cosmog constroem o arco dos personagens durante a jornada, mas a primeira ruptura explícita das Rift Missions fica para depois da Liga. O incidente de Blackthorn abre a investigação pós-game como Missão 1 (V14), não como evento pré-E4. Não atribuir todos os acontecimentos de Johto a Necrozma nem transformar cada encontro em uma explicação sobre portais.

O efeito desejado é um mundo maior e em movimento: o jogador cruza caminhos com outras pessoas, acompanha suas mudanças e, no final, reúne aliados que conheceu ao longo da jornada. Cosmog conecta o início íntimo dessa relação à escala do desfecho no altar.

### Regra visual de parceiros recorrentes

Nos encontros de campanha e nas cenas narrativas em que estão presentes, os parceiros principais de Gladion e Lillie devem aparecer **fora da Poké Ball**, acompanhando seus Trainers no mapa sempre que a cena permitir sem quebrar colisão, follower, warps ou limites de objetos.

- **Gladion:** Type: Null permanece fora da Poké Ball em Violet e Cianwood. Depois da evolução, **Silvally continua fora da Poké Ball em todas as aparições narrativas posteriores de Gladion**, incluindo Victory Road, Blackthorn, suas Rift Missions, reunião e clímax quando ele estiver presente.
- **Lillie:** Alolan Vulpix permanece fora da Poké Ball em seus encontros iniciais e em Goldenrod. No Dragon’s Den, ela já aparece como **Alolan Ninetales**. A partir daí, **Ninetales continua fora da Poké Ball em todas as aparições narrativas posteriores de Lillie**, incluindo a missão de Xurkitree + Celesteela, reunião e clímax quando ela estiver presente.
- Essa regra é visual e narrativa; não exige sistema de follower genérico nem altera quem inicia cada batalha.
- Quando a cena começar, o parceiro deve estar posicionado de forma coerente ao lado do Trainer. Quando a cena terminar, ambos devem sair ou ser ocultados de forma coordenada quando aplicável.
- Se um mapa específico não comportar o objeto extra sem conflito técnico real, a implementação deve registrar a limitação e preservar a intenção por outro meio de encenação, sem simplesmente remover o parceiro por conveniência.


## 2. Estrutura geral

1. Apresentar Lillie, Gladion e Kukui durante a campanha normal; receber o Mystery Egg de Cosmog em Violet, o SquirtBottle com Lillie em Goldenrod e Fly com Gladion em Cianwood; concluir o arco pré-Liga de Lillie no Dragon’s Den após Clair.
2. Antes de entrar na Victory Road, reencontrar Gladion. Ele apresenta Silvally e ocorre uma batalha obrigatória que avança tanto em vitória quanto em derrota, sem blackout.
3. Concluir Victory Road e a Liga normalmente, sem ruptura de Ultra Beast obrigatória antes da E4.
4. Looker e Anabel moram em Olivine (`OlivineCity_House1`) desde o começo do jogo, com um diálogo discreto de "férias". No pós-game, depois do Hall of Fame, ao sair de casa em New Bark o jogador recebe a ligação do Elm e, logo em seguida, a de Looker, pedindo a ajuda do novo Campeão de Johto e chamando-o a Olivine.
5. Na casa de Olivine, Looker e Anabel apresentam a investigação e enviam o jogador a Blackthorn.
6. **Missão 1 — Blackthorn:** primeira ruptura explícita; Buzzwole e Pheromosa surgem juntos, com Gladion/Silvally, Looker e Anabel presentes e a cidade evacuada. O jogador escolhe qual enfrenta numa boss battle; Gladion e Silvally ficam com a outra. A partir daqui derrotas contra ameaças usam blackout/retry. O fim da missão manda o jogador de volta a Olivine.
7. Concluir as Missões 2–4 (§6), retornando ao escritório após cada uma. Após as quatro missões, apresentar Solgaleo **ou** Lunala a Looker para liberar a reunião e o navio.
8. Viajar ao altar com o parceiro evoluído do Mystery Egg para abrir a passagem até Necrozma.
9. Encenar o clímax conhecido como Eclipse no mesmo altar, resolver o conflito com Lusamine e enfrentar Ultra Necrozma.
10. Encerrar a história com uma despedida e manter Looker e Anabel no altar para expedições repetíveis.

Todo o conteúdo explícito de Ultra Beasts desta questline fica no pós-E4, incluindo Blackthorn. No V14, Blackthorn abre a investigação **e** é a Missão 1; não existe mais prólogo separado das missões. Isso não instrui remover fontes de Pokémon já existentes em outros sistemas do jogo.

## 3. Elenco e arcos

### Looker

Investiga as aparições e rupturas em Johto. Mora em Olivine com Anabel desde o começo do jogo (antes das missões, fingindo estar de férias); o antigo Looker da Route 29 foi removido no V14. Deve aparecer em todas as quests de Ultra Beasts, além de participar do incidente de Blackthorn. É o fio condutor da investigação, apresenta as missões e recebe o jogador ao final de cada uma.

Sua presença não deve se limitar a entregar tarefas no escritório: os roteiros precisam incluí-lo nas ocorrências locais. O acompanhante da tabela de missões se soma a Looker, não o substitui.

### Anabel

Anabel é uma Faller e já sabe disso nesta continuação. Ainda possui lacunas de memória. Sua experiência pessoal com o deslocamento entre realidades orienta o cuidado com quem chega pelas rupturas e sua insistência em preparar o retorno das expedições. Ela compartilha essa história com o jogador **durante a Missão 4, em New Bark** (§6.4), e a usa depois, na reunião de Olivine, para sustentar o plano de retorno (§7). Até a V16 a revelação acontecia na reunião; a V17 a antecipou para o campo.

Trabalha com Looker na investigação. Compartilha o escritório em Olivine e vende Beast Balls desde o início das missões pós-E4. Participa da preparação do evento final e, após Necrozma, permanece no altar com Looker.

O fornecimento de Beast Balls faz parte do apoio à investigação. Não é necessário introduzir uma ligação com a Ultra Recon Squad para justificar esse serviço.

### Lusamine

A história assume uma continuidade própria posterior aos acontecimentos de Alola, combinando elementos de Sun/Moon e Ultra Sun/Ultra Moon. Lusamine viaja para Johto, busca reparar seus erros e reconstruir sua relação com os filhos. Participa diretamente da missão final (Kartana + Guzzlord + Nihilego, New Bark).

O jogador a enfrenta uma única vez, perto do final. Para conter a crise, o grupo precisa atravessar uma passagem instável e derrotar Necrozma, mas existe o risco de não conseguir retornar. Lusamine insiste em assumir a operação sozinha, movida pela culpa e pela necessidade de reparação. O confronto com o jogador resolve essa disputa e conduz à aceitação de ajuda.

O encerramento do arco deve mostrar responsabilidade, cooperação e continuidade da relação familiar. O perigo da travessia é um conflito a resolver, não uma recompensa ou prova de valor pessoal.

### Lillie

Viaja com a mãe e está se encontrando como treinadora. Sua progressão pré-Liga possui três estágios claros: na Route 30 começa a batalhar; em Goldenrod aprende a observar sua parceira e adaptar um plano; no Dragon’s Den participa do mesmo teste do jogador, escuta respostas diferentes das suas e demonstra que consegue considerar outra perspectiva sem abandonar o próprio julgamento. **Vulpix acompanha Lillie fora da Poké Ball nos encontros anteriores; no Dragon’s Den, a parceira já evoluiu para Alolan Ninetales e continua visível ao lado dela. Ninetales permanece fora da Poké Ball também nas aparições pós-game de Lillie.** Atua depois na Missão 2 (Xurkitree + Celesteela, Mahogany).

No Dragon’s Den, o jogador não escolhe as respostas de Lillie. O Elder faz ao protagonista as cinco perguntas do teste vanilla; depois de cada escolha, Lillie reage ao que ouviu e formula sua própria posição. A implementação preserva o comportamento real do quiz: **9 alternativas são aceitas e avançam; 6 são rejeitadas, incrementam o contador vanilla e fazem o Elder repetir a pergunta**. Lillie reage também às seis rejeitadas, uma vez por visita, sem alterar `VAR_DRAGONS_DEN_QUIZ`. Ela pode concordar, discordar ou aceitar parte do raciocínio sem copiar o jogador. A cena não transforma sua independência em hostilidade à família: seu crescimento é demonstrado pela capacidade de ouvir sem entregar o próprio julgamento.

Ela não entrega Cosmog nem Cosmoem. O jogador recebe Cosmog pelo Mystery Egg em Violet e o desenvolve ao longo da jornada.

### Gladion

Age como um rival recorrente ao longo da história, alternando desafios e cooperação. Sua primeira batalha ocorre no Pokémon Center de Violet, onde substitui o assistente de Elm e entrega o Mystery Egg após a batalha, independentemente de vitória ou derrota do jogador. Reaparece em Cianwood após Chuck, enfrenta o jogador novamente e assume a entrega de Fly; a revanche deixa de ser opcional no V13. Antes da Victory Road, apresenta Silvally e trava a última batalha de rival da campanha, também com continuidade em vitória ou derrota. No pós-game é o acompanhante da Missão 1, em Blackthorn (Buzzwole + Pheromosa). O antigo encontro ligado à Whitney e o antigo aquecimento opcional na entrada da Liga foram removidos.

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

Na missão final, diante de Nihilego, explorar responsabilidade e limites da pesquisa, sem pressupor lembranças de uma fusão nesta continuidade. No clímax, ela quer liderar a travessia por acreditar que sua experiência lhe impõe responsabilidade. O grupo constrói um plano de retorno; a batalha demonstra coordenação e leva à aceitação de ajuda. Reconciliação exige atitudes posteriores, não apenas uma derrota.

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
| Missões 1 e 2 pós-E4 | Mostra atenção especial a desorientação e deslocamento. Não explica toda a biografia no primeiro briefing. Em Mahogany planta **uma única linha**: sente a ruptura antes de os instrumentos se moverem e corta o assunto. |
| Missão 3 (Cherrygrove) | Segunda semente, do mesmo tamanho: o mar ficou quieto antes da leitura. "Later. Not now." Nada mais. |
| **Missão 4 (New Bark), em campo** | **A revelação.** Três rupturas ao mesmo tempo são demais para ela: ela perde alguns segundos de pé, Looker a ampara, e ela conta ao jogador ali mesmo, de pé, em poucas caixas. É o pagamento das duas sementes, e não uma cena nova inventada para isso. Detalhe em §6.4. |
| Reunião em Olivine, antes de liberar o navio | Já revelada, ela **usa** a própria condição em vez de anunciá-la: é o argumento de por que ninguém atravessa sem plano de volta. Se o jogador precisar de recapitulação, cabe em uma caixa. |
| Preparação no altar | Usa essa experiência para sustentar um plano coletivo. Escuta Lusamine, mas insiste em que todos tenham uma forma de voltar. |
| Despedida e pós-Necrozma | Escolhe permanecer para ajudar a fechar rupturas e dar assistência a quem for deslocado. Sua motivação vai além da obrigação profissional. |

**Sequência de cena para Terra (V17: acontece em New Bark, no meio da Missão 4, não na reunião):**

1. As três rupturas abrem juntas. Anabel para de falar no meio de uma instrução e fica parada alguns segundos. Looker chega antes de qualquer outro e a ampara sem alarde.
2. Ela recusa sentar. Pede um momento e o toma de pé.
3. Revela que é uma Faller e que ainda faltam lembranças. A fala é serena e pessoal, sem exposição longa: o que ela descreve é uma sensação física, não um dossiê.
4. Diz o que lembra e o que não lembra — não lembra o nome do lugar de onde veio; lembra que alguém a ajudou quando chegou. Quer oferecer o mesmo a quem chegar.
5. Looker reconhece a decisão de compartilhar isso sem contar a história por ela.
6. Anabel retoma o comando na frase seguinte e escolhe sua Ultra Beast. A revelação **não** interrompe a missão: ela volta ao trabalho com ela nas costas, e é isso que a caracteriza.
7. Na reunião de Olivine (§7), a mesma condição reaparece **como argumento**, não como notícia: é por isso que ela exige um plano de volta antes de liberar o navio.

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
- Na missão final (Kartana + Guzzlord + Nihilego), dar mais peso à preparação e à confiança na equipe; não transformar a missão em uma exposição longa de seu passado.
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

### 3.2. Aplicação às quatro missões (V14)

Orientações de escrita, preservando cidades e acompanhantes definidos em §6. Cada missão junta os temas que, no V13, eram divididos entre missões separadas (histórico em §6.1):

| Missão | O que a participação revela |
| --- | --- |
| 1 · Buzzwole + Pheromosa / Gladion | Força aplicada à proteção de quem está perto, não uma disputa de ego; Silvally já age sem esperar ordem. |
| 2 · Xurkitree + Celesteela / Lillie | Ela observa antes de agir, explica sua ideia ao grupo e sustenta sua posição. |
| 3 · Blacephalon + Stakataka / Kukui | Curiosidade acompanhada de responsabilidade pelo entorno; observações de coordenação e movimento viram ajuda prática. |
| 4 · Kartana + Guzzlord + Nihilego / Lusamine | Oferece conhecimento sem exigir obediência; reconhece limites e prioriza cuidado sobre controle. **A missão põe duas mães na mesma rua** (Lusamine e a mãe do jogador) e é quem a repreende que a faz perguntar em vez de decidir. Elm, a mãe e Gold/Crystal participam sem batalhar. |

Looker participa de todas as quests. Anabel ajuda a estabelecer objetivos e condições de segurança. Os acompanhantes não devem repetir a mesma explicação do investigador com palavras diferentes.

**Continuidade visual dos parceiros:** quando Lillie participa (Missão 2 e cenas finais), Alolan Ninetales deve estar presente fora da Poké Ball ao lado dela. Quando Gladion participa (Missão 1 e cenas finais), Silvally deve estar presente fora da Poké Ball ao lado dele. A batalha específica da missão pode usar outros membros da equipe; a presença overworld do parceiro principal continua sendo parte da identidade visual da cena.

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
| Blackthorn — Missão 1 | Pós-game: ligação do Looker ao sair de casa após o HoF → briefing em Olivine | Primeira ruptura explícita: Buzzwole + Pheromosa ao mesmo tempo, com Gladion/Silvally, Looker e Anabel na cidade evacuada; o jogador escolhe qual enfrenta (boss battle) e Gladion fica com a outra; derrota é falha real com blackout/retry. Termina com gancho de volta a Olivine. |

A ordem pré-Liga fica: **Route 30 → Violet → Goldenrod → Cianwood → Dragon’s Den → Gladion antes da Victory Road → Victory Road → Liga**. A ordem lista apenas os encontros desta questline, não todos os eventos vanilla entre eles. Não existe mais batalha opcional de Gladion na entrada da Liga.

Depois da E4: **ligação do Looker → escritório de Olivine → Missão 1 (Blackthorn) → Olivine → Missões 2, 3 e 4 com retorno a Olivine após cada → reunião/altar → Lusamine → Ultra Necrozma**.

**Diretriz para Blackthorn:** o incidente abre a trama pós-game e é o primeiro confronto em que derrota deixa de ser apenas um resultado de personagem. No V14 ele é a Missão 1 e não deve oferecer captura antecipada de Buzzwole ou Pheromosa: a implementação bloqueia a captura (`B_FLAG_NO_CATCHING`). **Formato da batalha (V14, revisão 2):** o jogador escolhe Buzzwole ou Pheromosa e enfrenta a escolhida numa **boss battle simples** pelo sistema de boss do projeto (`setbossbattle`, várias barras de HP, IA inteligente); Gladion e Silvally enfrentam a outra, de forma narrativa. "Run" num boss é desistência e dá blackout, como a derrota. Motivo técnico, verificado em 19/09/2026: o boss só existe em batalha simples, e batalha selvagem com parceiro só existe via NPC follower (desligado).

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

**Status V13:** implementado e compilado em 17/09/2026; runtime ainda pendente. A implementação preserva o quiz vanilla, integra Lillie/Ninetales ao Shrine e adiciona a batalha final pré-Liga da Lillie.

#### Papel no arco

O Dragon’s Den fecha o mini-arco pré-Liga da Lillie:

1. **Route 30:** começa a batalhar.
2. **Goldenrod:** aprende que um plano só funciona se ela continuar observando sua parceira.
3. **Dragon’s Den:** escuta as mesmas perguntas que o jogador, reage às escolhas dele e demonstra que consegue considerar outra perspectiva sem abandonar o próprio julgamento.

Alolan Vulpix já evoluiu antes da cena. **Alolan Ninetales está fora da Poké Ball desde a chegada ao Shrine** e permanece visível durante o reencontro, quiz, transição para batalha e despedida.

#### Estrutura real do quiz

O quiz deste projeto é `loop-until-correct`, não um questionário em que todas as alternativas avançam.

Mapa real:

| Pergunta | Alternativa | Índice | Resultado vanilla |
| --- | --- | ---: | --- |
| Q1 | Pal / Ally | 0 | aceita |
| Q1 | Underling / Junior | 1 | rejeitada |
| Q1 | Friend | 2 | aceita |
| Q2 | Strategy | 0 | aceita |
| Q2 | Training | 1 | aceita |
| Q2 | Cheating | 2 | rejeitada |
| Q3 | Weak person | 0 | rejeitada |
| Q3 | Tough person / Strong | 1 | aceita |
| Q3 | Anybody | 2 | aceita |
| Q4 | Love | 0 | aceita |
| Q4 | Violence | 1 | rejeitada |
| Q4 | Knowledge | 2 | aceita |
| Q5 | Tough / Strength | 0 | rejeitada |
| Q5 | Weak / Weakness | 1 | rejeitada |
| Q5 | Both | 2 | aceita |

Portanto:

```text
9 respostas aceitas
→ RightAnswer vanilla
→ reação completa da Lillie
→ próxima pergunta

6 respostas rejeitadas
→ ElderWrong vanilla
→ VAR_DRAGONS_DEN_QUIZ++
→ reação curta da Lillie (uma vez por visita)
→ repetir a mesma pergunta
```

As seis falas rejeitadas usam `FLAG_TEMP_2` até `FLAG_TEMP_7`, uma por fala. Elas são temporárias e não criam save persistente.

A ordem real dos menus deve ser respeitada:
- Q4 = Love / Violence / Knowledge
- Q5 = Tough / Weak / Both

#### Recompensa e contador

A camada da Lillie não altera:
- `VAR_DRAGONS_DEN_QUIZ`;
- lógica de resposta correta/incorreta;
- Risingbadge;
- estado de Clair;
- Dratini;
- movimentos/recompensas vanilla.

O Dratini especial continua dependendo de **zero erros**. Uma resposta rejeitada continua custando essa condição exatamente como no jogo atual.

#### Encenação implementada

Posições:

```text
Elder      (6,9)
Lillie     (7,9)
Ninetales  (8,9)
Player     (6,10)
Follower   ~ (6,11)
```

Objetos do Shrine:
1. Elder
2. Elder2
3. Elder3
4. Clair
5. Lillie
6. Ninetales

**Clair continua obrigatoriamente como objeto 4.**

Lillie e Ninetales foram appendados após Clair. `LOCALID_DRAGONSDEN3_LILLIE = 5` e `LOCALID_DRAGONSDEN3_NINETALES = 6`.

Um `MAP_SCRIPT_ON_TRANSITION` foi adicionado. `FLAG_TEMP_1` controla a visibilidade temporária de Lillie/Ninetales conforme `VAR_BLACKTHORN_CITY_STATE == 2`. As flags temporárias 2–7 controlam as seis reações rejeitadas já mostradas naquela visita.

#### Fala de conclusão do Elder

A fala antiga que dizia que os dois “não deram sempre as mesmas respostas” foi removida porque podia ser falsa.

Texto vigente:

> Elder: “Interesting.”
>
> “You listened to the same questions.”
>
> “Yet each answer still had to be your own.”
>
> “Understanding another Trainer does not require surrendering your own judgment.”

Depois:

> Elder: “You listened before answering, yet you did not surrender your own judgment.”

Lillie:

> “I almost did.”
>
> “A few times.”
>
> “But then they wouldn't really have been my answers.”

#### Transição para a batalha

O Elder transforma o teste de palavras em demonstração prática. A batalha é obrigatória, mas não exige vitória.

Contrato:

```text
cura
→ salvar estado anterior de B_FLAG_NO_WHITEOUT
→ ativar B_FLAG_NO_WHITEOUT
→ trainerbattle_no_intro TRAINER_LILLIE_DRAGONS_DEN
→ GetBattleOutcome
→ copiar imediatamente para VAR_TEMP_3
→ restaurar B_FLAG_NO_WHITEOUT
→ WON / LOST / DREW / FORFEITED / UNKNOWN
→ cura
→ conclusão do Elder
→ saída Lillie + Ninetales
→ ClairEnter vanilla
```

A progressão nunca depende da flag de trainer derrotado.

#### Trainer e equipe final

`TRAINER_LILLIE_DRAGONS_DEN = 970`, reaproveitando o antigo `TRAINER_UNUSED_106`, que foi verificado como livre antes do uso.

A party foi calibrada contra o dataset único atual de Clair. Não existe mais uma equipe Hard separada: `DIFFICULTY_HARD` é alias do único dataset vigente.

Referência:
- Clair: níveis 58/58/58/58/58/59;
- Elite Four / Lance: aproximadamente 68–70.

Equipe final da Lillie:

| Ordem | Pokémon | Lv | Item | Ability | Nature | Golpes |
| ---: | --- | ---: | --- | --- | --- | --- |
| 1 | **Alolan Ninetales** | 62 | Light Clay | Snow Warning | Timid | Aurora Veil, Freeze-Dry, Moonblast, Encore |
| 2 | Ribombee | 59 | Focus Sash | Shield Dust | Timid | Sticky Web, Pollen Puff, Psychic, U-Turn |
| 3 | Clefable | 60 | Leftovers | Magic Guard | Bold | Moonblast, Thunder Wave, Moonlight, Flamethrower |
| 4 | Lilligant | 59 | Lum Berry | Own Tempo | Timid | Quiver Dance, Giga Drain, Sleep Powder, Pollen Puff |
| 5 | Milotic | 61 | Leftovers | Marvel Scale | Bold | Scald, Ice Beam, Recover, Haze |
| 6 | Comfey | 60 | Big Root | Triage | Modest | Draining Kiss, Giga Drain, Calm Mind, Synthesis |

Configuração:
- `Smart Trainer`;
- IVs 31;
- EVs 252/252/4;
- Ninetales é **lead e ace narrativo**;
- time completo de seis Pokémon;
- dificuldade acima de Clair e abaixo da Elite Four.

Ninetales abre para ativar Snow no turno 1 e tornar Aurora Veil utilizável pela IA. O comportamento real da IA ainda precisa ser testado em runtime.

#### Snow e recuperação

Não alterar Moonlight/Synthesis antes do runtime. Como Snow reduz a eficiência desses golpes no engine local, o primeiro teste deve verificar se Clefable/Comfey ficam significativamente piores. Só então considerar mudança.

#### Saída

Lillie e Ninetales saem **antes de Clair entrar**. Ambos usam movimentos próprios e `waitmovement` com IDs explícitos. Depois da remoção dos dois, a coreografia vanilla de Clair/Elder roda com o corredor livre.

#### Estado

`VAR_BLACKTHORN_CITY_STATE` permanece a autoridade:
- 2 = cena/quiz pendentes;
- 3 = quiz + batalha + ClairEnter concluídos;
- 4 = cena posterior de Clair na Cavern concluída / Dratini liberado.

Nenhuma nova flag persistente foi criada.

#### Evidência atual

- **Inspecionado:** sim.
- **Compilado:** sim.
- **Runtime:** não testado ainda.

Pontos obrigatórios para runtime:
- 0 erros → Dratini especial;
- ≥1 erro → Dratini básico;
- seis respostas rejeitadas repetem corretamente;
- 15 falas aparecem no branch correto;
- Ninetales visível e sem colisão;
- vitória/derrota/empate/forfeit continuam;
- Aurora Veil é usada adequadamente;
- Snow não destrói o sustain do próprio time;
- Risingbadge/Clair/Dratini permanecem intactos.


### 4.9. Gladion antes da Victory Road — “O primeiro passo”

**Status:** novo encontro fechado em design no V13; implementação e balanceamento pendentes.

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

**Local definido (V14):** `OlivineCity_House1` — a casa da rua norte de Olivine mais próxima do Ginásio. O NPC da troca do Voltorb Hisuiano que ocupava a casa muda para `OlivineCity_House3`, posição (7,4), mantendo `FLAG_OLIVINE_NPC_TRADE_COMPLETED`.

**Entrada no arco:** depois do primeiro Hall of Fame, ao sair de casa em New Bark, Looker liga para o jogador, apresenta-se, fala das aparições de seres estranhos e pede ajuda ao novo Campeão de Johto. Ao chegar à casa, Looker e Anabel recebem o jogador numa cena automática e o enviam a Blackthorn. O escritório é visitado **antes** da Missão 1 e depois de cada missão.

Looker e Anabel moram na casa **desde o New Game, sem flag de visibilidade**; `VAR_RIFT_MISSIONS_STATE` só troca o diálogo ("férias" antes da ligação, briefing, "vá na frente", stub da próxima missão) e dispara a cena de chegada. A cena de chegada e o despachante de briefing atendem **todas** as missões: cada retorno ao escritório reaproveita a mesma coreografia e só troca o texto e o par flag/estado que ela seta. Durante as missões eles aparecem em Olivine e no local da missão ao mesmo tempo — **aceito pelo autor**: a missão inteira é uma cutscene, e não se esconde ninguém em Olivine. Estado e implementação: [`.claude/BLACKTHORN_ULTRABEAST_IMPLEMENTATION.md`](BLACKTHORN_ULTRABEAST_IMPLEMENTATION.md) (§1.2 e §3) para a entrada no arco e a Missão 1; [`.claude/MAHOGANY_ULTRABEAST_IMPLEMENTATION.md`](MAHOGANY_ULTRABEAST_IMPLEMENTATION.md) (§2) para o retorno ao escritório e o briefing da Missão 2; [`.claude/CHERRYGROVE_ULTRABEAST_IMPLEMENTATION.md`](CHERRYGROVE_ULTRABEAST_IMPLEMENTATION.md) (§2) para o da Missão 3. A partir da M2 o padrão está fechado: **cada missão nova acrescenta um estado ao gatilho de chegada e um ramo ao despachante `BriefingTalk`, e renomeia o stub da missão seguinte** — nenhum objeto novo, nenhuma coreografia nova.

O escritório concentra o briefing da missão ativa, o retorno após cada missão e a compra de Beast Balls com Anabel. As missões são consecutivas, seguindo a ordem fixa abaixo. Não é necessário criar um sistema aberto de seleção durante essa parte da história.

Cada missão deve ter uma ocorrência local, participação do elenco indicado e resolução que permita ao jogador apresentar o resultado a Looker. Os objetivos intermediários e diálogos completos serão desenvolvidos a partir das diretrizes de personagem; este design não estabelece puzzles ou minijogos obrigatórios.

## 6. As quatro missões pós-E4 (V14)

Para deixar o pós-game mais dinâmico e menos maçante, as nove missões de uma Ultra Beast cada foram condensadas em **quatro missões de chefes simultâneos**: duas Ultra Beasts por missão, e três na missão final.

| Ordem | Ultra Beasts | Cidade | Personagem em destaque, além de Looker | Estado do evento | Implementação |
| --- | --- | --- | --- | --- | --- |
| 1 | Buzzwole + Pheromosa | Blackthorn | Gladion (+ Silvally); Anabel presente | **Esqueleto implementado** (19/09/2026), build limpo, runtime pendente | [`.claude/BLACKTHORN_ULTRABEAST_IMPLEMENTATION.md`](BLACKTHORN_ULTRABEAST_IMPLEMENTATION.md) |
| 2 | Xurkitree + Celesteela | Mahogany | Lillie (+ Ninetales); Anabel presente | **Esqueleto implementado** (19/09/2026), build limpo, runtime pendente | [`.claude/MAHOGANY_ULTRABEAST_IMPLEMENTATION.md`](MAHOGANY_ULTRABEAST_IMPLEMENTATION.md) |
| 3 | Blacephalon + Stakataka | Cherrygrove | Kukui (sem parceiro fora da Poké Ball); Anabel presente | **Esqueleto implementado** (20/09/2026), build limpo, runtime pendente | [`.claude/CHERRYGROVE_ULTRABEAST_IMPLEMENTATION.md`](CHERRYGROVE_ULTRABEAST_IMPLEMENTATION.md) |
| 4 | Kartana + Guzzlord + Nihilego | New Bark | Lusamine + Anabel (ficam com as duas UBs que o jogador não escolher); **Prof. Elm, a mãe do jogador e Gold/Crystal** em papéis sem batalha | **Esqueleto implementado** (20/09/2026), build limpo, runtime pendente | [`.claude/NEWBARK_ULTRABEAST_IMPLEMENTATION.md`](NEWBARK_ULTRABEAST_IMPLEMENTATION.md) |

Estados possíveis de um evento, conforme a skill `evento-esqueleto`: **não planejado** → **planejado** (doc de implementação escrito) → **esqueleto implementado** (build limpo) → **validado em runtime** → **evoluído** (falas, coreografia e balanceamento finais). Nenhum evento avança de estado neste documento sem o doc correspondente ser atualizado junto.

A progressão exige retorno ao escritório de Olivine após cada missão; cada missão termina com um gancho que manda o jogador de volta. A Missão 4 é a última ocorrência e prepara a transição para o encerramento da investigação e a expedição ao altar.

Regras comuns a todas as missões:

- **Escolha + boss (estrutura padrão, V14 revisão 2):** as UBs da missão surgem juntas; o jogador escolhe qual enfrenta e o acompanhante fica com a(s) outra(s). A luta do jogador é uma boss battle simples com captura bloqueada; a do acompanhante é narrativa e muda a fala depois da vitória. A escolha é refeita a cada tentativa. Isso deixa a história dinâmica e cada missão rejogável de outro jeito.
- Batalha de ameaça: derrota ou desistência = blackout no Pokémon Center e retry, sem avançar o estado. O retry vem de manter o estado "missão ativa" até a vitória.
- Durante a missão ativa, a cidade é evacuada: NPCs e Pokémon ambientes escondidos por uma flag de evento; ficam só o elenco da missão. Joy e o interior dos prédios continuam funcionando.
- A cena é 100% scriptada a partir da confirmação do jogador na primeira conversa com Looker.
- Progresso em uma única var (`VAR_RIFT_MISSIONS_STATE`, numeração continua a partir do doc de Blackthorn). Cada missão ocupa **três valores**: briefing pendente → incidente ativo → resolvido. Missão 1 = 2/3/4, Missão 2 = 4/5/6, e assim por diante, com o valor "resolvido" de uma servindo de "briefing pendente" da seguinte.
- Cada missão ganha **uma** flag persistente própria, só para esvaziar a cidade (o campo `flag` do `map.json` não lê var), com a invariante flag setada ⇔ var no valor "ativo". Flag de batalha (`FLAG_NO_CATCHING`) é compartilhada por todas.
- **Dificuldade crescente (V15).** A Missão 1 é a mais fácil de propósito: é onde o jogador aprende que perder para uma Ultra Beast custa blackout. As missões seguintes sobem de patamar em barras de vida, nível, multiplicador de status, moveset curado e item segurado. Referência fixada: M1 = 2 barras / Lv70 / x110 / golpes de nível; M2 = 4 barras / Lv80 / x130 / moveset curado + item; **M3 = 4 barras / Lv85 / x140 / moveset curado com um golpe de controle por chefe + item**; **M4 = 4 barras / Lv90 / x150 / moveset de dois eixos (preparo + controle) + item**. A partir da M2 as barras estão no teto da engine (`MAX_BOSS_HEALTH_BARS 4`), então a escalada passa a vir de nível, multiplicador e **qualidade do moveset** — não de mais barras.


  **Ressalva da V17.** x140 (M3) nunca foi jogado, e o doc da M3 o registra como possível parede. O x150 da M4 é portanto um **alvo condicional**: se o runtime da M3 mostrar que x140 já é parede, a M4 herda o número corrigido em vez de continuar subindo. Nenhuma missão se balanceia por cima de um número não testado abaixo dela.
- Missão final com três Ultra Beasts: o jogador escolhe uma; **Lusamine e Anabel** ficam com as outras duas (decisão do autor). Looker não batalha. A distribuição deixou de ser detalhe do doc: a V17 a fixou em §6.4, porque qual UB sobra para Lusamine é uma decisão de personagem, não de conveniência.
- **A cadeia de estados termina na M4.** A regra de que o valor "resolvido" de uma missão é o "briefing pendente" da seguinte vale de M1 a M4 (2/3/4, 4/5/6, 6/7/8, 8/9/10). O valor 10 não abre missão nenhuma: significa *quatro missões concluídas, reunião de Olivine pendente*, e é de onde o §7 continua.

### 6.1. Como era antes (V13, substituído)

Registrado para consulta; não implementar.

- Blackthorn era um **prólogo** fora da contagem: jogador + Gladion/Silvally contra Buzzwole + Pheromosa, com Looker; ao final, Looker encaminhava o jogador ao escritório de Olivine, cuja casa não estava escolhida. O escritório só abria **depois** de Blackthorn.
- Havia **nove missões** consecutivas, uma Ultra Beast cada:

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

- Orientação de escrita V13 por missão: Buzzwole/Gladion — força a serviço da proteção; Pheromosa/Lillie — observa antes de agir e decide sozinha; Xurkitree/Gladion — aceita dividir tarefas; Celesteela/Lillie — explica e sustenta sua ideia; Blacephalon/Kukui — curiosidade com responsabilidade; Stakataka/Kukui — observação vira ajuda prática; Kartana/Lusamine — conhecimento sem exigir obediência; Guzzlord/Lillie e Gladion — irmãos como parceiros; Nihilego/Lusamine — limites e cuidado acima de controle.
- Gladion participava de Buzzwole, Xurkitree e Guzzlord; Lillie de Pheromosa, Celesteela e Guzzlord; Lusamine de Kartana e Nihilego. Kitakami, Goldenrod, Olivine (como local de missão), Cianwood, Violet e Ecruteak deixam de ser locais de missão no V14.

As capturas das Ultra Beasts integram o objetivo de disponibilizar esses Pokémon. A condição exata para concluir uma missão — captura ou vitória com captura disponível depois — ainda precisa ser definida. Nenhuma escolha pode tornar uma espécie permanentemente indisponível por uma derrota ou captura perdida.

Os acompanhantes indicam participação narrativa. Não se deve presumir que todas as missões serão batalhas com aliado: esse formato só está fechado para o encontro de Blackthorn.

### 6.2. Missão 2 — Mahogany (Xurkitree + Celesteela / Lillie) — conteúdo fechado

Decidido na V15; implementação detalhada em [`.claude/MAHOGANY_ULTRABEAST_IMPLEMENTATION.md`](MAHOGANY_ULTRABEAST_IMPLEMENTATION.md).

**Ocorrência.** Mahogany Town está sem energia há três noites. O gancho de Blackthorn aponta para "luzes estranhas sobre o Lake of Rage"; o briefing de Olivine **corrige** a origem: a leitura vem da própria cidade. Essa correção é obra da Lillie, que chegou antes da polícia e passou dois dias observando.

**Elenco e função.** Looker conduz e recebe o relatório; Anabel cuida da evacuação (os moradores estão no porão do Ginásio) e confirma pelos instrumentos o que Lillie deduziu observando; Lillie é a autoridade técnica da cena. Alolan Ninetales está fora da Poké Ball ao lado dela do começo ao fim, conforme §3.2.

**O que Lillie revela.** As duas Ultra Beasts não estão caçando: estão se alimentando uma da outra. Xurkitree drena a corrente da cidade, Celesteela queima essa energia e recarrega o ambiente. Atacar as duas juntas as fortalece; a única saída é **separá-las e segurá-las apartadas** — que é exatamente a estrutura padrão escolha + boss. Looker duvida da conclusão ("isso é muita coisa a concluir de anotações"), Lillie **sustenta a posição** com o que mediu, e Anabel a confirma. É a cena que entrega o tema da missão definido em §3.2: observar antes de agir, explicar a ideia ao grupo, sustentá-la.

**Anabel.** Uma única linha planta sua condição de Faller — ela sente a ruptura antes de os instrumentos se moverem e corta o assunto ("Never mind. Later."). A revelação completa continua reservada para a reunião antes do altar (§7, item 6). Não adiantar.

**Chefes.** Primeira aplicação da escala crescente: 4 barras (teto da engine), nível 80, multiplicador de status 130, moveset curado de quatro golpes e item segurado — Xurkitree com Tail Glow + Magnet, Celesteela com cobertura física/especial + Leftovers. Captura bloqueada; derrota ou desistência = blackout no Centro de Mahogany e retry, com a escolha refeita.

**Gancho.** A cidade recupera a luz; Anabel pede as anotações de Lillie; chega o relatório de **Cherrygrove**, com duas assinaturas e "um homem de jaleco que não sai da praia" — Kukui. Looker manda o jogador de volta ao escritório de Olivine para o briefing da Missão 3. Lillie fica em campo e pede que avisem o Professor de que ela está bem.

**O que a implementação da Missão 2 fixou (19/09/2026).** O esqueleto foi
implementado inteiro, sem cortes, nos cinco arquivos previstos pelo plano e sem
alterar nenhuma decisão de estado. O que saiu de lá e passa a valer como contrato
para as missões seguintes:

- **`FLAG_EVENT_ULTRABEAST_MAHOGANY` = `0x1042`,** com `CUSTOM_FLAGS_END` movida
  para ela. Cada missão nova ocupa a próxima flag livre e move `CUSTOM_FLAGS_END`
  junto (a M3 fica em `0x1043`).
- **O escritório de Olivine virou um padrão de acréscimo.** Cada missão
  acrescenta um `goto_if_eq` ao gatilho de chegada, um ramo ao despachante
  `BriefingTalk` e dois ramos por NPC (o "vá na frente" da missão ativa e o stub
  da seguinte). Nenhum objeto novo em `OlivineCity_House1` desde a M1.
- **`goto_if_ge VAR_RIFT_MISSIONS_STATE, <n>` é a armadilha recorrente:** um
  desses sobrando em qualquer ramo engole os estados da missão seguinte. Todo doc
  de missão precisa da checagem por `grep` depois de editar Olivine.
- **`local_id` explícito no `map.json`** para todo objeto novo de missão, com o
  nome da constante. Isso não revoga a regra de anexar sempre no fim de
  `object_events`.
- **Conferir os gatilhos herdados do mapa antes de esconder os objetos que eles
  referenciam** (`coord_events`, `ON_FRAME_TABLE`). Em Mahogany a checagem
  mostrou que `VAR_MAHOGANY_TOWN_STATE` vale 17 no pós-E4 e nenhum dos 48
  `coord_events` do vendedor dispara.
- **A questline inteira é estritamente pós-E4:** `VAR_RIFT_MISSIONS_STATE` só sai
  de 0 em `PokemonLeague_HallOfFame`. Toda missão pode assumir isso ao avaliar as
  vars de progresso do mapa que vai esvaziar.
- **O que o build não prova** está registrado em §12.4 daquele doc e continua
  pendente: se o "bolso de parede" do Looker é mesmo inalcançável, se x130 com 4
  barras é ameaça ou parede, e se o follower volta certo nas duas saídas.

### 6.3. Missão 3 — Cherrygrove (Blacephalon + Stakataka / Kukui) — conteúdo fechado

Decidido na V16; implementação detalhada em [`.claude/CHERRYGROVE_ULTRABEAST_IMPLEMENTATION.md`](CHERRYGROVE_ULTRABEAST_IMPLEMENTATION.md).

**Ocorrência.** A ruptura de Cherrygrove não abre em terra: abre **sobre o mar**,
na frente da praia noroeste, e vem se abrindo e fechando num ritmo há quatro
dias. É por isso que o gancho da Missão 2 descreve Kukui como "um homem de jaleco
que não sai da praia" — ele não sai porque a abertura é intermitente e alguém
precisa estar olhando quando acontecer.

**Elenco e função.** Looker conduz e recebe o relatório; Anabel cuidou da
evacuação (a cidade foi levada para o Ginásio de Violet) e confirma a leitura do
Kukui com um dado; Kukui é a autoridade técnica da cena. **Kukui não tem Pokémon
fora da Poké Ball** — a regra visual de §3.2 nomeia apenas Lillie e Gladion, e
esta é a primeira missão com três atores de elenco em vez de quatro. Decisão do
autor, confirmada: não abrir exceção por conveniência de cena.

**Evacuação.** Cherrygrove esvazia **por completo**, incluindo o Friendly Trader
e os dois Pokémon que ele oferece de presente. Decisão do autor: nenhum morador
fica de pé numa cidade evacuada só porque o objeto dele já tinha flag própria.
O custo técnico e o risco de regressão disso estão em §3.1.1 do doc da missão.

**O que Kukui revela.** As duas Ultra Beasts trabalham **em par, e a coordenação
é a arma delas**: Blacephalon entra primeiro e chama toda a atenção com as luzes,
e Stakataka avança por trás enquanto ninguém está olhando. A contramedida é a
mesma estrutura padrão escolha + boss: alguém precisa segurar o olhar de uma para
que a outra não possa se esconder. É a cena que entrega o tema da missão definido
em §3.2 — observação de coordenação e movimento virando ajuda prática.

**A responsabilidade do Kukui.** Looker cobra os quatro dias na praia sob uma
ruptura aberta. Kukui responde com o motivo, não com desculpa: se a fenda abrisse
sem ninguém olhando, ninguém saberia a hora de mandar a cidade correr. Anabel
fecha a discussão com o dado — ele previu a segunda abertura com onze minutos de
antecedência. É assim que a "curiosidade com responsabilidade pelo entorno" de
§3.2 aparece em cena, sem virar lição.

**Anabel.** Uma única linha continua a semente de Faller plantada em Mahogany —
o mar ficou quieto antes de os instrumentos se moverem, e ela corta o assunto
("Later. Not now."). A revelação completa continua reservada para a reunião antes
do altar (§7, item 6). Não adiantar.

**Chefes.** Terceiro degrau da escala crescente: 4 barras (teto da engine),
nível 85, multiplicador 140 e, principalmente, **um golpe de controle em cada
chefe** — Blacephalon com Calm Mind (+ Wise Glasses), Stakataka com Trick Room
(+ Weakness Policy). Com as barras no teto desde a M2, é o moveset que carrega a
escalada. Captura bloqueada; derrota ou desistência = blackout no Centro de
Cherrygrove e retry, com a escolha refeita.

**Gancho.** O mar volta ao normal e as duas voltam sozinhas; Looker tira Kukui da
praia à força; chega o relatório de **New Bark Town**, com **três** assinaturas —
a cidade onde o jogador começou — e a notícia de que há uma mulher já esperando
na estrada, que deu um nome: **Lusamine**. Looker manda o jogador de volta ao
escritório de Olivine para o briefing da Missão 4, dizendo explicitamente que
dessa vez ninguém entra sem preparação.

**O que a implementação da Missão 3 fixou (20/09/2026).** O esqueleto saiu
inteiro, sem cortes, nos cinco arquivos previstos e sem alterar nenhuma decisão
de estado (feedback completo em §12 daquele doc). O que vale como contrato para
a Missão 4:

- **`FLAG_EVENT_ULTRABEAST_CHERRYGROVE` = `0x1043`,** com `CUSTOM_FLAGS_END`
  movida para ela. Numeração confirmada: M3 = 6/7/8, e a M4 começa em 8.
- **Evacuar objeto de flag alheia tem caminho aprovado e caminho proibido.**
  Aprovado: trocar o campo `flag` do template por um cache temporário
  recalculado no load e acrescentar o `setflag` persistente explícito que o
  `removeobject` fazia por efeito colateral. Proibido: `removeobject` em objeto
  de moradia. É hoje o maior risco de **regressão silenciosa** do projeto — se
  os dois `setflag` do Friendly Trader falharem, o presente vira repetível com
  build limpo e sem sintoma.
- **A leitura de mapa deste repo não é a do `pokeemerald`,** e a diferença é
  silenciosa: com as máscaras clássicas sai uma planta plausível e falsa. §12.7
  do doc da M3 tem a tabela e as duas conferências baratas, e é **leitura
  obrigatória** antes de medir qualquer cena nova. Em cena de costa, ler colisão
  **e** comportamento: água rasa tem colisão 0 e o jogador anda nela.
- **Nenhum `goto_if_ge VAR_RIFT_MISSIONS_STATE` novo em Olivine sem checagem.**
  A M3 teve de apagar exatamente uma dessas linhas, deixada pela M2, que engolia
  os estados 7 e 8.
- **O que o build não prova** continua em §12.4 daquele doc: a regressão do
  presente do trader, o spawn do elenco, se x140 com 4 barras é ameaça ou
  parede, o sprite 32x32 sobre água e o follower nas duas saídas.

### 6.4. Missão 4 — New Bark (Kartana + Guzzlord + Nihilego / Lusamine) — conteúdo fechado

Decidido na V17 e **implementado em esqueleto em 20/09/2026**; implementação
detalhada em
[`NEWBARK_ULTRABEAST_IMPLEMENTATION.md`](NEWBARK_ULTRABEAST_IMPLEMENTATION.md),
cujo **§12 é a verdade** onde o plano e o código divergiram. Build limpo;
runtime pendente.

**O que muda de tamanho.** As três primeiras missões são a mesma peça em três
cidades. A quarta mantém a estrutura — ela é o contrato do arco — e muda tudo em
volta: é **New Bark**, a cidade onde o jogador começou e a única do arco sem
Centro Pokémon e sem Ginásio; são **três** Ultra Beasts; é a primeira cidade que
**não quer evacuar**; entram três personagens que o jogador conhece desde a
primeira hora de jogo (**Elm**, **a mãe** e **Gold/Crystal**); é onde a **Anabel
revela que é uma Faller**; e é o primeiro encontro cara a cara com a
**Lusamine**. Consequência de escrita: é a única missão em que o design autoriza
gastar mais caixas de texto que as outras, respeitadas as regras de §3.3.

**A volta de Cherrygrove no escritório.** O escritório segue o padrão de
acréscimo fechado desde a M2 (§5) — o que muda é o tom. Looker recebe o
relatório e pergunta pelo Kukui **antes** de perguntar pelas Ultra Beasts; o
Kukui não está em Olivine, foi direto para New Bark levar o método dele ao Elm
(é assim que o "write it down" do gancho da M3 desemboca nesta missão, sem cena
própria). Anabel põe as três leituras na mesa, começa a dizer o que sente e para
na metade — **terceira e última semente** antes da revelação em campo. Looker diz
o que a cidade é e admite que a evacuação **falhou**, porque parte dos moradores
se recusou a sair e uma delas é a mãe do jogador. E então faz o que não fez em
três missões: **pergunta se o jogador quer ir**. Não é menu de recusa; é a
pergunta dita em voz alta, e é ela que estabelece o tamanho desta missão.

**Ocorrência.** Três rupturas abrem sobre New Bark ao mesmo tempo, em terra —
não há mar envolvido. O laboratório do Elm registra a mesma anomalia há semanas
e ele a arquivou como defeito de instrumento; é um erro humilde e inteiramente
dele, que ele admite sem que ninguém cobre. Com o método do Kukui, ele
recalculou e viu o ritmo — é ele o cronômetro da cena.

**Elenco e função.** Looker conduz, cuida das pessoas antes do relatório e
ampara a Anabel; **não batalha**. Anabel comanda a retirada, quebra pela primeira
vez no arco e fica com uma UB. Lusamine é a autoridade técnica **e** o nó da
cena. Elm é o cronômetro e o abrigo. A mãe do jogador recusa o abrigo. Gold ou
Crystal — conforme o gênero do jogador — faz a evacuação porta a porta, pede
para lutar, aceita o não e assume um trabalho real. **Nenhum dos três novos
batalha.** A regra visual de §3.2 não é flexibilizada: Lusamine não ganha
parceiro fora da Poké Ball; o Marill do Gold/Crystal não é exceção, é o par que
já existe no mapa desde o começo do jogo.

**O que Lusamine revela.** A razão de o ponto fraco ser justamente New Bark é
que o parceiro da família de Cosmog que o jogador criou desde Violet **brilha**,
e ela é a única pessoa viva que sabe como aquilo se parece do outro lado —
porque um dia usou um Cosmog exatamente assim. Ela conta isso sem que ninguém
pergunte. Regra inegociável: **isso não é culpa do jogador, e a cena não pode
sugerir que seja.** Quem diz isso em voz alta é ela, na mesma cena em que o
assunto aparece. Não é absolvição: é a forma que a reparação dela assume aqui.

**O nó da cena.** Lusamine anuncia que fica com as três. Não é bravata — é a
conduta dela de sempre (§3), agora com um argumento que soa bom. **Quem a faz
parar é a mãe do jogador**, não Looker, não Anabel, não o jogador: mãe para mãe,
sem sermão, em poucas caixas. A mãe não sabe nada de Ultra Beasts e não precisa
saber; ela reconhece a coisa que está vendo porque é a mesma que ela faria, e
diz por que não é proteção. É o único momento do arco em que alguém de fora da
investigação tem razão contra um especialista. Depois disso, Lusamine faz o que
não faz desde Alola: **pergunta**. Pergunta à Anabel o que os instrumentos dizem
e pergunta ao jogador qual das três ele vai enfrentar — **essa pergunta é o menu
de escolha**, e é a melhor justificativa narrativa que a estrutura padrão recebeu
no arco.

**Anabel.** A revelação entra entre o pedido da Lusamine e a escolha do jogador,
pela sequência de §3.1: três rupturas simultâneas são demais, ela para no meio de
uma instrução, Looker a ampara, ela recusa sentar e conta de pé, em poucas
caixas. Diz o que lembra e o que não lembra. Volta ao comando na frase seguinte e
escolhe sua Ultra Beast. A revelação não para a missão, não vira flashback e não
ganha flag própria.

**Distribuição das três.** **Lusamine fica com Nihilego sempre que o jogador não
a escolher**; a Anabel fica com a que sobrar. Não é importar a fusão de Sun/Moon
(§3 proíbe): é responsabilidade e limite de pesquisa, que é o que aquela espécie
significa para ela. Se o jogador escolher Nihilego, ela tem **uma** linha
reconhecendo a perda do gesto, e aceita.

**Chefes.** Quarto degrau da escala: 4 barras (teto), nível 90, multiplicador 150
e moveset de dois eixos — preparo e controle — com item, respeitada a ressalva
condicional de §6. As três precisam ser distinguíveis na prática, não só no
texto: uma que sobe, uma que aguenta, uma que atrapalha. Captura bloqueada.

**Derrota e retry.** New Bark não tem Centro Pokémon, e isso acabou sendo uma
vantagem: o ponto de recuperação da cidade é a **porta de casa do jogador**, e a
engine cura a equipe sozinha. Perder devolve o jogador curado, a poucos passos da
cena, na porta da mãe dele. O design manda **usar** isso: na derrota a mãe tem
uma fala curta, e só uma. Ela não comenta a batalha e não consola em excesso —
está na porta, é onde estava antes, e é onde vai continuar. Sem flag nova; a
escolha é refeita a cada tentativa, como nas três missões anteriores.

**Resolução.** As três voltam e a cidade fica de pé, com um custo visível e
pequeno: os instrumentos do Elm não sobreviveram, e ele está bem com isso porque
agora tem o dado. Quem comenta a escolha do jogador é a Lusamine — o Kukui não
está nesta cena. Gold/Crystal diz o que o protagonista mudo não pode dizer, e é a
única fala puramente emocional da missão. A mãe fecha com uma caixa, sem abraço
encenado.

**Gancho — todo mundo em Olivine.** Precisa fazer três coisas e nada além:
(1) Anabel diz o que as três rupturas tiveram de diferente — não se dispersaram,
fecharam **na direção de um lugar só**, e é isso que torna o altar localizável: a
investigação acabou e o que vem é expedição; (2) **Lusamine pede a reunião e pede
que chamem os filhos** — Lillie, Gladion e Kukui, nomeados por ela, não como
Aether mas como alguém que deve uma explicação, e duas dessas pessoas são dela;
Looker acrescenta Anabel e ele mesmo, fechando **seis pessoas e o jogador** no
escritório de Olivine; (3) Looker manda o jogador **trazer o parceiro** — como
convite ao Pokémon, nunca como requisito, porque o jogador pode ainda não ter
Solgaleo ou Lunala e a checagem do §7 tem de ser lida como cena, não como parede.

**Estado.** M4 = 8/9/10, com uma flag persistente própria só para esvaziar a
cidade e a invariante de sempre (flag setada ⇔ var no valor "ativo"). O valor 10
não abre missão nenhuma: é *quatro missões concluídas, reunião pendente*, e é de
onde o §7 continua.

**O que esta missão não faz.** Não exige Solgaleo nem Lunala e não checa a
família de Cosmog em momento algum — a única verificação de time do arco continua
sendo a do §7. Não gasta a batalha da Lusamine contra o jogador, que acontece
depois, na disputa sobre quem atravessa (§3, §9). Não resolve a reconciliação
familiar: Lillie e Gladion não estão aqui. Não importa a fusão com Nihilego. Não
machuca ninguém do elenco e não mata nenhuma Ultra Beast. Não culpa o jogador. E
não transforma Gold/Crystal em parceiro de batalha: a cena já tem três atores em
combate, e um quarto diluiria a escolha, que é o coração da estrutura.


**O que a implementação da Missão 4 fixou (20/09/2026).** O esqueleto saiu
inteiro, sem cortes, nos nove arquivos previstos e sem alterar nenhuma decisão
de estado (feedback completo em §12 daquele doc, que **vence** o resto do
arquivo onde os dois divergem). O que vale como contrato daqui para frente:

- **`FLAG_EVENT_ULTRABEAST_NEWBARK` = `0x1044`,** com `CUSTOM_FLAGS_END` movida
  para ela. Numeração confirmada: M4 = 8/9/10, e **10 é o fim da cadeia** —
  é de onde o §7 começa, e ninguém mais pode usar a regra de sobreposição.
- **O teto de object events entrou no planejamento, e a primeira conta estava
  errada.** `OBJECT_EVENTS_COUNT` é 16 e inclui o jogador e o follower;
  **light sprite não ocupa slot** (`TrySpawnObjectEvents` desvia para
  `SpawnLightSprite`, que nunca toca `gObjectEvents[]`). A conta real da cena é
  12/16 com as quatro lâmpadas intactas. A M4 chegou a planejar esconder as
  lâmpadas por causa da conta errada e **desfez**. Regra que fica: medir o
  orçamento antes de encher uma cena, e lembrar que **objeto que não cabe não
  spawna, sem erro nenhum**, na ordem dos templates — quem desaparece primeiro
  é quem foi acrescentado por último.
- **Quatro armadilhas de sintaxe/encenação que o build não pega, agora
  documentadas:** (1) `DIR_UP`/`DIR_RIGHT` **não existem** neste repo — só
  `DIR_SOUTH`/`DIR_NORTH`/`DIR_WEST`/`DIR_EAST`; (2) o travessão `—` (U+2014)
  **quebra o build** (`unknown character`), enquanto `“ ”` e `…` estão no
  charmap; (3) bloco que começa com `applymovement` precisa de `closemessage`
  antes, ou o movimento roda **atrás** da caixa de texto aberta; (4) trazer NPC
  escondido para a cena é `removeobject` + `setobjectxyperm` + `addobject` —
  `setobjectxy` sozinho **não aparece**, e falha em silêncio.
- **Ator fora da câmera não pode falar.** O plano dava uma caixa ao Elm nove
  tiles antes de ele entrar na cena; a leitura passou para a Anabel, que estava
  à vista. Vale para qualquer cena grande: conferir **onde** cada objeto está
  no momento de cada caixa.
- **Decisão de personagem que não chega à tela não existe.** A distribuição das
  três UBs (Lusamine fica com Nihilego sempre que o jogador não a escolher) só
  era legível em um dos três ramos; as três falas passaram a dizer a divisão
  inteira em voz alta. O mesmo aconteceu com o “não” ao Gold/Crystal, prometido
  na prosa do doc e ausente do script. Reler o próprio doc antes de fechar o
  esqueleto virou passo obrigatório.
- **`goto_if_ge VAR_RIFT_MISSIONS_STATE` em Olivine falhou pela terceira vez
  seguida.** A M4 teve de mover um `goto_if_ge …, 8` deixado pela M3, que
  tornava os estados 9 e 10 inalcançáveis. A regra é a mesma desde a M2, e o
  aviso já está no código: **todo estado novo entra como `goto_if_eq`, e só o
  último da lista pode ser `goto_if_ge`.**
- **A melhor recuperação do arco veio do mapa, não do design.**
  `HEAL_LOCATION_NEW_BARK_TOWN` é (20,12), que é o tile de fala do Looker: o
  blackout devolve o jogador curado exatamente onde a cena começa, e o retry
  custa zero passo (a M3 custava 20).
- **Custo registrado e não resolvido:** a cena inteira se repete a cada
  tentativa, inclusive o nó da Lusamine e a revelação da Anabel, que é a fala
  mais longa do arco. Fica como pendência de evolução da M4 — e como lição já
  aplicada no evento PRÉ-NECROZMA, cujo doc separa a cutscene longa (roda uma
  vez) da pergunta repetível (ramo curto).
- **O que o build não prova** está em §10 daquele doc: o spawn dos dez objetos
  (à noite também), a mãe e o Elm voltando aos dois interiores, o repovoamento
  dos sete moradores, e se x150 com 4 barras é ameaça ou parede.


## 7. Reunião e expedição

Após concluir as quatro missões, o jogador retorna ao escritório de Olivine — **convocado pelo gancho da Missão 4** (§6.4), que é quem monta esta cena: Lusamine pede a reunião e nomeia Lillie, Gladion e Kukui; Looker acrescenta Anabel e ele mesmo. O jogador chega para uma sala cheia, e não para mais um relatório. Looker verifica se há **Solgaleo OU Lunala no time**. Basta um deles; não é necessário ter ambos, e um registro na Pokédex não substitui sua presença.

Essa condição bloqueia somente a expedição final. Não bloqueia o início nem a realização das quatro missões de Ultra Beasts.

**Estado e escopo do evento (V18) — PRÉ-NECROZMA.** Esta cena passa a ser um
evento próprio, com nome e documento: **PRÉ-NECROZMA**, plano técnico em
[`PRE_NECROZMA_ULTRABEAST_IMPLEMENTATION.md`](PRE_NECROZMA_ULTRABEAST_IMPLEMENTATION.md)
(**esqueleto implementado em 20/09/2026**, build limpo, runtime pendente; o §12
daquele doc registra o feedback da implementação). Três decisões do autor
fecham o escopo:

1. **Acontece inteiro dentro de `OlivineCity_House1`.** Nenhum mapa novo,
   nenhuma viagem, nenhuma cena de rua. Todo o elenco principal está na sala:
   Looker, Anabel, Lusamine, Lillie, Gladion e Kukui, mais Ninetales e Silvally
   fora da Poké Ball por §3.2 — **oito objetos e o jogador**.
2. **Termina antes da ida ao altar.** A viagem, o altar, o duelo da Lusamine
   (§9) e Ultra Necrozma ficam para o documento seguinte. O item 7 da ordem
   abaixo (liberar o navio) continua valendo como design, mas **não é escopo
   deste evento**.
3. **Entrega o gancho do altar** em vez de encená-lo, e termina ligando **uma
   flag persistente** (`FLAG_EVENT_NECROZMA_ALTAR_UNLOCKED`, nunca limpa). É ela
   que o doc do altar vai ler para acender o navio e o que mais precisar de campo
   `flag` em `map.json`; a var continua sendo a autoridade da história.

**Estado na var:** 10 = quatro missões concluídas, reunião pendente (o elenco
está na sala); 11 = reunião **feita**, faltando Solgaleo ou Lunala — o elenco
continua na sala e a pergunta é repetível, sem repetir a cutscene; 12 = reunião
completa, expedição liberada, flag ligada. A checagem de time do §7 é a
**única** do arco e olha só a **equipe** (um dos dois guardado no PC não conta,
e registro na Pokédex não conta).

**O que a implementação fixou como contrato (20/09/2026).** Estes pontos
deixaram de ser plano e passaram a ser código; uma evolução da cena não pode
regredir nenhum deles sem atualizar este §7 e o §7 do doc de implementação:

- **A cutscene longa roda uma vez.** O valor 11 existe exatamente para isso: ele
  não é necessidade técnica, é o item 4 da ordem abaixo, e é o que impede a cena
  mais longa do arco de tocar de novo enquanto o jogador termina de evoluir o
  Cosmog. É a pendência que a M4 registrou (§9 daquele doc: “a cena inteira se
  repete a cada tentativa… num retry isso cansa”) resolvida antes de custar.
- **A checagem é `checkspecies` duas vezes, nunca uma, e nunca pela família.**
  Ela percorre só `gPlayerParty`, então o item 3 da ordem abaixo (Cosmog,
  Cosmoem, ovo ou ausência não satisfazem) sai de graça — com a ressalva de que
  “um ovo não satisfaz” é atendido por acidente da espécie, não por guarda no
  script: não existe ovo de Solgaleo nem de Lunala por criação.
- **`FLAG_EVENT_NECROZMA_ALTAR_UNLOCKED` nunca é limpa**, e muda no mesmo script
  que o `setvar 12`. É o oposto das quatro flags de missão, que são “incidente
  ativo” e são limpas na resolução. Até o doc do altar existir, ela é **escrita
  e nunca lida**: um erro nela não tem sintoma, e a conferência em runtime é
  pelo estado 12 e pelas falas de porto.
- **Os seis visitantes compartilham uma única `FLAG_TEMP_1`**, recalculada sem
  condição no `ON_TRANSITION` (que este mapa não tinha e passou a ter). Quem
  introduzir `removeobject` em qualquer um deles tem de separar a flag daquele
  objeto antes, ou o elenco inteiro some junto. Quem tirar os seis da sala é o
  `warpsilent` do fim, não um `removeobject`.
- **Não há batalha, e portanto não há retry de graça.** O papel que o blackout
  cumpria nas quatro missões é do estado 11: a checagem pode falhar
  indefinidamente sem que nada se perca e sem repetir missão nenhuma.

### Ordem da cena para implementação

1. Looker encerra o relatório da missão final (Kartana + Guzzlord + Nihilego) e explica que o grupo localizou o altar ligado às rupturas.
2. Anabel explica que alcançar Necrozma exige um Pokémon capaz de abrir a passagem.
3. Looker verifica o time. Cosmog, Cosmoem, um ovo ou a ausência da família não satisfazem o requisito.
4. Se faltar Solgaleo ou Lunala, Looker orienta o jogador a continuar desenvolvendo seu parceiro. A expedição permanece pendente, sem repetir missões concluídas.
5. Quando o jogador voltar com um dos dois, a cena prossegue. Não exigir evolução no próprio mapa, procedência individual ou presença dos dois lendários.
6. A reunião inclui Looker, Anabel, Lusamine, Lillie, Gladion e Kukui — **seis NPCs e o jogador**. O grupo reconhece que o Pokémon recebido no começo da jornada agora pode ajudá-los a alcançar Necrozma. **A condição de Faller da Anabel já foi revelada em New Bark (V17, §6.4 e §3.1):** aqui ela não é notícia, é **argumento** — é por isso que ela exige que ninguém atravesse sem plano de volta, e é ela quem impõe essa condição ao plano da Lusamine. Se o jogador precisar de recapitulação, cabe em uma caixa. Lillie e Gladion reagem à mãe ter pedido a reunião; a conversa de família começa aqui e não se resolve aqui.
7. A reunião libera o navio em Olivine. A primeira chegada ao altar acontece por essa viagem.

**Nota de escala:** com a Ninetales da Lillie e o Silvally do Gladion, que por §3.2 têm de estar fora da Poké Ball, são oito objetos e o jogador numa sala pequena. A sala comporta — conferido na V17 —, mas é a cena mais cheia do arco, e a coreografia dela é assunto do doc daquela cena, não deste documento.

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

Com as quatro missões concluídas e Solgaleo ou Lunala apresentado a Looker, a investigação chega ao ponto de enfrentar a origem da instabilidade. A travessia até Necrozma envolve risco de a passagem se desestabilizar e impedir o retorno.

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
| Escritório em local indefinido ou Goldenrod | Substituída por Olivine; no V14, `OlivineCity_House1`. |
| Nove missões de uma Ultra Beast cada | Substituída no V14 por quatro missões de chefes simultâneos (§6; histórico em §6.1). |
| Blackthorn como prólogo fora da contagem, com escritório aberto só depois | Substituída no V14: ligação do Looker → escritório → Blackthorn como Missão 1 → retorno ao escritório. |
| Lillie em Pheromosa/Celesteela/Guzzlord; Gladion em Buzzwole/Xurkitree/Guzzlord | Substituída no V14: Gladion na Missão 1, Lillie na Missão 2, Lusamine na Missão 4. |
| Revelação de Anabel | Ela já sabe ser Faller. **Substituído na V17 quanto ao lugar:** conta ao jogador **em campo, na Missão 4 (New Bark)**, com três rupturas abertas, e não na reunião. Na reunião a condição vira argumento para o plano de retorno. Sem flag exclusiva, em qualquer dos dois casos. |
| Gladion ligado ao choro de Whitney | Substituído pela batalha e entrega do ovo em Violet. |
| Assistente de Elm entrega o ovo | Substituído por Gladion; revisar ligação de Violet e indicação da Route 32. |
| Lillie em Goldenrod | Evento implementado conforme o autor; vitória ou derrota permitem SquirtBottle, seguido de saída pela porta. FLAG_RECEIVED_SQUIRTBOTTLE controla a ausência. |
| Vitória obrigatória contra Lillie em Goldenrod | Substituída por continuidade em vitória e derrota. O V12 preserva a mesma filosofia aos demais duelos narrativos. |
| Gladion sem encontro intermediário antes de Blackthorn | Substituído por Cianwood e pelo novo encontro obrigatório antes da Victory Road. |
| Fly condicionado a vencer Gladion | Não aprovado: vitória ou derrota permitem receber a HM. A opção de recusa foi removida no V13. |
| Aviso explícito de bolsa/HM na checagem inicial de Gladion | Substituído por fala de treino ocupado, sem iniciar a cena. |
| Vitória obrigatória em Route 30/Violet/Dragon’s Den | Substituída: esses duelos concluem em vitória ou derrota, sem blackout. |
| Gladion opcional na entrada da Liga | Removido: a luta foi movida para antes da Victory Road, é obrigatória e não exige vitória. |
| Retry de Lillie após derrota no Dragon’s Den | Removido: a demonstração termina após a batalha independentemente do vencedor. |
| Altares do Sol, Lua e Eclipse em locais separados | Substituída por um único local com estados diferentes. |
| Sol à noite e Lua de dia | Corrigida: visual do Sol de dia e da Lua à noite, sem capturas nesses horários. |
| Blacephalon com Lillie e Stakataka com Gladion | Substituída: ambas as missões têm Kukui em destaque. |
| Kartana duplicada na lista | Corrigida no V13 (Kitakami); no V14 Kartana está na missão final, em New Bark. |
| Hoopa como centro da história | Não faz parte deste design. |
| Lillie entregar Cosmog cedo | Substituída pelo Mystery Egg de Cosmog em Violet. |
| Capturar Solgaleo e Lunala no altar | Removida: Looker exige apenas um dos dois no time após as quatro missões. |
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
| Escritório | Definido: `OlivineCity_House1`, Looker (4,5) e Anabel (7,5), presentes desde o New Game. Estar em Olivine e na missão ao mesmo tempo é aceito (a missão é cutscene). Pendente: presença após a história e venda de Beast Balls. |
| Campanha | Route 30, Goldenrod e Dragon’s Den da Lillie estão implementados e compilados; runtime/regressão ainda pendentes. Violet/Cianwood/Gladion seguem conforme seus próprios estados. Victory Road Gladion permanece pendente. |
| Lillie em Goldenrod | Implementada e compilada com Vulpix fora da Poké Ball. Preservar batalha/entrega existentes e validar em runtime a nova coreografia, especialmente possível sobreposição visual na saída. |
| Gladion em Cianwood | Preservar a implementação existente, mas remover a recusa e garantir batalha obrigatória com vitória/derrota sem blackout. |
| Lillie no Dragon’s Den | Implementação compilada concluída. Validar em runtime quiz, 15 reações, flags temporárias, Ninetales OW, battle outcomes, IA/Aurora Veil, Snow/recovery, Clair, Risingbadge e Dratini. |
| Gladion / Victory Road | Escolher gatilho/mapa seguro antes do acesso, criar estado de conclusão independente do vencedor e fechar equipe de cinco com Silvally lead. |
| Blackthorn | Esqueleto implementado e compilado em 19/09/2026; runtime pendente (checklist no doc §11). Evolução pendente: moveset curado dos bosses, mostrar a luta do Gladion na tela. |
| Mahogany | Esqueleto implementado e compilado em 19/09/2026; runtime pendente (checklist no doc §10, ordem sugerida em §12.5). Evolução pendente: apagão visual da cidade, mostrar a luta da Lillie na tela, saída do elenco a pé, reações dos moradores. |
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
- [ ] Dragon’s Den preserva as cinco perguntas, avaliação e recompensas vanilla; Lillie reage às 15 alternativas sem responder pelo jogador.
- [ ] Das 15 alternativas, 9 aceitas avançam e 6 rejeitadas preservam `ElderWrong`, incremento de `VAR_DRAGONS_DEN_QUIZ` e re-pergunta; as seis falas rejeitadas aparecem uma vez por visita via `FLAG_TEMP_2..7`.
- [ ] As falas de Lillie não modificam diretamente pontuação, contador, Dratini ou qualquer outro estado/recompensa vanilla; a punição decorre exclusivamente da escolha rejeitada original.
- [ ] No Dragon’s Den, Alolan Ninetales já está evoluída antes da chegada do jogador e permanece fora da Poké Ball ao lado de Lillie durante reencontro, quiz e transição para a batalha.
- [ ] Após o Dragon’s Den, Ninetales continua fora da Poké Ball em todas as aparições posteriores de Lillie, inclusive nas Rift Missions e cenas finais em que ela estiver presente.
- [ ] A batalha de Dragon’s Den usa um time completo de 6 Pokémon: Ninetales-A 62, Ribombee 59, Clefable 60, Lilligant 59, Milotic 61 e Comfey 60; Ninetales é lead e ace narrativo.
- [ ] Derrota contra Lillie no Dragon’s Den conclui a demonstração sem blackout ou retry obrigatório; o script continua para a conclusão e Clair. Reset manual antes de `state 3` pode repetir quiz+batalha e deve ser validado como comportamento seguro.
- [ ] Vitória ou derrota contra Lillie devolvem o fluxo ao estado correto de Clair e Lillie deixa o Shrine normalmente.
- [ ] A ordem final pré-Liga inclui Gladion antes da Victory Road: Clair → Dragon’s Den/Lillie → Victory Road Gladion → Victory Road → Liga, sem ruptura obrigatória de Ultra Beast.
- [ ] Gladion antes da Victory Road usa Silvally como lead planejado, batalha obrigatória sem blackout e saída definitiva da cena em vitória ou derrota.
- [ ] Victory Road permanece acessível independentemente do resultado e o encontro antigo na entrada da Liga não existe mais.
- [ ] Diálogos seguem o guia de voz; diferenças entre SM, USUM e adaptações próprias permanecem explícitas.
- [ ] Depois do primeiro HoF, sair de casa dispara a ligação do Looker uma única vez; ela chama o jogador a `OlivineCity_House1`.
- [ ] O NPC do Voltorb está em `OlivineCity_House3` (7,4) e a troca continua funcionando.
- [ ] O briefing em Olivine envia o jogador a Blackthorn e ativa `FLAG_EVENT_ULTRABEAST_BLACKTHORN`.
- [ ] Durante o evento, Blackthorn só mostra Looker, Anabel, Gladion e Silvally; Joy continua curando.
- [ ] O Looker não existe mais na Route 29; Looker e Anabel estão em `OlivineCity_House1` desde o New Game.
- [ ] Em Blackthorn, Buzzwole e Pheromosa surgem juntos; o jogador escolhe qual enfrenta numa boss battle sem captura, Gladion fica com a outra, e a fala dele depois muda conforme a escolha; Looker e Anabel presentes; **Silvally já está fora da Poké Ball ao lado de Gladion quando a crise começa**. Derrota usa blackout e o evento recomeça do início; não avança o incidente.
- [ ] Ao resolver Blackthorn, o gancho manda o jogador de volta ao escritório de Olivine para a Missão 2.
- [ ] Quatro missões seguem a ordem e os acompanhantes da tabela §6, com Looker em todas.
- [ ] Há retorno ao escritório após cada missão e venda de Beast Balls desde o começo.
- [ ] Em New Bark, as três Ultra Beasts surgem juntas; o jogador escolhe uma, **Lusamine fica com Nihilego sempre que o jogador não a escolher** e Anabel fica com a restante; Looker não batalha; Elm, a mãe e Gold/Crystal participam sem batalhar.
- [ ] A Missão 4 não verifica a família de Cosmog em momento nenhum e não gasta a batalha da Lusamine contra o jogador.
- [ ] Derrota em New Bark devolve o jogador curado em (20,12), na porta de casa, com o estado 9 intacto e a escolha refeita; a mãe tem **uma** fala de retry, sem flag nova.
- [ ] O gancho da Missão 4 convoca Lusamine, Lillie, Gladion, Kukui, Looker e Anabel para o escritório de Olivine, e pede o parceiro do jogador sem informar condição de evolução.
- [ ] Após a missão final e apresentação de Solgaleo OU Lunala no time, a reunião libera o navio.
- [ ] Cosmog/Cosmoem não liberam a expedição; a ausência da evolução não impede as quatro missões.
- [ ] Primeira visita desbloqueia o destino do altar no mapa de Fly, sem entregar outra HM; navio permanece disponível nos dois sentidos.
- [ ] Existe apenas um altar físico, com visual diurno/noturno e sem capturas de Solgaleo/Lunala.
- [ ] Um dos dois lendários permite abrir o portal em qualquer horário.
- [ ] Não há presente de Cosmoem nem evolução automática no altar.
- [ ] Lusamine é enfrentada apenas uma vez na história, perto da travessia final. Vitória ou derrota continuam sem blackout e levam à aceitação do plano coletivo.
- [ ] Necrozma pode ser obtido e falhas não bloqueiam permanentemente sua captura.
- [ ] Despedida deixa Looker e Anabel no altar.
- [ ] Anabel revela sua condição de Faller **em New Bark, no meio da Missão 4** (V17), sem uma flag exclusiva; na reunião anterior ao navio a condição é usada como argumento, não anunciada.
- [ ] Sua decisão de permanecer no altar inclui a motivação pessoal de ajudar outros deslocados.
- [ ] Expedições têm cinco treinadores e um boss lendário capturável.
- [ ] Quinto treinador tem associação temática com o lendário e as batalhas possuem frases contextuais.
- [ ] Lendários já capturados continuam disponíveis para repetição e busca de IVs.
- [ ] Acesso ao loop funciona em qualquer horário.
- [ ] Pool preserva uma luta de cada personagem de Hoenn aprovado, incluindo Steven, sem variantes de dificuldade adicionais.
- [ ] Repetição do loop não depende de apagar flags de vitória da campanha.
- [ ] Espaço para o ovo em Violet considera party e PC antes da batalha.
- [ ] Todos os duelos narrativos V13 salvam o resultado e continuam sem blackout; progressão não depende de vitória nem de menu de recusa.
- [ ] Memória, assets e persistência são validados na ROM local, sem presumir suporte pelo design.

## 16. Entrega por etapas

1. **Lillie / campanha:** Route 30, Goldenrod e Dragon’s Den estão implementados e compilados. Próxima etapa é runtime/regressão: outcomes sem blackout, Vulpix/Ninetales OW, follower, quiz/Dratini, IA e coreografia.
2. **Dragon’s Den:** validar em runtime a implementação vigente da seção 4.8; não reescrever os 15 branches nem a party antes dos testes, salvo correção de bug comprovado.
3. Implementar Gladion antes da Victory Road conforme a seção 4.9; fechar equipe de cinco e gatilho seguro sem criar gate de acesso.
4. Preservar Victory Road e Liga sem incidente obrigatório de Ultra Beast e sem segundo encontro de Gladion na entrada da Liga.
5. Implementar em esqueleto a ligação do Looker, o escritório de Olivine e Blackthorn (Missão 1) pelo doc `.claude/BLACKTHORN_ULTRABEAST_IMPLEMENTATION.md`; derrota usa blackout/retry e não avança a resolução.
6. **Missões 2 (Mahogany) e 3 (Cherrygrove) estão em esqueleto implementado** (19 e 20/09/2026) por `.claude/MAHOGANY_ULTRABEAST_IMPLEMENTATION.md` e `.claude/CHERRYGROVE_ULTRABEAST_IMPLEMENTATION.md`; falta validar as duas em runtime pelas checklists §10 daqueles docs (ordem sugerida em §12.5 e §12.6), com atenção especial ao balanceamento inédito de x130/x140 e à **regressão do presente do Friendly Trader** de Cherrygrove (§3.1.1 do doc da M3). Em seguida implementar a Missão 4 — **planejada na V17: conteúdo em §6.4 e plano técnico em `NEWBARK_ULTRABEAST_IMPLEMENTATION.md`** —, depois a reunião de Olivine, a expedição, o duelo de Lusamine sem blackout e o boss de Ultra Necrozma com retry, conforme os contratos aprovados. **A Missão 4 e a reunião de Olivine (evento PRÉ-NECROZMA) foram implementadas em esqueleto em 20/09/2026** por `.claude/NEWBARK_ULTRABEAST_IMPLEMENTATION.md` e `.claude/PRE_NECROZMA_ULTRABEAST_IMPLEMENTATION.md`; restam a expedição, o duelo e o boss, cujo documento começa lendo `FLAG_EVENT_NECROZMA_ALTAR_UNLOCKED` e `VAR_RIFT_MISSIONS_STATE >= 12`.
7. Integrar o inventário de treinadores preservados ao loop repetível e validar acesso e repetição.

Uma divisão prática de produção continua sendo: encontros de campanha; ligação/escritório/Blackthorn e progressão das quatro missões; expedição/navio/Fly/altar; clímax e despedida; loop repetível. Cada etapa deve entregar gatilhos, textos, batalhas e recuperação de falhas de forma verificável antes da próxima.

Esta divisão é uma recomendação de produção. Não autoriza alterar o elenco, a ordem das missões, a condição de evolução exigida por Looker ou a estrutura do loop.

## 17. Registro da revisão V13

- Consolidado o estado real da implementação da Lillie em 17/09/2026.
- Route 30 foi refatorada para no-whiteout com tratamento explícito de WON/LOST/DREW/FORFEITED/UNKNOWN e continua para Mystery Egg/Pokédex.
- Alolan Vulpix foi adicionado ao overworld de Route 30 e Goldenrod, saindo em conjunto com Lillie.
- Dragon’s Den foi implementado e compilado.
- O quiz real é `loop-until-correct`: 9 alternativas aceitas avançam e 6 rejeitadas preservam punição e re-pergunta.
- As 15 reações da Lillie foram mantidas. As seis rejeitadas usam `FLAG_TEMP_2..7` para aparecer uma vez por visita.
- `FLAG_TEMP_1` controla temporariamente a visibilidade de Lillie/Ninetales no Shrine conforme `VAR_BLACKTHORN_CITY_STATE`.
- Lillie e Ninetales são objetos 5 e 6; Clair permanece objeto 4.
- A fala do Elder foi corrigida para funcionar tanto quando jogador e Lillie concordam quanto quando discordam.
- `TRAINER_LILLIE_DRAGONS_DEN = 970` foi criado a partir do antigo `TRAINER_UNUSED_106`.
- A batalha final pré-Liga da Lillie usa seis Pokémon e foi calibrada acima de Clair: Ninetales-A 62, Ribombee 59, Clefable 60, Lilligant 59, Milotic 61, Comfey 60.
- Ninetales é lead e ace narrativo para ativar Snow e permitir uso coerente de Aurora Veil.
- Não existe dataset Hard separado; o antigo Hard foi promovido ao dataset único atual.
- Nenhuma flag ou var persistente nova foi necessária.
- Todo esse conjunto foi **inspecionado e compilado**, mas ainda **não testado em runtime**.
- Moonlight/Synthesis permanecem até o runtime confirmar se Snow prejudica demais o sustain.
- Pequenas correções de coreografia em Goldenrod/Route 30 estão autorizadas se sobreposições aparecerem no emulador.
- Preservados Gladion antes da Victory Road, Blackthorn pós-game, escritório de Olivine, nove Rift Missions, altar, clímax e loop repetível.

### Nota de autoridade da V13

O V13 substitui o V12 para decisões de design e estado da implementação documentada. Para cenas já implementadas, preservar dados técnicos que não foram alterados — equipes, mapas, assets e entregas — mas refatorar branches incompatíveis com a nova política de resultado. Uma implementação antiga não prevalece sobre a decisão V13 de permitir continuidade após derrota.

O contrato editorial principal é: **duelo de personagem testa/revela relação; boss de ameaça precisa ser resolvido**. Assim, perder para Lillie, Gladion ou Lusamine pode fazer parte da história sem punição estrutural, enquanto perder para Ultra Beasts, Ultra Necrozma ou outro boss de ameaça mantém o conflito pendente e exige recuperação/retry.

## 18. Registro da revisão V14

- Pós-E4 simplificado: nove missões de uma Ultra Beast → **quatro missões de chefes simultâneos** (§6). Histórico V13 em §6.1.
  - 1 · Buzzwole + Pheromosa — Blackthorn — Gladion
  - 2 · Xurkitree + Celesteela — Mahogany — Lillie
  - 3 · Blacephalon + Stakataka — Cherrygrove — Kukui
  - 4 · Kartana + Guzzlord + Nihilego — New Bark — Lusamine
- Entrada no arco definida: após o primeiro HoF, ao sair de casa, **Looker liga** e chama o jogador a Olivine.
- Escritório definido: `OlivineCity_House1`, com Looker e Anabel. O NPC da troca do Voltorb muda para `OlivineCity_House3` (7,4).
- Blackthorn deixa de ser prólogo e vira a Missão 1: enviado por Looker a partir de Olivine; `FLAG_EVENT_ULTRABEAST_BLACKTHORN` evacua a cidade (só Looker, Anabel, Gladion e Silvally; Joy continua no Centro); evento 100% scriptado a partir da primeira conversa; derrota recomeça o evento; termina com gancho de volta a Olivine.
- Verificado no engine: sem suporte a parceiro em batalha selvagem fora do NPC follower (desligado); o sistema de boss só existe em batalha simples.
- **Revisão 2 (mesmo dia):** Looker sai da Route 29; Looker e Anabel moram em `OlivineCity_House1` desde o New Game, sem flag — a var só troca o diálogo. Ligações do Elm e do Looker em sequência, aprovadas. Batalha vira **escolha + boss**: o jogador escolhe qual UB enfrenta (boss battle simples) e o acompanhante fica com a outra — estrutura padrão para todas as missões. Na Missão 4, Lusamine e Anabel ficam com as duas UBs não escolhidas. Looker e Anabel em Olivine e na missão ao mesmo tempo: aceito, a missão é cutscene.
- Novo modo de produção: **esqueleto** (skill `evento-esqueleto`), com um documento de implementação por evento em `.claude/`.
- Campanha pré-Liga, política de duelos, altar, clímax e loop: inalterados em relação ao V13.

## 19. Registro da revisão V15

Escopo: pós-E4 apenas. Campanha pré-Liga, política de duelos, altar, clímax e loop repetível ficam **inalterados** em relação ao V14/V13.

### O que a implementação da Missão 1 fixou (e agora vale como contrato)

Implementada em esqueleto em 19/09/2026 (`make -j$(nproc)` limpo, ROM 92,47%, EWRAM 94,28%; runtime inteiramente pendente). O que saiu do plano e virou regra geral:

- `VAR_RIFT_MISSIONS_STATE` = `0x4120`; `FLAG_EVENT_ULTRABEAST_BLACKTHORN` = `0x1040`; `FLAG_NO_CATCHING` = `0x1041` ligada a `B_FLAG_NO_CATCHING` e **compartilhada por todas as Rift Missions** (a engine a limpa ao fim de toda batalha).
- Looker saiu da Route 29. Looker e Anabel vivem em `OlivineCity_House1` com `flag: 0` — nunca `removeobject` neles.
- O NPC da troca do Voltorb foi para `OlivineCity_House3` (7,4), com `FLAG_OLIVINE_NPC_TRADE_COMPLETED` preservada.
- Blackthorn: 16 objetos passaram a carregar a flag do evento; item ball e light sprites ficaram de fora. **Consequência permanente:** `removeobject` em qualquer um dos 16 agora esvazia a cidade.
- Escolha + boss confirmada tecnicamente: `ignoreBPress = TRUE` elimina o cancelamento do menu, e `VAR_TEMP_3` sobrevive à batalha porque voltar de batalha não passa por `LoadMapFromWarp`.
- Erro do plano corrigido na implementação e agora obrigatório em todo doc: **todo bloco terminado em `warpsilent` leva `waitstate` / `releaseall` / `end`**.
- Pendências herdadas: Beast Balls com a Anabel (§5) continuam não implementadas; Looker e Anabel visíveis em Olivine e no local da missão ao mesmo tempo continua aceito.

### O que a Missão 2 acrescenta ao design

- **Mahogany fechado em conteúdo** (§6.2): apagão da cidade, Lillie como autoridade técnica da cena, Anabel confirmando pelos instrumentos e plantando uma única semente de Faller, gancho para Cherrygrove/Kukui via escritório de Olivine.
- **Escala de dificuldade crescente entre missões** (§6, regras comuns): M1 = 2 barras / Lv70 / x110 / golpes de nível; M2 = 4 barras / Lv80 / x130 / moveset curado + item. A M1 fica como missão-tutorial de ameaça, de propósito. Missões 3 e 4 não devem ficar abaixo da M2. O multiplicador 130 é o primeiro acima de 110 no projeto inteiro.
- **Contrato de numeração da var:** cada missão ocupa três valores (briefing pendente → ativo → resolvido), com o "resolvido" de uma servindo de "briefing pendente" da seguinte. M1 = 2/3/4, M2 = 4/5/6, M3 começa em 6.
- **Uma flag persistente por missão**, só para esvaziar a cidade, com invariante flag ⇔ valor "ativo". `FLAG_EVENT_ULTRABEAST_MAHOGANY` = `0x1042`, com `CUSTOM_FLAGS_END` movida.
- **O escritório de Olivine é reutilizável:** a cena de chegada e o `BriefingTalk` viram um despachante por estado, atendendo todas as missões com a mesma coreografia (§5).
- **Tabela de estado do evento** adicionada em §6, com a escala não planejado → planejado → esqueleto implementado → validado em runtime → evoluído.

### O que continua em aberto

- Runtime de tudo que é pós-E4: nada foi testado no emulador.
- Beast Balls com a Anabel.
- Missões 3 (Cherrygrove / Kukui) e 4 (New Bark / Lusamine) sem doc de implementação. *(Superado na V16 quanto à Missão 3 — ver §20.)*
- Se o autor quiser nivelar a Missão 1 por cima em vez de manter a escalada, isso exige editar `BlackthornCity/scripts.inc` **e** atualizar o doc da M1; o design não decide isso sozinho.

## 20. Registro da revisão V16

Escopo: pós-E4 apenas. Campanha pré-Liga, política de duelos, altar, clímax e loop repetível ficam **inalterados** em relação ao V15/V14/V13.

### Arquivo renomeado

`MAHOGANY_ULTRA_BEAST_IMPLEMENTATION.md` → [`MAHOGANY_ULTRABEAST_IMPLEMENTATION.md`](MAHOGANY_ULTRABEAST_IMPLEMENTATION.md), para ficar igual a `BLACKTHORN_ULTRABEAST_IMPLEMENTATION.md` e `CHERRYGROVE_ULTRABEAST_IMPLEMENTATION.md`. Todas as referências no design e no doc da Missão 1 foram atualizadas. O padrão de nome para as próximas missões é `<CIDADE>_ULTRABEAST_IMPLEMENTATION.md`.

### O que a implementação da Missão 2 acrescentou ao design

Registrado em §6.2, no bloco "O que a implementação da Missão 2 fixou". Em resumo: o esqueleto saiu inteiro, nos cinco arquivos previstos e sem mexer em nenhuma decisão de estado; o escritório de Olivine virou um padrão de acréscimo (um estado no gatilho, um ramo no `BriefingTalk`, dois ramos por NPC); `local_id` explícito passou a ser regra para objeto novo de missão; conferir os gatilhos herdados do mapa antes de esconder objetos virou passo obrigatório; e ficou registrado que `VAR_RIFT_MISSIONS_STATE` só sai de 0 no Hall of Fame, o que autoriza toda missão a assumir contexto estritamente pós-E4.

### O que a Missão 3 acrescenta ao design

- **Cherrygrove fechado em conteúdo** (§6.3): ruptura intermitente **sobre o mar**, Kukui como autoridade técnica da cena, a coordenação das duas UBs como justificativa narrativa da estrutura escolha + boss, a responsabilidade dele como contraponto à curiosidade, e gancho para New Bark/Lusamine via escritório de Olivine.
- **Primeira missão com três atores de elenco.** Kukui não tem parceiro fora da Poké Ball: a regra visual de §3.2 nomeia só Lillie e Gladion, e o design não cria exceção por conveniência de cena.
- **Terceiro degrau da escala** (§6, regras comuns): M3 = 4 barras / Lv85 / x140 / moveset curado com um golpe de controle por chefe + item. Como as barras estão no teto da engine desde a M2, fica registrado que **a escalada passa a vir de nível, multiplicador e qualidade do moveset**, não de mais barras. A Missão 4 não deve ficar abaixo da M3.
- **Numeração da var confirmada na prática:** M3 = 6/7/8, com `FLAG_EVENT_ULTRABEAST_CHERRYGROVE` = `0x1043` e `CUSTOM_FLAGS_END` movida. A Missão 4 começa em 8.
- **Primeira missão em que as Ultra Beasts ficam sobre a água** e em que o Centro de Pokémon não fica ao lado da cena: o custo do retry (20 tiles em linha reta) está registrado como risco assumido no doc da missão, não escondido.
- **Evacuação completa, inclusive de objetos com flag própria (decisão do autor).** Até a M2, um objeto que já tivesse flag ficava de fora da evacuação (o Fat man de Mahogany). Em Cherrygrove os dois Pokémon do Friendly Trader **também somem**: o campo `flag` do template deles passa a ser uma flag temporária recalculada no load, no mesmo padrão já usado por `FLAG_HIDE_CIANWOOD_GLADION`, e `FLAG_PICKED_ZIGZAGOON`/`FLAG_PICKED_RATTATA` continuam sendo a verdade persistente. **Isso obriga a missão a mexer num evento que existia antes dela** — é a primeira vez que isso acontece no arco. A regra que fica: *quando uma missão precisar evacuar um objeto de flag alheia, o caminho aprovado é trocar o campo `flag` por um cache temporário e recalcular, nunca `removeobject`.*

### O que continua em aberto

- Runtime de tudo que é pós-E4: nada foi testado no emulador. Três missões dependem disso.
- Beast Balls com a Anabel (§5), pendentes desde a M1.
- Missão 4 (New Bark / Lusamine) sem documento de implementação.
- O presente do Friendly Trader de Cherrygrove passa a depender de dois `setflag` explícitos (decisão registrada abaixo). Os dois `setflag` **já estão no código** desde a implementação da M3 (20/09/2026); enquanto não forem testados em runtime, esse continua sendo o ponto do projeto com maior risco de regressão silenciosa.
- Se o autor quiser nivelar a Missão 1 por cima em vez de manter a escalada, isso continua exigindo editar `BlackthornCity/scripts.inc` **e** atualizar o doc da M1; o design não decide isso sozinho.

## 21. Registro da revisão V17

Escopo: pós-E4 apenas. Campanha pré-Liga, política de duelos, altar, clímax e loop repetível ficam **inalterados** em relação ao V16/V15/V14/V13.

### O que a implementação da Missão 3 acrescentou ao design

Registrado em §6.3, no bloco "O que a implementação da Missão 3 fixou". Em resumo: o esqueleto saiu inteiro, nos cinco arquivos previstos e sem mexer em nenhuma decisão de estado; `FLAG_EVENT_ULTRABEAST_CHERRYGROVE` = `0x1043` com `CUSTOM_FLAGS_END` movida; a numeração 6/7/8 confirmada, deixando a M4 em 8/9/10; e duas regras técnicas que passam a valer para todo o projeto — o caminho aprovado para evacuar objeto de flag alheia (cache temporário + `setflag` explícito, nunca `removeobject`) e o fato de que **este repo não usa o formato de `map.bin` nem de `metatile_attributes.bin` do `pokeemerald`** (§12.7 daquele doc é leitura obrigatória antes de medir qualquer cena).

Além do plano, a implementação da M3 consertou um furo anterior a ela no Friendly Trader de Cherrygrove: checagem de espaço em party **e** PC antes de qualquer diálogo de oferta, mais guarda `MON_CANT_GIVE` antes do `setflag` de "já pegou". Esse padrão é o da skill `entregar-pokemon-ou-ovo` e vale para qualquer presente futuro do arco.

### O que a Missão 4 acrescenta ao design

- **New Bark fechado em conteúdo** (§6.4): três rupturas simultâneas em terra, a cidade que se recusa a evacuar, Elm com seis semanas de dados arquivados como defeito de sensor, Lusamine querendo assumir as três sozinha, a mãe do jogador sendo quem a faz parar, e o gancho que monta a reunião do §7.
- **A revelação da Anabel mudou de lugar** — de §7 (reunião) para §6.4 (campo, com três rupturas abertas). §3, §3.1, §7, §13 e §15 foram atualizados juntos. Motivo: as sementes plantadas em Mahogany e Cherrygrove pedem pagamento sob pressão, não numa sala. Continua **sem flag exclusiva**.
- **Elenco novo sem batalha nova.** Elm, a mãe do jogador e Gold/Crystal entram no arco com função concreta e nenhum deles luta. Gold/Crystal traz um custo de escrita registrado: o nome depende de `checkplayergender` (Crystal se o jogador é homem, Gold se é mulher), então toda fala que o nomeie custa dois blocos de texto.
- **Quarto degrau da escala, com ressalva** (§6, regras comuns): M4 = 4 barras / Lv90 / x150 / moveset de dois eixos + item, **condicionado ao runtime da M3** — se x140 já for parede, a M4 herda o número corrigido em vez de continuar subindo. É a primeira vez que o design se recusa a fixar um número de balanceamento antes de o degrau anterior ser jogado.
- **A cadeia de estados termina em 10.** A regra de sobreposição (resolvido de uma = briefing pendente da seguinte) vale de M1 a M4; 10 significa quatro missões concluídas e reunião pendente, e é de onde o §7 continua.
- **Distribuição das UBs virou decisão de personagem, não de doc:** Lusamine fica com Nihilego sempre que o jogador não a escolher.
- **A melhor recuperação do arco veio de graça.** New Bark não tem Centro Pokémon, mas o ponto de recuperação da cidade é a porta de casa do jogador e a engine cura a equipe sozinha: perder devolve o jogador na porta da mãe, e ela tem uma fala. Detalhe técnico no doc da missão.

### O que continua em aberto

- Runtime de tudo que é pós-E4: **nada foi testado no emulador**. Três missões dependem disso, e o balanceamento da M4 depende do resultado da M3.
- Beast Balls com a Anabel (§5), pendentes desde a M1.
- **Missão 4: planejada, não implementada.** Conteúdo em §6.4, plano técnico em [`NEWBARK_ULTRABEAST_IMPLEMENTATION.md`](NEWBARK_ULTRABEAST_IMPLEMENTATION.md) (20/09/2026). O doc levanta um risco que as três missões anteriores não tinham: **o orçamento de 16 object events simultâneos** — sete atores de elenco mais três Ultra Beasts deixam a cena a quatro slots do teto, e objeto que não cabe não spawna sem erro nenhum.
- A reunião do §7, a expedição, o duelo da Lusamine e Ultra Necrozma continuam sem doc.
- O presente do Friendly Trader de Cherrygrove continua sendo o ponto de maior risco de regressão silenciosa do projeto até ser testado.

## 22. Registro da revisão V18

Escopo: pós-E4 apenas. Campanha pré-Liga, política de duelos, altar, clímax e
loop repetível ficam **inalterados** em relação ao V17/V16/V15/V14/V13.

### O que a implementação da Missão 4 acrescentou ao design

Registrado em §6.4, no bloco “O que a implementação da Missão 4 fixou”. Em
resumo: o esqueleto saiu inteiro, nos nove arquivos previstos e sem mexer em
nenhuma decisão de estado; `FLAG_EVENT_ULTRABEAST_NEWBARK` = `0x1044` com
`CUSTOM_FLAGS_END` movida; a numeração 8/9/10 confirmada e a cadeia **encerrada**
em 10; o **orçamento de object events** entrou no vocabulário do projeto — teto
16 incluindo jogador e follower, light sprite custando zero, e objeto que não
cabe desaparecendo em silêncio; e quatro armadilhas que o build não pega
(`DIR_UP`/`DIR_RIGHT` inexistentes, travessão fora do charmap, `closemessage`
antes de `applymovement`, `setobjectxy` que não traz NPC escondido).

Duas lições de escrita, não de código, também viraram regra: **ator fora da
câmera não fala**, e **decisão de personagem que não chega à tela não existe** —
a distribuição das três Ultra Beasts e o “não” ao Gold/Crystal só passaram a
existir para quem joga depois de serem ditos em voz alta em todos os ramos.

E o aviso do `goto_if_ge` em Olivine falhou pela **terceira** vez seguida. A
regra, agora no código em comentário: estado novo entra como `goto_if_eq`, e só
o último da lista pode ser `goto_if_ge`.

### O que o evento PRÉ-NECROZMA acrescenta ao design

- **A reunião do §7 virou um evento com nome, escopo e documento** — o primeiro
  do arco que não é missão de Ultra Beast. Escopo fechado pelo autor: inteiro
  dentro de `OlivineCity_House1`, terminando **antes** da ida ao altar, com o
  gancho do altar e uma flag persistente.
- **`FLAG_EVENT_NECROZMA_ALTAR_UNLOCKED` é o primeiro handoff por flag do arco.**
  As quatro flags de missão são temporárias por natureza (setada ⇔ incidente
  ativo); esta é o contrário: liga uma vez e **nunca** é limpa. Invariante:
  setada ⇔ `VAR_RIFT_MISSIONS_STATE >= 12`.
- **A cadeia de estados continua onde as missões pararam, sem sobreposição.**
  10 → 11 → 12. O valor 11 existe por uma razão de design, não técnica: é o
  “reunião feita, parceiro ainda não evoluído” do §7 item 4, e é ele que impede a
  cutscene longa de tocar de novo enquanto o jogador desenvolve o Cosmog —
  lição herdada direto da pendência registrada na M4.
- **A checagem de time do §7 ganhou forma técnica:** `checkspecies` sobre
  `SPECIES_SOLGALEO` e, se falhar, `SPECIES_LUNALA`. Ela olha **apenas a
  equipe** (`CheckPartyHasSpecies` percorre `gPlayerParty`), o que realiza
  exatamente o §7: qualquer um dos dois serve, os dois não são exigidos, Cosmog
  e Cosmoem não passam, e Pokédex não substitui presença.
- **A sala mais cheia do arco está medida:** oito objetos e o jogador, 10/16 com
  o follower contado, num quarto de 11x7 tiles úteis com a mesa sólida no meio.
  A nota de escala do §7 (“a sala comporta”) deixa de ser estimativa.
- **Os dois parceiros fora da Poké Ball (§3.2) entram sem exceção e sem
  flexibilização:** Ninetales ao lado da Lillie, Silvally ao lado do Gladion,
  com a mesma flag de ocultação dos donos. Lusamine e Kukui continuam sem
  parceiro, como §3.2 determina.

### O que continua em aberto

- Runtime de tudo que é pós-E4: **nada foi testado no emulador**. Quatro missões
  dependem disso, e o balanceamento da M4 depende do resultado da M3.
- Beast Balls com a Anabel (§5), pendentes desde a M1 — e o evento PRÉ-NECROZMA
  passa exatamente pelo script dela sem resolvê-las.
- **Evento PRÉ-NECROZMA: esqueleto implementado (20/09/2026), runtime pendente.**
  A checklist de teste é o §10 do doc dele, e o passo 1 é o mais barato e o que
  pega o erro mais grave: entrar na casa **antes** do estado 10 e conferir que
  nenhum visitante está lá. Dois riscos de runtime herdados: os oito objetos
  numa sala pequena (10/16 medido em código, não em jogo) e o follower que fica
  escondido no estado 11 até o jogador sair da casa, porque `hidefollower` não
  tem inverso na engine.
- O altar, a viagem de navio, o duelo da Lusamine e Ultra Necrozma continuam sem
  doc. O próximo documento começa lendo `FLAG_EVENT_NECROZMA_ALTAR_UNLOCKED` e
  `VAR_RIFT_MISSIONS_STATE >= 12`, e precisa decidir o mecanismo de retry e de
  captura **antes** de começar (§9).
- A recomendação do §8 — reconferir Solgaleo/Lunala na primeira abertura do
  portal — é do doc do altar, não deste: o PRÉ-NECROZMA checa uma vez, na
  reunião, e não guarda “qual dos dois”.
- O presente do Friendly Trader de Cherrygrove continua sendo o ponto de maior
  risco de regressão silenciosa do projeto até ser testado.
