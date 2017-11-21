#!/bin/bash
# Skript ist auf dem Rechner auszuführen, auf dem die Datenbank läuft.

states=("UKN" "DOWN" "IDLE" "MAINT" "PROC")
RANDOM=$$$(date +%s)

user=""
password=""
database=""
tool=""

if [ $# -ge 3 ]
then 
	user=$1
	password=$2
	database=$3
else 
	echo "You can use the options script.sh DB_USER DB_USER_PASSWORD DATABASE_NAME."
	printf "User: "
	read user
	printf "Password: "
	read password
	printf "Database: "
	read database
fi

changeRandom() {
	randState=${states[$RANDOM % ${#states[@]} ]}
	changeState $randState
}

changeState(){
	printf "State change to $1: "
	PGPASSWORD=$password psql -U $user -d $database -c "UPDATE tool SET state = '$1' WHERE tool = '$tool';"
}

while :
do
	sleepTime=2
	# Auswahl des Tools:
	echo "------------------------------"
	echo "Available tools:"
	PGPASSWORD=$password psql -U $user -d $database -c "SELECT tool FROM tool" | cat | tail -n +3 | head -n -2 | tr -d '\n' | tr '  ' ', '
	printf "\n"
	printf "Tool: "
	read tool
	while :
	do
		echo "------------------------------"
		echo "Possible commands: 1=random once, 2=cycle all stats once, 3=loop random, 0=reselect tool"
		printf "Change $tool status: "
		read command
		if [ ${command#0} -eq 3 ]
		then
			trap 'break 2' INT
			while :
			do
				changeRandom
				sleep $sleepTime
			done
			trap - INT
		else
			if [ ${command#0} -eq 2 ]
			then
				counter=0
				changeState ${states[0]}
				sleep $sleepTime
				changeState ${states[1]}
				sleep $sleepTime
				changeState ${states[2]}
				sleep $sleepTime
				changeState ${states[3]}
				sleep $sleepTime
				changeState ${states[4]}
			else
				if [ ${command#0} -eq 1 ]
				then
					changeRandom
				else
					break
				fi
			fi
		fi
	done
done
#PGPASSWORD=meinSE2#1 psql -U se2 -d se2 -c "UPDATE tool SET state = 'IDLE' WHERE tool = 'MET9001';"
#PGPASSWORD=meinSE2#1 psql -U se2 -d se2 -c "SELECT * FROM tool;"