
#include "res/unit_descp.h"
#include "res/identifier_table.h"
#include "res/resource_descp.h"


#include "res/property_file.h"

UnitDescription::UnitDescription(
        IdentifierTable& table,
        const PropertyFile& propertyFile,
        int id_,
        int nunits,
        int nres) :
    name              { propertyFile.get_property("name").asString()     },
	id{id_},

    speed             { propertyFile.get_property("speed"   ).asDouble() },
    carrying_capacity { propertyFile.get_property("capacity").asDouble() },
    line_of_sight     { propertyFile.get_property("los"     ).asDouble() },
    range             { propertyFile.get_property("range"   ).asDouble() },
    width             { propertyFile.get_property("width"   ).asDouble() },
    height            { propertyFile.get_property("height"  ).asDouble() },
    image_id          { 0},//table.get_image_id(propertyFile.get_property("images")[0].asString()) },
    creatable         { propertyFile.get_property("creatable").asBool()  },

	damage{new double[nunits]},
	resistance{new double[nunits]},
    cost{new double[nres]},
    collection_speed{new double[nres]}
{
    for (auto it = table.get_resources().begin(); it != table.get_resources().end(); ++it)
    {
        cost[it->second] = propertyFile.get_property("cost",       it->first).asDouble();
        cost[it->second] = propertyFile.get_property("coll-speed", it->first).asDouble();
    }

    if (id != table.get_unit_id(name))
    {
        std::cerr << "This other test fails." << std::endl;
        exit(-1);
    }
}

UnitDescription::~UnitDescription()
{
    delete[] damage;
    delete[] resistance;
    delete[] cost;
    delete[] collection_speed;
}



void UnitDescription::link_building()
{
    if (!id_child_of("building"))
    {
        return;
    }


}

void UnitDescription::set_parent(UnitDescription* parent)
{
    if (parent != nullptr)
    {
        parent->children.insert(this);
    }
    this->parent = parent;
}

UnitDescription* UnitDescription::get_parent()
{
    return parent;
}

const std::set<UnitDescription*>& UnitDescription::get_children() const
{
    return children;
}

bool UnitDescription::is_child_of(const std::string& unitName)
{
    if (name == unitName)
    {
        return true;
    }
    if (parent == nullptr)
    {
        return false;
    }
    return parent->is_child_of(unitName);
}

void UnitDescription::link_properties(UnitDescription** descriptions, const PropertyFile& propertyFile, int nunits)
{
    for (int i=0; i<nunits; i++)
    {
        // By default it is inherited by the parent unit...
        damage[i] = parent->damage[i];
        resistance[i] = parent->resistance[i];
    }

    {
        const Json::Value& damages = propertyFile.get_property("damage");
        for (unsigned int i=0; i<damages.size(); i++)
        {
            const Json::Value& jsonChild = damages[i];

            const std::string& ounit = jsonChild["against"].asString();
            double damageV           = jsonChild["value"].asDouble();
            for (int j=0; j<nunits; j++)
            {
                UnitDescription* other = descriptions[j];
                if (other->is_child_of(ounit))
                {
                    damage[other->id] = damageV;
                }
            }
        }
    }

    {
        const Json::Value& resistances = propertyFile.get_property("resistance");
        for (unsigned int i=0; i<resistances.size(); i++)
        {
            const Json::Value& jsonChild = resistances[i];

            const std::string& ounit = jsonChild["torwards"].asString();
            double resistanceV       = jsonChild["value"].asDouble();
            for (int j=0; j<nunits; j++)
            {
                UnitDescription* other = descriptions[j];
                if (other->is_child_of(ounit))
                {
                    resistance[other->id] = resistanceV;
                }
            }
        }
    }
}


UnitDescription* clone()
{
    return nullptr;
}


UnitDescription *create()
{
    return nullptr;
}




/*



UnitDescription* UnitDescription::get_most_precise_parent(std::set<std::string> possible_defs)
{
    if (possible_defs.find(name) != possible_defs.end())
    {
        return this;
    }

    if (parent == nullptr)
    {
        return nullptr;
    }

    return parent->get_most_precise_parent(possible_defs);
}
void UnitDescription::push(UnitDescriptions* descriptions)
{
    for (auto it = children.begin(); it != children.end(); ++it)
    {
        UnitDescription* child = *it;

        for (int i=0;i<nunits;i++)
        {
            child->damage[i] = damage[i];
        }

        for (int j=0;j<nres;j++)
        {

        }
    }
}*/
