cmake_minimum_required(VERSION 3.9)
project(Akinator C)

set(CMAKE_C_STANDARD 99)

add_executable(Akinator main.c Node/Node.c Node/Node.h Akinator/Akinator.h Akinator/Akinator.c Determination/Determination.c Determination/Determination.h Stack/Stack.c Stack/Stack.h)