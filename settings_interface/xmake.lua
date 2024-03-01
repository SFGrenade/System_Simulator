--add_requires( "simpleini" )

target( "Settings-Interface" )
    set_default( false )
    add_rules("qt.static")
    --add_rules("qt.shared")
    --add_rules( "utils.symbols.export_all", { export_classes = true } )

    --add_packages( "simpleini", { public = true } )

    add_deps( "Logger", { public = true } )
    add_deps( "Proto-Messages", { public = true } )

    add_includedirs( "include", { public = true } )

    add_headerfiles( "include/SFG/SystemSimulator/SettingsInterface/*.h" )
    add_files( "include/SFG/SystemSimulator/SettingsInterface/mainWindow.h" ) -- add files with Q_OBJECT meta (only for qt.moc)

    add_files( "src/*.cpp" )
    remove_files( "src/main.cpp" )

    add_frameworks( "QtCore", "QtGui", "QtWidgets" )

target( "Settings-Interface-Exe" )
    add_rules("qt.widgetapp")

    add_deps( "Settings-Interface", { public = true } )

    add_files( "src/main.cpp" )

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
        set_default( false )
        add_rules("qt.widgetapp")
        add_deps(  "Settings-Interface", { public = true } )
        add_files( "test/" .. name .. ".cpp" )
        add_tests( "default" )
        add_frameworks( "QtCore", "QtGui", "QtWidgets" )
end
