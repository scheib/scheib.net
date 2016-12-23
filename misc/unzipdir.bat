@echo off
echo.______________________________________________________
echo.
echo.UNZIPDIR by Vincent Scheib ( www.scheib.net )
echo.
echo.This will unzip files *.zip to individual directories.
echo.
echo. (This requires that the executable pkzip25.exe be in
echo.  your path.)
echo.
echo.Press CONTROL-C to cancel
echo.

if (%1)==() goto NORMAL
cd %1
if errorlevel==1 echo.ERROR, OPTIONAL PARAMETER MUST BE A DIRECTORY NAME
if errorlevel==1 goto END


:NORMAL

if not exist *.zip echo.THERE ARE NO .ZIP FILES TO EXTRACT, quitting
if not exist *.zip goto END
pause


if exist temp_zip echo.CAN NOT PROCEED, REQUIRED THAT temp_zip DOES NOT EXIST
if exist temp_all echo.CAN NOT PROCEED, REQUIRED THAT temp_all DOES NOT EXIST
if exist temp_zip goto END
if exist temp_all goto END

md temp_zip
md temp_all


if exist *.zip move *.zip temp_zip
move *.*   temp_all
if errorlevel 1 echo.PLEASE DISREGARD THAT ERROR MESSAGE, EVERYTHING IS OK!

cd temp_zip
rename *.zip *.
for %%f in (*.*) do md ..\%%f


REM If you would like to use classic command line pkzip
REM comment out the first for statement and uncomment
REM the following one.

for %%f in (*.*) do pkzip25 -extract -dir %%f. ..\%%f
REM for %%f in (*.*) do pkzip -d %%f. ..\%%f

rename *. *.zip
cd ..

if exist temp_zip\*.* move temp_zip\*.* .
move temp_all\*.* .
if errorlevel 1 echo.PLEASE DISREGARD THAT ERROR MESSAGE, EVERYTHING IS OK!

rd temp_zip
rd temp_all

:END

echo.
echo. DONE.
pause
