#!/bin/bash

#clear

# compile
g++ \
    $1 \
    -o compiled_temp \
    -lpthread \
    -std=c++11

# execute
./compiled_temp 

# delete
rm ./compiled_temp 

