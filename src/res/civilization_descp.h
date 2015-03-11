
#ifndef CIVILIZATION_DESCRIPTION_H_
#define CIVILIZATION_DESCRIPTION_H_

class Civilization;

class CivilizationDescription
{
private:
    bool *units;
    bool *technologies;
public:
  CivilizationDescription(int nunits, int ntechs);
  ~CivilizationDescription();

  Civilization* create();
};


#endif
