
#include <iostream>

#include "model/engine.h"
#include "gfx/cvdisplay.h"

#include "res/property_file.h"
#include "res/game_info.h"
#include "ai/player/ai_strategy.h"
#include "util/timer.h"
#include "util/fs.h"
#include "model/game.h"
#include "gen/generator.h"
#include "main/settings.h"
#include "model/player.h"

#include "gfx/gldisplay.h"

#include <X11/Xlib.h>
#include <GL/glut.h>

int main_2(int argc, char* argv[]);

namespace aoe
{
void test();
}

int main(int argc, char **argv)
{
    aoe::test();
    if (1) return 0;
//    main_2(argc, argv);
    XInitThreads();
    glutInit(&argc, argv);

    aoe::ensure_directory_exists("data");

    // The images are still used after this method...
    aoe::GameInfo& info = *new aoe::GameInfo{"."};

    // need to set strategies

    std::vector<std::string> civ_names;
    civ_names.push_back("Turks");
    civ_names.push_back("Britons");

    aoe::Game* game = new aoe::Game{info.get_table()};

    int nplayers = 2;
    for (int i=0;i<nplayers;i++)
    {

        game->add_player(new aoe::AiStrategy{&game->get_engine()}, new aoe::Player{info.create_civilization(0),
                                                  info.clone_resources(),
                                                  game->get_map().get_civilization_center(i, nplayers)});
    }

    aoe::generate_map(&info, game);


    aoe::Timer timer{aoe::Settings::get_instance().ENGINE_CLOCK_FREQ};

    timer.add(game);

    aoe::GlDisplay* display = new aoe::GlDisplay(info, "OpenGL");

    timer.start();

    display->renderLoop(game);

    if (1)
    {
        exit(-1);
    }

    delete display;

    timer.end();

    delete game;

    std::cout << "All done.\n";

    return 0;
}



