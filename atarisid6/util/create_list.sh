#! /bin/sh

# create list of all authors and songs

for i in *.inc ; do
    grep '    .sb' "$i" |
    tail -n 3 |
    head -n 2 |
    cut -d\" -f2 |
    tac |
    sed 's/^  by /  /' |
    awk 'NR%2{printf $0" - ";next;}1'
done | sort
