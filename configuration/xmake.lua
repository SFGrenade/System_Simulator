add_requires( "simpleini" )

-- because this otherwise uses MT and we have MD
--add_requireconfs( "simpleini", { configs = { shared = true } } )

target( "Configuration" )
    set_kind( "static" )
    --set_kind( "shared" )
    --add_rules( "utils.symbols.export_all", { export_classes = true } )

    add_packages( "simpleini", { public = true } )

    add_includedirs( "include", { public = true } )

    add_headerfiles( "include/SFG/SystemSimulator/Configuration/*.h" )

    add_files( "src/*.cpp" )

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
        add_deps(  "Configuration"  )
        set_default( false )
        add_files( "test/" .. name .. ".cpp" )
        add_tests( "default" )
end
