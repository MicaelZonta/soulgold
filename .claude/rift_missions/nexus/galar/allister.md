# Allister

**Região da ficha:** Galar

Aparece no checklist como:

- **Allister — Fantasma** (Galar · Líderes de Ginásio) — Líder exclusivo de *Shield*, tímido e sempre mascarado.

**Pronto para o Nexus:** ✅ sim — tem sprite e battle sprite (03/10/2026). Falta o time e as falas irem para o código.

## Checklist

- [x] Sprite de overworld *(obrigatório)* — `OBJ_EVENT_GFX_ALISTER`, 03/10/2026
- [x] Battle sprite / front pic *(obrigatório)* — `TRAINER_PIC_FRONT_ALLISTER` (64x64 + 80x80), 03/10/2026
- [ ] Field mugshot (retrato na caixa de diálogo)
- [ ] Time para as Rift Missions definido
- [ ] Associado a um lendário
- [ ] Diálogo genérico escrito
- [ ] Diálogo associado ao lendário escrito

## Referências no repositório

### Sprite de overworld

| Constante | Arquivo |
|---|---|
| `OBJ_EVENT_GFX_ALISTER` | `graphics/object_events/pics/people/special/alister.png` (boneco 16x22, quadro 16x32, 12 quadros, `sAnimTable_StandardAsym`; paleta própria `OBJ_EVENT_PAL_TAG_ALISTER`) — registrado em 03/10/2026, visto no jogo de frente |

Origem: `.filetransfer/.trainers/Alister/Sprite - DiegoWT.png` (tamanho escolhido pelo autor; ver `TAMANHOS.md`).

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_ALLISTER` | `graphics/trainers/front_pics/allister.png` (64x64) + `allister_large.png` (80x80, `TRAINER_SPRITE_LARGE`) — 03/10/2026; nenhuma batalha usa ainda |

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
