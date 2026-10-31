S = 'VAR_ABUNDANCE_ISLE_STATE'
# condicoes: rotulo -> corpo asm que pula para _Show quando deve mostrar (cai em _Hide se nao)
def cond_asm(c, show):
    if c.startswith('lt'): return f'\tgoto_if_lt {S}, {c[2:]}, {show}\n'
    if c.startswith('ge'): return f'\tgoto_if_ge {S}, {c[2:]}, {show}\n'
    if c.startswith('eq'): return f'\tgoto_if_eq {S}, {c[2:]}, {show}\n'
    if c == 'tornadus':  return f'\tgoto_if_set FLAG_ABUNDANCE_TORNADUS_DONE, {show}_No\n\tgoto_if_ge {S}, 4, {show}\n'
    if c == 'thundurus': return f'\tgoto_if_set FLAG_ABUNDANCE_THUNDURUS_DONE, {show}_No\n\tgoto_if_ge {S}, 4, {show}\n'
    if c == 'landorus':
        return (f'\tgoto_if_set FLAG_ABUNDANCE_LANDORUS_DONE, {show}_No\n\tgoto_if_unset FLAG_ABUNDANCE_TORNADUS_DONE, {show}_No\n'
                f'\tgoto_if_unset FLAG_ABUNDANCE_THUNDURUS_DONE, {show}_No\n\tgoto_if_ge {S}, 7, {show}\n')
    if c == 'reshiram':  return f'\tgoto_if_set FLAG_ABUNDANCE_RESHIRAM_DONE, {show}_No\n\tgoto_if_eq {S}, 12, {show}\n'
    if c == 'enamorus':  return f'\tgoto_if_set FLAG_ABUNDANCE_ENAMORUS_DONE, {show}_No\n\tgoto_if_ge {S}, 8, {show}\n'
    if c == 'dock':      return f'\tgoto_if_ge {S}, 10, {show}_No\n\tgoto_if_ge {S}, 7, {show}\n'
    if c == 'n_lab':     return f'\tgoto_if_ge {S}, 6, {show}_No\n\tgoto_if_ge {S}, 4, {show}\n'
    if c == 'day':       return f'\tgettime\n\tgoto_if_lt VAR_0x8000, 18, {show}\n'
    if c == 'dusk':      return f'\tgettime\n\tgoto_if_ge VAR_0x8000, 18, {show}\n'
    if c[:6] == 'rocket' and c[6:].isdigit(): return f'\tgoto_if_eq VAR_ABUNDANCE_ROCKET_STAGE, {c[6:]}, {show}\n'
    if c == 'nouniform': return f'\tgoto_if_unset FLAG_ABUNDANCE_PLASMA_UNIFORM, {show}\n'
    sat = lambda go: f'\tspecialvar VAR_RESULT, GetDayOfWeek\n\t{go} VAR_RESULT, WEEKDAY_SAT, {show}\n'
    if c == 'sat':       return sat('goto_if_eq')
    if c == 'notsat':    return sat('goto_if_ne')
    if c == 'sat14':     return f'\tgoto_if_lt {S}, 14, {show}_No\n' + sat('goto_if_eq')
    if c == 'rocketsat': return f'\tgoto_if_lt VAR_ABUNDANCE_ROCKET_STAGE, 3, {show}_No\n' + sat('goto_if_eq')
    if c == 'notnight':  return f'\tgettime\n\tgoto_if_lt VAR_0x8000, 6, {show}_No\n\tgoto_if_lt VAR_0x8000, 20, {show}\n'
    if c.startswith('flag:'): return f'\tgoto_if_set {c[5:]}, {show}\n'
    raise KeyError(c)

