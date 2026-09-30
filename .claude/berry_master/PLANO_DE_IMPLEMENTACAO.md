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
| 1 | Alocação e fundação | constantes, vars, flags, plaquinhas, itens; nada visível | — |
| 2 | A horta física | 10 canteiros + canteiro da Laurel na Route 30; plantar, regar, colher | 1 |
| 3 | Livro de Berries | colher registra; o Bram só dá berries do Livro; marcos | 1, 2 |
| 4 | Cruzamento completo | 58 receitas em 6 bits; Lansat/Starf só pós-Liga | 2, 3 |
| 5 | Estado diário | `FLAG_DAILY_GARDEN_NEW_DAY` + `VAR_GARDEN_TODAY` | 1 |
| 6 | Níveis da horta | reformas 1–4, canteiro B, irrigação, semente encomendada | 3, 5 |
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
   (`LaurelSaysName`, §14.1 item 4).

**Teste no jogo:** colher uma Sitrus de rota → no dia seguinte o Bram pode dá-la;
nunca dá uma que não foi colhida; debug com 12 flags ligadas → prêmio do marco 12 uma
vez só; bolsa cheia → o Bram avisa e não perde o prêmio.

**Pronto quando:** `flag_audit` mostra as 67 como lidas e escritas pelo C.

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

---

## Parte 6 — Níveis da horta

**Objetivo.** Reformas 1–4 (a 5 é da Parte 16), com pagamento e cena na manhã
seguinte.

**Skills:** `encenar-cutscene`, `visibilidade-e-gatilhos`.

**Passos**

1. Menu de reforma com o Bram (em casa, de dia): mostra o próximo nível, o que pede
   (Livro N + ₽) e cobra. Grava “pago, pronto amanhã” sem flag nova (ex.: nível + 10
   em `VAR_BERRY_GARDEN_LEVEL` até a manhã seguinte; o `ON_TRANSITION` da manhã conclui).
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
| 6 | Vars novas em `0x4127..` ou reciclar `VAR_GIFT_UNUSED_5..7` | Parte 1 | vars novas |
| 7 | Onde guardar o “último marco do Livro pago” | Parte 3 | var própria |
