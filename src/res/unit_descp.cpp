
#include "res/unit_descp.h"

#include "res/identifier_table.h"
#include "res/resource_descp.h"
#include "res/property_file.h"
#include "res/unit_structure.h"
#include "model/unit.h"
#include "res/images.h"
#include "model/spc/size.h"


namespace aoe
{


UnitDescription::UnitDescription(
        IdentifierTable& table,
        const PropertyFile& propertyFile,
        int id_,
        int nunits,
        int nres,
        Images& images) :
    name              { propertyFile.get_property("name").asString()     },
	id{id_},

    speed             { propertyFile.get_property("speed"   ).asDouble() },
    carrying_capacity { propertyFile.get_property("capacity").asDouble() },
    line_of_sight     { propertyFile.get_property("los"     ).asDouble() },
    range             { propertyFile.get_property("range"   ).asDouble() },
    width             { propertyFile.get_property("width"   ).asDouble() },
    height            { propertyFile.get_property("height"  ).asDouble() },
    image_id          { images.get_id_for(propertyFile.get_property("images")[0].asString()) },
    creatable         { propertyFile.get_property("creatable").asBool()  }
{
    damage.resize(nunits);
    resistance.resize(nunits);
    cost.resize(nres);
    collection_speed.resize(nres);


    for (auto it = table.get_resources().begin(); it != table.get_resources().end(); ++it)
    {
        Json::Value value = propertyFile.get_property("costs", it->first);
        if (value == DEFAULT_JSON_VALUE)
        {
            std::cerr << "Unit " << name << " does not have field costs for " << it->first << std::endl;
            exit(-1);
        }
        cost[it->second] = value.asDouble();
        value = propertyFile.get_property("coll-speed", it->first);
        if (value == DEFAULT_JSON_VALUE)
        {
            std::cerr << "Unit " << name << " does not have coll-speed for " << it->first << std::endl;
            exit(-1);
        }
        collection_speed[it->second] = value.asDouble();
    }

    if (id != table.get_unit_id(name))
    {
        std::cerr << "This other test fails." << std::endl;
        exit(-1);
    }
}

UnitDescription::~UnitDescription() {}


void UnitDescription::link_units(IdentifierTable& table,
                                      std::vector<UnitDescription>& descriptions,
                                      const PropertyFile& propertyFile,
                                      const UnitStructure& tree)
{
    int nunits = descriptions.size();

    int parentIdx = tree.get_parent(id);
    if (parentIdx >= 0)
    {
        const UnitDescription& parent = descriptions[parentIdx];
        for (int i=0; i<nunits; i++)
        {
            // By default values are inherited by the parent unit...
            damage[i] = parent.damage[i];
            resistance[i] = parent.resistance[i];
            creates_units.insert(parent.creates_units.begin(), parent.creates_units.end());
            creates_techs.insert(parent.creates_techs.begin(), parent.creates_techs.end());
        }
    }

    {
        const Json::Value& damages = propertyFile.get_property("damage");
        for (unsigned int i=0; i<damages.size(); i++)
        {
            const Json::Value& jsonChild = damages[i];

            int ounit                = table.get_unit_id(jsonChild["against"].asString());
            double damageV           = jsonChild["value"].asDouble();

            for (auto it = tree.get_children(ounit).begin(); it != tree.get_children(ounit).end(); ++it)
            {
                damage[*it] = damageV;
            }
        }
    }

    {
        const Json::Value& resistances = propertyFile.get_property("resistance");
        for (unsigned int i=0; i<resistances.size(); i++)
        {
            const Json::Value& jsonChild = resistances[i];

            int ounit                = table.get_unit_id(jsonChild["torwards"].asString());
            double resistanceV       = jsonChild["value"].asDouble();

            for (auto it = tree.get_children(ounit).begin(); it != tree.get_children(ounit).end(); ++it)
            {
                resistance[*it] = resistanceV;
            }
        }
    }


    const Json::Value& creates = propertyFile.get_property("creates", false);
    if (creates != DEFAULT_JSON_VALUE)
    {
        const Json::Value& creates_units_child = creates["units"];
        for (int i=0;i<creates_units_child.size();i++)
        {
            const std::string& unit = creates_units_child[i]["name"].asString();
            bool possible           = creates_units_child[i]["value"].asBool();

            if (possible)
            {
                creates_units.insert(table.get_unit_id(unit));
            }
            else
            {
                creates_units.erase(table.get_unit_id(unit));
            }
        }
    }
}

void UnitDescription::link_techs(IdentifierTable& table,
                                      std::vector<UnitDescription>& descriptions,
                                      const PropertyFile& propertyFile,
                                      const UnitStructure& tree)
{
    int nunits = descriptions.size();

    int parentIdx = tree.get_parent(id);
    if (parentIdx >= 0)
    {
        const UnitDescription& parent = descriptions[parentIdx];
        for (int i=0; i<nunits; i++)
        {
            // By default values are inherited by the parent unit...
            creates_techs.insert(parent.creates_techs.begin(), parent.creates_techs.end());
        }
    }

    const Json::Value& creates = propertyFile.get_property("creates", false);
    if (creates != DEFAULT_JSON_VALUE)
    {
        const Json::Value& creates_techs_child = creates["techs"];
        for (int i=0;i<creates_techs_child.size();i++)
        {
            const std::string& tech = creates_techs_child[i]["name"].asString();
            bool possible           = creates_techs_child[i]["value"].asBool();

            if (possible)
            {
                creates_techs.insert(table.get_technology_id(tech));
            }
            else
            {
                creates_techs.erase(table.get_technology_id(tech));
            }
        }
    }
}


int UnitDescription::get_id() const
{
    return id;
}

Unit *UnitDescription::create() const
{
    Unit* returnValue = new Unit{this};
    returnValue->getArea() = getSize();
    return returnValue;
}

const std::string& UnitDescription::get_name() const
{
    return name;
}


int UnitDescription::get_image_id() const
{
    return image_id;
}



bool UnitDescription::isCreatable() const { return creatable; }
Size UnitDescription::getSize() const { return Size{width, height}; }
//double UnitDescription::get_width() const { return width; }
//double UnitDescription::get_height() const { return height; }
double UnitDescription::get_speed() const { return speed; }


/*


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

bool UnitDescription::is_building()
{
    return is_child_of("building");
}

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

}
