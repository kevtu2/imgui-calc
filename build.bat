@echo off

if "%1" == "" (goto printHelp) else (goto compile)

:compile
    start C:\Users\unive\Desktop\Projects\graphing-calc\vendor\bin\premake\premake5.exe %1
    goto done

:printHelp
    type "buildhelp.txt"
    goto done

:done



