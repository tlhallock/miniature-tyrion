
#include "res/civilization_descp.h"
#include "res/property_file.h"
#include "model/civilization.h"

CivilizationDescription::CivilizationDescription(
        const PropertyFile& pfile,
        const std::vector<UnitDescription*>& units_,
        const std::vector<Technology>& techs) :
    name{pfile.get_property("name").asString()},
    nunits{(int) units_.size()},
    units{new bool[nunits]},
    ntechs{(int) techs.size()},
    technologies{new bool[ntechs]}
{
    for (int i=0;i<nunits;i++)
    {
//        // Could just use i, instead of get_id()
//        // This is all wrong:
//        units[units[i]->get_id()] = pfile.get_property("units", units_[i]->get_name());

        units[i] = true;
    }

//    for (int i=0;i<nunits;i++)
//    {
//        const std::string& uname = units[i]->get_name();
//        if (!pfile.has_property("units", uname))
//        {
//            continue;
//        }
//        bool enabled = pfile.get_property("units", uname);
//        for (int j=0;j<nunits;j++)
//        {
//            if (units[j]->is_child_of(uname))
//            {
//                units[j] = enabled;
//            }
//        }
//    }

    for (auto it=techs.begin();it!=techs.end();++it)
    {
        technologies[it->get_id()] = pfile.get_property("techs", it->get_name()).asBool();
    }
}

CivilizationDescription::CivilizationDescription(const CivilizationDescription& desc) :
       name{desc.name},
       id{desc.id},
       nunits{desc.nunits},
       units{new bool[nunits]},
       ntechs{desc.ntechs},
       technologies{new bool[ntechs]}
{
    for (int i=0;i<ntechs;i++)
    {
        technologies[i] = desc.technologies[i];
    }
    for (int i=0;i<nunits;i++)
    {
        units[i] = desc.units[i];
    }
}

CivilizationDescription::CivilizationDescription(CivilizationDescription& desc) : CivilizationDescription{desc} {}

CivilizationDescription::~CivilizationDescription()
{
    delete[] units;
    delete[] technologies;
}

Civilization* CivilizationDescription::create()
{
    Civilization* returnValue = new Civilization;

    for (int i=0;i<nunits;i++)
    {

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

