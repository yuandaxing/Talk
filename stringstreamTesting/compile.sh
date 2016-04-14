#! /bin/bash

g++  -O3 -o thread_manager_ut.exe thread_manager_ut.cpp -std=c++11 -I../../lib/tbb -L../../lib/tbb -fdiagnostics-color=auto -ltbb -lpthread

/usr/bin/g++  -O3 -o old.exe old.cpp -I../../lib/tbb -L../../lib/tbb  -ltbb -lpthread
