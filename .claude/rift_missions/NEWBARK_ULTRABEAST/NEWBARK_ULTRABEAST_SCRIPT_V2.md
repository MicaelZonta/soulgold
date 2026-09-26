# New Bark — Kartana, Guzzlord, Nihilego e Ultra Necrozma

**Rift Mission 4 · Roteiro reconstruído V2 · 25/09/2026**

**Status:** proposta completa de história, falas e encenação para implementação. Substitui o roteiro anterior desta missão. Continuidade: Blackthorn V3, Mahogany V3, Cherrygrove revisada e convocação diária de Looker. Falas em inglês; explicações em português. Não representa mudanças já executadas na ROM.

## 1. A razão deste encontro

Kukui pediu os registros de Elm depois de Cherrygrove. Elm comparou o histórico de seis semanas com os pulsos registrados pela polícia e confirmou uma atividade crescente em New Bark. Os registros eram fracos e inconclusivos antes; agora há dados externos suficientes para reconhecê-los. Ele não ignorou por seis semanas três monstros aparecendo em sua cidade.

Looker chama o jogador para Olivine. A equipe combina evacuação e contenção antes de uma manifestação completa. Anabel solicitou apoio de Aether para interromper as ligações, e Lusamine veio pessoalmente com equipamento. Ela chega para trabalhar, com conhecimento relevante e tendência a assumir decisões demais. Não aparece de barco por coincidência no momento exato do desastre.

Quando o jogador chega, Gold/Crystal e Azumarill mantêm a rua livre, a mãe ajuda a organizar o abrigo e Elm prepara o registro. As três UBs aparecem durante a operação e pressionam diferentes acessos à cidade. A equipe segura as frentes, tenta isolar as criaturas e quase completa a contenção. Necrozma rompe a barreira preparada, absorve as três e manifesta sua forma Ultra. Seu poder aumenta, mas a instabilidade também: ele perde a capacidade de sustentar a forma e recua pela abertura.

**A cidade foi protegida. As UBs ainda precisam ser recuperadas. O objetivo seguinte é chegar a Necrozma e contê-lo, em vez de continuar tentando resgatar criaturas de cada nova abertura que ele cria.**

Esta missão não apaga as vitórias anteriores nem afirma que o jogador foi responsável pela crise por enfrentar UBs que ameaçavam moradores.

## 2. Regras de continuidade e personalidade

| Personagem | Função na operação | Como fala e decide |
| --- | --- | --- |
| Mãe | Organiza abrigo, confere moradores, oferece descanso ao jogador | Afetuosa, prática; confia na experiência do filho/filha e também entra em segurança |
| Gold/Crystal | Protege o corredor entre a rua e o abrigo com Azumarill | Familiar, seguro, breve; ajuda porque mora ali, sem pedir validação profissional |
| Elm | Cruza dados, instala sensores e registra os sinais | Observador e cuidadoso; admite incerteza sem se chamar inútil |
| Lusamine | Opera a contenção de Aether e segura uma frente com Milotic | Precisa, formal, acostumada a decidir; aceita uma divisão concreta sem resolver todo seu arco |
| Anabel | Coordena frentes, acompanha Necrozma e segura a segunda frente com Snorlax | Direta, distingue informação medida de sensação; aceita apoio |
| Looker | Cuida de acessos, comunicação e retirada | Humano, cortês, objetivo na emergência; nunca ridiculariza o rival |
| Protagonista | Escolhe e enfrenta a UB prioritária | Tem responsabilidade real pela defesa e a batalha decisiva |

**Rival:** é o Gold/Crystal previsto no projeto, nunca Silver. Usar o nome correspondente ao ator efetivo, ou o nome personalizado já existente se houver. Nos blocos abaixo, `{RIVAL_NAME}` representa a plaquinha dinâmica; não é texto impresso nem novo buffer declarado como existente. Resolver a identidade pela regra atual do jogo, sem inventar gênero, idade, famílias ou dois anos de exclusão.

**Pokémon dos NPCs:** Azumarill é preservado. Milotic é escolhida dentre os Pokémon já previstos para Lusamine no design do projeto. Snorlax é a proposta de parceiro de campo de Anabel nesta revisão; precisa ser integrado ao ator e à encenação. Ambos saem da Ball antes de ajudar. Não transformar gestos de ataque dos humanos em golpes invisíveis de Pokémon.

**Toda caixa tem identificação acima dela:** um falante por bloco, inclusive menus, telefone, mensagens opcionais, retry e sistema. `NARRATOR`, `NOTE` e `SYSTEM` identificam texto sem interlocutor humano. Nunca usar `NONE`. Não reaproveitar o nome de Lusamine depois de trocar o falante.

Necrozma já é conhecido. A condição de Faller foi explicada em Cherrygrove. Anabel não ganha alcance de Olivine até New Bark, não narra uma memória inédita para justificar o perigo e não repete sua apresentação pessoal.

## 3. A ligação diária

Exigir Cherrygrove concluída, nenhum convite anterior pendente e nenhuma convocação de Looker no dia corrente do sistema diário/RTC. Blackthorn e as demais chamadas usam o mesmo registro. O limite é de ligações, não de tentativas de batalha. Não exige 24 horas corridas.

Disparar em controle livre, fora de menu, batalha, diálogo, cutscene e transição. Dentro da base de Olivine, aguardar saída. Adiar não consome a ligação. Ao terminar, registrar juntos a data e o convite de New Bark. Convite persiste entre dias e saves, sem lembrete automático, expiração ou acumulação de chamadas por dias ausentes.

### `Phone_Text_LookerNewBarkInvite`

```text
LOOKER
{PLAYER}, Professor Elm contacted us.
His readings match the rift at Cherrygrove.

Come to the Olivine base.
We need to plan our approach to New Bark.
```

Não anunciar que a mãe já está cercada enquanto se exige o desvio para Olivine. O motivo da ligação é uma atividade preocupante confirmada, e a equipe está preparando a resposta.

### `OlivineCity_House1_Text_WaitForNewBarkCall`

Reutilizar a label/texto de transição definidos em Cherrygrove, sem duplicar definição no código:

```text
LOOKER
We're waiting for Professor Elm's records.
I'll call when we've compared them.
```

Depois da ligação, liberar briefing. Depois do briefing, ativar a preparação de New Bark. Visitar a cidade antes não contorna a ordem nem antecipa as três aparições. Saves anteriores com missão já briefada/iniciada mantêm esse progresso sem chamada retroativa; não inventar datas históricas desconhecidas.

## 4. Briefing — por que voltar para casa

Preservar a chegada de Looker e Anabel à porta da base. O texto abaixo é a substituição integral dos três grandes blocos antigos. Nenhuma oferta de itens sem definir item, quantidade e entrega: a frase antiga “Take these” é removida.

### `OlivineCity_House1_Text_BriefingM4Evidence`

```text
LOOKER
Elm sent the records Kukui requested.
Some go back six weeks.

He checked the equipment.
The pulses kept coming back.
```

### `OlivineCity_House1_Text_BriefingM4Comparison`

```text
ANABEL
They match our recordings.
The latest readings are stronger,
and three points are responding.

We need to clear the area
before they open fully.
```

### `OlivineCity_House1_Text_BriefingM4Safety`

```text
LOOKER
Your mother is helping prepare the lab.
There's room to shelter the residents.

We'll meet you outside your house.
```

### `OlivineCity_House1_Text_BriefingM4Containment`

```text
ANABEL
Timing wasn't enough at Cherrygrove.
We need to interrupt the connection.

I asked Aether for containment equipment.
Lusamine is bringing it herself.
```

### `OlivineCity_House1_Text_BriefingM4Plan`

```text
ANABEL
We'll hold the three fronts,
then isolate the weakened Pokémon.

Prepare your team before you join us.
```

O briefing apresenta o recurso antes de ele resolver qualquer coisa. Não anuncia que a contenção certamente funcionará nem esconde que Lusamine estará ajudando.

### Orientações repetíveis

#### `OlivineCity_House1_Text_LookerGoAheadM4`

```text
LOOKER
Outside your house in New Bark.
We'll keep the approach clear.
```

#### `OlivineCity_House1_Text_AnabelGoAheadM4`

```text
ANABEL
There's no Pokémon Center in New Bark.
Heal before we begin.
```

## 5. Encenação — uma cidade, três frentes, um corredor

Abandonar a fila de seis humanos diante da casa e a obrigação de manter todos na mesma tela. Organizar enquadramentos de preparação, frentes e rescaldo. O jogador entende a rua por ações e posições, não por uma aula sobre o mapa.

O mapa original oferece como referências a porta do laboratório `(10,9)`, a porta da casa `(20,11)` e o ponto de chegada/recuperação `(20,12)`. **Não bloquear esse ponto com ator, equipamento ou disparo automático de boss.** As posições antigas das UBs servem apenas de referência de região; a nova coreografia exige validação no mapa atual.

| Área | Uso | Regra de circulação |
| --- | --- | --- |
| Laboratório | Abrigo e registro de Elm | Entrada protegida, sem equipamento na porta |
| Casa do jogador | Encontro com Looker e apoio para descanso | Porta e tile de chegada livres |
| Frente norte | Kartana e cerca/barreira temporária | Separada do acesso final ao laboratório |
| Frente sul | Guzzlord e bloqueio de caixas vazio | Faixa já evacuada para atrair seu avanço |
| Frente central | Nihilego e linha de defesa | Distância visível dos moradores |
| Corredor protegido | Rival/Azumarill e trânsito para o abrigo | Não coincide com nenhuma trajetória de ataque |
| Contenção | Dois emissores móveis de Aether | Montados nas laterais, fora de warps e da passagem |
| Aparição de Necrozma | Área livre entre as frentes | Distância suficiente para sua forma Ultra e a retirada |
| Parceiro do jogador | Ao lado protegido do protagonista | Sem sobreposição com Azumarill, Snorlax ou Milotic |

**Mapa:** se as distâncias não couberem, ampliar localmente a área útil ou redistribuir frentes. Não inventar coordenadas “validadas”. Verificar colisão, comportamento, elevação, largura visual dos sprites, rotas de câmera e limite de objetos. Não assumir que ausência de água torna qualquer tile apropriado para todos os movimentos.

Equipamento pode usar metatiles/efeitos; não precisa consumir dois slots de NPC. Abrigados saem da população visível antes da fase com três UBs e três parceiros. Recolher parceiros que terminaram sua função antes de outros entrarem, com ação visível. Não esconder um Pokémon que ainda está supostamente contendo uma ameaça.

## 6. Preparação em New Bark

Ainda não há três UBs atacando enquanto o jogador conversa livremente. Há pulsos e sinais locais, moradores terminando o abrigo e a equipe preparando a operação. O incidente completo começa após confirmar prontidão. Não usar contagem de três minutos que fica congelada indefinidamente nos menus.

### Lusamine — `NewBarkTown_Text_UBLusamineIdle`

```text
LUSAMINE
{PLAYER}. I'm Lusamine.
Anabel sent me the recordings.

I'll handle the containment field.
Keep this approach clear for the equipment.
```

Apresentação curta, sem fotografias inventadas, carta de Lillie, pedido antecipado de perdão ou confissão sobre uma fusão com Nihilego não estabelecida nesta continuidade. Não dizer que é a única pessoa que conhece Ultra Space.

### Elm — `NewBarkTown_Text_UBElmIdle`

```text
ELM
Kukui asked for the old readings.
I almost sent only the recent ones.

The earlier pulses helped us find
where to place the sensors.
```

Elm aponta uma estação de registro protegida na entrada interna do laboratório. Esse aparelho compara os dados, não cura ferimentos nem abre portais. Não destruir todos os registros depois e ainda dizer que os tem sem uma cópia definida.

### Mãe — `NewBarkTown_Text_UBMomIdle`

```text
MOM
There you are.
We're nearly ready at the lab.

Have you and your Pokémon rested?
```

Se ainda não houve compromisso ou durante retry, oferecer a cura habitual da mãe numa interação própria, mantendo sua localização coerente com o abrigo. Esta revisão preserva essa função e não inventa um Centro Pokémon.

### Rival — `NewBarkTown_Text_UBRivalIdle`

```text
{RIVAL_NAME}
I've checked the houses.
Azumarill and I will keep the path open.

You handle whatever comes through.
```

Azumarill já está fora da Ball junto do rival, olhando o acesso. Há confiança no protagonista sem comparação de currículos. O rival não precisa ser contratado pela polícia para defender sua cidade.

### Anabel — `NewBarkTown_Text_UBAnabelIdle`

```text
ANABEL
Elm's sensors are in place.
We'll be able to compare all three openings.

Speak with Looker when you're ready.
```

### Bilhete — `NewBarkTown_Text_UBDoorNote`

```text
NOTE
Shelter is available at Professor Elm's lab.
Please keep the main road clear.
```

Só mostrar nas portas realmente fechadas pelo evento. Não bloquear a casa do jogador ou o laboratório se são necessários para preparação, recuperação e cura.

## 7. Prontidão e equipamento de Aether

### `NewBarkTown_Text_UBLookerGreet`

```text
LOOKER
The residents are almost inside.
We have a clear route back to the lab.
```

### `NewBarkTown_Text_UBReady`

```text
LOOKER
Are you and your Pokémon ready?
```

Yes/No com LOOKER. Recusa:

### `NewBarkTown_Text_UBNotReady`

```text
LOOKER
Take care of your team first.
We'll finish the preparations.
```

**Yes:** ocultar follower com restauração posterior e completar a formação. Mostrar os dois emissores sendo posicionados nas laterais da frente. Lusamine aciona um teste curto: uma linha de luz liga os pontos e se apaga, deixando claro qual área cobre. Elm está no enquadramento ou a câmera se volta para ele antes de sua fala.

### `NewBarkTown_Text_UBFieldExplanation`

```text
LUSAMINE
Once they're weakened, keep them
between these markers.

The field should interrupt the link.
It won't stop them walking out.
```

### `NewBarkTown_Text_UBFieldPositions`

```text
ANABEL
Then we keep the Pokémon inside it.
Looker, watch the route to the lab.
```

**Regra autoral do equipamento:** protótipo portátil de contenção de energia de Aether trazido a pedido de Anabel. Interrompe filamentos existentes dentro de uma área pequena por tempo limitado, com operação contínua; não abre ou fecha rupturas, não é uma prisão física, não desativa Pokémon nem substitui uma Ball. A capacidade de interromper precisa ser demonstrada durante esta cena, não afirmada como tecnologia canônica universal.

Não é o estabilizador de passagem da futura reunião: aquele mantém uma abertura existente para permitir retorno; este tenta cortar conexões locais. Identificar funções e aparência de forma distinta na implementação. Não inventar item de inventário, recompensa ou minigame para o aparelho.

### `NewBarkTown_Text_UBElmPositions`

```text
ELM
I'll record the links from the lab.
Keep the markers where they are.
```

Anabel libera Snorlax na frente livre, com Ball e cry. Lusamine libera Milotic, também visível. As falas e movimentos seguintes são executados por esses parceiros, não pelos humanos.

### `NewBarkTown_Text_UBAnabelPartner`

```text
ANABEL
Snorlax, hold this side.
Leave the middle clear.
```

### `NewBarkTown_Text_UBLusaminePartner`

```text
LUSAMINE
Milotic, with me.
```

## 8. As três UBs aparecem e fazem coisas diferentes

Os sensores reagem em sequência curta. Anabel sente a distorção **agora que está perto**, sem localizar nada à distância. Não transformar o esforço dela em novo discurso.

### `NewBarkTown_Text_UBAnabelOpening`

```text
ANABEL
They're opening. Clear the road!
```

Tema local sai e a ameaça entra antes da revelação. Três pequenas aberturas surgem em áreas separadas, enquadradas uma a uma ou em pares. Cries distintos. Não sincronizar três caminhadas para provar uma mente coletiva.

### `NewBarkTown_Text_UBAppear`

```text
ANABEL
Kartana. Guzzlord. Nihilego.
Keep the path to the lab clear.
```

**Kartana:** corta uma seção de cerca ou barreira temporária, abrindo acesso lateral. Mostrar mudança real do objeto/metatile. O corte não invade uma casa ou apaga permanentemente uma passagem sem plano de restauração.

### `NewBarkTown_Text_UBKartanaBreaks`

```text
{RIVAL_NAME}
Kartana's opened the side path!
```

**Guzzlord:** alcança um bloqueio de caixas vazio que mantinha a faixa sul fechada. Consome/esmaga parte do obstáculo e avança. Isso tira da equipe uma rota que parecia protegida; não consome alguém nem provoca dano gráfico.

### `NewBarkTown_Text_UBGuzzlordBreaks`

```text
LOOKER
The south barrier's gone.
Stay on this side!
```

**Nihilego:** deriva pela abertura deixada no corredor central, obrigando a última pessoa que auxilia no abrigo — a mãe — a parar antes de cruzar. Não pressupor que Nihilego recebeu uma ordem dos outros. O encontro dos três comportamentos cria o cerco.

### `NewBarkTown_Text_UBRivalIntercept`

```text
{RIVAL_NAME}
Azumarill, push it back!
Keep that path clear!
```

Azumarill intercepta lateralmente sem passar por baixo do sprite da mãe. Um ataque de água curto repele Nihilego o suficiente para reabrir passagem; não derrota a UB. O rival mantém a posição, sem celebrar permissão para participar.

### `NewBarkTown_Text_UBAnabelCorridor`

```text
ANABEL
Good. Hold that gap.
Looker, get the last residents inside.
```

**Interação das três:** Kartana abre acessos, Guzzlord destrói bloqueios e Nihilego pressiona o recuo. Não regeneram umas às outras, não dividem mente e não precisam cair no mesmo segundo. As três frentes precisam ser controladas para ninguém contornar o combate do jogador.

## 9. Mãe e Lusamine — uma decisão, não uma palestra

A conversa acontece enquanto Azumarill/Snorlax mantêm o corredor e Milotic cobre Lusamine. Duração curta, sem suspender artificialmente UBs por várias páginas.

Lusamine avança para reorganizar a frente e tenta mandar o protagonista para o abrigo junto da mãe.

### `NewBarkTown_Text_UBLusamineControl`

```text
LUSAMINE
Take your child inside.
I'll handle the front.
```

A mãe olha para o jogador, depois para Lusamine.

### `NewBarkTown_Text_UBMomTrust`

```text
MOM
{PLAYER} knows what they're doing.
Let them help you.

I'll get everyone inside.
You won't have to watch this door too.
```

Lusamine vê o rival sustentando o corredor, o jogador pronto e Anabel mantendo a outra frente. Não responde contando o que seus filhos disseram em um passado não mostrado.

### `NewBarkTown_Text_UBLusamineAccepts`

```text
LUSAMINE
Very well.
Anabel, which front do you need me on?
```

A mãe conclui a travessia para o laboratório com Looker. Porta fecha depois de ambos passarem; Looker retorna ao posto externo quando ela já está segura. Não ficar na rua recusando abrigo para servir de exemplo de coragem. A mãe terá sua próxima fala quando a rua for liberada.

Este é um avanço pequeno de Lusamine: aceita dividir uma tarefa real. Ainda poderá discordar do plano no Altar; não foi moralmente transformada por uma conversa de trinta segundos.

## 10. A escolha do jogador e as outras frentes

### `NewBarkTown_Text_UBChoosePrompt`

```text
ANABEL
Choose your target, {PLAYER}.
We'll keep the other two off you.
```

Menu Kartana / Guzzlord / Nihilego, plaquinha ANABEL. Sem B após compromisso. Não prometer batalha dupla: o rival atua no overworld, protegendo o corredor e impedindo a aproximação de outra UB.

| Escolha | Lusamine/Milotic | Anabel/Snorlax | Rival/Azumarill |
| --- | --- | --- | --- |
| Kartana | Nihilego | Guzzlord | Impede Nihilego de alcançar a retaguarda e mantém a saída |
| Guzzlord | Nihilego | Kartana | Mantém o flanco e impede que o avanço corte a saída |
| Nihilego | Guzzlord | Kartana | Afasta Nihilego da porta e abre espaço para o jogador assumir |

### Escolha Kartana

#### `NewBarkTown_Text_UBPickedKartanaLusamine`

```text
LUSAMINE
I'll keep Nihilego away from the houses.
Milotic, this way.
```

#### `NewBarkTown_Text_UBPickedKartanaAnabel`

```text
ANABEL
Snorlax and I have Guzzlord.
Keep Kartana inside the markers.
```

### Escolha Guzzlord

#### `NewBarkTown_Text_UBPickedGuzzlordAnabel`

```text
ANABEL
I'll block Kartana's path.
Draw Guzzlord toward the cleared ground.
```

#### `NewBarkTown_Text_UBPickedGuzzlordLusamine`

```text
LUSAMINE
Milotic, keep Nihilego here.
```

### Escolha Nihilego

Lusamine acompanha Nihilego por um instante. Anabel aguarda a confirmação. Uma breve hesitação pode existir sem transformar a UB em propriedade ou dívida pessoal.

#### `NewBarkTown_Text_UBPickedNihilegoLusamine`

```text
LUSAMINE
Then I'll take Guzzlord.
Milotic, stay with me.
```

#### `NewBarkTown_Text_UBPickedNihilegoAnabel`

```text
ANABEL
I'll hold Kartana.
Keep Nihilego away from the entrance.
```

### Apoio do rival — comum

#### `NewBarkTown_Text_UBRivalCover`

```text
{RIVAL_NAME}
I've got the way back.
Go ahead, {PLAYER}.
```

Mover NPCs primeiro pelos corredores livres; jogador assume a frente escolhida depois. Mostrar as UBs contidas na área demarcada, sem teletransportá-las durante o menu. Sensores e emissores ficam protegidos na retaguarda, separados dos alvos.

**Boss:** batalha única contra a UB escolhida, quarto degrau do sistema já previsto. Valores de nível, barras, item e golpes permanecem no documento técnico. As demais frentes são encenadas; não precisam terminar no mesmo segundo. Captura em batalha permanece bloqueada enquanto a conexão ainda está ativa.

Após vitória, restaurar ameaça, atores, orientação ao alvo e nome do próximo falante. Não mover automaticamente o protagonista para a fila antiga diante de casa.

## 11. A defesa funciona e a contenção começa

Primeiro mostrar a UB do jogador enfraquecida. Depois Milotic e Snorlax concluem suas frentes, um de cada vez, em breves cortes de câmera. As três continuam visíveis; nenhuma foi absorvida ainda.

### `NewBarkTown_Text_UBAfterBattleAnabel`

```text
ANABEL
Our side is holding.
Keep them inside the markers.
```

### `NewBarkTown_Text_UBAfterBattleLusamine`

```text
LUSAMINE
Milotic, hold there.
I'm starting the field.
```

Lusamine volta ao controle do equipamento por rota livre; Milotic mantém sua frente. Azumarill cobre o corredor e Snorlax segura a outra abertura. A batalha do jogador é o que permite manter a última criatura dentro da área, sem expor a equipe durante a ativação.

O campo aparece entre os emissores. Filamentos das três UBs até as rupturas enfraquecem e se interrompem. Mostrar a reação de cada conexão, com breve leitura dos sensores, antes de anunciar sucesso. Os Pokémon não desaparecem ou ficam paralisados por poder novo.

### `NewBarkTown_Text_UBFieldWorks`

```text
ELM
The links have dropped.
All three Pokémon are still inside.
```

Elm fala da estação no laboratório; usar corte de câmera à porta/interior de trabalho, não uma voz inexplicável vinda de fora da tela. Não é preciso construir uma interface científica nova: três indicadores simples já apresentados bastam.

### `NewBarkTown_Text_UBCaptureStart`

```text
ANABEL
Keep the field running.
I'll secure this one first.
```

Anabel prepara uma Ball policial para a UB escolhida. **Não é a Beast Ball de Kurt.** Item da NPC, sem gasto no inventário do jogador. Não dizer que o lançamento já capturou a criatura e depois removê-la sem explicar.

## 12. Necrozma força a contenção

Anabel e Elm detectam o pulso conhecido. Uma abertura aparece na frente externa da área, com distância dos treinadores; Necrozma atravessa. Ele já é identificado, não precisa ouvir três descrições de sua forma.

### `NewBarkTown_Text_UBNecrozmaArrives`

```text
ANABEL
Necrozma. Keep the field up!
```

Lusamine mantém o aparelho funcionando, em vez de interromper a operação para uma revelação. Necrozma estende novos filamentos que atingem o campo. **Primeiro, o campo os bloqueia:** mostrar choque de luz e ausência de arrasto. A contramedida realmente tem efeito.

### `NewBarkTown_Text_UBFieldHolding`

```text
LUSAMINE
It's holding.
Anabel, now!
```

Anabel lança a Ball. Necrozma aumenta o pulso enquanto a Ball chega: a borda do campo começa a falhar, indicadores mudam e Lusamine precisa sustentar o controle. Evitar um fracasso instantâneo que pareça aparelho decorativo.

### `NewBarkTown_Text_UBFieldStrain`

```text
ELM
The output is climbing!
The field can't hold that level!
```

O aumento de energia é visível no corpo de Necrozma e nos filamentos, antes da conclusão. O equipamento tem capacidade limitada; não introduzir imunidade nova a toda contenção. Ele está sendo vencido por uma fonte que segue ativa do lado de fora.

### `NewBarkTown_Text_UBRivalRetreat`

```text
{RIVAL_NAME}
The path's clear!
Azumarill, cover them!
```

Rival/Azumarill cobrem o recuo lateral dos operadores, sem investida solitária contra Necrozma. Anabel tenta retirar a Ball/afastar a equipe; a conexão restabelecida repele a Ball intacta antes de selar a captura. Lusamine desliga o aparelho quando o campo rompe, evitando que os emissores continuem descarregando junto dos aliados.

Necrozma puxa as UBs em três linhas distintas. Elas resistem brevemente, tornam-se luz antes de atravessar obstáculos sólidos e são absorvidas. Somente seus atores somem. Milotic e Snorlax tentam interromper a aproximação dos filamentos; Azumarill mantém a rota. Nenhum humano ataca com `walk_in_place` fingindo ser um Pokémon.

### `NewBarkTown_Text_UBAbsorbed`

```text
ANABEL
Back behind the markers!
Keep recording, Professor!
```

A captura falhou apesar de ações melhores: a equipe chegou a interromper as ligações, mas não conseguiu mantê-las interrompidas com Necrozma alimentando novas conexões. Esse resultado prepara o plano de conter a fonte no Altar; não conclui que qualquer aparelho ou estratégia sempre falhará.

## 13. Ultra Necrozma — transformação e instabilidade

**Regra autoral do hack:** a absorção das nove UBs acumuladas permite esta manifestação Ultra. Não apresentar esse mecanismo como regra canônica de evolução nem exigir que Solgaleo/Lunala do jogador seja absorvido.

As UBs já foram removidas. Necrozma permanece no seu ponto, com espaço livre ao redor. Sua luz cresce, uma pausa revela a mudança e o ator passa para a forma Ultra. **Normal e Ultra nunca aparecem simultaneamente.** Quando o flash termina, mostrar silhueta e paleta próprias antes de abrir texto.

### `NewBarkTown_Text_UBUltraRises`

```text
ELM
The reading's still rising!
```

### `NewBarkTown_Text_UBUltraRetreat`

```text
ANABEL
Everyone back. Stay together!
```

Ultra Necrozma emite um pulso que força a linha a recuar. Snorlax segura o flanco, Milotic cobre a passagem com seu corpo/ação defensiva apropriada, Azumarill impede que o corredor se feche. Os treinadores recuam por rotas previamente livres; ninguém atravessa o outro ou cai sobre uma porta bloqueada.

Não criar batalha jogável de derrota obrigatória. Não mostrar quatro humanos atacando sincronizados. Não colocar todos no chão enquanto conversam por dez caixas. A ameaça é maior do que a contenção disponível; a resposta é proteger a retirada.

**Pista obrigatória:** depois do primeiro pico, a luz da forma Ultra falha em pulsos desiguais. As bordas de sua silhueta/halo tremem, sua postura perde estabilidade e as aberturas começam a contrair. Isso acontece **antes e independentemente** da reação opcional do parceiro.

### `NewBarkTown_Text_UBUltraUnstable`

```text
LUSAMINE
It can't hold that light steady.
Keep your distance.
```

Anabel não ordena novo ataque “no mesmo instante”. A equipe conserva a cobertura, observa a instabilidade e aguarda uma rota segura. Não declarar vitória contra Ultra Necrozma: a conquista é manter as pessoas protegidas.

## 14. Parceiro do jogador — todos os ramos

Reavaliar espécie depois da batalha. Representar um membro elegível da família Cosmog, escolhido consistentemente pela ordem da party, sem duplicar follower. Manter nome, forma, cry e buffers corretos durante toda a cena. Reações opcionais não condicionam sobrevivência da cidade, confirmação das nove assinaturas ou acesso à reunião.

### Sem família Cosmog

A retirada continua sob cobertura dos três parceiros NPCs. Ultra Necrozma perde estabilidade e se afasta para a passagem. Não inventar que alguém saiu de uma Ball inexistente.

### Cosmog ou Cosmoem

Ball reage e abre; parceiro aparece ao lado protegido do jogador, fora da linha de luz. Cry e movimento adequados; Cosmoem pode flutuar/oscilar, sem caminhada inventada. Necrozma vira o olhar por um instante, mas suas oscilações continuam.

#### `NewBarkTown_Text_UBUltraSensesCosmog`

```text
LUSAMINE
Keep {STR_VAR_1} beside you.
Milotic, cover that side.
```

O jogador olha o parceiro e o recolhe antes de completar o recuo, mostrando Ball. Não colocá-lo como “único ainda de pé”, nem afirmar que é isca, culpado pela ocorrência ou imune ao perigo.

### Solgaleo ou Lunala

Ball abre **antes de qualquer fala descrever sua ação**. Parceiro aparece na lateral protegida, encara a passagem e emite cry/pulso. Uma faixa de luz entre a ruptura e a retaguarda reduz a oscilação brevemente, permitindo ao rival conduzir o último recuo em segurança. O corpo de Ultra Necrozma continua instável; não recupera estabilidade por receber energia do parceiro.

#### `NewBarkTown_Text_UBUltraPartner`

```text
ANABEL
The edge is steady. Move now!
```

#### `NewBarkTown_Text_UBRivalPartnerCover`

```text
{RIVAL_NAME}
We're clear, {PLAYER}!
Bring {STR_VAR_1} back with you!
```

O jogador acompanha o parceiro e o recolhe quando estiver seguro, antes de liberar nova circulação no rescaldo. Não dizer que Ultra Necrozma teve medo, reconheceu uma forma canônica específica ou desistiu por causa dele. O parceiro facilita a retirada; a instabilidade explica a saída em todos os ramos.

**Sem dependência de cenas opcionais anteriores:** não usar “como sempre” ou atribuir uma observação de Blackthorn/Mahogany ao jogador que não levou o parceiro. O teste obrigatório da reunião futura continua necessário para quem ainda não demonstrou a função.

## 15. Retirada de Necrozma e registro das nove

Ultra Necrozma tenta sustentar outro pulso, falha e recua em direção à abertura principal. Mostrar hesitação/postura instável, recuo e travessia. As aberturas menores se contraem na mesma direção e fecham depois dele. Não usar um teleporte de todos os atores.

Elm continua registrando de dentro da área protegida. A estação recebeu previamente cópias dos registros das três missões anteriores. Durante o pico e sua queda, nove padrões distinguíveis aparecem em sequência/grupos no registro. Evitar nove sprites ou nove interfaces simultâneas.

### `NewBarkTown_Text_UBElmNine`

```text
ELM
Nine patterns.
Six match the earlier recordings.
The other three are the ones from here.
```

### `NewBarkTown_Text_UBAnabelNine`

```text
ANABEL
They stayed distinct after the absorption?
```

### `NewBarkTown_Text_UBElmConfirms`

```text
ELM
Yes. Until the opening closed.
I've saved the record.
```

O padrão de saída mais legível permite separar sinais antes misturados nos registros antigos. Não confundir a simples conta 2+2+2+3 com prova de presença: comparar padrões efetivamente registrados. Na implementação, apresentar os indicadores antes/depois e a comparação; se só houver uma linha única sem diferenciação, a afirmação não está sustentada visualmente.

**Conhecimento permitido:** as nove assinaturas persistem, sustentando a tentativa de recuperar as criaturas. Isso não prova que estão ilesas, conscientes ou em perfeitas condições. Não criar certeza médica a partir do aparelho.

### `NewBarkTown_Text_UBStreetClear`

```text
ANABEL
All three openings are closed.
Check the street before we let anyone out.
```

Só agora encerrar trilha de ameaça. Pequena pausa e retorno ao tema local. Rival/Azumarill e Looker conferem acessos; Milotic/Snorlax são recolhidos visivelmente quando deixam de ser necessários. Nenhum nome fica preso no buffer após efeitos.

## 16. Rescaldo — pessoas e resultado

Abrir a porta do abrigo somente depois da conferência. A mãe aparece na entrada; moradores podem sair em pequenos grupos fora da conversa, com caminho livre. Não repovoar a rua em cima de atores de evento.

### `NewBarkTown_Text_UBAftermathLooker`

```text
LOOKER
Everyone in the lab is safe.
How are your Pokémon?
```

Rival verifica Azumarill; o jogador faz um gesto de confirmação. Não inventar condição clínica nem curar silenciosamente se o sistema não executou cura.

### `NewBarkTown_Text_UBAftermathRival`

```text
{RIVAL_NAME}
Azumarill's ready for a rest.
I'll check the side path first.
```

### `NewBarkTown_Text_UBLookerRivalThanks`

```text
LOOKER
You kept our way back open.
Thank you.
```

Reconhecimento específico, sem “ato inútil mais corajoso”, sem surpresa de o rival ser capaz. O rival vai verificar a passagem com Azumarill e depois retorna ao apoio; não desaparece sem cumprir a fala.

### `NewBarkTown_Text_UBMomAftermath`

```text
MOM
Come home when you're ready, {PLAYER}.
You and your Pokémon can rest there.
```

A mãe pode voltar à casa depois de o caminho ser liberado. Não usar “I'll leave the light on” como única instrução de cura, nem prendê-la no laboratório para sempre. Se o jogo exige um ponto fixo para o helper de cura, integrar uma conversa apropriada no abrigo durante o incidente e o helper normal em casa após ele.

### `NewBarkTown_Text_UBAftermathLusamine`

```text
LUSAMINE
The field broke when Necrozma increased
the flow. The Pokémon were contained
until then.

We have to stop the source.
```

### `NewBarkTown_Text_UBAftermathAnabel`

```text
ANABEL
We kept it away from the residents.
We still need to get the Pokémon out.

Next time, the operation has to be
around Necrozma itself.
```

Sem “nós só enfraquecemos comida para ele”, “ninguém ganhou” ou “nunca atacou Johto”. A cena mostrou perigo real e ações que impediram dano maior. A responsabilidade pelo fenômeno não é transferida ao protagonista.

## 17. O caminho para Olivine e o Altar

Elm confere o registro com o alinhamento das aberturas no mapa local. Anabel cruza a direção de retirada com Cherrygrove e os dados anteriores. Isso reduz a área de busca, mas não coloca instantaneamente uma localização exata no mapa por poder de Faller.

### `NewBarkTown_Text_UBElmDirection`

```text
ELM
All three openings closed toward
this same point.

I'll send the full record to Olivine.
```

### `NewBarkTown_Text_UBAnabelCompare`

```text
ANABEL
We'll compare it with Cherrygrove's bearing.
That should narrow the search.
```

### `NewBarkTown_Text_UBLusamineRecords`

```text
LUSAMINE
I'll bring Aether's records too.
You should have had them before today.
```

Lusamine oferece informação sem guardar o nome de Necrozma ou discursar sobre sua própria redenção. Sua admissão tem consequência: fornecer material antes de discutir quem lidera a próxima etapa.

### `NewBarkTown_Text_UBLusamineChildren`

```text
LUSAMINE
Please ask Lillie and Gladion to join us.
I want to hear what they found.
```

### `NewBarkTown_Text_UBLookerReunion`

```text
LOOKER
I'll contact them, and Professor Kukui.
We'll arrange the meeting in Olivine.
```

Kukui havia anunciado que deixaria Johto depois de encaminhar os dados. Não presumir que já viajou para Alola ou que reapareceu instantaneamente: Looker confirma sua disponibilidade durante o intervalo. A convocação final só ocorre quando os participantes e a análise estiverem prontos, respeitando o limite diário.

### `NewBarkTown_Text_UBHook`

```text
LOOKER
Rest here for now, {PLAYER}.
I'll call when we're ready in Olivine.
```

A análise de Elm/Aether identifica a rota ao Altar **durante esse intervalo**, para que a reunião a apresente com base no material reunido. Não dizer que a investigação está encerrada ou que já se conhece o destino de um portal apenas por uma direção de bússola.

Não exigir Solgaleo/Lunala na equipe para terminar New Bark. A apresentação e a checagem do parceiro acontecem na reunião; falta de evolução ou Pokémon guardado no PC devem receber orientações diferentes naquele roteiro.

## 18. Resolução e chamada da reunião

Concluir a missão no estado herdado **10**, após vitória, transformação, retirada e rescaldo. Confirmar no código atual o significado exato dos estados anteriores; não usar o estado da história como substituto do registro diário de telefone.

Limpar UBs, versões de Necrozma, filamentos, efeitos temporários e barreira de contenção. Retirar emissores com Lusamine/Looker ou mostrar seu desligamento antes da transição. Restaurar follower uma vez e devolver o jogador ao ponto seguro, com orientação definida. Não teleportar civis para posições ocupadas.

**Danos leves mostrados têm consequência:** cerca e caixas afetadas ficam em reparo ou são restauradas durante uma transição de tempo assumida explicitamente. Para um fluxo simples de mapa, manter o remendo até o jogador sair; na visita seguinte, restaurar o layout normal. Não declarar “nenhuma cerca foi quebrada” depois de mostrar Kartana cortando uma. Reparo temporário precisa de estado de visibilidade apropriado, ainda a integrar.

Repor os moradores conforme as flags próprias do mapa. Preservar laboratório, serviços, itens e eventos anteriores. O número de sete moradores do documento original deve ser conferido na versão atual; não remover NPCs novos por uma contagem antiga.

### Espera na base — `OlivineCity_House1_Text_WaitForAltarCall`

```text
LOOKER
We're comparing the records
and arranging the meeting.
I'll call when everyone's ready.
```

Não iniciar automaticamente a reunião só porque o estado chegou a 10. Ela exige convite próprio, exceto em saves antigos onde já estiver iniciada/liberada segundo o fluxo anterior.

### Convocação — `Phone_Text_LookerAltarInvite`

```text
LOOKER
{PLAYER}, everyone's here in Olivine.
We have a route to Necrozma.

Meet us at the base.
We need you for the plan.
```

A chamada só acontece após a conclusão desta missão e quando Looker ainda não ligou no dia corrente. Se ligou hoje para New Bark, a reunião aguarda outra data elegível. Se o convite de New Bark era de dia anterior, a próxima chamada pode acontecer hoje, depois da resolução e em controle livre. Não interromper o rescaldo.

Convite persiste sem expirar. Reunião → ida ao Altar é uma única operação, sem outra espera diária no meio. O roteiro `PRE_NECROZMA_ULTRABEAST_SCRIPT.md` ainda precisa incorporar essa condição antes do gatilho antigo de estado 10.

## 19. Retry e recuperação

**Derrota no boss de UB:** não absorver, não transformar, não concluir missão. Respeitar o blackout e sua cura antes de oferecer nova tentativa. O ponto herdado `(20,12)` deve permanecer livre e seguro; falar com Looker pode reiniciar a preparação curta, nunca uma batalha automática no frame de retorno.

Guardar que a introdução já ocorreu. Mãe permanece abrigada, rival já está no posto, Pokémon NPCs seguram as frentes. Não repetir a primeira conversa de Lusamine, evacuação, surpresa das três UBs ou pedido da mãe como se ninguém lembrasse.

### `NewBarkTown_Text_UBRetryLooker`

```text
LOOKER
The lab is safe.
We've kept the way back clear.
```

### `NewBarkTown_Text_UBRetryAnabel`

```text
ANABEL
The field is ready.
Are your Pokémon ready to try again?
```

Yes/No com ANABEL. O campo está preparado, não ativo: precisa de alvos enfraquecidos dentro da área para poder operar.

### `NewBarkTown_Text_UBRetryNotReady`

```text
ANABEL
Take care of them first.
We'll hold the fronts.
```

Aceite: repetir escolha dos três alvos e reposicionamento coerente, com parceiros já presentes. Não forçar o mesmo alvo da derrota. Boss mantém balanceamento. Após vitória, continuar para a primeira ativação real do campo e chegada de Necrozma; esses fatos ainda não ocorreram na tentativa perdida.

**Cura antes de uma nova tentativa:** acesso à mãe deve continuar disponível no abrigo, ou na localização que o motor mantém para a recuperação, sem atravessar uma frente de UB. A implementação precisa escolher uma representação coerente e atualizar visibilidade/diálogo, não duplicar a mãe em casa e no laboratório.

### `NewBarkTown_Text_UBMomHeal`

```text
MOM
Let your Pokémon rest a moment.
I'll take care of them.
```

Executar cura habitual/fanfarra, depois retomar a trilha apropriada ao mapa. Fora da cena comprometida, não repetir música de aparição a cada conversa.

### Resultado não resolvido — `NewBarkTown_Text_UBUnresolved`

```text
ANABEL
The fronts aren't clear yet.
Regroup before we try again.
```

Mapear fuga/interrupção/resultados do motor sem inventar vitória. A sequência posterior à vitória é cutscene: não deve gerar um segundo blackout pela transformação, apagar a vitória ou exigir refazer o boss porque faltou um recurso visual. Problemas de carregamento de ator são falhas de implementação a corrigir, não derrotas narrativas.

## 20. Ultra Necrozma — asset confirmado, integração pendente

Consulta realizada em 25/09/2026 ao repositório `MicaelZonta/soulgold`, branch `soulgold-custom`:

| Arquivo | Evidência encontrada | Consequência |
| --- | --- | --- |
| `graphics/pokemon/necrozma/ultra/overworld.png` | Arquivo existe; imagem inspecionada, folha dourada de Ultra Necrozma | Não precisa usar Substitute por ausência deste asset |
| `src/data/pokemon/species_info/gen_7_families.h` | `SPECIES_NECROZMA_ULTRA` possui `sPicTable_NecrozmaUltra`, paletas próprias e `SIZE_32x32` dentro de `#if OW_BATTLE_ONLY_FORMS` | A forma de overworld depende dessa compilação condicional |
| `include/config/overworld.h` | `OW_BATTLE_ONLY_FORMS FALSE` e `OW_SUBSTITUTE_PLACEHOLDER TRUE` | Configuração compatível com ausência da forma compilada e uso de fallback; investigar a seleção real do ator |

Referências: [sprite](https://github.com/MicaelZonta/soulgold/blob/soulgold-custom/graphics/pokemon/necrozma/ultra/overworld.png), [espécie](https://github.com/MicaelZonta/soulgold/blob/soulgold-custom/src/data/pokemon/species_info/gen_7_families.h), [configuração](https://github.com/MicaelZonta/soulgold/blob/soulgold-custom/include/config/overworld.h).

**Limite:** a branch consultada pode diferir da build jogada. Isso identifica um caminho concreto para o problema, mas não prova sozinho qual fallback o evento atual escolheu. Não houve build nem execução da ROM nesta revisão.

**Integração recomendada:** disponibilizar seletivamente o gráfico/paleta de Ultra Necrozma para o ator de cena, ou incluir a forma específica pelo mecanismo adequado, e verificar seu mapeamento. Não habilitar todas as formas de batalha sem avaliar custo de ROM/VRAM. Usar tamanho real 32×32 e espaço de cena suficiente; não trocar automaticamente para 64×64 só porque existe um comentário TODO.

Exigir teste visual: normal → Ultra → retirada, silhueta e paleta corretas, cry de Ultra, sem Substitute, sem Necrozma normal persistindo sobreposto e sem follower falso. A transformação precisa ser legível depois do flash.

## 21. Música, câmera e nomes

| Momento | Contrato |
| --- | --- |
| Ligação/base | Ambiente normal; LOOKER acima da interface telefônica |
| Preparação | Câmera mostra abrigo, marcadores e parceiros antes do uso |
| Três aberturas | Tema de ameaça ativo antes das UBs; cries separados |
| Três comportamentos | Mostrar corte, bloqueio destruído e avanço; evitar explicação longa |
| Mãe/Lusamine | Conversa curta sob cobertura; civis terminam de entrar |
| Menu | ANABEL; nome do rival resolvido corretamente nas falas seguintes |
| Boss | Tema do sistema; retorno restaura ameaça, posição e plaquinha |
| Campo | Filamentos realmente cessam; indicadores mostram tensão antes da falha |
| Necrozma | Aparição prevista pela equipe; contenção tentada antes da absorção |
| Ultra | Flash curto, forma própria visível, instabilidade independente do parceiro |
| Retirada | Caminhos seguros, parceiros visíveis, sem derrota jogável obrigatória |
| Segurança | Ameaça termina após confirmação de fechamento |
| Rescaldo | Mãe volta do abrigo; rival verifica rota; ninguém fala sob caixa que o oculta |

`MUS_DP_LEGEND_APPEARS` permanece proposta de ameaça do arco, sujeita a habilitação e audição no build. A forma Ultra pode intensificar a mesma faixa ou usar transição musical validada, sem cair no tema alegre da cidade enquanto ela está presente. Não inventar constante de música não consultada.

Preservar `fadescreenswapbuffers` para flashes conforme orientação herdada. Reduzir tremores longos repetidos: três aparições distintas e uma transformação legível comunicam escala sem uma sequência contínua de tela branca. Testar dia/noite e restauração de paleta.

**Olhares:** jogador acompanha alvo escolhido, retorna à cena depois de menu/batalha, olha parceiro quando ele aparece e volta à ameaça. Após retirada, acompanha cada interlocutor. NPCs continuam olhando suas frentes ao falar durante combate; não usar `faceplayer` indiscriminadamente.

## 22. Contratos para a reunião e o Altar

A próxima revisão precisa partir destes resultados, sem repetir o roteiro antigo:

- Necrozma identificado desde Blackthorn; Lusamine não guarda esse nome como segredo.
- Nove assinaturas persistentes sustentam o objetivo de recuperar as UBs.
- O campo funcionou brevemente; Necrozma o venceu enquanto continuava alimentando conexões.
- A equipe quer conter Necrozma e resolver a origem da instabilidade, não apenas derrotar as UBs de outra cidade.
- A forma Ultra é poderosa e instável; potência não equivale a controle.
- Dados de Elm, Cherrygrove e Aether permitem localizar a rota durante o intervalo antes da reunião. Anabel não localiza o Altar por um novo superpoder.
- Lusamine aceitou uma tarefa compartilhada e entrega registros. Sua disputa por liderança no Altar deve avançar esse conflito, sem fazê-la esquecer completamente a cooperação daqui.
- A mãe ajudou e se abrigou. Gold/Crystal e Azumarill foram parte competente da defesa.
- Reunião tem chamada diária própria. O estado 10 sozinho não deve disparar a cena longa antes dela.
- Apresentação obrigatória do parceiro, preparação do estabilizador de passagem e Beast Ball de Kurt pertencem à reunião/Altar. Não foram entregues por este encontro.
- New Bark não dá Solgaleo, Necrozma ou item de captura ao jogador. A captura roteirizada de Necrozma continua sendo o clímax posterior.

## 23. Conferência final para implementação

- [ ] Ligação diária, convite persistente e briefing precedem o evento.
- [ ] Sem ataque congelado à mãe enquanto se espera a data da próxima ligação.
- [ ] Elm recebeu solicitação de Kukui e comparou dados; não é tratado como incapaz.
- [ ] Lusamine tem motivo de presença e equipamento apresentado antes do uso.
- [ ] Rival Gold/Crystal usa nome correto em todas as caixas; nunca `NONE` ou Silver.
- [ ] Kartana, Guzzlord e Nihilego têm ações distintas e interação espacial compreensível.
- [ ] Nenhuma regra exige derrotar três criaturas no mesmo segundo.
- [ ] Mãe ajuda, fala pouco com Lusamine e entra no abrigo sob cobertura.
- [ ] Milotic, Snorlax e Azumarill estão visíveis antes de agir.
- [ ] Todas as escolhas de alvo têm frentes, rotas e cobertura coerentes.
- [ ] Campo primeiro interrompe conexões; Necrozma aumenta a pressão antes da ruptura.
- [ ] Ball é da NPC; não captura com sucesso antes de a narrativa dizer que falhou.
- [ ] UBs são absorvidas sem atravessar sólidos em forma corpórea.
- [ ] Ultra usa asset próprio, sem Substitute ou Necrozma normal sobreposto.
- [ ] Instabilidade e retirada existem sem família Cosmog na party.
- [ ] Parceiro aparece, usa identidade correta e é recolhido; não é culpado nem causa única da sobrevivência.
- [ ] Nove padrões são comparados, não apenas contados por memória dos incidentes.
- [ ] Moradores seguros e vitória local reconhecidos; rival não é ridicularizado.
- [ ] Cerca/caixas destruídas têm reparo ou restauração coerente.
- [ ] Retry preserva introdução, libera cura e não consome nova convocação.
- [ ] Estado 10 é concluído após resolução; reunião aguarda chamada própria.
- [ ] Nomes, largura das linhas, posições, música, paletas e objetos testados no build real.

**Entrega:** reconstrução do roteiro e dos contratos de cena. Mapa, atores adicionais, campo de contenção, importação de texto, build e testes em jogo permanecem pendentes.
