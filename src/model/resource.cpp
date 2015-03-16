#include "resource.h"

#include "res/resource_descp.h"

namespace aoe
{

Resource::Resource(ResourceDescription* type_, const Area& location_) :
    type{type_},
    location{location_}
{
}

Resource::~Resource()
{
}

int Resource::get_image_id() const
{
    return type->get_image_id();
}
Area& Resource::getArea()
{
    return location;
}

const Area& Resource::getArea() const
{
    return location;
}


std::ostream& operator<<(std::ostream& out, const Resource& g)
{
    return out << g.type->get_name() << " at " << g.location;
}


}
