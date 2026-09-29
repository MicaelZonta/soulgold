#!/usr/bin/env python3
"""Familias sem fonte "de verdade" no mundo (principio do autor, 29/09/2026).

Le os dados do site (docs/data/species-details, gerados por
tools/soulgold_docs/build_docs.py) e lista as familias de evolucao que so saem
por fontes de sistema: Nexus, Gachapon, recompensa de trofeu (Route 40),
Battle Cafe, Game Corner, Odd Egg. Troca de forma (tosa da Mom, item) nao conta
nem para um lado nem para o outro: herda a fonte da forma base.

Regenere o site antes para a lista refletir o jogo atual:
    ~/.venvs/soulgold-docs/bin/python tools/soulgold_docs/build_docs.py
    python3 dev_scripts/fontes_legitimas.py

Limitacao conhecida: o parser do site nao le a escolha do inicial no Elm, entao
os iniciais de Johto aparecem como "so Gachapon" (um deles tem fonte real).
"""
import json,glob,os,collections,re
det={}; const2slug={}
sp=json.load(open('docs/data/species.json'))
rows=sp if isinstance(sp,list) else sp.get('species',sp)
for r in rows:
    if isinstance(r,dict) and 'constant' in r and 'slug' in r: const2slug[r['constant']]=r['slug']
for f in glob.glob('docs/data/species-details/*.json'):
    det[os.path.basename(f)[:-5]]=json.load(open(f))
slug2const={v:k for k,v in const2slug.items()}
def cat(l):
    n=l['name']; m=l['method']
    if any(k in n for k in ('Nexus','Gachapon','Achievement','Battle Cafe','Game Corner')) or 'Odd Egg' in m: return 'meta'
    if m.startswith(("Mom's","Use ","Hold ","Fuse ","Bring Rotom","Form change")) or '(random form)' in m: return 'form'
    return 'legit'
# union-find by evolutions
parent={}
def find(x):
    parent.setdefault(x,x)
    while parent[x]!=x: parent[x]=parent[parent[x]]; x=parent[x]
    return x
def union(a,b): parent[find(a)]=find(b)
for s,d in det.items():
    find(s)
    for e in d.get('evolutions') or []:
        t=const2slug.get(e.get('target'))
        if t in det: union(s,t)
fam=collections.defaultdict(list)
for s in det: fam[find(s)].append(s)
battle=re.compile(r'-(mega|gmax|primal|totem|busted|zen|school|blade|pirouette|complete|crowned|eternamax|ultra|hangry|noice|stellar|terastal|mega-[xyz]|mega-z)|-tera$')
res=collections.defaultdict(list)
for root,members in fam.items():
    members=[m for m in members if not battle.search(m)]
    if not members: continue
    cats=collections.defaultdict(set)
    for m in members:
        for l in det[m]['locations']:
            c=cat(l); cats[c].add(l['name'].split(' (')[0] if c=='meta' else l['method'])
    if cats['legit']: continue
    name=sorted(members,key=len)[0]
    if cats['meta']: res[' + '.join(sorted(cats['meta']))].append(name)
    elif not cats['form']: res['NENHUMA'].append(name)
for k,v in sorted(res.items(), key=lambda x:-len(x[1])):
    print(f'## {k} ({len(v)})'); print(', '.join(sorted(v)))
