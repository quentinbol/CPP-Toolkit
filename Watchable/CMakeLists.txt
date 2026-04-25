add_executable(watchable_demo test.cpp)

target_include_directories(watchable_demo
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(watchable_demo PRIVATE cxx_std_20)
