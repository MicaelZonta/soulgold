# B07 — Warps com destino inválido e gatilhos que nunca disparam

**Gravidade:** BAIXA/MÉDIA · **Status:** CORRIGIDO em 30/09/2026, exceto os warps do Battle Tower (build limpo; falta teste no mGBA)

## Warps

| Origem | Problema | O que a engine faz |
|---|---|---|
| `Route22/map.json` warp 0 (12,9) → `MAP_RECEPTION_GATE` warp **4** | ReceptionGate só tem warps 0–3 | `SetPlayerCoordsFromWarp` (`src/overworld.c:654`): warp id inválido e sem x,y → jogador cai no **centro do mapa** (11,10), que por sorte é chão |
| `ReceptionGate/map.json` warp 3 (1,9) → Route 28 | pelo `dump_mapa.py`, (1,9) fica cercado de parede; a área andável é x=9..12 | portão para a Route 28 inacessível por dentro — conferir no Porymap |
| `BattleFrontier_BattleTowerBattleRoom/map.json` warps 0,1 → Lobby warp **2** | Lobby só tem 0–1 | mesmo fallback; provavelmente nunca pisados (sala controlada por script) |

Não há warp de volta do ReceptionGate para a Route 22: a ida é de mão única.
Decidir se a Route 22 deveria ter par no portão.

## Gatilhos mortos (var comparada com valor que nada escreve)

| Onde | Condição | Valores escritos | Efeito |
|---|---|---|---|
| `IcePath_1F/map.json` coord (49,29) `IcePath_1F_Trigger_KimonoGirl` | `VAR_ICE_PATH_STATE == 1` | 0 (Mahogany), 2 (Ice Path) | a fala "Leave" + empurrão nunca acontece. Mudou em `44c11bc004`; confirmar se o gatilho ainda é desejado |
| `TinTower_1F/scripts.inc:7,22,37` e `EcruteakCity_SageOffice1/scripts.inc:74-75` | `VAR_ECRUTEAK_CITY_STATE == 10/11` | 0–4 | as falas dos sábios sobre Ho-Oh nunca aparecem |

## Frágil

`MtMoon_Cave/scripts.inc:15-16` dispara a cena do Silver com
`VAR_GARBAGEVAR == 0 ou 1` e marca 2 no fim. Funciona hoje, mas
`VAR_GARBAGEVAR` é a var-lixo do projeto (escrita por dezenas de scripts de
Hoenn, vários ainda montados na ROM): se algo a voltar para 0, a cena do rival
se repete com o Silver escondido. Trocar por uma var ou flag própria
(`FLAG_HIDE_MTMOON_SILVER` já existe e é setada no fim da cena).

## Id de objeto de outro mapa

`BlackthornCity_House3/scripts.inc:7` usa `LOCALID_MOVE_DELETER`, que é de
`LilycoveCity_MoveDeletersHouse`. Vale 1 e o objeto 1 de Blackthorn é o próprio
Move Deleter — funciona por coincidência; quebra se a ordem dos objetos mudar.

## Correção aplicada (30/09/2026)

- **Route 22 ↔ ReceptionGate** (decisão do autor: easter egg por enquanto):
  warp 4 novo no ReceptionGate em (9,9), chão comum, só ponto de chegada — o
  warp da Route 22 que apontava para "4" passou a valer. Uma rachadura na
  parede oeste (`bg_event` em (8,9), olhando para oeste,
  `ReceptionGate_EventScript_HiddenPassage`) leva de volta à porta da Route 22
  só com `FLAG_SYS_GAME_CLEAR`; antes disso mostra "A faint draft...". O warp 3
  (1,9) → Route 28 continua isolado e sem uso.
- **Ice Path** (decisão do autor: bloquear até ajudar): falar com a Kimono Girl
  pela primeira vez (sem ser pelo norte) põe `VAR_ICE_PATH_STATE` em 1; o
  gatilho de (49,29), único corredor para Blackthorn, empurra o jogador de
  volta até ela ser empurrada para fora do gelo (estado 2).
- **Sábios de Ecruteak/Tin Tower**: `VAR_ECRUTEAK_CITY_STATE == 10/11` (sobra do
  HGSS) trocado por `VAR_COMPLETED_HO_OH == 2 ou 4` (Ho-Oh no topo / encontro
  pós-história), que é quando as falas fazem sentido.
- **Mt. Moon**: a cena do Silver agora é armada no `ON_TRANSITION` por
  `VAR_TEMP_1` enquanto `FLAG_HIDE_MTMOON_SILVER` está limpa; não usa mais
  `VAR_GARBAGEVAR`.
- **Blackthorn Move Deleter**: `applymovement VAR_LAST_TALKED` no lugar do
  `LOCALID_MOVE_DELETER` de Lilycove.
