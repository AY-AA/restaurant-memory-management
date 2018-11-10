cmake_minimum_required(VERSION 3.12)
project(Restaurant)

set(CMAKE_CXX_STANDARD 11)

add_executable(Restaurant src/Main.cpp src/Action.cpp src/Customer.cpp src/Dish.cpp src/Restaurant.cpp src/Table.cpp src/Dish.cpp)