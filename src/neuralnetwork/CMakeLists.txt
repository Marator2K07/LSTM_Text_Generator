qt_add_library(neuralnetwork STATIC
    ineuralnetworkmodel.h
    autodifferentiation/num.h
    autodifferentiation/numwithgradient.h
    autodifferentiation/numwithgradient.cpp
    autodifferentiation/simplenum.h
    autodifferentiation/simplenum.cpp
)
target_link_libraries(neuralnetwork PRIVATE
    Qt6::Core
)
target_link_libraries(neuralnetwork PRIVATE
    
)
target_include_directories(neuralnetwork PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
