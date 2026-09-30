# Tamanho do overworld de cada personagem

Folhas refeitas em 29/09/2026 com o método híbrido (seam carving nas colunas +
linhas com prioridade). Tamanho = **largura x altura do boneco**. Boneco de 16 px
vai no quadro 16x32 (metade da ROM/VRAM); acima disso, quadro 32x32.

A coluna **Decidido** começa igual à recomendação: edite só o que mudar.
"manter" = não regravar o PNG do jogo. Depois de decidido, cada linha vira:

```bash
$PY dev_scripts/sprites/propostas_overworld.py final <Nome> <largura> <png do jogo> --altura <altura>
```

## Já no jogo

| Personagem | Hoje | Recomendado | Decidido | Nota |
|---|---|---|---|---|
| Anabel | 16 (arte nova) | manter | manter | já aprovado |
| Blue | 18x26 | 16x22 | 16x23 | |
| Brendan | 18 | 16x20 | 17x22  | |
| Bruno | 18 | 20x22 | 16x20 | arte larga, embola a 16/18 |
| Byron | 18 | 18x22 | 18x22 | rosto some a 16 |
| Colress | 18 | 16x22 | 16x22 | |
| Cynthia | 18 | 18x22 | 18x22 | |
| Elesa | 22 (arte antiga) | 16x19 | 16x19 | arte BW aprovada, único tamanho |
| Fantina | 18 | 16x22 | 16x22 | |
| Gladion | 16 antigo | manter | manter | escolha do autor |
| Guzma | 18 | 16x24 | 18x27 | alto |
| Kukui | 16 antigo | manter | manter | escolha do autor |
| Lillie | 16 | manter | manter | aprovada; cena da Missão 4 no limite da VRAM |
| Looker | 16 antigo | manter | manter | escolha do autor |
| Lusamine | 24 | 18x20 | 22x21 | cabelo engole o corpo a 16 |
| Misty | 16 (outra arte) | 16x21 | 16x21 | |
| Ramos | 18x30 | 16x22 | 16x22 | |
| Soliera | 18x26 | 18x22 | 18x22 | armadura perde detalhe a 16 |
| Steven | 18 | 16x22 | 16x22 | |
| Volkner | 18 | 16x22 | 16x22 | |

## Ainda não registrados no jogo

| Personagem | Recomendado | Decidido | Nota |
|---|---|---|---|
| Agatha | 16x21 | 16x21 | |
| Alder | 18x22 | 20 | chibi |
| Ash | 18x22 | 18x22 | chibi |
| Barry | 16x20 | 16x20 | |
| Cheren | 16x22 | 16x22 | arte nova (PurpleZaffre) |
| Cyrus | 16x22 | 16x22 | |
| Diantha | 18x22 | 18x22 | chibi |
| Gardenia | 16x21 | 16x21 | |
| Hau | 16x24 | 16x24 | |
| Hilda | 18x20 | 18x20 | boné come o rosto a 16 |
| Jessie | 16x18 | 16x18 | |
| James | 16x19 | 16x19 | |
| Leon | 16x23 | 16x23 | |
| Lorelei | 16x22 | 16x22 | |
| N | 16x18 | 16x18 | único tamanho; rosto escuro, vale arte nova |
| Olivia | 16x20 | 16x20 | arte nova (folha ampliada por IA, 30/09) |
| Shelly | 16x19 | 16x19 | |
| Zinnia | 18x22 | 18x22 | chibi |
