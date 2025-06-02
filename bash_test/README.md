# Minishell

A minimal implementation of a shell program, similar to bash, written in C. This project is part of the 42 school curriculum.

## Features

- Command execution (both built-in and external commands)
- Environment variable handling
- Signal handling (Ctrl+C, Ctrl+D, Ctrl+\)
- Command history (up/down arrows)
- Input parsing and tokenization
- Redirections (>, >>, <, <<)
- Pipes (|)
- Environment variable expansion ($VAR)
- Quote handling (single and double quotes)

## Built-in Commands

1. `echo [-n] [args...]`
   - Prints arguments to stdout
   - `-n` option suppresses the trailing newline

2. `cd [dir]`
   - Changes the current directory
   - Without arguments, changes to HOME directory
   - `cd -` changes to the previous directory
   - Updates PWD and OLDPWD environment variables

3. `pwd`
   - Prints the current working directory

4. `export [name=value...]`
   - Sets environment variables
   - Without arguments, displays all exported variables

5. `unset [name...]`
   - Removes environment variables

6. `env`
   - Displays all environment variables

7. `exit [n]`
   - Exits the shell with status n
   - Without arguments, exits with status 0

## Project Structure

```
minishell/
├── include/
│   └── minishell.h      # Main header file
├── src/
│   ├── builtins/        # Built-in command implementations
│   │   ├── builtins_core.c    # Core builtin functions
│   │   ├── builtins_echo.c    # echo command
│   │   ├── builtins_cd.c      # cd command
│   │   ├── builtins_pwd.c     # pwd command
│   │   ├── builtins_env.c     # env, export, unset commands
│   │   └── builtins_exit.c    # exit command
│   ├── env/             # Environment handling
│   │   ├── copy_env.c
│   │   └── allocate_and_init_expand_list.c
│   ├── expansion/       # Variable expansion
│   │   ├── expand_if_possible.c
│   │   ├── should_i_expand.c
│   │   ├── is_expand_separator.c
│   │   └── new_string_after_expand.c
│   ├── parser/          # Command parsing
│   │   ├── check_input_error.c
│   │   ├── remove_quotes_from_args.c
│   │   ├── split_with_operators.c
│   │   ├── make_token.c
│   │   ├── is_between_quotes.c
│   │   ├── customized_split.c
│   │   ├── parse_tokenized.c
│   │   ├── handle_heredoc.c
│   │   ├── handle_redir_in.c
│   │   ├── handle_redir_out.c
│   │   └── handle_append.c
│   ├── signals/         # Signal handling
│   │   └── handle_signals.c
│   ├── execution/       # Command execution
│   │   └── execute_command.c
│   └── utils/           # Utility functions
│       ├── ft_strncmp.c
│       ├── ft_putstr_fd.c
│       ├── ft_atoi.c
│       └── ... (other utility functions)
├── main.c              # Main program entry point
└── Makefile           # Build configuration
```

## Building and Running

1. Clone the repository:
```bash
git clone <repository-url>
cd minishell
```

2. Build the project:
```bash
make
```

3. Run the shell:
```bash
./minishell
```

## Signal Handling

- `Ctrl+C` (SIGINT): Interrupts the current command
- `Ctrl+D` (EOF): Exits the shell
- `Ctrl+\` (SIGQUIT): Quits the current command (if running)

## Error Handling

The shell handles various error conditions:
- Command not found
- Permission denied
- No such file or directory
- Invalid syntax
- Environment variable not set
- Memory allocation failures

Error messages follow the format:
```
minishell: command: error message
```

## Memory Management

- All allocated memory is properly freed
- No memory leaks
- Uses garbage collection for complex operations

## Coding Standards

- Follows 42 school coding standards (norminette)
- Functions limited to 25 lines
- Files limited to 5 functions
- Proper header protection
- Clear and consistent naming conventions

## Dependencies

- C compiler (gcc/clang)
- Make
- readline library
- Standard C libraries

## Testing

Test the shell with various commands:
```bash
# Basic commands
ls
pwd
cd /path/to/dir
echo "Hello, World!"

# Environment variables
export MYVAR=value
echo $MYVAR
unset MYVAR

# Redirections
echo "Hello" > file.txt
cat < file.txt
echo "Append" >> file.txt

# Pipes
ls | grep "file"
cat file.txt | wc -l

# Heredoc
cat << EOF
This is a heredoc
EOF

# Quotes and special characters
echo "Hello $USER"
echo 'Hello $USER'
echo "Special chars: \$ \" '"
```

## Contributing

1. Fork the repository
2. Create your feature branch
3. Commit your changes
4. Push to the branch
5. Create a Pull Request

## License

This project is part of the 42 school curriculum and follows its guidelines and restrictions. 