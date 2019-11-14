cmake_minimum_required(VERSION 3.10)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpic -std=c++11")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

qt5_wrap_ui(UIS_HEADERS
        views/connectview.ui
        views/menuwindow.ui
        )

qt5_wrap_cpp(CPP_MOCK
        views/connectview.h
        views/menuwindow.h
        )


add_library (connectView
        views/connectview.cpp
        ${CPP_MOCK}
        ${UIS_HEADERS}
        )

add_library (menuWindow
        views/menuwindow.cpp
        ${CPP_MOCK}
        ${UIS_HEADERS}
        )


add_library(viewManager
        view_manager.cpp)

target_link_libraries(connectView common Qt5::Widgets)
target_link_libraries(menuWindow common Qt5::Widgets)
target_link_libraries(viewManager common menuWindow connectView Qt5::Widgets)