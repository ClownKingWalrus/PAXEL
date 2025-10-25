cmake_minimum_required(VERSION 3.19)
project(Paxel-MSVC-Release LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(Paxel-MSVC-Release
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    signup.h signup.cpp signup.ui
    profile.h profile.cpp profile.ui
    homescreen.h homescreen.cpp homescreen.ui
    followers.h followers.cpp followers.ui
    following.h following.cpp following.ui
    follow.h follow.cpp follow.ui
    discussionboard.h discussionboard.cpp discussionboard.ui
    threadmenuwindow.h threadmenuwindow.cpp threadmenuwindow.ui
	replieswindow.h replieswindow.cpp replieswindow.ui
    utils.h utils.cpp

)

target_link_libraries(Paxel-MSVC-Release
    PRIVATE
        Qt::Core
        Qt::Widgets
)

include(GNUInstallDirs)

install(TARGETS Paxel-MSVC-Release
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET Paxel-MSVC-Release
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
