qt_add_library(loss STATIC
    iloss.h
    softmaxcrossentropyloss.h softmaxcrossentropyloss.cpp
    activationfunctions.h activationfunctions.cpp
)
target_link_libraries(loss PRIVATE
    Qt6::Core
)
target_link_libraries(loss PRIVATE
    maths
)
target_include_directories(loss PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
