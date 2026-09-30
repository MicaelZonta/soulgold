#ifndef GUARD_DIFFICULTY_CONSTANTS_H
#define GUARD_DIFFICULTY_CONSTANTS_H

enum DifficultyLevel
{
    // The former Hard teams were promoted into this sole dataset.
    DIFFICULTY_NORMAL,
    DIFFICULTY_COUNT,
};

// Source compatibility for archived scripts and tests. These names no longer
// select separate data or player-facing modes.
#define DIFFICULTY_EASY DIFFICULTY_NORMAL
#define DIFFICULTY_HARD DIFFICULTY_NORMAL
#define DIFFICULTY_MIN 0
#define DIFFICULTY_MAX (DIFFICULTY_COUNT - 1)

#endif // GUARD_DIFFICULTY_CONSTANTS_H
