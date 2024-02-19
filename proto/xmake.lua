add_requires( "protobuf-cpp" )
add_requires( "zmqpb master" )

target( "Proto-Messages" )
    --set_kind( "static" )
    set_kind( "shared" )
    add_rules( "utils.symbols.export_all", { export_classes = true } )

    add_packages( "protobuf-cpp", { public = true } )
    add_packages( "zmqpb", { public = true } )

    add_rules( "protobuf.cpp" )

    add_files( "SFG/*.proto", { proto_public = true } )
