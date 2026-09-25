# E) Abordagem adicional: linear agora, disco virtual seletivo depois

Esta não estava na lista. Ela surge de um fato do diagnóstico: **as
abordagens não são exclusivas, e A não fecha nenhuma porta.**

---

## A observação

A, C e D resolvem o mesmo problema em horizontes diferentes:

| | ganho | custo no jogo | teto |
|---|---:|---:|---|
| A (linear 96 MB) | +66 MB | ~5 linhas | 96 MB |
| C (disco virtual) | ilimitado | 3.000–8.000 linhas | nenhum |
| D (port nativo) | ilimitado | 20.000+ linhas | nenhum |

O instinto é escolher pelo teto. Mas o teto de A só é atingido se o projeto
**mais que triplicar** de conteúdo. E, crucialmente: adotar A hoje não
encarece C ou D amanhã. Os dados continuam exatamente onde estão, nas
mesmas tabelas, com os mesmos ponteiros. C e D partiriam do mesmo ponto de
partida que teriam hoje.

Isso torna A não apenas a opção mais barata, mas uma opção **sem custo de
arrependimento**.

## O plano em estágios

### Estágio 1 — agora: A completa

Os cinco itens de [02-abordagem-a-linear.md](02-abordagem-a-linear.md) mais
os cinco de [01-achados-transversais.md](01-achados-transversais.md).

Resultado: 29,66 MB de conteúdo num teto de 96 MB, com o `.gba` mantendo
exatamente o tamanho atual. Margem passa de 7,9% para 69%.

**Ordem sugerida**, porque um erro aqui é silencioso:

1. Recompilar `mgba-rom-test` a partir de `tools/mgba-master/` **sem
   patch nenhum**, confirmar que os 1.027 testes passam. Isso separa
   "quebrou por causa do rebuild" de "quebrou por causa do patch".
2. Aplicar o patch de máscara no mGBA. Rodar os testes de novo com a ROM
   ainda abaixo de 32 MB — o mapeamento linear tem de ser um no-op nesse
   regime.
3. Só então subir `LENGTH` para 96M e corrigir os quatro pontos de uma
   linha.
4. Validar em jogo: uma cena que use plaquinha de falante (achado 1), uma
   que troque de tileset, e uma batalha com áudio — os três subsistemas
   que mais dependem de ponteiro de ROM.

### Estágio 2 — se e quando passar de ~80 MB: C seletiva

**Não** a C completa. Só para tileset e mapa
(`src/tilesets.o` 2,5 MB + `data/maps.o` 1,3 MB), que são os únicos
subsistemas onde o modelo de disco virtual encaixa naturalmente: já
carregam em bloco na troca de mapa, já têm ponto de entrada único, e a
latência fica escondida pela transição de tela.

O registrador fictício vai na faixa livre 0x0400020A–0x040003FE
([io.h:154](../tools/mgba-master/include/mgba/internal/gba/io.h#L154)).

O que **não** entra nesse estágio, e o motivo:

- **Som** (10,1 MB): o mixer lê samples por DMA continuamente; não tolera
  dado não residente sem reescrever `src/m4a_1.s`. Fica na ROM linear.
- **Fontes** (422 KB): usadas a todo instante, latência inaceitável.
- **Sprites de Pokémon** (6,1 MB): 273 pontos de descompressão; é o
  estágio 3, se existir.

### Estágio 3 — se o objetivo mudar: D

Quando a meta deixar de ser "caber" e virar resolução maior, 60fps ou
distribuição em loja. Aí o limite de ROM é a menor das mudanças, e nada
feito nos estágios 1 e 2 atrapalha — a camada de plataforma substitui o
emulador inteiro de qualquer forma.

## Uma variante conservadora de A

Se houver receio de mexer nas três regiões de uma vez: estender só até
**0x0BFFFFFF (64 MB)**, mantendo 0x0C/0x0D como espelhos.

- Máscara vira `0x03FFFFFF` em vez de `0x07FFFFFF`.
- Ganho: +34 MB em vez de +66 MB. Ainda mais que dobra a margem.
- Vantagem: se existir algum código dependente de espelho que a varredura
  não achou, ele continua funcionando em 0x0C/0x0D.
- Custo: idêntico ao de A. Mesmas cinco linhas.

64 MB não é uma abordagem diferente — é a mesma constante com outro valor.
Trocar de 64 para 96 depois é mudar um `#define`. Pode ser o passo 2.5 do
estágio 1 para quem quiser validar em duas etapas.

## O que E acrescenta à decisão

Que a pergunta "qual abordagem escolher" está mal posta. A escolha real é
**quando** pagar cada custo. E como A é barata, reversível e não bloqueia
nada, ela é a única que não precisa dessa decisão ser tomada agora.
