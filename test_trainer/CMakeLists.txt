cmake_minimum_required(VERSION 3.14)

project(Test_Trainer LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS
    Core
    Test
)

qt_standard_project_setup()

qt_add_executable(Test_Trainer 
    testtrainer.cpp
)

target_link_libraries(Test_Trainer PRIVATE
    Qt6::Core
    Qt6::Test	
    activationfunctions
    randommanaging
    neuralnetwork
    textembedding
    optimizer
    exception
    trainer
    matrix
    loss
)
