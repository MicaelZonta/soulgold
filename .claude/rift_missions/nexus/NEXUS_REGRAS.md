# Nexus — regras

Regras do autor para o **Nexus** (o loop pós-Necrozma das Rift Missions,
design §10). **Valem para qualquer trabalho no Nexus**: time de treinador,
sorteio, pool de lendários, prêmio, mapa, script. Se uma tarefa pedir algo que
contraria uma regra daqui, pare e pergunte ao autor antes.

Decididas pelo autor em 25/09/2026. As notas "No código" dizem o que já existe
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

## R3. Abre uma vez por dia; perder não tranca

- O Nexus (modo Daily) **abre 1x por dia**: o conteúdo daquele dia — os
  treinadores de cada teleporte, o lendário e o campeão — é **sorteado uma vez
  por dia** e fica igual até virar o dia.
- **Perder não tranca**: o jogador pode entrar de novo quantas vezes quiser no
  mesmo dia.
- **No código:** flags do bloco `DAILY` (`include/constants/flags.h`,
  `DAILY_FLAGS_START`) zeram na virada do dia. A fenda do altar já usa daily
  flag (V24). Nova flag → skills `alocar-flag` e `catalogar-flags`.

## R4. Modos de jogo — só o Daily agora

O rift pode oferecer modos diferentes. **Implementar agora só o Daily.** Os
outros ficam registrados como ideia futura e **não** devem ser implementados
nem ter estrutura preparada sem pedido do autor.

| Modo | Regra | Status |
|---|---|---|
| **Daily** | dungeon reseta todo dia; no mesmo dia pode tentar quantas vezes quiser; **perder não recomeça do primeiro** | **foco atual** |
| Gauntlet | perdeu, é expulso e recomeça do começo | ideia futura |
| Infinito | segue enquanto não perder | ideia futura |

## R5. Estrutura do Daily

1. **4 treinadores sorteados**
2. **1 "Campeão" do lendário** sorteado — o treinador associado ao lendário da
   vez (fichas do Nexus, seção "Lendário associado")
3. **Boss battle contra o lendário** sorteado, com captura possível

"As 5 lutas" = os 4 treinadores + o campeão. O boss vem depois.

### Sala e escolha de caminho (R5.1)

Cada sala tem **3 teleportes**. Cada teleporte recebe um treinador sorteado.
Quando o jogador entra em um, os outros dois **se desativam**. A ideia é o
jogador **escolher entre 3 treinadores** a cada passo e montar o próprio
caminho.

### Vida entre lutas (R5.2)

**Não há cura entre as lutas.** Para recuperar, o jogador **sai** do Nexus.

No Daily, **perder** expulsa o jogador **sem apagar o progresso do dia**: ele
volta e continua da luta onde parou (R4). A frase do autor "ou você perde e
começa do começo" descreve o **Gauntlet**, não o Daily — ver "Pontos a
confirmar".

## R6. Boss final

A luta com o lendário é **boss battle** (`setbossbattle` / macros
`bosslegendaryencounter*`, barras + multiplicador + perfil de fase). O boss
segue o R2 de nível.

## R7. Loop infinito, com repetição

Lendários e treinadores **podem aparecer N vezes**. Não há filtro de "já
enfrentado" nem de "já capturado" (a única restrição de pool é a R1). Capturar
de novo o mesmo lendário é permitido — serve para caçar IV melhor.

## R8. Lendário do Nexus vem com IV alto

Os lendários daqui têm **chance alta de IVs altos** — acima do padrão de
lendário do jogo.

- **No código:** hoje o padrão é `LEGENDARY_PERFECT_IV_COUNT 3`
  (`include/constants/pokemon.h`, campo `perfectIVCount` da espécie). O Nexus
  deve usar um valor próprio maior na criação do boss (por exemplo 4 a 6 IVs
  perfeitos, ou IVs sorteados com piso alto); o número exato fica para a
  implementação.

## R9. Prêmio de quem vence tudo

Vencer as 5 lutas **e** capturar o lendário dá **um item prêmio**, que o
jogador "encontra" no fim. Candidatos (já existem no jogo):

| Categoria | Itens | O que faz aqui |
|---|---|---|
| **Mints** | `ITEM_LONELY_MINT` … `ITEM_SERIOUS_MINT` (21, `include/constants/items.h`) | trocam a Nature efetiva |
| **Feathers** (repropostas neste hack) | Health, Muscle, Resist, Genius, Clever, Swift Feather | **+5 IV** permanente no stat (HP, Atk, Def, SpA, SpD, Spe) até 31 — `src/pokemon.c`, `ITEM10_IVS_ALL` |
| **TMs sorteados** | tabela de TMs | o autor quer TMs mais raros; o Nexus é uma fonte deles |

- Os **Herbs** (Withered, Grimy, Brittle, Goopy, Dull, Soggy) fazem o
  contrário: **baixam** IV. Não são prêmio de "melhorar", mas podem servir
  para ajuste fino (IV 0 de Speed para Trick Room).
- **Bottle Cap / Gold Bottle Cap** estão com `ItemUseOutOfBattle_CannotUse` —
  hoje não fazem nada. Não oferecer como prêmio sem implementar.
- Prêmio entregue por script → checar espaço na bolsa **antes** (padrão
  `checkitemspace` das skills).

## R10. Formato **Traditional**

O Nexus usa o formato **Traditional** (o nome existe porque outros formatos
podem vir depois):

- **6 Pokémon**, como estão
- **no máximo 1 Mega**
- **no máximo 1 Uber**
- batalhas **Singles ou Doubles**

**Uber** = espécie com **BST ≥ 600**. O jogo **não tem** lista de tiers (o
único marcador é `isFrontierBanned`, que pega lendários e míticos). Hoje
passam de 600, fora os lendários: Dragonite, Tyranitar, Slaking, Salamence,
Metagross, Garchomp, Hydreigon, Greninja-Ash, Goodra (e Hisui), Wishiwashi
School, Kommo-o, Archaludon, Dragapult, Palafin Hero e Baxcalibur.

- Conta o **BST da forma base**, não o da Mega. Um Uber que também é o Mega do
  time (Mega Metagross, Mega Garchomp…) ocupa **as duas vagas**.
- **Ponto a confirmar:** vários lendários ficam **abaixo** de 600 (Tapus e UBs
  570, Paradoxos 570–590, Regis e o trio de Johto 580). Pela regra literal eles
  **não** são Uber. Ver "Pontos a confirmar".

## R11. Todo treinador do Nexus segue o Traditional

- Todo time de treinador tem **1 Mega e 1 Uber**.
- **Exceção:** se for impossível achar uma Mega que combine com o personagem,
  troca a Mega por **um segundo Uber** — mas antes **proponha ao autor** uma
  **Mega custom** que faça sentido (o hack já tem Megas próprias, ex.: a
  `Steeltite` do Steven).
- Mega em treinador = Pokémon segurando a pedra certa no `trainers.party`.

## R12. Times com sinergia

Os times precisam ter **sinergia e ser interessantes**: um plano (clima,
Trick Room, hazards, pivot, dupla que se cobre em Doubles), a cara do
personagem e um motivo para o Mega e o Uber estarem ali. Não é uma lista de
seis Pokémon fortes.

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

---

## Checklist rápido para um time do Nexus

- [ ] 6 Pokémon
- [ ] exatamente 1 Mega (pedra certa segurada) — ou 2 Ubers com exceção aprovada
- [ ] exatamente 1 Uber (BST base ≥ 600)
- [ ] Singles ou Doubles definido
- [ ] 31 IV e 252 EV em todos os stats
- [ ] Nature, item, habilidade e 4 golpes escritos
- [ ] plano de jogo claro (R12) e cara do personagem
- [ ] scaling `PARTY_HIGHEST` (R2)
- [ ] ficha do treinador atualizada (`nexus/<região>/<treinador>.md`)

## Pontos a confirmar com o autor

1. **Lendário abaixo de 600 conta como Uber?** Pela regra literal, não
   (Tapu Koko, Flutter Mane, Raikou…). Recomendo contar **todo lendário,
   mítico, Ultra Beast e Paradoxo** como Uber, além do BST ≥ 600 — senão um
   time pode ter 1 Uber de 600 + vários lendários de 570–590.
2. **Singles ou Doubles:** quem escolhe — cada treinador, o sorteio, ou o
   jogador ao entrar?
3. **O jogador também precisa seguir o Traditional** (checado na entrada), ou
   só os treinadores?
4. **Perder no Daily:** confirmado que mantém o progresso do dia e o jogador
   volta de onde parou? (A frase "ou você perde e começa do começo" foi lida
   como regra do Gauntlet.)
5. **TMs como prêmio:** hoje `I_REUSABLE_TMS` é `TRUE` (`include/config/item.h`).
   O plano de "TMs mais raros" muda isso para uso único, ou só torna os TMs
   difíceis de achar?
6. **Quantos IVs perfeitos** no lendário do Nexus (R8)?
