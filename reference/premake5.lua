project "PracticeProject" -- This time, we're in the specific project in our workspace and not the workspace itself.
    kind "ConsoleApp" -- What type of project it is. Is it a static library? Is it a console app? What is the project??
    language "C++" -- C# can also work with premake
    cppdialect "C++20" -- Specify C++ version.
    staticruntime "on" -- Basically says that if we're importing extra libraries, we're statically importing them.
    -- Statically importing libraries refers to the process of including the code from external libraries directly into the compiled executable or library at compile time. This is in contrast to dynamic linking, where the library code is linked to the executable at runtime.

    targetdir("../bin/" .. outputdir .. "/%{prj.name}") -- Specify final output directory to be in the root ofc! (When compiling) (..) is concatenation in lua. Also, %{} is string formatting in lua.
    objdir("../bin-int/" .. outputdir .. "/%{prj.name}") -- Specify object directory which contain our object files or intermediate files.

    files { -- Specify where our files can be found.
        "src/**.cpp", -- ** Includes all possible extensions with .cpp including ones in subdirectories. * will only work for all .cpp in current directory.
        "include/**.h", -- Another common header file extension is hpp
    }

    includedirs { -- These are the directories of files we want to include
        "include"
    }

    defines { -- Any definitions or customizations for different platforms defined in here. (Check this on docs plz)
        "WINDOWS"
    }

    filter { "configurations:Debug" } -- We can now customize how to build our project specific to a windows system ("system:windows",) and for the debug config. You can also not specify system for all platforms.
        buildoptions "/MTd" -- MT(d) for debug
        runtime "Debug"
        symbols "on" -- Specify to generate debug symbols

    filter { "configurations:Release" } -- Sets memory pool ??
        buildoptions "/MT"
        runtime "Release"
        optimize "on" -- We want to optimize our code as much as possible for release, ofc.