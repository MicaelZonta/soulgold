// Nexus legendary pool. CONTENT ONLY: the rules that use it are in src/nexus.c.
//
// One line per legendary that can be the boss of the day. A legendary only
// enters once it has a champion (.claude/rift_missions/nexus/POOL_LENDARIOS.md,
// "Campeao de cada lendario") and that champion is in src/data/nexus/trainers.h.
//
//   requiresCaught  R1: TRUE when the legendary can be obtained outside the
//                   Nexus; it is only drawn after the player caught it
//                   (Pokedex "caught"). Keep in sync with POOL_LENDARIOS.md.
//   boss            R6: bars / stat multiplier / phase profile of setbossbattle.
//   afterBossScript optional script run after the fragment is caught.
//   lookerFileScript R18: the Looker File notebook lying on the floor of the
//                   champion room on the days of this legendary - Looker's
//                   notes on the universe it comes from. NULL = no notebook.
//
// R7: no "already fought" or "already caught" filter. R17: the boss is never
// caught; beating it leaves a fragment - the first form of the species, level
// 1, with the boss's perfect IVs (R8) - caught with a ball from the Bag (a
// Beast Ball for an Ultra Beast).

#define NEXUS_BOSS_DEFAULT  .bossBars = 4, .bossStatMultiplier = 140, .bossPhaseProfile = BOSS_PHASE_PROFILE_NONE

#define NEXUS_LOOKER_FILE(Concept)  .lookerFileScript = Nexus_EventScript_##Concept##_LookerFile
#define NEXUS_LOOKER_FILE_EXTERN(Concept)  extern const u8 Nexus_EventScript_##Concept##_LookerFile[];

// A trainer with only one legendary keeps the plain <Name>_ChampionFight
// script; a trainer who champions more than one (NEXUS_REGRAS R16) gets one
// <Name>_<Legendary>_ChampionFight per legendary - never share one script
// between two legendaries just because the trainer is the same.
// Form items nothing else in the game hands out (.claude/evolucoes.md).
#define NEXUS_AFTER_BOSS(Concept)  .afterBossScript = Nexus_EventScript_##Concept##_AfterBoss
#define NEXUS_AFTER_BOSS_EXTERN(Concept)  extern const u8 Nexus_EventScript_##Concept##_AfterBoss[];

NEXUS_AFTER_BOSS_EXTERN(Kyurem)
NEXUS_AFTER_BOSS_EXTERN(Genesect)
NEXUS_AFTER_BOSS_EXTERN(Zygarde)
NEXUS_AFTER_BOSS_EXTERN(Calyrex)

#define NEXUS_CHAMPION(Name)  .championScript = Nexus_EventScript_##Name##_ChampionFight
#define NEXUS_CHAMPION_EXTERN(Name)  extern const u8 Nexus_EventScript_##Name##_ChampionFight[];

NEXUS_LOOKER_FILE_EXTERN(Symbiont)
NEXUS_LOOKER_FILE_EXTERN(Absorption)
NEXUS_LOOKER_FILE_EXTERN(Beauty)
NEXUS_LOOKER_FILE_EXTERN(Lighting)
NEXUS_LOOKER_FILE_EXTERN(Blaster)
NEXUS_LOOKER_FILE_EXTERN(Blade)
NEXUS_LOOKER_FILE_EXTERN(Glutton)
NEXUS_LOOKER_FILE_EXTERN(Stinger)
NEXUS_LOOKER_FILE_EXTERN(Assembly)
NEXUS_LOOKER_FILE_EXTERN(Burst)
NEXUS_LOOKER_FILE_EXTERN(Arceus)
NEXUS_LOOKER_FILE_EXTERN(Articuno)
NEXUS_LOOKER_FILE_EXTERN(Azelf)
NEXUS_LOOKER_FILE_EXTERN(BruteBonnet)
NEXUS_LOOKER_FILE_EXTERN(Calyrex)
NEXUS_LOOKER_FILE_EXTERN(Celebi)
NEXUS_LOOKER_FILE_EXTERN(ChiYu)
NEXUS_LOOKER_FILE_EXTERN(ChienPao)
NEXUS_LOOKER_FILE_EXTERN(Cobalion)
NEXUS_LOOKER_FILE_EXTERN(Cresselia)
NEXUS_LOOKER_FILE_EXTERN(Darkrai)
NEXUS_LOOKER_FILE_EXTERN(Deoxys)
NEXUS_LOOKER_FILE_EXTERN(Dialga)
NEXUS_LOOKER_FILE_EXTERN(Diancie)
NEXUS_LOOKER_FILE_EXTERN(Enamorus)
NEXUS_LOOKER_FILE_EXTERN(Entei)
NEXUS_LOOKER_FILE_EXTERN(Eternatus)
NEXUS_LOOKER_FILE_EXTERN(Fezandipiti)
NEXUS_LOOKER_FILE_EXTERN(FlutterMane)
NEXUS_LOOKER_FILE_EXTERN(GalarianArticuno)
NEXUS_LOOKER_FILE_EXTERN(GalarianMoltres)
NEXUS_LOOKER_FILE_EXTERN(GalarianZapdos)
NEXUS_LOOKER_FILE_EXTERN(Genesect)
NEXUS_LOOKER_FILE_EXTERN(Giratina)
NEXUS_LOOKER_FILE_EXTERN(Glastrier)
NEXUS_LOOKER_FILE_EXTERN(GougingFire)
NEXUS_LOOKER_FILE_EXTERN(GreatTusk)
NEXUS_LOOKER_FILE_EXTERN(Groudon)
NEXUS_LOOKER_FILE_EXTERN(Heatran)
NEXUS_LOOKER_FILE_EXTERN(HoOh)
NEXUS_LOOKER_FILE_EXTERN(Hoopa)
NEXUS_LOOKER_FILE_EXTERN(IronBoulder)
NEXUS_LOOKER_FILE_EXTERN(IronBundle)
NEXUS_LOOKER_FILE_EXTERN(IronCrown)
NEXUS_LOOKER_FILE_EXTERN(IronHands)
NEXUS_LOOKER_FILE_EXTERN(IronJugulis)
NEXUS_LOOKER_FILE_EXTERN(IronLeaves)
NEXUS_LOOKER_FILE_EXTERN(IronMoth)
NEXUS_LOOKER_FILE_EXTERN(IronThorns)
NEXUS_LOOKER_FILE_EXTERN(IronTreads)
NEXUS_LOOKER_FILE_EXTERN(IronValiant)
NEXUS_LOOKER_FILE_EXTERN(Jirachi)
NEXUS_LOOKER_FILE_EXTERN(Keldeo)
NEXUS_LOOKER_FILE_EXTERN(Koraidon)
NEXUS_LOOKER_FILE_EXTERN(Kyogre)
NEXUS_LOOKER_FILE_EXTERN(Kyurem)
NEXUS_LOOKER_FILE_EXTERN(Landorus)
NEXUS_LOOKER_FILE_EXTERN(Latias)
NEXUS_LOOKER_FILE_EXTERN(Latios)
NEXUS_LOOKER_FILE_EXTERN(Lugia)
NEXUS_LOOKER_FILE_EXTERN(Lunala)
NEXUS_LOOKER_FILE_EXTERN(Magearna)
NEXUS_LOOKER_FILE_EXTERN(Manaphy)
NEXUS_LOOKER_FILE_EXTERN(Marshadow)
NEXUS_LOOKER_FILE_EXTERN(Melmetal)
NEXUS_LOOKER_FILE_EXTERN(Meloetta)
NEXUS_LOOKER_FILE_EXTERN(Mesprit)
NEXUS_LOOKER_FILE_EXTERN(Mew)
NEXUS_LOOKER_FILE_EXTERN(Mewtwo)
NEXUS_LOOKER_FILE_EXTERN(Miraidon)
NEXUS_LOOKER_FILE_EXTERN(Moltres)
NEXUS_LOOKER_FILE_EXTERN(Munkidori)
NEXUS_LOOKER_FILE_EXTERN(Necrozma)
NEXUS_LOOKER_FILE_EXTERN(Ogerpon)
NEXUS_LOOKER_FILE_EXTERN(Okidogi)
NEXUS_LOOKER_FILE_EXTERN(Palkia)
NEXUS_LOOKER_FILE_EXTERN(Pecharunt)
NEXUS_LOOKER_FILE_EXTERN(RagingBolt)
NEXUS_LOOKER_FILE_EXTERN(Raikou)
NEXUS_LOOKER_FILE_EXTERN(Rayquaza)
NEXUS_LOOKER_FILE_EXTERN(Regice)
NEXUS_LOOKER_FILE_EXTERN(Regidrago)
NEXUS_LOOKER_FILE_EXTERN(Regieleki)
NEXUS_LOOKER_FILE_EXTERN(Regigigas)
NEXUS_LOOKER_FILE_EXTERN(Regirock)
NEXUS_LOOKER_FILE_EXTERN(Registeel)
NEXUS_LOOKER_FILE_EXTERN(Reshiram)
NEXUS_LOOKER_FILE_EXTERN(RoaringMoon)
NEXUS_LOOKER_FILE_EXTERN(SandyShocks)
NEXUS_LOOKER_FILE_EXTERN(ScreamTail)
NEXUS_LOOKER_FILE_EXTERN(Shaymin)
NEXUS_LOOKER_FILE_EXTERN(Silvally)
NEXUS_LOOKER_FILE_EXTERN(SlitherWing)
NEXUS_LOOKER_FILE_EXTERN(Solgaleo)
NEXUS_LOOKER_FILE_EXTERN(Spectrier)
NEXUS_LOOKER_FILE_EXTERN(Suicune)
NEXUS_LOOKER_FILE_EXTERN(TapuBulu)
NEXUS_LOOKER_FILE_EXTERN(TapuFini)
NEXUS_LOOKER_FILE_EXTERN(TapuKoko)
NEXUS_LOOKER_FILE_EXTERN(TapuLele)
NEXUS_LOOKER_FILE_EXTERN(Terapagos)
NEXUS_LOOKER_FILE_EXTERN(Terrakion)
NEXUS_LOOKER_FILE_EXTERN(Thundurus)
NEXUS_LOOKER_FILE_EXTERN(TingLu)
NEXUS_LOOKER_FILE_EXTERN(Tornadus)
NEXUS_LOOKER_FILE_EXTERN(Urshifu)
NEXUS_LOOKER_FILE_EXTERN(Uxie)
NEXUS_LOOKER_FILE_EXTERN(Victini)
NEXUS_LOOKER_FILE_EXTERN(Virizion)
NEXUS_LOOKER_FILE_EXTERN(Volcanion)
NEXUS_LOOKER_FILE_EXTERN(WalkingWake)
NEXUS_LOOKER_FILE_EXTERN(WoChien)
NEXUS_LOOKER_FILE_EXTERN(Xerneas)
NEXUS_LOOKER_FILE_EXTERN(Yveltal)
NEXUS_LOOKER_FILE_EXTERN(Zacian)
NEXUS_LOOKER_FILE_EXTERN(Zamazenta)
NEXUS_LOOKER_FILE_EXTERN(Zapdos)
NEXUS_LOOKER_FILE_EXTERN(Zarude)
NEXUS_LOOKER_FILE_EXTERN(Zekrom)
NEXUS_LOOKER_FILE_EXTERN(Zeraora)
NEXUS_LOOKER_FILE_EXTERN(Zygarde)

NEXUS_CHAMPION_EXTERN(Colress)
NEXUS_CHAMPION_EXTERN(Bruno)
NEXUS_CHAMPION_EXTERN(Elesa)
NEXUS_CHAMPION_EXTERN(Volkner)
NEXUS_CHAMPION_EXTERN(Steven)
NEXUS_CHAMPION_EXTERN(Ramos)
NEXUS_CHAMPION_EXTERN(Guzma)
NEXUS_CHAMPION_EXTERN(Soliera)
NEXUS_CHAMPION_EXTERN(Byron)
NEXUS_CHAMPION_EXTERN(Fantina)
NEXUS_CHAMPION_EXTERN(Anabel_Deoxys)
NEXUS_CHAMPION_EXTERN(Anabel_Necrozma)
NEXUS_CHAMPION_EXTERN(Archer_Marshadow)
NEXUS_CHAMPION_EXTERN(Archer_WoChien)
NEXUS_CHAMPION_EXTERN(Archie)
NEXUS_CHAMPION_EXTERN(Ariana)
NEXUS_CHAMPION_EXTERN(Blaine_Moltres)
NEXUS_CHAMPION_EXTERN(Blaine_Volcanion)
NEXUS_CHAMPION_EXTERN(Blue_Victini)
NEXUS_CHAMPION_EXTERN(Blue_Zacian)
NEXUS_CHAMPION_EXTERN(Brandon_Regice)
NEXUS_CHAMPION_EXTERN(Brandon_Regirock)
NEXUS_CHAMPION_EXTERN(Brandon_Registeel)
NEXUS_CHAMPION_EXTERN(Brawly_IronHands)
NEXUS_CHAMPION_EXTERN(Brawly_Keldeo)
NEXUS_CHAMPION_EXTERN(Brendan_Jirachi)
NEXUS_CHAMPION_EXTERN(Brendan_Reshiram)
NEXUS_CHAMPION_EXTERN(Brock_IronThorns)
NEXUS_CHAMPION_EXTERN(Brock_Terrakion)
NEXUS_CHAMPION_EXTERN(Bugsy_IronMoth)
NEXUS_CHAMPION_EXTERN(Bugsy_SlitherWing)
NEXUS_CHAMPION_EXTERN(Chuck_Cobalion)
NEXUS_CHAMPION_EXTERN(Chuck_Urshifu)
NEXUS_CHAMPION_EXTERN(Clair)
NEXUS_CHAMPION_EXTERN(Drake_RagingBolt)
NEXUS_CHAMPION_EXTERN(Drake_Regidrago)
NEXUS_CHAMPION_EXTERN(Erika_Shaymin)
NEXUS_CHAMPION_EXTERN(Erika_Virizion)
NEXUS_CHAMPION_EXTERN(Eusine_Entei)
NEXUS_CHAMPION_EXTERN(Eusine_Raikou)
NEXUS_CHAMPION_EXTERN(Eusine_Suicune)
NEXUS_CHAMPION_EXTERN(Falkner)
NEXUS_CHAMPION_EXTERN(Flannery_ChiYu)
NEXUS_CHAMPION_EXTERN(Flannery_Heatran)
NEXUS_CHAMPION_EXTERN(Giovanni_Genesect)
NEXUS_CHAMPION_EXTERN(Giovanni_Mewtwo)
NEXUS_CHAMPION_EXTERN(Glacia_ChienPao)
NEXUS_CHAMPION_EXTERN(Glacia_IronBundle)
NEXUS_CHAMPION_EXTERN(Gladion_Silvally)
NEXUS_CHAMPION_EXTERN(Gladion_TapuBulu)
NEXUS_CHAMPION_EXTERN(Greta_GreatTusk)
NEXUS_CHAMPION_EXTERN(Greta_Koraidon)
NEXUS_CHAMPION_EXTERN(Janine_Munkidori)
NEXUS_CHAMPION_EXTERN(Janine_Okidogi)
NEXUS_CHAMPION_EXTERN(Jasmine_Lugia)
NEXUS_CHAMPION_EXTERN(Jasmine_Melmetal)
NEXUS_CHAMPION_EXTERN(Juan_TapuFini)
NEXUS_CHAMPION_EXTERN(Juan_WalkingWake)
NEXUS_CHAMPION_EXTERN(Karen_Darkrai)
NEXUS_CHAMPION_EXTERN(Karen_GalarianMoltres)
NEXUS_CHAMPION_EXTERN(Koga)
NEXUS_CHAMPION_EXTERN(Kukui_Solgaleo)
NEXUS_CHAMPION_EXTERN(Kukui_TapuKoko)
NEXUS_CHAMPION_EXTERN(Lance_GougingFire)
NEXUS_CHAMPION_EXTERN(Lance_Rayquaza)
NEXUS_CHAMPION_EXTERN(Leaf_IronLeaves)
NEXUS_CHAMPION_EXTERN(Leaf_Mew)
NEXUS_CHAMPION_EXTERN(Lillie_Lunala)
NEXUS_CHAMPION_EXTERN(Lillie_TapuLele)
NEXUS_CHAMPION_EXTERN(LtSurge_Regieleki)
NEXUS_CHAMPION_EXTERN(LtSurge_SandyShocks)
NEXUS_CHAMPION_EXTERN(LtSurge_Zapdos)
NEXUS_CHAMPION_EXTERN(Lucy_IronJugulis)
NEXUS_CHAMPION_EXTERN(Lucy_Zygarde)
NEXUS_CHAMPION_EXTERN(Lusamine_Enamorus)
NEXUS_CHAMPION_EXTERN(Lusamine_Fezandipiti)
NEXUS_CHAMPION_EXTERN(Maxie_Groudon)
NEXUS_CHAMPION_EXTERN(Maxie_Landorus)
NEXUS_CHAMPION_EXTERN(May_Mesprit)
NEXUS_CHAMPION_EXTERN(May_Zekrom)
NEXUS_CHAMPION_EXTERN(Misty_Kyogre)
NEXUS_CHAMPION_EXTERN(Misty_Manaphy)
NEXUS_CHAMPION_EXTERN(Morty_HoOh)
NEXUS_CHAMPION_EXTERN(Morty_Spectrier)
NEXUS_CHAMPION_EXTERN(Noland_IronTreads)
NEXUS_CHAMPION_EXTERN(Noland_Miraidon)
NEXUS_CHAMPION_EXTERN(Norman_Zamazenta)
NEXUS_CHAMPION_EXTERN(Norman_Zarude)
NEXUS_CHAMPION_EXTERN(Petrel_Meloetta)
NEXUS_CHAMPION_EXTERN(Petrel_Ogerpon)
NEXUS_CHAMPION_EXTERN(Phoebe)
NEXUS_CHAMPION_EXTERN(Proton_RoaringMoon)
NEXUS_CHAMPION_EXTERN(Proton_TingLu)
NEXUS_CHAMPION_EXTERN(Pryce_Articuno)
NEXUS_CHAMPION_EXTERN(Pryce_Glastrier)
NEXUS_CHAMPION_EXTERN(Red)
NEXUS_CHAMPION_EXTERN(Roxanne_Terapagos)
NEXUS_CHAMPION_EXTERN(Roxanne_Uxie)
NEXUS_CHAMPION_EXTERN(Sabrina_GalarianArticuno)
NEXUS_CHAMPION_EXTERN(Sabrina_Palkia)
NEXUS_CHAMPION_EXTERN(Sidney_BruteBonnet)
NEXUS_CHAMPION_EXTERN(Sidney_Yveltal)
NEXUS_CHAMPION_EXTERN(Silver)
NEXUS_CHAMPION_EXTERN(Spenser_Celebi)
NEXUS_CHAMPION_EXTERN(Spenser_Dialga)
NEXUS_CHAMPION_EXTERN(TateAndLiza_IronBoulder)
NEXUS_CHAMPION_EXTERN(TateAndLiza_Latias)
NEXUS_CHAMPION_EXTERN(TateAndLiza_Latios)
NEXUS_CHAMPION_EXTERN(Tucker_Eternatus)
NEXUS_CHAMPION_EXTERN(Tucker_Hoopa)
NEXUS_CHAMPION_EXTERN(Wallace_Diancie)
NEXUS_CHAMPION_EXTERN(Wallace_Xerneas)
NEXUS_CHAMPION_EXTERN(Wally_Azelf)
NEXUS_CHAMPION_EXTERN(Wally_IronValiant)
NEXUS_CHAMPION_EXTERN(Wattson_Magearna)
NEXUS_CHAMPION_EXTERN(Wattson_Zeraora)
NEXUS_CHAMPION_EXTERN(Whitney_Regigigas)
NEXUS_CHAMPION_EXTERN(Whitney_ScreamTail)
NEXUS_CHAMPION_EXTERN(Will_Calyrex)
NEXUS_CHAMPION_EXTERN(Will_IronCrown)
NEXUS_CHAMPION_EXTERN(Winona_GalarianZapdos)
NEXUS_CHAMPION_EXTERN(Winona_Thundurus)

const struct NexusLegendary gNexusLegendaries[] =
{
    { .species = SPECIES_NIHILEGO,    .champion = NEXUS_TRAINER_COLRESS, NEXUS_CHAMPION(Colress), NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Symbiont) },
    { .species = SPECIES_BUZZWOLE,    .champion = NEXUS_TRAINER_BRUNO,   NEXUS_CHAMPION(Bruno),   NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Absorption) },
    { .species = SPECIES_PHEROMOSA,   .champion = NEXUS_TRAINER_ELESA,   NEXUS_CHAMPION(Elesa),   NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Beauty) },
    { .species = SPECIES_XURKITREE,   .champion = NEXUS_TRAINER_VOLKNER, NEXUS_CHAMPION(Volkner), NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Lighting) },
    { .species = SPECIES_CELESTEELA,  .champion = NEXUS_TRAINER_STEVEN,  NEXUS_CHAMPION(Steven),  NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Blaster) },
    { .species = SPECIES_KARTANA,     .champion = NEXUS_TRAINER_RAMOS,   NEXUS_CHAMPION(Ramos),   NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Blade) },
    { .species = SPECIES_GUZZLORD,    .champion = NEXUS_TRAINER_GUZMA,   NEXUS_CHAMPION(Guzma),   NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Glutton) },
    {
        .species = SPECIES_NAGANADEL,
        .champion = NEXUS_TRAINER_SOLIERA,
        NEXUS_CHAMPION(Soliera),
        .requiresCaught = TRUE,             // evolves from the Route 40 Poipole
        NEXUS_BOSS_DEFAULT,
        NEXUS_LOOKER_FILE(Stinger),         // its fragment is a Poipole (R17)
    },
    { .species = SPECIES_STAKATAKA,   .champion = NEXUS_TRAINER_BYRON,   NEXUS_CHAMPION(Byron),   NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Assembly) },
    { .species = SPECIES_BLACEPHALON, .champion = NEXUS_TRAINER_FANTINA, NEXUS_CHAMPION(Fantina), NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Burst) },
    { .species = SPECIES_KYOGRE, .champion = NEXUS_TRAINER_MISTY, NEXUS_CHAMPION(Misty_Kyogre), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Kyogre) },
    { .species = SPECIES_KYOGRE, .champion = NEXUS_TRAINER_ARCHIE, NEXUS_CHAMPION(Archie), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Kyogre) },
    { .species = SPECIES_MEWTWO, .champion = NEXUS_TRAINER_GIOVANNI, NEXUS_CHAMPION(Giovanni_Mewtwo), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Mewtwo) },
    { .species = SPECIES_GENESECT, .champion = NEXUS_TRAINER_GIOVANNI, NEXUS_CHAMPION(Giovanni_Genesect), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_AFTER_BOSS(Genesect), NEXUS_LOOKER_FILE(Genesect) },
    { .species = SPECIES_LUGIA, .champion = NEXUS_TRAINER_JASMINE, NEXUS_CHAMPION(Jasmine_Lugia), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Lugia) },
    { .species = SPECIES_HO_OH, .champion = NEXUS_TRAINER_MORTY, NEXUS_CHAMPION(Morty_HoOh), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(HoOh) },
    { .species = SPECIES_GROUDON, .champion = NEXUS_TRAINER_MAXIE, NEXUS_CHAMPION(Maxie_Groudon), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Groudon) },
    { .species = SPECIES_RAYQUAZA, .champion = NEXUS_TRAINER_LANCE, NEXUS_CHAMPION(Lance_Rayquaza), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Rayquaza) },
    { .species = SPECIES_DIALGA, .champion = NEXUS_TRAINER_SPENSER, NEXUS_CHAMPION(Spenser_Dialga), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Dialga) },
    { .species = SPECIES_PALKIA, .champion = NEXUS_TRAINER_SABRINA, NEXUS_CHAMPION(Sabrina_Palkia), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Palkia) },
    { .species = SPECIES_GIRATINA_ALTERED, .champion = NEXUS_TRAINER_SILVER, NEXUS_CHAMPION(Silver), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Giratina) },
    { .species = SPECIES_SOLGALEO, .champion = NEXUS_TRAINER_KUKUI, NEXUS_CHAMPION(Kukui_Solgaleo), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Solgaleo) },
    { .species = SPECIES_LUNALA, .champion = NEXUS_TRAINER_LILLIE, NEXUS_CHAMPION(Lillie_Lunala), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Lunala) },
    { .species = SPECIES_NECROZMA, .champion = NEXUS_TRAINER_ANABEL, NEXUS_CHAMPION(Anabel_Necrozma), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Necrozma) },
    { .species = SPECIES_KORAIDON, .champion = NEXUS_TRAINER_GRETA, NEXUS_CHAMPION(Greta_Koraidon), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Koraidon) },
    { .species = SPECIES_MIRAIDON, .champion = NEXUS_TRAINER_NOLAND, NEXUS_CHAMPION(Noland_Miraidon), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Miraidon) },
    { .species = SPECIES_SILVALLY, .champion = NEXUS_TRAINER_GLADION, NEXUS_CHAMPION(Gladion_Silvally), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Silvally) },
    { .species = SPECIES_OGERPON, .champion = NEXUS_TRAINER_PETREL, NEXUS_CHAMPION(Petrel_Ogerpon), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Ogerpon) },
    { .species = SPECIES_ARTICUNO, .champion = NEXUS_TRAINER_PRYCE, NEXUS_CHAMPION(Pryce_Articuno), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Articuno) },
    { .species = SPECIES_ARTICUNO_GALAR, .champion = NEXUS_TRAINER_SABRINA, NEXUS_CHAMPION(Sabrina_GalarianArticuno), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(GalarianArticuno) },
    { .species = SPECIES_ZAPDOS, .champion = NEXUS_TRAINER_LT_SURGE, NEXUS_CHAMPION(LtSurge_Zapdos), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Zapdos) },
    { .species = SPECIES_ZAPDOS_GALAR, .champion = NEXUS_TRAINER_WINONA, NEXUS_CHAMPION(Winona_GalarianZapdos), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(GalarianZapdos) },
    { .species = SPECIES_MOLTRES, .champion = NEXUS_TRAINER_BLAINE, NEXUS_CHAMPION(Blaine_Moltres), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Moltres) },
    { .species = SPECIES_MOLTRES_GALAR, .champion = NEXUS_TRAINER_KAREN, NEXUS_CHAMPION(Karen_GalarianMoltres), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(GalarianMoltres) },
    { .species = SPECIES_RAIKOU, .champion = NEXUS_TRAINER_EUSINE, NEXUS_CHAMPION(Eusine_Raikou), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Raikou) },
    { .species = SPECIES_ENTEI, .champion = NEXUS_TRAINER_EUSINE, NEXUS_CHAMPION(Eusine_Entei), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Entei) },
    { .species = SPECIES_SUICUNE, .champion = NEXUS_TRAINER_EUSINE, NEXUS_CHAMPION(Eusine_Suicune), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Suicune) },
    { .species = SPECIES_REGIROCK, .champion = NEXUS_TRAINER_BRANDON, NEXUS_CHAMPION(Brandon_Regirock), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Regirock) },
    { .species = SPECIES_REGICE, .champion = NEXUS_TRAINER_BRANDON, NEXUS_CHAMPION(Brandon_Regice), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Regice) },
    { .species = SPECIES_REGISTEEL, .champion = NEXUS_TRAINER_BRANDON, NEXUS_CHAMPION(Brandon_Registeel), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Registeel) },
    { .species = SPECIES_LATIAS, .champion = NEXUS_TRAINER_TATE_AND_LIZA, NEXUS_CHAMPION(TateAndLiza_Latias), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Latias) },
    { .species = SPECIES_LATIOS, .champion = NEXUS_TRAINER_TATE_AND_LIZA, NEXUS_CHAMPION(TateAndLiza_Latios), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Latios) },
    { .species = SPECIES_UXIE, .champion = NEXUS_TRAINER_ROXANNE, NEXUS_CHAMPION(Roxanne_Uxie), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Uxie) },
    { .species = SPECIES_MESPRIT, .champion = NEXUS_TRAINER_MAY, NEXUS_CHAMPION(May_Mesprit), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Mesprit) },
    { .species = SPECIES_AZELF, .champion = NEXUS_TRAINER_WALLY, NEXUS_CHAMPION(Wally_Azelf), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Azelf) },
    { .species = SPECIES_HEATRAN, .champion = NEXUS_TRAINER_FLANNERY, NEXUS_CHAMPION(Flannery_Heatran), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Heatran) },
    { .species = SPECIES_REGIGIGAS, .champion = NEXUS_TRAINER_WHITNEY, NEXUS_CHAMPION(Whitney_Regigigas), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Regigigas) },
    { .species = SPECIES_CRESSELIA, .champion = NEXUS_TRAINER_ARIANA, NEXUS_CHAMPION(Ariana), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Cresselia) },
    { .species = SPECIES_COBALION, .champion = NEXUS_TRAINER_CHUCK, NEXUS_CHAMPION(Chuck_Cobalion), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Cobalion) },
    { .species = SPECIES_TERRAKION, .champion = NEXUS_TRAINER_BROCK, NEXUS_CHAMPION(Brock_Terrakion), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Terrakion) },
    { .species = SPECIES_VIRIZION, .champion = NEXUS_TRAINER_ERIKA, NEXUS_CHAMPION(Erika_Virizion), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Virizion) },
    { .species = SPECIES_TORNADUS_INCARNATE, .champion = NEXUS_TRAINER_FALKNER, NEXUS_CHAMPION(Falkner), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Tornadus) },
    { .species = SPECIES_THUNDURUS_INCARNATE, .champion = NEXUS_TRAINER_WINONA, NEXUS_CHAMPION(Winona_Thundurus), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Thundurus) },
    { .species = SPECIES_LANDORUS_INCARNATE, .champion = NEXUS_TRAINER_MAXIE, NEXUS_CHAMPION(Maxie_Landorus), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Landorus) },
    { .species = SPECIES_TAPU_KOKO, .champion = NEXUS_TRAINER_KUKUI, NEXUS_CHAMPION(Kukui_TapuKoko), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(TapuKoko) },
    { .species = SPECIES_TAPU_LELE, .champion = NEXUS_TRAINER_LILLIE, NEXUS_CHAMPION(Lillie_TapuLele), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(TapuLele) },
    { .species = SPECIES_TAPU_BULU, .champion = NEXUS_TRAINER_GLADION, NEXUS_CHAMPION(Gladion_TapuBulu), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(TapuBulu) },
    { .species = SPECIES_TAPU_FINI, .champion = NEXUS_TRAINER_JUAN, NEXUS_CHAMPION(Juan_TapuFini), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(TapuFini) },
    { .species = SPECIES_URSHIFU_SINGLE_STRIKE, .champion = NEXUS_TRAINER_CHUCK, NEXUS_CHAMPION(Chuck_Urshifu), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Urshifu) },
    { .species = SPECIES_ENAMORUS_INCARNATE, .champion = NEXUS_TRAINER_LUSAMINE, NEXUS_CHAMPION(Lusamine_Enamorus), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Enamorus) },
    { .species = SPECIES_CHIEN_PAO, .champion = NEXUS_TRAINER_GLACIA, NEXUS_CHAMPION(Glacia_ChienPao), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(ChienPao) },
    { .species = SPECIES_CHI_YU, .champion = NEXUS_TRAINER_FLANNERY, NEXUS_CHAMPION(Flannery_ChiYu), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(ChiYu) },
    { .species = SPECIES_FEZANDIPITI, .champion = NEXUS_TRAINER_LUSAMINE, NEXUS_CHAMPION(Lusamine_Fezandipiti), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Fezandipiti) },
    { .species = SPECIES_ARCEUS, .champion = NEXUS_TRAINER_RED, NEXUS_CHAMPION(Red), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Arceus) },
    { .species = SPECIES_MEW, .champion = NEXUS_TRAINER_LEAF, NEXUS_CHAMPION(Leaf_Mew), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Mew) },
    { .species = SPECIES_CELEBI, .champion = NEXUS_TRAINER_SPENSER, NEXUS_CHAMPION(Spenser_Celebi), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Celebi) },
    { .species = SPECIES_JIRACHI, .champion = NEXUS_TRAINER_BRENDAN, NEXUS_CHAMPION(Brendan_Jirachi), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Jirachi) },
    { .species = SPECIES_MANAPHY, .champion = NEXUS_TRAINER_MISTY, NEXUS_CHAMPION(Misty_Manaphy), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Manaphy) },
    { .species = SPECIES_DARKRAI, .champion = NEXUS_TRAINER_KAREN, NEXUS_CHAMPION(Karen_Darkrai), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Darkrai) },
    { .species = SPECIES_SHAYMIN_LAND, .champion = NEXUS_TRAINER_ERIKA, NEXUS_CHAMPION(Erika_Shaymin), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Shaymin) },
    { .species = SPECIES_VICTINI, .champion = NEXUS_TRAINER_BLUE, NEXUS_CHAMPION(Blue_Victini), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Victini) },
    { .species = SPECIES_MELOETTA, .champion = NEXUS_TRAINER_PETREL, NEXUS_CHAMPION(Petrel_Meloetta), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Meloetta) },
    { .species = SPECIES_DIANCIE, .champion = NEXUS_TRAINER_WALLACE, NEXUS_CHAMPION(Wallace_Diancie), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Diancie) },
    { .species = SPECIES_HOOPA_CONFINED, .champion = NEXUS_TRAINER_TUCKER, NEXUS_CHAMPION(Tucker_Hoopa), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Hoopa) },
    { .species = SPECIES_MAGEARNA, .champion = NEXUS_TRAINER_WATTSON, NEXUS_CHAMPION(Wattson_Magearna), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Magearna) },
    { .species = SPECIES_MARSHADOW, .champion = NEXUS_TRAINER_ARCHER, NEXUS_CHAMPION(Archer_Marshadow), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Marshadow) },
    { .species = SPECIES_ZERAORA, .champion = NEXUS_TRAINER_WATTSON, NEXUS_CHAMPION(Wattson_Zeraora), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Zeraora) },
    { .species = SPECIES_MELMETAL, .champion = NEXUS_TRAINER_JASMINE, NEXUS_CHAMPION(Jasmine_Melmetal), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Melmetal) },
    { .species = SPECIES_ZARUDE, .champion = NEXUS_TRAINER_NORMAN, NEXUS_CHAMPION(Norman_Zarude), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Zarude) },
    { .species = SPECIES_GREAT_TUSK, .champion = NEXUS_TRAINER_GRETA, NEXUS_CHAMPION(Greta_GreatTusk), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(GreatTusk) },
    { .species = SPECIES_SCREAM_TAIL, .champion = NEXUS_TRAINER_WHITNEY, NEXUS_CHAMPION(Whitney_ScreamTail), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(ScreamTail) },
    { .species = SPECIES_BRUTE_BONNET, .champion = NEXUS_TRAINER_SIDNEY, NEXUS_CHAMPION(Sidney_BruteBonnet), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(BruteBonnet) },
    { .species = SPECIES_FLUTTER_MANE, .champion = NEXUS_TRAINER_PHOEBE, NEXUS_CHAMPION(Phoebe), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(FlutterMane) },
    { .species = SPECIES_SLITHER_WING, .champion = NEXUS_TRAINER_BUGSY, NEXUS_CHAMPION(Bugsy_SlitherWing), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(SlitherWing) },
    { .species = SPECIES_SANDY_SHOCKS, .champion = NEXUS_TRAINER_LT_SURGE, NEXUS_CHAMPION(LtSurge_SandyShocks), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(SandyShocks) },
    { .species = SPECIES_IRON_TREADS, .champion = NEXUS_TRAINER_NOLAND, NEXUS_CHAMPION(Noland_IronTreads), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(IronTreads) },
    { .species = SPECIES_IRON_BUNDLE, .champion = NEXUS_TRAINER_GLACIA, NEXUS_CHAMPION(Glacia_IronBundle), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(IronBundle) },
    { .species = SPECIES_IRON_HANDS, .champion = NEXUS_TRAINER_BRAWLY, NEXUS_CHAMPION(Brawly_IronHands), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(IronHands) },
    { .species = SPECIES_IRON_JUGULIS, .champion = NEXUS_TRAINER_LUCY, NEXUS_CHAMPION(Lucy_IronJugulis), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(IronJugulis) },
    { .species = SPECIES_IRON_MOTH, .champion = NEXUS_TRAINER_BUGSY, NEXUS_CHAMPION(Bugsy_IronMoth), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(IronMoth) },
    { .species = SPECIES_IRON_THORNS, .champion = NEXUS_TRAINER_BROCK, NEXUS_CHAMPION(Brock_IronThorns), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(IronThorns) },
    { .species = SPECIES_ROARING_MOON, .champion = NEXUS_TRAINER_PROTON, NEXUS_CHAMPION(Proton_RoaringMoon), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(RoaringMoon) },
    { .species = SPECIES_IRON_VALIANT, .champion = NEXUS_TRAINER_WALLY, NEXUS_CHAMPION(Wally_IronValiant), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(IronValiant) },
    { .species = SPECIES_WALKING_WAKE, .champion = NEXUS_TRAINER_JUAN, NEXUS_CHAMPION(Juan_WalkingWake), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(WalkingWake) },
    { .species = SPECIES_IRON_LEAVES, .champion = NEXUS_TRAINER_LEAF, NEXUS_CHAMPION(Leaf_IronLeaves), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(IronLeaves) },
    { .species = SPECIES_GOUGING_FIRE, .champion = NEXUS_TRAINER_LANCE, NEXUS_CHAMPION(Lance_GougingFire), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(GougingFire) },
    { .species = SPECIES_RAGING_BOLT, .champion = NEXUS_TRAINER_DRAKE, NEXUS_CHAMPION(Drake_RagingBolt), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(RagingBolt) },
    { .species = SPECIES_IRON_BOULDER, .champion = NEXUS_TRAINER_TATE_AND_LIZA, NEXUS_CHAMPION(TateAndLiza_IronBoulder), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(IronBoulder) },
    { .species = SPECIES_IRON_CROWN, .champion = NEXUS_TRAINER_WILL, NEXUS_CHAMPION(Will_IronCrown), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(IronCrown) },
    { .species = SPECIES_DEOXYS, .champion = NEXUS_TRAINER_ANABEL, NEXUS_CHAMPION(Anabel_Deoxys), NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Deoxys) },
    { .species = SPECIES_RESHIRAM, .champion = NEXUS_TRAINER_BRENDAN, NEXUS_CHAMPION(Brendan_Reshiram), NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Reshiram) },
    { .species = SPECIES_ZEKROM, .champion = NEXUS_TRAINER_MAY, NEXUS_CHAMPION(May_Zekrom), NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Zekrom) },
    { .species = SPECIES_KYUREM, .champion = NEXUS_TRAINER_CLAIR, NEXUS_CHAMPION(Clair), NEXUS_BOSS_DEFAULT, NEXUS_AFTER_BOSS(Kyurem), NEXUS_LOOKER_FILE(Kyurem) },
    { .species = SPECIES_KELDEO, .champion = NEXUS_TRAINER_BRAWLY, NEXUS_CHAMPION(Brawly_Keldeo), NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Keldeo) },
    { .species = SPECIES_XERNEAS, .champion = NEXUS_TRAINER_WALLACE, NEXUS_CHAMPION(Wallace_Xerneas), NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Xerneas) },
    { .species = SPECIES_YVELTAL, .champion = NEXUS_TRAINER_SIDNEY, NEXUS_CHAMPION(Sidney_Yveltal), NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Yveltal) },
    { .species = SPECIES_ZYGARDE, .champion = NEXUS_TRAINER_LUCY, NEXUS_CHAMPION(Lucy_Zygarde), NEXUS_BOSS_DEFAULT, NEXUS_AFTER_BOSS(Zygarde), NEXUS_LOOKER_FILE(Zygarde) },
    { .species = SPECIES_VOLCANION, .champion = NEXUS_TRAINER_BLAINE, NEXUS_CHAMPION(Blaine_Volcanion), NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Volcanion) },
    { .species = SPECIES_ZACIAN, .champion = NEXUS_TRAINER_BLUE, NEXUS_CHAMPION(Blue_Zacian), NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Zacian) },
    { .species = SPECIES_ZAMAZENTA, .champion = NEXUS_TRAINER_NORMAN, NEXUS_CHAMPION(Norman_Zamazenta), NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Zamazenta) },
    { .species = SPECIES_ETERNATUS, .champion = NEXUS_TRAINER_TUCKER, NEXUS_CHAMPION(Tucker_Eternatus), NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Eternatus) },
    { .species = SPECIES_REGIELEKI, .champion = NEXUS_TRAINER_LT_SURGE, NEXUS_CHAMPION(LtSurge_Regieleki), NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Regieleki) },
    { .species = SPECIES_REGIDRAGO, .champion = NEXUS_TRAINER_DRAKE, NEXUS_CHAMPION(Drake_Regidrago), NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Regidrago) },
    // The Berry Master's Harvest King (Greenfield / the Brass Tower memory / Route 30):
    // only the steed the player chose can be caught outside; src/nexus.c asks
    // GardenSteed_NexusEligible which one waits for the capture.
    { .species = SPECIES_GLASTRIER, .champion = NEXUS_TRAINER_PRYCE, NEXUS_CHAMPION(Pryce_Glastrier), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Glastrier) },
    { .species = SPECIES_SPECTRIER, .champion = NEXUS_TRAINER_MORTY, NEXUS_CHAMPION(Morty_Spectrier), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Spectrier) },
    { .species = SPECIES_CALYREX, .champion = NEXUS_TRAINER_WILL, NEXUS_CHAMPION(Will_Calyrex), .requiresCaught = TRUE, NEXUS_BOSS_DEFAULT, NEXUS_AFTER_BOSS(Calyrex), NEXUS_LOOKER_FILE(Calyrex) },
    { .species = SPECIES_WO_CHIEN, .champion = NEXUS_TRAINER_ARCHER, NEXUS_CHAMPION(Archer_WoChien), NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(WoChien) },
    { .species = SPECIES_TING_LU, .champion = NEXUS_TRAINER_PROTON, NEXUS_CHAMPION(Proton_TingLu), NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(TingLu) },
    { .species = SPECIES_OKIDOGI, .champion = NEXUS_TRAINER_JANINE, NEXUS_CHAMPION(Janine_Okidogi), NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Okidogi) },
    { .species = SPECIES_MUNKIDORI, .champion = NEXUS_TRAINER_JANINE, NEXUS_CHAMPION(Janine_Munkidori), NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Munkidori) },
    { .species = SPECIES_TERAPAGOS, .champion = NEXUS_TRAINER_ROXANNE, NEXUS_CHAMPION(Roxanne_Terapagos), NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Terapagos) },
    { .species = SPECIES_PECHARUNT, .champion = NEXUS_TRAINER_KOGA, NEXUS_CHAMPION(Koga), NEXUS_BOSS_DEFAULT, NEXUS_LOOKER_FILE(Pecharunt) },
};

#undef NEXUS_CHAMPION_EXTERN
#undef NEXUS_CHAMPION
#undef NEXUS_LOOKER_FILE_EXTERN
#undef NEXUS_LOOKER_FILE
#undef NEXUS_BOSS_DEFAULT
