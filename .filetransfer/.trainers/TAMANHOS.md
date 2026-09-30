# Tamanho do overworld de cada personagem

Folhas refeitas em 29/09/2026 com o método híbrido (seam carving nas colunas +
linhas com prioridade). Tamanho = **largura x altura do boneco**. Boneco de 16 px
vai no quadro 16x32 (metade da ROM/VRAM); acima disso, quadro 32x32.

A coluna **Decidido** começa igual à recomendação: edite só o que mudar.
"manter" = não regravar o PNG do jogo. Depois de decidido, cada linha vira:

```bash
$PY dev_scripts/sprites/propostas_overworld.py final <Nome> <largura> <png do jogo> --altura <altura>
```

**Escolha em negrito = forma pronta (30/09/2026).** Não regravar, não retratar,
não rodar `propostas` de novo para estes personagens, a não ser que o autor
peça explicitamente: mudanças no método de redução já causaram regressão em
sprites aprovados. Se o script mudar, os PNGs do jogo destes ficam como estão.

## Já no jogo

| Personagem | Hoje | Recomendado | Decidido | Nota |
|---|---|---|---|---|
| Anabel | 16 (arte nova) | manter | **17x22** | já aprovado; escolhido 30/09: forma pronta |
| Blue | 18x26 | 16x22 | **17x25** | escolhido 30/09: forma pronta |
| Brendan | 18 | 16x20 | **16x20** | escolhido 30/09: forma pronta |
| Bruno | 18 | 20x22 | **20x22** | arte larga, embola a 16/18; escolhido 30/09: forma pronta |
| Byron | 18 | 18x22 | **16x21** | escolhido 30/09: forma pronta |
| Colress | 18 | 16x22 | **16x22** | escolhido 30/09: forma pronta |
| Cynthia | 18 | 18x22 | **16x20** | método de 29/09 (simples); escolhido 30/09: forma pronta |
| Elesa | 22 (arte antiga) | 16x19 | **16x19** | arte BW aprovada, único tamanho; escolhido 30/09: forma pronta |
| Fantina | 18 | 16x22 | **16x22 (quadro 16x32)** | escolhido 30/09: forma pronta |
| Gladion | 16 antigo | manter | **16x19** | método de 29/09 (simples); escolhido 30/09: forma pronta |
| Guzma | 18 | 16x24 | **17x22** | escolhido 30/09: forma pronta |
| Kukui | 16 antigo | manter | **16x24** | escolha do autor; escolhido 30/09: forma pronta |
| Lillie | 16 | manter | **16x19** | aprovada; cena da Missão 4 no limite da VRAM; escolhido 30/09: forma pronta |
| Looker | 16 antigo | manter | **manter** | o do jogo (07/09) é o perfeito: nunca regravar; escolhido 30/09: forma pronta |
| Lusamine | 24 | 18x20 | **22x21** | cabelo engole o corpo a 16; escolhido 30/09: forma pronta |
| Misty | 16 (outra arte) | 16x21 | **17x23** | escolhido 30/09: forma pronta |
| Ramos | 18x30 | 16x22 | **18x22** | escolhido 30/09: forma pronta |
| Soliera | 18x26 | 18x22 | **16x22** | armadura perde detalhe a 16; escolhido 30/09: forma pronta |
| Steven | 18 | 16x22 | **16x22** | escolhido 30/09: forma pronta |
| Volkner | 18 | 16x22 | **16x22** | escolhido 30/09: forma pronta |

## Ainda não registrados no jogo

| Personagem | Recomendado | Decidido | Nota |
|---|---|---|---|
| Agatha | 16x21 | **17x23** | arte nova (image.png ampliada por IA); escolhido 30/09: forma pronta |
| Alder | 18x22 | **16x20** | chibi; escolhido 30/09: forma pronta |
| Barry | 16x20 | **17x21** | escolhido 30/09: forma pronta |
| Cheren | 16x22 | **16x22** | arte nova (PurpleZaffre); escolhido 30/09: forma pronta |
| Cyrus | 16x22 | **17x22** | escolhido 30/09: forma pronta |
| Diantha | 18x22 | **16x20** | chibi; escolhido 30/09: forma pronta |
| Gardenia | 16x21 | **16x21** | escolhido 30/09: forma pronta |
| Hau | 16x24 | **16x24** | escolhido 30/09: forma pronta |
| Hilda | 18x20 | **20x22** | escolhido 30/09: forma pronta |
| Jessie | 16x18 | **16x18** | escolhido 30/09: forma pronta |
| James | 16x19 | **16x19** | escolhido 30/09: forma pronta |
| Leon | 16x23 | **16x23** | escolhido 30/09: forma pronta |
| Lorelei | 16x22 | **18x22** | escolhido 30/09: forma pronta |
| N | 16x18 | **16x18** | único tamanho; rosto escuro, vale arte nova; escolhido 30/09: forma pronta |
| Olivia | 16x20 | **16x20** | arte nova (folha ampliada por IA, 30/09); escolhido 30/09: forma pronta |
| Shelly | 16x19 | **16x19** | escolhido 30/09: forma pronta |
| Zinnia | 18x22 | **16x20** | chibi; escolhido 30/09: forma pronta |
