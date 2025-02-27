#!/bin/bash

MINISHELL="./minishell"

BASH_OUT="bash_output.txt"
MINISHELL_RAW="minishell_raw.txt"
MINISHELL_OUT="minishell_output.txt"

TEST_COMMANDS=(
	"ECHO (no environment)"
	'unset PATH; echo hello world'
	'unset PATH; echo $USER'
	'unset PATH; echo $PATH'
)

echo "Running tests..."

for cmd in "${TEST_COMMANDS[@]}"; do
	#Run command in Bash and save output
	echo "$cmd" | bash > "$BASH_OUT" 2>&1
	#Run command in Minishell and save output
	echo "$cmd" | $MINISHELL > "$MINISHELL_RAW" 2>&1
	# Remove the first line containing the prompt (minishell>>>)
	 sed '1d; s/minishell>>>//g' "$MINISHELL_RAW" | sed '/^$/d' > "$MINISHELL_OUT"
	 sed 's/[[:space:]]*$//' "$BASH_OUT" | tr -d '\r' > "$BASH_OUT.norm"
	#Compare outputs
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
