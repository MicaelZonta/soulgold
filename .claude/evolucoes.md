# Formas e evoluções — de onde vem cada uma

Inventário das formas alternativas e dos itens de forma do SoulGold. Existe
para duas coisas: saber **onde** cada forma se consegue hoje, e lembrar quais
fontes são **provisórias** e ainda esperam um lugar ou evento definitivo.

Atualizado em 28/09/2026. Ao mudar uma fonte, mude aqui, rode o site
(`~/.venvs/soulgold-docs/bin/python tools/soulgold_docs/build_docs.py`) e
confira que a forma não voltou a aparecer "sem fonte".

## Pendências do autor (fonte provisória)

| O quê | Fonte hoje | O que o autor quer |
|---|---|---|
| **DNA Splicers** (Kyurem Black/White) | drop do Nexus quando o boss é Kyurem (NEXUS_REGRAS R22) | um **lugar certo** no mundo |
| **Sinistea Antique / Poltchageist Artisan** | colecionadora de chá, casa 3 de Kitakami (¥20.000 cada, Lv 30) | um **evento** no lugar da loja |
| **Gimmighoul Roaming** | Gachapon Great, Rare | "for now" — pode ganhar fonte própria |
| **Pichu Spiky-eared** | Gachapon Basic, Ultra Rare | — |
| **Reins of Unity** (Calyrex Ice/Shadow Rider) | **nenhuma** — as duas Riders não são obteníveis | decidir |

## Itens de forma

| Item | Forma | Fonte | Onde está no código |
|---|---|---|---|
| Memories (17) | Silvally de cada tipo | revanche semanal do Gladion em Cianwood (ter/qua/sáb, estado ≥ 16): cada vitória dá uma Memory que o jogador ainda não tem, sorteada | `CianwoodCity_EventScript_PostGladionMemory` |
| Drives (4) | Genesect Douse/Shock/Burn/Chill | Nexus, boss Genesect: um Drive que falta, 1 por dia | `Nexus_EventScript_Genesect_AfterBoss` |
| DNA Splicers | Kyurem Black/White | Nexus, boss Kyurem (**provisório**) | `Nexus_EventScript_Kyurem_AfterBoss` |
| Zygarde Cube | Zygarde 10% / Power Construct | Nexus, boss Zygarde, uma vez | `Nexus_EventScript_Zygarde_AfterBoss` |
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
| Deerling/Sawsbuck (estações) | perfume da Mom, depois da missão do Seasonal Perfume (`sMomDeerlingSeasonalForms`) |
| Burmy Sandy/Trash | depois de batalhar em caverna/areia ou em construção (Wormadam segue o manto) |
| Rotom (aparelhos) | porão do Goldenrod Apartment |
| Castform, Cherrim, Cramorant, Palafin Hero, Minior Core, Xerneas Active | só em batalha — não são buraco |
