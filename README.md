# Minishell

A minimal shell implementation in C that supports basic shell functionality including command execution, pipes, redirections, and built-in commands.

## Project Structure

The project has been reorganized into a hierarchical structure for better maintainability and clarity:

```
minishell/
├── include/                 # Header files
│   ├── minishell.h         # Main header with structures and core functions
│   ├── builtins.h          # Built-in command declarations
│   ├── execution.h         # Execution and redirection functions
│   ├── expansion.h         # Variable expansion functions
│   ├── parser.h            # Parsing and tokenization functions
│   ├── utils.h             # Utility functions
│   └── env.h               # Environment handling functions
├── src/                    # Source code
│   ├── main.c              # Entry point
│   ├── core/               # Core shell functionality
│   │   └── shell.c         # Shell initialization and main loop
│   ├── builtins/           # Built-in commands
│   │   ├── builtin_dispatcher.c  # Built-in command dispatcher
│   │   ├── echo.c          # echo command
│   │   ├── cd.c            # cd command
│   │   ├── pwd.c           # pwd command
│   │   ├── env.c           # env command
│   │   ├── export.c        # export command
│   │   ├── unset.c         # unset command
│   │   ├── env_validation.c # Environment variable validation
│   │   └── *.c             # Built-in utility functions
│   ├── execution/          # Command execution
│   │   ├── command_executor.c     # Command execution logic
│   │   ├── execute_command_line.c # Pipeline execution
│   │   ├── handle_signals.c       # Signal handling
│   │   ├── handle_redir_*.c       # Redirection handling
│   │   └── handle_heredoc.c       # Here document handling
│   ├── parser/             # Parsing and tokenization
│   │   ├── tokenizer.c     # Token creation
│   │   ├── lexer.c         # Lexical analysis
│   │   ├── file_parser.c   # File name parsing
│   │   ├── split_with_operators.c # Operator splitting
│   │   └── *.c             # Other parsing functions
│   ├── expansion/          # Variable expansion
│   │   ├── expand_if_possible.c   # Main expansion logic
│   │   ├── expand_outside_dollars.c # Dollar expansion
│   │   └── *.c             # Other expansion functions
│   ├── env/                # Environment handling
│   │   ├── copy_env.c      # Environment copying
│   │   └── allocate_and_init_expand_list.c # Expansion list allocation
│   └── utils/              # Utility functions
│       ├── ft_*.c          # Standard library replacements
│       ├── garbage_collector.c # Memory management
│       ├── get_next_line.c # Line reading utility
│       └── *.c             # Other utility functions
├── Makefile                # Build configuration
└── README.md               # This file
```

## Features

- **Command Execution**: Execute external commands with full path resolution
- **Built-in Commands**: 
  - `echo` - Print arguments
  - `cd` - Change directory
  - `pwd` - Print working directory
  - `env` - Print environment variables
  - `export` - Export environment variables
  - `unset` - Unset environment variables
  - `exit` - Exit the shell
- **Pipes**: Support for command pipelines using `|`
- **Redirections**: 
  - Input redirection `<`
  - Output redirection `>`
  - Append redirection `>>`
  - Here documents `<<`
- **Variable Expansion**: Support for `$VAR` and `$?` expansion
- **Signal Handling**: Proper handling of Ctrl+C, Ctrl+D, and Ctrl+\
- **Memory Management**: Garbage collection system to prevent memory leaks

## Building

To build the project:

```bash
make
```

To clean object files:

```bash
make clean
```

To clean everything and rebuild:

```bash
make re
```

## Usage

Run the shell:

```bash
./minishell
```

The shell will display a prompt and wait for commands. You can:

- Type commands and press Enter to execute them
- Use pipes to chain commands: `ls | grep .c`
- Use redirections: `echo "hello" > file.txt`
- Use environment variables: `echo $PATH`
- Use built-in commands: `cd /tmp`, `pwd`, `export VAR=value`

To exit the shell, type `exit` or press Ctrl+D.

## Dependencies

- GCC compiler
- Make
- Readline library (for command line editing and history)

## Notes

- This is a minimal shell implementation for educational purposes
- It follows the 42 school coding standards
- All memory is managed through a garbage collection system
- The shell supports basic shell functionality but is not a full replacement for bash 