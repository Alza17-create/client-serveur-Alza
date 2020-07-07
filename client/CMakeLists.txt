cmake_minimum_required(VERSION 3.10.2)
project(fork)

include_directories(../include)
set(SOURCES myClient.c)
add_executable(myClient ${SOURCES})
