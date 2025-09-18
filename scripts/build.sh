#!/bin/bash
# Compiler yea its g++ get over it
CXX=g++

# All flags included (this is for errors and linking when it compiles)
CXXFLAGS="-Wall -Wextra -std=c++17 -I ./hdr -I ./src"

# This is * all cpp files its called a wildcard character
SRC=./src/*.cpp

# This is what the binarary it produces gets outputted
OUT=./bin/my_program

#ensure the bin for the binarary exist IE the program we make
mkdir -p ./bin

# attempt to comple
echo "Attempting Build..."

# Arguments goes as follows btw this is a litteraly command in the terminal line as shown below (bin\bash, Compiler, Flags, ObjFiles, -o ProgramFileOutput)
# "g++ -Wall -Wextra -std=c++17 -I./hdr -I./src ./src/*.cpp -o ./bin/my_program" 
$CXX $CXXFLAGS $SRC -o $OUT

# if it completes then this will echo
echo "Build complete: $OUT"
