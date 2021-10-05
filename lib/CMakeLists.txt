cmake_minimum_required(VERSION 3.20)
project(PCB)

set(CMAKE_CXX_STANDARD 20)

ADD_LIBRARY( PCB STATIC Printed_Circuit_Board.h Printed_Circuit_Board.cpp )