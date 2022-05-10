#!/usr/bin/env bash

cmpl="clang++ -Wall -Werror -Wextra -std=c++98  -I ../includes"

function grepTest() {
	cat ./measure_$1.cpp | grep '//' | sed -e 's/.* TEST: //g'
}

function measure() {
rm $1_std.compare
rm $1_ft.compare

$cmpl measure_$1.cpp -D STD -o $1_std.compare 
$cmpl measure_$1.cpp -D FT  -o $1_ft.compare 

./$1_std.compare > $1_std.log
./$1_ft.compare  > $1_ft.log
grepTest $1 > $1_test_.log

python3 measurement.py vector vector_std.log vector_ft.log vector_test_.log
}

measure vector