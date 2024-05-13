project "CalcGUI"
    kind "WindowedApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"

    targetdir("../bin/" .. outputdir .. "/%{prj.name}")
    objdir("../binint/" .. outputdir .. "/%{prj.name}")

    files {
        "include/**.h",
        "src/**.cpp",
        "vendor/imgui/*.cpp",
        "vendor/imgui/*.h",
        "vendor/imgui/backends/imgui_impl_opengl3.h",
        "vendor/imgui/backends/imgui_impl_opengl3.cpp",
        "vendor/imgui/misc/debuggers/imgui.natvis",
        "vendor/imgui/misc/debuggers/imgui.natstepfilter",
        "vendor/imgui/misc/cpp/imgui_stdlib.*"
    }

    includedirs {
        "include",
        "vendor/imgui",
        "vendor/imgui/backends",
        "vendor/imgui/misc/cpp/",
    }

    filter { "configurations:Debug" }
        buildoptions "/MTd"
        runtime "Debug"
        symbols "on"

    filter { "configurations:Release" }
        buildoptions "/MT"
        runtime "Release"
        symbols "off"
        optimize "on"