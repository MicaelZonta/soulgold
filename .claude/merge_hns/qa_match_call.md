# QA no jogo — Match Call GSC (24/10/2026)

ROM: `Soulgold.gba` do build limpo (ELF do mesmo build). mGBA headless (`.claude/qa`), evidencia em
`/tmp/qa/ev/`, savestates em `/tmp/qa/st/`. Ninguem editou codigo do jogo.

## Atalhos de RAM usados (declarados)

- Nao joguei a introducao: usei o `Soulgold.sav` de desenvolvimento ja existente (Route 30, party com
  Chespin, 3:47 de jogo, 0 insignias). Ligados por `flag.py`: `FLAG_HAS_MATCH_CALL`, `FLAG_BADGE01..03_GET`,
  `FLAG_SYS_POKEDEX_GET`, `FLAG_RECEIVED_FIRST_BALLS` (esta ultima so para o botao DexNav aparecer) e
  limpa `FLAG_HIDE_ROUTE_30_NPCS` (a mae em New Bark nao foi testada).
- T08: `FLAG_WADE_HAS_PHONE_ITEM`=1 e `VAR_WADE_PHONE_ITEM`=520 (ITEM_ORAN_BERRY) escritos na RAM.
- T08b: bolso de berries enchido com `Fill Pocket Berries` (67/70) e os 3 slots vazios + o slot da Oran
  reescritos na RAM com Persim Berry (70/70, Oran ausente). Bolsa cheia de verdade, sem a Oran.
- Batalhas: Instant Win do debug de batalha (SELECT abre o menu; Instant Win e o ultimo item).

## Consertado depois deste QA (24/10/2026, mesmo dia)

As tres observacoes que eram do codigo novo foram corrigidas logo apos o
relatorio; **nenhuma foi retestada no jogo** (ficam para o proximo passe):

| Observacao | Conserto |
|---|---|
| Lupa do DexNav vira bolinha preta; o cabo branco some na borda do botao | Icone redesenhado: lente branca, aro escuro, contorno branco e cabo escuro com borda branca (`graphics/pokegear/icon_dexnav.png`), no mesmo estilo dos outros |
| Tracinho de ~5 px pendurado no topo depois do `\p`/`\l` | O texto da ligacao passou a comecar em `y = 0`: o `\l` rola exatamente 16 px (altura da FONT_NORMAL), entao qualquer margem no topo deixava as duas primeiras linhas de pixel da pagina anterior |
| Barra de ajuda diz "A Call" com a agenda vazia | Com zero contatos a barra mostra so "{B_BUTTON}Back" |

As observacoes 4 (fala pos-batalha sem plaquinha) e 5 (cabelo rosa do Brock de
campo) **nao** foram mexidas: a 4 e um padrao do jogo inteiro (texto de
treinador nunca teve plaquinha fora da fala de entrada) e a 5 e grafico de NPC,
fora do telefone.

## Resultados

| Teste | Resultado | Evidencia |
|---|---|---|
| T01 menu com 5 botoes | PASS com observacao | `T01_pokegear_x4.png`, `T01_icon_dex.png`, `T01_icon_phone.png` |
| T02 agenda vazia | PASS | `T02_vazia.png`, `T02_voltou_B.png` |
| T03 pedir o numero | PASS | `T03_fala.png`, `T03_registered.png` (+ `T03_a_*`, `T03_d_*`, `T03_e_*`) |
| T04 agenda lista | PASS | `T04_agenda.png` |
| T05 ligar | PASS com observacao | `T05_plaquinha_joey.png`, `T05_p2..p6.png`, `T05_obs_pixel_solto.png` |
| T06 ligacao de rota (255 passos) | PASS | `T06_ligacao_01..07.png` |
| T07 revanche | PASS | `T07_batalha_time.png`, `T07_01/02.png`, `T07_pos_*.png` |
| T08a bolsa com espaco | PASS | `T08a_01..06.png` |
| T08b bolsa cheia | PASS | `T08b_01..06.png` |
| T09 texto do Kanto | PASS | `T09_brock_01..08.png`, `T09_win_0*.png`, `T09_estatua.png` |

### T01
Cinco botoes (Map, DexNav, Trophies, Radio, Phone), nenhum na faixa laranja nem no cabecalho, texto dentro
dos botoes, celular no Phone, lupa no DexNav. Observacao: a lupa e um disco preto cheio com aro branco; o
cabo e branco sobre a borda branca do botao e some. Le-se como "bolinha com aro", nao claramente como lupa
(`T01_icon_dex.png`, ampliado 12x). Sem `FLAG_RECEIVED_FIRST_BALLS` o botao DexNav nao aparece (so 4 botoes):
e a regra do jogo, nao defeito.

### T02
Sem numeros: "No numbers yet. / Beat a trainer and they may ask for your number." B volta ao menu com o cursor
em Phone. Observacao menor: a barra de ajuda continua mostrando "A Call" com a lista vazia.

### T03
Joey viu o jogador (visao) e puxou a batalha: "I just lost, so I'm trying to find more Pokémon..." com
plaquinha "Joey". Depois da vitoria: "You're pretty good! ..." (4 paginas), e "Registered Youngster Joey
in the Pokégear." `FLAG_REGISTERED_JOEY` 0 -> 1. (Aviso de roteiro: o Joey nao fica parado em (20,28) esperando
`ir.py`; a visao dele dispara a batalha no caminho e ele anda ate o jogador. A primeira vez isso aconteceu
no meio de um `ir.py` e foi desfeito: refiz do savestate.)

### T04
Phone lista "Youngster Joey". Mais tarde, com o item do Wade forcado, a lista mostra "Bug Catcher Wade" com
"!" (`T08_agenda_exclamacao.png`) e o Joey sem "!" depois da revanche.

### T05
Som nao verificado (headless). Plaquinha "Joey" correta (nao lixo). Fala: "Yo, A! How're you doing?" / "I'm
checking out Rattata's moves and devising some strategies." / "When I come up with a good one, let's battle!"
(o jogador se chama "A"; Rattata e o Pokemon do time). A no fim desliga e volta a lista; A de novo na lista
liga outra fala ("Yo, A! Got a minute?"). B no meio so avanca a pagina, nao desliga (consistente com texto).
Observacao: na 2a pagina de varias ligacoes da agenda fica um pixel solto (traco horizontal, ~5 px) acima da
primeira linha de texto, resto do descendente do "g" de "checking" da pagina anterior apos o scroll do `\p`
(`T05_obs_pixel_solto.png`, reproduzido 2 vezes). Cosmetico.

### T06
Contador `VAR_ROUTE_STEP_COUNTER` lido da RAM: partiu de 55, subiu 1 por passo ate 254; no 255o passo zerou e
a janela de ligacao tocou sozinha: icone de celular + "..........", depois plaquinha "Joey": "Yo, A!" /
"Let's get together and battle!" / "I promise things will be different!". Foram ~255 passos no mesmo mapa
(Route 30, ida e volta (20,31)<->(20,36)), 3 insignias, Joey registrado e derrotado. Nenhuma ligacao do vanilla
(30 passos) tocou antes nesse trecho.

### T07
Falando com o Joey: "I promised things would be different! Let's battle!". Time na batalha: Rattata **Lv27**
(trainers.party `TRAINER_JOEY_2`: Rattata Lv27 com Silk Scarf), contra Lv5 da primeira vez. Derrota: "Ack! I lost
again!", ₽432 (era ₽80). Depois: "I'm checking out my Rattata's moves...".

### T08a
Fala com o Wade: "Hey! I've been looking for you!" / "I found something while I was in the grass." / "Here, you
can have it!" -> "Obtained the Oran Berry!" Oran 1 -> 2 (`bolsa.py`), `FLAG_WADE_HAS_PHONE_ITEM` 1 -> 0,
"I'll let you know if I find anything else!". Pela agenda, ligar para o Wade com o item pendente tambem
funciona e mostra a fala do item (plaquinha "Wade").

### T08b
Bolso 70/70, sem Oran: "Hmm, looks like your Bag is full." / "Come back when you have room!". Oran continua
ausente, `FLAG_WADE_HAS_PHONE_ITEM` = **1** e `VAR_WADE_PHONE_ITEM` = 520. O item nao some.

### T09
Pewter City Gym: Jerry com plaquinha "Jerry" e "Rock-type Pokémon". Brock com plaquinha "Brock":
"I'm an expert on Rock-type Pokémon.", "My Pokémon are impervious...". Depois da vitoria: "A received
Boulderbadge." (decapado) e fala dele com plaquinha; a fala de derrota dentro da batalha mantem o prefixo
"Brock: ..." (proposital). Placa da estatua: "Pewter Pokémon Gym / Leader: Brock".

## Defeitos do jogo

Nenhum defeito funcional encontrado nos testes executados.

## Observacoes

1. Lupa do DexNav pouco legivel (T01).
2. Pixel solto na 2a pagina de ligacao da agenda (T05) — cosmetico.
3. Barra de ajuda "A Call" aparece na agenda vazia (T02).
4. Falas de script dos treinadores pos-batalha (Joey: "You're pretty good!...", pos-revanche; Wade: "You're
   awesome!...") nao tem plaquinha; as de antes da batalha, tem. Nao ha "Nome:" no texto original, entao nao
   e regressao do passe K8; so inconsistencia visual.
5. Sprite de campo do Brock no ginasio tem cabelo rosa (o mugshot/front pic na batalha e o Brock normal) —
   fora do escopo do telefone.
6. Roteiro/ferramenta: coordenadas do Joey/Wade sao as de spawn, eles andam ate o jogador pela visao;
   macros `fill`/`warp` do `lib.sh` assumem indices antigos do menu de debug (usei a sequencia manual);
   `go.sh` com Instant Win precisa de espera antes do SELECT (SELECT na intro da batalha nao abre o menu).
7. Ambiente: sem `pip`/Lua dev no container; instalei Pillow com get-pip `--user` e compilei o Lua 5.4.7 em
   `/tmp/luadeb` para o `setup.sh` achar o Lua. Nada no repo.

## Nao testado

- Introducao e a mae entregando o Pokegear (flags ligadas por RAM; Route 30 NPCs idem).
- Corte de insignias (<3 nao liga): nao rodei o caso negativo.
- Sorteio de 1/5 de item na ligacao de rota e a ligacao aleatoria do vanilla (30 passos/10 min/30%).
- Lista com mais de 5 entradas (rolagem) e os outros 38 treinadores; revanches 3 a 5.
- Som de ligacao (headless).
- Item do Wade com pilha em 999 (so testei bolso cheio com item ausente).
