# Fase 6 - Radio do PokeGear (12 estacoes do HnS)

Fonte: `pokehns-expansion-Release-v2.0.6/src/pokenav_radio.c` (+ `data/text/radio_strings.h`).
O `src/pokegear_radio.c` do SoulGold ja era um port; foi expandido, nao substituido.

## Arquivos
- `src/pokegear_radio.c` - novas estacoes, disponibilidade, `CheckRadioStation()`, `IsHoennSoundPlaying()`.
- `include/pokegear_radio.h` - prototipos dos dois acima.
- `src/regions.c` (novo) + `include/regions.h` - `IsMapSectionInKanto`, `IsPlayerInKanto`, `IsPlayerInJohto`.
  O `regions.h` ja existia (stub `GetCurrentRegion() == REGION_HOENN`, usado por pokemon.c/daycare.c); foi mantido e so ganhou prototipos.
- `src/wild_encounter.c` - `TryGetHoennSoundWildMonIndex` (land e water).
- `include/config/songs_enabled.h` - `SONG_MUS_HG_RADIO_JINGLE` 0 -> 1 (Lucky Channel). `MUS_HG_RADIO_ROUTE101` ja era 1; as demais musicas usadas nao estao na lista de desligaveis.
- `src/time_events.c` NAO mexido: o reset diario e `ClearDailyFlags` (faixa DAILY_FLAGS), que ja cobre `FLAG_DAILY_LUCKY_NUMBER_SET` (DAILY_FLAGS_START+3).

## Estacoes e posicoes (escala 0-63)
| pos | estacao | disponibilidade |
|---|---|---|
| 5 | Hoenn Sound | Kanto + FLAG_KANTO_RADIO_GOT |
| 13 | Pokemon Talk (nossa, topicos do Oak) / Pokedex Show de manha | em todo lugar (como antes) |
| 22 | Pokemon Music (Ben) | em todo lugar (como antes) |
| 25 | Lucky Channel | so Johto |
| 32 | Buena's Password | em todo lugar (como antes) |
| 41 | Unown | so Ruins of Alph (como antes) |
| 50 | Places & People | Kanto + FLAG_KANTO_RADIO_GOT |
| 57 | Let's All Sing (Fern) | Kanto + FLAG_KANTO_RADIO_GOT |
| 61 | Poke Flute (so musica) | Kanto + FLAG_KANTO_RADIO_GOT |
| 63 | Evolution (so musica, nome "?????") | !FLAG_HIDE_MAHOGANY_ROCKETS e mapsec Mahogany/Route 43/Lake of Rage |
| - | Rocket | sequestro do Goldenrod (VAR_GOLDENROD_CITY_STATE 6..9, logica nossa) |

Johto = tudo que nao esta em `KANTO_MAPSEC_START..END` (o SoulGold nao tem JOHTO_MAPSEC_*).
Sequestro Rocket nao afeta Unown, Evolution, P&P, Sing, Poke Flute, Hoenn Sound (igual ao HnS); afeta Talk/Dex/Music/Lucky/Buena.

## Conteudo
- Lucky Channel: numero 0-99999 sorteado 1x/dia em VAR_RADIO_LUCKY_ID(_HI), trava em FLAG_DAILY_LUCKY_NUMBER_SET.
- Pokedex Show: sorteia entre as especies capturadas, descricao com quebra por largura em pixels. Sem capturas: linha de aviso (extra nossa).
- Places & People: lugares de Kanto + treinadores aleatorios de `gTrainers` (exclui Champion/E4/Leader/Rival e entradas sem nome).
- Let's All Sing: mesma musica de Pokemon Music (marcha em dia par, ninho em impar), falas da Fern.
- Hoenn Sound: toca um tema Hoenn aleatorio (lista do HnS, sorteado ao sintonizar).
- Textos em ingles com "Pokémon/Pokédex" (estilo do nosso arquivo), nao em CAIXA ALTA como o HnS.
- `RADIO_MAX_LINES` 12 -> 16; linhas montadas em runtime usam `topicLineBuffers[numLines]`.

## Specials
- `CheckRadioStation`: VAR_RESULT 1 se a musica atual e `MUS_HG_RADIO_POKE_FLUTE`, 2 se Hoenn Sound, 0 senao (Snorlax de Vermilion).
  Funciona porque ao sair do radio a musica da estacao continua tocando (so volta ao padrao se estava em silencio).
- `IsHoennSoundPlaying`: musica atual esta na lista Hoenn **e** o jogador esta em Kanto.

## Diferencas do P
- P e um modulo Pokenav com looped tasks; o nosso e a tela propria do PokeGear (mantida).
- Pokemon Talk: mantivemos nossos topicos do Oak (sem o ciclo Mary/Oak por rota nem os "Special Reports" do P). Pendencia opcional.
- Buena: mantivemos o sistema proprio (`buenas_password.c`); nao portamos a tabela de senhas nem `Special_BuenaPasswordShowMultichoice/CheckAnswer/RollReward` do P (nao pedidos).
- Pokemon Music: mantivemos nossas 3 linhas; nao tem "Today's <dia>," do P.
- Taxa Hoenn Sound: P usa 1/10 (`Random() % 10`), nao 5%; mantido o 1/10 do P. Aplicado em land e water; usa `IsPlayerInKanto()` em vez de `GetCurrentRegion() == REGION_HOENN` (nosso `GetCurrentRegion` e stub fixo em Hoenn).
- Evolution usa o flag `FLAG_HIDE_MAHOGANY_ROCKETS` (nosso, 0x30E); confirmar no jogo se o sentido bate com a historia de Mahogany.
- Lucky Channel: nao ha NPC premiando o numero (a Radio Tower do P tambem nao faz parte desta fase).
- `GetKantoSubregion` / `enum KantoSubRegion` do `regions.c` do P NAO foram portados: so o `region_map.c` os usa e esse trecho esta comentado no nosso tree.

## Verificacao
Compilados so os objetos (`pokegear_radio.o`, `regions.o`, `wild_encounter.o`), sem warnings; `tools/check_song_config.py` OK. Nao testado no jogo.
Pendente de teste: sintonizar cada posicao em Kanto/Johto, Snorlax de Vermilion com Poke Flute (pos 61) e encontros com Hoenn Sound.
