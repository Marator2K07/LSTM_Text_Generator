qt_add_library(optimizer STATIC
    ioprimizer.h
)
target_link_libraries(optimizer PRIVATE
    Qt6::Core
)
target_link_libraries(optimizer PRIVATE
    matrix
    exception
    neuralnetwork
)
target_include_directories(optimizer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
