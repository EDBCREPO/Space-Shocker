#pragma once

namespace rl { namespace game {

    struct bullet_t {
        Vector2 pos = { 0, 0 };
        float speed = 500.0f;
        float angle = 0.0f;
    };  

    void bullet( ptr_t<Item> self ) {

        struct NODE {
            Texture img = LoadTexture( "Assets/sprites/effect/bala.png" );
            Vector2 pos[2] = { { 0, 0 }, { 0, 0 } };
            queue_t<bullet_t> bullet;
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

        self->onLoop([=]( float delta ){ [=](){
        coStart

            if( IsMouseButtonDown(0) ){ 
                coDelay(100); do {

                    bullet_t bullet1; 
                    bullet1.angle = obj->angle-90;
                    bullet1.pos   = obj->pos[0];
                    obj->bullet.push( bullet1 );

                    bullet_t bullet2; 
                    bullet2.angle = obj->angle-90;
                    bullet2.pos   = obj->pos[1];
                    obj->bullet.push( bullet2 );

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
        
        });

        self->onDraw([=](){
          //DrawCircleV( obj->pos[0], obj->size, WHITE );
          //DrawCircleV( obj->pos[1], obj->size, WHITE );
            auto x = obj->bullet.first(); while( x!=nullptr ){
                DrawCircleV( x->data.pos, 5, YELLOW );
                x = x->next;
            }
        });

        self->onRemove([=](){
            if( IsTextureReady( obj->img ) ){ UnloadTexture( obj->img ); }
        });

    }

}}