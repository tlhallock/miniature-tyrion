#-------------------------------------------------
#
# Project created by QtCreator 2015-03-09T11:10:43
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = LastIde
CONFIG   += console
CONFIG   -= app_bundle
CONFIG += debug

TEMPLATE = app

LIBS += -L/work/miniature-tyrion/opencv/prefix/lib \
-ljsoncpp \
-lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_imgcodecs \
-lboost_filesystem  -lboost_system \
-lX11 \
-lGL -lGLU -lglut \
-lboost_log

INCLUDEPATH += src /usr/include/jsoncpp/ /work/miniature-tyrion/opencv/prefix/include/ /work/miniature-tyrion/opencv/opencv/build

QMAKE_CXXFLAGS += -std=c++11 -Wunused-parameter -pg
QMAKE_LFLAGS += -pg


OTHER_FILES +=


OBJECTS_DIR=objects/

#-lglut -lglu








SOURCES += \
        src/ai/player/ai_strategy.cpp \
        src/ai/player/network_strategy.cpp \
        src/ai/player/player_listener.cpp \
        src/ai/player/strategy.cpp \
        src/ai/player/user_strategy.cpp \
        src/ai/unit/collect_strategy.cpp \
        src/ai/unit/construct_strategy.cpp \
        src/ai/unit/defend_strategy.cpp \
        src/ai/unit/farm_strategy.cpp \
        src/ai/unit/follow_strategy.cpp \
        src/ai/unit/harass_strategy.cpp \
        src/ai/unit/hide_strategy.cpp \
        src/ai/unit/monitor_strategy.cpp \
        src/ai/unit/random_movement_strategy.cpp \
        src/ai/unit/route_strategy.cpp \
        src/ai/unit/scout_strategy.cpp \
        src/ai/unit/unit_listener.cpp \
        src/ai/unit/unit_strategy.cpp \
        src/gen/generator.cpp \
        src/gfx/cvdisplay.cpp \
        src/gfx/display.cpp \
        src/gfx/gfx.cpp \
        src/gfx/gfxobject.cpp \
        src/gfx/glapi.cpp \
        src/gfx/gldisplay.cpp \
        src/gfx/viewport_listener.cpp \
        src/main/main.cpp \
        src/main/settings.cpp \
        src/model/building.cpp \
        src/model/civilization.cpp \
        src/model/engine.cpp \
        src/model/game.cpp \
        src/model/map.cpp \
        src/model/player.cpp \
        src/model/resource.cpp \
        src/model/spc/area.cpp \
        src/model/spc/location.cpp \
        src/model/spc/size.cpp \
        src/model/unit.cpp \
        src/res/civilization_descp.cpp \
        src/res/game_info_construction.cpp \
        src/res/game_info.cpp \
        src/res/identifier_table.cpp \
        src/res/images.cpp \
        src/res/property_file.cpp \
        src/res/resource_descp.cpp \
        src/res/technology.cpp \
        src/res/unit_descp.cpp \
        src/res/unit_structure.cpp \
        src/task/attack.cpp \
        src/task/build.cpp \
        src/task/collect.cpp \
        src/task/create.cpp \
        src/task/movable.cpp \
        src/task/research.cpp \
        src/task/task.cpp \
        src/util/fs.cpp \
        src/util/timer.cpp \

HEADERS += \
        src/ai/player/ai_strategy.h \
        src/ai/player/network_strategy.h \
        src/ai/player/player_listener.h \
        src/ai/player/strategy.h \
        src/ai/player/user_strategy.h \
        src/ai/unit/collect_strategy.h \
        src/ai/unit/construct_strategy.h \
        src/ai/unit/defend_strategy.h \
        src/ai/unit/farm_strategy.h \
        src/ai/unit/follow_strategy.h \
        src/ai/unit/harass_strategy.h \
        src/ai/unit/hide_strategy.h \
        src/ai/unit/monitor_strategy.h \
        src/ai/unit/random_movement_strategy.h \
        src/ai/unit/route_strategy.h \
        src/ai/unit/scout_strategy.h \
        src/ai/unit/unit_event.h \
        src/ai/unit/unit_listener.h \
        src/ai/unit/unit_strategy.h \
        src/gen/generator.h \
        src/gfx/cvdisplay.h \
        src/gfx/display.h \
        src/gfx/gfx.h \
        src/gfx/gfxobject.h \
        src/gfx/glapi.h \
        src/gfx/gldisplay.h \
        src/gfx/viewport_listener.h \
        src/main/settings.h \
        src/model/building.h \
        src/model/civilization.h \
        src/model/destructible.h \
        src/model/engine.h \
        src/model/game.h \
        src/model/map.h \
        src/model/player.h \
        src/model/resource.h \
        src/model/spc/area.h \
        src/model/spc/location.h \
        src/model/spc/size.h \
        src/model/unit.h \
        src/res/civilization_descp.h \
        src/res/game_info.h \
        src/res/identifier_table.h \
        src/res/images.h \
        src/res/property_file.h \
        src/res/resource_descp.h \
        src/res/technology.h \
        src/res/unit_descp.h \
        src/res/unit_structure.h \
        src/task/attack.h \
        src/task/build.h \
        src/task/collect.h \
        src/task/create.h \
        src/task/movable.h \
        src/task/research.h \
        src/task/task.h \
        src/util/fs.h \
        src/util/timer.h \

