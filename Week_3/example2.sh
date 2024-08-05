#!/bin/bash

X=0
while [ $X -le 20 ]; do
    echo $X
    X=$(expr $X \+ 1)
    # or x=$((x+1)) 
done

echo "All command line arguments:"

while [ "$#" -ne 0 ]; do
    echo "$1"
    shift
done

