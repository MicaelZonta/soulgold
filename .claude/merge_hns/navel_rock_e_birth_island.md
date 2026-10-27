# Navel Rock e Birth Island — as duas últimas casas de lendário

Rodada de 25/10/2026. Duas ilhas do Emerald/FRLG que estavam na pasta mas
**fora da ROM** entraram, e com elas as duas últimas espécies ativas sem
nenhuma fonte no mundo: **Deoxys** e **Volcanion**. As duas ganharam história,
não só `seteventmon`.

Ambas estão em `gMapGroup_SpecialArea` e se entra pelo
`VermilionCity_PortInside`. Falas escritas pelo gpt-6-sol via Codex, com
briefing de personalidade por personagem; andaime, coordenadas e estado meus.

## Birth Island / Deoxys

| Peça | Onde |
|---|---|
| Boss Lv70, 3 barras | `data/maps/BirthIsland_Exterior/scripts.inc` (`setbossbattle 3` + `seteventmon`, puzzle do triângulo intacto) |
| Gatilho narrativo | chuva de meteoros no `VermilionCity_PortOutside` (`data/scripts/meteor_shower.inc`): `FLAG_IS_KANTO_CHAMPION` + ser **noite** + não ter visto |
| Bilhete | Aurora Ticket com a mulher de Olivine (`data/scripts/gift_aurora_ticket.inc`) — ela **não** entrega antes da chuva: a carta náutica ainda não foi corrigida, então ela não tem do que falar |
| Hora no script | `special GetTimeOfDayForScript` + `SCRIPT_TIME_*` em `#define` (enum de C o assembler não vê) |
| Meteorite | `finditem` na cratera (`data/scripts/birth_island_residents.inc`) — primeira fonte na ROM das Formes de Deoxys |
| Moradores | Colress e Soliera, com agenda de **dia e hora** (`src/data/npc_schedule.h`) |

O portão de progresso não mudou (continua a Liga de Kanto); a chuva só
acrescenta o **quando**. Looker e Anabel aparecem só durante a cena, escondidos
por `FLAG_TEMP_B` e `FLAG_TEMP_C`.

### A armadilha que custou um conserto: flag de resultado como portão de estado

`FLAG_BATTLED_DEOXYS` só é alcançada quando o resultado **não** é vitória nem
fuga. Usá-la como portão deixava quem derrotasse o Deoxys sem capturar com a
ilha presa em modo "cena" para sempre — Colress e Soliera fora da agenda. Quem
manda agora é `VAR_BIRTH_ISLAND_SCENE`, que vai a 2 **logo depois do
`waitstate`**, antes de qualquer `GetBattleOutcome`: vencer, perder, fugir ou
capturar, todos contam.

Regra geral: **estado de mundo nunca sai de flag de resultado de batalha.**
Resultado é um dos quatro ramos; estado é "a cena já aconteceu".

## Navel Rock / Volcanion

Cinco salas novas (`Entrance`, `Shaft`, `FireVent`, `SeaBreach`,
`SteamChamber`) mais `Exterior` e `Harbor`. A geometria é a do Navel Rock
original de propósito: nos jogos antigos o ramo de cima é o Ho-Oh e o de baixo
o Lugia, e aqui os dois já têm casa. A forma fica e o significado muda — em
cima o calor, embaixo o mar, e a criatura onde os dois se encontram.

**O puzzle** (`data/scripts/navel_rock.inc`): só a fenda de fogo e a câmara
assa seca; só a brecha do mar e ela alaga fria; **as duas**, e enche de vapor —
e só então o Volcanion está lá. `FLAG_HIDE_VOLCANION` é recalculada em **todo**
`ON_TRANSITION` da câmara, então nunca é um "já vi" velho; quem segura o
reaparecimento é `FLAG_CAUGHT_VOLCANION`. Perder ou fugir não mexe em nenhuma
das duas, então a luta repete (mesma receita do Keldeo do Mt. Silver).

**A corrente do bilhete** (`data/scripts/navel_rock_quest.inc`,
`VAR_NAVELROCK_QUEST`): quatro pessoas, e nenhuma das quatro sabe o que mora
lá.

| Valor | Quem | Onde |
|---|---|---|
| 0 → 1 | Blaine dá a leitura velha dele | `SeafoamIslands_Gym` |
| 1 → 2 | Bill acha o ritmo de três dias | `GoldenrodCity_BillsHouse` |
| 2 → 3 | Flannery reescreve em tábua de marés | onde ela estiver hoje |
| 3 → 4 | o marinheiro emite o Mystic Ticket | `OneIsland_Harbor_Frlg` |

Quem emite o bilhete é o marinheiro, que é de onde bilhete vem. O Blaine dá a
pergunta, o Bill dá o número, a Flannery dá a tradução, o marinheiro dá o
papel.

## A agenda: `src/data/npc_schedule.h`

Três personagens rodam pelo mundo (`IsScheduledNpcHere`, `VAR_0x8004` =
`SCHEDULED_NPC_*`). Cada mapa anfitrião chama o `*_OnTransition` do personagem
e tem um `object_event` dele escondido por `FLAG_TEMP_*` — flag temporária
zera a cada carregamento de mapa, então a resposta é recalculada em toda
entrada e nenhuma flag persistente é gasta só para esconder.

| Personagem | Flag de ocultação | Casa fixa | Curinga (resto da semana) |
|---|---|---|---|
| Flannery | `FLAG_TEMP_D` | — (não mora em lugar nenhum) | `NewSinjoh_HotSprings` à noite, `CinnabarIsland` / `MtEmber_Exterior_Frlg` / `SeafoamIslands_Gym` de dia |
| Colress | `FLAG_TEMP_B` | `BirthIsland_Exterior` (seg/qua/sex de dia, sáb até a tarde) | `RuinsOfAlph_Lab` |
| Soliera | `FLAG_TEMP_C` | `BirthIsland_Exterior` (ter/qui/sáb à noite) | `OlivineCity_LighthouseTop` |

**Regra do autor:** personagem de agenda tem que estar em **algum** lugar
sempre. A última fatia de cada um é um curinga `SCHED_EVERY_DAY +
SCHED_ANY_TIME`; as 7 × 4 combinações precisam casar com alguma fatia. Quem
acrescentar personagem mantém isso.

## A armadilha que quase apagou a rodada: `.inc` de mapa que tem `.pory`

Três ganchos desta rodada foram escritos à mão no `scripts.inc` de mapas que
têm `scripts.pory` — e o `.inc` desses mapas é **gerado**. O primeiro `make`
depois disso apagou os três sem avisar e sem erro de build:

| Mapa | O que sumiu | Efeito |
|---|---|---|
| `GoldenrodCity_BillsHouse` | o ramo do Navel Rock no Bill | `VAR_NAVELROCK_QUEST` travava em 1 → sem Mystic Ticket → Navel Rock inalcançável |
| `OlivineCity_LighthouseTop` | `call ScheduledNpcs_OnTransition` | Soliera nunca aparecia fora da ilha |
| `RuinsOfAlph_Lab` | `call ScheduledNpcs_OnTransition` | Colress nunca aparecia fora da ilha |

Consertado em 27/10/2026 movendo os três para o `.pory`. Os quatro mapas
anfitriões da Flannery escaparam porque nenhum deles tem `.pory`.

Para conferir o repositório inteiro de uma vez (regenera cada `.inc` num temp e
compara; 227 pares, tem que dar 0 divergentes):

```bash
for p in $(find data -name '*.pory'); do
  inc=${p%.pory}.inc; [ -f "$inc" ] || continue
  t=$(mktemp); tools/poryscript/poryscript -i "$p" -o "$t" \
    -fc tools/poryscript/font_config.json -cc tools/poryscript/command_config.json -lm=false
  diff -q "$inc" "$t" >/dev/null || echo "DIVERGE: $inc"
done
```

## Falhas de design pegas no QA

- As falas de convite terminavam perguntando, mas a batalha começava mesmo para
  quem respondesse que não (`trainerbattle_no_intro` logo depois do `msgbox`,
  sem yes/no). Cinco pontos — Flannery, Colress e Soliera — viraram
  `MSGBOX_YESNO` com saída limpa no não.
- Com a leitura do Bill na mão, a Flannery precisava ser abordada duas vezes: a
  apresentação saía e o beat da corrente só era conferido na conversa seguinte.
  Agora a primeira conversa já cai no beat.
- O sinal da brecha saía de dentro da poça (`NavelRock_SeaBreach`) e foi para a
  parede.

## Catálogos que isso mexeu

- `.claude/rift_missions/nexus/POOL_LENDARIOS.md`: Deoxys e Volcanion saíram de
  "sem método" (⚠️/❌) e entraram em "Com método"; Resumo recontado.
- `.claude/evolucoes.md`: as duas saíram da coluna "só vem do Nexus"; o
  Meteorite deixou de ser "fora da ROM".
- `tools/soulgold_docs/constants.py`: a lista que escondia Kanto inteiro do site
  saiu (ver `kanto_no_site.md`).
