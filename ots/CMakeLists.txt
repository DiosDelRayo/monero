cmake_minimum_required(VERSION 3.10)
project(monero-ots VERSION 0.1.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Require C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Options
option(BUILD_TESTS "Build test suite" OFF)
option(BUILD_SHARED_LIBS "Build shared library" OFF)  # Default to static

# Require Monero source directory
if(NOT MONERO_SOURCE_DIR)
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../src/crypto/crypto.cpp")
        set(MONERO_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/..)
    else()
        message(FATAL_ERROR "Please specify MONERO_SOURCE_DIR pointing to Monero source")
    endif()
endif()

# Version configuration
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/src/version.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/include/version.h
)

# Main library
add_library(monero-ots
    src/ots.cpp
	# src/ots-abi.cpp
	src/address.cpp
    src/key-jar.cpp
	src/seed-jar.cpp
	src/seed-language.cpp
	src/seed.cpp
	src/seed-legacy.cpp
	src/seed-monero.cpp
	src/seed-polyseed.cpp
	src/wallet.cpp
)

# Add version definitions
target_compile_definitions(monero-ots
    PRIVATE
        OTS_VERSION="${PROJECT_VERSION}"
)

# Include directories
target_include_directories(monero-ots
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        ${MONERO_SOURCE_DIR}/src
        ${MONERO_SOURCE_DIR}/contrib/epee/include
        ${MONERO_SOURCE_DIR}/external/easylogging++
)

# Library properties
set_target_properties(monero-ots PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    C_VISIBILITY_PRESET hidden
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN ON
    POSITION_INDEPENDENT_CODE ON
)

# Tests configuration
if(BUILD_TESTS)
	enable_testing()
	add_subdirectory(tests)
endif()

# Installation rules
install(TARGETS monero-ots
    EXPORT monero-ots-targets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

install(FILES
    include/ots.h
    include/ots.hpp
    ${CMAKE_CURRENT_BINARY_DIR}/include/version.h
    DESTINATION include/monero-ots
)

install(EXPORT monero-ots-targets
    FILE monero-ots-targets.cmake
    NAMESPACE MoneroOTS::
    DESTINATION lib/cmake/monero-ots
)

# Generate and install package config files
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/monero-ots-config-version.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/monero-ots-config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/monero-ots-config.cmake
    INSTALL_DESTINATION lib/cmake/monero-ots
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/monero-ots-config.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/monero-ots-config-version.cmake
    DESTINATION lib/cmake/monero-ots
)

# Doxygen documentation
find_package(Doxygen)
if(DOXYGEN_FOUND)
    # Set the Doxyfile input and output directories
    set(DOXYGEN_INPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/src")
    set(DOXYGEN_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/docs")

    # Configure the Doxyfile
    configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in
        ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        @ONLY
    )

    # Add custom target for documentation
    add_custom_target(docs
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM
    )
endif()
