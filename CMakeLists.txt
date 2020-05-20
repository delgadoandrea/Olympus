# $Id$

#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
cmake_policy(SET CMP0020 NEW)
project(OLYMPUSEX)

#----------------------------------------------------------------------------
# Qt package
#set (CMAKE_PREFIX_PATH "C:\\Users\\delga\\Geant4_10_4\\Qt5\\qt-5.6.3")
include_directories("C:\\Users\\delga\\Geant4_10_4\\xerces-c\\install\\lib\\")
find_package(Qt5Core REQUIRED)
find_package(ROOT REQUIRED COMPONENTS RIO Net)


find_package(XercesC REQUIRED)

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#

find_package(Geant4 REQUIRED ui_all vis_all)

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
# Setup include directory for this project
#
include(${Geant4_USE_FILE})
include(${ROOT_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)


#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
#
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#

#link_directories(C:\Users\delga\Geant4_10_4\xerces-c\install\lib\) 

add_executable(Olympus Olympus.cc ${sources} ${headers})
target_link_libraries(Olympus ${Geant4_LIBRARIES})
target_link_libraries(Olympus ${ROOT_LIBRARIES})
target_link_libraries(Olympus xerces-c_3D.lib)


#find_package(ROOT REQUIRED COMPONENTS Core MathCore MathMore RIO Tree)
#include_directories(SYSTEM ${ROOT_INCLUDE_DIRS})
#----------------------------------------------------------------------------
# Copy all scripts to the build directory, i.e. the directory in which we
# build B1. This is so that we can run the executable directly because it
# relies on these scripts being in the current working directory.
#
set(Olympus_SCRIPTS
  init_vis.mac
  vis.mac
  )

foreach(_script ${Olympus_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()

#----------------------------------------------------------------------------
# For internal Geant4 use - but has no effect if you build this
# example standalone
#
add_custom_target(OLYMPUSEX DEPENDS Olympus)


