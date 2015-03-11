
#include "res/game_info.h"

#include "res/property_file.h"
#include "util/fs.h"
#include "res/unit_descp.h"
#include "res/civilization_descp.h"

#include <functional>
#include <list>

namespace
{
/*******************************
 * Utilities
 *******************************/
void bfs(UnitDescription* root, std::function<void(UnitDescription* desc)> f)
{
    std::list<UnitDescription*> horizon;
    horizon.push_back(root);

    while (horizon.size() > 0)
    {
        UnitDescription* next = horizon.front();
        horizon.pop_front();

        f(next);

        for (auto it = next->get_children().begin(); it != next->get_children().end(); ++it)
        {
            horizon.push_back(*it);
        }
    }
}


/*******************************
 * Resource creation
 *******************************/
std::vector<ResourceDescription> collect_resources(IdentifierTable& table, OpenedPropertyFiles&& pfiles)
{
    std::vector<std::string> property_files;
    collect_files_by_ext(pfiles.get_base(), property_files, ".json");

    std::vector<ResourceDescription> returnValue;

    int index = 0;
    for (auto it = property_files.begin(); it != property_files.end(); ++it)
    {
        PropertyFile pfile = pfiles.get_property_file(*it);
        if (pfile.get_property("ignore").asBool())
        {
            continue;
        }
        returnValue.push_back(ResourceDescription{index, table, pfile});

        std::cout << "Found resource: " << returnValue.at(index).get_name() << '\n';

        index++;
    }

    return returnValue;
}


/*******************************
 * Unit creation
 *******************************/


UnitDescription* find_root(UnitDescription* returnValue)
{
    while (returnValue->get_parent() != nullptr)
    {
        returnValue = returnValue->get_parent();
    }
    return returnValue;
}
UnitDescription** construct_unit_descriptions(IdentifierTable& table, OpenedPropertyFiles&& pfiles)
{
    std::vector<std::string> property_file_names;
    collect_files_by_ext(pfiles.get_base(), property_file_names, ".json");
    
    if (property_file_names.size() == 0)
    {
        std::cerr << "No units found!" << std::endl;
        exit(-1);
    }

    int nunits = table.get_units().size();
    int nres = table.get_resources().size();

    UnitDescription** descriptions = new UnitDescription*[nunits];

    /**
     * Perform initial read...
     */
    int index = 0;
    for (auto it = property_file_names.begin(); it != property_file_names.end(); ++it, index++)
    {
        descriptions[index] = new UnitDescription{table, pfiles.get_property_file(*it), index, nunits, nres};
        std::cout << "Found unit: " << descriptions[index]->get_name() << '\n';
    }

    /**
     * Link parents...
     */
	index = 0;
//	int num_roots = 0;
	// set parents
	for (auto it = property_file_names.begin(); it != property_file_names.end(); ++it, index++)
	{
		const PropertyFile* parentFile = pfiles.get_property_file(*it).get_parent();
		if (parentFile == nullptr)
		{
			continue;
		}

		int s = table.get_unit_id(parentFile->get_property("name").asString());
		descriptions[index]->set_parent(descriptions[s]);

		if (index != descriptions[index]->get_id())
		{
			std::cerr << "This test fails" << std::endl;
			exit(-1);
		}
	}

    /**
     * Link against other units.
     */
    bfs(find_root(descriptions[0]),
            [descriptions, &pfiles, &property_file_names, nunits](UnitDescription* description)
        {
            description->link_properties(descriptions, pfiles.get_property_file(property_file_names.at(description->get_id())), nunits);
        });

    return descriptions;
}

/*******************************
 * Civilization creation
 *******************************/

std::vector<CivilizationDescription> collect_civilizations(OpenedPropertyFiles&& pfiles)
{
    std::vector<std::string> property_file_names;
    collect_files_by_ext(pfiles.get_base(), property_file_names, ".json");


    return std::vector<CivilizationDescription>{};
}



}




GameInfo::GameInfo(const std::string& root_directory) :
    table{},
    images{root_directory + "/data/images/"},
    resources{collect_resources(table, OpenedPropertyFiles{root_directory + "/data/resources/"})},
    units{construct_unit_descriptions(table, OpenedPropertyFiles{root_directory + "/data/units/"})},
    root {find_root(units[0])},
    civs{collect_civilizations(OpenedPropertyFiles{root_directory + "/data/civilizations/"})}
{

}


GameInfo::~GameInfo()
{
    delete root;
    delete[] units;
}


Game* GameInfo::create_game(const std::vector<std::string>& civ_names)
{
    Game *game = new Game;

    for (auto it = civ_names.begin(); it != civ_names.end(); ++it)
    {
        game->add_player(nullptr, new Player{nullptr});
    }


    return game;
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

