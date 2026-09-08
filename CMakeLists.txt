


# Version on the PI is this one, so I am going with the greatest
# common denominator
cmake_minimum_required(VERSION 3.18)

project(pi-cnc)

# I forgot why but I needed this one for a reason
set(CMAKE_CXX_STANDARD 17)





# Need to rebuild some of the headers for the arduino, because it
# can't find the headers in other folders easy, so lowtech it is
# I fucking hate you arduino
# WHY CAN"T YOU BE NORMAL AND HAVE RELATIVE BUILD PATHS
# AOIEFJLIADJFLSJGOSJDFJNOSDFJHOSFIJ

execute_process(
    COMMAND bash -c "../scripts/cpheaderCMAKE.sh"
)

# Compile Arduino code
execute_process(
    COMMAND bash -c "arduino-cli compile -b arduino:avr:nano  ../vfd/vfd.ino
"
)

# The background service source files
set(SERVICE_SOURCE_FILES
    ./service/gcode.cpp
    ./service/gcodeparse.cpp
    ./service/iocontroller.cpp
    ./service/positioncalc.cpp
    ./service/programrun.cpp
    ./service/stepper.cpp
    ./service/vfdcontrol.cpp
    ./service/gcodeinterface.cpp

    ./globaldef/socketmanager.cpp
    ./globaldef/file.cpp
    ./globaldef/globalcommunication.cpp
    ./globaldef/netpacket.cpp

    ./service/servicemain.cpp
)

# The cli client source files
set(CLIENT_CLI_SOURCE_FILES
    ./globaldef/socketmanager.cpp
    ./globaldef/file.cpp
    ./globaldef/globalcommunication.cpp
    ./globaldef/netpacket.cpp

    ./clientcli/clidisplay.cpp

    ./clientcli/clientmain.cpp
)


find_package(Curses REQUIRED)




include_directories(${CURSES_INCLUDE_DIR})


add_executable(pi-cnc-service-exec ${SERVICE_SOURCE_FILES})

add_executable(pi-cnc-cli ${CLIENT_CLI_SOURCE_FILES})




target_link_libraries(
	pi-cnc-cli

	PRIVATE ${CURSES_LIBRARIES}
)

target_link_libraries(
    pi-cnc-service-exec

	PRIVATE wiringPi
)

