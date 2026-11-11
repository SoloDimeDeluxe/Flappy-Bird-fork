@echo off
rem COPIA LA CARPETA RES AL LADO DEL EXE DESPUES DE COMPILAR
rem %1 = CARPETA DE LA SOLUCION, %2 = CARPETA DE SALIDA (bin\x64\Debug o bin\x64\Release)

xcopy "%~1res" "%~2res" /E /I /Y /D

rem XCOPY DEVUELVE 1 CUANDO NO HAY NADA NUEVO PARA COPIAR, ESO NO ES UN ERROR
if errorlevel 2 exit /b %errorlevel%
exit /b 0