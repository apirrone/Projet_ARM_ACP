cmake_minimum_required(VERSION 3.5)

# project name
project(VisioBrain)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)


#Variable "source_files" to store all the files in src directory
file(
  GLOB_RECURSE
  source_files
  src/*
)

# Executable + source_files
add_executable(
  VisioBrain
  ${source_files}
  )

target_link_libraries(VisioBrain Qt5::Widgets Qt5::Core)

