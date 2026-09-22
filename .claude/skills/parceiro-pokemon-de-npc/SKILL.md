---
name: parceiro-pokemon-de-npc
description: Use quando um NPC de historia aparece com o proprio Pokemon fora da Poke Ball andando ao lado dele (Lillie + Vulpix/Ninetales, Gladion + Type Null) - objeto OBJ_EVENT_GFX_SPECIES no map.json, flag de ocultacao compartilhada, movimento pareado e saida juntos. Cobre por que waitmovement 0 deixa o parceiro sem espera, a ordem certa de removeobject e onde conferir se a especie tem sprite de overworld. Nao use para o follower do jogador.
---

# Pokémon parceiro de NPC, fora da Poké Ball

Exemplos reais, todos em produção:

| Cena | Dono | Parceiro | Flag compartilhada |
|---|---|---|---|
| `Route30_MrPokemonsHouse` | Lillie | Vulpix Alola | `FLAG_DELIVERED_EGG` |
| `GoldenrodCity_FlowerShop` | Lillie | Vulpix Alola | `FLAG_RECEIVED_SQUIRTBOTTLE` |
| `DragonsDen_Shrine` | Lillie | Ninetales Alola | `FLAG_TEMP_1` (ver `visibilidade-e-gatilhos` §6) |
| `CianwoodCity` | Gladion | Type: Null | `FLAG_HIDE_CIANWOOD_GLADION` |

Não existe sistema de "follower de NPC". São dois object events comuns,
movidos em par pelo script.

## 1. O objeto: nenhum asset novo

`OW_POKEMON_OBJECT_EVENTS` está `TRUE` (`include/config/overworld.h:52`),
então qualquer espécie com sprite de overworld entra direto no `map.json`:

```json
{
  "local_id": "LOCALID_ROUTE30_VULPIX",
  "graphics_id": "OBJ_EVENT_GFX_SPECIES(VULPIX_ALOLA)",
  "x": 4, "y": 6, "elevation": 0,
  "movement_type": "MOVEMENT_TYPE_FACE_RIGHT",
  "movement_range_x": 0, "movement_range_y": 0,
  "trainer_type": "TRAINER_TYPE_NONE",
  "trainer_sight_or_berry_tree_id": "0",
  "script": "NULL",
  "flag": "FLAG_DELIVERED_EGG"
}
```

- Antes de usar, confira que a espécie tem bloco `OVERWORLD(` em
  `src/data/pokemon/species_info/gen_*_families.h`. Formas regionais têm o
  próprio bloco (`sPicTable_NinetalesAlola`). A skill `adicionar-npc` **não**
  se aplica aqui.
- **Mesma flag do dono.** Os dois somem juntos quando a flag é setada, e o
  `removeobject` de cada um seta essa mesma flag. Nada de flag nova.
- **Sempre no fim de `object_events`.** Inserir no meio renumera os
  `local_id` posicionais seguintes (ver `adicionar-npc`: mapa sem `local_id`).
- `local_id` nomeado → adicione a linha em `include/constants/map_event_ids.h`
  à mão (ver `batalha-sem-blackout`).

## 2. Mover em par: `waitmovement <ID>` para cada um

`waitmovement 0` espera **só o último objeto que recebeu `applymovement`**:
`ScrCmd_applymovement` grava `sMovingNpcId = localId` (`src/scrcmd.c:1337`),
e `WaitForMovementFinish` checa apenas esse ID (`:1343`).

Com dois `applymovement` seguidos de um `waitmovement 0`, o script segue
assim que o segundo termina. O primeiro pode ainda estar andando quando vem
o `removeobject` ou a próxima fala.

```
	applymovement LOCALID_ROUTE30_VULPIX, MrPokemonHouse_Movement_VulpixLeave
	applymovement LOCALID_ROUTE30_LILLIE, MrPokemonHouse_Movement_LillieLeave
	waitmovement LOCALID_ROUTE30_VULPIX
	waitmovement LOCALID_ROUTE30_LILLIE
	playse SE_EXIT
	removeobject LOCALID_ROUTE30_VULPIX
	removeobject LOCALID_ROUTE30_LILLIE
```

## 3. Formação: o parceiro anda um passo atrás

Dois padrões usados nas cenas acima:

- **Dono sai primeiro:** o parceiro começa com `delay_16` (a duração de um
  passo) e depois repete o caminho, ou já entra no tile que o dono acabou de
  deixar. Exemplo: `GoldenrodCity_FlowerShop_Movement_VulpixApproach`.
- **Parceiro sai na frente pela porta:** o parceiro termina no tile da porta
  e o dono para no tile imediatamente atrás. Os dois são removidos juntos.
  Exemplo: `MrPokemonHouse_Movement_VulpixLeave`.

Escreva a planta como comentário `@` acima de cada movimento, com o caminho
completo em coordenadas: `@ Vulpix: (5,6) -> (5,7) -> door (5,8).`

Rode `dump_mapa.py` (skill `encenar-cutscene`) para conferir **cada** tile
dos dois caminhos. Os dois caminhos são diferentes: no Shrine a coluna do
Ninetales é bloqueada em (8,15), e ele precisa entrar na coluna da Lillie
logo no primeiro passo.

## 4. Depois da batalha os dois estão onde a cena os deixou

`trainerbattle` não recarrega o mapa. O caminho de saída do par parte das
posições **finais da aproximação**, não do `map.json`. Se o dono se
aproximou do jogador, recalcule a saída dos dois a partir dali.

## Checklist

- [ ] A espécie tem bloco `OVERWORLD(` (inclusive a forma regional certa)
- [ ] Objeto no **fim** de `object_events`, `script: NULL`, mesma flag do dono
- [ ] `map_event_ids.h` atualizado se o objeto tem `local_id`
- [ ] Todo par de `applymovement` usa `waitmovement <ID>` para **cada** objeto
- [ ] `removeobject` dos dois; nenhum dos dois fica sozinho no mapa
- [ ] Todo tile dos dois caminhos conferido no `dump_mapa.py`
- [ ] Saída calculada a partir das posições depois da aproximação
- [ ] Reentrei no mapa depois do evento e nenhum dos dois reapareceu
