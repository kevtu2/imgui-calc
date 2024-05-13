@echo off

if "%1" == "" (goto printHelp) else (goto compile)

:compile
    vendor\bin\premake\premake5.exe %1

    if not defined DevEnvDir (
        :: Originally, we had to search up dev to open up the VS command prompt. This automates things and ensures that if it isn't already opened, we open it.
        call "C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\Tools\VsDevCmd.bat"
    )

    goto done

:printHelp
    type "buildhelp.txt"

:done



