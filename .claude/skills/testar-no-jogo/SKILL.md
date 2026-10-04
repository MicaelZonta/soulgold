---
name: testar-no-jogo
description: Use para TESTAR NO JOGO de verdade, sem humano - rodar um roteiro de QA (ex. .claude/berry_master/TESTES_NO_JOGO.md), confirmar que uma cena/NPC/flag/presente funciona em runtime, reproduzir um bug, ou gerar evidencia (prints, estado da RAM). Sobe o mGBA patchado em modo headless com um driver Lua, aperta botoes, tira screenshots, le posicao/bolsa/objetos direto da RAM, navega pelo menu de debug (L+START) e anda ate coordenadas com rota calculada. Cobre as armadilhas que fazem o teste mentir - texto engolindo inputs, cursor de menu lembrado, virada que come o passo, borda de tapete, limite de objetos, save que some ao fechar - e como reportar PASS/FALHA com evidencia.
---

# Testar no jogo (QA headless)

Build limpo prova só que compila. Esta skill **joga** a ROM: mGBA headless,
comandado por arquivo, com prints e leitura de RAM. Tudo fica em
`.claude/qa/`.

## 1. Subir o ambiente (uma vez por sessão)

```bash
.claude/qa/setup.sh            # toolchain, Pillow, mGBA headless com Lua, make -j
```

Depois suba o emulador **com `run_in_background: true`** no Bash (com `&`
ou `nohup` ele morre junto com o shell):

```bash
QA_BUILD=/tmp/qa-build .claude/qa/start.sh      # fica parado esperando comandos
```

O `setup.sh` compila o `headless-main.c` do `tools/mgba-master` numa cópia
com duas correções, **sem tocar no fonte do repo** (mudar o mGBA do repo
obriga a recompilar o de Windows):
- **buffer de vídeo**: sem ele `emu:screenshot()` grava um PNG de 33 bytes;
- **`mCoreAutoloadSave`**: sem ele o save do jogo vive só na memória e some
  ao fechar. Com ele, o save vai para `Soulgold.sav` ao lado da ROM
  (ignorado pelo git).

O RTC é o relógio do container (UTC). Se começar de noite, adiante com
`Berry Master… → Clock…` ou equivalente antes de tirar prints.

## 2. Mandar comandos

`q.py` manda um lote e espera o fim (o jogo fica **pausado** entre lotes):

```bash
Q=".claude/qa/q.py"
python3 $Q "press A" "wait 60" "shot /tmp/qa/x.png"
python3 $Q "rep 10 press A 6 40; shot /tmp/qa/y.png"     # ';' separa, rep N repete
```

Comandos do `driver.lua`: `press KEY [hold] [after]`, `combo L+START`,
`hold KEY N`, `wait N`, `shot PATH`, `save/load PATH` (savestate),
`r8/r16/r32 ADDR`, `range ADDR LEN`, `w8/w16/w32 ADDR VAL`, `quit`.
O headless roda a ~3000 fps: 600 quadros levam 0,2 s.

Macros em `lib.sh` (`. .claude/qa/lib.sh`): `clean` (B×8), `dbg_main N`,
`bm N` (submenu Berry Master), `clock`, `book`, `lvl`, `give ITEM QTD`,
`fill`, `clearbag`, `warp GRUPO MAPA WARP`, `num`/`num0` (seletor numérico
do debug), `seqshots PREFIXO N`, `pos`.

Ferramentas:

| Script | Faz |
|---|---|
| `ir.py Mapa X Y` | anda até (X,Y) com rota BFS e confere a posição na RAM a cada passo; se o alvo é bloqueado (NPC, árvore, cova), para ao lado **virado para ele**. Desvia só dos objetos **vivos** (lidos da RAM): NPC escondido por flag não tranca a rota |
| `rota.py Mapa X0 Y0 X1 Y1` | só calcula a rota (colisão do `map.bin` no bit 11, água e ledge pelo comportamento, bordas direcionais; sozinho, trata **todo** objeto do `map.json` como bloqueio, inclusive os escondidos) |
| `conversa.py PREFIXO --abrir --respostas NY` | conduz uma conversa: um print por caixa, responde Yes/No pela lista, para em menus que não são Yes/No |
| `bolsa.py [berries\|items\|key]` | lê um bolso da bolsa da RAM (quantidade decifrada) — prova objetiva de "recebeu X" |
| `objetos.py` | lista os `gObjectEvents` ativos — prova se um NPC/árvore foi criado |
| `flag.py FLAG_X [0\|1]` / `flag.py --dex N…` | lê ou muda uma flag do save (ex.: insígnia) e marca espécies como capturadas na Pokédex, direto na RAM; números e offsets compilados dos headers |
| `sprites.py` | lista os `gSprites` vivos com os tiles de VRAM e aponta sprite desenhando nos tiles de um objeto (gráfico “listrado”) |
| `grid.py OUT a.png b.png…` / `zoom.py` / `crop.py` | junta prints em grade, amplia, recorta a mesma região de vários prints lado a lado |

## 3. Armadilhas que fazem o teste mentir

1. **Caixa de texto aberta engole tudo.** O L+START, os passos e o menu
   viram "avançar texto". Sempre `clean` antes de abrir menu ou andar
   (`ir.py` já faz). `seqshots` **não** aperta A depois do último print, para
   não reabrir a conversa com o NPC à frente.
2. **Menus lembram o cursor.** O menu START (Save/Docs…) e o bolso da bolsa
   voltam onde você parou. Não conte "DOWN×2" às cegas: tire print do menu
   antes de confirmar.
3. **Virar come o aperto.** Parado e virado para outro lado, o primeiro
   aperto pode só virar o boneco. Use `ir.py` (confere na RAM e repete) ou
   segure mais de 16 quadros.
4. **Bordas direcionais.** Metatiles `MB_IMPASSABLE_WEST/EAST/…` (borda de
   tapete, mesa) bloqueiam a passagem só daquele lado. Na casa do Bram,
   (4,4)/(4,5) bloqueiam a borda oeste: de (4,5) não se vai para (3,5). O
   `rota.py` já lê isso do tileset.
5. **Yes/No precisa de espera.** O DOWN apertado enquanto o menu ainda aparece
   é ignorado e o A confirma **Yes**. `conversa.py` espera 30 quadros.
6. **Limite de objetos (`OBJECT_EVENTS_COUNT`, 24 desde 02/10/2026; era 16).** Num mapa cheio, NPCs e árvores de berry **não
   são criados**: ficam invisíveis e dá para andar por cima. O spawn só
   acontece quando o objeto **entra pela borda da câmera** com slot livre.
   Antes de concluir "a árvore não existe", rode `objetos.py`; mude o
   ângulo de chegada. (O WorldHub tinha esse problema com 16 slots; em
   03/10/2026 os grupos de NPC foram afastados do pomar e a pior janela
   ficou em 21 objetos, então todas as árvores são criadas.)
7. **Print durante a fala não mostra a mudança do mapa.** Metatile trocado por
   script (terra molhada, porta) pode só aparecer quando a caixa fecha.
   Tire o print de prova com a caixa fechada.
8. **Ferramentas de debug têm manias.** `Fill Pocket Berries/Items` só enche
   o que você ainda **não tem**; pilhas existentes ficam como estão.
   `Clear Bag` antes, quando o teste depende de bolsa cheia de verdade.
9. **O ponteiro da SaveBlock muda em tempo de jogo.** `gSaveBlock1Ptr` e
   `gSaveBlock2Ptr` trocam de endereço quando o mapa recarrega. Leia o
   ponteiro de novo a cada consulta (as ferramentas já fazem); um valor
   guardado num `$P` do shell lê lixo e inventa um bug (no reteste, a Oran
   "virou Kelpsy" por isso).
   **Endereços mudam a cada build.** Nunca fixe `0x0300…`: `ir.sym()` lê do
   `Soulgold.elf`. Offsets de struct (bolsa, árvores, flags) saem de
   `offsetof` compilado contra os headers:
   ```bash
   cat > /tmp/off.c <<'EOF'
   #include "global.h"
   #include <stddef.h>
   const int off = offsetof(struct SaveBlock1, berryTrees);
   EOF
   arm-none-eabi-cpp -iquote include -DMODERN=1 -DTESTING=0 -DEMERALD -std=gnu17 /tmp/off.c \
     | /usr/lib/gcc/arm-none-eabi/*/cc1 -quiet -mthumb -O2 -mabi=apcs-gnu -march=armv4t -std=gnu17 -o - - | grep -A1 '^off:'
   ```
10. **Input quadro-exato vicia o RNG.** Repetir a mesma sequência de
    botões, com os mesmos quadros, correlaciona os sorteios entre tentativas
    (cruzamento de berry: 1/16 e 2/14 contra 25% esperados). Com espera
    aleatória antes da ação que sorteia (`cruzar.py --jitter 300`), voltou a
    7/20. Para medir frequência, use jitter e amostra ≥ 20.
11. **O RTC é o relógio real.** O avanço rápido não adianta a hora do jogo.
    Para "esperar a meia-noite", acerte o relógio para 23:58 (`Utilities →
    Time Functions → Set wall clock`) e espere em tempo real (Monitor com
    `until`). Leia o relógio de parede pela RAM (`gTasks[t].data[2]` = horas,
    `data[3]` = minutos), não pelos ponteiros. O "Is this the correct
    time?" começa em **No** e fica no meio da tela (o `conversa.py` não o
    reconhece): `A`, `UP`, `A`.
12. **Detecção de caixa por pixel tem limites.** `conversa.py` reconhece
    caixa de texto, Yes/No do canto direito e menu no canto superior
    esquerdo (só olha a faixa y 36..56, abaixo da caixa de dinheiro e do
    pop-up de descrição de item, que também ficam no topo e enganavam a
    detecção). Menu novo em outro lugar = print e decisão manual.
13. **"Fechar e abrir o emulador" é literal**: `quit`, suba de novo com
    `start.sh`, título → START → Continue. Savestate não substitui esse
    passo (ele guarda a RAM inteira, inclusive o que o save perderia).

14. **Atalhos pela RAM (Parte 14–16 do Berry Master).** Para ir direto a um NPC atrás
    de piso de gelo ou treinadores: escreva `pos` em `gSaveBlock1Ptr` (offset 0, dois
    `s16`) e recarregue o mapa por uma ação do debug que chame `BerryDebug_ReloadMap`.
    Para não lutar meia hora contra um time escalado: HP 1 em `gBattleMons[1].hp`
    (`offsetof(struct BattlePokemon, hp)`) e em `gEnemyParty[i].hp` (`offsetof(struct
    Pokemon, hp)`) **só nos slots que têm espécie** — HP em slot vazio faz o jogo tentar
    mandar um Pokémon que não existe e a batalha trava. Diga no relatório quando usou.

## 4. Rodar um roteiro e reportar

- Siga o roteiro **na ordem**; faça `save /tmp/qa/st/<bloco>.ss` no começo
  de cada bloco e antes de cada escolha (Yes/No), para refazer sem
  recomeçar.
- Para cada teste, guarde a evidência em `/tmp/qa/ev/Tnn_*.png` e anote:
  **PASS**, **FALHA** (o que saiu × o esperado), **BLOQUEADO** (o teste não
  pôde rodar e por quê) ou **PASS com observação**.
- Prefira prova objetiva a "parece": RAM da bolsa (`bolsa.py`), posição
  (`pos`), objetos (`objetos.py`), cor de pixel antes/depois (terra
  molhada: (189,148,140) clara → (140,99,82) escura).
- **Confirme todo achado no print isolado**, ampliado, antes de reportar.
  Grade de prints serve para varrer, não para concluir: no reteste de 03/10 uma
  plaquinha da caixa vizinha foi lida como "narração herdando a plaquinha" e
  virou um falso defeito. Quando der, confirme também por pixel ou RAM.
- Separe defeito do jogo, defeito do roteiro (passo impossível, coordenada
  errada, ferramenta de debug que não faz o que o roteiro supõe) e erro seu
  de input. Erro de input não é achado: refaça a partir do savestate.
- No fim, publique um relatório com a tabela de resultados e os prints
  (Artifact), e diga ao autor o que é bug, o que é roteiro e o que ficou
  bloqueado.
