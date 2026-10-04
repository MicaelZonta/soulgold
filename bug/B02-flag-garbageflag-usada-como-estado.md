# B02 — `FLAG_GARBAGEFLAG` virou estado compartilhado de três features

**Gravidade:** ALTA (perde feature para sempre no save) · **Probabilidade:** certa após o gatilho
**Tipo:** flag reaproveitada · **Status:** CORRIGIDO em 30/09/2026 (build limpo; falta teste no mGBA)

## Sintoma

- A Daisy (Pallet Town, casa 2) só faz o grooming **uma vez na vida do save**.
  Depois diz "already groomed" para sempre.
- Ela também para de fazer grooming, sem nunca ter feito, se o jogador:
  vencer a Blaine; ou perder a batalha contra o Tentacruel nível 100 da
  Route 41; ou perder uma das batalhas do Lickilicky no Fighting Dojo.
- A estátua do ginásio de Saffron diz que o jogador venceu Sabrina depois de
  qualquer um dos eventos acima, mesmo sem ter vencido.

## Onde

`flags.h:119` — `#define FLAG_GARBAGEFLAG 0x53 //used to store calls of removed flags`.
Numa limpeza antiga, flags distintas foram removidas e as chamadas apontadas
para esta. Hoje ela é **lida** como estado em três lugares vivos:

| Leitura | Significado pretendido |
|---|---|
| `PalletTown_House2/scripts.inc:8` `goto_if_unset` → grooming | "Daisy ainda não fez grooming" |
| `SeafoamIslands_Gym/scripts.inc:46` `goto_if_set` → estátua pós-vitória | "Blaine vencida" |
| `SaffronCity_Gym/scripts.inc:169` `goto_if_set` → estátua pós-vitória | "Sabrina vencida" |

E **escrita** em cinco:

| Escrita | Efeito |
|---|---|
| `PalletTown_House2/scripts.inc:54` `setflag` após o grooming | permanente |
| `SeafoamIslands_Gym/scripts.inc:19` `setflag` ao vencer Blaine | permanente |
| `Route41/scripts.pory:203/208` set antes / clear depois do `dowildbattle` | fica setada se o jogador **perder** (blackout não roda o `clearflag`) |
| `SaffronCity_FightingDojo/scripts.inc:47/51, 75/79, 103/107, 131/135, 159/163, 187/191` | idem, 6 pares |

(Nenhum objeto de mapa vivo usa `FLAG_GARBAGEFLAG` no campo `flag`, então
ninguém some — o estrago é só nessas leituras.)

Observação: `B_FLAG_NO_CATCHING`, setada junto no Route 41 e no Dojo, **é**
limpa no blackout (`Overworld_ResetBattleFlagsAndVars`,
`B_RESET_FLAGS_VARS_AFTER_WHITEOUT TRUE`). Só a `FLAG_GARBAGEFLAG` fica.

## Correção sugerida

1. Estátuas: ler a flag real — `FLAG_DEFEATED_CINNABAR_ISLAND_GYM` em Seafoam
   (a própria Blaine já seta, linha 20) e `FLAG_DEFEATED_SAFFRON_CITY_GYM` em
   Saffron. Apagar o `setflag FLAG_GARBAGEFLAG` de Seafoam:19.
2. Daisy: flag própria. Se a intenção é "uma vez por dia" (como no FRLG), usar
   uma flag do bloco diário — há 17 `FLAG_UNUSED_0x94F..` livres ali (auditoria
   de flags §8.4); se for "uma vez só", flag nova em `CUSTOM_FLAGS`. Skill
   `alocar-flag`. Decisão de design do autor.
3. Route 41 e Dojo: apagar os `setflag/clearflag FLAG_GARBAGEFLAG` — não servem
   a nada vivo.
4. Rodar `catalogar-flags` no fim.

Save antigo: quem já está com a flag setada continua sem Daisy até a
correção; depois dela, volta a funcionar sozinho (a flag nova nasce zerada).

## Correção aplicada (30/09/2026)

- Daisy: `FLAG_DAILY_DAISY_GROOMED` (`DAILY_FLAGS_START + 0x34`, antes
  `FLAG_UNUSED_0x954`) — **uma vez por dia**, como sugere a fala "I always have
  tea around this time". 0x952/0x953 ficaram de fora porque o design do Berry
  Master os reserva.
- Estátuas: `FLAG_DEFEATED_CINNABAR_ISLAND_GYM` e `FLAG_DEFEATED_SAFFRON_GYM`.
- Removidos os `setflag/clearflag FLAG_GARBAGEFLAG` de Seafoam, Route 41 e Dojo.
