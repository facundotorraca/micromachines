cmake_minimum_required(VERSION 3.10)

project(qt-views)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Find the QtWidgets library
find_package(Qt5Widgets)

qt5_wrap_ui(UIS_HEADERS
        client_views/mainwindow.ui
        client_views/conectview.ui
        client_views/createView.ui
        client_views/joinView.ui
        client_views/startView.ui
        client_views/waitView.ui
        )

qt5_wrap_cpp(CPP_MOCK
        client_views/ConectView.h
        client_views/MainWindow.h
        client_views/CreateView.h
        client_views/JoinView.h
        client_views/StartView.h
        client_views/WaitView.h
        )


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
        client_views/CreateView.cpp
        ${CPP_MOCK}
        ${UIS_HEADERS})

add_library(joinView
        client_views/JoinView.cpp
        ${CPP_MOCK}
        ${UIS_HEADERS})

add_library(conectView
        client_views/ConectView.cpp
        ${CPP_MOCK}
        ${UIS_HEADERS})

add_library(waitView
        client_views/WaitView.cpp
        ${CPP_MOCK}
        ${UIS_HEADERS})

add_library(startView
        client_views/StartView.cpp
        ${CPP_MOCK}
        ${UIS_HEADERS})



add_library(viewManager
        view_manager.cpp)

target_link_libraries(startView common Qt5::Widgets)
target_link_libraries(waitView common Qt5::Widgets)
target_link_libraries(joinView common Qt5::Widgets)
target_link_libraries(createView common Qt5::Widgets)
target_link_libraries(mainView createView joinView common Qt5::Widgets)
target_link_libraries(conectView common Qt5::Widgets)
target_link_libraries(viewManager common mainView conectView Qt5::Widgets)