"""BFS de alcance por mapa instalado (colisao + elevacao; objetos bloqueiam). reach(nome, extra_open) e grid(nome)."""
import json,struct,collections,re,sys
def grid(name):
    j=json.load(open(f'data/maps/{name}/map.json'))
    L=[l for l in json.load(open('data/layouts/layouts.json'))['layouts'] if l.get('id')==j['layout']][0]
    w,h=L['width'],L['height']; raw=open(L['blockdata_filepath'],'rb').read()
    return j,w,h,[struct.unpack_from('<H',raw,k*2)[0] for k in range(w*h)]
def reach(name, extra_open=()):
    j,w,h,b=grid(name)
    objs={(o['x'],o['y']) for o in j['object_events'] if o['graphics_id']!='OBJ_EVENT_GFX_ITEM_BALL'}
    def ok(x,y): return 0<=x<w and 0<=y<h and ((x,y) in extra_open or not(b[y*w+x]>>11&1)) and (x,y) not in objs
    def el(x,y): return b[y*w+x]>>12
    seen=set(); q=collections.deque()
    for wp in j['warp_events']:
        p=(wp['x'],wp['y'])
        if 0<=p[0]<w and 0<=p[1]<h: seen.add(p); q.append(p)
    while q:
        x,y=q.popleft()
        for dx,dy in((1,0),(-1,0),(0,1),(0,-1)):
            p=(x+dx,y+dy)
            if p in seen or not ok(*p): continue
            a,c=el(x,y),el(*p)
            if a==c or a in(0,15) or c in(0,15): seen.add(p); q.append(p)
    return seen
if __name__=='__main__':
    ex=json.load(open('.claude/abundance_isle/instalar/extras.json'))['extras']
    MAPS=dict(re.findall(r"'(\w+)':\s*\('(\w+)',\s*'MAPSEC",open('.claude/abundance_isle/instalar/maps.py').read()))
    for d,e in ex.items():
        name=MAPS[d]; s=reach(name)
        for bg in e['bg']:
            t=(bg['x'],bg['y']+1) if bg['type']=='sign' else (bg['x'],bg['y'])
            if t not in s: print('NAO',name,bg.get('script',bg.get('item')),bg['x'],bg['y'])
        for o in e['objects']:
            if not any((o['x']+dx,o['y']+dy) in s for dx,dy in((1,0),(-1,0),(0,1),(0,-1))): print('NAO',name,o['local_id'])
    print('fim')
