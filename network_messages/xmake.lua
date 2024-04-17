add_requires( "boost" )
add_requires( "nng" )

add_requireconfs( "boost", { configs = { serialization = true } } )

target( "Network-Messages" )
    set_kind( "static" )

    set_default( false )
    set_group( "LIBS" )

    add_packages( "boost", { public = true } )
    add_packages( "nng", { public = true } )

    --add_rules( "protobuf.cpp" )

    --add_files( "messages/*.proto", { proto_public = true } )

target( "Network-Messages-Test" )
    set_kind( "binary" )

    set_default( false )
    set_group( "TESTS" )

    add_deps( "Network-Messages", { public = true } )
    add_deps( "Logger", { public = true } )
    add_packages( "gtest", { public = true } )

    add_files( "test/*.cpp" )
