

# 🐚 Minishell - A simple Unix Shell

![C](https://img.shields.io/badge/Language-C-blue.svg)
![42](https://img.shields.io/badge/42-Project-success.svg)
![License](https://img.shields.io/badge/License-MIT-lightgrey.svg)

*This project has been created as part of the 42 curriculum by jiyanwang, mhnatovs*

`minishell` is a core project of the 42 curriculum, designed to implement a simplified Unix shell from scratch. This project involves a deep dive into process management, system calls, signal handling, and complex string parsing.

---

## 📖 Table of Contents
- [Project Description](#project-description)
- [Core Features](#core-features)
- [Built-in Commands](#built-in-commands)
- [Quick Start](#quick-start)
- [Usage Examples](#usage-examples)
- [Technical Architecture](#technical-architecture)
- [Resources](#resources)

---

## 📝 Project Description
`minishell` is a lightweight simulation of Bash. It reads user commands, handles quotes and environment variable expansions, combines programs using pipes and redirections, and reacts to system signals (such as `Ctrl-C`, `Ctrl-D`, `Ctrl-\`) just like a real Bash environment.

The project demands high-quality code, strict memory management (zero leaks allowed), and a profound understanding of Unix internals like Inter-Process Communication (IPC) and File Descriptors.

---

## ✨ Core Features
- **Interactive Command Handling**: Support for command history using the `readline` library.
- **Process Management**: Execution of external binaries via `fork` and `execve` using the `PATH`.
- **Redirections**:
  - Input redirection `<`
  - Output redirection `>`
  - Append mode redirection `>>`
  - Heredoc `<<` with support for delimiters and signal interruption.
- **Pipes**: Multi-stage piping `|` to pass data flow between commands.
- **Parsing Logic**:
  - Single quotes `' '` (literal interpretation).
  - Double quotes `" "` (supports variable expansion).
  - Environment variable expansion (e.g., `$USER`, `$HOME`, `$?`).
- **Signal Handling**: Accurate simulation of Bash's behavior in interactive mode.

---

## 🛠 Built-in Commands
The following standard Bash built-ins are implemented:
- `echo` (with `-n` option)
- `cd` (supports relative and absolute paths)
- `pwd`
- `export` (manages environment variables)
- `unset`
- `env`
- `exit`

---

## 🚀 Quick Start

### Installation
Clone the repository:
```bash
git clone https://github.com/Fiona-87327/42Core_minishell.git
cd 42Core_minishell
```

### Compilation
Use the provided `Makefile` to compile:
```bash
make        # Compiles the 'minishell' executable
make clean  # Removes object files
make fclean # Removes object files and the executable
make re     # Recompiles from scratch
```

### Execution
```bash
./minishell
```

---

## 💡 Usage Examples

**1. Basic Pipes and Redirection**
```bash
minishell> ls -l | grep "m" > result.txt
minishell> cat < result.txt
```

**2. Environment Variable Expansion**
```bash
minishell> echo "Hello $USER, status of last command: $?"
```

**3. Multi-Piping**
```bash
minishell> cat Makefile | grep "CC" | wc -l
```

---

## 🏗 Technical Architecture

### Parsing Pipeline
The shell processes input through a multi-stage pipeline:
1. **Lexer**: Tokenizes the raw input string into meaningful units.
2. **Syntax Checker**: Validates the sequence of tokens (e.g., preventing `| |`).
3. **Parser**: Builds a command structure and resolves environment variables.
4. **Executor**: 
   - Runs built-ins in the parent process if no pipes are present.
   - Forks child processes for external commands and pipelines.
   - Manages `dup2` for file descriptor redirections.

### Signal Strategy
- Uses a single global variable to track signals as per 42 constraints.
- **Ctrl-C**: Displays a new prompt on a new line.
- **Ctrl-D**: Quits the shell (EOF).
- **Ctrl-\**: Does nothing in interactive mode to match Bash behavior.

---

## 📚 Resources
- [GNU Bash Manual](https://www.gnu.org/software/bash/manual/bash.pdf)
- [The Bash Parser Wiki](https://mywiki.wooledge.org/BashParser)
- [Unix Processes in C - Tutorials](https://www.youtube.com/playlist?list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY)

---

## 👥 Authors
- **jiyanwang**
- **mhnatovs**

---

## 🤖 AI Usage
AI tools (such as GitHub Copilot or ChatGPT) were utilized to:
- Review edge-case handling in execution logic.
- Debug complex parsing scenarios.
- Improve code readability and documentation structure.
