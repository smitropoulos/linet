cmake_minimum_required(VERSION 3.14)
project(linet VERSION 1.6.0 LANGUAGES C)

set(CMAKE_C_STANDARD 99)
SET(CMAKE_CXX_FLAGS -o3)

add_library(linet STATIC
        src/inet_rdrwn.c
        src/inet_sockets.c
        src/inet_spec_packet.c
        src/inet_oper.c
        )

set_target_properties(linet PROPERTIES COMPILE_FLAGS "-Wall -Werror")

target_include_directories(linet
        PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        )

# 'make install' to the correct locations (provided by GNUInstallDirs).
include(GNUInstallDirs)
install(TARGETS linet
        EXPORT linetConfig
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
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
set(CPACK_PACKAGE_RELEASE 1)
set(CPACK_PACKAGE_CONTACT "Stefanos Mitropoulos")
set(CPACK_PACKAGING_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX})
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CPACK_PACKAGE_RELEASE}.${CMAKE_SYSTEM_PROCESSOR}")
include(CPack)

