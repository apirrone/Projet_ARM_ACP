cmake_minimum_required(VERSION 3.5)

# project name
project(VisioBrain)

set(CMAKE_CXX_STANDARD 11)

# Qt5
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5 COMPONENTS Core Widgets OpenGL REQUIRED)

#CGAL
find_package(CGAL REQUIRED COMPONENTS Core) # If the dependency is required, use REQUIRED option - if it's not found CMake will issue an error
include( ${CGAL_USE_FILE} )

#Variable "source_files" to store all the files in src directory
file(
  GLOB_RECURSE
  source_files
  src/*
  include/*
)

include_directories(ext/)
include_directories(assets/)
include_directories(include/)
include_directories(eigen3/)

# Executable + source_files
add_executable(
  VisioBrain
  ${source_files}
  )

target_link_libraries(VisioBrain Qt5::Widgets Qt5::Core Qt5::OpenGL GL)
