"""Gera data/maps/<Mapa>/scripts.inc (esqueleto da fase 1) para os mapas da Abundance Isle.
Nao sobrescreve um scripts.inc que ja tenha o marcador '@ FASE2' (escrito a mao depois)."""
import json, os, re, sys
R = '/home/ADMIN/decomps/soulgold_v1'
SC = os.path.join(R, '.claude/abundance_isle')
sys.path.insert(0, SC + '/instalar')
os.chdir(R)
need = json.load(open(SC + '/instalar/scripts_needed.json'))
VIS = json.load(open(SC + '/instalar/vis.json'))
import importlib.util
spec = importlib.util.spec_from_file_location('maps_mod_cond', SC + '/instalar/cond.py')
from cond import cond_asm
_tp = os.path.join(SC, 'instalar', 'treinadores.json')
TREIN = json.load(open(_tp)) if os.path.exists(_tp) else {}
TRTXT = {
 'PLASMA': ("Team Plasma has business on this\\nisland. Get lost, kid!", "Wh-what? Our plans...", "Lord Ghetsis will make this island\\nours, no matter what you do."),
 'HIKER': ("These rocks have been shaking with\\nthunder all week! Let's battle!", "Whoa, you've got legs of steel!", "A real hiker never fears a storm."),
 'PICNICKER': ("Snow at harvest time? At least we\\ncan still battle!", "Aww, I lost!", "I hope the flowers come back soon."),
 'FISHERMAN': ("The fish here bite even in this\\nweird weather. You, too?", "Snapped my line!", "The sea always gives something back."),
 'SWIMMER_F': ("The water here is so warm, even\\nwith all this strange weather!", "I'm all washed up!", "Swimming is the best way to cross\\nthe strait."),
 'SWIMMER_M': ("Out here, only the strong swimmers\\nmake it. Show me!", "Glub... You win!", "The current pulls south, toward\\nthe sand island."),
 'CAMPER': ("The farm needs every hand it can\\nget. But first, a battle!", "Back to work for me...", "This island lives on its harvest."),
 'LASS': ("Are you here because of the snow?\\nLet's see how strong you are!", "You're really good!", "Everyone here says the shrine\\nis angry."),
 'BIRD': ("My birds can't fly in these winds!\\nBut they can still battle!", "Grounded...", "When the winds calm down, we'll\\nsoar again."),
 'BLACK_BELT': ("I train under the lightning itself!\\nHaaah!", "Ugh! Defeated!", "A strong body weathers any storm."),
 'BEAUTY': ("The wind ruins my hair, but not\\nmy battling!", "How rude, winning like that.", "Even storms have their beauty."),
 'RUIN': ("These ruins hold the legend of the\\nHero of Truth! Don't touch anything!", "Ahh, my notes!", "The murals speak of a white stone\\nthat sleeps under the sand."),
}
COMMON = {'Common_EventScript_FindItem', 'EventScript_CutTree', 'EventScript_RockSmash', 'EventScript_StrengthBoulder',
          'Common_EventScript_Nurse', '0x0'}

def label_text(lbl):
    return lbl + '_Text'

for name, v in need.items():
    path = f'data/maps/{name}/scripts.inc'
    if os.path.exists(path) and '@ FASE2' in open(path).read():
        continue
    d, objs, bgs = v['d'], v['objs'], v['bgs']
    f2p = os.path.join(SC, 'fase2', name + '.inc')
    fase2 = open(f2p).read() if os.path.exists(f2p) else ''
    defined = set(re.findall(r'^(\w+)::', fase2, re.M)) | set(re.findall(r'^(\w+):(?!:)', fase2, re.M))
    out = [f'{name}_MapScripts::'] if f'{name}_MapScripts' not in defined else []
    vis = VIS.get(d, {})
    if out and vis:
        out.append(f'\tmap_script MAP_SCRIPT_ON_TRANSITION, {name}_OnTransition')
    if out: out += ['\t.byte 0', '']
    if vis and f'{name}_MapScripts' not in defined:
        out.append(f'{name}_OnTransition::')
        for fl in vis: out.append(f'\tcall {name}_EventScript_Vis_{fl[5:]}')
        out += ['\tend', '']
    if vis:
        for fl, (cond, _) in vis.items():
            base = f'{name}_EventScript_Vis_{fl[5:]}'
            out.append(f'{base}::')
            out.append(cond_asm(cond, base + '_Show').rstrip('\n'))
            out += [f'{base}_No::', f'{base}_Show_No::', f'\tsetflag {fl}', '\treturn', f'{base}_Show::', f'\tclearflag {fl}', '\treturn', '']
    done = set(); texts = []
    for o in objs:
        s = o['script']
        if s in COMMON or s in done or s in defined: continue
        done.add(s)
        g = o['graphics_id'].replace('OBJ_EVENT_GFX_', '')
        if o['local_id'] in TREIN:
            tr = TREIN[o['local_id']]; base = s
            txt = TRTXT[tr['cls']]
            out += [f'{s}::', f'\ttrainerbattle_single {tr["const"]}, {base}_Text_Seen, {base}_Text_Beaten', f'\tmsgbox {base}_Text_After, MSGBOX_AUTOCLOSE', '\tend', '']
            texts += [(f'{base}_Text_Seen', txt[0]), (f'{base}_Text_Beaten', txt[1]), (f'{base}_Text_After', txt[2])]
            continue
        if s.endswith('_EventScript_Nurse'):
            out += [f'{s}::', f'\tsetvar VAR_0x800B, {o["local_id"]}', '\tcall Common_EventScript_PkmnCenterNurse', '\twaitmessage',
                    '\twaitbuttonpress', '\trelease', '\tend', '']
            continue
        m = re.match(r'SPECIES\((\w+)\)', g)
        if m:
            sp = m.group(1)
            out += [f'{s}::', '\tlock', '\tfaceplayer', f'\tplaymoncry SPECIES_{sp}, CRY_MODE_NORMAL',
                    f'\tmsgbox {label_text(s)}, MSGBOX_DEFAULT', '\twaitmoncry', '\trelease', '\tend', '']
            texts.append((label_text(s), sp.split('_')[0].capitalize() + '!'))
        else:
            out += [f'{s}::', '\tmsgbox ' + label_text(s) + ', MSGBOX_NPC', '\tend', '']
            texts.append((label_text(s), '...'))
    for b in bgs:
        if b['type'] != 'sign': continue
        s = b['script']
        if s in done or s in defined: continue
        done.add(s)
        out += [f'{s}::', '\tmsgbox ' + label_text(s) + ', MSGBOX_SIGN', '\tend', '']
        texts.append((label_text(s), '...'))
    for k, dest, wid, *queda in v.get('warp_triggers', []):
        if queda and queda[0]:   # buraco / sumidouro: o jogador cai (mesma animacao do Mt. Pyre)
            out += [f'{name}_EventScript_WarpTrigger{k}::', '\tlockall', f'\tsetwarp {dest}, {wid}',
                    '\tspecial DoFallWarp', '\twaitstate', '\tend', '']
        else:
            out += [f'{name}_EventScript_WarpTrigger{k}::', f'\twarp {dest}, {wid}', '\twaitstate', '\tend', '']
    for lbl, tx in texts:
        if lbl in defined: continue
        out += [f'{lbl}:', f'\t.string "{tx}$"', '']
    if fase2: out += ['@ ---------------- fase 2 (.claude/abundance_isle/fase2/%s.inc)' % name, fase2]
    open(path, 'w').write('\n'.join(out) + '\n')
print('ok', len(need))
