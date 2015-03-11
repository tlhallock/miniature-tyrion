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

LIBS += -ljsoncpp -lopencv_core -lopencv_highgui -lboost_filesystem -lboost_log -lboost_system


INCLUDEPATH += src /usr/include/jsoncpp/

QMAKE_CXXFLAGS += -std=c++11 -Wunused-parameter


OTHER_FILES +=


OBJECTS_DIR=objects/



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
        src/ai/unit/route_strategy.cpp \
        src/ai/unit/scout_strategy.cpp \
        src/ai/unit/unit_listener.cpp \
        src/gen/generator.cpp \
        src/gfx/cvdisplay.cpp \
        src/main/main.cpp \
        src/model/area.cpp \
        src/model/building.cpp \
        src/model/civilization.cpp \
        src/model/engine.cpp \
        src/model/game.cpp \
        src/model/map.cpp \
        src/model/player.cpp \
        src/model/resource.cpp \
        src/model/unit.cpp \
        src/res/civilization_descp.cpp \
        src/res/game_info.cpp \
        src/res/identifier_table.cpp \
        src/res/images.cpp \
        src/res/property_file.cpp \
        src/res/resource_descp.cpp \
        src/res/technology.cpp \
        src/res/unit_descp.cpp \
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
        src/ai/unit/route_strategy.h \
        src/ai/unit/scout_strategy.h \
        src/ai/unit/unit_listener.h \
        src/gen/generator.h \
        src/gfx/cvdisplay.h \
        src/gfx/display.h \
        src/model/area.h \
        src/model/building.h \
        src/model/civilization.h \
        src/model/destructible.h \
        src/model/engine.h \
        src/model/game.h \
        src/model/map.h \
        src/model/player.h \
        src/model/resource.h \
        src/model/unit.h \
        src/res/civilization_descp.h \
        src/res/game_info.h \
        src/res/identifier_table.h \
        src/res/images.h \
        src/res/property_file.h \
        src/res/resource_descp.h \
        src/res/technology.h \
        src/res/unit_descp.h \
        src/task/attack.h \
        src/task/build.h \
        src/task/collect.h \
        src/task/create.h \
        src/task/movable.h \
        src/task/research.h \
        src/task/task.h \
        src/util/fs.h \
        src/util/timer.h \

