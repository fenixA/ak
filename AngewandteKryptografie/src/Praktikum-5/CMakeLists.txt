# +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
# + CMakeLists.txt
# + Folder: src/Praktikum-5
# +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

FIND_PACKAGE(CryptoPP REQUIRED)
FIND_PACKAGE(Threads REQUIRED)

INCLUDE_DIRECTORIES(${CRYPTOPP_INCLUDE_DIR})

ADD_EXECUTABLE(cryptopp-intro cryptopp-intro PRNG BlumBlumShubGenerator)
TARGET_LINK_LIBRARIES(cryptopp-intro ${CRYPTOPP_LIBRARY} ${CMAKE_THREAD_LIBS_INIT})



