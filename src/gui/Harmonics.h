#include <juce_dsp/juce_dsp.h>
#pragma once

template <typename PhaseType, typename AmplitudeType>
class Harmonic {
public:
    Harmonic(PhaseType& phase, AmplitudeType& amplitude)
            : phase(phase), amplitude(amplitude)
    {}

    const PhaseType &getPhase() const {
        return phase;
    }

    const AmplitudeType &getAmplitude() const {
        return amplitude;
    }

    void setPhase(PhaseType phase) {
        Harmonic::phase = phase;
    }

    void setAmplitude(AmplitudeType amplitude) {
        Harmonic::amplitude = amplitude;
    }

private:
    PhaseType& phase;
    AmplitudeType& amplitude;
};


template <typename PhaseType, typename AmplitudeType>
class Harmonics {
public:
    Harmonics(size_t size, std::unique_ptr<PhaseType[]>&& phases, std::unique_ptr<AmplitudeType[]>&& amplitudes)
            : size(size), phases(std::move(phases)), amplitudes(std::move(amplitudes))
    {}

    Harmonic<PhaseType, AmplitudeType> getHarmonic(size_t index) {
        return Harmonic<PhaseType, AmplitudeType>(*(phases.get() + index), *(amplitudes.get() + index));
    }

    size_t getSize() {
        return size;
    }

private:
    size_t size;
    std::unique_ptr<PhaseType[]> phases;
    std::unique_ptr<AmplitudeType[]>  amplitudes;
};
