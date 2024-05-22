workspace "Calculator"
    configurations {
        "Debug",
        "Release"
    }
    platforms {
        "Win32",
        "Win64"
    }
    filter { "platforms:Win32" }
        system "Windows"
        architecture "x86"
    
    filter { "platforms:Win64" }
        system "Windows"
        architecture "x86_64"
    

startproject "Calculator"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}" -- Global output dir name variable

include "CalcGUI"
include "Calculator"

newaction {
    trigger = "clean", -- How is this action called or "triggered"?
    description = "Remove all binaries, intermediate binaries, and vs files.",  -- Gives a description of what this action does.
    execute =function()
        print("Removing binaries..")
        os.rmdir("bin")
        print("Done.")
        print("Removing intermediate binaries..")
        os.rmdir("binint")
        print("Done.")
        print("Removing project files..")
        os.rmdir(".vs") -- This is a visual studio directory
        os.remove("Calculator.sln")
        os.remove("CalcGUI/CalcGUI.vcxproj.**")
        os.remove("Calculator/Calculator.vcxproj.**")
        print("Done all.")
    end
}