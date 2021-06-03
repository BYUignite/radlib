
g++ -std=c++11 -I/Users/dol4/codes/radlib/installed/include -c c_interface.cc

gfortran -c rad_module.f90
gfortran -c main.f90

gfortran -o test.x -L/Users/dol4/codes/radlib/installed/lib/ main.o rad_module.o c_interface.o -lc++ -lradlib
