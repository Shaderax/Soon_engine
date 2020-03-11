cmake_minimum_required(VERSION 3.10)

project(ECS)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

include_directories(./)

add_library(ECS
	Component.cpp
	ComponentPool.cpp
	Entity.cpp
	EntityAttributes.cpp
	EntityCache.cpp
	EntityPool.cpp
	System.cpp
	World.cpp
	)
