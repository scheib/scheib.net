@echo off
if (%1) == (keyword) goto OK

echo. This is not intended to be called from comand line
goto END

:== OK

echo. BUILD: %*

if (%2) == (test1) goto TEST1
if (%2) == (1) goto NORMAL
if (%2) == (2) goto TALL
if (%2) == (3) goto WIDE

echo. error, did not catch build format?
goto END

:== TEST1

echo. building %3.html
echo %3 > temp1
type 1 > %3.html
type temp1 >> %3.html
type 2 >> %3.html
type 3 >> %3.html
del temp1
goto END

:== NORMAL

type noframes-1.html > %3.html
echo %4 >> %3.html
echo ### >> %3.html
type noframes-2.html >> %3.html
echo %3 >> %3.html
echo ### >> %3.html
type noframes-3.html >> %3.html
echo %4 >> %3.html
echo ### >> %3.html
type noframes-4.html >> %3.html

goto END

:== TALL

type frames-cols-1.html > %3.html
echo %4 >> %3.html
echo ### >> %3.html
type frames-cols-2.html >> %3.html
echo %3 >> %3.html
echo ### >> %3.html
type frames-cols-3.html >> %3.html
echo %3 >> %3.html
echo ### >> %3.html
type frames-cols-4.html >> %3.html

type frames-cols-content-1.html > %3f.html
echo %4 >> %3f.html
echo ### >> %3f.html
type frames-cols-content-2.html >> %3f.html
echo %3 >> %3f.html
echo ### >> %3f.html
type frames-cols-content-3.html >> %3f.html
echo %4 >> %3f.html
echo ### >> %3f.html
type frames-cols-content-4.html >> %3f.html

goto END

:== WIDE

type frames-rows-1.html > %3.html
echo %4 >> %3.html
echo ### >> %3.html
type frames-rows-2.html >> %3.html
echo %3 >> %3.html
echo ### >> %3.html
type frames-rows-3.html >> %3.html
echo %3 >> %3.html
echo ### >> %3.html
type frames-rows-4.html >> %3.html

type frames-rows-content-1.html > %3f.html
echo %4 >> %3f.html
echo ### >> %3f.html
type frames-rows-content-2.html >> %3f.html
echo %3 >> %3f.html
echo ### >> %3f.html
type frames-rows-content-3.html >> %3f.html
echo %4 >> %3f.html
echo ### >> %3f.html
type frames-rows-content-4.html >> %3f.html

goto END

:== END