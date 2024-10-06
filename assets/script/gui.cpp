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
                DrawRectangleV( Vector2Add( obj->pos, { 0, 5 }), { 1, 5 }, WHITE );
                DrawRectangleV( Vector2Add( obj->pos, { 0,-9 }), { 1, 5 }, WHITE );
                DrawRectangleV( Vector2Add( obj->pos, { 5, 0 }), { 5, 1 }, WHITE );
                DrawRectangleV( Vector2Add( obj->pos, {-9, 0 }), { 5, 1 }, WHITE );
                DrawRectangleV( obj->pos, { 1, 1 }, WHITE );
            } else {
                DrawRectangleV( Vector2Add( obj->pos, { 0, 3 }), { 1, 5 }, WHITE );
                DrawRectangleV( Vector2Add( obj->pos, { 0,-7 }), { 1, 5 }, WHITE );
                DrawRectangleV( Vector2Add( obj->pos, { 3, 0 }), { 5, 1 }, WHITE );
                DrawRectangleV( Vector2Add( obj->pos, {-7, 0 }), { 5, 1 }, WHITE );
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

    void enemy_stats( ptr_t<Item> self, ptr_t<Item> gui ){

        auto sht = GetScene(). GetItem("enemy").GetAttr("getHealth").as<function_t<float>>();

        gui->onDraw([=](){

            float h = GetRenderHeight(), w = GetRenderWidth();
            DrawRectangleLines( 8*w/100, 4*h/100, 84*w/100, 4*h/100, WHITE );
            DrawRectangle( 10*w/100, 3*h/100, 80*w/100, 3*h/100, BLACK );
            DrawRectangle( 10*w/100, 3*h/100, 80*w/100*sht(), 3*h/100, WHITE );

        });

    }

}}

/*────────────────────────────────────────────────────────────────────────────*/

namespace rl { namespace game {

    void player_stats( ptr_t<Item> self, ptr_t<Item> gui ){

        auto stt = GetScene().GetItem("player").GetAttr("getState").as<function_t<int*>>();
        auto def = GetScene().GetItem("player").GetAttr("getDeflt").as<function_t<int*>>();

        struct NODE {
           Texture img = LoadTexture( "assets/sprites/effect/selector.png" );
        }; ptr_t<NODE> obj = new NODE();

        gui->onDraw([=](){

            float h = GetRenderHeight(), w = GetRenderWidth();
            DrawRectangle( 2*w/100+2, 86*h/100+2, w/13, w/13, WHITE );
            DrawRectangleLines( 2*w/100, 86*h/100, w/13, w/13, WHITE );
            DrawRectangleLines( 2*w/100+4, 86*h/100+4, w/13-4, w/13-4, BLACK );

            DrawTexturePro( obj->img, { 32, 0, 32, 32 },
                { 4*w/100+3, 89*h/100+3, w/13-4, w/13-4 },
                { 16, 16 }, 0, WHITE 
            );
        
        });

        gui->onDraw([=](){

            float h = GetRenderHeight(), w = GetRenderWidth();
            float a = type::cast<float>( stt()[ stt()[5] ] );
            float b = type::cast<float>( stt()[ 0 ] );
            float c = stt()[ 4 ];
            float d = stt()[ 3 ];

            float _a = type::cast<float>( def()[ stt()[5] ] );
            float _b = type::cast<float>( def()[ 0 ] );
            float _c = def()[ 4 ];
            float _d = def()[ 3 ];

            uint x = 0;

            DrawRectangle( 10*w/100, 86*h/100, b*50, 2*h/100, RED );
            DrawRectangleLines( 10*w/100, 86*h/100, _b*50, 2*h/100, RED );

            DrawRectangle( 10*w/100, 89*h/100, a/2, 2*h/100, YELLOW );
            DrawRectangleLines( 10*w/100, 89*h/100, _a/2, 2*h/100, YELLOW );

            x=0; while( x<_d ){ float add = 3 * w / 95 * x; if( d-->0 ){
                DrawRectangle( 10*w/100+add, 95*h/100, 3*w/100, 2*h/100, GRAY );
            } else {
                DrawRectangleLines( 10*w/100+add, 95*h/100, 3*w/100, 2*h/100, GRAY );
            } x++; }

            x=0; while( x<_c ){ float add = 3 * w / 95 * x; if( c-->0 ){
                DrawRectangle( 10*w/100+add, 92*h/100, 3*w/100, 2*h/100, WHITE );
            } else {
                DrawRectangleLines( 10*w/100+add, 92*h/100, 3*w/100, 2*h/100, WHITE );
            } x++; }

        });

        self->onRemove([=](){
            if( IsTextureReady( obj->img ) ){ UnloadTexture( obj->img ); }
        });

    }

}}

/*────────────────────────────────────────────────────────────────────────────*/

namespace rl { namespace game {

    void gui( ptr_t<Item> self ){

        Item p_stat( player_stats, self );
        Item e_stat( enemy_stats, self );
        Item aim   ( gui_aim ); 

        self->onDraw([=](){ 
            float h = GetRenderHeight(), w = GetRenderWidth();
          //DrawRectangleV( { 0, 0        }, { w, 7*h/100 }, BLACK );
          //DrawRectangleV( { 0, 90*h/100 }, { w, 15*h/100 }, BLACK );
            DrawFPS( 5, 5 );
        });

        self->onRemove([=](){ 
            p_stat.close();
            e_stat.close();
            aim.close();
        });

    }

}}

/*────────────────────────────────────────────────────────────────────────────*/