qt_add_library(matrix STATIC
    constants.h
    matrix.h matrix.cpp
)
target_link_libraries(matrix PRIVATE
    Qt6::Core
)
target_link_libraries(matrix PRIVATE
    
)
target_include_directories(matrix PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
