cmake_minimum_required(VERSION 3.18)
project(SignalToMidi)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# Build static libs to avoid DLL issues on Windows
set(BUILD_SHARED_LIBS OFF)

# -------------------------
# RtAudio
# -------------------------
FetchContent_Declare(
    rtaudio
    GIT_REPOSITORY https://github.com/thestk/rtaudio.git
    GIT_TAG master
)

set(RTAUDIO_API_WASAPI ON CACHE BOOL "" FORCE)
set(RTAUDIO_BUILD_TESTING OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(rtaudio)

# -------------------------
# RtMidi
# -------------------------
FetchContent_Declare(
    rtmidi
    GIT_REPOSITORY https://github.com/thestk/rtmidi.git
    GIT_TAG master
)

set(RTMIDI_API_WINMM ON CACHE BOOL "" FORCE)
set(RTMIDI_BUILD_TESTING OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(rtmidi)

FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG docking 
)
FetchContent_MakeAvailable(imgui)

add_executable(s2m 
    src/main.cpp
    src/AudioInputManager.cpp
    src/NoteDetector.cpp
    src/MidiOutputManager.cpp
    src/InstanceManager.cpp
    src/AppWindow.cpp
    src/UIManager.cpp
    external/Yin-Pitch-Tracking/Yin.c

    # ImGui core
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/imgui_demo.cpp   # optional, handy for exploring widgets — drop later

    # Win32 + DX11 backend
    ${imgui_SOURCE_DIR}/backends/imgui_impl_win32.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_dx11.cpp
)

target_sources(s2m PRIVATE
    src/AudioInputManager.cpp
    src/NoteDetector.cpp
    src/MidiOutputManager.cpp
    src/InstanceManager.cpp
    src/AppWindow.cpp
    src/UIManager.cpp
    external/Yin-Pitch-Tracking/Yin.c
)

target_link_libraries(s2m
    PRIVATE
        rtaudio
        rtmidi
        d3d11
        dxgi
)

target_include_directories(s2m PRIVATE
    external/Yin-Pitch-Tracking
    include
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
)