# Auditoria de bugs — SoulGold

Levantamento de 30/09/2026 no branch `rift-mission-v1-complete` (commit
`429d6c03db`, Berry Master parte 6). Foco pedido: flags, estados (VARs) e
possíveis travamentos. Nada do jogo foi alterado; cada arquivo `B*.md` descreve
um problema com sintoma, causa, como reproduzir e a correção sugerida.

## Bugs, por prioridade

| # | Bug | Gravidade | Chance |
|---|---|---|---|
| [B01](B01-goldenrod-congela-apos-rival-route34.md) ✅ corrigido | Goldenrod congela ao voltar se o rival da Route 34 vier antes da Whitney | **ALTA** — jogo parado | alta |
| [B02](B02-flag-garbageflag-usada-como-estado.md) ✅ corrigido | `FLAG_GARBAGEFLAG` lida como estado: Daisy só faz grooming uma vez na vida; perder para o Tentacruel da Route 41 ou vencer a Blaine a desliga; estátua de Saffron mente | **ALTA** — perda permanente no save | certa |
| [B03](B03-kurt-cena-repete-com-bolsa-cheia.md) ✅ corrigido | Casa do Kurt: com o bolso de Balls cheio, a cena de volta do poço se repete para sempre | **ALTA** — preso | baixa |
| [B04](B04-kukui-mystery-egg-cena-repete.md) ✅ corrigido | Casa do Kukui (Route 30, mapa `Route30_MrPokemonsHouse`): bolso de Key Items cheio repete a cena inteira (com a batalha) | média | muito baixa |
| [B05](B05-laboratorio-de-fosseis.md) ✅ corrigido | Laboratório de fósseis não aceita Claw Fossil (Anorith sem fonte no jogo); fóssil é consumido antes do `givemon` | média | certa / baixa |
| [B06](B06-script-termina-sem-release.md) ✅ corrigido | Scripts que terminam sem `release`: Chansey de 26 Centros, Gramps de Pewter, fazendeiro da Route 39, 7 NPCs com bolsa cheia | baixa/média — glitch visual | alta (Chansey) |
| [B07](B07-warps-e-gatilhos-mortos.md) ✅ corrigido | Warp Route 22 → ReceptionGate com id inexistente; gatilhos que nunca disparam (Ice Path, sábios de Ecruteak); cena da Mt. Moon presa à var-lixo | baixa/média | — |
| [B08](B08-flags-pendentes-e-limites.md) | Pendências da auditoria de flags de 24/09; mapas com objetos acima do limite de 16 | baixa | — |

Ordem sugerida de correção: B01 → B02 → B06 (Chansey) → B03 → B05 → resto.
B01 e B03 são do tipo que só aparece jogando numa ordem diferente da testada,
então valem teste no mGBA nos estados "antes" e "depois" do evento.

## O que foi verificado e está limpo

- **Catálogo de flags:** regenerado à parte e comparado com o do `HEAD` —
  nenhuma flag mudou de valor ou status, nenhuma fora do array de save.
- **Scripts imediatos** (ON_LOAD, ON_TRANSITION, ON_RESUME, ON_RETURN_TO_FIELD,
  ON_WARP_INTO, coord event com var 0): 325 varridos, nenhum com comando que
  espera frame. (Espera ali congela o jogo de vez: `RunScriptImmediately` gira
  num `while`.)
- **Laços infinitos em script** (sem nenhum comando que devolva o controle):
  nenhum em código vivo. Os 5 que o analisador aponta são laços de link cable
  do Emerald, falso positivo.
- **Laços em C nos módulos do SoulGold** (`nexus.c`, `berry_garden.c`,
  `hidden_grotto.c`, `game_corner_gacha.c`, `derby.c`, `trainer_moves.c`,
  `battle_boss.c`, `achievements.c`): todos com limite ou fallback. Revisão só
  de laços, não de lógica completa.
- **`B_FLAG_NO_CATCHING` depois de blackout:** limpa pela engine
  (`B_RESET_FLAGS_VARS_AFTER_WHITEOUT`). Não fica presa.
- **Líderes repetidos no `SaffronCity_FightingDojoVIP`:** usam
  `trainerbattle_no_intro`, que não consulta a flag de derrota. Sem conflito.
- **`VAR_STARTER_MON`:** só assume 0/1/2 (`src/ui_birch_case.c:139-149`), então
  as cenas de rival com três ramos cobrem tudo.

## Três fatos da engine que decidiram a gravidade

1. **`lock` sem `release` não trava.** O jogador segue andando (held movement
   ignora `frozen`), só sem animação, e os NPCs ficam parados até trocar de
   mapa. Por isso B06 é glitch, não travamento.
2. **`return` com pilha vazia só encerra o script** (`ScriptPop` devolve `NULL`,
   `RunScriptCommand` para). Por isso `goto` para `Common_EventScript_BagIsFull`
   não crasha — mas termina sem `release`.
3. **Gatilho de frame cuja condição não muda é livelock:** `PlayerStep` só roda
   nos frames em que nenhum script de frame foi enfileirado. B01, B03 e B04 são
   este caso.

## Ferramenta

`bug/auditar_scripts.py` refaz a varredura (precisa de um build feito, porque
lê `build/emerald/data/event_scripts.filtered.s` para saber o que está na ROM):

```bash
python3 bug/auditar_scripts.py              # tudo
python3 bug/auditar_scripts.py --so TRAVA_FRAME
```

Ela só olha código alcançável: parte dos mapas ligados ao mundo
(`map_graph.py`) e das labels citadas em `src/*.c`, e segue
`goto`/`call`/desvios/ponteiros. Categorias e o quanto confiar em cada uma:

| Categoria | O que acusa | Ruído |
|---|---|---|
| `TRAVA_FRAME` | alvo de `map_script_2` com caminho que termina sem mudar a var da condição | baixo — origem de B01, B03, B04 |
| `TRAVA_IMEDIATO` | espera dentro de script imediato | baixo |
| `TRAVA_LACO` | laço sem espera e sem mudança de estado | médio (não expande `call`) |
| `WARP` | destino fora da ROM, warp id inexistente, x,y fora do layout | baixo |
| `VAR_ESTADO` | var comparada com valor que nenhum script escreve | médio (`VAR_ITEM_ID` e afins são escritas em C) |
| `OBJ_ID` | `applymovement`/`removeobject`/... com local id de outro mapa | baixo |
| `REMOVE_FLAG` | `removeobject` em objeto cuja flag é de progresso | alto — quase sempre intencional |
| `CALL_END` | `call` para rotina que termina em `end` | médio |
| `TRAVA_LOCK` / `_POSSIVEL` | `end` com lock ativo | alto — ver B06 |
| `TRAINER_DUP` | mesmo `TRAINER_*` em dois mapas | informativo |
| `FALLTHROUGH` | rotina que cai na label seguinte sem desvio | alto — informativo |

## Fora do escopo desta passada

- Testes automatizados (`make check`) não foram rodados.
- Nada foi testado no emulador; B01–B04 são deduzidos do código e da engine.
- Lógica de batalha e C da engine herdada do expansion não foram revisados.

## Listas do analisador já revisadas à mão (30/09/2026)

| Categoria | Resultado |
|---|---|
| `TRAVA_LOCK` | 42 pontos únicos: 17 reais (corrigidos, ver B06) e 25 falsos positivos. Os 63 achados que sobram na saída são esses falsos positivos |
| `CALL_END` | 23, nenhum bug: todos são "abortar" de propósito (PC cheio no Safari, reset do quebra-cabeça do Heatran, estado inválido no debug, link cable no Battle Arcade) ou o chamador terminaria logo em seguida |
| `REMOVE_FLAG` | 32, todos intencionais (a mesma flag é setada na mesma cena). O analisador agora ignora esse padrão e não acusa mais nenhum |
| `TRAVA_FRAME` | os 9 restantes: Kukui (só se a checagem de espaço falhar, inalcançável), laboratório do Elm (sim/não exaustivo) e o resto Battle Frontier/Battle Arcade original |
| `VAR_ESTADO` | 34 → 0. `VAR_ITEM_ID` é o `gSpecialVar_ItemId` escrito pelo C (analisador corrigido); código morto dos fósseis apagado do laboratório; Route 32: os 3 gatilhos do careca com `VAR_VIOLET_CITY_STATE == 2` (valor que nada escreve) passaram a 3, o único estado que não era coberto |
| `FALLTHROUGH` | 206, nenhum bug na queda em si: 190 caem na continuação de um `if` do poryscript, 15 são seções em sequência (teatro de Ecruteak, batalhas duplas do Rocket Hideout), 1 é o gatilho duplo do Ilex. Lendo os trechos achei **três bugs vizinhos**, todos por comando comentado (ver abaixo) |
| `TRAVA_WAITSTATE` (nova) | `waitstate` sem nada antes que retome o script = jogo parado de vez. Achou o sandpit (corrigido). O único restante (`MoveTutor_AfterChooseBoxMon`) é retomado pelo C |

### Bugs por comando comentado (30/09/2026)

- **Swinub e Delibird do Ice Path B3F, Pidgeotto da Route 14:** o
  `chooseitem BERRIES_POCKET` estava comentado, então o `removeitem VAR_ITEM_ID`
  tirava da bolsa **o último item que o jogador usou ou escolheu**, qualquer que
  fosse. Agora abre o bolso de Berries; cancelar não custa nada e só a Berry
  certa (Aspear / Qualot) é consumida.
- **Ability Expert do Fighting Dojo:** ver B06.
- **Sandpit (`data/scripts/sandpit.inc`):** com o `warphole` comentado (o mapa
  de destino não existe) sobrava um `waitstate` sem retorno: pisar numa areia
  movediça deixaria o jogador invisível e congelado para sempre. Nenhum tileset
  tem esse tile hoje, então era armadilha latente; agora o jogador volta a
  aparecer e é liberado.
