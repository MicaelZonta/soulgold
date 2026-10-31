"""Simula um andar de portoes por script (para-raios da Thunderspire 3F) levando em conta ONDE o jogador esta:
estado = (posicao, portoes abertos). Rodar da raiz do repo; RODS em JSON por argv para outro andar.
Alcance a partir so dos warps (sem a posicao) da resposta errada: o jogador fica preso do lado do portao que fechou."""
import sys,collections,json,struct
sys.path.insert(0, __import__('os').path.dirname(__file__))
from alcance import grid
n='Thunderspire_3F'; j,w,h,b=grid(n)
G={'A':(6,16),'B':(14,12),'C':(20,9),'D':(17,6)}
RODS=json.loads(sys.argv[1]) if len(sys.argv)>1 else {'E':[[4,20],'A'],'W':[[3,6],'AB'],'T':[[26,13],'BC'],'I':[[26,5],'CD']}
objs={(o['x'],o['y']) for o in j['object_events'] if o['graphics_id']!='OBJ_EVENT_GFX_ITEM_BALL'}
def comp(start,op):
    opn={G[g] for g in op}
    ok=lambda x,y:0<=x<w and 0<=y<h and ((x,y) in opn or not(b[y*w+x]>>11&1)) and (x,y) not in objs
    el=lambda x,y:b[y*w+x]>>12
    s={start}; q=collections.deque(s)
    while q:
        x,y=q.popleft()
        for dx,dy in((1,0),(-1,0),(0,1),(0,-1)):
            p=(x+dx,y+dy)
            if p in s or not ok(*p): continue
            a,c=el(x,y),el(*p)
            if a==c or a in(0,15) or c in(0,15): s.add(p);q.append(p)
    return s
start=((26,22),frozenset()); seen={start}; q=collections.deque([(start,[])])
while q:
    (p,st),path=q.popleft(); r=comp(p,st)
    if (17,6) in r: print('SOLUCAO',len(path),path); break
    for nm,((rx,ry),gs) in RODS.items():
        adj=[(rx+dx,ry+dy) for dx,dy in((0,1),(0,-1),(1,0),(-1,0)) if (rx+dx,ry+dy) in r]
        if adj:
            ns=(adj[0],frozenset(set(st)^set(gs)))
            if ns not in seen: seen.add(ns); q.append((ns,path+[nm]))
else: print('SEM SOLUCAO', len(seen))
