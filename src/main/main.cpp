
#include <iostream>

#include "model/engine.h"
#include "gfx/cvdisplay.h"

#include "res/property_file.h"
#include "res/game_info.h"

#include "util/fs.h"
#include "model/game.h"
#include "gen/generator.h"

#include <X11/Xlib.h>

void initialize()
{
    aoe::GameInfo *info = new aoe::GameInfo{"./"};

    // need to set strategies

    std::vector<std::string> civ_names;
    civ_names.push_back("Turks");
    civ_names.push_back("Britons");

    aoe::Game* game = info->create_game(civ_names);


    generate_map(game->get_map());

    aoe::CvDisplay *display = new aoe::CvDisplay{game, info->get_images()};

    game->get_timer().add(display);


//    fill_map();
}


int main(int argc, char **argv)
{
    XInitThreads();
    aoe::ensure_directory_exists("data");

    initialize();
//  Engine *engine = new Engine();

//  Timer *timer = new Timer{200};

//  timer->add(engine);
//  timer->add(display);


//  PropertyFile pf {"test"};
  
//  std::this_thread::sleep_for(std::chrono::milliseconds(10000));



  //  timer.end();

  std::cout << "All done.\n";

  return 0;
}



