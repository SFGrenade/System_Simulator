add_requires( "portaudio" )
add_requires( "simpleini" )

-- because this otherwise uses MT and we have MD
--add_requireconfs( "portaudio", { configs = { shared = true } } )

target( "Audio-Interface" )
    set_kind("binary")

    add_packages( "portaudio" )
    add_packages( "simpleini" )

    add_deps( "Logger" )
    add_deps( "Proto-Messages" )

    add_includedirs( "include", { public = true } )

    add_headerfiles( "include/SFG/SystemSimulator/AudioInterface/*.h" )

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
        add_deps(  "Audio-Interface"  )
        set_default( false )
        add_files( "test/" .. name .. ".cpp" )
        add_tests( "default" )
end
