#! /bin/bash
if [ $# -eq 2 ]
then
   if [ -f $2 ]
   then
      echo "Wortanzahl in Datei:"
      echo $1: `grep -o $1 $2 | wc -l`
   else
      echo "Keine korrekte Datei"
   fi
else
   echo "Nicht genug Parameter: \$Tier \$Datei"
fi
