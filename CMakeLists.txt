cmake_minimum_required(VERSION 3.14)

project(sticky_notes CXX)

set(src
src/main.cpp
src/testRapid.cpp
)

set (CMAKE_EXPORT_COMPILE_COMMANDS on )

message("CMAKE BUILD TYPE: " ${CMAKE_BUILD_TYPE})

add_compile_definitions(-DRAYGUI_IMPLEMENTATION)


add_executable(${PROJECT_NAME} ${src})

include_directories(include)


find_package(raylib) 
find_package(fmt) 
find_package(RapidJSON) 


target_link_libraries(${PROJECT_NAME} raylib fmt)

file(COPY ${CMAKE_SOURCE_DIR}/test.json DESTINATION ${CMAKE_BINARY_DIR})
