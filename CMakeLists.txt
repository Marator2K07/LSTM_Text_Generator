cmake_minimum_required(VERSION 3.14)

project(RNN_Core LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_executable(RNN_Core
  main.cpp
)
target_link_libraries(RNN_Core Qt${QT_VERSION_MAJOR}::Core)

find_package(Qt6 6.3 REQUIRED COMPONENTS
    Core
    Widgets
    Network
)

include(GNUInstallDirs)
install(TARGETS RNN_Core
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
