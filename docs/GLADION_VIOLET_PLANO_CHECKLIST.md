# Gladion em Violet — plano e checklist

## Escopo

Implementar a batalha obrigatória e a entrega do ovo de Cosmog por Gladion no Pokémon Center de Violet, após Falkner. Inclui a remoção do teste da Route 29, os ajustes de encaminhamento de Elm e do NPC da Route 32 e a remoção completa do Exp. Jar do jogo. Não executar outras etapas das Rift Missions. Este documento consolida as decisões mais recentes para esta tarefa.

Base: auditoria fornecida pelo autor. Confirmar seus identificadores na branch atual; os caminhos abaixo não representam uma nova auditoria do código.

## 1. Decisões

- Gladion substitui o assistente de Elm na entrega de Violet, fazendo um favor durante sua viagem.
- A batalha acontece depois de Falkner, antes de receber o ovo.
- Antes de lutar, verificar espaço no time OU no PC usando o teste existente. Bloquear somente quando ambos estiverem cheios. O jogador pode enfrentar Gladion com seis Pokémon.
- Após a vitória, entregar Cosmog ainda no ovo no time quando houver vaga; caso contrário, enviar ao PC e comunicar o destino.
- Remover Gladion da Route 29: era apenas um teste de sprite.
- Reutilizar seu trainer ID existente, indicado pela auditoria como `TRAINER_GLADION`, ID 967, após conferir referências.
- Reutilizar música de batalha de rival, preferencialmente Silver; Green é alternativa caso exista. Descobrir a constante real no projeto.
- Sem mugshot. Usar os sprites overworld e de batalha existentes.
- Trabalhar para New Game; compatibilidade com saves antigos não é requisito.
- Gladion entrega somente o ovo de Cosmog. Remover o Exp. Jar, sem oferecer outro item em seu lugar.
- Equipe aprovada: Grubbin, Sandile, Rockruff e Type: Null. Evitar sobreposição com Zubat e Sneasel de Silver.

## 2. Gladion como boss — quatro Pokémon

**Meta:** superar Falkner em dificuldade e exigir uma equipe preparada. Gladion é um treinador experiente de patamar E4 que está formando novos parceiros; sua experiência aparece na composição e nas decisões. Não usar a proposta antiga de dois Pokémon com IVs 0.

**Referência local inspecionada:** `trainers.party` contém Falkner normal com três Pokémon de níveis 11–12 e IVs 12; a variante Hard tem quatro de níveis 12–13, batalha dupla e `AI: Smart Trainer`. Esta cópia pode diferir da branch atual do autor. Confirmar também level cap e variantes antes de implementar; não considerar a comparação uma simulação ou teste de vitória.

### Equipe-base para implementar e testar

Formato: batalha simples, quatro Pokémon, IVs 31 em todos os atributos, EVs indicados abaixo e demais EVs 0. Usar a IA de boss adequada existente, com `Smart Trainer` como referência encontrada. Não inventar constantes de IA nem pressupor que ela executa um roteiro fixo.

| Ordem inicial | Pokémon | Nível | Natureza | Ability | Item | Golpes |
| --- | --- | --- | --- | --- | --- | --- |
| 1 | Grubbin | 14 | Modest | Swarm | Oran Berry | Struggle Bug / Electroweb / Mud-Slap / String Shot |
| 2 | Sandile | 14 | Jolly | Intimidate | Oran Berry | Bite / Bulldoze / Rock Tomb / Taunt |
| 3 | Rockruff | 14 | Jolly | Vital Spirit | Oran Berry | Rock Tomb / Bite / Quick Attack / Howl |
| 4 | Type: Null | 15 | Adamant | Battle Armor | Sitrus Berry | Headbutt / Aerial Ace / Bulldoze / Work Up |

| Pokémon | EVs |
| --- | --- |
| Grubbin | 40 HP / 40 SpA |
| Sandile | 40 Atk / 40 Spe |
| Rockruff | 40 Atk / 40 Spe |
| Type: Null | 40 HP / 40 Atk |

Os movesets são escolhas de equipe de treinador para este boss, não uma afirmação de que todos os golpes são aprendidos nesses níveis. Confirmar constantes, restrições locais e funcionamento no build. Não alterar learnsets globais para atender esta batalha.

### Função de cada parceiro

- **Grubbin:** lead especial de suporte. Struggle Bug reduz Sp. Atk e Electroweb reduz velocidade enquanto causa dano; String Shot também permite reduzir a velocidade de Ground, imune a Electroweb. Mud-Slap é cobertura fraca, não o fundamento da dificuldade. Sua tarefa é enfraquecer o avanço adversário e obrigar decisões de troca. Pode cair cedo se o jogador responder bem: isso é contrajogo válido.
- **Sandile:** Intimidate pressiona atacantes físicos e complementa a redução de Sp. Atk de Grubbin. Bite e Bulldoze dão STAB; Rock Tomb cobre Flying; Taunt pune cura por golpes e preparação passiva. Tem defesas frágeis e exige decisões de troca da IA. Não usar Moxie nesta versão.
- **Rockruff:** Rock Tomb reduz velocidade e ameaça Fire/Flying. Howl pune turnos cedidos; Quick Attack permite concluir um alvo enfraquecido. Vital Spirit e o innate local Sturdy tornam sua presença difícil de apagar com uma ação.
- **Type: Null:** principal ameaça, com resistência natural e recuperação única da Sitrus. Headbutt é o ataque consistente; Aerial Ace cobre Fighting; Bulldoze pressiona Rock/Steel e controla velocidade; Work Up permite aproveitar uma oportunidade de setup. Mantém vulnerabilidade a redução de Attack e status, sem Rest ou cura repetida.

A ordem da tabela define o lead e a organização inicial. Não criar um bloqueio artificial que impeça a IA de mandar Type: Null antes quando apropriado. Avaliar trocas, prioridade, reduções de atributos e uso de setup na IA real. As reduções no adversário desaparecem quando ele troca: a estratégia força decisões, não garante um bônus permanente para Null.

### Innates e oportunidades de resposta

Na cópia inspecionada, Grubbin tem Swarm e innate Shield Dust; Sandile pode usar Intimidate e tem innate Dust Devil; Rockruff tem innate Sturdy e Type: Null tem Scrappy. Confirmar os efeitos e se estão ativos na configuração atual, especialmente Dust Devil. Não mudar dados globais das espécies para esta luta. Se Scrappy estiver ativo, Ghost não é resposta imune aos ataques Normal do principal; não basear o teste nessa suposição. Battle Armor impede críticos contra Null; a vitória precisa de respostas consistentes.

O desafio oferece respostas, mas exige combinar parceiros: Fire/Flying/Rock pressionam Grubbin; Water/Grass pressionam Sandile e Rockruff; Type: Null pode ser enfraquecido e pressionado pelo time. A cobertura não elimina essas vulnerabilidades. Grubbin deve impedir que a equipe inteira seja trivializada apenas por reduzir Attack. O agente deve conferir encontros, golpes e itens acessíveis até Violet e demonstrar alternativas reais, especialmente para cada inicial.

Curar o time antes da luta. Permitir equipe de seis graças à entrega possível no PC. Berries seguradas fornecem recursos finitos; não adicionar também spam de poções, multiplicador de HP ou aura de Ultra Beast. Boss significa composição forte e boa IA, sem necessidade de empilhar todos os bônus do engine.

### Validação de dificuldade

- [ ] Confirmar a equipe efetiva de Falkner na dificuldade testada e o level cap após sua vitória.
- [ ] Testar cada inicial com parceiros e recursos realmente disponíveis até Violet, dentro do cap vigente. Não exigir seis Pokémon perfeitos ou uma captura rara específica.
- [ ] A vitória deve exigir decisões e uso de recursos; não depender de crítico, erro de golpe ou grinding acima do limite para ser possível.
- [ ] Verificar Intimidate/Dust Devil de Sandile, controle de Grubbin, Sturdy de Rockruff e um Work Up do Type: Null. Registrar se eliminam respostas razoáveis.
- [ ] Se excessivo, ajustar primeiro EVs de suporte ou trocar Work Up por Leer, preservando quatro membros e o papel central de Type: Null. Se Mud-Slap transformar a luta em dependência de sorte, substituir por outro golpe validado. Registrar os ajustes.
- [ ] Se fácil, verificar se a IA está usando os recursos antes de aumentar níveis. Calibrar a variante Hard separadamente contra o Falkner Hard, sem assumir que a mesma equipe garante dificuldade superior em ambos.
- [ ] Registrar equipes utilizadas, níveis, recursos, resultado e ajustes. Este MD define um candidato forte; equilíbrio ainda depende de teste em jogo.

Gladion está treinando um novo Type: Null acolhido em Alola. Seu parceiro original não foi regredido; essa história não reduz sua competência.

## 3. Sequência da cena

1. A ligação de Elm, após o ginásio, indica Gladion no Pokémon Center.
2. Ao conversar, verificar primeiro se o ovo já foi entregue.
3. Enquanto a entrega estiver pendente, verificar espaço no time OU no PC. Se ambos estiverem cheios, pedir espaço e liberar o jogador, sem iniciar a batalha.
4. Gladion reconhece o nome do jogador pelo que Lillie contou e apresenta brevemente seu novo Type: Null.
5. Aproximar e orientar os personagens, curar o time e iniciar a batalha obrigatória.
6. Em derrota, seguir o retorno normal ao Pokémon Center; a entrega permanece pendente.
7. Em vitória, mostrar a fala de conclusão e executar a entrega do ovo, sem abrir gestão do time nem entregar outro Pokémon entre a checagem e esse momento.
8. Confirmar o resultado de `giveegg` antes de marcar recebimento. Informar o destino quando enviado ao PC. Não chamar a antiga entrega de Exp. Jar.
9. Avançar a Kimono Girl e retirar Gladion conforme o fluxo do mapa. O bloqueio da Route 32 passa a considerar o ovo recebido.

O envio do ovo ao PC faz parte do fluxo normal. O teste de capacidade é uma consulta ao estado atual, não uma nova flag persistente. Reutilizar o helper existente após confirmar seu contrato; não chamar `giveegg` antecipadamente como teste, pois ele cria o Pokémon.

## 4. Falas propostas em inglês

Textos originais para adaptar aos limites das caixas. Tom de Gladion: breve, reservado e atento ao parceiro.

**Ligação de Elm:**

> “{PLAYER}, I've asked a Trainer named Gladion to bring you the Egg. He was heading to Violet City. Meet him at the Pokémon Center, would you?”

**Time e PC cheios:**

> “There's no room for the Egg in your party or your PC. Make some space first. I'll wait here.”

**Ovo enviado ao PC:**

> “Your party is full, so the Egg was sent to your PC. Don't forget to check on it.”

**Reconhecimento:**

> “You're {PLAYER}? Lillie mentioned you. She's already planning your next battle.”

**Parceiro e desafio:**

> “I found this Type: Null in Alola. Someone had left it behind. It's traveling with me now.”
>
> “We're training. That doesn't mean we'll hold back. Let me see how you fight.”

**Depois da vitória do jogador:**

> “We're getting there, Null. That was a good battle.”
>
> “Here's the Egg. Elm asked me to bring it to you. Take care of it.”

**Despedida:**

> “And when Lillie challenges you again... give her a proper battle.”

**Lembrete de Elm:**

> “Gladion is waiting for you at Violet City's Pokémon Center. He has the Egg I wanted you to look after.”

**NPC da Route 32:**

> “{PLAYER}, right? A Trainer named Gladion was looking for you. He's waiting at the Pokémon Center.”

Não identificar o conteúdo do ovo nas falas de Gladion como se ele já soubesse que é Cosmog.

## 5. Arquivos e alterações

| Fonte indicada pela auditoria | Trabalho |
| --- | --- |
| `data/maps/Route29/map.json` e `scripts.pory` | Remover object event, script de teste e textos exclusivos de Gladion. Preservar os assets usados em Violet. |
| `data/maps/VioletCity/scripts.pory` | Atualizar `VioletCity_Text_Elm_Call` e aparição do entregador; manter o gatilho pós-Falkner. |
| `data/maps/VioletCity_PokemonCenter/map.json` | Usar `OBJ_EVENT_GFX_GLADION`, script novo e local ID verificado. |
| `data/maps/VioletCity_PokemonCenter/scripts.pory` | Implementar a cena, checagem de espaço, batalha e entrega. |
| `data/maps/NewBarkTown_Lab/scripts.pory` | Atualizar `ElmAideIsWaiting` e sua condição para Gladion, independente da presença do cientista. |
| `data/maps/NewBarkTown_Lab/map.json` | Ajustar a flag do cientista apenas se ficar obsoleta após desacoplar a entrega. |
| `data/maps/Route32/scripts.pory` | Atualizar indicação do homem de óculos para Gladion; preservar requisitos de ginásio, Sprout Tower e ovo. |
| `src/data/trainers.party` | Substituir a Rattata nível 5 do teste pela equipe proposta. |
| `include/constants/opponents.h` | Conferir ID e referências; renomear símbolo somente se necessário, preservando o ID reutilizado. |
| `include/constants/flags.h` e inicialização | Renomear a flag de ocultação reutilizada e liberar apenas slots comprovadamente abandonados. |
| Seletor musical de batalha | Reutilizar o caminho de Silver/Green, sem trocar a música de toda uma classe de treinadores. |

Editar as fontes reais: `.pory`, `map.json`, `trainers.party`. Regenerar derivados pelo build; não editar manualmente `trainers.h` ou duplicar alterações nos `.inc` gerados.

## 6. Estados e flags

- [ ] Reutilizar a flag de recebimento já existente, indicada na auditoria como `FLAG_RECEIVED_MYSTERY_EGG`.
- [ ] Reutilizar e renomear `FLAG_HIDE_VIOLET_CITY_AIDE` para refletir Gladion, mantendo o ID e atualizando todos os consumidores.
- [ ] Manter o cientista em New Bark; remover sua ocultação e reaparição relacionadas a esta entrega.
- [ ] Reescrever o lembrete de Elm com condições de ligação concluída e ovo pendente. Não usar a ausência do cientista como sinal.
- [ ] Confirmar `VAR_VIOLET_CITY_STATE`: a auditoria indica estado 3 após o ginásio e 4 após a ligação. Não criar variável paralela.
- [ ] Antes de `trainerbattle_no_intro`, consultar explicitamente o estado de treinador derrotado se necessário para retomar uma entrega após falha. O comando não faz essa checagem automaticamente segundo a auditoria.
- [ ] Confirmar que a vitória registra o estado do trainer ID e a derrota não.
- [ ] Não criar uma nova flag de “batalha vencida” quando o estado de treinador já atende ao caso.
- [ ] Não confundir índice do array de object events com local ID: conferir o formato e nomear o objeto corretamente.

**Liberação de flags:** procurar referências em C, scripts, mapas, inicialização, aliases e usos numéricos aplicáveis. Somente quando o slot não tiver mais função, renomear conforme o padrão local de livres, como `UNUSED_FLAG_<ID_HEX>`. Preservar os IDs das demais flags. Cada símbolo livre precisa de nome único.

Renomear não reduz o tamanho do save; torna um slot disponível para outra função. A flag de Violet continua ocupada por Gladion. A de ocultação do cientista só fica livre se nenhum outro evento precisar dela. Não reutilizar a faixa reservada de flags de treinador como flags comuns.

## 7. Entrega robusta

- [ ] Consultar capacidade antes da batalha: vaga no time OU em qualquer caixa válida permite continuar. Só bloquear se ambos estiverem cheios; contar ovos como ocupantes.
- [ ] Confirmar que o caminho entre checagem e entrega não aumenta a ocupação do time.
- [ ] Ler `VAR_RESULT` imediatamente após `giveegg SPECIES_COSMOG`.
- [ ] Distinguir entrega ao time, `MON_GIVEN_TO_PC` e `MON_CANT_GIVE`; preservar o resultado antes de diálogos/helpers que o sobrescrevam. Informar envio ao PC quando acontecer.
- [ ] Marcar recebimento somente após sucesso. Em falha inesperada, manter a entrega pendente e não repetir a vitória já registrada.
- [ ] Remover a chamada e o fluxo de `VioletPCGiveExpJar`. Não existe recompensa secundária nem retry de item neste evento.
- [ ] Avançar o evento da Kimono Girl somente após recebimento real.
- [ ] Encerrar a cena com movimento e remoção do objeto segundo o padrão do mapa.
- [ ] Preservar a origem narrada pelas Kimono Girls: Kukui → Elm → jogador. Não é necessário citar o transportador em toda recapitulação.

## 8. Checklist de implementação

- [ ] Ler as instruções locais e confirmar a branch atual antes das mudanças.
- [ ] Atualizar a referência antiga do projeto que ainda coloca Gladion em Goldenrod.
- [ ] Remover o teste da Route 29 e confirmar que o trainer ID não tem outro consumidor incompatível.
- [ ] Configurar equipe e música existente, sem mugshot.
- [ ] Ajustar objeto e movimentos em Violet, com espera de movimento e espaço para circular.
- [ ] Atualizar ligação de Elm, lembrete no laboratório e texto da Route 32.
- [ ] Implementar capacidade no time OU PC antes de lutar, derrota, vitória e entrega única no destino adequado.
- [ ] Remover o Exp. Jar conforme a seção 10 e revisar os estados da Kimono Girl.
- [ ] Buscar textos, labels e flags antigos; remover somente sobras sem consumidores.
- [ ] Registrar IDs reutilizados ou liberados e seus novos nomes.
- [ ] Compilar pelas fontes corretas e conferir o resultado.

## 9. Checklist de validação

- [ ] Antes de Falkner, a entrega não aparece antecipadamente.
- [ ] Após Falkner, a ligação indica Gladion e ele está no Pokémon Center.
- [ ] Time com seis Pokémon e vaga no PC: permite batalha; após vitória, envia ovo ao PC e informa o destino.
- [ ] Time e PC cheios: pede espaço, libera o jogador e não inicia batalha. Ao liberar uma vaga em qualquer dos dois, permite continuar.
- [ ] PC cheio e vaga no time: permite batalha e entrega normalmente no time.
- [ ] Time com cinco, incluindo ovos: inicia normalmente e entrega o ovo na sexta posição após vitória.
- [ ] Derrota: nenhum ovo ou avanço; reentrada permite tentar novamente.
- [ ] Vitória: uma única entrega, com diálogo e música corretos.
- [ ] Falha inesperada de entrega, se testável: retry sem revanche e sem flag extra.
- [ ] Receber o ovo conclui o evento sem entrega, texto ou dependência de Exp. Jar.
- [ ] Cientista de New Bark e lembrete de Elm permanecem coerentes.
- [ ] Kimono Girl e bloqueio da Route 32 avançam corretamente.
- [ ] Sprite, paleta, movimento e ausência de mugshot verificados em jogo.
- [ ] Route 29 não contém mais o teste de Gladion.

## 10. Remoção completa do Exp. Jar

Decisão aprovada: remover o item e sua funcionalidade do jogo, sem presente substituto. Não basta impedir a entrega em Violet. Não criar compatibilidade ou migração de saves antigos.

**Ponto de partida confirmado na cópia local:** `data/maps/VioletCity_PokemonCenter/scripts.pory` contém `VioletPCGiveExpJar`, que entrega `ITEM_CANDY_JAR`. Portanto, buscar também Candy Jar e seus símbolos; não presumir que a constante se chama `ITEM_EXP_JAR`. Confirmar essa correspondência na branch de implementação.

### Auditoria e implementação

- [ ] Mapear referências de `VioletPCGiveExpJar`, `ITEM_CANDY_JAR`, Exp Jar, Exp. Jar, Candy Jar e funções/campos descobertos ao seguir esses símbolos.
- [ ] Remover a chamada, o script de entrega e os textos exclusivos de Violet. Após receber o ovo, seguir diretamente para a conclusão e a Kimono Girl.
- [ ] Remover outras fontes de obtenção encontradas: scripts, lojas, recompensas e listas aplicáveis.
- [ ] Remover o registro funcional do item, handlers de uso, menus, descrições e assets exclusivos que não tenham outros consumidores.
- [ ] Auditar o mecanismo real: armazenamento/conversão de experiência ou doces, contadores, callbacks e inicialização. Remover somente o que pertencer exclusivamente ao Jar. Não presumir seu funcionamento apenas pelo nome.
- [ ] Preservar ganho normal de experiência, Rare Candy, Exp. Candy e outros sistemas que compartilhem helpers, salvo dependência comprovadamente exclusiva do Jar.
- [ ] Manter os IDs dos demais itens estáveis. Reservar o slot desativado conforme o padrão local, sem deixar um item utilizável ou obtível e sem deslocar a enumeração.
- [ ] Remover campos persistentes exclusivos somente após rastrear todos os acessos e avaliar layout/alinhamento. Não prometer economia de save ou ROM antes de medir.
- [ ] Renomear flags realmente abandonadas para `UNUSED_FLAG_<ID_HEX>` ou o padrão equivalente local, mantendo IDs. Remover suas referências antigas de inicialização e registrar os slots liberados.
- [ ] Regenerar derivados pelo build e verificar referências restantes: aceitar somente reservas documentadas ou registros históricos pertinentes.

### Validação da remoção

- [ ] New Game inicializa corretamente, sem acesso a dados removidos.
- [ ] Gladion entrega somente o ovo, tanto no time quanto no PC, e a cena termina normalmente.
- [ ] Não existe fonte normal de obtenção, comando de uso ou interface ativa do Jar.
- [ ] Ganho de experiência em batalha, subida de nível e evolução continuam funcionando.
- [ ] Itens e sistemas compartilhados preservados continuam operacionais.
- [ ] IDs dos itens posteriores e flags ainda utilizadas não foram deslocados.
- [ ] Build concluído; registrar testes realmente executados e qualquer pendência.

## 11. Ordem de execução e entrega

1. Confirmar a branch, as fontes e os IDs da auditoria; mapear as dependências do Jar.
2. Remover o teste da Route 29 e configurar Gladion em Violet com o time aprovado.
3. Implementar capacidade time/PC, batalha obrigatória, entrega única e movimentos.
4. Atualizar ligação e lembrete de Elm, Route 32 e sequência da Kimono Girl.
5. Remover o Jar em todo o escopo identificado e liberar flags comprovadamente sem uso.
6. Compilar, executar os checklists funcionais e calibrar a batalha no emulador.

**Entrega ao autor:** resumo dos arquivos alterados, equipe efetiva, música escolhida, remoção do Jar, flags reutilizadas/liberadas, resultado do build e testes efetivamente executados. Separar verificação estática de teste no emulador. Este documento é um plano de implementação; não afirma que o código foi alterado ou que a batalha já foi balanceada em jogo. Não implementar o restante das Rift Missions nesta tarefa.
