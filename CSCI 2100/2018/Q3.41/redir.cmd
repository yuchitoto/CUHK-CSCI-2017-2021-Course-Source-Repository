@echo off
SET dirname=%~dp0
SET exename=Q3.exe
%dirname%bin\Debug\%exename% < %dirname%test3.txt
TIMEOUT /T 10
