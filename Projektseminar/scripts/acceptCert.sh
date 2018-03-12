#!/bin/bash
cd "$(dirname "$0")"

echo -n "Passwort von $USER: "
read -s password
echo

# Prüfen, ob Host online ist (ping) und über sshpass mit dem eingegebenen Passwort anmelden, damit der Host in keinem Fall beim MPI-Aufruf nach dem Passwort fragt.
checkHost() {
	ping -c 1 -w 1 $1 &> /dev/null
	if [ $? -eq 1 ]
	then
		echo " offline: $1"
		return 0
	else
		$(sshpass -p$2 ssh -oStrictHostKeyChecking=no $1 exit) &
		wait $pids
		echo "  online: $1"
		echo "$1" >> "../machines/machinefile"
		return 1
	fi
}

rm "../machines/machinefile" &>/dev/null
touch "../machines/machinefile"
# Alle Hosts in Array speichern.
mapfile -t hosts < ../machines/machinefileAll
count=0
onlinecount=0
# Hosts prüfen, indem Hostarray durchlaufen wird.
for userhost in "${hosts[@]}"
do
	checkHost $userhost $password
	onlinecount=`expr $onlinecount + $?`
	count=`expr $count + 1`
done
# Auf alle ssh-Verbindungen warten.
while [ $count -gt 0 ]; do
	wait $pids
	count=`expr $count - 1`
done
echo "Hosts online: $onlinecount"