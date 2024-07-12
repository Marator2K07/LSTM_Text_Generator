qt_add_library(pagesandbox STATIC
    newmodelgroupbox.h newmodelgroupbox.cpp newmodelgroupbox.ui
    pagesandbox.h pagesandbox.cpp pagesandbox.ui	
)
target_link_libraries(pagesandbox PRIVATE
    Qt6::Core
    Qt6::Widgets
)
target_link_libraries(pagesandbox PRIVATE
    
)
target_include_directories(pagesandbox PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
