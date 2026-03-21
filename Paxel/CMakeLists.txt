cmake_minimum_required(VERSION 3.19)
project(Paxel LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

#Sql find for cmake
find_path(MYSQL_INCLUDE_DIR #Sets the var
    NAMES mysql/jdbc.h
    PATHS "../mysql-connector-c++-9.4.0-winx64/include"
    )

find_library(MYSQL_LIB #Sets the var
    NAMES mysqlcppconn
    PATHS "../mysql-connector-c++-9.4.0-winx64/lib64/vs14"
    )

qt_add_resources(RESOURCES images.qrc)
qt_add_resources(RESOURCES PaxelFont.qrc)
qt_add_resources(RESOURCES ProfileImages.qrc)

message(STATUS "MYSQL_INCLUDE_DIR = ${MYSQL_INCLUDE_DIR}")
message(STATUS "MYSQL_LIB = ${MYSQL_LIB}")


#Sql error checking
if (NOT MYSQL_INCLUDE_DIR OR NOT MYSQL_LIB)
    message(FATAL_ERROR "Could not find MySql connector relative path?")
endif()

qt_standard_project_setup()

file(GLOB SOURCES
    ../hdr/*.h
    ../src/*.cpp
)

qt_add_executable(Paxel
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    signup.h signup.cpp signup.ui
    homescreen.h homescreen.cpp homescreen.ui
    discussionboard.h discussionboard.cpp discussionboard.ui
    threadmenuwindow.h threadmenuwindow.cpp threadmenuwindow.ui
    interestselect.h interestselect.cpp interestselect.ui
    replieswindow.h replieswindow.cpp replieswindow.ui
    threadbannerbox.h threadbannerbox.cpp
    YourPaxelBoard.h YourPaxelBoard.cpp YourPaxelBoard.ui
    createboardorthread.h createboardorthread.cpp createboardorthread.ui
    followedboards.h followedboards.cpp followedboards.ui
    follow.h follow.cpp follow.ui
    followers.h followers.cpp followers.ui
    following.h following.cpp following.ui
    profile.h profile.cpp profile.ui
    postreply.h postreply.cpp postreply.ui
    messagewindow.h messagewindow.cpp messagewindow.ui
    profilepicture.h profilepicture.cpp
    utils.h utils.cpp
    windowsettings.h
    ${SOURCES}
    ${RESOURCES}
)

target_include_directories(Paxel
PRIVATE
    ${MYSQL_INCLUDE_DIR}
)

target_link_libraries(Paxel
    PRIVATE
        Qt::Core
        Qt::Widgets
        ${MYSQL_LIB}
)
target_link_libraries(Paxel PRIVATE Qt6::Core Qt6::Widgets)
target_link_libraries(Paxel PRIVATE Qt6::Widgets)

include(GNUInstallDirs)

install(TARGETS Paxel
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET Paxel
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  goggletesting
  goggletesting.cpp
)
target_link_libraries(
  goggletesting
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(goggletesting)
