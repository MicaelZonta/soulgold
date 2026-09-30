# Auditoria de itens do SoulGold

Catálogo de todos os `ITEM_*` de `include/constants/items.h` cruzados com `gItemsInfo` (`src/data/items.h`) e com toda fonte de obtenção que este levantamento conseguiu achar no repo, para localizar **itens órfãos**: itens que existem na tabela mas que nenhum script/mapa/loja/mecânica do jogo entrega ao jogador.

Gerado por `dev_scripts/item_audit.py` (`python3 dev_scripts/item_audit.py --md`). É levantamento estático (grep + parse de `.h`/`.inc`/`.pory`/`.json`), não substitui testar no jogo — leia o cabeçalho do script para a lista completa de fontes reconhecidas e as limitações conhecidas.

Colunas da tabela:

- **Item** — constante `ITEM_*` e nome em inglês (como aparece no jogo).
- **O que faz** — resumo da `.description` da tabela (texto do jogo, em inglês).
- **Obtível in-game?** — Sim / Não / Verificar (mencionado em script mas sem comando de entrega reconhecido) / Só held item (via Roubo ou Golpe do Dia) / Não (só em mapa fora da campanha, isto é, conteúdo de Hoenn/Emerald que sobrou no repo mas não faz parte da campanha Johto/Kanto do SoulGold).
- **Como se obtém** — toda fonte encontrada, truncada quando há muitos locais.

Itens marcados **★ exclusivo SoulGold** são específicos do romhack (Rift Missions / Nexus / mecânicas próprias) e não existem no pokeemerald-expansion vanilla — são os mais prováveis de estarem esquecidos num evento incompleto.

**Resumo**: 933 itens catalogados — 590 obtíveis, 21 só held item (Roubo/Golpe do Dia), 4 para verificar manualmente, 22 só em mapa fora da campanha, e **296 sem nenhuma fonte encontrada** (candidatos a órfão — ver seção final).

## Poké Balls (28)

| Item | O que faz | Obtível in-game? | Como se obtém |
|---|---|---|---|
| `ITEM_BEAST_BALL` — Beast Ball | A Ball designed to catch Ultra Beasts. | Sim | Script (dado ao jogador): data/maps/AzaleaTown_KurtsHouse/scripts.inc:1558, data/maps/AzaleaTown_KurtsHouse/scripts.pory:779 \| Script (dado ao jogador, var computado): data/maps/AzaleaTown_KurtsHouse/scripts.inc:1246, data/maps/AzaleaTown_KurtsHouse/scripts.pory:623 |
| `ITEM_CHERISH_BALL` — Cherish Ball | A rare Ball made in commemoration of some event. | Sim | Script (dado ao jogador): data/maps/AzaleaTown_KurtsHouse/scripts.inc:1564, data/maps/AzaleaTown_KurtsHouse/scripts.pory:782 \| Script (dado ao jogador, var computado): data/maps/AzaleaTown_KurtsHouse/scripts.inc:1222, data/maps/AzaleaTown_KurtsHouse/scripts.pory:611 |
| `ITEM_DIVE_BALL` — Dive Ball | A Ball that works better on Pokémon on the ocean floor. | Sim | Script (dado ao jogador, var computado): data/maps/AzaleaTown_KurtsHouse/scripts.inc:1158, data/maps/AzaleaTown_KurtsHouse/scripts.pory:579 |
| `ITEM_DREAM_BALL` — Dream Ball | A Ball that works well on sleeping Pokémon. A Poké Ball used in the Entree Forest. | Sim | Script (dado ao jogador): data/maps/AzaleaTown_KurtsHouse/scripts.inc:1528, data/maps/AzaleaTown_KurtsHouse/scripts.pory:764 \| Script (dado ao jogador, var computado): data/maps/AzaleaTown_KurtsHouse/scripts.inc:1214, data/maps/AzaleaTown_KurtsHouse/scripts.pory:607 |
| `ITEM_DUSK_BALL` — Dusk Ball | Works well if used in a dark place. | Sim | Script (dado ao jogador, var computado): data/maps/AzaleaTown_KurtsHouse/scripts.inc:1166, data/maps/AzaleaTown_KurtsHouse/scripts.pory:583 |
| `ITEM_FAST_BALL` — Fast Ball | Works well on very fast Pokémon. | Sim | Script (dado ao jogador): data/maps/AzaleaTown_KurtsHouse/scripts.inc:1516, data/maps/AzaleaTown_KurtsHouse/scripts.inc:240, data/maps/AzaleaTown_KurtsHouse/scripts.pory:120 (+1) \| Script (dado ao jogador, var computado): data/maps/AzaleaTown_KurtsHouse/scripts.inc:1092, data/maps/AzaleaTown_KurtsHouse/scripts.pory:546 |
| `ITEM_FRIEND_BALL` — Friend Ball | A Ball that makes a Pokémon friendly when caught. | Sim | Script (dado ao jogador): data/maps/AzaleaTown_KurtsHouse/scripts.inc:1504, data/maps/AzaleaTown_KurtsHouse/scripts.pory:752 \| Script (dado ao jogador, var computado): data/maps/AzaleaTown_KurtsHouse/scripts.inc:1084, data/maps/AzaleaTown_KurtsHouse/scripts.pory:542 |
| `ITEM_GREAT_BALL` — Great Ball | A good Ball with a higher catch rate than a Poké Ball. | Sim | Loja / pokemart: …F/scripts.inc (LilycoveCity_DepartmentStore_2F), …arborTown_Mart/scripts.inc (FallarborTown_Mart) \| Script (dado ao jogador, var computado): data/maps/AzaleaTown_KurtsHouse/scripts.inc:1036, data/maps/AzaleaTown_KurtsHouse/scripts.pory:518 |
| `ITEM_HEAL_BALL` — Heal Ball | A remedial Ball that restores caught Pokémon. | Sim | Script (dado ao jogador, var computado): data/maps/AzaleaTown_KurtsHouse/scripts.inc:1044, data/maps/AzaleaTown_KurtsHouse/scripts.pory:522 |
| `ITEM_HEAVY_BALL` — Heavy Ball | Works well on very heavy Pokémon. | Sim | Script (dado ao jogador): data/maps/AzaleaTown_KurtsHouse/scripts.inc:1522, data/maps/AzaleaTown_KurtsHouse/scripts.pory:761 \| Script (dado ao jogador, var computado): data/maps/AzaleaTown_KurtsHouse/scripts.inc:1100, data/maps/AzaleaTown_KurtsHouse/scripts.pory:550 |
| `ITEM_LEVEL_BALL` — Level Ball | A Ball that works well on lower level Pokémon. | Sim | Script (dado ao jogador): data/maps/AzaleaTown_KurtsHouse/scripts.inc:1486, data/maps/AzaleaTown_KurtsHouse/scripts.pory:743 \| Script (dado ao jogador, var computado): data/maps/AzaleaTown_KurtsHouse/scripts.inc:1060, data/maps/AzaleaTown_KurtsHouse/scripts.pory:530 |
| `ITEM_LOVE_BALL` — Love Ball | Works well on Pokémon of the opposite gender. | Sim | Script (dado ao jogador): data/maps/AzaleaTown_KurtsHouse/scripts.inc:1510, data/maps/AzaleaTown_KurtsHouse/scripts.pory:755 \| Script (dado ao jogador, var computado): data/maps/AzaleaTown_KurtsHouse/scripts.inc:1108, data/maps/AzaleaTown_KurtsHouse/scripts.pory:554 |
| `ITEM_LURE_BALL` — Lure Ball | A Ball that works well on fished up Pokémon. | Sim | Script (dado ao jogador): data/maps/AzaleaTown_KurtsHouse/scripts.inc:1492, data/maps/AzaleaTown_KurtsHouse/scripts.pory:746 \| Script (dado ao jogador, var computado): data/maps/AzaleaTown_KurtsHouse/scripts.inc:1068, data/maps/AzaleaTown_KurtsHouse/scripts.pory:534 |
| `ITEM_LUXURY_BALL` — Luxury Ball | A cozy Ball that makes Pokémon more friendly. | Sim | Favor Lady (Lilycove): …c/data/lilycove_lady.h (tabela conferida a mao) \| Held item de presente (givemon): data/maps/Kitakami_Houses/scripts.inc:92, data/maps/Kitakami_Houses/scripts.pory:155 \| Script (dado ao jogador): data/maps/AzaleaTown_KurtsHouse/scripts.inc:1480, data/maps/AzaleaTown_KurtsHouse/scripts.pory:740, data/scripts/contest_hall.inc:1137 (+1) \| Script (dado ao jogador, var computado): data/maps/AzaleaTown_KurtsHouse/scripts.inc:1182, data/maps/AzaleaTown_KurtsHouse/scripts.pory:591 |
| `ITEM_MASTER_BALL` — Master Ball | The best Ball that catches them all. | Sim | Script (dado ao jogador): data/maps/AzaleaTown_KurtsHouse/scripts.inc:1578, data/maps/AzaleaTown_KurtsHouse/scripts.pory:789, data/maps/NewBarkTown_Lab/scripts.inc:998 (+1) |
| `ITEM_MOON_BALL` — Moon Ball | A Ball that works well on Moon Stone users. | Sim | Script (dado ao jogador): data/maps/AzaleaTown_KurtsHouse/scripts.inc:1498, data/maps/AzaleaTown_KurtsHouse/scripts.pory:749 \| Script (dado ao jogador, var computado): data/maps/AzaleaTown_KurtsHouse/scripts.inc:1076, data/maps/AzaleaTown_KurtsHouse/scripts.pory:538 |
| `ITEM_NEST_BALL` — Nest Ball | A Ball that works better on weaker Pokémon. | Sim | Item ball no mapa (object_event): Route120 \| Script (dado ao jogador, var computado): data/maps/AzaleaTown_KurtsHouse/scripts.inc:1116, data/maps/AzaleaTown_KurtsHouse/scripts.pory:558 |
| `ITEM_NET_BALL` — Net Ball | A Ball that works well on Water- and Bug-type Pokémon. | Sim | Script (dado ao jogador, var computado): data/maps/AzaleaTown_KurtsHouse/scripts.inc:1124, data/maps/AzaleaTown_KurtsHouse/scripts.pory:562 |
| `ITEM_PARK_BALL` — Park Ball | A special Ball for the Pal Park. | Sim | Script (dado ao jogador): data/maps/AzaleaTown_KurtsHouse/scripts.inc:1546, data/maps/AzaleaTown_KurtsHouse/scripts.pory:773 \| Script (dado ao jogador, var computado): data/maps/AzaleaTown_KurtsHouse/scripts.inc:1198, data/maps/AzaleaTown_KurtsHouse/scripts.pory:599 |
| `ITEM_POKE_BALL` — Poké Ball | A tool used for catching wild Pokémon. | Sim | Item ball no mapa (object_event): MtMortar_1F_North, RocketHideout_B3F, Route10 (+8) \| Item escondido (hidden_item): Route26North, Route42, Route43 (+1) \| Loja / pokemart: …F/scripts.inc (LilycoveCity_DepartmentStore_2F) \| Script (additem): data/scripts/debug.inc:49 \| Script (dado ao jogador): data/maps/NewBarkTown_Lab/scripts.inc:1134, data/maps/NewBarkTown_Lab/scripts.pory:567, …tlerootTown_ProfessorBirchsLab/scripts.inc:1058 (+3) \| Script (dado ao jogador, var computado): data/maps/AzaleaTown_KurtsHouse/scripts.inc:1028, data/maps/AzaleaTown_KurtsHouse/scripts.pory:514 \| Script (finditem): data/maps/Route31/scripts.inc:166, data/maps/Route31/scripts.pory:83 |
| `ITEM_PREMIER_BALL` — Premier Ball | A rare Ball made in commemoration of some event. | Sim | Script (dado ao jogador, var computado): data/maps/AzaleaTown_KurtsHouse/scripts.inc:1174, data/maps/AzaleaTown_KurtsHouse/scripts.pory:587 |
| `ITEM_QUICK_BALL` — Quick Ball | Works well if used on the first turn. | Sim | Script (dado ao jogador, var computado): data/maps/AzaleaTown_KurtsHouse/scripts.inc:1132, data/maps/AzaleaTown_KurtsHouse/scripts.pory:566, …aps/GoldenrodCity_RadioTower_2F/scripts.inc:396 (+1) |
| `ITEM_REPEAT_BALL` — Repeat Ball | A Ball that works better on Pokémon caught before. | Sim | Script (dado ao jogador, var computado): data/maps/AzaleaTown_KurtsHouse/scripts.inc:1148, data/maps/AzaleaTown_KurtsHouse/scripts.pory:574 |
| `ITEM_SAFARI_BALL` — Safari Ball | A special Ball that is used only in the Safari Zone. | Sim | Script (dado ao jogador): data/maps/AzaleaTown_KurtsHouse/scripts.inc:1534, data/maps/AzaleaTown_KurtsHouse/scripts.pory:767, data/maps/Gate_NationalPark/scripts.inc:141 (+3) \| Script (dado ao jogador, var computado): data/maps/AzaleaTown_KurtsHouse/scripts.inc:1206, data/maps/AzaleaTown_KurtsHouse/scripts.pory:603 |
| `ITEM_SPORT_BALL` — Sport Ball | A special Ball used in the Bug- Catching Contest. | Sim | Script (dado ao jogador): data/maps/AzaleaTown_KurtsHouse/scripts.inc:1540, data/maps/AzaleaTown_KurtsHouse/scripts.pory:770 \| Script (dado ao jogador, var computado): data/maps/AzaleaTown_KurtsHouse/scripts.inc:1190, data/maps/AzaleaTown_KurtsHouse/scripts.pory:595 |
| `ITEM_STRANGE_BALL` — Strange Ball | An unusual Ball warped through space and time. | Sim | Script (dado ao jogador): data/maps/AzaleaTown_KurtsHouse/scripts.inc:1570, data/maps/AzaleaTown_KurtsHouse/scripts.pory:785 \| Script (dado ao jogador, var computado): data/maps/AzaleaTown_KurtsHouse/scripts.inc:1234, data/maps/AzaleaTown_KurtsHouse/scripts.pory:617 |
| `ITEM_TIMER_BALL` — Timer Ball | A Ball that gains power in battles taking many turns. | Sim | Script (dado ao jogador): …aps/Route110_TrickHouseEntrance/scripts.inc:347 \| Script (dado ao jogador, var computado): data/maps/AzaleaTown_KurtsHouse/scripts.inc:1140, data/maps/AzaleaTown_KurtsHouse/scripts.pory:570 |
| `ITEM_ULTRA_BALL` — Ultra Ball | A better Ball with a higher catch rate than a Great Ball. | Sim | Loja / pokemart: …F/scripts.inc (LilycoveCity_DepartmentStore_2F) \| Script (dado ao jogador, var computado): data/maps/AzaleaTown_KurtsHouse/scripts.inc:1052, data/maps/AzaleaTown_KurtsHouse/scripts.pory:526 |

## Itens (233)

| Item | O que faz | Obtível in-game? | Como se obtém |
|---|---|---|---|
| `ITEM_ABILITY_CAPSULE` — Ability Capsule | Switches a Pokémon's ability. | Sim | Item ball no mapa (object_event): GoldenrodShore, VictoryRoadKanto_B2F \| Loja / pokemart: …cripts.pory (BattleFrontier_BattleFactoryLobby), …scripts.inc (BattleFrontier_BattleFactoryLobby) \| Pickup (habilidade): battle_script_commands.c sPickupTable |
| `ITEM_ABILITY_PATCH` — Ability Patch | Turns the ability of a Pokémon into a rare ability. | Sim | Item ball no mapa (object_event): Route27, SnowtopMountain_B1F, TinTower_4F (+1) \| Item escondido (hidden_item): UnionCave_B2F \| Loja / pokemart: …Lobby/scripts.pory (GoldenrodBattleAracdeLobby), …cripts.pory (BattleFrontier_BattleFactoryLobby), …eLobby/scripts.inc (GoldenrodBattleAracdeLobby) (+1) \| Pickup (habilidade): battle_script_commands.c sPickupTable \| Script (dado ao jogador, var computado): …aps/GoldenrodCity_RadioTower_2F/scripts.inc:476, …ps/GoldenrodCity_RadioTower_2F/scripts.pory:238 |
| `ITEM_ADAMANT_MINT` — Adamant Mint | Can be smelled. It ups Attack, but reduces Sp. Atk. | Sim | Item ball no mapa (object_event): RocketHideout_B3F, UnionCave_B2F \| Item escondido (hidden_item): Route32 \| Loja / pokemart: …aps/Route40_House5/scripts.inc (Route40_House5), …owerShop/scripts.inc (GoldenrodCity_FlowerShop), …ps/Route40_House5/scripts.pory (Route40_House5) (+1) |
| `ITEM_AMAZE_MULCH` — Amaze Mulch | A fertilizer Rich Surprising and Boosting as well. | Não | - |
| `ITEM_ARMORITE_ORE` — Armorite Ore | A rare ore. Can be found in the Isle of Armor at Galar. | Não | - |
| `ITEM_ARMOR_FOSSIL` — Armor Fossil | A piece of a prehistoric Poké- mon's head. | Não | - |
| `ITEM_AUSPICIOUS_ARMOR` — Auspicious Armor | Armor inhabited by auspicious wishes. Causes evolution. | Sim | Item ball no mapa (object_event): MtMortar_1F_North \| Loja / pokemart: …enter/scripts.inc (IndigoPlateau_PokemonCenter), …nter/scripts.pory (IndigoPlateau_PokemonCenter) |
| `ITEM_AUX_EVASION` — Aux Evasion | Sharply raises evasiveness during one battle. Raises evasiveness during one battle. | Não | - |
| `ITEM_AUX_GUARD` — Aux Guard | Sharply raises defenses during one battle. Raises defenses during one battle. | Não | - |
| `ITEM_AUX_POWER` — Aux Power | Sharply raises offenses during one battle. Raises offenses during one battle. | Não | - |
| `ITEM_AUX_POWERGUARD` — Aux Powerguard | Sharply raises offense & defense during one battle. Raises offense and defense during one battle. | Não | - |
| `ITEM_BALM_MUSHROOM` — Balm Mushroom | A rare mushroom that would sell at a high price. | Sim | Pickup (habilidade): battle_script_commands.c sPickupTable |
| `ITEM_BEAD_MAIL` — Bead Mail | Mail featuring a sketch of the holding Pokémon. | Sim | Item ball no mapa (object_event): Route110_TrickHousePuzzle8 |
| `ITEM_BECKONING_BELL` — Beckoning Bell | An ornate bell that renews hidden grottos once. | Sim | Loja / pokemart: …cripts.pory (BattleFrontier_BattleFactoryLobby), …scripts.inc (BattleFrontier_BattleFactoryLobby) \| Script (dado ao jogador): data/maps/IlexForest/scripts.inc:1628, data/maps/IlexForest/scripts.pory:825 |
| `ITEM_BERRY_SWEET` — Berry Sweet | A berry-shaped sweet loved by Milcery. | Não | - |
| `ITEM_BIG_BAMBOO_SHOOT` — Big Bamboo Shoot | A large and rare bamboo shoot. Best sold to gourmands. | Não | - |
| `ITEM_BIG_MUSHROOM` — Big Mushroom | A rare mushroom that would sell at a high price. | Sim | Pickup (habilidade): battle_script_commands.c sPickupTable |
| `ITEM_BIG_NUGGET` — Big Nugget | A big nugget made of gold, sellable at a high price. | Sim | Item ball no mapa (object_event): RocketHideout, RocketHideout_B1F, Route35 (+3) \| Item escondido (hidden_item): Route50 \| Loja / pokemart: …cripts.pory (BattleFrontier_BattleFactoryLobby), …scripts.inc (BattleFrontier_BattleFactoryLobby) \| Pickup (habilidade): battle_script_commands.c sPickupTable \| Script (dado ao jogador): data/maps/Route25/scripts.inc:82, …aps/GoldenrodCity_RadioTower_1F/scripts.inc:188, …aps/GoldenrodCity_RadioTower_1F/scripts.pory:94 |
| `ITEM_BIG_PEARL` — Big Pearl | A lovely large pearl that would sell at a high price. | Sim | Item ball no mapa (object_event): CeruleanCave_B1F \| Item escondido (hidden_item): DarkCave_NorthSide |
| `ITEM_BLACK_APRICORN` — Black Apricorn | A black apricorn. It has an inde- scribable scent. | Não | - |
| `ITEM_BLACK_AUGURITE` — Black Augurite | A black stone that makes some Pokémon evolve. | Sim | Item ball no mapa (object_event): LakeOfRage |
| `ITEM_BLACK_FLUTE` — Black Flute | A glass flute that keeps away wild Pokémon. | Não (só em mapa fora da campanha) | Mencionado em script (verificar): data/maps/Route113_GlassWorkshop/scripts.inc:123, data/maps/Route113_GlassWorkshop/scripts.inc:264 \| Script (dado ao jogador, var computado): data/maps/Route113_GlassWorkshop/scripts.inc:123, data/maps/Route113_GlassWorkshop/scripts.inc:264 |
| `ITEM_BLUE_APRICORN` — Blue Apricorn | A blue apricorn. It smells a bit like grass. | Não | - |
| `ITEM_BLUE_SCARF` — Blue Scarf | A hold item that raises Beauty in Contests. | Não (só em mapa fora da campanha) | Mencionado em script (verificar): …aps/SlateportCity_PokemonFanClub/scripts.inc:83 \| Script (dado ao jogador): …aps/SlateportCity_PokemonFanClub/scripts.inc:87 |
| `ITEM_BLUE_SHARD` — Blue Shard | A shard from an ancient item. Can be sold cheaply. | Sim | Rock Smash: …c/data/lilycove_lady.h (tabela conferida a mao) |
| `ITEM_BOLD_MINT` — Bold Mint | Can be smelled. It ups Defense, but reduces Attack. | Sim | Loja / pokemart: …aps/Route40_House5/scripts.inc (Route40_House5), …owerShop/scripts.inc (GoldenrodCity_FlowerShop), …ps/Route40_House5/scripts.pory (Route40_House5) (+1) |
| `ITEM_BOOST_MULCH` — Boost Mulch | A fertilizer that ups the dry speed of soft soil. | Não | - |
| `ITEM_BOTTLE_CAP` — Bottle Cap | A beautiful bottle cap that gives off a silver gleam. | Sim | Loja / pokemart: …/scripts.pory (BattleFrontier_BattleTowerLobby), …y/scripts.inc (BattleFrontier_BattleTowerLobby) \| Pickup (habilidade): battle_script_commands.c sPickupTable \| Vara de pescar (item bonus): …c/data/lilycove_lady.h (tabela conferida a mao) |
| `ITEM_BRAVE_MINT` — Brave Mint | Can be smelled. It ups Attack, but reduces Speed. | Sim | Loja / pokemart: …aps/Route40_House5/scripts.inc (Route40_House5), …owerShop/scripts.inc (GoldenrodCity_FlowerShop), …ps/Route40_House5/scripts.pory (Route40_House5) (+1) |
| ★ `ITEM_BRITTLE_HERB` — Brittle Herb | An herb that lowers one Pokémon's Defense IV by one. | Sim | Loja / pokemart: …/scripts.pory (GoldenrodCity_UndergroundTunnel), …l/scripts.inc (GoldenrodCity_UndergroundTunnel) |
| `ITEM_BUG_TERA_SHARD` — Bug Tera Shard | These shards may form when a Tera Pokémon faints. | Não | - |
| `ITEM_CALCIUM_EX` — Calcium EX | Maximizes the effort value of a Pokémon's Sp. Atk. | Sim | Item ball no mapa (object_event): MtSilver_1F_WaterfallRoom, TinTower_9F, VictoryRoadKanto_1F \| Loja / pokemart: …/scripts.pory (BattleFrontier_BattleTowerLobby), …Lobby/scripts.pory (GoldenrodBattleAracdeLobby), …eLobby/scripts.inc (GoldenrodBattleAracdeLobby) (+1) |
| `ITEM_CALM_MINT` — Calm Mint | Can be smelled. It ups Sp. Def, but reduces Attack. | Sim | Loja / pokemart: …aps/Route40_House5/scripts.inc (Route40_House5), …owerShop/scripts.inc (GoldenrodCity_FlowerShop), …ps/Route40_House5/scripts.pory (Route40_House5) (+1) |
| `ITEM_CARBOS_EX` — Carbos EX | Maximizes the effort value of a Pokémon's Speed. | Sim | Item ball no mapa (object_event): MtSilver_1F_WaterfallRoom, Route27, VajraDesertEast \| Loja / pokemart: …/scripts.pory (BattleFrontier_BattleTowerLobby), …Lobby/scripts.pory (GoldenrodBattleAracdeLobby), …eLobby/scripts.inc (GoldenrodBattleAracdeLobby) (+1) |
| `ITEM_CAREFUL_MINT` — Careful Mint | Can be smelled. It ups Sp. Def, but reduces Sp. Atk. | Sim | Loja / pokemart: …aps/Route40_House5/scripts.inc (Route40_House5), …owerShop/scripts.inc (GoldenrodCity_FlowerShop), …ps/Route40_House5/scripts.pory (Route40_House5) (+1) |
| `ITEM_CHIPPED_POT` — Chipped Pot | A chipped teapot that makes certain Pokémon evolve. | Sim | Loja / pokemart: …aps/SafariZoneGate/scripts.inc (SafariZoneGate), …ps/SafariZoneGate/scripts.pory (SafariZoneGate) |
| `ITEM_CHOICE_DUMPLING` — Choice Dumpling | ????? | Não | - |
| `ITEM_CLAW_FOSSIL` — Claw Fossil | A fossil of an ancient, seafloor- dwelling Pokémon. | Sim | Script (finditem): data/maps/PewterCity_Museum_1F/scripts.inc:15 |
| `ITEM_CLOVER_SWEET` — Clover Sweet | A clover-shaped sweet loved by Milcery. | Não | - |
| `ITEM_COMET_SHARD` — Comet Shard | A comet's shard. It would sell for a high price. | Não | - |
| `ITEM_COVER_FOSSIL` — Cover Fossil | A piece of a prehistoric Poké- mon's back. | Sim | Rock Smash: …c/data/lilycove_lady.h (tabela conferida a mao) |
| `ITEM_CRACKED_POT` — Cracked Pot | A cracked teapot that makes certain Pokémon evolve. | Sim | Loja / pokemart: …aps/SafariZoneGate/scripts.inc (SafariZoneGate), …ps/SafariZoneGate/scripts.pory (SafariZoneGate) |
| `ITEM_DAMP_MULCH` — Damp Mulch | A fertilizer that decelerates the growth of Berries. | Sim | Loja / pokemart: …owerShop/scripts.inc (GoldenrodCity_FlowerShop), …werShop/scripts.pory (GoldenrodCity_FlowerShop) |
| `ITEM_DARK_TERA_SHARD` — Dark Tera Shard | These shards may form when a Tera Pokémon faints. | Não | - |
| `ITEM_DAWN_STONE` — Dawn Stone | Makes certain species of Pokémon evolve. | Sim | Item ball no mapa (object_event): Route45 \| Loja / pokemart: …enter/scripts.inc (IndigoPlateau_PokemonCenter), …nter/scripts.pory (IndigoPlateau_PokemonCenter) \| Script (dado ao jogador, var computado): data/scripts/bug_contest.inc:140 |
| `ITEM_DIRE_HIT` — Dire Hit | Raises the critical-hit ratio during one battle. | Sim | Item ball no mapa (object_event): ViridianForest \| Loja / pokemart: …/scripts.inc (GoldenrodCity_DepartmentStore_3F), …arborTown_Mart/scripts.inc (FallarborTown_Mart), …ill_Entrance/scripts.inc (TrainerHill_Entrance) |
| `ITEM_DOME_FOSSIL` — Dome Fossil | A piece of an ancient marine Pokémon's shell. | Sim | Rock Smash: …c/data/lilycove_lady.h (tabela conferida a mao) |
| `ITEM_DRAGON_SCALE` — Dragon Scale | A strange scale held by Dragon- type Pokémon. | Sim | Item ball no mapa (object_event): MtMortar_2F \| Loja / pokemart: …hoganyTown_Shop/scripts.inc (MahoganyTown_Shop) |
| `ITEM_DRAGON_TERA_SHARD` — Dragon Tera Shard | These shards may form when a Tera Pokémon faints. | Não | - |
| `ITEM_DREAM_MAIL` — Dream Mail | Mail featuring a sketch of the holding Pokémon. | Não | - |
| `ITEM_DUBIOUS_DISC` — Dubious Disc | A clear device overflowing with dubious data. | Sim | Loja / pokemart: …hoganyTown_Shop/scripts.inc (MahoganyTown_Shop) |
| ★ `ITEM_DULL_HERB` — Dull Herb | An herb that lowers one Pokémon's Sp. Atk IV by one. | Sim | Loja / pokemart: …/scripts.pory (GoldenrodCity_UndergroundTunnel), …l/scripts.inc (GoldenrodCity_UndergroundTunnel) |
| `ITEM_DUSK_STONE` — Dusk Stone | Makes certain species of Pokémon evolve. | Sim | Item ball no mapa (object_event): DarkCave_SouthSide, MtMortar_B1F \| Loja / pokemart: …enter/scripts.inc (IndigoPlateau_PokemonCenter), …nter/scripts.pory (IndigoPlateau_PokemonCenter) \| Script (dado ao jogador, var computado): data/scripts/bug_contest.inc:148 |
| `ITEM_DYNAMAX_CANDY` — Dynamax Candy | Raises the Dynamax Level of a single Pokémon by one. | Não | - |
| `ITEM_DYNITE_ORE` — Dynite Ore | A mysterious ore. It can be found in Galar's Max Lair. | Não | - |
| `ITEM_ELECTIRIZER` — Electirizer | Loved by a certain Pokémon. It's full of electric energy. | Só held item (Roubo/Golpe do Dia) | Held item selvagem (Roubo/Golpe do Dia): gen_1_families.h |
| `ITEM_ELECTRIC_TERA_SHARD` — Electric Tera Shard | These shards may form when a Tera Pokémon faints. | Não | - |
| `ITEM_EXP_CANDY_L` — Exp. Candy L | Gives a large amount of Exp. to a single Pokémon. | Sim | Script (dado ao jogador): data/maps/Kitakami_Houses/scripts.inc:47, data/maps/Kitakami_Houses/scripts.inc:56, data/maps/Kitakami_Houses/scripts.pory:23 (+1) \| Script (dado ao jogador, var computado): …aps/GoldenrodCity_RadioTower_2F/scripts.inc:446, …ps/GoldenrodCity_RadioTower_2F/scripts.pory:223 |
| `ITEM_EXP_CANDY_M` — Exp. Candy M | Gives a moderate amount of Exp. to a single Pokémon. | Sim | Script (dado ao jogador): data/maps/Kitakami_Houses/scripts.inc:42, data/maps/Kitakami_Houses/scripts.inc:49, data/maps/Kitakami_Houses/scripts.pory:21 (+1) |
| `ITEM_EXP_CANDY_S` — Exp. Candy S | Gives a small amount of Exp. to a single Pokémon. | Não | - |
| `ITEM_EXP_CANDY_XL` — Exp. Candy XL | Gives a very large amount of Exp. to a single Pokémon. | Sim | Item ball no mapa (object_event): Route50 \| Loja / pokemart: …/scripts.pory (BattleFrontier_BattleTowerLobby), …y/scripts.inc (BattleFrontier_BattleTowerLobby) \| Script (dado ao jogador): data/maps/BattleCafe/scripts.inc:2137, data/maps/BattleCafe/scripts.pory:1145, data/maps/Kitakami_Houses/scripts.inc:54 (+1) |
| `ITEM_EXP_CANDY_XS` — Exp. Candy XS | Gives a very small amount of Exp. to a single Pokémon. | Não | - |
| `ITEM_FAB_MAIL` — Fab Mail | A gorgeous-print Mail to be held by a Pokémon. | Não | - |
| `ITEM_FAIRY_TERA_SHARD` — Fairy Tera Shard | These shards may form when a Tera Pokémon faints. | Não | - |
| `ITEM_FIGHTING_TERA_SHARD` — Fighting Tera Shard | These shards may form when a Tera Pokémon faints. | Não | - |
| `ITEM_FIRE_STONE` — Fire Stone | Makes certain species of Pokémon evolve. | Sim | Item ball no mapa (object_event): MtMortar_Depths_1, RuinsOfAlph_PuzzleAndRewardChambers \| Loja / pokemart: …aps/SafariZoneGate/scripts.inc (SafariZoneGate), …enter/scripts.inc (IndigoPlateau_PokemonCenter), …nter/scripts.pory (IndigoPlateau_PokemonCenter) (+1) \| Script (dado ao jogador): …a/maps/MauvilleCity_GameCorner/scripts.inc:1752, …a/maps/MauvilleCity_GameCorner/scripts.pory:876 \| Script (dado ao jogador, var computado): data/scripts/bug_contest.inc:169, …e124_DivingTreasureHuntersHouse/scripts.inc:222 |
| `ITEM_FIRE_TERA_SHARD` — Fire Tera Shard | These shards may form when a Tera Pokémon faints. | Não | - |
| `ITEM_FLOWER_SWEET` — Flower Sweet | A flower-shaped sweet loved by Milcery. | Não | - |
| `ITEM_FLUFFY_TAIL` — Fluffy Tail | Use to flee from any battle with a wild Pokémon. | Sim | Loja / pokemart: …F/scripts.inc (LilycoveCity_DepartmentStore_2F) |
| `ITEM_FLYING_TERA_SHARD` — Flying Tera Shard | These shards may form when a Tera Pokémon faints. | Não | - |
| `ITEM_FOSSILIZED_BIRD` — Fossilized Bird | A fossil of an ancient, sky- soaring Pokémon. | Não | - |
| `ITEM_FOSSILIZED_DINO` — Fossilized Dino | A fossil of an ancient, sea- dwelling Pokémon. | Não | - |
| `ITEM_FOSSILIZED_DRAKE` — Fossilized Drake | A fossil of an ancient, land- roaming Pokémon. | Não | - |
| `ITEM_FOSSILIZED_FISH` — Fossilized Fish | A fossil of an ancient, sea- dwelling Pokémon. | Não | - |
| `ITEM_FRESH_START_MOCHI` — Fresh-Start Mochi | An item that resets all base points of a Pokémon. | Não | - |
| `ITEM_GALARICA_CUFF` — Galarica Cuff | A cuff from Galar that makes certain Pokémon evolve. | Sim | Loja / pokemart: …/AzaleaTown_Mart/scripts.pory (AzaleaTown_Mart), …s/AzaleaTown_Mart/scripts.inc (AzaleaTown_Mart) |
| `ITEM_GALARICA_TWIG` — Galarica Twig | A twig from a tree in Galar called Galarica. | Não | - |
| `ITEM_GALARICA_WREATH` — Galarica Wreath | A wreath made in Galar. Makes some Pokémon evolve. | Sim | Loja / pokemart: …/AzaleaTown_Mart/scripts.pory (AzaleaTown_Mart), …s/AzaleaTown_Mart/scripts.inc (AzaleaTown_Mart) |
| `ITEM_GENTLE_MINT` — Gentle Mint | Can be smelled. It ups Sp. Def, but reduces Defense. | Sim | Loja / pokemart: …aps/Route40_House5/scripts.inc (Route40_House5), …owerShop/scripts.inc (GoldenrodCity_FlowerShop), …ps/Route40_House5/scripts.pory (Route40_House5) (+1) |
| `ITEM_GHOST_TERA_SHARD` — Ghost Tera Shard | These shards may form when a Tera Pokémon faints. | Não | - |
| `ITEM_GIMMIGHOUL_COIN` — Gimmighoul Coin | Gimmighoul hoard and treasure these curious coins. | Não | - |
| `ITEM_GLITTER_MAIL` — Glitter Mail | A Pikachu-print Mail to be held by a Pokémon. | Sim | Item ball no mapa (object_event): Route110_TrickHousePuzzle6 |
| `ITEM_GOLD_BOTTLE_CAP` — Gold Bottle Cap | A beautiful bottle cap that gives off a golden gleam. | Sim | Item ball no mapa (object_event): CianwoodCity \| Loja / pokemart: …/scripts.pory (BattleFrontier_BattleTowerLobby), …y/scripts.inc (BattleFrontier_BattleTowerLobby) \| Script (dado ao jogador): data/maps/BattleCafe/scripts.inc:1845, data/maps/BattleCafe/scripts.pory:997 \| Vara de pescar (item bonus): …c/data/lilycove_lady.h (tabela conferida a mao) |
| `ITEM_GOOEY_MULCH` — Gooey Mulch | A fertilizer that makes more Berries regrow after fall. | Sim | Loja / pokemart: …owerShop/scripts.inc (GoldenrodCity_FlowerShop), …werShop/scripts.pory (GoldenrodCity_FlowerShop) |
| `ITEM_GOOPY_HERB` — Goopy Herb | An herb that lowers one Pokémon's Speed IV by one. | Sim | Loja / pokemart: …/scripts.pory (GoldenrodCity_UndergroundTunnel), …l/scripts.inc (GoldenrodCity_UndergroundTunnel) |
| `ITEM_GRASS_TERA_SHARD` — Grass Tera Shard | These shards may form when a Tera Pokémon faints. | Não | - |
| `ITEM_GREEN_APRICORN` — Green Apricorn | A green apricorn. It has a strange, aromatic scent. | Não | - |
| `ITEM_GREEN_SCARF` — Green Scarf | A hold item that raises Smart in Contests. | Não (só em mapa fora da campanha) | Mencionado em script (verificar): …ps/SlateportCity_PokemonFanClub/scripts.inc:103 \| Script (dado ao jogador): …ps/SlateportCity_PokemonFanClub/scripts.inc:107 |
| `ITEM_GREEN_SHARD` — Green Shard | A shard from an ancient item. Can be sold cheaply. | Sim | Rock Smash: …c/data/lilycove_lady.h (tabela conferida a mao) |
| `ITEM_GRIMY_HERB` — Grimy Herb | An herb that lowers one Pokémon's Attack IV by one. | Sim | Loja / pokemart: …/scripts.pory (GoldenrodCity_UndergroundTunnel), …l/scripts.inc (GoldenrodCity_UndergroundTunnel) |
| `ITEM_GROUND_TERA_SHARD` — Ground Tera Shard | These shards may form when a Tera Pokémon faints. | Não | - |
| `ITEM_GROWTH_MULCH` — Growth Mulch | A fertilizer that accelerates the growth of Berries. | Sim | Loja / pokemart: …owerShop/scripts.inc (GoldenrodCity_FlowerShop), …werShop/scripts.pory (GoldenrodCity_FlowerShop) |
| `ITEM_GUARD_SPEC` — Guard Spec. | Prevents stat reduction when used in battle. | Sim | Item ball no mapa (object_event): WhirlIslands_1F \| Loja / pokemart: …/scripts.inc (GoldenrodCity_DepartmentStore_3F), …arborTown_Mart/scripts.inc (FallarborTown_Mart), …ill_Entrance/scripts.inc (TrainerHill_Entrance) |
| `ITEM_HARBOR_MAIL` — Harbor Mail | A Wingull-print Mail to be held by a Pokémon. | Sim | Item ball no mapa (object_event): Route110_TrickHousePuzzle2 |
| `ITEM_HASTY_MINT` — Hasty Mint | Can be smelled. It ups Speed, but reduces Defense. | Sim | Loja / pokemart: …aps/Route40_House5/scripts.inc (Route40_House5), …owerShop/scripts.inc (GoldenrodCity_FlowerShop), …ps/Route40_House5/scripts.pory (Route40_House5) (+1) |
| `ITEM_HEART_SCALE` — Heart Scale | A lovely scale. It can be sold at a high price. | Sim | Favor Lady (Lilycove): …c/data/lilycove_lady.h (tabela conferida a mao) \| Script (dado ao jogador): data/scripts/field_move_scripts.inc:586 |
| `ITEM_HELIX_FOSSIL` — Helix Fossil | A piece of an ancient marine Pokémon's seashell. | Verificar (só mencionado em script) | Mencionado em script (verificar): data/maps/RuinsOfAlph_Lab/scripts.inc:136, data/maps/RuinsOfAlph_Lab/scripts.inc:994, data/maps/RuinsOfAlph_Lab/scripts.pory:497 (+1) |
| `ITEM_HONEY` — Honey | Sweet honey that attracts wild Pokémon when used. | Só held item (Roubo/Golpe do Dia) | Held item selvagem (Roubo/Golpe do Dia): gen_2_families.h, gen_3_families.h, gen_4_families.h (+1) |
| `ITEM_HP_UP_EX` — HP Up EX | Maximizes the effort value of a Pokémon's HP. | Sim | Loja / pokemart: …/scripts.pory (BattleFrontier_BattleTowerLobby), …Lobby/scripts.pory (GoldenrodBattleAracdeLobby), …eLobby/scripts.inc (GoldenrodBattleAracdeLobby) (+1) |
| `ITEM_ICE_STONE` — Ice Stone | Makes certain species of Pokémon evolve. | Sim | Hidden Grotto (item raro): src/hidden_grotto.c \| Item ball no mapa (object_event): SnowtopMountain \| Loja / pokemart: …enter/scripts.inc (IndigoPlateau_PokemonCenter), …nter/scripts.pory (IndigoPlateau_PokemonCenter) \| Script (dado ao jogador, var computado): data/scripts/bug_contest.inc:152 |
| `ITEM_ICE_TERA_SHARD` — Ice Tera Shard | These shards may form when a Tera Pokémon faints. | Não | - |
| `ITEM_IMPISH_MINT` — Impish Mint | Can be smelled. It ups Defense, but reduces Sp. Atk. | Sim | Loja / pokemart: …aps/Route40_House5/scripts.inc (Route40_House5), …owerShop/scripts.inc (GoldenrodCity_FlowerShop), …ps/Route40_House5/scripts.pory (Route40_House5) (+1) |
| `ITEM_IRON_EX` — Iron EX | Maximizes the effort value of a Pokémon's Defense. | Sim | Loja / pokemart: …/scripts.pory (BattleFrontier_BattleTowerLobby), …Lobby/scripts.pory (GoldenrodBattleAracdeLobby), …eLobby/scripts.inc (GoldenrodBattleAracdeLobby) (+1) |
| `ITEM_JAW_FOSSIL` — Jaw Fossil | A piece of a prehistoric Poké- mon's large jaw. | Sim | Rock Smash: …c/data/lilycove_lady.h (tabela conferida a mao) |
| `ITEM_JOLLY_MINT` — Jolly Mint | Can be smelled. It ups Speed, but reduces Sp. Atk. | Sim | Item ball no mapa (object_event): RocketHideout_B1F \| Loja / pokemart: …aps/Route40_House5/scripts.inc (Route40_House5), …owerShop/scripts.inc (GoldenrodCity_FlowerShop), …ps/Route40_House5/scripts.pory (Route40_House5) (+1) |
| `ITEM_LAX_MINT` — Lax Mint | Can be smelled. It ups Defense, but reduces Sp. Def. | Sim | Item ball no mapa (object_event): IcePath_B1F \| Loja / pokemart: …aps/Route40_House5/scripts.inc (Route40_House5), …owerShop/scripts.inc (GoldenrodCity_FlowerShop), …ps/Route40_House5/scripts.pory (Route40_House5) (+1) |
| `ITEM_LEADERS_CREST` — Leader's Crest | A shard of an old blade of some sort. Held by Bisharp. | Sim | Item ball no mapa (object_event): AzaleaTown |
| `ITEM_LEAF_STONE` — Leaf Stone | Makes certain species of Pokémon evolve. | Sim | Hidden Grotto (item raro): src/hidden_grotto.c \| Item ball no mapa (object_event): RuinsOfAlph_PuzzleAndRewardChambers \| Loja / pokemart: …aps/SafariZoneGate/scripts.inc (SafariZoneGate), …enter/scripts.inc (IndigoPlateau_PokemonCenter), …nter/scripts.pory (IndigoPlateau_PokemonCenter) (+1) \| Script (dado ao jogador): …a/maps/MauvilleCity_GameCorner/scripts.inc:1830, …a/maps/MauvilleCity_GameCorner/scripts.pory:915 \| Script (dado ao jogador, var computado): data/maps/Route25_BillsHouse/scripts.inc:66, data/scripts/bug_contest.inc:136, …e124_DivingTreasureHuntersHouse/scripts.inc:237 |
| `ITEM_LINKING_CORD` — Linking Cord | A mysterious string that makes some Pokémon evolve. | Sim | Item ball no mapa (object_event): Route38 \| Loja / pokemart: …aps/SafariZoneGate/scripts.inc (SafariZoneGate), …enter/scripts.inc (IndigoPlateau_PokemonCenter), …nter/scripts.pory (IndigoPlateau_PokemonCenter) (+1) \| Script (dado ao jogador): …a/maps/MauvilleCity_GameCorner/scripts.inc:1648, …a/maps/MauvilleCity_GameCorner/scripts.pory:824 |
| `ITEM_LONELY_MINT` — Lonely Mint | Can be smelled. It ups Attack, but reduces Defense. | Sim | Loja / pokemart: …aps/Route40_House5/scripts.inc (Route40_House5), …owerShop/scripts.inc (GoldenrodCity_FlowerShop), …ps/Route40_House5/scripts.pory (Route40_House5) (+1) |
| `ITEM_LOVE_SWEET` — Love Sweet | A heart-shaped sweet loved by Milcery. | Não | - |
| `ITEM_LURE` — Lure | Makes Pokémon more likely to appear for 100 steps. | Verificar (só mencionado em script) | Mencionado em script (verificar): data/scripts/repel.inc:14 |
| `ITEM_MAGMARIZER` — Magmarizer | Loved by a certain Pokémon. It's full of magma energy. | Sim | Item ball no mapa (object_event): RintoVillage |
| `ITEM_MALICIOUS_ARMOR` — Malicious Armor | Armor inhabited by malicious will. Causes evolution. | Sim | Item ball no mapa (object_event): BurnedTower_B1F \| Loja / pokemart: …enter/scripts.inc (IndigoPlateau_PokemonCenter), …nter/scripts.pory (IndigoPlateau_PokemonCenter) |
| `ITEM_MASTERPIECE_TEACUP` — Masterpiece Teacup | A chipped teacup that makes certain Pokémon evolve. | Sim | Loja / pokemart: data/maps/OlivineCity/scripts.inc (OlivineCity), data/maps/OlivineCity/scripts.pory (OlivineCity) |
| `ITEM_MAX_LURE` — Max Lure | Makes Pokémon more likely to appear for 250 steps. | Não | - |
| `ITEM_MAX_MUSHROOMS` — Max Mushrooms | Raises every stat during one battle by one stage. | Não | - |
| `ITEM_MAX_REPEL` — Max Repel | Repels weak wild Pokémon for 250 steps. | Sim | Item ball no mapa (object_event): KitakamiMountain1F, Route44 \| Item escondido (hidden_item): Route47, VictoryRoadKanto_1F \| Loja / pokemart: …F/scripts.inc (LilycoveCity_DepartmentStore_2F) \| Pickup (habilidade): battle_script_commands.c sPickupTable |
| `ITEM_MECH_MAIL` — Mech Mail | A Magnemite-print Mail to be held by a Pokémon. | Sim | Item ball no mapa (object_event): Route110_TrickHousePuzzle4 \| Loja / pokemart: …/AzaleaTown_Mart/scripts.pory (AzaleaTown_Mart), …F/scripts.inc (LilycoveCity_DepartmentStore_2F), …s/AzaleaTown_Mart/scripts.inc (AzaleaTown_Mart) |
| `ITEM_MEOWSCARADITE` — Meowscaradite | Lets Meowscarada Mega Evolve in battle. | Não | - |
| `ITEM_METAL_ALLOY` — Metal Alloy | A peculiar metal that makes certain Pokémon evolve. | Só held item (Roubo/Golpe do Dia) | Held item selvagem (Roubo/Golpe do Dia): gen_8_families.h |
| `ITEM_MILD_MINT` — Mild Mint | Can be smelled. It ups Sp. Atk, but reduces Defense. | Sim | Loja / pokemart: …aps/Route40_House5/scripts.inc (Route40_House5), …owerShop/scripts.inc (GoldenrodCity_FlowerShop), …ps/Route40_House5/scripts.pory (Route40_House5) (+1) |
| `ITEM_MODEST_MINT` — Modest Mint | Can be smelled. It ups Sp. Atk, but reduces Attack. | Sim | Item escondido (hidden_item): Route34 \| Loja / pokemart: …aps/Route40_House5/scripts.inc (Route40_House5), …owerShop/scripts.inc (GoldenrodCity_FlowerShop), …ps/Route40_House5/scripts.pory (Route40_House5) (+1) |
| `ITEM_MOON_STONE` — Moon Stone | Makes certain species of Pokémon evolve. | Sim | Hidden Grotto (item raro): src/hidden_grotto.c \| Item ball no mapa (object_event): Route27, RuinsOfAlph_PuzzleAndRewardChambers \| Loja / pokemart: …enter/scripts.inc (IndigoPlateau_PokemonCenter), …nter/scripts.pory (IndigoPlateau_PokemonCenter) \| Pickup (habilidade): battle_script_commands.c sPickupTable \| Script (dado ao jogador): …a/maps/MauvilleCity_GameCorner/scripts.inc:1726, …a/maps/MauvilleCity_GameCorner/scripts.pory:863 \| Script (dado ao jogador, var computado): data/scripts/bug_contest.inc:128 |
| `ITEM_NAIVE_MINT` — Naive Mint | Can be smelled. It ups Speed, but reduces Sp. Def. | Sim | Loja / pokemart: …aps/Route40_House5/scripts.inc (Route40_House5), …owerShop/scripts.inc (GoldenrodCity_FlowerShop), …ps/Route40_House5/scripts.pory (Route40_House5) (+1) |
| `ITEM_NAUGHTY_MINT` — Naughty Mint | Can be smelled. It ups Attack, but reduces Sp. Def. | Sim | Loja / pokemart: …aps/Route40_House5/scripts.inc (Route40_House5), …owerShop/scripts.inc (GoldenrodCity_FlowerShop), …ps/Route40_House5/scripts.pory (Route40_House5) (+1) |
| `ITEM_NONE` — None | ????? | Sim | Held item de presente (givemon): data/maps/SunMoonAltar/scripts.inc:1655, data/maps/UltraSpaceArena/scripts.inc:502, data/scripts/debug.inc:12 (+5) \| Loja / pokemart: data/maps/MtMoon_Shop/scripts.inc (MtMoon_Shop), data/maps/OlivineCity/scripts.inc (OlivineCity), …/scripts.inc (GoldenrodCity_DepartmentStore_5F) (+22) \| Script (dado ao jogador, var computado): …aps/GoldenrodCity_RadioTower_1F/scripts.inc:864, …ps/GoldenrodCity_RadioTower_1F/scripts.pory:432 |
| `ITEM_NORMAL_TERA_SHARD` — Normal Tera Shard | These shards may form when a Tera Pokémon faints. | Não | - |
| `ITEM_NUGGET` — Nugget | A nugget of pure gold. Can be sold at a high price. | Sim | Favor Lady (Lilycove): …c/data/lilycove_lady.h (tabela conferida a mao) \| Item ball no mapa (object_event): MtMortar_1F_North, Route119, Route120 (+3) \| Item escondido (hidden_item): Route30 \| Loja / pokemart: …cripts.pory (BattleFrontier_BattleFactoryLobby), …scripts.inc (BattleFrontier_BattleFactoryLobby) \| Pickup (habilidade): battle_script_commands.c sPickupTable \| Script (dado ao jogador): data/maps/Route2_House/scripts.inc:9 \| Script (dado ao jogador, var computado): …aps/GoldenrodCity_RadioTower_2F/scripts.inc:436, …ps/GoldenrodCity_RadioTower_2F/scripts.pory:218 |
| `ITEM_ODD_KEYSTONE` — Odd Keystone | Voices can be heard from this odd stone occasionally. | Não | - |
| `ITEM_OLD_AMBER` — Old Amber | A stone containing the genes of an ancient Pokémon. | Sim | Rock Smash: …c/data/lilycove_lady.h (tabela conferida a mao) \| Script (dado ao jogador): …a/maps/MauvilleCity_GameCorner/scripts.inc:1674, …a/maps/MauvilleCity_GameCorner/scripts.pory:837 |
| `ITEM_OVAL_STONE` — Oval Stone | Peculiar stone that evolves a certain Pokémon. | Só held item (Roubo/Golpe do Dia) | Held item selvagem (Roubo/Golpe do Dia): gen_1_families.h |
| `ITEM_PEARL` — Pearl | A pretty pearl that would sell at a cheap price. | Só held item (Roubo/Golpe do Dia) | Held item selvagem (Roubo/Golpe do Dia): gen_1_families.h, gen_3_families.h |
| `ITEM_PEARL_STRING` — Pearl String | Very large pearls that would sell at a high price. | Não | - |
| `ITEM_PEAT_BLOCK` — Peat Block | A block of material that makes some Pokémon evolve. | Sim | Item ball no mapa (object_event): DarkCave_NorthSide |
| `ITEM_PINK_APRICORN` — Pink Apricorn | A pink apricorn. It has a nice, sweet scent. | Não | - |
| `ITEM_PINK_NECTAR` — Pink Nectar | Flower nectar that changes the form of certain Pokémon. | Sim | Loja / pokemart: data/maps/OlivineCity/scripts.inc (OlivineCity), data/maps/OlivineCity/scripts.pory (OlivineCity) |
| `ITEM_PINK_SCARF` — Pink Scarf | A hold item that raises Cute in Contests. | Não (só em mapa fora da campanha) | Mencionado em script (verificar): …aps/SlateportCity_PokemonFanClub/scripts.inc:93 \| Script (dado ao jogador): …aps/SlateportCity_PokemonFanClub/scripts.inc:97 |
| `ITEM_PLUME_FOSSIL` — Plume Fossil | A piece of a prehistoric Poké- mon's wing. | Sim | Rock Smash: …c/data/lilycove_lady.h (tabela conferida a mao) |
| `ITEM_POISON_TERA_SHARD` — Poison Tera Shard | These shards may form when a Tera Pokémon faints. | Não | - |
| `ITEM_POKESHI_DOLL` — Pokéshi Doll | A wooden toy resembling a Poké- mon. Can be sold. | Não | - |
| `ITEM_POKE_DOLL` — Poké Doll | Use to flee from any battle with a wild Pokémon. | Sim | Loja / pokemart: data/maps/MtMoon_Shop/scripts.inc (MtMoon_Shop) \| Pickup (habilidade): battle_script_commands.c sPickupTable |
| `ITEM_POKE_TOY` — Poké Toy | Use to flee from any battle with a wild Pokémon. | Não | - |
| `ITEM_PRETTY_FEATHER` — Pretty Feather | A beautiful yet plain feather that does nothing. | Só held item (Roubo/Golpe do Dia) | Held item selvagem (Roubo/Golpe do Dia): gen_3_families.h |
| `ITEM_PRIMARINITE` — Primarinite | This stone enables Primarina to Mega Evolve in battle. | Não | - |
| `ITEM_PRISM_SCALE` — Prism Scale | A mysterious scale that evolves a certain Pokémon. | Sim | Item ball no mapa (object_event): Route47 \| Script (dado ao jogador): …a/maps/MauvilleCity_GameCorner/scripts.inc:1620, …a/maps/MauvilleCity_GameCorner/scripts.pory:810 |
| `ITEM_PROTECTOR` — Protector | Loved by a certain Pokémon. It's stiff and heavy. | Sim | Item ball no mapa (object_event): Kitakami_Temple_Storage |
| `ITEM_PROTEIN_EX` — Protein EX | Maximizes the effort value of a Pokémon's Attack. | Sim | Item ball no mapa (object_event): CeruleanCave_B1F, KitakamiWell_B1F, RuinsOfAlph_WordsRoom2 \| Loja / pokemart: …/scripts.pory (BattleFrontier_BattleTowerLobby), …Lobby/scripts.pory (GoldenrodBattleAracdeLobby), …eLobby/scripts.inc (GoldenrodBattleAracdeLobby) (+1) |
| `ITEM_PSYCHIC_TERA_SHARD` — Psychic Tera Shard | These shards may form when a Tera Pokémon faints. | Não | - |
| `ITEM_PURPLE_NECTAR` — Purple Nectar | Flower nectar that changes the form of certain Pokémon. | Sim | Loja / pokemart: data/maps/OlivineCity/scripts.inc (OlivineCity), data/maps/OlivineCity/scripts.pory (OlivineCity) |
| `ITEM_QUIET_MINT` — Quiet Mint | Can be smelled. It ups Sp. Atk, but reduces Speed. | Sim | Item escondido (hidden_item): Route41 \| Loja / pokemart: …aps/Route40_House5/scripts.inc (Route40_House5), …owerShop/scripts.inc (GoldenrodCity_FlowerShop), …ps/Route40_House5/scripts.pory (Route40_House5) (+1) |
| `ITEM_RARE_BONE` — Rare Bone | A very rare bone. It can be sold at a high price. | Sim | Item escondido (hidden_item): Route46 |
| `ITEM_RARE_CANDY` — Rare Candy | Raises the level of a Pokémon by one. | Sim | Favor Lady (Lilycove): …c/data/lilycove_lady.h (tabela conferida a mao) \| Item ball no mapa (object_event): CeruleanCave_1F, MtSilver_Snow, Route119 (+4) \| Item escondido (hidden_item): LakeOfRage, Route26, RuinsOfAlph_Outside \| Pickup (habilidade): battle_script_commands.c sPickupTable \| Script (dado ao jogador): data/maps/VermilionCity_FanClub/scripts.inc:14, …aps/Route110_TrickHouseEntrance/scripts.inc:339 \| Script (finditem): data/maps/VioletCity/scripts.inc:450, data/maps/VioletCity/scripts.pory:225 |
| `ITEM_RASH_MINT` — Rash Mint | Can be smelled. It ups Sp. Atk, but reduces Sp. Def. | Sim | Loja / pokemart: …aps/Route40_House5/scripts.inc (Route40_House5), …owerShop/scripts.inc (GoldenrodCity_FlowerShop), …ps/Route40_House5/scripts.pory (Route40_House5) (+1) |
| `ITEM_REAPER_CLOTH` — Reaper Cloth | Loved by a certain Pokémon. Imbued with spirit energy. | Sim | Item ball no mapa (object_event): KitakamiMountain4F |
| `ITEM_RED_APRICORN` — Red Apricorn | A red apricorn. It assails your nostrils. | Não | - |
| `ITEM_RED_NECTAR` — Red Nectar | Flower nectar that changes the form of certain Pokémon. | Sim | Loja / pokemart: data/maps/OlivineCity/scripts.inc (OlivineCity), data/maps/OlivineCity/scripts.pory (OlivineCity) |
| `ITEM_RED_SCARF` — Red Scarf | A hold item that raises Cool in Contests. | Não (só em mapa fora da campanha) | Mencionado em script (verificar): …aps/SlateportCity_PokemonFanClub/scripts.inc:73 \| Script (dado ao jogador): …aps/SlateportCity_PokemonFanClub/scripts.inc:77 |
| `ITEM_RED_SHARD` — Red Shard | A shard from an ancient item. Can be sold cheaply. | Sim | Rock Smash: …c/data/lilycove_lady.h (tabela conferida a mao) |
| `ITEM_RELAXED_MINT` — Relaxed Mint | Can be smelled. It ups Defense, but reduces Speed. | Sim | Loja / pokemart: …aps/Route40_House5/scripts.inc (Route40_House5), …owerShop/scripts.inc (GoldenrodCity_FlowerShop), …ps/Route40_House5/scripts.pory (Route40_House5) (+1) |
| `ITEM_RELIC_BAND` — Relic Band | An old bracelet. It sells at a high price. | Não | - |
| `ITEM_RELIC_COPPER` — Relic Copper | A copper coin used long ago. It sells at a high price. | Não | - |
| `ITEM_RELIC_CROWN` — Relic Crown | An old crown. It sells at a high price. | Não | - |
| `ITEM_RELIC_GOLD` — Relic Gold | A gold coin used long ago. It sells at a high price. | Sim | Item ball no mapa (object_event): VajraPyramidFloor3 \| Script (finditem): data/maps/VajraPyramidFloor1/scripts.inc:11, data/maps/VajraPyramidFloor1/scripts.pory:10, data/maps/VajraPyramidFloor2/scripts.inc:11 (+7) |
| `ITEM_RELIC_SILVER` — Relic Silver | A silver coin used long ago. It sells at a high price. | Não | - |
| `ITEM_RELIC_STATUE` — Relic Statue | An old statue. It sells at a high price. | Não | - |
| `ITEM_RELIC_VASE` — Relic Vase | A vase made long ago. It sells at a high price. | Não | - |
| `ITEM_REPEL` — Repel | Repels weak wild Pokémon for 100 steps. | Sim | Loja / pokemart: data/maps/MtMoon_Shop/scripts.inc (MtMoon_Shop), …F/scripts.inc (LilycoveCity_DepartmentStore_2F) \| Pickup (habilidade): battle_script_commands.c sPickupTable |
| `ITEM_RETRO_MAIL` — Retro Mail | Mail featuring the drawings of three Pokémon. | Sim | Loja / pokemart: …hornCity_Mart/scripts.inc (BlackthornCity_Mart), …ornCity_Mart/scripts.pory (BlackthornCity_Mart) |
| ★ `ITEM_REVERSE_CANDY` — Reverse Candy | Lowers the level of a Pokémon by one. | Sim | Loja / pokemart: …/scripts.inc (GoldenrodCity_DepartmentStore_3F) |
| `ITEM_RIBBON_SWEET` — Ribbon Sweet | A ribbon-shaped sweet loved by Milcery. | Não | - |
| `ITEM_RICH_MULCH` — Rich Mulch | A fertilizer that ups the number of Berries harvested. | Não | - |
| `ITEM_ROCK_TERA_SHARD` — Rock Tera Shard | These shards may form when a Tera Pokémon faints. | Não | - |
| `ITEM_ROOT_FOSSIL` — Root Fossil | A fossil of an ancient, seafloor- dwelling Pokémon. | Sim | Rock Smash: …c/data/lilycove_lady.h (tabela conferida a mao) \| Script (finditem): data/maps/PewterCity_Museum_1F/scripts.inc:9 |
| `ITEM_RUSTED_SHIELD` — Rusted Shield | A rusty shield. A hero used it to halt a disaster. | Só held item (Roubo/Golpe do Dia) | Held item de treinador (so via Roubo): trainers.party:12087, trainers.party:15248 |
| `ITEM_RUSTED_SWORD` — Rusted Sword | A rusty sword. A hero used it to halt a disaster. | Não | - |
| `ITEM_SACHET` — Sachet | A sachet of strong perfumes, loved by a certain Pokémon. | Sim | Loja / pokemart: …enter/scripts.inc (IndigoPlateau_PokemonCenter), …nter/scripts.pory (IndigoPlateau_PokemonCenter) |
| `ITEM_SAIL_FOSSIL` — Sail Fossil | A piece of a prehistoric Poké- mon's skin sail. | Sim | Rock Smash: …c/data/lilycove_lady.h (tabela conferida a mao) |
| `ITEM_SASSY_MINT` — Sassy Mint | Can be smelled. It ups Sp. Def, but reduces Speed. | Sim | Loja / pokemart: …aps/Route40_House5/scripts.inc (Route40_House5), …owerShop/scripts.inc (GoldenrodCity_FlowerShop), …ps/Route40_House5/scripts.pory (Route40_House5) (+1) |
| `ITEM_SERIOUS_MINT` — Serious Mint | Can be smelled. It makes each stat grow equally. | Sim | Loja / pokemart: …aps/Route40_House5/scripts.inc (Route40_House5), …owerShop/scripts.inc (GoldenrodCity_FlowerShop), …ps/Route40_House5/scripts.pory (Route40_House5) (+1) |
| `ITEM_SHADOW_MAIL` — Shadow Mail | A Duskull-print Mail to be held by a Pokémon. | Sim | Item ball no mapa (object_event): Route110_TrickHousePuzzle3 |
| `ITEM_SHINY_STONE` — Shiny Stone | Makes certain species of Pokémon evolve. | Sim | Loja / pokemart: …enter/scripts.inc (IndigoPlateau_PokemonCenter), …nter/scripts.pory (IndigoPlateau_PokemonCenter) \| Script (dado ao jogador, var computado): data/scripts/bug_contest.inc:144 |
| ★ `ITEM_SHIN_GENOME` — Shiny Genome | A genome capable of turning Pokémon shiny. | Sim | Loja / pokemart: …Lobby/scripts.pory (GoldenrodBattleAracdeLobby), …eLobby/scripts.inc (GoldenrodBattleAracdeLobby) \| Script (dado ao jogador): data/maps/BattleCafe/scripts.inc:1793, data/maps/BattleCafe/scripts.pory:973, data/maps/Route40_House4/scripts.inc:192 (+1) |
| `ITEM_SHOAL_SALT` — Shoal Salt | Salt obtained from deep inside the Shoal Cave. | Não (só em mapa fora da campanha) | Mencionado em script (verificar): …ps/ShoalCave_LowTideEntranceRoom/scripts.inc:23, …ps/ShoalCave_LowTideEntranceRoom/scripts.inc:43, …ps/ShoalCave_LowTideEntranceRoom/scripts.inc:62 \| Script (dado ao jogador): …/maps/ShoalCave_LowTideLowerRoom/scripts.inc:20, …maps/ShoalCave_LowTideInnerRoom/scripts.inc:114, …maps/ShoalCave_LowTideInnerRoom/scripts.inc:130 (+1) |
| `ITEM_SHOAL_SHELL` — Shoal Shell | A seashell found deep inside the Shoal Cave. | Não (só em mapa fora da campanha) | Mencionado em script (verificar): …ps/ShoalCave_LowTideEntranceRoom/scripts.inc:25, …ps/ShoalCave_LowTideEntranceRoom/scripts.inc:48, …ps/ShoalCave_LowTideEntranceRoom/scripts.inc:64 \| Script (dado ao jogador): …/maps/ShoalCave_LowTideInnerRoom/scripts.inc:65, …/maps/ShoalCave_LowTideInnerRoom/scripts.inc:81, …/maps/ShoalCave_LowTideInnerRoom/scripts.inc:92 (+1) |
| `ITEM_SKULL_FOSSIL` — Skull Fossil | A piece of a prehistoric Poké- mon's collar. | Não | - |
| ★ `ITEM_SOGGY_HERB` — Soggy Herb | An herb that lowers one Pokémon's Sp. Def IV by one. | Sim | Loja / pokemart: …/scripts.pory (GoldenrodCity_UndergroundTunnel), …l/scripts.inc (GoldenrodCity_UndergroundTunnel) |
| `ITEM_STABLE_MULCH` — Stable Mulch | A fertilizer that ups the life time of Berry trees. | Sim | Loja / pokemart: …owerShop/scripts.inc (GoldenrodCity_FlowerShop), …werShop/scripts.pory (GoldenrodCity_FlowerShop) |
| `ITEM_STARDUST` — Stardust | Beautiful red sand. Can be sold at a high price. | Sim | Hidden Grotto (item raro): src/hidden_grotto.c \| Item ball no mapa (object_event): GoldenrodCity_UndergroundTunnel, Route39, Route47 (+1) \| Item escondido (hidden_item): CherrygroveCity, Route35 |
| `ITEM_STAR_PIECE` — Star Piece | A red gem shard. It would sell for a very high price. | Sim | Item escondido (hidden_item): SnowtopMountain_B1F, VajraDesertEast |
| `ITEM_STAR_SWEET` — Star Sweet | A star-shaped sweet loved by Milcery. | Não | - |
| `ITEM_STEEL_TERA_SHARD` — Steel Tera Shard | These shards may form when a Tera Pokémon faints. | Não | - |
| `ITEM_STELLAR_TERA_SHARD` — Stellar Tera Shard | These shards may form when a Tera Pokémon faints. | Não | - |
| `ITEM_STRANGE_SOUVENIR` — Strange Souvenir | An ornament that depicts a Pokémon from another region. | Sim | Loja / pokemart: data/maps/OlivineCity/scripts.inc (OlivineCity), data/maps/OlivineCity/scripts.pory (OlivineCity) |
| `ITEM_STRAWBERRY_SWEET` — Strawberry Sweet | Strawberry-shaped sweet loved by Milcery. | Não | - |
| `ITEM_SUN_STONE` — Sun Stone | Makes certain species of Pokémon evolve. | Sim | Hidden Grotto (item raro): src/hidden_grotto.c \| Item ball no mapa (object_event): Route43, VajraDesertEast \| Loja / pokemart: …enter/scripts.inc (IndigoPlateau_PokemonCenter), …nter/scripts.pory (IndigoPlateau_PokemonCenter) \| Pickup (habilidade): battle_script_commands.c sPickupTable \| Script (dado ao jogador): …a/maps/MauvilleCity_GameCorner/scripts.inc:1700, …a/maps/MauvilleCity_GameCorner/scripts.pory:850 \| Script (dado ao jogador, var computado): data/maps/Route25_BillsHouse/scripts.inc:100, data/scripts/bug_contest.inc:132 |
| `ITEM_SUPER_LURE` — Super Lure | Makes Pokémon more likely to appear for 200 steps. | Não | - |
| `ITEM_SUPER_REPEL` — Super Repel | Repels weak wild Pokémon for 200 steps. | Sim | Item ball no mapa (object_event): Route119 \| Item escondido (hidden_item): SnowtopMountainOutside \| Loja / pokemart: …F/scripts.inc (LilycoveCity_DepartmentStore_2F), …arborTown_Mart/scripts.inc (FallarborTown_Mart) \| Pickup (habilidade): battle_script_commands.c sPickupTable |
| `ITEM_SURPRISE_MULCH` — Surprise Mulch | A fertilizer that ups the chance of Berry mutations. | Não | - |
| `ITEM_SWAP_SNACK` — Swap Snack | ????? | Não | - |
| `ITEM_SWEET_APPLE` — Sweet Apple | A very sweet apple that makes certain Pokémon evolve. | Sim | Loja / pokemart: …aps/Route40_House5/scripts.inc (Route40_House5), …ps/Route40_House5/scripts.pory (Route40_House5) |
| `ITEM_SYRUPY_APPLE` — Syrupy Apple | A very syrupy apple that makes certain Pokémon evolve. | Sim | Loja / pokemart: …aps/Route40_House5/scripts.inc (Route40_House5), …ps/Route40_House5/scripts.pory (Route40_House5) |
| `ITEM_TART_APPLE` — Tart Apple | A very tart apple that makes certain Pokémon evolve. | Sim | Loja / pokemart: …aps/Route40_House5/scripts.inc (Route40_House5), …ps/Route40_House5/scripts.pory (Route40_House5) |
| `ITEM_THUNDER_STONE` — Thunder Stone | Makes certain species of Pokémon evolve. | Sim | Item ball no mapa (object_event): OlivineCity_Lighthouse, RuinsOfAlph_PuzzleAndRewardChambers \| Loja / pokemart: …enter/scripts.inc (IndigoPlateau_PokemonCenter), …nter/scripts.pory (IndigoPlateau_PokemonCenter) \| Script (dado ao jogador): …a/maps/MauvilleCity_GameCorner/scripts.inc:1778, …a/maps/MauvilleCity_GameCorner/scripts.pory:889 \| Script (dado ao jogador, var computado): data/scripts/bug_contest.inc:173, …e124_DivingTreasureHuntersHouse/scripts.inc:227 |
| `ITEM_TIMID_MINT` — Timid Mint | Can be smelled. It ups Speed, but reduces Attack. | Sim | Loja / pokemart: …aps/Route40_House5/scripts.inc (Route40_House5), …owerShop/scripts.inc (GoldenrodCity_FlowerShop), …ps/Route40_House5/scripts.pory (Route40_House5) (+1) |
| `ITEM_TINY_BAMBOO_SHOOT` — Tiny Bamboo Shoot | A small and rare bamboo shoot. Best sold to gourmands. | Não | - |
| `ITEM_TINY_MUSHROOM` — Tiny Mushroom | A plain mushroom that would sell at a cheap price. | Sim | Item escondido (hidden_item): IlexForest \| Pickup (habilidade): battle_script_commands.c sPickupTable |
| `ITEM_TROPIC_MAIL` — Tropic Mail | A Bellossom-print Mail to be held by a Pokémon. | Sim | Item ball no mapa (object_event): Route110_TrickHousePuzzle7 |
| `ITEM_TWICE_SPICED_RADISH` — Twice-Spiced Radish | ????? | Não | - |
| `ITEM_TYPHLOSIONITE` — Typhlosionite | This stone enables Typhlosion to Mega Evolve in battle. | Não | - |
| `ITEM_UNREMARKABLE_TEACUP` — Unremarkable Teacup | A cracked teacup that makes certain Pokémon evolve. | Sim | Hidden Grotto (item raro): src/hidden_grotto.c \| Loja / pokemart: data/maps/OlivineCity/scripts.inc (OlivineCity), data/maps/OlivineCity/scripts.pory (OlivineCity) |
| `ITEM_UNUSED_887` — Unused 887 | ????? | Não | - |
| `ITEM_UPGRADE` — Upgrade | A peculiar box made by Silph Co. | Sim | Loja / pokemart: …aps/SafariZoneGate/scripts.inc (SafariZoneGate), …ps/SafariZoneGate/scripts.pory (SafariZoneGate) |
| `ITEM_WATER_STONE` — Water Stone | Makes certain species of Pokémon evolve. | Sim | Item ball no mapa (object_event): RuinsOfAlph_PuzzleAndRewardChambers \| Loja / pokemart: …aps/SafariZoneGate/scripts.inc (SafariZoneGate), …enter/scripts.inc (IndigoPlateau_PokemonCenter), …nter/scripts.pory (IndigoPlateau_PokemonCenter) (+1) \| Script (dado ao jogador): …a/maps/MauvilleCity_GameCorner/scripts.inc:1804, …a/maps/MauvilleCity_GameCorner/scripts.pory:902 \| Script (dado ao jogador, var computado): data/scripts/bug_contest.inc:177, …e124_DivingTreasureHuntersHouse/scripts.inc:232 |
| `ITEM_WATER_TERA_SHARD` — Water Tera Shard | These shards may form when a Tera Pokémon faints. | Não | - |
| `ITEM_WAVE_MAIL` — Wave Mail | A Wailmer-print Mail to be held by a Pokémon. | Sim | Item ball no mapa (object_event): Route110_TrickHousePuzzle2 \| Loja / pokemart: …F/scripts.inc (LilycoveCity_DepartmentStore_2F) |
| `ITEM_WHIPPED_DREAM` — Whipped Dream | A soft and sweet treat loved by a certain Pokémon. | Sim | Loja / pokemart: …enter/scripts.inc (IndigoPlateau_PokemonCenter), …nter/scripts.pory (IndigoPlateau_PokemonCenter) |
| `ITEM_WHITE_APRICORN` — White Apricorn | A white apricorn. It doesn't smell like anything. | Não | - |
| `ITEM_WHITE_FLUTE` — White Flute | A glass flute that lures wild Pokémon. | Sim | Item ball no mapa (object_event): Route47 |
| `ITEM_WISHING_PIECE` — Wishing Piece | Throw into a {PKMN} Den to attract Dynamax Pokémon. | Não | - |
| ★ `ITEM_WITHERED_HERB` — Withered Herb | An herb that lowers one Pokémon's HP IV by one. | Sim | Loja / pokemart: …/scripts.pory (GoldenrodCity_UndergroundTunnel), …l/scripts.inc (GoldenrodCity_UndergroundTunnel) |
| `ITEM_WOOD_MAIL` — Wood Mail | A Slakoth-print Mail to be held by a Pokémon. | Sim | Item ball no mapa (object_event): Route110_TrickHousePuzzle3 \| Loja / pokemart: …/VioletCity_Mart/scripts.pory (VioletCity_Mart), …s/VioletCity_Mart/scripts.inc (VioletCity_Mart) |
| `ITEM_X_ACCURACY` — X Accuracy | Sharply raises move accuracy during one battle. Raises accuracy of attack moves during one battle. | Sim | Loja / pokemart: …/scripts.inc (GoldenrodCity_DepartmentStore_3F), …ill_Entrance/scripts.inc (TrainerHill_Entrance) |
| `ITEM_X_ATTACK` — X Attack | Sharply raises stat Attack during one battle. Raises the stat Attack during one battle. | Sim | Loja / pokemart: …/scripts.inc (GoldenrodCity_DepartmentStore_3F), …arborTown_Mart/scripts.inc (FallarborTown_Mart), …ill_Entrance/scripts.inc (TrainerHill_Entrance) |
| `ITEM_X_DEFENSE` — X Defense | Sharply raises stat Defense during one battle. Raises the stat Defense during one battle. | Sim | Loja / pokemart: …/scripts.inc (GoldenrodCity_DepartmentStore_3F), …arborTown_Mart/scripts.inc (FallarborTown_Mart), …ill_Entrance/scripts.inc (TrainerHill_Entrance) |
| `ITEM_X_SPEED` — X Speed | Sharply raises stat Speed during one battle. Raises the stat Speed during one battle. | Sim | Item ball no mapa (object_event): MauvilleCity \| Loja / pokemart: …/scripts.inc (GoldenrodCity_DepartmentStore_3F), …arborTown_Mart/scripts.inc (FallarborTown_Mart), …ill_Entrance/scripts.inc (TrainerHill_Entrance) |
| `ITEM_X_SP_ATK` — X Sp. Atk | Sharply raises stat Sp. Atk during one battle. Raises the stat Sp. Atk during one battle. | Sim | Loja / pokemart: …/scripts.inc (GoldenrodCity_DepartmentStore_3F), …arborTown_Mart/scripts.inc (FallarborTown_Mart), …ill_Entrance/scripts.inc (TrainerHill_Entrance) |
| `ITEM_X_SP_DEF` — X Sp. Def | Sharply raises stat Sp. Def during one battle. Raises the stat Sp. Def during one battle. | Não | - |
| `ITEM_YELLOW_APRICORN` — Yellow Apricorn | A yellow apricorn. It has an invigor- ating scent. | Não | - |
| `ITEM_YELLOW_NECTAR` — Yellow Nectar | Flower nectar that changes the form of certain Pokémon. | Sim | Loja / pokemart: data/maps/OlivineCity/scripts.inc (OlivineCity), data/maps/OlivineCity/scripts.pory (OlivineCity) |
| `ITEM_YELLOW_SCARF` — Yellow Scarf | A hold item that raises Tough in Contests. | Não (só em mapa fora da campanha) | Mencionado em script (verificar): …ps/SlateportCity_PokemonFanClub/scripts.inc:113 \| Script (dado ao jogador): …ps/SlateportCity_PokemonFanClub/scripts.inc:117 |
| `ITEM_YELLOW_SHARD` — Yellow Shard | A shard from an ancient item. Can be sold cheaply. | Sim | Rock Smash: …c/data/lilycove_lady.h (tabela conferida a mao) |
| `ITEM_ZINC_EX` — Zinc EX | Maximizes the effort value of a Pokémon's Sp. Def. | Sim | Item ball no mapa (object_event): CeruleanCave_B1F, EcruteakCity \| Loja / pokemart: …/scripts.pory (BattleFrontier_BattleTowerLobby), …Lobby/scripts.pory (GoldenrodBattleAracdeLobby), …eLobby/scripts.inc (GoldenrodBattleAracdeLobby) (+1) |

## Remédios (Medicine) (65)

| Item | O que faz | Obtível in-game? | Como se obtém |
|---|---|---|---|
| `ITEM_ANTIDOTE` — Antidote | Heals a poisoned Pokémon. | Sim | Item escondido (hidden_item): Route31 \| Loja / pokemart: …F/scripts.inc (LilycoveCity_DepartmentStore_2F), …arborTown_Mart/scripts.inc (FallarborTown_Mart), …ill_Entrance/scripts.inc (TrainerHill_Entrance) (+2) \| Script (finditem): data/maps/Route31/scripts.inc:174, data/maps/Route31/scripts.pory:87 |
| `ITEM_AWAKENING` — Awakening | Awakens a sleeping Pokémon. | Sim | Item ball no mapa (object_event): UnionCave_1F \| Item escondido (hidden_item): Route34 \| Loja / pokemart: …F/scripts.inc (LilycoveCity_DepartmentStore_2F), …ill_Entrance/scripts.inc (TrainerHill_Entrance) |
| `ITEM_BERRY_JUICE` — Berry Juice | A 100% pure juice that restores HP by 20 points. | Sim | Script (dado ao jogador): …/maps/MauvilleCity_GameCorner/scripts.pory:1272, …a/maps/MauvilleCity_GameCorner/scripts.inc:2544 |
| `ITEM_BIG_MALASADA` — Big Malasada | Heals all the status problems of one Pokémon. | Sim | Loja / pokemart: …aps/Route40_House5/scripts.inc (Route40_House5), …ps/Route40_House5/scripts.pory (Route40_House5) |
| `ITEM_BLUE_FLUTE` — Blue Flute | A glass flute that awakens sleeping Pokémon. | Não (só em mapa fora da campanha) | Mencionado em script (verificar): data/maps/Route113_GlassWorkshop/scripts.inc:236, data/maps/Route113_GlassWorkshop/scripts.inc:75 \| Script (dado ao jogador, var computado): data/maps/Route113_GlassWorkshop/scripts.inc:236, data/maps/Route113_GlassWorkshop/scripts.inc:75 |
| `ITEM_BURN_HEAL` — Burn Heal | Heals Pokémon of a burn. | Sim | Item escondido (hidden_item): BurnedTower_1F \| Loja / pokemart: …F/scripts.inc (LilycoveCity_DepartmentStore_2F) |
| `ITEM_CALCIUM` — Calcium | Raises the base Sp. Atk stat of one Pokémon. | Sim | Item ball no mapa (object_event): Route12 \| Item escondido (hidden_item): BurnedTower_B1F \| Loja / pokemart: …/scripts.inc (GoldenrodCity_DepartmentStore_3F), …ipts.inc (BattleFrontier_ExchangeServiceCorner) |
| `ITEM_CARBOS` — Carbos | Raises the base Speed stat of one Pokémon. | Sim | Item ball no mapa (object_event): IcePath_B2F, MtMortar_B1F, Route2 \| Item escondido (hidden_item): Route36 \| Loja / pokemart: …/scripts.inc (GoldenrodCity_DepartmentStore_3F), …ipts.inc (BattleFrontier_ExchangeServiceCorner) |
| `ITEM_CASTELIACONE` — Casteliacone | Heals all the status problems of one Pokémon. | Sim | Loja / pokemart: …aps/Route40_House5/scripts.inc (Route40_House5), …ps/Route40_House5/scripts.pory (Route40_House5) |
| `ITEM_CLEVER_FEATHER` — Clever Feather | An item that raises the Innate Sp. Def value of a Pokémon. | Sim | Loja / pokemart: …cripts.pory (BattleFrontier_BattleFactoryLobby), …scripts.inc (BattleFrontier_BattleFactoryLobby) \| Vara de pescar (item bonus): …c/data/lilycove_lady.h (tabela conferida a mao) |
| `ITEM_CLEVER_MOCHI` — Clever Mochi | An item that raises the base Sp. Def. of a Pokémon. | Não | - |
| `ITEM_ELIXIR` — Elixir | Restores the PP of all moves by 10. | Sim | Item ball no mapa (object_event): DarkCave_SouthSide, MtMortar_1F_South, MtMortar_2F (+5) \| Item escondido (hidden_item): IcePath_B2F \| Loja / pokemart: …Frontier_Mart/scripts.inc (BattleFrontier_Mart) \| Script (dado ao jogador, var computado): …aps/GoldenrodCity_RadioTower_2F/scripts.inc:416, …ps/GoldenrodCity_RadioTower_2F/scripts.pory:208 |
| `ITEM_ENERGY_POWDER` — Energy Powder | A bitter powder that restores HP by 60 points. by 50 points. | Sim | Item ball no mapa (object_event): RuinsOfAlph_PuzzleAndRewardChambers \| Loja / pokemart: …/scripts.pory (GoldenrodCity_UndergroundTunnel), …l/scripts.inc (GoldenrodCity_UndergroundTunnel) |
| `ITEM_ENERGY_ROOT` — Energy Root | A bitter root that restores HP by 120 points. by 200 points. | Sim | Item ball no mapa (object_event): RuinsOfAlph_PuzzleAndRewardChambers \| Loja / pokemart: …/scripts.pory (GoldenrodCity_UndergroundTunnel), …l/scripts.inc (GoldenrodCity_UndergroundTunnel) |
| `ITEM_ETHER` — Ether | Restores the PP of a selected move by 10. | Sim | Item ball no mapa (object_event): BurnedTower_1F, IlexForest, MtMortar_2F (+1) \| Item escondido (hidden_item): DarkCave_SouthSide, Route29, Route33 \| Loja / pokemart: …Frontier_Mart/scripts.inc (BattleFrontier_Mart) \| Pickup (habilidade): battle_script_commands.c sPickupTable |
| `ITEM_FINE_REMEDY` — Fine Remedy | A bitter powder that restores HP by 60 points. by 50 points. | Não | - |
| `ITEM_FRESH_WATER` — Fresh Water | A mineral water that restores HP by 30 points. by 50 points. | Sim | Loja / pokemart: data/maps/MtMoon_Shop/scripts.inc (MtMoon_Shop), …aps/Route40_House5/scripts.inc (Route40_House5), …ps/Route40_House5/scripts.pory (Route40_House5) \| Script (finditem): data/maps/BattleCafe/scripts.inc:2381, data/maps/BattleCafe/scripts.pory:1317 |
| `ITEM_FULL_HEAL` — Full Heal | Heals all the status problems of one Pokémon. | Sim | Item ball no mapa (object_event): IcePath_B2F, IlexForest, RocketHideout_B3F (+3) \| Item escondido (hidden_item): Route30, Route37, VajraDesert \| Loja / pokemart: …F/scripts.inc (LilycoveCity_DepartmentStore_2F), …ill_Entrance/scripts.inc (TrainerHill_Entrance) \| Pickup (habilidade): battle_script_commands.c sPickupTable |
| `ITEM_FULL_RESTORE` — Full Restore | Fully restores the HP and status of a Pokémon. | Sim | Item ball no mapa (object_event): GoldenrodCity_UndergroundSwitches, MtSilver_1F_WaterfallRoom, RuinsOfAlph_PuzzleAndRewardChambers (+7) \| Item escondido (hidden_item): Route45 \| Loja / pokemart: …ill_Entrance/scripts.inc (TrainerHill_Entrance) \| Script (dado ao jogador, var computado): …aps/GoldenrodCity_RadioTower_2F/scripts.inc:406, …ps/GoldenrodCity_RadioTower_2F/scripts.pory:203 |
| `ITEM_GENIUS_FEATHER` — Genius Feather | An item that raises the Innate Sp. Atk value of a Pokémon. | Sim | Loja / pokemart: …cripts.pory (BattleFrontier_BattleFactoryLobby), …scripts.inc (BattleFrontier_BattleFactoryLobby) \| Vara de pescar (item bonus): …c/data/lilycove_lady.h (tabela conferida a mao) |
| `ITEM_GENIUS_MOCHI` — Genius Mochi | An item that raises the base Sp. Atk. of a Pokémon. | Não | - |
| `ITEM_HEALTH_FEATHER` — Health Feather | An item that raises the Innate HP value of a Pokémon. | Sim | Loja / pokemart: …cripts.pory (BattleFrontier_BattleFactoryLobby), …scripts.inc (BattleFrontier_BattleFactoryLobby) \| Vara de pescar (item bonus): …c/data/lilycove_lady.h (tabela conferida a mao) |
| `ITEM_HEALTH_MOCHI` — Health Mochi | An item that raises the base HP of a Pokémon. | Não | - |
| `ITEM_HEAL_POWDER` — Heal Powder | A bitter powder that heals all status problems. | Sim | Item ball no mapa (object_event): RuinsOfAlph_PuzzleAndRewardChambers \| Loja / pokemart: …/scripts.pory (GoldenrodCity_UndergroundTunnel), …l/scripts.inc (GoldenrodCity_UndergroundTunnel) |
| `ITEM_HP_UP` — HP Up | Raises the base HP of one Pokémon. | Sim | Item ball no mapa (object_event): Route4, VictoryRoadKanto_B1F \| Item escondido (hidden_item): Route38 \| Loja / pokemart: …/scripts.inc (GoldenrodCity_DepartmentStore_3F), …ipts.inc (BattleFrontier_ExchangeServiceCorner) \| Script (dado ao jogador): data/maps/VermilionCity/scripts.inc:191, …/maps/Gate_GoldenrodCity_Route35/scripts.inc:84, …maps/Gate_GoldenrodCity_Route35/scripts.pory:42 |
| `ITEM_HYPER_POTION` — Hyper Potion | Restores the HP of a Pokémon by 120 points. 200 points. | Sim | Item ball no mapa (object_event): GoldenrodCity_DepartmentStoreBasement, OlivineCity_Lighthouse, RocketHideout (+4) \| Item escondido (hidden_item): Route39 \| Loja / pokemart: …F/scripts.inc (LilycoveCity_DepartmentStore_2F), …ill_Entrance/scripts.inc (TrainerHill_Entrance) \| Pickup (habilidade): battle_script_commands.c sPickupTable \| Script (finditem): data/maps/VioletCity/scripts.inc:466, data/maps/VioletCity/scripts.pory:233 |
| `ITEM_ICE_HEAL` — Ice Heal | Defrosts a frozen Pokémon. | Sim | Loja / pokemart: …F/scripts.inc (LilycoveCity_DepartmentStore_2F) |
| `ITEM_IRON` — Iron | Raises the base Defense stat of one Pokémon. | Sim | Item ball no mapa (object_event): IcePath_B1F, MtMortar_2F, RockTunnel_1F \| Item escondido (hidden_item): Route48 \| Loja / pokemart: …/scripts.inc (GoldenrodCity_DepartmentStore_3F), …ipts.inc (BattleFrontier_ExchangeServiceCorner) |
| `ITEM_JUBILIFE_MUFFIN` — Jubilife Muffin | Heals all the status problems of one Pokémon. | Não | - |
| `ITEM_LAVA_COOKIE` — Lava Cookie | A local specialty that heals all status problems. | Sim | Loja / pokemart: …aps/Route40_House5/scripts.inc (Route40_House5), …ps/Route40_House5/scripts.pory (Route40_House5) |
| `ITEM_LEMONADE` — Lemonade | A very sweet drink that restores HP by 70 points. by 80 points. | Sim | Loja / pokemart: data/maps/MtMoon_Shop/scripts.inc (MtMoon_Shop), …aps/Route40_House5/scripts.inc (Route40_House5), …ps/Route40_House5/scripts.pory (Route40_House5) |
| `ITEM_LUMIOSE_GALETTE` — Lumiose Galette | Heals all the status problems of one Pokémon. | Sim | Loja / pokemart: …aps/Route40_House5/scripts.inc (Route40_House5), …ps/Route40_House5/scripts.pory (Route40_House5) |
| `ITEM_MAX_ELIXIR` — Max Elixir | Fully restores the PP of a Pokémon's moves. | Sim | Item ball no mapa (object_event): CeruleanCave_1F \| Loja / pokemart: …Frontier_Mart/scripts.inc (BattleFrontier_Mart) \| Script (dado ao jogador, var computado): …aps/GoldenrodCity_RadioTower_2F/scripts.inc:426, …ps/GoldenrodCity_RadioTower_2F/scripts.pory:213 |
| `ITEM_MAX_ETHER` — Max Ether | Fully restores the PP of a selected move. | Sim | Item ball no mapa (object_event): KitakamiBorder, ViridianForest \| Loja / pokemart: …Frontier_Mart/scripts.inc (BattleFrontier_Mart) \| Pickup (habilidade): battle_script_commands.c sPickupTable |
| `ITEM_MAX_HONEY` — Max Honey | Revives a fainted Pokémon with all its HP. | Não | - |
| `ITEM_MAX_POTION` — Max Potion | Fully restores the HP of a Pokémon. | Sim | Item ball no mapa (object_event): DragonsDen_Cavern, MtMortar_1F_North, TinTower_4F (+2) \| Loja / pokemart: …F/scripts.inc (LilycoveCity_DepartmentStore_2F), …ill_Entrance/scripts.inc (TrainerHill_Entrance) \| Pickup (habilidade): battle_script_commands.c sPickupTable |
| `ITEM_MAX_REVIVE` — Max Revive | Revives a fainted Pokémon with all its HP. | Sim | Item ball no mapa (object_event): CeruleanCave_B2F, GoldenrodCity_UndergroundSwitches, KitakamiMountain3F (+7) \| Item escondido (hidden_item): Route28, Route44 \| Loja / pokemart: …Frontier_Mart/scripts.inc (BattleFrontier_Mart) \| Pickup (habilidade): battle_script_commands.c sPickupTable |
| `ITEM_MOOMOO_MILK` — Moomoo Milk | A nutritious milk that restores HP by 100 points. | Sim | Script (additem): data/maps/Route39_FarmHouse/scripts.inc:45 |
| `ITEM_MUSCLE_FEATHER` — Muscle Feather | An item that raises the Innate Attack value of a Pokémon. | Sim | Item ball no mapa (object_event): UnionCave_1F \| Loja / pokemart: …cripts.pory (BattleFrontier_BattleFactoryLobby), …scripts.inc (BattleFrontier_BattleFactoryLobby) \| Vara de pescar (item bonus): …c/data/lilycove_lady.h (tabela conferida a mao) |
| `ITEM_MUSCLE_MOCHI` — Muscle Mochi | An item that raises the base Attack of a Pokémon. | Não | - |
| `ITEM_OLD_GATEAU` — Old Gateau | Heals all the status problems of one Pokémon. | Sim | Loja / pokemart: …aps/Route40_House5/scripts.inc (Route40_House5), …ps/Route40_House5/scripts.pory (Route40_House5) |
| `ITEM_PARALYZE_HEAL` — Paralyze Heal | Heals a paralyzed Pokémon. | Sim | Item ball no mapa (object_event): SproutTower_1F \| Item escondido (hidden_item): Route40 \| Loja / pokemart: …F/scripts.inc (LilycoveCity_DepartmentStore_2F), …arborTown_Mart/scripts.inc (FallarborTown_Mart), …ill_Entrance/scripts.inc (TrainerHill_Entrance) |
| `ITEM_PEWTER_CRUNCHIES` — Pewter Crunchies | Heals all the status problems of one Pokémon. | Sim | Loja / pokemart: …aps/Route40_House5/scripts.inc (Route40_House5), …ps/Route40_House5/scripts.pory (Route40_House5) |
| `ITEM_POTION` — Potion | Restores the HP of a Pokémon by 20 points. | Sim | Item ball no mapa (object_event): DarkCave_SouthSide, Route102, Route29 (+1) \| Item escondido (hidden_item): Route30 \| Loja / pokemart: …F/scripts.inc (LilycoveCity_DepartmentStore_2F), …oveCity_Mart/scripts.inc (CherrygroveCity_Mart), …veCity_Mart/scripts.pory (CherrygroveCity_Mart) \| Pickup (habilidade): battle_script_commands.c sPickupTable \| Script (dado ao jogador): data/maps/NewBarkTown_Lab/scripts.inc:744, data/maps/NewBarkTown_Lab/scripts.pory:372, data/maps/OldaleTown/scripts.inc:74 (+5) |
| `ITEM_PP_MAX` — PP Max | Raises the PP of a move to its maximum points. | Sim | Favor Lady (Lilycove): …c/data/lilycove_lady.h (tabela conferida a mao) \| Item ball no mapa (object_event): CeruleanCave_1F, GoldenrodCity_DepartmentStoreBasement, GoldenrodCity_UndergroundStorage (+1) \| Item escondido (hidden_item): VajraDesertEast, VictoryRoadKanto_B1F \| Loja / pokemart: …/scripts.pory (BattleFrontier_BattleTowerLobby), …Lobby/scripts.pory (GoldenrodBattleAracdeLobby), …eLobby/scripts.inc (GoldenrodBattleAracdeLobby) (+1) \| Script (dado ao jogador): …aps/Route110_TrickHouseEntrance/scripts.inc:383 \| Script (dado ao jogador, var computado): …aps/GoldenrodCity_RadioTower_2F/scripts.inc:466, …ps/GoldenrodCity_RadioTower_2F/scripts.pory:233 |
| `ITEM_PP_UP` — PP Up | Raises the maximum PP of a selected move. | Sim | Item ball no mapa (object_event): IcePath_1F, MtMortar_B1F, RockTunnel_1F (+1) \| Item escondido (hidden_item): IcePath_1F, IlexForest, Route47 \| Loja / pokemart: …Frontier_Mart/scripts.inc (BattleFrontier_Mart) \| Pickup (habilidade): battle_script_commands.c sPickupTable |
| `ITEM_PROTEIN` — Protein | Raises the base Attack stat of one Pokémon. | Sim | Favor Lady (Lilycove): …c/data/lilycove_lady.h (tabela conferida a mao) \| Item ball no mapa (object_event): IcePath_1F, OlivineCity_Lighthouse \| Item escondido (hidden_item): BlackthornCity \| Loja / pokemart: …/scripts.inc (GoldenrodCity_DepartmentStore_3F), …ipts.inc (BattleFrontier_ExchangeServiceCorner) |
| `ITEM_RAGE_CANDY_BAR` — Rage Candy Bar | Heals all the status problems of one Pokémon. | Sim | Script (dado ao jogador): data/maps/Mahoganytown/scripts.inc:219, data/maps/Mahoganytown/scripts.inc:252 |
| `ITEM_RED_FLUTE` — Red Flute | A glass flute that snaps Pokémon out of attraction. | Sim | Item ball no mapa (object_event): LakeOfRage |
| `ITEM_REMEDY` — Remedy | A bitter powder that restores HP by 20 points. | Não | - |
| `ITEM_RESIST_FEATHER` — Resist Feather | An item that raises the Innate Defense value of a Pokémon. | Sim | Loja / pokemart: …cripts.pory (BattleFrontier_BattleFactoryLobby), …scripts.inc (BattleFrontier_BattleFactoryLobby) \| Vara de pescar (item bonus): …c/data/lilycove_lady.h (tabela conferida a mao) |
| `ITEM_RESIST_MOCHI` — Resist Mochi | An item that raises the base Defense of a Pokémon. | Não | - |
| `ITEM_REVIVAL_HERB` — Revival Herb | A very bitter herb that revives a fainted Pokémon. | Sim | Loja / pokemart: …/scripts.pory (GoldenrodCity_UndergroundTunnel), …l/scripts.inc (GoldenrodCity_UndergroundTunnel) |
| `ITEM_REVIVE` — Revive | Revives a fainted Pokémon with half its HP. | Sim | Item ball no mapa (object_event): BurnedTower_1F, DarkCave_SouthSide, MtMortar_1F_North (+6) \| Item escondido (hidden_item): Route27, Route38, Route49 \| Loja / pokemart: …F/scripts.inc (LilycoveCity_DepartmentStore_2F), …ill_Entrance/scripts.inc (TrainerHill_Entrance) \| Pickup (habilidade): battle_script_commands.c sPickupTable \| Script (finditem): data/maps/Route46/scripts.inc:68, data/maps/Route46/scripts.pory:34 |
| `ITEM_SACRED_ASH` — Sacred Ash | Fully revives and restores all fainted Pokémon. | Sim | Item ball no mapa (object_event): RuinsOfAlph_PuzzleAndRewardChambers |
| `ITEM_SHALOUR_SABLE` — Shalour Sable | Heals all the status problems of one Pokémon. | Sim | Loja / pokemart: …aps/Route40_House5/scripts.inc (Route40_House5), …ps/Route40_House5/scripts.pory (Route40_House5) |
| `ITEM_SODA_POP` — Soda Pop | A fizzy soda drink that restores HP by 50 points. by 60 points. | Sim | Loja / pokemart: data/maps/MtMoon_Shop/scripts.inc (MtMoon_Shop), …aps/Route40_House5/scripts.inc (Route40_House5), …ps/Route40_House5/scripts.pory (Route40_House5) |
| `ITEM_SUPERB_REMEDY` — Superb Remedy | A bitter powder that restores HP by 120 points. by 200 points. | Não | - |
| `ITEM_SUPER_POTION` — Super Potion | Restores the HP of a Pokémon by 60 points. 50 points. | Sim | Item ball no mapa (object_event): IlexForest, Route34, SlowpokeWell_B1F (+1) \| Loja / pokemart: …F/scripts.inc (LilycoveCity_DepartmentStore_2F), …arborTown_Mart/scripts.inc (FallarborTown_Mart), …ill_Entrance/scripts.inc (TrainerHill_Entrance) \| Pickup (habilidade): battle_script_commands.c sPickupTable |
| `ITEM_SWEET_HEART` — Sweet Heart | A sweet chocolate that restores HP by 20 points. | Sim | Loja / pokemart: …aps/Route40_House5/scripts.inc (Route40_House5), …ps/Route40_House5/scripts.pory (Route40_House5) |
| `ITEM_SWIFT_FEATHER` — Swift Feather | An item that raises the Innate Speed value of a Pokémon. | Sim | Loja / pokemart: …cripts.pory (BattleFrontier_BattleFactoryLobby), …scripts.inc (BattleFrontier_BattleFactoryLobby) \| Vara de pescar (item bonus): …c/data/lilycove_lady.h (tabela conferida a mao) |
| `ITEM_SWIFT_MOCHI` — Swift Mochi | An item that raises the base Speed of a Pokémon. | Não | - |
| `ITEM_YELLOW_FLUTE` — Yellow Flute | A glass flute that snaps Pokémon out of confusion. | Não (só em mapa fora da campanha) | Mencionado em script (verificar): data/maps/Route113_GlassWorkshop/scripts.inc:243, data/maps/Route113_GlassWorkshop/scripts.inc:87 \| Script (dado ao jogador, var computado): data/maps/Route113_GlassWorkshop/scripts.inc:243, data/maps/Route113_GlassWorkshop/scripts.inc:87 |
| ★ `ITEM_ZEROMIN` — Zeromin | Resets all effort values of one Pokémon to zero. | Sim | Loja / pokemart: …/scripts.inc (GoldenrodCity_DepartmentStore_3F) |
| `ITEM_ZINC` — Zinc | Raises the base Sp. Def stat of one Pokémon. | Sim | Item ball no mapa (object_event): Route119 \| Item escondido (hidden_item): KitakamiBorder \| Loja / pokemart: …/scripts.inc (GoldenrodCity_DepartmentStore_3F), …ipts.inc (BattleFrontier_ExchangeServiceCorner) |

## Itens de batalha / held items (225)

| Item | O que faz | Obtível in-game? | Como se obtém |
|---|---|---|---|
| `ITEM_ABILITY_SHIELD` — Ability Shield | Ability changes are prevented for this items's holder. | Sim | Loja / pokemart: …/scripts.pory (GoldenrodCity_UndergroundTunnel), …l/scripts.inc (GoldenrodCity_UndergroundTunnel) |
| `ITEM_ABSORB_BULB` — Absorb Bulb | Raises Sp. Atk if the holder is hit by a Water-type move. | Sim | Item ball no mapa (object_event): TohjoPass |
| `ITEM_ADAMANT_CRYSTAL` — Adamant Crystal | A large, glowing gem that lets Dialga change form. | Não | - |
| `ITEM_ADAMANT_ORB` — Adamant Orb | Boosts Dialga's Dragon/Steel moves and changes form. | Sim | Script (finditem): data/maps/SpearPillarTop/scripts.inc:49, data/maps/SpearPillarTop/scripts.pory:22 |
| `ITEM_ADRENALINE_ORB` — Adrenaline Orb | This orb boosts Speed if the holder is intimidated. | Sim | Item ball no mapa (object_event): BlackthornCity |
| `ITEM_AIR_BALLOON` — Air Balloon | Makes the holder float but bursts if hit by an attack. | Sim | Loja / pokemart: …/scripts.pory (GoldenrodCity_UndergroundTunnel), …l/scripts.inc (GoldenrodCity_UndergroundTunnel) \| Script (dado ao jogador): data/maps/Route31/scripts.inc:396, data/maps/Route31/scripts.pory:219 |
| `ITEM_ALORAICHIUM_Z` — Aloraichium Z | Upgrade Alolan Raichu's Thunder- bolt into a Z-Move. | Não | - |
| `ITEM_AMULET_COIN` — Amulet Coin | Doubles money in battle if the holder takes part. | Sim | Item ball no mapa (object_event): GoldenrodCity_DepartmentStoreBasement \| Script (dado ao jogador): data/scripts/players_house.inc:373 |
| `ITEM_ASSAULT_VEST` — Assault Vest | Raises Sp. Def but prevents the use of status moves. | Sim | Item ball no mapa (object_event): RocketHideout_B3F \| Loja / pokemart: …cripts.pory (BattleFrontier_BattlePyramidLobby), …scripts.inc (BattleFrontier_BattlePyramidLobby) |
| `ITEM_BERSERK_GENE` — Berserk Gene | Sharply boosts Attack, but causes lasting confusion. | Sim | Item ball no mapa (object_event): RuinsOfAlph_PuzzleAndRewardChambers |
| `ITEM_BIG_ROOT` — Big Root | A held item that ups the power of HP-stealing moves. | Sim | Item ball no mapa (object_event): MeteorCave2 |
| `ITEM_BINDING_BAND` — Binding Band | Increases the power of binding moves when held. | Sim | Loja / pokemart: …a/maps/RintoVillage/scripts.pory (RintoVillage), …ta/maps/RintoVillage/scripts.inc (RintoVillage) |
| `ITEM_BLACK_BELT` — Black Belt | A hold item that boosts Fighting- type moves. | Sim | Script (dado ao jogador): data/maps/LakeOfRage/scripts.inc:758, data/maps/LakeOfRage/scripts.pory:379 |
| `ITEM_BLACK_GLASSES` — Black Glasses | A hold item that raises the power of Dark-type moves. | Sim | Script (dado ao jogador): data/maps/DarkCave_NorthSide/scripts.inc:14, data/maps/DarkCave_NorthSide/scripts.pory:7 |
| `ITEM_BLACK_SLUDGE` — Black Sludge | Restores HP for Poison-types. Damages all others. | Sim | Loja / pokemart: …cripts.pory (BattleFrontier_BattlePyramidLobby), …scripts.inc (BattleFrontier_BattlePyramidLobby) |
| `ITEM_BLUE_ORB` — Blue Orb | A blue, glowing orb said to contain an ancient power. | Sim | Script (finditem): …maps/Route33South_UnderwaterCave/scripts.inc:30, …maps/Route33South_UnderwaterCave/scripts.pory:9 |
| `ITEM_BLUNDER_POLICY` — Blunder Policy | Raises Speed if the user misses due to Accuracy. | Sim | Item ball no mapa (object_event): Route50 \| Loja / pokemart: …/scripts.pory (BattleFrontier_BattleTowerLobby), …y/scripts.inc (BattleFrontier_BattleTowerLobby) |
| `ITEM_BOOSTER_ENERGY` — Booster Energy | Encapsuled energy ups Pokémon with certain Abilities. | Sim | Item ball no mapa (object_event): MeteorCave1, MeteorCave2 |
| `ITEM_BRIGHT_POWDER` — Bright Powder | A hold item that casts a glare to reduce accuracy. | Sim | Loja / pokemart: …ipts.inc (BattleFrontier_ExchangeServiceCorner) \| Script (dado ao jogador): …aps/GoldenrodCity_RadioTower_4F/scripts.inc:362, …ps/GoldenrodCity_RadioTower_4F/scripts.pory:184 |
| `ITEM_BUGINIUM_Z` — Buginium Z | Upgrade Bug- type moves into Z-Moves. | Não | - |
| `ITEM_BUG_GEM` — Bug Gem | Increases the power of Bug Type moves. | Sim | Loja / pokemart: …enter/scripts.inc (IndigoPlateau_PokemonCenter), …nter/scripts.pory (IndigoPlateau_PokemonCenter) |
| `ITEM_BUG_MEMORY` — Bug Memory | A disc with Bug type data. It swaps Silvally's type. | Não | - |
| `ITEM_BURN_DRIVE` — Burn Drive | Changes Genesect's Techno Blast to Fire-type. | Não | - |
| `ITEM_CELL_BATTERY` — Cell Battery | Raises Attack if the holder is hit by an Electric move. | Sim | Item ball no mapa (object_event): RailwayCave_2F |
| `ITEM_CHARCOAL` — Charcoal | A hold item that raises the power of Fire-type moves. | Sim | Script (dado ao jogador): data/maps/AzaleaTown_House1/scripts.inc:53 |
| `ITEM_CHILL_DRIVE` — Chill Drive | Changes Genesect's Techno Blast to Ice-type. | Não | - |
| `ITEM_CHOICE_BAND` — Choice Band | Boosts Attack, but allows the use of only one move. | Sim | Loja / pokemart: …/scripts.pory (BattleFrontier_BattleTowerLobby), …ipts.inc (BattleFrontier_ExchangeServiceCorner), …y/scripts.inc (BattleFrontier_BattleTowerLobby) \| Script (dado ao jogador): data/maps/Route27/scripts.inc:386, data/maps/Route27/scripts.pory:220 |
| `ITEM_CHOICE_SCARF` — Choice Scarf | Boosts Speed, but allows the use of only one move. | Sim | Item ball no mapa (object_event): Route26North \| Loja / pokemart: …/scripts.pory (BattleFrontier_BattleTowerLobby), …y/scripts.inc (BattleFrontier_BattleTowerLobby) |
| `ITEM_CHOICE_SPECS` — Choice Specs | Boosts Sp. Atk, but allows the use of only one move. | Sim | Item ball no mapa (object_event): FoggyShore2 \| Loja / pokemart: …/scripts.pory (BattleFrontier_BattleTowerLobby), …y/scripts.inc (BattleFrontier_BattleTowerLobby) |
| `ITEM_CLEANSE_TAG` — Cleanse Tag | A hold item that helps repel wild Pokémon. | Só held item (Roubo/Golpe do Dia) | Held item selvagem (Roubo/Golpe do Dia): gen_3_families.h |
| `ITEM_CLEAR_AMULET` — Clear Amulet | Stat lowering is prevented for this items's holder. | Sim | Loja / pokemart: …/scripts.pory (GoldenrodCity_UndergroundTunnel), …l/scripts.inc (GoldenrodCity_UndergroundTunnel) |
| `ITEM_CORNERSTONE_MASK` — Cornerstone Mask | Allows Ogerpon to wield the Rock- type in battle. | Sim | Script (dado ao jogador): data/maps/Kitakami_Temple_Storage/scripts.inc:62, …ta/maps/Kitakami_Temple_Storage/scripts.pory:44 |
| `ITEM_COVERT_CLOAK` — Covert Cloak | Protects holder from additional effects of moves. | Sim | Loja / pokemart: …/scripts.pory (GoldenrodCity_UndergroundTunnel), …l/scripts.inc (GoldenrodCity_UndergroundTunnel) |
| `ITEM_DAMP_ROCK` — Damp Rock | Extends the length of Rain Dance if used by the holder. | Sim | Item ball no mapa (object_event): UnionCave_B1F \| Loja / pokemart: …/scripts.pory (BattleFrontier_BattleTowerLobby), …y/scripts.inc (BattleFrontier_BattleTowerLobby) |
| `ITEM_DARKINIUM_Z` — Darkinium Z | Upgrade Dark- type moves into Z-Moves. | Não | - |
| `ITEM_DARK_GEM` — Dark Gem | Increases the power of Dark Type moves. | Sim | Loja / pokemart: …enter/scripts.inc (IndigoPlateau_PokemonCenter), …nter/scripts.pory (IndigoPlateau_PokemonCenter) |
| `ITEM_DARK_MEMORY` — Dark Memory | A disc with Dark type data. It swaps Silvally's type. | Não | - |
| `ITEM_DECIDIUM_Z` — Decidium Z | Upgrade Decidu- eye's Spirit Sha- ckle into a Z-Move. | Não | - |
| `ITEM_DEEP_SEA_SCALE` — Deep Sea Scale | A hold item that raises the Sp. Def of Clamperl. | Sim | Script (dado ao jogador, var computado): data/maps/Route25_BillsHouse/scripts.inc:117 |
| `ITEM_DEEP_SEA_TOOTH` — Deep Sea Tooth | A hold item that raises the Sp. Atk of Clamperl. | Sim | Script (dado ao jogador, var computado): data/maps/Route25_BillsHouse/scripts.inc:83 |
| `ITEM_DESTINY_KNOT` — Destiny Knot | If the holder falls in love, the foe does too. | Sim | Pickup (habilidade): battle_script_commands.c sPickupTable \| Script (dado ao jogador): data/maps/Route34_DayCare/scripts.inc:1242, data/maps/Route34_DayCare/scripts.pory:633 |
| `ITEM_DOUSE_DRIVE` — Douse Drive | Changes Genesect's Techno Blast to Water-type. | Não | - |
| `ITEM_DRACO_PLATE` — Draco Plate | A tablet that ups the power of Dragon-type moves. | Não | - |
| `ITEM_DRAGONIUM_Z` — Dragonium Z | Upgrade Dragon- type moves into Z-Moves. | Não | - |
| `ITEM_DRAGON_FANG` — Dragon Fang | A hold item that raises the power of Dragon-type moves. | Sim | Item ball no mapa (object_event): DragonsDen_Cavern |
| `ITEM_DRAGON_GEM` — Dragon Gem | Increases the power of Dragon Type moves. | Sim | Loja / pokemart: …enter/scripts.inc (IndigoPlateau_PokemonCenter), …nter/scripts.pory (IndigoPlateau_PokemonCenter) |
| `ITEM_DRAGON_MEMORY` — Dragon Memory | A disc with Dragon type data. It swaps Silvally's type. | Não | - |
| `ITEM_DREAD_PLATE` — Dread Plate | A tablet that ups the power of Dark-type moves. | Não | - |
| `ITEM_EARTH_PLATE` — Earth Plate | A tablet that ups the power of Ground-type moves. | Não | - |
| `ITEM_EEVIUM_Z` — Eevium Z | Upgrade Eevee's Last Resort into a Z-Move. | Não | - |
| `ITEM_EJECT_BUTTON` — Eject Button | Switches out the user if they're hit by the foe. | Sim | Loja / pokemart: …a/maps/RintoVillage/scripts.pory (RintoVillage), …ta/maps/RintoVillage/scripts.inc (RintoVillage) |
| `ITEM_EJECT_PACK` — Eject Pack | Forces the user to switch if its stats are lowered. | Sim | Item ball no mapa (object_event): MtSilver_1F_WaterfallRoom |
| `ITEM_ELECTRIC_GEM` — Electric Gem | Increases the power of Electric Type moves. | Sim | Loja / pokemart: …enter/scripts.inc (IndigoPlateau_PokemonCenter), …nter/scripts.pory (IndigoPlateau_PokemonCenter) |
| `ITEM_ELECTRIC_MEMORY` — Electric Memory | A disc with Electric type data. It swaps Silvally's type. | Não | - |
| `ITEM_ELECTRIC_SEED` — Electric Seed | Boosts Defense on Electric Terrain, but only one time. | Sim | Loja / pokemart: …/scripts.pory (BattleFrontier_BattleTowerLobby), …y/scripts.inc (BattleFrontier_BattleTowerLobby) |
| `ITEM_ELECTRIUM_Z` — Electrium Z | Upgrade Electric- type moves into Z-Moves. | Não | - |
| `ITEM_EVERSTONE` — Everstone | A wondrous hold item that prevents evolution. | Sim | Hidden Grotto (item raro): src/hidden_grotto.c \| Script (dado ao jogador, var computado): data/maps/Route25_BillsHouse/scripts.inc:49 |
| `ITEM_EVIOLITE` — Eviolite | Raises the Def and Sp. Def of Pokémon that can evolve. | Sim | Hidden Grotto (item raro): src/hidden_grotto.c \| Script (dado ao jogador): data/maps/NewBarkTown_Lab/scripts.inc:1234, data/maps/NewBarkTown_Lab/scripts.pory:617 \| Script (dado ao jogador, var computado): …aps/GoldenrodCity_RadioTower_2F/scripts.inc:456, …ps/GoldenrodCity_RadioTower_2F/scripts.pory:228 |
| `ITEM_EXPERT_BELT` — Expert Belt | A belt that boosts the power of super effective moves. | Sim | Loja / pokemart: …a/maps/RintoVillage/scripts.pory (RintoVillage), …ta/maps/RintoVillage/scripts.inc (RintoVillage) |
| `ITEM_FAIRIUM_Z` — Fairium Z | Upgrade Fairy- type moves into Z-Moves. | Não | - |
| `ITEM_FAIRY_FEATHER` — Fairy Feather | A hold item that raises the power of Fairy-type moves. | Sim | Item ball no mapa (object_event): CeruleanCave_B2F |
| `ITEM_FAIRY_GEM` — Fairy Gem | Increases the power of Fairy Type moves. | Sim | Loja / pokemart: …enter/scripts.inc (IndigoPlateau_PokemonCenter), …nter/scripts.pory (IndigoPlateau_PokemonCenter) |
| `ITEM_FAIRY_MEMORY` — Fairy Memory | A disc with Fairy type data. It swaps Silvally's type. | Não | - |
| `ITEM_FIGHTING_GEM` — Fighting Gem | Increases the power of Fighting Type moves. | Sim | Loja / pokemart: …enter/scripts.inc (IndigoPlateau_PokemonCenter), …nter/scripts.pory (IndigoPlateau_PokemonCenter) |
| `ITEM_FIGHTING_MEMORY` — Fighting Memory | Disc with Fighting type data. It swaps Silvally's type. | Não | - |
| `ITEM_FIGHTINIUM_Z` — Fightinium Z | Upgrade Fighting- type moves into Z-Moves. | Não | - |
| `ITEM_FIRE_GEM` — Fire Gem | Increases the power of Fire Type moves. | Sim | Loja / pokemart: …enter/scripts.inc (IndigoPlateau_PokemonCenter), …nter/scripts.pory (IndigoPlateau_PokemonCenter) |
| `ITEM_FIRE_MEMORY` — Fire Memory | A disc with Fire type data. It swaps Silvally's type. | Não | - |
| `ITEM_FIRIUM_Z` — Firium Z | Upgrade Fire- type moves into Z-Moves. | Não | - |
| `ITEM_FIST_PLATE` — Fist Plate | A tablet that ups the power of Fight- ing-type moves. | Não | - |
| `ITEM_FLAME_ORB` — Flame Orb | A bizarre orb that inflicts a burn on holder in battle. | Sim | Loja / pokemart: …cripts.pory (BattleFrontier_BattlePyramidLobby), …scripts.inc (BattleFrontier_BattlePyramidLobby) \| Script (dado ao jogador): data/maps/Route47/scripts.inc:390, data/maps/Route47/scripts.pory:224 |
| `ITEM_FLAME_PLATE` — Flame Plate | A tablet that ups the power of Fire-type moves. | Não | - |
| `ITEM_FLOAT_STONE` — Float Stone | It's so light that when held, it halves a Pokémon's weight. | Sim | Item ball no mapa (object_event): TohjoPass |
| `ITEM_FLYING_GEM` — Flying Gem | Increases the power of Flying Type moves. | Sim | Loja / pokemart: …enter/scripts.inc (IndigoPlateau_PokemonCenter), …nter/scripts.pory (IndigoPlateau_PokemonCenter) |
| `ITEM_FLYING_MEMORY` — Flying Memory | A disc with Flying type data. It swaps Silvally's type. | Não | - |
| `ITEM_FLYINIUM_Z` — Flyinium Z | Upgrade Flying- type moves into Z-Moves. | Não | - |
| `ITEM_FOCUS_BAND` — Focus Band | A hold item that occasionally prevents fainting. | Sim | Loja / pokemart: …ipts.inc (BattleFrontier_ExchangeServiceCorner) |
| `ITEM_FOCUS_SASH` — Focus Sash | If the holder has full HP, it endures KO hits with 1 HP. | Sim | Loja / pokemart: …cripts.pory (BattleFrontier_BattlePyramidLobby), …scripts.inc (BattleFrontier_BattlePyramidLobby) \| Script (dado ao jogador): …aps/Kitakami_Temple_TrainingRoom/scripts.inc:23, …ps/Kitakami_Temple_TrainingRoom/scripts.pory:14 |
| `ITEM_FULL_INCENSE` — Full Incense | A held item that makes the holder move slower. | Sim | Loja / pokemart: …aps/SafariZoneGate/scripts.inc (SafariZoneGate), …ps/SafariZoneGate/scripts.pory (SafariZoneGate) |
| `ITEM_GHOSTIUM_Z` — Ghostium Z | Upgrade Ghost- type moves into Z-Moves. | Não | - |
| `ITEM_GHOST_GEM` — Ghost Gem | Increases the power of Ghost Type moves. | Sim | Loja / pokemart: …enter/scripts.inc (IndigoPlateau_PokemonCenter), …nter/scripts.pory (IndigoPlateau_PokemonCenter) |
| `ITEM_GHOST_MEMORY` — Ghost Memory | A disc with Ghost type data. It swaps Silvally's type. | Não | - |
| `ITEM_GRASSIUM_Z` — Grassium Z | Upgrade Grass- type moves into Z-Moves. | Não | - |
| `ITEM_GRASSY_SEED` — Grassy Seed | Boosts Defense on Grassy Terrain, but only one time. | Sim | Item ball no mapa (object_event): VajraDesertEast \| Loja / pokemart: …/scripts.pory (BattleFrontier_BattleTowerLobby), …owerShop/scripts.inc (GoldenrodCity_FlowerShop), …werShop/scripts.pory (GoldenrodCity_FlowerShop) (+1) |
| `ITEM_GRASS_GEM` — Grass Gem | Increases the power of Grass Type moves. | Sim | Loja / pokemart: …enter/scripts.inc (IndigoPlateau_PokemonCenter), …nter/scripts.pory (IndigoPlateau_PokemonCenter) |
| `ITEM_GRASS_MEMORY` — Grass Memory | A disc with Grass type data. It swaps Silvally's type. | Não | - |
| `ITEM_GRIP_CLAW` — Grip Claw | A held item that extends binding moves like Wrap. | Só held item (Roubo/Golpe do Dia) | Held item selvagem (Roubo/Golpe do Dia): gen_1_families.h |
| `ITEM_GRISEOUS_CORE` — Griseous Core | A large, glowing gem that lets Giratina change form. | Não | - |
| `ITEM_GRISEOUS_ORB` — Griseous Orb | Boosts Giratina's Dragon/Ghost moves and changes form. | Sim | Script (finditem): data/maps/SpearPillarTop/scripts.inc:125, data/maps/SpearPillarTop/scripts.pory:62 |
| `ITEM_GROUNDIUM_Z` — Groundium Z | Upgrade Ground- type moves into Z-Moves. | Não | - |
| `ITEM_GROUND_GEM` — Ground Gem | Increases the power of Ground Type moves. | Sim | Loja / pokemart: …enter/scripts.inc (IndigoPlateau_PokemonCenter), …nter/scripts.pory (IndigoPlateau_PokemonCenter) |
| `ITEM_GROUND_MEMORY` — Ground Memory | A disc with Ground type data. It swaps Silvally's type. | Não | - |
| `ITEM_HARD_STONE` — Hard Stone | A hold item that raises the power of Rock-type moves. | Sim | Script (dado ao jogador): data/maps/Route36/scripts.inc:140, data/maps/Route36/scripts.pory:70 |
| `ITEM_HEARTHFLAME_MASK` — Hearthflame Mask | Allows Ogerpon to wield the Fire- type in battle. | Sim | Script (dado ao jogador): data/maps/Kitakami_Temple_Storage/scripts.inc:66, …ta/maps/Kitakami_Temple_Storage/scripts.pory:46 |
| `ITEM_HEAT_ROCK` — Heat Rock | Extends the length of Sunny Day if used by the holder. | Sim | Item ball no mapa (object_event): MtMortar_Depths_1 \| Loja / pokemart: …/scripts.pory (BattleFrontier_BattleTowerLobby), …y/scripts.inc (BattleFrontier_BattleTowerLobby) |
| `ITEM_HEAVY_DUTY_BOOTS` — Heavy-Duty Boots | Boots that prevent effects of traps set in the field. | Sim | Item ball no mapa (object_event): IcePath_Depths \| Loja / pokemart: …/scripts.pory (BattleFrontier_BattleTowerLobby), …y/scripts.inc (BattleFrontier_BattleTowerLobby) |
| `ITEM_ICE_GEM` — Ice Gem | Increases the power of Ice Type moves. | Sim | Loja / pokemart: …enter/scripts.inc (IndigoPlateau_PokemonCenter), …nter/scripts.pory (IndigoPlateau_PokemonCenter) |
| `ITEM_ICE_MEMORY` — Ice Memory | A disc with Ice type data. It swaps Silvally's type. | Não | - |
| `ITEM_ICICLE_PLATE` — Icicle Plate | A tablet that ups the power of Ice-type moves. | Não | - |
| `ITEM_ICIUM_Z` — Icium Z | Upgrade Ice- type moves into Z-Moves. | Não | - |
| `ITEM_ICY_ROCK` — Icy Rock | Extends the length of the move Hail used by the holder. | Sim | Item ball no mapa (object_event): SnowtopMountain_B1F \| Loja / pokemart: …/scripts.pory (BattleFrontier_BattleTowerLobby), …y/scripts.inc (BattleFrontier_BattleTowerLobby) |
| `ITEM_INCINIUM_Z` — Incinium Z | Upgrade Incine- roar's Darkest La- riat into a Z-Move. | Não | - |
| `ITEM_INSECT_PLATE` — Insect Plate | A tablet that ups the power of Bug-type moves. | Não | - |
| `ITEM_IRON_BALL` — Iron Ball | Cuts Speed and becomes vulnerable to Ground moves. | Sim | Held item de presente (givemon): data/maps/Kitakami_Houses/scripts.inc:92, data/maps/Kitakami_Houses/scripts.pory:155 |
| `ITEM_IRON_PLATE` — Iron Plate | A tablet that ups the power of Steel-type moves. | Não | - |
| `ITEM_KINGS_ROCK` — King's Rock | A hold item that may cause flinching when the foe is hit. | Sim | Item ball no mapa (object_event): MtMortar_1F_North, SlowpokeWell_B2F \| Loja / pokemart: …hoganyTown_Shop/scripts.inc (MahoganyTown_Shop), …ipts.inc (BattleFrontier_ExchangeServiceCorner) |
| `ITEM_KOMMONIUM_Z` — Kommonium Z | Upgrade Kommo-o's Clanging Scales into a Z-Move. | Não | - |
| `ITEM_LAGGING_TAIL` — Lagging Tail | A held item that makes the holder move slower. | Só held item (Roubo/Golpe do Dia) | Held item selvagem (Roubo/Golpe do Dia): gen_1_families.h, gen_8_families.h |
| `ITEM_LAX_INCENSE` — Lax Incense | A hold item that lowers the foe's accuracy. | Sim | Loja / pokemart: …aps/SafariZoneGate/scripts.inc (SafariZoneGate), …ps/SafariZoneGate/scripts.pory (SafariZoneGate) |
| `ITEM_LEEK` — Leek | A hold item that raises Farfetch'd's critical-hit ratio. | Só held item (Roubo/Golpe do Dia) | Held item de treinador (so via Roubo): trainers.party:568 \| Held item selvagem (Roubo/Golpe do Dia): gen_1_families.h |
| `ITEM_LEFTOVERS` — Leftovers | A hold item that gradually restores HP in battle. | Sim | Item ball no mapa (object_event): GoldenrodCity_UndergroundStorage \| Loja / pokemart: …ipts.inc (BattleFrontier_ExchangeServiceCorner) \| Pickup (habilidade): battle_script_commands.c sPickupTable |
| `ITEM_LIFE_ORB` — Life Orb | Boosts move power but holder loses HP with each attack. | Sim | Item ball no mapa (object_event): TinTower_5F, WhirlIslands_B1F \| Loja / pokemart: …cripts.pory (BattleFrontier_BattlePyramidLobby), …scripts.inc (BattleFrontier_BattlePyramidLobby) |
| `ITEM_LIGHT_BALL` — Light Ball | A hold item that raises the Atk and Sp. Atk of Pikachu. | Só held item (Roubo/Golpe do Dia) | Held item de treinador (so via Roubo): trainers.party:10500 \| Held item selvagem (Roubo/Golpe do Dia): gen_1_families.h |
| `ITEM_LIGHT_CLAY` — Light Clay | Extends the length of barrier moves used by the holder. | Sim | Hidden Grotto (item raro): src/hidden_grotto.c |
| `ITEM_LOADED_DICE` — Loaded Dice | Rolls high numbers. Multihit strikes hit more times. | Sim | Script (dado ao jogador): data/maps/GoldenrodShore/scripts.inc:49, data/maps/GoldenrodShore/scripts.pory:38 |
| `ITEM_LUCKY_EGG` — Lucky Egg | A hold item that boosts Exp. points earned in battle. | Sim | Hidden Grotto (item raro): src/hidden_grotto.c \| Item ball no mapa (object_event): KitakamiMountain \| Loja / pokemart: …/scripts.pory (BattleFrontier_BattleTowerLobby), …y/scripts.inc (BattleFrontier_BattleTowerLobby) |
| `ITEM_LUCKY_PUNCH` — Lucky Punch | A hold item that raises Chansey's critical-hit rate. | Sim | Item ball no mapa (object_event): Route47 |
| `ITEM_LUCK_INCENSE` — Luck Incense | Doubles money in battle if the holder takes part. | Sim | Loja / pokemart: …aps/SafariZoneGate/scripts.inc (SafariZoneGate), …ps/SafariZoneGate/scripts.pory (SafariZoneGate) |
| `ITEM_LUMINOUS_MOSS` — Luminous Moss | Raises Sp. Def if the holder is hit by a Water-type move. | Sim | Loja / pokemart: …owerShop/scripts.inc (GoldenrodCity_FlowerShop), …werShop/scripts.pory (GoldenrodCity_FlowerShop) |
| `ITEM_LUNALIUM_Z` — Lunalium Z | Upgrade Lunala's Moongeist Beam into a Z-Move. | Não | - |
| `ITEM_LUSTROUS_GLOBE` — Lustrous Globe | A large, glowing gem that lets Palkia change form. | Não | - |
| `ITEM_LUSTROUS_ORB` — Lustrous Orb | Boosts Palkia's Dragon/Water moves and changes form. | Sim | Script (finditem): data/maps/SpearPillarTop/scripts.inc:87, data/maps/SpearPillarTop/scripts.pory:42 |
| `ITEM_LYCANIUM_Z` — Lycanium Z | Upgrade Lycanroc's Stone Edge into a Z-Move. | Não | - |
| `ITEM_MACHO_BRACE` — Macho Brace | A hold item that promotes growth, but reduces Speed. | Sim | Loja / pokemart: …ipts.inc (BattleFrontier_ExchangeServiceCorner) |
| `ITEM_MAGNET` — Magnet | A hold item that boosts Electric- type moves. | Sim | Script (dado ao jogador): data/maps/Route37/scripts.inc:110, data/maps/Route37/scripts.pory:55 |
| `ITEM_MARSHADIUM_Z` — Marshadium Z | Upgrade Marsha- dow's Spectral Thi- ef into a Z-Move. | Não | - |
| `ITEM_MEADOW_PLATE` — Meadow Plate | A tablet that ups the power of Grass-type moves. | Não | - |
| `ITEM_MENTAL_HERB` — Mental Herb | Snaps Pokémon out of move-binding effects. A hold item that snaps Pokémon out of infatuation. | Sim | Loja / pokemart: …ipts.inc (BattleFrontier_ExchangeServiceCorner) \| Pickup (habilidade): battle_script_commands.c sPickupTable |
| `ITEM_METAL_COAT` — Metal Coat | A hold item that raises the power of Steel-type moves. | Sim | Loja / pokemart: …hoganyTown_Shop/scripts.inc (MahoganyTown_Shop) |
| `ITEM_METAL_POWDER` — Metal Powder | A hold item that raises Ditto's Defense. | Só held item (Roubo/Golpe do Dia) | Held item selvagem (Roubo/Golpe do Dia): gen_1_families.h |
| `ITEM_METRONOME` — Metronome | A held item that boosts a move used consecutively. | Sim | Item ball no mapa (object_event): KitakamiMountain2F |
| `ITEM_MEWNIUM_Z` — Mewnium Z | Upgrade Mew's Psychic into a Z-Move. | Não | - |
| `ITEM_MIMIKIUM_Z` — Mimikium Z | Upgrade Mimikyu's Play Rough into a Z-Move. | Não | - |
| `ITEM_MIND_PLATE` — Mind Plate | A tablet that ups the power of Psy chic-type moves. | Não | - |
| `ITEM_MIRACLE_SEED` — Miracle Seed | A hold item that raises the power of Grass-type moves. | Sim | Script (dado ao jogador): data/maps/Route32/scripts.inc:444, data/maps/Route32/scripts.pory:222 |
| `ITEM_MIRROR_HERB` — Mirror Herb | Mirrors an enemy's stat increases but only once. | Sim | Item ball no mapa (object_event): AbandonedRocketHideout |
| `ITEM_MISTY_SEED` — Misty Seed | Boosts Sp. Def. on Misty Terrain, but only one time. | Sim | Loja / pokemart: …/scripts.pory (BattleFrontier_BattleTowerLobby), …y/scripts.inc (BattleFrontier_BattleTowerLobby) |
| `ITEM_MUSCLE_BAND` — Muscle Band | A headband that boosts the power of physical moves. | Só held item (Roubo/Golpe do Dia) | Held item de treinador (so via Roubo): trainers.party:14332 \| Held item selvagem (Roubo/Golpe do Dia): gen_5_families.h |
| `ITEM_MYSTIC_WATER` — Mystic Water | A hold item that raises the power of Water-type moves. | Sim | Held item de presente (givemon): …aps/Route119_WeatherInstitute_2F/scripts.inc:85 \| Script (dado ao jogador): data/maps/CherrygroveCity/scripts.inc:298, data/maps/CherrygroveCity/scripts.pory:149 |
| `ITEM_NEVER_MELT_ICE` — Never-Melt Ice | A hold item that raises the power of Ice-type moves. | Sim | Item ball no mapa (object_event): IcePath_B4F \| Script (finditem): data/maps/MtSilver_Snow/scripts.inc:11 |
| `ITEM_NORMALIUM_Z` — Normalium Z | Upgrade Normal- type moves into Z-Moves. | Não | - |
| `ITEM_NORMAL_GEM` — Normal Gem | Increases the power of Normal Type moves. | Sim | Loja / pokemart: …enter/scripts.inc (IndigoPlateau_PokemonCenter), …nter/scripts.pory (IndigoPlateau_PokemonCenter) |
| `ITEM_ODD_INCENSE` — Odd Incense | A hold item that boosts Psychic- type moves. | Sim | Item ball no mapa (object_event): RuinsOfAlph_PuzzleAndRewardChambers |
| `ITEM_PIKANIUM_Z` — Pikanium Z | Upgrade Pikachu's Volt Tackle into a Z-Move. | Não | - |
| `ITEM_PIKASHUNIUM_Z` — Pikashunium Z | Upgrade Pikachu w/ a cap's Thunderbolt into a Z-Move. | Não | - |
| `ITEM_PIXIE_PLATE` — Pixie Plate | A tablet that ups the power of Fairy-type moves. | Não | - |
| `ITEM_POISONIUM_Z` — Poisonium Z | Upgrade Poison- type moves into Z-Moves. | Não | - |
| `ITEM_POISON_BARB` — Poison Barb | A hold item that raises the power of Poison-type moves. | Sim | Script (dado ao jogador): data/maps/Route32/scripts.inc:320, data/maps/Route32/scripts.pory:160 |
| `ITEM_POISON_GEM` — Poison Gem | Increases the power of Poison Type moves. | Sim | Loja / pokemart: …enter/scripts.inc (IndigoPlateau_PokemonCenter), …nter/scripts.pory (IndigoPlateau_PokemonCenter) |
| `ITEM_POISON_MEMORY` — Poison Memory | A disc with Poison type data. It swaps Silvally's type. | Não | - |
| `ITEM_POWER_ANKLET` — Power Anklet | A hold item that promotes Spd gain, but reduces Speed. | Sim | Loja / pokemart: …/scripts.inc (GoldenrodCity_DepartmentStore_3F) |
| `ITEM_POWER_BAND` — Power Band | Hold item that pro- motes Sp. Def gain, but reduces Speed. | Sim | Loja / pokemart: …/scripts.inc (GoldenrodCity_DepartmentStore_3F) |
| `ITEM_POWER_BELT` — Power Belt | A hold item that promotes Def gain, but reduces Speed. | Sim | Loja / pokemart: …/scripts.inc (GoldenrodCity_DepartmentStore_3F) |
| `ITEM_POWER_BRACER` — Power Bracer | A hold item that promotes Atk gain, but reduces Speed. | Sim | Loja / pokemart: …/scripts.inc (GoldenrodCity_DepartmentStore_3F) |
| `ITEM_POWER_HERB` — Power Herb | Allows immediate use of a move that charges first. | Sim | Loja / pokemart: …cripts.pory (BattleFrontier_BattlePyramidLobby), …scripts.inc (BattleFrontier_BattlePyramidLobby) \| Pickup (habilidade): battle_script_commands.c sPickupTable \| Script (dado ao jogador): data/maps/Route43/scripts.inc:322, data/maps/Route43/scripts.pory:184 |
| `ITEM_POWER_LENS` — Power Lens | Hold item that pro- motes Sp. Atk gain, but reduces Speed. | Sim | Loja / pokemart: …/scripts.inc (GoldenrodCity_DepartmentStore_3F) |
| `ITEM_POWER_WEIGHT` — Power Weight | A hold item that promotes HP gain, but reduces Speed. | Sim | Loja / pokemart: …/scripts.inc (GoldenrodCity_DepartmentStore_3F) |
| `ITEM_PRIMARIUM_Z` — Primarium Z | Upgrade Primarina's Sparkling Aria into a Z-Move. | Não | - |
| `ITEM_PROTECTIVE_PADS` — Protective Pads | Guard the holder from contact move effects. | Sim | Item ball no mapa (object_event): KitakamiBorder |
| `ITEM_PSYCHIC_GEM` — Psychic Gem | Increases the power of Psychic Type moves. | Sim | Loja / pokemart: …enter/scripts.inc (IndigoPlateau_PokemonCenter), …nter/scripts.pory (IndigoPlateau_PokemonCenter) |
| `ITEM_PSYCHIC_MEMORY` — Psychic Memory | A disc with Psychic type data. It swaps Silvally's type. | Não | - |
| `ITEM_PSYCHIC_SEED` — Psychic Seed | Boosts Sp. Def. on Psychic Terrain, but only one time. | Sim | Loja / pokemart: …/scripts.pory (BattleFrontier_BattleTowerLobby), …y/scripts.inc (BattleFrontier_BattleTowerLobby) |
| `ITEM_PSYCHIUM_Z` — Psychium Z | Upgrade Psychic- type moves into Z-Moves. | Não | - |
| `ITEM_PUNCHING_GLOVE` — Punching Glove | Powers up punching moves and removes their contact. | Sim | Item ball no mapa (object_event): GoldenrodCity_DepartmentStoreBasement |
| `ITEM_PURE_INCENSE` — Pure Incense | A hold item that helps repel wild Pokémon. | Sim | Loja / pokemart: …aps/SafariZoneGate/scripts.inc (SafariZoneGate), …ps/SafariZoneGate/scripts.pory (SafariZoneGate) |
| `ITEM_QUICK_CLAW` — Quick Claw | A hold item that occasionally allows the first strike. | Sim | Loja / pokemart: …ipts.inc (BattleFrontier_ExchangeServiceCorner) \| Script (dado ao jogador): data/maps/NationalPark_Normal/scripts.inc:98, data/maps/NationalPark_Normal/scripts.pory:49 |
| `ITEM_QUICK_POWDER` — Quick Powder | A hold item that raises the Speed of Ditto. | Só held item (Roubo/Golpe do Dia) | Held item selvagem (Roubo/Golpe do Dia): gen_1_families.h |
| `ITEM_RAZOR_CLAW` — Razor Claw | A hooked claw that ups the holder's critical-hit ratio. | Sim | Item ball no mapa (object_event): Route41 |
| `ITEM_RAZOR_FANG` — Razor Fang | A hold item that may cause flinching when the foe is hit. | Sim | Item ball no mapa (object_event): Route47 |
| `ITEM_RED_CARD` — Red Card | Switches out the foe if they hit the holder. | Não | - |
| `ITEM_RED_ORB` — Red Orb | A red, glowing orb said to contain an ancient power. | Sim | Script (finditem): data/maps/Route50UnderwaterCave2/scripts.inc:30, data/maps/Route50UnderwaterCave2/scripts.pory:9 |
| `ITEM_RING_TARGET` — Ring Target | Moves that usually have no effect will hit the holder. | Sim | Loja / pokemart: …a/maps/RintoVillage/scripts.pory (RintoVillage), …ta/maps/RintoVillage/scripts.inc (RintoVillage) |
| `ITEM_ROCKIUM_Z` — Rockium Z | Upgrade Rock- type moves into Z-Moves. | Não | - |
| `ITEM_ROCKY_HELMET` — Rocky Helmet | Hurts the foe if they touch its holder. | Sim | Script (dado ao jogador): data/maps/Gate_Route39North/scripts.inc:27, data/maps/Gate_Route39North/scripts.pory:30 |
| `ITEM_ROCK_GEM` — Rock Gem | Increases the power of Rock Type moves. | Sim | Loja / pokemart: …enter/scripts.inc (IndigoPlateau_PokemonCenter), …nter/scripts.pory (IndigoPlateau_PokemonCenter) |
| `ITEM_ROCK_INCENSE` — Rock Incense | A hold item that raises the power of Rock-type moves. | Sim | Loja / pokemart: …aps/SafariZoneGate/scripts.inc (SafariZoneGate), …ps/SafariZoneGate/scripts.pory (SafariZoneGate) |
| `ITEM_ROCK_MEMORY` — Rock Memory | A disc with Rock type data. It swaps Silvally's type. | Não | - |
| `ITEM_ROOM_SERVICE` — Room Service | Lowers Speed if Trick Room is active. | Sim | Item ball no mapa (object_event): Route42 \| Loja / pokemart: …/scripts.pory (BattleFrontier_BattleTowerLobby), …y/scripts.inc (BattleFrontier_BattleTowerLobby) |
| `ITEM_ROSE_INCENSE` — Rose Incense | A hold item that raises the power of Grass-type moves. | Sim | Loja / pokemart: …aps/SafariZoneGate/scripts.inc (SafariZoneGate), …ps/SafariZoneGate/scripts.pory (SafariZoneGate) |
| `ITEM_SAFETY_GOGGLES` — Safety Goggles | Protect from weather damage and powder moves. | Sim | Item ball no mapa (object_event): VajraDesert |
| `ITEM_SCOPE_LENS` — Scope Lens | A hold item that improves the critical-hit rate. | Sim | Loja / pokemart: …ipts.inc (BattleFrontier_ExchangeServiceCorner) \| Script (dado ao jogador): data/maps/Route39_Barn/scripts.inc:111 |
| `ITEM_SEA_INCENSE` — Sea Incense | A hold item that slightly boosts Water-type moves. | Sim | Item ball no mapa (object_event): Route32 \| Loja / pokemart: …aps/SafariZoneGate/scripts.inc (SafariZoneGate), …ps/SafariZoneGate/scripts.pory (SafariZoneGate) |
| `ITEM_SHARP_BEAK` — Sharp Beak | A hold item that raises the power of Flying-type moves. | Sim | Script (dado ao jogador): data/maps/Route40/scripts.inc:360, data/maps/Route40/scripts.pory:180 |
| `ITEM_SHED_SHELL` — Shed Shell | Allows the holder to switch out without fail. | Só held item (Roubo/Golpe do Dia) | Held item selvagem (Roubo/Golpe do Dia): gen_1_families.h, gen_3_families.h, gen_5_families.h (+1) |
| `ITEM_SHELL_BELL` — Shell Bell | A hold item that restores HP upon striking the foe. | Sim | Item ball no mapa (object_event): Route47 |
| `ITEM_SHOCK_DRIVE` — Shock Drive | Changes Genesect's Techno Blast to Electric-type. | Não | - |
| `ITEM_SILK_SCARF` — Silk Scarf | A hold item that raises the power of Normal-type moves. | Sim | Script (dado ao jogador): data/maps/Route29/scripts.inc:206, data/maps/Route29/scripts.pory:103 |
| `ITEM_SILVER_POWDER` — Silver Powder | A hold item that raises the power of Bug-type moves. | Só held item (Roubo/Golpe do Dia) | Held item selvagem (Roubo/Golpe do Dia): gen_1_families.h, gen_3_families.h, gen_4_families.h (+1) |
| `ITEM_SKY_PLATE` — Sky Plate | A tablet that ups the power of Flying-type moves. | Não | - |
| `ITEM_SMOKE_BALL` — Smoke Ball | A hold item that assures fleeing from wild Pokémon. | Sim | Item ball no mapa (object_event): GoldenrodCity_UndergroundSwitches |
| `ITEM_SMOOTH_ROCK` — Smooth Rock | Extends the length of Sandstorm if used by the holder. | Sim | Hidden Grotto (item raro): src/hidden_grotto.c \| Item ball no mapa (object_event): MtMortar_B1F, Route45 \| Loja / pokemart: …/scripts.pory (BattleFrontier_BattleTowerLobby), …y/scripts.inc (BattleFrontier_BattleTowerLobby) |
| `ITEM_SNORLIUM_Z` — Snorlium Z | Upgrade Snorlax's Giga Impact into a Z-Move. | Não | - |
| `ITEM_SNOWBALL` — Snowball | Raises Atk if its holder is hit by an Ice-type move. | Sim | Item ball no mapa (object_event): SnowtopMountainOutside |
| `ITEM_SOFT_SAND` — Soft Sand | A hold item that raises the power of Ground-type moves. | Sim | Item ball no mapa (object_event): Route34 |
| `ITEM_SOLGANIUM_Z` — Solganium Z | Upgrade Solgaleo's Sunsteel Strike into a Z-Move. | Não | - |
| `ITEM_SOOTHE_BELL` — Soothe Bell | A hold item that calms spirits and fosters friendship. | Sim | Item ball no mapa (object_event): NationalPark_Normal |
| `ITEM_SOUL_DEW` — Soul Dew | Powers up Latios' & Latias' Psychic and Dragon-type moves. Hold item: raises Sp. Atk & Sp. Def of Latios & Latias. | Sim | Script (finditem): data/maps/LatiTempleSouldewRoom/scripts.inc:11, data/maps/LatiTempleSouldewRoom/scripts.pory:10 |
| `ITEM_SPELL_TAG` — Spell Tag | A hold item that raises the power of Ghost-type moves. | Sim | Script (dado ao jogador): data/maps/BlackthornCity/scripts.inc:246 |
| `ITEM_SPLASH_PLATE` — Splash Plate | A tablet that ups the power of Water-type moves. | Não | - |
| `ITEM_SPOOKY_PLATE` — Spooky Plate | A tablet that ups the power of Ghost-type moves. | Não | - |
| `ITEM_STEELIUM_Z` — Steelium Z | Upgrade Steel- type moves into Z-Moves. | Não | - |
| `ITEM_STEEL_GEM` — Steel Gem | Increases the power of Steel Type moves. | Sim | Loja / pokemart: …enter/scripts.inc (IndigoPlateau_PokemonCenter), …nter/scripts.pory (IndigoPlateau_PokemonCenter) |
| `ITEM_STEEL_MEMORY` — Steel Memory | A disc with Steel type data. It swaps Silvally's type. | Não | - |
| `ITEM_STICKY_BARB` — Sticky Barb | Damages the holder each turn. May latch on to foes. | Só held item (Roubo/Golpe do Dia) | Held item selvagem (Roubo/Golpe do Dia): gen_3_families.h, gen_5_families.h |
| `ITEM_STONE_PLATE` — Stone Plate | A tablet that ups the power of Rock-type moves. | Não | - |
| `ITEM_TAPUNIUM_Z` — Tapunium Z | Upgrade the tapus' Nature's Madness into a Z-Move. | Não | - |
| `ITEM_TERRAIN_EXTENDER` — Terrain Extender | Extends the length of the active battle terrain. | Sim | Item ball no mapa (object_event): Route32 |
| `ITEM_THICK_CLUB` — Thick Club | A hold item that raises Cubone or Marowak's Attack. | Só held item (Roubo/Golpe do Dia) | Held item selvagem (Roubo/Golpe do Dia): gen_1_families.h |
| `ITEM_THROAT_SPRAY` — Throat Spray | Raises Sp. Atk. if the holder uses a sound-based move. | Só held item (Roubo/Golpe do Dia) | Held item selvagem (Roubo/Golpe do Dia): gen_8_families.h |
| `ITEM_TOXIC_ORB` — Toxic Orb | A bizarre orb that badly poisons the holder in battle. | Sim | Loja / pokemart: …cripts.pory (BattleFrontier_BattlePyramidLobby), …scripts.inc (BattleFrontier_BattlePyramidLobby) \| Script (dado ao jogador): data/maps/Route47/scripts.inc:392, data/maps/Route47/scripts.pory:225 |
| `ITEM_TOXIC_PLATE` — Toxic Plate | A tablet that ups the power of Poison-type moves. | Não | - |
| `ITEM_TWISTED_SPOON` — Twisted Spoon | A hold item that boosts Psychic- type moves. | Só held item (Roubo/Golpe do Dia) | Held item de treinador (so via Roubo): trainers.party:4172, trainers.party:4294, trainers.party:6613 (+1) \| Held item selvagem (Roubo/Golpe do Dia): gen_1_families.h |
| `ITEM_ULTRANECROZIUM_Z` — Ultranecrozium Z | A crystal to turn fused Necrozma into a new form. | Não | - |
| `ITEM_UTILITY_UMBRELLA` — Utility Umbrella | An umbrella that protects from weather effects. | Sim | Loja / pokemart: data/maps/OlivineCity/scripts.inc (OlivineCity), data/maps/OlivineCity/scripts.pory (OlivineCity), …/scripts.pory (GoldenrodCity_UndergroundTunnel) (+1) |
| `ITEM_WATERIUM_Z` — Waterium Z | Upgrade Water- type moves into Z-Moves. | Não | - |
| `ITEM_WATER_GEM` — Water Gem | Increases the power of Water Type moves. | Sim | Loja / pokemart: …enter/scripts.inc (IndigoPlateau_PokemonCenter), …nter/scripts.pory (IndigoPlateau_PokemonCenter) |
| `ITEM_WATER_MEMORY` — Water Memory | A disc with Water type data. It swaps Silvally's type. | Não | - |
| `ITEM_WAVE_INCENSE` — Wave Incense | A hold item that slightly boosts Water-type moves. | Sim | Loja / pokemart: …aps/SafariZoneGate/scripts.inc (SafariZoneGate), …ps/SafariZoneGate/scripts.pory (SafariZoneGate) |
| `ITEM_WEAKNESS_POLICY` — Weakness Policy | If hit by a super- effective move, ups Atk and Sp. Atk. | Sim | Item ball no mapa (object_event): VictoryRoadKanto_B2F \| Loja / pokemart: …/scripts.pory (BattleFrontier_BattleTowerLobby), …y/scripts.inc (BattleFrontier_BattleTowerLobby) |
| `ITEM_WELLSPRING_MASK` — Wellspring Mask | Allows Ogerpon to wield the Water- type in battle. | Sim | Script (dado ao jogador): data/maps/Kitakami_Temple_Storage/scripts.inc:64, …ta/maps/Kitakami_Temple_Storage/scripts.pory:45 |
| `ITEM_WHITE_HERB` — White Herb | A hold item that restores any lowered stat. | Sim | Loja / pokemart: …cripts.pory (BattleFrontier_BattlePyramidLobby), …ipts.inc (BattleFrontier_ExchangeServiceCorner), …scripts.inc (BattleFrontier_BattlePyramidLobby) \| Pickup (habilidade): battle_script_commands.c sPickupTable \| Script (dado ao jogador): data/maps/Route43/scripts.inc:324, data/maps/Route43/scripts.pory:185 |
| `ITEM_WIDE_LENS` — Wide Lens | A magnifying lens that boosts the accuracy of moves. | Sim | Loja / pokemart: …a/maps/RintoVillage/scripts.pory (RintoVillage), …ta/maps/RintoVillage/scripts.inc (RintoVillage) |
| `ITEM_WISE_GLASSES` — Wise Glasses | A pair of glasses that ups the power of special moves. | Sim | Loja / pokemart: …a/maps/RintoVillage/scripts.pory (RintoVillage), …ta/maps/RintoVillage/scripts.inc (RintoVillage) |
| `ITEM_ZAP_PLATE` — Zap Plate | A tablet that ups the power of Elec- tric-type moves. | Não | - |
| `ITEM_ZOOM_LENS` — Zoom Lens | If the holder moves after the foe, it'll boost accuracy. | Sim | Item ball no mapa (object_event): MtSilver_1F_ItemRoom |

## Berries (68)

| Item | O que faz | Obtível in-game? | Como se obtém |
|---|---|---|---|
| `ITEM_AGUAV_BERRY` — Aguav Berry | A hold item that restores HP but may confuse. | Sim | Script (dado ao jogador): data/maps/VioletCity/scripts.inc:1132, data/maps/VioletCity/scripts.pory:565 \| Script (dado ao jogador, var computado): data/maps/Route120/scripts.inc:124 \| Sorteio de pool (Route30 Berry Master, comum): …/maps/Route30_House/scripts.inc (Route30_House) |
| `ITEM_APICOT_BERRY` — Apicot Berry | A hold item that raises Sp. Def in a pinch. | Sim | Sorteio de pool (Route30 Berry Master, raro pos-Liga): …/maps/Route30_House/scripts.inc (Route30_House) |
| `ITEM_ASPEAR_BERRY` — Aspear Berry | A hold item that defrosts Pokémon in battle. | Sim | Script (dado ao jogador): data/maps/VioletCity/scripts.inc:1109, data/maps/VioletCity/scripts.pory:542 \| Sorteio de pool (Route30 Berry Master, comum): …/maps/Route30_House/scripts.inc (Route30_House) |
| `ITEM_BABIRI_BERRY` — Babiri Berry | A hold item that weakens a Steel move if weak to it. | Sim | Loja / pokemart: …owerShop/scripts.inc (GoldenrodCity_FlowerShop), …werShop/scripts.pory (GoldenrodCity_FlowerShop) \| Sorteio de pool (Route30 Berry Master, comum): …/maps/Route30_House/scripts.inc (Route30_House) |
| `ITEM_BELUE_BERRY` — Belue Berry | {POKEBLOCK} ingredient. Plant in loamy soil to grow Belue. | Sim | Sorteio de pool (Route30 Berry Master, comum): …/maps/Route30_House/scripts.inc (Route30_House) |
| `ITEM_BLUK_BERRY` — Bluk Berry | {POKEBLOCK} ingredient. Plant in loamy soil to grow Bluk. | Sim | Sorteio de pool (Route30 Berry Master, comum): …/maps/Route30_House/scripts.inc (Route30_House) |
| `ITEM_CHARTI_BERRY` — Charti Berry | A hold item that weakens a Rock move if weak to it. | Sim | Loja / pokemart: …owerShop/scripts.inc (GoldenrodCity_FlowerShop), …werShop/scripts.pory (GoldenrodCity_FlowerShop) \| Sorteio de pool (Route30 Berry Master, comum): …/maps/Route30_House/scripts.inc (Route30_House) |
| `ITEM_CHERI_BERRY` — Cheri Berry | A hold item that heals paralysis in battle. | Sim | Script (dado ao jogador): data/maps/Route30_House/scripts.inc:57, data/maps/VioletCity/scripts.inc:1075, data/maps/VioletCity/scripts.pory:510 \| Sorteio de pool (Route30 Berry Master, comum): …/maps/Route30_House/scripts.inc (Route30_House) |
| `ITEM_CHESTO_BERRY` — Chesto Berry | A hold item that awakens Pokémon in battle. | Sim | Script (dado ao jogador): data/maps/VioletCity/scripts.inc:1094, data/maps/VioletCity/scripts.pory:527 \| Sorteio de pool (Route30 Berry Master, comum): …/maps/Route30_House/scripts.inc (Route30_House) |
| `ITEM_CHILAN_BERRY` — Chilan Berry | A hold item that weakens a Normal move. | Sim | Loja / pokemart: …owerShop/scripts.inc (GoldenrodCity_FlowerShop), …werShop/scripts.pory (GoldenrodCity_FlowerShop) \| Sorteio de pool (Route30 Berry Master, comum): …/maps/Route30_House/scripts.inc (Route30_House) |
| `ITEM_CHOPLE_BERRY` — Chople Berry | A hold item that weakens a Fighting move if weak to it. | Sim | Loja / pokemart: …owerShop/scripts.inc (GoldenrodCity_FlowerShop), …werShop/scripts.pory (GoldenrodCity_FlowerShop) \| Sorteio de pool (Route30 Berry Master, comum): …/maps/Route30_House/scripts.inc (Route30_House) |
| `ITEM_COBA_BERRY` — Coba Berry | A hold item that weakens a Flying move if weak to it. | Sim | Loja / pokemart: …owerShop/scripts.inc (GoldenrodCity_FlowerShop), …werShop/scripts.pory (GoldenrodCity_FlowerShop) \| Sorteio de pool (Route30 Berry Master, comum): …/maps/Route30_House/scripts.inc (Route30_House) |
| `ITEM_COLBUR_BERRY` — Colbur Berry | A hold item that weakens a Dark move if weak to it. | Sim | Loja / pokemart: …owerShop/scripts.inc (GoldenrodCity_FlowerShop), …werShop/scripts.pory (GoldenrodCity_FlowerShop) \| Sorteio de pool (Route30 Berry Master, comum): …/maps/Route30_House/scripts.inc (Route30_House) |
| `ITEM_CORNN_BERRY` — Cornn Berry | {POKEBLOCK} ingredient. Plant in loamy soil to grow Cornn. | Sim | Sorteio de pool (Route30 Berry Master, comum): …/maps/Route30_House/scripts.inc (Route30_House) |
| `ITEM_CUSTAP_BERRY` — Custap Berry | It allows a Pokémon in a pinch to move first just once. | Sim | Sorteio de pool (Route30 Berry Master, raro pos-Liga): …/maps/Route30_House/scripts.inc (Route30_House) |
| `ITEM_DURIN_BERRY` — Durin Berry | {POKEBLOCK} ingredient. Plant in loamy soil to grow Durin. | Sim | Sorteio de pool (Route30 Berry Master, comum): …/maps/Route30_House/scripts.inc (Route30_House) |
| `ITEM_ENIGMA_BERRY` — Enigma Berry | A hold item that heals from super effective moves. | Sim | Sorteio de pool (Route30 Berry Master, raro pos-Liga): …/maps/Route30_House/scripts.inc (Route30_House) |
| `ITEM_ENIGMA_BERRY_E_READER` — Enigma Berry | {POKEBLOCK} ingredient. Plant in loamy soil to grow a mystery. | Não (só em mapa fora da campanha) | Mencionado em script (verificar): data/maps/PetalburgCity_Gym/scripts.inc:305, data/maps/PetalburgCity_Gym/scripts.inc:307 \| Script (dado ao jogador): data/maps/PetalburgCity_Gym/scripts.inc:319 |
| `ITEM_FIGY_BERRY` — Figy Berry | A hold item that restores HP but may confuse. | Sim | Script (dado ao jogador): data/maps/SootopolisCity/scripts.inc:730 \| Script (dado ao jogador, var computado): data/maps/Route120/scripts.inc:109 \| Sorteio de pool (Route30 Berry Master, comum): …/maps/Route30_House/scripts.inc (Route30_House) |
| `ITEM_GANLON_BERRY` — Ganlon Berry | A hold item that raises Defense in a pinch. | Sim | Sorteio de pool (Route30 Berry Master, raro pos-Liga): …/maps/Route30_House/scripts.inc (Route30_House) |
| `ITEM_GREPA_BERRY` — Grepa Berry | Makes a Pokémon friendly but lowers base Sp. Def. | Sim | Loja / pokemart: …/scripts.inc (GoldenrodCity_DepartmentStore_3F) \| Sorteio de pool (Route30 Berry Master, comum): …/maps/Route30_House/scripts.inc (Route30_House) |
| `ITEM_HABAN_BERRY` — Haban Berry | A hold item that weakens a Dragon move if weak to it. | Sim | Loja / pokemart: …owerShop/scripts.inc (GoldenrodCity_FlowerShop), …werShop/scripts.pory (GoldenrodCity_FlowerShop) \| Sorteio de pool (Route30 Berry Master, comum): …/maps/Route30_House/scripts.inc (Route30_House) |
| `ITEM_HONDEW_BERRY` — Hondew Berry | Makes a Pokémon friendly but lowers base Sp. Atk. | Sim | Loja / pokemart: …/scripts.inc (GoldenrodCity_DepartmentStore_3F) \| Sorteio de pool (Route30 Berry Master, comum): …/maps/Route30_House/scripts.inc (Route30_House) |
| `ITEM_IAPAPA_BERRY` — Iapapa Berry | A hold item that restores HP but may confuse. | Sim | Script (dado ao jogador): data/maps/SootopolisCity/scripts.inc:737, data/maps/VioletCity/scripts.inc:1113, data/maps/VioletCity/scripts.pory:544 \| Script (dado ao jogador, var computado): data/maps/Route120/scripts.inc:129 \| Sorteio de pool (Route30 Berry Master, comum): …/maps/Route30_House/scripts.inc (Route30_House) |
| `ITEM_JABOCA_BERRY` — Jaboca Berry | If hit by a physical move, it will hurt the attacker a bit. | Sim | Sorteio de pool (Route30 Berry Master, raro pos-Liga): …/maps/Route30_House/scripts.inc (Route30_House) |
| `ITEM_KASIB_BERRY` — Kasib Berry | A hold item that weakens a Ghost move if weak to it. | Sim | Loja / pokemart: …owerShop/scripts.inc (GoldenrodCity_FlowerShop), …werShop/scripts.pory (GoldenrodCity_FlowerShop) \| Sorteio de pool (Route30 Berry Master, comum): …/maps/Route30_House/scripts.inc (Route30_House) |
| `ITEM_KEBIA_BERRY` — Kebia Berry | A hold item that weakens a Poison move if weak to it. | Sim | Loja / pokemart: …owerShop/scripts.inc (GoldenrodCity_FlowerShop), …werShop/scripts.pory (GoldenrodCity_FlowerShop) \| Sorteio de pool (Route30 Berry Master, comum): …/maps/Route30_House/scripts.inc (Route30_House) |
| `ITEM_KEE_BERRY` — Kee Berry | If hit by a physical move, it raises the Defense a bit. | Sim | Sorteio de pool (Route30 Berry Master, raro pos-Liga): …/maps/Route30_House/scripts.inc (Route30_House) |
| `ITEM_KELPSY_BERRY` — Kelpsy Berry | Makes a Pokémon friendly but lowers base Attack. | Sim | Loja / pokemart: …/scripts.inc (GoldenrodCity_DepartmentStore_3F) \| Sorteio de pool (Route30 Berry Master, comum): …/maps/Route30_House/scripts.inc (Route30_House) |
| `ITEM_LANSAT_BERRY` — Lansat Berry | A hold item that ups the critical- hit rate in a pinch. | Sim | Sorteio de pool (Route30 Berry Master, raro pos-Liga): …/maps/Route30_House/scripts.inc (Route30_House) |
| `ITEM_LEPPA_BERRY` — Leppa Berry | A hold item that restores 10 PP in battle. | Sim | Item escondido (hidden_item): UnionCave_1F \| Script (dado ao jogador): data/maps/VioletCity/scripts.inc:1079, data/maps/VioletCity/scripts.pory:512 \| Sorteio de pool (Route30 Berry Master, comum): …/maps/Route30_House/scripts.inc (Route30_House) |
| `ITEM_LIECHI_BERRY` — Liechi Berry | A hold item that raises Attack in a pinch. | Sim | Sorteio de pool (Route30 Berry Master, raro pos-Liga): …/maps/Route30_House/scripts.inc (Route30_House) |
| `ITEM_LUM_BERRY` — Lum Berry | A hold item that heals any status problem in battle. | Sim | Item ball no mapa (object_event): RuinsOfAlph_PuzzleAndRewardChambers \| Script (dado ao jogador): data/maps/VioletCity/scripts.inc:1130, data/maps/VioletCity/scripts.pory:564 \| Sorteio de pool (Route30 Berry Master, comum): …/maps/Route30_House/scripts.inc (Route30_House) |
| `ITEM_MAGOST_BERRY` — Magost Berry | {POKEBLOCK} ingredient. Plant in loamy soil to grow Magost. | Sim | Sorteio de pool (Route30 Berry Master, comum): …/maps/Route30_House/scripts.inc (Route30_House) |
| `ITEM_MAGO_BERRY` — Mago Berry | A hold item that restores HP but may confuse. | Sim | Script (dado ao jogador, var computado): data/maps/Route120/scripts.inc:119 \| Sorteio de pool (Route30 Berry Master, comum): …/maps/Route30_House/scripts.inc (Route30_House) |
| `ITEM_MARANGA_BERRY` — Maranga Berry | If hit by a special move, it raises the Sp. Def. a bit. | Sim | Sorteio de pool (Route30 Berry Master, raro pos-Liga): …/maps/Route30_House/scripts.inc (Route30_House) |
| `ITEM_MICLE_BERRY` — Micle Berry | When held, it ups the Accuracy of a move in a pinch. | Sim | Sorteio de pool (Route30 Berry Master, raro pos-Liga): …/maps/Route30_House/scripts.inc (Route30_House) |
| `ITEM_NANAB_BERRY` — Nanab Berry | {POKEBLOCK} ingredient. Plant in loamy soil to grow Nanab. | Sim | Sorteio de pool (Route30 Berry Master, comum): …/maps/Route30_House/scripts.inc (Route30_House) |
| `ITEM_NOMEL_BERRY` — Nomel Berry | {POKEBLOCK} ingredient. Plant in loamy soil to grow Nomel. | Sim | Sorteio de pool (Route30 Berry Master, comum): …/maps/Route30_House/scripts.inc (Route30_House) |
| `ITEM_OCCA_BERRY` — Occa Berry | A hold item that weakens a Fire move if weak to it. | Sim | Loja / pokemart: …owerShop/scripts.inc (GoldenrodCity_FlowerShop), …werShop/scripts.pory (GoldenrodCity_FlowerShop) \| Sorteio de pool (Route30 Berry Master, comum): …/maps/Route30_House/scripts.inc (Route30_House) |
| `ITEM_ORAN_BERRY` — Oran Berry | A hold item that restores 10 HP in battle. | Sim | Script (dado ao jogador): data/maps/VioletCity/scripts.inc:1092, data/maps/VioletCity/scripts.pory:526 \| Sorteio de pool (Route30 Berry Master, comum): …/maps/Route30_House/scripts.inc (Route30_House) |
| `ITEM_PAMTRE_BERRY` — Pamtre Berry | {POKEBLOCK} ingredient. Plant in loamy soil to grow Pamtre. | Sim | Sorteio de pool (Route30 Berry Master, comum): …/maps/Route30_House/scripts.inc (Route30_House) |
| `ITEM_PASSHO_BERRY` — Passho Berry | A hold item that weakens a Water move if weak to it. | Sim | Loja / pokemart: …owerShop/scripts.inc (GoldenrodCity_FlowerShop), …werShop/scripts.pory (GoldenrodCity_FlowerShop) \| Sorteio de pool (Route30 Berry Master, comum): …/maps/Route30_House/scripts.inc (Route30_House) |
| `ITEM_PAYAPA_BERRY` — Payapa Berry | A hold item that weakens a Psychic move if weak to it. | Sim | Loja / pokemart: …owerShop/scripts.inc (GoldenrodCity_FlowerShop), …werShop/scripts.pory (GoldenrodCity_FlowerShop) \| Sorteio de pool (Route30 Berry Master, comum): …/maps/Route30_House/scripts.inc (Route30_House) |
| `ITEM_PECHA_BERRY` — Pecha Berry | A hold item that heals poisoning in battle. | Sim | Item ball no mapa (object_event): RuinsOfAlph_PuzzleAndRewardChambers \| Script (dado ao jogador): data/maps/VioletCity/scripts.inc:1077, data/maps/VioletCity/scripts.pory:511, data/scripts/berry_blender.inc:267 (+1) \| Script (finditem): data/maps/VioletCity/scripts.inc:458, data/maps/VioletCity/scripts.pory:229 \| Sorteio de pool (Route30 Berry Master, comum): …/maps/Route30_House/scripts.inc (Route30_House) |
| `ITEM_PERSIM_BERRY` — Persim Berry | A hold item that heals confusion in battle. | Sim | Script (dado ao jogador): data/maps/VioletCity/scripts.inc:1115, data/maps/VioletCity/scripts.pory:549 \| Sorteio de pool (Route30 Berry Master, comum): …/maps/Route30_House/scripts.inc (Route30_House) |
| `ITEM_PETAYA_BERRY` — Petaya Berry | A hold item that raises Sp. Atk in a pinch. | Sim | Sorteio de pool (Route30 Berry Master, raro pos-Liga): …/maps/Route30_House/scripts.inc (Route30_House) |
| `ITEM_PINAP_BERRY` — Pinap Berry | {POKEBLOCK} ingredient. Plant in loamy soil to grow Pinap. | Sim | Sorteio de pool (Route30 Berry Master, comum): …/maps/Route30_House/scripts.inc (Route30_House) |
| `ITEM_POMEG_BERRY` — Pomeg Berry | Makes a Pokémon friendly but lowers base HP. | Sim | Loja / pokemart: …/scripts.inc (GoldenrodCity_DepartmentStore_3F) \| Sorteio de pool (Route30 Berry Master, comum): …/maps/Route30_House/scripts.inc (Route30_House) |
| `ITEM_QUALOT_BERRY` — Qualot Berry | Makes a Pokémon friendly but lowers base Defense. | Sim | Loja / pokemart: …/scripts.inc (GoldenrodCity_DepartmentStore_3F) \| Sorteio de pool (Route30 Berry Master, comum): …/maps/Route30_House/scripts.inc (Route30_House) |
| `ITEM_RABUTA_BERRY` — Rabuta Berry | {POKEBLOCK} ingredient. Plant in loamy soil to grow Rabuta. | Sim | Sorteio de pool (Route30 Berry Master, comum): …/maps/Route30_House/scripts.inc (Route30_House) |
| `ITEM_RAWST_BERRY` — Rawst Berry | A hold item that heals a burn in battle. | Sim | Script (dado ao jogador): data/maps/VioletCity/scripts.inc:1128, data/maps/VioletCity/scripts.pory:563 \| Sorteio de pool (Route30 Berry Master, comum): …/maps/Route30_House/scripts.inc (Route30_House) |
| `ITEM_RAZZ_BERRY` — Razz Berry | {POKEBLOCK} ingredient. Plant in loamy soil to grow Razz. | Sim | Sorteio de pool (Route30 Berry Master, comum): …/maps/Route30_House/scripts.inc (Route30_House) |
| `ITEM_RINDO_BERRY` — Rindo Berry | A hold item that weakens a Grass move if weak to it. | Sim | Loja / pokemart: …owerShop/scripts.inc (GoldenrodCity_FlowerShop), …werShop/scripts.pory (GoldenrodCity_FlowerShop) \| Sorteio de pool (Route30 Berry Master, comum): …/maps/Route30_House/scripts.inc (Route30_House) |
| `ITEM_ROSELI_BERRY` — Roseli Berry | A hold item that weakens a Fairy move if weak to it. | Sim | Loja / pokemart: …owerShop/scripts.inc (GoldenrodCity_FlowerShop), …werShop/scripts.pory (GoldenrodCity_FlowerShop) \| Sorteio de pool (Route30 Berry Master, comum): …/maps/Route30_House/scripts.inc (Route30_House) |
| `ITEM_ROWAP_BERRY` — Rowap Berry | If hit by a special move, it will hurt the attacker a bit. | Sim | Sorteio de pool (Route30 Berry Master, raro pos-Liga): …/maps/Route30_House/scripts.inc (Route30_House) |
| `ITEM_SALAC_BERRY` — Salac Berry | A hold item that raises Speed in a pinch. | Sim | Sorteio de pool (Route30 Berry Master, raro pos-Liga): …/maps/Route30_House/scripts.inc (Route30_House) |
| `ITEM_SHUCA_BERRY` — Shuca Berry | A hold item that weakens a Ground move if weak to it. | Sim | Loja / pokemart: …owerShop/scripts.inc (GoldenrodCity_FlowerShop), …werShop/scripts.pory (GoldenrodCity_FlowerShop) \| Sorteio de pool (Route30 Berry Master, comum): …/maps/Route30_House/scripts.inc (Route30_House) |
| `ITEM_SITRUS_BERRY` — Sitrus Berry | A hold item that restores the user's HP a little. | Sim | Item escondido (hidden_item): Route49 \| Script (dado ao jogador): data/maps/VioletCity/scripts.inc:1111, data/maps/VioletCity/scripts.pory:543 \| Sorteio de pool (Route30 Berry Master, comum): …/maps/Route30_House/scripts.inc (Route30_House) |
| `ITEM_SPELON_BERRY` — Spelon Berry | {POKEBLOCK} ingredient. Plant in loamy soil to grow Spelon. | Sim | Sorteio de pool (Route30 Berry Master, comum): …/maps/Route30_House/scripts.inc (Route30_House) |
| `ITEM_STARF_BERRY` — Starf Berry | A hold item that sharply boosts a stat in a pinch. | Sim | Sorteio de pool (Route30 Berry Master, raro pos-Liga): …/maps/Route30_House/scripts.inc (Route30_House) |
| `ITEM_TAMATO_BERRY` — Tamato Berry | Makes a Pokémon friendly but lowers base Speed. | Sim | Loja / pokemart: …/scripts.inc (GoldenrodCity_DepartmentStore_3F) \| Sorteio de pool (Route30 Berry Master, comum): …/maps/Route30_House/scripts.inc (Route30_House) |
| `ITEM_TANGA_BERRY` — Tanga Berry | A hold item that weakens a Bug move if weak to it. | Sim | Loja / pokemart: …owerShop/scripts.inc (GoldenrodCity_FlowerShop), …werShop/scripts.pory (GoldenrodCity_FlowerShop) \| Sorteio de pool (Route30 Berry Master, comum): …/maps/Route30_House/scripts.inc (Route30_House) |
| `ITEM_WACAN_BERRY` — Wacan Berry | A hold item that weakens a Electric move if weak to it. | Sim | Loja / pokemart: …owerShop/scripts.inc (GoldenrodCity_FlowerShop), …werShop/scripts.pory (GoldenrodCity_FlowerShop) \| Sorteio de pool (Route30 Berry Master, comum): …/maps/Route30_House/scripts.inc (Route30_House) |
| `ITEM_WATMEL_BERRY` — Watmel Berry | {POKEBLOCK} ingredient. Plant in loamy soil to grow Watmel. | Sim | Sorteio de pool (Route30 Berry Master, comum): …/maps/Route30_House/scripts.inc (Route30_House) |
| `ITEM_WEPEAR_BERRY` — Wepear Berry | {POKEBLOCK} ingredient. Plant in loamy soil to grow Wepear. | Sim | Sorteio de pool (Route30 Berry Master, comum): …/maps/Route30_House/scripts.inc (Route30_House) |
| `ITEM_WIKI_BERRY` — Wiki Berry | A hold item that restores HP but may confuse. | Sim | Script (dado ao jogador): data/maps/VioletCity/scripts.inc:1096, data/maps/VioletCity/scripts.pory:528 \| Script (dado ao jogador, var computado): data/maps/Route120/scripts.inc:114 \| Sorteio de pool (Route30 Berry Master, comum): …/maps/Route30_House/scripts.inc (Route30_House) |
| `ITEM_YACHE_BERRY` — Yache Berry | A hold item that weakens a Ice move if weak to it. | Sim | Loja / pokemart: …owerShop/scripts.inc (GoldenrodCity_FlowerShop), …werShop/scripts.pory (GoldenrodCity_FlowerShop) \| Sorteio de pool (Route30 Berry Master, comum): …/maps/Route30_House/scripts.inc (Route30_House) |

## TMs & HMs (110)

| Item | O que faz | Obtível in-game? | Como se obtém |
|---|---|---|---|
| `ITEM_HM_CUT` — HM01 Cut | Attacks the foe with sharp blades or claws. | Sim | Script (dado ao jogador): data/maps/IlexForest/scripts.inc:384, data/maps/IlexForest/scripts.pory:192 |
| `ITEM_HM_DIVE` — HM08 Dive | Dives underwater the 1st turn, then attacks next turn. | Sim | Script (dado ao jogador): data/maps/NewBarkTown_House3/scripts.inc:209, data/maps/NewBarkTown_House3/scripts.pory:165 |
| `ITEM_HM_FLASH` — HM05 Flash | Looses a powerful blast of light that reduces accuracy. | Sim | Script (dado ao jogador): data/maps/SproutTower_3F/scripts.inc:226, data/maps/SproutTower_3F/scripts.pory:113 |
| `ITEM_HM_FLY` — HM02 Fly | Flies up on the first turn, then attacks next turn. | Sim | Script (dado ao jogador): data/maps/CianwoodCity/scripts.inc:193, data/maps/CianwoodCity/scripts.inc:430 |
| `ITEM_HM_ROCK_CLIMB` — HM09 Rock Climb | A charging attack that may confuse the foe. | Sim | Script (dado ao jogador): data/maps/VictoryRoadKanto_1F/scripts.inc:26 |
| `ITEM_HM_ROCK_SMASH` — HM06 Rock Smash | A rock-crushingly tough attack that may lower Defense. | Sim | Script (dado ao jogador): data/maps/Route36/scripts.inc:52, data/maps/Route36/scripts.pory:26 |
| `ITEM_HM_STRENGTH` — HM04 Strength | Builds enormous power, then slams the foe. | Sim | Script (dado ao jogador): data/maps/OlivineCity_Cafe/scripts.inc:70, data/maps/OlivineCity_Cafe/scripts.pory:35 |
| `ITEM_HM_SURF` — HM03 Surf | Creates a huge wave, then crashes it down on the foe. | Sim | Script (additem): data/scripts/debug.inc:48 \| Script (dado ao jogador): data/maps/EcruteakCity_Theater/scripts.inc:307, data/maps/EcruteakCity_Theater/scripts.inc:329, data/maps/NewBarkTown_Lab/scripts.inc:1070 (+1) |
| `ITEM_HM_WATERFALL` — HM07 Waterfall | Attacks the foe with enough power to climb waterfalls. | Sim | Item ball no mapa (object_event): IcePath_1F |
| `ITEM_HM_WHIRLPOOL` — HM10 Whirlpool | Traps the foe in a whirlpool for several turns. | Sim | Script (dado ao jogador): data/maps/RocketHideout_B2F/scripts.inc:535 |
| `ITEM_TM_ACROBATICS` — TM62 Acrobatics | Hits harder if the user holds no item. | Sim | Loja / pokemart: …hornCity_Mart/scripts.inc (BlackthornCity_Mart), …ornCity_Mart/scripts.pory (BlackthornCity_Mart) |
| `ITEM_TM_AERIAL_ACE` — TM40 Aerial Ace | An extremely fast attack that can't be avoided. | Sim | Item ball no mapa (object_event): Route37 |
| `ITEM_TM_ATTRACT` — TM45 Attract | Makes it tough to attack a foe of the opposite gender. | Sim | Script (dado ao jogador): data/maps/GoldenrodCity_Gym/scripts.inc:162, data/maps/GoldenrodCity_Gym/scripts.pory:81 |
| `ITEM_TM_AURORA_VEIL` — TM70 Aurora Veil | Weakens physical and special hits during hail. | Sim | Item ball no mapa (object_event): SnowtopMountainOutside |
| `ITEM_TM_BLIZZARD` — TM14 Blizzard | A snow-and-wind attack that may inflict frostbite. A brutal snow-and- wind attack that may freeze the foe. | Sim | Item ball no mapa (object_event): IcePath_Depths |
| `ITEM_TM_BRICK_BREAK` — TM31 Brick Break | Destroys barriers like Light Screen and causes damage. | Sim | Loja / pokemart: …ntoVillage_Mart/scripts.inc (RintoVillage_Mart), …toVillage_Mart/scripts.pory (RintoVillage_Mart) |
| `ITEM_TM_BRUTAL_SWING` — TM59 Brutal Swing | Swings around to damage everything near the user. | Sim | Loja / pokemart: …OlivineCity_Mart/scripts.inc (OlivineCity_Mart), …livineCity_Mart/scripts.pory (OlivineCity_Mart) |
| `ITEM_TM_BULK_UP` — TM08 Bulk Up | Bulks up the body to boost both Attack & Defense. | Sim | Script (dado ao jogador): data/maps/CianwoodGym/scripts.inc:71 |
| `ITEM_TM_BULLDOZE` — TM78 Bulldoze | Damages everyone, lowering the Speed of all hit. | Sim | Item ball no mapa (object_event): VajraDesert |
| `ITEM_TM_CALM_MIND` — TM04 Calm Mind | Raises Sp. Atk and Sp. Def by focusing the mind. | Sim | Item ball no mapa (object_event): GoldenrodCity_UndergroundStorage |
| `ITEM_TM_CHARGE_BEAM` — TM57 Charge Beam | Attacks with an electric charge. May raise Sp. Atk. | Sim | Loja / pokemart: …OlivineCity_Mart/scripts.inc (OlivineCity_Mart), …livineCity_Mart/scripts.pory (OlivineCity_Mart) |
| `ITEM_TM_DARK_PULSE` — TM97 Dark Pulse | Releases a horrible aura. May also make the foe flinch. | Sim | Item ball no mapa (object_event): SproutTower_Basement |
| `ITEM_TM_DAZZLING_GLEAM` — TM99 Dazzling Gleam | A powerful fairy attack damaging foe with a flash. | Sim | Item ball no mapa (object_event): MeteorCave1 |
| `ITEM_TM_DIG` — TM77 Dig | Burrows on the first turn, then strikes on the next turn. | Sim | Loja / pokemart: …/scripts.inc (GoldenrodCity_DepartmentStore_5F), …scripts.pory (GoldenrodCity_DepartmentStore_5F) |
| `ITEM_TM_DOUBLE_TEAM` — TM32 Double Team | Creates illusory copies to enhance elusiveness. | Sim | Script (dado ao jogador): …a/maps/MauvilleCity_GameCorner/scripts.inc:1940, …a/maps/MauvilleCity_GameCorner/scripts.pory:970 |
| `ITEM_TM_DRAGON_CLAW` — TM02 Dragon Claw | Hooks and slashes the foe with long, sharp claws. | Sim | Script (dado ao jogador): data/maps/DragonsDen_Cavern/scripts.inc:114, data/maps/DragonsDen_Cavern/scripts.pory:57 |
| `ITEM_TM_DRAGON_TAIL` — TM82 Dragon Tail | Knocks away foe and drags out another Pokémon. | Sim | Loja / pokemart: …hornCity_Mart/scripts.inc (BlackthornCity_Mart), …ornCity_Mart/scripts.pory (BlackthornCity_Mart) |
| `ITEM_TM_DRAINING_KISS` — TM64 Draining Kiss | Steals the foe's HP with a kiss, healing over half the damage. | Sim | Loja / pokemart: …OlivineCity_Mart/scripts.inc (OlivineCity_Mart), …livineCity_Mart/scripts.pory (OlivineCity_Mart) |
| `ITEM_TM_DRAIN_PUNCH` — TM85 Drain Punch | The user heals half of the damage. dealt with a punch. | Sim | Item ball no mapa (object_event): Route39 |
| `ITEM_TM_EARTHQUAKE` — TM26 Earthquake | Causes a quake that has no effect on flying foes. | Sim | Item ball no mapa (object_event): VictoryRoadKanto_1F |
| `ITEM_TM_ECHOED_VOICE` — TM49 Echoed Voice | An echoing voice. Repeated uses boost its power. | Sim | Script (dado ao jogador): data/maps/Route39_FarmHouse/scripts.inc:17 |
| `ITEM_TM_ENERGY_BALL` — TM53 Energy Ball | Draws power from nature to attack. May lower Sp. Def. | Sim | Item ball no mapa (object_event): TohjoPass |
| `ITEM_TM_FACADE` — TM42 Facade | Raises Attack when poisoned, burned, or paralyzed. | Sim | Loja / pokemart: …ntoVillage_Mart/scripts.inc (RintoVillage_Mart), …toVillage_Mart/scripts.pory (RintoVillage_Mart) |
| `ITEM_TM_FALSE_SWIPE` — TM54 False Swipe | A restrained hit that leaves the foe with 1 HP. | Sim | Script (dado ao jogador): …aps/Gate_GoldenrodCity_Route35/scripts.pory:151, …maps/Gate_GoldenrodCity_Route35/scripts.inc:280 |
| `ITEM_TM_FIRE_BLAST` — TM38 Fire Blast | A powerful fire attack that may burn the foe. | Sim | Item ball no mapa (object_event): MtMortar_Depths_1 |
| `ITEM_TM_FIRE_PUNCH` — TM69 Fire Punch | A fiery punch that may burn the target. | Sim | Loja / pokemart: …/scripts.inc (GoldenrodCity_DepartmentStore_5F), …scripts.pory (GoldenrodCity_DepartmentStore_5F) |
| `ITEM_TM_FLAMETHROWER` — TM35 Flamethrower | Looses a stream of fire that may burn the foe. | Sim | Script (dado ao jogador): …a/maps/MauvilleCity_GameCorner/scripts.inc:1990, …a/maps/MauvilleCity_GameCorner/scripts.pory:995 |
| `ITEM_TM_FLAME_CHARGE` — TM43 Flame Charge | Surround the user with flames to ram Foe. Raises speed | Sim | Item ball no mapa (object_event): UnionCave_B1F |
| `ITEM_TM_FLASH_CANNON` — TM91 Flash Cannon | Releases light energy at the foe lowering Sp. Def. | Sim | Script (dado ao jogador): data/maps/OlivineCity_Gym/scripts.inc:500, data/maps/OlivineCity_Gym/scripts.pory:250 |
| `ITEM_TM_FLING` — TM56 Fling | The user flings its held item at the foe to attack. | Sim | Item ball no mapa (object_event): SnowtopMountain_B1F |
| `ITEM_TM_FOCUS_BLAST` — TM52 Focus Blast | A focused blast. May lower the target's Sp. Def. | Sim | Item ball no mapa (object_event): VajraDesertEast |
| `ITEM_TM_FROST_BREATH` — TM79 Frost Breath | Blows a cold breath on the foe. Always critical-hits. | Sim | Item ball no mapa (object_event): SnowtopMountainOutside |
| `ITEM_TM_FRUSTRATION` — TM21 Frustration | The less the user likes you, the more powerful this move. | Sim | Script (dado ao jogador): …e_Route40_TrainerHill_Courtyard/scripts.pory:18, …te_Route40_TrainerHill_Courtyard/scripts.inc:32 |
| `ITEM_TM_GIGA_DRAIN` — TM87 Giga Drain | Drains the foe's HP, healing half of the damage dealt. | Sim | Loja / pokemart: …/AzaleaTown_Mart/scripts.pory (AzaleaTown_Mart), …s/AzaleaTown_Mart/scripts.inc (AzaleaTown_Mart) |
| `ITEM_TM_GIGA_IMPACT` — TM68 Giga Impact | The user charges with all its power. Must recharge. | Sim | Loja / pokemart: …aps/SafariZoneGate/scripts.inc (SafariZoneGate), …ps/SafariZoneGate/scripts.pory (SafariZoneGate) |
| `ITEM_TM_GRASS_KNOT` — TM86 Grass Knot | Trips the foe. Heavier foes take more damage. | Sim | Item ball no mapa (object_event): DeepIlexForest |
| `ITEM_TM_GYRO_BALL` — TM74 Gyro Ball | Hits harder the slower the user is. | Sim | Item ball no mapa (object_event): RailwayCave |
| `ITEM_TM_HAIL` — TM07 Hail | Raises the Defense of Ice type {PKMN} for 5 turns. | Sim | Script (dado ao jogador): data/maps/MahoganyTown_Gym/scripts.inc:178, data/maps/MahoganyTown_Gym/scripts.pory:89 |
| `ITEM_TM_HEX` — TM05 Hex | Doubles in power against ailing foes. | Sim | Script (dado ao jogador): data/maps/EcruteakCity_House3/scripts.inc:17, data/maps/EcruteakCity_House3/scripts.pory:18 |
| `ITEM_TM_HIDDEN_POWER` — TM Hidden Power | The attack power varies among different Pokémon. | Sim | Script (dado ao jogador): data/maps/LakeOfRage_House1/scripts.inc:20, data/maps/LakeOfRage_House1/scripts.pory:10 |
| `ITEM_TM_HONE_CLAWS` — TM76 Hone Claws | Sharpens claws to raise Attack and accuracy. | Sim | Loja / pokemart: …/VioletCity_Mart/scripts.pory (VioletCity_Mart), …s/VioletCity_Mart/scripts.inc (VioletCity_Mart) |
| `ITEM_TM_HYPER_BEAM` — TM15 Hyper Beam | Powerful, but needs recharging the next turn. | Sim | Loja / pokemart: …/scripts.inc (GoldenrodCity_DepartmentStore_5F), …scripts.pory (GoldenrodCity_DepartmentStore_5F) |
| `ITEM_TM_ICE_BEAM` — TM13 Ice Beam | Fires an icy cold beam that may inflict frostbite. freeze the foe. | Sim | Script (dado ao jogador): …/maps/MauvilleCity_GameCorner/scripts.pory:1020, …a/maps/MauvilleCity_GameCorner/scripts.inc:2040 |
| `ITEM_TM_ICE_PUNCH` — TM100 Ice Punch | An icy cold punch that may inflict frostbite. freeze the foe. | Sim | Loja / pokemart: …/scripts.inc (GoldenrodCity_DepartmentStore_5F), …scripts.pory (GoldenrodCity_DepartmentStore_5F) |
| `ITEM_TM_ICE_SPINNER` — TM94 Ice Spinner | Covers its feet in ice and spins into the foe. | Sim | Item ball no mapa (object_event): IcePath_B2F |
| `ITEM_TM_INFESTATION` — TM83 Infestation | The foe is infested and attacked for four to five turns. | Sim | Item ball no mapa (object_event): OlivineCity_Lighthouse \| Loja / pokemart: …/AzaleaTown_Mart/scripts.pory (AzaleaTown_Mart), …s/AzaleaTown_Mart/scripts.inc (AzaleaTown_Mart) |
| `ITEM_TM_LEECH_LIFE` — TM28 Leech Life | Drains the foe and restores half the damage dealt. | Sim | Item ball no mapa (object_event): NationalPark_Normal |
| `ITEM_TM_LIGHT_SCREEN` — TM16 Light Screen | Creates a wall of light that lowers Sp. Atk damage. | Sim | Loja / pokemart: …/scripts.inc (GoldenrodCity_DepartmentStore_5F), …scripts.pory (GoldenrodCity_DepartmentStore_5F) |
| `ITEM_TM_LOW_SWEEP` — TM47 Low Sweep | Attacks target's legs. Lowers their speed. | Sim | Loja / pokemart: …aps/SafariZoneGate/scripts.inc (SafariZoneGate), …ps/SafariZoneGate/scripts.pory (SafariZoneGate) |
| `ITEM_TM_NATURE_POWER` — TM96 Nature Power | The effects vary depending on the user's environment. | Sim | Item ball no mapa (object_event): RuinsOfAlph_Outside |
| `ITEM_TM_OVERHEAT` — TM50 Overheat | Enables full-power attack, but sharply lowers Sp. Atk. | Sim | Item ball no mapa (object_event): AbandonedRocketHideout |
| `ITEM_TM_PAYBACK` — TM66 Payback | The power doubles if the user moves after the target. | Sim | Loja / pokemart: …hoganyTown_Shop/scripts.inc (MahoganyTown_Shop) |
| `ITEM_TM_PLAY_ROUGH` — TM98 Play Rough | Plays rough with the foe. May lower Attack. | Sim | Loja / pokemart: …ntoVillage_Mart/scripts.inc (RintoVillage_Mart), …toVillage_Mart/scripts.pory (RintoVillage_Mart) |
| `ITEM_TM_POISON_JAB` — TM84 Poison Jab | Jabs the foe with poison. May also poison them. | Sim | Item ball no mapa (object_event): Route50 |
| `ITEM_TM_PROTECT` — TM17 Protect | Negates all damage, but may fail if used in succession. | Sim | Loja / pokemart: …/scripts.inc (GoldenrodCity_DepartmentStore_5F), …scripts.pory (GoldenrodCity_DepartmentStore_5F) |
| `ITEM_TM_PSYCHIC` — TM29 Psychic | A powerful psychic attack that may lower Sp. Def. | Sim | Script (dado ao jogador): …a/maps/MauvilleCity_GameCorner/scripts.inc:1964, …a/maps/MauvilleCity_GameCorner/scripts.pory:982 |
| `ITEM_TM_PSYSHOCK` — TM03 Psyshock | Cuts with a psychic wave. It is physical. | Sim | Item ball no mapa (object_event): BattleFactoryGrounds |
| `ITEM_TM_RAIN_DANCE` — TM18 Rain Dance | Raises the power of Water-type moves for 5 turns. | Sim | Script (dado ao jogador): data/maps/SlowpokeWell_B2F/scripts.inc:34 |
| `ITEM_TM_REFLECT` — TM33 Reflect | Creates a wall of light that weakens physical attacks. | Sim | Loja / pokemart: …/scripts.inc (GoldenrodCity_DepartmentStore_5F), …scripts.pory (GoldenrodCity_DepartmentStore_5F) |
| `ITEM_TM_REST` — TM44 Rest | The user sleeps for 2 turns to restore health and status. | Sim | Script (dado ao jogador): data/maps/RintoVillage/scripts.inc:90, data/maps/RintoVillage/scripts.pory:78 |
| `ITEM_TM_RETURN` — TM27 Return | The more the user likes you, the more powerful this move. | Sim | Script (dado ao jogador): …ldenrodCity_DepartmentStore_5F/scripts.pory:105, …oldenrodCity_DepartmentStore_5F/scripts.inc:188 |
| `ITEM_TM_ROCK_SLIDE` — TM80 Rock Slide | Hurls boulders at foes. May make them flinch. | Sim | Item ball no mapa (object_event): Route49 |
| `ITEM_TM_ROCK_TOMB` — TM39 Rock Tomb | Stops the foe from moving with rocks. May lower Speed. | Sim | Item ball no mapa (object_event): Route35 |
| `ITEM_TM_ROOST` — TM19 Roost | Restores half HP and removes the Flying type. | Sim | Script (dado ao jogador): data/maps/VioletCity_Gym/scripts.inc:90, data/maps/VioletCity_Gym/scripts.pory:45 |
| `ITEM_TM_ROUND` — TM48 Round | A song attack. Allies may join to boost power. | Sim | Script (dado ao jogador): …maps/GoldenrodCity_RadioTower_3F/scripts.inc:70 |
| `ITEM_TM_SAFEGUARD` — TM20 Safeguard | Prevents status abnormality with a mystical power. | Sim | Loja / pokemart: …oveCity_Mart/scripts.inc (CherrygroveCity_Mart), …veCity_Mart/scripts.pory (CherrygroveCity_Mart) |
| `ITEM_TM_SANDSTORM` — TM37 Sandstorm | Causes a sandstorm that hits the foe over several turns. | Sim | Script (dado ao jogador): data/maps/Route27_House/scripts.inc:34 |
| `ITEM_TM_SCALD` — TM55 Scald | Shoots boiling water at the foe. May leave a burn. | Sim | Item ball no mapa (object_event): VajraPyramidOutside |
| `ITEM_TM_SHADOW_BALL` — TM30 Shadow Ball | Hurls a dark lump at the foe. It may lower Sp. Def. | Sim | Script (dado ao jogador): data/maps/EcruteakCity_Gym/scripts.inc:110, data/maps/EcruteakCity_Gym/scripts.pory:55 |
| `ITEM_TM_SHADOW_CLAW` — TM65 Shadow Claw | Slashes with claws of shadows. High critical-hit ratio. | Sim | Item ball no mapa (object_event): Route42 |
| `ITEM_TM_SKY_DROP` — TM58 Sky Drop | Takes the foe into the sky and drops them the next turn. | Sim | Loja / pokemart: …hornCity_Mart/scripts.inc (BlackthornCity_Mart), …ornCity_Mart/scripts.pory (BlackthornCity_Mart) |
| `ITEM_TM_SLUDGE_BOMB` — TM36 Sludge Bomb | Hurls sludge at the foe. It may poison the foe. | Sim | Script (dado ao jogador): data/maps/Gate_Route43/scripts.inc:56 |
| `ITEM_TM_SLUDGE_WAVE` — TM34 Sludge Wave | Hits all around with sludge. May poison targets. | Sim | Item ball no mapa (object_event): OlivineCity |
| `ITEM_TM_SMACK_DOWN` — TM23 Smack Down | Slams the foe with a rock. It will ground the target. | Sim | Script (dado ao jogador): data/maps/GoldenrodCity/scripts.inc:1024, data/maps/GoldenrodCity/scripts.pory:546 |
| `ITEM_TM_SMART_STRIKE` — TM67 Smart Strike | Stabs with a sharp horn. This attack never misses. | Sim | Item ball no mapa (object_event): GoldenrodApartment |
| `ITEM_TM_SNARL` — TM95 Snarl | Yells at the foe lowering their Sp. Atk. | Sim | Loja / pokemart: …ruteakCity_Mart/scripts.inc (EcruteakCity_Mart), …uteakCity_Mart/scripts.pory (EcruteakCity_Mart) |
| `ITEM_TM_SOLAR_BEAM` — TM22 Solar Beam | Absorbs sunlight in the 1st turn, then attacks next turn. | Sim | Item ball no mapa (object_event): Route27 |
| `ITEM_TM_STEEL_WING` — TM51 Steel Wing | Hits with steel wings. May raise user's Defense. | Sim | Script (dado ao jogador): data/maps/Route28_House/scripts.inc:8 |
| `ITEM_TM_STONE_EDGE` — TM71 Stone Edge | Stabs the foe with sharp stones. High critical-hit ratio. | Sim | Item ball no mapa (object_event): KitakamiWell_B1F |
| `ITEM_TM_SUBSTITUTE` — TM90 Substitute | The user cuts some HP to create a copy of itself. | Sim | Loja / pokemart: …hoganyTown_Shop/scripts.inc (MahoganyTown_Shop) |
| `ITEM_TM_SUNNY_DAY` — TM11 Sunny Day | Raises the power of Fire-type moves for 5 turns. | Sim | Item ball no mapa (object_event): IlexForest |
| `ITEM_TM_SWORDS_DANCE` — TM75 Swords Dance | A frenetic dance that sharply raises the user's Attack. | Sim | Item ball no mapa (object_event): KitakamiMountain2F |
| `ITEM_TM_TAUNT` — TM12 Taunt | Enrages the foe so it can only use attack moves. | Sim | Item ball no mapa (object_event): BurnedTower_B1F |
| `ITEM_TM_THIEF` — TM46 Thief | While attacking, it may steal the foe's held item. | Sim | Item ball no mapa (object_event): RocketHideout_B2F |
| `ITEM_TM_THUNDER` — TM25 Thunder | Strikes the foe with a thunderbolt. It may paralyze. | Sim | Script (dado ao jogador): …/maps/MauvilleCity_GameCorner/scripts.pory:1007, …a/maps/MauvilleCity_GameCorner/scripts.inc:2014 |
| `ITEM_TM_THUNDERBOLT` — TM24 Thunderbolt | A powerful electric attack that may cause paralysis. | Sim | Item ball no mapa (object_event): RailwayCave_3F |
| `ITEM_TM_THUNDER_PUNCH` — TM63 Thunder Punch | An electric punch. May paralyze. | Sim | Loja / pokemart: …/scripts.inc (GoldenrodCity_DepartmentStore_5F), …scripts.pory (GoldenrodCity_DepartmentStore_5F) |
| `ITEM_TM_THUNDER_WAVE` — TM73 Thunder Wave | A weak electric charge that causes paralysis. | Sim | Item ball no mapa (object_event): Route41 |
| `ITEM_TM_TORMENT` — TM41 Torment | Prevents the foe from using the same move in a row. | Sim | Item ball no mapa (object_event): BurnedTower_1F |
| `ITEM_TM_TOXIC` — TM06 Toxic | Poisons the foe with a toxin that gradually worsens. | Sim | Item ball no mapa (object_event): FoggyForest |
| `ITEM_TM_TRAILBLAZE` — TM60 Trailblaze | Attack's suddenly and boosts user's speed. | Sim | Loja / pokemart: …ruteakCity_Mart/scripts.inc (EcruteakCity_Mart), …uteakCity_Mart/scripts.pory (EcruteakCity_Mart) |
| `ITEM_TM_TRICK_ROOM` — TM92 Trick Room | Causes slower Pokémon to move first for 5 turns. | Sim | Loja / pokemart: …ruteakCity_Mart/scripts.inc (EcruteakCity_Mart), …uteakCity_Mart/scripts.pory (EcruteakCity_Mart) |
| `ITEM_TM_U_TURN` — TM89 U-Turn | Attacks and rushes back to switch with a party Pokémon. | Sim | Script (dado ao jogador): data/maps/AzaleaTown_Gym/scripts.inc:1100, data/maps/AzaleaTown_Gym/scripts.pory:550 |
| `ITEM_TM_VENOSHOCK` — TM09 Venoshock | Drenches target with poison. Strong against poisoned. | Sim | Loja / pokemart: …aps/SafariZoneGate/scripts.inc (SafariZoneGate), …ps/SafariZoneGate/scripts.pory (SafariZoneGate) |
| `ITEM_TM_VOLT_SWITCH` — TM72 Volt Switch | Attacks and rushes back to switch with a party Pokémon. | Sim | Item ball no mapa (object_event): VajraDesertEast |
| `ITEM_TM_WATER_PULSE` — TM88 Water Pulse | Attacks with a water pulse that may also confuse the foe. | Sim | Item ball no mapa (object_event): Kitakami_Temple_Bedroom |
| `ITEM_TM_WILD_CHARGE` — TM93 Wild Charge | An electric charge smashes the foe, damaging the user. | Sim | Item ball no mapa (object_event): KitakamiBorder |
| `ITEM_TM_WILL_O_WISP` — TM61 Will-o-Wisp | Shoots a bluish- white flame to burn the foe. | Sim | Loja / pokemart: …ruteakCity_Mart/scripts.inc (EcruteakCity_Mart), …uteakCity_Mart/scripts.pory (EcruteakCity_Mart) |
| `ITEM_TM_WORK_UP` — TM01 Work Up | Rouses the user to raise Attack and Sp. Atk. | Sim | Item ball no mapa (object_event): Route40 |
| `ITEM_TM_X_SCISSOR` — TM81 X-Scissor | The user attacks foe with crossed scythes or claws. | Sim | Loja / pokemart: …/AzaleaTown_Mart/scripts.pory (AzaleaTown_Mart), …s/AzaleaTown_Mart/scripts.inc (AzaleaTown_Mart) |

## Mega Stones (112)

| Item | O que faz | Obtível in-game? | Como se obtém |
|---|---|---|---|
| `ITEM_ABOMASITE` — Abomasite | This stone enables Abomasnow to Mega Evolve in battle. | Não | - |
| `ITEM_ABSOLITE` — Absolite | This stone enables Absol to Mega Evolve in battle. | Não | - |
| `ITEM_ABSOLITE_Z` — Absolite Z | This stone enables Absol to Mega Evolve in battle. | Não | - |
| `ITEM_AERODACTYLITE` — Aerodactylite | This stone enables Aerodactyl to Mega Evolve in battle. | Não | - |
| `ITEM_AGGRONITE` — Aggronite | This stone enables Aggron to Mega Evolve in battle. | Não | - |
| `ITEM_ALAKAZITE` — Alakazite | This stone enables Alakazam to Mega Evolve in battle. | Não | - |
| `ITEM_ALTARIANITE` — Altarianite | This stone enables Altaria to Mega Evolve in battle. | Não | - |
| `ITEM_AMPHAROSITE` — Ampharosite | This stone enables Ampharos to Mega Evolve in battle. | Não | - |
| `ITEM_AUDINITE` — Audinite | This stone enables Audino to Mega Evolve in battle. | Não | - |
| `ITEM_BANETTITE` — Banettite | This stone enables Banette to Mega Evolve in battle. | Não | - |
| `ITEM_BARBARACITE` — Barbaracite | This stone enables Barbaracle to Mega Evolve in battle. | Não | - |
| `ITEM_BAXCALIBRITE` — Baxcalibrite | This stone enables Baxcalibur to Mega Evolve in battle. | Não | - |
| `ITEM_BEEDRILLITE` — Beedrillite | This stone enables Beedrill to Mega Evolve in battle. | Não | - |
| `ITEM_BLASTOISINITE` — Blastoisinite | This stone enables Blastoise to Mega Evolve in battle. | Não | - |
| `ITEM_BLAZIKENITE` — Blazikenite | This stone enables Blaziken to Mega Evolve in battle. | Não | - |
| ★ `ITEM_BONDSTONE` — Bondstone | A stone that lets your partner Mega Evolve. | Sim | Script (dado ao jogador): data/maps/NewBarkTown_Lab/scripts.inc:2372, data/maps/NewBarkTown_Lab/scripts.pory:1191 |
| `ITEM_BUGTITE` — Bugtite | Allows certain Pokemon to Mega Evolve into Bug-type form. | Sim | Item ball no mapa (object_event): NationalPark_Normal |
| `ITEM_CAMERUPTITE` — Cameruptite | This stone enables Camerupt to Mega Evolve in battle. | Não | - |
| `ITEM_CHANDELURITE` — Chandelurite | This stone enables Chandelure to Mega Evolve in battle. | Não | - |
| `ITEM_CHARIZARDITE_X` — Charizardite X | This stone enables Charizard to Mega Evolve in battle. | Não | - |
| `ITEM_CHARIZARDITE_Y` — Charizardite Y | This stone enables Charizard to Mega Evolve in battle. | Não | - |
| `ITEM_CHESNAUGHTITE` — Chesnaughtite | This stone enables Chesnaught to Mega Evolve in battle. | Não | - |
| `ITEM_CHIMECHITE` — Chimechite | This stone enables Chimecho to Mega Evolve in battle. | Não | - |
| `ITEM_CLEFABLITE` — Clefablite | This stone enables Clefable to Mega Evolve in battle. | Não | - |
| `ITEM_CRABOMINITE` — Crabominite | This stone enables Crabominable to Mega in battle. | Não | - |
| `ITEM_DARKRANITE` — Darkranite | This stone enables Darkrai to Mega Evolve in battle. | Não | - |
| `ITEM_DARKTITE` — Darktite | Allows certain Pokemon to Mega Evolve into Dark-type form. | Sim | Item ball no mapa (object_event): RocketHideout_B3F |
| `ITEM_DELPHOXITE` — Delphoxite | This stone enables Delphox to Mega Evolve in battle. | Não | - |
| `ITEM_DIANCITE` — Diancite | This stone enables Diancie to Mega Evolve in battle. | Não | - |
| `ITEM_DRAGALGITE` — Dragalgite | This stone enables Dragalge to Mega Evolve in battle. | Não | - |
| `ITEM_DRAGONINITE` — Dragoninite | This stone enables Dragonite to Mega Evolve in battle. | Não | - |
| `ITEM_DRAGOTITE` — Dragotite | Allows certain Pokemon to Mega Evolve into Dragon-type form. | Sim | Item ball no mapa (object_event): DragonsDen_Cavern |
| `ITEM_DRAMPANITE` — Drampanite | This stone enables Drampa to Mega Evolve in battle. | Não | - |
| `ITEM_EELEKTROSSITE` — Eelektrossite | This stone enables Eelektross to Mega Evolve in battle. | Não | - |
| `ITEM_ELECTRITE` — Electrite | Allows certain Pokemon to Mega Evolve into Electric-type form. | Sim | Item ball no mapa (object_event): RailwayCave_2F |
| `ITEM_EMBOARITE` — Emboarite | This stone enables Emboar to Mega Evolve in battle. | Não | - |
| `ITEM_EXCADRITE` — Excadrite | This stone enables Excadrill to Mega Evolve in battle. | Não | - |
| `ITEM_FAIRYTITE` — Fairytite | Allows certain Pokemon to Mega Evolve into Fairy-type form. | Sim | Script (dado ao jogador): …a/maps/Route30_MrPokemonsHouse/scripts.pory:243, …ta/maps/Route30_MrPokemonsHouse/scripts.inc:486 |
| `ITEM_FALINKSITE` — Falinksite | This stone enables Falinks to Mega Evolve in battle. | Não | - |
| `ITEM_FERALIGITE` — Feraligite | This stone enables Feraligatr to Mega Evolve in battle. | Não | - |
| `ITEM_FIGHTITE` — Fightite | Allows certain Pokemon to Mega Evolve into Fighting-type form. | Sim | Item ball no mapa (object_event): DarkCave_NorthSide |
| `ITEM_FIRETITE` — Firetite | Allows certain Pokemon to Mega Evolve into Fire-type form. | Sim | Item ball no mapa (object_event): MtMortar_Depths_1 |
| `ITEM_FLOETTITE` — Floettite | This stone enables Floette to Mega Evolve in battle. | Não | - |
| `ITEM_FLYINGITE` — Flyingite | Allows certain Pokemon to Mega Evolve into Flying-type form. | Sim | Item ball no mapa (object_event): Route47 |
| `ITEM_FROSLASSITE` — Froslassite | This stone enables Froslass to Mega Evolve in battle. | Não | - |
| `ITEM_GALLADITE` — Galladite | This stone enables Gallade to Mega Evolve in battle. | Não | - |
| `ITEM_GARCHOMPITE` — Garchompite | This stone enables Garchomp to Mega Evolve in battle. | Não | - |
| `ITEM_GARCHOMPITE_Z` — Garchompite Z | This stone enables Garchomp to Mega Evolve in battle. | Não | - |
| `ITEM_GARDEVOIRITE` — Gardevoirite | This stone enables Gardevoir to Mega Evolve in battle. | Não | - |
| `ITEM_GENGARITE` — Gengarite | This stone enables Gengar to Mega Evolve in battle. | Não | - |
| `ITEM_GHOSTITE` — Ghostite | Allows certain Pokemon to Mega Evolve into Ghost-type form. | Sim | Item ball no mapa (object_event): SproutTower_Basement |
| ★ `ITEM_GIGANTATITE` — Gigantatite | A stone that lets former Gigantamax {PKMN} Mega Evolve. | Não | - |
| `ITEM_GLALITITE` — Glalitite | This stone enables Glalie to Mega Evolve in battle. | Não | - |
| `ITEM_GLIMMORANITE` — Glimmoranite | This stone enables Glimmora to Mega Evolve in battle. | Não | - |
| `ITEM_GOLISOPITE` — Golisopite | This stone enables Golisopod to Mega Evolve in battle. | Não | - |
| `ITEM_GOLURKITE` — Golurkite | This stone enables Golurk to Mega Evolve in battle. | Não | - |
| `ITEM_GRASSTITE` — Grasstite | Allows certain Pokemon to Mega Evolve into Grass-type form. | Sim | Item ball no mapa (object_event): DeepIlexForest |
| `ITEM_GRENINJITE` — Greninjite | This stone enables Greninja to Mega Evolve in battle. | Não | - |
| `ITEM_GROUNDITE` — Groundite | Allows certain Pokemon to Mega Evolve into Ground-type form. | Sim | Item ball no mapa (object_event): UnionCave_B2F |
| `ITEM_GYARADOSITE` — Gyaradosite | This stone enables Gyarados to Mega Evolve in battle. | Não | - |
| `ITEM_HAWLUCHANITE` — Hawluchanite | This stone enables Hawlucha to Mega Evolve in battle. | Não | - |
| `ITEM_HEATRANITE` — Heatranite | This stone enables Heatran to Mega Evolve in battle. | Não | - |
| `ITEM_HERACRONITE` — Heracronite | This stone enables Heracross to Mega Evolve in battle. | Não | - |
| `ITEM_HOUNDOOMINITE` — Houndoominite | This stone enables Houndoom to Mega Evolve in battle. | Não | - |
| `ITEM_ICETITE` — Icetite | Allows certain Pokemon to Mega Evolve into Ice-type form. | Sim | Item ball no mapa (object_event): IcePath_Depths |
| `ITEM_KANGASKHANITE` — Kangaskhanite | This stone enables Kangaskhan to Mega Evolve in battle. | Não | - |
| `ITEM_LATIASITE` — Latiasite | This stone enables Latias to Mega Evolve in battle. | Não | - |
| `ITEM_LATIOSITE` — Latiosite | This stone enables Latios to Mega Evolve in battle. | Não | - |
| `ITEM_LOPUNNITE` — Lopunnite | This stone enables Lopunny to Mega Evolve in battle. | Não | - |
| `ITEM_LUCARIONITE` — Lucarionite | This stone enables Lucario to Mega Evolve in battle. | Não | - |
| `ITEM_LUCARIONITE_Z` — Lucarionite Z | This stone enables Lucario to Mega Evolve in battle. | Não | - |
| `ITEM_MAGEARNITE` — Magearnite | This stone enables Magearna to Mega Evolve in battle. | Não | - |
| `ITEM_MALAMARITE` — Malamarite | This stone enables Malamar to Mega Evolve in battle. | Não | - |
| `ITEM_MANECTITE` — Manectite | This stone enables Manectric to Mega Evolve in battle. | Não | - |
| `ITEM_MAWILITE` — Mawilite | This stone enables Mawile to Mega Evolve in battle. | Não | - |
| `ITEM_MEDICHAMITE` — Medichamite | This stone enables Medicham to Mega Evolve in battle. | Não | - |
| `ITEM_MEGANIUMITE` — Meganiumite | This stone enables Meganium to Mega Evolve in battle. | Não | - |
| `ITEM_MEOWSTICITE` — Meowsticite | This stone enables Meowstic to Mega Evolve in battle. | Não | - |
| `ITEM_METAGROSSITE` — Metagrossite | This stone enables Metagross to Mega Evolve in battle. | Não | - |
| `ITEM_MEWTWONITE_X` — Mewtwonite X | This stone enables Mewtwo to Mega Evolve in battle. | Não | - |
| `ITEM_MEWTWONITE_Y` — Mewtwonite Y | This stone enables Mewtwo to Mega Evolve in battle. | Não | - |
| `ITEM_NORMALITE` — Normalite | Allows certain Pokemon to Mega Evolve into Normal-type form. | Sim | Item ball no mapa (object_event): TohjoFalls_Cavern |
| `ITEM_PIDGEOTITE` — Pidgeotite | This stone enables Pidgeot to Mega Evolve in battle. | Não | - |
| `ITEM_PINSIRITE` — Pinsirite | This stone enables Pinsir to Mega Evolve in battle. | Não | - |
| `ITEM_POISONTITE` — Poisontite | Allows certain Pokemon to Mega Evolve into Poison-type form. | Sim | Item ball no mapa (object_event): FoggyForest |
| `ITEM_PSYCHITE` — Psychite | Allows certain Pokemon to Mega Evolve into Psychic-type form. | Sim | Item ball no mapa (object_event): MtMortar_2F |
| `ITEM_PYROARITE` — Pyroarite | This stone enables Pyroar to Mega Evolve in battle. | Não | - |
| `ITEM_RAICHUNITE_X` — Raichunite X | This stone enables Raichu to Mega Evolve in battle. | Não | - |
| `ITEM_RAICHUNITE_Y` — Raichunite Y | This stone enables Raichu to Mega Evolve in battle. | Não | - |
| `ITEM_ROCKTITE` — Rocktite | Allows certain Pokemon to Mega Evolve into Rock-type form. | Sim | Item ball no mapa (object_event): Route46 |
| `ITEM_SABLENITE` — Sablenite | This stone enables Sableye to Mega Evolve in battle. | Não | - |
| `ITEM_SALAMENCITE` — Salamencite | This stone enables Salamence to Mega Evolve in battle. | Não | - |
| `ITEM_SCEPTILITE` — Sceptilite | This stone enables Sceptile to Mega Evolve in battle. | Não | - |
| `ITEM_SCIZORITE` — Scizorite | This stone enables Scizor to Mega Evolve in battle. | Não | - |
| `ITEM_SCOLIPITE` — Scolipite | This stone enables Scolipede to Mega Evolve in battle. | Não | - |
| `ITEM_SCOVILLAINITE` — Scovillainite | This stone enables Scovillain to Mega Evolve in battle. | Não | - |
| `ITEM_SCRAFTINITE` — Scraftinite | This stone enables Scrafty to Mega Evolve in battle. | Não | - |
| `ITEM_SHARPEDONITE` — Sharpedonite | This stone enables Sharpedo to Mega Evolve in battle. | Não | - |
| `ITEM_SKARMORITE` — Skarmorite | This stone enables Skarmory to Mega Evolve in battle. | Não | - |
| `ITEM_SLOWBRONITE` — Slowbronite | This stone enables Slowbro to Mega Evolve in battle. | Não | - |
| `ITEM_STARAPTITE` — Staraptite | This stone enables Staraptor to Mega Evolve in battle. | Não | - |
| `ITEM_STARMINITE` — Starminite | This stone enables Starmie to Mega Evolve in battle. | Não | - |
| `ITEM_STEELIXITE` — Steelixite | This stone enables Steelix to Mega Evolve in battle. | Não | - |
| `ITEM_STEELTITE` — Steeltite | Allows certain Pokemon to Mega Evolve into Steel-type form. | Sim | Item ball no mapa (object_event): VictoryRoadKanto_B1F |
| `ITEM_SWAMPERTITE` — Swampertite | This stone enables Swampert to Mega Evolve in battle. | Não | - |
| `ITEM_TATSUGIRINITE` — Tatsugirinite | This stone enables Tatsugiri to Mega Evolve in battle. | Não | - |
| `ITEM_TYRANITARITE` — Tyranitarite | This stone enables Tyranitar to Mega Evolve in battle. | Não | - |
| `ITEM_VENUSAURITE` — Venusaurite | This stone enables Venusaur to Mega Evolve in battle. | Não | - |
| `ITEM_VICTREEBELITE` — Victreebelite | This stone enables Victreebel to Mega Evolve in battle. | Não | - |
| `ITEM_WATERTITE` — Watertite | Allows certain Pokemon to Mega Evolve into Water-type form. | Sim | Item ball no mapa (object_event): WhirlIslands_B1F |
| `ITEM_ZERAORITE` — Zeraorite | This stone enables Zeraora to Mega Evolve in battle. | Não | - |
| `ITEM_ZYGARDITE` — Zygardite | This stone enables Zygarde to Mega Evolve in battle. | Não | - |

## Key Items (92)

| Item | O que faz | Obtível in-game? | Como se obtém |
|---|---|---|---|
| `ITEM_ACRO_BIKE` — Acro Bike | A folding bicycle capable of jumps and wheelies. | Sim | Script (additem): data/scripts/debug.inc:52 |
| `ITEM_AURORA_TICKET` — Aurora Ticket | A ticket required to board the ship to Birth Island. | Sim | Loja / pokemart: …ipts.inc (BattleFrontier_ExchangeServiceCorner) \| Script (dado ao jogador): data/maps/OlivineCity/scripts.inc:614, data/maps/OlivineCity/scripts.pory:307, data/scripts/gift_aurora_ticket.inc:14 |
| `ITEM_BASEMENT_KEY` — Underground Key | The key for the Tunnels beneath the Goldenrod City. | Sim | Script (dado ao jogador): data/maps/MauvilleCity/scripts.inc:407, …aps/GoldenrodCity_RadioTower_5F/scripts.pory:45, …maps/GoldenrodCity_RadioTower_5F/scripts.inc:90 |
| `ITEM_BERRY_POUCH` — Berry Pouch | A convenient container that holds Berries. | Não | - |
| `ITEM_BICYCLE` — Bike | A folding bicycle that is faster than the Running Shoes. | Não | - |
| `ITEM_BIKE_VOUCHER` — Bike Voucher | A voucher for obtaining a bicycle from the Bike Shop. | Não | - |
| ★ `ITEM_BLACK_MIRROR` — Black Mirror | An eerie mirror that does not show your own reflection. | Sim | Item ball no mapa (object_event): KitakamiMountain4F |
| `ITEM_CARD_KEY` — Card Key | A card-type door key used in the Radio Tower. | Sim | Script (dado ao jogador): …GoldenrodCity_UndergroundStorage/scripts.inc:11 |
| `ITEM_CATCHING_CHARM` — Catching Charm | A charm that raises the chance of Critical Captures. | Sim | Item ball no mapa (object_event): FarawayIslandJungle |
| `ITEM_CLEAR_BELL` — Clear Bell | Old fashioned bell that makes a gentle ringing. | Sim | Script (dado ao jogador): data/maps/EcruteakCity_Theater/scripts.inc:896 |
| `ITEM_COIN_CASE` — Coin Case | A case that holds up to 9,999 Coins. | Sim | Item ball no mapa (object_event): GoldenrodCity_UndergroundTunnel |
| `ITEM_CONTEST_PASS` — Contest Pass | The pass required for entering Pokémon Contests. | Sim | Script (additem): …/maps/LilycoveCity_ContestLobby/scripts.inc:353 |
| ★ `ITEM_DARK_CRYSTAL` — Dark Crystal | An ominous crystal radianting an aura of wrath. | Sim | Item ball no mapa (object_event): AbandonedRocketHideoutBackroom |
| `ITEM_DEVON_PARTS` — Devon Parts | A package that contains Devon's machine parts. | Não (só em mapa fora da campanha) | Mencionado em script (verificar): …s/SlateportCity_OceanicMuseum_2F/scripts.inc:69 \| Script (dado ao jogador): data/maps/RusturfTunnel/scripts.inc:305 |
| `ITEM_DEVON_SCOPE` — Devon Scope | A device by Devon that signals any unseeable Pokémon. | Sim | Script (dado ao jogador): data/maps/Route120/scripts.inc:218 |
| `ITEM_DNA_SPLICERS` — DNA Splicers | Splicer that fuses Kyurem and a certain Pokémon. | Não | - |
| `ITEM_DOWSING_MACHINE` — Dowsing Machine | A device that signals an invisible item by sound. | Sim | Script (dado ao jogador): data/maps/EcruteakCity_House4/scripts.inc:35, data/maps/EcruteakCity_House4/scripts.pory:30 |
| `ITEM_DYNAMAX_BAND` — Dynamax Band | A band carrying a Wishing Star that allows Dynamaxing. | Não | - |
| `ITEM_EON_TICKET` — Eon Ticket | The ticket for a ferry to a distant southern island. | Sim | Loja / pokemart: …ipts.inc (BattleFrontier_ExchangeServiceCorner) \| Script (dado ao jogador): data/scripts/cable_club.inc:38, …s/FuchsiaCity_SafariZoneEntrance/scripts.inc:87 |
| `ITEM_ESCAPE_ROPE` — Escape Rope | Use to escape instantly from a cave or a dungeon. | Sim | Item ball no mapa (object_event): MtMortar_1F_North, SproutTower_3F, TinTower_4F (+1) \| Loja / pokemart: …F/scripts.inc (LilycoveCity_DepartmentStore_2F), …arborTown_Mart/scripts.inc (FallarborTown_Mart) |
| `ITEM_EXP_CHARM` — Exp. Charm | A charm that raises the amount of Exp. earned in battle. | Não | - |
| `ITEM_EXP_SHARE` — Exp. Share | This device gives exp. to other party members. | Sim | Script (dado ao jogador): data/maps/Gate_Route31_VioletCity/scripts.inc:94, …ta/maps/Gate_Route31_VioletCity/scripts.pory:49 |
| `ITEM_FAME_CHECKER` — Fame Checker | Stores information on famous people for instant recall. | Não | - |
| `ITEM_GLIMMERING_CHARM` — Glimmering Charm | A charm that will raise the shards from Tera Raids. | Não | - |
| `ITEM_GOLD_TEETH` — Gold Teeth | Gold dentures lost by the Safari Zone's Warden. | Não | - |
| `ITEM_GOOD_ROD` — Good Rod | A decent fishing rod for catching wild Pokémon. | Sim | Script (dado ao jogador): data/maps/OlivineCity_House3/scripts.inc:12 |
| `ITEM_GO_GOGGLES` — Go-Goggles | Nifty goggles that protect eyes from desert sandstorms. | Sim | Script (dado ao jogador): data/maps/LavaridgeTown/scripts.inc:62, data/maps/LavaridgeTown/scripts.inc:70 |
| `ITEM_GRACIDEA` — Gracidea | Bouquets made with it are offered as a token of gratitude. | Sim | Script (dado ao jogador): …/maps/GoldenrodCity_FlowerShop/scripts.inc:1631, …/maps/GoldenrodCity_FlowerShop/scripts.pory:841 |
| ★ `ITEM_GROOMING_KIT` — Grooming Kit | A set of brushes and tools for grooming Pokémon. | Sim | Script (dado ao jogador): …GoldenrodCity_UndergroundTunnel/scripts.inc:340, …oldenrodCity_UndergroundTunnel/scripts.pory:170 |
| ★ `ITEM_GS_BALL` — GS Ball | A strange ball with ornaments. | Sim | Item ball no mapa (object_event): RuinsOfAlph_SecretRoom \| Script (dado ao jogador): data/maps/AzaleaTown/scripts.inc:500, data/maps/AzaleaTown/scripts.pory:250 |
| `ITEM_JADE_ORB` — Jade Orb | A Green, glowing orb said to contain an ancient power. | Sim | Script (dado ao jogador): data/maps/Kitakami_Houses/scripts.inc:158, data/maps/Kitakami_Houses/scripts.pory:91 |
| `ITEM_KEY_TO_ROOM_1` — Key to Room 1 | A key that opens a door inside the Abandoned Ship. | Não (só em mapa fora da campanha) | Mencionado em script (verificar): …andonedShip_HiddenFloorCorridors/scripts.inc:56 |
| `ITEM_KEY_TO_ROOM_2` — Key to Room 2 | A key that opens a door inside the Abandoned Ship. | Não (só em mapa fora da campanha) | Mencionado em script (verificar): …andonedShip_HiddenFloorCorridors/scripts.inc:70 |
| `ITEM_KEY_TO_ROOM_4` — Key to Room 4 | A key that opens a door inside the Abandoned Ship. | Não (só em mapa fora da campanha) | Mencionado em script (verificar): …andonedShip_HiddenFloorCorridors/scripts.inc:84 |
| `ITEM_KEY_TO_ROOM_6` — Key to Room 6 | A key that opens a door inside the Abandoned Ship. | Não (só em mapa fora da campanha) | Mencionado em script (verificar): …andonedShip_HiddenFloorCorridors/scripts.inc:98 |
| `ITEM_LETTER` — Letter | A letter to Steven from the President of the Devon Corp. | Não (só em mapa fora da campanha) | Mencionado em script (verificar): data/maps/GraniteCave_StevensRoom/scripts.inc:8 \| Script (dado ao jogador): …a/maps/RustboroCity_DevonCorp_3F/scripts.inc:50 |
| `ITEM_LIFT_KEY` — Lift Key | An elevator key used in Team Rocket's Hideout. | Não | - |
| `ITEM_LOST_ITEM` — Lost Item | The POKéDOLL lost by the copycat. | Sim | Script (dado ao jogador): data/maps/VermilionCity_FanClub/scripts.inc:59 |
| `ITEM_MACHINE_PART` — Machine Part | Important machine part stolen from the POWER PLANT. | Sim | Script (finditem): data/maps/CeruleanCity_Gym/scripts.inc:69 |
| `ITEM_MACH_BIKE` — Mach Bike | A folding bicycle that doubles your speed or better. | Sim | Script (dado ao jogador): data/maps/GoldenrodCity_BikeShop/scripts.inc:36, data/maps/GoldenrodCity_BikeShop/scripts.pory:18 |
| `ITEM_MAGMA_EMBLEM` — Magma Emblem | A medal-like item in the same shape as Team Magma's mark. | Não (só em mapa fora da campanha) | Mencionado em script (verificar): data/maps/JaggedPass/scripts.inc:13 \| Script (dado ao jogador): data/maps/MtPyre_Summit/scripts.inc:60 |
| `ITEM_MEGA_RING` — Mega Ring | Enables {PKMN} holding their Mega Stone to Mega Evolve. | Sim | Script (dado ao jogador): …aps/GoldenrodCity_RadioTower_5F/scripts.inc:834, …aps/GoldenrodCity_RadioTower_5F/scripts.inc:969, …ps/GoldenrodCity_RadioTower_5F/scripts.pory:419 (+1) |
| `ITEM_METEORITE` — Meteorite | A meteorite found at Meteor Falls. | Não (só em mapa fora da campanha) | Mencionado em script (verificar): …a/maps/FallarborTown_CozmosHouse/scripts.inc:20, …ta/maps/FallarborTown_CozmosHouse/scripts.inc:8 \| Script (dado ao jogador): data/maps/MtChimney/scripts.inc:410 |
| `ITEM_MYSTERY_EGG` — Mystery Egg | Obtained from Mr. Pokémon. Who knows what's inside? | Sim | Script (dado ao jogador): …a/maps/Route30_MrPokemonsHouse/scripts.pory:154, …ta/maps/Route30_MrPokemonsHouse/scripts.inc:308 |
| `ITEM_MYSTIC_TICKET` — Mystic Ticket | A ticket required to board the ship to Navel Rock. | Sim | Loja / pokemart: …ipts.inc (BattleFrontier_ExchangeServiceCorner) \| Script (dado ao jogador): data/scripts/gift_mystic_ticket.inc:15 |
| `ITEM_N_LUNARIZER` — N-Lunarizer | A device to fuse and split Necrozma using a Lunala. | Não | - |
| `ITEM_N_SOLARIZER` — N-Solarizer | A device to fuse and split Necrozma using a Solgaleo. | Não | - |
| `ITEM_OLD_ROD` — Old Rod | Use by any body of water to fish for wild Pokémon. | Sim | Script (dado ao jogador): data/maps/Route32_PokemonCenter/scripts.inc:32 |
| `ITEM_OLD_SEA_MAP` — Old Sea Map | A faded sea chart that shows the way to a certain island. | Sim | Item ball no mapa (object_event): VermilionCity \| Loja / pokemart: …ipts.inc (BattleFrontier_ExchangeServiceCorner) \| Script (dado ao jogador): data/scripts/gift_old_sea_map.inc:14 |
| `ITEM_OVAL_CHARM` — Oval Charm | Raises the chance of finding eggs at the daycare. | Sim | Script (dado ao jogador): data/maps/NewBarkTown_House3/scripts.inc:231, data/maps/NewBarkTown_House3/scripts.pory:199 |
| `ITEM_PARCEL` — Parcel | A parcel for Prof. Oak from a Pokémon Mart's clerk. | Não | - |
| `ITEM_PASS` — Pass | A ticket for riding the Magnet Train. | Sim | Script (dado ao jogador): …ps/SaffronCity_CopyCatsHouse_2F/scripts.inc:154 |
| `ITEM_POKEBLOCK_CASE` — {POKEBLOCK} Case | A case for holding {POKEBLOCK}s made with a Berry Blender. | Sim | Script (dado ao jogador): data/scripts/contest_hall.inc:17, …afariZoneGate_SafariZoneEntrance/scripts.inc:49, …s/FuchsiaCity_SafariZoneEntrance/scripts.inc:68 |
| `ITEM_POKEMON_BOX_LINK` — {PKMN} Box Link | This device grants access to the {PKMN} Storage System. | Não | - |
| `ITEM_POKE_FLUTE` — Poké Flute | A sweet-sounding flute that awakens Pokémon. | Não | - |
| `ITEM_POKE_RADAR` — Poké Radar | A tool used to search out Pokémon hiding in grass. | Não | - |
| `ITEM_POWDER_JAR` — Powder Jar | Stores Berry Powder made using a Berry Crusher. | Verificar (só mencionado em script) | Mencionado em script (verificar): data/scripts/cable_club.inc:970 |
| `ITEM_PRISON_BOTTLE` — Prison Bottle | A bottle used to seal a certain Pokémon long ago. | Sim | Script (finditem): …a/maps/VajraPyramidFinalChamber/scripts.pory:19, …ta/maps/VajraPyramidFinalChamber/scripts.inc:46 |
| `ITEM_RADIO` — Radio | A legacy receiver. The Radio Tower will exchange it. | Verificar (só mencionado em script) | Mencionado em script (verificar): …aps/GoldenrodCity_RadioTower_1F/scripts.inc:136, …aps/GoldenrodCity_RadioTower_1F/scripts.pory:68 |
| `ITEM_RAINBOW_PASS` — Rainbow Pass | For ferries serving Vermilion and the Sevii Islands. | Não | - |
| `ITEM_RAINBOW_WING` — Rainbow Wing | A mystical rainbow feather that sparkles. | Sim | Script (dado ao jogador): data/maps/PewterCity/scripts.inc:34, …ps/GoldenrodCity_RadioTower_5F/scripts.inc:1004, …ps/GoldenrodCity_RadioTower_5F/scripts.inc:1075 (+2) |
| `ITEM_RED_SCALE` — Red Scale | A scale from the red Gyarados. It glows red. | Sim | Script (dado ao jogador): data/maps/LakeOfRage/scripts.inc:224, data/maps/LakeOfRage/scripts.pory:112 |
| `ITEM_REINS_OF_UNITY` — Reins of Unity | Reins that unite Calyrex with its beloved steed. | Não | - |
| `ITEM_REVEAL_GLASS` — Reveal Glass | This glass returns a Pokémon back to its original form. | Sim | Script (dado ao jogador): data/maps/BattleCafe/scripts.inc:1663, data/maps/BattleCafe/scripts.pory:902 |
| `ITEM_ROTOM_CATALOG` — Rotom Catalog | A catalog full of devices liked by Rotom. | Não | - |
| `ITEM_RUBY` — Ruby | An exquisite, red- glowing gem that symbolizes passion. | Não | - |
| `ITEM_SAPPHIRE` — Sapphire | A brilliant blue gem that symbolizes honesty. | Não | - |
| `ITEM_SCANNER` — Scanner | A device found inside the Abandoned Ship. | Não (só em mapa fora da campanha) | Item ball no mapa (object_event): AbandonedShip_HiddenFloorRooms \| Mencionado em script (verificar): data/maps/SlateportCity_Harbor/scripts.inc:317, …maps/AbandonedShip_CaptainsOffice/scripts.inc:8 |
| `ITEM_SCROLL_OF_DARKNESS` — Darkness Scroll | A peculiar scroll with secrets of the dark path. | Sim | Loja / pokemart: …Lobby/scripts.pory (GoldenrodBattleAracdeLobby), …eLobby/scripts.inc (GoldenrodBattleAracdeLobby) |
| `ITEM_SCROLL_OF_WATERS` — Water Scroll | A peculiar scroll with secrets of the water path. | Sim | Loja / pokemart: …Lobby/scripts.pory (GoldenrodBattleAracdeLobby), …eLobby/scripts.inc (GoldenrodBattleAracdeLobby) |
| ★ `ITEM_SEASONAL_PERFUME` — Seasonal Perfume | A perfume with scents inspired by the seasons. | Sim | Script (dado ao jogador): …a/maps/GoldenrodCity_FlowerShop/scripts.inc:132, …a/maps/GoldenrodCity_FlowerShop/scripts.pory:66 |
| `ITEM_SECRET_KEY` — Secret Key | The key to the Cinnabar Island Gym's entrance. | Não | - |
| `ITEM_SECRET_POTION` — Secret Potion | A fantastic medicine from the Cianwood pharmacy. | Sim | Script (dado ao jogador): data/maps/CianwoodShop/scripts.inc:14, data/maps/CianwoodShop/scripts.inc:34, data/maps/CianwoodShop/scripts.pory:17 (+1) |
| `ITEM_SHINY_CHARM` — Shiny Charm | A charm that will raise the chance of Shiny Pokémon. | Não | - |
| `ITEM_SILPH_SCOPE` — Silph Scope | Silph Co's scope makes unseeable POKéMON visible. | Não | - |
| `ITEM_SILVER_WING` — Silver Wing | A strange silvery feather that sparkles. | Sim | Script (dado ao jogador): data/maps/PewterCity/scripts.inc:45, …ps/GoldenrodCity_RadioTower_5F/scripts.inc:1015, …ps/GoldenrodCity_RadioTower_5F/scripts.inc:1054 (+2) |
| `ITEM_SOOT_SACK` — Soot Sack | A sack used to gather and hold volcanic ash. | Não (só em mapa fora da campanha) | Mencionado em script (verificar): data/maps/Route113_GlassWorkshop/scripts.inc:43 \| Script (dado ao jogador): data/maps/Route113_GlassWorkshop/scripts.inc:30 |
| `ITEM_SQUIRTBOTTLE` — Squirtbottle | A tool used for watering Berries and plants. | Sim | Script (dado ao jogador): …/maps/GoldenrodCity_FlowerShop/scripts.pory:427, …a/maps/GoldenrodCity_FlowerShop/scripts.inc:854 |
| `ITEM_SS_TICKET` — S.S. Ticket | The ticket required for sailing on a ferry. | Sim | Script (dado ao jogador): data/maps/NewBarkTown_Lab/scripts.inc:1102, data/maps/NewBarkTown_Lab/scripts.pory:551, data/scripts/players_house.inc:469 |
| `ITEM_STORAGE_KEY` — Storage Key | The key to the storage inside the Abandoned Ship. | Não (só em mapa fora da campanha) | Item ball no mapa (object_event): AbandonedShip_CaptainsOffice \| Mencionado em script (verificar): …maps/AbandonedShip_Corridors_B1F/scripts.inc:30 |
| ★ `ITEM_SUN_MOON_TICKET` — Sun&Moon Ticket | A ferry ticket from Olivine to the Sun and Moon Altar. | Sim | Script (dado ao jogador): data/maps/OlivineCity_House1/scripts.inc:994, data/maps/OlivineCity_House1/scripts.pory:497, data/maps/OlivineCity_PortInside/scripts.inc:367 (+1) |
| `ITEM_SUPER_ROD` — Super Rod | The best fishing rod for catching wild Pokémon. | Sim | Script (dado ao jogador): data/maps/BlackthornCity/scripts.inc:216 |
| `ITEM_TEA` — Tea | A thirst-quenching tea prepared by an old lady. | Não | - |
| `ITEM_TEACHY_TV` — Teachy TV | A TV set tuned to an advice program for Trainers. | Não | - |
| `ITEM_TERA_ORB` — Tera Orb | Energy charges can be used to cause Terastallization. | Não | - |
| `ITEM_TIDAL_BELL` — Tidal Bell | Old-fashioned bell with a gentle, soothing sound. | Sim | Script (dado ao jogador): data/maps/EcruteakCity_Theater/scripts.inc:849 |
| `ITEM_TM_CASE` — TM Case | A convenient case that holds TMs and HMs. | Não | - |
| `ITEM_TOWN_MAP` — Town Map | Can be viewed anytime. Shows your present location. | Não | - |
| `ITEM_TRI_PASS` — Tri-Pass | A pass for ferries between One, Two, and Three Island. | Não | - |
| `ITEM_VS_SEEKER` — Vs. Seeker | A rechargeable unit that resets the route Trainers. | Sim | Script (dado ao jogador): …aps/GoldenrodCity_RadioTower_1F/scripts.inc:162, …aps/GoldenrodCity_RadioTower_1F/scripts.inc:318, …aps/GoldenrodCity_RadioTower_1F/scripts.pory:81 (+1) |
| `ITEM_ZYGARDE_CUBE` — Zygarde Cube | An item to store Zygarde Cores and Cells. | Não | - |
| `ITEM_Z_POWER_RING` — Z-Power Ring | A strange ring that enables Z-Move usage. | Não | - |

## Itens órfãos (candidatos)

Agrupados por pocket. **Sem fonte** = nenhuma fonte reconhecida foi achada em lugar nenhum. **Só mencionado** = o item aparece num script (`checkitem`, comparação, `bufferitemname`...) mas nenhum comando de entrega foi achado numa fonte de campanha — pode ser um giveitem que o regex não reconheceu, ou pode ser dado só num mapa fora da campanha (ver limitações no cabeçalho do script). **Fora da campanha** = só existe um giveitem/loja num mapa de Hoenn/Emerald que não faz parte da campanha Johto/Kanto. Isto é uma lista para o autor decidir o que fazer com cada um — nada foi alterado.

### Itens (93)

> Inclui os 13 `ITEM_*_APRICORN` coloridos — CONFIRMADO em `.claude/KURT_BALL_CRAFT_DESIGN.md` seção 1.5 que são um corte conhecido ("apricorn não é obtenível no jogo", `APRICORN_TREE_COUNT` é 0): não é achado do script, é órfão documentado à espera da Fase 2. O resto é majoritariamente Sweet (Milcery), fóssil/Relic Gen4-9, Mulch Gen4 (diferente do Mulch Gen8 que a Flower Shop já vende) e Tera Shard (mecânica de Terastallize) — prováveis mecânicas Gen6-9 não ativadas nesta campanha.

- `ITEM_AMAZE_MULCH` [sem fonte] — A fertilizer Rich Surprising and Boosting as well.
- `ITEM_ARMORITE_ORE` [sem fonte] — A rare ore. Can be found in the Isle of Armor at Galar.
- `ITEM_ARMOR_FOSSIL` [sem fonte] — A piece of a prehistoric Poké- mon's head.
- `ITEM_AUX_EVASION` [sem fonte] — Sharply raises evasiveness during one battle. Raises evasiveness during one battle.
- `ITEM_AUX_GUARD` [sem fonte] — Sharply raises defenses during one battle. Raises defenses during one battle.
- `ITEM_AUX_POWER` [sem fonte] — Sharply raises offenses during one battle. Raises offenses during one battle.
- `ITEM_AUX_POWERGUARD` [sem fonte] — Sharply raises offense & defense during one battle. Raises offense and defense during one battle.
- `ITEM_BERRY_SWEET` [sem fonte] — A berry-shaped sweet loved by Milcery.
- `ITEM_BIG_BAMBOO_SHOOT` [sem fonte] — A large and rare bamboo shoot. Best sold to gourmands.
- `ITEM_BLACK_APRICORN` [sem fonte] — A black apricorn. It has an inde- scribable scent.
- `ITEM_BLUE_APRICORN` [sem fonte] — A blue apricorn. It smells a bit like grass.
- `ITEM_BOOST_MULCH` [sem fonte] — A fertilizer that ups the dry speed of soft soil.
- `ITEM_BUG_TERA_SHARD` [sem fonte] — These shards may form when a Tera Pokémon faints.
- `ITEM_CHOICE_DUMPLING` [sem fonte] — ?????
- `ITEM_CLOVER_SWEET` [sem fonte] — A clover-shaped sweet loved by Milcery.
- `ITEM_COMET_SHARD` [sem fonte] — A comet's shard. It would sell for a high price.
- `ITEM_DARK_TERA_SHARD` [sem fonte] — These shards may form when a Tera Pokémon faints.
- `ITEM_DRAGON_TERA_SHARD` [sem fonte] — These shards may form when a Tera Pokémon faints.
- `ITEM_DREAM_MAIL` [sem fonte] — Mail featuring a sketch of the holding Pokémon.
- `ITEM_DYNAMAX_CANDY` [sem fonte] — Raises the Dynamax Level of a single Pokémon by one.
- `ITEM_DYNITE_ORE` [sem fonte] — A mysterious ore. It can be found in Galar's Max Lair.
- `ITEM_ELECTRIC_TERA_SHARD` [sem fonte] — These shards may form when a Tera Pokémon faints.
- `ITEM_EXP_CANDY_S` [sem fonte] — Gives a small amount of Exp. to a single Pokémon.
- `ITEM_EXP_CANDY_XS` [sem fonte] — Gives a very small amount of Exp. to a single Pokémon.
- `ITEM_FAB_MAIL` [sem fonte] — A gorgeous-print Mail to be held by a Pokémon.
- `ITEM_FAIRY_TERA_SHARD` [sem fonte] — These shards may form when a Tera Pokémon faints.
- `ITEM_FIGHTING_TERA_SHARD` [sem fonte] — These shards may form when a Tera Pokémon faints.
- `ITEM_FIRE_TERA_SHARD` [sem fonte] — These shards may form when a Tera Pokémon faints.
- `ITEM_FLOWER_SWEET` [sem fonte] — A flower-shaped sweet loved by Milcery.
- `ITEM_FLYING_TERA_SHARD` [sem fonte] — These shards may form when a Tera Pokémon faints.
- `ITEM_FOSSILIZED_BIRD` [sem fonte] — A fossil of an ancient, sky- soaring Pokémon.
- `ITEM_FOSSILIZED_DINO` [sem fonte] — A fossil of an ancient, sea- dwelling Pokémon.
- `ITEM_FOSSILIZED_DRAKE` [sem fonte] — A fossil of an ancient, land- roaming Pokémon.
- `ITEM_FOSSILIZED_FISH` [sem fonte] — A fossil of an ancient, sea- dwelling Pokémon.
- `ITEM_FRESH_START_MOCHI` [sem fonte] — An item that resets all base points of a Pokémon.
- `ITEM_GALARICA_TWIG` [sem fonte] — A twig from a tree in Galar called Galarica.
- `ITEM_GHOST_TERA_SHARD` [sem fonte] — These shards may form when a Tera Pokémon faints.
- `ITEM_GIMMIGHOUL_COIN` [sem fonte] — Gimmighoul hoard and treasure these curious coins.
- `ITEM_GRASS_TERA_SHARD` [sem fonte] — These shards may form when a Tera Pokémon faints.
- `ITEM_GREEN_APRICORN` [sem fonte] — A green apricorn. It has a strange, aromatic scent.
- `ITEM_GROUND_TERA_SHARD` [sem fonte] — These shards may form when a Tera Pokémon faints.
- `ITEM_ICE_TERA_SHARD` [sem fonte] — These shards may form when a Tera Pokémon faints.
- `ITEM_LOVE_SWEET` [sem fonte] — A heart-shaped sweet loved by Milcery.
- `ITEM_MAX_LURE` [sem fonte] — Makes Pokémon more likely to appear for 250 steps.
- `ITEM_MAX_MUSHROOMS` [sem fonte] — Raises every stat during one battle by one stage.
- `ITEM_MEOWSCARADITE` [sem fonte] — Lets Meowscarada Mega Evolve in battle.
- `ITEM_NORMAL_TERA_SHARD` [sem fonte] — These shards may form when a Tera Pokémon faints.
- `ITEM_ODD_KEYSTONE` [sem fonte] — Voices can be heard from this odd stone occasionally.
- `ITEM_PEARL_STRING` [sem fonte] — Very large pearls that would sell at a high price.
- `ITEM_PINK_APRICORN` [sem fonte] — A pink apricorn. It has a nice, sweet scent.
- `ITEM_POISON_TERA_SHARD` [sem fonte] — These shards may form when a Tera Pokémon faints.
- `ITEM_POKESHI_DOLL` [sem fonte] — A wooden toy resembling a Poké- mon. Can be sold.
- `ITEM_POKE_TOY` [sem fonte] — Use to flee from any battle with a wild Pokémon.
- `ITEM_PRIMARINITE` [sem fonte] — This stone enables Primarina to Mega Evolve in battle.
- `ITEM_PSYCHIC_TERA_SHARD` [sem fonte] — These shards may form when a Tera Pokémon faints.
- `ITEM_RED_APRICORN` [sem fonte] — A red apricorn. It assails your nostrils.
- `ITEM_RELIC_BAND` [sem fonte] — An old bracelet. It sells at a high price.
- `ITEM_RELIC_COPPER` [sem fonte] — A copper coin used long ago. It sells at a high price.
- `ITEM_RELIC_CROWN` [sem fonte] — An old crown. It sells at a high price.
- `ITEM_RELIC_SILVER` [sem fonte] — A silver coin used long ago. It sells at a high price.
- `ITEM_RELIC_STATUE` [sem fonte] — An old statue. It sells at a high price.
- `ITEM_RELIC_VASE` [sem fonte] — A vase made long ago. It sells at a high price.
- `ITEM_RIBBON_SWEET` [sem fonte] — A ribbon-shaped sweet loved by Milcery.
- `ITEM_RICH_MULCH` [sem fonte] — A fertilizer that ups the number of Berries harvested.
- `ITEM_ROCK_TERA_SHARD` [sem fonte] — These shards may form when a Tera Pokémon faints.
- `ITEM_RUSTED_SWORD` [sem fonte] — A rusty sword. A hero used it to halt a disaster.
- `ITEM_SKULL_FOSSIL` [sem fonte] — A piece of a prehistoric Poké- mon's collar.
- `ITEM_STAR_SWEET` [sem fonte] — A star-shaped sweet loved by Milcery.
- `ITEM_STEEL_TERA_SHARD` [sem fonte] — These shards may form when a Tera Pokémon faints.
- `ITEM_STELLAR_TERA_SHARD` [sem fonte] — These shards may form when a Tera Pokémon faints.
- `ITEM_STRAWBERRY_SWEET` [sem fonte] — Strawberry-shaped sweet loved by Milcery.
- `ITEM_SUPER_LURE` [sem fonte] — Makes Pokémon more likely to appear for 200 steps.
- `ITEM_SURPRISE_MULCH` [sem fonte] — A fertilizer that ups the chance of Berry mutations.
- `ITEM_SWAP_SNACK` [sem fonte] — ?????
- `ITEM_TINY_BAMBOO_SHOOT` [sem fonte] — A small and rare bamboo shoot. Best sold to gourmands.
- `ITEM_TWICE_SPICED_RADISH` [sem fonte] — ?????
- `ITEM_TYPHLOSIONITE` [sem fonte] — This stone enables Typhlosion to Mega Evolve in battle.
- `ITEM_UNUSED_887` [sem fonte] — ?????
- `ITEM_WATER_TERA_SHARD` [sem fonte] — These shards may form when a Tera Pokémon faints.
- `ITEM_WHITE_APRICORN` [sem fonte] — A white apricorn. It doesn't smell like anything.
- `ITEM_WISHING_PIECE` [sem fonte] — Throw into a {PKMN} Den to attract Dynamax Pokémon.
- `ITEM_X_SP_DEF` [sem fonte] — Sharply raises stat Sp. Def during one battle. Raises the stat Sp. Def during one battle.
- `ITEM_YELLOW_APRICORN` [sem fonte] — A yellow apricorn. It has an invigor- ating scent.
- `ITEM_HELIX_FOSSIL` [só mencionado] — A piece of an ancient marine Pokémon's seashell.
- `ITEM_LURE` [só mencionado] — Makes Pokémon more likely to appear for 100 steps.
- `ITEM_BLACK_FLUTE` [fora da campanha] — A glass flute that keeps away wild Pokémon.
- `ITEM_BLUE_SCARF` [fora da campanha] — A hold item that raises Beauty in Contests.
- `ITEM_GREEN_SCARF` [fora da campanha] — A hold item that raises Smart in Contests.
- `ITEM_PINK_SCARF` [fora da campanha] — A hold item that raises Cute in Contests.
- `ITEM_RED_SCARF` [fora da campanha] — A hold item that raises Cool in Contests.
- `ITEM_SHOAL_SALT` [fora da campanha] — Salt obtained from deep inside the Shoal Cave.
- `ITEM_SHOAL_SHELL` [fora da campanha] — A seashell found deep inside the Shoal Cave.
- `ITEM_YELLOW_SCARF` [fora da campanha] — A hold item that raises Tough in Contests.

### Remédios (Medicine) (13)

- `ITEM_CLEVER_MOCHI` [sem fonte] — An item that raises the base Sp. Def. of a Pokémon.
- `ITEM_FINE_REMEDY` [sem fonte] — A bitter powder that restores HP by 60 points. by 50 points.
- `ITEM_GENIUS_MOCHI` [sem fonte] — An item that raises the base Sp. Atk. of a Pokémon.
- `ITEM_HEALTH_MOCHI` [sem fonte] — An item that raises the base HP of a Pokémon.
- `ITEM_JUBILIFE_MUFFIN` [sem fonte] — Heals all the status problems of one Pokémon.
- `ITEM_MAX_HONEY` [sem fonte] — Revives a fainted Pokémon with all its HP.
- `ITEM_MUSCLE_MOCHI` [sem fonte] — An item that raises the base Attack of a Pokémon.
- `ITEM_REMEDY` [sem fonte] — A bitter powder that restores HP by 20 points.
- `ITEM_RESIST_MOCHI` [sem fonte] — An item that raises the base Defense of a Pokémon.
- `ITEM_SUPERB_REMEDY` [sem fonte] — A bitter powder that restores HP by 120 points. by 200 points.
- `ITEM_SWIFT_MOCHI` [sem fonte] — An item that raises the base Speed of a Pokémon.
- `ITEM_BLUE_FLUTE` [fora da campanha] — A glass flute that awakens sleeping Pokémon.
- `ITEM_YELLOW_FLUTE` [fora da campanha] — A glass flute that snaps Pokémon out of confusion.

### Itens de batalha / held items (77)

> Boa parte é Plate (Arceus), Drive (Genesect), Memory (Silvally) e Z-Crystal (golpes Z de Alola) — mecânicas de gerações/jogos específicos que este romhack de Johto/Kanto provavelmente nunca pretendeu ativar. Vale conferir se alguma delas é usada por algum Pokémon relevante da campanha antes de descartar a lista inteira.

- `ITEM_ADAMANT_CRYSTAL` [sem fonte] — A large, glowing gem that lets Dialga change form.
- `ITEM_ALORAICHIUM_Z` [sem fonte] — Upgrade Alolan Raichu's Thunder- bolt into a Z-Move.
- `ITEM_BUGINIUM_Z` [sem fonte] — Upgrade Bug- type moves into Z-Moves.
- `ITEM_BUG_MEMORY` [sem fonte] — A disc with Bug type data. It swaps Silvally's type.
- `ITEM_BURN_DRIVE` [sem fonte] — Changes Genesect's Techno Blast to Fire-type.
- `ITEM_CHILL_DRIVE` [sem fonte] — Changes Genesect's Techno Blast to Ice-type.
- `ITEM_DARKINIUM_Z` [sem fonte] — Upgrade Dark- type moves into Z-Moves.
- `ITEM_DARK_MEMORY` [sem fonte] — A disc with Dark type data. It swaps Silvally's type.
- `ITEM_DECIDIUM_Z` [sem fonte] — Upgrade Decidu- eye's Spirit Sha- ckle into a Z-Move.
- `ITEM_DOUSE_DRIVE` [sem fonte] — Changes Genesect's Techno Blast to Water-type.
- `ITEM_DRACO_PLATE` [sem fonte] — A tablet that ups the power of Dragon-type moves.
- `ITEM_DRAGONIUM_Z` [sem fonte] — Upgrade Dragon- type moves into Z-Moves.
- `ITEM_DRAGON_MEMORY` [sem fonte] — A disc with Dragon type data. It swaps Silvally's type.
- `ITEM_DREAD_PLATE` [sem fonte] — A tablet that ups the power of Dark-type moves.
- `ITEM_EARTH_PLATE` [sem fonte] — A tablet that ups the power of Ground-type moves.
- `ITEM_EEVIUM_Z` [sem fonte] — Upgrade Eevee's Last Resort into a Z-Move.
- `ITEM_ELECTRIC_MEMORY` [sem fonte] — A disc with Electric type data. It swaps Silvally's type.
- `ITEM_ELECTRIUM_Z` [sem fonte] — Upgrade Electric- type moves into Z-Moves.
- `ITEM_FAIRIUM_Z` [sem fonte] — Upgrade Fairy- type moves into Z-Moves.
- `ITEM_FAIRY_MEMORY` [sem fonte] — A disc with Fairy type data. It swaps Silvally's type.
- `ITEM_FIGHTING_MEMORY` [sem fonte] — Disc with Fighting type data. It swaps Silvally's type.
- `ITEM_FIGHTINIUM_Z` [sem fonte] — Upgrade Fighting- type moves into Z-Moves.
- `ITEM_FIRE_MEMORY` [sem fonte] — A disc with Fire type data. It swaps Silvally's type.
- `ITEM_FIRIUM_Z` [sem fonte] — Upgrade Fire- type moves into Z-Moves.
- `ITEM_FIST_PLATE` [sem fonte] — A tablet that ups the power of Fight- ing-type moves.
- `ITEM_FLAME_PLATE` [sem fonte] — A tablet that ups the power of Fire-type moves.
- `ITEM_FLYING_MEMORY` [sem fonte] — A disc with Flying type data. It swaps Silvally's type.
- `ITEM_FLYINIUM_Z` [sem fonte] — Upgrade Flying- type moves into Z-Moves.
- `ITEM_GHOSTIUM_Z` [sem fonte] — Upgrade Ghost- type moves into Z-Moves.
- `ITEM_GHOST_MEMORY` [sem fonte] — A disc with Ghost type data. It swaps Silvally's type.
- `ITEM_GRASSIUM_Z` [sem fonte] — Upgrade Grass- type moves into Z-Moves.
- `ITEM_GRASS_MEMORY` [sem fonte] — A disc with Grass type data. It swaps Silvally's type.
- `ITEM_GRISEOUS_CORE` [sem fonte] — A large, glowing gem that lets Giratina change form.
- `ITEM_GROUNDIUM_Z` [sem fonte] — Upgrade Ground- type moves into Z-Moves.
- `ITEM_GROUND_MEMORY` [sem fonte] — A disc with Ground type data. It swaps Silvally's type.
- `ITEM_ICE_MEMORY` [sem fonte] — A disc with Ice type data. It swaps Silvally's type.
- `ITEM_ICICLE_PLATE` [sem fonte] — A tablet that ups the power of Ice-type moves.
- `ITEM_ICIUM_Z` [sem fonte] — Upgrade Ice- type moves into Z-Moves.
- `ITEM_INCINIUM_Z` [sem fonte] — Upgrade Incine- roar's Darkest La- riat into a Z-Move.
- `ITEM_INSECT_PLATE` [sem fonte] — A tablet that ups the power of Bug-type moves.
- `ITEM_IRON_PLATE` [sem fonte] — A tablet that ups the power of Steel-type moves.
- `ITEM_KOMMONIUM_Z` [sem fonte] — Upgrade Kommo-o's Clanging Scales into a Z-Move.
- `ITEM_LUNALIUM_Z` [sem fonte] — Upgrade Lunala's Moongeist Beam into a Z-Move.
- `ITEM_LUSTROUS_GLOBE` [sem fonte] — A large, glowing gem that lets Palkia change form.
- `ITEM_LYCANIUM_Z` [sem fonte] — Upgrade Lycanroc's Stone Edge into a Z-Move.
- `ITEM_MARSHADIUM_Z` [sem fonte] — Upgrade Marsha- dow's Spectral Thi- ef into a Z-Move.
- `ITEM_MEADOW_PLATE` [sem fonte] — A tablet that ups the power of Grass-type moves.
- `ITEM_MEWNIUM_Z` [sem fonte] — Upgrade Mew's Psychic into a Z-Move.
- `ITEM_MIMIKIUM_Z` [sem fonte] — Upgrade Mimikyu's Play Rough into a Z-Move.
- `ITEM_MIND_PLATE` [sem fonte] — A tablet that ups the power of Psy chic-type moves.
- `ITEM_NORMALIUM_Z` [sem fonte] — Upgrade Normal- type moves into Z-Moves.
- `ITEM_PIKANIUM_Z` [sem fonte] — Upgrade Pikachu's Volt Tackle into a Z-Move.
- `ITEM_PIKASHUNIUM_Z` [sem fonte] — Upgrade Pikachu w/ a cap's Thunderbolt into a Z-Move.
- `ITEM_PIXIE_PLATE` [sem fonte] — A tablet that ups the power of Fairy-type moves.
- `ITEM_POISONIUM_Z` [sem fonte] — Upgrade Poison- type moves into Z-Moves.
- `ITEM_POISON_MEMORY` [sem fonte] — A disc with Poison type data. It swaps Silvally's type.
- `ITEM_PRIMARIUM_Z` [sem fonte] — Upgrade Primarina's Sparkling Aria into a Z-Move.
- `ITEM_PSYCHIC_MEMORY` [sem fonte] — A disc with Psychic type data. It swaps Silvally's type.
- `ITEM_PSYCHIUM_Z` [sem fonte] — Upgrade Psychic- type moves into Z-Moves.
- `ITEM_RED_CARD` [sem fonte] — Switches out the foe if they hit the holder.
- `ITEM_ROCKIUM_Z` [sem fonte] — Upgrade Rock- type moves into Z-Moves.
- `ITEM_ROCK_MEMORY` [sem fonte] — A disc with Rock type data. It swaps Silvally's type.
- `ITEM_SHOCK_DRIVE` [sem fonte] — Changes Genesect's Techno Blast to Electric-type.
- `ITEM_SKY_PLATE` [sem fonte] — A tablet that ups the power of Flying-type moves.
- `ITEM_SNORLIUM_Z` [sem fonte] — Upgrade Snorlax's Giga Impact into a Z-Move.
- `ITEM_SOLGANIUM_Z` [sem fonte] — Upgrade Solgaleo's Sunsteel Strike into a Z-Move.
- `ITEM_SPLASH_PLATE` [sem fonte] — A tablet that ups the power of Water-type moves.
- `ITEM_SPOOKY_PLATE` [sem fonte] — A tablet that ups the power of Ghost-type moves.
- `ITEM_STEELIUM_Z` [sem fonte] — Upgrade Steel- type moves into Z-Moves.
- `ITEM_STEEL_MEMORY` [sem fonte] — A disc with Steel type data. It swaps Silvally's type.
- `ITEM_STONE_PLATE` [sem fonte] — A tablet that ups the power of Rock-type moves.
- `ITEM_TAPUNIUM_Z` [sem fonte] — Upgrade the tapus' Nature's Madness into a Z-Move.
- `ITEM_TOXIC_PLATE` [sem fonte] — A tablet that ups the power of Poison-type moves.
- `ITEM_ULTRANECROZIUM_Z` [sem fonte] — A crystal to turn fused Necrozma into a new form.
- `ITEM_WATERIUM_Z` [sem fonte] — Upgrade Water- type moves into Z-Moves.
- `ITEM_WATER_MEMORY` [sem fonte] — A disc with Water type data. It swaps Silvally's type.
- `ITEM_ZAP_PLATE` [sem fonte] — A tablet that ups the power of Elec- tric-type moves.

### Berries (1)

- `ITEM_ENIGMA_BERRY_E_READER` [fora da campanha] — {POKEBLOCK} ingredient. Plant in loamy soil to grow a mystery.

### Mega Stones (93)

> A maioria destas são as mega stones oficiais (uma por espécie, `gGengarite` etc.) da base pokeemerald-expansion. O SoulGold parece ter optado por um sistema próprio de mega evolução por TIPO (os 18 itens `ITEM_*TITE` genéricos em Poké Balls/Itens, tipo `ITEM_NORMALITE`/`ITEM_FIRETITE`, gerados pela macro `TYPE_MEGA_STONE` — esses SÃO vendidos em `AzaleaTown_Mart`). As mega stones de espécie individual abaixo não têm nenhum giveitem, loja ou item ball — parecem sobra da tabela vanilla, não conteúdo cortado por engano.

- `ITEM_ABOMASITE` [sem fonte] — This stone enables Abomasnow to Mega Evolve in battle.
- `ITEM_ABSOLITE` [sem fonte] — This stone enables Absol to Mega Evolve in battle.
- `ITEM_ABSOLITE_Z` [sem fonte] — This stone enables Absol to Mega Evolve in battle.
- `ITEM_AERODACTYLITE` [sem fonte] — This stone enables Aerodactyl to Mega Evolve in battle.
- `ITEM_AGGRONITE` [sem fonte] — This stone enables Aggron to Mega Evolve in battle.
- `ITEM_ALAKAZITE` [sem fonte] — This stone enables Alakazam to Mega Evolve in battle.
- `ITEM_ALTARIANITE` [sem fonte] — This stone enables Altaria to Mega Evolve in battle.
- `ITEM_AMPHAROSITE` [sem fonte] — This stone enables Ampharos to Mega Evolve in battle.
- `ITEM_AUDINITE` [sem fonte] — This stone enables Audino to Mega Evolve in battle.
- `ITEM_BANETTITE` [sem fonte] — This stone enables Banette to Mega Evolve in battle.
- `ITEM_BARBARACITE` [sem fonte] — This stone enables Barbaracle to Mega Evolve in battle.
- `ITEM_BAXCALIBRITE` [sem fonte] — This stone enables Baxcalibur to Mega Evolve in battle.
- `ITEM_BEEDRILLITE` [sem fonte] — This stone enables Beedrill to Mega Evolve in battle.
- `ITEM_BLASTOISINITE` [sem fonte] — This stone enables Blastoise to Mega Evolve in battle.
- `ITEM_BLAZIKENITE` [sem fonte] — This stone enables Blaziken to Mega Evolve in battle.
- `ITEM_CAMERUPTITE` [sem fonte] — This stone enables Camerupt to Mega Evolve in battle.
- `ITEM_CHANDELURITE` [sem fonte] — This stone enables Chandelure to Mega Evolve in battle.
- `ITEM_CHARIZARDITE_X` [sem fonte] — This stone enables Charizard to Mega Evolve in battle.
- `ITEM_CHARIZARDITE_Y` [sem fonte] — This stone enables Charizard to Mega Evolve in battle.
- `ITEM_CHESNAUGHTITE` [sem fonte] — This stone enables Chesnaught to Mega Evolve in battle.
- `ITEM_CHIMECHITE` [sem fonte] — This stone enables Chimecho to Mega Evolve in battle.
- `ITEM_CLEFABLITE` [sem fonte] — This stone enables Clefable to Mega Evolve in battle.
- `ITEM_CRABOMINITE` [sem fonte] — This stone enables Crabominable to Mega in battle.
- `ITEM_DARKRANITE` [sem fonte] — This stone enables Darkrai to Mega Evolve in battle.
- `ITEM_DELPHOXITE` [sem fonte] — This stone enables Delphox to Mega Evolve in battle.
- `ITEM_DIANCITE` [sem fonte] — This stone enables Diancie to Mega Evolve in battle.
- `ITEM_DRAGALGITE` [sem fonte] — This stone enables Dragalge to Mega Evolve in battle.
- `ITEM_DRAGONINITE` [sem fonte] — This stone enables Dragonite to Mega Evolve in battle.
- `ITEM_DRAMPANITE` [sem fonte] — This stone enables Drampa to Mega Evolve in battle.
- `ITEM_EELEKTROSSITE` [sem fonte] — This stone enables Eelektross to Mega Evolve in battle.
- `ITEM_EMBOARITE` [sem fonte] — This stone enables Emboar to Mega Evolve in battle.
- `ITEM_EXCADRITE` [sem fonte] — This stone enables Excadrill to Mega Evolve in battle.
- `ITEM_FALINKSITE` [sem fonte] — This stone enables Falinks to Mega Evolve in battle.
- `ITEM_FERALIGITE` [sem fonte] — This stone enables Feraligatr to Mega Evolve in battle.
- `ITEM_FLOETTITE` [sem fonte] — This stone enables Floette to Mega Evolve in battle.
- `ITEM_FROSLASSITE` [sem fonte] — This stone enables Froslass to Mega Evolve in battle.
- `ITEM_GALLADITE` [sem fonte] — This stone enables Gallade to Mega Evolve in battle.
- `ITEM_GARCHOMPITE` [sem fonte] — This stone enables Garchomp to Mega Evolve in battle.
- `ITEM_GARCHOMPITE_Z` [sem fonte] — This stone enables Garchomp to Mega Evolve in battle.
- `ITEM_GARDEVOIRITE` [sem fonte] — This stone enables Gardevoir to Mega Evolve in battle.
- `ITEM_GENGARITE` [sem fonte] — This stone enables Gengar to Mega Evolve in battle.
- ★ `ITEM_GIGANTATITE` [sem fonte] — A stone that lets former Gigantamax {PKMN} Mega Evolve.
- `ITEM_GLALITITE` [sem fonte] — This stone enables Glalie to Mega Evolve in battle.
- `ITEM_GLIMMORANITE` [sem fonte] — This stone enables Glimmora to Mega Evolve in battle.
- `ITEM_GOLISOPITE` [sem fonte] — This stone enables Golisopod to Mega Evolve in battle.
- `ITEM_GOLURKITE` [sem fonte] — This stone enables Golurk to Mega Evolve in battle.
- `ITEM_GRENINJITE` [sem fonte] — This stone enables Greninja to Mega Evolve in battle.
- `ITEM_GYARADOSITE` [sem fonte] — This stone enables Gyarados to Mega Evolve in battle.
- `ITEM_HAWLUCHANITE` [sem fonte] — This stone enables Hawlucha to Mega Evolve in battle.
- `ITEM_HEATRANITE` [sem fonte] — This stone enables Heatran to Mega Evolve in battle.
- `ITEM_HERACRONITE` [sem fonte] — This stone enables Heracross to Mega Evolve in battle.
- `ITEM_HOUNDOOMINITE` [sem fonte] — This stone enables Houndoom to Mega Evolve in battle.
- `ITEM_KANGASKHANITE` [sem fonte] — This stone enables Kangaskhan to Mega Evolve in battle.
- `ITEM_LATIASITE` [sem fonte] — This stone enables Latias to Mega Evolve in battle.
- `ITEM_LATIOSITE` [sem fonte] — This stone enables Latios to Mega Evolve in battle.
- `ITEM_LOPUNNITE` [sem fonte] — This stone enables Lopunny to Mega Evolve in battle.
- `ITEM_LUCARIONITE` [sem fonte] — This stone enables Lucario to Mega Evolve in battle.
- `ITEM_LUCARIONITE_Z` [sem fonte] — This stone enables Lucario to Mega Evolve in battle.
- `ITEM_MAGEARNITE` [sem fonte] — This stone enables Magearna to Mega Evolve in battle.
- `ITEM_MALAMARITE` [sem fonte] — This stone enables Malamar to Mega Evolve in battle.
- `ITEM_MANECTITE` [sem fonte] — This stone enables Manectric to Mega Evolve in battle.
- `ITEM_MAWILITE` [sem fonte] — This stone enables Mawile to Mega Evolve in battle.
- `ITEM_MEDICHAMITE` [sem fonte] — This stone enables Medicham to Mega Evolve in battle.
- `ITEM_MEGANIUMITE` [sem fonte] — This stone enables Meganium to Mega Evolve in battle.
- `ITEM_MEOWSTICITE` [sem fonte] — This stone enables Meowstic to Mega Evolve in battle.
- `ITEM_METAGROSSITE` [sem fonte] — This stone enables Metagross to Mega Evolve in battle.
- `ITEM_MEWTWONITE_X` [sem fonte] — This stone enables Mewtwo to Mega Evolve in battle.
- `ITEM_MEWTWONITE_Y` [sem fonte] — This stone enables Mewtwo to Mega Evolve in battle.
- `ITEM_PIDGEOTITE` [sem fonte] — This stone enables Pidgeot to Mega Evolve in battle.
- `ITEM_PINSIRITE` [sem fonte] — This stone enables Pinsir to Mega Evolve in battle.
- `ITEM_PYROARITE` [sem fonte] — This stone enables Pyroar to Mega Evolve in battle.
- `ITEM_RAICHUNITE_X` [sem fonte] — This stone enables Raichu to Mega Evolve in battle.
- `ITEM_RAICHUNITE_Y` [sem fonte] — This stone enables Raichu to Mega Evolve in battle.
- `ITEM_SABLENITE` [sem fonte] — This stone enables Sableye to Mega Evolve in battle.
- `ITEM_SALAMENCITE` [sem fonte] — This stone enables Salamence to Mega Evolve in battle.
- `ITEM_SCEPTILITE` [sem fonte] — This stone enables Sceptile to Mega Evolve in battle.
- `ITEM_SCIZORITE` [sem fonte] — This stone enables Scizor to Mega Evolve in battle.
- `ITEM_SCOLIPITE` [sem fonte] — This stone enables Scolipede to Mega Evolve in battle.
- `ITEM_SCOVILLAINITE` [sem fonte] — This stone enables Scovillain to Mega Evolve in battle.
- `ITEM_SCRAFTINITE` [sem fonte] — This stone enables Scrafty to Mega Evolve in battle.
- `ITEM_SHARPEDONITE` [sem fonte] — This stone enables Sharpedo to Mega Evolve in battle.
- `ITEM_SKARMORITE` [sem fonte] — This stone enables Skarmory to Mega Evolve in battle.
- `ITEM_SLOWBRONITE` [sem fonte] — This stone enables Slowbro to Mega Evolve in battle.
- `ITEM_STARAPTITE` [sem fonte] — This stone enables Staraptor to Mega Evolve in battle.
- `ITEM_STARMINITE` [sem fonte] — This stone enables Starmie to Mega Evolve in battle.
- `ITEM_STEELIXITE` [sem fonte] — This stone enables Steelix to Mega Evolve in battle.
- `ITEM_SWAMPERTITE` [sem fonte] — This stone enables Swampert to Mega Evolve in battle.
- `ITEM_TATSUGIRINITE` [sem fonte] — This stone enables Tatsugiri to Mega Evolve in battle.
- `ITEM_TYRANITARITE` [sem fonte] — This stone enables Tyranitar to Mega Evolve in battle.
- `ITEM_VENUSAURITE` [sem fonte] — This stone enables Venusaur to Mega Evolve in battle.
- `ITEM_VICTREEBELITE` [sem fonte] — This stone enables Victreebel to Mega Evolve in battle.
- `ITEM_ZERAORITE` [sem fonte] — This stone enables Zeraora to Mega Evolve in battle.
- `ITEM_ZYGARDITE` [sem fonte] — This stone enables Zygarde to Mega Evolve in battle.

### Key Items (45)

> Muitos são key items de Kanto (`ITEM_SILPH_SCOPE`, `ITEM_LIFT_KEY`, `ITEM_SECRET_KEY`, `ITEM_GOLD_TEETH`) — o mapa correspondente já se chama `AbandonedRocketHideout`, sugerindo que essa sub-questline foi conscientemente esvaziada nesta campanha, não esquecida. Vale conferir os key items de Sevii Islands/Orange Islands (`ITEM_TRI_PASS`, `ITEM_RAINBOW_PASS`, `ITEM_TEA`) e os de gimmick tardio (Z-Power Ring, Dynamax Band, Tera Orb) com mais atenção, pois indicam mecânica de geração later nunca ligada.

- `ITEM_BERRY_POUCH` [sem fonte] — A convenient container that holds Berries.
- `ITEM_BICYCLE` [sem fonte] — A folding bicycle that is faster than the Running Shoes.
- `ITEM_BIKE_VOUCHER` [sem fonte] — A voucher for obtaining a bicycle from the Bike Shop.
- `ITEM_DNA_SPLICERS` [sem fonte] — Splicer that fuses Kyurem and a certain Pokémon.
- `ITEM_DYNAMAX_BAND` [sem fonte] — A band carrying a Wishing Star that allows Dynamaxing.
- `ITEM_EXP_CHARM` [sem fonte] — A charm that raises the amount of Exp. earned in battle.
- `ITEM_FAME_CHECKER` [sem fonte] — Stores information on famous people for instant recall.
- `ITEM_GLIMMERING_CHARM` [sem fonte] — A charm that will raise the shards from Tera Raids.
- `ITEM_GOLD_TEETH` [sem fonte] — Gold dentures lost by the Safari Zone's Warden.
- `ITEM_LIFT_KEY` [sem fonte] — An elevator key used in Team Rocket's Hideout.
- `ITEM_N_LUNARIZER` [sem fonte] — A device to fuse and split Necrozma using a Lunala.
- `ITEM_N_SOLARIZER` [sem fonte] — A device to fuse and split Necrozma using a Solgaleo.
- `ITEM_PARCEL` [sem fonte] — A parcel for Prof. Oak from a Pokémon Mart's clerk.
- `ITEM_POKEMON_BOX_LINK` [sem fonte] — This device grants access to the {PKMN} Storage System.
- `ITEM_POKE_FLUTE` [sem fonte] — A sweet-sounding flute that awakens Pokémon.
- `ITEM_POKE_RADAR` [sem fonte] — A tool used to search out Pokémon hiding in grass.
- `ITEM_RAINBOW_PASS` [sem fonte] — For ferries serving Vermilion and the Sevii Islands.
- `ITEM_REINS_OF_UNITY` [sem fonte] — Reins that unite Calyrex with its beloved steed.
- `ITEM_ROTOM_CATALOG` [sem fonte] — A catalog full of devices liked by Rotom.
- `ITEM_RUBY` [sem fonte] — An exquisite, red- glowing gem that symbolizes passion.
- `ITEM_SAPPHIRE` [sem fonte] — A brilliant blue gem that symbolizes honesty.
- `ITEM_SECRET_KEY` [sem fonte] — The key to the Cinnabar Island Gym's entrance.
- `ITEM_SHINY_CHARM` [sem fonte] — A charm that will raise the chance of Shiny Pokémon.
- `ITEM_SILPH_SCOPE` [sem fonte] — Silph Co's scope makes unseeable POKéMON visible.
- `ITEM_TEA` [sem fonte] — A thirst-quenching tea prepared by an old lady.
- `ITEM_TEACHY_TV` [sem fonte] — A TV set tuned to an advice program for Trainers.
- `ITEM_TERA_ORB` [sem fonte] — Energy charges can be used to cause Terastallization.
- `ITEM_TM_CASE` [sem fonte] — A convenient case that holds TMs and HMs.
- `ITEM_TOWN_MAP` [sem fonte] — Can be viewed anytime. Shows your present location.
- `ITEM_TRI_PASS` [sem fonte] — A pass for ferries between One, Two, and Three Island.
- `ITEM_ZYGARDE_CUBE` [sem fonte] — An item to store Zygarde Cores and Cells.
- `ITEM_Z_POWER_RING` [sem fonte] — A strange ring that enables Z-Move usage.
- `ITEM_POWDER_JAR` [só mencionado] — Stores Berry Powder made using a Berry Crusher.
- `ITEM_RADIO` [só mencionado] — A legacy receiver. The Radio Tower will exchange it.
- `ITEM_DEVON_PARTS` [fora da campanha] — A package that contains Devon's machine parts.
- `ITEM_KEY_TO_ROOM_1` [fora da campanha] — A key that opens a door inside the Abandoned Ship.
- `ITEM_KEY_TO_ROOM_2` [fora da campanha] — A key that opens a door inside the Abandoned Ship.
- `ITEM_KEY_TO_ROOM_4` [fora da campanha] — A key that opens a door inside the Abandoned Ship.
- `ITEM_KEY_TO_ROOM_6` [fora da campanha] — A key that opens a door inside the Abandoned Ship.
- `ITEM_LETTER` [fora da campanha] — A letter to Steven from the President of the Devon Corp.
- `ITEM_MAGMA_EMBLEM` [fora da campanha] — A medal-like item in the same shape as Team Magma's mark.
- `ITEM_METEORITE` [fora da campanha] — A meteorite found at Meteor Falls.
- `ITEM_SCANNER` [fora da campanha] — A device found inside the Abandoned Ship.
- `ITEM_SOOT_SACK` [fora da campanha] — A sack used to gather and hold volcanic ash.
- `ITEM_STORAGE_KEY` [fora da campanha] — The key to the storage inside the Abandoned Ship.

