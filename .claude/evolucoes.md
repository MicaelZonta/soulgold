# Formas e evoluções — de onde vem cada uma

Inventário das formas alternativas e dos itens de forma do SoulGold. Existe
para duas coisas: saber **onde** cada forma se consegue hoje, e lembrar quais
fontes são **provisórias** e ainda esperam um lugar ou evento definitivo.

Atualizado em 28/09/2026. Ao mudar uma fonte, mude aqui, rode o site
(`~/.venvs/soulgold-docs/bin/python tools/soulgold_docs/build_docs.py`) e
confira que a forma não voltou a aparecer "sem fonte".

## Princípio: toda espécie precisa de uma fonte legítima no mundo

Decisão do autor (29/09/2026): **todo Pokémon — e toda forma — deve ter uma
fonte "de verdade"** no mundo do jogo: encontro selvagem, evento de história,
presente de NPC, troca, fóssil, loja comum. Fontes de **sistema** não bastam
sozinhas: **Nexus**, **Gachapon**, **troféus** (Route 40), **Battle Cafe**,
**Game Corner**, **Odd Egg** e afins. Elas podem continuar existindo, mas
como fonte extra, nunca a única.

Hoje muita coisa só vem dessas fontes. A lista viva sai de:

```bash
~/.venvs/soulgold-docs/bin/python tools/soulgold_docs/build_docs.py
python3 dev_scripts/fontes_legitimas.py
```

Contam como legítimos, além do óbvio: **ser Pokémon inicial** (todas as
gerações — a fonte deles é serem iniciais) e **roamer** (Raikou, Entei e
Suicune vagam por Johto desde a Burned Tower, nível 40; os covis de Hoenn deles
estão fora da ROM).

Retrato de 29/09/2026 (famílias, pela forma de nome mais curto):

| Só vem de | Quantas | Quem |
|---|---|---|
| Nexus | 49 | UBs (Nihilego, Buzzwole, Pheromosa, Xurkitree, Celesteela, Kartana, Guzzlord, Stakataka, Blacephalon), Celebi, Heatran, Regieleki, Regidrago, Reshiram, Zekrom, Kyurem, Keldeo, Xerneas, Yveltal, Zygarde, Volcanion, Zacian, Zamazenta, Eternatus, Calyrex/Glastrier/Spectrier, Deoxys, Chi-Yu, Ting-Lu e Wo-Chien, Okidogi e Munkidori (Loyal Three), Pecharunt, Terapagos — e as formas por item que só o Nexus dá (Drives do Genesect, DNA Splicers, Reins of Unity, Zygarde Cube) |
| Gachapon | 12 | Togepi, Cleffa, Sentret, Lotad, Seedot, Remoraid, Spinda, Castform, Relicanth, Clamperl/Huntail, Pichu Spiky-eared, Gimmighoul Roaming |
| Battle Cafe (e Nexus) | 18 | Tapus, aves de Galar, Koraidon, Miraidon, o quarteto das Forças da Natureza (Incarnate e Therian), Diancie |
| Troféus (Route 40) | 5 | Floette Eternal, Greninja (Battle Bond), Magearna Original, Poipole, Zarude |
| Game Corner + Gachapon | 1 | Porygon |
| **Nada** | — | **Keldeo Resolute** (depende de aprender Secret Sword) — o resto da lista "nada" são formas só de batalha |

Ao criar evento, rota ou NPC novo, olhe esta tabela: é o estoque de espécies
esperando um lugar.

## Pendências do autor (fonte provisória)

| O quê | Fonte hoje | O que o autor quer |
|---|---|---|
| **DNA Splicers** (Kyurem Black/White) | drop do Nexus quando o boss é Kyurem (NEXUS_REGRAS R22) | um **lugar certo** no mundo |
| **Sinistea Antique / Poltchageist Artisan** | colecionadora de chá, casa 3 de Kitakami (¥20.000 cada, Lv 30) | um **evento** no lugar da loja |
| **Gimmighoul Roaming** | Gachapon Great, Rare | "for now" — pode ganhar fonte própria |
| **Pichu Spiky-eared** | Gachapon Basic, Ultra Rare | — |
| **Gigantatite** (a "Mega" das Gmax de 21 espécies: Venusaur, Charizard, Blastoise, Pikachu, Meowth, Gengar, Kingler, Eevee, Garbodor, Melmetal, Orbeetle, Drednaw, Coalossal, Flapple, Appletun, Hatterene, Grimmsnarl, Alcremie, Copperajah, Duraludon, Urshifu Single Strike) | Elm entrega junto com a Bondstone (`NewBarkTown_Lab_GiveStarterMega`, depois do Mega Ring). Save que já passou dessa cena não recebe | **repensar no futuro**: ideia do autor (29/09/2026) é uma **GMAX Adventure com o Leon**, provavelmente a fonte definitiva da Gigantatite |

## Itens de forma

| Item | Forma | Fonte | Onde está no código |
|---|---|---|---|
| Memories (17) | Silvally de cada tipo | revanche semanal do Gladion em Cianwood (ter/qua/sáb, estado ≥ 16): cada vitória dá uma Memory que o jogador ainda não tem, sorteada | `CianwoodCity_EventScript_PostGladionMemory` |
| Drives (4) | Genesect Douse/Shock/Burn/Chill | Nexus, boss Genesect: um Drive que falta, 1 por dia | `Nexus_EventScript_Genesect_AfterBoss` |
| DNA Splicers | Kyurem Black/White | Nexus, boss Kyurem (**provisório**) | `Nexus_EventScript_Kyurem_AfterBoss` |
| Zygarde Cube | Zygarde 10% / Power Construct | Nexus, boss Zygarde, uma vez | `Nexus_EventScript_Zygarde_AfterBoss` |
| N-Solarizer / N-Lunarizer | Necrozma Dusk Mane / Dawn Wings | revanche diária da Lusamine no Altar (seg/qua/sáb): 1ª vitória dá o Solarizer, a seguinte o Lunarizer, cada um com fala própria | `SunMoonAltar_EventScript_LusamineFusionItem` |
| Reins of Unity | Calyrex Ice/Shadow Rider (fundindo com Glastrier/Spectrier, que também vêm do Nexus) | Nexus, boss Calyrex, enquanto não tiver | `Nexus_EventScript_Calyrex_AfterBoss` |
| Meteorite | Deoxys Attack/Defense/Speed | **fora da ROM** (Mt. Chimney). As Formes vêm do fragmento do Nexus, sorteadas | `sDeoxysFragmentForms`, `src/nexus.c` |
| Nectars (4) | Oricorio Baile/Pom-Pom/Pa'u/Sensu | loja de Olivine City | `OlivineCity/scripts.inc` |
| Máscaras (3) | Ogerpon Wellspring/Hearthflame/Cornerstone | Kitakami Temple Storage | `Kitakami_Temple_Storage` |
| Chipped Pot / Cracked Pot | Polteageist Antique / Phony | portão da Safari Zone | `SafariZoneGate` |
| Masterpiece / Unremarkable Teacup | Sinistcha Masterpiece / Unremarkable | loja de Olivine City | `OlivineCity/scripts.inc` |

O sorteio "um item da faixa que o jogador ainda não tem (bolsa ou PC)" é o
special `GetRandomMissingItemInRange` (`src/field_specials.c`):
`VAR_0x8004` = primeiro item, `VAR_0x8005` = quantos, `VAR_RESULT` = item ou
`ITEM_NONE`. Serve para qualquer faixa contínua de itens.

> ⚠ Neste hack o Sinistea **comum** evolui com Chipped Pot para o
> Polteageist **Antique**, e o Poltchageist comum com Masterpiece Teacup para o
> Sinistcha **Masterpiece** (`gen_8_families.h`, `gen_9_families.h`). As
> formas raras de **base** só vêm da colecionadora de Kitakami.

## Formas sorteadas no encontro selvagem

`GetWildFormVariantSpecies` (`src/wild_encounter.c`): o slot da tabela
selvagem guarda **uma** forma e o encontro sorteia qualquer uma do grupo.

| Slot na tabela | Sorteia |
|---|---|
| Minior Meteor Red | as 7 cores |
| Pumpkaboo Average | os 4 tamanhos (Gourgeist herda) |
| Scatterbug Fancy | os 20 padrões (Spewpa/Vivillon herdam) |
| Squawkabilly Green | Green/Blue/Yellow/White |
| Tatsugiri (Curly) | Curly/Droopy/Stretchy |

## Troca de forma sem item

| Forma | Como |
|---|---|
| Furfrou (cortes) | tosa da Mom, New Bark Town (`sMomFurfrouTrimOrder`, destrava com `VAR_MOM_FURFROU_EXP`) |
| Pikachu (6 Cosplay + 8 bonés) | tosa da Mom com o **Pikachu Cosplay Kit** (`sMomPikachuCostumes`, `ApplyPikachuCostume`). Sem o kit, a Mom tosa e manda o jogador ao Rocker do 3º andar da Goldenrod Dept. Store, que vende o kit (¥100.000) a qualquer hora. "No costume" volta a Pikachu normal. A Pikachu Starter fica de fora. Como follower, a fantasia aparece com o sprite da Pikachu normal (não tem sprite de overworld próprio) |
| Deerling/Sawsbuck (estações) | perfume da Mom, depois da missão do Seasonal Perfume (`sMomDeerlingSeasonalForms`) |
| Burmy Sandy/Trash | depois de batalhar em caverna/areia ou em construção (Wormadam segue o manto) |
| Rotom (aparelhos) | porão do Goldenrod Apartment |
| Castform, Cherrim, Cramorant, Palafin Hero, Minior Core, Xerneas Active | só em batalha — não são buraco |
