cmake_minimum_required(VERSION 3.14)

project(Test_Optimizer LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS
    Core
    Test
)

qt_standard_project_setup()

qt_add_executable(Test_Optimizer 
    testoptimizer.cpp
)

target_link_libraries(Test_Optimizer PRIVATE
    Qt6::Core
    Qt6::Test	
    activationfunctions
    neuralnetwork
    textembedding
    optimizer
    exception
    matrix
    loss
)
