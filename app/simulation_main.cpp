

#include <event_loop/RaylibGameLoop.h>
#include <renderer/RaylibRenderer.h>
#include <mouse_handler/RaylibMouseHandler.h>
#include <data_structures/NaiveLinear.h>
#include <data_structures/SpatialHash.h>
#include <data_structures/MultiLevelGrid.h>
#include <data_structures/SweepAndPrune.h>

int main(){
    MultiLevelGrid data_structure{};
    RaylibRenderer raylib_renderer{};
    RaylibMouseHandler raylib_mouse_handler{};
    RaylibGameLoop raylib_game_loop{data_structure, raylib_renderer, raylib_mouse_handler};

    raylib_game_loop.initialize();
    raylib_game_loop.run();

    return 0;
}
