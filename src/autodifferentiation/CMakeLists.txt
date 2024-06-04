qt_add_library(autodifferentiation STATIC
    inum.h
    numwithgradient.h numwithgradient.cpp
    simplenum.h simplenum.cpp
)
target_link_libraries(autodifferentiation PRIVATE
    Qt6::Core
)
target_link_libraries(autodifferentiation PRIVATE
    
)
target_include_directories(autodifferentiation PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
