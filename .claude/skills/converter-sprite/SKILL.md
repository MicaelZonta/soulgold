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
  `.filetransfer/` (commit + push na branch).

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

Registre o autor da arte (como `Beliot419`, `Derlo`, `Wolfang62` nos nomes
dos arquivos em `.filetransfer/`). Se não souber, pergunte antes de fechar.

## Checklist

- [ ] Arte de comunidade, não desenhada por código
- [ ] Convertida com `sprite_gba.py` e vista ampliada ao lado do original
- [ ] `conferir`: ≤16 índices, nenhum quadro vazio, boneco no lugar certo
- [ ] Formato do overworld escolhido (16x32 / 32x32 / 1 quadro) e justificado
- [ ] Autor da arte registrado
- [ ] Registrado no jogo pelas skills `adicionar-npc` / `adicionar-grafico-trainer`
      e **visto no jogo**
