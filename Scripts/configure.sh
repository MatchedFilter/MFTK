#!/bin/bash
chmod +x build.sh install.sh clean.sh
cd ..
cmake -S . -B ../Out/BuildDir -DCMAKE_BUILD_TYPE=Debug -G"Ninja" -DCMAKE_INSTALL_PREFIX=Out/Debug
cd Scripts