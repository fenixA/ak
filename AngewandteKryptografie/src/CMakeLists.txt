# +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
# + CMakeLists.txt
# + Folder: src
# +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

PROJECT(AngewandteKryptografie)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin )

SET(CMAKE_VERBOSE_MAKEFILE true)

ADD_SUBDIRECTORY( Basics )

SET( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
${PROJECT_SOURCE_DIR}/CMakeModules)
ADD_SUBDIRECTORY( Praktikum-1 )
ADD_SUBDIRECTORY( Praktikum-2 )
ADD_SUBDIRECTORY( Praktikum-3 )
ADD_SUBDIRECTORY( Praktikum-4 )
ADD_SUBDIRECTORY( Praktikum-5 )
ADD_SUBDIRECTORY( Praktikum-6 )
ADD_SUBDIRECTORY( Praktikum-7 )
