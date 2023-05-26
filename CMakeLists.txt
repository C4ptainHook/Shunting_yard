cmake_minimum_required(VERSION 3.23)
project(Shunting_yard)

set(CMAKE_CXX_STANDARD 20)

add_executable(Shunting_yard main.cpp Stack.h Queue.h Shunting_yard.h Parser.h Parser.cpp Evaluator.h)
