
#ifndef FS_H_
#define FS_H_

#include <string>
#include <vector>

bool file_ends_with(const std::string& filename, const std::string& ext);

void collect_files_by_ext(const std::string& root_directory, std::vector<std::string>& files, const std::string& ext);

void ensure_directory_exists(const std::string& directory);

#endif

