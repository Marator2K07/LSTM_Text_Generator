qt_add_library(textgeneration STATIC
    itextgeneration.h
)
target_link_libraries(textgeneration PRIVATE
    Qt6::Core
)
target_link_libraries(textgeneration PRIVATE
    neuralnetwork
    exception
    matrix
    loss
)
target_include_directories(textgeneration PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
