workspace "Workspace" -- in Visual Studio, this refers to the overall project

    configurations { -- Specify VS project configurations. (Debug - for debugging purposes, Release - Optimize for distributing/releasing project)
        "Debug",
        "Release"
    }
    platforms { -- Once set, these platforms with their specific builds will appear in the Platforms list in VS
        "Win32",
        "Win64"
    }
    filter { "platforms:Win32" }
        system "Windows"
        architecture "x86"

    filter { "platforms:Win64" }
        system "Windows"
        architecture "x86_64"
        
    startproject "PracticeProject" -- This specifies the start project that we go into when you open the solution file.


outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}" -- These variables is what premake will give us.
-- An example of what this is is the output directory will now be if the build config was DEBUG, the system is windows and the architecture is x64,
-- We'd get "Debug-Windows-x64"
-- This basically just names our directories (Namely, the output directory)

include "PracticeProject" -- We have no way to include the practice project tho :(. What this does is that it goes into the folder "PracticeProject"
-- and it will look for a premake5.lua file.

include "MathLibrary"

-- We can add custom actions into premake:
newaction {
    trigger = "clean", -- How is this action called or "triggered"?
    description = "Remove all binaries, intermediate binaries, and vs files.",  -- Gives a description of what this action does.
    execute =function()
        print("Removing binaries..")
        os.rmdir("./bin")
        print("Done.")
        print("Removing intermediate binaries..")
        os.rmdir("./bin-int")
        print("Done.")
        print("Removing project files..")
        os.rmdir("./.vs") -- This is a visual studio directory
        os.remove("**.sln")
        os.remove("**.vcxproj")
        os.remove("**.vcxproj.filters")
        os.remove("**.vcxproj.user")
        print("Done all.")
    end
}