import sys; sys.path.insert(0, sys.argv[1])
from grids import MAPS
from collections import deque
WALK=set('.SHLEXiVPCDNg')
starts={'room1':[(11,18),(19,2)],'room2':[(1,15),(22,8)],'room3':[(1,9),(14,6)],'room4':[(11,22),(13,8)],'ext':[(9,37),(10,5)]}
for k,g in MAPS.items():
    W=len(g[0]); bad=[i for i,r in enumerate(g) if len(r)!=W]
    print('==',k,W,'x',len(g),'linhas erradas',bad)
    if bad: continue
    walk=[(x,y) for y in range(len(g)) for x in range(W) if g[y][x] in WALK]
    if not walk: continue
    st=starts.get(k) or [walk[0]]
    seen={st[0]}; q=deque([st[0]])
    while q:
        x,y=q.popleft()
        for dx,dy in ((1,0),(-1,0),(0,1),(0,-1)):
            n=(x+dx,y+dy)
            if 0<=n[0]<W and 0<=n[1]<len(g) and g[n[1]][n[0]] in WALK and n not in seen:
                seen.add(n); q.append(n)
    for s_ in st: print('  alvo',s_,repr(g[s_[1]][s_[0]]),'alcancavel' if s_ in seen else 'NAO ALCANCAVEL')
    isl=[c for c in walk if c not in seen]
    print('  celulas andaveis ilhadas:',len(isl), isl[:30])
