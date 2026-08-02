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
max=10
target=""
number=""

if [ -z $1 ]; then
    echo "Please enter \"target number\" as a arg of this script !"
    echo "EX: ./NGG.sh 5"
else

    if [ $1 -gt $max ]; then
        echo "Too Big, out of range!"
        echo "Please enter the target number between $min ~ $max"
        exit 1
    fi

    if [ $1 -lt $min ]; then
        echo "Too Small, out of range!"
        echo "Please enter the target number between $min ~ $max"
        exit 1
    fi

    target=$1
fi


echo "Please guess a number between $min and $max"
read number


while [ $number -ne $target ]; do
    AskForGuess $number
done


echo "Bingo!"
exit 0

