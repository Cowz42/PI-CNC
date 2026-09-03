# PI-CNC
This project is just a hobby project, and I am mostly using github for easy cloud storage I may update this more as I go, but for now it will just kinda be added to
Don't expect much, might not even finish

Run it on the PI (obviously)

I am also making the hardware part as I go, so lets see how it goes

# Installation

Dependencies
cmake          Building

Ncurses        Client CLI

wiringPI       Under the hood hardware access

https://github.com/WiringPi/WiringPi

run in project directory

cmake --build build --parallel
sudo ./install.sh

needs sudo to mount into systemctl

# Usage

run the client executable ./build/pi-cnc

the service should start from install and always be on after that

# Future


I am not going to make this too much more in depth, because this is still a hobby project

Also may make it so that you can run the client on another machine
