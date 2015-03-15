
#include "res/resource_descp.h"

#include "res/property_file.h"
#include "res/identifier_table.h"
#include "res/images.h"

namespace aoe
{

ResourceDescription::ResourceDescription(int id_, IdentifierTable& table, PropertyFile& file, Images& images) :
    name          { file.get_property("name").asString()          },
    id            { id_                                           },
    num_villagers { file.get_property("num-collect").asInt()      },
    width         { file.get_property("width").asDouble()         },
    height        { file.get_property("height").asDouble()        },
    rejuv_speed   { file.get_property("rejuv").asDouble()         },
    initial_cap   { file.get_property("quantity-init").asDouble() },
    player_init   { file.get_property("player-init").asDouble()   },
    image_id      { images.get_id_for(file.get_property("image").asString()) }
{
    if (table.get_resource_id(name) != id_)
    {
        std::cerr << "This test failed." << std::endl;
        exit(-1);
    }
}

ResourceDescription::~ResourceDescription() {}


const std::string& ResourceDescription::get_name() const
{
    return name;
}


int ResourceDescription::get_image_id() const
{
    return image_id;
}

double ResourceDescription::get_initial_value() const { return initial_cap; }



}
