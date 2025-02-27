#!/bin/bash

MINISHELL="./minishell"

BASH_OUT="bash_output.txt"
MINISHELL_RAW="minishell_raw.txt"
MINISHELL_OUT="minishell_output.txt"

TEST_COMMANDS=(
	"echo Hello, world!"
	"pwd"
	'ECHO'
	'Echo'
	'echo'
	'echo hello'
	'echo hello'
	'echo hello world'
	'echo hello      world'
	'echo                      hello world'
	'echo hello world                '
	'echo helololollllolllolol loollolllololllol lllol  looololololollllloooolll'
	'echo helololollllolllolol                                 loollolllololllol                   lllol                looololololollllloooolll'
	'echo -n'
	'echo -n hello world'
	'echo hello      world'
	'echo                      hello world'
	'echo -n hello world                '
	'echo -n helololollllolllolol loollolllololllol lllol  looololololollllloooolll'
	'echo -n helololollllolllolol                                 loollolllololllol                   lllol                looololololollllloooolll'
	'echo hello -n'
	'             echo                 hello                world'
	'             echo             -n                  hello               world                       '
	"echo a '' b '' c '' d"
	'echo a "" b "" c "" d'
	"echo -n a '' b '' c '' d"
	'echo -n a "" b "" c "" d'
	'echo -nhello world'
	'echo -n -n -n hello world'
	'echo -n -n -nnnn -nnnnm'
	'echo a
	'echo -n -nnn hello -n'
	'echo a
)

echo "Running tests..."

for test in "${TESTS[@]}"; do
    EXPECTED_OUTPUT=$(bash -c "$test")  # Get expected output from bash
    ACTUAL_OUTPUT=$(echo "$test" | $MINISHELL_EXEC | tail -n +2)  # Run in minishell and remove first line (prompt)

    if [ "$ACTUAL_OUTPUT" == "$EXPECTED_OUTPUT" ]; then
        echo "[✅] Test passed: $test"
    else
        echo "[❌] Test failed: $test"
        echo "Expected output:"
        echo "$EXPECTED_OUTPUT"
        echo "Your minishell output:"
        echo "$ACTUAL_OUTPUT"
    fi
done

# Cleanup temporary files

rm -f "$BASH_OUT" "$MINISHELL_OUT" "$MINISHELL_RAW"

echo "Testing completed!"
