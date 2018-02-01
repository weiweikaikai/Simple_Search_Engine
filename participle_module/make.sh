#!/bin/bash


g++  participle.cpp -std=c++11 -o  participle -g  -I../lib/THULAC/include/
g++  hash_chain.cpp inverted_index.cpp   -std=c++11 -o  inverted_index -g  
