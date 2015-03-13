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

    double MAP_WIDTH = 20;
    double MAP_HEIGHT = 20;
    Area INITIAL_VIEWPORT{0, 0, MAP_WIDTH, MAP_HEIGHT};

    double BACKGROUND_COLOR = 0.0;


    double PERCENT_OF_RADIUS = .75;

    double INITIAL_HEIGHT = 3;

    long EGNINE_CLOCK_FREQ = 2000;
private:
    Settings();
    ~Settings();

public:
    static Settings& get_instance();
};


}

#endif // SETTINGS_H
