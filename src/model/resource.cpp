#include "resource.h"

#include "res/resource_descp.h"

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
const Area& Resource::get_location() const
{
    return location;
}
