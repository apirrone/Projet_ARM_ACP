cmake_minimum_required(VERSION 3.5)

# project name
project(VisioBrain)

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
