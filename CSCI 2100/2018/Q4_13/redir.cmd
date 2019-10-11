@echo off
SET dirname=%~dp0
SET exename=Q4_13.exe
%dirname%bin\Debug\%exename% < %dirname%test.txt
TIMEOUT /T 10
