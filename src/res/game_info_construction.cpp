
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
std::vector<UnitDescription*> construct_unit_descriptions(IdentifierTable& table, OpenedPropertyFiles&& pfiles, UnitStructure& structure)
{
    std::vector<std::string> property_file_names;
    collect_files_by_ext(pfiles.get_base(), property_file_names, ".json");

    if (property_file_names.size() == 0)
    {
        std::cerr << "No units found!" << std::endl;
        exit(-1);
    }

    int nunits = property_file_names.size();
    int nres = table.get_resources().size();

    structure.set_size(nunits);

    std::vector<UnitDescription*> descriptions;

    /**
     * Perform initial read...
     */
    int index = 0;
    for (auto it = property_file_names.begin(); it != property_file_names.end(); ++it, index++)
    {
        descriptions.push_back(new UnitDescription{table, pfiles.get_property_file(*it), index, nunits, nres});
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
        structure.set_parent(index, s);

        if (index != descriptions[index]->get_id())
        {
            std::cerr << "This test fails" << std::endl;
            exit(-1);
        }
    }

    structure.compile();

    /**
     * Link against other units.
     */
    bfs(find_root(descriptions[0]),
            [&descriptions, &pfiles, &property_file_names, nunits](UnitDescription* description)
        {
            description->link_properties(descriptions, pfiles.get_property_file(property_file_names.at(description->get_id())));
        });

    return descriptions;
}

/*******************************
 * Technology creation
 *******************************/

std::vector<Technology> collect_technologies(OpenedPropertyFiles&& pfiles,
                                                           IdentifierTable& table,
                                                           const std::vector<UnitDescription*>& units)
{
    std::vector<std::string> property_file_names;
    collect_files_by_ext(pfiles.get_base(), property_file_names, ".json");

    std::vector<Technology> returnValue;
    for (auto it = property_file_names.begin(); it != property_file_names.end(); ++it)
    {
        const PropertyFile& pfile = pfiles.get_property_file(*it);
        if (pfile.should_ignore())
        {
            continue;
        }

        Technology tech{pfile, (int) returnValue.size()};
        table.get_technology_id(tech.get_name());
        returnValue.push_back(tech);

        std::cout << "Found technology: " << tech.get_name() << '\n';
    }
    return returnValue;
}


/*******************************
 * Civilization creation
 *******************************/

std::vector<CivilizationDescription> collect_civilizations(OpenedPropertyFiles&& pfiles,
                                                           IdentifierTable& table,
                                                           const std::vector<UnitDescription*>& units,
                                                           const std::vector<Technology>& techs)
{
    std::vector<std::string> property_file_names;
    collect_files_by_ext(pfiles.get_base(), property_file_names, ".json");

    std::vector<CivilizationDescription> returnValue;
    for (auto it = property_file_names.begin(); it != property_file_names.end(); ++it)
    {
        const PropertyFile& pfile = pfiles.get_property_file(*it);
        if (pfile.should_ignore())
        {
            continue;
        }

        CivilizationDescription civ{pfile, units, techs};
        civ.set_id(table.get_civilization_id(civ.get_name()));
        returnValue.push_back(civ);

        std::cout << "Found civilization: " << civ.get_name() << '\n';
    }
    return returnValue;
}

}
}

