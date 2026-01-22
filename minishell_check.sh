#!/bin/bash

MINISHELL=./minishell

run_test() {
    CMD="$1"

    echo "=============================="
    echo "COMMAND: $CMD"
    echo "=============================="

    MINI_OUT=$(printf "%s\nexit\n" "$CMD" | $MINISHELL 2>mini_err | sed 's/^minishell\$ //g')
    MINI_STATUS=$?

    BASH_OUT=$(printf "%s\n" "$CMD" | bash 2>bash_err)
    BASH_STATUS=$?

    if [ "$MINI_OUT" = "$BASH_OUT" ] && [ "$MINI_STATUS" = "$BASH_STATUS" ]; then
        echo "OK"
    else
        echo "KO"
        echo "--- minishell output ---"
        echo "$MINI_OUT"
        echo "--- bash output ---"
        echo "$BASH_OUT"
        echo "--- minishell status: $MINI_STATUS"
        echo "--- bash status: $BASH_STATUS"
    fi
}

# ===== BASIC =====
run_test "pwd"
run_test "echo hello"
run_test "echo -n hello"
run_test "echo \$HOME"
run_test "echo \$?"

# ===== BUILTINS =====
run_test "export TEST=42"
run_test "echo \$TEST"
run_test "unset TEST"
run_test "echo \$TEST"

# ===== REDIRECTIONS =====
run_test "echo hello > file"
run_test "cat < file"
run_test "echo world >> file"
run_test "cat file"
rm -f file

# ===== PIPES =====
run_test "echo hello | wc -c"
run_test "ls | wc -l"

# ===== QUOTES =====
run_test "echo 'hello world'"
run_test "echo \"hello \$HOME\""

# ===== ERRORS =====
run_test "| ls"
run_test "echo hello | | wc"
run_test "pwd -x"
run_test "echo 'unclosed"
