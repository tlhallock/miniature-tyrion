
#include "res/game_info.h"

#include "res/property_file.h"
#include "util/fs.h"
#include "res/unit_descp.h"
#include "res/civilization_descp.h"
#include "res/technology.h"
#include "model/game.h"
#include "model/player.h"

#include <functional>
#include <list>

namespace aoe
{

namespace game_info
{
    std::vector<ResourceDescription> collect_resources(IdentifierTable& table, OpenedPropertyFiles&& pfiles);
    UnitDescription* find_root(UnitDescription* returnValue);
    std::vector<UnitDescription*> construct_unit_descriptions(IdentifierTable& table, OpenedPropertyFiles&& pfiles, UnitStructure& structure);
    std::vector<Technology> collect_technologies(OpenedPropertyFiles&& pfiles,
                                                           IdentifierTable& table,
                                                           const std::vector<UnitDescription*>& units);
    std::vector<CivilizationDescription> collect_civilizations(OpenedPropertyFiles&& pfiles,
                                                           IdentifierTable& table,
                                                           const std::vector<UnitDescription*>& units,
                                                           const std::vector<Technology>& techs);
}


GameInfo::GameInfo(const std::string& root_directory) :
    table{},
    images{root_directory + "/data/images/"},
    resources{game_info::collect_resources(table, OpenedPropertyFiles{root_directory + "/data/resources/"})},
    structure{},
    units{game_info::construct_unit_descriptions(table, OpenedPropertyFiles{root_directory + "/data/units/"}, structure)},
    root {game_info::find_root(units[0])},
    techs {game_info::collect_technologies(OpenedPropertyFiles{root_directory + "data/tech/"}, table, units)},
    civs{game_info::collect_civilizations(OpenedPropertyFiles{root_directory + "/data/civilizations/"}, table, units, techs)},
    nplayers{2},
    player_civs{new int[nplayers]}
{
    for (int i=0;i<nplayers;i++)
    {
        player_civs[i] = rand() % nplayers;
    }
}


GameInfo::~GameInfo()
{
    delete root;
    delete[] player_civs;
}


Game* GameInfo::create_game(const std::vector<std::string>& civ_names)
{
    Game *game = new Game;

    for (int i=0;i<nplayers;i++)
    {
        game->add_player(nullptr, new Player{this, i});
    }

    return game;
}


int GameInfo::get_number_of_resources() const
{
    return resources.size();
}

Images* GameInfo::get_images()
{
    return &images;
}


/*
 *

void read_unit(UnitDescription** descs, std::vector<PropertyFile> pfiles, bool* already_read, int i)
{
    UnitDescription* parent;
    int pid;
    if ((parent = descs[i]->get_parent()) != nullptr && !already_read[pid = parent->get_id()])
    {
        read_unit(descs, pfiles, already_read, pid);
    }
    descs[i]->read(pfiles.at(i));
    already_read[i] = true;
}
*/


}
