#!/usr/bin/env bash
#Get the Directory where the script lives
#break down cd to (get the bash script could be ./file/file/.sh, then dirname stripts the file parts off, then cd into the files location, then print the working directory and thats where scripts is)
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

#Then set the Build directory
BUILD_DIR="$SCRIPT_DIR/../Paxel/build/Desktop_Qt_6_9_3_MSVC2022_64bit-GOOGLETEST"

echo "Building Test..."
cmake --build "$BUILD_DIR" --target goggletesting

if [ $? -ne 0 ]; then
    echo "Build Through QT first then Run this"
    exit 1
fi

#Full break down --uncomment if you want
#echo "PWD: $(pwd)"
#echo "BASH_SOURCE: ${BASH_SOURCE[0]}"
#echo "DIRNAME: $(dirname "${BASH_SOURCE[0]}")"
#echo "SCRIPT_DIR: $(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"


echo "Running tests..."
cd "$BUILD_DIR" || exit 1
./goggletesting.exe
#seemingly the color option is optinal if your colors do not work then uncomment below
#"$BUILD_DIR/goggletesting.exe" #--gtest_color=yes 

