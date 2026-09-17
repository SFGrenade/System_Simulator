-- required
add_requires( "boost" )
-- for resampling
add_requires( "soxr" )
-- for hardware IO
add_requires( "portaudio" )
--add_requires( "alsa-lib" )
--add_requires( "jack2" )
--add_requires( "pulseaudio" )
--add_requires( "pipewire" )

add_requireconfs( "boost", { configs = { header_only = true, asio = true, system = true } } )
-- because this otherwise uses MT and we have MD
--add_requireconfs( "portaudio", { configs = { shared = true } } )
----add_requireconfs( "alsa-lib", { configs = { shared = true } } )
----add_requireconfs( "jack2", { configs = { shared = true } } )
----add_requireconfs( "pulseaudio", { configs = { shared = true } } )
----add_requireconfs( "pipewire", { configs = { shared = true } } )

target( "Audio-Interface" )
    set_kind( "static" )

    set_default( false )
    set_group( "LIBS" )

    add_packages( "boost", { public = true } )
    add_packages( "soxr", { public = true } )
    add_packages( "portaudio", { public = true } )
    --add_packages( "alsa-lib", { public = true } )
    --add_packages( "jack2", { public = true } )
    --add_packages( "pulseaudio", { public = true } )
    --add_packages( "pipewire", { public = true } )

    add_deps( "Configuration", { public = true } )
    add_deps( "Logger", { public = true } )
    add_deps( "Network-Messages", { public = true } )

    add_includedirs( "include", { public = true } )

    add_headerfiles( "include/(SFG/SystemSimulator/AudioInterface/*.h)" )

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

target( "Audio-Interface-Test" )
    set_kind( "binary" )

    set_default( false )
    set_group( "TESTS" )

    add_deps( "Audio-Interface", { public = true } )
    add_deps( "Logger", { public = true } )
    add_packages( "gtest", { public = true } )

    add_files( "test/*.cpp" )
