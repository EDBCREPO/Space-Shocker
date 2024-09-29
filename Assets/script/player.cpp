#pragma once

#include "prop.cpp"

namespace rl { namespace game {

    void player( ptr_t<Item> self ) {

        struct NODE {
            Rectangle pos = { GetRenderWidth()*0.5f, GetRenderHeight()*0.5f, 32, 32 };
            Texture   img = LoadTexture( "Assets/sprites/player/player.png" );
            float     spd = 300;
            float     ang = 0;
            bool        b = 0;
        };  ptr_t<NODE> obj = new NODE(); 

        auto bullet = GetScene().GetItem("bullet");
        auto prop   = GetScene().GetItem("prop");
        auto idt    = timer::interval([=](){ obj->b =! obj->b; },100);
        auto idy    = timer::interval([=](){ 

            if( !prop.GetAttr("append").has_value() ){ return; }

            prop_t item1; item1.pos = { 
                obj->pos.x + 16 * cos( ( obj->ang + 120 ) * DEG2RAD ), 
                obj->pos.y + 16 * sin( ( obj->ang + 120 ) * DEG2RAD )
            };  item1.angle = obj->ang + 15;

            prop_t item2; item2.pos = { 
                obj->pos.x + 16 * cos( ( obj->ang + 60 ) * DEG2RAD ), 
                obj->pos.y + 16 * sin( ( obj->ang + 60 ) * DEG2RAD )
            };  item2.angle = obj->ang - 15;

            prop.GetAttr("append").as<function_t<void,prop_t>>()(item1);
            prop.GetAttr("append").as<function_t<void,prop_t>>()(item2);

        }, 30 );

        self->onDraw([=](){
            float x = type::cast<float>(obj->b) * 64;
            DrawTexturePro( 
                obj->img, { x, 0, 64, 64 }, 
                obj->pos, { 16, 20 }, obj->ang, WHITE 
            );
        });

        self->onLoop([=]( float delta ){

              if( IsKeyDown( 'W' ) ){ obj->pos.y -= delta * obj->spd; }
            elif( IsKeyDown( 'S' ) ){ obj->pos.y += delta * obj->spd; }
              if( IsKeyDown( 'A' ) ){ obj->pos.x -= delta * obj->spd; }
            elif( IsKeyDown( 'D' ) ){ obj->pos.x += delta * obj->spd; }

            obj->ang = atan2( 
                ( GetMouseY() - obj->pos.y ), 
                ( GetMouseX() - obj->pos.x )
            ) * RAD2DEG + 90;

            auto aim = bullet.GetAttr("aim"); if( aim.has_value() ){ 
                aim.as<function_t<void,Vector2,float>>()( 
                    { obj->pos.x, obj->pos.y }, obj->ang  
                );
            }

        });

        self->onRemove([=](){
            if( IsTextureReady( obj->img ) ){ UnloadTexture( obj->img ); }
            timer::clear( idy ); timer::clear( idt ); prop.close();
        });

    }

}}