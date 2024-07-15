qt_add_library(pagesandbox STATIC
    newmodelgroupbox.h newmodelgroupbox.cpp newmodelgroupbox.ui
    pagesandbox.h pagesandbox.cpp pagesandbox.ui
    aboutlayersdialog.h aboutlayersdialog.cpp aboutlayersdialog.ui
    aboutlearningdatadialog.h aboutlearningdatadialog.cpp aboutlearningdatadialog.ui
    aboutmodeldatadialog.h aboutmodeldatadialog.cpp aboutmodeldatadialog.ui
)
target_link_libraries(pagesandbox PRIVATE
    Qt6::Core
    Qt6::Widgets
)
target_link_libraries(pagesandbox PRIVATE
    activationfunctions
    neuralnetwork
    textembedding
    exception
    matrix
    loss
)
target_include_directories(pagesandbox PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
