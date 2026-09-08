# SoulGold — Rift Missions

**Design consolidado v1 · 8 de setembro de 2026**

## 1. Objetivo e autoridade deste documento

Rift Missions é uma história adicional de SoulGold que apresenta personagens de Alola durante a campanha de Johto, desenvolve uma investigação de Ultra Beasts após a Elite Four e termina em um sistema permanente de expedições com batalhas e capturas de lendários.

Este documento consolida as decisões mais recentes da conversa. É uma especificação de design, não um relatório de implementação: nenhuma mecânica, mapa, disponibilidade de Pokémon ou capacidade do engine foi validada no código para esta entrega. O repositório público pode não refletir as alterações locais do projeto.

As seções de conteúdo estabelecido são a referência para a execução. Recomendações técnicas e pendências são identificadas separadamente; não devem ser confundidas com novas decisões aprovadas.

## 2. Estrutura geral

1. Apresentar Lillie, Gladion e Kukui durante a campanha normal.
2. Mostrar uma ruptura em Blackthorn, com Buzzwole e Pheromosa em batalha dupla.
3. Após a E4, iniciar a investigação no escritório de Looker e Anabel em Olivine.
4. Concluir nove missões consecutivas de Ultra Beasts, retornando ao escritório após cada uma.
5. Reunir o elenco e desbloquear uma viagem de navio ao altar.
6. Capturar Solgaleo durante o dia e Lunala durante a noite no mesmo local.
7. Ativar o evento do Eclipse, resolver o conflito com Lusamine e enfrentar Ultra Necrozma.
8. Encerrar a história com uma despedida e manter Looker e Anabel no altar para expedições repetíveis.

O conteúdo de captura de Ultra Beasts desta história fica no pós-E4. A batalha de Blackthorn é a única aparição antecipada prevista nesta questline. Isso não instrui remover fontes de Pokémon já existentes em outros sistemas do jogo.

## 3. Elenco e arcos

### Looker

Investiga as aparições e rupturas em Johto. Deve aparecer em todas as quests de Ultra Beasts, além de participar do incidente de Blackthorn. É o fio condutor da investigação, apresenta as missões e recebe o jogador ao final de cada uma.

Sua presença não deve se limitar a entregar tarefas no escritório: os roteiros precisam incluí-lo nas ocorrências locais. O acompanhante da tabela de missões se soma a Looker, não o substitui.

### Anabel

Trabalha com Looker na investigação. Compartilha o escritório em Olivine e vende Beast Balls desde o início das missões pós-E4. Participa da preparação do evento final e, após Necrozma, permanece no altar com Looker.

Sua ligação com a Ultra Recon Squad pode explicar o fornecimento de Beast Balls, conforme a ideia discutida anteriormente. O diálogo específico ainda será escrito.

### Lusamine

A história assume uma continuidade posterior a Ultra Sun/Ultra Moon para esta adaptação. Lusamine viaja para Johto, busca reparar seus erros e reconstruir sua relação com os filhos. Participa diretamente das missões de Kartana e Nihilego.

O jogador a enfrenta uma única vez, perto do final. Para conter a crise, o grupo precisa atravessar uma passagem instável e derrotar Necrozma, mas existe o risco de não conseguir retornar. Lusamine insiste em assumir a operação sozinha, movida pela culpa e pela necessidade de reparação. O confronto com o jogador resolve essa disputa e conduz à aceitação de ajuda.

O encerramento do arco deve mostrar responsabilidade, cooperação e continuidade da relação familiar. O perigo da travessia é um conflito a resolver, não uma recompensa ou prova de valor pessoal.

### Lillie

Viaja com a mãe e está se encontrando como treinadora. Sua progressão começa com uma batalha simples no recebimento da Pokédex e reaparece no teste do Dragon’s Den. Atua nas missões de Pheromosa, Celesteela e Guzzlord.

Ela não entrega Cosmog durante a campanha. O evento associado a Cosmoem acontece depois de obter Solgaleo e Lunala.

### Gladion

Age como um rival recorrente ao longo da história, alternando desafios e cooperação. Tem um encontro em Goldenrod, oferece aquecimento opcional na Liga, luta ao lado do jogador em Blackthorn e participa das missões de Buzzwole, Xurkitree e Guzzlord.

### Kukui

Estava viajando por Kanto e decide visitar Johto ao ouvir relatos de formas de Alola na região. Sua curiosidade o envolve na investigação. Está com Oak e Lillie na apresentação inicial e participa diretamente das missões de Blacephalon e Stakataka.

Seu papel deve preservar essa motivação de pesquisador que acaba envolvido nos acontecimentos, sem exigir outra linha de quests independente.

## 4. Encontros durante a campanha

| Evento | Gatilho narrativo | Conteúdo fechado |
| --- | --- | --- |
| Primeira batalha de Lillie | Recebimento da Pokédex | Lillie está com Oak e Kukui; usa Alolan Vulpix nível 7. |
| Gladion em Goldenrod | Retorno ao Ginásio para resolver a entrega da insígnia, enquanto Whitney está chorando | Antes de o jogador entrar, Gladion sai, interpreta a situação como algo provocado pelo jogador e o desafia. |
| Lillie no Dragon’s Den | Depois de derrotar Clair, durante o teste de perguntas | Jogador e Lillie participam das perguntas. Ao final, o mestre pede uma demonstração da sintonia de ambos com seus Pokémon, levando à batalha entre eles. |
| Incidente de Blackthorn | Durante a passagem pela cidade, antes da E4 | Jogador e Gladion enfrentam Buzzwole + Pheromosa em uma batalha dupla conjunta; Looker participa da história. |
| Aquecimento de Gladion | Entrada da Liga | Gladion oferece uma batalha opcional antes do desafio da E4. |

O posicionamento exato do incidente de Blackthorn em relação ao Dragon’s Den ainda precisa ser definido no roteiro. A entrega da insígnia de Whitney e os eventos de Clair devem continuar funcionando normalmente após a inserção das cenas.

**Diretriz para Blackthorn:** apresentar a ameaça sem antecipar o ciclo de captura pós-E4. A implementação deve definir explicitamente a restrição de captura desse encontro. A falta de Beast Balls, por si só, não é uma regra suficiente para impedir capturas. O formato exato da batalha com aliado depende de verificação do engine.

## 5. Escritório em Olivine

O início formal da investigação exige que o jogador tenha concluído a E4 e visite o escritório de Looker e Anabel em Olivine. A casa ou sala exata ainda será escolhida.

O escritório concentra o briefing da missão ativa, o retorno após cada missão e a compra de Beast Balls com Anabel. As missões são consecutivas, seguindo a ordem fixa abaixo. Não é necessário criar um sistema aberto de seleção durante essa parte da história.

Cada missão deve ter uma ocorrência local, participação do elenco indicado e resolução que permita ao jogador apresentar o resultado a Looker. Os objetivos intermediários e diálogos serão desenvolvidos posteriormente; a v1 não inventa puzzles ou minijogos obrigatórios.

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

Após concluir as nove missões, o jogador retorna a Looker e Anabel. Um evento reúne todos os participantes principais: Looker, Anabel, Lusamine, Lillie, Gladion e Kukui, além do jogador.

A cena conecta a investigação ao altar e desbloqueia um navio saindo de Olivine. A primeira chegada acontece por essa viagem, dando à descoberta do local uma apresentação própria.

### Transporte permanente

- O navio permanece disponível nos dois sentidos após ser desbloqueado.
- A viagem funciona em qualquer horário.
- A primeira chegada libera o altar como destino de Fly.
- O ponto de pouso fica próximo à entrada; Fly também permite sair normalmente.
- Visitas posteriores não repetem a cena completa da expedição.
- O acesso permanece disponível no pós-Necrozma, quando o local se torna a base do conteúdo repetível.

## 8. Um único altar: Sol e Lua

Existe um único local físico. Sol e Lua são estados narrativos e visuais desse altar; não são diois destinos independentes.

| Condição | Estado | Conteúdo |
| --- | --- | --- |
| Dia, após a expedição ser liberada | Altar do Sol | Encontro com Solgaleo. |
| Noite, após a expedição ser liberada | Altar da Lua | Encontro com Lunala. |
| Após o encerramento | Altar com portal estável | Base permanente das Rift Missions repetíveis. |

O jogador captura Solgaleo e Lunala no mesmo lugar, em horários diferentes. Os limites de dia/noite devem seguir a convenção do jogo, a confirmar no código. Não há ordem obrigatória de captura definida.

Depois de ter ambos, o jogador conversa com Looker e Anabel para iniciar a próxima etapa. O teste de posse precisa ser especificado: a intenção é apresentar os dois, não presumir que apenas vê-los na Pokédex é suficiente. Uma vez desbloqueada a progressão, ela não deve ser perdida por guardar os Pokémon nas boxes.

### Cosmoem

A ideia mantida é um evento de Cosmoem associado à apresentação de Solgaleo e Lunala no altar. Não há presente de Cosmog por Lillie durante a campanha. A forma concreta de obtenção de Cosmoem — encontro ou presente — e o instante exato dentro da ativação do Eclipse ainda precisam ser definidos.

### Direção visual

A arquitetura segue as referências dos altares de USUM: paredão avermelhado, mecanismo vertical de pedra, disco celestial monumental, escadarias, plataformas e canais de água.

O acabamento deve seguir a escala e o estilo dos tilesets de SoulGold, com peças modulares compactas e pixels definidos. A paleta deve ter mais vida: terracota, pedra clara, água azul-turquesa, vegetação verde, dourado para o Sol e lilás para a Lua.

As imagens conceituais produzidas são referências visuais. Ainda não constituem tilesets de produção validados quanto a grade, paletas, metatiles, camadas ou colisões.

## 9. Lusamine e Ultra Necrozma

Com Solgaleo e Lunala obtidos, a investigação chega ao ponto de enfrentar a origem da instabilidade. A travessia até Necrozma envolve risco de a passagem se desestabilizar e impedir o retorno.

Lusamine insiste em realizar a operação sozinha. A única batalha do jogador contra ela ocorre aqui, resolvendo a disputa e levando-a a aceitar a ajuda do grupo. O roteiro deve dar espaço à reação de Lillie e Gladion sem retirar do jogador o papel no confronto final.

O jogador então atravessa para enfrentar Ultra Necrozma em uma boss battle e obter Necrozma por captura. O tratamento da forma após a batalha precisa respeitar a implementação local: não presumir que Ultra Necrozma pode permanecer como forma de armazenamento. Também não está definido se a captura ocorre durante o combate ou em uma etapa posterior.

Perder, fugir quando permitido ou derrotar sem capturar não pode bloquear definitivamente o encerramento nem a obtenção do Pokémon. O mecanismo de repetição deve ser definido antes da implementação do encontro.

Após a resolução, ocorre o evento de despedida. Looker e Anabel permanecem no altar; os destinos e falas finais dos demais personagens ainda serão escritos.

## 10. Pós-Necrozma: expedições permanentes

As rupturas continuam surgindo depois da história, mas a passagem principal está mais estável sem a interferência de Ultra Necrozma. Looker e Anabel conduzem novas missões para fechar o máximo possível dessas conexões.

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

O horário não deve restringir o loop: dia e noite controlam os encontros iniciais de Solgaleo/Lunala e a apresentação do altar. Navio e Fly mantêm o acesso fácil. A venda de Beast Balls por Anabel acompanha sua mudança para a base final.

## 11. Regras de continuidade e recuperação

Estas são diretrizes de execução para preservar a intenção do design, não sistemas adicionais de progressão.

- Distinguir encontro apresentado, batalha vencida, Pokémon capturado, missão resolvida e relatório entregue.
- Não apagar progresso concluído ao perder uma batalha posterior.
- Oferecer nova tentativa quando uma captura necessária não acontece.
- Não repetir presentes de história, como Cosmoem, por sair e entrar no mapa.
- Manter retorno seguro do altar e das expedições.
- Não exigir Solgaleo e Lunala novamente a cada expedição depois de liberar o sistema.
- Evitar cenas repetidas ou diálogos longos obrigatórios em viagens e runs posteriores.
- Manter os gatilhos de Whitney, Clair e da Liga compatíveis com a campanha existente.
- Para saves já avançados, prever como iniciar o conteúdo pós-E4 sem exigir retroceder a eventos antigos; a solução concreta depende da implementação.

## 12. Escopo técnico e assets

O projeto é uma ROM GBA de SoulGold. A execução deve verificar primeiro os sistemas locais de quests, encontros especiais, batalhas com aliado, bosses, navios, Fly, horário e persistência. Reutilizar mecanismos adequados é preferível a introduzir sistemas paralelos sem necessidade.

Já houve trabalho visual na conversa para sprites de Lillie, Gladion, Lusamine, Kukui e Looker, além de referências de Anabel. A existência dos arquivos não comprova integração na ROM. Sprites e tilesets precisam passar pela conversão e validação exigidas pelo projeto, incluindo transparência, paletas e dimensões.

O elenco recorrente e o altar compartilhado favorecem reutilização de assets. Não há orçamento de memória atualizado confirmado neste documento; medir ROM, EWRAM e IWRAM na árvore local durante a implementação. Os valores antigos discutidos não são um orçamento garantido para esta versão.

## 13. Decisões substituídas ou não confirmadas

| Ideia anterior | Situação na v1 |
| --- | --- |
| Quatro missões completas de Ultra Beasts antes da E4 | Substituída: apenas o incidente duplo de Blackthorn ocorre antes da E4. |
| Escritório em local indefinido ou Goldenrod | Substituída por Olivine. |
| Altares do Sol, Lua e Eclipse em locais separados | Substituída por um único local com estados diferentes. |
| Sol à noite e Lua de dia | Corrigida: Solgaleo de dia; Lunala à noite. |
| Blacephalon com Lillie e Stakataka com Gladion | Substituída: ambas as missões têm Kukui em destaque. |
| Kartana duplicada na lista | Corrigida: uma missão de Kartana em Kitakami, com Lusamine. |
| Hoopa como centro da história | Não faz parte deste design. |
| Lillie entregar Cosmog cedo | Removida; evento de Cosmoem após Solgaleo e Lunala. |
| Troca de formas de Solgaleo/Lunala nos altares | Não faz parte da versão atual. |
| Apenas lendários ainda não capturados no loop | Rejeitada: capturas repetidas são parte do objetivo. |
| Gladion entregar Type: Null | Ideia anterior não reafirmada na versão final; não implementar automaticamente. |

## 14. Detalhes a fechar antes de executar cada etapa

O desenho geral está fechado. As pendências abaixo completam a implementação sem alterar sua estrutura.

| Tema | Detalhe pendente |
| --- | --- |
| Escritório | Edifício e coordenadas em Olivine; presença dos NPCs antes e depois da história. |
| Campanha | Gatilhos exatos, resultado de derrota e equipes; apenas o Vulpix inicial tem nível definido. |
| Blackthorn | Posição na sequência de eventos e suporte real à batalha com aliado contra duas Ultra Beasts. |
| Missões | Objetivos locais, diálogos, pontos de encontro, níveis e parâmetros de boss. |
| Capturas | Condição de conclusão da missão e mecanismo de revanche/recuperação. |
| Beast Balls | Preço, estoque e eventual entrega inicial; nenhum valor está fechado. |
| Altar | Localização, nome no mapa, embarque, desembarque e ponto de Fly. |
| Solgaleo/Lunala | Horários conforme o engine e regra de apresentação dos dois. |
| Cosmoem | Forma de obtenção e instante exato do evento. |
| Necrozma | Equipe de Lusamine, sequência de travessia, regras de boss, captura e forma armazenada. |
| Despedida | Diálogos e posição final dos personagens além de Looker e Anabel. |
| Loop | Pools de treinadores/lendários, equipes, níveis, cura, itens, derrota, saída e eventual recompensa adicional. |
| Conteúdo total | Disponibilidade de Type: Null e Poipole/Naganadel fora desta sequência; auditar antes de adicionar fontes. |
| Texto | Idioma final dos diálogos e nomes exibidos. |

## 15. Critérios de aceite do design implementado

- [ ] Encontros de campanha preservam os personagens, locais e motivações definidos.
- [ ] Vulpix de Alola da primeira Lillie está no nível 7.
- [ ] Aquecimento de Gladion na Liga pode ser recusado.
- [ ] Blackthorn contém a batalha jogador + Gladion contra Buzzwole + Pheromosa e a participação de Looker.
- [ ] Escritório de Olivine inicia a sequência somente após a E4.
- [ ] Nove missões seguem a ordem e os acompanhantes da tabela, com Looker em todas.
- [ ] Há retorno ao escritório após cada missão e venda de Beast Balls desde o começo.
- [ ] Após Nihilego, a reunião do elenco libera o navio.
- [ ] Primeira visita desbloqueia Fly; navio permanece disponível nos dois sentidos.
- [ ] Existe apenas um altar físico, com Solgaleo de dia e Lunala à noite.
- [ ] Obter ambos permite iniciar o evento final com Looker e Anabel.
- [ ] Cosmoem tem evento único e recuperação adequada quando necessário.
- [ ] Lusamine é enfrentada apenas uma vez na história, perto da travessia final.
- [ ] Necrozma pode ser obtido e falhas não bloqueiam permanentemente sua captura.
- [ ] Despedida deixa Looker e Anabel no altar.
- [ ] Expedições têm cinco treinadores e um boss lendário capturável.
- [ ] Quinto treinador tem associação temática com o lendário e as batalhas possuem frases contextuais.
- [ ] Lendários já capturados continuam disponíveis para repetição e busca de IVs.
- [ ] Acesso ao loop funciona em qualquer horário.
- [ ] Memória, assets e persistência são validados na ROM local, sem presumir suporte pelo design.

## 16. Entrega por etapas

Uma divisão prática de implementação é: encontros de campanha; escritório e progressão das nove missões; expedição/navio/Fly/altar; clímax e despedida; loop repetível. Cada etapa deve entregar seus gatilhos, textos, batalhas e recuperação de falhas de forma verificável antes da próxima.

Esta divisão é uma recomendação de produção. Não autoriza alterar o elenco, a ordem das missões, os horários dos lendários ou a estrutura do loop.
