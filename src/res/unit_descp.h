

#ifndef UNIT_DESCP_H_
#define UNIT_DESCP_H_

#include <iostream>
#include <set>

class IdentifierTable;
class PropertyFile;
class UnitDescription;

class UnitDescription
{
 private:
    std::string name;
    int id;

  double speed;
  double carrying_capacity;
  double line_of_sight;
  double range;
  double width;
  double height;
  double health;
  int image_id;
  bool creatable;

  double* damage;
  double* resistance;
  double* cost;
  double* collection_speed;

  
  UnitDescription* parent;
  std::set<UnitDescription*> children;

 public:
  UnitDescription(
          IdentifierTable& table,
          const PropertyFile& propertyFile,
          int id_,
          int nunits,
          int nres);
  ~UnitDescription();

  void link_properties(UnitDescription** descriptions, const PropertyFile& propertyFile, int nunits);
  void link_building();

  UnitDescription* clone();
  UnitDescription *create();
  
  int get_id() const { return id; }
  UnitDescription* get_parent();
  void set_parent(UnitDescription*p);
  const std::set<UnitDescription*>& get_children() const;


  friend std::ostream& operator<<(std::ostream& out, const UnitDescription& u);



 private:
  bool is_child_of(const std::string& unitName);
};



#endif

