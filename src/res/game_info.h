

#ifndef GAME_INFO_H_
#define GAME_INFO_H_

#include "res/identifier_table.h"
#include "res/images.h"
#include "res/resource_descp.h"
#include "res/civilization_descp.h"
#include "res/unit_descp.h"
#include "res/unit_structure.h"

namespace aoe
{

class Civilization;

class GameInfo
{

private:
	IdentifierTable table;
    Images images;
    std::vector<ResourceDescription> resources;
    UnitStructure structure;
    std::vector<UnitDescription> units;
    std::vector<Technology> techs;
    std::vector<CivilizationDescription> civs;
public:
	GameInfo(const std::string& root_directory);
	~GameInfo();

    int get_number_of_resources() const;
    Images* get_images();

    Civilization* create_civilization(int index) const;
    std::vector<double> clone_resources() const;


    IdentifierTable& get_table() { return table; }
    const std::vector<UnitDescription>& get_units() const { return units; }
};

}


#endif
