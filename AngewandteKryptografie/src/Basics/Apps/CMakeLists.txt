# +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
# + CMakeLists.txt
# + Folder: src/Basics/Apps
# +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

ADD_EXECUTABLE( helloWorld helloWorld )
ADD_EXECUTABLE( helloStudi helloStudi Greetings)
INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_SOURCE_DIR}/../Lib)
ADD_EXECUTABLE( calculate calculate )
TARGET_LINK_LIBRARIES( calculate functions )
ADD_EXECUTABLE( message message Secret )
