# Auditoria: redução de overworld para 16-18 px (29/09/2026)

Personagens auditados: Leon (Wolfang62, 21x30), Lusamine (DiegoWT, 27x26),
Steven (Klein, 20x28), Ramos (desconhecido, JPG, 18x30). Cada um foi reduzido
para 16 px e 18 px de largura com sete estratégias; as folhas desta pasta
mostram o resultado ampliado, com o nativo e os sprites 16 px aprovados do jogo
(Gladion, Kukui, Looker, Lillie) como referência do que é "bom".

## O que a referência ensina

Os 16 px aprovados do jogo têm: contorno preto contínuo de 1 px, rosto feito de
2 pixels de olho + 1 de boca, cabeça grande (metade da altura) e 18-22 px de
altura. Um redutor que trate todo pixel como igual apaga exatamente isso.

## Problemas do processo atual (`propostas_overworld.py`)

1. **Apaga linhas/colunas em faixas uniformes.** Em cada faixa sai a linha
   mais parecida com a vizinha. Faixa que cai no rosto apaga um olho ou a
   boca; a costura de cabelo/rosto some. Leon 16 px fica sem rosto; Lusamine
   16 px vira um bloco de cabelo.
2. **Altura amarrada à largura** (`H = h0*W/w0`). Lusamine é mais larga que
   alta por causa do cabelo: a 16 px de largura sai com 15 px de altura, menor
   que qualquer NPC do elenco. A altura precisa ser escolhida separadamente
   (18-22 px, como os aprovados).
3. **Fonte JPG é reduzida suja.** O Ramos tem 2.590 cores; a quantização só
   acontece depois da redução (`pre_quant` para 40 cores, depois 15). Reduzir
   ruído gera contorno duplo e rosto salpicado.
4. **Nenhuma proteção de contorno.** A escolha da linha a apagar não sabe que
   um traço escuro de 1 px é o contorno.

## Estratégias testadas

| Sigla | Método | Resultado |
|---|---|---|
| A | atual: apaga linha/coluna uniforme | rosto destruído a 16 px (Leon, Lusamine) |
| E | apaga com prioridade (contorno de 1 px e pixel de olho pesam) | melhora pouco; a faixa uniforme continua mandando |
| B | seam carving (energia = gradiente + contorno) | rosto e cabelo preservados; **achata regiões lisas** (capacete do Ramos, topo da cabeça do Steven) quando corre nas linhas |
| B2 | B + máscara de rosto (pixel escuro cercado de claro) | melhor rosto de todos; mesmo defeito de B nas linhas |
| B3 | B2 + penalidade de vizinhança (espalha as costuras) | não resolve o achatamento |
| C | média de área + encaixe na paleta + contorno reforçado | borrado, cores viram lama (o "voto de área" que já sujou os 64x64) |
| C2 | voto ponderado (contorno 2x) + contorno reforçado | contorno grosso, rosto some |
| D | Lanczos + paleta | pior de todos: ruído e contorno furado |
| **H** | **híbrido: seam carving só nas colunas (rosto protegido) + apaga linhas com prioridade** | **melhor nos quatro**: rosto do Leon e da Lusamine inteiros, olhos e tufo do Steven, capacete do Ramos intacto |

Por que o híbrido funciona: a largura é onde o rosto sofre (cabelo largo
disputa espaço com o rosto), e o seam carving escolhe tirar cabelo liso em vez
de olho. A altura tem regiões lisas grandes (capacete, topo da cabeça) que o
seam carving achata, mas o apagamento uniforme com prioridade de contorno
reduz sem deformar.

## Recomendações, em ordem

1. **Trocar a redução de colunas por seam carving com rosto protegido** e
   manter o apagamento de linhas, agora com custo que protege traço de 1 px
   (protótipo em `prototipo/exp3.py`, função `H_hibrido`; energia e máscara em
   `prototipo/experimento.py`).
2. **Desacoplar a altura da largura**: propor cada largura com altura 18-22 px
   (a do elenco), e não a altura proporcional. Para arte mais larga que alta
   (Lusamine) isso é a diferença entre 15 e 21 px de altura.
3. **Limpar JPG antes de reduzir**: quantizar a folha nativa para 15 cores
   (`prototipo/exp2.py`, `limpar_jpg`) e só então reduzir. No Ramos, isso
   sozinho tira o contorno duplo.
4. Manter o mesmo conjunto de costuras para todos os quadros da mesma direção
   (o protótipo já soma a energia dos quadros do grupo), senão a animação
   "respira".
5. As métricas automáticas (gaps de contorno, pixels isolados) não separam
   bem os métodos quando o contorno da arte é cinza (Lusamine, Steven); a
   decisão continua visual, com o close-up 8x.

## Arquivos

- `<Nome> - atual x proposto.png`: 12 quadros, atual × híbrido, 16 e 18 px.
- `<Nome> - closeup 8x (A E B2 C2).png`: quatro estratégias, 4 quadros, 8x.
- `closeup 8x - atual x hibrido x seam nos dois eixos.png`: a decisão final.
- `closeup 8x - Ramos JPG limpo e costuras espalhadas.png`: o efeito de limpar o JPG.
- `referencia - sprites 16px aprovados do jogo.png`.
- `prototipo/`: scripts do experimento (rodam com o Python do Windows, PIL).

## Integrado (29/09/2026, aprovado pelo autor)

O híbrido é agora o método padrão de `dev_scripts/sprites/propostas_overworld.py`
(`seam_colunas`, `escolher_descartes` com prioridade, `limpar_jpg`, linha
"altura do elenco" nas propostas e `final ... --altura H`). A skill
`converter-sprite` e o guia `.claude/sprites-restricoes-e-custos.md` descrevem
o processo. Os scripts em `prototipo/` ficam só como registro do experimento.

## Revisão depois de regenerar todos os personagens (29/09, noite)

O autor apontou Cyrus (pernas), Diantha, Gladion e Hilda. Duas causas:

1. **Costura diagonal serra.** Em arte que encolhe pela metade (Diantha 32→16,
   Gladion 33→16) e em cabelo com linhas (Steven), a costura que anda ±1 por
   linha deixa as linhas verticais em zigue-zague. Testado: diagonal livre,
   diagonal penalizada (+60, +150) e **coluna reta**. A coluna reta venceu em
   todos, mas com a penalidade fraca de vizinhança (150) concentrava os cortes
   no corpo e alargava o chapéu da Hilda de lado. Com **penalidade 800, raio
   3** a proporção volta e o rosto da Lusamine continua inteiro. É o padrão
   agora (`DIAGONAL = None`, `seam_colunas(pen=800, raio=3)`).
2. **Linha de borda/grade escura no JPG (Cyrus).** A cor do canto da folha era
   uma linha azul-marinho, quase igual à sombra da calça; `sem_fundo` a tratava
   como fundo com tolerância 70 e comia a perna. Agora a cor do canto só é
   fundo se cobrir ≥5% da imagem; senão serve só de porta de entrada do
   preenchimento e é apagada apenas nas linhas/colunas em que domina (grade).

Folhas do teste: `prototipo/exp4_*.png` (variantes de costura) e
`prototipo/exp5_*.png` (penalidades).

## Segunda revisão (30/09): Zinnia, Agatha, Olivia

- **Zinnia (32→16/18 px):** só conteúdo mantém as colunas dos olhos (pixel
  escuro pesa) e apaga a pele em volta: olhos enormes. Testados peso da
  máscara (300/100/0/proporcional), custo das linhas (com/sem prioridade) e
  faixa inteira do rosto protegida: nada muda ou piora. O que resolve é a
  **mistura**: parte das colunas sai em faixas uniformes antes da costura,
  crescendo com a redução (`parte_por_conteudo` = (r-0,4)/0,4; r = largura
  alvo / nativa). Lusamine (r=0,59) segue com rosto; Zinnia e Diantha voltam
  à proporção do método antigo com o rosto limpo.
- **Agatha (JPG 2x):** a fusão gulosa a 15 cores antes de reduzir absorveu
  os olhos (cor rara) na pele. Agora o JPG só passa por median cut a 24
  antes; a fusão a 15 fica para depois de reduzir. Ramos continua limpo.
- **Olivia:** igual ao antes; a origem é um JPG borrado (nota do autor em
  TAMANHOS.md: vale arte nova). Nenhum redutor conserta.

Folhas: `prototipo/exp6_*` (JPG e peso da máscara), `exp7_*` (linhas),
`exp8_*` (mistura e faixa do rosto).

## Terceira revisão (30/09): Steven e Zinnia

- **Steven:** a arte do Klein traz uma sombra cinza (148,147,146) sob os pés;
  o jogo já desenha sombra. A cor entrou em `bgs` na entrada de `CHARS` e o
  nativo passou de 20x28 para 20x27.
- **Zinnia 16x20:** um olho com 4 px e outro com 2, porque as colunas
  removidas não eram espelhadas. Agora, nos grupos de frente e costas, tanto
  a parte uniforme quanto a costura removem colunas aos pares simétricos em
  relação ao eixo do boneco (`centro`, `espelhar=True`); se o número é ímpar,
  a coluna extra é a do eixo. Os grupos de lado seguem sem espelho.

## Quarta revisão (30/09): olho de 1 px no 16x32

Regra do autor: no elenco 16x32 o olho tem 1 px de largura por 2 de altura.
A Zinnia a 16x20 saía com olhos de 2 px de largura porque o protetor de rosto
(olho = pixel escuro cercado de claro, +300 de energia) nunca deixa uma coluna
do olho sair. Agora, para boneco de até 16 px (`OLHO_1PX_ATE`),
`afinar_olhos` detecta cada olho no quadro parado de frente, mantém a coluna
mais perto do eixo e tira as outras (em par espelhado) **antes** da redução;
grupo com mais de 4 colunas é franja/contorno e fica. `olhos()` agrupa só as
sementes (crescer para pixel escuro vizinho engole o contorno inteiro).
Conferido a 10x em Zinnia, Gladion, Lusamine, Leon, Hilda, Diantha e Steven:
olhos 1x2 onde havia olho de 2 colunas; os demais sem mudança.

Estado final do método (30/09): JPG → median cut 24; fundo/grade pela cor do
canto só se ≥5%; colunas = afinar olhos (≤16 px) → faixas uniformes
(parte cresce com a redução) → costura reta com penalidade 800, tudo
espelhado em frente/costas; linhas = faixas com prioridade de contorno;
altura do elenco 18-22 proposta à parte; fusão final a 15 cores.
