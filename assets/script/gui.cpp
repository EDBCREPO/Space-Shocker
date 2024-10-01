#pragma once

/*────────────────────────────────────────────────────────────────────────────*/

namespace rl { namespace game {

    void gui_aim( ptr_t<Item> self ) {

        struct NODE {
            bool b = 0;
            Vector2 pos = { 0, 0 };
        };  ptr_t<NODE> obj = new NODE();

        HideCursor(); DisableCursor();

        auto idt = timer::interval([=](){ obj->b =! obj->b; }, 150 );

        self->onDraw([=](){
            if( obj->b ){
                DrawRectangleV( Vector2Add( obj->pos, { 0, 5 }), { 1, 5 }, rl::WHITE );
                DrawRectangleV( Vector2Add( obj->pos, { 0,-9 }), { 1, 5 }, rl::WHITE );
                DrawRectangleV( Vector2Add( obj->pos, { 5, 0 }), { 5, 1 }, rl::WHITE );
                DrawRectangleV( Vector2Add( obj->pos, {-9, 0 }), { 5, 1 }, rl::WHITE );
                DrawRectangleV( obj->pos, { 1, 1 }, rl::WHITE );
            } else {
                DrawRectangleV( Vector2Add( obj->pos, { 0, 3 }), { 1, 5 }, rl::WHITE );
                DrawRectangleV( Vector2Add( obj->pos, { 0,-7 }), { 1, 5 }, rl::WHITE );
                DrawRectangleV( Vector2Add( obj->pos, { 3, 0 }), { 5, 1 }, rl::WHITE );
                DrawRectangleV( Vector2Add( obj->pos, {-7, 0 }), { 5, 1 }, rl::WHITE );
            }
        });

        self->onLoop([=]( float delta ){
            obj->pos.x = GetMouseX();
            obj->pos.y = GetMouseY();
        });

        self->onRemove([=](){ 
            timer::clear( idt );
        });

    }

}}

/*────────────────────────────────────────────────────────────────────────────*/

namespace rl { namespace game {

    void gui( ptr_t<Item> self ){

        Item aim ( gui_aim );

        self->onDraw([=](){ auto y = GetRenderHeight() - GetRenderHeight()*0.15f;
            DrawRectangleV( { 0, 0 }, { GetRenderWidth()*1.0f, GetRenderHeight()*0.10f }, BLACK );
            DrawRectangleV( { 0, y }, { GetRenderWidth()*1.0f, GetRenderHeight()*0.15f }, BLACK );
            DrawFPS( 5, 5 );
        });

    }

}}

/*────────────────────────────────────────────────────────────────────────────*/