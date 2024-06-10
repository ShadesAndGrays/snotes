cmake_minimum_required(VERSION 3.14)

project(sticky_notes CXX)

include_directories(${PROJECT_SOURCE_DIR}/include)

set(src
src/main.cpp
src/Menu.cpp
src/testRapid.cpp
src/Editor.cpp
src/exec_command.cpp
src/Notes.cpp
)

set (CMAKE_EXPORT_COMPILE_COMMANDS on )

set(CMAKE_BUILD_TYPE Release)

#[[ add_compile_definitions(
    RAYGUI_IMPLEMENTATION
) ]]



add_executable(${PROJECT_NAME} ${src})


find_package(raylib) 
find_package(fmt) 
find_package(RapidJSON) 


target_link_libraries(${PROJECT_NAME} raylib fmt)

file(COPY ${CMAKE_SOURCE_DIR}/test.json DESTINATION ${CMAKE_BINARY_DIR})

install(TARGETS ${PROJECT_NAME})
