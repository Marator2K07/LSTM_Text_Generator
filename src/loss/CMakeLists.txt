qt_add_library(loss STATIC
    loss.h
)
target_link_libraries(loss PRIVATE
    Qt6::Core
)
target_link_libraries(loss PRIVATE
    
)
target_include_directories(loss PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
