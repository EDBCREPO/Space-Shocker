#pragma once

namespace rl { namespace game {

    struct prop_t {
        Vector2 pos = { 0, 0 };
        float speed = 50.0f;
        float size  = 15.0f;
        float angle = 0.0f;
    };

    void prop( ptr_t<Item> self ) {

        struct NODE {
            Texture img = LoadTexture( "Assets/sprites/effect/prop.png" );
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

        self->onDraw([=](){
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