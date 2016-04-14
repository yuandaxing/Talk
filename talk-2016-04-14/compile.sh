#! /bin/bash

g++  -O3 -o thread_manager_ut.exe thread_manager_ut.cpp -std=c++11 -I../../lib/gtest -L../../lib/gtest -fdiagnostics-color=auto -lgtest -lpthread

/usr/bin/g++  -O3 -o old.exe old.cpp -I../../lib/gtest -L../../lib/gtest  -lgtest -lpthread
