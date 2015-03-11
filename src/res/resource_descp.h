

#ifndef RESOURCE_H_
#define RESOURCE_H_

#include <iostream>

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
    double initial_player_value;

    int image_id;

public:
    ResourceDescription(int id, IdentifierTable& table, PropertyFile& file);
    ~ResourceDescription();
};


#endif
