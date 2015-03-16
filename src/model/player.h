#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include <vector>

#include "model/spc/area.h"
#include "model/civilization.h"

namespace aoe
{

class Civilization;
class CivilizationDescription;
class Unit;
class Building;
class PlayerListener;
class GameInfo;

class Player
{
private:
    std::unique_ptr<Civilization> civilization;

    std::vector<Unit*> units;
    std::vector<Building*> buildings;
    std::vector<double> resources;

    std::vector<PlayerListener*> listeners;

    Location center;

public:
    Player(Civilization* civ, const std::vector<double>& res, const Location& center);
    ~Player();

    void add_listener(PlayerListener* listener);
    void remove_listener(PlayerListener* listener);

    Civilization* get_civilization();
    const Location& get_location();

    void unit_added(Unit* unit);

};

}

#endif // PLAYER_H
