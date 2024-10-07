#pragma once

#include "../script/player.cpp"
#include "../script/enemy.cpp"
#include "../script/item.cpp"
#include "../script/gui.cpp"

namespace rl { namespace scene {

    void scene_1( ptr_t<Scene> self ) {

        self->AppendItem( "enemy",  rl::game::enemy  );
        self->AppendItem( "item",   rl::game::item   );
        self->AppendItem( "player", rl::game::player );
        self->AppendItem( "gui",    rl::game::gui    );

        self->onDraw([](){
            ClearBackground( Color({ 69, 2, 41, 255 }) );
        });

    }

}}