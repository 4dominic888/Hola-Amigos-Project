@echo off
setlocal enabledelayedexpansion

rem variables feas
set "src_dir=src"
set "obj_dir=obj"
set "txt_file=datenow.txt"

rem Obtiene la fecha de modificación del archivo "datenow.txt"
for %%F in ("%txt_file%") do (
    set "txt_date=%%~tF"
)

for %%f in ("%src_dir%\*.cpp") do (
    set "filename=%%~nf"

    rem Obtiene la fecha de modificación del archivo
    for %%d in ("%%~f") do (
        set "file_date=%%~td"
    )

    rem Compara las fechas
    if "!file_date!" gtr "!txt_date!" (
        echo Archivo modificado: !filename!
        g++ -c "%%f" -o "%obj_dir%\!filename!.o" -lglad
    )
)

set "output_file=datenow.txt"

echo Halo, teri teri > "%output_file%"

endlocal




IF %ERRORLEVEL% NEQ 0 (
    echo Compilacion mala1
) else (
    g++ main.cpp obj/*.o -o "Hola Amigos.exe" -lglfw3 -lopengl32 -lgdi32 -lglad

    IF %ERRORLEVEL% EQU 0 (
        start "" "Hola Amigos.exe"
    ) else (
        echo Compilacion mala2
    )
)


