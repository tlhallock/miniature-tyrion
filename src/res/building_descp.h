
#ifndef BUILDING_H_
#define BUILDING_H_

#include <iostream>

class PropertyFile;
class BuildingDescription;
class Building;


class BuildingDescription
{
 private:
    int id;
    std::string name;

    int ntechs, nunits;
    double *tech_creation_speed;
    double *unit_creation_speed;

 public:
  BuildingDescription(const std::string& name, int id, int nunits, int nres);
  ~BuildingDescription();

  BuildingDescription* clone();
  Building *create();

  void compile(const PropertyFile& table);

  friend std::ostream& operator<<(std::ostream& out, const BuildingDescription& u);
};


#endif
