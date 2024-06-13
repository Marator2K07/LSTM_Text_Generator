qt_add_library(neuralnetwork STATIC
    ineuralnetworkmodel.h
    ineuralnetworknode.h
)
target_link_libraries(neuralnetwork PRIVATE
    Qt6::Core
)
target_link_libraries(neuralnetwork PRIVATE
    matrix
)
target_include_directories(neuralnetwork PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
