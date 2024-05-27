cmake_minimum_required(VERSION 3.14)

project(LSTM_Text_Generator_Test LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS
    Core
    Test
)

qt_standard_project_setup()

qt_add_executable(LSTM_Text_Generator_Test
    test.cpp
)

target_link_libraries(LSTM_Text_Generator_Test PRIVATE
    Qt6::Core
    Qt6::Test
    lstm
    loss
)
