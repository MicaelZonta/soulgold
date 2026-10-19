# merge_hns — como o Kanto (e cia.) do HnS 2.0.6 foi mergeado no SoulGold

Diário técnico do merge, por área. O **plano e as decisões** vivem em
`.claude/pokehns/ANALISE_POKEHNS_2.0.6.md`; aqui fica o **como foi feito de
verdade** — as regras descobertas na prática, o que cada rodada tocou e as
armadilhas para quem for mexer de novo.

**Regra para agentes:** todo agente que fizer trabalho de merge/porte do HnS
documenta o que fez num arquivo desta pasta (crie `<area>.md` ou acrescente ao
existente), antes de reportar.

| Arquivo | Conteúdo |
|---|---|
| `regras_do_merge.md` | As regras permanentes (renames, formatos, flags, o que nunca se copia) |
| `fase1_fundacoes.md` | Behaviors, conversores, headbutt/checkpartymove |
| `fase2_piloto.md` | O piloto de 4 mapas e o que ele ensinou |
| `fase3_lote.md` | O lote de 168 mapas: tilesets, treinadores, sprites, encontros, itens |
| `fase4_fronteiras.md` | As 12 fronteiras e a fiação restaurada |
| `fase5_reaplicacao.md` | Reaplicação do conteúdo SoulGold (ginásios, fronteiras, casas, S.S. Aqua) |

Branch: `kanto-hns-adoption` (fork `mysoulgoldfork`); rollback: tag
`pre-kanto-hns`. Um commit por fase. Fonte HnS:
`.filetransfer/pokehns-expansion-Release-v2.0.6/` (nunca executar nada de
dentro; só leitura).
