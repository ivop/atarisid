#! /bin/sh

mkdir -p xex

for i in songs/*.inc ; do
    j=`basename "$i" .inc`
    ./setsong.sh $j
    mads -o:as6s-$j.xex atarisid6s.asm
    mv -f as6s-$j.xex xex
done

