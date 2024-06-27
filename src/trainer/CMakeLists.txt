qt_add_library(trainer STATIC
    itrainer.h
    consistenttrainer.h consistenttrainer.cpp
)
target_link_libraries(trainer PRIVATE
    Qt6::Core
)
target_link_libraries(trainer PRIVATE

)
target_include_directories(trainer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
