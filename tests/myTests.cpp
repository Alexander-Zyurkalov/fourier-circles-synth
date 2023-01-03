#include <catch2/catch_test_macros.hpp>
#include <juce_core/juce_core.h>
#include <juce_audio_basics/juce_audio_basics.h>
#include <catch2/catch_approx.hpp>

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

TEST_CASE("Learning decibelsToGain"){
    auto gain = juce::Decibels::decibelsToGain<float>(0);
    REQUIRE(gain == 1.0f);

    gain = juce::Decibels::decibelsToGain<float>(10);
    REQUIRE(gain == Catch::Approx(3.16228f));

    gain = juce::Decibels::decibelsToGain<float>(20);
    REQUIRE(gain == Catch::Approx(10.0f));
}