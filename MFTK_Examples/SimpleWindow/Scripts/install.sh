#!/bin/bash
ninja -C ../Out/BuildDir
cd ..
cmake --install Out/BuildDir
cd Scripts