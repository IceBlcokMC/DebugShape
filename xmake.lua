add_rules("mode.debug", "mode.release")

add_repositories("levimc-repo https://github.com/LiteLDev/xmake-repo.git")

-- add_requires("levilamina x.x.x") for a specific version
-- add_requires("levilamina develop") to use develop version
-- please note that you should add bdslibrary yourself if using dev version
if is_config("target_type", "server") then
    add_requires("levilamina 26.20.0", {configs = {target_type = "server"}})
else
    add_requires("levilamina 26.20.0", {configs = {target_type = "client"}})
end

add_requires("levibuildscript")

if has_config("addon") then 
    add_requires("jspp main")
end

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

option("addon")
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
    add_includedirs("src")

    if has_config("test") then
        add_defines("DS_TEST")
        add_includedirs("tests")
        add_files("tests/**.cc")
    end

    if is_plat("windows") then
        add_cxxflags("/wd4250", {force = true}) -- ignore warning C4250
    end

    if has_config("addon") then
        add_packages("jspp")
        add_defines("DS_ADDON")
        add_files("src-addon/**.cc")

        after_build(function (target) 
            local src_addon = os.projectdir().. "/src-addon"
            local bin_dir = os.projectdir().. "/bin"
            local bin_out_dir = bin_dir.. "/" .. target:name()
            local dts_file = src_addon.."/*.d.ts";
            os.cp(dts_file, bin_out_dir)
        end)
    end 

    if is_config("target_type", "server") then
        add_defines("LL_PLAT_S")
    else
        add_defines("LL_PLAT_C")
    end


package("jspp")
    set_urls("https://github.com/engsr6982/jspp.git")
    add_versions("2.0.0", "7ed577a4b7e0aa37cbf1bd23c86f148577082bae")

    add_deps("cmake")
    add_deps("quickjs-ng 0.13.0", { configs = { libc = true }, public = true })

    on_install(function (package)
        local configs = { "-DJSPP_BACKEND=quickjs" }

        local quickjs = package:dep("quickjs-ng")
        if quickjs then
            local installdir = quickjs:installdir()
            local incdir = path.join(installdir, "include")
            local libdir = path.join(installdir, "lib")

            table.insert(configs, "-DJSPP_EXTERNAL_INC=" .. incdir)
            table.insert(configs, "-DJSPP_EXTERNAL_LIB=" .. libdir)
        end

        import("package.tools.cmake").build(package, configs)

        local function install_headers(srcdir)
            for _, f in ipairs(os.files(path.join(srcdir, "**.h"))) do
                local rel = path.relative(f, srcdir)
                os.cp(f, path.join(package:installdir("include"), rel))
            end
            for _, f in ipairs(os.files(path.join(srcdir, "**.inl"))) do
                local rel = path.relative(f, srcdir)
                os.cp(f, path.join(package:installdir("include"), rel))
            end
        end
        install_headers("src")
        install_headers("src-quickjs")

        -- 安装库文件
        local libfiles
        if is_plat("windows") then
            libfiles = os.files("bin/**.lib")
        else
            libfiles = os.files("bin/**.a")
        end
        for _, libfile in ipairs(libfiles) do
            os.cp(libfile, package:installdir("lib"))
        end
    end)
package_end()