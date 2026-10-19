# Topo do Mt. Silver — Red + rival em revezamento semanal

Decisão do autor (19/10/2026): o Red aparece DEPOIS do rival, e dali em
diante os dois se revezam por dia da semana. Implementado em
`data/maps/MtSilver_SummitDay/scripts.pory` (o .inc é gerado).

## Fluxo
1. **Primeira subida**: só o rival (cena autoral intacta: mugshots, batalha
   GOLD/CRYSTAL_FINAL por gênero, ovo, corrida pra casa com warp pra New
   Bark). O Red fica escondido pelo ON_TRANSITION enquanto
   `FLAG_DEFEATED_MTSILVER_RIVAL` não estiver setada (o LeaveBoat do
   S.S. Aqua limpa `FLAG_HIDE_MTSILVER_RED`, então re-escondemos).
2. **Depois da vitória**, ON_TRANSITION decide por `VAR_DAY_OF_WEEK`
   (0 = domingo, como no NPC de domingo do Goldenrod Dept):
   - **Red**: domingo (0), quarta (3), sábado (6) — `cleartrainerflag
     TRAINER_RED` a cada entrada (rebatalhável).
   - **Rival**: segunda, terça, quinta, sexta — `cleartrainerflag` dos dois
     FINAL (rebatalhável); script pós-game próprio (fala nova, cita "o
     quieto do Pikachu… a gente se reveza").

## Ovo (skill entregar-pokemon-ou-ovo aplicada)
- Espécie trocada: **SPECIES_JIRACHI → SPECIES_TERAPAGOS** (decisão Parte D;
  1ª fonte de Terapagos do jogo; Jirachi fica com a pedra do Mt. Moon).
- Era o "pior caso" documentado na skill (anunciava antes de entregar e o
  doador sumia). Agora: checagem party+PC ANTES da cena
  (`RivalNoRoom`, retomável), guarda `MON_CANT_GIVE` depois do giveegg →
  `FLAG_RIVAL_SUMMIT_EGG_PENDING` (0x111E): o rival segura o ovo e entrega
  nos dias de rival, com nova checagem de espaço.

## Red
- `TRAINER_RED` (851) ganhou time: o do HnS (Pikachu-Starter Lv93 com Light
  Ball, Snorlax 77, Charizard/Venusaur/Blastoise 79, Espeon 80; Music Hg
  Champion). `TRAINER_RED_POSTOBC` (do lote F3) fica para quando o pós-OBC
  de Sinjoh existir (Fase 8).
- Objeto novo no map.json: OBJ_EVENT_GFX_RED em (10,6),
  `FLAG_HIDE_MTSILVER_RED`, `LOCALID_MTSILVER_RED`.
- Fala minimalista clássica ("……"), `FLAG_DEFEATED_RED` na 1ª vitória.

## QA sugerido
- Dia de rival × dia de Red (mudar relógio/fake RTC), rebatalha no mesmo
  dia, ovo com party cheia + PC cheio (pendência → entrega depois),
  SummitNight (layout) herda os objetos do SummitDay.
