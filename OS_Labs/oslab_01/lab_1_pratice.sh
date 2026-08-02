#!/bin/bash


# system variables

echo $PWD


# User defined variables

var_one=var_one

echo $var_one

# #############################################################

# shell arithmetic, ops:"+ - * /"
# syntax: $ expr $operand ops $operand

expr 1 + 1

expr 9 - 3

expr 3 \* 7

expr 9 / 3

# #############################################################

# double quotes: interprete string, `` -> mark execute 

# single quotes: pure string

echo "$var_one, there"

echo '$var_one, there'

echo "expr 1 + 3"

echo 'expr 1 + 3'

echo "`expr 1 + 3`"

echo '`expr 1 + 3`'

# #############################################################

# The "read" statement

echo "input fname and lname:"

read fname lname

echo "fname:$fname, lname:$lname"


# #############################################################

# The "Arguments"
# ex: ./lab_1_pratice.sh apple banana
# $0 -> current execute path, $1 -> arg1, $2 -> arg2 ...
# $# -> Holds the total number of arguments passed.
# $@ -> Expands to all arguments passed to the function.

echo "arg0:$0 arg1:$1 arg2:$2, number of args passed:$#, all arg passed:$@"

# #############################################################

# The Conditionals

foo=foo

if [ "$foo" = "foo" ]; then
    echo "foo equal"
fi


foo=fooo

if [ "$foo" = "foo" ]; then
    echo "foo equal"
else
    echo "foo not equal"
fi


foo=foooo

if [ "$foo" = "foo" ]; then
    echo "foo equal"
elif [ "$foo" = "fooo" ]; then
    echo "fooo equal"
else
    echo "$foo not match"
fi


# Operations for Mathematics: -eq, -ne, -gt, -ge, -lt, -le

op1=3
op2=3

if [ $op1 -eq $op2 ]; then
    echo "$op1 is equal to $op2"
fi

op2=6

if [ $op1 -ne $op2 ]; then
    echo "$op1 is not equal to $op2"
else
    echo "$op1 is equal to $op2"
fi


# Operations for Strings: str1 = str2, str1 != str2, str1, -n str1, -z str1


# ...


# #############################################################

# Shell "For Loop Statement"

for i in 1 2 3 4 5 ; do
    echo "item $i"
done

for ((i=1; i<6; i++)); do
    echo "item `expr $i + 1`"
done

# #############################################################

# Shell "While Loop Statement"

i=1

while [ $i -lt 6 ]; do
    echo "item $i"
    i=`expr $i + 1`
done

# #############################################################

# Shell "Case Statement"

echo "please input something:"

read var1

case $var1 in
    "apple") echo "$var1 matched";;
    "guava") echo "$var1 matched";;
    "banana") echo "$var1 matched";;
    *) echo "$var1 not match !";;
esac

# #############################################################

# Shell "Function"

num=100

PrintNumber(){
    echo "print the number plus one: `expr $num + 1`"
}

PrintNumber



