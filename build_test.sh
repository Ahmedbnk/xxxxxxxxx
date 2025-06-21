#!/bin/bash

echo "Cleaning previous build..."
make clean

echo "Building minishell..."
make

if [ $? -eq 0 ]; then
    echo "✅ Build successful!"
    echo "You can now run: ./minishell"
else
    echo "❌ Build failed!"
    echo "Check the error messages above."
fi 