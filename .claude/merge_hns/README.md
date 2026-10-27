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
| `fase6_radio.md`, `fase6_roamers.md`, `fase6_mom_surf_fanfarras.md` | Fase 6: rádio de 12 estações, roamers, poupança da mãe, surf e fanfarras |
| `fase7_trio_leal.md`, `fase7_bosses_e_casas.md` | Fase 7: Trio Leal, lendários em Boss Fight, casas novas, Café enxuto |
| `fase8_alola_sinjoh.md` | Fase 8: Alola, New Sinjoh/Sinjoh Ruins, Snowswept Cavern |
| `summit_red_rival.md` | Red × rival no topo do Mt. Silver (ovo de Terapagos) |
| `match_call_gsc.md` | O telefone do Pokégear: agenda, ligações, revanches, itens e o custo de save |
| `bug_alola_trava.md` | **Resolvido** (24/10): Melemele Isle travava ao entrar — porta de Alola fora de `sDoorAnimGraphicsTable`, `gfx->size` em NULL virava `udf` |
| `ssaqua_ida_e_volta.md` | S.S. Aqua nos dois sentidos e a retirada do flagheap que apagava progresso de Kanto no desembarque |
| `k8_plaquinhas_e_decap.md` | K8: decap do texto HnS (`dev_scripts/decap_texto.py`) e plaquinhas `{SPEAKER}` |
| `navel_rock_e_birth_island.md` | As duas ilhas que entraram na ROM: Deoxys, Volcanion, a agenda de NPC e a armadilha do `.inc` gerado |
| `kanto_no_site.md` | A lista que escondia Kanto inteiro do site de docs, e a suíte de testes que estava vermelha desde o import |

Branch: `kanto-hns-adoption` (fork `mysoulgoldfork`); rollback: tag
`pre-kanto-hns`. Um commit por fase. Fonte HnS:
`.filetransfer/pokehns-expansion-Release-v2.0.6/` (nunca executar nada de
dentro; só leitura).
