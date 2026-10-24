# Match Call GSC — o telefone do Pokégear (24/10/2026)

Porte do telefone do pokehns 2.0.6: os treinadores pedem o número, ligam depois,
pedem revanche e guardam itens — e o Pokégear ganhou a **agenda** para ligar de
volta (§8, feita em 24/10/2026 na mesma rodada). **Build limpo** (`make -j`),
`flag_audit.py` regenerado, nenhuma linha acima de 208 px. **Não testado no
jogo.**

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

## 7. A agenda do Pokégear (`src/pokegear_phone.c`)

App novo, `POKEGEAR_APP_PHONE`, no fim do enum de propósito (o
`registeredPokegearApps` do save guarda esses números; inserir no meio trocaria
o atalho que o jogador já registrou). Aparece quando o jogador tem o Pokégear
(`FLAG_HAS_MATCH_CALL`), a mesma flag que liga as ligações.

**Lista**: quem deu o número, na ordem da tabela de revanche, com classe e nome
("Youngster Joey"), 5 por tela, rolando. Um **`!`** marca quem está esperando
revanche ou guardou um item — as duas coisas que a ligação recebida marca
(`DoesPhoneTrainerHaveItem`, em `match_call.c`).

**Ligar**: A liga, e a fala sai da **mesma** `SelectMatchCallMessage` que atende
a ligação recebida no campo, com o nome de quem fala na plaquinha de cima.
Ligar **não** muda estado: quem marca revanche é a ligação de rota. Quer dizer
que a agenda é para conversar e para conferir quem está esperando — não dá para
farmar revanche ligando.

Desenho: reaproveita o fundo do próprio Pokégear (versão do menino e da menina),
janela com moldura padrão para a lista/fala, barra de ajuda embaixo. Molde:
`src/pokegear_radio.c`.

### O que mudou no menu principal

Cabiam 4 botões de 4 linhas nos 16 tiles do painel azul. Com 5 apps o botão
passou a ocupar **3 linhas**: `DrawMainButtons` copia as duas primeiras linhas
da arte e a última, pulando a segunda linha de preenchimento — **a arte não
mudou** e o botão continua com borda em cima e embaixo. O texto e o ícone
desceram junto (`GetButtonY(i) * 8 - 11` e `+ 12`).

O ícone de celular (`icon_phone.png`) era usado pelo **DexNav**: voltou para o
telefone, e o DexNav ganhou uma **lupa** desenhada por código
(`graphics/pokegear/icon_dexnav.png`, mesma paleta e mesmo tamanho dos outros).

### Armadilha que custaria tela corrompida

A janela da lista tem 28x10 = **280 tiles** a partir do `baseBlock` 1; a moldura
padrão (`DrawStdFrameWithCustomTileAndPalette`) estava com tile base 150, que o
rádio usa porque a janela dele é pequena. Dentro dos 280, a moldura escreveria
por cima do texto. Mapa do BG1 agora: lista 1-280, moldura 300-308, nome
320-367, ajuda 370-417 (o bloco tem 512).

## 8. O que falta (rodada própria)

- [ ] Texto de "check page" por treinador: os 40 caem num genérico
      (`gText_MatchCallGeneric_*`) em `GetMatchCallFlavorText`. A agenda não usa
      essa página — é a do Pokénav de Hoenn, que continua inalcançável.
- [ ] Contato que não é treinador (mãe, Elm, Baoba): o Pokénav tem os headers
      (`src/pokenav_match_call_data.c`), mas a agenda só lista treinador.
- [ ] QA no jogo: pedir o número ao Joey, andar 255 passos na Route 30, receber
      a ligação, voltar e revanchar; ligação de item do Wade (Route 31) com a
      bolsa cheia e vazia; confirmar que o telefone só começa com 3 medalhas; e
      **a tela da agenda** (5 botões no menu, lista rolando, ligação com `\p`).
- [ ] Decidir se as falas do rival no Johto passam a usar `NAME_RIVAL` (K8).
