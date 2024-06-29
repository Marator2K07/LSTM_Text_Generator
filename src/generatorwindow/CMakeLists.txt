qt_add_library(generatorwindow STATIC
    generatorwindow.h generatorwindow.cpp
)
target_link_libraries(generatorwindow PRIVATE
    Qt6::Core
    Qt6::Widgets
)
target_link_libraries(generatorwindow PRIVATE
    
)
target_include_directories(generatorwindow PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
