qt_add_library(matrix STATIC
    imatrix.h
    matrix2d.h matrix2d.cpp
    matrix3d.h matrix3d.cpp    
)
target_link_libraries(matrix PRIVATE
    Qt6::Core
)
target_link_libraries(matrix PRIVATE
    loss
    exception    
    activationfunctions
)
target_include_directories(matrix PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
