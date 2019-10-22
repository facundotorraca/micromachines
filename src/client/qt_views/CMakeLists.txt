cmake_minimum_required(VERSION 3.10)

qt5_wrap_ui(UIS_HEADERS
        views/mainwindow.ui
        views/conectview.ui
        views/createView.ui
        views/joinView.ui
        views/startView.ui
        views/waitView.ui
        )

qt5_wrap_cpp(CPP_MOCK
        views/ConectView.h
        views/MainWindow.h
        views/CreateView.h
        views/JoinView.h
        views/StartView.h
        views/WaitView.h
        )


add_library (mainView
        views/MainWindow.cpp
        ${CPP_MOCK}
        ${UIS_HEADERS}
        )

add_library(createView
        views/CreateView.cpp
        ${CPP_MOCK}
        ${UIS_HEADERS})

add_library(joinView
        views/JoinView.cpp
        ${CPP_MOCK}
        ${UIS_HEADERS})

add_library(conectView
        views/ConectView.cpp
        ${CPP_MOCK}
        ${UIS_HEADERS})

add_library(waitView
        views/WaitView.cpp
        ${CPP_MOCK}
        ${UIS_HEADERS})

add_library(startView
        views/StartView.cpp
        ${CPP_MOCK}
        ${UIS_HEADERS})



add_library(viewManager
        view_manager.cpp)

target_link_libraries(startView common Qt5::Widgets)
target_link_libraries(waitView common Qt5::Widgets)
target_link_libraries(joinView common Qt5::Widgets)
target_link_libraries(createView common Qt5::Widgets)
target_link_libraries(mainView createView joinView startView waitView common Qt5::Widgets)
target_link_libraries(conectView common Qt5::Widgets)
target_link_libraries(viewManager common mainView conectView Qt5::Widgets)