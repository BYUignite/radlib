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
g++ -O3 -std=c++11 -I$include -L$lib ex_B3.cc parallel_planes.cc -lradlib -o ex_B3.x; 
g++ -O3 -std=c++11 -I$include -L$lib ex_Sb1.cc parallel_planes.cc -lradlib -o ex_Sb1.x; 

