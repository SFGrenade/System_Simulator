--add_requires( "fmt" )
add_requires( "spdlog" )

add_requireconfs( "spdlog", { configs = { fmt_external_ho = true } } )

target( "Logger" )
    set_kind( "static" )

    set_default( false )
    set_group( "LIBS" )

    --add_packages( "fmt", { public = true } )
    add_packages( "spdlog", { public = true } )

    add_includedirs( "include", { public = true } )

    add_headerfiles( "include/(SFG/SystemSimulator/Logger/*.h)" )

    add_files( "src/Logger/*.cpp" )
    remove_files( "src/main.cpp" )

target( "Logger-Qt" )
    add_rules("qt.static")

    set_default( false )
    set_group( "LIBS" )

    add_deps( "Logger", { public = true } )

    add_includedirs( "include", { public = true } )

    add_headerfiles( "include/(SFG/SystemSimulator/Logger-Qt/*.h)" )

    add_files( "src/Logger-Qt/*.cpp" )
    remove_files( "src/main.cpp" )

    add_frameworks( "QtCore" )

for _, file in ipairs( os.files( "test/*.cpp" ) ) do
    local name = path.basename( file )
    target( name )
        set_kind( "binary" )
        set_default( false )
        set_group( "TESTS" )
        add_deps(  "Logger", { public = true } )
        add_deps(  "Logger-Qt", { public = true } )
        add_files( "test/" .. name .. ".cpp" )
        add_tests( "default" )
end
