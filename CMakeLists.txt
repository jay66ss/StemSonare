cmake_minimum_required(VERSION 3.16)
project(StemSonare VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(juce)

juce_add_gui_app(StemSonare
    COMPANY_NAME "ArturoAudio"
    PRODUCT_NAME "StemSonare"
)

target_sources(StemSonare PRIVATE
    Source/Main.cpp
)

target_link_libraries(StemSonare PRIVATE
    juce::juce_gui_basics
)
