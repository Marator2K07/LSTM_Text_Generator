qt_add_library(exception STATIC
    matrixexception.h matrixexception.cpp
    lossexception.h lossexception.cpp
    textembeddingexception.h textembeddingexception.cpp
    activationfunctionsexception.h activationfunctionsexception.cpp
    neuralnetworkexception.h neuralnetworkexception.cpp
    trainerexception.h trainerexception.cpp
)
target_link_libraries(exception PRIVATE
    Qt6::Core
)
target_link_libraries(exception PRIVATE
    
)
target_include_directories(exception PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
