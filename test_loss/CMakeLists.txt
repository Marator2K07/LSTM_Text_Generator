cmake_minimum_required(VERSION 3.14)

project(Test_Loss LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS
    Core
    Test
)

qt_standard_project_setup()

qt_add_executable(Test_Loss
    testloss.cpp
)

target_link_libraries(Test_Loss PRIVATE
    Qt6::Core
    Qt6::Test
    loss
    matrix
    exception
    activationfunctions
)
