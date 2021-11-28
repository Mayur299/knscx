#!/bin/bash
g++ fcfs.cpp
./a.out $1 $2
gedit $2 &
python3 plt.py $2 