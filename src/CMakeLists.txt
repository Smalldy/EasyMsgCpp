option(BUILD_SHARED_LIBS "Specifies the type of libraries (SHARED or STATIC) to build" OFF)
message(STATUS "Start building : " ${PROJECT_NAME})

if (BUILD_SHARED_LIBS)
    add_library(EasyMsg SHARED)
    target_compile_definitions(EasyMsg PUBLIC -DEASYMSG_SHARED_BUILD)
    target_compile_definitions(EasyMsg PRIVATE -DEASYMSG_EXPORTS)
else()
    add_library(EasyMsg STATIC)
endif()

target_compile_features(EasyMsg PUBLIC cxx_std_11)
set_target_properties(EasyMsg PROPERTIES CXX_EXTENSIONS OFF)

set(EASYMASG_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_sources(EasyMsg
    PRIVATE
        easy_msg.cpp
        easymsg_callback.cpp
        easymsg_dispatcher.cpp
        easymsg_subscriber.cpp

        include/easymsg_export.h
        include/easy_msg.h
        include/easymsg_callback.h
        include/easymsg_dispatcher.h
        include/easymsg_subscriber.h
)

target_include_directories(EasyMsg
    PRIVATE
        ${EASYMASG_INCLUDE_DIR})


set(CMAKE_INSTALL_PREFIX ${PROJECT_BINARY_DIR}/install)

install(TARGETS EasyMsg
        EXPORT  EasyMsgTargets
        RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        )

# 安装头文件
install(DIRECTORY ${PROJECT_SOURCE_DIR}/src/include DESTINATION ${CMAKE_INSTALL_PREFIX})
# 将目标文件可导出文件
install(EXPORT EasyMsgTargets DESTINATION ${PROJECT_SOURCE_DIR}/cmake)
# 生成 ${Target}Config.cmake
configure_file(${PROJECT_SOURCE_DIR}/config/EasyMsgConfig.cmake.in ${PROJECT_SOURCE_DIR}/cmake/EasyMsgConfig.cmake)
install(FILES ${PROJECT_SOURCE_DIR}/cmake/EasyMsgConfig.cmake DESTINATION ${CMAKE_INSTALL_PREFIX}/cmake)

message(STATUS "Stop building : " ${PROJECT_NAME})
