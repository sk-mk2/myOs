#! /bin/bash
for i in {0..92160}
do
    echo -en "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
done >> helloos.img
