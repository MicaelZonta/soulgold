# Como encenar um evento / cutscene no SoulGold

Guia derivado da cena dos professores em `Route30_MrPokemonsHouse`
(Kukui + Oak + Lillie, entrega do Mystery Egg e da Pokédex).

Serve para qualquer cena com NPCs andando, falando e saindo de cena.
Para **criar** o NPC do zero veja [adicionar-npc.md](adicionar-npc.md) e
[adicionar-grafico-trainer.md](adicionar-grafico-trainer.md); para a
batalha em si veja [adicionar-batalha-npc.md](adicionar-batalha-npc.md).

> ⚠️ **Regra de ouro:** as posições no `map.json` são a **fonte de verdade**.
> Nunca reposicione um objeto para fazer um `applymovement` antigo funcionar —
> recalcule o caminho a partir das coordenadas reais.

---

## Checklist rápido

| # | O que | Onde |
|---|-------|------|
| 1 | Ler as coordenadas dos objetos e do warp | `data/maps/<Mapa>/map.json` |
| 2 | Dumpar a grade de colisão do layout | `data/layouts/<Layout>/map.bin` |
| 3 | Escolher os tiles-âncora (jogador, NPCs, saída) | papel/comentário |
| 4 | Escrever movimentos tile a tile | `data/maps/<Mapa>/scripts.pory` |
| 5 | `make` (regenera o `.inc` via poryscript) | raiz do repo |

Edite **sempre o `.pory`**. O `scripts.inc` é gerado (`data/%.inc: data/%.pory`
no `Makefile`) — mexer nele à mão é perdido no próximo build.

---

## 1. Ler as posições reais

```bash
python3 -c "
import json
m=json.load(open('data/maps/<Mapa>/map.json'))
for o in m['object_events']: print(o['local_id'], o['graphics_id'], (o['x'],o['y']), o['movement_type'])
for w in m['warp_events']:   print('WARP ->', w['dest_map'], (w['x'],w['y']))
"
```

O `x`/`y` do `map.json` é **relativo ao mapa** e usa o mesmo índice da
blockdata: `bloco = vals[y * width + x]`. Não há offset de +7 aqui.

## 2. Dumpar a grade de colisão

`map.bin` é um array de `u16` little-endian, um por bloco
(ver `include/global.fieldmap.h`):

| Bits | Campo | Máscara |
|------|-------|---------|
| 0-10 | metatile id | `0x07FF` |
| 11 | **colisão** (1 = intransponível) | `0x0800` |
| 12-15 | elevação | `0xF000` |

> ⚠️ **A armadilha:** é **1 bit** de colisão, não 2. Se você usar
> `(v >> 10) & 3` (o layout antigo do pokeemerald) o bit 10 do metatile
> vaza pra dentro da colisão e metade do chão vira "parede" fantasma.

```bash
python3 -c "
import struct, json
name='<Layout>'   # ex.: Route30_MrPokemonsHouse
lay=[l for l in json.load(open('data/layouts/layouts.json'))['layouts'] if l['name']==name+'_Layout'][0]
w,h=lay['width'],lay['height']
v=struct.unpack('<%dH'%(w*h), open('data/layouts/%s/map.bin'%name,'rb').read())
print('    '+''.join(' %d'%(x%10) for x in range(w)))
for y in range(h):
    print('%2d  '%y + ''.join(' #' if (v[y*w+x]>>11)&1 else ' .' for x in range(w)))
"
```

Leia a saída assim:

- `.` = o NPC pode pisar. `#` = móvel, parede ou vazio.
- O **warp** de porta em parede fica no tile `.` logo à frente da porta;
  é ali que o jogador nasce ao entrar (virado para o norte).
- Um NPC **pode** estar parado em cima de um `#` (cadeira, balcão, cama).
  Nesse caso confira se ele tem pelo menos **um vizinho ortogonal `.`**,
  senão ele não consegue sair sem atravessar móvel.

## 3. Escolher os tiles-âncora

Antes de escrever qualquer `walk_`, defina no papel:

- **Tile do jogador** durante a cena. Precisa ser ortogonalmente adjacente
  ao NPC que mais fala, e deixar **tiles livres em volta** para quem vai
  se aproximar depois. Reserve um tile por NPC que se move.
- **Tile de parada** de cada NPC que se aproxima (adjacente ao jogador).
- **Caminho até a saída** de cada NPC que vai embora — pode passar por
  onde outro NPC *já saiu*, mas nunca por cima do jogador.

Exemplo real (Mr. Pokémon's House): jogador em `(7,6)`, Kukui fixo em
`(7,5)` ao norte dele, Lillie para em `(6,6)` a oeste, Oak desce para
`(8,6)` a leste. Três interlocutores, zero colisões.

Documente essa planta como comentário `@` no topo do `.pory`. É o que
faz o próximo agente não precisar refazer esta análise.

## 4. Escrever o script

Padrão de um beat da cena:

```
	@ --- 6. Lillie sai da cadeira: (5,5) -> (5,6) -> (6,6) ---
	applymovement LOCALID_<MAPA>_LILLIE, <Mapa>_Movement_LillieToPlayer
	waitmovement 0
	turnobject OBJ_EVENT_ID_PLAYER, DIR_WEST
	msgbox <Mapa>_Text_LillieIntro, MSGBOX_DEFAULT
```

Regras que evitam 90% dos bugs de encenação:

- **`waitmovement 0` depois de todo `applymovement`** que precede uma fala.
  Sem isso o diálogo abre com o NPC ainda no meio do passo.
- `applymovement` com `walk_*` **ignora colisão**. Ele nunca vai falhar —
  o NPC simplesmente atravessa a mesa. A validação é sua, na grade.
- `turnobject <id>, DIR_*` para quem está parado; `faceplayer` só funciona
  em script acionado pelo jogador (`lock` + `faceplayer`), não em cutscene.
- Nomeie o movimento pelo que ele faz (`_LillieToPlayer`, `_OakLeave`) e
  comente o caminho tile a tile em cima do label.
- `closemessage` antes de `call Common_EventScript_OutOfCenterPartyHeal`
  (ele faz `fadescreenswapbuffers`, e a caixa de texto ficaria na tela).
- Mugshot: `createfieldmugshot MUGSHOT_X` … `removefieldmugshot`, **um por
  falante**. `removefieldmugshot` é seguro mesmo sem mugshot ativo, então
  vale chamá-lo antes de uma batalha por garantia.
- Só existe mugshot para quem está em `include/constants/field_mugshots.h`.

### Saída persistente de um NPC

`removeobject` some com o NPC **só na sessão atual do mapa**. Para ele não
voltar, o objeto precisa ter uma `flag` no `map.json` e o script precisa
setá-la no fim:

```json
{ "local_id": "LOCALID_ROUTE30_OAK", ..., "flag": "FLAG_DELIVERED_EGG" }
```
```
	applymovement LOCALID_ROUTE30_OAK, MrPokemonHouse_Movement_OakLeave
	waitmovement 0
	playse SE_EXIT
	removeobject LOCALID_ROUTE30_OAK
	...
	setflag FLAG_DELIVERED_EGG      @ agora ele não reaparece mais
```

### Derrota / blackout / reentrada

Com `trainerbattle_no_intro`, **perder causa blackout e o script para ali**.
Isso é o comportamento desejado numa cutscene:

- Deixe todo `setvar`/`setflag` de recompensa **depois** do `trainerbattle`.
- A `VAR_<...>_STATE` continua no valor antigo, então o `map_script_2` do
  `MAP_SCRIPT_ON_FRAME_TABLE` dispara de novo ao reentrar.
- Ao reentrar, os objetos renascem nas coordenadas do `map.json` — a cena
  recomeça consistente **sem** nenhum código de "reset" manual.

Ou seja: nunca faça `setvar` de progresso antes da batalha.

### O que sobrevive à batalha

Depois de um `trainerbattle`, o mapa **não** é recarregado: os NPCs ficam
onde estavam quando a batalha começou. Então o caminho de saída de um NPC
deve ser calculado a partir do tile em que ele **parou na cena**, não do
tile original do `map.json`.

---

## 5. Build

```bash
make -j$(nproc)
```

O poryscript roda sozinho (`data/%.inc: data/%.pory`). Erros de sintaxe
aparecem como falha do `tools/poryscript/poryscript`; nomes de constante
errados aparecem depois, no `arm-none-eabi-as`.

---

## Checagem final antes de fechar a task

- [ ] Todo tile de todo `walk_*` é `.` na grade de colisão.
- [ ] Nenhum NPC termina em cima de outro NPC ou do jogador.
- [ ] `waitmovement 0` antes de cada fala que depende de aproximação.
- [ ] Movimentos antigos incompatíveis foram **apagados**, não deixados órfãos.
- [ ] Recompensas/`setvar` só depois da batalha.
- [ ] Quem sai de cena tem `flag` no `map.json` **e** `setflag` no script.
- [ ] Falas novas têm no máximo ~180 px por linha (ver abaixo).
- [ ] `make` limpo.

### Medir a largura de uma fala

O limite prático da caixa de diálogo é **~180 px** por linha (`\n`).
Ultrapassar não quebra o build — só corta o texto na tela.

```bash
python3 - <<'EOF'
import re
nums=[int(x) for x in re.findall(r'-?\d+', re.search(
    r'gFontNormalLatinGlyphWidths\[\] = \{(.*?)\};', open('src/fonts.c').read(), re.S).group(1))]
cm={m.group(1): int(m.group(2),16) for m in
    (re.match(r"^'(.)'\s*=\s*([0-9A-Fa-f]{2})\s*$", l) for l in open('charmap.txt', encoding='utf-8')) if m}
for line in ["Oak: A battle? An excellent chance"]:      # <- suas linhas aqui
    print(sum(nums[cm[c]] for c in line), '|', line)
EOF
```

Apóstrofo e acentos não estão no mapa simples acima; troque-os por uma
letra qualquer só para medir.
