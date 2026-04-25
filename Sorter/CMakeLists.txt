add_executable(sorter_demo src/test.cpp)

target_include_directories(sorter_demo
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/strategy
)

target_compile_features(sorter_demo PRIVATE cxx_std_20)
