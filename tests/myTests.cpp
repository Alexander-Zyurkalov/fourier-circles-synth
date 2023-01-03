#include <catch2/catch_test_macros.hpp>
#include <juce_core/juce_core.h>
#include <juce_audio_basics/juce_audio_basics.h>
#include <catch2/catch_approx.hpp>
#include <juce_dsp/juce_dsp.h>

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

/**
 *  1. Generate a wave
 *  2. Use FFT function on it
 *  3. Reproduce the wave from the FFT
 *  4. Compare the waves.
 */

TEST_CASE("Learning FFT") {
    int fftOrder  = 11;
    int fftSize   = 1 << fftOrder;



}


TEST_CASE("Learning oscillators") {

    juce::dsp::ProcessSpec processSpec{};
    processSpec.sampleRate = 44100.0f;
    processSpec.numChannels = 1;
    processSpec.maximumBlockSize = 1024;



    const std::function <float(float)> mySine{
            []( const auto &x) {
                return std::sin(x);
            }
    };

    juce::dsp::Oscillator<float> oscillator{mySine, 100};
    oscillator.setFrequency(440);
    REQUIRE(oscillator.isInitialised());

    oscillator.prepare(processSpec);
    float phase = - juce::MathConstants<float>::pi;
    for (int i = 0; i < 100; ++i) {
        float y = oscillator.processSample(0);
        REQUIRE(y == Catch::Approx(std::sin(phase)).epsilon(0.001));
        phase += juce::MathConstants<float>::twoPi * oscillator.getFrequency()/processSpec.sampleRate;
    }
}