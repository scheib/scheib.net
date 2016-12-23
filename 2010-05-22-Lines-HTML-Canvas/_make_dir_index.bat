echo ^<html^>^<body^>^<table^> > index.html
for %%x in (*.*) do echo ^<tr^>^<td^>^<a href="%%~x"^>%%~x^</a^>^</td^>^<td align="right"^>%%~zx Bytes^</td^>^</tr^> >> index.html
echo ^</body^>^</html^> >> index.html

: Strip index.html from list
move /y index.html index.tmp
type index.tmp | find /v "index.html" > index.html

: Strip this batch file from list
move /y index.html index.tmp
type index.tmp | find /v "%~n0%~x0" > index.html

del /q index.tmp
pause