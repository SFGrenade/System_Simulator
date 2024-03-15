add_rules( "mode.debug", "mode.release" )
add_rules( "plugin.compile_commands.autoupdate", { outputdir = ".vscode" } )

set_project( "System_Simulator" )

if is_plat( "windows" ) then
    set_languages( "cxxlatest" )

    -- bruh
    --add_defines( "_WIN32_WINNT=0x0601" )

    add_cxflags( "/Zc:__cplusplus" )
    add_cxflags( "/Zc:preprocessor" )

    add_cxflags( "/permissive-" )

    -- MDd somehow breaks installation of packages lol
    --set_runtimes(is_mode("debug") and "MDd" or "MD")
    set_runtimes(is_mode("debug") and "MD" or "MD")
else
    set_languages( "cxx20" )
end

set_warnings( "allextra" )

if is_mode( "debug" ) then
    add_defines( "DEBUG" )
end
if is_mode( "release" ) then
    add_defines( "NDEBUG" )
end

-- maybe this helps for the ci?
set_policy("build.across_targets_in_parallel", false)

--add_repositories( "local-repo E:\\xmake_packages" )

add_requireconfs( "*", { configs = { shared = false } } )

includes( "audio_interface" )
includes( "configuration" )
includes( "logger" )
includes( "login_server" )
includes( "proto_messages" )
includes( "settings_interface" )
