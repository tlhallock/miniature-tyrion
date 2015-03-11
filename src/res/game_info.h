

#ifndef GAME_INFO_H_
#define GAME_INFO_H_

#include "res/identifier_table.h"
#include "res/images.h"
#include "res/resource_descp.h"
#include "res/civilization_descp.h"

class Game;
class UnitDescription;

class GameInfo
{

private:
	IdentifierTable table;
    Images images;
    std::vector<ResourceDescription> resources;
    UnitDescription** units;
    UnitDescription* root;
    std::vector<CivilizationDescription> civs;
    int nplayers;
    int player_civs;
public:
	GameInfo(const std::string& root_directory);
	~GameInfo();

    Game* create_game(const std::vector<std::string>& civ_names);
};


#endif
