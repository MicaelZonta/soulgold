# Lillie em Goldenrod — refinamento completo V5

Documento único para o agente executor. Substitui integralmente V2, V3, V4 e o script dinâmico antigo. Não é necessário consultar essas versões para implementar. Inclui roteiro, equipe, contrato técnico e checklist no mesmo arquivo.

Status: especificação revisada; não implementada nem compilada nesta entrega. Referências técnicas herdadas da revisão do commit 26bff3cc. Por confirmação do usuário, assumir que a equipe do antigo Hard de Whitney é a única versão existente no projeto-alvo, ainda que esteja em outra branch. Não exigir nova consulta de Whitney nem troca/merge de branch para iniciar este trabalho. Nenhuma evolução de Vulpix nesta cena.

## 1. Regras fechadas

- Cutscene na entrada da floricultura, depois de Whitney, enquanto FLAG_RECEIVED_SQUIRTBOTTLE estiver unset.
- Lillie conversa com a dona, percebe o jogador, mostra exclamação e se aproxima. MUS_HG_LYRA começa quando ela reconhece o jogador.
- Verificar espaço para ITEM_SQUIRTBOTTLE antes de curar e iniciar a luta.
- Batalha simples de treino: ganhar OU perder permite concluir a cena. Só o diálogo varia. Não mandar o jogador ao Pokémon Center.
- Curar antes e depois da luta, nos dois resultados.
- O SquirtBottle não é prêmio por vitória. A florista autorizou Lillie a passá-lo ao jogador, que seguirá para Route 36; Lillie vai encontrar a mãe antes de continuar a viagem.
- Depois da entrega confirmada, marcar FLAG_RECEIVED_SQUIRTBOTTLE, despedida, caminhada até a porta, removeobject e retorno da música da loja.
- O objeto de Lillie usa diretamente FLAG_RECEIVED_SQUIRTBOTTLE. Ela não reaparece ao retornar à loja.
- Nenhuma nova flag persistente de visibilidade ou história. B_FLAG_NO_WHITEOUT é um controle existente, usado somente durante esta luta.

## 2. Referência de Whitney e dificuldade

Premissa fechada por confirmação do usuário: o antigo Hard é a única Whitney considerada neste refinamento. Não há versão Normal a preservar, comparar ou recriar. A localização dessa implementação em outra branch não é uma pendência de auditoria de Whitney.

| Pokémon de Whitney | Nível |
| --- | --- |
| Maushold | 27 |
| Audino | 27 |
| Cinccino | 27 |
| Miltank | 27 |

Referência adotada: batalha dupla, equipe do antigo Hard. Isso é uma premissa de projeto aceita, não uma alegação de nova verificação remota. Não alterar Whitney, adicionar seletor de dificuldade, recriar variantes nem mudar de branch por conta própria. O executor implementa Lillie no checkout indicado para a tarefa.

Lillie fica em 28/29/28/29: mais próxima desse estágio do que o ás nível 30 proposto antes. Vulpix continua pequena e frágil; Eviolite e controle de velocidade dão função real sem evolução antecipada. Clefairy e Vulpix podem repetir Eviolite: não impor Item Clause a esta batalha de história. A dificuldade pretendida vem da equipe de quatro, IVs/EVs, IA e suporte, não de um salto exagerado de nível. Comfey usa Synthesis com cautela: clima pode reduzir sua cura. Validar comportamento real da IA.

Não prometer que essa equipe vence a Whitney em confronto direto. O requisito é um desafio maior ao jogador naquela etapa, com teste contra equipes representativas, respeitando o level cap e o scaling atualmente ativos.

## 3. Roteiro completo da cena

Falas abaixo definem conteúdo. O executor deve distribuí-las em caixas curtas, com identificação do falante quando necessário e quebras compatíveis com a fonte. São acontecimentos autorais da viagem em Johto, não fatos canônicos externos.

### 1. Conversa com a florista

Florista: “It stops people on their way to Ecruteak. A little water makes it wriggle, but nobody wants to get too close.”

Lillie: “Then we shouldn't pull at its branches. If it can move, perhaps we can persuade it to move on its own.”

Florista: “You can take this SquirtBottle. Just be careful, dear.”

Lillie percebe o jogador, vira, mostra !. Começa MUS_HG_LYRA; ela se aproxima.

### 2. Reencontro e Johto

Lillie: “{PLAYER}! You've been to Whitney's Gym, haven't you? I recognized the Badge.”

Lillie: “I thought traveling would mean getting better at following a map. Then I spent half a morning in Ilex Forest watching which flowers Ribombee visited.”

Lillie: “She kept returning to the sheltered flowers whenever the wind picked up. I was watching the path. She was watching everything around us.”

### 3. Gladion e o parceiro

Lillie: “Gladion told me he met you in Violet. He said, 'They didn't hesitate.' From him, that's practically a speech.”

Lillie: “And you met the Type: Null traveling with him. He pretends not to fuss over it, but he checks on it whenever he thinks nobody is looking.”

Não presumir que o jogador venceu Gladion com facilidade, que o ovo já chocou, nem confundir este Type: Null com o antigo Silvally. O encontro de Violet já é parte da progressão normal.

### 4. A razão para entregar o item

Lillie: “Are you heading north? I promised Mother I'd meet her before we leave Goldenrod.”

Lillie, para a dona: “Would it be all right if {PLAYER} took the bottle? We've traveled some of the same roads.”

Florista: “Of course. You may keep it. I'd just like that path clear again!”

Lillie: “Then it's yours. But before you go... could we have another battle? I want to see how much we've learned.”

Checar espaço aqui. Se não houver: “Your Bag looks full. Make room for the bottle first. I'll be here.” Não curar nem lutar; liberar os controles e manter acesso à saída.

### 5. Desafio

Lillie: “Vulpix and I have been practicing. She's started looking back at me when she sees an opening. I'm learning not to miss it.”

Lillie: “Let's take care of your Pokémon first. And please don't hold back. I won't, either.”

Cura, batalha. Manter Vulpix Alola, a mesma parceira de Route 30, sem evolução nesta cena.

### 6A. Jogador vence

Texto de derrota da treinadora: “We couldn't quite catch up... but we kept trying!”

Depois: “I spent so long deciding what to do that I missed some of Vulpix's signals. I want to get better at answering her.”

Depois: “I want to try that again someday. After I've worked out a better answer!”

### 6B. Jogador perde

Lillie: “We did it...? We did! Oh, Vulpix, you were wonderful!”

Lillie: “Sorry! I didn't mean to get carried away. I kept watching Vulpix instead of worrying about every command. That felt different.”

Lillie: “Thank you for taking us seriously. Let's get your Pokémon feeling better.”

Empate usa uma fala própria curta: “That was close for both of us. Let's take a moment to look after everyone.” Forfeit, se o menu permitir, não deve ser chamado de vitória da Lillie: “Of course. We can stop here. Let's look after your Pokémon.”

### 7. Final comum

Curar o time em todos os resultados. Ler/salvar o resultado antes da cura; ela pode modificar variáveis especiais.

Lillie: “Here, the SquirtBottle, just as we agreed. Try a little water first. Whatever that tree is, there's no need to frighten it.”

giveitem; confirmar sucesso; setflag FLAG_RECEIVED_SQUIRTBOTTLE.

Lillie, virando para a dona: “Thank you for your help. And for letting us borrow a little room!”

Florista: “Just don't make a habit of battling beside my flowers!”

Lillie, para o jogador: “I'd better find Mother. Tell me what happened when we meet again, won't you?”

Jogador abre passagem se necessário. Lillie caminha até a porta e some. Retorna a música normal.

## 4. Equipe e identidade de batalha

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

## 5. Equipe para trainers.party

Preservar o ID inicial de Lillie. Esta é uma nova entrada de batalha; verificar disponibilidade do número antes de defini-lo. Golpes autorados são proposta para boss, não alegação de learnset natural neste nível.

```text
=== TRAINER_LILLIE_GOLDENROD ===
Name: Lillie
Class: Lass
Pic: Lillie
Gender: Female
Music: Hg Girl 1
Double Battle: No
AI: Smart Trainer

Clefairy @ Eviolite
Bold Nature
Level: 28
Ability: Magic Guard
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 100 HP / 100 Def / 60 SpA
- Reflect
- Moonblast
- Thunder Wave
- Flamethrower

Ribombee @ Sitrus Berry
Timid Nature
Level: 29
Ability: Shield Dust
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 60 HP / 100 SpA / 100 Spe
- Pollen Puff
- Draining Kiss
- Psychic
- Stun Spore

Comfey @ Sitrus Berry
Modest Nature
Level: 28
Ability: Triage
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 100 HP / 60 Def / 100 SpA
- Draining Kiss
- Giga Drain
- Calm Mind
- Synthesis

Vulpix Alola @ Eviolite
Timid Nature
Level: 29
Ability: Snow Warning
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 100 HP / 60 SpA / 100 Spe
- Aurora Veil
- Ice Beam
- Icy Wind
- Encore
```

## 6. Estados e contrato da cutscene

A fonte atual da loja é scripts.pory. O novo documento é independente: não reutilizar os branches incorretos dos scripts anteriores.

1. Objeto adicional com OBJ_EVENT_GFX_LILLIE, TRAINER_TYPE_NONE e flag FLAG_RECEIVED_SQUIRTBOTTLE; local ID definido segundo objetos atuais.
2. Gatilho de entrada em tile validado após a porta; encerrar imediatamente antes de Whitney ou depois da entrega.
3. Uma única aproximação por visita. Se a tentativa foi interrompida por bolsa cheia, permitir conversar e tentar novamente sem replay do deslocamento.
4. Posicionar os personagens de frente para conversar; usar esperas em todos os movimentos. A dona mantém seus serviços e deixa de entregar o item.
5. Espaço disponível: cura, batalha sem blackout, resultado preservado, diálogo correspondente, cura, entrega.
6. Entrega bem-sucedida: FLAG_RECEIVED_SQUIRTBOTTLE setada; despedida, passagem liberada, caminhada até a porta, removeobject, música da loja e releaseall.
7. Não setar a flag de entrega antes da batalha: a NPC poderia desaparecer no retorno do combate.
8. Não usar flag de trainer derrotado para esconder Lillie: na derrota do jogador ela também precisa sair depois da entrega.
9. Follower e retorno da batalha precisam de teste no emulador. Não declarar movimentação validada apenas por coordenadas no JSON.

### Modelo de estados locais

| Estado | Persistência | Uso |
| --- | --- | --- |
| FLAG_RECEIVED_SQUIRTBOTTLE | Save | Recompensa entregue e NPC escondida |
| FLAG_BADGE03_GET | Save existente | Permissão para iniciar a cena |
| VAR_TEMP_2 | Visita atual | Aproximação já realizada |
| VAR_TEMP_3 | Visita atual | Resultado capturado antes da cura |
| VAR_TEMP_4 | Visita atual | Treino concluído, entrega pendente |
| B_FLAG_NO_WHITEOUT | Controle existente | Impedir blackout apenas durante a luta |

Conferir colisões dessas variáveis com outros scripts do mapa e chamadas comuns. O bit automático de vitória do trainer não controla conclusão: perder também conclui após a entrega.

## 7. Batalha com vitória ou derrota

Vitória não é requisito para a entrega. Não usar trainerbattle_no_intro sozinho: o callback normal pode executar blackout.

No código consultado, CB2_EndTrainerBattle respeita B_FLAG_NO_WHITEOUT; o comentário em include/config/battle.h esclarece que não cura automaticamente. GetBattleOutcome está disponível como special.

Esqueleto do trecho de batalha (labels de texto devem ser criados pelo executor a partir do roteiro):

```asm
    checkitemspace ITEM_SQUIRTBOTTLE, 1
    goto_if_eq VAR_RESULT, FALSE, Lillie_NoRoom
    call Common_EventScript_OutOfCenterPartyHeal
    removefieldmugshot
    setflag B_FLAG_NO_WHITEOUT
    setvar VAR_LAST_TALKED, LOCALID_GOLDENROD_FLOWER_SHOP_LILLIE
    trainerbattle_no_intro TRAINER_LILLIE_GOLDENROD, Lillie_DefeatedText
    specialvar VAR_RESULT, GetBattleOutcome
    copyvar VAR_TEMP_3, VAR_RESULT
    clearflag B_FLAG_NO_WHITEOUT
    playbgm MUS_HG_LYRA, TRUE
    goto_if_eq VAR_TEMP_3, B_OUTCOME_WON, Lillie_PlayerWon
    goto_if_eq VAR_TEMP_3, B_OUTCOME_LOST, Lillie_PlayerLost
    goto_if_eq VAR_TEMP_3, B_OUTCOME_DREW, Lillie_Draw
    goto_if_eq VAR_TEMP_3, B_OUTCOME_FORFEITED, Lillie_Forfeit
    goto Lillie_UnexpectedOutcome
```

Cada branch normal apresenta sua fala e converge para cura e entrega. UnexpectedOutcome deve curar, restaurar música, liberar controles e não entregar; não assumir vitória em resultado desconhecido. Preservar/restaurar o valor prévio de B_FLAG_NO_WHITEOUT se puder estar ativo na entrada; não deixar este controle ligado em nenhuma saída. Conferir efeitos sobre dinheiro, replay e estatísticas; derrota de treino não deve cobrar penalidade de blackout. Não transformar derrota em vitória nem registrar achievement de vitória artificialmente.

Depois de qualquer resultado aceito, usar VAR_TEMP_4 = 1 como “treino concluído nesta visita” antes da tentativa de entrega. Se giveitem falhar excepcionalmente, conservar esse estado e repetir somente a entrega ao falar novamente. Não usar checktrainerflag como único gate: derrota não marca vitória. Sem novo estado persistente, a retomada depois de sair do mapa após uma falha excepcional não preserva a conclusão por derrota; a prevenção real é checkitemspace e entrega imediata no mesmo fluxo. Documentar essa limitação, não alegar que uma variável temporária persiste no save.

## 8. Encenação, reentrada e saída

- O trigger deve ser idempotente: depois de bolsa cheia, pisar novamente em (6,8) não deve repetir o movimento de aproximação a partir da posição alterada. Reservar VAR_TEMP_2 para estados 0=conversa com dona, 1=aproximação já feita. Consultá-la antes de qualquer movimento.
- Usar lockall/releaseall para uma cena automática com vários objetos, e definir VAR_LAST_TALKED antes do comando de batalha. O trigger não é uma conversa iniciada com A.
- Antes da batalha, guardar a posição de cena no template se necessário para sobreviver ao retorno do combate. Verificar que Lillie permanece em (6,7), não volta a (4,4).
- Lillie inicial (4,4), dona (2,4), jogador (6,8), aproximação até (6,7), porta (6,9): propostas baseadas no mapa antigo. Validar colisões, follower e todas as direções de interação no branch atual.
- Se faltar espaço, liberar controles sem bloquear a saída; a conversa manual retoma o desafio sem repetir aproximação. Se o jogador reentrar, usar estado local reinicializado e posição inicial coerente.
- Remover o fallback que simplesmente desaparece com fade como conclusão normal. A saída normal deve ser sempre caminhada visível até a porta. Debug com posição inesperada deve normalizar posições com caminho validado ou abortar antes da luta, não inventar passos.
- Usar FLAG_RECEIVED_SQUIRTBOTTLE como flag do objeto; setar apenas após sucesso de giveitem. Setflag não substitui removeobject na cena atual.
- Revisar clears existentes da flag de recebimento: nenhum gatilho de reentrada pode apagar a entrega concluída. Não replicar a flag em flagheaps por hábito.
- A dona deixa de entregar o item, mas preserva perfume sazonal e demais serviços. Ajustar encaminhamento da Route 36; não alterar a luta de Sudowoodo.
- Música: tema alegre no reencontro e pós-luta, música normal ao sair ou cancelar por falta de espaço. Reutilizar áudio, sem importar faixa nova; os comandos do script ainda têm pequeno custo de ROM.

## 9. Arquivos e entrega técnica

Revalidar ID livre de TRAINER_LILLIE_GOLDENROD após limpeza; 968 era uma sugestão, não reserva garantida. Preservar TRAINER_LILLIE 965. Criar equipe em trainers.party e regenerar trainers.h. Editar scripts.pory e regenerar scripts.inc. Não alterar arquivos gerados manualmente. Atualizar documentação da seção 4.6 para substituir vitória obrigatória por batalha de treino com continuidade nos dois resultados.

Testar: antes/depois de Whitney; bolsa cheia antes da luta; nova tentativa na mesma visita; saída e reentrada após bolsa cheia; vitória, derrota, empate e forfeit; cura em ambos resultados; nenhuma cobrança de blackout; controles restaurados; follower não bloqueia movimentos; Lillie sai andando e não reaparece após entrega/reload; apenas uma cópia do item; Route 30 intacta; batalha acima da Whitney de referência (única equipe do antigo Hard, Lv.27) em testes com equipes representativas. Reportar build, warnings e quais testes foram realmente executados.

## 10. Checklist de execução e validação

Executar na ordem abaixo. Todos os itens começam pendentes: este documento não comprova implementação. Marcar [x] somente após executar e registrar evidência. Build aprovado não substitui teste no emulador. Se não puder testar, manter [ ] e registrar o bloqueio. Não fazer commit/push sem autorização.

### 1. Conferência antes de editar

- [ ] Ler este refinamento completo e as instruções aplicáveis do repositório; usar esta versão como autoridade sobre os roteiros anteriores.
- [ ] Registrar branch, SHA e git status; preservar alterações do usuário e a limpeza já realizada.
- [ ] Adotar a premissa confirmada: única Whitney = antigo Hard, Maushold/Audino/Cinccino/Miltank Lv.27; não solicitar reconferência nem consultar outra branch para validar essa decisão.
- [ ] Respeitar as regras de scaling/level cap ao implementar Lillie; não recriar variantes Normal/Hard nem alterar Whitney.
- [ ] Resolver um ID livre e seguro para TRAINER_LILLIE_GOLDENROD; conferir referências e faixa de flags. Não assumir que 968 está livre nem tocar TRAINER_LILLIE 965.
- [ ] Conferir todos os set/clear de FLAG_RECEIVED_SQUIRTBOTTLE e garantir que revisitas não apaguem a entrega.
- [ ] Confirmar B_FLAG_NO_WHITEOUT, GetBattleOutcome e a recuperação da party no código atual; identificar efeitos sobre dinheiro e estatísticas.

Evidência da etapa: SHA, arquivos inspecionados, premissa de Whitney adotada, ID escolhido e justificativa.

### 2. Equipe da Lillie

- [ ] Adicionar a constante do novo trainer sem renumerar outros IDs.
- [ ] Adicionar o bloco de trainers.party deste documento: Clefairy 28, Ribombee 29, Comfey 28 e Vulpix Alola 29.
- [ ] Conferir itens, naturezas, abilities, EVs, IVs e quatro golpes de cada Pokémon contra o bloco proposto.
- [ ] Manter Vulpix sem evolução; verificar também se regras de scaling poderiam evoluí-la automaticamente e impedir isso nesta batalha, se necessário.
- [ ] Conferir innates e interação entre Snow Warning, Aurora Veil, Triage e Synthesis na configuração atual.
- [ ] Manter batalha simples e Smart Trainer, sem variante Hard adicional; preservar integralmente a batalha de Route 30.

### 3. Mapa e gatilho

- [ ] Editar GoldenrodCity_FlowerShop/map.json preservando os cinco objetos e serviços atuais; atribuir local IDs sem colisão.
- [ ] Adicionar Lillie com OBJ_EVENT_GFX_LILLIE, TRAINER_TYPE_NONE e flag FLAG_RECEIVED_SQUIRTBOTTLE, sem nova flag de ocultação.
- [ ] Validar posição inicial frente à dona, tile de entrada, aproximação e porta contra layout/colisões atuais; não copiar coordenadas sem conferir.
- [ ] Implementar a condição automática: Whitney derrotada e item ainda não recebido. Antes de Whitney, permitir apenas conversa normal.
- [ ] Reservar variáveis temporárias livres no mapa, documentando aproximação já realizada, resultado da batalha e entrega pendente nesta visita.
- [ ] Evitar repetição do movimento ao pisar novamente no trigger; manter acesso à saída quando a bolsa estiver cheia.
- [ ] Usar lockall/releaseall e esperas de movimento; definir VAR_LAST_TALKED corretamente antes da batalha automática.
- [ ] Preservar a posição de Lillie no retorno da batalha; testar com follower ligado e desligado.

### 4. Roteiro e música

- [ ] Implementar conversa inicial com a florista, reconhecimento, exclamação, aproximação e reencontro.
- [ ] Incluir a experiência em Ilex Forest, a referência a Gladion/Type: Null e o crescimento da relação com Vulpix.
- [ ] Explicar a entrega antes da luta: florista autoriza, jogador segue para Route 36 e Lillie encontrará a mãe. O item não depende de vencer.
- [ ] Criar falas distintas de vitória, derrota, empate e desistência conforme o roteiro, sem atribuir fatos que dependem do time do jogador ou do ovo ter chocado.
- [ ] Remover referências à evolução de Vulpix nesta cena; converter falas em caixas curtas e conferir identificação dos falantes.
- [ ] Iniciar MUS_HG_LYRA após a exclamação, retomá-la após a luta e restaurar música normal na saída ou cancelamento por bolsa cheia.

### 5. Batalha e entrega

- [ ] Executar checkitemspace ITEM_SQUIRTBOTTLE, 1 antes da cura e da luta; falta de espaço encerra sem batalhar ou marcar progresso.
- [ ] Curar antes do desafio e ativar no-whiteout apenas pelo período necessário, preservando/restaurando o estado anterior quando aplicável.
- [ ] Capturar GetBattleOutcome imediatamente após o retorno e antes de chamadas que possam sobrescrever VAR_RESULT.
- [ ] Tratar vitória e derrota como resultados válidos; curar em ambos, sem blackout nem penalidade de blackout e sem falsificar flag/achievement de vitória.
- [ ] Tratar empate/desistência explicitamente, e resultado desconhecido como saída defensiva sem recompensa.
- [ ] Usar estado temporário de treino concluído para retomar uma falha excepcional de entrega nesta visita; não depender só da flag de trainer vencido.
- [ ] Entregar exatamente uma unidade e verificar VAR_RESULT imediatamente após giveitem.
- [ ] Marcar FLAG_RECEIVED_SQUIRTBOTTLE somente após sucesso; não marcar antes da batalha ou em falha de entrega.
- [ ] Fazer despedida, abrir passagem sem atravessar jogador/follower, caminhar até a porta e executar removeobject.
- [ ] Restaurar música e controles em todas as saídas. Não usar desaparecimento com fade como final normal.
- [ ] Remover entrega pela dona, preservando perfume, vendedores e scripts compartilhados de Route104; ajustar encaminhamento da Route36 sem alterar Sudowoodo.

### 6. Build e revisão estática

- [ ] Regenerar scripts.inc a partir de scripts.pory e trainers.h a partir de trainers.party pelos comandos do projeto; não editar derivados manualmente.
- [ ] Executar build e registrar comando, código de saída, warnings e tamanho da ROM.
- [ ] Verificar diff/whitespace, labels e referências indefinidas, IDs duplicados e ausência de flags persistentes novas.
- [ ] Confirmar no diff que Route30, Whitney e serviços não relacionados não foram alterados inadvertidamente.

### 7. Testes no emulador

- [ ] Antes de Whitney: sem cutscene/batalha/entrega; interação normal funciona.
- [ ] Após Whitney: conversa, !, música e aproximação executam na ordem correta.
- [ ] Bolsa cheia: sem cura ou luta; pode sair, voltar e tentar novamente sem movimento duplicado ou bloqueio da porta.
- [ ] Liberar espaço na mesma visita: interação retoma corretamente.
- [ ] Vitória: fala correta, cura, item, saída andando e música restaurada.
- [ ] Derrota: sem transporte ao Center ou cobrança de blackout; fala correta, cura, item e mesma saída definitiva.
- [ ] Empate/desistência, quando suportados: comportamento explícito, sem travamento.
- [ ] Falha de entrega injetada em ambiente de teste: não esconder Lillie; repetir somente a entrega na mesma visita. Registrar a limitação após troca de mapa.
- [ ] Reentrar e recarregar save após entrega: Lillie ausente e nenhuma duplicata do item.
- [ ] Testar as direções possíveis da interação manual, retorno pós-batalha e follower; nenhuma colisão ou personagem reposicionado incorretamente.
- [ ] Usar o SquirtBottle na Route36; confirmar serviços da loja e batalha inicial de Lillie intactos.
- [ ] Comparar dificuldade com Whitney de referência (única equipe do antigo Hard, Lv.27) usando equipes representativas de jogadores; registrar níveis, resultados e ajustes. Não marcar este teste só por comparar níveis.

### 8. Handoff

- [ ] Atualizar os documentos do repositório que ainda exigem vitória ou citam evolução para esta cena, respeitando o escopo desta implementação.
- [ ] Entregar resumo de arquivos alterados, trainer ID, flags/temporários usados, equipe, build e resultados dos testes.
- [ ] Separar claramente itens implementados, testados e pendentes; anexar logs/capturas relevantes quando disponíveis.
- [ ] Registrar cada bloqueio com próximo passo concreto, sem marcar a tarefa inteira como validada se faltam testes essenciais.

Formato de evidência por item: ID/etapa — arquivo ou teste — resultado observado — evidência/log — pendência (se houver).

## 11. Prompt para o executor

Implemente este refinamento completo, substituindo as versões anteriores. Mantenha Vulpix Alola sem evolução. Assuma como confirmado pelo usuário que só existe a Whitney do antigo Hard: Maushold, Audino, Cinccino e Miltank, todos nível 27, em batalha dupla. Não exigir reconferência dessa equipe, consulta remota, troca ou merge de branch; não recriar Normal/Hard nem alterar Whitney. Respeite o scaling e o level cap aplicáveis à batalha de Lillie. Use o time proposto e verifique a dificuldade efetiva. Escreva os diálogos do roteiro em caixas curtas, preservando Johto, Gladion, Type: Null e a motivação do SquirtBottle. O treino continua em vitória ou derrota, com cura e falas diferentes; não exigir vitória nem simular uma vitória no save. Use o controle existente de no-whiteout apenas nesta luta. A entrega bem-sucedida seta FLAG_RECEIVED_SQUIRTBOTTLE; Lillie sai andando e permanece invisível em visitas futuras por essa mesma flag. Não criar flag persistente adicional. Corrija reentrada, falta de espaço, VAR_LAST_TALKED e posicionamento pós-batalha. Regenere derivados, compile, teste e relate limitações reais.
