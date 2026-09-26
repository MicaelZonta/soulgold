# Mahogany — Necrozma, Xurkitree e Celesteela

**Rift Mission 2 · Roteiro revisado V3 · 25/09/2026**

**Status:** roteiro completo para implementação, com falas finais propostas em inglês. Não descreve alterações já executadas na ROM. Continuidade: planejamento geral aprovado e **Blackthorn revisada V3**, na qual Gladion identifica Necrozma e Anabel observa uma ligação entre as UBs e a ruptura.

Escopo: convocação diária por telefone, briefing em Olivine, encontro em Mahogany, evacuação, duas rodadas de boss, plano de Lillie e Pryce, absorção, reações do parceiro, rescaldo e recuperação. Os números de combate continuam em `MAHOGANY_ULTRABEAST_IMPLEMENTATION.md`.

## 1. O que esta missão acrescenta

**Lillie encontra um modo de interromper a recarga das duas Ultra Beasts. O plano funciona, mas Necrozma as recolhe por outra ligação. Anabel consegue registrar suas assinaturas depois da absorção: pela primeira vez, o grupo tem motivo concreto para acreditar que ainda podem ser recuperadas.**

A vitória do jogador continua importante: impede o avanço sobre a cidade, permite testar a barreira e dá ao grupo tempo para observar a absorção. Necrozma escapar não apaga esses resultados.

Lillie começa com uma hipótese baseada em observação, identifica sua limitação e a melhora. Pryce fornece experiência e execução; não existe apenas para falhar diante de Necrozma. Anabel relaciona o que ocorre às evidências de Blackthorn. Looker mantém pessoas e rotas seguras.

### Vozes

| Personagem | Motivação imediata | Expressão |
| --- | --- | --- |
| Lillie | Ajudar os moradores e entender os Pokémon | Educada, atenta, capaz de decidir; hesita diante de incerteza real, sem pedir desculpas por contribuir |
| Pryce | Manter seu povo protegido e a rua defensável | Poucas palavras, instruções claras, humor seco; respeita Lillie confiando numa tarefa concreta |
| Anabel | Interromper a ligação observada em Blackthorn | Separa dados de hipótese; coordena, presta apoio e registra a descoberta |
| Looker | Concluir a evacuação e ligar as duas ocorrências | Cordial antes da ação; direto durante o perigo; não desqualifica o caderno de Lillie |

**Não repetir:** “ninguém sabe o nome de Necrozma”, “Lillie reconhece, mas se recusa a contar”, circuito infinito, gelo como explicação científica absoluta ou uma criatura revivendo a outra por uma habilidade canônica inexistente.

## 2. Regras de apresentação

1. **Todo diálogo tem o nome acima da message box.** Cada bloco abaixo contém um único falante. A primeira linha representa a plaquinha, não o corpo da mensagem.
2. A plaquinha persiste na paginação e é atualizada após batalha, cura, menu e troca de personagem. Nunca usar `NONE`.
3. Narração, bilhete e notificações usam `NARRATOR`, `NOTE` e `SYSTEM`, respectivamente. Não herdam a identidade do último NPC.
4. Nenhuma ação do parceiro é descrita como se estivesse visível enquanto ele continua na Ball. Solgaleo/Lunala aparece fisicamente nos ramos correspondentes.
5. Todas as pistas essenciais acontecem também sem família Cosmog na equipe.
6. Ninetales permanece ao lado de Lillie antes, durante e depois da cena. Não aparece apenas quando é conveniente usar um golpe.
7. A ameaça mantém sua trilha entre as duas batalhas, durante a cura e na absorção. Música de cidade só retorna quando a rua está segura.
8. O horário não bloqueia o evento. Falas funcionam de dia e à noite; o apagão afeta lâmpadas e equipamentos, não apaga artificialmente o sol.
9. Medir texto na fonte real com nomes expandidos. As quebras abaixo indicam ritmo, não substituem validação de largura.
10. As novas labels dividem falantes e intenções; atualizar as chamadas dos scripts, não apenas substituir strings antigas.

## 3. Espaço de cena — corrigir o aperto de verdade

O roteiro anterior concentra duas UBs grandes, Necrozma, quatro treinadores, dois parceiros e a barreira numa faixa de três tiles de altura. **Esta versão não deve reutilizar aquela formação comprimida.**

### Direção espacial obrigatória

Organizar a ação em três áreas conectadas:

| Área | Ocupantes | Função |
| --- | --- | --- |
| Abrigo, junto ao Ginásio | Pryce, Mamoswine, Hector e neto; depois Looker | Evacuação inicial; não fica lotada durante o combate |
| Rua de confronto | Xurkitree ao norte, Celesteela ao sul, Necrozma a oeste | Duas frentes distintas e ligação visível entre elas |
| Apoio a leste | Jogador, Lillie/Ninetales, Anabel | Escolha dos alvos, cura e recuo; corredor até o Centro |

**Medidas de encenação:** deixar pelo menos três tiles livres entre as âncoras das duas UBs, dois entre a frente de cada criatura e seu treinador e uma faixa de circulação independente para apoio. Conferir também o tamanho visual real dos sprites: âncoras distantes não bastam se a arte se sobrepõe.

O Ginásio e o Centro mantêm acesso e warps. A faixa antiga não comporta toda essa formação vertical. Para implementar esta encenação, ampliar localmente a área caminhável ou remanejar a luta para uma área contígua de Mahogany que comporte essas distâncias. **Não alegar que o problema foi resolvido apenas mudando texto ou reduzindo sprites.**

A ampliação é uma dependência desta coreografia, não um mapa editado nesta entrega. Não fornecer coordenadas supostamente validadas sem ter o layout atual em mãos. Os pontos nomeados abaixo são marcações narrativas, não constantes existentes do motor.

### Marcações para a implementação

| Ponto | Posição relativa |
| --- | --- |
| `ABRIGO` | Porta do Ginásio, com caminho reservado |
| `APOIO` | A leste do conflito, ligado ao Centro |
| `FRENTE_NORTE` | Xurkitree e seu corredor de confronto |
| `FRENTE_SUL` | Celesteela e seu corredor de confronto |
| `VAO_CENTRAL` | Trajeto da energia entre as frentes; recebe a barreira |
| `FLANCO_OESTE` | Necrozma, separado das UBs e sob cobertura de Pryce |
| `PARCEIRO` | Lateral protegida do jogador, sem ocupar a frente de Ninetales |

A câmera tem três enquadramentos: evacuação; confronto; rescaldo. Não exigir que todos apareçam simultaneamente. Looker só entra no enquadramento de combate quando uma ação dele precisa ser vista. Durante textos, os atores relevantes ficam acima da message box.

## 4. Regra da ligação nesta missão

**Regra autoral do hack:** uma ligação energética da ruptura permite transferência entre estas duas UBs. Xurkitree drena a rede; o fluxo passa até Celesteela. Quando uma é enfraquecida, a outra e a energia acumulada na ligação produzem uma única recarga mostrada na cena.

Não é uma troca inesgotável de calor por eletricidade. Ao enviar energia, a fonte perde brilho ou reduz atividade; a ruptura oscila. Não chamar a recuperação de ressurreição nem afirmar que ambas são imortais.

Afastá-las estica o fluxo, mas não o corta. A barreira interrompe **esse trajeto visível**. Isso é testado em cena: Lillie não apresenta uma lei universal sobre gelo e eletricidade.

Necrozma depois cria uma ligação direta por cima/ao redor da barreira. O gelo não some sozinho, e a captura continua sendo o objetivo da equipe. O problema mudou de geometria; o primeiro plano não foi inútil.

## 5. Ato I — Ligação e briefing em Olivine

### Regra de entrada — convocação diária

Depois de concluir Blackthorn, Mahogany aguarda uma ligação do Looker. Usar o dia do calendário do jogo, conforme seu sistema diário/RTC, e não um intervalo de 24 horas. **Se Looker já ligou hoje, ele não liga outra vez hoje. A ligação inicial de Blackthorn também conta.** O limite é compartilhado pelas convocações deste arco.

No primeiro momento seguro de controle livre, chamar se Blackthorn estiver concluída, Mahogany ainda não tiver sido convocada e nenhuma missão anterior estiver pendente. Não interromper batalha, menu, diálogo, transição ou cutscene. Se o jogador estiver dentro da base de Olivine, aguardar sua saída para evitar Looker telefonar diante dele. Não consumir a ligação enquanto o disparo estiver adiado.

Ao terminar a chamada, registrar juntos o dia e a convocação de Mahogany. Esse convite persiste no save até o briefing e não expira ao virar o dia. Não voltar a telefonar para lembrar a mesma missão. Derrota, retorno a Olivine, carregar o save ou trocar de mapa não geram nova convocação. Derrota permite tentar a missão já liberada no mesmo dia.

**Fluxo:** Blackthorn concluída → aguarda ligação elegível → chamada de Mahogany → briefing em Olivine → missão em Mahogany. A ligação não substitui o briefing nem ativa a cena de campo sozinha. Os estados numéricos existentes continuam representando a missão; a convocação exige controle persistente separado, com nomes a definir na implementação.

### `Phone_Text_LookerMahoganyInvite` — identificador proposto

```text
LOOKER
{PLAYER}, it's Looker.
Pryce reported unusual Pokémon in Mahogany.

Meet us at our base in Olivine.
Anabel has compared the readings
with Blackthorn's.
```

Mostrar LOOKER acima de todas as páginas, inclusive se o telefone usar uma janela própria. Tocar o sinal de chamada, concluir a interface e devolver controle. Não usar música de aparição de UB nesta ligação: a ameaça visual pertence à cena de campo.

### Visita a Olivine antes da convocação

#### `OlivineCity_House1_Text_WaitForMahoganyCall`

```text
LOOKER
We're still checking the reports.
I'll call when we have a lead.
```

Essa fala só vale entre Blackthorn concluída e a convocação de Mahogany. Não iniciar o briefing antecipadamente nem falar de um ataque em andamento enquanto o jogador espera o próximo dia.

### Depois da ligação, antes do briefing

Se houver interação de orientação antes do início do briefing:

#### `OlivineCity_House1_Text_MahoganyBriefingReady`

```text
LOOKER
Anabel's ready.
Let's go over the Mahogany report.
```

### Briefing liberado pela ligação

Reaproveitar a aproximação de Looker e Anabel ao jogador na sala. Depois retornam às posições usuais. Lillie não é anunciada: o jogador a encontra ajudando em Mahogany.

### `OlivineCity_House1_Text_BriefingM2Welcome`

```text
LOOKER
{PLAYER}! Our holiday reading
has finally proved useful.

We've compared Gladion's account
with the Alola records.

Necrozma absorbs light. We found nothing
about it taking Ultra Beasts.
```

### `OlivineCity_House1_Text_BriefingM2Link`

```text
ANABEL
The rift kept them connected in Blackthorn.
We need a way to cut that connection.
```

### `OlivineCity_House1_Text_BriefingM2Town`

```text
LOOKER
The power is out in Mahogany.
Two Pokémon have been appearing
in the street.

Pryce is sheltering the residents
in his Gym.
```

### `OlivineCity_House1_Text_BriefingM2Meet`

```text
ANABEL
The readings match another rupture.
We haven't confirmed Necrozma there yet.

Meet us by the Pokémon Center.
```

A informação útil de Blackthorn mudou o plano. Não repetir uma explicação geral de Ultra Wormholes. A confirmação de Necrozma ocorrerá na rua.

### Orientação repetível

#### `OlivineCity_House1_Text_LookerGoAheadM2`

```text
LOOKER
Mahogany's Pokémon Center.
Pryce has kept the road to it clear.
```

#### `OlivineCity_House1_Text_AnabelGoAheadM2`

```text
ANABEL
Prepare for a longer fight.
We may need to change our approach.
```

Não prever duas rodadas como conhecimento dos personagens.

## 6. Ato II — Reencontro em Mahogany

Cidade evacuada, luzes elétricas apagadas, Centro disponível. Se houver som de equipamentos no mapa, interrompê-lo. A ausência de moradores e o contraste do Centro comunicam o problema mesmo sob luz diurna.

### Bilhete nas portas

#### `Mahoganytown_Text_DoorLocked`

```text
NOTE
Shelter is available at the Gym.
Stay off the street.
—Pryce
```

Não dizer “todos estão seguros lá dentro” enquanto Hector e o neto ainda estão na entrada.

### Anabel — opcional

#### `Mahoganytown_Text_UBAnabelIdle`

```text
ANABEL
The Center has backup power.
You can heal there.

Looker is waiting by the road.
```

### Lillie — opcional

Ela reconhece o jogador, se volta para ele e sorri brevemente. Ninetales continua atenta à rua. Após a conversa, Lillie acompanha o olhar da parceira.

#### `Mahoganytown_Text_UBLillieIdle`

```text
LILLIE
{PLAYER}! I'm glad you're here.

I was staying nearby when the lights went out.
Ninetales noticed something in the street.

I've been watching from the Gym window.
I think I've found something useful.
```

Não contar as batalhas anteriores nem reapresentar a viagem a Johto. Se o jogador pular esta interação, a conversa obrigatória também reconhece o reencontro, sem depender dela.

### Ninetales — opcional

Cry curto, olhar para a rua. Não fazê-la sair do lado de Lillie para um movimento que atrapalhe a formação inicial.

#### `Mahoganytown_Text_UBNinetalesIdle`

```text
NARRATOR
Ninetales lifts its ears toward the street.
```

### Pryce — opcional

Pryce está ajudando os últimos moradores. Fala sem abandonar sua posição.

#### `Mahoganytown_Text_UBPryceIdle`

```text
PRYCE
Good. You're here.

I'll have the last two inside shortly.
Speak to the detectives.
```

### Hector — opcional

Usar **HECTOR**, nome já existente na cena original, de forma consistente. Não alternar entre HECTOR, OLD_MAN e ausência de nome nas caixas.

#### `Mahoganytown_Text_UBOldManIdle`

```text
HECTOR
My lamp's still on the porch.
I don't want to leave it out there.
```

### Neto — opcional

Sem inventar nome próprio; plaquinha **BOY** em todas as intervenções.

#### `Mahoganytown_Text_UBBoyIdle`

```text
BOY
Grandpa, we can get it later.
Please come inside.
```

### Mamoswine — opcional

#### `Mahoganytown_Text_UBMamoswineIdle`

```text
NARRATOR
Mamoswine leaves a clear path to the door.
```

Sua posição precisa corresponder à descrição. Remover as antigas reações opcionais à família Cosmog nesta fase: o parceiro será mostrado num único momento próprio, depois das batalhas.

## 7. Ato III — O que Lillie viu

Falar com Looker é o ponto de compromisso. Lillie e Ninetales se aproximam apenas o suficiente para a conversa. Não amontoar todos na entrada do Centro.

### `Mahoganytown_Text_UBLookerGreet`

```text
LOOKER
Lillie has been keeping watch from the Gym.
She saw the two Pokémon before we arrived.
```

### `Mahoganytown_Text_UBLillieGreet`

```text
LILLIE
{PLAYER}, could you help us keep them apart?
I'll show you what I mean.
```

Essa fala funciona tenha ou não ocorrido a conversa opcional. Não repetir uma apresentação.

Lillie abre seu caderno. Câmera acompanha a direção que ela aponta, sem mostrar UBs que ainda não apareceram nesta tentativa.

### `Mahoganytown_Text_UBLillieObservation`

```text
LILLIE
Xurkitree touches the power lines.
Then a light runs across the street
to Celesteela.

Celesteela's engines flare each time.
```

### `Mahoganytown_Text_UBAnabelObservation`

```text
ANABEL
Does the light stay between them?
```

### `Mahoganytown_Text_UBLillieLimit`

```text
LILLIE
For as long as I could see them.
I couldn't follow it back any farther.

If we draw them apart, we might break it.
```

### `Mahoganytown_Text_UBAnabelPlan`

```text
ANABEL
We'll try that.
I'll watch the connection as they move.
```

Lillie oferece uma hipótese; Anabel a transforma em teste. Nenhuma delas conhece ainda a recarga. Looker não questiona sua competência só para que ela precise defendê-la.

### `Mahoganytown_Text_UBReady`

```text
LOOKER
Ready to join them, {PLAYER}?
```

Menu **Yes / No**, nome LOOKER mantido.

### `Mahoganytown_Text_UBNotReady`

```text
LOOKER
Take the time to prepare.
We'll keep the road clear.
```

Ao voltar, repetir apenas a pergunta depois que esta conversa já foi ouvida. Registrar esse fato no estado de preparação da implementação; não repetir todo o caderno em cada interação.

## 8. Ato IV — Terminar a evacuação

**Yes:** controlar a cena, ocultar o follower comum e preparar os atores narrativos. Primeiro enquadramento no Ginásio. Não conduzir o jogador para a linha de combate antes de concluir a retirada dos moradores.

### `Mahoganytown_Text_UBTimeIsClose`

```text
ANABEL
The readings are rising.
Pryce, we need the street clear.
```

### `Mahoganytown_Text_UBPryceEvacuates`

```text
PRYCE
Inside, Hector. Both of you.
```

### `Mahoganytown_Text_UBHectorLamp`

```text
HECTOR
And my lamp?
```

### `Mahoganytown_Text_UBPryceLamp`

```text
PRYCE
I'll fetch it when we're done.
Go on. Your grandson is waiting.
```

O neto entra primeiro, Hector o acompanha. Abrir porta, concluir a travessia de cada um e só depois fechar. Mamoswine mantém livre o acesso. Nenhum morador se teleporta para dentro diante da câmera.

Looker verifica a porta e fica na área de apoio/abrigo, evitando a fila de pessoas atrás do jogador.

### `Mahoganytown_Text_UBLookerEvacuated`

```text
LOOKER
That's everyone.
I'll keep this entrance clear.
```

### `Mahoganytown_Text_UBPryceMeets`

```text
PRYCE
Lillie. Show us where you saw the light.
```

Lillie indica o vão central; Ninetales acompanha. Pryce confia nela sem um discurso sobre idade ou experiência. Mamoswine vai para o flanco oeste, com rota que não atravesse os futuros pontos de surgimento.

## 9. Ato V — A energia atravessa a rua

### Beat 1 — Formação

Mover em ordem: Ninetales/Lillie para a linha de apoio; jogador para sua posição; Anabel para o corredor de apoio; Pryce/Mamoswine para cobertura oeste. Reservar a faixa central para o efeito de energia e a futura barreira.

O jogador e Lillie começam a leste das UBs. A atribuição das frentes acontece depois da escolha. Até lá, ambos têm espaço para avançar sem se cruzar.

### Beat 2 — Necrozma

Anabel interrompe o olhar no instrumento e observa a rua. Tema local sai. Uma abertura estreita surge no flanco oeste; Necrozma emerge. A trilha de ameaça já está ativa antes de sua revelação e permanece para a chegada das UBs.

#### `Mahoganytown_Text_UBNecrozmaArrives`

```text
ANABEL
Necrozma. Pryce, watch the west side.
```

Lillie prende a respiração por um instante, olha para Ninetales e retoma sua postura. Ela pode sentir o peso da lembrança sem interromper a operação.

#### `Mahoganytown_Text_UBLillieRecognizes`

```text
LILLIE
Necrozma...
Ninetales, stay close.
```

#### `Mahoganytown_Text_UBPryceCover`

```text
PRYCE
Mamoswine. Keep it away from the Gym.
```

Mamoswine ocupa a passagem. **Não repetir o ataque ineficaz de Clair:** Pryce começa pela cobertura. Seu confronto com Necrozma terá consequência na absorção.

### Beat 3 — Ruptura e UBs

Necrozma abre mais a passagem. Xurkitree surge na frente norte; Celesteela na sul. Cries separados; pausa breve para distinguir as posições. Nenhum NPC precisa nomear novamente as duas, pois Lillie já o fez.

#### `Mahoganytown_Text_UBAppear`

```text
LILLIE
There. Those are the two I saw.
```

Xurkitree alcança uma representação visível da alimentação elétrica. Uma lâmpada remanescente ou indicador apaga; um fluxo corre dele até Celesteela pelo vão central. Celesteela aumenta a atividade dos motores. A conexão com a ruptura pulsa ao fundo.

**Dependência de arte:** se o mapa não tem fiação desenhada, usar um ponto de alimentação coerente com os tiles do local. Ajustar “power lines” no diálogo para esse objeto real. Não fazer Xurkitree tocar uma fiação invisível.

#### `Mahoganytown_Text_UBSynergyObserved`

```text
LILLIE
That's the light.
It reaches Celesteela every time.
```

#### `Mahoganytown_Text_UBSynergyRead`

```text
ANABEL
I have it. Keep that path in sight.
```

### Beat 4 — Ninetales abre espaço

Celesteela avança pelo corredor sul, aproximando-se da linha do jogador. Lillie vê o movimento e dá a ordem **antes** do golpe.

#### `Mahoganytown_Text_UBSavedOrder`

```text
LILLIE
Ninetales, Icy Wind!
Across the road!
```

Ninetales se coloca num ponto lateral e lança o golpe. Celesteela reduz o avanço; o jogador dá um passo seguro para trás e vira imediatamente para a ameaça. Não tratar um golpe de gelo como arremesso trivial de uma criatura enorme.

#### `Mahoganytown_Text_UBSavedCheck`

```text
LILLIE
Are you all right, {PLAYER}?
```

Gesto breve de confirmação do jogador, sem caixa de resposta. Ninetales retorna ao lado de Lillie, mantendo a faixa central livre.

### Beat 5 — Escolha

#### `Mahoganytown_Text_UBChoosePrompt`

```text
LILLIE
Which one will you take?
Ninetales and I will draw the other away.
```

Menu **Xurkitree / Celesteela**, plaquinha LILLIE. Sem cancelamento após compromisso, conforme fluxo existente. A escolha vale para as duas rodadas da tentativa.

#### `Mahoganytown_Text_UBPickedXurkitree`

```text
LILLIE
We'll take Celesteela.
Ninetales, lead it down this side.
```

#### `Mahoganytown_Text_UBPickedCelesteela`

```text
LILLIE
We'll take Xurkitree.
Ninetales, keep it away from the lines.
```

### Beat 6 — Separação mostrada

| Escolha | Jogador | Lillie/Ninetales |
| --- | --- | --- |
| Xurkitree | Frente norte | Frente sul, contendo Celesteela |
| Celesteela | Frente sul | Frente norte, contendo Xurkitree |

Mover o par NPC primeiro pela faixa de apoio, depois o jogador pelo caminho livre. As UBs se afastam um pouco dentro de seus corredores. **O fluxo se estica, mas permanece:** os personagens ainda não sabem se ele consegue transferir uma recarga a essa distância.

Anabel acompanha a leitura, Looker mantém o abrigo, Pryce impede aproximação de Necrozma. Não reunir os quatro ao lado do jogador para a escolha.

### Beat 7 — Rodada 1

Primeiro boss, curto conforme o balanceamento herdado. Captura bloqueada enquanto há ligação. Não introduzir um novo teste de Ball repetindo Blackthorn.

No retorno, preservar a escolha, a formação e a trilha de ameaça. Desfazer apenas a apresentação da batalha; não resetar a cena por um callback de mapa genérico.

## 10. Ato VI — Afastar não bastou

### Beat 1 — A primeira vitória

A UB do jogador reduz sua atividade e para. A outra continua contida por Ninetales. Lillie olha para o jogador.

#### `Mahoganytown_Text_UBFirstDown`

```text
LILLIE
You've stopped it!
```

O fluxo aumenta. Lillie volta o olhar imediatamente para ele.

#### `Mahoganytown_Text_UBCurrentReturns`

```text
LILLIE
Wait—the light is still reaching it!
```

### Beat 2 — Recarga, com origem e custo

**Jogador escolheu Xurkitree:** Celesteela perde brilho nos motores; a energia acumulada percorre a ligação até Xurkitree. Xurkitree se ergue/reativa, enquanto Celesteela leva um momento para recuperar sua postura. Não desenhar calor se convertendo espontaneamente em eletricidade.

#### `Mahoganytown_Text_UBRevivedXurkitree`

```text
ANABEL
Celesteela's output dropped.
Xurkitree is taking the energy.
```

**Jogador escolheu Celesteela:** Xurkitree envia a carga pelo fluxo; suas extremidades perdem brilho por um instante. Celesteela retoma os motores e a postura de combate.

#### `Mahoganytown_Text_UBRevivedCelesteela`

```text
ANABEL
Xurkitree sent another charge.
Celesteela's engines are restarting.
```

A ruptura oscila nos dois ramos. A segunda luta representa uma criatura recarregada pelo fenômeno; não declarar que todos os danos desapareceram ou que isso poderia repetir infinitamente.

### Beat 3 — Lillie corrige a hipótese

Lillie acompanha visualmente o fluxo inteiro, aponta o trecho central e fala ao grupo. Sem monólogo de culpa.

#### `Mahoganytown_Text_UBLilliePlanCorrection`

```text
LILLIE
I thought the distance would break it.
It didn't.

Mr. Pryce, can Mamoswine put a wall
right across that light?
```

#### `Mahoganytown_Text_UBPrycePlan`

```text
PRYCE
A wall? That we can do.
Keep them clear of the middle.
```

#### `Mahoganytown_Text_UBAnabelWallPlan`

```text
ANABEL
I'll watch for a change.
Looker, keep the way back clear.
```

Não há garantia de sucesso antes do teste. A coragem de Lillie está em agir sobre uma observação melhor, não em inventar uma certeza.

## 11. Ato VII — A barreira e a segunda rodada

### Beat 1 — Criar proteção antes da cura

O gelo precisa ganhar tempo real. Não deixar as UBs soltas enquanto Anabel cura e todos conversam.

#### `Mahoganytown_Text_UBNinetalesCover`

```text
LILLIE
Ninetales, Icy Wind!
Keep them back while Mamoswine moves!
```

Ninetales produz uma faixa de vento e neve entre as frentes e o apoio. A UB que sofreu a recarga ainda retoma o movimento; a outra está reduzida pelo envio de energia. Pryce faz Mamoswine assumir o vão, sem virar as costas a Necrozma: mantém-no no flanco oeste dentro do campo de visão.

#### `Mahoganytown_Text_UBWallOrder`

```text
PRYCE
Mamoswine. Ice across the gap.
```

Mamoswine ergue uma barreira curta e espessa **no trajeto do fluxo**, não na saída dos moradores nem atravessando todas as rotas do jogador. O vento de Ninetales protege sua execução; não usar Aurora Veil como gelo sólido.

### Beat 2 — Teste visível

O fluxo atinge a barreira, se fragmenta e cessa. A UB tenta receber outra carga; a pulsação do seu corpo falha. A câmera precisa mostrar a ligação interrompida e a resposta da criatura antes da conclusão de Anabel.

#### `Mahoganytown_Text_UBWallHolds`

```text
ANABEL
The transfer stopped.
The wall is cutting it off.
```

#### `Mahoganytown_Text_UBLillieWall`

```text
LILLIE
It's working.
Ninetales, stay on this side of it.
```

Sem “agora nunca mais levanta” ou explicação universal sobre propriedades do gelo. A barreira funcionou contra esta conexão.

### Beat 3 — Apoio e cura

Mamoswine mantém o vão e Ninetales cobre a frente; Anabel se aproxima pelo corredor de apoio e o jogador recua para encontrá-la. Nenhum deles atravessa a parede. Necrozma permanece do lado oeste, com Pryce atento.

#### `Mahoganytown_Text_UBAnabelHeals`

```text
ANABEL
Come back here, {PLAYER}.
Let me treat your team.
```

Executar a cura inteira. Se houver fade, ele não altera a posição dos atores nem remove a barreira. Fanfarra curta de cura, depois retorno imediato ao tema de ameaça.

#### `Mahoganytown_Text_UBAnabelHealed`

```text
ANABEL
They're ready.
The connection is still down.
```

Jogador volta à mesma frente escolhida e encara o alvo; Anabel retorna ao apoio. Só então Lillie orienta a continuação.

#### `Mahoganytown_Text_UBSecondRound`

```text
LILLIE
I'll keep the other one here.
Go ahead, {PLAYER}!
```

### Beat 4 — Rodada 2

Mesma UB escolhida, perfil completo previsto no balanceamento. A parede continua sendo a razão de não ocorrer nova recarga narrativa. A batalha não muda os papéis dos parceiros nem introduz um terceiro confronto jogável.

Os valores de barras, nível, item e golpes permanecem no documento técnico; esta revisão não os substitui.

## 12. Ato VIII — Eles aprenderam; Necrozma muda a aproximação

### Beat 1 — Conclusão da frente de Lillie

Ninetales encerra sua contenção com um ataque curto. Ambas as UBs permanecem visíveis, sem desaparecer na vitória. Não é necessário mostrar pose caída se o sprite não a possui.

#### Se o jogador enfrentou Xurkitree: `Mahoganytown_Text_UBLillieFoughtCelesteela`

```text
LILLIE
Celesteela's stopped too.
Ninetales, hold there.
```

#### Se o jogador enfrentou Celesteela: `Mahoganytown_Text_UBLillieFoughtXurkitree`

```text
LILLIE
Xurkitree can't reach the connection.
We've stopped it.
```

### Beat 2 — Tentativa de assegurar as UBs

Anabel avança pelo corredor livre, prepara contenção e olha as duas frentes. Looker mantém o caminho livre. Pryce já vigia Necrozma: não se surpreende com a existência dele.

#### `Mahoganytown_Text_UBSecure`

```text
ANABEL
Keep the barrier up.
We'll try to secure them now.
```

Necrozma muda de posição no flanco oeste e ergue os braços. Pryce vê o movimento.

#### `Mahoganytown_Text_UBPryceIntercept`

```text
PRYCE
Mamoswine, block Necrozma!
```

Mamoswine intercepta seu acesso pelo chão. Necrozma recua/flutua para fora dessa linha, então estende uma nova ligação luminosa **por cima da barreira**, diretamente até as UBs. Mostrar esse desvio antes do arrasto.

#### `Mahoganytown_Text_UBLillieNewLink`

```text
LILLIE
Above the ice!
It's reaching them from above!
```

Pryce acompanha o novo ângulo, enquanto Lillie manda Ninetales interromper a ligação.

#### `Mahoganytown_Text_UBNinetalesIntercept`

```text
LILLIE
Ninetales! Break that light!
```

O ataque cruza o fluxo, mas não o rompe antes que as UBs sejam recolhidas. O grupo reage, porém a transferência direta é mais rápida do que a abordagem de contenção que preparou.

**A parede continua intacta.** Não removê-la para abrir um caminho conveniente para Necrozma. UBs recolhidas pelo fenômeno passam a luz antes de atravessar a barreira; sprites sólidos não caminham através de metatiles bloqueados.

### Beat 3 — Absorção e evidência nova

As duas são puxadas em direção a Necrozma, resistem brevemente ao deslocamento e desaparecem no fluxo. O brilho dele aumenta; em seguida oscila, como em Blackthorn.

Anabel mantém o instrumento apontado para ele, sem interromper a leitura para falar com todos.

#### `Mahoganytown_Text_UBAbsorbedRead`

```text
ANABEL
I still have both signals.
They're moving with Necrozma!
```

#### `Mahoganytown_Text_UBLillieSignals`

```text
LILLIE
Both of them?
```

#### `Mahoganytown_Text_UBAbsorbedConfirm`

```text
ANABEL
Yes. The same patterns as before.
I'm recording them.
```

Uma confirmação curta e perceptível do instrumento acompanha a fala. Não exigir uma interface científica nova; dois indicadores ou sons distintos, usados antes da absorção e repetidos agora, bastam para sustentar a leitura.

Ainda não afirmar que todas as UBs de Blackthorn foram detectadas. Mahogany tem dois sinais reconhecíveis desta ocorrência. A interpretação sobre as anteriores continua sendo hipótese.

## 13. Ato IX — O parceiro do jogador

Reavaliar a equipe após a segunda batalha. Nenhum ramo altera o resultado da missão, a descoberta dos sinais ou a disponibilidade da próxima etapa.

### Sem família Cosmog

Necrozma encara a ruptura. Seu brilho oscila e ele prepara a retirada. Ir ao ato seguinte. Não substituir o parceiro por um Pokémon inexistente na equipe.

### Cosmog ou Cosmoem

A Ball reage; o jogador a segura e o Pokémon aparece no ponto `PARCEIRO`, do lado protegido da barreira. Cry/gesto correspondente à espécie. Cosmoem pode oscilar/flutuar, sem um andar inexistente.

Necrozma vira para ele. Ninetales toma posição lateral de cobertura, sem bloquear a saída do jogador.

#### `Mahoganytown_Text_UBNecrozmaSensesCosmog`

```text
LILLIE
{PLAYER}, keep {STR_VAR_1} beside you.
Ninetales, stay with them.
```

O jogador se orienta para o parceiro e depois para Necrozma. Nenhuma promessa de que a criatura está segura para sempre. Necrozma volta sua atenção à ruptura instável.

### Solgaleo ou Lunala

A Ball abre **antes de qualquer fala**. O parceiro surge no ponto reservado, encara a ruptura e emite seu pulso. A borda estabiliza brevemente. Anabel aproveita esse intervalo para acompanhar os dois sinais já detectados; o ruído entre eles diminui, mas nenhum sai de Necrozma. Quando o parceiro interrompe o pulso e recua para junto do jogador, a oscilação retorna e a leitura fica ruidosa de novo, ainda reconhecível.

Esta é a contribuição nova de Mahogany: estabilizar a passagem melhora a observação, mas **não liberta automaticamente as criaturas absorvidas**. A cena mostra uma associação observada, não uma teoria completa sobre os poderes do parceiro. As assinaturas foram reconhecidas antes de ele aparecer; a possibilidade de sobrevivência permanece obrigatória em todos os ramos.

#### `Mahoganytown_Text_UBNecrozmaSensesLegend`

```text
LILLIE
The opening's steady.
Anabel, can you still see the two signals?
```

A câmera mantém o parceiro e a borda em relação legível. Anabel olha brevemente a ruptura e volta ao instrumento.

#### `Mahoganytown_Text_UBPartnerRead`

```text
ANABEL
More clearly now.
But they're still moving with Necrozma.
```

O parceiro permanece ao lado do jogador depois de interromper o pulso. Não fazer Anabel pedir que se aproxime da abertura para obter mais dados. A oscilação retorna antes de Necrozma partir; ele continua carregando as duas assinaturas. Ninguém conclui que tem medo do parceiro.

#### `Mahoganytown_Text_UBLilliePartnerLimit`

```text
LILLIE
They're still in there...
Stay beside {PLAYER}, {STR_VAR_1}.
```

Sem repetir “como em Blackthorn”: o teste funciona como primeira observação para quem não trouxe o parceiro antes e acrescenta uma consequência para quem trouxe. Não afirmar que o Pokémon tentou conscientemente libertar as UBs, algo que esta cena não demonstra.

### Regras comuns dos ramos

- Mostrar apenas um parceiro; se houver Solgaleo e Lunala, selecionar o primeiro elegível na ordem da equipe e manter essa identidade.
- Usar a espécie real após evolução, com cry, gráfico e aparência corretos.
- Não transformar o Cosmog do jogador em Nebby.
- Não dizer “de novo, como em Blackthorn” sem registrar que esse ramo realmente ocorreu lá. As falas acima não dependem desse histórico opcional.
- Se já havia follower da espécie, ocultar/reutilizar sua representação, nunca duplicá-la.
- O ponto do parceiro não pode coincidir com a barreira, Ninetales, rota de cura ou entrada de Anabel.

## 14. Ato X — A rua volta a respirar

### Beat 1 — Retirada

Necrozma se afasta da linha de Mamoswine e retorna pela abertura. O efeito fecha; Anabel mantém a leitura até o final, sem conseguir prolongar o rastreio depois do fechamento.

#### `Mahoganytown_Text_UBNecrozmaGone`

```text
ANABEL
The opening has closed.
I've lost the signal.
```

Pausa breve. Mamoswine verifica a frente. Ninetales relaxa a postura sem abandonar Lillie.

### Beat 2 — Energia volta

Um indicador/lâmpada volta a funcionar, seguido por outros pontos do mapa. De dia, mostrar os equipamentos; à noite, restaurar também o brilho das lâmpadas. Não trocar diretamente para pleno dia nem aplicar tint noturno várias vezes.

#### `Mahoganytown_Text_UBPowerReturns`

```text
LOOKER
The power's back.
I'll check on everyone inside.
```

Agora encerrar a música de ameaça e retomar o tema local suavemente. Não tocar fanfarra de vitória antes de fechar a ruptura.

O jogador recolhe seu parceiro visivelmente, caso ele tenha aparecido. Ninetales permanece com Lillie. Pryce orienta Mamoswine a abrir uma passagem segura na barreira; mostrar a remoção parcial ou total antes de os atores atravessarem aquele espaço.

### Beat 3 — Pryce e Lillie

Pryce se aproxima da área de apoio, mantendo distância confortável dos demais. O jogador olha para ele. Lillie verifica Ninetales primeiro, depois responde.

#### `Mahoganytown_Text_UBPryceThanks`

```text
PRYCE
That gave us the room we needed.
Good work, both of you.
```

#### `Mahoganytown_Text_UBLillieThanks`

```text
LILLIE
Thank you for trusting us.
I didn't know whether the wall would work.
```

#### `Mahoganytown_Text_UBPryceAnswer`

```text
PRYCE
You saw where to put it.
Mamoswine did the rest.
```

Mamoswine reage discretamente. A fala reconhece observação e cooperação sem uma palestra sobre errar ou aprender.

### Beat 4 — Pagar a pequena promessa

Pryce olha para a entrada do Ginásio e depois para a direção da casa de Hector.

#### `Mahoganytown_Text_UBPryceGoodbye`

```text
PRYCE
I'd better fetch that lamp.
He'll ask before he asks about the town.
```

Pryce e Mamoswine saem juntos por uma rota validada, sem atravessar gelo remanescente ou jogadores. Não reaparecer imediatamente dentro do Ginásio se o texto diz que foi buscar a lâmpada.

Looker conclui sua checagem no abrigo durante essa pequena conversa e retorna antes da discussão da investigação. A primeira saída dos moradores acontece depois de o caminho estar aberto.

## 15. Ato XI — O que ainda pode ser salvo

O grupo está numa formação aberta: jogador, Lillie/Ninetales e Anabel; Looker chega pela lateral do abrigo. Ninguém fala através de outra pessoa. Ajustar olhares a cada troca.

### `Mahoganytown_Text_UBAftermathLooker`

```text
LOOKER
Everyone's all right.
The path is clear.
They're heading home.
```

### `Mahoganytown_Text_UBAftermathLillie`

```text
LILLIE
Those signals you recorded...
Could Xurkitree and Celesteela still be alive?
```

### `Mahoganytown_Text_UBAftermathAnabel`

```text
ANABEL
They could. The patterns stayed distinct
after the two disappeared.

We have a reason to keep looking for them.
```

### `Mahoganytown_Text_UBAftermathBlackthorn`

```text
LOOKER
And perhaps the two from Blackthorn.
I'll compare both recordings.
```

### `Mahoganytown_Text_UBAftermathLillieResolve`

```text
LILLIE
Then we should try to get them out.
I'll help however I can.
```

A decisão emocional vem de Lillie. Ela não exige certeza impossível de Anabel, mas também não aceita que a investigação trate as UBs como objetos já perdidos.

### O plano para a próxima ocorrência

#### `Mahoganytown_Text_UBAftermathNextPlan`

```text
ANABEL
The wall stopped the transfer.
Necrozma reached around it.

Next time, we need to see that move sooner.
```

#### `Mahoganytown_Text_UBAftermathNotes`

```text
LILLIE
I marked when each pulse started.
You can keep these pages.
```

Lillie destaca ou oferece páginas do caderno; Anabel recebe. Não declarar que o caderno substitui os instrumentos: os dois registraram partes diferentes.

#### `Mahoganytown_Text_UBAftermathAcceptNotes`

```text
ANABEL
Thank you. I'll match them to the readings.
```

Essa tarefa prepara Cherrygrove, onde observar o momento e o movimento das criaturas ganhará importância. Não anunciar Kukui nem prever um comportamento específico que ainda não ocorreu.

### Retorno opcional ao parceiro

Apenas se Solgaleo/Lunala apareceu:

#### `Mahoganytown_Text_UBAftermathLegend`

```text
ANABEL
{STR_VAR_1} steadied the opening.
The two signals became clearer,
but stayed with Necrozma.

We still need a way to free them.
```

Apenas se Cosmog/Cosmoem apareceu:

#### `Mahoganytown_Text_UBAftermathCosmog`

```text
LILLIE
Is {STR_VAR_1} all right?
It can rest with Ninetales while we finish.
```

A pergunta refere-se ao que aconteceu. Não afirmar que está visível ou dormindo se já foi recolhido. Não acrescentar uma nova saída da Ball só para repetir um aviso.

## 16. Ato XII — Despedida

### `Mahoganytown_Text_UBHookLooker`

```text
LOOKER
We'll compare the records in Olivine.
I'll call when we have something.

Some rest for you.
Some paperwork for us.
```

### `Mahoganytown_Text_UBHookLillieStay`

```text
LILLIE
I'll stay until the residents are settled.
Then I'll send you anything else I find.
```

A convocação de Cherrygrove depende da conclusão desta missão e do limite diário compartilhado. Se Looker ligou hoje, aguardar outro dia; se a convocação de Mahogany ocorreu em dia anterior e ele ainda não ligou hoje, a próxima chamada pode ocorrer no primeiro momento seguro após o encerramento. Nenhuma ligação interrompe esta despedida ou sua resolução.

Antes da convocação seguinte, a base não oferece o briefing de Cherrygrove:

#### `OlivineCity_House1_Text_WaitForCherrygroveCall`

```text
LOOKER
We're comparing Lillie's notes
with Anabel's recordings.
I'll call when we have a lead.
```

Depois da chamada, liberar o briefing correspondente. Convites não expiram nem repetem nos dias seguintes. A espera representa análise; não anunciar que Cherrygrove já está sob ataque enquanto o calendário bloqueia a chamada. Em saves anteriores à mudança, preservar missões já briefadas/iniciadas sem convocação retroativa; datas de chamadas desconhecidas não devem ser inventadas.

Looker e Anabel se orientam para partir. Lillie se volta ao jogador para uma última fala pessoal, fora do tom de relatório.

### `Mahoganytown_Text_UBLillieGoodbye`

```text
LILLIE
I'm glad we got to battle on the same side.

Next time, I hope it's somewhere quieter.
```

Ninetales encosta ao lado dela; Lillie abaixa a mão para a parceira. Pequeno gesto, sem nova caixa. Há familiaridade construída na campanha, sem citar uma fala antiga ou contar encontros.

### Resolução

Limpar o incidente e chegar ao estado 6 conforme contrato existente. Restaurar moradores, portas, iluminação normal por horário e follower. Remover efeitos, ligação, gelo de evento e atores temporários de ameaça.

Lillie e Ninetales permanecem brevemente junto ao abrigo enquanto o jogador é liberado, correspondendo à promessa de ajudar. A implementação pode manter uma conversa curta de rescaldo enquanto o jogador não sai do mapa; em nova visita, assume-se que concluiu sua tarefa. Não dizer que ficará “mais alguns dias” e removê-la imediatamente no mesmo enquadramento.

#### `Mahoganytown_Text_UBLillieSettling`

```text
LILLIE
They're coming out now.
We'll make sure the path stays clear.

Go and rest, {PLAYER}.
```

Essa presença temporária depende de estado/visibilidade apropriados da versão atual. Não reutilizar cegamente a flag das UBs para ela se essa flag é limpa na resolução.

## 17. Recuperação sem repetir revelações

**Manter a regra de desafio existente:** perder em qualquer rodada reinicia o conjunto das duas batalhas e permite escolher novamente a UB. Esta revisão não transforma a segunda rodada em um checkpoint gratuito.

**Alteração de apresentação:** a introdução longa, evacuação e surpresa da primeira recarga não devem ser narradas outra vez como fatos desconhecidos. O retry precisa guardar que o grupo já viu esse comportamento. Os IDs e estados necessários serão definidos na implementação; não são declarados como existentes aqui.

### Retorno após derrota

#### `Mahoganytown_Text_UBRetryGreeting`

```text
LOOKER
We've kept them away from the Gym.
The Center is ready for you.
```

#### `Mahoganytown_Text_UBRetryLillie`

```text
LILLIE
Ninetales and I can try again.
Are your Pokémon ready?
```

Menu Yes/No, LILLIE.

#### `Mahoganytown_Text_UBRetryNotReady`

```text
LILLIE
Take care of them first.
We'll stay here.
```

### Retry da primeira rodada

**Se a derrota ocorreu antes de a recarga ser vista:** retomar a escolha e o plano inicial de afastamento. A recarga e sua discussão ainda são novas e usam as falas da primeira execução. Não usar as falas abaixo antes desse ponto.

**Se o grupo já presenciou a recarga:** usar o plano abreviado abaixo. A implementação deve distinguir esses casos, além de guardar a apresentação inicial já concluída.

O grupo sabe que a ligação existe. As UBs ainda carregadas impedem Mamoswine de ocupar o vão com segurança; a primeira luta volta a abrir essa janela. Assim, não repetir conscientemente um plano que já se sabe incompleto sem motivo.

#### `Mahoganytown_Text_UBRetryPlan`

```text
ANABEL
We need to slow one down
before Mamoswine can reach the gap.

Choose your target.
```

Executar a escolha e primeira batalha. Na recarga, usar:

#### `Mahoganytown_Text_UBRetryRecharge`

```text
LILLIE
It's sending the charge.
Mr. Pryce, now!
```

Mostrar novamente barreira, proteção e cura; eliminar a longa discussão de descoberta. Segunda rodada normal.

### Falha depois da primeira barreira

A barreira continua bloqueando a transferência de energia. A derrota tira a pressão sobre a UB enfrentada pelo jogador, que consegue atacar fisicamente o gelo enquanto a equipe cobre a retirada.

- **Contra Xurkitree:** mostrar seus membros golpeando a base da parede; surgem rachaduras e um trecho cai. Não usar descarga elétrica atravessando gelo intacto.
- **Contra Celesteela:** mostrar um avanço curto de seu corpo contra a borda da parede; um trecho cai. Não precisar de um golpe de batalha ou animação de voo nova.

Só depois da abertura física a ligação volta a atravessar o vão. Mamoswine acompanha a retirada para impedir o avanço ao Centro; por isso terá de retomar sua posição no retry. Não quebrar a parede antes de a derrota ser confirmada, nem executar movimentos enquanto o motor ainda resolve o blackout.

Se a recuperação do motor não permite um corte antes do blackout, mostrar essa consequência numa curta retomada do mapa antes da nova tentativa: o dano se completa à vista, sem repetir a emergência inicial. Uma transição não deve ressuscitar atores já removidos ou reabrir a missão concluída. Ninguém afirma que as UBs escaparam se continuam na rua.

### Resultado não resolvido sem blackout

#### `Mahoganytown_Text_UBUnresolved`

```text
ANABEL
The street isn't clear yet.
Regroup before we move in again.
```

Fuga, interrupção e outros resultados reais do motor não acionam absorção, descoberta final ou conclusão. A implementação deve distinguir resultado inesperado de derrota normal, preservando recuperação segura.

## 18. Áudio, direção de olhar e recursos visuais

| Momento | Regra |
| --- | --- |
| Antes da operação | Apagão mostrado por equipamentos e população, compatível com dia/noite |
| Necrozma emerge | Tema local sai; ameaça começa antes da aparição completa |
| UBs surgem | Manter ameaça, cries separados e espaço para ler silhuetas |
| Energia circula | Efeito direcional no trajeto, sem depender só de flash geral |
| Retorno de ambas as batalhas | Tema de ameaça, mesmas frentes, nome do próximo falante reestabelecido |
| Barreira interrompe energia | Fluxo realmente cessa; efeito persistente até a absorção |
| Cura | Som/fanfarra breve; retomar ameaça, não música de cidade |
| Absorção | Ligação nova por cima do gelo e sinais separados no instrumento |
| Saída de Necrozma | Fechar passagem antes de retomar ambiente local |
| Moradores retornam | Caminho desobstruído e gelo removido visualmente |

`MUS_DP_LEGEND_APPEARS` é a proposta de tema de ameaça herdada da revisão de Blackthorn; confirmar faixa habilitada e resultado sonoro na ROM. Manter o tema de boss já definido pelo sistema.

Preservar a orientação herdada de `fadescreenswapbuffers` nos flashes, evitando recompor repetidamente tint de horário. Não descrever isso como correção já executada.

**Olhares explícitos:** jogador retorna ao alvo após o recuo de Celesteela; volta à frente após a cura; acompanha Pryce e depois Anabel no rescaldo. Lillie olha o fluxo ao corrigir a hipótese e Pryce ao pedir a barreira. Nenhuma dessas direções deve depender de um `faceplayer` genérico aplicado durante cena automática.

## 19. Alterações que o documento de implementação deve receber

| Aspecto | Contrato desta revisão |
| --- | --- |
| Convocação | Ligação diária compartilhada, convite persistente e briefing obrigatório antes da missão |
| Continuidade | Necrozma já identificado; registros de Blackthorn e hipótese da ligação conhecidos |
| Espaço | Formação distribuída, três áreas e enquadramentos; ampliar área útil quando necessário |
| Surpresa de Lillie | Reencontro no mapa, sem anúncio no briefing e sem tratá-la como desconhecida |
| Energia | Transferência visível com origem/custo; retirar explicações de ciclo infinito |
| Primeira rodada | Vitória seguida de uma recarga narrativa, preservando a escolha |
| Segunda estratégia | Vento de Ninetales cobre Mamoswine; barreira corta fluxo; evidência antecede conclusão |
| Cura | Só acontece sob cobertura e com caminho livre |
| Necrozma | Recolhe por ligação diferente, acima do gelo; equipe tenta impedir |
| Descoberta | Duas assinaturas reconhecíveis persistem após absorção; sobrevivência é hipótese sustentada |
| Parceiro | Ator real; estabilização melhora leitura sem libertar as UBs; descoberta básica independente da party |
| Retry | Duas rodadas continuam necessárias, mas texto reconhece aprendizado anterior |
| Pós-cena | Lillie termina de ajudar no abrigo; não desaparecer contradizendo a fala |
| Nomes | Um falante por bloco; plaquinha em todos os ramos e helpers |
| Cherrygrove | Herdar registros e tentativa de prever a intervenção; não repetir identificação de Necrozma |

A formação espacial antiga, seus movimentos por coordenadas e o `warpsilent` que removia todo o elenco imediatamente **não são reaplicáveis sem revisão**. Este roteiro fornece a sequência e as relações espaciais; a tradução para coordenadas depende do mapa real ajustado.

## 20. Conferência antes de considerar a cena pronta

- [ ] Despedidas orientam esperar ligação; base não adianta o próximo briefing.
- [ ] Briefing menciona Pryce explicitamente, mesmo se o telefone foi ouvido em outro dia.
- [ ] Barreira no retry rompe por impacto físico; corrente retorna somente depois.
- [ ] Solgaleo/Lunala melhora a leitura, mas não liberta as UBs; nenhum ramo opcional anterior é presumido.
- [ ] Looker mantém humor fora da emergência; Pryce demonstra confiança sem discurso longo.
- [ ] Ligação de Blackthorn bloqueia outra convocação no mesmo dia.
- [ ] Mahogany recebe uma única chamada, com LOOKER em todas as páginas.
- [ ] Sem chamada, visitar Olivine ou Mahogany não inicia a próxima missão.
- [ ] Convite persiste entre dias e saves; derrota não exige nova ligação.
- [ ] Encerrar Mahogany não dispara Cherrygrove se Looker já ligou nesse dia.
- [ ] Briefing reconhece o avanço de Blackthorn V3.
- [ ] Nenhum personagem esconde o nome de Necrozma ou promete contar informação essencial depois.
- [ ] Lillie é gentil e firme; seu erro leva a uma observação melhor, sem autodepreciação.
- [ ] Pryce ajuda a executar a solução e cumpre o pequeno compromisso com Hector.
- [ ] Looker realiza evacuação/apoio, sem ocupar inutilmente a formação de combate.
- [ ] Formação tem espaço real, inclusive para Celesteela, Mamoswine, Ninetales e parceiro.
- [ ] Jogador vê a ligação, a recarga, a falha contra o gelo e o novo ângulo da absorção.
- [ ] Ambas as escolhas funcionam nas duas rodadas e no retry.
- [ ] A cura tem cobertura e retorna à música correta.
- [ ] Parede não desaparece sem ação nem é atravessada por atores sólidos.
- [ ] Os dois sinais persistentes são mostrados antes da hipótese de sobrevivência.
- [ ] A pista obrigatória independe da família Cosmog na party.
- [ ] Solgaleo/Lunala sai da Ball antes de sua ação; sem cópia do follower.
- [ ] Texto não presume o ramo opcional de Blackthorn.
- [ ] Todos os diálogos têm plaquinha, incluindo Hector, menino, menus e recuperação.
- [ ] Olhares se restabelecem após recuo, cura, batalha e movimento de câmera.
- [ ] Dia e noite preservam legibilidade; nenhum “tonight” contradiz horário livre.
- [ ] Estado 6 só é alcançado após vitória da segunda rodada e resolução da cena.
- [ ] Lillie/Ninetales permanecem coerentes com a despedida antes de sumirem numa visita futura.
- [ ] Próxima revisão de Cherrygrove recebe os registros e o objetivo de antecipar a intervenção.

## 21. Fechamento da auditoria V3

Integrados: telefonema e despedida compatíveis com o limite diário; espera na base antes de Cherrygrove; referente explícito a Pryce no briefing; humor breve de Looker e segurança de Pryce; consequência própria para a estabilização do parceiro; barreira rompida por impacto físico exclusivamente na recuperação de derrota; orientação de Ninetales preservando a frente até a absorção; moradores saindo por passagem já aberta.

O espaço ampliado continua como requisito de mapa, com três enquadramentos e corredores independentes. Não substituir essa revisão espacial por ajustes apenas de texto. Efeitos de energia, barreira, saída da Ball, áudio e nomes precisam ser conferidos na versão jogável.

**Entrega:** roteiro reescrito, falas e encenação. Mapa, importação dos textos, efeitos, build e testes em jogo permanecem pendentes.
