qt_add_library(neuralnetwork STATIC
    ineuralnetworkmodel.h
    ineuralnetworklayer.h
    ineuralnetworknode.h
    lstmnode.h lstmnode.cpp
    lstmlayer.h lstmlayer.cpp
    lstmmodel.h lstmmodel.cpp
)
target_link_libraries(neuralnetwork PRIVATE
    Qt6::Core
)
target_link_libraries(neuralnetwork PRIVATE
    loss
    matrix
    exception
    activationfunctions
)
target_include_directories(neuralnetwork PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
