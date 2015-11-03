#! /bin/bash
#echo "3-buchstabige Wörter: " `grep -o "\<[[:alpha:]]\{3\}\>" bibel.txt | wc -l`
#echo "4-buchstabige Wörter: " `grep -o "\<[[:alpha:]]\{4\}\>" bibel.txt | wc -l`
echo "verschiedene Versanfänge: " 
cat bibel.txt | cut -d' ' -f 3- | grep -o "^\<[[:alpha:]]*\>[[:space:]]\<[[:alpha:]]*\>" | sort | uniq | wc -l"
