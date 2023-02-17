#include <juce_dsp/juce_dsp.h>
#include <span>
#pragma once

class Harmonic {
public:
    Harmonic(const float& phase, const float& amplitude)
            : phase(phase), amplitude(amplitude)
    {}

    [[nodiscard]] const float &getPhase() const {
        return phase;
    }

    [[nodiscard]] const float &getAmplitude() const {
        return amplitude;
    }

private:
    const float& phase;
    const float& amplitude;
};


class Harmonics {
public:
    Harmonics(const size_t size, std::unique_ptr<float[]>&& phases, std::unique_ptr<float[]>&& amplitudes)
            : size(size), phases(std::move(phases)),
              amplitudes(std::move(amplitudes))
    {}

    Harmonic getHarmonic(const size_t index) {
        return Harmonic{*(phases.get() + index), *(amplitudes.get() + index)};
    }

    [[nodiscard]] size_t getSize() const {
        return size;
    }

    void rotate(float omega) {
        std::span<float> phasesSpan{phases.get(), size};
        std::for_each(phasesSpan.begin(), phasesSpan.end(), [omega](float& v){v+=omega;});
    }

private:
    const size_t size;
    const std::unique_ptr<float[]> phases;
    const std::unique_ptr<float[]> amplitudes;
};
