
#ifndef CIVILIZATION_DESCRIPTION_H_
#define CIVILIZATION_DESCRIPTION_H_

class Civilization;

class CivilizationDescription
{
private:
    int nunits;
    bool *units;
    int ntechs;
    bool *technologies;
public:
  CivilizationDescription(
          const PropertyFile& pfile,
          int nunits_, UnitDescription** units_,
          std::vector<Technology>& techs);
  ~CivilizationDescription();

  Civilization* create();
};


#endif
