#!/bin/bash


echo "Compiling Source Code"
./cpheader.sh
g++ -c gcode.cpp -Wall
g++ -c gcodeparse.cpp -Wall
g++ -c iocontroller.cpp -Wall
g++ -c positioncalc.cpp -Wall
g++ -c programrun.cpp -Wall
g++ -c stepper.cpp -Wall
g++ -c vfdcontrol.cpp -Wall

if [$1 == "main" OR $1 == ""]
g++ -c main.cpp -Wall
cd ./Build/
rm tests.o
cd ..
fi

if [$1 == "tests"]
g++ -c tests.cpp -Wall
cd ./Build/
rm main.o
cd ..
fi


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