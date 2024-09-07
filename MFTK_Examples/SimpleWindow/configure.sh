#!/bin/bash
rm -rf vendor
cp -r ../../Out/Debug/vendor .
cp -r ../../Out/Debug/MFTK ./vendor/

chmod +x install.sh clean.sh
cmake -S . -B Out/BuildDir -DCMAKE_BUILD_TYPE=Debug -DSDL2_TTF_SHARED=ON -G"Ninja" -DSDL2_TTF_SHARED=ON -DCMAKE_INSTALL_PREFIX=Out/Debug