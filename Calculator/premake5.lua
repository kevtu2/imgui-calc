project "Calculator"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"

targetdir("../bin/" .. outputdir .. "/%{prj.name}")
objdir("../binint/" .. outputdir .. "/%{prj.name}")

files {
    "include/**.h",
    "src/**.cpp"
}

includedirs { "include" }
defines {  }

filter { "configurations:Debug" }
    buildoptions "/MTd" -- Multi threaded debug DLL runtime library
    runtime "Debug"
    symbols "on"

filter { "configurations:Release" }
    buildoptions "/MT"
    runtime "Release"
    symbols "off"
    optimize "on"