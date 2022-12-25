//
// Created by Alexandr Zyurkalov on 15.12.22.
//

#include <juce_gui_basics/juce_gui_basics.h>

class FourierCircle {
private:
    float radius;
    juce::Point<float> center, pointOnArc;
    juce::Rectangle<float> plotArea;
    juce::Line<float> line;
public:
    FourierCircle() = delete;

    FourierCircle(const FourierCircle* const prevCircle , int windowWidth, int windowHeight,
                  float deltaX, float deltaY, float amplitude);

    void paint(juce::Graphics& g);

    const juce::Point<float> &getPointOnArc() const;
};


