cmake_minimum_required(VERSION 3.10)
project(ECS)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

add_library(ECS
	ClassTypeId.hpp
	Component.hpp
	ComponentPool.cpp
	ComponentPool.hpp
	Config.hpp
	Entity.cpp
	Entity.hpp
	EntityAttributes.cpp
	EntityAttributes.hpp
	EntityCache.cpp
	EntityCache.hpp
	EntityPool.cpp
	EntityPool.hpp
	Id.hpp
	System.cpp
	System.hpp
	World.cpp
	World.hpp
	)
