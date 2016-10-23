#!/bin/bash
insmod calcul.ko || exit

rm -f /dev/second
rm -f /dev/first
rm -f /dev/operator

mknod /dev/first c $(awk '$2=="first" {print $1}' /proc/devices) 0
mknod /dev/second c $(awk '$2=="second" {print $1}' /proc/devices) 0
mknod /dev/operator c $(awk '$2=="operator" {print $1}' /proc/devices) 0

chmod 666 /dev/operator
chmod 666 /dev/second
chmod 666 /dev/first