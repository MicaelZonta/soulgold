import os
import json, glob, os, html, re
os.chdir(os.path.dirname(os.path.abspath(__file__)))
css = open('m20/_css.css').read() + """
.region{border:1px solid var(--rule);border-radius:4px;overflow:auto;max-height:640px;background:#3f78d8}
.region img{display:block;width:100%;min-width:900px}
.graph{background:var(--surface);border:1px solid var(--rule);border-radius:4px;padding:8px}
.graph svg{width:100%;height:auto;display:block}
.graph a text{fill:var(--ink);font:600 12px var(--body)}
.graph a:hover rect{stroke:var(--moon);stroke-width:2}
.cards{display:flex;flex-direction:column;gap:34px}
.card{display:grid;grid-template-columns:minmax(0,1.25fr) minmax(0,1fr);gap:22px;align-items:start;scroll-margin-top:20px}
.card .stage img{width:100%}
.card h3{font-family:var(--display);font-size:1.25rem}
.card .meta{font-family:var(--mono);font-size:.78rem;color:var(--muted)}
ul.fun{margin:0;padding-left:1.1em;display:flex;flex-direction:column;gap:5px;font-size:.95rem}
details{background:var(--surface);border:1px solid var(--rule);border-radius:4px;padding:6px 10px}
details summary{cursor:pointer;font-weight:600;font-size:.9rem}
.props{display:grid;grid-template-columns:repeat(4,minmax(0,1fr));gap:14px}
.props figure{margin:0;background:var(--surface);border:1px solid var(--rule);border-radius:4px;padding:10px;display:flex;flex-direction:column;gap:8px}
.props img{width:100%;border-radius:3px}.props .art{background:#e8e8ec;padding:8px;border-radius:3px}
.props figcaption{font-size:.9rem;line-height:1.4}.props figcaption b{display:block;font-family:var(--display);font-size:1.05rem}
.acts{display:flex;flex-direction:column;gap:14px}.acts div{border-left:3px solid var(--moon);padding-left:14px}
.acts h3{font-family:var(--display)}.quote{font-style:italic;color:var(--muted)}
.maplink{font:600 .78rem var(--mono);background:var(--moon-soft);color:var(--moon);padding:1px 6px;border-radius:999px;text-decoration:none;white-space:nowrap}
@media (max-width:760px){.card{grid-template-columns:1fr}.props{grid-template-columns:repeat(2,minmax(0,1fr))}}
"""
I = {os.path.dirname(f)[4:]: json.load(open(f)) for f in glob.glob('m20/*/info.json')}
ORDER = ['AbundanceIsle', 'AbundanceIsle_Barn', 'AbundanceIsle_Farmhouse', 'AbundanceIsle_HarvestFields', 'AbundanceIsle_KeeperHouse',
         'AbundanceIsle_SpringGrove', 'AbundanceIsle_WindsweptCape', 'AbundanceIsle_PokemonCenter', 'PLASMA_FRIGATE_DECK', 'PLASMA_FRIGATE_HOLD',
         'FROSTFALL_CRATER_1F', 'FROSTFALL_CRATER_B1F', 'FROSTFALL_CRATER_LAB', 'FROSTFALL_CRATER_CORE',
         'AbundanceIsle_GaleCave', 'AbundanceIsle_GaleShore', 'THUNDER_RIDGE', 'THUNDERSPIRE_1F', 'THUNDERSPIRE_2F', 'ThunderspireSummit']
EXTRA = {'AbundanceIsle_SkylaHangar': 'AbundanceIsle_PokemonCenter', 'AbundanceIsle_ElderHouse': 'AbundanceIsle_SkylaHangar',
         'PLASMA_FRIGATE_CABINS': 'PLASMA_FRIGATE_HOLD', 'PLASMA_FRIGATE_ENGINE_ROOM': 'PLASMA_FRIGATE_CABINS',
         'ABUNDANCE_ISLE_SUNSET_STRAIT': 'ThunderspireSummit', 'EMBERDUNE_ISLE': 'ABUNDANCE_ISLE_SUNSET_STRAIT',
         'TRUTHSAND_RUINS_1F': 'EMBERDUNE_ISLE', 'TRUTHSAND_RUINS_B1F': 'TRUTHSAND_RUINS_1F',
         'TRUTHSAND_RUINS_HALL_OF_TRUTH': 'TRUTHSAND_RUINS_B1F', 'SHRINE_OF_THE_FIRST_DRAGON': 'TRUTHSAND_RUINS_HALL_OF_TRUTH'}
for k, after in EXTRA.items():
    if k in I and after in ORDER: ORDER.insert(ORDER.index(after) + 1, k)
ACT6 = [('SUNSET', (1.5, 8.6)), ('EMBERDUNE', (1.5, 9.8)), ('RUINS_1F', (3.0, 9.8)), ('RUINS_B1F', (4.5, 9.8)), ('HALL', (5.6, 9.8)), ('SHRINE', (3.0, 8.6))]
ACT6POS = {}
for kw, pos in ACT6:
    for d in sorted(I):
        if d not in ORDER and kw in d.upper().replace('ABUNDANCEISLE_', '').replace('TRUTHSANDRUINS', 'TRUTHSAND_RUINS'):
            ORDER.append(d); ACT6POS[d] = pos
EXTRA2 = [('THUNDERSPIRE_3F', 'THUNDERSPIRE_2F', (0.6, -0.4)), ('SUNKEN', None, (0.4, 9.2)), ('NROOM', None, (0.4, 10.4)),
          ('NS_ROOM', None, (0.4, 10.4)), ('N_ROOM', None, (0.4, 10.4)), ('FESTIVAL', 'AbundanceIsle_WindsweptCape', (5.6, 3.6))]
for kw, after, pos in EXTRA2:
    for d in sorted(I):
        if d not in ORDER and kw in d.upper().replace('ABUNDANCEISLE_', '').replace('EMBERDUNEISLE_', ''):
            if after and after in ORDER: ORDER.insert(ORDER.index(after) + 1, d)
            else: ORDER.append(d)
            ACT6POS[d] = pos
for d in sorted(I):
    if d not in ORDER: ORDER.append(d); ACT6POS[d] = (5.6, 8.6)
for d in ORDER:
    u = d.upper()
    if 'UNDERWATER' in u: ACT6POS[d] = (0.2, 7.6)
    elif 'SUNKEN' in u: ACT6POS[d] = (0.2, 8.6)
    elif 'NSROOM' in u: ACT6POS[d] = (0.2, 9.8)
    elif 'FESTIVAL' in u: ACT6POS[d] = (5.6, 3.6)
missing = set(I) ^ set(ORDER); assert not missing, missing
NMAPS = len(ORDER)
def const(d):
    m = I[d]['map']
    return 'MAP_' + m if m.isupper() else 'MAP_' + re.sub(r'(?<=[a-z])(?=[A-Z])', '_', m).upper()
C = {const(d): d for d in I}
NAME = {d: I[d]['ingame'] for d in I}
def link(d): return f'<a class=maplink href="#{d}">{html.escape(NAME[d])}</a>'
NEXUS = ['LEON','NESSA','ALISTER','BEA','ZINNIA','LIZA','TATE','ROXANNE','GRETA','WINONA','NOLAND','TUCKER','JUAN','SHELLY','LUCY','PHOEBE','SPENSER',
         'RAMOS','DIANTHA','AGATHA','JAMES','JESSIE','LORELEI','NEMONA','DAWN','CYNTHIA','BARRY','CYRUS','FANTINA','GARDENIA','VOLKNER','BYRON',
         'N','CHEREN','ALDER','SKYLA','ELESA','ROSA','LENORA','HILDA']
cast = []
for d in ORDER:
    seen = set()
    for o in I[d]['objects']:
        g = o['graphics_id'].replace('OBJ_EVENT_GFX_', '')
        if g in NEXUS and g not in seen:
            seen.add(g); cast.append((g.title(), d, o.get('trainer_type', '') != 'TRAINER_TYPE_NONE'))
# ---------------- grafo (SVG)
POS = {'AbundanceIsle': (3, 3), 'AbundanceIsle_Barn': (3, 4.2), 'AbundanceIsle_Farmhouse': (4.05, 4.2),
       'AbundanceIsle_HarvestFields': (1.5, 3), 'AbundanceIsle_KeeperHouse': (0.5, 4.2), 'AbundanceIsle_SpringGrove': (1.5, 1.8),
       'AbundanceIsle_WindsweptCape': (4.5, 3), 'AbundanceIsle_PokemonCenter': (5.6, 4.2), 'PLASMA_FRIGATE_DECK': (4.5, 4.2) if False else (4.5, 5.4),
       'PLASMA_FRIGATE_HOLD': (5.6, 5.4), 'FROSTFALL_CRATER_1F': (2, 5.4), 'FROSTFALL_CRATER_B1F': (1, 6.4), 'FROSTFALL_CRATER_LAB': (2.6, 6.6),
       'FROSTFALL_CRATER_CORE': (0.5, 7.5), 'AbundanceIsle_GaleCave': (5.6, 1.8), 'AbundanceIsle_GaleShore': (4.5, 0.8),
       'THUNDER_RIDGE': (3, 1.8), 'THUNDERSPIRE_1F': (3, 0.8), 'THUNDERSPIRE_2F': (2, 0.2) if False else (1.9, 0.6), 'ThunderspireSummit': (0.6, 0.6)}
POS['AbundanceIsle_Farmhouse'] = (3.9, 4.2); POS['AbundanceIsle_Barn'] = (2.9, 4.2)
POS.update({'AbundanceIsle_SkylaHangar': (5.6, 3.0), 'AbundanceIsle_ElderHouse': (5.6, 2.4) if False else (4.5, 4.2),
            'PLASMA_FRIGATE_CABINS': (4.5, 6.4), 'PLASMA_FRIGATE_ENGINE_ROOM': (5.6, 6.4),
            **ACT6POS})
SX, SY, BW, BH = 150, 64, 132, 34
OFFY = 0.8
edges = set()
for d in ORDER:
    for w in I[d]['warps']:
        t = C.get(w['dest_map'])
        if t and t != d: edges.add(tuple(sorted((d, t))) + ('w',))
    for c in I[d].get('connections', []):
        t = C.get(c['map'])
        if t: edges.add(tuple(sorted((d, t))) + ('c',))
ctr = lambda d: (POS[d][0] * SX + 20 + BW / 2, (POS[d][1] + OFFY) * SY + 20 + BH / 2)
svg = [f'<svg viewBox="0 0 {int(6.6 * SX)} {int(12.0 * SY)}" role="img" aria-label="Ligações entre os 20 mapas">']
for a, b, k in sorted(edges):
    (x1, y1), (x2, y2) = ctr(a), ctr(b)
    svg.append(f'<line x1="{x1:.0f}" y1="{y1:.0f}" x2="{x2:.0f}" y2="{y2:.0f}" stroke="{"#4a8fd8" if k == "c" else "#9a8fb8"}" stroke-width="2" {"stroke-dasharray=\"6 4\"" if k == "c" else ""}/>')
GROUPC = {'EMBER': '#f7eccd', 'TRUTH': '#f3e3c3', 'SHRIN': '#efe1f5', 'ABUND': '#e7f3df', 'Abund': '#e7f3df', 'PLASM': '#dfe6f7', 'FROST': '#e1f2f8', 'THUND': '#f6ead8', 'Thund': '#f6ead8'}
for d in ORDER:
    x, y = POS[d][0] * SX + 20, (POS[d][1] + OFFY) * SY + 20
    fill = GROUPC.get(d[:5], '#eee')
    svg.append(f'<a href="#{d}"><rect x="{x:.0f}" y="{y:.0f}" width="{BW}" height="{BH}" rx="6" fill="{fill}" stroke="#8a8fa0"/>'
               f'<text x="{x + BW / 2:.0f}" y="{y + 21:.0f}" text-anchor="middle" style="fill:#1d2130">{html.escape(NAME[d])}</text></a>')
svg.append('</svg>')
# ---------------- cartoes
LBL = {'dia': 'Dia', 'estado': 'Outro estado', 'depois': 'Depois', 'colisao': 'Colisão'}
cards = []
for n, d in enumerate(ORDER, 1):
    i = I[d]
    views = [k for k in ('dia', 'estado', 'depois', 'colisao') if os.path.exists(f'img/m/{d}_{k}.png')]
    caps = {k: i.get('estados', {}).get(k, '') for k in views}
    if 'colisao' in views: caps['colisao'] = 'Vermelho = bloqueio, azul = água; roxo = warps.'
    btn = ''.join(f'<button type=button data-map="{d}" data-k="{k}" data-cap="{html.escape(caps.get(k) or LBL[k])}" aria-pressed="{"true" if k == "dia" else "false"}">{LBL[k] if k != "estado" else html.escape((i.get("estados", {}).get("estado") or "Outro estado")[:28])}</button>' for k in views)
    warps = ''.join(f'<li class=mono>({w["x"]},{w["y"]}) → {link(C[w["dest_map"]]) if w["dest_map"] in C else html.escape(w["dest_map"])}</li>' for w in i['warps'])
    conns = ''.join(f'<li class=mono>conexão {c["direction"]} → {link(C[c["map"]]) if c["map"] in C else c["map"]}</li>' for c in i.get('connections', []))
    expl = ''.join(f'<li>{html.escape(e)}</li>' for e in i.get('explorar', []))
    objs = ''.join(f'<tr><td class=mono>{html.escape(o["local_id"])}</td><td class=mono>{html.escape(o["graphics_id"].replace("OBJ_EVENT_GFX_", ""))}</td><td class=num>{o["x"]},{o["y"]}</td><td>{o["movement_type"].replace("MOVEMENT_TYPE_", "").lower()}</td></tr>' for o in i['objects'])
    sec = i['secondary'].replace('gTileset_', ''); pri = i['primary'].replace('gTileset_', '')
    cards.append(f'''<article class=card id="{d}">
  <div class=viewer><div class=stage><img class=pixel id="img-{d}" src="img/m/{d}_dia.png" alt="{html.escape(NAME[d])}" loading=lazy></div>
  <div class=seg>{btn}</div><p class=caption id="cap-{d}">{html.escape(caps.get("dia", ""))}</p></div>
  <div style="display:flex;flex-direction:column;gap:10px"><div class=eyebrow>{n:02d} · {html.escape(i.get("map_type", "").replace("MAP_TYPE_", "").lower())}</div>
  <h3>{html.escape(NAME[d])}</h3><div class=meta>{i["w"]}×{i["h"]} · {pri} + {sec}</div>
  <p>{html.escape(i.get("historia", ""))}</p>
  <ul class=fun>{expl}</ul>
  <details><summary>Ligações</summary><ul class=fun>{warps}{conns}</ul></details>
  <details><summary>Objetos ({len(i["objects"])})</summary><div class=table-scroll><table><thead><tr><th>local_id</th><th>gráfico</th><th>x,y</th><th>movimento</th></tr></thead><tbody>{objs}</tbody></table></div></details>
  <p class=note>Conferido: {html.escape(str(i.get("conferido", "")))}</p></div></article>''')
cast_rows = ''.join(f'<tr><td><b>{html.escape(n)}</b></td><td>{link(d)}</td><td>{"sim" if t else "fala/ajuda"}</td></tr>' for n, d, t in cast)
L = link
def LX(k):
    for d in ORDER:
        if k in d.upper().replace('ABUNDANCEISLE_', ''): return link(d)
    return k
acts = f'''<div class=acts>
<div><h3>1 · Neve na colheita</h3><p>O barco chega em {L("AbundanceIsle")}, coberta de neve em plena colheita. Tornadus e Thundurus brigam sobre a montanha. N e Hilda estão à beira do lago. O guardião conta a lenda; a Cynthia, na {L("AbundanceIsle_KeeperHouse")} em {L("AbundanceIsle_HarvestFields")}, estuda os pergaminhos. Jessie e James rondam as plantações e a Lenora decifra a estela do caminho.</p><p class=quote>N: “The winds aren't angry. They're in pain. Someone is keeping this winter alive.”</p></div>
<div><h3>2 · A cratera</h3><p>A Lorelei investiga o frio fora de época na entrada de {L("FROSTFALL_CRATER_1F")}. O salão de gelo de {L("FROSTFALL_CRATER_B1F")}, onde o Byron analisa as lascas do meteorito, leva ao {L("FROSTFALL_CRATER_LAB")}. Lá o Ghetsis revela o plano (o frio do meteorito do Kyurem → tempestades → raios para a Pedra Escura → Kyurem Black). Batalha; ele foge e o jogador desliga a máquina. Um buraco secreto leva ao {L("FROSTFALL_CRATER_CORE")}, onde a Zinnia conta a história do meteoro.</p></div>
<div><h3>3 · A tempestade desce</h3><p>A neve para. Pela {L("AbundanceIsle_WindsweptCape")} (Pokémon Center com Nemona e Barry, Nessa no quebra-mar, Skyla no mirante) o jogador atravessa a {L("AbundanceIsle_GaleCave")}, onde o Noland espera numa sala de Rock Smash, até a {L("AbundanceIsle_GaleShore")}. Lá a Winona vigia o círculo de pedras onde o Tornadus caiu. No cais da Cape está o Plasma Frigate: no {L("PLASMA_FRIGATE_DECK")} a Rosa, infiltrada, cura a equipe e indica o {L("PLASMA_FRIGATE_HOLD")}, onde está a pesquisa dos DNA Splicers.</p></div>
<div><h3>4 · Thunderspire</h3><p>A {L("THUNDER_RIDGE")}: terraços sob os raios, com Volkner e Elesa (dupla), Thundurus no alto (Rock Smash) e Alder diante da torre. Nas ruínas, {L("THUNDERSPIRE_1F")} (Cheren e a lenda dos heróis gêmeos) e {L("THUNDERSPIRE_2F")} (Allister, o fantasma da torre). No {L("ThunderspireSummit")}, espiral de colunas, Pedra Escura, Ghetsis contra N, o Zekrom desperta e testa o jogador. O N entrega os DNA Splicers e a Hilda testemunha.</p><p class=quote>N: “Kyurem is waiting in the snow. Its emptiness can be filled... but not by force.”</p></div>
<div><h3>5 · Primavera</h3><p>Com Tornadus e Thundurus na equipe, o Landorus desce no santuário de {L("AbundanceIsle")} e o guardião entrega a Reveal Glass. O {L("AbundanceIsle_SpringGrove")} floresce: Ramos e Gardenia recebem o Arauto da Primavera, e o Enamorus chega ao jardim. N e Hilda se despedem no cais.</p></div>
<div><h3>6 · A luz da verdade</h3><p>A carta do N traz o jogador de volta. A Lenora completa a estela: a Light Stone dorme “onde o sol se põe sobre a areia”. Pela {LX("SUNSET")}, ilhotas, Shelly e nadadores, chega-se a {LX("EMBERDUNE")}, onde o resto do Plasma escava. Nas {LX("RUINS_1F")}, a areia movediça derruba para o {LX("RUINS_B1F")}; Lucy e Spenser estudam os murais. No {LX("HALL")}, Ghetsis tenta despertar a pedra, mas ela brilha para a Hilda: o Reshiram desperta, recusa o Plasma e testa o jogador. No fim, a porta selada da ilhota abre o {LX("SHRINE")}: murais do Primeiro Dragão, Tate e Liza, a batalha dupla final contra N e Hilda e a fusão do Kyurem Black e White.</p><p class=quote>Hilda: “Truth isn't something you can steal, Ghetsis. It finds you.”</p></div></div>'''
pend = '''<div class=open>
<div class=hi><b>Estado da implementação:</b> a fase 1 começou no repositório com os 24 primeiros mapas instalados, os 3 tilesets com os desenhos escolhidos (santuário A, máquina D, avião A), o sprite da Pedra Escura (C), a var de estado e as flags. O build ainda não foi conferido e está pausado para entrarem os 6 mapas do ato 6.</div>
<div class=hi><b>Escolher 1 proposta de cada desenho</b> (santuário, máquina, Pedra Escura).</div>
<div class=hi><b>Sprites do Ghetsis, dos recrutas do Plasma e do Plasma Frigate.</b> Nos renders estão os placeholders Sage, Scientist e S.S. Tidal.</div>
<div class=hi><b>Como se chega na região</b> e em que ponto do jogo ela abre.</div>
<div><b>Portas trancadas:</b> os camarotes do Plasma Frigate que não levam às Cabins ficam trancados por script.</div>
<div class=hi><b>Nexus:</b> ao implementar, marcar <code>requiresCaught</code> no pool para Zekrom, Reshiram, Tornadus, Thundurus, Landorus e Enamorus, porque passam a ter fonte na campanha. As Forças continuam no Battle Café como fonte extra, e os DNA Splicers deixam de vir só do drop do Kyurem no Nexus.</div>
<div><b>Itens que as missões pedem e precisam existir:</b> sacos de sementes, fragmentos da estela e velas espirituais podem ser só objetos com flag, sem item novo na bolsa. O uniforme Plasma é uma flag. O contador da corrida do Barry é uma var de passos.</div>
<div><b>Interiores reaproveitados:</b> celeiro, casa do fazendeiro, casa do guardião e o PC são cópias de layouts existentes (Route39_Barn, Route39_FarmHouse, AzaleaTown_KurtsHouse, CianwoodPokecenter), com pequenas mudanças.</div>
<div><b>Retoques no Porymap:</b> na Windswept Cape e na Gale Shore o penhasco encosta direto na areia no topo; a fachada da torre na Thunder Ridge traz junto um pedaço de grama e árvores vermelhas; o porão do Frigate tem um trecho de parede duplicado pelo alargamento.</div>
<div><b>Tiles:</b> route38_farmland e cave_ice estão com 384 tiles no PNG; é preciso medir o uso real antes de instalar os desenhos (ou clonar o secundário).</div>
<div><b>Flags e vars</b> ainda não foram alocadas (neve, atalhos de gelo, aparições dos lendários, NPCs que mudam de lugar). </div></div>'''
facts = ''.join(f'<div><b>{a}</b><span>{b}</span></div>' for a, b in ((str(NMAPS), 'mapas'), ('6', 'lendários com fonte de verdade'), (str(len({n for n, _, _ in cast})), 'personagens do Nexus em cena'), ('24', 'propostas de desenho')))
AV = [('A', 'Cargueiro azul', 'Monomotor de carga, o mais “piloto de Unova”: as cores do uniforme da Skyla.'),
      ('B', 'Biplano', 'Mais antigo e charmoso; combina com uma ilha de fazendas.'),
      ('C', 'Hidroavião', 'Com flutuadores, explica pousar numa ilha sem pista.'),
      ('D', 'Coberto pela lona', 'Avião preso pela tempestade, sob lona: estado do ato 1, troca pela versão descoberta depois.')]
TOYS = '<section><div class=eyebrow>Desenho novo 6 · canto de brinquedos</div><h2>Quarto do N</h2><p>O canto de brinquedos do quarto do castelo (trilho de trem, bola de basquete, skate) não existe em nenhum tileset.</p><div class=props>' + ''.join(
    f'<figure><div class=art><img class=pixel src="img/arte_toys_{c}.png" alt="Proposta {c}"></div><img class=pixel src="img/toys_{c}.png" alt="Proposta {c} no mapa"><figcaption><b>{c} · {t}</b></figcaption></figure>' for c, t in (('A', 'Oval com o trem'), ('B', 'Trilho em oito'), ('C', 'Aro de basquete e trilho'), ('D', 'Brinquedos no tatame'))) + '</div></section>'
AVIAO = '<section><div class=eyebrow>Desenho novo 4 · 4×3 metatiles</div><h2>O avião da Skyla</h2><p>No Skyla\'s Hangar (Windswept Cape). Não existe avião em nenhum tileset do repositório.</p><div class=props>' + ''.join(
    f'<figure><div class=art><img class=pixel src="img/arte_aviao_{c}.png" alt="Proposta {c}"></div><img class=pixel src="img/aviao_{c}.png" alt="Proposta {c} no mapa"><figcaption><b>{c} · {t}</b>{d}</figcaption></figure>' for c, t, d in AV) + '</div></section>'
LS = [('A', 'Oval com veios de fogo', 'Pedra branca com rachaduras de fogo: espelho da proposta A da Pedra Escura.'),
      ('B', 'No pedestal de arenito', 'Sobre um pedestal de arenito com brasas soltas, como relíquia de museu (a Lenora a reconheceria).'),
      ('C', 'Escama em espiral', 'Gêmea da Pedra Escura escolhida (C): mesma forma, em branco. Usada nos renders.'),
      ('D', 'Despertando', 'Dentro de uma aura de chamas: pode ser o 2º quadro quando o Reshiram acorda.')]
import glob as _g
_ls = sorted(_g.glob('img/arte_light_*.png'))
LIGHT = '<section><div class=eyebrow>Desenho novo 5 · objeto 32×32</div><h2>Light Stone</h2><p>No altar do Hall of Truth. Sprite novo, irmão do da Pedra Escura.</p><div class=props>' + ''.join(
    f'<figure><div class=art><img class=pixel src="img/arte_light_{c}.png" alt="Proposta {c}"></div><img class=pixel src="img/light_{c}.png" alt="Proposta {c} no mapa"><figcaption><b>{c} · {t}</b>{d}</figcaption></figure>' for c, t, d in LS) + '</div></section>'
script = '''<script>
document.querySelectorAll('.seg button[data-map]').forEach(b=>b.addEventListener('click',()=>{
 const m=b.dataset.map; b.parentElement.querySelectorAll('button').forEach(x=>x.setAttribute('aria-pressed',x===b?'true':'false'));
 document.getElementById('img-'+m).src='img/m/'+m+'_'+b.dataset.k+'.png'; document.getElementById('cap-'+m).textContent=b.dataset.cap;}));
</script>'''
page = f'''<!DOCTYPE html><html lang="pt-BR"><head><meta charset="utf-8"><meta name="viewport" content="width=device-width,initial-scale=1">
<title>Abundance Isle — proposta de ilha</title>
<link rel="preconnect" href="https://fonts.googleapis.com"><link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
<link rel="stylesheet" href="https://fonts.googleapis.com/css2?family=Pixelify+Sans:wght@500;700&family=Source+Sans+3:ital,wght@0,400;0,600;0,700;1,400&family=JetBrains+Mono:wght@400;600&display=swap">
<style>{css}</style></head><body><div class=wrap>
<header style="display:flex;flex-direction:column;gap:12px"><div class=eyebrow>Proposta · SoulGold · 30/10/2026 · v3 ({NMAPS} mapas, eventos e lore)</div>
<h1>Abundance Isle</h1>
<p class=lede>Uma aventura em {NMAPS} mapas. Uma ilha de colheita está presa num inverno fora de época: Ghetsis rouba o frio do meteorito do Kyurem para provocar tempestades, enlouquecer Tornadus e Thundurus e usar os raios para acordar a Pedra Escura do Zekrom. N ouve a dor dos ventos e pede ajuda.</p>
<div class=facts style="grid-template-columns:repeat(4,1fr)">{facts}</div>
<p class=note>Montado só com tilesets que já existem no repositório. Os renders saem dos map.bin gerados, com os sprites reais. Nada no repositório foi alterado.</p></header>
<section><div class=eyebrow>A região</div><h2>Seis ilhas ligadas pelo mar</h2>
<p>A Abundance Isle no centro; a Harvest Fields a oeste, a Windswept Cape a leste e a Gale Shore ao norte. Ao sul da Harvest Fields, a Sunset Strait desce até Emberdune, a ilha de areia. Tudo ligado por conexões de mapa (de Surf). Role a imagem para ver tudo.</p>
<div class=region><img class=pixel src="img/regiao.png" alt="Região costurada"></div>
<p>As ligações entre os {NMAPS} mapas (clique num nome para ir até ele). Linha tracejada azul = conexão pelo mar; linha cheia = porta, caverna ou escada.</p>
<div class=graph>{''.join(svg)}</div></section>
<section><div class=eyebrow>História · N e Ghetsis</div><h2>A aventura, na ordem do jogador</h2>{acts}</section>
{open('m20/_eventos.html').read()}
{open('m20/_lendarios.html').read()}
<section><div class=eyebrow>Os {NMAPS} mapas</div><h2>Mapa por mapa</h2><div class=cards>{''.join(cards)}</div></section>
<section><div class=eyebrow>Elenco do Nexus</div><h2>Personagens que ganham lugar no mundo</h2>
<p>Treinadores do Nexus que já tinham sprite de overworld e não apareciam em nenhum mapa.</p>
<div class=table-scroll><table><thead><tr><th>Personagem</th><th>Onde</th><th>Batalha</th></tr></thead><tbody>{cast_rows}</tbody></table></div></section>
{open('m20/_desenhos.html').read()}
{AVIAO}
{LIGHT}
{TOYS}
<section><div class=eyebrow>Para decidir</div><h2>Pendências</h2>{pend}</section>
{open('m20/_fontes.html').read()}
<footer>Protótipo gerado por código. map.bin/border.bin, info.json e geradores de cada mapa estão no scratchpad da sessão, prontos para instalar quando aprovado.</footer>
</div>{script}</body></html>'''
open('index.html', 'w').write(page)
print('ok', len(page), 'elenco', len(cast))
