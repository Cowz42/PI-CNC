cmake_minimum_required(VERSION 3.18)

project(pi-cnc)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
    gcode.cpp
    gcodeparse.cpp
    iocontroller.cpp
    positioncalc.cpp
    programrun.cpp
    stepper.cpp
    vfdcontrol.cpp
    globalcommunication.cpp
    clidisplay.cpp
    main.cpp
)


find_package(Curses REQUIRED)




include_directories(${CURSES_INCLUDE_DIR})


add_executable(${PROJECT_NAME} ${SOURCE_FILES})



#add_subdirectory(./lib/glfw-3.4/)
#target_link_libraries(${PROJECT_NAME} glfw)



target_link_libraries(
	${PROJECT_NAME}

	PRIVATE ${CURSES_LIBRARIES}

	PRIVATE wiringPi
)


