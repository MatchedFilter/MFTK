@echo off
ninja -C ..\Out\BuildDir
pushd ..
cmake --install Out/BuildDir
popd 