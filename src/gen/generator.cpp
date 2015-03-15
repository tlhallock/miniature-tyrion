#include "generator.h"

#include "model/game.h"
#include "model/civilization.h"
#include "model/unit.h"
#include "model/player.h"
#include "res/property_file.h"
#include "res/game_info.h"

#include <cmath>

namespace aoe
{

# define PI           3.14159265358979323846


Area find_place(const Map& map, const Location& close_to, const Size& size)
{
    double cx = close_to.x;
    double cy = close_to.y;

    double radius_x = size.x;
    double radius_y = size.y;
    for (;;)
    {
        int angles_to_try = 100;
        for (int i=0; i<angles_to_try; i++)
        {
            double angle = 2 * PI * i / angles_to_try;
            Area destination{cx + radius_x * cos(angle), cy + radius_y * sin(angle), size.x, size.y};

            if (!map.is_obstructed(destination))
            {
                return destination;
            }
        }

        radius_x += size.x;
        radius_y += size.y;
    }
}


void generate_map(GameInfo* info, Game* game)
{
    std::cout << "Generating the map..." << std::endl;

    for (int pNum = 0; pNum < game->get_num_players(); pNum++)
    {
        Player *player = game->get_player(pNum);

        OpenedPropertyFiles opened{"data/"};
        const PropertyFile& pFile = opened.get_property_file("initial.json");


        Json::Value units = pFile.get_property("units");
        for (int i=0;i<units.size();i++)
        {
            const std::string& type = units[i]["type"].asString();
            int number = units[i]["num"].asInt();

            for (int i = 0; i<number; i++)
            {
                int unit_it = game->get_table().get_unit_id(type);
                const UnitDescription& description = info->get_units()[unit_it];

                Unit* unit = description.create();
                if (unit == nullptr)
                {
                    std::cerr << "Unable to create " << type << std::endl;
                    exit(-1);
                }

                Area location = find_place(game->get_map(), player->get_location(), unit->get_size());
                if (location.x < 0)
                {
                    std::cout << "Unable to place." << std::endl;
                    exit(-1);
                }

                unit->set_location(Location{location});

                game->get_map().place_unit(unit);

                player->unit_added(unit);
            }
        }
    }
}

}
