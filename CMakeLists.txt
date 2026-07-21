cmake_minimum_required(VERSION 3.18)

project(pi-cnc)

set(CMAKE_CXX_STANDARD 17)

set(SERVICE_SOURCE_FILES
    ./service/gcode.cpp
    ./service/gcodeparse.cpp
    ./service/iocontroller.cpp
    ./service/positioncalc.cpp
    ./service/programrun.cpp
    ./service/stepper.cpp
    ./service/vfdcontrol.cpp
    ./service/globalcommunication.cpp
    ./service/gcodeinterface.cpp
    ./service/socketmanager.cpp
    ./service/servicemain.cpp
)

set(CLIENT_SOURCE_FILES
    ./service/socketmanager.cpp
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

