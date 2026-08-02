#!/bin/bash

AskForGuess() {
    if [ $1 -gt $target ] && [ $1 -le $max ]; then
        echo "Too high!"
        max=`expr $1 - 1`
    fi

    if [ $1 -lt $target ] && [ $1 -ge $min ]; then
        echo "Too low!"
        min=`expr $1 + 1`
    fi

    echo "Please guess a number between $min and $max"
    read number
}


min=1
max=100
target=$((( RANDOM % ($max - $min + 1)) + $min ))
number=""
count=""


if [ -z $1 ]; then
    echo "Please enter the max number of guess"
    echo "EX: ./ngg.sh 10"
    exit 0;
else
    count=$1
fi

echo "Please guess a number between $min and $max"
read number

count=`expr $count - 1`

while [ $number -ne $target ]; do
    AskForGuess $number

    count=`expr $count - 1`

    if [ $count -eq 0 ]; then
        echo "You loss!"
        exit 0;
    fi
done


echo "Bingo!"
exit 0

