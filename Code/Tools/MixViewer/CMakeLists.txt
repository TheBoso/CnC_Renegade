set(MIXVIEWER_SRC
    AVAssetSuck.cpp
    duplicatecombiner.cpp
    MainFrm.cpp
    MakeMixFileDialog.cpp
    MixCombiningDialog.cpp
    MixPatchMaker.cpp
    MixViewer.cpp
    MixViewer.rc
    MixViewerDoc.cpp
    MixViewerView.cpp
    StdAfx.cpp
    AVAssetSuck.h
    duplicatecombiner.h
    MainFrm.h
    MakeMixFileDialog.h
    MixCombiningDialog.h
    MixPatchMaker.h
    MixViewer.h
    MixViewerDoc.h
    MixViewerView.h
    Resource.h
    StdAfx.h
)

# Targets to build.
add_executable(mixviewer WIN32)

target_compile_definitions(mixviewer PRIVATE
    _AFXDLL
    $<$<CONFIG:Debug>:WWDEBUG>
    $<$<CONFIG:Debug>:_DEBUG>
)

target_include_directories(mixviewer PRIVATE
    ../../wwdebug
    ../../wwlib
    ../..
)

target_compile_options(mixviewer PRIVATE
    ${WARNING_FLAGS}
)

target_link_libraries(mixviewer PRIVATE wwdebug wwlib winmm)

target_sources(mixviewer PRIVATE ${MIXVIEWER_SRC})
