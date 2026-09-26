# Altar do Sol e da Lua — o caminho de volta

**Roteiro reconstruído V2 · 25/09/2026**

**Status:** substituição narrativa integral do roteiro anterior, pronta para revisão e integração. Falas originais em inglês; direção em português. Este documento não altera a ROM nem certifica correção de bugs. Blackthorn V3, Mahogany V3, Cherrygrove V2, New Bark V2 e Pré-Necrozma V2 governam a continuidade. Os registros técnicos antigos ajudam a localizar a implementação; não prevalecem sobre a história revisada.

**Escopo completo:** porto, chegada, impasse, exploração do Altar, duelo de Lusamine e seus resultados, abertura/teste da passagem, travessia, boss, recuperação, resgate das nove UBs, captura de Necrozma, estabilização, despedida, conversas opcionais, transporte e pós-game. Labels abaixo são propostas de integração; confirmar símbolos e chamadas reais antes de importar.

## 1. O que esta versão encerra

Necrozma vem puxando luz pelas rupturas e mantendo nove Ultra Beasts presas ao seu fluxo. Cada absorção aumentou seu poder sem resolver a instabilidade. A equipe protegeu as cidades e reuniu evidências suficientes para chegar à origem do fenômeno. Agora dispõe de uma passagem sustentada, retirada organizada e pessoas preparadas para receber os Pokémon.

Lusamine trouxe equipamento, compartilhou registros e ensinou Anabel a usá-lo. Ainda quer assumir a travessia. O conflito é aceitar entregar a etapa de maior risco a outra pessoa, permanecendo responsável por uma parte indispensável do resgate. Lillie e Gladion precisam que ela trabalhe com eles. A mudança se completa quando Lusamine escuta uma instrução da filha durante a operação e a cumpre.

**Linha dramática:** chegar e preparar → discordar sobre quem atravessa → duelo → acordo → testar a passagem → enfrentar Ultra Necrozma → libertar as nove → capturar Necrozma → estabilizar juntos → reencontro familiar pequeno e concreto.

Não repetir a reunião inteira. Não apresentar a fome como revelação: Gladion já explicou a absorção de luz em Blackthorn. O que o final resolve é por que obter mais luz nunca bastava, como recuperar as criaturas e como interromper o ciclo.

## 2. Regra absoluta: nome acima de TODAS as caixas

A primeira linha de cada bloco `text` deste documento identifica a **plaquinha acima da message box**. Não é uma linha que será impressa dentro do diálogo. Cada bloco contém um único falante. Cada página mantém sua identificação; cada mensagem seguinte a declara de novo pelo mecanismo real do projeto.

| Conteúdo | Plaquinha |
| --- | --- |
| Personagens | LOOKER, ANABEL, LUSAMINE, LILLIE, GLADION, KUKUI, SAILOR |
| Notificação, escolha técnica de parceiro, recebimento, envio ao PC, apelido | SYSTEM |
| Narração, somente se indispensável | NARRATOR |
| Bilhete, se houver futura inclusão | NOTE |

Neste roteiro, movimentos, luz, cries e expressões ficam na direção de cena; não recebem caixas de narração redundantes. Menu mantém o nome de quem fez a pergunta, exceto a seleção técnica de parceiro, que usa SYSTEM. Falas por comunicador usam o nome real do interlocutor; o canal é indicado por som/retrato/efeito, sem transformar o nome em uma variável improvisada.

**Nunca:** `NONE`, campo vazio, `LUSAMINE:` dentro do corpo como substituto da plaquinha, nome herdado por acidente, ou nome do parceiro reutilizado como identidade de um humano.

### Retorno da batalha de Lusamine — contrato específico do bug

A causa do nome corrompido não foi comprovada nesta revisão. A integração precisa:

1. Salvar o resultado da batalha antes de cura, menus ou helpers.
2. Restaurar o estado de batalha sem blackout e a interface de diálogo.
3. Definir explicitamente **LUSAMINE** antes da primeira fala de cada resultado, incluindo fala de derrota dentro da batalha quando aplicável.
4. Definir explicitamente **LILLIE**, **GLADION**, **ANABEL** ou **LOOKER** ao mudar o interlocutor. Não depender do último treinador carregado pelo motor.
5. Manter o identificador do falante separado de buffers de espécie, apelido, item e resultado. Reconstruir cada buffer no ponto de uso.
6. Reaplicar a identificação após cura, fanfarra, fade e menu. Conferir paginação também.
7. Testar vitória, derrota, empate, desistência, retorno inesperado e revanche de pós-game. Nenhum desses ramos pode herdar o nome do boss ou do parceiro.

Escrever os nomes no Markdown estabelece o contrato; a correção só estará concluída após integração e teste na ROM.

## 3. Vozes, emoção e callbacks

As vozes foram revistas usando as seções dos jogos principais nas páginas de falas listadas ao final. SM e USUM são referências distintas; a continuidade híbrida de SoulGold escolhe o que aconteceu. Masters, anime e fusão com Nihilego não são incorporados por associação.

| Personagem | Direção de escrita nesta cena |
| --- | --- |
| Lusamine | Precisa e formal, acostumada a assumir o controle. Frases mais curtas quando perde a segurança. Demonstra afeto ao permanecer disponível e perguntar; não faz um discurso sobre ter aprendido a amar. |
| Lillie | Gentil, observadora e firme. Pede algo concreto à mãe e mantém seu papel no resgate. Não volta a pedir desculpas por cada decisão. |
| Gladion | Direto e protetor. Confia no jogador e protege a retaguarda. Seu afeto aparece quando aceita ficar mais um pouco com a família. |
| Anabel | Comando calmo, instruções claras e preocupação concreta. Opera o retorno; não comenta o gênero da cena, a própria utilidade ou a interface do jogo. |
| Looker | Caloroso e profissional, humor discreto quando cabe. Organiza transporte, comunicação e acolhimento; tem trabalho durante todo o evento. |
| Kukui | Entusiasmado com uma observação real, vocabulário de batalha e incentivo. Cada intervenção acrescenta uma leitura ou instrução. Não fala por metáforas sobre portas, agulhas ou cosmologia. |

**Callbacks usados:** falha de contenção em New Bark; nove sinais de Elm; equipamento e Ball apresentados na reunião; confiança entre Gladion e jogador já construída na campanha. São acontecimentos obrigatórios conhecidos pelos interlocutores.

**Callbacks removidos:** frases supostamente ditas na entrega do ovo; quatro anos de correspondência com Kurt; anos exatos de carreira; idade inventada de Lusamine; Kukui presente em Blackthorn; Pokémon do jogador chamado de Nebby; parceiro sempre presente nas missões. Nada exige que um ramo opcional anterior tenha ocorrido.

## 4. Regras de Necrozma e dos equipamentos

Regras autorais desta continuidade, não alegações de mecânica canônica:

- Necrozma já está **Ultra** quando o grupo o encontra. A forma continua oscilando, como em New Bark. Não há nova transformação provocada pelo parceiro.
- As nove UBs permanecem ligadas a ele. O boss representa o desgaste da energia acumulada. Vencê-lo rompe esse vínculo e permite que elas voltem a se separar fisicamente.
- O confronto agora tem retirada e apoio preparados. Não existem outras UBs livres na arena para uma nova absorção durante a luta. A energia acumulada é finita; a batalha reduz essa reserva. Não anunciar imunidade, enfraquecimento automático ou garantia de vitória.
- O **estabilizador de passagem**, apresentado na reunião, tem base externa e módulo interno. Exige operação contínua, mantém a rota já aberta e permite seu ajuste. Não ataca Necrozma, extrai UBs ou cria luz infinita.
- O **campo de contenção de New Bark** interrompia filamentos locais. Não é o estabilizador. Não atribuir suas funções a este aparelho nem exigir seu retorno sem encenação.
- Solgaleo/Lunala abre e sustenta a passagem junto dos operadores. Não alimenta Ultra Necrozma, não desaparece da equipe e não se funde com ele.
- A derrota libera as UBs; o parceiro e o equipamento sustentam a saída. Essas funções são diferentes e aparecem em ações diferentes.
- A captura retira Necrozma da arena depois do resgate. Não estabiliza todas as rupturas instantaneamente. Essa estabilização será mostrada no Altar, com Necrozma e o parceiro atuando juntos.
- A melhora é local e observável: o Altar e as conexões ligadas a ele deixam de oscilar violentamente. Não afirmar cura definitiva de Necrozma nem segurança universal de Ultra Space.

A sequência de estados herdada permanece 12 → 13 → 14 → 15 → 16. Os checkpoints de tentativa e de entrega pendente precisam de representação persistente adequada na implementação; não inventar IDs livres.

## 5. Espaço, atores e câmera

Preservar como referências o cais em `(14,27)`, terraço, escadaria de acesso, disco e abertura de chão em torno de `(14,10)`. A formação antiga não pode ser reutilizada cegamente: agora há equipamento, área de acolhimento e Pokémon retornando.

| Zona | Uso |
| --- | --- |
| Disco e passagem | Parceiro abre a rota; manter o tile da abertura desocupado antes de criá-la |
| Lateral do terraço | Base externa, Lusamine e Kukui; acesso sem atravessar o portal |
| Corredor de saída | Gladion/Silvally; passagem contínua até a área de acolhimento |
| Área de acolhimento | Lillie/Ninetales; receber uma ou duas UBs de cada vez |
| Apoio e cais | Looker, provisões, comunicação e transporte |
| Arena | Ultra Necrozma à frente; jogador com espaço de batalha; parceiro lateral; Anabel ao lado do módulo interno |

A arena herdada possui corredor `x=9..11`, chegada em `(10,19)` e frente próxima de `y=11`, com Necrozma em `(10,8)`. Usar esses pontos apenas após conferir layout, sprites, metatiles e visibilidade. O módulo fica fora do corredor de retirada. O parceiro precisa de um ponto que deixe livre a trajetória das UBs até o portal.

**Orçamento:** nunca mostrar nove UBs simultaneamente. Receber em grupos de até duas, registrar o grupo e conduzi-lo à área protegida antes do seguinte. A transição entre mapas não deve esconder o fato do resgate. Se o terraço não comportar Stakataka, Celesteela e Guzzlord em segurança, ampliar/remapear localmente a área de acolhimento. Não reduzir sprites ou fazê-los atravessar paredes para caber.

Ninetales e Silvally continuam fora da Ball junto dos treinadores. Ocultar o follower durante a cutscene, representando o parceiro escolhido por um único ator; restaurá-lo uma vez ao devolver controle. Em todo ramo: saída da Ball → posição → olhar/ação → recolhimento visível. Pokémon não age enquanto só existe no texto.

Durante conversa livre, instrumentos ficam desligados e não há ninguém preso mantendo uma passagem por horas. A operação ativa começa após a confirmação de travessia. Não inventar cronômetro congelado durante menus.

## 6. Porto e viagem

A reunião V2 entrega o passe. Reutilizar acesso persistente e transporte nos dois sentidos, em qualquer horário. Sem nova ligação ou espera diária.

### `OlivinePort_Text_AltarAsk`

```text
SAILOR
The ship for the Sun and Moon Altar
is ready. Shall we set sail?
```

Menu Yes/No, SAILOR. Se também houver Faraway Island, preservar o menu de destinos existente e seus acessos; nome SAILOR permanece. Cancelar não altera progresso.

### `OlivinePort_Text_AltarDepart`

```text
SAILOR
All aboard!
```

### `OlivinePort_Text_AltarStay`

```text
SAILOR
I'll be here when you're ready.
```

Se o fluxo exibe o passe:

### `OlivinePort_Text_AltarPass`

```text
SYSTEM
{PLAYER} showed the Sun & Moon Ticket.
```

**Compatibilidade:** manter a recuperação antiga de passe somente para save cuja liberação anterior esteja comprovada, sem contornar o teste da reunião V2. Não dar passe a quem apenas chegou ao estado 11.

### `OlivinePort_Text_AltarPassRecovery`

```text
SAILOR
Looker left your pass with me.
Here you are.
```

Helper de entrega com SYSTEM; confirmar sucesso e não duplicar item. O desembarque deixa jogador fora do warp e com caminho livre à escada.

## 7. Ato I — chegada e preparação (12 → 13)

Cena uma vez ao subir a escadaria. Looker encontra o jogador; os demais já estão montando a operação. Não começar com narração do disco: mostrar o movimento irregular, poeira levantando perto dele e pulsos fracos. Trilha de preparação; a ameaça cresce quando a abertura responder.

### `SunMoonAltar_Text_ArrivalLooker`

```text
LOOKER
There you are. The ship will stay.
We've brought supplies for the Pokémon.
```

Câmera mostra a área de acolhimento, dois auxiliares de transporte Aether/polícia junto dos suprimentos no acesso inferior, e depois a base externa. Os auxiliares são apoio visual sem novas falas ou biografias; saem do enquadramento antes das cenas cheias e reaparecem nos cortes de acolhimento. Lusamine ajusta controles; Kukui observa o indicador. Lillie e Gladion estão em seus postos, com parceiros visíveis.

### `SunMoonAltar_Text_ArrivalKukui`

```text
KUKUI
Same pulse as New Bark.
Strong, then unsteady.

Let's see how the passage responds
before we take anyone through.
```

Anabel coloca o módulo portátil ao lado da base e confere a comunicação. Ela não usa a condição de Faller para identificar o mundo do outro lado.

### `SunMoonAltar_Text_ArrivalAnabel`

```text
ANABEL
I'll take the inside unit.
We need someone at these controls here.
```

Lusamine termina o ajuste antes de responder. Não ignorou o plano da reunião: concordou em testar o equipamento, mas a liderança da travessia ainda estava aberta.

### `SunMoonAltar_Text_ArrivalLusamine`

```text
LUSAMINE
Professor Kukui can operate this unit.
I'll go with you.
```

### `SunMoonAltar_Text_ArrivalKukuiLimit`

```text
KUKUI
I can keep it running.
If it drifts, I'll need your help.
```

Lusamine olha para o módulo que Anabel carrega.

### `SunMoonAltar_Text_ArrivalLusamineInsists`

```text
LUSAMINE
And if the inside unit fails?
I cannot repair it from here.
```

### `SunMoonAltar_Text_ArrivalAnabelPlan`

```text
ANABEL
Then we withdraw.
You showed me how to do that.

{PLAYER} handles Necrozma.
You keep our return clear.
```

A resposta reconhece a competência que Lusamine compartilhou na reunião. Ela sabe por que a proposta faz sentido e ainda resiste ao risco.

### `SunMoonAltar_Text_ArrivalLusamineFear`

```text
LUSAMINE
I saw what it did in New Bark.
I cannot simply send you in there.
```

Lillie deixa Ninetales junto à área preparada e se aproxima pelo lado livre.

### `SunMoonAltar_Text_ArrivalLillie`

```text
LILLIE
Mother, we're asking you to help us
bring them back.

I need you here with me.
```

Lusamine olha para a filha. Uma pausa curta; não responder com toda a história de Alola.

### `SunMoonAltar_Text_ArrivalLusamineChildren`

```text
LUSAMINE
I know.
I wanted you both far from all this.
```

### `SunMoonAltar_Text_ArrivalGladion`

```text
GLADION
We're here because we chose to help.
Let us.
```

Lusamine volta ao equipamento, sem sair da conversa. Não sobe ao disco para fazer greve silenciosa.

### `SunMoonAltar_Text_ArrivalLusaminePause`

```text
LUSAMINE
{PLAYER}. Speak with me before you go.
```

### `SunMoonAltar_Text_ArrivalLookerRelease`

```text
LOOKER
We'll finish setting up.
Come to me if your team needs care.
```

Devolver controle no estado 13, fora da escada/warp. Base desligada; disco instável, mas sem operação de travessia iniciada. Ativar o destino de Fly conforme integração existente, sem alterar progresso da reunião.

**Se o parceiro está ausente:** esta conversa continua possível; nenhuma ação invisível dele acontece. A presença será exigida antes do duelo que leva à abertura. Isso preserva liberdade de preparação e evita uma convergência sem Pokémon capaz de abrir a rota.

## 8. Conversas livres antes do duelo

### `SunMoonAltar_Text_LillieBefore`

```text
LILLIE
Ninetales and I will meet them here.
They may be frightened when they come out.

I hope Mother will stay beside us.
```

### `SunMoonAltar_Text_GladionBefore`

```text
GLADION
Silvally knows these creatures.
We'll keep the exit clear.

You won't have to fight your way back.
```

Gladion promete sua tarefa, não invulnerabilidade nem resgate automático em qualquer mundo.

### `SunMoonAltar_Text_KukuiBefore`

```text
KUKUI
Your partner steadied the equipment
in Olivine. That was a good start.

This time we'll test both ends.
```

### `SunMoonAltar_Text_AnabelBefore`

```text
ANABEL
I've checked the inside unit.
If the signal drops, we come back.
```

Looker oferece a cura descrita na seção 18. Lusamine usa a conversa de desafio abaixo. Parceiros de NPCs podem emitir cry ao interagir; se houver mensagem, usar plaquinha da espécie devidamente resolvida, nunca texto sem nome.

## 9. Ato II — o duelo de Lusamine

Falar com Lusamine no estado 13. Ela se volta de fato para o jogador. A conversa é particular o suficiente para não soar como um julgamento conduzido pelos filhos.

### `SunMoonAltar_Text_DuelApproach`

```text
LUSAMINE
They trust you.
I've seen why.

Still... I would rather face it myself
than watch you go.
```

Pausa. Ela fecha o estojo de ferramentas e prepara a Ball de sua equipe.

### `SunMoonAltar_Text_DuelAsk`

```text
LUSAMINE
Will you battle me, {PLAYER}?
I want to face you properly
before I leave this to you.
```

Menu Yes/No, LUSAMINE. A luta expressa sua dificuldade de confiar; não é autorização policial nem prova de que o vencedor tem razão.

### `SunMoonAltar_Text_DuelDeclined`

```text
LUSAMINE
Of course. Take your time.
```

Recusa não altera estado, não desloca elenco e permite sair. Na próxima interação, usar apenas a pergunta, sem repetir a aproximação longa caso haja suporte de visita apropriado.

### Preparação antes do aceite efetivo

Checar parceiro elegível na equipe: Solgaleo ou Lunala, não ovo. Com ambos, escolha SYSTEM; manter a identidade escolhida nesta execução. Sem elegível, a luta ainda não começa:

### `SunMoonAltar_Text_DuelPartnerMissing`

```text
LUSAMINE
Bring Solgaleo or Lunala with you.
We'll need your partner for the passage.
```

### `SunMoonAltar_Text_PartnerSelect`

```text
SYSTEM
Which Pokémon will open the passage?
```

Menu Solgaleo/Lunala/Not now. `Not now` devolve controle sem duelo, custo ou mudança de estado. Espécie pode liberar o evento independentemente da origem individual do ovo; não afirmar procedência não comprovada.

### `SunMoonAltar_Text_DuelAccept`

```text
LUSAMINE
Thank you.
Let's give them a proper battle.
```

Curar antes da luta pelo helper, mensagens eventuais com SYSTEM. Recolher atores que ficariam sobre a área de batalha sem sumir com parceiros permanentes arbitrariamente. Preservar equipe e balanceamento definidos no projeto: não rebalancear nesta revisão.

**Duelo narrativo:** sem blackout e sem penalidade de derrota. Salvar resultado imediatamente; restaurar configuração anterior de no-whiteout. Curar ambos os resultados normais antes da operação. Vitória, derrota, empate e desistência têm falas próprias e convergem. Resultado técnico desconhecido mantém estado 13 e não inventa conclusão.

### Derrota da treinadora na batalha — `SunMoonAltar_Text_DuelLusamineBeaten`

```text
LUSAMINE
Well fought.
```

### Jogador venceu — `SunMoonAltar_Text_DuelWon`

```text
LUSAMINE
You earned that victory.
I'll leave Necrozma to you.
```

### Jogador perdeu — `SunMoonAltar_Text_DuelLost`

```text
LUSAMINE
This battle was mine.
Let's take care of your Pokémon.
```

Executar cura; não interromper a fala fingindo que já aconteceu. Depois, LUSAMINE explicitamente novamente:

### `SunMoonAltar_Text_DuelLostAfterCare`

```text
LUSAMINE
And we still need someone here
who can bring you back.
```

A derrota não apaga as quatro missões vencidas nem muda quem tem o parceiro da travessia. O grupo não decide a operação por placar de treino.

### Empate — `SunMoonAltar_Text_DuelDrew`

```text
LUSAMINE
Neither team has anything left.
They've done enough. Let them rest.
```

### Desistência — `SunMoonAltar_Text_DuelForfeited`

```text
LUSAMINE
All right. We'll stop here.
Let me see to your Pokémon.
```

Não elogiar uma manobra específica que o motor não garante, nem chamar desistência de vitória. Curar e seguir à conversa comum.

### Resultado técnico inesperado — `SunMoonAltar_Text_DuelUnexpected`

```text
LUSAMINE
Let's stop for now.
Speak to me when you're ready.
```

Restaurar controles, equipe conforme contrato seguro e estado 13. Esta é recuperação de implementação, não resultado dramático secreto.

## 10. Ato III — ficar e ajudar (13 → 14)

A convergência ocorre depois da cura, com todos em segurança e o equipamento ainda desligado. Lillie se aproxima; Ninetales acompanha até um tile que não bloqueie os controles. Gladion permanece com a saída à vista.

### `SunMoonAltar_Text_AgreementLillie`

```text
LILLIE
Mother, come and check the receiving area
with me.
```

Lusamine olha para o espaço preparado, depois para a filha.

### `SunMoonAltar_Text_AgreementLusamine`

```text
LUSAMINE
You really want me beside you?
```

### `SunMoonAltar_Text_AgreementLillieAnswer`

```text
LILLIE
Yes.
But please listen when I need your help.
```

Lusamine deixa o módulo portátil com Anabel e caminha até a base externa. **Essa é a decisão.** Não há abraço obrigatório, choro repentino ou declaração de perdão.

### `SunMoonAltar_Text_AgreementLusamineStay`

```text
LUSAMINE
I will.
Show me where you want them to come through.
```

Lillie indica o corredor de acolhimento; Lusamine verifica a distância e ajusta a orientação da base conforme indicado. Gladion abre espaço junto de Silvally.

### `SunMoonAltar_Text_AgreementGladion`

```text
GLADION
I'll keep that side clear.
```

Anabel volta-se para o jogador.

### `SunMoonAltar_Text_AgreementAnabel`

```text
ANABEL
We're ready to test the passage.
Bring your partner forward.
```

### Abertura visível

Revalidar o parceiro depois da batalha; reconstruir identidade e nome. Mostrar saída da Ball, cry e orientação ao disco. O jogador fica ao lado, sem ocupar a futura abertura. Um pulso do parceiro faz o disco responder; a passagem de chão se abre e oscila. A base externa acompanha o pulso, sem criar o portal sozinha.

### `SunMoonAltar_Text_OpeningKukui`

```text
KUKUI
There it is!
Hold that steady, {STR_VAR_1}.
```

Kukui acompanha os indicadores; Lusamine ajusta a base. Anabel atravessa apenas até a borda interna com o módulo, visível num corte curto da arena, e confirma a ligação. O parceiro permanece sustentando a boca externa; Anabel volta imediatamente após a leitura. Ainda não avança até Necrozma nem dispara boss.

### `SunMoonAltar_Text_OpeningAnabelTest`

```text
ANABEL
Both units are responding.
The way back is clear.
```

### `SunMoonAltar_Text_OpeningLusamine`

```text
LUSAMINE
The outside signal is steady too.
We can close the test.
```

Anabel volta com o módulo; Lusamine reduz a base, parceiro encerra o pulso. A abertura se contrai até uma marca dormente reconhecível no chão, sem passagem ativa. Recolher o parceiro visivelmente.

### `SunMoonAltar_Text_OpeningLooker`

```text
LOOKER
Speak with Anabel by the passage
when you're ready to go.
```

**Estado 14:** acordo e teste concluídos. Livre preparação; ninguém precisa sustentar uma abertura ativa enquanto o jogador visita o PC. A marca de chão é o ponto de interação, não um portal pronto que funciona sem parceiro. Ao confirmar a partida, reabrir pela mesma ação breve. Não repetir duelo ou conversa familiar.

Se houver falha de implementação entre duelo válido e teste, preservar o acordo e retomar somente a preparação; não exigir a luta novamente. Esse checkpoint deve ser integrado ao estado persistente apropriado.

## 11. A travessia — checagens discretas

Interação com Anabel/marca de chão no estado 14. Ordem: verificar espaço → verificar parceiro → escolher entre os dois se necessário → prontidão. **Quando houver espaço, nenhuma fala comenta party, PC, captura futura ou regra moral de ter uma vaga.** Equipe cheia sozinha não impede; PC pode receber.

### Somente equipe E PC lotados — `SunMoonAltar_Text_RiftNoRoom`

```text
ANABEL
Your team and Boxes are full.
Make room for one Pokémon before we go.
```

Uma caixa. Devolver controle, sem abrir passagem nem alterar progresso. Não repetir esse assunto em nenhuma conversa normal.

### Sem Solgaleo/Lunala na equipe — `SunMoonAltar_Text_RiftNoPartner`

```text
ANABEL
Bring Solgaleo or Lunala in your team.
We need your partner to open the passage.
```

Não apagar passe, Fly, acordo ou teste. O Pokémon no PC não satisfaz a travessia. Não presumir que Cosmog ainda não evoluiu sem consulta que comprove isso.

### Prontidão — `SunMoonAltar_Text_RiftAsk`

```text
ANABEL
Ready, {PLAYER}?
I'll keep the inside unit running.
You take Necrozma.
```

Yes/No, ANABEL.

### `SunMoonAltar_Text_RiftNotYet`

```text
ANABEL
All right. We'll be here.
```

Aceite: representar o parceiro; reabrir a passagem; base externa ativa; Anabel transporta módulo; Looker confere comunicação. Retomar sem novas instruções longas.

### `SunMoonAltar_Text_RiftLooker`

```text
LOOKER
I can hear you clearly, Chief.
We're ready to receive them.
```

### `SunMoonAltar_Text_RiftLusamine`

```text
LUSAMINE
The outside unit is ready.
```

Lillie olha o jogador antes de ele atravessar.

### `SunMoonAltar_Text_RiftLillie`

```text
LILLIE
We'll be waiting for you too, {PLAYER}.
```

Parceiro atravessa primeiro, jogador depois, Anabel por último; base mantém o intervalo de transição. Usar movimentos e warp compatíveis; nenhuma cópia fica no Altar. Na arena, estabelecer módulo interno e parceiro junto da rota antes de aproximar o jogador da ameaça.

## 12. Ato IV — Ultra Necrozma

A entrada começa com Ultra Necrozma já visível à distância, dourado e instável. Não fazer a forma normal aparecer antes. A luz ao redor dele cresce e falha; nove padrões no instrumento continuam reconhecíveis, sem nove personagens simultâneos na tela.

A trilha de ameaça acompanha a revelação. O jogador para na frente segura; o parceiro ocupa a lateral da rota; Anabel posiciona o módulo interno, deixa seu estojo de apoio ao alcance e testa a resposta externa. O enquadramento mostra seu trabalho antes de justificar por que ela não luta.

### `UltraSpaceArena_Text_AnabelFound`

```text
ANABEL
Necrozma. The nine signals are still here.
```

Ultra Necrozma tenta puxar luz da borda instável. Ela se distorce, mas o parceiro recupera sua forma com um pulso breve. Não desenhar um feixe nutritivo do parceiro até Necrozma.

### `UltraSpaceArena_Text_AnabelProtectPartner`

```text
ANABEL
Keep Necrozma away from your partner.
We need that passage open.
```

O jogador assume a frente. Ultra Necrozma volta-se para ele; o parceiro mantém a passagem sem ser sacrificado, capturado ou removido da equipe jogável.

### `UltraSpaceArena_Text_AnabelAtControls`

```text
ANABEL
I'll hold the return steady.
We get the others out when its grip weakens.
```

Anabel segura o módulo e ajusta os controles quando os indicadores oscilam. Sem poder novo de Faller, telecinese humana ou fala de inutilidade. Seu lugar na cena explica sua ausência como parceira de batalha.

### `UltraSpaceArena_Text_BattleStart`

```text
ANABEL
Now, {PLAYER}!
```

**Boss de ameaça:** preservar perfil vigente, dificuldade e fases do projeto; referência herdada: cinco barras, nível 90, multiplicador 160%, fases Ultra → normal conforme energia se esgota. Conferir implementação real antes de usar números. Não recriar três barras Ultra depois de o combate já exibir normal. Captura bloqueada durante a batalha; derrota exige retry.

O parceiro continua elegível no time como no sistema anterior. Não criar bloqueio de seleção, consumo de HP por script ou imunidade: sua atuação no overworld não equivale a uma segunda entidade combatendo. Durante a batalha o módulo mantém a rota; o ator do parceiro só retoma ações após a transição. Na vitória, sua capacidade de ajudar é restaurada explicitamente pelo apoio descrito a seguir, inclusive se desmaiou no combate.

## 13. Vitória — separar, receber, conferir

Ao retornar, sincronizar o ator com o resultado: somente Necrozma normal, enfraquecido, no ponto da criatura. O halo Ultra se desfaz; filamentos começam a se desprender. Não interpretar tamanho de sprite como transformação numa criatura minúscula diferente.

### `UltraSpaceArena_Text_VictoryAnabel`

```text
ANABEL
The links are separating.
Looker, get everyone ready.
```

### `UltraSpaceArena_Text_VictoryLooker`

```text
LOOKER
We're ready. Bring them through.
```

**Parceiro após combate:** Anabel trata o parceiro ao alcance de sua posição, com uma mão mantendo o controle e a outra aplicando o tratamento do estojo de apoio. Mostrar esse estojo junto do módulo na preparação da arena. Lusamine continua operando a base externa. Executar o helper real antes de pedir outro pulso; não dizer que Anabel abandonou o equipamento nem introduzir autonomia temporária do aparelho. A direção não exige deslocamento ou cura do time inteiro durante a retirada.

### `UltraSpaceArena_Text_PartnerCare`

```text
ANABEL
One moment, {STR_VAR_1}.
Let me help you.
```

Executar restauração necessária do parceiro selecionado (HP e condições que impediriam a ação); não inventar special existente. Se a implementação só oferece cura completa segura, executá-la explicitamente como apoio da equipe. O efeito termina e a plaquinha seguinte é reaplicada.

### `UltraSpaceArena_Text_PartnerReturn`

```text
ANABEL
Good. Keep the opening steady.
```

Parceiro assume o pulso. Necrozma não ataca durante esse trecho: está vencido e perdeu a forma Ultra. Seu estado de vitória é preservado antes de qualquer entrega.

### Resgate mostrado em cinco passagens

Filamentos desprendidos se condensam em UBs ao lado de Necrozma, uma ou duas por vez. As criaturas recuperam forma **antes** de atravessar. Cada saída interna tem uma chegada externa correspondente. Não usar a captura de Necrozma como explicação retroativa para o resgate.

| Grupo | Dentro da arena | No Altar |
| --- | --- | --- |
| Buzzwole e Pheromosa | Reaparecem separados, param, percebem a saída livre | Silvally mantém distância e bloqueia somente o acesso às pessoas; segue o corredor livre |
| Xurkitree e Celesteela | Luz própria fraca, sem circuito de recarga; atravessam em sequência | Kukui mantém aparelhos/cabos fora do alcance e orienta a passagem maior |
| Blacephalon e Stakataka | Um clarão fraco, passos de Stakataka visíveis | Lillie pede pausa para evitar amontoamento; Lusamine mantém a abertura enquanto o corredor é liberado |
| Kartana e Guzzlord | Saídas separadas dentro do mesmo grupo | Gladion conduz a equipe para o lado seguro; retirar obstáculos frágeis do percurso antes |
| Nihilego | Última a se separar, deriva pela rota estável | Lillie/Ninetales oferecem espaço; Lusamine impede que a abertura se contraia antes da passagem completa |

Não supor que todas obedecem a comandos humanos. A saída é o espaço estável e livre; o elenco se afasta e orienta o ambiente, sem domesticação instantânea. Na área protegida, equipe de apoio Aether/polícia, preparada por Looker e mostrada brevemente junto aos suprimentos antes do resgate, faz acolhimento em contenção temporária apropriada. Não entregar nove Pokémon ao jogador nem deixá-los vagando sobre o cais. Se usados recipientes/Balls de transporte, mostrar seu uso após o acolhimento, sem confundir com a Beast Ball reservada de Necrozma. A representação concreta e os assets devem ser integrados antes de importar as confirmações.

### Primeiro grupo — `SunMoonAltar_Text_RescueGladion`

```text
GLADION
Silvally, give them room.
Keep this side clear.
```

Mostrar os dois primeiros passando e sendo recebidos. Som de confirmação do registro de Looker; não abrir uma caixa para cada contagem.

### Grupo grande — `SunMoonAltar_Text_RescueKukui`

```text
KUKUI
Celesteela needs more room.
Clear the middle!
```

Kukui afasta um suporte já mostrado, sem abandonar a base; Looker conduz apoio pelo trajeto preparado. Celesteela nunca atravessa um objeto sólido.

### O pedido de Lillie — `SunMoonAltar_Text_RescueLillieWait`

```text
LILLIE
Wait, Mother. Stakataka hasn't cleared it.
Keep it open a little longer.
```

Lusamine tinha a mão no ajuste para estreitar a abertura entre grupos. Para, olha a criatura e segue a filha.

### `SunMoonAltar_Text_RescueLusamineWait`

```text
LUSAMINE
All right. Tell me when it's through.
```

Stakataka conclui a passagem; Lillie acompanha, sem tocar na UB por intimidade inventada.

### `SunMoonAltar_Text_RescueLillieClear`

```text
LILLIE
It's clear now.
Thank you.
```

Lusamine ajusta só então. Esse pequeno gesto paga a conversa anterior: a filha pede, a mãe escuta, algo concreto dá certo.

### Última — `SunMoonAltar_Text_RescueNihilego`

```text
LILLIE
This way. There's room.
Ninetales, stay beside me.
```

Lillie fala em voz baixa, não como se Nihilego entendesse inglês. Ninetales mantém distância; a criatura segue o corredor. Não fazer Lusamine tocá-la ou reivindicá-la.

### Confirmação — `UltraSpaceArena_Text_AllNineSafe`

```text
LOOKER
All nine are through.
We're checking them now.
```

**Contagem:** confirmação exige nove chegadas registradas, não a soma das missões na memória. Não garantir que estejam ilesas. Durante cortes externos, a arena segue como cutscene comprometida; volta sem reiniciar boss ou duplicar atores. A operação só é considerada concluída após todos os grupos, captura e retorno.

## 14. Captura de Necrozma (14 → 15)

Necrozma permanece normal. Tenta erguer-se e para; a luz já não recebe os nove filamentos. Anabel observa primeiro. A captura estava planejada antes da viagem; não é descoberta improvisada nem adoção por pena.

### `UltraSpaceArena_Text_CaptureAnabel`

```text
ANABEL
Now Necrozma.
We can take it out of here.
```

Anabel passa ao jogador a Beast Ball mostrada na reunião, mantendo-se junto do módulo. Animar mão/lançamento curto entre eles ou apoio em estojo ao alcance, conforme assets. Não dar a Ball à mochila para depois exigir que o jogador a tenha comprado ou fabricado.

### `UltraSpaceArena_Text_CaptureBall`

```text
ANABEL
Here. Kurt's Beast Ball.
```

O jogador aproxima-se pelo corredor seguro; Necrozma acompanha seu movimento. Não acrescentar narração que atribua pensamentos ou diga que nunca foi cuidado na vida.

### Captura visual obrigatória

1. Última checagem silenciosa de capacidade, antes da animação irreversível.
2. Jogador lança a Beast Ball; trajetória legível da sua posição até Necrozma.
3. Necrozma vira luz e entra na Ball, usando animação compatível com o objeto real.
4. Ball cai no ponto de captura e permanece como ator/efeito próprio.
5. Balanços visíveis curtos, som sincronizado e clique final. Se o asset não tiver frames de balanço, deslocamento curto no lugar; não afirmar animação que ainda não foi integrada.
6. Fanfarra no clique. Confirmar registro e destino do Pokémon antes de avançar estado.
7. Entregar **Necrozma normal, nível 75, em Beast Ball**, uma única vez. Validar a Ball armazenada nos dados, não apenas a aparência da cena.
8. Remover ator da Ball depois da confirmação. Não dar Solgaleo/Lunala nem modificar a identidade do parceiro.

### `UltraSpaceArena_Text_CaptureConfirmed`

```text
SYSTEM
{PLAYER} caught Necrozma!
```

Helper de apelido e aviso de PC também usam SYSTEM. Usar uma única confirmação final, sem duplicar a mensagem genérica de presente. Rebufferizar explicitamente Necrozma antes de qualquer helper: `{STR_VAR_1}` pode ter sido usado para o parceiro. O documento antigo registra um anúncio incorreto de SOLGALEO causado por reutilização; conferir também a espécie efetivamente entregue.

### `UltraSpaceArena_Text_CaptureReturn`

```text
ANABEL
Let's take you both back.
```

A fala é para jogador e Necrozma capturado; parceiro também atravessa visivelmente. Anabel recolhe o módulo após a sequência segura de retorno: parceiro sustenta a passagem durante a retirada interna; base externa permanece ativa. Ninguém remove o último suporte antes de quem o opera sair.

**Estado 15:** boss vencido, nove resgatadas, Necrozma recebido, retorno/despedida pendentes. Voltar ao Altar em tile seguro fora da boca da passagem. Não requerer Necrozma na party: pode ter ido ao PC.

### Falha inesperada de entrega — preservar tudo que já aconteceu

A guarda inicial deve impedir lotação, mas um erro não apaga a vitória. Não repetir boss, resgate ou captura concluída. Manter uma pendência persistente distinguindo vitória, resgate e registro de Necrozma. Se não há espaço na última checagem, Anabel recolhe Necrozma na Ball de missão para transporte, mantendo-o sob custódia até entregar ao jogador. O objeto não é perdido ao sair do mapa.

### `UltraSpaceArena_Text_CapturePending`

```text
ANABEL
I'll keep Necrozma with me for now.
Make room, then speak to me at the altar.
```

Mostrar a captura de custódia uma vez e retornar. Na retomada, confirmar capacidade e entregar somente Necrozma; sem nova animação de captura, sem novo boss. Se a falha for um retorno técnico inesperado do helper, preservar pendência sem afirmar sucesso. O fechamento espera a entrega confirmada, com a instabilidade mantida sob controle pela equipe.

### `SunMoonAltar_Text_CapturePendingRetry`

```text
ANABEL
Ready to take Necrozma with you?
```

Yes/No, ANABEL. Espaço ainda ausente usa somente a caixa de bloqueio de espaço. Sucesso usa SYSTEM e segue ao retorno pendente. Os subestados necessários não existem por serem descritos aqui: implementá-los e testá-los antes de considerar esse fluxo pronto.

## 15. Ato V — retorno, luz estável e família (15 → 16)

### Primeiro, quem voltou

Looker se aproxima pela lateral, deixando o portal livre. Lillie confere o último registro de acolhimento; Gladion/Silvally mantêm a passagem desobstruída. Lusamine continua na base externa até Anabel confirmar o retorno.

### `SunMoonAltar_Text_ReturnLooker`

```text
LOOKER
There you are!
Are you hurt?
```

Jogador confirma com gesto; Anabel pousa o módulo em segurança.

### `SunMoonAltar_Text_ReturnAnabel`

```text
ANABEL
We're all back.
Thank you for keeping it steady.
```

Lusamine solta o controle apenas depois de ver a base em manutenção segura e todos do lado de fora. Sem comentário sobre quarenta minutos ou um dia inteiro sem dados de tempo.

### `SunMoonAltar_Text_ReturnLillie`

```text
LILLIE
All nine, {PLAYER}.
Nihilego was the last one through.
```

Lillie olha para a área de acolhimento. O jogador vê o registro concluído e um Pokémon já recebido à distância, conforme orçamento; não nove sprites amontoados.

### Estabilização de verdade

A abertura ainda oscila, embora menos. Kukui nota um pulso vindo da Ball de Necrozma **antes do envio definitivo ao PC**. A sequência de entrega deve permitir essa saída de cena mesmo se o destino final for o PC: representar o mesmo indivíduo recém-capturado, mantendo seu registro, sem criar outro Pokémon nem alterar a composição final da equipe. Se o helper já o enviou, preparar uma apresentação temporária que referencie aquele indivíduo e devolva-o ao destino registrado ao terminar. Não exigir retirada manual para fechar a história.

### `SunMoonAltar_Text_ReturnKukui`

```text
KUKUI
Necrozma's reacting to the opening.
Let's give it room.
```

Jogador libera Necrozma em ponto protegido, com Ball e cry; parceiro já está visível ou sai da Ball antes de agir. Lusamine mantém a base, Anabel fica perto do jogador. Ninguém manda Necrozma executar um golpe que não possui.

O parceiro reduz a oscilação da passagem. Necrozma se volta para a luz espalhada em pequenos filamentos ao redor do disco; esses filamentos convergem para ele. Sua luz pulsa mais devagar. O parceiro sustenta a borda enquanto esse fluxo se reorganiza; não transfere sua própria luz ao corpo de Necrozma.

### `SunMoonAltar_Text_ReturnAnabelObserve`

```text
ANABEL
The loose light is drawing back.
Keep the passage steady.
```

Necrozma recolhe somente o fluxo residual. Nenhuma UB ou pessoa é puxada. Um corte curto mostra a área de acolhimento tranquila; as nove continuam separadas. O disco volta ao estado Sol/Lua do horário, poeira/efeitos de ameaça cessam e a passagem assume um pulso regular.

### `SunMoonAltar_Text_ReturnKukuiSteady`

```text
KUKUI
That's it. No more surges.
Ease the outside unit down.
```

Lusamine reduz a base em etapas; Anabel acompanha a leitura. O parceiro encerra seu pulso. A borda continua estável **sem ambos os suportes**, demonstrando a mudança. Necrozma continua normal; não volta a Ultra nem recebe uma cura milagrosa da fome.

### `SunMoonAltar_Text_ReturnAnabelStable`

```text
ANABEL
It's holding on its own.
We can switch the equipment off.
```

Desligar, com efeito visual. Encerrar tema de ameaça somente aqui; iniciar música calma. O jogador se aproxima do parceiro e recolhe ambos os Pokémon visivelmente. Necrozma retorna ao destino confirmado de equipe/PC; parceiro mantém o próprio slot. Sem substituição ou duplicação.

### A parte de Lusamine

Sem urgência, Lillie se aproxima da mãe. Elas ficam lado a lado, olhando a área onde receberam as UBs. Uma pausa deixa o som ambiente reaparecer.

### `SunMoonAltar_Text_FamilyLusamine`

```text
LUSAMINE
Lillie... you knew when to give them space.
I would have hurried them.
```

### `SunMoonAltar_Text_FamilyLillie`

```text
LILLIE
I was frightened too.
It helped having you there.
```

Lusamine começa a levantar a mão na direção da filha e a deixa repousar ao seu lado. Não forçar contato. Lillie permanece perto por vontade própria.

### `SunMoonAltar_Text_FamilyLusamineAsk`

```text
LUSAMINE
Would you tell me about your journey?
When we've finished here.

There is so much I haven't asked.
```

### `SunMoonAltar_Text_FamilyLillieAnswer`

```text
LILLIE
I'd like that.
We could have tea in Olivine.
```

Gladion termina de conferir Silvally e aproxima-se, sem ser convocado como criança. Lusamine se volta para ele.

### `SunMoonAltar_Text_FamilyLusamineGladion`

```text
LUSAMINE
Will you join us, Gladion?
```

### `SunMoonAltar_Text_FamilyGladion`

```text
GLADION
...Yeah.
I can stay a while.
```

Lillie sorri; Silvally se aproxima de Gladion. Não encerrar com alguém dizendo que a família foi consertada. Esse encontro prepara a rotina de chá em Olivine já escrita na reunião V2; não fixa “amanhã” contra o calendário semanal.

### Últimas tarefas

Looker recebe a confirmação da equipe de apoio: as nove foram acolhidas e seguirão sob cuidado Aether/polícia para avaliação e retorno adequado. Mostrar partida organizada para a área de transporte; não deixá-las desaparecer sem destino. Essa custódia não é recompensa pessoal de Lusamine.

### `SunMoonAltar_Text_FarewellLooker`

```text
LOOKER
The Pokémon are ready for transport.
We'll see them safely aboard.
```

### `SunMoonAltar_Text_FarewellAnabel`

```text
ANABEL
There are still other passages to check.
Looker and I will stay here.

Next time, we'll be ready for what arrives.
```

### `SunMoonAltar_Text_FarewellGladion`

```text
GLADION
You brought them back.
Good work, {PLAYER}.
```

### `SunMoonAltar_Text_FarewellKukui`

```text
KUKUI
Go get some rest, cousin.
I'd like our next battle to be on a beach
with nothing coming out of it.
```

Uma brincadeira específica depois de encerrado o perigo, apoiada em Cherrygrove. Não promete outra região jogável ou Liga de Alola inédita.

### `SunMoonAltar_Text_FarewellLusamine`

```text
LUSAMINE
Thank you, {PLAYER}.
Take good care of them.
```

Ela olha os Pokémon do jogador/ suas Balls, sem reivindicar mérito ou crédito pela reconciliação.

### `SunMoonAltar_Text_FarewellLookerHome`

```text
LOOKER
The sailor will take you home.
We'll call if we need you.
```

A última frase não cria convocação automática adicional desta cadeia. Não ligar no dia seguinte só porque o texto menciona contato futuro.

Concluir estado 16 após resgate, entrega, estabilização e conversa. Limpar atores temporários, equipamento ativo e efeitos. Preservar transporte, Fly e acesso pós-game. Não fazer todos sumirem no mesmo enquadramento: saída organizada/curto fade depois de voltarem aos preparativos de transporte. Restaurar follower e controles uma vez.

## 16. Derrota no boss e nova tentativa

Boss mantém derrota real, blackout e recuperação do sistema. Estado geral continua 14; duelo e acordo não se repetem. Um marcador de introdução vista permite abrir a próxima tentativa com instruções curtas. Não repetir a chegada à arena como primeira descoberta.

A retirada precisa ser representada pelo retorno da equipe e dos equipamentos, sem interromper o processamento do blackout. Se não houver espaço seguro para encenar antes dele, mostrar Anabel retornando e Lusamine encerrando o ajuste ao revisitar o Altar. Ninguém afirma ter capturado ou resgatado UBs numa tentativa perdida.

### `SunMoonAltar_Text_RetryAnabel`

```text
ANABEL
Everyone's back.
Rest your team before we try again.
```

### `SunMoonAltar_Text_RetryLusamine`

```text
LUSAMINE
The outside unit is ready.
I'll stay here.
```

Lusamine não usa a derrota para retomar a disputa. Essa permanência também demonstra sua decisão.

### `SunMoonAltar_Text_RetryGladion`

```text
GLADION
We've still got the exit.
Take the time you need.
```

Looker cura mediante interação. Retomar checagens silenciosas, parceiro e prontidão; reabrir passagem. Ultra continua como boss não resolvido; dados de tentativa resetam conforme sistema, sem duplicar recompensas.

### Entrada curta da arena — `UltraSpaceArena_Text_RetryStart`

```text
ANABEL
The return is steady.
Ready when you are, {PLAYER}.
```

Fuga/desistência do boss segue o tratamento real de ameaça. Resultado inesperado sem vitória não chama resgate ou captura; retorno seguro e caixa abaixo:

### `SunMoonAltar_Text_BossUnresolved`

```text
ANABEL
We need to regroup.
We'll try again when you're ready.
```

**Depois de uma vitória confirmada:** nunca usar esse retry para falha de helper, ator ou espaço. Retomar a etapa pendente. Boss vencido não é desfeito porque a entrega não terminou.

## 17. Conversas com acordo concluído (estado 14)

### `SunMoonAltar_Text_LusamineReady`

```text
LUSAMINE
I'll be at the controls.
Anabel knows how to reach me.
```

### `SunMoonAltar_Text_LillieReady`

```text
LILLIE
We've cleared a path for the larger ones.
Ninetales will stay with me.
```

### `SunMoonAltar_Text_GladionReady`

```text
GLADION
Nothing's blocking the way back.
I'll keep it that way.
```

### `SunMoonAltar_Text_KukuiReady`

```text
KUKUI
Both units passed the test.
We'll watch the readings from this side.
```

### `SunMoonAltar_Text_AnabelReady`

```text
ANABEL
Speak to me by the passage
when you're ready to cross.
```

Anabel não pode existir em dois objetos simultâneos no Altar. Se esta interação já ocorre junto da marca, encaminhar diretamente à prontidão em vez de mandar falar consigo mesma novamente.

## 18. Looker: cura desde o estado 13

Disponível antes do duelo, antes do boss, em retry e no pós-game. Uma pergunta curta; sem sermão sobre descanso ou duas páginas sobre profissão.

### `SunMoonAltar_Text_LookerHealAsk`

```text
LOOKER
Shall I take care of your Pokémon?
```

Yes/No, LOOKER.

### `SunMoonAltar_Text_LookerHealDone`

```text
LOOKER
There. Ready for the next step.
```

Só depois do helper confirmar cura. Fanfarra apropriada e retorno ao tema do estado atual.

### `SunMoonAltar_Text_LookerHealNo`

```text
LOOKER
Whenever you need it.
```

Mensagens automáticas de cura, se houver, usam SYSTEM. Looker permanece num posto acessível, nunca bloqueando a abertura.

## 19. Pós-game, transporte e portal

### Presença funcional

Looker fica junto aos suprimentos e registros; Anabel acompanha o ponto de entrada. Pequenos percursos seguros fora de cutscene, sem bloquear portal, equipamento, marinheiro ou Fly. Interagir interrompe movimento de forma previsível. Não reaplicar posições de wandering durante eventos de coordenadas fixas.

### `SunMoonAltar_Text_LookerPost`

```text
LOOKER
Welcome back, {PLAYER}.
Supplies are ready, and so are we.
```

Encaminhar à cura quando solicitada, sem duplicar pergunta em cada visita.

### `SunMoonAltar_Text_AnabelPost`

```text
ANABEL
The passage is stable today.
We're checking where the others lead.
```

A fala pressupõe condição realmente estável após estado 16; não usar durante entrega pendente.

### `SunMoonAltar_Text_AnabelKurt`

```text
ANABEL
For more Beast Balls, speak to Kurt
in Azalea. He made the one we used here.
```

Anabel não vende Balls e não exige crafting para a captura de história. Receita, materiais, nível e cota pertencem ao sistema de Kurt; não informar números antigos sem verificar. Não inventar exclusividade mundial, quantidade restante ou anos de correspondência.

### Lusamine no Altar

Manter dias herdados: segunda, quarta e sábado; Olivine com os filhos em domingo e sexta. A agenda completa do projeto impede presença simultânea em dois locais. A reunião V2 já escreve as falas familiares na casa; não duplicá-las aqui.

### `SunMoonAltar_Text_LusaminePost`

```text
LUSAMINE
We've been checking on the Pokémon
that came back with us.

Aether entrusted Nihilego to my care.
I intend to give her the time she needs.
```

Só usar após o resgate mostrado. A Nihilego da revanche é uma das nove, confiada a Lusamine para cuidados pela Aether; não é fusão, troféu ou captura adicional do jogador. Sua entrada no time pressupõe avaliação e cuidados após o resgate. Para não afirmar recuperação instantânea, no próprio dia da resolução a revanche usa a composição anterior sem Nihilego; a composição de pós-game com ela passa a valer nas aparições agendadas seguintes, após a virada de data. Preservar o acesso à revanche, sua regra de uma por dia e os demais membros; integrar a seleção de composição sem inventar um ID de estado livre.

### `SunMoonAltar_Text_LusamineRematchAsk`

```text
LUSAMINE
Would you care for another battle?
I'd like to face your team again.
```

Yes/No, LUSAMINE. Uma revanche por dia por regra existente. Revanche é batalha comum com blackout; não herda o duelo narrativo. Registrar uso diário antes da batalha pelo fluxo real.

### `SunMoonAltar_Text_LusamineRematchNo`

```text
LUSAMINE
Another time, then.
```

### `SunMoonAltar_Text_LusamineRematchBeaten`

```text
LUSAMINE
Nicely done.
```

### `SunMoonAltar_Text_LusamineRematchAfter`

```text
LUSAMINE
Thank you for the battle.
We'll be ready for the next one.
```

Esta fala só roda se o resultado retorna ao script. Derrota com blackout não deve tentar abri-la durante recuperação. Reaplicar LUSAMINE em todo pós-batalha válido.

### `SunMoonAltar_Text_LusamineDoneToday`

```text
LUSAMINE
That's enough for today.
My Pokémon could use a rest.
```

### Marinheiro de retorno — todos os estados elegíveis

#### `SunMoonAltar_Text_SailorAsk`

```text
SAILOR
Shall we sail back to Olivine?
```

Yes/No, SAILOR.

#### `SunMoonAltar_Text_SailorDepart`

```text
SAILOR
All aboard!
```

#### `SunMoonAltar_Text_SailorStay`

```text
SAILOR
I'll be here at the pier.
```

### Expedição: preservar o acesso diário herdado sem prometer o loop pronto

O Altar antigo entrega uma entrada diária e arena ainda vazia. Esta reescrita preserva **uma entrada por dia**, disponível em qualquer horário, e não implementa os cinco treinadores/pools do futuro sistema. A divergência do design geral sobre runs ilimitadas deve ser resolvida no documento do loop; aqui não se altera economia por diálogo.

Depois do estado 16, não exigir Solgaleo/Lunala ou Necrozma no time. A estabilização foi mostrada e persiste. A disponibilidade diária não usa o registro de convocações de Looker.

#### `SunMoonAltar_Text_RiftDailyAsk`

```text
ANABEL
The passage is ready for today's survey.
Would you like to go through?
```

Yes/No, ANABEL. Registrar uso quando a entrada efetivamente se compromete com um warp válido; recusa, menu cancelado e falha de transição não gastam o dia. Sair imediatamente após entrar conta como uso, conforme regra herdada.

#### `SunMoonAltar_Text_RiftDailyNo`

```text
ANABEL
All right. Come back when you're ready.
```

Recusar não significa esperar amanhã.

#### `SunMoonAltar_Text_RiftDailyUsed`

```text
ANABEL
We've finished today's survey.
Come back tomorrow.
```

Usar somente quando a entrada diária já foi usada. No mesmo dia da conclusão, o evento final não deve consumir silenciosamente a expedição; seguir o estado diário efetivo do projeto e explicar se indisponível.

#### Arena sem conteúdo de loop — `UltraSpaceArena_Text_EmptySurvey`

```text
NARRATOR
The chamber is quiet.
The passage behind you remains open.
```

Os gatilhos de retorno ao sul funcionam normalmente. Não disparar cutscene de Necrozma, resgate ou captura em estado 16. Esta caixa é o ponto de substituição pelo futuro loop, não promessa de que já há treinadores e lendários ali.

## 20. Música, efeitos e apresentação

| Trecho | Direção |
| --- | --- |
| Porto | Tema local e sons de embarque |
| Chegada | Preparação contida; disco visivelmente irregular |
| Conversa familiar inicial | Sem tremor ou alarme interrompendo cada fala |
| Duelo | Tema de treinador vigente; retorno ao Altar, não fanfarra final de história |
| Teste da passagem | Ameaça/estranhamento cresce com abertura; cessa em intensidade quando o teste fecha |
| Travessia e arena | Tema de ameaça até o boss; restauração correta após batalha |
| Resgate | Tensão controlada, foco em movimentos; sem cinco novas aparições explosivas |
| Captura | Lançamento, balanços, clique e fanfarra sincronizados |
| Estabilização | Música acompanha redução dos pulsos; calma só após desligamento dos aparelhos |
| Família e despedida | Tema calmo; pausas curtas, som ambiente e poucos gestos |
| Pós-game | Ambiente estável; sem tema de crise permanente |

Confirmar faixas habilitadas e ouvir na ROM. Não inventar nomes de constantes. Preservar `fadescreenswapbuffers` para flashes no mesmo mapa; fade habitual de warp somente quando a carga seguinte recompõe as paletas. Shake curto, parâmetros completos e duração controlada. Não usar clarões para esconder personagens sem coreografia.

**Abertura:** centro profundo, borda legível e pulsos distintos entre instável, teste encerrado e estável pós-game. Respeitar orçamento de arte/paleta. Ultra usa asset próprio; normal/Ultra nunca se sobrepõem nem usam Substitute como substituto narrativo.

**Texto:** medir na fonte real com nomes e apelidos expandidos. Quebras deste Markdown sugerem ritmo, não garantem largura. A ação deve acontecer entre blocos após fechar a caixa, com olhar explícito para quem fala ou para a ameaça. Não colocar atores relevantes sob a message box.

## 21. Estados, recuperação e integração

| Situação | Progresso preservado | Retomada |
| --- | --- | --- |
| Estado 12 | Reunião e passe | Chegada uma vez |
| Estado 13 | Chegada, conversa de impasse | Preparação/duelo por interação |
| Duelo válido, teste pendente | Resultado narrativo aceito | Só acordo/teste que faltar; não repetir luta |
| Estado 14, antes do boss | Acordo e teste | Checagens breves e partida |
| Derrota no boss | Duelo, acordo, acesso | Cura e nova tentativa; intro curta |
| Boss vencido, resgate em curso | Vitória e grupos já recebidos | Recuperação não duplica UBs nem reinicia boss |
| Resgate feito, entrega pendente | Nove recebidas, custódia de Necrozma | Somente entrega e fechamento |
| Estado 15 | Resgate, captura e registro | Retorno, estabilização e despedida |
| Estado 16 | História concluída | Rotina semanal e entrada diária |

São estados narrativos, não uma alocação de flags. Conferir suporte do save a cada checkpoint e impedir save manual em transições comprometidas se o motor já opera assim; isso não elimina a necessidade de preservar vitória contra falha de entrega. Nenhuma rotina de load deve reconstruir indiscriminadamente o boss em todo estado 14.

**Separar dados:** espécie/slot do parceiro; identidade do Necrozma recebido; falante; resultado de duelo; resultado do boss; grupos resgatados; entrega pendente; entrada diária. Não sobrecarregar uma var temporária para funções incompatíveis. Não usar flags compartilhadas de objeto quando remover um deles esconderia todo o grupo.

**Mapa e warp:** manter nome curto de MAPSEC dentro do limite confirmado no projeto, Fly e recuperação válidos. O travamento de tela branca do portal diário é pendência técnica independente do texto: verificar estados, callbacks, waits e liberação de controles na build atual. Este roteiro não declara o bug corrigido.

**Fontes de implementação citadas, não anexadas:** `ALTAR_SUN_MOON_IMPLEMENTATION.md`, mapas `.inc`/`.pory`, helpers de entrega e sistema de Kurt. Ausência desses arquivos nesta tarefa impede certificar comandos, IDs, posição exata e runtime; não impede fechar a história.

## 22. Conferência final

- [ ] Todo bloco, menu, helper e página mostra a plaquinha correta acima da caixa.
- [ ] LUSAMINE reestabelecida após cada resultado; buffers de Pokémon não alteram falante.
- [ ] Espaço disponível não produz comentário algum; equipe cheia com PC livre permite seguir.
- [ ] Lusamine preserva o progresso de New Bark e da reunião; seu medo não vira martírio.
- [ ] Lillie pede ajuda, Lusamine segue uma instrução dela durante o resgate e o gesto tem consequência.
- [ ] Duelo não decide competência por vitória obrigatória; derrota é reconhecida honestamente.
- [ ] Nenhum callback pressupõe ramo opcional, origem não verificada ou presença impossível.
- [ ] Kukui só comenta fenômeno visível, dá instrução útil ou faz humor após o perigo.
- [ ] Ultra já está Ultra na arena; parceiro não fornece uma nova transformação.
- [ ] Anabel mantém equipamento apresentado na reunião; Faller não ganha poder novo.
- [ ] Parceiro aparece fisicamente; elegibilidade, nome, forma e recolhimento são consistentes.
- [ ] Parceiro desmaiado no boss recebe tratamento real antes de agir no resgate.
- [ ] As nove UBs se separam e são recebidas na tela, em grupos, com destino de cuidado definido.
- [ ] A contagem final depende de chegadas; nenhuma UB é perdida ou duplicada em retomada.
- [ ] Captura mostra Ball correta, trajetória, entrada, balanços e confirmação.
- [ ] Entrega registra Necrozma normal Lv75 em Beast Ball; PC é aceito; nunca entrega o parceiro.
- [ ] Falha de entrega preserva vitória e resgate, com custódia/retomada explícitas.
- [ ] Necrozma e parceiro estabilizam a passagem em cena; aparelhos e pulso podem cessar depois.
- [ ] PC cheio/party, apelido, dupla Solgaleo+Lunala e evolução não corrompem buffers.
- [ ] Família termina com convite concreto; não há perdão obrigatório nem discurso de absolvição.
- [ ] Cura, navio, Fly, retry e pós-game permanecem acessíveis.
- [ ] Recusar expedição não consome dia; entrada diária não reexecuta a história.
- [ ] Teste visual diurno/noturno, colisões, orçamento de objetos, nomes e música concluído na ROM.

## 23. Referências de voz e limites

Consulta em 25/09/2026. Usadas as seções dos jogos principais, especialmente SM/USUM, para estudar registro de fala e prioridades; não para copiar falas nem importar automaticamente todos os acontecimentos. Os diálogos deste roteiro são originais.

- [Lusamine — falas](https://bulbapedia.bulbagarden.net/wiki/Lusamine/Quotes#Pokémon_Ultra_Sun_and_Ultra_Moon): autoridade, cuidado expresso como controle e resistência à decisão dos filhos.
- [Lillie — falas](https://bulbapedia.bulbagarden.net/wiki/Lillie/Quotes): educação, atenção a Pokémon e coragem adquirida.
- [Gladion — falas](https://bulbapedia.bulbagarden.net/wiki/Gladion/Quotes#Pokémon_Ultra_Sun_and_Ultra_Moon): linguagem direta e proteção por ações.
- [Anabel — falas](https://bulbapedia.bulbagarden.net/wiki/Anabel/Quotes#Pokémon_Sun_and_Moon): comando, proteção de pessoas e das UBs, valor do apoio operacional.
- [Looker — falas](https://bulbapedia.bulbagarden.net/wiki/Looker/Quotes#Pokémon_Sun_and_Moon): cortesia, expressividade e dedicação à equipe.
- [Kukui — falas](https://bulbapedia.bulbagarden.net/wiki/Professor_Kukui/Quotes): entusiasmo por movimentos e incentivo de treinador.

As regras da absorção das nove, do equipamento, da captura roteirizada e da estabilização conjunta são adaptações de SoulGold. A autoridade de continuidade é o conjunto de roteiros revisados anexados e o pedido atual do autor.

**Entrega:** reconstrução integral do roteiro, incluindo ramificações e pós-game. Integração no código, assets adicionais, correção da plaquinha de Lusamine, importação e testes permanecem trabalho de implementação.
