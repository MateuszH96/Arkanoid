#!/bin/bash

cmake ..

if [[ $? != 0 ]]; then
    # There was an error, display the error in $output
    echo -e "cmake Error"
    exit 1
fi

make

if [[ $? != 0 ]]; then
    # There was an error, display the error in $output
    echo -e "make Error"
else
    # Compilation successfull
    ./Arkanoid
fi