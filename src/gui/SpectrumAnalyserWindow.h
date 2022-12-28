#pragma once
#include <juce_graphics/juce_graphics.h>
#include <juce_core/juce_core.h>
#include <juce_gui_basics/juce_gui_basics.h>
class SpectrumAnalyserWindow    : public juce::DocumentWindow
{
public:
    SpectrumAnalyserWindow (const juce::String& name, juce::Component* c, juce::JUCEApplication& a)
            : DocumentWindow (name, juce::Desktop::getInstance().getDefaultLookAndFeel()
                                      .findColour (ResizableWindow::backgroundColourId),
                              juce::DocumentWindow::allButtons),
              app (a)
    {
        setUsingNativeTitleBar (true);
        setContentOwned (c, true);

#if JUCE_ANDROID || JUCE_IOS
        setFullScreen (true);
#else
        setResizable (true, false);
        setResizeLimits (300, 250, 10000, 10000);
        centreWithSize (getWidth(), getHeight());
#endif

        setVisible (true);
    }

    void closeButtonPressed() override
    {
        app.systemRequestedQuit();
    }

private:
    juce::JUCEApplication& app;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SpectrumAnalyserWindow)
};
