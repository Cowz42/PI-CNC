cmake_minimum_required(VERSION 3.18)

project(pi-cnc)

set(SOURCE_FILES
    gcode.cpp
    gcodeparse.cpp
    iocontroller.cpp
    positioncalc.cpp
    programrun.cpp
    stepper.cpp
    vfdcontrol.cpp
    main.cpp
)

#add_subdirectory(./lib/glfw-3.4/)
#target_link_libraries(${PROJECT_NAME} glfw)


add_executable(${PROJECT_NAME} ${SOURCE_FILES})


target_link_libraries(
	${PROJECT_NAME}

	PRIVATE wiringPi
)


