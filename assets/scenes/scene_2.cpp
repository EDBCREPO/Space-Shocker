#pragma once

namespace rl { namespace scene {

    void scene_2( ptr_t<Scene> self ) {

        self->onDraw([](){
            ClearBackground( BLACK );
            DrawText( "Congratulation", 100, 100, 13, WHITE );
        });

    }

}}