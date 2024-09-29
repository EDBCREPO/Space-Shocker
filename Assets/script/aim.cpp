#pragma once 

namespace rl { namespace game {

    void aim( ptr_t<Item> self ) {

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