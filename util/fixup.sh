#! /bin/sh

A=1

while test "$A" = "1"; do
    B=`atasm -r "$1" 2>&1 | grep "Error: Unknown symbol" | cut -d"'" -f2`
    if test -z "$B" ; then
        A=0
        continue
    fi

    C=`echo "$B" | cut -d_ -f2`
    echo $B $C
    sed "s/$B/\$$C/g" <"$1" >"$1".tmp
    mv "$1".tmp "$1"

done

atasm -r "$1"

