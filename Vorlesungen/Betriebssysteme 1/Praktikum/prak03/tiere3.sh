#! /bin/bash
if [ $# -eq 1 ]
then
   if [ -e $1 ]
   then
      echo "Anzahl folgender Worte in Datei:"
      read tier
      while [ "$tier" != "" ]
      do 
         echo $tier: `grep -o $tier $1 | wc -l`
         read tier
      done
   else
      echo "Keine korrekte Datei"
   fi
else
   echo "Nicht genug Parameter:\$Datei"
fi
