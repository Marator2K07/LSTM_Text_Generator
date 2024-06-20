cmake_minimum_required(VERSION 3.14)

project(Test_NeuralNetwork LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS
    Core
    Test
)

qt_standard_project_setup()

qt_add_executable(Test_NeuralNetwork 
    testneuralnetwork.cpp
)

target_link_libraries(Test_NeuralNetwork PRIVATE
    Qt6::Core
    Qt6::Test	
    activationfunctions
    neuralnetwork
    textembedding    
    exception
    matrix
    loss
)
