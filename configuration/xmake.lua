add_requires( "simpleini" )

target( "Configuration" )
    set_kind( "static" )
    --set_kind( "shared" )
    --add_rules( "utils.symbols.export_all", { export_classes = true } )

    add_packages( "simpleini", { public = true } )

    add_includedirs( "include", { public = true } )

    add_headerfiles( "include/SFG/SystemSimulator/Configuration/*.h" )

    add_files( "src/*.cpp" )
    remove_files( "src/main.cpp" )

    after_build( function ( target )
        import( "core.project.config" )
        os.cp( path.join( "$(scriptdir)", "config" ), path.join( "$(projectdir)", target.targetdir( target ) ) )
    end )
    after_install( function ( target )
        import( "core.project.config" )
        os.cp( path.join( "$(scriptdir)", "config" ), target.installdir( target ) )
    end )

for _, file in ipairs( os.files( "test/*.cpp" ) ) do
    local name = path.basename( file )
    target( name )
        set_kind( "binary" )
        add_deps(  "Configuration", { public = true } )
        set_default( false )
        add_files( "test/" .. name .. ".cpp" )
        add_tests( "default" )
end
