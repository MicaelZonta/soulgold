"""Visual do Team Plasma na Abundance Isle (sprites novos de 31/10/2026), comum ao maps.py e ao treinadores.py.
Ghetsis: OBJ_EVENT_GFX_GHETSIS / pic Ghetsis. Recrutas: PLASMA_GRUNT_M/F (genero fixo por local_id, o mesmo no
boneco e no pic de batalha). Cientistas de verdade (lab, pesquisador, sala de maquinas) continuam Scientist."""
import zlib

SCIENTIST_KEYS = ('SCIENTIST', 'RESEARCHER', 'ENGINE_ROOM_CHIEF', 'ENGINE_ROOM_ASSIST')


def is_scientist(local_id):
    return any(k in local_id.upper() for k in SCIENTIST_KEYS)


def grunt_female(local_id):
    suf = local_id.upper().split('LOCALID_')[-1]
    return zlib.crc32(suf.encode()) % 2 == 1


def object_gfx(local_id, gfx):
    if gfx == 'OBJ_EVENT_GFX_SS_TIDAL' and 'PLASMA_FRIGATE' in local_id.upper():   # navio do cais da Cape (arte A, 31/10)
        return 'OBJ_EVENT_GFX_PLASMA_FRIGATE'
    if gfx == 'OBJ_EVENT_GFX_SAGE' and 'GHETSIS' in local_id.upper():
        return 'OBJ_EVENT_GFX_GHETSIS'
    if gfx == 'OBJ_EVENT_GFX_SCIENTIST_1' and not is_scientist(local_id):
        return 'OBJ_EVENT_GFX_PLASMA_GRUNT_F' if grunt_female(local_id) else 'OBJ_EVENT_GFX_PLASMA_GRUNT_M'
    return gfx


def trainer_look(local_id):
    """(classe, pic, genero) para um treinador comum do Plasma."""
    if is_scientist(local_id):
        return 'Scientist', 'Scientist', 'Male'
    return ('Team Plasma', 'Plasma Grunt F', 'Female') if grunt_female(local_id) else ('Team Plasma', 'Plasma Grunt M', 'Male')
