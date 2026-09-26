# SoulGold — planejamento narrativo de Blackthorn ao Altar

**Proposta V1 · 25/09/2026 · Para discussão da história, não implementação.**

Base: os sete arquivos fornecidos, com prioridade para os roteiros de cena e para o feedback atual do autor. Pesquisa de voz: personagens dos jogos principais de Pokémon, distinguindo SM de USUM. O hack continua sendo uma continuação híbrida própria; anime e Masters não definem sua caracterização.

Este documento propõe uma direção completa, com motivos, revelações, encenação e amostras de voz. Não substitui silenciosamente os scripts, não altera a ROM e não certifica correções dos bugs relatados. Falas de exemplo são originais, em inglês. Explicações de planejamento estão em português.

## Regra aprovada — convocações diárias de Looker

**Atualização de 25/09/2026:** cada missão posterior a Blackthorn começa com uma ligação de Looker convocando o jogador à base de Olivine. A reunião que prepara a ida ao Altar também recebe uma convocação. A ligação existente de Blackthorn entra no mesmo limite: **no máximo uma ligação de convocação de Looker por dia do calendário do jogo.** Esta regra prevalece sobre acessos automáticos ao próximo briefing descritos nos roteiros antigos. Ainda precisa ser implementada na ROM.

Olivine é o lugar onde os registros são comparados, a equipe apresenta o próximo objetivo e combina a operação. O telefone comunica uma pista e o local do encontro; os detalhes e decisões ficam no briefing. O intervalo entre chamadas representa investigação. Não anunciar que a próxima cidade já está sendo atacada no encerramento anterior, para depois obrigar a equipe a esperar o calendário.

| Convocação | Pré-requisito narrativo | Destino após o briefing |
| --- | --- | --- |
| Blackthorn | Gatilho inicial já existente | Blackthorn |
| Mahogany | Blackthorn concluída, incluindo sua resolução/presente | Mahogany |
| Cherrygrove | Mahogany concluída | Cherrygrove |
| New Bark | Cherrygrove concluída | New Bark |
| Preparação do Altar | New Bark concluída | Reunião em Olivine e operação no Altar |

### Regra de disponibilidade

- O limite controla **novas ligações**, não expira missões, não impede novas tentativas e não impõe um segundo bloqueio diário ao briefing.
- Se a missão anterior acabou e Looker ainda não ligou naquele dia, a próxima ligação pode acontecer no primeiro momento seguro. Se ele já ligou, esperar o próximo dia elegível.
- O dia é o calendário usado pelo sistema diário/RTC do jogo, não 24 horas desde a ligação, nem o relógio do computador desta edição. Uma virada de dia basta; não acumular convocações pelos dias em que o jogador não abriu o jogo.
- Uma chamada concluída grava juntos o dia da última convocação e a missão convidada. Um convite pendente continua válido entre dias e ao carregar o save. Não mandar lembretes automáticos nem saltar para a missão seguinte enquanto a atual estiver pendente.
- Disparar apenas com controle livre. Batalhas, menus, cutscenes, diálogos e transições adiam a chamada. Dentro da base de Olivine, aguardar a saída do jogador; não gastar a convocação antes de ela ocorrer.
- Visitar Olivine antes da chamada oferece a fala de investigação em andamento. Depois da chamada, libera o briefing. A cena de campo só começa depois desse briefing; chegar primeiro à cidade não contorna a ordem.
- Reiniciar, trocar de mapa ou perder uma batalha não limpa o registro diário. A implementação deve seguir o tratamento já existente para ajustes de RTC, sem inventar aqui um novo sistema de punição.
- Separar o estado da história, o convite pendente e o registro diário. Não reutilizar o controle de expedições do portal: a frequência dessas expedições é outra decisão.
- Em saves anteriores à mudança, preservar missões já iniciadas/briefadas sem exigir uma ligação retroativa. Para a próxima missão ainda não convocada, aplicar a regra no primeiro momento elegível, sem inventar um histórico de ligações que o save não registrou.

**Exemplo:** Looker liga para Blackthorn na segunda-feira. O jogador conclui Blackthorn nesse dia; Mahogany só poderá ser convocada na terça-feira. Se guardar o convite de Mahogany até sexta e concluir a missão na sexta, Cherrygrove pode ser convocada ainda na sexta, pois a última ligação foi na terça. Se a chamada de Mahogany aconteceu na própria sexta, a próxima aguarda sábado.

### Falas de convocação

Falas em inglês, com **LOOKER acima de todas as páginas**. Estes são textos de abertura para integrar às revisões dos respectivos roteiros; não representam mudanças já aplicadas à ROM.

**Mahogany** — já incorporada ao roteiro reescrito:

```text
LOOKER
{PLAYER}, it's Looker.
Pryce reported unusual Pokémon in Mahogany.

Meet us at our base in Olivine.
Anabel has compared the readings
with Blackthorn's.
```

**Cherrygrove:**

```text
LOOKER
{PLAYER}, we've had a report
from the Cherrygrove coast.

Meet us at the Olivine base.
Anabel found something in Lillie's notes
that may help us this time.
```

O briefing deve concretizar essa pista: cruzar as anotações de Lillie com o registro de Anabel para reconhecer o intervalo anterior à intervenção de Necrozma. Não anunciar o encontro com Kukui antes de haver informação sobre ele.

**New Bark:**

```text
LOOKER
{PLAYER}, Professor Elm contacted us.
His readings match the rift at Cherrygrove.

Come to the Olivine base.
We need to plan our approach to New Bark.
```

A correspondência dos dados justifica a investigação. Não revelar por telefone um cerco à casa da mãe enquanto se pede ao jogador um desvio burocrático; o quadro completo de New Bark é apresentado no briefing/campo, com a equipe organizando ajuda.

**Reunião antes do Altar:**

```text
LOOKER
{PLAYER}, everyone's here in Olivine.
We have a route to Necrozma.

Meet us at the base.
We need you for the plan.
```

O encerramento de New Bark encaminha a análise dos registros e a busca de uma rota; não manda o jogador imediatamente à reunião e depois bloqueia sua entrada por um dia. O Altar continua a operação acordada nessa reunião, sem outra ligação nem espera diária adicional no meio dela.

**Espera entre missões, ao visitar a base antes da convocação:**

```text
LOOKER
We're still checking the reports.
I'll call when we have a lead.
```

Usar somente quando a missão anterior terminou e a próxima ainda não foi convocada. Depois de um convite, orientar ao briefing; depois do briefing, orientar ao destino da missão. Ao concluir o arco, substituir pela rotina de pós-game.

### Verificação para implementação

Confirmar: uma ligação por dia entre todas as etapas; registro da chamada inicial; nenhuma repetição de convite pendente; briefing bloqueado antes da chamada; convite preservado depois da virada de dia; retry liberado no mesmo dia; adiamento seguro sem consumo; saves antigos sem bloqueio de missão ativa; nenhuma chamada adicional entre a reunião final e o Altar. Os nomes concretos das flags, vars e hooks dependem do código atual e não foram inventados neste planejamento.

## 1. A história que estamos contando

**Necrozma tenta recuperar sua luz abrindo rupturas em Johto. Cada absorção o fortalece por pouco tempo e agrava uma instabilidade que ele não consegue resolver sozinho. Um grupo que inicialmente só consegue proteger as cidades aprende a interromper esse ciclo — e precisa aprender a colaborar para conseguir fazê-lo.**

O arco tem dois conflitos ligados por ações, sem transformar todas as falas numa metáfora:

- **Externo:** conter as Ultra Beasts, entender Necrozma, resgatar as criaturas absorvidas e estabilizar as passagens.
- **Humano:** pessoas competentes precisam dividir decisões. Lusamine tem dificuldade em aceitar isso; Lillie e Gladion não aceitam mais que ela decida por eles; Anabel coordena sem prometer onisciência; Looker transforma informações dispersas em investigação.

A conclusão desejada não é “o monstro era inocente, então ninguém precisava lutar”. Ele estava causando perigo real. Entender a causa permite uma solução melhor do que continuar repelindo ataques.

**A captura de Necrozma é parte do plano antes da batalha final.** Vencer reduz sua instabilidade; a Beast Ball permite retirá-lo daquele ambiente; depois ele participa, junto do parceiro do jogador, da estabilização das fendas. A história mostra essa última ação. Capturá-lo não pode funcionar como um botão mágico que resolve tudo fora de cena.

### O que preservar

Blackthorn com Clair, Gladion e Silvally; Mahogany com Pryce, Lillie e Ninetales; Cherrygrove com Kukui e a revelação da Anabel; New Bark com a mãe, Elm, Lusamine e Gold/Crystal; reunião em Olivine; impasse e duelo narrativo com Lusamine no altar; Ultra Necrozma como clímax; captura roteirizada de Necrozma; pós-game de expedições.

Preservar também o parceiro vindo do ovo da campanha, os presentes existentes e o papel de Looker em todas as missões. O jogador continua resolvendo as batalhas decisivas.

### Mudanças estruturais propostas — ainda são propostas

1. Identificar Necrozma após Blackthorn, em vez de todos evitarem seu nome por quatro missões.
2. Substituir a “mente única das nove UBs” por comportamentos de cada encontro e uma causa energética comum nas fendas.
3. Manter a absorção visual, mas explicitar que as UBs permanecem vivas e precisam ser recuperadas.
4. Fazer o grupo tentar contramedidas diferentes após cada descoberta.
5. Usar o altar como local onde a instabilidade pode ser contida, não só como cenário da última luta.
6. Reformular o conflito da Lusamine como dificuldade de delegar responsabilidade, com progresso entre New Bark e o altar.

São mudanças necessárias para a versão desenvolvida abaixo. Se a identificação tardia ou a mente coletiva forem preservadas, será preciso outra justificativa consistente; não misturar as duas versões na implementação.

## 2. Diagnóstico dos roteiros atuais

| Problema concreto | Efeito na história | Direção proposta |
| --- | --- | --- |
| Gladion, Lillie e Lusamine reconhecem algo, mas adiam informações essenciais | O suspense depende de personagens omitirem ajuda | Revelar o nome cedo; preservar o mistério do comportamento novo |
| As quatro missões repetem absorção e retirada | Parece que os investigadores não aprendem | Cada retorno a Olivine produz uma nova ação de campo |
| A fome aparece como revelação final, apesar de já ser descrita em Blackthorn | O clímax revela o que o jogador já sabe | Revelar que acumular luz não estabiliza Necrozma e que as UBs ainda podem ser salvas |
| Mahogany afirma um circuito inesgotável, cura total e isolamento por gelo como certezas | A solução depende de regras improvisadas | Mostrar uma recarga finita e interromper uma ligação visível, sem aula de física |
| Cherrygrove estabelece teleporte, mas a solução é observar melhor | Contramedida não responde ao poder apresentado | Avanço encoberto pelos flashes, com deslocamento demonstrável |
| Looker e Anabel tratam Kukui como incapaz até descobrirem a Liga | A surpresa enfraquece os policiais | Eles conhecem suas credenciais; o jogador vê sua habilidade prática |
| New Bark deduz “um ser em três corpos” de passos simultâneos | A conclusão excede a evidência | Três comportamentos que criam uma ameaça conjunta, sem mente compartilhada |
| Gold/Crystal implora por uma vaga e é humilhado | Surge um arco pessoal não construído antes | Rival já participa da defesa e recebe uma responsabilidade real |
| O texto final diz que Necrozma nunca atacou, após ataques mostrados | A narrativa contradiz a tela | Sua necessidade explica o comportamento, mas não apaga o perigo |
| Anabel passa de sentir rupturas a sustentá-las com as mãos por ser Faller | Um poder novo resolve o clímax | Ela mantém um dispositivo de estabilização preparado e testado antes |
| A reunião diz que só Lusamine atravessou uma ruptura, diante da Anabel | Contradição direta | Diferenciar experiência de pesquisa, experiência operacional e memória pessoal |
| Várias falas descrevem o próprio arco ou o gênero da cena | Todos parecem o mesmo narrador | Cada pessoa fala para conseguir algo imediato de outra pessoa |
| O pós-game menciona uma Nihilego recuperada sem mostrar o resgate das nove | A consequência principal fica sem resolução | Encenação explícita de libertação e acolhimento antes do epílogo |

Também remover quantificações inventadas que não sustentam nada: dois anos de jornada, quarenta moradores, milhas, idade exata de Lusamine, décadas de carreira da Anabel, semanas precisas de burocracia. Só manter um número quando a continuidade o estabelece e a cena precisa dele.

## 3. Bíblia de personagens: como pensam e como falam

As bases canônicas abaixo são resumos curtos. Motivações e decisões para este arco são propostas autorais. Fontes no final.

### Lusamine

**Base:** autoridade da Aether, orgulho e comportamento controlador; SM e USUM dão pesos diferentes à obsessão, à família e a Necrozma. Não importar automaticamente a fusão com Nihilego.

**Aqui:** ela quer ajudar de verdade. Ainda acredita que ter mais conhecimento lhe dá o direito de assumir todas as decisões. Quando teme falhar, torna-se mais formal e mais centralizadora. Seu problema não é falta de amor; é confundir cuidado com controle.

**Pensamento inicial:** “Conheço esse perigo. Devo conduzir a resposta.”

**Progressão:** em New Bark aceita uma divisão tática; em Olivine compartilha o que sabe; no altar aceita que outra pessoa lidere a travessia e cumpre uma função indispensável de apoio. Não aprende tudo numa fala da mãe e esquece cinco minutos depois.

**Voz:** frases completas, precisas, um pouco mais formais que as dos filhos. Poucas contrações. Orgulho pode aparecer numa correção breve, sem discursos ornamentados. A mudança aparece quando ela faz uma pergunta e espera a resposta.

**Evitar:** autoanálise constante, pedidos de perdão em toda cena, linguagem de contabilidade emocional, transformar reparação em punição pessoal, uma mãe instantaneamente perfeita.

**Amostra — ao aceitar a tarefa no altar:**

> **LUSAMINE**  
> I will keep this side stable.  
> Tell me when you are ready.

### Lillie

**Base:** educada, observadora, leitora; seu desenvolvimento inclui coragem e capacidade de confrontar a mãe. A delicadeza não desaparece quando ela se torna firme.

**Aqui:** já viveu os encontros da campanha de Johto e sabe batalhar. Quer ser útil sem fingir certeza. Observa os Pokémon antes de formular um plano. Corrige a hipótese quando a tela a contradiz.

**Pensamento inicial:** “Talvez eu consiga perceber algo que ajude.”

**Progressão:** em Mahogany formula e revisa uma estratégia; na reunião apresenta dados sem pedir licença para existir; no altar defende uma decisão própria diante da mãe. Seu arco não é aprender a falar alto, e sim confiar no próprio julgamento sem parar de ouvir.

**Voz:** gentil e concreta. Pode hesitar uma vez diante de algo difícil; não precisa se desculpar a cada instrução. Fala do que viu, do que teme e do que quer tentar.

**Evitar:** profecias, saber o plano de Necrozma, metáforas filosóficas sobre portas, regressão à insegurança inicial de Alola, “sempre soube” sem antecedente.

> **LILLIE**  
> The current is still reaching it.  
> We need to block the connection.

### Gladion

**Base:** reservado, exigente, protetor; valoriza força, mas sua relação com Type: Null/Silvally é construída por confiança.

**Aqui:** reconhece o jogador como alguém com quem pode dividir uma linha de defesa. Cuida por ações. Com Lusamine, testa decisões concretas em vez de aceitar uma declaração de mudança.

**Pensamento inicial:** “Se ninguém assumir essa frente, alguém ficará exposto.”

**Progressão:** em Blackthorn divide os alvos com o jogador; em Olivine exige um plano claro; no altar entrega a frente principal ao jogador e mantém a retaguarda. Confiar não significa ficar sem função.

**Voz:** curta, direta, ocasionalmente seca. Não precisa começar toda fala com reticências. Elogio específico vale mais que grande declaração.

**Evitar:** soar igual a Silver, hostilidade gratuita, tratar Lillie como incapaz, dar ordens a todos por ser protetor.

> **GLADION**  
> Take the opening.  
> Silvally and I have your back.

### Anabel

**Base:** comanda a força-tarefa de UBs e se preocupa tanto com pessoas quanto com as criaturas. Sua história de Faller não equivale a conhecer tudo sobre Ultra Space.

**Aqui:** sabe de sua condição, como já aprovado no projeto. Quer encerrar a crise sem abandonar ninguém. Sente a abertura próxima de rupturas, mas instrumentos e observações continuam necessários.

**Progressão:** coordena proteção; em Cherrygrove revela uma informação pessoal relevante; antes de New Bark explica seus limites; no altar formula a captura como objetivo e mantém a rota de retorno por um meio visível.

**Voz:** instruções curtas, perguntas objetivas e cuidado sem condescendência. Em conversa tranquila pode admitir algo pessoal sem virar um monólogo.

**Evitar:** radar de alcance crescente sem regra, leitura da mente de Necrozma, chamar-se inútil, comentários sobre inventário quando nada impede o evento, garantias impossíveis de retorno.

> **ANABEL**  
> We capture Necrozma.  
> We will need its help to stabilize the rifts.

### Looker

**Base:** teatral e às vezes excêntrico na linguagem, mas dedicado à investigação e às pessoas.

**Aqui:** reúne testemunhas, organiza evacuações, mantém contato entre cidades e registra o que o grupo ainda precisa explicar. Sua humanidade aparece no que prioriza, não na repetição literal de “o relatório pode esperar”.

**Progressão:** de ocorrências isoladas a uma investigação integrada. No altar, coordena comunicação, recuperação e retirada; não sai do problema por achar que “não é assunto de polícia”.

**Voz:** uma cerimônia curta ou humor discreto entre momentos tensos. No perigo, fala simples. Reconhece competência sem precisar ridicularizar alguém antes.

**Evitar:** arquivos como bordão, incompetência para engrandecer Kukui, humilhar Gold/Crystal, chamar-se decorativo.

> **LOOKER**  
> The road is clear.  
> Bring everyone through this way.

### Kukui

**Base:** entusiasmado, informal, pesquisador de movimentos e treinador experiente; está ligado à criação da Liga de Alola.

**Aqui:** observa como as criaturas se movem, atacam e reagem. Sua contribuição é tornar um fenômeno estranho em algo que o grupo consegue enfrentar. Também oferece familiaridade e calor a Lillie e Gladion.

**Progressão:** em Cherrygrove lê a ameaça pelo comportamento; depois conecta sua observação aos registros de Elm; no altar mede a resposta do parceiro e ajuda a operar o plano.

**Voz:** contrações naturais, incentivo e vocabulário de batalha. “Yeah” ou “cousin” ocasional, sem preencher toda caixa. Uma descoberta pode animá-lo; a presença de perigo muda seu tom.

**Evitar:** piada durante pedido de socorro, instrumentos mágicos, prever arquivos que nunca leu, dar uma palestra sobre seu currículo no meio de um ataque.

> **KUKUI**  
> Watch the sand, not the flash.  
> There! That's where it's moving!

### Mãe, Elm, Clair, Pryce e Gold/Crystal

| Pessoa | O que quer nesta cena | Como isso vira ação e voz |
| --- | --- | --- |
| Mãe | Ver o filho voltar e ajudar sua cidade | Organiza abrigo, entrega o que falta e aceita recuar; fala de sua própria experiência sem diagnosticar Lusamine |
| Elm | Entender um fenômeno com os dados que possui | Admite limites, compara registros, protege o laboratório; não se declara inútil por não conhecer UBs |
| Clair | Impedir que a ameaça atravesse sua cidade | Orgulhosa e incisiva; reconhece o jogador que já a enfrentou, sem agir como se Lance precisasse apresentá-lo |
| Pryce | Proteger moradores e manter a rua defensável | Poucas palavras, experiência prática, respeito demonstrado por confiar na ideia de Lillie |
| Gold/Crystal | Defender a cidade e os vizinhos | Já atua quando o jogador chega; conhece rotas e tem Azumarill; coopera sem implorar por reconhecimento |

**Identidade importante:** o roteiro de New Bark especifica **Gold/Crystal**, não Silver. Não aplicar a personalidade de Silver nem renomear esse personagem. Na reescrita final, carregar o nome e o gênero efetivamente usados pelo projeto. Nos exemplos abaixo, `{RIVAL_NAME}` significa essa identidade dinâmica; não é uma string técnica confirmada.

Não há fonte canônica que valide o arco particular de exclusão inventado para esse rival no script. Removê-lo não exige substituir por outro passado inventado.

## 4. Regras do fenômeno: poucas, visíveis e consistentes

### Base canônica e licença do hack

Necrozma tem relação com absorção de luz e formas ligadas a Solgaleo/Lunala. **Absorver nove UBs e alcançar a forma Ultra por essa rota é uma regra autoral deste hack**, não um acontecimento padrão de SM/USUM.

A versão proposta preserva esse espetáculo, mas fixa limites:

1. O altar é um ponto de conexão já enfraquecido. Necrozma o usa como acesso a Johto. Não criar uma conspiração nova da Aether nem responsabilizar o jogador pelo ovo.
2. Ao puxar luz por uma ruptura, ele também desloca UBs. Elas reagem ao ambiente e à instabilidade; não são um exército consciente obedecendo ordens.
3. As absorções mantêm as UBs contidas numa ligação de energia. Elas não desaparecem da história. A sobrevivência começa a ser detectada em Mahogany e é confirmada em New Bark.
4. Mais energia aumenta a potência de Necrozma, mas sua luz continua oscilando. Esse padrão é mostrado antes do clímax.
5. Solgaleo/Lunala consegue reduzir brevemente a oscilação de uma fenda; não vence Necrozma automaticamente e não funciona como reserva infinita de energia.
6. As reações opcionais ao parceiro enriquecem as missões. Nenhuma pista indispensável depende de o jogador tê-lo levado antes da reunião.
7. O altar concentra a ligação que o grupo precisa interromper. Isso torna possível uma operação planejada, diferente dos confrontos improvisados nas ruas.
8. Depois da derrota, as UBs são libertadas; Necrozma volta à forma normal, é capturado e ajuda a estabilizar o que resta.

**Não adicionar:** telepatia universal das UBs; cura infinita; humanos segurando portais por poder novo; nove absorções como número místico; Necrozma como estrategista que planejou cada escolha do jogador.

### Por que lutar nas cidades, se isso facilita a absorção?

Porque as UBs estão avançando sobre pessoas e edifícios. O grupo não pode deixá-las agir. Depois de Blackthorn, porém, já tenta impedir a intervenção de Necrozma: separa fontes, prepara captura, mantém cobertura e mede a retirada. As tentativas têm ganhos, embora não resolvam a origem.

A equipe pode reconhecer que Necrozma aproveitou o enfraquecimento das UBs. Não deve concluir que salvar moradores foi um erro ou culpar o jogador por vencer as batalhas que o próprio jogo exigiu.

### Por que a captura comum das UBs não resolve as missões?

Proposta: enquanto ligadas à ruptura, o fluxo impede que a contenção se complete. Isso precisa ser mostrado numa tentativa curta, sem consumir item do jogador. Não basta bloquear a opção de captura na interface e presumir que a ficção explicou.

Ao final, o grupo rompe essa ligação e retira Necrozma da fonte de instabilidade. A Beast Ball é um recurso do plano, não um item anunciado depois de tudo terminar. Seu sucesso roteirizado com Necrozma é uma decisão da cena; não implica que ele seja uma UB ou que a Ball tenha bônus canônico contra ele.

## 5. Progressão da investigação

| Etapa | Pergunta | Descoberta verificável | Decisão que muda a próxima etapa |
| --- | --- | --- | --- |
| Blackthorn | O que está abrindo as fendas? | Necrozma abre a passagem e recolhe as UBs | Identificar a criatura, comparar sinais e preparar contenção |
| Mahogany | Podemos cortar o fornecimento de energia? | A conexão pode ser interrompida; os sinais das UBs persistem após a absorção | Procurar uma janela de captura e sinais que indiquem para onde ele retorna |
| Cherrygrove | Podemos agir antes que ele recolha tudo? | Há um intervalo observável; a captura falha enquanto a ligação está ativa | Cruzar a direção de retirada com os registros de Elm; reunir apoio |
| New Bark | Conseguimos controlar várias rupturas e impedir a absorção? | A forma Ultra emerge, mas não se mantém estável; as nove assinaturas continuam distinguíveis | Parar de perseguir ocorrências e agir no ponto comum: o altar |
| Olivine | Como chegar, trazer todos de volta e retirar Necrozma? | Dados convergem; parceiro demonstra estabilização breve | Aprovar captura, retorno e funções de cada participante |
| Altar | O grupo consegue cumprir esse plano junto? | A ligação é rompida; Necrozma e UBs são recuperados | Estabilizar as passagens e iniciar expedições supervisionadas |

## 6. Blackthorn — confiança sob pressão

**Função:** apresentar uma ameaça que o jogador ainda não compreende e mostrar que Gladion já confia nele.

### Sequência proposta

1. Briefing em Olivine: Clair está mantendo a passagem livre, há moradores abrigados e o grupo precisa de apoio. Evitar um manual de Ultra Space antes de qualquer ocorrência.
2. Ao chegar, Clair e Kingdra já estão protegendo a cidade. Ela reconhece o protagonista: “Champion now? Good. I could use the help.” Não precisa fingir surpresa com suas habilidades.
3. Um ataque de Kingdra obriga Necrozma a mudar de posição, mas não rompe sua proteção. Clair continua útil; não repetir “nenhum golpe funciona” em todas as cidades.
4. Necrozma abre a ruptura. A música muda antes de as UBs avançarem. Buzzwole pressiona a linha de frente; Pheromosa tenta passar pela lateral. Comportamentos diferentes, não dois sprites fazendo o mesmo movimento.
5. Silvally intercepta a aproximação. Gladion chega e distribui a defesa com o jogador. O resgate é rápido, sem rodada de apresentações.
6. Escolha do alvo e boss. Clair mantém Necrozma afastado das casas; Looker protege a saída; Anabel acompanha a ruptura.
7. Necrozma aproveita a abertura após a luta e absorve as duas UBs. É a primeira ocorrência: surpresa completa é apropriada aqui.
8. Se Solgaleo/Lunala estiver na equipe, sai da Ball e encara a ruptura. A borda fica estável por um instante. Necrozma reage ao parceiro e recua; ninguém conclui “ele tem medo” como certeza.
9. Necrozma parte. Clair verifica a cidade. Gladion fornece a identificação que conhece ou uma pista concreta para confirmá-la. A confirmação pode acontecer no briefing seguinte, mas não ficar artificialmente retida até o final.
10. Depois de a rua estar segura, preservar a entrega de Type: Null em uma conversa breve.

### Type: Null: corrigir a continuidade sem remover o presente

O documento consolidado distingue o parceiro da jornada de Gladion, que já evoluiu, e outro indivíduo recebido pelo jogador em Blackthorn. O texto precisa manter essa distinção. Não recontar a história de abandono como se o Silvally visível fosse voltar a ser Type: Null.

Proposta de encenação: mostrar brevemente o Type: Null do presente aproximando-se do jogador. Gladion observa sua escolha; não precisa declarar que “assistiu à batalha” se ele nunca apareceu na tela. A procedência aprovada pode ser resumida sem abrir outra investigação.

### Tom de diálogo

> **GLADION**  
> Pick one. We'll take the other.
>
> **CLAIR**  
> Kingdra and I will keep Necrozma here. Go!

A fala da Clair usa o nome apenas depois de ele ter sido identificado em cena; antes, referir-se à criatura. A ordem de conhecimento governa a versão final.

**Ganho:** cidade protegida, parceiro de Gladion demonstrado em ação, primeira regra do fenômeno registrada. O fim não é simplesmente “falhamos”.

## 7. Mahogany — observar, tentar, corrigir

**Função:** dar a Lillie uma contribuição intelectual e tática própria, com Pryce como colaborador experiente.

### Espaço e entrada

A cena atual comprime monstros grandes, treinadores e uma parede de gelo numa faixa estreita. Reorganizar em três áreas: abrigo/apoio junto ao Ginásio; frente de Lillie e jogador; zona das UBs. Reservar corredores separados para Ninetales, Mamoswine e o parceiro do jogador. Reduzir o número de pessoas simultaneamente em quadro depois da evacuação.

Não fixar coordenadas novas neste planejamento sem conferir o mapa atual. A aceitação visual exige enxergar quem bloqueia quem, inclusive com a caixa de diálogo aberta.

### Sequência proposta

1. Looker informa apagões e avistamentos. Não anuncia Lillie; ela é encontrada ajudando Pryce.
2. Reencontro curto: ela reconhece o jogador e apresenta algo observado, sem enumerar as três batalhas que tiveram.
3. Pryce termina a evacuação. A interação com o morador e sua lâmpada pode ficar em duas ou três caixas, como traço local, não um discurso antes da emergência.
4. Xurkitree drena a rede. Celesteela ocupa a saída e recebe um fluxo visível através da ruptura. Não afirmar que as duas criam energia infinita entre si.
5. Lillie propõe afastá-las. O jogador vence a primeira rodada curta, mas um pulso da ligação faz a UB se reerguer. Mostrar a fonte também oscilar: a recarga tem custo e origem.
6. Ela identifica que a ligação continua atravessando a rua. Pede a Pryce uma barreira no trajeto do fluxo. Mamoswine cria a parede; Ninetales protege a equipe durante a execução. Aurora Veil não é descrito como material de construção.
7. Mostrar a corrente falhar contra a barreira e a mudança na reação das UBs. A fala explica apenas o necessário.
8. Anabel cura a equipe durante a proteção. Segunda rodada sem recarga narrativa. Preservar o desafio de duas rodadas, sem rebalanceamento numérico nesta etapa.
9. Necrozma intervém de outro ângulo, recolhendo as duas. O grupo tenta alcançá-lo; o gelo que funcionou contra a ligação local não é uma prisão universal para ele.
10. Anabel detecta as duas assinaturas ainda presentes no sinal dele. Lillie pede que não as deem por perdidas. Essa é a descoberta que paga o resgate final.

> **LILLIE**  
> They're farther apart, but the current is still reaching them.
>
> **LILLIE**  
> Mr. Pryce, can you block that gap?
>
> **PRYCE**  
> Mamoswine. With Ninetales.

Não usar a certeza “gelo não conduz corrente” como fundamento científico. É um teste de uma barreira no fenômeno fictício; a tela mostra que funcionou naquele ponto.

**Solgaleo/Lunala:** quando sua reação for mencionada, fazê-lo aparecer e tentar conter a oscilação da ruptura. Se estiver ausente, instrumentos e observações entregam a descoberta obrigatória.

**Ganho:** Lillie aprende corrigindo o plano; Pryce protege e ajuda; o grupo descobre que as UBs podem estar vivas.

## 8. Cherrygrove — ler o movimento, revelar um limite

**Função:** mostrar Kukui em ação e tornar pessoal a preocupação de Anabel com o retorno.

### Sequência proposta

1. Kukui avisa a polícia. O briefing reconhece que ele é pesquisador e treinador experiente. O humor pode ser que ele já enviou anotações demais, não que ninguém sabe quem ele é.
2. Na praia, ele mostra marcas sucessivas na areia ou no raso: Stakataka se aproxima enquanto Blacephalon produz flashes. A primeira hipótese ainda pode estar incompleta.
3. Necrozma abre a passagem. Anabel reage um pouco antes do instrumento. Uma fala e um movimento bastam.
4. Primeiro flash: Stakataka aparece mais perto. No segundo, Kukui percebe o deslocamento no chão ou na água e manda Incineroar interceptá-lo. Não afirmar teleporte e depois combatê-lo como simples distração.
5. O jogador participa da separação. Se escolher Blacephalon, corta a cobertura de flashes; se escolher Stakataka, Kukui e Incineroar mantêm Blacephalon ocupado para não encobrir o avanço.
6. Necrozma emite um pulso na direção da linha. Anabel puxa o jogador para fora da trajetória. Sem parceiro, o alvo pode ser a frente de combate; não inventar que o protagonista é Faller. Com Solgaleo/Lunala, sua presença fornece um motivo específico para o interesse de Necrozma.
7. Após o deslocamento, o jogador vira explicitamente para a ação. Anabel verifica se ele está bem. Não deixar a animação de recuo determinar o olhar pelo resto da cutscene.
8. Depois do boss, Anabel tenta conter uma UB. A energia da ruptura impede a captura; Necrozma recolhe as duas. Kukui registra a direção e a duração do pulso. O grupo tentou algo novo e viu por que falhou.
9. Fora da emergência, Anabel revela ser Faller em poucas caixas. O restante fica para o briefing seguinte, sem contar a mesma história duas vezes.
10. Kukui pede a Elm registros de anomalias para comparação. Não prevê que alguém escreveu “sensor quebrado” num caderno que ainda não leu.

> **ANABEL**  
> I've been through an Ultra Wormhole.  
> That's what they call a Faller.
>
> **ANABEL**  
> Sometimes I feel one opening before the meter reacts.  
> I still need the meter.

A vulnerabilidade está na admissão do limite. Não aumentar sua percepção para dezenas de quilômetros em New Bark apenas para intensificar a cena.

**Liga de Alola:** o convite de Kukui pode sobreviver como conversa opcional posterior. Não prometer uma região jogável que o projeto não oferece; ele pode propor uma batalha futura em Johto. Não dizer que Alola está esperando seu primeiro Campeão numa continuação que já pressupõe os acontecimentos de Alola.

**Ganho:** contramedida coerente, tentativa concreta de captura, explicação pessoal da Anabel e ligação causal com Elm.

## 9. New Bark — defender a casa do jogador

**Função:** tornar a ameaça próxima, juntar tudo que foi aprendido e mostrar que a resposta precisa mudar de escala.

### O rival entra como aliado, não como candidato

Gold/Crystal já verificou casas e está mantendo uma passagem segura com Azumarill. Anabel pergunta o que ele viu e atribui uma tarefa. Ninguém precisa ser cruel para Lusamine ganhar uma oportunidade de ser gentil.

Seu valor é duplo: conhece o lugar e responde rápido. A participação não depende de uma vaga artificial num plano de “três criaturas exigem quatro pessoas”.

> **{RIVAL_NAME}**  
> The houses are clear. Elm still has people inside.
>
> **ANABEL**  
> Keep the path to the lab open. We need it.
>
> **{RIVAL_NAME}**  
> Got it. Azumarill, with me.

### A mãe e Lusamine

Preservar a conversa, mas retirar a longa interpretação psicológica. A mãe observa Lusamine tentando assumir todas as frentes. Ela não conhece intimamente sua família e não precisa falar como se conhecesse.

> **LUSAMINE**  
> I can keep them away from your child.
>
> **MOM**  
> Then help us. {PLAYER} knows what they're doing.
>
> **MOM**  
> I'll take everyone inside. You won't have to watch this door too.
>
> **LUSAMINE**  
> Thank you. Anabel, where do you need me?

A mãe também age: termina sua tarefa e entra no abrigo. Sua coragem não depende de permanecer atrapalhando na rua. Lusamine aceita colaboração numa ação pequena e concreta.

### As três UBs: ameaça combinada que a tela explica

**Recomendação:** abandonar mente coletiva, ressurreição compartilhada e derrota no mesmo segundo.

| UB | Comportamento proposto | Como piora a situação das outras | Resposta |
| --- | --- | --- | --- |
| Kartana | Corta cercas e passa rapidamente entre ruas | Abre acessos que a equipe tentava manter fechados | Conter seu corredor e impedir que alcance o abrigo |
| Guzzlord | Avança sobre o caminho e consome obstáculos | Desfaz bloqueios e força todos a mudar de posição | Atrair sua atenção para uma faixa já evacuada |
| Nihilego | Deriva para a área de pessoas e Pokémon | Sua aproximação obriga a defesa a recuar para os outros dois | Manter distância e uma cobertura dedicada |

Isso é uma interação tática autoral entre comportamentos, não uma habilidade canônica secreta. Evitar afirmar um efeito específico de veneno sobre outras UBs se ele não for mostrado nem necessário.

### Sequência completa

1. Briefing: Elm comparou seus registros com Kukui; três perturbações convergem para New Bark. A condição de Faller da Anabel é retomada apenas se acrescentar informação. As leituras, não um poder novo, localizam o incidente.
2. Chegada: rival trabalhando; mãe organizando abrigo; Elm acompanhando instrumentos. Lusamine está ajudando, sem entrada em forma de confissão.
3. Aparição das três, com música de ameaça já ativa. Cada uma demonstra seu comportamento uma vez.
4. Azumarill intercepta Nihilego para abrir tempo de retirada. Anabel reconhece isso com uma instrução útil, sem discurso sobre idade ou credenciais.
5. Conversa breve entre mãe e Lusamine; civis saem da frente. A ação não fica congelada para um debate familiar longo.
6. O grupo divide as frentes. O jogador escolhe a UB; Lusamine e Anabel contêm as restantes. Preservar a preferência de Lusamine por enfrentar Nihilego quando a escolha permitir, sem tratá-la como propriedade ou dívida pessoal.
7. Gold/Crystal e Azumarill mantêm o corredor e ajudam a isolar o alvo escolhido. Essa atuação é de overworld; não prometer batalha dupla se o sistema continua sendo boss simples.
8. A batalha do jogador rompe a pressão principal. As outras frentes concluem sua contenção. Não exigir sincronização literal de uma batalha por turnos com duas batalhas invisíveis.
9. O grupo já espera a intervenção de Necrozma. Lusamine prepara contenção; Anabel acompanha a ligação; o rival protege o recuo. Todos agem sobre o que aprenderam.
10. Necrozma recolhe as três antes que o isolamento se complete. A descarga é maior do que nas cidades anteriores. Sua forma Ultra aparece, com sprite correto, silhueta distinta e tempo de leitura.
11. A equipe recua sob a pressão. Não impor uma batalha jogável para o jogador perder automaticamente. Também não transformar o rival em alguém que ataca sem pensar para provar que merece estar ali.
12. Se Solgaleo/Lunala estiver na equipe, sai da Ball, protege a linha e estabiliza brevemente a borda da ruptura. Sem ele, a retirada funciona pela cobertura e pela barreira preparada; a oscilação da forma Ultra continua visível.
13. Necrozma perde estabilidade e retorna pela passagem. Não vai embora apenas porque o roteiro precisa poupar a cidade. Elm registra o ponto comum da retirada e as nove assinaturas.
14. Rescaldo: pessoas protegidas, criaturas ainda não recuperadas, transformação confirmada, destino localizado. A vitória local tem valor; a crise maior permanece.

> **ELM**  
> The nine signals are still there.  
> They're inside the same reading.
>
> **ANABEL**  
> Then we can still bring them back.
>
> **LUSAMINE**  
> We'll need to reach Necrozma before it opens another rift.

### Fecho emocional

O rival verifica Azumarill e retoma o abrigo. Looker agradece pelo corredor mantido. A mãe chama o jogador para descansar quando puder; “I'll leave the light on” pode ficar, porque pertence à situação concreta.

Lusamine pede que chamem Lillie e Gladion porque o plano exige compartilhar informações e ouvir a decisão deles. Não faz uma convocação possessiva nem retém a identidade de Necrozma como grande segredo.

**Ganho:** New Bark continua sendo o momento mais grave, mas também prova que o grupo evoluiu. A crise não apaga o valor das quatro batalhas do jogador.

## 10. Olivine — transformar evidência em plano

**Função:** responder as dúvidas necessárias para o clímax e permitir que os personagens discordem sobre decisões reais.

Cena principal em cinco blocos curtos; detalhes pessoais ficam em conversas opcionais na sala.

1. **Looker:** os moradores estão seguros e os registros apontam para o altar. Mostra a convergência num mapa, sem repetir as quatro missões em prosa.
2. **Kukui:** em todas as absorções, a energia sobe e volta a oscilar. O aumento de potência não resolve o problema. Elm forneceu o registro longo que permite comparar os incidentes.
3. **Lillie:** as assinaturas das UBs não desapareceram. O plano precisa recuperá-las, não apenas encerrar as rupturas.
4. **Lusamine:** apresenta o conhecimento relevante de Aether, admite o que ainda é hipótese e oferece equipamento. Não diz ser a única pessoa viva com experiência do outro lado.
5. **Anabel:** define objetivo, retorno e funções. Capturar Necrozma faz parte da solução porque afastá-lo só deslocou a crise para outra cidade. Ela já providenciou uma Beast Ball com Kurt.

### O parceiro precisa demonstrar sua função

O jogador apresenta Solgaleo ou Lunala. Ele aparece no mapa e um dispositivo próximo registra estabilização breve. Caso o parceiro tenha acompanhado as missões, o grupo reconhece a repetição; caso não tenha, esta é a primeira demonstração.

Gladion pode reconhecer que veio do ovo entregue em Violet. A única informação afirmada é a que a campanha sustenta. Cortar o callback de uma advertência que não foi confirmada e a fala de Lillie dizendo que sabia de tudo.

Sem parceiro adequado, orientar de forma breve e preservar a reunião concluída. Distinguir falta de evolução de parceiro já evoluído guardado no PC; não afirmar que ele “ainda está crescendo” sem verificar.

### Preparar o recurso da Anabel

Lusamine apresenta um estabilizador portátil; Kukui e Anabel testam sua resposta junto do parceiro. É uma ferramenta ficcional proposta para o hack, não um item canônico. Sua função é manter uma passagem já aberta por tempo limitado, com operação contínua. Não abre portais sozinha e não resolve o problema de Necrozma.

Essa preparação responde ao pedido de a Anabel segurar algo e ficar ocupada durante a batalha. Sua condição de Faller orienta sua cautela; não vira um superpoder novo.

### O que cada um quer da reunião

Lusamine quer liderar a travessia; Gladion exige uma retirada concreta; Lillie exige que as UBs entrem no objetivo; Kukui quer testar a hipótese antes de arriscar a equipe; Anabel decide o procedimento; Looker torna a operação viável. O jogador e seu parceiro são o elo que permite agir.

O conflito sobre quem atravessa pode continuar até o altar, onde as condições serão verificadas. Não encerrar com Lusamine já aceitando exatamente o plano que ela vai rejeitar na cena seguinte.

## 11. Altar — aceitar uma função e cumprir o plano

### Ato I: chegada e objetivo explícito

Mostrar o altar instável com efeitos legíveis: borda irregular, partículas deslocando-se para a abertura, pulsos de luz. Não depender de narrador para explicar um efeito que a tela não mostra.

Solgaleo/Lunala aparece assim que sua reação é mencionada. Se o jogador o guardou depois da reunião, pedir que o traga antes de iniciar a parte que depende dele.

Anabel comunica cedo:

> **ANABEL**  
> I've brought a Beast Ball from Kurt.
>
> **ANABEL**  
> We need to capture Necrozma. Driving it away won't stop this.
>
> **ANABEL**  
> Your partner can hold the passage.  
> We'll need Necrozma's help to stabilize the rest.

A afirmação decorre da investigação e do teste; não é conhecimento surgido na ilha. “Único jeito” significa a solução viável que eles identificaram, não uma lei universal sobre toda fenda do universo.

### Ato II: o impasse com Lusamine

Ela ainda quer atravessar porque conhece o equipamento e teme delegar uma etapa crítica. Já aprendeu em New Bark a trabalhar com outros; agora precisa aceitar não liderar a parte decisiva.

Lillie não pede apenas que a mãe fique. Explica a tarefa que precisa dela: operar a base externa e acompanhar as criaturas resgatadas. Gladion protege a equipe dessa margem. Anabel mantém autoridade operacional.

O jogador fica livre no altar, como previsto. Falar com Lusamine inicia o duelo após confirmação; recusar permite preparar-se.

**Motivo do duelo:** Lusamine quer observar como o protagonista e sua equipe respondem sob pressão antes de entregar-lhes a travessia. Ainda é uma tentativa de controlar a decisão. O duelo não decide quem tem razão nem resolve a relação familiar por força.

### Ato III: resultado e mudança de comportamento

Vitória e derrota continuam levando adiante, com falas honestas sobre cada resultado. Empate e desistência recebem respostas próprias conforme o contrato do projeto; resultado técnico inesperado não é uma vitória fictícia.

> **LUSAMINE — jogador venceu**  
> You kept your team together.  
> I see why Anabel trusts you.
>
> **LUSAMINE — jogador perdeu**  
> Your team needs a rest. We'll see to that first.
>
> **LILLIE — convergência**  
> Mother, we still need you here.  
> Please help us bring them back.
>
> **LUSAMINE**  
> Show me the controls again, Lillie.

Essa última ação tem mais valor que anunciar “aprendi a ouvir”. A derrota do jogador não elimina seu parceiro indispensável nem a experiência acumulada. A equipe é curada; o plano segue sendo cooperativo.

### Ato IV: abertura e travessia

| Participante | Função visível |
| --- | --- |
| Jogador | Enfrentar Necrozma e executar a captura |
| Solgaleo/Lunala | Abrir a rota e responder à instabilidade; permanece visível quando age |
| Anabel | Acompanhar a travessia e operar o estabilizador interno |
| Lusamine | Operar a base externa e coordenar o acolhimento das UBs |
| Lillie e Ninetales | Proteger e acalmar os Pokémon que retornarem |
| Gladion e Silvally | Manter a saída livre e cobrir uma retirada |
| Kukui | Acompanhar variações e orientar ajustes da base |
| Looker | Manter comunicação, apoio e rota de transporte |

A aparência do dispositivo pode ser simples. O essencial é mostrar Anabel posicionando-o, segurando os controles e reagindo a seus indicadores. Uma fala curta explica por que não luta. Não chamá-la de inútil.

> **ANABEL**  
> I'll keep the stabilizer running.  
> You handle Necrozma.

### Ato V: Ultra Necrozma

O jogador já viu essa forma em New Bark. O reencontro confirma sua potência e a oscilação; não reencenar uma “primeira descoberta”.

A luta continua sendo difícil. A vantagem agora não é uma profecia nem coragem extra: a fonte de recarga foi isolada, o parceiro mantém a passagem e há suporte dos dois lados. Esses preparativos explicam por que o confronto agora pode ser vencido.

O perfil existente de fases pode ser preservado: forma Ultra enquanto há energia acumulada, forma normal quando ela se dissipa. Ajustes de barras, golpes e números ficam fora deste planejamento. Não inventar que cada parte visual do corpo é uma UB diferente se o jogo não o representa.

Derrota mantém uma nova tentativa segura. Não repetir os grandes discursos e o duelo da Lusamine. A cena de retorno deve mostrar que a equipe cumpriu a tarefa de retirada.

### Ato VI: resgate e captura — em ordem legível

1. A forma Ultra cede. Necrozma normal aparece no mesmo lugar.
2. A ligação se rompe e as nove assinaturas se separam. Mostrar as UBs atravessando para a área de acolhimento em pequenos grupos, com corte para o elenco externo se necessário. Não criar nove sprites ao mesmo tempo por obrigação.
3. Solgaleo/Lunala sustenta a passagem durante essa saída; Anabel mantém o dispositivo.
4. Looker confirma pelo comunicador que todas foram recebidas. Isso paga a investigação de Mahogany e New Bark.
5. Anabel libera a Beast Ball já preparada. O jogador a lança; mostrar trajetória, conversão de Necrozma em luz, entrada na Ball, fechamento e confirmação de captura.
6. Registrar **Necrozma normal**, em Beast Ball, com o nível definido pelo projeto. O roteiro atual especifica nível 75; mantê-lo nesta proposta.
7. Confirmar a entrega antes de encerrar o evento. Nunca entregar Solgaleo/Lunala nem duplicar o parceiro usado na cena.
8. Retornar ao altar. Anabel recolhe o estabilizador; o movimento demonstra que agora é possível sair.

Uma chamada de entrega de Pokémon, isoladamente, não comunica captura. A animação é um requisito narrativo, não um acabamento opcional.

**Espaço:** checar equipe e PC antes do compromisso final. Com lugar disponível, não falar disso. Com ambos cheios, uma mensagem curta com nome de Anabel bloqueia o avanço. Se uma falha inesperada ocorrer depois da vitória, preservar a vitória e a captura pendente; não obrigar a refazer todo o boss.

### Ato VII: Necrozma ajuda a estabilizar

Depois de a captura ser confirmada, o jogador solta Necrozma num ponto seguro do altar. Ele se aproxima do parceiro. Os dois agem sobre a passagem: a luz dispersa converge, os pulsos diminuem, a borda se firma e o disco volta ao estado calmo.

A função de Necrozma precisa ser distinta: ele reorganiza o fluxo que vinha puxando pelas rupturas; Solgaleo/Lunala mantém a conexão durante o ajuste. São regras autorais preparadas pelas medições e pelo teste, não uma amizade instantânea que resolve cosmologia.

A Ball possibilitou interromper o surto e trazê-lo de volta. A estabilização acontece pela ação conjunta mostrada depois. Não dizer que uma batalha “curou para sempre” sua condição.

### Ato VIII: despedida

Encerrar com ações e poucas falas:

- Looker confirma os resgates e o retorno da equipe.
- Anabel verifica Necrozma e explica que restam conexões estáveis a investigar.
- Lillie observa uma UB acolhida, pagando sua preocupação de Mahogany.
- Gladion reconhece o trabalho do jogador sem diminuir o próprio apoio.
- Lusamine pergunta aos filhos sobre um encontro posterior; eles podem aceitar sem declarar tudo resolvido.
- Kukui volta a soar mais descontraído quando o perigo termina.

> **LUSAMINE**  
> Will you both be in Olivine tomorrow?
>
> **LILLIE**  
> I can be there in the afternoon.
>
> **GLADION**  
> I'll come by.

A família termina com um próximo encontro concreto, não com uma tese sobre perdão.

## 12. Pós-game: pessoas com tarefas e lugares

**Looker e Anabel não precisam ficar imóveis encarando a fenda.** Proposta: manter presença funcional no altar, mas em postos de apoio — Looker junto aos registros e à recuperação; Anabel junto ao equipamento, com pequenos percursos seguros. Nas entradas de expedição, assumem suas posições de trabalho.

Isso preserva acesso aos serviços sem exigir um sistema novo de horários. Visitas a Olivine e rotinas mais extensas são possíveis depois, desde que não removam um serviço indispensável quando o jogador precisa dele.

Lusamine acompanha o acolhimento e continua a reconstrução familiar. A Nihilego de sua revanche pode ser uma das recuperadas, como já aprovado, mas a entrega e o vínculo devem ser posteriores ao resgate mostrado. Evitar tratá-la como prêmio automático pela boa conduta de Lusamine.

Lillie continua treinando e pode encontrar Kukui na praia; Gladion volta a Cianwood; o jogador encontra a mãe e Gold/Crystal com reações curtas sobre New Bark. Essa volta à cidade importa para o encerramento pessoal.

**Portal diário:** as rotas residuais explicam expedições futuras; não significam que o clímax falhou. Não exigir que Necrozma ou Solgaleo/Lunala fiquem presos ao time para sempre. A estabilização do altar persiste.

O design herdado contém conflito entre “uma entrada por dia” e “loop sem restrição de horário”. Esta proposta não resolve economia ou frequência do loop; isso deve ficar no documento próprio. A história não precisa prometer um uso diário se a regra final ainda vai ser revista.

## 13. Regra absoluta de nomes nas caixas

**Todo diálogo tem identificação do falante acima da message box, em todas as páginas e em todos os ramos. Escrever `LUSAMINE:` dentro do texto não atende à regra.**

Abrange cenas obrigatórias, NPCs opcionais, menus SIM/NÃO, pós-batalha, derrota, empate, desistência, retry, entrega, bloqueios e pós-game. Inclui mãe, marinheiro, moradores e Gold/Crystal.

| Conteúdo | Identificação |
| --- | --- |
| Personagem conhecido | Nome efetivo do personagem |
| Gold/Crystal | Nome dinâmico correto; nunca `NONE` |
| Morador sem nome próprio | Rótulo consistente, como `RESIDENT` ou `SAILOR` |
| Pokémon emitindo fala/cry acompanhado de texto | Espécie ou apelido conforme padrão do projeto |
| Narração realmente necessária | Proposta: `NARRATOR`, sem herdar o último NPC |
| Notificação de sistema | Proposta: `SYSTEM`, sem herdar o último NPC |
| Bilhete | Proposta: `NOTE`, ou autor identificado quando a caixa representa sua mensagem |

Usar rótulos explícitos também para narração e sistema é a solução proposta para uma interface sempre identificada. Isso não autoriza deixar diálogos sem nome. Preferir eliminar narração redundante em vez de encher a cena de caixas `NARRATOR`.

Após toda batalha, reestabelecer explicitamente o falante antes da primeira mensagem. Para o bug da Lusamine, validar nome e janela no retorno de **todos** os resultados, não só na vitória. Variáveis de texto reutilizadas, reinicialização de janela e estado do falante são pontos a inspecionar, não causas já diagnosticadas.

## 14. Regras de diálogo e callbacks

### Conversa natural

Uma caixa deve cumprir uma intenção: orientar, perguntar, responder, reconhecer, discordar ou decidir. Uma intervenção normalmente cabe em uma ou duas frases. Informações maiores são divididas por reação ou ação, não por monólogos arbitrariamente paginados.

Durante perigo, comando → ação → resultado. Discussões pessoais ficam antes ou depois. Não fazer todos verbalizarem a mesma descoberta. Se a animação mostra aproximação, não acrescentar três pessoas dizendo que algo se aproximou.

Não fixar contagem de caracteres sem medir fonte, janela e substituições reais. `{PLAYER}`, nomes dinâmicos e apelidos podem quebrar uma linha que parecia curta no Markdown.

### Registro de continuidade

| Callback | Uso recomendado |
| --- | --- |
| Ovo entregue em Violet | Gladion reconhece o parceiro na reunião; não inventa uma frase antiga |
| Type: Null → Silvally | Mostrar iniciativa e confiança; distinguir o indivíduo do presente |
| Lillie em Goldenrod | Recuperar a postura de observar e ajustar; evitar citar um episódio inteiro |
| Dragon's Den | Sua posição própria diante da mãe paga esse desenvolvimento sem precisar nomear o teste |
| Anabel em Cherrygrove | Reaparece no cuidado com a volta; não repetir toda a revelação |
| Nove UBs | Contagem física e resgate visível, não número místico |
| Nihilego e Lusamine | Conhecimento e cautela; fusão passada não é presumida |
| Cosmog do jogador | Não é chamado de Nebby; sem procedência individual nova |

**Teste de callback:** onde aconteceu, quem estava presente e o que muda agora? Se não houver resposta, cortar. Uma lembrança opcional nunca pode fornecer a única explicação de uma ação obrigatória.

## 15. Solgaleo/Lunala na encenação

Regra do autor: **quando Solgaleo estiver na party e a cutscene mencionar sua reação ou ação, ele sai da Poké Ball e participa visualmente.** Aplicar o mesmo cuidado a Lunala, que já é alternativa aceita pelo design.

| Cena | Ação proposta |
| --- | --- |
| Blackthorn | Sai ao reagir à ruptura; encara Necrozma e estabiliza a borda por um instante |
| Mahogany | Observa o fluxo e tenta conter sua oscilação |
| Cherrygrove | Aparece antes da fala sobre seu interesse ou da reação de Necrozma |
| New Bark | Protege a linha durante o recuo e interfere brevemente na ruptura |
| Olivine | É apresentado e participa do teste de estabilização |
| Altar | Abre a passagem, participa da travessia e depois age junto de Necrozma |

Saída, posição, olhar, ação e retorno à Ball devem estar escritos no roteiro. Se já for follower, não criar uma segunda cópia. Quando o follower normal for ocultado, o ator de cutscene precisa representar o mesmo parceiro, inclusive forma e aparência aplicáveis.

Com ambos no time, usar uma regra de escolha consistente — proposta: primeiro elegível na ordem da party — e manter a identidade durante a cena. Conferir novamente após batalha se uma evolução puder ter ocorrido. Não mostrar Solgaleo a partir de um Cosmog/Cosmoem que ainda não evoluiu.

## 16. Música e linguagem visual

### Trilha por estado dramático

| Momento | Regra |
| --- | --- |
| Cidade sob investigação | Ambiente contido, sem triunfalismo |
| Ruptura começando | Retirar a música alegre antes da aparição |
| UBs presentes | Tema de ameaça mantido durante movimentos, menus e diálogos |
| Batalha | Tema de boss apropriado |
| Retorno do boss com perigo ainda presente | Retomar tema de ameaça, nunca cidade alegre |
| Absorção / forma Ultra | Acento próprio, sem fanfarra de missão concluída |
| Cidade realmente segura | Transição curta e retorno ao tema local |
| Captura final | Confirmação de captura, seguida de resolução calma |

O roteiro de Cherrygrove já menciona `MUS_DP_LEGEND_APPEARS`; o feedback de jogo continua sendo autoridade sobre o problema observado. Aplicar a mesma revisão às quatro implementações, incluindo restauração após batalha, retry, save/load e noite.

A branch consultada declara `MUS_DP_LEGEND_APPEARS`, `MUS_PL_GIRATINA_APPEARS_1`, `MUS_PL_GIRATINA_APPEARS_2` e `MUS_PL_VS_GIRATINA`. A existência da constante não prova que a faixa está habilitada no build atual ou que é a melhor escolha auditiva. Ouvir no jogo antes de fechar o cue sheet. Não inventar uma constante de tema de Ultra Beast.

### Rift mais bonito e legível

Direção proposta em pixels do próprio jogo: centro profundo azul/roxo, contorno claro irregular, dois ou três estados de pulsação e partículas convergindo. Na instabilidade, a borda oscila; após estabilização, fica regular e mais lenta. Sol e Lua mudam os acentos de cor sem mudar a função.

Reservar contraste para os personagens e para a boca da passagem. Evitar depender de sucessivos flashes de tela inteira para toda ação. A captura precisa de animação específica; a absorção precisa de direção; a travessia precisa de entrada e saída reconhecíveis.

Isso é direção de arte, não um asset pronto nem um tileset já validado.

## 17. Verificação de Ultra Necrozma e limites da auditoria técnica

Consulta ao repositório `MicaelZonta/soulgold`, branch `soulgold-custom`, árvore `433462e0c79cf7263bc2a63b318eb45ae606962d`, em 25/09/2026.

**Sim, o projeto contém arquivos próprios de Ultra Necrozma**, incluindo:

- `graphics/pokemon/necrozma/ultra/front.png`
- `graphics/pokemon/necrozma/ultra/back.png`
- `graphics/pokemon/necrozma/ultra/overworld.png`
- `graphics/pokemon/necrozma/ultra/overworld_normal.pal`
- `graphics/pokemon/necrozma/ultra/overworld_shiny.pal`

O registro de `SPECIES_NECROZMA_ULTRA` em `src/data/pokemon/species_info/gen_7_families.h` referencia front/back/paletas próprios. O bloco de overworld usa `sPicTable_NecrozmaUltra`, tamanho declarado `SIZE_32x32`, e está sob `#if OW_BATTLE_ONLY_FORMS`. Nessa árvore, `include/config/overworld.h` define **`OW_BATTLE_ONLY_FORMS FALSE`**.

**Conclusão delimitada:** há asset e ligação condicional, mas a configuração consultada não inclui esse bloco de overworld. Isso é um ponto concreto de investigação para a aparência errada; não prova sozinho qual fallback a versão jogada usou. Não houve inspeção visual dos PNGs nem execução da ROM nesta etapa.

Não recomendar ligar todas as formas de batalha indiscriminadamente: para a implementação, avaliar um ator específico de cena ou habilitação seletiva, com medição de memória.

**Defasagem importante:** no commit consultado, `SunMoonAltar/scripts.inc` ainda contém o altar em esqueleto e `UltraSpaceArena/scripts.inc` apenas o retorno pelo rift. Portanto, não corresponde à implementação de clímax descrita no anexo e jogada pelo autor. Não é possível diagnosticar nela a entrega de Solgaleo, o crash do mapa ou a tela branca como se fosse o código atual.

### Backlog técnico vinculado à história

| Relato do autor | Contrato esperado | Inspeção necessária na versão realmente jogada |
| --- | --- | --- |
| Música errada nas quatro missões | Ameaça audível desde a aparição até o encerramento | Chamadas de BGM, faixa habilitada e restauração pós-batalha |
| Mahogany apertada | Corredores e ações legíveis com texto aberto | Mapa, câmera, posições, colisões e orçamento de objetos |
| Protagonista não vira em Cherrygrove | Reorientar antes de retomar combate/diálogo | Último movimento de recuo, direção explícita e lock de olhar |
| Solgaleo citado mas invisível | Ator aparece antes da reação descrita | Spawn, flags, follower ocultado, party e espaço na cena |
| Nomes ausentes ou Lusamine corrompida | Nome correto acima de toda caixa | Estado do falante, buffers e retorno de todos os resultados |
| Ultra com aparência errada | Ultra distinto em New Bark e arena | Espécie, gráfico do objeto, paletas, opções e fallback |
| Recebe Solgaleo ao vencer Necrozma | Recebe Necrozma normal em Beast Ball uma vez | Parâmetros da entrega, buffers e ordem entre animação e registro |
| Abrir mapa no altar causa crash | Mapa e Fly funcionam de dentro e de fora | MAPSEC, página regional, índices, destino e localização de cura |
| Entrar no rift pós-boss trava em branco | Transição conclui e libera controle | Estado de história, fades, warp, callbacks, waits e scripts de entrada |
| Looker/Anabel imóveis diante da fenda | Postos de apoio e presença funcional | Posições de pós-game, interação e circulação |

São hipóteses de inspeção, não correções executadas. Os arquivos `_IMPLEMENTATION` devem receber esses contratos quando o roteiro de cada etapa for aprovado.

## 18. Ordem recomendada da reescrita

1. Fechar as regras do fenômeno e a progressão de revelações deste documento.
2. Reescrever Blackthorn e Mahogany juntos, plantando identificação, absorção e sobrevivência das UBs.
3. Reescrever Cherrygrove e o briefing de New Bark juntos, alinhando Faller e cadeia Kukui → Elm → investigação.
4. Reconstruir New Bark com seus três comportamentos, rival competente e consequência Ultra.
5. Reescrever reunião e altar como um único plano causal: preparação → divergência → cooperação → batalha → resgate → captura → estabilização.
6. Revisar falas opcionais e epílogo, removendo callbacks que ficaram órfãos.
7. Só então atualizar coreografias, música e implementações da versão atual, mantendo os bugs de bloqueio como prioridade técnica.

### Critérios para considerar a história pronta

- Cada missão tem uma pergunta, uma descoberta e uma consequência diferentes.
- Nenhum personagem omite o nome ou uma solução conhecida só para adiar a revelação.
- Cada contramedida responde ao fenômeno mostrado na tela.
- Gold/Crystal tem função real sem biografia nova de exclusão.
- Lusamine progride de uma cena à seguinte; os filhos preservam sua autonomia.
- Anabel não adquire um poder novo no clímax.
- O jogador entende por que agora pode vencer Necrozma.
- As nove UBs têm destino mostrado.
- Necrozma é capturado com animação e depois ajuda a estabilizar as fendas.
- Todos os diálogos têm nome acima da caixa; toda ação atribuída ao parceiro tem representação visual.
- O retorno a New Bark e os encontros posteriores dão encerramento aos personagens.

## 19. Fontes e rastreabilidade

### Arquivos fornecidos

`SOULGOLD_RIFT_MISSIONS_DESIGN.md`; `BLACKTHORN_ULTRABEAST_SCRIPT.md`; `MAHOGANY_ULTRABEAST_SCRIPT.md`; `CHERRYGROVE_ULTRABEAST_SCRIPT.md`; `NEWBARK_ULTRABEAST_SCRIPT.md`; `PRE_NECROZMA_ULTRABEAST_SCRIPT.md`; `ALTAR_SUN_MOON_SCRIPT.md`.

Referências mais importantes: design §3 e suas revisões; Blackthorn, absorção e presente; Mahogany, teoria/recarga/parede; Cherrygrove, sinergia/revelação/gancho; New Bark, atos 4–7; reunião, exclusividade da experiência e apresentação do parceiro; altar, disputa/captura/despedida.

### Pesquisa de personagens dos jogos

As páginas de falas foram usadas para estudar registro, prioridades e diferenças entre versões, sem reproduzir diálogos canônicos. Não usar falas de Masters listadas nas mesmas páginas como continuidade obrigatória.

- [Lusamine — falas dos jogos](https://bulbapedia.bulbagarden.net/wiki/Lusamine/Quotes)
- [Lillie — falas dos jogos](https://bulbapedia.bulbagarden.net/wiki/Lillie/Quotes)
- [Gladion — falas dos jogos](https://bulbapedia.bulbagarden.net/wiki/Gladion/Quotes)
- [Anabel — falas dos jogos](https://bulbapedia.bulbagarden.net/wiki/Anabel/Quotes)
- [Looker — falas dos jogos](https://bulbapedia.bulbagarden.net/wiki/Looker/Quotes)
- [Professor Kukui — falas dos jogos](https://bulbapedia.bulbagarden.net/wiki/Professor_Kukui/Quotes)
- [Necrozma — formas e biologia](https://bulbapedia.bulbagarden.net/wiki/Necrozma_(Pok%C3%A9mon))

### Evidência de projeto

- [Árvore consultada, commit fixo](https://github.com/MicaelZonta/soulgold/tree/433462e0c79cf7263bc2a63b318eb45ae606962d)
- [Dados de espécies da geração 7](https://github.com/MicaelZonta/soulgold/blob/433462e0c79cf7263bc2a63b318eb45ae606962d/src/data/pokemon/species_info/gen_7_families.h)
- [Configuração de overworld](https://github.com/MicaelZonta/soulgold/blob/433462e0c79cf7263bc2a63b318eb45ae606962d/include/config/overworld.h)
- [Pasta de assets de Ultra Necrozma](https://github.com/MicaelZonta/soulgold/tree/433462e0c79cf7263bc2a63b318eb45ae606962d/graphics/pokemon/necrozma/ultra)

Todas as regras novas do fenômeno e todas as falas de exemplo deste planejamento são propostas originais para SoulGold, não fatos canônicos nem alterações já implementadas.
