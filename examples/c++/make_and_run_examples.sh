#!/bin/bash

set -x

include="../../installed/include"
lib="../../installed/lib"

g++ -O3 -std=c++11 -I$include -L$lib simple_interface.cc -lradlib -o simple_interface.x; 
g++ -O3 -std=c++11 -I$include -L$lib ex_S1.cc parallel_planes.cc -lradlib -o ex_S1.x; 
g++ -O3 -std=c++11 -I$include -L$lib ex_S2.cc parallel_planes.cc -lradlib -o ex_S2.x; 
g++ -O3 -std=c++11 -I$include -L$lib ex_S3.cc parallel_planes.cc -lradlib -o ex_S3.x; 
g++ -O3 -std=c++11 -I$include -L$lib ex_S4.cc parallel_planes.cc -lradlib -o ex_S4.x; 
g++ -O3 -std=c++11 -I$include -L$lib ex_S5.cc parallel_planes.cc -lradlib -o ex_S5.x; 

printf "\n\n********** Simple Interface\n"
./simple_interface.x
printf "\n\n********** Ex S1\n\n"
./ex_S1.x
printf "\n\n********** Ex S2\n\n"
./ex_S2.x
printf "\n\n********** Ex S3\n\n"
./ex_S3.x
printf "\n\n********** Ex S4\n\n"
./ex_S4.x
printf "\n\n********** Ex S5\n\n"
./ex_S5.x
