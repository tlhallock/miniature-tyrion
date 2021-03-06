#include "resource.h"

#include "res/resource_descp.h"
#include <sstream>

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

int Resource::getImageId() const
{
    return type->getImageId();
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


SpatialType Resource::getSpatialType() const { return SpatialType::RESOURCE_TYPE; }
std::string Resource::getSpatialDescription() const
{
    std::stringstream ret;
    ret << *this;
    return ret.str();
}


}
