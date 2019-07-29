cmake_minimum_required(VERSION 3.14)
project(linet C)

set(CMAKE_C_STANDARD 99)
SET(CMAKE_CXX_FLAGS -o3)

include_directories(include)

add_library(linet STATIC
        src/inet_rdrwn.c
        src/inet_sockets.c
        include/inet_spec_packet.h src/inet_spec_packet.c src/inet_oper.c include/inet_oper.h)

FILE(GLOB headerFiles include/*.h)

SET(INST_DIR "/usr/local")
#Install header files
INSTALL(
        DIRECTORY ${CMAKE_SOURCE_DIR}/include/
        DESTINATION "${INST_DIR}/include"
        FILES_MATCHING PATTERN "*.h*")
#Install the library
INSTALL(TARGETS linet DESTINATION ${INST_DIR}/lib)
#[[===================================================================]]