cmake_minimum_required(VERSION 3.9)
project(grettingLib VERSION 1.0.2 DESCRIPTION "My countLib description")
include(GNUInstallDirs)
add_library(count SHARED count.c)
set_target_properties(count PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER count.h)
