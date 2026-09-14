# Auditoria — Gladion em Cianwood / entrega de Fly

> Auditoria somente leitura. Nenhum código, mapa ou derivado foi alterado nesta tarefa.

## Escopo e estado do checkout

- Branch: `soulgold-rift-missions`
- HEAD: `a5956912f9dbf2480224a9067334d2c4f74b0afc` ("Lillie Goldenrod")
- Alterações locais não commitadas no momento da auditoria: `.claude/SOULGOLD_RIFT_MISSIONS_DESIGN_V1.md` modificado; vários docs de auditorias antigas (`docs/LILLIE_GOLDENROD_*`, `docs/TOGEPI_COSMOG_SWAP_AUDIT.md`, `docs/TRAINER_BATTLES_ACCESSIBILITY_AUDIT.*`, `docs/PROMPT_REMOVE_DIFFICULTY_AND_INACCESSIBLE_TRAINERS.md`) marcados como deletados na árvore de trabalho; `docs/PROMPT_AUDITORIA_GLADION_CIANWOOD_FLY.md` não rastreado. Nada disso foi tocado por esta auditoria.
- Esta é uma passada rigorosa mas **não exaustiva** sobre as seis seções do prompt: priorizei os pontos que decidem viabilidade (controle real de Fly, mecanismo de batalha com continuidade, limite de objetos ativos, existência de assets) e não persegui cada sub-item do checklist final até o fim (ex.: não abri o disassembly de `giveitem`/`CheckBagHasSpace` linha a linha, não naveguei todas as saídas de mapa da praia de Cianwood). Onde não verifiquei, digo explicitamente "não verificado" em vez de presumir.

## A. Veredito

**Viável com ajustes.** O controle real de entrega de Fly (`VAR_GETFLY`) existe, é único, e pode ser reutilizado como o plano pede. O mecanismo de "batalha com continuidade após derrota" já está implementado neste checkout (evento de Lillie em Goldenrod) e é replicável sem flags novas. Os assets gráficos de Gladion e de Type: Null (overworld) já existem no repositório. Os impeditivos não são de mecanismo, e sim de:

1. **Risco de entrega duplicada de Fly já existente hoje**, independente do plano novo (achado GLD-01, severidade alta) — precisa ser corrigido ou pelo menos absorvido pelo novo fluxo antes de empilhar mais lógica em cima.
2. **Orçamento de object events em runtime é apertado** (`OBJECT_EVENTS_COUNT = 16`) frente aos objetos já definidos em Cianwood City e a mais dois objetos (Gladion + Type: Null) somados a jogador/follower (achado GLD-02, severidade média-alta) — precisa de medição real em jogo, não só leitura de mapa.
3. **Dessincronia entre `FLAG_DEFEATED_CIANWOOD_GYM`/`FLAG_BADGE05_GET`/`VAR_GETFLY`** cria janelas onde os três não avançam juntos — o plano depende de "recebeu Fly" ser uma condição única e estável, e hoje ela não é (achado GLD-03).

Nenhum desses é bloqueador estrutural: todos têm correção sem flags novas, descrita abaixo. Nenhuma decisão de design (equipe do Chuck, equipe nova de Gladion, dificuldade) foi tomada aqui.

## B. Evento atual

**Cadeia real, verificada por leitura de código:**

1. `data/maps/CianwoodGym/scripts.inc` → `CianwoodGym_EventScript_Chuck` — diálogo/batalha do ginásio. Ao vencer, cai em `CianwoodGym_EventScript_ChuckVictory` (linhas 59–77):
   - `setflag FLAG_BADGE05_GET`
   - `setflag FLAG_DEFEATED_CIANWOOD_GYM`
   - `giveitem ITEM_TM_BULK_UP` (TM, não é a Fly)
   - `setvar VAR_GETFLY, 1` ← **este é o controle real que dispara a entrega da HM**
   - `setrespawn HEAL_LOCATION_CIANWOOD_CITY`
2. `data/maps/CianwoodCity/scripts.inc`:
   - `CianwoodCity_OnFrame` (map script `MAP_SCRIPT_ON_FRAME_TABLE`, linha 12-14): `map_script_2 VAR_GETFLY, 1, CianwoodCity_EventScript_Flytrigger` — dispara **automaticamente**, todo frame, sempre que a Cianwood City está carregada e `VAR_GETFLY == 1`.
   - `CianwoodCity_EventScript_Flytrigger` (linhas 34–47): faz a esposa de Chuck (`LOCALID_CIANWOOD_CHUCKSWIFE`) se aproximar do jogador, `giveitem ITEM_HM_FLY` **sem checar bolsa cheia nem se o item já existe**, mostra fala, e só então `setvar VAR_GETFLY, 2`.
   - `CianwoodCity_EventScript_ChucksWife` (linhas 64–88): interação manual com a NPC. Usa `checkitem ITEM_HM_FLY` para decidir a fala, e se `FLAG_BADGE05_GET` estiver setada dá o item de novo via `CianwoodCity_EventScript_ChucksWifeGiveFly` — **mas não seta `VAR_GETFLY` para 2**.
3. Item entregue: `ITEM_HM_FLY` (`src/data/items.h:14815`), pocket `POCKET_TM_HM`, `importance = 1`. HMs neste engine (pokeemerald-expansion) não são consumíveis nem têm "espaço" limitado por slot da forma como itens normais têm — cada HM ocupa uma entrada fixa na pasta de TM/HM.
4. Controle real de conclusão: **`VAR_GETFLY`** (0 = não elegível, 1 = elegível/pendente, 2 = já entregue). Permissão de uso de Fly no mapa é outra coisa: vem de `FLAG_BADGE05_GET` (ver `include/config/battle.h:251`, que também usa essa flag para o bônus de defesa de badge — é a flag oficial de "possui a Storm Badge", não específica de Fly). O registro de destinos de Fly é outro sistema (flags de "visitou local"), fora do escopo desta entrega.

**Localização da esposa de Chuck:** `data/maps/CianwoodCity/map.json`, objeto `LOCALID_CIANWOOD_CHUCKSWIFE`, `graphics_id: OBJ_EVENT_GFX_WOMAN_3`, posição (18,47), `movement_type: MOVEMENT_TYPE_WANDER_AROUND`, sem flag de visibilidade condicional (`"flag": "0"`) — ou seja, ela está sempre presente no mapa, ganha ou não Fly.

## C. Achados priorizados

| ID | Severidade | Falha/risco | Evidência: arquivo, símbolo e linhas | Condição de reprodução | Correção mínima sem novas flags |
| --- | --- | --- | --- | --- | --- |
| GLD-01 | Alta | Entrega manual de Fly pela esposa (`CianwoodCity_EventScript_ChucksWifeGiveFly`) não avança `VAR_GETFLY` para 2. Se o jogador falar com ela manualmente antes do trigger automático de frame rodar (ex.: entra no mapa e já a aborda no mesmo frame, ou savestate/timing), recebe a HM, mas `VAR_GETFLY` continua 1 → no próximo recarregamento do mapa o `map_script_2` dispara `Flytrigger` de novo e **dá a HM pela segunda vez** (ela verifica `checkitem` só no ramo do diálogo manual, não no trigger automático). | `data/maps/CianwoodCity/scripts.inc:34-47` (Flytrigger, sem checkitem) vs `:64-88` (ChucksWifeGiveFly, não seta VAR_GETFLY) | Falar com a esposa manualmente entre sair do ginásio e o primeiro frame de Cianwood City processar o `map_script_2` (tecnicamente possível se o jogador for teleportado/warpado diretamente para perto dela, ou em builds com frame-skip) | Fazer `CianwoodCity_EventScript_ChucksWifeGiveFly` também `setvar VAR_GETFLY, 2` antes de `release`. Não introduz flag nova, só sincroniza o controle já existente. |
| GLD-02 | Média-alta | `OBJECT_EVENTS_COUNT = 16` (`include/constants/global.h:83`) é o teto de object events ativos simultaneamente no engine (jogador + follower + NPCs carregados nos mapas conectados). Cianwood City já define 19 objetos no `map.json` (não todos ativos ao mesmo tempo, mas incluindo Suicune/Eusine, transeuntes, Chuck's wife etc.), mais mapas conectados. Adicionar Gladion + Type: Null como dois objetos permanentes simultâneos no momento certo do jogo aumenta a pressão sobre esse teto. | `include/constants/global.h:83`; `data/maps/CianwoodCity/map.json` (19 `graphics_id` entries) | Não reproduzido em emulador nesta auditoria — é um risco de leitura estática, não teste real. Precisa ser medido em jogo no ponto da progressão onde a cena ocorreria (quais outros objetos de Cianwood/mapas vizinhos estão carregados nesse momento). | Nenhuma correção de código aqui — é um dado de orçamento que o refinamento precisa levantar antes de commitar a posições dos dois novos objetos. Se apertado, usar objetos que só existem enquanto a flag/controle de "Fly pendente com Gladion" está ativa (mesmo padrão de `addobject`/`removeobject` que Eusine/Suicune já usam nesse mesmo mapa). |
| GLD-03 | Média | Três controles avançam de forma independente ao vencer Chuck: `FLAG_RECEIVED_BADGE_5` (setado dentro de `CianwoodGym_EventScript_Chuck_Battle1/2/3`, um flag genérico também usado por Mahogany e Olivine — não é exclusivo de Cianwood, é reaproveitado por ordem de badge, não por localidade), `FLAG_BADGE05_GET` + `FLAG_DEFEATED_CIANWOOD_GYM` (setados em `ChuckVictory`), e `VAR_GETFLY`. O plano do Gladion precisa de "o jogador já pode receber Fly" como uma condição única e estável; hoje isso é `VAR_GETFLY == 1` (pendente) ou `== 2` (recebido), que é o controle certo, mas quem for revisar o evento sem ler isto pode confundir com `FLAG_BADGE05_GET` (que também controla o bônus de defesa de badge global, `include/config/battle.h:251` — reaproveitar essa flag para outra coisa seria errado). | `data/maps/CianwoodGym/scripts.inc:64-77,110-123`; `include/config/battle.h:251` | N/A (achado de leitura de código, não de reprodução em jogo) | Nenhuma mudança necessária além de documentar explicitamente no futuro refinamento que o único controle a ler/gravar é `VAR_GETFLY`, nunca `FLAG_BADGE05_GET` nem `FLAG_RECEIVED_BADGE_5`. |
| GLD-04 | Baixa-média | O aviso vago combinado ("Agora não. Estou terminando um treino com ele." / "Volte depois.") do passo 3 do plano não deixa claro ao jogador *o que* falta (badge vs. já recebeu vs. outra condição futura), especialmente porque o requisito real de disponibilidade (`VAR_GETFLY == 1`) é opaco para quem não tem Storm Badge ainda — nesse caso a interação manual com Gladion antes de vencer Chuck nem deveria ser possível fisicamente (ele só apareceria perto do ginásio depois do requisito), mas não há registro/objeto dele no mapa hoje para confirmar isso; ver seção F. | Não localizado (Gladion/Type: Null ainda não têm objeto definido em nenhum `map.json` de Cianwood) | — | Registrar o achado sem substituir a fala aprovada, conforme pedido no prompt. Recomendação: a condição de bloqueio deveria depender apenas de `VAR_GETFLY != 1` (ainda não elegível ou já entregue), nunca aparecer se a badge não foi conquistada — isso é uma decisão de objeto/spawn, não de flag nova. |

Não encontrei, nesta passada, evidência de sumiço indevido de outro NPC, perda de progresso, ou consumo de flags de terceiros — mas também não tracei todos os `map_script`/eventos de Cianwood City e do ginásio (ex.: Suicune/Eusine trigger, que compartilha o mesmo mapa e pode competir por slots de objeto — ver GLD-02). Ausência de achado aqui não é prova de ausência do problema.

## D. Controles reutilizados

| Controle real | Significado atual | Uso proposto | Outros consumidores | Persistência e conflitos |
| --- | --- | --- | --- | --- |
| `VAR_GETFLY` (0/1/2) | 0 = Chuck não derrotado; 1 = derrotado, entrega pendente; 2 = HM já entregue | Mesma semântica: a checagem prévia do Gladion e a entrega final devem ler/escrever exatamente este var, sem criar variável irmã | `CianwoodGym_EventScript_ChuckVictory` (seta 1), `CianwoodCity_OnFrame`/`Flytrigger` (lê 1, seta 2), `CianwoodCity_EventScript_ChucksWife*` (lê via `checkitem`, não via este var — inconsistência já registrada em GLD-01), `OlivineCity/scripts.inc:124` (`setvar VAR_GETFLY, 0` — resetado lá, precisa entender por quê antes de mexer; não investiguei essa dependência a fundo nesta passada) | É uma var global de save, sem reset por save/load. Nenhum consumidor além dos listados foi encontrado nesta busca (`grep` no repositório inteiro por `VAR_GETFLY`), mas a ocorrência em `OlivineCity/scripts.inc:124` merece investigação dedicada no refinamento — não presumir que é irrelevante só porque é outro mapa. |
| `FLAG_BADGE05_GET` | Storm Badge obtida (flag de sistema, também usada pelo bônus de defesa de badge do battle engine) | Apenas como *pré-condição de leitura* (o jogador precisa da badge para o evento fazer sentido), nunca como controle de conclusão do evento do Gladion | `include/config/battle.h:251` (B_FLAG_BADGE_BOOST_DEFENSE), `data/scripts/players_house.inc:367`, `data/maps/BlackthornCity/scripts.inc` (gating de Gym Boy), `BattleFrontier_ExchangeServiceCorner` | Reaproveitável como leitura, nunca como escrita/gravação nova de significado. |
| Nenhum objeto/flag de Gladion/Type: Null em Cianwood | N/A — não existe hoje | O plano propõe compartilhar o mecanismo de presença com `VAR_GETFLY` (objeto visível apenas enquanto `VAR_GETFLY == 1`, some quando vira `2`) | — | Ver seção F: não há nenhum `LOCALID` reservado para Gladion/Type: Null em `CianwoodCity/map.json` nem em `CianwoodGym/map.json` hoje. Precisa ser criado no refinamento (custo de "entrada/ID de treinador" citado nas restrições — não é uma flag de história nova, é o custo normal de adicionar um NPC). |

## E. Fluxo corrigido

Descrição do fluxo proposto, separando o que já está **comprovado por código existente** (equivalente já implementado em Lillie/Goldenrod ou no próprio evento de Chuck) do que é **proposta ainda não implementada** para Cianwood.

- **Entrada / checagem prévia** (proposta): antes de qualquer diálogo/movimento/batalha do Gladion, checar `VAR_GETFLY == 1` (elegível, ainda não recebido). Padrão análogo já existe: `CianwoodCity_OnFrame` já usa exatamente essa mesma condição (`map_script_2 VAR_GETFLY, 1, ...`) para o trigger da esposa — reaproveitar a leitura, não necessariamente o gatilho automático de frame (o plano quer interação manual, não automática).
- **Impedimento inicial** (proposta): se `VAR_GETFLY != 1` (badge ainda não obtida OU já recebeu Fly), Gladion mostra a fala curta e libera controle sem progressão. Nenhum precedente direto no código para essa fala específica; é texto novo.
- **Aceite/recusa** (proposta, sem precedente direto de "recusa pula pra entrega" no código atual — o evento de Lillie sempre batalha, não tem opção de recusa com entrega imediata. Isso é fluxo novo, ainda que simples).
- **Batalha com continuidade em derrota** (**comprovado por precedente real**: `data/maps/GoldenrodCity_FlowerShop/scripts.inc:710-760`, evento de Lillie). Padrão a copiar:
  1. `checkflag B_FLAG_NO_WHITEOUT` → salvar estado anterior em variável temporária (`VAR_TEMP_5` no exemplo de Lillie).
  2. `setflag B_FLAG_NO_WHITEOUT` antes da batalha.
  3. `trainerbattle_no_intro TRAINER_X, texto_derrota`.
  4. `specialvar VAR_RESULT, GetBattleOutcome` **imediatamente após**, antes de qualquer cura ou outra chamada — copiar para var temporária própria.
  5. Restaurar `B_FLAG_NO_WHITEOUT` ao estado salvo (só limpar se estava limpo antes; se já estava setada por outro motivo, não mexer — é exatamente o que o código de Lillie faz e o prompt pede para replicar).
  6. Ramificar em `B_OUTCOME_WON` / `B_OUTCOME_LOST` / `B_OUTCOME_DREW` / `B_OUTCOME_FORFEITED` (todas as quatro já são tratadas no evento de Lillie — usar como referência de quais resultados o engine realmente produz aqui, incluindo empate e desistência).
  7. Curar depois (fala + cura, não antes da leitura do resultado).
- **Vitória/derrota** (proposta de texto; mecanismo de captura de resultado comprovado acima).
- **Entrega de Fly** (comprovado: `giveitem ITEM_HM_FLY` já existe em `CianwoodCity_EventScript_ChucksWifeGiveFly`; reaproveitar a chamada, script e mensagens, mas garantir que segue confirmando sucesso e setando `VAR_GETFLY, 2` como em `Flytrigger` — ver GLD-01). Não duplicar a entrega feita pela esposa: a interação manual dela precisa continuar funcionando para quem nunca cruzar com Gladion (ex.: se o refinamento tornar o encontro dele evitável), então os dois caminhos de entrega devem convergir no mesmo `giveitem` + `setvar VAR_GETFLY, 2`, nunca dois `giveitem` independentes.
- **Reentrada/saída** (proposta): remoção dos dois objetos, restauração de música/controles — sem precedente direto de "dois NPCs saindo juntos" no código auditado; o evento de Suicune/Eusine no mesmo mapa (`CianwoodCity_EventScript_SuicuneTrigger`) é a referência mais próxima de sequência de `applymovement` + `removeobject` para *dois* objetos em cena (Suicune e Eusine), incluindo restauração de música (`fadedefaultbgm`) — vale usar como modelo de "coreografia de saída com música", mas ele é definitivo (Suicune/Eusine somem para sempre), enquanto o Gladion deveria reaparecer coerente em Blackthorn — isso é comportamento não verificado nesta auditoria (não explorei os mapas de Blackthorn).
- **Falha excepcional de entrega**: não há precedente de tratamento explícito de "giveitem falhou" nem em Chuck's wife nem em Lillie para a HM/objeto principal — ambos assumem sucesso. Isso é uma lacuna real de robustez que o plano já reconhece (restrição "confirmar sucesso antes de marcar"), mas o padrão a copiar (`copyvar VAR_0x8008, VAR_RESULT` + `goto_if_eq ..., MON_CANT_GIVE, ...`) existe no evento de Gladion em Violet para o ovo (`VioletCity_PokemonCenter_EventScript_Gladion_Battle:74-76`), não para itens de bolsa — o equivalente para `giveitem` (que retorna `VAR_RESULT` TRUE/FALSE, não os mesmos códigos de "dar mon") precisa ser conferido separadamente; não verifiquei o retorno exato de `giveitem` nesta passada.

## F. Referências para o futuro refinamento

- **Arquivos a alterar:** `data/maps/CianwoodCity/scripts.inc` (novo script de interação do Gladion/Type: Null, objeto novo), `data/maps/CianwoodCity/map.json` (dois `object_events` novos com `LOCALID` a definir), possivelmente `CianwoodGym/scripts.inc` se a checagem/aviso também precisar ser acessível de dentro do ginásio (o plano diz "perto do ginásio", não dentro — verificar coordenadas exatas no refinamento).
- **Mecanismo de batalha:** copiar o padrão de `GoldenrodCity_FlowerShop/scripts.inc:700-830` (captura de `B_FLAG_NO_WHITEOUT`, `GetBattleOutcome`, ramificação de 4 resultados). `TRAINER_GLADION` já existe (`include/constants/opponents.h`) mas seu time atual (`src/data/trainers.party:13952`, nível 14, Grubbin/Sandile/Rockruff) é o **time de Violet**, não serve para a revanche de Cianwood — precisa de treinador novo (`TRAINER_GLADION_2` ou similar, ainda não existente), o que é o "custo de entrada/ID de treinador" citado nas restrições.
- **Item/controle:** `ITEM_HM_FLY`, `VAR_GETFLY` (ver seção D). Não reservar flag nova — os únicos consumidores atuais estão listados na seção D.
- **Assets confirmados existentes** (verificado, não presumido):
  - Gladion: `graphics/object_events/pics/people/special/gladion.png/.4bpp/.gbapal`, wired em `src/data/object_events/object_event_graphics.h:447,501`, `OBJ_EVENT_GFX_GLADION = 333` (`include/constants/event_objects.h:340`), já usado como object event em `VioletCity_PokemonCenter`.
  - Type: Null: `graphics/pokemon/type_null/overworld.4bpp` + `.png` + paletas normal/shiny existem no repositório (formato padrão de sprite overworld de Pokémon seguidor deste engine). **Não confirmei** se `SPECIES_TYPE_NULL` está de fato habilitado na tabela de espécies "seguíveis"/overworld (`include/config/species_enabled.h` lista a espécie, mas não verifiquei se há uma tabela separada de gráficos overworld habilitados por espécie) — isso precisa de teste em emulador antes de prometer que o sprite renderiza como objeto de mapa.
- **Orçamento de objetos:** `OBJECT_EVENTS_COUNT = 16` (`include/constants/global.h:83`) é dado real, não estimativa — ver GLD-02.
- **Chuck (checkout atual, dificuldade única):** `TRAINER_CHUCK_1` (`src/data/trainers.party:10005`), nível 42, batalha dupla (`Double Battle: Yes`), Hitmontop/Annihilape/Mienshao com IVs 30/30/30/12/15/15, sem EVs listados, mugshot Pink. `DIFFICULTY_HARD`/`DIFFICULTY_EASY` são aliases de `DIFFICULTY_NORMAL` (`include/constants/difficulty.h:13-14`, `DIFFICULTY_COUNT = 1`) — **confirma que a dificuldade única já está em vigor neste checkout**, não é uma promessa pendente. Não há `TRAINER_CHUCK_1` alternativo por dificuldade para comparar — só existe esta versão.
- **Gladion (Violet, referência):** `TRAINER_GLADION`, nível 14, Grubbin/Sandile/Rockruff, sem Type: Null no time (consistente com o plano: Type: Null é uma aquisição posterior a Violet). Batalha simples (`Double Battle: No`), `AI: Smart Trainer`. Limitação relevante para a revanche: o time de nível 14 está muito abaixo do nível de Chuck (42) e do estágio de Cianwood — um novo time precisa ser escrito do zero (não é uma escala automática do time de Violet).
- Não reservei nenhum ID/flag apenas por falta de referência direta — os pontos em que não há mecanismo dinâmico equivalente (aviso de treino ocupado, saída coreografada de dois NPCs específicos para Blackthorn) estão marcados como lacuna real, não como "criar flag nova".

## G. Checklist de testes para a implementação

Plano de teste (nada abaixo foi executado nesta auditoria — não há build/emulador rodado):

- [ ] Antes de Chuck, sem acesso antecipado a Fly.
- [ ] Após Chuck, fluxo normal de interação.
- [ ] Fly já recebido (`VAR_GETFLY == 2`): sem reencontro ou duplicata.
- [ ] Impedimento inicial real, se possível: fala curta, sem batalha/progresso.
- [ ] Recusa: entrega e saída definitiva.
- [ ] Vitória: diálogo, cura, entrega e saída.
- [ ] Derrota: sem blackout/penalidade, com diálogo, cura e entrega (replicar exatamente o padrão `B_FLAG_NO_WHITEOUT` de Lillie).
- [ ] Empate/desistência/resultado inesperado (os 4 outcomes de `GetBattleOutcome` já tratados por Lillie — confirmar que Cianwood trata os mesmos 4).
- [ ] Falha excepcional da entrega: NPCs presentes e progresso intacto (nenhum precedente direto — testar deliberadamente, ex. bolsa em estado incomum).
- [ ] Retomada na mesma visita e comportamento documentado após reload — testar especificamente o cenário do GLD-01 (falar com a esposa antes do trigger de frame).
- [ ] Follower ligado/desligado e diferentes direções de interação.
- [ ] Posições corretas ao retornar da batalha.
- [ ] Esposa de Chuck preservada e sem segunda entrega — testar GLD-01 explicitamente.
- [ ] Reentrada e save/load após conclusão: ambos ausentes.
- [ ] Encontro adiado até depois de Blackthorn/Liga: Fly acessível e continuidade coerente (não bloquear Fly, não reapresentar Type: Null pós-evolução para Silvally).
- [ ] No-whiteout, música e controles restaurados, inclusive estado prévio de `B_FLAG_NO_WHITEOUT` (não apenas limpar incondicionalmente).
- [ ] Contagem real de object events ativos em Cianwood City no momento da cena, para validar GLD-02 em jogo (não só por leitura de mapa).
- [ ] Nenhuma nova flag/variável persistente proposta como necessária sem explicitar conflito com o requisito.

## H. Decisões pendentes

1. **Ordem de correção do GLD-01**: o bug de dessincronia entre `ChucksWifeGiveFly` e `VAR_GETFLY` já existe hoje, independente do plano do Gladion. Recomendação: corrigir como parte deste refinamento (é a linha que o novo fluxo vai reutilizar), e não como um bug separado depois — impacto: sem a correção, o novo evento do Gladion herda a mesma janela de duplicação.
2. **Onde exatamente colocar os dois objetos novos**: o plano diz "perto do ginásio" mas não dá coordenadas; o código não tem nenhum `LOCALID` reservado. Recomendação: usar uma posição fora do raio de colisão da entrada do ginásio e da esposa de Chuck (18,47), documentando no refinamento as coordenadas exatas depois de medir o mapa real (não estimado aqui).
3. **Se o orçamento de 16 object events (GLD-02) se provar insuficiente em teste real**: recomendação do prompt já cobre isso — usar o mesmo padrão de `addobject`/`removeobject` condicionado que Suicune/Eusine já usam no mesmo mapa, em vez de objetos sempre carregados. Isso não é uma decisão de design pendente sobre o plano em si, é uma decisão técnica de implementação a confirmar com teste.
