add_executable(msgmatch_example 01_msgmatch_example/main.cxx)
target_compile_features(msgmatch_example PUBLIC cxx_std_11)
target_include_directories(msgmatch_example
    PRIVATE
        ${PROJECT_SOURCE_DIR}/src/include
)
target_link_directories( msgmatch_example
    PRIVATE
      ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}/
)
target_link_libraries( msgmatch_example
    PRIVATE
        libEasyMsg
)
set_target_properties(msgmatch_example PROPERTIES CXX_EXTENSIONS OFF)
