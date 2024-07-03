cmake_minimum_required(VERSION 3.14)

project(LSTM_Text_Generator LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_executable(LSTM_Text_Generator
    main.cpp
    mainwindow.h mainwindow.cpp mainwindow.ui
)
target_link_libraries(LSTM_Text_Generator PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Widgets
    activationfunctions
    neuralnetwork
    textembedding
    optimizer
    exception
    trainer
    matrix
    loss
)

find_package(Qt6 6.3 REQUIRED COMPONENTS
    Core
    Widgets
    Network
)

add_subdirectory(src)
add_subdirectory(test_loss)
add_subdirectory(test_matrix)
add_subdirectory(test_autodifferentiation)
add_subdirectory(test_activationfunctions)
add_subdirectory(test_textembedding)
add_subdirectory(test_neuralnetwork)
add_subdirectory(test_optimizer)
add_subdirectory(test_trainer)

include(GNUInstallDirs)
install(TARGETS LSTM_Text_Generator
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
