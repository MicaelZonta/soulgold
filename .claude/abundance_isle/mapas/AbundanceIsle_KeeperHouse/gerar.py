import sys; sys.path.insert(0, '/tmp/claude-1000/-home-ADMIN-decomps-soulgold-v1/f7061873-479d-4342-8a14-d05cd0f98ec2/scratchpad/ilha/m20')
from interior import *
D = os.path.dirname(os.path.abspath(__file__))
OBJ = [o('KEEPER_WIFE', 'OLD_WOMAN', 10, 5, 'DOWN', 'KeeperHouse_EventScript_Wife'),
       o('APPRENTICE', 'YOUNGSTER', 4, 3, 'UP', 'KeeperHouse_EventScript_Apprentice'),
       o('CYNTHIA', 'CYNTHIA', 15, 4, 'UP', 'KeeperHouse_EventScript_Cynthia', flag='FLAG_HIDE_KEEPER_HOUSE_CYNTHIA'),
       o('ITEM_REVEAL_GLASS_CASE', 'ITEM_BALL', 2, 7, script='KeeperHouse_EventScript_ItemSoothBell')]
interior(D, 'AzaleaTown_KurtsHouse', dict(map='AbundanceIsle_KeeperHouse', ingame='Shrine Keeper\'s House',
    warps=[dict(x=4, y=8, dest_map='MAP_ABUNDANCE_ISLE_HARVEST_FIELDS', dest_warp_id='0', nota='porta da casa do guardiao em Harvest Fields')], connections=[],
    explorar=['Bancada de trabalho: o aprendiz pole a Reveal Glass que o guardiao entrega depois do Landorus.',
              'Cynthia estuda os pergaminhos da lenda: conta a ordem certa (os dois genios, depois o Senhor da Terra, depois o Arauto) e aceita batalha opcional depois do ato 5, com revanche semanal.',
              'A esposa do guardiao explica que ele fica no santuario do hub e so volta quando a neve parar.',
              'Soothe Bell no canto da sala.'],
    historia='Atos 1 e 5: guarda a lenda em pergaminhos e a Reveal Glass; Cynthia da a leitura "academica" da lenda.',
    estados=dict(dia='Interior (oficina e sala).')), OBJ, (4, 8), crop_w=17)
