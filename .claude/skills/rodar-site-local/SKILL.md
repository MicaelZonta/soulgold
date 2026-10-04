---
name: rodar-site-local
description: Use quando o usuario pedir para rodar, abrir, subir, executar ou ver o site/docs/Pokedex do SoulGold em localhost, ou para regenerar o site antes de ver. Regenera docs/ com build_docs.py (opcional), sobe um servidor HTTP estatico em background na porta 8000 e entrega o link. Cobre por que file:// nao funciona e como parar o servidor.
---

# Rodar o site (docs/) em localhost

O site é estático, em `docs/` (`index.html`, `pokedex/`, `moves/`, `trainers/`…).
Ele carrega os JSON de `docs/data/` por `fetch`, então **não abre por `file://`**:
precisa de servidor HTTP.

## Passos

1. **Regenerar (só se o jogo mudou desde a última vez, ou se o usuário pediu):**

   ```bash
   ~/.venvs/soulgold-docs/bin/python tools/soulgold_docs/build_docs.py
   ```

   Ele não imprime nada quando dá certo. Os `docs/data/*.json` ficam modificados
   no working tree: **não commite sem o usuário pedir**.

2. **Ver se já tem servidor na porta:**

   ```bash
   ss -ltn 'sport = :8000' | tail -n +2
   ```

   Se a porta estiver ocupada por um servidor anterior nosso, reaproveite (diga
   ao usuário que já está no ar). Se for outra coisa, use 8001, 8002…

3. **Subir em background** (`run_in_background: true` no Bash):

   ```bash
   cd /home/ADMIN/decomps/soulgold_v1/docs && python3 -m http.server 8000
   ```

4. **Conferir que respondeu:**

   ```bash
   curl -s -o /dev/null -w '%{http_code}\n' http://localhost:8000/
   ```

   Deve dar `200`.

5. **Entregar o link** `http://localhost:8000` (WSL2 encaminha a porta para o
   navegador do Windows; se não abrir, `hostname -I` dá o IP do WSL). Sugira a
   página que interessa, por exemplo `http://localhost:8000/pokedex/`.

## Parar

Encerrar a tarefa em background (TaskStop) ou `Ctrl+C` no terminal onde rodou.
Só pare quando o usuário pedir ou ao terminar de usar.

## Conferir uma fonte na Pokédex

Os dados vêm de `docs/data/species-details/<slug>.json` (campo `locations`).
Para provar que um método aparece, leia o JSON em vez de depender só do visual.
Ex.: infestações da horta = método `Berry Master's garden (pest on a Berry plot)`
(parser em `tools/soulgold_docs/parsers/berry_garden.py`).
