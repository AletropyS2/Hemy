@echo off
cd ..
title Generating Projects (DLL)...
call premake5 vs2022 --lib=shared
pause