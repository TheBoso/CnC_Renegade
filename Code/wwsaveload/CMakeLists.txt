# Set source files
set(WWSAVELOAD_SRC
    definition.cpp
    definitionfactory.cpp
    definitionfactorymgr.cpp
    definitionmgr.cpp
    parameter.cpp
    persistfactory.cpp
    pointerremap.cpp
    saveload.cpp
    saveloadstatus.cpp
    saveloadsubsystem.cpp
    twiddler.cpp
    wwsaveload.cpp
    definition.h
    definitionclassids.h
    definitionfactory.h
    definitionfactorymgr.h
    definitionmgr.h
    editable.h
    parameter.h
    parameterlist.h
    parametertypes.h
    persist.h
    persistfactory.h
    pointerremap.h
    postloadable.h
    saveload.h
    saveloadids.h
    saveloadstatus.h
    saveloadstatus.h
    saveloadsubsystem.h
    simpledefinitionfactory.h
    simpleparameter.h
    twiddler.h
    wwsaveload.h
)

# Targets to build.
add_library(wwsaveload STATIC)

target_link_libraries(wwsaveload PRIVATE
    wwcommon
)

target_sources(wwsaveload PRIVATE ${WWSAVELOAD_SRC})

# This module needs building differently for the level editor
if (RENEGADE_TOOLS)
    # Targets to build.
    add_library(wwsaveloade STATIC)

    target_link_libraries(wwsaveloade PRIVATE
        wwcommon
    )

    target_compile_definitions(wwsaveloade PRIVATE PARAM_EDITING_ON)

    target_sources(wwsaveloade PRIVATE ${WWSAVELOAD_SRC})
endif()
