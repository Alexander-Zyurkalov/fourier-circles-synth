//
// Created by Alexandr Zyurkalov on 28.12.22.
//

#include "Harmonics.h"
#include <juce_core/juce_core.h>

void Harmonics::perform() {
    std::array<float, 2048> data{};
    float phase = 0.0f;
    for (int i = 0; i < 1024; ++i) {
        phase += 0.303;
        data[i] = std::sin(phase);
    }
    fft.performRealOnlyForwardTransform(data.data(), true);

    std::cout << "hello";

}