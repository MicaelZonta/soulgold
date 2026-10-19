#ifndef GUARD_POKEGEAR_RADIO_H
#define GUARD_POKEGEAR_RADIO_H

#include "main.h"

void OpenPokegearRadio(MainCallback callback);
void CheckRadioStation(void);
bool8 IsHoennSoundPlaying(void);

#endif // GUARD_POKEGEAR_RADIO_H
