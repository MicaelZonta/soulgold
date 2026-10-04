#!/usr/bin/env python3
"""Acha falas de personagens com falante cadastrado que ainda saem sem plaquinha.

Para cada mapa, liga cada objeto do map.json ao falante pelo grafico
(OBJ_EVENT_GFX_MORTY -> NAME_MORTY, OBJ_EVENT_GFX_SPECIES(MILTANK) ->
NAME_MILTANK) e segue o script dele no mesmo arquivo (goto/call/
goto_if_*/call_if_*, e o que cai de um rotulo no outro). Toda fala que ele
abre com msgbox/message e que nao comeca com {SPEAKER ...} e candidata.
Fica de fora: texto de batalha (argumentos de trainerbattle_*), texto usado
tambem por outro objeto com outro falante, e narracao reconhecida pelo
comeco ("{PLAYER} received", "obtained", placas...).

    falantes_por_objeto.py              # lista por mapa
    falantes_por_objeto.py --aplicar    # poe {SPEAKER NAME_X} no comeco
    falantes_por_objeto.py --mapa EcruteakCity_Gym

Edita o .pory quando existe (o .inc e gerado).
"""
import json, re, sys
from pathlib import Path

REPO = Path(__file__).resolve().parents[3]
NOMES = set(re.findall(r'SP_NAME_(\w+),', (REPO / 'include/constants/speaker_names.h').read_text()))
NOMES -= {'COUNT', 'NONE', 'PLAYER', 'UNKNOWN'}
# so personagem com nome proprio: titulo generico (Boy, Sailor, Referee...) nao
# ganha plaquinha em todo NPC daquele grafico, e Pokemon de overworld costuma ter
# narracao ("Kingdra holds its ground."), nao fala
GENERICOS = {'BOY', 'SAILOR', 'OLD_MAN', 'NEIGHBOR', 'FLORIST', 'ELDER', 'OFFICER', 'ATTENDANT',
             'DIRECTOR', 'MANAGER', 'REFEREE', 'ROCKET', 'SPECTATORS', 'SCIENTIST', 'POLICE',
             'KIMONO_GIRL', 'AETHER', 'CHUCKS_WIFE', 'COPYCAT', 'DOVES'}
# graficos cujo nome nao bate com o falante
APELIDOS = {'OAK': 'OAK', 'PROF_ELM': 'ELM', 'ELM': 'ELM', 'BERRY_MASTER': 'BERRY_MASTER',
            'MOM': 'MOM', 'LEAF': 'GREEN', 'MOLLY_HALE': 'MOLLY', 'MOLLY_CHILD': 'MOLLY',
            'RIVAL_SILVER': 'SILVER', 'SILVER': 'SILVER'}
NARRACAO = re.compile(r'^(\{PLAYER\} (received|obtained|got|put|handed|found|gave|returned|traded|sent|learned|is|was|stored|registered|switched)'
                      r'|Obtained|Received|You (got|received|obtained|found)|.{0,40}\b(was|were) (registered|added|sent)\b)')
PREFIXO = re.compile(r'^[A-Z][A-Za-z.\' ]{1,14}: ')   # "Nome: " -> aplicar_falante.py
NARRACAO2 = re.compile(r'(\{PLAYER\} (passed|caught)|^Registered |\b(used|is snoring|is mimicking) |^The Kimono Girls|^The last ribbon'
                       r'|^A section of|^Later, |^The Radio was|^\{PLAYER\} caught)')
# texto ligado ao grafico, mas de outra pessoa: disfarces (Fuchsia: treinadores
# vestidos de Janine; Petrel fingindo ser o Giovanni)
NAO = {'FuchsiaCity_Gym_Text_CamperBarry_After', 'FuchsiaCity_Gym_Text_CamperBarry_Before',
       'FuchsiaCity_Gym_Text_LassAlice_After', 'FuchsiaCity_Gym_Text_LassAlice_Before',
       'FuchsiaCity_Gym_Text_LassLinda_After', 'FuchsiaCity_Gym_Text_LassLinda_Before',
       'FuchsiaCity_Gym_Text_PicnickerCindy_After', 'FuchsiaCity_Gym_Text_PicnickerCindy_Before',
       'RocketHideout_B3F_Text_PetrelIntro', 'RocketHideout_B3F_Text_PetrelDisbelief',
       'RocketHideout_B3F_Text_MurkrowMimic'}
SALTOS = re.compile(r'^\s*(goto|call|goto_if_\w+|call_if_\w+|goto_if_set|goto_if_unset|call_if_set|call_if_unset)\b(.*)$')
FALA = re.compile(r'^\s*(msgbox|message)\s+([A-Za-z_]\w*)')
FIM = re.compile(r'^\s*(end|return|goto|releaseall\s*$)')


def falante(gfx):
    if 'SPECIES' in gfx:
        return None
    n = gfx.replace('OBJ_EVENT_GFX_', '')
    n = re.sub(r'^(LEADER_|GYM_LEADER_|ELITE4_|E4_)', '', n)
    if n in APELIDOS:
        return APELIDOS[n]
    return n if n in NOMES and n not in GENERICOS else None


def blocos(linhas):
    """rotulo -> (inicio, fim) e a ordem dos rotulos, para seguir a queda."""
    pos = [(i, m.group(1)) for i, l in enumerate(linhas) if (m := re.match(r'^(\w+)::?\s*$', l))]
    return pos


def textos_do_script(linhas, inicio):
    idx = {nome: i for i, nome in blocos(linhas)}
    vistos, falas, fila = set(), [], [inicio]
    while fila:
        r = fila.pop()
        if r in vistos or r not in idx:
            continue
        vistos.add(r)
        i = idx[r] + 1
        while i < len(linhas):
            l = linhas[i].split('@')[0]
            if re.match(r'^\w+::?\s*$', l):      # cai no proximo rotulo
                fila.append(l.strip().rstrip(':'))
                break
            if re.match(r'^\s*\.string', l) or re.match(r'^\s*(step_end|\.byte|\.2byte)', l):
                break
            if 'trainerbattle' in l:
                i += 1
                continue
            m = FALA.match(l)
            if m:
                falas.append(m.group(2))
            m = SALTOS.match(l)
            if m:
                for alvo in re.findall(r'[A-Za-z_]\w*', m.group(2)):
                    if alvo in idx:
                        fila.append(alvo)
                if m.group(1) == 'goto':
                    break
            if re.match(r'^\s*(end|return)\s*$', l):
                break
            i += 1
    return falas


def batalha(linhas):
    s = set()
    for l in linhas:
        if 'trainerbattle' in l:
            s.update(re.findall(r'[A-Za-z_]\w*_Text_\w+|\b\w*Text\w*\b', l))
    return s


def primeira_string(linhas, rotulo):
    for i, l in enumerate(linhas):
        if re.match(rf'^{re.escape(rotulo)}::?\s*$', l):
            for j in range(i + 1, min(i + 4, len(linhas))):
                if re.match(r'^\s*\.string "', linhas[j]):
                    return j
            return None
    return None


def main():
    aplicar = '--aplicar' in sys.argv
    so = sys.argv[sys.argv.index('--mapa') + 1] if '--mapa' in sys.argv else None
    total = 0
    for mj in sorted((REPO / 'data/maps').glob('*/map.json')):
        mapa = mj.parent.name
        if so and mapa != so:
            continue
        src = mj.parent / 'scripts.pory'
        if not src.exists():
            src = mj.parent / 'scripts.inc'
        if not src.exists():
            continue
        linhas = src.read_text().split('\n')
        try:
            objs = json.loads(mj.read_text()).get('object_events', [])
        except Exception:
            continue
        bat = batalha(linhas)
        dono = {}
        for o in objs:
            sp = falante(o.get('graphics_id', ''))
            sc = o.get('script', '')
            if not sp or not sc or sc == 'NULL':
                continue
            for t in textos_do_script(linhas, sc):
                dono.setdefault(t, set()).add(sp)
        mud = []
        for t, sps in sorted(dono.items()):
            if len(sps) != 1 or t in bat:
                continue
            j = primeira_string(linhas, t)
            if j is None or 'SPEAKER' in linhas[j]:
                continue
            txt = re.match(r'^\s*\.string "(.*)', linhas[j]).group(1)
            if NARRACAO.match(txt) or NARRACAO2.search(txt) or PREFIXO.match(txt) or t in NAO:
                continue
            sp = next(iter(sps))
            mud.append((j, t, sp, txt[:60]))
        if mud:
            print(f'== {mapa} ({src.name}) {len(mud)}')
            for j, t, sp, txt in mud:
                print(f'   {sp:14} {t}: {txt}')
                if aplicar:
                    linhas[j] = linhas[j].replace('.string "', '.string "{SPEAKER NAME_%s}' % sp, 1)
            total += len(mud)
            if aplicar:
                src.write_text('\n'.join(linhas))
    print('total', total)


main()
