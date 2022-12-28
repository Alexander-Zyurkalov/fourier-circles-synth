

#pragma once
#include "juce_audio_basics/juce_audio_basics.h"
#include "juce_audio_utils/juce_audio_utils.h"
//==============================================================================
class AnalyserComponent   : public juce::AudioAppComponent,
                            private juce::Timer
{
public:
    AnalyserComponent()
    {
        setOpaque (true);
        setAudioChannels (2, 0);  // we want a couple of input channels but no outputs
        startTimerHz (30);
        setSize (700, 500);
    }

    ~AnalyserComponent() override
    {
        shutdownAudio();
    }

    //==============================================================================
    void prepareToPlay (int, double) override {}
    void releaseResources() override          {}

    void getNextAudioBlock (const juce::AudioSourceChannelInfo&) override {}

    //==============================================================================
    void paint (juce::Graphics& g) override
    {
        g.fillAll (juce::Colours::black);

        g.setOpacity (1.0f);
        g.setColour (juce::Colours::white);
        drawFrame (g);
    }

    void timerCallback() override {}

    void pushNextSampleIntoFifo (float) noexcept
    {
        // if the fifo contains enough data, set a flag to say
        // that the next frame should now be rendered..
    }

    void drawNextFrameOfSpectrum() {}
    void drawFrame (juce::Graphics&)     {}

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AnalyserComponent)
};
