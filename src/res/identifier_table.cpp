
#include "res/identifier_table.h"
	
IdentifierTable::IdentifierTable() {}
IdentifierTable::~IdentifierTable() {}
	
int IdentifierTable::get_unit_id(const std::string& name)
{
	return get_id(unit_ids, name);
}
int IdentifierTable::get_building_id(const std::string& name)
{
	return get_id(building_ids, name);
}
int IdentifierTable::get_resource_id(const std::string& name)
{
	return get_id(resource_ids, name);
}
int IdentifierTable::get_image_id(const std::string& name)
{
	return get_id(image_ids, name);
}
int IdentifierTable::get_civilization_id(const std::string& name)
{
	return get_id(civilization_ids, name);
}
int IdentifierTable::get_technology_id(const std::string& name)
{
    return get_id(technology_ids, name);
}

int IdentifierTable::get_id(std::map<std::string, int>& ids, const std::string& name)
{
	auto it = ids.find(name);
	if (it == ids.end())
	{
		int id = ids.size();
        ids.insert(std::pair<std::string, int>{name, id});
		return id;
	}
	return it->second;
}

const std::map<std::string, int>& IdentifierTable::get_units() const            { return unit_ids         ; }
const std::map<std::string, int>& IdentifierTable::get_buildings() const        { return building_ids     ; }
const std::map<std::string, int>& IdentifierTable::get_resources() const        { return resource_ids     ; }
const std::map<std::string, int>& IdentifierTable::get_images() const           { return image_ids        ; }
const std::map<std::string, int>& IdentifierTable::get_civilizations() const    { return civilization_ids ; }
const std::map<std::string, int>& IdentifierTable::get_technologies() const     { return technology_ids   ; }
