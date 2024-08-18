qt_add_library(randommanaging STATIC
    distributor.h distributor.cpp
)
target_link_libraries(randommanaging PRIVATE
    Qt6::Core
)
target_link_libraries(randommanaging PRIVATE

)
target_include_directories(randommanaging PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
