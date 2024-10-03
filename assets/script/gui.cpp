#pragma once

/*────────────────────────────────────────────────────────────────────────────*/

namespace rl { namespace game {

    void gui_aim( ptr_t<Item> self ) {

        struct NODE {
            bool b = 0; 
            Vector2 pos = { 0, 0 };
        };  ptr_t<NODE> obj = new NODE(); 
        
        HideCursor(); DisableCursor();

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

        self->onLoop([=]( float delta ){[=](){
            obj->pos.x = GetMouseX();
            obj->pos.y = GetMouseY();
        coStart
            obj->b =! obj->b;
            coDelay( 150 );
        coStop
        }();});

    }

}}

/*────────────────────────────────────────────────────────────────────────────*/

namespace rl { namespace game {

    void player_stats( ptr_t<Item> self, ptr_t<Item> gui ){

        auto stt = GetScene().GetItem("player").GetAttr("getState").as<function_t<int*>>();

        gui->onDraw([=](){

            float h = GetRenderHeight(), w = GetRenderWidth();

            float x = type::cast<float>( stt()[ stt()[5] ] );

            DrawRectangleV( { w/10*1.5f+12, 10*h/12 }, { x/3, 10 }, YELLOW );

        });

    }

}}

/*────────────────────────────────────────────────────────────────────────────*/

namespace rl { namespace game {

    void gui( ptr_t<Item> self ){

        Item aim ( gui_aim ); Item p_stat( player_stats, self );

        self->onDraw([=](){ 

            float h = GetRenderHeight(), w = GetRenderWidth();

            DrawRectangleV( { 0, 0     }, { w, h/10 }, BLACK );
            DrawRectangleV( { 0, 7*h/8 }, { w, h/8  }, BLACK );

            DrawRectangleLines( 28, 10*h/12-2, w/10, w/10, WHITE );
            DrawRectangleV( { 30, 10*h/12 }, { w/10, w/10 }, WHITE );
            DrawRectangleLines( 30+2, 10*h/12+2, w/10-4, w/10-4, BLACK );

            DrawFPS( 5, 5 );
        });

    }

}}

/*────────────────────────────────────────────────────────────────────────────*/