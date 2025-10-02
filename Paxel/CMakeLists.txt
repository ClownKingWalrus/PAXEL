cmake_minimum_required(VERSION 3.19)
project(Paxel LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

#Sql find for cmake
find_path(MYSQL_INCLUDE_DIR #Sets the var
    NAMES mysql/jdbc.h
    PATHS "../mysql-connector-c++-9.4.0-winx64/include"
    )

find_library(MYSQL_LIB #Sets the var
    NAMES mysqlcppconn
    PATHS "../mysql-connector-c++-9.4.0-winx64/lib64/vs14"
    )

#Sql error checking
if (NOT MYSQL_INCLUDE_DIR OR NOT MYSQL_LIB)
    message(FATAL_ERROR "Could not find MySql connector relative path?")
endif()

qt_standard_project_setup()

qt_add_executable(Paxel
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    signup.h signup.cpp signup.ui
    homescreen.h homescreen.cpp homescreen.ui
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
