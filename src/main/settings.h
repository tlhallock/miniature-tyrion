#ifndef SETTINGS_H
#define SETTINGS_H

#include "model/area.h"

namespace aoe
{


class Settings
{
public:

    int DISPLAY_WIDTH = 500;
    int DISPLAY_HEIGHT = 500;

    double MAP_WIDTH = 1000;
    double MAP_HEIGHT = 1000;
    Area INITIAL_VIEWPORT{0, 0, MAP_WIDTH, MAP_HEIGHT};

    double BACKGROUND_COLOR = 0.0;


    double PERCENT_OF_RADIUS = .75;
private:
    Settings();
    ~Settings();

public:
    static Settings& get_instance();
};


}

#endif // SETTINGS_H
