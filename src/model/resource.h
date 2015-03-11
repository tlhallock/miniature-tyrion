#ifndef RESOURCE_H
#define RESOURCE_H

#include "model/area.h"

class ResourceDescription;

class Resource
{
private:
    ResourceDescription *type;
    Area location;
    int quantity;
    int num_villages;
public:
    Resource();
    ~Resource();
};

#endif // RESOURCE_H
