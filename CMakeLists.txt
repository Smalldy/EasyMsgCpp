cmake_minimum_required(VERSION 3.12)

project(LIBEASYMSG CXX)

#${CMAKE_INSTALL_LIBDIR}
#${CMAKE_INSTALL_BINDIR}


set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
        ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY
        ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
        ${PROJECT_BINARY_DIR}/bin)


set(PROJECT_DESCRIPTION "EasyMsg is a simple tool for comuniation between objects")
set(PROJECT_VERSION_MAJOR "1")
set(PROJECT_VERSION_MINOR "0")
set(PROJECT_VERSION_PATCH "0")
set(PROJECT_VERSION "${META_VERSION_MAJOR}.${META_VERSION_MINOR}.${META_VERSION_PATCH}")

set(BOOST_DIR "D:/cmakelib/boost/" CACHE PATH "boost install dir" FORCE)
message("BOOST_DIR = " ${BOOST_DIR})

add_subdirectory(src)
add_subdirectory(examples)
