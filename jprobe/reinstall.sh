#!/bin/bash

module_name="xtw.ko"
rmmod $module_name
make clean
make
insmod $module_name
dmesg -C
