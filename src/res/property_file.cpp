 
#include "res/property_file.h"
#include "util/fs.h"

#include <fstream>

Json::Value DEFAULT_JSON_VALUE;

namespace
{
	
void read_json(const std::string& filename, Json::Value& root)
{
	Json::Reader reader;
	
	std::ifstream in_stream {filename};
	if (!in_stream.is_open())
	{
		std::cerr << "Unable to open file " << filename << std::endl;
		exit(-1);
	}
	
	bool parsingSuccessful = reader.parse(in_stream, root );
	if ( !parsingSuccessful )
	{
		// report to the user the failure and their locations in the document.
		std::cerr << "Failed to parse configuration for " << filename << "\n"
			<< reader.getFormattedErrorMessages();
		exit(-1);
	}
	
	// Get the value of the member of root named 'encoding', return a 'null' value if
	// there is no such member.
//	const Json::Value plugins = root["plug-ins"];
//	for ( int index = 0; index < plugins.size(); ++index )  // Iterates over the sequence elements.
//	   loadPlugIn( plugins[index].asString() );
	
//	Json::StyledWriter writer;
//	// Make a new JSON document for the configuration. Preserve original comments.
//	std::string outputConfig = writer.write( root );
//	
//	// You can also use streams.  This will put the contents of any JSON
//	// stream at a particular sub-value, if you'd like.
//	std::cin >> root["subtree"];
//	
//	// And you can write to a stream, using the StyledWriter automatically.
//	std::cout << root;
}

}
PropertyFile::PropertyFile(OpenedPropertyFiles* pfiles, const std::string& filename_) :
	filename{filename_},
	opened{pfiles}
{
	read_json(filename, root);
	pfiles->opened.insert(std::pair<std::string, PropertyFile>{filename, *this});
	
}
PropertyFile::~PropertyFile() {}

Json::Value PropertyFile::get_property(const std::vector<std::string>& properties) const
{
	Json::Value current = root;
	for (auto it = properties.begin(); it != properties.end(); ++it)
	{
//		std::cout << "Getting " << *it << " within " << filename << std::endl;
		const Json::Value value = current.get(*it, DEFAULT_JSON_VALUE);
//		std::cout << "has value " << value.asString() << std::endl;
		
		if (value == DEFAULT_JSON_VALUE)
		{
			const PropertyFile *parent = get_parent();
			if (parent == nullptr)
			{
				std::cerr << "Property " << *it << " not defined in " << filename << std::endl;
				exit(-1);
			}
			
			return parent->get_property(properties);
		}
        	current = value;
	}
	
    return current;
}

Json::Value PropertyFile::get_property(const std::string& name) const
{
	std::vector<std::string> names;
	names.push_back(name);
	return get_property(names);
}

Json::Value PropertyFile::get_property(const std::string& name, const std::string& name2) const
{
	std::vector<std::string> names;
	names.push_back(name);
	names.push_back(name2);
	return get_property(names);
}

const PropertyFile* PropertyFile::get_parent() const
{
	const Json::Value pProperty = root.get("parent", DEFAULT_JSON_VALUE);
	if (pProperty == DEFAULT_JSON_VALUE)
	{
		return nullptr;
	}
	return &opened->get_property_file(opened->get_base() + pProperty.asString());
}


bool PropertyFile::should_ignore() const
{
    return get_property("ignore").asBool();
}










OpenedPropertyFiles::OpenedPropertyFiles(const std::string& root_directory_) : root_directory{root_directory_} { ensure_directory_exists(root_directory_); }
OpenedPropertyFiles::~OpenedPropertyFiles() {}

const PropertyFile& OpenedPropertyFiles::get_property_file(const std::string& filename)
{
	auto it = opened.find(filename);
	if (it != opened.end())
	{
		return it->second;
	}

	PropertyFile pfile{this, filename};

	return opened.find(filename)->second;
}

