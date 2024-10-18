

#pragma once

namespace rl { namespace scene {

    void scene_0( ptr_t<Scene> self ) {

        self->onDraw([](){
            ClearBackground( BLACK );
            DrawText( "You Have Died", 100, 100, 13, WHITE );
        });

    }

}}