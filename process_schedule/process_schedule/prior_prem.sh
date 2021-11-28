#!/bin/bash
g++ priorityp_premptive.cpp
./a.out $1 $2
gedit $2 &
python3 pltnp.py $2 