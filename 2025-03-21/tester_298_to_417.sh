#!/bin/bash

# Path to your minishell binary
MINISHELL="./minishell"

# Temporary files for storing output
BASH_OUT="298_to_417_bash_output.txt"
MINISHELL_OUT="298_to_417_minishell_output.txt"

# List of commands to test
TEST_COMMANDS=(
'export HOLA=p'
'export BYE=w'
'"$HOLA"'$BYE'd'
'export HOLA=p'
'export BYE=w'
'"$HOLA""$BYE"d'
'export HOLA=p'
'export BYE=w'
'$"HOLA"$"BYE"d'
'export HOLA=p'
'export BYE=w'
'$'HOLA'$'BYE'd'
'export HOLA=-n'
'"echo $HOLA" hey'
'export A=1 B=2 C=3 D=4 E=5 F=6 G=7 H=8'
#'echo "$A'$B"'$C"$D'$E'"$F'"'$G'$H"'
'export HOLA=bonjour'
'env'
'unset HOLA'
'env'
'export HOLA=bonjour'
'env'
'unset HOLA'
'unset HOLA'
'env'
'unset PATH'
'echo $PATH'
'unset PATH'
'ls'
'unset ""'
'unset INEXISTANT'
'unset PWD'
'env | grep PWD'
'pwd'
'pwd'
'unset PWD'
'env | grep PWD'
'cd $PWD'
'pwd'
'unset OLDPWD'
'env | grep OLDPWD'
'unset 9HOLA'
'unset HOLA9'
'unset HOL?A'
'unset HOLA HOL?A'
'unset HOL?A HOLA'
'unset HOL?A HOL.A'
'unset HOLA='
'unset HOL\\\\A'
'unset HOL;A'
'unset HOL.A'
'unset HOL+A'
'unset HOL=A'
'unset HOL{A'
'unset HOL}A'
'unset HOL-A'
'unset -HOLA'
'unset _HOLA'
'unset HOL_A'
'unset HOLA_'
'unset HOL*A'
'unset HOL#A'
'unset $HOLA'
'unset $PWD'
'unset HOL@'
'unset HOL!A'
'unset HOL^A'
'unset HOL$?A'
'unset HOL\~A'
'unset "" HOLA'
'env | grep HOLA'
'unset PATH'
'echo $PATH'
'unset PATH'
'cat Makefile'
'unset ='
'unset ======'
'unset ++++++'
'unset _______'
'unset export'
'unset echo'
'unset pwd'
'unset cd'
'unset unset'
'unset sudo'
'export hola | unset hola | echo $?'
'/bin/echo'
'/bin/echo Hola Que Tal'
'/bin/env'
'/bin/cd Desktop'
'history'
'[touche du haut]'
'pwd'
'pwd hola'
'pwd ./hola'
'pwd hola que tal'
'pwd -p'
'pwd --p'
'pwd ---p'
'pwd -- p'
'pwd pwd pwd'
'pwd ls'
'pwd ls env'
'cd'
'cd .'
'cd ./'
'cd ./././.'
'cd ././././'
'cd ..'
'cd ../'
'cd ../..'
'cd ../.'
'cd .././././.'
'cd srcs'
'cd srcs objs'
'cd 'srcs''
'cd "srcs"'
'cd '/etc''
'cd /e'tc''
'cd /e"tc"'
'cd sr'
'cd Makefile'
'cd ../minishell'
'cd ../../../../../../..'
'cd .././../.././../bin/ls'
'cd /'
'cd '/''
'cd //'
'pwd'
'cd '//''
'pwd'
'cd ///'
'pwd'
'cd ////////'
'pwd'
'cd '////////''
'pwd'
'cd /minishell'
'cd /'
'cd ..'
'cd _'
'cd -'
'cd --'
'cd ---'
'cd $HOME'
'cd $HOME $HOME'
'cd $HOME/42_works'
'cd "$PWD/srcs"'
'cd '$PWD/srcs''
'unset HOME'
'cd $HOME'
'unset HOME'
'export HOME='
'cd'
'unset HOME'
'export HOME'
'cd'
'cd minishell Docs crashtest.c'
'cd / | echo $?'
'pwd'

)

counter=1

# Run tests
echo "Running tests..."
for cmd in "${TEST_COMMANDS[@]}"; do
    # Run command in Bash and save output
    echo "[$counter] cmd:$cmd cmdend" >> "$BASH_OUT"
    echo "$cmd" | bash >> "$BASH_OUT" 2>&1
	echo "[$counter]------------------------" >> "$BASH_OUT"

    # Run command in Minishell and save output
    #echo "[$counter]-----------------" >> "$MINISHELL_OUT"
    #echo "$cmd" | $MINISHELL >> "$MINISHELL_OUT" 2>&1
    	#echo "[$counter]-----------------------" >> "$MINISHELL_OUT"

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

