# Fase 5 — Reaplicação do conteúdo SoulGold

## Ginásios (agente)
- A camada S real era pequena: `special Achievement_CheckAll` após cada
  badge (reaplicado nos 8; o do Blaine é SeafoamIslands_Gym). Rematches em
  texto, Suicune da Cerulean, latas do Surge: o HnS já cobria.
- Mantidos os TMs reais do HnS (Blue=Trick Room, Blaine=Overheat, Erika=
  Giga Drain, Sabrina=Skill Swap, Surge=Shock Wave, Brock=Rock Slide,
  Janine=Poison Jab) — os do S eram texto sem entrega.
- HnS realoca líderes derrotados p/ fora (Janine→ReceptionGate,
  Sabrina→porto de Olivine; flags existem nesses mapas S).

## Fronteiras (agente)
- Route27: expert reaplicado (12 treinadores pré-requisito → Choice Band;
  realocado (52,26)→(41,23), a posição antiga virou rocha) + Ability Patch
  (149,21). Route26: Rare Candy escondido. Route26North: Choice Scarf,
  Ultra Ball escondida, 2 luzes noturnas. Route28: Max Revive escondido.
  TohjoFalls: bola virou megastone Normalite (mesma flag da Heart Scale).
- Conflitos de item bola-a-bola: ficou o conteúdo HnS (anotado).

## Casas/lojas (agente caiu no rate limit; terminado pelo orquestrador)
- O agente interrompido estava APAGANDO base HnS (Super Rod da Route 12,
  Moon Stone do Mt. Moon, mart do Celadon) — revertido via git checkout.
  Regra nova em regras_do_merge.md: a base HnS fica; camada S por cima.
- Sobreviventes íntegros mantidos: Pallet (Exeggcute de fundo + OnLoad
  setrespawn), Viridian (fisher dá TM Sludge Bomb com checkitemspace +
  OnLoad), Bill's House (avô com pedidos S+HnS encadeados 1–12, Teleporter
  preservado).
- Celadon Dept 4F: clerk religado ao script do Goldenrod Dept do S (stub do
  Lilycove removido). 5F/Lavender/Route5/MtMoon/Route12: idênticos ao HnS,
  nada a reaplicar.
- S.S. Aqua 1F: só `clearflag FLAG_HIDE_MTSILVER_RIVAL` no desembarque
  (revela o rival). O flagheap antigo do S NÃO volta (respawnaria bosses a
  cada viagem no barco multi-viagem) — respawn é design da Fase 7.

## Pendências desta fase
- Plaquinhas {SPEAKER} + decap dos textos HnS (K8) — passe próprio.
- Itens divergentes bola-a-bola (Route 27) se o autor quiser os do S.
- Cameron/GS Ball do S vivem em Route20/Route28/HOF (patches) — avaliar na
  Fase 7/histórias.
