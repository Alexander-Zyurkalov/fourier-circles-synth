cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(FourierCirclesSynth VERSION 0.0.1 LANGUAGES CXX  )
cmake_policy(SET CMP0076 NEW)
set(CMAKE_CXX_STANDARD 20)
add_subdirectory(libs/JUCE)
juce_add_gui_app(FourierCirclesSynth PRODUCT_NAME "FourierCirclesSynth")
target_link_libraries(FourierCirclesSynth
        PRIVATE
            juce::juce_core
            juce::juce_data_structures
            juce::juce_events
            juce::juce_graphics
            juce::juce_gui_basics
            juce::juce_gui_extra
        )
add_subdirectory(src)
target_compile_definitions(FourierCirclesSynth
        PRIVATE
            JUCE_WEB_BROWSER=0
            JUCE_USE_CULR=0
            JUCE_APPLICATION_NAME_STRING="Geometric Median"
            JUCE_APPLICATION_VERSION="0.0.1"
        )
