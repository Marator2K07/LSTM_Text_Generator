qt_add_library(activationfunctions STATIC
    activationfunctions.h activationfunctions.cpp
)
target_link_libraries(activationfunctions PRIVATE
    Qt6::Core
)
target_link_libraries(activationfunctions PRIVATE
    
)
target_include_directories(activationfunctions PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
