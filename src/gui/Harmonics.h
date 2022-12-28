#include <juce_dsp/juce_dsp.h>
class Harmonics {
public:
    void perform();

private:
    juce::dsp::FFT fft{10};
};
