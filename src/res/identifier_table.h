
#ifndef IDENTIFIER_TABLE_H_
#define IDENTIFIER_TABLE_H_

#include <string>
#include <map>

namespace aoe
{

class IdentifierTable
{
private:
	std::map<std::string, int> unit_ids;
	std::map<std::string, int> building_ids;
    std::map<std::string, int> resource_ids;
	std::map<std::string, int> image_ids;
	std::map<std::string, int> civilization_ids;
    std::map<std::string, int> technology_ids;

public:
    IdentifierTable();
    ~IdentifierTable();
	
	int get_unit_id(const std::string& name);
	int get_building_id(const std::string& name);
	int get_resource_id(const std::string& name);
	int get_image_id(const std::string& name);
	int get_civilization_id(const std::string& name);
    int get_technology_id(const std::string& name);

    const std::map<std::string, int>& get_units() const;
    const std::map<std::string, int>& get_buildings() const;
    const std::map<std::string, int>& get_resources() const;
    const std::map<std::string, int>& get_images() const;
    const std::map<std::string, int>& get_civilizations() const;
    const std::map<std::string, int>& get_technologies() const;
	
private:
	int get_id(std::map<std::string, int>& ids, const std::string& name);
};


}


#endif
