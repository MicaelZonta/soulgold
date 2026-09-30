# Berry Master — índice

| Arquivo | O que é | Status |
|---|---|---|
| [`REI_DA_COLHEITA.md`](REI_DA_COLHEITA.md) | **O design que vale**: horta, Livro, cruzamento, níveis, pedidos, infestações, rotina, falas, batalhas, a sidequest e as dungeons dos corcéis (rev1–rev4, §1–§15) | aprovado; em implementação (ver o plano) |
| [`PLANO_DE_IMPLEMENTACAO.md`](PLANO_DE_IMPLEMENTACAO.md) | Ordem de trabalho em 17 partes numeradas, cada uma jogável sozinha; o feedback de cada parte feita fica dentro dela | Partes 1–6 no código (30/09); 2–6 esperam o teste no jogo |
| [`BERRY_MASTER_DESIGN.md`](BERRY_MASTER_DESIGN.md) | Primeira proposta da horta (rev1); auditoria do motor e das coordenadas | superado em parte pelo `REI_DA_COLHEITA.md` |
| [`LENDARIO_E_INFESTACAO.md`](LENDARIO_E_INFESTACAO.md) | Análise: lendários sem fonte e onde cada inseto aparece hoje | superado em parte pelo `REI_DA_COLHEITA.md` |
| `cenas/` | Renders das cenas dos atos e da rotina (usados na página “O Rei da Colheita”) | — |
| `prototipo_corceis/` | Protótipo dos 4 mapas das dungeons (`gera.py`, `map.bin`, objetos, renders) — ver `REI_DA_COLHEITA.md` §15.5c | aprovado 30/09/2026 |
| `horta_*.png` | Renders da Route 30 com a horta | — |

**Testar no jogo:** menu de debug **L + START → Berry Master…** (relógio, Livro, nível,
canteiros, teleporte, reset). **Roteiro completo, em ordem: [`TESTES_NO_JOGO.md`](TESTES_NO_JOGO.md)**
(40 testes, T01–T40). Resumo por parte: `PLANO_DE_IMPLEMENTACAO.md`, seção “Como testar”.

Páginas (artifacts), só apresentação — tudo o que dizem está nos `.md`:

- [Horta do Berry Master](https://claude.ai/artifact/L7mDjKKS2aq63SUgY323nD) — o sistema.
- [O Rei da Colheita](https://claude.ai/artifact/DkvvWE7XYtx3C6SJyJZCcm) — a história.
- [Caminhos dos Corcéis](https://claude.ai/artifact/R65MTm61Y7NGT8doiocyRY) — o protótipo dos mapas.
