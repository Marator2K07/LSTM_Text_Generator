qt_add_library(newmodelwidget STATIC
    newmodelgroupbox.h newmodelgroupbox.cpp newmodelgroupbox.ui
    aboutlayersdialog.h aboutlayersdialog.cpp aboutlayersdialog.ui
    aboutlearningdatadialog.h aboutlearningdatadialog.cpp aboutlearningdatadialog.ui
    aboutmodeldatadialog.h aboutmodeldatadialog.cpp aboutmodeldatadialog.ui
)
target_link_libraries(newmodelwidget PRIVATE
    Qt6::Core
    Qt6::Widgets
)
target_link_libraries(newmodelwidget PRIVATE
    activationfunctions
    randommanaging
    neuralnetwork
    textembedding
    optimizer
    exception
    trainer
    matrix
    loss
)
target_include_directories(newmodelwidget PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
