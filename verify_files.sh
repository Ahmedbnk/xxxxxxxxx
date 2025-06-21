#!/bin/bash

echo "Verifying that all files in Makefile exist..."

# Extract file paths from Makefile
files=$(grep -E '^\t\$\(.*\)/.*\.c' Makefile | sed 's/^\t//' | sed 's/\\//')

missing_files=0

for file in $files; do
    if [ ! -f "$file" ]; then
        echo "❌ Missing: $file"
        missing_files=$((missing_files + 1))
    else
        echo "✅ Found: $file"
    fi
done

echo ""
if [ $missing_files -eq 0 ]; then
    echo "🎉 All files exist! Ready to build."
else
    echo "❌ Found $missing_files missing files. Please fix the Makefile."
fi 