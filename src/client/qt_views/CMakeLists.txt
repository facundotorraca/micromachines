cmake_minimum_required(VERSION 3.10)

project(qt-views)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Find the QtWidgets library
find_package(Qt5Widgets)

qt5_wrap_ui(UIS_HEADERS
        client_views/mainwindow.ui
        client_views/conectView.ui
        client_views/createWindow.ui
        )

qt5_wrap_cpp(CPP_MOCK
        client_views/ConectView.h
        client_views/MainWindow.h
        client_views/CreateWindow.h)


message("Headers generados: ${UIS_HEADERS}")
# Agrego la carpeta con los headers autogenerados a los includes
message("Agregando '${PROJECT_BINARY_DIR}' como directorio de includes")
include_directories(${PROJECT_BINARY_DIR})


add_library (mainView
        client_views/MainWindow.cpp
        ${CPP_MOCK}
        ${UIS_HEADERS}
        )

add_library(createView
        client_views/CreateWindow.cpp
        ${CPP_MOCK}
        ${UIS_HEADERS}
        )

add_library(conectView
        client_views/ConectView.cpp
        ${CPP_MOCK}
        ${UIS_HEADERS})

add_library(viewManager
        view_manager.cpp)

target_link_libraries(createView common Qt5::Widgets)
target_link_libraries(mainView common Qt5::Widgets)
target_link_libraries(conectView common Qt5::Widgets)
target_link_libraries(viewManager common mainView conectView Qt5::Widgets)