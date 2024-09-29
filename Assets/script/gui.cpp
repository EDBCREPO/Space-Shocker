#pragma once

namespace rl { namespace game {

    void gui( ptr_t<Item> self ){

        self->onDraw([=](){ auto y = GetRenderHeight() - GetRenderHeight()*0.15f;
            DrawRectangleV( { 0, 0 }, { GetRenderWidth()*1.0f, GetRenderHeight()*0.10f }, BLACK );
            DrawRectangleV( { 0, y }, { GetRenderWidth()*1.0f, GetRenderHeight()*0.15f }, BLACK );
            DrawFPS( 5, 5 );
        });

    }

}}