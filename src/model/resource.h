#ifndef RESOURCE_H
#define RESOURCE_H

#include "gfx/gfx.h"
#include "model/area.h"

namespace aoe
{

class ResourceDescription;

class Resource : public Gfx
{
private:
    ResourceDescription *type;
    Area location;
public:
    Resource(ResourceDescription* type, const Area& location);
    ~Resource();

    int get_image_id() const;
    const Area& get_location() const;


    friend std::ostream& operator<<(std::ostream& out, const Resource& g);
};

}

#endif // RESOURCE_H
