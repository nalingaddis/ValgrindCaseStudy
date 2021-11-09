#!/bin/bash

mkdir -p traces
mkdir -p traces/$1_tests

for test in tests/*
    do valgrind bin/$1 < $test > traces/$1_$test.txt
done