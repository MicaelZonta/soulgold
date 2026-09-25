# Kurt — a economia de Poké Balls por receitas

**Status:** **IMPLEMENTADO — revisão 4** (24/09/2026). O sistema inteiro está no
código e a `make` fecha limpa; o que falta é **teste em runtime**. A revisão 4 é o
retorno da implementação, e está toda no **§8**.
**A pendência 1 do §7 está respondida, e a resposta é SIM:** `checkitem`,
`removeitem` e `checkitemspace` fazem `VarGet` nos **dois** argumentos
(`src/scrcmd.c:632-673`), então a quantidade pode ser var e a sub-rotina genérica
do §2.8 é possível. Ela foi escrita, e as 27 receitas são duas linhas cada.
A única coisa que sobra no §7 é a Fase 2 dos apricorns, que é documento próprio.
**Protótipo interativo:** <https://claude.ai/artifact/9J1xo2D9jW6XppCdBFAxvP>
**Design de referência:** [`ALTAR_SUN_MOON_IMPLEMENTATION.md`](rift_missions/ALTAR_SUN_MOON/ALTAR_SUN_MOON_IMPLEMENTATION.md)
§10.3 (a Anabel manda o jogador ao Kurt) e
[`SOULGOLD_RIFT_MISSIONS_DESIGN.md`](rift_missions/SOULGOLD_RIFT_MISSIONS_DESIGN.md) §14.
Este documento nasceu quando a loja de Beast Balls da Anabel foi substituída por
"ela te manda ao Kurt", e o único acoplamento entre os dois continua sendo **uma
caixa de fala** — mais, desde a rev3, **uma leitura** de `VAR_RIFT_MISSIONS_STATE`.

**O que cada revisão decidiu:**

| Rev | Data | Decisões |
|---|---|---|
| 1 | 23/09 | A auditoria (§1) e a primeira proposta: 10 níveis, EXP por bola, 100 de teto |
| 2 | 23/09 | Lojas só com Poké Ball; sorteio mantido sem EXP; toda bola com receita; 20 níveis; EXP por **lote**; 190 dias |
| **3** | **24/09** | **EXP por bola** de novo e **32 dias** (o autor pediu "uns 30"); **Beast Ball destranca pelo Necrozma**, não por nível; **Master Ball sem receita, só na sorte do sorteio**; **Berry Master na `Route30_House`**, escolha do autor, "para já fazer o sistema cedo". **Fechada no mesmo dia:** gate da face 16 em `>= 360`, cota inicial de 1 lote, e o Berry Master aprovado como desenhado |
| **4** | **24/09** | **Implementado.** A pendência das macros respondida (sim, aceitam var), a sub-rotina genérica escrita, a colisão de daily flag com o doc do altar resolvida, o Berry Master reusando uma flag que já existia, e seis achados da escrita — todos no §8 |

O pedido original do autor, em quatro frases:

1. Todas as bolas que o Kurt faz deviam ser refazíveis N vezes — **analisar se
   isso é verdade hoje**, e se não for, transformar em loop infinito.
2. **Tirar Poké Balls de lojas e de presentes de história.** Loja vende Poké Ball
   e mais nada.
3. **O Kurt passa a ser responsável por todas as bolas, via receitas, N por dia.**
4. **Níveis de EXP numa var só**, `EXP += 1` por bola feita.

O objetivo declarado, que governa todos os números deste documento: **o jogo é
para ser lento** — um forever game em que farmar berries e criar Pokémon valem a
pena.

---

## 1. Análise: é verdade que o Kurt já faz bolas infinitas?

**Resposta curta: em parte, e a parte que funciona está inalcançável.**

O Kurt tem **dois** sistemas hoje, e eles não se falam.

### 1.1 O sorteio diário — funciona, e é a única coisa que funciona

`KurtDaily` (`data/maps/AzaleaTown_KurtsHouse/scripts.pory:530`):

- Trancado por `FLAG_DAILY_KURT_FREE_BALLS` (`DAILY_FLAGS_START + 0x19`): **uma
  vez por dia**, e a daily flag zera sozinha na virada da data.
- `random(15)` — ou `random(16)` se `VAR_KURT_PROFICIENCY >= 4` — e entrega
  **5 unidades** de uma de 15 bolas sorteadas, ou **1 Master Ball** no caso 15.
- `VAR_KURT_PROFICIENCY` (`0x40DF`) **incrementa 1 por dia**, teto 255. Hoje ela
  significa "dias em que ele fez bolas para você", e o **único** efeito dela é
  abrir a 16ª face do dado (a Master Ball) a partir de 4.
- É **de graça**: não consome item nenhum.

Bolas que só existem por aqui: Luxury, Level, Lure, Moon, Friend, Love, Fast,
Heavy, Dream, Safari, Sport, Park, **Beast**, Cherish, Strange, Master.

### 1.2 O crafting por berries — escrito para ser infinito, e é **código morto**

Existem sete receitas escritas, e a mecânica delas é **exatamente** o loop
infinito que o autor quer: `checkitem <berry>, 5` → animação → `giveitem <bola>, 5`
→ `removeitem <berry>, 5`. **Sem flag, sem limite diário, repetível para sempre**
enquanto houver berries.

| Receita | Ingrediente |
|---|---|
| Love Ball ×5 | 5 Pecha Berry |
| Lure Ball ×5 | 5 Rawst Berry |
| Friend Ball ×5 | 5 Cheri Berry |
| Heavy Ball ×5 | 5 Oran Berry |
| Moon Ball ×5 | 5 Chesto Berry |
| Fast Ball ×5 | 5 Aspear Berry |
| Level Ball ×5 | 5 Persim Berry |

**Mas ninguém consegue chegar lá.** O menu é
`AzaleaTown_KurtsHouse_EventScript_Kurt2` (`scripts.inc:230`), e o script de
objeto do Kurt é:

```asm
AzaleaTown_KurtsHouse_EventScript_Kurt::
	lock
	faceplayer
	goto_if_eq VAR_AZALEA_TOWN_STATE, 8, ..._KurtGsBall2
	goto_if_eq VAR_AZALEA_TOWN_STATE, 9, ..._KurtGsBall3
	call_if_unset FLAG_CAUGHT_CELEBI, ..._KurtCheckGSBall
	goto KurtDaily                 @ <- sai aqui, SEMPRE
	AzaleaTown_KurtsHouse_EventScript_Kurt2::     @ <- e nunca chega aqui
		multichoice 20, 0, MULTI_KURT_BALLS, FALSE
```

O `goto KurtDaily` é incondicional e `KurtDaily` termina em `release`/`end`.
A única coisa no repositório que chama `Kurt2` é
`AzaleaTown_KurtsHouse_EventScript_DontHaveBerry` (`scripts.inc:602`) — que só é
alcançável **de dentro** de uma receita. É um ciclo fechado sem porta de entrada.

**Conclusão da análise:** o crafting infinito do Kurt não é uma coisa a construir,
é uma coisa a **religar** — e a ligar direito, porque tem um bug esperando (§1.3).

### 1.3 Bug encontrado: as sete receitas comem a berry quando a bolsa está cheia

Em todas as sete, nesta ordem:

```asm
	giveitem ITEM_LOVE_BALL, 5
	removeitem ITEM_PECHA_BERRY, 5
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
```

`removeitem` **escreve `VAR_RESULT`**. A guarda de bolsa cheia lê o resultado do
`removeitem`, não o do `giveitem`. Com a bolsa cheia: o `giveitem` falha
(`VAR_RESULT = FALSE`), o `removeitem` tira as cinco berries e devolve `TRUE`, a
guarda passa, e **o jogador perde cinco berries e não recebe nada**. Build limpo,
sintoma só em save com bolsa cheia.

Ordem correta, e vale para todas as receitas novas:

```asm
	checkitemspace ITEM_LOVE_BALL, 5
	goto_if_eq VAR_RESULT, FALSE, ..._BagFull       @ antes de qualquer consumo
	removeitem ITEM_PECHA_BERRY, 5
	giveitem ITEM_LOVE_BALL, 5
	goto_if_eq VAR_RESULT, FALSE, ..._BagFull       @ guarda defensiva
```

É a mesma regra da skill `entregar-pokemon-ou-ovo` aplicada a item: **conferir
espaço antes de consumir**, e nunca ler `VAR_RESULT` depois de outra chamada.

### 1.4 De onde vêm as bolas hoje — inventário completo

Lojas usam duas fontes. A principal é `pokemart 0`, que cai em
`sShopInventories[GetNumberOfBadges()]` (`src/shop.c:319` e `:842`) — uma tabela
**única para todo o jogo**, indexada por insígnias:

| Insígnias | Bolas na lista |
|---|---|
| 0 | Poké Ball |
| 1 a 4 | Poké Ball, Great Ball |
| 5 a 8 | Poké Ball, Great Ball, Ultra Ball |

A segunda são os **balcões especiais** de cada cidade (a lista de TMs), cada um
com uma ou quatro bolas:

| Loja | Bolas |
|---|---|
| Cherrygrove | Heal |
| Violet | Heal, Net, Nest |
| Azalea | Nest |
| Ecruteak | Quick, Net, Timer |
| Olivine | Dive, Level, Net |
| Blackthorn | Quick, Dusk, Premier, Luxury |
| Rinto Village | Dusk, Quick |
| Battle Frontier | Safari |
| Liga (EverGrande 1F) | Ultra |

Presentes de história em Johto/Kanto, fora da casa do Kurt:

| Onde | O quê |
|---|---|
| `NewBarkTown_Lab` | Poké Ball ×10 e **Master Ball** ×1 |
| `Route31` | Poké Ball (item no chão) |
| `Gate_NationalPark` | Safari Ball ×30 (×4 pontos — é a mecânica do Safari) |
| `AzaleaTown` | **GS Ball** (item de história, não é bola de captura) |
| `EcruteakCity_Gym` | TM Shadow Ball (não é bola) |
| `VajraDesertEast` | Beast Ball (item no chão) |
| `GoldenrodBattleArcadeLobby` | Master Ball (prêmio de BP) |

As lojas de Hoenn (`gMapGroup_Emerald1/2`) também vendem bolas, mas aqueles mapas
não fazem parte da campanha; ficam **fora de escopo** e não se mexe nelas.

### 1.5 Apricorns: os itens existem, o mundo não

Existem 13 `ITEM_*_APRICORN` (`include/constants/items.h:250`), existe
`OBJ_EVENT_GFX_APRICORN_TREE`, existe `src/apricorn_tree.c` e existe
`gApricornTrees` — mas `APRICORN_TREE_COUNT` é **0**
(`include/constants/apricorn_tree.h:88`), a tabela só tem a entrada `NONE`, e
**nenhum mapa** referencia apricorn. Ou seja: **apricorn não é obtenível no jogo
hoje**, e o Kurt já usa berries justamente por isso.

Berries, em contraste, são abundantes: **418 objetos de árvore de berry** nos
mapas, mais as berries de EV vendidas em Goldenrod 3F e na floricultura.

**Decisão:** a proposta usa **berries** na Fase 1. Ligar as árvores de apricorn é
um documento próprio (§7, pendência 1), e a tabela de receitas foi desenhada para
que a coluna de ingrediente possa ser trocada sem tocar em nada mais.


### 1.6 Auditoria de berries: 22 das 67 não têm fonte nenhuma

O autor pediu que **todas** as berries fossem obteníveis. Varredura de lojas,
presentes e itens de chão em `data/maps/`, `data/scripts/` e `data/event_scripts.s`:

**Fontes que existem e são alcançáveis em Johto/Kanto:**

| Fonte | Berries |
|---|---|
| NPC de Violet City | Aguav, Aspear, Cheri, Chesto, Iapapa, Leppa, Lum, Oran, Pecha, Rawst, Sitrus, Wiki — **12** |
| Floricultura de Goldenrod (loja) | Babiri, Charti, Chilan, Chople, Coba, Colbur, Haban, Kasib, Kebia, Occa, Passho, Payapa, Rindo, Roseli, Shuca, Tanga, Wacan, Yache — **18** |
| Goldenrod Dept. Store 3F (loja) | Grepa, Hondew, Kelpsy, Pomeg, Qualot, Tamato — **6** |
| Chão | Leppa (`UnionCave_1F`), Sitrus (`Route49`) |
| `BattleFrontier_ScottsHouse` | Lansat, Starf — pós-game |

**Fontes que NÃO contam** porque os mapas não fazem parte da campanha:
Figy (Sootopolis), Razz (Route 111), Belue/Durin/Pamtre/Spelon/Watmel (Berry
Master's House da Route 123).

**As 22 sem fonte nenhuma:**

> Persim, Mago, Bluk, Nanab, Wepear, Pinap, Cornn, Magost, Rabuta, Nomel,
> Liechi, Ganlon, Salac, Petaya, Apicot, Enigma, Micle, Custap, Jaboca, Rowap,
> Kee, Maranga

**A Persim está nessa lista, e ela é a receita canônica da Level Ball** — a que o
código morto do Kurt já usa. Ou seja: a receita mais antiga dele é
**inexecutável** hoje, mesmo se o menu fosse religado.

**Árvores de berry começam vazias.** `ClearBerryTrees` (`src/berry.c:1869`) zera
as 139 vagas no New Game: elas são **solo**, não árvores plantadas. Toda berry do
jogo vem de uma fonte externa e é **multiplicada plantando**. Isso é exatamente o
que faz o custo em berries virar um sistema de fazenda em vez de um imposto — ver
§3.3.

---

## 2. A proposta

### 2.1 Regra de ouro: o Kurt é a única fábrica

| Quem | Vende / faz | Muda? |
|---|---|---|
| **Todas as lojas** | **Poké Ball, e só** | `sShopInventories` perde Great e Ultra nas 18 listas; os 9 balcões especiais perdem as bolas deles |
| **Kurt — receitas** | **27 bolas**: 26 por nível + a Beast Ball por história | novo |
| **Kurt — sorteio diário** | 5 de uma bola sorteada, de graça, 1×/dia | **mantido**, e **não dá EXP** |
| **Laboratório do Elm** | Poké Ball ×10 e Master Ball | **mantidos** |
| **Gate do Parque Nacional** | Safari Ball ×30 | **mantido** — é o minijogo |
| **Qualquer bola no chão ou de qualquer outra fonte** | — | **vira Poké Ball** |
| **Anabel no altar** | nada | manda o jogador ao Kurt |

Decisões do autor que isso fixa:

- **O sorteio diário fica, e não dá EXP.** É o piso de segurança: mesmo quem nunca
  fabricou nada recebe 5 bolas por dia. E como não dá EXP, ele não compete com as
  receitas — quem quer subir de nível tem de trabalhar.
- **A Master Ball e as 10 Poké Balls do Elm ficam.** São presentes de abertura de
  história, não economia.
- **Toda outra fonte de bola vira Poké Ball.** Inclui a Beast Ball do chão de
  `VajraDesertEast` e a Master Ball do prêmio do Battle Arcade.
- **E toda bola tem receita.** Inclusive a Poké Ball (nível 1, a mais barata) e a
  **Strange Ball** (nível 20, a última — o troféu de quem terminou a árvore).
  Única exceção: a **GS Ball**, que é item de trama e não se fabrica.

### 2.2 EXP por bola, 20 níveis, e a resposta sobre o teto de 100

**"Tem como fazer mais XP que 100 e ter mais níveis, sem gastar mais flags nem
nada?" — sim, e sem gastar nada.**

`VAR_KURT_PROFICIENCY` é uma entrada de `u16 vars[VARS_COUNT]`
(`include/global.h:1175`). O teto real dela é **65535**, não 100 — o 100 era
escolha minha, não limite do motor. Dá para usar qualquer curva sem alocar **uma
var, uma flag ou um byte de saveblock a mais**. O único custo são as 20 linhas da
escada de `goto_if_ge` que converte EXP em nível, lida uma vez por conversa.

**As três mudanças de ritmo que a rev3 fixa:**

| | rev1 | rev2 | **rev3 (esta)** |
|---|---|---|---|
| EXP | +1 por bola | +1 por lote | **+1 por bola** |
| Níveis | 10 | 20 | **20** |
| Nível 20 em | ~7 dias | 190 dias | **32 dias** |
| EXP máxima | 100 | 1900 | **1520** |

**A curva:**

```
EXP necessária para o nível L  =  4 · L · (L - 1)
lotes por dia                  =  nível
bolas por lote                 =  5      (todas, sem exceção)
EXP ganha por lote             =  5
```

O intervalo entre dois níveis é `8 × L` e a produção diária é `5 × L`, então
**cada nível custa 1,6 dia** no ritmo máximo e os dois crescem juntos. Simulado:
**32 dias, 304 lotes, 1520 bolas e 929 berries** do nível 1 ao 20.

| Nível | EXP | Lotes/dia | Berries/lote |
|---|---|---|---|
| 1 | 0 | 1 | 5 |
| 2 | 8 | 2 | 5 |
| 3 | 24 | 3 | 5 |
| 4 | 48 | 4 | 5 |
| 5 | 80 | 5 | 5 |
| 6 | 120 | 6 | 4 |
| 7 | 168 | 7 | 4 |
| 8 | 224 | 8 | 4 |
| 9 | 288 | 9 | 4 |
| 10 | 360 | 10 | 4 |
| 11 | 440 | 11 | 3 |
| 12 | 528 | 12 | 3 |
| 13 | 624 | 13 | 3 |
| 14 | 728 | 14 | 3 |
| 15 | 840 | 15 | 3 |
| 16 | 960 | 16 | 2 |
| 17 | 1088 | 17 | 2 |
| 18 | 1224 | 18 | 2 |
| 19 | 1368 | 19 | 2 |
| **20** | **1520** | **20** | **2** |

**O botão de ritmo é o 4.** `EXP(L) = K · L · (L-1)`: K=3 dá 25 dias, **K=4 dá
32**, K=5 dá 38, K=6 dá 48. Mudar K é reescrever 20 literais na escada e nada mais.

**Se você quiser números maiores na barra**, multiplique os dois lados por
qualquer constante — EXP por bola = 5 com `EXP(L) = 20·L·(L-1)` (máx. 7600) dá
exatamente os mesmos 32 dias. O ritmo é a razão entre os dois números, não o
tamanho deles, e há folga de 65535 para o que você quiser.

**O lote é 5 para tudo, e isso mudou na rev3.** Na rev2 a Poké, a Great e a Ultra
saíam em lotes de 10. Com EXP por **bola**, um lote de 10 daria o dobro de EXP
pela mesma vaga da cota — a jogada ótima viraria "fabricar Great Ball o dia
inteiro" e a árvore de receitas perderia a graça. Lote uniforme de 5 resolve sem
regra extra. Quem precisa de volume no começo do jogo compra Poké Ball na loja,
que continua ilimitada, e pega as 5 do sorteio diário.

**Não há exceção nenhuma na cota.** Todo lote são 5 bolas, +5 EXP, 1 vaga. A rev2
tinha a Master Ball como caso especial (lote de 1, cota inteira, EXP proporcional);
a rev3 **tirou a Master Ball da árvore** (§2.5), e com isso a última irregularidade
do sistema saiu. Não existe escolha de receita que renda mais EXP do que outra, e
por isso não existe jogada ótima a descobrir — só a árvore a abrir.

**A var começa em 0.** Nível 1 exige 0 EXP, então não há semente a plantar na cena
de aprendiz e a escada nunca precisa de piso artificial.

### 2.3 Custo em berries: cai com o nível

```
berries por lote = 6 - teto(nível / 5)
```

| Níveis | Berries por lote |
|---|---|
| 1 a 5 | 5 |
| 6 a 10 | 4 |
| 11 a 15 | 3 |
| 16 a 20 | 2 |

**Onde a fazenda realmente vive.** Subir do nível 1 ao 20 custa **929 berries** em
32 dias — cerca de 29 por dia. Mas o custo que importa é o **depois**: no nível
20, usar a cota inteira todo dia é **40 berries por dia, para sempre**. É esse
número que faz plantar valer a pena, não o da subida.

### 2.4 As 27 receitas

Vinte e seis por nível, **uma por história**, e **uma que ele nunca aprende**. A
ordem é de personagem: a Poké Ball
e a Great Ball saem no nível 1 porque ele já fez dez mil de cada; a **linha das
apricorns** (as sete que já eram receita dele) ocupa os níveis 4 a 10; as bolas
modernas vêm depois, de má vontade; e as encomendas fecham a árvore.

| Nv | Receita | Lote | Ingrediente | Nota |
|---|---|---|---|---|
| 1 | Poké Ball | ×5 | Leppa | a loja vende mais barato |
| 1 | Great Ball | ×5 | Aguav | |
| 2 | Heal Ball | ×5 | Lum | a berry que cura tudo |
| 3 | Ultra Ball | ×5 | Iapapa | |
| 4 | **Level Ball** | ×5 | Persim | receita original dele |
| 5 | **Lure Ball** | ×5 | Rawst | receita original |
| 6 | **Moon Ball** | ×5 | Chesto | receita original |
| 7 | **Friend Ball** | ×5 | Cheri | receita original |
| 8 | **Fast Ball** | ×5 | Aspear | receita original |
| 9 | **Heavy Ball** | ×5 | Oran | receita original |
| 10 | **Love Ball** | ×5 | Pecha | receita original |
| 11 | Nest Ball | ×5 | Kelpsy | |
| 11 | Net Ball | ×5 | Qualot | |
| 12 | Quick Ball | ×5 | Sitrus | |
| 13 | Timer Ball | ×5 | Wiki | |
| 14 | Repeat Ball | ×5 | Grepa | |
| 15 | Dive Ball | ×5 | Passho | Passho resiste a Água |
| 15 | Dusk Ball | ×5 | Kasib | Kasib resiste a Fantasma |
| 16 | Premier Ball | ×5 | Hondew | |
| 16 | Luxury Ball | ×5 | Tamato | |
| 17 | Sport Ball | ×5 | Pomeg | |
| 17 | Park Ball | ×5 | Chilan | |
| 18 | Safari Ball | ×5 | Roseli | |
| 18 | Dream Ball | ×5 | Yache | |
| 19 | Cherish Ball | ×5 | Colbur | |
| 20 | Strange Ball | ×5 | Starf | **o troféu** |
| — | **Beast Ball** | ×5 | Haban | **não é por nível — ver §2.5** |
| — | ~~Master Ball~~ | — | — | **não tem receita — ver §2.6** |

A Starf só existe no `BattleFrontier_ScottsHouse`, o que é **pós-game** — e está
certo: ela é a receita de nível 20.

**A última receita da árvore é a Strange Ball, e isso é de propósito.** Trinta e
dois dias de trabalho, vinte níveis, e o que ele finalmente aprende a fabricar é a
bola que não faz absolutamente nada — a bola de Pokémon que vieram de outro jogo.
É a única piada que este sistema conta, e ela só funciona porque está no fim.

### 2.5 A Beast Ball não é por nível: é por ter derrotado o Necrozma

Decisão do autor na rev3, e é a melhor costura que este sistema ganha com o arco
das Rift Missions. Na rev2 ela era receita de nível 18 (~170 dias), o que tornava
a fala da Anabel no altar ("vá até o Kurt") uma promessa que o Kurt não podia
cumprir por meses.

**Agora a receita destranca com a história, não com o trabalho:**

```asm
@ Beast Ball. The ONLY recipe not gated by Kurt's level. It appears the moment
@ the player beats Ultra Necrozma, because that is when Anabel sends them here
@ (ALTAR_SUN_MOON_IMPLEMENTATION.md section 10.3) - and a pointer that leads to
@ "I can't make that yet" is worse than no pointer.
@ State 15 is "Necrozma defeated and received", set by the arena. NOT 16: the
@ farewell has not played yet when the player could first come back, and one
@ wasted trip to Azalea is exactly the friction this decision removes.
KurtCraft_EventScript_BeastBallGate::
	goto_if_lt VAR_RIFT_MISSIONS_STATE, 15, KurtCraft_EventScript_BeastBallLocked
	...
```

Três consequências que valem escrever:

1. **Zero estado novo.** Ela lê `VAR_RIFT_MISSIONS_STATE`, que já existe e já é a
   autoridade da história. Nenhuma flag, nenhuma var.
2. **Ela continua custando cota**, e o custo em berry segue a tabela do nível
   atual — quem chega ao altar com o Kurt no nível 3 faz 5 Beast Balls por dia a
   5 Haban cada; quem chega no 15 faz 15 lotes a 3.
3. **É a única receita que o sorteio diário também sorteia**, o que dá uma fonte
   lenta a quem ainda não chegou ao altar. Isso agora é redundância de segurança,
   e não a fonte principal.

**Fala do Kurt antes do altar,** para quem perguntar (o menu simplesmente não
mostra a linha, mas a neta comenta):

> Kurt: Uma mulher da polícia me escreveu há quatro anos pedindo uma bola que
> segurasse uma coisa que não é daqui. Eu fiz quatro. Ela levou as quatro.
> Se você algum dia vir o que ela estava caçando, volte aqui e me conte. Aí eu
> faço mais.

### 2.6 A Master Ball: ele nunca aprende

Decisão do autor na rev3. Ela **não tem receita** e o Kurt **nunca** aprende a
fazer uma. A única coisa que ela continua sendo é a **face 16 do sorteio diário** —
a peça que sai por acidente, uma vez a cada dezesseis manhãs, e que ele mesmo não
sabe explicar. O texto disso já está escrito no código de hoje:

> "This once is a masterpiece! I can hardly believe I managed to craft it."

Isso é, de longe, a melhor coisa que a Master Ball podia ser neste sistema. Uma
receita a transformaria em item de lista de compras; a sorte a mantém como o que
ela é. E como é **a única** coisa no sorteio que não tem receita, o sorteio deixa de
ser redundante no fim do jogo: mesmo no nível 20 com as 26 receitas abertas, vale
falar com o Kurt todo dia — por causa de uma face de um dado.

**A única mudança de código:** o gate do sorteio. Hoje a face 16 exige
`VAR_KURT_PROFICIENCY >= 4`, que significava "quatro dias de visita". Com a var
virando EXP, `>= 4` passa quase de imediato (um lote é +5). **Decidido pelo autor
em 24/09: re-gate em `>= 360`** — nível 10, metade da árvore.

```asm
@ The Master Ball face of the daily draw. It is NOT a recipe and never will be.
@ Re-gated from ">= 4 days" to ">= 360 EXP" (level 10) because the var changed
@ meaning: a master craftsman turns one out by accident, an apprentice does not.
	goto_if_ge VAR_KURT_PROFICIENCY, 360, KurtCraft_EventScript_DrawSixteen
	random 15
	goto KurtCraft_EventScript_Draw
KurtCraft_EventScript_DrawSixteen::
	random 16
```

A outra fonte de Master Ball do jogo — o presente do laboratório do Elm — **fica**
(§2.1). O prêmio do Battle Arcade sai, como todo resto.

> **A alternativa considerada e descartada** era não ter gate: a face 16 valendo do
> primeiro dia, 1 em 16. Era defensável — sorte não pede licença —, mas tirava a
> única leitura de progresso que o sorteio tem. Com o gate, o sorteio conta uma
> história: até o nível 10 ele te dá bolas, depois do nível 10 ele às vezes te dá
> um milagre.

### 2.7 A cota do dia

**Cota = nível, e o nível 1 dá um lote por dia.** Decidido pelo autor em 24/09; a
alternativa (`cota = nível + 1`, que levaria os 32 dias para 27) foi considerada e
descartada. O começo da campanha é apertado de propósito: quem precisa de volume
compra Poké Ball na loja, que continua ilimitada, e pega as 5 de graça do sorteio.

Uma var nova, e é a única do sistema:

```
VAR_KURT_TODAY = 0x4121   (primeira livre depois de VAR_RIFT_MISSIONS_STATE)
```

O reset é trabalho do motor: uma daily flag marca "o dia de hoje já foi
inicializado", e `ClearDailyFlags` (`src/event_data.c:71`) a zera na virada da
data.

```asm
KurtCraft_EventScript_RollOver::
	goto_if_set FLAG_DAILY_KURT_NEW_DAY, KurtCraft_EventScript_RollOverDone
	setvar VAR_KURT_TODAY, 0
	setflag FLAG_DAILY_KURT_NEW_DAY
KurtCraft_EventScript_RollOverDone::
	return
```

> **Duas daily flags, não uma.** O sorteio continua existindo e continua
> precisando da **dele**: `FLAG_DAILY_KURT_FREE_BALLS` (já existe, "já peguei o
> sorteio de hoje") e `FLAG_DAILY_KURT_NEW_DAY` (nova, sobre
> `FLAG_UNUSED_0x949`). Reusar uma só faz o sorteio zerar a cota, ou a cota
> engolir o sorteio.

### 2.8 O menu e o esqueleto do script

`MULTI_KURT_BALLS` é uma lista fixa de 8 linhas e não sabe crescer; o menu novo é
`dynmultichoice` (`asm/macros/event.inc:1942`), em **dois passos** — grupo, depois
receita. Com 27 receitas não cabe em um. O protótipo publicado como Artifact é a
referência visual das duas telas.

```asm
@ ---------------------------------------------------------------------------
@ Kurt. ONE entry point, and it replaces the `goto KurtDaily` that today makes
@ the recipe menu unreachable (section 1.2). The free draw stays, as a branch.
@ Order of guards, none of them reorderable:
@   1. plot branches (GS Ball / Slowpoke Well), as today
@   2. the day rollover, so the quota is always about today
@   3. the free draw, if it has not been taken - it gives NO exp
@   4. the quota, BEFORE the menu: never let the player pick and then refuse
@   5. the menu, by level
@   6. per recipe: item space -> consume -> give -> guard -> exp
@ ---------------------------------------------------------------------------
AzaleaTown_KurtsHouse_EventScript_Kurt::
	lock
	faceplayer
	goto_if_eq VAR_AZALEA_TOWN_STATE, 8, ..._KurtGsBall2
	goto_if_eq VAR_AZALEA_TOWN_STATE, 9, ..._KurtGsBall3
	call_if_unset FLAG_CAUGHT_CELEBI, ..._KurtCheckGSBall
	call KurtCraft_EventScript_RollOver
	call_if_unset FLAG_DAILY_KURT_FREE_BALLS, KurtCraft_EventScript_FreeDraw
	call KurtCraft_EventScript_ComputeLevel      @ VAR_0x8004 = level, 1..20
	goto_if_lt VAR_KURT_TODAY, VAR_0x8004, KurtCraft_EventScript_Menu
	goto KurtCraft_EventScript_DoneForToday

@ The free daily draw, kept as-is EXCEPT for one thing: it no longer touches
@ VAR_KURT_PROFICIENCY. The old `addvar VAR_KURT_PROFICIENCY, 1` comes out, and
@ so does the `>= 4` gate on the Master Ball face - proficiency is EXP now, and
@ a gift must not buy progress.
KurtCraft_EventScript_FreeDraw::
	@ ... the existing random(16) switch, unchanged ...
	setflag FLAG_DAILY_KURT_FREE_BALLS
	return

@ There is NO divvar in this tree (only addvar, subvar, setvar, copyvar), so the
@ level is a descending ladder against the 4*L*(L-1) thresholds. Twenty lines,
@ read once per conversation, and the ONLY place that turns EXP into a level.
KurtCraft_EventScript_ComputeLevel::
	setvar VAR_0x8004, 20
	goto_if_ge VAR_KURT_PROFICIENCY, 1520, KurtCraft_EventScript_LevelDone
	setvar VAR_0x8004, 19
	goto_if_ge VAR_KURT_PROFICIENCY, 1368, KurtCraft_EventScript_LevelDone
	setvar VAR_0x8004, 18
	goto_if_ge VAR_KURT_PROFICIENCY, 1224, KurtCraft_EventScript_LevelDone
	setvar VAR_0x8004, 17
	goto_if_ge VAR_KURT_PROFICIENCY, 1088, KurtCraft_EventScript_LevelDone
	setvar VAR_0x8004, 16
	goto_if_ge VAR_KURT_PROFICIENCY, 960, KurtCraft_EventScript_LevelDone
	setvar VAR_0x8004, 15
	goto_if_ge VAR_KURT_PROFICIENCY, 840, KurtCraft_EventScript_LevelDone
	setvar VAR_0x8004, 14
	goto_if_ge VAR_KURT_PROFICIENCY, 728, KurtCraft_EventScript_LevelDone
	setvar VAR_0x8004, 13
	goto_if_ge VAR_KURT_PROFICIENCY, 624, KurtCraft_EventScript_LevelDone
	setvar VAR_0x8004, 12
	goto_if_ge VAR_KURT_PROFICIENCY, 528, KurtCraft_EventScript_LevelDone
	setvar VAR_0x8004, 11
	goto_if_ge VAR_KURT_PROFICIENCY, 440, KurtCraft_EventScript_LevelDone
	setvar VAR_0x8004, 10
	goto_if_ge VAR_KURT_PROFICIENCY, 360, KurtCraft_EventScript_LevelDone
	setvar VAR_0x8004, 9
	goto_if_ge VAR_KURT_PROFICIENCY, 288, KurtCraft_EventScript_LevelDone
	setvar VAR_0x8004, 8
	goto_if_ge VAR_KURT_PROFICIENCY, 224, KurtCraft_EventScript_LevelDone
	setvar VAR_0x8004, 7
	goto_if_ge VAR_KURT_PROFICIENCY, 168, KurtCraft_EventScript_LevelDone
	setvar VAR_0x8004, 6
	goto_if_ge VAR_KURT_PROFICIENCY, 120, KurtCraft_EventScript_LevelDone
	setvar VAR_0x8004, 5
	goto_if_ge VAR_KURT_PROFICIENCY, 80, KurtCraft_EventScript_LevelDone
	setvar VAR_0x8004, 4
	goto_if_ge VAR_KURT_PROFICIENCY, 48, KurtCraft_EventScript_LevelDone
	setvar VAR_0x8004, 3
	goto_if_ge VAR_KURT_PROFICIENCY, 24, KurtCraft_EventScript_LevelDone
	setvar VAR_0x8004, 2
	goto_if_ge VAR_KURT_PROFICIENCY, 8, KurtCraft_EventScript_LevelDone
	setvar VAR_0x8004, 1
KurtCraft_EventScript_LevelDone::
	return

@ One recipe, and it is the pattern for all 28. The bug of section 1.3 is fixed
@ here and must stay fixed: space FIRST, then consume, then give, then guard.
@ VAR_0x8005 carries the berry count for this level, set by ComputeCost.
KurtCraft_EventScript_MakeLevelBall::
	checkitemspace ITEM_LEVEL_BALL, 5
	goto_if_eq VAR_RESULT, FALSE, KurtCraft_EventScript_BagFull
	call KurtCraft_EventScript_ComputeCost           @ VAR_0x8005 = 5,4,3 or 2
	checkitem ITEM_PERSIM_BERRY, VAR_0x8005
	goto_if_eq VAR_RESULT, FALSE, KurtCraft_EventScript_NoIngredient
	call KurtCraft_EventScript_WorkAnimation
	removeitem ITEM_PERSIM_BERRY, VAR_0x8005
	giveitem ITEM_LEVEL_BALL, 5
	goto_if_eq VAR_RESULT, FALSE, KurtCraft_EventScript_BagFull
	addvar VAR_KURT_TODAY, 1
	call KurtCraft_EventScript_AddExp5               @ +5 (uma por bola), teto 1520
	goto KurtCraft_EventScript_Finished

@ +1 per BALL (rev3). Every lot is 5 balls, so every lot is +5, with no
@ exceptions - the Master Ball left the tree (2.6) and took the last special
@ case with it. The cap is checked BEFORE the add, the shape the old code used.
KurtCraft_EventScript_AddExp5::
	goto_if_ge VAR_KURT_PROFICIENCY, 1516, KurtCraft_EventScript_AddExpMax
	addvar VAR_KURT_PROFICIENCY, 5
	return
KurtCraft_EventScript_AddExpMax::
	setvar VAR_KURT_PROFICIENCY, 1520
	return
```

> **`checkitem`/`removeitem` aceitam var na quantidade?** Conferir antes de
> escrever (`asm/macros/event.inc:549` e `:557`): as macros recebem um imediato de
> 16 bits. Se não aceitarem var, o custo decrescente vira **quatro** ramos por
> receita (5/4/3/2), ou — bem melhor — **uma sub-rotina genérica** que recebe item
> de entrada, item de saída e quantidade em `VAR_0x8004..8006` e faz o trabalho
> uma vez para as 27. Essa é a forma recomendada de qualquer jeito: 27 cópias de
> 12 linhas é 336 linhas em que o bug de §1.3 pode voltar.

### 2.9 Como o jogador percebe o nível

- **A neta do Kurt** (`KurtsHouse_Text_Granddaughter*`, já existe) comenta por
  faixa de cinco níveis. Quatro caixas, não vinte.
- **O menu é a notificação:** uma linha nova aparecendo é a coisa mais clara
  possível, e não custa caixa nenhuma.
- **Ninguém diz "nível 13" em voz alta.** O jogador nunca lê o número; ele lê a
  lista crescendo. O número é do documento, não do jogo.

---

## 3. Estado — contrato

| Constante | Arquivo | Valor | Papel |
|---|---|---|---|
| `VAR_KURT_PROFICIENCY` | `include/constants/vars.h:243` | `0x40DF` (**já existe**) | **Muda de significado:** era "dias", passa a ser **EXP, 0..1520**. `u16`, então há folga de sobra (`include/global.h:1175`) |
| `VAR_KURT_TODAY` | idem | `0x4121` (livre) | Lotes feitos hoje, `0..nível` |
| `FLAG_DAILY_KURT_FREE_BALLS` | `include/constants/flags.h:1840` | `DAILY_FLAGS_START + 0x19` (**já existe**) | Continua igual: "já peguei o sorteio de hoje" |
| `FLAG_DAILY_KURT_NEW_DAY` | idem | `DAILY_FLAGS_START + 0x29` (era `FLAG_UNUSED_0x949`) | "o dia de hoje já foi inicializado" — zera `VAR_KURT_TODAY` |
| `FLAG_KURT_CRAFTED_MASTER_BALL` | `include/constants/flags.h:853` | `0x31E` (**já existe**) | **Não muda nada:** continua sendo setada **só pelo sorteio** e continua alimentando a conquista (`src/achievements.c:590`). A Master Ball não tem receita (§2.6) |
| `VAR_RIFT_MISSIONS_STATE` | `include/constants/vars.h:333` | `0x4120` (**já existe**) | **Lida, nunca escrita:** `>= 15` destranca a receita da Beast Ball (§2.5). É o único acoplamento entre este sistema e as Rift Missions |

**Invariantes:**

- `nível = maior L com VAR_KURT_PROFICIENCY >= 4·L·(L-1)`, calculado **só** por
  `ComputeLevel`.
- `0 <= VAR_KURT_PROFICIENCY <= 1520`; o teto é conferido antes de cada `addvar`.
- `0 <= VAR_KURT_TODAY <= nível`, zerada apenas pelo `RollOver`.
- **O sorteio diário nunca escreve em `VAR_KURT_PROFICIENCY`.**
- Nenhuma receita muda estado antes de o item estar garantido (§1.3).

**Uma var nova e uma daily flag nova.** Nada de flag persistente.

---

## 4. Arquivos tocados

| Arquivo | Mudança |
|---|---|
| `include/constants/vars.h` | `VAR_KURT_TODAY 0x4121`; reescrever o comentário de `VAR_KURT_PROFICIENCY` com a fórmula e a tabela de níveis |
| `include/constants/flags.h` | `FLAG_DAILY_KURT_NEW_DAY` sobre `FLAG_UNUSED_0x949` |
| `src/shop.c` | Tirar `GREAT_BALL` e `ULTRA_BALL` das 9 listas `sShopInventory_*` e das 9 `_PC` |
| `data/maps/AzaleaTown_KurtsHouse/scripts.pory` | Religar o menu; 27 receitas (via sub-rotina genérica); `RollOver`; `ComputeLevel`; `ComputeCost`; `AddExp5`; tirar o `addvar VAR_KURT_PROFICIENCY` do sorteio e re-gatear a face 16 em `>= 360`; falas da neta por faixa |
| `src/data/script_menu.h`, `include/constants/script_menu.h` | Apagar `MULTI_KURT_BALLS` e `MultichoiceList_KurtsBalls` |
| 9 balcões de loja | Cherrygrove, Violet, Azalea (2 listas), Ecruteak, Olivine, Blackthorn, Rinto, Battle Frontier, Liga 1F — tirar todas as bolas |
| `data/maps/VajraDesertEast/map.json` | Beast Ball do chão → `ITEM_POKE_BALL` |
| `data/maps/GoldenrodBattleAracdeLobby/scripts.inc` | Master Ball do prêmio → outro item |
| Itens de chão de bola em qualquer mapa | → `ITEM_POKE_BALL` (a varredura do §1.4 lista Dusk, Quick, Ultra e Beast) |
| `data/maps/Route30_House/scripts.inc` | O careca vira **Berry Master**: mantém a Cheri de tutorial e ganha 2 berries sorteadas por dia; corrigir a vírgula faltando do `msgbox` (§5.6) |
| `data/maps/Route30_House/map.json` | **1 objeto novo:** a mulher dele (faixa rara, pós-Liga) |
| `include/constants/items.h` | `FIRST/LAST/NUM_BERRY_MASTER_COMMON` e `..._RARE` (§5.2) |
| `include/constants/flags.h` | `FLAG_DAILY_BERRY_MASTER_RARE` sobre `FLAG_UNUSED_0x94A` |
| `data/maps/VioletCity/scripts.inc` | **+1 linha:** a Persim entra na lista do NPC (opcional depois do §5.3, mas barato) |

**Não se mexe:** o laboratório do Elm (Poké Ball ×10 e Master Ball ficam), o Gate
do Parque Nacional (Safari Ball é o minijogo), a Poké Ball do chão da Route 31 (já
é Poké Ball), e as lojas de Hoenn (`gMapGroup_Emerald1/2`, fora da campanha).

---

## 5. O Berry Master na casa da Route 30

Aprovado pelo autor, com o lugar escolhido por ele: **`Route30_House`**, *"para já
fazer o sistema cedo"*. E a escolha é melhor do que parece, porque aquela casa
**já é a casa das berries**.

### 5.1 O NPC já existe, e já é o cara das berries

`data/maps/Route30_House/scripts.inc` tem um único NPC,
`Route30_House_EventScript_BaldMan` (`OBJ_EVENT_GFX_BALDING_MAN`, em (4,4)): ele
entrega **uma Cheri Berry** uma vez, explica que Pokémon comem berries e que as
árvores dão fruto de novo em 12 horas, e aponta a casa do Kukui ao norte.

Ou seja: **não é portar um NPC, é promover o que já está lá.** O tutorial de berry
do jogo vira a fonte permanente de berry do jogo, na primeira rota, antes da
primeira insígnia.

Três coisas que isso resolve de graça:

- **O sistema começa cedo.** Route 30 é logo depois de Cherrygrove. O jogador
  começa a acumular berries dezenas de horas antes de conhecer o Kurt, que é
  exatamente o que faz a economia de bolas não travar no começo.
- **A fala dele já ensina a mecânica certa** ("as árvores dão fruto de novo em 12
  horas"). O que falta é dizer que ele **dá** berries todo dia.
- **Zero mapa novo, zero objeto novo** para a parte principal.

### 5.2 O que muda no script dele

```asm
@ The Route 30 berry man becomes the Berry Master. He keeps the one-off Cheri
@ Berry (it is the tutorial and it explains the whole system), and gains a
@ daily gift on top of it.
@ FLAG_GOT_BERRY_ROUTE_30_HOUSE stays exactly as it is: it is the tutorial
@ marker, not the daily gate.
Route30_House_EventScript_BaldMan::
	lock
	faceplayer
	dotimebasedevents
	call_if_unset FLAG_GOT_BERRY_ROUTE_30_HOUSE, Route30_House_EventScript_Tutorial
	goto_if_set FLAG_DAILY_BERRY_MASTER_RECEIVED_BERRY, Route30_House_EventScript_DoneToday
	msgbox Route30_House_Text_TakeTwo, MSGBOX_DEFAULT
	call Route30_House_EventScript_GiveCommonBerry
	setflag FLAG_DAILY_BERRY_MASTER_RECEIVED_BERRY
	call Route30_House_EventScript_GiveCommonBerry
	msgbox Route30_House_Text_PlantThem, MSGBOX_DEFAULT
	release
	end

@ The common pool is a CONTIGUOUS range of the item enum, so it is three lines.
@ Cheri (FIRST_BERRY_INDEX) .. Roseli = 53 berries, which covers every berry in
@ the 28 recipes except Starf and Lansat - and those two are the level-20
@ recipes and belong to the post-game (5.4).
Route30_House_EventScript_GiveCommonBerry::
	random NUM_BERRY_MASTER_COMMON
	addvar VAR_RESULT, FIRST_BERRY_INDEX
	giveitem VAR_RESULT
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	return
```

Constantes novas em `include/constants/items.h`, ao lado das que já existem
(`:1140`):

```c
// The Route 30 Berry Master's daily pool: the contiguous common range.
#define FIRST_BERRY_MASTER_COMMON     ITEM_CHERI_BERRY      // = FIRST_BERRY_INDEX
#define LAST_BERRY_MASTER_COMMON      ITEM_ROSELI_BERRY
#define NUM_BERRY_MASTER_COMMON       (LAST_BERRY_MASTER_COMMON - FIRST_BERRY_MASTER_COMMON + 1)

// The rare range, post-Hall of Fame only.
#define FIRST_BERRY_MASTER_RARE       ITEM_LIECHI_BERRY
#define LAST_BERRY_MASTER_RARE        ITEM_MARANGA_BERRY
#define NUM_BERRY_MASTER_RARE         (LAST_BERRY_MASTER_RARE - FIRST_BERRY_MASTER_RARE + 1)
#define NUM_BERRY_MASTER_RARE_SKIPPED (FIRST_BERRY_MASTER_RARE - FIRST_BERRY_INDEX)
```

> **O enum de berry é contíguo, e é isso que torna tudo isto barato:**
> `ITEM_CHERI_BERRY` (= `FIRST_BERRY_INDEX`, 514) até `ITEM_MARANGA_BERRY` (580),
> **67 berries sem buraco**. Sorteio de pool é `random N` + `addvar` + `giveitem
> VAR_RESULT`, sem tabela e sem `switch` — o padrão que o Berry Master de Hoenn já
> usa (`Route123_BerryMastersHouse/scripts.inc:15`).

**Dois cuidados obrigatórios:**

1. **`FLAG_DAILY_BERRY_MASTER_RECEIVED_BERRY` já existe** e está no bloco daily
   (`flags.h`, `DAILY_FLAGS_START + 0xD`), então o reset é do motor. O Berry Master
   de Hoenn usa **`FLAG_GARBAGEFLAG`** como trava diária
   (`Route123_BerryMastersHouse/scripts.inc:13`), que é uma gambiarra. **Não copiar
   essa linha** — usar a flag daily de verdade.
2. **A flag é setada entre a primeira e a segunda berry**, como no original. Se
   ela fosse setada depois das duas, uma bolsa cheia na segunda deixaria o jogador
   pegar as duas de novo no mesmo dia.

### 5.3 A distribuição que isso produz

| Faixa | Quantas | Fonte | Quando |
|---|---|---|---|
| Comuns do NPC de Violet | 12 | de graça, uma vez | começo |
| De loja | 24 | Floricultura de Goldenrod (18) + Dept. Store 3F (6) | dinheiro |
| **Sorteio comum** | **53** | **Route 30, 2 por dia** | **Route 30** |
| Rara | 14 | §5.4 | pós-Liga |

As 53 do sorteio comum **contêm as 10 órfãs que as receitas não usam** (Mago, Bluk,
Nanab, Wepear, Pinap, Cornn, Magost, Rabuta, Nomel) **e a Persim**, que é a
ingrediente da Level Ball e hoje não tem fonte nenhuma. Ou seja: **o sorteio da
Route 30 resolve sozinho o único furo das 27 receitas.**

A linha extra no NPC de Violet City continua valendo a pena de qualquer forma —
uma Persim garantida é melhor que uma sorteada —, mas deixa de ser bloqueante.

### 5.4 As 14 raras: a mulher dele, depois da Liga

Liechi, Ganlon, Salac, Petaya, Apicot, Lansat, Starf, Enigma, Micle, Custap,
Jaboca, Rowap, Kee, Maranga. Elas são as berries competitivas, e **duas delas são
as receitas de nível 20** (Starf e Lansat).

**Um objeto novo** em `Route30_House` — a mulher do Berry Master — com uma segunda
daily flag e uma guarda de Hall of Fame:

```asm
@ One object, one daily flag, one berry, and a gate: FLAG_SYS_GAME_CLEAR.
@ Before the Hall of Fame she just talks. This is what keeps Lansat and Starf
@ out of the early game without a single new var.
Route30_House_EventScript_BerryWife::
	lock
	faceplayer
	dotimebasedevents
	goto_if_unset FLAG_SYS_GAME_CLEAR, Route30_House_EventScript_WifeChat
	goto_if_set FLAG_DAILY_BERRY_MASTER_RARE, Route30_House_EventScript_WifeDoneToday
	msgbox Route30_House_Text_WifeRare, MSGBOX_DEFAULT
	random NUM_BERRY_MASTER_RARE
	addvar VAR_RESULT, NUM_BERRY_MASTER_RARE_SKIPPED
	addvar VAR_RESULT, FIRST_BERRY_INDEX
	giveitem VAR_RESULT
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_DAILY_BERRY_MASTER_RARE
	release
	end
```

`FLAG_DAILY_BERRY_MASTER_RARE` é a segunda daily flag nova do plano, sobre
`FLAG_UNUSED_0x94A`. `Route30_House` tem **um** objeto hoje e um único warp em
(4,8), então há espaço de sobra — conferir a posição com
`dump_mapa.py Route30_House` antes de escolher o tile.

**O que NÃO se porta do Berry Master de Hoenn:** o mecanismo de frases do Easy
Chat (`PHRASE_GREAT_BATTLE` e as outras quatro), que dá as cinco berries de bolo
de Hoenn. É um vestígio de Gen 3 sem equivalente em Johto, e as cinco berries dele
(Spelon, Pamtre, Watmel, Durin, Belue) estão dentro da faixa comum do §5.2 e saem
no sorteio.

### 5.5 Textos

> `Text_TakeTwo`
> Careca: Você voltou! E olhou as árvores, eu aposto.
> Eu colho mais do que dois velhos conseguem comer. Leve duas -- tem mais amanhã, tem sempre mais amanhã.
>
> `Text_PlantThem`
> Careca: E não coma as duas. Plante uma.
> É assim que isso funciona: uma berry plantada é uma árvore, e uma árvore é berry para sempre.
>
> `Text_WifeRare` — **pós-Liga**
> Mulher: Meu marido dá as fáceis. Eu guardo as outras.
> Estas aqui só dão fruto se alguém souber o que está fazendo, e eu vi o que você fez na Liga.
> Uma por dia. Não discuta.

### 5.6 Achado de passagem

`Route30_House/scripts.inc:13` tem
`msgbox Route30_BerryHouse_Text_CheckTrees MSGBOX_DEFAULT` — **sem vírgula**.
Compila porque o `gas` separa argumentos de macro por espaço também, mas é o único
`msgbox` do repositório escrito assim. Corrigir de passagem, já que o arquivo vai
ser tocado.

---

## 6. Riscos, todos respondidos pelo autor

| Risco da rev1 | Resposta | Situação |
|---|---|---|
| Tirar Great e Ultra das lojas muda a curva de captura do jogo inteiro | "o objetivo eh deixar tudo mais lento" | **É a intenção.** Fica. O piso de segurança é a Poké Ball na loja + o sorteio diário de 5 bolas |
| As berries raras podem não ser obteníveis | "a gente tem que deixar todas berries obteníveis" + "vamos portar o Berry Master" | **Virou escopo e está desenhado:** §5, na casa da Route 30 que o autor escolheu. O sorteio comum de 53 berries resolve o único furo das receitas (a Persim) sozinho |
| 5 berries por lote vira farm chato | "eh para ser um joguinho lento, eu to pensando em deixar breeding mais importante" | **É a intenção.** O custo cai com o nível (§2.3) e os dois totais estão medidos: **929 berries** para chegar ao nível 20, e **40 por dia para sempre** depois |
| A var reaproveitada quebra saves em andamento | "nunca se preocupa com isso, não lanço" | **Fechado.** Não é problema |
| Apagar o sorteio tira a única fonte de algumas bolas | "pode manter" + "literalmente TODAS as poké bolas têm que ter receita" | **O sorteio fica** (sem EXP). Todas têm receita, Strange Ball incluída, **menos a Master Ball** — que na rev3 o autor decidiu deixar só na sorte do sorteio (§2.6) |

### As decisões de 24/09, e por que cada uma ficou assim

O autor fechou as três últimas perguntas abertas. Ficam registradas com a
alternativa que foi descartada, porque uma decisão sem a alternativa ao lado
vira dogma na próxima leitura.

| Pergunta | Decisão | Alternativa descartada |
|---|---|---|
| A face 16 do sorteio (Master Ball) tem gate? | **`VAR_KURT_PROFICIENCY >= 360`** (nível 10) | Sem gate, valendo do primeiro dia. Tirava a única leitura de progresso que o sorteio tem |
| Cota inicial 1 ou 2 lotes/dia? | **`cota = nível`** — um lote no nível 1 | `cota = nível + 1`, que levaria os 32 dias para 27. O começo apertado é intencional |
| O Berry Master, onde e como? | **`Route30_House`, promovendo o careca que já mora lá** (§5) | Casa nova em Azalea, ou uma loja vendendo as 67. A loja transformava a fazenda numa conta bancária |

### O que continua sendo risco

**1. Vinte e sete receitas copiadas e coladas** são ~324 linhas em que o bug de
`VAR_RESULT` do §1.3 pode voltar. A **sub-rotina genérica** do §2.8 — item de
entrada, item de saída e quantidade em `VAR_0x8004..8006` — não é otimização, é o
que impede a terceira reincidência. **É o único risco de implementação que sobra.**

**2. A lentidão mora no depois, não na subida.** 929 berries chegam ao nível 20 em
32 dias; depois são **40 berries por dia, para sempre**, para usar a cota cheia
(§2.3). Se a sensação de forever game não aparecer no teste, o botão é o
`K = 4` da curva (§2.2), não a tabela de custo — e é um número, em 20 literais.

**3. O começo da campanha é o trecho a olhar em runtime.** Entre Cherrygrove e
Azalea o jogador tem: Poké Ball ilimitada na loja, 2 berries por dia na Route 30, e
nada do Kurt. Depois de Azalea: 5 bolas de graça por dia mais 1 lote de 5. É
apertado por decisão, mas é o único lugar onde o ritmo pode virar frustração em vez
de paciência.

---

## 7. Pendências

Nenhuma delas é decisão de design — as três últimas foram fechadas em 24/09 (§6).

1. **`checkitem`/`removeitem` aceitam quantidade em var?** Se só aceitarem
   imediato, o custo decrescente vira quatro ramos por receita, e a sub-rotina
   genérica do §2.8 deixa de ser recomendação e passa a ser requisito. **Conferir
   antes de escrever a primeira receita** (`asm/macros/event.inc:549` e `:557`).
2. **As árvores de apricorn — Fase 2, documento próprio.** `APRICORN_TREE_COUNT` é
   0; os 13 itens, o `gApricornTrees` e o `src/apricorn_tree.c` existem, mas
   nenhuma árvore foi plantada. Trocar a coluna de ingrediente de berry para
   apricorn é a versão canônica do Kurt, e a tabela do §2.4 foi montada para que
   seja **só aquela coluna** a mudar.
3. **Runtime.** Nada deste documento foi jogado. A ordem de teste que importa: o
   trecho Cherrygrove→Azalea (risco 3), a virada de data com as **quatro** daily
   flags do sistema (`KURT_FREE_BALLS`, `KURT_NEW_DAY`, `BERRY_MASTER_RECEIVED_BERRY`
   e `BERRY_MASTER_RARE`), e a bolsa cheia em cada um dos dois pontos onde o bug de
   §1.3 vivia.

---

## 8. Retorno da implementação (revisão 4, 24/09/2026)

Implementado numa passada junto com
[`ALTAR_SUN_MOON_IMPLEMENTATION.md`](rift_missions/ALTAR_SUN_MOON/ALTAR_SUN_MOON_IMPLEMENTATION.md). `make`
limpa, `checar_falantes.py` limpo, `medir_linha.py` sem estouro.

**O que a análise do §1 acertou, e é bom registrar:** o menu de receitas
realmente era **inalcançável** (`goto KurtDaily` incondicional, e o único
`goto ..._Kurt2` do repositório estava **dentro** de uma receita), e as sete
receitas realmente comiam a berry com a bolsa cheia, na ordem exata que o §1.3
descreve. Nada disso foi exagero do documento.

### 8.1 A pendência de código: respondida, e ela muda a forma do sistema

```c
// src/scrcmd.c:665
bool8 ScrCmd_checkitem(struct ScriptContext *ctx)
{
    enum Item itemId = VarGet(ScriptReadHalfword(ctx));   // <- var aceita
    u32 quantity = VarGet(ScriptReadHalfword(ctx));       // <- var aceita TAMBEM
```

O mesmo vale para `removeitem`, `checkitemspace` e `additem`, e o `giveitem`
funciona por `setorcopyvar`. Então a **sub-rotina genérica** do §2.8 não é só
recomendada, ela é o que o motor permite escrever, e foi assim que ficou:

```asm
KurtCraft_EventScript_MakeLevel::
	setvar VAR_0x8006, ITEM_LEVEL_BALL
	setvar VAR_0x8007, ITEM_PERSIM_BERRY
	goto KurtCraft_EventScript_Make
```

Vinte e sete receitas, duas linhas cada, **um** corpo. As 324 linhas em que o bug
do §1.3 podia voltar (risco 1 do §6) deixaram de existir: existe um só lugar no
jogo onde a ordem espaço → consome → entrega → guarda está escrita.

Alocação de vars de rascunho, e ela não pode ser renumerada de leve:

| Var | Papel |
|---|---|
| `VAR_0x8004` | nível, de `ComputeLevel` |
| `VAR_0x8005` | berries por lote, de `ComputeCost` |
| `VAR_0x8006` | a bola que esta receita faz |
| `VAR_0x8007` | a berry que esta receita custa |
| `VAR_0x8000`/`0x8001` | **do `giveitem`** — é por isso que nada acima usa essas duas |

### 8.2 As seis correções

**1. Colisão de daily flag com o documento do altar.** Os dois pediam
`FLAG_UNUSED_0x949`. `FLAG_DAILY_KURT_NEW_DAY` ficou em **`+ 0x2E`**; o altar fica
com `+ 0x29` a `+ 0x2D`. Se os dois tivessem sido implementados em semanas
diferentes, o segundo teria redefinido a flag do primeiro **sem erro de build**.

**2. `FLAG_DAILY_BERRY_MASTER_RARE` não precisava existir.**
`FLAG_DAILY_BERRY_MASTERS_WIFE` (`DAILY_FLAGS_START + 0x11`) **já existia** no
bloco daily e **nenhuma linha do repositório a referenciava** — a mulher do Berry
Master de Hoenn trava em `FLAG_GARBAGEFLAG`, que é a gambiarra que o §5.2 já
manda não copiar. A flag nova saiu e a antiga foi reusada: a mulher da Route 30
custa **zero** alocação, e o plano inteiro passa de duas daily flags novas para
**uma**.

**3. Um backtick dentro de comentário fecha o bloco `raw` do poryscript.**
`scripts.pory` do Kurt é um `raw` … `` ` `` gigante. Um comentário `@ ... goto
KurtDaily ...` com o nome entre backticks (hábito de markdown) **encerra o bloco
raw ali** e o poryscript morre com
`could not parse top-level statement for 'goto'`. Sem backtick em comentário
dentro de `raw`, nunca.

**4. O sorteio virou sub-rotina, e a razão é estrutural.** O `KurtDaily` antigo
era um `script` de poryscript que terminava em `release`/`end`. Como agora a
conversa **continua** para o menu de receitas, ele foi reescrito como asm dentro
do bloco `raw`, terminando em `return`, e o `script KurtDaily { }` de poryscript
deixou de existir. O `goto KurtDaily` que o ramo da GS Ball fazia
(`KurtGsBall3`, o "Anyway, can I make you some Balls?") passou a apontar para
`KurtCraft_EventScript_Entry`.

**5. Três textos afirmavam "5 Berries" em número fixo.**
`KurtsHouse_Text_KurtBallsFromApricorns` ("bring 'em to me in batches of 5"),
`KurtAskYouHaveAnApricorn` ("You have 5 Berries for me?") e
`KurtThatsALetdown` ("I don't see 5 {STR_VAR_1}s!") deixam de ser verdade no
momento em que o custo cai com o nível (§2.3). Os três foram reescritos; o de
recusa agora usa `{STR_VAR_3} {STR_VAR_1}`, com o número vindo de `ComputeCost` e
o nome pluralizado por `bufferitemnameplural`.

**6. `MULTI_KURT_BALLS` não pode simplesmente sair do header.** O valor (116) é um
**índice de tabela** em `sMultichoiceLists`; apagar a linha renumeraria tudo
depois dela. A `MenuAction` e a entrada da tabela foram removidas e a constante
ficou como `MULTI_UNUSED_116`, com o motivo no comentário.

### 8.3 O menu: o §2.8 estava certo pelo motivo errado

O §2.8 diz que 27 receitas "não cabem em um" menu. **Cabem:**
`dynmultistack` tem `maxBeforeScroll` e rola a lista. O motivo real para os dois
passos é de leitura, não de capacidade — 27 linhas roláveis são um paredão — e por
isso a estrutura de dois passos **ficou**, com cinco grupos:

| Grupo | Rótulo no jogo | Receitas | Aparece a partir de |
|---|---|---|---|
| 0 | "Everyday Balls" | Poké, Great, Heal, Ultra | sempre (nível 1) |
| 1 | "My own recipes" | Level, Lure, Moon, Friend, Fast, Heavy, Love | nível 4 |
| 2 | "The new-fangled ones" | Nest, Net, Quick, Timer, Repeat, Dive, Dusk | nível 11 |
| 3 | "The hard ones" | Premier, Luxury, Sport, Park, Safari, Dream, Cherish, Strange | nível 16 |
| 4 | "BEAST BALL" | Beast | `VAR_RIFT_MISSIONS_STATE >= 15` |

O grupo do Beast Ball é uma **linha de primeiro nível**, não um submenu de um
item: ela leva direto à fabricação e é a única entrada do menu cuja condição é a
história e não o nível.

Detalhe do motor que faz isso funcionar: `dynmultipush` guarda um **id**, e
`dynmultistack` devolve **esse id** em `VAR_RESULT`, não a posição na lista
(`ScrCmd_dynmultipush`, `src/scrcmd.c:1926`). Então cada `case` do `switch` é um
id fixo e uma receita trancada **simplesmente não é empilhada** — nenhum índice se
desloca quando o Kurt aprende algo. É o mesmo padrão do `move_relearner.inc`.

E é isso que cumpre o §2.9 sem gastar caixa de fala: **o menu é a notificação.**
A outra metade é a neta, com quatro caixas por faixa de cinco níveis
(`KurtCraft_EventScript_GranddaughterTier`), e ela nunca diz um número.

### 8.4 Fontes de bola: o que a varredura do §1.4 não tinha

A regra "toda outra fonte de bola vira Poké Ball" foi aplicada com uma varredura
por grupo de mapa, ignorando `gMapGroup_Emerald1` a `5` como o §4 manda. Números
reais:

| O quê | Quantos | O que se fez |
|---|---|---|
| `ITEM_GREAT_BALL`/`ITEM_ULTRA_BALL` em `sShopInventories` | **24 linhas** em 18 listas | removidas |
| Bolas nos balcões especiais da campanha | **20** em 9 lojas | removidas (7 via `.pory`, 2 via `.inc`) |
| Bolas de chão/escondidas em mapas da campanha | **16** | viraram `ITEM_POKE_BALL` |
| Master Ball do prêmio do Battle Arcade | 1 | virou `ITEM_ABILITY_PATCH` |

Duas coisas que o §1.4 não listava:

- **A Quick Ball do prêmio da Buena** (`GoldenrodCity_RadioTower_2F`,
  `BuenaPrizeQuickBall`). **Ficou como está**, e é decisão a confirmar com o
  autor: é prêmio de minijogo por pontos, a mesma categoria das 30 Safari Balls
  que o §2.1 mantém de propósito. Se o autor quiser rigor total, é uma linha.
- **Os nomes das flags dos itens de chão ficaram mentindo.**
  `FLAG_ITEM_MTMORTAR2_ULTRA_BALL` agora guarda um lugar que dá uma Poké Ball.
  Renomear são quatro arquivos e zero ganho funcional; ficou como está, registrado
  aqui para ninguém "descobrir" isso como bug.

### 8.5 Berry Master: uma diferença do §5

O §5.2 mantinha a fala `Route30_BerryHouse_Text_CheckTrees` ("Check trees for
Berries. They grow back after 12 hours.") como a fala de segunda visita. Com o
presente diário no lugar dela, ela ficaria inalcançável, e a informação dela é a
que **ensina a mecânica** — então a frase foi **absorvida** por
`Route30_House_Text_PlantThem`, que é a caixa que o jogador passa a ver todo dia.
A do §5.6 (o `msgbox` sem vírgula) sumiu junto, porque era exatamente aquela
linha.

Os textos do §5.5 e a fala do Kurt no §2.5 estavam em **português** no documento.
Foram escritos em inglês, como manda o `CLAUDE.md`, e o Kurt ganhou plaquinha:
`SP_NAME_KURT` é o 14º falante. As falas dele que usavam o prefixo `"Kurt: "`
foram convertidas na mesma passada.

### 8.6 O que sobra para o teste em runtime

O §7 pendência 3 vale inteiro. Em ordem de risco:

- [ ] **O trecho Cherrygrove → Azalea** (risco 3 do §6): Poké Ball ilimitada na
      loja, 2 berries por dia na Route 30, nada do Kurt. É onde o ritmo pode
      virar frustração.
- [ ] **A virada de data com as quatro daily flags do sistema**
      (`KURT_FREE_BALLS`, `KURT_NEW_DAY`, `BERRY_MASTER_RECEIVED_BERRY`,
      `BERRY_MASTERS_WIFE`). Em especial: falar com o Kurt, virar o dia, falar de
      novo — a cota tem de zerar **e** o sorteio tem de voltar.
- [ ] **Bolsa cheia nos dois pontos do bug do §1.3**: antes de fabricar (recusa
      sem consumir) e na guarda depois do `giveitem`.
- [ ] **Berry insuficiente**: tem de voltar ao menu de grupos sem gastar cota.
- [ ] **A cota**: no nível 1, um lote e depois `KurtQuotaSpent`.
- [ ] **O sorteio não dá EXP**: falar com ele sete dias sem fabricar nada e
      conferir que o menu não cresceu.
- [ ] **A face 16**: antes de 360 de EXP ela não pode sair. Difícil de testar sem
      debug de var; vale conferir a linha e não o comportamento.
- [ ] **A Beast Ball aparece no menu no estado 15**, ou seja antes do Ato V do
      altar, e não depois.
