@echo off
echo ^<html^>^<body^> > index.html
for %%x in (*.*) do call :additem %%~nxx
echo ^</html^>^</body^> >> index.html
echo done.
pause
exit /b

:additem
if "%*"=="" exit /b
if "%*"=="%~nx0" exit /b
if "%*"=="index.html" exit /b
echo ^<a href="%*"^>%*^</a^>^<br^> >> index.html
