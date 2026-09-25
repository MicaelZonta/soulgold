# Auditoria — entrega de Pokémon e ovos (`givemon` / `giveegg`)

**Data:** 20/09/2026 · **Revisão:** V1 · **Escopo:** todo o repositório
**Regra auditada:** skill [`entregar-pokemon-ou-ovo`](../.claude/skills/entregar-pokemon-ou-ovo/SKILL.md)
**Motivo:** a correção do Friendly Trader de Cherrygrove
([`CHERRYGROVE_ULTRABEAST_IMPLEMENTATION.md`](../.claude/rift_missions/CHERRYGROVE_ULTRABEAST/CHERRYGROVE_ULTRABEAST_IMPLEMENTATION.md) §12.3
item 5) expôs um furo que não é local daquele NPC. Esta auditoria mede o
tamanho dele no jogo inteiro.

---

## 1. O problema em uma frase

`givemon` e `giveegg` devolvem **três** resultados, e a maioria dos scripts do
projeto só trata dois. Com a party **e** o PC cheios, o presente não é entregue —
e, em 18 pontos, o script marca o evento como concluído mesmo assim. O jogador
perde o Pokémon **para sempre**, com build limpo e sem nenhum sintoma.

```
GiveCapturedMonToPlayer (src/pokemon.c:2949)
  MON_GIVEN_TO_PARTY 0   vaga na party
  MON_GIVEN_TO_PC    1   party cheia, PC com vaga
  MON_CANT_GIVE      2   party cheia E PC cheio  ← ninguém trata
```

`Common_EventScript_GiftMon` (`data/event_scripts.s:1152`), o helper mais usado
do projeto, **retorna calado** em `MON_CANT_GIVE`. O script continua, seta a
flag de "já pegou", o NPC se despede, e o jogador não recebeu nada.

---

## 2. Resumo executivo

De **63** chamadas encontradas, 15 são código morto ou debug. Das **48 reais**:

| Camada | Sites | Eventos | O que acontece com party+PC cheios |
|---|---:|---:|---|
| **A — Perda de conteúdo** | **18** | **10** | Nada é entregue **e o evento se tranca**. Irrecuperável sem editar o save. |
| **B — Mudo** | 1 | 1 | Nada é entregue, nada avisa, mas dá para repetir |
| **C — Seguro** | 25 | 13 | Avisa e continua disponível. Trata os três resultados |
| **D — Correto** | 4 | 4 | Checa **antes** do diálogo de oferta |

> **10 eventos perdem conteúdo permanentemente.** Entre eles: o ovo de
> **Jirachi**, cinco míticos do mural de conquistas (**Zarude**, **Magearna**,
> **Poipole**, **Greninja-Bond**, **Floette Eterna**), **Victini**, **Kubfu** e
> os três starters de Hoenn.

A boa notícia: os presentes mais críticos do começo de jogo — **os starters de
Johto**, os fósseis e os prêmios do Game Corner — já estão corretos. O problema
está concentrado em **conteúdo de pós-game e recompensa rara**, que é exatamente
o que o jogador coleta quando a party e as caixas já estão cheias. **A população
em risco é a mesma que sofre o bug.**

---

## 3. Camada A — perda de conteúdo (prioridade 1)

Ordenada por gravidade. "Trava" = o que impede de tentar de novo.

### A1 · Ovo de Jirachi — `MtSilver_SummitDay/scripts.pory:107`

**O pior caso do repositório.** Único que anuncia a entrega **antes** de
entregar, e o único em que o doador desaparece do mapa no mesmo script:

```
msgbox("{PLAYER} received an Egg!")      ← promete
giveegg(SPECIES_JIRACHI)                 ← pode falhar
...
setflag(FLAG_HIDE_MTSILVER_RIVAL)        ← e o rival some
removeobject(LOCALID_MTSILVER_RIVAL)
setvar(VAR_RIVAL_STATE, 12)              ← e o arco do rival avança
```

O jogo afirma que você ganhou um Jirachi, você não ganha nada, e quem daria sai
do mapa. **Trava:** `VAR_RIVAL_STATE = 12` + `FLAG_HIDE_MTSILVER_RIVAL`.

### A2 · Mural de conquistas — `Route40_House4/scripts.pory` (5 sites)

| Linha | Pokémon | Marco |
|---|---|---|
| 119 | `SPECIES_GRENINJA_BOND` | 30 |
| 139 | `SPECIES_POIPOLE` | 45 |
| 158 | `SPECIES_FLOETTE_ETERNAL` | 60 |
| 178 | `SPECIES_ZARUDE` | 75 |
| 200 | `SPECIES_MAGEARNA_ORIGINAL` | 100 |

Todos seguem `givemon` → `Common_EventScript_GiftMon` →
`setvar(VAR_ACHIEVEMENT_REWARD_MILESTONE, <marco>)`. A var é a porta
(`scripts.pory:21-41`), então o marco nunca é reoferecido.

**Este é o caso de maior probabilidade real.** São recompensas de longo prazo,
entregues a quem jogou muito — ou seja, a quem tem 6 na party e as caixas
cheias. Cinco míticos exclusivos de evento, cinco oportunidades de perder.

### A3 · Demais eventos da camada A

| Evento | Arquivo:linha | Pokémon | Trava |
|---|---|---|---|
| Victini do aposentado | `KitakamiRoad_House/scripts.pory:122` | Victini | `FLAG_GOT_VICTINI` |
| Beldum do Steven | `Kitakami_Houses/scripts.pory:155` | Beldum + Luxury Ball | `FLAG_MET_STEVEN` (porta em `:50`) |
| Kubfu | `BlackthornCave/scripts.pory:28` | Kubfu | `FLAG_GOT_KUBFU` |
| Gimmighoul | `CianwoodHouse3/scripts.pory:168` | Gimmighoul Chest | `FLAG_CIANWOOD_GIMMIGHOUL` |
| Dratini do Shrine | `DragonsDen_Shrine/scripts.inc:998` e `:1012` | Dratini c/ Extreme Speed | `FLAG_GOT_DRATINI` |
| Presente do Bill | `GoldenrodCity_BillsHouse/scripts.pory:102` e `:117` | Eevee ou Pikachu starter | `FLAG_GOT_BILL_GIFTMON` |
| Tyrogue do Kiyo | `MtMortar_B1F/scripts.inc:25` | Tyrogue | `FLAG_GOT_TYROGUE` |
| Starters de Hoenn | `SaffronCity_SilphCo/scripts.inc:41`, `:49`, `:57` | Treecko / Torchic / Mudkip | `FLAG_GOT_HOENN_STARTER`, que é a **flag do template do objeto do Steven** (`map.json`) — ele some do mapa |

> **Agravante no presente do Bill** (`:102`, `:117`): o
> `setflag(FLAG_GOT_BILL_GIFTMON)` vem **antes** do
> `call(Common_EventScript_GiftMon)`. O evento se tranca mesmo na ordem de
> execução, não só por omissão.

---

## 4. Camada B — mudo, mas recuperável

| Evento | Arquivo:linha | Observação |
|---|---|---|
| Tentacool do pescador | `CianwoodPokecenter/scripts.inc:26` | Marca com `FLAG_TEMP_1`, que zera a cada load — sair do mapa e voltar reoferece. Perde-se só a tentativa |

---

## 5. Camada C — seguro (os modelos a copiar)

Tratam os três resultados e **não** avançam estado no caminho de erro. Nenhuma
ação necessária; servem de referência.

| Evento | Arquivo | Sites | Padrão |
|---|---|---:|---|
| Starters de Johto | `LittlerootTown_ProfessorBirchsLab/scripts.pory` | 3 | `goto_if_eq` PARTY / PC → `goto Common_EventScript_NoMoreRoomForPokemon`; o `removeobject` da Poké Ball só roda nos ramos de sucesso |
| Fósseis | `RuinsOfAlph_Lab/scripts.pory` | 7 | Mesmo padrão. **`VAR_FOSSIL_RESURRECTION_STATE` só volta a 0 nos ramos de sucesso**, então o fóssil consumido não se perde: o resgate continua pendente |
| Fósseis (Devon) | `RustboroCity_DevonCorp_2F/scripts.inc` | 2 | idem |
| Prêmios do Game Corner | `GoldenrodCity_GameCorner/scripts.pory` | 6 | `CheckReceivedMon` trata 0/1/2; **`removecoins` só nos ramos de sucesso** — não cobra por prêmio não entregue |
| Battle Café | `BattleCafe/scripts.pory` | 3 | guarda `MON_CANT_GIVE` antes do `setflag` |
| Ovo de Arceus (Oak) | `GoldenrodCity_RadioTower_2F/scripts.pory:645` | 1 | guarda antes de `FLAG_ARCEUS_EGG_GIVE`, com fala própria de "sem espaço" |
| Ovo de Wynaut | `LavaridgeTown/scripts.inc:245` | 1 | vanilla |
| Beldum do Steven (Mossdeep) | `MossdeepCity_StevensHouse/scripts.inc:85` | 1 | vanilla |
| Castform | `Route119_WeatherInstitute_2F/scripts.inc:85` | 1 | vanilla |

**Observação:** os da camada C tratam o erro **depois** do diálogo de oferta.
Estão seguros (não perdem conteúdo), mas ainda prometem antes de conferir. A
regra da skill pede a checagem **antes**. Promovê-los para a camada D é polimento
de UX, não correção de bug — **prioridade 3**.

---

## 6. Camada D — correto

| Evento | Arquivo | Como |
|---|---|---|
| Ovo de Cosmog (Gladion) | `VioletCity_PokemonCenter/scripts.pory:16-22` | `getpartysize` + `ScriptCheckFreePokemonStorageSpace` antes da cena; guarda defensiva depois da batalha |
| Presente do Friendly Trader | `CherrygroveCity/scripts.pory`, `Cherrygrove_FriendlyTrader` | idem, com `Cherrygrove_TraderNoRoom` compartilhado |
| Pichu do Mystery Gift | `data/scripts/gift_pichu.inc:6-8` | **Exceção legítima:** checa `CalculatePlayerPartyCount` e exige vaga **na party**, não aceitando o PC, porque depois usa o índice do slot (`setmonmove`, `setmonmetlocation`). `FLAG_MYSTERY_GIFT_DONE` só é setada depois de passar |

> **Regra derivada do Pichu, que a skill registra:** quando o script precisa do
> **índice do slot** depois de entregar, ele tem de exigir vaga na party e
> bloquear com a party cheia — mandar para o PC deixaria o índice inválido. Nos
> demais casos, bloquear só com party cheia é errado.

---

## 7. Excluídos da contagem

| Origem | Sites | Por quê |
|---|---:|---|
| `Route25_BillsHouse_EventScript_Test` (`scripts.inc:143-149`) | 5 | Script de teste, **sem nenhuma referência** no repo |
| `SafariZoneGate_SafariZoneEntrance_EventScript_Test` (`scripts.inc:179-184`) | 4 | idem |
| `data/scripts/debug.inc:12-17` | 6 | Menu de debug |

Os dois scripts `_Test` são código morto e podem ser apagados num trabalho de
limpeza — **não** fazem parte desta auditoria.

---

## 8. Prioridade de correção

1. **A1 (Jirachi)** — único que promete antes de entregar e remove o doador.
   Além da checagem, a fala de "sem espaço" tem de manter `VAR_RIVAL_STATE` e
   `FLAG_HIDE_MTSILVER_RIVAL` intocados.
2. **A2 (mural de conquistas, 5 míticos)** — maior probabilidade real, maior
   volume de conteúdo exclusivo. Os cinco compartilham estrutura: cabe um único
   rótulo de "sem espaço" no arquivo, como em Cherrygrove.
3. **A3 (8 eventos restantes)** — mesma correção, um de cada vez.
4. **B (Tentacool)** — barato, sem risco.
5. **C → D** — polimento de UX, opcional.

Em todos: a checagem entra **antes do diálogo de oferta**, e o caminho de erro
**não pode setar nenhuma flag/var de conclusão**.

---

## 9. Como corrigir

O passo a passo, o snippet em poryscript e asm, a ordem em relação ao `setflag`
e o que o texto de "sem espaço" precisa dizer estão na skill
[`entregar-pokemon-ou-ovo`](../.claude/skills/entregar-pokemon-ou-ovo/SKILL.md)
(§2 a §5 e §8). Resumo:

```
	getpartysize
	if (var(VAR_RESULT) == PARTY_SIZE) {
		specialvar(VAR_RESULT, ScriptCheckFreePokemonStorageSpace)
		if (var(VAR_RESULT) == FALSE) { goto(<Mapa>_NoRoom) }
	}
	msgbox("...a oferta começa aqui...")
```

Decisão registrada do autor (20/09/2026): **corrigir sem consultar** sempre que
se encostar num script de entrega. Uma varredura das 10 correções da camada A é
trabalho de escopo próprio e precisa de aval.

---

## 10. Metodologia e reprodução

Levantamento automático, **classificação conferida à mão** — a detecção
automática errou em quatro grupos, todos re-verificados lendo o código:

- `RuinsOfAlph_Lab` e `LittlerootTown_ProfessorBirchsLab` pareciam sem rede:
  tratam o erro via `Common_EventScript_NoMoreRoomForPokemon`, sem citar
  `MON_CANT_GIVE`.
- `GoldenrodCity_GameCorner` trata num rótulo alcançado por `goto`, longe da
  chamada.
- `SaffronCity_SilphCo` tranca num rótulo compartilhado (`AfterStarterGiven`)
  pelos três ramos.
- `VioletCity_PokemonCenter` e `CherrygroveCity` checam no topo do script, longe
  da chamada.

Ponto de partida:

```bash
grep -rnE "\bgive(mon|egg)\b" \
  data/maps/*/scripts.pory data/maps/*/scripts.inc \
  data/scripts/ data/event_scripts.s
```

Para cada ocorrência foram respondidas três perguntas, lendo o código:

1. Há checagem de espaço **antes** do diálogo de oferta?
2. Os três resultados de `givemon`/`giveegg` são tratados **depois**?
3. O caminho de falha avança alguma flag/var/`removeobject` que **impeça
   repetir**? *(é esta que separa a camada A da C)*

Auditoria feita sobre o arquivo-fonte de cada mapa (`.pory` quando existe,
`.inc` quando não), nunca sobre `.inc` gerado.
