# K8 — plaquinhas `{SPEAKER}` e decap do texto HnS (24/10/2026)

Passe de **texto** sobre os 205 `scripts.*` que a adoção do Kanto/Alola/Sinjoh
trouxe (tudo que mudou desde a tag `pre-kanto-hns`, menos `.inc` com `.pory`
vivo). Build limpo (`make -j`), `checar_falantes.py` limpo, nenhuma linha nova
estourando a caixa. **Não testado no jogo** (K8 é texto; o QA consolidado é o
passe seguinte).

## 1. Decap — `dev_scripts/decap_texto.py` (ferramenta nova)

O texto do HnS é estilo Gen 3/GSC: frase em caixa mista, mas **nome próprio,
espécie, item, golpe e lugar em CAIXA ALTA** ("There's a rare POKéMON on this
route.", "LEADER: BROCK"). O SoulGold é decapado ("Pokémon", "Leader: Brock",
"Zephyrbadge"). Eram **2 659 ocorrências em 165 arquivos**; sobraram **109**,
todas de propósito (ver §1.3).

A ferramenta decide **por bloco de texto** (rótulo + `.string` até o `$`):

| Bloco | Regra |
|---|---|
| **misto** (tem minúscula) | só troca o que casa no dicionário; caixa alta que sobra é **ênfase do autor** ("I STILL only sell to locals!") e fica — o relatório lista todas |
| **todo em caixa alta** (placa, diretório de loja, estátua de ginásio, lista de golpe do tutor) | vira Title Case; palavra pequena (of, to, and…) em minúscula; `MANTER` intacta |
| rótulo em `FRASES_NAO_PLACA` | sentença normal ("Mirror, mirror on the wall…") |
| rótulo em `PULAR` | intocado |

O dicionário de formas canônicas é **lido do repositório** a cada rodada
(espécies, golpes, itens, habilidades, MAPSECs, `speaker_names.h`) + `FRASES_MANUAIS`
(lugar/instituição que nenhuma tabela tem: "Pokémon Center", "Gym Leader",
"Dept.Store", "Silph Co.") + `PALAVRAS` (palavra isolada). Frase casa **atravessando
`\n`/`\l`/`\p`**, então "POKéMON\nCENTER" sai certo.

Convenções confirmadas no texto que já era nosso:
- badge é palavra só com a inicial maiúscula (`ZEPHYRBADGE` → **Zephyrbadge**),
  como na Violet Gym;
- abreviação **não ganha espaço** que não tinha: `MT.MOON` → `Mt.Moon`,
  `DEPT.STORE` → `Dept.Store`, `S.S.TICKET` → `S.S.Ticket` (mexer no espaço
  mexeria na largura da linha);
- placa é Title Case com palavra pequena em minúscula ("The Link Between Kanto
  and Johto", "Violet City / The City of Nostalgic Scents");
- `REGION` vira **region** minúsculo ("of the Johto region"), como o nosso
  "Hoenn region".

### 1.1 Armadilhas do tokenizador (todas já resolvidas no script)

- `\n` dentro do conteúdo fazia o token virar `nISLES` — hoje `\n`/`\l`/`\p`
  são mascarados antes de tokenizar.
- `--` colava duas palavras (`SPEAROW--and`); hoje o token para no `--`.
- Sufixo é separado do miolo (`BILL's` → `Bill's`, `SP.DEF.` → `Sp.Def.`,
  `EGGs` → `Eggs`), e `junta()` evita `Diglett's's`.
- Caixa que o tokenizador não vê (minúscula no meio) tem troca literal em
  `PRE_TROCA`: `POKeMON` (sem é!) → `Pokémon`, `ROCK-type` → `Rock-type`.
- `TM82`/`HM05` e `X-TYPE` têm regra própria.

### 1.2 Duas correções que não são de caixa

`GRANPDA` → `Grandpa` e `DOWNHILL COASING` → `Coasting` (erros de digitação do
texto original; decapar sem corrigir deixaria "Granpda" à vista).

### 1.3 O que ficou em caixa alta de propósito

`TM`/`HM`/`PC`/`PP`/`TV`/`OK`/`PM`/`HQ`/`NES`/`DNA`/`Expn`; a **voz de máquina**
do Teleporter do Bill (`Route25_BillsHouse_Text_Teleporter`,
`..._Text_NotInParty`) — o SoulGold também escreve terminal em caixa alta
(`AbandonedRocketHideout`); o grito do rival `ALL BY MYSELF!` (a página
anterior já diz "all by myself" em caixa mista — a caixa alta é a entonação);
e os gritos/cantos de Pokémon (`SHAAAAAAAA`, `KEEEEEEEEEEEE`, `TUUUUU`,
`KA-BOOM`, `PI-PIKACHU`, `AGH`, `URGH`, `SHRIEEEEK`).

## 2. Plaquinhas `{SPEAKER}`

140 falas convertidas por `aplicar_falante.py --aplicar` (prefixo `"Nome: "` →
código antes da primeira letra) + **33 blocos a mão** (§2.2).

### 2.1 Falantes novos (11)

`adicionar_falante.py` (sempre no fim do enum; charmap regerado):
**Miharu**, **Shizuko**, **Youko** (as três do `NewSinjoh_KimonoHideout`),
**Arceus**, **Jirachi**, **Magikarp**, **Natu**, **Dennis** (o Magikarp shiny
da Route 20), **Radio**, **Linguist** e **{RIVAL}**. Total: 288 falantes.

`SP_NAME_RIVAL = COMPOUND_STRING("{RIVAL}")` usa o mesmo truque do
`SP_NAME_NEIGHBOR`: o placeholder é expandido no desenho
(`ExpandPlaceholder_RivalName` → "Silver", ou o nome que o jogador deu no
boletim de ocorrência). As 5 falas `"{RIVAL}: "` da Route 22 foram para ele.
**Atenção:** o Johto nosso usa `NAME_SILVER` (texto fixo "Silver") em toda fala
do rival — com o `NAME_RIVAL` existindo, trocar lá faria o nome escolhido pelo
jogador aparecer. É decisão do autor, não foi feito.

`aplicar_falante.py` ganhou dois verbetes: apelido `{rival}` → `NAME_RIVAL` e
não-falante `"And listen: "`.

### 2.2 Plaquinha que faltava (flicker)

O texto do HnS raramente traz prefixo; então, numa cena em que 3 falas tinham
`"Brock: "` e a 4ª não, a plaquinha piscava. Varredura: bloco **sem**
`{SPEAKER}` cujo **rótulo** cita um personagem que já tem plaquinha no mesmo
arquivo → 33 blocos corrigidos (Brock/Misty/Erika/Janine/Sabrina/Blaine/
Lt. Surge/Blue nos ginásios — tipicamente o `_GiveTM`/`_ExplainTM` —, Oak,
Eusine, Steven, Giovanni, Copycat, Dodrio, o Manager da Power Plant, o
Linguist de Sinjoh e a Buena do Radio Tower 2F).

**Ficaram de fora de propósito** (rótulo cita o personagem, mas quem fala é
outro, ou é narração): `Route14_Text_PidgeottoAteBerry`,
`VermilionCity_Text_Machop*`, `NewSinjoh_Text_OldLady2Steven`,
`PalletTown_Lab_Text_OaksAssistant1..3`, `..._Text_OaksLabPC`,
`TohjoFalls_GiovanniRoom_Text_RadioObject`,
`NewBarkTown_PlayersHouse_1F_Text_MomsFriend`, `Copycat_Text_2FDoll`
(`MSGBOX_SIGN`) e `Copycat_Text_Male_1..3` (a Copycat imita o jogador, e o
próprio texto já tem `"{PLAYER}: "`).

### 2.3 O que continua com `"Nome: "` (correto)

31 linhas: placa de estátua de ginásio ("Leader: Sabrina"), fala de **derrota
dentro da batalha** (`lose_text` do `trainerbattle_*` — lá não existe
plaquinha) e `"And listen: "`.

## 3. Achados de fora do texto (encontrados pelas conferências)

1. **Build quebrado em `8db1fbf091`**: `Route50Sinjoh/map.json` aponta para
   `MAPSEC_ROUTE_50`, que nunca entrou no `region_map_sections.json`
   (`undefined reference to MAPSEC_ROUTE_50`). Corrigido: entrada **no fim** do
   enum, só com nome (como os outros MAPSECs de Sinjoh; x/y é o item cosmético
   pendente). Atenção: o nome visível fica igual ao do nosso `MAPSEC_ROUTE50`
   ("Route 50") — resolver quando o mapa regional de Sinjoh for desenhado.
   `Route49Sinjoh` **compartilha** `MAPSEC_ROUTE_49` com a nossa Route 49.
2. **`FLAG_NO_WILD_CATCHING` morta em 3 mapas**: a regra da Fase 8 (script usa
   `FLAG_NO_CATCHING`, a flag crua que `B_FLAG_NO_CATCHING` lê) não foi aplicada
   em `Route49Sinjoh`, `Route50Sinjoh` e `SinjohRuins_ArceusRoom` — 13
   `setflag`/`clearflag` que ninguém lia, ou seja, **noble/Arceus capturáveis**.
   Trocado para `FLAG_NO_CATCHING` (0x1041: 35 → 47 escritas). `0x1114` ficou
   `SO_EM_DOC` — órfã, candidata a aposentar.
3. `FLAG_NO_SHINY` (0x4F9) tem 44 escritas e **nenhum leitor**
   (`P_FLAG_FORCE_NO_SHINY` = 0). É o combinado da Fase 8 ("captura desligada
   já impede shiny"), então são no-ops inofensivos — mas a flag está marcada
   "livre desde 24/09/2026": quem reaproveitar o 0x4F9 herda 44 escritas.
4. **28 linhas estouram 208 px** nos arquivos do HnS (eram 33; o decap resolveu
   5). Todas pré-existentes, a maioria fala de entrada de treinador de Alola
   (`Alola_*_TrainerBattle*_Text_0`). Não é K8 — fica para um passe de largura.
5. As três Kimono Girls de Sinjoh (Miharu/Shizuko/Youko) têm nomes diferentes
   das nossas (Zuki/Kuni/Naoko/Sayo). Mantidos os nomes do HnS.

## 4. Como repetir / conferir

```bash
F=$(git diff --name-only pre-kanto-hns HEAD -- 'data/maps/*/scripts.*')   # tire .inc com .pory vivo
python3 dev_scripts/decap_texto.py --resumo $F        # contagens + palavra fora do dicionario
python3 dev_scripts/decap_texto.py --conferir $F      # diff, nao grava
python3 dev_scripts/decap_texto.py --blocos-caixa-alta $F
python3 .claude/skills/nomear-falante/aplicar_falante.py --resumo $F
python3 .claude/skills/nomear-falante/checar_falantes.py
python3 .claude/skills/nomear-falante/medir_linha.py $F
```

O script é **idempotente**: rodar de novo em texto já decapado não muda nada.
Palavra nova em caixa alta que ele não conhecer aparece no relatório — acrescente
em `PALAVRAS`/`FRASES_MANUAIS` em vez de corrigir o texto a mão.
