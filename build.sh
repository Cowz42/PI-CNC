#!/bin/bash


echo "Compiling Source Code"
./cpheader.sh
g++ -c *.cpp -Wall
cp *.o ./Build/
rm *.o
cd Build
echo "Finished Compilation, now Linking"
g++ -o a.out *o -l wiringPi
cd ..
cp ./Build/a.out ./
rm ./Build/a.out
chmod +x a.out
echo "Build Done"