# Nemona

**Região da ficha:** Paldea (Kitakami e Blueberry)

Aparece no checklist como:

- **Nemona** (Paldea (Kitakami e Blueberry) · Rivais e companheiros) — Campeã extremamente entusiasmada por batalhas e principal rival do jogador.
- **Nemona — nível Campeão** (Paldea (Kitakami e Blueberry) · Elite Four e Campeões) — já possui o título antes de iniciar uma nova jornada ao lado do jogador.

**Pronto para o Nexus:** ✅ sim — tem sprite e battle sprite (03/10/2026). Falta o time e as falas irem para o código.

## Checklist

- [x] Sprite de overworld *(obrigatório)* — `OBJ_EVENT_GFX_NEMONA`, 03/10/2026
- [x] Battle sprite / front pic *(obrigatório)* — `TRAINER_PIC_FRONT_NEMONA` (64x64 + 80x80), 03/10/2026
- [ ] Field mugshot (retrato na caixa de diálogo)
- [ ] Time para as Rift Missions definido
- [ ] Associado a um lendário
- [ ] Diálogo genérico escrito
- [ ] Diálogo associado ao lendário escrito

## Referências no repositório

### Sprite de overworld

| Constante | Arquivo |
|---|---|
| `OBJ_EVENT_GFX_NEMONA` | `graphics/object_events/pics/people/special/nemona.png` (boneco 20x22, quadro 32x32, 12 quadros, `sAnimTable_StandardAsym`; paleta própria `OBJ_EVENT_PAL_TAG_NEMONA`) — registrado em 03/10/2026, visto no jogo de frente |

Origem: `.filetransfer/.trainers/Nemona/Sprite - DiegoWT.png` (tamanho escolhido pelo autor; ver `TAMANHOS.md`).

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_NEMONA` | `graphics/trainers/front_pics/nemona.png` (64x64) + `nemona_large.png` (80x80, `TRAINER_SPRITE_LARGE`) — 03/10/2026; nenhuma batalha usa ainda |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

Nenhuma. Ao criar, seguir a skill `adicionar-batalha-npc` (e `alocar-flag` se precisar de flag nova).

### Time das Rift Missions

_Não definido._

### Lendário associado

_Nenhum ainda._

### Diálogo genérico

_Não escrito._ (texto do jogo em inglês)

### Diálogo associado ao lendário

_Não escrito._ (texto do jogo em inglês)
