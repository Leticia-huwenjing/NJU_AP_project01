cmake_minimum_required(VERSION 3.21)
project(project01)

set(CMAKE_CXX_STANDARD 14)

add_executable(project01 main.cpp seller.cpp seller.h buyer.cpp buyer.h admin.cpp admin.h user.cpp user.h data.h sql.cpp sql.h calculator.cpp calculator.h file.cpp file.h)
