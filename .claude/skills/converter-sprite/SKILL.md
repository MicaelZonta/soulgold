---
name: converter-sprite
description: Use ao trazer arte de personagem de fora para o GBA - sprite de treinador do Showdown/DeviantArt (80x80, ampliado, fundo colorido), folha de overworld de comunidade em grade (4x4, 3x4, ampliada 2x) ou qualquer PNG com mais de 16 cores - e transformar em front pic 64x64 e overworld de 9 quadros (16x32 ou 32x32). Tambem use para decidir entre 16x32, 32x32 ou um quadro so, calcular quanto um lote de personagens custa de ROM, conferir um PNG antes de registrar, e quando o usuario reclamar que um sprite desenhado por codigo ficou ruim.
---

# Converter sprite de fora para o GBA

Restrições, formatos e custos medidos:
**[`.claude/sprites-restricoes-e-custos.md`](../../sprites-restricoes-e-custos.md)**.
Ferramenta: `dev_scripts/sprites/sprite_gba.py` (precisa de `pip install pillow`).

Depois de converter, registre no jogo com a skill `adicionar-npc` (overworld)
e `adicionar-grafico-trainer` (front pic / mugshot).

## Não desenhe personagem por código

Pixel art gerado por código (polígonos, contorno automático, recolorir sprite
de outro personagem) **não chega no nível** dos sprites de comunidade que o
jogo usa. O autor recusou o rascunho do Guzma feito assim ("horrível"). O
caminho que funciona: **arte pronta de comunidade, com crédito**, convertida
sem redesenhar. Peça ao autor os PNGs.

Como a arte chega:
- **O autor cola a imagem no chat:** ela fica salva em disco (caminho no
  `[Image: source: ...]`) e dá para converter direto.
- **Link:** DeviantArt (`images-wixmp-*.wixmp.com`), Showdown e Bulbapedia são
  **bloqueados** pela rede da nuvem. Peça o arquivo no chat ou em
  `.filetransfer/` (commit + push na branch); arte de treinador vai para
  `.filetransfer/.trainers/<Nome>/` (formato abaixo).

## Regra do autor: várias opções de tamanho, com comparação, antes de registrar

Overworld novo **não vai direto** para o jogo (pedido do autor, 27/09/2026).
Gere uma proposta por largura do boneco (16, 17, 18… px, até onde a arte
permite sem ampliar e sem passar de 31 px de altura) e uma folha de
comparação ampliada com o jogador e o sprite atual ao lado; o autor escolhe;
só então grave o PNG do jogo:

```bash
PY=/mnt/c/Users/User/AppData/Local/Programs/Python/Python310/python.exe   # tem PIL
$PY dev_scripts/sprites/propostas_overworld.py propostas <Nome>   # -> Sprite - comparacao no jogo.png
$PY dev_scripts/sprites/trainer_na_batalha.py <Nome>              # -> Trainer - comparacao no jogo.png
$PY dev_scripts/sprites/propostas_overworld.py final <Nome> <largura> "$(wslpath -w graphics/object_events/pics/people/special/<nome>.png)" [--quadro 16] [--altura H]
# registra (ou ajusta 16x32 <-> 32x32, 9 <-> 12 quadros) nos 8 lugares do jogo:
$PY dev_scripts/sprites/registrar_overworld.py <NomeC> graphics/object_events/pics/people/special/<nome>.png --quadro 16|32 [--const X]
```

O registrador cria tudo ao lado da Brendan Hoenn; nome C que já existe em
outro lugar quebra o build (o Ash virou `AshKetchum`: `sPicTable_Ash` é o
efeito de cinzas).

### Pasta de cada personagem: `.filetransfer/.trainers/<Nome>/`

Toda arte de treinador fica neste formato (a Anabel foi o modelo):

| Arquivo | O que é |
|---|---|
| `Sprite - AUTOR.png` | folha de overworld de origem (recortada se vinha junto com o trainer) |
| `Trainer - AUTOR.png` | arte de batalha de origem |
| `Sprite - comparacao no jogo.png` | uma linha por largura do boneco, com o sprite de hoje e o jogador ao lado |
| `Trainer - comparacao no jogo.png` | tela de batalha com o trainer de hoje, o 64x64 e o 80x80 |
| `outras/` | folha completa, versões antigas, alternativas recusadas |

O crédito vai **sempre** no nome (`Sprite - AUTOR`, `Trainer - AUTOR`); autor
não sabido fica `desconhecido` até o autor do hack dizer. Personagem novo:
crie a pasta nesse formato, some uma entrada em `CHARS`
(`propostas_overworld.py`) e em `TRAINERS` (`trainer_na_batalha.py`) e rode os
dois. Folha com bonecos encostados ou com linhas de grade: `grade=True`
(recorta pela célula); grade irregular: `xs`/`ys`; folha FRLG de 7 quadros:
`FRLG7` (espelha o passo de baixo/cima).

Qualidade (medido em 28/09 contra os aprovados do jogo): o 80x80 usa a
fusão de cores do `--merge` (custo = pixels × distância) e sai idêntico ao
jogo; o 64x64 reduz **apagando linhas/colunas** (voto de área sujou rostos
de Kukui e Elesa).

**Overworld de 16-18 px** (auditoria de 29/09, aprovada pelo autor; folhas em
`.filetransfer/.trainers/_auditoria resize 16px/`): o `propostas_overworld.py`
reduz as **colunas por costura reta de menor energia** (gradiente + contorno +
máscara de olho/boca, com penalidade forte nas vizinhas da última coluna
removida; a mesma coluna em todos os quadros da mesma direção) e as
**linhas apagando em faixas** com custo que protege traço escuro de 1 px. É o
que mantém o rosto quando o cabelo disputa espaço (Lusamine 27→16 px). O que
já foi tentado e descartado, não volte: costura **diagonal** serra cabelo e
silhueta (Gladion, Steven, Diantha); seam carving nas **linhas** achata
capacete e topo de cabeça (Ramos, Steven); penalidade fraca deixa os cortes
se concentrarem no corpo e alarga o chapéu (Hilda); média de área, voto
ponderado e Lanczos borram; fundir a 15 cores **antes** de reduzir apaga os
olhos (Agatha), por isso o JPG só passa por median cut a 24 antes e a fusão
final fica para depois; só conteúdo em arte que encolhe pela **metade**
(chibi de 32 px: Zinnia, Diantha) mantém os olhos na largura nativa e come a
pele em volta, por isso a parte apagada em faixas uniformes cresce com a
redução (`parte_por_conteudo`: 100% conteúdo até r=0,8, 25% em r=0,5).
Folha JPG com **linha de borda** de cor escura (Cyrus): a cor do canto só
vale como fundo se cobrir ≥5% da imagem, senão é só porta de entrada do
preenchimento e é apagada apenas nas linhas/colunas de grade. Arte JPG
borrada na origem (Olivia zender1752) continua borrada: o caminho é arte nova.
Folha **ampliada por IA** (sem grade fixa, o pixel varia de 5 a 8 px; Olivia
de 30/09): `reamostrar=(celula, N)` reduz cada célula ao medoide do miolo de
cada bloco antes de tudo. Roupa clara de poucos pixels (top rosa) some no
median cut a 40 cores quando o cabelo domina: `pre_cores=96` na entrada. Nos
quadros de **frente e costas** as colunas saem aos pares espelhados no eixo
do boneco, senão um olho fica com 4 px e o outro com 2 (Zinnia). **Olho no
16x32 tem 1 px de largura por 2 de altura** (regra do autor, 30/09; é o que
Gladion, Kukui, Looker e Lillie têm): para boneco de até 16 px, `afinar_olhos`
detecta cada olho no quadro parado (pixel escuro cercado de claro) e tira as
colunas de fora dele, em par espelhado, antes do resto da redução; olho com
mais de 4 colunas não é olho (franja) e fica; o espelho nunca apaga a coluna
que ficou de outro olho (o eixo vem da silhueta, e o Blue e o Looker perdiam
um olho inteiro a 16). **O olho nunca perde o
pixel preto**: olho de 4 px pode (2 branco + 2 preto), olho de 4 px pretos ou
sem preto não (autor, 30/09). Os pixels de olho levam alfa 254 (`OLHO`) do
começo ao fim da redução, e linha ou coluna com eles custa 100000; sem isso a
linha da pupila saía inteira (Misty, Lorelei, Looker, Leon, Hilda, Guzma).
Quem o autor prefere com o método de 29/09, de antes dos tratamentos, leva
`metodo='simples'` em `CHARS` (Gladion, Cynthia). Arte que traz **sombra
desenhada sob os pés** (Steven, Klein): o jogo já desenha a sombra, então a
cor dela entra em `bgs` na entrada de `CHARS` e some. Fonte **JPG é quantizada a 15 cores antes** de reduzir (senão o
contorno dobra). A **altura é escolhida à parte da largura**: os 16 px
aprovados do jogo têm 18-22 px de altura, então quando a proporcional cai fora
disso a folha traz também a linha "altura do elenco" (Lusamine a 16 px:
proporcional 15, elenco 20), e `final ... --altura H` grava a escolhida. Se a arte já tem front pic no jogo, as cores vão para a
paleta dele, mas só quando é a mesma arte (distância média ≤ 10; a Lillie e
a Cynthia de hoje são outra arte). Em PNG a cor de fundo sai na imagem
toda, não só a partir da borda (o verde entre braço e cabelo da Elesa). Cor
muito usada só vira fundo se for área lisa (o roxo do cabelo do Byron não).
No JPG a cor do canto e a do fundo contam junto o ruído (tolerância 8): o
branco do Blue é 1,4% exato e 35% com ruído, e contado exato virava "linha de
borda" e deixava borrão branco no boneco. A cor de canto que é linha de grade
também sai em PNG (a linha branca no topo da folha do Byron).

Cada personagem é uma entrada em `CHARS` no script (arquivo, grade, células
na ordem do jogo, crédito). Se a folha tem o lado direito desenhado, sai com
12 quadros (`sAnimTable_StandardAsym`); senão 9. Arte que vem também em 2x dá
tamanhos acima do nativo sem ampliar. O tamanho de cada personagem está em
`.filetransfer/.trainers/TAMANHOS.md`. **Escolha do autor = forma pronta**
(30/09): o PNG do jogo desse personagem não é regravado nem retratado, nem
quando o script de redução melhora, a não ser que o autor peça explicitamente
(ajuste de método já regrediu sprites aprovados). A cena da Missão 4 em New
Bark (7 Pokémon na tela) está no limite da VRAM de sprite e a Anabel passou a
32x32 (17x22) em 30/09; antes de aumentar outro NPC dessas cenas, meça. A mesma ideia vale para o front pic:
arte de treinador maior que 64 px vai para o 80x80 (`TRAINER_SPRITE_LARGE`,
skill `adicionar-grafico-trainer`).

## Receita

```bash
S=dev_scripts/sprites/sprite_gba.py

# 1. front pic: detecta ampliação (4x, 2x...), tira o fundo, encolhe para 64x64
python3 $S front entrada.png graphics/trainers/front_pics/<nome>.png

# 2. overworld: diga o tamanho da célula (já nativo) e as 9 células na ordem do jogo
#    parado baixo, parado cima, parado esq, 2x andar baixo, 2x andar cima, 2x andar esq
python3 $S overworld folha.png graphics/object_events/pics/people/special/<nome>.png \
    --celula 32 32 --mapa "0,0 3,0 1,0 0,1 0,3 3,1 3,3 1,1 1,3" [--quadro 32 32]

# 3. conferir antes de registrar
python3 $S conferir <png>
```

Identifique a grade **olhando** a folha: qual linha é baixo/esquerda/direita/
cima, e quais colunas são os dois passos (na folha do Guzma, colunas 0 e 2
eram o mesmo quadro parado; 1 e 3, os passos). A linha "direita" é descartada:
o jogo espelha a esquerda.

## O que a ferramenta resolve (e já quebrou)

| Problema | Como é tratado |
|---|---|
| Imagem ampliada 2x/4x | detecta o fator pelo MDC das sequências de pixels iguais |
| Fundo colorido (verde-limão do Showdown) | cor do canto superior esquerdo vira transparente |
| 80x80 não cabe em 64x64 | apaga linhas/colunas **espalhadas pelo corpo**, a mais parecida com a vizinha em cada faixa. Cortar só onde há mais repetição **achatou as pernas e deixou a cabeça enorme** |
| Mais de 15 cores | funde o par mais próximo, pesado pela quantidade de pixels; imprime cada fusão |
| **Contorno preto sumiu** | a cor do índice 0 era (0,0,0), igual ao contorno. A ferramenta usa uma cor de índice 0 que não existe no desenho |
| Boneco mais largo que 16 px | avisa; escolha `--quadro 32 32` ou corte a arte |

Confira sempre o resultado **ampliado ao lado do original** antes de mostrar.

## Decidir o formato do overworld

| Situação | Formato |
|---|---|
| Personagem normal, boneco ≤ 16 px de largura | **16x32**, 9 quadros (padrão) |
| Boneco mais largo e cortar estraga | **32x32**, 9 quadros (precedente: Quinty Plump) |
| Só fica parado de frente (ex.: treinadores do Nexus) | **1 quadro** (16x32 ou 32x32); ver §3.4 do guia |

Custo medido por personagem: overworld 16x32 = 2,3 KB, 32x32 = 4,6 KB,
1 quadro = 0,25/0,5 KB; front pic ≈ 0,67 KB; mugshot ≈ 0,4 KB. A ROM está
em 92,83% (2,30 MB livres) — **o 94% que aparece no build é a EWRAM**, não a
ROM. Remeça com `python3 $S rom --log <log do make>`.

## Crédito

Registre o autor da arte no nome do arquivo, sempre como `Sprite - AUTOR` e
`Trainer - AUTOR` em `.filetransfer/.trainers/<Nome>/` (regra do autor,
28/09/2026). Se não souber, use `desconhecido` e pergunte antes de fechar.

## Checklist

- [ ] Arte de comunidade, não desenhada por código
- [ ] Convertida com `sprite_gba.py` e vista ampliada ao lado do original
- [ ] `conferir`: ≤16 índices, nenhum quadro vazio, boneco no lugar certo
- [ ] Folha de comparação vista **ampliada** (8x): olhos iguais dos dois lados,
      1 px de largura no 16x32, contorno sem serra, sem sombra desenhada sob os pés
- [ ] Formato do overworld escolhido (16x32 / 32x32 / 1 quadro) e justificado
- [ ] Autor da arte registrado
- [ ] Registrado no jogo pelas skills `adicionar-npc` / `adicionar-grafico-trainer`
      e **visto no jogo**
