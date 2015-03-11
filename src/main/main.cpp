
#include <iostream>

#include "model/engine.h"
#include "gfx/cvdisplay.h"

#include "res/property_file.h"
#include "res/game_info.h"

#include "util/fs.h"
#include "model/game.h"
#include "gen/generator.h"

void initialize()
{
    GameInfo *info = new GameInfo{"./"};

    // need to set strategies

    std::vector<std::string> civ_names;
    civ_names.push_back("Turks");
    civ_names.push_back("Britons");

    Game* game = info->create_game(civ_names);

    generate_map(game->get_map());
//    fill_map();
}


int main(int argc, char **argv)
{
    ensure_directory_exists("data");
//  Engine *engine = new Engine();
//  CvDisplay *display = new CvDisplay{engine};

//  Timer *timer = new Timer{200};

//  timer->add(engine);
//  timer->add(display);


//  PropertyFile pf {"test"};
  
//  std::this_thread::sleep_for(std::chrono::milliseconds(10000));



  //  timer.end();

  std::cout << "All done.\n";

  return 0;
}


