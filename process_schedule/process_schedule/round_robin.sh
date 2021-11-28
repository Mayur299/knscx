#!/bin/bash
g++ rr.cpp
./a.out $1 $2
gedit $2 &
python3 pltrr.py $2 