
#include "res/civilization_descp.h"

#include "model/civilization.h"

CivilizationDescription::CivilizationDescription(int nunits, int ntechs) :
    units{new bool[nunits]},
    technologies{new bool[ntechs]} {}

CivilizationDescription::~CivilizationDescription()
{
    delete[] units;
    delete[] technologies;
}

Civilization* CivilizationDescription::create()
{
    return nullptr;
}
