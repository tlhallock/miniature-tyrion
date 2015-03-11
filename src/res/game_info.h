

#ifndef GAME_INFO_H_
#define GAME_INFO_H_

#include "res/identifier_table.h"
#include "res/images.h"
#include "res/resource_descp.h"
#include "res/civilization_descp.h"
#include "res/unit_structure.h"

class Game;
class UnitDescription;

class GameInfo
{

private:
	IdentifierTable table;
    Images images;
    std::vector<ResourceDescription> resources;
    UnitStructure structure;
    std::vector<UnitDescription*> units;
    UnitDescription* root;
    std::vector<Technology> techs;
    std::vector<CivilizationDescription> civs;
    int nplayers;
    int *player_civs;
public:
	GameInfo(const std::string& root_directory);
	~GameInfo();

    Game* create_game(const std::vector<std::string>& civ_names);
    int get_number_of_resources() const;
    Images* get_images();
};


#endif
