$src_dir = "src"
$obj_dir = "obj"
$txt_file = "datenow.txt"

$salidaO = "nada"

# Obtiene la fecha de modificación del archivo "datenow.txt"
$txt_date = (Get-Item $txt_file).LastWriteTime
try{
    foreach ($file in Get-ChildItem -Path $src_dir -Filter "*.cpp") {
        $filename = $file.BaseName

        # Obtiene la fecha de modificación del archivo
        $file_date = (Get-Item $file.FullName).LastWriteTime

        # Compara las fechas
        if ($file_date -gt $txt_date) {
            Write-Host "Archivo modificado: $filename"
            g++ -c $file.FullName -o "$obj_dir\$filename.o" -lglad
            if ($LASTEXITCODE -ne 0) {$salidaO = "error"}
        }
    }

    $output_file = "datenow.txt"
    Set-Content -Path $output_file -Value "Halo, teri teri"

    if($salidaO -eq "nada") {
        g++ main.cpp obj/*.o -o "Hola Amigos.exe" -lglfw3 -lopengl32 -lgdi32 -lglad -lwinmm
        if ($LASTEXITCODE -eq 0) {
            Start-Process -FilePath "Hola Amigos.exe"
        }
        else{
            Write-Host "Error al crear el exe :("
        }
    }
    else{
        Write-Host "Error al cargar las dependencias de src"
    }
}
catch{
    $errorMessage = $Error[0].Exception.FullyQualifiedErrorId
    Write-Host "Error: $errorMessage"
}


