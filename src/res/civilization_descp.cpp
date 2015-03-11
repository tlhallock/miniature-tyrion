
#include "res/civilization_descp.h"

#include "model/civilization.h"

CivilizationDescription::CivilizationDescription(
        const PropertyFile& pfile,
        int nunits_, UnitDescription** units_,
        std::vector<Technology>& techs) :
    nunits{nunits_},
    ntechs{techs.size()},
    units{new bool[nunits]},
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
