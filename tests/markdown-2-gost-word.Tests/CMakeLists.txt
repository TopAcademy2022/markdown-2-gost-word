add_library(UnitTest SHARED
    pch.h
    pch.cpp
    UnitTest.cpp
    ../../markdown-2-gost-word/MdSection.cpp
    ../../markdown-2-gost-word/MdSection.h
    ../../markdown-2-gost-word/MdSectionRule.cpp
    ../../markdown-2-gost-word/MdSectionRule.h
    ../../markdown-2-gost-word/MdSectionType.h
)

target_include_directories(UnitTest PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../../markdown-2-gost-word
)

target_precompile_headers(UnitTest PRIVATE pch.h)

add_dependencies(UnitTest markdown-2-gost-word)

set_target_properties(UnitTest PROPERTIES
    VS_GLOBAL_ProjectTypes "{3AC096D0-A1C2-E12C-1390-A8335801FDAB}"
)

if(DEFINED ENV{VCToolsInstallDir})
    file(TO_CMAKE_PATH "$ENV{VCToolsInstallDir}../../Auxiliary/VS/UnitTest" _vs_unittest_default)
else()
    set(_vs_unittest_default "")
endif()

set(VS_UNITTEST_ROOT "${_vs_unittest_default}" CACHE PATH
    "Path to VS's Auxiliary/VS/UnitTest folder (contains include/ and lib/)")

if(NOT VS_UNITTEST_ROOT)
    message(FATAL_ERROR
        "VS_UNITTEST_ROOT could not be auto-detected. Configure from a "
        "'Developer Command Prompt for VS', or pass "
        "-DVS_UNITTEST_ROOT=\"C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Auxiliary/VS/UnitTest\"")
endif()

target_include_directories(UnitTest PRIVATE "${VS_UNITTEST_ROOT}/include")
target_link_directories(UnitTest PRIVATE
    "${VS_UNITTEST_ROOT}/lib/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>")

find_program(VSTEST_EXECUTABLE vstest.console.exe)
if(VSTEST_EXECUTABLE)
    add_test(NAME UnitTest COMMAND ${VSTEST_EXECUTABLE} $<TARGET_FILE:UnitTest>)
else()
    message(WARNING "vstest.console.exe not found - 'ctest' won't be able to run UnitTest. "
                     "You can still run it from VS Test Explorer.")
endif()