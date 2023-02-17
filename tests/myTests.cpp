#include <catch2/catch_test_macros.hpp>
#include <juce_core/juce_core.h>
#include <juce_audio_basics/juce_audio_basics.h>
#include <catch2/catch_approx.hpp>
#include <juce_dsp/juce_dsp.h>
#include "../src/gui/Harmonics.h"

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
    constexpr auto fftOrder = 10;
    constexpr auto fftSize  = 1 << fftOrder;

    const std::function <float(float)> mySine{
            []( const auto &x) {
                return std::sin(x);
            }
    };

    juce::dsp::Oscillator<float> oscillator{mySine};
    oscillator.setFrequency(440);

    juce::dsp::ProcessSpec processSpec{};
    processSpec.sampleRate = 44100.0f;
    processSpec.numChannels = 1;
    processSpec.maximumBlockSize = fftSize;
    oscillator.prepare(processSpec);


    juce::AudioBuffer<float> buffer{(int)processSpec.numChannels, (int) processSpec.maximumBlockSize};
    juce::dsp::AudioBlock<float> audioBlock{buffer};
    audioBlock.clear();
    juce::dsp::ProcessContextReplacing<float> context{audioBlock};

    oscillator.process(context);
    float phase = - juce::MathConstants<float>::pi;
    for (int i = 0; i < processSpec.maximumBlockSize/2; ++i) {
        float y = audioBlock.getSample(0, i);
        REQUIRE(y == Catch::Approx(std::sin(phase)).margin(0.004));
//        std::cout << phase << "\t" << y << std::endl;
        phase += juce::MathConstants<float>::twoPi * oscillator.getFrequency()/processSpec.sampleRate;
    }

    juce::dsp::WindowingFunction<float> window (fftSize, juce::dsp::WindowingFunction<float>::hann);
    float fftData[2 * fftSize];
    juce::zeromem (fftData, sizeof (fftData));
    memcpy (fftData, audioBlock.getChannelPointer(0), fftSize);
    juce::dsp::FFT forwardFFT{fftOrder};

    window.multiplyWithWindowingTable(fftData, fftSize);
    forwardFFT.performFrequencyOnlyForwardTransform(fftData, false);


    auto mindB = -100.0f;
    auto maxdB =    0.0f;
    auto scopeSize = fftSize/2;
    for (size_t i = 0; i < scopeSize; ++i) {

        auto skewedProportionX = 1.0f - std::exp (std::log (1.0f - (float) i / (float) scopeSize) * 0.2f);
        auto fftDataIndex = juce::jlimit (0, fftSize / 2, (int) (skewedProportionX * (float) fftSize * 0.5f));
        float dcb = juce::jlimit(
                mindB,
                maxdB,
                juce::Decibels::gainToDecibels(fftData[fftDataIndex]) - juce::Decibels::gainToDecibels((float) fftSize)
                );
        auto level = juce::jmap (dcb, mindB, maxdB, 0.0f, 1.0f);
        auto frequency = juce::jmap<float>((float)fftDataIndex, 0, scopeSize, 0, processSpec.sampleRate/2);
        std::cout << frequency  << "\t" << level << std::endl;
    }

}



TEST_CASE("Test Harmonics class", "[Harmonics]") {
    size_t size = 3;
    std::unique_ptr<float[]> phases(new float[size]);
    std::unique_ptr<float[]> amplitudes(new float[size]);

    phases[0] = 0.0f;
    phases[1] = 0.5f;
    phases[2] = 1.0f;

    amplitudes[0] = 1.0f;
    amplitudes[1] = 0.5f;
    amplitudes[2] = 0.1f;

    Harmonics<float, float> harmonics(size, std::move(phases), std::move(amplitudes));

    REQUIRE(phases == nullptr);

    SECTION("Test size") {
        REQUIRE(harmonics.getSize() == size);
    }

    SECTION("Test getHarmonic method") {
        Harmonic<float, float> harmonic = harmonics.getHarmonic(1);
        float initialPhase = 0.5f;
        REQUIRE(harmonic.getPhase() == initialPhase);
        REQUIRE(harmonic.getAmplitude() == 0.5f);

        harmonics.rotate(0.1f);
        REQUIRE(
                (initialPhase + 0.1f) == Catch::Approx( harmonic.getPhase() )
        );


    }
}