cmake_minimum_required(VERSION 3.13)
project(TsunagariTestingWorld)

add_subdirectory(TsunagariC)

if(WIN32 OR APPLE)
    set(EXE "Tsu")
else()
    set(EXE "tsu")
endif()

add_executable(${EXE})
target_include_directories(${EXE} PRIVATE src)
target_link_libraries(${EXE} tsunagari)

target_sources(${EXE}
    PRIVATE src/ai/ai-wander.cpp
            src/ai/ai-wander.h
            src/areas/big-tree.cpp
            src/areas/big-tree.h
            src/areas/cave01.cpp
            src/areas/cave01.h
            src/areas/grove01.cpp
            src/areas/grove01.h
            src/areas/grove04.cpp
            src/areas/grove04.h
            src/areas/grove06.cpp
            src/areas/grove06.h
            src/areas/grove-house.cpp
            src/areas/grove-house.h
            src/areas/secret-room.cpp
            src/areas/secret-room.h
            src/world/clouds.cpp
            src/world/clouds.h
            src/world/world.cpp
            src/world/world.h
)

get_target_property(EXE_SOURCES ${EXE} SOURCES)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src
    FILES ${EXE_SOURCES}
)
