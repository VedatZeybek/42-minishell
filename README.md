# 🐚 Minishell

<div align="center">

![42 School](https://img.shields.io/badge/42-School-000000?style=for-the-badge&logo=42&logoColor=white)
![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)

**A minimal UNIX shell implementation**

_As beautiful as a shell_ 🐚

</div>

---

## 📋 Table of Contents

- [About](#about)
- [Features](#features)
- [Project Structure](#project-structure)
- [Installation](#installation)
- [Usage](#usage)
- [Built-in Commands](#built-in-commands)
- [Technical Implementation](#technical-implementation)
- [Authors](#authors)
- [Acknowledgments](#acknowledgments)

---

## 🎯 About

**Minishell** is a project from the 42 School curriculum that challenges students to create their own shell, similar to bash. This project provides a deep understanding of processes, file descriptors, pipes, redirections, and the inner workings of UNIX shells.

The goal is to create a simple yet functional shell that can:

- Execute commands with their parameters
- Handle environment variables
- Implement redirections and pipes
- Provide built-in commands
- Manage signals properly

---

## ✨ Features

### Command Execution

- ✅ Execute commands from PATH
- ✅ Execute commands with absolute/relative paths
- ✅ Handle command arguments

### Redirections

- ✅ Input redirection (`<`)
- ✅ Output redirection (`>`)
- ✅ Append mode (`>>`)
- ✅ Here-document (`<<`)

### Pipes

- ✅ Multiple pipe support (`|`)
- ✅ Proper pipe chaining

### Quote Handling

- ✅ Single quotes (`'`) - prevent interpretation
- ✅ Double quotes (`"`) - allow variable expansion

### Environment Variables

- ✅ Variable expansion (`$VAR`)
- ✅ Exit status expansion (`$?`)
- ✅ Environment variable management

### Signal Handling

- ✅ `ctrl-C` - Interrupt (SIGINT)
- ✅ `ctrl-D` - Exit shell (EOF)
- ✅ `ctrl-\` - Quit (SIGQUIT)

### Built-in Commands

- ✅ `echo` with `-n` option
- ✅ `cd` with relative/absolute paths
- ✅ `pwd` (no options)
- ✅ `export` (no options)
- ✅ `unset` (no options)
- ✅ `env` (no options or arguments)
- ✅ `exit` (no options)

---

## 📁 Project Structure

```
minishell/
├── includes/
│   └── minishell.h          # Main header file with structures and prototypes
├── libft/                   # Custom C library
│   ├── *.c                  # Library functions
│   ├── libft.h
│   ├── get_next_line.c
│   └── Makefile
├── srcs/
│   ├── builtin/            # Built-in command implementations
│   │   ├── ft_cd.c
│   │   ├── ft_echo.c
│   │   ├── ft_env.c
│   │   ├── ft_exit.c
│   │   ├── ft_export.c
│   │   ├── ft_pwd.c
│   │   ├── ft_unset.c
│   │   └── ft_utils.c
│   ├── executor/           # Command execution logic
│   │   ├── ft_executor.c
│   │   ├── ft_exec_pipe.c
│   │   ├── ft_cmd_exec.c
│   │   ├── ft_redirections.c
│   │   ├── ft_heredoc.c
│   │   └── ...
│   ├── input/              # Input handling
│   │   └── read_line.c
│   ├── lexer/              # Tokenization and lexical analysis
│   │   ├── tokenizer.c
│   │   ├── syntax_check.c
│   │   ├── append_env_var.c
│   │   └── ...
│   └── parser/             # Command parsing
│       ├── command_parser.c
│       └── ...
├── main.c                   # Entry point
├── Makefile
└── README.md
```

---

## 🚀 Installation

### Prerequisites

- GCC compiler
- GNU Make
- Readline library

#### Install readline on Ubuntu/Debian:

```bash
sudo apt-get install libreadline-dev
```

#### Install readline on macOS:

```bash
brew install readline
```

### Build

1. Clone the repository:

```bash
git clone https://github.com/VedatZeybek/42-minishell.git
cd 42-minishell
```

2. Compile the project:

```bash
make
```

3. Run the shell:

```bash
./minishell
```

### Clean up

```bash
make clean    # Remove object files
make fclean   # Remove object files and executable
make re       # Rebuild everything
```

---

## 💻 Usage

### Basic Examples

```bash
# Simple command execution
$ ls -la

# Pipes
$ cat file.txt | grep "pattern" | wc -l

# Redirections
$ echo "Hello World" > output.txt
$ cat < input.txt > output.txt

# Append redirection
$ echo "New line" >> output.txt

# Here-document
$ cat << EOF
> line 1
> line 2
> EOF

# Environment variables
$ echo $HOME
$ export MY_VAR="value"
$ echo $MY_VAR

# Exit status
$ ls non_existent_file
$ echo $?

# Quotes
$ echo "Hello $USER"    # Variable expansion
$ echo 'Hello $USER'    # Literal string
```

---

## 🔧 Built-in Commands

### `echo`

Print arguments to standard output.

```bash
$ echo Hello World
Hello World
$ echo -n "No newline"
No newline$
```

### `cd`

Change the current directory.

```bash
$ cd /path/to/directory
$ cd ..
$ cd ~
$ cd
```

### `pwd`

Print the current working directory.

```bash
$ pwd
/home/user/minishell
```

### `export`

Set environment variables.

```bash
$ export VAR=value
$ export PATH=$PATH:/new/path
```

### `unset`

Remove environment variables.

```bash
$ unset VAR
```

### `env`

Display all environment variables.

```bash
$ env
```

### `exit`

Exit the shell.

```bash
$ exit
$ exit 42
```

---

## 🛠 Technical Implementation

### Architecture

The minishell follows a three-stage pipeline architecture:

1. **Lexer (Tokenization)**

   - Reads input and splits into tokens
   - Identifies token types (words, operators, quotes, etc.)
   - Handles quote parsing and escape sequences

2. **Parser**

   - Builds command structures from tokens
   - Groups arguments and redirections
   - Creates command pipeline

3. **Executor**
   - Executes commands in the correct order
   - Handles pipes and redirections
   - Manages processes and file descriptors

### Key Data Structures

```c
// Token structure for lexical analysis
typedef struct s_token
{
    char            *value;
    t_token_type    type;
    struct s_token  *next;
} t_token;

// Command structure
typedef struct s_command
{
    t_arg           *argv;
    t_redir         *redirections;
    struct s_command *next;
} t_command;

// Environment variables and execution context
typedef struct s_vars
{
    char    **envp;
    char    **path;
} t_vars;
```

### Process Flow

1. Read user input using readline
2. Check for unclosed quotes
3. Tokenize input into token list
4. Perform syntax checking
5. Parse tokens into command structures
6. Execute commands (built-in or external)
7. Handle pipes and redirections
8. Update exit status
9. Free all allocated memory

### Memory Management

- All dynamically allocated memory is properly freed
- No memory leaks (verified with valgrind)
- Proper cleanup on exit and error conditions

### Signal Handling

- Signals are handled in both interactive and non-interactive modes
- Proper signal masking in child processes
- Clean terminal state on exit

---

## 👥 Authors

<table>
  <tr>
    <td align="center">
      <a href="https://github.com/VedatZeybek">
        <img src="https://github.com/VedatZeybek.png" width="100px;" alt="Vedat Zeybek"/>
        <br />
        <sub><b>Vedat Zeybek</b></sub>
      </a>
      <br />
      <a href="https://github.com/VedatZeybek" title="GitHub">🔗</a>
    </td>
    <td align="center">
      <a href="https://github.com/Ertugrul-Pakdamar">
        <img src="https://github.com/Ertugrul-Pakdamar.png" width="100px;" alt="Ertuğrul Pakdamar"/>
        <br />
        <sub><b>Ertuğrul Pakdamar</b></sub>
      </a>
      <br />
      <a href="https://github.com/Ertugrul-Pakdamar" title="GitHub">🔗</a>
    </td>
  </tr>
</table>

---

## 🙏 Acknowledgments

- **42 School** - For providing this challenging project
- **Bash & UNIX creators** - For inspiration and reference
- **The 42 Community** - For support and collaboration

---

<div align="center">

**Made with ❤️ at 42 School**

⭐ Star this repository if you found it helpful!

</div>
