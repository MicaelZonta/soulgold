# B05 — Laboratório de fósseis (Ruins of Alph): Claw Fossil não revive; fóssil some com party e PC cheios

**Gravidade:** MÉDIA · **Tipo:** menu incompleto + ordem errada na entrega · **Status:** CORRIGIDO em 30/09/2026 (build limpo; falta teste no mGBA)

Arquivo: `data/maps/RuinsOfAlph_Lab/scripts.pory` (o `.inc` é gerado).

## a) Claw Fossil não tem `case`

`RuinsOfAlph_Lab_EventScript_ChooseFossil` (linha 468) só trata Dome, Root,
Plume, Jaw, Sail, Old Amber e Cover. O Claw Fossil cai em "That's not a
fossil". Os scripts `GiveClawFossil`/`AnorithReady` existem (linhas 62-64 e 142)
mas nada chega a eles pelo menu atual.

O único Claw Fossil do jogo vivo é o do Museu de Pewter
(`PewterCity_Museum_1F/scripts.inc:15`). `SPECIES_ANORITH` não aparece em
nenhum outro lugar de `data/` nem em `wild_encounters.json`. Resultado:
**Anorith/Armaldo sem fonte nenhuma no jogo**. O `fontes_legitimas.py` não
acusa porque o site conta o script do laboratório como fonte — o script existe,
só não é alcançável pelo menu.

Correção: `case ITEM_CLAW_FOSSIL, RuinsOfAlph_Lab_EventScript_GiveClawFossil`.
Se Helix/Armor/Skull também devem existir, falta a fonte deles no mundo
(não há nenhum em mapa vivo nem na tabela de Rock Smash de
`src/wild_encounter.c:127-133`).

## b) O fóssil é removido antes do `givemon`

```
RuinsOfAlph_Lab_EventScript_GiveRootFossil::
	...
	removeitem ITEM_ROOT_FOSSIL
	goto RuinsOfAlph_Lab_EventScript_LileepReady      @ -> givemon
...
	goto Common_EventScript_NoMoreRoomForPokemon       @ MON_CANT_GIVE
```

Com party **e** PC cheios, o `givemon` devolve `MON_CANT_GIVE`, o jogador vê
"no more room" e o fóssil já foi consumido. É o padrão da skill
`entregar-pokemon-ou-ovo` (checar espaço antes da oferta). Corrigir junto com
(a): checagem de espaço antes do "Want to bring a fossil back to life?".

## Nota

`VAR_FOSSIL_RESURRECTION_STATE` só recebe 0 e `VAR_WHICH_FOSSIL_REVIVED` nunca
é escrita: os ramos "ainda regenerando" / "está pronto" (linhas 7, 48-49,
125-133) são restos do Emerald e nunca rodam. O fóssil revive na hora. Não é
bug, só código morto — pode sair na mesma limpeza.

## Revisão de todos os fósseis (30/09/2026, depois da correção)

| Fóssil | Onde se consegue | Laboratório aceita | Pokémon |
|---|---|---|---|
| Dome | Rock Smash nas Ruins of Alph | sim | Kabuto (nv 5 antes da 4ª insígnia, 20 depois) |
| Root | Rock Smash nas Ruins + Museu de Pewter | sim | Lileep |
| Claw | Museu de Pewter (1 só) | sim (desde esta correção) | Anorith |
| Plume / Jaw / Sail / Cover | Rock Smash nas Ruins | sim | Archen / Tyrunt / Amaura / Tirtouga |
| Old Amber | Rock Smash nas Ruins + prêmio do Game Corner de Goldenrod | sim | Aerodactyl |
| Helix | **nenhum lugar** | não | Omanyte — **sem fonte nenhuma no jogo** |
| Armor / Skull | nenhum lugar | não | Shieldon / Cranidos saem selvagens no Rock Smash das Ruins |
| Fossilized Bird/Fish/Drake/Dino | nenhum lugar | não | os 4 de Galar saem selvagens (Routes 43, Snowtop, Olivine, Cianwood) |

Rock Smash: `src/wild_encounter.c:120-142`, só em `MAPSEC_RUINS_OF_ALPH`; 30%
de chance de item por pedra, 7 de 11 entradas são fósseis (~2,7% cada fóssil
por pedra). As 8 pedras de `RuinsOfAlph_Outside` usam `FLAG_TEMP_*`, então
voltam a cada visita — dá para farmar. Os fósseis ficam em `POCKET_ITEMS`, o
bolso que o laboratório abre.

Pendente: **Omanyte/Omastar não têm fonte nenhuma** (a lista `sRandomSpecies`
de `src/pokemon.c:7206` que cita Omanyte não é usada). O script do laboratório
para o Helix já existe (`GiveHelixFossil` → `OmanyteReady` → `ReceiveOmanyte`);
falta um `case ITEM_HELIX_FOSSIL` e uma fonte para o item.

## Todos os fósseis no Rock Smash e no laboratório (30/09/2026, pedido do autor)

- `src/wild_encounter.c`: os 15 fósseis na tabela de Rock Smash das Ruins of
  Alph (19 entradas de peso 10: 4 fragmentos + 15 fósseis). Com 30% de chance
  de item por pedra, cada fóssil sai em ~1,6% das pedras quebradas.
- `RuinsOfAlph_Lab/scripts.pory`: o menu aceita os 15. Helix → Omanyte,
  Armor → Shieldon, Skull → Cranidos. Os quatro de Galar pedem a outra metade
  (qualquer ordem): Bird+Drake Dracozolt, Bird+Dino Arctozolt, Fish+Drake
  Dracovish, Fish+Dino Arctovish. Par inválido não consome nada.
- Com isso Omanyte/Omastar deixam de ficar sem fonte.
