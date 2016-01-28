#!/bin/bash

# Belegaufgabe BS1 im WS 2015/16 von Falk-Jonatan Strube (s74053)
# Zeigt die Onlinezeit eines Nutzers an.
# Bei dem Rückgabewerten gilt grundsätzlich: 0: ja/erfolgreich, 1: nein/nicht erfolgreich

# Einige Ausgaben gesammelt
mystart="==================\n Beleg von s74053 \n=================="
myinter="------------------"
myerror="Eingabeparameter: \$Rechnername \$Nutzerkennzeichen \$Monatskürzel\nMonatskürzel: Jan, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec\n"$myinter
myerrorP="Der Rechner "$1" ist entweder nicht erreichbar oder die Parameter wurden falsch eingegeben.\n"
myerrorU="Der Nutzer "$2" existiert nicht an "$1" oder die Parameter wurden falsch eingegeben.\n"
myerrorM="Es wurde ein falsches Monatskürzel eingeben oder die Parameter wurden falsch eingegben.\n"
mymonths=(Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec)
mycolor="\e[32m"
myfin="==================\e[39m"
myclear="                                                             "

timeSum=0
timeSumUniq=0

# Gibt aus, ob Rechner ein korrekter Rechnername ist (oder Raum 146a)
# $1: Rechner
isCorrectPC (){  
  echo -en "Prüfe Rechnerparameter...\r"
  ping -c 1 -w 1 $1 &> /dev/null
  if [ $? -eq 0 ]
  then
    return 0
  fi
  if [[ $1 == "146a" ]]
  then
    return 0
  fi
  return 1
}

# Gibt aus, ob das NKZ ein korrekter Nutzer auf dem Rechner ist (oder im Raum 146a)
# $1: NKZ
# $2: Rechner
isCorrectUser (){  
  echo -en "Prüfe Nutzerparameter...\r"
  local fingerResult
  if [[ $2 == "146a" ]]
  then
    for i in {1..22}
    do
      local fingerResult=$(ssh -oStrictHostKeyChecking=no "isys$i" finger -m $1)
      if [[ $fingerResult == *$1* ]]
      then
	return 0
      fi
    done
  else
    fingerResult=$(ssh -oStrictHostKeyChecking=no $2 finger -m $1)
    if [[ $fingerResult == *$1* ]]
    then
      return 0
    fi
  fi
  return 1
}

# Gibt aus, ob der Monatskürzel korrekt ist
# $1: Monatskürzel
isCorrectMonth () {  
  echo -en "Prüfe Monatskürzel...\r"
  for month in "${mymonths[@]}"; do
    if [[ $month == $1 ]]; then
      return 0
    fi
  done
  return 1
}

# Überprüfen, ob Eingabeparameter in Ordnung sind (Aufgabenpunkt 2)
# $1: Rechner
# $2: NKZ
# $3: Monatskürzel
isCorrectInput(){
  if isCorrectPC $1
  then
    if isCorrectUser $2 $1
    then
      if isCorrectMonth $3
      then
        return 0
      else
        echo -e $myerrorM$myfin
        exit 1
      fi
    else
      echo -e $myerrorU$myfin
      exit 1
    fi
  else 
    echo -e $myerrorP$myfin
    exit 1
  fi
}

# Zeigt Namen des übergebenen Nutzer an
# $1: NKZ
# $2: Rechner
displayName (){  
  echo -en "Hole Nutzernamen...\r"
  local nutzerinfo
  if [[ $2 == "146a" ]]
  then
    nutzerinfo=$(ssh -oStrictHostKeyChecking=no "isys1" finger -m $1)
  else
    nutzerinfo=$(ssh -oStrictHostKeyChecking=no $2 finger -m $1)
  fi
  local infocut=${nutzerinfo#*"Name:"}
  local name=${infocut%"Directory"*}
  #echo "Nutzerkürzel: "$1
  echo -en "$myclear\r"
  echo "Nutzername: "$name
}

# Berchnet die aktive Zeit des übergebenen Nutzers innerhalb des gegebenen Monats
# $1: NKZ
# $2: Rechner
# $3: Monatskürzel
calculateOnlineTime (){    
  timeSumUniq=0
  local roomPC=""
  if [[ $2 == "isys"* ]]
  then
    roomPC=" auf $2"
  fi
  
  # erneutes Prüfen für isys-Rechner
  if !(isCorrectPC $2)
  then
    return 1
  fi
  echo -en "$myclear\r"
  echo -en "Hole Logs von $2...\r"
  local allLogs=$(ssh -oStrictHostKeyChecking=no $2 ls /var/log 2> /dev/null | grep "wtmp")
  echo -en "$myclear\r"
  echo -en "Erstelle temporäres Verzeichnis...\r"
  local tmpDir=$(ssh -oStrictHostKeyChecking=no $2 mktemp -d)
  local fileNo=0
  local maxFiles=$(grep -o "wtmp" <<< "$allLogs" | wc -l)
  
  echo -en "$myclear\r"
  echo -en "Berechne aktive Zeit$roomPC...\r"
  for line in $allLogs
  do
    let "fileNo+=1"
    echo -en "Berechne aktive Zeit$roomPC (aus Datei $fileNo von $maxFiles)...\r\r"
    local lastF=$tmpDir/$line
    ssh -oStrictHostKeyChecking=no $2 cp /var/log/$line $lastF
    if [ ${#line} -ne 4 ]
    then
      ssh $2 unxz $lastF
      lastF=${lastF%.*}
    fi
    times=$(ssh -oStrictHostKeyChecking=no $2 last -f $lastF $1 | grep $3 | grep -o \(.*\))
    hours=$(echo $times | grep -o [0-9][0-9]:[0-9][0-9] | cut -d ':' -f 1)
    minutes=$(echo $times | grep -o [0-9][0-9]:[0-9][0-9] | cut -d ':' -f 2)
    days=$(echo $times | grep -o [0-9]*+ | cut -d '+' -f 1)
    
    for day in $days
    do
      timeSum=$(echo $timeSum + $day*24*60 | bc)
      timeSumUniq=$(echo $timeSum + $day*24*60 | bc)
    done   
    for hour in $hours
    do
      timeSum=$(echo $timeSum + $hour*60 | bc)
      timeSumUniq=$(echo $timeSum + $hour*60 | bc)
    done
    for minute in $minutes
    do
      timeSum=$(echo $timeSum + $minute | bc)
      timeSumUniq=$(echo $timeSum + $minute | bc)
    done
  done 
  rm -r $tmpDir 2> /dev/null
  return 0
}

# Zeigt die berechnete aktive Zeit des übergebenen Nutzers innerhalb des gegebenen Monats an (insgesamt im Fall 146a)
# $1: NKZ
# $2: Rechner
# $3: Monatskürzel
displayOnlineTime(){
  uDays=$(echo $timeSum/60/24 | bc)
  uHours=$(echo $timeSum/60%24 | bc)
  uMinutes=$(echo $timeSum%60 | bc)
  local hour0
  local minute0
  if [ $uHours -lt 10 ]
  then 
    hour0="0"
  fi
  if [ $uMinutes -lt 10 ]
  then 
    minute0="0"
  fi
  
  echo -en "$myclear\r"
  echo "Gesamte aktive Zeit im $3 auf $2: $timeSum min ($uDays Tage, $hour0$uHours Stunden, $minute0$uMinutes Minuten)"
}

# Zeigt die berechnete aktive Zeit des übergebenen Nutzers innerhalb des gegebenen Monats an (für Einzelrechner im Fall 146a)
# $1: NKZ
# $2: Rechner
# $3: Monatskürzel
displayOnlineTimeUniq(){
  uDays=$(echo $timeSumUniq/60/24 | bc)
  uHours=$(echo $timeSumUniq/60%24 | bc)
  uMinutes=$(echo $timeSumUniq%60 | bc)
  local hour0
  local minute0
  if [ $uHours -lt 10 ]
  then 
    hour0="0"
  fi
  if [ $uMinutes -lt 10 ]
  then 
    minute0="0"
  fi
  
  echo -en "$myclear\r"
  echo "Aktive Zeit im $3 auf $2: $timeSum min ($uDays Tage, $hour0$uHours Stunden, $minute0$uMinutes Minuten)"
}

# Gebe Nutzerinformationen aus (Aufgabenpunkt 3)
# $1: NKZ
# $2: Rechner
# $3: Monatskürzel
displayInfo (){
  displayName $1 $2
  if [[ $2 == "146a" ]]
  then
    for i in {1..22}
    do
      calculateOnlineTime $1 "isys$i" $3
	  displayOnlineTimeUniq $1 "isys$i" $3
	  echo $myinter
    done
  else
    echo "pc"
    calculateOnlineTime $1 $2 $3
  fi
  displayOnlineTime $1 $2 $3
  return 1
}

# MAIN
#########################
echo -n -e $mycolor
echo -e $mystart
# Überprüfen der Eingabeparameter (Aufgabenpunkt 1)
if [ $# -eq 3 ]
then
  if isCorrectInput $1 $2 $3
  then
    displayInfo $2 $1 $3
  fi
else
echo -e $myerror$myfin
exit 1
fi
echo -e $myfin
exit 0