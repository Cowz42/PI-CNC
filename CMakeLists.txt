


# Version on the PI is this one, so I am going with the greatest
# common denominator
cmake_minimum_required(VERSION 3.18)

project(pi-cnc)

# I forgot why but I needed this one for a reason
set(CMAKE_CXX_STANDARD 17)

# Need to rebuild some of the headers for the arduino, because it
# can't find the headers in other folders easy, so lowtech it is
execute_process(
    COMMAND cpheader.sh
)



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

set(CLIENT_SOURCE_FILES
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

add_executable(${PROJECT_NAME} ${CLIENT_SOURCE_FILES})




target_link_libraries(
	${PROJECT_NAME}

	PRIVATE ${CURSES_LIBRARIES}
)

target_link_libraries(
    pi-cnc-service-exec

	PRIVATE wiringPi
)

