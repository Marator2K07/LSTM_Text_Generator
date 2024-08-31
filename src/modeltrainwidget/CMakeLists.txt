qt_add_library(modeltrainwidget STATIC
    modeltraininggroupbox.h modeltraininggroupbox.cpp modeltraininggroupbox.ui
    aboutcurmodelstatedialog.h aboutcurmodelstatedialog.cpp aboutcurmodelstatedialog.ui
    aboutoptimizerdialog.h aboutoptimizerdialog.cpp aboutoptimizerdialog.ui
    abouttrainingdialog.h abouttrainingdialog.cpp abouttrainingdialog.ui
)
target_link_libraries(modeltrainwidget PRIVATE
    Qt6::Core
    Qt6::Widgets
)
target_link_libraries(modeltrainwidget PRIVATE
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
target_include_directories(modeltrainwidget PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
