#!/bin/bash

echo "🔍 Checking all files in Makefile..."

# Extract all file paths from Makefile
files=$(grep -E '^\t\$\(.*\)/.*\.c' Makefile | sed 's/^\t//' | sed 's/\\//')

missing_files=()
existing_files=()

for file in $files; do
    if [ ! -f "$file" ]; then
        echo "❌ Missing: $file"
        missing_files+=("$file")
    else
        echo "✅ Found: $file"
        existing_files+=("$file")
    fi
done

echo ""
echo "📊 Summary:"
echo "✅ Found: ${#existing_files[@]} files"
echo "❌ Missing: ${#missing_files[@]} files"

if [ ${#missing_files[@]} -gt 0 ]; then
    echo ""
    echo "📝 Missing files:"
    for file in "${missing_files[@]}"; do
        echo "  - $file"
    done
fi 