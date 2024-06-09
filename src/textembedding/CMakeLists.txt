qt_add_library(textembedding STATIC
    itextembedding.h
)
target_link_libraries(textembedding PRIVATE
    Qt6::Core
)
target_link_libraries(textembedding PRIVATE
    matrix
)
target_include_directories(textembedding PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
