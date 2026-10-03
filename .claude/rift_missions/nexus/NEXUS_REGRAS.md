# Nexus — regras

> **Implementação:** [`NEXUS_IMPLEMENTATION.md`](NEXUS_IMPLEMENTATION.md) —
> onde cada regra está no código e como acrescentar treinador, lendário ou prêmio.

Regras do autor para o **Nexus** (o loop pós-Necrozma das Rift Missions,
design §10). **Valem para qualquer trabalho no Nexus**: time de treinador,
sorteio, pool de lendários, prêmio, mapa, script. Se uma tarefa pedir algo que
contraria uma regra daqui, pare e pergunte ao autor antes.

Decididas pelo autor em 25/09/2026; revisão 2 em 26/09/2026 (formato
Traditional por categoria, Singles/Doubles, derrota no Daily, IV do boss);
revisão 3 em 27/09/2026 (fragmento, Looker Files, forma superior do boss, tom
do lugar — R17 a R20). As notas "No código" dizem o que já existe
no repositório para cumprir a regra e onde está a armadilha.

---

## R1. Lendário que dá para pegar fora do Nexus só aparece depois de capturado

Se o lendário tem **método de obtenção fora do Nexus**, ele só entra no sorteio
depois que o jogador o tiver **capturado** (Pokédex: *caught*). Ex.: Mewtwo tem
encontro na `CeruleanCave_B2F`; ele só aparece no Nexus depois de o jogador
pegar o Mewtwo de lá. Isso protege os eventos da campanha e não estraga a
surpresa.

Lendário **sem** método fora do Nexus entra no sorteio desde o início.

- A classificação de quem tem método está em
  [`POOL_LENDARIOS.md`](POOL_LENDARIOS.md) (96 com método, 32 sem, em
  25/09/2026). Método novo criado na campanha **move** o lendário para o grupo
  "precisa capturar antes"; atualize aquele arquivo junto.
- Formas contam pela espécie: pegar Kyogre libera Kyogre (a Primal vem com ele).
  Aves de Galar são espécies separadas das de Kanto.
- **No código:** `getcaughtmon SPECIES_X` (`asm/macros/event.inc`) lê a flag de
  capturado da Pokédex — é o que as Meteor Caves já usam.
- **Os corcéis do Calyrex** (Berry Master, 03/10/2026): só um deles pode ser pego na
  campanha. Antes da escolha das sementes os dois esperam captura; depois, o corcel
  **não escolhido** volta a ser só do Nexus e entra sempre no sorteio
  (`GardenSteed_NexusEligible`, `src/berry_garden.c`). O Calyrex segue a R1 normal.

## R2. Level scaling: 100% no maior nível da equipe

Todo treinador e o boss do Nexus sobem ou descem para o **maior nível da equipe
atual** do jogador. O Nexus é **sempre difícil**, e funciona igual com um time
nível 100 (para se desafiar) ou nível 50 (para upar).

- A dificuldade vem de time, sinergia, IV/EV, itens e boss — **nunca** de
  deixar o adversário acima do jogador.
- **No código:** o modo pronto é `LEVEL_SCALING_CONFIG_PARTY_HIGHEST`
  (`include/level_scaling.h`), por treinador em `src/data/level_scaling_rules.h`.
- ⚠️ **Armadilha:** `GetCurrentTrainerLevelScalingMode()`
  (`src/level_scaling.c`) desliga **todo** scaling de treinador quando a opção
  do jogador está OFF — e ela nasce OFF (`src/new_game.c`). O Nexus precisa
  escalar **independente da opção do menu**; isso é código a escrever, não
  configuração.
- O boss lendário também escala; o `setbossbattle` só cuida de barras e
  multiplicador, não de nível.

## R3. Abre uma vez por dia; perder não tranca nem custa nada

- O Nexus (modo Daily) **abre 1x por dia**: o conteúdo daquele dia — os
  treinadores de cada teleporte, o lendário e o campeão — é **sorteado uma vez
  por dia** e fica igual até virar o dia.
- **Perder não custa nada**: sem blackout de verdade, sem perder dinheiro, sem
  trancar o portal. O jogador sai, pode curar e **entra de novo no portal**,
  quantas vezes quiser no mesmo dia.
- **O progresso do dia fica.** Ao voltar, o jogador **anda desde a primeira
  sala**, mas **não luta de novo** com quem já venceu: os teleportes que ele
  escolheu continuam os mesmos e os que ele descartou continuam desativados. A
  primeira luta de verdade é a do treinador que o derrotou (ou o próximo, se
  ele saiu por conta própria).
- **No código:** flags do bloco `DAILY` (`include/constants/flags.h`,
  `DAILY_FLAGS_START`) zeram na virada do dia. A fenda do altar deixou de
  ser "uma vez por dia" (27/09/2026): fica aberta e é a entrada do Nexus. Derrota sem penalidade → skill `batalha-sem-blackout`
  (`B_FLAG_NO_WHITEOUT`). Nova flag → skills `alocar-flag` e
  `catalogar-flags`.

## R4. Modos de jogo — só o Daily agora

O rift pode oferecer modos diferentes. **Implementar agora só o Daily.** Os
outros ficam registrados como ideia futura e **não** devem ser implementados
nem ter estrutura preparada sem pedido do autor.

| Modo | Regra | Status |
|---|---|---|
| **Daily** | dungeon reseta todo dia; no mesmo dia pode tentar quantas vezes quiser; perder não custa nada e quem já foi vencido não luta de novo | **foco atual** |
| Gauntlet | perdeu, é expulso e recomeça do começo | ideia futura |
| Infinito | segue enquanto não perder | ideia futura |

## R5. Estrutura do Daily

1. **4 treinadores sorteados**
2. **1 "Campeão" do lendário** sorteado — o treinador associado ao lendário da
   vez (fichas do Nexus, seção "Lendário associado")
3. **Boss battle contra o lendário** sorteado; na vitória o jogador leva um
   fragmento dele, no nível 1 e na primeira forma (R17)

"As 5 lutas" = os 4 treinadores + o campeão. O boss vem depois.

### Sala e escolha de caminho (R5.1)

Cada sala tem **3 teleportes**. Cada teleporte recebe um treinador sorteado.
Quando o jogador entra em um, os outros dois **se desativam**. A ideia é o
jogador **escolher entre 3 treinadores** a cada passo e montar o próprio
caminho.

### Vida entre lutas (R5.2)

**Não há cura entre as lutas.** Dentro de uma tentativa, o HP e o PP que
sobraram de uma luta vão para a próxima. Para recuperar, o jogador **sai** do
Nexus — e ao voltar anda pelas salas já vencidas sem lutar (R3). Sair é,
portanto, a forma de curar sem perder progresso.

## R6. Boss final

A luta com o lendário é **boss battle** (`setbossbattle` / macros
`bosslegendaryencounter*`, barras + multiplicador + perfil de fase). O boss
segue o R2 de nível. O que o jogador leva no fim segue o R17 (nível 1, primeira
forma).

## R7. Loop infinito, com repetição

Lendários e treinadores **podem aparecer N vezes**. Não há filtro de "já
enfrentado" nem de "já capturado" (a única restrição de pool é a R1). Levar de novo o
fragmento do mesmo lendário (R17) é permitido — serve para caçar IV melhor.

## R8. Lendário do Nexus: 3 IVs perfeitos

O fragmento que o jogador leva (R17) vem com **3 IVs perfeitos garantidos** — o padrão do jogo
(`LEGENDARY_PERFECT_IV_COUNT 3`, `include/constants/pokemon.h`, campo
`perfectIVCount` da espécie). O número vem do **boss**, não da primeira forma:
um fragmento de Naganadel (Poipole) tem os mesmos 3 IVs garantidos. Como o lendário pode ser recapturado sem limite
(R7), caçar IV melhor é repetir o Nexus, não aumentar o piso.

## R9. Prêmio de quem vence tudo

Vencer as 5 lutas e **levar o fragmento** do lendário (R17) dá **um item
prêmio**, que o jogador encontra no fim. O lendário em si **nunca** é
capturado: nocauteá-lo deixa o fragmento, e é o fragmento preso numa bola que
conclui o dia (revisão de 27/09/2026 — substitui "capturar na batalha" e
"nocautear e ele se rende").

Logo depois do prêmio, **a dimensão desmorona e expulsa o jogador** de volta
ao Altar — é o final do dia. Bolsa cheia deixa a Poké Ball do prêmio no chão:
voltando no mesmo dia, a sala final quieta ainda a oferece.

Candidatos (já existem no jogo):

| Categoria | Itens | O que faz aqui |
|---|---|---|
| **Mints** | `ITEM_LONELY_MINT` … `ITEM_SERIOUS_MINT` (21, `include/constants/items.h`) | trocam a Nature efetiva |
| **Feathers** (repropostas neste hack) | Health, Muscle, Resist, Genius, Clever, Swift Feather | **+5 IV** permanente no stat (HP, Atk, Def, SpA, SpD, Spe) até 31 — `src/pokemon.c`, `ITEM10_IVS_ALL` |
| **TMs sorteados** | tabela de TMs | TMs vão ficar raros no jogo (R14); o Nexus é uma das fontes |

- Os **Herbs** (Withered, Grimy, Brittle, Goopy, Dull, Soggy) fazem o
  contrário: **baixam** IV. Não são prêmio de "melhorar", mas podem servir
  para ajuste fino (IV 0 de Speed para Trick Room).
- **Bottle Cap / Gold Bottle Cap** estão com `ItemUseOutOfBattle_CannotUse` —
  hoje não fazem nada. Não oferecer como prêmio sem implementar.
- Prêmio entregue por script → checar espaço na bolsa **antes** (padrão
  `checkitemspace` das skills).

## R10. Formato **Traditional** — jogador **e** treinadores

O Nexus usa o formato **Traditional** (outros formatos podem vir depois; o
Nexus segue sempre o formato escolhido). Ele vale para o **time do jogador**,
conferido na entrada do portal, **e** para **todo treinador** do Nexus:

| Vaga | Máximo |
|---|---|
| Pokémon no time | 6 |
| **Lendário** | 1 |
| **Semi-lendário** | 1 |
| **Mega** | 1 |

A regra antiga de "Uber = BST ≥ 600" **foi abandonada**: ela pegava casos como
Slaking, que não é lendário. Pseudo-lendários (Dragonite, Tyranitar,
Garchomp, Dragapult…) e Slaking são **Pokémon comuns** aqui.

**Quem é o quê** (pelas flags da espécie em `src/data/pokemon/species_info/`):

| Categoria | Flag no engine | Exemplos |
|---|---|---|
| **Lendário** | `isRestrictedLegendary` | Mewtwo, Lugia, Kyogre, Dialga, Zacian, Koraidon, Cosmog/Solgaleo, Necrozma |
| **Semi-lendário** | `isSubLegendary` | aves, cães, Regis, Lati@s, Heatran, Tapus, Type: Null/Silvally, Urshifu, Ogerpon |
| **Semi-lendário** | `isUltraBeast` | Buzzwole, Kartana, Poipole/Naganadel, Stakataka… |
| **Semi-lendário** | `isParadox` | Flutter Mane, Iron Valiant, Walking Wake, Raging Bolt… |
| **Mítico** | `isMythical` | **um a um**, pela tabela abaixo |

### Míticos: lendário ou semi-lendário

Decisão do autor: **depende do peso do Pokémon**. A tabela abaixo está
**fechada** (26/09/2026). O BST **não** serve de régua aqui: quase todo
mítico tem BST 600 (Mew e Darkrai inclusive). A régua usada é o **nível de
poder competitivo** (quem historicamente é "Uber" nos jogos oficiais conta
como lendário).

| Mítico | BST | Vaga | Status |
|---|---|---|---|
| Arceus | 720 | **Lendário** | decidido |
| Darkrai | 600 | **Lendário** | decidido |
| Mew | 600 | Semi-lendário | decidido |
| Deoxys (todas as formas) | 600 | Lendário | decidido |
| Hoopa (Unbound 680) | 600/680 | Lendário | decidido |
| Genesect | 600 | Lendário | decidido |
| Magearna (e Original) | 600 | Lendário | decidido |
| Marshadow | 600 | Lendário | decidido |
| Shaymin (Land e Sky) | 600 | Semi-lendário | decidido |
| Celebi | 600 | Semi-lendário | decidido |
| Jirachi | 600 | Semi-lendário | decidido |
| Manaphy | 600 | Semi-lendário | decidido |
| Phione | 480 | Semi-lendário | decidido |
| Victini | 600 | Semi-lendário | decidido |
| Keldeo | 580 | Semi-lendário | decidido |
| Meloetta | 600 | Semi-lendário | decidido |
| Diancie | 600 | Semi-lendário | decidido |
| Volcanion | 600 | Semi-lendário | decidido |
| Zeraora | 600 | Semi-lendário | decidido |
| Meltan / Melmetal | 300/600 | Semi-lendário | decidido |
| Zarude | 600 | Semi-lendário | decidido |
| Pecharunt | 600 | Semi-lendário | decidido |

Mítico novo no jogo → entra nesta tabela antes de aparecer num time.

- **A Mega de um lendário ou semi-lendário ocupa as duas vagas**: a da
  categoria **e** a de Mega. Exemplos do autor: **Mewtwo com Mewtwonite X ou Y** =
  vaga de lendário + vaga de Mega; **Diancie com Diancite** = vaga de
  semi-lendário + vaga de Mega. O mesmo vale para Mega Rayquaza, Mega Latios,
  Mega Heatran, Mega Darkrai, Mega Zeraora, Mega Magearna e qualquer outra.
  Nesse time não cabe outra Mega nem outro Pokémon da mesma categoria.
- Primal (Kyogre/Groudon) conta como a vaga de **Mega**.

### Singles ou Doubles

É uma **opção do jogo inteiro**: o jogador escolhe se joga a campanha toda em
Singles ou em Doubles, e o Nexus segue essa escolha. Consequência para os
times: **todo time do Nexus precisa funcionar nos dois**.

- **No código:** a opção **existe** — **Battle Format** no menu de opções
  (`src/option_menu.c`) e na tela de opções do New Game, com três valores:
  **Default** (cada treinador usa o formato com que foi escrito), **Singles** e
  **Doubles**.
  - Guardada nas flags `FLAG_REPLAY_BATTLE_FORMAT_DOUBLES` / `_SINGLES`
    (`0x937`/`0x938`, `include/constants/flags.h`); lida por
    `GetReplayBattleFormat()` (`src/replay_options.c`).
  - Aplicada em `src/battle_setup.c` (`ShouldForceReplayTrainerDoubles` e a
    montagem do tipo de batalha) e em `src/trainer_see.c`.
  - **Não força Doubles** quando: vários treinadores avistam juntos, há
    parceiro seguindo o jogador, Battle Pyramid/Trainer Hill, o jogador tem
    menos de 2 Pokémon utilizáveis, ou o time do treinador tem menos de 2.
    Batalha selvagem, de facility, com parceiro ou multi mantém o próprio
    formato.
- **Consequências para o Nexus:**
  - As lutas de treinador precisam passar pelo caminho **normal** de
    `trainerbattle` para herdar a opção. Se o Nexus for montado como
    "facility" (estilo Frontier), a opção deixa de valer — evitar.
  - Com a opção em **Default**, vale o `Double Battle:` do `trainers.party`
    de cada treinador do Nexus; escolha o formato em que o time brilha mais,
    mas o time continua tendo que funcionar no outro.
  - O **boss lendário** é batalha selvagem: fica no formato próprio dele
    (hoje 1 contra 1), independente da opção.

## R11. Todo treinador do Nexus usa as três vagas

- Todo time de treinador tem **1 lendário, 1 semi-lendário e 1 Mega** (e mais
  três Pokémon comuns, ou menos se o lendário/semi-lendário for o Mega).
- Se não houver uma Mega que combine com o personagem, **proponha ao autor uma
  Mega custom** que faça sentido (o hack já tem Megas próprias, ex.: a
  `Steeltite` do Steven). Só sem Mega possível a vaga fica vazia — nunca vira
  um segundo lendário.
- Mega em treinador = Pokémon segurando a pedra certa no `trainers.party`.

## R12. Times com sinergia

Os times precisam ter **sinergia e ser interessantes**: um plano (clima,
Trick Room, hazards, pivot, dupla que se cobre em Doubles), a cara do
personagem e um motivo para o lendário, o semi-lendário e a Mega estarem ali.
Não é uma lista de seis Pokémon fortes. Como a batalha pode ser Singles ou
Doubles (R10), o plano precisa sobreviver aos dois.

## R13. Times no máximo: 31 IV e 252 EV em tudo

Todo Pokémon de treinador do Nexus tem **31 em todos os IVs** e **252 em todos
os EVs**:

```
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
```

- **No código:** isso é válido neste hack — `MAX_TOTAL_EVS` está em **1512**
  (`include/constants/pokemon.h`), então 6×252 não é cortado.
- Nature, item, habilidade e os 4 golpes são sempre escritos à mão (sem golpe
  escrito, o engine põe o set de level-up).

## R14. Direção de design do jogo: breeding em primeiro lugar

Decisão **futura** do autor, que já orienta o Nexus: o jogo vai **valorizar o
breeding**. Para isso serão restringidos, no resto do jogo:

- tudo que dá **EV** e **IV** (vitaminas, Feathers, Bottle Caps…);
- **Poké Balls**;
- **TMs** — a ideia é valer mais breedar para o filhote nascer com o golpe do
  que usar TM.

Para o Nexus isso significa: os prêmios (R9) — **Feathers (+IV), Mints e TMs** —
ficam **mais valiosos**, porque serão fontes raras. **Não implementar** essas
restrições sem pedido do autor; é só para não desenhar nada no Nexus que vá
contra elas (ex.: não dar Poké Ball em quantidade como prêmio).

## R15. Estado do Daily: uma variável só, sorteio pela semente do dia

O que o jogador **fez** no dia cabe numa única var de 16 bits (nome sugerido
`VAR_NEXUS_DAILY`). O que o jogo **sorteou** não é guardado: é recalculado.

| Bits | Guarda | Valores |
|---|---|---|
| 0–1 | teleporte escolhido na sala 1 | 0, 1, 2; 3 = ainda não escolheu |
| 2–3 | sala 2 | idem |
| 4–5 | sala 3 | idem |
| 6–7 | sala 4 | idem |
| 8–10 | progresso | 0–5 = lutas vencidas (4 treinadores + campeão); 6 = lendário nocauteado, fragmento esperando; 7 = fragmento levado (R17) |
| 11 | prêmio do R9 já entregue hoje | 0/1 |
| 12 | presente extra pós-boss já entregue hoje (`afterBossScript`; drops do R22 desde 28/09) | 0/1 |
| 13–15 | sala onde o jogador está (0–5), para o load e a volta (acrescentado na implementação, 27/09/2026) | — |

- Ao reentrar (R3), o script lê a var: teleporte escolhido ativo, os outros
  dois desativados, luta pulada enquanto `sala < progresso`. A primeira luta
  de verdade é a da sala `progresso`.
- Os campos se escrevem **na hora** em que acontecem (escolha ao entrar no
  teleporte; progresso logo depois da vitória), nunca só no fim — assim sair
  ou perder no meio não perde nada.
- **Sorteio:** treinador de cada teleporte, lendário e campeão saem de
  `gSaveBlock1Ptr->dailySeed` (`include/global.h`), que o jogo já salva e
  **troca uma vez por dia** em `UpdatePerDay` (`src/clock.c`; o Buenas
  Password já sorteia assim). Mesmo dia → mesmo resultado; dia seguinte →
  resultado novo, sem gastar save. O filtro da R1 (capturado na Pokédex)
  entra depois do sorteio, então o resultado pode mudar no mesmo dia se o
  jogador capturar um lendário fora do Nexus — aceitável.
- **Zerar na virada do dia:** var não zera sozinha. Usar o padrão do Kurt
  (`VAR_KURT_TODAY`, `include/constants/vars.h`): uma flag do bloco `DAILY`
  marca "dia novo"; o script do Nexus, ao encontrá-la limpa, zera a var e liga
  a flag. Tudo no script, sem mexer em C.
- **Onde alocar:** as vars do hack vão até `0x4121` (`VAR_KURT_TODAY`) e o
  bloco termina em `VARS_END = 0x42FF`, então há espaço. A flag diária nova
  segue as skills `alocar-flag` e `catalogar-flags`.

## R16. Falas dos treinadores: genérica e de campeão

Decidido pelo autor em 26/09/2026. Todo treinador do Nexus tem **dois
registros** de fala, na própria ficha:

| Onde aparece | Registro | Sobre o quê |
|---|---|---|
| Uma das **4 primeiras salas** (R5) | **Genérico** (`_Intro`, `_Defeat`) | **Ele mesmo.** Não cita o lugar nem o lendário do dia: serve para qualquer dia. |
| **Campeão**, logo antes do lendário | **Do lendário** (`_ChampionIntro`, `_ChampionDefeat`, `_ChampionAfter`) | **O lendário:** o que o treinador vê nele, pelo olhar de quem é. |

- O nome da espécie não aparece na fala; ela aparece na batalha.
- A relação lendário → campeão fica em [`POOL_LENDARIOS.md`](POOL_LENDARIOS.md).
- **No código:** cada luta do Nexus é um `TRAINER_NEXUS_*` próprio (flag de
  treinador exclusiva). O jogo está no teto de treinadores (`MAX_TRAINERS_COUNT`
  = 1164), os IDs 1056–1163 não servem (`RECLAIMED_TRAINER_FLAGS`) e subir o
  teto desloca o bloco `SYSTEM_FLAGS`; reaproveitar IDs aposentados abaixo de
  1056 é o caminho mais barato. `_ChampionAfter` usa a plaquinha de fala
  (skill `nomear-falante`), que pede um `SP_NAME_*` por treinador.

## R17. O fim da run: só um fragmento

Decidido pelo autor em 27/09/2026. O Nexus é uma realidade quebrada (R20): o
que se enfrenta no fim é um **conceito**, e conceito não se captura. O jogo
tem que deixar isso **claro** para o jogador.

- **Na batalha o boss não pode ser capturado** (`B_FLAG_NO_CATCHING`; a bola
  diz "Poké Balls cannot be used right now!").
- **Nocauteado, ele se desfaz** e sobra **um fragmento** no lugar dele.
- O fragmento é sempre a **primeira forma** da espécie: Silvally → **Type:
  Null**, Naganadel → **Poipole**, forma de batalha → forma base.
  - **Exceção — Deoxys** (autor, 28/09/2026): o fragmento sai numa **Forme
    sorteada** (Normal, Attack, Defense ou Speed). O Meteorite só existe no
    Mt. Chimney, fora da ROM, então o Nexus é a única fonte das outras Formes.
    Código: `sDeoxysFragmentForms` em `src/nexus.c`.
- **Sempre nível 1** — é o começo de algo, não o fim.
- Famílias com pré-evolução (o fragmento é a primeira forma):

| Boss (enfrentado) | Recebido (nível 1) |
|---|---|
| Solgaleo, Lunala | Cosmog |
| Silvally | Type: Null |
| Urshifu (as duas formas) | Kubfu |
| Melmetal | Meltan |
| Manaphy | Phione (neste hack Manaphy evolui de Phione) |
| Naganadel | Poipole (o presente antigo da luta saiu, ver acima) |

  As pré-evoluções **não são boss** do Nexus; só existem como fragmento.
- Para levar o fragmento o jogador usa **uma bola da própria bolsa**, que é
  gasta:
  - **Ultra Beast** → **só Beast Ball**; sem Beast Ball, não leva;
  - **Necrozma** (qualquer forma) também → **só Beast Ball** (autor,
    28/09/2026). No engine ele não é `isUltraBeast`; a exceção vive só em
    `FragmentNeedsBeastBall` e ele continua **Lendário** no sorteio;
  - **qualquer outro** → **qualquer Poké Ball** da bolsa, escolhida pelo
    jogador (abre o bolso de Poké Balls).
  - O fragmento sai **na bola usada**.
- Sem bola que sirva, ou com equipe **e** PC cheios, o fragmento **fica
  esperando** no mesmo dia (nada é gravado nem gasto). Espaço é conferido
  antes da oferta (skill `entregar-pokemon-ou-ovo`).
- Consequência: o Poipole "de presente" na luta do Naganadel (decisão de
  26/09) saiu — o fragmento do Naganadel **já é** um Poipole.

## R18. Looker Files: o caderno do campeão

Decidido pelo autor em 27/09/2026. Cada lendário tem um **Looker File**: um
**caderno no chão** que só aparece **na sala do campeão**, no dia em que
aquele personagem é o campeão. Ele **descreve o universo** de onde o lendário
vem (a seção "O fragmento" da ficha do campeão).

- O Looker nunca esteve no Nexus, mas a letra é dele, a tinta está molhada e a
  página tem a data de um dia que ainda não chegou (R20).
- É texto escrito: narração, **sem plaquinha**.
- Lendário sem Looker File = sem caderno naquele dia.

## R19. Boss sempre na forma superior

Decidido pelo autor em 27/09/2026. Se o lendário tem **forma superior**, o
boss é **sempre** ela: nunca Mewtwo, sempre **Mega Mewtwo** — e **qual** das
formas (X ou Y) é **sorteado** no dia.

- Conta como superior: **Mega** (pedra ou golpe), **Primal**, **Ultra
  Burst** e **fusões** (autor, 27/09/2026), seguidas até dois passos.
- Fusão só vale para quem funde: Kyurem → Black/White, Necrozma → Dusk
  Mane/Dawn Wings, Calyrex → Ice/Shadow Rider. Os parceiros (Reshiram,
  Zekrom, Solgaleo, Lunala, Glastrier, Spectrier) não têm forma superior.
- Dois passos: Necrozma → Dusk Mane ou Dawn Wings (sorteado) → **Ultra
  Necrozma**.
- O fragmento (R17) continua sendo a primeira forma: Mega Mewtwo X → Mewtwo,
  Kyurem White → Kyurem, Ultra Necrozma → Necrozma.
- O sprite no mapa é a forma superior só se ela tiver sprite de overworld;
  senão, a forma base.

## R20. O tom do Nexus

Decidido pelo autor em 27/09/2026. O Nexus é uma **realidade meio quebrada**,
**solta no tempo, no espaço e na dimensão** — algo **conceitual e estranho**.
Todo texto, cena e ideia nova do Nexus parte daí: coisas fora de ordem,
datas que não batem, lugares lembrados em vez de visitados, o lendário como
ideia e não como bicho. Não é uma dungeon comum com cara de sci-fi.

## R21. Ninguém no Nexus é da realidade do jogador

Decidido pelo autor em 27/09/2026. Todo treinador que aparece nas salas ou como
campeão vem de **outro fragmento**: outro universo, outro tempo, outra
dimensão. **Nunca** é a pessoa que o jogador conhece da campanha, nem o elenco
que mora no altar (Looker, Anabel, Lusamine, Kukui, Lillie, Gladion).

- Pode ter acontecido **nada** ou **tudo** do que o jogador viveu com aquela
  pessoa. A fala pode brincar com isso (uma Lillie cujo Cosmog virou o Lunala
  dela; uma Anabel que jogou a Beast Ball no Necrozma), mas não pode depender
  de o jogador ser lembrado.
- É isso que explica time e lendário "impossíveis" na campanha (Gladion com
  Necrozma, Anabel com Necrozma, Lillie com Lunala): naquele fragmento a
  história foi outra.
- O Looker e a Anabel **do altar** continuam sendo os da campanha; eles não
  lutam no Nexus.

## R22. Drops de item de forma

Decidido pelo autor em 28/09/2026. Alguns lendários do Nexus deixam, além do
fragmento, o **item que troca a forma** deles — itens que nada mais no jogo
entrega (inventário em [`../../evolucoes.md`](../../evolucoes.md)):

| Boss | Drop | Quando |
|---|---|---|
| Kyurem | DNA Splicers | enquanto o jogador não tiver |
| Genesect | um Drive que o jogador ainda não tem (sorteado) | 1 por dia; nada quando tiver os 4 |
| Zygarde | Zygarde Cube | uma vez |
| Calyrex | Reins of Unity | enquanto o jogador não tiver |

- É o `afterBossScript` (bit 12 do R15): roda depois do fragmento e de novo
  na volta ao dia concluído. Bolsa cheia não grava nada — volta no mesmo dia.
- Narração, sem plaquinha (R20). O DNA Splicers está aqui **provisoriamente**:
  o autor quer um lugar certo para ele no futuro.
- Não é o prêmio do R9: o prêmio continua sendo um só, sorteado.

## Checklist rápido para um time do Nexus

- [ ] 6 Pokémon
- [ ] 1 lendário, 1 semi-lendário e 1 Mega (pedra certa segurada) — Mega custom proposta se nenhuma servir
- [ ] nenhum Pokémon comum "contando" como lendário (pseudo-lendário e Slaking são comuns)
- [ ] plano que funciona em Singles **e** em Doubles
- [ ] 31 IV e 252 EV em todos os stats
- [ ] Nature, item, habilidade e 4 golpes escritos
- [ ] plano de jogo claro (R12) e cara do personagem
- [ ] scaling `PARTY_HIGHEST` (R2)
- [ ] falas genérica e de campeão na ficha (R16)
- [ ] ficha do treinador atualizada (`nexus/<região>/<treinador>.md`)

## Pontos a confirmar com o autor

Nenhum em aberto.

## Decisões já tomadas (histórico)

- 28/09/2026 — **drops de item de forma** (R22: DNA Splicers do Kyurem, Drives
  do Genesect, Zygarde Cube do Zygarde; Reins of Unity do Calyrex em 29/09) e **fragmento do Deoxys em Forme
  sorteada** (exceção do R17).

- 27/09/2026 (revisão 3) — o lendário **nunca** é capturado: nocauteado,
  deixa um **fragmento** (primeira forma, nível 1) que se leva com uma bola da
  bolsa, Beast Ball obrigatória para UB (R17); o Poipole de presente saiu;
  **Looker Files** como caderno na sala do campeão (R18); boss sempre na
  **forma superior**, com sorteio entre elas (R19); o **tom** do lugar (R20).

- 26/09/2026 — "Uber = BST ≥ 600" substituído por **1 lendário + 1
  semi-lendário + 1 Mega**, para jogador e treinadores.
- 26/09/2026 — Singles/Doubles é **opção do jogo inteiro**, escolhida pelo
  jogador — é a opção **Battle Format** que já existe (Default/Singles/Doubles).
- 26/09/2026 — o **jogador** também segue o Traditional.
- 26/09/2026 — derrota no Daily **não custa nada**.
- 26/09/2026 — lendário do boss com **3 IVs perfeitos**.
- 26/09/2026 — Ultra Beasts e Paradoxos são **semi-lendários**; míticos são
  classificados um a um (Mew semi; Darkrai e Arceus lendários).
- 26/09/2026 — depois de perder no Daily o jogador anda desde a primeira sala,
  mas **não luta** com quem já venceu.
- 26/09/2026 — restrição de EV/IV, Poké Balls e TMs é **direção futura** (R14).
- 26/09/2026 — tabela dos míticos **fechada**: Shaymin semi-lendário; o resto
  como estava proposto.
- 26/09/2026 — Mega de lendário/semi-lendário ocupa **as duas vagas**
  (Mewtwo + Mewtwonite X/Y = lendário + Mega; Diancie + Diancite = semi + Mega).
- 26/09/2026 — estado do Daily numa var só; sorteio pela `dailySeed`; zera
  pelo padrão do Kurt (R15).
- 26/09/2026 — **Poipole sai do pool**: não tem dia próprio; o jogador ganha
  um Poipole na luta do Naganadel (bit 12 do R15).
- 26/09/2026 — dois registros de fala: genérico nas 4 salas, sobre o lendário
  no campeão (R16).
- 27/09/2026 (feedback do primeiro teste em runtime) —
  - **nocautear o boss também ganha o lendário** (ele se rende, Beast Ball,
    nível do boss); só fugir/perder deixa o dia em aberto (R9);
  - o dia termina com **a dimensão desmoronando e expulsando o jogador**
    (tremor + flashes + warp para o Altar), logo depois do prêmio (R9);
  - **narração de sala removida**: as regras do Nexus são explicadas **uma
    única vez por save**, na primeira chegada (`FLAG_NEXUS_RULES_EXPLAINED`);
    depois, chegada silenciosa (só a sala do boss ainda fala);
  - **todas as batalhas do Nexus** (treinador, campeão e boss) acontecem no
    **campo Ultra Space** (`MAP_BATTLE_SCENE_ULTRA_SPACE` vence classe de
    treinador e branch de lendário em `src/battle_bg.c`);
  - **portal próprio do Nexus** (`OBJ_EVENT_GFX_NEXUS_PORTAL`, 32x32, 4
    quadros, vórtice violeta com aro dourado) — o anel branco 16x16
    (`OBJ_EVENT_GFX_PORTAL`) não aparece mais lá;
  - **sorteio por sala**: cada sala embaralha o pool sem o campeão e sem o
    trio da sala anterior — sala nunca repete pessoa, salas vizinhas nunca
    repetem ninguém, e o "wrap" que devolvia o trio da sala 1 na sala 4
    acabou. R7 continua: com pool pequeno, alguém pode voltar em sala
    não adjacente.
- 27/09/2026 — o lendário que o jogador leva vem **no nível 1** e, se a família
  tem pré-evolução, **na primeira forma** (Cosmog, Type: Null, Kubfu, Meltan,
  Phione, Poipole): é um fragmento da criatura enfrentada (R17; detalhado na revisão 3).
- 27/09/2026 — os treinadores do Nexus **nunca** são os da realidade do jogador
  nem o elenco do altar: vêm de outros fragmentos (R21).
