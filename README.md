*This project has been created as part of the 42 curriculum by jiyanwang, mhnatovs*

# minishell

## Description

`minishell` is a simplified Unix shell built for educational purposes as part of the 42 curriculum. Its goal is to help students understand the fundamentals of command-line interpreters, process management, parsing, and I/O redirection. The project aims to replicate the core behavior of a shell, accepting user commands, executing them, handling errors, and managing environment variables and reacting to system signals.

The shell reads commands, applies quoting and variable‑expansion rules, runs built‑in functions, and executes external programs found through the PATH variable. It supports input/output redirections, pipelines, and heredocs, allowing users to combine commands and control data flow much like in Bash. Minishell also manages environment variables, including $?, which stores the exit status of the last executed command.

Signal handling is an important part of the project. Minishell must react to Ctrl‑C, Ctrl‑D, and Ctrl‑\ the same way Bash does in interactive mode, without breaking its internal state. The project allows using only one global variable to track signals, ensuring that signal handlers stay simple and safe.

By building Minishell, students learn how command interpreters work, how processes interact, and how Unix systems manage execution. The project encourages clean structure, modular code, and careful memory management, resulting in a functional and reliable mini‑shell.

## Instructions
#### Installation
Clone the repo:
```bash
git clone https://github.com/Fiona-87327/minishell.git
```

To compile the project, run:
```bash
make
```
To remove object files in obj directory:
```bash
make clean
```
To remove everything including the executable:
```bash
make fclean
```
To rebuild from scratch:
```bash
make re
```

###### Use commands:
###### Builtins
- echo (with -n)
- cd
- pwd
- export
- unset
- env
- exit

###### Shell behavior
- Environment variable expansion ($USER, $HOME, $?, etc.)
- Single and double quotes handling
- Pipes (|)
- Redirections (>, >>, <, <<)
- Heredoc with correct quote behavior
- Signal handling (Ctrl-C, Ctrl-D, Ctrl-\)
- Execution of external binaries via PATH

### Technical Overview

#### Parsing
The shell uses a multi-stage parsing pipeline:

Lexer — tokenizes the input string

Syntax checker — validates token sequences

Parser — builds a command structure and resolves environment variables

Executor — runs builtins or external commands

#### Execution Model
Builtins without pipes run in the parent process

Commands in pipelines run in child processes

Redirections are applied before execution

Exit status is tracked and updated according to Bash rules

## Resources

- [GNU Bash Manual](https://www.gnu.org/software/bash/manual/bash.pdf)
- Linux man pages (man bash, man execve, man dup2, man pipe, man fork)
- “Unix Processes in C” tutorials
- https://mywiki.wooledge.org/BashParser
- https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf
- https://m4nnb3ll.medium.com/minishell-building-a-mini-bash-a-42-project-b55a10598218
- https://www.manpagez.com/info/rlman/rlman-6.0/rlman_43.php

### AI Usage

AI tools (such as GitHub Copilot or ChatGPT) were used to:
- Review edge-case handling in built-in command execution
- Clarifying Bash behavior in some cases
- Debugging logic and identifying incorrect behavior
- Improving code structure and readability
- Generating documentation
- Validating parsing and execution rules
