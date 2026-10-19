#include "global.h"
#include "regions.h"
#include "constants/region_map_sections.h"

bool8 IsMapSectionInKanto(u32 mapSecId)
{
    return mapSecId >= KANTO_MAPSEC_START && mapSecId <= KANTO_MAPSEC_END;
}

bool8 IsPlayerInKanto(void)
{
    return IsMapSectionInKanto(gMapHeader.regionMapSectionId);
}

bool8 IsPlayerInJohto(void)
{
    return !IsPlayerInKanto();
}
