cmake_minimum_required(VERSION 3.6)
project(TsunagariC_Testing)

include(TsunagariC/CMakeLists.txt)
include(src/CMakeLists.txt)

if (WIN32 OR APPLE)
    set(EXE_NAME "Tsunagari")
else()
    set(EXE_NAME "tsunagari")
endif()

add_executable(${EXE_NAME} ${GUI_TYPE} ${TSUNAGARIC_TESTING_SOURCES} ${TSUNAGARIC_SOURCES})
target_link_libraries(${EXE_NAME} ${TSUNAGARIC_LIBRARIES})
