# Gladion — revisão dos encontros de Violet e Cianwood

## Retrofit de Type: Null fora da Poké Ball e duelos sem vitória obrigatória

**Data:** 18/09/2026  
**Base narrativa:** `SOULGOLD_RIFT_MISSIONS_DESIGN_V13(1).md`  
**Base inspecionada:** branch `soulgold-rift-missions` do repositório `MicaelZonta/soulgold`.

**Parecer:** vale revisar os dois encontros, mas eles estão em estados diferentes. **Violet precisa do retrofit completo. Cianwood já possui Type: Null no mapa e já permite continuar após derrota; precisa de regressão e pequenos alinhamentos, não de reconstrução.**

---

## 1. Arco visual fechado

| Encontro | Parceiro | Comportamento visual | Relação apresentada |
|---|---|---|---|
| Violet | Type: Null | Permanece junto de Gladion; observa e o segue na saída | Ainda cauteloso; começa a confiar |
| Cianwood | Type: Null | Explora, toma a iniciativa e sai na frente | Começa a decidir por si mesmo |
| Victory Road | Silvally | Gladion e Silvally saem lado a lado | Confiança consolidada |

Esse arco funciona melhor quando o parceiro está realmente visível desde Violet. Apenas mencioná-lo no texto e enviá-lo da Poké Ball durante a batalha enfraquece a progressão que Cianwood e Victory Road tentam mostrar.

---

## 2. Auditoria de Violet

### Estado atual confirmado

O evento existe em `data/maps/VioletCity_PokemonCenter`.

- Gladion é o objeto local 6, em `(9,4)`.
- Não existe objeto de Type: Null no `map.json`.
- O texto já apresenta o parceiro: “I found this Type: Null in Alola...”
- A checagem de espaço já considera party e PC antes da batalha.
- A party é curada antes do duelo.
- A batalha usa `trainerbattle_no_intro TRAINER_GLADION` sem preservar `B_FLAG_NO_WHITEOUT`.
- Não há leitura de `GetBattleOutcome`.
- O script segue diretamente para o ovo apenas se o jogador retorna pelo fluxo de vitória normal.
- Gladion sai sozinho; apenas seu objeto é removido.

Portanto, Violet ainda não cumpre duas decisões da V13: Type: Null visível e derrota válida.

### Mudança visual

Adicionar ao `map.json`:

```json
{
  "local_id": "LOCALID_VIOLET_TYPENULL",
  "graphics_id": "OBJ_EVENT_GFX_SPECIES(TYPE_NULL)",
  "x": 10,
  "y": 4,
  "elevation": 0,
  "movement_type": "MOVEMENT_TYPE_FACE_DOWN",
  "movement_range_x": 0,
  "movement_range_y": 0,
  "trainer_type": "TRAINER_TYPE_NONE",
  "trainer_sight_or_berry_tree_id": "0",
  "script": "NULL",
  "flag": "FLAG_HIDE_VIOLET_CITY_GLADION"
}
```

`(10,4)` é uma posição candidata ao lado de Gladion. Validar colisão, enquadramento, nurse/Chansey, NPC em `(12,5)`, follower e acesso ao balcão antes de fechar. Se o tile ou a passagem forem ruins, manter Type: Null na mesma área visível e ajustar a coreografia; a presença do parceiro é o requisito, não essa coordenada específica.

Usar a mesma flag de Gladion é apropriado: ambos pertencem à mesma cena e devem desaparecer juntos depois do ovo. Não criar uma flag persistente separada apenas para Type: Null.

Também vale declarar `local_id` nominal para Gladion no JSON, eliminando a dependência de um `.set` numérico solto no `.pory`.

### Encenação revisada

1. O jogador fala com Gladion.
2. A checagem de party/PC ocorre antes da fala longa e da batalha.
3. Quando Gladion menciona Type: Null, ele se vira para o parceiro.
4. Type: Null reage com uma animação curta, sem caminhar em direção ao jogador.
5. Gladion cura a party e inicia o duelo obrigatório.
6. Vitória, derrota, empate e desistência recebem falas diferentes.
7. Todos os outcomes reais convergem para a entrega do Cosmog Egg.
8. Depois da entrega, Gladion começa a sair; Type: Null hesita brevemente e segue o mesmo caminho atrás dele.
9. Ambos são removidos e `FLAG_HIDE_VIOLET_CITY_GLADION` é marcada.

Em Violet, Type: Null **segue** Gladion. Isso diferencia a cena de Cianwood, onde ele já toma a frente.

### Contrato de batalha

Usar o mesmo padrão já existente em Cianwood e Dragon’s Den:

```text
call Common_EventScript_OutOfCenterPartyHeal
checkflag B_FLAG_NO_WHITEOUT
copyvar <temp_whiteout_anterior>, VAR_RESULT
setflag B_FLAG_NO_WHITEOUT
setvar VAR_LAST_TALKED, LOCALID_VIOLET_GLADION
trainerbattle_no_intro TRAINER_GLADION, <texto_derrota_gladion>
specialvar VAR_RESULT, GetBattleOutcome
copyvar <temp_outcome>, VAR_RESULT
restaurar B_FLAG_NO_WHITEOUT conforme <temp_whiteout_anterior>
call Common_EventScript_OutOfCenterPartyHeal
ramificar outcome
```

Não limpar `B_FLAG_NO_WHITEOUT` incondicionalmente; outro sistema pode tê-la deixado ativa antes do evento. Salvar `GetBattleOutcome` antes da cura, música ou outro `special`.

### Outcomes de Violet

#### Jogador vence

O texto atual pode ser preservado como string automática de derrota de Gladion:

> **Gladion:** We're getting there, Null.
> That was a good battle.

Depois:

> I see why Lillie wants
> another match.

#### Jogador perde

> **Gladion:** You kept looking
> for a way through.

> That's enough for me to understand
> how you fight.

#### Empate

> **Gladion:** Neither team
> could finish that.

> I still saw what I needed to see.

#### Desistência/fuga

> **Gladion:** You're stopping?
> Fine.

> Look after your team.
> Elm's Egg still belongs with you.

#### Resultado inesperado

> **Gladion:** That didn't end cleanly.
> Let's check on everyone.

Recomendação: concluir também nesse branch, seguindo Dragon’s Den, pois o evento já aconteceu e repetir a luta criaria farming/duplicação de experiência. Se a equipe preferir o padrão defensivo atual de Cianwood, documentar a diferença e garantir que o ovo continue recuperável sem softlock.

### Entrega do ovo

Depois de qualquer outcome tratado:

> **Gladion:** Here's the Egg.
> Elm asked me to bring it to you.

> Take care of it.

Ovo na party quando houver espaço; PC quando a party estiver cheia. Confirmar `giveegg` antes de marcar `FLAG_RECEIVED_MYSTERY_EGG`.

A checagem anterior torna `MON_CANT_GIVE` defensiva, mas o fluxo não deve exigir outra batalha caso a entrega falhe excepcionalmente. A opção mais robusta é separar “duelo realizado” de “ovo recebido” com estado persistente próprio. Porém, isso só se justifica se o runtime demonstrar uma falha possível entre a checagem e `giveegg`; não criar flag nova apenas para um estado teoricamente inalcançável.

### Saída de Violet

Gladion já possui duas rotas, dependendo de o jogador estar a oeste. Type: Null precisa de rotas equivalentes, com pequeno atraso visual, seguindo Gladion sem ocupar o mesmo tile.

Critérios:

- enfileirar movimentos de ambos sem atravessar o jogador;
- não fazer os dois tentarem o tile da porta ao mesmo tempo;
- esperar os dois IDs explicitamente;
- remover Type: Null e Gladion;
- só então marcar o ovo/ocultação e liberar controles;
- validar interação a partir de todas as quatro direções permitidas.

---

## 3. Auditoria de Cianwood

### O que já está correto

O branch atual já implementa a maior parte do pedido:

- `LOCALID_CIANWOOD_TYPENULL` existe no `map.json`.
- Type: Null usa `OBJ_EVENT_GFX_SPECIES(TYPE_NULL)`.
- Gladion e Type: Null compartilham `FLAG_HIDE_CIANWOOD_GLADION` como flag de template.
- A visibilidade é recalculada no carregamento a partir de Chuck derrotado e Fly ainda não recebido.
- A batalha é automática e não oferece recusa.
- A checagem de espaço da HM acontece antes do `lockall`.
- O estado anterior de `B_FLAG_NO_WHITEOUT` é preservado e restaurado.
- `GetBattleOutcome` é copiado imediatamente.
- Vitória, derrota, empate e desistência convergem para Fly.
- Type: Null participa da conversa e sai na frente de Gladion.
- `FLAG_RECEIVED_HM_FLY` continua sendo a autoridade da conclusão.

Não vale reimplementar Cianwood do zero. Isso arriscaria quebrar uma solução que já trata respawn de objetos, decorativos, esposa de Chuck, item space, late delivery, música e controles.

### Ajustes recomendados

#### 1. Manter todos os outcomes reais como conclusão

Já está correto para:

- `B_OUTCOME_WON`
- `B_OUTCOME_LOST`
- `B_OUTCOME_DREW`
- `B_OUTCOME_FORFEITED`

O resultado inesperado atualmente cura, restaura decorativos e encerra sem entregar Fly. Isso é defensivo e não contradiz “não precisar ganhar”, porque não representa uma derrota normal. Para uniformidade com Dragon’s Den e com a proposta de Victory Road, recomendo fazê-lo convergir para a entrega, desde que o runtime confirme que não representa uma batalha inválida/link battle que deva ser repetida.

#### 2. Corrigir comentário inconsistente

O comentário em `GladionDeliver` afirma que “UnexpectedOutcome” também converge ali, mas o branch real termina antes. Atualizar o comentário mesmo se o comportamento for mantido.

#### 3. Conferir cura pós-batalha

Todos os branches reais chegam a `GladionDeliver`, que começa com `Common_EventScript_OutOfCenterPartyHeal`. Confirmar em runtime:

- derrota não produz blackout;
- dinheiro não é perdido;
- posição retorna corretamente;
- música de Gladion reinicia;
- Fly é entregue;
- decorativos e esposa de Chuck voltam conforme o fluxo final;
- reentrada não repete a luta.

#### 4. Preservar a encenação existente

Não alterar Type: Null saindo na frente. Essa é a progressão que a Victory Road conclui com os dois lado a lado.

---

## 4. Flags e custo

### Violet

- Gladion e Type: Null podem compartilhar `FLAG_HIDE_VIOLET_CITY_GLADION`.
- `FLAG_RECEIVED_MYSTERY_EGG` permanece a autoridade da entrega.
- Evitar uma flag nova para o parceiro.
- Uma flag separada de “duelo concluído” só seria necessária para recuperar falha real de entrega após a batalha sem repeti-la. Validar se esse estado é alcançável.

### Cianwood

- Gladion e Type: Null já compartilham `FLAG_HIDE_CIANWOOD_GLADION`.
- `FLAG_RECEIVED_HM_FLY` continua sendo a única conclusão persistente.
- Não reintroduzir as flags individuais antigas para Type: Null, Youngster ou Battle Girl como autoridade narrativa.

Adicionar um objeto de Type: Null consome dados de ROM para o template e movimentos, mas compartilhar uma flag evita um estado persistente separado. O bitset de flags continua sendo gerenciado por `FLAGS_COUNT`; medir o delta final da build em vez de estimar pelo número de `#define`.

---

## 5. Checklist de implementação

### Violet

- [ ] Adicionar Type: Null ao `map.json` com local ID nominal.
- [ ] Compartilhar `FLAG_HIDE_VIOLET_CITY_GLADION`.
- [ ] Validar posição/collision e visibilidade em tela.
- [ ] Fazer Gladion olhar para Type: Null durante a apresentação.
- [ ] Adicionar reação curta do parceiro.
- [ ] Preservar/restaurar `B_FLAG_NO_WHITEOUT`.
- [ ] Capturar outcome antes da cura.
- [ ] Criar branches WON/LOST/DREW/FORFEITED/UNKNOWN.
- [ ] Fazer todos os outcomes aprovados convergirem para `giveegg`.
- [ ] Curar depois da batalha.
- [ ] Fazer Type: Null seguir Gladion na saída.
- [ ] Remover os dois objetos coordenadamente.
- [ ] Confirmar party cheia + PC livre.
- [ ] Confirmar party cheia + PC cheio, sem iniciar batalha.
- [ ] Confirmar falha defensiva de `giveegg` sem softlock.
- [ ] Confirmar Route 32 liberada somente depois do ovo.

### Cianwood

- [ ] Vitória entrega Fly.
- [ ] Derrota entrega Fly sem blackout.
- [ ] Empate entrega Fly.
- [ ] Desistência entrega Fly sem whiteout comum.
- [ ] Decidir e documentar `UnexpectedOutcome`.
- [ ] Corrigir comentário divergente.
- [ ] Type: Null permanece visível antes, durante e depois da luta.
- [ ] Type: Null continua sem evoluir.
- [ ] Type: Null sai na frente e Gladion o acompanha.
- [ ] Reentrada após Fly não respawna a dupla.
- [ ] Bolsa cheia não inicia a cena e permite tentar novamente.
- [ ] Late delivery da esposa de Chuck continua funcional.
- [ ] Decorativos, Suicune/Eusine, follower, chuva, música e controles permanecem corretos.

---

## 6. Teste narrativo conjunto

Depois de implementar Violet, jogar as três cenas em sequência e observar apenas o parceiro:

1. **Violet:** Type: Null fica próximo, reage ao jogador e segue Gladion.
2. **Cianwood:** Type: Null demonstra curiosidade, toma a frente e Gladion o acompanha.
3. **Victory Road:** Silvally reconhece o jogador e termina caminhando lado a lado com Gladion.

Se essa progressão for legível sem uma explicação longa, o arco funcionou. Os diálogos servem para apoiar a imagem, não para substituí-la.

---

## 7. Parecer final

**Sim, a revisão vale a pena e Violet deve ser a prioridade imediata.** Ela transforma a primeira aparição do novo Type: Null em algo que o jogador realmente presencia e aplica a política já usada com Lillie: a batalha desenvolve a relação, mas não bloqueia a recompensa por derrota.

Cianwood já está alinhado ao pedido nos outcomes normais e na presença do parceiro. O trabalho ali é testar e corrigir pequenas inconsistências. Depois desses ajustes, Victory Road deixa de apresentar uma evolução sem base visual e passa a concluir uma progressão construída em três encontros.

