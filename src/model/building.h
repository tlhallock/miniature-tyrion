#ifndef BUILDING_H
#define BUILDING_H

#include <iostream>
#include <vector>

class Player;
class BuildingDescription;
class Technology;
class UnitDescription;

class Building
{
private:
    BuildingDescription* description;
    Player *parent;

    std::vector<UnitDescription*> units;
    std::vector<Technology> techs;

public:
    Building();
    ~Building();

    void create_unit(const std::string& name);
    void research_technology(const std::string& name);

};

#endif // BUILDING_H
