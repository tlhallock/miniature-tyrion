#ifndef CIVILIZATION_H
#define CIVILIZATION_H

#include <iostream>

class CivilizationDescription;
class Player;
class Building;

class Civilization
{
private:
    CivilizationDescription* type;
    Player *parent;

public:
    Civilization(CivilizationDescription* desc);
    ~Civilization();

    Building* create_building(const std::string& type);
};

#endif // CIVILIZATION_H
