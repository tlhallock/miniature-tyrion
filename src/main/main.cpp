
#include <iostream>

#include "model/engine.h"
#include "gfx/cvdisplay.h"

#include "res/property_file.h"
#include "res/game_info.h"
#include "ai/player/ai_strategy.h"

#include "util/fs.h"
#include "model/game.h"
#include "gen/generator.h"

#include "model/player.h"

#include "gfx/gldisplay.h"

#include <X11/Xlib.h>
#include <GL/glut.h>

int main_2(int argc, char* argv[]);

int main(int argc, char **argv)
{
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

    game->start();

    aoe::GlDisplay* display = new aoe::GlDisplay(info, "OpenGL");

    display->renderLoop(game);

    delete display;

    game->end();

    delete game;

    std::cout << "All done.\n";

    return 0;
}



