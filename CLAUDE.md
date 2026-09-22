# SoulGold — orientações para agentes

Romhack de Pokémon sobre pokeemerald-expansion. Instruções em português;
**todo texto que aparece no jogo é em inglês**.

## Build

Existem **dois** builds:

```bash
make -j$(nproc)                            # testar / iterar — use este no dia a dia
make release USE_LTO_ON_RELEASE=1 -j32     # release
```

Ambos geram `Soulgold.gba`. O build regenera sozinho tudo que é derivado
(`mapjson`, `poryscript`, learnsets). Um build limpo prova só que compila —
**não** prova que a cena funciona no jogo.

## Carregue a skill certa antes de mexer

| Vou fazer | Skill |
|---|---|
| Movimento de NPC, `applymovement`, `turnobject`, coreografia de cena | `encenar-cutscene` |
| NPC aparecer/sumir por progresso; gatilho automático de mapa | `visibilidade-e-gatilhos` |
| NPC novo com sprite próprio (ou NPC invisível) | `adicionar-npc` |
| Front pic / back pic / field mugshot | `adicionar-grafico-trainer` |
| Tileset novo ou portado; mapa com desenho deslocado | `adicionar-tileset` |
| Criar a arte/paletas de um tileset por código; peças do primário em outra cor; troca dia/noite | `montar-tileset` |
| Protótipo de mapa (map.bin gerado, renders, NPCs) e a página de proposta | `prototipo-de-mapa` |
| Bordas, árvores, montanha; revisar mapa; aprender com retoque do autor no Porymap | `acabamento-de-mapa` |
| Treinador batalhável (ID, time, raio de visão) | `adicionar-batalha-npc` |
| Batalha que continua mesmo se o jogador perder | `batalha-sem-blackout` |
| NPC com o próprio Pokémon fora da Poké Ball ao lado dele | `parceiro-pokemon-de-npc` |
| Script que entrega Pokémon ou ovo (`givemon`, `giveegg`) | `entregar-pokemon-ou-ovo` |
| Evento em modo esqueleto (Rift Missions) e seu doc de implementação | `evento-esqueleto` |

Todas cobrem armadilhas que **não dão erro de build** — compilam limpo e
quebram no jogo: NPC invisível, NPC olhando pro lado errado, NPC
reaparecendo sozinho, vitória disparando evento de outro mapa, ou o jogo
congelando ao entrar na cidade.

Cada skill aponta para o guia longo correspondente em `.claude/`, com o
passo a passo completo e exemplo real. Esses `.md` **não** são carregados
sozinhos — abra sob demanda.

## Onde editar script de mapa

```bash
ls data/maps/<Mapa>/scripts.pory 2>/dev/null
```

Existe `.pory` → edite só o `.pory` (o `.inc` é gerado e sua edição some).
Não existe → edite o `.inc` direto; é o caso da maioria dos mapas.

`events.inc`, `header.inc` e `connections.inc` são **sempre** gerados a
partir do `map.json` — nunca edite à mão.

## Regra de ouro

As coordenadas do `map.json` e a colisão do `map.bin` são a fonte de
verdade. Medir, nunca supor — inclusive a direção do olhar, que depende
de `y` crescer **para baixo**.
