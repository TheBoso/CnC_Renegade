# Interface libraries to set common defines and includes, avoid duplication later
add_library(wwcommon INTERFACE)

target_compile_definitions(wwcommon INTERFACE
    #NOMINMAX
    #WIN32_LEAN_AND_MEAN
    #_WIN32_WINNT=0x400
    #_MBCS
    _CRT_NONSTDC_NO_WARNINGS
    _CRT_SECURE_NO_WARNINGS
    $<$<CONFIG:Debug>:WWDEBUG>
    $<$<CONFIG:Debug>:_DEBUG>
)

target_compile_options(wwcommon INTERFACE
    ${WARNING_FLAGS}
)

target_include_directories(wwcommon INTERFACE
    BinkMovie
    Combat
    Commando
    SControl
    ww3d2
    WWAudio
    wwbitpack
    wwdebug
    wwlib
    WWMath
    wwnet
    WWOnline
    wwphys
    wwsaveload
    wwtranslatedb
    wwui
    wwutil
    wolapi
    .
)

target_link_libraries(wwcommon INTERFACE
    milesstub
    binkstub
    gamespy
    d3d8lib
)

# Module static libraries
add_subdirectory(BinkMovie)
add_subdirectory(Combat)
add_subdirectory(SControl)
add_subdirectory(ww3d2)
add_subdirectory(wwaudio)
add_subdirectory(wwbitpack)
add_subdirectory(wwdebug)
add_subdirectory(wwlib)
add_subdirectory(WWMath)
add_subdirectory(wwnet)
add_subdirectory(WWOnline)
add_subdirectory(wwphys)
add_subdirectory(wwsaveload)
add_subdirectory(wwtranslatedb)
add_subdirectory(wwui)
add_subdirectory(wwutil)

# Final targets
add_subdirectory(BandTest)
add_subdirectory(Scripts)
add_subdirectory(Commando)

if (RENEGADE_TOOLS)
    add_subdirectory(Tools)
endif()
