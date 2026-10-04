#!/bin/bash

# Check if Linux executable exists, build if missing
if [ ! -f "./Library_Management" ]; then
    echo "Executable ./Library_Management not found. Building now..."
    bash ./build_linux.sh
fi

echo "Starting Library Management System on Linux..."
./Library_Management
