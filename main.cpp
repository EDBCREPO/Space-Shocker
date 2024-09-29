#include <nodepp/nodepp.h>
#include <nodepp/timer.h>

using namespace nodepp;

#include "Assets/script/game.cpp"
#include "Assets/scenes/scene_1.cpp"

void onMain() {

    rl::Init( { 800, 600 }, 60, "Game" );

    rl::AppendScene( rl::scene::scene_1 );

    rl::onClose([](){
        console::log("Closed");
        rl::Close();
    });

}