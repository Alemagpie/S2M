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

# -------------------------
# Your executable
# -------------------------
add_executable(s2m
    src/main.cpp
)

target_link_libraries(s2m
    PRIVATE
        rtaudio
        rtmidi
)

target_include_directories(s2m PRIVATE
    external/Yin-Pitch-Tracking
    include
)