

#ifndef UNIT_DESCP_H_
#define UNIT_DESCP_H_

#include <iostream>
#include <set>
#include <vector>

namespace aoe
{

class IdentifierTable;
class PropertyFile;
class UnitDescription;
class UnitStructure;
class Unit;
class Location;

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

    std::vector<double> damage;
    std::vector<double> resistance;
    std::vector<double> cost;
    std::vector<double> collection_speed;

    std::set<int> creates_units;
    std::set<int> creates_techs;
public:
    UnitDescription(
            IdentifierTable& table,
            const PropertyFile& propertyFile,
            int id_,
            int nunits,
            int nres);
    ~UnitDescription();

    void link_units(IdentifierTable& table,
                                          std::vector<UnitDescription>& descriptions,
                                          const PropertyFile& propertyFile,
                                          const UnitStructure& tree);
    void link_techs(IdentifierTable& table,
                                          std::vector<UnitDescription>& descriptions,
                                          const PropertyFile& propertyFile,
                                          const UnitStructure& tree);

    Unit *create() const;

    int get_id() const;

    friend std::ostream& operator<<(std::ostream& out, const UnitDescription& u);

    const std::string& get_name() const;

    int get_image_id() const;

    bool isCreatable() const;
    Location get_size() const;
    double get_width() const;
    double get_height() const;

private:
    bool is_child_of(const std::string& unitName);
    bool is_building();
};


}


#endif

