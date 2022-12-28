


#pragma once
#include <juce_graphics/juce_graphics.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_gui_extra/juce_gui_extra.h>
#include <juce_core/juce_core.h>
#include <juce_dsp/juce_dsp.h>
#include "gui/FourierCircle.h"

//==============================================================================
class MainContentComponent   : public juce::AnimatedAppComponent
{
public:
    //==============================================================================
    MainContentComponent()
    {
        setSize (800, 600);
        setFramesPerSecond(frameRate);
    }

    void update() override
    {
        // This function is called at the frequency specified by the setFramesPerSecond() call
        // in the constructor. You can use it to update counters, animate values, etc.

        for(int i = 0; i < 7; i++) {
            float w = 0.3f * float(i + 1) * 2 * juce::MathConstants<float>::pi / (float) frameRate;
            phase[i] += w;
            if (phase[i] > juce::MathConstants<float>::pi )
                phase[i] -= 2 * juce::MathConstants<float>::pi;
            y[i] = juce::dsp::FastMathApproximations::sin(phase[i]);
            x[i] = juce::dsp::FastMathApproximations::cos(phase[i]);
        }
    }

    void paint (juce::Graphics& g) override
    {
//        / // (Our component is opaque, so we must completely fill the background with a solid colour)
        g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
        g.setColour (getLookAndFeel().findColour (juce::Slider::thumbColourId));

        FourierCircle* prevCircle{nullptr};
        for(int i=0; i< 7; ++i) {
            auto* fourierCircle = new FourierCircle{prevCircle, getWidth(), getHeight(),
                                        x[i],
                                        y[i], 1.0f/((float)i+1.0f)};
            fourierCircle->paint(g);
            delete prevCircle;
            prevCircle = fourierCircle;
        }
        delete prevCircle;
    }

    void resized() override
    {
        // This is called when the MainContentComponent is resized.
        // If you add any child components, this is where you should
        // update their positions.
    }

private:

    std::array<float, 7> phase{};
    std::array<float, 7> x{}, y{};
    int frameRate = 60;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};
