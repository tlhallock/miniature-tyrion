
#include "res/technology.h"

#include "res/property_file.h"

Technology::Technology(const PropertyFile& filename, int id_) :
    name{filename.get_property("name").asString()},
    id{id_}
{

}

Technology::~Technology() {}


int Technology::get_id() const
{
    return id;
}


const std::string& Technology::get_name() const
{
    return name;
}
