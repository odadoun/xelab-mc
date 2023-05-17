cmake_minimum_required(VERSION 3.24 FATAL_ERROR)

# Setting project options
project(xelab_mc LANGUAGES C CXX)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Searching and copying files
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)
file(GLOB MACRO_FILES "*.mac")
file(COPY ${MACRO_FILES} DESTINATION ${PROJECT_BINARY_DIR})
file(GLOB DATA_FILES "*.dat")
file(COPY ${DATA_FILES} DESTINATION ${PROJECT_BINARY_DIR})

# Creating the executable
add_executable(xelab_mc xelab_mc.cc ${sources} ${headers})
target_include_directories(xelab_mc PRIVATE ${PROJECT_SOURCE_DIR}/include)

# Setting GEANT4
find_package(Geant4 REQUIRED ui_all vis_all)
include(${Geant4_USE_FILE})
target_link_libraries(xelab_mc PRIVATE ${Geant4_LIBRARIES})
