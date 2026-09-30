# SoulGold — Rift Missions

**Design vigente · 26/09/2026.** Este arquivo descreve **como o arco é hoje**:
o que está no código, as regras que valem para tudo que ainda for escrito e o que
falta. Não guarda histórico de revisões — a versão anterior, com os registros
V13 a V27, está no git (`git log -- .claude/rift_missions/SOULGOLD_RIFT_MISSIONS_DESIGN.md`).

**Onde está cada coisa:**

| Assunto | Documento |
| --- | --- |
| Cena de cada evento (falas, encenação) | `<EVENTO>/<EVENTO>_SCRIPT_V2.md` — o roteiro do autor |
| Como a cena foi implementada, arquivos, flags, riscos | `<EVENTO>/<EVENTO>_IMPLEMENTATION.md` (a seção mais recente vence o resto do arquivo) |
| Planejamento narrativo de Blackthorn ao Altar, vozes | [`SOULGOLD_RIFT_ARCO_NARRATIVO.md`](SOULGOLD_RIFT_ARCO_NARRATIVO.md) |
| Loop pós-Necrozma (Nexus) | [`nexus/NEXUS_REGRAS.md`](nexus/NEXUS_REGRAS.md) — vence este arquivo no que tratar |
| Poké Balls do Kurt / Beast Ball | [`../KURT_BALL_CRAFT_DESIGN.md`](../KURT_BALL_CRAFT_DESIGN.md) |
| Catálogo de flags | `docs/SOULGOLD_FLAGS_AUDIT.csv` e `.claude/SOULGOLD_FLAGS_AUDIT.md` |

Precedência: numa cena, o roteiro V2 aplicado e a última seção do doc de
implementação valem sobre este arquivo; nas regras do arco, vale este arquivo.

---

## 1. Estado atual

| Evento | Estado | Runtime | Documento |
| --- | --- | --- | --- |
| Encontros pré-Liga (Lillie ×3, Gladion ×3, Kukui/Oak) | Implementados, todos os duelos sem blackout | Reações à família Cosmog validadas pelo autor (22/09); o resto sem teste registrado | §4 |
| Ligação do Looker + escritório de Olivine | Implementado; convocação diária para os estados 4/6/8/10 | Pendente | §5 |
| **M1 — Blackthorn** (Buzzwole + Pheromosa, Gladion, Clair) | Roteiro V2 aplicado (25/09) | Pendente (a cena mudou desde o teste de 22/09) | [`BLACKTHORN_ULTRABEAST/`](BLACKTHORN_ULTRABEAST/BLACKTHORN_ULTRABEAST_IMPLEMENTATION.md) §15–§16 |
| **M2 — Mahogany** (Xurkitree + Celesteela, Lillie, Pryce) | Roteiro V3 aplicado (25/09), rua alargada, parede de gelo em metatile | Pendente | [`MAHOGANY_ULTRABEAST/`](MAHOGANY_ULTRABEAST/MAHOGANY_ULTRABEAST_IMPLEMENTATION.md) §16 |
| **M3 — Cherrygrove** (Blacephalon + Stakataka, Kukui) | Roteiro V2 aplicado (26/09), banco de areia no mapa | Pendente | [`CHERRYGROVE_ULTRABEAST/`](CHERRYGROVE_ULTRABEAST/CHERRYGROVE_ULTRABEAST_IMPLEMENTATION.md) §15 |
| **M4 — New Bark** (Kartana + Guzzlord + Nihilego, Lusamine) | Roteiro V2 aplicado (26/09): três frentes, campo de contenção da Aether, Ultra Necrozma instável; cerca e barricada em metatile | Pendente | [`NEWBARK_ULTRABEAST/`](NEWBARK_ULTRABEAST/NEWBARK_ULTRABEAST_IMPLEMENTATION.md) |
| **PRÉ-NECROZMA** — reunião em Olivine | Roteiro V2 aplicado (26/09): teste do parceiro em cena, passe idempotente, chá no pós-game | Pendente | [`PRE_NECROZMA_ULTRABEAST/`](PRE_NECROZMA_ULTRABEAST/PRE_NECROZMA_ULTRABEAST_IMPLEMENTATION.md) |
| **ALTAR DO SOL E DA LUA** — Lusamine, Ultra Necrozma, resgate das nove, despedida | Roteiro V2 aplicado (26/09, rev. 7): duelo, acordo e teste da passagem, resgate das nove na tela, captura em Beast Ball, custódia, estabilização | Pendente para o V2 (a rev. 4, V1, foi testada pelo autor); tela branca na fenda diária em aberto | [`ALTAR_SUN_MOON/`](ALTAR_SUN_MOON/ALTAR_SUN_MOON_IMPLEMENTATION.md) §21 |
| Loop pós-Necrozma (Nexus) | **Esqueleto implementado** (27/09): modo Daily completo no mapa `Nexus` — 4 salas × 3 portas, campeão, boss capturável, prêmio, Poipole; 10 treinadores, 10 UBs no pool | Pendente | [`nexus/NEXUS_IMPLEMENTATION.md`](nexus/NEXUS_IMPLEMENTATION.md) |

---

## 2. O arco

Personagens de Alola cruzam a campanha de Johto em paralelo; a primeira ruptura
explícita só acontece depois da Liga.

**Pré-Liga:** Route 30 (Lillie) → Violet (Gladion, Mystery Egg) → Goldenrod
(Lillie, SquirtBottle) → Cianwood (Gladion, Fly) → Dragon's Den (Lillie) →
antes da Victory Road (Gladion + Silvally) → Liga. Nenhuma Ultra Beast.

**Pós-E4:** Hall of Fame → ligação do Looker ao sair de casa → escritório de
Olivine → **M1 Blackthorn** → ligação → Olivine → **M2 Mahogany** → ligação →
Olivine → **M3 Cherrygrove** → ligação → Olivine → **M4 New Bark** → ligação →
**reunião de Olivine** (exige Solgaleo **ou** Lunala na equipe) → navio →
**Altar do Sol e da Lua** (Lusamine, Ultra Necrozma, despedida) → **Nexus**.

**O fio.** Em toda missão o Necrozma abre a ruptura por onde as Ultra Beasts
chegam e, depois da vitória do jogador, as **absorve**. Cada missão tenta algo
novo contra isso e aprende um limite:

| Missão | O que o grupo tenta | O que aprende |
| --- | --- | --- |
| M1 | Conter a UB derrotada com uma Ball policial | Uma ligação com a fenda repele a Ball |
| M2 | Cortar a ligação (parede de gelo da Lillie + Pryce) | Dá para interromper um trajeto; o Necrozma cria outro por cima. As assinaturas das UBs **persistem** depois da absorção |
| M3 | Agir **antes** do arrasto (pausa registrada em Mahogany) | Chegar a tempo não basta enquanto a ligação existe; é preciso cortá-la antes de capturar. Fica uma **direção** da abertura |
| M4 | Cortar as ligações com o campo de contenção da Aether e capturar com as UBs dentro dele | O campo funciona até o Necrozma aumentar o fluxo; ele absorve as três e assume a forma Ultra — potente e **instável**, recua. Nove assinaturas persistem; o objetivo passa a ser conter a **fonte** |
| Altar | Atravessar com o parceiro do Mystery Egg e derrotar Ultra Necrozma | Captura roteirizada; a fenda fica, e vira o Nexus |

**A surpresa guardada para o altar:** a criatura coleta as Ultra Beasts porque
**está com fome** — a luz é comida. Nenhuma fala anterior ao altar usa essa
palavra.

---

## 3. Elenco e vozes

Continuação híbrida de Sun/Moon e Ultra Sun/Ultra Moon, posterior a Alola. As
escolhas deste hack vencem as fontes; anime, mangá e Masters não são
continuidade. Falas no jogo em inglês. Amostras de voz e pesquisa estão em
[`SOULGOLD_RIFT_ARCO_NARRATIVO.md`](SOULGOLD_RIFT_ARCO_NARRATIVO.md).

| Personagem | Papel | Voz |
| --- | --- | --- |
| **Looker** | Polícia Internacional; mora em `OlivineCity_House1` com a Anabel desde o New Game. Está em todas as missões; conduz relatórios, acessos e pessoas; **não batalha** | Cortês, caloroso, um pouco teatral fora de perigo; direto na emergência. Pergunta pelas pessoas antes do relatório. Humor discreto só fora da crise |
| **Anabel** | Chefe da investigação. Coordena proteção, preparo e retirada; lê o instrumento | Calma, precisa, separa o que mediu do que sente. Aceita apoio sem perder autoridade |
| **Kukui** | Pesquisador de golpes em visita a Johto; M3 e reunião; no pós-game, revanche na praia | Entusiasmado, informal ("cousin"), concreto; transforma observação em instrução útil. Treinador competente desde a primeira cena — sem "civil que era um mestre secreto" |
| **Lillie** (+ Vulpix → Ninetales Alola) | Três encontros pré-Liga; M2; reunião; pós-game | Educada e firme. **Observa e duvida; nunca prevê.** Relata o que anotou, diz onde não viu, corrige o plano sem se depreciar |
| **Gladion** (+ Type: Null → Silvally) | Três duelos pré-Liga; M1 (chega de surpresa, nomeia o Necrozma, dá ao jogador **outro** Type: Null) | Frases curtas; cuidado mostrado em ação; reconhecimento relutante e sincero |
| **Lusamine** | M4, reunião, duelo narrativo no altar. Sprite de overworld **32×32 de DiegoWT** (12 quadros, direita própria; doc da M4 §6.2) | Formal, habituada a decidir; a reparação aparece quando pergunta e escuta. Sem fusão com Nihilego |
| **Líder local** | Clair (M1), Pryce (M2); Cherrygrove não tem Ginásio | A autoridade local agiu antes de o jogador chegar |

**Anabel é Faller**, sabe disso desde antes de Johto e tem lacunas de memória.
A única percepção especial do arco é dela: **sente uma abertura próxima
segundos antes do instrumento**. Alcance local, antecedência breve, com
incerteza — não localiza cidades, não prevê o que vem, não conta criaturas.
Quem mede e entra no relatório é o instrumento. Progressão:

| Momento | Conteúdo |
| --- | --- |
| M1, M2 | Atenção a quem é deslocado; em Mahogany ela percebe a ruptura antes do instrumento, sem explicar |
| **M3, no rescaldo** | Depois de tirar o jogador de uma abertura e **só com a praia segura**, ela conta: veio por uma Ultra Wormhole, lembra pouco de antes, sente aberturas próximas um instante antes. Looker não fala por ela |
| M4 | Nada novo sobre a condição. Ela sente as aberturas **quando já está perto** ("They're opening"), sem discurso. Não localiza New Bark de Olivine |
| Reunião / altar | A condição é **argumento** para exigir plano de volta, não notícia |
| Pós-Necrozma | Fica no altar para ajudar quem chegar pelas fendas |

**Parceiros visíveis.** Silvally ao lado do Gladion e Ninetales ao lado da
Lillie em toda aparição narrativa, fora da Poké Ball. Isso é presença
permanente; um Pokémon solto no meio da cena (o Incineroar do Kukui, o parceiro
do jogador) é encenação e sai antes do fim.

**O Cosmog do jogador não é o Nebby.** A Lillie lembra do Nebby; ninguém chama o
Pokémon do jogador por esse nome. O Gladion não sabia o que havia no ovo.

---

## 4. Campanha pré-Liga

Todos implementados. Todo duelo de personagem segue a **política de duelo
narrativo**: batalha obrigatória (sem menu de recusa), `B_FLAG_NO_WHITEOUT`
salvo e restaurado, resultado copiado logo depois da batalha, fala própria para
vitória/derrota/empate/desistência, cura, e **os ramos convergem** para a mesma
entrega. O progresso é o estado real do evento, nunca a flag de treinador
vencido. Presente com checagem de espaço **antes** da luta.

| Encontro | Onde | Entrega / conclusão | Estado persistente |
| --- | --- | --- | --- |
| Lillie + Vulpix Lv7 | Casa da Route 30, com Kukui e Oak | Mystery Egg (para o Elm) e Pokédex | cena de Oak/Kukui |
| Gladion + Type: Null | Centro de Violet (no lugar do assistente) | Mystery Egg de **Cosmog** | `FLAG_RECEIVED_TOGEPI_EGG` renomeada |
| Lillie + Vulpix | Floricultura de Goldenrod, após Whitney | SquirtBottle; saem pela porta | `FLAG_RECEIVED_SQUIRTBOTTLE` |
| Gladion + Type: Null | Cianwood, após Chuck | Fly (a esposa de Chuck passa a HM ao Gladion) | controle original de Fly |
| Lillie + Ninetales | Dragon's Den, durante o quiz | 15 reações às respostas vanilla (9 aceitas avançam, 6 rejeitadas repetem, `FLAG_TEMP_2..7`); batalha de 6 (`TRAINER_LILLIE_DRAGONS_DEN`) | `VAR_BLACKTHORN_CITY_STATE` |
| Gladion + Silvally | `ReceptionGate`, antes da Victory Road | Primeira aparição do Silvally; não é gate | estado da cena |
| Elm e a família Cosmog | Laboratório | Eviolite uma vez, com Cosmog/Cosmoem/Solgaleo/Lunala na equipe | `FLAG_SHOWN_ELM_TOGEPI` renomeada |

**Reações à família Cosmog (validadas pelo autor).** Goldenrod, Cianwood,
Dragon's Den e Victory Road têm uma fala opcional se houver Cosmog, Cosmoem,
Solgaleo ou Lunala (não ovo) na equipe: special `CheckMysteryEggPokemon`, sem
flag e sem var, o parceiro do NPC reage primeiro. Sem a família, a cena corre
igual.

**Batalhas de ameaça são outra coisa:** Ultra Beasts, Ultra Necrozma e bosses
capturáveis dão blackout e exigem nova tentativa; nunca tornam um Pokémon único
indisponível para sempre.

---

## 5. Pós-E4: o sistema das missões

### 5.1 Escritório e convocação

- `OlivineCity_House1`: Looker (4,5) e Anabel (7,5), presentes desde o New Game
  (o NPC do Voltorb Hisuiano foi para `OlivineCity_House3` (7,4)). Estar em
  Olivine e na missão ao mesmo tempo é aceito: a missão é cutscene. No estado 16
  os dois se mudam para o altar.
- **A ligação é a convocação.** Fechar uma missão não abre o briefing seguinte;
  a casa só oferece uma fala de espera até o Looker telefonar
  (`ShouldDoRiftMissionCall`, `src/field_control_avatar.c` →
  `RiftMissions_EventScript_LookerCall`, `data/scripts/rift_missions.inc`).
  Condições: estado em {4, 6, 8, 10}; `FLAG_DAILY_LOOKER_CALL` limpa (uma por
  **dia do calendário** do jogo); `FLAG_RIFT_LOOKER_SUMMONS` limpa (convite
  emitido persiste entre dias e saves e não se repete); nenhuma pendência
  (`FLAG_BLACKTHORN_TYPE_NULL_PENDING`); fora da própria casa. O estado 2
  (Blackthorn) usa a cena de ligação em New Bark e não entra nessa regra.
- **Fim das M1–M3 seta `FLAG_DAILY_LOOKER_CALL`** (o Looker acabou de
  falar em pessoa) e a despedida pede para esperar a ligação. **A M4 não seta**
  (roteiro V2 §18): se o convite de New Bark foi de um dia anterior, a ligação
  da reunião pode tocar no mesmo dia, depois do rescaldo e em controle livre.
  Um retry não muda estado e não toca telefone.
- A ligação nomeia o lugar e o motivo; o briefing em Olivine dá o plano; a cena
  de campo só existe depois do briefing. O gancho de fim de missão **não tem
  destino**.
- Chegada ao escritório: gatilho de frame só na porta (4,8) e só com convite;
  Looker e Anabel se aproximam, `BriefingTalk` escolhe o texto pelo estado e
  seta **flag e var juntos**.
- **Armadilha que já falhou três vezes:** estado novo entra como `goto_if_eq`;
  só a última linha de uma lista pode ser `goto_if_ge VAR_RIFT_MISSIONS_STATE`.
  Conferir com `grep` depois de editar Olivine.

### 5.2 Estado

`VAR_RIFT_MISSIONS_STATE` (`0x4120`), só sai de 0 no Hall of Fame:

| Valor | Significa |
| --- | --- |
| 0–1 | Antes do HoF / ligação de Blackthorn pendente |
| 2 / 3 / 4 | M1: briefing pendente / ativa / resolvida (= briefing M2 pendente) |
| 4 / 5 / 6 | M2 |
| 6 / 7 / 8 | M3 |
| 8 / 9 / 10 | M4 |
| 10 | Quatro missões concluídas; reunião pendente |
| 11 | Reunião feita; falta Solgaleo ou Lunala na equipe (pergunta repetível, sem repetir a cutscene) |
| 12 | Reunião completa; `FLAG_EVENT_NECROZMA_ALTAR_UNLOCKED` (nunca é limpa) |
| 13 | Altar: chegada vista; duelo, acordo e teste pendentes |
| 14 | Acordo e teste feitos; a abertura dorme como marca até a travessia; Ultra Necrozma pendente |
| 15 | Boss vencido, nove resgatadas, Necrozma capturado ou sob custódia da Anabel; retorno, estabilização e despedida pendentes |
| 16 | Arco encerrado (permanente) |
| 17+ | Livre (o Nexus deve preferir var própria) |

Os checkpoints **dentro** de 13–15 (duelo feito, travessia, boss visto,
resgate, captura, custódia) moram em `VAR_RIFT_ALTAR_STEP` (`0x4122`,
`ALTAR_STEP_*` em `vars.h`), e o parceiro escolhido em `VAR_RIFT_ALTAR_PARTNER`
(`0x4123`) — a cena do Altar cruza para a arena e volta, e `VAR_TEMP_*` não
sobrevive a warp.

Flags das missões (bloco `CUSTOM`):

| Flag | Valor | Uso |
| --- | --- | --- |
| `FLAG_EVENT_ULTRABEAST_BLACKTHORN/MAHOGANY/CHERRYGROVE/NEWBARK` | `0x1040`, `0x1042`, `0x1043`, `0x1044` | Esvazia a cidade. Invariante: setada ⇔ var no valor "ativo" |
| `FLAG_NO_CATCHING` | `0x1041` | = `B_FLAG_NO_CATCHING`, compartilhada, a engine limpa após a batalha |
| `FLAG_BLACKTHORN_UB_ENGAGED`, `FLAG_BLACKTHORN_TYPE_NULL_PENDING` | — | Checkpoint de retry; presente pendente |
| `FLAG_MAHOGANY_UB_ENGAGED`, `_SAW_RECHARGE`, `_PICKED_CELESTEELA`, `_LILLIE_SETTLING` | `0x104A`–`0x104D` | Dois retries; espelho da escolha; Lillie fica uma carga de mapa |
| `FLAG_CHERRYGROVE_UB_PREPARED`, `FLAG_CHERRYGROVE_UB_ENGAGED` | `0x104E`, `0x104F` | Leitura do Kukui ouvida; checkpoint de retry |
| `FLAG_NEWBARK_UB_ENGAGED` | `0x1050` | Checkpoint de retry da M4 (setada na escolha); mostra a mãe abrigada no laboratório |
| `FLAG_RIFT_LOOKER_SUMMONS`, `FLAG_DAILY_LOOKER_CALL` | — | Convite pendente; ligação do dia |

Próxima flag nova: `0x1051` (skill `alocar-flag`).

### 5.3 Regras comuns de cena

Valem para toda missão e para qualquer encontro novo com Ultra Beast.

**Estrutura**
- **Escolha + boss.** As UBs surgem juntas; o jogador escolhe qual enfrenta
  (menu sem cancelamento, com a plaquinha de quem pergunta) e o acompanhante
  fica com a outra, de forma **narrativa**. Boss simples pelo sistema do
  projeto (`setbossbattle`), captura bloqueada. A escolha é refeita a cada
  tentativa. Motivo técnico: boss só existe em batalha simples, e não há
  parceiro em batalha selvagem.
- **Derrota ou desistência** = blackout no Centro e retry, sem avançar o
  estado. **Checkpoint de retry:** uma flag persistente por missão, setada no
  último beat antes da escolha; o `ON_TRANSITION` repõe as ameaças nos tiles de
  combate (`setobjectxyperm`) e o NPC de entrada usa texto de retry. Nada já
  visto é reapresentado. As quatro missões cumprem.
- Resultado sem vitória não diz que as UBs fugiram se elas continuam lá.
- A cena é 100% scriptada a partir do SIM; nada muda de estado antes dele.
- **Fala de derrota dentro da batalha não tem plaquinha:** `{SPEAKER …}` em
  texto impresso na batalha é consumido sem abrir janela (`src/text.c`,
  `gMain.inBattle`). Antes ele abria a janela do overworld por cima da batalha
  (o nome corrompido da Lusamine). Pode continuar escrito no texto.
- **Evacuação:** moradores com a flag do evento; objeto de flag alheia usa
  cache temporário recalculado no load + `setflag` explícito, **nunca**
  `removeobject` (Friendly Trader de Cherrygrove).
- **Portas trancadas** menos a do Centro: tabela `sLockedTownDoors`
  (`src/field_control_avatar.c`), uma linha por missão, com até duas portas
  abertas. New Bark não tem Centro: ficam abertos o laboratório (abrigo, onde a
  mãe cura depois do cerco) e a casa do jogador. Bilhete de quem evacuou, **sem
  plaquinha**. As quatro missões cumprem.
- **Presente que falha não apaga a vitória:** cidade salva, só a entrega fica
  pendente numa flag própria (padrão da M1).

**Necrozma**
- Está em toda missão, abre a ruptura, nenhum golpe o resolve, absorve as UBs
  da missão depois da vitória e sai pela mesma abertura. **É nomeado desde a M1**
  (Gladion); a partir daí o briefing e a cena usam o nome. O mistério é o que ele
  faz e por quê.
- A fenda é um objeto visível (`OBJ_EVENT_GFX_ALTAR_RIFT`, 32×32): abre antes
  de ele passar e fecha **depois** dele.
- **Tentativa de contenção:** depois da vitória, a Anabel lança uma Ball do
  equipamento policial (nada sai da bolsa do jogador) e a ligação a repele,
  mostrado com movimento e som. A dedução é local, nunca uma lei sobre Poké Balls.
- A absorção é **tentada**, não assistida: o elenco ataca a ligação; as UBs
  resistem antes de serem levadas. Depois, **oscilação obrigatória** da fenda
  em todos os ramos.

**Ultra Beasts**
- Cada par tem uma **relação** mostrada antes de explicada, com consequência que
  o jogador vê e uma contramedida que o acompanhante enxerga e que justifica a
  divisão. Sem circuito infinito nem teleporte: transferência com origem e
  custo, movimento real encoberto. M1 é exceção deliberada (duas criaturas
  soltas, ritmos diferentes).
- Na M2 as assinaturas persistem depois da absorção; ninguém afirma que as UBs
  estão perdidas para sempre, e ninguém confirma contagens maiores sem
  evidência.

**Parceiro do jogador (família Cosmog)**
- Opcional, sem estado: `CheckMysteryEggPokemon` **depois** da batalha, primeiro
  elegível pela ordem da equipe, guardado numa `VAR_TEMP_*` até o fim da cena.
- Aparece **na tela antes** de qualquer fala sobre ele: quatro templates no
  mesmo tile com uma `FLAG_TEMP_*`, no máximo um é adicionado; o follower fica
  escondido na cena inteira. Movimento verdadeiro para o sprite (Cosmoem só
  flutua). Recolhido visivelmente antes de alguém ocupar o tile.
- Cosmog/Cosmoem: o Necrozma o nota e é mantido longe. Solgaleo/Lunala: a borda
  firma por um instante e ajuda a **confirmar** uma leitura; não liberta UBs, não
  prende o Necrozma, não resolve nada.
- A **única** checagem de equipe que bloqueia algo no arco é a da reunião
  (Solgaleo ou Lunala).

**Texto**
- Plaquinha `{SPEAKER NAME_X}` acima da caixa, um falante por mensagem;
  narração e bilhetes **sem** plaquinha (decisão do autor). Skill
  `nomear-falante`; nada acima de 1000 bytes por `msgbox`.
- **Gold/Crystal** falam com `{SPEAKER NAME_NEIGHBOR}`: a plaquinha mostra
  `{NEIGHBOR}`, que vira Crystal para jogador menino e Gold para menina (a mesma
  regra da batalha do rival em New Bark). Nunca Silver (`{RIVAL}` é o Silver),
  nunca sem nome.
- **Experiência não é previsão.** Quem reconhece algo não sabe o que vem;
  quem mede é quem tem instrumento.
- **Conversa longa não acontece no meio da luta.** Revelação vai para depois da
  segurança; no campo, só o custo e uma instrução.
- Nenhum texto cita hora do dia; o evento funciona em qualquer horário.
- Ator fora da câmera não fala; decisão de personagem que não chega à tela não
  existe.
- **Pares de texto entre mapas andam juntos:** fim de uma missão ↔ ligação e
  briefing da seguinte. Hoje: `CherrygroveCity_Text_UBKukuiElm`/`UBHookKukui` ↔
  `RiftMissions_Text_LookerCallM4` ↔ `OlivineCity_House1_Text_BriefingM4Evidence`.
- Travessão U+2014 quebra o build.

**Apresentação**
- **Trilha:** `fadeoutbgm` quando alguém percebe, `playbgm MUS_DP_LEGEND_APPEARS, TRUE`
  antes da revelação completa, reaplicada depois da batalha e no retry (o load
  zera o `savedMusic`), `fadedefaultbgm` só depois de a passagem fechar. As
  quatro missões cumprem.
- **Flash de cena é `fadescreenswapbuffers`, nunca `fadescreen`** (`fadescreen`
  empilha o tint noturno e a cena fica preta). `fadescreen` só antes de warp.
- **Espaço é medido pelo sprite:** UBs, Necrozma e parceiros são 32×32. Pelo
  menos três tiles livres entre duas UBs, dois entre frente e treinador; renderizar
  o quadro antes de aceitar (skill `prototipo-de-mapa`). Se não cabe, **o mapa
  muda** (Mahogany alargada, banco de areia em Cherrygrove).
- **A caixa de diálogo cobre as três linhas de baixo:** ninguém que precisa ser
  visto ao sul do jogador; câmera escolhida para a caixa cair em cenário morto.
- Direções derivadas de coordenadas (`y` cresce para baixo); `turnobject`
  explícito depois de cada deslocamento, flash e batalha.
- **Orçamento de objetos:** 16 incluindo jogador e follower; light sprite não
  conta; objeto que não cabe não spawna, sem erro. Dois templates podem dividir um
  tile se nunca estiverem spawnados juntos e tiverem flags próprias.
- Em costa, ler **colisão e comportamento**: `MB_SHALLOW_WATER` tem colisão 0 e
  o jogador anda nele. Formato do `map.bin` deste repo: metatile `0x07FF`,
  colisão 1 bit (`0x0800`); atributos `u16`; metatile de 24 bytes.
- Armadilhas de script: só `DIR_NORTH/SOUTH/EAST/WEST`; `closemessage` antes de
  `applymovement`; NPC escondido volta com `removeobject` + `setobjectxyperm` +
  `addobject`; bloco que termina em `warpsilent` leva `waitstate`/`releaseall`/`end`.
- Quando a engine não permite o que a cena quer, **a limitação vira encenação**
  (a Anabel segurando a fenda no altar em vez de lutar).

### 5.4 Escala de dificuldade

| Missão | Barras | Nível | Multiplicador | Moveset |
| --- | --- | --- | --- | --- |
| M1 | 3 | 75 | 120 | curado + item |
| M2 | 2, depois 4 | 80 | 130 | curado + item; duas rodadas seguidas contra a mesma UB, a segunda carrega o degrau |
| M3 | 4 | 85 | 140 | um golpe de controle por boss (Calm Mind / Trick Room) + item |
| M4 | 4 | 90 | 150 | dois eixos (preparo + controle) + item |
| Ultra Necrozma | 5 | 90 | 160 | `BOSS_PHASE_PROFILE_NECROZMA` |

4 barras é o teto da engine. Nenhum desses números foi jogado de M2 em diante;
se x140 for parede, a M4 herda o número corrigido em vez de subir. Parafusos da
M3, em ordem: tirar Weakness Policy → 140→135→130 → trocar Trick Room → nível 80.

---

## 6. As quatro missões

### M1 — Blackthorn (Buzzwole + Pheromosa)

A Clair (+ Kingdra) já segura o Necrozma na rua; o Dragon Pulse dela o faz
recuar um tile — contém, não resolve. Ele abre a fenda; as duas UBs avançam com
ritmos e linhas diferentes contra o jogador; o Silvally corta a frente e depois
a lateral, e o Gladion chega e **nomeia o Necrozma**. Escolha + boss. Contenção
da Anabel repelida, absorção tentada por Kingdra e Silvally, oscilação da fenda.
O parceiro Cosmog aparece como ator. O Gladion entrega um Type: Null
(**checagem de espaço antes do SIM**; falha não repete a batalha). Retry com
texto próprio. Despedida: esperar a ligação.

### M2 — Mahogany (Xurkitree + Celesteela)

A rua sul foi alargada para cinco linhas. Pryce evacua e **cobre** a porta do
Ginásio com o Mamoswine. A Lillie é descoberta na rua. Uma UB recarrega a outra
— **uma** transferência, com a fonte perdendo brilho. A Lillie corrige o plano
numa linha e, com o Pryce, ergue uma **parede de gelo real** (metatiles
`METATILE_MahoganyTown_IceWall_*`) que corta aquele trajeto. O Necrozma é
bloqueado no chão e alcança as UBs **por cima do gelo**; **duas assinaturas
persistem** no instrumento. Dois retries distintos (antes e depois de a parede
existir). Pryce cumpre a promessa da lâmpada e sai; Lillie fica até os
moradores voltarem.

### M3 — Cherrygrove (Blacephalon + Stakataka)

A ligação cita a costa e as notas da Lillie; o briefing apresenta o Kukui como
quem reportou e o plano: agir antes de o Necrozma recolher as UBs. Na praia
noroeste, o Kukui explica que o clarão da Blacephalon **esconde os passos** do
Stakataka. Ele solta o Incineroar antes do perigo. A Anabel sente uma abertura
antes do instrumento; o Necrozma sai **através** dela. Sob o clarão o Stakataka
**anda** pelo banco de areia (24,10)→(25,10); o Incineroar ocupa (26,10) antes
dele e o empurra um tile. Uma distorção começa onde o jogador está; a Anabel o
tira de lá e só ocupa o tile depois que a distorção passa. Escolha + boss (o
Incineroar muda de frente conforme a escolha). Depois da vitória, a Ball chega
**antes** do arrasto e a ligação a repele; o Incineroar ataca o filamento a
tempo de vê-lo oscilar, não de rompê-lo. Sinais persistem; o Looker registra a
direção. Com a praia segura, a Anabel conta que é Faller. O Kukui vai pedir ao
**Elm** as leituras dele. Estado 8.

### M4 — New Bark (Kartana + Guzzlord + Nihilego)

A pedido do Kukui, o Elm compara seis semanas de leituras com as da polícia:
três pontos de New Bark estão acordando. O Looker liga; o briefing apresenta o
recurso antes do uso — a Anabel pediu à Aether um **campo de contenção** e a
Lusamine vem trazê-lo pessoalmente. Na rua (sem Centro Pokémon): a mãe ajuda o
abrigo no laboratório, Gold/Crystal e Azumarill guardam o corredor até ele, o
Elm registra da porta do laboratório. No SIM, o jogador vai ao posto de comando
(16,12); Lusamine e Anabel instalam os dois **emissores** nas laterais, um teste
curto acende a linha entre eles, Snorlax (da Anabel) e Milotic (da Lusamine)
saem da Ball.

As três aberturas fazem coisas **diferentes**: o Kartana corta uma seção da
cerca temporária, o Guzzlord come metade da barricada de toras e avança até
debaixo da mãe, e o Nihilego sobe para a faixa por onde ela atravessa. O
Azumarill o repele pela lateral. A Lusamine tenta mandar o jogador para o abrigo
com a mãe; a mãe confia no filho/filha e a Lusamine aceita uma divisão
concreta — um avanço pequeno, não uma conversão. A mãe e o Looker entram no
laboratório; o Looker volta ao posto. Escolha + boss (três ramos com parceiros
trocando de frente). Depois da vitória o campo **realmente corta** as três
ligações; a Anabel lança uma Ball policial; o Necrozma chega por uma distorção,
o campo o segura, ele aumenta o fluxo, o campo cede, a Ball volta intacta, a
Lusamine desliga os emissores e as três viram luz e são absorvidas. **Ultra
Necrozma** surge no mesmo tile, força a linha a recuar, e sua luz falha em
pulsos desiguais — antes e independentemente do parceiro Cosmog. Ele recua pela
abertura principal; as menores fecham depois. O Elm registra **nove padrões
distintos** (dois de cada missão anterior e os três daqui). Rescaldo com a mãe à
porta do abrigo; a Lusamine entrega os registros da Aether e pede Lillie e
Gladion; o Looker convoca a reunião. Estado 10.

Contratos que a reunião e o altar herdam (V2 §22): o campo funcionou e foi
vencido pela fonte; a forma Ultra é potente e instável; nove assinaturas
persistem; a rota ao altar é encontrada **no intervalo** com os dados de Elm,
Aether e Cherrygrove; a Lusamine aceitou dividir uma tarefa; New Bark não dá
Solgaleo, Necrozma nem item de captura.

---

## 7. Reunião PRÉ-NECROZMA

Dentro de `OlivineCity_House1`: Looker, Anabel, Lusamine, Lillie + Ninetales,
Gladion + Silvally e Kukui, mais a instância de cena do parceiro do jogador
durante o teste (11/16 objetos). Estados 10 → 11 → 12. **Roteiro V2 aplicado
(26/09/2026)** — [`PRE_NECROZMA_ULTRABEAST_SCRIPT_V2.md`](PRE_NECROZMA_ULTRABEAST/PRE_NECROZMA_ULTRABEAST_SCRIPT_V2.md)
e [`PRE_NECROZMA_ULTRABEAST_IMPLEMENTATION.md`](PRE_NECROZMA_ULTRABEAST/PRE_NECROZMA_ULTRABEAST_IMPLEMENTATION.md);
runtime pendente. A cena parte dos contratos da M4 (§6): a rota veio dos dados
de Elm, Aether e Cherrygrove no intervalo; ninguém promete UBs ilesas; a
Lusamine mantém o progresso de dividir tarefas (ensina o controle porque a
Lillie pediu algo concreto) e o conflito de liderança fica para o Altar.

O que a cena estabelece: o estabilizador de duas unidades (recurso ficcional,
segura passagem aberta, não abre nem garante volta; a Anabel opera o módulo de
dentro, e é por isso que ela não luta no Altar), a Beast Ball do Kurt **retida
pela Anabel** até a captura roteirizada do Ato IV, e o teste de bancada do
parceiro — sprite em cena, pulso, luzes — que prova compatibilidade, nunca
travessia segura.

Mecânica: no estado 10 os visitantes só aparecem **depois** da convocação
(`FLAG_RIFT_LOOKER_SUMMONS` também na visibilidade); a cutscene roda uma vez;
o estado 11 não dispara nada na entrada — Looker/Anabel oferecem a retomada
(menu Yes/Not yet), que repete só a elegibilidade e o teste. O gate é
`checkspecies` de `SPECIES_SOLGALEO` e `SPECIES_LUNALA` **só na equipe** (PC e
Pokédex não contam; Cosmog/Cosmoem não passam); com os dois, menu explícito. A
consulta ao PC (`CheckPCHasSpecies`, só leitura) escolhe a orientação do ramo
de falha: "traga do PC" / "precisa evoluir" (procedência via
`CheckMysteryEggPokemon` ou PC) / fala neutra. Termina ligando
`FLAG_EVENT_NECROZMA_ALTAR_UNLOCKED` + estado 12 (juntos) e entregando o
`ITEM_SUN_MOON_TICKET` com `checkitemspace` **antes** do teste e `checkitem`
antes do `giveitem`: sem estado 12 sem passe, sem passe duplicado. Os seis
visitantes compartilham `FLAG_TEMP_1` recalculada no `ON_TRANSITION` — quem
introduzir `removeobject` num deles separa a flag antes; o parceiro de cena
tem `FLAG_TEMP_4` própria. No pós-game (≥16, dom/sex) a Lusamine senta à mesa
via `setobjectxyperm`, e os textos são os do chá (V2 §11).

---

## 8. Altar do Sol e da Lua

`MAP_SUN_MOON_ALTAR` (30×30) e `MAP_ULTRA_SPACE_ARENA` (21×21). Um único altar:
visual de sol de dia e de lua à noite, sem captura de Solgaleo/Lunala, sem
evolução automática, qualquer um dos dois abre em qualquer horário.

Roteiro V2 aplicado (26/09/2026, [`ALTAR_sUN_MOON_SCRIPT_V2.md`](ALTAR_SUN_MOON/ALTAR_sUN_MOON_SCRIPT_V2.md),
doc §21). O conflito é quem atravessa: a Lusamine trouxe o equipamento e ainda
quer ir; aceita ficar na base, e durante o resgate **segue uma instrução da
Lillie** — e dá certo.

| Ato | Estado | O que acontece |
| --- | --- | --- |
| I | 12 → 13 | Navio com o passe (SAILOR). Equipe já montada: disco irregular, cinza, auxiliares da Aether/polícia nos suprimentos. Impasse: a Lusamine quer ir; a Anabel lembra que foi ela quem a ensinou a recuar; a Lillie pede a mãe ao lado. Fly liberado |
| II | 13 | Duelo com a Lusamine: exige Solgaleo/Lunala na equipe (menu SYSTEM com os dois), cura antes e depois, sem blackout, quatro resultados com fala própria. Resultado inesperado não conclui nada |
| III | 13 → 14 | Acordo (a Lusamine fica na base externa) e **teste da passagem**: o parceiro sai da Ball e abre; a Anabel vai até a borda interna e volta; a abertura se contrai numa **marca** (`OBJ_EVENT_GFX_PORTAL`). Estado 14 não tem passagem ativa |
| IV | 14 → 15 | Travessia pela Anabel ou pela marca (espaço → parceiro → qual → pronto). Arena: Ultra Necrozma **já Ultra**; a Anabel segura o módulo interno (por isso não luta). Boss 5/90/x160 inalterado; derrota = blackout, reagrupamento na escada e intro curta. Vitória: o parceiro é tratado, as **nove saem em cinco grupos** e um corte mostra as chegadas no Altar; volta para a **captura** (Beast Ball da reunião, `givemon` Lv75 `ball=BALL_BEAST`). Sem espaço: a Anabel guarda o Necrozma e entrega no Altar |
| V | 15 → 16 | Retorno; Necrozma e o parceiro estabilizam a passagem **em cena** e os aparelhos desligam; Lillie ao lado da mãe, convite para o chá, Gladion fica; despedida. A fenda fica, aberta o dia todo: é a entrada do Nexus (27/09; antes, uma vez por dia com `FLAG_DAILY_ALTAR_RIFT`, hoje livre) |

**Depois do estado 16:** Looker e Anabel moram no altar (andam, `WANDER_AROUND`
trocado no `ON_TRANSITION`); a Anabel manda o jogador ao Kurt para Beast Balls.
Escala de dias da semana (`GetDayOfWeek`, nunca sorteio; ninguém em dois
lugares no mesmo dia), com uma revanche diária por personagem (daily flag setada
**antes** da batalha; revanche dá blackout). A Nihilego entra no time da
Lusamine só depois da virada do dia em que o arco fechou
(`FLAG_DAILY_ALTAR_RESOLVED`); nesse dia ela luta com o time do duelo:

| Dia | Altar: Lusamine | Olivine: os cinco | Praia: Kukui | Praia: Lillie + Ninetales | Cianwood: Gladion + Silvally |
| --- | --- | --- | --- | --- | --- |
| Dom | — | sim | — | — | — |
| Seg | sim | — | sim | — | — |
| Ter | — | — | sim | sim | sim |
| Qua | sim | — | — | — | sim |
| Qui | — | — | sim | sim | — |
| Sex | — | sim | — | — | — |
| Sáb | sim | — | sim | sim | sim |

Duas regras técnicas saídas daqui: **nome de `MAPSEC` novo tem no máximo 16
caracteres** (`GetMapName` não limita; acima de 19 corrompe memória) e o Ultra
Necrozma de overworld depende de `OW_BATTLE_ONLY_FORMS_NECROZMA_ULTRA`.

---

## 9. Pós-Necrozma: Nexus

Regras do autor em [`nexus/NEXUS_REGRAS.md`](nexus/NEXUS_REGRAS.md) (modo Daily,
formato, level scaling, pool condicionado à captura) e pool de lendários em
[`nexus/POOL_LENDARIOS.md`](nexus/POOL_LENDARIOS.md); fichas por treinador nas
pastas por região, incluindo a proposta de campeão para cada uma das 11 Ultra
Beasts (aguarda aprovação). Implementado em modo esqueleto (27/09/2026): a fenda do
altar, aberta o dia todo, leva ao mapa `Nexus`; detalhes, receitas para
acrescentar conteúdo e checklist de runtime em
[`nexus/NEXUS_IMPLEMENTATION.md`](nexus/NEXUS_IMPLEMENTATION.md). Lendários já capturados continuam elegíveis; o horário não
restringe o loop.

Reserva de treinadores de Hoenn para os pools: uma luta de cada Líder, da Elite
Four, de Archie e Maxie, a última de May e Brendan, Wally e Steven.

---

## 10. Pendências

**Runtime** — nada abaixo foi jogado depois da última mudança:
1. M1 inteira (checklist §11 do doc da M1).
2. M2 (§16.10 do doc da M2).
3. M3 (§15.7 do doc da M3), incluindo o passo do Stakataka sob o clarão, a
   distorção no tile vazio e o Friendly Trader no fim.
4. M4 (checklist do doc da M4: três ramos, retry, parceiro, noite, paletas
   e orçamento de objetos), PRÉ-NECROZMA (checklist §11 do doc dela, agora
   com o V2: gate de convite na visibilidade, menu de escolha, consulta ao
   PC, teste do parceiro com sprite dinâmico, pós-game do chá) e a
   convocação diária inteira (estados 4, 6, 8, 10).
5. Altar V2 inteiro (checklist §21.8 do doc do Altar): duelo e plaquinha
   depois da batalha, teste da passagem, travessia, retry, o corte de
   acolhimento sem o jogador na tela, captura em Beast Ball, custódia, Ato V.
6. Balanceamento x130 / x140 / x150.
7. Tudo de dia **e** de noite.

**Roteiros V2 a aplicar:** nenhum. (PRÉ-NECROZMA e Altar aplicados em 26/09/2026.)

**Técnico**
- Tela branca ao entrar na fenda diária do altar (doc do altar §18.5).
- `ShouldDoRiftMissionCall` cita `FLAG_BLACKTHORN_TYPE_NULL_PENDING` por nome; a
  próxima missão com presente pendente acrescenta a sua ou vira uma flag
  genérica.
- A ligação toca em qualquer mapa; se incomodar, filtrar com `MapAllowsMatchCall`.
- Clair pode aparecer no Dragon's Den durante a M1 (entrada é caverna).
- Mapas alterados por código (rua de Mahogany, banco de areia de Cherrygrove)
  ainda não passaram pelo retoque do autor no Porymap. As barreiras de New Bark
  não mudam o `map.bin`: são `setmetatile` no `ON_LOAD` enquanto o evento está
  ativo.
- Nexus: runtime inteiro (checklist §9 do doc do Nexus) e as três confirmações
  do §8 dele.

---

## 11. Decisões fechadas que não voltam

| Ideia | Situação |
| --- | --- |
| Ultra Beast obrigatória antes da E4 | Não: todo conteúdo explícito de UB é pós-E4 |
| Nove missões de uma UB | Quatro missões com duas (três na M4) |
| Escritório fora de Olivine; Looker na Route 29 | `OlivineCity_House1`; Looker saiu da Route 29 |
| Menu de recusa / vitória obrigatória em duelo narrativo | Removidos; derrota continua a história |
| Gladion na entrada da Liga / com a Whitney | Removidos; duelo antes da Victory Road |
| Assistente do Elm entregando o ovo; Togepi/Shiny Stone | Gladion entrega; Elm dá Eviolite pela família Cosmog |
| Lillie entregar Cosmog; presente de Cosmoem; evolução automática | Não; Mystery Egg em Violet, evolução normal |
| Altares separados de Sol, Lua e Eclipse; capturar Solgaleo/Lunala neles | Um altar, dois visuais, sem captura |
| Filtro de lendários ainda não capturados no loop | Rejeitado |
| Anabel como loja de Beast Balls | Não: ela manda ao Kurt, que as fabrica |
| Anabel lutando ao lado do jogador no altar | Não: ela segura a fenda |
| Necrozma sem nome até a reunião | Superado: nomeado na M1 |
| Teleporte do Stakataka; "não piscar"; Kukui Fundador da Liga revelado em cena; Anabel levando a luz no corpo | Substituídos pelo roteiro V2 da M3 |
| Kukui lendo todos os logs de Johto e adivinhando o sensor quebrado | Substituído: ele pede os dados ao Elm |
| M4 como derrota: Ultra Necrozma derrubando os quatro treinadores, "a conta de nove" como coleta, "we softened them for it" | Substituído pelo V2: a cidade é protegida, o campo funciona até ser vencido, a forma Ultra é instável e recua |
| Conversa de Faller no briefing da M4; a Anabel sentindo New Bark de Olivine | Fora: a condição foi contada em Cherrygrove; ela só sente de perto |
| Lusamine como surpresa na estrada; Kukui indo a New Bark | Fora: o briefing anuncia a Lusamine com o equipamento; o Kukui deixou Johto |
| Gold/Crystal sem plaquinha | Substituído: `NAME_NEIGHBOR` |
| Altar V1: a Lusamine atravessa sozinha para "pagar" o passado; a Lillie encerra a discussão depois do duelo; o parceiro "harmoniza" os portais no fim da luta; as nove só na memória | Substituído pelo V2: ela fica na base e segue a filha no resgate; as nove saem na tela; Necrozma e o parceiro estabilizam juntos no Altar |
| Sorteio por load para presença no pós-game | Escala de dia da semana |
| Suporte a saves antigos | Fora de escopo; alvo é New Game |
| Hoopa no centro da história; fusão Lusamine/Nihilego | Fora |
