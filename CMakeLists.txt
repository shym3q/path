cmake_minimum_required(VERSION 3.4...3.18)
project(ok)
add_subdirectory(pybind11)
pybind11_add_module(module_name main.cpp)
