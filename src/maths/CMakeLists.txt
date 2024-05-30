qt_add_library(maths STATIC
    matrix3d.h matrix3d.cpp
    constants.h
    imatrix.h
    matrix2d.h matrix2d.cpp
)
target_link_libraries(maths PRIVATE
    Qt6::Core
)
target_link_libraries(maths PRIVATE
    
)
target_include_directories(maths PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
