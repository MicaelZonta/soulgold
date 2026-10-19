# Patches de preservação — conteúdo SoulGold em Kanto (Fase 0)

Gerados em 19/10/2026 no branch `kanto-hns-adoption` (tag do estado anterior:
`pre-kanto-hns`).

Cada `<Mapa>.diff` é o resultado de:

```bash
git diff a57644df9a..HEAD -- data/maps/<Mapa>/
```

onde `a57644df9a` é o commit-base comum com o Heart & Soul ("Ported all the
johto maps to pokeemerald-expansion", 13/11/2025) e `HEAD` é
`1ebed1705b` (merge upstream v1.2). O escopo (197 mapas) está em
`../KANTO_ESCOPO.txt`; `MANIFEST.txt` lista cada patch por tamanho (linhas de
diff, decrescente).

## Para que servem

Na **Fase 5** do roadmap (`../ANALISE_POKEHNS_2.0.6.md`, K9), depois que os
mapas forem sobrescritos pelo Kanto do HnS, estes diffs são a referência do
que o SoulGold tinha feito em cada mapa — para reaplicar **seletivamente**
(Liga/HOF, Rift Missions, Mewtwo boss, rival, ginásios, BP rewards), não na
íntegra: boa parte é decap/plaquinha em massa que será refeita de outro jeito
(ver K8).

- Patches grandes = conteúdo real (ver topo do MANIFEST: FightingDojoVIP,
  Route27, IndigoPlateau_PokemonCenter, TohjoFalls_GiovanniRoom,
  CeruleanCave_B2F, MtSilver_*, PokemonLeague_*).
- Patches pequenos = quase sempre só decap/plaquinha/species — conferir antes
  de descartar.
- Os 2 mapas TitleDefense da Liga são exclusivos do S, fora do escopo: não
  serão sobrescritos e não têm patch aqui.

**Não aplicar com `git apply` por cima do Kanto novo** — os mapas do HnS têm
outra base; usar os diffs como leitura/guia de reimplementação.
