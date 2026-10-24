# Melemele Isle trava ao entrar (aberto, 24/10/2026)

**Sintoma:** ao chegar na Melemele Isle o jogo para de responder. A plaquinha
com o nome do mapa fica na tela para sempre, nenhum botão funciona, e o jogo
nunca volta.

Não é tela preta nem reset: a CPU continua viva (`gMain.vblankCounter1` avança
60 por 60 quadros), os callbacks continuam `CB1_Overworld`/`CB2_Overworld`, mas
o **laço principal não roda** (`UpdateTilesetAnimations` não é mais chamada).

## Como reproduzir (QA headless)

```bash
.claude/qa/setup.sh && QA_BUILD=/tmp/qa-build .claude/qa/start.sh   # background
# jogo novo até o overworld, depois:
. .claude/qa/lib.sh; python3 .claude/qa/q.py "$(warp 36 2 0)"      # Melemele Isle
python3 .claude/qa/q.py "wait 300" "press START" "wait 90" "shot /tmp/qa/x.png"
```

O START não abre menu nenhum. Para comparar, `warp 0 12 0` (Route 30) funciona
normalmente no mesmo build.

## O que já foi descartado

| Suspeito | Veredito |
|---|---|
| Animação do tileset de Alola (porte de 24/10) | **não é**: trava igual com `.callback = NULL` |
| `OBJECT_EVENTS_COUNT` 40 | **não é**: trava igual com 24 |
| `MAX_SPRITES` 127 | idem (estava 127 nos dois testes) |
| Flash de 256 KB / save novo | Route 30 e New Bark funcionam no mesmo build |
| Índice fora da tabela de tema da plaquinha | **não é**: depois do desconto de Kanto (−106) o índice da Melemele é 210, dentro das 255 entradas de `sRegionMapSectionId_To_PopUpThemeIdMapping` |

Ou seja: o defeito **já existia** no conteúdo importado de Alola (Fase 8) e
nunca apareceu porque ninguém jogou Alola — o QA de 24/10 ficou em Johto/Kanto.

## A pista

Três leituras do PC durante o travamento caem todas dentro de
`HBlankCB_DoublePopupWindow` (`src/menu.c`), chamado por `HBlankIntr`. Esse
callback é instalado por `src/map_name_popup.c` quando
`OW_POPUP_GENERATION == GEN_5` e só é retirado quando a tarefa da plaquinha
termina — tarefa que roda no laço principal. Se o laço parou, a plaquinha fica
e o HBlank também: por isso o sintoma se alimenta.

Falta saber **o que para o laço**. O próximo palpite a testar é o script do
mapa: `MelemeleIsle_MapScripts_MAP_SCRIPT_ON_TRANSITION` faz
`setvar VAR_OBJ_GFX_ID_1, OBJ_EVENT_GFX_SPECIES(RATICATE_ALOLA)` (ou LEAFEON de
dia) — um objeto com sprite de **espécie**. Se a folha de overworld dessa
espécie não existir ou vier com stream LZ quebrado, o descompressor entra em
laço e o jogo para exatamente assim.

## Como continuar

1. Entrar em outro mapa de Alola que **não** use objeto de espécie (Akala
   Forest, Ulaula) — se não travar, é o sprite da espécie.
2. Trocar `OBJ_EVENT_GFX_SPECIES(RATICATE_ALOLA)` por um NPC comum no
   `ON_TRANSITION` e ver se destrava.
3. Conferir se `RATICATE_ALOLA` e `LEAFEON` têm folha de overworld no nosso
   repositório (o HnS tinha a dele).
4. O `pc` novo do `driver.lua` (r0..r15) é a ferramenta: com o jogo travado,
   três leituras dizem onde ele está.

Enquanto não estiver resolvido, **Alola não é jogável** — vale avisar antes de
qualquer QA que passe por lá.
