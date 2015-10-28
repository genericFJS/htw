#! /bin/bash
echo "Tiere in der Bibel:"
echo "Schlangen"
grep -o Schlange bibel.txt | wc -l
echo "Mäuse"
grep -o "M[aä]use\{0,1\}" bibel.txt | wc -l
echo "Löwen"
grep -o Löwe bibel.txt | wc -l
