#ifndef GUARD_REMATCHES_H
#define GUARD_REMATCHES_H

// Match Call GSC: os treinadores que pedem o numero de telefone. A ordem e a
// posicao no save (SaveBlock1.trainerRematches[]) e na flag de registro
// (TRAINER_REGISTERED_FLAGS_START + indice): nao reordene sem motivo.
// Tudo abaixo de REMATCH_SPECIAL_TRAINER_START e treinador "normal", ou seja,
// entra no sorteio da ligacao por rota (src/match_call.c).
enum {
    // Johto
    REMATCH_JOEY,
    REMATCH_WADE,
    REMATCH_RALPH,
    REMATCH_LIZ,
    REMATCH_ANTHONY,
    REMATCH_TODD,
    REMATCH_GINA,
    REMATCH_IRWIN,
    REMATCH_ARNIE,
    REMATCH_ALAN,
    REMATCH_DANA,
    REMATCH_CHAD,
    REMATCH_DEREK,
    REMATCH_TULLY,
    REMATCH_BRENT,
    REMATCH_TIFFANY,
    REMATCH_VANCE,
    REMATCH_WILTON,
    REMATCH_KENJI,
    REMATCH_PARRY,
    REMATCH_ERIN,
    REMATCH_JACK,
    REMATCH_BEVERLY,
    REMATCH_HUEY,
    REMATCH_GAVEN,
    REMATCH_BETH,
    REMATCH_JOSE,
    REMATCH_REENA,
    // Kanto
    REMATCH_ALEX,
    REMATCH_RILEY,
    REMATCH_TREVOR,
    REMATCH_KYLE,
    REMATCH_CARTER,
    REMATCH_HILLARY,
    REMATCH_ROB,
    REMATCH_NICOLE,
    REMATCH_BILLY,
    REMATCH_KENNY,
    REMATCH_JOEL,
    REMATCH_CHARLES,
    // Daqui para baixo e treinador especial: fora do sorteio de rota. Os nomes
    // de Hoenn continuam porque src/pokenav_match_call_data.c os referencia
    // (os mapas deles estao fora da ROM; as entradas da tabela ficam vazias).
    REMATCH_WALLY_VR,
    REMATCH_ROXANNE,
    REMATCH_BRAWLY,
    REMATCH_WATTSON,
    REMATCH_FLANNERY,
    REMATCH_NORMAN,
    REMATCH_WINONA,
    REMATCH_TATE_AND_LIZA,
    REMATCH_JUAN,
    REMATCH_SIDNEY, // Entries from SIDNEY below are considered part of REMATCH_ELITE_FOUR_ENTRIES.
    REMATCH_PHOEBE,
    REMATCH_GLACIA,
    REMATCH_DRAKE,
    REMATCH_WALLACE,
    REMATCH_TABLE_ENTRIES // The total number of rematch entries. Must be last in enum
};

#define REMATCH_SPECIAL_TRAINER_START   REMATCH_WALLY_VR
#define REMATCH_ELITE_FOUR_ENTRIES      REMATCH_SIDNEY

#endif // GUARD_REMATCHES_H
