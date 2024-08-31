qt_add_library(modeltextgenerationwidget STATIC
    pagemodel.h pagemodel.cpp pagemodel.ui
    directorymodelview.h directorymodelview.cpp
)
target_link_libraries(modeltextgenerationwidget PRIVATE
    Qt6::Core
    Qt6::Widgets
)
target_link_libraries(modeltextgenerationwidget PRIVATE
    activationfunctions
    textgeneration
    randommanaging
    neuralnetwork
    textembedding
    optimizer
    exception
    trainer
    matrix
    loss
)
target_include_directories(modeltextgenerationwidget PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
