# Gladion em Cianwood — refinamento completo V3

Documento único para o executor. Substitui integralmente os refinamentos V1/V2 de Gladion em Cianwood. Instruções em português; TODAS as falas e opções em inglês. Inclui equipe definida, roteiro, encenação, movimentos de referência, contrato de scripts, persistência e checklist.

Status: design e estratégia de implementação; não é código compilado ou cena testada. Evidência principal: auditoria do HEAD a5956912f9dbf2480224a9067334d2c4f74b0afc, branch soulgold-rift-missions. Coordenadas e cabeçalho de treinador também usam a cópia local antiga como referência explicitamente identificada. Não tratar essa cópia como versão atual pós-limpeza.

## 1. Decisões fechadas

- Encontro manual depois de Chuck, integrado à entrega de Fly; sem trigger automático da recompensa.
- Gladion e o novo Type: Null conversam com a esposa de Chuck perto do ginásio.
- Checagem silenciosa da entrega antes da conversa longa, movimento, cura ou batalha.
- Recusar, vencer e perder permitem receber Fly. Cura antes/depois do combate; sem blackout ou penalidade correspondente.
- Único progresso persistente: VAR_GETFLY já existente, mantendo 0/1/2. Nenhuma flag nova, nenhum campo novo no save.
- ITEM_HM_FLY, quantidade 1; confirmar retorno antes de marcar 2.
- Esposa fornece a HM narrativamente; não mantém uma segunda entrega independente.
- Dois NPCs decorativos ficam ocultos durante o evento e pelo restante da visita. Só voltam no próximo carregamento real do mapa.
- Type: Null sai na frente; Gladion o acompanha. Não fazê-los sumir no lugar como final normal.
- Batalha simples, quatro Pokémon Lv.43–44, Smart Trainer e dificuldade única. Não alterar Violet, Chuck ou Lillie.
- Type: Null permanece sem evoluir. Ausência na equipe de Violet não significa aquisição posterior; preservar a continuidade narrativa já aprovada.

## 2. Referências e correções obrigatórias

| Ponto da auditoria | Decisão de implementação |
| --- | --- |
| Chuck Lv.42: Hitmontop, Annihilape, Mienshao; dupla | Referência única de dificuldade. Gladion oferece formato e cobertura diferentes. |
| VAR_GETFLY 0/1/2 | 0 indisponível, 1 pendente, 2 entregue. Não usar valores extras como fase de conversa. |
| OnFrame entrega Fly quando var = 1 | Remover só esse disparo; preservar outros hooks da cidade. |
| Esposa entrega sem sincronizar var | Uma rotina de entrega com checagem e conclusão comuns. |
| Reset em Olivine | Rastrear chamador e guardar progresso 1/2; não aceitar reset indevido nem apagar inicialização legítima. |
| 16 slots ativos / 19 definições | Medir ativos reais; usar troca de decorativos, sem aumentar teto. |
| Retorno de giveitem não auditado completamente | Inspecionar macro/rotina de item antes de codificar. Não usar MON_CANT_GIVE do ovo. |

A janela de duplicação por “mesmo frame/frame-skip” é hipótese não reproduzida, não bug demonstrado em jogo. A inconsistência entre as duas rotas de entrega, porém, deve ser removida.

A auditoria confirma dificuldade única no checkout citado. Não buscar outra branch nem recriar variantes. O reset antigo de Olivine está em evento de inicialização; a implementação deve determinar sua alcançabilidade e preservar os estados já avançados, sem inventar uma migração de save antigo.

## 3. Equipe definida para esta implementação

Equipe escolhida neste refinamento: quatro Pokémon, batalha simples, Smart Trainer, sem variante adicional e sem itens de cura pela IA. Evolui as famílias citadas de Violet e inclui Type: Null. Referência de Chuck Lv.42 em dupla; Gladion Lv.43–44 não garante, por si, dificuldade superior.

| Pokémon | Nível | Item | Ability | Nature | EVs | Golpes |
| --- | --- | --- | --- | --- | --- | --- |
| Krookodile | 43 | Sitrus Berry | Intimidate | Jolly | 100 HP / 100 Atk / 100 Spe | Earthquake, Crunch, Rock Slide, Taunt |
| Vikavolt | 43 | Sitrus Berry | Levitate | Modest | 100 HP / 100 SpA / 100 Spe | Thunderbolt, Bug Buzz, Energy Ball, Volt Switch |
| Lycanroc Midday | 44 | Focus Sash | Sand Rush | Jolly | 60 HP / 100 Atk / 100 Spe | Stone Edge, Accelerock, Drill Run, Swords Dance |
| Type: Null | 44 | Eviolite | Battle Armor | Adamant | 100 HP / 100 Atk / 60 SpD | Crush Claw, X-Scissor, Shadow Claw, Swords Dance |

IVs 31 em todos. Sand Rush não implica adicionar tempestade de areia; é uma habilidade sem ativação própria nesta composição; o valor competitivo vem de velocidade, prioridade e Focus Sash. Não adicionar clima só para ativá-la. O executor pode apontar inadequação no conjunto de abilities/innates do hack, mas não deve alterar globalmente espécies para atender esta luta. Confirmar golpes, formas e nomes aceitos pelo parser. Type: Null não evolui via scaling.

A equipe oferece Intimidate e pressão física, atacante especial com Levitate, prioridade de Rock e um parceiro resistente com Eviolite. Não usa cura infinita nem tenta eliminar todas as fraquezas. Avaliar a força de Swords Dance e innates no engine real.

Bloco de equipe com cabeçalho da referência funcional de Violet. Resolver um ID numérico livre para o novo símbolo; não renumerar entradas existentes:
```text
=== TRAINER_GLADION_CIANWOOD ===
Name: Gladion
Class: Rival
Pic: Gladion
Gender: Male
Music: Silver
Double Battle: No
AI: Smart Trainer

Krookodile @ Sitrus Berry
Jolly Nature
Level: 43
Ability: Intimidate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 100 HP / 100 Atk / 100 Spe
- Earthquake
- Crunch
- Rock Slide
- Taunt

Vikavolt @ Sitrus Berry
Modest Nature
Level: 43
Ability: Levitate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 100 HP / 100 SpA / 100 Spe
- Thunderbolt
- Bug Buzz
- Energy Ball
- Volt Switch

Lycanroc Midday @ Focus Sash
Jolly Nature
Level: 44
Ability: Sand Rush
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 60 HP / 100 Atk / 100 Spe
- Stone Edge
- Accelerock
- Drill Run
- Swords Dance

Type: Null @ Eviolite
Adamant Nature
Level: 44
Ability: Battle Armor
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 100 HP / 100 Atk / 60 SpD
- Crush Claw
- X-Scissor
- Shadow Claw
- Swords Dance
```


## 4. Roteiro consolidado

Todos os diálogos e opções exibidos no jogo devem ser em inglês. As falas abaixo são a versão inglesa autoral a implementar; ajustar apenas quebras de linha e tamanho das caixas, preservando intenção e voz. As instruções técnicas permanecem em português.

**Conversa com a esposa de Chuck**

> Chuck's wife: “You came all this way, and you're going back by sea?”
>
> “Take Fly. Even someone who enjoys walking needs a rest.”
>
> Gladion: “I'm not in a hurry.”

Type: Null percebe o jogador e vira a cabeça. Gladion acompanha seu olhar.

> Gladion: “Look who it is.”
>
> “You beat Chuck? He doesn't usually cut a training session short.”
>
> Chuck's wife: “And then he says he lost track of time!”
>
> “I brought an HM for you, too. Gladion, would you pass it along? I'll see if my husband will finally take a break.”

Ela passa a HM destinada ao jogador a Gladion e segue em direção ao ginásio. A encenação não concede automaticamente uma HM ao jogador antes da etapa de entrega.

**Johto e Lillie**

> Gladion: “Lillie told me about Goldenrod.”
>
> “First the battle. Then the flowers. Then back to the battle.”
>
> “She's enjoying it here.”

Type: Null se acomoda ao lado dele.

> Gladion: “So am I.”
>
> “I thought I'd spend my time in Johto looking for the strongest Trainers.”
>
> “Instead, we spent a whole morning on this beach. He was still getting used to the waves.”

Gladion olha para o parceiro.

> “Every time the water came near him, he backed away.”
>
> “Then he started following it back.”
>
> “We stayed longer than I planned.”

Pausa curta; ele volta a olhar para o jogador.

> “It was a good morning.”

**Revanche**

Type: Null se levanta e dá alguns passos na direção do jogador.

> Gladion: “You remember this Trainer?”
>
> “Yeah. I want to find out, too.”
>
> “A rematch before you leave?”
>
> “Fly is yours either way. The battle is something I'm asking for.”

Opções: “Let's battle!” / “Not today.”

Recusa:

> “Fine. Another time.”

A fala é despedida narrativa, não promessa de um sistema de revanche: seguir diretamente à entrega e conclusão.

Aceite:

> “First, let's take care of your Pokémon. I want you at your best.”
>
> “Ready. Don't hold back.”

Curar e iniciar a batalha. A redação funciona também quando a interação não ocorre imediatamente após o ginásio.

**Vitória do jogador**

> “You've changed since Violet.”
>
> “I looked for the same openings. They weren't there anymore.”

Gladion se volta para Type: Null.

> “We'll need another plan.”
>
> “You noticed it too, didn't you?”

**Derrota do jogador**

> “That one was ours.”
>
> “But you made us work for it.”

Ele olha para Type: Null.

> “You stayed focused. Let's keep working on that.”
>
> “Good work.”

Vitória e derrota convergem para cura e entrega, sem blackout ou penalidade correspondente.

**Entrega e despedida**

> Gladion: “Here. The HM she left for you.”
>
> “Fly. It'll make the trip back easier.”

Entregar a HM e confirmar sucesso. Só depois marcar o estado existente de recebimento.

> “If you see Lillie, tell her we're doing fine.”
>
> “And that I heard the whole story about the battle.”

Type: Null começa a caminhar pela praia. Para após alguns passos e olha para trás. Gladion percebe.

> “Made up your mind?”
>
> “I'm coming.”

Ele se vira uma última vez para o jogador.

> “See you around, {PLAYER}.”

Type: Null segue na frente; Gladion o acompanha. Ambos saem visivelmente, a música normal retorna e o jogador recupera os controles.


### Falas complementares

Empate: “That was close for both of us. Let's look after our Pokémon.”
Desistência: “All right. We can stop. I'll take care of your Pokémon.”
Após fala de resultado conhecido, curar e seguir à entrega; não usar texto de vitória em desistência.


## 5. Encenação fechada

### Posições e acesso

Âncoras escolhidas para a cena: Gladion (17,47), Type: Null (17,48), esposa (18,47). Porta do ginásio na referência antiga: (15,44). Área do jogador: lado oeste ou norte de Gladion. Usar como layout-alvo; verificar tiles e ajustar deslocamento conjunto mínimo se uma âncora não for transitável no checkout atual. Não alegar que coordenadas foram testadas.

O jogador não é teleportado nem obrigado a um único tile. A cena aceita interação pelos lados livres. Antes de mover Null, calcular a rota sem atravessar o jogador/follower. Gladion vira para o interlocutor real; a esposa e Null viram por direção relativa. Se o jogador falar com Null, ele emite o cry e Gladion assume o mesmo script/interlocutor da batalha.

A esposa deixa de vagar somente durante a cena. Ela espera próxima do ginásio; não precisa trocar de mapa. Depois retorna à posição segura original e ao comportamento anterior. Se não puder retornar sem colisão, aguarda em tile livre e retoma movimento normal ao liberar controles.

### Sequência de direção

| Momento | Ação | Ritmo/som |
| --- | --- | --- |
| Interação | Checagens silenciosas, lockall, esposa e Gladion se encaram | Música normal |
| Conversa da esposa | Duas caixas, Gladion responde curto | Sem exclamação ainda |
| Reconhecimento | Null vira primeiro para o jogador; Gladion acompanha, exclamação em Gladion | SE_PIN; esperar movimento |
| Reencontro | Gladion volta-se ao jogador | Iniciar MUS_HG_ENCOUNTER_RIVAL |
| HM confiada | Esposa aproxima-se um passo se houver espaço, encara Gladion e se afasta para espera segura | Pausa de 12 frames; sem inventar animação de item |
| Lillie | Gladion conversa; sem animação por caixa | Pausa curta após observação das flores |
| Ondas | Gladion olha para Null; Null vira para o mar, depois de volta | Pausa de 24 frames antes de “It was a good morning.” |
| Convite | Null dá um passo num tile livre voltado ao jogador; Gladion o observa | Esperar o passo antes do texto |
| Aceite | Cura e batalha | Música de batalha definida abaixo |
| Pós-batalha | Restaurar posições, ler outcome antes da cura, fala própria | Retomar tema de encontro |
| Entrega | Gladion encara jogador; entregar HM e confirmar | Fanfare padrão de giveitem, sem tocar duas vezes |
| Despedida | Null avança, para, olha para trás | Pausa de 20 frames |
| Partida | Gladion responde, acena por orientação e segue Null | Tema de saída |
| Fim | Dois objetos fora de vista são removidos | Restaurar MUS_HG_CIANWOOD; liberar controles |

Movimentos acontecem entre caixas fechadas, nunca com mensagem aberta cobrindo a ação. Cada applymovement tem waitmovement. Follower permanece funcional e não é globalmente desligado.

### Música definida

- Conversa antes do reconhecimento: música atual da cidade.
- Reconhecimento e pós-combate: MUS_HG_ENCOUNTER_RIVAL.
- Combate: MUS_HG_VS_RIVAL, se o seletor local da classe Rival já o usa; configurar só esta batalha se necessário.
- Saída: MUS_HG_RIVAL_EXIT; retornar ao padrão ao terminar.

Essas constantes existem na cópia local consultada. Reutilizar áudio, sem importar faixas. Não se trata de afirmar que são um tema canônico de Gladion; é uma escolha de assets disponíveis no hack.

### Movimentos de referência

Escolha de saída: seguir ao sul pela praia, Null pelo corredor x=17 e Gladion um passo atrás. A esposa sai do corredor antes. A extensão deve chegar fora da câmera; a sequência abaixo descreve os primeiros momentos, não autoriza atravessar obstáculos.

```asm
Cianwood_Movement_NullFirstStep:
    walk_down
    face_up
    step_end

Cianwood_Movement_NullContinue:
    walk_down
    walk_down
    walk_down
    walk_down
    step_end

Cianwood_Movement_GladionFollow:
    walk_down
    walk_down
    walk_down
    walk_down
    step_end
```

Iniciar Null de (17,48) só se o tile sul estiver livre. Depois de “I'm coming”, Null retoma e Gladion segue com defasagem de um passo; não iniciar ambos num mesmo tile. Se a câmera ainda os mostrar após quatro passos, continuar pelo corredor validado até fora da vista ANTES de removeobject. O executor deve entregar a rota final registrada no mapa atual. Não fingir que esta referência parcial resolve colisões dinâmicas.

## 6. Dois decorativos e controle transitório

Selecionados: Youngster (27,41), script CianwoodCity_EventScript_Youngster; Battle Girl (20,54), script CianwoodCity_EventScript_Lass. Na cópia antiga, apenas dizem como voltar a Olivine com Fly e que Chuck treina com Pokémon. Confirmar que continuam decorativos, atribuir aliases aos mesmos local IDs e não reordenar objetos.

Escolha técnica: um pequeno estado estático de RAM, sem malloc/free e sem novo save, restrito ao evento. Evita reservar temporários do mapa que já podem pertencer a Suicune. Usar 8 bytes lógicos e conferir sizeof/alinhamento no build:

```c
struct CianwoodFlySceneState {
    u16 outcome;
    u8 phase; // 0 idle, 1 intro, 2 reward pending, 3 exit
    u8 busy;
    u8 decorHiddenUntilReload;
    u8 previousNoWhiteout;
    u8 noWhiteoutOwned;
    u8 initialized;
};
```

O custo é fixo (alvo 8 bytes, confirmar no map file), não vazamento. Nenhum estado extra em VAR_GETFLY. Registrar custo adicional de qualquer posição salva; preferir mecanismo existente de templates para retorno da batalha. Não alegar RAM zero.

Inicializar antes do spawn ao entrar de outro mapa ou carregar save. NÃO reinicializar no retorno da batalha, menus ou movimento de câmera. Ao entrar com var=1 e cena normal, decorHiddenUntilReload=1. Após receber e sair, o campo continua 1 até novo carregamento; os decorativos não reaparecem nessa visita.

O filtro se aplica somente a Cianwood e aos quatro objetos. Preservar as condições originais de spawn e flags de terceiros:

```c
// Contrato; nomes dos helpers são novos, não APIs já existentes.
bool8 CianwoodFlyAllowsObject(u8 localId)
{
    if (IsSelectedDecorative(localId))
        return !sFlyScene.decorHiddenUntilReload;
    if (IsGladionOrNull(localId))
        return sFlyScene.phase == 3
            || (VarGet(VAR_GETFLY) == 1 && CianwoodFlyNormalWindow());
    return TRUE;
}
```

Aplicar ANTES da alocação nos caminhos de câmera, spawn explícito e retorno ao campo. Um removeobject isolado é insuficiente. Remover decorativos ativos antes de criar visitantes; no fim, remover visitantes e não restaurar decorativos. Não tocar outros mapas. Não aumentar OBJECT_EVENTS_COUNT. Ocultar dois NPCs fora da área ativa não garante dois slots: medir o pico real.

## 7. Entrega, recuperação e ordem tardia

A conclusão é VAR_GETFLY=2, gravada apenas após item entregue. Rotina comum primeiro verifica var=2, depois item já presente, depois capacidade/adição. Item presente com var=1 pode ser reconciliado para 2 sem cópia após confirmar semântica local. Estado 2 sem item não justifica regenerar HMs infinitamente.

Esposa encaminha para Gladion no fluxo normal. Recusa é válida e entrega imediatamente. Fly adiado até depois do incidente de Blackthorn: esposa assume a mesma rotina comum, Gladion/Null ausentes e decorativos normais. Esta é a decisão desta revisão para não regredir o parceiro nem bloquear HM. Usar o estado existente de conclusão do incidente; enquanto ele não existir no checkout, usar conclusão da Liga como guarda tardia já disponível e conectar o marco de Blackthorn quando sua cena for implementada. Não inventar ID nem flag para esse marco.

O primeiro uso da guarda tardia deve ser testado com save da campanha. A janela não depende de vencer Gladion nem do recebimento de Fly em outra região.

Em falha excepcional após combate, phase=2 preserva entrega pendente na mesma visita. Ao sair/recarregar antes de receber, sem estado persistente novo, essa lembrança não sobrevive. A prevenção é a checagem correta antes da luta e entrega no mesmo fluxo; não alegar recuperação ilimitada sem armazenamento.

No resultado desconhecido, restaurar no-whiteout, curar e encerrar sem item, mantendo elegibilidade. Não alterar vitória/achievement para forçar avanço. Respeitar derrota/empate/desistência pelo padrão local de Lillie.

## 8. Fluxo técnico e integração de script

Este é pseudocódigo estruturado para transpor à fonte local (Pory/ASM/C). Não é anunciado como arquivo compilável. Funções em PascalCase abaixo são contratos a implementar com comandos locais. Nomes de constantes comprovados pela auditoria são preservados. Esta separação evita inventar comandos do engine ou trajetos ainda não validados.

### Papéis do estado transitório

- busy: trava reentrada da cena; não substitui lockall.
- phase: registra introdução, entrega pendente e despedida.
- previousNoWhiteout: estado anterior, para restauração exata.
- outcome: resultado antes de cura.
- decorHiddenUntilReload: mantém os dois decorativos ausentes até uma nova visita/load após a entrega; apenas RAM.
- posições e direção necessárias ao retorno da batalha, se o sistema local exigir.

Usar a estrutura da seção 6. O fluxo abaixo usa phase diretamente: 0 sem introdução, 1 introdução concluída, 2 entrega pendente, 3 despedida. Não há booleanos separados de introdução/entrega/saída. busy e previousNoWhiteout correspondem aos campos definidos. Não salvar no save.

```text
OnCityLoadOrResume(reason):
    if reason == entering_from_other_map:
        ResetSceneRam()
    PreserveExistingCityHooks()
    ReconcileOnlyVerifiedFlyInconsistency()
    if VAR_GETFLY == 1 and IsNormalStoryWindow():
        decorHiddenUntilReload = true
    ApplySpawnPolicyBeforeAllocation()
    // Sem iniciar diálogo por OnFrame.

OnGladionInteract:
    if busy:
        return
    if VAR_GETFLY != 1 or not IsNormalStoryWindow():
        RefreshScenePresence()
        return
    if HasItem(ITEM_HM_FLY, 1):
        ReconcileExistingItemWithoutGivingAgain()
        RefreshScenePresence()
        return
    if not CanReceiveItem(ITEM_HM_FLY, 1):
        SayBusyLineAndRelease()
        return

    busy = true
    LockAll()
    if phase == 2:
        goto Reward
    if phase == 0:
        StageActorsUsingValidatedRoutes()
        ShowWifeConversation()
        MoveWifeToSafeWaitingPoint()
        ShowJohtoAndLillieConversation()
        phase = 1

    ShowChallenge()
    if PlayerDeclines():
        ShowDeclineText()
        phase = 2
        goto Reward

    HealPlayerParty()
    previousNoWhiteout = ReadFlag(B_FLAG_NO_WHITEOUT)
    noWhiteoutOwned = true
    SetFlag(B_FLAG_NO_WHITEOUT)
    SetCorrectLastTalkedObject()
    StartTrainerBattleNoIntro(TRAINER_GLADION_CIANWOOD)
    outcome = GetBattleOutcome()
    RestoreFlag(B_FLAG_NO_WHITEOUT, previousNoWhiteout)
    noWhiteoutOwned = false
    RestoreScenePositionsAndEncounterMusic()

    if outcome == B_OUTCOME_WON:
        ShowPlayerWonText()
    else if outcome == B_OUTCOME_LOST:
        ShowPlayerLostText()
    else if outcome == B_OUTCOME_DREW:
        ShowDrawText()
    else if outcome == B_OUTCOME_FORFEITED:
        ShowForfeitText()
    else:
        HealPlayerParty()
        RestoreWifeAndSafePositions()
        RestoreDefaultMusic()
        busy = false
        ReleaseAll()
        return

    HealPlayerParty()
    phase = 2

Reward:
    if VAR_GETFLY == 2:
        goto Exit
    if HasItem(ITEM_HM_FLY, 1):
        // Só após validar que este estado pode ser reconciliado.
        VAR_GETFLY = 2
        goto Exit
    if not CanReceiveItem(ITEM_HM_FLY, 1):
        goto DeliveryFailed

    ShowDeliveryIntro()
    phase = 3
    success = GiveItemAndCaptureResultImmediately(ITEM_HM_FLY, 1)
    if not success:
        phase = 2
        goto DeliveryFailed
    VAR_GETFLY = 2

Exit:
    phase = 3
    ShowFarewellAboutLillie()
    MoveNullForwardThenLookBackAndWait()
    ShowGladionImComing()
    MoveBothAlongValidatedExitPathsAndWait()
    RemoveNullObject()
    RemoveGladionObject()
    RestoreWifeOriginalBehavior()
    phase = 0
    // decorHiddenUntilReload permanece true até novo carregamento.
    // Não restaurar decorativos nesta visita.
    RestoreDefaultMusic()
    busy = false
    ReleaseAll()
    return

DeliveryFailed:
    // Nada de nova flag, var = 1 permanece.
    ShowShortDelayText()
    RestoreWifeAndSafePositions()
    RestoreDefaultMusic()
    busy = false
    ReleaseAll()
    // phase = 2 continua pendente na mesma visita.
    return

OnWifeInteract:
    if VAR_GETFLY == 2:
        ShowOriginalPostFlyDialogue()
    else if not OriginalChuckEligibility():
        ShowOriginalPreChuckDialogue()
    else if IsNormalStoryWindow():
        PointPlayerToGladion()
    else:
        // Caso tardio: mesma rotina de entrega, sem cena regredida.
        RunCommonFlyDeliveryWithoutGladion()
```

O fluxo da esposa tardio também checa capacidade, captura retorno, marca 2 somente após sucesso e não usa a coreografia de Gladion. O ramo não deve ser habilitado por falha silenciosa de spawn; corrigir a falta de slots no fluxo normal.

### Mapeamento para comandos existentes

| Contrato | Referência local a usar |
| --- | --- |
| Receber item / checar capacidade | rotina real de itens; confirmar checkitemspace e retorno de giveitem |
| Batalha | trainerbattle_no_intro |
| Resultado | specialvar VAR_RESULT, GetBattleOutcome, seguido de cópia imediata |
| Controle | lockall / releaseall conforme suporte do script |
| Movimento | applymovement / waitmovement e rotas com colisão validada |
| Desaparecimento | removeobject, junto com filtro de respawn |
| Som normal da cidade | MUS_HG_CIANWOOD ou restauração padrão que respeite evento anterior |

Não copiar MON_CANT_GIVE do ovo para retorno de item. Não assumir que o mecanismo de geração usa nomes de forma iguais ao exemplo.


## 9. Mensagens auxiliares em inglês

| Label de intenção | Texto |
| --- | --- |
| Busy | “Not now. We're finishing our training.” / “Come back later.” |
| DeliveryFailed | “Give me a moment. Come back in a little while.” |
| WifePointsToGladion | “Gladion has something for you. Go and speak to him.” |
| UnexpectedOutcome | “We should stop here. Let me take care of your Pokémon.” |
| LillieNeutral | “Lillie is enjoying her time in Johto.” |
| GladionDefeated | “You kept us on our toes. Good battle.” |
| WifeLateDelivery | “You earned this when you beat Chuck. Here, take Fly.” |

Menu: “Let's battle!” / “Not today.” Preservar textos ingleses originais da esposa antes da elegibilidade e após entrega. Se Goldenrod não tiver ocorrido, usar LillieNeutral e retirar a referência à história da batalha na despedida; não criar flag de conversa.

## 10. Arquivos, execução e checklist

Editar fontes reais: CianwoodCity/map.json e script-fonte; produtor em CianwoodGym somente se necessário; fonte de Olivine para proteger progresso; src/data/trainers.party e constantes de trainer; pequeno filtro/estado restrito a Cianwood no mecanismo de objetos ou módulo existente adequado. Nunca editar .inc gerado se houver .pory. Adicionar referências de gráficos apenas se não estiverem já integradas.

O reset de Olivine é investigação obrigatória sobre código, não decisão narrativa a devolver ao autor. Encontrar seu chamador, garantir que 1/2 não sejam apagados por revisita e manter New Game correto. Preservar todas as mudanças locais e não trocar branch.

### Dados e entrega

- [ ] Documentar todos os consumidores de VAR_GETFLY e corrigir reset indevido de Olivine/Chuck.
- [ ] Remover trigger automático antigo sem afetar Suicune/Eusine.
- [ ] Usar uma rotina de Fly, retorno confirmado e sincronização de var=2.
- [ ] Checar capacidade antes da cena, sem aviso explícito de bolsa.
- [ ] Tratar item presente/var pendente sem duplicata.
- [ ] Confirmar que nenhum caminho altera badges ou usa flag de trainer como conclusão.

### Equipe

- [ ] Adicionar quatro Pokémon definidos, com itens, moves, níveis, IVs e EVs completos.
- [ ] Preservar trainer de Violet e resolver ID próprio sem renumerar.
- [ ] Confirmar parser de forma Lycanroc, innates e efeito real de scaling.
- [ ] Garantir Type: Null sem evolução; manter dificuldade única.
- [ ] Comparar desafio com Chuck usando equipes representativas, sem declarar balanceamento pelo nível apenas.

### Cena

- [ ] Confirmar âncoras e registrar rota final no mapa atual.
- [ ] Aceitar direções livres da interação e entrada pelo objeto Null.
- [ ] Usar diálogo inglês integral e pausas/música por momento.
- [ ] Preservar esposa e follower sem atravessar objetos.
- [ ] Capturar resultado antes da cura e restaurar no-whiteout prévio.
- [ ] Vitória, derrota, recusa, empate e desistência levam aos ramos corretos.
- [ ] Resultado desconhecido encerra com recuperação, sem falsa vitória.
- [ ] Fazer Null partir primeiro, esperar, olhar para trás e Gladion acompanhar.
- [ ] Remover visitantes fora da vista; não restaurar decorativos nessa visita.

### Memória e objetos

- [ ] Confirmar que os dois candidatos permanecem decorativos.
- [ ] Preservar seus IDs e regras originais.
- [ ] Filtrar respawn por câmera, retorno ao campo e addobject.
- [ ] Medir pico real com follower/mapas conectados.
- [ ] Medir sizeof do estado e delta EWRAM/ROM; sem heap e sem novo save.
- [ ] Preservar RAM da cena através da batalha; reinicializar em nova visita/load.
- [ ] Decorativos permanecem ausentes mesmo após caminhar pela cidade depois da entrega.
- [ ] Decorativos voltam ao recarregar com var=2; Gladion permanece ausente.

### Testes e entrega

- [ ] Pré-Chuck; pós-Chuck; Fly já recebido; interação adiada.
- [ ] Aceite/vitória, aceite/derrota, recusa, empate/desistência quando disponíveis.
- [ ] no-whiteout inicialmente ativo/inativo; sem penalidade de blackout.
- [ ] Falha de capacidade real e falha de entrega injetada somente em teste.
- [ ] Retomada da entrega na mesma visita e comportamento após reload documentados.
- [ ] Viagem Cianwood–Olivine com var=1 e var=2.
- [ ] Cena após Blackthorn/Liga usa caminho tardio sem regressão narrativa.
- [ ] Regenerar derivados e compilar; registrar comando, warnings e tamanho da ROM.
- [ ] Entregar arquivos alterados, IDs, estado, equipe e evidências; distinguir implementado de testado.

## 11. Prompt de execução

Implemente este V3 como documento único. O time, idioma, cena, música, resultados e política dos dois decorativos estão definidos: não devolver esses itens como decisões abertas. Resolva no código atual apenas os detalhes mecânicos que exigem evidência — IDs livres, fonte/gerador, retorno de giveitem, chamadores do reset, colisões e slots ativos. Preserve Violet/Lillie/Chuck. Use VAR_GETFLY 0/1/2 e a estrutura de RAM de tamanho explícito, sem flags novas ou heap. Decorativos ficam ocultos até o próximo carregamento, mesmo após a saída. Aplique inglês em todas as mensagens. Compile e teste o fluxo completo, reportando limitações reais. Não fazer commit/push nem mudar branch sem autorização.
