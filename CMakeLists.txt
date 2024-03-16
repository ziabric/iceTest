cmake_minimum_required(VERSION 3.6)

project(iceTest VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

include_directories( ${PROJECT_SOURCE_DIR}/ )
include_directories( ${PROJECT_SOURCE_DIR}/imgui )
include_directories( ${PROJECT_SOURCE_DIR}/udp )

find_package(SFML COMPONENTS system graphics audio network REQUIRED)

set(IMGUI
        imgui/imconfig.h
        imgui/imgui.cpp
        imgui/imgui.h
        imgui/imgui_demo.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_internal.h
        imgui/imgui_tables.cpp
        imgui/imgui_widgets.cpp
        imgui/imstb_rectpack.h
        imgui/imstb_textedit.h
        imgui/imstb_truetype.h
        imgui/imconfig-SFML.h
        imgui/imgui-SFML.cpp
        imgui/imgui-SFML.h
        imgui/imgui-SFML_export.h
)

set(SOURCES
        ${PROJECT_SOURCE_DIR}/udp/ClientUDPThread.h
        ${PROJECT_SOURCE_DIR}/udp/ClientUDPThread.cpp
        ${PROJECT_SOURCE_DIR}/main.cpp
)

if(WIN32)
    add_executable(${PROJECT_NAME} WIN32 ${SOURCES} ${IMGUI})
    target_link_libraries(${PROJECT_NAME} PRIVATE sfml-window sfml-network sfml-graphics sfml-system opengl32 websockets)
endif()

if(UNIX)
    add_executable(${PROJECT_NAME} ${SOURCES} ${IMGUI})
    target_link_libraries(${PROJECT_NAME} PRIVATE sfml-window sfml-network sfml-graphics sfml-system GL websockets)
endif()
