#!/bin/bash

# Path to your minishell binary
MINISHELL="./minishell"

# Temporary files for storing output
BASH_OUT="424_to_548_bash_output.txt"
MINISHELL_OUT="424_to_548_minishell_output.txt"

# List of commands to test
TEST_COMMANDS=(
'mkdir a'
'mkdir a/b'
'cd a/b'
'rm -r ../../a'
'cd ..'
'mkdir a'
'mkdir a/b'
'cd a/b'
'rm -r ../../a'
'pwd'
'mkdir a'
'mkdir a/b'
'cd a/b'
'rm -r ../../a'
'echo $PWD'
'echo $OLDPWD'
'mkdir a'
'mkdir a/b'
'cd a/b'
'rm -r ../../a'
'cd'
'echo $PWD'
'echo $OLDPWD'
'mkdir a'
'cd a'
'rm -r ../a'
'echo $PWD'
'echo $OLDPWD'
'export CDPATH=/'
'cd $HOME/..'
'export CDPATH=/'
'cd home/vietdu91'
'export CDPATH=./'
'cd .'
'export CDPATH=./'
'cd ..'
'chmod 777 minishell'
'./minishell'
'chmod 777 minishell'
'ls hola'
'./Makefile'
'./minishell'
'env | grep SHLVL'
'./minishell'
'env | grep SHLVL'
'exit'
'env | grep SHLVL'
'touch hola'
'./hola'
'env|"wc" -l'
'env|"wc "-l'
'expr 1 + 1'
'expr $? + $?'
'env -i ./minishell'
'env'
'env -i ./minishell'
'export'
'env -i ./minishell'
'cd'
'env -i ./minishell'
'cd ~'
'exit'
'exit exit'
'exit hola'
'exit hola que tal'
'exit 42'
'exit 000042'
'exit 666'
'exit 666 666'
'exit -666 666'
'exit hola 666'
'exit 666 666 666 666'
'exit 666 hola 666'
'exit hola 666 666'
'exit 259'
'exit -4'
'exit -42'
'exit -0000042'
'exit -259'
'exit -666'
'exit +666'
'exit 0'
'exit +0'
'exit -0'
'exit +42'
'exit -69 -96'
'exit --666'
'exit ++++666'
'exit ++++++0'
'exit ------0'
'exit "666"'
'exit '666''
'exit '-666''
'exit '+666''
'exit '----666''
'exit '++++666''
'exit '6'66'
'exit '2'66'32''
'exit "'666'"'
'exit '"666"''
'exit '666'"666"666'
'exit +'666'"666"666'
'exit -'666'"666"666'
'exit 9223372036854775807'
'exit 9223372036854775808'
'exit -9223372036854775808'
'exit -9223372036854775809'
'cat | cat | cat | ls'
'ls | exit'
'ls | exit 42'
'exit | ls'
'echo hola > bonjour'
'exit | cat -e bonjour'
'echo hola > bonjour'
'cat -e bonjour | exit'
'echo | echo'
'echo hola | echo que tal'
'pwd | echo hola'
'env | echo hola'
'echo oui | cat -e'
'echo oui | echo non | echo hola | grep oui'
'echo oui | echo non | echo hola | grep non'
'echo oui | echo non | echo hola | grep hola'
'echo hola | cat -e | cat -e | cat -e'
'cd .. | echo "hola"'
'cd / | echo "hola"'
'cd .. | pwd'
'ifconfig | grep ":"'
'ifconfig | grep hola'
'whoami | grep $USER'
'whoami | grep $USER > /tmp/bonjour'
'cat /tmp/bonjour'
'whoami | cat -e | cat -e > /tmp/bonjour'
'cat /tmp/bonjour'
'whereis ls | cat -e | cat -e > /tmp/bonjour'
'cat /tmp/bonjour'
'ls | hola'
'ls | ls hola'
'ls | ls | hola'
'ls | hola | ls'
'ls | ls | hola | rev'
'ls | ls | echo hola | rev'
'ls -la | grep "."'
'ls -la | grep "'.'"'
'echo test.c | cat -e| cat -e| cat -e| cat -e| cat -e| cat -e| cat -e| cat -e|cat -e|cat -e|cat -e'
'ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls'
'|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls|ls'
'echo hola | cat | cat | cat | cat | cat | grep hola'
'echo hola | cat'
'echo hola| cat'
'echo hola |cat'
'echo hola|cat'
'echo hola || cat'
'echo hola ||| cat'
'ech|o hola | cat'
'cat Makefile | cat -e | cat -e'
'cat Makefile | grep srcs | cat -e'
'cat Makefile | grep srcs | grep srcs | cat -e'
'cat Makefile | grep pr | head -n 5 | cd file_not_exist'
'cat Makefile | grep pr | head -n 5 | hello'
'export HOLA=bonjour | cat -e | cat -e'
'unset HOLA | cat -e'
'export HOLA | echo hola'
'env | grep PROUT'
'export | echo hola'
'sleep 3 | sleep 3'
'time sleep 3 | sleep 3'
'sleep 3 | exit'
'exit | sleep 3'
'echo hola > a'
'>>b echo que tal'
'cat a | <b cat | cat > c | cat'

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

