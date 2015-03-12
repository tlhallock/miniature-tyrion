#include "main/settings.h"

namespace aoe
{

Settings::Settings() {}
Settings::~Settings() {}

Settings& Settings::get_instance()
{
    static Settings instance;
    return instance;
}


}
