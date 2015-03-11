
#ifndef CIVILIZATION_DESCRIPTION_H_
#define CIVILIZATION_DESCRIPTION_H_

#include <vector>

#include "res/technology.h"

class Civilization;
class UnitDescription;
class PropertyFile;

class CivilizationDescription
{
private:
    std::string name;
    int id;

    int nunits;
    bool *units;
    int ntechs;
    bool *technologies;
public:
  CivilizationDescription(
          const PropertyFile& pfile,
          const std::vector<UnitDescription*>& units_,
          const std::vector<Technology>& techs);

  CivilizationDescription(const CivilizationDescription& desc);
  CivilizationDescription(CivilizationDescription& desc);

  ~CivilizationDescription();

  CivilizationDescription& operator=(const CivilizationDescription& desc) = delete;
  CivilizationDescription& operator=(CivilizationDescription& desc) = delete;

  Civilization* create();

  const std::string& get_name() const;
  void set_id(int id);
};


#endif
