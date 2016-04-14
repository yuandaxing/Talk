#! /bin/bash

g++  -O3 -o binary_search_ut.exe binary_search_ut.cpp -std=c++11 -I../../lib/gtest -L../../lib/gtest -fdiagnostics-color=auto -lgtest -lpthread

/usr/bin/g++  -O3 -o binary_search-test1.exe binary_search-test1.cpp -std=c++11 -I../../lib/gtest -L../../lib/gtest  -lgtest -lpthread
