
#ifndef CIVILIZATION_DESCRIPTION_H_
#define CIVILIZATION_DESCRIPTION_H_

#include <map>
#include <set>

#include "res/technology.h"
#include "res/unit_descp.h"

namespace aoe
{

class Civilization;
class PropertyFile;
class IdentifierTable;
class CivilizationDescription;

class Override
{
    friend class CivilizationDescription;

    int value;
    bool overridden;

    Override(int value_, bool overridden_) : value{value_}, overridden{overridden_} {}
    bool operator() (const Override& o1, const Override& o2) { return o1.value > o2.value; }
};


class CivilizationDescription
{
private:
    std::string name;
    int id;

    std::set<Override> buildings;
    std::map<int, std::set<Override>> units;
    std::set<Override> techs;

public:
  CivilizationDescription(
          const PropertyFile& pfile,
          IdentifierTable& table);

  ~CivilizationDescription();

  Civilization* create(const std::vector<UnitDescription>& basis) const;

  const std::string& get_name() const;
  void set_id(int id);
};

}


#endif
