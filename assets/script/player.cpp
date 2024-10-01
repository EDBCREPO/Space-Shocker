#pragma once

/*────────────────────────────────────────────────────────────────────────────*/

namespace rl { namespace game {

    void player_power( ptr_t<Item> self, ptr_t<Item> player ){

        auto sos = player->GetAttr("setPos").as<function_t<void,Vector2>>();
        auto gos = player->GetAttr("getPos").as<function_t<Vector2>>();
        auto imv = player->GetAttr("isMoving").as<function_t<bool>>();
        auto tlp = player->GetAttr("Teleport").as<function_t<void>>();

        struct NODE {
            Texture rec1 = LoadTexture( "assets/sprites/effect/recAn1.png" );
            Texture rec2 = LoadTexture( "assets/sprites/effect/recAn2.png" );
            float frame  = 0.0f;
            bool      b  = 0;
        };  ptr_t<NODE> obj = new NODE();

        player->onDraw([=](){
            if( !obj->b ){ return; } DrawTexturePro(
                obj->rec1, { obj->frame, 0, 64, 64 }, 
                { gos().x, gos().y, 80, 80 },
                { 40, 40 }, 0, WHITE
            );
        });

        self->onLoop([=]( float delta ){[=](){
            static uchar x = 1; 
        coStart

            while( !IsKeyDown(KEY_LEFT_SHIFT) || !imv() ){
                x = 1; obj->b = 0; coNext; 
            }   tlp();

            while( x != 0 ){
                obj->frame = 64 * ( x - 1 );
                x++; x %= 12; coDelay( 20 );
                obj->b = 1;
            }   

            while( IsKeyDown(KEY_LEFT_SHIFT) ){ coNext; }

        coStop
        }();});

        self->onRemove([=](){
            if( IsTextureReady(obj->rec1) ){ UnloadTexture( obj->rec1 ); }
            if( IsTextureReady(obj->rec2) ){ UnloadTexture( obj->rec2 ); }
        });

    }

}}

/*────────────────────────────────────────────────────────────────────────────*/

namespace rl { namespace game {

    struct bullet_t {
        Vector2 pos = { 0, 0 };
        float speed = 500.0f;
        float size  = 10.0f;
        float angle = 0.0f;
        bool  b = 0;
    };  

    void player_bullet( ptr_t<Item> self, ptr_t<Item> player ) {

        struct NODE {
            Texture img = LoadTexture( "assets/sprites/effect/bala.png" );
            Vector2 pos[2] = { { 0, 0 }, { 0, 0 } };
            queue_t<bullet_t> bullet;
            queue_t<bullet_t> flash;
            float size  = 3.0f;
            float angle = 0.0f;
            uchar type  = 0;
        };  ptr_t<NODE> obj = new NODE();

        self->SetAttr( "aim", function_t<void,Vector2,float>(
            [=]( Vector2 pos, float angle ){ obj->angle = angle;
                obj->pos[0].x = pos.x - 20 * cos( ( angle + 45 ) * DEG2RAD );
                obj->pos[0].y = pos.y - 20 * sin( ( angle + 45 ) * DEG2RAD );
                obj->pos[1].x = pos.x - 20 * cos( ( angle +135 ) * DEG2RAD );
                obj->pos[1].y = pos.y - 20 * sin( ( angle +135 ) * DEG2RAD );
            })
        );

        self->onLoop([=]( float delta ){[=](){
            static bool b = 0; 
        coStart

            if( IsMouseButtonDown(0) ){ 
                coDelay(100); do {

                    bullet_t bullet1; 
                    bullet1.angle = obj->angle-90;
                    bullet1.pos   = obj->pos[0];
                    obj->bullet.push( bullet1 );

                    bullet_t flash1;
                    flash1.b     = b;
                    flash1.speed = 40.0f;
                    flash1.pos   = obj->pos[0];
                    obj->flash.push( flash1 );

                    bullet_t bullet2; 
                    bullet2.angle = obj->angle-90;
                    bullet2.pos   = obj->pos[1];
                    obj->bullet.push( bullet2 );

                    bullet_t flash2;
                    flash2.b     = b;
                    flash2.speed = 40.0f;
                    flash2.pos   = obj->pos[1];
                    obj->flash.push( flash2 );

                    b =! b;

                } while(0);
            }

        coStop
        }();});

        self->onLoop([=]( float delta ){
            
            auto x = obj->bullet.first(); while( x!=nullptr ){
            auto y = x->next;
            
                  if( x->data.pos.x > GetRenderWidth()  + 10 ){ goto DONE; }
                elif( x->data.pos.y > GetRenderHeight() + 10 ){ goto DONE; }
                elif( x->data.pos.x < -10 ){ goto DONE; }
                elif( x->data.pos.y < -10 ){ goto DONE; } 

                x->data.pos.x += delta * x->data.speed * cos( x->data.angle * DEG2RAD );
                x->data.pos.y += delta * x->data.speed * sin( x->data.angle * DEG2RAD );

                x = y; continue; DONE:; obj->bullet.erase(x); x = y;
            }

            auto y = obj->flash.first(); while( y!=nullptr ){
            auto x = y->next;

                if( y->data.size < 0 ){ goto NODE; }

                y->data.size -= delta * y->data.speed;

                y = x; continue; NODE:; obj->flash.erase(y); y = x;
            }
        
        });

        player->onDraw([=](){

            auto x = obj->bullet.first(); while( x!=nullptr ){
                DrawTexturePro( obj->img, { 0, 0, 32, 32 }, 
                    { x->data.pos.x, x->data.pos.y, 20, 20 },
                    { 10, 10 }, x->data.angle, WHITE 
                );  x = x->next;
            }

            auto y = obj->flash.first(); while( y!=nullptr ){
                if( y->data.b )
                  { DrawCircleV( y->data.pos, y->data.size, YELLOW ); }
                else 
                  { DrawCircleLinesV( y->data.pos, y->data.size, YELLOW ); }
                y = y->next;
            }

        });

        self->onRemove([=](){
            if( IsTextureReady( obj->img ) ){ UnloadTexture( obj->img ); }
        });

    }

}}

/*────────────────────────────────────────────────────────────────────────────*/

namespace rl { namespace game {

    struct prop_t {
        Vector2 pos = { 0, 0 };
        float speed = 70.0f;
        float size  = 15.0f;
        float angle = 0.0f;
    };

    void player_prop( ptr_t<Item> self, ptr_t<Item> player ) {

        struct NODE {
            Texture img = LoadTexture( "assets/sprites/effect/prop.png" );
            queue_t<prop_t> list;
        };  ptr_t<NODE> obj = new NODE();

        self->SetAttr( "append", function_t<void,prop_t>([=]( prop_t arg ){
            obj->list.push( arg );
        }));

        self->onLoop([=]( float delta ){
            auto x = obj->list.first(); while( x!=nullptr ){ auto y = x->next;
                if ( x->data.size <= 0 ){ obj->list.erase( x ); goto END; }
                     x->data.size -= delta * x->data.speed;
                END:; x = y;
            }
        });

        player->onDraw([=](){
            auto x = obj->list.first(); while( x!=nullptr ){
                DrawTexturePro(
                    obj->img, { 0, 0, 16, 16 }, 
                    { x->data.pos.x, x->data.pos.y, x->data.size, x->data.size }, 
                    { 8, 8 }, x->data.angle, WHITE 
                );  x = x->next;
            }
        });

        self->onRemove([=](){
            if( IsTextureReady( obj->img ) ){ UnloadTexture( obj->img ); }
        });

    }

}}

/*────────────────────────────────────────────────────────────────────────────*/

namespace rl { namespace game {

    void player( ptr_t<Item> self ) {

        struct NODE {
            Rectangle pos = { GetRenderWidth()*0.5f, GetRenderHeight()*0.5f, 32, 32 };
            Texture   img = LoadTexture( "assets/sprites/player/player.png" );
            Vector2   dir = { 0, 0 };
            bool    ismov = false;
            float     spd = 300;
            float     ang = 0;
            bool        b = 0;
        };  ptr_t<NODE> obj = new NODE();

        self->SetAttr("setPos",function_t<void,Vector2>([=]( Vector2 pos ){ 
            obj->pos.x = pos.x; obj->pos.y = pos.y;
        }));

        self->SetAttr("Teleport",function_t<void>([=](){
            obj->pos.x += obj->dir.x * 100;
            obj->pos.y += obj->dir.y * 100;
            console::log("teleported");
        }));

        self->SetAttr("isMoving",function_t<bool>([=](){
            return obj->ismov;
        }));

        self->SetAttr("getPos",function_t<Vector2>([=](){ 
            return Vector2({ obj->pos.x, obj->pos.y }); 
        }));

        Item prop   ( player_prop, self );
        Item power  ( player_power, self );
        Item bullet ( player_bullet, self );

        self->onDraw([=](){
            float x = type::cast<float>(obj->b) * 64;
            DrawTexturePro( 
                obj->img, { x, 0, 64, 64 }, 
                obj->pos, { 16, 20 }, obj->ang, WHITE 
            );
        });

        auto idt = timer::interval([=](){ obj->b =! obj->b; },100);

        self->onLoop([=]( float delta ){[=](){
        coStart; coDelay(30);
            
            if( !prop.GetAttr("append").has_value() ){ coEnd; }

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

        coStop
        }();});

        self->onLoop([=]( float delta ){ obj->ismov=0;
            
            obj->pos.x += obj->dir.x*delta*obj->spd; 
            obj->pos.y += obj->dir.y*delta*obj->spd;

              if( IsKeyDown( 'W' ) ){ obj->dir.y =-1; obj->ismov=1; }
            elif( IsKeyDown( 'S' ) ){ obj->dir.y = 1; obj->ismov=1; }
            else                    { obj->dir.y = 0; }

              if( IsKeyDown( 'A' ) ){ obj->dir.x =-1; obj->ismov=1; }
            elif( IsKeyDown( 'D' ) ){ obj->dir.x = 1; obj->ismov=1; }
            else                    { obj->dir.x = 0; }

            auto aim = bullet.GetAttr("aim"); if( aim.has_value() ){ 
                aim.as<function_t<void,Vector2,float>>()( 
                    { obj->pos.x, obj->pos.y }, obj->ang  
                );
            }

            obj->ang = atan2(
                ( GetMouseY()-obj->pos.y ),
                ( GetMouseX()-obj->pos.x )
            ) * RAD2DEG + 90;

        });

        self->onRemove([=](){
            if( IsTextureReady( obj->img ) )
              { UnloadTexture( obj->img ); }
                timer::clear( idt ); 
                prop.close();
        });

    }

}}

/*────────────────────────────────────────────────────────────────────────────*/