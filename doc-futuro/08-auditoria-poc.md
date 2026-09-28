# Auditoria da POC da abordagem A (ROM linear de 96 MiB)

Feita em 27/09/2026 sobre o commit `29f9ed17` da branch `poc-rom-96mb-linear`,
por leitura do diff completo (jogo e `tools/mgba-master`) e por reprodução
dos testes do [doc 07](07-poc-abordagem-a-resultado.md) numa máquina limpa:
toolchain ARM instalado do zero, ROM compilada da branch, mGBA patchado e
`romrun` compilados pelo `tools/rom_linear_poc/build.sh`, e um mGBA **sem**
patch (árvore do commit anterior) compilado como controle.

## Veredito

**A implementação funciona e as alegações centrais do doc 07 se reproduzem.**

| Teste reproduzido | Resultado |
|---|---|
| ROM padrão da branch (toggles ligados) | 33,14 MiB (34.754.444 B), igual ao doc |
| `make ROM_FILLER_MB=59` | 92,14 MiB, `__rom_end` em 0x0DC24F8C, igual ao doc |
| `boot_intro.txt`, 33 × 92 MiB no mGBA patchado | 7/7 screenshots idênticos, RMS de áudio idêntico por janela, 0 acessos inválidos |
| `surf_squirtle.txt`, 33 × 92 MiB | 26/26 screenshots idênticos, 11.682 frames, 0 acessos inválidos |
| Savestate: salva, anda, carrega, anda (roteiro próprio) | telas idênticas nos dois tamanhos |
| ROM de 33 MiB no mGBA sem patch | tela morta (só branco e preto) e ruído no áudio |
| Ponteiros de script no binário | marcados com bit 28 (`0x1823D671`); specials sem marca em 0x08 |
| `make syms` | 13.857 símbolos acima de 0x0A000000 que o filtro antigo descartava |
| RSS do runner | ~133 MB, igual ao doc |

Não reproduzido: save na Flash (o roteiro com `V` não foi commitado),
`make release` com LTO, e `make check` (já não compila antes da branch).

O que sustenta o veredito no código:

- **Marca no bit 28** (`SCRIPT_EFFECT_TAG`) é o achado certo: falha rápido em
  vez de executar dado, funciona igual em ROM ≤ 32 MiB, e os seis pontos de
  chamada (`script.c` ×3, `scrcmd.c` ×3) estão cobertos.
- **Região única de 96 M** no linker, sem buraco: o `.gba` é só conteúdo.
- **`romAddrMask` por cartucho** no mGBA: todas as máscaras de load, store e
  patch foram trocadas; não sobrou `GBA_SIZE_ROM0 - N` em caminho de acesso.
- **`malloc` com 15 bits**: a aritmética reconstrói 0x0DFFFFFF corretamente.
- **Filler por stamp** só relinka quando o valor muda.

## O que faltava, e o que foi corrigido

| # | Achado | Gravidade | Correção |
|---|---|---|---|
| 1 | Os três toggles foram ligados no mesmo commit da infraestrutura; a ROM padrão da branch só roda no mGBA patchado | decisão | **não alterado** — é escolha do autor (item 6 do doc 07) |
| 2 | `ld_script_test.ld` continuava com `LENGTH = 32M`; o ROM de teste linka os mesmos objetos e estouraria a região | alta | 96M, seção `rom_filler`, e `.rodata` movido para depois do slot DACS (abaixo) |
| 3 | `GBAApplyPatch` do mGBA recusava em silêncio saída > 32 MiB, e o `TargetCopy` do BPS checava limites contra a base em vez da saída (bug do upstream): soft-patch de BPS não funcionava | alta | aceita até 96 MiB com buffer linear; limites do `TargetCopy` corrigidos; aviso quando o patch falha; testado (abaixo) |
| 4 | `make syms` sem `ROM_FILLER_MB` relinkava o ELF com filler 0 e deixava o `.gba` de 92 MiB ao lado | média | `$(SYM)` depende também de `$(ROM)`; os três artefatos ficam consistentes |
| 5 | Memory viewer/debugger: `cart1`/`cart2` devolviam o início da ROM em vez de 0x0A/0x0C | média (dev) | em ROM linear, `cart0` cobre a janela toda e `cart1`/`cart2` ficam vazios |
| 6 | `serialize.c` mudou a checagem do PC também para ROMs ≤ 32 MiB | baixa | expressão do upstream mantida para ROM espelhada; a linear checa as seis regiões |
| 7 | Arquivo > 96 MiB caía em silêncio no truncamento de 32 MiB; leitura curta rejeitava a ROM sem log | baixa | `mLOG` nos dois casos; leitura em laço; `romAddrMask` volta ao normal em falha |
| 8 | `SCRIPT_EFFECT_TAG` vive em dois arquivos sem checagem de sincronia | baixa | `make check-script-effect-tag`, pré-requisito do link |
| 9 | Docs: README dizia "nenhum commit"; doc 02 dizia que o savestate grava `romSize` e que bastava manter `sound_data` abaixo de 32 MB | doc | corrigidos |

### 2 — o slot DACS é fixo

O BIOS (e o HLE do mGBA, `hle-bios.s`) salta para **0x09FFC000** em instrução
indefinida. O test runner põe `DACSEntry` nesse endereço para capturar
crashes. Com a ROM de teste acima de 32 MiB não dá para manter todo o
conteúdo antes do slot, então o layout novo é:

```
.text, script_data, lib_text     (código, < 0x09FFC000; ASSERT garante)
dacs 0x09FFC000
rom_filler, .rodata, song_data, lib_rodata, .data.*, tests   (0x09FFC00C+)
```

Verificado linkando um ELF de teste com os objetos da ROM e
`test_runner.o`/`test_test_runner.o` (com `--unresolved-symbols=ignore-all`,
porque a suíte inteira não compila): `DACSEntry` em 0x09FFC000, `__rom_end`
em 0x0BDD6A34, **61,84 MiB** por shard. É o custo real desta correção: o
ROM de teste passa a ter ~28 MiB de padding entre o código e o slot.

### 3 — soft-patch de BPS

Criado um `.bps` da ROM de 33 MiB para a de 92 MiB com o Flips (500 KB).
Com `ROMRUN_PATCH=1`, o `romrun` chama `mCoreAutoloadPatch` antes do reset
e imprime `memory.romSize` do core, que é a única prova de que o patch foi
aplicado (o "ok" do autoload só diz que o arquivo foi parseado, e as ROMs
de 33 e 92 MiB renderizam igual).

Dois defeitos independentes impediam o soft-patch:

1. `GBAApplyPatch` recusava saída acima de 32 MiB (limite do buffer antigo).
2. Em `src/util/patch-ups.c`, o comando `TargetCopy` do BPS checava
   `readTargetLocation` contra `inSize` (a base) em vez de `outSize` (a
   saída). Qualquer patch cuja saída seja maior que a base e que copie do
   próprio alvo além do tamanho da base era recusado, sem log. **É bug do
   upstream e vale também para o mGBA de estoque**: um BPS de Emerald limpo
   (16 MiB) para SoulGold (33 MiB) pode cair nele, porque o Flips usa
   `TargetCopy` para trechos repetidos.

Depois das duas correções: `memory.romSize` = 96.620.428 bytes após o
patch, 7/7 screenshots idênticos à ROM de 92 MiB carregada direto, 0
acessos inválidos. `GBAApplyPatch` agora emite `mLOG` quando o patch é
recusado ou falha, em vez de rodar a base em silêncio.

### Memória residente

As leituras de dado são barradas por `romSize` e o fetch de código usa
`romMask` (potência de 2 acima do tamanho), então só a faixa entre
`romSize` e `toPow2(romSize)` precisa do preenchimento com `0xFF`. O
`memset` foi limitado a essa faixa e o resto do mapeamento de 128 MiB fica
sem tocar (páginas não comprometidas com `mmap`).

| ROM | RSS antes | RSS depois |
|---|---:|---:|
| 33 MiB | 133 MB | 68 MB |
| 92 MiB | 133 MB | 132 MB |
| 33 MiB + BPS para 92 MiB | — | 194 MB (base + saída durante a aplicação) |

Isso importa para o port de Switch em modo applet, que tem uma fração da
RAM. O port de Switch compila o caminho linear (não define
`FIXED_ROM_BUFFER`; só 3DS e Wii definem) e usa o `mmap` do libnx via
`src/platform/posix/memory.c`. Não foi testado em hardware.

### Regressão depois das correções

Os mesmos roteiros rodados no mGBA corrigido: 33 screenshots (boot + surf,
33 e 92 MiB) idênticos aos da rodada anterior, savestate ok nos dois
tamanhos, 0 acessos inválidos.

## O que continua em aberto

1. Distribuição do mGBA patchado para três plataformas, e recompilar o
   `mgba-rom-test` de `tools/mgba/` (o `build.yml` roda `make check` com o
   hydra e o binário de estoque).
2. Os testes (`make check`) precisam voltar a compilar antes de o item 2
   acima poder ser exercitado de ponta a ponta.
3. Decidir os toggles (item 1 da tabela).
4. Roteiro de save na Flash no `tools/rom_linear_poc/` (o doc 07 cita o
   teste, mas o `.txt` não está no repositório).
