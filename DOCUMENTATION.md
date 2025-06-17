# Minishell Project Documentation

## Table of Contents
1. [Project Overview](#project-overview)
2. [Architecture](#architecture)
3. [Data Structures](#data-structures)
4. [Core Components](#core-components)
5. [Built-in Commands](#built-in-commands)
6. [Parsing System](#parsing-system)
7. [Expansion System](#expansion-system)
8. [Execution System](#execution-system)
9. [Memory Management](#memory-management)
10. [Signal Handling](#signal-handling)
11. [Error Handling](#error-handling)
12. [Compilation](#compilation)
13. [Usage Examples](#usage-examples)
14. [Troubleshooting](#troubleshooting)

## Project Overview

Minishell is a simplified shell implementation that mimics the behavior of bash. It provides a command-line interface where users can execute commands, use environment variables, handle pipes and redirections, and run built-in commands.

### Key Features
- Command execution with arguments
- Environment variable expansion
- Built-in commands (echo, cd, pwd, export, unset, env)
- Pipe handling (|)
- Redirections (<, >, >>, <<)
- Signal handling (Ctrl+C, Ctrl+D)
- Memory management with garbage collection
- Error handling and status codes

## Architecture

The project follows a modular architecture with clear separation of concerns:

```
minishell/
├── main.c                 # Entry point and main loop
├── include/
│   └── minishell.h       # Header file with all declarations
├── src/
│   ├── parser/           # Command parsing and tokenization
│   ├── expansion/        # Variable expansion system
│   ├── execution/        # Command execution logic
│   ├── built_in/         # Built-in command implementations
│   ├── env/              # Environment management
│   ├── utils/            # Utility functions
│   ├── signals/          # Signal handling
│   └── main_tools/       # Main loop utilities
└── Makefile              # Build configuration
```

## Data Structures

### Core Structures

#### `t_shell_control_block`
The main control structure that holds all shell state:

```c
typedef struct s_shell_control_block
{
    char **env_cpy;           // Environment variables copy
    char *line;               // Current input line
    char **splitted;          // Split input into words
    t_token *tokenized;       // Tokenized commands
    char **cmd_and_args;      // Command and arguments for execution
    t_expand *expand_arr;     // Expansion data array
    
    int arr[2];               // Pipe file descriptors
    int previous_read_end;    // Previous pipe read end
    t_token *line_pointer;    // Current token pointer
    char *in_file_name;       // Input redirection file
    char *file_name;          // Output redirection file
    int fd_out;               // Output file descriptor
    int fd_in;                // Input file descriptor
    int last_child_pid;       // Last child process PID
    int status;               // Process status
    int exit_status;          // Shell exit status
} t_shell_control_block;
```

#### `t_token`
Represents a tokenized command element:

```c
typedef struct s_token
{
    int type;                 // Token type (WORD, PIPE, REDIR_IN, etc.)
    char *word;               // Token content
    char *heredoc_file_name;  // Heredoc temporary file name
    char *delimiter;          // Heredoc delimiter
} t_token;
```

#### `t_expand`
Handles variable expansion data:

```c
typedef struct s_expand
{
    char *befor_dollar;       // Text before $ symbol
    char *to_expand;          // Variable name to expand
    char *after_dollar;       // Text after $ symbol
    int last_one;             // Flag for last expansion
    int heredoc_flag;         // Heredoc context flag
} t_expand;
```

#### `t_list`
Generic linked list for garbage collection:

```c
typedef struct s_list
{
    void *content;            // Pointer to allocated memory
    struct s_list *next;      // Next list node
} t_list;
```

### Token Types
```c
typedef enum e_type
{
    WORD,         // 0 - Regular words/commands
    PIPE,         // 1 - Pipe operator (|)
    REDIR_IN,     // 2 - Input redirection (<)
    REDIR_OUT,    // 3 - Output redirection (>)
    REDIR_APPEND, // 4 - Append redirection (>>)
    HEREDOC,      // 5 - Here document (<<)
} t_type;
```

## Core Components

### Main Loop (`main.c`)

The main function implements the shell's primary loop:

```c
int main(int ac, char **av, char **env)
{
    t_shell_control_block shell;
    
    ft_init_shell_block(&shell, ac, av);
    shell.env_cpy = copy_env(env);
    
    while (1) {
        handle_signals(0);
        if(!ft_readline(&shell))
            continue;
        parse_line(&shell);
        execute_line(&shell);
        free_memory(get_garbage_pointer(0));
        free(shell.line);
    }
    return (0);
}
```

**Flow:**
1. **Initialization**: Set up shell control block and copy environment
2. **Signal Handling**: Set up signal handlers for Ctrl+C, Ctrl+D
3. **Input Reading**: Read command line using readline
4. **Parsing**: Parse the input into tokens
5. **Execution**: Execute the parsed commands
6. **Cleanup**: Free allocated memory
7. **Repeat**: Continue until exit

### Parsing System (`src/parser/`)

The parsing system converts raw input into executable tokens through several stages:

#### 1. Customized Split (`customized_split.c`)
Splits input on whitespace while preserving quoted strings:
- Handles single and double quotes
- Preserves spaces within quotes
- Returns array of strings

#### 2. Operator Splitting (`split_with_operators.c`)
Separates operators from words:
- Identifies pipes (|), redirections (<, >, >>, <<)
- Creates separate tokens for operators
- Maintains command structure

#### 3. Variable Expansion (`expand.c`)
Expands environment variables:
- Processes $VARIABLE syntax
- Handles special cases like $?
- Replaces variables with their values

#### 4. Post-Expansion Splitting (`splitte_after_expantion.c`)
Re-splits after variable expansion:
- Handles cases where expansion creates spaces
- Ensures proper command/argument separation

#### 5. Quote Handling (`handle_dollar_with_quotes.c`)
Processes dollar signs within quotes:
- Different behavior for single vs double quotes
- Variable expansion rules in quoted contexts

#### 6. Token Creation (`make_token.c`)
Converts parsed strings into structured tokens:
- Assigns appropriate token types
- Handles redirection file names
- Creates token array for execution

### Expansion System (`src/expansion/`)

Handles environment variable expansion and special character processing:

#### Key Functions:

**`expand_if_possible()`**
- Main expansion function
- Identifies variables to expand
- Manages expansion array allocation

**`get_env_var()`**
- Retrieves environment variable values
- Handles special cases ($?, $USER, etc.)
- Returns NULL for undefined variables

**`new_str_after_expand()`**
- Reconstructs string after expansion
- Joins before, expanded, and after parts
- Handles multiple expansions in one string

**`should_i_expand()`**
- Determines if character should trigger expansion
- Considers quote context and syntax rules

**`is_expand_separator()`**
- Identifies valid variable name characters
- Handles alphanumeric and underscore characters

### Execution System (`src/execution/`)

Manages command execution, process creation, and built-in command handling:

#### Command Execution Flow:

1. **Built-in Check**: First checks if command is built-in
2. **Process Creation**: Forks child process for external commands
3. **Redirection Setup**: Handles input/output redirections
4. **Command Execution**: Uses execve for external commands
5. **Status Collection**: Waits for child process completion

#### Key Functions:

**`execute_command_line()`**
- Main execution coordinator
- Handles pipes and redirections
- Manages process creation and cleanup

**`execute_command()`**
- Executes individual commands
- Sets up redirections
- Handles command path resolution

**`get_cmd_and_its_args()`**
- Extracts command and arguments from tokens
- Filters out redirection operators
- Prepares command array for execve

### Built-in Commands (`src/built_in/`)

Implements shell built-in commands that don't require external processes:

#### 1. `echo` (`echo.c`)
- Prints arguments to stdout
- Handles -n flag for no newline
- Supports quoted strings

#### 2. `cd` (`cd.c`)
- Changes current working directory
- Handles relative and absolute paths
- Updates PWD environment variable
- Error handling for invalid directories

#### 3. `pwd` (`pwd.c`)
- Prints current working directory
- Uses getcwd() system call
- Returns NULL on error

#### 4. `export` (`export.c`)
- Sets environment variables
- Validates variable names
- Handles multiple variables
- Updates shell environment

#### 5. `unset` (`unset.c`)
- Removes environment variables
- Validates variable names
- Handles multiple variables
- Updates shell environment

#### 6. `env` (`env.c`)
- Prints all environment variables
- Simple iteration through env array

#### Built-in Handler (`check_built_in_command.c`)
- Central dispatcher for built-in commands
- Returns appropriate exit status
- Handles command validation

### Environment Management (`src/env/`)

Manages shell environment variables:

#### Key Functions:

**`copy_env()`**
- Creates copy of system environment
- Allocates memory for environment array
- Preserves all existing variables

**`allocate_and_init_expand_list()`**
- Manages expansion array allocation
- Initializes expansion structures
- Handles memory reuse for efficiency

## Memory Management

### Garbage Collection System

The shell implements a custom garbage collection system to prevent memory leaks:

#### Key Components:

**`ft_malloc()`**
- Custom memory allocator
- Tracks allocated memory
- Integrates with garbage collection

**`garbage_collector.c`**
- Manages memory tracking list
- Provides cleanup functions
- Handles memory deallocation

**`get_garbage_pointer()`**
- Returns global garbage collection list
- Ensures single instance
- Thread-safe memory management

#### Usage Pattern:
```c
// Allocate memory
char *str = ft_malloc(size, 1);

// Memory is automatically tracked
// Cleanup at end of command
free_memory(get_garbage_pointer(0));
```

### Memory Safety Features

1. **Automatic Tracking**: All allocations are tracked
2. **Command-Level Cleanup**: Memory freed after each command
3. **Error Recovery**: Memory cleanup on errors
4. **No Memory Leaks**: Comprehensive cleanup system

## Signal Handling (`src/signals/`)

Manages shell signals for proper behavior:

### Signal Types:

1. **SIGINT (Ctrl+C)**: Interrupts current command
2. **SIGQUIT (Ctrl+\)**: Quits current command
3. **SIGTSTP (Ctrl+Z)**: Suspends current command

### Implementation:

**`handle_signals()`**
- Sets up signal handlers
- Different behavior for parent/child processes
- Preserves shell state

**`child_signal_handler()`**
- Handles signals in child processes
- Default behavior for external commands
- Proper process termination

## Error Handling

### Error Types:

1. **Syntax Errors**: Invalid command syntax
2. **Permission Errors**: File access issues
3. **Command Not Found**: Non-existent commands
4. **Memory Errors**: Allocation failures
5. **Redirection Errors**: File operation issues

### Error Management:

**`print_error()`**
- Centralized error reporting
- Supports variable arguments
- Consistent error format

**Status Codes:**
- 0: Success
- 1: General error
- 2: Syntax error
- 126: Command not executable
- 127: Command not found
- 128+n: Signal n

## Compilation

### Build System

The project uses a Makefile for compilation:

```makefile
NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -Iinclude
READLINE = -lreadline
```

### Compilation Commands:

```bash
# Build the project
make

# Clean object files
make clean

# Clean everything and rebuild
make fclean && make

# Rebuild
make re
```

### Dependencies:

1. **readline**: Command line editing library
2. **Standard C libraries**: stdio, stdlib, unistd, etc.
3. **System calls**: fork, execve, wait, etc.

## Usage Examples

### Basic Commands:
```bash
# Simple command execution
ls -la
pwd
echo "Hello World"

# Environment variables
export PATH=/usr/bin:/bin
echo $PATH
unset PATH
```

### Redirections:
```bash
# Input redirection
cat < file.txt

# Output redirection
ls > output.txt

# Append redirection
echo "new line" >> file.txt

# Here document
cat << EOF
line 1
line 2
EOF
```

### Pipes:
```bash
# Simple pipe
ls | grep "\.c$"

# Multiple pipes
cat file.txt | grep "pattern" | wc -l
```

### Built-in Commands:
```bash
# Change directory
cd /home/user
cd ..

# Environment management
export VAR="value"
unset VAR
env

# Working directory
pwd
```

### Complex Examples:
```bash
# Variable expansion with commands
export CMD="ls -la"
$CMD

# Redirection with pipes
cat < input.txt | grep "pattern" > output.txt

# Multiple commands with variables
export DIR="/usr/bin"
ls $DIR | head -5
```

## Troubleshooting

### Common Issues:

1. **Segmentation Faults**
   - Check memory allocation
   - Verify pointer validity
   - Review garbage collection

2. **Command Not Found**
   - Verify PATH environment variable
   - Check command existence
   - Review file permissions

3. **Redirection Errors**
   - Check file permissions
   - Verify file existence
   - Review redirection syntax

4. **Memory Leaks**
   - Ensure proper cleanup
   - Check garbage collection
   - Review allocation patterns

### Debug Features:

1. **Debug Prints**: Built-in debug statements
2. **Memory Tracking**: Garbage collection logs
3. **Error Messages**: Detailed error reporting
4. **Status Codes**: Exit status tracking

### Testing Strategy:

1. **Unit Tests**: Individual function testing
2. **Integration Tests**: Command execution testing
3. **Edge Cases**: Error condition testing
4. **Memory Tests**: Leak detection

## Project Structure Summary

```
minishell/
├── main.c                    # Entry point and main loop
├── include/minishell.h       # All declarations and structures
├── src/
│   ├── parser/              # Command parsing (8 files)
│   ├── expansion/           # Variable expansion (7 files)
│   ├── execution/           # Command execution (3 files)
│   ├── built_in/            # Built-in commands (12 files)
│   ├── env/                 # Environment management (2 files)
│   ├── utils/               # Utility functions (20 files)
│   ├── signals/             # Signal handling (1 file)
│   └── main_tools/          # Main loop utilities (2 files)
└── Makefile                 # Build configuration
```

## Conclusion

This minishell implementation provides a robust, feature-complete shell environment with proper memory management, error handling, and signal processing. The modular architecture makes it maintainable and extensible, while the comprehensive documentation ensures understanding of all components and their interactions.

The shell successfully mimics bash behavior for basic operations while providing a solid foundation for more advanced features. The garbage collection system ensures memory safety, and the built-in commands provide essential shell functionality. 