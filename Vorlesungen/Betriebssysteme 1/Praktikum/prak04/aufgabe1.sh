#! /bin/bash
# Vorbereitung verse:
cut -d ' ' -f 3- bibel.txt > verse.txt
echo -e "\e[1m13-buchstabige Wörter: \e[0m" `grep -o "\<[[:alpha:]]\{3\}\>" verse.txt | wc -l`
echo -e "\e[1m14-buchstabige Wörter: \e[0m" `grep -o "\<[[:alpha:]]\{4\}\>" verse.txt | wc -l`
echo -e "\e[1m1verschiedene Versanfänge: \e[0m" `grep -o "^\<[[:alpha:]]*\>[[:space:]]\<[[:alpha:]]*\>" verse.txt | sort | uniq | wc -l`
echo -e "\e[1mmind. 2* Löwe in einem Vers: \e[0m" `grep -o "Löwe.*Löwe" verse.txt | wc -l`
echo -e "\e[1mmind. 3* Löwe in einem Vers: \e[0m" `grep -o "Löwe.*Löwe.*Löwe" verse.txt | wc -l`
echo -e "\e[1mlängstes Wort: \e[0m"  `grep -o "\<[[:alpha:]]\+\>" verse.txt | awk '{ print length " " $1}' | uniq | sort -n -r | head -n 1`
echo -e "\e[1mlängstes Wort ohne Zahlen: \e[0m" `grep -o "\<[[:alpha:]]\+\>" verse.txt | awk '{ print length " " $1}' | grep -v "\(eins\)\|\(zwei\)\|\(drei\)\|\(vier\)\|\(fünf\)\|\(sechs\)\|\(sieben\)\|\(acht\)\|\(neun\)\|\(zehn\)\|\(hundert\)\|\(tausend\)" | uniq | sort -n -r | head -n 1`
echo -e "\e[1mWorte die mit 'g' beginnen und mit 'n' enden: \e[0m" 
echo `grep -o "\<[Gg][[:alpha:]]*n\>" verse.txt | sort | uniq`
echo -e "\e[1mWorte die mit 'a' beginnen und mit 'ing' oder 'ung' enden: \e[0m" 
echo `grep -o "\<[Aa][[:alpha:]]*ung\>\|\<[Aa][[:alpha:]]*ing\>" verse.txt | sort | uniq`
