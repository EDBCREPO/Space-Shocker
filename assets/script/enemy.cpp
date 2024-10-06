#pragma once

/*────────────────────────────────────────────────────────────────────────────*/

namespace rl { namespace game {

    void enemy( ptr_t<Item> self ) {

        struct NODE {
            Rectangle pos = { GetRenderWidth()*0.5f, GetRenderHeight()*0.5f, 300, 300 };
            Texture   img = LoadTexture( "assets/sprites/enemy/estados.png" ); 
            float   speed = 300.0f;
            float  health = 1000;
            Vector2   dir;
        };  ptr_t<NODE> obj = new NODE();

        auto player = GetScene().GetItem("player");

        obj->dir = { 
            type::cast<float>( rand() % 2==0 ? -1 : 1 ), 
            type::cast<float>( rand() % 2==0 ? -1 : 1 ) 
        };

    /*.........................................................................*/

        self->SetAttr("setHealth",function_t<void,float>([=]( float value ){ 
            obj->health = value * 1000.0f; 
        }));

        self->SetAttr("getHealth",function_t<float>([=](){ 
            return obj->health / 1000.0f; 
        }));

        self->SetAttr("hurt",function_t<void>([=](){ 
            obj->health -= 1.0f; 
        }));

    /*.........................................................................*/

        self->onLoop([=]( float delta ){
                
              if( obj->pos.y > GetRenderHeight() ){ obj->dir.y =-1; }
            elif( obj->pos.y < 0 )                { obj->dir.y = 1; }

              if( obj->pos.x > GetRenderWidth() ){ obj->dir.x =-1; }
            elif( obj->pos.x < 0 )               { obj->dir.x = 1; }

            obj->pos.x += obj->dir.x * obj->speed * delta;
            obj->pos.y += obj->dir.y * obj->speed * delta;

        });

    /*.........................................................................*/

        self->onLoop([=]( float delta ){ if( !player.HasAttr("bullet") ){ return; }

            auto bullet = player.GetAttr("bullet").as<function_t<queue_t<bullet_t>>>();
            auto sos    = player.GetAttr("setPos").as<function_t<void,Vector2>>();
            auto gos    = player.GetAttr("getPos").as<function_t<Vector2>>();
            auto hrt    = player.GetAttr("hurt").as<function_t<void>>();

            auto x = bullet().first(); while( x != nullptr ){
                if( CheckCollisionCircles( x->data.pos, 3, { obj->pos.x, obj->pos.y }, 90 ) )
                  { x->data.size = 0; obj->health--; } x = x->next;
            }

            if( CheckCollisionCircles( gos(), 20, { obj->pos.x, obj->pos.y }, 90 ) ){
                hrt(); console::log("hit!");
            }

        });

    /*.........................................................................*/

        self->onDraw([=](){ DrawTexturePro(
            obj->img, { 64, 0, 64, 64 },
            obj->pos, { 150, 150 }, 0, WHITE
        );});

    }

}}

/*────────────────────────────────────────────────────────────────────────────*/