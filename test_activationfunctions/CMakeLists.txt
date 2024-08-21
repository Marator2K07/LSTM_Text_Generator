cmake_minimum_required(VERSION 3.14)

project(Test_ActivationFunctions LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS
    Core
    Test
)

qt_standard_project_setup()

qt_add_executable(Test_ActivationFunctions 
    testactivationfunctions.cpp
)

target_link_libraries(Test_ActivationFunctions PRIVATE
    Qt6::Core
    Qt6::Test
    activationfunctions
    randommanaging
    exception
    matrix    
)
