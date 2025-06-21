#!/bin/bash

echo "🔍 Debugging build issues..."

echo "1. Checking if print_exit_signal_message.c exists:"
if [ -f "src/execution/print_exit_signal_message.c" ]; then
    echo "✅ File exists"
    ls -la src/execution/print_exit_signal_message.c
else
    echo "❌ File missing"
fi

echo ""
echo "2. Trying to compile just this file:"
if gcc -Wall -Wextra -Werror -g -Iinclude -c src/execution/print_exit_signal_message.c -o test.o 2>&1; then
    echo "✅ Compilation successful"
    rm -f test.o
else
    echo "❌ Compilation failed"
fi

echo ""
echo "3. Checking all execution files:"
ls -la src/execution/*.c

echo ""
echo "4. Checking if there are any hidden characters in filenames:"
find src/execution -name "*.c" -exec ls -la {} \; 