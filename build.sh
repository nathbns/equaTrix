#!/bin/bash

# Vérifier si le fichier lib.a existe
if [ ! -f "build/libantlr4_runtime.a" ]; then
    echo "Compilation complete"
    rm -rf build && mkdir build
fi

# Check if system is MacOS
if [[ "$OSTYPE" == "darwin"* ]]; then
    cd build && cmake .. && make && ./EquaTrix_qt.app/Contents/MacOS/EquaTrix_qt
else
    cd build && cmake .. && make && ./EquaTrix_qt
fi