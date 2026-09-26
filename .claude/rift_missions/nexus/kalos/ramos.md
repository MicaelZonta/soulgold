# Ramos

**Região da ficha:** Kalos

Aparece no checklist como:

- **Ramos — Grama** (Kalos · Líderes de Ginásio) — jardineiro veterano e Líder de Coumarine.

**Pronto para o Nexus:** ❌ não — falta sprite de overworld e battle sprite (os dois são obrigatórios).

## Checklist

- [ ] Sprite de overworld *(obrigatório)*
- [ ] Battle sprite / front pic *(obrigatório)*
- [ ] Field mugshot (retrato na caixa de diálogo)
- [ ] Time para as Rift Missions definido
- [ ] Associado a um lendário
- [ ] Diálogo genérico escrito
- [ ] Diálogo associado ao lendário escrito

## Referências no repositório

### Sprite de overworld

Não existe. Criar com a skill `adicionar-npc`.

### Battle sprite (front pic)

Não existe. Criar com a skill `adicionar-grafico-trainer`.

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

Nenhuma. Ao criar, seguir a skill `adicionar-batalha-npc` (e `alocar-flag` se precisar de flag nova).

### Time das Rift Missions

📝 **Proposta de 26/09/2026, aguardando o autor.** `TRAINER_NEXUS_RAMOS` em [`ULTRA_BEASTS.party`](../ULTRA_BEASTS.party): Xerneas · Celebi · Mega Victreebel + Gogoat, Jumpluff, Ferrothorn. Segue R10–R13; plano de jogo em [`ULTRA_BEASTS.md`](../ULTRA_BEASTS.md) §3.6.

### Lendário associado

📝 **Proposta de 26/09/2026:** campeão da **Kartana** (UB-04 Blade) no Nexus. Por quê: [`ULTRA_BEASTS.md`](../ULTRA_BEASTS.md) §3.6.

### Diálogo genérico

_Não escrito._ (texto do jogo em inglês)

### Diálogo associado ao lendário

📝 **Proposta de 26/09/2026:** `Nexus_Text_Blade_Intro`, `_Defeat` e `_After` (mais `_Arrival`, `_Boss` e a `_LookerFile` do fragmento) em [`ULTRA_BEASTS_TEXTS.inc`](../ULTRA_BEASTS_TEXTS.inc); leitura corrida em [`ULTRA_BEASTS.md`](../ULTRA_BEASTS.md) §3.6.
