qt_add_library(textgenerator STATIC
    itextgenerator.h
    neuralnetworktextgenerator.h neuralnetworktextgenerator.cpp
)
target_link_libraries(textgenerator PRIVATE
    Qt6::Core
    Qt6::Widgets
)
target_link_libraries(textgenerator PRIVATE
    activationfunctions
    randommanaging
    neuralnetwork
    textembedding
    optimizer
    exception
    matrix
    loss
)
target_include_directories(textgenerator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
