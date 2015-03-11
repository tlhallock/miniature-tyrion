#ifndef UNITSTRUCTURE_H
#define UNITSTRUCTURE_H

#include <iostream>
#include <vector>
#include <set>

class UnitStructure
{
private:
    std::vector<std::set<int>> children;
public:
    UnitStructure();
    ~UnitStructure();

    void set_size(int nunits);

    void set_parent(int child, int parent);
    const std::set<int>& get_children(int parent) const;

   void compile();

   friend std::ostream& operator<<(std::ostream& out, const UnitStructure& u);
};

#endif // UNITSTRUCTURE_H
