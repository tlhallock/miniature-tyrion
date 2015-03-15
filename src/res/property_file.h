
#ifndef PROPERTY_FILE_H_
#define PROPERTY_FILE_H_

#include <iostream>
#include <vector>

#include <json/json.h>

namespace aoe
{

class PropertyFile;
class OpenedPropertyFiles;


extern Json::Value DEFAULT_JSON_VALUE;


class PropertyFile
{
private:
	std::string filename;
	Json::Value root;
	OpenedPropertyFiles* opened;

 public:
  PropertyFile(OpenedPropertyFiles* pfiles, const std::string& filename);
  ~PropertyFile();
  
  Json::Value get_property(const std::string& name, bool mustExist = true) const;
  Json::Value get_property(const std::string& name1, const std::string& name2, bool mustExist = true) const;
  Json::Value get_property(const std::vector<std::string>& values, bool mustExist = true) const;
  
  const PropertyFile* get_parent() const;
  bool should_ignore() const;
};



class OpenedPropertyFiles
{
	friend class PropertyFile;
	
private:
	std::string root_directory;
	std::map<std::string, PropertyFile> opened;
	
public:
    OpenedPropertyFiles(const std::string& root_directory);
    ~OpenedPropertyFiles();
	
    const PropertyFile& get_property_file(const std::string& filename, bool relative=true);
//    const PropertyFile& get_property_file(const std::string& filename, bool relative=true);

    const std::string& get_base() const
    {
        return root_directory;
    }
};

}



#endif



