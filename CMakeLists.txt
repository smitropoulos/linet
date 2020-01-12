cmake_minimum_required(VERSION 3.14)
project(linet LANGUAGES C)

# Add _debug when building a debug configuration of the library
set(CMAKE_DEBUG_POSTFIX _debug)

add_library(linet STATIC
            src/inet_rdrwn.c
            src/inet_sockets.c
            src/inet_spec_packet.c
            src/inet_oper.c
            )

#set_target_properties(linet PROPERTIES COMPILE_FLAGS "-Wall -Werror")
set_target_properties(linet PROPERTIES PUBLIC_HEADER "include/inet_oper.h;include/inet_rdrwn.h;include/inet_sockets.h;include/inet_spec_packet.h")

target_include_directories(linet
                           PUBLIC
                           $<INSTALL_INTERFACE:include>
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                           PRIVATE
                           ${CMAKE_CURRENT_SOURCE_DIR}/src
                           )

# Add git version of the project inside the src code
find_package(Git REQUIRED)
execute_process(
        COMMAND ${GIT_EXECUTABLE} rev-list -1 HEAD -- projectVersionDetails.cmake
        RESULT_VARIABLE result
        OUTPUT_VARIABLE lastChangeHash
        OUTPUT_STRIP_TRAILING_WHITESPACE
)

if (result)
    message(FATAL_ERROR "Failed to get hash of last change: ${result}")
endif ()

execute_process(
        COMMAND ${GIT_EXECUTABLE} rev-list ${lastChangeHash}..HEAD
        RESULT_VARIABLE result
        OUTPUT_VARIABLE hashList
        OUTPUT_STRIP_TRAILING_WHITESPACE
)
if (result)
    message(FATAL_ERROR "Failed to get list of git hashes: ${result}")
endif ()
string(REGEX REPLACE "[\n\r]+" ";" hashList "${hashList}")
list(LENGTH hashList FooBar_COMMITS_SINCE_VERSION_CHANGE)

configure_file(linet_version.c.in src/linetbar_version.c @ONLY)

# 'make install' to the correct locations (provided by GNUInstallDirs).
include(GNUInstallDirs)
install(TARGETS linet
        EXPORT linetConfig
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        )

# This makes the project importable from the install directory
# Put config file in per-project dir (name MUST match), can also
# just go into 'cmake'.
install(EXPORT linetConfig
        NAMESPACE linet::
        DESTINATION share/linet/cmake
        )

# This makes the project importable from the build directory
export(TARGETS linet
       FILE linetConfig.cmake
       )

set(CPACK_PACKAGE_VERSION ${VERSION})
set(CPACK_GENERATOR "RPM")
set(CPACK_PACKAGE_NAME "linet")
set(CPACK_PACKAGE_RELEASE ${PROJECT_VERSION})
set(CPACK_PACKAGE_CONTACT "Stefanos Mitropoulos")
set(CPACK_PACKAGING_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX})
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CPACK_PACKAGE_RELEASE}.${CMAKE_SYSTEM_PROCESSOR}")
include(CPack)

