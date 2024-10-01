#include <nodepp/nodepp.h>
#include <nodepp/fs.h>

using namespace nodepp;

void onMain(){

    auto file = fs::readable( "main.cpp" );

    file.onData([]( string_t data ){
        ptr_t<uchar> bff ( data.size() );
        memcpy( &bff, data.get(), data.size() );
        for( auto& x: bff ){ console::log( "->", (char)x, x ); }
    });

    stream::line( file );

}