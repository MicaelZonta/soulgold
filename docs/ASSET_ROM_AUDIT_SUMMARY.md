# Auditoria de Assets e Espaço de ROM — SoulGold

> Auditoria **somente leitura**. Nenhum arquivo de código, gráfico ou configuração do
> repositório foi alterado. Anexo: [`ASSET_ROM_AUDIT.csv`](ASSET_ROM_AUDIT.csv) (88 linhas).

---

## 1. Identificação e baseline

| Campo | Valor |
|---|---|
| Repositório | `/home/ADMIN/decomps/soulgold` |
| Branch | `master` |
| Commit analisado (HEAD) | `692c07cd71643e970f4206fbc9099004579323b7` ("update docs", 2026-09-04) |
| Estado da árvore | **Suja** — mudanças locais não commitadas foram compiladas junto (ver §1.1). Nenhum arquivo foi criado/alterado por esta auditoria além dos dois entregáveis em `docs/`. |
| Data da análise | 2026-09-06 |
| Comando de build | `make release USE_LTO_ON_RELEASE=1 -j32` |
| Resultado do build | `Soulgold.elf` / `Soulgold.gba` / `Soulgold.map` gerados com sucesso. O alvo final `bps` falhou (`Missing base ROM: clean.gba`) — **não afeta esta auditoria**, pois ELF/GBA/MAP já existem e são a fonte de todas as medições. |
| Toolchain | `arm-none-eabi-gcc 14.2.1`, `arm-none-eabi-nm` para extração de símbolos |

### 1.1 Mudanças locais não commitadas incluídas neste build

A árvore de trabalho tinha modificações não commitadas no momento da compilação. As mais
relevantes para esta auditoria:

- `OW_GFX_COMPRESS`: `FALSE → TRUE` (ver §3, é uma otimização já ativa e correta)
- `OW_BATTLE_ONLY_FORMS`: `TRUE → FALSE` (verificado: não incluído nenhum sprite overworld órfão de Mega/Gigantamax — ver CSV)
- ~15 famílias em `species_enabled.h` religadas de `FALSE` para `P_GEN_1/2_POKEMON` (Spearow, Paras, Venonat, Psyduck, Doduo, Drowzee, Krabby, Goldeen, Jynx, Omanyte, Sentret, Ledyba, Sunkern, Pineco, Snubbull, entre outras)
- `data/wild_encounters.json`, `src/wild_encounter.c` e 2 mapas com mudanças de conteúdo

Se o Terra costuma compilar a partir de um commit limpo, refazer esta auditoria após o próximo
commit é recomendado — os números abaixo já refletem a árvore **atual**, que é o que o usuário
pediu ("build atual").

---

## 2. Baseline medido

| Métrica | Valor | % |
|---|---:|---:|
| **ROM usada** | 32.732.272 B (31,22 MiB) | **97,55%** de 32 MiB |
| **ROM livre** | 822.160 B (~803 KiB) | 2,45% |
| **EWRAM** | 255.579 B / 262.144 B | 97,50% |
| **IWRAM** | 24.080 B / 32.768 B | 73,49% |

Fonte: saída do linker (`--print-memory-usage`) e `arm-none-eabi-nm --print-size --size-sort -C
Soulgold.elf` (116.295 símbolos, dos quais 84 mil com tamanho >0 residem em ROM). A soma dos
símbolos categorizados (32.664.289 B) reconcilia com o total do linker a menos de 0,2%
(diferença = padding/alinhamento entre seções).

### Flags relevantes confirmadas

| Flag | Valor neste build | Nota |
|---|---|---|
| `OW_GFX_COMPRESS` | `TRUE` | Economiza **~5,88 MB (17,9% da ROM inteira)** — ver §3. Não reverter. |
| `OW_BATTLE_ONLY_FORMS` | `FALSE` | Confirmado 0 sprites overworld de Mega/Gigantamax vazando na ROM. |
| `P_MODIFIED_MEGA_CRIES` | `FALSE` | Já economiza ~3% da ROM (comentário do próprio código); confirmado 0 símbolos `Cry_*Mega*` no ELF. |
| `P_MEGA_EVOLUTIONS` / `P_GIGANTAMAX_FORMS` | `TRUE` | 112 Megas ativáveis; G-Max majoritariamente travado (ver §5). |
| `DEBUG_*` | `DISABLED_ON_RELEASE` | Funciona bem: só 2.400 B (0,007%) de código residual de debug sobrou no release. |
| `FREE_MYSTERY_EVENT_BUFFERS`/`FREE_MYSTERY_GIFT`/`FREE_BATTLE_TOWER_E_READER` | `TRUE` | RAM já liberada; sobra código/dados de ROM (ver §6). |
| 14 famílias Ultra Beast/Treasures of Ruin | `FALSE` | Confirmado 0 bytes vazando (exceto 1 sobra trivial de 408 B, ver CSV). |

---

## 3. Maiores consumidores da ROM (categorias medidas via símbolo real)

| # | Categoria | Bytes | % da ROM |
|---|---|---:|---:|
| 1 | **Cries (gritos, PCM cru)** | 7.920.256 | 24,2% |
| 2 | Código (funções, `.text`) | 2.792.069 | 8,5% |
| 3 | Follower/overworld — **Pokémon surfáveis** (sprite de surfe) | 2.273.280 | 6,9% |
| 4 | Amostras de instrumento musical (DirectSound) | 1.948.636 | 6,0% |
| 5 | Gráficos de tileset de mapa | 1.943.888 | 5,9% |
| 6 | Follower/overworld comprimido (sprite normal de seguidor) | 1.677.488 | 5,1% |
| 7 | Ícones de Pokémon | 1.429.504 | 4,4% |
| 8 | Front sprites de batalha | 1.551.588 | 4,7% |
| 9 | Layout/header de mapas | 1.305.900 | 4,0% |
| 10 | Back sprites de batalha | 883.780 | 2,7% |
| — | Diversos não categorizados (UI, minigames, cassino, trade, etc.) | 5.066.883 | 15,5% |

**Cries é isoladamente a maior categoria da ROM** — maior que front+back sprites somados. Isso é
esperado em qualquer ROM Pokémon (cada espécie precisa de um grito), mas é onde qualquer
otimização de compressão de áudio teria o maior efeito absoluto — fora do escopo desta auditoria
de assets visuais, mas vale registrar para o Terra.

O bloco de **2,27 MB em sprites de "Pokémon surfando"** é a maior linha decorativa isolada:
~136 espécies têm uma folha de sprite dedicada (corpo + 6 frames de overlay do jogador) definida
em `src/data/object_events/surfable/surfable_pokemon_graphics.h`, **independente** do arquivo
`surfable_species_enabled.h` (que é só uma lista de desejo para arte futura, hoje 100% zerada).
Não é bug nem código morto — é uma feature real e visível — mas é a maior decisão de **escopo**
disponível se a equipe precisar liberar espaço sem tocar em conteúdo de espécie/Pokédex.

---

## 4. Duplicatas confirmadas (byte-a-byte, via `md5sum` + `nm`)

Todas as linhas abaixo foram **verificadas diretamente**: os arquivos-fonte comparados têm hash
MD5 idêntico, e os símbolos correspondentes aparecem com o mesmo tamanho no ELF final. Isso é
economia **comprovada por conteúdo real**, não estimativa.

| Achado | Bytes recuperáveis | Risco visual |
|---|---:|---|
| Minior Core (7 cores) — ícone com pixels idênticos, só paleta muda | 6.144 | **Zero** — já é o padrão usado no front/back de Minior |
| Floette (5 cores comuns) — sprite de seguidor idêntico | 3.648 | **Zero** |
| Florges (4 de 5 cores) — sprite de seguidor idêntico (Yellow é distinto, cuidado) | 3.588 | **Zero** |
| Squawkabilly (4 cores) — sprite de seguidor idêntico | 2.760 | **Zero** |
| Deerling (4 estações) — sprite de seguidor idêntico, só paleta muda | 1.524 | **Zero** |
| Dialga / Dialga-Primal — ícone idêntico | 1.024 | **Zero** (confirmar se é intencional ou arte pendente) |
| Flabébé (Orange+Yellow apenas) — sprite de seguidor idêntico | 596 | **Zero** |
| Finizen / Palafin-Zero — back sprite idêntico | 412 | **Zero** — condiz com a piada de design oficial da espécie |
| **Subtotal — mesma espécie/família, risco zero** | **19.696** | |
| Latias-Mega / Latios-Mega — front+back+ícone idênticos entre **espécies diferentes** | 2.660 | Zero tecnicamente, mas confirmar com arte se é lacuna |
| Appletun-Gmax / Flapple-Gmax — front+back+ícone idênticos entre **espécies diferentes** | 2.264 | Zero tecnicamente, mas confirmar com arte (forma **alcançável** hoje) |
| **Subtotal — espécies diferentes, mesma arte hoje** | **4.924** | |
| **TOTAL COMPROVADO POR MD5** | **24.620 B (0,073% da ROM)** | |

Isso **não é uma varredura completa**: os três agentes que eu havia despachado para cobrir
sistematicamente todas as categorias de asset (front/back/ícone/paleta/footprint × todas as ~950
espécies habilitadas, mais uma checagem dedicada em cries) **falharam por limite de sessão da
API antes de terminar** — um deles chegou a reportar "44 grupos de duplicata brutos" encontrados
antes de cair, mas os detalhes não foram salvos. Eu completei manualmente os tipos de arquivo
mais baratos de varrer (ícone, back, front, overworld — todas as ~950 pastas de espécie, cada
uma), mas **não cobri paletas, footprints, nem uma varredura de cries além da amostra inicial**.
**Recomendo ao Terra rodar a mesma metodologia (`find … -exec md5sum {} + | sort | uniq -w32 -D`)
nessas categorias restantes antes de fechar o escopo** — o padrão encontrado (formas de cor que
compartilham forma e só variam paleta) sugere que ainda há duplicatas de paleta/footprint não
descobertas.

Famílias auditadas e **sem duplicata encontrada** (arte confirmada como genuinamente distinta,
não compartilhar): Furfrou (10 cortes, ícones e backs todos únicos), Scatterbug/Spewpa/Vivillon
(20 padrões, todos únicos), Sawsbuck (4 estações, overworld confirmado distinto ao contrário de
Deerling), Pumpkaboo/Gourgeist (8 combinações, todas únicas).

---

## 5. Conteúdo compilado mas inacessível ao jogador

Esta seção cruza os achados desta auditoria com `docs/POKEMON_AVAILABILITY_AUDIT.md`, gerado na
mesma commit por uma sessão anterior — os números de espécie/obtenibilidade vêm de lá; os
**bytes de ROM são medidos aqui, agora, pela primeira vez**.

| Achado | Bytes medidos | Evidência |
|---|---:|---|
| **24 lendários/míticos** habilitados (`P_FAMILY_*=TRUE`) sem nenhuma fonte no jogo (Deoxys, Reshiram, Zekrom, Kyurem, Keldeo, Xerneas, Yveltal, Zygarde, Volcanion, linha Cosmog, Necrozma, Zacian, Zamazenta, Eternatus, Regieleki, Regidrago, Glastrier, Spectrier, Calyrex, Terapagos, Pecharunt) | **716.399** | `nm` (por espécie, ver CSV) + `POKEMON_AVAILABILITY_SPECIES.csv` (Habilitada=Sim, Obtível=Não) |
| 14 de 17 formas Gigantamax travadas (`B_FLAG_DYNAMAX_BATTLE=0`, item não distribuído) | ~77.000 (calculado, ver nota) | Total G-Max medido = 94.219 B / 17 formas; proporção 14/17 aplicada |
| Blacephalon (família desligada) — sobra de asset de animação de golpe | 408 | `nm`, achado incidental |

**Isso não é um bug técnico** — é conteúdo que existe no binário porque a *espécie* está ligada
na config, mas ninguém conectou uma rota de obtenção (script, encontro, presente, evolução). A
mesma flag que os liga também os desliga: **desabilitar `P_FAMILY_*` recupera o espaço por
completo**; a alternativa é escrever a rota de obtenção. É uma decisão de design do Terra, não
uma limpeza automática segura.

**716 KB é o segundo maior bloco de oportunidade encontrado nesta auditoria**, atrás só da
hipótese (não validada) de cries por linha evolutiva.

---

## 6. Features de hardware legado / multiplayer

| Feature | Bytes medidos | Situação |
|---|---:|---|
| GameCube Multiboot — bônus disc Pokémon Colosseum (Eevee/Pichu via cabo link real) | 163.840 | Código **incondicional** em `src/intro.c` (tela de copyright), roda em todo boot. **Remover exige mudança de código**, não só de asset. |
| GameCube Multiboot — E-Reader | 12.512 | Mesmo mecanismo |
| GameCube Multiboot — correção de bug de Berry (hardware real RS) | 15.348 | Mesmo mecanismo |
| **Subtotal Multiboot/link legado** | **191.700** | Conectividade GBA↔GameCube real, quase certamente irrelevante para um romhack de emulador/flashcart |
| Mystery Gift / Mystery Event / Wonder Card (RAM já liberada, sobra ROM) | 24.800 | Precisa confirmar se há alguma rota de distribuição real no hack |
| Union Room | 20.505 | `OW_UNION_DISABLE_CHECK` só acelera a Pokémon Center, não desliga a feature |
| Contest (concursos de beleza) | 126.562 | **Alcançabilidade não confirmada** — não há flag de liga/desliga; precisa checar se existe Contest Hall conectado nos mapas |
| Battle Frontier | ~535.000 (fora do total acima, ver CSV) | **Provavelmente alcançável** — 47 pastas de mapa e 53 conexões de mapa referenciando `MAP_BATTLE_FRONTIER*` encontradas; não confirmado percorrendo scripts do início ao fim |

O item de maior retorno aqui é o **Multiboot GameCube (191,7 KB)**: é código real de conectividade
para hardware que praticamente nenhum jogador de romhack possui, roda sem gating de config, e o
código-fonte que o aciona já foi localizado (`src/intro.c:1082-1120`).

---

## 7. Segundo frame do front sprite (metodologia própria)

**100% dos 933 arquivos `anim_front.4bpp` verificados têm exatamente 4.096 bytes** — sempre 2
frames de 2.048 bytes (animação de "respiração" do sprite de batalha). Isso é uniforme em todo o
jogo, não varia por espécie.

Comprimi (com a ferramenta real do projeto, `tools/compresSmol`) só o 1º frame de uma amostra de
41 espécies (do menor ao maior sprite) e comparei ao `.smol` atual (2 frames): o 2º frame
correspondeu a **43,6%** do peso comprimido da amostra. Extrapolando para o total medido da
categoria (1.551.588 B): **~676.000 B (2% da ROM)**.

Isso é **calculado por amostragem real, não medido símbolo-a-símbolo**, e a economia **não é uma
troca de ponteiro** — exigiria mudar a engine de animação de sprite de batalha e reprocessar o
front pic de ~950 espécies. Risco alto de regressão visual em massa. Não é a primeira
recomendação da lista.

---

## 8. Hipótese não validada — cries por linha evolutiva

O Terra pediu para avaliar se cries de pré-evoluções poderiam reaproveitar o cry do estágio
final. Hoje **cada estágio tem grito próprio** (comportamento oficial de qualquer jogo Pokémon,
não uma duplicata). Contei blocos `.evolutions = EVOLUTION(` em `species_info/*.h`: 491 de 1.577
entradas (31,1%) têm pelo menos um alvo de evolução. Aplicando essa proporção aos 1.052 cries
realmente linkados hoje (média 7.529 B cada): **~2.462.000 B (7,3% da ROM)** se todas as
pré-evoluções fossem redirecionadas para o cry final da linha.

**Isto é uma estimativa por proporção, não uma contagem espécie-a-espécie** (não construí a
árvore de evolução completa por restrição de tempo — o agente que tentaria isso caiu por limite
de API). É a maior cifra desta auditoria, mas também a menos confiável e a mais arriscada:
mudaria a identidade sonora de centenas de Pokémon. Só vale prototipar se o Terra estiver disposto
a essa mudança de design; não é uma limpeza técnica.

---

## 9. Dez otimizações por custo-benefício

| # | Ação | Economia | Risco | Tipo de esforço |
|---|---|---:|---|---|
| 1 | Redirecionar ponteiro: Minior Core (7 ícones → 1) | 6.144 B | Zero | Só dado (tabela de ponteiro) |
| 2 | Redirecionar ponteiro: Floette (5 seguidores → 1) | 3.648 B | Zero | Só dado |
| 3 | Redirecionar ponteiro: Florges (4 de 5 seguidores → 1, **não mexer em Yellow**) | 3.588 B | Zero | Só dado |
| 4 | Redirecionar ponteiro: Squawkabilly (4 seguidores → 1) | 2.760 B | Zero | Só dado |
| 5 | Redirecionar ponteiro: Deerling (4 seguidores → 1) | 1.524 B | Zero | Só dado |
| 6 | Redirecionar ponteiro: Dialga/Dialga-Primal (ícone), Flabébé, Finizen/Palafin | 2.032 B | Zero | Só dado |
| 7 | Remover código+dados do GameCube Multiboot (Colosseum + E-Reader + Berry Fix) | 191.700 B | Baixo (feature de hardware quase inacessível) | **Código** em `src/intro.c` |
| 8 | Decisão de produto: desabilitar as 24 famílias lendárias/míticas inatingíveis (ou dar rota de obtenção) | até 716.399 B | Médio (decisão de conteúdo) | Config (`species_enabled.h`) — ou trabalho de conteúdo se a rota for implementada em vez de cortada |
| 9 | Confirmar alcançabilidade de Contest e, se morto, remover código+dados | até 126.562 B | Médio (precisa investigação antes) | Investigação → possível código |
| 10 | Decisão de escopo: reduzir a lista curada de ~136 espécies com sprite de surfe | até 2.273.280 B (parcial, por espécie removida) | Alto (visível ao jogador) | Decisão de design + dado |

**Completar a varredura de duplicatas** (paletas e footprints de todas as espécies, que não deu
tempo de cobrir) provavelmente soma mais alguns milhares de bytes na mesma faixa de risco zero
dos itens 1–6, pelo padrão já observado.

---

## 10. Economia — comprovada vs. calculada vs. hipótese

| Cenário | Bytes | % da ROM | ROM usada depois | ROM livre depois | Composição |
|---|---:|---:|---:|---:|---|
| **Baseline atual** | — | — | 97,55% | 2,45% | — |
| **Conservadora** (só duplicatas comprovadas por md5, risco zero) | 24.620 | 0,07% | 97,48% | 2,52% | §4 completo |
| **Provável** (conservadora + itens medidos que dependem de decisão de produto) | 1.181.994 | 3,52% | 94,03% | 5,97% | §4 + §5 + §6 |
| **Máxima** (provável + hipóteses de alto risco: 2º frame + colapso de cries) | 4.319.994 | 12,87% | 84,68% | 15,32% | tudo acima |

- **Comprovada por tamanho/símbolo + conteúdo idêntico**: 24.620 B (§4) — pode ser aplicada hoje sem qualquer risco visual, é puro redirecionamento de ponteiro.
- **Calculada** (medição real de símbolo, mas savings depende de decisão de produto ou de mudança de código não trivial): 1.157.374 B (§5 + §6) — números medidos com precisão, ação não é automática.
- **Hipótese ainda não validada** (extrapolação/amostragem, precisa de protótipo e/ou playtesting): 3.138.000 B (§7 segundo frame + §8 cries) — tratar como teto teórico, não como meta.

---

## 11. Arquivos que precisam DEIXAR de ser incluídos (não só redirecionar ponteiro)

Estes exigem remover a chamada/inclusão em código-fonte, não apenas repontar um array:

1. `src/intro.c` — chamadas incondicionais a `GameCubeMultiBoot_Init/Main/ExecuteProgram` e o `#include` de `include/multiboot_pokemon_colosseum.h` (arrasta os 3 payloads de 191,7 KB).
2. Qualquer template/tabela de Mystery Gift/Union Room/Contest que o Terra decidir cortar — hoje não há uma única flag central que os desligue; são vários pontos de chamada espalhados que precisam ser localizados e removidos junto com os dados.
3. Para as 24 famílias lendárias e as 14 formas G-Max travadas: **não é preciso mudar código** — desligar `P_FAMILY_*` (ou o form-change correspondente) já remove os dados via `--gc-sections`. Esse é o caminho mais barato dessa lista.

---

## 12. Limitações desta auditoria (para o Terra saber onde não confiar cegamente)

- A varredura de duplicatas por `md5sum` cobriu **front, back, ícone e overworld** de todas as
  ~950 pastas de espécie habilitadas, mas **não cobriu paletas nem footprints**, nem uma
  segunda passada em cries além da amostra de 41 usada para o cálculo do 2º frame.
- Os 5.066.883 B (15,5% da ROM) na categoria "diversos não categorizados" **não foram
  investigados item a item** — é uma cauda longa de ~72 mil símbolos pequenos (minigames de
  cassino/derby/roleta, papéis de parede de PC, telas de troca, sequências de música). Pode
  conter mais oportunidades, mas o volume por símbolo é pequeno o suficiente para não valer a
  pena sem uma triagem dedicada.
- **Contest e Union Room**: tamanho medido com confiança, alcançabilidade **não confirmada** —
  qualquer remoção deve ser precedida de uma checagem de scripts/mapas.
- Três sub-agentes que eu havia despachado para paralelizar essa investigação (duplicatas
  completas, formas especiais, cries+features) **caíram por limite de sessão da API** antes de
  terminar. Um deles reportou "44 grupos de duplicata brutos" sem detalhar — não incluí esse
  número no total comprovado porque não pude verificá-lo.
