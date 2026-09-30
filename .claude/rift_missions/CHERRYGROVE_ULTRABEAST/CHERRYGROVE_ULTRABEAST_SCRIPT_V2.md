# Cherrygrove — Necrozma, Blacephalon e Stakataka

**Rift Mission 3 · Revisão completa V2 · 25/09/2026**

**Status:** roteiro proposto para implementação, revisado a partir de `CHERRYGROVE_ULTRABEAST_SCRIPT(2).md`. Continuidade: Blackthorn V3, Mahogany V3 e regra aprovada de convocações diárias. Falas finais propostas em inglês; encenação e contratos em português. Este arquivo não comprova alterações na ROM.

Escopo: ligação, briefing, preparação na praia, cooperação com Kukui/Incineroar, resgate do protagonista, escolha de boss, tentativa antecipada de contenção, absorção, parceiro opcional, conversa pessoal de Anabel, investigação de Elm e recuperação. Balanceamento continua em `CHERRYGROVE_ULTRABEAST_IMPLEMENTATION.md`; não inventar IDs ou flags disponíveis.

## 1. O que muda no arco

Blackthorn mostrou que a ligação à ruptura impede a contenção. Mahogany mostrou que uma conexão pode ser interrompida e que os sinais das UBs persistem após a absorção. Agora o grupo tenta agir **antes** de Necrozma recolhê-las. Consegue reconhecer o início do movimento e lançar a Ball a tempo, mas descobre que antecipação sem interromper a ligação ainda não basta.

Kukui oferece uma observação específica: Blacephalon oculta com clarões os deslocamentos de Stakataka. Anabel percebe uma abertura próxima segundos antes do instrumento, protege o jogador e, depois da emergência, explica sua condição de Faller. A retirada de Necrozma deixa uma direção registrada para cruzar com observações de outros pesquisadores. Isso justifica procurar Elm; não prova onde será a próxima ocorrência.

**Vitória concreta:** a praia é contida, a rota de acesso à cidade continua livre e os registros ficam melhores. Nenhuma pessoa afirma que as criaturas absorvidas já estão perdidas para sempre.

### Vozes e decisões

| Personagem | O que procura | Como aparece na cena |
| --- | --- | --- |
| Kukui | Entender o movimento e impedir a chegada das UBs à cidade | Entusiasmado, informal, concreto; demonstra experiência dando instruções úteis |
| Anabel | Proteger a equipe e antecipar a absorção | Calma, precisa, distingue sensação de medição; decide quando explicar algo pessoal |
| Looker | Manter o acesso seguro e apoiar Anabel | Cortês, atento, breve no perigo; humor discreto só na preparação e no rescaldo |
| Protagonista | Conter uma frente e ajudar a equipe | Escolhe o alvo, vence o boss e acompanha a ação com olhares e movimentos claros |
| Incineroar | Cooperar com Kukui e guardar a frente | Sai da Ball antes da interceptação; contém sem arremessar um gigante pela praia |

O conhecimento anterior do jogador sobre Kukui não é presumido. O briefing identifica sua profissão; Kukui fala com naturalidade sem afirmar encontros anteriores não documentados. Looker e Anabel já conhecem seu papel como pesquisador e treinador. Não há surpresa de “civil incapaz que era um mestre secreto”.

## 2. Contratos gerais

1. **Toda message box tem identificação acima dela.** Um falante por bloco. A primeira linha dos blocos abaixo é metadado da plaquinha, nunca texto incorporado ao corpo.
2. `NARRATOR`, `NOTE` e `SYSTEM` identificam mensagens sem interlocutor humano. Não usar `NONE`. Menus mantêm a identidade de quem perguntou.
3. Reaplicar nome depois de telefone, batalha, flashes, menus e mudança de personagem. Nenhuma rotina herda silenciosamente a plaquinha anterior.
4. Necrozma já foi identificado. Não repetir descobertas de Blackthorn ou prometer explicar seu nome depois.
5. Falas opcionais não contêm a única explicação de uma ação obrigatória.
6. Solgaleo/Lunala aparece fisicamente se sua ação for mostrada. Reavaliar espécie após a batalha; não duplicar follower.
7. As sensações de Anabel têm alcance local e antecedência breve, com incerteza. Não são um localizador de cidades ou um meio de prever ataques indefinidamente.
8. A ameaça conserva sua música após a batalha e durante a absorção. O tema local só volta quando a passagem estiver fechada.
9. O evento funciona em qualquer horário. Sem quatro dias fixos de vigília, horário telefônico obrigatório ou promessas de acontecimentos “esta noite”.
10. Quebras de linha são sugestões. Medir na fonte real, com nomes e variáveis expandidos, antes de importar.

## 3. Ligação diária — convocação para Olivine

Mahogany concluída, nenhum convite anterior pendente e nenhuma convocação de Looker no dia corrente: a chamada pode ocorrer no primeiro momento seguro. A chamada inicial de Blackthorn conta no mesmo limite. Usar o calendário do sistema diário/RTC, não um intervalo móvel de 24 horas.

Não interromper menus, batalhas, cutscenes, diálogos ou transições. Se o jogador estiver dentro da base de Olivine, aguardar sua saída. Adiar não consome a chamada. Ao terminá-la, registrar juntos dia e convite de Cherrygrove. Convite persiste entre dias e saves, sem ligações de lembrete e sem expiração.

### `Phone_Text_LookerCherrygroveInvite`

```text
LOOKER
{PLAYER}, we've had a report
from the Cherrygrove coast.

Meet us at the Olivine base.
Anabel found something in Lillie's notes
that may help us this time.
```

A chamada anuncia o local e o motivo da reunião. Nenhum ataque em andamento é anunciado na despedida de Mahogany para depois aguardar arbitrariamente a mudança de dia.

### `OlivineCity_House1_Text_WaitForCherrygroveCall`

Antes da convocação, reutilizar a mesma label e texto definidos em Mahogany V3; não criar uma segunda definição no código:

```text
LOOKER
We're comparing Lillie's notes
with Anabel's recordings.
I'll call when we have a lead.
```

Depois da chamada, liberar o briefing; depois do briefing, liberar a cena de campo. Visitar Cherrygrove primeiro não pula essa sequência. Derrota permite retomar a missão já liberada no mesmo dia. Saves antigos com briefing ou operação iniciados conservam seu progresso sem uma chamada retroativa; não inventar datas de chamadas não registradas.

## 4. Olivine — o novo plano

Preservar a aproximação herdada: jogador em `(4,8)`, Looker de `(4,5)` a `(4,7)`, Anabel de `(7,5)` a `(5,7)`. Retornar ao fim. Interação manual fornece o briefing pendente sem repetir deslocamentos incompatíveis com a posição do jogador.

### `OlivineCity_House1_Text_BriefingM3Welcome`

```text
LOOKER
Professor Kukui reported the disturbance.
He studies Pokémon moves in Alola.

Fortunately for us, he was visiting Johto.
Unfortunately for his holiday.
```

### `OlivineCity_House1_Text_BriefingM3Evidence`

```text
ANABEL
Lillie marked a pause before Necrozma
reached over the ice.
It matches a change in my recording.

If it happens again, we may have time
to act before it takes them.
```

A pausa é uma hipótese baseada nos registros de Mahogany, não previsão garantida. Não exigir um flashback novo nem reescrever retroativamente uma observação que ninguém fez: Lillie já registrou o começo dos pulsos.

### `OlivineCity_House1_Text_BriefingM3Plan`

```text
ANABEL
We'll weaken the Ultra Beasts,
then try to secure one before it moves.

I'll watch Necrozma.
Kukui will help you hold the shore.
```

### `OlivineCity_House1_Text_BriefingM3Safety`

```text
LOOKER
The residents are sheltered at Violet Gym.
The Pokémon Center is still available.

Meet us on Cherrygrove's northwest shore.
```

Preservar o abrigo herdado em Violet, sem inventar ônibus, disputa pessoal com moradores ou deixar Kukui sozinho por dias depois do pedido de ajuda. Centro continua atendendo como exceção ao fechamento civil.

### Orientações repetíveis

#### `OlivineCity_House1_Text_LookerGoAheadM3`

```text
LOOKER
The northwest shore in Cherrygrove.
We'll meet you there.
```

#### `OlivineCity_House1_Text_AnabelGoAheadM3`

```text
ANABEL
Prepare before you approach the beach.
We need both fronts covered.
```

## 5. Espaço, água e atores

O arquivo original distingue colisão de comportamento do metatile. Isso continua obrigatório: colisão livre não torna oceano caminhável. A revisão abaixo é uma proposta de integração sobre a geometria fornecida, não uma validação do mapa atual.

**Correção espacial necessária:** Stakataka se desloca fisicamente. Portanto, seu ponto inicial `(24,10)` precisa ser uma bancada rasa que sustente o contato com o chão, conectada ao raso `(25,10)` e à margem `(26,10)`. No mapa herdado, `(24,10)` é oceano. Alterar de forma localizada esse trecho e sua aparência, ou remapear a frente inteira para uma bancada rasa real. Não fazê-la caminhar sobre mar profundo sem explicação nem apenas liberar colisão invisível. Blacephalon pode flutuar acima da água; Necrozma paira junto da abertura em `(22,10)`.

| Ator | Preparação | Confronto | Rescaldo |
| --- | --- | --- | --- |
| Jogador | Interage de `(27,8)` | `(27,10)`; após resgate `(28,10)` | `(28,10)` |
| Looker | `(27,7)` | `(27,8)`; depois `(27,9)` | `(28,9)` |
| Anabel | `(28,7)` | `(28,9)`; depois `(27,10)` | `(27,10)` |
| Kukui | `(26,7)` | `(26,8)` | `(29,10)` |
| Incineroar | Na Ball até a preparação da frente | Surge `(26,9)`; intercepta em `(26,10)` | Recolhido antes da aproximação de Kukui |
| Necrozma | Ausente | `(22,10)`, flutuando junto da abertura | Removido depois da retirada |
| Blacephalon | Ausente | `(24,9)`, sobre a água | Absorvido |
| Stakataka | Ausente | `(24,10)` → `(25,10)`; recua a `(24,10)` | Absorvido |
| Parceiro do jogador | Follower ocultado como os demais | Surge após batalha em `(29,10)` | Recolhido antes de Kukui ocupar o tile |

**Intercepção:** Incineroar ocupa `(26,10)` antes que Stakataka chegue lá. Fica realmente entre ela e o jogador. O salto original de Stakataka diretamente para esse tile foi removido.

Candidatos de posições devem ser conferidos com sprites reais, colisões, elevação, metatiles e orçamento de objetos. Efeitos de ruptura e pulsos podem ser efeitos/metatiles: não assumir um slot de NPC disponível. Manter a saída para leste livre. Remover/recolher atores na ordem, sem sobreposição entre Kukui e o parceiro.

## 6. Antes do confronto — cidade e preparação

### `CherrygroveCity_Text_DoorLocked`

```text
NOTE
Residents are sheltered at Violet Gym.
Please keep away from the northwest shore.
—International Police
```

Cidade evacuada, Centro acessível. Restaurar posteriormente moradores e objetos de presentes conforme seus próprios estados; não reaparecer Pokémon já recebidos.

### `CherrygroveCity_Text_UBAnabelIdle`

```text
ANABEL
The route back to town is clear.
Use the Center if you need it.

Speak with Looker when you're ready.
```

Anabel acompanha o jogador ao falar e depois volta-se para a abertura esperada, a oeste. Remover a repetição prévia de avisos sobre a família Cosmog.

### `CherrygroveCity_Text_UBKukuiIdle`

```text
KUKUI
Hey, cousin. Kukui.
Looker said you'd be joining us.

I'd rather study these two
somewhere they can't flatten a town.
```

Uma introdução curta que funciona sem encontro anterior. Se a campanha já tiver uma apresentação obrigatória confirmada, adaptar somente a saudação, sem inventar callback.

### `CherrygroveCity_Text_UBLookerGreet`

```text
LOOKER
Watch your footing, {PLAYER}.
The sand is firmer on this side.

Professor, show us what you noticed.
```

### `CherrygroveCity_Text_UBKukuiObservation`

```text
KUKUI
Blacephalon flashes first.
When I can see again, Stakataka's closer.

But look at those tracks.
It leaves a trail through the shallows.
```

Kukui aponta marcas rasas/ondulações na bancada. Arte ou efeito simples precisa existir antes da fala. Não fabricar pegadas sobre oceano. Se não houver decal persistente, usar sulcos junto da margem e um rastro de água na demonstração seguinte.

### `CherrygroveCity_Text_UBAnabelObservation`

```text
ANABEL
So it moves while the flash hides it.
```

### `CherrygroveCity_Text_UBKukuiPlan`

```text
KUKUI
That's what I think.
We need to keep the flashes away
from the other fight.

You take one. I'll take the other.
```

Não confundir hipótese com certeza: o movimento será confirmado na aparição. Evitar “ninguém consegue não piscar”, imunidade por fechar os olhos ou invisibilidade cancelada por observação.

### `CherrygroveCity_Text_UBReady`

```text
ANABEL
Are you and your Pokémon ready?
```

Menu Yes/No, plaquinha ANABEL. Guardar que a explicação de Kukui já foi ouvida para não repeti-la a cada recusa.

### `CherrygroveCity_Text_UBNotReady`

```text
LOOKER
The Center is open.
We'll keep the approach clear.
```

## 7. Aproximação e aviso de Anabel

**Yes:** controlar a cena e ocultar o follower, guardando o necessário para restaurá-lo uma vez. Mover Kukui para `(26,8)`, depois jogador para `(27,10)`, Looker para `(27,8)` e Anabel para `(28,9)`. Todos olham oeste ao terminar. Não mover Looker antes de desocupar `(27,8)`.

Kukui já prepara seu parceiro antes de a ameaça estar sobre o jogador.

### `CherrygroveCity_Text_UBKukuiPrepare`

```text
KUKUI
Incineroar, with me.
Keep the way back open.
```

Ball abre; Incineroar aparece em `(26,9)`, olhando oeste. Cry correspondente. O policial não se surpreende por ele possuir um Pokémon.

Anabel interrompe o olhar no instrumento. Expressão breve, sem ajoelhar ou iniciar explicação.

### `CherrygroveCity_Text_UBAnabelSenses`

```text
ANABEL
Wait. An opening, close by.
Step back from the water.
```

### `CherrygroveCity_Text_UBLookerMeter`

```text
LOOKER
The meter hasn't changed yet.
```

### `CherrygroveCity_Text_UBAnabelCertain`

```text
ANABEL
I know. Give it room.
```

Kukui observa a superfície, que para de ondular perto da abertura. O aviso antecede o sinal instrumental por um intervalo curto; o aparelho reage logo depois. Não dizer que Anabel sabe sempre onde Necrozma está.

### `CherrygroveCity_Text_UBKukuiWater`

```text
KUKUI
The water's going still.
Incineroar, hold there.
```

Tema local sai durante o aviso. Abertura estreita sobre a água, Necrozma emerge **através dela**, pairando. Não declarar ao mesmo tempo que ele nunca atravessa rupturas e que sai de uma.

### `CherrygroveCity_Text_UBNecrozmaArrives`

```text
ANABEL
Necrozma.
Watch its arms and the light around them.
```

Tema de ameaça ativo antes da revelação completa. Necrozma alarga a abertura; Blacephalon aparece ao norte, Stakataka na bancada ao sul. Cries separados, breve pausa para ler as silhuetas.

### `CherrygroveCity_Text_UBAppear`

```text
KUKUI
Blacephalon and Stakataka.
Those are the two.
```

## 8. O truque das duas — movimento sob cobertura

Blacephalon prepara a cabeça luminosa. Kukui percebe e dá a instrução antes do clarão.

### `CherrygroveCity_Text_UBFlashWarning`

```text
KUKUI
Here comes the flash!
Turn your eyes away from its head!
```

Um clarão curto cobre parte da tela. Stakataka **anda** de `(24,10)` para `(25,10)` durante o efeito, deixando rastro e som de passos na água. Mostrar o final do deslocamento quando a luz baixa. Não usar `setobjectxy` como teleporte diegético. O clarão prejudica a visão dos personagens; o jogador recebe som e movimento suficientes para entender a relação.

### `CherrygroveCity_Text_UBMovementConfirmed`

```text
KUKUI
There! It's moving through the shallows.
The flash hides its steps.
```

Stakataka se inclina para avançar ao tile `(26,10)`. O jogador vira brevemente para o movimento, mantendo o corpo no lugar.

### `CherrygroveCity_Text_UBKukuiIntercept`

```text
KUKUI
Incineroar, block the path!
```

Incineroar desce de `(26,9)` para `(26,10)` e encara oeste antes de Stakataka avançar. Um impacto curto de contenção, Stakataka perde o passo e recua um tile até `(24,10)`. Não arremessar vários tiles nem transformar Incineroar numa parede indestrutível; ele precisa manter pressão depois.

### `CherrygroveCity_Text_UBKukuiHold`

```text
KUKUI
Good! Keep it in the water.
Don't give it room to step forward.
```

A força de Kukui aparece nessa leitura e no comando. Não parar a emergência para contar a história da Liga de Alola.

## 9. Anabel tira o jogador da abertura

Necrozma move os braços; uma pequena distorção começa a se formar junto da posição do protagonista. A cena não revela se ele foi escolhido deliberadamente: todos veem o risco local. Anabel percebe esse começo antes de ele ganhar força.

### `CherrygroveCity_Text_UBAnabelMove`

```text
ANABEL
{PLAYER}, move right! Now!
```

| Ordem | Ator | Ação |
| --- | --- | --- |
| 1 | Anabel | `(28,9)` → `(27,9)`, olha sul e faz gesto de puxar/indicar |
| 2 | Jogador | `(27,10)` → `(28,10)`, deslocamento com direção preservada |
| 3 | Efeito | Clarão e distorção no ponto abandonado `(27,10)`; Anabel permanece ao norte até o efeito se dissipar |
| 4 | Anabel | Só depois do fechamento local, avança a `(27,10)` e encara oeste |
| 5 | Looker | `(27,8)` → `(27,9)`, olha sul para Anabel |

Não representar Anabel absorvendo um raio no corpo. O gesto é retirar o jogador da área de uma abertura antes de ela se formar. Anabel também fica fora dessa área até a distorção cessar; só então ocupa a posição de apoio. Não exigir sprite ajoelhado nem inventar impacto no corpo para justificar a revelação. Incineroar continua contendo Stakataka, sem atravessar o resgate.

### `CherrygroveCity_Text_UBLookerChecks`

```text
LOOKER
Anabel! Are you hurt?
```

### `CherrygroveCity_Text_UBAnabelReady`

```text
ANABEL
I'm all right.
Keep the way back clear.
```

Anabel retoma a observação da abertura principal. **Correção explícita do protagonista:** virar oeste depois do deslocamento e novamente depois do clarão. Ao olhar Anabel durante a resposta, fazê-lo voltar oeste antes da escolha. Não depender do estado de direção salvo por uma animação, nem deixar o jogador permanentemente olhando para leste.

A explicação de Faller acontece no rescaldo. Não parar as duas UBs para uma confissão longa.

## 10. Divisão das frentes e batalha

### `CherrygroveCity_Text_UBChoosePrompt`

```text
KUKUI
Which one will you take, {PLAYER}?
Incineroar and I will handle the other.
```

Menu Blacephalon/Stakataka, plaquinha KUKUI, sem cancelamento com B após compromisso. Jogador olha o alvo escolhido, não um ponto genérico da margem. Escolha vale pela tentativa.

### Se escolher Blacephalon — `CherrygroveCity_Text_UBPickedBlacephalon`

```text
KUKUI
Keep Blacephalon facing your side.
We'll hold Stakataka here.
```

Incineroar mantém a linha sul em `(26,10)`. Blacephalon volta a atenção para a frente do jogador, ao leste/nordeste de seu ponto. Encenação mostra os clarões orientados para fora do corredor de Stakataka. Não prometer cegueira zero: a contenção de Incineroar impede avanço mesmo quando há luz residual.

### Se escolher Stakataka — `CherrygroveCity_Text_UBPickedStakataka`

```text
KUKUI
We'll draw Blacephalon this way.
Keep Stakataka off the shore!
```

O jogador assume a frente sul do seu ponto seguro, com seu Pokémon representado pela transição normal de batalha. Incineroar recua de `(26,10)` para `(26,9)`, olha oeste e pressiona Blacephalon para orientar os flashes ao norte. Kukui permanece ao norte, dando suporte. A troca ocorre sob contenção, sem deixar a frente sul aberta antes de o jogador assumir.

**Regra dramática:** dividir atenção e linhas de ataque impede que um clarão cubra um avanço livre. Olhar para Stakataka não bloqueia movimento por magia. Nenhuma ordem manda entrar debaixo dela ou lutar de olhos fechados.

### `CherrygroveCity_Text_UBAnabelWatch`

```text
ANABEL
I'll watch Necrozma.
Leave the capture to me.
```

Boss único contra a escolhida, no terceiro degrau do balanceamento herdado. Não acrescentar batalha jogável contra Kukui, rodada extra ou mudança de time neste roteiro. Captura em batalha segue bloqueada pela ligação. Derrota real/blackout conforme sistema do projeto.

Retorno com a mesma formação e trilha de ameaça. Jogador explicitamente oeste/em direção ao alvo; Anabel e Incineroar conservam suas funções. Reconstruir buffers e nome do próximo falante antes do texto.

## 11. Antecipar a absorção — avanço com limite

Kukui encerra sua frente com uma ação curta de Incineroar. As duas UBs permanecem visíveis em posições de contenção: Blacephalon `(24,9)`, Stakataka `(24,10)`. Não narrar pose caída se o sprite não a possui.

### `CherrygroveCity_Text_UBKukuiFoughtStakataka`

```text
KUKUI
Stakataka's stopped.
Stay on it, Incineroar.
```

### `CherrygroveCity_Text_UBKukuiFoughtBlacephalon`

```text
KUKUI
No more flashes.
Good work, Incineroar.
```

Necrozma ergue os braços; o instrumento repete a mudança de pulso identificada em Mahogany. Isso acontece **antes** de qualquer arrasto. Anabel acompanha o indicador e prepara a Ball policial comum. Não é a Beast Ball especial de Kurt e não consome item do jogador.

### `CherrygroveCity_Text_UBAnabelWindow`

```text
ANABEL
That pulse—it's starting.
Keep them still!
```

Anabel lança para a UB vencida pelo jogador. Mostrar a Ball chegando enquanto a criatura ainda está no seu ponto: a equipe realmente agiu antes. A ligação à ruptura pulsa, interrompe a contenção e repele a Ball intacta. Não fingir que foi o atraso de Anabel que causou a falha.

### `CherrygroveCity_Text_UBContainmentFailed`

```text
ANABEL
I reached it in time.
The connection still pulled it back!
```

### `CherrygroveCity_Text_UBKukuiBreakLink`

```text
KUKUI
Incineroar, hit the light between them!
```

Incineroar ataca da margem na direção do filamento próximo. O filamento oscila, mas não se rompe a tempo. Ação ocorre enquanto o arrasto começa, não depois de todos comentarem. Não reproduzir uma parede de gelo sem Pokémon ou ambiente que a justifique.

As UBs resistem brevemente ao arrasto. Transformam-se em luz antes de passar para os pontos de oceano `(23,9)` e `(23,10)` em direção a Necrozma. Somente os atores das UBs são removidos. Necrozma fica visível, recebe um pulso de brilho e volta a oscilar.

### `CherrygroveCity_Text_UBAbsorbedSignals`

```text
ANABEL
Their signals are still there.
Keep recording, Looker.
```

### `CherrygroveCity_Text_UBLookerRecording`

```text
LOOKER
Recording. I have the direction too.
```

**Instrumentos:** Anabel lê o aparelho já estabelecido; Looker anota a orientação mostrada por ele e o alinhamento visível da abertura. Não lhe dar um detector novo sem apresentação, nem dizer que localizou Necrozma em outra cidade. Não confirmar seis criaturas apenas contando pulsos: o registro desta ocorrência reconhece Blacephalon e Stakataka; comparar os anteriores é trabalho posterior.

## 12. Parceiro opcional — preservar a leitura de retirada

Reavaliar a equipe após a batalha. Escolher um representante elegível da família Cosmog pela ordem da party, com espécie/forma atual, e manter a escolha até o fim. Se ambos Solgaleo e Lunala estiverem presentes, não alternar nomes no buffer. A ausência da família não impede missão, pista ou avanço.

### Sem família Cosmog

Looker registra a direção da abertura antes de ela fechar. Dados suficientes para comparação, ainda sem destino exato. Seguir para a retirada. Não inventar um Pokémon emprestado.

### Cosmog ou Cosmoem

Ball reage e abre. Parceiro aparece em `(29,10)`, na lateral protegida do jogador, com cry e movimento compatíveis. Necrozma volta o olhar para ele; não avançar através da bancada e da contenção de Incineroar por conveniência.

#### `CherrygroveCity_Text_UBNecrozmaSensesCosmog`

```text
KUKUI
Keep {STR_VAR_1} beside you, cousin.
Incineroar, hold the shore.
```

Jogador olha o parceiro à direita e volta oeste antes da retirada de Necrozma. Não alegar que Cosmoem caminha se apenas flutua. Kukui não chama o Pokémon de Nebby nem inventa histórias de telhado, barco e documentos.

### Solgaleo ou Lunala

Ball abre antes da descrição. Parceiro surge em `(29,10)`, olha oeste, emite cry e pulso. A borda da abertura reduz a oscilação; Looker consegue confirmar a mesma direção anotada no primeiro registro. Anabel acompanha o sinal até Necrozma começar a atravessar.

#### `CherrygroveCity_Text_UBPartnerWindow`

```text
ANABEL
The opening's steady.
Looker, check the bearing now.
```

#### `CherrygroveCity_Text_UBPartnerBearing`

```text
LOOKER
It matches. I've marked it.
```

Kukui mantém Incineroar na frente. O parceiro não liberta UBs, não prende Necrozma e não fixa uma passagem permanente. A estabilização dá alguns instantes para **confirmar** uma observação já disponível no caminho obrigatório. Quando o pulso acaba, a oscilação retorna e a passagem fecha normalmente.

Essa função progride em relação às missões anteriores: Blackthorn observa estabilização; Mahogany lê melhor os sinais; Cherrygrove usa o intervalo para conferir o registro da saída. Sem o parceiro, a comparação com outros pesquisadores continua possível.

## 13. Retirada e segurança

Necrozma atravessa a abertura; a borda fecha depois dele. Não sumir com o grupo inteiro no mesmo flash. Anabel aguarda a leitura cair antes de liberar a praia.

### `CherrygroveCity_Text_UBNecrozmaGone`

```text
ANABEL
The opening has closed.
Hold here a moment.
```

Pausa curta; instrumento não registra nova abertura. Kukui mantém Incineroar pronto até a confirmação.

### `CherrygroveCity_Text_UBStreetClear`

```text
ANABEL
It's clear.
```

Agora encerrar tema de ameaça e retomar tema local suavemente. Jogador recolhe o parceiro **visivelmente**, se apareceu. Kukui recolhe Incineroar após verificar a margem. Efeito de Ball, sem flash que pareça outro ataque. Nenhum ator é removido enquanto ainda precisa executar uma ação.

### `CherrygroveCity_Text_UBAftermathCheck`

```text
LOOKER
Everyone all right?
Anabel, take a moment.
```

### `CherrygroveCity_Text_UBAftermathAnabel`

```text
ANABEL
Thank you. I will.
```

Ela aceita apoio sem perder autoridade. Não transformar exaustão em piada nem fazê-la explicar que está bem repetidamente.

### Formação da conversa

1. Looker: `(27,9)` → `(28,9)`, olha sul.
2. Kukui: `(26,8)` → `(29,8)` → `(29,10)`, olha oeste. Parceiro do jogador já foi recolhido.
3. Anabel: permanece `(27,10)`, olha leste.
4. Jogador: permanece `(28,10)`, olha oeste para Anabel; norte ao responder a Looker; leste ao ouvir Kukui. Volta ao interlocutor a cada bloco.

Percursos candidatos dependem do mapa atual. Ninguém fica em `(28,11)` sob a caixa. Não reutilizar a rota antiga que passava pelo tile de Incineroar como se ele ainda estivesse ao norte.

## 14. Anabel — a explicação depois do perigo

A conversa é obrigatória, curta e após segurança confirmada. Não criar um interrogatório nem exigir que Looker divulgue o passado de Anabel por ela.

### `CherrygroveCity_Text_UBAnabelFallerIntro`

```text
ANABEL
{PLAYER}, about what happened...
I felt that opening before I saw it.
```

### `CherrygroveCity_Text_UBAnabelFaller`

```text
ANABEL
I once came through an Ultra Wormhole.
That's what they call a Faller.

I don't remember much from before.
```

Pausa breve. Looker olha para ela; não interrompe. Kukui ouve, sem inserir uma teoria sobre sua vida.

### `CherrygroveCity_Text_UBAnabelFallerLimit`

```text
ANABEL
Sometimes I feel an opening nearby.
Only a moment before it happens.

I can't tell where the next one will be.
```

A sensibilidade é a regra narrativa escolhida para este hack. A fala não afirma que todos os Fallers possuem um poder idêntico nem que ela consegue localizar cidades por intuição. Amnésia permanece limitada ao que ela descreve, sem inventar história pessoal perdida.

### `CherrygroveCity_Text_UBLookerSupport`

```text
LOOKER
Then we won't leave you watching it alone.
```

### `CherrygroveCity_Text_UBAnabelSupport`

```text
ANABEL
Agreed.
```

O jogador faz um gesto de reconhecimento/agradecimento. Nada de mensagem do protagonista se o projeto o mantém silencioso. A equipe volta ao trabalho depois de dar espaço à explicação, não no meio dela.

No próximo briefing de Olivine, não repetir esta revelação como novidade. Qualquer continuação pessoal deve acrescentar algo pertinente ao plano e acontecer antes da emergência, sem tornar Anabel um dispositivo de exposição.

## 15. O que Kukui e os registros acrescentam

### `CherrygroveCity_Text_UBKukuiThanks`

```text
KUKUI
You kept your side covered, cousin.
That gave Incineroar room to work.

Next time we team up,
let's leave the town out of it.
```

Kukui reconhece uma ação concreta. Não promete Liga de Alola jogável, não desvaloriza o Campeão de Alola existente e não repete currículo.

### `CherrygroveCity_Text_UBAftermathPlan`

```text
ANABEL
We acted before the pull this time.
It wasn't enough while they were connected.

We need to stop the connection
before we try to capture them.
```

Isso desenvolve uma evidência conhecida: Mahogany provou interrupção local, Cherrygrove testa antecipação sem aquela barreira. Evitar vender novamente a própria existência da ligação como descoberta.

### `CherrygroveCity_Text_UBAftermathBearing`

```text
LOOKER
We have a direction for the opening.
Can we trace it?
```

### `CherrygroveCity_Text_UBAftermathLimit`

```text
ANABEL
Not from this reading alone.
We need another point of comparison.
```

Direção é uma observação local, não coordenada garantida do destino dentro de Ultra Space. Cruzar registros pode localizar outra manifestação relacionada em Johto; não chamar isso de triangulação precisa com um dado só.

### `CherrygroveCity_Text_UBKukuiElm`

```text
KUKUI
I'll ask Professor Elm for his readings.
His lab is close to this coast.

We can compare the times and see
whether he's picked up the same pulses.
```

### `CherrygroveCity_Text_UBLookerElm`

```text
LOOKER
Send them to Olivine.
Even the readings he couldn't explain.
```

### `CherrygroveCity_Text_UBKukuiLogs`

```text
KUKUI
You got it.
A strange result's still a result.
```

A razão de procurar Elm é proximidade e possibilidade de dados comparáveis. Kukui não sabe antecipadamente que existem seis semanas de registros rotulados como defeito. Essa descoberta pertence à resposta de Elm, durante o intervalo entre missões.

### Retorno opcional — somente se parceiro apareceu

#### Cosmog/Cosmoem — `CherrygroveCity_Text_UBAftermathCosmog`

```text
KUKUI
How's {STR_VAR_1} doing?
Give it a quiet place to rest.
```

#### Solgaleo/Lunala — `CherrygroveCity_Text_UBAftermathLegend`

```text
ANABEL
{STR_VAR_1} gave us time
to check the bearing.
I'll include that in the report.
```

Não acrescentar fala sobre medo de Necrozma. Não presumir que o jogador trouxe o mesmo parceiro a Blackthorn ou Mahogany. Parceiro já recolhido; ninguém o descreve agindo fora da Ball agora.

## 16. Despedida e resolução

### `CherrygroveCity_Text_UBHookLooker`

```text
LOOKER
We'll compare the records in Olivine.
I'll call when we have a lead.

For now, leave this beach to the waves.
```

### `CherrygroveCity_Text_UBHookKukui`

```text
KUKUI
I'll contact Elm before I leave Johto.
Take care, cousin.
```

Looker/Anabel partem para tratar dos registros e da liberação da cidade. Kukui recolhe seus apontamentos e sai depois de confirmar o encaminhamento, sem viagem instantânea para todas as bibliotecas. A transição final pode ocultar a saída longa, não a coleta dos registros ou o recolhimento dos Pokémon.

**Estado final herdado: 8.** Só avançar após vitória e rescaldo. A integração deve conservar a progressão anterior 6 → briefing/ativação → missão → 8, verificando o significado concreto dos estados na versão atual. A convocação diária é controle separado; não inventar que um número livre já existe.

Restaurar cidade, portas, follower e posição segura do jogador. O roteiro herdado lista catorze moradores e Pokémon de presentes do Friendly Trader: reconciliar cada objeto com suas próprias flags. Não reabrir presentes recebidos, resetar trocas ou ativar simultaneamente variantes de NPCs. Não reaplicar automaticamente a população inteira apenas porque a flag do incidente foi limpa.

**Próxima convocação:** New Bark depende desta conclusão e de não ter ocorrido ligação de Looker no dia. Se a chamada de Cherrygrove ocorreu hoje, esperar outro dia; se ocorreu em dia anterior e hoje ele ainda não ligou, a próxima pode ocorrer após o encerramento, em controle livre. Nenhuma chamada interrompe despedida ou fade.

### `OlivineCity_House1_Text_WaitForNewBarkCall`

```text
LOOKER
We're waiting for Professor Elm's records.
I'll call when we've compared them.
```

Usar somente antes da convocação seguinte. Depois dela, disponibilizar o briefing de New Bark. Não enviar o jogador de volta a uma praia já resolvida.

## 17. Ponte obrigatória para a revisão de New Bark

O arquivo original de New Bark ainda descreve Kukui lendo todos os registros de Johto, telefonando num horário específico e descobrindo sozinho um sensor supostamente quebrado. **Esse trecho não é compatível com esta revisão.** A substituição abaixo é o contrato de integração da próxima missão; está documentada aqui, sem alegar que o outro arquivo já foi modificado.

Ordem causal: Kukui solicita dados → Elm consulta seu próprio histórico e responde → Anabel/Looker comparam → Looker convoca o jogador quando a regra diária permitir. Preservar as seis semanas de registros se mantidas na missão de Elm; retirar a previsão disso por Kukui.

### `Phone_Text_LookerNewBarkInvite` — texto de integração

```text
LOOKER
{PLAYER}, Professor Elm contacted us.
His readings match the rift at Cherrygrove.

Come to the Olivine base.
We need to plan our approach to New Bark.
```

### `OlivineCity_House1_Text_BriefingM4Evidence` — substituição proposta da abertura antiga

```text
LOOKER
Elm sent the records Kukui requested.
Some go back six weeks.

He kept them even when he thought
the sensor might be faulty.
```

### `OlivineCity_House1_Text_BriefingM4Comparison`

```text
ANABEL
The pulses match our recordings.
The latest readings are stronger.

Elm is checking the instruments
while we prepare to join him.
```

### `OlivineCity_House1_Text_BriefingM4Kukui`

```text
LOOKER
Kukui sent his notes before leaving.
We have both sets to work with.
```

O restante de New Bark ainda precisa de sua revisão completa: três UBs, mãe/Lusamine, Gold/Crystal e Ultra Necrozma. Não importar automaticamente a antiga conversa de Faller como primeira revelação; Anabel já contou em Cherrygrove. Não antecipar cerco à casa do jogador por dias durante a espera da ligação.

## 18. Derrota e retomada

Preservar dificuldade e blackout do boss. A escolha pode ser refeita. Não repetir ligação, evacuação, aparição surpresa de Necrozma, interceptação de Incineroar ou resgate do protagonista como se todos os esquecessem.

Checkpoint narrativo de preparação precisa registrar se a introdução foi vista. No retry, Kukui/Incineroar mantêm as UBs na margem e o jogador retorna ao ponto seguro. Abertura, água e formação são reconstruídas sem duplicar efeitos ou atores.

### `CherrygroveCity_Text_UBRetryLooker`

```text
LOOKER
The approach is still clear.
How are your Pokémon?
```

### `CherrygroveCity_Text_UBRetryKukui`

```text
KUKUI
We've kept them off the shore.
Ready to take one again?
```

Menu Yes/No, KUKUI. Recusa:

### `CherrygroveCity_Text_UBRetryNotReady`

```text
KUKUI
Get your team ready.
Incineroar and I will hold here.
```

Aceite: reposicionar jogador em `(28,10)` e equipe na formação posterior ao resgate, pelos caminhos livres; não fingir que ele foi puxado outra vez. Voltar à escolha de alvo, com textos correspondentes e Incineroar no ponto necessário.

A revelação pessoal de Anabel ainda não ocorreu se o jogador perdeu o boss; permanece para o rescaldo da vitória. A identificação de Necrozma e a observação de Stakataka já ocorreram e não são repetidas como novas.

### `CherrygroveCity_Text_UBUnresolved`

```text
ANABEL
The shore isn't clear yet.
Regroup before we move in again.
```

Fuga/interrupção sem vitória não executam absorção, conversa final ou estado 8. Mapear os resultados reais do motor antes de integrar. Não dizer que as UBs escaparam se continuam na praia. Save/reload não limpa convite, data ou conhecimento já registrado.

## 19. Música, olhares e efeitos

| Momento | Apresentação exigida |
| --- | --- |
| Telefone/base | Interface e ambiente normais; plaquinha LOOKER no telefone |
| Aviso de Anabel | Fade do tema local; aparelho responde depois da sensação |
| Necrozma aparece | Ameaça ativa antes da revelação completa |
| UBs aparecem | Cries distintos, pausa curta para reconhecer as duas |
| Clarão de Blacephalon | Movimento e rastro de Stakataka legíveis; sem teleporte |
| Resgate | Protagonista volta oeste após deslocamento e novamente após efeito |
| Escolha/batalha | Nome KUKUI no menu; olhar ao alvo; retorno com ameaça |
| Contenção | Ball chega antes do arrasto; ligação a repele |
| Absorção | Tentativa de interrupção; somente UBs somem; Necrozma oscila |
| Parceiro | Saída real da Ball; nome/cry corretos; slot próprio |
| Retirada | Fechar borda após Necrozma; confirmar segurança antes do tema local |
| Conversa final | Olhares acompanham cada falante; parceiros recolhidos antes de movimentar Kukui |

Preservar a proposta de `MUS_DP_LEGEND_APPEARS`, confirmando disponibilidade e resultado sonoro no build. Manter tema de boss do projeto. Reaplicar tema de ameaça após a batalha, sem depender somente de `save_song` se o motor sobrescreve esse estado.

Preservar a orientação herdada de `fadescreenswapbuffers` para flashes e testar dia/noite. Clarões curtos, sem sucessões longas para esconder falta de coreografia. Efeito de água parada deve ser local e reversível; não congelar permanentemente a animação do mapa.

**Olhar final do jogador:** controle devolvido em posição segura com orientação definida. Qualquer fala para um NPC seguida de nova ação oeste precisa de retorno explícito. A correção é um contrato para o script, não uma alegação de bug já resolvido no motor.

## 20. Integração e aceitação

| Item | Alteração necessária |
| --- | --- |
| Convocação | Registro diário compartilhado e convite persistente antes do briefing |
| Textos | Novas labels por falante; retirar blocos antigos e nomes misturados |
| Conhecimento | Necrozma já conhecido; registros de Mahogany usados no plano |
| Mapa | Bancada rasa real para Stakataka; conferir comportamento e aparência dos tiles |
| Movimento | Remover teleporte sob flash; passos e rastro de água visíveis |
| Incineroar | Preparado antes do perigo; posição de interceptação realmente entre UB e jogador |
| Resgate | Sequência de tiles sem disputa; jogador retorna à cena |
| Captura | Tentativa antecipada com Ball da NPC; filamento ainda bloqueia |
| Faller | Revelação no rescaldo; percepção local sem radar de longa distância |
| Parceiro | Branches independentes, sem duplicar follower ou ocupar posição futura de Kukui |
| New Bark | Substituir abertura do briefing antigo pelo encadeamento de registros descrito aqui |
| Retry | Retoma divisão de alvos, preservando introdução e convocação |
| Resolução | Estado 8 só após vitória e conclusão; respeitar flags do Friendly Trader |

- [ ] Chamada só ocorre uma vez no dia e não se repete para convite pendente.
- [ ] Briefing e campo não podem ser pulados visitando diretamente a cidade.
- [ ] Kukui é tratado como pesquisador e treinador competente desde a preparação.
- [ ] Stakataka anda sobre raso real; a luz oculta movimentos, não concede teleporte.
- [ ] Ambos os alvos têm contramedida coerente e papéis próprios para Incineroar.
- [ ] Jogador encara novamente a ação após resgate, flashes e retorno de batalha.
- [ ] Anabel salva por antecipação local e explica Faller somente após a segurança.
- [ ] Ball chega antes da absorção; falha tem causa visível e item não sai do inventário do jogador.
- [ ] UBs absorvidas continuam com sinais; o jogo não confirma contagens maiores sem evidência.
- [ ] Sem família Cosmog, há registro suficiente para seguir a investigação.
- [ ] Cosmog/Cosmoem, Solgaleo, Lunala e múltiplos elegíveis têm ator/cry/nome coerentes.
- [ ] Parceiro sai da Ball e é recolhido antes de Kukui ocupar seu tile.
- [ ] A direção registrada é pista para comparação, não destino confirmado.
- [ ] Elm é consultado antes de alguém conhecer seus registros antigos.
- [ ] Diálogos, menus, telefone, narrador e bilhete têm plaquinhas corretas.
- [ ] Música de ameaça retorna após boss e termina somente depois do fechamento.
- [ ] Retry não repete resgate ou revelações; derrota não consome outro dia.
- [ ] Moradores/presentes retornam conforme suas flags, sem duplicação de recompensas.
- [ ] Novo briefing de New Bark não repete a revelação de Faller nem a história das bibliotecas.

## 21. Exemplos do que a revisão melhora

| Antes | Agora | Ganho |
| --- | --- | --- |
| Stakataka não anda; solução é não piscar | “The flash hides its steps.”, com rastro e movimento | A contramedida combate um comportamento demonstrado |
| Looker desconhece competência de Kukui e lê seu arquivo no perigo | Kukui prepara Incineroar e bloqueia a passagem | Competência mostrada em ação; policiais mantêm credibilidade |
| Anabel faz longa revelação entre ataques | Resgate curto; “I once came through an Ultra Wormhole” depois da segurança | Ritmo e espaço emocional adequados |
| Todos redescobrem que Necrozma absorve | Equipe antecipa a absorção, mas a ligação ainda impede captura | Continuidade e avanço sem sucesso artificial |
| Parceiro reage dentro de Ball e Necrozma “tem medo” | Sai fisicamente e ajuda a confirmar a direção da abertura | Ação verificável com função própria nesta missão |
| Kukui prevê semanas de sensor quebrado | Solicita registros a Elm para comparação | Causa concreta para New Bark, sem presciência |
| “Volte a Olivine depois de descansar” | “I'll call when we have a lead.” | Despedida compatível com a convocação diária |

**Entrega:** revisão completa de história, falas, encenação e condições de retomada. Edição do mapa, importação no `.pory`, efeitos, build e validação na ROM permanecem pendentes.
