cmake_minimum_required(VERSION 3.9)
project(grettingLib VERSION 1.0.2 DESCRIPTION "My grettingLib description")
include(GNUInstallDirs)
add_library(gretting SHARED gretting.c)
set_target_properties(gretting PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER gretting.h)
target_include_directories(gretting PRIVATE .)
install(TARGETS gretting
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})