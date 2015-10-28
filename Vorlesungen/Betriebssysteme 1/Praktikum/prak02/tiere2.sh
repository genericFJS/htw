#! /bin/bash
echo $1: `grep -o $1 $2 | wc -l`
echo $1:
grep -o $1 $2 | wc -l
