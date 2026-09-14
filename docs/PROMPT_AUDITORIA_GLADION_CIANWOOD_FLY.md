# Prompt de auditoria — Gladion em Cianwood / entrega de Fly

## Missão do agente

Audite o evento atual de entrega de Fly em Cianwood no checkout do SoulGold e confronte-o com o plano abaixo. O objetivo é descobrir falhas antes de implementar, fundamentando o próximo refinamento em evidências reais.

Faça somente leitura do código. A única escrita autorizada nesta tarefa é o relatório `AUDITORIA_GLADION_CIANWOOD_FLY.md`. Não implementar correções, alterar mapas, regenerar derivados, trocar/mesclar branches ou fazer commit/push. Preserve alterações do usuário. Leia as instruções aplicáveis do repositório e registre branch, SHA e estado do checkout.

Não presumir comportamento vanilla nem inventar constantes, IDs, comandos ou resultados de teste. Se houver V8 do design, use-o; o plano autocontido abaixo prevalece sobre o V7 nos pontos atualizados.

## Plano aprovado: “O caminho de volta”

1. Após os requisitos originais de Chuck para receber Fly, o jogador interage manualmente com Gladion, perto do ginásio. Ele está acompanhado do novo Type: Null e conversa com a esposa de Chuck.
2. Antes de conversa longa, movimentação ou batalha, verificar silenciosamente se a entrega já ocorreu e se é possível receber uma unidade do item correto de Fly.
3. Se não puder receber, Gladion olha para você e volta a atenção ao parceiro: “Agora não. Estou terminando um treino com ele.” / “Volte depois.” Liberar controles sem progresso. Não mencionar bolsa ou HM nesse aviso.
4. Com capacidade, a esposa de Chuck reconhece a conquista do jogador e pede que Gladion entregue a HM enquanto vai falar com o marido. Ela continua sendo a origem narrativa da recompensa.
5. Gladion comenta que Lillie contou sobre Goldenrod: primeiro a batalha, depois as flores, depois a batalha novamente. Não presumir quem venceu.
6. Ele diz que pretendia procurar treinadores fortes em Johto, mas passou uma manhã na praia acompanhando Type: Null: primeiro o parceiro recuava das ondas, depois passou a segui-las. “Foi uma boa manhã.”
7. Type: Null reconhece o jogador e se aproxima. Gladion oferece uma revanche: “Uma revanche antes de partir? Fly já é sua. A batalha é um pedido meu.”
8. Opções: aceitar ou recusar. Recusa segue diretamente à entrega; não há revanche pendente nem estado persistente de recusa.
9. Aceite: curar antes, batalhar e continuar tanto em vitória quanto em derrota. Falas diferentes; curar depois. Sem blackout nem penalidade de blackout. Não falsificar vitória.
10. Vitória do jogador: Gladion reconhece que você mudou desde Violet e que precisam de outro plano. Derrota: reconhece o trabalho da equipe e a iniciativa de Type: Null. Evitar falas que dependam de uma troca ou movimento que talvez não tenha ocorrido.
11. Entregar Fly; confirmar sucesso antes de marcar o controle existente de recebimento. Não duplicar a entrega pela esposa de Chuck.
12. Gladion pede que você diga a Lillie que estão bem e que ele ouviu a história inteira da batalha.
13. Type: Null começa a caminhar, para e olha para trás. Gladion diz “Já escolheu? Estou indo.” e se despede do jogador. O parceiro sai na frente e Gladion o acompanha.
14. Remover os dois objetos após caminhada visível, restaurar música e controles. Ambos permanecem ausentes após o recebimento. A esposa de Chuck mantém sua presença e funções normais após a encenação.

O Type: Null é outro indivíduo acolhido em Alola, não o antigo Silvally regredido. Ele permanece Type: Null nesta etapa e em Blackthorn; evolui entre Blackthorn e a Liga. Não é presente para o jogador. A cena não introduz investigação de Rift em Cianwood antes da E4.

## Restrições fechadas

- Nenhuma nova flag de história, visibilidade, conversa ou batalha concluída; nenhuma nova variável persistente ou campo de save.
- Reutilizar o controle REAL de recebimento de Fly, preservando seu significado. Não usar flags alheias ou aparentemente livres.
- Estado de vitória do treinador não é requisito para receber Fly: derrota e recusa também concluem com entrega.
- Uma entrada/ID de treinador tem custo próprio. Distinguir esse custo de novas flags de história e não prometer armazenamento zero.
- A checagem prévia de entrega deve ocorrer antes da batalha e da cena longa; confirmar sucesso novamente ao entregar.
- A equipe de Cianwood ainda não está aprovada. Auditar referências, sem inventar equipe ou níveis definitivos.
- Dificuldade única baseada no antigo Hard, conforme o autor. Não recriar Normal/Hard nem trocar de branch para buscar a versão mantida. Registrar limites da referência local quando necessário.
- Lillie em Goldenrod e Gladion em Violet já foram informados como implementados. Inspecionar como referências sem reimplementá-los.
- O alvo do projeto é New Game; não criar migração de saves antigos. Reentrada e saves da própria campanha atual continuam relevantes.

## 1. Evento original e dependências

- Localizar mapa, objeto, script-fonte, derivados e função efetivamente executada na entrega.
- Identificar item, quantidade, requisitos e controle real de recebimento. Informar valores/símbolos encontrados com evidências.
- Rastrear todas as leituras, sets, clears e resets desse controle, inclusive inicialização e scripts compartilhados.
- Distinguir recebimento da HM, permissão de uso de Fly e registro de destinos no mapa.
- Identificar serviços, falas, posição e comportamento da esposa de Chuck que precisam ser preservados.
- Examinar Fly já recebido, item presente sem controle marcado e controle marcado sem item presente. Distinguir estados alcançáveis normalmente de estados de debug.

## 2. Reutilização sem estado persistente adicional

- Demonstrar a condição de presença/ausência de Gladion e Type: Null usando apenas o mecanismo existente.
- Verificar se ambos podem compartilhar a flag do objeto ou se precisam de script de carregamento suportado pelo projeto.
- Verificar se marcar recebimento faz desaparecer os objetos antes da caminhada.
- Garantir que nenhum outro NPC desapareça e que a esposa não seja escondida permanentemente.
- Identificar temporários livres e suas colisões com scripts do mapa, cura, batalha e serviços comuns.
- Explicar seu ciclo de vida: retorno da batalha, recarga do mapa, saída e load do save.
- Se não for viável sem novo estado persistente, informar o impedimento e propor a menor adaptação de fluxo. Não alocar estado para contornar o requisito.

## 3. Checagem e entrega de Fly

- Determinar se falta de espaço é realmente possível para o item/bolso de Fly nesta configuração.
- Comparar a checagem prévia com a rotina efetiva de entrega: validam exatamente as mesmas condições?
- Examinar duplicatas, limites de quantidade e estados inconsistentes.
- Identificar condições que podem mudar entre checagem e entrega, inclusive efeitos da batalha sobre inventário.
- Verificar como a entrega retorna sucesso/falha e quais chamadas podem sobrescrever o resultado.
- Falha nunca pode marcar recebimento, remover personagens ou duplicar recompensas.
- Examinar retomada somente da entrega na mesma visita após falha excepcional; não usar vitória como único indicador porque perder também permite entrega.
- Documentar o que acontece após trocar de mapa ou recarregar nesse caso. Não afirmar persistência de temporários.
- Avaliar o risco de o aviso vago de treino ocupado deixar o jogador sem entender o impedimento. Registrar o achado sem substituir automaticamente a fala aprovada.

## 4. Batalha com continuidade após derrota

- Localizar comando e callback reais para batalha de treinador com continuidade em derrota.
- Inspecionar o evento implementado de Lillie como referência, sem presumir que todos os seus mecanismos se aplicam a Cianwood.
- Examinar blackout, dinheiro, cura, estatísticas, achievements, flag automática de vitória e retorno ao mapa.
- Verificar obtenção e preservação do resultado antes de cura/outras chamadas.
- Examinar empate, desistência, cancelamento e resultados inesperados quando disponíveis.
- Verificar restauração do estado anterior de no-whiteout em todas as saídas. Não simplesmente limpar um controle que já estava ativo.
- Confirmar interlocutor/objeto necessário, lock/release e retorno ao script.
- Recusa deve entregar Fly e concluir sem batalha; não criar revanche posterior por interpretação da fala “fica para a próxima”.

## 5. Mapa, objetos e encenação

- Inspecionar coordenadas, colisões, portas, warps, movimentos de NPCs e limite de objetos ativos.
- Identificar gráficos realmente disponíveis de Gladion e Type: Null; distinguir existência de asset de integração funcional.
- Verificar custo de dois objetos adicionais junto com follower e outros sprites ativos.
- Propor posições e caminhos baseados no mapa real, incluindo todas as direções acessíveis da interação manual.
- Verificar posição e orientação depois da batalha; não presumir que alterações transitórias sobrevivem ao retorno.
- Examinar a ida da esposa ao ginásio e a restauração do comportamento normal sem flag nova.
- Garantir caminhada de saída dos dois sem atravessar jogador, follower ou NPCs.
- Examinar música antes/depois da batalha, ausência de música definida para o encontro e restauração nas saídas de falha.
- Não declarar caminhos testados apenas pela leitura de coordenadas.

## 6. Continuidade e balanceamento de referência

- Verificar se é possível alcançar Fly sem os encontros de Violet ou Goldenrod. Se sim, apontar falas incompatíveis e condições existentes ou redação alternativa.
- Verificar interação adiada após Chuck: “você acabou de sair do ginásio” não deve afirmar algo que o fluxo não garante.
- Examinar Fly adiado até depois de Blackthorn e da Liga. Não bloquear Fly nem reapresentar Type: Null depois de sua evolução para Silvally como se tivesse regredido.
- Propor solução usando progressão existente; distinguir recomendação de decisão já aprovada.
- Verificar se outros Gladion/Type: Null podem aparecer simultaneamente em estados incompatíveis.
- Registrar equipe, níveis, itens, abilities/innates, formato, IA e scaling/level cap de Chuck no checkout, indicando se a referência corresponde à dificuldade única pretendida.
- Registrar o time implementado de Gladion em Violet e limitações relevantes para a futura revanche.
- Não definir o novo time nesta auditoria. A luta deve ser tratada como boss possível para a etapa, não como treino trivial por justificativa narrativa.

## Relatório obrigatório

Produza `AUDITORIA_GLADION_CIANWOOD_FLY.md`, em português, com:

### A. Veredito

Viável como proposto, viável com ajustes ou bloqueado. Justificar com os principais achados e separar impeditivos de melhorias opcionais.

### B. Evento atual

Arquivo → objeto/script → requisitos → entrega → controle de conclusão. Incluir branch, SHA, alterações locais relevantes e escopo efetivamente inspecionado.

### C. Achados priorizados

| ID | Severidade | Falha/risco | Evidência: arquivo, símbolo e linhas | Condição de reprodução | Correção mínima sem novas flags |
| --- | --- | --- | --- | --- | --- |

Priorizar bloqueio de Fly, duplicação, sumiço indevido, perda de progresso, batalha repetida, blackout e consumo de estados não autorizado. Ausência de teste não é por si só um bug comprovado.

### D. Controles reutilizados

| Controle real | Significado atual | Uso proposto | Outros consumidores | Persistência e conflitos |
| --- | --- | --- | --- | --- |

### E. Fluxo corrigido

Descrever entrada, impedimento inicial, aceite, recusa, vitória, derrota, resultado inesperado, entrega frustrada, reentrada e conclusão. Separar comportamento comprovado de proposta.

### F. Referências para o futuro refinamento

Listar arquivos que precisariam mudar, fontes/derivados, mecanismo de batalha, item e controles reais, assets, possíveis caminhos e dados de Chuck/Gladion. Não aplicar mudanças. Não reservar ID apenas por ausência de referência direta: conferir tabelas e mecanismos dinâmicos relevantes.

### G. Checklist de testes para a implementação

- [ ] Antes de Chuck, sem acesso antecipado a Fly.
- [ ] Após Chuck, fluxo normal de interação.
- [ ] Fly já recebido: sem reencontro ou duplicata.
- [ ] Impedimento inicial real, se possível: fala curta, sem batalha/progresso.
- [ ] Recusa: entrega e saída definitiva.
- [ ] Vitória: diálogo, cura, entrega e saída.
- [ ] Derrota: sem blackout/penalidade, com diálogo, cura e entrega.
- [ ] Empate/desistência/resultado inesperado, quando suportados.
- [ ] Falha excepcional da entrega: NPCs presentes e progresso intacto.
- [ ] Retomada na mesma visita e comportamento documentado após reload.
- [ ] Follower ligado/desligado e diferentes direções de interação.
- [ ] Posições corretas ao retornar da batalha.
- [ ] Esposa de Chuck preservada e sem segunda entrega.
- [ ] Reentrada e save/load após conclusão: ambos ausentes.
- [ ] Encontro adiado após Blackthorn/Liga: Fly acessível e continuidade coerente.
- [ ] No-whiteout, música e controles restaurados, inclusive estado prévio.
- [ ] Nenhuma nova flag/variável persistente proposta como necessária sem explicitar conflito com o requisito.

As caixas são plano de teste, não testes executados. Se houver teste real, registrar separadamente comando/ambiente, resultado e evidência. Build não substitui emulador.

### H. Decisões pendentes

Somente perguntas que o código e o plano não resolvem. Para cada uma, apresentar impacto e recomendação concreta. Não pedir autorização para leituras ou repetir confirmações já dadas sobre dificuldade única, ausência de flags novas e resultados da batalha.

## Critério de conclusão

Entregar achados acionáveis para o refinamento e não uma aprovação genérica do plano. Diferenciar claramente inspeção comprovada, hipótese que exige teste e decisão de design. Se faltarem dados ou acesso, documentar a limitação sem inventar evidências. Não implementar o evento durante esta auditoria.
