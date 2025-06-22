#!/bin/bash

echo "🧪 Testing build..."

echo "1. Cleaning previous build..."
make clean

echo "2. Attempting to build..."
if make; then
    echo "✅ Build successful!"
    echo "🎉 Your minishell is ready to use!"
    echo "Run it with: ./minishell"
else
    echo "❌ Build failed!"
    echo "Running comprehensive file check..."
    chmod +x check_all_files.sh
    ./check_all_files.sh
fi 