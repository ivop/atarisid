#! /bin/sh

sed -i "s@\(^ \+icl \"songs/\).*\(\.inc\"\)@\1$1\2@" atarisid7s.asm
