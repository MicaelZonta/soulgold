---
name: nomear-falante
description: Use ao por o nome de quem fala numa plaquinha acima da caixa de dialogo (como a caixa de fala de treinador), ao escrever ou revisar dialogo de cena com varios personagens, ao adicionar um personagem novo a lista de falantes, e ao converter textos antigos do formato "Nome: fala" para a plaquinha. Cobre o codigo {SPEAKER NAME_X}, os tres arquivos que precisam concordar na mesma ordem, a diferenca entre trocar de falante e continuar falando, narracao que herda plaquinha por engano, quantos falantes cabem (indice de 2 bytes, ate 65025 - pode criar a vontade, inclusive Pokemon), por que fala de derrota dentro da batalha fica com "Nome: ", e as ferramentas que medem largura de linha e conferem tudo. Nao use para mugshot (retrato) nem para grafico de treinador.
---

# Nome do falante acima da caixa

A plaquinha é a mesma que aparece na fala de entrada de um treinador. Em
diálogo de cena ela substitui o prefixo `"Looker: "` dentro do texto: o nome
sai da fala e sobe para cima da caixa.

```
      ┌────────┐
      │ Lillie │
   ┌──┴────────┴────────────────────┐
   │ …Yes. I think so.              │
   │                                │
   └────────────────────────────────┘
```

Motor: `src/field_name_box.c`, `src/text.c` (`EXT_CTRL_CODE_SPEAKER`),
`src/field_message_box.c`. Aparência: `include/config/name_box.h`.

## 1. Como se escreve

Ponha `{SPEAKER NAME_X}` **antes da primeira letra** da fala, dentro do
próprio texto. É só isso: nenhum comando de script, nenhuma mudança no
`.inc` de scripts.

```asm
Mahoganytown_Text_UBSaved:
	.string "{SPEAKER NAME_LILLIE}Ninetales, Icy Wind!\n"
	.string "Keep it away from {PLAYER}!\p"
	.string "…Are you all right?\n"
	.string "Good. Good.\p"
	.string "{SPEAKER NAME_PRYCE}Hmph. That one's got a\n"
	.string "good cold in her.$"
```

**A regra do motor, inteira, em três linhas:**

| Situação | O que acontece |
|---|---|
| Mensagem começa com `{SPEAKER NAME_X}` | a plaquinha é do X, e já sobe junto com a caixa |
| Mensagem **não** começa com `{SPEAKER ...}` | sem plaquinha — e, importante, ela **não** herda o nome da caixa anterior |
| `{SPEAKER ...}` no meio | troca a plaquinha a partir dali |

Consequências que economizam trabalho:

- **Continuar falando não precisa de nada.** Páginas seguidas (`\p`) da mesma
  pessoa seguem com o nome. Só marque onde o falante **muda**.
- **Narração num texto próprio não precisa de nada.** Como a plaquinha não
  atravessa de uma mensagem para outra, `msgbox <narração>` já nasce sem nome.
- **Narração no meio de uma fala precisa de `{SPEAKER NAME_NONE}`.** Esse é o
  único caso que exige marcar o vazio: dentro de UMA mensagem, a página de
  narração herdaria a plaquinha de quem falou na página anterior.

`{PLAYER}` funciona no nome (`SP_NAME_PLAYER`). O código não ocupa pixel
nenhum: pôr a plaquinha só **encurta** a linha, nunca estoura.

## 2. Adicionar um personagem

Três arquivos têm que concordar **na mesma ordem**, porque o índice gravado em
cada fala é o do enum:

| Arquivo | O quê |
|---|---|
| `include/constants/speaker_names.h` | `SP_NAME_PRYCE` — define o índice |
| `src/data/speaker_names.h` | `COMPOUND_STRING("Pryce")` — o que aparece |
| `charmap.txt` | `NAME_PRYCE = 00 08` — permite escrever `{SPEAKER NAME_PRYCE}` |

Não edite à mão: use o ajudante, que acrescenta no fim do enum e da tabela e
**regera o bloco `NAME_*` inteiro do charmap a partir do enum**:

```bash
python3 .claude/skills/nomear-falante/adicionar_falante.py PRYCE "Pryce"
python3 .claude/skills/nomear-falante/adicionar_falante.py FARFETCHD "Farfetch'd" DIRECTOR "Director"
python3 .claude/skills/nomear-falante/adicionar_falante.py --sincronizar   # só regera o charmap
python3 .claude/skills/nomear-falante/checar_falantes.py
```

**Nunca reordene nem remova.** Trocar a ordem troca o nome de toda fala já
escrita — e o build continua limpo, porque nada disso é verificado pelo
compilador.

### Quantos falantes cabem: sem limite prático (65.025)

O índice vai em **2 bytes** depois do código `FC 19` (`SPEAKER_ARG_BYTES`,
em `include/constants/speaker_names.h`, mudança de 30/09/2026). Cada byte vai
de `00` a `FE` — `FF` é o fim de texto e `StringCopy` cortaria a fala ali —,
então índice = alto × 255 + baixo, até 255 × 255 = **65.025**. Um
`STATIC_ASSERT` em `src/data/speaker_names.h` guarda o teto.

- A tabela só tem o tamanho dos falantes que existem: não há o que reservar.
  Cada falante custa ~15–20 bytes de ROM. Crie à vontade, inclusive Pokémon
  (`"Miltank: Mooo!"` → `NAME_MILTANK`) e títulos genéricos (Director, Referee).
- Os textos citam o falante pelo **nome** (`{SPEAKER NAME_ELM}`); os bytes só
  nascem no build, a partir do charmap. Mudar a codificação não exige tocar
  em nenhuma fala.
- Quem lê o argumento: `GetSpeakerNameFromArg` (`src/field_name_box.c`), o
  renderizador (`src/text.c`, `EXT_CTRL_CODE_SPEAKER`, e os três `case` que
  só pulam o argumento) e `GetExtCtrlCodeLength` (`src/string_util.c`). Se
  algum dia mudar o tamanho de novo, são esses — esquecer um faz sair um
  caractere de lixo logo depois da plaquinha.

O nome cabe em `OW_NAME_BOX_DEFAULT_WIDTH` tiles (8 = 64 px em `FONT_SMALL`)
e é cortado além disso. Por isso "Kukui" e não "Prof. Kukui", "Elm" e não
"Prof. Elm". O mais largo em uso é "Warden Baoba" (58 px).

## 3. Converter textos antigos

Para textos já escritos no formato `"Nome: fala"`:

```bash
python3 .claude/skills/nomear-falante/aplicar_falante.py --resumo   data/maps/<Mapa>/scripts.pory
python3 .claude/skills/nomear-falante/aplicar_falante.py --conferir data/maps/<Mapa>/scripts.pory
python3 .claude/skills/nomear-falante/aplicar_falante.py --aplicar  data/maps/<Mapa>/scripts.pory
```

Ele troca o prefixo pelo código **sem reencaixar o parágrafo**: as quebras de
linha do autor são batidas de cena, não acaso, e o código não ocupa pixel, então
a linha só encurta. Edite sempre o `.pory` quando existir; o `.inc` é gerado.

O que ele já sabe (30/09/2026, quando o jogo inteiro foi convertido):

- **Falantes conhecidos vêm da tabela** (`src/data/speaker_names.h`), sem
  diferença de maiúscula (`"BILL: "` → `NAME_BILL`), mais `APELIDOS`
  (`"Prof. Elm: "` → `NAME_ELM`, `"???: "` → `NAME_UNKNOWN`). Prefixo que não
  está em nenhum sai como `DESCONHECIDO`: crie o falante (§2) ou, se não é
  alguém falando, ponha em `NAO_FALANTES` (placa `"Leader: Falkner"`,
  `"Type: Null"`, terminal `"POWER RELAY: …"`).
- **Texto de batalha fica com `"Nome: "`.** Fala de derrota de treinador
  (`trainerbattle_*`, argumento `lose_text`) aparece **dentro da batalha**, e
  lá não existe plaquinha: o código é só consumido e o nome sumiria da tela.
  O conversor acha esses rótulos sozinho (`TEXTOS_DE_BATALHA`) e os lista como
  `BATALHA`; `checar_falantes.py` não reclama deles. Um texto usado nos dois
  lugares (`message` e `trainerbattle_no_intro`, como `CianwoodGym_Text_ChuckIntro2`)
  também fica.
- **Texto inline do Poryscript** (`msgbox("Blaine: …")`,
  `pokenavcall("???: …")`) é convertido também, inclusive troca de falante
  depois de linha em branco (que é `\p`).
- A fala de **entrada** do treinador é overworld: pode converter.

**Depois de converter, faça as duas conferências que o conversor não faz:**

1. **Falante que ficou de fora da tabela.** Um `"Elm: "` no meio de um bloco do
   Looker passa batido e fica com a plaquinha errada — o pior defeito possível,
   porque o build é limpo e o texto parece certo no arquivo. `checar_falantes.py`
   pega os nomes conhecidos; para os desconhecidos:

   ```bash
   grep -nE '\.string "[A-Z][A-Za-zÉé. ]{1,14}: ' data/maps/<Mapa>/scripts.*
   ```

   Cuidado com falso positivo: `"Type: Null"` e `"Remember Type: Null"` não são
   falantes.

2. **Narração dentro de um bloco de fala** (§1). O conversor lista os blocos com
   página sem nome depois de uma fala; quase todos são continuação e não pedem
   nada. Olhe só os que são narração de verdade.

## 4. Medir a linha

A caixa tem 27 tiles (216 px, `FONT_NORMAL`). O limite prático é 208 px:

```bash
python3 .claude/skills/nomear-falante/medir_linha.py data/maps/<Mapa>/scripts.inc
python3 .claude/skills/nomear-falante/medir_linha.py --largura "Anabel: Two Ultra Beasts that"
```

Mede em pixels de verdade (larguras de glifo de `src/fonts.c`), não em número
de letras, e ignora os códigos de controle. `{PLAYER}` é medido pelo pior caso
plausível.

Rode **nos arquivos que você tocou**, não no repositório inteiro: há texto
vanilla e de janela não-diálogo que passa de 208 px de origem, e o ruído
esconde o que importa.

## 5. Armadilhas

- **Traço longo quebra o build.** U+2014 não está em `charmap.txt`; use `--`.
- **Ordem dos falantes é sagrada** (§2). Nenhuma checagem do compilador cobre.
- **`{SPEAKER ...}` em texto de batalha não mostra nada** (§3): fala de
  derrota mantém `"Nome: "`.
- **`{SPEAKER ...}` tem que vir antes da primeira letra** para a plaquinha subir
  junto com a caixa. Depois de uma letra, ela aparece com um pulo.
- **Quem define o falante de fora do texto** (`setspeaker`, fala de entrada de
  treinador) usa `SetSpeakerNameForNextMessage`, que arma o nome para **uma**
  mensagem. Atribuir `gSpeakerName` direto faz o nome ser apagado antes de
  aparecer.
- **`OW_FLAG_SUPPRESS_NAME_BOX`** (em `include/config/name_box.h`) esconde toda
  plaquinha enquanto estiver setada. Hoje vale `0` (desligado).
- **Texto de mais de 1000 bytes trava o jogo.** `msgbox` expande o texto
  **inteiro** em `gStringVar4` antes de desenhar a caixa
  (`ExpandStringAndStartDrawFieldMessage`, `src/field_message_box.c`), e
  `gStringVar4` tem 1000 bytes (`u8 gStringVar4[0x3E8]`, `src/string_util.c`).
  `StringExpandPlaceholders` não checa tamanho: o que passar disso é escrito
  por cima da EWRAM seguinte e o jogo congela na hora da fala. O build fica
  limpo. Uma cena longa com muitos `{SPEAKER ...}` chega lá sem parecer
  grande — o briefing da Missão 4 em Olivine tinha ~2000 bytes.
  **Conserto:** quebrar em vários `msgbox` **seguidos**, sem `closemessage`
  entre eles (`sFieldMessageBoxVisible` continua `TRUE`, a caixa não desce nem
  sobe de novo, e a cena roda como uma fala só). Cada parte tem que começar
  com o seu `{SPEAKER ...}`: `TrySetSpeakerFromMessage` lê só o começo de cada
  mensagem, e uma parte sem o código perde a plaquinha no meio da conversa.
  Corte sempre no fim de uma página (`\p` vira `$`). `checar_falantes.py`
  mede todos os textos: erro acima de 1000, aviso acima de 900.

## Checklist

- [ ] `{SPEAKER NAME_X}` só onde o falante **muda**; continuação sem nada
- [ ] Narração no meio de uma fala levou `{SPEAKER NAME_NONE}`
- [ ] Nenhum prefixo `"Nome: "` sobrando (`checar_falantes.py` + o `grep` do §3)
- [ ] Falante novo entrou pelo `adicionar_falante.py` (no fim, charmap regerado)
- [ ] Fala de derrota (dentro da batalha) continuou com `"Nome: "`
- [ ] `checar_falantes.py` limpo (inclusive sem texto acima de 1000 bytes)
- [ ] `medir_linha.py` sem estouro
- [ ] `make -j$(nproc)` limpo
