--add_requires( "fmt" )
add_requires( "spdlog" )

add_requireconfs( "spdlog", { configs = { fmt_external_ho = true } } )

target( "Logger" )
    set_kind( "static" )
    --set_kind( "shared" )
    --add_rules( "utils.symbols.export_all", { export_classes = true } )

    --add_packages( "fmt", { public = true } )
    add_packages( "spdlog", { public = true } )

    add_includedirs( "include", { public = true } )

    add_headerfiles( "include/SFG/SystemSimulator/Logger/*.h" )

    add_files( "src/*.cpp" )
    remove_files( "src/main.cpp" )

for _, file in ipairs( os.files( "test/*.cpp" ) ) do
    local name = path.basename( file )
    target( name )
        set_kind( "binary" )
        add_deps(  "Logger", { public = true } )
        add_files( "test/" .. name .. ".cpp" )
        add_tests( "default" )
end
