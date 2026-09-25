# SoulGold — Rift Missions

**Design consolidado v21 — Missões 1 (Blackthorn), 2 (Mahogany) e 3 (Cherrygrove) com a história evoluída (M1: Clair, Necrozma, resgate do Gladion, presente do Type: Null; M2: Pryce evacuando, Lillie como descoberta, sinergia das UBs, duas rodadas, Necrozma; M3: o aviso do Kukui, a sinergia que teleporta, o Fundador da Liga de Alola, o Necrozma mirando o jogador e a Anabel revelando que é Faller); Missão 4 (New Bark) e o evento PRÉ-NECROZMA (reunião de Olivine) em esqueleto implementado; arco de missões fechado no código e a reunião em cima dele; runtime validado só na M1**

Revisão V21: 22 de setembro de 2026. Substitui o V20 apenas no pós-E4: a **Missão 3 (Cherrygrove)** ganha a história, a partir do feedback do autor sobre o esqueleto. Quem avisou o Looker foi o **Kukui**, e o briefing em Olivine monta o engano que a praia desfaz — a ficha de duas páginas de um "civil". O **Necrozma** sobe do mar, rasga a fenda, e pela primeira vez **ataca uma pessoa**: vira para o jogador, e a **Anabel entra na frente** — é aí que a condição de **Faller** dela vem a público, **antecipada da Missão 4**, que passa a contar só o resto. A **sinergia** das UBs ganha consequência visual (a Blacephalon apaga a baía e o Stakataka **já está mais perto**) e forma fixa como regra comum. A surpresa da missão é **o que o Kukui é**: o Fundador da Liga de Alola, subestimado de propósito pelos dois policiais. Portas trancadas e gancho sem destino passam a valer também na M3. Registro em §25; implementação em [`.claude/rift_missions/CHERRYGROVE_ULTRABEAST/CHERRYGROVE_ULTRABEAST_IMPLEMENTATION.md`](CHERRYGROVE_ULTRABEAST/CHERRYGROVE_ULTRABEAST_IMPLEMENTATION.md) §13.

Revisão V20: 22 de setembro de 2026. Substitui o V19 apenas no pós-E4: a **Missão 2 (Mahogany)** ganha a história, a partir do feedback do autor sobre o esqueleto. A Lillie deixa de ser anunciada no briefing e vira descoberta; o Pryce aparece evacuando a cidade, tenta atingir o Necrozma e empresta o gelo para a estratégia da Lillie; o jogador enfrenta a UB escolhida **duas vezes seguidas** — na primeira vitória a parceira a revive pela sinergia, a Lillie refaz o plano e uma parede de gelo corta a troca; o Necrozma absorve as duas. Portas trancadas, padrão do Necrozma, gancho sem destino e acompanhante surpresa passam a valer também na M2. A **sinergia entre as Ultra Beasts** de cada missão vira regra comum (§6). Registro em §24; implementação em [`.claude/rift_missions/MAHOGANY_ULTRABEAST/MAHOGANY_ULTRABEAST_IMPLEMENTATION.md`](MAHOGANY_ULTRABEAST/MAHOGANY_ULTRABEAST_IMPLEMENTATION.md) §13.

Revisão V19: 22 de setembro de 2026. Substitui o V18 no pós-E4 **e** acrescenta reações opcionais à família Cosmog em quatro encontros pré-Liga (§4.11). Feedback do autor sobre o esqueleto da Missão 1, que passa a ter uma **história de verdade**: a Clair já está lutando contra um Pokémon desconhecido (Necrozma) quando o jogador chega; Buzzwole e Pheromosa saem da fenda que ele abre e partem **para cima do jogador**; Gladion e Silvally chegam no último segundo; depois da luta o Necrozma **absorve as duas Ultra Beasts** e vai embora, diante de um elenco espantado; e o Gladion dá ao jogador um **Type: Null** que encontrou abandonado. Quatro decisões novas valem para o arco inteiro: o **padrão do Necrozma** (§6, regras comuns), as **portas trancadas** da cidade evacuada, o **gancho sem destino** (o próximo local é mistério até voltar a Olivine) e a **surpresa do acompanhante** (ninguém o anuncia antes da cena). Registro completo em §23.

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
| Ligação do Looker + escritório de Olivine + Blackthorn (Missão 1) | **História evoluída (22/09/2026, V19):** Clair contra Necrozma na chegada, UBs atacando o jogador, resgate do Gladion + Silvally, absorção pelo Necrozma, reação opcional à família Cosmog, presente do Type: Null com checagem de espaço antes do SIM, portas trancadas exceto o Centro, boss 3 barras / Lv75 / x120 / moveset curado + item. Falas finais. Build limpo; **validado em runtime pelo autor (22/09/2026)**. Receita na skill `evoluir-historia-de-evento`. **Antes: esqueleto implementado (19/09/2026):** conforme [`.claude/rift_missions/BLACKTHORN_ULTRABEAST/BLACKTHORN_ULTRABEAST_IMPLEMENTATION.md`](BLACKTHORN_ULTRABEAST/BLACKTHORN_ULTRABEAST_IMPLEMENTATION.md), da ligação ao gancho para a Missão 2 (Looker e Anabel moram em Olivine desde o New Game; escolha da UB + boss battle). Build limpo; runtime pendente. Primeira batalha de ameaça: derrota = blackout/retry. |
| Limpeza de treinadores | Informada como concluída pelo autor; este documento não certifica IDs ou contagens livres. |
| Missão 2 — Mahogany (Xurkitree + Celesteela, Lillie) | **História evoluída (22/09/2026, V20):** Lillie como descoberta ao chegar (fora do briefing); Pryce + Mamoswine evacuando os últimos moradores na tela, Blizzard sem efeito no Necrozma, entrada no Ginásio no fim; sinergia das UBs mostrada, vencendo a rodada 1 (revive) e derrotada pela parede de gelo da Lillie + Pryce; duas rodadas seguidas (2 barras, depois 4 / Lv80 / x130) com cura da Anabel entre elas; absorção pelo Necrozma; reação opcional à família Cosmog; portas trancadas exceto o Centro; gancho sem destino. Falas finais. Build limpo; **runtime pendente**. **Antes: esqueleto implementado (19/09/2026)**, conforme [`.claude/rift_missions/MAHOGANY_ULTRABEAST/MAHOGANY_ULTRABEAST_IMPLEMENTATION.md`](MAHOGANY_ULTRABEAST/MAHOGANY_ULTRABEAST_IMPLEMENTATION.md) §12. |
| Missão 3 — Cherrygrove (Necrozma, Blacephalon + Stakataka, Kukui) | **História evoluída (22/09/2026, V21):** o Kukui é quem avisou (briefing reescrito, com a ficha de duas páginas que a cena desmonta); Necrozma sobe do mar, abre a fenda e depois **absorve as duas**; a sinergia das UBs é mostrada como teleporte sob o flash, duas vezes, a segunda colada no jogador; o Kukui solta um Incineroar e revela que fundou a Liga de Alola; o Necrozma mira o **jogador** e a **Anabel entra na frente e revela que é Faller** (antecipado da M4); reação opcional à família Cosmog; portas trancadas exceto o Centro; presente sem item (o convite do Kukui); gancho sem destino. Dificuldade inalterada (4 barras / Lv85 / x140 / moveset curado + golpe de controle + item). Build limpo; **runtime pendente**. **Antes: esqueleto implementado (20/09/2026):** conforme [`.claude/rift_missions/CHERRYGROVE_ULTRABEAST/CHERRYGROVE_ULTRABEAST_IMPLEMENTATION.md`](CHERRYGROVE_ULTRABEAST/CHERRYGROVE_ULTRABEAST_IMPLEMENTATION.md) (§12 registra o feedback da implementação). Implementada **inteira, sem cortes**, nos cinco arquivos previstos e sem alterar nenhuma decisão de estado. Continua a var nos estados 6→7→8 e substituiu o stub da M3 em Olivine, que virou stub da M4. Terceiro degrau da escala (4 barras / Lv85 / x140 / moveset curado + golpe de controle + item) e **primeira missão a mexer em conteúdo pré-existente** (os dois presentes do Friendly Trader). Build limpo; runtime pendente. |
| Missão 4 — New Bark (Kartana + Guzzlord + Nihilego, Lusamine) | **Esqueleto implementado (20/09/2026):** conforme [`.claude/rift_missions/NEWBARK_ULTRABEAST/NEWBARK_ULTRABEAST_IMPLEMENTATION.md`](NEWBARK_ULTRABEAST/NEWBARK_ULTRABEAST_IMPLEMENTATION.md) (§12 registra o feedback da implementação e **vence o resto daquele doc** onde os dois divergem). Implementada **inteira, sem cortes**, nos nove arquivos previstos e sem alterar nenhuma decisão de estado. Continua a var nos estados 8→9→10, **encerra a cadeia de missões** e transformou o stub da M4 em Olivine no stub da **reunião**. Quarto degrau da escala (4 barras / Lv90 / x150 / moveset de dois eixos + item) e primeira cena do arco com **orçamento de objetos medido em código** (12/16). Build limpo; runtime pendente. |
| Evento PRÉ-NECROZMA — reunião de Olivine (Looker, Anabel, Lusamine, Lillie + Ninetales, Gladion + Silvally, Kukui) | **Esqueleto implementado (20/09/2026):** conforme [`.claude/rift_missions/PRE_NECROZMA_ULTRABEAST/PRE_NECROZMA_ULTRABEAST_IMPLEMENTATION.md`](PRE_NECROZMA_ULTRABEAST/PRE_NECROZMA_ULTRABEAST_IMPLEMENTATION.md) (§12 registra o feedback da implementação e **vence o resto daquele doc** onde os dois divergem). Implementada **inteira, sem cortes**, nos cinco arquivos previstos e sem alterar nenhuma decisão de estado. Continua a var nos estados 10→11→12, **substituiu o stub da reunião** que a M4 deixou em Olivine e termina ligando `FLAG_EVENT_NECROZMA_ALTAR_UNLOCKED` — a primeira flag do arco que **nunca é limpa** e o primeiro handoff por flag entre dois documentos. Primeiro evento do arco **sem batalha nenhuma**: o papel do retry cabe ao estado 11, e a única checagem de time do arco (Solgaleo **ou** Lunala, só na equipe) pode falhar indefinidamente sem custo. Oito objetos numa sala de 11x7 (10/16 de orçamento). Build limpo; runtime pendente. Navio, altar, duelo da Lusamine e Ultra Necrozma **não** são escopo dele. |
| Evento ALTAR DO SOL E DA LUA — Lusamine e Ultra Necrozma (clímax) | **Planejado, revisão 2 (23/09/2026, V24):** conforme [`.claude/rift_missions/ALTAR_SUN_MOON/ALTAR_SUN_MOON_IMPLEMENTATION.md`](ALTAR_SUN_MOON/ALTAR_SUN_MOON_IMPLEMENTATION.md). **Nada implementado**, e o plano já traz a **história completa** em vez de placeholder, porque o terreno estava pronto (mapa, tileset com estado de portal, navio, arena, sprites, `MAPSEC` renomeada). Cinco atos, estados 12→13→14→15→16, num mapa e meio: chegada e oferta da Lusamine; duelo narrativo dela (SIM/NÃO, sem blackout, os dois resultados resolvem, a Lillie fecha); a fenda de chão no pátio; Ultra Necrozma na arena com a Anabel, boss de **5 barras / Lv90 / x160** e perfil de fases que **descasca** a criatura; captura roteirizada; despedida. **Fecha cinco pendências do §14** (Escritório pós-história, Beast Balls, Altar menos o Fly, Necrozma, Despedida) e é o **primeiro evento do arco sem flag persistente nova** — toda visibilidade é `FLAG_TEMP_*` recalculada, mais cinco daily flags. Deixa a fenda diária e a arena vazia como handoff para o documento do **loop**. |

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
5. Na casa de Olivine, Looker e Anabel apresentam a investigação e enviam o jogador a Blackthorn, onde a Líder de Ginásio Clair relatou “um Pokémon feito de luz” e segura a criatura sozinha. **Ninguém menciona o Gladion** (V19).
6. **Missão 1 — Blackthorn:** a Clair já enfrenta o Necrozma na rua com o Kingdra, sem efeito. O Necrozma abre a primeira ruptura explícita; Buzzwole e Pheromosa atravessam e partem para cima do jogador; Gladion e Silvally chegam no último instante. O jogador escolhe qual enfrenta numa boss battle; Gladion e Silvally ficam com a outra. Depois da vitória, o Necrozma absorve as duas e some. A partir daqui derrotas contra ameaças usam blackout/retry. O fim da missão manda o jogador de volta a Olivine **sem dizer para onde vai a próxima** (V19).
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

**Voz (V17, validado pelo autor na M2).** Lillie **observa e duvida; nunca prevê**. Ela reconhece uma Ultra Beast à primeira vista e reconhece a luz do Necrozma — é a experiência de Alola —, e isso convive com não fazer ideia do que está acontecendo nem do que vem a seguir. Ela relata o que anotou, diz onde não enxergou, oferece uma ideia como ideia ("It's the only idea I have"), e corrige o próprio plano em voz alta quando os fatos mudam. O que ela **não** faz: marcar a hora, anunciar a fenda, ou chegar numa cena com a resposta pronta. Falas desse tipo vão para a Anabel.

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
| Blackthorn, Missão 1 pós-game | Silvally | Chega sem aviso e salta entre o jogador e as Ultra Beasts; a relação consolidada aparece sob pressão real. Gladion entrega ao jogador o Type: Null que encontrou. |
| Missões pós-E4 | Silvally | Mantém a evolução e a relação consolidada. |

A evolução acontece na jornada de Gladion entre Cianwood e a Victory Road. Não depende de vencer o jogador em nenhuma batalha anterior. A primeira apresentação explícita de Silvally ocorre no encontro anterior à Victory Road; portanto, Blackthorn já usa Silvally. Não exige uma cutscene de evolução ou nova flag: as equipes de cada encontro podem representar os estágios previstos. Níveis, golpes, itens, demais membros e Memórias ainda precisam de balanceamento.

**Sequência de diálogo para implementação:**

1. Em Violet, depois de mencionar Lillie e antes do desafio, Gladion apresenta brevemente Type: Null. Após qualquer resultado válido da batalha, reconhece algo observado e entrega o ovo.
2. Em Cianwood, o diálogo sobre Johto e Lillie mostra Gladion vivendo sua própria viagem; a batalha acontece sem menu de recusa e Type: Null sai na frente na despedida.
3. Antes da Victory Road, Gladion apresenta Silvally antes da luta. A evolução precisa ser vista mesmo se o jogador perder; não depende de resultado anterior.
4. Em Blackthorn, já no pós-game, Gladion e Silvally chegam de surpresa e cortam o ataque; uma instrução curta mostra a parceria consolidada. A história do abandono volta **uma vez**, para explicar o Type: Null que ele entrega ao jogador — sobre o bicho novo, não sobre o Silvally.

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

Não repetir a mesma explicação em todos os encontros. A evolução deve ser percebida nas atitudes de ambos. Esse parceiro permanece com Gladion.

**Presente de Type: Null (V19, decisão do autor, substitui a proibição anterior).** Ao fim da Missão 1, em Blackthorn, Gladion entrega ao jogador **outro** Type: Null — um terceiro indivíduo, que ele encontrou sozinho nas montanhas depois da Route 45, abandonado como o dele. O bicho não se acomoda com ele (“vive tentando ser a sombra do Silvally”), assistiu o jogador lutar e “já decidiu”. A fala de despedida devolve ao jogador a lição do arco do próprio Gladion: *não decida tudo por ele; deixe que ele dê o primeiro passo*. Como toda entrega de Pokémon (skill `entregar-pokemon-ou-ovo`), a checagem de espaço vem **antes** da oferta: com equipe **e** PC cheios o Looker não aceita o SIM (“regra da Anabel: sempre espaço para mais um Pokémon — se uma fenda deixar alguém para trás, ele precisa ter para onde ir”). Nível 50 no esqueleto; quem abandonou este Type: Null continua em aberto.

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

Ela distingue observação de hipótese. **Precisão da V21:** ser Faller lhe dá **uma** coisa, física e muda — ela **sente uma ruptura abrir**, alguns segundos antes de qualquer instrumento registrar, e não consegue explicar como. Só isso. Não identifica realidades, não sabe o que vem, quantos são nem o que vai acontecer, não prevê o enredo e não lê o Necrozma. Quem mede continua sendo o instrumento, e é o instrumento que ela cita em relatório. Saber que atravessou uma ruptura não significa lembrar de tudo que viveu antes dela. Ela pode falar com segurança sobre sua condição e admitir as lacunas.

**Progressão da revelação:**

| Momento | Conteúdo e intenção |
| --- | --- |
| Missões 1 e 2 pós-E4 | Mostra atenção especial a desorientação e deslocamento. Não explica toda a biografia no primeiro briefing. Em Mahogany planta **uma única linha**: sente a ruptura antes de os instrumentos se moverem e corta o assunto. |
| **Missão 3 (Cherrygrove), em campo — V21** | **A revelação**, antecipada da M4 a pedido do autor. Ela sente a ruptura antes do instrumento e diz apenas "It's here"; mais tarde o Necrozma mira o **jogador** e ela entra na frente e leva a luz. De joelho na areia molhada, em cinco caixas, ela diz **o que é** — "I knew it was coming because I have been on the other side of one. I'm a Faller." — e corta ("The rest of it later"), voltando ao trabalho na frase seguinte. Detalhe em §6.3. |
| **Missão 4 (New Bark), no briefing de Olivine — V22** | **O resto**, não a notícia, e **fora do campo de batalha**. Pedido do autor: a conversa de Faller não cabe no meio de uma luta. Três rupturas abrindo juntas são a primeira coisa que ela sente **de outra cidade** — de uma cadeira em Olivine, com sessenta milhas e uma montanha no meio —, e é esse susto que a faz pedir a cadeira e contar tudo, sentada, antes de qualquer perigo: o que é um Faller, o que ela não lembra, a mão de alguém, e a promessa. Começa em "On that beach in Cherrygrove I told you what I am. I did not tell you the rest." Detalhe em §6.4. |
| **Missão 4 (New Bark), em campo** | **Só o custo físico.** Três rupturas ao mesmo tempo são altas demais: ela perde alguns segundos de pé, Looker a ampara, ela recusa a ajuda em duas caixas e **recusa repetir o assunto** ("{PLAYER} knows why. I'm not saying it again in the middle of a road"). Volta ao comando na frase seguinte, e é ela quem entrega o contra-ataque da cena. |
| **Missão 4 (New Bark), no rescaldo** | **Uma caixa**, depois da derrota: a promessa de Olivine é a única coisa que sobrou. "We lost the road today. We did not lose that. Both. Always both." |
| Reunião em Olivine, antes de liberar o navio | Já revelada, ela **usa** a própria condição em vez de anunciá-la: é o argumento de por que ninguém atravessa sem plano de volta. Se o jogador precisar de recapitulação, cabe em uma caixa. |
| Preparação no altar | Usa essa experiência para sustentar um plano coletivo. Escuta Lusamine, mas insiste em que todos tenham uma forma de voltar. |
| Despedida e pós-Necrozma | Escolhe permanecer para ajudar a fechar rupturas e dar assistência a quem for deslocado. Sua motivação vai além da obrigação profissional. |

**Sequência de cena, em duas partes (V21: a primeira acontece em Cherrygrove, a segunda em New Bark; nenhuma delas na reunião):**

*Parte 1 — Cherrygrove, Missão 3, no meio do incidente:*

1. Ela para no meio de uma instrução, alguns segundos antes de qualquer leitura. "It's here." — "There is nothing on the meter." — "I know." Ninguém explica nada.
2. Mais tarde o Necrozma vira para o **jogador**. Ela grita e entra na frente, e a luz a pega.
3. De joelho na areia, recusa ajuda de pé: "Let go, Looker. I can stand."
4. Diz **o que é**, em poucas caixas, e liga isso ao que fez no passo 1: sentiu porque já esteve do outro lado de uma. É uma sensação física, não um dossiê.
5. Corta o assunto sozinha ("The rest of it later") e retoma o comando na frase seguinte. A revelação **não** interrompe a missão.

*Parte 2 — Olivine, briefing da Missão 4, sentada (V22):*

6. Ela para no meio do relatório e pede a cadeira: sentiu as três **de Olivine**, coisa que nunca aconteceu. Conta o resto sem pressa — não lembra o nome do lugar de onde veio; lembra a mão de alguém; quer oferecer o mesmo a quem chegar. Looker reconhece a decisão sem contar a história por ela, e ela manda pôr no relatório e assina.

*Parte 3 — New Bark, em campo, e depois no rescaldo:*

7. Em campo, só o custo: ela oscila, Looker a ampara, duas caixas, e ela **recusa repetir o assunto numa rua aberta**. Volta ao comando e entrega o contra-ataque. Depois da derrota, uma caixa: a promessa continua de pé mesmo quando o dia não.
8. Na reunião de Olivine (§7), a mesma condição reaparece **como argumento**, não como notícia: é por isso que ela exige um plano de volta antes de liberar o navio.

**Falas originais propostas em inglês:**

> Primeiras missões: “Being somewhere unfamiliar can be frightening. Give it room. We don't yet know what it has been through.”
>
> Revelação (Cherrygrove, V21): “I knew it was coming because I have been on the other side of one. I'm a Faller. I came through a tear like that one. There are years of me I have not got back.”
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

**Em Blackthorn:** chega depois da Clair, que já evacuou a cidade; recebe o jogador no Centro, impõe a regra da Anabel (espaço para mais um Pokémon), observa a ruptura e, terminada a luta, pergunta primeiro se alguém se feriu. Não nomeia a criatura: ninguém em Johto a conhece. Participar de todas as quests não exige dar-lhe uma batalha ou equipe nova. **No escritório:** reconhece uma informação específica de cada missão, em vez de repetir apenas que surgiu outra ocorrência. **No altar:** informa o que foi confirmado sobre a passagem e admite o que ainda é incerto. **No loop:** mantém falas breves para partidas repetidas, com interesse pelo retorno da equipe.

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
| 4 · Kartana + Guzzlord + Nihilego / Lusamine | Oferece conhecimento sem exigir obediência; reconhece limites e prioriza cuidado sobre controle. **A missão põe duas mães na mesma rua** (Lusamine e a mãe do jogador) e é quem a repreende que a faz perguntar em vez de decidir. **V22:** e a primeira coisa que ela faz com isso é pôr na linha o filho de outra pessoa, contra a polícia. Elm, a mãe e Gold/Crystal participam sem batalha de treinador. |

Looker participa de todas as quests. Anabel ajuda a estabelecer objetivos e condições de segurança. Os acompanhantes não devem repetir a mesma explicação do investigador com palavras diferentes.

**Continuidade visual dos parceiros:** quando Lillie participa (Missão 2 e cenas finais), Alolan Ninetales deve estar presente fora da Poké Ball ao lado dela. Quando Gladion participa (Missão 1 e cenas finais), Silvally deve estar presente fora da Poké Ball ao lado dele. A batalha específica da missão pode usar outros membros da equipe; a presença overworld do parceiro principal continua sendo parte da identidade visual da cena.

**Precisão da V21:** esta regra fala de presença **permanente** — o parceiro já está ao lado do personagem quando o jogador chega, e continua lá. Um Pokémon **solto no meio da cena** e devolvido à bola antes do fim é encenação, não identidade, e não abre exceção nenhuma. É por isso que o Kukui continua chegando sozinho na praia de Cherrygrove (§6.3) e mesmo assim solta um Incineroar na hora do perigo: ninguém ter visto uma Poké Ball nele em quatro dias é justamente o que faz a surpresa funcionar.

### 3.3. Regras de escrita e revisão de cenas

- Antes de escrever, identificar o que cada personagem sabe naquele momento. Experiência com Cosmog não revela automaticamente a espécie de um ovo fechado.
- Cada cena precisa dar ao personagem um objetivo além de elogiar o jogador ou entregar uma recompensa.
- Reencontros mudam a relação: Gladion passa de avaliação a confiança; Lillie transforma preparação em iniciativa; Lusamine aprende a compartilhar decisões.
- Tom de conversa e extensão da fala devem variar. Usar poucas caixas com informação concreta; reservar falas longas para decisões importantes.
- Equipes iniciais acessíveis não devem fazer personagens experientes fingirem que nunca lutaram. Tratar os confrontos iniciais como treino com uma equipe adequada; não fixar novas espécies ou níveis sem decisão de balanceamento.
- Teste editorial: sem a identificação do falante, a escolha das palavras e a intenção ainda sugerem quem está falando?
- **O nome de quem fala vai numa plaquinha acima da caixa, nunca dentro da fala (V17).** Escreve-se `{SPEAKER NAME_X}` no começo do texto; o prefixo `"Nome: "` não existe mais. Skill `nomear-falante`. Vale para toda cena de história, nova ou antiga.
- **Experiência não é previsão (V17).** Um personagem que já viu algo parecido reconhece o **que** é; isso não o autoriza a saber o **que vai acontecer**, nem a marcar a hora, nem a anunciar o que ainda não chegou. Quem mede é quem tem instrumento (a Anabel). Quando uma fala faz um personagem soar como quem sabia o que vinha, ela pertence a outro personagem. Regra tirada do retorno do autor sobre a Lillie em Mahogany (doc da M2 §14).
- **Presença recorrente no pós-game é escala de dia da semana, não sorteio (V24).**
  Um personagem que "aparece de vez em quando" aparece em dias fixos da semana,
  lidos com `GetDayOfWeek`. Sorteio por load faz o personagem piscar quando o
  jogador sai e volta, e consertar isso exige uma var de "sorteio de hoje" mais
  uma daily flag. A escala também é **descobrível** pelo jogador, que é a
  mecânica dos irmãos dos dias da semana que este jogo já tem. Regra que vem com
  ela: **ninguém em dois lugares no mesmo dia** — conferir a tabela inteira
  antes de acrescentar um personagem a ela (§9).
- **Revanche de pós-game não é duelo narrativo (V24).** Duelo narrativo é cena de
  história e não pode dar blackout; revanche diária é treinador comum e **dá**
  blackout. A daily flag da revanche é setada **antes** da batalha, nunca depois:
  depois é inalcançável na derrota, porque o blackout não volta para o script.
- **A única exceção, e ela é estreita (V21).** A Anabel **sente uma ruptura abrir** segundos antes do instrumento, porque é Faller. É uma sensação física e muda: ela diz que está acontecendo, não o que é, quantos são nem o que vem. Continua sendo o instrumento quem mede e quem entra no relatório. Nenhum outro personagem tem sentido nenhum, e a Anabel não ganha outros. Ver §3.1 e §6.3.

## 4. Encontros durante a campanha

| Evento | Gatilho narrativo | Conteúdo fechado |
| --- | --- | --- |
| Primeira batalha de Lillie | Recebimento da Pokédex | Batalha obrigatória com Alolan Vulpix nível 7; vitória ou derrota continuam a cena sem blackout. |
| Gladion em Violet | Ligação de Elm e entrega do Mystery Egg no Pokémon Center | Substitui o assistente; batalha obrigatória antes do ovo; vitória ou derrota permitem a entrega. |
| Lillie em Goldenrod | Evento de entrega do SquirtBottle, após Whitney | Cena automática; batalha obrigatória com continuidade em vitória ou derrota, entrega e saída pela porta. |
| Gladion em Cianwood | Entrega existente de Fly, após Chuck | Conversa sobre Johto/Lillie, batalha obrigatória e Fly em vitória ou derrota; Type: Null sai na frente. |
| Lillie no Dragon’s Den | Depois de derrotar Clair, durante o teste de perguntas | Lillie acompanha as cinco perguntas vanilla, reage às escolhas do jogador e responde por si mesma; o Elder encerra com uma demonstração prática. Vitória ou derrota concluem sem blackout. |
| Gladion antes da Victory Road | Imediatamente antes do acesso à Victory Road | Primeira apresentação de Silvally; batalha obrigatória, sem menu de recusa, com continuidade em vitória ou derrota. Gladion não é gate de acesso. |
| Blackthorn — Missão 1 | Pós-game: ligação do Looker ao sair de casa após o HoF → briefing em Olivine | Clair contra Necrozma na cidade evacuada, portas trancadas; o Necrozma abre a ruptura e Buzzwole + Pheromosa atacam o jogador; Gladion/Silvally chegam de surpresa; o jogador escolhe qual enfrenta (boss battle) e Gladion fica com a outra; derrota é falha real com blackout/retry. O Necrozma absorve as duas; Gladion entrega um Type: Null. Gancho de volta a Olivine, sem destino. |

A ordem pré-Liga fica: **Route 30 → Violet → Goldenrod → Cianwood → Dragon’s Den → Gladion antes da Victory Road → Victory Road → Liga**. A ordem lista apenas os encontros desta questline, não todos os eventos vanilla entre eles. Não existe mais batalha opcional de Gladion na entrada da Liga.

Depois da E4: **ligação do Looker → escritório de Olivine → Missão 1 (Blackthorn) → Olivine → Missões 2, 3 e 4 com retorno a Olivine após cada → reunião/altar → Lusamine → Ultra Necrozma**.

**Diretriz para Blackthorn (atualizada na V19 — história em §6, regras comuns, e no doc da M1 §5–§7):** o incidente abre a trama pós-game e é o primeiro confronto em que derrota deixa de ser apenas um resultado de personagem. No V14 ele é a Missão 1 e não deve oferecer captura antecipada de Buzzwole ou Pheromosa: a implementação bloqueia a captura (`B_FLAG_NO_CATCHING`). **Formato da batalha (V14, revisão 2):** o jogador escolhe Buzzwole ou Pheromosa e enfrenta a escolhida numa **boss battle simples** pelo sistema de boss do projeto (`setbossbattle`, várias barras de HP, IA inteligente); Gladion e Silvally enfrentam a outra, de forma narrativa. "Run" num boss é desistência e dá blackout, como a derrota. Motivo técnico, verificado em 19/09/2026: o boss só existe em batalha simples, e batalha selvagem com parceiro só existe via NPC follower (desligado).

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

### 4.11. Reações à família Cosmog nos encontros pré-Liga (V19)

Pedido do autor: quem traz o Pokémon do Mystery Egg na equipe recebe um momento
de Sun & Moon. Lillie e Gladion conhecem Cosmog de Alola — a Lillie viajou com o
**Nebby**, e o Gladion o viu metê-la em confusão e tirá-la dela. Ver um Cosmog em
Johto é, para os dois, uma lembrança.

Regras:

- **Opcional e sem estado.** Nenhuma flag, nenhuma var. Sem a família na equipe,
  a cena corre exatamente como antes.
- Detecção pelo special `CheckMysteryEggPokemon` (`src/braille_puzzles.c`), o
  mesmo da Eviolite do Elm: percorre a equipe inteira, ignora ovos, devolve a
  primeira espécie da família. Três falas por encontro: Cosmog, Cosmoem e
  Solgaleo/Lunala (nome pelo `{STR_VAR_1}`).
- O parceiro fora da Poké Ball reage primeiro (“!”) — é o Pokémon que percebe.
- **O Cosmog do jogador não é o Nebby** (§3.1). A Lillie **lembra** do Nebby; nunca
  chama o Pokémon do jogador por esse nome.
- **O Gladion não sabia o que havia no ovo** (§3.3): em Cianwood, a primeira vez
  que vê o Pokémon chocado, ele descobre ali (“então era isso que tinha no ovo”).

| Encontro | Arquivo | Onde entra | Quem reage | O que diz |
|---|---|---|---|---|
| Lillie inicial, Route 30 | — | **não se aplica** | — | O ovo ainda não existe. |
| Gladion, Violet | — | **não se aplica** | — | É ele quem entrega o ovo; não há Cosmog chocado. |
| Lillie, Goldenrod | `GoldenrodCity_FlowerShop/scripts.pory` | depois da fala sobre o Type: Null do irmão | Lillie | Cosmog: lembra do Nebby, que nunca ficava na bolsa. Cosmoem: “o Nebby fez igual; não está doente, está crescendo”. Solgaleo/Lunala: “o Nebby virou um também; escolheu alguém corajoso”. |
| Gladion, Cianwood | `CianwoodCity/scripts.inc` | depois de “Good morning”, antes do desafio | Type: Null, depois Gladion | Descobre o que havia no ovo; a Lillie teve um em Alola, que a meteu em mais confusão do que ele consegue contar — e a tirou de algumas. “Mantenha perto. Eles se perdem.” |
| Lillie, Dragon's Den | `DragonsDen_Shrine/scripts.inc` | depois da batalha, antes da despedida | Ninetales, depois Lillie | Liga o Nebby ao teste do Elder: o Nebby observava e fazia o contrário do que ela pedia — confiando que ela o alcançaria. |
| Gladion, Victory Road | `ReceptionGate/scripts.inc` | depois de “From here, it's you and your team” | Silvally, depois Gladion | Mede o Cosmog do jogador pelo crescimento do próprio parceiro: “o Type: Null também levou o tempo dele; não deixe a Liga apressá-lo”. |

No pós-game, a mesma reação aparece na Missão 1 (Necrozma e o elenco, §6 regras
comuns, doc da M1 §6.6), na Missão 3 (Necrozma depois da batalha, Anabel e Kukui
antes dela, e a conversa final — doc da M3 §5.2) e na **Missão 4** (Lusamine e
Elm nas conversas ociosas, a criatura depois da batalha e a Lusamine outra vez na
conversa final — doc da M4 §3.5.1 e §5.6). Na M4 a reação da Lusamine é onde o
§6.4 finalmente chega à tela: ela usou um Cosmog, sabe como aquele brilho se
parece do outro lado, e é ela quem diz que **nada disso é culpa do jogador**.

## 5. Escritório em Olivine

**Local definido (V14):** `OlivineCity_House1` — a casa da rua norte de Olivine mais próxima do Ginásio. O NPC da troca do Voltorb Hisuiano que ocupava a casa muda para `OlivineCity_House3`, posição (7,4), mantendo `FLAG_OLIVINE_NPC_TRADE_COMPLETED`.

**Entrada no arco:** depois do primeiro Hall of Fame, ao sair de casa em New Bark, Looker liga para o jogador, apresenta-se, fala das aparições de seres estranhos e pede ajuda ao novo Campeão de Johto. Ao chegar à casa, Looker e Anabel recebem o jogador numa cena automática e o enviam a Blackthorn. O escritório é visitado **antes** da Missão 1 e depois de cada missão.

Looker e Anabel moram na casa **desde o New Game, sem flag de visibilidade**; `VAR_RIFT_MISSIONS_STATE` só troca o diálogo ("férias" antes da ligação, briefing, "vá na frente", stub da próxima missão) e dispara a cena de chegada. A cena de chegada e o despachante de briefing atendem **todas** as missões: cada retorno ao escritório reaproveita a mesma coreografia e só troca o texto e o par flag/estado que ela seta. Durante as missões eles aparecem em Olivine e no local da missão ao mesmo tempo — **aceito pelo autor**: a missão inteira é uma cutscene, e não se esconde ninguém em Olivine. Estado e implementação: [`.claude/rift_missions/BLACKTHORN_ULTRABEAST/BLACKTHORN_ULTRABEAST_IMPLEMENTATION.md`](BLACKTHORN_ULTRABEAST/BLACKTHORN_ULTRABEAST_IMPLEMENTATION.md) (§1.2 e §3) para a entrada no arco e a Missão 1; [`.claude/rift_missions/MAHOGANY_ULTRABEAST/MAHOGANY_ULTRABEAST_IMPLEMENTATION.md`](MAHOGANY_ULTRABEAST/MAHOGANY_ULTRABEAST_IMPLEMENTATION.md) (§2) para o retorno ao escritório e o briefing da Missão 2; [`.claude/rift_missions/CHERRYGROVE_ULTRABEAST/CHERRYGROVE_ULTRABEAST_IMPLEMENTATION.md`](CHERRYGROVE_ULTRABEAST/CHERRYGROVE_ULTRABEAST_IMPLEMENTATION.md) (§2) para o da Missão 3. A partir da M2 o padrão está fechado: **cada missão nova acrescenta um estado ao gatilho de chegada e um ramo ao despachante `BriefingTalk`, e renomeia o stub da missão seguinte** — nenhum objeto novo, nenhuma coreografia nova.

O escritório concentra o briefing da missão ativa, o retorno após cada missão e a compra de Beast Balls com Anabel. As missões são consecutivas, seguindo a ordem fixa abaixo. Não é necessário criar um sistema aberto de seleção durante essa parte da história.

Cada missão deve ter uma ocorrência local, participação do elenco indicado e resolução que permita ao jogador apresentar o resultado a Looker. Os objetivos intermediários e diálogos completos serão desenvolvidos a partir das diretrizes de personagem; este design não estabelece puzzles ou minijogos obrigatórios.

## 6. As quatro missões pós-E4 (V14)

Para deixar o pós-game mais dinâmico e menos maçante, as nove missões de uma Ultra Beast cada foram condensadas em **quatro missões de chefes simultâneos**: duas Ultra Beasts por missão, e três na missão final.

| Ordem | Ultra Beasts | Cidade | Personagem em destaque, além de Looker | Estado do evento | Implementação |
| --- | --- | --- | --- | --- | --- |
| 1 | Buzzwole + Pheromosa (+ Necrozma, que absorve as duas) | Blackthorn | Gladion (+ Silvally), de surpresa; **Clair** (+ Kingdra), Líder de Ginásio defendendo a cidade; Anabel presente | **História evoluída e validada em runtime** (22/09/2026, V19) | [`.claude/rift_missions/BLACKTHORN_ULTRABEAST/BLACKTHORN_ULTRABEAST_IMPLEMENTATION.md`](BLACKTHORN_ULTRABEAST/BLACKTHORN_ULTRABEAST_IMPLEMENTATION.md) |
| 2 | Xurkitree + Celesteela (+ Necrozma, que absorve as duas) | Mahogany | Lillie (+ Ninetales), descoberta ao chegar; **Pryce** (+ Mamoswine), Líder de Ginásio evacuando a cidade; Anabel presente | **História evoluída** (22/09/2026, V20), build limpo, runtime pendente | [`.claude/rift_missions/MAHOGANY_ULTRABEAST/MAHOGANY_ULTRABEAST_IMPLEMENTATION.md`](MAHOGANY_ULTRABEAST/MAHOGANY_ULTRABEAST_IMPLEMENTATION.md) |
| 3 | Blacephalon + Stakataka (+ Necrozma, que absorve as duas) | Cherrygrove | Kukui, **Fundador da Liga de Alola** — chega sozinho e solta um Incineroar no meio da luta; Looker e Anabel o subestimam de propósito. Anabel presente, e é **aqui** que a condição de Faller dela vem a público | **História evoluída** (22/09/2026, V21), build limpo, runtime pendente | [`.claude/rift_missions/CHERRYGROVE_ULTRABEAST/CHERRYGROVE_ULTRABEAST_IMPLEMENTATION.md`](CHERRYGROVE_ULTRABEAST/CHERRYGROVE_ULTRABEAST_IMPLEMENTATION.md) |
| 4 | Kartana + Guzzlord + Nihilego | New Bark | Lusamine + Anabel (ficam com as duas UBs que o jogador não escolher); **Prof. Elm, a mãe do jogador e Gold/Crystal** em papéis sem batalha | **Esqueleto implementado** (20/09/2026), build limpo, runtime pendente | [`.claude/rift_missions/NEWBARK_ULTRABEAST/NEWBARK_ULTRABEAST_IMPLEMENTATION.md`](NEWBARK_ULTRABEAST/NEWBARK_ULTRABEAST_IMPLEMENTATION.md) |

Estados possíveis de um evento, conforme a skill `evento-esqueleto`: **não planejado** → **planejado** (doc de implementação escrito) → **esqueleto implementado** (build limpo) → **validado em runtime** → **evoluído** (falas, coreografia e balanceamento finais). Nenhum evento avança de estado neste documento sem o doc correspondente ser atualizado junto.

A progressão exige retorno ao escritório de Olivine após cada missão; cada missão termina com um gancho que manda o jogador de volta. A Missão 4 é a última ocorrência e prepara a transição para o encerramento da investigação e a expedição ao altar.

Regras comuns a todas as missões:

- **Escolha + boss (estrutura padrão, V14 revisão 2):** as UBs da missão surgem juntas; o jogador escolhe qual enfrenta e o acompanhante fica com a(s) outra(s). A luta do jogador é uma boss battle simples com captura bloqueada; a do acompanhante é narrativa e muda a fala depois da vitória. A escolha é refeita a cada tentativa. Isso deixa a história dinâmica e cada missão rejogável de outro jeito.
- Batalha de ameaça: derrota ou desistência = blackout no Pokémon Center e retry, sem avançar o estado. O retry vem de manter o estado "missão ativa" até a vitória.
- Durante a missão ativa, a cidade é evacuada: NPCs e Pokémon ambientes escondidos por uma flag de evento; ficam só o elenco da missão. **Portas trancadas (V19, sugestão do autor):** toda porta de prédio da cidade recusa o jogador (“trancada — ordens da Líder de Ginásio”), **menos a do Pokémon Center**, que precisa continuar aberta para cura e para o retorno do blackout. Mecanismo: tabela `sLockedTownDoors` em `src/field_control_avatar.c` (flag do evento, mapa, porta que fica aberta, script da fala); cada missão acrescenta **uma linha**. É o que impede o jogador de achar o Líder de Ginásio lá dentro enquanto ele luta na rua. Entradas de caverna (Dragon's Den, Ice Path, Valor Cavern) e gates de rota com porta não animada (o da Route 43 em Mahogany) não passam pela trava e continuam abertos — `MetatileBehavior_IsWarpDoor` só aceita a porta animada. **Implementado na M1, na M2 e na M3; M4 pendente.** Onde a cidade não tem Ginásio, o bilhete é de quem de fato evacuou — em Cherrygrove, a Polícia Internacional.
- **Padrão do Necrozma (V19, decisão do autor — vale para todas as missões).** Toda missão tem o Necrozma em cena. As Ultra Beasts atravessam a ruptura **que ele abre**; ele não luta contra ninguém e nenhum golpe o afeta. Depois da vitória do jogador ele **absorve as Ultra Beasts da missão** — a derrotada e a do acompanhante — e vai embora pela mesma luz. Os personagens **reagem espantados** às ações dele, cada um na própria voz (na M1: Clair não acredita, Looker registra, Gladion diz o que viu — “ele se alimentou delas” —, Anabel diz que nenhum Ultra Beast age assim). **Ninguém o nomeia** até a reunião de Olivine/altar: para Johto é “a criatura feita de luz”; na M1 o Gladion só admite ter visto “uma luz assim, em Alola”, e corta o assunto. Na M2 ele **chega** na cena (não está parado na rua como na M1): a Lillie tinha visto "primeiro uma luz, depois a fenda" nas noites anteriores; Looker e Anabel o reconhecem de Blackthorn e a Anabel conclui que é ele quem abre as fendas; a Lillie **reconhece** a luz de Alola (continuidade USUM) e, como o Gladion, corta o assunto ("Later. I promise."). O padrão é o fio que liga as quatro missões ao clímax: o que ele leva em cada cidade explica por que o grupo precisa ir atrás dele. Na M3 ele **sobe do mar** numa baía que ficou lisa, rasga a fenda sobre a água e, pela primeira vez, **ataca uma pessoa**: depois de as duas UBs falharem, ele vira para o jogador — e a Anabel entra na frente (§6.3). **Implementado na M1, na M2 e na M3; M4 pendente** (precisa de um objeto de Necrozma, do orçamento medido e de um ponto de absorção depois da batalha).
- **Reação opcional à família Cosmog (V19).** Com Cosmog, Cosmoem, Solgaleo ou Lunala (não ovo) na equipe, o Necrozma reage: com Cosmog/Cosmoem ele encara a Poké Ball e o Pokémon treme; com Solgaleo/Lunala a luz se acende entre os dois e ele recua. Os NPCs comentam depois. É opcional: sem a família na equipe a cena corre sem nenhuma falta. Detecção pelo special `CheckMysteryEggPokemon`, checado **depois** da batalha (a batalha pode evoluir o Pokémon). Base para o clímax: é o parceiro do Mystery Egg que abre a passagem até o Necrozma (§8).
- **Gancho sem destino (V19).** O fim de uma missão **não diz onde é a próxima**: “vamos continuar monitorando; volte a Olivine e a gente avisa quando acontecer”. O destino é revelado no briefing, ao voltar ao escritório. **M1, M2 e M3 cumprem.** O gancho da M3 deixou de citar New Bark, as três assinaturas e a Lusamine; quem revela os três é o `Text_BriefingM4`, que já estava escrito assim. Só a M4 fecha a cadeia e não precisa de gancho de missão.
- **Acompanhante é surpresa (V19).** O briefing não anuncia quem vai estar no local. Na M1 o Looker não fala do Gladion; ele aparece no meio da cena. Na M2 a Lillie já está na cidade quando o jogador chega — a surpresa é **encontrá-la** (fala de espanto dela), e nem o briefing nem o "vá na frente" da Anabel a citam. **A M3 é uma exceção registrada pelo autor (V21):** o Kukui é nomeado no briefing de propósito, porque foi **ele quem ligou** para o Looker. A surpresa da missão não é ele estar lá — é **o que ele é**: o briefing monta uma ficha de duas páginas ("Pokémon move research, no combat authorisation") e a cena a desmonta quando ele solta um Incineroar e conta que fundou a Liga de Alola. A regra passa a ler-se: *o briefing não entrega a surpresa*; se o acompanhante for anunciado, a surpresa tem de ser outra coisa, e o briefing tem de plantar o engano que ela desfaz. M4 pendente.
- **Sinergia entre as Ultra Beasts (V20, pedido do autor — padrão dos próximos encontros).** As UBs de uma missão não são dois chefes soltos: existe uma **relação entre elas** que as torna mais perigosas juntas, e a cena a **mostra** (movimento + flash) antes de alguém explicá-la. A estratégia do grupo existe para quebrar essa relação, e é o acompanhante quem a enxerga. Na M2: Xurkitree drena a corrente, Celesteela a queima e devolve; na primeira vitória a parceira **revive** a derrotada; a Lillie entende e pede ao Pryce uma parede de gelo entre as duas ("ice doesn't carry current"), e só então a vitória é de verdade — a sinergia do grupo (Lillie + Pryce) vence a sinergia delas. Na M3 (V21) a relação é **espacial e tem consequência visual**: a Blacephalon apaga a baía inteira com as luzes e, quando a tela volta, o Stakataka **já está mais perto** — ele não anda, e por isso ninguém o vê andar. A cena mostra isso duas vezes, a segunda colada no jogador, e corrige na cara do especialista a hipótese que ele tinha trazido ("It isn't walking in behind the lights. It isn't walking at all."). A contramedida é a própria estrutura escolha + boss, agora com motivo interno: **quem está sendo olhado não pode se esconder**. Na M4 (V22) a relação é **temporal e é a mais literal das três**: Kartana, Guzzlord e Nihilego derivam um tile no **mesmo instante**, de três pontos do mapa que não se enxergam, duas vezes — e quem percebe é o Elm, porque é o único na rua com um relógio. A Anabel nomeia ("one thing wearing three bodies"), e a contramedida é **simultaneidade**: quebre uma e as outras duas a carregam, então têm de cair todas no mesmo instante. Isso obriga quatro treinadores para três alvos, e é o que põe o Gold/Crystal na linha. **E é uma armadilha:** a mesma formação, usada dez segundos depois contra o que a criatura vira, não faz absolutamente nada — porque a sinergia nunca foi delas.

**Forma da regra, a partir da V21** — em todo encontro daqui para a frente a sinergia precisa de três coisas: (a) ser **mostrada** com movimento/flash antes de qualquer explicação; (b) ter **consequência mecânica ou visual** que o jogador sinta (a M2 revive a derrotada; a M3 teleporta a pesada para o lado do jogador); (c) ter uma **contramedida que o acompanhante enxerga** e que justifique como o grupo se divide. Cada missão escolhe sua forma; não é obrigatório repetir as duas rodadas da M2. **M2, M3 e M4 cumprem; a M1 é anterior à regra.**

**Acréscimo da V22, e ele fecha o arco:** a sinergia das Ultra Beasts **não era
delas**. A criatura estava sincronizando as nove desde Blackthorn, e é por isso
que ela aparece no fim de toda missão para levá-las. A M4 é onde isso é dito em
voz alta (§6.4, "a conta de nove"), e a partir dela a sinergia deixa de ser um
tema de encenação e passa a ser **a pista principal da investigação**. Quem
escrever um encontro novo de Ultra Beast depois da M4 tem de decidir de que lado
dessa revelação ele está.
- **Líder de Ginásio local (M1, M2).** Onde a cidade tem Ginásio, o Líder é quem chamou a polícia, evacuou a cidade e **tenta** atingir o Necrozma sem efeito (Clair e Kingdra; Pryce e Mamoswine). É a "autoridade local que tenta e falha" da skill `evoluir-historia-de-evento`, e justifica a evacuação sem exposição.
  **Onde não há Ginásio (V21).** Cherrygrove não tem Líder, e a M3 **não inventou um**: o papel foi dividido em dois. Quem chamou a polícia e ficou de plantão foi o Kukui — que tenta e **acerta**, e por isso é a surpresa em vez do fracasso —, e o preço que a cena precisava cobrar de alguém foi cobrado da Anabel, que entra na frente do jogador. A regra geral vira: **alguém local tem de ter agido antes de o jogador chegar**; se não houver autoridade, o custo da escalada recai sobre o elenco fixo.
- A cena é 100% scriptada a partir da confirmação do jogador na primeira conversa com Looker.
- Progresso em uma única var (`VAR_RIFT_MISSIONS_STATE`, numeração continua a partir do doc de Blackthorn). Cada missão ocupa **três valores**: briefing pendente → incidente ativo → resolvido. Missão 1 = 2/3/4, Missão 2 = 4/5/6, e assim por diante, com o valor "resolvido" de uma servindo de "briefing pendente" da seguinte.
- Cada missão ganha **uma** flag persistente própria, só para esvaziar a cidade (o campo `flag` do `map.json` não lê var), com a invariante flag setada ⇔ var no valor "ativo". Flag de batalha (`FLAG_NO_CATCHING`) é compartilhada por todas.
- **Dificuldade crescente (V15).** A Missão 1 continua sendo a mais fácil da escala, mesmo depois de endurecida na V19: é onde o jogador aprende que perder para uma Ultra Beast custa blackout. As missões seguintes sobem de patamar em barras de vida, nível, multiplicador de status, moveset curado e item segurado. Referência fixada: M1 = **3 barras / Lv75 / x120 / moveset curado + item** (V19: o autor pediu uma luta mais difícil; antes era 2 barras / Lv70 / x110 / golpes de nível); M2 = 4 barras / Lv80 / x130 / moveset curado + item (**V20:** precedida de uma rodada curta de 2 barras contra a mesma UB, com cura da Anabel entre as duas — a rodada 2 é quem carrega o número da escala); **M3 = 4 barras / Lv85 / x140 / moveset curado com um golpe de controle por chefe + item**; **M4 = 4 barras / Lv90 / x150 / moveset de dois eixos (preparo + controle) + item**. A partir da M2 as barras estão no teto da engine (`MAX_BOSS_HEALTH_BARS 4`), então a escalada passa a vir de nível, multiplicador e **qualidade do moveset** — não de mais barras.


  **Ressalva da V17.** x140 (M3) nunca foi jogado, e o doc da M3 o registra como possível parede. O x150 da M4 é portanto um **alvo condicional**: se o runtime da M3 mostrar que x140 já é parede, a M4 herda o número corrigido em vez de continuar subindo. Nenhuma missão se balanceia por cima de um número não testado abaixo dela.
- Missão final com três Ultra Beasts: o jogador escolhe uma; **Lusamine e Anabel** ficam com as outras duas (decisão do autor). Looker não batalha. A distribuição deixou de ser detalhe do doc: a V17 a fixou em §6.4, porque qual UB sobra para Lusamine é uma decisão de personagem, não de conveniência.
- **A cadeia de estados termina na M4.** A regra de que o valor "resolvido" de uma missão é o "briefing pendente" da seguinte vale de M1 a M4 (2/3/4, 4/5/6, 6/7/8, 8/9/10). O valor 10 não abre missão nenhuma: significa *quatro missões concluídas, reunião de Olivine pendente*, e é de onde o §7 continua.
- **Flash de ruptura é `fadescreenswapbuffers`, nunca `fadescreen` (V23, bug de runtime).** As quatro missões são cenas noturnas cheias de flashes, e `fadescreen` **escurece a cena de verdade a cada flash**: ao apagar ele copia `gPlttBufferFaded` por cima de `gPlttBufferUnfaded` (`FadeScreen`, `src/field_weather.c`) e o `FADE_FROM_*` seguinte reaplica o tint de horário por cima de paletas já tintadas. À noite o tint é ~0,46 (`gTimeOfDayBlend`, `coeff = 10`), então oito flashes deixam a cidade preta — foi o que o autor viu na M3. `fadescreenswapbuffers` faz o mesmo efeito com BLDY no hardware e não encosta em paleta. `fadescreen` fica **só** onde um warp recarrega o mapa logo depois (retry do blackout, gancho). **Corrigido nas quatro missões.**
- **Trilha própria durante a ruptura (V23, pedido do autor).** O tema da cidade tocando enquanto o Necrozma rasga o céu estraga a cena ("fica bizarra a música feliz"). Receita: `fadeoutbgm 4` quando alguém percebe (silêncio no tremor), `playbgm MUS_DP_LEGEND_APPEARS, TRUE` quando a criatura aparece, `fadedefaultbgm` no pós-cena. O `TRUE` grava em `savedMusic`, e é o que faz a batalha de boss devolver a trilha certa ao voltar; carregar mapa limpa o `savedMusic` sozinho, então o retry começa limpo. A trilha é a mesma em todas as missões — ela é **do Necrozma**, não da cidade. **Implementada na M3; M1, M2 e M4 pendentes.**

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

Decidido na V15; implementação detalhada em [`.claude/rift_missions/MAHOGANY_ULTRABEAST/MAHOGANY_ULTRABEAST_IMPLEMENTATION.md`](MAHOGANY_ULTRABEAST/MAHOGANY_ULTRABEAST_IMPLEMENTATION.md).

**Ocorrência.** Mahogany Town está sem energia há três noites. O briefing (V20)
revela a cidade, o apagão e a ligação do Pryce ("Lights out. Come now.") — e
mais nada: nem a Lillie, nem a evacuação, nem a criatura de Blackthorn ("no sign
of the light from Blackthorn. Not yet." é a promessa que a cena quebra).

**Elenco e função (V20).**
- **Lillie** (+ Alolan Ninetales, §3.2) chegou dois dias antes de todos e não
  saiu. O jogador **a descobre** ao chegar. É a autoridade técnica da cena.
- **Pryce** (+ Mamoswine), Líder de Ginásio: levou cada família para o próprio
  Ginásio e está terminando isso quando a cena começa; é ele quem diz que
  evacuou. Tenta atingir o Necrozma (Blizzard, sem efeito), empresta o gelo para o
  plano da Lillie e, no fim, volta para o Ginásio para dizer ao povo que acabou.
  Voz: seco, paciente, fala em inverno ("I've stood in the cold for fifty years").
- **Looker** conduz, apresenta a Lillie ao jogador com humor, duvida da conclusão
  dela e, terminada a luta, pergunta primeiro se alguém se feriu.
- **Anabel** confirma a leitura pelos instrumentos, conclui que o Necrozma é quem
  abre as fendas e **cura o time do jogador** entre as duas rodadas.

**O que Lillie revela, e o que ela aprende.** Antes do SIM: duas UBs, mesma
fenda, mesma hora; "primeiro uma luz, depois a fenda, depois elas"; uma drena a
corrente, a outra a queima e devolve — um circuito fechado. O Looker duvida
("muita coisa a concluir de um caderno"), ela **sustenta** com as noites de
anotação, a Anabel confirma. O plano dela é **separá-las** (a escolha + boss). A
cena prova que não basta: vencida, a UB do jogador é **revivida** pela parceira.
A Lillie **admite o erro diante do grupo** e refaz o plano — o gelo não conduz
corrente; Ninetales e o Mamoswine do Pryce erguem uma parede entre as duas — e a
segunda vitória é de verdade. É o tema da missão (§3.2) levado um passo além:
observar, explicar, sustentar **e corrigir**.

**Anabel.** Uma única linha planta sua condição de Faller — ela sente a ruptura
antes de os instrumentos se moverem e corta o assunto ("Never mind. Later.").

**Necrozma.** Chega na cena numa luz, é reconhecido por Looker e Anabel ("the
creature from Blackthorn"), abre a fenda, ignora o Blizzard e, depois da segunda
vitória, absorve as duas UBs. A Lillie o **reconhece** de Alola ("I know that
light"; "It's feeding. The same way it did before.") e promete contar tudo
"not in the middle of the street". Ninguém o nomeia.

**Chefes.** Duas rodadas contra a UB escolhida: rodada 1 = 2 barras / Lv80 / x130;
rodada 2 = 4 barras / Lv80 / x130 (o degrau da escala). Xurkitree com Tail Glow +
Magnet, Celesteela com cobertura física/especial + Leftovers. Captura bloqueada
nas duas; derrota ou desistência em qualquer uma = blackout no Centro de
Mahogany e retry da cena inteira, com a escolha refeita.

**Gancho (V20, sem destino).** As luzes voltam; o Pryce elogia a Lillie e entra
no Ginásio; a Anabel pede as anotações dela; a Lillie fica mais uns dias "in case
it comes back"; Looker: "Rest, then come back to our house in Olivine. The moment
something opens, you will be the first to know." A Lillie agradece por terem
ouvido os dois planos dela — "even the wrong one". Cherrygrove e Kukui só
aparecem no briefing da M3.

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

### 6.3. Missão 3 — Cherrygrove (Necrozma, Blacephalon + Stakataka / Kukui) — conteúdo fechado

Decidido na V16, **evoluído para história na V21**; implementação detalhada em
[`.claude/rift_missions/CHERRYGROVE_ULTRABEAST/CHERRYGROVE_ULTRABEAST_IMPLEMENTATION.md`](CHERRYGROVE_ULTRABEAST/CHERRYGROVE_ULTRABEAST_IMPLEMENTATION.md)
(§13 tem a tabela *pedido → como ficou*).

**Ocorrência.** A ruptura de Cherrygrove não abre em terra: abre **sobre o mar**,
na frente da praia noroeste, e vem se abrindo e fechando num ritmo há quatro
dias. Kukui não sai da praia porque a abertura é intermitente e alguém precisa
estar olhando quando acontecer.

**Quem avisou (V21, pedido do autor).** Não foi um Líder de Ginásio nem uma
patrulha: foi o **Kukui**, por telefone, quatro dias antes. Ele deu janela,
direção e maré, ligou de volta e **corrigiu a janela — duas vezes, certo as
duas**. O briefing em Olivine é a cena em que Looker e Anabel tentam entender de
onde veio um relatório tão bom e leem em voz alta a ficha de duas páginas do
homem que o mandou: *"Professor Kukui. Pokémon move research."* Sem registro de
força, sem autorização de combate. Os dois concluem que há um civil sentado
embaixo de um céu aberto e mandam o jogador buscá-lo. **É um engano de
propósito, e é o que a praia desmonta.**

**Elenco e função.** Looker conduz e recebe o relatório; Anabel cuidou da
evacuação (a cidade foi levada para o Ginásio de Violet) e é ela quem trancou as
portas; Kukui é a autoridade técnica da cena — e muito mais que isso. **Kukui
chega sem Pokémon fora da Poké Ball**, como a regra visual de §3.2 exige, e
**solta um Incineroar no meio da luta**, o que a mesma regra permite (precisão
da V21).

**Evacuação e portas.** Cherrygrove esvazia **por completo**, incluindo o
Friendly Trader e os dois Pokémon que ele oferece de presente, e todas as portas
de prédio recusam o jogador menos a do Pokémon Center. Como não há Líder, o
bilhete é da Polícia Internacional.

**A sinergia, que é o tema da missão.** As duas Ultra Beasts trabalham em par, e
a coordenação é a arma delas — mas **não** do jeito que o Kukui achava. A
hipótese dele, contada antes da cena, é que a Blacephalon distrai e o Stakataka
**anda** por trás. O que a cena mostra é outra coisa: a Blacephalon apaga a baía
inteira e, quando a vista volta, o Stakataka **já está mais perto**. Ele não
anda. A cena repete o truque duas vezes, a segunda deixando o Stakataka a um
tile do jogador, e o especialista se corrige em voz alta: *"It isn't walking in
behind the lights. It isn't walking at all."* A contramedida é a estrutura
padrão escolha + boss, agora com motivo interno: **quem está sendo olhado não
pode se esconder.**

**A surpresa: o Fundador da Liga (V21, pedido do autor).** Com o Stakataka em
cima do jogador, o civil de jaleco solta um Incineroar, tira a criatura dali e
responde à ficha de duas páginas: ninguém em Alola escreve relatório sobre o
cara que **construiu a Liga** — e, por um tempo, foi ele quem ficava no fim
dela. A Anabel pede desculpa pela ficha. Ele **não** é treinador batalhável: a
luta dele continua narrativa, como a do Gladion e a da Lillie.

**O Necrozma ataca uma pessoa.** Depois que as duas UBs falham, ele vira para o
**jogador**. É a primeira vez no arco que ele mira alguém.

**Anabel (V21).** Esta é a missão em que a condição dela vem a público, e as
duas metades estão aqui: ela **sente a ruptura antes do instrumento** ("It's
here." / "There is nothing on the meter." / "I know.") e, mais tarde, **entra na
frente do jogador** e leva a luz. De joelho na areia molhada, em cinco caixas,
ela diz o que é e por que sentiu, corta o assunto ("The rest of it later") e
volta ao comando na frase seguinte. O resto — o que ela lembra, a mão, a
promessa — continua sendo a cena de New Bark (§6.4). A segunda semente que a
V16 tinha reservado para cá **deixa de existir**: ela virou o pagamento.

**Chefes.** Terceiro degrau da escala crescente: 4 barras (teto da engine),
nível 85, multiplicador 140 e, principalmente, **um golpe de controle em cada
chefe** — Blacephalon com Calm Mind (+ Wise Glasses), Stakataka com Trick Room
(+ Weakness Policy). Captura bloqueada; derrota ou desistência = blackout no
Centro de Cherrygrove e retry, com a escolha refeita. Nada disso mudou na V21.

**Consequência e presente.** Depois da vitória o Necrozma **absorve as duas** e
vai embora pela mesma luz; os três reagem, cada um na própria voz, e ninguém o
nomeia. Looker pergunta pelas pessoas antes do relatório. O presente da missão
**não é um item**: é o fundador de uma Liga convidando um Campeão a ir até o fim
dela.

**Gancho.** **Sem destino** (V21): "the readings haven't settled… where, and
when, we don't know yet. Come back to our house in Olivine; the moment something
opens, you will be the first to know." Duas linhas do bloco são ganchos da M4 e
não são enfeite: Looker tirando o Kukui da praia à força para comer alguma coisa
(o briefing da M4 responde a isso) e a última caixa do Kukui.

> **Mudança da V22 (pedido do autor).** Essa última caixa dizia *"And I'm coming
> with"*, e era o que punha o Kukui em New Bark. **Ele não vai.** A caixa foi
> reescrita: ele vai para casa, mas antes passa a noite lendo todos os logs que
> ninguém achou que valessem a pena mandar, porque *"somebody out there has been
> writing this down for weeks and calling it a broken sensor"*. É isso que
> encontra as seis semanas do Elm e produz o telefonema para a polícia — a
> cadeia **Elm → Kukui → Looker** que abre a M4. Esta caixa e o
> `Text_BriefingM4` são **um par**: nunca editar um dos dois sozinho.

**O que a implementação da Missão 3 fixou.** Do esqueleto (20/09/2026), tudo que
continua valendo como contrato para a Missão 4:

- **`FLAG_EVENT_ULTRABEAST_CHERRYGROVE` = `0x1043`,** com `CUSTOM_FLAGS_END`
  movida para ela. Numeração confirmada: M3 = 6/7/8, e a M4 começa em 8.
- **Evacuar objeto de flag alheia tem caminho aprovado e caminho proibido.**
  Aprovado: trocar o campo `flag` do template por um cache temporário
  recalculado no load e acrescentar o `setflag` persistente explícito que o
  `removeobject` fazia por efeito colateral. Proibido: `removeobject` em objeto
  de moradia. É hoje o maior risco de **regressão silenciosa** do projeto.
- **A leitura de mapa deste repo não é a do `pokeemerald`,** e a diferença é
  silenciosa. §12.7 do doc da M3 tem a tabela e as duas conferências baratas, e
  é **leitura obrigatória** antes de medir qualquer cena nova. Em cena de costa,
  ler colisão **e** comportamento: água rasa tem colisão 0 e o jogador anda nela.
- **Nenhum `goto_if_ge VAR_RIFT_MISSIONS_STATE` novo em Olivine sem checagem.**

E o que a revisão 3 (V21) acrescentou como contrato:

- **Objeto escondido por cena tem flag temporária PRÓPRIA.** Necrozma e
  Incineroar usam `FLAG_TEMP_5` e `FLAG_TEMP_6`, e não a das UBs, porque
  `removeobject` seta a flag do template. Três `setflag` incondicionais no
  `ON_TRANSITION` são o que faz o retry depois de blackout começar limpo de graça.
- **`setobjectxy` sob `FADE_TO_WHITE` é mecânica, não conveniência** — e é o
  ponto de maior risco de runtime da missão, com plano B escrito (andar com o
  objeto de tela branca).
- **Pares de texto que não podem ser mexidos de um lado só:** a ficha de duas
  páginas ↔ a revelação do Kukui; o gancho ↔ o `Text_BriefingM4`; a revelação da
  Anabel em Cherrygrove ↔ a cena dela em New Bark.

### 6.4. Missão 4 — New Bark (Kartana + Guzzlord + Nihilego / Lusamine) — conteúdo fechado

Decidido na V17, implementado em esqueleto em 20/09/2026 e **evoluído para
história na V22**; implementação detalhada em
[`NEWBARK_ULTRABEAST_IMPLEMENTATION.md`](NEWBARK_ULTRABEAST/NEWBARK_ULTRABEAST_IMPLEMENTATION.md),
cujo **§13 é a verdade** (e vence o §12, que vence o resto daquele arquivo).
Build limpo; runtime pendente.

**O que muda de tamanho.** As três primeiras missões são a mesma peça em três
cidades. A quarta mantém a estrutura — ela é o contrato do arco — e muda tudo em
volta: é **New Bark**, a cidade onde o jogador começou e a única do arco sem
Centro Pokémon e sem Ginásio; são **três** Ultra Beasts; é a primeira cidade que
**não quer evacuar**; entram três personagens que o jogador conhece desde a
primeira hora de jogo (**Elm**, **a mãe** e **Gold/Crystal**); e é o primeiro
encontro cara a cara com a **Lusamine**. Consequência de escrita: é a única
missão em que o design autoriza gastar mais caixas de texto que as outras,
respeitadas as regras de §3.3.

**E é a missão que se perde.** Este é o ponto da V22 e tudo o mais se subordina
a ele: a cidade fica de pé, ninguém se machuca, nenhuma janela quebra — e a
criatura leva o que veio buscar e vai embora. Ver "Resolução" abaixo.

**Quem avisou (V22).** A cadeia é **Elm → Kukui → Looker**. O Elm tinha seis
semanas da mesma leitura anômala e escreveu "check the sensor" na margem toda
vez; quando Cherrygrove saiu no jornal, ele mandou o log inteiro para o único
homem do mundo que não riria dele, e esse homem telefonou para a polícia antes
de terminar de ler. **O Kukui não vai a New Bark** — ele fez a coisa que só ele
podia fazer, que era reconhecer, e entregou. Quem fica dentro da análise é o
Elm: é o instrumento dele, as seis semanas dele e a cidade dele.

**O briefing de Olivine é onde a Anabel conta o que é ser uma Faller (V22).**
Pedido do autor: essa conversa não cabe no meio de uma luta. Três rupturas
abrindo **juntas** são a primeira coisa que ela já sentiu de outra cidade — de
uma cadeira em Olivine —, e é isso que a faz parar o relatório, pedir a cadeira
e contar tudo, com tempo. Em campo sobram duas caixas de custo físico, e uma
única caixa de retomada no rescaldo. Detalhe em §3.1.

**A Lusamine não é anunciada (V22).** Nenhuma menção a ela no escritório.
Ninguém a mandou vir: ela leu os mesmos números e entrou num barco. O jogador a
encontra sozinha na estrada de entrada, e é a primeira fala dela no arco
inteiro. Pôr o nome dela no briefing gastaria a única surpresa que a missão tem
antes da criatura.

**Ocorrência.** Três rupturas abrem sobre New Bark ao mesmo tempo, em terra —
não há mar envolvido. O laboratório do Elm registra a anomalia há semanas e ele
a arquivou como defeito de instrumento; é um erro humilde e inteiramente dele,
que ele admite sem que ninguém cobre. É ele o cronômetro da cena.

**A sinergia, que é o tema da missão (V22).** As três **não se comportam como
três**: derivam um tile no **mesmo instante**, de três pontos do mapa que não se
enxergam, duas vezes. Quem percebe é o Elm, porque é o único na rua com um
relógio — e a Anabel nomeia: *"stop counting them as three; that is one thing
wearing three bodies, and it has been doing it since Blackthorn"*. A Lusamine
fecha o beat admitindo que **em Alola elas nunca fizeram isso**.

O contra-ataque que isso obriga é o que dá motivo interno à estrutura padrão:
quebre uma e as outras duas carregam; quebre duas e a terceira carrega as duas;
**têm de cair no mesmo instante ou não caem**. Logo a Lusamine não pode ficar
com as três, e a que o jogador pegar não cai para um treinador só.

**Elenco e função.** Looker conduz, cuida das pessoas antes do relatório e
ampara a Anabel; **não batalha**. Anabel comanda, oscila uma vez e entrega o
contra-ataque. Lusamine é a autoridade técnica **e** o nó da cena. Elm é o
cronômetro e o abrigo. A mãe do jogador recusa o abrigo e é quem desfaz o nó.
Gold ou Crystal — conforme o gênero do jogador — faz a evacuação porta a porta,
pede para lutar, **ouve não, e é posto na linha assim mesmo pela Lusamine**. A
regra visual de §3.2 não é flexibilizada: Lusamine não ganha parceiro fora da
Poké Ball; o parceiro do Gold/Crystal não é exceção, é o que já existe no mapa
desde o começo do jogo — **e nesse ponto da história já é um Azumarill** (V22).

**O que Lusamine revela, se o jogador trouxer o Pokémon.** A razão de o ponto
fraco ser justamente New Bark é que o parceiro da família de Cosmog que o jogador
criou desde Violet **brilha**, e ela é a única pessoa viva que sabe como aquilo
se parece do outro lado — porque um dia usou um Cosmog exatamente assim. Ela
conta isso sem que ninguém pergunte. Regra inegociável: **isso não é culpa do
jogador, e a cena não pode sugerir que seja.** Quem diz isso em voz alta é ela,
na mesma cena.

> **Precisão da V22.** Essa revelação é **opcional e sem estado**: sai da
> checagem `CheckMysteryEggPokemon`, não grava flag nem var persistente, não
> bloqueia nada, e sem o Pokémon a cena corre idêntica. Continua verdade que a
> **única verificação de equipe do arco** é a do §7.

**O nó da cena.** A Nihilego quebra a formação e vem em cima do jogador e da mãe
dele, e é isso que faz a Lusamine anunciar que fica com as três. Não é bravata —
é a conduta dela de sempre (§3), agora com um argumento que soa bom. **Quem a faz
parar é a mãe do jogador**, não Looker, não Anabel, não o jogador: mãe para mãe,
sem sermão, em poucas caixas. A mãe não sabe nada de Ultra Beasts e não precisa
saber; ela reconhece a coisa que está vendo porque é a mesma que ela faria.

**A lição da mãe, e o que ela produz (V22).** Ela não ganha a discussão por
argumento: conta como é acreditar em alguém **de dentro**, e tem exatamente um
exemplo — a manhã em que ficou na porta e deixou uma criança de dez anos andar
até Cherrygrove sozinha. *"Believing in somebody is worse than doing it
yourself. It just happens to be the thing that works."* É o único momento do arco
em que alguém de fora da investigação tem razão contra um especialista.

E a lição **vira ação na cena seguinte**: quando Looker e Anabel recusam o
Gold/Crystal, quem derruba a recusa é a **Lusamine**, trinta segundos depois de
ouvir aquilo. *"I have spent my life deciding who was ready. I was told, four
minutes ago, what that actually is."* Depois disso ela faz o que não faz desde
Alola: **pergunta** — à Anabel o que os instrumentos dizem, e ao jogador qual das
três ele vai enfrentar. **Essa pergunta é o menu de escolha.**

**Distribuição das três.** **Lusamine fica com Nihilego sempre que o jogador não
a escolher**; a Anabel fica com a que sobrar; **o Gold/Crystal vai junto com o
jogador** (V22). Não é importar a fusão de Sun/Moon (§3 proíbe): é
responsabilidade e limite de pesquisa. Se o jogador escolher Nihilego, ela tem
**uma** linha reconhecendo a perda do gesto, e aceita. São quatro pessoas para
três alvos, uma marca só, e as três falas de escolha dizem a divisão inteira em
voz alta.

**O Gold/Crystal não vira parceiro de batalha.** A regra da V17 continua valendo
e a V22 não a quebra: ele **não** tem batalha de treinador, **não** recebe um
quarto alvo e **não** dilui a escolha, que continua sendo entre três. Ele entra
na mesma Ultra Beast que o jogador.

**Chefes.** Quarto degrau da escala: 4 barras (teto), nível 90, multiplicador 150
e moveset de dois eixos — preparo e controle — com item, respeitada a ressalva
condicional de §6. As três precisam ser distinguíveis na prática, não só no
texto: uma que sobe, uma que aguenta, uma que atrapalha. Captura bloqueada.
**Nada disso mudou na V22.**

**Derrota e retry.** New Bark não tem Centro Pokémon, e isso acabou sendo uma
vantagem: o ponto de recuperação da cidade é a **porta de casa do jogador**, que
é também o tile de fala, e a engine cura a equipe sozinha. Perder devolve o
jogador curado exatamente onde a cena começa. Sem flag nova; a escolha é refeita
a cada tentativa.

**Resolução — a missão que se perde (V22, pedido do autor).** A vitória do
jogador derruba as três **no mesmo segundo**, e o plano funciona. E então a
criatura das outras três missões **sai do próprio asfalto** no meio da rua — não
desce do céu, usa a estrada, e o Elm é quem nota. O Gold/Crystal a ataca sozinho,
porque acabou de ser admitido, e é jogado de volta sem que ela bloqueie, desvie
ou faça coisa alguma. Ela **absorve as três de uma vez**, vira outra coisa, e os
quatro fazem exatamente o que funcionou dez segundos antes — mesma marca, mesmo
instante — e são postos no chão em um único golpe. Ela vai embora pelo mesmo
lugar.

**Nada quebra.** Nenhuma casa, nenhuma cerca, nenhuma janela, nenhuma pessoa. É
o que permite a leitura final: **nunca foi pela cidade.**

**A conta de nove (V22).** É a Anabel quem fecha, e é o que reenquadra o arco
inteiro: nove Ultra Beasts, quatro missões, e a criatura esteve em todas e saiu
de todas com todas. *"It was never attacking Johto. It was never attacking us at
all."* — "…It was collecting." — **"And we softened them for it. Four times."**
A Lusamine dá o nome da coisa sem nomear a criatura: *"I have been on the other
end of a plan like that. You do not notice it is a plan until it is finished."*
Ninguém em Johto a nomeia; o nome fica para a reunião.

**Custo pequeno e visível.** Os instrumentos do Elm não sobrevivem, e ele está
bem com isso porque os últimos trinta segundos de dado são **três assinaturas
virando uma**. Gold/Crystal diz o que o protagonista mudo não pode dizer — "I
finally got in, and it didn't even turn its head" — e quem responde é a
**Lusamine**, não o jogador: nem o dela virou a cabeça, nem o da Campeã. A mãe
fecha com uma caixa, sem abraço encenado.

**Gancho — todo mundo em Olivine.** Precisa fazer três coisas e nada além:
(1) Anabel diz o que as três rupturas tiveram de diferente — fecharam **na
direção em que a coisa saiu**, e é isso que torna o altar localizável: a
investigação acabou e o que vem é expedição; (2) **Lusamine pede a reunião e pede
que chamem os filhos** — Lillie, Gladion e Kukui, nomeados por ela, não como
Aether mas como alguém que deve uma explicação, e duas dessas pessoas são dela;
o Kukui é nomeado com o reconhecimento de que ganhou a sala **sem nunca ter posto
o pé nela**; Looker acrescenta Anabel e ele mesmo, fechando **seis pessoas e o
jogador**; (3) Looker manda o jogador **trazer o parceiro** — como convite ao
Pokémon, nunca como requisito.

**Estado.** M4 = 8/9/10, com uma flag persistente própria só para esvaziar a
cidade e a invariante de sempre (flag setada ⇔ var no valor "ativo"). O valor 10
não abre missão nenhuma: é *quatro missões concluídas, reunião pendente*, e é de
onde o §7 continua. **A V22 não mexeu em nada disso.**

**O que esta missão não faz.** Não exige Solgaleo nem Lunala e não bloqueia nada
pela família de Cosmog — a única verificação de time do arco continua sendo a do
§7. Não gasta a batalha da Lusamine contra o jogador (§3, §9) **nem a batalha
contra Ultra Necrozma** (§9): a derrota aqui é encenada, não jogada. Não resolve
a reconciliação familiar: Lillie e Gladion não estão aqui. Não importa a fusão
com Nihilego. Não machuca ninguém do elenco e não mata nenhuma Ultra Beast. E
**não culpa o jogador** — nem pelo brilho do Cosmog, nem por ter enfraquecido as
nove.

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

> **Consequência da V22.** A Missão 4 termina em **derrota**: a criatura absorve
> as três Ultra Beasts, vira outra coisa, derruba os quatro treinadores num golpe
> e vai embora com o que veio buscar. O arquivo fecha com algo pior do que o
> motivo de tê-lo aberto, e a reunião não é uma comemoração de "quatro em
> quatro" — é a sala onde se descobre que **as nove Ultra Beasts do arco foram
> coletadas, e que a investigação as enfraqueceu para quem as coletou**. O
> `Text_ReunionOpen` do PRÉ-NECROZMA já foi ajustado numa caixa para reconhecer
> isso; quem evoluir aquele evento deve ler o §5.7 do doc da M4 antes.
> Uma consequência prática: **é aqui que a criatura finalmente ganha nome.** Em
> Johto ninguém a nomeia em nenhuma das quatro missões.

**Estado e escopo do evento (V18) — PRÉ-NECROZMA.** Esta cena passa a ser um
evento próprio, com nome e documento: **PRÉ-NECROZMA**, plano técnico em
[`PRE_NECROZMA_ULTRABEAST_IMPLEMENTATION.md`](PRE_NECROZMA_ULTRABEAST/PRE_NECROZMA_ULTRABEAST_IMPLEMENTATION.md)
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

**Estado do evento (V24) — ALTAR DO SOL E DA LUA.** O clímax do arco passa a ser
um evento próprio, com nome e documento: plano técnico em
[`ALTAR_SUN_MOON_IMPLEMENTATION.md`](ALTAR_SUN_MOON/ALTAR_SUN_MOON_IMPLEMENTATION.md)
(**planejado em 23/09/2026**, história completa já escrita no próprio plano,
nada implementado). Ele cobre do estado 12 ao 16 e é o **último** evento de
história do arco: o que vem depois dele é o loop do §10.

O terreno já existe no repositório e foi auditado ao escrever o plano:
`MAP_SUN_MOON_ALTAR` (30x30, com o elenco posicionado e a balsa funcionando nos
dois sentidos), `MAP_ULTRA_SPACE_ARENA` (21x21, sem objetos), o
`ITEM_SUN_MOON_TICKET` entregue na reunião, o `gTileset_AltarSunMoon` com um
**segundo estado de arte do disco** pronto para `setmetatile`, e a `MAPSEC`
já renomeada para "Altar of Sun and Moon".

**Os cinco atos, que são a estrutura fechada deste evento:**

| Ato | Estado | O que acontece |
| --- | --- | --- |
| I — a chegada | 12 → 13 | O disco já está girando. O instrumento do Kukui está sendo lido por outra coisa. O disco deixa de ser disco, cai cinza, e a **Lusamine se oferece para atravessar sozinha, por arrependimento**. Lillie argumenta, Gladion recusa. O Looker se retira: "isto não é assunto de polícia". **O jogador é solto no altar com a discussão aberta.** |
| II — o duelo | 13 → 14 | Falar com a Lusamine, `SIM`/`NÃO`. O `NÃO` não avança e é repetível. O `SIM` é o duelo narrativo do §9: sem blackout, quatro resultados, e **vitória e derrota resolvem a disputa** — quem fecha é a Lillie, nos dois ramos. |
| III — a fenda | 14 | O parceiro do jogador aparece como objeto ao lado do disco, e **uma fenda nasce no chão, no meio do pátio**. É o objeto que o loop vai reusar. |
| IV — Ultra Necrozma | 14 → 15 | A Anabel acompanha o jogador pela fenda. Boss battle de **cinco barras / Lv 90 / 160%**, com perfil de fases que **descasca** a criatura (Ultra → Ultra → Ultra → Necrozma → Necrozma). Captura bloqueada na luta e **roteirizada na cutscene**. O parceiro harmoniza a passagem. |
| V — a despedida | 15 → 16 | Conversa de encerramento com os sete. O altar volta ao sol/lua, mas **a fenda fica**. Looker e Anabel ficam com ela. |

**A resposta da criatura, que é a surpresa guardada para este evento:** ela
coletou nove Ultra Beasts em quatro cidades porque **estava com fome**. A luz é
comida, a armadura é o que ela comeu, e a hesitação diante de um Cosmog em New
Bark (V22) era reconhecimento, não cálculo. Nenhuma caixa das quatro missões, da
reunião ou do Ato I usa essa palavra.

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

> **O que a V22 entrega para cá.** A forma Ultra **já apareceu**, em New Bark, no
> fim da Missão 4, e já derrotou o jogador uma vez — de graça, numa cutscene, sem
> batalha e sem blackout. O confronto deste §9 é a **revanche**, e o roteiro pode
> contar com isso: o jogador sabe exatamente o que a coisa faz e sabe que a
> formação de quatro não foi suficiente. Também já está plantado que ela não age
> por agressão e sim por **coleta** — e, se o jogador levava um Cosmog/Solgaleo/
> Lunala, que foi a única coisa diante da qual ela **hesitou**. Nada disso muda o
> contrato de batalha abaixo.



Lusamine insiste em realizar a operação sozinha. A única batalha do jogador contra ela ocorre aqui como **duelo de personagem**, não como boss de ameaça: usar o contrato V12 sem blackout. Vitória e derrota recebem respostas próprias, mas ambas resolvem a disputa narrativa e levam Lusamine a aceitar a ajuda do grupo. O resultado não deve ser reescrito como vitória do jogador. O roteiro deve dar espaço à reação de Lillie e Gladion sem retirar do jogador o papel no confronto contra Necrozma.

O jogador então atravessa para enfrentar Ultra Necrozma em uma boss battle e obter Necrozma por captura. O tratamento da forma após a batalha precisa respeitar a implementação local: não presumir que Ultra Necrozma pode permanecer como forma de armazenamento. Também não está definido se a captura ocorre durante o combate ou em uma etapa posterior.

Ultra Necrozma é um **boss de ameaça**. Derrota pode usar blackout ou retorno seguro para um checkpoint e exige nova tentativa; fugir quando permitido ou derrotar sem capturar também não pode tornar Necrozma permanentemente indisponível.

> **Fechado na V24 — o mecanismo de retry e de captura.** A pendência acima
> tinha três perguntas e as três têm resposta:
>
> 1. **A captura é etapa posterior, não combate.** `B_FLAG_NO_CATCHING` está
>    ligada durante a boss battle e a captura é uma cutscene depois da vitória
>    (`givemon SPECIES_NECROZMA`, nível 75, forma normal). Isso torna "derrotar
>    sem capturar" **impossível por construção**, que é a única forma de
>    garantir o requisito acima sem inventar um estado de recuperação.
> 2. **A forma armazenada é `SPECIES_NECROZMA`.** A dúvida sobre a forma Ultra
>    some: o jogador recebe a criatura *depois* de ela perder a luz, o que
>    também é a melhor leitura narrativa disponível.
> 3. **O retry é de graça e não custa estado.** Perder dá blackout com o estado
>    ainda em 14; o `ON_TRANSITION` da arena esconde tudo a cada load, então a
>    cena volta ao começo sozinha. O único custo é a viagem de balsa, e o Looker
>    cura a equipe no altar para compensar.
>
> A checagem de espaço na equipe/PC é feita **na fenda, antes da travessia**, na
> voz da regra da Anabel (a mesma da Missão 1). Detalhes:
> [`ALTAR_SUN_MOON_IMPLEMENTATION.md`](ALTAR_SUN_MOON/ALTAR_SUN_MOON_IMPLEMENTATION.md) §7, §8 e §11.

Após a resolução, ocorre o evento de despedida. Looker e Anabel permanecem no altar.

> **Fechado na V24 — os destinos finais.** A pendência "Despedida" do §14 está
> resolvida, e a forma é uma **escala de dias da semana** (`GetDayOfWeek`, o
> mecanismo dos irmãos dos dias da semana de HGSS), não sorteio: sorteio faz o
> personagem piscar quando o jogador sai e volta do mapa.
>
> | Dia | Altar: Lusamine | Olivine: os cinco | Praia de Cherrygrove: Kukui | Praia: Lillie + Ninetales | Cianwood: Gladion + Silvally |
> | --- | --- | --- | --- | --- | --- |
> | Domingo | — | **sim** | — | — | — |
> | Segunda | **sim** | — | **sim** | — | — |
> | Terça | — | — | **sim** | **sim** | **sim** |
> | Quarta | **sim** | — | — | — | **sim** |
> | Quinta | — | — | **sim** | **sim** | — |
> | Sexta | — | **sim** | — | — | — |
> | Sábado | **sim** | — | **sim** | **sim** | **sim** |
>
> Regras que a tabela carrega: **ninguém está em dois lugares no mesmo dia**;
> **domingo e sexta são os dias da família** em Olivine e não têm revanche em
> lugar nenhum; **sábado é o dia cheio**. Onde há personagem há **uma revanche
> por dia**, por daily flag — revanche não é duelo narrativo, então perder é
> blackout comum. O Kukui volta ao laboratório em Alola e reaparece na praia; ele
> nunca volta à sala de Olivine.

## 10. Pós-Necrozma: expedições permanentes

As rupturas continuam surgindo depois da história, mas a passagem principal está mais estável sem a interferência de Ultra Necrozma. Looker e Anabel conduzem novas missões para fechar o máximo possível dessas conexões. Anabel também permanece por uma razão pessoal: como Faller, quer oferecer assistência a quem precisar, assim como recebeu ajuda quando chegou. Isso não altera a natureza conceitual dos destinos nem significa que todas as expedições encontrem pessoas.

Os destinos são realidades quebradas: fragmentos que materializam conceitos do universo. Não representam necessariamente outra dimensão completa ou um mundo habitado. Essa premissa permite espaços temáticos e encontros variados sem exigir uma nova região coerente para cada expedição.

End of Time e Legendary Nexus foram nomes de trabalho usados para esse conteúdo. Rift Missions é o nome de trabalho do sistema; o nome final de cada destino e do altar no mapa ainda pode ser definido.

> **O que a V24 entrega para cá, pronto.** O evento do altar deixa o loop com a
> porta já construída e um mapa já ligado:
>
> - **A fenda é um objeto** (`LOCALID_SUN_MOON_ALTAR_RIFT`, `OBJ_EVENT_GFX_PORTAL`,
>   em (14,10) no pátio do altar) que aparece **uma vez por dia**, por daily flag,
>   do estado 16 em diante. O script dela é o ponto de entrada do loop.
> - **`MAP_ULTRA_SPACE_ARENA` já existe e já devolve o jogador ao altar** pelos
>   três `coord_event` da borda sul. Hoje ela está vazia de propósito: uma caixa
>   de narração e nada mais. **Substituir aquele script é a primeira coisa que o
>   documento do loop faz.**
> - **A Anabel já vende Beast Balls ali** (`pokemart` de uma linha, preço de
>   catálogo 1500, estoque infinito) e **o Looker já cura a equipe**.
> - **Não há checagem de Solgaleo/Lunala na fenda diária.** Isso é decisão, não
>   esquecimento: no Ato IV o parceiro **harmoniza** a passagem, e é por isso que
>   ela deixa de precisar dele. Fecha a regra do §11 ("não exigir Solgaleo ou
>   Lunala novamente a cada expedição").
> - **`VAR_RIFT_MISSIONS_STATE` para em 16.** O valor 17 e os seguintes estão
>   livres, e é provável que o loop prefira uma var própria a continuar esta.
> - **Uma pergunta aberta para o doc do loop:** a arena é **um** mapa, e este §10
>   descreve destinos que são realidades quebradas **diferentes**. Se cada
>   expedição quiser mapa próprio, quem escolhe o destino é o script da fenda, e
>   a decisão é do doc do loop.

> **Regras do Nexus (25/09/2026):** o loop tem regras próprias do autor em
> [`nexus/NEXUS_REGRAS.md`](nexus/NEXUS_REGRAS.md) — modo Daily (4 treinadores
> escolhidos por teleporte + o campeão do lendário + boss), formato
> Traditional, level scaling no maior nível da equipe, pool condicionado à
> captura. Onde esta seção e aquele arquivo divergirem, **vale o arquivo**.

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

> **Atualização de 24/09/2026.** O altar e o sistema do Kurt foram **implementados** numa passada
> — [`ALTAR_SUN_MOON_IMPLEMENTATION.md`](ALTAR_SUN_MOON/ALTAR_SUN_MOON_IMPLEMENTATION.md) §17 e
> [`KURT_BALL_CRAFT_DESIGN.md`](../KURT_BALL_CRAFT_DESIGN.md) §8 trazem o retorno da escrita. As
> linhas **Altar**, **Necrozma**, **Despedida**, **Beast Balls**, **Solgaleo/Lunala** e
> **Poké Balls / Kurt** desta tabela saem de "a fechar" e passam a "no código, sem teste em
> runtime". `VAR_RIFT_MISSIONS_STATE` vai agora até **16**, e **17+ está livre** para o loop. O
> `UltraSpaceArena_EventScript_EmptyRift` é o único `@ SKELETON:` que sobra no arco: substituí-lo é
> a primeira coisa que o documento do loop faz.

| Tema | Detalhe pendente |
| --- | --- |
| Escritório | Definido: `OlivineCity_House1`, Looker (4,5) e Anabel (7,5), presentes desde o New Game. Estar em Olivine e na missão ao mesmo tempo é aceito (a missão é cutscene). **Fechado na V24:** os dois **saem** da sala no estado 16 e passam a morar no altar, e a sala vira o lugar da família em dois dias da semana. A venda de Beast Balls é da Anabel **no altar**, não em Olivine. |
| Campanha | Route 30, Goldenrod e Dragon’s Den da Lillie estão implementados e compilados; runtime/regressão ainda pendentes. Violet/Cianwood/Gladion seguem conforme seus próprios estados. Victory Road Gladion permanece pendente. |
| Lillie em Goldenrod | Implementada e compilada com Vulpix fora da Poké Ball. Preservar batalha/entrega existentes e validar em runtime a nova coreografia, especialmente possível sobreposição visual na saída. |
| Gladion em Cianwood | Preservar a implementação existente, mas remover a recusa e garantir batalha obrigatória com vitória/derrota sem blackout. |
| Lillie no Dragon’s Den | Implementação compilada concluída. Validar em runtime quiz, 15 reações, flags temporárias, Ninetales OW, battle outcomes, IA/Aurora Veil, Snow/recovery, Clair, Risingbadge e Dratini. |
| Gladion / Victory Road | Escolher gatilho/mapa seguro antes do acesso, criar estado de conclusão independente do vencedor e fechar equipe de cinco com Silvally lead. |
| Blackthorn | Esqueleto implementado e compilado em 19/09/2026; runtime pendente (checklist no doc §11). Evolução pendente: moveset curado dos bosses, mostrar a luta do Gladion na tela. |
| Mahogany | Esqueleto implementado e compilado em 19/09/2026; runtime pendente (checklist no doc §10, ordem sugerida em §12.5). Evolução pendente: apagão visual da cidade, mostrar a luta da Lillie na tela, saída do elenco a pé, reações dos moradores. |
| Missões | Objetivos locais, diálogos, pontos de encontro, níveis e parâmetros de boss. |
| Capturas | Condição de conclusão da missão e mecanismo de revanche/recuperação. |
| Beast Balls | **No código (24/09).** Migrado na V24-rev2, por decisão do autor. A Anabel **não vende nada**: ela conta que a Beast Ball existe porque **ela pediu ao Kurt que a inventasse**, e manda o jogador a Azalea. Preço, estoque e fonte passam a ser assunto de [`KURT_BALL_CRAFT_DESIGN.md`](../KURT_BALL_CRAFT_DESIGN.md), onde a Beast Ball é a receita de nível 10. |
| Altar | **No código (24/09), Fly incluído.** Fechado na V24: `MAP_SUN_MOON_ALTAR`, nome de mapa já correto (a `MAPSEC` foi renomeada para "Altar of Sun and Moon"), embarque no porto de Olivine com o `ITEM_SUN_MOON_TICKET`, desembarque no cais em (14,27), volta pelo marujo do cais. **Fly entra**: a `MAPSEC` do altar já está na mesma página do mapa da região que a `MAPSEC_METEOR_ISLAND`, que é destino de Fly funcionando — a dúvida da rev1 está respondida por esse precedente. Custa três linhas em `src/region_map.c`, uma `HEAL_LOCATION` e um `setflag` no fim do Ato I. |
| Solgaleo/Lunala | **No código (24/09).** A checagem é `checkspecies SPECIES_SOLGALEO` / `SPECIES_LUNALA` no script da fenda, recusa repetível e de graça; e `CheckMysteryEggPokemon` (que já existia, e cobre Cosmog/Cosmoem/Solgaleo/Lunala) é o que escolhe **qual** lendário aparece no mapa. Os dois objetos dividem o tile e têm **flags separadas** — mesma flag faria os dois spawnarem um dentro do outro. |
| Necrozma | **No código (24/09).** Fechado na V24: equipe da Lusamine de cinco (Clefable, Lilligant, Mismagius, Bewear, Milotic, níveis 70-72, no `TRAINER_LUSAMINE` que era stub); travessia pela fenda de chão do pátio com checagem de espaço antes; boss de **5 barras / Lv 90 / 160%** com perfil de fases novo; captura **roteirizada depois da vitória**; forma armazenada `SPECIES_NECROZMA` nível 75. |
| Despedida | **No código (24/09).** Fechado na V24: Ato V escrito, e a posição final de cada um é uma **escala de dias da semana** (tabela no §9). Looker e Anabel no altar, permanentes. |
| Poké Balls / Kurt | **No código (24/09), documento próprio na revisão 4:** [`KURT_BALL_CRAFT_DESIGN.md`](../KURT_BALL_CRAFT_DESIGN.md). Lojas passam a vender só Poké Ball; o Kurt vira a única fábrica, com **26 receitas por nível + 1 por história**, em **20 níveis** (`EXP(nv) = 4·nv·(nv-1)`, +1 por **bola**, lotes uniformes de 5, cota = nível, **32 dias** até o topo). O sorteio diário dele fica, **sem dar EXP**, e é a **única** fonte de Master Ball — que ele nunca aprende a fabricar. O Berry Master vai para a `Route30_House`, promovendo o NPC de berry que já mora lá. **O único acoplamento com este arco:** a caixa de fala da Anabel no altar, e uma **leitura** de `VAR_RIFT_MISSIONS_STATE >= 15`, que é o que destranca a receita da Beast Ball no instante em que o Necrozma cai. |
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
5. Implementar em esqueleto a ligação do Looker, o escritório de Olivine e Blackthorn (Missão 1) pelo doc `.claude/rift_missions/BLACKTHORN_ULTRABEAST/BLACKTHORN_ULTRABEAST_IMPLEMENTATION.md`; derrota usa blackout/retry e não avança a resolução.
6. **Missões 2 (Mahogany) e 3 (Cherrygrove) estão em esqueleto implementado** (19 e 20/09/2026) por `.claude/rift_missions/MAHOGANY_ULTRABEAST/MAHOGANY_ULTRABEAST_IMPLEMENTATION.md` e `.claude/rift_missions/CHERRYGROVE_ULTRABEAST/CHERRYGROVE_ULTRABEAST_IMPLEMENTATION.md`; falta validar as duas em runtime pelas checklists §10 daqueles docs (ordem sugerida em §12.5 e §12.6), com atenção especial ao balanceamento inédito de x130/x140 e à **regressão do presente do Friendly Trader** de Cherrygrove (§3.1.1 do doc da M3). Em seguida implementar a Missão 4 — **planejada na V17: conteúdo em §6.4 e plano técnico em `NEWBARK_ULTRABEAST_IMPLEMENTATION.md`** —, depois a reunião de Olivine, a expedição, o duelo de Lusamine sem blackout e o boss de Ultra Necrozma com retry, conforme os contratos aprovados. **A Missão 4 e a reunião de Olivine (evento PRÉ-NECROZMA) foram implementadas em esqueleto em 20/09/2026** por `.claude/rift_missions/NEWBARK_ULTRABEAST/NEWBARK_ULTRABEAST_IMPLEMENTATION.md` e `.claude/rift_missions/PRE_NECROZMA_ULTRABEAST/PRE_NECROZMA_ULTRABEAST_IMPLEMENTATION.md`; restam a expedição, o duelo e o boss, cujo documento começa lendo `FLAG_EVENT_NECROZMA_ALTAR_UNLOCKED` e `VAR_RIFT_MISSIONS_STATE >= 12`.
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

`MAHOGANY_ULTRA_BEAST_IMPLEMENTATION.md` → [`MAHOGANY_ULTRABEAST_IMPLEMENTATION.md`](MAHOGANY_ULTRABEAST/MAHOGANY_ULTRABEAST_IMPLEMENTATION.md), para ficar igual a `BLACKTHORN_ULTRABEAST_IMPLEMENTATION.md` e `CHERRYGROVE_ULTRABEAST_IMPLEMENTATION.md`. Todas as referências no design e no doc da Missão 1 foram atualizadas. O padrão de nome para as próximas missões é `<CIDADE>_ULTRABEAST_IMPLEMENTATION.md`.

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
- **Missão 4: planejada, não implementada.** Conteúdo em §6.4, plano técnico em [`NEWBARK_ULTRABEAST_IMPLEMENTATION.md`](NEWBARK_ULTRABEAST/NEWBARK_ULTRABEAST_IMPLEMENTATION.md) (20/09/2026). O doc levanta um risco que as três missões anteriores não tinham: **o orçamento de 16 object events simultâneos** — sete atores de elenco mais três Ultra Beasts deixam a cena a quatro slots do teto, e objeto que não cabe não spawna sem erro nenhum.
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

## 23. Registro da revisão V19

Escopo: pós-E4 (Missão 1 e regras comuns das missões) e quatro encontros
pré-Liga, só com falas opcionais. Política de duelos, altar, clímax e loop
ficam **inalterados**. Feedback do autor sobre o esqueleto da M1: “o esqueleto
está pronto, agora vamos montar uma história épica”.

### O que muda na Missão 1

- **História.** A Clair (+ Kingdra) já enfrenta o Necrozma na rua quando o
  jogador chega; o golpe dela não o arranha. O Necrozma abre a ruptura,
  Buzzwole e Pheromosa atravessam e **partem para cima do jogador**; o Silvally
  salta entre eles no último segundo e o Gladion chega correndo pelo norte. O
  resto da estrutura (escolha + boss, retry) não muda. Depois da vitória, o
  Necrozma **absorve as duas** Ultra Beasts e some; o elenco reage espantado.
- **Gladion é surpresa.** O briefing de Olivine não o menciona; ele fica
  escondido até o resgate. Ninguém sabe quem ele é — o Looker pergunta.
- **Clair participa** como Líder de Ginásio que protege a própria cidade: foi
  ela quem chamou a polícia, evacuou a cidade e segurou a criatura sozinha.
- **Portas trancadas** em vez de esconder a Clair do Ginásio (sugestão do
  autor): mecanismo genérico em C, uma linha por missão (§6, regras comuns).
- **Luta mais difícil:** 3 barras / Lv75 / x120 / moveset curado + item.
  Buzzwole: Bulk Up, Drain Punch, Leech Life, Ice Punch, Leftovers. Pheromosa:
  Quiver Dance, Bug Buzz, Focus Blast, Ice Beam, Life Orb. A escala continua
  crescendo (M2 = 4 / Lv80 / x130).
- **Presente de Type: Null** (§3, Gladion), com a checagem de espaço **antes do
  SIM** do Looker.
- **Reação opcional ao Cosmog** do Necrozma e do elenco.
- **Gancho sem destino:** “volte a Olivine, a gente avisa”. O briefing da M2
  deixou de citar o “Lake of Rage” do gancho antigo e agora é quem revela
  Mahogany; ganhou uma linha de continuidade (“nenhum sinal da luz de
  Blackthorn — ainda”).
- **Falas finais** na ligação do Looker, no briefing da M1 e em toda a cena de
  Blackthorn, pela voz do §3.1.

### Regras novas para o arco inteiro

Padrão do Necrozma, portas trancadas, gancho sem destino, acompanhante surpresa
e reação à família Cosmog — todas em §6, regras comuns. **Só a M1 as cumpre
hoje.** Aplicar nas M2–M4 é trabalho de evolução de cada uma e precisa
reconferir o orçamento de objetos (o Necrozma é um objeto a mais).

### O que continua em aberto

- ~~Runtime: nada da V19 foi jogado.~~ **Validado pelo autor em 22/09/2026** (M1 e reações pré-Liga), sem correções. Antes do teste, Os pontos de maior risco estão no §11 do doc
  da M1: o salto do Silvally, a caixa de texto sobre a Anabel, a dificuldade
  nova e o fluxo de apelido do Type: Null no meio da cutscene.
- A reunião de Olivine (PRÉ-NECROZMA) foi escrita antes de o elenco ter visto o
  Necrozma; na evolução dela, o nome “Necrozma” deve chegar como resposta ao que
  todos viram em Blackthorn, não como notícia.
- A Clair pode continuar aparecendo no Dragon's Den durante o incidente (a
  entrada é caverna, não porta). Não há flag que a esconda de lá sem mexer em
  `FLAG_HIDE_DEN_CLAIR`; registrado como pendência no doc da M1.

## 24. Registro da revisão V20

Escopo: pós-E4, Missão 2 (Mahogany) e uma regra comum nova. Pré-Liga, política de
duelos, altar, clímax e loop ficam **inalterados**. Feedback do autor sobre o
esqueleto da M2: "o esqueleto está pronto, agora vamos montar uma história
épica". A tabela *pedido → como ficou* está no doc da M2, §13.

### O que muda na Missão 2

- **Lillie é descoberta**, não anunciada: saiu do briefing e do "vá na frente"
  da Anabel; ao ser encontrada, reage com espanto.
- **Pryce evacua a cidade na tela** e é ele quem diz que evacuou; tenta atingir
  o Necrozma (Blizzard, sem efeito) e, no fim, volta para o Ginásio.
- **Portas trancadas** como em Blackthorn (Ginásio, Shop e House1); gate da Route
  43 e Valor Cavern abertos (porta não animada).
- **Necrozma em cena**: chega numa luz, abre a fenda, absorve as duas UBs no fim.
  A Lillie o reconhece de Alola e corta o assunto.
- **Duas rodadas seguidas contra a mesma UB.** Na primeira vitória a parceira a
  revive pela sinergia; a Lillie admite o erro e refaz o plano com o gelo do
  Pryce; a Anabel cura o time; a segunda vitória é de verdade. Rodada 1 = 2
  barras; rodada 2 = 4 / Lv80 / x130.
- **Reação opcional à família Cosmog** do Necrozma, da Lillie e do Pryce.
- **Gancho sem destino.** O briefing da M3 deixou de dizer "Cherrygrove at last"
  e passou a revelar o lugar.
- Falas finais no briefing da M2 e em toda a cena de Mahogany.

### Regras novas ou ampliadas para o arco

- **Sinergia entre as Ultra Beasts** (§6, regras comuns): nova, padrão dos
  próximos encontros. M2 cumpre; M3 tem uma relação parecida a desenvolver; M4
  pendente.
- **Líder de Ginásio local** (§6): registrado como padrão das M1 e M2.
- Portas trancadas, padrão do Necrozma, gancho sem destino e acompanhante
  surpresa: agora **M1 e M2** cumprem; M3 e M4 pendentes.

### O que continua em aberto

- **Runtime da M2 pendente.** Maiores riscos (doc da M2 §9 e §10): o equilíbrio
  de duas rodadas de x130, a cura sob fade no meio da cutscene, as portas
  animadas abrindo com a trava ativa, e o retry que refaz as duas rodadas.
- A reunião de Olivine (PRÉ-NECROZMA) precisa, na evolução dela, cobrar as duas
  promessas: o "Later" do Gladion (M1) e o "Later. I promise." da Lillie (M2). Os
  dois irmãos reconheceram a luz; é ali que o nome chega.

---

## 21. Registro da revisão V17 — voz da Lillie e plaquinha do falante (22/09/2026)

Segundo retorno do autor sobre a Missão 2, depois de jogar. Detalhe completo
em [`MAHOGANY_ULTRABEAST_IMPLEMENTATION.md`](MAHOGANY_ULTRABEAST/MAHOGANY_ULTRABEAST_IMPLEMENTATION.md) §14.

### O que a M2 corrigiu

- **A Lillie estava prevendo a cena.** Ela anunciava a luz antes do Necrozma
  chegar, marcava a hora e chamava o Pryce pelo relógio. Tudo isso saiu dela: o
  relógio é da Anabel, e ninguém anuncia a luz. A experiência dela **cresceu** no
  lugar — reconhece as UBs e reconhece a luz —, mas o incidente agora a pega de
  surpresa.

### Regras comuns novas (§3.3), válidas para o arco inteiro

- **Plaquinha com o nome do falante** em vez de `"Nome: "` dentro da fala.
  Cumprido em **13 arquivos de mapa, 380 falas**: as quatro missões, o escritório
  de Olivine e todos os encontros pré-Liga de Gladion, Lillie e Kukui. Cena nova
  já nasce assim. Skill `nomear-falante`.
- **Experiência não é previsão.** Reconhecer o que é ≠ saber o que vem. Quem
  mede o tempo é quem tem instrumento.

### O que isso muda no motor

A plaquinha existia e era usada só pela fala de entrada de treinador. Agora vale
para diálogo de cena, com a regra "cada mensagem diz quem fala" — uma mensagem
sem `{SPEAKER ...}` não tem plaquinha e não herda a anterior, o que faz narração
funcionar sem marcação. Arquivos e detalhe em §14.2 do doc da M2.

### O que continua em aberto

- **Runtime da M2 continua pendente**, agora com os sete itens da plaquinha na
  checklist (doc da M2 §10).
- As missões 3 e 4 já estão com a plaquinha aplicada, mas **o texto delas não foi
  revisado** à luz da regra "experiência não é previsão". Vale checar o Kukui na
  M3 e a Lusamine na M4 quando forem evoluídas.
- A reunião de Olivine continua devendo as duas promessas ("Later", do Gladion;
  "Later. I promise.", da Lillie).

---

## 25. Registro da revisão V21 — a história da Missão 3 (22/09/2026)

Escopo: pós-E4, **Missão 3 (Cherrygrove)**, três regras comuns ampliadas e duas
precisões de personagem. Pré-Liga, política de duelos, altar, clímax e loop
ficam **inalterados**. Feedback do autor sobre o esqueleto da M3: "o esqueleto
está pronto, agora vamos montar uma história épica". Tabela *pedido → como
ficou* em [`CHERRYGROVE_ULTRABEAST_IMPLEMENTATION.md`](CHERRYGROVE_ULTRABEAST/CHERRYGROVE_ULTRABEAST_IMPLEMENTATION.md) §13.

### O que muda na Missão 3

- **Quem avisou foi o Kukui**, por telefone, quatro dias antes — e acertou a
  janela duas vezes. O briefing em Olivine virou a cena em que Looker e Anabel
  leem a ficha de duas páginas dele e decidem, errado, que é um civil.
- **Necrozma em cena**, pela primeira vez saindo do mar: ele rasga a fenda, as
  duas UBs atravessam, e no fim ele **absorve as duas** e vai embora.
- **Ele ataca uma pessoa.** Depois que as UBs falham, vira para o **jogador**.
- **Anabel sente a ruptura antes do instrumento e entra na frente do jogador**,
  e é aí que a condição de Faller dela vem a público — **antecipada da M4**.
- **Sinergia com consequência visual:** a Blacephalon apaga a baía e o Stakataka
  **já está mais perto** quando a tela volta (`setobjectxy` sob o flash), duas
  vezes, a segunda colada no jogador. O especialista se corrige na cara dele.
- **Surpresa: o Kukui é o Fundador da Liga de Alola.** Solta um Incineroar,
  afasta o Stakataka e responde à ficha. Não vira treinador batalhável.
- **Portas trancadas** em Cherrygrove, com bilhete da Polícia Internacional.
- **Reação opcional à família Cosmog** do Necrozma, do Kukui e da Anabel — antes
  e depois da cena.
- **Presente sem item:** o fundador convida o Campeão a ir até o fim da Liga dele.
- **Gancho sem destino.** New Bark, as três assinaturas e a Lusamine saem do
  gancho; quem revela os três é o briefing da M4, que já estava escrito assim.
- Falas finais no briefing da M3 e em toda a cena de Cherrygrove.
- Dificuldade **inalterada**: 4 barras / Lv85 / x140 / moveset + item.

### Regras novas ou ampliadas para o arco

- **Sinergia (§6):** ganhou forma fixa — mostrada antes de explicada,
  consequência que o jogador sente, contramedida que o acompanhante enxerga.
  **M2 e M3 cumprem; M4 pendente.**
- **Acompanhante é surpresa (§6):** relida como *o briefing não entrega a
  surpresa*. Se o acompanhante for anunciado (como o Kukui), a surpresa tem de
  ser outra coisa, e o briefing tem de plantar o engano que ela desfaz.
- **Autoridade local (§6):** onde não há Ginásio, não se inventa um Líder; o
  custo da escalada recai sobre o elenco fixo.
- **Portas trancadas, padrão do Necrozma e gancho sem destino:** agora **M1, M2
  e M3** cumprem; M4 pendente.
- **Parceiro visível (§3.2):** precisado — a regra fala de presença
  **permanente**; Pokémon solto no meio da cena é encenação e não abre exceção.
- **Experiência não é previsão (§3.3):** ganhou **uma** exceção estreita — a
  Anabel sente uma ruptura abrir, e só isso. Nenhum outro personagem tem sentido
  nenhum, e ela não ganha outros.
- **Objeto escondido por cena tem flag temporária própria**, e as `setflag` de
  visibilidade rodam incondicionalmente no `ON_TRANSITION`: é o que faz o retry
  depois de blackout começar limpo sem nenhum script lembrar disso.

### O que continua em aberto

- **Runtime da M3 pendente.** Maiores riscos (doc da M3 §9 e §10): o
  `setobjectxy` sob o flash (com plano B escrito), a regressão do presente do
  Friendly Trader herdada do esqueleto, se x140 com 4 barras é ameaça ou parede,
  os três sprites 32×32 sobre água, e a cena longa se repetindo inteira a cada
  tentativa.
- **Runtime da M2 também continua pendente.**
- **A M4 precisa das regras comuns:** Necrozma em cena com absorção, portas
  trancadas em New Bark e a forma nova da sinergia entre Kartana, Guzzlord e
  Nihilego. O texto da revelação da Anabel lá já foi ajustado para ser "o resto".
- A reunião de Olivine continua devendo as duas promessas ("Later", do Gladion;
  "Later. I promise.", da Lillie) — e agora também o "The rest of it later" da
  Anabel, que a M4 paga.
- **Beast Balls** continuam pendentes desde a M1 (§5).

---

## 26. Registro da revisão V22 — a história da Missão 4 (22/09/2026)

Feedback do autor sobre o esqueleto de New Bark: *"o esqueleto está pronto,
agora vamos montar uma história épica"*, mais quinze pedidos específicos. Feito
com a skill `evoluir-historia-de-evento`; tabela completa **pedido → como ficou**
em [`NEWBARK_ULTRABEAST_IMPLEMENTATION.md`](NEWBARK_ULTRABEAST/NEWBARK_ULTRABEAST_IMPLEMENTATION.md)
§13.1, e as contradições resolvidas por escrito em §13.2.

`make -j$(nproc)` limpo; runtime **pendente**.

### O que muda na Missão 4

- **Ela se perde.** A cidade fica de pé, ninguém se machuca, nenhuma janela
  quebra — e a criatura absorve as três Ultra Beasts, vira outra coisa, derruba
  os quatro treinadores num golpe e vai embora. Escrito em §6.4 ("Resolução").
- **A conta de nove.** Quatro missões, nove Ultra Beasts, todas levadas por ela:
  *"It was never attacking us at all."* / *"…It was collecting."* / **"And we
  softened them for it. Four times."** É o que reenquadra o arco inteiro e o que
  o §7 e o §9 herdam.
- **Cadeia Elm → Kukui → Looker.** O Kukui **não** vai a New Bark; a última
  caixa do gancho da M3 foi reescrita do outro lado para produzir esse aviso.
  Quem fica dentro da análise é o Elm.
- **A conversa de Faller saiu do campo de batalha** e foi para o briefing de
  Olivine, sentada, antes de tudo — porque três rupturas juntas são a primeira
  coisa que a Anabel sente de **outra cidade**. Em campo sobram duas caixas de
  custo físico; no rescaldo, uma de retomada. §3.1 e §6.4.
- **A Lusamine não é anunciada em Olivine.** Ninguém a mandou vir.
- **A sinergia virou estrutura, não enfeite:** as três derivam no mesmo instante,
  o Elm mede, a Anabel nomeia, e a simultaneidade que isso obriga é o que cria a
  vaga do quarto treinador e dá motivo interno ao menu de escolha.
- **Gold/Crystal:** parceiro agora é **Azumarill**; luta duas vezes (corta o bote
  da Nihilego antes de qualquer autorização, e ataca a criatura sozinho depois de
  ser admitido); e ganha o arco de quem se sente peça sobressalente. Continua
  **sem** batalha de treinador e **sem** um quarto alvo: entra na mesma Ultra
  Beast que o jogador.
- **A lição da mãe vira ação:** quem derruba o "não" ao Gold/Crystal é a
  **Lusamine**, trinta segundos depois de ouvir que decidir pelos outros não é
  proteção.
- **Reações opcionais à família Cosmog** (design §4.11) finalmente trazem o
  §6.4 para a tela: a Lusamine usou um Cosmog, sabe como aquele brilho se parece
  do outro lado, e é ela quem diz que **não é culpa do jogador**. Opcional, sem
  estado, sem flag.

### O que NÃO mudou

Estado (8/9/10), a invariante flag ⇔ 9, a estrutura escolha + boss, os três
chefes (4 barras / Lv90 / x150 e seus movesets), `B_FLAG_NO_CATCHING`, o
tratamento dos cinco resultados de batalha, o retry por blackout com a escolha
refeita, a evacuação por flag de evento, os dois recálculos de interior e a
regra visual de parceiros de §3.2.

### Regras novas ou ampliadas para o arco

- **A sinergia das Ultra Beasts nunca foi delas.** Regra comum de §6 ampliada:
  a criatura vinha sincronizando as nove desde Blackthorn. Todo encontro novo de
  Ultra Beast escrito depois da M4 tem de se posicionar em relação a isso.
- **Uma missão do arco pode terminar em derrota**, desde que a cidade e as
  pessoas fiquem inteiras e a perda seja **de objetivo**, não de vida. A M4 é o
  precedente e, por enquanto, a única.
- **Reação opcional à família Cosmog é padrão de encontro pós-E4**, não exceção:
  M1, M3 e M4 têm. Sempre `CheckMysteryEggPokemon`, sempre sem flag e sem var
  persistente, sempre re-amostrada depois de batalha quando a conversa final
  também reage.
- **Conversa de personagem não acontece no meio de uma luta.** Pedido explícito
  do autor sobre a Anabel, e vale como regra de escrita: revelação longa vai
  para uma sala, com cadeira; o campo fica com o custo físico e com uma
  retomada curta.
- **Par de textos em mapas diferentes anda junto.** Já valia desde a V21; a V22
  acrescentou o par gancho-da-M3 (Kukui) ↔ `Text_BriefingM4`, e o par
  `Text_ReunionOpen` ↔ o fim da M4.
- **Dois templates podem dividir um tile** desde que nunca estejam spawnados ao
  mesmo tempo e cada um tenha a **própria** flag temporária. É como a M4 põe a
  criatura e o que ela vira em (16,12) gastando **um** slot de object event.

### O que continua em aberto

- **Todo o runtime da M4** (checklist no §10 daquele doc). Nada foi jogado.
- **x150 com 4 barras** continua sem teste, e x140 da M3 também.
- **Orçamento de objetos:** pico medido em código de **13/16**; sobram três
  slots na M4. Precisa ser confirmado em jogo, inclusive à noite.
- **O PRÉ-NECROZMA (§7) foi escrito quando a M4 terminava em vitória.** Uma
  caixa foi ajustada; a cena inteira ainda merece uma releitura à luz da
  derrota, e é o próximo trabalho natural deste arco.
- Beast Balls com a Anabel, pendentes desde a M1.

## 27. Registro da revisão V23 — escurecimento dos flashes, trilha da ruptura e o reencontro da Lillie (23/09/2026)

Revisão de **runtime**, não de história: o autor jogou as quatro missões e trouxe
três problemas. Nenhum arco, coreografia, batalha ou estado mudou.

| Pedido do autor | Como ficou | Alcance |
|---|---|---|
| "Quando as Ultra Beasts aparecem é para ficar mais escuro e é legal, mas fica impossivelmente escuro" | Não era escurecimento, era o **flash**: `fadescreen` compõe o tint de horário sobre si mesmo a cada par, e à noite oito flashes levam a cena a ~0,2% do brilho. Todo `fadescreen` de dentro de cena virou `fadescreenswapbuffers` (BLDY no hardware, não toca em paleta). Regra comum nova em §6. | **M1, M2, M3 e M4** |
| "No incidente de Cherrygrove a música não muda quando as Ultra Beasts aparecem, então fica bizarra a música feliz" | `fadeoutbgm` na fala da Anabel, `playbgm MUS_DP_LEGEND_APPEARS, TRUE` na chegada do Necrozma, `fadedefaultbgm` no pós-cena. `SONG_MUS_DP_LEGEND_APPEARS` ligada em `include/config/songs_enabled.h`. Regra comum nova em §6. | **M3 implementada; M1, M2 e M4 pendentes** (o pedido foi sobre a M3) |
| "A Lillie no diálogo pré-luta de Mahogany fala uma fala totalmente desconectada e bizarra, sobre Johto" | `Mahoganytown_Text_UBLillieIdle` dizia "I came to Johto to see it. That's all. Just to see it." — "it" sem antecedente, e **explicando ao jogador que veio para Johto** depois de tê-lo encontrado três vezes lá (Route 30, Goldenrod, Dragon's Den). Reescrita como reencontro; a experiência dela, o susto e as anotações ficaram intactos, e a Lusamine continua fora (surpresa da M4). | **M2** |

**Regra de continuidade que isto deixa escrita:** a Lillie e o Gladion não são
personagens novos no pós-game. Antes de escrever qualquer caixa em que um deles
encontra o jogador, confira o que já aconteceu entre os dois na campanha (§4.5 a
§4.9) — *descoberta* quer dizer "o jogador não esperava encontrá-la aqui", nunca
"os dois não se conhecem".

**Conferido:** `make -j$(nproc)` limpo, ROM em 92,73%. `medir_linha.py` e
`checar_falantes.py` sem apontamentos. **Runtime pendente nos três pontos** — o
teste de todos eles é entrar na cena **à noite**.

---

## 28. Registro da revisão V24 — o clímax: Altar do Sol e da Lua, Ultra Necrozma e o mundo depois (23/09/2026)

Revisão de **história e de escopo**, escrita junto com
[`ALTAR_SUN_MOON_IMPLEMENTATION.md`](ALTAR_SUN_MOON/ALTAR_SUN_MOON_IMPLEMENTATION.md). Nenhum
valor de var, invariante, coreografia ou batalha das quatro missões nem do
PRÉ-NECROZMA mudou. O que esta revisão faz é **fechar o arco**: do estado 12 ao
16, e daí em diante o loop.

### O briefing do autor, pedido por pedido

| Pedido | Como ficou |
| --- | --- |
| "Monta uma história épica; já está tudo bem setado" | Cinco atos num mapa e meio, com falas finais já escritas no plano. O plano não é esqueleto porque o terreno não pedia um. |
| "Envolve o Solgaleo nas cutscenes e coloca ele no mapa" | O parceiro do jogador é objeto de overworld em três atos, e é ele quem estabiliza a fenda, quem se põe na frente da criatura e quem harmoniza a passagem no fim. Solgaleo **e** Lunala, escolhidos por `CheckMysteryEggPokemon`, em flags temporárias separadas. |
| "Tem que ficar claro que o mapa está instável, e o único jeito de entrar é com o Solgaleo" | Três camadas: `WEATHER_VOLCANIC_ASH` enquanto o estado é 13-15; o **disco vira portal** por `setmetatile` (os sete metatiles já existem no `gTileset_AltarSunMoon`); e a fenda recusa quem não tem um dos dois na **equipe**, com fala repetível e custo zero. |
| "A Lusamine se oferece por arrependimentos do passado" | Ato I, e é argumento dela, não pedido de desculpas: quem atravessa é quem já gastou os filhos de outras pessoas na própria curiosidade. Duas caixas, e a segunda termina em "That is not tragedy. That is bookkeeping." |
| "Gladion e Lillie ficam contra" | A Lillie argumenta ("você decidiu e depois veio nos contar"); o Gladion recusa sem discutir ("não estou discutindo, só não estou saindo daqui"). |
| "A cena para aí e o player é liberado; sim/não com a Lusamine; o não só não avança" | Estado **13**. A cutscene termina em `releaseall` e o jogador anda pelo altar. O `NÃO` não muda flag nem var e é repetível palavra por palavra. **Pela primeira vez no arco, o que trava a história não é uma criatura, é um desacordo entre pessoas — e quem desempata é o jogador.** |
| "Jogador vence, o portal se mostra mais instável; aparece um portal no meio do Altar" | Estado **14**: a fenda nasce em (14,10), no pátio, como **objeto** (`OBJ_EVENT_GFX_PORTAL`, o mesmo tipo dos quatro portais de `SpearPillarTop`). |
| "A gente vai reusar isso" | **É o mesmo objeto** no clímax e no loop diário. Só o script dele muda de ramo pelo estado. |
| "Entra lá dentro, luta com o Ultra Necrozma, e a Anabel te acompanha" | `MAP_ULTRA_SPACE_ARENA`. A Anabel acompanha **na encenação** (sobe o corredor, se põe na frente dele uma vez, dá a leitura, sai do caminho) e **não** como parceira de batalha — o sistema de follower NPC está desligado no projeto e o sistema de boss só funciona em batalha simples. Registrado como decisão reversível no §15 do plano. |
| "Boss battle beem difícil" | **5 barras / Lv 90 / x160**, com `BOSS_PHASE_PROFILE_NECROZMA` novo. A escala do arco continua subindo: 3/x120, 4/x130, 4/x140, 4/x150, **5/x160**. |
| "Captura como parte da cutscene; o Solgaleo harmoniza os portais" | `B_FLAG_NO_CATCHING` na luta e `givemon SPECIES_NECROZMA` nível 75 na cena. Isso **fecha** a pendência de §9 ("não está definido se a captura ocorre durante o combate ou depois") e torna "derrotar sem capturar" impossível por construção. |
| "Conversa de todo mundo encerrando" | Ato V, e a ordem das caixas é a de sempre: **as pessoas antes do relatório**. A Lusamine pede a única coisa que ela nunca pediu ("May I come back?"), e a Lillie responde sim "não porque está tudo bem — porque você perguntou". |
| "Mapa feliz de novo, mas com o portal aparecendo 1x por dia" | O disco volta ao sol/lua e a cinza para no Ato V; a fenda fica, e do estado 16 em diante aparece enquanto `FLAG_DAILY_ALTAR_RIFT` está limpa. |
| "A Anabel vende Beast Ball" | `pokemart` de uma linha, **1500**, estoque infinito, sem entrega inicial — e **atrás da fala dela**, porque o §3.1 proíbe transformá-la em vendedora. |
| "Lusamine, Gladion e Lillie algumas vezes no quarto de Olivine" | Domingo e sexta, os cinco (com Ninetales e Silvally). Sem batalha: a sala é onde eles **não** estão trabalhando. |
| "Kukui volta pro laboratório e aparece na praia de Cherrygrove; Lillie também, com ele" | O Kukui na praia da Missão 3 em segunda, terça, quinta e sábado; a Lillie em terça, quinta e sábado. Ele aparece sozinho na segunda, que é o ponto: é ele que não consegue deixar as leituras em paz. |
| "Gladion em Cianwood" | Terça, quarta e sábado, no tile da despedida dele, com o Silvally. |
| "Lusamine no Altar" | Segunda, quarta e sábado, em (14,9), de frente para o disco. |
| "Rematch nesses momentos" | Uma por dia por personagem, por daily flag, com time de seis de pós-game. Quatro treinadores: dois reaproveitam stubs nunca usados (`TRAINER_LUSAMINE`, `TRAINER_KUKUI`), dois são recuperados de `TRAINER_UNUSED_*`. |
| "Looker e Anabel ficam no Altar permanentemente, tomando conta dos resquícios" | Eles **saem de `OlivineCity_House1`**, o que exigiu mudar o campo `flag` dos dois de `"0"` para temporária recalculada — e **contradiz uma regra escrita** do doc anterior. A auditoria do §14.4 daquele plano registra por que a via escolhida não viola a regra (nenhum `removeobject`) e o que tem de ser reescrito no comentário daquele arquivo. |
| "Um portal 1x por dia que te deixa fazer as Rift Missions; por enquanto não tem nada lá dentro" | A fenda diária leva à arena vazia, com uma caixa de narração, e o gatilho sul que já existe devolve o jogador. É o **único `@ SKELETON:`** que o plano deixa, e é o ponto de partida do documento do loop. |

### A surpresa deste evento

O arco guardou uma por missão (o Gladion, a Lillie, o Incineroar do Kukui, a
forma Ultra). A deste não é um personagem: é **o motivo da coleta**. A criatura
recolheu nove Ultra Beasts em quatro cidades porque **estava com fome** — a luz é
comida, a armadura é o que ela comeu, e a hesitação diante de um Cosmog em New
Bark (V22) era reconhecimento. Quem descobre é a Anabel, e ela diz o que
**observa**, não o que prevê (§3.3). Nenhuma caixa das quatro missões, da reunião
ou do Ato I usa a palavra.

### O que esta revisão fecha no §14

Escritório (presença pós-história e Beast Balls), Beast Balls (preço, estoque,
entrega), Altar (localização, nome, embarque, desembarque — **menos o Fly**),
Necrozma (equipe da Lusamine, travessia, regras de boss, captura, forma
armazenada) e Despedida (falas e posição final).

### O que continua em aberto

1. **Fly para o altar.** Metade do caminho já existe no repositório: a `MAPSEC`
   tem nome ("Altar of Sun and Moon") e posição. Falta uma `FLAG_VISITED_*`, um
   `setflag` e uma linha em `sFlyDestinations` — **e confirmar em runtime** que um
   destino de Fly numa página secundária do mapa da região (`sevii123`, onde essa
   `MAPSEC` mora) é selecionável. A balsa funciona nos dois sentidos, então nada
   fica inacessível enquanto isso.
2. **A Anabel como parceira de batalha de verdade.** Pergunta para o autor: vale
   trocar o boss de cinco barras por uma dupla selvagem comum? A recomendação do
   plano é **não**, e manter a encenação.
3. **A Nihilego no time de revanche da Lusamine.** É o único Ultra Beast em mão de
   personagem no jogo. A intenção é "uma das nove, sob responsabilidade da
   Aether", não a fusão de Sun/Moon — mas é o item que mais depende de leitura, e a
   troca é de uma linha.
4. **A cura do Looker no altar:** a partir do estado 13 (antes do boss, quando é
   útil) ou só do 16? O plano escreve 16 e **recomenda 13**.
5. **Runtime de tudo o que veio antes.** As Missões 2, 3 e 4 e o PRÉ-NECROZMA
   continuam com build limpo e runtime pendente, e os três pontos da V23
   (escurecimento, trilha da M1/M2/M4, fala da Lillie em Mahogany) continuam
   pendentes de teste noturno.
6. **O documento do loop.** Pools de treinadores e lendários, sorteio, e a
   pergunta que o plano do altar deixa explícita: um mapa de arena para todas as
   expedições ou um destino por tema? Se for por tema, quem escolhe é o script da
   fenda.

### Registro da revisão V24-rev2 — o retorno do autor (23/09/2026)

Cinco respostas do autor à revisão 1 do plano do altar. As quatro primeiras
fecham pendências; a quinta abre um sistema novo e um documento novo.

| Pergunta da rev1 | Resposta do autor | Como ficou |
| --- | --- | --- |
| A Anabel pode ser parceira de batalha de verdade? | "Faz parecer que ela está segurando alguma coisa que mantém o portal estável e não pode lutar" | **A melhor das três saídas.** O motivo de ela não lutar deixa de ser uma limitação escondida da engine e passa a ser uma **cena**: quem atravessou uma ruptura é quem consegue segurar uma aberta, então ela entra, se posta, e **as mãos dela estão ocupadas até o fim do ato**. Duas caixas novas e uma correção de coreografia (ela recua para o tile de âncora e não se move mais). Nenhum jogador vai perceber que a engine não podia. |
| A Nihilego no time de revanche da Lusamine? | "Sim, pode utilizar" | Fica. Com **uma condição escrita**: uma caixa de fala dela tem de dizer de onde a Nihilego veio (uma das nove, sob responsabilidade da Aether), para que a presença dela nunca seja lida como a fusão de Sun/Moon que o §3.1 proíbe importar. |
| O Looker cura no altar desde o 13 ou só no 16? | "Pode curar" | Cura **desde o estado 13**, que é onde importa: é o retry da boss que manda o jogador para o continente. Junto com o Fly, o retry cai para duas telas. |
| Fly para o altar? | "Coloca no mesmo mapa secundário que tem a Crater" | **Já está lá.** A `MAPSEC` do altar divide a página `sevii123` do mapa da região com a `MAPSEC_METEOR_ISLAND` — a "Crater" —, que é destino de Fly funcionando, com linha em `sFlyDestinations`, `case` em `GetMapsecType` e entrada em `sMapHealLocations`. A dúvida da rev1 estava respondida pelo próprio repositório. Fly entra: três linhas, uma `HEAL_LOCATION` e um `setflag`. |
| A Anabel vende Beast Balls? | "Ela não é mais um shopping, ela só te direciona como faz para fazer poke bolas com o Kurt diariamente" + todo o pedido do Kurt | A loja **sai inteira** do plano do altar. No lugar: ela conta, **antes da luta contra o Necrozma**, que a Beast Ball existe porque ela escreveu a um velho de Azalea há quatro anos e pediu que ele inventasse uma. Depois da vitória ela entrega a que estava guardando. No pós-game, duas caixas mandando o jogador ao Kurt. |

**O sistema de Poké Balls do Kurt é documento próprio, e já está na revisão 2:**
[`KURT_BALL_CRAFT_DESIGN.md`](../KURT_BALL_CRAFT_DESIGN.md). Ele não é conteúdo das
Rift Missions e não toca em `VAR_RIFT_MISSIONS_STATE`; o acoplamento entre os
dois é **uma caixa de texto**. O que ele encontrou no código de hoje vale
registrar aqui porque é o tipo de coisa que este design já errou antes:

- As sete receitas de bola do Kurt **existem e são código morto** — o script dele
  termina em `goto KurtDaily` incondicional e o menu nunca é alcançado.
- As receitas têm um bug de `VAR_RESULT`: com a bolsa cheia, o jogador **perde as
  cinco berries e não recebe nada**, nas sete.
- **Apricorn não é obtenível no jogo**: `APRICORN_TREE_COUNT` é 0.

**Regra comum nova que a rev2 deixa para o arco inteiro:** quando a engine não
permite o que a cena quer, **a limitação vira encenação, não silêncio**. A Anabel
não podia ser parceira de batalha por três razões técnicas; a resposta certa não
foi escolher entre as duas opções técnicas, foi dar ao personagem um motivo para
estar de mãos ocupadas. Vale para toda cena futura em que o motor disser não.
