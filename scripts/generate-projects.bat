@echo off
pushd %~dp0\..\
call scripts\\bin\\premake5.exe vs2022
popd
PAUSE