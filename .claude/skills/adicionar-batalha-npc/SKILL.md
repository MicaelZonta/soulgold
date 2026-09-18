---
name: adicionar-batalha-npc
description: Use ao criar um treinador batalhavel - escolher TRAINER_ID em opponents.h, escrever o time em src/data/trainers.party, ligar trainer_type no map.json e chamar trainerbattle_* no script. Use tambem ao diagnosticar treinador que nunca avista, batalha que repete, mon vindo nivel 100, ou vitoria que dispara evento de outro mapa. Se a batalha precisa continuar mesmo se o jogador perder, use antes a skill batalha-sem-blackout.
---

# Montar uma batalha de NPC

Passo a passo com exemplo real (Youngster Joey):
**[`.claude/adicionar-batalha-npc.md`](../../adicionar-batalha-npc.md)**.

Se a cena tem que **continuar mesmo se o jogador perder** (batalha de
história, sem blackout), este não é o guia — use a skill
`batalha-sem-blackout`.

## A armadilha: escolher o ID é escolher uma flag

Você **não cria flag** para um treinador — a de "derrotado" é derivada do
ID (`TRAINER_FLAGS_START (0x500) + ID`). Por isso **nem todo
`TRAINER_UNUSED_*` serve**: neste projeto parte dessa faixa teve as flags
reaproveitadas como flags normais de história.

Usar um ID tomado faz o treinador **compartilhar flag com um evento de
mapa**: vencer o treinador dispara o evento, ou o treinador nasce "já
derrotado". Sintoma bizarro e difícil de rastrear.

**Não confie em faixa anotada — ela envelhece.** Rode:

```bash
python3 .claude/skills/adicionar-batalha-npc/ids_livres.py
```

Ele cruza `opponents.h` + `trainers.party` + `flags.h` e lista o que está
livre **hoje**, já excluindo os IDs cuja flag virou flag de história e os
que passam de `MAX_TRAINERS_COUNT`.

Duas regras que não mudam:

| Faixa | Status |
|---|---|
| `1056-1163` | ❌ flags `0x920-0x98B` viraram `FLAG_SNOWTOP_*`, `FLAG_VAJRAPYRAMID*`, `FLAG_LATITEMPLE_*`… |
| `1164` e acima | ❌ fora do range (`MAX_TRAINERS_COUNT`) |

Antes de fechar num ID, confirme que ele não é citado em outro lugar:

```bash
grep -rn "\bTRAINER_UNUSED_XXX\b" data/ src/ include/ | grep -v opponents.h
```

Renomeie o `TRAINER_UNUSED_*` daquele ID, **mantendo o número**.

## Os 5 lugares

| # | Arquivo |
|---|---------|
| 1 | `include/constants/opponents.h` — `TRAINER_<NOME>` com ID da faixa livre |
| 2 | `src/data/trainers.party` — bloco `=== TRAINER_<NOME> ===` |
| 3 | `data/maps/<Mapa>/map.json` — `trainer_type` + raio de visão + `script` |
| 4 | script do mapa — `trainerbattle_single` |
| 5 | mesmo script — os 3 textos: **Seen / Beaten / After** |

> ⚠️ **Nada de `lock`/`faceplayer` antes do `trainerbattle`.** A engine já
> cuida da aproximação e do "!". Um `lock` antes **trava a cena**.

## Armadilhas

| Sintoma | Causa |
|---|---|
| Mon nível 100 com IV 31 | Faltou `Level:`/`IVs:` no `.party` — são os padrões |
| Golpes "errados" | Nenhum golpe escrito → set automático de level-up. Escreva os 4 (`- None` para vazio) |
| trainerproc reclamando de linha estranha | Falta **linha em branco** entre cabeçalho e mon, ou entre mons |
| `undefined reference to TRAINER_X` | Bloco no `.party` sem `#define` em `opponents.h`, ou vice-versa |
| **Vitória dispara evento de outro mapa** | ID na faixa `1056-1163` — colisão de flag |
| Treinador nasce derrotado / volta batalhável sozinho | Mesma colisão de flag, sentido inverso |
| Nunca te avista | `trainer_type` em `TRAINER_TYPE_NONE`, raio `"0"`, ou `movement_type` virado pro outro lado |
| Cena trava ao ser avistado | `lock`/`faceplayer` antes do `trainerbattle_*` |
| Batalha repete infinitamente | Script não usa `trainerbattle_*`, ou sobrou um `cleartrainerflag` |
| Editou `src/data/trainers.h` e sumiu | É **gerado** e gitignored — a fonte é `trainers.party` |
| Texto pós-batalha nunca aparece | Ele só roda ao **falar** com o treinador já derrotado — correto |
| Treinador invisível | É sprite, não batalha → skill `adicionar-npc` |

## Checklist

- [ ] ID saiu do `ids_livres.py` (não de faixa decorada) e não é citado fora do `opponents.h`
- [ ] `#define` em `opponents.h` **e** bloco em `trainers.party`
- [ ] Todo mon tem `Level:`, `IVs:` e os 4 golpes explícitos
- [ ] Linha em branco entre cabeçalho e mons
- [ ] `trainer_type` e raio de visão setados no `map.json`
- [ ] Sem `lock`/`faceplayer` antes do `trainerbattle`
- [ ] Os 3 textos (Seen/Beaten/After) existem
