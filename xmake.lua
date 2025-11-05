add_rules("mode.debug", "mode.release")

add_repositories("levimc-repo https://github.com/LiteLDev/xmake-repo.git")

-- add_requires("levilamina x.x.x") for a specific version
-- add_requires("levilamina develop") to use develop version
-- please note that you should add bdslibrary yourself if using dev version
if is_config("target_type", "server") then
    add_requires("levilamina 1.7.0", {configs = {target_type = "server"}})
else
    add_requires("levilamina 1.4.1", {configs = {target_type = "client"}})
end

add_requires("levibuildscript")

if not has_config("vs_runtime") then
    set_runtimes("MD")
end

option("target_type")
    set_default("server")
    set_showmenu(true)
    set_values("server", "client")
option_end()

option("test")
    set_default(false)
    set_showmenu(true)
option_end()


target("DebugShape") -- Change this to your mod name.
    add_rules("@levibuildscript/linkrule")
    add_rules("@levibuildscript/modpacker")
    add_cxflags( "/EHa", "/utf-8", "/W4", "/w44265", "/w44289", "/w44296", "/w45263", "/w44738", "/w45204")
    add_defines("NOMINMAX", "UNICODE")
    add_packages("levilamina")
    set_exceptions("none") -- To avoid conflicts with /EHa.
    set_kind("shared")
    set_languages("c++20")
    set_symbols("debug")
    add_headerfiles("src/(debug_shape/api/**.h)")
    add_files("src/**.cpp", "src/**.cc")
    add_includedirs("src", "include")

    if has_config("test") then
        add_defines("DS_TEST")
        add_includedirs("tests")
        add_files("tests/**.cc")
    end

    if is_plat("windows") then
        add_cxxflags("/wd4250", {force = true}) -- ignore warning C4250
    end