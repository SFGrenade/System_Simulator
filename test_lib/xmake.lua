target( "Test-Lib" )
    set_kind( "static" )

    set_default( false )
    set_group( "LIBS" )

    add_deps( "Logger", { public = true } )
    add_deps( "Network-Messages", { public = true } )

    add_includedirs( "include", { public = true } )

    add_headerfiles( "include/(SFG/SystemSimulator/TestLib/*.h)" )

    add_files( "src/*.cpp" )
    remove_files( "src/main.cpp" )

target( "Test-Lib-Exe" )
    set_kind( "binary" )

    set_default( true )
    set_group( "EXES" )

    add_deps( "Test-Lib", { public = true } )

    add_files( "src/main.cpp" )

    after_build( function ( target )
        import( "core.project.config" )
        os.cp( path.join( "$(scriptdir)", "config" ), path.join( "$(projectdir)", target.targetdir( target ) ) )
    end )
    after_install( function ( target )
        import( "core.project.config" )
        os.cp( path.join( "$(scriptdir)", "config" ), target.installdir( target ) )
    end )

target( "Test-Lib-Test" )
    set_kind( "binary" )

    set_default( false )
    set_group( "TESTS" )

    add_deps( "Test-Lib", { public = true } )
    add_deps( "Logger", { public = true } )
    add_packages( "gtest", { public = true } )

    add_files( "test/*.cpp" )
