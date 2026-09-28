# Archie

**Região da ficha:** Hoenn

Aparece no checklist como:

- **Archie** (Hoenn · Team Aqua) — líder que deseja expandir os oceanos usando Kyogre.

**Pronto para o Nexus:** ✅ sim — tem sprite e battle sprite.

## Checklist

- [x] Sprite de overworld *(obrigatório)*
- [x] Battle sprite / front pic *(obrigatório)*
- [ ] Field mugshot (retrato na caixa de diálogo)
- [x] Time para as Rift Missions definido
- [x] Associado a um lendário
- [x] Diálogo genérico escrito
- [x] Diálogo associado ao lendário escrito

## Referências no repositório

### Sprite de overworld

| Constante | Arquivo |
|---|---|
| `OBJ_EVENT_GFX_ARCHIE` | `graphics/object_events/pics/people/team_aqua/archie.png` |

### Battle sprite (front pic)

| Constante | Arquivo |
|---|---|
| `TRAINER_PIC_FRONT_AQUA_LEADER_ARCHIE` | `graphics/trainers/front_pics/aqua_leader_archie.png` |

### Field mugshot

Não existe. Opcional; criar com a skill `adicionar-grafico-trainer` (precisa do `case` em `GetFieldMugshotIdByObjectGraphicsId`).

### Batalhas que já existem (campanha)

Flag de batalha = `TRAINER_FLAGS_START (0x500) + ID` — é o "já venceu" que `trainerbattle_*` liga. O loop do Nexus precisa repetir a batalha **sem** mexer nessa flag da campanha (design §10).

Nenhuma. Ao criar, seguir a skill `adicionar-batalha-npc` (e `alocar-flag` se precisar de flag nova).

### Time das Rift Missions

✅ **Implementado em 27/09/2026** (a proposta abaixo virou código): `TRAINER_NEXUS_ARCHIE` = **1036** (flag de batalha `0x90C`, limpa antes e depois de cada luta), bloco em `src/data/trainers.party`, nível pelo R2 (tabela em `src/data/nexus/trainers.h`). Fala genérica `Nexus_EventScript_Archie_Fight`; campeão: `Nexus_EventScript_Archie_ChampionFight` (para Kyogre). Tudo em `data/scripts/nexus.inc`, sem blackout, resultado em `VAR_TEMP_3`. Para testar: menu de debug → Rift Missions… → Nexus fights… → Archie.

📝 **Proposta de 27/09/2026, aguardando o autor.** `TRAINER_NEXUS_ARCHIE`, campeão de Kyogre. Segue [R10–R13](../NEXUS_REGRAS.md): 1 lendário, 1 semi-lendário e 1 Mega (pedra de tipo, como o hack exige); 31 IV e 252 EV em tudo; nível pelo R2 (o `Level: 100` é só teto do scaler).

Lendário e Mega na mesma peça: **Kyogre** com Blue Orb (Primal conta como Mega, R10), a criatura que ele acordou para devolver o mundo ao mar; semi-lendário **Manaphy** (Água, o príncipe do mar, que atravessa os oceanos até onde nasceu: o sonho do Archie de um mar para os Pokémon). Mais **Sharpedo** (o ás dele), **Crobat**, **Muk** e **Mightyena**, do time dele em ORAS. O Primordial Sea da Primal anula golpes de Fogo e reforça a Água do time inteiro.

*Plano (Singles):* o Mightyena entra com Intimidate e Yawn; o Crobat usa Taunt e Super Fang; a Manaphy (Hydration) sobe Tail Glow e se cura com Rest sem dormir na chuva; o Sharpedo ganha velocidade com Speed Boost; o Kyogre Primal fecha com Water Spout e Thunder certeiro.

*Plano (Doubles):* Origin Pulse e Water Spout acertam os dois lados sob chuva pesada; o Crobat põe Tailwind; Mightyena solta Snarl e Intimidate; o Muk de Assault Vest segura e bate com Knock Off.

| Pokémon | Item | Habilidade | Nature | Golpes |
|---|---|---|---|---|
| Kyogre | Blue Orb | Drizzle | Modest | Origin Pulse, Water Spout, Thunder, Ice Beam |
| Manaphy | Leftovers | Hydration | Timid | Tail Glow, Scald, Ice Beam, Rest |
| Sharpedo | Life Orb | Speed Boost | Adamant | Liquidation, Crunch, Ice Fang, Protect |
| Crobat | Sitrus Berry | Infiltrator | Jolly | Brave Bird, Tailwind, Super Fang, Taunt |
| Muk | Assault Vest | Poison Touch | Adamant | Gunk Shot, Knock Off, Drain Punch, Shadow Sneak |
| Mightyena | Sitrus Berry | Intimidate | Impish | Crunch, Taunt, Yawn, Snarl |

<details><summary>Bloco para o <code>src/data/trainers.party</code> (conferido com <code>dev_scripts/nexus_validar_time.py</code>)</summary>

```
=== TRAINER_NEXUS_ARCHIE ===
Name: Archie
Class: Aqua Leader
Pic: Aqua Leader Archie
Gender: Male
Music: Aqua
Double Battle: Yes
AI: Smart Trainer

Kyogre @ Blue Orb
Modest Nature
Level: 100
Ability: Drizzle
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Origin Pulse
- Water Spout
- Thunder
- Ice Beam

Manaphy @ Leftovers
Timid Nature
Level: 100
Ability: Hydration
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Tail Glow
- Scald
- Ice Beam
- Rest

Sharpedo @ Life Orb
Adamant Nature
Level: 100
Ability: Speed Boost
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Liquidation
- Crunch
- Ice Fang
- Protect

Crobat @ Sitrus Berry
Jolly Nature
Level: 100
Ability: Infiltrator
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Brave Bird
- Tailwind
- Super Fang
- Taunt

Muk @ Assault Vest
Adamant Nature
Level: 100
Ability: Poison Touch
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Gunk Shot
- Knock Off
- Drain Punch
- Shadow Sneak

Mightyena @ Sitrus Berry
Impish Nature
Level: 100
Ability: Intimidate
IVs: 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
EVs: 252 HP / 252 Atk / 252 Def / 252 SpA / 252 SpD / 252 Spe
- Crunch
- Taunt
- Yawn
- Snarl
```

</details>


### Lendário associado

#### Kyogre

✅ **Aprovado em 27/09/2026:** fragmento e ficha do Looker (`Nexus_EventScript_Kyogre_LookerFile`) implementados em `data/scripts/nexus.inc` e `src/data/nexus/legendaries.h`. O sorteio do Daily que usa esta ligação ainda não existe.

📝 **Proposta de 27/09/2026, aguardando o autor.** **Kyogre**. Archie é o campeão dele: a quinta luta do Daily, logo antes da boss battle.

**Quem é.** Archie, líder da Team Aqua. Marinheiro barulhento de risada larga, quis expandir o mar para os Pokémon e despertou o Kyogre para isso; na crise de Sootopolis viu, junto com o Maxie, o que tinha feito.

**A criatura.** Kyogre, a personificação do mar (Água), de Hoenn. Expandiu os oceanos com chuvas torrenciais, lutou contra o Groudon e dormia no fundo do mar; com a Blue Orb assume a forma Primal, cuja chuva não para.

Fragmento e ficha do Looker: na ficha da [Misty](../kanto/misty.md); nos dias do Kyogre o sorteio escolhe entre os dois campeões.

### Diálogo genérico

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Archie_Fight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Archie cai numa das **quatro primeiras salas**, em qualquer fragmento e com qualquer lendário. Fala dele mesmo, sem citar o lugar nem a criatura do dia ([R16](../NEXUS_REGRAS.md)).

**Antes da luta**

> Fwahahaha! Well, if it isn't a fresh face! Name's Archie.
>
> Boss of Team Aqua, lover of the sea and every Pokémon living in it.
>
> Once tried to give the whole world back to the ocean. Nearly drowned it doing so.
>
> Ah, water under the bridge! Let's have ourselves a real brawl!

**Derrota**

> Fwahaha! Beaten fair and square. The sea does that to a man, too.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Archie_Intro:
	.string "Fwahahaha! Well, if it isn't a fresh\n"
	.string "face! Name's Archie.\p"
	.string "Boss of Team Aqua, lover of the sea and\n"
	.string "every Pokémon living in it.\p"
	.string "Once tried to give the whole world back\n"
	.string "to the ocean. Nearly drowned it doing\l"
	.string "so.\p"
	.string "Ah, water under the bridge! Let's have\n"
	.string "ourselves a real brawl!$"

Nexus_Text_Archie_Defeat:
	.string "Fwahaha! Beaten fair and square. The\n"
	.string "sea does that to a man, too.$"
```

</details>


### Diálogo associado ao lendário

#### Kyogre

✅ **Implementado em 27/09/2026:** `Nexus_EventScript_Archie_ChampionFight` em `data/scripts/nexus.inc`. O texto abaixo é a proposta que virou código.

📝 **Proposta de 27/09/2026, aguardando o autor.** Quando Archie é o **campeão**, a luta logo antes do Kyogre. A fala é sobre a criatura, sem dizer o nome dele.

O Archie sonhou com isso: o mundo inteiro devolvido ao mar. No fragmento, a chuva não para, e não há um Wingull no céu, porque não sobrou lugar para pousar. A virada é de marinheiro: o mar só é bonito porque há uma praia para voltar. Ele e o Maxie esqueceram lados opostos da mesma coisa; a criatura não esquece nada, só chove.

**Antes da luta**

> You feel that rain? It hasn't stopped since I got here. Won't ever stop.
>
> I used to dream about this. The whole world given back to the sea.
>
> But there's not a single Wingull in the sky. Nowhere left for 'em to land.
>
> …Fwahaha! Let's fight before I start thinking too hard!

**Derrota**

> Fwahaha… Swamped. Figures.

**Depois da luta**

> Every sailor knows it. The sea's only beautiful 'cause there's a shore to come home to.
>
> I forgot that. Maxie forgot the opposite. We made a fine pair of fools.
>
> That great beast doesn't forget anything. It just rains.
>
> Go on, then. Show it where the shore is.

<details><summary><code>.inc</code></summary>

```asm
Nexus_Text_Archie_ChampionIntro:
	.string "You feel that rain? It hasn't stopped\n"
	.string "since I got here. Won't ever stop.\p"
	.string "I used to dream about this. The whole\n"
	.string "world given back to the sea.\p"
	.string "But there's not a single Wingull in the\n"
	.string "sky. Nowhere left for 'em to land.\p"
	.string "…Fwahaha! Let's fight before I start\n"
	.string "thinking too hard!$"

Nexus_Text_Archie_ChampionDefeat:
	.string "Fwahaha… Swamped. Figures.$"

Nexus_Text_Archie_ChampionAfter:
	.string "{SPEAKER NAME_ARCHIE}Every sailor knows it. The sea's only\n"
	.string "beautiful 'cause there's a shore to\l"
	.string "come home to.\p"
	.string "I forgot that. Maxie forgot the\n"
	.string "opposite. We made a fine pair of fools.\p"
	.string "That great beast doesn't forget\n"
	.string "anything. It just rains.\p"
	.string "Go on, then. Show it where the shore is.$"
```

</details>


Falante novo: `SP_NAME_ARCHIE` (ainda não existe em `include/constants/speaker_names.h`).
