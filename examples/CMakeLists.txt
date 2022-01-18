add_executable(mini_example 01_mini_example/main.cxx)
target_compile_features(mini_example PUBLIC cxx_std_11)
target_include_directories(mini_example
    PRIVATE
        ${PROJECT_SOURCE_DIR}/src/include
)
target_link_directories( mini_example
    PRIVATE
      ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}/
)
target_link_libraries( mini_example
    PRIVATE
        libEasyMsg
)
set_target_properties(mini_example PROPERTIES CXX_EXTENSIONS OFF)
