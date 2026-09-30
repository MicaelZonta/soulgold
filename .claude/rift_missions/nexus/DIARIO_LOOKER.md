# Diário do Looker — os cadernos de cada campeão

> 📝 **Proposta de 30/09/2026, aguardando o autor.** Nada disto está no código.
> Regras que valem: [R16, R18, R20 e R21](NEXUS_REGRAS.md).

O [R18](NEXUS_REGRAS.md) já põe **um** Looker File no chão da sala do campeão
(um texto por lendário, em `data/scripts/nexus.inc`). O diário amplia isso:
cada **campeão** ganha um caderno de **três páginas** — começo, meio e fim da
história daquele fragmento. O Looker File por lendário continua como está; o
diário é a história da **pessoa** que guarda a porta.

## Onde fica

```
nexus/<região>/diario_looker/<treinador>/1_comeco.md
nexus/<região>/diario_looker/<treinador>/2_meio.md
nexus/<região>/diario_looker/<treinador>/3_fim.md
```

Uma pasta por campeão (não por lendário). Quem campeia mais de um lendário tem
um caderno só, e ele atravessa os lendários dele.

## Mecânica proposta (para quando for ao código)

- O caderno no chão da sala do campeão mostra a **próxima página ainda não
  lida** daquele campeão: primeira vez que ele é campeão → página 1; segunda →
  página 2; terceira em diante → página 3 (e a 3 fica).
- Custa **2 bits por campeão** (0–3 páginas lidas). Para 86 campeões são 172
  bits: não cabe numa var só. Alternativas a decidir com o autor: um
  bloco de flags (skill `alocar-flag`), ou ler a página pela `dailySeed`
  (sem save: página = sorteio do dia; perde a ordem garantida).
- Texto de narração, **sem plaquinha** (R18). A letra é do Looker, a tinta
  está molhada, a data não chegou.

## Formato de cada página

Cada `.md` tem:

1. Título: `# <Treinador> — página N (começo|meio|fim)`
2. Linha de metadados: data que aparece no topo da página, estado da tinta.
3. **O texto** (inglês, texto do jogo), em citação `>`.
4. `<details>` com o bloco `.inc` pronto (`Nexus_Text_Diary_<Treinador>_<N>`),
   linhas ≤ 208 px (`python3 .claude/skills/nomear-falante/medir_linha.py`).
5. **Fios** (português): uma ou duas linhas dizendo que ponto esta página liga
   a outro caderno — para o autor enxergar a costura.

Tamanho: 4 a 8 caixas de texto por página. Interessante, não enciclopédico.

## A voz

O Looker da campanha: detetive da International Police, frases curtas,
observador, meio melancólico, às vezes engraçado sem querer. Anota fatos, não
adjetivos. Nunca diz o nome da espécie (R16) — descreve. Chama o jogador de
"you" quando a página parece escrita **para** ele. Não sabe que escreveu isso.

## Os fios que atravessam todos os cadernos

Estas são as costuras. Toda página 3 (fim) toca **pelo menos um** fio de
outro caderno; as páginas 1 e 2 podem tocar.

1. **A data que não existe.** As páginas 1 e 2 têm datas estranhas (um dia
   que se repete, um ano sem número, "the day after the last day"). **Toda
   página 3 é datada "September 31st".** Nenhum caderno explica. Quem lê
   vários percebe que todos os fins acontecem no mesmo dia que não existe.
2. **A mão que muda.** Na página 1 a letra é firme. Na 2, a mesma letra com
   uma segunda, mais nova, corrigindo à margem. Na 3, as duas se alternam
   no meio da frase. (Ninguém diz de quem é a segunda letra. Pista: ela
   escreve como alguém da Battle Frontier — curta, precisa, fala de
   "vibrations". É uma Anabel de algum fragmento. Nunca confirmar.)
3. **O casaco.** Em vários fragmentos há um homem de sobretudo que chegou
   antes, fez perguntas e foi embora. Os campeões lembram dele de jeitos
   diferentes. Ele é sempre descrito, nunca nomeado.
4. **Objetos que passam de um fragmento a outro.** Uma Beast Ball rachada; um
   relógio de bolso parado em horas diferentes; um elo de corrente vermelha;
   uma pena (arco-íris ou prateada); uma pedra de Mega sem dono. Um caderno
   perde o objeto na página 3; outro caderno o encontra na página 1 ou 2.
   Registre o par no campo **Fios**.
5. **Os pares entre fragmentos** (cada um sabe só um lado):

| Fio | Cadernos que se tocam | O que liga |
|---|---|---|
| Pallet | Red, Blue, Leaf | um garoto de Pallet com um Pikachu no ombro que nunca cresce, visto de longe nos três fragmentos (nunca nomeado); o relógio de bolso parado |
| Rocket | Giovanni, Silver, Archer, Ariana, Proton, Petrel, Jessie e James | um pai que não voltou; Jessie e James procuram um chefe que, no fragmento deles, nunca existiu; o laboratório de Cinnabar/Mewtwo |
| Liga de Kanto | Lorelei, Bruno, Agatha, Lance, Koga | uma Liga em que a Elite Four nunca foi derrotada; os corcéis do rei (Agatha e Lorelei) procuram o **Will**, que tem o rei |
| Tempo | Spenser, Cyrus, Cynthia, Eusine | o relógio parado; a corrente vermelha (Cyrus a usa, Cynthia a quebra); o Celebi do Spenser guarda as horas que o Cyrus apagou |
| Lagos | Barry, May, Wally, Roxanne | as três lagoas — conhecimento, emoção, vontade — em fragmentos diferentes; Barry chega sempre atrasado |
| Unova | Hilda, N, Cheren, Alder, Colress, Clair | verdade e ideal separados em pessoas diferentes; o terceiro dragão (Clair) é o que sobrou; Colress mede os dois |
| Hoenn | Maxie, Archie, Shelly, Zinnia, Steven, Wallace, Juan | mar e terra; a Zinnia chega depois de todos e fala de um céu que caiu; a Shelly larga a Aqua |
| Alola | Lillie, Gladion, Lusamine, Kukui, Hau, Olivia, Guzma, Soliera | a família Aether separada; o festival que o Hau nunca perdeu; o joalheiro de Konikoni |
| Ultra | Anabel, Colress, Elesa, Volkner, Steven, Ramos, Guzma, Soliera, Byron, Fantina, Bruno | a luz roubada de Ultra Megalopolis; a Beast Ball rachada |
| Galar | Leon, Blue, Norman, Tucker | a espada e o escudo em mãos erradas; a noite escura que o Leon não parou |
| Kalos | Diantha, Ramos, Wallace | a beleza que não envelhece; um homem muito alto (AZ, nunca nomeado) que esperou 3.000 anos |

6. **Looker Files existentes.** O caderno pode citar o número do Looker File
   do lendário (`File L-493`, `File UB-01`…) como "see also". Não repete o
   texto dele.

## Campeões novos (proposta de 30/09/2026)

Os 17 treinadores com arte nova (`.filetransfer/.trainers/<Nome>/`, ver
[README](README.md)) precisam de lendário. Proposta: **tirar um lendário de
quem campeia dois ou mais**, sem deixar ninguém sem nenhum; em dois casos,
**co-campeão** (como o Kyogre com Misty e Archie).

| Treinador novo | Lendário | Quem cede | Quem cede fica com |
|---|---|---|---|
| Agatha | Spectrier | Morty | Ho-Oh |
| Lorelei | Glastrier | Pryce | Articuno |
| Jessie e James | Meloetta | Petrel | Ogerpon |
| Barry | Uxie | Roxanne | Terapagos |
| Cynthia | Giratina | — (co-campeã com o Silver) | Giratina |
| Cyrus | Dialga | Spenser | Celebi |
| Gardenia | Shaymin | Erika | Virizion |
| Shelly | Manaphy | Misty | Kyogre |
| Zinnia | Rayquaza | Lance | Gouging Fire |
| Hilda | Reshiram | Brendan | Jirachi |
| N | Zekrom | May | Mesprit |
| Cheren | Cobalion | Chuck | Urshifu |
| Alder | Slither Wing | Bugsy | Iron Moth |
| Diantha | Xerneas | Wallace | Diancie |
| Hau | Tapu Koko | Kukui | Solgaleo |
| Olivia | Tapu Lele | Lillie | Lunala |
| Leon | Eternatus | Tucker | Hoopa |

Enquanto o autor não aprova, **as fichas de quem cede continuam como estão**
(o código também). A fala de campeão antiga de quem cede não é apagada: se a
troca for aprovada, ela vira fala genérica extra ou sai.

> O **Ash** estava na primeira versão desta tabela (→ Marshadow) e saiu: o autor o removeu do projeto em 30/09/2026 (sem fonte legítima de sprite). O Marshadow fica com o Archer.
