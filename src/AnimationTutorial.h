


#pragma once
#include <juce_graphics/juce_graphics.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_gui_extra/juce_gui_extra.h>
#include <juce_core/juce_core.h>
#include <juce_dsp/juce_dsp.h>
#include "gui/FourierCircle.h"
#include "gui/Harmonics.h"
#include <random>

//==============================================================================
class MainContentComponent   : public juce::AnimatedAppComponent,
                               public juce::Button::Listener
{
public:
    void buttonClicked(juce::Button *button) override {

    }

    //==============================================================================
    MainContentComponent()
    {
        setSize (800, 600);
        setFramesPerSecond(frameRate);
        myButton.setBounds(10, 10, 100, 40);
        myButton.addListener(this);
        addAndMakeVisible(myButton);

        juce::dsp::ProcessSpec processSpec{};
        processSpec.sampleRate = frameRate;
        processSpec.numChannels = 1;
        processSpec.maximumBlockSize = 512;

        std::unique_ptr<float[]> phases = makeRandomPhases(7);
        std::unique_ptr<float[]> amplitudes{new float[7]{10, 5, 4, 3, 2, 1, 0.5}};
        harmonics = std::make_unique<Harmonics>(7, std::move(phases), std::move(amplitudes), processSpec);
    }

    [[nodiscard]] std::unique_ptr<float[]> makeRandomPhases(size_t n) const {
        std::unique_ptr<float[]> phases = std::make_unique<float[]>(n);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dis(0, 2 * juce::MathConstants<float>::pi);

        for (int i = 0; i < n; ++i)
        {
            phases[i] = dis(gen);
        }
        return phases;
    }


    void update() override
    {
        float w = 0.3f  * 2 * juce::MathConstants<float>::pi / (float) frameRate;
        harmonics->rotate(w);
    }

    void paint (juce::Graphics& g) override
    {


//        / // (Our component is opaque, so we must completely fill the background with a solid colour)
        g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
        g.setColour (getLookAndFeel().findColour (juce::Slider::thumbColourId));

        FourierCircle* prevCircle{nullptr};
        for(int i=0; i< harmonics->getSize(); ++i) {
            const Harmonic &harmonic = harmonics->getHarmonic(i);
            auto* fourierCircle = new FourierCircle{prevCircle, getWidth(), getHeight(),
                                                    harmonic.getX(),
                                                    harmonic.getY(),
                                                    harmonic.getAmplitude()/5};
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
    juce::TextButton myButton{"Click"};
    int frameRate = 60;
    std::unique_ptr<Harmonics> harmonics;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};
