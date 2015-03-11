
#include "util/fs.h"

#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <boost/algorithm/string/predicate.hpp>

#include <functional>

namespace aoe
{

void recurse(const std::string& root, std::function<void(const std::string&)> f)
{
    boost::filesystem::path targetDir(root);
    boost::filesystem::directory_iterator it(targetDir), eod;

    BOOST_FOREACH(boost::filesystem::path const &p, std::make_pair(it, eod))
    {
        if (is_regular_file(p))
        {
            f(p.string());
        }
        else if (is_directory(p))
        {
            recurse(p.string(), f);
        }
    }
}

bool file_ends_with(const std::string& filename, const std::string& ext)
{
//    if (ext.size() > filename.size()) return false;
//    return std::equal(ext.rbegin(), ext.rend(), filename.rbegin());
	
	return boost::algorithm::ends_with(filename, ext);
#if 0
    int length = filename.length();
    int ext_length = ext.length();
    if (length < ext_length)
    {
        return false;
    }
    for (int i=0; i<length; i++)
    {
        if (ext.at(ext_length-i) != filename.at(length - i))
        {
            return false;
        }
    }
    return true;
#endif
}

void collect_files_by_ext(const std::string& root_directory, std::vector<std::string>& files, const std::string& ext)
{
    recurse(root_directory, [&files, &ext](const std::string& filename)
    {
        if (!file_ends_with(filename, ext))
        {
            return;
        }
        files.push_back(filename);
    });
}



void ensure_directory_exists(const std::string& directory)
{
	boost::filesystem::create_directory(directory);
}

}
