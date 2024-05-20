qt_add_library(lstm STATIC
    num.h
    constants.h
    numwithgradient.h numwithgradient.cpp    
)
target_link_libraries(lstm PRIVATE
    Qt6::Core
)
target_link_libraries(lstm PRIVATE
    
)
target_include_directories(lstm PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
