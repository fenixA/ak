# +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
# + CMakeLists.txt
# + Folder: src/Praktikum-7
# +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

INCLUDE_DIRECTORIES( ${CRYPTOPP_INCLUDE_DIR} 
    ${CMAKE_CURRENT_SOURCE_DIR}/../Praktikum-5
    ${CMAKE_CURRENT_SOURCE_DIR}/../Praktikum-6 )

LINK_DIRECTORIES( ${CRYPTOPP_LIBRARY_DIR} )

ADD_EXECUTABLE( encoder encoder MessageEncoder )
TARGET_LINK_LIBRARIES(encoder ${CRYPTOPP_LIBRARY} ${CMAKE_THREAD_LIBS_INIT})

ADD_EXECUTABLE( netintro netintro MessageEncoder )
TARGET_LINK_LIBRARIES(netintro ${CRYPTOPP_LIBRARY} ${CMAKE_THREAD_LIBS_INIT})

ADD_EXECUTABLE( dhprotocol 
    dhprotocol 
    MessageEncoder 
    DHProtocol 
    ${CMAKE_CURRENT_SOURCE_DIR}/../Praktikum-5/PRNG 
    ${CMAKE_CURRENT_SOURCE_DIR}/../Praktikum-6/FortunaGenerator )
TARGET_LINK_LIBRARIES(dhprotocol ${CRYPTOPP_LIBRARY} ${CMAKE_THREAD_LIBS_INIT})

