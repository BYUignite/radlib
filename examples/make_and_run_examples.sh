#!/bin/bash

 cd ../build; 
 cmake -C user_config ../source/c++; 
 make; 
 make install; 
 cd -; 

 g++ -std=c++11 -I../installed/include -L../installed/lib simple_interface.cc -lradlib -o simple_interface.x; 
 g++ -std=c++11 -I../installed/include -L../installed/lib ex_1.cc parallel_planes.cc -lradlib -o ex_1.x; 
 g++ -std=c++11 -I../installed/include -L../installed/lib ex_2.cc parallel_planes.cc -lradlib -o ex_2.x; 
 g++ -std=c++11 -I../installed/include -L../installed/lib ex_3.cc parallel_planes.cc -lradlib -o ex_3.x; 
 g++ -std=c++11 -I../installed/include -L../installed/lib ex_4.cc parallel_planes.cc -lradlib -o ex_4.x; 
 g++ -std=c++11 -I../installed/include -L../installed/lib ex_5.cc parallel_planes.cc -lradlib -o ex_5.x; 

 printf "\n\n********** Simple Interface\n"
 ./simple_interface.x
 printf "\n\n********** Ex 1\n\n"
 ./ex_1.x
 printf "\n\n********** Ex 2\n\n"
 ./ex_2.x
 printf "\n\n********** Ex 3\n\n"
 ./ex_3.x
 printf "\n\n********** Ex 4\n\n"
 ./ex_4.x
 printf "\n\n********** Ex 5\n\n"
 ./ex_5.x
