# +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
# + CMakeLists.txt
# + Folder: src/Praktikum-6
# +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

INCLUDE_DIRECTORIES( ${CRYPTOPP_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../Praktikum-5)

ADD_EXECUTABLE( primes  primes  FortunaGenerator MillerRabinTest 
    ${CMAKE_CURRENT_SOURCE_DIR}/../Praktikum-5/PRNG )

TARGET_LINK_LIBRARIES(primes ${CRYPTOPP_LIBRARY} ${CMAKE_THREAD_LIBS_INIT})


