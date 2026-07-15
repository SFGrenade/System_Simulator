add_requires( "cpp-httplib" )
add_requires( "libui" )
add_requires( "reflect-cpp" )

add_requireconfs( "cpp-httplib", { configs = { ssl = true, zlib = true } } )
add_requireconfs( "reflect-cpp", { configs = { xml = true, ubjson = true, shared = false } } )

target( "Luigi-Interface" )
    set_kind( "static" )

    set_default( false )
    set_group( "LIBS" )

    add_deps( "Configuration", { public = true } )
    add_deps( "Logger", { public = true } )
    add_deps( "Network-Messages", { public = true } )

    add_packages( "cpp-httplib", { public = true } )
    add_packages( "libui", { public = true } )
    add_packages( "reflect-cpp", { public = true } )

    add_includedirs( "include", { public = true } )

    add_headerfiles( "include/(SFG/SystemSimulator/LuigiInterface/*.h)" )
    add_headerfiles( "include/(SFG/SystemSimulator/LuigiInterface/Models/*.h)" )
    add_headerfiles( "include/(SFG/SystemSimulator/LuigiInterface/UI/*.h)" )

    add_files( "src/*.cpp" )
    add_files( "src/Models/*.cpp" )
    add_files( "src/UI/*.cpp" )
    remove_files( "src/main.cpp" )

target( "Luigi-Interface-Exe" )
    set_kind( "binary" )

    set_default( true )
    set_group( "EXES" )

    add_deps( "Luigi-Interface", { public = true } )

    add_files( "src/main.cpp" )

    if is_plat( "windows" ) then
        -- https://stackoverflow.com/a/43432980
        add_files( "resources/Luigi-Interface-Exe.exe.manifest" )
    end

    after_build( function ( target )
        import( "core.project.config" )
        os.cp( path.join( "$(scriptdir)", "config" ), path.join( "$(projectdir)", target.targetdir( target ) ) )
    end )
    after_install( function ( target )
        import( "core.project.config" )
        os.cp( path.join( "$(scriptdir)", "config" ), target.installdir( target ) )
    end )
