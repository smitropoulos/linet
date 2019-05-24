cmake_minimum_required(VERSION 3.14)
project(linet C)

set(CMAKE_C_STANDARD 99)

include_directories(include)

add_library(linet STATIC
        src/rdrwn.c
        src/inet_init.c
        )

set_target_properties(linet PROPERTIES PUBLIC_HEADER "include/inet_init.h;include/rdrwn.h")

install(TARGETS linet
        CONFIGURATIONS Debug
        RUNTIME DESTINATION /usr/local/lib/
        PUBLIC_HEADER DESTINATION /usr/local/include
        )
