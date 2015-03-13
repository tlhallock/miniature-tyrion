
#include "res/civilization_descp.h"
#include "res/property_file.h"
#include "model/civilization.h"

namespace aoe
{

CivilizationDescription::CivilizationDescription(
        const PropertyFile& pfile,
        IdentifierTable& table) :
    name {pfile.get_property("name").asString()}
{

}

CivilizationDescription::~CivilizationDescription() {}


Civilization* CivilizationDescription::create(const std::vector<UnitDescription>& basis) const
{
    Civilization* returnValue = new Civilization{name, basis};

    for (auto it = buildings.begin(); it != buildings.end(); ++it)
    {
        if (it->overridden)
        {
            returnValue->enable(it->value);
        }
        else
        {
            returnValue->disable(it->value);
        }
    }

    return returnValue;
}



const std::string& CivilizationDescription::get_name() const
{
    return name;
}

void CivilizationDescription::set_id(int id_)
{
    id = id_;
}




}
