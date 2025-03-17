#!/bin/bash

# Path to your minishell binary
MINISHELL="./minishell"

# Temporary files for storing output
BASH_OUT="0_bash_output.txt"
MINISHELL_OUT="0_minishell_output.txt"

# List of commands to test
TEST_COMMANDS=(
'TEST'
'\n (touche entrée)'
'[que des espaces]'
'[que des tabulations]'
':'
'!'
'>'
'<'
'>>'
'<<'
'<>'
'>>>>>'
'>>>>>>>>>>>>>>>'
'<<<<<'
'<<<<<<<<<<<<<<<<'
'> > > >'
'>> >> >> >>'
'>>>> >> >> >>'
'/'
'//'
'/.'
'/./../../../../..'
'///////'
'-'
'|'
'| hola'
'| | |'
'||'
'|||||'
'|||||||||||||'
'>>|><'
'&&'
'&&&&&'
'&&&&&&&&&&&&&&'
';;'
';;;;;'
';;;;;;;;;;;;;;;'
'()'
'( ( ) )'
'( ( ( ( ) ) ) )'
''
'hola'
'hola''
'''
'*'
'*/*'
'*/*'
'.'
'..'
'~'
'ABC=hola'
'4ABC=hola'
'hola'
'hola que tal'
'Makefile'
    	'echo'
'echo -n'
'echo Hola'
'echoHola'
'echo-nHola'
'echo -n Hola'
'echo "-n" Hola'
'echo -nHola'
'echo Hola -n'
'echo Hola Que Tal'
'echo         Hola'
'echo    Hola     Que    Tal'
'echo      \n hola'
'echo "         " | cat -e'
'echo           | cat -e'
'"''echo hola""'''' que""'' tal""'''
'echo -n -n'
'echo -n -n Hola Que'
'echo -p'
'echo -nnnnn'
'echo -n -nnn -nnnn'
'echo -n-nnn -nnnn'
'echo -n -nnn hola -nnnn'
'echo -n -nnn-nnnn'
'echo --------n'
'echo -nnn --------n'
'echo -nnn -----nn---nnnn'
'echo -nnn --------nnnn'
'echo $'
'echo $?'
'echo $?$'
'echo $? | echo $? | echo $?'
'echo $:$= | cat -e'
'echo " $ " | cat -e'
'echo ' $ ' | cat -e'
'echo $HOME'
'echo \$HOME'
'echo my shit terminal is [$TERM]'
'echo my shit terminal is [$TERM4'
'echo my shit terminal is [$TERM4]'
'echo $UID'
'echo $HOME9'
'echo $9HOME'
'echo $HOME%'
'echo $UID$HOME'
'echo Le path de mon HOME est $HOME'
'echo $USER$var\$USER$USER\$USERtest$USER'
'echo $hola*'
'echo -nnnn $hola'
'echo > <'
'echo | |'
'EechoE'
'.echo.'
'>echo>'
'<echo<'
'>>echo>>'
'|echo|'
'|echo -n hola'
'echo *'
'echo '*''
'echo D*'
'echo *Z'
'echo *t hola'
'echo *t'
'echo $*'
'echo hola*hola *'
'echo $hola*'
'echo $HOME*'
'echo $""'
'echo "$"""'
'echo '$''''
'echo $"HOME"'
'echo $''HOME'
'echo $""HOME'
'echo "$HO"ME'
'echo '$HO'ME'
'echo "$HO""ME"'
'echo '$HO''ME''
'echo "'$HO''ME'"'
'echo ""$HOME'
'echo "" $HOME'
'echo ''$HOME'
'echo '' $HOME'
'echo $"HO""ME"'
'echo $'HO''ME''
'echo $'HOME''
'echo "$"HOME'
'echo $=HOME'
'echo $"HOLA"'
'echo $'HOLA''
'echo $DONTEXIST Hola'
'echo "hola"'
'echo 'hola''
'echo ''hola'''
'echo ''h'o'la'''
'echo "''h'o'la''"'
'echo "'"h'o'la"'"'
'echo"'hola'"'
'echo "'hola'"'
'echo '"hola"''
'echo '''ho"''''l"a''''
'echo hola""""""""""""'
'echo hola"''''''''''"'
'echo hola'''''''''''''
'echo hola'""""""""""''
'e"cho hola"'
'e'cho hola''
'echo "hola     " | cat -e'
'echo ""hola'
'echo "" hola'
'echo ""             hola'
'echo ""hola'
'echo "" hola'
'echo hola""bonjour'
'e'c'ho 'b'"o"nj"o"'u'r'
'e"'c'ho 'b'"o"nj"o"'u'r"'
'echo "$DONTEXIST"Makefile'
'echo "$DONTEXIST""Makefile"'
'echo "$DONTEXIST" "Makefile"'
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
    echo "$cmd" | $MINISHELL >> "$MINISHELL_OUT" 2>&1
    	echo "[$counter]-----------------------" >> "$MINISHELL_OUT"

	((counter++))
    # Compare outputs
    if diff -q "$BASH_OUT" "$MINISHELL_OUT" > /dev/null; then
        echo "[✅] Test passed: $cmd"
    else
        echo "[❌] Test failed: $cmd"
	sleep 1
echo "Expected output:"
    cat "$BASH_OUT"
    echo "Your minishell output:"
    cat "$MINISHELL_OUT"
    fi
done

# Cleanup temporary files
#rm -f "$BASH_OUT" "$MINISHELL_OUT"

echo "Testing completed!"

