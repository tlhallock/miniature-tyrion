

#ifndef TECHNOLOGY_H_
#define TECHNOLOGY_H_

#include <iostream>
#include <set>

namespace aoe
{

class PropertyFile;

enum TechType
{
    Add,
    Multiply,
};

class Technology
{
private:
    std::string name;
    int id;
    std::set<std::string> includes;
    std::set<std::string> excludes;
    TechType type;
    double value;

public:
    Technology(const PropertyFile& filename, int id);
    ~Technology();


    int get_id() const;
    const std::string& get_name() const;
};

}

#endif
