# Match Call GSC — o telefone do Pokégear (24/10/2026)

Porte do telefone do pokehns 2.0.6: os treinadores pedem o número, ligam depois,
pedem revanche e guardam itens. **Build limpo** (`make -j`), `flag_audit.py`
regenerado, nenhuma linha acima de 208 px. **Não testado no jogo.**

O que entrou é a parte de **receber**: o jogador não discursa a agenda (não
existe app de telefone no Pokégear — ver §7). Na prática é o que o GSC faz 90%
do tempo: você bate no treinador, ele pede o número, depois ele liga.

## 1. Como funciona, de ponta a ponta

1. **Pedir o número.** O `trainerbattle_*` do treinador ganhou o 4º argumento
   (script que roda depois da vitória): ele pede o número e chama
   `register_matchcall TRAINER_X`, que seta
   `TRAINER_REGISTERED_FLAGS_START + REMATCH_X`.
2. **Ligar.** Dois gatilhos, os dois em `src/field_control_avatar.c`:
   - `TryStartRouteMatchCall` (novo, `src/match_call.c`): a cada **255 passos
     no mesmo mapa**, sorteia um treinador **daquele mapa** que já deu o número
     e já foi derrotado. Uma em cinco vezes ele **achou um item** (seta a flag e
     escreve o item na var); nas outras, marca revanche
     (`UpdateRematchIfDefeated`).
   - `TryStartMatchCall` (o do vanilla, ajustado): a cada 30 passos (era 10),
     10 minutos de jogo, 30% de chance, ao ar livre ou em caverna.
3. **A fala.** `SelectMatchCallMessage` tem um ramo novo: se o treinador está em
   `sPhoneTrainers`, a fala sai da tabela (revanche > item > conversa) em vez do
   montador de frases de Hoenn. `{STR_VAR_3}` é um Pokémon do time que o
   jogador enfrentou. A plaquinha com o nome de quem liga vem de
   `gSpeakerName = GetTrainerNameFromId(...)` em `MatchCall_PrintIntro`.
4. **Cobrar.** Voltando ao treinador: `ShouldTryRematchBattle` → `trainerbattle_rematch`
   (time mais forte), ou `goto_if_set FLAG_X_HAS_PHONE_ITEM` → ele entrega o item.

Pré-requisitos: `FLAG_HAS_MATCH_CALL` (setada quando a mãe entrega o Pokégear,
`NewBarkTown_PlayersHouse_1F_EventScript_GivePokeGear`) e **3 medalhas**
(`OW_REMATCH_BADGE_COUNT`, era 5; 3 = depois da Whitney, como no pokehns).

## 2. Os 40 da agenda

28 de Johto (Joey na Route 30 … Reena na Route 27) + 12 de Kanto (Alex, Riley,
Trevor, Kyle, Carter, Hillary, Rob, Nicole, Billy, Kenny, Joel, Charles). Os de
Kanto e os das Routes 26/27 **já estavam ligados**: aqueles mapas vieram do HnS
inteiros, com `register_matchcall` no script. Os 24 restantes foram costurados
por `dev_scripts/importa_match_call_scripts.py` (§5).

Nove guardam item: Wade (berries), Alan e Dana (pedras), Tully, Wilton (pedra +
balls), Derek e Beverly (Nugget), Jose (Sharp Beak/Silk Scarf), Kenji (PP Up).
Flag `FLAG_*_HAS_PHONE_ITEM` + var `VAR_*_PHONE_ITEM`. A do José é a 0x1112,
que veio junto com a Route 27 — renomeada de `FLAG_JOSE_HAS_ITEM` para o padrão
dos outros oito.

## 3. Tabela de revanche reconstruída

`include/constants/rematches.h` era a lista de Hoenn (49 normais + 14
especiais), e `gRematchTable` em `src/battle_setup.c` estava **destroçada** por
alguma renumeração antiga (entradas apontando para `TRAINER_GRUNT_33`,
`TRAINER_KIP`, todas na `MAP_ROUTE118`, que está fora da ROM). Virou:

- 40 entradas `REMATCH_<NOME>`, cada uma com o treinador, até 4 revanches e **o
  mapa onde ele está de pé** (o mapa é o que o "mesma rota" e o contador de
  passos usam — errar o mapa mata a ligação de rota sem erro de build);
- os 14 especiais de Hoenn continuam no enum, com a tabela vazia, porque
  `src/pokenav_match_call_data.c` referencia os nomes.

`REMATCH_TABLE_ENTRIES` caiu de 62 para 54.

**102 times de revanche** entraram em `src/data/trainers.party` (fases 2–5 dos
40, do `trainers_hns.party`), com IDs em slots `TRAINER_UNUSED_*` < 1056 e
`Class`/`Pic` sem o sufixo ` Hns`. O Rattata Lv65 do Joey com Silk Scarf,
Body Slam, Thunderbolt, Pursuit e Iron Tail está lá.

De brinde: os **165 nomes de treinador em CAIXA ALTA** do `.party` (importes das
fases 3 e 8 + os `_POSTOBC`) viraram caixa mista — em batalha aparecia
"JOEY", e o nosso Johto escreve "Joey". `LTSURGE` virou `Lt. Surge`.

## 4. Save: 60 bytes, e por que não no lugar do vanilla

`FREE_MATCH_CALL` virou `FALSE`. Os dois campos (`trainerRematchStepCounter` +
`trainerRematches[MAX_REMATCH_ENTRIES]`) **não** podem entrar no 0x9C8 do
vanilla: os offsets do meio do `SaveBlock1` estão presos por `STATIC_ASSERT` em
`src/save.c` (caixas 16–19 do PC, do upstream). Eles entraram **no fim**, logo
antes de `objectEventsExtra`, e os dois asserts do fim passaram a somar
`SAVEBLOCK1_MATCH_CALL_BYTES`.

`MAX_REMATCH_ENTRIES` foi de 100 para **58**: ≥ 54 (`STATIC_ASSERT` novo em
`battle_setup.c`) e 2+58 = 60, múltiplo de 4, para `objectEventsExtra` não
ganhar padding.

**Custo:** SaveBlock1 15760 → 15820 B. Sobram **52 B** no último setor + os 24
de `futureReserved`. `OBJECT_EVENTS_COUNT` agora só pode subir de 24 para 25
(era até 27) — a skill `limites-do-engine` foi corrigida.

## 5. As duas ferramentas

- `dev_scripts/importa_match_call_scripts.py` — costura o script de cada
  treinador de Johto: acrescenta o 4º argumento do `trainerbattle_*`, as
  checagens de item/revanche e os blocos e textos novos, convertendo os nomes
  `_HNS`. Casa por **rótulo**, não copia o arquivo: o nosso Johto e o deles têm
  a mesma origem, então `Route30_EventScript_RegisterJoey` é o mesmo rótulo nos
  dois lados. `--conferir` antes de `--aplicar`.
  Armadilha achada: vários dos nossos escrevem `trainerbattle_single
  TRAINER_X Route..._Seen, ...` **sem a vírgula** depois do treinador (o GAS
  aceita espaço como separador de argumento de macro), então o regex aceita os
  dois.
- `dev_scripts/decap_texto.py` — os 1298 linhas de fala do telefone
  (`data/text/match_call_phone.inc`, 156 rótulos) e os textos novos dos mapas
  passaram pelo decap do K8. A ferramenta ganhou os 40 nomes da agenda e um
  conserto importante: a chave do dicionário não tira mais a flexão
  (`"Moltres"` cadastrava `MOLTR`, e `MOLTRES` no texto não achava nada).

## 6. Bug consertado na importação (o item sumia)

O padrão do HnS entrega o item assim:

```
	msgbox ...HasItem
	giveitem VAR_X_PHONE_ITEM
	goto_if_eq VAR_RESULT, FALSE, ...NoRoom   @ nunca pega
	clearflag FLAG_X_HAS_PHONE_ITEM
```

`giveitem` chama `Std_ObtainItem`, que guarda o resultado em `VAR_0x8007` e
**sobrescreve `VAR_RESULT`** (`checkitemtype` escreve a pocket lá). Com a bolsa
cheia o teste falhava, a flag era limpa e **o item desaparecia**. Os nove
blocos agora checam espaço **antes da oferta** (`checkitemspace`), como manda a
regra do projeto. O José (Route 27) já estava com o bug no repo desde a Fase 3.

## 7. O que falta (rodada própria)

- [ ] **App de telefone no Pokégear** (ligar para quem está na agenda). O
      Pokégear tem 4 apps (Map/DexNav/Trophies/Radio) e nenhum de telefone; a
      UI do Match Call do Pokénav existe no código mas não é alcançável. É
      trabalho de interface, com arte.
- [ ] Texto de "check page" por treinador: os 40 caem num genérico
      (`gText_MatchCallGeneric_*`) em `GetMatchCallFlavorText`. Só aparece se o
      app do telefone existir.
- [ ] QA no jogo: pedir o número ao Joey, andar 255 passos na Route 30, receber
      a ligação, voltar e revanchar; ligação de item do Wade (Route 31) com a
      bolsa cheia e vazia; confirmar que o telefone só começa com 3 medalhas.
- [ ] Decidir se as falas do rival no Johto passam a usar `NAME_RIVAL` (K8).
