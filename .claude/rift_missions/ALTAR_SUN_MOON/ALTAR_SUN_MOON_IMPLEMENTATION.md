# Altar do Sol e da Lua — Ultra Necrozma — plano de implementação

**Status:** **IMPLEMENTADO E TESTADO — revisão 4** (25/09/2026). O autor jogou o
evento inteiro e voltou com **cinco itens**; os cinco estão corrigidos e estão em
**§18**. Dois deles eram travamento de jogo, e o do mapa do Pokégear era um
**estouro de buffer em cima de um ponteiro de função** — build limpo, crash
garantido. A revisão 3 é o retorno da implementação: nove correções ao plano,
todas em **§17**, e sete delas são coisas que compilariam limpo e quebrariam no
jogo.
A revisão 2 (23/09) tinha aplicado o retorno do autor: a Anabel **não** é loja
(ela aponta para o Kurt), Fly para o altar **entra** no escopo, a Nihilego está
aprovada, o Looker cura desde o estado 13, e o motivo de a Anabel não lutar
passou a ser **diegético**. O sistema de bolas do Kurt que esse retorno abriu é
**outro documento** — [`KURT_BALL_CRAFT_DESIGN.md`](../../KURT_BALL_CRAFT_DESIGN.md),
implementado na mesma passada — e o §10.3 aqui só depende dele por uma caixa de
texto.

> **Se você vai mexer neste evento, leia o §18 e o §17, nessa ordem, antes do
> §14.** O §14 é a auditoria de antes de escrever; o §17 é o que a escrita
> descobriu (inclui **duas correções de tile/flag que o plano errava** e a
> colisão de daily flags entre este documento e o do Kurt); o §18 é o que o
> **jogo rodando** descobriu, e é o único dos três que fala de coisas que
> travam o console.
**Modo:** **história completa desde a primeira passada**, não esqueleto. O
autor pediu "uma história épica" e o terreno já está pronto (mapa, tileset com
estado de portal, navio, arena, sprites), então não existe motivo para gastar
uma rodada de placeholder. As regras de esqueleto (skill `evento-esqueleto`)
continuam valendo **inteiras** para estado, visibilidade, gatilhos e resultados
de batalha: o que muda é que as falas já nascem finais.
**Roteiro da cena (falas e movimentos):** [`ALTAR_SUN_MOON_SCRIPT.md`](ALTAR_SUN_MOON_SCRIPT.md)
**Design de referência:** [`SOULGOLD_RIFT_MISSIONS_DESIGN.md`](../SOULGOLD_RIFT_MISSIONS_DESIGN.md)
§3.1 (voz), §3.3 (regras de escrita), §7 (o que a reunião entregou), §8 (o altar
único), §9 (Lusamine e Ultra Necrozma), §10 (o loop pós-Necrozma) e §11
(continuidade) — revisão **V24**, que este plano escreveu junto.
**Documento anterior:** [`PRE_NECROZMA_ULTRABEAST_IMPLEMENTATION.md`](../PRE_NECROZMA_ULTRABEAST/PRE_NECROZMA_ULTRABEAST_IMPLEMENTATION.md),
que terminou em `VAR_RIFT_MISSIONS_STATE = 12` + `FLAG_EVENT_NECROZMA_ALTAR_UNLOCKED`.
Este documento **continua** aquela máquina de estados (12 → 16) e é o **último**
evento de história do arco: o que vem depois dele é loop.

> **Leia o §14 antes de escrever a primeira linha.** Ele é a auditoria do que já
> existe no repositório para este evento, e três dos achados são bugs vivos hoje
> (o nome do mapa aparece como "Abandoned Lab", o texto do altar usa o prefixo
> `"LUSAMINE: "` que a V17 aboliu, e a arena devolve o jogador em cima de onde o
> portal vai ficar).

---

## 1. Escopo — as decisões do autor, traduzidas

O briefing do autor, item por item, e o que cada um virou aqui:

| Pedido | Como ficou |
|---|---|
| "Já está tudo bem setado, monta uma história épica" | Cinco atos num mapa e meio, com o elenco inteiro. Nada de placeholder: as falas do §5 ao §10 são as finais. |
| "Envolve o Solgaleo nas cutscenes e coloca ele no mapa" | O parceiro do jogador é um **objeto de overworld** (`OBJ_EVENT_GFX_SPECIES(SOLGALEO)` / `(LUNALA)`) no Ato III, no Ato IV e no Ato V. Ele é quem estabiliza a passagem e quem a harmoniza no fim. |
| "Tem que ficar claro que o mapa está instável, e o único jeito de entrar é com o Solgaleo" | Três camadas: `setweather WEATHER_VOLCANIC_ASH` enquanto o estado é 13-15; o **disco do altar vira portal** por `setmetatile` (os metatiles já existem no tileset, §4.3); e a entrada na fenda é guardada por `checkspecies` dos dois lendários, com fala própria e repetível. |
| "A Lusamine deve se oferecer por arrependimentos do passado" | Ato I, e é o argumento **dela**, não um pedido de desculpas: quem atravessa é quem já gastou os filhos de outras pessoas na própria curiosidade uma vez. |
| "Gladion e Lillie devem ficar contra" | Ato I, cada um do seu jeito — a Lillie argumenta, o Gladion recusa. E é a Lillie que fecha a discussão no Ato II, nos dois resultados da batalha. |
| "A cena para aí e o player é liberado; conversa com a Lusamine, sim/não, o não só não avança" | Estado **13**. A cutscene de chegada termina com `releaseall` e o jogador anda pelo altar. A batalha é um `MSGBOX_YESNO` no script de objeto dela; `NO` não muda estado nenhum e é repetível. |
| "Jogador vence, o portal se mostra mais instável" | Estado **14**: o disco troca de metatile, a fenda de chão nasce em (14,10), a câmera treme e a trilha muda. |
| "Aparece um portal perto ali no meio do Altar (a gente vai reusar isso)" | **Um único objeto** `LOCALID_SUN_MOON_ALTAR_RIFT` em (14,10), `OBJ_EVENT_GFX_PORTAL`. O mesmo objeto serve o Ato IV **e** o loop diário do pós-game; só o script dele muda de ramo pelo estado. |
| "Entra você lá dentro e luta com o Ultra Necrozma, e a Anabel te acompanha" | `MAP_ULTRA_SPACE_ARENA` (já existe, hoje sem objeto nenhum). A Anabel é um objeto que anda com o jogador na coreografia — **não** é parceira de batalha (§15, risco 1: o sistema de follower NPC está desligado no projeto). |
| "Você derrota ela numa boss battle beem difícil" | 5 barras / Lv 90 / 160% / perfil de fases novo `BOSS_PHASE_PROFILE_NECROZMA`, que **descasca** a criatura: Ultra, Ultra, Ultra, Necrozma, Necrozma. Escala do arco: M1 3/120, M2 4/130, M3 4/140, M4 4/150, aqui 5/160. |
| "Você captura ele como parte da Cutscene e o Solgaleo meio que harmoniza os portais" | `B_FLAG_NO_CATCHING` **durante** a luta (a luta é uma luta, não uma loteria de bola) e `givemon SPECIES_NECROZMA` **na cutscene** depois da vitória, com a checagem de espaço da skill `entregar-pokemon-ou-ovo` feita **antes** de entrar na fenda. Resolve de passagem a pendência aberta do design §9 ("não está definido se a captura ocorre durante o combate ou em etapa posterior"). |
| "Depois da luta, uma conversa de todo mundo encerrando o evento" | Ato V, no altar, estado 15 → 16. |
| "Deixa o mapa feliz de novo, mas com o portal aparecendo 1x por dia" | Estado 16: `WEATHER_NONE`, disco de volta ao sol/lua, e a fenda visível **só** enquanto `FLAG_DAILY_ALTAR_RIFT` estiver limpa. |
| ~~"A Anabel pode vender Beast Ball"~~ → **revisão 2: ela não vende nada** | A Anabel **não é loja**. Ela conta que a Beast Ball existe porque **ela pediu ao Kurt que a fizesse**, e manda o jogador a Azalea. A pendência "Beast Balls: preço, estoque" do design §14 sai deste documento e vira o sistema de receitas do Kurt ([`KURT_BALL_CRAFT_DESIGN.md`](../../KURT_BALL_CRAFT_DESIGN.md)). O único custo aqui é **uma caixa de fala** dela no Ato IV e **duas** no estado 16. |
| "Lusamine, Gladion e Lillie algumas vezes no quarto de Olivine" | Escala de dias da semana (§10.4). |
| "Kukui volta pro laboratório e de vez em quando aparece na praia de Cherrygrove (rematch)" | Idem, na praia da Missão 3. |
| "Lillie também de vez em quando na praia com o Kukui (rematch)" | Mesmos dias que o Kukui — eles aparecem **juntos**, o que é o que a fala dela precisa para funcionar. |
| "Gladion de vez em quando em Cianwood (rematch)" | Idem, no tile da despedida dele (§4.7 do design). |
| "Lusamine de vez em quando no Altar (rematch)" | Idem, em (14,9), de frente para o disco. |
| "Looker e Anabel ficam no Altar permanentemente, tomando conta dos resquícios" | Eles **saem de `OlivineCity_House1`**. Isso exige mudar o campo `flag` dos dois de `"0"` para uma temporária recalculada — ver §14, achado 4: o doc anterior proibia `removeobject` neles exatamente por isso. |
| "Um portal aparece ali 1x por dia que te deixa fazer as Rift Missions; por enquanto você só entra e não tem nada lá dentro" | A fenda diária leva a `MAP_ULTRA_SPACE_ARENA` vazia, e o gatilho sul que já existe lá devolve o jogador ao altar. O loop de cinco treinadores + lendário (design §10) é o **documento seguinte**. |

**Fora de escopo, explicitamente:**

- **O conteúdo do loop** (pools de treinadores, lendários, sorteio). A fenda
  diária abre, entra e volta. É o gancho para o doc seguinte, do mesmo jeito que
  a reunião foi o gancho para este.
- **O sistema de receitas do Kurt.** Toda a economia de Poké Balls que o retorno
  do autor abriu (lojas vendendo só Poké Ball, o Kurt como única fonte das outras,
  10 níveis de EXP, N por dia) é **documento próprio**:
  [`KURT_BALL_CRAFT_DESIGN.md`](../../KURT_BALL_CRAFT_DESIGN.md). Este evento só
  **aponta** para lá, em três caixas de fala da Anabel.
- **Mudar o desenho do mapa.** O `map.bin` do altar foi retocado à mão pelo
  autor no Porymap (106 de 195 células do carimbo original continuam idênticas,
  o resto é dele). Este plano **não toca em `data/layouts/SunMoonAltar/map.bin`**
  — só em metatiles individuais por `setmetatile`, em tempo de execução.

---

## 2. Resumo do fluxo

```text
estado 12 + FLAG_EVENT_NECROZMA_ALTAR_UNLOCKED      (fim do PRE-NECROZMA)
  └─ navio em OlivineCity_PortInside ──▶ warp MAP_SUN_MOON_ALTAR (14,27), o cais
       └─ o jogador sobe a ilha a pe; o elenco inteiro ja esta no patio
       └─ coord_event na escada (12..16, 15)
            ▶ ATO I - CHEGADA  (uma vez)
              o disco esta girando; o instrumento do Kukui esta morto
              Anabel: nao esta abrindo - esta aberto, e faz tempo
              o disco VIRA PORTAL (setmetatile) + cinzas (setweather) + tremor
              Lusamine se oferece para atravessar sozinha
              Lillie argumenta / Gladion recusa
              Looker: isto nao e decisao de policia
                 └─ setvar 13 ▶ releaseall   (o jogador fica solto no altar)

estado 13   falar com a Lusamine ▶ SIM/NAO
              NAO ▶ uma caixa, nada muda, repetivel
              SIM ▶ ATO II - O DUELO   (B_FLAG_NO_WHITEOUT, 4 resultados)
                     vitoria e derrota resolvem a disputa; a Lillie fecha
                       └─ ATO III - A FENDA ABRE
                          addobject SOLGALEO ou LUNALA ao lado do disco
                          addobject RIFT em (14,10)
                          setvar 14 ▶ warpsilent no lugar

estado 14   falar com a fenda ▶ checagem de espaco (regra da Anabel)
                             ▶ checkspecies SOLGALEO / LUNALA
                                  falta ▶ uma caixa, repetivel, nada muda
                                  tem   ▶ SIM/NAO ▶ warp MAP_ULTRA_SPACE_ARENA (10,19)
              └─ ATO IV - A ARENA
                 a Anabel e o parceiro entram com o jogador
                 coord_event (9..11, 12) ▶ a criatura, faminta
                 o parceiro se poe na frente ▶ ela toma a luz ▶ forma Ultra
                 BOSS 5 barras / Lv 90 / 160% / BOSS_PHASE_PROFILE_NECROZMA
                    perdeu/desistiu ▶ blackout ▶ retry de graca (estado segue 14)
                    venceu ▶ a armadura cai ▶ givemon SPECIES_NECROZMA
                             o parceiro harmoniza a passagem
                             setvar 15 ▶ warp MAP_SUN_MOON_ALTAR (14,11)

estado 15   coord_event de volta ao patio ▶ ATO V - A DESPEDIDA
              conversa de encerramento com os sete
              Looker e Anabel ficam; os outros vao embora
                 └─ setvar 16 ▶ warpsilent no lugar

estado 16   PERMANENTE
              altar: WEATHER_NONE, disco de volta ao sol/lua
              Looker (13,13) e Anabel (15,13) moram aqui; Anabel vende Beast Ball
              fenda em (14,10) visivel enquanto FLAG_DAILY_ALTAR_RIFT esta limpa
                 └─ entra ▶ MAP_ULTRA_SPACE_ARENA vazia ▶ volta pelo gatilho sul
                    (o conteudo do loop e o DOCUMENTO SEGUINTE)
              OlivineCity_House1: Looker e Anabel saem; a familia aparece por dia
              Cherrygrove (praia): Kukui + Lillie por dia, rematch diario
              Cianwood: Gladion por dia, rematch diario
              Altar: Lusamine por dia, rematch diario
```

---

## 3. Estado — contrato

### 3.1 Constantes novas

Nenhuma **var** nova e **nenhuma flag persistente nova**. Isto não é economia
por esporte: toda visibilidade deste evento é de **um mapa só** e derivável de
`VAR_RIFT_MISSIONS_STATE`, que é exatamente o caso da skill
`visibilidade-e-gatilhos` §6 (`FLAG_TEMP_*` como cache, recalculada no
`ON_TRANSITION`). É o primeiro evento do arco que não gasta flag persistente
nenhuma, e a razão é que ele não tem "incidente ativo" que precise ser lido de
outra cidade.

**Daily flags** (`DAILY_FLAGS_START`, limpas por `ClearDailyFlags()`,
`src/event_data.c:71`, chamado de `src/clock.c:56`). Cinco, todas em slots hoje
marcados `FLAG_UNUSED_*`, conferidos livres em 23/09/2026:

| Constante | Valor | Papel |
|---|---|---|
| `FLAG_DAILY_ALTAR_RIFT` | `DAILY_FLAGS_START + 0x29` (era `FLAG_UNUSED_0x949`) | A fenda do pós-game já foi usada hoje. Setada ao entrar nela; enquanto setada, o objeto da fenda fica escondido. |
| `FLAG_DAILY_REMATCH_LUSAMINE` | `+ 0x2A` | Revanche dela no altar, uma por dia |
| `FLAG_DAILY_REMATCH_KUKUI` | `+ 0x2B` | Revanche dele na praia de Cherrygrove |
| `FLAG_DAILY_REMATCH_LILLIE` | `+ 0x2C` | Revanche dela na praia de Cherrygrove |
| `FLAG_DAILY_REMATCH_GLADION` | `+ 0x2D` | Revanche dele em Cianwood |

Os cinco substituem `FLAG_UNUSED_0x949` a `FLAG_UNUSED_0x94D` **no lugar**, sem
mexer em `DAILY_FLAGS_END` nem em `FLAGS_COUNT` (o bloco vai até `+ 0x3F` e já
está dimensionado). Nada de `CUSTOM_FLAGS_END`: essas flags não moram lá.

> **Por que o rematch é diário e não "sempre".** O design §10 quer o loop
> infinito; isso vale para as expedições, não para revanche de personagem. Uma
> luta de história repetível sem limite transforma a Lusamine em máquina de
> experiência. Uma por dia é a dose que o próprio repositório já usa para o
> Silver (`FLAG_DAILY_BEAT_SILVER`) e para os oito treinadores do Battle Cafe.

**Local ids novos.** `include/constants/map_event_ids.h` é **gerado** a partir
da posição (1-based) de cada objeto no `map.json`; editar à mão no estilo
alfabético existente e deixar a `make` confirmar (skill `batalha-sem-blackout`,
bloco do `mapjson`). Objetos novos **sempre no fim** de `object_events`.

| Constante | Mapa | Valor |
|---|---|---|
| `LOCALID_SUN_MOON_ALTAR_RIFT` | `MAP_SUN_MOON_ALTAR` | 11 |
| `LOCALID_SUN_MOON_ALTAR_SOLGALEO` | idem | 12 |
| `LOCALID_SUN_MOON_ALTAR_LUNALA` | idem | 13 |
| `LOCALID_ULTRA_SPACE_ARENA_ANABEL` | `MAP_ULTRA_SPACE_ARENA` | 1 |
| `LOCALID_ULTRA_SPACE_ARENA_NECROZMA` | idem | 2 |
| `LOCALID_ULTRA_SPACE_ARENA_ULTRA` | idem | 3 |
| `LOCALID_ULTRA_SPACE_ARENA_SOLGALEO` | idem | 4 |
| `LOCALID_ULTRA_SPACE_ARENA_LUNALA` | idem | 5 |
| `LOCALID_CHERRYGROVE_POST_KUKUI` | `MAP_CHERRYGROVE_CITY` | fim do array |
| `LOCALID_CHERRYGROVE_POST_LILLIE` | idem | fim do array |
| `LOCALID_CHERRYGROVE_POST_NINETALES` | idem | fim do array |
| `LOCALID_CIANWOOD_POST_GLADION` | `MAP_CIANWOOD_CITY` | fim do array |
| `LOCALID_CIANWOOD_POST_SILVALLY` | idem | fim do array |

**Treinadores.** Cinco entradas em `include/constants/opponents.h` e cinco times
em `src/data/trainers.party`:

| Constante | Id | Origem | Uso |
|---|---|---|---|
| `TRAINER_LUSAMINE` | 964 | **já existe**, e hoje é um stub nunca referenciado (um Rattata nível 5). Reaproveitar o id e **reescrever o time**. | O duelo do Ato II |
| `TRAINER_KUKUI` | 966 | **já existe**, mesmo caso (Rattata nível 5, sem referência em `data/maps/`) | Revanche diária na praia |
| `TRAINER_LUSAMINE_ALTAR` | 972 | recuperado de `TRAINER_UNUSED_108` | Revanche diária no altar |
| `TRAINER_LILLIE_POSTGAME` | 973 | recuperado de `TRAINER_UNUSED_109` | Revanche diária na praia |
| `TRAINER_GLADION_POSTGAME` | 974 | recuperado de `TRAINER_UNUSED_110` | Revanche diária em Cianwood |

Comentário obrigatório em cada um citando este documento, no padrão do
`TRAINER_GLADION_VICTORY_ROAD` (`opponents.h:952`). `TRAINER_LILLIE` (965) e
`TRAINER_GLADION` (967) **não** podem ser reaproveitados: estão em uso na Route
30 e em Violet.

**MAPSEC: nada a fazer.** Isto foi verificado e é uma boa notícia. Os três
mapas (`SunMoonAltar`, `UltraSpaceArena`, `SouthPassageEnd`) usam
`MAPSEC_ABANDONED_LAB`, e essa `MAPSEC` **já foi renomeada** neste repositório:
`src/data/region_map/region_map_entries.h:1955` diz
`.name = COMPOUND_STRING("Altar of Sun and Moon")`, com `x = 16, y = 0`. Ou
seja, a plaquinha de nome de mapa já mostra a coisa certa, e o Necrozma
recebido no `givemon` já vai nascer com "Altar of Sun and Moon" como local de
encontro. **Não criar `MAPSEC` nova** e não "consertar" o nome herdado.

**Uma flag persistente, e agora ela é obrigatória:**
`FLAG_VISITED_SUN_MOON_ALTAR` = `0x1046` (primeira livre depois de
`FLAG_EVENT_NECROZMA_ALTAR_UNLOCKED`; conferida livre em 23/09/2026 com
`grep -n "0x1046" include/constants/flags.h` → nada), movendo
`CUSTOM_FLAGS_END`. O bloco `SYSTEM_FLAGS` das `FLAG_VISITED_*` está **cheio**
(termina em `FLAG_VISITED_RECEPTION_GATE`, `SYSTEM_FLAGS + 0x27`, e `+ 0x28` já
é `FLAG_SYS_USE_FLASH`), e é por isso que `FLAG_VISITED_BATTLE_FACTORY` (`0x96A`)
e `FLAG_VISITED_ROUTE50` (`0x1026`) já moram fora dele.

**Uma `HEAL_LOCATION` nova:** `HEAL_LOCATION_SUN_MOON_ALTAR`, em
`src/data/heal_locations.json` (o `.h` e o header de constantes são gerados),
apontando para `MAP_SUN_MOON_ALTAR` em **(14,16)** — o degrau logo abaixo da
escada, de onde o jogador entra no pátio andando para o norte. Ela **não** é
ponto de renascimento: só o `setrespawn` faria isso, e este plano não usa
`setrespawn` em lugar nenhum. Ela existe porque é assim que o Fly aterrissa
(§4.7).

**Perfil de boss.** `BOSS_PHASE_PROFILE_NECROZMA` em
`include/constants/battle.h` (valor 10, e `BOSS_PHASE_PROFILE_COUNT` vai a 11) +
`sNecrozmaBossPhases`/`sNecrozmaBossProfile` em `src/battle_boss.c` e um `case`
em `GetBossPhaseProfile` (`:357`). Detalhe em §8.4.

**Música da batalha.** `BattleSetup_StartLegendaryBattle` (`src/battle_setup.c:479`)
escolhe transição e trilha por espécie num `switch`. Acrescentar um `case` para
`SPECIES_NECROZMA`, `SPECIES_NECROZMA_DUSK_MANE`, `SPECIES_NECROZMA_DAWN_WINGS`
e `SPECIES_NECROZMA_ULTRA` → `CreateBattleStartTask(B_TRANSITION_BLUR, MUS_DP_VS_DIALGA_PALKIA)`.
**Custo de ROM zero**: `SONG_MUS_DP_VS_DIALGA_PALKIA` já está ligada em
`include/config/songs_enabled.h`, assim como `MUS_DP_SPEAR_PILLAR` (trilha da
arena, já no `map.json` dela) e `MUS_DP_LEGEND_APPEARS` (trilha da ruptura, que
a V23 ligou). **Nenhuma música nova neste evento.**

### 3.2 Máquina de estados `VAR_RIFT_MISSIONS_STATE`

`VAR_RIFT_MISSIONS_STATE` = `0x4120` (`include/constants/vars.h:333`). Valores
0-3 no doc de Blackthorn; 4-6 no de Mahogany; 6-8 no de Cherrygrove; 8-10 no de
New Bark; 10-12 no do PRÉ-NECROZMA. **Nenhum deles muda.**

| Valor | Significado | Quem escreve | Quem lê |
|---|---|---|---|
| 12 | Reunião completa, navio liberado, **primeira chegada ao altar pendente** | `OlivineCity_House1_EventScript_ReunionConfirmed` (já existe) | `SunMoonAltar_OnTransition`; o `coord_event` da escada |
| 13 | Ato I encenado. **Duelo da Lusamine pendente.** O jogador está solto no altar | `SunMoonAltar_EventScript_ArrivalDone` | `SunMoonAltar_OnTransition` (cinzas + disco-portal); o script da Lusamine; os outros seis scripts de objeto |
| 14 | Duelo resolvido. **A fenda de chão está aberta**; Ultra Necrozma pendente | `SunMoonAltar_EventScript_DuelResolved` | `SunMoonAltar_OnTransition` (mostra a fenda e o parceiro); o script da fenda; `UltraSpaceArena_OnTransition` |
| 15 | Necrozma derrotada e recebida. **Ato V pendente** | `UltraSpaceArena_EventScript_NecrozmaCaught` | `SunMoonAltar_OnTransition`; o `coord_event` do pátio |
| 16 | **Arco encerrado.** Estado permanente do pós-game | `SunMoonAltar_EventScript_FarewellDone` | tudo do §10 — altar, Olivine, Cherrygrove, Cianwood, loja, fenda diária, revanches |
| 17+ | Reservado para o **loop** das Rift Missions, se ele precisar | doc seguinte | — |

**O 15 é transitório de propósito, e não é desperdício.** Ele dura os segundos
entre o warp de volta da arena e o fim do Ato V. Existe porque a captura e a
conversa final acontecem em **mapas diferentes**: sem ele, um reset entre os dois
perderia a cena de encerramento ou a repetiria. É o mesmo papel do 11 no doc
anterior.

**Invariantes:**

- `FLAG_EVENT_NECROZMA_ALTAR_UNLOCKED` setada ⇔ `VAR_RIFT_MISSIONS_STATE >= 12`.
  Continua valendo sem mudança: nenhum valor deste documento a limpa, e nenhum
  a seta de novo.
- `13 <= estado <= 15` ⇔ o altar está instável: `WEATHER_VOLCANIC_ASH` **e** as
  sete células do disco mostrando os metatiles de portal. As duas coisas são
  recalculadas no `ON_TRANSITION`, nunca persistidas.
- Estado 14 ou 15 ⇔ `LOCALID_SUN_MOON_ALTAR_RIFT` visível **incondicionalmente**.
  Estado ≥ 16 ⇔ visível **se e somente se** `FLAG_DAILY_ALTAR_RIFT` está limpa.
  Estado ≤ 13 ⇔ escondida.
- Estado ≥ 16 ⇔ Looker e Anabel **não** estão em `OlivineCity_House1` e **estão**
  em `MAP_SUN_MOON_ALTAR`. As duas metades são recalculadas em dois
  `ON_TRANSITION` diferentes, a partir da mesma var.
- Estado ≥ 16 ⇔ a Anabel vende Beast Balls. Não há flag de loja.
- As quatro invariantes de missão continuam valendo: em 12-16 nenhuma das quatro
  `FLAG_EVENT_ULTRABEAST_*` está setada.
- **O parceiro do jogador nunca fica no mapa entre cenas.** Em qualquer estado, no
  primeiro load os dois objetos de lendário estão escondidos; só o script da cena
  faz `addobject`.

**A dívida do `vars.h`.** O bloco de comentário de `VAR_RIFT_MISSIONS_STATE`
(`include/constants/vars.h:311-332`) documenta 0 a 12 e as cinco invariantes.
Estender até **16** e acrescentar as invariantes novas de visibilidade. É o único
lugar do projeto onde a máquina inteira fica visível para quem abre o header, e
já foi paga duas vezes — não deixar apodrecer de novo.

### 3.3 Temporários por mapa

Conferir antes de implementar (o comando é parte da tarefa, não sugestão):

```bash
grep -rn "FLAG_TEMP_[0-9A-F]\+\b\|VAR_TEMP_[0-9]\b" \
     data/maps/SunMoonAltar data/maps/UltraSpaceArena \
     data/maps/CherrygroveCity data/maps/CianwoodCity \
     data/maps/OlivineCity_House1 data/scripts/
```

Situação em 23/09/2026: `SunMoonAltar` e `UltraSpaceArena` **não usam
temporário nenhum** (`scripts.inc` dos dois só tem `.byte 0` no `MapScripts`).
`OlivineCity_House1` usa `FLAG_TEMP_1` (os seis da reunião) e `VAR_TEMP_1`
(trava do gatilho). `CherrygroveCity` usa `FLAG_TEMP_1`, `2`, `5` e `6` na
Missão 3. Evitar sempre `FLAG_TEMP_E`, que a engine reserva para suprimir o
follower.

| Mapa | Temp | Uso |
|---|---|---|
| `SunMoonAltar` | `FLAG_TEMP_1` | Os **cinco visitantes** e os dois parceiros: Lusamine, Lillie, Ninetales, Gladion, Silvally, Kukui. Visíveis em 12-15; em ≥ 16 só a Lusamine, e por dia da semana, então ela **sai desta flag** (ver abaixo) |
| | `FLAG_TEMP_2` | A fenda de chão (`RIFT`) |
| | `FLAG_TEMP_3` | Solgaleo |
| | `FLAG_TEMP_4` | Lunala |
| | `FLAG_TEMP_5` | A Lusamine **sozinha**, porque no estado ≥ 16 ela aparece por escala de dia enquanto os outros cinco nunca voltam |
| | `VAR_TEMP_1` | Trava uma-vez-por-visita do **gatilho de frame** (Ato V) |
| | `VAR_TEMP_0` | Condição dos cinco `coord_event` da escada (Ato I). **Tem de ser diferente da `VAR_TEMP_1`** — ver §4.6 |
| | `VAR_TEMP_2` | Resultado do duelo (`GetBattleOutcome`), copiado na hora |
| | `VAR_TEMP_3` | Estado anterior de `B_FLAG_NO_WHITEOUT` |
| | `VAR_TEMP_4` | Espécie do parceiro (`CheckMysteryEggPokemon`), para as reações e para saber qual lendário mostrar |
| `UltraSpaceArena` | `FLAG_TEMP_1` | Anabel |
| | `FLAG_TEMP_2` | Necrozma |
| | `FLAG_TEMP_3` | Ultra Necrozma |
| | `FLAG_TEMP_4` | Solgaleo |
| | `FLAG_TEMP_5` | Lunala |
| | `VAR_TEMP_1` | Trava do `coord_event` do confronto |
| | `VAR_TEMP_2` | Resultado da boss battle |
| | `VAR_TEMP_4` | Espécie do parceiro |
| `CherrygroveCity` | `FLAG_TEMP_3` | **Kukui** do pós-game (**não** reusar a `FLAG_TEMP_1` da Missão 3: os objetos são outros e a condição é outra) |
| | `FLAG_TEMP_4` | **Lillie e a Ninetales** do pós-game, em flag separada porque a escala dela não é a mesma do Kukui (§10.4) |
| `CianwoodCity` | `FLAG_TEMP_1` | Gladion e Silvally do pós-game (o mapa não usa `FLAG_TEMP_*` hoje) |
| `OlivineCity_House1` | `FLAG_TEMP_1` | **Passa a servir dois elencos**: os seis da reunião em 10-11 e a família em ≥ 16. O Kukui **sai** dela |
| | `FLAG_TEMP_2` | Looker e Anabel — **novo**, e é a mudança mais delicada deste plano (§14, achado 4) |
| | `FLAG_TEMP_3` | Kukui, separado, porque no pós-game ele está em Alola e os outros cinco voltam à sala. Nunca limpa em ≥ 16 |

**Por que a Lusamine precisa de flag própria no altar.** No estado 16 os seis
visitantes se separam: Looker e Anabel moram lá (`FLAG_TEMP_1` não serve, eles
têm regra própria), a Lillie, o Gladion, os dois parceiros e o Kukui vão embora
para sempre, e **só a Lusamine volta**, por escala de dia. Uma flag para "o
grupo" mais uma para "ela" é o mínimo: o campo `flag` aceita uma flag e não sabe
combinar condições (skill `visibilidade-e-gatilhos` §1).

### 3.4 Orçamento de objetos

`OBJECT_EVENTS_COUNT` é **16** (`include/constants/global.h:83`) e **inclui o
jogador**. Objeto que não cabe não spawna, sem erro nenhum, e quem desaparece é
quem está por último no array.

**Altar, no pior momento (Ato III, com a fenda e o parceiro na tela):**

| Ocupante | Slots |
|---|---|
| Jogador | 1 |
| Follower do jogador | 1 |
| Lusamine, Lillie, Ninetales, Gladion, Silvally, Kukui | 6 |
| Looker, Anabel | 2 |
| Fenda | 1 |
| Parceiro (Solgaleo **ou** Lunala, nunca os dois) | 1 |
| **Total no pátio** | **12 / 16** |

O `Sailor` (15,27) e o `SS_TIDAL` (19,28) **não contam**: estão 12 a 18 linhas
ao sul do pátio, muito fora da janela de spawn, e a engine só spawna o que está
perto da câmera (`TrySpawnObjectEvents`, `src/event_object_movement.c:3166`).
Quando o jogador está no cais, a situação se inverte e o pátio é que não está
carregado. **Confirmar com `dump_mapa.py` depois de editar o `map.json`** —
nenhum objeto novo em y ≥ 16, e nenhum sobre os caminhos dos Atos I, III e V.

**Arena, no pior momento:** jogador + follower + Anabel + Ultra Necrozma +
parceiro = **5 / 16**. Sobra de fábrica.

`hidefollower` é usado nas cutscenes, mas a conta **não** desconta o follower: o
objeto continua alocado, e o número tem de fechar antes da cena.

---

## 4. Etapa A — `MAP_SUN_MOON_ALTAR`: o terreno

### 4.1 O que já existe (e não se mexe)

`data/maps/SunMoonAltar/` **não tem `.pory`** → editar o `scripts.inc` direto
(CLAUDE.md, "Onde editar script de mapa"). O `map.json` já traz dez objetos e o
`scripts.inc` já traz a balsa de volta, que funciona e não muda.

### 4.2 Planta (colisão real, `dump_mapa.py SunMoonAltar`; `y` cresce para baixo)

Só o pátio e a escada. `#` é colisão, o resto é chão de elevação 3.

```text
      x= 8  9 10 11 12 13 14 15 16 17 18 19 20
  y= 4     #  #  #  #  #  #  #  #  #  #  #  #  #    o paredao e o disco
  y= 5     #  #  #  #  #  D  D  D  #  #  #  #  #    D = disco (13..15, 5..6)
  y= 6     #  #  #  #  #  D  D  D  #  #  #  #  #
  y= 7     #  #  #  #  #  #  d  #  #  #  #  #  #    d = base do disco (14,7)
  y= 8     #  #  #  #  #  #  #  #  #  #  #  #  #
  y= 9     #  #  .  .  .  .  U  .  .  .  .  #  #    U = Lusamine (14,9)
  y=10     #  #  .  .  .  .  R  .  .  .  .  #  #    R = A FENDA, objeto novo (14,10)
  y=11     #  #  .  N  I  .  .  .  G  S  .  #  #    N=Ninetales(11) I=Lillie(12)
  y=12     #  #  #  #  #  .  .  .  #  #  #  #  #        G=Gladion(16) S=Silvally(17)
  y=13     .  #  .  #  .  L  .  A  .  #  .  #  .    L = Looker (13,13)
  y=14     .  .  K  .  .  .  .  .  .  .  .  .  #    A = Anabel (15,13)
  y=15     #  #  #  #  T  T  T  T  T  #  #  #  #    K = Kukui (10,14)
  y=16     .  .  .  .  .  .  .  .  .  .  .  .  .    T = gatilhos dos Atos I e V
```

Fatos medidos que a coreografia usa:

- O **pescoço** em y=12 tem três tiles: (13,12), (14,12), (15,12). Tudo que sobe
  ou desce entre o pátio e o terraço passa por ali. É o que torna barato mandar
  alguém "subir" ou "descer" em cena.
- A **escada** em y=15 tem cinco tiles: (12..16, 15). É a única entrada do pátio
  pelo sul, então cinco `coord_event` cobrem 100% das chegadas — não existe
  "entrou pelo lado errado".
- (14,10) está livre, é elevação 3, e é **exatamente** para onde a arena hoje
  devolve o jogador (`UltraSpaceArena_EventScript_SouthRift`). Ver §14, achado 3.
- (13,10) e (15,10) estão livres: é ali que o parceiro do jogador fica.
- Ninguém fica ao sul do jogador nas caixas de fala dos Atos I e V, então a caixa
  não cobre ator nenhum.

### 4.3 O disco vira portal — `setmetatile`, não `map.bin`

O tileset secundário `gTileset_AltarSunMoon` **já contém** um segundo estado do
disco, desenhado junto com o primeiro pelo gerador
`.claude/skills/montar-tileset/exemplo_altar_sol_lua.py` (§4 do cabeçalho dele,
"um segundo estado (portal) no mesmo tileset, para setmetatile"). Conferido
célula a célula contra `data/layouts/SunMoonAltar/map.bin` em 23/09/2026 — os
sete metatiles do disco no mapa batem com o carimbo, e os sete substitutos
existem:

| Tile do mapa | Metatile hoje | Metatile "portal" |
|---|---|---|
| (13,5) | 1037 | **1136** |
| (14,5) | 1038 | **1137** |
| (15,5) | 1039 | **1138** |
| (13,6) | 1041 | **1139** |
| (14,6) | 1042 | **1140** |
| (15,6) | 1043 | **1141** |
| (14,7) | 1045 | **1142** |

(Secundário começa em `NUM_METATILES_IN_PRIMARY` = 1024, `include/fieldmap.h:6`.
Os índices locais do tileset são 13-15/17-19/21 → 112-118.)

Dois scripts curtos, chamados do `ON_TRANSITION` e da cena:

```asm
@ The altar's disc has a second art state baked into gTileset_AltarSunMoon.
@ Seven metatiles, all impassable in both states - the disc is on the wall,
@ nobody ever walks on it. DrawWholeMapView is what makes the swap visible
@ when it happens on screen; from ON_TRANSITION the map has not been drawn
@ yet and the call is harmless.
SunMoonAltar_EventScript_DiscToPortal::
	setmetatile 13, 5, 1136, TRUE
	setmetatile 14, 5, 1137, TRUE
	setmetatile 15, 5, 1138, TRUE
	setmetatile 13, 6, 1139, TRUE
	setmetatile 14, 6, 1140, TRUE
	setmetatile 15, 6, 1141, TRUE
	setmetatile 14, 7, 1142, TRUE
	special DrawWholeMapView
	return

SunMoonAltar_EventScript_DiscToCalm::
	setmetatile 13, 5, 1037, TRUE
	setmetatile 14, 5, 1038, TRUE
	setmetatile 15, 5, 1039, TRUE
	setmetatile 13, 6, 1041, TRUE
	setmetatile 14, 6, 1042, TRUE
	setmetatile 15, 6, 1043, TRUE
	setmetatile 14, 7, 1045, TRUE
	special DrawWholeMapView
	return
```

> **Detalhe de arte que vale saber antes de testar à noite:** o disco normal usa
> as paletas 9 e 10, que estão na lista `swapPalettes` do tileset
> (`SWAP_PALS_ALTAR_SUN_MOON`), e por isso ele mostra **sol de dia e lua à
> noite**. Os metatiles de portal usam a paleta 11, que **não** está na lista:
> a fenda tem a mesma cor nos dois horários. Isso é intencional e é a leitura
> certa — a coisa que se abre ali não obedece ao horário de Johto. **Não
> "consertar".**

### 4.4 Os três objetos novos — `data/maps/SunMoonAltar/map.json`

No **fim** de `object_events`, com `local_id` explícito:

```json
{
  "local_id": "LOCALID_SUN_MOON_ALTAR_RIFT",
  "graphics_id": "OBJ_EVENT_GFX_PORTAL",
  "x": 14, "y": 10, "elevation": 3,
  "movement_type": "MOVEMENT_TYPE_NONE",
  "movement_range_x": 0, "movement_range_y": 0,
  "trainer_type": "TRAINER_TYPE_NONE", "trainer_sight_or_berry_tree_id": "0",
  "script": "SunMoonAltar_EventScript_Rift",
  "flag": "FLAG_TEMP_2"
},
{
  "local_id": "LOCALID_SUN_MOON_ALTAR_SOLGALEO",
  "graphics_id": "OBJ_EVENT_GFX_SPECIES(SOLGALEO)",
  "x": 13, "y": 10, "elevation": 3,
  "movement_type": "MOVEMENT_TYPE_FACE_UP",
  "movement_range_x": 0, "movement_range_y": 0,
  "trainer_type": "TRAINER_TYPE_NONE", "trainer_sight_or_berry_tree_id": "0",
  "script": "NULL",
  "flag": "FLAG_TEMP_3"
},
{
  "local_id": "LOCALID_SUN_MOON_ALTAR_LUNALA",
  "graphics_id": "OBJ_EVENT_GFX_SPECIES(LUNALA)",
  "x": 13, "y": 10, "elevation": 3,
  "movement_type": "MOVEMENT_TYPE_FACE_UP",
  "movement_range_x": 0, "movement_range_y": 0,
  "trainer_type": "TRAINER_TYPE_NONE", "trainer_sight_or_berry_tree_id": "0",
  "script": "NULL",
  "flag": "FLAG_TEMP_4"
}
```

Três coisas nessas três entradas que não são estilo:

1. **Solgaleo e Lunala ocupam o mesmo tile e têm flags DIFERENTES.** Mesma flag
   faria os dois spawnarem em cima um do outro; flags separadas fazem a cena
   escolher com `addobject` em exatamente um deles. Os dois sprites de overworld
   existem (`graphics/pokemon/solgaleo/overworld.png`, idem `lunala`).
2. **`script: NULL` nos parceiros**, como a Ninetales e o Silvally já fazem aqui
   e em Olivine (skill `parceiro-pokemon-de-npc`).
3. **A fenda é `MOVEMENT_TYPE_NONE`, não `FACE_*`.** `OBJ_EVENT_GFX_PORTAL` é
   `inanimate = TRUE` (`src/data/object_events/object_event_graphics_info.h:4589`)
   e não tem direção; é o mesmo uso dos quatro portais de `SpearPillarTop`, que é
   o precedente do repositório para isto.

Além disso, **cinco campos `flag` mudam** nos objetos que já existem:

| Objeto | `flag` hoje | `flag` novo |
|---|---|---|
| `LUSAMINE` | `"0"` | `FLAG_TEMP_5` |
| `LILLIE`, `NINETALES`, `GLADION`, `SILVALLY`, `KUKUI` | `"0"` | `FLAG_TEMP_1` |
| `LOOKER`, `ANABEL` | `"0"` | continuam `"0"` — eles moram aqui do estado 12 em diante e nunca somem |
| `SAILOR`, `SS_TIDAL` | `"0"` | continuam `"0"` |

> **Consequência que morde:** com flag temporária, o **default é visível**, porque
> `ClearTempFieldEventData()` zera toda `FLAG_TEMP_*` a cada load
> (`src/event_data.c:60`). Sem o `ON_TRANSITION` abaixo, o elenco aparece no altar
> desde o New Game — se o jogador chegar lá por debug. Editar o `map.json` e o
> `ON_TRANSITION` **na mesma passada**, nunca um sem o outro. É a mesma armadilha
> que o doc do PRÉ-NECROZMA registrou em §6, "Ordem de edição".

### 4.5 O mapa ganha um `MapScripts` de verdade

Hoje `SunMoonAltar_MapScripts` é só `.byte 0`. Passa a ser:

```asm
SunMoonAltar_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SunMoonAltar_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, SunMoonAltar_OnFrame
	.byte 0
```

`ON_TRANSITION` antes de `ON_FRAME_TABLE`, que é a ordem que os outros mapas do
arco usam, e **um só** `.byte 0` terminador (erro que o PRÉ-NECROZMA registrou
em §12.3).

```asm
@ Runs before the first spawn on EVERY load. Four independent decisions, all
@ recomputed from VAR_RIFT_MISSIONS_STATE, none of them ever persisted:
@   1. the five visitors and the two partners (FLAG_TEMP_1)
@   2. Lusamine alone (FLAG_TEMP_5) - she is the only one who comes back
@   3. the ground rift (FLAG_TEMP_2), story branch and daily branch
@   4. the weather and the disc art
@ The two legendary objects (FLAG_TEMP_3/4) are NEVER shown here: only a scene
@ addobjects them. Setting both unconditionally is what guarantees that a
@ blackout retry finds the map clean.
SunMoonAltar_OnTransition::
	setflag FLAG_TEMP_3
	setflag FLAG_TEMP_4
	call SunMoonAltar_EventScript_ApplyCastVisibility
	call SunMoonAltar_EventScript_ApplyLusamineVisibility
	call SunMoonAltar_EventScript_ApplyRiftVisibility
	call SunMoonAltar_EventScript_ApplyAltarMood
	end

@ The five visitors plus the two partners: present from the first arrival
@ (12) through the farewell (15), gone for good from 16 on.
SunMoonAltar_EventScript_ApplyCastVisibility::
	goto_if_lt VAR_RIFT_MISSIONS_STATE, 12, SunMoonAltar_EventScript_HideCast
	goto_if_ge VAR_RIFT_MISSIONS_STATE, 16, SunMoonAltar_EventScript_HideCast
	clearflag FLAG_TEMP_1
	return
SunMoonAltar_EventScript_HideCast::
	setflag FLAG_TEMP_1
	return

@ Lusamine: with the cast in 12..15, and then on her own rota from 16 on.
@ GetDayOfWeek is a special added by this document (section 10.4).
SunMoonAltar_EventScript_ApplyLusamineVisibility::
	goto_if_lt VAR_RIFT_MISSIONS_STATE, 12, SunMoonAltar_EventScript_HideLusamine
	goto_if_lt VAR_RIFT_MISSIONS_STATE, 16, SunMoonAltar_EventScript_ShowLusamine
	specialvar VAR_RESULT, GetDayOfWeek
	goto_if_eq VAR_RESULT, WEEKDAY_MON, SunMoonAltar_EventScript_ShowLusamine
	goto_if_eq VAR_RESULT, WEEKDAY_WED, SunMoonAltar_EventScript_ShowLusamine
	goto_if_eq VAR_RESULT, WEEKDAY_SAT, SunMoonAltar_EventScript_ShowLusamine
SunMoonAltar_EventScript_HideLusamine::
	setflag FLAG_TEMP_5
	return
SunMoonAltar_EventScript_ShowLusamine::
	clearflag FLAG_TEMP_5
	return

@ The rift: open and unconditional during the climax (14, 15), then once a
@ day forever. FLAG_DAILY_ALTAR_RIFT is cleared by ClearDailyFlags at the
@ date rollover, so "once a day" costs one daily flag and no var.
SunMoonAltar_EventScript_ApplyRiftVisibility::
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 14, SunMoonAltar_EventScript_ShowRift
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 15, SunMoonAltar_EventScript_ShowRift
	goto_if_lt VAR_RIFT_MISSIONS_STATE, 16, SunMoonAltar_EventScript_HideRift
	goto_if_set FLAG_DAILY_ALTAR_RIFT, SunMoonAltar_EventScript_HideRift
SunMoonAltar_EventScript_ShowRift::
	clearflag FLAG_TEMP_2
	return
SunMoonAltar_EventScript_HideRift::
	setflag FLAG_TEMP_2
	return

@ Weather and disc art. 13..15 is the unstable chapter; everything else is a
@ clear altar. setweather in ON_TRANSITION is applied by the map load itself,
@ so no doweather is needed here.
SunMoonAltar_EventScript_ApplyAltarMood::
	goto_if_lt VAR_RIFT_MISSIONS_STATE, 13, SunMoonAltar_EventScript_AltarCalm
	goto_if_ge VAR_RIFT_MISSIONS_STATE, 16, SunMoonAltar_EventScript_AltarCalm
	setweather WEATHER_VOLCANIC_ASH
	call SunMoonAltar_EventScript_DiscToPortal
	return
SunMoonAltar_EventScript_AltarCalm::
	setweather WEATHER_NONE
	call SunMoonAltar_EventScript_DiscToCalm
	return
```

**Por que `goto_if_lt`/`goto_if_ge` e não a lista de `goto_if_eq` do doc
anterior.** Lá a regra era "só 10 e 11", uma janela de dois valores no meio da
máquina, e `goto_if_ge` teria deixado a Lusamine na sala para sempre — por isso
o alerta daquele arquivo. Aqui as janelas são **fechadas dos dois lados** e
escritas assim, com um `lt` e um `ge`. É a mesma proteção, escrita de um jeito
que não se degrada quando o 17 existir.

### 4.6 Os dois gatilhos, e por que eles não podem usar a mesma `VAR_TEMP`

Este mapa precisa de **duas** entradas de cena, e elas são diferentes em
natureza:

| Cena | Como o jogador chega | Gatilho |
|---|---|---|
| Ato I (estado 12) | de balsa, subindo a escada | 5 `coord_event` em (12..16, 15) |
| Ato V (estado 15) | saindo da fenda, em (14,11) | `ON_FRAME_TABLE`, que dispara no load |

```asm
SunMoonAltar_OnFrame::
	map_script_2 VAR_TEMP_1, 0, SunMoonAltar_EventScript_FrameTrigger
	.2byte 0
```

Os cinco tiles da escada entram como `coord_event` no `map.json`, com
`"var": "VAR_TEMP_0", "var_value": "0"` e o mesmo script.

> **A armadilha, e ela mataria o Ato I sem erro de build.** Se os dois gatilhos
> usassem `VAR_TEMP_1`, o gatilho de frame — que dispara **no load**, sempre —
> faria `setvar VAR_TEMP_1, 1` como primeira instrução, e a partir daí a condição
> dos `coord_event` (`VAR_TEMP_1 == 0`) **nunca** seria verdadeira. A cena de
> chegada simplesmente não aconteceria, e o jogador andaria pelo altar com o
> elenco parado. Duas travas, duas vars: `VAR_TEMP_1` para o frame, `VAR_TEMP_0`
> para os `coord_event`.
>
> **E os `coord_event` não precisam de trava própria.** Um `coord_event` dispara
> ao **pisar** no tile, não a cada frame, então não existe livelock a evitar; o
> que impede a repetição é o estado (o Ato I termina em 13, e 13 não casa com
> nada na lista). É o mesmo padrão dos três `coord_event` que já existem em
> `UltraSpaceArena` (`"var": "VAR_TEMP_0", "var_value": "0"`).

```asm
@ The ONLY way into the courtyard from the pier is the five-tile stair at
@ y=15, so five coord_events cover every arrival: no getplayerxy guard is
@ needed and no approach can skip the scene.
@ No latch here on purpose (see the note above): the state is the guard.
SunMoonAltar_EventScript_StairTrigger::
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 12, SunMoonAltar_EventScript_Arrival
	end
```

### 4.7 Fly para o altar — cinco peças, e quatro já existem

Decisão do autor na revisão 2: *"coloca no mesmo mapa secundário que tem a
Crater"*. Pesquisado e **é exatamente onde ele já está**, o que torna o Fly
barato:

| Peça | Situação |
|---|---|
| A `MAPSEC` tem nome e posição | **existe.** `MAPSEC_ABANDONED_LAB`, `x = 16, y = 0`, `.name = "Altar of Sun and Moon"` (`region_map_entries.h:1955`) |
| A `MAPSEC` está numa página do mapa da região | **existe.** `region_map_layout_sevii123.h`, na mesma linha de `MAPSEC_METEOR_ISLAND` (`x = 10, y = 0`) |
| Precedente funcionando nessa mesma página | **existe.** A Meteor Island (a "Crater") **é** destino de Fly: `{MAPSEC_METEOR_ISLAND, FLAG_VISITED_METEOR_CAVE}` em `sFlyDestinations` (`src/region_map.c:496`), `case` em `GetMapsecType` (`:1693`), linha em `sMapHealLocations` (`:390`) e `HEAL_LOCATION_METEOR_ISLAND` (`src/data/heal_locations.h:475`) |
| `HEAL_LOCATION_METEOR_ISLAND` prova o mecanismo de pouso | `SetFlyDestination` (`src/region_map.c:2686`) resolve o destino por `sMapHealLocations[mapSecId][2]`, então um destino de Fly precisa de uma `HEAL_LOCATION` |
| O que falta | **quatro linhas e uma entrada de JSON** |

Ou seja: a dúvida da revisão 1 ("um destino numa página secundária é
selecionável?") está **respondida pela Meteor Island**, que está na mesma página
e funciona. As quatro linhas:

```c
/* src/region_map.c, sMapHealLocations (~:390), ao lado da Meteor Island */
[MAPSEC_ABANDONED_LAB] = {MAP_GROUP(MAP_SUN_MOON_ALTAR), MAP_NUM(MAP_SUN_MOON_ALTAR), HEAL_LOCATION_SUN_MOON_ALTAR},

/* src/region_map.c, sFlyDestinations (~:496) */
{MAPSEC_ABANDONED_LAB,    FLAG_VISITED_SUN_MOON_ALTAR},

/* src/region_map.c, GetMapsecType (~:1693) */
case MAPSEC_ABANDONED_LAB:
    return FlagGet(FLAG_VISITED_SUN_MOON_ALTAR) ? MAPSECTYPE_CITY_CANFLY : MAPSECTYPE_CITY_CANTFLY;
```

mais a entrada em `src/data/heal_locations.json` (mapa `SunMoonAltar`, x 14,
y 16) e **um `setflag` no Ato I**, colado no `setvar 13`:

```asm
SunMoonAltar_EventScript_ArrivalDone::
	setvar VAR_RIFT_MISSIONS_STATE, 13
	setflag FLAG_VISITED_SUN_MOON_ALTAR   @ the altar becomes a Fly destination
	fadedefaultbgm
	releaseall
	end
```

> **Por que no fim do Ato I e não na chegada ao cais.** O design §7 diz "a
> primeira chegada libera o altar como destino de Fly". Ligar no cais deixaria o
> jogador voar para cá antes de a cena de chegada existir — e o Ato I é o que dá
> sentido ao lugar. No fim do Ato I o jogador **já viu** o altar, e a partir daí
> Fly é conveniência pura.
>
> **Três mapas dividem essa `MAPSEC`** (`SunMoonAltar`, `UltraSpaceArena`,
> `SouthPassageEnd`). `sMapHealLocations` é indexada por `MAPSEC`, então Fly
> sempre pousa no altar, que é o certo. Efeito colateral bom: o Necrozma
> recebido no `givemon` nasce com "Altar of Sun and Moon" como local de encontro
> mesmo sendo entregue dentro da arena.

---

## 5. Ato I — a chegada (estado 12 → 13)

### 5.1 O arco da cena

Seguindo a receita da skill `evoluir-historia-de-evento` §2, e mudando de
propósito **um** passo dela:

| # | Passo | Aqui |
|---|---|---|
| 1 | O mundo já está em movimento na chegada | O disco já está girando, sem vento. Ninguém esperou o jogador; eles vieram no navio anterior |
| 2 | Uma autoridade tenta e falha | O instrumento do Kukui não está errado — está **sendo lido por outra coisa**. Seis semanas de trabalho, inúteis em uma caixa |
| 3 | Escalada | O disco deixa de ser disco (`setmetatile`), a cinza começa a cair, a ilha treme |
| 4 | Perigo direto ao jogador | **Não acontece aqui, e é intencional.** A ameaça deste evento não corre para cima de ninguém: ela fica parada e espera. O perigo direto é o Ato IV |
| 5 | Resgate por quem ninguém anunciou | **Também não.** Não há surpresa de elenco neste ato: todo mundo foi anunciado na reunião. A surpresa deste evento é outra, e está guardada no Ato IV (§8.6) |
| 6 | Estrutura de jogo | O ato **termina sem batalha**. O jogador é solto |
| 7 | Consequência inesperada | A consequência vem antes da luta, não depois: a Lusamine se oferece, e a cena descobre que o problema não é a criatura, é a família |
| 8 | Cada um reage na própria voz | Seis caixas, uma por pessoa |
| 9 | Cuidar das pessoas antes do relatório | O Looker larga o relatório inteiro: "isto não é assunto de polícia" |
| 10 | Um presente com significado | Não neste ato |
| 11 | Gancho | O gancho é uma **pessoa**, não um lugar: vá falar com ela |

**A decisão de encenação que sustenta tudo:** o ato acaba com o jogador solto e
uma discussão aberta. É o pedido literal do autor ("a cena para aí e o player é
liberado"), e é também a melhor coisa que este evento faz — pela primeira vez no
arco, o que trava a história não é uma criatura, é um desacordo entre pessoas, e
quem desempata é o jogador.

### 5.2 Coreografia

Posições de entrada (todas do `map.json`, nada é movido antes da cena):
Lusamine (14,9) olhando **para cima**, para o disco — `movement_type` dela muda
de `FACE_DOWN` para `FACE_UP`, única alteração num objeto existente; Ninetales
(11,11), Lillie (12,11), Gladion (16,11), Silvally (17,11) olhando para cima;
Looker (13,13), Anabel (15,13), Kukui (10,14).

```asm
@ ---------------------------------------------------------------------------
@ ACT I - the arrival. State 12 -> 13. Reached only from the stair coord_events
@ at (12..16, 15), so the player is always one tile south of the terrace.
@
@ Choreography, measured on dump_mapa.py SunMoonAltar:
@   player      (x,15) -> walk to (14,14), facing up
@   Looker      (13,13) turns down     Anabel (15,13) turns down
@   Kukui       (10,14) turns right    (same row as the player, to the west)
@   Lusamine    (14,9)  -> walk_down x2 -> (14,11), turns down
@               ...and at the end walks back up to (14,9) and turns up again,
@               so the map matches the templates after releaseall
@   Lillie      (12,11) turns right    Gladion (16,11) turns left
@               (the two children end up flanking their mother)
@ (14,10) and (14,12) are free in state 12: the rift does not exist yet and
@ the neck is the only way down from the platform.
@
@ Every fade inside this scene is fadescreenswapbuffers, NEVER fadescreen:
@ the scene comes back to this same map, and fadescreen composes the
@ time-of-day tint onto itself (V23 of the design).
@ ---------------------------------------------------------------------------
SunMoonAltar_EventScript_Arrival::
	lockall
	hidefollower
	delay 20
	applymovement OBJ_EVENT_ID_PLAYER, SunMoonAltar_Movement_PlayerStepUp
	waitmovement OBJ_EVENT_ID_PLAYER
	turnobject LOCALID_SUN_MOON_ALTAR_LOOKER, DIR_SOUTH
	turnobject LOCALID_SUN_MOON_ALTAR_ANABEL, DIR_SOUTH
	turnobject LOCALID_SUN_MOON_ALTAR_KUKUI, DIR_EAST
	msgbox SunMoonAltar_Text_ArrivalDisc, MSGBOX_DEFAULT
	closemessage
	msgbox SunMoonAltar_Text_ArrivalKukui, MSGBOX_DEFAULT
	closemessage
	fadeoutbgm 4
	msgbox SunMoonAltar_Text_ArrivalAnabel, MSGBOX_DEFAULT
	closemessage
	msgbox SunMoonAltar_Text_ArrivalLooker, MSGBOX_DEFAULT
	closemessage
	@ --- the escalation: the disc stops being a disc ---------------------
	playbgm MUS_DP_LEGEND_APPEARS, TRUE          @ TRUE: a battle restores it
	call SunMoonAltar_EventScript_Shake
	fadescreenswapbuffers FADE_TO_WHITE
	call SunMoonAltar_EventScript_DiscToPortal
	fadescreenswapbuffers FADE_FROM_WHITE
	setweather WEATHER_VOLCANIC_ASH
	doweather
	delay 40
	msgbox SunMoonAltar_Text_ArrivalTurns, MSGBOX_DEFAULT
	closemessage
	call SunMoonAltar_EventScript_PartnerStirs      @ optional, no state
	applymovement LOCALID_SUN_MOON_ALTAR_GLADION, Common_Movement_ExclamationMark
	waitmovement LOCALID_SUN_MOON_ALTAR_GLADION
	msgbox SunMoonAltar_Text_ArrivalGladionBack, MSGBOX_DEFAULT
	closemessage
	msgbox SunMoonAltar_Text_ArrivalLillieDoor, MSGBOX_DEFAULT
	closemessage
	@ --- the offer -------------------------------------------------------
	applymovement LOCALID_SUN_MOON_ALTAR_LUSAMINE, SunMoonAltar_Movement_LusamineDown
	waitmovement LOCALID_SUN_MOON_ALTAR_LUSAMINE
	turnobject LOCALID_SUN_MOON_ALTAR_LILLIE, DIR_EAST
	turnobject LOCALID_SUN_MOON_ALTAR_GLADION, DIR_WEST
	msgbox SunMoonAltar_Text_ArrivalOffer, MSGBOX_DEFAULT
	closemessage
	msgbox SunMoonAltar_Text_ArrivalOfferWhy, MSGBOX_DEFAULT
	closemessage
	msgbox SunMoonAltar_Text_ArrivalOfferCost, MSGBOX_DEFAULT
	closemessage
	@ --- the children ----------------------------------------------------
	msgbox SunMoonAltar_Text_ArrivalLillieNo, MSGBOX_DEFAULT
	closemessage
	msgbox SunMoonAltar_Text_ArrivalLillieNoTwo, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SUN_MOON_ALTAR_SILVALLY, Common_Movement_WalkInPlaceFasterLeft
	waitmovement LOCALID_SUN_MOON_ALTAR_SILVALLY
	msgbox SunMoonAltar_Text_ArrivalGladionNo, MSGBOX_DEFAULT
	closemessage
	msgbox SunMoonAltar_Text_ArrivalAnabelCondition, MSGBOX_DEFAULT
	closemessage
	@ --- she goes back to looking at the door -----------------------------
	applymovement LOCALID_SUN_MOON_ALTAR_LUSAMINE, SunMoonAltar_Movement_LusamineUp
	waitmovement LOCALID_SUN_MOON_ALTAR_LUSAMINE
	msgbox SunMoonAltar_Text_ArrivalLusamineWaits, MSGBOX_DEFAULT
	closemessage
	@ --- the handoff to the player ---------------------------------------
	applymovement LOCALID_SUN_MOON_ALTAR_LOOKER, SunMoonAltar_Movement_LookerAside
	waitmovement LOCALID_SUN_MOON_ALTAR_LOOKER
	msgbox SunMoonAltar_Text_ArrivalLookerAside, MSGBOX_DEFAULT
	closemessage
	msgbox SunMoonAltar_Text_ArrivalLookerHand, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_SUN_MOON_ALTAR_LOOKER, SunMoonAltar_Movement_LookerBack
	waitmovement LOCALID_SUN_MOON_ALTAR_LOOKER
	goto SunMoonAltar_EventScript_ArrivalDone

@ No warpsilent here: nothing about the map's population changes, everybody
@ ended on the tile their template names, and the player has to be left
@ standing in the courtyard. This is the whole point of the act.
SunMoonAltar_EventScript_ArrivalDone::
	setvar VAR_RIFT_MISSIONS_STATE, 13
	fadedefaultbgm
	releaseall
	end

SunMoonAltar_Movement_PlayerStepUp:
	walk_up
	face_up
	step_end

SunMoonAltar_Movement_LusamineDown:
	walk_down
	walk_down
	face_down
	step_end

SunMoonAltar_Movement_LusamineUp:
	walk_up
	walk_up
	face_up
	step_end

@ Looker takes one step west, away from the family, which is the staging of
@ his line: he is stepping out of the argument, not into it. (12,13) is free.
SunMoonAltar_Movement_LookerAside:
	walk_left
	face_down
	step_end

SunMoonAltar_Movement_LookerBack:
	walk_right
	face_down
	step_end

@ Reusable: a short camera shake, so no scene writes the numbers twice.
@ Signature copied verbatim from BlackthornCity_EventScript_UBShake (:533) -
@ FOUR vars, not two: pan, pan, count, delay.
SunMoonAltar_EventScript_Shake::
	setvar VAR_0x8004, 1    @ vertical pan
	setvar VAR_0x8005, 1    @ horizontal pan
	setvar VAR_0x8006, 12   @ num shakes
	setvar VAR_0x8007, 4    @ shake delay
	special ShakeCamera
	waitstate
	return
```

> **`ShakeCamera` lê quatro vars** (`data/specials.inc:360`), e as quatro
> missões já têm um `..._EventScript_UBShake` idêntico em cada mapa. Copiar o
> daquele arquivo. Passar só duas deixa `VAR_0x8006`/`VAR_0x8007` com o que
> sobrou da chamada anterior — o tremor sai com duração aleatória, e nada no
> build acusa.

### 5.3 A reação opcional ao parceiro

Sem flag, sem var persistente; se o jogador não tiver nenhum da família Cosmog
na equipe, a cena é idêntica e nada falta (padrão do design §4.11 e da skill
`evoluir-historia-de-evento` §5). `VAR_TEMP_4` guarda a espécie porque o Ato III
vai reler.

```asm
@ Called with VAR_RESULT free and not read afterwards by the caller.
@ CheckMysteryEggPokemon walks the whole party and ignores eggs.
SunMoonAltar_EventScript_PartnerStirs::
	specialvar VAR_RESULT, CheckMysteryEggPokemon
	copyvar VAR_TEMP_4, VAR_RESULT
	goto_if_eq VAR_TEMP_4, SPECIES_NONE, SunMoonAltar_EventScript_PartnerStirsEnd
	bufferspeciesname STR_VAR_1, VAR_TEMP_4
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	waitmovement OBJ_EVENT_ID_PLAYER
	goto_if_eq VAR_TEMP_4, SPECIES_COSMOG, SunMoonAltar_EventScript_PartnerStirsSmall
	goto_if_eq VAR_TEMP_4, SPECIES_COSMOEM, SunMoonAltar_EventScript_PartnerStirsSmall
	msgbox SunMoonAltar_Text_PartnerStirsLegend, MSGBOX_DEFAULT
	closemessage
	return
SunMoonAltar_EventScript_PartnerStirsSmall::
	msgbox SunMoonAltar_Text_PartnerStirsSmall, MSGBOX_DEFAULT
	closemessage
SunMoonAltar_EventScript_PartnerStirsEnd::
	return
```

### 5.4 Textos do Ato I

Todas as falas da chegada — incluindo a reação opcional ao parceiro — estão em
[`ALTAR_SUN_MOON_SCRIPT.md`](ALTAR_SUN_MOON_SCRIPT.md), "Ato I".

Regras que qualquer reescrita precisa respeitar:

- **Sem travessão `—`**: U+2014 não está em `charmap.txt`; use `--`. `“ ”` e `…` podem.
- Vozes do design §3.1. **Ninguém chama a criatura pelo nome** antes do Ato IV.
- Larguras de linha: conferir com a ferramenta da skill `nomear-falante`.

---

## 6. Ato II — o duelo da Lusamine (estado 13 → 14)

### 6.1 O contrato

Design §9 e §11, palavra por palavra: **duelo narrativo de personagem, não boss
de ameaça.** Isso significa `B_FLAG_NO_WHITEOUT`, os quatro resultados tratados,
e — a parte que é fácil errar — **os dois resultados resolvem a disputa**. A
vitória do jogador não é o que convence a Lusamine, e a derrota dele não impede
a história de andar. Skill `batalha-sem-blackout`, inteira.

**Quem convence é a Lillie, nos dois ramos.** É a única maneira de obedecer ao
design ("o resultado não deve ser reescrito como vitória do jogador") sem fazer
a batalha parecer decorativa: a batalha é o que faz a Lusamine **parar de falar
por tempo suficiente**, e o que entra na brecha é a filha. Na vitória ela entra
com a mãe já desmontada; na derrota ela entra com a mãe ainda de pé, e é uma
cena melhor.

### 6.2 O script de objeto da Lusamine

```asm
@ ---------------------------------------------------------------------------
@ Lusamine, one object script, five branches by state:
@   < 13  she is not here (FLAG_TEMP_5 keeps her hidden) - unreachable
@   13    the duel: one YES/NO. NO changes nothing and is repeatable.
@   14    the rift is open and she is holding the anchor
@   15    transient: the farewell has not played yet
@   >= 16 postgame: her line, plus one rematch a day
@ Nothing changes state before the YES. The YES is the last exit point.
@ ---------------------------------------------------------------------------
SunMoonAltar_EventScript_Lusamine::
	lock
	faceplayer
	goto_if_ge VAR_RIFT_MISSIONS_STATE, 16, SunMoonAltar_EventScript_LusaminePost
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 15, SunMoonAltar_EventScript_LusamineIdle
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 14, SunMoonAltar_EventScript_LusamineAnchor
	goto_if_ne VAR_RIFT_MISSIONS_STATE, 13, SunMoonAltar_EventScript_LusamineIdle
	msgbox SunMoonAltar_Text_DuelApproach, MSGBOX_DEFAULT
	closemessage
	msgbox SunMoonAltar_Text_DuelAsk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SunMoonAltar_EventScript_DuelDeclined
	goto SunMoonAltar_EventScript_Duel

@ NO costs nothing: no flag, no var, no movement. The player can walk away,
@ heal, come back and be asked again, word for word.
SunMoonAltar_EventScript_DuelDeclined::
	msgbox SunMoonAltar_Text_DuelDeclined, MSGBOX_DEFAULT
	closemessage
	release
	end

SunMoonAltar_EventScript_LusamineIdle::
	msgbox SunMoonAltar_Text_LusamineIdle, MSGBOX_DEFAULT
	release
	end
```

### 6.3 A batalha

```asm
@ Narrative duel (design section 9 and 11): NO blackout, NO penalty, and BOTH
@ outcomes move the story to state 14. The four results are handled and the
@ unexpected branch never turns into a win.
@ Reached from an object script (lock), and it moves other objects, so it
@ escalates to lockall - the same pattern as every mission scene in the arc.
SunMoonAltar_EventScript_Duel::
	closemessage
	lockall
	msgbox SunMoonAltar_Text_DuelAccept, MSGBOX_DEFAULT
	closemessage
	checkflag B_FLAG_NO_WHITEOUT
	copyvar VAR_TEMP_3, VAR_RESULT              @ remember if it was ALREADY on
	setflag B_FLAG_NO_WHITEOUT
	trainerbattle_no_intro TRAINER_LUSAMINE, SunMoonAltar_Text_DuelLusamineBeaten
	specialvar VAR_RESULT, GetBattleOutcome
	copyvar VAR_TEMP_2, VAR_RESULT              @ copy IMMEDIATELY, before anything
	goto_if_eq VAR_TEMP_3, TRUE, SunMoonAltar_EventScript_DuelKeepWhiteout
	clearflag B_FLAG_NO_WHITEOUT
SunMoonAltar_EventScript_DuelKeepWhiteout::
	goto_if_eq VAR_TEMP_2, B_OUTCOME_WON, SunMoonAltar_EventScript_DuelWon
	goto_if_eq VAR_TEMP_2, B_OUTCOME_LOST, SunMoonAltar_EventScript_DuelLost
	goto_if_eq VAR_TEMP_2, B_OUTCOME_DREW, SunMoonAltar_EventScript_DuelDrew
	goto_if_eq VAR_TEMP_2, B_OUTCOME_FORFEITED, SunMoonAltar_EventScript_DuelForfeited
	goto SunMoonAltar_EventScript_DuelUnexpected

@ The player won. She is not convinced by losing - she is interrupted by it.
SunMoonAltar_EventScript_DuelWon::
	msgbox SunMoonAltar_Text_DuelWon, MSGBOX_DEFAULT
	closemessage
	goto SunMoonAltar_EventScript_DuelSettled

@ The player lost. She won and it changed nothing, which is the better scene.
SunMoonAltar_EventScript_DuelLost::
	msgbox SunMoonAltar_Text_DuelLost, MSGBOX_DEFAULT
	closemessage
	goto SunMoonAltar_EventScript_DuelSettled

SunMoonAltar_EventScript_DuelDrew::
	msgbox SunMoonAltar_Text_DuelDrew, MSGBOX_DEFAULT
	closemessage
	goto SunMoonAltar_EventScript_DuelSettled

SunMoonAltar_EventScript_DuelForfeited::
	msgbox SunMoonAltar_Text_DuelForfeited, MSGBOX_DEFAULT
	closemessage
	goto SunMoonAltar_EventScript_DuelSettled

@ Unexpected: this scene is reached by TALKING to her, not by a frame trigger,
@ so it is allowed to stop. Nothing is marked, nobody has moved yet, and the
@ player can simply speak to her again. It is NEVER a win.
SunMoonAltar_EventScript_DuelUnexpected::
	msgbox SunMoonAltar_Text_DuelUnexpected, MSGBOX_DEFAULT
	closemessage
	releaseall
	end
```

**Os quatro resultados, e o que muda entre eles:**

| `GetBattleOutcome` | Acontece? | Fala | Estado |
|---|---|---|---|
| `B_OUTCOME_WON` | sim | Ela reconhece a derrota e **não** muda de ideia por causa dela | → 14 |
| `B_OUTCOME_LOST` | sim, e é o mais provável numa primeira tentativa | Ela ganha e diz que isso não provou nada; a Lillie fecha | → 14 |
| `B_OUTCOME_DREW` | sim (dupla queda por recuo, Destiny Bond, etc.) | Uma caixa própria, depois o ramo comum | → 14 |
| `B_OUTCOME_FORFEITED` | sim — sem `B_FLAG_NO_RUNNING`, fugir de treinador não é possível, mas **desistir pelo menu** é | Uma caixa própria; ela comenta a desistência em caráter | → 14 |
| qualquer outro | não deveria | Fala neutra, `releaseall`, **sem** mudar estado. O jogador fala com ela de novo | 13 |

### 6.4 A resolução comum e a abertura da fenda — Ato III

```asm
@ ---------------------------------------------------------------------------
@ Common tail of all four outcomes, and ACT III inside it: the rift opens.
@ Lillie is the one who ends the argument, in every branch, because the design
@ forbids rewriting this as the player's victory (section 9).
@
@ Choreography (positions after the battle - a battle does not reload the map,
@ and nobody moved during the duel):
@   Lusamine (14,9) facing up    player wherever he spoke to her from
@   Lillie   (12,11) -> walk to (13,11), turn up   (adjacent to her mother's
@                                                   column, still on the row)
@   Solgaleo/Lunala addobject at (13,10), facing up at the disc
@   the rift   addobject at (14,10)
@ (13,11) and (13,10) are free and elevation 3 (dump_mapa.py).
@ ---------------------------------------------------------------------------
SunMoonAltar_EventScript_DuelSettled::
	applymovement LOCALID_SUN_MOON_ALTAR_LILLIE, SunMoonAltar_Movement_LillieForward
	waitmovement LOCALID_SUN_MOON_ALTAR_LILLIE
	msgbox SunMoonAltar_Text_DuelLillieEnds, MSGBOX_DEFAULT
	closemessage
	msgbox SunMoonAltar_Text_DuelLusamineYields, MSGBOX_DEFAULT
	closemessage
	msgbox SunMoonAltar_Text_DuelGladion, MSGBOX_DEFAULT
	closemessage
	@ --- the partner answers the altar ------------------------------------
	playbgm MUS_DP_LEGEND_APPEARS, TRUE
	call SunMoonAltar_EventScript_ShowPartner
	call SunMoonAltar_EventScript_Shake
	fadescreenswapbuffers FADE_TO_WHITE
	addobject LOCALID_SUN_MOON_ALTAR_RIFT
	fadescreenswapbuffers FADE_FROM_WHITE
	playse SE_WARP_IN
	msgbox SunMoonAltar_Text_RiftOpens, MSGBOX_DEFAULT
	closemessage
	msgbox SunMoonAltar_Text_RiftKukui, MSGBOX_DEFAULT
	closemessage
	msgbox SunMoonAltar_Text_RiftAnabel, MSGBOX_DEFAULT
	closemessage
	goto SunMoonAltar_EventScript_DuelResolved

@ Exactly one of the two legendaries is added, chosen by what is actually in
@ the party. VAR_TEMP_4 was filled by PartnerStirs in Act I, but this scene is
@ reachable in a later visit, so it is read again here - never trust a temp
@ across map loads.
@ If the player deposited the partner after the reunion, nothing is added and
@ the scene still works: the rift opens anyway, and the RIFT script (section 7)
@ is what refuses to let anybody through. That refusal is repeatable and free.
SunMoonAltar_EventScript_ShowPartner::
	specialvar VAR_RESULT, CheckMysteryEggPokemon
	copyvar VAR_TEMP_4, VAR_RESULT
	goto_if_eq VAR_TEMP_4, SPECIES_SOLGALEO, SunMoonAltar_EventScript_ShowSolgaleo
	goto_if_eq VAR_TEMP_4, SPECIES_LUNALA, SunMoonAltar_EventScript_ShowLunala
	return
SunMoonAltar_EventScript_ShowSolgaleo::
	addobject LOCALID_SUN_MOON_ALTAR_SOLGALEO
	playmoncry SPECIES_SOLGALEO, CRY_MODE_ENCOUNTER
	waitmoncry
	return
SunMoonAltar_EventScript_ShowLunala::
	addobject LOCALID_SUN_MOON_ALTAR_LUNALA
	playmoncry SPECIES_LUNALA, CRY_MODE_ENCOUNTER
	waitmoncry
	return

@ End of Act II/III. The population of the map changed (the rift and possibly
@ a legendary were added, Lillie moved), so the scene closes the way every
@ scene in this arc closes: state under a fade, then a reload in place, and
@ ON_TRANSITION rebuilds everything from the var.
@ (14,14) is free, is not a warp, and is where the player can see the rift.
@ The stair trigger fires again after this load with VAR_TEMP_1 zeroed, but
@ dies immediately: state 14 matches no goto_if_eq in its list.
SunMoonAltar_EventScript_DuelResolved::
	fadescreen FADE_TO_BLACK
	setvar VAR_RIFT_MISSIONS_STATE, 14
	warpsilent MAP_SUN_MOON_ALTAR, 14, 14
	waitstate
	releaseall
	end

SunMoonAltar_Movement_LillieForward:
	walk_right
	face_up
	step_end
```

Quatro coisas nesse bloco que são contrato, não estilo:

1. **`fadescreen` aqui, e só aqui.** A regra da V23 é `fadescreenswapbuffers`
   dentro de cena; a exceção é o fade que precede um `warpsilent`, porque o load
   seguinte reconstrói as paletas de qualquer jeito. Os dois fades de flash logo
   acima **são** `fadescreenswapbuffers`.
2. **`warpsilent` + `waitstate` + `releaseall` + `end`, nessa ordem.** Erro que a
   M1 cometeu e virou regra do arco.
3. **`addobject` antes do `warpsilent`, não depois.** O `ON_TRANSITION` do load
   seguinte é quem torna a fenda permanente (estado 14 → `clearflag FLAG_TEMP_2`);
   o `addobject` aqui é só para o jogador **ver** a fenda nascer.
4. **O parceiro não sobrevive ao `warpsilent`,** e é assim que tem de ser:
   `FLAG_TEMP_3`/`4` voltam a ser setadas no load. Ele apareceu para atender ao
   altar e voltou para a bola. Quem o traz de volta é o Ato IV.

### 6.5 O time da Lusamine

`TRAINER_LUSAMINE` (964) é hoje um stub com um Rattata nível 5 e **nenhuma
referência em `data/maps/`**. Reaproveitar o id e reescrever o time em
`src/data/trainers.party`. Proposta, pós-Liga, equipe de cinco:

| # | Pokémon | Nível | Papel |
|---|---|---|---|
| 1 | Clefable @ Leftovers | 70 | Calm Mind / Moonblast / Moonlight / Thunder Wave |
| 2 | Lilligant @ Focus Sash | 70 | Quiver Dance / Petal Dance / Sleep Powder / Hidden Power |
| 3 | Mismagius @ Life Orb | 71 | Nasty Plot / Shadow Ball / Dazzling Gleam / Will-O-Wisp |
| 4 | Bewear @ Assault Vest | 71 | Double-Edge / Drain Punch / Ice Punch / Darkest Lariat |
| 5 | Milotic @ Flame Orb | 72 | Recover / Scald / Ice Beam / Mirror Coat |

`AI: Smart Trainer`, `Class: Beauty`, `Music: Hg Girl 2` (o que o stub já traz).
**Não é um boss** — cinco Pokémon, níveis de pós-Liga, sem multiplicador e sem
barra. Ela é difícil do jeito que um treinador é difícil.

> **Leitura de personagem que o time carrega:** nada aqui é uma Ultra Beast.
> Ela é presidente de uma fundação de conservação, e o time dela são criaturas
> bonitas e bem cuidadas. Isso é escolha, não descuido: o argumento inteiro da
> cena é que ela parou de colecionar o que não devia.

### 6.6 Textos do Ato II

Todas as falas do duelo e da abertura da fenda — incluindo **os cinco
desfechos** (venceu, perdeu, empate, desistiu, inesperado) e as três caixas do
portão da fenda — estão em [`ALTAR_SUN_MOON_SCRIPT.md`](ALTAR_SUN_MOON_SCRIPT.md), "Ato II", "Ato III" e "Ato III-b".

Regras que qualquer reescrita precisa respeitar:

- **Sem travessão `—`**: U+2014 não está em `charmap.txt`; use `--`. `“ ”` e `…` podem.
- Vozes do design §3.1. **Ninguém chama a criatura pelo nome** antes do Ato IV.
- Larguras de linha: conferir com a ferramenta da skill `nomear-falante`.

---

## 7. Etapa D — a fenda: o único objeto que este evento deixa para o futuro

`LOCALID_SUN_MOON_ALTAR_RIFT` em (14,10) é **o mesmo objeto** no clímax e no
loop diário. O autor pediu explicitamente que fosse reusável ("a gente vai
reusar isso"), e o script tem exatamente três ramos.

```asm
@ ---------------------------------------------------------------------------
@ The rift. One object, three lives:
@   14        the climax: Ultra Necrozma is on the other side
@   15        transient: it has been harmonised but the farewell has not played
@   >= 16     the daily expedition (the LOOP document starts here)
@ Its visibility is ON_TRANSITION's job (section 4.5); this script only
@ decides what happens when the player faces it and presses A.
@ It stands ON (14,10) and the player stands at (14,11) - an object event
@ always blocks its own tile, exactly like the four portals of SpearPillarTop.
@ ---------------------------------------------------------------------------
SunMoonAltar_EventScript_Rift::
	lock
	goto_if_ge VAR_RIFT_MISSIONS_STATE, 16, SunMoonAltar_EventScript_RiftDaily
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 15, SunMoonAltar_EventScript_RiftSettling
	@ --- state 14: the climax --------------------------------------------
	@ 1. Anabel's rule FIRST, before any offer: party full AND PC full blocks,
	@    because the scene on the other side ends in a givemon and a gift that
	@    silently fails is the worst bug this project knows how to write
	@    (skill entregar-pokemon-ou-ovo). Party full alone does NOT block.
	getpartysize
	goto_if_ne VAR_RESULT, PARTY_SIZE, SunMoonAltar_EventScript_RiftCheckPartner
	specialvar VAR_RESULT, ScriptCheckFreePokemonStorageSpace
	goto_if_eq VAR_RESULT, TRUE, SunMoonAltar_EventScript_RiftCheckPartner
	msgbox SunMoonAltar_Text_RiftNoRoom, MSGBOX_DEFAULT
	closemessage
	release
	end

@ 2. The partner. This is the author's "the only way in is with Solgaleo",
@    and it is a gate, not a puzzle: it costs nothing, changes nothing and is
@    repeatable for ever. checkspecies walks gPlayerParty only - Cosmog,
@    Cosmoem, an egg or the PC do not satisfy it, and that is correct.
SunMoonAltar_EventScript_RiftCheckPartner::
	checkspecies SPECIES_SOLGALEO
	goto_if_eq VAR_RESULT, TRUE, SunMoonAltar_EventScript_RiftAsk
	checkspecies SPECIES_LUNALA
	goto_if_eq VAR_RESULT, TRUE, SunMoonAltar_EventScript_RiftAsk
	msgbox SunMoonAltar_Text_RiftNoPartner, MSGBOX_DEFAULT
	closemessage
	release
	end

@ 3. The last exit point. After the YES everything is scripted through to a
@    battle outcome on the other map.
SunMoonAltar_EventScript_RiftAsk::
	msgbox SunMoonAltar_Text_RiftAsk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SunMoonAltar_EventScript_RiftNotYet
	msgbox SunMoonAltar_Text_RiftGo, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	warpsilent MAP_ULTRA_SPACE_ARENA, 10, 19
	waitstate
	release
	end

SunMoonAltar_EventScript_RiftNotYet::
	msgbox SunMoonAltar_Text_RiftNotYet, MSGBOX_DEFAULT
	closemessage
	release
	end

SunMoonAltar_EventScript_RiftSettling::
	msgbox SunMoonAltar_Text_RiftSettling, MSGBOX_DEFAULT
	release
	end

@ --- state >= 16: the daily expedition --------------------------------------
@ The flag is set ON THE WAY IN, not on the way out, so a player who walks in,
@ turns round and walks out has still used today's rift. That is deliberate:
@ the alternative is a re-entry loop that the LOOP document would have to undo.
@ ON_TRANSITION hides the object as soon as the altar reloads.
SunMoonAltar_EventScript_RiftDaily::
	msgbox SunMoonAltar_Text_RiftDailyAsk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SunMoonAltar_EventScript_RiftDailyNo
	setflag FLAG_DAILY_ALTAR_RIFT
	closemessage
	fadescreen FADE_TO_BLACK
	warpsilent MAP_ULTRA_SPACE_ARENA, 10, 19
	waitstate
	release
	end

SunMoonAltar_EventScript_RiftDailyNo::
	msgbox SunMoonAltar_Text_RiftDailyNo, MSGBOX_DEFAULT
	closemessage
	release
	end
```

> **A regra da Anabel não é reaproveitável do Blackthorn por acaso.** Ela existe
> no arco desde a Missão 1 (`BlackthornCity_EventScript_UBLooker`, `:415-423`)
> justamente porque uma cena de ruptura pode terminar entregando um Pokémon.
> Aqui ela é a **mesma regra**, dita pela mesma pessoa, e é o que faz a checagem
> não parecer um muro técnico. Conferir espaço no altar e não na arena é
> deliberado: a alternativa é o jogador atravessar, ganhar a luta mais difícil do
> jogo e descobrir na última caixa que não pode receber nada.

Textos:

> `RiftNoRoom`
> {SPEAKER NAME_ANABEL}Stop. Look at me.
> Your team is full and every box you own is full. I said room for one more and I meant it as a condition, not as advice.
> Go and make space, and come straight back. The passage has waited a long time. It can wait for a Pokemon Center.
>
> `RiftNoPartner`
> {SPEAKER NAME_ANABEL}Not like that.
> The tear held still when your partner looked at it, and it is holding still now because of the light, and I am not sending anyone in there on a light that is sitting in a box in a Pokemon Center.
> Bring Solgaleo. Or Lunala. Whichever one yours chose to become. Then we go.
>
> `RiftAsk` — **the YES/NO**
> {SPEAKER NAME_LOOKER}One more time, so that it is in the record and in your ears.
> Through there, and then back out through the same tear, and Madame Lusamine, Lillie, Gladion and the professor hold this end open while you do it.
> The Chief goes with you. I do not -- I have no Pokemon for a thing like that, and I have never been more honest about anything.
> Are you ready, {PLAYER}?
>
> `RiftNotYet`
> {SPEAKER NAME_LOOKER}Quite right. Prepare properly.
> I shall be here, holding a notebook and feeling largely decorative.
>
> `RiftGo`
> {SPEAKER NAME_ANABEL}With me, then. Close. Don't stop in the middle of it, whatever it looks like in there.
>
> `RiftSettling` — state 15 only, a few seconds long
> {SPEAKER NAME_KUKUI}Don't touch it! Don't -- okay, don't touch it yet. It's still deciding what shape it wants to be.
>
> `RiftDailyAsk` — **postgame**
> {SPEAKER NAME_ANABEL}It opened again this morning. They always do, now -- once, and then it closes itself by nightfall.
> Looker has a file for each one. I have a Ball for each one.
> Going in?
>
> `RiftDailyNo`
> {SPEAKER NAME_ANABEL}Then it will be here tomorrow. They always are.

---

## 8. Ato IV — `MAP_ULTRA_SPACE_ARENA` (estado 14 → 15)

### 8.1 O que já existe

O mapa existe, 21x21, primário `gTileset_Johto_General` + secundário
`gTileset_UltraSpaceArena`, trilha `MUS_DP_SPEAR_PILLAR`, cena de batalha
`MAP_BATTLE_SCENE_ULTRA_SPACE`, `show_map_name: false`. **Zero objetos.** Tem
três `coord_event` na linha de baixo do tapete, todos apontando para
`UltraSpaceArena_EventScript_SouthRift`, que devolve o jogador ao altar.

Planta (`dump_mapa.py UltraSpaceArena`): uma cruz. Corredor vertical em
x=9..11, alargando para x=8..12 em y=6..7 e y=13..14; a **arena** é a faixa
cheia y=9..11, x=0..20; e a barra horizontal larga em y=8 e y=12 (x=6..14).

```text
      x= 6  7  8  9 10 11 12 13 14
  y= 8     .  .  .  .  N  .  .  .  .   N = a criatura, (10,8)
  y= 9     #  #  .  .  .  .  .  .  .   a arena: a faixa inteira, x=0..20
  y=10     #  #  .  .  .  .  .  .  .
  y=11     #  #  .  .  .  .  .  .  .   A A A = o jogador e a escolta param aqui
  y=12     .  .  .  .  .  .  .  #  #   (x=6..12 andavel: a linha mais larga)
  y=13     #  #  .  .  .  .  .  #  #   (x=8..12)
  y=14     #  #  .  .  .  .  .  #  #
  y=15     #  #  #  .  .  .  #  #  #   (x=9..11: o corredor estreito)
  ...
  y=19     #  #  #  .  P  .  #  #  #   P = chegada do jogador, (10,19)
  y=20     #  #  #  R  R  R  #  #  #   R = os tres coord_event de volta
```

### 8.2 Objetos novos — `data/maps/UltraSpaceArena/map.json`

Cinco, todos com flag temporária própria, todos escondidos no load e mostrados
só pela cena:

| `local_id` | Gráfico | x,y | `movement_type` | `script` | `flag` |
|---|---|---|---|---|---|
| `..._ANABEL` | `OBJ_EVENT_GFX_ANABEL` | 11,19 | `FACE_UP` | `UltraSpaceArena_EventScript_Anabel` | `FLAG_TEMP_1` |
| `..._NECROZMA` | `OBJ_EVENT_GFX_SPECIES(NECROZMA)` | 10,8 | `FACE_DOWN` | `NULL` | `FLAG_TEMP_2` |
| `..._ULTRA` | `OBJ_EVENT_GFX_SPECIES(NECROZMA_ULTRA)` | 10,8 | `FACE_DOWN` | `NULL` | `FLAG_TEMP_3` |
| `..._SOLGALEO` | `OBJ_EVENT_GFX_SPECIES(SOLGALEO)` | 9,19 | `FACE_UP` | `NULL` | `FLAG_TEMP_4` |
| `..._LUNALA` | `OBJ_EVENT_GFX_SPECIES(LUNALA)` | 9,19 | `FACE_UP` | `NULL` | `FLAG_TEMP_5` |

Os dois Necrozma dividem o tile (10,8) e os dois lendários dividem (9,19), pelo
mesmo motivo do altar: só um de cada par existe por vez, e flags separadas são o
que garante isso. Os gráficos dos quatro Pokémon existem
(`graphics/pokemon/{necrozma,necrozma/ultra,solgaleo,lunala}/overworld.png`) e
`OBJ_EVENT_GFX_SPECIES(NECROZMA_ULTRA)` já está em uso em `NewBarkTown`.

> **Atenção (revisão 5).** O PNG existir e o `OBJ_EVENT_GFX_SPECIES` estar em
> uso em outro mapa **não** provam que o sprite aparece: até a revisão 5 os dois
> mapas desenhavam o boneco do Substitute, porque a ligação de overworld do
> `SPECIES_NECROZMA_ULTRA` estava desligada por config. Ver **§19**.

Os três `coord_event` que já existem em (9..11, 20) **não mudam**: continuam
sendo a saída, e continuam apontando para `UltraSpaceArena_EventScript_SouthRift`
(que precisa de uma correção de uma linha, §14 achado 3).

```asm
UltraSpaceArena_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, UltraSpaceArena_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, UltraSpaceArena_OnFrame
	.byte 0

@ Everything in this map is hidden on every load, unconditionally. The only
@ thing that shows an object here is a scene, and the only scene here is the
@ confrontation. This is what makes the blackout retry free: the player wakes
@ up in a Pokemon Center, sails back, walks into the rift again, and the map
@ is exactly as it was the first time.
UltraSpaceArena_OnTransition::
	setflag FLAG_TEMP_1
	setflag FLAG_TEMP_2
	setflag FLAG_TEMP_3
	setflag FLAG_TEMP_4
	setflag FLAG_TEMP_5
	end

UltraSpaceArena_OnFrame::
	map_script_2 VAR_TEMP_1, 0, UltraSpaceArena_EventScript_ArrivalTrigger
	.2byte 0
```

**Por que gatilho de frame e não `coord_event`.** A coreografia deste ato
precisa saber **exatamente** onde o jogador está, porque a Anabel e o parceiro
sobem o corredor em colunas vizinhas e param ao lado dele. Um `coord_event`
numa linha de três tiles deixa três posições possíveis e uma delas coloca um
NPC em cima do jogador. O gatilho de frame dispara **no load**, quando o
jogador ainda está obrigatoriamente no tile do warp (10,19) — é o mesmo padrão
de `OlivineCity_House1`, com `getplayerxy` de guarda pelo mesmo motivo.

### 8.3 A cena, até a batalha

```asm
@ ---------------------------------------------------------------------------
@ ACT IV. Fires on the load that follows the warp from the altar rift.
@ The rift is the ONLY way into this map, and it always lands the player on
@ (10,19) facing up, so the getplayerxy guard is belt-and-braces, not logic:
@ if some future entrance lands elsewhere, the scene declines instead of
@ walking two NPCs into a wall.
@ VAR_TEMP_1 is the once-per-visit latch and is set FIRST (livelock rule).
@ ---------------------------------------------------------------------------
UltraSpaceArena_EventScript_ArrivalTrigger::
	setvar VAR_TEMP_1, 1                        @ first instruction
	getplayerxy VAR_0x8004, VAR_0x8005
	goto_if_ne VAR_0x8004, 10, UltraSpaceArena_EventScript_End
	goto_if_ne VAR_0x8005, 19, UltraSpaceArena_EventScript_End
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 14, UltraSpaceArena_EventScript_Confront
	goto_if_ge VAR_RIFT_MISSIONS_STATE, 16, UltraSpaceArena_EventScript_EmptyRift
UltraSpaceArena_EventScript_End::
	end

@ State >= 16: the daily rift, with nothing in it yet. One box, no lock, no
@ objects, no state. THIS IS THE HANDOFF TO THE LOOP DOCUMENT - replacing this
@ script is the first thing that document does.
@ SKELETON: the expedition itself (five trainers + a legendary, design 10) is
@ not in this document. Deliberate scope, requested by the author.
UltraSpaceArena_EventScript_EmptyRift::
	lockall
	msgbox UltraSpaceArena_Text_EmptyRift, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

@ Choreography, measured on dump_mapa.py UltraSpaceArena:
@   player  (10,19) -> walk_up x8 -> (10,11), facing up
@   Anabel  addobject (11,19) -> walk_up x7 -> (11,12) -> walk_up -> (11,11)
@   partner addobject (9,19)  -> same, ending on (9,11)
@ The three end up abreast on y=11, the bottom row of the arena. The corridor
@ is exactly three tiles wide (x=9..11) from y=15 to y=19, so the three
@ columns never cross and nobody has to path around anybody.
@ The creature is at (10,8), three rows north of the player: inside the frame
@ (the camera shows about four rows above) and clear of the text box.
UltraSpaceArena_EventScript_Confront::
	lockall
	hidefollower
	delay 20
	call UltraSpaceArena_EventScript_ShowEscort
	applymovement OBJ_EVENT_ID_PLAYER, UltraSpaceArena_Movement_PlayerUp
	applymovement LOCALID_ULTRA_SPACE_ARENA_ANABEL, UltraSpaceArena_Movement_EscortUp
	call UltraSpaceArena_EventScript_MovePartnerUp
	waitmovement OBJ_EVENT_ID_PLAYER
	waitmovement LOCALID_ULTRA_SPACE_ARENA_ANABEL
	call UltraSpaceArena_EventScript_WaitPartner
	msgbox UltraSpaceArena_Text_ArenaLook, MSGBOX_DEFAULT
	closemessage
	@ --- it is already here, and it is not what New Bark left --------------
	fadescreenswapbuffers FADE_TO_WHITE
	addobject LOCALID_ULTRA_SPACE_ARENA_NECROZMA
	fadescreenswapbuffers FADE_FROM_WHITE
	playmoncry SPECIES_NECROZMA, CRY_MODE_ENCOUNTER
	waitmoncry
	msgbox UltraSpaceArena_Text_ArenaAnabelReads, MSGBOX_DEFAULT
	closemessage
	msgbox UltraSpaceArena_Text_ArenaStarving, MSGBOX_DEFAULT
	closemessage
	@ --- the partner steps in front, and it takes the light ---------------
	call UltraSpaceArena_EventScript_PartnerSteps
	call UltraSpaceArena_EventScript_Shake
	fadescreenswapbuffers FADE_TO_WHITE
	removeobject LOCALID_ULTRA_SPACE_ARENA_NECROZMA
	addobject LOCALID_ULTRA_SPACE_ARENA_ULTRA
	fadescreenswapbuffers FADE_FROM_WHITE
	playmoncry SPECIES_NECROZMA_ULTRA, CRY_MODE_ENCOUNTER
	waitmoncry
	msgbox UltraSpaceArena_Text_ArenaUltra, MSGBOX_DEFAULT
	closemessage
	@ --- Anabel gets in front of him, once, the way she always does --------
	@ (11,11) -> (11,10): one row up, beside the player's column, NOT on it.
	applymovement LOCALID_ULTRA_SPACE_ARENA_ANABEL, Common_Movement_WalkUp
	waitmovement LOCALID_ULTRA_SPACE_ARENA_ANABEL
	msgbox UltraSpaceArena_Text_ArenaAnabelFront, MSGBOX_DEFAULT
	closemessage
	msgbox UltraSpaceArena_Text_ArenaAnabelRead, MSGBOX_DEFAULT
	closemessage
	@ Revision 2, author's request: she says where the Beast Ball came from,
	@ BEFORE the fight, not after. It is the only place in the whole arc where
	@ anybody explains that item, and it is the hook for the Kurt document.
	@ No giveitem here: she does not hand one over. She says she asked for them.
	msgbox UltraSpaceArena_Text_ArenaAnabelBall, MSGBOX_DEFAULT
	closemessage
	msgbox UltraSpaceArena_Text_ArenaAnabelBallTwo, MSGBOX_DEFAULT
	closemessage
	@ Revision 2 (section 15, risk 1): she steps BACK to her anchor tile
	@ (11,10) -> (11,11) and does not move again for the rest of the act. This
	@ is the in-fiction reason she does not battle: from here on her hands are
	@ holding the way home open. Everything after this box moves the player,
	@ the partner or the creature - NEVER her.
	applymovement LOCALID_ULTRA_SPACE_ARENA_ANABEL, Common_Movement_WalkDown
	waitmovement LOCALID_ULTRA_SPACE_ARENA_ANABEL
	turnobject LOCALID_ULTRA_SPACE_ARENA_ANABEL, DIR_SOUTH
	msgbox UltraSpaceArena_Text_ArenaAnabelAnchor, MSGBOX_DEFAULT
	closemessage
	turnobject LOCALID_ULTRA_SPACE_ARENA_ANABEL, DIR_NORTH
	msgbox UltraSpaceArena_Text_ArenaAnabelAnchorTwo, MSGBOX_DEFAULT
	closemessage
	goto UltraSpaceArena_EventScript_Battle

@ Exactly one legendary, chosen by the party, and its own movement/wait pair.
@ The partner's flags are FLAG_TEMP_4 and FLAG_TEMP_5, so nothing it does can
@ touch Anabel or either Necrozma.
@ waitmovement 0 is NEVER used here: with two actors moving it waits for only
@ one of them (skill parceiro-pokemon-de-npc).
UltraSpaceArena_EventScript_ShowEscort::
	addobject LOCALID_ULTRA_SPACE_ARENA_ANABEL
	specialvar VAR_RESULT, CheckMysteryEggPokemon
	copyvar VAR_TEMP_4, VAR_RESULT
	goto_if_eq VAR_TEMP_4, SPECIES_LUNALA, UltraSpaceArena_EventScript_ShowLunala
	addobject LOCALID_ULTRA_SPACE_ARENA_SOLGALEO
	return
UltraSpaceArena_EventScript_ShowLunala::
	addobject LOCALID_ULTRA_SPACE_ARENA_LUNALA
	return

UltraSpaceArena_EventScript_MovePartnerUp::
	goto_if_eq VAR_TEMP_4, SPECIES_LUNALA, UltraSpaceArena_EventScript_MoveLunalaUp
	applymovement LOCALID_ULTRA_SPACE_ARENA_SOLGALEO, UltraSpaceArena_Movement_EscortUp
	return
UltraSpaceArena_EventScript_MoveLunalaUp::
	applymovement LOCALID_ULTRA_SPACE_ARENA_LUNALA, UltraSpaceArena_Movement_EscortUp
	return

UltraSpaceArena_EventScript_WaitPartner::
	goto_if_eq VAR_TEMP_4, SPECIES_LUNALA, UltraSpaceArena_EventScript_WaitLunala
	waitmovement LOCALID_ULTRA_SPACE_ARENA_SOLGALEO
	return
UltraSpaceArena_EventScript_WaitLunala::
	waitmovement LOCALID_ULTRA_SPACE_ARENA_LUNALA
	return

@ The partner walks two tiles up its own column, to (9,9), ending BESIDE the
@ creature's column instead of on it, and turns east to face it. It is putting
@ itself between the thing and the player, and it does it without being told.
UltraSpaceArena_EventScript_PartnerSteps::
	goto_if_eq VAR_TEMP_4, SPECIES_LUNALA, UltraSpaceArena_EventScript_LunalaSteps
	applymovement LOCALID_ULTRA_SPACE_ARENA_SOLGALEO, UltraSpaceArena_Movement_PartnerForward
	waitmovement LOCALID_ULTRA_SPACE_ARENA_SOLGALEO
	playmoncry SPECIES_SOLGALEO, CRY_MODE_ENCOUNTER
	waitmoncry
	return
UltraSpaceArena_EventScript_LunalaSteps::
	applymovement LOCALID_ULTRA_SPACE_ARENA_LUNALA, UltraSpaceArena_Movement_PartnerForward
	waitmovement LOCALID_ULTRA_SPACE_ARENA_LUNALA
	playmoncry SPECIES_LUNALA, CRY_MODE_ENCOUNTER
	waitmoncry
	return

UltraSpaceArena_Movement_PlayerUp:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	face_up
	step_end

UltraSpaceArena_Movement_EscortUp:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	face_up
	step_end

UltraSpaceArena_Movement_PartnerForward:
	walk_up
	walk_up
	face_right
	step_end

@ Same four vars as the altar and as the four mission maps.
UltraSpaceArena_EventScript_Shake::
	setvar VAR_0x8004, 1    @ vertical pan
	setvar VAR_0x8005, 1    @ horizontal pan
	setvar VAR_0x8006, 12   @ num shakes
	setvar VAR_0x8007, 4    @ shake delay
	special ShakeCamera
	waitstate
	return
```

> **Conferir as contagens de `walk_up` no `dump_mapa.py` antes de compilar.**
> Oito tiles de (10,19) a (10,11) é o que o `map.bin` de hoje permite; se o
> autor retocar a arena como retocou o altar, a conta muda e o NPC trava contra
> parede **sem erro de build**.

### 8.4 A boss battle

```asm
@ ---------------------------------------------------------------------------
@ THREAT battle, not a character duel: B_FLAG_NO_WHITEOUT is deliberately NOT
@ set. Losing is a blackout and a retry, which is the arc's rule from
@ Blackthorn on (design section 11).
@ Difficulty, continuing the scale: M1 3 bars/Lv75/x120, M2 4/Lv80/x130,
@ M3 4/x140, M4 4/x150, and this one 5/Lv90/x160 with a phase profile.
@ It is the only battle in the arc with a phase profile, and it should be.
@ B_FLAG_NO_CATCHING: the fight is a fight. The capture is a scene (8.5), and
@ that is what makes "beat it but fail to catch it" impossible - the design's
@ section 9 requirement that a lost catch can never make Necrozma unavailable.
@ ---------------------------------------------------------------------------
UltraSpaceArena_EventScript_Battle::
	setflag B_FLAG_NO_CATCHING                  @ cleared by the engine after the battle
	setbossbattle 5, SPECIES_NONE, 160, BOSS_PHASE_PROFILE_NECROZMA
	playmoncry SPECIES_NECROZMA_ULTRA, CRY_MODE_ENCOUNTER
	waitmoncry
	seteventmon SPECIES_NECROZMA_ULTRA, 90, ITEM_NONE
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	copyvar VAR_TEMP_2, VAR_RESULT
	goto_if_eq VAR_TEMP_2, B_OUTCOME_WON, UltraSpaceArena_EventScript_Victory
	goto UltraSpaceArena_EventScript_Unresolved

@ LOST, DREW and FORFEITED never come back here: the engine blacks the player
@ out. CAUGHT and RAN are unreachable (the ball is blocked, and Run in a boss
@ becomes FORFEITED) but are handled anyway: anything that is not WON resets
@ the scene, never wins it. Nothing is recorded, the state is still 14, and
@ ON_TRANSITION puts this map back the way it was.
UltraSpaceArena_EventScript_Unresolved::
	msgbox UltraSpaceArena_Text_Unresolved, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	warpsilent MAP_SUN_MOON_ALTAR, 14, 11
	waitstate
	releaseall
	end
```

**`seteventmonmoves` é dispensável aqui, e isso é fato do motor, não opinião.**
`TryStartBossBattle` (`src/battle_boss.c:735`) aplica `profile->phases[0]` — 
espécie **e** golpes — no começo da batalha. Escrever `seteventmonmoves`
também só criaria duas fontes de verdade para o mesmo moveset.

**O perfil de fases — `src/battle_boss.c`:**

```c
#if P_FAMILY_NECROZMA
static const struct BossPhase sNecrozmaBossPhases[] =
{
    {
        .species = SPECIES_NECROZMA_ULTRA,
        .moves = {MOVE_PHOTON_GEYSER, MOVE_PRISMATIC_LASER, MOVE_EARTH_POWER, MOVE_AUTOTOMIZE},
    },
    {
        .species = SPECIES_NECROZMA_ULTRA,
        .moves = {MOVE_PHOTON_GEYSER, MOVE_PRISMATIC_LASER, MOVE_SMART_STRIKE, MOVE_CALM_MIND},
    },
    {
        .species = SPECIES_NECROZMA_ULTRA,
        .moves = {MOVE_PHOTON_GEYSER, MOVE_PRISMATIC_LASER, MOVE_POWER_GEM, MOVE_EARTH_POWER},
    },
    {
        // The armour comes off. Weaker, and it starts trying to heal.
        .species = SPECIES_NECROZMA,
        .moves = {MOVE_PHOTON_GEYSER, MOVE_POWER_GEM, MOVE_CALM_MIND, MOVE_MORNING_SUN},
    },
    {
        .species = SPECIES_NECROZMA,
        .moves = {MOVE_PHOTON_GEYSER, MOVE_POWER_GEM, MOVE_EARTH_POWER, MOVE_MORNING_SUN},
    },
};

static const struct BossPhaseProfile sNecrozmaBossProfile =
{
    .baseSpecies = SPECIES_NECROZMA,
    .phaseCount = ARRAY_COUNT(sNecrozmaBossPhases),
    .phases = sNecrozmaBossPhases,
};
#endif
```

mais um `case BOSS_PHASE_PROFILE_NECROZMA: return &sNecrozmaBossProfile;` em
`GetBossPhaseProfile` (`:357`), entre `#if P_FAMILY_NECROZMA`.

Três checagens do motor que este perfil **precisa** passar
(`IsBossPhaseProfileValid`, `:552`) — se qualquer uma falhar, o perfil é
descartado em silêncio e a luta vira um boss comum de cinco barras, sem erro
nenhum:

1. `phaseCount == totalBars`. **Cinco fases ⇔ `setbossbattle 5`.** Mudar um sem
   o outro desliga o perfil.
2. `GET_BASE_SPECIES_ID(species do battler) == profile->baseSpecies`. As quatro
   formas de Necrozma têm base `SPECIES_NECROZMA`, então `seteventmon
   SPECIES_NECROZMA_ULTRA` casa.
3. Toda espécie de fase tem de estar habilitada (`IsSpeciesEnabled`) e ter a
   mesma base. `P_FAMILY_NECROZMA` cobre as quatro.

**A ideia da luta, em uma frase:** a criatura não escala, ela **descasca**. As
três primeiras barras são a coisa de New Bark, com a armadura de luz inteira; na
quarta a armadura cai e o que sobra é um Necrozma pequeno, mais fraco, que passa
a gastar turnos tentando se curar. A dificuldade cai de propósito na reta final,
e é aí que a cena muda de "você está sobrevivendo" para "você está olhando para
uma coisa faminta".

**A trilha.** `case SPECIES_NECROZMA ... SPECIES_NECROZMA_ULTRA:` no `switch` de
`BattleSetup_StartLegendaryBattle` → `CreateBattleStartTask(B_TRANSITION_BLUR,
MUS_DP_VS_DIALGA_PALKIA)`. Sem isso a luta mais importante do jogo entra com a
música de batalha selvagem comum.

### 8.5 A captura, que é cutscene

```asm
@ ---------------------------------------------------------------------------
@ The player won. Everything from here is scripted; there is no way to lose
@ the Pokemon from this point, which is exactly what the design's section 9
@ asks for ("nao pode tornar Necrozma permanentemente indisponivel").
@ Party space was checked at the rift, before the player ever crossed
@ (section 7), and the defensive guard below covers the impossible case.
@ ---------------------------------------------------------------------------
UltraSpaceArena_EventScript_Victory::
	fadescreenswapbuffers FADE_TO_WHITE
	removeobject LOCALID_ULTRA_SPACE_ARENA_ULTRA
	addobject LOCALID_ULTRA_SPACE_ARENA_NECROZMA
	fadescreenswapbuffers FADE_FROM_WHITE
	playmoncry SPECIES_NECROZMA, CRY_MODE_ENCOUNTER
	waitmoncry
	msgbox UltraSpaceArena_Text_VictoryArmourOff, MSGBOX_DEFAULT
	closemessage
	msgbox UltraSpaceArena_Text_VictoryAnabel, MSGBOX_DEFAULT
	closemessage
	@ --- the partner does the thing nobody planned ------------------------
	call UltraSpaceArena_EventScript_PartnerHarmonise
	msgbox UltraSpaceArena_Text_VictoryHarmony, MSGBOX_DEFAULT
	closemessage
	msgbox UltraSpaceArena_Text_VictoryBall, MSGBOX_DEFAULT
	closemessage
	@ --- the capture -------------------------------------------------------
	givemon SPECIES_NECROZMA, 75, ITEM_NONE
	goto_if_eq VAR_RESULT, MON_CANT_GIVE, UltraSpaceArena_EventScript_NoRoom
	call Common_EventScript_GiftMon
	playfanfare MUS_HG_CAUGHT
	waitfanfare
	msgbox UltraSpaceArena_Text_VictoryCaught, MSGBOX_DEFAULT
	closemessage
	fadescreenswapbuffers FADE_TO_WHITE
	removeobject LOCALID_ULTRA_SPACE_ARENA_NECROZMA
	fadescreenswapbuffers FADE_FROM_WHITE
	msgbox UltraSpaceArena_Text_VictoryLeave, MSGBOX_DEFAULT
	closemessage
	goto UltraSpaceArena_EventScript_NecrozmaCaught

@ Should be unreachable: the rift refused to let a full player through. It is
@ here because a gift that fails silently is the worst bug this project knows
@ how to write, and because a future edit could move the check.
@ NOTHING is marked: the state stays 14, the player is sent back to the altar,
@ and the whole act is replayable. No progress is lost.
UltraSpaceArena_EventScript_NoRoom::
	msgbox UltraSpaceArena_Text_NoRoom, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	warpsilent MAP_SUN_MOON_ALTAR, 14, 11
	waitstate
	releaseall
	end

@ State and warp together, under the fade, in the arc's order.
@ (14,11) is free, elevation 3, one tile SOUTH of the rift at (14,10) - so
@ the player comes out of the tear facing it, and does not respawn inside the
@ object. The altar's ON_TRANSITION then paints state 15: cast visible, ash
@ still falling, rift still there, disc still a hole.
UltraSpaceArena_EventScript_NecrozmaCaught::
	fadescreen FADE_TO_BLACK
	setvar VAR_RIFT_MISSIONS_STATE, 15
	warpsilent MAP_SUN_MOON_ALTAR, 14, 11
	waitstate
	releaseall
	end

@ Two tiles east, onto the creature's column, and it stays there: it is
@ holding the passage open from the inside while everyone leaves.
UltraSpaceArena_EventScript_PartnerHarmonise::
	bufferspeciesname STR_VAR_1, VAR_TEMP_4   @ Text_VictoryHarmony prints it
	goto_if_eq VAR_TEMP_4, SPECIES_LUNALA, UltraSpaceArena_EventScript_LunalaHarmonise
	applymovement LOCALID_ULTRA_SPACE_ARENA_SOLGALEO, UltraSpaceArena_Movement_PartnerHarmonise
	waitmovement LOCALID_ULTRA_SPACE_ARENA_SOLGALEO
	playmoncry SPECIES_SOLGALEO, CRY_MODE_ENCOUNTER
	waitmoncry
	call UltraSpaceArena_EventScript_Shake
	return
UltraSpaceArena_EventScript_LunalaHarmonise::
	applymovement LOCALID_ULTRA_SPACE_ARENA_LUNALA, UltraSpaceArena_Movement_PartnerHarmonise
	waitmovement LOCALID_ULTRA_SPACE_ARENA_LUNALA
	playmoncry SPECIES_LUNALA, CRY_MODE_ENCOUNTER
	waitmoncry
	call UltraSpaceArena_EventScript_Shake
	return

UltraSpaceArena_Movement_PartnerHarmonise:
	walk_up
	face_down
	step_end
```

> **`givemon SPECIES_NECROZMA, 75`, não `SPECIES_NECROZMA_ULTRA`.** O design §9
> manda não presumir que a forma Ultra pode ser guardada, e o motor concorda: as
> formas Ultra/Dusk Mane/Dawn Wings são formas de batalha. Nível 75 e não 90
> porque o que o jogador recebe é a criatura **depois** de perder a luz — dar
> nível 90 seria entregar o boss, não o que sobrou dele.
>
> **`Common_EventScript_GiftMon` engole `MON_CANT_GIVE` em silêncio**
> (`data/event_scripts.s:1152`). Por isso a guarda `goto_if_eq VAR_RESULT,
> MON_CANT_GIVE` vem **antes** da `call`, e não depois. Comparar não suja
> `VAR_RESULT`, então a `call` continua vendo o resultado do `givemon`.

### 8.6 A surpresa deste evento

O arco guardou uma surpresa por missão: o Gladion em Blackthorn, a Lillie em
Mahogany, o Incineroar do Kukui em Cherrygrove, a forma Ultra em New Bark. A
deste evento **não é um personagem** — é o que a criatura acaba sendo.

Durante quatro missões ela coletou nove Ultra Beasts e ninguém entendeu por quê.
A resposta, e ela só aparece aqui, é a mais simples possível: **estava com
fome.** A luz que ela toma é comida, a armadura que ela veste é o que ela comeu,
e o motivo de ela ter hesitado diante de um Cosmog em New Bark (V22) é que
aquilo não era uma refeição — era a coisa que ela costumava ser.

Regras do §3 da skill `evoluir-historia-de-evento` que isso obedece:

- **Ninguém anuncia antes.** Nenhuma caixa das quatro missões, nem da reunião,
  nem do Ato I, usa a palavra "fome" ou explica a coleta. Conferir com
  `grep -rn "hungry\|starving\|feeding" data/maps/` antes de escrever.
- **Quem descobre é quem tem direito de descobrir.** A Anabel diz o que
  **observa** ("it is not attacking, it is eating"), a Lusamine diz o que
  aquilo significa **para ela**, e ninguém prevê nada (design §3.3).
- **A revelação não interrompe o jogo.** Ela acontece em duas caixas antes da
  luta e uma depois, e a luta é a mesma de qualquer jeito.

### 8.7 Textos do Ato IV

Todas as falas da arena — a subida, a leitura da Anabel, o Ultra Necrozma, a
Beast Ball, a âncora, a derrota, a vitória e a captura — estão em [`ALTAR_SUN_MOON_SCRIPT.md`](ALTAR_SUN_MOON_SCRIPT.md),
"Ato IV" e "Ato IV-b".

Regras que qualquer reescrita precisa respeitar:

- **Sem travessão `—`**: U+2014 não está em `charmap.txt`; use `--`. `“ ”` e `…` podem.
- Vozes do design §3.1. **Ninguém chama a criatura pelo nome** antes do Ato IV.
- Larguras de linha: conferir com a ferramenta da skill `nomear-falante`.

---

## 9. Ato V — a despedida (estado 15 → 16)

O jogador sai da fenda em (14,11), no pátio, com o elenco inteiro em volta e o
altar ainda instável. Os `coord_event` da escada **não** servem aqui: o jogador
não passou pela escada. Esta é a cena do gatilho de frame declarado em §4.6.

```asm
@ Fires on the load that follows the warp back from the arena, which always
@ lands the player on (14,11). VAR_TEMP_1 is this trigger's own latch, and it
@ is NOT the var the stair coord_events use - see the box in section 4.6 for
@ what sharing it would break.
@ Every other state falls through in two instructions.
SunMoonAltar_EventScript_FrameTrigger::
	setvar VAR_TEMP_1, 1                        @ first instruction
	goto_if_ne VAR_RIFT_MISSIONS_STATE, 15, SunMoonAltar_EventScript_End
	getplayerxy VAR_0x8004, VAR_0x8005
	goto_if_ne VAR_0x8004, 14, SunMoonAltar_EventScript_End
	goto_if_ne VAR_0x8005, 11, SunMoonAltar_EventScript_End
	goto SunMoonAltar_EventScript_Farewell
SunMoonAltar_EventScript_End::
	end
```

**Os outros três loads que este gatilho atende sem fazer nada**, e é por isso que
ele é seguro: o `warpsilent` do Ato III (estado 14, jogador em (14,14)), o de
`Unresolved`/`NoRoom` (estado 14, jogador em (14,11) — morre no teste de estado,
não no de posição) e o do próprio Ato V (estado 16). Nenhum deles casa.

### 9.1 A cena

A ordem das caixas é o argumento da cena, e ela é a de sempre no arco: **as
pessoas antes do relatório**.

```asm
@ ---------------------------------------------------------------------------
@ ACT V. State 15 -> 16. Positions on entry are the templates (the map
@ reloaded when the player came back): Lusamine (14,9), Lillie (12,11),
@ Ninetales (11,11), Gladion (16,11), Silvally (17,11), Looker (13,13),
@ Anabel (15,13), Kukui (10,14), rift (14,10), player (14,11).
@
@ Note who is standing where: the player is BETWEEN the rift and everybody
@ else, and Lusamine is on the far side of the rift. Nobody moves for the
@ first half of the scene, because the picture is already right.
@ ---------------------------------------------------------------------------
SunMoonAltar_EventScript_Farewell::
	lockall
	hidefollower
	delay 20
	@ --- Looker, always, first ---------------------------------------------
	msgbox SunMoonAltar_Text_FarewellHurt, MSGBOX_DEFAULT
	closemessage
	msgbox SunMoonAltar_Text_FarewellShowThem, MSGBOX_DEFAULT
	closemessage
	@ --- what the player brought back --------------------------------------
	call SunMoonAltar_EventScript_ShowPartner
	msgbox SunMoonAltar_Text_FarewellKukui, MSGBOX_DEFAULT
	closemessage
	msgbox SunMoonAltar_Text_FarewellLillie, MSGBOX_DEFAULT
	closemessage
	msgbox SunMoonAltar_Text_FarewellGladion, MSGBOX_DEFAULT
	closemessage
	@ --- Lusamine comes down, for the last time ----------------------------
	applymovement LOCALID_SUN_MOON_ALTAR_LUSAMINE, SunMoonAltar_Movement_LusamineAside
	waitmovement LOCALID_SUN_MOON_ALTAR_LUSAMINE
	msgbox SunMoonAltar_Text_FarewellLusamine, MSGBOX_DEFAULT
	closemessage
	msgbox SunMoonAltar_Text_FarewellLusamineAsks, MSGBOX_DEFAULT
	closemessage
	msgbox SunMoonAltar_Text_FarewellLillieAnswers, MSGBOX_DEFAULT
	closemessage
	@ --- the altar comes back ----------------------------------------------
	fadeoutbgm 4
	call SunMoonAltar_EventScript_Shake
	fadescreenswapbuffers FADE_TO_WHITE
	call SunMoonAltar_EventScript_DiscToCalm
	fadescreenswapbuffers FADE_FROM_WHITE
	setweather WEATHER_NONE
	doweather
	delay 40
	msgbox SunMoonAltar_Text_FarewellCalm, MSGBOX_DEFAULT
	closemessage
	@ --- but not all the way back -------------------------------------------
	playse SE_WARP_IN
	msgbox SunMoonAltar_Text_FarewellStillThere, MSGBOX_DEFAULT
	closemessage
	msgbox SunMoonAltar_Text_FarewellAnabelStays, MSGBOX_DEFAULT
	closemessage
	msgbox SunMoonAltar_Text_FarewellLookerStays, MSGBOX_DEFAULT
	closemessage
	msgbox SunMoonAltar_Text_FarewellGoodbye, MSGBOX_DEFAULT
	closemessage
	goto SunMoonAltar_EventScript_FarewellDone

@ Lusamine steps off the disc's column onto (13,9) and turns to the group,
@ which is the whole point of her line: for the first time in the event she is
@ not looking at the door.
SunMoonAltar_Movement_LusamineAside:
	walk_left
	face_down
	step_end

@ The map's population changes completely: five visitors and the two partners
@ leave for good, the rift becomes a daily thing, the weather and the disc are
@ already correct but only in RAM. Reload in place and let ON_TRANSITION build
@ state 16 from scratch - which is also what stops the player from seeing
@ seven objects vanish one at a time as the camera moves.
@ (14,11) again: it is where the player already is, and it is not a warp.
SunMoonAltar_EventScript_FarewellDone::
	fadescreen FADE_TO_BLACK
	setvar VAR_RIFT_MISSIONS_STATE, 16
	warpsilent MAP_SUN_MOON_ALTAR, 14, 11
	waitstate
	releaseall
	end
```

> **Nenhum `removeobject` no elenco que vai embora.** Sete objetos partem nesta
> cena e todos partem pelo `warpsilent`: `FLAG_TEMP_1` volta a ser setada no load
> e eles simplesmente não spawnam. Um `removeobject` na Lillie setaria
> `FLAG_TEMP_1` e levaria o Gladion, os dois parceiros e o Kukui junto no meio da
> fala — é a armadilha que o doc do PRÉ-NECROZMA registrou em §1.3 e que continua
> valendo aqui palavra por palavra.
>
> **A Lusamine é a única exceção interessante:** ela fica em `FLAG_TEMP_5`, e no
> estado 16 a escala de dias decide se ela está lá. Ou seja, saindo do Ato V ela
> pode literalmente ainda estar no altar no dia seguinte — e isso é o correto,
> não um bug. A fala dela no estado ≥ 16 (§10.3) assume exatamente isso.

### 9.2 Textos do Ato V

Todas as falas da despedida estão em [`ALTAR_SUN_MOON_SCRIPT.md`](ALTAR_SUN_MOON_SCRIPT.md), "Ato V".

Regras que qualquer reescrita precisa respeitar:

- **Sem travessão `—`**: U+2014 não está em `charmap.txt`; use `--`. `“ ”` e `…` podem.
- Vozes do design §3.1. **Ninguém chama a criatura pelo nome** antes do Ato IV.
- Larguras de linha: conferir com a ferramenta da skill `nomear-falante`.

---

## 10. Etapa G — o mundo depois (estado 16, permanente)

### 10.1 A escala de dias da semana — o mecanismo comum

Todas as aparições "de vez em quando" que o autor pediu usam **um** mecanismo:
o dia da semana. Não é sorteio.

**Por que dia da semana e não `random`.** Um sorteio a cada load faz o
personagem piscar: o jogador sai da praia, volta, e a Lillie desapareceu. Para
evitar isso um sorteio precisa de uma var persistente ("o sorteio de hoje") mais
uma daily flag ("já sorteei hoje") — duas alocações e um estado a mais para dar
errado. O dia da semana é estável dentro do dia de graça, é **descobrível** pelo
jogador (é a mecânica dos irmãos dos dias da semana de HGSS, que este jogo é),
e custa uma linha.

`GetDayOfWeek()` já existe e já é usada em produção pelo rádio
(`src/rtc.c:476`, `src/pokegear_radio.c:433`), chama `RtcCalcLocalTime()` por si
mesma e devolve `enum Weekday` (`include/constants/siirtc.h:14`). Falta **uma
linha** para o script poder ler:

```
	def_special GetDayOfWeek          @ data/specials.inc
```

E então, em qualquer `ON_TRANSITION`:

```asm
	specialvar VAR_RESULT, GetDayOfWeek
	goto_if_eq VAR_RESULT, WEEKDAY_TUE, ..._Show
```

**A escala, completa.** Nenhum personagem está em dois lugares no mesmo dia —
conferido linha por linha, e é a única restrição real desta tabela:

| Dia | Altar: Lusamine | Olivine: os cinco | Praia: Kukui | Praia: Lillie + Ninetales | Cianwood: Gladion + Silvally |
|---|---|---|---|---|---|
| Domingo | — | **sim** | — | — | — |
| Segunda | **sim** | — | **sim** | — | — |
| Terça | — | — | **sim** | **sim** | **sim** |
| Quarta | **sim** | — | — | — | **sim** |
| Quinta | — | — | **sim** | **sim** | — |
| Sexta | — | **sim** | — | — | — |
| Sábado | **sim** | — | **sim** | **sim** | **sim** |

Leitura da tabela, que é de propósito:

- **Domingo e sexta são os dias da família.** Os cinco estão na sala de Olivine e
  não há revanche em lugar nenhum. O arco inteiro foi sobre uma família que não
  conseguia ficar no mesmo lugar; dois dias por semana em que a única coisa que
  eles fazem é estar juntos é a recompensa, e ela não precisa de fala nenhuma
  explicando isso.
- **Sábado é o dia cheio:** os quatro disponíveis, nas quatro cidades.
- **Quarta é o dia mais vazio** (Lusamine e Gladion), o que dá ao jogador um
  motivo para aprender a tabela em vez de chutar.

### 10.2 O altar no estado 16

Nada muda de posição: o Looker continua em (13,13) e a Anabel em (15,13), onde
sempre estiveram no `map.json` — eles não "se mudaram para cá", eles simplesmente
nunca voltaram. A Lusamine aparece em (14,9) pela escala. A fenda aparece em
(14,10) quando `FLAG_DAILY_ALTAR_RIFT` está limpa.

Os cinco scripts de objeto que hoje existem no `scripts.inc` (`Lusamine`,
`Lillie`, `Gladion`, `Looker`, `Anabel`, `Kukui`) **passam a ter ramos por
estado**. Os quatro que vão embora (`Lillie`, `Gladion`, `Kukui`) só existem em
12-15 e não precisam de ramo ≥ 16.

```asm
@ Looker: three branches. 12..14 is the crisis, 15 is the few seconds before
@ the farewell, >= 16 is home. He is the one who explains the daily rift the
@ first time and the one who never stops asking about the player's Pokemon.
SunMoonAltar_EventScript_Looker::
	lock
	faceplayer
	goto_if_ge VAR_RIFT_MISSIONS_STATE, 16, SunMoonAltar_EventScript_LookerHome
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 15, SunMoonAltar_EventScript_LookerIdle
	@ Revision 2, author's decision: he heals from state 13 on, not from 16.
	@ 13 and 14 are exactly the states where it matters - the boss retry lands
	@ the player on the mainland, and the boat back passes no Center.
	goto_if_ge VAR_RIFT_MISSIONS_STATE, 13, SunMoonAltar_EventScript_LookerCrisisHeal
	msgbox SunMoonAltar_Text_LookerCrisis, MSGBOX_DEFAULT
	release
	end

@ Same YES/NO as the postgame branch, different opening box: during the crisis
@ he is not being hospitable, he is being a field medic with a kettle.
SunMoonAltar_EventScript_LookerCrisisHeal::
	msgbox SunMoonAltar_Text_LookerCrisis, MSGBOX_DEFAULT
	closemessage
	goto SunMoonAltar_EventScript_LookerHealAsk

@ Free healing from state 13 on, and it is not a convenience: see section 15,
@ risk 2. The altar has no Pokemon Center and the ferry is a long way from one,
@ so the boss retry would otherwise cost two loading screens and a boat ride.
@ Looker checking on everybody's Pokemon before anything else is his single
@ most established behaviour in this entire arc (design section 3.1).
SunMoonAltar_EventScript_LookerHome::
	msgbox SunMoonAltar_Text_LookerHome, MSGBOX_DEFAULT
	closemessage
SunMoonAltar_EventScript_LookerHealAsk::
	msgbox SunMoonAltar_Text_LookerHeal, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SunMoonAltar_EventScript_LookerNoHeal
	closemessage
	call Common_EventScript_OutOfCenterPartyHeal
	msgbox SunMoonAltar_Text_LookerHealed, MSGBOX_DEFAULT
	release
	end

SunMoonAltar_EventScript_LookerNoHeal::
	msgbox SunMoonAltar_Text_LookerNoHeal, MSGBOX_DEFAULT
	release
	end
```

> **`Common_EventScript_OutOfCenterPartyHeal` existe e é o certo aqui:**
> `data/event_scripts.s:774` (`special HealPlayerParty` + `playfanfare MUS_HEAL`
> + `waitfanfare`), já usado pelo repositório em
> `GoldenrodCity_FlowerShop/scripts.inc:732` e em `players_house.inc:392`. Não
> escrever um wrapper novo e não chamar `HealPlayerParty` cru (perde a fanfarra
> e o jogador não sabe se foi curado).

### 10.3 A Anabel não vende nada — ela te manda para Azalea

**Revisão 2, mudança de decisão do autor.** A revisão 1 punha um `pokemart` de
Beast Balls no script dela. Isso sai inteiro, e a razão é boa: o design §3.1 já
avisava para não a transformar em "apenas vendedora de Beast Balls", e a resposta
melhor não era esconder a loja atrás de uma pergunta — era **não ter loja**.

O que fica no lugar é uma informação que o jogador não tinha: **a Beast Ball
existe porque ela pediu.** Ela encomendou a um velho de Azalea, e quem faz é o
Kurt. O papel dela no pós-game é apontar para lá.

```asm
SunMoonAltar_EventScript_Anabel::
	lock
	faceplayer
	goto_if_ge VAR_RIFT_MISSIONS_STATE, 16, SunMoonAltar_EventScript_AnabelHome
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 15, SunMoonAltar_EventScript_AnabelIdle
	msgbox SunMoonAltar_Text_AnabelCrisis, MSGBOX_DEFAULT
	release
	end

@ NO pokemart. Two boxes: what she does here, and where the Balls come from.
@ The second box is the only pointer in the whole game to the Kurt system, so
@ it has to name the man, the town and the fact that it is daily.
SunMoonAltar_EventScript_AnabelHome::
	msgbox SunMoonAltar_Text_AnabelHome, MSGBOX_DEFAULT
	closemessage
	msgbox SunMoonAltar_Text_AnabelKurt, MSGBOX_DEFAULT
	release
	end
```

**O que isso muda no §14 do design.** A pendência "Beast Balls: preço, estoque e
eventual entrega inicial" **não** é mais fechada por este documento: ela migra
inteira para [`KURT_BALL_CRAFT_DESIGN.md`](../../KURT_BALL_CRAFT_DESIGN.md), onde a
Beast Ball passa a ser a receita de nível 10 do Kurt. O acoplamento entre os dois
documentos é **uma caixa de texto**, e nada de estado.

Textos. Substituem `AnabelShopAsk`, `AnabelShopOpen`, `AnabelShopClose` e
`AnabelNoShop` da revisão 1, que deixam de existir — e são os **únicos** textos
de pós-game dela, então §10.9 aponta para cá em vez de repeti-los:

> `AnabelHome`
> {SPEAKER NAME_ANABEL}It opens most mornings, about an hour after the light hits the disc.
> Nine, that we have counted. Nothing has come through yet that needed help, and I am not going to stop being here on the day one does.
> …Looker has started calling it a posting. It is not a posting. I asked for it.
>
> `AnabelKurt` — **the only pointer to the Kurt system in the game**
> {SPEAKER NAME_ANABEL}If you need Beast Balls, don't ask me. I have two left and I am keeping them.
> Ask Kurt, in Azalea. He is the man who invented them, he is the only person alive who can make one, and he will make you a batch a day if you bring him what he needs.
> Tell him I sent you. He will pretend not to remember me and then he will ask after my Pokemon by name.

### 10.4 A Lusamine no altar e a revanche diária

O padrão das quatro revanches é **idêntico** e vale copiar e colar com os nomes
trocados. Modelo, na Lusamine:

```asm
@ Postgame. One box of character, then the rematch if today's daily flag is
@ still clear. A normal trainer battle: losing here is a normal blackout, and
@ that is correct - the narrative duel was in Act II and it is over.
@ trainerbattle_no_intro is used, not trainerbattle_single, because the
@ approach is a conversation and not a line of sight.
SunMoonAltar_EventScript_LusaminePost::
	msgbox SunMoonAltar_Text_LusaminePost, MSGBOX_DEFAULT
	closemessage
	goto_if_set FLAG_DAILY_REMATCH_LUSAMINE, SunMoonAltar_EventScript_LusamineDoneToday
	msgbox SunMoonAltar_Text_LusamineRematchAsk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, SunMoonAltar_EventScript_LusamineRematchNo
	setflag FLAG_DAILY_REMATCH_LUSAMINE          @ set BEFORE the battle
	trainerbattle_no_intro TRAINER_LUSAMINE_ALTAR, SunMoonAltar_Text_LusamineRematchBeaten
	msgbox SunMoonAltar_Text_LusamineRematchAfter, MSGBOX_DEFAULT
	release
	end

SunMoonAltar_EventScript_LusamineRematchNo::
	msgbox SunMoonAltar_Text_LusamineRematchNo, MSGBOX_DEFAULT
	release
	end

SunMoonAltar_EventScript_LusamineDoneToday::
	msgbox SunMoonAltar_Text_LusamineDoneToday, MSGBOX_DEFAULT
	release
	end
```

> **A daily flag é setada ANTES da batalha, não depois.** Depois é inalcançável
> na derrota: o blackout não volta para este script. Setar antes significa que
> perder gasta o dia — que é o comportamento certo para uma revanche e é o que o
> Battle Cafe já faz (`BattleCafe/scripts.pory:1162`).
>
> **Não há `B_FLAG_NO_WHITEOUT` em nenhuma das quatro revanches.** Elas não são
> duelos narrativos: são treinadores de pós-game, e perder para um treinador de
> pós-game é um blackout comum. O contrato "sem blackout" do design §11 fala de
> **duelos de história**, e o duelo de história da Lusamine acabou no Ato II.

### 10.5 Os quatro times de revanche

Todos pós-Liga, seis Pokémon, `AI: Smart Trainer / Prediction` (o mais forte que
o parser aceita hoje — `grep -o "^AI: .*" src/data/trainers.party | sort -u`).
Cada um leva o parceiro de identidade no time, o que nenhuma luta anterior do
arco fez.

| Treinador | Id | Time proposto | Níveis |
|---|---|---|---|
| `TRAINER_LUSAMINE_ALTAR` | 972 | Clefable, Lilligant, Mismagius, Bewear, Milotic, **Nihilego** | 78-80 |
| `TRAINER_KUKUI` | 966 | Lycanroc (Midday), Braviary, Alolan Ninetales, Magnezone, Snorlax, **Incineroar** | 78-80 |
| `TRAINER_LILLIE_POSTGAME` | 973 | Clefable, Comfey, Ribombee, Primarina, Togekiss, **Alolan Ninetales** | 76-78 |
| `TRAINER_GLADION_POSTGAME` | 974 | Lucario, Crobat, Weavile, Zoroark, Umbreon, **Silvally** | 78-80 |

Notas de personagem que os times carregam, e que não são enfeite:

- **A Nihilego da Lusamine é o único Ultra Beast em mão de personagem no jogo, e
  é dela. Aprovada pelo autor na revisão 2.** Não é a fusão de Sun/Moon (o design
  §3.1 proíbe importar isso): é uma das nove que o grupo recolheu, e ela é a
  pessoa da Aether que ficou responsável por ela. **Uma caixa de fala dela na
  revanche tem de dizer isso em voz alta**, para que ninguém leia a presença da
  Nihilego como a fusão: "She is not a trophy and she is not a symptom. She is
  the one the Foundation gave me, and I am the one who has to be worth it.
- **O Incineroar do Kukui é o do Cherrygrove** (§6.3 do design, a surpresa da
  M3). Ele fecha no time da revanche o que naquela cena foi um susto.
- **A Alolan Ninetales da Lillie é a mesma Vulpix da Route 30**, nível 7, cinco
  encontros atrás. É a coisa mais barata e mais eficaz que uma revanche de
  pós-game pode fazer.
- **O Silvally do Gladion é lead na Victory Road** (design §14) e aqui é o
  **último**. Ele deixou de ser a demonstração e passou a ser a resposta.

### 10.6 `OlivineCity_House1`: o Looker e a Anabel vão embora

Esta é a mudança mais delicada do plano, porque **contradiz uma regra escrita**
do documento anterior. Ver §14, achado 4, para a auditoria; aqui está o
resultado.

```asm
@ NOW three independent decisions, not one:
@   FLAG_TEMP_1 - the family: the six reunion visitors in 10..11, and the five
@                 of them again from 16 on, by the weekday rota
@   FLAG_TEMP_2 - Looker and Anabel: present below 16, gone from 16 on
@   FLAG_TEMP_3 - Kukui: present in 10..11 only. He never comes back to this
@                 room; from 16 on he is in Alola, and on some days on a beach
@                 in Cherrygrove
OlivineCity_House1_OnTransition::
	call OlivineCity_House1_EventScript_ApplyReunionVisibility
	call OlivineCity_House1_EventScript_ApplyInvestigatorVisibility
	call OlivineCity_House1_EventScript_ApplyKukuiVisibility
	end

@ FLAG_TEMP_1, rewritten. The old version was two goto_if_eq on 10 and 11 with
@ a comment warning never to use goto_if_ge; that warning still applies and is
@ why the postgame branch is a closed window too.
OlivineCity_House1_EventScript_ApplyReunionVisibility::
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 10, OlivineCity_House1_EventScript_ShowReunionCast
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 11, OlivineCity_House1_EventScript_ShowReunionCast
	goto_if_lt VAR_RIFT_MISSIONS_STATE, 16, OlivineCity_House1_EventScript_HideReunionCast
	specialvar VAR_RESULT, GetDayOfWeek
	goto_if_eq VAR_RESULT, WEEKDAY_SUN, OlivineCity_House1_EventScript_ShowReunionCast
	goto_if_eq VAR_RESULT, WEEKDAY_FRI, OlivineCity_House1_EventScript_ShowReunionCast
OlivineCity_House1_EventScript_HideReunionCast::
	setflag FLAG_TEMP_1
	return
OlivineCity_House1_EventScript_ShowReunionCast::
	clearflag FLAG_TEMP_1
	return

@ Looker and Anabel: the whole game up to the farewell, and then never again.
@ Their map.json "flag" changes from "0" to FLAG_TEMP_2 for this, which means
@ the DEFAULT IS VISIBLE and this block is the only thing that ever removes
@ them. It runs unconditionally on every load.
OlivineCity_House1_EventScript_ApplyInvestigatorVisibility::
	goto_if_ge VAR_RIFT_MISSIONS_STATE, 16, OlivineCity_House1_EventScript_HideInvestigators
	clearflag FLAG_TEMP_2
	return
OlivineCity_House1_EventScript_HideInvestigators::
	setflag FLAG_TEMP_2
	return

OlivineCity_House1_EventScript_ApplyKukuiVisibility::
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 10, OlivineCity_House1_EventScript_ShowKukui
	goto_if_eq VAR_RIFT_MISSIONS_STATE, 11, OlivineCity_House1_EventScript_ShowKukui
	setflag FLAG_TEMP_3
	return
OlivineCity_House1_EventScript_ShowKukui::
	clearflag FLAG_TEMP_3
	return
```

**E o gatilho de frame daquela casa não pode mais disparar no estado 16.** Ele
atende hoje os estados 2, 4, 6, 8, 10 e 11 por `goto_if_eq`, então o 16 já não
casa com nada e a casa vazia não dispara cena nenhuma. **Conferir de novo depois
de editar** — o arquivo tem um histórico documentado de trocar `goto_if_eq` por
`goto_if_ge` por engano três vezes.

**As falas da sala no estado ≥ 16.** Os cinco objetos da família ganham um ramo
`goto_if_ge VAR_RIFT_MISSIONS_STATE, 16`. Não há batalha nenhuma em Olivine: a
sala é o lugar onde eles **não** estão trabalhando.

> `HouseLusaminePost`
> {SPEAKER NAME_LUSAMINE}The Inspector left us the key and a note asking us not to reorganise anything.
> I have reorganised three things.
> …Sit down, {PLAYER}. Nobody here is going anywhere for several hours, which I understand is what people do.
>
> `HouseLilliePost`
> {SPEAKER NAME_LILLIE}Two days a week. That's what we agreed on -- two days, here, no instruments, no reports.
> The first one was terrible. We all sat in different corners.
> This is the fourth one. It's getting better. It's allowed to take a while.
>
> `HouseGladionPost`
> {SPEAKER NAME_GLADION}I'm not good at this part.
> …Silvally likes it. Look at him. He's asleep under the table where Looker used to put his files.
> If he's fine with it, I'm fine with it. That's the system I'm using.

### 10.7 A praia de Cherrygrove: o Kukui e a Lillie

A praia é a da Missão 3. Os objetos do incidente estavam em (26,7) Kukui, (27,7)
Looker, (28,7) Anabel, com as criaturas em x=22..26 — tudo em `FLAG_TEMP_1`,
`2`, `5` e `6`, e tudo escondido no pós-game. Os objetos novos vão para a mesma
faixa de areia, que `dump_mapa.py CherrygroveCity 18 34 2 16` mostra livre em
y=7 de x=18 a x=34:

| `local_id` | Gráfico | x,y | `movement_type` | `flag` |
|---|---|---|---|---|
| `..._POST_KUKUI` | `OBJ_EVENT_GFX_KUKUI` | 26,7 | `FACE_DOWN` | `FLAG_TEMP_3` |
| `..._POST_LILLIE` | `OBJ_EVENT_GFX_LILLIE` | 28,7 | `FACE_DOWN` | `FLAG_TEMP_4` |
| `..._POST_NINETALES` | `OBJ_EVENT_GFX_SPECIES(NINETALES_ALOLA)` | 29,7 | `FACE_DOWN` | `FLAG_TEMP_4` |

A Ninetales divide a flag da Lillie, e está certo: elas aparecem e somem juntas,
e nada neste evento faz `removeobject` em nenhuma das duas (regra da skill
`parceiro-pokemon-de-npc`).

`CherrygroveCity` **já tem** `ON_TRANSITION` (a Missão 3 pôs um). Acrescentar
duas `call`, não um bloco novo:

```asm
@ Postgame beach. Two separate rotas: Kukui on Mon/Tue/Thu/Sat, Lillie on
@ Tue/Thu/Sat. Kukui is there on Monday on his own, which is the point - he is
@ the one who cannot leave the readings alone.
CherrygroveCity_EventScript_ApplyPostKukui::
	goto_if_lt VAR_RIFT_MISSIONS_STATE, 16, CherrygroveCity_EventScript_HidePostKukui
	specialvar VAR_RESULT, GetDayOfWeek
	goto_if_eq VAR_RESULT, WEEKDAY_MON, CherrygroveCity_EventScript_ShowPostKukui
	goto_if_eq VAR_RESULT, WEEKDAY_TUE, CherrygroveCity_EventScript_ShowPostKukui
	goto_if_eq VAR_RESULT, WEEKDAY_THU, CherrygroveCity_EventScript_ShowPostKukui
	goto_if_eq VAR_RESULT, WEEKDAY_SAT, CherrygroveCity_EventScript_ShowPostKukui
CherrygroveCity_EventScript_HidePostKukui::
	setflag FLAG_TEMP_3
	return
CherrygroveCity_EventScript_ShowPostKukui::
	clearflag FLAG_TEMP_3
	return

CherrygroveCity_EventScript_ApplyPostLillie::
	goto_if_lt VAR_RIFT_MISSIONS_STATE, 16, CherrygroveCity_EventScript_HidePostLillie
	specialvar VAR_RESULT, GetDayOfWeek
	goto_if_eq VAR_RESULT, WEEKDAY_TUE, CherrygroveCity_EventScript_ShowPostLillie
	goto_if_eq VAR_RESULT, WEEKDAY_THU, CherrygroveCity_EventScript_ShowPostLillie
	goto_if_eq VAR_RESULT, WEEKDAY_SAT, CherrygroveCity_EventScript_ShowPostLillie
CherrygroveCity_EventScript_HidePostLillie::
	setflag FLAG_TEMP_4
	return
CherrygroveCity_EventScript_ShowPostLillie::
	clearflag FLAG_TEMP_4
	return
```

Falas, e as duas revanches pelo modelo de §10.4 com `FLAG_DAILY_REMATCH_KUKUI` e
`FLAG_DAILY_REMATCH_LILLIE`:

> `BeachKukui`
> {SPEAKER NAME_KUKUI}{PLAYER}! Hey! Look who the boat brought!
> I flew back to Alola, I walked into my own lab, I looked at my own desk for about four minutes, and then I got back on a boat. Burnet says hello and also that she is not surprised.
> This beach, {PLAYER}. Something happened on this beach and the sand still knows about it. I've got readings I can't explain and I have never been happier.
>
> `BeachKukuiRematchAsk`
> {SPEAKER NAME_KUKUI}Hold on, hold on. Before the science.
> You're the Champion of Johto, you've got a Necrozma in that team, and you have never once had to fight me for anything.
> That's been bothering me for weeks. Let's fix it. Right here, feet in the water. What do you say?
>
> `BeachLillie`
> {SPEAKER NAME_LILLIE}Hello. I hoped you'd come by.
> I'm not helping the professor, before you ask. I have my own notebook now, and it is about something completely different, and he is not allowed to read it.
> …It's about the nine of them. Where they came from. Somebody should be writing that down from the side of the ones who got eaten.
>
> `BeachLillieRematchAsk`
> {SPEAKER NAME_LILLIE}Before you go. Would you battle me?
> I know. You've beaten me in a flower shop, in a shrine and on a road. That's rather the point -- you have a very good record and I would like to ruin it.
> She's not a Vulpix any more, {PLAYER}. Look at her properly this time.

### 10.8 Cianwood: o Gladion

O tile da despedida dele é (17,47) (`LOCALID_CIANWOOD_GLADION`,
`FLAG_HIDE_CIANWOOD_GLADION`). O objeto do pós-game é **novo** e vai ao lado, não
em cima: reusar o objeto antigo significaria recalcular uma flag persistente que
pertence à campanha pré-Liga, e a skill `visibilidade-e-gatilhos` §1 diz por que
isso é caro. (16,47) e (16,48) estão livres.

| `local_id` | Gráfico | x,y | `movement_type` | `flag` |
|---|---|---|---|---|
| `..._POST_GLADION` | `OBJ_EVENT_GFX_GLADION` | 16,47 | `FACE_DOWN` | `FLAG_TEMP_1` |
| `..._POST_SILVALLY` | `OBJ_EVENT_GFX_SPECIES(SILVALLY)` | 16,48 | `FACE_UP` | `FLAG_TEMP_1` |

`CianwoodCity` já tem `MAP_SCRIPT_ON_LOAD` com
`CianwoodCity_EventScript_ApplyGladionVisibility`; acrescentar uma `call` no
mesmo lugar, com a mesma forma (`FLAG_TEMP_1`, Terça/Quarta/Sábado).

> `CianwoodGladion`
> {SPEAKER NAME_GLADION}You found me.
> This is where I told you I was going. Three cities ago, on this beach, I said I was going to train here until I was worth something in a fight. You probably don't remember.
> I trained here. Then I got called to Blackthorn, and then I spent four cities watching you do the actual work. So I came back and started over.
>
> `CianwoodGladionRematchAsk`
> {SPEAKER NAME_GLADION}You know why you're here.
> Every time we've done this, one of us needed something. An egg. A HM. A road. A city that was on fire.
> Nobody needs anything today. That's the only kind of fight I've never had with you. Ready?

### 10.9 As falas de espera — o resto do texto

Todas as falas de estado ≥ 16 — Looker em casa, a Anabel mandando para o Kurt em
Azalea, a Lusamine e a revanche diária, o marinheiro do cais e a fenda diária —
estão em [`ALTAR_SUN_MOON_SCRIPT.md`](ALTAR_SUN_MOON_SCRIPT.md), "Depois de tudo".

Regras que qualquer reescrita precisa respeitar:

- **Sem travessão `—`**: U+2014 não está em `charmap.txt`; use `--`. `“ ”` e `…` podem.
- Vozes do design §3.1. **Ninguém chama a criatura pelo nome** antes do Ato IV.
- Larguras de linha: conferir com a ferramenta da skill `nomear-falante`.

---

## 11. Tabela de resultados de batalha

Três batalhas neste documento, e **as três têm contratos diferentes**. Confundir
os dois primeiros é o erro que este arco já documentou quatro vezes.

| Batalha | Tipo | `B_FLAG_NO_WHITEOUT` | `B_FLAG_NO_CATCHING` | Perder | Retry | Muda estado |
|---|---|---|---|---|---|---|
| Ato II — Lusamine | duelo narrativo | **setada** (e restaurada) | n/a | segue a cena | n/a | 13 → 14 em **qualquer** resultado |
| Ato IV — Ultra Necrozma | boss de ameaça | **NÃO setada** | **setada** | blackout | de graça: estado continua 14 | 14 → 15 **só** em `B_OUTCOME_WON` |
| Pós-game — as quatro revanches | treinador comum | **NÃO setada** | n/a | blackout | amanhã | nenhuma |

Resultados do boss do Ato IV, um por um:

| `GetBattleOutcome` | Alcançável? | O que acontece |
|---|---|---|
| `B_OUTCOME_WON` | sim | Ato IV continua: armadura cai, `givemon`, estado 15 |
| `B_OUTCOME_LOST` | sim | A engine dá blackout; o script **não continua** |
| `B_OUTCOME_DREW` | sim | idem |
| `B_OUTCOME_FORFEITED` | sim (Run num boss vira desistência) | idem |
| `B_OUTCOME_CAUGHT` | **não** — `B_FLAG_NO_CATCHING` | cai em `Unresolved`, volta ao altar, nada muda |
| `B_OUTCOME_RAN` | **não** — num boss vira `FORFEITED` | idem |

---

## 12. Arquivos tocados — checklist de implementação

| Arquivo | Mudança |
|---|---|
| `include/constants/flags.h` | 5 daily flags sobre `FLAG_UNUSED_0x949..0x94D`; `FLAG_VISITED_SUN_MOON_ALTAR 0x1046` + mover `CUSTOM_FLAGS_END` |
| `include/constants/vars.h` | Estender o comentário de `VAR_RIFT_MISSIONS_STATE` de 12 até 16 e acrescentar as invariantes novas |
| `include/constants/battle.h` | `BOSS_PHASE_PROFILE_NECROZMA 10`; `BOSS_PHASE_PROFILE_COUNT` → 11 |
| `include/constants/opponents.h` | `TRAINER_LUSAMINE_ALTAR 972`, `TRAINER_LILLIE_POSTGAME 973`, `TRAINER_GLADION_POSTGAME 974`, com comentário citando este doc |
| `include/constants/map_event_ids.h` | 13 local ids novos (§3.1), **à mão**, no estilo alfabético |
| `src/battle_boss.c` | `sNecrozmaBossPhases` + `sNecrozmaBossProfile` + `case` em `GetBossPhaseProfile` |
| `src/battle_setup.c` | 1 `case` no `switch` de `BattleSetup_StartLegendaryBattle`: as 4 formas de Necrozma → `MUS_DP_VS_DIALGA_PALKIA` |
| `src/data/trainers.party` | Reescrever `TRAINER_LUSAMINE` e `TRAINER_KUKUI` (hoje stubs de Rattata); 3 times novos |
| `src/region_map.c` | 3 mudanças (§4.7): 1 linha em `sMapHealLocations`, 1 em `sFlyDestinations`, 1 `case` em `GetMapsecType` |
| `src/data/heal_locations.json` | `HEAL_LOCATION_SUN_MOON_ALTAR` → `MAP_SUN_MOON_ALTAR` (14,16). O `.h` e o header de constantes são **gerados** |
| `data/specials.inc` | `def_special GetDayOfWeek` |
| `data/maps/SunMoonAltar/map.json` | 3 objetos novos no fim; `flag` de 6 objetos existentes; `movement_type` da Lusamine → `FACE_UP`; 5 `coord_event` na escada com `VAR_TEMP_0` (**não** `VAR_TEMP_1`, §4.6) |
| `data/maps/SunMoonAltar/scripts.inc` | `MapScripts` com `ON_TRANSITION` + `ON_FRAME_TABLE`; visibilidade; clima; disco; Atos I, II, III e V; ramos por estado nos 6 scripts de objeto; a fenda; a loja; a revanche; **e a correção do prefixo `"LUSAMINE: "`** (§14 achado 2) |
| `data/maps/UltraSpaceArena/map.json` | 5 objetos novos |
| `data/maps/UltraSpaceArena/scripts.inc` | `MapScripts` com `ON_TRANSITION` + `ON_FRAME_TABLE`; Ato IV inteiro; **e a correção do warp de volta** (§14 achado 3) |
| `data/maps/OlivineCity_House1/scripts.pory` | `ON_TRANSITION` com 3 decisões; ramo ≥ 16 nos 5 objetos da família |
| `data/maps/OlivineCity_House1/map.json` | `flag` do Looker e da Anabel de `"0"` para `FLAG_TEMP_2`; `flag` do Kukui para `FLAG_TEMP_3` |
| `data/maps/CherrygroveCity/map.json` | 3 objetos novos no fim |
| `data/maps/CherrygroveCity/scripts.pory` | 2 `call` no `ON_TRANSITION` que já existe; 2 scripts de objeto com revanche |
| `data/maps/CianwoodCity/map.json` | 2 objetos novos no fim |
| `data/maps/CianwoodCity/scripts.inc` | 1 `call` no `ON_LOAD` que já existe; 1 script de objeto com revanche |

Vinte e um arquivos. Nenhum gráfico novo, nenhum tileset novo, nenhuma música
nova, nenhum mapa novo, nenhum `map.bin` tocado. **Nenhuma loja** — a revisão 2
tirou o `pokemart` deste documento inteiro.

**Ordem de edição** (a que evita estado intermediário quebrado):

1. Constantes: flags, vars, battle.h, opponents.h.
2. `battle_boss.c` + `battle_setup.c` + `trainers.party` + `specials.inc` +
   `heal_locations.json` + as três mudanças de `region_map.c`.
   **Build aqui.** Se não compilar, o problema é só C, e não script.
3. `SunMoonAltar/map.json` **junto com** o `ON_TRANSITION` dele. Nunca um sem o
   outro: com seis objetos em flag temporária e sem o recálculo, o elenco aparece
   no altar desde o New Game.
4. Resto do `SunMoonAltar/scripts.inc`, Ato por Ato.
5. `UltraSpaceArena` (json + scripts juntos, mesmo motivo).
6. `OlivineCity_House1` (json + pory juntos, mesmo motivo, e este é o par mais
   perigoso porque tira dois NPCs que hoje são `"flag": "0"`).
7. `CherrygroveCity` e `CianwoodCity`.
8. `map_event_ids.h`, e então build completo.

---

## 13. O que pode mudar depois, e o que não pode

**Pode mudar sem tocar neste doc:** qualquer fala; qualquer movimento; os times
das cinco batalhas; os golpes das fases do boss; a escala de dias; o preço e a
lista da loja; a trilha.

**Não pode mudar sem atualizar este documento E o design:**

1. **Os valores 12 a 16 e o que cada um significa.** O doc do loop vai começar
   lendo `>= 16`.
2. **As invariantes de §3.2**, em especial "a fenda é visível ⇔ estado 14/15 ou
   (≥ 16 e a daily limpa)".
3. **`FLAG_EVENT_NECROZMA_ALTAR_UNLOCKED` nunca é limpa** e nenhum valor deste
   documento a toca.
4. **Nenhum `removeobject` nos objetos de `FLAG_TEMP_1`** — nem no altar, nem em
   Olivine, nem em Cherrygrove, nem em Cianwood. Quem tira gente de cena é o
   `warpsilent`. Um `removeobject` num deles leva o grupo inteiro junto, no meio
   da fala, sem erro de build.
5. **A checagem de espaço fica na fenda, antes da travessia**, e a guarda
   `MON_CANT_GIVE` fica antes de qualquer `setvar`.
6. **`B_FLAG_NO_CATCHING` na boss battle.** Tirar isso transforma a captura
   roteirizada num caso duplicado (ele pode ser capturado E recebido) e reabre a
   pendência que o design §9 pedia para fechar.
7. **Cinco fases ⇔ cinco barras.** `IsBossPhaseProfileValid` descarta o perfil
   em silêncio se os dois números divergirem.
8. **`fadescreenswapbuffers` dentro de cena; `fadescreen` só antes de um warp.**
   Regra V23 do design, e o sintoma dela só aparece à noite.
9. **Ninguém em dois lugares no mesmo dia** na tabela de §10.1.

---

## 14. Auditoria do que já existe

Feita no checkout em **23/09/2026**, antes de escrever este plano. Quatro achados
reais, e três coisas que pareciam problema e não são.

### 14.1 Achado 1 — o texto do altar usa o prefixo que a V17 aboliu

`data/maps/SunMoonAltar/scripts.inc:80-105` tem seis textos no formato antigo:

```asm
SunMoonAltar_Text_Lusamine:
	.string "LUSAMINE: This is where the passage\n"
	.string "opens. I can feel it from here.$"
```

A V17 do design (§3.3) aboliu `"Nome: "` dentro da fala em favor da plaquinha
`{SPEAKER NAME_X}`, e vale "para toda cena de história, nova ou antiga". Os seis
textos são placeholders escritos antes da regra e **serão substituídos inteiros**
por este plano, então o conserto sai de graça — mas é preciso conferir depois:

```bash
python3 .claude/skills/nomear-falante/checar_falantes.py
grep -nE '\.string "[A-Z][A-Za-zÉé. ]{1,14}: ' data/maps/SunMoonAltar/scripts.inc
```

O `checar_falantes.py` pega os nomes conhecidos; o `grep` pega um `"Elm: "`
esquecido no meio de um bloco de outra pessoa, que é o defeito pior porque o
build fica limpo e o arquivo parece certo.

### 14.2 Achado 2 — o Ninetales do altar tem `script: "NULL"`, o Silvally também, e isso está certo

Conferido contra a skill `parceiro-pokemon-de-npc` e contra
`OlivineCity_House1/map.json`: é o padrão da casa. **Nada a fazer** — está
listado aqui porque é a primeira coisa que alguém "conserta" por engano.

### 14.3 Achado 3 — a arena devolve o jogador exatamente onde a fenda vai ficar

`data/maps/UltraSpaceArena/scripts.inc`:

```asm
UltraSpaceArena_EventScript_SouthRift::
	lockall
	playse SE_WARP_IN
	warp MAP_SUN_MOON_ALTAR, 14, 10
```

(14,10) é onde `LOCALID_SUN_MOON_ALTAR_RIFT` passa a morar. Um objeto sempre
bloqueia o próprio tile; respawnar o jogador em cima de um é pedir para descobrir
em runtime o que a engine faz com dois ocupantes no mesmo tile.

**Conserto, uma linha:** `warp MAP_SUN_MOON_ALTAR, 14, 11`. (14,11) é livre,
elevação 3, não é warp, e deixa o jogador **de frente para a fenda**, olhando
para o norte — que é a leitura certa para quem acabou de sair dela.

Os três `coord_event` de (9..11, 20) e o resto do script não mudam.

### 14.4 Achado 4 — o Looker e a Anabel têm `"flag": "0"` e o doc anterior proíbe mexer neles

`PRE_NECROZMA_ULTRABEAST_IMPLEMENTATION.md` §4.5 e o cabeçalho de
`OlivineCity_House1/scripts.pory` dizem, com essas palavras:

> Both NPCs have `"flag": "0"`: they live here from New Game on… **NEVER
> removeobject them** — with a clear flag the camera respawns them on the
> player's next step. Scene exits are done by walking back to their spots.

Este plano **precisa** que eles saiam da sala, porque o autor pediu que eles
ficassem no altar permanentemente. A regra citada não é violada — ela é
*substituída pela via correta*:

- O `removeobject` continua proibido, e este plano não usa nenhum.
- O que muda é o campo `flag` no `map.json`, de `"0"` para `FLAG_TEMP_2`, com
  recálculo incondicional no `ON_TRANSITION` (§10.6). É exatamente o padrão da
  skill `visibilidade-e-gatilhos` §6, e é o mesmo que os seis da reunião já usam
  no mesmo arquivo.

**Consequência que tem de ser escrita no código, no comentário do cabeçalho
daquele arquivo:** com `FLAG_TEMP_2`, o **default passa a ser visível**. Se um
dia alguém remover o `ApplyInvestigatorVisibility` "porque parecia redundante",
o Looker e a Anabel voltam a aparecer em Olivine **e** continuam no altar, ao
mesmo tempo, para sempre — e nada no build acusa. O comentário antigo daquele
arquivo tem de ser reescrito na mesma passada, porque hoje ele afirma uma coisa
que deixa de ser verdade.

### 14.5 Achado 5 — o `goto_if_ge ..., 10` de Olivine, pela quarta vez

O `scripts.pory` de Olivine registra que o erro `goto_if_ge` onde devia ser
`goto_if_eq` **já foi cometido três vezes** naquele arquivo, e o doc anterior
registra que a quarta foi evitada. Este plano acrescenta um ramo `>= 16` **de
verdade** àquele arquivo, o que significa que o `grep` de conferência daquele
doc deixa de ter a resposta esperada. Novo comando de conferência, e ele tem de
devolver exatamente três linhas de código — as duas de `LookerAltar`/`AnabelAltar`
(`, 12,`) e a nova de `ApplyInvestigatorVisibility` (`, 16,`):

```bash
grep -n "goto_if_ge VAR_RIFT_MISSIONS_STATE" data/maps/OlivineCity_House1/scripts.pory
```

### 14.6 Não é problema — a `MAPSEC` "Abandoned Lab"

Parecia o achado mais óbvio: três mapas (`SunMoonAltar`, `UltraSpaceArena`,
`SouthPassageEnd`) usam `MAPSEC_ABANDONED_LAB`, e o altar tem
`show_map_name: true`. Mas a `MAPSEC` **já foi renomeada** neste repositório:
`region_map_entries.h:1955` traz `"Altar of Sun and Moon"`, com posição no mapa
da região. A plaquinha já está certa, e o local de encontro do Necrozma também.
**Não mexer.**

### 14.7 Não é problema — o `map.bin` retocado

106 das 195 células do carimbo original do gerador ainda batem com
`data/layouts/SunMoonAltar/map.bin`; o resto é retoque do autor no Porymap. As
**sete células do disco batem exatamente**, que é tudo de que o `setmetatile` do
§4.3 precisa. Nenhuma alteração de `map.bin` neste plano — e, pela memória de
projeto sobre retoques do autor, **diff antes de qualquer coisa** se este plano
for executado dias depois de escrito.

### 14.8 Não é problema — a balsa

`SunMoonAltar_EventScript_Sailor` e `OlivinePort_Sailor` funcionam nos dois
sentidos, e o `OlivinePort_Sailor` até tem uma rede de segurança para saves
feitos depois da reunião e antes do ticket existir. **Nada a fazer.**

---

## 15. Pendências e riscos

### Risco 1 — RESOLVIDO: por que a Anabel não luta, dito dentro da ficção

O autor decidiu na revisão 2: *"faz parecer que ela está segurando alguma coisa
que mantém o portal estável e não pode lutar"*. Isso resolve de uma vez o
problema de design **e** o problema técnico, e é melhor do que qualquer das duas
opções anteriores.

**Na ficção:** a fenda não se sustenta sozinha. Do lado do altar, a Lusamine, a
Lillie, o Gladion e o Kukui seguram este lado; **do lado de dentro, quem segura é
a Anabel.** Ela atravessou uma ruptura uma vez — é a única pessoa viva que sabe
com o corpo como uma se sente por dentro — e é por isso que **ela** é a âncora e
não o Looker, não a Lusamine e não o jogador. Ela entra, se posta, e **a partir
daí as mãos dela estão ocupadas**. Se ela largar, o caminho de volta fecha, o que
é exatamente a condição que ela impôs em Olivine e vem repetindo desde a Missão 3.

O que isso muda no script: **uma caixa nova** antes da batalha e **uma correção de
coreografia**. Depois de se pôr na frente do jogador uma vez (que é o gesto dela
desde Cherrygrove), ela **volta um tile e para**, e não se mexe mais até o fim do
ato:

```asm
	@ Revision 2: she steps back to her anchor tile and stays there. Everything
	@ after this point in the act moves the player, the partner or the creature -
	@ NEVER her. She is holding the way home open with both hands, and the
	@ scene has to be able to be read that way without a single line of
	@ exposition after this box.
	applymovement LOCALID_ULTRA_SPACE_ARENA_ANABEL, Common_Movement_WalkDown
	waitmovement LOCALID_ULTRA_SPACE_ARENA_ANABEL
	msgbox UltraSpaceArena_Text_ArenaAnabelAnchor, MSGBOX_DEFAULT
	closemessage
```

> `ArenaAnabelAnchor` — **the in-fiction reason she does not battle**
> {SPEAKER NAME_ANABEL}Now listen, because I am going to be useless in about four seconds and I would rather you heard why.
> That tear behind us does not stay open. Somebody has to hold it, from this side, and it has to be somebody who has been through one -- I don't know why and I have stopped needing to know why.
> So this is where I stand and this is what I do. If I let go, you don't get home. I'm not going to let go.
>
> `ArenaAnabelAnchorTwo`
> {SPEAKER NAME_ANABEL}Which means the fight is yours. All of it. I can't throw so much as a Poke Ball from here.
> …I have spent my whole career being the one who gets in front. Standing still is the hardest thing anybody has asked me to do all year.
> Go on, {PLAYER}. I've got the door.

**Na técnica, isto era necessário de qualquer forma:**

- O sistema de follower NPC está **desligado**: `FNPC_ENABLE_NPC_FOLLOWERS` é
  `FALSE` (`include/config/follower_npc.h:5`) e a macro `setfollowernpc` dá
  `.error` se usada assim. Ligar aumenta `SaveBlock3` e nenhum mapa do jogo usa.
- E o decisivo: **o sistema de boss só funciona em batalha simples** (skill
  `evento-esqueleto`: "Dupla cancela o boss"). Uma Anabel parceira custaria as
  cinco barras, o perfil de fases e a forma Ultra.

A diferença entre a revisão 1 e a 2 é que antes isso era uma limitação
**escondida**, e agora é uma **cena**. Nenhum jogador vai perceber que a
engine não podia.

### Risco 2 — RESOLVIDO: o Looker cura desde o estado 13

O altar não tem Centro Pokémon e `allow_escaping` é `false`. Perder a boss
battle devolve o jogador ao último Centro visitado, do outro lado do mar.

**Decisão do autor na revisão 2: o Looker cura, e cura desde o 13** (§10.2), não
só no pós-game. É a recomendação da revisão 1 aprovada: `MSGBOX_YESNO` +
`Common_EventScript_OutOfCenterPartyHeal`, de graça, sem limite, sem flag.

**E Fly (§4.7) corta o resto do atrito:** depois do Ato I o altar é destino de
Fly, então o retry da boss é Fly → escada → fenda. Duas telas.

**Continua rejeitado:** `setrespawn HEAL_LOCATION_SUN_MOON_ALTAR`. Faria o jogador
renascer no altar depois de **qualquer** blackout em qualquer lugar de Johto, até
entrar em outro Centro. A `HEAL_LOCATION_SUN_MOON_ALTAR` que o §4.7 cria existe
só para o Fly saber onde pousar, e **nada** neste plano chama `setrespawn`.

### Risco 3 — o orçamento de 16 objetos no altar depende de o cais estar longe

A conta de §3.4 dá 12/16 **porque o `Sailor` e o `SS_TIDAL` estão a 12-18 linhas
ao sul** e não spawnam junto com o pátio. É verdade hoje e é verdade pela
geometria do mapa, não por sorte — mas é a única parte do orçamento que não é
aritmética pura. **Conferir em runtime com o elenco inteiro em tela no Ato III**,
e se algum objeto faltar, o primeiro a cair é o último do array (a Lunala ou o
Solgaleo, que é o pior possível).

### Risco 4 — RESOLVIDO: a Nihilego está aprovada

O autor aprovou na revisão 2 ("sim, pode utilizar"). Fica no time de
`TRAINER_LUSAMINE_ALTAR`, e o §10.5 acrescenta a condição que impede a leitura
errada: **uma caixa de fala dela tem de dizer de onde a Nihilego veio**, para que
a presença dela nunca seja lida como a fusão de Sun/Moon que o design §3.1
proíbe importar.

### Risco 5 — dois sprites no mesmo tile

Solgaleo/Lunala em (13,10) no altar e em (9,19) na arena, e Necrozma/Ultra em
(10,8). O padrão só é seguro porque as flags são **separadas** e porque nenhuma
cena mostra os dois. Se alguém algum dia der a mesma flag aos dois, os dois
spawnam, um fica invisível por baixo do outro, e o `applymovement` acerta o
errado. **Conferir com `dump_mapa.py`, que imprime a flag de cada objeto.**

### Risco 6 — RESOLVIDO: Fly entra, e a "Crater" é a prova

O autor respondeu *"coloca no mesmo mapa secundário que tem a Crater"*, e a
pesquisa mostrou que **a `MAPSEC` do altar já está nessa página** — linha a linha
ao lado da `MAPSEC_METEOR_ISLAND`, que é destino de Fly funcionando. A dúvida da
revisão 1 ("uma página secundária é selecionável?") está respondida pelo
precedente. Detalhe e as quatro linhas em **§4.7**.

O que sobra de risco é pequeno e é de runtime: **conferir que o cursor do mapa de
Fly realmente navega até `x = 16, y = 0` naquela página**, e que o pouso em
(14,16) deixa o jogador de pé no degrau e não dentro da parede. Se o pouso ficar
ruim, a `HEAL_LOCATION` muda de coordenada e nada mais precisa mexer.

### Risco 7 — o tamanho dos textos

A cena mais longa aqui (o Ato I, 17 caixas) passa **muito** dos 1000 bytes que
`gStringVar4` aceita — mas isso só quebra se as caixas estiverem no **mesmo**
`msgbox`. Todas as cenas deste plano usam um `msgbox` + `closemessage` por caixa,
que é o que o briefing da Missão 4 teve de virar depois de travar o jogo
(`nomear-falante` §5). **Rodar `checar_falantes.py` e `medir_linha.py` nos dois
`scripts.inc` tocados**, e em nenhum outro (há texto vanilla que estoura de
origem e o ruído esconde o que importa).

### Risco 8 — a escala de dias e o relógio do jogador

`GetDayOfWeek()` lê o RTC. Num emulador com RTC falso ou num save importado a
escala pode parecer travada num dia. Não é bug deste evento, mas é o primeiro
lugar onde o autor vai notar, e o teste de runtime tem de incluir avançar o dia
(o menu de debug tem controle de tempo — `src/debug.c:1939` já chama
`GetDayOfWeek`).

### Risco 9 — o que este documento deixa aberto para o doc do loop

- `UltraSpaceArena_EventScript_EmptyRift` é o único `@ SKELETON:` que sobra, e é
  de propósito. O doc do loop começa substituindo esse script.
- A arena é **um** mapa. O design §10 fala de destinos que são "realidades
  quebradas" diferentes — se o loop quiser mapas diferentes por expedição, a
  fenda do altar passa a escolher o destino, e é o doc do loop que decide como.
- Nada aqui aloca var para o loop. `17+` está livre, e é provável que o loop
  precise de var própria em vez de continuar esta.

---

## 16. Teste em runtime

Ordem sugerida, e cada linha existe porque algo específico pode quebrar nela.

**Antes do evento**

- [ ] Chegar ao altar por debug com o estado em 0: o pátio tem **só** o Looker,
      a Anabel, o marujo e o navio. Nada de Lusamine.
- [ ] Estado 0, olhar o disco: sol de dia, lua à noite, sem cinza.

**Ato I**

- [ ] Com o estado 12, subir a escada pelos **cinco** tiles, um teste por tile:
      a cena dispara em todos e ninguém atravessa parede. **Se não disparar em
      nenhum, é a armadilha do §4.6** (os dois gatilhos na mesma `VAR_TEMP`).
- [ ] Entrar no pátio **à noite**: os flashes do disco não escurecem a cena
      progressivamente (regra V23 — é este o teste que pega `fadescreen`).
- [ ] Com Cosmog na equipe / com Cosmoem / com Solgaleo / com Lunala / sem
      nenhum: as quatro reações e o silêncio, e a cena idêntica nos cinco casos.
- [ ] Depois da cena: salvar, desligar, voltar. O elenco está nos tiles do
      `map.json`, o clima é cinza, o disco é portal, a cena **não** repete.
- [ ] **Fly:** abrir o mapa da região e conferir que o altar aparece como destino
      na mesma página da Meteor Island, que o cursor chega nele, e que o pouso em
      (14,16) deixa o jogador de pé no degrau (§4.7).
- [ ] Falar com o Looker no estado 13: ele **cura** a equipe.

**Ato II**

- [ ] Falar com a Lusamine e responder **NÃO**: nada muda. Sair do mapa, voltar,
      falar de novo: a pergunta é idêntica.
- [ ] Vencer. Depois, num save separado, **perder de propósito**: sem blackout,
      sem perda de dinheiro, a cena continua, e a fala da Lillie é a mesma.
- [ ] **Desistir pela batalha** (Run): cai no ramo `FORFEITED` e a cena continua.
- [ ] Empatar, se der (Destiny Bond / recuo duplo).
- [ ] Entrar na batalha com `B_FLAG_NO_WHITEOUT` já ligada por outra coisa e
      confirmar que ela **continua** ligada depois.
- [ ] Depois do Ato III: a fenda está em (14,10), o parceiro **não** está mais no
      mapa, e o disco continua portal.

**Ato IV**

- [ ] Falar com a fenda com 6 na equipe e PC com vaga: **passa** (não bloqueia).
- [ ] Com 6 na equipe e PC cheio: **bloqueia**, sem oferta, e volta depois de
      abrir espaço.
- [ ] Guardar o Solgaleo/Lunala no PC e falar com a fenda: recusa, repetível,
      nada muda. Tirar do PC: passa.
- [ ] Responder **NÃO**: nada muda.
- [ ] Na arena: a Anabel e o parceiro sobem o corredor sem travar e param ao lado
      do jogador, não em cima.
- [ ] A Anabel dá o passo à frente, volta para (11,11), **e não se mexe mais**.
      Conferir olhando a tela durante todo o resto do ato: se ela andar depois
      da caixa da âncora, a leitura de "ela está segurando a porta" cai.
- [ ] As duas caixas da Beast Ball tocam **antes** da luta, e a caixa em que ela
      entrega a bola toca **depois** da vitória.
- [ ] A luta: **cinco** barras, e nas fases 4 e 5 o sprite é Necrozma comum. Se
      for Ultra nas cinco, o perfil foi descartado (fases ≠ barras).
- [ ] A música é a de Dialga/Palkia, não a selvagem comum.
- [ ] Tentar jogar uma bola: bloqueado.
- [ ] **Perder de propósito**: blackout, e o retry funciona — voltar de balsa,
      entrar na fenda, e o mapa está limpo (Anabel escondida, Necrozma escondido).
- [ ] Ganhar: recebe Necrozma **nível 75, forma normal**, com a fanfarra; volta
      ao altar em (14,11), de frente para a fenda.
- [ ] Com 5 na equipe: entra na equipe. Com 6 e PC com vaga: vai para a caixa
      **com aviso** (é o caso que `Common_EventScript_GiftMon` cobre e
      `GiftMonNamed` engoliria).

**Ato V**

- [ ] A cena dispara ao voltar da fenda, não ao subir a escada.
- [ ] No fim: cinza para, disco volta ao sol/lua, e a fenda **continua lá**.
- [ ] Sair e voltar: Looker e Anabel estão no altar; Lillie, Gladion, os dois
      parceiros e o Kukui **não**; a Lusamine depende do dia.

**Pós-game**

- [ ] Entrar na fenda: a arena vazia, uma caixa, e o gatilho sul devolve ao
      altar em (14,11).
- [ ] Voltar ao altar no mesmo dia: a fenda **sumiu**. Avançar o dia: voltou.
- [ ] Anabel: **não há loja nenhuma**. Duas caixas, e a segunda nomeia o Kurt,
      Azalea e o fato de ser diário.
- [ ] Looker: cura a equipe, e continua curando.
- [ ] Percorrer os **sete dias** com controle de tempo e conferir a tabela de
      §10.1 inteira, incluindo que ninguém está em dois mapas no mesmo dia.
- [ ] As quatro revanches: ganhar uma, e confirmar que ela não volta no mesmo
      dia. **Perder** uma: blackout, e ela também não volta no mesmo dia.
- [ ] `OlivineCity_House1`: vazia nos cinco dias úteis; a família em domingo e
      sexta; o Kukui nunca.
- [ ] Entrar em `OlivineCity_House1` no estado 16 e confirmar que **nenhuma**
      cutscene dispara.

**Ferramentas**

```bash
python3 .claude/skills/encenar-cutscene/dump_mapa.py SunMoonAltar
python3 .claude/skills/encenar-cutscene/dump_mapa.py UltraSpaceArena
python3 .claude/skills/nomear-falante/checar_falantes.py
python3 .claude/skills/nomear-falante/medir_linha.py data/maps/SunMoonAltar/scripts.inc
python3 .claude/skills/nomear-falante/medir_linha.py data/maps/UltraSpaceArena/scripts.inc
grep -rn "SKELETON:" data/maps/SunMoonAltar data/maps/UltraSpaceArena
make -j$(nproc)
```

O `grep` de `SKELETON:` tem de devolver **exatamente um** resultado: o
`EmptyRift` da arena. Qualquer outro é fala que ficou sem escrever.

---

## 17. Retorno da implementação (revisão 3, 24/09/2026)

Este documento foi executado inteiro numa passada, junto com
[`KURT_BALL_CRAFT_DESIGN.md`](../../KURT_BALL_CRAFT_DESIGN.md). A `make` fecha limpa,
`checar_falantes.py` diz "14 falantes, tudo em ordem" e `medir_linha.py` não acha
linha acima de 208 px em nenhum dos sete arquivos tocados.

**O que o plano acertou e não precisou de nada:** a máquina de estados 12→16, as
invariantes do §3.2, o orçamento de objetos do §3.4, as sete células do disco
(conferidas uma a uma contra o `map.bin` retocado pelo autor — batem), os cinco
`coord_event` da escada, a separação `VAR_TEMP_0`/`VAR_TEMP_1` do §4.6, as cinco
linhas do Fly do §4.7, o perfil de fases do §8.4, a ordem da checagem de espaço
do §7 e a coreografia inteira dos cinco atos, tile por tile.

### 17.1 As nove correções

**1. `setmetatile` não funciona em `ON_TRANSITION`. O §4.5 punha o disco lá.**

`setmetatile` escreve em `gBackupMapLayout`, que só existe **depois** do
`InitMap` — e é o `InitMap` que chama o `ON_LOAD` (`src/fieldmap.c`). O
`ON_TRANSITION` roda **antes** disso. Escrito como o §4.5 mandava, o disco
simplesmente nunca mudaria, com build limpo.

Conferido: **todos** os oito mapas do repositório que usam `setmetatile` o
penduram em `MAP_SCRIPT_ON_LOAD`, nenhum em `ON_TRANSITION`.

O `MapScripts` do altar ficou com **três** entradas, não duas:

```asm
SunMoonAltar_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SunMoonAltar_OnTransition   @ flags + clima
	map_script MAP_SCRIPT_ON_LOAD, SunMoonAltar_OnLoad               @ o disco, e SÓ o disco
	map_script MAP_SCRIPT_ON_FRAME_TABLE, SunMoonAltar_OnFrame
	.byte 0
```

A visibilidade continua no `ON_TRANSITION` (os dois rodam antes do spawn, então
qualquer um serviria) e `setweather` também, porque o load aplica o clima por
conta própria a partir de lá. `ApplyAltarMood` do §4.5 virou duas rotinas,
`ApplyWeather` e `ApplyDisc`.

**2. Este documento e o do Kurt alocavam a MESMA daily flag.**

Os dois pediam `FLAG_UNUSED_0x949`. Como foram implementados juntos, a colisão
apareceu na primeira edição de `flags.h`; se tivessem sido feitos em semanas
diferentes, a segunda implementação teria redefinido a flag da primeira e o
`make` **não** acusaria (são dois `#define` em linhas diferentes com o mesmo
valor, e quem lê o arquivo vê dois nomes plausíveis).

Reparte final, e ela é a verdade do código:

| Flag | Valor | De quem |
|---|---|---|
| `FLAG_DAILY_ALTAR_RIFT` | `+ 0x29` | este doc |
| `FLAG_DAILY_REMATCH_LUSAMINE` | `+ 0x2A` | este doc |
| `FLAG_DAILY_REMATCH_KUKUI` | `+ 0x2B` | este doc |
| `FLAG_DAILY_REMATCH_LILLIE` | `+ 0x2C` | este doc |
| `FLAG_DAILY_REMATCH_GLADION` | `+ 0x2D` | este doc |
| `FLAG_DAILY_KURT_NEW_DAY` | `+ 0x2E` | doc do Kurt |
| `FLAG_DAILY_BERRY_MASTERS_WIFE` | `+ 0x11` | doc do Kurt, **reusada** (já existia e ninguém referenciava) |

`+ 0x2F` em diante continua livre. **Seis daily flags novas no total**, não sete:
a do Berry Master saiu de graça.

**3. O jogador pode estar em pé exatamente onde a fenda nasce.**

O §6.4 fazia `addobject LOCALID_SUN_MOON_ALTAR_RIFT` em (14,10) sem olhar onde o
jogador está. Mas para falar com a Lusamine em (14,9) o jogador tem de estar em
(13,9), (15,9) **ou (14,10)** — e (14,10) é o tile da fenda. Um objeto sempre
bloqueia o próprio tile, então a cena acabaria com dois ocupantes no mesmo tile.

Conserto, três linhas, no começo de `DuelSettled`:

```asm
	getplayerxy VAR_0x8004, VAR_0x8005
	call_if_eq VAR_0x8005, 10, SunMoonAltar_EventScript_PlayerOffRiftTile
```

`y == 10` basta como teste: dos tiles andáveis com y=10, só (14,10) é adjacente à
Lusamine. A rotina dá um `walk_down` e termina com `face_up`, o que também deixa
o jogador de frente para a fenda — que é a posição em que ele quer estar para ver
a coisa abrir.

**4. `FLAG_TEMP_3` e `FLAG_TEMP_4` de Cherrygrove JÁ ESTÃO ocupadas.**

O §10.7 dava `FLAG_TEMP_3` ao Kukui do pós-game e `FLAG_TEMP_4` à Lillie. Mas
`CherrygroveCity` usa `FLAG_TEMP_1` a **`FLAG_TEMP_6`**, não só 1/2/5/6 como o
§3.3 registrou: `FLAG_TEMP_3` e `FLAG_TEMP_4` são o cache de visibilidade dos
**dois presentes do Friendly Trader** (o Zigzagoon de Galar e o Rattata de
Alola, locals 16 e 17). Reusá-las faria os dois presentes piscarem junto com a
escala de dias do pós-game — e, pior, o `ON_TRANSITION` da Missão 3 e o novo
brigariam pela mesma flag no mesmo load.

Passou para **`FLAG_TEMP_7`** (Kukui) e **`FLAG_TEMP_8`** (Lillie + Ninetales),
conferidas livres no mapa e em `data/scripts/`.

**5. `FLAG_TEMP_1` de Cianwood JÁ ESTÁ ocupada.**

Mesmo erro, outro mapa: o §10.8 dava `FLAG_TEMP_1` ao Gladion do pós-game, mas
`FLAG_TEMP_1` e `FLAG_TEMP_2` são as **duas pedras quebráveis** de Cianwood (no
`map.json`, não no `scripts.inc` — é por isso que o `grep` do §3.3 não as viu).
Passou para **`FLAG_TEMP_3`**.

> **A lição das correções 4 e 5, e ela vale para o doc seguinte.** O comando do
> §3.3 está **certo** — ele é `grep -rn` em diretórios de mapa, então já varre o
> `map.json`. O que estava errado era a **tabela de resultados**: alguém rodou o
> comando e transcreveu menos do que ele devolveu. `FLAG_TEMP_3`/`4` de
> Cherrygrove e `FLAG_TEMP_1`/`2` de Cianwood estavam lá para serem vistas.
>
> Conferência que é difícil de transcrever errado, porque ela imprime objeto por
> objeto em vez de uma lista de ocorrências:
>
> ```bash
> python3 .claude/skills/encenar-cutscene/dump_mapa.py <Mapa>   # a flag de CADA objeto
> ```
>
> Use as duas: o `grep` acha flag usada por script, o `dump_mapa.py` acha flag
> usada por template. As duas pedras de Cianwood só aparecem na segunda.

**6. O comentário do `PartnerHarmonise` (§8.5) descreve o movimento errado.**

O comentário diz "two tiles east, onto the creature's column"; o movimento é
`walk_up` + `face_down`, ou seja (9,9) → **(9,8)**, um tile ao norte, ao lado da
coluna da criatura. O **movimento está certo** — (9,8) é livre e a leitura da
cena ("põe-se entre a coisa pequena e a fenda") funciona — e foi o comentário que
se corrigiu no código.

**7. `trainers.party` não aceita `#` como comentário, e nem comentário entre o
cabeçalho e o `Name:`.**

Duas coisas, as duas descobertas com o parser gritando:

- O arquivo aceita **só** `/* ... */` (o cabeçalho dele diz isso na linha 84:
  "`//` cannot be used as comments"). `#` vira token e o parser morre.
- Um comentário **entre** `=== TRAINER_X ===` e `Name:` também quebra, porque
  depois do `cpp` ele deixa uma **linha em branco**, e linha em branco encerra o
  cabeçalho do treinador — o `Name:` seguinte passa a ser lido como se fosse um
  Pokémon. O comentário tem de ficar **acima** do `=== TRAINER_X ===`.

**8. O `grep` de conferência do §14.5 muda de resposta.**

Aquele comando devia devolver três linhas de código. Agora devolve **seis**, e é
o correto:

```bash
grep -n "goto_if_ge VAR_RIFT_MISSIONS_STATE" data/maps/OlivineCity_House1/scripts.pory
```

| Linha | Quem |
|---|---|
| `, 12,` × 2 | `LookerAltar` e `AnabelAltar`, que já existiam |
| `, 16,` × 1 | `ApplyInvestigatorVisibility`, novo |
| `, 16,` × 3 | os ramos de pós-game da Lusamine, da Lillie e do Gladion, novos |

**9. Faltavam dois textos e um deles é obrigatório.**

`SunMoonAltar_Text_LusamineIdle` estava truncado no §10.9 ("Not now." e mais
nada) e `SunMoonAltar_Text_DuelUnexpected` não existia — o §6.3 previa o ramo mas
não a fala. Os dois foram escritos. E o **risco 4** (a Nihilego não pode ser lida
como a fusão de Sun/Moon) foi pago dentro de `LusamineRematchAsk`, que agora diz
de onde ela veio antes de oferecer a revanche.

### 17.2 Decisões de implementação que o plano deixava abertas

| Ponto | O que se fez |
|---|---|
| Falante do Kurt | `SP_NAME_KURT` entrou como **14º** falante nos três arquivos. O doc do Kurt escrevia as falas dele como `"Kurt: ..."`, formato que a V17 aboliu |
| Textos em português nos docs | Os textos do §2.5 e do §5.5 do doc do Kurt estavam em **português**. Foram escritos em inglês, como manda o `CLAUDE.md` |
| Quebra de linha dos textos | Medida em **pixels de glifo** por um gerador que usa o `medir_linha.py` da skill, não em número de letras. Parágrafo vira página (`\p`), terceira linha em diante rola (`\l`) — que é a forma vanilla e evita página com uma linha órfã |
| Aspas dentro de fala | `“ ”` do charmap em vez de `\"` escapado, em `LookerCrisis` e `LusamineAnchor` |
| `grep "SKELETON:"` do §16 | Continua devolvendo **exatamente um** resultado, o `EmptyRift` da arena |

### 17.3 O que sobra para o teste em runtime

O §16 vale inteiro e nada dele foi executado. Os itens que a implementação tornou
**mais** importantes:

- [ ] **O disco.** Entrar no altar com o estado em 13 e conferir que o disco é
      portal. Se ele continuar sol/lua, a correção 1 foi desfeita por alguém.
- [ ] **O Ato III com o jogador em (14,10).** Falar com a Lusamine ficando
      exatamente embaixo dela e confirmar que ele dá um passo para o sul antes de
      a fenda nascer (correção 3).
- [ ] **Os dois presentes do Friendly Trader em Cherrygrove no pós-game.** Eles
      têm de continuar aparecendo/desaparecendo pela própria regra, sem relação
      com o dia da semana (correção 4).
- [ ] **As duas pedras quebráveis de Cianwood no pós-game** (correção 5).
- [ ] Os **sete dias** da tabela do §10.1, com controle de tempo.

---

## 18. Retorno do autor em runtime (revisão 4, 25/09/2026)

O autor jogou o evento inteiro, do cais de Olivine à fenda diária do pós-game, e
voltou com cinco itens. Os cinco estão corrigidos e a `make` fecha limpa.

| # | O que ele disse | Natureza | Onde está a correção |
|---|---|---|---|
| 1 | "Jogo crasha quando eu vejo o mapa lá dentro" (Town Map / Pokégear **dentro do Altar**) | **Crash certo** | §18.1 |
| 2 | "O rift podia ser mais bonito" | Arte | §18.2 |
| 3 | "Não acho que o Looker e a Anabel precisam ficar parados olhando pro Rift pós-jogo" | Encenação | §18.3 |
| 4 | "WTF ela deu um Solgaleo ao derrotar o Necrozma, era pra dar o Necrozma e ter uma animação capturando ele" | **Bug de texto + cena faltando** | §18.4 |
| 5 | "Quando eu entro no Rift logo após a luta do Necrozma a tela fica branca e o jogo trava" (fenda **diária**, evento já encerrado) | **Travamento — causa não provada** | §18.5 |

### 18.1 O mapa do Pokégear no Altar: 21 caracteres em cima de um ponteiro

Nome do `MAPSEC_ABANDONED_LAB` na revisão 3: **"Altar of Sun and Moon"** — 21
caracteres, **o único nome acima de 19 nos 312 do `gRegionMapEntries`**.

```c
// include/region_map.h, antes
struct RegionMap {
    /*0x000*/ mapsec_u16_t mapSecId;
    /*0x002*/ u8 mapSecType;
    /*0x003*/ u8 posWithinMapSec;
    /*0x004*/ u8 mapSecName[20];        // <- 20 bytes
    /*0x018*/ u8 (*inputCallback)(void); // <- e logo em seguida um PONTEIRO DE FUNCAO
```

`GetMapName()` faz um `StringCopy` **sem limite** de
`gRegionMapEntries[id].name`. 21 caracteres + `EOS` = 22 bytes num campo de 20:
os dois bytes que sobram caem nos dois primeiros bytes de `inputCallback`. O
mapa então chama `DoRegionMapInputCallback()` todo frame, ou seja, **salta para
um endereço lixo no primeiro frame depois de abrir**. Não é intermitente: é todo
Town Map aberto dentro do Altar, e só lá, porque só esse nome passa de 19.

O mesmo nome estourava, por 1 byte, o `mapDisplayHeader[27]` do popup de nome de
mapa (`src/map_name_popup.c`), que o Altar dispara toda vez que o jogador entra
(`show_map_name: true`) — ali o estouro é na **pilha**.

Três correções, porque uma só não fecha a classe do bug:

1. **O nome cabe agora.** `"Sun & Moon Altar"` — 16 caracteres, na mesma faixa
   dos outros nomes longos do jogo ("Snowtop Mountain", "Cherrygrove City"). O
   antigo não cabia nem na tela: medido com as larguras de glifo de
   `src/fonts.c`, ele dava **111 px** numa janela de **96 px** no mapa de região
   e **96 px** numa de **80 px** no popup. O novo dá 85 px e 74 px.
   Trocado **só no `src/data/region_map/region_map_sections.json`**, que é a
   fonte de verdade: o `region_map_entries.h` é **gerado** dele pelo
   `json_data_rules.mk` e está no `.gitignore`. Editar o `.h` à mão não
   sobrevive ao próximo `make` (foi testado: sobreviveu o nome, que vem do
   JSON, e sumiu o comentário que eu tinha posto lá).
2. **Os buffers passaram a ter folga.** `MAP_NAME_LENGTH_MAX = 24` novo em
   `include/region_map.h`; `mapSecName[MAP_NAME_LENGTH_MAX]` e
   `mapDisplayHeader[MAP_NAME_POPUP_PREFIX_SIZE + MAP_NAME_LENGTH_MAX]`. Com
   isso, um nome comprido volta a ser um defeito visual (texto cortado) em vez
   de um salto para endereço inválido.
3. **O porquê está escrito onde alguém vai tropeçar nele:** comentário no
   `include/region_map.h`, ao lado da definição de `MAP_NAME_LENGTH_MAX`,
   explicando que `MAP_NAME_LENGTH` (16) é o **preenchimento**, não o limite,
   que `GetMapName()` copia sem limite nenhum e o que exatamente quebra quando
   o nome passa do buffer. O JSON não aceita comentário, então esse é o único
   lugar de código onde o aviso cabe — por isso ele também está aqui e na
   revisão V25 do design.

> **Regra que sai daqui:** nome de `MAPSEC` novo tem no máximo **16 caracteres**.
> Acima disso ele não cabe nas janelas; acima de 23 ele volta a corromper
> memória.

### 18.2 A fenda: `OBJ_EVENT_GFX_ALTAR_RIFT`

O que estava lá era o `OBJ_EVENT_GFX_PORTAL`: um anel de **16x16 parado**, de
quadro único (`inanimate = TRUE`, `sAnimTable_Inanimate`), emprestado do
`SpearPillarTop`.

O que existe agora é um objeto próprio, **32x32 e com quatro quadros em loop**:

- `graphics/object_events/pics/misc/altar_rift.png` — 128x32 (quatro quadros de
  32x32), indexado, 9 cores, índice 0 transparente. Desenhado por código
  (`math`+`zlib`, sem PIL) como uma lente vertical: halo roxo por fora, anel
  magenta, violeta, ciano, o **vazio quase preto** no meio e um fio de luz
  branco no eixo. Os quadros respiram (a lente abre e fecha ~9%) e a ondulação
  desce um quarto de fenda por quadro.
- A paleta é a **mesma rampa do metatile de portal do `gTileset_AltarSunMoon`**
  (`palettes/11.gbapal`): o rasgo no chão e o disco na parede são visivelmente a
  mesma coisa. `OBJ_EVENT_PAL_TAG_ALTAR_RIFT = 0x116C`.
- `SHADOW_SIZE_NONE`: um rasgo no ar não faz sombra.
- `sAnimTable_AltarRift` aponta todas as 20 entradas para o mesmo loop, que é o
  padrão do `sAnimTable_TowerBeam` — o objeto é `inanimate` e nunca vira para
  lado nenhum.

**O `OBJ_EVENT_GFX_PORTAL` não foi tocado**: o `SpearPillarTop` continua com os
quatro portais dele exatamente como estavam. A regra em `spritesheet_rules.mk`
é `-mwidth 4 -mheight 4` (32x32), e não a do portal antigo.

### 18.3 Looker e Anabel moram lá, então se mexem

Os dois ficavam com `MOVEMENT_TYPE_FACE_UP` para sempre, encarando a fenda em
posição de sentido. A partir do estado **16** eles passam a
`MOVEMENT_TYPE_WANDER_AROUND`.

A troca é feita com `setobjectmovementtype` no **`ON_TRANSITION`**, e o lugar não
é escolha de estilo: `setobjectmovementtype` escreve no **template**
(`gSaveBlock1Ptr->objectEventTemplates`), não no objeto vivo, então só vale a
partir do próximo spawn — e o `ON_TRANSITION` é justamente o script que roda
**depois** de `LoadObjEventTemplatesFromHeader` ter reposto os templates e
**antes** de os objetos nascerem. Do `ON_LOAD` ou de um script de objeto não
mudaria nada.

Estados **12..15 ficam intocados de propósito**: os Atos I e V posicionam os dois
por coordenada e os viram com `turnobject`, e um NPC andando quebraria a
marcação de duas cenas com build limpo.

O alcance é 1 nos dois eixos (`map.json`), medido contra a colisão real:

| NPC | Tile | Alcança | Não alcança |
|---|---|---|---|
| Looker | (13,13) | x 13..14, y 12..14 | (14,10) a fenda, (14,11) o tile de volta da arena |
| Anabel | (15,13) | x 14..15, y 12..14 | idem |

O gargalo em `y=12` tem três tiles (x=13..15) e eles são dois: **nunca conseguem
fechar a passagem**.

### 18.4 O presente dizia "SOLGALEO", e a captura não acontecia na tela

**Dois defeitos no mesmo trecho.**

**O nome errado.** O Pokémon entregue sempre foi `SPECIES_NECROZMA` — a party
recebia o certo. O que estava errado era a **caixa**:
`Common_Text_ReceivedMon` é `"{PLAYER} received {STR_VAR_1}!"` e **nada no
caminho do `givemon` escreve `STR_VAR_1`** (`ScrCmd_createmon` →
`ScriptGiveMon` → `GiveScriptedMonToPlayer`: nenhum toca no buffer). Três caixas
antes, `UltraSpaceArena_EventScript_PartnerHarmonise` fazia
`bufferspeciesname STR_VAR_1, VAR_TEMP_4` para o `Text_VictoryHarmony` — e
`VAR_TEMP_4` guarda a espécie do **parceiro**. Resultado: "received SOLGALEO".

A convenção do repositório para presente de Pokémon (`BlackthornCave`,
`CianwoodPokecenter`, `BattleCafe`, `RuinsOfAlph_Lab`) é sempre este par, e ele
faltava aqui:

```asm
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_NECROZMA
	bufferspeciesname STR_VAR_1, SPECIES_NECROZMA
	givemon SPECIES_NECROZMA, 75, ITEM_NONE
```

`VAR_TEMP_TRANSFERRED_SPECIES` é o que `Common_EventScript_TransferredToPC` lê
para a caixa do PC (sem ele, "Bulbasaur foi para o PC"), e **é o mesmo var que
`VAR_TEMP_1`** (`include/constants/vars.h`), que esta arena usa como trava de
uma-vez-por-visita do `ON_FRAME`. `SPECIES_NECROZMA` é diferente de zero, então
a trava continua fechada. **Nunca escrever 0 nele aqui.**

**A captura na tela.** Está em §18.4 do roteiro
([`ALTAR_SUN_MOON_SCRIPT.md`](ALTAR_SUN_MOON_SCRIPT.md), "A captura"), passo a
passo. Resumo: `SE_BALL_THROW` → `enter_pokeball` no objeto do Necrozma (a
animação do próprio motor: pisca branco, encolhe dentro de uma Ball, termina
invisível) → a **Beast Ball** aparece como objeto próprio no tile dele → três
chacoalhadas e o clique só em som → `MUS_HG_CAUGHT` → a narração → só então o
`givemon`.

Objetos e gráficos novos:

| Coisa | Onde |
|---|---|
| `OBJ_EVENT_GFX_BEAST_BALL` (336) | `event_objects.h`, `object_event_graphics_info.h`, `..._pointers.h` |
| `sPicTable_BeastBall` | `object_event_pic_tables.h`, **fora** do `#if OW_FOLLOWERS_POKEBALLS` — o do follower está dentro dele, e um objeto de mapa não pode depender dessa config |
| `LOCALID_ULTRA_SPACE_ARENA_BEAST_BALL` (6) | `UltraSpaceArena/map.json`, (10,8), `FLAG_TEMP_6` |
| `setflag FLAG_TEMP_6` | `UltraSpaceArena_OnTransition` — a Ball entra na mesma regra de "tudo escondido em toda carga" dos outros cinco |

A arte é a que `gPokeballGraphics[BALL_BEAST]` já usava; ela só ganhou um
`OBJ_EVENT_GFX_*` para poder entrar num `map.json`. **Nenhum PNG novo.**

A checagem de espaço **mudou de lugar**: era depois do `givemon` (guarda
`MON_CANT_GIVE`), agora também acontece **antes** da Ball sair da mão da Anabel,
com o mesmo teste da fenda. A guarda velha continua onde estava, como rede; o
teste novo existe porque a partir daquela linha a cena **afirma** que a criatura
está dentro da Ball, e o ramo `NoRoom` não pode disparar depois disso.

### 18.5 A tela branca na fenda diária — o que se sabe, o que não se sabe

**Sintoma:** evento encerrado (estado 16, Looker e Anabel morando no altar), o
jogador fala com a fenda, responde SIM, e a tela fica **branca** com o jogo
travado. O mesmo caminho no estado 14 (a ida para a boss battle) funciona — o
autor jogou a luta inteira.

**O que foi verificado e descartado:** o par `fadescreen`/`warpsilent` é
idêntico nos dois estados (só muda o `setflag FLAG_DAILY_ALTAR_RIFT`);
`Task_WarpAndLoadMap`, `TryFadeOutOldMapMusic`, `BGMusicStopped`,
`DoEnterCaveTransition` e toda a cadeia `Task_EnterCaveTransition1..4` terminam e
entregam para `gMain.savedCallback`; as flags da arena estão todas dentro do
array de save; os textos não têm código de controle quebrado; o `map.bin` e as
colisões dos dois mapas estão corretos.

**O achado duro, e é o único lugar de onde pode sair branco nesse warp:**

```c
// src/fldeff_flash.c
{MAP_TYPE_ROUTE, MAP_TYPE_UNDERGROUND, TRUE, FALSE, DoEnterCaveTransition},
```

O Altar é `MAP_TYPE_ROUTE` e a arena é `MAP_TYPE_UNDERGROUND`, então o motor
trata essa passagem como **entrar numa caverna**: `WarpFadeOutScreen()` consulta
`GetMapPairFadeToType(ROUTE, UNDERGROUND)`, recebe `isEnter = TRUE` e faz
**`FadeScreen(FADE_TO_WHITE)`**, e depois roda a íris branca de entrada de
caverna antes de o mapa aparecer. E:

> `MAP_ULTRA_SPACE_ARENA` é o **único** dos **243** mapas `MAP_TYPE_UNDERGROUND`
> do jogo alcançado por `warpsilent` em vez de um warp event. Todos os outros
> 242 são cavernas em que se entra andando pela boca.

Ou seja, o caminho existe, é branco por construção e nunca foi exercitado assim
em nenhum outro lugar do projeto.

**O que foi feito (sem afirmar que resolve):** o `EventScript_EmptyRift` passou a
abrir exatamente como a cena do Ato IV, que é o caminho que comprovadamente
funciona — `lockall` / `hidefollower` / `delay 20` antes de qualquer caixa —, e
ganhou um `applymovement` que vira o jogador para o norte. Esse `applymovement`
conserta de passagem um defeito real e independente: o `warpsilent` larga o
jogador em (10,19) **de frente para o sul**, a um passo da fileira de
`coord_event` em `y=20` que o joga de volta para o altar — ele chegava apontando
para a saída.

**Se ainda travar**, o próximo passo é trocar o `map_type` da arena de
`MAP_TYPE_UNDERGROUND` para `MAP_TYPE_UNKNOWN`: o par `ROUTE → UNKNOWN` **não**
está em `sTransitionTypes`, então a transição de caverna deixa de existir e o
warp vira preto simples nos dois sentidos. Não foi feito agora porque muda
quatro coisas de tabela (`CurrentMapHasShadows`, o `BATTLE_ENVIRONMENT_CAVE`
padrão, o `TRANSITION_TYPE_CAVE` da batalha e o "conta como noite" do
`battle_script_commands.c`) e não se troca comportamento de motor por palpite. A
íris branca de entrada de caverna, aliás, é **errada de qualquer jeito** para um
rasgo no Ultra Space.

### 18.6 Arquivos tocados na revisão 4

| Arquivo | O quê |
|---|---|
| `include/region_map.h` | `MAP_NAME_LENGTH_MAX`, `mapSecName[]` maior, o comentário do porquê |
| `src/map_name_popup.c` | `mapDisplayHeader[]` maior, `MAP_NAME_POPUP_PREFIX_SIZE` |
| `src/data/region_map/region_map_sections.json` | nome do `MAPSEC_ABANDONED_LAB`. É a **fonte de verdade**: o `region_map_entries.h` é gerado dele e é gitignored — não edite o `.h` |
| `graphics/object_events/pics/misc/altar_rift.png` | **novo** — 128x32, quatro quadros |
| `graphics/object_events/palettes/altar_rift.pal` | **novo** |
| `spritesheet_rules.mk` | regra `-mwidth 4 -mheight 4` da fenda |
| `include/constants/event_objects.h` | `OBJ_EVENT_GFX_ALTAR_RIFT`, `OBJ_EVENT_GFX_BEAST_BALL`, `NUM_OBJ_EVENT_GFX` 335→337, `OBJ_EVENT_PAL_TAG_ALTAR_RIFT` |
| `src/data/object_events/object_event_graphics.h` | os dois `INCBIN` da fenda |
| `src/data/object_events/object_event_pic_tables.h` | `sPicTable_AltarRift`, `sPicTable_BeastBall` |
| `src/data/object_events/object_event_anims.h` | `sAnim_AltarRiftLoop`, `sAnimTable_AltarRift` |
| `src/data/object_events/object_event_graphics_info.h` | os dois `ObjectEventGraphicsInfo` |
| `src/data/object_events/object_event_graphics_info_pointers.h` | os dois ponteiros + `extern` |
| `src/event_object_movement.c` | paleta da fenda em `sObjectEventSpritePalettes` |
| `data/maps/SunMoonAltar/map.json` | fenda usa o gráfico novo; alcance 1 para Looker e Anabel |
| `data/maps/SunMoonAltar/scripts.inc` | `ApplyResidents` no `ON_TRANSITION` |
| `data/maps/UltraSpaceArena/map.json` | objeto da Beast Ball |
| `data/maps/UltraSpaceArena/scripts.inc` | `FLAG_TEMP_6`, cena de captura, correção do `STR_VAR_1`, checagem de espaço adiantada, `EmptyRift` endurecido |
| `docs/SOULGOLD_FLAGS_AUDIT.csv` | regerado: única mudança é `FLAG_TEMP_6` ganhando mais um mapa |

Nenhuma flag persistente nova — a revisão 4 mantém a propriedade do §3.1.

### 18.7 O que ainda precisa de runtime

- [ ] **Item 5.** Entrar na fenda diária no estado 16 e confirmar se a tela
      branca acabou. Se não, aplicar a troca de `map_type` do §18.5.
- [ ] **Item 1.** Abrir o Town Map dentro do Altar e ver "Sun & Moon Altar"
      inteiro na caixa, sem crash. Conferir também o popup ao entrar no mapa.
- [ ] **Item 2.** Ver a fenda animada em (14,10) nos estados 14, 15 e 16, e
      conferir que os portais do `SpearPillarTop` continuam iguais.
- [ ] **Item 3.** Estado 16: Looker e Anabel andando, e o gargalo em `y=12`
      nunca fechado.
- [ ] **Item 4.** Ganhar o boss e ver a Ball voar, chacoalhar três vezes e a
      caixa dizer **"received NECROZMA"**. Com a party cheia e o PC cheio, ver o
      `NoRoom` disparar **antes** da animação.
- [ ] **Item 6 (revisão 5).** Na arena, ver o **sprite dourado de verdade** em
      (10,8) — não o boneco do Substitute — e o Necrozma pequeno depois da
      batalha. Sobre *quando* cada forma aparece, ver o item 7 do §20.5: desde a
      revisão 6 ela já chega Ultra, não há transformação no meio da cena.

---

## 19. Retorno do autor em runtime (revisão 5, 25/09/2026) — o sprite do Ultra Necrozma

> *"Coloca o Ultra Necrozma como exception porque a gente usa o sprite dele na
> história."* — e, em seguida: *"aplica corretamente o sprite do Ultra Necrozma
> no Altar, dentro do rift também."*

Sexto item do mesmo teste em runtime. **Nada em `data/maps/` estava errado.** A
arena já tinha o objeto certo, no tile certo, com a flag certa, e a troca já
estava encenada desde a revisão 3. O que faltava era engine: o
`SPECIES_NECROZMA_ULTRA` não tinha dado de overworld nenhum, e a cena desenhava
o boneco do Substitute no lugar da criatura.

### 19.1 A causa

`include/config/overworld.h` traz `OW_BATTLE_ONLY_FORMS FALSE` — a config que
corta o sprite de overworld de **todas** as formas só-de-batalha (megas, ultra
burst) para economizar ROM. Em `gen_7_families.h`, o bloco `OVERWORLD(...)` do
`SPECIES_NECROZMA_ULTRA` estava inteiro sob `#if OW_BATTLE_ONLY_FORMS`, e a
`sPicTable_NecrozmaUltra` também.

Com o bloco fora, `gSpeciesInfo[SPECIES_NECROZMA_ULTRA].overworldData.tileTag`
fica **0**, e aí:

```c
// src/event_object_movement.c, GetObjectEventGraphicsInfo
if ((graphicsInfo->tileTag == 0 && species < NUM_SPECIES) || ...)
{
    if (OW_SUBSTITUTE_PLACEHOLDER)
        return &gSpeciesInfo[SPECIES_NONE].overworldData;   // o boneco
    return NULL;
}
```

`OW_SUBSTITUTE_PLACEHOLDER` é `TRUE` no projeto. **Por isso o build sempre
fechou limpo e a cena sempre rodou** — ela só desenhava a coisa errada. É o tipo
de armadilha que o `CLAUDE.md` descreve: compila, roda, e quebra na tela.

O §17 do [`SOULGOLD_RIFT_ARCO_NARRATIVO.md`](../SOULGOLD_RIFT_ARCO_NARRATIVO.md)
já tinha apontado o `#if OW_BATTLE_ONLY_FORMS` como "ponto concreto de
investigação", sem conseguir provar o fallback. Era esse.

### 19.2 A correção — uma feature flag só do Ultra Necrozma

O mesmo §17 recomendava **não** ligar `OW_BATTLE_ONLY_FORMS` inteiro
("não recomendar ligar todas as formas de batalha indiscriminadamente: avaliar
um ator específico de cena ou habilitação seletiva, com medição de memória").
Foi o que se fez — uma exceção por espécie, ao lado da config original:

```c
#define OW_BATTLE_ONLY_FORMS           FALSE
#define OW_BATTLE_ONLY_FORMS_NECROZMA_ULTRA TRUE  // SoulGold: per-species exception...
```

Três portões passaram a aceitar as duas condições
(`OW_BATTLE_ONLY_FORMS || OW_BATTLE_ONLY_FORMS_NECROZMA_ULTRA`):

| Arquivo | O quê |
|---|---|
| `include/config/overworld.h` | a config nova, logo abaixo de `OW_BATTLE_ONLY_FORMS` |
| `src/data/object_events/object_event_pic_tables_followers.h` | a `sPicTable_NecrozmaUltra` |
| `src/data/pokemon/species_info/gen_7_families.h` | o `OVERWORLD(...)` do `SPECIES_NECROZMA_ULTRA` |
| `include/event_object_movement.h` | `#error` novo, espelhando o de `OW_BATTLE_ONLY_FORMS`: a exceção também exige `OW_POKEMON_OBJECT_EVENTS` |

As megas continuam cortadas. Nenhum `.json`, `.inc` ou `.pory` mudou.

### 19.3 A medição de memória que o §17 pediu

Duas `make` completas, só trocando a config nova:

| `OW_BATTLE_ONLY_FORMS_NECROZMA_ULTRA` | ROM | EWRAM | IWRAM |
|---|---|---|---|
| `FALSE` | 31 149 932 B | 247 140 B | 24 172 B |
| `TRUE` | 31 149 940 B | 247 140 B | 24 172 B |

**+8 bytes de ROM. Zero de RAM.** O motivo: em `src/data/graphics/pokemon.h` os
`INCBIN` de `gObjectEventPic_NecrozmaUltra` e das duas paletas de overworld
estão sob `P_ULTRA_BURST_FORMS` e `OW_POKEMON_OBJECT_EVENTS`, **não** sob
`OW_BATTLE_ONLY_FORMS`. A folha e as paletas já estavam na ROM nos dois builds
(confirmado no `Soulgold.map`: `gObjectEventPic_NecrozmaUltra` aparece com a
config desligada). Ou seja: o projeto já pagava pelo sprite e não o usava. Os
8 bytes são a tabela de quadros.

### 19.4 O que isso muda na tela

Dois lugares, e os dois já estavam escritos:

| Mapa | Objeto | Cena |
|---|---|---|
| `UltraSpaceArena` | `LOCALID_ULTRA_SPACE_ARENA_ULTRA` (10,8), `FLAG_TEMP_3` | `UltraSpaceArena_EventScript_Confront`: `FADE_TO_WHITE` → `removeobject` Necrozma → `addobject` Ultra → `playmoncry SPECIES_NECROZMA_ULTRA`. E o caminho de volta, depois da batalha |
| `NewBarkTown` | `LOCALID_NEWBARK_UB_ULTRA_NECROZMA` | a aparição do evento pré-altar |

O `dump_mapa.py` confirma a premissa do **risco 5**: os três objetos que dividem
(10,8) na arena — `NECROZMA` (`FLAG_TEMP_2`), `ULTRA` (`FLAG_TEMP_3`) e
`BEAST_BALL` (`FLAG_TEMP_6`) — continuam com flags separadas, então só um existe
por vez. A folha é 256x32 (oito quadros de 32x32), igual à do Necrozma comum que
ocupa o mesmo tile, então a coreografia não muda de tamanho na tela.

### 19.5 Limite

`SIZE_32x32`, com o `//TODO: 64x64 overworld sprite!` que veio do upstream. Se o
clímax pedir um Ultra Necrozma **grande** na arena, isso é arte nova mais
`SIZE_64x64` mais `OW_LARGE_OW_SUPPORT` (já `TRUE`) — trabalho separado, fora
desta revisão.

---

## 20. Retorno do autor em runtime (revisão 6, 25/09/2026) — a criatura chega dourada

> *"O Necrozma fica dourado em New Bark, quando ele absorve as últimas 2 beasts.
> Na fenda ele deveria ser sempre Ultra Necrozma até ser derrotado e virar
> Necrozma novamente."*

Continuidade, e ele tem razão. O `NewBarkTown_EventScript_UBUltra` transforma a
criatura **e ela vai embora dourada** — `NewBarkTown_EventScript_UBUltraLeaves`
remove o objeto Ultra, não o pequeno. Ninguém nunca tirou aquela luz dela. A
arena estava contando a transformação **uma segunda vez**, como se o jogador não
tivesse visto a primeira.

### 20.1 A regra, agora escrita

**Durante o Ato IV só existe a forma Ultra nesta sala.** O
`LOCALID_ULTRA_SPACE_ARENA_NECROZMA` não é spawnado em lugar nenhum da
confrontação; o `FLAG_TEMP_2` dele fica setado desde o `ON_TRANSITION` até o fim
da batalha. O **único** script que põe a forma pequena no chão é o
`UltraSpaceArena_EventScript_Victory` — a forma pequena passou a significar uma
coisa só: **perder a luz**. É o que o §18.4 já tinha montado do outro lado
(`Text_VictoryArmourOff` → `addobject ..._NECROZMA` → captura → `givemon
SPECIES_NECROZMA, 75`), e agora os dois lados combinam.

### 20.2 O que mudou na cena

| Antes | Agora |
|---|---|
| `addobject` Necrozma, `playmoncry SPECIES_NECROZMA` | `addobject` **Ultra**, `playmoncry SPECIES_NECROZMA_ULTRA` |
| leitura da Anabel → parceiro se põe na frente → **shake + troca de objeto** → `Text_ArenaUltra` | `Text_ArenaUltra` **na revelação** → leitura da Anabel → parceiro se põe na frente → **flare + grito + shake** → `Text_ArenaAnswers` |
| a criatura mudava | a criatura **repara** |

O compasso do parceiro não foi perdido — foi o que herdou o lugar da
transformação. `UltraSpaceArena_Movement_UltraFlare` (quatro
`walk_in_place_fast_down`, a mesma forma do `NewBarkTown_Movement_UltraFlare`)
mais o grito e o `ShakeCamera` que já existiam. **`_down` e não `_right`:** ela
está em (10,8) olhando para o sul, para o jogador em (10,11) e para o parceiro em
(9,9) — `y` cresce para baixo.

E isso faz a fala seguinte funcionar melhor do que antes: a Anabel abre com
*"Behind me. Now. …Right. It looked at you"* logo depois de a narração dizer que
ela não tinha olhado para nada naquele chão até alguém se pôr entre a luz e o
jogador.

### 20.3 Texto

- `UltraSpaceArena_Text_ArenaUltra` — reescrito. Era a narração **da** transformação ("The armour came back on in pieces"); virou a narração **da chegada** ("It is already burning. Whatever it put on in New Bark it has not put down"). As duas imagens boas do original — o ladrão e o afogado — ficaram.
- `UltraSpaceArena_Text_ArenaAnswers` — **novo**, a narração do momento em que ela repara no parceiro.
- Nada mais mudou: `ArenaLook`, `ArenaAnabelReads`, `ArenaStarving`, `ArenaAnabelFront` e todo o bloco da vitória estão intactos.

`medir_linha.py`: nenhuma linha do mapa passa de 208 px. `checar_falantes.py`:
14 falantes em ordem. As duas narrações são `msgbox` próprios entre
`closemessage`, então não herdam a plaquinha da Anabel.

### 20.4 Arquivos tocados na revisão 6

| Arquivo | O quê |
|---|---|
| `data/maps/UltraSpaceArena/scripts.inc` | abertura do `Confront`, `Movement_UltraFlare`, `Text_ArenaUltra` reescrito, `Text_ArenaAnswers` novo |

Só isso. Nenhum `map.json`, nenhuma flag, nenhum `local_id` novo — os dois
objetos já existiam e continuam existindo, com as mesmas flags.

### 20.5 Runtime

- [ ] **Item 7.** Entrar na fenda no estado 14 e ver a criatura **já dourada** no
      primeiro flash, sem transformação nenhuma no meio da cena; o parceiro se
      pôr na frente e ela dar o flare no lugar; e, ao ganhar, a armadura sair e
      sobrar o Necrozma pequeno para a captura.
