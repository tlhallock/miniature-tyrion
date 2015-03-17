#include "generator.h"

#include "model/game.h"
#include "model/civilization.h"
#include "model/unit.h"
#include "model/player.h"
#include "res/property_file.h"
#include "res/game_info.h"

#include <cmath>

#define SLOW 1

namespace aoe
{

# define PI           3.14159265358979323846


Area find_place(const Map& map, const Location& close_to, const Size& size)
{
    double cx = close_to.x;
    double cy = close_to.y;

    double radius = 0;
    double inc = sqrt(size.width * size.width + size.height * size.height);

    double radius_x = 0;
    double radius_y = 0;

#if SLOW
    for (;;)
    {
        int angles_to_try = 100;
        for (int i=0; i<angles_to_try; i++)
        {
            double angle = 2 * PI * i / angles_to_try;
            Area destination{cx + radius * cos(angle), cy + radius * sin(angle), size.width, size.height};

            if (!map.isObstructed(destination))
            {
                return destination;
            }
        }

        radius += inc;
    }
#else
    for (;;)
    {
        double angle = rand() * 2 * PI;
        for (;;)
        {
            Area destination{cx + radius_x * cos(angle), cy + radius_y * sin(angle), size.width, size.height};
            if (!map.isInBounds(destination))
            {
                break;
            }

            if (!map.isObstructed(destination))
            {
                return destination;
            }
        }

        radius += inc;
    }
#endif
}


void generate_map(GameInfo* info, Game* game)
{
    std::cout << "Generating the map...";

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

                Area location = find_place(game->get_map(), player->get_location(), unit->getArea());
                if (location.x < 0)
                {
                    std::cout << "Unable to place." << std::endl;
                    exit(-1);
                }

                unit->getArea() = Location{location};

                game->get_map().place_unit(unit);

                player->unit_added(unit);
            }
        }
    }
    std::cout << " ...done generating map." << std::endl;
}

}
