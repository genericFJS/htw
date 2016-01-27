#!/bin/bash
mystart="==================\n Beleg von s74053 \n=================="
myinter="------------------"
myerror="Eingabeparameter: \$Rechnername \$Nutzerkennzeichen \$Monatskürzel\nMonatskürzel: Jan, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec\n"$myinter
myerrorP="Der Rechner "$1" ist entweder nicht erreichbar oder die Parameter wurden falsch eingegeben.\n"$myinter
myerrorU="Der Nutzer "$2" existiert nicht an "$1" oder die Parameter wurden falsch eingegeben.\n"$myinter
myerrorM="Es wurde ein falsches Monatskürzel eingeben oder die Parameter wurden falsch eingegben.\n"$myinter
mymonths=(Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec)
mycolor="\e[32m"
myfin=$myinter"\e[39m"

# Überprüft, ob der übergebene Parameter ein korrekter Rechnername ist
isCorrectPC (){
  local ok=1
  ping -c 1 $1 &> /dev/null
  if [ $? -eq 0 ]
  then
    ok=0
  fi
  return $ok
}

# Überprüft, ob der erste übergebene Parameter ein korrektes Nutzerkennzeichen auf dem entsprechenden Rechner (zweiter Parameter) ist
isCorrectUser (){
  local ok=1
  if [[ "`finger -m $1 2> /dev/null`" == *$1* ]]
  #if [[ "`finger -m $1"@"$2`" == *$1* ]] #NUTZER
  then
    ok=0
  fi
  return $ok
}

# Überprüft, ob der übergebene Parameter ein korrekter Monatskürzel ist
isCorrectMonth () {
  local ok=1
  for month in "${mymonths[@]}"; do
    if [[ $month == $1 ]]; then
      ok=0
      break
    fi
  done
  return $ok
}

# Überprüfen, ob Eingabeparameter in Ordnung sind (Aufgabenpunkt 1+2)
isCorrectInput(){
#echo $?
  if isCorrectPC $1
  then
    # id anstatt finger
    if isCorrectUser $2 $1
    then
      if isCorrectMonth $3
      then
        return 0
      else
        echo -e $myerrorM$myfin
      fi
    else
      echo -e $myerrorU$myfin
      return 1
    fi
  else 
    echo -e $myerrorP$myfin
    return 1
  fi
}

# Zeigt Namen von übergebenen Nutzer an
displayName (){  
  local a=$(finger $1) #NUTZER
  local b=${a#*"Name:"}
  local c=${b%"Directory"*}
  #echo "Nutzerkürzel: "$1
  echo "Nutzername: "$c
}

# Zeigt die aktive Zeit des übergebenen Nutzers an
displayOnlineTime (){
  local userdays=0
  local userhours=0
  local userminutes=0
  local overallminutes=0
  last -f /var/log/wtmp | grep $1 | grep -v "gone" | {
  while read -r line
  do
    local a=${line#*(}
    local b=${a%)*}
    local c=$b
    if [[ $b == *+* ]]
    then
      let "userdays+=$((10#${b%+*}))"
      c=${b#*+}
    fi
    let "userhours += $((10#${c%:*}))"
    let "userminutes += $((10#${c#*:}))"
    # Minuten in Stunden integrieren:
    let "userhours += $userminutes/60"
    let "userminutes = $userminutes%60"
    # Stunden in Tage integrieren
    let "userdays += $userhours/24"
    let "userhours = $userhours%60"
  done  
  let "overallminutes+= $userminutes"
  let "overallminutes+= $userhours*60"
  let "overallminutes+= $userdays*24*60"
  echo "Insgesamt aktiv: " $overallminutes " min"
  local hour0
  local minute0
  if [ $userhours -le 10 ]
  then 
    hour0="0"
  fi
  if [ $userminutes -le 10 ]
  then 
    minute0="0"
  fi
  echo "in Tagen+Stunden:Minuten: "$userdays"+"$hour0$userhours":"$minute0$userminutes
  }
}

# Gebe Nutzerinformationen aus
displayInfo (){
  displayName $2 $1
  displayOnlineTime $2 $3
  return 1
}

echo -n -e $mycolor
echo -e $mystart
# Punkt 1
if [ $# -eq 3 ]
then
  if isCorrectInput $1 $2 $3
  then
    displayInfo $1 $2 $3
  fi
else
echo -e $myerror
fi
echo -e $myfin