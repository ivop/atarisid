#! /bin/sh

mkdir -p xex

for i in songs/*.inc ; do
    j=`basename "$i" .inc`
    ./setsong.sh $j
    mads -o:as7s-$j.xex atarisid7s.asm
    mv -f as7s-$j.xex xex
    mads -d:NTSC=1 -o:as7s-$j.xex atarisid7s.asm
    mv -f as7s-$j.xex xex-ntsc
done

