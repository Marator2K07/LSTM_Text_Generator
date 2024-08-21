qt_add_library(textembedding STATIC
    itextembedding.h
    charasvectorembedding.h charasvectorembedding.cpp
)
target_link_libraries(textembedding PRIVATE
    Qt6::Core
)
target_link_libraries(textembedding PRIVATE
    loss
    matrix
    exception
    randommanaging
    activationfunctions
)
target_include_directories(textembedding PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
