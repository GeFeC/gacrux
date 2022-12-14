cmake_minimum_required(VERSION 3.10)

project(gacrux)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE sources 
  src/*.cpp 
  src/*.hpp 
  Framework/*.hpp
  Framework/*.cpp
  vendor/glad.c
  vendor/stb.cpp
)

add_executable(${PROJECT_NAME} ${sources})

set(includes
  src
  vendor/glfw/include 
  vendor/freetype/include
  vendor/include
)

set(lib_dirs lib)

set(libs 
  glfw
  pthread
  freetype
)

target_include_directories(${PROJECT_NAME} PUBLIC ${includes})
target_link_directories(${PROJECT_NAME} PUBLIC ${lib_dirs})
target_link_libraries(${PROJECT_NAME} PUBLIC ${libs})

add_subdirectory(${CMAKE_SOURCE_DIR}/vendor/glfw)
add_subdirectory(${CMAKE_SOURCE_DIR}/vendor/freetype)

add_dependencies(glfw freetype)
