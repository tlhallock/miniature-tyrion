

#ifndef TECHNOLOGY_H_
#define TECHNOLOGY_H_

#include <iostream>
#include <set>

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
    std::set<std::string> includes;
    std::set<std::string> excludes;
    TechType type;
    double value;

public:
    Technology(const PropertyFile& filename);
    ~Technology();
};

#endif
