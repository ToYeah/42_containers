#!/usr/bin/env bash

cmpl="clang++ -Wall -Werror -Wextra -std=c++98  -I ../includes"

function grepTest() {
	cat ./measure_$1.cpp | grep '//' | sed -e 's/.* TEST: //g'
}

function clean() {
	rm $1_std.compare
	rm $1_ft.compare
	rm $1_std.log
	rm $1_ft.log
	rm $1_test.log
}

function measure() {

clean $1
$cmpl measure_$1.cpp -D STD -o $1_std.compare 
$cmpl measure_$1.cpp -D FT  -o $1_ft.compare 

./$1_std.compare > $1_std.log
./$1_ft.compare  > $1_ft.log
grepTest $1 > $1_test.log

python3 measurement.py $1 $1_std.log $1_ft.log $1_test.log
}

if [ $# -eq 1 ];then
	measure $1
    exit 1
fi

measure vector
measure stack
