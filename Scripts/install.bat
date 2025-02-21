@echo off
call build
pushd ..
cmake --install Out\BuildDir
popd