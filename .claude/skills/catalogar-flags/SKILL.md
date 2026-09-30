---
name: catalogar-flags
description: Use SEMPRE que terminar qualquer trabalho que mexeu em flag - criar flag nova, renomear, mudar valor, mudar o significado de uma antiga, aposentar, ou so acrescentar setflag/clearflag/goto_if_set num script. Regenera docs/SOULGOLD_FLAGS_AUDIT.csv com dev_scripts/flag_audit.py, le o diff para confirmar que a flag caiu no bloco certo e com o status esperado, e pega de graca os erros silenciosos: flag fora do array de save, flag setada que ninguem le, flag lida que ninguem seta. Vale tambem quando o usuario pedir para auditar, catalogar, revisar ou contar flags.
---

# Catalogar flags no CSV de auditoria

`docs/SOULGOLD_FLAGS_AUDIT.csv` é o catálogo de todas as flags do jogo: uma
linha por `#define`, com bloco, status de uso, leituras, escritas e escopo.
Ele é **gerado**, nunca editado à mão.

Catalogar é barato (um comando) e é a única coisa que mantém
`.claude/SOULGOLD_FLAGS_AUDIT.md` verdadeiro. Mais importante: o diff do CSV é
uma **revisão automática do seu trabalho** — ele mostra, sem você pedir, se a
flag nova ficou órfã, se você escreveu numa flag que ninguém lê, ou se errou o
número.

## 1. Rode o script

```bash
python3 dev_scripts/flag_audit.py --csv
```

Saída normal (os números mudam conforme o jogo cresce):

```
flags nomeadas: 1735   FLAGS_COUNT: 5448 (0x1548)
[('EM_USO', 1296), ('NUNCA_REFERENCIADA', 249), ('SO_MAPAS_FORA_DA_ROM', 140), ...]
buracos sem nome (fora do bloco trainer): 2693 slots em 5 faixas
```

**Se aparecer `ERRO: flag fora do array flags[]`, pare e conserte antes de
seguir.** Significa que alguma flag tem valor ≥ `FLAGS_COUNT`: `GetFlagPointer`
(`src/event_data.c:329`) não checa limite, então `setflag` nela grava em cima
de `vars[]`/`gameStats[]`. Quase sempre é dígito a mais no hexadecimal
(`0x2A92` no lugar de `0x2A9`).

## 2. Confira a linha da sua flag — é aqui que o erro aparece

```bash
grep "FLAG_QUE_EU_MEXI\b" docs/SOULGOLD_FLAGS_AUDIT.csv
git diff docs/SOULGOLD_FLAGS_AUDIT.csv     # visão geral do que mudou
```

Colunas: `valor,dec,nome,bloco,status,leituras,escritas,arquivos,mapas,escopo,comentario`.
(O `git diff` só serve depois que o CSV estiver commitado ao menos uma vez; o
`grep` funciona sempre.)

Exemplo de flag recém-alocada e ainda não usada:

```
0x1047,4167,FLAG_MINHA_COISA_NOVA,CUSTOM,NUNCA_REFERENCIADA,0,0,0,,,o que significa
```

Compare o que você fez com o que o CSV diz:

| Você fez | Linha esperada | Se vier diferente |
|---|---|---|
| Criou a flag e já usa ela no script | `EM_USO`, leituras ≥ 1 e escritas ≥ 1 | ver abaixo |
| Criou a flag, vai usar depois | `NUNCA_REFERENCIADA` | normal; vira dívida se ficar |
| Só acrescentou `setflag` | escritas sobe | — |
| Marcou progresso com a flag | — | `SO_ESCRITA` = ninguém lê essa marca. Ou falta o `goto_if_set`, ou a marca não serve pra nada |
| Condicionou uma cena à flag | — | `SO_LEITURA` = nada seta. A cena nunca vai disparar |
| Flag de visibilidade de NPC | escopo `MAPA_UNICO:<Mapa>` | se `mapas` está vazio, o `map.json` não referencia a flag: veja `visibilidade-e-gatilhos` |

`SO_ESCRITA` e `SO_LEITURA` não quebram o build e não aparecem no jogo como
erro — a cena simplesmente nunca acontece. É o tipo de defeito que só o
catálogo pega.

Confira também o **bloco**: flag nova de conteúdo deve sair como `CUSTOM`. Se
saiu como `SCRIPT/EVENT`, `SYSTEM` ou `RECLAIMED_TRAINER`, você escolheu um
número no meio de um bloco alheio — releia `alocar-flag`.

## 3. Mudou o significado de uma flag antiga?

O CSV mostra o estado de agora, não a história. O histórico fica em dois
lugares, e os dois são responsabilidade sua:

1. **O comentário no `flags.h`** — o script copia esse comentário para a
   coluna `comentario`. É o único campo do catálogo que carrega intenção.
   Atualize-o na mesma edição:

   ```c
   #define FLAG_ALGUMA_COISA  0x1047 // Antes era "falou com o Kurt"; desde 25/09/2026 e "recebeu a bola"
   ```

2. **O commit** — o diff do CSV junto com a mudança de código é o registro.
   Commite os dois juntos; um CSV commitado sozinho depois não explica nada.

Se a flag foi aposentada, prefira **renomear** (`FLAG_UNUSED_<hex>`) a apagar:
apagar libera o número para alguém reusar sem perceber que saves antigos ainda
têm aquele bit ligado.

## 4. Quando também mexer no documento

`.claude/SOULGOLD_FLAGS_AUDIT.md` tem números e listas colados de uma rodada
específica. Atualize o texto quando:

- corrigir um dos problemas listados na seção 7 (tire-o de lá, ou marque
  como resolvido com a data)
- o bloco `CUSTOM` passar de uma faixa para outra, ou uma reserva grande
  encolher de verdade
- aparecer um problema novo que a próxima pessoa precisa saber

Mexer no `.md` a cada flag nova é desperdício — os números do resumo são
ordem de grandeza, não contabilidade.

## Checklist

- [ ] `python3 dev_scripts/flag_audit.py --csv` rodou sem `ERRO:`
- [ ] Li `git diff docs/SOULGOLD_FLAGS_AUDIT.csv` e a linha da minha flag está
      como eu esperava (bloco, status, leituras/escritas, escopo)
- [ ] Nenhuma flag minha saiu `SO_ESCRITA` ou `SO_LEITURA` sem eu querer
- [ ] Comentário no `flags.h` explica o que a flag significa hoje
- [ ] CSV vai no mesmo commit da mudança
