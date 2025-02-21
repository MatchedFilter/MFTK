#!/bin/bash
rm -rf vendor
mkdir -p vendor
cp -r ../../Out/Debug/MFTK ./vendor/MFTK

chmod +x install.sh clean.sh
cd ..
cmake -S . -B Out/BuildDir -DCMAKE_BUILD_TYPE=Debug -DSDL2_TTF_SHARED=ON -G"Ninja" -DSDL2_TTF_SHARED=ON -DCMAKE_INSTALL_PREFIX=Out/Debug
cd Scripts