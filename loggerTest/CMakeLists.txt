cmake_minimum_required(VERSION 3.0)
project(loggerTest)
set(sources main.cpp
	Logger.cpp
	)
add_executable(${PROJECT_NAME} ${sources})
