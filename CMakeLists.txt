cmake_minimum_required(VERSION 3.14)
project(markdown-2-gost-word
    VERSION 1.0.0
    DESCRIPTION "Markdown to GOST Word converter"
    LANGUAGES CXX
)

# Windows x64
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    add_definitions(-D_WIN64)
endif()

# Set C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# UTF-8 support for MSVC
if(MSVC)
    add_compile_options(/utf-8)
endif()

# Build configuration
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# Include directories (header files are in source directory)
include_directories(${CMAKE_SOURCE_DIR}/markdown-2-gost-word)

# Source files
set(SOURCES
    markdown-2-gost-word/markdown-2-gost-word.cpp
    markdown-2-gost-word/MdSectionParser.cpp
    markdown-2-gost-word/MdSectionConverter.cpp
    markdown-2-gost-word/OpenXmlService.cpp
    markdown-2-gost-word/MdSection.cpp
    markdown-2-gost-word/MdSectionRule.cpp
    markdown-2-gost-word/GostWordSection.cpp
    markdown-2-gost-word/ClrParser.cpp
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Set output directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Post-build command: copy example.md to output directory
if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_SOURCE_DIR}/markdown-2-gost-word/example.md
            $<TARGET_FILE_DIR:${PROJECT_NAME}>/example.md
        COMMENT "Copying example.md to output directory"
    )
    # Copy OpenXML SDK DLLs to output directory
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_SOURCE_DIR}/markdown-2-gost-word/DocumentFormat.OpenXml.dll
            $<TARGET_FILE_DIR:${PROJECT_NAME}>/DocumentFormat.OpenXml.dll
        COMMENT "Copying DocumentFormat.OpenXml.dll to output directory"
    )
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_SOURCE_DIR}/markdown-2-gost-word/DocumentFormat.OpenXml.Framework.dll
            $<TARGET_FILE_DIR:${PROJECT_NAME}>/DocumentFormat.OpenXml.Framework.dll
        COMMENT "Copying DocumentFormat.OpenXml.Framework.dll to output directory"
    )
endif()
