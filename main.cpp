#include <nodepp/nodepp.h>

using namespace nodepp;

#include "assets/script/game.cpp"
#include "assets/scenes/scene_2.cpp"
#include "assets/scenes/scene_1.cpp"
#include "assets/scenes/scene_0.cpp"

void onMain() {

    rl::Init( { 800, 600 }, 60, "Cursed Luna" );

    rl::AppendScene( rl::scene::scene_1 );

    rl::onClose([](){
        console::log("Closed");
        rl::Close();
    });

}