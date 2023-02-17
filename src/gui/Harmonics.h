#include <juce_dsp/juce_dsp.h>
#include <span>
#pragma once

class Harmonic {
public:
    Harmonic(float& phase, float& amplitude)
            : phase(phase), amplitude(amplitude)
    {}

    const float &getPhase() const {
        return phase;
    }

    const float &getAmplitude() const {
        return amplitude;
    }

private:
    float& phase;
    float& amplitude;
};


class Harmonics {
public:
    Harmonics(size_t size, std::unique_ptr<float[]>&& phases, std::unique_ptr<float[]>&& amplitudes)
            : size(size), phases(std::move(phases)), 
              amplitudes(std::move(amplitudes))
//              phasesSpan{phases.get(), size}
    {}

    Harmonic getHarmonic(size_t index) {
        return Harmonic(*(phases.get() + index), *(amplitudes.get() + index));
    }

    size_t getSize() {
        return size;
    }

    void rotate(float omega) {
        std::span<float> phasesSpan{phases.get(), size};
        std::for_each(phasesSpan.begin(), phasesSpan.end(), [omega](float& v){v+=omega;});
    }


private:
    size_t size;
    std::unique_ptr<float[]> phases;
    std::unique_ptr<float[]>  amplitudes;
//    std::array<float, 7> x{}, y{};
//    std::span<float> phasesSpan;
};
