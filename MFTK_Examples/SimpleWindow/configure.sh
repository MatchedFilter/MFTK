#!/bin/bash
chmod +x install.sh
cmake -S . -B Out/BuildDir -DCMAKE_BUILD_TYPE=Debug -G"Ninja" -DCMAKE_INSTALL_PREFIX=Out/Debug