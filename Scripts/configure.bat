@echo off
pushd ..
cmake -S . -B Out\BuildDir -DCMAKE_BUILD_TYPE=Debug -G"Ninja" -DCMAKE_INSTALL_PREFIX=Out\Debug
popd