#include "res/unit_structure.h"

namespace aoe
{

UnitStructure::UnitStructure() : parents{nullptr} {}
UnitStructure::~UnitStructure() { delete[] parents; }

void UnitStructure::set_size(int nunits)
{
    delete[] parents;
    parents = new int[nunits];
    for (int i=0;i<nunits;i++)
    {
        parents[i] = -1;
        children[i].insert(i);
    }
    children.resize(nunits);
}

void UnitStructure::set_parent(int child, int parent)
{
    parents[child] = parent;
    children[parent].insert(child);
}

int UnitStructure::get_parent(int child) const
{
    return parents[child];
}

const std::set<int>& UnitStructure::get_children(int parent) const
{
    return children[parent];
}

#if 0
namespace
{
    void recurse(std::vector<std::set<int>>& children, int i)
    {
        if (children[i].size() == 0)
        {
            return;
        }

        do
        {
            auto end = children[i].end();
            for (auto it = children[i].begin(); it != end; ++it)
            {
                int osize = children[i].size();
                children[i].insert(children[*it].begin(), children[*it].end());
                if (osize != children[i].size())
                {
                    continue;
                }
            }
            break;
        } while (true);
    }
}
#endif

void UnitStructure::compile()
{
    int nunits = (int) children.size();

    for (int i=0;i<nunits;i++)
    {
        std::set<int> accum;
        accum.insert(i);

        int p;
        int current = i;
        while ((p = parents[current]) >= 0)
        {
            children[p].insert(accum.begin(), accum.end());
            accum.insert(children[p].begin(), children[p].end());
            current = p;
        }
    }
}

std::ostream& operator<<(std::ostream& out, const UnitStructure& u)
{
    int nunits = (int) u.children.size();
    for (int i=0; i<nunits;i++)
    {
        out << "\tUnit:" << i << " has ";
        for (auto it = u.children[i].begin(); it != u.children[i].end(); ++it)
        {
            out << *it << " ";
        }
        out << "\n";
    }
    return out;
}

int UnitStructure::get_root() const
{
    int current = 0;
    while (parents[current] >= 0)
    {
        current = parents[current];
    }
    return current;
}


}
