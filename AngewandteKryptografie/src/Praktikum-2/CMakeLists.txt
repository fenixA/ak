# +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
# + CMakeLists.txt
# + Folder: src/Praktikum-2
# +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_SOURCE_DIR}/../Praktikum-1)

ADD_EXECUTABLE( vigenere vigenere VigenereCipher ../Praktikum-1/ClassicCipher)

ADD_EXECUTABLE( kasiski kasiski VigenereBreaker VigenereCipher ../Praktikum-1/ClassicCipher)

ADD_EXECUTABLE( coindex coindex VigenereBreaker VigenereCipher ../Praktikum-1/ClassicCipher)

ADD_EXECUTABLE( searchshift searchshift VigenereBreaker VigenereCipher ../Praktikum-1/ClassicCipher)

ADD_EXECUTABLE( vbreaker vbreaker VigenereBreaker VigenereCipher ../Praktikum-1/ClassicCipher)
