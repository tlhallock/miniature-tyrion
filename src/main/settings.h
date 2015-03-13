#ifndef SETTINGS_H
#define SETTINGS_H

#include "model/area.h"

namespace aoe
{


class Settings
{
public:

    int DISPLAY_WIDTH = 640;
    int DISPLAY_HEIGHT = 480;

    double MAP_SIZE = 100;
    double MAP_WIDTH = MAP_SIZE;
    double MAP_HEIGHT = MAP_SIZE;
    Area INITIAL_VIEWPORT{0, 0, MAP_WIDTH, MAP_HEIGHT};

    double BACKGROUND_COLOR = 0.0;


    double PERCENT_OF_RADIUS = .75;

    double INITIAL_HEIGHT = 3;

    long EGNINE_CLOCK_FREQ = 2000;

    double ZOOM_AMOUNT = .5;

    int KEY_WAIT_TIME = 20;

    double MODEL_TO_OPENGL_RATIO = 1.0/20;
private:
    Settings();
    ~Settings();

public:
    static Settings& get_instance();
};


}

#endif // SETTINGS_H
