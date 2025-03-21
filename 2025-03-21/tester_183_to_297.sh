#!/bin/bash

# Path to your minishell binary
MINISHELL="./minishell"

# Temporary files for storing output
BASH_OUT="183_to_297_bash_output.txt"
MINISHELL_OUT="183_to_297_minishell_output.txt"

# List of commands to test
TEST_COMMANDS=(
'$DONTEXIST'
'$LESS$VAR'
'Ctlr-C'
'holaCtlr-C'
'cat (faire Ctlr-C apres avoir fait plusieurs fois [ENTREE])'
'cat | rev(faire Ctlr-C apres avoir fait plusieurs fois [ENTREE])'
'Ctlr-D'
'hola Ctlr-D'
'Ctlr-\'
'hola Ctlr-\'
'cat (faire Ctlr-\ apres avoir fait plusieurs fois [ENTREE])'
'sleep 3 | sleep 3 | sleep 3 (faire Ctlr-C une seconde apres)'
'sleep 3 | sleep 3 | sleep 3 (faire Ctlr-D une seconde apres)'
'sleep 3 | sleep 3 | sleep 3 (faire Ctlr-\ une seconde apres)'
'env'
'env hola'
'env hola que tal'
'env env'
'env env env env env'
'env ls'
'env ./Makefile'
'export HOLA=bonjour'
'env'
'export HOLA=bonjour'
'env'
'export'
'export Hola'
'export'
'export Hola9hey'
'export'
'export $DONTEXIST'
'export | grep "HOME"'
'export ""'
'export ='
'export %'
'export $?'
'export ?=2'
'export 9HOLA='
'export HOLA9=bonjour'
'env'
'export _HOLA=bonjour'
'env'
'export ___HOLA=bonjour'
'env'
'export _HO_LA_=bonjour'
'env'
'export HOL@=bonjour'
'export HOL\~A=bonjour'
'export -HOLA=bonjour'
'export --HOLA=bonjour'
'export HOLA-=bonjour'
'export HO-LA=bonjour'
'export HOL.A=bonjour'
'export HOL\\\$A=bonjour'
'export HO\\\\LA=bonjour'
'export HOL}A=bonjour'
'export HOL{A=bonjour'
'export HO*LA=bonjour'
'export HO#LA=bonjour'
'export HO@LA=bonjour'
'export HO!LA=bonjour'
'export HO$?LA=bonjour'
'env'
'export +HOLA=bonjour'
'export HOL+A=bonjour'
'export HOLA+=bonjour'
'env'
'export HOLA=bonjour'
'export HOLA+=bonjour'
'env'
'exportHOLA=bonjour'
'env'
'export HOLA =bonjour'
'export HOLA = bonjour'
'export HOLA=bon jour'
'env'
'export HOLA= bonjour'
'env'
'export HOLA=bonsoir'
'export HOLA=bonretour'
'export HOLA=bonjour'
'env'
'export HOLA=$HOME'
'env'
'export HOLA=bonjour$HOME'
'env'
'export HOLA=$HOMEbonjour'
'env'
'export HOLA=bon$jour'
'env'
'export HOLA=bon\jour'
'env'
'export HOLA=bon\\jour'
'env'
'export HOLA=bon(jour'
'export HOLA=bon()jour'
'export HOLA=bon&jour'
'export HOLA=bon@jour'
'env'
'export HOLA=bon;jour'
'env'
'export HOLA=bon!jour'
'export HOLA=bon"jour"'
'env'
'export HOLA$USER=bonjour'
'env'
'export HOLA=bonjour=casse-toi'
'echo $HOLA'
'export "HOLA=bonjour"=casse-toi'
'echo $HOLA'
'export HOLA=bonjour'
'export BYE=casse-toi'
'echo $HOLA et $BYE'
'export HOLA=bonjour BYE=casse-toi'
'echo $HOLA et $BYE'
'export A=a B=b C=c'
'echo $A $B $C'
'export $HOLA=bonjour'
'env'
'export HOLA="bonjour " '
'echo $HOLA | cat -e'
'export HOLA=" -n bonjour " '
'echo $HOLA'
'export HOLA="bonjour "/'
'echo $HOLA'
'export HOLA='"''
'echo " $HOLA " | cat -e'
'export HOLA=at'
'c$HOLA Makefile'
'export "" HOLA=bonjour'
'env'
"
'export HOLA="cat Makefile | grep NAME" '
"
'echo $HOLA'
'export HOLA=hey '
'
'echo $HOLA$HOLA$HOLA=hey$HOLA'
'export HOLA=" bonjour hey " '
'echo $HOLA | cat -e'
'export HOLA=" bonjour hey " '
'echo """$HOLA""" | cat -e'
'export HOLA=" bonjour hey " '
'echo wesh"$HOLA" | cat -e'
'export HOLA=" bonjour hey " '
'echo wesh""$HOLA.'
'export HOLA=" bonjour hey " '
'echo wesh$""HOLA.'
'export HOLA=" bonjour hey " '
'echo wesh$"HOLA HOLA".'
'export HOLA=bonjour'
'export HOLA=" hola et $HOLA"'
'echo $HOLA'
'export HOLA=bonjour'
'export HOLA=' hola et $HOLA''
'echo $HOLA'
'export HOLA=bonjour'
'export HOLA=" hola et $HOLA"$HOLA'
'echo $HOLA'
'export HOLA="ls -l - a"'
'echo $HOLA'
'export HOLA="s -la" '
'l$HOLA'
'export HOLA="s -la" '
'l"$HOLA"'
'export HOLA="s -la" '
'l'$HOLA''
'export HOLA="l" '
'$HOLAs'
'export HOLA="l" '
'$HOLAs'
'export HOL=A=bonjour'

'env'
'export HOLA="l" '
''$HOLA's'
'export HOL=A=""'
'env'

'export TE+S=T'
'env'
"
'export ""=""'
'export ''='''
'export "="="="'
'export '='='=''

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

