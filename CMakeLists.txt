# CMakeTutorial

cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(CMakeTutorial VERSION 1.0.0 LANGUAGES C)


# External packages

find_package(HDF5 COMPONENTS C HL REQUIRED)

add_subdirectory(src)
