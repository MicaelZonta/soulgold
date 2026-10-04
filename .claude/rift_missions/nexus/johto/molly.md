# Molly Hale

**Região da ficha:** Johto

Aparece no checklist como:

- **Molly Hale** (Johto · Outros notáveis) — filha do Professor Hale, de Greenfield; adulta no hack, mora na Mansão Hale com o Entei de lembrança.

**Pronto para o Nexus:** ✅ sim — tem sprite e battle sprite (03/10/2026). Falta o time e as falas irem para o código.

## Checklist

- [x] Sprite de overworld *(obrigatório)* — `OBJ_EVENT_GFX_MOLLY_HALE`, 03/10/2026
- [x] Battle sprite / front pic *(obrigatório)* — `TRAINER_PIC_FRONT_MOLLY_HALE` (64x64 + 80x80), 03/10/2026
- [ ] Field mugshot (retrato na caixa de diálogo)
- [ ] Time para as Rift Missions definido
- [ ] Associado a um lendário
- [ ] Diálogo genérico escrito
- [ ] Diálogo associado ao lendário escrito

## Referências no repositório

### Sprite de overworld

| Constante | Arquivo |
|---|---|
| `OBJ_EVENT_GFX_MOLLY_HALE` | `graphics/object_events/pics/people/special/molly_hale.png` (boneco 17x20, quadro 32x32, 9 quadros, `sAnimTable_Standard`; paleta própria `OBJ_EVENT_PAL_TAG_MOLLY_HALE`) — registrado em 03/10/2026, visto no jogo de frente |

Origem: `.filetransfer/.trainers/Molly adulta/Sprite - AI.png` (tamanho escolhido pelo autor; ver `TAMANHOS.md`). Usado na `Greenfield_Mansion` (Molly do saguão e do salão) no lugar do provisório `WOMAN_2`.

A Molly criança (`.filetransfer/.trainers/Molly crianca/`, base da Lillie) é outra arte e não está registrada.

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_MOLLY_HALE` | `graphics/trainers/front_pics/molly_hale.png` (64x64) + `molly_hale_large.png` (80x80, `TRAINER_SPRITE_LARGE`) — 03/10/2026; nenhuma batalha usa ainda |

### Field mugshot

Não existe. Opcional.

### Plaquinha

`SP_NAME_MOLLY` já existe (`include/constants/speaker_names.h`), usada nas falas
da `Greenfield_Mansion`.

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

Nenhuma. Ao criar, seguir a skill `adicionar-batalha-npc` (e `alocar-flag` se precisar de flag nova).

### Time das Rift Missions

_Não definido._

### Lendário associado

_Nenhum ainda._ (Entei é a ligação natural da personagem, mas depende de aprovação
do autor e do [`POOL_LENDARIOS.md`](../POOL_LENDARIOS.md).)

### Diálogo genérico

_Não escrito._ (texto do jogo em inglês)

### Diálogo associado ao lendário

_Não escrito._ (texto do jogo em inglês)
