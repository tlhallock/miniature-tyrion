#ifndef UNITSTRUCTURE_H
#define UNITSTRUCTURE_H

#include <iostream>
#include <vector>
#include <set>

namespace aoe
{

class UnitStructure
{
private:
    std::vector<std::set<int>> children;
    int *parents;
public:
    UnitStructure();
    ~UnitStructure();

    void set_size(int nunits);

    int get_parent(int child) const;

    void set_parent(int child, int parent);
    const std::set<int>& get_children(int parent) const;

    void compile();

    int get_root() const;

   friend std::ostream& operator<<(std::ostream& out, const UnitStructure& u);
};

}

#endif // UNITSTRUCTURE_H
