cmake_minimum_required(VERSION 3.18)


project(PI-CNC)
add_executable(PI-CNC)
add_library(PI-CNC-LIB)


target_sources(PI-CNC
	PRIVATE
		main.cpp
		
)

target_sources(PI-CNC-LIB
	PRIVATE
		gcode.cpp
		gcodeparse.cpp
		iocontroller.cpp
		positioncalc.cpp
		programrun.cpp
		stepper.cpp
		vfdcontrol.cpp

	PUBLIC
		FILE_SET publicHeaders
		TYPE HEADERS
		FILES
			gcode.h
			gcodeparse.h
			iocontroller.h
			positioncalc.h
			stepper.h
			vfdcontrol.h
			

	INTERFACE
		FILE_SET deviceInfoHeaders
		TYPE HEADERS
		FILES
			buttoninfo.h
			commands.h
			gcodeinterface.h
			machine.h
			vfdcommands.h
			
)




target_link_libraries(PI-CNC
	PRIVATE
		PI-CNC-LIB
)

