#!/bin/bash
chmod +x build.sh install.sh clean.sh
cmake -S . -B BuildDir -DCMAKE_BUILD_TYPE=Debug -G"Ninja"