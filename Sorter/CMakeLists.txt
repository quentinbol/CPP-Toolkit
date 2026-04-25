add_executable(sorter_demo test.cpp)

target_include_directories(sorter_demo
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/strategy
)

target_compile_features(sorter_demo PRIVATE cxx_std_20)
