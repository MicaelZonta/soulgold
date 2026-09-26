# Blackthorn — Necrozma, Buzzwole e Pheromosa

**Rift Mission 1 · Roteiro revisado V3 · 25/09/2026**

**Status:** **IMPLEMENTADO em 25/09/2026**, incluindo a auditoria V3 do §18. Build limpo; runtime pendente. O que foi para o código, pedido por pedido, está no §15 de [`BLACKTHORN_ULTRABEAST_IMPLEMENTATION.md`](BLACKTHORN_ULTRABEAST_IMPLEMENTATION.md), e a lista de teste em jogo no §11 dele. As falas abaixo substituem a redação anterior do arquivo irmão `BLACKTHORN_ULTRABEAST_SCRIPT.md`, que fica como histórico da revisão 3. Base narrativa: `SOULGOLD_RIFT_ARCO_NARRATIVO_BLACKTHORN_V1.md`, aprovado como direção pelo autor.

Escopo: ligação após a Liga, briefing em Olivine, incidente de Blackthorn, presente de Type: Null, recuperação e gancho. Texto do jogo em inglês; direção de cena em português. Valores de boss, IDs e mecanismos do motor continuam sob responsabilidade de `BLACKTHORN_ULTRABEAST_IMPLEMENTATION.md`.

## 1. Intenção da missão

O jogador chega como Campeão a uma cidade que Clair já está defendendo. Gladion e Silvally o ajudam por reconhecerem nele um parceiro confiável. Juntos, contêm duas Ultra Beasts, mas presenciam um comportamento de Necrozma que ainda não sabem explicar.

**Resultado concreto:** os moradores ficam seguros; o grupo identifica Necrozma, registra a absorção e passa a investigar a ligação entre as criaturas e a ruptura. A possível sobrevivência das UBs só será sustentada por evidência em Mahogany.

**Mudança em relação ao roteiro anterior:** Gladion identifica Necrozma em Blackthorn. Não esconde o nome nem adia uma informação útil. O mistério é o que ele está fazendo em Johto e por que absorve outras criaturas.

### Vozes nesta cena

| Personagem | O que quer | Como fala e age |
| --- | --- | --- |
| Clair | Manter a ameaça longe das casas | Orgulhosa, objetiva; reconhece o jogador e aceita reforço sem perder iniciativa |
| Gladion | Dividir a defesa com alguém em quem confia | Poucas palavras, instruções concretas; cuidado demonstrado pela atuação de Silvally |
| Anabel | Conter a ocorrência e entender o suficiente para agir | Distingue observação de hipótese; coordena e tenta preservar as criaturas |
| Looker | Proteger as pessoas e organizar a investigação | Caloroso no encontro, direto no perigo; humor discreto apenas fora da emergência |

Não repetir a mesma descoberta por quatro vozes. Não transformar Clair em obstáculo inútil, Gladion em provocador ou Looker em alguém incapaz de reconhecer ajuda.

## 2. Contratos de apresentação e continuidade

1. **Toda fala tem nome acima da message box.** O nome indicado em cada bloco é metadado da plaquinha, não uma linha do corpo do texto.
2. **Cada bloco abaixo tem um único falante.** A troca de bloco com outro nome exige atualizar a plaquinha. A paginação do mesmo bloco mantém o nome.
3. `NARRATOR`, `NOTE` e `SYSTEM` identificam mensagens sem interlocutor humano. Nunca herdam a plaquinha anterior.
4. `{PLAYER}` e `{STR_VAR_1}` seguem as substituições do projeto. Não guardar identidade do parceiro em um buffer reutilizado por menus ou presentes; reconstruir o nome antes de usá-lo.
5. Solgaleo/Lunala presente na equipe **aparece fisicamente antes de uma fala descrever sua reação em cena**. Não criar uma cópia caso já esteja representado por follower.
6. Cosmog/Cosmoem não são transformados por conveniência narrativa. Ausência da família não bloqueia a missão.
7. Gladion e o jogador já se conhecem. Clair também conhece o protagonista. Looker e Anabel não precisam conhecer Gladion pessoalmente.
8. O Silvally de Gladion e o Type: Null do presente são indivíduos diferentes.
9. A trilha de ameaça começa na abertura da ruptura e permanece após a batalha até Necrozma partir. Não voltar ao tema alegre de Blackthorn no meio da absorção.
10. Falas opcionais não carregam nenhuma pista indispensável. A cena principal funciona mesmo que o jogador vá diretamente ao Looker.
11. Nenhum personagem conhece o destino da próxima ocorrência. O gancho prepara uma investigação, não prevê Mahogany.

**Formatação:** as quebras nos blocos são sugestões de ritmo. Medir as linhas com a fonte real, a largura da janela e nomes expandidos antes de importar. Não converter automaticamente cada parágrafo em uma caixa adicional.

## 3. Marcação da rua

As posições abaixo reaproveitam a geometria descrita no roteiro fornecido. Posições adicionais são propostas a conferir no mapa e no orçamento de objetos da versão atual; não são uma nova validação de colisões em runtime.

| Ator | Posição inicial | Posição principal |
| --- | --- | --- |
| Jogador | Fala com Looker de `(25,52)` | `(20,50)`, olhando oeste |
| Clair | `(18,49)` | Mantém a frente norte |
| Kingdra | `(17,49)` | Ao lado da linha de Necrozma |
| Necrozma | `(14,50)` | Recuo curto até `(13,50)` e retorno antes da ruptura |
| Looker | `(25,53)` | `(25,52)` durante combate; `(21,50)` no rescaldo |
| Anabel | `(26,53)` | `(26,52)` durante combate; `(22,51)` no rescaldo |
| Buzzwole | Surge em `(15,50)` | Avança até `(18,50)`; recua para `(17,50)` |
| Pheromosa | Surge em `(15,51)` | Avança pela lateral até `(18,51)`; recua para `(17,51)` |
| Silvally | Entrada pelo norte, `(19,44)` | `(19,50)` |
| Gladion | Entrada pelo norte, `(20,44)` | `(20,49)` |
| Parceiro do jogador | Somente nos ramos correspondentes | `(19,51)`, olhando oeste |
| Type: Null do presente | Somente após a ameaça e recolhimento do parceiro | Surge em `(19,49)`; aproxima-se até `(19,50)` |

Não usar a posição do futuro Type: Null enquanto Silvally a ocupa. A saída de Silvally para `(18,50)` faz parte da encenação do presente.

A pequena ruptura deve ter uma borda visível durante a absorção e a reação do parceiro. Pode ser efeito/metatile compatível com a cena; não pressupor slot livre para um objeto adicional. Se a representação atual for só um flash, adicionar o efeito antes de importar falas sobre sua oscilação.

## 4. Ato I — Ligação após a Liga

Em New Bark, após a ligação de Elm e o Hall of Fame. Preservar a elegibilidade inicial existente. A chamada aguarda um momento seguro após o término da ligação de Elm; não sobrepor janelas nem iniciar durante outro script. A tela de telefone identifica **LOOKER** durante toda a chamada.

**Registro diário compartilhado:** ao terminar esta ligação, registrar juntos a convocação de Blackthorn e o dia corrente do sistema diário/RTC do jogo. Esta chamada conta no limite de **uma convocação de Looker por dia** para o arco inteiro. Não contar a ligação de Elm. Se Looker já tiver convocado o jogador naquele dia, aguardar o próximo dia elegível; o gatilho não pode se perder por depender de um único frame.

O convite persiste até o briefing, sem expirar nem produzir lembretes nos dias seguintes. Checagens de mapa, reload e derrota não repetem a chamada. A cena de Blackthorn exige seu briefing concluído; chegar à cidade antes não inicia a operação. Não declarar flags ou IDs novos sem conferir o código atual.

Se o save já tem Blackthorn briefada ou iniciada, preservar esse progresso sem exigir uma chamada retroativa. Se não existe registro histórico do dia da chamada, não inventar esse dia nem bloquear permanentemente a sequência. Novas convocações passam a registrar a data pelo fluxo atualizado.

### `NewBarkTown_Text_LookerCall`

```text
LOOKER
Hello, {PLAYER}? Congratulations
on becoming Champion!

My name is Looker.
International Police.

My colleague and I need your help
with an investigation in Johto.

Please meet us in Olivine.
Our house is the one nearest the Gym.

I'll explain when you arrive.
```

**Direção:** cordial e profissional. Não recapitular a falsa viagem de férias por telefone nem esconder o pedido atrás de várias tentativas de apresentação.

## 5. Ato II — Escritório de Olivine

### 5.1. Antes do Hall of Fame — cobertura de férias

Manter estas falas para quem encontra a casa antes do arco. Elas não são repetidas depois do início da investigação.

#### `OlivineCity_House1_Text_LookerHoliday`

```text
LOOKER
A fine place for a holiday!

Though I seem to be spending rather
more time indoors than planned.
```

#### `OlivineCity_House1_Text_AnabelHoliday`

```text
ANABEL
It's peaceful here.

Looker keeps finding reasons
to check the telephone.
```

A cobertura tem uma pequena fissura, sem Anabel anunciar a mentira para qualquer visitante.

### 5.2. Chegada após a ligação

Jogador entra em `(4,8)`. Looker vai de `(4,5)` para `(4,7)`; Anabel vai de `(7,5)` para `(5,7)`. Ambos encaram o sul. Os trajetos herdados podem ser mantidos, sem cruzamento entre os dois.

Falar diretamente com um deles quando o briefing estiver pendente entrega o mesmo conteúdo, sem repetir movimentos de entrada incompatíveis com a posição do jogador.

#### `OlivineCity_House1_Text_BriefingWelcome`

```text
LOOKER
{PLAYER}! Thank you for coming.
I'm afraid the holiday is over.

This is Anabel. She's in charge
of our investigation.
```

#### `OlivineCity_House1_Text_BriefingAnabel`

```text
ANABEL
We've been tracking distortions
in Johto.

They resemble the Ultra Wormholes
we encountered in Alola.
```

#### `OlivineCity_House1_Text_BriefingWormholes`

```text
ANABEL
Passages to other worlds.
Sometimes Pokémon come through them.

We call those Pokémon Ultra Beasts.
They can be dangerous when displaced.
```

#### `OlivineCity_House1_Text_BriefingBlackthorn`

```text
LOOKER
Clair called from Blackthorn.
An unfamiliar Pokémon is in the street.

She's keeping it away from the houses,
but the readings are rising.
```

#### `OlivineCity_House1_Text_BriefingRequest`

```text
ANABEL
We need your help protecting the town.
And, if we can, the Pokémon too.

Meet us by the Pokémon Center.
Bring a team ready for a difficult battle.
```

**Encenação:** após a fala, ambos retornam às posições da sala. Não anunciar Gladion, as espécies das UBs ou a identidade de Necrozma com base apenas numa descrição telefônica.

### 5.3. Orientação repetível

#### `OlivineCity_House1_Text_LookerGoAhead`

```text
LOOKER
The Pokémon Center in Blackthorn.
We'll meet you there.
```

#### `OlivineCity_House1_Text_AnabelGoAhead`

```text
ANABEL
Prepare your team before you join us.
Clair is holding the street.
```

Sem afirmar simultaneamente que irão atrás e chegarão antes. A presença no destino é resolvida pelo estado existente do evento.

## 6. Ato III — Blackthorn antes da aproximação

Cidade evacuada, Centro disponível. A população não reaparece antes da resolução. Clair e Kingdra mantêm o olhar na ameaça mesmo durante interações opcionais.

### 6.1. Portas fechadas

#### `BlackthornCity_Text_DoorLocked`

```text
NOTE
Stay inside until the street is clear.
—Clair
```

O som/estado da porta comunica que está trancada. Não é necessária outra caixa de narração antes do bilhete.

### 6.2. Anabel

#### `BlackthornCity_Text_UBAnabelIdle`

```text
ANABEL
The residents are indoors.
The Center is still open.

Speak with Looker when you're ready.
```

**Família Cosmog:** retirar a antiga extensão opcional. A reação fica concentrada no momento posterior à absorção, com o Pokémon mostrado de verdade. Isso evita repetir a mesma advertência antes e depois da luta e mantém a primeira observação compreensível mesmo com o follower oculto.

### 6.3. Clair

Não virar para o jogador. Uma breve pausa no olhar ou um gesto basta para reconhecer a aproximação.

#### `BlackthornCity_Text_UBClairIdle`

```text
CLAIR
{PLAYER}. Stay behind Kingdra.

Every time it moves toward the houses,
we push it back.

The detectives are by the Center.
Speak to them first.
```

Ela está ocupada, não hostil. Não sabe por que a criatura está ali e não afirma que está esperando, que não oferece perigo ou que é invulnerável.

### 6.4. Kingdra

Cry curto; mantém a posição, de frente para Necrozma.

#### `BlackthornCity_Text_UBKingdraIdle`

```text
NARRATOR
Kingdra holds its ground.
```

### 6.5. Criatura desconhecida

Não dar o nome ao jogador por uma plaquinha de espécie antes da identificação narrativa. A caixa é descritiva, identificada como `NARRATOR`.

#### `BlackthornCity_Text_UBNecrozmaIdle`

```text
NARRATOR
Light gathers along the black crystal,
then fades inside it.
```

O objeto permanece vigiado por Kingdra. Não criar combate ou atração adicional aqui. A antiga reação opcional à Ball é removida: o primeiro interesse claro pelo parceiro acontecerá durante a cena principal.

## 7. Ato IV — Pronto para entrar

Looker recebe o jogador de `(25,52)`.

### `BlackthornCity_Text_UBLookerGreet`

```text
LOOKER
There you are.
Clair has kept the street clear for us.

We'll move up together.
```

### Bloqueio de espaço — só quando necessário

Preservar a checagem antecipada de **equipe e PC simultaneamente cheios**, devido ao presente existente. Não comentar quando há espaço e não exigir uma vaga na equipe se o PC pode receber.

#### `BlackthornCity_Text_UBNoRoom`

```text
LOOKER
Your team and Boxes are full.
Please make room for one Pokémon first.
```

Essa única mensagem substitui a explicação sobre uma regra moral de Anabel. Não revelar o presente. A condição não inicia a cena nem altera seu progresso.

### `BlackthornCity_Text_UBReady`

```text
LOOKER
Are you and your Pokémon ready?
```

Menu **Yes / No** com plaquinha LOOKER mantida.

### `BlackthornCity_Text_UBNotReady`

```text
LOOKER
The Center is just up the street.
We'll wait here.
```

**Yes:** começa a aproximação. Não repetir cumprimento ou briefing.

## 8. Ato V — A ruptura e o reforço

Ocultar o follower comum, preservando a informação necessária para restaurá-lo. Durante a cena, os Pokémon narrativos são atores próprios, com visibilidade controlada. Não presumir que ocultar o follower já fornece um ator para Solgaleo/Lunala.

### Beat 1 — Aproximação

| Ator | Movimento herdado |
| --- | --- |
| Jogador | `(25,52)` → `(20,50)`: subir 2, esquerda 5, olhar oeste |
| Looker | `(25,53)` → `(25,52)`: subir 1, olhar oeste |
| Anabel | `(26,53)` → `(26,52)`: subir 1, olhar oeste |

Clair vira brevemente para leste, reconhecendo quem chegou.

#### `BlackthornCity_Text_UBClairArrive`

```text
CLAIR
Champion already? Good.
I could use the help.
```

Necrozma inclina-se na direção das casas. Clair volta a olhar oeste **antes** da ordem.

#### `BlackthornCity_Text_UBClairAttack`

```text
CLAIR
Kingdra! Dragon Pulse!
```

Kingdra ataca; Necrozma recua de `(14,50)` para `(13,50)`, mantendo o olhar leste. Um pulso de luz percorre seu corpo. Após uma pausa curta, volta a `(14,50)`.

#### `BlackthornCity_Text_UBClairHeld`

```text
CLAIR
It keeps coming back.
Kingdra, hold there.
```

**Efeito dramático:** Clair consegue conter, mas não resolver. O golpe tem resultado visível; ela não desperdiçou uma hora atacando sem efeito.

### Beat 2 — Abertura

Anabel observa o instrumento. O tema local começa a sair. Não antecipar sua condição de Faller por explicação nesta missão.

#### `BlackthornCity_Text_UBRiftWarning`

```text
ANABEL
The distortion is growing.
Everyone, leave room to fall back.
```

Necrozma ergue os braços; o efeito de ruptura surge ao lado dele. A trilha de ameaça entra **antes de revelar Buzzwole e Pheromosa**. Um flash curto, cries separados e tempo suficiente para ler as duas silhuetas.

#### `BlackthornCity_Text_UBAppear`

```text
ANABEL
Buzzwole and Pheromosa.
Two Ultra Beasts!
```

### Beat 3 — Duas maneiras de avançar

Buzzwole avança com passos firmes por `y=50`, de `(15,50)` até `(18,50)`. Pheromosa dá uma pausa curta, vira para a lateral e avança rapidamente por `y=51`, de `(15,51)` até `(18,51)`.

A diferença de ritmo e de linha deve ser vista. Não mover ambos como uma formação sincronizada; Blackthorn não estabelece mente coletiva.

#### `BlackthornCity_Text_UBChargeWarning`

```text
LOOKER
{PLAYER}, on your left!
```

O jogador vira sul para acompanhar Pheromosa. Imediatamente começa a entrada de Silvally; não manter a ação suspensa para outra explicação.

### Beat 4 — Silvally intercepta

Silvally entra de `(19,44)` até `(19,50)` pela coluna 19, utilizando o salto herdado para os últimos dois tiles. Gladion desce a coluna 20 até `(20,49)`.

Silvally encara oeste e intercepta Buzzwole, que recua até `(17,50)`. Em seguida vira sul e faz um avanço curto no lugar em direção à frente lateral; Pheromosa interrompe sua corrida e recua até `(17,51)`.

Não afirmar que um único golpe derrubou as duas. Buzzwole é repelido; Pheromosa perde a abertura. Silvally termina olhando oeste. O jogador também retorna explicitamente ao oeste.

#### `BlackthornCity_Text_UBGladionArrives`

```text
GLADION
Stay with me, Silvally.

{PLAYER}. You all right?
```

Jogador vira norte para Gladion e faz um gesto breve de confirmação; volta a oeste. Não escrever uma fala para o protagonista se ele permanece silencioso no projeto.

### Beat 5 — Identificação sem retenção artificial

Gladion vê Necrozma claramente por cima da linha das UBs; uma pausa curta e olhar oeste. Ele o reconhece da experiência de Alola adotada pelo arco híbrido. Isso não lhe dá conhecimento do novo comportamento.

#### `BlackthornCity_Text_UBNecrozmaNamed`

```text
GLADION
Necrozma. What's it doing here?
```

#### `BlackthornCity_Text_UBAnabelFocus`

```text
ANABEL
Keep the Ultra Beasts away from the houses.
We'll deal with Necrozma next.
```

Não interromper o resgate para perguntar o nome ou as credenciais de Gladion. Looker pode apresentá-lo pelo nome depois de ouvi-lo no rescaldo.

### Beat 6 — Divisão dos alvos

#### `BlackthornCity_Text_UBChoosePrompt`

```text
GLADION
Pick one, {PLAYER}.
Silvally and I will take the other.
```

#### `BlackthornCity_Text_UBClairCover`

```text
CLAIR
I'll keep Necrozma back.
Go!
```

Menu **Buzzwole / Pheromosa**. Durante a escolha, plaquinha GLADION, pois é ele quem faz a pergunta. A cena comprometida mantém a regra existente de não cancelar com B. A escolha vale pela tentativa.

#### `BlackthornCity_Text_UBPickedBuzzwole`

```text
GLADION
Silvally, watch Pheromosa.
Don't let it get around us.
```

#### `BlackthornCity_Text_UBPickedPheromosa`

```text
GLADION
We'll hold Buzzwole here.
Take the opening.
```

O jogador mantém o olhar no alvo; Silvally reage ao alvo de Gladion. A formação de Clair não é desmontada para produzir outra fala.

### Beat 7 — Boss

Batalha contra a UB escolhida. Manter números, itens, golpes e escalonamento do documento de implementação; esta revisão não altera balanceamento.

Captura durante a batalha permanece bloqueada. A ligação que impede a contenção será mostrada imediatamente após a primeira vitória; ninguém conhece antecipadamente essa regra.

A batalha de ameaça mantém derrota real e recuperação. Não usar o contrato de duelo narrativo dos encontros de campanha. No retorno, restaurar **trilha de ameaça**, atores e olhares antes da próxima fala.

## 9. Ato VI — O que a vitória revela

### Beat 1 — Gladion conclui sua frente

Um ataque curto de Silvally encerra a contenção da outra UB. A criatura continua no chão/posição enfraquecida; não removê-la. Se o asset não tiver pose caída, usar um gesto de recuo e imobilidade, sem descrever uma pose inexistente.

#### Se o jogador enfrentou Buzzwole: `BlackthornCity_Text_UBGladionFoughtPheromosa`

```text
GLADION
Pheromosa's stopped.
Stay there, Silvally.
```

#### Se o jogador enfrentou Pheromosa: `BlackthornCity_Text_UBGladionFoughtBuzzwole`

```text
GLADION
Buzzwole's down.
Good work, Silvally.
```

### Beat 2 — Primeira tentativa de contenção

Anabel dá um passo à frente, de `(26,52)` para `(26,51)`, e prepara uma Ball de contenção do equipamento policial. Não chamá-la de Beast Ball especial nem introduzir Kurt nesta cena. A Ball do clímax permanece uma preparação posterior.

#### `BlackthornCity_Text_UBContainment`

```text
ANABEL
Keep clear. I'll try to secure it.
```

Ela lança a Ball na direção da UB que o jogador derrotou. Um filamento da ruptura ainda a alcança. Quando a contenção começa, o filamento pulsa e a Ball é repelida intacta. A UB permanece visível. O item é da NPC: nada é consumido do inventário do jogador.

#### `BlackthornCity_Text_UBContainmentFailed`

```text
ANABEL
The rift pulled it back.
It's still connected!
```

A dedução é local: Anabel acaba de observar o efeito. Não declara imunidade universal a Poké Balls.

**Dependência nova de encenação:** trajetória e tentativa precisam existir visualmente. Não substituir por uma caixa afirmando que aconteceu. Um efeito simples de Ball e pulso direcional basta; não é necessário criar uma batalha de captura extra.

### Beat 3 — A absorção

Necrozma pulsa. As duas UBs começam a ser puxadas de `(17,50/51)` para `(15,50/51)`, voltadas para leste. Um pequeno gesto contrário ao arrasto distingue serem recolhidas de voltarem voluntariamente.

#### `BlackthornCity_Text_UBAbsorbedClair`

```text
CLAIR
It's pulling them in!
Kingdra, break that light!
```

Kingdra ataca a ligação; Gladion avança um gesto com Silvally. A ligação se estreita e as duas UBs são absorvidas pelo corpo de Necrozma antes que os ataques rompam o filamento. Somente os atores das UBs desaparecem; Necrozma permanece visível para o pulso e a reação seguinte. O grupo tentou impedir; a surpresa não é uma desculpa para todos ficarem parados.

Um pulso deixa Necrozma mais luminoso. Logo em seguida, a luz oscila e a borda da ruptura treme. Essa segunda parte é obrigatória: planta o problema maior mesmo sem parceiro na party.

#### `BlackthornCity_Text_UBAbsorbedGladion`

```text
GLADION
It took both of them.
I've never seen it do that.
```

#### `BlackthornCity_Text_UBAbsorbedAnabel`

```text
ANABEL
The reading spiked...
Now it's fluctuating again.
```

Silêncio curto para observar o efeito. Ninguém confirma que as criaturas morreram ou sobreviveram. Ninguém afirma que Necrozma planejou usar o jogador.

### Beat 4 — Reação opcional do parceiro

Reavaliar a equipe **depois da batalha**, porque pode ter ocorrido evolução. Cada ramo acontece uma vez por execução da cena, sem nova condição de acesso à missão.

#### Ramo A — sem família Cosmog

Necrozma encara a ruptura, que continua oscilando. Ir diretamente à retirada. Todas as pistas obrigatórias já foram mostradas.

#### Ramo B — Cosmog ou Cosmoem

A Ball reage; o jogador a segura. Em um efeito breve, o Pokémon aparece em `(19,51)`, encarando oeste. Se já era follower antes da cena, reutilizar sua identidade no ator, sem duplicação.

Necrozma vira para ele e avança de `(14,50)` para `(15,50)`. Silvally mantém a cobertura entre Necrozma e o jogador.

##### `BlackthornCity_Text_UBNecrozmaSensesCosmog`

```text
GLADION
It noticed your {STR_VAR_1}.
Keep it behind Silvally.
```

O parceiro recua/oscila no lugar conforme seu sprite permite. Não fica diante de Silvally; a posição `(19,51)` é lateral à cobertura, não uma corrida até Necrozma. Não dizer que Cosmoem anda se o asset apenas flutua.

Necrozma hesita e volta a olhar a ruptura instável. Não explicar sua intenção.

#### Ramo C — Solgaleo ou Lunala

**Antes de qualquer fala:** a Ball abre, o parceiro surge em `(19,51)` e encara a ruptura. Cry e pulso próprio. O filamento da ruptura reduz a oscilação por um instante. Necrozma vira para o parceiro, avança um passo até `(15,50)` e para.

##### `BlackthornCity_Text_UBNecrozmaSensesLegend`

```text
ANABEL
The rift steadied when
{STR_VAR_1} came out.
```

O parceiro sustenta o olhar; a borda volta a oscilar. Não resolve a ruptura nesta missão. Gladion acompanha o movimento de Necrozma e mantém Silvally pronto, sem afirmar medo ou reconhecimento como certeza.

##### `BlackthornCity_Text_UBLegendCover`

```text
GLADION
Easy, Silvally.
Keep it away from them.
```

**Se ambos estiverem na party:** representar somente um, selecionado de forma consistente pela ordem da party. Registrar a escolha para a cena; não trocar de espécie no meio das falas. Usar cry, forma e aparência correspondentes.

### Beat 5 — Retirada

Necrozma volta-se para a abertura. A luz pulsa de novo, mas não estabiliza. Ele atravessa; a ruptura se fecha atrás dele. Não deixar a retirada parecer uma nova absorção das casas ou um teleporte do elenco inteiro.

#### `BlackthornCity_Text_UBNecrozmaGone`

```text
CLAIR
Hold your positions.
Make sure it's gone.
```

Anabel confere o instrumento. Pausa curta, sem falso alarme adicional.

#### `BlackthornCity_Text_UBStreetClear`

```text
ANABEL
The opening has closed.
The street is clear.
```

Agora a trilha de ameaça termina. Um intervalo curto e retorno suave ao tema local. Se houve parceiro em cena, o jogador se volta para ele e o recolhe **visivelmente** antes da aproximação do grupo e do presente.

## 10. Ato VII — Pessoas, evidência e próximo passo

### Beat 1 — Reagrupar

Looker vai de `(25,52)` para `(21,50)`: subir 2, esquerda 4, olhar oeste.

Anabel está agora em `(26,51)` por causa da tentativa de contenção. **Seu novo trajeto é esquerda 4 até `(22,51)`**, olhando oeste. Não reaproveitar o movimento antigo com uma subida adicional.

Movimentos sequenciais, Looker primeiro. Clair/Kingdra olham leste; Gladion olha sul; o jogador olha leste para os policiais. Silvally continua acompanhando a rua até a ameaça ser declarada encerrada.

#### `BlackthornCity_Text_UBAftermathLooker`

```text
LOOKER
Everyone all right?

Take a moment. I'll check the houses.
```

Looker dá uma olhada na direção das casas; sua inspeção completa acontece na transição de resolução. Não sai atravessando a formação durante a conversa.

#### `BlackthornCity_Text_UBAftermathClair`

```text
CLAIR
You kept them off the houses.
Both of you. Thank you.
```

#### `BlackthornCity_Text_UBAftermathGladion`

```text
GLADION
Gladion.
We were coming down from Route 45.
```

A apresentação curta responde naturalmente ao agradecimento de Clair. Não pedir que Gladion reconte sua chegada.

#### `BlackthornCity_Text_UBAftermathClairReturn`

```text
CLAIR
I'll check the rest of town, Gladion.
Kingdra, with me.
```

Clair vira para Kingdra; ambos se orientam para a cidade. A saída ou reposicionamento deve usar rota validada no mapa. Até a transição final, podem permanecer na frente norte, em gesto de inspeção; não inventar deslocamento por portas bloqueadas.

### Beat 2 — O que Gladion sabe

Anabel olha para Gladion; ele vira para leste para responder. O jogador acompanha a troca olhando norte/leste conforme necessário.

#### `BlackthornCity_Text_UBAftermathQuestion`

```text
ANABEL
You called it Necrozma.
What do you know about it?
```

#### `BlackthornCity_Text_UBAftermathNecrozma`

```text
GLADION
It absorbs light. It caused trouble
in Alola, too.

Taking Ultra Beasts like that?
That's new.
```

#### `BlackthornCity_Text_UBAftermathInference`

```text
ANABEL
Then it may be taking their energy.
We don't know what happened to them yet.
```

#### `BlackthornCity_Text_UBAftermathPlan`

```text
ANABEL
The rift kept them connected.
Next time, we need to break that link.
```

Esta é a ponte para Mahogany: a barreira e o teste de Lillie responderão a um problema já observado. Anabel não conhece ainda a interação elétrica específica nem a localização seguinte.

#### `BlackthornCity_Text_UBAftermathLookerPlan`

```text
LOOKER
I'll compare this with our Alola records.
Gladion, may I take your account?
```

#### `BlackthornCity_Text_UBAftermathGladionAgrees`

```text
GLADION
Yes. I'll tell you what I remember.
```

Sem “later” para suspender um dado essencial. A conversa técnica completa pode ocorrer fora da cena; a cooperação já foi aceita e a informação central entregue.

### Beat 3 — Nota opcional sobre o parceiro

Somente o ramo ocorrido na cena tem retorno. O ator já foi recolhido; estas falas relembram o que todos viram, não descrevem uma ação acontecendo invisivelmente agora.

#### Cosmog/Cosmoem — `BlackthornCity_Text_UBAftermathCosmog`

```text
ANABEL
Necrozma approached when your
{STR_VAR_1} appeared.

If it reacts again, let us know.
```

#### Solgaleo/Lunala — `BlackthornCity_Text_UBAftermathLegend`

```text
ANABEL
Your {STR_VAR_1} affected the rift.
Only for a moment, but I recorded it.
```

Não acrescentar outra advertência de Gladion repetindo a mesma conclusão. Não dizer que o parceiro é imune a Necrozma ou a causa dos incidentes.

## 11. Ato VIII — Type: Null

A rua está segura. A música é de rescaldo/local. Dar um pequeno intervalo antes do presente, para não parecer uma recompensa policial imediata pelas UBs perdidas.

### Beat 1 — Gladion chama o jogador

Jogador olha norte, para Gladion. Gladion olha sul.

#### `BlackthornCity_Text_UBGladionGiftIntro`

```text
GLADION
Before you go, there's a Pokémon
I'd like you to meet.
```

Silvally vai de `(19,50)` para `(18,50)` e vira leste, abrindo espaço. Gladion libera **outro Type: Null** em `(19,49)`, voltado ao sul. Os dois Pokémon ficam visíveis juntos, tornando inequívoca a diferença de indivíduos.

#### `BlackthornCity_Text_UBGladionGiftFound`

```text
GLADION
I brought it with me from Alola.
It needed someone to look after it.

Silvally helped it get used to traveling.
We've been training beyond Route 45.
```

**Origem revisada para o hack:** este indivíduo já estava sob os cuidados de Gladion em Alola e veio com ele para Johto. A Route 45 é onde o grupo treinava, não onde surgiu por coincidência outro Pokémon artificial abandonado. Esta versão substitui a origem anterior; não afirmar que é uma nova criação, que existem exemplares selvagens na rota ou que Gladion abandonou seu próprio parceiro. A história de como começou esse cuidado pode ficar fora desta cena: o motivo de estar em Johto e a responsabilidade atual já estão definidos.

Type: Null olha para Silvally e então para o jogador. Gladion não dá ordem.

### Beat 2 — Iniciativa própria

Type: Null desce até `(19,50)` e vira leste, ficando ao lado do jogador em `(20,50)`. O jogador vira oeste para ele. Cry baixo ou gesto curioso apropriado ao asset; sem menu de escolha novo.

#### `BlackthornCity_Text_UBGladionGiftTrust`

```text
GLADION
It usually stays close to Silvally.

Huh. It seems comfortable with you.
```

Pausa curta. Gladion olha para o jogador.

#### `BlackthornCity_Text_UBGladionGiftOffer`

```text
GLADION
I've seen how you treat your Pokémon.
I'd trust you to look after it.

Take it with you.
```

O protagonista responde com gesto de aceitação. O ato de aproximar-se mostra conforto inicial; não afirmar que o Pokémon decidiu todo o seu futuro porque observou uma batalha de dentro da Ball.

### Beat 3 — Entrega

Preservar **Type: Null, nível 50**, apelido e destino automático para equipe/PC conforme o fluxo de presentes do projeto.

Primeiro confirmar que a entrega foi aceita pelo sistema. Depois recolher/remover o ator temporário de Type: Null e apresentar a confirmação. Não remover o ator e avançar progresso se a entrega falhar.

#### Confirmação — texto equivalente do helper existente

```text
SYSTEM
{PLAYER} received Type: Null!
```

Aviso de PC, apelido e demais mensagens do helper também precisam da identificação correspondente. Não duplicar a confirmação se o helper já a produz.

### `BlackthornCity_Text_UBGladionGiftAfter`

```text
GLADION
Give it time.
Let it come to you.
```

Gladion olha brevemente para Silvally; Silvally volta a seu lado. A relação demonstra a origem do conselho sem uma explicação sobre “a lição do meu arco”.

### Guarda inesperada de espaço

A checagem inicial deve evitar este caso. Se a entrega ainda falhar, **não repetir a batalha nem apagar a vitória**. Manter o presente pendente e preservar uma forma de falar com Gladion para concluir somente a entrega.

#### `BlackthornCity_Text_UBGiftNoRoom`

```text
GLADION
Your team and Boxes are full.
Make room. I'll keep it with me until then.
```

O Type: Null retorna a Gladion e é recolhido. O contrato de pendência precisa ser implementado explicitamente no mecanismo existente ou em estado dedicado; este roteiro não inventa um ID de flag disponível.

#### `BlackthornCity_Text_UBGiftRetry`

```text
GLADION
Ready to take Type: Null with you?
```

Essa pergunta só aparece na retomada da entrega, com espaço já verificado. Não reabrir o duelo de UBs, a absorção ou o relatório. Após sucesso, seguir para a despedida ainda pendente ou a conclusão curta, conforme o estado real.

## 12. Ato IX — Gancho

Jogador olha leste para Looker. A formação de saída deixa a rua livre; nenhuma pessoa aparece em cima do parceiro ou do Type: Null, já recolhidos.

### `BlackthornCity_Text_UBHookAnabel`

```text
ANABEL
The distortion hasn't fully cleared.
We'll keep monitoring it.
```

### `BlackthornCity_Text_UBHookLooker`

```text
LOOKER
Get some rest, {PLAYER}.
We have some notes to compare.

I'll call when we have a lead.
```

### `BlackthornCity_Text_UBHookGladion`

```text
GLADION
You held your side.
Good.

Come on, Silvally.
```

Gladion e Silvally se orientam para sair juntos. A saída pode terminar sob o fade de resolução herdado; não colocar um percurso longo antes do encerramento.

**Conclusão normal:** resolver a flag de incidente e chegar ao estado 4 conforme o contrato existente. Cidade repovoada, portas liberadas, actors temporários removidos, follower restaurado uma única vez, jogador em posição segura. A próxima localização será anunciada na ligação de convocação; o briefing em Olivine apresenta o plano. Nenhuma nova missão é ativada apenas ao encerrar esta cena.

**Exceção da entrega pendente:** não limpar a única representação de Gladion antes de garantir o mecanismo de retomada. A cidade pode ser considerada salva independentemente da entrega; separar esses dois resultados no código.

## 13. Recuperação e branches que também precisam de texto

### 13.1. Derrota na batalha de ameaça

Respeitar o retorno seguro/blackout do sistema. A derrota não marca a missão como concluída. No retorno à linha, restaurar a formação e permitir nova escolha do alvo.

#### `BlackthornCity_Text_UBRetryGreeting`

```text
LOOKER
Clair and Gladion are holding them back.
How are your Pokémon?
```

#### `BlackthornCity_Text_UBRetryReady`

```text
ANABEL
Ready to try again?
```

**Yes:** retomar a formação e a escolha de UB. A implementação deve ter um checkpoint que diferencie primeira apresentação de retry. Não repetir telefonema, reconhecimento da Clair, identificação de Necrozma ou entrada surpresa de Gladion como se ninguém se conhecesse.

**No:**

#### `BlackthornCity_Text_UBRetryNotReady`

```text
ANABEL
Heal at the Center first.
We'll hold here.
```

Não dizer que as UBs fugiram se continuam na rua. Não produzir falas pós-derrota antes que o motor termine sua própria recuperação.

### 13.2. Resultado não resolvido sem blackout

Se o motor devolver fuga, interrupção ou outro resultado sem vitória, manter missão pendente. Adaptar a retomada ao que de fato ocorreu; não relatar derrota se houve apenas interrupção.

#### `BlackthornCity_Text_UBUnresolved`

```text
ANABEL
They're still here.
Regroup before we try again.
```

Resultados desconhecidos não executam absorção, presente ou conclusão. O script técnico deve mapear os resultados reais da versão atual antes de ligar estas falas.

### 13.3. Retorno a Olivine após concluir Blackthorn

A conclusão de Blackthorn habilita a espera pela convocação de Mahogany. A próxima chamada exige a resolução da missão e do presente, nenhum convite anterior pendente e um dia em que Looker ainda não tenha ligado. Se a chamada de Blackthorn ocorreu hoje, concluir a missão hoje não autoriza uma segunda ligação. O limite usa mudança de dia do calendário do jogo, não 24 horas desde a última chamada.

Antes da convocação de Mahogany, interagir na base usa:

#### `OlivineCity_House1_Text_WaitForMahoganyCall`

```text
LOOKER
We're still checking the reports.
I'll call when we have a lead.
```

Depois da chamada, o briefing de Mahogany substitui a espera. Depois do briefing, usar a orientação para Mahogany. Não manter o comando de voltar a Blackthorn e não oferecer o próximo briefing antecipadamente.

Se Looker ainda não ligou naquele dia e a missão anterior já terminou, chamar no primeiro momento de controle livre, fora de batalha, menu, diálogo, transição e da própria base. Estar dentro da base adia a ligação até a saída; não consome a chamada. O convite já emitido persiste entre dias e saves. Não repetir telefone para um retry.

A transição assume que **Necrozma já foi identificado** e que a ligação das UBs à ruptura já foi observada.

Contrato compartilhado com Mahogany V3:

- Looker comparou os registros de Alola.
- Anabel procura como interromper a ligação.
- Lillie traz observações específicas do novo encontro.
- A sobrevivência das UBs surge como evidência nova, não como certeza herdada de Blackthorn.
- A identidade de Necrozma não volta a ser segredo.

## 14. Trilha e efeitos por trecho

| Ponto | Áudio/efeito | Quando termina |
| --- | --- | --- |
| Telefone e escritório | Ambiente normal do sistema/mapa | Transição habitual |
| Rua antes da cena | Ambiente contido; pode manter tema local até a aproximação | Aviso da ruptura |
| Anabel percebe aumento | Fade curto do tema local | Antes da aparição |
| UBs aparecem | Tema de ameaça; proposta herdada `MUS_DP_LEGEND_APPEARS` | Somente após rua declarada segura |
| Boss | Tema de batalha definido pelo sistema | Retorno retoma ameaça |
| Tentativa de captura | Som de lançamento e resposta da ligação | Sem fanfarra de captura |
| Absorção | Pulso direcional e breve tremor | Manter ameaça |
| Parceiro aparece | Efeito de saída da Ball + cry correto | Sem trocar para música triunfal |
| Necrozma parte | Fechamento da ruptura, pausa curta | Confirmação de Anabel |
| Presente | Fanfarra do presente, uma vez | Retomar tema local |

Confirmar habilitação e reprodução da faixa no build atual. Não afirmar que o nome da constante garante áudio disponível.

O roteiro herdado especifica `fadescreenswapbuffers` para flashes por causa de um problema de tint noturno. Preservar essa orientação na integração, sem reintroduzir `fadescreen` para os mesmos flashes. Testar dia e noite; não aumentar flashes para compensar falta de movimento legível.

## 15. Mudanças de coreografia a integrar

| Trecho | Mudança | Dependência |
| --- | --- | --- |
| Clair ataca | Necrozma recua 1 tile e retorna | Conferir `(13,50)` e orientação travada |
| Carga das UBs | Ritmos distintos, com lateral de Pheromosa | Não usar uma única chamada simultânea para ambas |
| Resgate | Silvally interrompe a frente e depois a lateral | Olhares sul/oeste explícitos; jogador retorna oeste |
| Contenção | Anabel sobe para `(26,51)` e lança Ball | Efeito novo; alvo depende da escolha do jogador |
| Absorção | Kingdra e Silvally tentam interromper | Ordem curta que não interrompe o arrasto |
| Ruptura oscila | Pulso depois do ganho de luz | Obrigatório em todos os ramos |
| Parceiro | Ator em `(19,51)` nos ramos da família | Cry/gráfico/identidade reais, sem follower duplicado |
| Rescaldo | Novo trajeto de Anabel: esquerda 4 | Não aplicar o antigo movimento a partir de outra posição |
| Presente | Silvally libera `(19,50)` indo a `(18,50)` | UBs e Necrozma já removidos |
| Type: Null | Surge em `(19,49)`, desce e olha jogador | Parceiro do jogador já recolhido |
| Retry | Retoma escolha com Gladion já presente | Checkpoint a integrar; não alegar pronto |
| Falha de entrega | Retoma somente presente | Estado persistente de pendência a definir no código |

As labels de texto foram separadas quando havia múltiplos falantes. **Não fazer substituição cega por nome de label:** atualizar chamadas e transições de plaquinha no `.pory`/`.inc`, incluindo remoção das extensões opcionais antigas.

## 16. Pistas para o arco maior

| Pista em Blackthorn | Leitura permitida agora | Desenvolvimento posterior |
| --- | --- | --- |
| Necrozma abre a passagem | Ele participa ativamente da ocorrência | Investigar por que e onde essas conexões se concentram |
| Ligação repele tentativa de contenção | Esta UB ainda está conectada à ruptura | Mahogany testa uma interrupção física da ligação |
| Duas UBs são absorvidas | Foram recolhidas; destino desconhecido | Mahogany detecta sinais persistentes; New Bark amplia a evidência |
| Luz aumenta e volta a oscilar | A absorção não tornou o sinal estável | Olivine formula a diferença entre potência e estabilidade |
| Gladion conhece Necrozma, mas estranha a absorção | Informação anterior é útil e incompleta | Lusamine acrescenta conhecimento sem monopolizar a resposta |
| Solgaleo/Lunala estabiliza brevemente, quando presente | Há uma interação observada | Reunião demonstra e testa a função para todos os jogadores |
| Type: Null se aproxima por iniciativa própria | Gladion dá espaço ao parceiro | Sua confiança no jogador contrasta com o controle de Lusamine |

Nenhuma fala de Blackthorn explica antecipadamente o resgate das nove, a origem do altar ou a estratégia completa de captura de Necrozma.

## 17. Conferência para implementação

- [ ] Chamada inicial registra a data compartilhada e nunca sobrepõe a chamada de Elm.
- [ ] Concluir Blackthorn no dia da chamada não dispara Mahogany nesse dia.
- [ ] Antes da convocação seguinte, Olivine oferece espera; depois, oferece briefing.
- [ ] Despedida pede que o jogador aguarde a ligação; convite não expira.
- [ ] Type: Null veio com Gladion de Alola; Route 45 é local de treinamento.
- [ ] Somente as UBs somem na absorção; Necrozma continua visível.
- [ ] Ligação, briefing e todos os ramos têm plaquinha correta acima da caixa.
- [ ] Nenhum texto contém `NONE` como falante ou nome embutido como substituto da plaquinha.
- [ ] Clair reconhece o protagonista e seu ataque tem efeito visível.
- [ ] UBs avançam de maneiras diferentes; não sugerem mente coletiva.
- [ ] Gladion identifica Necrozma e compartilha informação útil nesta missão.
- [ ] Falas curtas durante ação; conversa mais longa somente após segurança.
- [ ] Tentativa de contenção e absorção são mostradas, não apenas narradas.
- [ ] A oscilação após absorção aparece mesmo sem família Cosmog na equipe.
- [ ] Solgaleo/Lunala sai da Ball antes de sua reação ser descrita.
- [ ] Cosmog/Cosmoem, Solgaleo, Lunala, ambos e ausência têm branches coerentes.
- [ ] O parceiro é recolhido antes do presente; não ocupa o espaço de outro ator.
- [ ] Pós-batalha mantém música de ameaça e reinicializa o falante.
- [ ] Looker e Anabel não cruzam tiles ocupados no rescaldo.
- [ ] Type: Null do presente é visivelmente distinto do Silvally de Gladion.
- [ ] Presente vai para equipe ou PC; checagem silenciosa quando cabe.
- [ ] Falha inesperada da entrega não apaga a vitória nem repete o boss.
- [ ] Retry usa texto próprio e não repete descobertas como novidades.
- [ ] Encerramento restaura população, portas, follower e posição segura.
- [ ] Atualizar o briefing de Mahogany para a identificação antecipada e a nova pista da ligação.
- [ ] Medir linhas com nomes reais e testar trilha, visibilidade e flashes à noite.

## 18. Fechamento da auditoria V3

Integrados: convocação diária desde a primeira ligação; despedida e espera de Olivine; absorção sem desaparecimento acidental de Necrozma; origem do segundo Type: Null ligada à viagem de Gladion; confiança apoiada na relação da campanha; pequeno retorno do humor de Looker fora da emergência. Permanecem os contratos de nomes, parceiro visível, trilha, presente pendente e retry sem repetir descobertas.

**Entrega desta revisão:** roteiro e contratos de cena. Importação, build, novas animações e validação em jogo continuam pendentes.
