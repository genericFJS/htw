#!/bin/bash
trap "echo CTRL-C gedrückt. Na fein." SIGINT
trap "echo CTRL-Z gedrückt. Mach ruhig weiter so." SIGTSTP
trap "echo Auch SIGQUIT kann mir nix anhaben." SIGQUIT
echo Entering loop
while true ; do echo -n ; done


