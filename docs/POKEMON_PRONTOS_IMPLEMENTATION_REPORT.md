# Implementação da aba "Prontos para inserir" — SoulGold

> Branch `master`, commit inicial `692c07cd71643e970f4206fbc9099004579323b7`.
> Nenhum commit foi criado por esta tarefa (não solicitado). Alterações permanecem no worktree.
> Continuação de [POKEMON_AVAILABILITY_AUDIT.md](POKEMON_AVAILABILITY_AUDIT.md) e
> [POKEMON_DISABLED_AUDIT_AND_DISTRIBUTION_PLAN.md](POKEMON_DISABLED_AUDIT_AND_DISTRIBUTION_PLAN.md).
>
> **Esta é a versão final** do relatório: a primeira passagem (registrada em `git log` como intenção,
> nunca commitada) havia implementado 45 famílias e bloqueado 76 por falta de espaço de ROM. No meio da
> tarefa, o usuário habilitou `OW_GFX_COMPRESS` (`include/config/overworld.h`) por conta própria, liberando
> ~3,15 MB. Isso tornou viável concluir as **120 famílias completáveis restantes**, deixando pendente
> apenas 1 família bloqueada por innate (já sabida) e 1 removida do escopo por ser sublendária (achado
> desta segunda passagem, não previsto na primeira).

**Anexo:** [`POKEMON_PRONTOS_IMPLEMENTATION_STATUS.csv`](POKEMON_PRONTOS_IMPLEMENTATION_STATUS.csv) — as 122 famílias da aba `Prontos para inserir`, uma por linha, com status final.

---

## 1. Preparação e rastreabilidade

| Campo | Valor |
|---|---|
| Branch no início | `master` |
| Commit inicial | `692c07cd71643e970f4206fbc9099004579323b7` |
| Commit final | nenhum (sem commit criado, conforme instrução de não commitar automaticamente) |
| Arquivos de código modificados por mim | `include/config/species_enabled.h`, `src/data/wild_encounters.json` |
| Arquivo modificado pelo usuário (fora desta tarefa) | `include/config/overworld.h` — `OW_GFX_COMPRESS FALSE → TRUE`, liberando ~3,15 MB de ROM. Não alterado por mim; apenas aproveitado para ampliar o escopo implementável. |
| Arquivos gerados (não versionados) | `src/data/wild_encounters.h` (regenerado pelo build, git-ignorado) |

`AGENTS.md` não existe neste repositório. `README.md`, `INSTALL.md` foram lidos. A auditoria estática completa
(`POKEMON_AVAILABILITY_AUDIT.md`) e o plano de distribuição por innates (`POKEMON_DISABLED_AUDIT_AND_DISTRIBUTION_PLAN.md`)
já existiam no worktree e foram usados como ponto de partida — mas **todas as afirmações relevantes foram
re-verificadas contra o código real** antes de qualquer implementação (ver §3).

---

## 2. Resumo executivo

| Métrica | Valor |
|---|---|
| Linhas auditadas na aba `Prontos para inserir` | 316 (122 famílias) |
| Famílias já obtíveis antes (todas estavam desligadas por `P_FAMILY_*`) | 0 |
| Famílias **implementadas** nesta tarefa | **120** |
| Famílias **bloqueadas por membro sem innate** | **1** (BURMY/WORMADAM — Mothim não tem innates) |
| Famílias **removidas do escopo por serem unique** | **1** (TYPE_NULL/SILVALLY — ver achado abaixo) |
| Famílias que precisam de teste manual (em jogo) | as 120 implementadas — nenhuma foi testada em emulador (ver §8) |
| Novas entradas de espécie/forma obtíveis | **109** substituições de slot em `wild_encounters.json` (+2 via correção de flag apenas, sem tocar tabela) |
| Regressões de disponibilidade | **0** (verificado programaticamente, ver §6) |

**Achado crítico da primeira passagem:** o orçamento de ROM (32 MB) já estava em 96,79 % de uso antes de
qualquer alteração; habilitar as 121 famílias completáveis de uma vez **excedia o limite em 2.136.468
bytes** (erro real do linker). Isso forçou uma primeira entrega parcial de 45 famílias.

**Mudança de estado entre as duas passagens:** o usuário ligou `OW_GFX_COMPRESS` (compressão de gráficos de
overworld, incluindo followers), liberando **3.150.208 bytes** (~3,0 MB) sem eu precisar tocar em nenhum
dado de espécie. Um novo teste de build com **todas as 76 famílias então bloqueadas** habilitadas de uma vez
couberam de primeira: **32.186.684 B (95,92 %)**. Isso permitiu concluir a tarefa quase inteiramente, restando
apenas os dois casos abaixo.

**Achado novo desta segunda passagem — inconsistência na própria planilha:** `TYPE_NULL` aparece tanto na
aba `Prontos para inserir` (linhas 773–774, como base + 17 formas de Silvally) quanto na aba
`Pokemon uniques` (linha 772), classificado ali como **"Sublendário"**. As instruções da tarefa exigem
excluir sublendários de encontros comuns independentemente do que outra aba da mesma planilha sugira, e o
próprio catchRate de Silvally (3, igual ao de vários lendários) e seu grupo de ovos
(`EGG_GROUP_NO_EGGS_DISCOVERED`) confirmam a classificação. **Removido do escopo desta implementação.**

---

## 3. Auditoria dos "já referenciados" (13 famílias) e casos especiais de evolução (2 famílias)

### 3.1 Já referenciados (inalterado da primeira passagem)

Todas as 13 linhas da aba com evidência de "Já referenciado" foram re-verificadas contra o código-fonte real
(não apenas a evidência textual da planilha), seguindo a cadeia completa exigida:
espécie → script/tabela compilado → mapa acessível → condição alcançável → evento executável → entrega.

| Família | Referência | Cadeia verificada | Decisão |
|---|---|---|---|
| SPEAROW | `Gate_GoldenrodCity_Route35/scripts.inc:18-20` | Presente "Kenya" num portão da rota inicial, mapa trivialmente alcançável | **Obtível confirmado** após corrigir a flag |
| OMANYTE | `RuinsOfAlph_Lab/scripts.pory` (`ReceiveOmanyte`) | Revivificação do Helix Fossil; `RuinsOfAlph_Outside` tem warp direto para `RuinsOfAlph_Lab` | **Obtível confirmado** |
| ANORITH | `RuinsOfAlph_Lab/scripts.pory` (`ReceiveAnorith`) | Idem, Claw Fossil | **Obtível confirmado** |
| SHUCKLE | `CianwoodHouse3/scripts.inc:30` | Presente "Shuckie"; `CianwoodCity` tem warp direto para `CianwoodHouse3` | **Obtível confirmado** |
| SPINDA | `Route25_BillsHouse/scripts.inc:144` | Presente do avô do Bill; `Route25` tem warp direto para a casa | **Obtível confirmado** |
| SENTRET, REMORAID, LOTAD, SEEDOT, CASTFORM, CLAMPERL, RELICANTH | pools do Gacha (`src/game_corner_gacha.c`) | Confirmado que os arrays `sGacha*Species*` são lidos por índice aleatório e consumidos por uma rotina de sorteio real (não são arrays mortos) | **Obtível confirmado** para todas |
| KECLEON | `data/scripts/kecleon.inc:74` | **Cadeia quebrada.** Só é chamado por object events em `Route119`/`Route120` (Hoenn, fora do grafo de mapas alcançáveis), e exige `ITEM_DEVON_SCOPE`, distribuído apenas em mapas igualmente inalcançáveis | **Referenciado, mas não obtível** pela cadeia original — implementado por **rota nova e independente** (§4.2) |

**Falso positivo descoberto:** a segunda evidência da planilha para CASTFORM aponta para
`SafariZoneGate_SafariZoneEntrance_EventScript_Test`, confirmado por `grep` como **nunca chamado** por
nenhum object event, sinal de mapa ou script — código de teste morto. Descartado; Castform permanece
obtível via Gacha de qualquer forma.

### 3.2 Casos com evolução parcialmente bloqueada (novo nesta passagem)

Duas famílias têm o membro-base obtível e com innate, mas uma evolução que depende de algo indisponível
**sem que isso seja um problema de innate** — não se enquadram na regra "família bloqueada por membro sem
innate" (essa regra é especificamente sobre innates ausentes), então o membro-base foi implementado e a
evolução ficou documentada como não obtível, sem tocar em evoluções, innates ou itens:

* **KARRABLAST → ESCAVALIER**: única evolução de Karrablast é `EVO_TRADE` condicionada a
  `IF_TRADE_PARTNER_SPECIES, SPECIES_SHELMET` (`gen_5_families.h:8788`). `SHELMET` tem `NumInnates = 0`
  (`Sem_innate.csv` linha 616) e permanece corretamente bloqueado — não foi habilitado nesta tarefa (regra
  explícita: não configurar innates novos). Como Shelmet nunca existirá em nenhum save, a troca é
  estruturalmente impossível single-player. **Karrablast: obtível confirmado. Escavalier: referenciado mas
  não obtível** (não é um problema de innate — `SPECIES_ESCAVALIER` tem 3 innates configurados,
  `gen_5_families.h:8809` — é a troca em si que é inviável).
* **MILCERY → ALCREMIE (63 formas)**: a mecânica `EVO_SPIN` com condições de item Sweet + direção/duração de
  giro **já está implementada** em `gen_8_families.h:4993-5183` (contrariando a suposição da primeira
  passagem de que faltaria `.evolutions`). O bloqueio real é outro: nenhum `ITEM_*_SWEET` é vendido, dado ou
  encontrado em nenhum mapa/script deste hack (`grep` não encontrou nenhuma referência fora de
  `constants/items.h`, `data/items.h` e a própria tabela de evolução). **Milcery: obtível confirmado.
  Formas de Alcremie: referenciadas mas não obtíveis** por falta de fonte dos itens Sweet — não é um
  problema de innate (Alcremie tem innates configurados) nem de evolução ausente.

Em ambos os casos, nenhuma evolução, innate ou item foi adicionado/alterado — apenas documentado o estado
real da cadeia, conforme a regra de não usar mudanças de evolução para facilitar distribuição.

---

## 4. Implementação (120 famílias)

### 4.1 Correção de bug — 13 famílias já referenciadas (flag apenas)

`SPEAROW, OMANYTE, SENTRET, SHUCKLE, REMORAID, LOTAD, SEEDOT, SPINDA, ANORITH, CASTFORM, CLAMPERL, RELICANTH`
→ `P_GEN_1/2/3_POKEMON` conforme a geração. Nenhuma tabela de encontro foi tocada — já tinham rota própria.

### 4.2 Kecleon — rota nova (flag + wild encounter)

A cadeia original (Devon Scope) permanece inacessível e **não foi consertada** (exigiria adicionar item +
object event + script, desproporcional para uma única espécie). `P_FAMILY_KECLEON` foi ligado e Kecleon
adicionado como encontro selvagem raro em `MAP_ROUTE50` (nível 50–55, substituindo 1 de 2 slots de Ninjask).

### 4.3 Fósseis Sinnoh — CRANIDOS e SHIELDON (desvio do método sugerido pela planilha)

A planilha sugeria "Restauração de fóssil" em `RUINS_OF_ALPH`. Verificado que `ITEM_SKULL_FOSSIL` e
`ITEM_ARMOR_FOSSIL` (os fósseis oficiais de Cranidos/Shieldon) **existem apenas como constantes**
(`src/data/items.h`) e não são distribuídos em nenhum mapa/script/loja deste hack — diferente dos 8 tipos de
fóssil já cabeados em `RuinsOfAlph_Lab/scripts.pory` (Root, Claw, Helix, Dome, Old Amber, Plume, Jaw, Sail).
Implementar a restauração exigiria criar um novo item coletável, o que é uma mudança de sistema maior do
que o justificável para 2 espécies. Em vez disso, mantendo a localização temática sugerida (Ruínas de Alph),
Cranidos e Shieldon foram adicionados como `rock_smash_mons` em `MAP_RUINS_OF_ALPH_OUTSIDE` (nível 30),
substituindo 1 Geodude e 1 Nosepass (ambos preservados no slot irmão da mesma tabela).

### 4.4 Onda "Alta prioridade" — 32 famílias (primeira passagem, antes do OW_GFX_COMPRESS)

| Família | Entrada | Local | Método | Nível | Slot substituído |
|---|---|---|---|---|---|
| SMEARGLE | Smeargle | Route 34 | selvagem | 12–14 | 1× Skiddo |
| PLUSLE | Plusle | Route 38 | selvagem | 21–23 | 1× Buneary |
| TAILLOW | Taillow | Route 38 | selvagem | 21–23 | 1× Swablu |
| MINUN | Minun | Route 43 | selvagem | 25–27 | 1× Flaaffy |
| SKITTY | Skitty | Route 43 | selvagem | 25–27 | 1× Murkrow |
| ZANGOOSE | Zangoose | Route 47 | selvagem | 33–50 | 1× Scrafty |
| SEVIPER | Seviper | Route 48 | selvagem | 30–32 | 1× Gloom |
| LUNATONE | Lunatone | Burned Tower B1F | selvagem | 19–21 | 1× Koffing |
| SOLROCK | Solrock | Foggy Forest | selvagem | 28–35 | 1× Murkrow |
| PARAS | Paras | Route 30 | selvagem | 3–4 | 1× Weedle |
| VENONAT | Venonat | Route 31 | selvagem | 5 | 1× Caterpie |
| PSYDUCK | Psyduck | Route 40 | pesca | 10 | 1× Finneon |
| DODUO | Doduo | Route 46 | selvagem | 2–3 | 1× Geodude |
| DROWZEE | Drowzee | Sprout Tower 2F | selvagem | 3–6 | 1× Rattata |
| KRABBY | Krabby | Route 41 | pesca | 10 | 1× Shellder |
| GOLDEEN | Goldeen | Whirl Islands 1F | pesca | 10 | 1× Skrelp |
| JYNX | Jynx | Ice Path 1F (dia) | selvagem | 32–40 | 1× Sneasel |
| LEDYBA | Ledyba | Ilex Forest | selvagem | 11–15 | 1× Oddish |
| SUNKERN | Sunkern | National Park | selvagem | 13–14 | 1× Nincada |
| PINECO | Pineco | Route 36 (dia) | selvagem | 6–7 | 1× Mankey |
| SNUBBULL | Snubbull | Route 33 | selvagem | 10–13 | 1× Ekans |
| SLUGMA | Slugma | Burned Tower 1F | selvagem | 18–21 | 1× Numel |
| POOCHYENA | Poochyena | Route 35 | selvagem | 14–17 | 1× Jigglypuff |
| SURSKIT | Surskit | Foggy Shore | surf | 15–24 | 1× Shellos-West |
| VOLBEAT/ILLUMISE | Volbeat + Illumise | Kitakami Border | selvagem | 42–48 | 1× Audino, 1× Sinistea |
| GULPIN | Gulpin | Route 44 | selvagem | 32–40 | 1× Lickitung |
| WAILMER | Wailmer | Route 33 South | surf | 30–35 | 1× Finizen |
| SPOINK | Spoink | Sprout Tower 3F | selvagem | 3–6 | 1× Yamask |
| CORPHISH | Corphish | Olivine City | surf | 21–25 | 1× Clauncher |
| SLAKOTH | Slakoth | Route 39 | selvagem | 21–23 | 1× Aipom |
| WHISMUR | Whismur | Route 42 | selvagem | 21–26 | 1× Drifloon |
| WURMPLE | Wurmple | Route 37 | selvagem | 18–22 | 1× Espurr |

### 4.5 Segunda passagem — 73 famílias restantes (após OW_GFX_COMPRESS liberar ROM)

Metodologia idêntica à onda anterior: para cada família, mapa sugerido pela aba `Distribuicao proposta` foi
validado (mapa existe, tabela do método sugerido existe), e um slot de espécie **duplicada** dentro da mesma
tabela foi escolhido (preservando a espécie original no slot irmão) — priorizando o nível real do slot local
em vez do intervalo genérico da planilha, para respeitar a progressão da área. Em 2 casos (`MAREANIE` em
Olivine City, `TENTACOOL` em Route 41) não havia duplicata na mesma tabela; confirmado que a espécie
permanece disponível globalmente em dezenas de outros mapas antes de substituir o único slot local.
Tabela completa (73 famílias) em [`POKEMON_PRONTOS_IMPLEMENTATION_STATUS.csv`](POKEMON_PRONTOS_IMPLEMENTATION_STATUS.csv);
resumo por tema de mapa:

* **Railway Cave (1F/2F/3F)** — tema elétrico/industrial reforçado: TOGEDEMARU, TADBULB, MORPEKO, YAMPER,
  VAROOM, PINCURCHIN, ORTHWORM, substituindo cópias de Tynamo/Stunfisk/Charjabug/Magnemite/Diglett-Alola/Pikachu.
  MORPEKO foi realocado da sugestão original (`BATTLE_FACTORY_GROUNDS`, que só tem `water_mons`/`fishing_mons`
  — incompatível com um roedor terrestre) para Railway Cave, mantendo o tema elétrico.
* **Rotas 29–50** — famílias de baixo/médio nível preenchendo rotas já existentes sem alterar a progressão
  local (BIDOOF, KRICKETOT, COMBEE, GLAMEOW, STUNKY, CHATOT, CROAGUNK, PIKIPEK, YUNGOOS, CUFANT, BOMBIRDIER,
  FOMANTIS, RELLOR, MORELULL, NICKIT, STUFFUL, BOUNSWEET, COMFEY, PASSIMIAN, DRACOZOLT, SKWOVET, WOOLOO,
  CLOBBOPUS, LECHONK, TAROUNTULA, NYMBLE, FIDOUGH, SMOLIV, SQUAWKABILLY, MASCHIFF, SHROODLE, KLAWF, entre outras).
* **Cavernas (Union Cave, Mt. Mortar, Cliff Edge Cave)** — MUDBRAY, ROLYCOLY, STONJOURNER, TURTONATOR, KLAWF,
  TOEDSCOOL.
* **Torres/ruínas** — BRONZOR (Tin Tower), SALANDIT/GREAVARD (Burned Tower B1F), HATENNA/BRAMBLIN (Sprout Tower).
* **Água/pesca/surf** — LUVDISC, VELUZA, WISHIWASHI, DEWPIDER, BRUXISH, CHEWTLE, CRAMORANT, ARROKUDA,
  DRACOVISH, ARCTOVISH, WIGLETT.
* **Gelo (Ice Path, Snowtop Mountain)** — SNOM, EISCUE, ARCTOZOLT, CETODDLE.
* **Pós-game (Cerulean Cave, Vajra Pyramid)** — SANDYGAST (58–69), ORANGURU (58–60), níveis altos mantidos
  consistentes com o restante das tabelas desses mapas.
* **Casos com evolução parcialmente bloqueada** — KARRABLAST, MILCERY (ver §3.2).

---

## 5. Removido do escopo / bloqueado

* **TYPE_NULL/SILVALLY** (18 formas) — **removido do escopo por ser sublendário**, apesar de estar listado
  em "Prontos para inserir" (ver achado em §2). `P_FAMILY_TYPE_NULL` permanece `FALSE`.
* **BURMY/WORMADAM** — todas as linhas têm innates, **exceto Mothim** (evolução macho), na aba
  `Sem innate`. Família inteira não implementada, conforme a regra de família completa.

---

## 6. Comparação antes/depois

| | Antes (commit `692c07cd`) | Depois |
|---|---|---|
| Famílias `P_FAMILY_*` habilitadas nesta tarefa | 0 | **120** |
| Espécies obtíveis perdidas em `wild_encounters.json` | — | **0** — verificado programaticamente: todo o conjunto de espécies presente antes é subconjunto do conjunto depois (`antes − depois = ∅`) |
| Total de espécies distintas em `wild_encounters.json` | 427 | 536 (+109) |
| Novas entradas espécie/forma introduzidas | — | 109 substituições de slot (34 na primeira onda + 73 na segunda + 2 fósseis) + 13 correções de flag sem tocar tabela |
| Formas afetadas | — | Castform (4 formas por clima, mecânica existente), Alcremie/Wishiwashi/Cramorant/Eiscue/Morpeko/Squawkabilly (formas cosméticas/de batalha existentes, base colocada no slot selvagem) |

---

## 7. Alterações por arquivo

| Arquivo | Alteração |
|---|---|
| `include/config/species_enabled.h` | 120 linhas `#define P_FAMILY_X FALSE → P_GEN_N_POKEMON` (13 correções de bug + Kecleon + 32 + 73 famílias + Cranidos + Shieldon). `TYPE_NULL` foi propositalmente deixado/revertido para `FALSE`. |
| `src/data/wild_encounters.json` | 109 substituições pontuais de `"species"` em slots (34 na primeira onda + 73 na segunda + 2 fósseis), preservando `min_level`/`max_level` originais; espécie substituída sempre preservada em outro slot (mesma tabela ou, em 2 casos confirmados, em outro mapa). |
| `include/config/overworld.h` | **Não alterado por mim.** `OW_GFX_COMPRESS` foi ligado pelo usuário fora desta tarefa; aproveitado apenas como pré-condição que tornou o restante da implementação cabível no ROM. |
| `docs/POKEMON_PRONTOS_IMPLEMENTATION_STATUS.csv` | Reescrito com o status final das 122 famílias. |
| `docs/POKEMON_PRONTOS_IMPLEMENTATION_REPORT.md` (este arquivo) | Reescrito para refletir a conclusão da tarefa. |

Nenhum outro arquivo foi tocado. `src/data/wild_encounters.h` é gerado automaticamente pelo build e não é versionado.

---

## 8. Validação

| Comando | Resultado |
|---|---|
| `python3 -m json.tool src/data/wild_encounters.json` | ✅ JSON válido, em ambas as passagens |
| `python3 tools/wild_encounters/wild_encounters_to_header.py` | ✅ gera header sem erro |
| `make -j$(nproc)` (13 famílias, primeira passagem) | ✅ ROM 32.475.820 B (96,79 %) |
| `make -j$(nproc)` (todas as 121, teste antes do OW_GFX_COMPRESS) | ❌ `region 'ROM' overflowed by 2136468 bytes` |
| `make -j$(nproc)` (13+32, entrega parcial da primeira passagem) | ✅ ROM 33.394.520 B (99,52 %) |
| `make -j$(nproc)` (13+32, após `OW_GFX_COMPRESS`, antes da segunda onda) | ✅ ROM 30.244.312 B (90,14 %) — confirma os ~3,15 MB liberados |
| `make -j$(nproc)` (todas as 76 famílias então restantes, teste de orçamento) | ✅ ROM 32.186.684 B (95,92 %) — coube de primeira, sem precisar de bisecção |
| `make -j$(nproc)` (build final, 120 famílias, `TYPE_NULL` revertido) | ✅ **0 erros, 0 warnings**, ROM 32.153.900 B (95,83 %), EWRAM 255.556 B (97,49 %, inalterado desde antes — não escala com nº de espécies), `Soulgold.gba` gerado (33.554.432 bytes) |
| Regressão de espécies em `wild_encounters.json` (script Python: `antes − depois`) | ✅ conjunto vazio — 0 espécies perdidas, em ambas as passagens |
| `git diff --stat` | ✅ apenas os 2 arquivos de código pretendidos (mais `overworld.h`, alterado pelo usuário) e os artefatos de doc |

**Testado em jogo: não.** Todas as validações acima são estáticas (sintaxe, geração) ou por build real do
ROM (compilação + link + geração do `.gba`). Nenhum emulador foi executado nesta sessão. Recomenda-se testar
manualmente ao menos: Kecleon em Route 50, Cranidos/Shieldon via Rock Smash nas Ruínas de Alph, e uma amostra
das famílias em cavernas/rotas para confirmar taxas de encontro, textos e sprites em jogo.

---

## 9. Pendências

1. **KARRABLAST → Escavalier**: estruturalmente inalcançável em single-player (troca exige Shelmet, que
   permanece bloqueado por não ter innate). Nenhuma ação recomendada sem violar a regra de não configurar
   innates novos — documentar como limitação conhecida.
2. **MILCERY → formas de Alcremie**: mecânica de evolução existe no motor, mas nenhum item Sweet é
   distribuído neste hack. Se desejado no futuro, adicionar uma fonte de Sweets (loja, prêmio, presente) é
   uma tarefa de escopo pequeno e independente desta.
3. **BURMY/WORMADAM**: bloqueada por Mothim sem innate; precisa de innates antes de qualquer distribuição
   (fora do escopo desta tarefa, que não configura innates).
4. **TYPE_NULL/SILVALLY**: removido do escopo por ser sublendário; recomenda-se reportar a inconsistência
   encontrada na planilha (aparece simultaneamente em "Prontos para inserir" e em "Pokemon uniques") para
   quem mantém a planilha original.
5. **Kecleon**: cadeia original (Devon Scope) continua quebrada; a rota nova (Route 50) é independente e não
   corrige o script/objeto órfão em `data/scripts/kecleon.inc`.
6. Nenhum teste em emulador foi realizado — apenas build estático real. Recomenda-se validação manual antes
   de considerar esta implementação pronta para um release.
