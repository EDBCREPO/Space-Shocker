#pragma once

#include "../script/bullet.cpp"
#include "../script/player.cpp"
#include "../script/prop.cpp"
#include "../script/aim.cpp"
#include "../script/gui.cpp"

namespace rl { namespace scene {

    void scene_1( ptr_t<Scene> self ) {

        self->AppendItem( "prop",   rl::game::prop   );
        self->AppendItem( "player", rl::game::player );
        self->AppendItem( "bullet", rl::game::bullet );
        self->AppendItem( "aim",    rl::game::aim    );
        self->AppendItem( "gui",    rl::game::gui    );

        self->onDraw([](){
            ClearBackground( Color({ 45, 2, 37, 255 }) );
        });

    }

}}