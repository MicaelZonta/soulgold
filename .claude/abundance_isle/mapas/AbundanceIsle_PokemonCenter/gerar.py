import sys; sys.path.insert(0, '/tmp/claude-1000/-home-ADMIN-decomps-soulgold-v1/f7061873-479d-4342-8a14-d05cd0f98ec2/scratchpad/ilha/m20')
from a2_comum import *
P = os.path.dirname(os.path.abspath(__file__))
L = src('CianwoodPokecenter')
g = Grid(L['w'], L['h'], 0); stamp(g, 'CianwoodPokecenter', 0, 0, L['w'], L['h'], 0, 0)
import shutil; shutil.copy(os.path.join(ROOT, L['info']['border_filepath']), os.path.join(P, 'border.bin'))
objs = [o('NURSE', 'NURSE', 7, 2, move='MOVEMENT_TYPE_NONE', script='Common_EventScript_Nurse'),
        o('CHANSEY', 'SPECIES(CHANSEY)', 8, 2, 'DOWN', 'NULL'),
        o('FARMER_GIRL', 'LASS', 3, 6, move='MOVEMENT_TYPE_WANDER_AROUND', script='AbundanceIsle_PokemonCenter_EventScript_Girl'),
        o('SAILOR', 'SAILOR', 12, 5, 'LEFT', 'AbundanceIsle_PokemonCenter_EventScript_Sailor'),
        o('OLD_WOMAN', 'OLD_WOMAN', 14, 6, 'LEFT', 'AbundanceIsle_PokemonCenter_EventScript_OldWoman'),
        o('NEMONA', 'NEMONA', 10, 4, 'DOWN', 'AbundanceIsle_PokemonCenter_EventScript_Nemona'),
        o('BARRY', 'BARRY', 6, 7, 'UP', 'AbundanceIsle_PokemonCenter_EventScript_Barry')]
d = bfs(g.flat(), g.w, g.h, (7, 8))
bad = [x['local_id'] for x in objs if not alcanca(d, x) and x['local_id'] not in ('NURSE', 'CHANSEY')]; assert not bad, bad
info = dict(map='AbundanceIsle_PokemonCenter', ingame='Abundance Isle Pokemon Center', primary=L['info']['primary_tileset'],
    secondary=L['info']['secondary_tileset'], map_type='MAP_TYPE_INDOOR',
    warps=[dict(x=7, y=8, dest_map='MAP_ABUNDANCE_ISLE_WINDSWEPT_CAPE', dest_warp_id='0', nota='porta do PC na Windswept Cape')],
    connections=[],
    explorar=['Marinheiro conta que o navio escuro no cais chegou junto com a primeira neve.',
              'Velhinha da ilha recita o verso da lenda: "when the winter breaks, love comes from across the sea" (pista do Enamorus).',
              'Menina da fazenda pede para ver um Pokémon de Tipo Terra (pista do Landorus).',
              'Nemona veio de férias e quer batalhar com todo mundo: batalha opcional, repetível uma vez por dia.',
              'Barry, apressado, entrou correndo para fugir da neve; reclama que o barco atrasou e aponta o navio escuro no cais (pista do Plasma Frigate). Multa o jogador por esbarrar nele (piada dele).'],
    historia='Único Centro Pokémon da ilha, no cabo. Layout padrão de PC (cópia do CianwoodPokecenter); as falas dos NPCs plantam pistas da lenda.',
    estados={'dia': 'Interior padrão com enfermeira, Chansey e três moradores.'},
    conferido='Layout copiado de CianwoodPokecenter (mesmo par de tilesets); BFS da porta até todos os NPCs; check_objects.')
entregar(P, g, L['prim'], L['sec'], info, objs)
