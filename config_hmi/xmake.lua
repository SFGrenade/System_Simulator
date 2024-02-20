add_requires( "fmt" )
add_requires( "spdlog" )
add_requires( "simpleini" )

add_requireconfs( "spdlog", { configs = { fmt_external = true } } )

target( "Config-HMI" )
    add_rules("qt.widgetapp")

    add_packages( "fmt" )
    add_packages( "spdlog" )
    add_packages( "simpleini" )

    add_deps( "Proto-Messages" )

    add_includedirs( "include" )

    add_headerfiles( "include/*.h" )
    add_files( "include/mainWindow.h" ) -- add files with Q_OBJECT meta (only for qt.moc)

    add_files( "src/*.cpp" )

    add_frameworks( "QtCore", "QtGui", "QtWidgets" )

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
        add_deps(  "Config-HMI"  )
        set_default( false )
        add_files( "test/" .. name .. ".cpp" )
        add_tests( "default" )
end
