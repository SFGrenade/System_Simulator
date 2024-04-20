add_requires( "boost" )
add_requires( "boostnng" )

add_requireconfs( "boost", { configs = { serialization = true } } )
add_requireconfs( "boostnng", { configs = { shared = false } } )

target( "Network-Messages" )
    set_kind( "static" )

    set_default( false )
    set_group( "LIBS" )

    add_packages( "boost", { public = true } )
    add_packages( "boostnng", { public = true } )

    add_includedirs( "include", { public = true } )

    add_headerfiles( "include/(SFG/SystemSimulator/NetworkMessages/*.h)" )

    add_files( "src/*.cpp" )
    remove_files( "src/main.cpp" )

target( "Network-Messages-Test" )
    set_kind( "binary" )

    set_default( false )
    set_group( "TESTS" )

    add_deps( "Network-Messages", { public = true } )
    add_deps( "Logger", { public = true } )
    add_packages( "gtest", { public = true } )
    add_packages( "boostnng", { public = true } )

    add_files( "test/*.cpp" )
