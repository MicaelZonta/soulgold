# Auditoria — substituir o assistente do Elm por Gladion na entrega do Mystery Egg (Violet City)

Levantamento apenas. Nenhum arquivo de jogo foi alterado para produzir este documento.

## Achado transversal — leia antes do resto

`.claude/SOULGOLD_RIFT_MISSIONS_DESIGN_V1.md` (linhas 54-73) já define o arco do Gladion, e ele **não** passa por Violet City nesse momento:

> "Gladion em Goldenrod | Retorno ao Ginásio para resolver a entrega da insígnia, enquanto Whitney está chorando | Antes de o jogador entrar, Gladion sai, interpreta a situação como algo provocado pelo jogador e o desafia."

Esse é o primeiro encontro nomeado planejado para ele — cronologicamente **depois** de Violet City (Goldenrod vem depois do ginásio da Whitney/Bugsy, Violet é o primeiro ginásio do jogo). A única aparição de Gladion hoje implementada antes disso é o cameo silencioso em `Route29_EventScript_Gladion` ("…", "…Tch"), sem nome nem reconhecimento — compatível com um "misterioso testando você". O pedido atual ("Gladion reconhece o jogador pelo que Lillie contou") é uma cena **falada e nomeada**, o que antecipa a apresentação formal dele para antes do 1º badge e entra em conflito direto com o gatilho de Goldenrod já desenhado. Isso não bloqueia a auditoria técnica abaixo, mas é uma decisão de roteiro que precisa ser resolvida (ou o doc de design atualizado) antes de implementar.

Some a isso: todas as falas atuais do fluxo tratam essa pessoa explicitamente como **funcionário/estagiário do Elm** ("my assistant", "my aide", "Prof. Elm asked me to find you"). Trocar o personagem por Gladion exige reescrever essas falas para justificar por que ele está fazendo esse favor para Elm (ou por que Elm o chama de "assistente"), não só trocar sprite.

---

## 1. Gatilho e texto da ligação do Elm em Violet

**Arquivo/label:** `data/maps/VioletCity/scripts.pory:181-190` (`VioletCity_EventScript_ElmCall_Trigger`), disparado pelo `map_script_2 VAR_VIOLET_CITY_STATE, 3, VioletCity_EventScript_ElmCall_Trigger` na linha 12. Texto em `VioletCity_Text_Elm_Call` (linhas 469-474).

**Comportamento atual:**
```
VioletCity_EventScript_ElmCall_Trigger::
	lock
	pokenavcall VioletCity_Text_Elm_Call
	waitmessage
	delay 30
	clearflag FLAG_HIDE_VIOLET_CITY_AIDE
	setflag FLAG_HIDE_NEWBARKTOWN_LAB_AIDE
	setvar VAR_VIOLET_CITY_STATE, 4
	release
	end
```
Texto: *"Elm: Hello, {PLAYER}? We discovered something about the Egg! My assistant is at the Pokémon Center in Violet City. Could you talk to him?"*

**Alteração necessária:** só o texto (trocar "My assistant" por algo que justifique Gladion — ex. "Gladion said he'd meet you there" — mas isso implica que Elm e Gladion já se conhecem, o que também precisa ser coerente com o resto da história). A lógica do gatilho (`clearflag`/`setflag`/`setvar`) não precisa mudar.

**Estado reutilizável:** `VAR_VIOLET_CITY_STATE == 3` (setado em `VioletCity_Gym/scripts.pory:47`, após o ginásio) já é o gatilho correto e único; nenhum novo var necessário.

**Risco:** nenhum técnico. Risco de coerência: a fala liga Elm→"assistant" diretamente a Gladion; se Gladion não é funcionário do Elm, a frase soa errada e precisa de reescrita, não só substituição de nome.

---

## 2. Como o assistente aparece no Pokémon Center e desaparece do laboratório

**Arquivos/labels e flags envolvidas:**
- `include/constants/flags.h`: `FLAG_HIDE_VIOLET_CITY_AIDE` (0x37A), `FLAG_HIDE_NEWBARKTOWN_LAB_AIDE` (0x35C).
- `data/maps/VioletCity_PokemonCenter/map.json`, object event índice 6: `graphics_id: OBJ_EVENT_GFX_SCIENTIST_M`, `flag: FLAG_HIDE_VIOLET_CITY_AIDE`, `script: VioletCity_PokemonCenter_EventScript_Aide`, sem `local_id` explícito.
- `data/maps/NewBarkTown_Lab/map.json`: `LOCALID_AIDE1`, `graphics_id: OBJ_EVENT_GFX_SCIENTIST_M`, `flag: FLAG_HIDE_NEWBARKTOWN_LAB_AIDE`, `script: NewBarkTown_EventScript_Aide1`.

**Comportamento atual (ciclo completo):**
1. `new_game.inc` — nunca toca `FLAG_HIDE_VIOLET_CITY_AIDE` diretamente; quem garante que ele começa escondido é o trigger de chegada `VioletCity_EventScript_Trigger` (`data/maps/VioletCity/scripts.pory:24-50`, ligado ao `Gate_Route31_VioletCity/map.json:82`), que faz `setflag FLAG_HIDE_VIOLET_CITY_AIDE` (linha 45) na primeira entrada em Violet City. `NewBarkTown_Lab_Aide1` já nasce visível (`clearflag FLAG_HIDE_NEWBARKTOWN_LAB_AIDE` em `new_game.inc:122`).
2. `VioletCity_EventScript_ElmCall_Trigger` (item 1) inverte os dois: esconde o do laboratório, mostra o de Violet.
3. `VioletCity_PokemonCenter_EventScript_Aide_Accepted` (item 3), ao entregar o ovo, inverte de novo: `setflag FLAG_HIDE_VIOLET_CITY_AIDE` / `clearflag FLAG_HIDE_NEWBARKTOWN_LAB_AIDE`.

**Alteração necessária:** nenhuma na lógica de flags — é exatamente o padrão "um personagem, duas posições" que o Gladion precisa. Só trocar `graphics_id` de `OBJ_EVENT_GFX_SCIENTIST_M` para `OBJ_EVENT_GFX_GLADION` no object event de Violet City PC (o de New Bark Town Lab pode continuar como cientista genérico, já que ali é só "o aide está ausente", ninguém vê o Gladion lá).

**Estado reutilizável:** `FLAG_HIDE_VIOLET_CITY_AIDE` + `FLAG_HIDE_NEWBARKTOWN_LAB_AIDE`, sem novas flags.

**Risco:** baixo. Único ponto de atenção: o object event de Violet City PC não tem `local_id` nomeado — se a cena do Gladion precisar de `turnobject`/`applymovement` (ex. um gesto de reconhecimento), é preciso declarar `.set LOCALID_<algo>, 6` no `.pory` (índice = posição no array + 1, confirmado contando os 6 object_events do mapa).

---

## 3. Script completo de entrega do Mystery Egg

**Arquivo:** `data/maps/VioletCity_PokemonCenter/scripts.pory:12-115`.

```
VioletCity_PokemonCenter_EventScript_Aide::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_MYSTERY_EGG, VioletCity_PokemonCenter_EventScript_Aide_Received
	msgbox VioletCity_PokeCenter_Text_ElmsAideFavor, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, VioletCity_PokemonCenter_EventScript_Aide_Refuse
	goto_if_eq VAR_RESULT, YES, VioletCity_PokemonCenter_EventScript_Aide_Accepted
	release
	end

VioletCity_PokemonCenter_EventScript_AideNoRoom::
	msgbox VioletCity_PokeCenter_Text_ElmsAideNoRoom, MSGBOX_DEFAULT
	closemessage
	release
	end

VioletCity_PokemonCenter_EventScript_Aide_Refuse::
	msgbox VioletCity_PokeCenter_Text_ElmsAideRefuse, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, VioletCity_PokemonCenter_EventScript_Aide_Refuse
	goto_if_eq VAR_RESULT, YES, VioletCity_PokemonCenter_EventScript_Aide_Accepted
	release
	end

VioletCity_PokemonCenter_EventScript_Aide_Accepted::
	msgbox VioletCity_PokeCenter_Text_ElmsAideGiveEgg, MSGBOX_DEFAULT
	giveegg SPECIES_COSMOG
	goto_if_eq VAR_RESULT, MON_CANT_GIVE, VioletCity_PokemonCenter_EventScript_AideNoRoom
	playfanfare MUS_OBTAIN_ITEM
	message LavaridgeTown_Text_ReceivedTheEgg
	waitfanfare
    call VioletPCGiveExpJar
    closemessage
	setflag FLAG_RECEIVED_MYSTERY_EGG
	setflag FLAG_HIDE_VIOLET_CITY_AIDE
	setvar VAR_VIOLET_CITY_KIMONO_GIRL, 1
	clearflag FLAG_HIDE_VIOLET_CITY_KIMONO_GIRL
	clearflag FLAG_HIDE_NEWBARKTOWN_LAB_AIDE
	release
	end

VioletCity_PokemonCenter_EventScript_Aide_Received::
	msgbox VioletCity_PokeCenter_Text_ElmsAideGiveEgg, MSGBOX_DEFAULT
	closemessage
	release
	end
```

Textos: `VioletCity_PokeCenter_Text_ElmsAideFavor/NoRoom/GiveEgg/GiveItem/FullParty/Refuse` (linhas 83-115). Nota: `VioletCity_PokeCenter_Text_ElmsAideFullParty` e `VioletCity_PokeCenter_Text_ElmsAideGiveItem` estão **definidos mas nunca referenciados** em nenhum `msgbox` — texto órfão, sobra de um fluxo anterior.

**Alteração necessária:** este é o script onde a batalha entra (ver item 4) e onde todos os textos precisam de nova voz (Gladion, não "Elm's aide").

**Estado reutilizável:** `FLAG_RECEIVED_MYSTERY_EGG` já cobre "já entreguei" vs. "ainda não"; nenhuma flag nova.

**Risco:** baixo isoladamente — o risco real está em como a batalha é encaixada aqui dentro (item 4/5).

---

## 4. Onde inserir a batalha obrigatória contra Gladion

**Ponto exato:** dentro de `VioletCity_PokemonCenter_EventScript_Aide_Accepted`, entre o `msgbox` de aceitação e o `giveegg`. Padrão idêntico ao de Lillie em `Route30_MrPokemonsHouse/scripts.pory:86-95` (documentado em `.claude/encenar-evento.md` e `.claude/adicionar-batalha-npc.md`):

```
VioletCity_PokemonCenter_EventScript_Aide_Accepted::
	msgbox VioletCity_PokeCenter_Text_GladionRecognizes, MSGBOX_DEFAULT   @ novo texto
	closemessage
	removefieldmugshot                                                    @ garantia, por padrão do projeto
	trainerbattle_no_intro TRAINER_GLADION, VioletCity_PokeCenter_Text_GladionDefeated
	msgbox VioletCity_PokeCenter_Text_GladionGiveEgg, MSGBOX_DEFAULT      @ pós-vitória
	giveegg SPECIES_COSMOG
	goto_if_eq VAR_RESULT, MON_CANT_GIVE, VioletCity_PokemonCenter_EventScript_AideNoRoom
	...
```

**Por que `trainerbattle_no_intro` e não `trainerbattle_single`:** o NPC é `TRAINER_TYPE_NONE` (só briga se você falar com ele, como Lillie/Kukui/Gladion na Route29 — confirmado em `adicionar-batalha-npc.md:276-278`), e a fala de reconhecimento já é dada manualmente por `msgbox` antes do comando, então não se quer a fala automática de avistamento do `trainerbattle_single`.

**Estado/flag reutilizável:** a flag de derrotado do `TRAINER_GLADION` é automática e derivada do ID (`TRAINER_FLAGS_START + 967`, `include/constants/flags.h`) — não é uma flag nova a criar.

**Risco — este é o ponto mais importante do pedido:**
- `TRAINER_GLADION` (ID 967) **já existe e já é usado** em `Route29_EventScript_Gladion` (`trainerbattle_single TRAINER_GLADION, ...`), com o time atual de `src/data/trainers.party:19712` sendo **1x Rattata nível 5, IVs 0** — claramente um placeholder de cameo, não um time para uma batalha obrigatória e "reconhecida" em Violet City.
- Reaproveitar o **mesmo ID** nos dois lugares significa reaproveitar o **mesmo time**. Se a batalha em Violet precisa ser mais robusta/condizente com a cena, editar `TRAINER_GLADION` também muda a Rattata do cameo da Route29.
- A flag de derrotado é compartilhada pelo ID: Route29 é passagem obrigatória entre New Bark Town e Cherrygrove (`Route29/connections.inc`: `right → MAP_NEW_BARK_TOWN`, `left → MAP_CHERRYGROVE_CITY`), então o jogador **sempre** passa por lá antes de chegar a Violet. `EventScript_TryDoNormalTrainerBattle` (usado por `trainerbattle_single`) verifica `GetTrainerFlag` e pula a luta se já derrotado; `EventScript_DoNoIntroTrainerBattle` (usado por `trainerbattle_no_intro`) **não verifica** essa flag — então a luta em Violet sempre acontece, mesmo se o jogador já bateu nele na Route29. Não há risco de a luta obrigatória ser pulada.
- O risco real é narrativo/de dados: reaproveitar o ID faz o cameo silencioso da Route29 e o confronto "falado" de Violet serem *mecanicamente* o mesmo treinador com o mesmo time. Se isso não for aceitável, a solução documentada em `adicionar-batalha-npc.md:295-394` é criar um **segundo `TRAINER_*`** (não uma flag nova — um ID novo de uma faixa livre: `280`, `951-963` ou `968-1055`) com o time exclusivo de Violet City, mantendo `TRAINER_GLADION` como está para a Route29.

---

## 5. Derrota, vitória, falta de espaço no time e envio do ovo ao PC

**Derrota:** `trainerbattle_no_intro` sem música/intro não trata blackout de forma especial — segue o padrão documentado em `encenar-evento.md` ("Derrota / blackout / reentrada"): o jogador apaga, é levado ao respawn (`setrespawn HEAL_LOCATION_VIOLET_CITY`, já setado em `VioletCity_Pokecenter_OnTransition`), e como **nenhum `setflag`/`setvar` de progresso pode rodar antes da vitória**, reabordar o Gladion reinicia o fluxo do zero (`Aide_Accepted` do início). Isso já é verdade no script atual — só é preciso manter a ordem "narração → batalha → recompensa" ao inserir a luta.

**Vitória:** segue direto para `giveegg SPECIES_COSMOG`.

**Falta de espaço no time:** aqui o comportamento real do engine é mais permissivo do que o texto atual sugere. `giveegg` chama `ScriptGiveEgg` → `GiveCapturedMonToPlayer` (`src/pokemon.c:2949-2980`):
- Time cheio, mas há espaço numa caixa do PC → `MON_GIVEN_TO_PC` (ovo vai para a caixa, **não** é bloqueado).
- Time cheio **e** todas as caixas do PC cheias → `MON_CANT_GIVE` (único caso que de fato barra a entrega).
- Time com espaço → `MON_GIVEN_TO_PARTY`.

O script atual só testa `VAR_RESULT == MON_CANT_GIVE` (o caso raríssimo de PC 100% cheio) — na prática, "falta de espaço no time" quase sempre resulta em `MON_GIVEN_TO_PC` silencioso, e o jogador só vê a mesma mensagem genérica de "recebeu o Ovo" sem saber que foi para o PC.

**Envio do ovo ao PC:** o padrão correto já existe no projeto, em `data/scripts/day_care.inc:37-44`:
```
call_if_eq VAR_0x8008, MON_GIVEN_TO_PC, Route117_EventScript_DaycareEggSentToPC
...
Route117_EventScript_DaycareEggSentToPC::
	msgbox Route117_Text_EggSentToPC, MSGBOX_DEFAULT
	return
```
Reproduzir esse `call_if_eq VAR_RESULT, MON_GIVEN_TO_PC, ...` no fluxo de Violet deixaria a entrega do Cosmog consistente com a do daycare. Não é obrigatório (o fluxo atual já funciona sem crashar), mas é uma lacuna real do script vigente que valeria corrigir junto.

**Estado reutilizável:** `MON_CANT_GIVE` / `MON_GIVEN_TO_PC` / `MON_GIVEN_TO_PARTY` (`include/constants/pokemon.h:168-170`) — constantes de engine, não flags de jogo.

**Risco de recompensa duplicada:** nenhum, desde que `setflag FLAG_RECEIVED_MYSTERY_EGG` continue depois do `giveegg` bem-sucedido (como já está) — reentrar após esse ponto cai em `Aide_Received`, que não chama `giveegg` de novo.

---

## 6. Estados existentes suficientes para encadear batalha + entrega (sem flag nova)

Demonstração de que os 3 estados já existentes cobrem toda a máquina de estados necessária:

| Estado | Valor/condição | Papel |
|---|---|---|
| `VAR_VIOLET_CITY_STATE` | `== 4` (setado por `ElmCall_Trigger`, item 1) | Único disparador de "Gladion está no PC"; nunca muda durante a interação, então uma derrota não perde esse contexto. |
| `FLAG_RECEIVED_MYSTERY_EGG` | unset | Gate de "ainda não lutei/recebi"; permanece unset se o jogador apagar na luta, permitindo reabordagem idêntica ao padrão Lillie/Route30. Setada só após `giveegg` bem-sucedido. |
| `FLAG_HIDE_VIOLET_CITY_AIDE` / `FLAG_HIDE_NEWBARKTOWN_LAB_AIDE` | alternam junto com os dois acima | Controlam onde o object event do Gladion aparece, sem relação com a lógica da batalha. |

Não há necessidade de uma variável nova tipo "já lutei mas não recebi o ovo": como a batalha fica **dentro** do mesmo script síncrono que dá o ovo (sem `release` entre a luta e o `giveegg`), não existe um estado intermediário para persistir — ou o jogador vence e sai do script já com o ovo, ou apaga e todo o bloco recomeça do zero na próxima interação. Exatamente o mesmo raciocínio já documentado em `encenar-evento.md` para a cena da Lillie.

---

## 7. NPC da Route 32 que bloqueia a passagem

**Arquivo/labels:** `data/maps/Route32/scripts.pory:191-249`, NPC `LOCALID_ROUTE32_BALDINGMAN` (`OBJ_EVENT_GFX_BALDING_MAN`, `data/maps/Route32/map.json`, posição `(26,10)`).

**Comportamento atual:**
```
Route32_EventScript_BaldingManCheck::
	goto_if_unset FLAG_HIDE_SPROUT_TOWER_SILVER, Route32_EventScript_BaldingManTower
	goto_if_unset FLAG_DEFEATED_VIOLET_GYM, Route32_EventScript_BaldingManGym
	goto_if_unset FLAG_RECEIVED_MYSTERY_EGG, Route32_EventScript_BaldingManEgg
	...

Route32_EventScript_BaldingManEgg::
	msgbox Route32_Text_CooltrainerM_WhatsTheHurry, MSGBOX_DEFAULT
	msgbox Route32_Text_CooltrainerM_AideIsWaiting, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Route32_Movement_Turnback
	waitmovement 0
	release
	end
```
Texto (`Route32_Text_CooltrainerM_AideIsWaiting`): *"{PLAYER}, right? Some guy wearing glasses was looking for you. See for yourself. He's waiting for you at the Pokémon Center."*

**Alteração necessária:** só o texto — "some guy wearing glasses" não descreve Gladion. A condição de bloqueio (`goto_if_unset FLAG_RECEIVED_MYSTERY_EGG`) não muda.

**Estado reutilizável:** `FLAG_RECEIVED_MYSTERY_EGG` — mesma flag do item 3/6.

**Risco:** nenhum técnico; risco de inconsistência textual se o texto não for atualizado (jogador é instruído a procurar "um cara de óculos" e encontra Gladion).

---

## 8. Referências posteriores que dizem que o assistente entregou o ovo

| Arquivo/label | Fala | Status/observação |
|---|---|---|
| `NewBarkTown_Lab/scripts.pory:88-98`, `NewBarkTown_Lab_EventScript_ElmAideIsWaiting` / `NewBarkTown_Lab_Text_ElmAideIsWaiting` | *"My aide is still waiting for you In Violet City!"* | **Ativa**, disparada quando `FLAG_HIDE_NEWBARKTOWN_LAB_AIDE` está setada e o jogador fala com Elm antes de ir a Violet. Precisa reescrita para Gladion. |
| `NewBarkTown_Lab/scripts.pory:857-864`, `NewBarkTown_Lab_Text_ElmAideHasEgg` | *"Didn't you meet my assistant? He should have met you with the Egg at Violet City's Pokémon Center..."* | **Órfã — definida mas nunca chamada em nenhum `msgbox`** (confirmado por grep no `.pory` e no `.inc` gerado). Não afeta o jogo hoje; se for reaproveitada para o fluxo do Gladion, precisa ser ligada a algum evento, não só reescrita. |
| `VioletCity/scripts.pory:480-486`, `VioletCity_Text_Kimono_Girl2` | *"Professor Kukui sent the Egg to Professor Elm... And Elm entrusted it to you."* | **Ativa**, dispara depois da entrega (`VAR_VIOLET_CITY_KIMONO_GIRL == 1`). Não menciona "aide" nominalmente, então tecnicamente sobrevive sem edição — mas ganha coerência extra se passar a mencionar Gladion, já que a Gueixa comenta sobre a origem do ovo. |
| `Route32/scripts.pory:303-307`, `Route32_Text_CooltrainerM_AideIsWaiting` | já coberto no item 7 | Ativa, precisa de reescrita. |

Nenhuma outra ocorrência de "aide"/"assistant" ligada a `FLAG_RECEIVED_MYSTERY_EGG` foi encontrada em `data/maps/**/scripts.pory` (busca por `FLAG_RECEIVED_MYSTERY_EGG` cobre as 4 únicas ocorrências no repo, já listadas nos itens 3, 6 e 7).

---

## 9. Object events, sprites, movimentos, mugshots e trainer data para Gladion

**Já existentes no repositório (nenhum asset novo necessário para o básico):**

| Recurso | Arquivo | Status |
|---|---|---|
| ID do treinador | `include/constants/opponents.h:948` — `TRAINER_GLADION 967` | Pronto (reaproveitável ou como base para um 2º ID, ver item 4) |
| Sprite de treinador (tela de batalha) | `include/constants/trainers.h:161` (`TRAINER_PIC_FRONT_GLADION`), `src/data/graphics/trainers.h:13-14,556` | Pronto |
| Gráfico overworld | `include/constants/event_objects.h:340` (`OBJ_EVENT_GFX_GLADION`), `518` (`OBJ_EVENT_PAL_TAG_GLADION`) | Pronto |
| Pic table / anim / graphics info | `src/data/object_events/object_event_pic_tables.h:2110-2119`, `object_event_graphics_info.h:4681`, `object_event_graphics_info_pointers.h:311,673` | Pronto (16x32, `SHADOW_SIZE_M`, animação padrão) |
| Paleta registrada no engine | `src/event_object_movement.c:573` | Pronto |
| Time de batalha | `src/data/trainers.party:19712-19723` | Existe, mas é só **1x Rattata nv.5 IV 0** — precisa de um time novo/maior se a cena exigir (ver item 4) |

**Faltando:**

| Recurso | O que falta | Necessário aqui? |
|---|---|---|
| `MUGSHOT_GLADION` | Não existe em `include/constants/field_mugshots.h`; exigiria também arte nova em `src/data/field_mugshots.h` (`graphics/field_mugshots/gladion.4bpp` + `.gbapal`, seguindo o padrão de `sFieldMugshotGfx_ElmNormal`) | **Opcional** — a cena da Lillie/Kukui em Route30 não usa mugshot para eles (só Oak tem), então dá para fazer a cena inteira com `msgbox` simples, sem mugshot. |
| Movimento customizado | Nenhum `Movement_*` para Gladion existe; se quiser um gesto (ex. erguer o olhar, cruzar os braços) precisa escrever um bloco `walk_*`/`face_*` novo, igual aos de Route30 | Opcional, cosmético |
| `local_id` no object event do PC de Violet | Não declarado hoje | Só necessário se usar `applymovement`/`turnobject` nele |

**Risco:** nenhum bloqueante — a parte gráfica está 100% pronta pelo trabalho já feito em Rift Missions/Route29. O único item que pede trabalho de dados é o time de batalha (e, opcionalmente, mugshot).

---

## 10. Editar só o `.pory` é suficiente?

**Não.** Mapeamento mínimo de arquivos por tipo de mudança:

| Mudança | Arquivo(s) | Gerado automaticamente? |
|---|---|---|
| Diálogos, chamada do Elm, inserção da `trainerbattle_no_intro`, textos novos | `VioletCity/scripts.pory`, `VioletCity_PokemonCenter/scripts.pory`, `NewBarkTown_Lab/scripts.pory`, `Route32/scripts.pory` | Sim — cada `.pory` gera o `.inc` correspondente via poryscript no `make` (regra `data/%.inc: data/%.pory` no `Makefile`) |
| Trocar o sprite do NPC no Pokémon Center de Violet | `data/maps/VioletCity_PokemonCenter/map.json` (`graphics_id`, e `script` se o label mudar de nome) | Sim — `map.json` → `events.inc`/`header.inc` via `tools/mapjson` durante o `make` |
| Time de batalha do Gladion (se for alterado ou duplicado em novo ID) | `src/data/trainers.party` (+ `include/constants/opponents.h` se for ID novo) | Parcial — `trainers.party` gera `src/data/trainers.h` via `tools/trainerproc` no build (`trainer_rules.mk`); `src/data/trainers.h` é **gitignored, nunca editar à mão** |
| Mugshot (se optarem por criar um) | `include/constants/field_mugshots.h` (enum) + `src/data/field_mugshots.h` (tabela) + arte `graphics/field_mugshots/gladion.4bpp`/`.gbapal` | Não — enum e tabela são editados manualmente; a arte precisa ser convertida/importada como qualquer gráfico novo do projeto |

Resumindo: o mínimo viável (reaproveitando o `TRAINER_GLADION` existente, sem mugshot) toca **2 fontes** — os `.pory` das cenas e o `map.json` do Pokémon Center de Violet. Se decidirem por um time exclusivo para essa luta (recomendado, dado o placeholder atual), soma-se `trainers.party` + `opponents.h`. Mugshot é a única adição que sai do fluxo de script puro.
