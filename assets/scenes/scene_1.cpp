#pragma once

#include "../script/player.cpp"
#include "../script/gui.cpp"

namespace rl { namespace scene {

    void scene_1( ptr_t<Scene> self ) {

        self->AppendItem( "player", rl::game::player );
        self->AppendItem( "gui",    rl::game::gui    );

        self->onDraw([](){
            ClearBackground( Color({ 45, 2, 37, 255 }) );
        });

    }

}}