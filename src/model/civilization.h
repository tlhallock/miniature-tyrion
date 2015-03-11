#ifndef CIVILIZATION_H
#define CIVILIZATION_H

#include <iostream>

class Player;
class Building;

class Civilization
{
private:
    std::map<std::set<int>> buildings;
    Player *parent;

public:
    Civilization();
    ~Civilization();

    void set_player(Player* parent);

    void enable(int building);
    void enable(int builing, int unit);

    Building* create_building(int building_id);
};

#endif // CIVILIZATION_H
