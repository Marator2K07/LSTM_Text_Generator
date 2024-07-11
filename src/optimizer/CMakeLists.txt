qt_add_library(optimizer STATIC
    ioptimizer.h
    sgd.h sgd.cpp
    adagrad.h adagrad.cpp
)
target_link_libraries(optimizer PRIVATE
    Qt6::Core
)
target_link_libraries(optimizer PRIVATE
    loss
    matrix
    exception
    textembedding
    neuralnetwork
    activationfunctions
)
target_include_directories(optimizer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
