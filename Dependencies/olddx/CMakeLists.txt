add_library(d3d8lib INTERFACE)
target_link_libraries(d3d8lib INTERFACE d3d8 d3dx8 dinput8 dxguid)

if(MSVC AND CMAKE_CXX_COMPILER_VERSION VERSION_GREATER "12.0.8804")
    target_link_libraries(d3d8lib INTERFACE legacy_stdio_definitions)
endif()

target_compile_definitions(d3d8lib INTERFACE -DBUILD_WITH_D3D8)

if(MSVC AND ${CMAKE_VERSION} VERSION_GREATER "3.13.0")   
    target_link_directories(d3d8lib BEFORE INTERFACE .)
    target_include_directories(d3d8lib INTERFACE .)
    target_link_options(d3d8lib INTERFACE /NODEFAULTLIB:libci.lib)
    if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER "12.0.8804")
        target_link_options(d3d8lib INTERFACE /SAFESEH:NO)
    endif()
endif()
