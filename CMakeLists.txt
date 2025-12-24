cmake_minimum_required(VERSION 3.28)
project(logc)

set(LIB_NAME logc)

file(GLOB_RECURSE LOGC_SOURCES src/*.c)

add_library(${LIB_NAME} STATIC ${LOGC_SOURCES})

target_include_directories(${LIB_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_compile_features(${LIB_NAME} PUBLIC c_std_99)

set_target_properties(${LIB_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ON)

