#include <juce_dsp/juce_dsp.h>
#include <juce_core/juce_core.h>
#include <juce_audio_basics/juce_audio_basics.h>
#include <span>
#pragma once

class Harmonic {
public:
    Harmonic(
            const float& phase, const float& amplitude,
             const float& x, const float& y
     ) :
             phase(phase), amplitude(amplitude), x(x), y(y)
    {}

    [[nodiscard]] const float &getPhase() const {
        return phase;
    }

    [[nodiscard]] const float &getAmplitude() const {
        return amplitude;
    }

    [[nodiscard]] const float &getX() const {
        return x;
    }

    [[nodiscard]] const float &getY() const {
        return y;
    }

private:
    const float& phase;
    const float& amplitude;
    const float &x;
    const float &y;
};

class Harmonics {
public:
    Harmonics(
            const size_t size,
            std::unique_ptr<float[]>&& phases,
            std::unique_ptr<float[]>&& amplitudes,
            juce::dsp::ProcessSpec processSpec
    ) :
            size(size), phases(std::move(phases)),
            amplitudes(std::move(amplitudes)),
            x(std::make_unique<float[]>(size)),
            y(std::make_unique<float[]>(size)),
            processSpec(processSpec)
    {
        calculate_xy();
    }

    [[nodiscard]] Harmonic getHarmonic(const size_t index) const {
        return Harmonic{
            phases.get()[index],
            amplitudes.get()[index],
            x.get()[index],
            y.get()[index]
        };
    }

    [[nodiscard]] size_t getSize() const {
        return size;
    }

    void rotate(float omega) {
        for (size_t i = 0; i < size; ++i) {
            phases.get()[i] += omega;
            if (phases.get()[i] > juce::MathConstants<float>::pi) {
                phases.get()[i] -= 2 * juce::MathConstants<float>::pi;
            }
        }
        calculate_xy();
    }

private:
    const size_t size;
    const std::unique_ptr<float[]> phases;
    const std::unique_ptr<float[]> amplitudes;
    const std::unique_ptr<float[]> x, y;
    const juce::dsp::ProcessSpec processSpec;

    void calculate_xy() {
        for (size_t i = 0; i <= size; ++i) {
            x.get()[i] = juce::dsp::FastMathApproximations::cos(phases.get()[i]);
            y.get()[i] = juce::dsp::FastMathApproximations::sin(phases.get()[i]);
        }
    }
};
