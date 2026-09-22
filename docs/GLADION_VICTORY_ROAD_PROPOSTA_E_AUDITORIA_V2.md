# Gladion antes da Victory Road — O primeiro passo

## Proposta consolidada e auditoria V2

**Data:** 18/09/2026  
**Base narrativa:** `SOULGOLD_RIFT_MISSIONS_DESIGN_V13(1).md`  
**Base técnica complementar:** checkout local `soulgold-rift-missions`, commit `87a1acc57d`, conforme auditoria anexada no `Markdown(7).md colado`.

**Status:** implementada em 18/09/2026 (ver seção 13). Esta V2 substitui a V1 onde houver conflito. Build `make -j$(nproc)` limpo; ainda **sem teste em emulador**.

---

## 1. Decisões finais desta revisão

| Tema | Decisão V2 |
|---|---|
| Local | Corredor norte da `ReceptionGate`, imediatamente antes dos warps da Victory Road |
| Momento | Depois de o guarda liberar a passagem e antes de o jogador entrar na caverna |
| Estrutura | Cena automática, cura, duelo obrigatório, outcome próprio e despedida |
| Resultado | Vitória, derrota, empate, desistência e resultado inesperado concluem a cena sem whiteout |
| Equipe | Seis Pokémon: Silvally, Krookodile, Vikavolt, Lycanroc Midday, Zoroark e Gastrodon |
| Níveis | 63–65; abaixo de Silver 66–67 e da Elite Four 68–71 |
| Lead | Silvally nível 65 |
| Parceiro visual | Silvally visível ao lado de Gladion durante toda a cena |
| Saída | Gladion e Silvally caminham lado a lado |
| Música | Preservar por enquanto `Music: Silver` e `MUS_HG_ENCOUNTER_RIVAL`, como nos encontros anteriores de Gladion |
| Estado | Flag própria; `VAR_ROUTE27_STATE` somente como leitura |

Esta versão corrige os dois problemas centrais da V1: preserva a equipe construída desde Violet/Cianwood e cria uma conclusão visual diferente da despedida de Cianwood.

---

## 2. Papel na jornada

O jogador já venceu Clair, passou pelo Dragon’s Den, concluiu a etapa obrigatória do lendário de Johto e chegou à passagem para a Liga. Gladion não está ali para autorizar a entrada. Ele quer comparar o crescimento das duas equipes antes de seguirem caminhos diferentes.

A cena conclui três progressões:

1. **Type: Null tornou-se Silvally.** A mudança decorre da confiança construída durante a viagem, não de uma vitória específica.
2. **Gladion aprendeu a acompanhar seu parceiro.** Em Cianwood, Type: Null saiu na frente e Gladion foi atrás. Aqui, Gladion e Silvally terminam caminhando juntos.
3. **A equipe de Gladion também percorreu Johto.** Sandile, Grubbin e Rockruff, vistos em Violet, agora são Krookodile, Vikavolt e Lycanroc Midday.

O encontro prepara a cooperação de Blackthorn sem mencionar Ultra Beasts, rupturas, Looker ou uma crise futura. O jogador entra sozinho na Victory Road e Silver mantém seu próprio duelo dentro da caverna.

### Ordem narrativa

**Clair → Dragon’s Den/Lillie → lendário de Johto → guarda da ReceptionGate → Gladion/Silvally → Victory Road → Silver → Liga → Blackthorn pós-game.**

---

## 3. Continuidade confirmada

### Violet

`TRAINER_GLADION`:

- Grubbin
- Sandile
- Rockruff
- Type: Null
- níveis 14–15

### Cianwood

`TRAINER_GLADION_CIANWOOD`:

- Krookodile
- Vikavolt
- Lycanroc Midday
- Type: Null
- níveis 43–44

### Victory Road

A equipe final conserva os quatro integrantes e acrescenta duas espécies:

- Type: Null → **Silvally**
- Krookodile permanece
- Vikavolt permanece
- Lycanroc Midday permanece
- **Zoroark** é a nova ameaça especial veloz
- **Gastrodon West Sea** fecha o time e serve como alvo planejado da Illusion

Zoroark e Gastrodon não recebem história retroativa longa. Gladion formou uma equipe completa durante sua própria viagem por Johto. A cena mostra o resultado sem transformar a despedida em uma lista de capturas.

---

## 4. Equipe final proposta

### Curva de níveis

| Treinador | Níveis locais |
|---|---:|
| Clair | 58–59 |
| Lillie no Dragon’s Den | 59–62 |
| **Gladion na ReceptionGate** | **63–65** |
| Silver na Victory Road | 66–67 |
| Will/Koga | 68–69 |
| Bruno | 69–70 |
| Karen/Lance | 70–71 |

Gladion é um boss forte de despedida, mas Silver continua sendo o pico de rivalidade imediatamente anterior à Liga.

### Configuração

- `Smart Trainer`.
- Batalha simples no fluxo normal.
- Replay Doubles pode convertê-la em dupla pelo sistema existente.
- IVs 31.
- EVs específicos abaixo somam 508; as flags de replay podem sobrescrevê-los.
- Sem Mega, Z-Move, Dynamax ou Terastal exclusivo desta cena.
- Silvally deve permanecer no slot 1.
- Gastrodon deve permanecer no slot 6 para a Illusion de Zoroark enquanto for elegível.

### Party

| Slot | Pokémon | Lv | Item | Ability | Nature | EVs | Golpes |
|---:|---|---:|---|---|---|---|---|
| 1 | **Silvally Normal** | **65** | Sitrus Berry | RKS System | Adamant | 156 HP / 252 Atk / 100 Spe | Multi-Attack, Crunch, Ice Fang, Parting Shot |
| 2 | **Krookodile** | 64 | Muscle Band | Intimidate | Jolly | 4 HP / 252 Atk / 252 Spe | Earthquake, Crunch, Rock Slide, Taunt |
| 3 | **Vikavolt** | 63 | Magnet | Levitate | Modest | 252 HP / 252 SpA / 4 SpD | Thunderbolt, Bug Buzz, Energy Ball, Volt Switch |
| 4 | **Lycanroc Midday** | 63 | Focus Sash | Tough Claws | Jolly | 4 HP / 252 Atk / 252 Spe | Accelerock, Stone Edge, Close Combat, Stealth Rock |
| 5 | **Zoroark** | 64 | Expert Belt | Illusion | Timid | 4 HP / 252 SpA / 252 Spe; 0 Atk IV | Dark Pulse, Flamethrower, Grass Knot, U-turn |
| 6 | **Gastrodon West Sea** | 64 | Leftovers | Storm Drain | Calm | 252 HP / 4 Def / 252 SpD; 0 Atk IV | Surf, Earth Power, Ice Beam, Recover |

### Observação de legalidade

Os 24 golpes da V1 haviam sido auditados; 23 eram acessíveis por level-up/TM/tutor, com Morning Sun restrito a egg move. A equipe V2 introduz golpes novos nos três membros preservados. Antes de codificar, validar especificamente `Earthquake`, `Rock Slide`, `Taunt`, `Energy Ball`, `Volt Switch`, `Accelerock`, `Close Combat` e `Stealth Rock` no learnset local ativo. O `trainerproc` pode compilar um golpe que não seria obtível pelo jogador, portanto compilação isolada não certifica a regra de legalidade adotada pelo projeto.

### Função de cada membro

**Silvally** abre por decisão narrativa e mecânica. Multi-Attack é o golpe de assinatura; Parting Shot permite que ele tome a iniciativa sem precisar permanecer até o final. O destaque do ace já ocorre na cena e na abertura, então não se força uma segunda entrada.

**Krookodile** representa a evolução mais direta do time de Violet. Intimidate oferece controle físico e a combinação Ground/Dark pressiona várias respostas. Em Replay Doubles, Earthquake funciona bem ao lado do Levitate de Vikavolt, mas pode atingir outros parceiros; esse comportamento deve ser observado pela IA.

**Vikavolt** traz dano especial lento e pesado. Levitate cria uma dupla natural com Krookodile. Volt Switch preserva mobilidade sem copiar a função exata de Parting Shot.

**Lycanroc Midday** mantém a identidade do Rockruff original. Focus Sash e Accelerock garantem presença sem depender das inatas. Stealth Rock pune trocas, mas deve ser revisto se a IA o usar tarde demais ou se deixar a luta excessivamente automatizada.

**Zoroark** cria a surpresa. Com Gastrodon no slot 6, Illusion pode convidar um golpe Grass e responder com Flamethrower. A estratégia é uma oportunidade, não uma coreografia garantida.

**Gastrodon** fecha a composição com estabilidade, imunidade elétrica e cobertura defensiva para o restante. A fraqueza Grass de 4× permanece deliberadamente aberta. Não usar Rindo Berry nesta versão.

### Inatas

Na campanha padrão desta faixa, as inatas estão bloqueadas:

- Innate 1: nível 75
- Innate 2: nível 85
- Innate 3: nível 95

Logo, nenhuma inata da equipe é considerada no balanceamento principal. Elas entram no teste condicional quando `FLAG_ALL_INNATES_UNLOCKED` estiver ativa pelo Artifact of Chaos ou Max Pain. Também testar `FLAG_REPLAY_NO_INNATES`.

### Ajustes após playtest

1. Se Silvally domina sozinho, reduzir Attack EV antes de alterar sua posição ou identidade.
2. Se o núcleo Krookodile/Vikavolt é forte demais em Doubles, revisar Earthquake ou a ordem de party nesse modo.
3. Se Lycanroc sempre gasta um turno ruim com Stealth Rock, trocar por cobertura ofensiva legal.
4. Se Gastrodon prolonga demais a luta, trocar Leftovers por Sitrus Berry antes de remover Recover.
5. Se Zoroark varre após a Illusion, reduzir cobertura/item antes de mexer no conceito.
6. Não elevar o grupo para 66–67 como primeira resposta; essa faixa pertence a Silver.

---

## 5. Local, gatilho e colisão

### Estrutura real da ReceptionGate

O corredor norte possui quatro colunas andáveis em `x=9..12`. Os warps para `VictoryRoadKanto_B2F` ficam em `(10,1)` e `(11,1)`. As posições candidatas de Gladion `(10,3)`, Silvally `(11,3)` e avanço de Silvally para `(11,4)` são andáveis.

### Gatilho final

- Quatro `coord_events` em `(9,5)`, `(10,5)`, `(11,5)` e `(12,5)`.
- Condição: `VAR_ROUTE27_STATE == 1`.
- Normalizar posição e orientação com `getplayerxy` para as quatro origens.
- Checar direção; se o jogador estiver voltado para sul, veio da caverna e a cena não dispara.
- Como segurança adicional, sair se a flag própria de conclusão estiver marcada ou se `FLAG_IS_CHAMPION` estiver ativa.
- Não colocar evento em cima dos warps.

O gatilho do guarda continua dono da liberação. Gladion não repete checks de insígnia/lendário e nunca escreve em `VAR_ROUTE27_STATE`.

### Estado

Reservar uma flag no bloco custom a partir de `0x103F`, após confirmar que permanece livre no momento da implementação. Nome proposto:

```c
FLAG_GLADION_VICTORY_ROAD_DONE
```

Atualizar `CUSTOM_FLAGS_END`. A flag ocupa um bit no bitset já dimensionado por `FLAGS_COUNT`; a mudança não cria sozinha um byte adicional de save. O custo relevante de ROM também inclui trainer, party, diálogos, movimentos e objetos.

### Objetos

- Local ID 2: Gladion.
- Local ID 3: Silvally.
- Usar `local_id` no `map.json`, seguindo Cianwood.
- O `.set LOCALID_INDIGOJUNCTION_JANINE, 4` é código morto no checkout auditado, mas não precisa ser apagado para implementar a cena.

### Saída

Gladion e Silvally seguem para sul pelas colunas livres, lado a lado. Disparar os dois `applymovement` antes de esperar; executar `waitmovement` para os dois IDs. Removê-los antes do funil próximo de `y=13–14`, evitando o guarda.

---

## 6. Encenação revisada

1. O jogador cruza a linha em direção ao norte.
2. O evento confirma `VAR_ROUTE27_STATE == 1`, direção correta e flag não concluída.
3. Controles, bicicleta e follower são estabilizados.
4. Silvally percebe o jogador, vira e avança um tile.
5. Gladion apresenta Silvally e comenta Cianwood.
6. Gladion anuncia o duelo completo.
7. Cura a party com o evento comum.
8. Preserva o estado anterior de `B_FLAG_NO_WHITEOUT` e ativa a proteção.
9. Inicia a luta obrigatória; Silvally abre.
10. Captura `GetBattleOutcome` imediatamente no retorno.
11. Restaura a flag de no-whiteout ao valor anterior.
12. Cura a party sem repetir um diálogo de cura.
13. Exibe o branch de resultado.
14. Gladion e Silvally olham para a passagem, depois para o jogador.
15. Ambos caminham lado a lado para sul.
16. Gladion para apenas o suficiente para a última frase enquanto Silvally também espera ao lado; os dois retomam a saída simultaneamente.
17. Marca a conclusão, remove os objetos fora do enquadramento, restaura música, follower e controles.
18. O jogador permanece voltado para a Victory Road e decide quando entrar.

Essa saída não repete Cianwood. A progressão visual é clara:

**Type: Null recua da água → toma a frente na despedida de Cianwood → Silvally e Gladion caminham juntos antes da Liga.**

---

## 7. Roteiro final em inglês

As quebras são propostas para caixas GBA e ainda precisam ser medidas com `{PLAYER}` longo. Gladion não possui mugshot local; usar `Gladion:` na primeira caixa de cada turno conforme os encontros existentes.

### Chegada

Silvally vira antes de Gladion, usa seu cry e avança um tile.

> **Gladion:** There you are, {PLAYER}.

> Looks like he noticed you first.

> Remember Type: Null from Cianwood?

> This is Silvally.

Gladion olha para Silvally.

> Back in Cianwood, he walked ahead
> before I was ready.

> I thought I had to call him back.
> I just had to keep up.

### Convite para a batalha

Gladion volta-se ao jogador.

> **Gladion:** Victory Road is ahead.
> We took a different route here.

> Before we go our separate ways,
> I want one more battle.

> All six. Everything we've learned.

> Your team has come a long way too.
> Let's meet at full strength.

Cura.

Gladion olha para Silvally.

> **Gladion:** Ready?

Silvally toma posição.

> Then take the first step.

Não existe menu de recusa.

### Texto de derrota de Gladion

Usar somente quando o jogador vence e o formato da macro exigir uma string durante a batalha:

> ...You got us.
> All six of us.

### Se o jogador vencer

> **Gladion:** I wanted to see how far
> we'd come. You gave us an answer.

Gladion olha para Silvally e para os demais Pokémon já recolhidos.

> We still have work to do.

> Next time, don't expect
> the same battle.

### Se Gladion vencer

> **Gladion:** We were ready this time.

Gladion olha para Silvally.

> You trusted me out there.
> I felt it.

> You know our team better now.
> Next time, make us pay for it.

### Empate

> **Gladion:** Neither team has
> anything left.

> ...We'll settle it another day.

### Desistência ou fuga

> **Gladion:** You're stopping here?
> All right.

> Then we'll leave it unfinished.
> Take care of your team.

### Resultado inesperado

> **Gladion:** That didn't end
> the way I expected.

> Let's make sure everyone's all right.

**Decisão V2:** outcome inesperado conclui a cena, seguindo o modelo do Dragon’s Den. O evento precisa priorizar recuperação segura e evitar repetição/farming.

### Despedida comum

Gladion e Silvally olham para a passagem norte.

> **Gladion:** From here,
> it's you and your team.

> I won't tell you how
> to face the League.

> Just come back with a battle
> worth showing us.

Gladion e Silvally se posicionam lado a lado.

> ...See you after the League,
> {PLAYER}.

Os dois saem juntos.

---

## 8. Música

O checkout confirma que Violet e Cianwood usam `Music: Silver`; Cianwood toca `MUS_HG_ENCOUNTER_RIVAL`. Silver usa a mesma identidade sonora na Victory Road.

**Recomendação V2:** manter essa música nesta implementação. Ela já funciona como identidade recorrente de Gladion neste hack, e trocar apenas no último encontro faria a cena parecer pertencer a outro personagem. A repetição com Silver é uma limitação conhecida, mas os duelos não ocorrem no mesmo mapa nem no mesmo instante: há a entrada e a travessia da Victory Road entre eles.

Se futuramente houver uma faixa existente claramente adequada a Gladion, trocar os três encontros como conjunto. Não atribuir um ID musical não verificado apenas para diferenciar esta cena.

---

## 9. Contrato técnico

### No-whiteout

Copiar o padrão já validado em Cianwood/Dragon’s Den:

```text
call Common_EventScript_OutOfCenterPartyHeal
checkflag B_FLAG_NO_WHITEOUT
copyvar <temp_estado_anterior>, VAR_RESULT
setflag B_FLAG_NO_WHITEOUT
setvar VAR_LAST_TALKED, <local id Gladion>
trainerbattle_no_intro <trainer>, <texto derrota>
specialvar VAR_RESULT, GetBattleOutcome
copyvar <temp_outcome>, VAR_RESULT
restaurar B_FLAG_NO_WHITEOUT conforme <temp_estado_anterior>
curar party
ramificar WON / LOST / DREW / FORFEITED / inesperado
```

Os temporários reais devem ser escolhidos após auditar todos os `call`/`special` usados. Não salvar o outcome em variável que a cura ou a música sobrescreva.

### Regras

- A batalha é obrigatória e não apresenta Yes/No.
- Resultado não governa o acesso à Victory Road.
- `trainer defeated` não é autoridade de conclusão.
- A flag própria é marcada em todos os outcomes tratados.
- Não há revanche infinita.
- Não há recompensa material, TM, Memory ou HM.
- EXP e prize money seguem o sistema existente; derrota não pode aplicar penalidade de whiteout.
- Itens consumidos do jogador seguem o comportamento global existente; a cura não promete restaurá-los.
- Party com 1–6 combatentes funciona; “All six” descreve a equipe de Gladion.
- Save antigo já além de Silver/Liga não recebe um bloqueio retroativo.
- Blackthorn não depende da nova flag, protegendo saves antigos.

### Silver

`VAR_ROUTE27_STATE` permanece:

- 0: guarda ainda não liberou.
- 1: passagem liberada; janela de Gladion e depois Silver.
- 2: Silver concluído.

Gladion apenas lê `VAR_ROUTE27_STATE == 1`. Silver mantém seus três triggers, a própria luta e a entrega de Rock Climb.

### Replay

`ShouldForceReplayTrainerDoubles` pode converter a batalha em dupla. Testar:

- modo normal simples;
- Replay Doubles;
- trainer perfect IVs;
- trainer max EVs;
- inatas normais bloqueadas;
- Artifact/Max Pain com inatas liberadas;
- replay sem inatas.

---

## 10. Auditoria consolidada

| ID | Achado | Estado V2 |
|---|---|---|
| C01 | V1 descartava o núcleo de Gladion | **Corrigido:** quatro membros preservados |
| C02 | V1 repetia a saída de Cianwood | **Corrigido:** Gladion e Silvally saem lado a lado |
| C03 | V1 usava “it” para Type: Null/Silvally | **Corrigido:** “he/him”, conforme texto local |
| C04 | V1 referia Violet na apresentação | **Corrigido:** Cianwood, encontro mais recente |
| C05 | Duas curas eram anunciadas | **Corrigido:** fala única antes; cura silenciosa depois |
| C06 | Faixa 64–66 encostava demais em Silver | **Corrigido:** 63–65 |
| C07 | Inatas tratadas como risco principal | **Corrigido:** risco condicional a flags especiais |
| C08 | Gatilho cobria colunas insuficientes | **Corrigido:** quatro tiles em x=9..12 |
| C09 | Cena poderia disparar na volta | **Corrigido no contrato:** checagem de direção/transition |
| C10 | IDs locais incertos | **Resolvido pela auditoria:** objetos 2 e 3 |
| C11 | Estado poderia conflitar com Silver | **Resolvido:** flag própria; variável vanilla só lida |
| C12 | Música tratada como identidade distinta | **Corrigido:** é compartilhada com Silver; repetição aceita conscientemente |
| C13 | Morning Sun não atendia à regra de obtenção | **Removido com Arcanine** |
| C14 | Novos golpes do núcleo não foram auditados | **Resolvido:** os 24 golpes conferidos no learnset ativo (seção 13.2) |
| C15 | Replay Doubles altera o lead efetivo | **Incluído nos testes:** Silvally + Krookodile |
| C16 | Earthquake pode atingir parceiro em Doubles | **Pendente de IA/playtest**, especialmente fora do par com Vikavolt |
| C17 | Rotas antigas da ReceptionGate têm bugs próprios | **Fora do escopo:** Route22 aponta para warp inexistente; warp 3 está em parede |

### Riscos que permanecem reais

1. ~~Legalidade local dos golpes novos de Krookodile, Vikavolt e Lycanroc.~~ Resolvido na implementação (seção 13.2).
2. Qualidade da IA com Parting Shot, Volt Switch, Stealth Rock e Earthquake em Doubles.
3. Colisão/follower nos quatro pontos de entrada, apesar dos tiles andáveis já confirmados.
4. Preservação do outcome após cura e restauração da flag de no-whiteout.
5. Comprimento real das caixas com nome máximo do jogador.
6. Balanceamento com Artifact ligado, pois as inatas podem mudar bastante o confronto.

---

## 11. Matriz mínima de testes

| Cenário | Resultado esperado |
|---|---|
| Sem badge 8 | Guarda mantém o bloqueio; Gladion não aparece |
| Badge 8, lendário incompleto | Orientação original continua |
| Guarda libera normalmente | `VAR_ROUTE27_STATE` vira 1; Gladion aparece adiante |
| Aproximação por x=9,10,11,12 | Cena única, sem desvio |
| Retorno da caverna voltado ao sul | Cena não dispara |
| Vitória | Branch de vitória, cura, saída lado a lado, flag marcada |
| Derrota | Branch de derrota; sem blackout nem perda de dinheiro |
| Empate | Branch próprio e conclusão |
| Fuga/desistência | Branch próprio; sem fluxo comum de whiteout |
| Outcome inesperado | Cleanup, cura e conclusão segura |
| Party com 1 combatente | Batalha ocorre normalmente |
| Party com ovos | Ovos não contam como combatentes; sem softlock |
| Follower de tamanhos variados | Sem colisão ou desaparecimento permanente |
| Bicicleta | Jogador normalizado e controle restaurado |
| Reentrada após cada outcome | Gladion e Silvally não reaparecem |
| Save/reload | Conclusão persistente |
| Entrada na Victory Road | Silver dispara normalmente |
| Vitória sobre Silver | Rock Climb entregue; estado vira 2 |
| Replay Doubles | Silvally/Krookodile entram; IA não destrói o próprio time |
| Perfect IV/Max EV replay | Overrides funcionam sem duplicar efeitos |
| Artifact desligado | Caso principal sem inatas |
| Artifact ligado | Dificuldade ainda justa e sem interação quebrada |
| Pós-Liga/Blackthorn | Silvally permanece evoluído; arco pós-game acessível |

---

## 12. Parecer

A direção está pronta para implementação com uma identidade mais forte do que a V1. A equipe agora conta uma história contínua: os quatro parceiros vistos desde Violet/Cianwood chegam evoluídos, enquanto Zoroark e Gastrodon completam o desafio. A saída lado a lado transforma o eco de Cianwood em progressão visível.

Antes de escrever o trainer definitivo, falta uma auditoria curta dos oito golpes novos do núcleo preservado. Depois disso, o evento pode ser implementado com o padrão sem whiteout já usado no projeto, quatro triggers na faixa `y=5`, flag custom própria e regressão obrigatória de Silver/Rock Climb.

---

## 13. Implementação

**Data:** 18/09/2026 · **Branch:** `soulgold-rift-missions` · **Build:** `make -j$(nproc)` limpo · **Emulador:** não testado.

### 13.1 Arquivos alterados

| Arquivo | Mudança |
|---|---|
| `include/constants/opponents.h` | `TRAINER_GLADION_VICTORY_ROAD = 971`, reaproveitado de `TRAINER_UNUSED_107` (livre segundo `ids_livres.py`, sem referências fora de `opponents.h`) |
| `src/data/trainers.party` | Bloco `=== TRAINER_GLADION_VICTORY_ROAD ===` no fim do arquivo, com a party da seção 4 |
| `include/constants/flags.h` | `FLAG_GLADION_VICTORY_ROAD_DONE = 0x103F`; `CUSTOM_FLAGS_END` atualizado |
| `data/maps/ReceptionGate/map.json` | Objetos Gladion (10,3) e Silvally (11,3), `FACE_UP`, `script: NULL`, `flag: FLAG_TEMP_1`; quatro `coord_events` em `(9..12, 5)` com `VAR_ROUTE27_STATE == 1` |
| `include/constants/map_event_ids.h` | `LOCALID_RECEPTIONGATE_GLADION 2` e `LOCALID_RECEPTIONGATE_SILVALLY 3`, editados à mão e confirmados pelo build |
| `data/maps/ReceptionGate/scripts.inc` | `MAP_SCRIPT_ON_TRANSITION`, rotina de visibilidade, chamada dela no gatilho do guarda e a cena completa |
| `src/data/pokemon/species_info/gen_7_families.h` | Lycanroc Midday: `ABILITY_KEEN_EYE` → `ABILITY_TOUGH_CLAWS` no slot 1 (ver 13.3) |

O mapa não tem `.pory`; a edição foi feita direto no `.inc`.

### 13.2 Auditoria de legalidade (C14)

Conferido contra `generated_legacy_level_up_learnsets.h` (o conjunto ativo: `P_LVL_UP_LEARNSETS = GEN_LATEST` com `P_LEGACY_LVL_UP_LEARNSETS = TRUE`) e `teachable_learnsets.h`.

| Pokémon | Golpe | Level-up | Ensinável |
|---|---|---:|:---:|
| Silvally | Multi-Attack | evolução | — |
| Silvally | Crunch | 45 | ✓ |
| Silvally | Ice Fang | 1 | ✓ |
| Silvally | Parting Shot | 60 | — |
| Krookodile | Earthquake | 44 | ✓ |
| Krookodile | Crunch | 27 | ✓ |
| Krookodile | Rock Slide | — | ✓ |
| Krookodile | Taunt | — | ✓ |
| Vikavolt | Thunderbolt | evolução | ✓ |
| Vikavolt | Bug Buzz | 36 | ✓ |
| Vikavolt | Energy Ball | — | ✓ |
| Vikavolt | Volt Switch | — | ✓ |
| Lycanroc Midday | Accelerock | 1 | — |
| Lycanroc Midday | Stone Edge | 60 | ✓ |
| Lycanroc Midday | Close Combat | — | ✓ |
| Lycanroc Midday | Stealth Rock | 54 | ✓ |
| Zoroark | Dark Pulse | — | ✓ |
| Zoroark | Flamethrower | — | ✓ |
| Zoroark | Grass Knot | — | ✓ |
| Zoroark | U-turn | 1 | ✓ |
| Gastrodon West | Surf | — | ✓ |
| Gastrodon West | Earth Power | 39 | ✓ |
| Gastrodon West | Ice Beam | — | ✓ |
| Gastrodon West | Recover | 1 | — |

Os 24 golpes são obtíveis. Os dois que dependem de nível (Parting Shot 60 e Stone Edge 60) ficam abaixo dos níveis da party (65 e 63).

Abilities conferidas contra o `.abilities` de cada espécie: RKS System, Intimidate, Levitate, Illusion e Storm Drain são válidas.

### 13.3 Tough Claws no Lycanroc Midday

Na base original, o Lycanroc Midday tinha `{ KEEN_EYE, SAND_RUSH, STEADFAST }`. Com isso, `Ability: Tough Claws` compilaria, mas a batalha **estouraria em runtime** (`CreateNPCTrainerPartyFromTrainer`, "illegal ability").

**Decisão:** trocar Keen Eye por Tough Claws na própria espécie. Agora ela é `{ TOUGH_CLAWS, SAND_RUSH, STEADFAST }`, e a party usa Tough Claws, como previsto na seção 4.

Efeitos colaterais conhecidos:

- Nenhum trainer do `trainers.party` usa Lycanroc Midday com Keen Eye. Cianwood usa Sand Rush, que continua válido.
- A mudança vale para o jogo inteiro. Lycanroc Midday do jogador e selvagens que caem no slot 1 passam a ter Tough Claws, inclusive os que já existem em saves, porque o save guarda o índice do slot.
- As inatas (Sturdy, Guard Dog, Battle Armor) não mudaram.

### 13.4 Planta final da cena

```
        x= 9 10 11 12
   y=1   #  W  W  #      warps para VictoryRoadKanto_B2F
   y=3   .  G  S  .      início: Gladion (10,3), Silvally (11,3), olhando para norte
   y=4   .  G' S' .      após a chegada
   y=5   t  P  .  .      t = gatilho; jogador normalizado em (10,5), olhando para norte
   ...                   colunas 9..12 livres até y=12
   y=13  #  #  .  .      funil do guarda
```

- **Chegada:** Silvally vira para sul, mostra `!`, usa o cry e desce para (11,4). Gladion vira e desce para (10,4), logo à frente do jogador.
- **Olhares:** Gladion ↔ Silvally usam `DIR_EAST`/`DIR_WEST`. Os dois olham para o jogador com `DIR_SOUTH`. Todos os olhares usam `turnobject`, sem nenhum `faceplayer`.
- **Normalização:** `getplayerxy`. Vindo de x=9, o jogador dá um passo para leste. De 11 ou 12, dá um ou dois passos para oeste. De 10, não anda.
- **Saída:**
  - Silvally (11,4) → (12,4) → espera um passo → (12,5).
  - Gladion (10,4) → espera um passo → (11,4) → (11,5). Ele só entra em (11,4) um passo inteiro depois que Silvally saiu.
  - Os dois param a leste do jogador (`DIR_WEST`) para a última frase, e o jogador vira para leste.
  - Depois descem juntos até y=12. Os dois `applymovement` são disparados antes de um `waitmovement` com o ID de cada um.
  - São removidos fora da tela, antes do funil. O jogador termina olhando para norte, para a Victory Road.

### 13.5 Estado, visibilidade e gatilho

- **Visibilidade:** `FLAG_TEMP_1` funciona como cache local do mapa (skill `visibilidade-e-gatilhos` §6). A rotina `ReceptionGate_EventScript_ApplyGladionVisibility` mostra o par só quando `VAR_ROUTE27_STATE == 1`, `FLAG_GLADION_VICTORY_ROAD_DONE` está limpa e `FLAG_IS_CHAMPION` está limpa.
  - Ela roda no `ON_TRANSITION` e também logo depois de `setvar VAR_ROUTE27_STATE, 1` no gatilho do guarda.
  - O guarda fica em y=14, fora do alcance de spawn de y=3. Por isso o par aparece quando a câmera chega ao corredor, sem `addobject`.
- **Gatilho:** `ReceptionGate_EventScript_GladionTrigger` sai sem travar o jogador se a flag de conclusão ou `FLAG_IS_CHAMPION` estiverem marcadas, ou se o jogador não estiver olhando para `DIR_NORTH`. Isso cobre a volta da caverna e o passo lateral dentro de y=5.
- **`VAR_ROUTE27_STATE`:** só é lida, nunca escrita. O guarda continua dono do 0 → 1 e o `VictoryRoadKanto_1F` do 1 → 2.
- **Conclusão:** `FLAG_GLADION_VICTORY_ROAD_DONE` é marcada no início da despedida comum, para a qual convergem os cinco resultados.
- **Temporárias:**
  - `VAR_0x8004/8005`: posição do jogador.
  - `VAR_TEMP_2`: resultado da batalha.
  - `VAR_TEMP_3`: estado anterior de `B_FLAG_NO_WHITEOUT`.
  - Todas são escritas antes de serem lidas.
- **Seguidor do jogador:** `hidefollower` no início da cena. A cura (`Common_EventScript_OutOfCenterPartyHeal`) chama `UpdateFollowingPokemon`.
- **Bicicleta:** o jogador não é tirado dela. Os passos de normalização funcionam montado.

### 13.6 Batalha e resultados

O fluxo segue a seção 9 à risca:

1. Cura com fala antes da luta.
2. Salva `B_FLAG_NO_WHITEOUT` em `VAR_TEMP_3` e a ativa.
3. `trainerbattle_no_intro TRAINER_GLADION_VICTORY_ROAD`.
4. Copia `GetBattleOutcome` para `VAR_TEMP_2` imediatamente.
5. Restaura a flag de no-whiteout.
6. Cura silenciosa.
7. Volta `MUS_HG_ENCOUNTER_RIVAL`.
8. Ramos `WON`, `LOST`, `DREW`, `FORFEITED` e inesperado, todos com o texto da seção 7.
9. Despedida comum, tocando `MUS_HG_RIVAL_EXIT`.

A música de saída é a mesma de Cianwood, para manter a identidade sonora de Gladion (seção 8).

### 13.7 Ajustes de texto

Dois textos foram quebrados de outra forma para não passar de 35 caracteres por linha:

- "Gladion: Back in Cianwood, he / walked ahead before I was ready."
- "Let's make sure / everyone's all right."

O restante do roteiro da seção 7 foi mantido palavra por palavra.

### 13.8 Pendências

Toda a matriz da seção 11 continua pendente de emulador, com prioridade para:

1. Entrada pelas quatro colunas; volta da caverna sem disparo.
2. Derrota proposital sem blackout nem perda de dinheiro.
3. Reentrada e save/reload: o par não reaparece.
4. Silver e Rock Climb intactos depois da cena.
5. Replay Doubles com Silvally e Krookodile.
6. Caixas de texto com `{PLAYER}` de 7 caracteres.
7. Seguidor de tamanho grande durante a normalização e a saída.
