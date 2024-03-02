add_requires( "protobuf-cpp" )
add_requires( "zmqpb master" )

target( "Proto-Messages" )
    set_kind( "static" )
    --set_kind( "shared" )
    --add_rules( "utils.symbols.export_all", { export_classes = true } )

    add_packages( "protobuf-cpp", { public = true } )
    add_packages( "zmqpb", { public = true } )

    add_rules( "protobuf.cpp" )

    add_files( "messages/*.proto", { proto_public = true } )

for _, file in ipairs( os.files( "test/*.cpp" ) ) do
    local name = path.basename( file )
    target( name )
        set_default( false )
        set_kind( "binary" )
        add_deps(  "Proto-Messages", { public = true } )
        add_deps( "Logger", { public = true } )
        add_files( "test/" .. name .. ".cpp" )
        add_tests( "default" )
end
