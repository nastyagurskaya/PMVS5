#!/bin/bash
sudo sh l.sh

function test {
	 echo $1 > /dev/first
    echo $2 > /dev/operator
    echo $3 > /dev/second
	result=$(cat /proc/result)
    if [ "$4" == "$result" ]; then
        echo "True! $1 $2 $3=$result"
    else
        echo "False! $1$2$3=$result"
    fi
}

test 7 + 14 21
test 1 + 11 12
test -4 + 10 6
test 20 / 2 10
test 10 / -2 -5
test 6 / 3 2
test 12 m 3 36
test 12 m -2 -24
test -6 m -6 36
test 8 - 21 -13
test 13 - -27 40
test 20 - 50 -30
test 3 - 3 0

sudo sh unl.sh