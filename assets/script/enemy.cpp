#pragma once

namespace rl { namespace game {

    void enemy( ptr_t<Item> self ) {

        struct NODE {
            Rectangle pos = { GetRenderWidth()*0.5f, GetRenderHeight()*0.5f, 32, 32 };
            Texture   img = LoadTexture( "assets/sprites/enemy/estados.png" );

        };  ptr_t<NODE> obj = new NODE();

        console::done("DONE");

    }

}}