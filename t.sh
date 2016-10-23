#!/bin/bash
function test {
	echo "$1" > /proc/first
	echo "$2" > /proc/operand
	echo "$3" > /proc/second
	res=`sudo cat /dev/result`
	echo "$1$2$3=${res}"
}

test 7 + 14 21
test 1 + 11 12
test -4 + 10 6
test 20 / 2 10
test 10 / -2 -5
test 6 / 3 2
test 12 '*' 3 36
test 12 '*' -2 -24
test -6 '*' -6 36
test 8 - 21 -13
test 13 - -27 40
test 20 - 50 -30
test 3 - 3 0