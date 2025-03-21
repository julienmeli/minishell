#!/bin/bash

# Path to your minishell binary
MINISHELL="./minishell"

# Temporary files for storing output
BASH_OUT="6_bash_output.txt"
MINISHELL_OUT="6_minishell_output.txt"

# List of commands to test
TEST_COMMANDS=(
'echo hola > bonjour'
'cat bonjour'
'echo que tal >> bonjour'
'cat bonjour'
'echo hola > bonjour'
'echo que tal >> bonjour'
'cat < bonjour'
'echo hola > bonjour'
'rm bonjour'
'echo que tal >> bonjour'
'cat < bonjour'
'echo hola que tal > bonjour'
'cat bonjour'
'echo hola que tal > /tmp/bonjour'
'cat -e /tmp/bonjour'
'export HOLA=hey'
'echo bonjour > $HOLA'
'echo $HOLA'
'whereis grep > Docs/bonjour'
'cat Docs/bonjour'
'ls -la > Docs/bonjour'
'cat Docs/bonjour'
'pwd>bonjour'
'cat bonjour'
'pwd >                     bonjour'
'cat bonjour'
'echo hola > > bonjour'
'echo hola < < bonjour'
'echo hola >>> bonjour'
'> bonjour echo hola'
'cat bonjour'
'> bonjour | echo hola'
'cat bonjour'
'prout hola > bonjour'
'ls'
'echo hola > hello >> hello >> hello'
'ls'
'cat hello'
'echo hola > hello >> hello >> hello'
'echo hola >> hello'
'cat < hello'
'echo hola > hello >> hello >> hello'
'echo hola >> hello'
'echo hola > hello >> hello >> hello'
'cat < hello'
'echo hola >> hello >> hello > hello'
'echo hola >> hello'
'cat < hello'
'echo hola >> hello >> hello > hello'
'echo hola >> hello'
'echo hola >> hello >> hello > hello'
'cat < hello'
'echo hola > hello'
'echo hola >> hello >> hello >> hello'
'echo hola >> hello'
'cat < hello'
'echo hola > hello'
'echo hey > bonjour'
'echo <bonjour <hello'
'echo hola > hello'
'echo hey > bonjour'
'echo <hello <bonjour'
'echo hola > bonjour'
'echo hey > hello'
'rm bonjour hello'
'echo hola > bonjour > hello > bonjour'
'cat bonjour'
'cat hello'
'echo hola > bonjour'
'echo hey > hello'
'echo hola > bonjour > hello > bonjour'
'cat bonjour'
'cat hello'
'echo hola > bonjour'
'echo hey > hello'
'rm bonjour hello'
'echo hola > bonjour >> hello > bonjour'
'cat bonjour'
'cat hello'
'echo hola > bonjour'
'echo hey > hello'
'echo hola > bonjour > hello > bonjour'
'cat bonjour'
'cat hello'
'echo hola > bonjour'
'echo hey > hello'
'rm bonjour hello'
'echo hola > bonjour > hello >> bonjour'
'cat bonjour'
'cat hello'
'echo hola > bonjour'
'echo hey > hello'
'echo hola > bonjour > hello >> bonjour'
'cat bonjour'
'cat hello'
'echo hola > bonjour'
'echo hey > hello'
'rm bonjour hello'
'echo hola >> bonjour > hello > bonjour'
'cat bonjour'
'cat hello'
'echo hola > bonjour'
'echo hey > hello'
'echo hola >> bonjour > hello > bonjour'
'cat bonjour'
'cat hello'
'echo hola > bonjour'
'echo hey > hello'
'rm bonjour hello'
'echo hola >> bonjour >> hello >> bonjour'
'cat bonjour'
'cat hello'
'echo hola > bonjour'
'echo hey > hello'
'echo hola >> bonjour >> hello >> bonjour'
'cat bonjour'
'cat hello'
'> bonjour echo hola bonjour'
'cat bonjour'
'>bonjour echo > hola>bonjour>hola>>bonjour>hola hey >bonjour hola >hola'
'cat bonjour'
'cat hola'
'echo bonjour > hola1'
'echo hello > hola2'
'echo 2 >hola1 >> hola2'
'ls'
'cat hola1'
'cat hola2'
'echo bonjour > hola1'
'echo hello > hola2'
'echo 2 >>hola1 > hola2'
'ls'
'cat hola1'
'cat hola2'
'> pwd'
'ls'
'< pwd'
'< Makefile .'
'cat <pwd'
'cat <srcs/pwd'
'cat <../pwd'
'cat >>'
'cat >>>'
'cat >> <<'
'cat >> > >> << >>'
'cat < ls'
'cat < ls > ls'
'cat > ls1 < ls2'
'ls'
'>>hola'
'cat hola'
'echo hola > bonjour'
'cat < bonjour'
'echo hola >bonjour'
'cat <bonjour'
'echo hola>bonjour'
'cat<bonjour'
'echo hola> bonjour'
'cat< bonjour'
'echo hola               >bonjour'
'cat<                     bonjour'
'echo hola          >     bonjour'
'cat            <         bonjour'
'echo hola > srcs/bonjour'
'cat < srcs/bonjour'
'echo hola >srcs/bonjour'
'cat <srcs/bonjour'
'echo hola > bonjour'
'echo que tal >> bonjour'
'cat < bonjour'
'echo hola > bonjour'
'rm bonjour'
'echo que tal >> bonjour'
'cat < bonjour'
'e'c'"h"o hola > bonjour'
'cat 'bo'"n"jour'
'echo hola > bonjour\ 1'
'ls'
'cat bonjour\ 1'
'echo hola > bonjour hey'
'ls'
'cat bonjour'
'cat hey'
'echo hola > srcs/bonjour'
'echo hey > srcs/hello'
'>srcs/bonjour >srcs/hello <prout'
'cat srcs/bonjour srcs/hello'
'echo hola > srcs/bonjour'
'echo hey > srcs/hello'
'rm srcs/bonjour srcs/hello'
'>srcs/bonjour >srcs/hello <prout'
'ls srcs'
'cat srcs/bonjour srcs/hello'
'echo hola > srcs/bonjour'
'echo hey > srcs/hello'
'>srcs/bonjour <prout >srcs/hello '
'cat srcs/bonjour '
'cat srcs/hello'
'echo hola > srcs/bonjour'
'echo hey > srcs/hello'
'rm srcs/bonjour srcs/hello'
'>srcs/bonjour <prout >srcs/hello '
'ls srcs'
'cat srcs/bonjour'
'echo hola > ../bonjour'
'echo hey > ../hello'
'>../bonjour >../hello <prout'
'cat ../bonjour ../hello'
'echo hola > ../bonjour'
'echo hey > ../hello'
'rm ../bonjour ../hello'
'>../bonjour >../hello <prout'
'ls ..'
'cat ../bonjour ../hello'
'echo hola > ../bonjour'
'echo hey > ../hello'
'>../bonjour <prout >../hello '
'cat ../bonjour '
'cat ../hello'
'echo hola > ../bonjour'
'echo hey > ../hello'
'rm ../bonjour ../hello'
'>../bonjour <prout >../hello '
'ls ..'
'cat ../bonjour'
'echo hola > srcs/bonjour'
'echo hey > srcs/hello'
'>srcs/bonjour >>srcs/hello <prout'
'cat srcs/bonjour '
'cat srcs/hello'
'echo hola > srcs/bonjour'
'echo hey > srcs/hello'
'>>srcs/bonjour >srcs/hello <prout'
'cat srcs/bonjour '
'cat srcs/hello'
'echo hola > srcs/bonjour'
'echo hey > srcs/hello'
'>>srcs/bonjour >>srcs/hello <prout'
'cat srcs/bonjour '
'cat srcs/hello'
'echo hola > srcs/bonjour'
'echo hey > srcs/hello'
'>srcs/bonjour <prout >>srcs/hello'
'cat srcs/bonjour '
'cat srcs/hello'
'echo hola > srcs/bonjour'
'echo hey > srcs/hello'
'>>srcs/bonjour <prout >srcs/hello'
'cat srcs/bonjour '
'cat srcs/hello'
'echo hola > srcs/bonjour'
'echo hey > srcs/hello'
'>>srcs/bonjour <prout >>srcs/hello'
'cat srcs/bonjour '
'cat srcs/hello'
'echo hola > srcs/bonjour'
'echo hey > srcs/hello'
'<prout >>srcs/bonjour >>srcs/hello'
'cat srcs/bonjour '
'cat srcs/hello'
'echo hola > bonjour'
'echo hey > hello'
'<bonjour >hello'
'cat bonjour '
'cat hello'
'echo hola > bonjour'
'echo hey > hello'
'>bonjour >hello < prout'
'cat bonjour '
'cat hello'
'echo hola > bonjour'
'echo hey > hello'
'rm bonjour hello'
'>bonjour >hello < prout'
'cat bonjour '
'cat hello'
'echo hola > bonjour'
'echo hey > hello'
'>bonjour <prout hello'
'cat bonjour '
'cat hello'
'echo hola > bonjour'
'echo hey > hello'
'rm bonjour hello'
'>bonjour <prout hello'
'cat bonjour '
'echo hola > bonjour'
'<bonjour cat | wc > bonjour'
'cat bonjour'
'rm -f bonjour'
'rm bonjour > bonjour'
'ls -l bonjour'
'export HOLA="bonjour hello"'
'>$HOLA'
'ls'
'export HOLA="bonjour hello"'
'>"$HOLA"'
'ls'
'export HOLA="bonjour hello"'
'>$"HOLA"'
'ls'
'export HOLA="bonjour hello"'
'>$HOLA>hey'
'ls'
'export HOLA="bonjour hello"'
'>hey>$HOLA'
'ls'
'export HOLA="bonjour hello"'
'>hey>$HOLA>hey>hey'
'ls'
'export A=hey'
'export A B=Hola D E C="Que Tal"'
'echo $PROUT$B$C > /tmp/a > /tmp/b > /tmp/c'
'cat /tmp/a'
'cat /tmp/b'
'cat /tmp/c'

)

counter=1

# Run tests
echo "Running tests..."
for cmd in "${TEST_COMMANDS[@]}"; do
    # Run command in Bash and save output
    #echo "[$counter] cmd:$cmd cmdend" >> "$BASH_OUT"
    #echo "$cmd" | bash >> "$BASH_OUT" 2>&1
	#echo "[$counter]------------------------" >> "$BASH_OUT"

    # Run command in Minishell and save output
    echo "[$counter]-----------------" >> "$MINISHELL_OUT"
    echo "$cmd" | $MINISHELL >> "$MINISHELL_OUT" 2>&1
    	echo "[$counter]-----------------------" >> "$MINISHELL_OUT"

	((counter++))
    # Compare outputs
    if diff -q "$BASH_OUT" "$MINISHELL_OUT" > /dev/null; then
        echo "[✅] Test passed: $cmd"
    else
        echo "[❌] Test failed: $cmd"
	sleep 0.05
echo "Expected output:"
    cat "$BASH_OUT"
    echo "Your minishell output:"
    cat "$MINISHELL_OUT"
    fi
done

# Cleanup temporary files
#rm -f "$BASH_OUT" "$MINISHELL_OUT"

echo "Testing completed!"

