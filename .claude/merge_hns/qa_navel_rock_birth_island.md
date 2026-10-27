# QA no jogo: ganchos Navel Rock / Birth Island e time de Vermilion (27/10/2026)

Rodado com o mGBA headless patchado (skill testar-no-jogo) sobre a Soulgold.gba
do build limpo de 27/10. Jogo novo (o Soulgold.sav antigo nao oferecia Continue),
estado montado direto na RAM (var/flag) e Set Party do menu de debug.
Nada de codigo de jogo foi editado.

## Resultados

| Teste | Resultado | Evidencia |
|---|---|---|
| T1 Bill le o ritmo (var=1) | PASS | falas NavelRockQuest_Text_BillReads na tela; VAR_NAVELROCK_QUEST lido na RAM: 1 antes, 2 depois |
| T1 controle (var=0) | PASS | Bill oferece Eevee/Pikachu normalmente; var continua 0 |
| T2 Colress no lab de Alph | PASS | NPC criado (objetos.py lista local 8 em (2,2)), visivel e fala "I'm a guest in this lab." |
| T3 Soliera no topo do farol | PASS | NPC local 2 em (11,8) ativo, visivel, fala "I have no duty here." |
| T4 Lt. Surge | PASS | Electrode Lv72 na batalha; gEnemyParty na RAM: niveis 72,74,73,73,74,75 (= trainers.party, Raichu Lv75 por ultimo) |

## Agenda no momento do teste

VAR_DAY_OF_WEEK = 1 (segunda-feira no calendario do jogo) e GetTimeOfDay = 2
(tarde/EVENING). Pela tabela: Colress segunda so tem fatia de dia (DAYLIGHT)
na Birth Island, entao cai no curinga (Alph); Soliera so fica na ilha ter/qui/sab
a noite, entao cai no curinga (farol). Nao foi preciso mexer no relogio.
FLAG_MET_COLRESS e FLAG_MET_SOLIERA setadas por flag.py.
NAO foi testado o lado oposto (ele/ela sumindo do lab/farol quando a agenda diz
Birth Island), nem a Birth Island em si.

## Observacoes

- Zapdos de Galar aparece no topo do farol em jogo novo (FLAG_HIDE_ZAPDOS_GALAR
  nao setada); nao e defeito do gancho.
- O ginasio de Vermilion precisa de FLAG_FOUND_BOTH_VERMILION_GYM_SWITCHES
  (setada pela RAM) e o mapa recarregado; rota.py/ir.py nao enxergam o raio
  aberto (colisao do map.bin), entao as ultimas casas foram a mao (UP x5).
- Falha de ambiente (nao do jogo): o setup.sh nao instala liblua5.4-dev se o
  gcc ja existe; sem Lua o qa-headless sobe e o driver nao carrega. Contornado
  extraindo o .deb em /tmp/luadeb (sem root) e compilando em /tmp/qa-build2.
- Primeiro teste de T4 acabou em blackout em jogo novo sem time; resolvido com
  Party > Set Party.

Prints: /tmp/claude-1000/-home-ADMIN-decomps-soulgold-v1/834b9dc2-e09d-45a1-9c25-9a88c950c27b/scratchpad/ev/
