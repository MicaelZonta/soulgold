---
name: entregar-pokemon-ou-ovo
description: Use sempre que um script entregar um Pokemon ou um ovo ao jogador - givemon, giveegg, givemonwithmoves, presente de NPC, recompensa, starter, ovo de historia, premio de jogo. A regra e checar espaco na party E no PC ANTES de qualquer dialogo de oferta, nunca depois. Cobre por que Common_EventScript_GiftMon engole MON_CANT_GIVE em silencio, por que so party cheia E PC cheio deve bloquear, e a ordem obrigatoria em relacao ao setflag de "ja pegou". Use tambem ao diagnosticar presente que sumiu, NPC que diz que entregou e nao entregou, ou presente que virou repetivel.
---

# Entregar Pokémon ou ovo ao jogador

## A regra

> **A checagem de espaço é a primeira coisa do diálogo de oferta.**
> Antes de qualquer fala que prometa, ofereça ou mostre o presente.
> Nunca depois do `givemon`/`giveegg`, nunca depois de uma batalha,
> nunca depois de um menu de escolha.

Esta skill vale para `givemon`, `giveegg`, `givemonwithmoves` e qualquer
macro que caia em `GiveCapturedMonToPlayer`. **Ovo e Pokémon são o mesmo
caso**: `giveegg` chama `ScriptGiveEgg` (`src/script_pokemon_util.c:68-78`),
que chama o mesmo `GiveCapturedMonToPlayer` do `givemon`.

## 1. Por que quebra em silêncio

`GiveCapturedMonToPlayer` (`src/pokemon.c:2949`) devolve **três** valores
(`include/constants/pokemon.h:168-170`):

| Valor | Quando | O que o jogador vê |
|---|---|---|
| `MON_GIVEN_TO_PARTY` 0 | havia vaga na party | entra na equipe |
| `MON_GIVEN_TO_PC` 1 | party cheia, PC com vaga | vai para a caixa |
| `MON_CANT_GIVE` 2 | **party cheia E PC cheio** | **nada** |

E os dois helpers comuns **não tratam os três**:

```asm
Common_EventScript_GiftMon::                     @ data/event_scripts.s:1152
	call_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, Common_EventScript_RecieveMonParty
	call_if_eq VAR_RESULT, MON_GIVEN_TO_PC, Common_EventScript_ReceiveMonPC
	return                                       @ MON_CANT_GIVE: volta calado

Common_EventScript_GiftMonNamed::                @ data/event_scripts.s:1182
	call_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, Common_EventScript_RecieveMonPartyNamed
	call_if_eq VAR_RESULT, MON_CANT_GIVE, Common_EventScript_PartyIsFull
	return                                       @ MON_GIVEN_TO_PC: volta calado
```

- `GiftMon` **engole `MON_CANT_GIVE`**: o script segue, seta a flag de "já
  pegou", o NPC se despede, e o jogador não recebeu nada.
- `GiftMonNamed` **engole `MON_GIVEN_TO_PC`**: o Pokémon vai para a caixa sem
  fanfarra nem aviso. E quando avisa, diz "party is full" mesmo quando o
  problema real seria outro.

Nenhum dos dois dá erro de build. O sintoma só aparece num save com 6 na party
e as caixas cheias — que é exatamente o save de quem jogou muito.

**O pior caso real do projeto** está em `MtSilver_SummitDay/scripts.pory:105-118`:

```
	msgbox("{PLAYER} received an Egg!")      @ anuncia ANTES de entregar
	giveegg(SPECIES_JIRACHI)                 @ pode devolver MON_CANT_GIVE
	...
	setflag(FLAG_HIDE_MTSILVER_RIVAL)        @ e o doador vai embora
	removeobject(LOCALID_MTSILVER_RIVAL)     @ para sempre
	setvar(VAR_RIVAL_STATE, 12)
```

Party e PC cheios = o jogo diz que você ganhou um ovo de **Jirachi**, você não
ganha nada, e quem daria some do mapa. Irrecuperável sem editar o save.

## 2. O padrão

Poryscript:

```
	// Espaço conferido ANTES da oferta: o jogador nunca é convidado a
	// escolher um Pokémon que não pode receber.
	getpartysize
	if (var(VAR_RESULT) == PARTY_SIZE) {
		specialvar(VAR_RESULT, ScriptCheckFreePokemonStorageSpace)
		if (var(VAR_RESULT) == FALSE) {
			goto(<Mapa>_NoRoom)
		}
	}
	msgbox("...a oferta começa aqui...")
```

Asm (`.inc`), mesma coisa:

```asm
	getpartysize
	goto_if_ne VAR_RESULT, PARTY_SIZE, <Segue>
	specialvar VAR_RESULT, ScriptCheckFreePokemonStorageSpace
	goto_if_eq VAR_RESULT, TRUE, <Segue>
	msgbox <Texto_SemEspaco>, MSGBOX_DEFAULT
	closemessage
	release
	end
<Segue>::
	msgbox <Texto_Oferta>, MSGBOX_DEFAULT
```

Peças, todas já existentes — não criar nada:

| Peça | Onde |
|---|---|
| `getpartysize` | `asm/macros/event.inc:535` (escreve `VAR_RESULT`) |
| `ScriptCheckFreePokemonStorageSpace` | `data/specials.inc:353`, `src/field_specials.c:1543` |
| `PARTY_SIZE` = 6 | `include/constants/global.h:70` |
| `MON_CANT_GIVE` | `include/constants/pokemon.h:170` |

## 3. Só party cheia **E** PC cheio bloqueia

Erro comum: bloquear só com a party cheia. **Não faça isso.** `givemon` manda
para o PC sozinho quando só a party está cheia — bloquear aí transforma um
comportamento normal num muro, e irrita mais que o bug original.

A ordem das duas checagens importa por economia: `getpartysize` é barato e
resolve a maioria dos casos; o `specialvar` do PC só roda quando a party está
cheia de verdade.

## 4. Onde exatamente colocar

"Primeira coisa do diálogo" significa **do diálogo de oferta**, não da fala
mais externa do NPC. A ordem certa:

1. `lock` / `faceplayer`
2. Porta de "já pegou" (`goto_if_set FLAG_RECEIVED_*`) — **não** checar espaço
   aqui: não há nada a entregar, e a fala de "sem espaço" seria mentira.
3. Portas de pré-requisito que não entregam nada (sem Poké Balls, sem badge…).
4. **A checagem de espaço.**
5. A oferta, o menu de escolha, a batalha, a coreografia, o `givemon`.

Se houver **batalha ou cutscene longa** entre a checagem e a entrega, a
checagem continua no passo 4 (antes de tudo) **e** ganha a guarda defensiva do
§5 — é o caso do ovo de Cosmog em Violet.

## 5. A guarda defensiva e a ordem do `setflag`

Depois do `givemon`/`giveegg`, ainda assim:

```
	givemon(SPECIES_X, 5)
	if (var(VAR_RESULT) == MON_CANT_GIVE) { goto(<Mapa>_NoRoom) }
	// só agora:
	setflag(FLAG_RECEIVED_X)
	removeobject(LOCALID_X)
	call(Common_EventScript_GiftMon)
```

Duas regras não negociáveis:

- **A guarda vem antes do `setflag` de "já pegou".** Um presente que falhou
  nunca pode se marcar como entregue — senão o jogador perde o conteúdo para
  sempre e nada no build acusa.
- **Comparar não suja `VAR_RESULT`.** `goto_if_*`/`compare` só leem, então
  `Common_EventScript_GiftMon` mais abaixo continua enxergando o resultado do
  `givemon`. Não é preciso salvar em var temporária — mas se salvar, restaure
  antes do `call`.

> ⚠ **`removeobject` seta a flag do template** (skill `visibilidade-e-gatilhos`
> §2). Se a permanência do presente depende disso, ela também depende do objeto
> estar spawnado. Prefira um `setflag` **explícito** da flag persistente: é o
> que torna a entrega permanente de forma independente do spawn.

## 6. Exemplos reais no projeto

| Cena | Arquivo | Observação |
|---|---|---|
| Ovo de Cosmog (Gladion, Violet) | `VioletCity_PokemonCenter/scripts.pory:16-22` | Checagem antes da fala de reconhecimento, **e** batalha no meio → tem a guarda defensiva em `..._GladionNoRoomAfterBattle` |
| Presente do Friendly Trader (Cherrygrove) | `CherrygroveCity/scripts.pory`, `Cherrygrove_FriendlyTrader` | Checagem antes da oferta; `Cherrygrove_TraderNoRoom` é o destino comum das duas guardas; `setflag(FLAG_PICKED_*)` explícito |
| **Contraexemplo:** ovo de Jirachi | `MtSilver_SummitDay/scripts.pory:105-118` | Anuncia antes de entregar e o doador some. **Ainda não corrigido** |

## 7. Situação do repositório (20/09/2026)

`grep -rnE "\bgive(mon|egg)\b" data/maps/*/scripts.{pory,inc} data/scripts/ data/event_scripts.s`
encontra **63 pontos de entrega em 26 arquivos-fonte**. Só dois seguem esta
regra hoje (os dois da tabela acima). Os demais são dívida conhecida — corrigir
ao encostar neles, seguindo §2 a §5.

Alguns precisam de mais que a checagem: onde o doador some depois de entregar
(Jirachi), a fala de "sem espaço" tem que deixar o evento **retomável**, sem
setar nenhuma flag de conclusão.

## 8. O texto de "sem espaço"

Em inglês, na voz do NPC, e tem que dizer as três coisas:

1. que a equipe **e** as caixas estão cheias (não só a equipe);
2. que por isso nada foi entregue;
3. que dá para voltar depois — o presente continua disponível.

Exemplo em produção (`Cherrygrove_TraderNoRoom`):

> Whoa, hold on there!
> Your team is full, and your storage boxes are full too.
> There's nowhere for either of these two to go, and I'm not handing one over
> just to have it disappear.
> Make some room and come find me. I'll be right here!

## Checklist

- [ ] A checagem é a primeira coisa do diálogo de oferta, antes de qualquer promessa
- [ ] Bloqueia só com party cheia **E** PC cheio
- [ ] Guarda `MON_CANT_GIVE` depois do `givemon`/`giveegg`
- [ ] A guarda vem **antes** do `setflag` de "já pegou"
- [ ] Nenhuma flag de conclusão é setada no caminho de "sem espaço"
- [ ] O evento continua retomável: dá para abrir espaço e voltar
- [ ] Texto de "sem espaço" na voz do NPC, citando equipe **e** caixas
- [ ] Testado com 6 na party e PC com vaga (vai pra caixa, com aviso)
- [ ] Testado com 6 na party e PC cheio (bloqueia, sem oferta, e volta depois)
