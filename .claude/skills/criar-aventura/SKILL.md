---
name: criar-aventura
description: Use ao criar uma AVENTURA nova (regiao, ilha, arco de historia com varios mapas) do zero ate a pagina de proposta - quantos mapas, como amarrar lore oficial, atos e cenas, missoes secundarias, personagens do Nexus sem mapa, desenhar mapas so com tilesets existentes, verificar alcance/quebra-cabecas por simulacao, dividir o trabalho em frentes paralelas e publicar o Artifact. Tambem use quando o autor pedir "mais mapas", "mais eventos/lore", "deixar top tier", ou reclamar que um mapa gerado ficou feio/chapado/clipando. Receita tirada da Abundance Isle (30/10/2026, 35 mapas, aprovada pelo autor).
---

# Criar uma aventura

Caso real: **Abundance Isle** (30/10/2026). Pedido: "uma ilha que resolva as storylines de
Zekrom, Kyurem, Tornadus, Thundurus, Landorus e Enamorus, com N e Ghetsis". Virou 35 mapas,
6 ilhas, 21 cenas, 16 missões. Artifact: `https://claude.ai/artifact/G3mY3cP6pfrz1rwntS52c1`.
Ferramentas e exemplos em `ferramentas/` (veja a tabela no fim).

## O que o autor espera (aprendido na conversa)

| Ele disse | Significa |
|---|---|
| "uns 2- mapas" → "são 20 mapas" | **Escala de aventura**: 20–35 mapas, não 2–3. Na dúvida sobre número, pergunte antes de desenhar |
| "é para ser uma aventura" | Região com rotas, cavernas, torre, navio, interiores e pós-jogo; não uma ilha solta |
| "interessantes, coisas divertidas de explorar, temático" | Todo mapa precisa de segredo, item escondido, atalho ou quebra-cabeça **e** fazer sentido com a lore |
| "pode buscar lore na internet" | Pesquisar (Bulbapedia) e **citar a fonte** na página; amarrar cada lendário à lore oficial |
| "caso desenhe, 4 propostas" | Todo desenho que não existe em tileset: 4 propostas, isoladas e já no mapa |
| "começa pelo Artifact" | Desenho e proposta primeiro; implementar só quando ele aprovar |
| "pode usar treinadores do Nexus" | Personagens com sprite e sem mapa viram elenco (veja abaixo) |
| "fica livre para upgrades no mGBA" | Liberdade para subir limites se a beleza pedir (skill `limites-do-engine`) |

## Ordem de trabalho

1. **Ler o que já existe** dos lendários: `.claude/rift_missions/nexus/POOL_LENDARIOS.md`,
   `.claude/evolucoes.md` (fonte legítima de cada espécie/forma) e as fichas em `nexus/<regiao>/`.
   A aventura deve dar **fonte de verdade** a quem só vem de Nexus/Café/Gachapon.
2. **Pesquisar a lore** (WebSearch, 2–4 buscas em paralelo) e achar o gancho de cada um. Exemplos
   que funcionaram: Forças da Natureza = Fūjin/Raijin/Inari (raposa, torii, colheita); Landorus só
   desce com os dois presentes; Enamorus "Arauto da Primavera" chega pelo mar quando o inverno acaba;
   Kyurem no meteorito de gelo (Lacunosa: "não saia à noite"); Pedra Escura/Light Stone;
   Lenora entrega a Light Stone no BW.
3. **Uma premissa que amarra tudo** (a da Abundance: Ghetsis rouba o frio do meteorito → inverno
   eterno → tempestades → raios acordam a Pedra Escura). Cada lendário = consequência da premissa.
4. **Atos e cenas** (tabela: gatilho, onde, o que acontece, batalha, o que muda). Estado da história
   numa **var única** (`VAR_<REGIAO>_STATE`), não em dezenas de flags.
5. **Lore própria**: 3–4 lendas contadas por personagens diferentes, com textos do jogo em inglês
   (placas, estelas em fragmentos, murais, quadro de avisos que muda por ato, carta).
6. **Missões secundárias** que obrigam a visitar vários mapas (fragmentos em 4 mapas, sementes em 6,
   velas em 2 andares...). Cada uma revela um pedaço de lore.
7. **Lista de mapas** com tileset sugerido e ligações (SPEC — exemplo em `ferramentas/SPEC_exemplo_abundance.md`).
8. **Desenhar** (frentes paralelas, abaixo), **verificar**, **publicar a página**.
9. **Perguntar** o que é do autor: proposta de cada desenho, sprites que não existem, acesso à região.

## Mapas que deixaram a aventura "top tier"

Depois dos 30, perguntei o que faltava e ele aprovou os quatro:
- **Andar de quebra-cabeça** na torre (para-raios em ordem: estados simulados, sem beco sem saída).
- **Momento pessoal** do personagem guia (quarto do N, homenagem ao do castelo).
- **Segredo submarino** (Dive) com naufrágio e mural.
- **Arena pós-jogo** com rodízio diário do elenco e a dupla final aos sábados.

## Elenco do Nexus

Personagens com `OBJ_EVENT_GFX_*` e **zero uso** em `data/maps/*/map.json` — o script que achou 40
está na conversa da Abundance; refaça com `grep` nas fichas `nexus/*/*.md` × `map.json`. Distribua pelo
tema (Winona no vento, Volkner/Elesa nos raios, Lorelei no gelo, Byron no meteorito, Zinnia na lore
do meteoro, Lenora na estela, Rosa infiltrada no navio, Tate e Liza nos gêmeos).
Sprites que não existem (Ghetsis, recrutas do Plasma) ficam com placeholder **e anotados**.

## Frentes paralelas (forks)

- Escreva o SPEC (regras, tabela de mapas, quem faz, warps entre frentes) **antes** de lançar.
- 4 frentes por região (fazenda/bosque, costa, caverna, torre/navio) rendeu bem; reaproveite a
  mesma frente para mapas vizinhos depois (ela já conhece o lugar) via SendMessage.
- Diga explicitamente "NÃO mexa no repositório" quando houver instalação em andamento.
- No fim, rode a **checagem de pares de warp** (todo warp aponta para um warp que volta) e acerte os
  `dest_warp_id` "?" das fronteiras entre frentes. Quedas de mão única são exceção anotada.

## Verificar (nunca entregar sem)

- `check_objects`: nenhum NPC em bloqueio/água.
- BFS da entrada até cada item, warp e ponto de história (`slide_reach` em `kit_aventura.py`).
- Quebra-cabeça de gelo: **simular sobre o map.bin final** (no primeiro gerador o simulador "fugia"
  por um atalho que não estava fechado; a solução certa só apareceu simulando o mapa real).
- Portões por script (`setmetatile`): **o estado da busca é (posição do jogador, portões)**, não só os
  portões. Calcular o alcance sempre a partir da entrada dá resposta falsa: no 3F ela pedia 10 toques e
  "corrigi" a dica do mural; no jogo o jogador fica preso do lado do portão que fechou, e a solução real
  era a da dica original (4 toques). `ferramentas/simular_portoes.py`.
- **Treinador não pode ficar em corredor de 1–2 casas**: vencido, ele não sai do lugar (e quem anda até o jogador
  para no meio do caminho) e prende o jogador. Achado no QA de 31/10/2026 (Lab da cratera e Thunderspire 2F).
  `ferramentas/treinador_tranca.py <Mapa...>` acusa o treinador que, como bloqueio, corta o caminho de alguma entrada.
- Placa/item/NPC novo só em célula alcançável a partir dos warps (`ferramentas/alcance.py`); piso de
  elevação 4 cercado nas torres é decoração e não se alcança.
- Espiral/labirinto: BFS mostra o caminho e o número de passos (o cume deu 78).
- **Olhar o render** de todo mapa. O autor reprova mapa chapado na hora.

## Página (Artifact)

`ferramentas/pagina_aventura.py` gera a página a partir de `m20/<Mapa>/info.json` + imagens:
região costurada pelas conexões, diagrama SVG de ligações (clicável), atos, lendas, cenas,
missões, eventos de mundo, tabela de lendários (hoje → na aventura), um cartão por mapa com
botões dia/estado/depois/colisão, elenco do Nexus, desenhos (4 propostas cada), pendências, fontes.
Publique com `publish_files` (página + `img/`), republique no **mesmo slug**.

## Ferramentas

| Arquivo | Para quê |
|---|---|
| `kit_aventura.py` | `Grid`, `stamp`, `nine` (9-slice), `put`, `plateau` (montanha Johto em níveis), `cave_wall` + `learn_walls` (paredes por assinatura de vizinhança), `slide_reach` (BFS com gelo) |
| `ruina_kit.py` | salas de ruína de deserto com a regra da RegirockChamber |
| `desenho.py` | pixel art por código (`Tela`) e `reduzir` (≤15 cores = 1 paleta) |
| `instalar_arte.py` | clona um secundário e encaixa um desenho nos tiles/índices de paleta livres |
| `exemplo_ilha_deserto.py` | Emberdune v2: ilha em dois níveis, paredão, bordas de água aprendidas |
| `exemplo_caverna_gelo.py` | caverna de gelo com quebra-cabeça gerado e verificado |
| `exemplo_cume_espiral.py` | cume da Spear Pillar alargado com espiral de colunas |
| `pagina_aventura.py` | gerador da página |

Regras de acabamento por tileset (deserto, gelo, ruínas, montanha, carimbo de prédio): skill
`acabamento-de-mapa`, seção "Aprendido na Abundance Isle".
