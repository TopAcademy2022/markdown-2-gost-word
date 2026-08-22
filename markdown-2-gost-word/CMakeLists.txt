string(REPLACE "/EHsc" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

foreach(_cfg DEBUG RELWITHDEBINFO)
    string(REPLACE "/RTC1" "" CMAKE_CXX_FLAGS_${_cfg} "${CMAKE_CXX_FLAGS_${_cfg}}")
endforeach()

add_executable(markdown-2-gost-word
    ClrParser.cpp
    ClrParser.h
    GostWordSection.cpp
    GostWordSection.h
    markdown-2-gost-word.cpp
    MdSection.cpp
    MdSection.h
    MdSectionConverter.cpp
    MdSectionConverter.h
    MdSectionParser.cpp
    MdSectionParser.h
    MdSectionRule.cpp
    MdSectionRule.h
    MdSectionType.h
    OpenXmlApi.h
    OpenXmlService.cpp
    OpenXmlService.h
)

target_compile_options(markdown-2-gost-word PRIVATE
    "/AI${CMAKE_CURRENT_SOURCE_DIR}"
)

target_compile_definitions(markdown-2-gost-word PRIVATE
    _CONSOLE
    $<$<CONFIG:Debug>:_DEBUG>
    $<$<CONFIG:Release>:NDEBUG>
)

set_target_properties(markdown-2-gost-word PROPERTIES
    VS_GLOBAL_CLRSupport "true"
    VS_DOTNET_REFERENCES "WindowsBase"
)

set_property(TARGET markdown-2-gost-word PROPERTY
    "VS_DOTNET_REFERENCE_DocumentFormat.OpenXml"
    "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/openxml/net46/DocumentFormat.OpenXml.dll")
set_property(TARGET markdown-2-gost-word PROPERTY
    "VS_DOTNET_REFERENCE_DocumentFormat.OpenXml.Framework"
    "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/openxml/net46/DocumentFormat.OpenXml.Framework.dll")

add_custom_command(TARGET markdown-2-gost-word POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/openxml/net46/DocumentFormat.OpenXml.dll"
        "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/openxml/net46/DocumentFormat.OpenXml.Framework.dll"
        "$<TARGET_FILE_DIR:markdown-2-gost-word>"
)