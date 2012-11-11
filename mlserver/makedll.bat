@echo off
set INCLUDE=%cd%\include;%INCLUDE%
set LIB=%cd%\lib;%LIB%
bin\cl /TP %1 /FI mlscript.h /nologo /O2 /w /LD /link /OUT:%2.dll > output.txt
del %2.lib
del %2.exp
del %2.obj