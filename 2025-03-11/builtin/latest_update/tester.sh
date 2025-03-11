#!/bin/bash

# Path to your minishell binary
MINISHELL="./minishell"

# Temporary files for storing output
BASH_OUT="bash_output.txt"
MINISHELL_OUT="minishell_output.txt"

# List of commands to test
TEST_COMMANDS=(
    "echo Hello, world!"
    "pwd"
    "ls -l"
    "export TEST_VAR=42 && echo \$TEST_VAR"
    "unset TEST_VAR && echo \$TEST_VAR"
    "cd / && pwd"
    "cd .. && pwd"
    "echo \$HOME"
    "exit"
)

# Run tests
echo "Running tests..."
for cmd in "${TEST_COMMANDS[@]}"; do
    # Run command in Bash and save output
    echo "$cmd" | bash > "$BASH_OUT" 2>&1

    # Run command in Minishell and save output
    echo "$cmd" | $MINISHELL > "$MINISHELL_OUT" 2>&1

    # Compare outputs
    if diff -q "$BASH_OUT" "$MINISHELL_OUT" > /dev/null; then
        echo "[✅] Test passed: $cmd"
    else
        echo "[❌] Test failed: $cmd"
        echo "Expected output:"
        cat "$BASH_OUT"
        echo "Your minishell output:"
        cat "$MINISHELL_OUT"
    fi
done

# Cleanup temporary files
rm -f "$BASH_OUT" "$MINISHELL_OUT"

echo "Testing completed!"

