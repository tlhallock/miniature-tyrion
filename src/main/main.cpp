
#include <iostream>

#include "model/engine.h"
#include "gfx/cvdisplay.h"

#include "res/property_file.h"
#include "res/game_info.h"

#include "util/fs.h"
#include "model/game.h"
#include "gen/generator.h"

#include "model/player.h"

#include <X11/Xlib.h>

aoe::Game* start_game(const std::string& root_dir)
{
    // The images are still used after this method...
    aoe::GameInfo& info = *new aoe::GameInfo{root_dir};

    // need to set strategies

    std::vector<std::string> civ_names;
    civ_names.push_back("Turks");
    civ_names.push_back("Britons");

    aoe::Game* game = new aoe::Game;

    for (int i=0;i<2;i++)
    {
        game->add_player(nullptr, new aoe::Player{info.create_civilization(0), info.clone_resources()});
    }

    aoe::generate_map(game);

    aoe::CvDisplay *display = new aoe::CvDisplay{game, info.get_images()};

    game->get_timer().add(display);

    game->start();

    return game;
}


int main(int argc, char **argv)
{
    XInitThreads();
    aoe::ensure_directory_exists("data");


    aoe::Game* game = start_game("./");

    std::this_thread::sleep_for(std::chrono::milliseconds(10000));

    game->end();

    std::cout << "All done.\n";

    return 0;
}



