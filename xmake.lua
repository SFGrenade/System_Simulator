set_project( "System_Simulator" )

set_version( "0.0.1", { build = "%Y%m%d", soname = true } )

add_rules( "mode.debug", "mode.release", "mode.releasedbg", "mode.minsizerel" )
add_rules( "plugin.compile_commands.autoupdate", { outputdir = ".vscode" } )


if is_plat( "windows" ) then
    set_languages( "cxx17" )

    add_cxflags( "/Zc:__cplusplus" )
    add_cxflags( "/Zc:preprocessor" )

    add_cxflags( "/permissive-" )

    -- MD required because Qt
    -- MDd somehow breaks installation of packages lol
    --set_runtimes( is_mode( "debug" ) and "MDd" or "MD" )
    set_runtimes( is_mode( "debug" ) and "MDd" or "MD" )
else
    set_languages( "c++17" )
end

set_warnings( "allextra" )

-- maybe this helps for the ci?
set_policy("build.across_targets_in_parallel", false)

add_repositories( "testing-repo https://github.com/SFGrenade/NetworkingHelpers-xmake-repo.git" )

-- test framework, gonna be added to each test
add_requires( "gtest" )

add_requireconfs( "*", { configs = { shared = get_config( "kind" ) == "shared" } } )

includes( "audio_interface" )
includes( "configuration" )
includes( "logger" )
includes( "login_server" )
includes( "network_messages" )
includes( "recording_server" )
includes( "settings_interface" )
