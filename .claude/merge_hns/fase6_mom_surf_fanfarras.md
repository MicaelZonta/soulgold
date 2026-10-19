# Fase 6 — Mom's Savings, fanfarras HGSS, surf sprites Gen 4

Fonte: pokehns-expansion v2.0.6 (somente leitura). Nada commitado; so objetos soltos compilados
(`mom_savings.o`, `new_game.o`, `field_control_avatar.o`, `trainer_card.o`, `battle_script_commands.o`,
`sound.o`, `event_scripts.o`), sem make completo e sem teste no jogo.

## 1. Mom's Savings

- `src/mom_savings.c` + `include/mom_savings.h` portados do P. Diferencas deliberadas:
  - **Sem VAR_MOM_GIFT_ITEM/QUANTITY** (nao existem no S e vars.h estava fora do escopo). O tipo do presente
    (item / berry / decoracao) fica nos 2 bits altos de `momSavings.normalGiftFlags` (bits 14-15; a tabela
    sequencial usa so os bits 0-9). O item ja foi para o PC na hora da compra, a ligacao so precisa do tipo.
  - **Sem randomizer** (nao existe no S) e **sem `challengeSettings.disableMatchCall`** (nao existe no S): a ligacao
    da mae nao respeita nenhuma opcao de desligar Match Call.
  - **Starter doll**: usa `VAR_PLAYER_STARTER_SPECIES` (especie, gravada por ui_birch_case.c) em vez do indice 0/1/2
    de `VAR_STARTER_MON`. Chikorita/Cyndaquil/Totodile -> boneca correspondente; outro -> Togepi.
  - `AdjustQuantityAccordingToDPadInput_MomVersion` copiada como `static` no proprio .c (nao mexe em menu_helpers).
  - Textos "How much would you like to deposit/withdraw" sao `static` no .c (nao mexe em strings.c).
  - **Sem specials.inc**: as funcoes `Special_Mom*` recebem `struct ScriptContext *` e sao chamadas com `callnative`.
  - `IS_HNS` nao existe no S; os hooks entram sem `#if`.
- Hooks: `new_game.c` (InitMomSavings apos ClearDecorationInventories), `field_control_avatar.c`
  (Mom_TryTriggerGiftCall em TryStartStepBasedScript, antes do repel), `battle_script_commands.c`
  (Cmd_getmoneyreward: deposita money/4 se Mom_IsSavingEnabled), `trainer_card.c` (mostra "¥dinheiro/saldo da mae").
- `data/scripts/mom_savings.inc` (3 scripts de ligacao + textos) copiado do P e incluido em `data/event_scripts.s`
  apos players_house.inc.
- **Mae real (NewBarkTown_PlayersHouse_1F)**: fluxo S preservado. Em `_Mom_Regular`:
  - com Grooming Kit: menu Rest / Grooming / **Savings** / Cancel (era Rest / Grooming / Cancel);
  - sem Kit: antes curava direto; agora pergunta Rest / **Savings** / Cancel (texto novo `MomWelcomeHomeNoKit`).
  Rest e Grooming chamam exatamente os mesmos scripts de antes. Submenu: Check savings / Deposit / Withdraw /
  Auto-saving / Exit, todo com `{SPEAKER NAME_MOM}`. Textos em ingles.
- Presentes (do P, inalterados): Super Potion 900, Repel 4000, Silk Scarf 7000, starter doll 10000, Moon Stone 15000,
  Hyper Potion 19000, Leftovers 30000, Choice Band 40000, Snorlax Doll 50000, Master Ball 100000; berries a cada 2300.
  Entregues ao PC (AddPCItem / DecorationAdd), nunca na bolsa, entao nao ha checkitemspace a fazer; se o PC estiver
  cheio o item se perde (mesmo comportamento do P). Pendencia opcional: checar espaco no PC antes de debitar.

### Pendencias / riscos
- Testar no jogo (nao feito): menu da mae, deposito/saque (tela de input usa janelas/baseBlock do P), ligacao de presente
  (pokenavcall com texto "MOM: ..." simples, sem plaquinha), trainer card (string "¥N/saldo" pode estourar largura).
- A ligacao dispara em Route/Ocean/City/Town. O S quase nao usa `pokenavcall`; confirmar a janela.
- `MOM_GIFT_KIND_*` ocupa bits 14-15 de normalGiftFlags: nao usar mais de 14 presentes sequenciais.
- Flags: nenhuma criada (FLAG_MOM_HAS_GIFT ja existia). flag_audit nao rodado (instrucao).
- Dialogo da mae com `FLAG_MOM_VISITED` etc. nao foi tocado.

## 2. Fanfarras HGSS

O `sFanfares[]` do S ja tem os 11 pares com `MUS_HG_*` (o S usa 3 campos: lookup, HG, duracao; o P tem tabela
separada `sFanfaresHnS` sob IS_HNS). Faltavam so 4 entradas, adicionadas (indices 18-21, com os mesmos numeros do P):
`FANFARE_HG_BUG_CONTEST_1ST/2ND/3RD` (232/186/84) e `FANFARE_HG_OBTAIN_EGG` (131). Como `include/constants/sound.h`
nao e meu, os `#define FANFARE_HG_*` ficam em `src/sound.c` sob `#ifndef`. Lookup e o proprio MUS_HG_*, entao
`playfanfare MUS_HG_OBTAIN_EGG` etc. funciona. Duracoes das 18 outras: mantidas as do S (S 240 no EVOLVED vs P 220;
S 185 no match call vs P 160 — nao alterei). Pendencia: ninguem chama as 4 novas ainda (concurso de insetos / ovo).

## 3. Surf sprites Gen 4

**Nada a fazer.** O S ja tem todas as familias (Bibarel, Buizel, Floatzel, Shellos E/W, Gastrodon E/W, Finneon,
Lumineon) registradas em `surfable_pokemon.h` / `_graphics.h` / pic tables / templates (guardadas por
`P_FAMILY_*`, todas habilitadas com `P_GEN_4_POKEMON`), com PNGs de nomes do upstream (`bibarel.png`,
`shellos_east_sea.png`, `finneon.png`...), sem prefixo numerico. Copiar os do P duplicaria simbolos e arte
(os do P usam `0400_bibarel` etc. e tags de paleta proprias). Nenhum arquivo copiado.
