"""Johto menos biodiverso (pedido do autor, 31/10/2026): enxuga as tabelas de terra dos mapas de Johto com 9+
especies e manda para a Abundance Isle as especies de Unova que so existiam ali.

Regra, mapa por mapa (so mapas de Johto na ROM, fora as salas de Unown de Sinjoh), ate ficar com <= ALVO especies:
  1. especie de fora de Johto que aparece em OUTROS mapas sai deste;
  2. especie de Unova listada em MIGRA (agora selvagem na ilha, selvagens.py) sai de Johto;
  3. especie de fora que so existe aqui fica, mas vai para os slots de 1% (mais rara so em Johto).
A vaga que sobra vai para a nativa de Johto mais comum da mesma tabela (mesmo nivel do slot).
Idempotente (rodar de novo nao muda nada). Grava o changelog em instalar/fauna_johto.log. Rodar da raiz do repo
DEPOIS do selvagens.py; depois make."""
import collections, glob, json, re

P = 'src/data/wild_encounters.json'
ALVO = 8
MIGRA = {'PIDOVE', 'PATRAT', 'MINCCINO', 'PURRLOIN', 'DUCKLETT', 'FOONGUS', 'PANSAGE', 'PANPOUR', 'SHELMET', 'JOLTIK',
         'MUNNA', 'GOTHITA', 'SOLOSIS', 'HEATMOR', 'KLINK', 'DURANT'}
CROSS = {'AZURILL', 'WYNAUT', 'BONSLY', 'MIME_JR', 'HAPPINY', 'MUNCHLAX', 'MANTYKE', 'HONCHKROW', 'MISMAGIUS', 'WEAVILE',
         'MAGNEZONE', 'LICKILICKY', 'RHYPERIOR', 'TANGROWTH', 'ELECTIVIRE', 'MAGMORTAR', 'TOGEKISS', 'YANMEGA', 'LEAFEON',
         'GLACEON', 'GLISCOR', 'MAMOSWINE', 'PORYGON_Z', 'AMBIPOM', 'SYLVEON', 'ANNIHILAPE', 'FARIGIRAF', 'DUDUNSPARCE',
         'CLODSIRE', 'URSALUNA', 'SNEASLER', 'OVERQWIL', 'WYRDEER', 'KLEAVOR', 'PERRSERKER', 'SIRFETCHD', 'MR_RIME'}
KANTO = ('PalletTown', 'ViridianCity', 'PewterCity', 'CeruleanCity', 'VermilionCity', 'LavenderTown', 'CeladonCity',
         'FuchsiaCity', 'SaffronCity', 'CinnabarIsland', 'MtMoon', 'DiglettsCave', 'RockTunnel', 'VictoryRoad', 'SeafoamIslands',
         'CeruleanCave', 'PowerPlant', 'ViridianForest', 'SafariZone', 'MtSilver', 'PokemonTower', 'MtEmber', 'OneIsland',
         'TwoIsland', 'ThreeIsland', 'FourIsland', 'FiveIsland', 'SixIsland', 'SevenIsland', 'NavelRock', 'BirthIsland', 'Kanto')
NAO_JOHTO = ('Abundance', 'Frostfall', 'Thunder', 'Plasma', 'Truthsand', 'Emberdune', 'Sunken', 'ShrineOfThe', 'NsRoom',
             'Nexus', 'Ula', 'Kitakami', 'Alola', 'Melemele', 'Akala', 'Poni')


def main():
    t = json.load(open(P))
    g = next(x for x in t['wild_encounter_groups'] if x['label'] == 'gWildMonHeaders')
    txt = open('include/constants/species.h').read()
    nd = {}
    for m in re.finditer(r'#define (SPECIES_\w+)\s+(\w+)\b', txt):
        nd[m.group(1)] = int(m.group(2)) if m.group(2).isdigit() else nd.get(m.group(2))
    ids = {json.load(open(f))['id']: json.load(open(f))['name'] for f in glob.glob('data/maps/*/map.json')}
    grp = json.load(open('data/maps/map_groups.json'))
    fora = {m for gname in grp['rom_excluded_groups'] for m in grp[gname]}

    def johto(nm):
        if nm in fora or any(k in nm for k in NAO_JOHTO) or nm.startswith(('SinjohRuins_Reg', 'SinjohRuins_Temple', 'RuinsOfAlph')):   # Unown: quebra-cabeca, nao mexe
            return False
        r = re.match(r'Route(\d+)', nm)
        if r:
            return int(r.group(1)) > 28
        return not nm.startswith(KANTO)

    def nativo(sp):
        n = nd.get(sp) or nd.get(re.sub(r'_[A-Z0-9]+$', '', sp)) or 0
        return n <= 251 or any(sp[8:].startswith(c) for c in CROSS)

    def lugares():
        porsp = collections.defaultdict(set)
        for e in g['encounters']:
            nm = ids.get(e['map'], e['map'])
            if nm in fora:
                continue
            for k in ('land_mons', 'water_mons', 'rock_smash_mons', 'fishing_mons'):
                for m in e.get(k, {}).get('mons', []):
                    porsp[m['species']].add(nm)
        return porsp

    log = []
    for e in g['encounters']:
        nm = ids.get(e['map'], e['map'])
        if not johto(nm) or 'land_mons' not in e:
            continue
        mons = e['land_mons']['mons']
        while True:
            esp = list(dict.fromkeys(m['species'] for m in mons))
            if len(esp) <= ALVO:
                break
            porsp = lugares()
            nativas = collections.Counter(m['species'] for m in mons if nativo(m['species']))
            if not nativas:
                break
            alvo_nat = nativas.most_common(1)[0][0]
            fora_j = [s for s in esp if not nativo(s)]
            sai = [s for s in fora_j if len(porsp[s]) > 1 or s[8:] in MIGRA]
            if sai:
                s = sorted(sai, key=lambda x: -len(porsp[x]))[0]
                for m in mons:
                    if m['species'] == s:
                        m['species'] = alvo_nat
                motivo = 'migrou para a Abundance Isle' if s[8:] in MIGRA else f'existe em {len(porsp[s]) - 1} outro(s) mapa(s)'
                log.append(f'{nm}: sai {s[8:]} ({motivo}) -> vaga para {alvo_nat[8:]}')
                continue
            # so especies unicas: rebaixa uma para 1% (slots 10 e 11) e conta como resolvido neste mapa
            raros = [m['species'] for m in mons[10:]]
            cand = [s for s in fora_j if s not in raros]
            if not cand:
                break
            s = cand[0]
            idx = [i for i, m in enumerate(mons) if m['species'] == s]
            livres = [i for i in (10, 11) if nativo(mons[i]['species'])]
            if not livres:
                break
            slot_raro = livres[0]
            quem = mons[slot_raro]['species']        # permuta: a nativa que estava no 1% assume as vagas da rebaixada
            for i in idx:
                mons[i]['species'] = quem
            mons[slot_raro]['species'] = s
            log.append(f'{nm}: {s[8:]} fica so em 1% (unico lugar do jogo); {quem[8:]} assume as vagas dela')
            break
    open(P, 'w').write(json.dumps(t, indent=2) + '\n')
    open('.claude/abundance_isle/instalar/fauna_johto.log', 'w').write('\n'.join(log) + '\n')
    print(len(log), 'mudancas')


if __name__ == '__main__':
    main()
