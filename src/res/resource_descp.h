

#ifndef RESOURCE_H_
#define RESOURCE_H_

#include <iostream>

namespace aoe
{

class IdentifierTable;
class PropertyFile;

class ResourceDescription
{
private:
    std::string name;
    int id;

    int num_villagers;
    double width;
    double height;
    double rejuv_speed;
    double initial_cap;
    double player_init;

    int image_id;

public:
    ResourceDescription(int id, IdentifierTable& table, PropertyFile& file);
    ~ResourceDescription();

    const std::string& get_name() const;

    int get_image_id() const;
    double get_initial_value() const;
};

}


#endif
