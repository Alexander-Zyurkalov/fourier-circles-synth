#include <catch2/catch_test_macros.hpp>
#include <juce_core/juce_core.h>

TEST_CASE("Learning how jmap is working") {
    float phase = juce::MathConstants<float>::pi/2;
    float degree = juce::jmap<float>(
            phase,
            0.0f, juce::MathConstants<float>::pi,
            0.0f, 180.0f
    );
    REQUIRE(degree == 90.0f);
}

TEST_CASE("Learning roundToInt"){
    float myFloat = 3.9;
    int myInt = juce::roundToInt(myFloat);
    REQUIRE(myInt == 4);
}

TEST_CASE("Learning nextPowerOfTwo") {
    auto nextPowerOfTwo = juce::nextPowerOfTwo(66);
    REQUIRE(nextPowerOfTwo == 128);
}
