# Pré-Necrozma — a reunião de Olivine

**Roteiro reconstruído V2 · 25/09/2026**

**Status:** proposta de substituição integral do roteiro anexado. Falas em inglês; direção e contratos em português. Nenhuma alteração na ROM, compilação ou validação em jogo foi feita nesta revisão. Os identificadores abaixo são nomes propostos para integração em `data/maps/OlivineCity_House1/scripts.pory`, não símbolos confirmados no código atual.

**Continuidade:** New Bark V2 e planejamento narrativo atualizado de Blackthorn ao Altar prevalecem sobre as falas antigas. Esta cena começa depois da convocação diária, acontece inteira na base e termina com a liberação da viagem. O duelo com Lusamine, a travessia e a batalha de Necrozma pertencem ao roteiro do Altar.

## 1. O que acontece nesta versão

Looker mostra onde a investigação chegou. Kukui explica por que Necrozma continua abrindo rupturas. Lillie exige que o resgate das UBs faça parte da operação. Lusamine oferece registros e equipamento, mas ainda quer comandar a travessia. Gladion exige uma saída concreta. Anabel transforma essas contribuições num plano de captura e retorno.

O parceiro do jogador encerra a discussão abstrata: aparece e participa de um teste curto. O equipamento responde, mas tem limite. A equipe pode seguir para o Altar; ainda precisa verificar a passagem real antes de decidir quem lidera.

**Tom:** reunião de pessoas que trabalharam nas mesmas ocorrências, não seis discursos de despedida. Ninguém precisa recapitular a própria biografia. Humor pontual, conflito sobre decisões e carinho em gestos pequenos.

## 2. Entrada, ligação e estados

Preservar a chamada prevista no fim de New Bark; não criar uma segunda convocação para o mesmo encontro.

### `Phone_Text_LookerAltarInvite`

```text
LOOKER
{PLAYER}, everyone's here in Olivine.
We have a route to Necrozma.

Meet us at the base.
We need you for the plan.
```

**Condição:** New Bark concluída, convite ainda não emitido e nenhuma convocação de Looker concluída na data corrente do calendário do jogo. Adiar durante batalha, menu, diálogo, transição ou dentro da base; registrar data e convite juntos quando a chamada terminar. Convite persiste entre dias e saves. Não mandar lembretes automáticos.

| Situação | Comportamento |
| --- | --- |
| Estado 10, sem convite | Base acessível; reunião não começa; visitantes ainda não reunidos |
| Estado 10, com convite | Elenco reunido; chegada inicia a cena principal uma vez |
| Estado 11 | Reunião ouvida; preparação pendente; apenas retomada curta |
| Estado 12–15 | Passe e acesso já liberados; orientação para o porto |
| Estado ≥16 | Diálogos familiares nos dias previstos; Looker e Anabel no Altar |

Estados são os contratos herdados do anexo. Conferir a integração atual antes de codificar. Convite e registro diário são dados separados do estado narrativo; não inventar endereços livres de flags/vars.

### `OlivineCity_House1_Text_WaitForAltarCall`

```text
LOOKER
We're comparing the records
and arranging the meeting.
I'll call when everyone's ready.
```

Saves antigos com reunião iniciada ou Altar liberado preservam o progresso. Não exigir chamada retroativa nem inventar data histórica. Não há outra ligação ou espera diária entre esta reunião e o Altar.

## 3. Sala e direção

Manter inicialmente a disposição herdada, sujeita à conferência no mapa real:

| Ator/elemento | Posição inicial | Função visual |
| --- | --- | --- |
| Looker | (4,5) | Próximo ao mapa de investigação sobre a mesa |
| Anabel | (7,5) | Ao lado do equipamento |
| Lillie / Ninetales | (3,6) / (2,6) | Juntas, à esquerda |
| Gladion / Silvally | (3,7) / (2,7) | Juntos, abaixo de Lillie |
| Lusamine | (9,6) | Diante dos filhos, do outro lado da sala |
| Kukui | (8,7) | Próximo ao estojo do estabilizador |
| Jogador | Entrada (4,8), depois (4,7) | Fora do warp durante a reunião e ao recuperar controle |
| Mesa sólida | (5–6,4–5) | Mapa e representação simples do equipamento |

**Mudança de coreografia:** Looker e Anabel permanecem junto à mesa. Cortar os dois avanços antigos até a porta; o jogador entra um tile. Assim, a cena se organiza em torno do plano e deixa o centro disponível para apresentar o parceiro.

O espaço próximo de (5–6,6–7) é candidato para o parceiro, não coordenada validada. Conferir tamanho do sprite, colisão e sobreposição com mesa/caixa de texto. Se necessário, reposicionar elenco antes de iniciar; não colocar um Solgaleo sobre a mesa nem atravessar objetos sólidos.

Ocultar o follower somente durante a cena, preservando seu estado para restauração. Ninetales e Silvally permanecem visíveis. O parceiro apresentado é uma instância de cena do Pokémon escolhido da equipe, sem duplicar o follower.

**Câmera:** enquadramento estável da sala; movimentos de olhar marcam as trocas. Música discreta de preparação, pausa curta no teste e retomada após o resultado. Sem tremores, alarme ou tema de batalha. Cada bloco tem um único falante identificado. Quebrar as linhas conforme a fonte real na implementação.

## 4. Cena principal — o destino e o problema

Looker se vira para o jogador. Após a primeira fala, indica o mapa na mesa. Basta gesto e marca visível; não é necessária uma nova interface.

### `OlivineCity_House1_Text_ReunionOpen`

```text
LOOKER
Good. We're all here.

Elm's readings narrowed the search.
Aether's charts gave us a landing point.
The ship can reach this altar.
```

**Base da conclusão:** os registros comparados durante o intervalo apontam para a região; os mapas fornecidos por Lusamine identificam acesso físico ao Altar. A rota de barco é até o Altar em Johto. A passagem para o outro lado ainda será aberta e verificada lá. Não afirmar que uma direção de bússola revelou sozinha o destino de um portal.

Kukui indica dois momentos do registro: pico após absorção e oscilação posterior. Usar uma animação simples do indicador já previsto, sem exigir leitura de números pelo jogador.

### `OlivineCity_House1_Text_ReunionKukui`

```text
KUKUI
See that spike? More power.
Then it starts flickering again.

Nine Pokémon, and Necrozma still
can't hold that light steady.
```

Lillie se volta para Lusamine. Não olha para o chão nem pede licença para falar.

### `OlivineCity_House1_Text_ReunionLillie`

```text
LILLIE
Elm could still detect all nine.
We need to get them out.

Mother, can your equipment do that?
```

### `OlivineCity_House1_Text_ReunionLusamineEvidence`

```text
LUSAMINE
Not while Necrozma keeps drawing them in.
We saw that in New Bark.

We'll have to weaken it first.
Then try to separate them.
```

Lusamine responde à pergunta da filha com o limite do próprio equipamento. Não promete que as UBs estão ilesas e não transforma a tentativa de separação numa certeza. O Altar demonstrará como a libertação ocorre.

## 5. Cena principal — uma saída de verdade

Gladion olha para o estojo ainda fechado, depois para Anabel.

### `OlivineCity_House1_Text_ReunionGladionPlan`

```text
GLADION
And if the passage closes behind us?
```

Lusamine abre o estojo. Mostrar uma base e um módulo portátil reconhecíveis como partes do mesmo conjunto; reutilizar gráficos adequados ou preparar assets simples. Não entregar item ao inventário.

### `OlivineCity_House1_Text_ReunionStabilizer`

```text
LUSAMINE
This holds an open passage steady.
One unit on each side.

It cannot open one. And someone
must keep both units running.
```

Anabel assume o módulo portátil. Lusamine permanece junto à base externa.

### `OlivineCity_House1_Text_ReunionAnabelReturn`

```text
ANABEL
I'll take the portable unit.
If its signal drops, we withdraw.

We test the connection at the altar
before anyone crosses.
```

**Limite do recurso:** estabilizador ficcional do hack, de operação contínua e duração limitada. Sustenta uma passagem aberta; não substitui o parceiro, não transporta sozinho e não garante retorno sob qualquer condição. A unidade de dentro ocupará Anabel na batalha; a base externa precisa de operador e apoio.

### `OlivineCity_House1_Text_ReunionCapture`

```text
ANABEL
Once the others are free,
we capture Necrozma.

I have a Beast Ball from Kurt ready.
Driving it away only moves the danger.
```

Anabel mostra a Ball e a guarda. **Ela permanece com Anabel até a captura roteirizada no Altar.** Não exigir crafting, compra, nível de receita ou item do jogador. Não dizer que Necrozma é uma Ultra Beast nem prometer um bônus canônico da Ball contra ele. A captura garantida posterior é regra autoral do evento.

Lusamine se volta para o mapa, como quem já organiza a próxima etapa.

### `OlivineCity_House1_Text_ReunionLusamineCross`

```text
LUSAMINE
Then I'll lead the crossing.
I know Aether's equipment best.
```

### `OlivineCity_House1_Text_ReunionLillieBoundary`

```text
LILLIE
Then show us how to use it, Mother.
We can't all depend on you alone.
```

Pausa curta. Lusamine olha para Lillie, depois indica o controle do módulo na mão de Anabel.

### `OlivineCity_House1_Text_ReunionLusamineControl`

```text
LUSAMINE
The lower dial. Keep the two lights level.
```

### `OlivineCity_House1_Text_ReunionAnabelLeadership`

```text
ANABEL
We'll decide who leads at the altar.
First, let's see whether this works.
```

**Progresso familiar:** Lusamine compartilha o controle porque Lillie pediu algo concreto. Não pede perdão em nome de toda a história, não recebe absolvição e não aceita antecipadamente ficar fora da travessia. O desacordo do Altar continua disponível, mas deverá partir desse progresso.

## 6. Apresentação do parceiro — uma pergunta clara

Até aqui, a cena principal acontece uma única vez. Antes de devolver controle por falta do parceiro ou adiamento, registrar estado 11. O teste e o passe ficam pendentes; não repetir a discussão.

### `OlivineCity_House1_Text_ReunionAsk`

```text
KUKUI
Now we need your partner, {PLAYER}.
Solgaleo or Lunala can open the way.

Let's check the equipment's response.
```

**Elegibilidade:** procurar Solgaleo e Lunala na equipe, nunca apenas a família ou a Pokédex. Cosmog/Cosmoem não bastam. Se ambos estiverem presentes, menu identificado como `SYSTEM`: `Solgaleo / Lunala / Not now`. Com um, usá-lo. Não exigir procedência específica do ovo; a espécie habilita o fluxo conforme o contrato anterior.

### `OlivineCity_House1_Text_ReunionDeferred`

```text
KUKUI
Sure. Speak to Looker when you're ready.
```

### Ausente da equipe, mas Solgaleo/Lunala encontrado no PC

`OlivineCity_House1_Text_ReunionStored`

```text
LOOKER
Bring Solgaleo or Lunala from the PC.
We need your partner here for the test.
```

### Sem forma final disponível; Cosmog/Cosmoem confirmado na equipe ou no PC

`OlivineCity_House1_Text_ReunionUnevolved`

```text
KUKUI
Your partner needs to evolve first.
Bring Solgaleo or Lunala when it's ready.
```

### Nenhum membro da família encontrado

`OlivineCity_House1_Text_ReunionMissing`

```text
LOOKER
We'll need Solgaleo or Lunala
in your team before we can leave.
```

Essa última fala não afirma crescimento, perda, troca ou liberação sem evidência. Se existe no save um ovo identificável do evento, ele pode usar a orientação de evolução; ovo genérico não comprova essa origem.

**Integração:** consulta ao PC é somente leitura e serve para escolher a orientação, nunca para liberar o teste. Se não existir helper apropriado, implementar a consulta ou usar a fala neutra até integrá-la. Não fingir que uma checagem apenas de equipe distingue os casos.

### Retomada no estado 11 — `OlivineCity_House1_Text_ReunionResume`

```text
LOOKER
Ready to try the equipment
with your partner?
```

Menu `SYSTEM`: `Yes / Not yet`. `Yes` repete somente a elegibilidade e segue ao teste; `Not yet` devolve controle. Entrar na casa no estado 11 não inicia diálogo automaticamente. Looker e Anabel oferecem a retomada ao conversar.

## 7. O teste — mostrar antes de explicar

1. Abrir espaço seguro no centro. Jogador se volta para ele e solta o Pokémon selecionado. Mostrar sprite correto e cry uma vez.
2. Anabel ativa o modo de calibração do módulo; duas luzes do instrumento piscam fora de ritmo. Kukui acompanha o indicador. **Não há fenda na sala.**
3. O parceiro se volta para o módulo e emite um brilho breve. As luzes se alinham por alguns instantes.
4. Anabel encerra o teste. As luzes apagam normalmente, sem explosão ou falha dramática. O resultado é compatibilidade e resposta breve, não prova de uma travessia segura.

### `OlivineCity_House1_Text_ReunionTestStart`

```text
ANABEL
Ready. Just a short pulse.
```

### `OlivineCity_House1_Text_ReunionTestResult`

```text
KUKUI
There! Both lights together.

The equipment can follow your partner.
Now we test it on a real passage.
```

**Sem dependência de cenas opcionais:** usar esse resultado em todos os saves. Não dizer que o grupo já viu o parceiro estabilizar rupturas se isso não foi registrado. Também não atribuir ao teste de bancada uma demonstração que só pode ocorrer no Altar.

Gladion olha para o parceiro; Silvally se vira na mesma direção.

### `OlivineCity_House1_Text_ReunionGladionPartner`

```text
GLADION
...You've looked after it.
Good.
```

**Callback opcional, somente com procedência verificável:** substituir a primeira frase por `Hard to believe I carried that egg.` se o Pokémon apresentado puder ser identificado como o do evento de Violet. Não testar apenas se o jogador recebeu o ovo; ele pode estar apresentando outro exemplar. A versão padrão preserva o reconhecimento de Gladion sem inventar uma fala antiga nem uma origem não verificada.

Lillie sorri/usa reação breve, Ninetales se volta para o parceiro. Sem uma rodada de elogios de cada personagem. Lusamine observa o instrumento e recolhe a base apenas depois de Anabel desligar o módulo.

## 8. Fechamento — trabalho distribuído e passe

### `OlivineCity_House1_Text_ReunionAssignments`

```text
ANABEL
Gladion, keep the exit clear.
Lillie, help the Pokémon we bring back.

Professor, check the outside unit
with Lusamine when we arrive.
```

Funções futuras: jogador enfrenta e captura; parceiro abre e sustenta a rota durante os ajustes; Anabel opera por dentro; Gladion/Silvally cobrem saída; Lillie/Ninetales recebem UBs; Kukui acompanha medições; Looker cuida de transporte, comunicação e recuperação. Lusamine aprende a aceitar a operação externa no Altar. Aqui ela apenas prepara e verifica a base com Kukui.

### `OlivineCity_House1_Text_ReunionTicket`

```text
LOOKER
The ship is ready at Olivine Port.
Show the sailor this pass.
```

Entregar `ITEM_SUN_MOON_TICKET` pelo helper adequado. Mensagem de obtenção e fanfarra normais identificadas como `SYSTEM`. Não substituir o texto do helper por uma segunda mensagem redundante.

### `OlivineCity_House1_Text_ReunionTicketUse`

```text
LOOKER
He'll take you to the altar and back.
Heal your team, and bring your partner.
```

**Transição:** recolher parceiro de cena; fade curto; quatro visitantes humanos e seus dois Pokémon seguem para os preparativos da viagem. Looker e Anabel permanecem na base até o estágio de deslocamento já previsto pelo projeto. Não dizer que todos já foram e deixar dois deles visíveis.

Confirmada a posse do passe, definir `FLAG_EVENT_NECROZMA_ALTAR_UNLOCKED` e estado 12. Restaurar jogador em (4,7), orientação apropriada, sem ocupar o warp. Restaurar follower e controle uma vez.

**Entrega idempotente:** se o passe já existe, não duplicar. Se o helper falhar, não liberar estado 12 como se tivesse entregue; preservar preparação concluída e permitir retomada só da entrega. Usar suporte existente ou prever um marcador específico de teste concluído, sem atribuir ID fictício. Não afirmar que item-chave nunca pode falhar sem conferir o helper.

## 9. Conversas opcionais — preparação no estado 11

São alternativas curtas para quem explora a sala. Não fazem parte da cena principal nem carregam informação indispensável ausente dela.

### Lusamine — `OlivineCity_House1_Text_IdleLusamine`

```text
LUSAMINE
Lillie's notes were useful.
She recorded when the light changed.

I should have asked to see them sooner.
```

### Lillie — `OlivineCity_House1_Text_IdleLillie`

```text
LILLIE
Mother asked for my notes.
Then she actually read them.

I'd like that to happen more often.
```

### Gladion — `OlivineCity_House1_Text_IdleGladion`

```text
GLADION
She showed Anabel the controls.
That's a start.

I'm still watching the exit.
```

### Kukui — `OlivineCity_House1_Text_IdleKukui`

```text
KUKUI
I had a boat booked for Alola.
Looker's going to owe me a new ticket.

Don't tell him I said that.
```

Ninetales e Silvally: interação opcional de cry voltado ao jogador, sem diálogo humano ou cura nova. Se mantiverem `script: NULL`, a cena continua completa. O grafo de visibilidade acompanha os respectivos treinadores.

## 10. Depois do passe — orientação repetível

### Looker — `OlivineCity_House1_Text_LookerAltar`

```text
LOOKER
Show your pass to the sailor
at Olivine Port.
The ship makes the return trip too.
```

### Anabel — `OlivineCity_House1_Text_AnabelAltar`

```text
ANABEL
Bring Solgaleo or Lunala.
We'll check the passage at the altar.
```

Liberar a viagem é persistente. Guardar o parceiro depois da reunião não apaga o passe ou repete a cena; o Altar revalida a equipe antes da ação que depende dele. A travessia exige rechecagem operacional, não outro dia de espera.

## 11. A casa depois do arco — estado ≥16

Aplicar nos dois dias semanais já previstos para a família. Conferir quais são no código; não escolher dias novos nesta revisão. Looker e Anabel atuam no Altar. Nos outros dias, usar o comportamento já definido para a casa, sem ressuscitar o briefing.

**Direção:** aproximar Lusamine da mesa e dos filhos, sem transformar todos numa fileira abraçada. Manter Ninetales e Silvally em tiles reais e acessíveis. Nenhuma fala descreve Silvally deitado sob a mesa sólida se o sprite continua parado longe dela.

### Lusamine — `OlivineCity_House1_Text_HouseLusaminePost`

```text
LUSAMINE
Lillie chose tea for this afternoon.
I had planned something more elaborate.

...Tea will do.
Would you like some?
```

### Lillie — `OlivineCity_House1_Text_HouseLilliePost`

```text
LILLIE
We meet here twice a week.
Mother tried to make an agenda.

Gladion put it under the teapot.
```

### Gladion — `OlivineCity_House1_Text_HouseGladionPost`

```text
GLADION
It was wobbling.

...I'm staying for another cup.
```

Representar bule na mesa se viável; a folha sob ele pode ficar apenas sugerida. Gladion permanece próximo da família por escolha. Esse é o fechamento: convivência pequena, ainda imperfeita, sem um discurso sobre estar aprendendo a conviver.

## 12. O que foi corrigido e por quê

| Problema anterior | Decisão nesta versão | Ganho |
| --- | --- | --- |
| Relatório fechado e cidade tratada como derrota total | Investigação produz rota; objetivo segue ativo | Respeita a defesa bem-sucedida dos moradores em New Bark |
| “Três ferramentas erradas” substituía explicação | Leituras delimitam área; cartas de Aether dão acesso | O destino decorre de trabalho feito entre missões |
| Lusamine se dizia única com experiência do outro lado | Oferece conhecimento específico do equipamento | Remove contradição com Anabel e evita autoridade inventada |
| Família dizia o que sentia em abstrações | Lillie pede os controles; Lusamine ensina | A relação muda por uma ação observável |
| Gladion apenas encerrava a conversa familiar | Pergunta como voltar e assume cobertura | Proteção vira responsabilidade concreta |
| “Voltaremos” funcionava como todo o plano | Duas unidades, operadores, teste e critério de retirada | Prepara a função de Anabel no clímax sem garantia impossível |
| Parceiro só era reconhecido por falas | Sprite, pulso e resposta do equipamento | Jogador vê sua contribuição e seu limite |
| Todos elogiavam o parceiro em sequência | Reação curta de Gladion e gestos dos demais | Evita o mesmo ponto repetido por quatro vozes |
| Ausência na equipe significava “ainda crescendo” | Ramos de PC, evolução e ausência desconhecida | A orientação corresponde ao que foi verificado |
| Beast Ball surgia tarde na solução | Anabel mostra a reserva de Kurt antes da viagem | Captura integra o plano, sem exigir crafting |
| Estado 10 iniciava reunião sozinho | Convite próprio no sistema diário compartilhado | Respeita a progressão das missões revisadas |
| Pós-game explicava que a família melhorou | Chá, agenda e Gladion ficando mais um pouco | Fecha com personalidade e algo que acontece na sala |

## 13. Conferência para implementação

- [ ] Convocação única integrada ao fim de New Bark e ao limite diário global.
- [ ] Sem reunião automática antes do convite; saves antigos preservados.
- [ ] Cena principal toca uma vez; estado 11 retoma só preparação.
- [ ] Falas têm um falante por caixa, nome correto e paginação conferida.
- [ ] Nenhuma certeza de UBs ilesas, destino de portal por bússola ou poder novo de Faller.
- [ ] Conflito de liderança permanece para o Altar; Lusamine mantém o progresso feito.
- [ ] Equipe e PC tratados separadamente; Cosmog/Cosmoem não liberam o teste.
- [ ] Com os dois elegíveis, escolha explícita; saída de menu devolve controle.
- [ ] Parceiro visível antes de agir; sem follower duplicado, mesa atravessada ou ator coberto.
- [ ] Teste mostra resposta limitada; não abre uma fenda na casa.
- [ ] Beast Ball mostrada, retida por Anabel e independente do crafting do jogador.
- [ ] Passe sem duplicação; falha de entrega recuperável sem repetir a reunião inteira.
- [ ] Unlock persistente, ponto seguro fora do warp e restauração única de follower/controle.
- [ ] Porto mantém retorno; Altar revalida o parceiro sem revogar a viagem.
- [ ] Pós-game respeita dias existentes e não mistura família com briefing antigo.

**Entrega:** roteiro completo para implementação. Equipamento, calibração, consultas ao PC, seleção entre parceiros, marcador de recuperação da entrega e posicionamento precisam ser integrados e testados na versão atual do projeto.
