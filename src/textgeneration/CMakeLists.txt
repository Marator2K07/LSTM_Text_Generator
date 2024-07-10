qt_add_library(textgeneration STATIC
    itextgenerator.h
    neuralnetworktextgenerator.h neuralnetworktextgenerator.cpp
)
target_link_libraries(textgeneration PRIVATE
    Qt6::Core
    Qt6::Widgets
)
target_link_libraries(textgeneration PRIVATE
    activationfunctions
    neuralnetwork
    textembedding
    optimizer
    exception
    matrix
    loss
)
target_include_directories(textgeneration PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
