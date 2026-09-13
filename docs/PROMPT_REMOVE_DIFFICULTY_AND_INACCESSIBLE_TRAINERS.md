# Terra executor prompt — single Hard-quality difficulty and inaccessible trainer cleanup

Work in the repository:

`https://github.com/MicaelZonta/soulgold`

Target branch:

`soulgold-rift-missions`

Use this action file as the operational source of truth:

`SOULGOLD_TRAINER_REMOVAL_ACTIONS.csv`

Also read:

- `SOULGOLD_RIFT_MISSIONS_DESIGN_V7.md`
- `SOULGOLD_HOENN_RIFT_RETENTION_PLAN.md`, if available
- `include/constants/opponents.h`
- `include/constants/flags.h`
- `include/global.h`
- `src/data/trainers.party`
- `src/difficulty.c`
- `include/difficulty.h`
- `include/constants/difficulty.h`
- `include/config/battle.h`

## Objective

Remove the selectable Normal/Hard difficulty system while preserving the current **Hard-quality trainer teams as the only default teams**. Remove trainer battles that exist only in statically unreachable legacy Hoenn maps, except the approved canonical Hoenn roster intended for the final Rift loop.

Do not interpret “remove Hard” as keeping the easier Normal teams. The desired final state has no difficulty choice and exactly one party per retained trainer, using the former Hard party wherever one exists.

## Non-negotiable protections

1. Preserve `TRAINER_STEVEN`, ID 804. Keep his former Hard party as his sole default party.
2. Preserve the 18 canonical Hoenn Rift battles marked `PROTECT_CANONICAL_RIFT_BATTLE` in the CSV.
3. Preserve `TRAINER_KUKUI`, ID 966. It is reserved by the Rift Missions design even if no current battle script calls it.
4. Do not automatically delete Frontier Brains marked `PROTECT_FRONTIER_BRAIN_REVIEW`.
5. Preserve Lusamine, Lillie, Gladion and every implemented Rift Missions battle.
6. Do not use trainer IDs `1056–1163`. Their trainer flags were reclaimed for standalone flags beginning at `TRAINER_UNUSED_192`.
7. Do not use ID 1164. It is outside the valid trainer range `0–1163`.
8. Preserve save compatibility. Do not physically remove or reorder serialized save-structure fields merely to delete the difficulty option. A former field may remain reserved/ignored if removing it would shift the save layout.

## Operating discipline

Work in small, verifiable phases. Before editing:

1. Confirm the active branch and commit.
2. Check `git status` and preserve unrelated user changes.
3. Build the current branch successfully.
4. Record baseline ROM, EWRAM and IWRAM sizes.
5. Parse the CSV and report the count of every action before applying it.
6. Create a checkpoint commit or clearly named backup branch before the first mutation.

Never execute the entire CSV as a blind text-replacement batch. Before deleting any symbol, search for every consumer in tracked runtime files.

## Phase 1 — make former Hard parties the only parties

Process every CSV row with `PROMOTE_HARD_TO_DEFAULT`.

For each trainer:

1. Locate both blocks with the same `=== TRAINER_* ===` label in `src/data/trainers.party`.
2. Confirm that one block has no difficulty marker and the other contains `Difficulty: Hard`.
3. Delete the former Normal block.
4. Keep the former Hard block.
5. Remove only its `Difficulty: Hard` line, turning that block into the default party.
6. Confirm that exactly one block remains for the trainer.

Do not change species, moves, items, levels, IVs, EVs, natures, AI or battle format during this phase.

After converting a small batch, regenerate trainer data and compile. Stop on the first duplicate-party, missing-party or trainer parser error instead of continuing through all 83 entries.

Expected result: 83 trainers that previously had Normal + Hard variants each have exactly one Hard-quality default party.

## Phase 2 — remove the difficulty selector safely

Apply the phase-3 system actions from the CSV only after Phase 1 builds successfully.

1. Temporarily force `GetCurrentDifficultyLevel()` and trainer/partner difficulty accessors to return the former Hard behavior.
2. Compile and test representative trainer, partner, PWT/Dome and Hall of Fame paths.
3. Remove the difficulty choice from the option menu.
4. Remove or neutralize `VAR_DIFFICULTY` and `FLAG_DIFFICULTY_HARD` only after proving that no runtime consumer needs them.
5. Simplify difficulty-indexed trainer slides, partner data and facility behavior to one dataset.
6. Remove the Hall of Fame Normal/Hard label.
7. Keep serialized save bytes reserved when deleting/reordering them would break existing saves.
8. Remove unused difficulty code, strings and tests only after all production consumers are migrated.

Do not collapse an array dimension until every accessor using that dimension has been updated and compiled.

## Phase 3 — remove inaccessible legacy trainer battles

Process CSV rows with `REMOVE_INACCESSIBLE_LEGACY_BATTLE`.

For every row:

1. Reconfirm that all direct map triggers belong only to legacy Hoenn maps and that no Johto, Kanto, custom-map, Rift, facility, Title Defense or active campaign consumer requires the battle.
2. Remove the trainer battle trigger from the authoritative source:
   - edit `.pory` when it exists and regenerate `.inc`;
   - edit tracked `.inc` only when it is the actual authoritative legacy source and no `.pory` exists.
3. Remove the associated trainer object event only when it has no remaining dialogue, item, movement or story purpose. Otherwise convert it into a non-trainer NPC safely.
4. Delete its `trainers.party` block when the CSV reason says a party exists and no protected consumer remains.
5. Remove rematch, Match Call, level-scaling, PWT/Dome or other table entries only when that trainer is not protected and the system entry would otherwise become dangling.
6. Delete or rename the `TRAINER_*` constant only after a repository-wide search reports no remaining runtime reference.

Rows marked `MIGRATE_CANONICAL_FROM_LEGACY_MAP` are different: remove the obsolete legacy-map trigger, but preserve the ID for its future canonical Rift battle.

## Phase 4 — remove orphaned parties

Process `REMOVE_ORPHANED_PARTY` rows one at a time.

Before deleting each party, search generated inputs, scripts, C code, rematches, facilities, Title Defense, PWT/Dome and data tables. Remove the party only when no indirect selector exists.

Never remove rows marked `PROTECT_RIFT_RESERVED`, `PROTECT_CANONICAL_RIFT_BATTLE`, `PROTECT_EXISTING_CHARACTER` or `PROTECT_FRONTIER_BRAIN_REVIEW`.

## Phase 5 — canonical Hoenn Rift roster

Preserve exactly one future battle for each of these 18 characters:

- Roxanne, Brawly, Wattson, Flannery, Norman, Winona, Tate & Liza, Juan;
- Sidney, Phoebe, Glacia, Drake;
- Wallace;
- Archie and Maxie;
- May, Brendan and Wally.

May and Brendan must each use one fixed endgame Rift team. Do not preserve separate starter-dependent battle IDs. Wally keeps one final battle. Tate & Liza remain one double-battle opponent.

This cleanup does not require designing the final 18 teams now. If a canonical ID currently lacks party data, preserve or reserve the ID and report `REBUILD_PARTY_PENDING`; do not invent an unapproved team during cleanup.

## Required validation

After every phase:

1. Regenerate generated trainer data using the repository's normal build rules.
2. Run a full clean build.
3. Search for dangling `TRAINER_*` symbols.
4. Confirm every retained trainer has exactly one default party.
5. Confirm no retained party still contains `Difficulty: Hard`.
6. Confirm there is no player-facing difficulty selector.
7. Confirm Steven ID 804 and his former Hard-quality party remain.
8. Confirm Kukui ID 966 remains.
9. Confirm Gladion's Violet battle and Egg delivery still work.
10. Confirm IDs 1056–1163 remain unavailable as trainer IDs.
11. Record ROM, EWRAM and IWRAM sizes and compare against the baseline.

Test at minimum:

- a normal route trainer;
- one Gym Leader that previously had two difficulties;
- Steven;
- Gladion in Violet, including defeat/retry and Egg-to-PC behavior;
- a partner or double battle;
- one PWT/Dome or Frontier path still retained;
- loading an existing save created before this cleanup.

## Deliverables

Return:

1. concise implementation summary;
2. list of modified files grouped by phase;
3. exact counts of party blocks, triggers, constants and system entries removed;
4. protected trainers confirmed intact;
5. build and test results;
6. ROM/EWRAM/IWRAM before-and-after measurements;
7. remaining `REBUILD_PARTY_PENDING` canonical Hoenn trainers;
8. any rows skipped because accessibility or indirect use could not be proven;
9. final commit hash.

Do not claim an inaccessible battle, party, constant or difficulty system was removed without verifying the final repository state.
