# Berry Master inteiro — plano de implementação em partes

> **Plano rev1 — 30/09/2026.** Ordem de trabalho para implementar tudo o que está em
> [`REI_DA_COLHEITA.md`](REI_DA_COLHEITA.md) (§1–§15): a horta, o Livro de Berries, o
> cruzamento, os níveis, os pedidos, as infestações, a rotina com 10 falas por
> evento, as batalhas de sempre, a sidequest “O Rei da Colheita” e as duas dungeons
> dos corcéis. Substitui o §11 do `REI_DA_COLHEITA.md` e o §11 do
> `BERRY_MASTER_DESIGN.md`.
>
> **Regras de todas as partes**
>
> - Cada parte **compila e se testa no jogo sozinha** (`make -j$(nproc)`, mGBA
>   patchado). Build limpo só prova que compila.
> - Cada parte é um commit (ou uma série curta) que deixa o jogo jogável. Nenhuma
>   parte deixa NPC, canteiro ou fala “pela metade” visível para o jogador.
> - Parte que cria ou passa a usar flag termina com `python3 dev_scripts/flag_audit.py
>   --csv` e a leitura do diff (skill `catalogar-flags`).
> - Texto no jogo em inglês, quebrado com `.claude/skills/nomear-falante/medir_linha.py`.
> - `Route30` e `Route30_House` **não têm `.pory`**: edita-se o `scripts.inc`. Mapas
>   novos podem nascer com `.pory` se o autor preferir; o plano assume `.inc`.
> - Onde o plano e o `REI_DA_COLHEITA.md` discordarem num fato de design, vale o
>   documento de design; onde discordarem num fato do código, vale o código (e o
>   documento é corrigido na mesma parte).

---

## 0. Mapa das partes

| # | Parte | Entrega jogável | Depende de |
|---|---|---|---|
| 1 | Alocação e fundação ✅ 30/09 | constantes, vars, flags, plaquinhas, itens; nada visível | — |
| 2 | A horta física 🧪 30/09 (código feito, falta teste no jogo) | 10 canteiros + canteiro da Laurel na Route 30; plantar, regar, colher | 1 |
| 3 | Livro de Berries 🧪 30/09 (código feito, falta teste no jogo) | colher registra; o Bram só dá berries do Livro; marcos | 1, 2 |
| 4 | Cruzamento completo 🧪 30/09 (código feito, falta teste no jogo) | 58 receitas em 6 bits; Lansat/Starf só pós-Liga | 2, 3 |
| 5 | Estado diário 🧪 30/09 (código feito, falta teste no jogo) | `FLAG_DAILY_GARDEN_NEW_DAY` + `VAR_GARDEN_TODAY` | 1 |
| 6 | Níveis da horta 🧪 30/09 (código feito, falta teste no jogo) | reformas 1–4, canteiro B, irrigação, semente encomendada | 3, 5 |
| 7 | Pedidos do dia | comum e descoberta, dica da Laurel | 3, 4, 5, 6 |
| 8 | Elenco e rotina | Bram, Laurel, Tilly, Sunflora por horário e dia da semana | 2, 5 |
| 9 | Banco de falas | rodízio de 10, corações, reações de contexto | 5, 8 |
| 10 | Infestações | pragas e ervas só na horta; 8 famílias só daqui | 2, 6 |
| 11 | Batalhas de sempre (Tilly, Bugsy, Klara) | `garden_fight`; assalto da Klara | 5, 8, 10 |
| 12 | Sidequest — Prólogo ao Ato 4 | estados 0 → 8 | 3, 6, 8, 10 |
| 13 | Sidequest — Ato 5 e 5b | estados 8 → 10/11, Peony e Peonia hóspedes, cenouras | 12 |
| 14 | Caminho branco — Greenfield | 2 mapas novos, Glastrier, estado 10 → 12 | 13 |
| 15 | Caminho escuro — Torre de Bronze | 2 mapas novos, Spectrier, estado 11 → 13 | 13 |
| 16 | Ato 7, Epílogo e pós-história | estados 12/13 → 15, nível 5, Avery, Peony/Peonia, Mustard | 11, 14 ou 15 |
| 17 | Fechamento | auditorias, Nexus, renders, jogada completa | todas |

As partes 14 e 15 são independentes entre si (dá para fazer uma, testar a 16 com ela,
e fazer a outra depois). As partes 9, 10 e 11 podem trocar de ordem entre si.

### Revisão das partes 1–3 (30/09/2026)

Revisão pedida pelo autor antes da Parte 4. O que ela achou e o que foi feito:

| # | Achado | Gravidade | Feito |
|---|---|---|---|
| 1 | Plaquinha em 2 bytes com base 255: do índice 250 em diante o byte baixo vira `FA`..`FE` (`\l`, `\p`, código, placeholder, `\n`). A fala desenha certo, mas `StripLineBreaks` (`line_break.c`) e o braille varrem byte a byte e leriam `FE` como quebra de linha. Faltavam 7 falantes para acontecer | alta, latente | Base **250** (`SPEAKER_ARG_BASE`); abaixo de 250 os bytes são os mesmos, o charmap não mudou um byte. As ferramentas da skill leem a base do cabeçalho em vez de ter `255` escrito à mão |
| 2 | No dia do tutorial o Bram dizia “One more thing… o Livro” e logo “You came back! And you looked at the trees” na mesma conversa (defeito antigo, a fala do Livro deixou à vista); a caixa ainda fechava e reabria entre as duas | média | Fala própria para a visita do tutorial (“And since you're here, take two more.”, `FLAG_TEMP_1`), e a caixa fica aberta |
| 3 | `REI_DA_COLHEITA.md` ainda dizia que a Oran natural sai, que o registro é no script, que o C fica em `berry.c`, e contava 15 objetos (são 16 com o Caterpie) | média (regra do plano: o doc é corrigido na mesma parte) | Corrigido nos 5 pontos, marcado *código (parte N)* |
| 4 | Skill `alocar-flag` mandava alocar em `0x1047` (velho desde antes da horta); `vars.h` sem marcador de próxima var | média | A skill manda ler o marcador `PROXIMA FLAG NOVA`; `vars.h` ganhou `PROXIMA VAR NOVA: 0x412E` |
| 5 | Comentários de `flags.h`/`vars.h` citavam `GardenRollDay` e `GardenHearts_Talk`, que ainda não existem | baixa | Marcados “plan part 5/9, not written yet” |
| 6 | Nenhum teste automático | — | `test/berry_garden.c`: 12 testes (faixa dos canteiros, canteiros e da Laurel não renascem, Oran do WorldHub renasce, Livro só aceita berry e vai de Cheri a Maranga, iniciais idempotentes, sorteios sem Lansat/Starf/Enigma e alcançando todo registrado, rara sem Enigma, marcos em ordem e sem o 66, colheita põe na bolsa e no Livro). **Compilam, mas não rodam** (item 7) |
| 7 | A infraestrutura de testes do repo **não roda hoje**, sem relação com a horta: (a) `test/vs_seeker.c` cita treinadores de Hoenn que não existem e `test/battle/*.party` quebra com `-Werror=override-init`; (b) o ROM de teste tem 39 MB e o `mgba-rom-test` de fábrica só lê 32 MB (opcode ilegal no primeiro frame). O mGBA patchado lê, mas não tem o executor `rom-test` | alta para o repo | **Não feito** (fora do escopo): recomendação de portar o `rom-test` para `tools/mgba-master` e consertar os dois arquivos de teste. Comando que chegou a compilar e linkar só a horta: `make check TEST_SHARDS=1 CFLAGS=-Wno-error=override-init TEST_SRCS_IN="test/test_runner.c test/test_runner_args.c test/test_runner_battle.c test/berry.c test/berry_garden.c"` |
| 8 | Site público de documentação (`tools/soulgold_docs`) não foi regenerado com as cenouras | decisão do autor | **Não feito de propósito:** as cenouras são spoiler do Crown Tundra e ainda não têm fonte. Regenerar quando a Parte 13 der a fonte |

Medido com a skill `limites-do-engine` (`dev_scripts/limites_janela_objetos.py --mapa
Route30`): pior janela de spawn = **14** objetos em (21,35), contando os escondidos por
flag; nenhum mapa do jogo passa de 15. Save: `SaveBlock1` com 428 bytes livres — a
Parte 4 não gasta nada (os 6 bits de mutação usam o `padding:2` que já existe).
Para a Parte 8 existem **duas** saídas para o 16º objeto: tirar o Caterpie de (36,34),
ou subir `OBJECT_EVENTS_COUNT` (cabe até 27 sem aumentar o save, mas exige o conserto
do `waitmovement` e de `MAX_SPRITES`, ver `.claude/limites-do-engine.md`). Decisão do
autor na Parte 8.

Conferido e sem problema: limite de 64 templates por mapa (Route 30 com 33, sobra para o
elenco); `SetBerryTreeJustPicked` sem teto de `local_id`; Berry Pouch é item-chave sem uso
(prêmio cosmético seguro); os 4 `case` do `text.c` e o `GetExtCtrlCodeLength` pulam os 2
bytes; nenhum script cita `local_id` da Route 30 acima de 6; `FLAG_TEMP_5/6` não aparecem
em script comum; build limpo, `map_graph` ok, `checar_falantes.py` “241, tudo em ordem”,
`medir_linha.py` sem estouro nos dois mapas.

### Como testar: menu de debug “Berry Master…” (30/09/2026)

No jogo de desenvolvimento (`make -j$(nproc)`; o release não tem debug): **L + START** no
campo → **Berry Master…**. Tudo nele muda o save do jeito que o jogo mudaria e diz o que
fez. Código: `sDebugMenu_Actions_BerryMaster*` em `src/debug.c`, scripts
`Debug_EventScript_Berry*` em `data/scripts/debug.inc`, regras `BerryDebug_*` em
`src/berry_garden.c`.

| Item | Faz |
|---|---|
| Status | nível, obra, canteiros plantados, Livro, marco pago e devido, hora, bits do dia, estado da sidequest, presente do Bram |
| Go: the garden / Go: Bram's house | teleporte para (27,45) na Route 30 / porta da casa |
| Clock… | +1 h, +6 h, +24 h, próxima 7:00 (que pode ser a de **hoje**: para virar o dia, use +24 h) — **move o relógio de verdade** (o deslocamento do RTC, como o relógio de parede), só para a frente, e recarrega o mapa: as árvores crescem as horas puladas e a virada de dia limpa as flags diárias pelo caminho normal |
| Clock… → New day, keep clock | dia novo **da horta** sem mexer no relógio: presente do Bram e rara da Laurel de volta, obra paga concluída |
| Book of Berries… | Livro com 8, 11, 12, 22, 32, 60, 66 (sem Enigma) ou 67; “Milestones unpaid” zera os marcos pagos |
| Garden level… | nível 1–4 (descarta obra em andamento) e recarrega |
| Ripen / Grow 1 stage / Empty | os 10 canteiros: tudo maduro, um estágio, ou terra vazia (vazio inclui o da Laurel) |
| Act 1 done: toggle | `VAR_HARVEST_KING` 0 ↔ 4 (libera as ofertas dos níveis 3 e 4) |
| League clear: toggle | `FLAG_SYS_GAME_CLEAR` (rara da Laurel; Lansat e Starf cruzam) |
| Give ¥10,000 / Money: set to ¥0 / 5 of each Mulch | dinheiro para as reformas (ou nenhum, para testar a recusa); os 8 adubos |
| Reset Berry Master | save que nunca viu o Bram: tutorial de novo, Livro, horta, níveis, marcos e história zerados |

Berries para plantar: **PC/Bag… → Fill Pocket Berries** (já existia).

**Roteiros por parte**
- **Parte 2:** Reset Berry Master → Go: Bram's house → tutorial → Go: the garden → plantar
  no A; B é grama; placa em (23,38). Garden level… → 2 → o B vira terra com 4 canteiros.
- **Parte 3:** Book… → 11, falar com o Bram (nada); Book… → 12, falar → 5 Growth Mulch
  (e, junto, a oferta da reforma do nível 2, que é da Parte 6).
  Colher de uma árvore de rota fora das 8 → Status mostra o Livro +1.
- **Parte 4:** a mutação é sorteada **no plantio** (25%, contra o vizinho já plantado) e
  só aparece **na colheita**. Ciclo: Fill Pocket Berries → plantar Chesto em A1 →
  plantar Cheri em A2 → Ripen → falar com A2: “…and 1 Lum Berry!” (se não veio, Empty e
  repetir; ~4 tentativas em média). Micle ao lado de Custap: sem League clear nunca dá
  Lansat; com League clear, dá.
- **Parte 5:** Status (bits do dia); Clock… → +24 h → bits zerados.
- **Parte 6:** Book 12, ¥10,000, falar com o Bram → pagar → Clock… → +24 hours →
  “Four more beds!” e o B aberto; o presente vira 3 / semente à escolha. Book 22 + Act 1
  → oferta do canal → pagar → dia seguinte → plantar → +24 h → ao entrar, já regado.

**Pendências do autor** (nenhuma bloqueia as partes 1–12; ver §18):
sprites de Peony, Peonia, Klara, Avery, Mustard e Molly adulta; prêmios grandes (Peony,
Mustard); falas novas dos moradores de Greenfield no estado 12.

---

## Parte 1 — Alocação e fundação

**Objetivo.** Reservar tudo que as outras partes usam, num lugar só, antes de escrever
qualquer script. Nada muda no jogo.

**Skills:** `alocar-flag`, `nomear-falante`, `catalogar-flags`.

**Fatos medidos no repo (30/09/2026)**

| Fato | Onde |
|---|---|
| Última flag custom é `0x1052`; `CUSTOM_FLAGS_END` aponta para ela; próxima livre `0x1053` | `include/constants/flags.h:1943-1946` |
| Última var custom é `VAR_SHINY_RATE` `0x4126`; livres a partir de `0x4127` até `VARS_END` `0x42FF` | `include/constants/vars.h:390-404` |
| `FLAG_UNUSED_0x952` do design é o **bit 0x32 do bloco diário** (`DAILY_FLAGS_START + 0x32`); fora do bloco, `0x952` é `FLAG_TM_SLEEP_TALK` | `flags.h:1662`, `:1954` |
| Plaquinhas são `SP_NAME_*` em `include/constants/speaker_names.h` (o design escreve `NAME_*`) | já existem `SP_NAME_PRYCE`, `SP_NAME_KURT`, `SP_NAME_BUGSY`, `SP_NAME_MORTY`, `SP_NAME_EUSINE` |
| `ITEM_REINS_OF_UNITY` existe (704); Iceroot/Shaderoot Carrot **não** | `include/constants/items.h:856` |
| `OW_BERRY_MUTATIONS`, `_WEEDS`, `_PESTS` = FALSE | `include/config/overworld.h:36-42` |

**Passos**

1. **Flags** (`flags.h`, bloco `CUSTOM_FLAGS`): `FLAG_BERRY_LEDGER_START 0x1053` ..
   `FLAG_BERRY_LEDGER_END 0x1095` (67, em ordem de item), `CUSTOM_FLAGS_END` passa a
   `FLAG_BERRY_LEDGER_END`. Comentário apontando para `REI_DA_COLHEITA.md` §3.2.
2. **Flag diária**: `FLAG_DAILY_GARDEN_NEW_DAY` no primeiro bit livre do bloco diário
   (o design sugere `+ 0x32`; conferir com `alocar-flag`).
3. **Vars** novas, contíguas a partir de `0x4127` (em vez de reciclar
   `VAR_GIFT_UNUSED_5..7`, que o design deixava “a conferir”):

   | Var | Faixa | Uso |
   |---|---|---|
   | `VAR_GARDEN_TODAY` | bits | estado do dia (§14.6) |
   | `VAR_GARDEN_HEARTS` | 4×4 bits | corações de Bram, Laurel, Tilly, Peony |
   | `VAR_GARDEN_RIVALS` | contador | vitórias contra a Klara |
   | `VAR_BERRY_GARDEN_LEVEL` | 1..5 | nível da horta |
   | `VAR_BERRY_ORDER` | índice + qtd | pedido do dia |
   | `VAR_HARVEST_KING` | 0..15 | estado da sidequest |

   Recomendação a confirmar na hora: se o autor preferir reciclar os `VAR_GIFT_UNUSED`,
   provar antes com `grep` que nada escreve neles.
4. **IDs de árvore**: 11 apelidos em `include/constants/berry.h` sobre IDs só de Hoenn
   sem berry natural, faixa contígua a partir de 5 (`BERRY_TREE_GARDEN_A1..A6`,
   `_B1..B4`, `BERRY_TREE_KINGS_PLOT`), mais `BERRY_TREE_GARDEN_FIRST/LAST`. Conferir
   que nenhum está em `sNaturalBerriesByTreeId` nem em `EventScript_ResetAllBerries`
   (design rev1 §2.2).
5. **Plaquinhas** (skill `nomear-falante`, os três arquivos na mesma ordem):
   `SP_NAME_BERRY_MASTER` (“Berry Master”), `SP_NAME_LAUREL`, `SP_NAME_TILLY`,
   `SP_NAME_CALYREX`, `SP_NAME_PEONY`, `SP_NAME_PEONIA`, `SP_NAME_KLARA`,
   `SP_NAME_AVERY`, `SP_NAME_MUSTARD`, `SP_NAME_MOLLY`, `SP_NAME_TOMO`. Plaquinha “???”
   para o Calyrex antes de se apresentar: conferir se a skill já tem o padrão.
6. **Itens-chave**: `ITEM_ICEROOT_CARROT`, `ITEM_SHADEROOT_CARROT` (nome, descrição,
   ícone emprestado de um item parecido até ter arte). Registrar no
   `SOULGOLD_ITEMS_AUDIT` pelo `dev_scripts/item_audit.py`.
7. `python3 dev_scripts/flag_audit.py --csv` e ler o diff: as 67 flags aparecem como
   “não usadas” até a Parte 3; isso é esperado e fica anotado no commit.

**Pronto quando:** build limpo; `checar_falantes.py` ok; o diff do CSV só mostra o
bloco novo.

### Parte 1 — feita (30/09/2026)

**O que entrou**

| O quê | Onde | Valor |
|---|---|---|
| Livro de Berries | `include/constants/flags.h` | `FLAG_BERRY_LEDGER_START 0x1053` (Cheri, item 514) .. `FLAG_BERRY_LEDGER_END 0x1095` (Maranga, 580); `CUSTOM_FLAGS_END` aponta para o END; próxima flag nova `0x1096` |
| Flag diária | `flags.h`, bloco DAILY | `FLAG_DAILY_GARDEN_NEW_DAY` = `DAILY_FLAGS_START + 0x32` (`0x153A`), no lugar do `FLAG_UNUSED_0x952` do bloco diário |
| Vars | `include/constants/vars.h` | `VAR_GARDEN_TODAY 0x4127`, `VAR_GARDEN_HEARTS 0x4128`, `VAR_GARDEN_RIVALS 0x4129`, `VAR_BERRY_GARDEN_LEVEL 0x412A`, `VAR_BERRY_ORDER 0x412B`, `VAR_HARVEST_KING 0x412C`, `VAR_BERRY_LEDGER_MILESTONE 0x412D`; próxima var livre `0x412E` |
| IDs de árvore | `include/constants/berry.h` | `BERRY_TREE_GARDEN_A1..A6` = 5..10, `_B1..B4` = 11..14, `BERRY_TREE_KINGS_PLOT` = 15; `GARDEN_FIRST` = A1, `GARDEN_LAST` = **B4** |
| Plaquinhas | os 3 arquivos, índices `00 55`..`00 60` (2 bytes) | `NAME_BERRY_MASTER`, `_LAUREL`, `_TILLY`, `_CALYREX`, `_PEONY`, `_PEONIA`, `_KLARA`, `_AVERY`, `_MUSTARD`, `_MOLLY`, `_TOMO`, **`_UNKNOWN` (“???”)** |
| Itens-chave | `include/constants/items.h`, `src/data/items.h` | `ITEM_ICEROOT_CARROT 935`, `ITEM_SHADEROOT_CARROT 936`; ícone e paleta do Big Root nas duas (provisório) |
| Catálogos | `docs/` | `SOULGOLD_FLAGS_AUDIT.csv`, `SOULGOLD_ITEMS_AUDIT.csv/.md` regenerados |

**Onde a Parte 1 divergiu do plano, e por quê**

1. **`VAR_BERRY_LEDGER_MILESTONE` já alocada** (pendência 7 do §18, na recomendação
   “var própria”). Custa uma var e deixa a Parte 3 sem decisão pendente. Guarda o
   último marco **pago** (0, 12, 20 … 66), não um índice.
2. **Pendência 6 fechada:** vars novas em `0x4127..`, nenhum `VAR_GIFT_UNUSED` reciclado.
3. **O canteiro da Laurel fica fora de `GARDEN_FIRST..LAST`.** A faixa cobre só os 10
   canteiros (5..14); `KINGS_PLOT` é o 15, logo depois. Motivo: praga, erva e a rega
   automática do nível 3 seguem a horta, e o canteiro da Laurel segue a história (uma
   praga em cima da Enigma no Ato 4 quebraria a cena). Se o autor quiser o contrário,
   é trocar `GARDEN_LAST` para `BERRY_TREE_KINGS_PLOT`, uma linha.
4. **Plaquinha “???” genérica** (`SP_NAME_UNKNOWN`), e não uma “Calyrex ???”: a skill
   não tinha o padrão, e qualquer personagem que ainda não se apresentou pode usar.
   Na troca de nome no meio da cena, `{SPEAKER NAME_UNKNOWN}` → `{SPEAKER NAME_CALYREX}`.
5. **Descrição das cenouras** (texto provisório, o autor pode trocar):
   “A carrot grown from / a seed of the Crown / Tundra. Icy cold.” e “… Pitch black.”
   Medidas contra as descrições que já existem (a maior tem ~108 px; a nossa, 103 px).

**O que as próximas partes precisam saber**

- **O `flag_audit` não enxerga as 65 flags do meio do Livro.** Elas não têm nome
  próprio (o C calcula `START + (item − FIRST_BERRY_INDEX)`), então o catálogo só lista
  `FLAG_BERRY_LEDGER_START` e `_END`, hoje como `SO_EM_DOC`. O “pronto quando” da
  Parte 3 (“as 67 como lidas e escritas pelo C”) **não vai aparecer no CSV**: a
  prova lá é o teste no jogo e um `STATIC_ASSERT(FLAG_BERRY_LEDGER_END -
  FLAG_BERRY_LEDGER_START + 1 == ITEM_MARANGA_BERRY - FIRST_BERRY_INDEX + 1)` em
  `src/berry.c`, que a Parte 3 deve pôr junto do `BerryLedger_Register`.
- **`FLAG_DAILY_GARDEN_NEW_DAY` já sai `EM_USO` no catálogo** (0 leituras, 0 escritas)
  porque o `ClearDailyFlags` limpa o bloco inteiro. Não é sinal de que alguém a usa.
- **As cenouras estão `SEM FONTE`** no catálogo de itens até a Parte 13.
- **Os dois catálogos estavam atrasados** antes desta parte. O de flags tinha 10
  linhas com contagem de docs velha (`FLAG_SYS_NO_CATCHING` passou de
  `SO_MAPAS_FORA_DA_ROM` para `SO_ESCRITA` só por isso). O de itens tinha sido gerado
  por uma versão antiga do `item_audit.py` (sem as colunas `display_name`,
  `out_camp_detail`, `trainer_held_only`), então o diff dele é o arquivo inteiro; foi
  regravado com CRLF, como estava. Por isso os catálogos foram para um commit separado.
- **Plaquinhas em 2 bytes.** No mesmo dia o índice de `{SPEAKER ...}` passou a 2 bytes
  e o jogo inteiro foi convertido para plaquinha (commit dos falantes, logo antes
  deste). As 12 da horta ficaram em `00 55`..`00 60`; `checar_falantes.py` dá
  “241 falantes, tudo em ordem”. Falante novo agora entra por
  `.claude/skills/nomear-falante/adicionar_falante.py`, não à mão.
- Os IDs 5..15 só aparecem em `Route103/104/123`, todos `fora da ROM`
  (`map_graph.py info`), e nenhum está em `sNaturalBerriesByTreeId` nem em
  `EventScript_ResetAllBerries`. Um save antigo não tem nada gravado neles.

**Teste no jogo:** nada muda no jogo nesta parte. O build limpo prova os asserts do
save (`global.h`, `save.c`). A primeira coisa visível é a Parte 2.

---

## Parte 2 — A horta física

**Objetivo.** Os canteiros existem e funcionam como terra de berry normal. Sem
cruzamento, sem praga, sem Livro ainda.

**Skills:** `encenar-cutscene` (medir colisão), `visibilidade-e-gatilhos`,
`mapa-de-ligacoes` (só conferir que nada muda de ligação), `prototipo-de-mapa`
(render antes/depois).

**Passos**

1. **Metatiles** em `data/layouts/Route30/map.bin`: canteiro A = (28..30, 43..44),
   hoje 189–191/205–207 → **46 com colisão**; canteiro B = (30..31, 41..42) → 46 com
   colisão; o canteiro da Laurel já é a árvore Oran de (23,38). Medir tudo com
   `dump_mapa.py Route30` antes.
2. **Objetos** em `data/maps/Route30/map.json`: 10 objetos de árvore
   (`BERRY_TREE_GARDEN_*`) e a árvore de (23,38) trocada para `BERRY_TREE_KINGS_PLOT`.
   **Tirar o Weedle decorativo de (19,42)** (decisão 7 do autor).
3. **Oran natural sai**: `BERRY_TREE_ORAN_2` sai de `sNaturalBerriesByTreeId` e de
   `EventScript_ResetAllBerries`, para o canteiro da Laurel não renascer Oran.
4. **Canteiro B trancado**: no `ON_LOAD` da Route 30, com `VAR_BERRY_GARDEN_LEVEL < 2`,
   `setmetatile` das 4 células de volta para grama sem colisão; no `ON_TRANSITION`,
   `setflag` da `FLAG_TEMP` que esconde os 4 objetos do B. As duas coisas: árvore vazia
   é invisível **mas interativa**.
5. **Canteiro da Laurel trancado** até o Ato 3: objeto escondido por `FLAG_TEMP` no
   `ON_TRANSITION` e `bg_event` no mesmo tile: “The soil here is hard and cold.
   Nothing's grown in it for a long time.”
6. Por enquanto `VAR_BERRY_GARDEN_LEVEL` = 1 quando o tutorial do Bram (que já existe)
   termina; só o A abre.

**Teste no jogo:** plantar nas 6 células do A, regar com a Squirtbottle, esperar,
colher; o B e o canteiro da Laurel não perguntam “plantar?”; o `bg_event` responde;
contar objetos na pior posição (jogador em (27,40)) com o render.

**Pronto quando:** render da Route 30 (dia e noite) mostra a horta; nenhum canteiro
invisível; nenhuma árvore de rota perdeu a berry.

### Parte 2 — feita no código (30/09/2026), falta o teste no jogo

**O que entrou**

| O quê | Onde |
|---|---|
| 10 células de solo: metatile 46, colisão 1, **elevação 3** (a mesma da grama em volta) — valor `0x382E` (ver “Bug 1” abaixo) | `data/layouts/Route30/map.bin`, A (28..30, 43..44) e B (30..31, 41..42) |
| 10 objetos `BERRY_TREE_GARDEN_A1..A6` / `_B1..B4`, local ids 24..33 | `data/maps/Route30/map.json` (no fim, para não mexer nos ids antigos) |
| Árvore de (23,38) → `BERRY_TREE_KINGS_PLOT`, flag `FLAG_TEMP_HIDE_KINGS_PLOT` | idem |
| `bg_event` em (23,38) → `Route30_EventScript_ColdSoil` (“The soil here is hard and cold. / Nothing's grown in it for a long time.”) | idem, `scripts.inc` |
| Weedle decorativo de (19,42) removido; ids 12..24 desceram um (nenhum script os citava) | idem |
| `ON_TRANSITION` → `Route30_EventScript_GardenVisibility`: esconde o B com nível < 2 e sempre o canteiro da Laurel | `data/maps/Route30/scripts.inc` |
| `ON_LOAD` novo → `LockGardenBSoil`: B volta a grama (0, 0, 1, 0) com nível < 2 | idem |
| `FLAG_TEMP_HIDE_GARDEN_B` = `FLAG_TEMP_5`, `FLAG_TEMP_HIDE_KINGS_PLOT` = `FLAG_TEMP_6` (apelidos) | `include/constants/flags.h` |
| Fim do tutorial do Bram: `setvar VAR_BERRY_GARDEN_LEVEL, 1` | `data/maps/Route30_House/scripts.inc` |

**Onde divergiu do plano, e por quê**

1. **O passo 3 não foi feito, e não deve ser.** `BERRY_TREE_ORAN_2` **não** é só da
   Route 30: o `WorldHub` (alcançável, pela casa do jogador em New Bark) tem uma horta
   de árvores naturais e usa o mesmo ID em (4,31). As duas árvores dividiam o estado
   até agora. Trocar o objeto da Route 30 para `KINGS_PLOT` já basta: a Route 30 deixa
   de ter Oran natural, e o WorldHub continua com a dele.
2. **Save antigo.** Quem já tinha feito o tutorial antes desta parte fica com
   `VAR_BERRY_GARDEN_LEVEL` = 0. O `ON_TRANSITION` da Route 30 corrige: com
   `FLAG_GOT_BERRY_ROUTE_30_HOUSE` e nível 0, grava 1. A Parte 6 não precisa pensar nisso.
3. **Canteiro A não tem trava.** Ele fica aberto desde o começo, até antes do tutorial,
   porque o nível só importa para o B. Se o autor quiser o A fechado até o tutorial, é
   o mesmo par de travas do B (flag temp + `setmetatile`).
4. **Elevação 3 no solo novo**, e não 0 como no solo de (23,38) e na maioria das
   árvores de Johto. Com 3, o `setmetatile` que devolve a grama no B (ele preserva a
   elevação) deixa a mesma elevação do resto do chão.

**Orçamento de objetos (medido com a janela real do spawn, `TrySpawnObjectEvents`)**

Hoje, na pior posição ((27,40) ou (31,40)), com o nível 2: 10 canteiros + o
**Caterpie decorativo de (36,34)** = 11, mais jogador e follower = **13**. O design
(§2.3) não contava esse Caterpie. Quando a Parte 8 puser Laurel e Bugsy (e o Ato 3
mostrar o canteiro da Laurel), a conta vai a **16**, acima do limite. **A Parte 8
tem que tirar o Caterpie de (36,34)** (ou movê-lo para fora da janela), como foi
feito com o Weedle.

**Renders** (nível 1 de dia, nível 1 à noite, nível 2): o B vira grama no nível 1, o
A aparece, e (23,38) mostra só a terra. Os três ficaram no scratchpad da sessão;
não são versionados.

**Bug 1 do teste no jogo (02/10/2026), corrigido:** as 10 covas apareciam como blocos
**rosa** (um tile do secundário de Cherrygrove) e **sem colisão**. Causa: o `map.bin` foi
gravado com o layout do pokeemerald original (ID do metatile em 10 bits, colisão no bit
10), mas **neste repo o ID tem 11 bits** (`MAPGRID_METATILE_ID_MASK 0x07FF`,
`include/global.fieldmap.h`) e a colisão é o **bit 11**. “46 + colisão” virou o metatile
**1070**. Gravado de novo como `0x382E` (46, colisão 1, elevação 3), igual em ID e colisão
à cova da Laurel (`0x082E`). A armadilha já estava escrita no `SKILL.md` da
`encenar-cutscene`, que esta parte listava e não foi lida; e o `check_objects` do
`mapa_kit` **não** marcava as covas como bloqueio, sintoma que foi explicado em vez de
investigado. Regra: decodificar `map.bin` só com as máscaras de `global.fieldmap.h`, e
conferir o valor contra uma célula que já funciona.

**Bug 2 do teste no jogo (02/10/2026), corrigido — terra molhada:** regar não mudava
nada na tela. O Gen 3 não tem tile de terra molhada (só o HGSS escurece a terra), e o
primário de Johto e o secundário de Cherrygrove estão com 640/640 e 384/384 tiles. Feito
sem tile novo (técnica 1 da skill `montar-tileset`): a paleta **7** do secundário
`CherrygroveCity` não é usada por nenhum metatile (nem dos primários `Johto_General` e
`Johto_NorthWest` que se juntam a ele), então ganhou a terra escurecida nos índices que o
tile 12 usa (9, 11, 12, 13, 15); o metatile novo **0x4C8**
(`METATILE_CherrygroveCity_SoilWet`, anexado no fim) é o 46 com a camada da terra na
paleta 7. `BerryTree_UpdateSoilTile` (`src/berry.c`), chamada a cada quadro pela árvore
(`MovementType_BerryTreeGrowth_Normal`), troca seco ↔ molhado conforme o bit de rega do
estágio atual — molhada depois da Squirtbottle ou do canal, seca no estágio seguinte, na
colheita e em cova vazia — e só mexe num tile que seja exatamente o seco ou o molhado da
tabela `sWetSoil`, mantendo a colisão. Outro tileset ganha terra molhada com uma linha na
tabela e um metatile seu. `check_tileset.py secondary/cherrygrove_city` limpo.

**Teste no jogo (falta, o autor faz):**
- Save novo: tutorial do Bram, sair, plantar nas 6 células do A, regar, esperar, colher.
- As 4 células do B: grama, dá para andar em cima, ninguém pergunta “plantar?”.
- (23,38): a placa responde, não pergunta “plantar?”.
- Save antigo com o tutorial já feito: entrar na Route 30 e conferir que o A funciona.
- Árvore Oran do WorldHub continua dando Oran.

---

## Parte 3 — Livro de Berries

**Objetivo.** A colheita registra a berry, e o presente diário do Bram passa a sair
só do Livro. Base de tudo o que vem depois.

**Skills:** `alocar-flag` (já feito), `catalogar-flags`, `entregar-pokemon-ou-ovo`
(não se aplica; mas a ordem `checkitemspace` antes de dar vale igual).

**Passos**

1. **C** (`src/berry.c`): `BerryLedger_Register`, `BerryLedger_Count`,
   `BerryLedger_RandomRegistered` (sem Lansat, Starf, Enigma),
   `BerryLedger_BuildSeedMenu` (fica pronto para a Parte 6),
   `BerryLedger_NextDiscovery` (depende da tabela da Parte 4: nesta parte devolve
   “nenhuma” com a tabela de 13 do jogo, e passa a valer sozinho quando a tabela crescer).
   Registrar os specials em `data/specials.inc`.
2. **Gancho na colheita**: `BerryTree_EventScript_PickBerry` e a versão com mutação
   (`data/scripts/berry_tree.inc`) chamam `BerryLedger_Register` logo depois de dar as
   berries. Vale para horta **e** rota. Comprar não registra.
3. **Tutorial**: ao fim do tutorial do Bram (`Route30_House/scripts.inc`), registrar as
   8 iniciais (Cheri, Chesto, Pecha, Rawst, Aspear, Leppa, Oran, Persim).
4. **Presente diário do Bram** (já existe, `FLAG_DAILY_BERRY_MASTER_RECEIVED_BERRY`):
   troca o sorteio de pool pelo `BerryLedger_RandomRegistered`, 2 berries (3 a partir do
   nível 2, na Parte 6).
5. **Rara diária da Laurel** (já existe, pós-Liga): sorteia **do Livro**, raras, nunca
   a Enigma.
6. **Marcos** (12 / 20 / 30 / 40 / 50 / 60 / 66): o Bram confere
   `BerryLedger_Count` na conversa e entrega o prêmio do §3.4 com `checkitemspace`
   antes. Estado “já entreguei o marco N” sem flag nova: guardar o último marco pago num
   nibble de `VAR_BERRY_GARDEN_LEVEL` **ou** numa var própria — decidir na parte (o
   design não diz; recomendação: var própria `VAR_BERRY_LEDGER_MILESTONE`, mais simples
   de ler em script).
7. Fala do Bram quando não tem a berry: “I don't hand out what I don't grow, sprout…”.
8. O marco 66 **não** toca a cena do nome ainda: deixa um gancho para a Parte 16
   (`LaurelSaysName`, §14.1 item 4). *Para a Parte 16:* o `BerryLedger_Count`
   **conta a Enigma**, então “66 no Livro” não é “todas menos a Enigma” (quem tem a
   Enigma e falta uma outra também chega a 66). A condição tem que ser “todas as 66
   que não são a Enigma”.

**Teste no jogo:** colher uma Sitrus de rota → no dia seguinte o Bram pode dá-la;
nunca dá uma que não foi colhida; debug com 12 flags ligadas → prêmio do marco 12 uma
vez só; bolsa cheia → o Bram avisa e não perde o prêmio.

**Pronto quando:** `flag_audit` mostra as 67 como lidas e escritas pelo C.

### Parte 3 — feita no código (30/09/2026), falta o teste no jogo

**O que entrou**

| O quê | Onde |
|---|---|
| Arquivo novo das regras da horta; o Livro é o primeiro bloco | `src/berry_garden.c`, `include/berry_garden.h` |
| `STATIC_ASSERT` de que o bloco de flags tem exatamente as 67 berries | `berry_garden.c` |
| Specials `BerryLedger_Register` (`VAR_0x8004` = item), `_RegisterStarters`, `_Count`, `_RandomRegistered`, `_RandomRegisteredRare`, `_PendingMilestone` | `data/specials.inc` |
| Registro na colheita: toda berry que **entra na bolsa** vai para o Livro, a normal e a de mutação, horta e rota | `ObjectEventInteractionPickBerryTree`, `src/berry.c` |
| Tutorial registra as 8 do Bram e explica o Livro (“I don't hand out what I don't grow, sprout…”) | `Route30_House/scripts.inc` |
| Presente diário: 2 berries sorteadas do Livro, nunca Lansat, Starf nem Enigma | idem |
| Marcos 12/20/30/40/50/60 com o prêmio do §3.4, `checkitemspace` antes; a var só anda depois que o prêmio entrou | idem, `VAR_BERRY_LEDGER_MILESTONE` |
| Rara diária da Laurel (pós-Liga): sorteada das raras **do Livro**, nunca a Enigma; sem nenhuma rara no Livro, fala nova e não gasta o dia | idem |

**Onde divergiu do plano, e por quê**

1. **O registro está no C, não no script** (passo 2). Os dois caminhos de colheita
   (normal e com mutação) passam por `ObjectEventInteractionPickBerryTree`, e só ali
   se sabe se a berry **entrou** na bolsa. Registrar no script exigiria repetir o
   gancho em dois lugares e poderia registrar uma colheita que não coube. O special
   `BerryLedger_Register` continua existindo para quem precisar pelo script.
2. **Arquivo novo `src/berry_garden.c`** em vez de `src/berry.c`: o `berry.c` é do
   motor (upstream), e a horta ainda vai ganhar estado diário, falas, corações e
   pragas. O `berry.c` só ganhou o gancho de 4 linhas e o `#include`.
3. **`BerryLedger_BuildSeedMenu` e `BerryLedger_NextDiscovery` não foram escritos
   agora.** O primeiro só tem uso na Parte 6 (semente encomendada, `dynmultichoice`) e
   o segundo depende da tabela de 58 receitas da Parte 4 (a de hoje é `static` em
   `berry.c`). Escritos agora, seriam código sem teste possível. Entram nas Partes 6 e 7.
   *(`BuildSeedMenu`: feito na Parte 6. `NextDiscovery`: Parte 7.)*
4. **Save antigo:** `BerryLedger_RegisterStarters` roda em **toda** conversa com o
   Bram (não custa nada, e é idempotente). Quem fez o tutorial antes desta parte ganha
   as 8 iniciais no Livro na próxima conversa, e o sorteio nunca fica vazio.
5. **O 3º berry do nível 2 não entrou** (passo 4): o texto de hoje diz “take two”, e o
   nível 2 só existe na Parte 6, que muda o texto junto. *(Feito na Parte 6.)*
6. **Marcos:** um texto só (“{STR_VAR_1} Berries! …”) para os seis; o `giveitem` já
   diz o que foi. Vários marcos pendentes (save antigo com Livro grande) saem todos na
   mesma conversa, em ordem. O 66 fica fora da lista: é da Parte 16.
7. **Falas sem plaquinha**, como as do Bram e da Laurel que já existiam: a casa é uma
   conversa de uma pessoa só. A Parte 9 decide se todo o banco de falas ganha plaquinha.

**Catálogo:** `FLAG_BERRY_LEDGER_START` agora aparece `EM_USO` (lida e escrita pelo
código). As 65 do meio continuam invisíveis para o `flag_audit` (é soma), como previsto.

**Teste no jogo (falta, o autor faz):**
- Save novo, tutorial: o texto do Livro aparece; nesse mesmo dia o presente é de
  berries entre as 8 iniciais.
- Colher uma berry de rota fora das 8 iniciais (Cheri, Chesto, Pecha, Rawst, Aspear,
  Leppa, Oran, Persim) → nos dias seguintes ela pode sair no presente.
- Bolsa sem espaço para berry na colheita → a berry **não** entra no Livro.
- Marco (debug: ligar 12 flags do Livro): o Bram dá 5 Growth Mulch uma vez só; com
  a bolsa cheia de adubo ele avisa e paga na próxima visita.
- Pós-Liga, Livro sem rara: a Laurel diz que falta, e no mesmo dia, depois de colher
  uma rara, ela dá.
- Save antigo que já tinha o tutorial: falar com o Bram → presente normal.

---

## Parte 4 — Cruzamento completo

**Objetivo.** As 67 berries nascem das 8 iniciais.

**Skills:** nenhuma específica; `diagnosticar-flag` se a trava pós-Liga falhar.

**Passos**

1. `OW_BERRY_MUTATIONS` = TRUE.
2. **4 → 6 bits**: `padding:2` do struct da árvore (`include/global.berry.h:80`) vira
   `mutationC:2`; `union TreeMutation` ganha o campo; `GetTreeMutationValue` e
   `SetTreeMutations` leem e gravam os 6 bits. Conferir o tamanho do struct com
   `STATIC_ASSERT` (o save não pode crescer).
3. `sBerryMutations` (`src/berry.c:2455`) passa de 13 para as 58 linhas do §4.2, com as
   13 do jogo intocadas.
4. **Trava pós-Liga**: `TryForMutation` ignora as linhas de Lansat e Starf sem
   `FLAG_SYS_GAME_CLEAR`.
5. **Script de verificação** em `dev_scripts/` (ex.: `berry_mutations_check.py`): lê a
   tabela do C e confere que nenhum par se repete, que toda berry menos a Enigma tem
   receita ou é inicial, e que a geração de cada uma bate com o §4.2. Rodar no CI se
   for barato.

**Teste no jogo (debug):** Chesto ao lado de Persim com Surprise Mulch → Kelpsy extra
na colheita e Kelpsy no Livro; três gerações seguidas; Micle + Custap antes da Liga
não dá Lansat; depois da Liga dá.

**Pronto quando:** o script passa e as três gerações foram vistas no jogo.

### Parte 4 — feita no código (30/09/2026), falta o teste no jogo

**O que entrou**

| O quê | Onde |
|---|---|
| `OW_BERRY_MUTATIONS` = TRUE | `include/config/overworld.h` |
| `padding:2` → `mutationC:2`; índice da receita em 6 bits (C:B:A), `union TreeMutation` com o campo `c` | `include/global.berry.h`, `src/berry.c` |
| `STATIC_ASSERT(sizeof(struct BerryTree) == 8)` (o save não cresce sem alguém ver) e `ARRAY_COUNT(sBerryMutations) <= 63` | idem |
| `sBerryMutations`: as 13 do jogo **nas mesmas posições** + 45 novas, por geração = 58 | `src/berry.c` |
| Trava pós-Liga: `IsMutationUnlocked` (Lansat, Starf só com `FLAG_SYS_GAME_CLEAR`) dentro de `GetMutationOutcome` | idem |
| `dev_scripts/berry_mutations_check.py`: 6 regras (6 bits, par repetido, duas receitas, sem receita, alcançável, receita e geração iguais às do §4.2) | novo |
| CI `.github/workflows/berry-mutations.yml`, no molde do `map-graph.yml` | novo |
| 3 testes de cruzamento em `test/berry_garden.c` | idem |

**Onde divergiu do plano, e por quê**

1. **Consertado um defeito do motor (upstream) que o plano não previa.** O
   `TryForMutation` sorteava a chance para **cada** árvore e, no primeiro vizinho
   adjacente sorteado, devolvia o resultado **mesmo quando o par não tinha receita**.
   Numa horta cheia, um vizinho sem receita roubava a chance do vizinho que tinha:
   com 4 vizinhos, a chance real de uma receita caía bem abaixo dos 25% do design.
   Agora só vizinho que forma receita (e está liberada) ganha sorteio, cada um com os
   25% (50% com Surprise/Amaze Mulch). Com dois vizinhos com receita, a chance de
   cruzar fica maior que 25%, e é isso que faz o canteiro cheio valer a pena (§4.2).
2. **A trava pós-Liga vale no plantio**, que é quando o motor decide a mutação. Plantar
   Micle ao lado de Custap antes da Liga e colher depois não dá Lansat; replantar
   depois da Liga dá.
3. **Verificador no CI** e não no `make`: o `map_graph` roda no `make` só como aviso,
   e uma tabela errada tem que **barrar**, não avisar.

**Medido**
- `berry_mutations_check.py`: “ok - 58 receitas, 66 berries alcançáveis (geração
  0: 8, 1: 15, 2: 13, 3: 13, 4: 8, 5: 5, 6: 2, 7: 2)” — igual ao ritmo do §4.2.
- O verificador **pega** erro: testado com 5 tabelas quebradas de propósito (par
  repetido, berry sem receita, geração errada, Enigma com receita, inicial com
  receita), todas reprovadas com a mensagem certa.
- Save: `struct BerryTree` continua com 8 bytes (o assert passa no build).
- Falas de colheita com mutação (do motor, agora alcançáveis): pior caso real
  (nome de 7 letras + “15 Maranga Berries”) = 200 px, dentro dos 208.

**Teste no jogo (falta, o autor faz; debug ajuda):**
- Cheri no canteiro, Chesto plantada ao lado **antes**, replantar a Cheri até cruzar →
  na colheita, “and 1 Lum Berry”; a Lum entra no Livro.
- Três gerações seguidas (ex.: Cheri+Chesto → Lum; Oran+Leppa → Sitrus; Lum+Sitrus →
  Tamato).
- Micle ao lado de Custap antes da Liga nunca dá Lansat; depois da Liga dá.
- Árvore de rota natural ao lado de um plantio: pode ser o vizinho que cruza, mas ela
  mesma nunca dá mutação (`stopGrowth`, regra do motor).

---

## Parte 5 — Estado diário da horta

**Objetivo.** Uma flag diária e uma var de bits controlam tudo o que é “uma vez por
dia”, como o Kurt (`VAR_KURT_TODAY` + `FLAG_DAILY_KURT_NEW_DAY`) e o Nexus.

**Passos**

1. Specials `GardenRollDay`, `GardenToday_Check`, `GardenToday_Set` (§14.6). O
   `GardenRollDay` zera `VAR_GARDEN_TODAY` quando `FLAG_DAILY_GARDEN_NEW_DAY` está
   limpa, seta a flag e sorteia os eventos do dia (Klara 1 em 7, Mustard 1 domingo em 4
   — os sorteios ficam desligados até as Partes 11 e 16).
2. Chamar `GardenRollDay` no `ON_TRANSITION` da `Route30` **e** da `Route30_House`
   (quem entrar primeiro no dia).
3. Constantes dos 16 bits (`GARDEN_TODAY_ORDER_ROLLED` … `GARDEN_TODAY_TALKED_PEONY`)
   num header novo, `include/constants/berry_garden.h`.

**Teste no jogo:** mudar o relógio para o dia seguinte → a var zera uma vez só; sair e
entrar no mesmo dia não zera.

### Parte 5 — feita no código (30/09/2026), falta o teste no jogo

**O que entrou**

| O quê | Onde |
|---|---|
| Os 16 bits `GARDEN_TODAY_*`, cada um com a parte que o usa pela primeira vez, e `GARDEN_TODAY_BIT_COUNT` | `include/constants/berry_garden.h` (novo), incluído em `data/event_scripts.s` e em `include/berry_garden.h` |
| `GardenRollDay`, `GardenToday_Check`, `GardenToday_Set` (specials, `VAR_0x8004` = bit) e `GardenToday_Has` / `GardenToday_Mark` para o C | `src/berry_garden.c`, `data/specials.inc` |
| `GardenRollDay` no `ON_TRANSITION` da `Route30` e da `Route30_House` (a casa ganhou `ON_TRANSITION`) | os dois `scripts.inc` |
| `GardenRollDay` também no começo da conversa do Bram e da Laurel, depois do `dotimebasedevents` | `Route30_House/scripts.inc` |
| 2 testes (o dia recomeça uma vez; bits independentes, nada além do 15) | `test/berry_garden.c` |

**Onde divergiu do plano, e por quê**

1. **`GardenRollDay` também nas conversas**, não só no `ON_TRANSITION`. Medido no
   motor: a flag diária é limpa pelo `DoTimeBasedEvents`, que roda **antes** do
   `ON_TRANSITION` em toda troca de mapa (`overworld.c`) — então o `ON_TRANSITION`
   sempre vê o dia certo. Mas o `DoTimeBasedEvents` também roda por uma tarefa
   periódica enquanto o jogador anda (`field_tasks.c`): se a meia-noite passar com o
   jogador parado na Route 30 ou dentro da casa, não há troca de mapa, e só uma
   conversa depois do `dotimebasedevents` percebe o dia novo. É o mesmo cuidado do Kurt.
   **Regra para as próximas partes:** todo NPC da horta que lê `VAR_GARDEN_TODAY` chama
   `dotimebasedevents` + `special GardenRollDay` antes.
2. **Sem macros de script** (`garden_today_check`…): uma macro teria que existir antes
   de todo mapa no `event_scripts.s`, e o repo não tem esse lugar para macros de
   conteúdo. Os scripts usam `setvar VAR_0x8004, GARDEN_TODAY_X` + `specialvar`/`special`,
   como o resto do repo.
3. **Os sorteios do dia não existem ainda** (Klara, Mustard): o `GardenRollDay` tem o
   ponto marcado onde entram, com a condição de cada um. Escrever agora seria código
   que ninguém lê.

**Revisão do que já existia, feita junto** (achados que só apareceram com a Parte 5):
- Comentários de `flags.h`/`vars.h` que diziam “not written yet” para o
  `GardenRollDay` foram atualizados.
- **Armadilha para a Parte 6** (escrita no passo 1 dela): o “nível + 10” que o plano
  sugeria para “reforma paga” abriria o canteiro B na hora, porque a Parte 2 compara
  a var com `< 2`.
- **Armadilha para a Parte 16** (escrita no passo 2 dela e no C): o
  `BerryLedger_Count` conta a Enigma, então “66 no Livro” não é “todas menos a Enigma”.
- **`FLAG_TEMP` já ocupadas** listadas no começo da Parte 8.

**Catálogo:** `FLAG_DAILY_GARDEN_NEW_DAY` agora aparece lida e escrita pelo código
(2/2), não só “limpa pelo bloco diário”.

**Teste no jogo (falta, o autor faz):** nada visível muda nesta parte; o teste é o
debug de var.
- Ver `VAR_GARDEN_TODAY` (0x4127) = 0 ao entrar na Route 30; marcar um bit no debug;
  sair e entrar no mesmo dia → o bit continua.
- Mudar o relógio para o dia seguinte e entrar → volta a 0.
- Ficar parado na casa virando a meia-noite e falar com o Bram → volta a 0.

---

## Parte 6 — Níveis da horta

**Objetivo.** Reformas 1–4 (a 5 é da Parte 16), com pagamento e cena na manhã
seguinte.

**Skills:** `encenar-cutscene`, `visibilidade-e-gatilhos`.

**Passos**

1. Menu de reforma com o Bram (em casa, de dia): mostra o próximo nível, o que pede
   (Livro N + ₽) e cobra. Grava “pago, pronto amanhã” sem flag nova (ex.: nível + 10
   em `VAR_BERRY_GARDEN_LEVEL` até a manhã seguinte; o `ON_TRANSITION` da manhã conclui).
   **Cuidado (revisão da Parte 5):** o “nível + 10” quebra quem já compara essa var.
   `Route30_EventScript_GardenVisibility` e `Route30_OnLoad` trancam o canteiro B com
   `< 2`, e a migração de save antigo testa `== 0`: com 1 pago para 2, a var vira 11 e
   o B **abre na hora**, antes da cena. O “pago” tem que morar fora do nível. O
   `VAR_GARDEN_TODAY` não serve: zera à meia-noite e a obra conclui só “na manhã
   seguinte”. Recomendação: var própria `VAR_BERRY_GARDEN_WORK` (nível encomendado,
   0 = nenhum), concluída no primeiro `GardenRollDay` de um dia **depois** do pagamento.
2. **Cenas de reforma** (§5), ao entrar na Route 30 na manhã seguinte ao pagamento:
   nível 2 (Bram), 3 (Bram + Laurel), 4 (Bugsy + Bram).
3. **Nível 2**: canteiro B abre (a trava da Parte 2 passa a ler o nível), presente vira
   3 berries, **semente encomendada** (`BerryLedger_BuildSeedMenu` + `dynmultichoice`,
   1 por dia, divide a flag diária do presente com o sorteio).
4. **Nível 3** (Livro 22 + ₽10.000 + Ato 1 feito): special `WaterGardenTrees` no
   `ON_TRANSITION`, uma vez por dia (bit “horta regada”).
5. **Nível 4** (Livro 32 + Ato 1 feito, o Bugsy constrói): `BERRY_PESTS_CHANCE` 30% e
   raro ×1,5 — só tem efeito depois da Parte 10; a condição já fica escrita.
6. A condição “Ato 1 feito” lê `VAR_HARVEST_KING >= 4`; até a Parte 12 existir, os
   níveis 3 e 4 ficam indisponíveis (o Bram diz que “falta alguém para ajudar”).

**Teste no jogo:** debug Livro 12 + ₽5.000 → paga → no dia seguinte a cena e o B
aberto; sem dinheiro não cobra; nível 3 rega sozinho às 4h.

### Parte 6 — feita no código (30/09/2026), falta o teste no jogo

**O que entrou**

| O quê | Onde |
|---|---|
| `VAR_BERRY_GARDEN_WORK` (`0x412E`): 0 = nada; 2..4 = nível pago, em obra; 12..14 = pronto, fala pendente | `include/constants/vars.h` (marcador → `0x412F`) |
| Constantes `GARDEN_LEVEL_*`, `GARDEN_WORK_*`, `GARDEN_REFORM_*`, `HARVEST_KING_ACT1_DONE` | `include/constants/berry_garden.h` |
| Tabela `sGardenReforms` (Livro, Ato 1, preço por nível) com `STATIC_ASSERT` de cobrir todo nível | `src/berry_garden.c` |
| `GardenReform_Check` / `_Pay` / `_TakeBuiltLevel`; a obra conclui dentro do `GardenRollDay` | idem |
| `GardenIrrigate` (nível 3): rega os 10 canteiros uma vez por dia (`GARDEN_TODAY_WATERED`), não o da Laurel | idem; `ON_TRANSITION` da Route 30, depois do `GardenRollDay` |
| Regra de rega extraída para `WaterBerryTreeById`, usada pela regadeira **e** pelo canal (uma regra, dois chamadores) | `src/berry.c`, `include/berry.h` |
| `GardenGift_Count` (2, ou 3 a partir do nível 2) e `BerryLedger_BuildSeedMenu` | `src/berry_garden.c` |
| Conversa do Bram: fala da obra pronta → marcos → oferta de reforma (1 vez por visita, `FLAG_TEMP_4`) → presente de 2/3 ou semente encomendada | `Route30_House/scripts.inc` |
| 16 textos novos (ofertas, obra pronta nos 3 níveis, semente, “three”) | idem |
| 6 testes (oferta só com Livro 12, sem dinheiro não cobra, obra só no dia seguinte e fala uma vez, Ato 1 e Bug Hotel grátis, canal, lista da semente) | `test/berry_garden.c` |

**Onde divergiu do plano, e por quê**

1. **O “pago, pronto amanhã” mora em `VAR_BERRY_GARDEN_WORK`**, não em “nível + 10”
   (armadilha achada na revisão da Parte 5: a trava do B compara o nível com `< 2`).
2. **A cena da manhã seguinte é a primeira fala do Bram na próxima conversa**, na casa.
   Motivo: o Bram só existe do lado de fora a partir da Parte 8, e um gatilho ao entrar
   na Route 30 precisaria cercar 4 entradas da horta (oeste, norte, porta, escada do
   sul) sem buraco. A fala do nível 3 tem as duas plaquinhas (Bram e Laurel, os dois na
   casa); a do nível 4 é o Bram contando do Bugsy. O design (§5) ganhou a nota.
3. **A obra conclui no primeiro `GardenRollDay` do dia seguinte**, que é à meia-noite
   (ou na primeira vez que o jogador aparece no dia). Como toda conversa do Bram chama o
   `GardenRollDay` antes, o pagamento sempre cai **depois** do rolamento do dia, e a obra
   nunca fica pronta no mesmo dia.
4. **A oferta de reforma e o “preciso de ajuda” aparecem uma vez por visita**
   (`FLAG_TEMP_4`), não em toda conversa. Sem isso, até a Parte 12 o jogador com Livro 22
   ouviria “preciso de ajuda” a cada presente.
5. **A oferta diz o número real do Livro** (`{STR_VAR_1}`): ela aparece quando o Livro
   chega ao tamanho **ou depois**; “Twelve Berries” erraria para quem chega com 20.
6. **Semente encomendada = 1 berry à escolha**, em vez das 3 sorteadas (“em vez do
   presente sorteado”, §3.5), qualquer uma do Livro **menos a Enigma**. B ou “Surprise me”
   voltam ao sorteio de 3. Lista em ordem de item; **sem** o `shouldSort` do motor, que
   ordena por id (a ordem já é essa) e, com lista vazia, estoura (`count - 1` em `u32`,
   `scrcmd.c`).
7. **Os nomes da lista são cópias no heap**: o menu dinâmico dá `Free` em cada nome ao
   fechar (`script_menu.c`); empurrar o ponteiro do nome direto da ROM travaria o jogo
   ao fechar o menu, com build limpo.
8. **Nível 4 (Bug Hotel)**: condição e oferta prontas; o efeito (pragas 30%, raro ×1,5)
   é da Parte 10, que deve ler `VAR_BERRY_GARDEN_LEVEL >= GARDEN_LEVEL_BUG_HOTEL`.

**Medido:** build limpo; `medir_linha.py` sem estouro; `checar_falantes.py` “241, tudo
em ordem”; `map_graph` ok; `berry_mutations_check` ok; testes compilam (não rodam: ver a
revisão das partes 1–3).

**Bug 3 do teste no jogo (02/10/2026), corrigido:** a oferta de reforma dizia “3052
Berries in your Book now” — o número era o **dinheiro** do jogador. O `showmoneybox`
imprime o dinheiro por `gStringVar1` (`PrintMoneyAmount`, `src/money.c`), e o tamanho do
Livro tinha sido posto no `STR_VAR_1` **antes** de abrir a caixa. Agora o número é
preenchido depois do `showmoneybox`. Regra: depois de `showmoneybox`/`updatemoneybox`, o
`STR_VAR_1` não vale mais nada.

**Ajuste do teste no jogo (02/10/2026): a oferta de reforma fecha a conversa.** Antes
a ordem era marcos → oferta → “Tomorrow morning, then.” → presente (“there's more
tomorrow…”), e o fechamento da obra ficava no meio do presente, com dois “amanhã”
seguidos. Agora: obra pronta → marcos → **presente** (ou “That's your two/three”) →
**oferta por último** (`Route30_House_EventScript_AfterGift`), e quem paga ouve “Done deal.
Come and look in the morning.” e a conversa acaba. A semente encomendada também termina
no `AfterGift`. Só a bolsa cheia encerra antes (sem oferta naquela conversa).

**Auditoria estática (`bug/auditar_scripts.py`, ferramenta de outra sessão, só lida):**
nos mapas da horta sobram 2 avisos `CALL_END` em `Route30_House` — as saídas de bolsa
cheia do presente (`Common_EventScript_ShowBagIsFull` faz `release` e encerra de
propósito, padrão que já existia). O aviso de fall-through do `msgbox` para `GiveDraw` foi
resolvido com `goto` explícito. O aviso de `lock` ativo em `berry_tree.inc:50` é falso
positivo: é um `end` depois de um `yesno` cujos dois resultados já desviaram.

**Teste no jogo (falta, o autor faz; debug):**
- Livro 12 (debug de 12 flags) e ₽5.000: o Bram oferece “12 Berries in your Book now…
  ¥5,000” com a caixa de dinheiro; “Não” → “Suit yourself”; falar de novo na mesma
  visita não repete; sair e entrar → oferece de novo.
- Pagar sem dinheiro: “Come back when you've got the money”, nada é cobrado.
- Pagar: no mesmo dia nada muda; virar o dia → o B abre (grama vira terra), e a próxima
  conversa começa com “Four more beds! Laurel dug them.” uma vez só; o presente vira
  “Three today… Or have you got one in mind?”.
- “I've got one”: lista com rolagem das berries do Livro, sem Enigma; escolher → 1
  berry, e o presente do dia acaba; B no menu → sorteio de 3.
- Nível 3 (debug `VAR_HARVEST_KING` = 4, Livro 22, ₽10.000): “preciso de ajuda” some,
  oferta do canal; no dia seguinte, plantar e entrar na Route 30 → a planta já regada.

---

## Parte 7 — Pedidos do dia

**Objetivo.** Um pedido por dia; o de descoberta traz a Laurel para o ciclo.

**Passos**

1. Na primeira conversa do dia com o Bram de manhã: sorteia o pedido (bit
   `ORDER_ROLLED`), grava em `VAR_BERRY_ORDER`.
2. **Comum**: N de uma berry do Livro; paga ₽ por berry + 1 adubo.
3. **Descoberta** (nível 2+, 1 dia em 3): `BerryLedger_NextDiscovery`; o Bram não sabe
   a receita e manda perguntar à Laurel. Paga ₽ em dobro + Surprise Mulch.
4. **Dica da Laurel**: um texto só com 3 buffers (berry, pai 1, pai 2) — **nunca**
   `STR_VAR_4` (não existe no `charmap.txt`, §14.1 item 1).
5. Entrega: `checkitem` → `yesno` → `checkitemspace` → `removeitem` → `giveitem` →
   bit `ORDER_DONE`.
6. Clientes só no texto (Kurt, floricultura, Nurse de Cherrygrove, Moomoo Farm, Day
   Care). Nunca Poké Ball.

**Teste no jogo:** entregar com a bolsa cheia de adubo → avisa antes de tirar as
berries; sair e entrar não troca o pedido; pedido de descoberta cruzado de verdade
com a dica.

---

## Parte 8 — Elenco e rotina por horário

**Objetivo.** O mini Harvest Moon: cada um no seu lugar por período e dia da semana,
sem flag persistente.

**Skills:** `visibilidade-e-gatilhos`, `encenar-cutscene`, `adicionar-npc` (só se a
Tilly precisar de sprite novo: `LITTLE_GIRL` existe), `parceiro-pokemon-de-npc` (não:
a Sunflora fica dentro de casa, sozinha).

**Passos**

0. **`FLAG_TEMP` já ocupadas** (revisão da Parte 5): na `Route30`, `FLAG_TEMP_1` (árvore
   de Cut em (30,10)), `FLAG_TEMP_5` (canteiro B) e `FLAG_TEMP_6` (canteiro da Laurel);
   na `Route30_House`, `FLAG_TEMP_1` (fala do dia do tutorial) e `FLAG_TEMP_4` (o Bram
   já falou da reforma nesta visita, Parte 6). A Parte 8 escolhe das livres (conferir
   com `grep` antes) e dá apelido em `flags.h`, como as da Parte 2.
   **Herança da Parte 6:** a fala da obra pronta (`Route30_House_EventScript_BuiltLevel`,
   que consome `GardenReform_TakeBuiltLevel`) e a oferta de reforma estão na conversa do
   Bram **na casa**. Quando o Bram passar a ficar na horta de manhã, a conversa dele lá
   tem que chamar as mesmas duas coisas (e o `GardenRollDay` antes), senão o jogador que
   só encontra o Bram de manhã nunca ouve a fala nem recebe a oferta.
1. Objetos na `Route30`: Bram (fora, manhã, (31,45)), Laurel (fora, dia, (27,43)),
   Tilly (banquinha, (24,41), fim de semana de dia), Bugsy ((31,43), ter/qui de dia,
   estado ≥ 3). Cada um com a sua `FLAG_TEMP`.
2. Objetos na `Route30_House`: Bram e Laurel em versão dia/noite (mesa, sofá,
   janela), Tilly (manhã de fim de semana), Sunflora da Laurel.
3. `ON_TRANSITION` de cada mapa: `GetTimeOfDay` + `GetDayOfWeek` + `VAR_HARVEST_KING`
   → seta a `FLAG_TEMP` de quem **não** está ali agora. Rev3: fim de semana de dia a
   Laurel fica em casa (dia de forno).
4. Bram dormindo à noite: fala dormindo (texto próprio).
5. Tilly de loja: `pokemart` com os adubos (inclusive Rich e Surprise quando a horta
   chega ao nível 4).
6. **Orçamento de objetos**: contar na pior hora de cada tabela (§2.3, §13.4, §14.3):
   nunca passar de 15 com jogador e follower. Registrar a conta no commit.

**Teste no jogo:** passar pelos três períodos e pelos 7 dias da semana mudando o
relógio; nenhum canteiro some; ninguém fica no único acesso de um canteiro.

---

## Parte 9 — Banco de falas

**Objetivo.** 10 falas por evento repetitivo, corações e reações.

**Skills:** `nomear-falante` (medir e checar), `evoluir-historia-de-evento` (voz de
cada personagem).

**Passos**

1. Specials `GardenLine_Pick` (`VAR_DAYS % N`, N por tier) e `GardenHearts_Talk`
   (sobe 1 por dia que o jogador fala, bit em `VAR_GARDEN_TODAY`, 4 bits por
   personagem em `VAR_GARDEN_HEARTS`; tiers 5 e 12 dias).
2. Ordem de cada conversa: cena pendente → reação de contexto (primeira conversa do
   dia) → rodízio.
3. Escrever os bancos do §14.4 A–S que não dependem da história (A–H, P, Q, R) num
   arquivo novo `data/scripts/berry_garden_lines.inc`, com os textos em
   `data/text/berry_garden.inc` (ou onde o repo guarda texto compartilhado).
4. Os bancos que dependem de personagem da história (I Klara, J Avery, K Peony, L
   Peonia, M/N Calyrex, O cartas, S Mustard) ficam para as partes que trazem o
   personagem.
5. **Regra da surpresa**: nenhuma fala desta parte cita rei, corcel ou Calyrex.

**Teste no jogo:** 10 dias seguidos no relógio → 10 falas diferentes do Bram; debug
com corações 5 e 12 → falas íntimas aparecem.

---

## Parte 10 — Infestações

**Objetivo.** Pragas e ervas só nos canteiros da horta; 8 famílias passam a existir só
ali.

**Skills:** `adicionar-batalha-npc` (não; é selvagem), `diagnosticar-flag` (se a
trava vazar para árvore de rota).

**Passos**

1. `OW_BERRY_WEEDS` e `OW_BERRY_PESTS` = TRUE; `IsBerryGardenTree` com `FIRST..LAST` e
   a guarda em `TryForWeeds` e `TryForPests` (design rev1 §6.1).
2. `GetBerryPestSpecies` vira tabela `[cor][slot]` (§7.2), com horário, geração da
   berry (da tabela da Parte 4) e adubo (Gooey/Rich → Rellor, Stable → Dwebble, metade
   das vezes).
3. Nível do selvagem: `10 + 4 × insígnias`, teto 60, no `CreateScriptedWildMon`
   (`src/berry.c:2397`).
4. `BERRY_PESTS_CHANCE` 15%, 30% no nível 4.
5. **Tirar as 8 famílias** de `src/data/wild_encounters.json` (Rellor e Wurmple da
   Route 37, Blipbug da Route 30, Scatterbug do National Park, Combee da Route 31,
   Volbeat e Illumise da Kitakami Border, Dwebble da Cliff Edge Cave), redistribuindo a
   porcentagem entre o que já existe na rota. Rodar `dev_scripts/fontes_legitimas.py`
   para confirmar que cada família ainda tem fonte (a horta).
6. Ervas daninhas cosméticas na v1 (decisão 4 do rev1).

**Teste no jogo:** 20 manhãs no relógio com a horta cheia → pragas aparecem nos
canteiros e **nunca** numa árvore de rota; cor vermelha dá Wurmple no incomum; Stable
Mulch dá Dwebble.

---

## Parte 11 — Batalhas de sempre: Tilly, Bugsy e Klara

**Objetivo.** As batalhas repetíveis que não dependem do fim da história.

**Skills:** `adicionar-batalha-npc`, `batalha-sem-blackout`,
`adicionar-grafico-trainer` (Klara), `converter-sprite` (quando o autor trouxer a arte).

**Passos**

1. Macro `garden_fight` em `data/scripts/berry_garden.inc`, cópia da `nexus_fight`
   (`cleartrainerflag` antes e depois, `B_FLAG_NO_WHITEOUT` só durante, resultado em
   `GetBattleOutcome`, bit “lutou hoje”).
2. Treinadores em `opponents.h` e `src/data/trainers.party`: Tilly ×3 (time pelo
   nível da horta, com os apelidos do §14.5), Bugsy ×3 (rodízio `VAR_DAYS % 3`),
   Klara ×3. Nível pela escala do repo (`src/level_scaling.c`).
3. **Assalto da Klara**: sorteado no `GardenRollDay` (1 manhã em 7, horta nível 2+ e
   algum canteiro maduro); objeto na frente de um canteiro maduro; vitória salva,
   derrota ou sair do mapa sem falar → special `EmptyRandomRipeGardenTree`; 5ª vitória
   → fala do gancho do mochi (`VAR_GARDEN_RIVALS`).
4. Banco I (Klara) do §14.4 e as falas de batalha do §14.5.
5. Sprite da Klara: `LASS` como substituto até o autor trazer o de verdade.

**Teste no jogo:** perder para a Tilly não dá blackout nem custa dinheiro; lutar duas
vezes no mesmo dia não pode; Klara: vencer, perder e sair do mapa, os três casos.

---

## Parte 12 — Sidequest: Prólogo ao Ato 4 (estados 0 → 8)

**Objetivo.** A história até a primeira folha, sem nenhuma menção a rei ou corcel.

**Skills:** `evento-esqueleto` (primeiro esqueleto com estado certo, depois as falas),
`evoluir-historia-de-evento`, `encenar-cutscene`, `visibilidade-e-gatilhos`,
`nomear-falante`.

**Passos** (um commit por ato; gatilhos da tabela do §8.1)

1. **Prólogo** (0 → 1): fala do tutorial (“Not the patch by the door.”).
2. **Ato 1a** (1 → 2): sub-rotina chamada pelo script de praga depois da batalha.
3. **Ato 1b** (2 → 3): 2ª insígnia + Route 30 de dia; o Bugsy chega; ele entra na
   rotina de ter/qui.
4. **Ato 1c** (3 → 4): 3 exclusivos da horta na Pokédex (`getcaughtmon`) + falar com o
   Bugsy; libera níveis 3 e 4 (Parte 6) e a batalha do Bugsy (Parte 11 já pronta).
5. **Ato 2** (4 → 5): horta nível 3 + noite no lago; o Spectrier como “visitante
   noturno” (objeto `SPECIES(SPECTRIER)` escondido por `FLAG_TEMP`, nunca batalhável
   aqui).
6. **Ato 2b** (5 → 6): o Bram acorda à noite.
7. **Ato 3** (6 → 7): Livro 40 + 7ª insígnia + Laurel à noite; ela entrega a Enigma;
   o canteiro da Laurel destrava (a trava da Parte 2 passa a ler o estado).
8. **Ato 4** (7 → 8): `GetKingsPlotStage` e `RipenGardenTrees` (C); a Enigma brota;
   começam as **cartas da manhã** (banco O) e a fala “I wrote to Freezington”.
9. **Retry** e **surpresa** conferidos com `grep` (nenhum “king”, “Calyrex”,
   “Glastrier”, “Spectrier” em texto alcançável antes do estado 7).

**Teste no jogo:** jogar os 8 estados com debug de var entre um e outro; cada ato
testado também entrando por um save velho no meio.

---

## Parte 13 — Ato 5 e 5b: o Rei e as sementes (estados 8 → 10/11)

**Skills:** `evoluir-historia-de-evento`, `encenar-cutscene`,
`parceiro-pokemon-de-npc` (não; o Calyrex é objeto de cena), `adicionar-npc` (Peony e
Peonia com substitutos `HIKER` e `PICNICKER`), `nomear-falante` (a plaquinha “???”).

**Passos**

1. **Ato 5** (8 → 9, versão §13.3 + §14.2): Enigma madura + noite; `hidefollower`;
   Peony ajoelhado, o Calyrex fala por ele; `removeobject` do Calyrex antes de a
   Peonia entrar; orçamento 15.
2. **As sementes**: fala do Peony e da Laurel; special `EmptyKingsPlot`; o canteiro da
   Laurel em estado 9 abre `multichoice` (Iceroot / Shaderoot / Not yet); plantar grava
   10 ou 11.
3. **A cenoura**: na noite seguinte o canteiro dá o item-chave; sem ele, o corcel não
   aparece (a checagem fica pronta para as Partes 14 e 15).
4. **Peony e Peonia hóspedes** (estados 9–14): objetos na casa e na horta com
   `FLAG_TEMP` pelo estado e período; bancos K, L e M (o Calyrex pelo Peony dormindo).
5. Batalha semanal do Peony na horta de manhã (Parte 11 já tem a macro).
6. Pryce e Morty nos ginásios ganham a fala de gancho (sem cenoura: só a linha curta;
   com cenoura: o recado do §15.2). O gatilho da dungeon fica escondido até as partes
   14/15 existirem.

**Teste no jogo:** as duas escolhas, cada uma num save; “Not yet” não muda nada;
cenoura só na noite seguinte.

---

## Parte 14 — Caminho branco: Greenfield (estado 10 → 12)

**Objetivo.** Os 2 mapas do protótipo instalados e a dungeon jogável.

**Skills:** `adicionar-tileset` e `montar-tileset` (paleta de cristal e a do “depois”),
`prototipo-de-mapa`, `mapa-de-ligacoes`, `acabamento-de-mapa`,
`adicionar-batalha-npc`, `batalha-sem-blackout`, `adicionar-npc` (Molly), `encenar-cutscene`.

**Material pronto:** `prototipo_corceis/greenfield_map.bin`, `mansion_map.bin`,
`greenfield_objects.json`, `gera.py`; tabela do `REI_DA_COLHEITA.md` §15.5c.

**Passos**

1. **Paletas**: secundário de uma cidade de Johto copiado, com a paleta de cristal
   (azul-claro) e a de “depois”; troca por estado no `ON_LOAD`. É a única arte nova.
2. **Layouts** `Greenfield` (30×39) e `Greenfield_Mansion` (26×23) em
   `layouts.json`; `map.json` com os objetos do protótipo (Molly e Glastrier vêm do
   `gera.py`).
3. **Ligação**: portão novo a oeste de `RuinsOfAlph_Outside` → entrada oeste de
   Greenfield; porta da casa grande → mansão. `mapa-de-ligacoes` confirma alcançável.
   O portão só deixa passar com a Iceroot na bolsa e estado 10 (senão uma fala curta
   do cristal).
4. **Cenas**: chegada da Peonia; os três moradores presos; Molly no saguão; o
   Scientist (1 treinador, preso no “mesmo dia”); o salão com a nota do Hale
   (`bg_event`); oferecer a Iceroot; batalha e captura do Glastrier (nível 60, retry
   do §8.1; só a captura avança); `removeitem` da cenoura; Never-Melt Ice da Molly
   (`checkitemspace` antes).
5. **Estado 12**: Greenfield com a paleta do “depois”; falas novas dos três moradores
   (**escrever**: o design só diz que “o dia deles andou”); o Pryce em Mahogany diz
   “I'll need a better coat.”
6. A mansão fica trancada pelo cristal se o jogador escolheu o outro corcel (estado
   11/13).

**Teste no jogo:** fugir, perder e derrotar sem capturar o Glastrier → volta; capturar
→ estado 12, cor volta; o outro caminho continua fechado.

---

## Parte 15 — Caminho escuro: a Torre de Bronze (estado 11 → 13)

**Skills:** as mesmas da Parte 14.

**Material pronto:** `prototipo_corceis/brasstower_1f_map.bin`,
`brasstower_1f_objects.json`, `brasstower_roof_objects.json`, `gera.py`; §15.5c.

**Passos**

1. **Paletas**: `burned_tower` com entardecer sépia (1F) e noite de incêndio (telhado).
2. **Layouts** `BrassTowerMemory_1F` (27×25, `BurnedTower_1F` sem buracos, 4 estátuas)
   e `BrassTowerMemory_Roof` (23×21, `TinTower_RoofDay` com brasas).
3. **Entrada**: `EcruteakCity_Theater` à noite, estado 11, Shaderoot na bolsa → cena
   da dança (Morty, Eusine) → warp para o 1F. Sem cenoura, as Kimono Girls não dançam
   isso.
4. **1F**: 3 Sábios-memória (falas), Kimono Girl no canto; `coord_event` na escada
   (14,4): raio (flash + `playse`) + narração + warp ao telhado.
5. **Telhado**: Sábio Tomo (treinador, sem blackout, time a definir — sugestão:
   fantasmas e fogo de Johto antigo); fala de vitória; a sombra do Ho-Oh passa e não
   para (movimento de objeto `SPECIES(HO_OH)` pelo céu, sem parar); batalha e captura do
   Spectrier (nível 60, retry); `removeitem` da cenoura.
6. **Volta**: o jogador acorda no `BurnedTower_B1F` (“You were gone three minutes.”);
   Spell Tag do Morty; lápide do Tomo em Ecruteak (`bg_event` no quintal dos Sábios).
7. O Spectrier-visitante do Ato 2 some da horta a partir do estado 13.

**Teste no jogo:** o mesmo da Parte 14, e a cena do raio sem travar (entrada e saída
por cada lado da escada).

---

## Parte 16 — Ato 7, Epílogo e pós-história (estados 12/13 → 15)

**Skills:** `batalha-sem-blackout`, `adicionar-batalha-npc`, `evoluir-historia-de-evento`,
`entregar-pokemon-ou-ovo` (não; é captura), `encenar-cutscene`.

**Passos**

1. **Ato 7** (→ 14): noite, corcel na party; a prova com
   `TRAINER_HARVEST_KING_TRIAL` (time do Peony, classe e nome “Calyrex”, front pic do
   Peony, sem blackout); depois o encontro fixo com o Calyrex (nível 65); só a captura
   avança; Reins of Unity da Laurel (`checkitemspace` antes).
2. **Epílogo** (→ 15): manhã seguinte; cena `LaurelSaysName` única (a primeira entre
   marco 66 e epílogo toca a principal; a outra toca a alternativa); carta da Honey.
   **Atenção:** “marco 66” = todas as berries **menos a Enigma** registradas, e não
   `BerryLedger_Count() >= 66` (a contagem inclui a Enigma; ver Parte 3, passo 8).
3. **Nível 5 — King's Garden**: canteiro da Laurel com colheita dobrada; a Enigma
   renasce sozinha quando o canteiro fica vazio (tratar o ID como natural de Enigma com
   `StartNaturalBerryTreeRegeneration`).
4. **Pós-história**: Avery às sextas (banco J, batalha), Peony e Peonia acampados no
   lago nas noites de fim de semana (bancos K e L, batalhas, dupla Tilly + Peonia),
   Mustard 1 domingo em 4 (banco S, batalha sem Urshifu), carta de Freezington
   (estátua) e a fala 6 do Calyrex na party (banco N).
5. Treinadores restantes do §14.6 (Avery ×3, Peony ×3, Peonia ×3 + dupla, Mustard ×1).

**Teste no jogo:** perder a prova e voltar na noite seguinte; capturar; epílogo nos
dois caminhos; a Enigma volta depois de colhida; uma semana inteira de pós-história no
relógio contando objetos.

---

## Parte 17 — Fechamento

1. `python3 dev_scripts/flag_audit.py --csv` e revisão final do diff (skill
   `catalogar-flags`): nenhuma flag órfã, nenhuma fora do array de save.
2. `checar_falantes.py` e `medir_linha.py` em todos os textos novos.
3. `mapa-de-ligacoes`: os 4 mapas novos alcançáveis; o `map_graph` sem aviso.
4. **Nexus**: pela R1 do `NEXUS_REGRAS.md`, Calyrex e o corcel escolhido entram no
   sorteio depois de capturados; atualizar `.claude/rift_missions/nexus/POOL_LENDARIOS.md`.
5. `dev_scripts/item_audit.py` e `fontes_legitimas.py`: Glastrier/Spectrier/Calyrex,
   as 8 famílias e os adubos sem fonte agora têm fonte.
6. Renders novos da Route 30 (dia/noite/fim de semana) e dos 4 mapas instalados;
   atualizar as páginas (artifacts) se o autor quiser.
7. `grep` da surpresa em todo texto alcançável antes do estado 7.
8. **Jogada completa** num save novo, do tutorial ao estado 15, nos dois caminhos.
9. Marcar no topo do `REI_DA_COLHEITA.md` o que foi implementado e onde o código
   divergiu do design.

---

## 18. Pendências do autor

| # | O quê | Bloqueia | Até lá |
|---|---|---|---|
| 1 | Sprites (overworld + front pic): Peony, Peonia, Klara, Avery, Mustard, Molly adulta | nada | `HIKER`, `PICNICKER`, `LASS`, `PSYCHIC_M`, (Mustard: a definir), `WOMAN_2` |
| 2 | Prêmio do Peony (Exp. Candy M? conferir no `SOULGOLD_ITEMS_AUDIT.md`) e o item grande do Mustard | Parte 16 | adubo |
| 3 | Falas novas dos 3 moradores de Greenfield no estado 12 | Parte 14 | o agente propõe, o autor aprova |
| 4 | Time do Sábio Tomo | Parte 15 | o agente propõe |
| 5 | Greenfield com outro desenho (mais flores, fonte no meio)? | Parte 14 | o protótipo aprovado |
| 6 | ~~Vars novas em `0x4127..` ou reciclar `VAR_GIFT_UNUSED_5..7`~~ | — | **fechada na Parte 1:** vars novas `0x4127..0x412D` |
| 7 | ~~Onde guardar o “último marco do Livro pago”~~ | — | **fechada na Parte 1:** `VAR_BERRY_LEDGER_MILESTONE` (`0x412D`) |
| 8 | Canteiro da Laurel fora das regras da horta (sem praga, erva nem rega automática)? | Parte 10 | fora (`GARDEN_LAST` = B4); ver “Parte 1 — feita” |
| 9 | Descrição e ícone das cenouras | nada | texto provisório + ícone do Big Root |
