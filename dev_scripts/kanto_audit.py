"""Varredura estatica de Kanto: para cada mapa com prefixo de Kanto lista
estado (alcancavel / INALCANCAVEL / fora da ROM), tilesets e se os assets
existem, estatisticas do map.bin, conexoes, warps, objetos, treinadores,
tamanho do script e quais tabelas de encontro selvagem existem.

Roda na raiz do repo:  python3 dev_scripts/kanto_audit.py
Escreve kanto_rows.json ao lado (dados brutos) e imprime a tabela.
Base do docs/KANTO_AUDITORIA.md.
"""
import json,re,os,collections,struct
root='.'
groups=json.load(open('data/maps/map_groups.json'))
excluded=set(groups['rom_excluded_groups'])
inrom={}
for g in groups['group_order']:
    for m in groups[g]: inrom[m]=(g not in excluded, g)
layouts={l['id']:l for l in json.load(open('data/layouts/layouts.json'))['layouts']}
unreach=set(l.strip() for l in open('docs/MAPAS_INALCANCAVEIS.txt') if l.strip() and not l.startswith('#'))
# wild encounters
we=json.load(open('src/data/wild_encounters.json'))
wild={}
for g in we['wild_encounter_groups']:
    for e in g['encounters']:
        if 'map' in e:
            kinds=[k for k in ('land_mons','water_mons','rock_smash_mons','fishing_mons') if k in e]
            wild.setdefault(e['map'],set()).update(kinds)
kanto_prefix=re.compile(r'^(PalletTown|ViridianCity|ViridianForest|PewterCity|CeruleanCity|CeruleanCave|VermilionCity|LavenderTown|CeladonCity|SaffronCity|Saffron_Temp|FuchsiaCity|CinnabarIsland|IndigoPlateau|Route([1-9]|1[0-9]|2[0-8])(_|$)|MtMoon|RockTunnel|DiglettsCave|PowerPlant|SeafoamIslands|VictoryRoadKanto|TohjoFalls|MtSilver|SafariZone(?!Gate))')
def tileset_assets(name):
    # name like gTileset_KantoGeneral -> folder
    s=re.sub(r'^gTileset_','',name)
    folder=re.sub(r'(?<!^)(?=[A-Z0-9])','_',s).lower()
    folder=re.sub(r'_+','_',folder)
    for base in ('data/tilesets/primary','data/tilesets/secondary'):
        p=os.path.join(base,folder)
        if os.path.isdir(p):
            ok=all(os.path.exists(os.path.join(p,f)) for f in ('tiles.png','metatiles.bin','metatile_attributes.bin'))
            pals=len([f for f in os.listdir(os.path.join(p,'palettes'))]) if os.path.isdir(os.path.join(p,'palettes')) else 0
            return folder,ok,pals
    return folder,None,0
def mapbin_stats(path):
    if not os.path.exists(path): return None
    b=open(path,'rb').read()
    n=len(b)//2
    vals=struct.unpack('<%dH'%n,b)
    mts=collections.Counter(v&0x3ff for v in vals)
    return n,len(mts),mts.most_common(1)[0][1]/n if n else 0
rows=[]
for m in sorted(os.listdir('data/maps')):
    if not kanto_prefix.match(m): continue
    mp=f'data/maps/{m}/map.json'
    if not os.path.exists(mp): continue
    mj=json.load(open(mp))
    rom,grp=inrom.get(m,(None,'(sem grupo)'))
    lay=layouts.get(mj['layout'],{})
    prim=lay.get('primary_tileset',''); sec=lay.get('secondary_tileset','')
    pa=tileset_assets(prim) if prim else ('',None,0); sa=tileset_assets(sec) if sec else ('',None,0)
    mb=mapbin_stats(lay.get('blockdata_filepath','')) if lay else None
    scr=f'data/maps/{m}/scripts.inc'; pory=f'data/maps/{m}/scripts.pory'
    sfile=pory if os.path.exists(pory) else scr
    stxt=open(sfile).read() if os.path.exists(sfile) else ''
    slines=len(stxt.splitlines())
    ntext=len(re.findall(r'^\s*\.string ',stxt,re.M))+len(re.findall(r'^\s*text\s+\w+\s*\{|^\s*msgbox\(',stxt,re.M))
    trainers=len(re.findall(r'trainerbattle',stxt))
    todo=len(re.findall(r'TODO|placeholder|PLACEHOLDER|WIP|dummy',stxt,re.I))
    objs=mj.get('object_events',[]); trn=sum(1 for o in objs if o.get('trainer_type','TRAINER_TYPE_NONE')!='TRAINER_TYPE_NONE')
    state='fora da ROM' if rom is False else ('sem grupo' if rom is None else ('INALCANCAVEL' if m in unreach else 'alcancavel'))
    rows.append(dict(map=m,group=grp,state=state,mapsec=mj.get('region_map_section',''),layout=mj['layout'],
        w=lay.get('width'),h=lay.get('height'),prim=pa[0],prim_ok=pa[1],sec=sa[0],sec_ok=sa[1],
        mapbin=mb,conn=len(mj.get('connections') or []),warps=len(mj.get('warp_events',[])),objs=len(objs),trainers_obj=trn,
        coords=len(mj.get('coord_events',[])),bg=len(mj.get('bg_events',[])),script_lines=slines,texts=ntext,trainerbattle=trainers,todo=todo,
        wild=','.join(sorted(k.replace('_mons','') for k in wild.get('MAP_'+re.sub(r'(?<!^)(?=[A-Z])','_',m).upper().replace('__','_'),()))),
        weather=mj.get('weather'),music=mj.get('music'),battle_scene=mj.get('battle_scene'),map_type=mj.get('map_type'),show_name=mj.get('show_map_name')))
json.dump(rows,open('dev_scripts/kanto_rows.json','w'),indent=1)
print(len(rows),'mapas Kanto')
import itertools
print(f"{'map':40} {'state':12} {'tam':8} {'prim':16} {'sec':24} {'mbin':14} {'con':>3} {'wrp':>3} {'obj':>3} {'trn':>3} {'scr':>5} {'txt':>4} {'tb':>3} {'wild':12}")
for r in rows:
    mb=r['mapbin']; mbs=f"{mb[1]}mt/{mb[2]:.0%}" if mb else '---'
    print(f"{r['map']:40} {r['state']:12} {str(r['w'])+'x'+str(r['h']):8} {r['prim'][:16]:16} {r['sec'][:24]:24} {mbs:14} {r['conn']:3} {r['warps']:3} {r['objs']:3} {r['trainers_obj']:3} {r['script_lines']:5} {r['texts']:4} {r['trainerbattle']:3} {r['wild']:12}")
