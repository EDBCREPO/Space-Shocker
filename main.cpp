#include <nodepp/nodepp.h>

using namespace nodepp;

#include "assets/script/game.cpp"
#include "assets/scenes/scene_1.cpp"

void onMain() {

    rl::Init( { 800, 600 }, 60, "Game" );

    rl::AppendScene( rl::scene::scene_1 );

    rl::onClose([](){
        console::log("Closed");
        rl::Close();
    });

}