add_requires( "portaudio" )

-- because this otherwise uses MT and we have MD
--add_requireconfs( "portaudio", { configs = { shared = true } } )

target( "Audio-Interface" )
    set_kind( "static" )
    --set_kind( "shared" )
    --add_rules( "utils.symbols.export_all", { export_classes = true } )

    set_default( false )
    set_group( "LIBS" )

    add_packages( "portaudio", { public = true } )

    add_deps( "Configuration", { public = true } )
    add_deps( "Logger", { public = true } )
    add_deps( "Proto-Messages", { public = true } )

    add_includedirs( "include", { public = true } )

    add_headerfiles( "include/SFG/SystemSimulator/AudioInterface/*.h" )

    add_files( "src/*.cpp" )
    remove_files( "src/main.cpp" )

target( "Audio-Interface-Exe" )
    set_kind( "binary" )

    set_default( true )
    set_group( "EXES" )

    add_deps( "Audio-Interface", { public = true } )

    add_files( "src/main.cpp" )

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
        set_default( false )
        set_group( "TESTS" )
        add_deps(  "Audio-Interface", { public = true } )
        add_deps( "Logger", { public = true } )
        add_files( "test/" .. name .. ".cpp" )
        add_tests( "default" )
end
