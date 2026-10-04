#!/bin/bash

# Exit immediately if a command exits with a non-zero status
set -e

echo "===================================================="
echo " Building Linux Library Management System with GCC  "
echo "===================================================="

# Compile with strict C11 flags and warnings enabled
gcc -Wall -Wextra -std=c11 Library_Management.c -o Library_Management

if [ -f "./Library_Management" ]; then
    chmod +x Library_Management
    echo "✔ Build Succeeded! Binary created: ./Library_Management"
    echo "Run using: ./Library_Management or ./run_linux.sh"
else
    echo "❌ Build Failed: Executable not found."
    exit 1
fi
