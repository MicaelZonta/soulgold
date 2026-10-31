# Revisão dos 53 times do Nexus — Singles e Doubles

Revisão estática de `times.party`, cruzada com `NEXUS_REGRAS.md` (R10–R13), `manifest.json` e os 24 arquivos de dados fornecidos em `repo/`. Os veredictos de cada treinador abaixo avaliam o **time original**; as alterações e o resultado revisado aparecem separadamente.

**Resultado:** 11 times originais não aprovados em pelo menos um formato; 42 têm um plano utilizável nos dois, alguns com ressalvas. Foram exportados **20 blocos completos alterados** em `times_revisados.party`; os outros **33 permanecem em `times.party`**. Alguns dos 20 ajustes são melhorias de robustez em times já funcionais, sem significar que o original era inviável.

“Funciona” significa ter condição de vitória, suporte/cobertura e uma sequência de jogo plausível nos dois formatos, com o mesmo elenco e os mesmos sets. Não exige vencer todo matchup. “Não aprovado” indica conflito central, legalidade não comprovada ou dependência excessiva de organizar parceiros/modos que a abertura original não sustenta. Fraqueza de tipo, um golpe situacional ou ausência de seis Protect não bastam, isoladamente, para reprovar uma equipe.

## Critérios e limites da conferência

- **R10/R11:** exatamente um lendário, um semi e uma Mega em cada elenco final; míticos classificados pela tabela das regras, sem usar BST. Paradoxos/Ultra Beasts contam como semi. Diancie de Serena/Valerie e Rayquaza de Zinnia acumulam duas vagas. Rayquaza de Hassel não tem Dragon Ascent; a Mega desse time é Salamence.
- **R13:** todos os 318 Pokémon finais têm os seis IVs em 31, os seis EVs em 252, nature, item, habilidade e quatro golpes explícitos. Não foram usados IV/EV zero para Trick Room: com R13, a baixa Speed é relativa à espécie/nature, e Gyro Ball exige cuidado adicional.
- **Legalidade:** todos os golpes finais estão no `repo/src/data/pokemon/all_learnables.json`, usando os aliases das formas e learnsets compartilhados; habilidades selecionadas foram confrontadas com `.abilities`, distinguindo-as de `.innates`. O índice é a evidência de aprendizado disponível, não uma simulação de breeding. Foram conferidos os campos de espécie, as flags de categoria, as formas Mega/custom/Gmax e a existência dos itens em `repo/src/data/items.h`.
- **Megas do hack:** pedras por tipo, Bondstone e Gigantatite foram preservadas nos portadores originais; Meganium, Floette, Crabominable, Staraptor, Eelektross e demais custom foram avaliados pelos dados locais, sem substituir seus efeitos pelos dos jogos oficiais. Mega Scolipede tem Speed 62 e Mega Staraptor possui Contrary. A contagem de Mega considera o portador da pedra ou Rayquaza com Dragon Ascent.
- **Inatas importam:** Articuno tem Snow Warning; Goodra tem Drizzle; Bellibolt/Morpeko têm Lightning Rod; Tapu Fini/Seismitoad/Walking Wake/Dragalge têm Storm Drain; Farigiraf tem Psychic Surge; Mr. Rime tem Slush Rush; Rayquaza tem Screen Cleaner. As avaliações consideram essas interações. Não deduzi o comportamento de habilidades custom apenas pelo nome.
- **Doubles:** os dois primeiros membros foram considerados a abertura normal, sem presumir escolha manual de leads ou uma IA que faça trocas perfeitas. Reordenações também estão exportadas como blocos inteiros. `Double Battle: No` foi mantido: ele decide Default, não impede a opção global Doubles descrita em R10.
- **Limite de evidência:** a cópia contém dados, mas não o motor de batalha, a implementação das habilidades/golpes, a IA, o parser `.party`, as tabelas completas de mudança de forma nem uma ROM executável. Não houve combate simulado, medição de win rate ou compilação. A legalidade de dados e a coerência dos planos foram verificadas; ativação exata das pedras genéricas/custom e decisões da IA ainda precisam de teste no jogo completo. “Após revisão: funciona” é parecer de construção do time, não resultado de playtest.

## Principais problemas corrigidos

- **Gardenia:** Growth ausente do learnset de Meganium; trocado por Work Up, com o setter de sol antecipado.
- **Iono/Nessa:** redirecionamento de golpes dos próprios parceiros por inatas de Bellibolt e Tapu Fini/Seismitoad; peças substituídas.
- **Nemona:** Drizzle de Goodra desfazia o sol; usada a forma Hisui, sem essa inata.
- **Melony:** Screen Cleaner de Mr. Rime apagava Aurora Veil; trocado por Ice Body.
- **Tulip:** Psychic Surge de Farigiraf bloqueava Bullet Punch contra alvos aterrados; prioridade removida e controle de velocidade compatibilizado com Espathra.
- **Allister/Ghetsis/Rowan/Tulip:** controladores de velocidade revistos para apoiar o núcleo rápido. Trick Room continua em Lorelei/Peony e como opção situacional de Calyrex em Melony.
- **Peonia:** Hydro Pump de Rotom-Wash não é comprovado pela cópia entregue. A ausência pode ser lacuna do índice para movimentos de forma; não afirmei ilegalidade no motor completo. Troquei por Will-O-Wisp, comprovadamente aprendível.

## Validação da entrega

Conferência automática do elenco final combinado (33 originais + 20 revisados): **53 IDs únicos do manifest, 318 Pokémon, 1.272 golpes, quatro golpes por Pokémon, itens existentes, habilidades selecionáveis, 31 IV/252 EV nos seis atributos e vagas 1/1/1 em todos os times**. Cabeçalhos/metadados originais preservados; cada bloco exportado é diferente do original e inclui os seis Pokémon completos. `times.party` e `repo/` não foram alterados.

Para aplicar: substituir pelo ID os 20 blocos correspondentes de `times.party`; `times_revisados.party` não é uma lista completa de 53 times e não deve ser concatenado ao original criando IDs duplicados.

## 01. AZ — `AZ`

**Original — Singles: Sim. Doubles: Sim, com ressalvas.**

- **Singles:** Xerneas é a condição de vitória; Celebi recupera e coloca Grassy Surge inato, Floette reforça a ofensiva de Fada, Torkoal enfrenta Aço e Sigilyph oferece burn/Tailwind. Recuperação e cobertura dão um caminho real em Singles.
- **Doubles:** Fairy Aura beneficia o núcleo e Golurk usa High Horsepower sem atingir o parceiro. A dupla original Xerneas/Celebi é muito passiva durante Geomancy; o suporte existe, mas chega tarde. Ajustei a abertura e dei Protect ao lendário.

**Vagas após revisão:** lendário Xerneas; semi-lendário Celebi; Mega Floette-Eternal.

**Alteração exportada:** Sigilyph + Xerneas abrem; Grass Knot → Protect em Xerneas. Tailwind cria ritmo e Protect permite cobrir o turno de pressão dupla; Celebi, Floette e Torkoal sustentam o núcleo de Fada/Planta e cobrem Aço.

**Após revisão:** funciona no papel em Singles e Doubles, com as ressalvas de execução indicadas acima.


## 02. Agatha — `AGATHA`

**Original — Singles: Sim. Doubles: Sim.**

- **Singles:** Status de Gengar/Arbok fortalece Hex, enquanto Spectrier e Marshadow pressionam defesas diferentes. Mega Gengar prende alvos e Marshadow impede que setup adversário vire uma vitória livre.
- **Doubles:** Crobat fornece Tailwind/Taunt, Arbok Intimidate/Glare, Marowak absorve Elétrico para Crobat e os principais atacantes possuem Protect. Bonemerang não causa o dano aliado de Earthquake. A dupla inicial é rápida e ofensiva; não exige Trick Room.

**Vagas após revisão:** lendário Marshadow; semi-lendário Spectrier; Mega Gengar.

**Decisão:** manter o bloco original; plano funcional nos dois formatos.


## 03. Alder — `ALDER`

**Original — Singles: Sim. Doubles: Sim.**

- **Singles:** Groudon estabelece sol para Slither Wing e Volcarona, Mega Scolipede explora pressão física/status e Druddigon espalha Glare. Hazards e Dragon Tail prolongam a pressão em Singles.
- **Doubles:** Precipice Blades acerta os adversários; Rage Powder de Volcarona oferece janela para o parceiro e Glare compensa a velocidade dos mais lentos. Mega Scolipede tem Speed base 62 nesta cópia: não o trate como um cleaner naturalmente veloz. O plano é sol + suporte, não seis atacantes rápidos.

**Vagas após revisão:** lendário Groudon; semi-lendário Slither Wing; Mega Scolipede.

**Decisão:** manter o bloco original; plano funcional nos dois formatos.


## 04. Allister — `ALLISTER`

**Original — Singles: Sim, com ressalvas. Doubles: Não aprovado.**

- **Singles:** Lunala, Spectrier e Mega Gengar conseguem abrir espaço por pressão especial; Mimikyu e os dois fantasmas lentos oferecem uma alternativa de Trick Room. Em Singles é possível separar essas fases por trocas.
- **Doubles:** A abertura Lunala/Spectrier não oferece controle de velocidade nem proteção ao Calm Mind de Lunala. O único Trick Room chega com Mimikyu e também atrapalha Spectrier/Mega Gengar quando coexistem em campo. A equipe depende de uma seleção de parceiros que não está garantida pela IA; substituí a inversão por redução da velocidade inimiga.

**Vagas após revisão:** lendário Lunala; semi-lendário Spectrier; Mega Gengar.

**Alteração exportada:** Mimikyu + Lunala abrem; Mimikyu passa a Jolly e troca Trick Room por Thunder Wave; Dusknoir troca Ice Punch por Icy Wind. O controle agora reduz a velocidade adversária sem inverter a dos próprios Spectrier e Mega Gengar; os lentos continuam como retaguarda resistente.

**Após revisão:** funciona no papel em Singles e Doubles, com as ressalvas de execução indicadas acima.


## 05. Avery — `AVERY`

**Original — Singles: Sim, com ressalvas. Doubles: Sim.**

- **Singles:** Psychic Surge fortalece o núcleo Psíquico e Healing Wish permite recuperar um atacante. Indeedee tem dois golpes exclusivamente de suporte a parceiro, perdendo bastante utilidade em Singles; ainda pode atacar e depois se sacrificar.
- **Doubles:** Indeedee + Mewtwo já oferece terreno e Follow Me para Calm Mind. Mega Alakazam e Articuno-Galar exploram esse campo; Slowking faz pivot com Regenerator. Dei cobertura a Indeedee e Tailwind ao semi-lendário para o mesmo elenco ter mais opções nos dois modos.

**Vagas após revisão:** lendário Mewtwo; semi-lendário Articuno-Galar; Mega Alakazam.

**Alteração exportada:** Indeedee troca Helping Hand por Dazzling Gleam, oferecendo cobertura real em Singles sem perder Follow Me; Articuno-Galar troca Calm Mind por Tailwind. Terreno + redirecionamento continuam protegendo o setup de Mewtwo e a ofensiva de Mega Alakazam.

**Após revisão:** funciona no papel em Singles e Doubles, com as ressalvas de execução indicadas acima.


## 06. Barry — `BARRY`

**Original — Singles: Sim. Doubles: Sim, com ressalvas.**

- **Singles:** Deoxys fornece Taunt/hazards, Uxie e Staraptor fazem pivot, Heracross rompe paredes e Snorlax pode finalizar após Belly Drum. Mega Staraptor tem Contrary nesta cópia e aproveita Close Combat.
- **Doubles:** Tailwind e Helping Hand existem, mas a dupla inicial Deoxys/Uxie concentra suporte e a resposta ofensiva demora. Snorlax também não tinha Protect após Belly Drum. Mantive o plano de pivot e fiz ajustes de abertura, velocidade e preservação do setup.

**Vagas após revisão:** lendário Deoxys-Speed; semi-lendário Uxie; Mega Staraptor.

**Alteração exportada:** Deoxys-Speed + Staraptor abrem, com Taunt, pressão e Tailwind disponíveis desde o início; Uxie troca Helping Hand por Thunder Wave e Snorlax troca Heavy Slam por Protect. O pivot por U-turn continua sendo a ligação entre os atacantes e a janela de Belly Drum.

**Após revisão:** funciona no papel em Singles e Doubles, com as ressalvas de execução indicadas acima.


## 07. Bea — `BEA`

**Original — Singles: Sim. Doubles: Sim.**

- **Singles:** Marshadow recupera boosts adversários e Urshifu quebra defesas/Protect; Mega Hawlucha e Falinks oferecem setup. Sirfetchd reforça a cobertura física e Hitmontop remove hazards.
- **Doubles:** Hitmontop fornece Fake Out, Intimidate e Wide Guard; Sirfetchd oferece Quick Guard, e Hawlucha/Falinks possuem proteção individual. A pressão dos dois primeiros permite jogar antes do suporte entrar. As fraquezas a Fada/Psíquico são um matchup difícil, não uma ausência de plano.

**Vagas após revisão:** lendário Marshadow; semi-lendário Urshifu-Rapid-Strike; Mega Hawlucha.

**Decisão:** manter o bloco original; plano funcional nos dois formatos.


## 08. Brycen — `BRYCEN`

**Original — Singles: Sim. Doubles: Sim.**

- **Singles:** Articuno tem Snow Warning inato, além do Snow Warning selecionado de Abomasnow e do inato de Beartic. Portanto a neve não depende só de Abomasnow: Blizzard e Slush Rush têm suporte real.
- **Doubles:** Kyurem + Articuno já abrem com a neve necessária; Froslass oferece Icy Wind/burn, e High Horsepower de Mamoswine preserva o parceiro. Mega Abomasnow e Beartic possuem Protect. Haze de Articuno deve ser reservado para boosts inimigos.

**Vagas após revisão:** lendário Kyurem; semi-lendário Articuno; Mega Abomasnow.

**Decisão:** manter o bloco original; plano funcional nos dois formatos.


## 09. Cheren — `CHEREN`

**Original — Singles: Sim. Doubles: Sim.**

- **Singles:** Intimidate de Stoutland, Encore/Thunder Wave de Liepard e Fake Out de Kangaskhan criam oportunidades para Cobalion/Samurott; Kyurem pressiona o lado especial.
- **Doubles:** O mesmo controle de turnos funciona ao lado de Kyurem ou da Mega. Liepard tem Foul Play para continuar útil e Stoutland usa Protect. A abertura é ofensiva, enquanto a retaguarda fornece interrupção; não depende de hazards para funcionar.

**Vagas após revisão:** lendário Kyurem; semi-lendário Cobalion; Mega Kangaskhan.

**Decisão:** manter o bloco original; plano funcional nos dois formatos.


## 10. Cilan — `CILAN`

**Original — Singles: Sim. Doubles: Sim.**

- **Singles:** Groudon fornece sol a Solar Beam de Mega Sceptile e ao Chlorophyll inato de Simisage; Virizion e Crustle dão alternativas físicas. Whimsicott acrescenta Encore e Tailwind.
- **Doubles:** Groudon + Whimsicott abre com clima e controle de velocidade. Precipice Blades não fere o parceiro, Sceptile possui Protect e Lightning Rod da Mega protege contra Elétrico sem bloquear nenhum golpe elétrico aliado deste elenco.

**Vagas após revisão:** lendário Groudon; semi-lendário Virizion; Mega Sceptile.

**Decisão:** manter o bloco original; plano funcional nos dois formatos.


## 11. Cynthia — `CYNTHIA`

**Original — Singles: Sim. Doubles: Sim.**

- **Singles:** Azelf fornece hazards/Taunt/pivot; Spiritomb queima, Milotic recupera e contém setup, e Mega Garchomp aproveita o desgaste. Giratina fornece pressão e cobertura contra imunidades.
- **Doubles:** Togekiss tem Follow Me e Friend Guard inato, Milotic pune Intimidate com Competitive e Spiritomb reduz o dano físico. Stomping Tantrum evita dano aliado. Haze de Milotic é situacional, pois também remove Swords Dance de Garchomp.

**Vagas após revisão:** lendário Giratina-Origin; semi-lendário Azelf; Mega Garchomp.

**Decisão:** manter o bloco original; plano funcional nos dois formatos.


## 12. Cyrus — `CYRUS`

**Original — Singles: Sim. Doubles: Sim.**

- **Singles:** Mesprit faz pivot/Healing Wish, Dialga espalha Thunder Wave e Mega Gyarados explora as aberturas. Crobat impede suporte e Weavile oferece pressão imediata.
- **Doubles:** Fake Out de Weavile, Tailwind de Crobat, Intimidate de Gyarados e Armor Tail inato de Mesprit apoiam a ofensiva. Não há Earthquake/Surf atrapalhando aliados. O núcleo funciona por controle de turnos e pivot mesmo quando Stealth Rock perde valor.

**Vagas após revisão:** lendário Dialga-Origin; semi-lendário Mesprit; Mega Gyarados.

**Decisão:** manter o bloco original; plano funcional nos dois formatos.


## 13. Dawn — `DAWN`

**Original — Singles: Sim. Doubles: Sim.**

- **Singles:** Cresselia e Togekiss sustentam Palkia/Mega Lopunny, Empoleon cobre Fada e Mamoswine oferece pressão física de Gelo/Terra. Recuperação e Thunder Wave mantêm o plano fora de Doubles.
- **Doubles:** Follow Me/Friend Guard de Togekiss e Fake Out de Lopunny criam turnos, enquanto Cresselia paralisa. High Horsepower é seguro ao lado dos parceiros. Thunder de Palkia continua sendo uma opção de 70% de precisão sem chuva; não o trate como cobertura garantida.

**Vagas após revisão:** lendário Palkia; semi-lendário Cresselia; Mega Lopunny.

**Decisão:** manter o bloco original; plano funcional nos dois formatos.


## 14. Diantha — `DIANTHA`

**Original — Singles: Sim. Doubles: Sim.**

- **Singles:** Fairy Aura liga Xerneas, Iron Valiant e Mega Gardevoir; Encore e burn de Gourgeist abrem janelas para os boosters físicos. Há pressão física e especial, em vez de depender só de Geomancy.
- **Doubles:** Dazzling Gleam/Hyper Voice oferecem pressão de área, Gardevoir tem Friend Guard inato e Protect, e Iron Valiant pode usar Encore. Gourgeist protege/queima. A abertura agressiva tem menos proteção ao setup que uma dupla de redirecionamento, mas ainda dispõe de ataque imediato e interrupção.

**Vagas após revisão:** lendário Xerneas; semi-lendário Iron Valiant; Mega Gardevoir.

**Decisão:** manter o bloco original; plano funcional nos dois formatos.


## 15. Gardenia — `GARDENIA`

**Original — Singles: Não aprovado. Doubles: Não aprovado.**

- **Singles:** Existe uma ideia reconhecível: sol, plantas, Flower Gift para os físicos, Protosynthesis de Shaymin-Sky e setup de Zygarde. Porém Growth não pertence ao learnset de Meganium fornecido: o bloco não passa pela legalidade exigida.
- **Doubles:** O mesmo golpe inválido impede aprovação. Além disso, Cherrim estava por último, atrasando o único Sunny Day explicitamente selecionado. Antecipei o setter e usei Work Up; a Mega continua sendo a Meganium custom, sem presumir efeitos não documentados de Mega Sol.

**Vagas após revisão:** lendário Zygarde-50-Power-Construct; semi-lendário Shaymin-Sky; Mega Meganium.

**Alteração exportada:** Growth ilegal no learnset fornecido vira Work Up; Cherrim + Zygarde abrem. Sunny Day fica disponível imediatamente para Solar Beam/Synthesis e Protosynthesis de Shaymin-Sky; Flower Gift tem parceiros físicos em Zygarde e Torterra. Não presumi o efeito de Mega Sol para dispensar o setter explícito.

**Após revisão:** funciona no papel em Singles e Doubles, com as ressalvas de execução indicadas acima.


## 16. Ghetsis — `GHETSIS`

**Original — Singles: Sim, com ressalvas. Doubles: Não aprovado.**

- **Singles:** Kyurem-White, Hydreigon e Mega Gyarados têm cobertura e pressão suficiente, com Cofagrigus oferecendo burn e uma inversão situacional contra ofensivas mais rápidas.
- **Doubles:** Trick Room de Cofagrigus não combina com os parceiros rápidos nem com Dragon Dance de Gyarados; não há Fake Out/redirecionamento para organizar essa transição. A versão revisada usa Thunder Wave/Icy Wind para apoiar os mesmos atacantes sem inverter a ordem.

**Vagas após revisão:** lendário Kyurem-White; semi-lendário Cobalion; Mega Gyarados.

**Alteração exportada:** Cobalion + Kyurem-White abrem; Swords Dance de Cobalion vira Thunder Wave e Trick Room de Cofagrigus vira Icy Wind. O plano passa a ser desacelerar o adversário para Kyurem, Hydreigon e Mega Gyarados, preservando a cobertura elétrica de Eelektross.

**Após revisão:** funciona no papel em Singles e Doubles, com as ressalvas de execução indicadas acima.


## 17. Gloria — `GLORIA`

**Original — Singles: Sim. Doubles: Sim.**

- **Singles:** Rillaboom faz pivot e cura o campo; Zacian e Mega Lucario são condições de vitória físicas, enquanto Inteleon fornece dano especial. Corviknight sustenta e controla velocidade.
- **Doubles:** Fake Out/Grassy Glide de Rillaboom, Tailwind de Corviknight e ataques que não acertam aliados sustentam Zacian/Urshifu. Grassy Terrain não bloqueia a própria prioridade e ajuda o elenco. O núcleo não precisa gastar todos os turnos em Swords Dance.

**Vagas após revisão:** lendário Zacian; semi-lendário Urshifu-Rapid-Strike; Mega Lucario.

**Decisão:** manter o bloco original; plano funcional nos dois formatos.


## 18. Grusha — `GRUSHA`

**Original — Singles: Sim, com ressalvas. Doubles: Não aprovado.**

- **Singles:** Neve, Aurora Veil e Slush Rush de Cetitan formam um plano válido, com Mega Altaria cobrindo pelo lado de Fada e Frosmoth protegendo contra área. Ninetales no último slot obriga uma troca precoce para ativar o plano.
- **Doubles:** A dupla inicial Kyurem/Chien-Pao não tem neve, Veil nem Protect, e Sword of Ruin expõe também a defesa de Kyurem. O setter essencial fica no fim. Corrigi a abertura e dei proteção a Chien-Pao; isso mantém o tema de gelo sem exigir absorver dois ataques antes do suporte.

**Vagas após revisão:** lendário Kyurem; semi-lendário Chien-Pao; Mega Altaria.

**Alteração exportada:** Ninetales-Alola + Kyurem abrem para neve/Blizzard/Aurora Veil já no começo; Chien-Pao troca Ice Shard por Protect, mantendo Sucker Punch como prioridade. Sword of Ruin também reduz a defesa dos aliados: Veil e Protect ajudam a administrar esse custo. Cetitan continua aproveitando neve; Altaria oferece Tailwind e cobertura de Fada.

**Após revisão:** funciona no papel em Singles e Doubles, com as ressalvas de execução indicadas acima.


## 19. Hassel — `HASSEL`

**Original — Singles: Sim. Doubles: Sim.**

- **Singles:** Rayquaza mantém cobertura e prioridade sem Dragon Ascent, deixando a vaga de Mega para Salamence. Regidrago oferece Dragon Energy, Noivern Tailwind e Baxcalibur uma rota de setup com Loaded Dice.
- **Doubles:** Salamence intimida, Noivern acelera e vários atacantes possuem Protect. Dragalge traz resistência especial e Storm Drain inato, mas não há outro usuário de Água de alvo único neste time para ser prejudicado. Air Lock de Rayquaza deve ser lembrado ao avaliar a chuva inata de Goodra: o plano principal é pressão de Dragão, não clima.

**Vagas após revisão:** lendário Rayquaza; semi-lendário Regidrago; Mega Salamence.

**Decisão:** manter o bloco original; plano funcional nos dois formatos.


## 20. Hau — `HAU`

**Original — Singles: Sim. Doubles: Sim.**

- **Singles:** Tapu Koko e o Electric Surge inato de Raichu-Alola alimentam Surge Surfer. Solgaleo/Mega Crabominable rompem pelo lado físico, Tauros intimida e Decidueye cobre Água/Terra.
- **Doubles:** Terreno elétrico, Volt Switch e Intimidate permitem reposicionar os atacantes, e os mais lentos possuem Protect. Raichu não está preso a um golpe de suporte por Choice Specs. O sono adversário também fica limitado para os aliados aterrados; não há plano de sono próprio sendo bloqueado.

**Vagas após revisão:** lendário Solgaleo; semi-lendário Tapu Koko; Mega Crabominable.

**Decisão:** manter o bloco original; plano funcional nos dois formatos.


## 21. Hilda — `HILDA`

**Original — Singles: Sim. Doubles: Sim.**

- **Singles:** Reshiram e Mega Emboar pressionam com Fogo por lados diferentes, Jellicent fornece burn/recuperação e Excadrill cobre Rocha/Fada. Tornadus e Galvantula dão velocidade/pivot.
- **Doubles:** Reshiram + Tornadus abre com pressão de área e Tailwind prioritário. Galvantula pode usar Electroweb mesmo com Choice Specs; Excadrill usa High Horsepower e Emboar Protect. Thunder de Galvantula depende de precisão aumentada por Compound Eyes, não de uma chuva que não foi selecionada.

**Vagas após revisão:** lendário Reshiram; semi-lendário Tornadus; Mega Emboar.

**Decisão:** manter o bloco original; plano funcional nos dois formatos.


## 22. Hop — `HOP`

**Original — Singles: Sim. Doubles: Sim, com ressalvas.**

- **Singles:** Zamazenta e Dubwool usam defesa como ofensiva; Snorlax é o terceiro caminho resistente, e Silvally conserva o ritmo com Parting Shot. Corviknight/Cramorant oferecem Tailwind.
- **Doubles:** Intenção defensiva e pivot sobrevivem ao formato, mas três boosters duráveis sem proteção coletiva podem ceder muitos turnos para foco duplo. Wide Guard em Zamazenta reforça o plano sem substituir o núcleo ou retirar o único lendário/Mega.

**Vagas após revisão:** lendário Zamazenta; semi-lendário Silvally; Mega Snorlax.

**Alteração exportada:** Zamazenta troca Crunch por Wide Guard. A equipe mantém o plano de defesa/Body Press em Singles e ganha proteção coletiva contra golpes de área enquanto Snorlax, Dubwool e Zamazenta se fortalecem em Doubles; Silvally continua como pivot.

**Após revisão:** funciona no papel em Singles e Doubles, com as ressalvas de execução indicadas acima.


## 23. Iono — `IONO`

**Original — Singles: Sim. Doubles: Não aprovado.**

- **Singles:** Miraidon estabelece terreno para o núcleo elétrico, Regieleki controla velocidade, Mega Eelektross cobre resistências e Mismagius dá imunidade a Terra. Bellibolt não desvia os próprios aliados em Singles porque eles não coexistem em campo.
- **Doubles:** Bellibolt possui Lightning Rod inato: mesmo com Electromorphosis selecionado, pode redirecionar Electro Drift, Thunderbolt e Volt Switch dos parceiros. Isso interrompe o ataque e o pivot que deveriam ligar o time. Substituí Bellibolt por Rotom-Wash, preservando Mismagius e o núcleo elétrico.

**Vagas após revisão:** lendário Miraidon; semi-lendário Regieleki; Mega Eelektross.

**Alteração exportada:** Bellibolt é substituído por Rotom-Wash (Thunderbolt / Will-O-Wisp / Volt Switch / Protect), removendo Lightning Rod da própria equipe; Kilowattrel + Miraidon abrem. O terreno elétrico alimenta Miraidon/Regieleki/Mega Eelektross, e o pivot de Rotom oferece imunidade a Terra sem desviar Electro Drift e Volt Switch.

**Após revisão:** funciona no papel em Singles e Doubles, com as ressalvas de execução indicadas acima.


## 24. Iris — `IRIS`

**Original — Singles: Sim. Doubles: Sim.**

- **Singles:** Latias fornece recuperação e Calm Mind; Reshiram/Mega Salamence/Haxorus atacam por lados diferentes, Lapras cobre Gelo/Água e Archeops controla velocidade. Dragon Dance não depende de outro formato.
- **Doubles:** Salamence e o Intimidate inato de Haxorus reduzem dano físico, Archeops oferece Tailwind e Armor Tail inato, e a Mega/Archeops têm Protect. Latias traz Air Lock inato, mas o elenco não depende de um clima para executar seu plano.

**Vagas após revisão:** lendário Reshiram; semi-lendário Latias; Mega Salamence.

**Decisão:** manter o bloco original; plano funcional nos dois formatos.


## 25. Jess&James — `JESSIE_JAMES`

**Original — Singles: Sim. Doubles: Sim.**

- **Singles:** Mew cria hazards/status/Tailwind, Mewtwo quebra pelo especial e Mega Gyarados pelo físico; Arbok paralisa e Victreebel ameaça sono. Meowth faz pivot e conserva utilidade com Knock Off.
- **Doubles:** Fake Out/Feint de Meowth, Intimidate de Gyarados/Arbok e Tailwind de Mew apoiam os atacantes. Não há Psychic Terrain próprio bloqueando Fake Out. Meowth é frágil mesmo com Eviolite, mas seus golpes têm uma função concreta e não são o único suporte do time.

**Vagas após revisão:** lendário Mewtwo; semi-lendário Mew; Mega Gyarados.

**Decisão:** manter o bloco original; plano funcional nos dois formatos.


## 26. Juniper — `JUNIPER`

**Original — Singles: Sim. Doubles: Sim.**

- **Singles:** Amoonguss gera sono e recupera ao trocar; Genesect mantém pivot, Meloetta oferece dano especial e Mega Audino suporte resistente. Cinccino e Sawsbuck quebram pelo físico.
- **Doubles:** Amoonguss + Genesect já oferece Rage Powder/Spore ao lado de pressão e U-turn; Audino tem Friend Guard/Triage inatos e Heal Pulse. Amoonguss ainda ataca com Pollen Puff/Clear Smog em Singles, evitando depender apenas de redirecionamento.

**Vagas após revisão:** lendário Genesect; semi-lendário Meloetta; Mega Audino.

**Decisão:** manter o bloco original; plano funcional nos dois formatos.


## 27. Katy — `KATY`

**Original — Singles: Sim. Doubles: Sim, com ressalvas.**

- **Singles:** Genesect e Mega Beedrill usam U-turn para trazer Slither Wing/Ursaring; Forretress fornece hazards/remoção e Vivillon cria janelas com Sleep Powder. Há um plano de pivot e desgaste.
- **Doubles:** Sleep Powder e First Impression fornecem interrupção imediata, e Ursaring/Slither Wing/Vivillon possuem Protect. Forretress perde bastante valor com hazards em Doubles, e falta Tailwind, mas a ofensiva não depende deles: pivots e sono continuam ativos. É menos flexível que Juniper/Viola, sem um conflito interno que exija troca.

**Vagas após revisão:** lendário Genesect; semi-lendário Slither Wing; Mega Beedrill.

**Decisão:** manter o bloco original; plano funcional nos dois formatos.


## 28. Klara — `KLARA`

**Original — Singles: Sim. Doubles: Sim.**

- **Singles:** Eternatus e Slowbro-Galar oferecem dano especial/cobertura; Toxic Chain de Munkidori e os venenos da equipe alimentam Merciless de Beedrill/Scolipede. Weezing queima e limita suporte.
- **Doubles:** Eternatus + Munkidori tem Fake Out e U-turn desde a abertura; os venenos e Protect de Scolipede sustentam a pressão. Weezing usa Levitate, evitando Neutralizing Gas sobre o próprio elenco. Toxic Spikes é secundário: o plano de veneno não depende só dele.

**Vagas após revisão:** lendário Eternatus; semi-lendário Munkidori; Mega Beedrill.

**Decisão:** manter o bloco original; plano funcional nos dois formatos.


## 29. Korrina — `KORRINA`

**Original — Singles: Sim. Doubles: Sim.**

- **Singles:** Mienshao/Urshifu/Koraidon fazem pivot ofensivo, Mega Lucario é a condição de setup e Hawlucha ativa Unburden com White Herb + Close Combat. O sol de Koraidon fortalece Flare Blitz.
- **Doubles:** Mienshao + Koraidon abre com Fake Out/Wide Guard e pressão; Hitmontop acrescenta outra camada de Fake Out/Intimidate/Wide Guard. Urshifu é Single Strike, então não perde o STAB de Água para o próprio sol. O plano de pressão e interrupção é o mesmo nos dois modos.

**Vagas após revisão:** lendário Koraidon; semi-lendário Urshifu; Mega Lucario.

**Decisão:** manter o bloco original; plano funcional nos dois formatos.


## 30. Larry — `LARRY`

**Original — Singles: Sim. Doubles: Sim.**

- **Singles:** Terapagos oferece setup resistente, Staraptor pivot/Intimidate e Dudunsparce Body Slam/Coil; Mega Pidgeot cobre pelo especial. Tornadus e Flamigo dão controle de velocidade.
- **Doubles:** Terapagos + Tornadus já possui Tailwind prioritário e Protect, com Staraptor para reduzir dano físico e vários ataques seguros de área. Tera Starstorm foi avaliado sem presumir que o treinador terá Terastalização disponível; a forma Stellar não é necessária para o plano básico.

**Vagas após revisão:** lendário Terapagos; semi-lendário Tornadus; Mega Pidgeot.

**Decisão:** manter o bloco original; plano funcional nos dois formatos.


## 31. Lenora — `LENORA`

**Original — Singles: Sim. Doubles: Sim, com ressalvas.**

- **Singles:** Arceus usa Swords Dance/Extreme Speed, Meloetta oferece pressão especial, Mega Kangaskhan dano físico e Stoutland Intimidate. Watchog desgasta com Super Fang e Braviary fornece Tailwind.
- **Doubles:** O controle de velocidade e Intimidate existem, mas a abertura Arceus/Meloetta não impede foco duplo no turno de setup. Acrescentei Fake Out à Mega e a trouxe para a abertura; o núcleo de Normais mantém sua função de dano misto e prioridade.

**Vagas após revisão:** lendário Arceus; semi-lendário Meloetta; Mega Kangaskhan.

**Alteração exportada:** Kangaskhan + Arceus abrem; Ice Punch de Kangaskhan vira Fake Out. Fake Out cria uma janela para Swords Dance ou um ataque livre de Arceus; Meloetta cobre o lado especial, Stoutland intimida e Braviary fornece Tailwind. Fake Out também tem utilidade imediata em Singles.

**Após revisão:** funciona no papel em Singles e Doubles, com as ressalvas de execução indicadas acima.


## 32. Leon — `LEON`

**Original — Singles: Sim. Doubles: Sim.**

- **Singles:** Eternatus usa Meteor Beam + Power Herb, Urshifu faz pivot e quebra proteção, e Mega Charizard reforça Fogo. Dragapult oferece telas e burn para os atacantes, Aegislash cobertura/prioridade.
- **Doubles:** Telas/Wisp, King’s Shield e pressão imediata da dupla inicial permitem jogar sem depender exclusivamente de setup. O Storm Drain inato de Seismitoad não bloqueia nenhum golpe de Água aliado, pois ele é o único usuário desse tipo de ataque no elenco; Muddy Water também é de área.

**Vagas após revisão:** lendário Eternatus; semi-lendário Urshifu; Mega Charizard.

**Decisão:** manter o bloco original; plano funcional nos dois formatos.


## 33. Lorelei — `LORELEI`

**Original — Singles: Sim, com ressalvas. Doubles: Sim, com ressalvas.**

- **Singles:** Slowbro/Jynx podem abrir Trick Room para Glastrier/Mega Lapras, enquanto Cloyster oferece o modo rápido. O plano existe, mas a ordem original começa com Glastrier sem seu setter e Blizzard de Kyurem não tem neve explicitamente garantida.
- **Doubles:** Dois setters, Protect de Glastrier/Lapras e Lovely Kiss dão uma rota real de Trick Room. A entrada tardia do setter torna essa rota mais custosa; antecipei Slowbro, protegi-o de Taunt com Mental Herb e removi a dependência de Blizzard. O time tem duas velocidades: Shell Smash deve ficar para a fase fora de Trick Room.

**Vagas após revisão:** lendário Kyurem; semi-lendário Glastrier; Mega Lapras.

**Alteração exportada:** Slowbro + Glastrier abrem; Slowbro recebe Mental Herb e Kyurem troca Blizzard por Ice Beam, pois não há Snow Warning explícito no time. Trick Room dá uma janela a Glastrier/Lapras; Cloyster e Jynx preservam o modo rápido depois dela. Não se deve usar Shell Smash enquanto ainda se pretende abusar de Trick Room.

**Após revisão:** funciona no papel em Singles e Doubles, com as ressalvas de execução indicadas acima.


## 34. Lysandre — `LYSANDRE`

**Original — Singles: Sim. Doubles: Sim.**

- **Singles:** Dark Aura liga Yveltal/Mega Gyarados/Honchkrow, Volcanion cobre Aço/Fada e Mienshao mantém pivot. Pyroar fornece dano de área e Intimidate inato.
- **Doubles:** Mienshao usa Fake Out/Wide Guard, Gyarados intimida e os ataques de área de Yveltal/Volcanion/Pyroar não acertam aliados. Water Absorb de Volcanion não redireciona Waterfall de Gyarados; não deve ser confundido com Storm Drain.

**Vagas após revisão:** lendário Yveltal; semi-lendário Volcanion; Mega Gyarados.

**Decisão:** manter o bloco original; plano funcional nos dois formatos.


## 35. Marnie — `MARNIE`

**Original — Singles: Sim. Doubles: Sim.**

- **Singles:** Telas de Grimmsnarl sustentam Moltres-Galar/Absol, Yveltal reforça os golpes de Trevas e Morpeko mantém pivot com Parting Shot. Toxicroak cobre tipos que resistem ao núcleo.
- **Doubles:** Grimmsnarl + Moltres-Galar já oferece Fake Out/telas para Nasty Plot; Fiery Wrath/Heat Wave pressionam em área. Morpeko tem Lightning Rod inato, mas não há outro atacante elétrico aliado para ser prejudicado aqui. Ao contrário de Iono, essa inata não desmonta o plano.

**Vagas após revisão:** lendário Yveltal; semi-lendário Moltres-Galar; Mega Absol.

**Decisão:** manter o bloco original; plano funcional nos dois formatos.


## 36. Melony — `MELONY`

**Original — Singles: Não aprovado. Doubles: Não aprovado.**

- **Singles:** A ideia de neve + Aurora Veil + atacantes de Gelo é boa, mas Mr. Rime com Screen Cleaner apaga a própria proteção ao entrar. Isso destrói um recurso central também em Singles.
- **Doubles:** O mesmo conflito remove o Veil dos dois parceiros; além disso, Trick Room de Mr. Rime disputa espaço com seu Slush Rush inato e Quiver Dance de Frosmoth. Troquei a habilidade e dei Fake Out. O Trick Room de Calyrex permanece apenas para matchups em que o núcleo lento precisa inverter a ordem.

**Vagas após revisão:** lendário Calyrex-Ice; semi-lendário Articuno; Mega Lapras.

**Alteração exportada:** Mr. Rime usa Ice Body em vez de Screen Cleaner, passa a Timid e troca Trick Room por Fake Out. Assim conserva Aurora Veil e aproveita Slush Rush inato. Trick Room de Calyrex fica como recurso situacional contra equipes mais rápidas; não é o modo de jogo obrigatório de Frosmoth/Mr. Rime.

**Após revisão:** funciona no papel em Singles e Doubles, com as ressalvas de execução indicadas acima.


## 37. Molly — `MOLLY`

**Original — Singles: Sim. Doubles: Sim, com ressalvas.**

- **Singles:** Xerneas é o finalizador especial, Clefable fornece recuperação/paralisia, Entei e Granbull reduzem a pressão adversária e Kingdra/Ursaring apresentam rotas distintas de dano.
- **Doubles:** Intimidate, Snarl e Thunder Wave funcionam, mas Geomancy/Calm Mind/Focus Energy disputam turnos sem redirecionamento e Xerneas não tem Protect. Tornei Clefable a guardiã do setup, preservando os seis Pokémon e o tema de Molly.

**Vagas após revisão:** lendário Xerneas; semi-lendário Entei; Mega Clefable.

**Alteração exportada:** Clefable + Xerneas abrem; Clefable troca Calm Mind por Follow Me e Xerneas troca Grass Knot por Protect. A Mega protege o setup do lendário, Entei usa Snarl e Granbull Intimidate/Thunder Wave; Kingdra e Ursaring oferecem formas distintas de romper defesas. Clefable continua atacando/curando/paralisando em Singles.

**Após revisão:** funciona no papel em Singles e Doubles, com as ressalvas de execução indicadas acima.


## 38. Mustard — `MUSTARD`

**Original — Singles: Sim. Doubles: Sim.**

- **Singles:** Koraidon e Urshifu mantêm pressão/pivot, Mega Lucario explora as aberturas e Corviknight oferece recuperação/Tailwind. Luxray cobre ameaças de Água/Voador pelo físico.
- **Doubles:** Mienshao + Koraidon abre com Fake Out/Wide Guard; Corviknight acelera e Luxray intimida. Urshifu Single Strike não perde potência de Água para o sol, e não há golpes de área que danifiquem o parceiro. A mesma sequência de interrupção e pressão funciona em Singles.

**Vagas após revisão:** lendário Koraidon; semi-lendário Urshifu; Mega Lucario.

**Decisão:** manter o bloco original; plano funcional nos dois formatos.


## 39. N — `N`

**Original — Singles: Sim. Doubles: Sim.**

- **Singles:** Zekrom e Thundurus ligam pressão elétrica/paralisia, Zoroark faz pivot e Mega Audino fornece uma condição resistente com Calm Mind. Carracosta/Klinklang representam duas rotas físicas de setup.
- **Doubles:** Thundurus tem Drizzle inato, que ajuda Carracosta sem contrariar um setter de sol próprio. Thunder Wave/Taunt e Heal Pulse/Friend Guard de Audino sustentam os atacantes. Zekrom e Klinklang têm Protect; a equipe pode atacar imediatamente sem exigir três setups ao mesmo tempo.

**Vagas após revisão:** lendário Zekrom; semi-lendário Thundurus; Mega Audino.

**Decisão:** manter o bloco original; plano funcional nos dois formatos.


## 40. Nemona — `NEMONA`

**Original — Singles: Não aprovado. Doubles: Não aprovado.**

- **Singles:** Koraidon + Walking Wake deveria explorar sol, Protosynthesis e Hydro Steam, com Pawmot abrindo espaço e Mega Gallade rompendo pelo físico. Porém Goodra possui Drizzle inato e troca o clima ao entrar, desfazendo essa ligação.
- **Doubles:** O conflito climático também ocorre com Goodra ao lado de Koraidon/Walking Wake. Troquei somente a forma de Goodra, mantendo a identidade de dragão resistente e o mesmo conjunto ofensivo, agora sem Drizzle.

**Vagas após revisão:** lendário Koraidon; semi-lendário Walking Wake; Mega Gallade.

**Alteração exportada:** Goodra vira Goodra-Hisui, com o mesmo Assault Vest, Sap Sipper e quatro golpes legais. A forma de Hisui não possui Drizzle nas inatas fornecidas; portanto preserva o sol de Koraidon, Protosynthesis e Hydro Steam de Walking Wake, além de acrescentar resistência a Fada pelo tipo Aço.

**Após revisão:** funciona no papel em Singles e Doubles, com as ressalvas de execução indicadas acima.


## 41. Nessa — `NESSA`

**Original — Singles: Sim. Doubles: Não aprovado.**

- **Singles:** Chuva de Kyogre acelera Drednaw/Barraskewda e fortalece os atacantes de Água; Mega Gyarados usa Intimidate/setup e Tapu Fini dá uma opção especial resistente. Storm Drain não interfere entre membros que não estão simultaneamente em campo.
- **Doubles:** Tapu Fini e Seismitoad possuem Storm Drain inato. Water Spout/Origin Pulse/Muddy Water são de área e não são o problema; Waterfall de Gyarados e Liquidation dos Swift Swim são de alvo único e podem ser desviados para o aliado. Substituí ambos os redirecionadores para a chuva beneficiar todo o elenco.

**Vagas após revisão:** lendário Kyogre; semi-lendário Suicune; Mega Gyarados.

**Alteração exportada:** Tapu Fini vira Suicune (Scald / Snarl / Calm Mind / Protect) e Seismitoad vira Pelipper (Hurricane / Tailwind / Roost / Protect). Ambos os antigos tinham Storm Drain inato; os novos não desviam Waterfall/Liquidation dos parceiros. Pelipper + Kyogre abrem: chuva, Tailwind e pressão de área sustentam Mega Gyarados, Drednaw e Barraskewda. Suicune ocupa a única vaga semi-lendária.

**Após revisão:** funciona no papel em Singles e Doubles, com as ressalvas de execução indicadas acima.


## 42. Olivia — `OLIVIA`

**Original — Singles: Sim. Doubles: Sim.**

- **Singles:** Psychic Terrain favorece Necrozma/Tapu Lele, Mega Aerodactyl oferece velocidade, Carbink telas e os rochosos cobertura física/especial. Necrozma pode usar Calm Mind atrás das telas.
- **Doubles:** Tailwind, telas e Protect da Mega apoiam os atacantes; Rock Slide atinge apenas adversários. Probopass tem Earth Eater inato para oferecer uma troca defensiva contra Terra. A equipe não seleciona prioridade própria que seja bloqueada pelo terreno de Lele.

**Vagas após revisão:** lendário Necrozma; semi-lendário Tapu Lele; Mega Aerodactyl.

**Decisão:** manter o bloco original; plano funcional nos dois formatos.


## 43. Peonia — `PEONIA`

**Original — Singles: Não aprovado pela evidência disponível. Doubles: Não aprovado pela evidência disponível.**

- **Singles:** Lugia e Suicune sustentam a equipe, Mega Aerodactyl/Tyrantrum oferecem dano físico e Toxtricity pressão especial. O plano de Tailwind + pivot funciona, mas Hydro Pump de Rotom-Wash não consta no índice de aprendizados fornecido.
- **Doubles:** Tailwind, Snarl, recuperação e ataques seguros permitem um plano de suporte/ofensiva; o impedimento de aprovação é o golpe não comprovado. Rotom pode receber Hydro Pump por troca de forma no motor completo, mas a tabela de formas não está nesta cópia. Usei Will-O-Wisp para garantir legalidade verificável.

**Vagas após revisão:** lendário Lugia; semi-lendário Suicune; Mega Aerodactyl.

**Alteração exportada:** Hydro Pump de Rotom-Wash vira Will-O-Wisp: Hydro Pump não consta no all_learnables.json nem no learnset por nível apontado pela forma. O repositório completo pode concedê-lo por mudança de forma, mas essa tabela não foi fornecida; o novo set é verificável nesta cópia e preserva o pivot elétrico, com Água já coberta por Suicune.

**Após revisão:** funciona no papel em Singles e Doubles, com as ressalvas de execução indicadas acima.


## 44. Peony — `PEONY`

**Original — Singles: Sim. Doubles: Sim, com ressalvas.**

- **Singles:** Perrserker reforça Aço, Dialga/Bronzong fornecem Trick Room e Registeel/Mega Aggron/Copperajah exploram a baixa velocidade relativa. O núcleo mantém resistências e dano físico/especial.
- **Doubles:** Fake Out + Trick Room já está disponível na abertura e Steely Spirit beneficia os parceiros. Porém há duas Stealth Rock, Thunder Wave reduz velocidade que o time quer superar por baixo e Gyro Ball perde força com Speed maximizado. Dei proteção e Iron Defense ao núcleo sem tirar Trick Room.

**Vagas após revisão:** lendário Dialga; semi-lendário Registeel; Mega Aggron.

**Alteração exportada:** Registeel troca Stealth Rock/Thunder Wave por Protect/Iron Defense, aproveitando Simple inato com Body Press; Aggron troca a segunda Stealth Rock por Protect; Bronzong usa Iron Head no lugar de Gyro Ball, menos confiável com Speed maximizado. Perrserker + Dialga mantêm Fake Out + Trick Room, Steely Spirit e o núcleo lento de Aço.

**Após revisão:** funciona no papel em Singles e Doubles, com as ressalvas de execução indicadas acima.


## 45. Rowan — `ROWAN`

**Original — Singles: Sim, com ressalvas. Doubles: Não aprovado.**

- **Singles:** Infernape inicia pressão, Dialga fornece dano especial, Uxie telas/pivot e Mega Gallade a rota física. Trick Room pode servir como recurso pontual para Torterra/Empoleon, mas não sustenta os rápidos.
- **Doubles:** Trick Room no segundo slot prejudica Infernape e depois Mega Gallade, enquanto Uxie usa os quatro slots em suporte e fica sem ataque até como último Pokémon. Troquei a inversão por Thunder Wave e tornei Uxie capaz de pressionar, preservando o plano de telas + pivot.

**Vagas após revisão:** lendário Dialga; semi-lendário Uxie; Mega Gallade.

**Alteração exportada:** Dialga troca Trick Room por Thunder Wave; Uxie troca Stealth Rock por Psychic, mantendo as duas telas e U-turn. Infernape + Dialga continuam abrindo, agora com Fake Out + controle de velocidade que também favorece Infernape e Mega Gallade; Uxie deixa de ser completamente passivo quando é o último Pokémon.

**Após revisão:** funciona no papel em Singles e Doubles, com as ressalvas de execução indicadas acima.


## 46. Rosa — `ROSA`

**Original — Singles: Sim. Doubles: Sim.**

- **Singles:** Reshiram cobre Aço para Serperior/Virizion, Mega Lucario limpa com prioridade e Braviary acelera. Serperior usa Contrary/Glare e Chandelure fornece pivot por Trick.
- **Doubles:** Heat Wave e Rock Slide dão área segura, Braviary oferece Tailwind/Defiant e Serperior paralisa. A pressão da dupla inicial não precisa de um turno obrigatório de setup. Não há Psychic Terrain próprio bloqueando Extreme Speed de Lucario.

**Vagas após revisão:** lendário Reshiram; semi-lendário Virizion; Mega Lucario.

**Decisão:** manter o bloco original; plano funcional nos dois formatos.


## 47. Serena — `SERENA`

**Original — Singles: Sim. Doubles: Sim.**

- **Singles:** Meowstic abre telas/paralisia para Geomancy de Xerneas, Mega Diancie e Sylveon reforçam Fada e Delphox/Pangoro cobrem Aço e Fantasma/Trevas.
- **Doubles:** A abertura Meowstic + Xerneas já executa proteção e setup; Meowstic tem Friend Guard inato. Sylveon usa Hyper Voice com Protect e Diancie pressiona em área com Diamond Storm. Diancie ocupa simultaneamente semi-lendário e Mega, sem uma segunda Mega escondida no elenco.

**Vagas após revisão:** lendário Xerneas; semi-lendário Diancie; Mega Diancie.

**Decisão:** manter o bloco original; plano funcional nos dois formatos.


## 48. Shelly — `SHELLY`

**Original — Singles: Sim. Doubles: Sim.**

- **Singles:** Kyogre fornece chuva para Hydration + Rest de Manaphy e Swift Swim de Ludicolo; Sharpedo explora Speed Boost antes da Mega e Mightyena/Crobat interrompem o adversário.
- **Doubles:** Ludicolo fornece Fake Out, Crobat Tailwind/Taunt e Sharpedo Intimidate inato/Protect. Manaphy tem Water Absorb inato, mas não Storm Drain: não desvia Hydro Pump dos aliados. A cura por Hydration depende de a chuva ainda estar ativa; cinco turnos de Drizzle não significam clima permanente.

**Vagas após revisão:** lendário Kyogre; semi-lendário Manaphy; Mega Sharpedo.

**Decisão:** manter o bloco original; plano funcional nos dois formatos.


## 49. Skyla — `SKYLA`

**Original — Singles: Sim. Doubles: Sim.**

- **Singles:** Tornadus e Mega Pidgeot pressionam/controlam velocidade, Lugia oferece uma condição resistente, Skarmory desgaste e Swoobat setup com Simple. O tema Voador está ligado por Tailwind e recuperação.
- **Doubles:** Tornadus + Lugia já reúne Tailwind prioritário e um atacante resistente. Pidgeot oferece Hurricane sem depender da chuva, Skarmory protege fisicamente e Swoobat tem Protect/Telepathy inato. Existem Tailwinds redundantes, mas não é necessário usar todos: é suporte disponível após perdas/trocas.

**Vagas após revisão:** lendário Lugia; semi-lendário Tornadus; Mega Pidgeot.

**Decisão:** manter o bloco original; plano funcional nos dois formatos.


## 50. Tulip — `TULIP`

**Original — Singles: Sim, com ressalvas. Doubles: Não aprovado.**

- **Singles:** Lunala, Mega Gardevoir e Espathra oferecem pressão/setup especial, Cresselia recupera/paralisa e Medicham cobre o físico. Porém Trick Room não conversa bem com Speed Boost e com as natures rápidas.
- **Doubles:** Farigiraf tem Psychic Surge inato: Bullet Punch de Medicham falha contra adversários aterrados sob o próprio terreno. Trick Room também inverte o ganho de Speed Boost de Espathra. Removi essas duas dependências conflitantes, mantendo Armor Tail, terreno e suporte ao núcleo Psíquico.

**Vagas após revisão:** lendário Lunala; semi-lendário Cresselia; Mega Gardevoir.

**Alteração exportada:** Farigiraf troca Trick Room por Thunder Wave, acompanhando Speed Boost de Espathra e os atacantes rápidos. Medicham troca High Jump Kick/Bullet Punch por Close Combat/Rock Slide: evita o custo de errar contra Protect e deixa de depender de prioridade bloqueada pelo Psychic Surge inato do próprio Farigiraf. Lunala e Mega Gardevoir recebem o suporte de Armor Tail/Helping Hand.

**Após revisão:** funciona no papel em Singles e Doubles, com as ressalvas de execução indicadas acima.


## 51. Valerie — `VALERIE`

**Original — Singles: Sim, com ressalvas. Doubles: Sim, com ressalvas.**

- **Singles:** Mr. Mime abre telas para Xerneas/Mega Diancie/Sylveon; Mawile fornece Intimidate e cobertura física. Aromatisse pode curar parceiros, mas Heal Pulse não resolve seu próprio sustento em Singles e o modo lento é secundário.
- **Doubles:** Telas, Friend Guard inato de Aromatisse, Intimidate e Hyper Voice oferecem um plano real. Trick Room pode beneficiar Aromatisse/Sylveon/Mawile, mas atrapalha Xerneas após Geomancy e Mega Diancie. Converti Aromatisse em suporte de cura que não exige inverter a velocidade do núcleo.

**Vagas após revisão:** lendário Xerneas; semi-lendário Diancie; Mega Diancie.

**Alteração exportada:** Aromatisse troca Psychic/Trick Room por Protect/Wish e Mental Herb por Leftovers. Wish/Protect funciona em Singles; Heal Pulse/Friend Guard continua oferecendo suporte em Doubles, sem inverter a velocidade de Xerneas e Mega Diancie. Mr. Mime permanece abrindo telas para o núcleo de Fada.

**Após revisão:** funciona no papel em Singles e Doubles, com as ressalvas de execução indicadas acima.


## 52. Viola — `VIOLA`

**Original — Singles: Sim. Doubles: Sim.**

- **Singles:** Masquerain fornece Sticky Web e Intimidate, Genesect/Mega Beedrill fazem pivot, Vivillon cria janelas de sono e Buzzwole/Frosmoth se fortalecem. Há pressão física e especial.
- **Doubles:** Tailwind de Masquerain substitui o valor perdido por Sticky Web, Frosmoth oferece Wide Guard e Vivillon sono/Protect. A abertura Masquerain + Genesect já combina controle e ataque/pivot; Beedrill entra em alvos enfraquecidos sem precisar usar Fell Stinger como único caminho de vitória.

**Vagas após revisão:** lendário Genesect; semi-lendário Buzzwole; Mega Beedrill.

**Decisão:** manter o bloco original; plano funcional nos dois formatos.


## 53. Zinnia — `ZINNIA`

**Original — Singles: Sim. Doubles: Sim.**

- **Singles:** Rayquaza com Dragon Ascent é a Mega e o lendário; Jirachi é o semi e fornece Wish. Salamence está sem pedra, portanto é comum neste elenco, oferecendo Intimidate; Exploud é o atacante especial que não repete o tipo Dragão.
- **Doubles:** Jirachi tem Friend Guard inato e Helping Hand ao lado de Rayquaza, Salamence intimida e Noivern fornece Tailwind. Hyper Voice de Exploud evita o dano aliado de Boomburst. Rayquaza possui Screen Cleaner inato, mas não há telas próprias para apagar. Dragon Ascent é essencial para a Mega de Rayquaza; não o removi.

**Vagas após revisão:** lendário Rayquaza; semi-lendário Jirachi; Mega Rayquaza.

**Decisão:** manter o bloco original; plano funcional nos dois formatos.

