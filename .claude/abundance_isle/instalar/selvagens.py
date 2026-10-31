"""Pokemon selvagens da Abundance Isle em src/data/wild_encounters.json (gWildMonHeaders).

So entram os tipos que o mapa consegue disparar: encontro em terra exige peca com comportamento de
encontro (grama alta, caverna, areia funda...). Hub, Harvest Fields, Gale Shore e Thunder Ridge nao tem
grama alta (so agua); a Engine Room do Frigate tem chao de caverna: taxa baixa (5).
Niveis pos-Liga: comuns 66-72, raros 72-76 (treinadores da ilha 70-80).
Idempotente: remove as entradas desses mapas e regrava. Rodar da raiz do repo; depois make."""
import json

P = 'src/data/wild_encounters.json'


def mons(lst):
    out = []
    for item in lst:
        sp, lo, hi = item if len(item) == 3 else (item[0], item[1], item[1])
        out.append(dict(min_level=lo, max_level=hi, species='SPECIES_' + sp))
    return out


def land(rate, *twelve):       # 12 slots: 20 20 10 10 10 10 5 5 4 4 1 1
    assert len(twelve) == 12
    return dict(encounter_rate=rate, mons=mons(twelve))


def five(rate, *five_):          # agua / rock smash: 60 30 5 4 1
    assert len(five_) == 5
    return dict(encounter_rate=rate, mons=mons(five_))


def fish(rate, *ten):           # old 0-1, good 2-4, super 5-9
    assert len(ten) == 10
    return dict(encounter_rate=rate, mons=mons(ten))


MAR = five(4, ('PELIPPER', 66, 70), ('TENTACRUEL', 66, 70), ('JELLICENT', 68, 72), ('WAILORD', 70, 74), ('LAPRAS', 72, 76))
LAGO = five(4, ('BASCULIN', 66, 70), ('LUMINEON', 66, 70), ('GOLDUCK', 68, 72), ('SEAKING', 68, 72), ('GYARADOS', 72, 76))
PESCA_MAR = fish(30, ('MAGIKARP', 20, 30), ('TENTACOOL', 30, 40), ('BASCULIN', 55, 65), ('FRILLISH', 55, 65), ('SHARPEDO', 60, 68),
                 ('GYARADOS', 66, 72), ('JELLICENT', 66, 72), ('ALOMOMOLA', 66, 72), ('KINGDRA', 70, 74), ('DRAGONAIR', 70, 74))
PESCA_LAGO = fish(30, ('MAGIKARP', 20, 30), ('GOLDEEN', 30, 40), ('BASCULIN', 55, 65), ('LUMINEON', 55, 65), ('SEAKING', 60, 68),
                  ('GYARADOS', 66, 72), ('BASCULIN', 66, 72), ('LUMINEON', 66, 72), ('POLITOED', 70, 74), ('DRAGONAIR', 70, 74))

GELO_A = land(10, ('VANILLISH', 66, 68), ('CUBCHOO', 66, 68), ('BEARTIC', 68, 70), ('VANILLUXE', 68, 70), ('CRYOGONAL', 68, 70),
              ('SNEASEL', 66, 68), ('GLALIE', 68, 70), ('FROSLASS', 68, 70), ('BERGMITE', 66, 68), ('AVALUGG', 70, 72),
              ('WEAVILE', 72, 74), ('DEINO', 66, 66))
GELO_B = land(10, ('BEARTIC', 68, 70), ('VANILLUXE', 68, 70), ('CRYOGONAL', 68, 72), ('AVALUGG', 70, 72), ('WEAVILE', 70, 72),
              ('FROSLASS', 70, 72), ('GLALIE', 70, 72), ('ABOMASNOW', 70, 72), ('ZWEILOUS', 70, 72), ('ZWEILOUS', 72, 74),
              ('HYDREIGON', 74, 76), ('DRUDDIGON', 74, 76))

TORRE = land(10, ('EELEKTRIK', 66, 68), ('GOLETT', 66, 68), ('LAMPENT', 66, 68), ('MUNNA', 66, 68), ('SOLOSIS', 66, 68),
             ('SIGILYPH', 68, 70), ('GOLURK', 68, 70), ('EELEKTROSS', 70, 72), ('FRAXURE', 70, 72), ('GOTHITA', 66, 68),
             ('ROTOM', 72, 74), ('CHANDELURE', 74, 76))
TORRE_ALTA = land(10, ('GOLURK', 68, 70), ('LAMPENT', 68, 70), ('GALVANTULA', 68, 70), ('EELEKTROSS', 70, 72), ('SIGILYPH', 70, 72),
                  ('KLINKLANG', 70, 72), ('FRAXURE', 70, 72), ('ZEBSTRIKA', 70, 72), ('ROTOM', 72, 74), ('CHANDELURE', 72, 74),
                  ('HAXORUS', 74, 76), ('ZWEILOUS', 74, 76))

FAZENDA = land(20, ('MAREEP', 66, 68), ('FLAAFFY', 66, 68), ('TAUROS', 68, 70), ('MILTANK', 68, 70), ('STOUTLAND', 68, 70),
               ('UNFEZANT', 68, 70), ('BOUFFALANT', 68, 70), ('GOGOAT', 68, 70), ('DUBWOOL', 70, 72), ('AMPHAROS', 70, 72),
               ('SAWSBUCK', 72, 74), ('FARFETCHD', 72, 74))
# campos da Harvest Fields: bichos de campo de Unova que sairam das rotas cheias de Johto (fauna.py) + gado
CAMPO = land(20, ('PATRAT', 66, 68), ('PIDOVE', 66, 68), ('MINCCINO', 66, 68), ('PURRLOIN', 66, 68), ('MAREEP', 66, 68),
             ('FOONGUS', 66, 68), ('DUCKLETT', 66, 68), ('TAUROS', 68, 70), ('MILTANK', 68, 70), ('BOUFFALANT', 68, 70),
             ('STOUTLAND', 70, 72), ('FARFETCHD', 72, 74))
VENTO = land(20, ('TRANQUILL', 66, 68), ('SWANNA', 66, 68), ('UNFEZANT', 68, 70), ('RUFFLET', 66, 68), ('DRIFBLIM', 68, 70),
             ('BRAVIARY', 70, 72), ('PELIPPER', 68, 70), ('EMOLGA', 68, 70), ('STARAPTOR', 70, 72), ('NOIVERN', 70, 72),
             ('TALONFLAME', 72, 74), ('ALTARIA', 72, 74))
VENTO_TEMPESTADE = land(25, ('EMOLGA', 68, 70), ('BRAVIARY', 70, 72), ('DRIFBLIM', 70, 72), ('SWANNA', 70, 72), ('NOIVERN', 70, 72),
                        ('STARAPTOR', 70, 72), ('TALONFLAME', 72, 74), ('ZEBSTRIKA', 72, 74), ('ROTOM', 72, 74), ('ALTARIA', 72, 74),
                        ('DRAGONITE', 74, 76), ('ARCHEOPS', 74, 76))
MONTANHA = land(20, ('JOLTIK', 66, 68), ('EMOLGA', 66, 68), ('BLITZLE', 66, 68), ('THROH', 68, 70), ('SAWK', 68, 70),
                ('ZEBSTRIKA', 68, 70), ('GALVANTULA', 68, 70), ('EXCADRILL', 70, 72), ('GIGALITH', 70, 72), ('LUXRAY', 70, 72),
                ('ELECTIVIRE', 72, 74), ('MAGNEZONE', 72, 74))
MONTANHA_TEMPESTADE = land(25, ('ZEBSTRIKA', 68, 70), ('GALVANTULA', 68, 70), ('EMOLGA', 68, 70), ('EELEKTROSS', 70, 72), ('LUXRAY', 70, 72),
                           ('ELECTIVIRE', 70, 72), ('MAGNEZONE', 70, 72), ('BRAVIARY', 70, 72), ('ROTOM', 72, 74), ('JOLTEON', 72, 74),
                           ('AMPHAROS', 74, 76), ('RAICHU', 74, 76))
# dia de tempestade (pos-jogo): tabela seguinte do mesmo mapa; src/wild_encounter.c troca quando VAR_ABUNDANCE_STORM == 1
TEMPESTADE = {
    'MAP_THUNDER_RIDGE': dict(land_mons=MONTANHA_TEMPESTADE),
    'MAP_ABUNDANCE_ISLE_GALE_SHORE': dict(land_mons=VENTO_TEMPESTADE,
                                         water_mons=five(6, ('PELIPPER', 68, 70), ('SWANNA', 68, 72), ('LANTURN', 68, 72), ('MANTINE', 70, 74), ('LAPRAS', 72, 76)),
                                         fishing_mons=PESCA_MAR),
}

ENC = {
    'MAP_ABUNDANCE_ISLE': dict(land_mons=FAZENDA, water_mons=MAR, fishing_mons=PESCA_MAR),
    'MAP_ABUNDANCE_ISLE_HARVEST_FIELDS': dict(land_mons=CAMPO, water_mons=MAR, fishing_mons=PESCA_MAR),
    'MAP_THUNDER_RIDGE': dict(land_mons=MONTANHA),
    'MAP_ABUNDANCE_ISLE_WINDSWEPT_CAPE': dict(water_mons=MAR, fishing_mons=PESCA_MAR),
    'MAP_ABUNDANCE_ISLE_GALE_SHORE': dict(land_mons=VENTO, water_mons=five(4, ('PELIPPER', 66, 70), ('TENTACRUEL', 66, 70), ('SWANNA', 68, 72),
                                                         ('WAILORD', 70, 74), ('LAPRAS', 72, 76)), fishing_mons=PESCA_MAR),
    'MAP_ABUNDANCE_ISLE_SPRING_GROVE': dict(
        land_mons=land(8, ('PANPOUR', 66, 68), ('PETILIL', 66, 68), ('COTTONEE', 66, 68), ('SAWSBUCK', 68, 70), ('LILLIGANT', 68, 70),
                       ('WHIMSICOTT', 68, 70), ('FLOETTE', 68, 70), ('SHELMET', 66, 68), ('PANSAGE', 66, 68), ('COMFEY', 70, 72),
                       ('FLORGES', 72, 74), ('TOGETIC', 72, 74)),   # Togetic: o Togepi so vinha do Gachapon
        water_mons=LAGO, fishing_mons=PESCA_LAGO),
    'MAP_ABUNDANCE_ISLE_GALE_CAVE': dict(
        land_mons=land(10, ('WOOBAT', 66, 68), ('BOLDORE', 66, 68), ('SWOOBAT', 68, 70), ('DRILBUR', 66, 68), ('CRUSTLE', 68, 70),
                       ('DURANT', 66, 68), ('EXCADRILL', 70, 72), ('GIGALITH', 70, 72), ('NOIBAT', 68, 70), ('CROBAT', 70, 72),
                       ('NOIVERN', 72, 74), ('ARCHEOPS', 72, 74)),
        water_mons=MAR, fishing_mons=PESCA_MAR,
        rock_smash_mons=five(20, ('ROGGENROLA', 60, 66), ('BOLDORE', 66, 70), ('DWEBBLE', 60, 66), ('CRUSTLE', 66, 70), ('GIGALITH', 70, 74))),
    'MAP_FROSTFALL_CRATER_1F': dict(land_mons=GELO_A),
    'MAP_FROSTFALL_CRATER_B1F': dict(land_mons=GELO_A),
    'MAP_FROSTFALL_CRATER_LAB': dict(land_mons=GELO_B),
    'MAP_FROSTFALL_CRATER_CORE': dict(land_mons=GELO_B),
    'MAP_THUNDERSPIRE_1F': dict(land_mons=TORRE),
    'MAP_THUNDERSPIRE_2F': dict(land_mons=TORRE),
    'MAP_THUNDERSPIRE_3F': dict(land_mons=TORRE_ALTA),
    'MAP_ABUNDANCE_ISLE_SUNSET_STRAIT': dict(
        water_mons=five(4, ('JELLICENT', 66, 70), ('TENTACRUEL', 66, 70), ('WAILORD', 68, 72), ('MANTINE', 70, 74), ('LAPRAS', 72, 76)),
        fishing_mons=PESCA_MAR),
    'MAP_ABUNDANCE_ISLE_SUNSET_STRAIT_UNDERWATER': dict(
        water_mons=five(4, ('HUNTAIL', 66, 70), ('GOREBYSS', 66, 70), ('LANTURN', 68, 72), ('ALOMOMOLA', 70, 74), ('RELICANTH', 72, 76))),
    'MAP_SUNKEN_TRUTH_SHIP': dict(
        land_mons=land(10, ('FRILLISH', 66, 68), ('SABLEYE', 66, 68), ('DRIFBLIM', 68, 70), ('BANETTE', 68, 70), ('JELLICENT', 68, 70),
                       ('GOLURK', 68, 70), ('COFAGRIGUS', 70, 72), ('DHELMISE', 70, 72), ('CARRACOSTA', 70, 72), ('ARCHEOPS', 70, 72),
                       ('GIMMIGHOUL_ROAMING', 70, 72), ('CHANDELURE', 74, 76))),   # Gimmighoul Roaming: so vinha do Gachapon
    # sala de maquinas do Frigate (chao de caverna): taxa baixa; Porygon2 da o Porygon (so vinha do Gachapon/Game Corner)
    'MAP_PLASMA_FRIGATE_ENGINE_ROOM': dict(
        land_mons=land(5, ('KLANG', 66, 68), ('MAGNETON', 66, 68), ('ELGYEM', 66, 68), ('KLINKLANG', 68, 70), ('BEHEEYEM', 68, 70),
                       ('MAGNEZONE', 68, 70), ('ROTOM', 68, 70), ('PORYGON2', 68, 70), ('KLINK', 66, 68), ('BEHEEYEM', 70, 72),
                       ('PORYGON2', 72, 74), ('PORYGON_Z', 74, 76))),
    'MAP_EMBERDUNE_ISLE': dict(
        land_mons=land(20, ('KROKOROK', 66, 68), ('SCRAGGY', 66, 68), ('HEATMOR', 66, 68), ('MARACTUS', 68, 70), ('SIGILYPH', 68, 70),
                       ('DARMANITAN', 68, 70), ('KROOKODILE', 70, 72), ('SCRAFTY', 70, 72), ('CRUSTLE', 70, 72), ('HIPPOWDON', 70, 72),
                       ('LARVESTA', 66, 66), ('SANDACONDA', 74, 76)),
        water_mons=MAR, fishing_mons=PESCA_MAR),
}


def main():
    t = json.load(open(P))
    g = next(x for x in t['wild_encounter_groups'] if x['label'] == 'gWildMonHeaders')
    g['encounters'] = [e for e in g['encounters'] if e['map'] not in ENC]
    for mp, fields in ENC.items():
        label = 'g' + ''.join(w.capitalize() for w in mp[4:].split('_'))
        g['encounters'].append(dict(map=mp, base_label=label, **fields))
        if mp in TEMPESTADE:   # tem que vir logo depois da calma (o C soma 1 ao indice)
            g['encounters'].append(dict(map=mp, base_label=label + 'Storm', **TEMPESTADE[mp]))
    open(P, 'w').write(json.dumps(t, indent=2) + '\n')
    print('selvagens:', len(ENC), 'mapas')


if __name__ == '__main__':
    main()
