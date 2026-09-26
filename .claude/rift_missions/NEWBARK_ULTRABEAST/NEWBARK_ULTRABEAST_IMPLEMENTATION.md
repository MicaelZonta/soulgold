# New Bark — Kartana + Guzzlord + Nihilego e Ultra Necrozma (Rift Mission 4) — implementação

**Status:** **roteiro V2 aplicado** — 26/09/2026. `make -j$(nproc)` limpo.
**Runtime pendente** (checklist §10).

**Fonte da cena:** [`NEWBARK_ULTRABEAST_SCRIPT_V2.md`](NEWBARK_ULTRABEAST_SCRIPT_V2.md).
Este arquivo descreve **como o V2 está no código**: estado, visibilidade,
planta, coreografia, retry e riscos. A história anterior (22/09 — a cidade que
não evacuava, a derrota dos quatro, "a conta de nove", a conversa de Faller no
briefing) foi **inteiramente substituída**; o registro dela está no git
(`git log -- .claude/rift_missions/NEWBARK_ULTRABEAST/`). O roteiro antigo
[`NEWBARK_ULTRABEAST_SCRIPT.md`](NEWBARK_ULTRABEAST_SCRIPT.md) não é mais
contrato.

**Design do arco:** [`SOULGOLD_RIFT_MISSIONS_DESIGN.md`](../SOULGOLD_RIFT_MISSIONS_DESIGN.md) §5 e §6 (M4).
**Defaults do autor para roteiros V2** (memória `roteiros-v2-decisoes-do-autor`):
alargar o mapa quando falta espaço, narração/bilhete sem plaquinha, dependência
de arte vira ajuste de texto quando dá.

---

## 0. Fluxo

```text
Cherrygrove resolvida ─────────────── estado 8
  └─ ligação diária do Looker (M4) ── FLAG_RIFT_LOOKER_SUMMONS
       └─ Olivine: briefing M4 (5 caixas) ─ setflag EVENT_NEWBARK + estado 9
            └─ New Bark: prep (conversas, cura da mãe, portas trancadas)
                 └─ Looker ▶ SIM
                      ├─ formação: jogador (16,12), emissores, teste, Snorlax, Milotic
                      ├─ três aberturas: Kartana corta a cerca, Guzzlord come a barricada,
                      │   Nihilego sobe na faixa da mãe; Azumarill o repele
                      ├─ Lusamine × mãe; mãe e Looker entram no laboratório
                      └─ ESCOLHA (setflag FLAG_NEWBARK_UB_ENGAGED) → boss
                           ├─ perdeu / fugiu → blackout (20,12) → retry direto na escolha
                           └─ venceu → campo corta as ligações → Ball → Necrozma →
                                campo cede → absorção → Ultra Necrozma → instabilidade →
                                [parceiro Cosmog] → recuo pela abertura → nove padrões →
                                rescaldo → gancho → narração → estado 10 + warp
  └─ Olivine, estado 10: espera ("comparing the records") até a ligação da reunião
```

---

## 1. Estado

### 1.1 Var e flags

`VAR_RIFT_MISSIONS_STATE` (`0x4120`):

| Valor | Significado | Quem escreve |
|---|---|---|
| 8 | Cherrygrove resolvida; M4 aguarda ligação e briefing | `CherrygroveCity_EventScript_UBFinish` |
| 9 | Briefing feito; incidente ativo | `OlivineCity_House1_EventScript_BriefingTalkM4` |
| 10 | New Bark resolvida; reunião aguarda **ligação própria** | `NewBarkTown_EventScript_UBFinish` |

| Flag | Valor | Uso |
|---|---|---|
| `FLAG_EVENT_ULTRABEAST_NEWBARK` | `0x1044` | Setada ⇔ estado 9. Esvazia a cidade, tira a mãe de casa e o Elm do laboratório, desenha as barreiras (`ON_LOAD`) e tranca as portas |
| `FLAG_NEWBARK_UB_ENGAGED` | `0x1050` | **Nova.** Checkpoint: setada em `UBChoose`, limpa em `UBFinish`. Faz o `ON_TRANSITION` montar a rua da escolha e o laboratório mostrar a mãe abrigada |
| `FLAG_NO_CATCHING` (= `B_FLAG_NO_CATCHING`) | `0x1041` | Antes da batalha; a engine limpa |
| `FLAG_DAILY_LOOKER_CALL` | daily | **Não** é setada no fim da M4 (V2 §18): a ligação da reunião pode tocar no mesmo dia se o convite de New Bark foi de outro dia |

### 1.2 Temporárias de `NewBarkTown`

Cada ator que sofre `removeobject` tem a **própria** flag: `removeobject` seta a
flag do template, e uma flag compartilhada faria o irmão re-adicionado ressuscitar
o outro no próximo passo de câmera.

| Temp | Uso |
|---|---|
| `FLAG_TEMP_1` | Anabel, Gold/Crystal, Azumarill, Lusamine (nunca removidos) |
| `FLAG_TEMP_2` | Kartana, Guzzlord, Nihilego (saem juntos) |
| `FLAG_TEMP_3` | Elm |
| `FLAG_TEMP_4` | Mãe (entra no laboratório, reaparece no rescaldo) |
| `FLAG_TEMP_5` / `_6` | Necrozma / Ultra Necrozma (mesmo tile, nunca juntos) |
| `FLAG_TEMP_7` | Looker (entra e sai do laboratório) |
| `FLAG_TEMP_8` / `_9` | Snorlax / Milotic |
| `FLAG_TEMP_A` | Os dois emissores |
| `FLAG_TEMP_B` | Abertura principal (só no recuo) |
| `FLAG_TEMP_C` | Parceiro: Cosmog, Cosmoem, Solgaleo, Lunala em (17,13) |
| `FLAG_TEMP_E` | `FLAG_TEMP_HIDE_FOLLOWER`: setada no SIM e em todo load de retry. **Remove** o objeto do follower (libera o slot); o warp final a zera |
| `VAR_TEMP_2/3/4` | Resultado; escolha (0 Kartana, 1 Guzzlord, 2 Nihilego); espécie Cosmog amostrada depois da batalha |

`NewBarkTown_Lab` usa `FLAG_TEMP_1` (Elm) e `FLAG_TEMP_2` (mãe abrigada);
`NewBarkTown_PlayersHouse_1F` usa `FLAG_TEMP_1` (mãe).

### 1.3 Orçamento

**Objetos** (`OBJECT_EVENTS_COUNT` 16, jogador incluído). Pico com as três UBs
fora e a mãe ainda na rua: jogador + Looker, Anabel, mãe, Gold/Crystal,
Azumarill, Elm, Lusamine, Snorlax, Milotic, 2 emissores, 3 UBs = **15**. Com o
Necrozma a mãe já entrou: 15 de novo. Por isso o Necrozma **chega por uma
distorção** (clarão + brilho) e a abertura principal só vira objeto no recuo,
depois da absorção. Templates: 36 (limite 64).

**Paletas de sprite** (16 slots): cada espécie carrega a sua, e Looker,
Lusamine, Elm e o emissor (`0x116D`) também. Pico ≈ 14 + efeitos. Testar à noite, com todos
na tela (§10).

---

## 2. Olivine e telefone

- `RiftMissions_Text_LookerCallM4` (já aplicado com a ponte da M3) e
  `OlivineCity_House1_Text_WaitForNewBarkCall` — iguais ao V2 §3.
- `BriefingTalkM4`: **cinco** `msgbox` seguidos, um falante cada, sem
  `closemessage` entre eles — `BriefingM4Evidence` (Looker), `Comparison`
  (Anabel), `Safety` (Looker), `Containment` (Anabel), `Plan` (Anabel). Saíram
  `BriefingM4Kukui`, `BriefingM4Faller`, `BriefingM4NewBark` e o "Take these".
- "Vá na frente" do estado 9: `LookerGoAheadM4` / `AnabelGoAheadM4` do V2.
- **Estado 10 sem ligação:** `LookerWaitCall` ganhou o ramo
  `OlivineCity_House1_EventScript_LookerWaitCallAltar` →
  `OlivineCity_House1_Text_WaitForAltarCall`. A reunião continua bloqueada até a
  ligação (`StageReunionIfCalled` / `LookerReunionIfCalled`, que já existiam).
- `RiftMissions_Text_LookerCallReunion` = `Phone_Text_LookerAltarInvite` do V2.

---

## 3. New Bark — mapa, visibilidade e barreiras

### 3.1 Planta (colisão real, `dump_mapa.py`; y cresce para baixo)

```text
      x= 10 11 12 13 14 15 16 17 18 19 20 21 22
  y= 9    D  #  .  #  k  f  N  r  #  #  #  #  #     D porta do laboratório (10,9)
  y=10    .  E  .  .  F  F  F  f  #  #  #  #  #     F cerca temporária
  y=11    .  .  W  U  .  m  .  #  #  #  d  #  #     d porta da casa (20,11)
  y=12    .  R  z  .  .  .  P  .  .  .  *  K  A     * (20,12) chegada / Fly / blackout
  y=13    .  .  .  .  .  .  .  .  .  .  .  M  .
  y=14    #  .  .  .  .  .  .  .  a  .  s  .  .
  y=15    .  .  .  .  .  .  .  .  .  .  B  B  B     B barricada de toras
  y=16    .  .  .  n  .  .  .  .  .  .  .  g  .
```

| Quem | Prep (`map.json`) | Na operação |
|---|---|---|
| Looker | (21,12) ←, talk só de (20,12) | escolta a mãe e volta a (21,12) |
| Anabel | (22,12) ← | (18,14) → |
| Mãe | (21,13) ↑ | atravessa a (16,13); entra no laboratório |
| Gold/Crystal + Azumarill | (11,12) → / (12,12) → | Azumarill (13,12) depois do corte |
| Elm | (11,10) ↓ ao lado da porta | fica ali; a estação é logo dentro da porta |
| Lusamine | (13,11) → no controle do emissor oeste | vai a (15,13) só na conversa com a mãe |
| Emissores | — | oeste (12,11), leste (22,12) |
| Snorlax / Milotic | — | (20,14) / (15,11) |
| Kartana / Guzzlord / Nihilego | nascem em (14,9) / (21,16) / (13,16) | (14,10) / (21,14) / (13,14) |
| Necrozma e Ultra | — | (16,9), fora da área, no canteiro |
| Abertura principal | — | (17,9), só no recuo |
| Parceiro | — | (17,13), lado protegido do jogador |

Há água no layout (lago em x 25–26, y 11–14, `MB_OCEAN_WATER` com colisão 0);
nada da cena passa de x 22.

**Câmera.** Nada mexe a câmera. O posto de comando (16,12) enquadra x 9..23 e,
com caixa aberta, y 8..14: porta do laboratório, Elm, corredor do rival, cerca,
casa, Looker, Anabel e Snorlax numa tela. A janela de spawn (x−9..x+10,
y−7..y+9) cobre a cena inteira, exceto quando o jogador vai ao Guzzlord (20,14):
a janela vira x 11..30 e Looker/Elm/rival podem ser recriados do template — por
isso **todo ator que termina uma caminhada fora do template recebe
`setobjectxyperm` + tipo de movimento** logo depois.

### 3.2 Visibilidade (`NewBarkTown_OnTransition` → `ApplyUBVisibility`)

1. Sem evento: todo o elenco escondido.
2. Estado 9, primeira tentativa: elenco da prep; tudo o mais só pela cena.
3. `FLAG_NEWBARK_UB_ENGAGED` (retry): `StageUBRetry` monta a formação da escolha
   com `setobjectxyperm` (UBs nos tiles pós-incursão, Azumarill (13,12),
   Anabel (18,14)), mostra Snorlax, Milotic e emissores, esconde a mãe (está no
   laboratório) e seta `FLAG_TEMP_HIDE_FOLLOWER`.

Interiores: a mãe de casa e o Elm do laboratório somem enquanto o evento está
ativo (padrão antigo, mantido). **Novo:** `LOCALID_NEWBARK_LAB_MOM` em (5,11) no
laboratório, visível ⇔ evento **e** `ENGAGED`, com a cura dela
(`NewBarkTown_Lab_EventScript_ShelterMom`). Nunca a mãe em dois lugares.

### 3.3 Barreiras em metatile (`ON_LOAD` → `ApplyUBBarriers`)

A barreira temporária do norte e o bloqueio do sul são `setmetatile`, sem
objeto (economia de slot) e sem tocar o `map.bin`:

| Barreira | Tiles | Metatile | Depois do rompimento |
|---|---|---|---|
| Cerca branca no canteiro | (14..16,10) | `0x0E7` | Kartana corta (14,10) → flor `0x004` |
| Barricada de toras na rua sul | (20..22,15) | `0x2E0` | Guzzlord destrói (21,15)/(22,15) → rua `0x0DC`/`0x105` |

`ON_LOAD` roda também na volta da batalha (depois da vista salva), então o
estado das barreiras segue `ENGAGED` sem redesenho manual. Na cena, cada
rompimento é `setmetatile` + `special DrawWholeMapView`. O warp final recarrega o
layout original: barreiras e emissores somem sob a narração da transição.

**Ajuste de arte (default 3 do autor):** o V2 pede "bloqueio de caixas vazio".
O primário não tem caixote (o metatile 61 é porta animada); ficou uma
**barricada de toras**, e a fala do Looker já diz "south barrier".

### 3.4 Portas

`sLockedTownDoors` (`src/field_control_avatar.c`) ganhou `openDoorMap2`. New Bark:
abertos o laboratório (abrigo) e a casa do jogador; as outras portas mostram
`NewBarkTown_Text_UBDoorNote`, sem plaquinha.

---

## 4. A cena (V2 §6–§10)

| Beat | Script | O essencial |
|---|---|---|
| Prep | `UBLusamine/Elm/Mom/Rival/Anabel` | Uma fala cada; a mãe pergunta "rested?" (NÃO = cura). Em retry, falas curtas próprias |
| SIM | `UBLooker` → `UBScene` | `hidefollower` + `FLAG_TEMP_HIDE_FOLLOWER`; jogador (20,12)→(16,12); Lusamine põe o emissor oeste; Anabel (22,12)→(22,13) põe o leste e segue a (18,14); `UBFieldLine` (teste); falas do campo; Looker acena; Elm vira para a estação; Snorlax e Milotic saem da Ball com SE e cry **antes** das falas deles |
| Aberturas | `UBOpenings` | três bipes do sensor; "!" da Anabel; `fadeoutbgm`; fala; `playbgm MUS_DP_LEGEND_APPEARS, TRUE`; três aberturas em sequência com brilho e cry separados, o jogador virando para cada |
| Kartana | `UBKartanaCuts` | ataque + `SE_M_CUT`; (14,10) volta a flor; entra no vão; Milotic vira; rival: "opened the side path" |
| Guzzlord | `UBGuzzlordBreaks` | ataque + `SE_M_BITE` + tremor; toras (21,15)/(22,15) viram rua; avança (21,16)→(21,14), debaixo da mãe; Snorlax vira; Looker: "south barrier's gone" |
| Nihilego | `UBNihilegoDrifts` | mãe (21,13)→(16,13) enquanto o Nihilego sobe (13,16)→(13,13) devagar; Azumarill (12,12)→(13,12), ataque para baixo, Nihilego empurrado a (13,14) |
| Mãe × Lusamine | `UBMomAndLusamine` | Lusamine (13,11)→(15,13) passando sob o Kartana com o Milotic ao lado; mãe olha o jogador (N) e a Lusamine (O); Lusamine olha rival e Anabel e aceita; volta ao controle. Looker vem a (17,13); mãe e Looker atravessam a (10,10)/(10,11) com `delay_16` separando os dois; porta abre, os dois entram, porta fecha; Looker sai e volta a (21,12) |
| Escolha | `UBChoose` | `setflag ENGAGED`; prompt da Anabel; menu sem B |

**Escolha — quem vai para onde** (parceiros primeiro, jogador por último; todos
com template sincronizado):

| Escolha | Milotic | Snorlax | Jogador |
|---|---|---|---|
| Kartana | (15,11)→(14,14) ← Nihilego | fica (20,14) → Guzzlord | (14,11) ↑ |
| Guzzlord | (15,11)→(14,14) ← Nihilego | (20,14)→(14,11) ↑ Kartana | (20,14) → |
| Nihilego | (15,11)→(21,13) ↓ Guzzlord | (20,14)→(14,11) ↑ Kartana | (14,14) ← |

No ramo Nihilego a Lusamine vira para o sul (Nihilego) e hesita antes da fala.
Em todos os ramos o rival cobre a volta ("I've got the way back") — sem batalha
dupla.

**Batalha** (inalterada): `setbossbattle 4, SPECIES_NONE, 150`, nível 90;
Kartana Muscle Band / Swords Dance; Guzzlord Leftovers / Toxic; Nihilego Black
Sludge / Acid Spray. `B_FLAG_NO_CATCHING`; sem `B_FLAG_NO_WHITEOUT`. Qualquer
resultado que não seja vitória → retry. Parafusos em ordem no comentário do
`.pory`.

**Retry** (`UBLookerRetry` → `UBSceneRetry`): Looker "The lab is safe", Anabel
SIM/NÃO; SIM → trilha de ameaça, jogador ao posto (de (20,12) pela linha 12 ou
de (21,13) pela linha 13, `getplayerxy`), direto à escolha. Nada visto é
reapresentado; outra UB pode ser escolhida. `UBUnresolved` (Anabel: "The fronts
aren't clear yet") recarrega em (20,12).

---

## 5. Depois da vitória (V2 §11–§18)

| Beat | Script | O essencial |
|---|---|---|
| Defesa funciona | `UBResolved` + `UBAfter*` | trilha de volta; a UB do jogador enfraquecida (cry `CRY_MODE_WEAK`); **o jogador volta ao posto (16,12)** (três trajetos); Milotic e Snorlax fecham as frentes deles, um de cada vez |
| Campo | `UBFieldStarts` | Anabel e Lusamine; `UBFieldLine`; uma leitura (brilho + bipe) por UB; "!" do Elm; "The links have dropped"; Anabel vira para o alvo |
| Necrozma | `UBNecrozma` | detecção; distorção em (16,9); o campo **bloqueia** primeiro (reflexo nos emissores); lançamento; o pulso sobe; Elm "can't hold"; Azumarill (13,12)→(14,12) cobre e a Lusamine recua a (13,12); Ball repelida intacta; `SE_PC_OFF` (desligamento); as três resistem viradas para longe enquanto Snorlax e Milotic atacam os filamentos; viram luz no lugar |
| Ultra | `UBUltra` | troca de objeto no mesmo tile sob um clarão; silhueta antes do texto; pulso: jogador (16,12)→(16,13), Lusamine →(12,12), parceiros firmam; **instabilidade** (pulsos desiguais + brilho nas três aberturas pequenas) antes de qualquer parceiro; Lusamine "can't hold that light steady" |
| Parceiro | `UBPartner` | `CheckMysteryEggPokemon` depois da batalha; sai da Ball em (17,13) antes de qualquer fala; Ultra olha e continua oscilando. Cosmog/Cosmoem: Lusamine "Keep {STR_VAR_1} beside you"; Solgaleo/Lunala: faixa de luz até a retaguarda, "The edge is steady", rival "Bring {STR_VAR_1} back"; recolhido na tela. Em todos os ramos (inclusive sem família) o Azumarill dá o último passo atrás |
| Recuo | `UBRetreat` | pulso que falha; a abertura principal abre em (17,9); Ultra entra de costas; as três pequenas fecham depois; **nove bipes em grupos 2-2-2-3** e o diálogo dos nove; "All three openings are closed"; só então `fadedefaultbgm`; Milotic e Snorlax recolhidos; Looker confere a barricada |
| Rescaldo | `UBAftermath` | jogador a (16,12); Looker a (17,12); porta abre e a mãe sai a (10,10); rival vai ver o Azumarill (13,13), o jogador acena; rival e Azumarill vão conferir a cerca cortada (14,11)/(14,12); falas na ordem do V2 §16–§17 |
| Fim | `UBFinish` | narração sem plaquinha da transição ("By evening..."); `fadescreen`; limpa as duas flags; estado 10; `warpsilent` (20,12). **Sem** `FLAG_DAILY_LOOKER_CALL` |

---

## 6. Plaquinha do Gold/Crystal

`{SPEAKER NAME_NEIGHBOR}` (índice `0x10`, `SP_NAME_NEIGHBOR`). A plaquinha é
`{NEIGHBOR}`, placeholder novo (`FD 0F`, `PLACEHOLDER_ID_NEIGHBOR`,
`ExpandPlaceholder_Neighbor` em `src/string_util.c`): **Crystal** se o jogador é
menino, **Gold** se menina — a regra de `NewBarkTown_EventScript_RivalBattle`.
`{RIVAL}` continua sendo o Silver. `checar_falantes.py`: 17 falantes em ordem.

### 6.1 Sprite novo: o emissor da Aether

`OBJ_EVENT_GFX_AETHER_EMITTER` (337; `NUM_OBJ_EVENT_GFX` 338), escolhido pelo
autor entre três propostas (opção A, "poste com lente"). Poste 16×32 com lente,
4 quadros em loop (`sAnim_AetherEmitterLoop`: apagado 10 → aceso 8 → pico com
faísca 8 → aceso com a outra luz do poste 8), `inanimate`, sombra pequena.
Paleta própria (`OBJ_EVENT_PAL_TAG_AETHER_EMITTER` `0x116D`) tirada das peças de
New Bark ao lado dele — contorno ardósia `(65,74,106)`, brancos frios da caixa de
correio e da placa do laboratório, vidro azul-céu do poste de luz, creme das
placas — para parecer do mesmo cenário.

| Lugar | O quê |
|---|---|
| `graphics/object_events/pics/misc/aether_emitter.png` | 64×32, 4 bits, 4 quadros de 16×32 |
| `graphics/object_events/palettes/aether_emitter.pal` | JASC, mesma ordem de índices do PNG |
| `spritesheet_rules.mk` | `-mwidth 2 -mheight 4` (sem isto o quadro 0 sai vazio) |
| `include/constants/event_objects.h` | gfx 337, `NUM` 338, pal tag `0x116D` |
| `src/data/object_events/object_event_graphics.h` | `gObjectEventPic_/Pal_AetherEmitter` |
| `object_event_pic_tables.h`, `object_event_anims.h`, `object_event_graphics_info.h`, `..._pointers.h` | tabela de quadros, loop, graphics info, ponteiro |
| `src/event_object_movement.c` | `sObjectEventSpritePalettes[]` |

Conferido: o `.4bpp` gerado (1024 bytes) decodificado quadro a quadro bate com o
PNG pixel a pixel. **Runtime:** ver os dois emissores aparecendo e pulsando.

### 6.2 Sprite novo da Lusamine (DiegoWT, 32×32) — vale para o jogo inteiro

Pedido do autor em 26/09/2026: `OBJ_EVENT_GFX_LUSAMINE` passou a usar a arte de
DiegoWT (`.filetransfer/Lusamine Sprite Diego WT.png`, 256×256, arte ampliada
2×). Reduzida para **32×32** por moda de cada bloco 2×2, descida 1 px para os pés
ficarem nas linhas 30/31 como no sprite antigo, e com 15 cores (o cinza
`(48,48,56)`, 14 pixels, foi fundido no contorno preto).

**12 quadros**, não 9: a arte desenha a direita à parte, então em vez de espelhar
a esquerda há três quadros próprios para o leste e a tabela
`sAnimTable_StandardAsym` (`object_event_anims.h`, mesmos tempos da
`sAnimTable_Standard`). Ordem: 0 S, 1 N, 2 O, 3-4 passos S, 5-6 passos N, 7-8
passos O, 9 L, 10-11 passos L.

| Lugar | Mudança |
|---|---|
| `graphics/object_events/pics/people/special/lusamine.png` | 384×32, 12 quadros 32×32 |
| `spritesheet_rules.mk` | `-mwidth 4 -mheight 4` |
| `object_event_pic_tables.h` | `sPicTable_Lusamine` com 12 `overworld_frame(…, 4, 4, i)` |
| `object_event_anims.h` | `sAnimTable_StandardAsym` + quatro animações do leste |
| `object_event_graphics_info.h` | 512 bytes, 32×32, OAM 32×32 |

Conferido: build limpo; `.4bpp` de 6144 bytes decodificado quadro a quadro bate
com o PNG. Aparece em **New Bark, `OlivineCity_House1` e `SunMoonAltar`**. Olhar
em runtime: os quatro lados, andando; no cerco de New Bark (15,13) o cabelo
encosta na mãe e no Nihilego, e no rescaldo (12,12) fica colado ao emissor oeste
— legível, mas mais apertado.

---

## 7. Pedido do V2 → como ficou

| V2 | Como ficou |
|---|---|
| §3 ligação diária, espera, convite persistente | Já existia (M3); textos do V2 |
| §4 briefing sem "Take these", recurso apresentado antes | 5 caixas; Lusamine anunciada com o equipamento |
| §5 sem fila de seis diante da casa; (20,12) livre | Elenco espalhado por laboratório, corredor, controle e casa; ninguém para em (20,12) |
| §5 equipamento sem gastar slots de NPC | Emissores são objetos com sprite próprio (`OBJ_EVENT_GFX_AETHER_EMITTER`, §6.1), distinto do estojo do estabilizador e da fenda; **barreiras** em metatile |
| §6 conversas curtas; cura da mãe; bilhete só nas portas fechadas | Sim; lab e casa abertos |
| §7 formação, emissores posicionados, teste de luz, parceiros com Ball e cry | Sim |
| §8 três comportamentos distintos, sem sincronia | Corte (metatile), destruição (metatile + avanço), deriva até a mãe; cries separados |
| §9 decisão curta; mãe entra com o Looker; porta fecha depois dos dois | Sim |
| §10 menu ANABEL sem B; tabela de frentes; rival no overworld | Sim, três ramos de movimentação |
| §11 UB enfraquecida primeiro; parceiros um de cada vez; leitura antes do sucesso; Ball policial | Sim; o jogador volta ao posto de comando ("retorna à cena depois da batalha", §21) |
| §12 campo bloqueia primeiro; falha visível; Ball repelida; desligamento | Sim. A abertura do Necrozma é uma **distorção** (orçamento, §1.3) |
| §13 Ultra no mesmo tile, sem sobreposição; recuo sem derrota jogável; instabilidade independente | Sim |
| §14 todos os ramos do parceiro | Sim, com recolhimento na tela |
| §15 recuo pela abertura principal; nove padrões comparados | Abertura como objeto só aqui; bipes 2-2-2-3 + falas |
| §16–§17 rescaldo e gancho | Falas do V2, cada falante visível acima da caixa |
| §18 estado 10; limpar tudo; reparo com transição explícita; reunião com ligação própria | Narração da transição + warp; espera `WaitForAltarCall`; ligação pode tocar no mesmo dia |
| §19 retry preserva introdução; cura acessível sem atravessar frente | `ENGAGED`; mãe cura no laboratório (e a máquina do Elm também cura) |
| §20 asset do Ultra Necrozma | Já resolvido no código: `OW_BATTLE_ONLY_FORMS_NECROZMA_ULTRA TRUE` compila o sprite próprio sem ligar todas as formas de batalha |
| §21 trilha, flashes, olhares | `fadeoutbgm` no aviso, `playbgm` antes da revelação e depois da batalha, `fadedefaultbgm` depois do fechamento; flashes com `fadescreenswapbuffers` |
| Rival `{RIVAL_NAME}` | `NAME_NEIGHBOR` (§6) |

---

## 8. Arquivos tocados

| Arquivo | Mudança |
|---|---|
| `include/constants/flags.h` | `FLAG_NEWBARK_UB_ENGAGED 0x1050`; `CUSTOM_FLAGS_END`; comentário da flag do evento |
| `include/constants/characters.h`, `charmap.txt`, `src/string_util.c`, `src/strings.c`, `include/strings.h` | Placeholder `{NEIGHBOR}` |
| `include/constants/speaker_names.h`, `src/data/speaker_names.h`, `charmap.txt` | Falante `NAME_NEIGHBOR` |
| `src/field_control_avatar.c`, `include/event_scripts.h` | `openDoorMap2`; linha de New Bark |
| Sprite do emissor (9 lugares, §6.1) | `OBJ_EVENT_GFX_AETHER_EMITTER` |
| Sprite da Lusamine 32×32 (§6.2) | PNG, regra, pic table, `sAnimTable_StandardAsym`, graphics info |
| `data/maps/NewBarkTown/map.json` | Elenco 16–27 reposicionado/re-flagado; 28–36 novos (Snorlax, Milotic, 2 emissores, abertura, 4 parceiros) |
| `data/maps/NewBarkTown/scripts.pory` | `ON_LOAD` chama as barreiras; bloco da M4 e textos reescritos inteiros |
| `data/maps/NewBarkTown_Lab/map.json`, `scripts.pory` | Mãe abrigada + cura |
| `data/maps/OlivineCity_House1/scripts.pory` | Briefing M4, "vá na frente", espera do estado 10 |
| `data/scripts/rift_missions.inc` | Texto da ligação da reunião; comentários da exceção do daily |
| `docs/SOULGOLD_FLAGS_AUDIT.csv` | Regenerado |

---

## 9. Conferido (26/09/2026)

- `make -j$(nproc)` limpo.
- `checar_falantes.py`: 17 falantes em ordem (os 18 prefixos "Elm: " do
  laboratório são vanilla, já estavam no HEAD).
- `medir_linha.py` em New Bark, Olivine, laboratório e `rift_missions.inc`:
  nada acima de 208 px.
- **30 trajetórias simuladas** contra a colisão real, com a cerca e a barricada
  aplicadas: todas só em tiles andáveis (a porta (10,9) é entrada roteirizada).
- Quadros renderizados (prep, operação, cerco, escolha, Necrozma, rescaldo) para
  sobreposição dos 32×32; ajustes: Anabel para (18,14), Nihilego por x=13, as
  UBs resistem sem arrasto (o arrasto do Nihilego cobria a Lusamine).
- `flag_audit.py --csv`: `FLAG_NEWBARK_UB_ENGAGED` `CUSTOM`, `EM_USO`, lida e
  escrita.
- `map_event_ids.h` gerado: locais 16–36 em New Bark, `LOCALID_NEWBARK_LAB_MOM 6`.
- Nenhuma referência sobrando a rótulos removidos.

---

## 10. Runtime — checklist

Nada foi jogado. Ordem para achar cedo o que quebra mais coisas:

1. Estado 8 sem ligação: Olivine só dá a espera; ligação no dia seguinte; briefing de 5 caixas → estado 9.
2. New Bark por Fly: chega em (20,12); elenco nos tiles; cerca e toras desenhadas; portas das casas trancadas com bilhete, laboratório e casa abertos; nenhum segundo Gold/Crystal. **Repetir à noite.**
3. Conversas da prep; cura da mãe com NÃO.
4. SIM: emissores aparecendo; teste de luz; Snorlax/Milotic.
5. As três aberturas; o corte da cerca e as toras sumindo **na hora**; a mãe atravessando e o Nihilego chegando **depois** dela.
6. Mãe × Lusamine; mãe e Looker entrando; Looker voltando a (21,12).
7. **Contar sprites e paletas** nesse ponto (pico): ninguém invisível nem com cor errada.
8. Cada escolha (3): parceiros trocando de frente sem se atravessar; o jogador no alvo.
9. Perder de propósito: blackout curado em (20,12); rua montada (cerca cortada, toras quebradas); mãe no laboratório com a cura; Looker e Anabel no retry; escolher outra UB.
10. Vencer nos três ramos: volta ao posto; campo; Necrozma; Ball repelida; absorção; Ultra com sprite próprio (sem Substitute); instabilidade; recuo pela abertura.
11. Parceiro: sem família, Cosmog, Cosmoem, Solgaleo, Lunala (e um que evolui na batalha).
12. Rescaldo e fim: follower volta; moradores; mãe em casa e Elm no laboratório; cerca e toras sumidas; estado 10.
13. Ligação da reunião: mesmo dia se a de New Bark foi em outro; senão no dia seguinte. Espera `WaitForAltarCall` antes dela.
14. Salvar/recarregar nos estados 8, 9 (antes e depois do checkpoint) e 10; entrar por Route 29 e Route 27.

---

## 11. Riscos conhecidos

- **Orçamento de objetos no limite (15/16) e paletas (~14 + efeitos).** Se algo
  não aparecer, é aqui; a primeira alavanca é esconder o Elm durante o cerco.
- **Ramo Guzzlord** tira Looker, Elm e rival da janela de spawn; eles voltam do
  template (sincronizado). Se algum reaparecer no lugar errado, faltou
  `setobjectxyperm`.
- `setmetatile` no `ON_LOAD` depende de `ON_LOAD` rodar na volta da batalha
  (`InitMapFromSavedGame`, lido no código).
- x150 nunca foi jogado (herda correção da M3 se x140 for parede).
- A abertura da reunião (`OlivineCity_House1_Text_ReunionOpen`) ainda é da M4
  antiga; o V2 da reunião deve partir dos contratos do V2 §22.

## 12. O que não pode regredir

- Estado 8/9/10 e a invariante flag ⇔ 9; `ENGAGED` setada só em `UBChoose`.
- (20,12) nunca ocupado por ator; talk do Looker na prep só de (20,12).
- Uma `FLAG_TEMP` própria por ator removível; `FLAG_TEMP_HIDE_FOLLOWER` no SIM e no retry.
- Barreiras só por `setmetatile` enquanto o evento está ativo; nada no `map.bin`.
- Normal e Ultra nunca juntos; abertura principal só depois da absorção.
- Instabilidade mostrada antes e independente do parceiro; nenhuma derrota jogável.
- A M4 **não** seta `FLAG_DAILY_LOOKER_CALL`.
- Mãe nunca em dois lugares (rua / laboratório / casa).
