#pragma once

/*────────────────────────────────────────────────────────────────────────────*/

namespace rl { namespace game {

    struct item_t {
        Color    col;
        Texture* img;
        Vector2  dir;
        Vector2  pos;
        float   size;
        float  speed;
        bool   state;
    };

    void item( ptr_t<Item> self ){

        struct NODE {
            Texture img1 = LoadTexture( "assets/sprites/effect/recarga.png" ); 
            Texture img2 = LoadTexture( "assets/sprites/effect/vida.png" ); 
            queue_t<item_t> particle, init, list;
        };  ptr_t<NODE> obj = new NODE();

    /*.........................................................................*/

        auto player = GetScene().GetItem("player");

    /*.........................................................................*/

        self->onLoop([=]( float delta ){
            auto x = obj->particle.first(); while( x!=nullptr ){
            auto y = x->next;
                if ( x->data.size < 0 ){ goto DONE; } 
                x->data.size -= delta * x->data.speed; x = y; 
                continue; DONE:; obj->particle.erase(x); x = y;
            }
        });

    /*.........................................................................*/

        self->onLoop([=]( float delta ){
            auto x = obj->init.first(); while( x!=nullptr ){
            auto y = x->next;
                if ( x->data.size < 0 ){ goto DONE; } 
                x->data.size -= delta * x->data.speed; x = y; 
                continue; DONE:; obj->init.erase(x);   x = y;
            }
        });

    /*.........................................................................*/

        self->onLoop([=]( float delta ){[=](){
            static bool b = rand() % 2 == 0;
        coStart; coDelay(30000); do { item_t item;
            while( obj->list.size() > 5 ){ coNext; }

            item.state = b; item.speed = 100.0f; b =! b;
            item.img = item.state ? &obj->img1 : &obj->img2;

            item.pos = { 
                type::cast<float>( rand() % GetRenderWidth()  ), 
                type::cast<float>( rand() % GetRenderHeight() ) 
            };

            item.dir = { 
                type::cast<float>( rand() % 2==0 ? -1 : 1 ), 
                type::cast<float>( rand() % 2==0 ? -1 : 1 ) 
            };

            item_t part; part.state = 1; part.speed = 50.0f;
                   part.pos = item.pos;  part.size  = 30.0f;
                   part.col = item.state ? GREEN : RED;

            obj->init.push( part ); obj->list.push( item );
            
        } while(0); coStop
        }();});

    /*.........................................................................*/

        self->onLoop([=]( float delta ){
            auto p = player.GetAttr("getPos").as<function_t<Vector2>>()();
            auto x = obj->list.first(); while( x!=nullptr ){
            auto y = x->next;
                
                  if( x->data.pos.y > GetRenderHeight() ){ x->data.dir.y =-1; }
                elif( x->data.pos.y < 0 )                { x->data.dir.y = 1; }

                  if( x->data.pos.x > GetRenderWidth() ){ x->data.dir.x =-1; }
                elif( x->data.pos.x < 0 )               { x->data.dir.x = 1; }

                x->data.pos.x += x->data.dir.x * x->data.speed * delta;
                x->data.pos.y += x->data.dir.y * x->data.speed * delta;

                if ( CheckCollisionCircles( p, 20, x->data.pos, 20 )){ 
                    player.GetAttr("recharge").as<function_t<void,bool>>()(
                        x->data.state    
                    ); console::log("collided"); goto DONE; 
                }

                x = y; continue; DONE:; obj->list.erase(x); x = y;
            }

        });

    /*.........................................................................*/

        self->onLoop([=]( float delta ){[=](){
        coStart; coDelay(100); do { static bool b = 0;
            auto x = obj->list.last(); while( x!=nullptr ){
                item_t item; item.state = b; item.speed = 50.0f;
                item.pos = x->data.pos; item.size = 20.0f;
                item.col = x->data.state ? GREEN : RED;
                obj->particle.push( item ); x = x->prev;
            }   b =! b;
        } while(0); coStop
        }();});

    /*.........................................................................*/

        self->onDraw([=](){
            auto x = obj->init.first(); while( x!=nullptr ){
                DrawCircleLines( x->data.pos.x, x->data.pos.y, x->data.size, x->data.col );
                x = x->next;
            }
        });

        self->onDraw([=](){
            auto x = obj->particle.first(); while( x!=nullptr ){
                  if ( x->data.state == 1 )
                     { DrawRectangle( x->data.pos.x, x->data.pos.y, x->data.size, x->data.size, x->data.col ); }
                else { DrawRectangleLines( x->data.pos.x, x->data.pos.y, x->data.size, x->data.size, x->data.col ); }
                x = x->next;
            }
        });

        self->onDraw([=](){
            auto x = obj->list.first(); while( x!=nullptr ){
                DrawTexturePro(
                     *x->data.img, { 0, 0, 16, 16 }, 
                    { x->data.pos.x, x->data.pos.y, 32, 32 }, 
                    { 8, 8 }, 0, WHITE
                ); x = x->next;
            }
        });

    /*.........................................................................*/

        self->onRemove([=](){
            if( IsTextureReady( obj->img2 ) ){ UnloadTexture( obj->img2 ); }
            if( IsTextureReady( obj->img1 ) ){ UnloadTexture( obj->img1 ); } 
        });

    }

}}

/*────────────────────────────────────────────────────────────────────────────*/