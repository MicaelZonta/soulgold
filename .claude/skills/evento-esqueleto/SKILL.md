---
name: evento-esqueleto
description: Use ao planejar ou implementar um evento de historia em modo ESQUELETO - dialogos curtos e placeholder, coreografia minima, mas estado, flags, visibilidade, gatilhos, batalha e retry completos e corretos - e ao escrever o documento de implementacao (<EVENTO>_IMPLEMENTATION.md) que outro agente vai usar para incrementar a cena depois. Vale para as Rift Missions (Looker/Anabel, Ultra Beasts; estrutura padrao escolha-qual-UB-enfrentar + boss battle) e qualquer evento novo feito nesse ritmo. Tambem use ao evoluir um esqueleto existente, para saber o que pode e o que nao pode mudar.
---

# Evento em modo esqueleto

Esqueleto = **o evento inteiro funciona de ponta a ponta no jogo**, com o
mínimo de enfeite. Quem pega o trabalho depois só acrescenta: fala melhor,
movimento mais bonito, time mais difícil. Nunca precisa refazer estado,
flags ou gatilhos.

Exemplo real completo: [`.claude/rift_missions/BLACKTHORN_ULTRABEAST/BLACKTHORN_ULTRABEAST_IMPLEMENTATION.md`](../../rift_missions/BLACKTHORN_ULTRABEAST/BLACKTHORN_ULTRABEAST_IMPLEMENTATION.md).
Design da questline: [`.claude/rift_missions/SOULGOLD_RIFT_MISSIONS_DESIGN.md`](../../rift_missions/SOULGOLD_RIFT_MISSIONS_DESIGN.md).

## 1. A linha que separa esqueleto de gambiarra

| Pode ser simples (esqueleto) | Tem que estar completo desde já |
|---|---|
| Diálogo curto, placeholder, em inglês | Máquina de estados: toda var/flag com significado, quem escreve e quem lê |
| Fade no lugar de caminhada longa | Visibilidade pelo campo `flag` do template, recalculada no load |
| Ruptura = tremor + flash; bicho surge parado | Gatilho que dispara uma vez e não congela o jogo |
| Nível/time placeholder, sem item/golpes | Todos os resultados de batalha tratados; derrota nunca vira vitória |
| NPC some em fade em vez de sair pela porta | Retry depois de blackout sem estado novo e sem softlock |
| Stub "volte depois" para a próxima etapa | Coordenadas e caminhos medidos na colisão real |
| | Pré-checagens (party, espaço na bolsa) antes de qualquer mudança de estado |
| | Build limpo |

Se para ficar "simples" você precisa pular algo da coluna da direita, não é
esqueleto — é bug adiado. Pare e resolva.

## 2. Carregue as skills de sempre

O esqueleto não dispensa nenhuma armadilha. Antes de escrever:

- `visibilidade-e-gatilhos` — flag de template, `FLAG_TEMP_*` como cache, gatilho de frame.
- `encenar-cutscene` — `dump_mapa.py`, colisão de 1 bit, `y` cresce para baixo.
- `parceiro-pokemon-de-npc` — Silvally/Ninetales ao lado do dono.
- `batalha-sem-blackout` ou `adicionar-batalha-npc` — conforme o tipo de luta.

Rift Missions: luta contra Ultra Beast é **batalha de ameaça** — perder é
blackout e retry, **sem** `B_FLAG_NO_WHITEOUT`. Luta contra personagem
(Lillie, Gladion, Lusamine) é duelo narrativo — sem blackout.

## 3. Estado: decida antes de escrever qualquer script

1. **Uma var de progresso por arco**, com tabela de valores. Nas Rift Missions
   é `VAR_RIFT_MISSIONS_STATE` (valores no doc de Blackthorn §1.2). Próxima
   missão continua a numeração; não crie outra var.
2. **Flag persistente só quando o `map.json` exige** (o campo `flag` não lê
   var). Ex.: `FLAG_EVENT_ULTRABEAST_BLACKTHORN` esconde a cidade.
   Escreva a **invariante** flag ⇔ valor da var e mude as duas no mesmo script.
3. **Todo o resto é temporário**: `FLAG_TEMP_*` para aparecer/sumir num mapa
   só, `VAR_TEMP_*` para trava de gatilho e resultado de batalha. Confira que
   estão livres com `grep` no mapa e em `data/scripts/`.
4. **Retry vem de graça** se o estado "ativo" só é limpo na vitória: o blackout
   te devolve ao Centro, a flag continua setada, o load recalcula tudo.
5. Números novos: var livre depois da última usada em `vars.h`; flag no fim do
   bloco custom de `flags.h`, atualizando `CUSTOM_FLAGS_END`, com comentário
   de quem seta/limpa. Nunca reaproveite flag "que parece livre".

## 4. Padrões que o esqueleto usa

**Início determinístico.** Faça o jogador só conseguir falar com o NPC de um
tile (bolso de parede, parceiro bloqueando o outro lado) ou cheque
`getplayerxy` e desista da coreografia se ele não estiver onde a cena espera.
Nunca escreva caminho que só funciona "se o jogador veio pelo lado certo".

**Último ponto de saída explícito.** Pré-checagens → pergunta SIM/NÃO → a
partir do SIM, tudo é script até o fim. Nada de estado mudado antes do SIM.

**Estrutura padrão das Rift Missions: escolha + boss.** Toda missão com mais
de uma Ultra Beast funciona assim (decisão do autor, 19/09/2026):

1. As UBs aparecem juntas.
2. O jogador **escolhe qual enfrenta** (`dynmultichoice` com `ignoreBPress
   TRUE`, resultado em `VAR_TEMP_*`). O acompanhante da missão fica com a(s)
   outra(s). A escolha é por tentativa: depois de um blackout, escolhe de novo.
3. A luta do jogador é um **boss simples** pelo sistema do projeto.
4. A luta do acompanhante é narrativa: resolve junto com a vitória do
   jogador, e a fala depois da batalha muda conforme a escolha.

```asm
	setflag B_FLAG_NO_CATCHING       @ limpa pela engine no fim de toda batalha: setar logo antes
	setbossbattle 2, SPECIES_NONE, 110, BOSS_PHASE_PROFILE_NONE
	playmoncry SPECIES_X, CRY_MODE_ENCOUNTER
	waitmoncry
	seteventmon SPECIES_X, LV
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	copyvar VAR_TEMP_2, VAR_RESULT
	goto_if_eq VAR_TEMP_2, B_OUTCOME_WON, <Resolvido>
	goto <NaoResolvido>              @ nunca cair na vitória por omissão
```

Fatos do sistema de boss (`src/battle_boss.c`, macros em `asm/macros/event.inc`
perto de `setbossbattle`):

- **Só batalha simples.** Dupla cancela o boss. Por isso a escolha também é a
  solução técnica: não existe dupla selvagem com parceiro sem o NPC follower,
  que está desligado.
- Só `BattleSetup_StartLegendaryBattle` aplica o boss pendente; `dowildbattle` não.
- IA inteligente é automática no boss.
- "Run" no boss é desistência: `B_OUTCOME_FORFEITED` → blackout, igual a
  perder. Não precisa de `B_FLAG_NO_RUNNING` (o boss nem o consulta).
- Boss é capturável por padrão: bloqueie com `B_FLAG_NO_CATCHING` quando a
  missão não deve dar a UB ainda.
- LOST/DREW/FORFEITED dão blackout sozinhos; o script não continua.

Missão com três UBs (Missão 4): o jogador escolhe uma; Lusamine e Anabel ficam
com as outras duas. Looker não batalha.

Looker e Anabel moram em Olivine e aparecem também no local da missão ao
mesmo tempo — aceito, porque a missão inteira é cutscene. Não gaste flag
para escondê-los em Olivine.

**Fim de cena que muda a população do mapa.** Mude flag/var sob fade e
recarregue no lugar com `warpsilent <MAPA>, x, y` + `waitstate`. O
`ON_TRANSITION` recalcula quem aparece; ninguém surge do nada quando a câmera
anda, e não há `removeobject` em objeto de flag alheia.

**NPC que mora num lugar fixo (Looker e Anabel em Olivine).** Sem flag: o
objeto existe desde o New Game e a var de progresso só troca o diálogo. Nunca
`removeobject` num objeto de flag `0`: ele volta no primeiro passo. Saídas de
cena são feitas andando de volta ao lugar.

## 5. Convenções no código

- Comentário `@` no topo de cada bloco com a **planta**: coordenadas de todos
  os atores, caminho completo de cada movimento, direção de olhar derivada.
- Marque o que é provisório com `@ SKELETON:` e uma frase dizendo o que falta
  (`@ SKELETON: fala placeholder, reescrever pela voz do design §3.1`).
  Um `grep -rn "SKELETON:" data/` tem que listar tudo que falta polir.
- Textos em inglês, curtos, com o nome do falante no começo da caixa.
- Stub de etapa futura é um script real e inofensivo ("come back soon"),
  nunca um label vazio ou um objeto sem script.

## 6. O documento de implementação

Um arquivo por evento em `.claude/<EVENTO>_IMPLEMENTATION.md`, escrito
**antes** do código e atualizado quando o código divergir. Estrutura:

1. **Status e escopo** — do quê até o quê; qual o gancho final.
2. **Resumo do fluxo** — diagrama em texto com os valores da var.
3. **Estado** — constantes novas com número e arquivo; tabela da var (valor,
   significado, quem escreve, quem lê); invariantes; temporários por mapa.
4. **Uma seção por etapa/mapa** — arquivo a editar (`.pory` ou `.inc`),
   objetos novos (local id, gráfico, x/y, movimento, script, flag), planta
   ASCII tirada do `dump_mapa.py`, scripts em asm, textos.
5. **Tabela de resultados** da batalha e o que acontece em cada um.
6. **Arquivos tocados** — checklist.
7. **Esqueleto × evolução** — o que está simples e como evoluir; e o que
   **não pode regredir** numa evolução.
8. **Pendências e riscos** — com arquivo/linha quando houver.
9. **Teste em runtime** — checklist, incluindo perder de propósito,
   salvar/recarregar em cada estado e chegar ao mapa por todas as entradas.

E registre no design (`SOULGOLD_RIFT_MISSIONS_DESIGN.md`, tabela de status)
o estado do evento: planejado / esqueleto implementado / evoluído.

## 7. Evoluindo um esqueleto

- Leia o doc de implementação inteiro antes; ele é o contrato.
- Pode trocar: textos, movimentos, fades por caminhadas, time/nível/IA, música.
- Não pode trocar sem atualizar o doc e o design: valores da var, invariantes,
  flags, ponto de saída, tratamento de resultados, local ids (objetos novos
  sempre no **fim** de `object_events`).
- Ao terminar, apague o `@ SKELETON:` correspondente e atualize a seção 7 do doc.
- Para a passada de **história** (falas finais, arco da cena, surpresas, reações
  opcionais), use a skill `evoluir-historia-de-evento`.

## Checklist

- [ ] Tabela da var e invariantes escritas antes do primeiro script
- [ ] Nenhuma flag persistente além das exigidas pelo `map.json`
- [ ] Toda coordenada e caminho conferidos no `dump_mapa.py`
- [ ] Início da cena determinístico; SIM/NÃO antes de qualquer mudança de estado
- [ ] Rift Mission: jogador escolhe a UB, acompanhante fica com a outra, luta via boss simples com captura bloqueada
- [ ] Todos os resultados de batalha tratados; perder e desistir ("Run") testados de propósito
- [ ] Retry funciona só com o estado existente
- [ ] Fim da cena recarrega o mapa sob fade quando a população muda
- [ ] `@ SKELETON:` em tudo que é provisório
- [ ] Doc de implementação com as 9 seções; status atualizado no design
- [ ] `make -j$(nproc)` limpo
