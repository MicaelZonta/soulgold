# Professor Kukui

**Região da ficha:** Alola

Aparece no checklist como:

- **Professor Kukui** (Alola · Elite Four e Campeões) — professor que testa o jogador na primeira defesa do título em *Sun/Moon*.

**Pronto para o Nexus:** ✅ sim — tem sprite e battle sprite.

## Checklist

- [x] Sprite de overworld *(obrigatório)*
- [x] Battle sprite / front pic *(obrigatório)*
- [ ] Field mugshot (retrato na caixa de diálogo)
- [ ] Time para as Rift Missions definido
- [ ] Associado a um lendário
- [ ] Diálogo genérico escrito
- [ ] Diálogo associado ao lendário escrito

## Referências no repositório

### Sprite de overworld

| Constante | Arquivo |
|---|---|
| `OBJ_EVENT_GFX_KUKUI` | `graphics/object_events/pics/people/special/kukui.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_KUKUI` | `graphics/trainers/front_pics/kukui.png` |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

> **Atenção:** Personagem do arco das Rift Missions (M3 Cherrygrove, reunião de Olivine, altar).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

| Constante | ID | Flag de batalha | Time em `trainers.party` | Usada em |
|---|---|---|---|---|
| `TRAINER_KUKUI` | 966 | 0x8C6 | Lycanroc Midday Lv78, Braviary Lv78, Ninetales Alola Lv79, Magnezone Lv79, Snorlax Lv79, Incineroar Lv80 | `CherrygroveCity` |

### Time das Rift Missions

_Não definido._ Ponto de partida mais forte já escrito: `TRAINER_KUKUI` (até Lv80).

### Lendário associado

_Nenhum ainda._

### Diálogo genérico

_Não escrito._ (texto do jogo em inglês)

### Diálogo associado ao lendário

_Não escrito._ (texto do jogo em inglês)
