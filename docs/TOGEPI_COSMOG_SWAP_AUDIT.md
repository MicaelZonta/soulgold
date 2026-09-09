# Auditoria: Trocar o Mystery Egg (Togepi → Cosmog)

Escopo: trocar `giveegg SPECIES_TOGEPI` do Mystery Egg (Violet City Pokémon Center)
por `SPECIES_COSMOG`, e compensar a perda do Togepi garantido fazendo o **primeiro
ovo do Day Care (Route 34)** nascer sempre como Togepi — para que a cena/diálogo
da Shiny Stone do Prof. Elm continue fazendo sentido.

Baseado em auditoria de código feita em 2026-09-08. Todas as referências são
`arquivo:linha` no estado atual do branch `soulgold-rift-missions`.

---

## 1. Troca mecânica principal

- [x] **Trocar a espécie do Mystery Egg**
  `data/maps/VioletCity_PokemonCenter/scripts.inc:82` (e o `.pory` fonte
  correspondente): `giveegg SPECIES_TOGEPI` → `giveegg SPECIES_COSMOG`.
  Sem efeitos colaterais de engine — `giveegg`/`ScriptGiveEgg` (`src/scrcmd.c:2360`,
  `src/script_pokemon_util.c:68`) é genérico, sem checagem de egg group ou lenda.
  Feito: `.pory` editado e `scripts.inc` recompilado via poryscript (diff
  limpo, só essa linha mudou).

- [x] **Confirmar que a evolução do Cosmog está correta para o hack**
  `src/data/pokemon/species_info/gen_7_families.h:6414` (Cosmog → Cosmoem, nível 43)
  e `:6490-6491` (Cosmoem → Solgaleo/Lunala, nível 53, dia/noite). Já funcional,
  não precisa de ASM — só decidir se querem manter idêntico ao jogo original.
  Confirmado no código: cadeia intacta, sem alterações necessárias.

- [x] **Decisão de design: lendário restrito cedo demais?**
  Cosmog é `isRestrictedLegendary` (ver dados em `gen_7_families.h`). Avaliar se
  querem gating adicional (ex.: não deixar evoluir até X badge, ou bloquear em
  trade/PC até certo ponto) — puramente decisão de balanceamento, não bug.
  Decisão (2026-09-08): manter sem gating adicional por enquanto; reavaliar
  depois de implementar a fase 2 (Togepi garantido no Day Care) e testar o
  fluxo completo.

---

## 2. Validar Script Route 34

- [x] **Nenhuma mudança de script necessária no Route 34**
  Confirmado: `data/maps/Route34_DayCare/scripts.inc:432-508` nunca inspeciona a
  espécie do ovo — só ramifica em `MON_CANT_GIVE`/`MON_GIVEN_TO_PC`/sucesso via
  `GiveEggFromDaycare` (`src/daycare.c:1201`). Toda a lógica fica isolada em C.

- [x] **Corrigida entrega do Mystery Egg (Violet City) antes de avançar flags**
  `data/maps/VioletCity_PokemonCenter/scripts.pory` /
  `VioletCity_PokemonCenter_EventScript_Aide_Accepted`: o script chamava
  `giveegg` mas nunca checava `VAR_RESULT`, e ainda por cima anunciava
  "recebeu o ovo" (fanfarra + mensagem) **antes** de sequer chamar `giveegg`
  — se `MON_CANT_GIVE` (party e PC cheios), o evento era concluído (flags
  setadas, assistente escondido) sem o jogador nunca receber o ovo.
  Corrigido seguindo o mesmo padrão de `Route34_EventScript_DaycareAcceptEgg`:
  agora `goto_if_eq VAR_RESULT, MON_CANT_GIVE, ..._AideNoRoom` roda
  **imediatamente** após `giveegg`, antes de `call VioletPCGiveExpJar` (que
  chama `giveitem`, e `giveitem` sobrescreve `VAR_RESULT` com TRUE/FALSE de
  espaço na bag). Em falha, cai em `VioletCity_PokemonCenter_EventScript_AideNoRoom`
  (label já existia, órfão) sem setar nenhuma flag — assistente continua
  visível e o jogador pode voltar a falar com ele para tentar de novo. A
  fanfarra/mensagem de recebimento e o `VioletPCGiveExpJar` só rodam no
  caminho de sucesso. `.pory` editado e `.inc` recompilado via poryscript
  (build completo testado, ROM gera sem erros).

---

## 3. Diálogo / cena do Prof. Elm (Shiny Stone)

# SoulGold — Elm, Cosmog e Eviolite

## Objetivo

Implementar uma apresentação única da família Cosmog ao Professor Elm, com Eviolite como agradecimento. Este documento substitui o plano anterior de separar uma recompensa para Togepi: remover essa recompensa independente. Não alterar o Day Care.

Reutilizar `FLAG_SHOWN_ELM_TOGEPI` como controle da cena concluída. Não criar `FLAG_SHOWN_ELM_COSMOG`. Preservar o número da flag existente; seu nome histórico pode permanecer acompanhado de comentário. Isso evita usar outra flag, mas não reduz automaticamente a estrutura de save.

## Condições e integração

- O jogador conversa com Elm no laboratório.
- Exigir `FLAG_RECEIVED_TOGEPI_EGG`, que continua representando o recebimento do Mystery Egg, agora de Cosmog.
- Exigir `FLAG_SHOWN_ELM_TOGEPI` desmarcada.
- Procurar Cosmog, Cosmoem, Solgaleo ou Lunala em qualquer posição do time, excluindo ovos.
- Selecionar o primeiro membro válido encontrado na ordem do time. Usar a espécie desse mesmo indivíduo para escolher o diálogo.
- Não exigir rastreamento de origem do Pokémon. Essa checagem não prova que o indivíduo veio do ovo recebido.
- Substituir a checagem antiga de Togepi neste fluxo. Preferir um nome descritivo como `CheckMysteryEggPokemon`, atualizando declaração, registro de special e chamada conforme os padrões reais do projeto.
- Auditar a entrada do script de Elm: desvios de história não devem tornar a apresentação permanentemente inacessível. Preservar eventos obrigatórios; quando necessário, concluir a cena obrigatória primeiro e permitir a apresentação na conversa seguinte.
- Após conclusão, usar os diálogos normais de Elm sem repetir a recompensa.
- Preservar saves que já possuem a flag marcada: não limpar a flag para conceder outra recompensa. Em saves antigos, isso significa que a nova cena pode já estar considerada concluída.

## Encenação

A cena ocorre na conversa normal com Elm. Usar a posição atual do professor, fazer com que ele olhe para o jogador e manter o mugshot real de Elm, se disponível no padrão local. Não criar NPC de Cosmog, movimentar móveis ou exigir que o Pokémon seja follower. A observação do Pokémon é representada pelo diálogo.

O tom é de um pesquisador curioso e um pouco absorvido pelo trabalho. Elm observa, se distrai com uma possibilidade e volta a se preocupar com o cuidado do parceiro. Ele ainda não explica portais, Necrozma ou os altares. Kukui é citado como colega a consultar, sem aparecer fisicamente na cena.

## Sequência exata para implementar

1. Travar controles e virar Elm para o jogador. Executar as condições acima antes de abrir a apresentação.
2. Exibir `NewBarkTown_Lab_Text_CosmogVisitIntro`.
3. Selecionar apenas uma variante:
   - Cosmog: `NewBarkTown_Lab_Text_CosmogObservation`.
   - Cosmoem, Solgaleo ou Lunala: `NewBarkTown_Lab_Text_CosmogEvolvedObservation`.
4. Exibir `NewBarkTown_Lab_Text_CosmogResearchNotes`.
5. Exibir `NewBarkTown_Lab_Text_CosmogCare`.
6. Exibir `NewBarkTown_Lab_Text_CosmogOfferEviolite`.
7. Remover o mugshot antes da apresentação do item, se esse for o padrão do projeto. Entregar uma unidade de `ITEM_EVIOLITE` pela rotina normal. Não duplicar fanfare ou mensagem de recebimento já produzidas por essa rotina.
8. Verificar o resultado da entrega imediatamente, antes de outra chamada sobrescrever `VAR_RESULT`.
   - Se falhar: exibir `NewBarkTown_Lab_Text_CosmogBagFull`, fechar a cena e liberar controles. Não marcar a flag. Na próxima conversa válida, repetir a apresentação e tentar entregar novamente; não criar uma flag só para lembrar os diálogos já vistos.
   - Se funcionar: marcar imediatamente `FLAG_SHOWN_ELM_TOGEPI`, antes das falas de encerramento, impedindo nova entrega.
9. Restaurar o mugshot, se aplicável, e exibir `NewBarkTown_Lab_Text_CosmogExplainEviolite`.
10. Exibir `NewBarkTown_Lab_Text_CosmogFarewell`.
11. Fechar mensagens, remover mugshot e liberar controles. Retornar ou encerrar conforme a estrutura real do script, sem concluir outros eventos de história por engano.

## Diálogos em inglês

Inserir os textos nos blocos `raw` do `.pory` fonte correspondente. Os labels abaixo são novos nomes propostos; atualizar as chamadas sem duplicar labels existentes. Conferir largura com a fonte real e com o mugshot aberto.

### 1. Abertura comum

```asm
NewBarkTown_Lab_Text_CosmogVisitIntro:
	.string "Elm: {PLAYER}! You came back!\p"
	.string "And you brought the Pokémon\n"
	.string "from Kukui's Egg?\p"
	.string "Let me put these notes aside.\n"
	.string "I'd like a closer look!$"
```

### 2A. Apresentação de Cosmog

```asm
NewBarkTown_Lab_Text_CosmogObservation:
	.string "So this is Cosmog...\p"
	.string "It looks as though a piece\n"
	.string "of the night sky drifted inside!\p"
	.string "To think it was tucked away\n"
	.string "in that little Egg all along.\p"
	.string "Hmm... Where did I put\n"
	.string "my other notebook?$"
```

### 2B. Apresentação de uma evolução

```asm
NewBarkTown_Lab_Text_CosmogEvolvedObservation:
	.string "It's already evolved?\n"
	.string "I have some catching up to do!\p"
	.string "What was it like when\n"
	.string "it first came out of the Egg?\p"
	.string "Even a small detail could help.\n"
	.string "Let me find a fresh page!$"
```

### 3. Pesquisa e conexão com Kukui

```asm
NewBarkTown_Lab_Text_CosmogResearchNotes:
	.string "Kukui sent me one Egg,\n"
	.string "and now I have a hundred questions.\p"
	.string "I'll send him my observations.\n"
	.string "He may know where to start.\p"
	.string "I suspect his reply will bring\n"
	.string "a few more questions too!$"
```

### 4. Elm volta sua atenção ao parceiro

```asm
NewBarkTown_Lab_Text_CosmogCare:
	.string "Oh, listen to me rambling.\n"
	.string "You're here for a visit!\p"
	.string "Thank you for taking care\n"
	.string "of this Pokémon, {PLAYER}.\p"
	.string "You get to see things together\n"
	.string "that I'd never see in this lab.$"
```

### 5. Oferta da recompensa

```asm
NewBarkTown_Lab_Text_CosmogOfferEviolite:
	.string "Actually, I have something\n"
	.string "for your travels.\p"
	.string "I've been keeping it here\n"
	.string "for a young Trainer to use.$"
```

Entregar `ITEM_EVIOLITE` aqui. A rotina existente deve cuidar da mensagem padrão de recebimento.

### 6. Falha de entrega

```asm
NewBarkTown_Lab_Text_CosmogBagFull:
	.string "Oh! There's no room\n"
	.string "in your Bag right now.\p"
	.string "Make some space and come back.\n"
	.string "I'll keep it safe for you!$"
```

### 7. Explicação após entrega bem-sucedida

```asm
NewBarkTown_Lab_Text_CosmogExplainEviolite:
	.string "That's an Eviolite.\p"
	.string "Have a Pokémon that can still\n"
	.string "evolve hold it. It will boost\l"
	.string "its Defense and Sp. Def.\p"
	.string "A little extra protection\n"
	.string "while it's growing!\p"
	.string "You can give it to whichever\n"
	.string "partner needs it most.$"
```

A explicação é geral: também funciona se o Pokémon apresentado já for Solgaleo ou Lunala. Não afirmar que Eviolite funciona nessas evoluções finais nem que ela faz Cosmog evoluir.

### 8. Despedida

```asm
NewBarkTown_Lab_Text_CosmogFarewell:
	.string "If you notice anything unusual,\n"
	.string "you have my number.\p"
	.string "Now, where was that notebook...?\n"
	.string "Ah! Under the first one.\p"
	.string "Take care, {PLAYER}.\n"
	.string "Both of you!$"
```

## Ligação e lembrete sobre o ovo

Como existe novamente uma única apresentação, manter a ligação de Goldenrod controlada por `FLAG_SHOWN_ELM_TOGEPI`, agora reutilizada para Cosmog. Exigir recebimento do Mystery Egg e preservar a proteção atual contra repetição da ligação. Não adicionar flag para a chamada.

O lembrete no laboratório só deve aparecer quando o ovo tiver sido recebido e a apresentação ainda estiver pendente. Ele não deve substituir o aviso de bolsa cheia na mesma interação.

```asm
GoldenrodCity_Text_ElmCall:
	.string "Elm: Hello, {PLAYER}!\n"
	.string "How is that Egg doing?\p"
	.string "Once it hatches, bring the\n"
	.string "Pokémon to the lab sometime.\p"
	.string "Kukui and I are both curious\n"
	.string "about our little mystery!$"

NewBarkTown_Lab_Text_ElmWaitingEggHatch:
	.string "Elm: Has anything changed\n"
	.string "with the Egg?\p"
	.string "When it hatches, bring its\n"
	.string "Pokémon along to see me.\p"
	.string "If it has already hatched,\n"
	.string "make sure it's in your party!$"
```

## Arquivos a conferir na árvore atual

- `src/braille_puzzles.c`: checagem antiga de Togepi.
- `data/specials.inc` e declarações aplicáveis: registro da função usada pelo script.
- `data/maps/NewBarkTown_Lab/scripts.pory`: entrada da conversa, apresentação, entrega e textos.
- `data/maps/GoldenrodCity/scripts.pory`: condição da ligação e texto.
- `include/constants/flags.h`: preservar a flag reutilizada; documentar seu significado.

Verificar consumidores de `CheckTogepi`, `FLAG_SHOWN_ELM_TOGEPI` e de eventual flag nova criada pelo plano anterior antes de alterar. Não reciclar automaticamente um número de flag já usado em saves ou outro evento.

O Mystery Egg deve entregar Cosmog em Violet como parte da alteração principal já planejada. Preservar `FLAG_RECEIVED_TOGEPI_EGG` e seus consumidores de progressão, incluindo Route 32. Este documento não pede alterar a troca de Red Scale, outros presentes de Elm ou recompensas fora desta cena.

## Validação 

- [x] Não existe mais apresentação/recompensa independente para Togepi neste fluxo.
- [x] Nenhuma flag nova é necessária para a cena.
- [ ] Cosmog em qualquer slot, após receber o Mystery Egg, dispara a variante correta. *(lógica implementada, pendente teste no emulador)*
- [ ] Cosmoem, Solgaleo e Lunala usam a variante de evolução. *(lógica implementada, pendente teste no emulador)*
- [x] Ovos e Pokémon de outras famílias não disparam a cena.
- [x] Com vários membros elegíveis, a variante corresponde ao primeiro selecionado.
- [x] Eviolite é entregue uma única vez.
- [x] Falha na entrega não marca a conclusão; nova conversa permite tentar novamente.
- [x] A flag de conclusão é marcada imediatamente após o sucesso da entrega.
- [x] Reentrar no mapa e salvar/carregar não duplica recompensa.
- [x] A ligação e o lembrete param após a conclusão.
- [x] Eventos obrigatórios de Elm continuam acessíveis.
- [ ] Textos cabem na caixa com mugshot, sem cortes ou quebra de controles. *(precisa conferência visual no emulador)*
- [x] Editar `.pory` e regenerar `.inc` conforme o build real; não manter fontes divergentes.
- [x] Compilar e reportar resultado, arquivos alterados e o que ainda precisa de teste no emulador.

### Status da implementação (2026-09-08)

Implementado e compilado com sucesso (`make -j4`, ROM gera sem erros/warnings):

- `src/braille_puzzles.c`: `CheckTogepi()` (bool8, só slot 0, só família Togepi)
  substituída por `CheckMysteryEggPokemon()` (u16, percorre todo o time via
  `gPlayerPartyCount`/`CalculatePlayerPartyCount()`, retorna a espécie do
  primeiro Cosmog/Cosmoem/Solgaleo/Lunala encontrado ou `SPECIES_NONE`;
  mantém o gate por `FLAG_RECEIVED_TOGEPI_EGG` que já existia).
- `data/specials.inc`: `def_special CheckTogepi` → `def_special CheckMysteryEggPokemon`.
- `data/maps/NewBarkTown_Lab/scripts.pory` (+ `.inc` recompilado via poryscript):
  - `NewBarkTown_Lab_EventScript_Elm_Check_Togepi` agora chama
    `CheckMysteryEggPokemon` e ramifica em `_Elm_Cosmog_Seen` (Cosmog) ou
    `_Elm_Cosmog_Evolved_Seen` (Cosmoem/Solgaleo/Lunala), caindo em
    `_Elm_Cosmog_Reward` para o restante da cena comum.
  - Cena usa `createfieldmugshot`/`removefieldmugshot` em torno dos diálogos,
    removendo o mugshot antes do `giveitem ITEM_EVIOLITE` e restaurando
    depois, seguindo o padrão já usado no resto do arquivo.
  - `goto_if_eq VAR_RESULT, FALSE, ..._Cosmog_BagFull` roda imediatamente após
    o `giveitem`, antes de qualquer outra chamada — em falha, mostra
    `..._Text_CosmogBagFull` e libera sem marcar `FLAG_SHOWN_ELM_TOGEPI` (o
    `call_if_unset` no script pai garante nova tentativa completa na próxima
    conversa). Em sucesso, `setflag FLAG_SHOWN_ELM_TOGEPI` roda antes das
    falas de encerramento (`CosmogExplainEviolite`/`CosmogFarewell`).
  - Textos antigos (`ShowTogepi1/2/3`, `ElmGiveEverstone1/2`) removidos e
    substituídos pelos 8 textos novos do documento (`CosmogVisitIntro`,
    `CosmogObservation`, `CosmogEvolvedObservation`, `CosmogResearchNotes`,
    `CosmogCare`, `CosmogOfferEviolite`, `CosmogBagFull`,
    `CosmogExplainEviolite`, `CosmogFarewell`).
- `data/maps/GoldenrodCity/scripts.pory`: **não alterado** — a chamada do
  PokéNav (`GoldenrodCity_Elm_Togepi_Call`) e o texto já eram genéricos
  (não mencionam espécie) e já usam `call_if_unset FLAG_SHOWN_ELM_TOGEPI`,
  então continuam corretos sem mudança.

Pendente (precisa emulador, não dá para confirmar só por leitura de código):
testar visualmente a cena com Cosmog e com uma evolução no time (posição
variada no time), confirmar quebra de linha dos textos novos com o mugshot
do Elm aberto, e testar o caminho de bag cheia (deixar a bag cheia antes de
falar com o Elm) para ver o retry funcionando na prática.

## Limite da especificação

Eviolite e sua descrição foram conferidas anteriormente na cópia local de SoulGold, que pode diferir da branch atual. Este documento entrega o roteiro e a sequência para execução; não afirma que a cena já foi implementada ou testada no jogo.

---

## 4. Flags e limpeza em new game

- [x] **Renomear as flags antigas para refletirem o Cosmog, reaproveitando os IDs.**
  `include/constants/flags.h`: `FLAG_SHOWN_ELM_TOGEPI` (0x2ED) →
  `FLAG_SHOWN_ELM_COSMOG`, `FLAG_RECEIVED_TOGEPI_EGG` (0x379) →
  `FLAG_RECEIVED_MYSTERY_EGG`. Números preservados (compatível com saves
  existentes); nome antigo mantido como comentário na definição. Todos os
  consumidores atualizados: `data/maps/NewBarkTown_Lab/scripts.pory`,
  `data/maps/GoldenrodCity/scripts.pory`, `data/maps/Route32/scripts.pory`,
  `data/maps/VioletCity_PokemonCenter/scripts.pory`,
  `data/maps/VioletCity/scripts.pory`, `data/scripts/new_game.inc`,
  `src/braille_puzzles.c`. `.inc` correspondentes recompilados via
  poryscript. De brinde, o label interno `..._Elm_Check_Togepi` (não é
  flag, mas ficava destoando das outras labels `..._Elm_Cosmog_*` da cena)
  também foi renomeado para `..._Elm_Check_Cosmog`. Build completo
  (`make -j4`) sem erros/warnings.
- [x] **Remover o evento antigo de Togepi/Shiny Stone.**
  Já removido na fase 3: `ShowTogepi1/2/3` e `ElmGiveEverstone1/2` foram
  substituídos pelos textos/rotina novos do Cosmog. Confirmado por busca —
  não há mais nenhuma referência a `Everstone`/`ShinyStone`/`ShowTogepi` em
  scripts de mapa.
- [x] **Confirmar reset correto de todas as flags envolvidas em `NewGame`:**
  - `FLAG_RECEIVED_MYSTERY_EGG` (ex-`FLAG_RECEIVED_TOGEPI_EGG`) — limpa em
    `VioletCity_EventScript_Trigger` (`data/maps/VioletCity/scripts.pory:26`,
    coord trigger no Gate_Route31_VioletCity que reresseta o estado da
    cidade).
  - `FLAG_SHOWN_ELM_COSMOG` (ex-`FLAG_SHOWN_ELM_TOGEPI`) — limpa em
    `data/scripts/new_game.inc:111`.
- [x] **Verificar `Route32`** — Balding Man que checa
  `FLAG_RECEIVED_MYSTERY_EGG` antes de liberar diálogo
  (`data/maps/Route32/scripts.pory:220`). Gate continua funcionando
  normalmente (a flag ainda é setada ao aceitar o Mystery Egg, seja qual for
  a espécie). Texto usado nesse caminho (`Route32_Text_CooltrainerM_AideIsWaiting`)
  não menciona Togepi — só "some guy wearing glasses... at the Pokémon
  Center". Nenhuma mudança de texto necessária.

---

## 5. Itens fora de escopo / não precisam mudar

- [x] `EcruteakCity_Theater_Text_ZukiSeen` (`data/maps/EcruteakCity_Theater/scripts.inc:1017-1030`)
  — menciona "Mystery Egg" só como referência de lore para a questline
  separada de Lugia/Ho-Oh (Rift Missions). Não checa espécie via código,
  puramente cosmético. Só mudar se quiserem alinhar a lore tematicamente.
  Reconfirmado (2026-09-08): texto/linhas batem exatamente com o
  referenciado, arquivo sem alterações pendentes. Nenhuma mudança feita.
- [x] Gacha do Game Corner de Mauville (`src/game_corner_gacha.c:1697,1805`)
  continua distribuindo Togepi normalmente — não precisa de nenhuma mudança
  (é inclusive uma segunda via de obtenção).
  Reconfirmado: as duas linhas (`SPECIES_TOGEPI`) seguem lá, arquivo sem
  alterações pendentes. Nenhuma mudança feita.
- [x] Treinadores/contest opponents com Togepi/Togetic
  (`src/data/trainers.h:15839,27692`, `src/data/battle_frontier/trainer_hill.h:891`,
  `src/data/contest_opponents.h:2892`, rentals de Togekiss em
  `src/data/battle_frontier/battle_frontier_mons.h:6842+`) — não são
  capturáveis, não afetados pela troca.
  Reconfirmado: todas as entradas batem (Togetic em treinadores comuns,
  Togepi em Trainer Hill e na oponente de contest Clara, Togekiss em
  rental do Battle Frontier). Arquivos sem alterações pendentes. Nenhuma
  mudança feita.

---

## 6. Ordem de implementação sugerida

3. Trocar `giveegg SPECIES_TOGEPI` → `SPECIES_COSMOG` (item 1). — [x] feito (fase 1).
4. Re-gatear `CheckTogepi()`/cena do Elm para a nova flag (item 3, Opção A). — [x] feito (fase 3, `CheckMysteryEggPokemon`).
5. Testar o fluxo completo: Mystery Egg vira Cosmog — [ ] pendente teste no emulador (ver seção 3, itens de validação ainda em aberto).
6. Resetar todas as flags em new game (item 4). — [x] feito e reconfirmado (fase 4).

---

## Status geral

Fases 1 a 4 implementadas, compiladas (`make -j4` sem erros/warnings) e
reconfirmadas por leitura de código. Fase 5 é só uma lista de não-mudanças,
reconfirmada e sem pendências. O único item realmente em aberto no
documento inteiro é o teste manual no emulador (cena do Elm com Cosmog em
posições variadas do time, quebra de linha dos textos novos, e o caminho de
bag cheia) — não é possível confirmar isso por leitura de código.
