@echo off
SET dirname=%~dp0
SET exename=Q2.exe
%dirname%bin\Debug\%exename% < %dirname%test.txt
TIMEOUT /T 10
