#!/usr/bin/env python3
"""Liga os treinadores de Johto ao telefone (Match Call GSC).

Para cada treinador da agenda, costura no script do NOSSO mapa o que o pokehns
tem no dele: o quarto argumento do `trainerbattle_*` (o script que pede o
numero), a checagem de revanche, o item guardado e os textos novos. Os rotulos
dos dois lados sao os mesmos (nosso Johto e o deles tem a mesma origem), entao a
costura e por rotulo, nao por copia do arquivo inteiro.

Os treinadores de Kanto e das Routes 26/27 nao estao aqui: aqueles mapas vieram
do HnS inteiros, ja com o telefone ligado.

Uso:
    python3 dev_scripts/importa_match_call_scripts.py --conferir
    python3 dev_scripts/importa_match_call_scripts.py --aplicar
"""
import argparse
import os
import re
import sys

DUMP = '.filetransfer/pokehns-expansion-Release-v2.0.6/data/maps'

# (nome, mapa nosso, pasta no dump, flag do item, var do item)
TREINADORES = [
    ('Joey',    'Route30',                'Route30_hns',                None, None),
    ('Wade',    'Route31',                'Route31_hns',                'FLAG_WADE_HAS_PHONE_ITEM',    'VAR_WADE_PHONE_ITEM'),
    ('Ralph',   'Route32',                'Route32_hns',                None, None),
    ('Liz',     'Route32',                'Route32_hns',                None, None),
    ('Anthony', 'Route33',                'Route33_hns',                None, None),
    ('Todd',    'Route34',                'Route34_hns',                None, None),
    ('Gina',    'Route34',                'Route34_hns',                None, None),
    ('Irwin',   'Route35',                'Route35_hns',                None, None),
    ('Arnie',   'Route35',                'Route35_hns',                None, None),
    ('Alan',    'Route36',                'Route36_hns',                'FLAG_ALAN_HAS_PHONE_ITEM',    'VAR_ALAN_PHONE_ITEM'),
    ('Dana',    'Route38',                'Route38_hns',                'FLAG_DANA_HAS_PHONE_ITEM',    'VAR_DANA_PHONE_ITEM'),
    ('Chad',    'Route38',                'Route38_hns',                None, None),
    ('Derek',   'Route39',                'Route39_hns',                'FLAG_DEREK_HAS_PHONE_ITEM',   'VAR_DEREK_PHONE_ITEM'),
    ('Tully',   'Route42',                'Route42_hns',                'FLAG_TULLY_HAS_PHONE_ITEM',   'VAR_TULLY_PHONE_ITEM'),
    ('Brent',   'Route43',                'Route43_hns',                None, None),
    ('Tiffany', 'Route43',                'Route43_hns',                None, None),
    ('Vance',   'Route44',                'Route44_hns',                None, None),
    ('Wilton',  'Route44',                'Route44_hns',                'FLAG_WILTON_HAS_PHONE_ITEM',  'VAR_WILTON_PHONE_ITEM'),
    ('Kenji',   'Route45',                'Route45_hns',                'FLAG_KENJI_HAS_PHONE_ITEM',   'VAR_KENJI_PHONE_ITEM'),
    ('Parry',   'Route45',                'Route45_hns',                None, None),
    ('Erin',    'Route46',                'Route46_hns',                None, None),
    ('Jack',    'NationalPark_Normal',    'NationalPark_Normal_hns',    None, None),
    ('Beverly', 'NationalPark_Normal',    'NationalPark_Normal_hns',    'FLAG_BEVERLY_HAS_PHONE_ITEM', 'VAR_BEVERLY_PHONE_ITEM'),
    ('Huey',    'OlivineCity_Lighthouse', 'OlivineCity_Lighthouse_hns', None, None),
]

FLAG_HNS = re.compile(r'FLAG_(\w+)_HAS_ITEM_HNS')
VAR_HNS = re.compile(r'VAR_(\w+)_ITEM_HNS')


def converte(txt):
    """Nomes do HnS -> nossos."""
    txt = FLAG_HNS.sub(lambda m: 'FLAG_%s_HAS_PHONE_ITEM' % m.group(1), txt)
    txt = VAR_HNS.sub(lambda m: 'VAR_%s_PHONE_ITEM' % m.group(1), txt)
    txt = re.sub(r'(TRAINER_\w+?)_HNS\b', r'\1', txt)
    return txt


def nosso_arquivo(mapa):
    pory = f'data/maps/{mapa}/scripts.pory'
    return pory if os.path.exists(pory) else f'data/maps/{mapa}/scripts.inc'


def bloco_script(txt, rotulo):
    """Do '<rotulo>::' ate o 'end'/'return' que fecha."""
    m = re.search(r'^%s::\s*$' % re.escape(rotulo), txt, re.M)
    if not m:
        return None
    linhas = txt[m.start():].split('\n')
    out = [linhas[0]]
    for l in linhas[1:]:
        out.append(l)
        if l.strip() in ('end', 'return'):
            break
    return '\n'.join(out)


def bloco_texto(txt, rotulo):
    """Do '<rotulo>:' ate a .string que termina em $."""
    m = re.search(r'^%s:\s*$' % re.escape(rotulo), txt, re.M)
    if not m:
        return None
    linhas = txt[m.start():].split('\n')
    out = [linhas[0]]
    for l in linhas[1:]:
        out.append(l)
        if l.rstrip().endswith('$"'):
            break
    return '\n'.join(out)


def main():
    ap = argparse.ArgumentParser()
    g = ap.add_mutually_exclusive_group(required=True)
    g.add_argument('--conferir', action='store_true')
    g.add_argument('--aplicar', action='store_true')
    a = ap.parse_args()

    # agrupa por arquivo nosso, porque dois treinadores dividem mapa
    por_arquivo = {}
    for nome, mapa, pasta, flag, var in TREINADORES:
        por_arquivo.setdefault(nosso_arquivo(mapa), []).append((nome, mapa, pasta, flag, var))

    total = 0
    for arq, lista in sorted(por_arquivo.items()):
        texto = open(arq, encoding='utf-8').read()
        novos = []          # blocos de script/texto a acrescentar
        for nome, mapa, pasta, flag, var in lista:
            hns = open(f'{DUMP}/{pasta}/scripts.inc', encoding='utf-8').read()
            ALVO = nome.upper()

            # 1) a linha do trainerbattle no HnS, com o 4o argumento
            m_hns = re.search(
                r'^\t(trainerbattle_\w+) TRAINER_%s_HNS,([^\n]*)$' % ALVO, hns, re.M)
            if not m_hns:
                print(f'!! {nome}: sem trainerbattle no dump'); continue
            args_hns = [x.strip() for x in m_hns.group(2).split(',')]
            if len(args_hns) < 3:
                print(f'!! {nome}: trainerbattle do dump sem script de registro'); continue
            registro = args_hns[2]

            # 2) o resto do bloco dele (checagens de item/revanche)
            ini = hns.index(m_hns.group(0))
            resto = hns[ini + len(m_hns.group(0)):].split('\n')
            meio = []
            for l in resto[1:]:
                if l.strip() in ('end', 'return'):
                    break
                if l.strip().startswith('msgbox'):
                    break
                meio.append(l)

            # 3) a nossa linha (3 argumentos) ganha o 4o + as checagens
            # alguns dos nossos escrevem sem a virgula depois do treinador
            # (o GAS aceita espaco como separador de argumento de macro)
            m_nosso = re.search(
                r'^\t(trainerbattle_\w+) TRAINER_%s[ ,]+([^\n]*)$' % ALVO, texto, re.M)
            if not m_nosso:
                print(f'!! {nome}: sem trainerbattle em {arq}'); continue
            args_nossos = [x.strip() for x in m_nosso.group(2).split(',')]
            if len(args_nossos) >= 3:
                print(f'== {nome}: ja tem script de registro, pulando')
                continue
            nova_linha = '\t%s TRAINER_%s, %s, %s' % (
                m_nosso.group(1), ALVO, ', '.join(args_nossos), registro)
            if meio:
                nova_linha += '\n' + converte('\n'.join(meio))
            texto = texto.replace(m_nosso.group(0), nova_linha, 1)

            # 4) blocos de script novos + textos que eles usam
            rotulos = [registro]
            for l in meio:
                rotulos += re.findall(r'(\w+_EventScript_\w+)', l)
            vistos = set()
            while rotulos:
                rot = rotulos.pop(0)
                if rot in vistos:
                    continue
                vistos.add(rot)
                if re.search(r'^%s::' % re.escape(rot), texto, re.M):
                    continue
                b = bloco_script(hns, rot)
                if b is None:
                    print(f'!! {nome}: bloco {rot} nao achado no dump'); continue
                novos.append(converte(b))
                rotulos += re.findall(r'(\w+_EventScript_\w+)', b)
                for t in re.findall(r'(\w+_Text_\w+)', b):
                    if re.search(r'^%s:' % re.escape(t), texto, re.M):
                        continue
                    bt = bloco_texto(hns, t)
                    if bt is None:
                        print(f'!! {nome}: texto {t} nao achado no dump'); continue
                    novos.append(converte(bt))
            total += 1

        if not novos:
            continue
        # insere antes do fim do bloco raw (no .pory) ou no fim do arquivo (.inc)
        corpo = '\n' + '\n\n'.join(novos) + '\n'
        if arq.endswith('.pory'):
            linhas = texto.split('\n')
            fim = next(i for i, l in enumerate(linhas) if l.strip() == '`')
            linhas.insert(fim, corpo)
            texto = '\n'.join(linhas)
        else:
            texto = texto.rstrip('\n') + '\n' + corpo

        if a.aplicar:
            open(arq, 'w', encoding='utf-8').write(texto)
            print(f'{arq}: {len(novos)} blocos')
        else:
            print(f'--- {arq}: {len(novos)} blocos a acrescentar')
            for b in novos:
                print(b.split('\n')[0])
    print(f'{total} treinadores ligados')


if __name__ == '__main__':
    main()
