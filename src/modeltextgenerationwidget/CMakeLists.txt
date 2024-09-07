qt_add_library(modeltextgenerationwidget STATIC
    directorymodelview.h directorymodelview.cpp
    modeltextgenerationgroupbox.h modeltextgenerationgroupbox.cpp modeltextgenerationgroupbox.ui
)
target_link_libraries(modeltextgenerationwidget PRIVATE
    Qt6::Core
    Qt6::Widgets
)
target_link_libraries(modeltextgenerationwidget PRIVATE
    activationfunctions    
    randommanaging
    textgenerator
    neuralnetwork
    textembedding
    optimizer
    exception
    trainer
    matrix
    loss
)
target_include_directories(modeltextgenerationwidget PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
