qt_add_library(neuralnetwork STATIC
    ineuralnetworkmodel.h
)
target_link_libraries(neuralnetwork PRIVATE
    Qt6::Core
)
target_link_libraries(neuralnetwork PRIVATE
    
)
target_include_directories(neuralnetwork PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
