@echo off

rmdir /S /Q ..\vendor
mkdir ..\vendor\MFTK
xcopy /S /E /H /Y ..\..\..\Out\Debug\MFTK ..\vendor\MFTK
pushd ..
cmake -S . -B Out/BuildDir -DCMAKE_BUILD_TYPE=Debug -DSDL2_TTF_SHARED=ON -G"Ninja" -DSDL2_TTF_SHARED=ON -DCMAKE_INSTALL_PREFIX=Out/Debug
popd
