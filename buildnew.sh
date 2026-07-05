#!/bin/bash

git fetch

echo "Removing existing .o files"
cd ./Build/
rm *.o
cd ..
./build.sh