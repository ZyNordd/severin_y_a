add_library(MPprj MPprj.h MPprj.cpp)

add_executable(MPprj_test MPprj_test.cpp)
target_link_libraries(MPprj_test MPprj)